#pragma once

#include "crosslink/api/proto/TypedPacket.hpp"

#include <string>
#include <string_view>

namespace crosslink::proto {

/// Carries the signed token the client uses to derive the AES session key.
///
/// A relay terminates this handshake on both legs: it verifies the backend's
/// token, derives the backend key, then issues a token of its own to the client
/// and derives a separate client key. Reusing one key on the other leg cannot
/// work, because the client's ECDH private key never leaves the client.
class CROSSLINK_API ServerToClientHandshakePacket final
: public TypedPacket<ServerToClientHandshakePacket, PacketId::ServerToClientHandshake> {
public:
    static constexpr std::string_view staticName = "ServerToClientHandshakePacket";

    using TypedPacket::TypedPacket;

    explicit ServerToClientHandshakePacket(std::string token);

    [[nodiscard]] std::string const& token() const;
    void                             setToken(std::string token);

protected:
    Result<> decodeImpl() override;
    Result<> encodeImpl() override;

private:
    std::string mToken;
};

/// The client's (empty) acknowledgement that it switched to encryption.
class CROSSLINK_API ClientToServerHandshakePacket final
: public TypedPacket<ClientToServerHandshakePacket, PacketId::ClientToServerHandshake> {
public:
    static constexpr std::string_view staticName = "ClientToServerHandshakePacket";

    using TypedPacket::TypedPacket;

protected:
    Result<> decodeImpl() override;
    Result<> encodeImpl() override;
};

} // namespace crosslink::proto
