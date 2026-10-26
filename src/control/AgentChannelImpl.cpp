#include "control/AgentChannelImpl.hpp"

#include "crosslink/api/Logger.hpp"

#include <format>
#include <utility>
#include <vector>

#ifndef CROSSLINK_PLATFORM_WINDOWS
#include <sys/socket.h>
#include <unistd.h>
#endif

namespace crosslink::control {
namespace {

Logger& log() { return LoggerRegistry::instance().getOrCreate("control"); }

bool writeAll(SocketHandle socket, std::string_view data) {
    std::size_t sent = 0;
    while (sent < data.size()) {
        const auto written = ::send(
            socket,
            data.data() + sent,
            static_cast<int>(data.size() - sent),
            0
        );
        if (written <= 0) return false;
        sent += static_cast<std::size_t>(written);
    }
    return true;
}

} // namespace

AgentChannelImpl::AgentChannelImpl(AgentId id, ServerId server, std::string remote, SocketHandle socket)
: mId(std::move(id)), mServer(std::move(server)), mRemote(std::move(remote)), mSocket(socket) {}

AgentChannelImpl::~AgentChannelImpl() { close("channel destroyed"); }

AgentId AgentChannelImpl::id() const { return mId; }

ServerId AgentChannelImpl::server() const { return mServer; }

std::string AgentChannelImpl::remote() const { return mRemote; }

bool AgentChannelImpl::online() const { return mOnline.load() && mSocket != invalidSocket; }

Json AgentChannelImpl::capabilities() const {
    std::lock_guard lock{mCapabilitiesMutex};
    return mCapabilities;
}

void AgentChannelImpl::setCapabilities(Json capabilities) {
    std::lock_guard lock{mCapabilitiesMutex};
    mCapabilities = std::move(capabilities);
}

bool AgentChannelImpl::sendLine(Json const& json) const {
    const auto line = json.dump() + "\n";
    std::lock_guard lock{mSendMutex};
    if (mSocket == invalidSocket) return false;
    if (!writeAll(mSocket, line)) {
        log().warn("agent '{}' lost the control connection while sending", mServer.str());
        mOnline.store(false);
        return false;
    }
    touch();
    return true;
}

Result<> AgentChannelImpl::notify(std::string_view kind, Json payload) const {
    Message message;
    message.kind = std::string{kind};
    message.payload = std::move(payload);
    if (!sendLine(message.toJson())) return std::unexpected(Error{std::format("cannot notify agent '{}'", mServer.str())});
    return {};
}

Result<Json> AgentChannelImpl::sendRequest(
    std::string_view         kind,
    Json                     payload,
    std::chrono::milliseconds timeout,
    ResponseHandler          handler
) const {
    if (!online()) return std::unexpected(Error{std::format("agent '{}' is offline", mServer.str())});

    auto pending = std::make_shared<Pending>();
    pending->handler = std::move(handler);
    pending->deadline = std::chrono::steady_clock::now() + timeout;
    const auto requestId = mNextRequestId.fetch_add(1);

    {
        std::lock_guard lock{mPendingMutex};
        mPending.emplace(requestId, pending);
    }

    Message message;
    message.id = requestId;
    message.kind = std::string{kind};
    message.payload = std::move(payload);
    if (!sendLine(message.toJson())) {
        std::lock_guard lock{mPendingMutex};
        mPending.erase(requestId);
        return std::unexpected(Error{std::format("cannot reach agent '{}'", mServer.str())});
    }

    // An async caller gets its answer from handleInbound() or from the watchdog
    // expiring the entry; only a blocking caller waits here.
    if (!pending->handler) return pending->result;

    std::unique_lock lock{pending->mutex};
    if (pending->condition.wait_for(lock, timeout, [&pending] { return pending->done; })) return pending->result;

    std::lock_guard pendingLock{mPendingMutex};
    mPending.erase(requestId);
    return std::unexpected(Error{std::format("agent '{}' did not answer '{}' within {} ms", mServer.str(), kind, timeout.count())});
}

Result<Json> AgentChannelImpl::request(std::string_view kind, Json payload, std::chrono::milliseconds timeout) const {
    return sendRequest(kind, std::move(payload), timeout, {});
}

Result<> AgentChannelImpl::requestAsync(
    std::string_view         kind,
    Json                     payload,
    ResponseHandler          handler,
    std::chrono::milliseconds timeout
) const {
    if (!handler) return std::unexpected(Error{"requestAsync needs a response handler"});
    auto result = sendRequest(kind, std::move(payload), timeout, std::move(handler));
    if (!result) return std::unexpected(result.error());
    return {};
}

void AgentChannelImpl::handleInbound(Message const& message) {
    touch();

    if (message.isReply()) {
        std::shared_ptr<Pending> pending;
        {
            std::lock_guard lock{mPendingMutex};
            const auto found = mPending.find(message.replyTo);
            if (found == mPending.end()) return;
            pending = found->second;
            mPending.erase(found);
        }

        {
            std::lock_guard lock{pending->mutex};
            if (message.kind == kinds::error) {
                const auto text = message.payload.value("message", std::string{"the agent reported an error"});
                pending->result = std::unexpected(Error{text});
            } else {
                pending->result = message.payload;
            }
            pending->done = true;
        }
        pending->condition.notify_all();
        if (pending->handler) pending->handler(pending->result);
        return;
    }

    auto result = AgentRegistry::instance().dispatch(message.kind, *this, message.payload);
    if (!message.isRequest()) {
        if (!result) log().debug("agent '{}' sent '{}' which nobody handled", mServer.str(), message.kind);
        return;
    }

    Message reply;
    reply.replyTo = message.id;
    if (result) {
        reply.kind = message.kind;
        reply.payload = *result;
    } else {
        reply.kind = std::string{kinds::error};
        reply.payload = Json::object();
        reply.payload["message"] = result.error().message;
        log().warn("agent '{}' request '{}' failed: {}", mServer.str(), message.kind, result.error().message);
    }
    (void)sendLine(reply.toJson());
}

void AgentChannelImpl::failAllPending(std::string_view reason) {
    std::vector<std::shared_ptr<Pending>> pending;
    {
        std::lock_guard lock{mPendingMutex};
        pending.reserve(mPending.size());
        for (auto& [id, entry] : mPending) pending.push_back(entry);
        mPending.clear();
    }
    for (auto& entry : pending) {
        {
            std::lock_guard lock{entry->mutex};
            entry->result = std::unexpected(Error{std::string{reason}});
            entry->done = true;
        }
        entry->condition.notify_all();
        if (entry->handler) entry->handler(entry->result);
    }
}

void AgentChannelImpl::close(std::string_view reason) noexcept {
    const bool wasOnline = mOnline.exchange(false);
    SocketHandle socket;
    {
        std::lock_guard lock{mSendMutex};
        socket = mSocket;
        mSocket = invalidSocket;
    }
    if (socket != invalidSocket) {
#ifdef CROSSLINK_PLATFORM_WINDOWS
        ::shutdown(socket, SD_BOTH);
        ::closesocket(socket);
#else
        ::shutdown(socket, SHUT_RDWR);
        ::close(socket);
#endif
    }
    failAllPending(reason);
    if (wasOnline) log().info("agent '{}' control channel closed: {}", mServer.str(), reason);
}

void AgentChannelImpl::expireRequests() {
    const auto now = std::chrono::steady_clock::now();
    std::vector<std::pair<std::uint64_t, std::shared_ptr<Pending>>> expired;
    {
        std::lock_guard lock{mPendingMutex};
        for (auto it = mPending.begin(); it != mPending.end();) {
            if (it->second->deadline <= now) {
                expired.emplace_back(it->first, it->second);
                it = mPending.erase(it);
                continue;
            }
            ++it;
        }
    }
    for (auto& [requestId, pending] : expired) {
        {
            std::lock_guard lock{pending->mutex};
            pending->result = std::unexpected(Error{std::format("agent '{}' did not answer request {}", mServer.str(), requestId)});
            pending->done = true;
        }
        pending->condition.notify_all();
        if (pending->handler) pending->handler(pending->result);
    }
}

void AgentChannelImpl::touch() const noexcept { mLastTraffic.store(std::chrono::steady_clock::now()); }

bool AgentChannelImpl::silentFor(std::chrono::seconds limit) const noexcept {
    return std::chrono::steady_clock::now() - mLastTraffic.load() > limit;
}

} // namespace crosslink::control
