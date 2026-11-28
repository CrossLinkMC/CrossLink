#include "crosslink/api/proto/ConnectionRequest.hpp"

#include "proto/Jose.hpp"

#include <openssl/evp.h>

#include <array>
#include <charconv>
#include <chrono>
#include <cstdint>
#include <cstring>
#include <format>
#include <optional>
#include <string>
#include <utility>
#include <vector>

namespace crosslink::proto::auth {
namespace {

using Json = jose::Json;

constexpr std::string_view kAudience = "api://auth-minecraft-services/multiplayer";
/// A chain of one placeholder link is how a client says "no legacy chain".
constexpr std::string_view kEmptyChain = "{\"chain\":[\"..\"]}";

/// The blob inside Login is two int32 little-endian length-prefixed strings: the
/// authentication JSON (with a trailing newline counted in its length), then the
/// signed client properties JWT.
struct AuthBlob {
    std::string authJson;
    std::string clientProperties;
};

[[nodiscard]] Result<AuthBlob> split(std::string_view raw) {
    AuthBlob blob;
    std::size_t offset = 0;
    for (std::size_t index = 0; index < 2; ++index) {
        if (raw.size() - offset < 4) return std::unexpected(Error{"the connection request ended inside a length"});
        std::uint32_t length = 0;
        for (std::size_t byte = 0; byte < 4; ++byte) {
            length |= static_cast<std::uint32_t>(static_cast<unsigned char>(raw[offset + byte])) << (8U * byte);
        }
        offset += 4;
        if (length > raw.size() - offset) {
            return std::unexpected(Error{"the connection request ended inside a string"});
        }
        auto& part = index == 0 ? blob.authJson : blob.clientProperties;
        part = std::string{raw.substr(offset, length)};
        offset += length;
    }
    return blob;
}

[[nodiscard]] std::string frame(std::string_view authJson, std::string_view clientProperties) {
    std::string out;
    out.reserve(authJson.size() + clientProperties.size() + 8);
    for (const auto part : {authJson, clientProperties}) {
        const auto length = static_cast<std::uint32_t>(part.size());
        for (std::size_t byte = 0; byte < 4; ++byte) {
            out.push_back(static_cast<char>((length >> (8U * byte)) & 0xFFU));
        }
        out.append(part);
    }
    return out;
}

[[nodiscard]] Result<Json> parseJson(std::string_view text) {
    try {
        return Json::parse(text);
    } catch (std::exception const& error) {
        return std::unexpected(Error{std::string{"malformed authentication JSON: "} + error.what()});
    }
}

[[nodiscard]] std::string jsonString(Json const& object, std::string_view name) {
    const auto found = object.find(name);
    if (found == object.end() || !found->is_string()) return {};
    return found->get<std::string>();
}

[[nodiscard]] std::int64_t jsonInt(Json const& object, std::string_view name, std::int64_t fallback = 0) {
    const auto found = object.find(name);
    if (found == object.end() || !found->is_number_integer()) return fallback;
    return found->get<std::int64_t>();
}

[[nodiscard]] bool isDecimal(std::string_view text) {
    if (text.empty()) return false;
    std::uint64_t value = 0;
    const auto* end = text.data() + text.size();
    const auto result = std::from_chars(text.data(), end, value);
    return result.ec == std::errc{} && result.ptr == end;
}

[[nodiscard]] std::int64_t unixNow() {
    return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

[[nodiscard]] std::string randomUuid() {
    auto bytes = jose::randomBytes(16);
    if (!bytes) return {};
    auto& data = *bytes;
    data[6] = static_cast<std::byte>((static_cast<unsigned char>(data[6]) & 0x0FU) | 0x40U);
    data[8] = static_cast<std::byte>((static_cast<unsigned char>(data[8]) & 0x3FU) | 0x80U);
    std::string hex;
    hex.reserve(32);
    for (const auto byte : data) {
        hex += std::format("{:02x}", static_cast<unsigned char>(byte));
    }
    return std::format("{}-{}-{}-{}-{}", hex.substr(0, 8), hex.substr(8, 4), hex.substr(12, 4), hex.substr(16, 4), hex.substr(20, 12));
}

/// The offline UUID Mojang derives from an XUID: MD5 of a fixed prefix plus the
/// decimal id, with the version and variant nibbles forced to UUID v3.
[[nodiscard]] std::string identityFromXuid(std::string_view xuid) {
    const std::string input = std::format("pocket-auth-1-xuid:{}", xuid);
    std::array<unsigned char, EVP_MAX_MD_SIZE> digest{};
    unsigned int length = 0;
    if (EVP_Digest(input.data(), input.size(), digest.data(), &length, EVP_md5(), nullptr) != 1 || length < 16) {
        return {};
    }
    digest[6] = static_cast<unsigned char>((digest[6] & 0x0FU) | 0x30U);
    digest[8] = static_cast<unsigned char>((digest[8] & 0x3FU) | 0x80U);
    std::string hex;
    for (std::size_t index = 0; index < 16; ++index) hex += std::format("{:02x}", digest[index]);
    return std::format("{}-{}-{}-{}-{}", hex.substr(0, 8), hex.substr(8, 4), hex.substr(12, 4), hex.substr(16, 4), hex.substr(20, 12));
}

/// Everything the gateway reads out of one connection request.
struct Request {
    Json                   auth;
    jose::Jwt              properties;
    std::optional<jose::Jwt> token;
    /// The legacy chain's leaf certificate: the link that carries extraData.
    std::optional<jose::Jwt> leaf;
    std::vector<std::string> chainLinks;
    bool                   hasTopLevelIdentityKey{};
    std::string            topLevelIdentityKey;
};

[[nodiscard]] Result<Request> parse(std::string_view raw) {
    CROSSLINK_ASSIGN(blob, split(raw));
    CROSSLINK_ASSIGN(auth, parseJson(blob->authJson));
    if (!auth->is_object()) return std::unexpected(Error{"the authentication JSON is not an object"});
    CROSSLINK_ASSIGN(properties, jose::parse(blob->clientProperties));

    Request request;
    request.auth = std::move(*auth);
    request.properties = std::move(*properties);

    if (const auto token = jsonString(request.auth, "Token"); !token.empty()) {
        auto parsed = jose::parse(token);
        if (parsed) request.token = std::move(*parsed);
    }

    // The chain may sit in a "Certificate" string (modern) or directly under
    // "chain" (legacy). Both are an object holding an array of JWT strings.
    std::string chainText = jsonString(request.auth, "Certificate");
    if (chainText.empty()) {
        if (request.auth.contains("chain") && request.auth["chain"].is_array()) {
            chainText = request.auth["chain"].dump();
            chainText = std::format("{{\"chain\":{}}}", chainText);
        }
    }
    if (!chainText.empty() && chainText.find(kEmptyChain) == std::string::npos) {
        if (auto chain = parseJson(chainText); chain && chain->is_object()) {
            const auto links = chain->find("chain");
            if (links != chain->end() && links->is_array()) {
                for (auto const& link : *links) {
                    if (!link.is_string()) continue;
                    auto text = link.get<std::string>();
                    auto parsed = jose::parse(text);
                    if (!parsed) continue;
                    if (parsed->payload.contains("extraData") && !request.leaf) request.leaf = *parsed;
                    request.chainLinks.push_back(std::move(text));
                }
            }
        }
    }

    request.topLevelIdentityKey = jsonString(request.auth, "identityPublicKey");
    request.hasTopLevelIdentityKey = request.auth.contains("identityPublicKey");
    return request;
}

[[nodiscard]] std::string extraDataString(Request const& request, std::string_view name) {
    if (!request.leaf) return {};
    const auto extra = request.leaf->payload.find("extraData");
    if (extra == request.leaf->payload.end() || !extra->is_object()) return {};
    return jsonString(*extra, name);
}

} // namespace

PlayerIdentity ConnectionRequestView::toIdentity() const {
    PlayerIdentity result;
    result.xuid = xuid;
    result.name = name;
    result.playFabId = playFabId;
    result.identity = !identity.empty() ? identity : selfSignedId;
    return result;
}

Result<ConnectionRequestView> inspect(std::string_view rawConnectionRequest) {
    CROSSLINK_ASSIGN(request, parse(rawConnectionRequest));

    ConnectionRequestView view;
    const auto& properties = request->properties.payload;

    view.deviceId = jsonString(properties, "DeviceId");
    view.deviceModel = jsonString(properties, "DeviceModel");
    view.selfSignedId = jsonString(properties, "SelfSignedId");
    view.serverAddress = jsonString(properties, "ServerAddress");
    view.gameVersion = jsonString(properties, "GameVersion");
    view.platformType = static_cast<int>(jsonInt(properties, "PlatformType"));
    view.name = jsonString(properties, "ThirdPartyName");
    view.playFabId = jsonString(properties, "PlayFabId");
    view.clientPublicKey = request->properties.headerString("x5u");

    if (request->token) {
        const auto& claims = request->token->payload;
        if (const auto xuid = jsonString(claims, "xid"); isDecimal(xuid)) {
            view.xuid = xuid;
            view.onlineAuthenticated = request->token->headerString("alg") == "RS256";
        }
        if (const auto name = jsonString(claims, "xname"); !name.empty()) view.name = name;
        if (const auto mid = jsonString(claims, "mid"); !mid.empty()) view.playFabId = mid;
        if (view.clientPublicKey.empty()) view.clientPublicKey = jsonString(claims, "cpk");
    }

    // A legacy chain states the Xbox identity explicitly, and wins over the token.
    if (const auto xuid = extraDataString(*request, "XUID"); isDecimal(xuid)) {
        view.xuid = xuid;
        view.onlineAuthenticated = true;
    }
    if (const auto name = extraDataString(*request, "displayName"); !name.empty()) view.name = name;
    if (view.clientPublicKey.empty() && request->leaf) {
        view.clientPublicKey = request->leaf->payloadString("identityPublicKey");
    }

    view.identity = !view.xuid.empty() ? identityFromXuid(view.xuid) : view.selfSignedId;
    return view;
}

Result<std::string> resign(ResignRequest const& request) {
    CROSSLINK_ASSIGN(parsed, parse(request.rawConnectionRequest));
    if (parsed->properties.headerString("x5u").empty()) {
        return std::unexpected(Error{"the connection request carries no client public key"});
    }

    const std::string publicKey = jose::compactKey(request.keyPair.publicKeyPem);
    const auto now = unixNow();

    // A self-signed token replayed to another backend. Every claim the client
    // sent survives except the ones that name a key we no longer hold.
    Json claims;
    if (parsed->token) claims = parsed->token->payload;
    claims["cpk"] = publicKey;
    claims["ap"] = 0;
    claims["aud"] = kAudience;
    claims["exp"] = now + 365 * 24 * 3600;
    if (!claims.contains("mid")) claims["mid"] = jsonString(parsed->properties.payload, "PlayFabId");
    if (!claims.contains("xid")) claims["xid"] = "";
    if (!claims.contains("xname")) claims["xname"] = jsonString(parsed->properties.payload, "ThirdPartyName");
    if (!claims.contains("leguuid") || jsonString(claims, "leguuid").empty()) claims["leguuid"] = randomUuid();
    for (const auto* name : {"nid", "nname", "pid", "pname"}) {
        if (!claims.contains(name)) claims[name] = "";
    }
    claims.erase("sub");
    claims.erase("ipt");
    claims.erase("tid");
    claims.erase("pfcd");
    claims.erase("iss");
    claims.erase("iat");
    CROSSLINK_ASSIGN(token, jose::sign(Json::object(), std::move(claims), request.keyPair.privateKeyPem));

    // Re-sign the client properties with their payload untouched, so no claim the
    // backend or a trusted agent reads is lost to a re-serialization.
    Json properties = parsed->properties.payload;
    if (request.deviceIdOverride) properties["DeviceId"] = *request.deviceIdOverride;
    if (request.deviceModelOverride) properties["DeviceModel"] = *request.deviceModelOverride;
    CROSSLINK_ASSIGN(signedProperties, jose::sign(parsed->properties.header, std::move(properties), request.keyPair.privateKeyPem));

    Json auth;
    auth["AuthenticationType"] = 2; // SelfSigned
    auth["Token"] = *token;

    if (parsed->leaf) {
        Json leaf = parsed->leaf->payload;
        leaf["identityPublicKey"] = publicKey;
        leaf["nbf"] = now;
        leaf["exp"] = now + 24 * 3600;
        if (leaf.contains("iat")) leaf["iat"] = now;
        CROSSLINK_ASSIGN(signedLeaf, jose::sign(parsed->leaf->header, std::move(leaf), request.keyPair.privateKeyPem));
        Json chain;
        chain["chain"] = Json::array({*signedLeaf});
        auth["Certificate"] = chain.dump() + "\n";
    }

    // Some backend builds read the connecting client's ECDH key from this legacy
    // top-level claim rather than from the token. Without it they have no key for
    // the session and silently drop the encrypted handshake forever.
    if (parsed->hasTopLevelIdentityKey) auth["identityPublicKey"] = publicKey;

    std::string authJson = auth.dump();
    authJson.push_back('\n');
    return frame(authJson, *signedProperties);
}

std::string keyFingerprint(std::string_view key) {
    // PEM markers are decoration: both the PEM and the compact base64 form of the
    // same key must fingerprint identically, and every P-384 key shares its first
    // DER bytes, so a prefix is worthless here. Hash the base64 body instead.
    const std::string compact = jose::compactKey(key);
    std::uint64_t hash = 14695981039346656037ULL;
    for (const char ch : compact) {
        hash ^= static_cast<std::uint8_t>(ch);
        hash *= 1099511628211ULL;
    }
    return std::format("{:08x}({})", static_cast<std::uint32_t>(hash >> 32U), compact.size());
}

std::string describeAuthentication(std::string_view rawConnectionRequest) {
    auto request = parse(rawConnectionRequest);
    if (!request) return "unparsable connection request";

    std::string out = std::format("authType={}", jsonInt(request->auth, "AuthenticationType", -1));
    if (request->token) {
        out += std::format(
            " token.alg={} token.x5u={} token.cpk={}",
            request->token->headerString("alg"),
            keyFingerprint(request->token->headerString("x5u")),
            keyFingerprint(request->token->payloadString("cpk"))
        );
    } else {
        out += " token=<none>";
    }
    out += std::format(" props.x5u={}", keyFingerprint(request->properties.headerString("x5u")));

    if (!request->chainLinks.empty()) {
        out += std::format(" chain={} links", request->chainLinks.size());
        if (request->leaf) {
            out += std::format(
                " leaf.identityPublicKey={} leaf.XUID={}",
                keyFingerprint(request->leaf->payloadString("identityPublicKey")),
                extraDataString(*request, "XUID")
            );
        }
    } else {
        out += " chain=no";
    }

    out += " members=[";
    bool first = true;
    for (auto const& [name, value] : request->auth.items()) {
        out += first ? "" : ",";
        out += name;
        first = false;
    }
    out += "]";
    out += request->hasTopLevelIdentityKey
             ? std::format(" identityPublicKey={}", keyFingerprint(request->topLevelIdentityKey))
             : " identityPublicKey=<absent>";
    return out;
}

} // namespace crosslink::proto::auth