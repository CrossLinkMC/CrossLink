#include "crosslink/api/net/Transport.hpp"

#include <algorithm>
#include <map>
#include <mutex>
#include <utility>

namespace crosslink::net {

Connection::~Connection() = default;

InboundListener::~InboundListener() = default;

Transport::~Transport() = default;

struct TransportRegistry::Impl {
    mutable std::recursive_mutex        mutex;
    std::map<std::string, TransportPtr> transports;
    std::string                         active;
};

TransportRegistry::TransportRegistry() : mImpl(std::make_unique<Impl>()) {}
TransportRegistry::~TransportRegistry() = default;

TransportRegistry& TransportRegistry::instance() {
    static TransportRegistry registry;
    return registry;
}

bool TransportRegistry::registerTransport(std::string name, TransportPtr transport) {
    if (name.empty() || !transport) return false;
    std::lock_guard lock{mImpl->mutex};
    mImpl->transports.insert_or_assign(name, std::move(transport));
    if (mImpl->active.empty()) mImpl->active = name;
    return true;
}

bool TransportRegistry::unregisterTransport(std::string_view name) {
    std::lock_guard lock{mImpl->mutex};
    const auto key = std::string{name};
    if (mImpl->active == key) mImpl->active.clear();
    return mImpl->transports.erase(key) > 0;
}

TransportPtr TransportRegistry::get(std::string_view name) const {
    std::lock_guard lock{mImpl->mutex};
    const auto found = mImpl->transports.find(std::string{name});
    return found == mImpl->transports.end() ? nullptr : found->second;
}

TransportPtr TransportRegistry::active() const {
    std::lock_guard lock{mImpl->mutex};
    if (mImpl->active.empty()) return nullptr;
    const auto found = mImpl->transports.find(mImpl->active);
    return found == mImpl->transports.end() ? nullptr : found->second;
}

bool TransportRegistry::setActive(std::string_view name) {
    std::lock_guard lock{mImpl->mutex};
    if (!mImpl->transports.contains(std::string{name})) return false;
    mImpl->active = std::string{name};
    return true;
}

std::vector<std::string> TransportRegistry::names() const {
    std::lock_guard lock{mImpl->mutex};
    std::vector<std::string> names;
    names.reserve(mImpl->transports.size());
    for (auto const& [name, transport] : mImpl->transports) names.push_back(name);
    return names;
}

} // namespace crosslink::net
