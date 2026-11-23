#include "crosslink/api/proto/ConnectionRequest.hpp"

#include <cstdint>
#include <cstring>
#include <format>
#include <optional>
#include <string>
#include <vector>

#include <sculk/protocol/auth/ClientProperties.hpp>
#include <sculk/protocol/auth/ConnectionRequest.hpp>
#include <sculk/protocol/auth/LegacyCertificateChain.hpp>
#include <sculk/protocol/auth/LoginToken.hpp>
#include <sculk/protocol/utility/BinaryStream.hpp>
#include <sculk/protocol/utility/ReadOnlyBinaryStream.hpp>

namespace crosslink::proto::auth {
namespace {

namespace bp = sculk::protocol;

/// The authentication JSON is a flat one-line object; only its top-level members
/// matter here, so a small depth- and quote-aware scan beats pulling in the JSON
/// library's typed accessors.
struct AuthJsonShape {
    std::vector<std::string> members{};
    std::string              identityPublicKey{};
    bool                     hasIdentityPublicKey = false;
    bool                     identityIsText       = false;
};

[[nodiscard]] std::string authJsonOf(std::string_view rawConnectionRequest) {
    bp::ReadOnlyBinaryStream stream(rawConnectionRequest);
    std::string              json{};
    if (!stream.readLongString(json)) return {};
    return json;
}

[[nodiscard]] std::vector<std::string> clientPropertiesOf(std::string_view rawConnectionRequest) {
    // The request is two length-prefixed strings: the authentication JSON, then the
    // signed client properties. Both have to survive a re-frame untouched.
    bp::ReadOnlyBinaryStream     stream(rawConnectionRequest);
    std::vector<std::string>     parts{};
    std::string                  value{};
    while (stream.readLongString(value)) parts.push_back(std::move(value));
    return parts;
}

[[nodiscard]] AuthJsonShape describeAuthJson(std::string_view json) {
    AuthJsonShape shape;
    int                  depth = 0;
    bool                 inText = false;
    bool                 escaped = false;
    std::optional<bool>  pendingIsKey{};
    std::string          current{};
    std::string          key{};
    bool                 afterColon = false;

    for (const char ch : json) {
        if (inText) {
            if (escaped) {
                escaped = false;
            } else if (ch == '\\') {
                escaped = true;
            } else if (ch == '"') {
                inText = false;
                if (depth == 1 && !afterColon) {
                    key = current;
                    pendingIsKey = true;
                } else if (depth == 1 && afterColon && key == "identityPublicKey") {
                    shape.hasIdentityPublicKey = true;
                    shape.identityIsText = true;
                    shape.identityPublicKey = current;
                }
                current.clear();
                continue;
            }
            current.push_back(ch);
            continue;
        }

        switch (ch) {
        case '{':
        case '[':
            ++depth;
            break;
        case '}':
        case ']':
            --depth;
            break;
        case '"':
            inText = true;
            current.clear();
            break;
        case ':':
            if (depth == 1 && pendingIsKey) {
                shape.members.push_back(key);
                if (key == "identityPublicKey") shape.hasIdentityPublicKey = true;
                afterColon = true;
                pendingIsKey.reset();
            }
            break;
        case ',':
            if (depth == 1) {
                afterColon = false;
                key.clear();
            }
            break;
        default:
            break;
        }
    }
    return shape;
}

[[nodiscard]] std::string compactKey(std::string_view key) {
    std::string body{key};
    for (std::size_t open = body.find("-----"); open != std::string::npos; open = body.find("-----")) {
        const auto close = body.find("-----", open + 5);
        if (close == std::string::npos) break;
        body.erase(open, close + 5 - open);
    }
    std::string compact;
    compact.reserve(body.size());
    for (const char ch : body) {
        if (ch == '\r' || ch == '\n' || ch == ' ' || ch == '\t') continue;
        compact.push_back(ch);
    }
    return compact;
}

/// Re-frames a serialized connection request with a top-level identityPublicKey
/// claim, which is what a backend reads the connecting client's ECDH key from.
[[nodiscard]] std::string withIdentityPublicKey(std::string_view serialized, std::string_view compactKey) {
    auto parts = clientPropertiesOf(serialized);
    if (parts.empty()) return std::string{serialized};

    auto& json = parts.front();
    if (json.empty() || json.front() != '{') return std::string{serialized};
    if (const auto at = json.find("\"identityPublicKey\""); at != std::string_view::npos && at < json.find(':')) {
        return std::string{serialized};  // the library already emitted one
    }

    json.insert(1, std::format("\"identityPublicKey\":\"{}\",", compactKey));

    std::vector<std::byte> buffer{};
    bp::BinaryStream       stream(buffer);
    stream.writeLongString(json);
    for (std::size_t index = 1; index < parts.size(); ++index) stream.writeLongString(parts[index]);

    std::string out{};
    out.resize_and_overwrite(buffer.size(), [&buffer](char* data, std::size_t size) {
        std::memcpy(data, buffer.data(), size);
        return size;
    });
    return out;
}

Result<bp::ConnectionRequest> parse(std::string_view raw) {
    auto request = bp::ConnectionRequest::fromString(raw);
    if (!request) {
        return std::unexpected(Error{"could not decode the connection request: " + std::string{request.error().message()}});
    }
    return std::move(*request);
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
    auto request = parse(rawConnectionRequest);
    if (!request) return std::unexpected(request.error());

    ConnectionRequestView view;
    if (const auto xuid = request->getXboxLiveID(); xuid && !xuid->empty()) {
        view.xuid = *xuid;
        view.onlineAuthenticated = true;
    }
    view.name = request->getXboxLiveName();
    view.playFabId = request->getPlayFabID();
    view.identity = request->getIdentity().toString();
    view.clientPublicKey = request->getClientPublicKey();

    auto const& properties = request->mClientProperties;
    view.deviceId = properties.getDeviceId();
    view.deviceModel = properties.getDeviceModel();
    view.selfSignedId = properties.getSelfSignedId();
    view.serverAddress = properties.getServerAddress();
    view.gameVersion = properties.getGameVersion();
    view.platformType = properties.mPayload.mPlatformType;

    if (view.name.empty()) view.name = properties.mPayload.mThirdPartyName;
    if (view.clientPublicKey.empty()) view.clientPublicKey = properties.mHeader.x5u;
    if (view.identity.empty()) view.identity = view.selfSignedId;

    return view;
}

Result<std::string> resign(ResignRequest const& request) {
    auto parsed = parse(request.rawConnectionRequest);
    if (!parsed) return std::unexpected(parsed.error());

    if (parsed->getClientPublicKey().empty()) {
        return std::unexpected(Error{"the connection request carries no client public key"});
    }

    if (request.deviceIdOverride) parsed->mClientProperties.mPayload.mDeviceId = *request.deviceIdOverride;
    if (request.deviceModelOverride) parsed->mClientProperties.mPayload.mDeviceModel = *request.deviceModelOverride;

    const bp::PemKeyPair keyPair{
        .mPublicKeyPem  = request.keyPair.publicKeyPem,
        .mPrivateKeyPem = request.keyPair.privateKeyPem,
    };
    if (const auto status = parsed->selfSign(keyPair); !status) {
        return std::unexpected(Error{"could not re-sign the connection request: " + std::string{status.error().message()}});
    }

    // selfSign re-serializes from the three fields the library models, so every
    // other top-level claim the client sent is gone - including the legacy
    // identityPublicKey that a backend reads the connecting client's ECDH key
    // from. Without it the backend has no key for the session and silently drops
    // the encrypted ClientToServerHandshake forever.
    auto serialized = parsed->toString();
    if (const auto original = describeAuthJson(authJsonOf(request.rawConnectionRequest)); original.hasIdentityPublicKey) {
        serialized = withIdentityPublicKey(serialized, compactKey(request.keyPair.publicKeyPem));
    }
    return serialized;
}

std::string keyFingerprint(std::string_view key) {
    // PEM markers are decoration: both the PEM and the compact base64 form of the
    // same key must fingerprint identically, and every P-384 key shares its first
    // DER bytes, so a prefix is worthless here. Hash the base64 body instead.
    std::string body{key};
    for (std::size_t open = body.find("-----"); open != std::string::npos; open = body.find("-----")) {
        const auto close = body.find("-----", open + 5);
        if (close == std::string::npos) break;
        body.erase(open, close + 5 - open);
    }

    std::string compact;
    compact.reserve(body.size());
    for (const char ch : body) {
        if (ch == '\r' || ch == '\n' || ch == ' ' || ch == '\t') continue;
        compact.push_back(ch);
    }

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

    const auto& token = request->mLoginToken;
    std::string out = std::format(
        "authType={} token.x5u={} token.cpk={} props.x5u={}",
        static_cast<int>(request->mAuthenticationType),
        token.mHeader.x5u ? keyFingerprint(*token.mHeader.x5u) : std::string{"<none>"},
        keyFingerprint(token.mPayload.cpk),
        keyFingerprint(request->mClientProperties.mHeader.x5u)
    );

    if (const auto& chain = request->mLegacyCertificateChain; chain) {
        out += std::format(" chain=yes chain.login.x5u={}", keyFingerprint(chain->mLoginCertificate.mHeader.x5u));
        out += std::format(" chain.identityPublicKey={}", keyFingerprint(chain->getClientPublicKey()));
        if (chain->mClientCertificate) {
            out += std::format(
                " chain.client.iss={} chain.client.identity={}",
                chain->mClientCertificate->mPayload.iss ? *chain->mClientCertificate->mPayload.iss : std::string{"<none>"},
                keyFingerprint(chain->mClientCertificate->mPayload.identityPublicKey)
            );
        }
    } else {
        out += " chain=no";
    }

    const auto shape = describeAuthJson(authJsonOf(rawConnectionRequest));
    out += " members=[";
    for (std::size_t index = 0; index < shape.members.size(); ++index) {
        out += index == 0 ? "" : ",";
        out += shape.members[index];
    }
    out += "]";
    if (shape.hasIdentityPublicKey) {
        out += std::format(" identityPublicKey={} {}", keyFingerprint(shape.identityPublicKey), shape.identityIsText ? "text" : "raw");
    } else {
        out += " identityPublicKey=<absent>";
    }
    return out;
}

} // namespace crosslink::proto::auth
