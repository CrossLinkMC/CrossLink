#pragma once

// The `bedrock-nethernet` transport: Minecraft Bedrock from 26.60 onwards. The
// frontend answers a client's HTTP join, the backend dials one. Everything above
// the Transport interface is unchanged from the RakNet days.

#include "crosslink/api/Config.hpp"
#include "crosslink/api/net/Transport.hpp"
#include "net/nethernet/NetherNetSession.hpp"
#include "net/nethernet/Signaling.hpp"

#include <cstdint>
#include <functional>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>

namespace crosslink::net::nethernet {

class NetherNetConnection final : public Connection {
public:
    NetherNetConnection(std::string label, std::shared_ptr<NetherNetSession> session);
    ~NetherNetConnection() override;

    [[nodiscard]] std::string_view label() const noexcept override { return mLabel; }
    [[nodiscard]] bool             connected() const noexcept override;
    [[nodiscard]] Endpoint         remote() const noexcept override;

    [[nodiscard]] Result<> send(ByteSpan packet, bool immediate) override;
    void                   setCompression(Compression algorithm, std::int32_t threshold) override;
    [[nodiscard]] Result<> setEncryption(Bytes sessionKey) override;
    [[nodiscard]] bool     encrypted() const noexcept override;
    void                   close() noexcept override;

    [[nodiscard]] std::shared_ptr<NetherNetSession> session() const noexcept { return mSession; }

    void startDial(std::function<void()> dial);

private:
    std::string                      mLabel;
    std::shared_ptr<NetherNetSession> mSession;
    std::thread                      mDial;
};

class NetherNetListener final : public InboundListener {
public:
    NetherNetListener(ListenerConfig config, ConnectionHooks hooks, config::NetherNetConfig settings, std::uint32_t protocolVersion, std::string gameVersion);
    ~NetherNetListener() override;

    [[nodiscard]] Result<>    start() override;
    void                      stop() noexcept override;
    [[nodiscard]] std::size_t connectionCount() const noexcept override;

private:
    void onJoin(JoinRequest const& request, JoinResponse response);
    [[nodiscard]] ServerPing ping(std::optional<std::uint32_t> protocol) const;

    ListenerConfig             mConfig;
    ConnectionHooks            mHooks;
    config::NetherNetConfig    mSettings;
    std::uint32_t              mProtocolVersion;
    std::string                mGameVersion;
    std::shared_ptr<IdentityKey> mIdentity;
    std::unique_ptr<SignalingServer> mSignaling;

    mutable std::mutex                            mMutex;
    std::unordered_map<std::uint64_t, ConnectionPtr> mConnections;
    std::uint64_t                                 mNextId{1};
    bool                                          mStarted{};
};

class NetherNetTransport final : public Transport {
public:
    NetherNetTransport(std::uint32_t protocolVersion, std::string gameVersion, config::NetherNetConfig settings);

    [[nodiscard]] ProtocolInfo                           info() const noexcept override;
    [[nodiscard]] Result<std::unique_ptr<InboundListener>> listen(ListenerConfig const& config, ConnectionHooks hooks) override;
    [[nodiscard]] Result<ConnectionPtr>                    connect(Endpoint const& endpoint, ConnectionHooks hooks) override;
    [[nodiscard]] std::optional<proto::crypto::KeyPair>    identityKeyPair() const override;

private:
    [[nodiscard]] NetherNetSession::Config sessionConfig() const;
    [[nodiscard]] Result<std::shared_ptr<IdentityKey>> ensureIdentity() const;

    ProtocolInfo          mInfo;
    config::NetherNetConfig mSettings;
    mutable std::mutex    mIdentityMutex;
    mutable std::shared_ptr<IdentityKey> mIdentity;
};

} // namespace crosslink::net::nethernet