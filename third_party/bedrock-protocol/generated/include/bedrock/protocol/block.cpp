#include <bedrock/protocol/block.h>

namespace bedrock::protocol {


void Serializer<base::AnvilDamagePacket>::serialize(BinaryWriter &stream, const base::AnvilDamagePacket &value)
{
    stream.write<std::uint8_t>(value.damage);
    Serializer<base::NetworkBlockPosition>::serialize(stream, value.position);
}

auto Serializer<base::AnvilDamagePacket>::deserialize(BinaryReader &stream) -> std::expected<base::AnvilDamagePacket, std::error_code>
{
    base::AnvilDamagePacket out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.damage = static_cast<std::int32_t>(*v);
    }
    {
        auto v = Serializer<base::NetworkBlockPosition>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.position = *v;
    }
    return out;
}

void Serializer<v944::AnvilDamagePacket>::serialize(BinaryWriter &stream, const v944::AnvilDamagePacket &value)
{
    stream.write<std::uint8_t>(value.damage);
    Serializer<BlockPos>::serialize(stream, value.position);
}

auto Serializer<v944::AnvilDamagePacket>::deserialize(BinaryReader &stream) -> std::expected<v944::AnvilDamagePacket, std::error_code>
{
    v944::AnvilDamagePacket out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.damage = static_cast<std::int32_t>(*v);
    }
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.position = *v;
    }
    return out;
}

void Serializer<v2168::AnvilDamagePacket>::serialize(BinaryWriter &stream, const v2168::AnvilDamagePacket &value)
{
    Serializer<BlockPos>::serialize(stream, value.position);
}

auto Serializer<v2168::AnvilDamagePacket>::deserialize(BinaryReader &stream) -> std::expected<v2168::AnvilDamagePacket, std::error_code>
{
    v2168::AnvilDamagePacket out;
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.position = *v;
    }
    return out;
}

void Serializer<base::UpdateBlockPacket>::serialize(BinaryWriter &stream, const base::UpdateBlockPacket &value)
{
    Serializer<base::NetworkBlockPosition>::serialize(stream, value.pos);
    stream.writeVarInt<std::uint32_t>(value.runtime_id);
    stream.writeVarInt<std::uint32_t>(value.update_flags);
    stream.writeVarInt<std::uint32_t>(value.layer);
}

auto Serializer<base::UpdateBlockPacket>::deserialize(BinaryReader &stream) -> std::expected<base::UpdateBlockPacket, std::error_code>
{
    base::UpdateBlockPacket out;
    {
        auto v = Serializer<base::NetworkBlockPosition>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<BlockRuntimeId>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.update_flags = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.layer = static_cast<std::uint32_t>(*v);
    }
    return out;
}

void Serializer<v944::UpdateBlockPacket>::serialize(BinaryWriter &stream, const v944::UpdateBlockPacket &value)
{
    Serializer<BlockPos>::serialize(stream, value.pos);
    stream.writeVarInt<std::uint32_t>(value.runtime_id);
    stream.writeVarInt<std::uint32_t>(value.update_flags);
    stream.writeVarInt<std::uint32_t>(value.layer);
}

auto Serializer<v944::UpdateBlockPacket>::deserialize(BinaryReader &stream) -> std::expected<v944::UpdateBlockPacket, std::error_code>
{
    v944::UpdateBlockPacket out;
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<BlockRuntimeId>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.update_flags = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.layer = static_cast<std::uint32_t>(*v);
    }
    return out;
}

void Serializer<base::BlockEventPacket>::serialize(BinaryWriter &stream, const base::BlockEventPacket &value)
{
    Serializer<base::NetworkBlockPosition>::serialize(stream, value.pos);
    stream.writeVarInt<std::int32_t>(value.b0);
    stream.writeVarInt<std::int32_t>(value.b1);
}

auto Serializer<base::BlockEventPacket>::deserialize(BinaryReader &stream) -> std::expected<base::BlockEventPacket, std::error_code>
{
    base::BlockEventPacket out;
    {
        auto v = Serializer<base::NetworkBlockPosition>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.b0 = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.b1 = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<v944::BlockEventPacket>::serialize(BinaryWriter &stream, const v944::BlockEventPacket &value)
{
    Serializer<BlockPos>::serialize(stream, value.pos);
    stream.writeVarInt<std::int32_t>(value.b0);
    stream.writeVarInt<std::int32_t>(value.b1);
}

auto Serializer<v944::BlockEventPacket>::deserialize(BinaryReader &stream) -> std::expected<v944::BlockEventPacket, std::error_code>
{
    v944::BlockEventPacket out;
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.b0 = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.b1 = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<BlockPickRequestPacket>::serialize(BinaryWriter &stream, const BlockPickRequestPacket &value)
{
    Serializer<BlockPos>::serialize(stream, value.pos);
    stream.write<bool>(value.with_data);
    stream.write<std::uint8_t>(value.max_slots);
}

auto Serializer<BlockPickRequestPacket>::deserialize(BinaryReader &stream) -> std::expected<BlockPickRequestPacket, std::error_code>
{
    BlockPickRequestPacket out;
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.with_data = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.max_slots = static_cast<std::uint8_t>(*v);
    }
    return out;
}

void Serializer<base::BlockActorDataPacket>::serialize(BinaryWriter &stream, const base::BlockActorDataPacket &value)
{
    Serializer<base::NetworkBlockPosition>::serialize(stream, value.pos);
    Serializer<CompoundTag>::serialize(stream, value.data);
}

auto Serializer<base::BlockActorDataPacket>::deserialize(BinaryReader &stream) -> std::expected<base::BlockActorDataPacket, std::error_code>
{
    base::BlockActorDataPacket out;
    {
        auto v = Serializer<base::NetworkBlockPosition>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = Serializer<CompoundTag>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.data = *v;
    }
    return out;
}

void Serializer<v944::BlockActorDataPacket>::serialize(BinaryWriter &stream, const v944::BlockActorDataPacket &value)
{
    Serializer<BlockPos>::serialize(stream, value.pos);
    Serializer<CompoundTag>::serialize(stream, value.data);
}

auto Serializer<v944::BlockActorDataPacket>::deserialize(BinaryReader &stream) -> std::expected<v944::BlockActorDataPacket, std::error_code>
{
    v944::BlockActorDataPacket out;
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = Serializer<CompoundTag>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.data = *v;
    }
    return out;
}

void Serializer<base::UpdateBlockSyncedPacket>::serialize(BinaryWriter &stream, const base::UpdateBlockSyncedPacket &value)
{
    Serializer<base::NetworkBlockPosition>::serialize(stream, value.pos);
    stream.writeVarInt<std::uint32_t>(value.runtime_id);
    stream.writeVarInt<std::uint32_t>(value.update_flags);
    stream.writeVarInt<std::uint32_t>(value.layer);
    stream.writeVarInt<std::uint64_t>(value.entity_unique_id);
    stream.writeVarInt<std::uint64_t>(value.message);
}

auto Serializer<base::UpdateBlockSyncedPacket>::deserialize(BinaryReader &stream) -> std::expected<base::UpdateBlockSyncedPacket, std::error_code>
{
    base::UpdateBlockSyncedPacket out;
    {
        auto v = Serializer<base::NetworkBlockPosition>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<BlockRuntimeId>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.update_flags = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.layer = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_unique_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.message = static_cast<ActorBlockSyncMessage::MessageId>(*v);
    }
    return out;
}

void Serializer<v944::UpdateBlockSyncedPacket>::serialize(BinaryWriter &stream, const v944::UpdateBlockSyncedPacket &value)
{
    Serializer<BlockPos>::serialize(stream, value.pos);
    stream.writeVarInt<std::uint32_t>(value.runtime_id);
    stream.writeVarInt<std::uint32_t>(value.update_flags);
    stream.writeVarInt<std::uint32_t>(value.layer);
    stream.writeVarInt<std::uint64_t>(value.entity_unique_id);
    stream.writeVarInt<std::uint64_t>(value.message);
}

auto Serializer<v944::UpdateBlockSyncedPacket>::deserialize(BinaryReader &stream) -> std::expected<v944::UpdateBlockSyncedPacket, std::error_code>
{
    v944::UpdateBlockSyncedPacket out;
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<BlockRuntimeId>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.update_flags = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.layer = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_unique_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.message = static_cast<ActorBlockSyncMessage::MessageId>(*v);
    }
    return out;
}

void Serializer<base::LecternUpdatePacket>::serialize(BinaryWriter &stream, const base::LecternUpdatePacket &value)
{
    stream.write<std::uint8_t>(value.page);
    stream.write<std::uint8_t>(value.total_pages);
    Serializer<base::NetworkBlockPosition>::serialize(stream, value.pos);
}

auto Serializer<base::LecternUpdatePacket>::deserialize(BinaryReader &stream) -> std::expected<base::LecternUpdatePacket, std::error_code>
{
    base::LecternUpdatePacket out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.page = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.total_pages = static_cast<std::int32_t>(*v);
    }
    {
        auto v = Serializer<base::NetworkBlockPosition>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    return out;
}

void Serializer<v944::LecternUpdatePacket>::serialize(BinaryWriter &stream, const v944::LecternUpdatePacket &value)
{
    stream.write<std::uint8_t>(value.page);
    stream.write<std::uint8_t>(value.total_pages);
    Serializer<BlockPos>::serialize(stream, value.pos);
}

auto Serializer<v944::LecternUpdatePacket>::deserialize(BinaryReader &stream) -> std::expected<v944::LecternUpdatePacket, std::error_code>
{
    v944::LecternUpdatePacket out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.page = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.total_pages = static_cast<std::int32_t>(*v);
    }
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    return out;
}

void Serializer<base::OpenSignPacket>::serialize(BinaryWriter &stream, const base::OpenSignPacket &value)
{
    Serializer<base::NetworkBlockPosition>::serialize(stream, value.pos);
    stream.write<bool>(value.is_front_side);
}

auto Serializer<base::OpenSignPacket>::deserialize(BinaryReader &stream) -> std::expected<base::OpenSignPacket, std::error_code>
{
    base::OpenSignPacket out;
    {
        auto v = Serializer<base::NetworkBlockPosition>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_front_side = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v944::OpenSignPacket>::serialize(BinaryWriter &stream, const v944::OpenSignPacket &value)
{
    Serializer<BlockPos>::serialize(stream, value.pos);
    stream.write<bool>(value.is_front_side);
}

auto Serializer<v944::OpenSignPacket>::deserialize(BinaryReader &stream) -> std::expected<v944::OpenSignPacket, std::error_code>
{
    v944::OpenSignPacket out;
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_front_side = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<base::UpdateSubChunkNetworkBlockInfo>::serialize(BinaryWriter &stream, const base::UpdateSubChunkNetworkBlockInfo &value)
{
    Serializer<base::NetworkBlockPosition>::serialize(stream, value.pos);
    stream.writeVarInt<std::uint32_t>(value.runtime_id);
    stream.writeVarInt<std::uint32_t>(value.update_flags);
    stream.writeVarInt<std::uint64_t>(value.entity_unique_id);
    stream.writeVarInt<std::uint32_t>(value.message);
}

auto Serializer<base::UpdateSubChunkNetworkBlockInfo>::deserialize(BinaryReader &stream) -> std::expected<base::UpdateSubChunkNetworkBlockInfo, std::error_code>
{
    base::UpdateSubChunkNetworkBlockInfo out;
    {
        auto v = Serializer<base::NetworkBlockPosition>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<BlockRuntimeId>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.update_flags = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_unique_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.message = static_cast<ActorBlockSyncMessage::MessageId>(*v);
    }
    return out;
}

void Serializer<v944::UpdateSubChunkNetworkBlockInfo>::serialize(BinaryWriter &stream, const v944::UpdateSubChunkNetworkBlockInfo &value)
{
    Serializer<BlockPos>::serialize(stream, value.pos);
    stream.writeVarInt<std::uint32_t>(value.runtime_id);
    stream.writeVarInt<std::uint32_t>(value.update_flags);
    stream.writeVarInt<std::uint64_t>(value.entity_unique_id);
    stream.writeVarInt<std::uint32_t>(value.message);
}

auto Serializer<v944::UpdateSubChunkNetworkBlockInfo>::deserialize(BinaryReader &stream) -> std::expected<v944::UpdateSubChunkNetworkBlockInfo, std::error_code>
{
    v944::UpdateSubChunkNetworkBlockInfo out;
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<BlockRuntimeId>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.update_flags = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_unique_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.message = static_cast<ActorBlockSyncMessage::MessageId>(*v);
    }
    return out;
}

void Serializer<base::UpdateSubChunkBlocksChangedInfo>::serialize(BinaryWriter &stream, const base::UpdateSubChunkBlocksChangedInfo &value)
{
    stream.writeVarInt<std::uint32_t>(value.standards.size());
    for (const auto &e0 : value.standards) {
        Serializer<base::UpdateSubChunkNetworkBlockInfo>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.extras.size());
    for (const auto &e0 : value.extras) {
        Serializer<base::UpdateSubChunkNetworkBlockInfo>::serialize(stream, e0);
    }
}

auto Serializer<base::UpdateSubChunkBlocksChangedInfo>::deserialize(BinaryReader &stream) -> std::expected<base::UpdateSubChunkBlocksChangedInfo, std::error_code>
{
    base::UpdateSubChunkBlocksChangedInfo out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.standards.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.standards.emplace_back();
            auto v = Serializer<base::UpdateSubChunkNetworkBlockInfo>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.standards.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.extras.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.extras.emplace_back();
            auto v = Serializer<base::UpdateSubChunkNetworkBlockInfo>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.extras.back() = *v;
        }
    }
    return out;
}

void Serializer<v944::UpdateSubChunkBlocksChangedInfo>::serialize(BinaryWriter &stream, const v944::UpdateSubChunkBlocksChangedInfo &value)
{
    stream.writeVarInt<std::uint32_t>(value.standards.size());
    for (const auto &e0 : value.standards) {
        Serializer<v944::UpdateSubChunkNetworkBlockInfo>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.extras.size());
    for (const auto &e0 : value.extras) {
        Serializer<v944::UpdateSubChunkNetworkBlockInfo>::serialize(stream, e0);
    }
}

auto Serializer<v944::UpdateSubChunkBlocksChangedInfo>::deserialize(BinaryReader &stream) -> std::expected<v944::UpdateSubChunkBlocksChangedInfo, std::error_code>
{
    v944::UpdateSubChunkBlocksChangedInfo out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.standards.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.standards.emplace_back();
            auto v = Serializer<v944::UpdateSubChunkNetworkBlockInfo>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.standards.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.extras.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.extras.emplace_back();
            auto v = Serializer<v944::UpdateSubChunkNetworkBlockInfo>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.extras.back() = *v;
        }
    }
    return out;
}

void Serializer<base::UpdateSubChunkBlocksPacket>::serialize(BinaryWriter &stream, const base::UpdateSubChunkBlocksPacket &value)
{
    Serializer<base::NetworkBlockPosition>::serialize(stream, value.sub_chunk_block_position);
    Serializer<base::UpdateSubChunkBlocksChangedInfo>::serialize(stream, value.blocks_changed);
}

auto Serializer<base::UpdateSubChunkBlocksPacket>::deserialize(BinaryReader &stream) -> std::expected<base::UpdateSubChunkBlocksPacket, std::error_code>
{
    base::UpdateSubChunkBlocksPacket out;
    {
        auto v = Serializer<base::NetworkBlockPosition>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.sub_chunk_block_position = *v;
    }
    {
        auto v = Serializer<base::UpdateSubChunkBlocksChangedInfo>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.blocks_changed = *v;
    }
    return out;
}

void Serializer<v944::UpdateSubChunkBlocksPacket>::serialize(BinaryWriter &stream, const v944::UpdateSubChunkBlocksPacket &value)
{
    Serializer<BlockPos>::serialize(stream, value.sub_chunk_block_position);
    Serializer<v944::UpdateSubChunkBlocksChangedInfo>::serialize(stream, value.blocks_changed);
}

auto Serializer<v944::UpdateSubChunkBlocksPacket>::deserialize(BinaryReader &stream) -> std::expected<v944::UpdateSubChunkBlocksPacket, std::error_code>
{
    v944::UpdateSubChunkBlocksPacket out;
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.sub_chunk_block_position = *v;
    }
    {
        auto v = Serializer<v944::UpdateSubChunkBlocksChangedInfo>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.blocks_changed = *v;
    }
    return out;
}

void Serializer<RemoveVolumeEntityPacket>::serialize(BinaryWriter &stream, const RemoveVolumeEntityPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.entity_net_id);
    stream.writeVarInt<std::int32_t>(value.dimension_type);
}

auto Serializer<RemoveVolumeEntityPacket>::deserialize(BinaryReader &stream) -> std::expected<RemoveVolumeEntityPacket, std::error_code>
{
    RemoveVolumeEntityPacket out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_net_id = static_cast<EntityNetId>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.dimension_type = static_cast<DimensionType>(*v);
    }
    return out;
}

void Serializer<base::AddVolumeEntityPacket>::serialize(BinaryWriter &stream, const base::AddVolumeEntityPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.entity_net_id);
    Serializer<CompoundTag>::serialize(stream, value.components);
    stream.write(value.json_identifier);
    stream.write(value.instance_name);
    Serializer<base::NetworkBlockPosition>::serialize(stream, value.min_bounds);
    Serializer<base::NetworkBlockPosition>::serialize(stream, value.max_bounds);
    stream.writeVarInt<std::int32_t>(value.dimension_type);
    stream.write(value.min_engine_version);
}

auto Serializer<base::AddVolumeEntityPacket>::deserialize(BinaryReader &stream) -> std::expected<base::AddVolumeEntityPacket, std::error_code>
{
    base::AddVolumeEntityPacket out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_net_id = static_cast<EntityNetId>(*v);
    }
    {
        auto v = Serializer<CompoundTag>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.components = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.json_identifier = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.instance_name = *v;
    }
    {
        auto v = Serializer<base::NetworkBlockPosition>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.min_bounds = *v;
    }
    {
        auto v = Serializer<base::NetworkBlockPosition>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.max_bounds = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.dimension_type = static_cast<DimensionType>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.min_engine_version = *v;
    }
    return out;
}

void Serializer<v944::AddVolumeEntityPacket>::serialize(BinaryWriter &stream, const v944::AddVolumeEntityPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.entity_net_id);
    Serializer<CompoundTag>::serialize(stream, value.components);
    stream.write(value.json_identifier);
    stream.write(value.instance_name);
    Serializer<BlockPos>::serialize(stream, value.min_bounds);
    Serializer<BlockPos>::serialize(stream, value.max_bounds);
    stream.writeVarInt<std::int32_t>(value.dimension_type);
    stream.write(value.min_engine_version);
}

auto Serializer<v944::AddVolumeEntityPacket>::deserialize(BinaryReader &stream) -> std::expected<v944::AddVolumeEntityPacket, std::error_code>
{
    v944::AddVolumeEntityPacket out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_net_id = static_cast<EntityNetId>(*v);
    }
    {
        auto v = Serializer<CompoundTag>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.components = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.json_identifier = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.instance_name = *v;
    }
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.min_bounds = *v;
    }
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.max_bounds = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.dimension_type = static_cast<DimensionType>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.min_engine_version = *v;
    }
    return out;
}

void Serializer<SerializableCells>::serialize(BinaryWriter &stream, const SerializableCells &value)
{
    stream.write<std::uint8_t>(value.x_size);
    stream.write<std::uint8_t>(value.y_size);
    stream.write<std::uint8_t>(value.z_size);
    stream.writeVarInt<std::uint32_t>(value.storage.size());
    for (const auto &e0 : value.storage) {
        stream.write<std::uint8_t>(e0);
    }
}

auto Serializer<SerializableCells>::deserialize(BinaryReader &stream) -> std::expected<SerializableCells, std::error_code>
{
    SerializableCells out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.x_size = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.y_size = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.z_size = static_cast<std::uint8_t>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.storage.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.storage.emplace_back();
            auto v = stream.read<std::uint8_t>();
            if (!v) return std::unexpected(v.error());
            out.storage.back() = static_cast<std::uint8_t>(*v);
        }
    }
    return out;
}

void Serializer<SerializableVoxelShape>::serialize(BinaryWriter &stream, const SerializableVoxelShape &value)
{
    Serializer<SerializableCells>::serialize(stream, value.cells);
    stream.writeVarInt<std::uint32_t>(value.x_coords.size());
    for (const auto &e0 : value.x_coords) {
        stream.write<float>(e0);
    }
    stream.writeVarInt<std::uint32_t>(value.y_coords.size());
    for (const auto &e0 : value.y_coords) {
        stream.write<float>(e0);
    }
    stream.writeVarInt<std::uint32_t>(value.z_coords.size());
    for (const auto &e0 : value.z_coords) {
        stream.write<float>(e0);
    }
}

auto Serializer<SerializableVoxelShape>::deserialize(BinaryReader &stream) -> std::expected<SerializableVoxelShape, std::error_code>
{
    SerializableVoxelShape out;
    {
        auto v = Serializer<SerializableCells>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.cells = *v;
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.x_coords.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.x_coords.emplace_back();
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            out.x_coords.back() = static_cast<float>(*v);
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.y_coords.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.y_coords.emplace_back();
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            out.y_coords.back() = static_cast<float>(*v);
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.z_coords.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.z_coords.emplace_back();
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            out.z_coords.back() = static_cast<float>(*v);
        }
    }
    return out;
}

void Serializer<v924::VoxelShapesPacket>::serialize(BinaryWriter &stream, const v924::VoxelShapesPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.shapes.size());
    for (const auto &e0 : value.shapes) {
        Serializer<SerializableVoxelShape>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.name_map.size());
    for (const auto &[k0, v0] : value.name_map) {
        stream.write(k0);
        stream.write<std::uint16_t>(v0);
    }
}

auto Serializer<v924::VoxelShapesPacket>::deserialize(BinaryReader &stream) -> std::expected<v924::VoxelShapesPacket, std::error_code>
{
    v924::VoxelShapesPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.shapes.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.shapes.emplace_back();
            auto v = Serializer<SerializableVoxelShape>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.shapes.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.name_map.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            std::string key0{};
            {
                auto v = stream.read<std::string>();
                if (!v) return std::unexpected(v.error());
                key0 = *v;
            }
            auto v = stream.read<std::uint16_t>();
            if (!v) return std::unexpected(v.error());
            out.name_map[key0] = static_cast<RegistryHandle>(*v);
        }
    }
    return out;
}

void Serializer<v944::VoxelShapesPacket>::serialize(BinaryWriter &stream, const v944::VoxelShapesPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.shapes.size());
    for (const auto &e0 : value.shapes) {
        Serializer<SerializableVoxelShape>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.name_map.size());
    for (const auto &[k0, v0] : value.name_map) {
        stream.write(k0);
        stream.write<std::uint16_t>(v0);
    }
    stream.write<std::uint16_t>(value.custom_shape_count);
}

auto Serializer<v944::VoxelShapesPacket>::deserialize(BinaryReader &stream) -> std::expected<v944::VoxelShapesPacket, std::error_code>
{
    v944::VoxelShapesPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.shapes.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.shapes.emplace_back();
            auto v = Serializer<SerializableVoxelShape>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.shapes.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.name_map.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            std::string key0{};
            {
                auto v = stream.read<std::string>();
                if (!v) return std::unexpected(v.error());
                key0 = *v;
            }
            auto v = stream.read<std::uint16_t>();
            if (!v) return std::unexpected(v.error());
            out.name_map[key0] = static_cast<RegistryHandle>(*v);
        }
    }
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.custom_shape_count = static_cast<std::uint16_t>(*v);
    }
    return out;
}

void Serializer<LevelEventPacket>::serialize(BinaryWriter &stream, const LevelEventPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.event_id);
    Serializer<Vec3>::serialize(stream, value.pos);
    stream.writeVarInt<std::int32_t>(value.data);
}

auto Serializer<LevelEventPacket>::deserialize(BinaryReader &stream) -> std::expected<LevelEventPacket, std::error_code>
{
    LevelEventPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.event_id = static_cast<std::int32_t>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.data = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<LevelEventGenericPacket>::serialize(BinaryWriter &stream, const LevelEventGenericPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.event_id);
    Serializer<CompoundTag>::serialize(stream, value.data);
}

auto Serializer<LevelEventGenericPacket>::deserialize(BinaryReader &stream) -> std::expected<LevelEventGenericPacket, std::error_code>
{
    LevelEventGenericPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.event_id = static_cast<std::int32_t>(*v);
    }
    {
        auto v = Serializer<CompoundTag>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.data = *v;
    }
    return out;
}

void Serializer<SpawnParticleEffectPacket>::serialize(BinaryWriter &stream, const SpawnParticleEffectPacket &value)
{
    stream.write<std::uint8_t>(value.vanilla_dimension_id);
    stream.writeVarInt<std::int64_t>(value.actor_id);
    Serializer<Vec3>::serialize(stream, value.pos);
    stream.write(value.effect_name);
    stream.write<bool>(value.molang_variables.has_value());
    if (value.molang_variables.has_value()) {
        stream.write((*value.molang_variables));
    }
}

auto Serializer<SpawnParticleEffectPacket>::deserialize(BinaryReader &stream) -> std::expected<SpawnParticleEffectPacket, std::error_code>
{
    SpawnParticleEffectPacket out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.vanilla_dimension_id = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.actor_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.effect_name = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::string staged{};
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.molang_variables = std::move(staged);
        }
    }
    return out;
}

}  // namespace bedrock::protocol
