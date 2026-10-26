#include "crosslink/api/plugin/PluginManager.hpp"

#include <format>
#include <map>
#include <mutex>
#include <utility>

namespace crosslink::plugin {

struct PluginManager::Impl {
    std::string                                  type;
    mutable std::recursive_mutex                 mutex;
    std::map<std::string, std::shared_ptr<Plugin>> plugins;
};

PluginManager::PluginManager(std::string type) : mImpl(std::make_unique<Impl>()) { mImpl->type = std::move(type); }

PluginManager::~PluginManager() = default;

std::string_view PluginManager::type() const noexcept { return mImpl->type; }

bool PluginManager::hasPlugin(std::string_view name) const {
    std::lock_guard lock{mImpl->mutex};
    return mImpl->plugins.contains(std::string{name});
}

std::shared_ptr<Plugin> PluginManager::getPlugin(std::string_view name) const {
    std::lock_guard lock{mImpl->mutex};
    const auto found = mImpl->plugins.find(std::string{name});
    return found == mImpl->plugins.end() ? nullptr : found->second;
}

std::size_t PluginManager::count() const {
    std::lock_guard lock{mImpl->mutex};
    return mImpl->plugins.size();
}

std::vector<std::shared_ptr<Plugin>> PluginManager::plugins() const {
    std::lock_guard lock{mImpl->mutex};
    std::vector<std::shared_ptr<Plugin>> snapshot;
    snapshot.reserve(mImpl->plugins.size());
    for (auto const& [name, plugin] : mImpl->plugins) snapshot.push_back(plugin);
    return snapshot;
}

void PluginManager::addPlugin(std::string_view name, std::shared_ptr<Plugin> const& plugin) {
    std::lock_guard lock{mImpl->mutex};
    mImpl->plugins.insert_or_assign(std::string{name}, plugin);
}

void PluginManager::removePlugin(std::string_view name) {
    std::lock_guard lock{mImpl->mutex};
    mImpl->plugins.erase(std::string{name});
}

Result<> PluginManager::enable(std::string_view name) {
    const auto plugin = getPlugin(name);
    if (!plugin) return std::unexpected(Error{std::format("no {} plugin named '{}'", mImpl->type, name)});
    return plugin->enable();
}

Result<> PluginManager::disable(std::string_view name) {
    const auto plugin = getPlugin(name);
    if (!plugin) return std::unexpected(Error{std::format("no {} plugin named '{}'", mImpl->type, name)});
    return plugin->disable();
}

} // namespace crosslink::plugin
