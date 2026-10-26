#pragma once

#include "crosslink/api/plugin/NativePlugin.hpp"

#include <memory>

namespace crosslink::plugin::detail {

/// Maps module handles to the plugins loaded from them, so plugin code can ask
/// "which plugin am I?" from an address inside its own module.
void registerHandle(void* handle, std::shared_ptr<NativePlugin> const& plugin);
void unregisterHandle(void* handle);
[[nodiscard]] std::shared_ptr<NativePlugin> findByHandle(void* handle);

/// The module (HMODULE / dl handle) that contains `address`.
[[nodiscard]] void* moduleOfAddress(void* address) noexcept;

/// A plugin's own `cl_plugin_load` runs before its handle is published, so
/// `NativePlugin::current()` falls back to this while a module is being loaded.
void setCurrentLoading(std::shared_ptr<NativePlugin> const& plugin);
[[nodiscard]] std::shared_ptr<NativePlugin> currentLoading();

} // namespace crosslink::plugin::detail
