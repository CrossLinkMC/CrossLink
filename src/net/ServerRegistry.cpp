#include "crosslink/api/net/ServerRegistry.hpp"

#include <format>
#include <map>
#include <mutex>
#include <utility>

namespace crosslink::net {

struct ServerRegistry::Impl {
    mutable std::recursive_mutex       mutex;
    std::map<std::string, ServerInfo> servers;
    std::string                        lobby;
    std::string                        entry;
};

ServerRegistry::ServerRegistry() : mImpl(std::make_unique<Impl>()) {}
ServerRegistry::~ServerRegistry() = default;

ServerRegistry& ServerRegistry::instance() {
    static ServerRegistry registry;
    return registry;
}

Result<> ServerRegistry::add(ServerInfo server) {
    if (server.id.empty()) return std::unexpected(Error{"a server needs a non-empty id"});

    std::lock_guard lock{mImpl->mutex};
    const auto key = server.id.str();
    if (mImpl->servers.contains(key)) return std::unexpected(Error{std::format("server '{}' is already registered", key)});

    if (server.isLobby && !mImpl->lobby.empty() && mImpl->lobby != key) {
        return std::unexpected(Error{std::format("lobby is already '{}', cannot also be '{}'", mImpl->lobby, key)});
    }
    if (server.isLobby) mImpl->lobby = key;
    // The first server becomes the lobby when the configuration did not name one.
    if (mImpl->lobby.empty() && mImpl->servers.empty()) mImpl->lobby = key;
    if (mImpl->lobby == key) server.isLobby = true;

    mImpl->servers.emplace(key, std::move(server));
    if (mImpl->entry.empty()) mImpl->entry = mImpl->lobby;
    return {};
}

bool ServerRegistry::remove(ServerId const& id) {
    std::lock_guard lock{mImpl->mutex};
    const auto key = id.str();
    if (mImpl->servers.erase(key) == 0) return false;
    if (mImpl->lobby == key) mImpl->lobby.clear();
    if (mImpl->entry == key) mImpl->entry = mImpl->lobby;
    return true;
}

std::optional<ServerInfo> ServerRegistry::find(ServerId const& id) const {
    std::lock_guard lock{mImpl->mutex};
    const auto found = mImpl->servers.find(id.str());
    if (found == mImpl->servers.end()) return std::nullopt;
    return found->second;
}

bool ServerRegistry::has(ServerId const& id) const { return find(id).has_value(); }

std::vector<ServerInfo> ServerRegistry::all() const {
    std::lock_guard lock{mImpl->mutex};
    std::vector<ServerInfo> servers;
    servers.reserve(mImpl->servers.size());
    for (auto const& [id, server] : mImpl->servers) servers.push_back(server);
    return servers;
}

std::size_t ServerRegistry::count() const {
    std::lock_guard lock{mImpl->mutex};
    return mImpl->servers.size();
}

Result<> ServerRegistry::setLobby(ServerId const& id) {
    std::lock_guard lock{mImpl->mutex};
    const auto found = mImpl->servers.find(id.str());
    if (found == mImpl->servers.end()) return std::unexpected(Error{std::format("unknown server '{}'", id.str())});

    for (auto& [key, server] : mImpl->servers) server.isLobby = (key == id.str());
    mImpl->lobby = id.str();
    if (mImpl->entry.empty()) mImpl->entry = mImpl->lobby;
    return {};
}

ServerId ServerRegistry::lobbyId() const {
    std::lock_guard lock{mImpl->mutex};
    return ServerId{mImpl->lobby};
}

std::optional<ServerInfo> ServerRegistry::lobby() const { return find(lobbyId()); }

std::vector<ServerInfo> ServerRegistry::subServers() const {
    std::lock_guard lock{mImpl->mutex};
    std::vector<ServerInfo> subs;
    for (auto const& [id, server] : mImpl->servers) {
        if (id != mImpl->lobby) subs.push_back(server);
    }
    return subs;
}

bool ServerRegistry::isLobby(ServerId const& id) const {
    std::lock_guard lock{mImpl->mutex};
    return id.str() == mImpl->lobby;
}

Result<> ServerRegistry::setEntryServer(ServerId const& id) {
    std::lock_guard lock{mImpl->mutex};
    if (!mImpl->servers.contains(id.str())) return std::unexpected(Error{std::format("unknown server '{}'", id.str())});
    mImpl->entry = id.str();
    return {};
}

ServerId ServerRegistry::entryServerId() const {
    std::lock_guard lock{mImpl->mutex};
    return ServerId{mImpl->entry.empty() ? mImpl->lobby : mImpl->entry};
}

} // namespace crosslink::net
