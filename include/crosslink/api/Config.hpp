#pragma once

#include "crosslink/api/Export.hpp"
#include "crosslink/api/Result.hpp"
#include "crosslink/api/Types.hpp"

#include <nlohmann/json.hpp>

#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

namespace crosslink::config {

using Json = nlohmann::ordered_json;

/// Client-facing listener: the only address players ever connect to.
struct NetworkConfig {
    std::string   listenHost{"0.0.0.0"};
    std::uint16_t listenPort{19132};
    std::uint32_t maxConnections{1024};
    std::string   motd{"CrossLink gateway"};
    std::size_t   maxPacketBytes{8u * 1024u * 1024u};
    std::size_t   maxPacketsPerSecond{1024};
    /// 0 lets the transport pick hardware_concurrency.
    std::uint32_t workerThreads{0};
    std::size_t   flushReadyPerTick{512};
    /// Deferred packet queues are bounded so a stuck handoff cannot grow forever.
    std::size_t   maxDeferredPackets{4096};
};

/// Control plane the backend agents connect to. Never expose this publicly.
struct ControlConfig {
    std::string   listenHost{"127.0.0.1"};
    std::uint16_t listenPort{31920};
    /// Shared secret an agent presents in its hello. At least 32 characters.
    std::string   token;
    std::uint32_t heartbeatSeconds{15};
    std::uint32_t requestTimeoutSeconds{10};
    std::uint32_t handshakeTimeoutSeconds{10};
    std::size_t   maxLineBytes{1u * 1024u * 1024u};
};

struct ServerEntry {
    std::string   id;
    std::string   gameHost{"127.0.0.1"};
    std::uint16_t gamePort{19133};
    /// Where the agent inside this server is expected to come from. Informational:
    /// agents dial the gateway, they are matched by the serverId they report.
    std::string   agentHost{"127.0.0.1"};
    std::uint16_t agentPort{0};
};

struct GatewayConfig {
    /// Bumped when the on-disk shape changes, so an old file can be migrated
    /// instead of being silently misread.
    int version{1};

    NetworkConfig           network;
    ControlConfig           control;
    /// The lobby: the hub every sub server is reachable from.
    std::string             lobby;
    /// Where a fresh client lands. Defaults to the lobby.
    std::string             entryServer;
    std::vector<ServerEntry> servers;

    std::string pluginDir{"plugins"};
    std::string logLevel{"info"};
    std::string logFile;
    /// Transport implementation to use; see net::TransportRegistry.
    std::string transport{"bedrock-raknet"};

    [[nodiscard]] Result<>                      validate() const;
    [[nodiscard]] std::string                   entryServerOrLobby() const;
    [[nodiscard]] const ServerEntry*            findServer(std::string_view id) const;
};

[[nodiscard]] CROSSLINK_API GatewayConfig    defaultConfig();
[[nodiscard]] CROSSLINK_API Result<GatewayConfig> fromJson(Json const& json);
[[nodiscard]] CROSSLINK_API Json             toJson(GatewayConfig const& config);
/// Reads the file, or writes a commented default when it does not exist yet.
[[nodiscard]] CROSSLINK_API Result<GatewayConfig> loadFile(std::filesystem::path const& path);
[[nodiscard]] CROSSLINK_API Result<>              saveFile(GatewayConfig const& config, std::filesystem::path const& path);

} // namespace crosslink::config
