#include "crosslink/api/control/ControlChannel.hpp"

#include <algorithm>
#include <format>
#include <map>
#include <mutex>
#include <ranges>
#include <utility>
#include <vector>

namespace crosslink::control {
namespace {

std::uint64_t readUint64(Json const& json, std::string_view key) {
    const auto found = json.find(key);
    if (found == json.end() || !found->is_number_unsigned()) return 0;
    return found->get<std::uint64_t>();
}

} // namespace

Json Message::toJson() const {
    auto json = Json::object();
    json["v"] = 1;
    json["id"] = id;
    if (replyTo != 0) json["replyTo"] = replyTo;
    json["kind"] = kind;
    json["payload"] = payload.is_null() ? Json::object() : payload;
    return json;
}

Result<Message> Message::fromJson(Json const& json) {
    if (!json.is_object()) return std::unexpected(Error{"a control message must be a JSON object"});

    const auto kindFound = json.find("kind");
    if (kindFound == json.end() || !kindFound->is_string()) {
        return std::unexpected(Error{"a control message needs a string 'kind'"});
    }

    Message message;
    message.id = readUint64(json, "id");
    message.replyTo = readUint64(json, "replyTo");
    message.kind = kindFound->get<std::string>();
    if (const auto payload = json.find("payload"); payload != json.end()) message.payload = *payload;
    return message;
}

AgentChannel::AgentChannel() = default;
AgentChannel::~AgentChannel() = default;

struct AgentRegistry::Impl {
    struct Subscription {
        std::uint64_t                  id{};
        std::string                    kind;
        int                            priority{};
        AgentRegistry::RequestHandler  handler;
        std::weak_ptr<plugin::Plugin>  owner;
        /// False for host-owned handlers, which have no plugin to expire with.
        bool                           owned{};
    };

    mutable std::recursive_mutex              mutex;
    std::map<std::string, AgentChannelPtr>    byServer;
    std::vector<AgentChannelPtr>              channels;
    std::vector<Subscription>                 subscriptions;
    std::uint64_t                             nextSubscription{1};
};

AgentRegistry::AgentRegistry() : mImpl(std::make_unique<Impl>()) {}
AgentRegistry::~AgentRegistry() = default;

AgentRegistry& AgentRegistry::instance() {
    static AgentRegistry registry;
    return registry;
}

AgentChannelPtr AgentRegistry::find(AgentId const& id) const {
    std::lock_guard lock{mImpl->mutex};
    for (auto const& channel : mImpl->channels) {
        if (channel->id() == id) return channel;
    }
    return nullptr;
}

AgentChannelPtr AgentRegistry::forServer(ServerId const& server) const {
    std::lock_guard lock{mImpl->mutex};
    const auto found = mImpl->byServer.find(server.str());
    return found == mImpl->byServer.end() ? nullptr : found->second;
}

std::vector<AgentChannelPtr> AgentRegistry::all() const {
    std::lock_guard lock{mImpl->mutex};
    return mImpl->channels;
}

std::size_t AgentRegistry::count() const {
    std::lock_guard lock{mImpl->mutex};
    return mImpl->channels.size();
}

std::uint64_t AgentRegistry::subscribe(
    std::string_view              kind,
    RequestHandler                handler,
    int                           priority,
    std::weak_ptr<plugin::Plugin> owner
) {
    if (!handler) return 0;
    std::lock_guard lock{mImpl->mutex};
    const auto id = mImpl->nextSubscription++;
    mImpl->subscriptions.push_back(
        {id, std::string{kind}, priority, std::move(handler), owner, !owner.expired()}
    );
    std::stable_sort(mImpl->subscriptions.begin(), mImpl->subscriptions.end(), [](auto const& left, auto const& right) {
        return left.priority < right.priority;
    });
    return id;
}

bool AgentRegistry::unsubscribe(std::uint64_t subscription) noexcept {
    std::lock_guard lock{mImpl->mutex};
    return std::erase_if(mImpl->subscriptions, [subscription](auto const& entry) { return entry.id == subscription; }) > 0;
}

std::size_t AgentRegistry::unsubscribeAll(std::weak_ptr<plugin::Plugin> owner) noexcept {
    const auto target = owner.lock();
    if (!target) return 0;
    std::lock_guard lock{mImpl->mutex};
    return std::erase_if(mImpl->subscriptions, [&target](auto const& entry) { return entry.owner.lock() == target; });
}

void AgentRegistry::attach(AgentChannelPtr channel) {
    if (!channel) return;
    std::lock_guard lock{mImpl->mutex};
    const auto key = channel->server().str();
    mImpl->byServer.insert_or_assign(key, channel);
    std::erase_if(mImpl->channels, [&key](auto const& existing) { return existing->server().str() == key; });
    mImpl->channels.push_back(std::move(channel));
}

void AgentRegistry::detach(ServerId const& server) {
    std::lock_guard lock{mImpl->mutex};
    const auto key = server.str();
    mImpl->byServer.erase(key);
    std::erase_if(mImpl->channels, [&key](auto const& existing) { return existing->server().str() == key; });
}

bool AgentRegistry::handles(std::string_view kind) const {
    std::lock_guard lock{mImpl->mutex};
    return std::ranges::any_of(mImpl->subscriptions, [kind](auto const& entry) { return entry.kind == kind; });
}

Result<Json> AgentRegistry::dispatch(std::string_view kind, AgentChannel& agent, Json const& payload) {
    std::vector<RequestHandler> chain;
    {
        std::lock_guard lock{mImpl->mutex};
        for (auto const& entry : mImpl->subscriptions) {
            if (entry.kind != kind) continue;
            if (entry.owned && entry.owner.expired()) continue;
            chain.push_back(entry.handler);
        }
    }
    if (chain.empty()) return std::unexpected(Error{std::format("no handler for control message '{}'", kind)});

    Error last{"no handler accepted the message"};
    for (auto const& handler : chain) {
        auto result = handler(agent, payload);
        if (result) return *result;
        last = result.error();
    }
    return std::unexpected(last);
}

} // namespace crosslink::control
