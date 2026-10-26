#include "crosslink/api/Gateway.hpp"

#include <chrono>

#ifndef CROSSLINK_VERSION
#define CROSSLINK_VERSION "0.0.0"
#endif

namespace crosslink {

struct Gateway::Impl {
    config::GatewayConfig                 config;
    Logger*                               logger{};
    BuildInfo                             info;
    bool                                  running{};
    std::chrono::steady_clock::time_point startedAt{};
};

Gateway::Gateway() : mImpl(std::make_unique<Impl>()) {
    mImpl->logger = &LoggerRegistry::instance().getOrCreate("CrossLink");
    mImpl->info.crossLinkVersion = CROSSLINK_VERSION;
    mImpl->info.pluginApiVersion = CROSSLINK_PLUGIN_API_VERSION;
#ifdef CROSSLINK_PROTOCOL_VERSION
    mImpl->info.protocolVersion = CROSSLINK_PROTOCOL_VERSION;
#endif
#ifdef CROSSLINK_GAME_VERSION
    mImpl->info.gameVersion = CROSSLINK_GAME_VERSION;
#endif
}

Gateway::~Gateway() = default;

Gateway& Gateway::instance() {
    static Gateway gateway;
    return gateway;
}

config::GatewayConfig const& Gateway::config() const noexcept { return mImpl->config; }

BuildInfo Gateway::buildInfo() const noexcept {
    auto info = mImpl->info;
    if (const auto transport = net::TransportRegistry::instance().active()) info.transport = transport->info().name;
    return info;
}

net::ServerRegistry& Gateway::servers() noexcept { return net::ServerRegistry::instance(); }

net::SessionRegistry& Gateway::sessions() noexcept { return net::SessionRegistry::instance(); }

net::TransportRegistry& Gateway::transports() noexcept { return net::TransportRegistry::instance(); }

control::AgentRegistry& Gateway::agents() noexcept { return control::AgentRegistry::instance(); }

proto::PacketCodecs& Gateway::codecs() noexcept { return proto::PacketCodecs::instance(); }

plugin::PluginManagerRegistry& Gateway::plugins() noexcept { return plugin::PluginManagerRegistry::instance(); }

EventBus& Gateway::events() noexcept { return EventBus::instance(); }

Logger& Gateway::logger() noexcept { return *mImpl->logger; }

bool Gateway::running() const noexcept { return mImpl->running; }

std::chrono::steady_clock::time_point Gateway::startTime() const noexcept { return mImpl->startedAt; }

std::chrono::seconds Gateway::uptime() const noexcept {
    if (!mImpl->running) return std::chrono::seconds{0};
    return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - mImpl->startedAt);
}

void Gateway::configure(config::GatewayConfig config) {
    mImpl->config = std::move(config);
    LoggerRegistry::instance().setLevel(parseLogLevel(mImpl->config.logLevel, LogLevel::Info));
    if (!mImpl->config.logFile.empty()) {
        if (!LoggerRegistry::instance().setLogFile(mImpl->config.logFile)) {
            logger().warn("cannot write the log file '{}', logging to the console only", mImpl->config.logFile);
        }
    }
}

void Gateway::setRunning(bool running) {
    mImpl->running = running;
    mImpl->startedAt = running ? std::chrono::steady_clock::now() : mImpl->startedAt;
}

} // namespace crosslink
