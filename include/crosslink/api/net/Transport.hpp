#pragma once

#include "crosslink/api/Export.hpp"
#include "crosslink/api/Result.hpp"
#include "crosslink/api/Types.hpp"
#include "crosslink/api/proto/PacketId.hpp"

#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

namespace crosslink::net {

enum class Compression : std::int8_t {
    None   = -1,
    Zlib   = 0,
    Snappy = 1,
};

/// What a transport stack can do. The gateway asks the transport instead of
/// assuming, so a future stack can declare what it supports.
struct ProtocolInfo {
    std::string   name;
    std::uint32_t protocolVersion{};
    std::string   gameVersion;
    bool          supportsEncryption{};
    bool          supportsCompression{};
    /// True when the gateway can terminate a session on both legs, which is what
    /// makes a seamless backend switch possible at all.
    bool          supportsTermination{};
};

class CROSSLINK_API Connection {
public:
    Connection(Connection const&)            = delete;
    Connection& operator=(Connection const&) = delete;
    virtual ~Connection();

    /// "client" for the leg facing the player, "backend:<serverId>" otherwise.
    [[nodiscard]] virtual std::string_view label() const noexcept = 0;
    [[nodiscard]] virtual bool             connected() const noexcept = 0;
    [[nodiscard]] virtual Endpoint         remote() const noexcept = 0;

    /// `packet` is one complete protocol packet, header included. Batched and
    /// flushed by the transport unless `immediate` is set.
    [[nodiscard]] virtual Result<> send(ByteSpan packet, bool immediate = false) = 0;

    virtual void setCompression(Compression algorithm, std::int32_t threshold) = 0;
    [[nodiscard]] virtual Result<> setEncryption(Bytes sessionKey)               = 0;
    [[nodiscard]] virtual bool     encrypted() const noexcept                    = 0;

    virtual void close() noexcept = 0;

protected:
    Connection() = default;
};

using ConnectionPtr = std::shared_ptr<Connection>;

struct ConnectionHooks {
    std::function<void(ConnectionPtr const&)>                       onConnected;
    std::function<void(ConnectionPtr const&)>                       onDisconnected;
    /// One de-batched, decrypted packet. The buffer may be rewritten in place.
    std::function<void(ConnectionPtr const&, Bytes&)>               onPacket;
    std::function<void(ConnectionPtr const&, proto::PacketId, std::string_view)> onParseFailure;
};

struct ListenerConfig {
    std::string   host{"0.0.0.0"};
    std::uint16_t port{19132};
    std::uint32_t maxConnections{1024};
    std::string   motd;
    /// Per-connection ingress guard rails.
    std::size_t   maxPacketBytes{8u * 1024u * 1024u};
    std::size_t   maxPacketsPerSecond{1024};
};

class CROSSLINK_API InboundListener {
public:
    InboundListener(InboundListener const&)            = delete;
    InboundListener& operator=(InboundListener const&) = delete;
    virtual ~InboundListener();

    [[nodiscard]] virtual Result<> start() = 0;
    virtual void                   stop() noexcept = 0;
    [[nodiscard]] virtual std::size_t connectionCount() const noexcept = 0;

protected:
    InboundListener() = default;
};

/// A network stack.
///
/// CrossLink ships `bedrock-raknet` on top of the BedrockProtocol library.
/// Minecraft forces the nethernet stack from 26.60 onwards; that will arrive as
/// a second implementation of this interface. Nothing above this line — routing,
/// sessions, the plugin API, or any plugin — may assume RakNet or Bedrock
/// framing.
class CROSSLINK_API Transport {
public:
    Transport(Transport const&)            = delete;
    Transport& operator=(Transport const&) = delete;
    virtual ~Transport();

    [[nodiscard]] virtual ProtocolInfo info() const noexcept = 0;

    [[nodiscard]] virtual Result<std::unique_ptr<InboundListener>> listen(
        ListenerConfig const& config,
        ConnectionHooks       hooks
    ) = 0;

    /// Opens an outbound connection. Asynchronous: `onConnected` reports success.
    [[nodiscard]] virtual Result<ConnectionPtr> connect(Endpoint const& endpoint, ConnectionHooks hooks) = 0;

protected:
    Transport() = default;
};

using TransportPtr = std::shared_ptr<Transport>;

/// Transports registered by the host or by plugins; config selects the active one.
class CROSSLINK_API TransportRegistry {
public:
    [[nodiscard]] static TransportRegistry& instance();

    bool         registerTransport(std::string name, TransportPtr transport);
    bool         unregisterTransport(std::string_view name);
    TransportPtr get(std::string_view name) const;
    TransportPtr active() const;
    bool         setActive(std::string_view name);
    [[nodiscard]] std::vector<std::string> names() const;

private:
    TransportRegistry();
    ~TransportRegistry();

    struct Impl;
    std::unique_ptr<Impl> mImpl;
};

} // namespace crosslink::net
