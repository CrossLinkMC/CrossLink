#include "crosslink/api/Events.hpp"

#include <algorithm>
#include <map>
#include <mutex>
#include <vector>

namespace crosslink {

struct EventBus::Impl {
    struct Subscription {
        SubscriptionId                    id{};
        int                               priority{};
        Handler                           handler;
        std::weak_ptr<plugin::Plugin>     owner;
        /// False for host-owned subscriptions, which never expire.
        bool                              owned{};
    };

    mutable std::recursive_mutex                    mutex;
    std::multimap<std::type_index, Subscription>    subscriptions;
    SubscriptionId                                  nextId{1};
};

EventBus::EventBus() : mImpl(std::make_unique<Impl>()) {}
EventBus::~EventBus() = default;

EventBus& EventBus::instance() {
    static EventBus bus;
    return bus;
}

EventBus::SubscriptionId EventBus::subscribe(
    std::type_index               type,
    Handler                       handler,
    int                           priority,
    std::weak_ptr<plugin::Plugin> owner
) {
    if (!handler) return 0;
    std::lock_guard lock{mImpl->mutex};
    const auto id = mImpl->nextId++;
    mImpl->subscriptions.emplace(type, Impl::Subscription{id, priority, std::move(handler), owner, !owner.expired()});
    return id;
}

void EventBus::publish(std::type_index type, Event& event) {
    std::vector<Impl::Subscription> snapshot;
    {
        std::lock_guard lock{mImpl->mutex};
        const auto range = mImpl->subscriptions.equal_range(type);
        snapshot.reserve(static_cast<std::size_t>(std::distance(range.first, range.second)));
        for (auto it = range.first; it != range.second; ++it) snapshot.push_back(it->second);
    }

    std::stable_sort(snapshot.begin(), snapshot.end(), [](auto const& left, auto const& right) {
        return left.priority < right.priority;
    });

    for (auto const& subscription : snapshot) {
        if (subscription.owned && subscription.owner.expired()) continue;
        subscription.handler(event);
    }
}

bool EventBus::cancel(SubscriptionId id) noexcept {
    std::lock_guard lock{mImpl->mutex};
    return std::erase_if(mImpl->subscriptions, [id](auto const& entry) { return entry.second.id == id; }) > 0;
}

std::size_t EventBus::cancelAll(std::weak_ptr<plugin::Plugin> owner) noexcept {
    const auto target = owner.lock();
    if (!target) return 0;
    std::lock_guard lock{mImpl->mutex};
    return std::erase_if(mImpl->subscriptions, [&target](auto const& entry) { return entry.second.owner.lock() == target; });
}

} // namespace crosslink
