#include "crosslink/api/proto/Crypto.hpp"

#include "proto/Jose.hpp"

#include <utility>

namespace crosslink::proto::crypto {
namespace {

/// BDS issues a 16-byte salt; match it rather than relying on the client
/// accepting an arbitrary length. Carried as standard (padded) base64.
constexpr std::size_t kSaltSize = 16;

} // namespace

Result<KeyPair> generateKeyPair() { return jose::generateKeyPair(); }

Result<HandshakeToken> parseHandshakeToken(std::string_view jsonWebToken) {
    CROSSLINK_ASSIGN(token, jose::parse(jsonWebToken));

    HandshakeToken parsed;
    parsed.raw = std::string{jsonWebToken};
    parsed.remotePublicKey = token->headerString("x5u");
    if (parsed.remotePublicKey.empty()) {
        return std::unexpected(Error{"the handshake token carries no x5u key"});
    }

    CROSSLINK_ASSIGN(salt, jose::base64Decode(token->payloadString("salt")));
    if (salt->empty()) return std::unexpected(Error{"handshake token carries no salt"});
    parsed.salt = std::move(*salt);
    return parsed;
}

Result<> verifyHandshakeToken(HandshakeToken const& token) {
    CROSSLINK_ASSIGN(parsed, jose::parse(token.raw));
    return jose::verifySelfSigned(*parsed);
}

Result<HandshakeToken> createHandshakeToken(KeyPair const& localKeyPair) {
    CROSSLINK_ASSIGN(salt, jose::randomBytes(kSaltSize));

    jose::Json payload;
    payload["salt"] = jose::base64Encode(*salt);

    CROSSLINK_ASSIGN(raw, jose::sign(jose::Json::object(), std::move(payload), localKeyPair.privateKeyPem));

    HandshakeToken created;
    created.raw = std::move(*raw);
    created.remotePublicKey = localKeyPair.publicKeyPem;
    created.salt = std::move(*salt);
    return created;
}

Result<Bytes> deriveSessionKey(std::string_view localPrivateKeyPem, std::string_view remotePublicKeyPem, ByteSpan salt) {
    CROSSLINK_ASSIGN(secret, jose::ecdh(localPrivateKeyPem, remotePublicKeyPem));
    // The order is salt first: both peers must hash the same byte string.
    const std::array parts{salt, ByteSpan{*secret}};
    CROSSLINK_ASSIGN(key, jose::sha256(parts));
    if (key->size() != 32) return std::unexpected(Error{"the session key must be 32 bytes"});
    return *key;
}

} // namespace crosslink::proto::crypto