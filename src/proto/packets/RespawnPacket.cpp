#include "crosslink/api/proto/packets/RespawnPacket.hpp"

#include "proto/EndstoneBridge.hpp"

namespace crosslink::proto {
namespace {

namespace bp = bridge::bp;

bp::PlayerRespawnState toWire(RespawnState state) noexcept {
    return static_cast<bp::PlayerRespawnState>(static_cast<std::uint8_t>(state));
}

RespawnState fromWire(bp::PlayerRespawnState state) noexcept {
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
    mState = fromWire(packet->state);
    mPosition = bridge::fromWire(packet->pos);
    mRuntimeId = packet->runtime_id;
    return {};
}

Result<> RespawnPacket::encodeImpl() {
    bp::RespawnPacket packet;
    packet.state = toWire(mState);
    packet.pos = bridge::toWire(mPosition);
    packet.runtime_id = bp::ActorRuntimeID{mRuntimeId};
    setSerialized(bridge::serialize(header(), packet), bridge::serializedHeaderSize(header()));
    return {};
}

} // namespace crosslink::proto
