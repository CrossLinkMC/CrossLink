#pragma once

#include "crosslink/api/Export.hpp"
#include "crosslink/api/Result.hpp"
#include "crosslink/api/Types.hpp"
#include "crosslink/api/net/Session.hpp"
#include "crosslink/api/net/Transport.hpp"
#include "crosslink/api/proto/packets/LoginPacket.hpp"

#include <cstdint>
#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <typeindex>
#include <utility>

namespace crosslink::plugin {
class Plugin;
}

namespace crosslink {

/// Base of everything published on the event bus. Concrete events are plain
/// structs so they stay trivially usable from a plugin.
struct Event {
    virtual ~Event() = default;
};

struct SessionOpenedEvent final : Event {
    net::PlayerSessionPtr session;
};

struct SessionClosedEvent final : Event {
    net::PlayerSessionPtr session;
    std::string           reason;
};

/// Fired once the relayed login revealed who the player is.
struct IdentityResolvedEvent final : Event {
    net::PlayerSessionPtr session;
    PlayerIdentity        identity;
};

/// Emitted right before the gateway re-signs a Login towards a backend, so a
/// plugin can attach whatever the trusted agent on that backend needs to
/// recognise the verified identity (the gateway itself stays out of that policy).
struct LoginOutboundEvent final : Event {
    LoginOutboundEvent(net::PlayerSessionPtr eventSession, ServerId eventServer, proto::LoginPacket& eventLogin)
    : session(std::move(eventSession)), server(std::move(eventServer)), login(eventLogin) {}

    net::PlayerSessionPtr      session;
    ServerId                   server;
    proto::LoginPacket&        login;
    std::optional<std::string> deviceIdOverride;
    std::optional<std::string> deviceModelOverride;
};

struct BackendOpenedEvent final : Event {
    net::PlayerSessionPtr session;
    net::ConnectionPtr    backend;
    ServerId              server;
};

struct BackendClosedEvent final : Event {
    net::PlayerSessionPtr session;
    net::ConnectionPtr    backend;
    ServerId              server;
    std::string           reason;
};

/// The session's current backend changed. Purely informational: the routing
/// switch already happened.
struct BackendSwitchedEvent final : Event {
    net::PlayerSessionPtr session;
    ServerId              from;
    ServerId              to;
};

/// A control-channel agent (the LeviLamina plugin on a BDS) authenticated.
struct AgentOnlineEvent final : Event {
    AgentId     agent;
    ServerId    server;
    std::string remote;
};

struct AgentOfflineEvent final : Event {
    AgentId     agent;
    ServerId    server;
    std::string reason;
};

/// Publish/subscribe over the events above, plus anything a plugin defines.
///
/// Handlers run on the thread that emits, so they must not block. Subscriptions
/// are owned by the plugin that made them and are dropped when it unloads.
class CROSSLINK_API EventBus {
public:
    using SubscriptionId = std::uint64_t;
    using Handler        = std::function<void(Event&)>;

    [[nodiscard]] static EventBus& instance();

    bool        cancel(SubscriptionId id) noexcept;
    std::size_t cancelAll(std::weak_ptr<plugin::Plugin> owner) noexcept;

    template <typename E, typename F>
    SubscriptionId on(
        F&&                         handler,
        int                         priority = 0,
        std::weak_ptr<plugin::Plugin> owner  = {}
    ) {
        return subscribe(
            std::type_index(typeid(E)),
            [fn = std::forward<F>(handler)](Event& event) { fn(static_cast<E&>(event)); },
            priority,
            std::move(owner)
        );
    }

    template <typename E>
    void emit(E& event) {
        publish(std::type_index(typeid(E)), event);
    }

    template <typename E, typename... Args>
    void emit(Args&&... args) {
        E event{std::forward<Args>(args)...};
        publish(std::type_index(typeid(E)), event);
    }

private:
    EventBus();
    ~EventBus();

    SubscriptionId subscribe(std::type_index type, Handler handler, int priority, std::weak_ptr<plugin::Plugin> owner);
    void           publish(std::type_index type, Event& event);

    struct Impl;
    std::unique_ptr<Impl> mImpl;
};

} // namespace crosslink
