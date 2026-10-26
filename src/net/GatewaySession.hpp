#pragma once

#include "crosslink/api/net/Session.hpp"

#include <condition_variable>
#include <deque>
#include <functional>
#include <map>
#include <mutex>
#include <string>
#include <vector>

namespace crosslink {

class Gateway;

namespace net {

/// The concrete session the gateway runs for one player.
///
/// Everything here is forwarding: terminate the two encryption handshakes, keep
/// the legs' compression state straight, run the pipeline, and move bytes to the
/// other side. What a handoff *means* is decided by plugins through the pipeline
/// and the events this class emits.
class GatewaySession final : public PlayerSession {
public:
    GatewaySession(Gateway& gateway, SessionId id, ConnectionPtr client, std::size_t maxDeferredPackets);
    ~GatewaySession() override;

    // ---- PlayerSession ------------------------------------------------
    [[nodiscard]] SessionId             id() const noexcept override { return mId; }
    [[nodiscard]] PlayerIdentity const& identity() const override;
    void                                setIdentity(PlayerIdentity identity) override;
    [[nodiscard]] std::string           identityKey() const override;

    [[nodiscard]] ServerId                     currentServer() const override;
    [[nodiscard]] ConnectionPtr                client() const override;
    [[nodiscard]] ConnectionPtr                backend() const override;
    [[nodiscard]] std::vector<ConnectionPtr>   backends() const override;

    [[nodiscard]] Pipeline& pipeline() override;
    [[nodiscard]] Gateway&  gateway() override;

    [[nodiscard]] proto::crypto::KeyPair const& gatewayKeyPair() const override;
    [[nodiscard]] std::string const&     clientPublicKey() const override;
    void                                 setClientPublicKey(std::string pem) override;

    [[nodiscard]] Result<> terminateBackendHandshake(
        ConnectionPtr const& backend,
        std::string_view     serverToClientToken,
        bool                 issueFrontendHandshake
    ) override;

    [[nodiscard]] bool frontendReady() const noexcept override;

    [[nodiscard]] Result<ConnectionPtr> openBackend(ServerId const& server, AttachOptions const& options) override;
    void                                setCurrentBackend(ConnectionPtr const& backend) override;
    void                                closeBackend(ConnectionPtr const& backend) noexcept override;

    [[nodiscard]] Result<>    defer(Flow flow, Bytes packet) override;
    std::size_t             releaseDeferred(Flow flow) override;
    void                    clearDeferred(Flow flow) noexcept override;
    [[nodiscard]] std::size_t deferredCount(Flow flow) const noexcept override;

    [[nodiscard]] Result<> sendToClient(ByteSpan packet, bool immediate = false) override;
    [[nodiscard]] Result<> sendToBackend(ByteSpan packet, bool immediate = false) override;
    // Un-hide the Packet& overloads the base provides.
    using PlayerSession::sendToClient;
    using PlayerSession::sendToBackend;

    void disconnectClient(std::string_view reason) noexcept override;

    [[nodiscard]] std::shared_ptr<void> state(std::string_view key) const override;
    void                                setState(std::string_view key, std::shared_ptr<void> value) override;
    void                                eraseState(std::string_view key) override;

    // ---- transport callbacks, invoked by the router --------------------
    void handleClientPacket(Bytes& packet);
    void handleClientClosed(std::string reason);
    void handleBackendConnected(ConnectionPtr const& backend, ServerId const& server);
    void handleBackendPacket(ConnectionPtr const& backend, ServerId const& server, Bytes& packet);
    void handleBackendClosed(ConnectionPtr const& backend, ServerId const& server, std::string reason);

    [[nodiscard]] bool closed() const noexcept;

private:
    struct BackendLeg {
        ConnectionPtr connection;
        ServerId      server;
        bool          connected{};
        bool          failed{};
    };

    void routePacket(
        Flow flow,
        proto::PacketPtr packet,
        ServerId const& server,
        bool currentBackend,
        bool allowForward = true
    );
    void handleLoginOutbound(proto::Packet& packet, ServerId const& server);
    bool handleBackendNetworkSettings(ConnectionPtr const& backend, proto::Packet& packet);
    void emitClosed(std::string reason);
    BackendLeg* legFor(ConnectionPtr const& connection);

    Gateway&                       mGateway;
    SessionId                      mId;
    ConnectionPtr                  mClient;
    mutable std::recursive_mutex   mMutex;
    std::condition_variable_any    mCondition;
    std::vector<BackendLeg>        mBackends;
    ConnectionPtr                  mCurrent;
    ServerId                       mCurrentServer;
    Pipeline                       mPipeline;
    PlayerIdentity                 mIdentity;
    std::deque<Bytes>              mDeferredToClient;
    std::deque<Bytes>              mDeferredToBackend;
    std::size_t                    mMaxDeferred;
    std::map<std::string, std::shared_ptr<void>> mState;
    proto::crypto::KeyPair                mKeyPair;
    std::string                    mClientPublicKey;
    bool                           mFrontendReady{};
    bool                           mFrontendEncrypted{};
    bool                           mClosed{};
};

/// Owns the client listener and the set of live sessions.
class SessionRouter {
public:
    explicit SessionRouter(Gateway& gateway);
    ~SessionRouter();

    [[nodiscard]] Result<> start();
    void                   stop() noexcept;

    [[nodiscard]] std::size_t sessionCount() const noexcept;

private:
    void onClientConnected(ConnectionPtr const& client);
    void onClientPacket(ConnectionPtr const& client, Bytes& packet);
    void onClientDisconnected(ConnectionPtr const& client);

    Gateway&                                        mGateway;
    std::unique_ptr<InboundListener>                mListener;
    mutable std::recursive_mutex                    mMutex;
    std::map<std::string, std::shared_ptr<GatewaySession>> mSessions;
    std::uint64_t                                   mNextId{1};
};

} // namespace net
} // namespace crosslink
