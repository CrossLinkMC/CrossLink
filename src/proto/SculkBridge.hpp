#pragma once

// Internal bridge between CrossLink's packet API and the vendored protocol
// library. Nothing in here is part of the plugin ABI: plugins only ever see
// crosslink/api/proto/*.hpp, which is what keeps the ABI stable when the
// transport library underneath changes.

#include "crosslink/api/Result.hpp"
#include "crosslink/api/Types.hpp"
#include "crosslink/api/net/Transport.hpp"
#include "crosslink/api/proto/Packet.hpp"

#include <sculk/protocol/codec/MinecraftPackets.hpp>
#include <sculk/protocol/codec/actor/player/GameType.hpp>
#include <sculk/protocol/codec/level/CompressionAlgorithm.hpp>
#include <sculk/protocol/codec/math/Vec3.hpp>
#include <sculk/protocol/codec/packet/IPacket.hpp>
#include <sculk/protocol/utility/BinaryStream.hpp>
#include <sculk/protocol/utility/ReadOnlyBinaryStream.hpp>

#include <string>
#include <type_traits>
#include <utility>

namespace crosslink::proto::bridge {

namespace bp = sculk::protocol;

using SculkHeader = bp::MinecraftPackets::PacketHeader;

[[nodiscard]] inline SculkHeader toSculk(PacketHeader const& header) {
    return SculkHeader{
        .mPacketId          = static_cast<bp::MinecraftPacketIds>(packetIdValue(header.id)),
        .mSenderSubClientId = header.senderSubClientId,
        .mTargetSubClientId = header.targetSubClientId,
    };
}

[[nodiscard]] inline PacketHeader fromSculk(SculkHeader const& header) {
    return PacketHeader{
        .id                = makePacketId(static_cast<std::uint16_t>(header.mPacketId)),
        .senderSubClientId = header.mSenderSubClientId,
        .targetSubClientId = header.mTargetSubClientId,
    };
}

[[nodiscard]] inline Result<SculkHeader> readSculkHeader(ByteSpan bytes) {
    bp::ReadOnlyBinaryStream stream{bytes};
    const auto header = bp::MinecraftPackets::readPacketHeader(stream);
    if (!header) return std::unexpected(Error{std::string{header.error().message()}});
    return *header;
}

[[nodiscard]] inline std::size_t serializedHeaderSize(PacketHeader const& header) {
    Bytes scratch;
    bp::BinaryStream stream{scratch};
    bp::MinecraftPackets::writePacketHeader(stream, toSculk(header));
    return scratch.size();
}

/// Serializes `header` followed by `packet`'s body.
[[nodiscard]] inline Bytes serialize(PacketHeader const& header, bp::IPacket const& packet) {
    Bytes out;
    bp::BinaryStream stream{out};
    bp::MinecraftPackets::writePacketHeader(stream, toSculk(header));
    packet.write(stream);
    return out;
}

/// Decodes a packet body, rejecting trailing bytes so a version mismatch fails
/// loudly instead of silently forwarding garbage.
template <typename T>
[[nodiscard]] Result<T> decode(ByteSpan payload) {
    T packet;
    bp::ReadOnlyBinaryStream stream{payload};
    if (const auto status = packet.read(stream); !status) {
        return std::unexpected(Error{std::string{status.error().message()}});
    }
    return packet;
}

/// Read-modify-write: decodes the whole packet, applies `mutator`, re-serializes.
/// Every field the mutator does not touch survives the round trip.
template <typename T, typename Mutator>
[[nodiscard]] Result<Bytes> modify(PacketHeader const& header, ByteSpan payload, Mutator&& mutator) {
    auto packet = decode<T>(payload);
    if (!packet) return std::unexpected(packet.error());
    mutator(*packet);
    return serialize(header, *packet);
}

// ---- type conversions -------------------------------------------------

[[nodiscard]] inline GameType fromSculk(bp::GameType gameType) noexcept {
    return static_cast<GameType>(static_cast<std::int32_t>(gameType));
}

[[nodiscard]] inline bp::GameType toSculk(GameType gameType) noexcept {
    return static_cast<bp::GameType>(static_cast<std::int8_t>(gameType));
}

[[nodiscard]] inline Vec3 fromSculk(bp::Vec3 const& position) noexcept {
    return Vec3{position.mX, position.mY, position.mZ};
}

[[nodiscard]] inline bp::Vec3 toSculk(Vec3 const& position) noexcept {
    return bp::Vec3{position.x, position.y, position.z};
}

[[nodiscard]] inline net::Compression fromSculk(bp::CompressionAlgorithm algorithm) noexcept {
    return static_cast<net::Compression>(static_cast<std::int8_t>(algorithm));
}

[[nodiscard]] inline bp::CompressionAlgorithm toSculk(net::Compression compression) noexcept {
    return static_cast<bp::CompressionAlgorithm>(static_cast<std::int8_t>(compression));
}

[[nodiscard]] inline PacketId fromSculk(bp::MinecraftPacketIds id) noexcept {
    return makePacketId(static_cast<std::uint16_t>(id));
}

[[nodiscard]] inline bp::MinecraftPacketIds toSculk(PacketId id) noexcept {
    return static_cast<bp::MinecraftPacketIds>(packetIdValue(id));
}

/// Converts a sculk Result<>'s error into a CrossLink Error.
template <typename T>
[[nodiscard]] Error convertError(T const& status) {
    return Error{std::string{status.error().message()}};
}

} // namespace crosslink::proto::bridge
