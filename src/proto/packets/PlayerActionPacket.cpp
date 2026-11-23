#include "crosslink/api/proto/packets/PlayerActionPacket.hpp"

#include "proto/EndstoneBridge.hpp"

namespace crosslink::proto {
namespace {

namespace bp = bridge::bp;

using ActionType = bp::v2168::PlayerActionType;

} // namespace

std::int32_t PlayerActionPacket::action() const { return mAction; }

std::uint64_t PlayerActionPacket::runtimeId() const { return mRuntimeId; }

std::int32_t PlayerActionPacket::positionX() const { return mPositionX; }

std::int32_t PlayerActionPacket::positionY() const { return mPositionY; }

std::int32_t PlayerActionPacket::positionZ() const { return mPositionZ; }

std::int32_t PlayerActionPacket::face() const { return mFace; }

bool PlayerActionPacket::isRespawn() const { return mAction == static_cast<std::int32_t>(ActionType::Respawn); }

bool PlayerActionPacket::isDimensionChangeAck() const {
    return mAction == static_cast<std::int32_t>(ActionType::ChangeDimensionAck);
}

void PlayerActionPacket::setRuntimeId(std::uint64_t runtimeId) {
    mRuntimeId = runtimeId;
    markDirty();
}

Result<> PlayerActionPacket::decodeImpl() {
    auto packet = bridge::decode<bp::PlayerActionPacket>(payload());
    if (!packet) return std::unexpected(packet.error());
    mAction = static_cast<std::int32_t>(packet->action);
    mRuntimeId = packet->runtime_id;
    mPositionX = packet->pos.x;
    mPositionY = packet->pos.y;
    mPositionZ = packet->pos.z;
    mFace = packet->face;
    return {};
}

Result<> PlayerActionPacket::encodeImpl() {
    auto rewritten =
        bridge::modify<bp::PlayerActionPacket>(header(), payload(), [this](bp::PlayerActionPacket& packet) {
            packet.runtime_id = bp::ActorRuntimeID{mRuntimeId};
        });
    if (!rewritten) return std::unexpected(rewritten.error());
    setSerialized(std::move(*rewritten), bridge::serializedHeaderSize(header()));
    return {};
}

} // namespace crosslink::proto
