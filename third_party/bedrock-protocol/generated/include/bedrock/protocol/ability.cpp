#include <bedrock/protocol/ability.h>

namespace bedrock::protocol {


void Serializer<RequestPermissionsPacket>::serialize(BinaryWriter &stream, const RequestPermissionsPacket &value)
{
    stream.write<std::int64_t>(value.target_player_id);
    stream.writeVarInt<std::int32_t>(value.player_permissions);
    stream.write<std::uint16_t>(value.custom_permission_flags);
}

auto Serializer<RequestPermissionsPacket>::deserialize(BinaryReader &stream) -> std::expected<RequestPermissionsPacket, std::error_code>
{
    RequestPermissionsPacket out;
    {
        auto v = stream.read<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.target_player_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.player_permissions = static_cast<PlayerPermissionLevel>(*v);
    }
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.custom_permission_flags = static_cast<std::uint16_t>(*v);
    }
    return out;
}

void Serializer<AdventureSettings>::serialize(BinaryWriter &stream, const AdventureSettings &value)
{
    stream.write<bool>(value.no_pv_m);
    stream.write<bool>(value.no_mv_p);
    stream.write<bool>(value.immutable_world);
    stream.write<bool>(value.show_name_tags);
    stream.write<bool>(value.auto_jump);
}

auto Serializer<AdventureSettings>::deserialize(BinaryReader &stream) -> std::expected<AdventureSettings, std::error_code>
{
    AdventureSettings out;
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.no_pv_m = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.no_mv_p = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.immutable_world = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.show_name_tags = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.auto_jump = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<UpdateAdventureSettingsPacket>::serialize(BinaryWriter &stream, const UpdateAdventureSettingsPacket &value)
{
    Serializer<AdventureSettings>::serialize(stream, value.adventure_settings);
}

auto Serializer<UpdateAdventureSettingsPacket>::deserialize(BinaryReader &stream) -> std::expected<UpdateAdventureSettingsPacket, std::error_code>
{
    UpdateAdventureSettingsPacket out;
    {
        auto v = Serializer<AdventureSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.adventure_settings = *v;
    }
    return out;
}

void Serializer<base::RequestAbilityPacket>::serialize(BinaryWriter &stream, const base::RequestAbilityPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.ability);
    stream.write<std::uint8_t>(value.value_type);
    stream.write<bool>(value.bool_);
    stream.write<float>(value.float_);
}

auto Serializer<base::RequestAbilityPacket>::deserialize(BinaryReader &stream) -> std::expected<base::RequestAbilityPacket, std::error_code>
{
    base::RequestAbilityPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.ability = static_cast<base::AbilitiesIndex>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.value_type = static_cast<base::RequestAbilityPacket::Type>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.bool_ = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.float_ = static_cast<float>(*v);
    }
    return out;
}

void Serializer<v776::RequestAbilityPacket>::serialize(BinaryWriter &stream, const v776::RequestAbilityPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.ability);
    stream.write<std::uint8_t>(value.value_type);
    stream.write<bool>(value.bool_);
    stream.write<float>(value.float_);
}

auto Serializer<v776::RequestAbilityPacket>::deserialize(BinaryReader &stream) -> std::expected<v776::RequestAbilityPacket, std::error_code>
{
    v776::RequestAbilityPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.ability = static_cast<v776::AbilitiesIndex>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.value_type = static_cast<v776::RequestAbilityPacket::Type>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.bool_ = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.float_ = static_cast<float>(*v);
    }
    return out;
}

void Serializer<base::SerializedAbilitiesData::SerializedLayer>::serialize(BinaryWriter &stream, const base::SerializedAbilitiesData::SerializedLayer &value)
{
    stream.write<std::uint16_t>(value.serialized_layer);
    stream.write<std::uint32_t>(value.abilities_set);
    stream.write<std::uint32_t>(value.ability_values);
    stream.write<float>(value.fly_speed);
    stream.write<float>(value.walk_speed);
}

auto Serializer<base::SerializedAbilitiesData::SerializedLayer>::deserialize(BinaryReader &stream) -> std::expected<base::SerializedAbilitiesData::SerializedLayer, std::error_code>
{
    base::SerializedAbilitiesData::SerializedLayer out;
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.serialized_layer = static_cast<base::SerializedAbilitiesData::SerializedAbilitiesLayer>(*v);
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.abilities_set = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.ability_values = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.fly_speed = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.walk_speed = static_cast<float>(*v);
    }
    return out;
}

void Serializer<v776::SerializedAbilitiesData::SerializedLayer>::serialize(BinaryWriter &stream, const v776::SerializedAbilitiesData::SerializedLayer &value)
{
    stream.write<std::uint16_t>(value.serialized_layer);
    stream.write<std::uint32_t>(value.abilities_set);
    stream.write<std::uint32_t>(value.ability_values);
    stream.write<float>(value.fly_speed);
    stream.write<float>(value.vertical_fly_speed);
    stream.write<float>(value.walk_speed);
}

auto Serializer<v776::SerializedAbilitiesData::SerializedLayer>::deserialize(BinaryReader &stream) -> std::expected<v776::SerializedAbilitiesData::SerializedLayer, std::error_code>
{
    v776::SerializedAbilitiesData::SerializedLayer out;
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.serialized_layer = static_cast<v776::SerializedAbilitiesData::SerializedAbilitiesLayer>(*v);
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.abilities_set = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.ability_values = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.fly_speed = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.vertical_fly_speed = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.walk_speed = static_cast<float>(*v);
    }
    return out;
}

void Serializer<base::SerializedAbilitiesData>::serialize(BinaryWriter &stream, const base::SerializedAbilitiesData &value)
{
    stream.write<std::int64_t>(value.target_player);
    stream.write<std::int8_t>(value.player_permissions);
    stream.write<std::uint8_t>(value.command_permissions);
    stream.writeVarInt<std::uint32_t>(value.layers.size());
    for (const auto &e0 : value.layers) {
        Serializer<base::SerializedAbilitiesData::SerializedLayer>::serialize(stream, e0);
    }
}

auto Serializer<base::SerializedAbilitiesData>::deserialize(BinaryReader &stream) -> std::expected<base::SerializedAbilitiesData, std::error_code>
{
    base::SerializedAbilitiesData out;
    {
        auto v = stream.read<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.target_player = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.player_permissions = static_cast<PlayerPermissionLevel>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.command_permissions = static_cast<CommandPermissionLevel>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.layers.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.layers.emplace_back();
            auto v = Serializer<base::SerializedAbilitiesData::SerializedLayer>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.layers.back() = *v;
        }
    }
    return out;
}

void Serializer<v776::SerializedAbilitiesData>::serialize(BinaryWriter &stream, const v776::SerializedAbilitiesData &value)
{
    stream.write<std::int64_t>(value.target_player);
    stream.write<std::int8_t>(value.player_permissions);
    stream.write<std::uint8_t>(value.command_permissions);
    stream.writeVarInt<std::uint32_t>(value.layers.size());
    for (const auto &e0 : value.layers) {
        Serializer<v776::SerializedAbilitiesData::SerializedLayer>::serialize(stream, e0);
    }
}

auto Serializer<v776::SerializedAbilitiesData>::deserialize(BinaryReader &stream) -> std::expected<v776::SerializedAbilitiesData, std::error_code>
{
    v776::SerializedAbilitiesData out;
    {
        auto v = stream.read<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.target_player = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.player_permissions = static_cast<PlayerPermissionLevel>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.command_permissions = static_cast<CommandPermissionLevel>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.layers.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.layers.emplace_back();
            auto v = Serializer<v776::SerializedAbilitiesData::SerializedLayer>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.layers.back() = *v;
        }
    }
    return out;
}

void Serializer<base::UpdateAbilitiesPacket>::serialize(BinaryWriter &stream, const base::UpdateAbilitiesPacket &value)
{
    Serializer<base::SerializedAbilitiesData>::serialize(stream, value.data);
}

auto Serializer<base::UpdateAbilitiesPacket>::deserialize(BinaryReader &stream) -> std::expected<base::UpdateAbilitiesPacket, std::error_code>
{
    base::UpdateAbilitiesPacket out;
    {
        auto v = Serializer<base::SerializedAbilitiesData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.data = *v;
    }
    return out;
}

void Serializer<v776::UpdateAbilitiesPacket>::serialize(BinaryWriter &stream, const v776::UpdateAbilitiesPacket &value)
{
    Serializer<v776::SerializedAbilitiesData>::serialize(stream, value.data);
}

auto Serializer<v776::UpdateAbilitiesPacket>::deserialize(BinaryReader &stream) -> std::expected<v776::UpdateAbilitiesPacket, std::error_code>
{
    v776::UpdateAbilitiesPacket out;
    {
        auto v = Serializer<v776::SerializedAbilitiesData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.data = *v;
    }
    return out;
}

}  // namespace bedrock::protocol
