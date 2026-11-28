#include "proto/Jose.hpp"

#include <openssl/bn.h>
#include <openssl/core_names.h>
#include <openssl/ec.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rand.h>

#include <algorithm>
#include <array>
#include <cctype>
#include <cstring>
#include <memory>
#include <utility>

namespace crosslink::proto::jose {
namespace {

constexpr std::size_t kScalarSize = 48; // P-384
constexpr std::size_t kJoseSignatureSize = 2 * kScalarSize;

struct BioDeleter {
    void operator()(BIO* bio) const noexcept { BIO_free(bio); }
};
struct PkeyDeleter {
    void operator()(EVP_PKEY* key) const noexcept { EVP_PKEY_free(key); }
};
struct PkeyCtxDeleter {
    void operator()(EVP_PKEY_CTX* ctx) const noexcept { EVP_PKEY_CTX_free(ctx); }
};
struct MdCtxDeleter {
    void operator()(EVP_MD_CTX* ctx) const noexcept { EVP_MD_CTX_free(ctx); }
};
struct EcdsaSigDeleter {
    void operator()(ECDSA_SIG* sig) const noexcept { ECDSA_SIG_free(sig); }
};
struct BnDeleter {
    void operator()(BIGNUM* bn) const noexcept { BN_free(bn); }
};

using BioPtr = std::unique_ptr<BIO, BioDeleter>;
using PkeyPtr = std::unique_ptr<EVP_PKEY, PkeyDeleter>;
using PkeyCtxPtr = std::unique_ptr<EVP_PKEY_CTX, PkeyCtxDeleter>;
using MdCtxPtr = std::unique_ptr<EVP_MD_CTX, MdCtxDeleter>;
using EcdsaSigPtr = std::unique_ptr<ECDSA_SIG, EcdsaSigDeleter>;
using BnPtr = std::unique_ptr<BIGNUM, BnDeleter>;

[[nodiscard]] unsigned char byteValue(std::byte value) noexcept { return static_cast<unsigned char>(value); }

[[nodiscard]] std::string_view standardAlphabet() noexcept {
    return "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
}

[[nodiscard]] std::string_view urlAlphabet() noexcept {
    return "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";
}

[[nodiscard]] int base64Value(unsigned char ch) noexcept {
    if (ch >= 'A' && ch <= 'Z') return ch - 'A';
    if (ch >= 'a' && ch <= 'z') return ch - 'a' + 26;
    if (ch >= '0' && ch <= '9') return ch - '0' + 52;
    if (ch == '+' || ch == '-') return 62;
    if (ch == '/' || ch == '_') return 63;
    return -1;
}

[[nodiscard]] std::string encodeBase64(ByteSpan data, bool url) {
    const auto alphabet = url ? urlAlphabet() : standardAlphabet();
    std::string out;
    out.reserve((data.size() + 2) / 3 * 4);

    std::size_t index = 0;
    for (; index + 3 <= data.size(); index += 3) {
        const std::uint32_t group = (static_cast<std::uint32_t>(byteValue(data[index])) << 16U)
                                  | (static_cast<std::uint32_t>(byteValue(data[index + 1])) << 8U)
                                  | static_cast<std::uint32_t>(byteValue(data[index + 2]));
        out.push_back(alphabet[(group >> 18U) & 63U]);
        out.push_back(alphabet[(group >> 12U) & 63U]);
        out.push_back(alphabet[(group >> 6U) & 63U]);
        out.push_back(alphabet[group & 63U]);
    }

    const auto remaining = data.size() - index;
    if (remaining == 1) {
        const std::uint32_t group = static_cast<std::uint32_t>(byteValue(data[index])) << 16U;
        out.push_back(alphabet[(group >> 18U) & 63U]);
        out.push_back(alphabet[(group >> 12U) & 63U]);
        if (!url) out.append("==");
    } else if (remaining == 2) {
        const std::uint32_t group = (static_cast<std::uint32_t>(byteValue(data[index])) << 16U)
                                  | (static_cast<std::uint32_t>(byteValue(data[index + 1])) << 8U);
        out.push_back(alphabet[(group >> 18U) & 63U]);
        out.push_back(alphabet[(group >> 12U) & 63U]);
        out.push_back(alphabet[(group >> 6U) & 63U]);
        if (!url) out.push_back('=');
    }
    return out;
}

[[nodiscard]] Result<Bytes> decodeBase64(std::string_view text) {
    Bytes out;
    out.reserve(text.size() / 4 * 3 + 2);

    std::uint32_t accumulator = 0;
    int bits = 0;
    for (const unsigned char ch : text) {
        if (ch == '=') break;
        if (std::isspace(ch) != 0) continue;
        const int value = base64Value(ch);
        if (value < 0) return std::unexpected(Error{"invalid base64 character"});
        accumulator = (accumulator << 6U) | static_cast<std::uint32_t>(value);
        bits += 6;
        if (bits >= 8) {
            bits -= 8;
            out.push_back(static_cast<std::byte>((accumulator >> bits) & 0xFFU));
        }
    }
    // A trailing group of one character carries no whole byte and is never valid.
    if (bits == 6) return std::unexpected(Error{"truncated base64 input"});
    return out;
}

[[nodiscard]] Result<PkeyPtr> readPrivateKey(std::string_view pem) {
    const std::string normalized = keyToPem(pem);
    BioPtr bio{BIO_new_mem_buf(normalized.data(), static_cast<int>(normalized.size()))};
    if (!bio) return std::unexpected(Error{"cannot allocate a key buffer"});
    PkeyPtr key{PEM_read_bio_PrivateKey(bio.get(), nullptr, nullptr, nullptr)};
    if (!key) return std::unexpected(Error{"cannot read the private key"});
    return key;
}

[[nodiscard]] Result<PkeyPtr> readPublicKey(std::string_view key) {
    const std::string pem = keyToPem(key);
    BioPtr bio{BIO_new_mem_buf(pem.data(), static_cast<int>(pem.size()))};
    if (!bio) return std::unexpected(Error{"cannot allocate a key buffer"});
    PkeyPtr parsed{PEM_read_bio_PUBKEY(bio.get(), nullptr, nullptr, nullptr)};
    if (!parsed) return std::unexpected(Error{"cannot read the public key"});
    return parsed;
}

[[nodiscard]] Result<std::string> writePem(EVP_PKEY* key, bool privatePart) {
    BioPtr bio{BIO_new(BIO_s_mem())};
    if (!bio) return std::unexpected(Error{"cannot allocate a PEM buffer"});
    const int written = privatePart
                          ? PEM_write_bio_PrivateKey(bio.get(), key, nullptr, nullptr, 0, nullptr, nullptr)
                          : PEM_write_bio_PUBKEY(bio.get(), key);
    if (written != 1) return std::unexpected(Error{"cannot write the key as PEM"});

    char* data = nullptr;
    const auto length = BIO_get_mem_data(bio.get(), &data);
    if (length <= 0 || data == nullptr) return std::unexpected(Error{"the PEM buffer is empty"});
    return std::string{data, static_cast<std::size_t>(length)};
}

/// JOSE carries ECDSA signatures as the fixed-width pair r||s, while OpenSSL
/// produces DER. Every conversion goes through here.
[[nodiscard]] Result<std::string> signEs384(std::string_view signingInput, EVP_PKEY* privateKey) {
    MdCtxPtr ctx{EVP_MD_CTX_new()};
    if (!ctx) return std::unexpected(Error{"cannot allocate a signing context"});
    if (EVP_DigestSignInit(ctx.get(), nullptr, EVP_sha384(), nullptr, privateKey) != 1) {
        return std::unexpected(Error{"cannot initialize ES384 signing"});
    }
    if (EVP_DigestSignUpdate(ctx.get(), signingInput.data(), signingInput.size()) != 1) {
        return std::unexpected(Error{"cannot feed the signing input"});
    }
    std::size_t derLength = 0;
    if (EVP_DigestSignFinal(ctx.get(), nullptr, &derLength) != 1 || derLength == 0) {
        return std::unexpected(Error{"cannot size the ES384 signature"});
    }
    std::vector<unsigned char> der(derLength);
    if (EVP_DigestSignFinal(ctx.get(), der.data(), &derLength) != 1) {
        return std::unexpected(Error{"cannot produce the ES384 signature"});
    }
    der.resize(derLength);

    const unsigned char* cursor = der.data();
    EcdsaSigPtr sig{d2i_ECDSA_SIG(nullptr, &cursor, static_cast<long>(der.size()))};
    if (!sig) return std::unexpected(Error{"cannot decode the ES384 signature"});

    const BIGNUM* r = nullptr;
    const BIGNUM* s = nullptr;
    ECDSA_SIG_get0(sig.get(), &r, &s);
    std::array<std::byte, kJoseSignatureSize> jose{};
    if (BN_bn2binpad(r, reinterpret_cast<unsigned char*>(jose.data()), static_cast<int>(kScalarSize))
            != static_cast<int>(kScalarSize)
        || BN_bn2binpad(
               s,
               reinterpret_cast<unsigned char*>(jose.data()) + kScalarSize,
               static_cast<int>(kScalarSize)
           ) != static_cast<int>(kScalarSize)) {
        return std::unexpected(Error{"the ES384 signature does not fit P-384"});
    }
    return base64UrlEncode(jose);
}

[[nodiscard]] Result<> verifyEs384(std::string_view signingInput, std::string_view signature, EVP_PKEY* publicKey) {
    CROSSLINK_ASSIGN(decoded, base64UrlDecode(signature));
    if (decoded->size() != kJoseSignatureSize) {
        return std::unexpected(Error{"an ES384 signature must be 96 bytes"});
    }

    BnPtr r{BN_bin2bn(reinterpret_cast<const unsigned char*>(decoded->data()), static_cast<int>(kScalarSize), nullptr)};
    BnPtr s{
        BN_bin2bn(reinterpret_cast<const unsigned char*>(decoded->data()) + kScalarSize, static_cast<int>(kScalarSize), nullptr)
    };
    if (!r || !s) return std::unexpected(Error{"cannot read the ES384 scalars"});

    EcdsaSigPtr sig{ECDSA_SIG_new()};
    if (!sig) return std::unexpected(Error{"cannot allocate an ES384 signature"});
    if (ECDSA_SIG_set0(sig.get(), r.release(), s.release()) != 1) {
        return std::unexpected(Error{"cannot assemble the ES384 signature"});
    }

    int derLength = i2d_ECDSA_SIG(sig.get(), nullptr);
    if (derLength <= 0) return std::unexpected(Error{"cannot size the DER signature"});
    std::vector<unsigned char> der(static_cast<std::size_t>(derLength));
    unsigned char* cursor = der.data();
    if (i2d_ECDSA_SIG(sig.get(), &cursor) != derLength) {
        return std::unexpected(Error{"cannot encode the DER signature"});
    }

    MdCtxPtr ctx{EVP_MD_CTX_new()};
    if (!ctx) return std::unexpected(Error{"cannot allocate a verification context"});
    if (EVP_DigestVerifyInit(ctx.get(), nullptr, EVP_sha384(), nullptr, publicKey) != 1) {
        return std::unexpected(Error{"cannot initialize ES384 verification"});
    }
    if (EVP_DigestVerifyUpdate(ctx.get(), signingInput.data(), signingInput.size()) != 1) {
        return std::unexpected(Error{"cannot feed the signing input"});
    }
    if (EVP_DigestVerifyFinal(ctx.get(), der.data(), der.size()) != 1) {
        return std::unexpected(Error{"the ES384 signature does not verify"});
    }
    return {};
}

[[nodiscard]] std::string jsonString(Json const& value, std::string_view name) {
    const auto found = value.find(name);
    if (found == value.end() || !found->is_string()) return {};
    return found->get<std::string>();
}

} // namespace

// ---- base64 -----------------------------------------------------------

std::string base64Encode(ByteSpan data) { return encodeBase64(data, false); }

Result<Bytes> base64Decode(std::string_view text) { return decodeBase64(text); }

std::string base64UrlEncode(ByteSpan data) { return encodeBase64(data, true); }

Result<Bytes> base64UrlDecode(std::string_view text) { return decodeBase64(text); }

Result<Bytes> randomBytes(std::size_t count) {
    Bytes out(count);
    if (count == 0) return out;
    if (RAND_bytes(reinterpret_cast<unsigned char*>(out.data()), static_cast<int>(count)) != 1) {
        return std::unexpected(Error{"the system RNG refused a request"});
    }
    return out;
}

Result<Bytes> sha256(std::span<const ByteSpan> parts) {
    MdCtxPtr ctx{EVP_MD_CTX_new()};
    if (!ctx) return std::unexpected(Error{"cannot allocate a digest context"});
    if (EVP_DigestInit_ex(ctx.get(), EVP_sha256(), nullptr) != 1) {
        return std::unexpected(Error{"cannot initialize SHA-256"});
    }
    for (const auto part : parts) {
        if (part.empty()) continue;
        if (EVP_DigestUpdate(ctx.get(), part.data(), part.size()) != 1) {
            return std::unexpected(Error{"cannot feed SHA-256"});
        }
    }
    Bytes out(EVP_MAX_MD_SIZE);
    unsigned int length = 0;
    if (EVP_DigestFinal_ex(ctx.get(), reinterpret_cast<unsigned char*>(out.data()), &length) != 1) {
        return std::unexpected(Error{"cannot finalize SHA-256"});
    }
    out.resize(length);
    return out;
}

// ---- keys -------------------------------------------------------------

Result<crypto::KeyPair> generateKeyPair() {
    PkeyPtr key{EVP_EC_gen("P-384")};
    if (!key) return std::unexpected(Error{"cannot generate a P-384 key pair"});

    CROSSLINK_ASSIGN(publicPem, writePem(key.get(), false));
    CROSSLINK_ASSIGN(privatePem, writePem(key.get(), true));
    return crypto::KeyPair{.publicKeyPem = *publicPem, .privateKeyPem = *privatePem};
}

std::string compactKey(std::string_view pemOrCompact) {
    std::string out;
    out.reserve(pemOrCompact.size());
    for (std::size_t index = 0; index < pemOrCompact.size(); ++index) {
        if (pemOrCompact.compare(index, 5, "-----") == 0) {
            // A PEM marker runs to the next "-----"; everything inside is decoration.
            const auto close = pemOrCompact.find("-----", index + 5);
            if (close == std::string_view::npos) break;
            index = close + 4;
            continue;
        }
        const char ch = pemOrCompact[index];
        if (ch == '\r' || ch == '\n' || ch == ' ' || ch == '\t') continue;
        out.push_back(ch);
    }
    return out;
}

std::string keyToPem(std::string_view compactOrPem) {
    if (compactOrPem.find("-----BEGIN") != std::string_view::npos) return std::string{compactOrPem};

    const std::string body = compactKey(compactOrPem);
    std::string out = "-----BEGIN PUBLIC KEY-----\n";
    for (std::size_t index = 0; index < body.size(); index += 64) {
        out.append(body, index, 64);
        out.push_back('\n');
    }
    out.append("-----END PUBLIC KEY-----\n");
    return out;
}

Result<Bytes> publicKeyDer(std::string_view compactOrPem) { return base64Decode(compactKey(compactOrPem)); }

Result<std::string> publicKeyPem(std::string_view privateKeyPem) {
    CROSSLINK_ASSIGN(key, readPrivateKey(privateKeyPem));
    return writePem(key->get(), false);
}

Result<Bytes> ecdh(std::string_view privateKeyPem, std::string_view peerPublicKey) {
    CROSSLINK_ASSIGN(local, readPrivateKey(privateKeyPem));
    CROSSLINK_ASSIGN(peer, readPublicKey(peerPublicKey));

    PkeyCtxPtr ctx{EVP_PKEY_CTX_new(local->get(), nullptr)};
    if (!ctx) return std::unexpected(Error{"cannot allocate an ECDH context"});
    if (EVP_PKEY_derive_init(ctx.get()) != 1) return std::unexpected(Error{"cannot initialize ECDH"});
    if (EVP_PKEY_derive_set_peer(ctx.get(), peer->get()) != 1) {
        return std::unexpected(Error{"the peer key is not usable for ECDH"});
    }

    std::size_t length = 0;
    if (EVP_PKEY_derive(ctx.get(), nullptr, &length) != 1 || length == 0) {
        return std::unexpected(Error{"cannot size the ECDH secret"});
    }
    Bytes secret(length);
    if (EVP_PKEY_derive(ctx.get(), reinterpret_cast<unsigned char*>(secret.data()), &length) != 1) {
        return std::unexpected(Error{"cannot derive the ECDH secret"});
    }
    secret.resize(length);
    return secret;
}

// ---- JWT --------------------------------------------------------------

std::string Jwt::signingInput() const { return rawHeader + "." + rawPayload; }

std::string Jwt::toString() const { return signingInput() + "." + signature; }

std::string Jwt::headerString(std::string_view name) const { return jsonString(header, name); }

std::string Jwt::payloadString(std::string_view name) const { return jsonString(payload, name); }

Result<Jwt> parse(std::string_view token) {
    const auto first = token.find('.');
    const auto last = token.rfind('.');
    if (first == std::string_view::npos || last == std::string_view::npos || first == last) {
        return std::unexpected(Error{"a JWT must have three dot-separated parts"});
    }

    Jwt jwt;
    jwt.rawHeader = std::string{token.substr(0, first)};
    jwt.rawPayload = std::string{token.substr(first + 1, last - first - 1)};
    jwt.signature = std::string{token.substr(last + 1)};

    const auto decodePart = [](std::string_view raw) -> Result<Json> {
        CROSSLINK_ASSIGN(bytes, base64UrlDecode(raw));
        try {
            return Json::parse(viewOf(*bytes));
        } catch (std::exception const& error) {
            return std::unexpected(Error{std::string{"malformed JWT JSON: "} + error.what()});
        }
    };

    CROSSLINK_ASSIGN(header, decodePart(jwt.rawHeader));
    CROSSLINK_ASSIGN(payload, decodePart(jwt.rawPayload));
    if (!header->is_object() || !payload->is_object()) {
        return std::unexpected(Error{"JWT header and payload must be objects"});
    }
    jwt.header = std::move(*header);
    jwt.payload = std::move(*payload);
    return jwt;
}

Result<std::string> sign(Json header, Json payload, std::string_view privateKeyPem) {
    CROSSLINK_ASSIGN(key, readPrivateKey(privateKeyPem));
    CROSSLINK_ASSIGN(publicPem, writePem(key->get(), false));

    header["alg"] = "ES384";
    header["x5u"] = compactKey(*publicPem);
    return signCompact(std::move(header), payload.dump(), privateKeyPem);
}

Result<std::string> signCompact(Json header, std::string_view payloadJson, std::string_view privateKeyPem) {
    CROSSLINK_ASSIGN(key, readPrivateKey(privateKeyPem));

    Jwt jwt;
    jwt.rawHeader = base64UrlEncode(bytesOf(header.dump()));
    jwt.rawPayload = base64UrlEncode(bytesOf(payloadJson));
    CROSSLINK_ASSIGN(signature, signEs384(jwt.signingInput(), key->get()));
    jwt.signature = *signature;
    return jwt.toString();
}

Result<> verify(Jwt const& token, std::string_view publicKey) {
    if (token.headerString("alg") != "ES384") {
        return std::unexpected(Error{"the token is not signed with ES384"});
    }
    CROSSLINK_ASSIGN(key, readPublicKey(publicKey));
    return verifyEs384(token.signingInput(), token.signature, key->get());
}

Result<> verifySelfSigned(Jwt const& token) {
    const std::string x5u = token.headerString("x5u");
    if (x5u.empty()) return std::unexpected(Error{"the token carries no x5u key"});
    return verify(token, x5u);
}

} // namespace crosslink::proto::jose