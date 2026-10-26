#pragma once

#include "crosslink/api/Export.hpp"
#include "crosslink/api/Result.hpp"
#include "crosslink/api/Types.hpp"
#include "crosslink/api/net/Pipeline.hpp"
#include "crosslink/api/net/Transport.hpp"
#include "crosslink/api/proto/Crypto.hpp"

#include <chrono>
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

namespace crosslink {

class Gateway;

namespace net {

struct AttachOptions {
    /// Register the leg as the session's current backend, so its packets are
    /// routed to the client. Leave false to prewarm a target while the player is
    /// still served by the old backend.
    bool makeCurrent{true};
    /// Close the previous current backend once the new one is registered.
    bool closePrevious{true};
    std::chrono::milliseconds connectTimeout{std::chrono::seconds(15)};
    /// Block until the leg connects or the timeout expires. Only safe off the
    /// packet dispatch threads (the control channel worker qualifies).
    bool waitForConnection{false};
};

/// One player: the leg facing the game client, the leg facing the backend server
/// the player is currently on, and the pipeline in between.
///
/// The session is a forwarding primitive. It has no idea what a handoff is; a
/// plugin drives it by opening backends, installing interceptors, and deferring
/// or rewriting packets.
class CROSSLINK_API PlayerSession : public std::enable_shared_from_this<PlayerSession> {
public:
    PlayerSession(PlayerSession const&)            = delete;
    PlayerSession& operator=(PlayerSession const&) = delete;
    virtual ~PlayerSession();

    [[nodiscard]] virtual SessionId           id() const noexcept = 0;
    [[nodiscard]] virtual PlayerIdentity const& identity() const   = 0;
    virtual void                              setIdentity(PlayerIdentity identity) = 0;
    /// Convenience: xuid, else offline identity, else name.
    [[nodiscard]] virtual std::string         identityKey() const = 0;

    [[nodiscard]] virtual ServerId        currentServer() const = 0;
    [[nodiscard]] virtual ConnectionPtr   client() const        = 0;
    /// Current backend leg, or nullptr while detached.
    [[nodiscard]] virtual ConnectionPtr   backend() const       = 0;
    /// Every open backend leg, including prewarming ones.
    [[nodiscard]] virtual std::vector<ConnectionPtr> backends() const = 0;

    [[nodiscard]] virtual Pipeline& pipeline() = 0;
    [[nodiscard]] virtual Gateway&  gateway()  = 0;

    /// The key pair this gateway uses for the player's encryption handshakes.
    /// Every leg terminates its own handshake with it, so a session key derived
    /// for one leg is never valid on another.
    [[nodiscard]] virtual proto::crypto::KeyPair const& gatewayKeyPair() const             = 0;
    [[nodiscard]] virtual std::string const&     clientPublicKey() const             = 0;
    virtual void                                 setClientPublicKey(std::string pem)  = 0;

    /// Terminates a backend's ServerToClientHandshake: verifies the token,
    /// derives and applies the backend session key, and acknowledges it.
    /// `issueFrontendHandshake` also encrypts the client leg, which only the very
    /// first login may do.
    [[nodiscard]] virtual Result<> terminateBackendHandshake(
        ConnectionPtr const& backend,
        std::string_view     serverToClientToken,
        bool                 issueFrontendHandshake
    ) = 0;

    /// True once the client leg negotiated compression, i.e. after the first
    /// NetworkSettings was relayed.
    [[nodiscard]] virtual bool frontendReady() const noexcept = 0;

    /// Opens a leg to `server`. With `makeCurrent` the session starts routing the
    /// client's packets to it; without, the leg only feeds the pipeline so a
    /// plugin can watch the target's login sequence before committing.
    [[nodiscard]] virtual Result<ConnectionPtr> openBackend(ServerId const& server, AttachOptions const& options = {}) = 0;
    virtual void                                setCurrentBackend(ConnectionPtr const& backend)                        = 0;
    virtual void                                closeBackend(ConnectionPtr const& backend) noexcept                    = 0;

    /// Deferred queues, one per flow. Interceptors return Verdict::Defer to park
    /// a packet here; the plugin decides when it is safe to let them through.
    [[nodiscard]] virtual Result<> defer(Flow flow, Bytes packet)      = 0;
    virtual std::size_t            releaseDeferred(Flow flow)          = 0;
    virtual void                   clearDeferred(Flow flow) noexcept   = 0;
    [[nodiscard]] virtual std::size_t deferredCount(Flow flow) const noexcept = 0;

    [[nodiscard]] virtual Result<> sendToClient(ByteSpan packet, bool immediate = false)  = 0;
    [[nodiscard]] virtual Result<> sendToBackend(ByteSpan packet, bool immediate = false) = 0;
    [[nodiscard]] Result<>         sendToClient(proto::Packet& packet, bool immediate = false);
    [[nodiscard]] Result<>         sendToBackend(proto::Packet& packet, bool immediate = false);

    virtual void disconnectClient(std::string_view reason) noexcept = 0;

    /// Per-plugin scratch space that dies with the session.
    [[nodiscard]] virtual std::shared_ptr<void> state(std::string_view key) const          = 0;
    virtual void                                setState(std::string_view key, std::shared_ptr<void> value) = 0;
    virtual void                                eraseState(std::string_view key)                            = 0;

    template <typename T>
    [[nodiscard]] std::shared_ptr<T> typedState(std::string_view key) const {
        return std::static_pointer_cast<T>(state(key));
    }

    template <typename T, typename... Args>
    std::shared_ptr<T> emplaceState(std::string_view key, Args&&... args) {
        auto value = std::make_shared<T>(std::forward<Args>(args)...);
        setState(key, value);
        return value;
    }

protected:
    PlayerSession();
};

using PlayerSessionPtr = std::shared_ptr<PlayerSession>;

/// All live sessions, addressable by session id, identity key or name.
class CROSSLINK_API SessionRegistry {
public:
    [[nodiscard]] static SessionRegistry& instance();

    void             track(PlayerSessionPtr const& session);
    void             untrack(SessionId const& id);
    [[nodiscard]] PlayerSessionPtr              find(SessionId const& id) const;
    [[nodiscard]] PlayerSessionPtr              findByIdentity(std::string_view identityKey) const;
    [[nodiscard]] PlayerSessionPtr              findByName(std::string_view name) const;
    [[nodiscard]] std::vector<PlayerSessionPtr> all() const;
    [[nodiscard]] std::size_t                   count() const;

private:
    SessionRegistry();
    ~SessionRegistry();

    struct Impl;
    std::unique_ptr<Impl> mImpl;
};

} // namespace net
} // namespace crosslink
