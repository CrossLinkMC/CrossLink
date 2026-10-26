#include "crosslink/api/proto/Crypto.hpp"

#include <sculk/protocol/auth/PemKeyPair.hpp>
#include <sculk/protocol/connection/HandShakeToken.hpp>
#include <sculk/protocol/connection/encryption/CryptoManager.hpp>

namespace crosslink::proto::crypto {
namespace {

namespace bp = sculk::protocol;

bp::PemKeyPair toSculk(KeyPair const& keyPair) {
    return bp::PemKeyPair{.mPublicKeyPem = keyPair.publicKeyPem, .mPrivateKeyPem = keyPair.privateKeyPem};
}

} // namespace

Result<KeyPair> generateKeyPair() {
    const auto keyPair = bp::ssl::randomES384KeyPair();
    if (!keyPair) return std::unexpected(Error{std::string{keyPair.error().message()}});
    return KeyPair{keyPair->mPublicKeyPem, keyPair->mPrivateKeyPem};
}

Result<HandshakeToken> parseHandshakeToken(std::string_view jsonWebToken) {
    auto token = bp::HandShakeToken::fromString(jsonWebToken);
    if (!token) return std::unexpected(Error{std::string{token.error().message()}});

    HandshakeToken parsed;
    parsed.raw = std::string{jsonWebToken};
    parsed.remotePublicKey = token->getRemotePublicKey();
    parsed.salt = token->getSaltBytes();
    if (parsed.salt.empty()) return std::unexpected(Error{"handshake token carries no salt"});
    return parsed;
}

Result<> verifyHandshakeToken(HandshakeToken const& token) {
    auto parsed = bp::HandShakeToken::fromString(token.raw);
    if (!parsed) return std::unexpected(Error{std::string{parsed.error().message()}});
    if (const auto status = parsed->verify(); !status) {
        return std::unexpected(Error{std::string{status.error().message()}});
    }
    return {};
}

Result<HandshakeToken> createHandshakeToken(KeyPair const& localKeyPair) {
    const auto token = bp::HandShakeToken::random(toSculk(localKeyPair));
    if (!token) return std::unexpected(Error{std::string{token.error().message()}});

    HandshakeToken created;
    created.raw = token->toString();
    created.remotePublicKey = localKeyPair.publicKeyPem;
    created.salt = token->getSaltBytes();
    return created;
}

Result<Bytes> deriveSessionKey(std::string_view localPrivateKeyPem, std::string_view remotePublicKeyPem, ByteSpan salt) {
    const auto key = bp::CryptoManager::computeSessionKey(localPrivateKeyPem, remotePublicKeyPem, salt);
    if (!key) return std::unexpected(Error{std::string{key.error().message()}});
    return *key;
}

} // namespace crosslink::proto::crypto
