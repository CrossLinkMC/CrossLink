#pragma once

#include "crosslink/api/Export.hpp"
#include "crosslink/api/Result.hpp"
#include "crosslink/api/plugin/NativePlugin.hpp"
#include "crosslink/api/plugin/PluginManager.hpp"

#include <cstdint>
#include <filesystem>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

namespace crosslink {

class Gateway;

namespace plugin {

/// Outcome of one dependency-resolution pass. Rejected plugins are reported with
/// a human readable reason instead of being silently skipped.
struct PluginLoadReport {
    std::vector<std::string>            order;
    std::vector<std::string>            loaded;
    std::map<std::string, std::string>  rejected;

    [[nodiscard]] bool empty() const noexcept { return order.empty(); }
};

/// Global plugin query and lifecycle facade, the counterpart of LeviLamina's
/// ModManagerRegistry. Everything a plugin needs to know about its neighbours
/// goes through here.
class CROSSLINK_API PluginManagerRegistry {
public:
    using CallbackId = std::uint64_t;

    PluginManagerRegistry(PluginManagerRegistry const&)            = delete;
    PluginManagerRegistry& operator=(PluginManagerRegistry const&) = delete;

    [[nodiscard]] static PluginManagerRegistry& instance();

    // ---- managers --------------------------------------------------
    bool                                     addManager(std::shared_ptr<PluginManager> manager);
    bool                                     removeManager(std::string_view type);
    [[nodiscard]] bool                       hasManager(std::string_view type) const;
    [[nodiscard]] std::shared_ptr<PluginManager> getManager(std::string_view type) const;
    [[nodiscard]] std::shared_ptr<PluginManager> getManagerForPlugin(std::string_view name) const;
    [[nodiscard]] std::vector<std::shared_ptr<PluginManager>> managers() const;

    // ---- querying --------------------------------------------------
    [[nodiscard]] std::vector<std::shared_ptr<Plugin>> plugins() const;
    [[nodiscard]] bool                       hasPlugin(std::string_view name) const;
    [[nodiscard]] std::shared_ptr<Plugin>    getPlugin(std::string_view name) const;
    [[nodiscard]] std::string                pluginType(std::string_view name) const;

    template <typename T>
    [[nodiscard]] std::shared_ptr<T> getPluginAs(std::string_view name) const {
        return std::dynamic_pointer_cast<T>(getPlugin(name));
    }

    // ---- lifecycle observers ---------------------------------------
    /// Runs `callback` whenever any plugin reaches `event`. The subscription is
    /// owned by `owner` and disappears with it, so a plugin never has to remember
    /// to unsubscribe. Defaults to the calling plugin.
    CallbackId executeOnPlugin(
        PluginEvent                             event,
        std::function<void(std::string_view)>   callback,
        std::weak_ptr<Plugin>                   owner = NativePlugin::current()
    ) noexcept;
    bool       eraseOnPluginCallback(CallbackId id) noexcept;
    std::size_t eraseOnPluginCallbacks(std::weak_ptr<Plugin> owner) noexcept;

    // ---- orchestration ---------------------------------------------
    void bindGateway(Gateway& gateway) noexcept;

    /// Scans `root` for `*/manifest.json`, resolves dependencies, and loads every
    /// plugin that survived resolution in dependency order.
    [[nodiscard]] Result<PluginLoadReport> loadPluginsFrom(std::filesystem::path const& root);

    /// Loads a single plugin directory at runtime, re-checking its dependencies,
    /// conflicts and platform against what is already loaded.
    [[nodiscard]] Result<> loadPlugin(std::filesystem::path const& pluginDir);

    [[nodiscard]] Result<> enableAll();
    [[nodiscard]] Result<> disableAll();
    [[nodiscard]] Result<> unloadAll();

    [[nodiscard]] Result<> enablePlugin(std::string_view name);
    [[nodiscard]] Result<> disablePlugin(std::string_view name);

    /// Refused while another loaded plugin still depends on this one.
    [[nodiscard]] Result<> unloadPlugin(std::string_view name);

    /// Plugins that declared a dependency on `name`, used to guard unload.
    [[nodiscard]] std::vector<std::string> dependentsOf(std::string_view name) const;

private:
    PluginManagerRegistry();
    ~PluginManagerRegistry();

    struct Impl;
    std::unique_ptr<Impl> mImpl;
};

} // namespace plugin
} // namespace crosslink
