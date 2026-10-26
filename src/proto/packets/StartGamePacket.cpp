#include "crosslink/api/proto/packets/StartGamePacket.hpp"

#include "proto/SculkBridge.hpp"

#include <sculk/protocol/codec/packet/StartGamePacket.hpp>

namespace crosslink::proto {
namespace {

namespace bp = bridge::bp;

} // namespace

std::int64_t StartGamePacket::actorUniqueId() const { return mActorUniqueId; }

std::uint64_t StartGamePacket::runtimeId() const { return mRuntimeId; }

GameType StartGamePacket::gameType() const { return mGameType; }

GameType StartGamePacket::levelGameType() const { return mLevelGameType; }

GameType StartGamePacket::effectiveGameType() const {
    return mGameType == GameType::Default ? mLevelGameType : mGameType;
}

std::int32_t StartGamePacket::dimension() const { return mDimension; }

Vec3 StartGamePacket::position() const { return mPosition; }

Result<> StartGamePacket::decodeImpl() {
    auto packet = bridge::decode<bp::StartGamePacket>(payload());
    if (!packet) return std::unexpected(packet.error());

    mActorUniqueId = packet->mActorUniqueId;
    mRuntimeId = packet->mActorRuntimeId;
    mGameType = bridge::fromSculk(packet->mGameType);
    mLevelGameType = bridge::fromSculk(packet->mLevelSettings.mGameType);
    mDimension = packet->mLevelSettings.mSpawnSettings.mDimension;
    mPosition = bridge::fromSculk(packet->mPosition);
    return {};
}

} // namespace crosslink::proto
