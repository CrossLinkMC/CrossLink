#include "crosslink/api/Config.hpp"

#include <format>
#include <fstream>
#include <set>
#include <sstream>
#include <type_traits>

namespace crosslink::config {
namespace {

template <typename T>
T read(Json const& json, std::string_view key, T fallback) {
    const auto found = json.find(key);
    if (found == json.end() || found->is_null()) return fallback;
    if constexpr (std::is_same_v<T, std::string>) {
        return found->is_string() ? found->get<std::string>() : fallback;
    } else if constexpr (std::is_same_v<T, bool>) {
        return found->is_boolean() ? found->get<bool>() : fallback;
    } else {
        return found->is_number() ? static_cast<T>(found->get<std::int64_t>()) : fallback;
    }
}

Json const& section(Json const& json, std::string_view key, Json& scratch) {
    const auto found = json.find(key);
    if (found == json.end() || !found->is_object()) {
        scratch = Json::object();
        return scratch;
    }
    return *found;
}

NetworkConfig readNetwork(Json const& json) {
    Json scratch;
    auto const& network = section(json, "network", scratch);
    NetworkConfig config;
    config.listenHost = read<std::string>(network, "listenHost", config.listenHost);
    config.listenPort = read<std::uint16_t>(network, "listenPort", config.listenPort);
    config.maxConnections = read<std::uint32_t>(network, "maxConnections", config.maxConnections);
    config.motd = read<std::string>(network, "motd", config.motd);
    config.maxPacketBytes = read<std::size_t>(network, "maxPacketBytes", config.maxPacketBytes);
    config.maxPacketsPerSecond = read<std::size_t>(network, "maxPacketsPerSecond", config.maxPacketsPerSecond);
    config.workerThreads = read<std::uint32_t>(network, "workerThreads", config.workerThreads);
    config.flushReadyPerTick = read<std::size_t>(network, "flushReadyPerTick", config.flushReadyPerTick);
    config.maxDeferredPackets = read<std::size_t>(network, "maxDeferredPackets", config.maxDeferredPackets);
    return config;
}

ControlConfig readControl(Json const& json) {
    Json scratch;
    auto const& control = section(json, "control", scratch);
    ControlConfig config;
    config.listenHost = read<std::string>(control, "listenHost", config.listenHost);
    config.listenPort = read<std::uint16_t>(control, "listenPort", config.listenPort);
    config.token = read<std::string>(control, "token", config.token);
    config.heartbeatSeconds = read<std::uint32_t>(control, "heartbeatSeconds", config.heartbeatSeconds);
    config.requestTimeoutSeconds = read<std::uint32_t>(control, "requestTimeoutSeconds", config.requestTimeoutSeconds);
    config.handshakeTimeoutSeconds = read<std::uint32_t>(control, "handshakeTimeoutSeconds", config.handshakeTimeoutSeconds);
    config.maxLineBytes = read<std::size_t>(control, "maxLineBytes", config.maxLineBytes);
    return config;
}

} // namespace

GatewayConfig defaultConfig() {
    GatewayConfig config;
    config.servers.push_back(ServerEntry{.id = "lobby", .gameHost = "127.0.0.1", .gamePort = 19133});
    config.servers.push_back(ServerEntry{.id = "survival", .gameHost = "127.0.0.1", .gamePort = 19134});
    config.lobby = "lobby";
    config.entryServer = "lobby";
    return config;
}

const ServerEntry* GatewayConfig::findServer(std::string_view id) const {
    for (auto const& server : servers) {
        if (server.id == id) return &server;
    }
    return nullptr;
}

std::string GatewayConfig::entryServerOrLobby() const { return entryServer.empty() ? lobby : entryServer; }

Result<> GatewayConfig::validate() const {
    if (network.listenPort == 0) return std::unexpected(Error{"network.listenPort must not be 0"});
    if (network.maxConnections == 0) return std::unexpected(Error{"network.maxConnections must be at least 1"});
    if (servers.empty()) return std::unexpected(Error{"at least one server must be configured"});

    std::set<std::string> ids;
    for (auto const& server : servers) {
        if (server.id.empty()) return std::unexpected(Error{"every server needs an id"});
        if (!ids.insert(server.id).second) return std::unexpected(Error{std::format("server id '{}' is duplicated", server.id)});
        if (server.gamePort == 0) {
            return std::unexpected(Error{std::format("server '{}' needs a non-zero gamePort", server.id)});
        }
        if (server.gameHost.empty()) {
            return std::unexpected(Error{std::format("server '{}' needs a gameHost", server.id)});
        }
    }

    if (lobby.empty()) return std::unexpected(Error{"lobby must name one of the configured servers"});
    if (findServer(lobby) == nullptr) return std::unexpected(Error{std::format("lobby '{}' is not in the server list", lobby)});
    if (!entryServer.empty() && findServer(entryServer) == nullptr) {
        return std::unexpected(Error{std::format("entryServer '{}' is not in the server list", entryServer)});
    }

    if (control.listenPort == 0) return std::unexpected(Error{"control.listenPort must not be 0"});
    if (control.token.size() < 32) {
        return std::unexpected(Error{"control.token must be at least 32 characters; generate one with `openssl rand -hex 24`"});
    }
    if (pluginDir.empty()) return std::unexpected(Error{"pluginDir must not be empty"});
    if (transport.empty()) return std::unexpected(Error{"transport must not be empty"});

    return {};
}

Result<GatewayConfig> fromJson(Json const& json) {
    if (!json.is_object()) return std::unexpected(Error{"the configuration must be a JSON object"});

    GatewayConfig config;
    config.version = read<int>(json, "version", config.version);
    config.network = readNetwork(json);
    config.control = readControl(json);
    config.lobby = read<std::string>(json, "lobby", config.lobby);
    config.entryServer = read<std::string>(json, "entryServer", config.entryServer);
    config.pluginDir = read<std::string>(json, "pluginDir", config.pluginDir);
    config.logLevel = read<std::string>(json, "logLevel", config.logLevel);
    config.logFile = read<std::string>(json, "logFile", config.logFile);
    config.transport = read<std::string>(json, "transport", config.transport);

    if (const auto found = json.find("servers"); found != json.end() && found->is_array()) {
        for (auto const& entry : *found) {
            if (!entry.is_object()) return std::unexpected(Error{"every entry of 'servers' must be an object"});
            ServerEntry server;
            server.id = read<std::string>(entry, "id", server.id);
            server.gameHost = read<std::string>(entry, "gameHost", server.gameHost);
            server.gamePort = read<std::uint16_t>(entry, "gamePort", server.gamePort);
            server.agentHost = read<std::string>(entry, "agentHost", server.agentHost);
            server.agentPort = read<std::uint16_t>(entry, "agentPort", server.agentPort);
            config.servers.push_back(std::move(server));
        }
    }

    if (config.version != 1) {
        return std::unexpected(Error{std::format("configuration version {} is not supported, this build reads version 1", config.version)});
    }
    return config;
}

Json toJson(GatewayConfig const& config) {
    auto json = Json::object();
    json["version"] = config.version;

    auto network = Json::object();
    network["listenHost"] = config.network.listenHost;
    network["listenPort"] = config.network.listenPort;
    network["maxConnections"] = config.network.maxConnections;
    network["motd"] = config.network.motd;
    network["maxPacketBytes"] = config.network.maxPacketBytes;
    network["maxPacketsPerSecond"] = config.network.maxPacketsPerSecond;
    network["workerThreads"] = config.network.workerThreads;
    network["flushReadyPerTick"] = config.network.flushReadyPerTick;
    network["maxDeferredPackets"] = config.network.maxDeferredPackets;
    json["network"] = std::move(network);

    auto control = Json::object();
    control["listenHost"] = config.control.listenHost;
    control["listenPort"] = config.control.listenPort;
    control["token"] = config.control.token;
    control["heartbeatSeconds"] = config.control.heartbeatSeconds;
    control["requestTimeoutSeconds"] = config.control.requestTimeoutSeconds;
    control["handshakeTimeoutSeconds"] = config.control.handshakeTimeoutSeconds;
    control["maxLineBytes"] = config.control.maxLineBytes;
    json["control"] = std::move(control);

    json["lobby"] = config.lobby;
    json["entryServer"] = config.entryServer;

    auto servers = Json::array();
    for (auto const& server : config.servers) {
        auto entry = Json::object();
        entry["id"] = server.id;
        entry["gameHost"] = server.gameHost;
        entry["gamePort"] = server.gamePort;
        entry["agentHost"] = server.agentHost;
        entry["agentPort"] = server.agentPort;
        servers.push_back(std::move(entry));
    }
    json["servers"] = std::move(servers);

    json["pluginDir"] = config.pluginDir;
    json["logLevel"] = config.logLevel;
    json["logFile"] = config.logFile;
    json["transport"] = config.transport;
    return json;
}

Result<GatewayConfig> loadFile(std::filesystem::path const& path) {
    std::error_code ignored;
    if (!std::filesystem::exists(path, ignored)) {
        auto config = defaultConfig();
        if (auto saved = saveFile(config, path); !saved) return std::unexpected(saved.error());
        return config;
    }

    std::ifstream input{path};
    if (!input) return std::unexpected(Error{std::format("cannot open '{}'", path.string())});
    std::stringstream buffer;
    buffer << input.rdbuf();

    const auto json = Json::parse(buffer.str(), nullptr, false, true);
    if (json.is_discarded()) return std::unexpected(Error{std::format("'{}' is not valid JSON", path.string())});

    auto config = fromJson(json);
    if (!config) return config;
    if (auto validated = config->validate(); !validated) return std::unexpected(validated.error());
    return config;
}

Result<> saveFile(GatewayConfig const& config, std::filesystem::path const& path) {
    if (path.has_parent_path()) {
        std::error_code ignored;
        std::filesystem::create_directories(path.parent_path(), ignored);
    }
    std::ofstream output{path};
    if (!output) return std::unexpected(Error{std::format("cannot write '{}'", path.string())});
    output << toJson(config).dump(4) << '\n';
    return {};
}

} // namespace crosslink::config
