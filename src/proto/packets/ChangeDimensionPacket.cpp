#include "crosslink/api/proto/packets/ChangeDimensionPacket.hpp"

#include "proto/SculkBridge.hpp"

#include <sculk/protocol/codec/packet/ChangeDimensionPacket.hpp>

namespace crosslink::proto {
namespace {

namespace bp = bridge::bp;

} // namespace

ChangeDimensionPacket::ChangeDimensionPacket(std::int32_t dimension, Vec3 position, bool respawn)
: mDimension(dimension), mPosition(position), mRespawn(respawn) {}

std::int32_t ChangeDimensionPacket::dimension() const { return mDimension; }

Vec3 ChangeDimensionPacket::position() const { return mPosition; }

bool ChangeDimensionPacket::respawn() const { return mRespawn; }

std::optional<std::uint32_t> ChangeDimensionPacket::loadingScreenId() const { return mLoadingScreenId; }

void ChangeDimensionPacket::setDimension(std::int32_t dimension) {
    mDimension = dimension;
    markDirty();
}

void ChangeDimensionPacket::setPosition(Vec3 position) {
    mPosition = position;
    markDirty();
}

void ChangeDimensionPacket::setRespawn(bool respawn) {
    mRespawn = respawn;
    markDirty();
}

void ChangeDimensionPacket::setLoadingScreenId(std::optional<std::uint32_t> id) {
    mLoadingScreenId = id;
    markDirty();
}

Result<> ChangeDimensionPacket::decodeImpl() {
    auto packet = bridge::decode<bp::ChangeDimensionPacket>(payload());
    if (!packet) return std::unexpected(packet.error());
    mDimension = packet->mDimensionType;
    mPosition = bridge::fromSculk(packet->mPosition);
    mRespawn = packet->mRespawn;
    mLoadingScreenId = packet->mLoadingScreenId;
    return {};
}

Result<> ChangeDimensionPacket::encodeImpl() {
    bp::ChangeDimensionPacket packet;
    packet.mDimensionType = mDimension;
    packet.mPosition = bridge::toSculk(mPosition);
    packet.mRespawn = mRespawn;
    packet.mLoadingScreenId = mLoadingScreenId;
    setSerialized(bridge::serialize(header(), packet), bridge::serializedHeaderSize(header()));
    return {};
}

} // namespace crosslink::proto
