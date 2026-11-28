#pragma once

// JOSE primitives the Bedrock login and encryption handshakes are built from:
// base64url, ES384 (P-384 / SHA-384) JWTs, and ECDH. Internal to the core; the
// plugin-facing surface stays crosslink/api/proto/Crypto.hpp.

#include "crosslink/api/Result.hpp"
#include "crosslink/api/Types.hpp"
#include "crosslink/api/proto/Crypto.hpp"

#include <nlohmann/json.hpp>

#include <cstddef>
#include <span>
#include <string>
#include <string_view>

namespace crosslink::proto::jose {

using Json = nlohmann::ordered_json;

// ---- base64 -----------------------------------------------------------

[[nodiscard]] std::string   base64Encode(ByteSpan data);
[[nodiscard]] Result<Bytes> base64Decode(std::string_view text);
[[nodiscard]] std::string   base64UrlEncode(ByteSpan data);
[[nodiscard]] Result<Bytes> base64UrlDecode(std::string_view text);

[[nodiscard]] Result<Bytes> randomBytes(std::size_t count);
[[nodiscard]] Result<Bytes> sha256(std::span<const ByteSpan> parts);

// ---- keys -------------------------------------------------------------

/// Bedrock signs every login and handshake token with ES384.
[[nodiscard]] Result<crypto::KeyPair> generateKeyPair();

/// The form a JWT `x5u` / `cpk` claim carries: base64 of the DER
/// SubjectPublicKeyInfo, with no PEM markers and no whitespace.
[[nodiscard]] std::string compactKey(std::string_view pemOrCompact);

/// Accepts either the compact claim form or a PEM block, because a peer may
/// send either and both name the same key.
[[nodiscard]] std::string keyToPem(std::string_view compactOrPem);

[[nodiscard]] Result<Bytes> publicKeyDer(std::string_view compactOrPem);

/// The public half of a private key, as PEM.
[[nodiscard]] Result<std::string> publicKeyPem(std::string_view privateKeyPem);

/// Raw ECDH shared secret, which is hashed with the handshake salt to make the
/// batch session key.
[[nodiscard]] Result<Bytes> ecdh(std::string_view privateKeyPem, std::string_view peerPublicKey);

// ---- JWT --------------------------------------------------------------

struct Jwt {
    std::string rawHeader;
    std::string rawPayload;
    /// base64url, empty for an unsigned token.
    std::string signature;
    Json        header;
    Json        payload;

    [[nodiscard]] std::string signingInput() const;
    [[nodiscard]] std::string toString() const;

    [[nodiscard]] std::string headerString(std::string_view name) const;
    [[nodiscard]] std::string payloadString(std::string_view name) const;
};

[[nodiscard]] Result<Jwt> parse(std::string_view token);

/// Signs `header`/`payload` with ES384. `alg` and `x5u` are filled in from the
/// key so a caller cannot accidentally sign under a mismatched identity.
[[nodiscard]] Result<std::string> sign(Json header, Json payload, std::string_view privateKeyPem);

/// Signs with the header exactly as given and an already-serialized payload.
/// A detached JWS keeps the header and signature but drops the payload slot,
/// which is how NetherNet binds an identity to an SDP's fingerprints.
[[nodiscard]] Result<std::string> signCompact(Json header, std::string_view payloadJson, std::string_view privateKeyPem);

/// Verifies against an explicit key, which may be compact base64 or PEM.
[[nodiscard]] Result<> verify(Jwt const& token, std::string_view publicKey);

/// Verifies against the key the token itself carries in `x5u`. This only proves
/// the token is internally consistent, not that the key is trusted.
[[nodiscard]] Result<> verifySelfSigned(Jwt const& token);

} // namespace crosslink::proto::jose