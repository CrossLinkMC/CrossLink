#include "crosslink/api/plugin/Plugin.hpp"

#include "crosslink/api/Gateway.hpp"

#include <exception>
#include <format>
#include <system_error>

namespace crosslink::plugin {
namespace {

std::size_t slot(PluginEvent event) noexcept { return static_cast<std::size_t>(event); }

std::filesystem::path ensureDirectory(std::filesystem::path const& parent, std::string_view name) {
    auto path = parent / name;
    std::error_code ignored;
    std::filesystem::create_directories(path, ignored);
    return path;
}

} // namespace

std::string_view pluginStateName(PluginState state) noexcept {
    switch (state) {
    case PluginState::Unloaded: return "unloaded";
    case PluginState::Loaded:   return "loaded";
    case PluginState::Enabled:  return "enabled";
    case PluginState::Disabled: return "disabled";
    case PluginState::Failed:   return "failed";
    }
    return "unknown";
}

Plugin::Plugin(Manifest manifest, std::filesystem::path pluginDir)
: mManifest(std::move(manifest)), mDir(std::move(pluginDir)) {
    mLogger = &LoggerRegistry::instance().getOrCreate(mManifest.name);
}

Plugin::~Plugin() = default;

std::filesystem::path Plugin::configDir() const { return ensureDirectory(mDir, "config"); }

std::filesystem::path Plugin::dataDir() const { return ensureDirectory(mDir, "data"); }

void Plugin::setLifecycle(PluginEvent event, LifecycleCallback callback) { mCallbacks[slot(event)] = std::move(callback); }

void Plugin::clearLifecycle() noexcept {
    for (auto& callback : mCallbacks) callback = nullptr;
}

bool Plugin::hasLifecycle(PluginEvent event) const noexcept { return static_cast<bool>(mCallbacks[slot(event)]); }

void Plugin::bindGateway(Gateway& gateway) noexcept { mGateway = &gateway; }

Gateway& Plugin::gateway() const noexcept { return mGateway != nullptr ? *mGateway : Gateway::instance(); }

Result<> Plugin::invoke(PluginEvent event, std::string_view what) {
    auto const& callback = mCallbacks[slot(event)];
    if (!callback) {
        return std::unexpected(Error{std::format("plugin '{}' registered no {} entry point", mManifest.name, what)});
    }
    try {
        if (!callback(*this)) {
            return std::unexpected(Error{std::format("plugin '{}' refused to {}", mManifest.name, what)});
        }
    } catch (std::exception const& exception) {
        return std::unexpected(
            Error{std::format("plugin '{}' threw while trying to {}: {}", mManifest.name, what, exception.what())}
        );
    } catch (...) {
        return std::unexpected(Error{std::format("plugin '{}' threw an unknown exception while trying to {}", mManifest.name, what)});
    }
    return {};
}

Result<> Plugin::load() {
    if (mState == PluginState::Loaded || mState == PluginState::Enabled) return {};
    auto result = invoke(PluginEvent::Load, "load");
    if (!result) {
        mState = PluginState::Failed;
        return result;
    }
    mState = PluginState::Loaded;
    mLogger->info("loaded {}", mManifest.versionString());
    return {};
}

Result<> Plugin::enable() {
    if (mState == PluginState::Enabled) return {};
    if (mState != PluginState::Loaded && mState != PluginState::Disabled) {
        return std::unexpected(Error{std::format("plugin '{}' is {} and cannot be enabled", mManifest.name, pluginStateName(mState))});
    }
    if (hasLifecycle(PluginEvent::Enable)) {
        auto result = invoke(PluginEvent::Enable, "enable");
        if (!result) return result;
    }
    mState = PluginState::Enabled;
    mLogger->debug("enabled");
    return {};
}

Result<> Plugin::disable() {
    if (mState != PluginState::Enabled) return {};
    if (hasLifecycle(PluginEvent::Disable)) {
        auto result = invoke(PluginEvent::Disable, "disable");
        if (!result) return result;
    }
    mState = PluginState::Disabled;
    mLogger->debug("disabled");
    return {};
}

Result<> Plugin::unload() {
    if (mState == PluginState::Unloaded) return {};
    if (auto result = disable(); !result) return result;

    // Unloading is the one transition a plugin must opt into: without it the host
    // cannot safely FreeLibrary, because static state would still be referenced.
    auto result = invoke(PluginEvent::Unload, "unload");
    if (!result) return result;

    clearLifecycle();
    mState = PluginState::Unloaded;
    LoggerRegistry::instance().getOrCreate(mManifest.name).info("unloaded");
    return {};
}

} // namespace crosslink::plugin
