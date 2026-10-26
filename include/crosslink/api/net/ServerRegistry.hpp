#pragma once

#include "crosslink/api/Export.hpp"
#include "crosslink/api/Result.hpp"
#include "crosslink/api/Types.hpp"

#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace crosslink::net {

/// Topology bookkeeping for the one-lobby-plus-N-sub-servers layout.
///
/// This is deliberately pure topology. The registry knows which servers exist
/// and which one is the lobby; deciding *when* a player moves is business logic
/// and belongs to a plugin.
class CROSSLINK_API ServerRegistry {
public:
    [[nodiscard]] static ServerRegistry& instance();

    [[nodiscard]] Result<> add(ServerInfo server);
    bool                   remove(ServerId const& id);
    [[nodiscard]] std::optional<ServerInfo> find(ServerId const& id) const;
    [[nodiscard]] bool                      has(ServerId const& id) const;
    [[nodiscard]] std::vector<ServerInfo>   all() const;
    [[nodiscard]] std::size_t               count() const;

    /// Exactly one server is the lobby: the one clients land on and the hub every
    /// sub server is reachable from.
    [[nodiscard]] Result<>            setLobby(ServerId const& id);
    [[nodiscard]] ServerId            lobbyId() const;
    [[nodiscard]] std::optional<ServerInfo> lobby() const;
    [[nodiscard]] std::vector<ServerInfo>   subServers() const;
    [[nodiscard]] bool                      isLobby(ServerId const& id) const;

    /// Where a brand new client is routed. Defaults to the lobby.
    [[nodiscard]] Result<> setEntryServer(ServerId const& id);
    [[nodiscard]] ServerId entryServerId() const;

private:
    ServerRegistry();
    ~ServerRegistry();

    struct Impl;
    std::unique_ptr<Impl> mImpl;
};

} // namespace crosslink::net
