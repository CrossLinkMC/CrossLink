#include "crosslink/api/plugin/PluginManagerRegistry.hpp"

#include "crosslink/api/Gateway.hpp"
#include "plugin/ManifestJson.hpp"
#include "plugin/NativePluginManager.hpp"
#include "plugin/PluginLoadPlanner.hpp"

#include <algorithm>
#include <filesystem>
#include <format>
#include <map>
#include <memory>
#include <mutex>
#include <set>
#include <utility>
#include <vector>

namespace crosslink::plugin {

struct PluginManagerRegistry::Impl {
    struct Subscription {
        std::uint64_t                         id{};
        PluginEvent                           event{PluginEvent::Load};
        std::function<void(std::string_view)> callback;
        std::weak_ptr<Plugin>                 owner;
        /// False for host-owned subscriptions, which never expire.
        bool                                  owned{};
    };

    mutable std::recursive_mutex                          mutex;
    std::map<std::string, std::shared_ptr<PluginManager>> managers;
    Gateway*                                              gateway{};
    std::uint64_t                                         nextCallbackId{1};
    std::vector<Subscription>                             subscriptions;
    /// plugin -> the dependencies it was actually loaded with, used to refuse an
    /// unload that would leave a dependent dangling.
    std::map<std::string, std::set<std::string>>          lifecycleDependencies;
    std::vector<std::string>                              loadOrder;
    std::filesystem::path                                 pluginsRoot;

    void notify(PluginEvent event, std::string_view name) {
        // Copy first: a callback may unsubscribe.
        std::vector<Subscription> snapshot;
        {
            std::lock_guard lock{mutex};
            for (auto& subscription : subscriptions) {
                if (subscription.event != event) continue;
                if (subscription.owned && subscription.owner.expired()) continue;
                snapshot.push_back(subscription);
            }
        }
        for (auto& subscription : snapshot) {
            if (subscription.owned && subscription.owner.expired()) continue;
            subscription.callback(name);
        }
    }
};

PluginManagerRegistry::PluginManagerRegistry() : mImpl(std::make_unique<Impl>()) {}

PluginManagerRegistry::~PluginManagerRegistry() = default;

PluginManagerRegistry& PluginManagerRegistry::instance() {
    static PluginManagerRegistry registry;
    return registry;
}

bool PluginManagerRegistry::addManager(std::shared_ptr<PluginManager> manager) {
    if (!manager) return false;
    std::lock_guard lock{mImpl->mutex};
    mImpl->managers.insert_or_assign(std::string{manager->type()}, std::move(manager));
    return true;
}

bool PluginManagerRegistry::removeManager(std::string_view type) {
    std::lock_guard lock{mImpl->mutex};
    return mImpl->managers.erase(std::string{type}) > 0;
}

bool PluginManagerRegistry::hasManager(std::string_view type) const {
    std::lock_guard lock{mImpl->mutex};
    return mImpl->managers.contains(std::string{type});
}

std::shared_ptr<PluginManager> PluginManagerRegistry::getManager(std::string_view type) const {
    std::lock_guard lock{mImpl->mutex};
    const auto found = mImpl->managers.find(std::string{type});
    return found == mImpl->managers.end() ? nullptr : found->second;
}

std::shared_ptr<PluginManager> PluginManagerRegistry::getManagerForPlugin(std::string_view name) const {
    const auto plugin = getPlugin(name);
    return plugin ? getManager(plugin->type()) : nullptr;
}

std::vector<std::shared_ptr<PluginManager>> PluginManagerRegistry::managers() const {
    std::lock_guard lock{mImpl->mutex};
    std::vector<std::shared_ptr<PluginManager>> snapshot;
    snapshot.reserve(mImpl->managers.size());
    for (auto const& [type, manager] : mImpl->managers) snapshot.push_back(manager);
    return snapshot;
}

std::vector<std::shared_ptr<Plugin>> PluginManagerRegistry::plugins() const {
    std::vector<std::shared_ptr<Plugin>> all;
    for (auto const& manager : managers()) {
        for (auto& plugin : manager->plugins()) all.push_back(std::move(plugin));
    }
    std::ranges::sort(all, [](auto const& left, auto const& right) { return left->name() < right->name(); });
    return all;
}

bool PluginManagerRegistry::hasPlugin(std::string_view name) const { return getPlugin(name) != nullptr; }

std::shared_ptr<Plugin> PluginManagerRegistry::getPlugin(std::string_view name) const {
    for (auto const& manager : managers()) {
        if (auto plugin = manager->getPlugin(name)) return plugin;
    }
    return nullptr;
}

std::string PluginManagerRegistry::pluginType(std::string_view name) const {
    const auto plugin = getPlugin(name);
    return plugin ? std::string{plugin->type()} : std::string{};
}

PluginManagerRegistry::CallbackId PluginManagerRegistry::executeOnPlugin(
    PluginEvent                           event,
    std::function<void(std::string_view)> callback,
    std::weak_ptr<Plugin>                 owner
) noexcept {
    std::lock_guard lock{mImpl->mutex};
    const auto id = mImpl->nextCallbackId++;
    mImpl->subscriptions.push_back({id, event, std::move(callback), owner, !owner.expired()});
    return id;
}

bool PluginManagerRegistry::eraseOnPluginCallback(CallbackId id) noexcept {
    std::lock_guard lock{mImpl->mutex};
    const auto removed = std::erase_if(mImpl->subscriptions, [id](auto const& subscription) {
        return subscription.id == id;
    });
    return removed > 0;
}

std::size_t PluginManagerRegistry::eraseOnPluginCallbacks(std::weak_ptr<Plugin> owner) noexcept {
    std::lock_guard lock{mImpl->mutex};
    const auto target = owner.lock();
    if (!target) return 0;
    return std::erase_if(mImpl->subscriptions, [&target](auto const& subscription) {
        return subscription.owner.lock() == target;
    });
}

void PluginManagerRegistry::bindGateway(Gateway& gateway) noexcept { mImpl->gateway = &gateway; }

namespace {

Logger& hostLogger(Gateway* gateway) {
    if (gateway != nullptr) return gateway->logger();
    return LoggerRegistry::instance().getOrCreate("CrossLink");
}

} // namespace

Result<PluginLoadReport> PluginManagerRegistry::loadPluginsFrom(std::filesystem::path const& root) {
    PluginLoadReport report;
    std::lock_guard lock{mImpl->mutex};
    mImpl->pluginsRoot = root;

    if (!hasManager("native")) {
        if (mImpl->gateway == nullptr) return std::unexpected(Error{"the plugin registry has no gateway bound"});
        addManager(std::make_shared<NativePluginManager>(*mImpl->gateway));
    }
    if (auto* native = dynamic_cast<NativePluginManager*>(getManager("native").get())) native->setPluginsRoot(root);

    std::error_code ignored;
    if (!std::filesystem::exists(root, ignored)) {
        std::filesystem::create_directories(root, ignored);
        return report;
    }

    std::map<std::string, Manifest> manifests;
    std::map<std::string, std::filesystem::path> directories;
    for (auto const& entry : std::filesystem::directory_iterator{root}) {
        if (!entry.is_directory()) continue;
        const auto name = entry.path().filename().string();
        if (!std::filesystem::exists(entry.path() / "manifest.json")) {
            hostLogger(mImpl->gateway).warn("skipping '{}': no manifest.json", entry.path().string());
            continue;
        }
        auto manifest = NativePluginManager::readManifest(entry.path());
        if (!manifest) {
            report.rejected[name] = manifest.error().message;
            hostLogger(mImpl->gateway).error("{}", manifest.error().message);
            continue;
        }
        manifests[name] = *manifest;
        directories[name] = entry.path();
    }

    const auto plan = PluginLoadPlanner::resolve(manifests);
    report.order = plan.order;

    for (auto const& [name, issue] : plan.rejected) {
        report.rejected[name] = issue.message;
        hostLogger(mImpl->gateway).error("plugin '{}' not loaded: {}", name, issue.message);
    }

    for (auto const& name : plan.order) {
        // A dependency may have failed at load time even though resolution passed.
        bool dependenciesReady = true;
        for (auto const& dependency : manifests.at(name).dependencies) {
            if (!hasPlugin(dependency.name)) {
                dependenciesReady = false;
                break;
            }
        }
        if (!dependenciesReady) {
            report.rejected[name] = "a dependency failed to load";
            hostLogger(mImpl->gateway).error("plugin '{}' skipped: a dependency failed to load", name);
            continue;
        }

        auto manager = getManager(manifests.at(name).type);
        if (!manager) {
            report.rejected[name] = std::format("no plugin manager for type '{}'", manifests.at(name).type);
            hostLogger(mImpl->gateway).error("{}", report.rejected[name]);
            continue;
        }
        if (auto result = manager->load(manifests.at(name)); !result) {
            report.rejected[name] = result.error().message;
            hostLogger(mImpl->gateway).error("plugin '{}' failed to load: {}", name, result.error().message);
            continue;
        }

        report.loaded.push_back(name);
        const auto dependencies = plan.lifecycleDependencies.find(name);
        mImpl->lifecycleDependencies[name] = dependencies == plan.lifecycleDependencies.end()
                                                ? std::set<std::string>{}
                                                : dependencies->second;
        mImpl->loadOrder.push_back(name);
        mImpl->notify(PluginEvent::Load, name);
    }

    hostLogger(mImpl->gateway).info("{} plugin(s) loaded, {} rejected", report.loaded.size(), report.rejected.size());
    return report;
}

Result<> PluginManagerRegistry::loadPlugin(std::filesystem::path const& pluginDir) {
    auto manifest = NativePluginManager::readManifest(pluginDir);
    if (!manifest) return std::unexpected(manifest.error());

    std::lock_guard lock{mImpl->mutex};
    if (hasPlugin(manifest->name)) {
        return std::unexpected(Error{std::format("plugin '{}' is already loaded", manifest->name)});
    }
    if (!manifest->compatibleWithHost()) {
        return std::unexpected(Error{std::format("plugin '{}' is not compatible with this host", manifest->name)});
    }

    for (auto const& dependency : manifest->dependencies) {
        const auto loaded = getPlugin(dependency.name);
        if (!loaded) {
            return std::unexpected(Error{std::format("dependency '{}' of '{}' is not loaded", dependency.name, manifest->name)});
        }
        if (!PluginLoadPlanner::matchesDependency(loaded->manifest(), dependency)) {
            return std::unexpected(Error{std::format(
                "dependency '{}' of '{}' is {}, need {}",
                dependency.name,
                manifest->name,
                loaded->manifest().versionString(),
                dependency.version.toString()
            )});
        }
    }
    for (auto const& conflict : manifest->conflicts) {
        if (const auto loaded = getPlugin(conflict.name);
            loaded && PluginLoadPlanner::matchesDependency(loaded->manifest(), conflict)) {
            return std::unexpected(Error{std::format("'{}' conflicts with loaded plugin '{}'", manifest->name, conflict.name)});
        }
    }
    // The other direction: an already loaded plugin may have declared a conflict
    // against the one being added.
    for (auto const& existing : plugins()) {
        for (auto const& conflict : existing->manifest().conflicts) {
            if (conflict.name == manifest->name && PluginLoadPlanner::matchesDependency(*manifest, conflict)) {
                return std::unexpected(
                    Error{std::format("loaded plugin '{}' conflicts with '{}'", existing->name(), manifest->name)}
                );
            }
        }
    }

    auto manager = getManager(manifest->type);
    if (!manager) return std::unexpected(Error{std::format("no plugin manager for type '{}'", manifest->type)});

    CROSSLINK_PROPAGATE(manager->load(*manifest));

    std::set<std::string> bound;
    for (auto const& dependency : manifest->dependencies) bound.insert(dependency.name);
    for (auto const& dependency : manifest->optionalDependencies) {
        if (const auto loaded = getPlugin(dependency.name);
            loaded && PluginLoadPlanner::matchesDependency(loaded->manifest(), dependency)) {
            bound.insert(dependency.name);
        }
    }
    mImpl->lifecycleDependencies[manifest->name] = std::move(bound);
    mImpl->loadOrder.push_back(manifest->name);
    mImpl->notify(PluginEvent::Load, manifest->name);
    return {};
}

Result<> PluginManagerRegistry::enableAll() {
    std::vector<std::string> order;
    {
        std::lock_guard lock{mImpl->mutex};
        order = mImpl->loadOrder;
    }
    for (auto const& name : order) {
        if (auto result = enablePlugin(name); !result) {
            hostLogger(mImpl->gateway).error("plugin '{}' failed to enable: {}", name, result.error().message);
        }
    }
    return {};
}

Result<> PluginManagerRegistry::disableAll() {
    std::vector<std::string> order;
    {
        std::lock_guard lock{mImpl->mutex};
        order = mImpl->loadOrder;
    }
    for (auto it = order.rbegin(); it != order.rend(); ++it) {
        if (auto result = disablePlugin(*it); !result) {
            hostLogger(mImpl->gateway).error("plugin '{}' failed to disable: {}", *it, result.error().message);
        }
    }
    return {};
}

Result<> PluginManagerRegistry::unloadAll() {
    CROSSLINK_PROPAGATE(disableAll());
    std::vector<std::string> order;
    {
        std::lock_guard lock{mImpl->mutex};
        order = mImpl->loadOrder;
    }
    for (auto it = order.rbegin(); it != order.rend(); ++it) {
        if (auto result = unloadPlugin(*it); !result) {
            hostLogger(mImpl->gateway).error("plugin '{}' failed to unload: {}", *it, result.error().message);
        }
    }
    return {};
}

Result<> PluginManagerRegistry::enablePlugin(std::string_view name) {
    const auto key = std::string{name};
    const auto plugin = getPlugin(key);
    if (!plugin) return std::unexpected(Error{std::format("plugin '{}' is not loaded", key)});
    if (plugin->isEnabled()) return {};

    std::set<std::string> dependencies;
    {
        std::lock_guard lock{mImpl->mutex};
        const auto found = mImpl->lifecycleDependencies.find(key);
        if (found != mImpl->lifecycleDependencies.end()) dependencies = found->second;
    }
    for (auto const& dependency : dependencies) {
        const auto loaded = getPlugin(dependency);
        if (!loaded) return std::unexpected(Error{std::format("dependency '{}' of '{}' is not loaded", dependency, key)});
        if (!loaded->isEnabled()) {
            return std::unexpected(Error{std::format("dependency '{}' of '{}' is not enabled", dependency, key)});
        }
    }

    auto manager = getManager(plugin->type());
    if (!manager) return std::unexpected(Error{std::format("no plugin manager for type '{}'", plugin->type())});
    CROSSLINK_PROPAGATE(manager->enable(key));
    mImpl->notify(PluginEvent::Enable, key);
    return {};
}

Result<> PluginManagerRegistry::disablePlugin(std::string_view name) {
    const auto key = std::string{name};
    const auto plugin = getPlugin(key);
    if (!plugin) return std::unexpected(Error{std::format("plugin '{}' is not loaded", key)});
    if (!plugin->isEnabled()) return {};

    for (auto const& dependent : dependentsOf(key)) {
        const auto loaded = getPlugin(dependent);
        if (loaded && loaded->isEnabled()) {
            return std::unexpected(Error{std::format("plugin '{}' still depends on '{}' and is enabled", dependent, key)});
        }
    }

    auto manager = getManager(plugin->type());
    if (!manager) return std::unexpected(Error{std::format("no plugin manager for type '{}'", plugin->type())});
    CROSSLINK_PROPAGATE(manager->disable(key));
    mImpl->notify(PluginEvent::Disable, key);
    return {};
}

Result<> PluginManagerRegistry::unloadPlugin(std::string_view name) {
    const auto key = std::string{name};
    const auto plugin = getPlugin(key);
    if (!plugin) return std::unexpected(Error{std::format("plugin '{}' is not loaded", key)});

    if (const auto dependents = dependentsOf(key); !dependents.empty()) {
        std::string list;
        for (auto const& dependent : dependents) {
            if (!list.empty()) list += ", ";
            list += dependent;
        }
        return std::unexpected(Error{std::format("'{}' cannot be unloaded, still needed by: {}", key, list)});
    }

    auto manager = getManager(plugin->type());
    if (!manager) return std::unexpected(Error{std::format("no plugin manager for type '{}'", plugin->type())});
    CROSSLINK_PROPAGATE(manager->unload(key));

    {
        std::lock_guard lock{mImpl->mutex};
        mImpl->lifecycleDependencies.erase(key);
        std::erase(mImpl->loadOrder, key);
        // Subscriptions belonging to this plugin die with it.
        std::erase_if(mImpl->subscriptions, [&plugin](auto const& subscription) {
            return subscription.owner.expired() || subscription.owner.lock() == plugin;
        });
    }
    mImpl->notify(PluginEvent::Unload, key);
    return {};
}

std::vector<std::string> PluginManagerRegistry::dependentsOf(std::string_view name) const {
    const auto key = std::string{name};
    std::lock_guard lock{mImpl->mutex};
    std::vector<std::string> dependents;
    for (auto const& [plugin, dependencies] : mImpl->lifecycleDependencies) {
        if (plugin == key) continue;
        if (dependencies.contains(key)) dependents.push_back(plugin);
    }
    std::ranges::sort(dependents);
    return dependents;
}

} // namespace crosslink::plugin
