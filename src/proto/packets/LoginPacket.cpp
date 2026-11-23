#include "crosslink/api/proto/packets/LoginPacket.hpp"

#include "proto/EndstoneBridge.hpp"

namespace crosslink::proto {
namespace {

namespace bp = bridge::bp;

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
    mNetworkVersion       = packet->client_network_version;
    mRawConnectionRequest = std::move(packet->connection_request);
    return {};
}

Result<> LoginPacket::encodeImpl() {
    bp::LoginPacket packet;
    packet.client_network_version = mNetworkVersion;
    packet.connection_request     = mRawConnectionRequest;
    setSerialized(bridge::serialize(header(), packet), bridge::serializedHeaderSize(header()));
    return {};
}

} // namespace crosslink::proto
