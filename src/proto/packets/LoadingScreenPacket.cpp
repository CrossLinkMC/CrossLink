#include "crosslink/api/proto/packets/LoadingScreenPacket.hpp"

#include "proto/SculkBridge.hpp"

#include <sculk/protocol/codec/packet/ServerboundLoadingScreenPacket.hpp>

namespace crosslink::proto {
namespace {

namespace bp = bridge::bp;
using SculkType = bp::ServerboundLoadingScreenPacket::Type;

SculkType toSculk(LoadingScreenType type) noexcept { return static_cast<SculkType>(static_cast<std::int8_t>(type)); }

LoadingScreenType fromSculk(SculkType type) noexcept { return static_cast<LoadingScreenType>(static_cast<std::int8_t>(type)); }

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
    mType = fromSculk(packet->mType);
    mLoadingScreenId = packet->mLoadingScreenId;
    return {};
}

Result<> LoadingScreenPacket::encodeImpl() {
    bp::ServerboundLoadingScreenPacket packet;
    packet.mType = toSculk(mType);
    packet.mLoadingScreenId = mLoadingScreenId;
    setSerialized(bridge::serialize(header(), packet), bridge::serializedHeaderSize(header()));
    return {};
}

} // namespace crosslink::proto
