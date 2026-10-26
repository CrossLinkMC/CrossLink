#include "net/bedrock/BedrockTransport.hpp"

#include "crosslink/api/Logger.hpp"

#include <sculk/protocol/codec/level/CompressionAlgorithm.hpp>
#include <sculk/protocol/connection/NetworkStartResult.hpp>

#include <format>
#include <mutex>
#include <utility>

namespace crosslink::net::bedrock {
namespace {

bp::CompressionAlgorithm toSculk(Compression algorithm) noexcept {
    return static_cast<bp::CompressionAlgorithm>(static_cast<std::int8_t>(algorithm));
}

std::string_view startResultName(bp::NetworkStartResult result) noexcept {
    switch (result) {
    case bp::NetworkStartResult::Success:                  return "success";
    case bp::NetworkStartResult::AlreadyStarted:           return "already started";
    case bp::NetworkStartResult::InvalidSocketDescriptors: return "invalid socket descriptors";
    case bp::NetworkStartResult::InvalidMaxConnections:    return "invalid max connections";
    case bp::NetworkStartResult::SocketFamilyNotSupported: return "socket family not supported";
    case bp::NetworkStartResult::SocketPortAlreadyInUse:   return "port already in use";
    case bp::NetworkStartResult::SocketFailedToBind:       return "failed to bind";
    case bp::NetworkStartResult::SocketFailedTestSend:     return "failed test send";
    case bp::NetworkStartResult::PortCannotBeZero:         return "port cannot be zero";
    case bp::NetworkStartResult::FailedToCreateNetworkThread: return "failed to create network thread";
    case bp::NetworkStartResult::CouldNotGenerateGuid:     return "could not generate guid";
    case bp::NetworkStartResult::UnknownError:             return "unknown error";
    }
    return "unknown error";
}

} // namespace

// ---- BedrockConnection -------------------------------------------------

BedrockConnection::BedrockConnection(
    std::string label,
    Endpoint remote,
    bp::ServerNetworkSystem& server,
    RakNet::RakNetGUID guid
)
: mLabel(std::move(label)), mRemote(std::move(remote)), mServer(&server), mGuid(guid) {}

BedrockConnection::BedrockConnection(std::string label, Endpoint remote, std::unique_ptr<bp::ClientNetworkSystem> client)
: mLabel(std::move(label)), mRemote(std::move(remote)), mClient(std::move(client)) {}

BedrockConnection::~BedrockConnection() { close(); }

std::weak_ptr<bp::Session> BedrockConnection::session() const {
    if (mClient) return mClient->getSession();
    if (mServer != nullptr) return mServer->getSession(mGuid);
    return {};
}

bool BedrockConnection::connected() const noexcept {
    const auto session = this->session().lock();
    return session && session->isConnected();
}

Result<> BedrockConnection::send(ByteSpan packet, bool immediate) {
    const auto session = this->session().lock();
    if (!session) return std::unexpected(Error{std::format("'{}' has no live session", mLabel)});
    if (!session->isConnected()) return std::unexpected(Error{std::format("'{}' is not connected", mLabel)});

    const bool sent = immediate ? session->sendPacketImmediately(packet) : session->sendPacket(packet);
    if (!sent) return std::unexpected(Error{std::format("'{}' refused a packet", mLabel)});
    return {};
}

void BedrockConnection::setCompression(Compression algorithm, std::int32_t threshold) {
    const auto session = this->session().lock();
    if (!session) return;
    session->setCompressed(toSculk(algorithm), threshold);
}

Result<> BedrockConnection::setEncryption(Bytes sessionKey) {
    const auto session = this->session().lock();
    if (!session) return std::unexpected(Error{std::format("'{}' has no live session", mLabel)});
    session->setEncrypted(std::move(sessionKey));
    mEncrypted = true;
    return {};
}

void BedrockConnection::close() noexcept {
    if (mClient) {
        mClient->disconnect();
        mClient->stop();
        return;
    }
    if (mServer != nullptr) mServer->disconnectClient(mGuid);
}

// ---- BedrockListener ---------------------------------------------------

BedrockListener::BedrockListener(ListenerConfig config, ConnectionHooks hooks)
: mConfig(std::move(config)), mHooks(std::move(hooks)), mServer(0) {}

BedrockListener::~BedrockListener() { stop(); }

Result<> BedrockListener::start() {
    if (mStarted) return std::unexpected(Error{"the listener is already running"});

    if (!mConfig.motd.empty()) mServer.setMotd(mConfig.motd);

    // The transport library requires every callback to be installed before
    // start(), and a raw packet callback only after a parsed packet callback.
    if (auto result = mServer.setRawIngressLimits(mConfig.maxPacketBytes, mConfig.maxPacketsPerSecond); !result) {
        return std::unexpected(Error{std::string{result.error().message()}});
    }
    if (auto result = mServer.setOnPacketReceive(
            [](RakNet::RakNetGUID const&, RakNet::SystemAddress const&, std::unique_ptr<bp::IPacket>&&) {
                // The raw callback consumes every packet; this one only enables it.
            }
        );
        !result) {
        return std::unexpected(Error{std::string{result.error().message()}});
    }

    if (auto result = mServer.setOnConnected([this](RakNet::RakNetGUID const& guid, RakNet::SystemAddress const& address) {
            onConnected(guid, address);
        });
        !result) {
        return std::unexpected(Error{std::string{result.error().message()}});
    }
    if (auto result = mServer.setOnDisconnected([this](RakNet::RakNetGUID const& guid, RakNet::SystemAddress const&) {
            onDisconnected(guid);
        });
        !result) {
        return std::unexpected(Error{std::string{result.error().message()}});
    }
    if (auto result = mServer.setOnRawPacketReceive(
            [this](RakNet::RakNetGUID const& guid, RakNet::SystemAddress const&, bp::Session::Buffer& payload) {
                onRawPacket(guid, payload);
                return false;
            }
        );
        !result) {
        return std::unexpected(Error{std::string{result.error().message()}});
    }
    if (auto result = mServer.setOnPacketParseFailed(
            [this](RakNet::RakNetGUID const& guid, RakNet::SystemAddress const&, bp::MinecraftPacketIds id, std::string_view message) {
                if (!mHooks.onParseFailure) return;
                ConnectionPtr connection;
                {
                    std::lock_guard lock{mMutex};
                    const auto found = mConnections.find(guid.ToString());
                    if (found == mConnections.end()) return;
                    connection = found->second;
                }
                mHooks.onParseFailure(connection, proto::makePacketId(static_cast<std::uint16_t>(id)), message);
            }
        );
        !result) {
        return std::unexpected(Error{std::string{result.error().message()}});
    }

    const auto status = mServer.start(mConfig.host, mConfig.port, mConfig.maxConnections);
    if (status != bp::NetworkStartResult::Success) {
        return std::unexpected(Error{std::format("cannot bind {}:{} ({})", mConfig.host, mConfig.port, startResultName(status))});
    }
    mStarted = true;
    return {};
}

void BedrockListener::stop() noexcept {
    if (!mStarted) return;
    mStarted = false;
    mServer.stop();
    std::lock_guard lock{mMutex};
    mConnections.clear();
}

std::size_t BedrockListener::connectionCount() const noexcept {
    std::lock_guard lock{mMutex};
    return mConnections.size();
}

void BedrockListener::onConnected(RakNet::RakNetGUID const& guid, RakNet::SystemAddress const& address) {
    Endpoint remote;
    remote.host = address.ToString(false);
    remote.port = address.GetPort();

    auto connection = std::make_shared<BedrockConnection>(std::format("client:{}", remote.toString()), remote, mServer, guid);
    {
        std::lock_guard lock{mMutex};
        mConnections[guid.ToString()] = connection;
    }
    if (mHooks.onConnected) mHooks.onConnected(connection);
}

void BedrockListener::onDisconnected(RakNet::RakNetGUID const& guid) {
    ConnectionPtr connection;
    {
        std::lock_guard lock{mMutex};
        const auto found = mConnections.find(guid.ToString());
        if (found == mConnections.end()) return;
        connection = found->second;
        mConnections.erase(found);
    }
    if (mHooks.onDisconnected) mHooks.onDisconnected(connection);
}

void BedrockListener::onRawPacket(RakNet::RakNetGUID const& guid, bp::Session::Buffer& payload) {
    if (!mHooks.onPacket) return;
    ConnectionPtr connection;
    {
        std::lock_guard lock{mMutex};
        const auto found = mConnections.find(guid.ToString());
        if (found == mConnections.end()) return;
        connection = found->second;
    }
    // The session may move out of `payload`; the packet is consumed either way
    // because the raw callback returned false.
    mHooks.onPacket(connection, payload);
}

// ---- BedrockTransport ---------------------------------------------------

BedrockTransport::BedrockTransport(std::uint32_t protocolVersion, std::string gameVersion) {
    mInfo.name = "bedrock-raknet";
    mInfo.protocolVersion = protocolVersion;
    mInfo.gameVersion = std::move(gameVersion);
    mInfo.supportsEncryption = true;
    mInfo.supportsCompression = true;
    // Both legs terminate here, which is the precondition for a seamless switch.
    mInfo.supportsTermination = true;
}

ProtocolInfo BedrockTransport::info() const noexcept { return mInfo; }

Result<std::unique_ptr<InboundListener>> BedrockTransport::listen(ListenerConfig const& config, ConnectionHooks hooks) {
    return std::unique_ptr<InboundListener>{std::make_unique<BedrockListener>(config, std::move(hooks))};
}

Result<ConnectionPtr> BedrockTransport::connect(Endpoint const& endpoint, ConnectionHooks hooks) {
    auto client = std::make_unique<bp::ClientNetworkSystem>();
    auto connection = std::make_shared<BedrockConnection>(
        std::format("backend:{}", endpoint.toString()),
        endpoint,
        std::move(client)
    );

    auto* rawClient = connection->client();
    std::weak_ptr<BedrockConnection> weak = connection;
    auto storedHooks = std::make_shared<ConnectionHooks>(std::move(hooks));

    // Same ordering rule as the listener: parsed callback first, then raw, and
    // everything before start().
    if (auto result = rawClient->setOnPacketReceive([](std::unique_ptr<bp::IPacket>&&) {}); !result) {
        return std::unexpected(Error{std::string{result.error().message()}});
    }
    if (auto result = rawClient->setOnConnected([weak, storedHooks] {
            const auto connection = weak.lock();
            if (!connection) return;
            if (storedHooks->onConnected) storedHooks->onConnected(connection);
        });
        !result) {
        return std::unexpected(Error{std::string{result.error().message()}});
    }
    if (auto result = rawClient->setOnDisconnected([weak, storedHooks] {
            const auto connection = weak.lock();
            if (!connection) return;
            if (storedHooks->onDisconnected) storedHooks->onDisconnected(connection);
        });
        !result) {
        return std::unexpected(Error{std::string{result.error().message()}});
    }
    if (auto result = rawClient->setOnConnectionFailed([weak, storedHooks] {
            const auto connection = weak.lock();
            if (!connection) return;
            if (storedHooks->onDisconnected) storedHooks->onDisconnected(connection);
        });
        !result) {
        return std::unexpected(Error{std::string{result.error().message()}});
    }
    if (auto result = rawClient->setOnRawPacketReceive([weak, storedHooks](bp::Session::Buffer& payload) {
            const auto connection = weak.lock();
            if (!connection) return false;
            if (storedHooks->onPacket) storedHooks->onPacket(connection, payload);
            return false;
        });
        !result) {
        return std::unexpected(Error{std::string{result.error().message()}});
    }
    if (auto result = rawClient->setOnPacketParseFailed([weak, storedHooks](bp::MinecraftPacketIds id, std::string_view message) {
            const auto connection = weak.lock();
            if (!connection) return;
            if (storedHooks->onParseFailure) {
                storedHooks->onParseFailure(connection, proto::makePacketId(static_cast<std::uint16_t>(id)), message);
            }
        });
        !result) {
        return std::unexpected(Error{std::string{result.error().message()}});
    }

    if (const auto status = rawClient->start(); status != bp::NetworkStartResult::Success) {
        return std::unexpected(Error{std::format("cannot start the backend stack for {} ({})", endpoint.toString(), startResultName(status))});
    }
    if (const auto status = rawClient->connect(endpoint.host, endpoint.port);
        status != bp::ClientNetworkSystem::ConnectionResult::ConnectionAttemptStarted) {
        rawClient->stop();
        return std::unexpected(Error{std::format("cannot dial {} (result {})", endpoint.toString(), static_cast<int>(status))});
    }
    return ConnectionPtr{std::move(connection)};
}

} // namespace crosslink::net::bedrock
