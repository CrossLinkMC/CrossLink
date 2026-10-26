#include "crosslink/api/net/Pipeline.hpp"

#include "crosslink/api/net/Session.hpp"

#include <algorithm>
#include <mutex>
#include <utility>
#include <vector>

namespace crosslink::net {

std::string_view flowName(Flow flow) noexcept { return flow == Flow::ToClient ? "to-client" : "to-backend"; }

struct PacketContext::Impl {
    PlayerSession*  session{};
    Flow            flow{Flow::ToClient};
    proto::Packet*  packet{};
    ServerId        server;
    Verdict         verdict{Verdict::Forward};
    bool            currentBackend{true};
};

PacketContext::PacketContext(PlayerSession& session, Flow flow, proto::Packet& packet, ServerId server, bool currentBackend)
: mImpl(std::make_unique<Impl>()) {
    mImpl->session = &session;
    mImpl->flow = flow;
    mImpl->packet = &packet;
    mImpl->server = std::move(server);
    mImpl->currentBackend = currentBackend;
}

PacketContext::~PacketContext() = default;

PlayerSession& PacketContext::session() const noexcept { return *mImpl->session; }

Flow PacketContext::flow() const noexcept { return mImpl->flow; }

proto::Packet& PacketContext::packet() const noexcept { return *mImpl->packet; }

proto::PacketId PacketContext::id() const noexcept { return mImpl->packet->id(); }

ServerId const& PacketContext::server() const noexcept { return mImpl->server; }

bool PacketContext::isCurrentBackend() const noexcept { return mImpl->currentBackend; }

Result<> PacketContext::sendToClient(ByteSpan packet, bool immediate) {
    return mImpl->session->sendToClient(packet, immediate);
}

Result<> PacketContext::sendToBackend(ByteSpan packet, bool immediate) {
    return mImpl->session->sendToBackend(packet, immediate);
}

Result<> PacketContext::sendToClient(proto::Packet& packet, bool immediate) {
    return mImpl->session->sendToClient(packet, immediate);
}

Result<> PacketContext::sendToBackend(proto::Packet& packet, bool immediate) {
    return mImpl->session->sendToBackend(packet, immediate);
}

void PacketContext::drop() noexcept { mImpl->verdict = Verdict::Drop; }

void PacketContext::defer() noexcept { mImpl->verdict = Verdict::Defer; }

void PacketContext::consume() noexcept { mImpl->verdict = Verdict::Consumed; }

Verdict PacketContext::verdict() const noexcept { return mImpl->verdict; }

struct Pipeline::Impl {
    struct Entry {
        std::uint64_t                      id{};
        Flow                               flow{Flow::ToClient};
        std::optional<proto::PacketId>     packetId{};
        int                                priority{};
        std::shared_ptr<PacketInterceptor> interceptor;
        std::weak_ptr<plugin::Plugin>      owner;
        /// False for host-registered interceptors, which have no plugin to expire
        /// with and must never be dropped by the ownership check.
        bool                               owned{};
    };

    mutable std::recursive_mutex mutex;
    std::vector<Entry>           entries;
    std::uint64_t                nextId{1};
};

Pipeline::Pipeline() : mImpl(std::make_unique<Impl>()) {}

Pipeline::~Pipeline() = default;

InterceptorHandle Pipeline::add(
    Flow                           flow,
    std::optional<proto::PacketId> id,
    int                            priority,
    std::shared_ptr<PacketInterceptor> interceptor,
    std::weak_ptr<plugin::Plugin>  owner
) {
    if (!interceptor) return {};

    std::lock_guard lock{mImpl->mutex};
    const auto handleId = mImpl->nextId++;
    mImpl->entries.push_back({handleId, flow, id, priority, std::move(interceptor), owner, !owner.expired()});
    // Ascending priority, insertion order as the tie-break, so a plugin can
    // reliably run before or after another one.
    std::stable_sort(mImpl->entries.begin(), mImpl->entries.end(), [](auto const& left, auto const& right) {
        return left.priority < right.priority;
    });
    return InterceptorHandle{handleId};
}

bool Pipeline::remove(InterceptorHandle handle) {
    if (!handle) return false;
    std::lock_guard lock{mImpl->mutex};
    const auto removed = std::erase_if(mImpl->entries, [handle](auto const& entry) { return entry.id == handle.id; });
    return removed > 0;
}

std::size_t Pipeline::removeAll(std::weak_ptr<plugin::Plugin> owner) {
    const auto target = owner.lock();
    std::lock_guard lock{mImpl->mutex};
    return std::erase_if(mImpl->entries, [&target](auto const& entry) {
        if (!entry.owned) return false;
        return entry.owner.expired() || (target != nullptr && entry.owner.lock() == target);
    });
}

void Pipeline::clear() noexcept {
    std::lock_guard lock{mImpl->mutex};
    mImpl->entries.clear();
}

std::size_t Pipeline::size() const noexcept {
    std::lock_guard lock{mImpl->mutex};
    return mImpl->entries.size();
}

Verdict Pipeline::dispatch(PacketContext& context) {
    std::vector<std::shared_ptr<PacketInterceptor>> chain;
    {
        std::lock_guard lock{mImpl->mutex};
        chain.reserve(mImpl->entries.size());
        for (auto const& entry : mImpl->entries) {
            if (entry.flow != context.flow()) continue;
            if (entry.packetId.has_value() && *entry.packetId != context.id()) continue;
            if (entry.owned && entry.owner.expired()) continue;
            chain.push_back(entry.interceptor);
        }
    }

    for (auto const& interceptor : chain) {
        const auto verdict = interceptor->onPacket(context);
        if (verdict != Verdict::Forward) return verdict;
    }
    return context.verdict();
}

} // namespace crosslink::net
