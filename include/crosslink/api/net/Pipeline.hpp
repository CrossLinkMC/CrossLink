#pragma once

#include "crosslink/api/Export.hpp"
#include "crosslink/api/Result.hpp"
#include "crosslink/api/Types.hpp"
#include "crosslink/api/proto/Packet.hpp"

#include <cstdint>
#include <memory>
#include <optional>
#include <string_view>

namespace crosslink::plugin {
class Plugin;
}

namespace crosslink::net {

class PlayerSession;

/// Which leg a packet is travelling on.
enum class Flow : std::uint8_t {
    /// Backend server -> gateway -> game client.
    ToClient = 0,
    /// Game client -> gateway -> backend server.
    ToBackend = 1,
};

[[nodiscard]] CROSSLINK_API std::string_view flowName(Flow flow) noexcept;

enum class Verdict : std::uint8_t {
    /// Keep going: next interceptor, then the destination leg.
    Forward = 0,
    /// Discard the packet.
    Drop = 1,
    /// Park it in the session's deferred queue; `PlayerSession::releaseDeferred`
    /// flushes it later. This is how a handoff holds back the outgoing server's
    /// world updates until the client has accepted the new one.
    Defer = 2,
    /// The interceptor already produced whatever had to be sent.
    Consumed = 3,
};

/// What an interceptor sees. The packet is mutable: rewrite it in place, replace
/// its bytes, or emit extra packets on either leg.
class CROSSLINK_API PacketContext {
public:
    PacketContext(PacketContext const&)            = delete;
    PacketContext& operator=(PacketContext const&) = delete;
    ~PacketContext();

    [[nodiscard]] PlayerSession&       session() const noexcept;
    [[nodiscard]] Flow                 flow() const noexcept;
    [[nodiscard]] proto::Packet&       packet() const noexcept;
    [[nodiscard]] proto::PacketId      id() const noexcept;
    /// Server the packet came from / is going to.
    [[nodiscard]] ServerId const&      server() const noexcept;
    /// False when the packet arrived on a backend leg that is not the session's
    /// current one (a prewarming target, for example). The pipeline still sees it,
    /// but the default routing decision is to drop it.
    [[nodiscard]] bool                 isCurrentBackend() const noexcept;

    [[nodiscard]] Result<> sendToClient(ByteSpan packet, bool immediate = false);
    [[nodiscard]] Result<> sendToBackend(ByteSpan packet, bool immediate = false);
    [[nodiscard]] Result<> sendToClient(proto::Packet& packet, bool immediate = false);
    [[nodiscard]] Result<> sendToBackend(proto::Packet& packet, bool immediate = false);

    void drop() noexcept;
    void defer() noexcept;
    void consume() noexcept;
    [[nodiscard]] Verdict verdict() const noexcept;

    /// Only a session builds a context. The constructor is public because
    /// friendship would not reach a session's implementation class; plugins get
    /// their context handed to them and never build one.
    PacketContext(PlayerSession& session, Flow flow, proto::Packet& packet, ServerId server, bool currentBackend);

private:
    struct Impl;
    std::unique_ptr<Impl> mImpl;
};

class CROSSLINK_API PacketInterceptor {
public:
    PacketInterceptor(PacketInterceptor const&)            = delete;
    PacketInterceptor& operator=(PacketInterceptor const&) = delete;
    virtual ~PacketInterceptor() = default;

    [[nodiscard]] virtual Verdict          onPacket(PacketContext& context) = 0;
    [[nodiscard]] virtual std::string_view name() const noexcept { return "interceptor"; }

protected:
    PacketInterceptor() = default;
};

struct InterceptorHandle {
    std::uint64_t id{};

    [[nodiscard]] explicit operator bool() const noexcept { return id != 0; }
    [[nodiscard]] auto     operator<=>(InterceptorHandle const&) const = default;
};

/// Ordered interceptor chain of one session. Interceptors are keyed by flow and
/// optionally by packet id, run in ascending priority, and are owned by the
/// plugin that registered them: when that plugin unloads, its interceptors go
/// with it.
class CROSSLINK_API Pipeline {
public:
    /// Only a session owns a pipeline; the constructor is public because the
    /// session implementation lives outside this header.
    Pipeline();
    Pipeline(Pipeline const&)            = delete;
    Pipeline& operator=(Pipeline const&) = delete;
    ~Pipeline();

    InterceptorHandle add(
        Flow                                      flow,
        std::optional<proto::PacketId>            id,
        int                                       priority,
        std::shared_ptr<PacketInterceptor>        interceptor,
        std::weak_ptr<plugin::Plugin>             owner = {}
    );
    bool        remove(InterceptorHandle handle);
    std::size_t removeAll(std::weak_ptr<plugin::Plugin> owner);
    void        clear() noexcept;
    [[nodiscard]] std::size_t size() const noexcept;

    /// Runs the chain. Called by the session, not by plugins.
    [[nodiscard]] Verdict dispatch(PacketContext& context);

private:
    struct Impl;
    std::unique_ptr<Impl> mImpl;
};

} // namespace crosslink::net
