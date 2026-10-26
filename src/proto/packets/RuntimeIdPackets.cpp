#include "crosslink/api/proto/packets/RuntimeIdPackets.hpp"

#include "proto/SculkBridge.hpp"

#include <sculk/protocol/codec/packet/ActorEventPacket.hpp>
#include <sculk/protocol/codec/packet/AnimatePacket.hpp>
#include <sculk/protocol/codec/packet/InteractPacket.hpp>
#include <sculk/protocol/codec/packet/MobArmorEquipmentPacket.hpp>
#include <sculk/protocol/codec/packet/MobEffectPacket.hpp>
#include <sculk/protocol/codec/packet/MobEquipmentPacket.hpp>
#include <sculk/protocol/codec/packet/MovePlayerPacket.hpp>
#include <sculk/protocol/codec/packet/SetActorDataPacket.hpp>
#include <sculk/protocol/codec/packet/SetActorMotionPacket.hpp>
#include <sculk/protocol/codec/packet/UpdateAttributesPacket.hpp>

#include <algorithm>
#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

namespace crosslink::proto {
namespace {

namespace bp = bridge::bp;

using Getter = std::function<std::uint64_t(bp::IPacket const&)>;
using Setter = std::function<void(bp::IPacket&, std::uint64_t)>;

/// One row of the group table: how to reach the runtime id field of a packet.
struct Accessor {
    Getter get;
    Setter set;
};

template <typename T>
Accessor makeAccessor(std::uint64_t T::*field) {
    return Accessor{
        .get =
            [field](bp::IPacket const& packet) {
                return static_cast<T const&>(packet).*field;
            },
        .set =
            [field](bp::IPacket& packet, std::uint64_t value) {
                static_cast<T&>(packet).*field = value;
            },
    };
}

/// Adding a packet to the runtime-id group is one line here and nothing else.
std::unordered_map<std::uint16_t, Accessor> const& accessorTable() {
    static const std::unordered_map<std::uint16_t, Accessor> table = {
        {packetIdValue(PacketId::ActorEvent), makeAccessor<bp::ActorEventPacket>(&bp::ActorEventPacket::mRuntimeId)},
        {packetIdValue(PacketId::Animate), makeAccessor<bp::AnimatePacket>(&bp::AnimatePacket::mActorRuntimeId)},
        {packetIdValue(PacketId::Interact), makeAccessor<bp::InteractPacket>(&bp::InteractPacket::mActorRuntimeId)},
        {packetIdValue(PacketId::MobArmorEquipment),
         makeAccessor<bp::MobArmorEquipmentPacket>(&bp::MobArmorEquipmentPacket::mRuntimeId)},
        {packetIdValue(PacketId::MobEffect), makeAccessor<bp::MobEffectPacket>(&bp::MobEffectPacket::mActorRuntimeId)},
        {packetIdValue(PacketId::MobEquipment), makeAccessor<bp::MobEquipmentPacket>(&bp::MobEquipmentPacket::mRuntimeId)},
        {packetIdValue(PacketId::MovePlayer), makeAccessor<bp::MovePlayerPacket>(&bp::MovePlayerPacket::mActorRuntimeId)},
        {packetIdValue(PacketId::SetActorData), makeAccessor<bp::SetActorDataPacket>(&bp::SetActorDataPacket::mActorRuntimeId)},
        {packetIdValue(PacketId::SetActorMotion),
         makeAccessor<bp::SetActorMotionPacket>(&bp::SetActorMotionPacket::mActorRuntimeId)},
        {packetIdValue(PacketId::UpdateAttributes),
         makeAccessor<bp::UpdateAttributesPacket>(&bp::UpdateAttributesPacket::mActorRuntimeId)},
    };
    return table;
}

Accessor const* accessorFor(PacketId id) {
    auto const& table = accessorTable();
    const auto found = table.find(packetIdValue(id));
    return found == table.end() ? nullptr : &found->second;
}

/// Creates the sculk packet instance that matches an id in the group.
Result<std::unique_ptr<bp::IPacket>> createSculkPacket(PacketId id) {
    auto packet = bp::MinecraftPackets::createPacket(bridge::toSculk(id));
    if (!packet) return std::unexpected(Error{std::string{packet.error().message()}});
    return std::move(*packet);
}

} // namespace

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

    auto packet = createSculkPacket(id());
    if (!packet) return std::unexpected(packet.error());

    bp::ReadOnlyBinaryStream stream{payload()};
    if (const auto status = (*packet)->read(stream); !status) {
        return std::unexpected(Error{std::string{status.error().message()}});
    }
    mRuntimeId = accessor->get(**packet);
    mHasRuntimeId = true;
    return mRuntimeId;
}

bool RuntimeIdPacket::setRuntimeId(std::uint64_t runtimeId) {
    const auto* accessor = accessorFor(id());
    if (accessor == nullptr) return false;

    auto packet = createSculkPacket(id());
    if (!packet) return false;

    bp::ReadOnlyBinaryStream stream{payload()};
    if (const auto status = (*packet)->read(stream); !status) return false;
    if (accessor->get(**packet) == runtimeId) return false;

    accessor->set(**packet, runtimeId);
    setSerialized(bridge::serialize(header(), **packet), bridge::serializedHeaderSize(header()));
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
