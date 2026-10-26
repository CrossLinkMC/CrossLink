#pragma once

#include "crosslink/api/Export.hpp"
#include "crosslink/api/Result.hpp"
#include "crosslink/api/Types.hpp"

#include <string>
#include <string_view>

namespace crosslink::proto::crypto {

/// An ES384 (P-384) key pair in PEM form, which is what the Bedrock login and
/// encryption handshakes use.
struct KeyPair {
    std::string publicKeyPem;
    std::string privateKeyPem;
};

[[nodiscard]] CROSSLINK_API Result<KeyPair> generateKeyPair();

/// The signed token a server sends in ServerToClientHandshake. Both legs of a
/// relay terminate this handshake independently: the session key derived for the
/// client must never be reused for a backend.
struct HandshakeToken {
    std::string raw;
    std::string remotePublicKey;
    Bytes       salt;
};

[[nodiscard]] CROSSLINK_API Result<HandshakeToken> parseHandshakeToken(std::string_view jsonWebToken);
[[nodiscard]] CROSSLINK_API Result<>               verifyHandshakeToken(HandshakeToken const& token);
[[nodiscard]] CROSSLINK_API Result<HandshakeToken> createHandshakeToken(KeyPair const& localKeyPair);

/// AES-256-CTR session key: ECDH(local private, remote public) + salt, hashed.
[[nodiscard]] CROSSLINK_API Result<Bytes> deriveSessionKey(
    std::string_view localPrivateKeyPem,
    std::string_view remotePublicKeyPem,
    ByteSpan         salt
);

} // namespace crosslink::proto::crypto
