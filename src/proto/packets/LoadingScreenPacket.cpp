#include "crosslink/api/proto/packets/LoadingScreenPacket.hpp"

#include "proto/EndstoneBridge.hpp"

namespace crosslink::proto {
namespace {

namespace bp = bridge::bp;
using WireType = bp::ServerboundLoadingScreenPacketType;

WireType toWire(LoadingScreenType type) noexcept { return static_cast<WireType>(static_cast<std::int8_t>(type)); }

LoadingScreenType fromWire(WireType type) noexcept { return static_cast<LoadingScreenType>(static_cast<std::int8_t>(type)); }

} // namespace

LoadingScreenPacket::LoadingScreenPacket(LoadingScreenType type, std::optional<std::uint32_t> loadingScreenId)
: mType(type), mLoadingScreenId(loadingScreenId) {}

LoadingScreenType LoadingScreenPacket::type() const { return mType; }

std::optional<std::uint32_t> LoadingScreenPacket::loadingScreenId() const { return mLoadingScreenId; }

void LoadingScreenPacket::setType(LoadingScreenType type) {
    mType = type;
    markDirty();
}

void LoadingScreenPacket::setLoadingScreenId(std::optional<std::uint32_t> id) {
    mLoadingScreenId = id;
    markDirty();
}

Result<> LoadingScreenPacket::decodeImpl() {
    auto packet = bridge::decode<bp::ServerboundLoadingScreenPacket>(payload());
    if (!packet) return std::unexpected(packet.error());
    mType = fromWire(packet->loading_screen_packet_type);
    mLoadingScreenId = packet->loading_screen_id;
    return {};
}

Result<> LoadingScreenPacket::encodeImpl() {
    bp::ServerboundLoadingScreenPacket packet;
    packet.loading_screen_packet_type = toWire(mType);
    packet.loading_screen_id = mLoadingScreenId;
    setSerialized(bridge::serialize(header(), packet), bridge::serializedHeaderSize(header()));
    return {};
}

} // namespace crosslink::proto
