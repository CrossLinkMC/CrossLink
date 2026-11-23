#include <bedrock/protocol/player.h>

namespace bedrock::protocol {


void Serializer<RespawnPacket>::serialize(BinaryWriter &stream, const RespawnPacket &value)
{
    Serializer<Vec3>::serialize(stream, value.pos);
    stream.write<std::uint8_t>(value.state);
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
}

auto Serializer<RespawnPacket>::deserialize(BinaryReader &stream) -> std::expected<RespawnPacket, std::error_code>
{
    RespawnPacket out;
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.state = static_cast<PlayerRespawnState>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    return out;
}

void Serializer<base::HurtArmorPacket>::serialize(BinaryWriter &stream, const base::HurtArmorPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.cause);
    stream.writeVarInt<std::int32_t>(value.dmg);
    stream.writeVarInt<std::uint64_t>(value.armor_slots);
}

auto Serializer<base::HurtArmorPacket>::deserialize(BinaryReader &stream) -> std::expected<base::HurtArmorPacket, std::error_code>
{
    base::HurtArmorPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.cause = static_cast<base::ActorDamageCause>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.dmg = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.armor_slots = static_cast<std::uint64_t>(*v);
    }
    return out;
}

void Serializer<v898::HurtArmorPacket>::serialize(BinaryWriter &stream, const v898::HurtArmorPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.cause);
    stream.writeVarInt<std::int32_t>(value.dmg);
    stream.writeVarInt<std::uint64_t>(value.armor_slots);
}

auto Serializer<v898::HurtArmorPacket>::deserialize(BinaryReader &stream) -> std::expected<v898::HurtArmorPacket, std::error_code>
{
    v898::HurtArmorPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.cause = static_cast<v898::ActorDamageCause>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.dmg = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.armor_slots = static_cast<std::uint64_t>(*v);
    }
    return out;
}

void Serializer<v924::HurtArmorPacket>::serialize(BinaryWriter &stream, const v924::HurtArmorPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.cause);
    stream.writeVarInt<std::int32_t>(value.dmg);
    stream.writeVarInt<std::uint64_t>(value.armor_slots);
}

auto Serializer<v924::HurtArmorPacket>::deserialize(BinaryReader &stream) -> std::expected<v924::HurtArmorPacket, std::error_code>
{
    v924::HurtArmorPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.cause = static_cast<v924::ActorDamageCause>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.dmg = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.armor_slots = static_cast<std::uint64_t>(*v);
    }
    return out;
}

void Serializer<SetHealthPacket>::serialize(BinaryWriter &stream, const SetHealthPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.health);
}

auto Serializer<SetHealthPacket>::deserialize(BinaryReader &stream) -> std::expected<SetHealthPacket, std::error_code>
{
    SetHealthPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.health = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<AwardAchievementPacket>::serialize(BinaryWriter &stream, const AwardAchievementPacket &value)
{
    stream.write<std::int32_t>(value.achievement_id);
}

auto Serializer<AwardAchievementPacket>::deserialize(BinaryReader &stream) -> std::expected<AwardAchievementPacket, std::error_code>
{
    AwardAchievementPacket out;
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.achievement_id = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<InteractPacket>::serialize(BinaryWriter &stream, const InteractPacket &value)
{
    stream.write<std::uint8_t>(value.action);
    stream.writeVarInt<std::uint64_t>(value.target_id);
    stream.write<bool>(value.pos.has_value());
    if (value.pos.has_value()) {
        Serializer<Vec3>::serialize(stream, (*value.pos));
    }
}

auto Serializer<InteractPacket>::deserialize(BinaryReader &stream) -> std::expected<InteractPacket, std::error_code>
{
    InteractPacket out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.action = static_cast<InteractPacket::Action>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.target_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec3 staged{};
            auto v = Serializer<Vec3>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.pos = std::move(staged);
        }
    }
    return out;
}

void Serializer<base::SetSpawnPositionPacket>::serialize(BinaryWriter &stream, const base::SetSpawnPositionPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.spawn_pos_type);
    Serializer<base::NetworkBlockPosition>::serialize(stream, value.pos);
    stream.writeVarInt<std::int32_t>(value.dimension_type);
    Serializer<base::NetworkBlockPosition>::serialize(stream, value.spawn_block_pos);
}

auto Serializer<base::SetSpawnPositionPacket>::deserialize(BinaryReader &stream) -> std::expected<base::SetSpawnPositionPacket, std::error_code>
{
    base::SetSpawnPositionPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.spawn_pos_type = static_cast<SpawnPositionType>(*v);
    }
    {
        auto v = Serializer<base::NetworkBlockPosition>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.dimension_type = static_cast<DimensionType>(*v);
    }
    {
        auto v = Serializer<base::NetworkBlockPosition>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.spawn_block_pos = *v;
    }
    return out;
}

void Serializer<v944::SetSpawnPositionPacket>::serialize(BinaryWriter &stream, const v944::SetSpawnPositionPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.spawn_pos_type);
    Serializer<BlockPos>::serialize(stream, value.pos);
    stream.writeVarInt<std::int32_t>(value.dimension_type);
    Serializer<BlockPos>::serialize(stream, value.spawn_block_pos);
}

auto Serializer<v944::SetSpawnPositionPacket>::deserialize(BinaryReader &stream) -> std::expected<v944::SetSpawnPositionPacket, std::error_code>
{
    v944::SetSpawnPositionPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.spawn_pos_type = static_cast<SpawnPositionType>(*v);
    }
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.dimension_type = static_cast<DimensionType>(*v);
    }
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.spawn_block_pos = *v;
    }
    return out;
}

void Serializer<SetLocalPlayerAsInitializedPacket>::serialize(BinaryWriter &stream, const SetLocalPlayerAsInitializedPacket &value)
{
    stream.writeVarInt<std::uint64_t>(value.player_id);
}

auto Serializer<SetLocalPlayerAsInitializedPacket>::deserialize(BinaryReader &stream) -> std::expected<SetLocalPlayerAsInitializedPacket, std::error_code>
{
    SetLocalPlayerAsInitializedPacket out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.player_id = static_cast<ActorRuntimeID>(*v);
    }
    return out;
}

void Serializer<ArmorSlotAndDamagePair>::serialize(BinaryWriter &stream, const ArmorSlotAndDamagePair &value)
{
    stream.writeVarInt<std::int32_t>(value.armor_slot);
    stream.write<std::int16_t>(value.damage);
}

auto Serializer<ArmorSlotAndDamagePair>::deserialize(BinaryReader &stream) -> std::expected<ArmorSlotAndDamagePair, std::error_code>
{
    ArmorSlotAndDamagePair out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.armor_slot = static_cast<ArmorSlot>(*v);
    }
    {
        auto v = stream.read<std::int16_t>();
        if (!v) return std::unexpected(v.error());
        out.damage = static_cast<std::int16_t>(*v);
    }
    return out;
}

void Serializer<base::PlayerArmorDamagePacket>::serialize(BinaryWriter &stream, const base::PlayerArmorDamagePacket &value)
{
    stream.write<std::uint8_t>(value.slots);
    if (((value.slots) & (1)) != (0)) {
        stream.writeVarInt<std::int32_t>(value.head_damage);
    }
    if (((value.slots) & (2)) != (0)) {
        stream.writeVarInt<std::int32_t>(value.torso_damage);
    }
    if (((value.slots) & (4)) != (0)) {
        stream.writeVarInt<std::int32_t>(value.legs_damage);
    }
    if (((value.slots) & (8)) != (0)) {
        stream.writeVarInt<std::int32_t>(value.feet_damage);
    }
    if (((value.slots) & (16)) != (0)) {
        stream.writeVarInt<std::int32_t>(value.body_damage);
    }
}

auto Serializer<base::PlayerArmorDamagePacket>::deserialize(BinaryReader &stream) -> std::expected<base::PlayerArmorDamagePacket, std::error_code>
{
    base::PlayerArmorDamagePacket out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.slots = static_cast<std::uint8_t>(*v);
    }
    if (((out.slots) & (1)) != (0)) {
        {
            auto v = stream.readVarInt<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            out.head_damage = static_cast<std::int32_t>(*v);
        }
    }
    if (((out.slots) & (2)) != (0)) {
        {
            auto v = stream.readVarInt<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            out.torso_damage = static_cast<std::int32_t>(*v);
        }
    }
    if (((out.slots) & (4)) != (0)) {
        {
            auto v = stream.readVarInt<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            out.legs_damage = static_cast<std::int32_t>(*v);
        }
    }
    if (((out.slots) & (8)) != (0)) {
        {
            auto v = stream.readVarInt<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            out.feet_damage = static_cast<std::int32_t>(*v);
        }
    }
    if (((out.slots) & (16)) != (0)) {
        {
            auto v = stream.readVarInt<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            out.body_damage = static_cast<std::int32_t>(*v);
        }
    }
    return out;
}

void Serializer<v844::PlayerArmorDamagePacket>::serialize(BinaryWriter &stream, const v844::PlayerArmorDamagePacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.slot_and_damage_pairs.size());
    for (const auto &e0 : value.slot_and_damage_pairs) {
        Serializer<ArmorSlotAndDamagePair>::serialize(stream, e0);
    }
}

auto Serializer<v844::PlayerArmorDamagePacket>::deserialize(BinaryReader &stream) -> std::expected<v844::PlayerArmorDamagePacket, std::error_code>
{
    v844::PlayerArmorDamagePacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.slot_and_damage_pairs.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.slot_and_damage_pairs.emplace_back();
            auto v = Serializer<ArmorSlotAndDamagePair>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.slot_and_damage_pairs.back() = *v;
        }
    }
    return out;
}

void Serializer<PlayerFogPacket>::serialize(BinaryWriter &stream, const PlayerFogPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.fog_stack.size());
    for (const auto &e0 : value.fog_stack) {
        stream.write(e0);
    }
}

auto Serializer<PlayerFogPacket>::deserialize(BinaryReader &stream) -> std::expected<PlayerFogPacket, std::error_code>
{
    PlayerFogPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.fog_stack.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.fog_stack.emplace_back();
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.fog_stack.back() = *v;
        }
    }
    return out;
}

void Serializer<v786::UpdateClientOptionsPacket>::serialize(BinaryWriter &stream, const v786::UpdateClientOptionsPacket &value)
{
    stream.write<bool>(value.graphics_mode.has_value());
    if (value.graphics_mode.has_value()) {
        stream.write<std::uint8_t>((*value.graphics_mode));
    }
}

auto Serializer<v786::UpdateClientOptionsPacket>::deserialize(BinaryReader &stream) -> std::expected<v786::UpdateClientOptionsPacket, std::error_code>
{
    v786::UpdateClientOptionsPacket out;
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            GraphicsMode staged{};
            auto v = stream.read<std::uint8_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<GraphicsMode>(*v);
            out.graphics_mode = std::move(staged);
        }
    }
    return out;
}

void Serializer<v975::UpdateClientOptionsPacket>::serialize(BinaryWriter &stream, const v975::UpdateClientOptionsPacket &value)
{
    stream.write<bool>(value.graphics_mode.has_value());
    if (value.graphics_mode.has_value()) {
        stream.write<std::uint8_t>((*value.graphics_mode));
    }
    stream.write<bool>(value.filter_profanity.has_value());
    if (value.filter_profanity.has_value()) {
        stream.write<bool>((*value.filter_profanity));
    }
}

auto Serializer<v975::UpdateClientOptionsPacket>::deserialize(BinaryReader &stream) -> std::expected<v975::UpdateClientOptionsPacket, std::error_code>
{
    v975::UpdateClientOptionsPacket out;
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            GraphicsMode staged{};
            auto v = stream.read<std::uint8_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<GraphicsMode>(*v);
            out.graphics_mode = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.filter_profanity = std::move(staged);
        }
    }
    return out;
}

void Serializer<base::PlayerListEntry>::serialize(BinaryWriter &stream, const base::PlayerListEntry &value)
{
    Serializer<UUID>::serialize(stream, value.uuid);
    stream.writeVarInt<std::int64_t>(value.id);
    stream.write(value.name);
    stream.write(value.xuid);
    stream.write(value.platform_online_id);
    stream.write<std::int32_t>(value.build_platform);
    Serializer<legacy::SerializedSkinRef>::serialize(stream, value.skin);
    stream.write<bool>(value.is_teacher);
    stream.write<bool>(value.is_host);
    stream.write<bool>(value.is_sub_client);
}

auto Serializer<base::PlayerListEntry>::deserialize(BinaryReader &stream) -> std::expected<base::PlayerListEntry, std::error_code>
{
    base::PlayerListEntry out;
    {
        auto v = Serializer<UUID>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.uuid = *v;
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.xuid = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.platform_online_id = *v;
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.build_platform = static_cast<BuildPlatform>(*v);
    }
    {
        auto v = Serializer<legacy::SerializedSkinRef>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.skin = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_teacher = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_host = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_sub_client = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v800::PlayerListEntry>::serialize(BinaryWriter &stream, const v800::PlayerListEntry &value)
{
    Serializer<UUID>::serialize(stream, value.uuid);
    stream.writeVarInt<std::int64_t>(value.id);
    stream.write(value.name);
    stream.write(value.xuid);
    stream.write(value.platform_online_id);
    stream.write<std::int32_t>(value.build_platform);
    Serializer<legacy::SerializedSkinRef>::serialize(stream, value.skin);
    stream.write<bool>(value.is_teacher);
    stream.write<bool>(value.is_host);
    stream.write<bool>(value.is_sub_client);
    stream.write<std::int32_t>(value.color);
}

auto Serializer<v800::PlayerListEntry>::deserialize(BinaryReader &stream) -> std::expected<v800::PlayerListEntry, std::error_code>
{
    v800::PlayerListEntry out;
    {
        auto v = Serializer<UUID>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.uuid = *v;
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.xuid = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.platform_online_id = *v;
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.build_platform = static_cast<BuildPlatform>(*v);
    }
    {
        auto v = Serializer<legacy::SerializedSkinRef>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.skin = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_teacher = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_host = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_sub_client = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.color = static_cast<Color>(*v);
    }
    return out;
}

void Serializer<base::PlayerListPacket::RemoveEntry>::serialize(BinaryWriter &stream, const base::PlayerListPacket::RemoveEntry &value)
{
    stream.write<std::uint8_t>(value.action);
    Serializer<UUID>::serialize(stream, value.uuid);
}

auto Serializer<base::PlayerListPacket::RemoveEntry>::deserialize(BinaryReader &stream) -> std::expected<base::PlayerListPacket::RemoveEntry, std::error_code>
{
    base::PlayerListPacket::RemoveEntry out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.action = static_cast<PlayerListPacketType>(*v);
    }
    {
        auto v = Serializer<UUID>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.uuid = *v;
    }
    return out;
}

void Serializer<base::PlayerListPacket::AddEntry>::serialize(BinaryWriter &stream, const base::PlayerListPacket::AddEntry &value)
{
    stream.write<std::uint8_t>(value.action);
    Serializer<UUID>::serialize(stream, value.uuid);
    stream.writeVarInt<std::int64_t>(value.id);
    stream.write(value.name);
    stream.write(value.xuid);
    stream.write(value.platform_online_id);
    stream.write<std::int32_t>(value.build_platform);
    Serializer<base::SerializedSkinRef>::serialize(stream, value.skin);
    stream.write<bool>(value.is_teacher);
    stream.write<bool>(value.is_host);
    stream.write<bool>(value.is_sub_client);
    stream.write<std::int32_t>(value.color);
}

auto Serializer<base::PlayerListPacket::AddEntry>::deserialize(BinaryReader &stream) -> std::expected<base::PlayerListPacket::AddEntry, std::error_code>
{
    base::PlayerListPacket::AddEntry out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.action = static_cast<PlayerListPacketType>(*v);
    }
    {
        auto v = Serializer<UUID>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.uuid = *v;
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.xuid = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.platform_online_id = *v;
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.build_platform = static_cast<BuildPlatform>(*v);
    }
    {
        auto v = Serializer<base::SerializedSkinRef>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.skin = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_teacher = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_host = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_sub_client = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.color = static_cast<Color>(*v);
    }
    return out;
}

void Serializer<v800::PlayerListPacket::AddEntry>::serialize(BinaryWriter &stream, const v800::PlayerListPacket::AddEntry &value)
{
    stream.write<std::uint8_t>(value.action);
    Serializer<UUID>::serialize(stream, value.uuid);
    stream.writeVarInt<std::int64_t>(value.id);
    stream.write(value.name);
    stream.write(value.xuid);
    stream.write(value.platform_online_id);
    stream.write<std::int32_t>(value.build_platform);
    Serializer<base::SerializedSkinRef>::serialize(stream, value.skin);
    stream.write<bool>(value.is_teacher);
    stream.write<bool>(value.is_host);
    stream.write<bool>(value.is_sub_client);
    stream.write<std::int32_t>(value.color);
}

auto Serializer<v800::PlayerListPacket::AddEntry>::deserialize(BinaryReader &stream) -> std::expected<v800::PlayerListPacket::AddEntry, std::error_code>
{
    v800::PlayerListPacket::AddEntry out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.action = static_cast<PlayerListPacketType>(*v);
    }
    {
        auto v = Serializer<UUID>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.uuid = *v;
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.xuid = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.platform_online_id = *v;
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.build_platform = static_cast<BuildPlatform>(*v);
    }
    {
        auto v = Serializer<base::SerializedSkinRef>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.skin = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_teacher = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_host = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_sub_client = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.color = static_cast<Color>(*v);
    }
    return out;
}

void Serializer<v2168::PlayerListPacket::AddEntry>::serialize(BinaryWriter &stream, const v2168::PlayerListPacket::AddEntry &value)
{
    stream.write<std::uint8_t>(value.action);
    Serializer<UUID>::serialize(stream, value.uuid);
    stream.writeVarInt<std::int64_t>(value.id);
    stream.write(value.name);
    stream.write(value.xuid);
    stream.write(value.platform_online_id);
    stream.write<std::int32_t>(value.build_platform);
    Serializer<v2168::SerializedSkinRef>::serialize(stream, value.skin);
    stream.write<bool>(value.is_teacher);
    stream.write<bool>(value.is_host);
    stream.write<bool>(value.is_sub_client);
    stream.write<std::int32_t>(value.color);
}

auto Serializer<v2168::PlayerListPacket::AddEntry>::deserialize(BinaryReader &stream) -> std::expected<v2168::PlayerListPacket::AddEntry, std::error_code>
{
    v2168::PlayerListPacket::AddEntry out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.action = static_cast<PlayerListPacketType>(*v);
    }
    {
        auto v = Serializer<UUID>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.uuid = *v;
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.xuid = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.platform_online_id = *v;
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.build_platform = static_cast<BuildPlatform>(*v);
    }
    {
        auto v = Serializer<v2168::SerializedSkinRef>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.skin = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_teacher = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_host = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_sub_client = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.color = static_cast<Color>(*v);
    }
    return out;
}

void Serializer<v2225::PlayerListPacket::AddEntry>::serialize(BinaryWriter &stream, const v2225::PlayerListPacket::AddEntry &value)
{
    stream.write<std::uint8_t>(value.action);
    Serializer<UUID>::serialize(stream, value.uuid);
    stream.writeVarInt<std::int64_t>(value.id);
    stream.write(value.name);
    stream.write(value.xuid);
    stream.write(value.play_fab_id);
    stream.write(value.platform_online_id);
    stream.write<std::int32_t>(value.build_platform);
    Serializer<v2225::SerializedSkinRef>::serialize(stream, value.skin);
    stream.write<bool>(value.is_teacher);
    stream.write<bool>(value.is_host);
    stream.write<bool>(value.is_sub_client);
    stream.write<std::int32_t>(value.color);
}

auto Serializer<v2225::PlayerListPacket::AddEntry>::deserialize(BinaryReader &stream) -> std::expected<v2225::PlayerListPacket::AddEntry, std::error_code>
{
    v2225::PlayerListPacket::AddEntry out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.action = static_cast<PlayerListPacketType>(*v);
    }
    {
        auto v = Serializer<UUID>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.uuid = *v;
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.xuid = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.play_fab_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.platform_online_id = *v;
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.build_platform = static_cast<BuildPlatform>(*v);
    }
    {
        auto v = Serializer<v2225::SerializedSkinRef>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.skin = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_teacher = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_host = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_sub_client = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.color = static_cast<Color>(*v);
    }
    return out;
}

void Serializer<base::PlayerListPacket>::serialize(BinaryWriter &stream, const base::PlayerListPacket &value)
{
    stream.write<std::uint8_t>(value.action);
    if ((value.action) == (PlayerListPacketType::Add)) {
        stream.writeVarInt<std::uint32_t>(value.entries.size());
        for (const auto &e0 : value.entries) {
            Serializer<base::PlayerListEntry>::serialize(stream, e0);
        }
    }
    if ((value.action) == (PlayerListPacketType::Remove)) {
        stream.writeVarInt<std::uint32_t>(value.removed_entries.size());
        for (const auto &e0 : value.removed_entries) {
            Serializer<UUID>::serialize(stream, e0);
        }
    }
    if ((value.action) == (PlayerListPacketType::Add)) {
        for (const auto &e0 : value.trusted_skins) {
            stream.write<bool>(e0);
        }
    }
}

auto Serializer<base::PlayerListPacket>::deserialize(BinaryReader &stream) -> std::expected<base::PlayerListPacket, std::error_code>
{
    base::PlayerListPacket out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.action = static_cast<PlayerListPacketType>(*v);
    }
    if ((out.action) == (PlayerListPacketType::Add)) {
        {
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            out.entries.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                out.entries.emplace_back();
                auto v = Serializer<base::PlayerListEntry>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                out.entries.back() = *v;
            }
        }
    }
    if ((out.action) == (PlayerListPacketType::Remove)) {
        {
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            out.removed_entries.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                out.removed_entries.emplace_back();
                auto v = Serializer<UUID>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                out.removed_entries.back() = *v;
            }
        }
    }
    if ((out.action) == (PlayerListPacketType::Add)) {
        {
            out.trusted_skins.clear();
            for (auto rep0 = out.entries.size(); rep0 > 0; --rep0) {
                out.trusted_skins.emplace_back();
                auto v = stream.read<bool>();
                if (!v) return std::unexpected(v.error());
                out.trusted_skins.back() = static_cast<bool>(*v);
            }
        }
    }
    return out;
}

void Serializer<v800::PlayerListPacket>::serialize(BinaryWriter &stream, const v800::PlayerListPacket &value)
{
    stream.write<std::uint8_t>(value.action);
    if ((value.action) == (PlayerListPacketType::Add)) {
        stream.writeVarInt<std::uint32_t>(value.entries.size());
        for (const auto &e0 : value.entries) {
            Serializer<v800::PlayerListEntry>::serialize(stream, e0);
        }
    }
    if ((value.action) == (PlayerListPacketType::Remove)) {
        stream.writeVarInt<std::uint32_t>(value.removed_entries.size());
        for (const auto &e0 : value.removed_entries) {
            Serializer<UUID>::serialize(stream, e0);
        }
    }
    if ((value.action) == (PlayerListPacketType::Add)) {
        for (const auto &e0 : value.trusted_skins) {
            stream.write<bool>(e0);
        }
    }
}

auto Serializer<v800::PlayerListPacket>::deserialize(BinaryReader &stream) -> std::expected<v800::PlayerListPacket, std::error_code>
{
    v800::PlayerListPacket out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.action = static_cast<PlayerListPacketType>(*v);
    }
    if ((out.action) == (PlayerListPacketType::Add)) {
        {
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            out.entries.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                out.entries.emplace_back();
                auto v = Serializer<v800::PlayerListEntry>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                out.entries.back() = *v;
            }
        }
    }
    if ((out.action) == (PlayerListPacketType::Remove)) {
        {
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            out.removed_entries.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                out.removed_entries.emplace_back();
                auto v = Serializer<UUID>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                out.removed_entries.back() = *v;
            }
        }
    }
    if ((out.action) == (PlayerListPacketType::Add)) {
        {
            out.trusted_skins.clear();
            for (auto rep0 = out.entries.size(); rep0 > 0; --rep0) {
                out.trusted_skins.emplace_back();
                auto v = stream.read<bool>();
                if (!v) return std::unexpected(v.error());
                out.trusted_skins.back() = static_cast<bool>(*v);
            }
        }
    }
    return out;
}

void Serializer<v2168::PlayerListPacket>::serialize(BinaryWriter &stream, const v2168::PlayerListPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.entries.size());
    for (const auto &e0 : value.entries) {
        stream.writeVarInt<std::uint32_t>((e0).index());
        switch ((e0).index()) {
            case 0: {
                Serializer<v2168::PlayerListPacket::RemoveEntry>::serialize(stream, std::get<0>(e0));
                break;
            }
            case 1: {
                Serializer<v2168::PlayerListPacket::AddEntry>::serialize(stream, std::get<1>(e0));
                break;
            }
        }
    }
}

auto Serializer<v2168::PlayerListPacket>::deserialize(BinaryReader &stream) -> std::expected<v2168::PlayerListPacket, std::error_code>
{
    v2168::PlayerListPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.entries.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.entries.emplace_back();
            auto tag1 = stream.readVarInt<std::uint32_t>();
            if (!tag1) return std::unexpected(tag1.error());
            std::variant<v2168::PlayerListPacket::RemoveEntry, v2168::PlayerListPacket::AddEntry> var1{};
            switch (*tag1) {
                case 0: {
                    std::variant_alternative_t<0, std::variant<v2168::PlayerListPacket::RemoveEntry, v2168::PlayerListPacket::AddEntry>> alt1{};
                    {
                        auto v = Serializer<v2168::PlayerListPacket::RemoveEntry>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<0>(alt1);
                    break;
                }
                case 1: {
                    std::variant_alternative_t<1, std::variant<v2168::PlayerListPacket::RemoveEntry, v2168::PlayerListPacket::AddEntry>> alt1{};
                    {
                        auto v = Serializer<v2168::PlayerListPacket::AddEntry>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<1>(alt1);
                    break;
                }
                default: {
                    return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
                }
            }
            out.entries.back() = var1;
        }
    }
    return out;
}

void Serializer<v2225::PlayerListPacket>::serialize(BinaryWriter &stream, const v2225::PlayerListPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.entries.size());
    for (const auto &e0 : value.entries) {
        stream.writeVarInt<std::uint32_t>((e0).index());
        switch ((e0).index()) {
            case 0: {
                Serializer<v2225::PlayerListPacket::RemoveEntry>::serialize(stream, std::get<0>(e0));
                break;
            }
            case 1: {
                Serializer<v2225::PlayerListPacket::AddEntry>::serialize(stream, std::get<1>(e0));
                break;
            }
        }
    }
}

auto Serializer<v2225::PlayerListPacket>::deserialize(BinaryReader &stream) -> std::expected<v2225::PlayerListPacket, std::error_code>
{
    v2225::PlayerListPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.entries.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.entries.emplace_back();
            auto tag1 = stream.readVarInt<std::uint32_t>();
            if (!tag1) return std::unexpected(tag1.error());
            std::variant<v2225::PlayerListPacket::RemoveEntry, v2225::PlayerListPacket::AddEntry> var1{};
            switch (*tag1) {
                case 0: {
                    std::variant_alternative_t<0, std::variant<v2225::PlayerListPacket::RemoveEntry, v2225::PlayerListPacket::AddEntry>> alt1{};
                    {
                        auto v = Serializer<v2225::PlayerListPacket::RemoveEntry>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<0>(alt1);
                    break;
                }
                case 1: {
                    std::variant_alternative_t<1, std::variant<v2225::PlayerListPacket::RemoveEntry, v2225::PlayerListPacket::AddEntry>> alt1{};
                    {
                        auto v = Serializer<v2225::PlayerListPacket::AddEntry>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<1>(alt1);
                    break;
                }
                default: {
                    return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
                }
            }
            out.entries.back() = var1;
        }
    }
    return out;
}

void Serializer<v786::PlayerUpdateEntityOverridesPacket::ClearOverride>::serialize(BinaryWriter &stream, const v786::PlayerUpdateEntityOverridesPacket::ClearOverride &value)
{
    stream.write("clearoverrides");
}

auto Serializer<v786::PlayerUpdateEntityOverridesPacket::ClearOverride>::deserialize(BinaryReader &stream) -> std::expected<v786::PlayerUpdateEntityOverridesPacket::ClearOverride, std::error_code>
{
    v786::PlayerUpdateEntityOverridesPacket::ClearOverride out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        if (*v != "clearoverrides") {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    return out;
}

void Serializer<v786::PlayerUpdateEntityOverridesPacket::RemoveOverride>::serialize(BinaryWriter &stream, const v786::PlayerUpdateEntityOverridesPacket::RemoveOverride &value)
{
    stream.write("removeoverride");
}

auto Serializer<v786::PlayerUpdateEntityOverridesPacket::RemoveOverride>::deserialize(BinaryReader &stream) -> std::expected<v786::PlayerUpdateEntityOverridesPacket::RemoveOverride, std::error_code>
{
    v786::PlayerUpdateEntityOverridesPacket::RemoveOverride out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        if (*v != "removeoverride") {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    return out;
}

void Serializer<v786::PlayerUpdateEntityOverridesPacket::IntOverride>::serialize(BinaryWriter &stream, const v786::PlayerUpdateEntityOverridesPacket::IntOverride &value)
{
    stream.write("setintoverride");
    stream.write<std::int32_t>(value.value);
}

auto Serializer<v786::PlayerUpdateEntityOverridesPacket::IntOverride>::deserialize(BinaryReader &stream) -> std::expected<v786::PlayerUpdateEntityOverridesPacket::IntOverride, std::error_code>
{
    v786::PlayerUpdateEntityOverridesPacket::IntOverride out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        if (*v != "setintoverride") {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.value = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<v786::PlayerUpdateEntityOverridesPacket::FloatOverride>::serialize(BinaryWriter &stream, const v786::PlayerUpdateEntityOverridesPacket::FloatOverride &value)
{
    stream.write("setfloatoverride");
    stream.write<float>(value.value);
}

auto Serializer<v786::PlayerUpdateEntityOverridesPacket::FloatOverride>::deserialize(BinaryReader &stream) -> std::expected<v786::PlayerUpdateEntityOverridesPacket::FloatOverride, std::error_code>
{
    v786::PlayerUpdateEntityOverridesPacket::FloatOverride out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        if (*v != "setfloatoverride") {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.value = static_cast<float>(*v);
    }
    return out;
}

void Serializer<v786::PlayerUpdateEntityOverridesPacket>::serialize(BinaryWriter &stream, const v786::PlayerUpdateEntityOverridesPacket &value)
{
    stream.writeVarInt<std::int64_t>(value.id);
    stream.writeVarInt<std::uint32_t>(value.property_index);
    stream.write<std::uint8_t>(value.update_type);
    if ((value.update_type) == (UpdateType::SetIntOverride)) {
        stream.write<std::int32_t>(value.int_value);
    }
    if ((value.update_type) == (UpdateType::SetFloatOverride)) {
        stream.write<float>(value.float_value);
    }
}

auto Serializer<v786::PlayerUpdateEntityOverridesPacket>::deserialize(BinaryReader &stream) -> std::expected<v786::PlayerUpdateEntityOverridesPacket, std::error_code>
{
    v786::PlayerUpdateEntityOverridesPacket out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.property_index = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.update_type = static_cast<UpdateType>(*v);
    }
    if ((out.update_type) == (UpdateType::SetIntOverride)) {
        {
            auto v = stream.read<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            out.int_value = static_cast<std::int32_t>(*v);
        }
    }
    if ((out.update_type) == (UpdateType::SetFloatOverride)) {
        {
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            out.float_value = static_cast<float>(*v);
        }
    }
    return out;
}

void Serializer<v2168::PlayerUpdateEntityOverridesPacket>::serialize(BinaryWriter &stream, const v2168::PlayerUpdateEntityOverridesPacket &value)
{
    stream.writeVarInt<std::int64_t>(value.id);
    stream.writeVarInt<std::uint32_t>(value.property_index);
    stream.writeVarInt<std::uint32_t>((value.update).index());
    switch ((value.update).index()) {
        case 0: {
            Serializer<v2168::PlayerUpdateEntityOverridesPacket::ClearOverride>::serialize(stream, std::get<0>(value.update));
            break;
        }
        case 1: {
            Serializer<v2168::PlayerUpdateEntityOverridesPacket::RemoveOverride>::serialize(stream, std::get<1>(value.update));
            break;
        }
        case 2: {
            Serializer<v2168::PlayerUpdateEntityOverridesPacket::IntOverride>::serialize(stream, std::get<2>(value.update));
            break;
        }
        case 3: {
            Serializer<v2168::PlayerUpdateEntityOverridesPacket::FloatOverride>::serialize(stream, std::get<3>(value.update));
            break;
        }
    }
}

auto Serializer<v2168::PlayerUpdateEntityOverridesPacket>::deserialize(BinaryReader &stream) -> std::expected<v2168::PlayerUpdateEntityOverridesPacket, std::error_code>
{
    v2168::PlayerUpdateEntityOverridesPacket out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.property_index = static_cast<std::uint32_t>(*v);
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v2168::PlayerUpdateEntityOverridesPacket::ClearOverride, v2168::PlayerUpdateEntityOverridesPacket::RemoveOverride, v2168::PlayerUpdateEntityOverridesPacket::IntOverride, v2168::PlayerUpdateEntityOverridesPacket::FloatOverride> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v2168::PlayerUpdateEntityOverridesPacket::ClearOverride, v2168::PlayerUpdateEntityOverridesPacket::RemoveOverride, v2168::PlayerUpdateEntityOverridesPacket::IntOverride, v2168::PlayerUpdateEntityOverridesPacket::FloatOverride>> alt0{};
                {
                    auto v = Serializer<v2168::PlayerUpdateEntityOverridesPacket::ClearOverride>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v2168::PlayerUpdateEntityOverridesPacket::ClearOverride, v2168::PlayerUpdateEntityOverridesPacket::RemoveOverride, v2168::PlayerUpdateEntityOverridesPacket::IntOverride, v2168::PlayerUpdateEntityOverridesPacket::FloatOverride>> alt0{};
                {
                    auto v = Serializer<v2168::PlayerUpdateEntityOverridesPacket::RemoveOverride>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<v2168::PlayerUpdateEntityOverridesPacket::ClearOverride, v2168::PlayerUpdateEntityOverridesPacket::RemoveOverride, v2168::PlayerUpdateEntityOverridesPacket::IntOverride, v2168::PlayerUpdateEntityOverridesPacket::FloatOverride>> alt0{};
                {
                    auto v = Serializer<v2168::PlayerUpdateEntityOverridesPacket::IntOverride>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<v2168::PlayerUpdateEntityOverridesPacket::ClearOverride, v2168::PlayerUpdateEntityOverridesPacket::RemoveOverride, v2168::PlayerUpdateEntityOverridesPacket::IntOverride, v2168::PlayerUpdateEntityOverridesPacket::FloatOverride>> alt0{};
                {
                    auto v = Serializer<v2168::PlayerUpdateEntityOverridesPacket::FloatOverride>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.update = var0;
    }
    return out;
}

void Serializer<v800::PlayerLocationPacket::CoordinatesLocation>::serialize(BinaryWriter &stream, const v800::PlayerLocationPacket::CoordinatesLocation &value)
{
    stream.writeVarInt<std::int32_t>(value.type);
    Serializer<Vec3>::serialize(stream, value.pos);
}

auto Serializer<v800::PlayerLocationPacket::CoordinatesLocation>::deserialize(BinaryReader &stream) -> std::expected<v800::PlayerLocationPacket::CoordinatesLocation, std::error_code>
{
    v800::PlayerLocationPacket::CoordinatesLocation out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<v800::PlayerLocationPacket::Type>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    return out;
}

void Serializer<v800::PlayerLocationPacket::HiddenLocation>::serialize(BinaryWriter &stream, const v800::PlayerLocationPacket::HiddenLocation &value)
{
    stream.writeVarInt<std::int32_t>(value.type);
}

auto Serializer<v800::PlayerLocationPacket::HiddenLocation>::deserialize(BinaryReader &stream) -> std::expected<v800::PlayerLocationPacket::HiddenLocation, std::error_code>
{
    v800::PlayerLocationPacket::HiddenLocation out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<v800::PlayerLocationPacket::Type>(*v);
    }
    return out;
}

void Serializer<v800::PlayerLocationPacket>::serialize(BinaryWriter &stream, const v800::PlayerLocationPacket &value)
{
    stream.write<std::int32_t>(value.type);
    stream.writeVarInt<std::int64_t>(value.id);
    if ((value.type) == (v800::PlayerLocationPacket::Type::PlayerLocationCoordinates)) {
        Serializer<Vec3>::serialize(stream, value.pos);
    }
}

auto Serializer<v800::PlayerLocationPacket>::deserialize(BinaryReader &stream) -> std::expected<v800::PlayerLocationPacket, std::error_code>
{
    v800::PlayerLocationPacket out;
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<v800::PlayerLocationPacket::Type>(*v);
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.id = static_cast<ActorUniqueID>(*v);
    }
    if ((out.type) == (v800::PlayerLocationPacket::Type::PlayerLocationCoordinates)) {
        {
            auto v = Serializer<Vec3>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.pos = *v;
        }
    }
    return out;
}

void Serializer<v2168::PlayerLocationPacket>::serialize(BinaryWriter &stream, const v2168::PlayerLocationPacket &value)
{
    stream.writeVarInt<std::int64_t>(value.id);
    stream.writeVarInt<std::uint32_t>((value.location).index());
    switch ((value.location).index()) {
        case 0: {
            Serializer<v2168::PlayerLocationPacket::CoordinatesLocation>::serialize(stream, std::get<0>(value.location));
            break;
        }
        case 1: {
            Serializer<v2168::PlayerLocationPacket::HiddenLocation>::serialize(stream, std::get<1>(value.location));
            break;
        }
    }
}

auto Serializer<v2168::PlayerLocationPacket>::deserialize(BinaryReader &stream) -> std::expected<v2168::PlayerLocationPacket, std::error_code>
{
    v2168::PlayerLocationPacket out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v2168::PlayerLocationPacket::CoordinatesLocation, v2168::PlayerLocationPacket::HiddenLocation> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v2168::PlayerLocationPacket::CoordinatesLocation, v2168::PlayerLocationPacket::HiddenLocation>> alt0{};
                {
                    auto v = Serializer<v2168::PlayerLocationPacket::CoordinatesLocation>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v2168::PlayerLocationPacket::CoordinatesLocation, v2168::PlayerLocationPacket::HiddenLocation>> alt0{};
                {
                    auto v = Serializer<v2168::PlayerLocationPacket::HiddenLocation>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.location = var0;
    }
    return out;
}

void Serializer<base::AddPlayerPacket>::serialize(BinaryWriter &stream, const base::AddPlayerPacket &value)
{
    Serializer<UUID>::serialize(stream, value.uuid);
    stream.write(value.name);
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    stream.write(value.platform_online_id);
    Serializer<Vec3>::serialize(stream, value.pos);
    Serializer<Vec3>::serialize(stream, value.velocity);
    Serializer<Vec2>::serialize(stream, value.rot);
    stream.write<float>(value.y_head_rot);
    Serializer<NetworkItemStackDescriptor>::serialize(stream, value.carried_item);
    stream.writeVarInt<std::int32_t>(value.player_game_type);
    Serializer<base::SynchedActorData::CopyableDataList>::serialize(stream, value.unpack);
    Serializer<PropertySyncData>::serialize(stream, value.synched_properties);
    Serializer<base::SerializedAbilitiesData>::serialize(stream, value.abilities_data);
    stream.writeVarInt<std::uint32_t>(value.links.size());
    for (const auto &e0 : value.links) {
        Serializer<ActorLink>::serialize(stream, e0);
    }
    stream.write(value.device_id);
    stream.write<std::int32_t>(value.build_platform);
}

auto Serializer<base::AddPlayerPacket>::deserialize(BinaryReader &stream) -> std::expected<base::AddPlayerPacket, std::error_code>
{
    base::AddPlayerPacket out;
    {
        auto v = Serializer<UUID>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.uuid = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.platform_online_id = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.velocity = *v;
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.rot = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.y_head_rot = static_cast<float>(*v);
    }
    {
        auto v = Serializer<NetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.carried_item = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.player_game_type = static_cast<GameType>(*v);
    }
    {
        auto v = Serializer<base::SynchedActorData::CopyableDataList>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.unpack = *v;
    }
    {
        auto v = Serializer<PropertySyncData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.synched_properties = *v;
    }
    {
        auto v = Serializer<base::SerializedAbilitiesData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.abilities_data = *v;
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.links.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.links.emplace_back();
            auto v = Serializer<ActorLink>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.links.back() = *v;
        }
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.device_id = *v;
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.build_platform = static_cast<BuildPlatform>(*v);
    }
    return out;
}

void Serializer<v776::AddPlayerPacket>::serialize(BinaryWriter &stream, const v776::AddPlayerPacket &value)
{
    Serializer<UUID>::serialize(stream, value.uuid);
    stream.write(value.name);
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    stream.write(value.platform_online_id);
    Serializer<Vec3>::serialize(stream, value.pos);
    Serializer<Vec3>::serialize(stream, value.velocity);
    Serializer<Vec2>::serialize(stream, value.rot);
    stream.write<float>(value.y_head_rot);
    Serializer<NetworkItemStackDescriptor>::serialize(stream, value.carried_item);
    stream.writeVarInt<std::int32_t>(value.player_game_type);
    Serializer<base::SynchedActorData::CopyableDataList>::serialize(stream, value.unpack);
    Serializer<PropertySyncData>::serialize(stream, value.synched_properties);
    Serializer<v776::SerializedAbilitiesData>::serialize(stream, value.abilities_data);
    stream.writeVarInt<std::uint32_t>(value.links.size());
    for (const auto &e0 : value.links) {
        Serializer<ActorLink>::serialize(stream, e0);
    }
    stream.write(value.device_id);
    stream.write<std::int32_t>(value.build_platform);
}

auto Serializer<v776::AddPlayerPacket>::deserialize(BinaryReader &stream) -> std::expected<v776::AddPlayerPacket, std::error_code>
{
    v776::AddPlayerPacket out;
    {
        auto v = Serializer<UUID>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.uuid = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.platform_online_id = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.velocity = *v;
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.rot = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.y_head_rot = static_cast<float>(*v);
    }
    {
        auto v = Serializer<NetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.carried_item = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.player_game_type = static_cast<GameType>(*v);
    }
    {
        auto v = Serializer<base::SynchedActorData::CopyableDataList>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.unpack = *v;
    }
    {
        auto v = Serializer<PropertySyncData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.synched_properties = *v;
    }
    {
        auto v = Serializer<v776::SerializedAbilitiesData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.abilities_data = *v;
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.links.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.links.emplace_back();
            auto v = Serializer<ActorLink>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.links.back() = *v;
        }
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.device_id = *v;
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.build_platform = static_cast<BuildPlatform>(*v);
    }
    return out;
}

void Serializer<v2168::AddPlayerPacket>::serialize(BinaryWriter &stream, const v2168::AddPlayerPacket &value)
{
    Serializer<UUID>::serialize(stream, value.uuid);
    stream.write(value.name);
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    stream.write(value.platform_online_id);
    Serializer<Vec3>::serialize(stream, value.pos);
    Serializer<Vec3>::serialize(stream, value.velocity);
    Serializer<Vec2>::serialize(stream, value.rot);
    stream.write<float>(value.y_head_rot);
    Serializer<v2168::SerializedNetworkItemStackDescriptor>::serialize(stream, value.carried_item);
    stream.writeVarInt<std::int32_t>(value.player_game_type);
    Serializer<v2168::SynchedActorData::CopyableDataList>::serialize(stream, value.unpack);
    Serializer<PropertySyncData>::serialize(stream, value.synched_properties);
    Serializer<v776::SerializedAbilitiesData>::serialize(stream, value.abilities_data);
    stream.writeVarInt<std::uint32_t>(value.links.size());
    for (const auto &e0 : value.links) {
        Serializer<ActorLink>::serialize(stream, e0);
    }
    stream.write(value.device_id);
    stream.write<std::int32_t>(value.build_platform);
}

auto Serializer<v2168::AddPlayerPacket>::deserialize(BinaryReader &stream) -> std::expected<v2168::AddPlayerPacket, std::error_code>
{
    v2168::AddPlayerPacket out;
    {
        auto v = Serializer<UUID>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.uuid = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.platform_online_id = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.velocity = *v;
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.rot = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.y_head_rot = static_cast<float>(*v);
    }
    {
        auto v = Serializer<v2168::SerializedNetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.carried_item = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.player_game_type = static_cast<GameType>(*v);
    }
    {
        auto v = Serializer<v2168::SynchedActorData::CopyableDataList>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.unpack = *v;
    }
    {
        auto v = Serializer<PropertySyncData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.synched_properties = *v;
    }
    {
        auto v = Serializer<v776::SerializedAbilitiesData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.abilities_data = *v;
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.links.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.links.emplace_back();
            auto v = Serializer<ActorLink>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.links.back() = *v;
        }
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.device_id = *v;
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.build_platform = static_cast<BuildPlatform>(*v);
    }
    return out;
}

void Serializer<v2225::AddPlayerPacket>::serialize(BinaryWriter &stream, const v2225::AddPlayerPacket &value)
{
    Serializer<UUID>::serialize(stream, value.uuid);
    stream.write(value.name);
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    stream.write(value.platform_online_id);
    Serializer<Vec3>::serialize(stream, value.pos);
    Serializer<Vec3>::serialize(stream, value.velocity);
    Serializer<Vec2>::serialize(stream, value.rot);
    stream.write<float>(value.y_head_rot);
    Serializer<v2168::SerializedNetworkItemStackDescriptor>::serialize(stream, value.carried_item);
    stream.writeVarInt<std::int32_t>(value.player_game_type);
    Serializer<v2168::SynchedActorData::CopyableDataList>::serialize(stream, value.unpack);
    Serializer<PropertySyncData>::serialize(stream, value.synched_properties);
    Serializer<v776::SerializedAbilitiesData>::serialize(stream, value.abilities_data);
    stream.writeVarInt<std::uint32_t>(value.links.size());
    for (const auto &e0 : value.links) {
        Serializer<ActorLink>::serialize(stream, e0);
    }
    stream.write<bool>(value.passenger_block_data.has_value());
    if (value.passenger_block_data.has_value()) {
        Serializer<PassengerOfBlockArguments>::serialize(stream, (*value.passenger_block_data));
    }
    stream.write(value.device_id);
    stream.write<std::int32_t>(value.build_platform);
}

auto Serializer<v2225::AddPlayerPacket>::deserialize(BinaryReader &stream) -> std::expected<v2225::AddPlayerPacket, std::error_code>
{
    v2225::AddPlayerPacket out;
    {
        auto v = Serializer<UUID>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.uuid = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.platform_online_id = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.velocity = *v;
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.rot = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.y_head_rot = static_cast<float>(*v);
    }
    {
        auto v = Serializer<v2168::SerializedNetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.carried_item = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.player_game_type = static_cast<GameType>(*v);
    }
    {
        auto v = Serializer<v2168::SynchedActorData::CopyableDataList>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.unpack = *v;
    }
    {
        auto v = Serializer<PropertySyncData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.synched_properties = *v;
    }
    {
        auto v = Serializer<v776::SerializedAbilitiesData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.abilities_data = *v;
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.links.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.links.emplace_back();
            auto v = Serializer<ActorLink>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.links.back() = *v;
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            PassengerOfBlockArguments staged{};
            auto v = Serializer<PassengerOfBlockArguments>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.passenger_block_data = std::move(staged);
        }
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.device_id = *v;
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.build_platform = static_cast<BuildPlatform>(*v);
    }
    return out;
}

}  // namespace bedrock::protocol
