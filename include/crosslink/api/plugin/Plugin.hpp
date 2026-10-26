#pragma once

#include "crosslink/api/Export.hpp"
#include "crosslink/api/Logger.hpp"
#include "crosslink/api/Result.hpp"
#include "crosslink/api/plugin/Manifest.hpp"

#include <cstdint>
#include <filesystem>
#include <functional>
#include <string>
#include <string_view>

namespace crosslink {

class Gateway;

namespace plugin {

enum class PluginState : std::uint8_t {
    Unloaded = 0,
    Loaded   = 1,
    Enabled  = 2,
    Disabled = 3,
    Failed   = 4,
};

[[nodiscard]] CROSSLINK_API std::string_view pluginStateName(PluginState state) noexcept;

enum class PluginEvent : std::uint8_t {
    Load    = 0,
    Unload  = 1,
    Enable  = 2,
    Disable = 3,
};

class Plugin;

/// A lifecycle callback returns false to refuse the transition; the host then
/// leaves the plugin in its previous state and reports the failure.
using LifecycleCallback = std::function<bool(Plugin&)>;

/// One loaded plugin: its manifest, its directories, its logger, and the four
/// lifecycle slots the loader fills in from the plugin's exported entry points.
///
/// The shape follows LeviLamina's mod object so that a mod author recognises it
/// immediately, but nothing here depends on BDS.
class CROSSLINK_API Plugin {
public:
    Plugin(Manifest manifest, std::filesystem::path pluginDir);
    virtual ~Plugin();

    Plugin(Plugin const&)            = delete;
    Plugin& operator=(Plugin const&) = delete;

    [[nodiscard]] Manifest const&              manifest() const noexcept { return mManifest; }
    [[nodiscard]] std::string_view             name() const noexcept { return mManifest.name; }
    [[nodiscard]] std::string_view             type() const noexcept { return mManifest.type; }
    [[nodiscard]] PluginState                  state() const noexcept { return mState; }
    [[nodiscard]] bool                         isEnabled() const noexcept { return mState == PluginState::Enabled; }
    [[nodiscard]] std::filesystem::path const& dir() const noexcept { return mDir; }

    /// `plugins/<name>/config` and `plugins/<name>/data`, created on demand.
    [[nodiscard]] std::filesystem::path configDir() const;
    [[nodiscard]] std::filesystem::path dataDir() const;

    [[nodiscard]] Logger&  logger() const noexcept { return *mLogger; }
    [[nodiscard]] Gateway& gateway() const noexcept;

    // ---- host side -------------------------------------------------
    void setLifecycle(PluginEvent event, LifecycleCallback callback);
    void clearLifecycle() noexcept;
    [[nodiscard]] bool hasLifecycle(PluginEvent event) const noexcept;
    void             bindGateway(Gateway& gateway) noexcept;

    // ---- transitions, driven by the manager ------------------------
    [[nodiscard]] Result<> load();
    [[nodiscard]] Result<> enable();
    [[nodiscard]] Result<> disable();
    [[nodiscard]] Result<> unload();

protected:
    void setState(PluginState state) noexcept { mState = state; }

private:
    [[nodiscard]] Result<> invoke(PluginEvent event, std::string_view what);

    Manifest                mManifest;
    std::filesystem::path   mDir;
    Logger*                 mLogger{};
    Gateway*                mGateway{};
    PluginState             mState{PluginState::Unloaded};
    LifecycleCallback       mCallbacks[4];
};

} // namespace plugin
} // namespace crosslink
