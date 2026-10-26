#include "net/GatewaySession.hpp"

#include "crosslink/api/Events.hpp"
#include "crosslink/api/Gateway.hpp"
#include "crosslink/api/net/ServerRegistry.hpp"
#include "crosslink/api/proto/Crypto.hpp"
#include "crosslink/api/proto/packets/AllPackets.hpp"

#include <format>
#include <utility>

namespace crosslink::net {
namespace {

proto::PacketId idOf(proto::Packet const& packet) noexcept { return packet.id(); }

} // namespace

GatewaySession::GatewaySession(Gateway& gateway, SessionId id, ConnectionPtr client, std::size_t maxDeferredPackets)
: mGateway(gateway), mId(std::move(id)), mClient(std::move(client)), mMaxDeferred(maxDeferredPackets) {
    if (auto keyPair = proto::crypto::generateKeyPair()) {
        mKeyPair = std::move(*keyPair);
    } else {
        gateway.logger().error("session {}: could not generate a gateway key pair: {}", mId.str(), keyPair.error().message);
    }
}

GatewaySession::~GatewaySession() = default;

// ---- identity ----------------------------------------------------------

PlayerIdentity const& GatewaySession::identity() const {
    std::lock_guard lock{mMutex};
    return mIdentity;
}

void GatewaySession::setIdentity(PlayerIdentity identity) {
    {
        std::lock_guard lock{mMutex};
        mIdentity = std::move(identity);
    }
}

std::string GatewaySession::identityKey() const {
    std::lock_guard lock{mMutex};
    return mIdentity.key();
}

// ---- legs --------------------------------------------------------------

ServerId GatewaySession::currentServer() const {
    std::lock_guard lock{mMutex};
    return mCurrentServer;
}

ConnectionPtr GatewaySession::client() const {
    std::lock_guard lock{mMutex};
    return mClient;
}

ConnectionPtr GatewaySession::backend() const {
    std::lock_guard lock{mMutex};
    return mCurrent;
}

std::vector<ConnectionPtr> GatewaySession::backends() const {
    std::lock_guard lock{mMutex};
    std::vector<ConnectionPtr> legs;
    legs.reserve(mBackends.size());
    for (auto const& leg : mBackends) legs.push_back(leg.connection);
    return legs;
}

Pipeline& GatewaySession::pipeline() { return mPipeline; }

Gateway& GatewaySession::gateway() { return mGateway; }

proto::crypto::KeyPair const& GatewaySession::gatewayKeyPair() const { return mKeyPair; }

std::string const& GatewaySession::clientPublicKey() const {
    std::lock_guard lock{mMutex};
    return mClientPublicKey;
}

void GatewaySession::setClientPublicKey(std::string pem) {
    std::lock_guard lock{mMutex};
    mClientPublicKey = std::move(pem);
}

bool GatewaySession::frontendReady() const noexcept { return mFrontendReady; }

bool GatewaySession::closed() const noexcept { return mClosed; }

GatewaySession::BackendLeg* GatewaySession::legFor(ConnectionPtr const& connection) {
    for (auto& leg : mBackends) {
        if (leg.connection == connection) return &leg;
    }
    return nullptr;
}

Result<ConnectionPtr> GatewaySession::openBackend(ServerId const& server, AttachOptions const& options) {
    const auto info = ServerRegistry::instance().find(server);
    if (!info) return std::unexpected(Error{std::format("unknown server '{}'", server.str())});

    const auto transport = TransportRegistry::instance().active();
    if (!transport) return std::unexpected(Error{"no transport is active"});

    std::weak_ptr<GatewaySession> self = std::static_pointer_cast<GatewaySession>(shared_from_this());
    const auto targetServer = server;

    ConnectionHooks hooks;
    hooks.onConnected = [self, targetServer](ConnectionPtr const& connection) {
        if (auto session = self.lock()) session->handleBackendConnected(connection, targetServer);
    };
    hooks.onPacket = [self, targetServer](ConnectionPtr const& connection, Bytes& packet) {
        if (auto session = self.lock()) session->handleBackendPacket(connection, targetServer, packet);
    };
    hooks.onDisconnected = [self, targetServer](ConnectionPtr const& connection) {
        if (auto session = self.lock()) session->handleBackendClosed(connection, targetServer, "disconnected");
    };
    hooks.onParseFailure = [self, targetServer](ConnectionPtr const&, proto::PacketId id, std::string_view message) {
        if (auto session = self.lock()) {
            session->mGateway.logger().warn(
                "session {}: parse failure from {}: {} ({})",
                session->mId.str(),
                targetServer.str(),
                proto::packetName(id),
                message
            );
        }
    };

    auto connection = transport->connect(info->gameEndpoint, std::move(hooks));
    if (!connection) return std::unexpected(connection.error());

    ConnectionPtr previous;
    {
        std::lock_guard lock{mMutex};
        mBackends.push_back(BackendLeg{*connection, server, false, false});
        if (options.makeCurrent) {
            previous = mCurrent;
            mCurrent = *connection;
            mCurrentServer = server;
        }
    }

    if (options.waitForConnection) {
        std::unique_lock lock{mMutex};
        const auto ready = mCondition.wait_for(lock, options.connectTimeout, [this, &connection] {
            const auto* leg = legFor(*connection);
            return leg == nullptr || leg->connected || leg->failed;
        });
        const auto* leg = legFor(*connection);
        if (!ready || leg == nullptr || leg->failed) {
            lock.unlock();
            closeBackend(*connection);
            return std::unexpected(
                Error{std::format("backend '{}' did not accept the connection within {} ms", server.str(), options.connectTimeout.count())}
            );
        }
    }

    if (options.makeCurrent && options.closePrevious && previous && previous != *connection) {
        mGateway.logger().debug("session {}: closing previous backend {}", mId.str(), previous->label());
        closeBackend(previous);
    }
    return *connection;
}

void GatewaySession::setCurrentBackend(ConnectionPtr const& backend) {
    ServerId previousServer;
    ServerId nextServer;
    {
        std::lock_guard lock{mMutex};
        if (mCurrent == backend) return;
        auto* leg = legFor(backend);
        if (leg == nullptr) {
            mGateway.logger().warn("session {}: refusing to make an unknown leg current", mId.str());
            return;
        }
        previousServer = mCurrentServer;
        mCurrent = backend;
        mCurrentServer = leg->server;
        nextServer = leg->server;
    }

    mGateway.logger().info("session {}: routing to backend '{}'", mId.str(), nextServer.str());
    BackendSwitchedEvent event;
    event.session = std::static_pointer_cast<PlayerSession>(shared_from_this());
    event.from = std::move(previousServer);
    event.to = std::move(nextServer);
    mGateway.events().emit(event);
}

void GatewaySession::closeBackend(ConnectionPtr const& backend) noexcept {
    if (!backend) return;
    ServerId server;
    {
        std::lock_guard lock{mMutex};
        auto* leg = legFor(backend);
        if (leg != nullptr) server = leg->server;
        if (mCurrent == backend) {
            mCurrent = nullptr;
            mCurrentServer = ServerId{};
        }
        std::erase_if(mBackends, [&backend](auto const& candidate) { return candidate.connection == backend; });
    }
    backend->close();
    mCondition.notify_all();

    if (!server.empty()) {
        BackendClosedEvent event;
        event.session = std::static_pointer_cast<PlayerSession>(shared_from_this());
        event.backend = backend;
        event.server = std::move(server);
        event.reason = "closed";
        mGateway.events().emit(event);
    }
}

// ---- deferred queues ---------------------------------------------------

Result<> GatewaySession::defer(Flow flow, Bytes packet) {
    std::lock_guard lock{mMutex};
    auto& queue = flow == Flow::ToClient ? mDeferredToClient : mDeferredToBackend;
    if (queue.size() >= mMaxDeferred) {
        return std::unexpected(Error{std::format("deferred queue for {} is full ({} packets)", flowName(flow), queue.size())});
    }
    queue.push_back(std::move(packet));
    return {};
}

std::size_t GatewaySession::releaseDeferred(Flow flow) {
    std::deque<Bytes> queued;
    {
        std::lock_guard lock{mMutex};
        auto& queue = flow == Flow::ToClient ? mDeferredToClient : mDeferredToBackend;
        queued.swap(queue);
    }
    for (auto& packet : queued) {
        if (flow == Flow::ToClient) {
            (void)sendToClient(ByteSpan{packet}, false);
        } else {
            (void)sendToBackend(ByteSpan{packet}, false);
        }
    }
    return queued.size();
}

void GatewaySession::clearDeferred(Flow flow) noexcept {
    std::lock_guard lock{mMutex};
    auto& queue = flow == Flow::ToClient ? mDeferredToClient : mDeferredToBackend;
    queue.clear();
}

std::size_t GatewaySession::deferredCount(Flow flow) const noexcept {
    std::lock_guard lock{mMutex};
    return flow == Flow::ToClient ? mDeferredToClient.size() : mDeferredToBackend.size();
}

// ---- sending -----------------------------------------------------------

Result<> GatewaySession::sendToClient(ByteSpan packet, bool immediate) {
    ConnectionPtr client;
    {
        std::lock_guard lock{mMutex};
        client = mClient;
    }
    if (!client || !client->connected()) return std::unexpected(Error{"the client is not connected"});
    return client->send(packet, immediate);
}

Result<> GatewaySession::sendToBackend(ByteSpan packet, bool immediate) {
    ConnectionPtr backend;
    {
        std::lock_guard lock{mMutex};
        backend = mCurrent;
    }
    if (!backend || !backend->connected()) return std::unexpected(Error{"no backend is attached"});
    return backend->send(packet, immediate);
}

void GatewaySession::disconnectClient(std::string_view reason) noexcept {
    ConnectionPtr client;
    {
        std::lock_guard lock{mMutex};
        client = mClient;
    }
    mGateway.logger().info("session {}: disconnecting client ({})", mId.str(), reason);
    if (client) client->close();
}

// ---- per-plugin state --------------------------------------------------

std::shared_ptr<void> GatewaySession::state(std::string_view key) const {
    std::lock_guard lock{mMutex};
    const auto found = mState.find(std::string{key});
    return found == mState.end() ? nullptr : found->second;
}

void GatewaySession::setState(std::string_view key, std::shared_ptr<void> value) {
    std::lock_guard lock{mMutex};
    if (!value) {
        mState.erase(std::string{key});
        return;
    }
    mState.insert_or_assign(std::string{key}, std::move(value));
}

void GatewaySession::eraseState(std::string_view key) {
    std::lock_guard lock{mMutex};
    mState.erase(std::string{key});
}

// ---- handshake termination ---------------------------------------------

Result<> GatewaySession::terminateBackendHandshake(
    ConnectionPtr const& backend,
    std::string_view     serverToClientToken,
    bool                 issueFrontendHandshake
) {
    if (!backend) return std::unexpected(Error{"no backend leg to terminate"});

    auto token = proto::crypto::parseHandshakeToken(serverToClientToken);
    if (!token) return std::unexpected(token.error());
    if (auto verified = proto::crypto::verifyHandshakeToken(*token); !verified) return verified;

    auto backendKey = proto::crypto::deriveSessionKey(mKeyPair.privateKeyPem, token->remotePublicKey, ByteSpan{token->salt});
    if (!backendKey) return std::unexpected(backendKey.error());

    Bytes frontendKey;
    proto::crypto::HandshakeToken frontendToken;
    if (issueFrontendHandshake) {
        std::string clientPublicKey;
        {
            std::lock_guard lock{mMutex};
            clientPublicKey = mClientPublicKey;
        }
        if (clientPublicKey.empty()) {
            return std::unexpected(Error{"the client public key is not known yet, cannot issue a frontend handshake"});
        }
        auto created = proto::crypto::createHandshakeToken(mKeyPair);
        if (!created) return std::unexpected(created.error());
        auto derived = proto::crypto::deriveSessionKey(mKeyPair.privateKeyPem, clientPublicKey, ByteSpan{created->salt});
        if (!derived) return std::unexpected(derived.error());
        frontendToken = std::move(*created);
        frontendKey = std::move(*derived);
    }

    // The client handshake has to go out in the pre-encryption framing, so it is
    // sent immediately and only then does the client leg switch to encryption.
    if (issueFrontendHandshake) {
        proto::ServerToClientHandshakePacket handshake{proto::PacketHeader{proto::PacketId::ServerToClientHandshake}};
        handshake.setToken(frontendToken.raw);
        if (auto sent = sendToClient(handshake, true); !sent) return sent;
        if (auto encrypted = mClient->setEncryption(std::move(frontendKey)); !encrypted) return encrypted;
        mFrontendEncrypted = true;
    }

    if (auto encrypted = backend->setEncryption(std::move(*backendKey)); !encrypted) return encrypted;

    proto::ClientToServerHandshakePacket acknowledgement{
        proto::PacketHeader{proto::PacketId::ClientToServerHandshake}
    };
    if (auto encoded = acknowledgement.encode(); !encoded) return encoded;
    return backend->send(ByteSpan{acknowledgement.bytes()}, true);
}

// ---- routing -----------------------------------------------------------

void GatewaySession::handleClientPacket(Bytes& raw) {
    if (mClosed) return;

    auto wrapped = mGateway.codecs().wrap(std::move(raw));
    if (!wrapped) {
        mGateway.logger().warn("session {}: cannot wrap a client packet: {}", mId.str(), wrapped.error().message);
        return;
    }
    auto& packet = **wrapped;

    switch (idOf(packet)) {
    case proto::PacketId::Login:
        handleLoginOutbound(packet, currentServer());
        break;
    case proto::PacketId::ClientToServerHandshake:
        // The client leg terminated its handshake with the gateway, not with a
        // backend; there is nothing to forward.
        return;
    default:
        break;
    }

    routePacket(Flow::ToBackend, std::move(*wrapped), currentServer(), true);
}

void GatewaySession::handleLoginOutbound(proto::Packet& packet, ServerId const& server) {
    auto* login = proto::asOrNull<proto::LoginPacket>(packet);
    if (login == nullptr) return;
    if (auto decoded = login->decode(); !decoded) {
        mGateway.logger().error("session {}: cannot decode Login: {}", mId.str(), decoded.error().message);
        return;
    }

    if (const auto view = login->inspect()) {
        setIdentity(view->toIdentity());
        setClientPublicKey(view->clientPublicKey);
        mGateway.logger().info(
            "session {}: login for '{}' (xuid={}, identity={})",
            mId.str(),
            view->name,
            view->xuid.empty() ? "-" : view->xuid,
            view->identity
        );

        IdentityResolvedEvent resolved;
        resolved.session = std::static_pointer_cast<PlayerSession>(shared_from_this());
        resolved.identity = identity();
        mGateway.events().emit(resolved);
    } else {
        mGateway.logger().warn("session {}: cannot inspect the connection request: {}", mId.str(), view.error().message);
    }

    // The gateway only knows how to re-sign; what has to be attached for a
    // trusted backend agent to recognise the identity is plugin policy.
    LoginOutboundEvent outbound{std::static_pointer_cast<PlayerSession>(shared_from_this()), server, *login};
    mGateway.events().emit(outbound);

    if (auto resigned = login->resign(mKeyPair, outbound.deviceIdOverride, outbound.deviceModelOverride); !resigned) {
        mGateway.logger().error("session {}: cannot re-sign Login for '{}': {}", mId.str(), server.str(), resigned.error().message);
    }
}

void GatewaySession::handleBackendPacket(ConnectionPtr const& backend, ServerId const& server, Bytes& raw) {
    if (mClosed) return;

    auto wrapped = mGateway.codecs().wrap(std::move(raw));
    if (!wrapped) {
        mGateway.logger().warn("session {}: cannot wrap a packet from '{}': {}", mId.str(), server.str(), wrapped.error().message);
        return;
    }
    auto& packet = **wrapped;

    const bool currentBackend = [&] {
        std::lock_guard lock{mMutex};
        return mCurrent == backend;
    }();

    if (idOf(packet) == proto::PacketId::ServerToClientHandshake) {
        auto* handshake = proto::asOrNull<proto::ServerToClientHandshakePacket>(packet);
        if (handshake == nullptr || !handshake->decode()) {
            mGateway.logger().error("session {}: cannot decode the handshake token from '{}'", mId.str(), server.str());
            return;
        }
        if (auto terminated = terminateBackendHandshake(backend, handshake->token(), !mFrontendEncrypted); !terminated) {
            mGateway.logger().error("session {}: handshake termination with '{}' failed: {}", mId.str(), server.str(), terminated.error().message);
            disconnectClient("encryption handshake failed");
        }
        return;
    }

    const bool networkSettings = idOf(packet) == proto::PacketId::NetworkSettings;
    const bool framingAlreadyNegotiated = mFrontendReady;
    if (networkSettings && handleBackendNetworkSettings(backend, packet)) return;

    // A second NetworkSettings must never reach the client: its framing is already
    // fixed. Plugins still see it, they just cannot forward it by default.
    routePacket(Flow::ToClient, std::move(*wrapped), server, currentBackend, !(networkSettings && framingAlreadyNegotiated));
}

bool GatewaySession::handleBackendNetworkSettings(ConnectionPtr const& backend, proto::Packet& packet) {
    auto* settings = proto::asOrNull<proto::NetworkSettingsPacket>(packet);
    if (settings == nullptr) return false;
    if (auto decoded = settings->decode(); !decoded) {
        mGateway.logger().warn("session {}: cannot decode NetworkSettings: {}", mId.str(), decoded.error().message);
        return false;
    }

    // Compression is per leg: whatever a backend announces applies to that leg
    // only, and never to the client leg mid-session.
    if (backend) backend->setCompression(settings->compressionAlgorithm(), settings->compressionThreshold());

    if (mFrontendReady) return false;

    // First login: the settings themselves still use the uncompressed framing, so
    // they go out immediately and only then does the client leg switch.
    if (auto sent = sendToClient(ByteSpan{packet.bytes()}, true); !sent) {
        mGateway.logger().error("session {}: cannot relay NetworkSettings to the client: {}", mId.str(), sent.error().message);
        return true;
    }
    if (mClient) mClient->setCompression(settings->compressionAlgorithm(), settings->compressionThreshold());
    mFrontendReady = true;
    mCondition.notify_all();
    return true;
}

void GatewaySession::routePacket(
    Flow flow,
    proto::PacketPtr packet,
    ServerId const& server,
    bool currentBackend,
    bool allowForward
) {
    if (!packet) return;

    PacketContext context{*static_cast<PlayerSession*>(this), flow, *packet, server, currentBackend};
    const auto verdict = mPipeline.dispatch(context);

    switch (verdict) {
    case Verdict::Forward:
        if (!allowForward) {
            mGateway.logger().debug(
                "session {}: not relaying {} to the client, the leg framing is already negotiated",
                mId.str(),
                packet->name()
            );
            return;
        }
        break;
    case Verdict::Drop:
        return;
    case Verdict::Defer:
        if (auto deferred = defer(flow, Bytes{packet->bytes()}); !deferred) {
            mGateway.logger().warn("session {}: {}", mId.str(), deferred.error().message);
        }
        return;
    case Verdict::Consumed:
        return;
    }

    if (flow == Flow::ToClient) {
        // Only the current backend may drive the client; a prewarming leg stays
        // silent unless a plugin explicitly sent something itself.
        if (!currentBackend) return;
        if (auto sent = sendToClient(*packet, false); !sent) {
            mGateway.logger().debug(
                "session {}: cannot forward {} to the client: {}",
                mId.str(),
                packet->name(),
                sent.error().message
            );
        }
        return;
    }

    if (!currentBackend) return;
    if (auto sent = sendToBackend(*packet, false); !sent) {
        mGateway.logger().debug(
            "session {}: cannot forward {} to '{}': {}",
            mId.str(),
            packet->name(),
            server.str(),
            sent.error().message
        );
    }
}

void GatewaySession::handleBackendConnected(ConnectionPtr const& backend, ServerId const& server) {
    {
        std::lock_guard lock{mMutex};
        if (auto* leg = legFor(backend)) leg->connected = true;
    }
    mCondition.notify_all();
    mGateway.logger().info("session {}: backend '{}' connected at {}", mId.str(), server.str(), backend->remote().toString());

    BackendOpenedEvent event;
    event.session = std::static_pointer_cast<PlayerSession>(shared_from_this());
    event.backend = backend;
    event.server = server;
    mGateway.events().emit(event);
}

void GatewaySession::handleBackendClosed(ConnectionPtr const& backend, ServerId const& server, std::string reason) {
    bool wasCurrent = false;
    std::size_t remainingLegs = 0;
    {
        std::lock_guard lock{mMutex};
        if (auto* leg = legFor(backend)) leg->failed = true;
        wasCurrent = mCurrent == backend;
        if (wasCurrent) {
            mCurrent = nullptr;
            mCurrentServer = ServerId{};
        }
        std::erase_if(mBackends, [&backend](auto const& candidate) { return candidate.connection == backend; });
        remainingLegs = mBackends.size();
    }
    mCondition.notify_all();

    mGateway.logger().warn("session {}: backend '{}' closed ({})", mId.str(), server.str(), reason);

    BackendClosedEvent event;
    event.session = std::static_pointer_cast<PlayerSession>(shared_from_this());
    event.backend = backend;
    event.server = server;
    event.reason = std::move(reason);
    mGateway.events().emit(event);

    // A handoff keeps a second leg open before dropping the old one, so losing the
    // current backend while no other leg exists means the player has nowhere left
    // to be and must not be left hanging.
    if (wasCurrent && remainingLegs == 0 && !mClosed) {
        disconnectClient("backend server closed the connection");
        emitClosed("backend lost");
    }
}

void GatewaySession::handleClientClosed(std::string reason) {
    emitClosed(std::move(reason));
}

void GatewaySession::emitClosed(std::string reason) {
    {
        std::lock_guard lock{mMutex};
        if (mClosed) return;
        mClosed = true;
    }

    std::vector<BackendLeg> legs;
    {
        std::lock_guard lock{mMutex};
        legs.swap(mBackends);
        mCurrent = nullptr;
        mCurrentServer = ServerId{};
        mDeferredToClient.clear();
        mDeferredToBackend.clear();
    }
    mPipeline.clear();
    for (auto& leg : legs) {
        if (leg.connection) leg.connection->close();
    }

    mGateway.logger().info("session {}: closed ({})", mId.str(), reason);

    SessionClosedEvent event;
    event.session = std::static_pointer_cast<PlayerSession>(shared_from_this());
    event.reason = std::move(reason);
    mGateway.events().emit(event);
}

// ---- router ------------------------------------------------------------

SessionRouter::SessionRouter(Gateway& gateway) : mGateway(gateway) {}

SessionRouter::~SessionRouter() { stop(); }

Result<> SessionRouter::start() {
    const auto transport = TransportRegistry::instance().active();
    if (!transport) return std::unexpected(Error{"no transport is registered"});

    auto const& network = mGateway.config().network;
    ListenerConfig config;
    config.host = network.listenHost;
    config.port = network.listenPort;
    config.maxConnections = network.maxConnections;
    config.motd = network.motd;
    config.maxPacketBytes = network.maxPacketBytes;
    config.maxPacketsPerSecond = network.maxPacketsPerSecond;

    ConnectionHooks hooks;
    hooks.onConnected = [this](ConnectionPtr const& client) { onClientConnected(client); };
    hooks.onPacket = [this](ConnectionPtr const& client, Bytes& packet) { onClientPacket(client, packet); };
    hooks.onDisconnected = [this](ConnectionPtr const& client) { onClientDisconnected(client); };
    hooks.onParseFailure = [this](ConnectionPtr const& client, proto::PacketId id, std::string_view message) {
        mGateway.logger().warn("client {}: parse failure on {}: {}", client->remote().toString(), proto::packetName(id), message);
    };

    auto listener = transport->listen(config, std::move(hooks));
    if (!listener) return std::unexpected(listener.error());
    if (auto started = (*listener)->start(); !started) return started;

    mListener = std::move(*listener);
    mGateway.logger().info(
        "listening on {}:{} with transport '{}' (protocol {})",
        config.host,
        config.port,
        transport->info().name,
        transport->info().protocolVersion
    );
    return {};
}

void SessionRouter::stop() noexcept {
    std::vector<std::shared_ptr<GatewaySession>> sessions;
    {
        std::lock_guard lock{mMutex};
        if (mListener) {
            mListener->stop();
            mListener.reset();
        }
        sessions.reserve(mSessions.size());
        for (auto& [key, session] : mSessions) sessions.push_back(session);
        mSessions.clear();
    }
    for (auto& session : sessions) session->handleClientClosed("gateway shutting down");
}

std::size_t SessionRouter::sessionCount() const noexcept {
    std::lock_guard lock{mMutex};
    return mSessions.size();
}

void SessionRouter::onClientConnected(ConnectionPtr const& client) {
    std::shared_ptr<GatewaySession> session;
    {
        std::lock_guard lock{mMutex};
        const auto id = SessionId{std::format("s{}", mNextId++)};
        session = std::make_shared<GatewaySession>(mGateway, id, client, mGateway.config().network.maxDeferredPackets);
        mSessions.emplace(client->remote().toString(), session);
    }

    SessionRegistry::instance().track(session);
    mGateway.logger().info("client {} connected as session {}", client->remote().toString(), session->id().str());

    SessionOpenedEvent event;
    event.session = session;
    mGateway.events().emit(event);

    const auto entry = ServerRegistry::instance().entryServerId();
    AttachOptions options;
    options.makeCurrent = true;
    options.closePrevious = false;
    if (auto attached = session->openBackend(entry, options); !attached) {
        mGateway.logger().error("session {}: cannot attach entry backend '{}': {}", session->id().str(), entry.str(), attached.error().message);
        session->disconnectClient("no backend server available");
        onClientDisconnected(client);
    }
}

void SessionRouter::onClientPacket(ConnectionPtr const& client, Bytes& packet) {
    std::shared_ptr<GatewaySession> session;
    {
        std::lock_guard lock{mMutex};
        const auto found = mSessions.find(client->remote().toString());
        if (found != mSessions.end()) session = found->second;
    }
    if (session) session->handleClientPacket(packet);
}

void SessionRouter::onClientDisconnected(ConnectionPtr const& client) {
    std::shared_ptr<GatewaySession> session;
    {
        std::lock_guard lock{mMutex};
        const auto key = client->remote().toString();
        if (const auto found = mSessions.find(key); found != mSessions.end()) {
            session = found->second;
            mSessions.erase(found);
        }
    }
    if (!session) return;

    SessionRegistry::instance().untrack(session->id());
    session->handleClientClosed("client disconnected");
}

} // namespace crosslink::net
