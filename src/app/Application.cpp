#include "app/Application.hpp"

#include "crosslink/api/plugin/PluginManagerRegistry.hpp"
#include "net/bedrock/BedrockTransport.hpp"
#include "proto/BuiltinCodecs.hpp"

#include <format>

namespace crosslink {

Application::Application() = default;

Application::~Application() { stop(); }

bool Application::running() const noexcept { return Gateway::instance().running(); }

Result<> Application::registerServers() {
    auto& registry = gateway().servers();
    auto const& config = gateway().config();

    for (auto const& entry : config.servers) {
        ServerInfo info;
        info.id = ServerId{entry.id};
        info.gameEndpoint = Endpoint{entry.gameHost, entry.gamePort};
        info.agentEndpoint = Endpoint{entry.agentHost, entry.agentPort};
        info.isLobby = entry.id == config.lobby;
        if (auto added = registry.add(std::move(info)); !added) return added;
    }
    if (auto lobby = registry.setLobby(ServerId{config.lobby}); !lobby) return lobby;
    if (!config.entryServer.empty()) {
        if (auto entry = registry.setEntryServer(ServerId{config.entryServer}); !entry) return entry;
    }

    gateway().logger().info(
        "{} backend server(s) registered, lobby '{}', entry '{}'",
        registry.count(),
        registry.lobbyId().str(),
        registry.entryServerId().str()
    );
    return {};
}

Result<> Application::registerTransports() {
    auto& transports = gateway().transports();
    auto const& config = gateway().config();

#ifdef CROSSLINK_PROTOCOL_VERSION
    constexpr std::uint32_t protocolVersion = CROSSLINK_PROTOCOL_VERSION;
#else
    constexpr std::uint32_t protocolVersion = 0;
#endif
#ifdef CROSSLINK_GAME_VERSION
    const std::string gameVersion = CROSSLINK_GAME_VERSION;
#else
    const std::string gameVersion = "unknown";
#endif

    // Additional transports (nethernet, ...) register themselves here or from a
    // plugin; the configuration picks which one serves traffic.
    transports.registerTransport(
        "bedrock-raknet",
        std::make_shared<net::bedrock::BedrockTransport>(protocolVersion, gameVersion)
    );

    if (!transports.setActive(config.transport)) {
        return std::unexpected(Error{std::format(
            "transport '{}' is not registered; available: {}",
            config.transport,
            [&] {
                std::string names;
                for (auto const& name : transports.names()) {
                    if (!names.empty()) names += ", ";
                    names += name;
                }
                return names;
            }()
        )});
    }

    const auto info = transports.active()->info();
    gateway().logger().info(
        "transport '{}' active (protocol {}, game {}, termination {})",
        info.name,
        info.protocolVersion,
        info.gameVersion,
        info.supportsTermination ? "yes" : "no"
    );
    if (!info.supportsTermination) {
        gateway().logger().warn(
            "transport '{}' cannot terminate sessions, so a backend switch will reconnect players instead of being seamless",
            info.name
        );
    }
    return {};
}

Result<> Application::initialize(std::filesystem::path const& configPath) {
    auto config = config::loadFile(configPath);
    if (!config) return std::unexpected(config.error());

    gateway().configure(*config);
    gateway().logger().info("CrossLink {} starting with '{}'", gateway().buildInfo().crossLinkVersion, configPath.string());

    proto::registerBuiltinCodecs();

    if (auto servers = registerServers(); !servers) return servers;
    if (auto transports = registerTransports(); !transports) return transports;

    gateway().plugins().bindGateway(gateway());

    mControl = std::make_unique<control::ControlServer>(gateway());
    mRouter = std::make_unique<net::SessionRouter>(gateway());
    mInitialized = true;
    return {};
}

Result<> Application::start() {
    if (!mInitialized) return std::unexpected(Error{"the application was not initialized"});

    if (auto started = mControl->start(gateway().config().control); !started) return started;

    const auto pluginRoot = std::filesystem::path{gateway().config().pluginDir};
    const auto report = gateway().plugins().loadPluginsFrom(pluginRoot);
    if (!report) return std::unexpected(report.error());
    if (auto enabled = gateway().plugins().enableAll(); !enabled) {
        gateway().logger().error("plugin activation failed: {}", enabled.error().message);
    }
    if (report->loaded.empty()) {
        gateway().logger().warn(
            "no plugin is active: the gateway will forward packets between the lobby and sub servers, "
            "but nothing implements a cross-server transfer"
        );
    }

    if (auto listening = mRouter->start(); !listening) return listening;

    gateway().setRunning(true);
    return {};
}

void Application::stop() noexcept {
    if (!mInitialized) return;
    gateway().setRunning(false);

    if (mRouter) mRouter->stop();
    if (auto unloaded = gateway().plugins().unloadAll(); !unloaded) {
        gateway().logger().error("plugin shutdown reported: {}", unloaded.error().message);
    }
    if (mControl) mControl->stop();

    gateway().logger().info("CrossLink stopped");
}

} // namespace crosslink
