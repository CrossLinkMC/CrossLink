#include "net/nethernet/Identity.hpp"

#include "net/nethernet/Sdp.hpp"
#include "proto/Jose.hpp"

#include <nlohmann/json.hpp>

#include <chrono>
#include <fstream>
#include <iterator>
#include <utility>

namespace jose = crosslink::proto::jose;

namespace crosslink::net::nethernet {
namespace {

using Json = nlohmann::ordered_json;

constexpr std::string_view kIdpDomain = "self";
constexpr std::int64_t kTokenLifetimeSeconds = 3600;

[[nodiscard]] std::int64_t unixNow() {
    return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

[[nodiscard]] Result<Json> parseJson(std::string_view text) {
    try {
        return Json::parse(text);
    } catch (std::exception const& error) {
        return std::unexpected(Error{std::string{"malformed identity JSON: "} + error.what()});
    }
}

[[nodiscard]] std::string jsonString(Json const& object, std::string_view name) {
    const auto found = object.find(name);
    if (found == object.end() || !found->is_string()) return {};
    return found->get<std::string>();
}

/// A detached JWS keeps the header and signature and leaves the payload slot
/// empty: `header..signature`.
[[nodiscard]] Result<std::string> detach(std::string_view compact) {
    const auto first = compact.find('.');
    const auto last = compact.rfind('.');
    if (first == std::string_view::npos || last == std::string_view::npos || first == last) {
        return std::unexpected(Error{"a detached JWS needs three parts"});
    }
    return std::string{compact.substr(0, first)} + ".." + std::string{compact.substr(last + 1)};
}

} // namespace

IdentityKey::IdentityKey(proto::crypto::KeyPair keyPair) : mKeyPair(std::move(keyPair)) {
    mPublicKey = jose::compactKey(mKeyPair.publicKeyPem);
}

Result<IdentityKey> IdentityKey::generate() {
    CROSSLINK_ASSIGN(keyPair, proto::crypto::generateKeyPair());
    return IdentityKey{std::move(*keyPair)};
}

Result<IdentityKey> IdentityKey::loadOrCreate(std::filesystem::path const& path) {
    if (std::filesystem::exists(path)) {
        std::ifstream input{path};
        if (!input) return std::unexpected(Error{"cannot open the NetherNet identity key"});
        const std::string privatePem{std::istreambuf_iterator<char>{input}, std::istreambuf_iterator<char>{}};
        CROSSLINK_ASSIGN(publicPem, jose::publicKeyPem(privatePem));
        return IdentityKey{proto::crypto::KeyPair{.publicKeyPem = *publicPem, .privateKeyPem = privatePem}};
    }

    CROSSLINK_ASSIGN(created, generate());
    std::error_code error;
    std::filesystem::create_directories(path.parent_path(), error);
    std::ofstream output{path, std::ios::binary | std::ios::trunc};
    if (!output) return std::unexpected(Error{"cannot write the NetherNet identity key"});
    output << created->mKeyPair.privateKeyPem;
    output.close();
    if (!output) return std::unexpected(Error{"cannot flush the NetherNet identity key"});
    return created;
}

Result<std::string> IdentityKey::assertion(std::string_view sdp) const {
    const std::string fingerprints = sdp::fingerprintJson(sdp);
    if (fingerprints == "{\"fingerprint\":[]}") {
        return std::unexpected(Error{"the SDP carries no fingerprint to bind an identity to"});
    }

    Json fingerprintHeader;
    fingerprintHeader["alg"] = "ES384";
    CROSSLINK_ASSIGN(fingerprintJws, jose::signCompact(fingerprintHeader, fingerprints, mKeyPair.privateKeyPem));
    CROSSLINK_ASSIGN(detached, detach(*fingerprintJws));

    CROSSLINK_ASSIGN(der, jose::publicKeyDer(mPublicKey));
    const auto now = unixNow();
    Json claims;
    claims["cpk"] = jose::base64Encode(*der);
    claims["iat"] = now;
    claims["exp"] = now + kTokenLifetimeSeconds;
    claims["iss"] = kIdpDomain;
    CROSSLINK_ASSIGN(token, jose::sign(Json::object(), std::move(claims), mKeyPair.privateKeyPem));

    Json inner;
    inner["fingerprints"] = *detached;
    inner["token"] = *token;

    Json idp;
    idp["domain"] = kIdpDomain;
    idp["protocol"] = "default";

    Json envelope;
    envelope["assertion"] = inner.dump();
    envelope["idp"] = std::move(idp);
    return jose::base64Encode(bytesOf(envelope.dump()));
}

Result<> verifyAssertion(std::string_view sdp) {
    const auto value = sdp::identity(sdp);
    if (!value) return std::unexpected(Error{"the SDP carries no identity assertion"});

    CROSSLINK_ASSIGN(envelopeBytes, jose::base64Decode(*value));
    CROSSLINK_ASSIGN(envelope, parseJson(viewOf(*envelopeBytes)));
    const std::string assertion = jsonString(*envelope, "assertion");
    if (assertion.empty()) return std::unexpected(Error{"the identity envelope carries no assertion"});
    CROSSLINK_ASSIGN(inner, parseJson(assertion));

    const std::string token = jsonString(*inner, "token");
    if (token.empty()) return std::unexpected(Error{"the identity assertion carries no token"});
    CROSSLINK_ASSIGN(parsed, jose::parse(token));
    CROSSLINK_ASSIGN(selfSigned, jose::verifySelfSigned(*parsed));

    const std::string cpk = parsed->payloadString("cpk");
    if (cpk.empty()) return std::unexpected(Error{"the identity token carries no cpk"});

    const std::string fingerprints = jsonString(*inner, "fingerprints");
    const auto first = fingerprints.find('.');
    const auto last = fingerprints.rfind('.');
    if (first == std::string::npos || last == std::string::npos || first == last) {
        return std::unexpected(Error{"the identity assertion carries no fingerprint JWS"});
    }

    // Rebuild the signing input from the SDP we actually received: a peer cannot
    // substitute fingerprints without breaking the signature.
    jose::Jwt detached;
    detached.rawHeader = fingerprints.substr(0, first);
    detached.rawPayload = jose::base64UrlEncode(bytesOf(sdp::fingerprintJson(sdp)));
    detached.signature = fingerprints.substr(last + 1);
    detached.header = Json{{"alg", "ES384"}};
    return jose::verify(detached, cpk);
}

} // namespace crosslink::net::nethernet