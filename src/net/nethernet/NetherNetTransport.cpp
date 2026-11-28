#include "net/nethernet/NetherNetTransport.hpp"

#include "crosslink/api/Logger.hpp"
#include "proto/Jose.hpp"

#include <format>
#include <utility>

namespace jose = crosslink::proto::jose;

namespace crosslink::net::nethernet {
namespace {

/// The session outlives the connection object in callbacks, so hooks reach the
/// connection through a slot that is filled in once it exists. Holding a weak
/// pointer keeps the session -> connection -> session cycle from leaking.
using ConnectionSlot = std::shared_ptr<std::weak_ptr<NetherNetConnection>>;

[[nodiscard]] NetherNetSession::Hooks forwardHooks(ConnectionSlot slot, std::shared_ptr<ConnectionHooks> hooks) {
    NetherNetSession::Hooks forwarded;
    forwarded.onOpen = [slot, hooks] {
        const auto connection = slot->lock();
        if (connection && hooks->onConnected) hooks->onConnected(connection);
    };
    forwarded.onPacket = [slot, hooks](Bytes& packet) {
        const auto connection = slot->lock();
        if (connection && hooks->onPacket) hooks->onPacket(connection, packet);
    };
    forwarded.onClosed = [slot, hooks](std::string reason) {
        const auto connection = slot->lock();
        if (connection && hooks->onDisconnected) hooks->onDisconnected(connection);
    };
    return forwarded;
}

[[nodiscard]] std::string randomNetworkId() {
    auto bytes = jose::randomBytes(8);
    if (!bytes) return "1";
    std::uint64_t value = 0;
    for (std::size_t index = 0; index < 8; ++index) {
        value |= static_cast<std::uint64_t>(static_cast<unsigned char>((*bytes)[index])) << (8U * index);
    }
    return std::to_string(value);
}

} // namespace

// ---- NetherNetConnection ----------------------------------------------

NetherNetConnection::NetherNetConnection(std::string label, std::shared_ptr<NetherNetSession> session)
: mLabel(std::move(label)), mSession(std::move(session)) {}

NetherNetConnection::~NetherNetConnection() {
    if (mSession) mSession->close();
    if (mDial.joinable()) mDial.join();
}

void NetherNetConnection::startDial(std::function<void()> dial) {
    mDial = std::thread{[dial = std::move(dial)] { dial(); }};
}

bool NetherNetConnection::connected() const noexcept { return mSession && mSession->open(); }

Endpoint NetherNetConnection::remote() const noexcept { return mSession ? mSession->remote() : Endpoint{}; }

Result<> NetherNetConnection::send(ByteSpan packet, bool immediate) {
    if (!mSession) return std::unexpected(Error{std::format("'{}' has no session", mLabel)});
    return mSession->send(packet, immediate);
}

void NetherNetConnection::setCompression(Compression algorithm, std::int32_t threshold) {
    if (mSession) mSession->setCompression(algorithm, threshold);
}

bool NetherNetConnection::encrypted() const noexcept { return mSession && mSession->encrypted(); }

Result<> NetherNetConnection::setEncryption(Bytes sessionKey) {
    if (!mSession) return std::unexpected(Error{std::format("'{}' has no session", mLabel)});
    return mSession->enableEncryption(sessionKey);
}

void NetherNetConnection::close() noexcept {
    if (mSession) mSession->close();
}

// ---- NetherNetListener ------------------------------------------------

NetherNetListener::NetherNetListener(
    ListenerConfig          config,
    ConnectionHooks         hooks,
    config::NetherNetConfig settings,
    std::uint32_t           protocolVersion,
    std::string             gameVersion
)
: mConfig(std::move(config))
, mHooks(std::move(hooks))
, mSettings(std::move(settings))
, mProtocolVersion(protocolVersion)
, mGameVersion(std::move(gameVersion)) {}

NetherNetListener::~NetherNetListener() { stop(); }

ServerPing NetherNetListener::ping(std::optional<std::uint32_t> protocol) const {
    ServerPing result;
    result.name = mConfig.motd;
    result.protocol = protocol && *protocol == mProtocolVersion ? *protocol : mProtocolVersion;
    result.version = mGameVersion;
    result.level = mSettings.levelName;
    result.players = static_cast<std::uint32_t>(connectionCount());
    result.maxPlayers = mConfig.maxConnections;
    result.gameType = mSettings.gameType;
    return result;
}

Result<> NetherNetListener::start() {
    if (mStarted) return std::unexpected(Error{"the listener is already running"});

    CROSSLINK_ASSIGN(identity, IdentityKey::loadOrCreate(mSettings.identityKeyFile));
    mIdentity = std::make_shared<IdentityKey>(std::move(*identity));

    SignalingHooks signaling;
    signaling.onPing = [this](std::optional<std::uint32_t> protocol, std::string_view) { return ping(protocol); };
    signaling.onJoin = [this](JoinRequest const& request, JoinResponse response) { onJoin(request, std::move(response)); };

    SignalingLimits limits;
    limits.maxRequestBytes = 65536;

    mSignaling = std::make_unique<SignalingServer>(
        mConfig.host,
        mConfig.port,
        std::move(signaling),
        limits,
        TlsConfig{.certificateChainFile = mSettings.tlsCertificate, .privateKeyFile = mSettings.tlsPrivateKey}
    );
    CROSSLINK_PROPAGATE(mSignaling->start());
    mStarted = true;
    logger("nethernet").info("listening on {}:{} (nethernet)", mConfig.host, mSignaling->port());
    return {};
}

void NetherNetListener::stop() noexcept {
    if (!mStarted) return;
    mStarted = false;
    if (mSignaling) mSignaling->stop();
    std::unordered_map<std::uint64_t, ConnectionPtr> connections;
    {
        std::lock_guard lock{mMutex};
        connections.swap(mConnections);
    }
    for (auto const& [id, connection] : connections) connection->close();
}

std::size_t NetherNetListener::connectionCount() const noexcept {
    std::lock_guard lock{mMutex};
    return mConnections.size();
}

void NetherNetListener::onJoin(JoinRequest const& request, JoinResponse response) {
    if (connectionCount() >= mConfig.maxConnections) {
        response.reject(SessionError::IncomingConnectionIgnored);
        return;
    }

    // A client's identity binds its DTLS certificate to its login key. The gateway
    // re-signs logins for backends, so it checks structure and reports, not trust.
    if (auto verified = verifyAssertion(request.offer); !verified) {
        logger("nethernet").warn(
            "join from {} (networkId {}): {}",
            request.remoteAddress,
            request.networkId,
            verified.error().message
        );
    }

    std::uint64_t id = 0;
    {
        std::lock_guard lock{mMutex};
        id = mNextId++;
    }

    auto slot = std::make_shared<std::weak_ptr<NetherNetConnection>>();
    auto hooks = std::make_shared<ConnectionHooks>(mHooks);
    auto forwarded = forwardHooks(slot, hooks);
    forwarded.onClosed = [this, slot, hooks, id](std::string reason) {
        ConnectionPtr connection;
        {
            std::lock_guard lock{mMutex};
            const auto found = mConnections.find(id);
            if (found != mConnections.end()) {
                connection = found->second;
                mConnections.erase(found);
            }
        }
        if (!connection) connection = slot->lock();
        if (connection && hooks->onDisconnected) hooks->onDisconnected(connection);
    };

    NetherNetSession::Config config;
    config.bindAddress = mSettings.iceBindAddress;
    config.portRangeBegin = mSettings.icePortBegin;
    config.portRangeEnd = mSettings.icePortEnd;
    config.maxSegmentBytes = mSettings.maxSegmentBytes;
    config.maxPacketBytes = mConfig.maxPacketBytes;
    config.identity = mIdentity;
    config.iceServers = mSettings.iceServers;

    auto session = NetherNetSession::create(config, std::move(forwarded), NetherNetSession::Role::Answerer);
    if (!session) {
        logger("nethernet").error("cannot answer a join from {}: {}", request.remoteAddress, session.error().message);
        response.reject(SessionError::FailedToCreatePeerConnection);
        return;
    }

    auto connection = std::make_shared<NetherNetConnection>(
        std::format("client:{}", request.remoteAddress),
        *session
    );
    *slot = connection;
    {
        std::lock_guard lock{mMutex};
        mConnections[id] = connection;
    }

    auto answer = (*session)->acceptOffer(request.offer);
    if (!answer) {
        logger("nethernet").error("cannot answer a join from {}: {}", request.remoteAddress, answer.error().message);
        {
            std::lock_guard lock{mMutex};
            mConnections.erase(id);
        }
        (*session)->close();
        response.reject(SessionError::FailedToSetRemoteDescription);
        return;
    }
    response.answer(std::move(*answer));
}

// ---- NetherNetTransport -----------------------------------------------

NetherNetTransport::NetherNetTransport(
    std::uint32_t           protocolVersion,
    std::string             gameVersion,
    config::NetherNetConfig settings
)
: mSettings(std::move(settings)) {
    mInfo.name = "bedrock-nethernet";
    mInfo.protocolVersion = protocolVersion;
    mInfo.gameVersion = std::move(gameVersion);
    mInfo.supportsEncryption = true;
    mInfo.supportsCompression = true;
    mInfo.supportsTermination = true;
    // DTLS protects the wire, but BDS still runs Bedrock's own batch encryption
    // handshake on top of it, so the gateway terminates that as usual.
    mInfo.transportEncrypted = false;
}

ProtocolInfo NetherNetTransport::info() const noexcept { return mInfo; }

NetherNetSession::Config NetherNetTransport::sessionConfig() const {
    NetherNetSession::Config config;
    config.bindAddress = mSettings.iceBindAddress;
    config.portRangeBegin = mSettings.icePortBegin;
    config.portRangeEnd = mSettings.icePortEnd;
    config.maxSegmentBytes = mSettings.maxSegmentBytes;
    config.identity = mIdentity;
    config.iceServers = mSettings.iceServers;
    return config;
}

Result<std::unique_ptr<InboundListener>> NetherNetTransport::listen(ListenerConfig const& config, ConnectionHooks hooks) {
    return std::unique_ptr<InboundListener>{std::make_unique<NetherNetListener>(
        config,
        std::move(hooks),
        mSettings,
        mInfo.protocolVersion,
        mInfo.gameVersion
    )};
}

Result<std::shared_ptr<IdentityKey>> NetherNetTransport::ensureIdentity() const {
    std::lock_guard lock{mIdentityMutex};
    if (!mIdentity) {
        CROSSLINK_ASSIGN(loaded, IdentityKey::loadOrCreate(mSettings.identityKeyFile));
        mIdentity = std::make_shared<IdentityKey>(std::move(*loaded));
    }
    return mIdentity;
}

std::optional<proto::crypto::KeyPair> NetherNetTransport::identityKeyPair() const {
    auto identity = ensureIdentity();
    if (!identity) {
        logger("nethernet").error("cannot load the identity key: {}", identity.error().message);
        return std::nullopt;
    }
    return (*identity)->keyPair();
}

Result<ConnectionPtr> NetherNetTransport::connect(Endpoint const& endpoint, ConnectionHooks hooks) {
    CROSSLINK_ASSIGN(identity, ensureIdentity());

    auto slot = std::make_shared<std::weak_ptr<NetherNetConnection>>();
    auto stored = std::make_shared<ConnectionHooks>(std::move(hooks));
    auto config = sessionConfig();
    config.identity = *identity;
    auto session = NetherNetSession::create(config, forwardHooks(slot, stored), NetherNetSession::Role::Dialer);
    if (!session) return std::unexpected(session.error());

    auto connection = std::make_shared<NetherNetConnection>(std::format("backend:{}", endpoint.toString()), *session);
    *slot = connection;

    const std::string networkId = randomNetworkId();
    const std::string host = endpoint.host;
    const std::uint16_t port = endpoint.port;
    auto dialSession = *session;

    connection->startDial([slot, stored, dialSession, host, port, networkId] {
        const auto fail = [&](std::string message) {
            logger("nethernet").error("cannot dial {}:{}: {}", host, port, message);
            dialSession->close();
            if (const auto connection = slot->lock(); connection && stored->onDisconnected) {
                stored->onDisconnected(connection);
            }
        };

        auto offer = dialSession->createOffer();
        if (!offer) {
            fail(offer.error().message);
            return;
        }
        auto answer = SignalingClient::requestAnswer(host, port, networkId, *offer);
        if (!answer) {
            fail(answer.error().message);
            return;
        }
        if (auto applied = dialSession->acceptAnswer(*answer); !applied) {
            fail(applied.error().message);
            return;
        }
    });

    return ConnectionPtr{std::move(connection)};
}

} // namespace crosslink::net::nethernet