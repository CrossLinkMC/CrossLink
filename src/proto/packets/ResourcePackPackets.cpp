#include "crosslink/api/proto/packets/ResourcePackPackets.hpp"

#include "proto/SculkBridge.hpp"

#include <sculk/protocol/codec/packet/ResourcePackClientResponsePacket.hpp>

namespace crosslink::proto {
namespace {

namespace bp = bridge::bp;

} // namespace

ResourcePackClientResponsePacket::ResourcePackClientResponsePacket(ResourcePackResponse response) : mResponse(response) {}

ResourcePackResponse ResourcePackClientResponsePacket::response() const { return mResponse; }

void ResourcePackClientResponsePacket::setResponse(ResourcePackResponse response) {
    mResponse = response;
    markDirty();
}

Result<> ResourcePackClientResponsePacket::decodeImpl() {
    auto packet = bridge::decode<bp::ResourcePackClientResponsePacket>(payload());
    if (!packet) return std::unexpected(packet.error());
    mResponse = static_cast<ResourcePackResponse>(packet->mResponse);
    return {};
}

Result<> ResourcePackClientResponsePacket::encodeImpl() {
    bp::ResourcePackClientResponsePacket packet;
    packet.mResponse = static_cast<std::uint8_t>(mResponse);
    setSerialized(bridge::serialize(header(), packet), bridge::serializedHeaderSize(header()));
    return {};
}

} // namespace crosslink::proto
