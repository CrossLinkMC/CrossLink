#include "crosslink/api/proto/ConnectionRequest.hpp"

#include <sculk/protocol/auth/ClientProperties.hpp>
#include <sculk/protocol/auth/ConnectionRequest.hpp>

namespace crosslink::proto::auth {
namespace {

namespace bp = sculk::protocol;

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
    return parsed->toString();
}

} // namespace crosslink::proto::auth
