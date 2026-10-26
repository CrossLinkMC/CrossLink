#include "crosslink/api/proto/packets/RespawnPacket.hpp"

#include "proto/SculkBridge.hpp"

#include <sculk/protocol/codec/packet/RespawnPacket.hpp>

namespace crosslink::proto {
namespace {

namespace bp = bridge::bp;

bp::RespawnPacket::PlayerRespawnState toSculk(RespawnState state) noexcept {
    return static_cast<bp::RespawnPacket::PlayerRespawnState>(static_cast<std::uint8_t>(state));
}

RespawnState fromSculk(bp::RespawnPacket::PlayerRespawnState state) noexcept {
    return static_cast<RespawnState>(static_cast<std::uint8_t>(state));
}

} // namespace

RespawnPacket::RespawnPacket(RespawnState state, Vec3 position, std::uint64_t runtimeId)
: mState(state), mPosition(position), mRuntimeId(runtimeId) {}

RespawnState RespawnPacket::state() const { return mState; }

Vec3 RespawnPacket::position() const { return mPosition; }

std::uint64_t RespawnPacket::runtimeId() const { return mRuntimeId; }

void RespawnPacket::setState(RespawnState state) {
    mState = state;
    markDirty();
}

void RespawnPacket::setPosition(Vec3 position) {
    mPosition = position;
    markDirty();
}

void RespawnPacket::setRuntimeId(std::uint64_t runtimeId) {
    mRuntimeId = runtimeId;
    markDirty();
}

Result<> RespawnPacket::decodeImpl() {
    auto packet = bridge::decode<bp::RespawnPacket>(payload());
    if (!packet) return std::unexpected(packet.error());
    mState = fromSculk(packet->mState);
    mPosition = bridge::fromSculk(packet->mPosition);
    mRuntimeId = packet->mActorRuntimeId;
    return {};
}

Result<> RespawnPacket::encodeImpl() {
    bp::RespawnPacket packet;
    packet.mState = toSculk(mState);
    packet.mPosition = bridge::toSculk(mPosition);
    packet.mActorRuntimeId = mRuntimeId;
    setSerialized(bridge::serialize(header(), packet), bridge::serializedHeaderSize(header()));
    return {};
}

} // namespace crosslink::proto
