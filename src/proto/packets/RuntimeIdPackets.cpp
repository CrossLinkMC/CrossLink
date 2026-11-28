#include "crosslink/api/proto/packets/RuntimeIdPackets.hpp"

#include "proto/EndstoneBridge.hpp"

#include <algorithm>
#include <functional>
#include <unordered_map>
#include <vector>

namespace crosslink::proto {
namespace {

namespace bp = bridge::bp;

/// One row of the group table: how to read a packet body's runtime id and how to
/// rewrite it. Both directions decode the full body, so untouched fields survive.
struct Accessor {
    std::function<Result<std::uint64_t>(ByteSpan)> read;
    std::function<Result<Bytes>(PacketHeader const&, ByteSpan, std::uint64_t)> rewrite;
};

template <typename T, typename Field>
Accessor makeAccessor(Field T::* field) {
    return Accessor{
        .read =
            [field](ByteSpan payload) -> Result<std::uint64_t> {
                auto packet = bridge::decode<T>(payload);
                if (!packet) return std::unexpected(packet.error());
                return static_cast<std::uint64_t>((*packet).*field);
            },
        .rewrite =
            [field](PacketHeader const& header, ByteSpan payload, std::uint64_t runtimeId) -> Result<Bytes> {
                return bridge::modify<T>(header, payload, [&](T& packet) {
                    packet.*field = Field{runtimeId};
                });
            },
    };
}

/// Adding a packet to the runtime-id group is one line here and nothing else.
std::unordered_map<std::uint16_t, Accessor> const& accessorTable() {
    static const std::unordered_map<std::uint16_t, Accessor> table = {
        {packetIdValue(PacketId::ActorEvent), makeAccessor<bp::ActorEventPacket>(&bp::ActorEventPacket::runtime_id)},
        {packetIdValue(PacketId::Animate), makeAccessor<bp::AnimatePacket>(&bp::AnimatePacket::runtime_id)},
        {packetIdValue(PacketId::Interact), makeAccessor<bp::InteractPacket>(&bp::InteractPacket::target_id)},
        {packetIdValue(PacketId::MobArmorEquipment),
         makeAccessor<bp::MobArmorEquipmentPacket>(&bp::MobArmorEquipmentPacket::runtime_id)},
        {packetIdValue(PacketId::MobEffect), makeAccessor<bp::MobEffectPacket>(&bp::MobEffectPacket::runtime_id)},
        {packetIdValue(PacketId::MobEquipment), makeAccessor<bp::MobEquipmentPacket>(&bp::MobEquipmentPacket::runtime_id)},
        {packetIdValue(PacketId::MovePlayer), makeAccessor<bp::MovePlayerPacket>(&bp::MovePlayerPacket::player_id)},
        {packetIdValue(PacketId::SetActorData), makeAccessor<bp::SetActorDataPacket>(&bp::SetActorDataPacket::id)},
        {packetIdValue(PacketId::SetActorMotion),
         makeAccessor<bp::SetActorMotionPacket>(&bp::SetActorMotionPacket::runtime_id)},
        {packetIdValue(PacketId::UpdateAttributes),
         makeAccessor<bp::UpdateAttributesPacket>(&bp::UpdateAttributesPacket::runtime_id)},
    };
    return table;
}

Accessor const* accessorFor(PacketId id) {
    auto const& table = accessorTable();
    const auto found = table.find(packetIdValue(id));
    return found == table.end() ? nullptr : &found->second;
}

} // namespace

Result<std::optional<std::int64_t>> actorUniqueId(Packet const& packet) {
    switch (packet.id()) {
    case PacketId::AddActor:
    case PacketId::AddItemActor:
    case PacketId::RemoveActor: {
        bp::BinaryReader reader{bridge::toStringView(packet.payload())};
        const auto id = reader.readVarInt<std::int64_t>();
        if (!id) return std::unexpected(Error{id.error().message()});
        return std::optional{*id};
    }
    case PacketId::AddPlayer: {
        auto player = bridge::decode<bp::AddPlayerPacket>(packet.payload());
        if (!player) return std::unexpected(player.error());
        return std::optional{static_cast<std::int64_t>(player->abilities_data.target_player)};
    }
    default:
        return std::nullopt;
    }
}

Bytes makeRemoveActorPacket(std::int64_t uniqueId) {
    bp::RemoveActorPacket packet;
    packet.entity_id = bp::ActorUniqueID{uniqueId};
    return bridge::serialize(PacketHeader{PacketId::RemoveActor}, packet);
}

RuntimeIdPacket::RuntimeIdPacket(PacketHeader header, Bytes bytes, std::size_t headerSize)
: Packet(header, std::move(bytes), headerSize) {}

RuntimeIdPacket::RuntimeIdPacket(PacketHeader header) : Packet(header) {}

std::vector<PacketId> const& RuntimeIdPacket::coveredIds() {
    static const std::vector<PacketId> ids = [] {
        std::vector<PacketId> result;
        result.reserve(accessorTable().size());
        for (auto const& [value, accessor] : accessorTable()) result.push_back(makePacketId(value));
        std::ranges::sort(result, [](PacketId left, PacketId right) { return packetIdValue(left) < packetIdValue(right); });
        return result;
    }();
    return ids;
}

bool RuntimeIdPacket::covers(PacketId id) { return accessorFor(id) != nullptr; }

Result<std::uint64_t> RuntimeIdPacket::runtimeId() {
    if (mHasRuntimeId) return mRuntimeId;

    const auto* accessor = accessorFor(id());
    if (accessor == nullptr) return std::unexpected(Error{"this packet does not carry a runtime id"});

    auto value = accessor->read(payload());
    if (!value) return std::unexpected(value.error());
    mRuntimeId = *value;
    mHasRuntimeId = true;
    return mRuntimeId;
}

bool RuntimeIdPacket::setRuntimeId(std::uint64_t runtimeId) {
    const auto* accessor = accessorFor(id());
    if (accessor == nullptr) return false;

    const auto current = this->runtimeId();
    if (!current) return false;
    if (*current == runtimeId) return false;

    auto rewritten = accessor->rewrite(header(), payload(), runtimeId);
    if (!rewritten) return false;
    setSerialized(std::move(*rewritten), bridge::serializedHeaderSize(header()));
    mRuntimeId = runtimeId;
    mHasRuntimeId = true;
    mDecoded = true;
    return true;
}

Result<> RuntimeIdPacket::decodeImpl() {
    // Reading the runtime id is the whole decode for this group.
    if (const auto value = runtimeId(); !value) return std::unexpected(value.error());
    return {};
}

Result<> RuntimeIdPacket::encodeImpl() {
    // setRuntimeId() already wrote the serialized form.
    return {};
}

} // namespace crosslink::proto
