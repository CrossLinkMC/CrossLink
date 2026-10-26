#include "control/ControlServer.hpp"

#include "crosslink/api/Events.hpp"
#include "crosslink/api/Gateway.hpp"
#include "crosslink/api/net/ServerRegistry.hpp"

#include <algorithm>
#include <chrono>
#include <format>
#include <utility>

#ifdef CROSSLINK_PLATFORM_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

namespace crosslink::control {
namespace {

Logger& log() { return LoggerRegistry::instance().getOrCreate("control"); }

bool constantTimeEquals(std::string_view left, std::string_view right) {
    if (left.size() != right.size()) return false;
    unsigned char difference = 0;
    for (std::size_t index = 0; index < left.size(); ++index) {
        difference |= static_cast<unsigned char>(left[index]) ^ static_cast<unsigned char>(right[index]);
    }
    return difference == 0;
}

void closeSocket(SocketHandle socket) {
    if (socket == invalidSocket) return;
#ifdef CROSSLINK_PLATFORM_WINDOWS
    ::shutdown(socket, SD_BOTH);
    ::closesocket(socket);
#else
    ::shutdown(socket, SHUT_RDWR);
    ::close(socket);
#endif
}

/// Buffers a stream socket into '\n' terminated JSON documents.
class LineReader {
public:
    LineReader(SocketHandle socket, std::size_t maxLineBytes) : mSocket(socket), mMaxLineBytes(maxLineBytes) {}

    [[nodiscard]] Result<std::string> readLine() {
        while (true) {
            if (const auto newline = mBuffer.find('\n'); newline != std::string::npos) {
                auto line = mBuffer.substr(0, newline);
                mBuffer.erase(0, newline + 1);
                while (!line.empty() && (line.back() == '\r' || line.back() == ' ')) line.pop_back();
                if (line.empty()) continue;
                return line;
            }
            if (mBuffer.size() > mMaxLineBytes) {
                return std::unexpected(Error{std::format("a control message exceeded {} bytes", mMaxLineBytes)});
            }

            char chunk[8192];
            const auto received = ::recv(mSocket, chunk, sizeof(chunk), 0);
            if (received == 0) return std::unexpected(Error{"the agent closed the connection"});
            if (received < 0) return std::unexpected(Error{"recv failed on the control connection"});
            mBuffer.append(chunk, static_cast<std::size_t>(received));
        }
    }

private:
    SocketHandle mSocket;
    std::size_t  mMaxLineBytes;
    std::string  mBuffer;
};

} // namespace

ControlServer::ControlServer(Gateway& gateway) : mGateway(gateway) {}

ControlServer::~ControlServer() { stop(); }

Result<> ControlServer::start(config::ControlConfig const& config) {
    mConfig = config;

    if (mConfig.token.size() < 32) {
        return std::unexpected(Error{"control.token must be at least 32 characters; refusing to start an unprotected control plane"});
    }

#ifdef CROSSLINK_PLATFORM_WINDOWS
    WSADATA data{};
    if (::WSAStartup(MAKEWORD(2, 2), &data) != 0) return std::unexpected(Error{"WSAStartup failed"});
    mWinsockStarted = true;
#endif

    mListener = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (mListener == invalidSocket) return std::unexpected(Error{"cannot create the control socket"});

    int reuse = 1;
    (void)::setsockopt(mListener, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char*>(&reuse), sizeof(reuse));

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_port = htons(mConfig.listenPort);
    if (mConfig.listenHost == "0.0.0.0" || mConfig.listenHost.empty()) {
        address.sin_addr.s_addr = htonl(INADDR_ANY);
    } else if (::InetPtonA(AF_INET, mConfig.listenHost.c_str(), &address.sin_addr) != 1) {
        closeSocket(mListener);
        mListener = invalidSocket;
        return std::unexpected(Error{std::format("control.listenHost '{}' is not an IPv4 address", mConfig.listenHost)});
    }

    if (::bind(mListener, reinterpret_cast<sockaddr*>(&address), sizeof(address)) != 0) {
        const auto error = std::format("cannot bind the control plane at {}:{}", mConfig.listenHost, mConfig.listenPort);
        closeSocket(mListener);
        mListener = invalidSocket;
        return std::unexpected(Error{error});
    }
    if (::listen(mListener, SOMAXCONN) != 0) {
        closeSocket(mListener);
        mListener = invalidSocket;
        return std::unexpected(Error{"cannot listen on the control socket"});
    }

    mStopping.store(false);
    mAcceptThread = std::thread([this] { acceptLoop(); });
    mWatchdogThread = std::thread([this] { watchdogLoop(); });

    log().info("control plane listening on {}:{}", mConfig.listenHost, mConfig.listenPort);
    return {};
}

void ControlServer::stop() noexcept {
    mStopping.store(true);

    std::vector<std::shared_ptr<AgentChannelImpl>> channels;
    {
        std::lock_guard lock{mMutex};
        channels.swap(mChannels);
        if (mListener != invalidSocket) {
            closeSocket(mListener);
            mListener = invalidSocket;
        }
    }
    for (auto& channel : channels) {
        AgentRegistry::instance().detach(channel->server());
        channel->close("the gateway is shutting down");
    }

    if (mAcceptThread.joinable()) mAcceptThread.join();
    if (mWatchdogThread.joinable()) mWatchdogThread.join();

#ifdef CROSSLINK_PLATFORM_WINDOWS
    if (mWinsockStarted) {
        ::WSACleanup();
        mWinsockStarted = false;
    }
#endif
}

std::size_t ControlServer::channelCount() const {
    std::lock_guard lock{mMutex};
    return mChannels.size();
}

void ControlServer::acceptLoop() {
    while (!mStopping.load()) {
        sockaddr_in peer{};
#ifdef CROSSLINK_PLATFORM_WINDOWS
        int peerSize = sizeof(peer);
#else
        socklen_t peerSize = sizeof(peer);
#endif
        const auto socket = ::accept(mListener, reinterpret_cast<sockaddr*>(&peer), &peerSize);
        if (socket == invalidSocket) {
            if (mStopping.load()) return;
            continue;
        }

        char addressText[INET_ADDRSTRLEN] = {0};
        ::inet_ntop(AF_INET, &peer.sin_addr, addressText, sizeof(addressText));
        const auto remote = std::format("{}:{}", addressText, ntohs(peer.sin_port));

        // One thread per agent: there are only a handful of backend servers, and
        // a blocking reader keeps the protocol handling obvious.
        std::thread([this, socket, remote] { connectionLoop(socket, remote); }).detach();
    }
}

void ControlServer::connectionLoop(SocketHandle socket, std::string remote) {
    // An agent that connects and says nothing must not hold a socket open.
#ifdef CROSSLINK_PLATFORM_WINDOWS
    const DWORD handshakeTimeout = static_cast<DWORD>(mConfig.handshakeTimeoutSeconds) * 1000u;
    (void)::setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char*>(&handshakeTimeout), sizeof(handshakeTimeout));
#endif

    LineReader reader{socket, mConfig.maxLineBytes};

    const auto helloLine = reader.readLine();
    if (!helloLine) {
        log().warn("control connection from {} closed before hello: {}", remote, helloLine.error().message);
        closeSocket(socket);
        return;
    }

    const auto helloJson = Json::parse(*helloLine, nullptr, false, true);
    if (helloJson.is_discarded()) {
        log().warn("control connection from {} sent an invalid hello", remote);
        closeSocket(socket);
        return;
    }
    auto hello = Message::fromJson(helloJson);
    if (!hello || hello->kind != kinds::hello) {
        log().warn("control connection from {} did not start with '{}'", remote, kinds::hello);
        closeSocket(socket);
        return;
    }

    const auto token = hello->payload.value("token", std::string{});
    const auto serverId = hello->payload.value("serverId", std::string{});
    if (!constantTimeEquals(token, mConfig.token)) {
        log().error("control connection from {} presented a wrong token", remote);
        closeSocket(socket);
        return;
    }
    if (serverId.empty()) {
        log().warn("control connection from {} did not name a serverId", remote);
        closeSocket(socket);
        return;
    }
    if (!net::ServerRegistry::instance().has(ServerId{serverId})) {
        log().error("agent '{}' from {} is not a configured server", serverId, remote);
        closeSocket(socket);
        return;
    }

    const auto agentId = AgentId{std::format("agent-{}", mNextAgentId.fetch_add(1))};
    auto channel = std::make_shared<AgentChannelImpl>(agentId, ServerId{serverId}, remote, socket);
    if (const auto capabilities = hello->payload.find("capabilities"); capabilities != hello->payload.end()) {
        channel->setCapabilities(*capabilities);
    }

    Message ack;
    ack.kind = std::string{kinds::helloAck};
    ack.replyTo = hello->id;
    ack.payload = Json::object();
    ack.payload["gateway"] = mGateway.buildInfo().crossLinkVersion;
    ack.payload["protocolVersion"] = mGateway.buildInfo().protocolVersion;
    ack.payload["gameVersion"] = std::string{mGateway.buildInfo().gameVersion};
    ack.payload["transport"] = std::string{mGateway.buildInfo().transport};
    ack.payload["heartbeatSeconds"] = mConfig.heartbeatSeconds;
    if (!channel->sendLine(ack.toJson())) {
        channel->close("cannot answer the hello");
        return;
    }

    registerChannel(channel);
    log().info(
        "agent '{}' connected from {} (agent version {})",
        serverId,
        remote,
        hello->payload.value("agentVersion", std::string{"unknown"})
    );

    AgentOnlineEvent online;
    online.agent = agentId;
    online.server = ServerId{serverId};
    online.remote = remote;
    mGateway.events().emit(online);

    // Traffic keeps the socket alive; the watchdog only closes silent agents, and
    // closing the channel also unblocks the reader below.
#ifdef CROSSLINK_PLATFORM_WINDOWS
    const DWORD receiveTimeout = 0;
    (void)::setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char*>(&receiveTimeout), sizeof(receiveTimeout));
#endif

    while (!mStopping.load() && channel->online()) {
        const auto line = reader.readLine();
        if (!line) {
            dropChannel(channel, line.error().message);
            return;
        }
        const auto json = Json::parse(*line, nullptr, false, true);
        if (json.is_discarded()) {
            dropChannel(channel, "sent a malformed control message");
            return;
        }
        auto message = Message::fromJson(json);
        if (!message) {
            log().warn("agent '{}' sent an unusable message: {}", serverId, message.error().message);
            continue;
        }

        if (message->kind == kinds::ping) {
            Message pong;
            pong.kind = std::string{kinds::pong};
            pong.replyTo = message->id;
            pong.payload = Json::object();
            pong.payload["echo"] = message->payload;
            if (!channel->sendLine(pong.toJson())) {
                dropChannel(channel, "lost while answering a ping");
                return;
            }
            continue;
        }
        if (message->kind == kinds::bye) {
            dropChannel(channel, "the agent said goodbye");
            return;
        }

        channel->handleInbound(*message);
    }

    dropChannel(channel, mStopping.load() ? "the gateway is shutting down" : "the connection ended");
}

void ControlServer::watchdogLoop() {
    while (!mStopping.load()) {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        std::vector<std::shared_ptr<AgentChannelImpl>> channels;
        {
            std::lock_guard lock{mMutex};
            channels = mChannels;
        }
        const auto silenceLimit = std::chrono::seconds(static_cast<long long>(mConfig.heartbeatSeconds) * 3);
        for (auto& channel : channels) {
            channel->expireRequests();
            if (channel->silentFor(silenceLimit)) dropChannel(channel, "missed too many heartbeats");
        }
    }
}

void ControlServer::registerChannel(std::shared_ptr<AgentChannelImpl> const& channel) {
    {
        std::lock_guard lock{mMutex};
        // A reconnecting agent replaces the stale channel for the same server.
        std::erase_if(mChannels, [&channel](auto const& existing) {
            if (existing->server() != channel->server()) return false;
            existing->close("replaced by a newer connection");
            AgentRegistry::instance().detach(existing->server());
            return true;
        });
        mChannels.push_back(channel);
    }
    AgentRegistry::instance().attach(channel);
}

void ControlServer::dropChannel(std::shared_ptr<AgentChannelImpl> const& channel, std::string_view reason) {
    bool wasTracked = false;
    {
        std::lock_guard lock{mMutex};
        // Both the reader thread and the watchdog can notice a dead agent; only
        // the first one gets to report it.
        wasTracked = std::erase_if(mChannels, [&channel](auto const& existing) { return existing == channel; }) > 0;
    }
    if (!wasTracked) return;

    AgentRegistry::instance().detach(channel->server());
    channel->close(reason);

    AgentOfflineEvent offline;
    offline.agent = channel->id();
    offline.server = channel->server();
    offline.reason = std::string{reason};
    mGateway.events().emit(offline);
}

} // namespace crosslink::control
