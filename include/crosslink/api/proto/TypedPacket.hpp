#pragma once

#include "crosslink/api/proto/Packet.hpp"

#include <utility>

namespace crosslink::proto {

/// CRTP base for the packets CrossLink interprets.
///
/// It fixes the packet id, the readable name (`Derived::staticName`), the three
/// constructors the codec registry needs, and the one-call registration helper.
/// A concrete packet therefore only declares its typed fields plus decodeImpl()
/// and encodeImpl().
template <typename Derived, PacketId Id>
class TypedPacket : public Packet {
public:
    static constexpr PacketId packetId = Id;

    TypedPacket(PacketHeader header, Bytes bytes, std::size_t headerSize)
    : Packet(header, std::move(bytes), headerSize) {}

    explicit TypedPacket(PacketHeader header) : Packet(header) {}

    /// Builds an empty packet of this type, ready to be filled in and encoded.
    TypedPacket() : Packet(PacketHeader{Id}) {}

    [[nodiscard]] std::string_view name() const noexcept override { return Derived::staticName; }

    /// Makes the codec table build this type for `Id`. Idempotent; called once
    /// from the packet's translation unit.
    static bool registerIn(PacketCodecs& codecs = PacketCodecs::instance()) {
        return codecs.registerPacket<Derived>(Id);
    }
};

} // namespace crosslink::proto
