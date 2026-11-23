#include "crosslink/api/proto/packets/ResourcePackPackets.hpp"

#include "proto/EndstoneBridge.hpp"

#include <variant>

namespace crosslink::proto {
namespace {

namespace bp = bridge::bp;

using WirePacket = bp::ResourcePackClientResponsePacket;

} // namespace

ResourcePackClientResponsePacket::ResourcePackClientResponsePacket(ResourcePackResponse response) : mResponse(response) {}

ResourcePackResponse ResourcePackClientResponsePacket::response() const { return mResponse; }

void ResourcePackClientResponsePacket::setResponse(ResourcePackResponse response) {
    mResponse = response;
    markDirty();
}

Result<> ResourcePackClientResponsePacket::decodeImpl() {
    auto packet = bridge::decode<WirePacket>(payload());
    if (!packet) return std::unexpected(packet.error());

    // The answer is a variant of one tag type per state, so the alternative in
    // play is the state.
    if (const auto* downloading = std::get_if<WirePacket::Downloading>(&packet->response)) {
        mResponse         = ResourcePackResponse::SendPacks;
        mDownloadingPacks = downloading->downloading_packs;
    } else if (std::holds_alternative<WirePacket::Cancel>(packet->response)) {
        mResponse = ResourcePackResponse::Refused;
    } else if (std::holds_alternative<WirePacket::DownloadingFinished>(packet->response)) {
        mResponse = ResourcePackResponse::HaveAllPacks;
    } else {
        mResponse = ResourcePackResponse::Completed;
    }
    return {};
}

Result<> ResourcePackClientResponsePacket::encodeImpl() {
    WirePacket packet;
    switch (mResponse) {
    case ResourcePackResponse::Refused:
        packet.response = WirePacket::Cancel{};
        break;
    case ResourcePackResponse::SendPacks:
        packet.response = WirePacket::Downloading{{mDownloadingPacks}};
        break;
    case ResourcePackResponse::HaveAllPacks:
        packet.response = WirePacket::DownloadingFinished{};
        break;
    case ResourcePackResponse::Completed:
        packet.response = WirePacket::ResourcePackStackFinished{};
        break;
    }
    setSerialized(bridge::serialize(header(), packet), bridge::serializedHeaderSize(header()));
    return {};
}

} // namespace crosslink::proto
