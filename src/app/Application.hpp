#pragma once

#include "control/ControlServer.hpp"
#include "crosslink/api/Export.hpp"
#include "crosslink/api/Gateway.hpp"
#include "net/GatewaySession.hpp"

#include <filesystem>
#include <memory>

namespace crosslink {

/// Owns the subsystems and their lifetime.
///
/// Start-up order matters: the control plane comes up first so backend agents can
/// attach, then plugins load and enable (they install the interceptors that give
/// a handoff its behaviour), and only then does the client listener start
/// accepting players. Shut-down is the exact reverse.
class CROSSLINK_API Application {
public:
    Application();
    ~Application();

    Application(Application const&)            = delete;
    Application& operator=(Application const&) = delete;

    [[nodiscard]] Result<> initialize(std::filesystem::path const& configPath);
    [[nodiscard]] Result<> start();
    void                   stop() noexcept;

    [[nodiscard]] Gateway& gateway() noexcept { return Gateway::instance(); }
    [[nodiscard]] bool     running() const noexcept;

private:
    [[nodiscard]] Result<> registerServers();
    [[nodiscard]] Result<> registerTransports();

    bool                                  mInitialized{};
    std::unique_ptr<control::ControlServer> mControl;
    std::unique_ptr<net::SessionRouter>   mRouter;
};

} // namespace crosslink
