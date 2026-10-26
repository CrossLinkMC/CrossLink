#pragma once

#include "crosslink/api/proto/TypedPacket.hpp"

#include <cstdint>
#include <string_view>

namespace crosslink::proto {

enum class RespawnState : std::uint8_t {
    SearchingForSpawn   = 0,
    ReadyToSpawn        = 1,
    ClientReadyToSpawn  = 2,
};

/// Respawn handshake. It travels both ways and carries a runtime id, so a
/// handoff has to translate it in each direction: the client only ever knows the
/// runtime id the gateway showed it at first login, while each backend assigns
/// its own.
class CROSSLINK_API RespawnPacket final : public TypedPacket<RespawnPacket, PacketId::Respawn> {
public:
    static constexpr std::string_view staticName = "RespawnPacket";

    using TypedPacket::TypedPacket;

    RespawnPacket(RespawnState state, Vec3 position, std::uint64_t runtimeId);

    [[nodiscard]] RespawnState   state() const;
    [[nodiscard]] Vec3           position() const;
    [[nodiscard]] std::uint64_t  runtimeId() const;

    void setState(RespawnState state);
    void setPosition(Vec3 position);
    void setRuntimeId(std::uint64_t runtimeId);

protected:
    Result<> decodeImpl() override;
    Result<> encodeImpl() override;

private:
    RespawnState  mState{RespawnState::SearchingForSpawn};
    Vec3          mPosition{};
    std::uint64_t mRuntimeId{};
};

} // namespace crosslink::proto
