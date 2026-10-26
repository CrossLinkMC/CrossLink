#pragma once

#include "crosslink/api/Config.hpp"
#include "crosslink/api/Events.hpp"
#include "crosslink/api/Export.hpp"
#include "crosslink/api/Logger.hpp"
#include "crosslink/api/control/ControlChannel.hpp"
#include "crosslink/api/net/ServerRegistry.hpp"
#include "crosslink/api/net/Session.hpp"
#include "crosslink/api/net/Transport.hpp"
#include "crosslink/api/plugin/PluginManagerRegistry.hpp"
#include "crosslink/api/proto/Packet.hpp"

#include <chrono>
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>

namespace crosslink {

class Application;

/// Version and protocol facts a plugin can check at run time instead of trusting
/// the headers it was compiled against.
struct BuildInfo {
    std::string_view crossLinkVersion;
    std::uint32_t    pluginApiVersion{};
    std::uint32_t    protocolVersion{};
    std::string_view gameVersion;
    /// Name of the active transport, e.g. "bedrock-raknet".
    std::string      transport;
};

/// The facade handed to plugins: every subsystem the host owns, reachable from
/// one object. Plugins never touch the singletons directly, which keeps the host
/// free to reorder or replace what sits behind them.
class CROSSLINK_API Gateway {
public:
    Gateway(Gateway const&)            = delete;
    Gateway& operator=(Gateway const&) = delete;
    ~Gateway();

    [[nodiscard]] static Gateway& instance();

    [[nodiscard]] config::GatewayConfig const& config() const noexcept;
    [[nodiscard]] BuildInfo                    buildInfo() const noexcept;

    [[nodiscard]] net::ServerRegistry&             servers() noexcept;
    [[nodiscard]] net::SessionRegistry&            sessions() noexcept;
    [[nodiscard]] net::TransportRegistry&          transports() noexcept;
    [[nodiscard]] control::AgentRegistry&          agents() noexcept;
    [[nodiscard]] proto::PacketCodecs&             codecs() noexcept;
    [[nodiscard]] plugin::PluginManagerRegistry&   plugins() noexcept;
    [[nodiscard]] EventBus&                        events() noexcept;
    [[nodiscard]] Logger&                          logger() noexcept;

    [[nodiscard]] bool                            running() const noexcept;
    [[nodiscard]] std::chrono::steady_clock::time_point startTime() const noexcept;
    [[nodiscard]] std::chrono::seconds            uptime() const noexcept;

private:
    friend class Application;
    Gateway();

    void configure(config::GatewayConfig config);
    void setRunning(bool running);

    struct Impl;
    std::unique_ptr<Impl> mImpl;
};

/// Shorthand for `Gateway::instance()`, for plugin code that does not hold a
/// Plugin reference.
[[nodiscard]] inline Gateway& gateway() noexcept { return Gateway::instance(); }

} // namespace crosslink
