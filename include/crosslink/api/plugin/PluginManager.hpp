#pragma once

#include "crosslink/api/Export.hpp"
#include "crosslink/api/Result.hpp"
#include "crosslink/api/plugin/Plugin.hpp"

#include <memory>
#include <string>
#include <string_view>
#include <vector>

namespace crosslink::plugin {

class PluginManagerRegistry;

/// Loads and owns the plugins of one `Manifest::type`. `native` (DLL plugins) is
/// built in; another manager can be registered later for scripted plugins
/// without touching the registry.
class CROSSLINK_API PluginManager {
    friend class PluginManagerRegistry;

public:
    virtual ~PluginManager();

    [[nodiscard]] std::string_view type() const noexcept;
    [[nodiscard]] bool             hasPlugin(std::string_view name) const;
    [[nodiscard]] std::shared_ptr<Plugin> getPlugin(std::string_view name) const;
    [[nodiscard]] std::size_t             count() const;

    /// Snapshot, so callers can iterate while a callback loads or unloads plugins.
    [[nodiscard]] std::vector<std::shared_ptr<Plugin>> plugins() const;

protected:
    explicit PluginManager(std::string type);

    void addPlugin(std::string_view name, std::shared_ptr<Plugin> const& plugin);
    void removePlugin(std::string_view name);

    virtual Result<> load(Manifest manifest)      = 0;
    virtual Result<> unload(std::string_view name) = 0;
    virtual Result<> enable(std::string_view name);
    virtual Result<> disable(std::string_view name);

private:
    struct Impl;
    std::unique_ptr<Impl> mImpl;
};

} // namespace crosslink::plugin
