#include "crosslink/api/proto/packets/LoginPacket.hpp"

#include "proto/SculkBridge.hpp"

#include <sculk/protocol/auth/ConnectionRequest.hpp>
#include <sculk/protocol/codec/packet/LoginPacket.hpp>

namespace crosslink::proto {
namespace {

namespace bp = bridge::bp;

Result<bp::ConnectionRequest> parseRequest(std::string const& raw) {
    auto request = bp::ConnectionRequest::fromString(raw);
    if (!request) return std::unexpected(bridge::convertError(request));
    return std::move(*request);
}

} // namespace

std::int32_t LoginPacket::networkVersion() const { return mNetworkVersion; }

std::string const& LoginPacket::rawConnectionRequest() const { return mRawConnectionRequest; }

void LoginPacket::setRawConnectionRequest(std::string raw) {
    mRawConnectionRequest = std::move(raw);
    markDirty();
}

Result<auth::ConnectionRequestView> LoginPacket::inspect() const { return auth::inspect(mRawConnectionRequest); }

Result<> LoginPacket::resign(
    crypto::KeyPair const&     keyPair,
    std::optional<std::string> deviceIdOverride,
    std::optional<std::string> deviceModelOverride
) {
    auth::ResignRequest request;
    request.rawConnectionRequest = mRawConnectionRequest;
    request.keyPair = keyPair;
    request.deviceIdOverride = std::move(deviceIdOverride);
    request.deviceModelOverride = std::move(deviceModelOverride);

    auto resigned = auth::resign(request);
    if (!resigned) return std::unexpected(resigned.error());

    mRawConnectionRequest = std::move(*resigned);
    markDirty();
    return {};
}

Result<> LoginPacket::decodeImpl() {
    auto packet = bridge::decode<bp::LoginPacket>(payload());
    if (!packet) return std::unexpected(packet.error());
    mNetworkVersion = packet->mNetworkVersion;
    mRawConnectionRequest = std::move(packet->mRawConnectionRequest);
    return {};
}

Result<> LoginPacket::encodeImpl() {
    bp::LoginPacket packet;
    packet.mNetworkVersion = mNetworkVersion;
    packet.mRawConnectionRequest = mRawConnectionRequest;
    setSerialized(bridge::serialize(header(), packet), bridge::serializedHeaderSize(header()));
    return {};
}

} // namespace crosslink::proto
