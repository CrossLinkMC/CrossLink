#pragma once

#include "crosslink/api/Export.hpp"
#include "crosslink/api/Result.hpp"
#include "crosslink/api/Types.hpp"

#include <nlohmann/json.hpp>

#include <chrono>
#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

namespace crosslink::plugin {
class Plugin;
}

/// Control plane between the gateway and the agents running inside each backend
/// server (the LeviLamina plugin on a BDS).
///
/// One persistent TCP connection per agent, framed as JSON Lines: exactly one
/// JSON object per line. Requests carry an id and are answered by a reply whose
/// `replyTo` matches; notifications carry id 0. Both directions may initiate,
/// which is what lets the gateway drive a transaction
/// (prepare -> detach -> commit / abort) instead of only answering polls.
///
/// The framing, authentication, heartbeat, correlation and dispatch live in the
/// host. Message *kinds* are not interpreted by the host at all beyond hello and
/// ping: a plugin registers the kinds it owns.
namespace crosslink::control {

using Json = nlohmann::ordered_json;

/// Reserved kinds handled by the host itself.
namespace kinds {
inline constexpr std::string_view hello        = "hello";
inline constexpr std::string_view helloAck     = "hello.ack";
inline constexpr std::string_view ping         = "ping";
inline constexpr std::string_view pong         = "pong";
inline constexpr std::string_view error        = "error";
inline constexpr std::string_view bye          = "bye";
} // namespace kinds

/// Wire envelope. `payload` is opaque to the host.
struct Message {
    std::uint64_t id{};
    std::uint64_t replyTo{};
    std::string   kind;
    Json          payload;

    [[nodiscard]] bool isRequest() const noexcept { return id != 0 && replyTo == 0; }
    [[nodiscard]] bool isReply() const noexcept { return replyTo != 0; }
    [[nodiscard]] bool isNotification() const noexcept { return id == 0 && replyTo == 0; }

    [[nodiscard]] Json    toJson() const;
    [[nodiscard]] static Result<Message> fromJson(Json const& json);
};

class CROSSLINK_API AgentChannel {
public:
    AgentChannel(AgentChannel const&)            = delete;
    AgentChannel& operator=(AgentChannel const&) = delete;
    virtual ~AgentChannel();

    [[nodiscard]] virtual AgentId     id() const      = 0;
    [[nodiscard]] virtual ServerId    server() const  = 0;
    [[nodiscard]] virtual std::string remote() const  = 0;
    [[nodiscard]] virtual bool        online() const  = 0;
    /// Whatever the agent reported in its hello, so a plugin can feature-detect.
    [[nodiscard]] virtual Json        capabilities() const = 0;

    [[nodiscard]] virtual Result<> notify(std::string_view kind, Json payload = {}) const = 0;

    /// Blocking request/reply. Only call this off the packet dispatch threads.
    [[nodiscard]] virtual Result<Json> request(
        std::string_view         kind,
        Json                     payload = {},
        std::chrono::milliseconds timeout = std::chrono::seconds(10)
    ) const = 0;

    using ResponseHandler = std::function<void(Result<Json>)>;
    [[nodiscard]] virtual Result<> requestAsync(
        std::string_view         kind,
        Json                     payload,
        ResponseHandler          handler,
        std::chrono::milliseconds timeout = std::chrono::seconds(10)
    ) const = 0;

    virtual void close(std::string_view reason) noexcept = 0;

protected:
    AgentChannel();
};

using AgentChannelPtr = std::shared_ptr<AgentChannel>;

class CROSSLINK_API AgentRegistry {
public:
    [[nodiscard]] static AgentRegistry& instance();

    [[nodiscard]] AgentChannelPtr                find(AgentId const& id) const;
    [[nodiscard]] AgentChannelPtr                forServer(ServerId const& server) const;
    [[nodiscard]] std::vector<AgentChannelPtr>   all() const;
    [[nodiscard]] std::size_t                    count() const;

    /// Handles inbound requests of one kind. The returned json becomes the reply
    /// payload; an error becomes an `error` reply. Later registrations of the same
    /// kind are consulted in ascending priority until one succeeds.
    using RequestHandler = std::function<Result<Json>(AgentChannel& agent, Json const& payload)>;

    std::uint64_t subscribe(
        std::string_view                    kind,
        RequestHandler                      handler,
        int                                 priority = 0,
        std::weak_ptr<plugin::Plugin>       owner    = {}
    );
    bool          unsubscribe(std::uint64_t subscription) noexcept;
    std::size_t   unsubscribeAll(std::weak_ptr<plugin::Plugin> owner) noexcept;

    [[nodiscard]] bool         handles(std::string_view kind) const;
    [[nodiscard]] Result<Json> dispatch(std::string_view kind, AgentChannel& agent, Json const& payload);

    /// Host-only: registers a channel that just finished its hello handshake.
    void attach(AgentChannelPtr channel);
    /// Host-only: forgets a channel whose connection went away.
    void detach(ServerId const& server);

private:
    AgentRegistry();
    ~AgentRegistry();

    struct Impl;
    std::unique_ptr<Impl> mImpl;
};

} // namespace crosslink::control
