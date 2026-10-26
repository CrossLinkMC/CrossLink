#include "plugin/NativePluginManager.hpp"

#include "crosslink/api/Gateway.hpp"
#include "plugin/ManifestJson.hpp"
#include "plugin/NativePluginRegistry.hpp"

#include <algorithm>
#include <format>
#include <fstream>
#include <sstream>

#ifdef CROSSLINK_PLATFORM_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <dlfcn.h>
#endif

namespace crosslink::plugin {
namespace {

using LifecycleFn = bool (*)(Plugin&);
using ApiVersionFn = unsigned int (*)();

/// Minimal RAII over LoadLibrary/dlopen. Kept local: nothing above the loader
/// sees a raw module handle except as `void*` bookkeeping.
class DynamicLibrary {
public:
    DynamicLibrary() = default;
    ~DynamicLibrary() { close(); }

    DynamicLibrary(DynamicLibrary const&)            = delete;
    DynamicLibrary& operator=(DynamicLibrary const&) = delete;

    DynamicLibrary(DynamicLibrary&& other) noexcept : mHandle(other.mHandle) { other.mHandle = nullptr; }
    DynamicLibrary& operator=(DynamicLibrary&& other) noexcept {
        if (this != &other) {
            close();
            mHandle = other.mHandle;
            other.mHandle = nullptr;
        }
        return *this;
    }

    [[nodiscard]] Result<> open(std::filesystem::path const& file) {
#ifdef CROSSLINK_PLATFORM_WINDOWS
        mHandle = ::LoadLibraryW(file.wstring().c_str());
        if (mHandle == nullptr) {
            return std::unexpected(Error{std::format("LoadLibrary failed for '{}' (winerror {})", file.string(), ::GetLastError())});
        }
#else
        mHandle = ::dlopen(file.string().c_str(), RTLD_NOW | RTLD_LOCAL);
        if (mHandle == nullptr) {
            const char* message = ::dlerror();
            return std::unexpected(Error{std::format("dlopen failed for '{}': {}", file.string(), message ? message : "unknown")});
        }
#endif
        return {};
    }

    [[nodiscard]] void* symbol(std::string_view name) const {
        if (mHandle == nullptr) return nullptr;
        const auto symbolName = std::string{name};
#ifdef CROSSLINK_PLATFORM_WINDOWS
        return reinterpret_cast<void*>(::GetProcAddress(static_cast<HMODULE>(mHandle), symbolName.c_str()));
#else
        return ::dlsym(mHandle, symbolName.c_str());
#endif
    }

    void close() {
        if (mHandle == nullptr) return;
#ifdef CROSSLINK_PLATFORM_WINDOWS
        ::FreeLibrary(static_cast<HMODULE>(mHandle));
#else
        ::dlclose(mHandle);
#endif
        mHandle = nullptr;
    }

    [[nodiscard]] void* handle() const noexcept { return mHandle; }
    void* release() noexcept {
        void* handle = mHandle;
        mHandle = nullptr;
        return handle;
    }

private:
    void* mHandle{};
};

std::unordered_map<std::string, DynamicLibrary>& openLibraries() {
    static std::unordered_map<std::string, DynamicLibrary> libraries;
    return libraries;
}

/// Lets a plugin find DLLs sitting next to it, the same trick LeviLamina uses for
/// mod directories.
void addToModuleSearchPath(std::filesystem::path const& directory) {
#ifdef CROSSLINK_PLATFORM_WINDOWS
    wchar_t* current{};
    std::wstring combined = directory.wstring();
    if (::GetEnvironmentVariableW(L"PATH", nullptr, 0) != 0) {
        const auto length = ::GetEnvironmentVariableW(L"PATH", nullptr, 0);
        auto buffer = std::make_unique<wchar_t[]>(length + 1);
        if (::GetEnvironmentVariableW(L"PATH", buffer.get(), length + 1) != 0) {
            current = buffer.get();
            combined += L";";
            combined += current;
        }
    }
    ::SetEnvironmentVariableW(L"PATH", combined.c_str());
#else
    static_cast<void>(directory);
#endif
}

} // namespace

NativePluginManager::NativePluginManager(Gateway& gateway) : PluginManager("native"), mGateway(gateway) {}

NativePluginManager::~NativePluginManager() {
    for (auto const& name : loadOrder()) {
        if (auto plugin = getPlugin(name)) {
            (void)plugin->unload();
        }
        auto& libraries = openLibraries();
        if (const auto found = libraries.find(name); found != libraries.end()) libraries.erase(found);
    }
}

Result<Manifest> NativePluginManager::readManifest(std::filesystem::path const& pluginDir) {
    const auto file = pluginDir / "manifest.json";
    std::ifstream input{file};
    if (!input) return std::unexpected(Error{std::format("no manifest.json in '{}'", pluginDir.string())});

    std::stringstream buffer;
    buffer << input.rdbuf();
    const auto content = buffer.str();
    if (content.empty()) return std::unexpected(Error{std::format("'{}' is empty", file.string())});

    const auto json = nlohmann::ordered_json::parse(content, nullptr, false, true);
    if (json.is_discarded()) return std::unexpected(Error{std::format("'{}' is not valid JSON", file.string())});

    auto manifest = manifestFromJson(json);
    if (!manifest) return manifest;

    // The folder name is the plugin's identity, exactly like a LeviLamina mod.
    const auto folder = pluginDir.filename().string();
    if (manifest->name != folder) {
        return std::unexpected(
            Error{std::format("manifest name '{}' must match its folder '{}'", manifest->name, folder)}
        );
    }
    return manifest;
}

std::vector<std::string> NativePluginManager::loadOrder() const { return mLoadOrder; }

Result<> NativePluginManager::load(Manifest manifest) {
    if (manifest.type != "native") {
        return std::unexpected(Error{std::format("plugin '{}' has type '{}', this manager only loads 'native'", manifest.name, manifest.type)});
    }
    if (hasPlugin(manifest.name)) {
        return std::unexpected(Error{std::format("plugin '{}' is already loaded", manifest.name)});
    }

    const auto pluginDir = mRoot / manifest.name;
    const auto entryFile = pluginDir / manifest.entry;
    if (!std::filesystem::exists(entryFile)) {
        return std::unexpected(Error{std::format("entry library '{}' does not exist", entryFile.string())});
    }

    addToModuleSearchPath(pluginDir);

    DynamicLibrary library;
    if (auto result = library.open(entryFile); !result) return result;

    const auto versionSymbol = reinterpret_cast<ApiVersionFn>(library.symbol("cl_plugin_api_version"));
    if (versionSymbol == nullptr) {
        return std::unexpected(Error{std::format("'{}' does not export cl_plugin_api_version; is it a CrossLink plugin?", manifest.name)});
    }
    const auto pluginApiVersion = versionSymbol();
    if (pluginApiVersion != CROSSLINK_PLUGIN_API_VERSION) {
        return std::unexpected(Error{std::format(
            "plugin '{}' was built against plugin API {}, the host provides {}",
            manifest.name,
            pluginApiVersion,
            CROSSLINK_PLUGIN_API_VERSION
        )});
    }

    const auto loadFn = reinterpret_cast<LifecycleFn>(library.symbol("cl_plugin_load"));
    if (loadFn == nullptr) {
        return std::unexpected(Error{std::format("'{}' does not export cl_plugin_load", manifest.name)});
    }

    auto plugin = std::make_shared<NativePlugin>(manifest, pluginDir);
    plugin->setHandle(library.handle());
    plugin->bindGateway(mGateway);
    plugin->setLifecycle(PluginEvent::Load, [loadFn](Plugin& self) { return loadFn(self); });

    // Optional direct exports; a plugin that binds its own callbacks inside
    // cl_plugin_load simply overrides these.
    for (const auto& [symbolName, event] : {
             std::pair{"cl_plugin_enable", PluginEvent::Enable},
             std::pair{"cl_plugin_disable", PluginEvent::Disable},
             std::pair{"cl_plugin_unload", PluginEvent::Unload},
         }) {
        if (const auto fn = reinterpret_cast<LifecycleFn>(library.symbol(symbolName))) {
            plugin->setLifecycle(event, [fn](Plugin& self) { return fn(self); });
        }
    }

    // Published before load() so that code inside the plugin's own entry point can
    // ask "which plugin am I?" through NativePlugin::current().
    detail::registerHandle(plugin->handle(), plugin);
    detail::setCurrentLoading(plugin);
    auto loaded = plugin->load();
    detail::setCurrentLoading(nullptr);
    if (!loaded) {
        detail::unregisterHandle(plugin->handle());
        library.close();
        return loaded;
    }

    openLibraries().insert_or_assign(manifest.name, std::move(library));
    addPlugin(manifest.name, plugin);
    mLoadOrder.push_back(manifest.name);
    mGateway.logger().info("plugin '{}' v{} loaded", manifest.name, manifest.versionString());
    return {};
}

Result<> NativePluginManager::unload(std::string_view name) {
    const auto key = std::string{name};
    const auto plugin = std::dynamic_pointer_cast<NativePlugin>(getPlugin(key));
    if (!plugin) return std::unexpected(Error{std::format("native plugin '{}' is not loaded", key)});

    if (auto result = plugin->unload(); !result) return result;

    detail::unregisterHandle(plugin->handle());
    auto& libraries = openLibraries();
    if (const auto found = libraries.find(key); found != libraries.end()) {
        // Frees the module; nothing may touch plugin state after this point.
        found->second.close();
        libraries.erase(found);
    }
    plugin->setHandle(nullptr);

    removePlugin(key);
    std::erase(mLoadOrder, key);
    LoggerRegistry::instance().forget(key);
    mGateway.logger().info("plugin '{}' unloaded", key);
    return {};
}

} // namespace crosslink::plugin
