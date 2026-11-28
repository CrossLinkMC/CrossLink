#pragma once

// NetherNet's a=identity: an operator key signs a token carrying its own public
// key, plus a detached JWS over the SDP's fingerprints. That binds the DTLS
// certificate a peer will use to an identity, which is what replaces the Bedrock
// encryption handshake on this transport.

#include "crosslink/api/Result.hpp"
#include "crosslink/api/proto/Crypto.hpp"

#include <filesystem>
#include <string>
#include <string_view>

namespace crosslink::net::nethernet {

/// Long-lived and persisted, so restarting the gateway does not change the
/// identity a client or a backend has already seen.
class IdentityKey {
public:
    [[nodiscard]] static Result<IdentityKey> loadOrCreate(std::filesystem::path const& path);
    [[nodiscard]] static Result<IdentityKey> generate();

    /// The a=identity attribute value for a *final* SDP: anything that changes a
    /// fingerprint line afterwards invalidates the assertion.
    [[nodiscard]] Result<std::string> assertion(std::string_view sdp) const;

    [[nodiscard]] std::string const& publicKey() const noexcept { return mPublicKey; }

    [[nodiscard]] proto::crypto::KeyPair const& keyPair() const noexcept { return mKeyPair; }

private:
    explicit IdentityKey(proto::crypto::KeyPair keyPair);

    proto::crypto::KeyPair mKeyPair;
    std::string            mPublicKey;
};

/// Structural check only: the token's self-signature and the fingerprint JWS
/// under the key the token embeds. It proves consistency, not trust.
[[nodiscard]] Result<> verifyAssertion(std::string_view sdp);

} // namespace crosslink::net::nethernet