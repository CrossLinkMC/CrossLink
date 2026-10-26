#pragma once

#include "crosslink/api/proto/TypedPacket.hpp"

#include <cstdint>
#include <string_view>

namespace crosslink::proto {

enum class PlayerAction : std::int32_t {
    StartBreak         = 0,
    AbortBreak         = 1,
    StopBreak          = 2,
    DropItem           = 4,
    StartJumping       = 7,
    ChangeDimensionAck = 14,
    Respawn            = 7,
};

/// Client-initiated actor action. Carries the local player's runtime id, and the
/// Respawn action is the client's half of the spawn handshake a handoff has to
/// drive to completion against the new backend.
class CROSSLINK_API PlayerActionPacket final
: public TypedPacket<PlayerActionPacket, PacketId::PlayerAction> {
public:
    static constexpr std::string_view staticName = "PlayerActionPacket";

    using TypedPacket::TypedPacket;

    [[nodiscard]] std::int32_t  action() const;
    [[nodiscard]] std::uint64_t runtimeId() const;
    [[nodiscard]] std::int32_t  positionX() const;
    [[nodiscard]] std::int32_t  positionY() const;
    [[nodiscard]] std::int32_t  positionZ() const;
    [[nodiscard]] std::int32_t  face() const;

    [[nodiscard]] bool isRespawn() const;
    [[nodiscard]] bool isDimensionChangeAck() const;

    void setRuntimeId(std::uint64_t runtimeId);

protected:
    Result<> decodeImpl() override;
    Result<> encodeImpl() override;

private:
    std::int32_t  mAction{};
    std::uint64_t mRuntimeId{};
    std::int32_t  mPositionX{};
    std::int32_t  mPositionY{};
    std::int32_t  mPositionZ{};
    std::int32_t  mFace{};
};

} // namespace crosslink::proto
