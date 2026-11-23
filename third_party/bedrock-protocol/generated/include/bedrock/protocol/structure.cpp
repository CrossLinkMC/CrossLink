#include <bedrock/protocol/structure.h>

namespace bedrock::protocol {


void Serializer<base::StructureSettings>::serialize(BinaryWriter &stream, const base::StructureSettings &value)
{
    stream.write(value.palette_name);
    stream.write<bool>(value.ignore_entities);
    stream.write<bool>(value.ignore_blocks);
    stream.write<bool>(value.allow_non_ticking_player_and_ticking_area_chunks);
    Serializer<base::NetworkBlockPosition>::serialize(stream, value.structure_size);
    Serializer<base::NetworkBlockPosition>::serialize(stream, value.structure_offset);
    stream.writeVarInt<std::int64_t>(value.last_touched_by_player);
    stream.write<std::uint8_t>(value.rotation);
    stream.write<std::uint8_t>(value.mirror);
    stream.write<std::uint8_t>(value.animation_mode);
    stream.write<float>(value.animation_seconds);
    stream.write<float>(value.integrity_value);
    stream.write<std::uint32_t>(value.integrity_seed);
    Serializer<Vec3>::serialize(stream, value.pivot);
}

auto Serializer<base::StructureSettings>::deserialize(BinaryReader &stream) -> std::expected<base::StructureSettings, std::error_code>
{
    base::StructureSettings out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.palette_name = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.ignore_entities = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.ignore_blocks = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.allow_non_ticking_player_and_ticking_area_chunks = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<base::NetworkBlockPosition>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.structure_size = *v;
    }
    {
        auto v = Serializer<base::NetworkBlockPosition>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.structure_offset = *v;
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.last_touched_by_player = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.rotation = static_cast<Rotation>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.mirror = static_cast<Mirror>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.animation_mode = static_cast<AnimationMode>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.animation_seconds = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.integrity_value = static_cast<float>(*v);
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.integrity_seed = static_cast<RandomSeed>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pivot = *v;
    }
    return out;
}

void Serializer<v944::StructureSettings>::serialize(BinaryWriter &stream, const v944::StructureSettings &value)
{
    stream.write(value.palette_name);
    stream.write<bool>(value.ignore_entities);
    stream.write<bool>(value.ignore_blocks);
    stream.write<bool>(value.allow_non_ticking_player_and_ticking_area_chunks);
    Serializer<BlockPos>::serialize(stream, value.structure_size);
    Serializer<BlockPos>::serialize(stream, value.structure_offset);
    stream.writeVarInt<std::int64_t>(value.last_touched_by_player);
    stream.write<std::uint8_t>(value.rotation);
    stream.write<std::uint8_t>(value.mirror);
    stream.write<std::uint8_t>(value.animation_mode);
    stream.write<float>(value.animation_seconds);
    stream.write<float>(value.integrity_value);
    stream.write<std::uint32_t>(value.integrity_seed);
    Serializer<Vec3>::serialize(stream, value.pivot);
}

auto Serializer<v944::StructureSettings>::deserialize(BinaryReader &stream) -> std::expected<v944::StructureSettings, std::error_code>
{
    v944::StructureSettings out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.palette_name = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.ignore_entities = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.ignore_blocks = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.allow_non_ticking_player_and_ticking_area_chunks = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.structure_size = *v;
    }
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.structure_offset = *v;
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.last_touched_by_player = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.rotation = static_cast<Rotation>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.mirror = static_cast<Mirror>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.animation_mode = static_cast<AnimationMode>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.animation_seconds = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.integrity_value = static_cast<float>(*v);
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.integrity_seed = static_cast<RandomSeed>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pivot = *v;
    }
    return out;
}

void Serializer<base::StructureEditorData>::serialize(BinaryWriter &stream, const base::StructureEditorData &value)
{
    stream.write(value.structure_name);
    stream.write(value.data_field);
    stream.write<bool>(value.include_players);
    stream.write<bool>(value.show_bounding_box);
    stream.writeVarInt<std::int32_t>(value.type);
    Serializer<base::StructureSettings>::serialize(stream, value.settings);
    stream.writeVarInt<std::int32_t>(value.redstone_save_mode);
}

auto Serializer<base::StructureEditorData>::deserialize(BinaryReader &stream) -> std::expected<base::StructureEditorData, std::error_code>
{
    base::StructureEditorData out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.structure_name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.data_field = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.include_players = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.show_bounding_box = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<StructureBlockType>(*v);
    }
    {
        auto v = Serializer<base::StructureSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.settings = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.redstone_save_mode = static_cast<StructureRedstoneSaveMode>(*v);
    }
    return out;
}

void Serializer<v766::StructureEditorData>::serialize(BinaryWriter &stream, const v766::StructureEditorData &value)
{
    stream.write(value.structure_name);
    stream.write(value.data_field);
    stream.write<bool>(value.include_players);
    stream.write<bool>(value.show_bounding_box);
    stream.writeVarInt<std::int32_t>(value.type);
    Serializer<base::StructureSettings>::serialize(stream, value.settings);
    stream.writeVarInt<std::int32_t>(value.redstone_save_mode);
}

auto Serializer<v766::StructureEditorData>::deserialize(BinaryReader &stream) -> std::expected<v766::StructureEditorData, std::error_code>
{
    v766::StructureEditorData out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.structure_name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.data_field = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.include_players = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.show_bounding_box = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<StructureBlockType>(*v);
    }
    {
        auto v = Serializer<base::StructureSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.settings = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.redstone_save_mode = static_cast<StructureRedstoneSaveMode>(*v);
    }
    return out;
}

void Serializer<v776::StructureEditorData>::serialize(BinaryWriter &stream, const v776::StructureEditorData &value)
{
    Serializer<v766::RedactableString>::serialize(stream, value.structure_name);
    stream.write(value.data_field);
    stream.write<bool>(value.include_players);
    stream.write<bool>(value.show_bounding_box);
    stream.writeVarInt<std::int32_t>(value.type);
    Serializer<base::StructureSettings>::serialize(stream, value.settings);
    stream.writeVarInt<std::int32_t>(value.redstone_save_mode);
}

auto Serializer<v776::StructureEditorData>::deserialize(BinaryReader &stream) -> std::expected<v776::StructureEditorData, std::error_code>
{
    v776::StructureEditorData out;
    {
        auto v = Serializer<v766::RedactableString>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.structure_name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.data_field = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.include_players = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.show_bounding_box = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<StructureBlockType>(*v);
    }
    {
        auto v = Serializer<base::StructureSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.settings = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.redstone_save_mode = static_cast<StructureRedstoneSaveMode>(*v);
    }
    return out;
}

void Serializer<v944::StructureEditorData>::serialize(BinaryWriter &stream, const v944::StructureEditorData &value)
{
    Serializer<v766::RedactableString>::serialize(stream, value.structure_name);
    stream.write(value.data_field);
    stream.write<bool>(value.include_players);
    stream.write<bool>(value.show_bounding_box);
    stream.writeVarInt<std::int32_t>(value.type);
    Serializer<v944::StructureSettings>::serialize(stream, value.settings);
    stream.writeVarInt<std::int32_t>(value.redstone_save_mode);
}

auto Serializer<v944::StructureEditorData>::deserialize(BinaryReader &stream) -> std::expected<v944::StructureEditorData, std::error_code>
{
    v944::StructureEditorData out;
    {
        auto v = Serializer<v766::RedactableString>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.structure_name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.data_field = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.include_players = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.show_bounding_box = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<StructureBlockType>(*v);
    }
    {
        auto v = Serializer<v944::StructureSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.settings = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.redstone_save_mode = static_cast<StructureRedstoneSaveMode>(*v);
    }
    return out;
}

void Serializer<v2168::StructureEditorData>::serialize(BinaryWriter &stream, const v2168::StructureEditorData &value)
{
    Serializer<v2168::RedactableString>::serialize(stream, value.structure_name);
    stream.write(value.data_field);
    stream.write<bool>(value.include_players);
    stream.write<bool>(value.show_bounding_box);
    stream.writeVarInt<std::int32_t>(value.type);
    Serializer<v944::StructureSettings>::serialize(stream, value.settings);
    stream.write<std::uint8_t>(value.redstone_save_mode);
}

auto Serializer<v2168::StructureEditorData>::deserialize(BinaryReader &stream) -> std::expected<v2168::StructureEditorData, std::error_code>
{
    v2168::StructureEditorData out;
    {
        auto v = Serializer<v2168::RedactableString>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.structure_name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.data_field = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.include_players = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.show_bounding_box = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<StructureBlockType>(*v);
    }
    {
        auto v = Serializer<v944::StructureSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.settings = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.redstone_save_mode = static_cast<StructureRedstoneSaveMode>(*v);
    }
    return out;
}

void Serializer<base::StructureBlockUpdatePacket>::serialize(BinaryWriter &stream, const base::StructureBlockUpdatePacket &value)
{
    Serializer<base::NetworkBlockPosition>::serialize(stream, value.block_pos);
    Serializer<base::StructureEditorData>::serialize(stream, value.data);
    stream.write<bool>(value.trigger);
    stream.write<bool>(value.is_waterlogged);
}

auto Serializer<base::StructureBlockUpdatePacket>::deserialize(BinaryReader &stream) -> std::expected<base::StructureBlockUpdatePacket, std::error_code>
{
    base::StructureBlockUpdatePacket out;
    {
        auto v = Serializer<base::NetworkBlockPosition>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.block_pos = *v;
    }
    {
        auto v = Serializer<base::StructureEditorData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.data = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.trigger = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_waterlogged = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v766::StructureBlockUpdatePacket>::serialize(BinaryWriter &stream, const v766::StructureBlockUpdatePacket &value)
{
    Serializer<base::NetworkBlockPosition>::serialize(stream, value.block_pos);
    Serializer<v766::StructureEditorData>::serialize(stream, value.data);
    stream.write<bool>(value.trigger);
    stream.write<bool>(value.is_waterlogged);
}

auto Serializer<v766::StructureBlockUpdatePacket>::deserialize(BinaryReader &stream) -> std::expected<v766::StructureBlockUpdatePacket, std::error_code>
{
    v766::StructureBlockUpdatePacket out;
    {
        auto v = Serializer<base::NetworkBlockPosition>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.block_pos = *v;
    }
    {
        auto v = Serializer<v766::StructureEditorData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.data = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.trigger = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_waterlogged = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v776::StructureBlockUpdatePacket>::serialize(BinaryWriter &stream, const v776::StructureBlockUpdatePacket &value)
{
    Serializer<base::NetworkBlockPosition>::serialize(stream, value.block_pos);
    Serializer<v776::StructureEditorData>::serialize(stream, value.data);
    stream.write<bool>(value.trigger);
    stream.write<bool>(value.is_waterlogged);
}

auto Serializer<v776::StructureBlockUpdatePacket>::deserialize(BinaryReader &stream) -> std::expected<v776::StructureBlockUpdatePacket, std::error_code>
{
    v776::StructureBlockUpdatePacket out;
    {
        auto v = Serializer<base::NetworkBlockPosition>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.block_pos = *v;
    }
    {
        auto v = Serializer<v776::StructureEditorData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.data = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.trigger = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_waterlogged = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v944::StructureBlockUpdatePacket>::serialize(BinaryWriter &stream, const v944::StructureBlockUpdatePacket &value)
{
    Serializer<BlockPos>::serialize(stream, value.block_pos);
    Serializer<v944::StructureEditorData>::serialize(stream, value.data);
    stream.write<bool>(value.trigger);
    stream.write<bool>(value.is_waterlogged);
}

auto Serializer<v944::StructureBlockUpdatePacket>::deserialize(BinaryReader &stream) -> std::expected<v944::StructureBlockUpdatePacket, std::error_code>
{
    v944::StructureBlockUpdatePacket out;
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.block_pos = *v;
    }
    {
        auto v = Serializer<v944::StructureEditorData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.data = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.trigger = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_waterlogged = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v2168::StructureBlockUpdatePacket>::serialize(BinaryWriter &stream, const v2168::StructureBlockUpdatePacket &value)
{
    Serializer<BlockPos>::serialize(stream, value.block_pos);
    Serializer<v2168::StructureEditorData>::serialize(stream, value.data);
    stream.write<bool>(value.trigger);
    stream.write<bool>(value.is_waterlogged);
}

auto Serializer<v2168::StructureBlockUpdatePacket>::deserialize(BinaryReader &stream) -> std::expected<v2168::StructureBlockUpdatePacket, std::error_code>
{
    v2168::StructureBlockUpdatePacket out;
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.block_pos = *v;
    }
    {
        auto v = Serializer<v2168::StructureEditorData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.data = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.trigger = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_waterlogged = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<TickingAreasLoadStatusPacket>::serialize(BinaryWriter &stream, const TickingAreasLoadStatusPacket &value)
{
    stream.write<bool>(value.waiting_for_preload);
}

auto Serializer<TickingAreasLoadStatusPacket>::deserialize(BinaryReader &stream) -> std::expected<TickingAreasLoadStatusPacket, std::error_code>
{
    TickingAreasLoadStatusPacket out;
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.waiting_for_preload = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<CurrentStructureFeaturePacket>::serialize(BinaryWriter &stream, const CurrentStructureFeaturePacket &value)
{
    stream.write(value.current_structure_feature);
}

auto Serializer<CurrentStructureFeaturePacket>::deserialize(BinaryReader &stream) -> std::expected<CurrentStructureFeaturePacket, std::error_code>
{
    CurrentStructureFeaturePacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.current_structure_feature = *v;
    }
    return out;
}

void Serializer<base::StructureTemplateDataRequestPacket>::serialize(BinaryWriter &stream, const base::StructureTemplateDataRequestPacket &value)
{
    stream.write(value.structure_name);
    Serializer<base::NetworkBlockPosition>::serialize(stream, value.structure_block_pos);
    Serializer<base::StructureSettings>::serialize(stream, value.structure_settings);
    stream.write<std::uint8_t>(value.request_operation);
}

auto Serializer<base::StructureTemplateDataRequestPacket>::deserialize(BinaryReader &stream) -> std::expected<base::StructureTemplateDataRequestPacket, std::error_code>
{
    base::StructureTemplateDataRequestPacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.structure_name = *v;
    }
    {
        auto v = Serializer<base::NetworkBlockPosition>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.structure_block_pos = *v;
    }
    {
        auto v = Serializer<base::StructureSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.structure_settings = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.request_operation = static_cast<StructureTemplateRequestOperation>(*v);
    }
    return out;
}

void Serializer<v944::StructureTemplateDataRequestPacket>::serialize(BinaryWriter &stream, const v944::StructureTemplateDataRequestPacket &value)
{
    stream.write(value.structure_name);
    Serializer<BlockPos>::serialize(stream, value.structure_block_pos);
    Serializer<v944::StructureSettings>::serialize(stream, value.structure_settings);
    stream.write<std::uint8_t>(value.request_operation);
}

auto Serializer<v944::StructureTemplateDataRequestPacket>::deserialize(BinaryReader &stream) -> std::expected<v944::StructureTemplateDataRequestPacket, std::error_code>
{
    v944::StructureTemplateDataRequestPacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.structure_name = *v;
    }
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.structure_block_pos = *v;
    }
    {
        auto v = Serializer<v944::StructureSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.structure_settings = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.request_operation = static_cast<StructureTemplateRequestOperation>(*v);
    }
    return out;
}

void Serializer<StructureTemplateDataResponsePacket>::serialize(BinaryWriter &stream, const StructureTemplateDataResponsePacket &value)
{
    stream.write(value.structure_name);
    stream.write<bool>(value.structure_tag.has_value());
    if (value.structure_tag.has_value()) {
        Serializer<CompoundTag>::serialize(stream, (*value.structure_tag));
    }
    stream.write<std::uint8_t>(value.response_type);
}

auto Serializer<StructureTemplateDataResponsePacket>::deserialize(BinaryReader &stream) -> std::expected<StructureTemplateDataResponsePacket, std::error_code>
{
    StructureTemplateDataResponsePacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.structure_name = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            CompoundTag staged{};
            auto v = Serializer<CompoundTag>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.structure_tag = std::move(staged);
        }
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.response_type = static_cast<StructureTemplateResponseType>(*v);
    }
    return out;
}

void Serializer<JigsawStructureDataPacket>::serialize(BinaryWriter &stream, const JigsawStructureDataPacket &value)
{
    Serializer<CompoundTag>::serialize(stream, value.jigsaw_structure_data_tag);
}

auto Serializer<JigsawStructureDataPacket>::deserialize(BinaryReader &stream) -> std::expected<JigsawStructureDataPacket, std::error_code>
{
    JigsawStructureDataPacket out;
    {
        auto v = Serializer<CompoundTag>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.jigsaw_structure_data_tag = *v;
    }
    return out;
}

void Serializer<FeatureRegistry::FeatureBinaryJsonFormat>::serialize(BinaryWriter &stream, const FeatureRegistry::FeatureBinaryJsonFormat &value)
{
    stream.write(value.feature_name);
    stream.write(value.binary_json_output);
}

auto Serializer<FeatureRegistry::FeatureBinaryJsonFormat>::deserialize(BinaryReader &stream) -> std::expected<FeatureRegistry::FeatureBinaryJsonFormat, std::error_code>
{
    FeatureRegistry::FeatureBinaryJsonFormat out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.feature_name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.binary_json_output = *v;
    }
    return out;
}

void Serializer<FeatureRegistryPacket>::serialize(BinaryWriter &stream, const FeatureRegistryPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.features_data_list.size());
    for (const auto &e0 : value.features_data_list) {
        Serializer<FeatureRegistry::FeatureBinaryJsonFormat>::serialize(stream, e0);
    }
}

auto Serializer<FeatureRegistryPacket>::deserialize(BinaryReader &stream) -> std::expected<FeatureRegistryPacket, std::error_code>
{
    FeatureRegistryPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.features_data_list.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.features_data_list.emplace_back();
            auto v = Serializer<FeatureRegistry::FeatureBinaryJsonFormat>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.features_data_list.back() = *v;
        }
    }
    return out;
}

void Serializer<GameTestResultsPacket>::serialize(BinaryWriter &stream, const GameTestResultsPacket &value)
{
    stream.write<bool>(value.succeeded);
    stream.write(value.error);
    stream.write(value.test_name);
}

auto Serializer<GameTestResultsPacket>::deserialize(BinaryReader &stream) -> std::expected<GameTestResultsPacket, std::error_code>
{
    GameTestResultsPacket out;
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.succeeded = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.error = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.test_name = *v;
    }
    return out;
}

void Serializer<GameTestRequestPacket>::serialize(BinaryWriter &stream, const GameTestRequestPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.max_tests_per_batch);
    stream.writeVarInt<std::int32_t>(value.repeat_count);
    stream.write<std::uint8_t>(value.rotation);
    stream.write<bool>(value.stop_on_failure);
    Serializer<BlockPos>::serialize(stream, value.test_pos);
    stream.writeVarInt<std::int32_t>(value.tests_per_row);
    stream.write(value.test_name);
}

auto Serializer<GameTestRequestPacket>::deserialize(BinaryReader &stream) -> std::expected<GameTestRequestPacket, std::error_code>
{
    GameTestRequestPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.max_tests_per_batch = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.repeat_count = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.rotation = static_cast<Rotation>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.stop_on_failure = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.test_pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.tests_per_row = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.test_name = *v;
    }
    return out;
}

}  // namespace bedrock::protocol
