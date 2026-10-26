#pragma once

#include "crosslink/api/Export.hpp"
#include "crosslink/api/plugin/NativePlugin.hpp"

namespace crosslink::plugin {

// A plugin class only has to provide `load()`; the other three are optional and
// are bound as lifecycle callbacks when they exist.
template <typename T>
concept Loadable = requires(T& t) {
    { t.load() } -> std::same_as<bool>;
};

template <typename T>
concept Unloadable = requires(T& t) {
    { t.unload() } -> std::same_as<bool>;
};

template <typename T>
concept Enableable = requires(T& t) {
    { t.enable() } -> std::same_as<bool>;
};

template <typename T>
concept Disableable = requires(T& t) {
    { t.disable() } -> std::same_as<bool>;
};

/// Wires the optional transitions of a plugin object into the host's Plugin.
template <Loadable T>
inline void bindToPlugin(T& plugin, Plugin& self) {
    if constexpr (Enableable<T>) {
        self.setLifecycle(PluginEvent::Enable, [&plugin](Plugin&) { return plugin.enable(); });
    }
    if constexpr (Disableable<T>) {
        self.setLifecycle(PluginEvent::Disable, [&plugin](Plugin&) { return plugin.disable(); });
    }
    if constexpr (Unloadable<T>) {
        self.setLifecycle(PluginEvent::Unload, [&plugin](Plugin&) { return plugin.unload(); });
    }
}

} // namespace crosslink::plugin

/// Declares the exported C entry points of a CrossLink plugin DLL.
///
/// Only two symbols are exported: `cl_plugin_api_version`, which the host checks
/// before touching anything else, and `cl_plugin_load`, which binds the optional
/// enable/disable/unload transitions and then runs the plugin's own `load()`.
///
///     CL_REGISTER_PLUGIN(my_plugin::MyPlugin, my_plugin::MyPlugin::getInstance())
#define CL_REGISTER_PLUGIN(Class, Instance)                                                                          \
    static_assert(::crosslink::plugin::Loadable<Class>, #Class " must provide `bool load()`");                        \
    CROSSLINK_PLUGIN_ENTRY unsigned int cl_plugin_api_version() { return CROSSLINK_PLUGIN_API_VERSION; }               \
    CROSSLINK_PLUGIN_ENTRY bool cl_plugin_load(::crosslink::plugin::Plugin& self) {                                    \
        Class& crosslinkPluginInstance = (Instance);                                                                   \
        ::crosslink::plugin::bindToPlugin(crosslinkPluginInstance, self);                                              \
        return crosslinkPluginInstance.load();                                                                         \
    }
