#include "crosslink/api/plugin/NativePlugin.hpp"

#include "plugin/NativePluginRegistry.hpp"

#include <mutex>
#include <unordered_map>

#ifdef CROSSLINK_PLATFORM_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <dlfcn.h>
#endif

namespace crosslink::plugin {
namespace {

std::recursive_mutex& handleMutex() {
    static std::recursive_mutex mutex;
    return mutex;
}

std::unordered_map<void*, std::weak_ptr<NativePlugin>>& handleMap() {
    static std::unordered_map<void*, std::weak_ptr<NativePlugin>> map;
    return map;
}

} // namespace

NativePlugin::NativePlugin(Manifest manifest, std::filesystem::path pluginDir)
: Plugin(std::move(manifest), std::move(pluginDir)) {}

NativePlugin::~NativePlugin() {
    if (mHandle != nullptr) detail::unregisterHandle(mHandle);
}

std::shared_ptr<NativePlugin> NativePlugin::current(void* callerAddress) {
    if (auto plugin = detail::findByHandle(detail::moduleOfAddress(callerAddress))) return plugin;
    // Called from inside the plugin's own load entry point, before the host
    // published its handle.
    return detail::currentLoading();
}

std::shared_ptr<NativePlugin> NativePlugin::byHandle(void* handle) { return detail::findByHandle(handle); }

namespace detail {

void registerHandle(void* handle, std::shared_ptr<NativePlugin> const& plugin) {
    if (handle == nullptr || !plugin) return;
    std::lock_guard lock{handleMutex()};
    handleMap()[handle] = plugin;
}

void unregisterHandle(void* handle) {
    if (handle == nullptr) return;
    std::lock_guard lock{handleMutex()};
    handleMap().erase(handle);
}

std::shared_ptr<NativePlugin> findByHandle(void* handle) {
    if (handle == nullptr) return nullptr;
    std::lock_guard lock{handleMutex()};
    auto& map = handleMap();
    const auto found = map.find(handle);
    if (found == map.end()) return nullptr;
    auto plugin = found->second.lock();
    if (!plugin) map.erase(found);
    return plugin;
}

std::weak_ptr<NativePlugin>& loadingSlot() {
    static thread_local std::weak_ptr<NativePlugin> loading;
    return loading;
}

void setCurrentLoading(std::shared_ptr<NativePlugin> const& plugin) { loadingSlot() = plugin; }

std::shared_ptr<NativePlugin> currentLoading() { return loadingSlot().lock(); }

void* moduleOfAddress(void* address) noexcept {    if (address == nullptr) return nullptr;
#ifdef CROSSLINK_PLATFORM_WINDOWS
    HMODULE module{};
    if (::GetModuleHandleExW(
            GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
            reinterpret_cast<LPCWSTR>(address),
            &module
        ) == 0) {
        return nullptr;
    }
    return module;
#else
    Dl_info info{};
    if (::dladdr(address, &info) == 0 || info.dli_fbase == nullptr) return nullptr;
    return info.dli_fbase;
#endif
}

} // namespace detail
} // namespace crosslink::plugin
