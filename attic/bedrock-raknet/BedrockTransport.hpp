#pragma once

#include "crosslink/api/net/Transport.hpp"

#include <sculk/protocol/connection/ClientNetworkSystem.hpp>
#include <sculk/protocol/connection/ServerNetworkSystem.hpp>

#include <memory>
#include <string>
#include <unordered_map>

namespace crosslink::net::bedrock {

namespace bp = sculk::protocol;

/// One leg of a Bedrock/RakNet connection. The transport library terminates
/// RakNet, batching, compression and encryption here, so everything above sees
/// plain protocol packets.
class BedrockConnection final : public Connection {
public:
    /// Frontend leg: the session is owned by the listener.
    BedrockConnection(std::string label, Endpoint remote, bp::ServerNetworkSystem& server, RakNet::RakNetGUID guid);
    /// Backend leg: this connection owns its client stack.
    BedrockConnection(std::string label, Endpoint remote, std::unique_ptr<bp::ClientNetworkSystem> client);
    ~BedrockConnection() override;

    [[nodiscard]] std::string_view label() const noexcept override { return mLabel; }
    [[nodiscard]] bool             connected() const noexcept override;
    [[nodiscard]] Endpoint         remote() const noexcept override { return mRemote; }

    [[nodiscard]] Result<> send(ByteSpan packet, bool immediate) override;
    void                   setCompression(Compression algorithm, std::int32_t threshold) override;
    [[nodiscard]] Result<> setEncryption(Bytes sessionKey) override;
    [[nodiscard]] bool     encrypted() const noexcept override { return mEncrypted; }
    void                   close() noexcept override;

    [[nodiscard]] std::weak_ptr<bp::Session> session() const;
    [[nodiscard]] bp::ClientNetworkSystem*   client() noexcept { return mClient.get(); }

private:
    std::string                              mLabel;
    Endpoint                                 mRemote;
    bp::ServerNetworkSystem*                 mServer{};
    RakNet::RakNetGUID                       mGuid{};
    std::unique_ptr<bp::ClientNetworkSystem> mClient;
    bool                                     mEncrypted{};
};

/// Accepts game clients. One `bp::ServerNetworkSystem` behind it.
class BedrockListener final : public InboundListener {
public:
    BedrockListener(ListenerConfig config, ConnectionHooks hooks);
    ~BedrockListener() override;

    [[nodiscard]] Result<> start() override;
    void                   stop() noexcept override;
    [[nodiscard]] std::size_t connectionCount() const noexcept override;

private:
    void onConnected(RakNet::RakNetGUID const& guid, RakNet::SystemAddress const& address);
    void onDisconnected(RakNet::RakNetGUID const& guid);
    void onRawPacket(RakNet::RakNetGUID const& guid, bp::Session::Buffer& payload);

    ListenerConfig                                     mConfig;
    ConnectionHooks                                    mHooks;
    bp::ServerNetworkSystem                            mServer;
    mutable std::mutex                                 mMutex;
    std::unordered_map<std::string, ConnectionPtr>     mConnections;
    bool                                               mStarted{};
};

/// The `bedrock-raknet` transport: today's Minecraft Bedrock networking.
///
/// A future nethernet transport (mandatory from 26.60) implements the same
/// `Transport` interface and is selected by name in the configuration; nothing
/// above this file changes.
class BedrockTransport final : public Transport {
public:
    BedrockTransport(std::uint32_t protocolVersion, std::string gameVersion);

    [[nodiscard]] ProtocolInfo info() const noexcept override;

    [[nodiscard]] Result<std::unique_ptr<InboundListener>> listen(ListenerConfig const& config, ConnectionHooks hooks) override;
    [[nodiscard]] Result<ConnectionPtr>                    connect(Endpoint const& endpoint, ConnectionHooks hooks) override;

private:
    ProtocolInfo mInfo;
};

} // namespace crosslink::net::bedrock
