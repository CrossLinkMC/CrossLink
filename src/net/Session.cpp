#include "crosslink/api/net/Session.hpp"

#include <map>
#include <mutex>
#include <utility>

namespace crosslink::net {

PlayerSession::PlayerSession() = default;
PlayerSession::~PlayerSession() = default;

Result<> PlayerSession::sendToClient(proto::Packet& packet, bool immediate) {
    CROSSLINK_PROPAGATE(packet.encode());
    return sendToClient(ByteSpan{packet.bytes()}, immediate);
}

Result<> PlayerSession::sendToBackend(proto::Packet& packet, bool immediate) {
    CROSSLINK_PROPAGATE(packet.encode());
    return sendToBackend(ByteSpan{packet.bytes()}, immediate);
}

struct SessionRegistry::Impl {
    mutable std::recursive_mutex          mutex;
    std::map<SessionId, PlayerSessionPtr> sessions;
};

SessionRegistry::SessionRegistry() : mImpl(std::make_unique<Impl>()) {}
SessionRegistry::~SessionRegistry() = default;

SessionRegistry& SessionRegistry::instance() {
    static SessionRegistry registry;
    return registry;
}

void SessionRegistry::track(PlayerSessionPtr const& session) {
    if (!session) return;
    std::lock_guard lock{mImpl->mutex};
    mImpl->sessions.insert_or_assign(session->id(), session);
}

void SessionRegistry::untrack(SessionId const& id) {
    std::lock_guard lock{mImpl->mutex};
    mImpl->sessions.erase(id);
}

PlayerSessionPtr SessionRegistry::find(SessionId const& id) const {
    std::lock_guard lock{mImpl->mutex};
    const auto found = mImpl->sessions.find(id);
    return found == mImpl->sessions.end() ? nullptr : found->second;
}

PlayerSessionPtr SessionRegistry::findByIdentity(std::string_view identityKey) const {
    if (identityKey.empty()) return nullptr;
    std::lock_guard lock{mImpl->mutex};
    for (auto const& [id, session] : mImpl->sessions) {
        if (session->identityKey() == identityKey) return session;
    }
    return nullptr;
}

PlayerSessionPtr SessionRegistry::findByName(std::string_view name) const {
    if (name.empty()) return nullptr;
    std::lock_guard lock{mImpl->mutex};
    for (auto const& [id, session] : mImpl->sessions) {
        if (session->identity().name == name) return session;
    }
    return nullptr;
}

std::vector<PlayerSessionPtr> SessionRegistry::all() const {
    std::lock_guard lock{mImpl->mutex};
    std::vector<PlayerSessionPtr> sessions;
    sessions.reserve(mImpl->sessions.size());
    for (auto const& [id, session] : mImpl->sessions) sessions.push_back(session);
    return sessions;
}

std::size_t SessionRegistry::count() const {
    std::lock_guard lock{mImpl->mutex};
    return mImpl->sessions.size();
}

} // namespace crosslink::net
