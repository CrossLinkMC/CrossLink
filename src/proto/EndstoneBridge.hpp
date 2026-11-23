#pragma once

// Internal bridge between CrossLink's packet API and the vendored protocol
// library. Nothing in here is part of the plugin ABI: plugins only ever see
// crosslink/api/proto/*.hpp, which is what keeps the ABI stable when the
// protocol library underneath changes.

#include "crosslink/api/Result.hpp"
#include "crosslink/api/Types.hpp"
#include "crosslink/api/net/Transport.hpp"
#include "crosslink/api/proto/Packet.hpp"

#include <bedrock/protocol.hpp>
#include <bedrock/protocol/serializer.hpp>
#include <bedrock/protocol/stream.hpp>
#include <bedrock/protocol/version.hpp>

#include <cstddef>
#include <cstdint>
#include <string>
#include <string_view>
#include <utility>

namespace crosslink::proto::bridge {

namespace bp = bedrock::protocol;

// The codecs in third_party/bedrock-protocol are generated for exactly one
// protocol version. CrossLink advertises CROSSLINK_PROTOCOL_VERSION, so a
// mismatch would silently re-encode every packet with the wrong layout.
inline constexpr int kProtocolVersion = CROSSLINK_PROTOCOL_VERSION;
static_assert(kProtocolVersion == BEDROCK_PROTOCOL_LATEST,
              "protocol_version does not match the vendored bedrock-protocol codecs; regenerate them or set the "
              "matching xmake option");

[[nodiscard]] inline std::string_view toStringView(ByteSpan bytes) noexcept {
    // std::byte and char are both allowed to alias the buffer's object
    // representation, which is what makes this view legal.
    return {reinterpret_cast<char const*>(bytes.data()), bytes.size()}; // NOLINT: byte buffer view
}

[[nodiscard]] inline Bytes toBytes(std::string_view text) {
    Bytes out(text.size());
    for (std::size_t i = 0; i != text.size(); ++i) {
        out[i] = static_cast<std::byte>(static_cast<unsigned char>(text[i]));
    }
    return out;
}

/// Bedrock's packet header: one unsigned LEB128 varint holding the id in the low
/// 10 bits and each sub-client id in 2 bits above it.
[[nodiscard]] inline Result<PacketHeader> readHeader(ByteSpan bytes) {
    bp::BinaryReader stream{toStringView(bytes)};
    const auto raw = stream.readVarInt<std::uint32_t>();
    if (!raw) return std::unexpected(Error{raw.error().message()});
    return PacketHeader{
        .id                = makePacketId(static_cast<std::uint16_t>(*raw & 0x3FF)),
        .senderSubClientId = static_cast<std::uint8_t>((*raw >> 10) & 3),
        .targetSubClientId = static_cast<std::uint8_t>((*raw >> 12) & 3),
    };
}

inline void writeHeader(Bytes& out, PacketHeader const& header) {
    std::string buffer;
    bp::BinaryWriter stream{buffer};
    stream.writeVarInt<std::uint32_t>(
        (packetIdValue(header.id) & 0x3FF) | ((header.senderSubClientId & 3) << 10)
        | ((header.targetSubClientId & 3) << 12)
    );
    out.insert(out.end(), toBytes(buffer).begin(), toBytes(buffer).end());
}

[[nodiscard]] inline std::size_t serializedHeaderSize(PacketHeader const& header) {
    Bytes scratch;
    writeHeader(scratch, header);
    return scratch.size();
}

/// Decodes a packet body into the layout of `T`.
template <typename T>
[[nodiscard]] Result<T> decode(ByteSpan payload) {
    bp::BinaryReader stream{toStringView(payload)};
    auto packet = bp::deserialize<T>(stream);
    if (!packet) return std::unexpected(Error{packet.error().message()});
    return *std::move(packet);
}

/// Serializes `header` followed by `packet`'s body.
template <typename T>
[[nodiscard]] Bytes serialize(PacketHeader const& header, T const& packet) {
    std::string buffer;
    bp::BinaryWriter stream{buffer};
    bp::Serializer<T>::serialize(stream, packet);
    Bytes out;
    writeHeader(out, header);
    auto body = toBytes(buffer);
    out.insert(out.end(), std::make_move_iterator(body.begin()), std::make_move_iterator(body.end()));
    return out;
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

[[nodiscard]] inline Vec3 fromWire(bp::Vec3 const& position) noexcept {
    return Vec3{position.x, position.y, position.z};
}

[[nodiscard]] inline bp::Vec3 toWire(Vec3 const& position) noexcept {
    return bp::Vec3{position.x, position.y, position.z};
}

[[nodiscard]] inline GameType fromWire(bp::GameType gameType) noexcept {
    return static_cast<GameType>(static_cast<std::int32_t>(gameType));
}

[[nodiscard]] inline bp::GameType toWire(GameType gameType) noexcept {
    return static_cast<bp::GameType>(static_cast<std::int32_t>(gameType));
}

[[nodiscard]] inline net::Compression fromWire(bp::PacketCompressionAlgorithm algorithm) noexcept {
    switch (algorithm) {
    case bp::PacketCompressionAlgorithm::None:   return net::Compression::None;
    case bp::PacketCompressionAlgorithm::ZLib:   return net::Compression::Zlib;
    case bp::PacketCompressionAlgorithm::Snappy: return net::Compression::Snappy;
    }
    return net::Compression::None;
}

[[nodiscard]] inline bp::PacketCompressionAlgorithm toWire(net::Compression compression) noexcept {
    switch (compression) {
    case net::Compression::None:   return bp::PacketCompressionAlgorithm::None;
    case net::Compression::Zlib:   return bp::PacketCompressionAlgorithm::ZLib;
    case net::Compression::Snappy: return bp::PacketCompressionAlgorithm::Snappy;
    }
    return bp::PacketCompressionAlgorithm::None;
}

} // namespace crosslink::proto::bridge
