#pragma once

#include "crosslink/api/proto/TypedPacket.hpp"

#include <cstdint>
#include <string_view>
#include <vector>

namespace crosslink::proto {

/// Every packet that names the local player by runtime id.
///
/// One class covers the whole group because the handling is identical: read the
/// runtime id field, and rewrite it when it refers to the local player. Which id
/// each packet uses lives in a table in the implementation, so adding a packet to
/// the group is one line there and nothing here.
///
/// This is what keeps a player's own entity stable across a handoff: the client
/// keeps seeing the runtime id it was given at first login while each backend
/// uses its own.
class CROSSLINK_API RuntimeIdPacket final : public Packet {
public:
    static constexpr std::string_view staticName = "RuntimeIdPacket";

    RuntimeIdPacket(PacketHeader header, Bytes bytes, std::size_t headerSize);
    explicit RuntimeIdPacket(PacketHeader header);

    [[nodiscard]] std::string_view name() const noexcept override { return staticName; }

    /// Packet ids handled by this class.
    [[nodiscard]] static std::vector<PacketId> const& coveredIds();
    [[nodiscard]] static bool                        covers(PacketId id);

    [[nodiscard]] Result<std::uint64_t> runtimeId();
    /// Rewrites the runtime id in place. Returns false when this packet does not
    /// carry one, or when it already had the requested value.
    [[nodiscard]] bool setRuntimeId(std::uint64_t runtimeId);

protected:
    Result<> decodeImpl() override;
    Result<> encodeImpl() override;

private:
    std::uint64_t mRuntimeId{};
    bool          mHasRuntimeId{};
};

} // namespace crosslink::proto
