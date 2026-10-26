#pragma once

#include "crosslink/api/Export.hpp"
#include "crosslink/api/plugin/Plugin.hpp"

#include <memory>

namespace crosslink::plugin {

class NativePluginManager;

namespace detail {

/// Address of a static that always lives in the module of the translation unit
/// instantiating it, which is how a plugin identifies itself to the host without
/// passing a handle around. Each DLL gets its own copy of the anchor.
[[nodiscard]] inline void* moduleAnchor() noexcept {
    static int anchor = 0;
    return &anchor;
}

} // namespace detail

/// A plugin backed by a dynamically loaded library.
///
/// The host resolves four optional C entry points in the module
/// (`cl_plugin_load`, `cl_plugin_enable`, `cl_plugin_disable`,
/// `cl_plugin_unload`, all `bool(Plugin&)`) plus the mandatory
/// `cl_plugin_api_version`, and refuses the module when the API version differs
/// from CROSSLINK_PLUGIN_API_VERSION.
class CROSSLINK_API NativePlugin : public Plugin {
    friend class NativePluginManager;

public:
    NativePlugin(Manifest manifest, std::filesystem::path pluginDir);
    ~NativePlugin() override;

    /// Opaque module handle (HMODULE on Windows, void* from dlopen elsewhere).
    [[nodiscard]] void* handle() const noexcept { return mHandle; }

    /// The plugin whose code is calling, resolved from the calling module.
    [[nodiscard]] static std::shared_ptr<NativePlugin> current(void* callerAddress = detail::moduleAnchor());

    [[nodiscard]] static std::shared_ptr<NativePlugin> byHandle(void* handle);

protected:
    void setHandle(void* handle) noexcept { mHandle = handle; }

private:
    void* mHandle{};
};

} // namespace crosslink::plugin
