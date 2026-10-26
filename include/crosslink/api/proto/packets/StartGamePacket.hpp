#pragma once

#include "crosslink/api/proto/TypedPacket.hpp"

#include <cstdint>
#include <string_view>

namespace crosslink::proto {

/// The world entry packet. Everything a handoff has to reconcile — the local
/// player's runtime id, the dimension, the game type, the spawn position — comes
/// from here, which is why the gateway reads it on every backend login.
///
/// Only the fields the gateway needs are exposed. The packet is never
/// re-encoded, so the remaining fields pass through untouched.
class CROSSLINK_API StartGamePacket final : public TypedPacket<StartGamePacket, PacketId::StartGame> {
public:
    static constexpr std::string_view staticName = "StartGamePacket";

    using TypedPacket::TypedPacket;

    [[nodiscard]] std::int64_t  actorUniqueId() const;
    [[nodiscard]] std::uint64_t runtimeId() const;
    [[nodiscard]] GameType      gameType() const;
    /// The level-wide game type, used when `gameType()` is Default.
    [[nodiscard]] GameType      levelGameType() const;
    [[nodiscard]] GameType      effectiveGameType() const;
    [[nodiscard]] std::int32_t  dimension() const;
    [[nodiscard]] Vec3          position() const;

protected:
    Result<> decodeImpl() override;

private:
    std::int64_t  mActorUniqueId{};
    std::uint64_t mRuntimeId{};
    GameType      mGameType{GameType::Undefined};
    GameType      mLevelGameType{GameType::Undefined};
    std::int32_t  mDimension{};
    Vec3          mPosition{};
};

} // namespace crosslink::proto
