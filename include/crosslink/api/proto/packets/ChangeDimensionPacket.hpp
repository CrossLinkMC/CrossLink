#pragma once

#include "crosslink/api/proto/TypedPacket.hpp"

#include <cstdint>
#include <optional>
#include <string_view>

namespace crosslink::proto {

/// Asks the client to load another dimension. The gateway both forwards this and
/// synthesizes it: when the target backend spawns the player in a different
/// dimension than the client currently believes it is in, the client has to be
/// walked through a dimension load before the target's StartGame is acceptable.
class CROSSLINK_API ChangeDimensionPacket final
: public TypedPacket<ChangeDimensionPacket, PacketId::ChangeDimension> {
public:
    static constexpr std::string_view staticName = "ChangeDimensionPacket";

    using TypedPacket::TypedPacket;

    ChangeDimensionPacket(std::int32_t dimension, Vec3 position, bool respawn = false);

    [[nodiscard]] std::int32_t             dimension() const;
    [[nodiscard]] Vec3                     position() const;
    [[nodiscard]] bool                     respawn() const;
    [[nodiscard]] std::optional<std::uint32_t> loadingScreenId() const;

    void setDimension(std::int32_t dimension);
    void setPosition(Vec3 position);
    void setRespawn(bool respawn);
    void setLoadingScreenId(std::optional<std::uint32_t> id);

protected:
    Result<> decodeImpl() override;
    Result<> encodeImpl() override;

private:
    std::int32_t                mDimension{};
    Vec3                        mPosition{};
    bool                        mRespawn{};
    std::optional<std::uint32_t> mLoadingScreenId{};
};

} // namespace crosslink::proto
