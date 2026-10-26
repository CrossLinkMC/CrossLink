#pragma once

#include "crosslink/api/plugin/NativePlugin.hpp"
#include "crosslink/api/plugin/PluginManager.hpp"
#include "crosslink/api/Result.hpp"

#include <filesystem>
#include <unordered_map>
#include <vector>

namespace crosslink {

class Gateway;

namespace plugin {

/// Loads DLL plugins: puts the plugin directory on the module search path, loads
/// the entry library, checks the exported API version, resolves the entry points
/// and drives the lifecycle.
class NativePluginManager final : public PluginManager {
public:
    explicit NativePluginManager(Gateway& gateway);
    ~NativePluginManager() override;

    /// Reads `plugins/<name>/manifest.json`.
    [[nodiscard]] static Result<Manifest> readManifest(std::filesystem::path const& pluginDir);

    [[nodiscard]] std::filesystem::path const& pluginsRoot() const noexcept { return mRoot; }
    void setPluginsRoot(std::filesystem::path root) { mRoot = std::move(root); }

    [[nodiscard]] std::vector<std::string> loadOrder() const;

protected:
    Result<> load(Manifest manifest) override;
    Result<> unload(std::string_view name) override;

private:
    Gateway&                             mGateway;
    std::filesystem::path                mRoot;
    std::vector<std::string>             mLoadOrder;
    std::unordered_map<void*, std::weak_ptr<NativePlugin>> mByHandle;
};

} // namespace plugin
} // namespace crosslink
