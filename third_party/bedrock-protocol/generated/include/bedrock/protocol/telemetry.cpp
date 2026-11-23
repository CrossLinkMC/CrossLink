#include <bedrock/protocol/telemetry.h>

namespace bedrock::protocol {


void Serializer<base::LegacyTelemetryEventPacket::Achievement>::serialize(BinaryWriter &stream, const base::LegacyTelemetryEventPacket::Achievement &value)
{
    stream.write<std::uint8_t>(value.achievement_id);
}

auto Serializer<base::LegacyTelemetryEventPacket::Achievement>::deserialize(BinaryReader &stream) -> std::expected<base::LegacyTelemetryEventPacket::Achievement, std::error_code>
{
    base::LegacyTelemetryEventPacket::Achievement out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.achievement_id = static_cast<base::MinecraftEventing::AchievementIds>(*v);
    }
    return out;
}

void Serializer<base::LegacyTelemetryEventPacket::Interaction>::serialize(BinaryWriter &stream, const base::LegacyTelemetryEventPacket::Interaction &value)
{
    stream.writeVarInt<std::int64_t>(value.interacted_entity_id);
    stream.write<std::uint8_t>(value.interaction_type);
    stream.writeVarInt<std::int32_t>(value.interacted_entity_type);
    stream.writeVarInt<std::int32_t>(value.interacted_entity_variant);
    stream.write<std::uint8_t>(value.interacted_entity_color);
}

auto Serializer<base::LegacyTelemetryEventPacket::Interaction>::deserialize(BinaryReader &stream) -> std::expected<base::LegacyTelemetryEventPacket::Interaction, std::error_code>
{
    base::LegacyTelemetryEventPacket::Interaction out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.interacted_entity_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.interaction_type = static_cast<base::MinecraftEventing::InteractionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.interacted_entity_type = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.interacted_entity_variant = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.interacted_entity_color = static_cast<std::uint8_t>(*v);
    }
    return out;
}

void Serializer<base::LegacyTelemetryEventPacket::PortalCreated>::serialize(BinaryWriter &stream, const base::LegacyTelemetryEventPacket::PortalCreated &value)
{
    stream.writeVarInt<std::int32_t>(value.built_in_dimension);
}

auto Serializer<base::LegacyTelemetryEventPacket::PortalCreated>::deserialize(BinaryReader &stream) -> std::expected<base::LegacyTelemetryEventPacket::PortalCreated, std::error_code>
{
    base::LegacyTelemetryEventPacket::PortalCreated out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.built_in_dimension = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<base::LegacyTelemetryEventPacket::PortalUsed>::serialize(BinaryWriter &stream, const base::LegacyTelemetryEventPacket::PortalUsed &value)
{
    stream.writeVarInt<std::int32_t>(value.from_dimension);
    stream.writeVarInt<std::int32_t>(value.to_dimension);
}

auto Serializer<base::LegacyTelemetryEventPacket::PortalUsed>::deserialize(BinaryReader &stream) -> std::expected<base::LegacyTelemetryEventPacket::PortalUsed, std::error_code>
{
    base::LegacyTelemetryEventPacket::PortalUsed out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.from_dimension = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.to_dimension = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<base::LegacyTelemetryEventPacket::MobKilled>::serialize(BinaryWriter &stream, const base::LegacyTelemetryEventPacket::MobKilled &value)
{
    stream.writeVarInt<std::int64_t>(value.killer_entity_id);
    stream.writeVarInt<std::int64_t>(value.killed_mob_id);
    stream.writeVarInt<std::int32_t>(value.damage_child_type);
    stream.writeVarInt<std::int32_t>(value.damage_source);
    stream.writeVarInt<std::int32_t>(value.trader_tier);
    stream.write(value.trader_name);
}

auto Serializer<base::LegacyTelemetryEventPacket::MobKilled>::deserialize(BinaryReader &stream) -> std::expected<base::LegacyTelemetryEventPacket::MobKilled, std::error_code>
{
    base::LegacyTelemetryEventPacket::MobKilled out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.killer_entity_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.killed_mob_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.damage_child_type = static_cast<base::ActorType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.damage_source = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.trader_tier = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.trader_name = *v;
    }
    return out;
}

void Serializer<base::LegacyTelemetryEventPacket::CauldronUsed>::serialize(BinaryWriter &stream, const base::LegacyTelemetryEventPacket::CauldronUsed &value)
{
    stream.writeVarInt<std::uint32_t>(value.contents_color);
    stream.writeVarInt<std::int32_t>(value.contents_type);
    stream.writeVarInt<std::int32_t>(value.fill_level);
}

auto Serializer<base::LegacyTelemetryEventPacket::CauldronUsed>::deserialize(BinaryReader &stream) -> std::expected<base::LegacyTelemetryEventPacket::CauldronUsed, std::error_code>
{
    base::LegacyTelemetryEventPacket::CauldronUsed out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.contents_color = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.contents_type = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.fill_level = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<base::LegacyTelemetryEventPacket::PlayerDied>::serialize(BinaryWriter &stream, const base::LegacyTelemetryEventPacket::PlayerDied &value)
{
    stream.writeVarInt<std::int32_t>(value.killer_id);
    stream.writeVarInt<std::int32_t>(value.killer_variant);
    stream.writeVarInt<std::int32_t>(value.damage_source);
    stream.write<bool>(value.in_raid);
}

auto Serializer<base::LegacyTelemetryEventPacket::PlayerDied>::deserialize(BinaryReader &stream) -> std::expected<base::LegacyTelemetryEventPacket::PlayerDied, std::error_code>
{
    base::LegacyTelemetryEventPacket::PlayerDied out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.killer_id = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.killer_variant = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.damage_source = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.in_raid = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<base::LegacyTelemetryEventPacket::BossKilled>::serialize(BinaryWriter &stream, const base::LegacyTelemetryEventPacket::BossKilled &value)
{
    stream.writeVarInt<std::int64_t>(value.boss_unique_id);
    stream.writeVarInt<std::int32_t>(value.party_size);
    stream.writeVarInt<std::int32_t>(value.boss_type);
}

auto Serializer<base::LegacyTelemetryEventPacket::BossKilled>::deserialize(BinaryReader &stream) -> std::expected<base::LegacyTelemetryEventPacket::BossKilled, std::error_code>
{
    base::LegacyTelemetryEventPacket::BossKilled out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.boss_unique_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.party_size = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.boss_type = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<base::LegacyTelemetryEventPacket::SlashCommand>::serialize(BinaryWriter &stream, const base::LegacyTelemetryEventPacket::SlashCommand &value)
{
    stream.writeVarInt<std::int32_t>(value.success_count);
    stream.writeVarInt<std::int32_t>(value.error_count);
    stream.write(value.command_name);
    stream.write(value.error_list);
}

auto Serializer<base::LegacyTelemetryEventPacket::SlashCommand>::deserialize(BinaryReader &stream) -> std::expected<base::LegacyTelemetryEventPacket::SlashCommand, std::error_code>
{
    base::LegacyTelemetryEventPacket::SlashCommand out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.success_count = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.error_count = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.command_name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.error_list = *v;
    }
    return out;
}

void Serializer<base::LegacyTelemetryEventPacket::MobBorn>::serialize(BinaryWriter &stream, const base::LegacyTelemetryEventPacket::MobBorn &value)
{
    stream.writeVarInt<std::int32_t>(value.baby_type);
    stream.writeVarInt<std::int32_t>(value.baby_variant);
    stream.write<std::uint8_t>(value.baby_color);
}

auto Serializer<base::LegacyTelemetryEventPacket::MobBorn>::deserialize(BinaryReader &stream) -> std::expected<base::LegacyTelemetryEventPacket::MobBorn, std::error_code>
{
    base::LegacyTelemetryEventPacket::MobBorn out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.baby_type = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.baby_variant = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.baby_color = static_cast<std::uint8_t>(*v);
    }
    return out;
}

void Serializer<base::LegacyTelemetryEventPacket::POICauldronUsed>::serialize(BinaryWriter &stream, const base::LegacyTelemetryEventPacket::POICauldronUsed &value)
{
    stream.write<std::uint8_t>(value.interaction_type);
    stream.writeVarInt<std::int32_t>(value.item_id);
}

auto Serializer<base::LegacyTelemetryEventPacket::POICauldronUsed>::deserialize(BinaryReader &stream) -> std::expected<base::LegacyTelemetryEventPacket::POICauldronUsed, std::error_code>
{
    base::LegacyTelemetryEventPacket::POICauldronUsed out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.interaction_type = static_cast<base::MinecraftEventing::POIBlockInteractionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.item_id = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<base::LegacyTelemetryEventPacket::ComposterUsed>::serialize(BinaryWriter &stream, const base::LegacyTelemetryEventPacket::ComposterUsed &value)
{
    stream.write<std::uint8_t>(value.interaction_type);
    stream.writeVarInt<std::int32_t>(value.item_id);
}

auto Serializer<base::LegacyTelemetryEventPacket::ComposterUsed>::deserialize(BinaryReader &stream) -> std::expected<base::LegacyTelemetryEventPacket::ComposterUsed, std::error_code>
{
    base::LegacyTelemetryEventPacket::ComposterUsed out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.interaction_type = static_cast<base::MinecraftEventing::POIBlockInteractionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.item_id = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<base::LegacyTelemetryEventPacket::BellUsed>::serialize(BinaryWriter &stream, const base::LegacyTelemetryEventPacket::BellUsed &value)
{
    stream.writeVarInt<std::int32_t>(value.item_id);
}

auto Serializer<base::LegacyTelemetryEventPacket::BellUsed>::deserialize(BinaryReader &stream) -> std::expected<base::LegacyTelemetryEventPacket::BellUsed, std::error_code>
{
    base::LegacyTelemetryEventPacket::BellUsed out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.item_id = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<base::LegacyTelemetryEventPacket::ActorDefinition>::serialize(BinaryWriter &stream, const base::LegacyTelemetryEventPacket::ActorDefinition &value)
{
    stream.write(value.event_name);
}

auto Serializer<base::LegacyTelemetryEventPacket::ActorDefinition>::deserialize(BinaryReader &stream) -> std::expected<base::LegacyTelemetryEventPacket::ActorDefinition, std::error_code>
{
    base::LegacyTelemetryEventPacket::ActorDefinition out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.event_name = *v;
    }
    return out;
}

void Serializer<base::LegacyTelemetryEventPacket::RaidUpdate>::serialize(BinaryWriter &stream, const base::LegacyTelemetryEventPacket::RaidUpdate &value)
{
    stream.writeVarInt<std::int32_t>(value.current_wave);
    stream.writeVarInt<std::int32_t>(value.total_waves);
    stream.write<bool>(value.success);
}

auto Serializer<base::LegacyTelemetryEventPacket::RaidUpdate>::deserialize(BinaryReader &stream) -> std::expected<base::LegacyTelemetryEventPacket::RaidUpdate, std::error_code>
{
    base::LegacyTelemetryEventPacket::RaidUpdate out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.current_wave = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.total_waves = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.success = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<base::LegacyTelemetryEventPacket::TargetBlockHit>::serialize(BinaryWriter &stream, const base::LegacyTelemetryEventPacket::TargetBlockHit &value)
{
    stream.writeVarInt<std::int32_t>(value.redstone_level);
}

auto Serializer<base::LegacyTelemetryEventPacket::TargetBlockHit>::deserialize(BinaryReader &stream) -> std::expected<base::LegacyTelemetryEventPacket::TargetBlockHit, std::error_code>
{
    base::LegacyTelemetryEventPacket::TargetBlockHit out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.redstone_level = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<base::LegacyTelemetryEventPacket::PiglinBarter>::serialize(BinaryWriter &stream, const base::LegacyTelemetryEventPacket::PiglinBarter &value)
{
    stream.writeVarInt<std::int32_t>(value.item_id);
    stream.write<bool>(value.was_targeting_bartering_player);
}

auto Serializer<base::LegacyTelemetryEventPacket::PiglinBarter>::deserialize(BinaryReader &stream) -> std::expected<base::LegacyTelemetryEventPacket::PiglinBarter, std::error_code>
{
    base::LegacyTelemetryEventPacket::PiglinBarter out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.item_id = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.was_targeting_bartering_player = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<base::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper>::serialize(BinaryWriter &stream, const base::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper &value)
{
    stream.writeVarInt<std::int32_t>(value.block_id);
}

auto Serializer<base::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper>::deserialize(BinaryReader &stream) -> std::expected<base::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, std::error_code>
{
    base::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.block_id = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<base::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction>::serialize(BinaryWriter &stream, const base::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction &value)
{
    stream.write(value.runtime_action);
}

auto Serializer<base::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction>::deserialize(BinaryReader &stream) -> std::expected<base::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, std::error_code>
{
    base::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.runtime_action = *v;
    }
    return out;
}

void Serializer<base::LegacyTelemetryEventPacket::CodeBuilderScoreboard>::serialize(BinaryWriter &stream, const base::LegacyTelemetryEventPacket::CodeBuilderScoreboard &value)
{
    stream.write(value.objective_name);
    stream.writeVarInt<std::int32_t>(value.score);
}

auto Serializer<base::LegacyTelemetryEventPacket::CodeBuilderScoreboard>::deserialize(BinaryReader &stream) -> std::expected<base::LegacyTelemetryEventPacket::CodeBuilderScoreboard, std::error_code>
{
    base::LegacyTelemetryEventPacket::CodeBuilderScoreboard out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.objective_name = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.score = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<base::LegacyTelemetryEventPacket::ItemUsed>::serialize(BinaryWriter &stream, const base::LegacyTelemetryEventPacket::ItemUsed &value)
{
    stream.write<std::int16_t>(value.item_id);
    stream.write<std::int32_t>(value.item_aux);
    stream.write<std::int32_t>(value.use_method);
    stream.write<std::int32_t>(value.count);
}

auto Serializer<base::LegacyTelemetryEventPacket::ItemUsed>::deserialize(BinaryReader &stream) -> std::expected<base::LegacyTelemetryEventPacket::ItemUsed, std::error_code>
{
    base::LegacyTelemetryEventPacket::ItemUsed out;
    {
        auto v = stream.read<std::int16_t>();
        if (!v) return std::unexpected(v.error());
        out.item_id = static_cast<std::int16_t>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.item_aux = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.use_method = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.count = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<base::LegacyTelemetryEventPacket::Empty>::serialize(BinaryWriter &stream, const base::LegacyTelemetryEventPacket::Empty &value)
{
}

auto Serializer<base::LegacyTelemetryEventPacket::Empty>::deserialize(BinaryReader &stream) -> std::expected<base::LegacyTelemetryEventPacket::Empty, std::error_code>
{
    base::LegacyTelemetryEventPacket::Empty out;
    return out;
}

void Serializer<v766::LegacyTelemetryEventPacket::Achievement>::serialize(BinaryWriter &stream, const v766::LegacyTelemetryEventPacket::Achievement &value)
{
    stream.write<std::uint8_t>(value.achievement_id);
}

auto Serializer<v766::LegacyTelemetryEventPacket::Achievement>::deserialize(BinaryReader &stream) -> std::expected<v766::LegacyTelemetryEventPacket::Achievement, std::error_code>
{
    v766::LegacyTelemetryEventPacket::Achievement out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.achievement_id = static_cast<v766::MinecraftEventing::AchievementIds>(*v);
    }
    return out;
}

void Serializer<v766::LegacyTelemetryEventPacket::Interaction>::serialize(BinaryWriter &stream, const v766::LegacyTelemetryEventPacket::Interaction &value)
{
    stream.writeVarInt<std::int64_t>(value.interacted_entity_id);
    stream.write<std::uint8_t>(value.interaction_type);
    stream.writeVarInt<std::int32_t>(value.interacted_entity_type);
    stream.writeVarInt<std::int32_t>(value.interacted_entity_variant);
    stream.write<std::uint8_t>(value.interacted_entity_color);
}

auto Serializer<v766::LegacyTelemetryEventPacket::Interaction>::deserialize(BinaryReader &stream) -> std::expected<v766::LegacyTelemetryEventPacket::Interaction, std::error_code>
{
    v766::LegacyTelemetryEventPacket::Interaction out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.interacted_entity_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.interaction_type = static_cast<v766::MinecraftEventing::InteractionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.interacted_entity_type = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.interacted_entity_variant = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.interacted_entity_color = static_cast<std::uint8_t>(*v);
    }
    return out;
}

void Serializer<v766::LegacyTelemetryEventPacket::MobKilled>::serialize(BinaryWriter &stream, const v766::LegacyTelemetryEventPacket::MobKilled &value)
{
    stream.writeVarInt<std::int64_t>(value.killer_entity_id);
    stream.writeVarInt<std::int64_t>(value.killed_mob_id);
    stream.writeVarInt<std::int32_t>(value.damage_child_type);
    stream.writeVarInt<std::int32_t>(value.damage_source);
    stream.writeVarInt<std::int32_t>(value.trader_tier);
    stream.write(value.trader_name);
}

auto Serializer<v766::LegacyTelemetryEventPacket::MobKilled>::deserialize(BinaryReader &stream) -> std::expected<v766::LegacyTelemetryEventPacket::MobKilled, std::error_code>
{
    v766::LegacyTelemetryEventPacket::MobKilled out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.killer_entity_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.killed_mob_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.damage_child_type = static_cast<v766::ActorType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.damage_source = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.trader_tier = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.trader_name = *v;
    }
    return out;
}

void Serializer<v766::LegacyTelemetryEventPacket::POICauldronUsed>::serialize(BinaryWriter &stream, const v766::LegacyTelemetryEventPacket::POICauldronUsed &value)
{
    stream.write<std::uint8_t>(value.interaction_type);
    stream.writeVarInt<std::int32_t>(value.item_id);
}

auto Serializer<v766::LegacyTelemetryEventPacket::POICauldronUsed>::deserialize(BinaryReader &stream) -> std::expected<v766::LegacyTelemetryEventPacket::POICauldronUsed, std::error_code>
{
    v766::LegacyTelemetryEventPacket::POICauldronUsed out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.interaction_type = static_cast<v766::MinecraftEventing::POIBlockInteractionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.item_id = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<v766::LegacyTelemetryEventPacket::ComposterUsed>::serialize(BinaryWriter &stream, const v766::LegacyTelemetryEventPacket::ComposterUsed &value)
{
    stream.write<std::uint8_t>(value.interaction_type);
    stream.writeVarInt<std::int32_t>(value.item_id);
}

auto Serializer<v766::LegacyTelemetryEventPacket::ComposterUsed>::deserialize(BinaryReader &stream) -> std::expected<v766::LegacyTelemetryEventPacket::ComposterUsed, std::error_code>
{
    v766::LegacyTelemetryEventPacket::ComposterUsed out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.interaction_type = static_cast<v766::MinecraftEventing::POIBlockInteractionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.item_id = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<v776::LegacyTelemetryEventPacket::Achievement>::serialize(BinaryWriter &stream, const v776::LegacyTelemetryEventPacket::Achievement &value)
{
    stream.write<std::uint8_t>(value.achievement_id);
}

auto Serializer<v776::LegacyTelemetryEventPacket::Achievement>::deserialize(BinaryReader &stream) -> std::expected<v776::LegacyTelemetryEventPacket::Achievement, std::error_code>
{
    v776::LegacyTelemetryEventPacket::Achievement out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.achievement_id = static_cast<v776::MinecraftEventing::AchievementIds>(*v);
    }
    return out;
}

void Serializer<v776::LegacyTelemetryEventPacket::Interaction>::serialize(BinaryWriter &stream, const v776::LegacyTelemetryEventPacket::Interaction &value)
{
    stream.writeVarInt<std::int64_t>(value.interacted_entity_id);
    stream.write<std::uint8_t>(value.interaction_type);
    stream.writeVarInt<std::int32_t>(value.interacted_entity_type);
    stream.writeVarInt<std::int32_t>(value.interacted_entity_variant);
    stream.write<std::uint8_t>(value.interacted_entity_color);
}

auto Serializer<v776::LegacyTelemetryEventPacket::Interaction>::deserialize(BinaryReader &stream) -> std::expected<v776::LegacyTelemetryEventPacket::Interaction, std::error_code>
{
    v776::LegacyTelemetryEventPacket::Interaction out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.interacted_entity_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.interaction_type = static_cast<v776::MinecraftEventing::InteractionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.interacted_entity_type = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.interacted_entity_variant = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.interacted_entity_color = static_cast<std::uint8_t>(*v);
    }
    return out;
}

void Serializer<v776::LegacyTelemetryEventPacket::MobKilled>::serialize(BinaryWriter &stream, const v776::LegacyTelemetryEventPacket::MobKilled &value)
{
    stream.writeVarInt<std::int64_t>(value.killer_entity_id);
    stream.writeVarInt<std::int64_t>(value.killed_mob_id);
    stream.writeVarInt<std::int32_t>(value.damage_child_type);
    stream.writeVarInt<std::int32_t>(value.damage_source);
    stream.writeVarInt<std::int32_t>(value.trader_tier);
    stream.write(value.trader_name);
}

auto Serializer<v776::LegacyTelemetryEventPacket::MobKilled>::deserialize(BinaryReader &stream) -> std::expected<v776::LegacyTelemetryEventPacket::MobKilled, std::error_code>
{
    v776::LegacyTelemetryEventPacket::MobKilled out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.killer_entity_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.killed_mob_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.damage_child_type = static_cast<v766::ActorType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.damage_source = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.trader_tier = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.trader_name = *v;
    }
    return out;
}

void Serializer<v776::LegacyTelemetryEventPacket::POICauldronUsed>::serialize(BinaryWriter &stream, const v776::LegacyTelemetryEventPacket::POICauldronUsed &value)
{
    stream.write<std::uint8_t>(value.interaction_type);
    stream.writeVarInt<std::int32_t>(value.item_id);
}

auto Serializer<v776::LegacyTelemetryEventPacket::POICauldronUsed>::deserialize(BinaryReader &stream) -> std::expected<v776::LegacyTelemetryEventPacket::POICauldronUsed, std::error_code>
{
    v776::LegacyTelemetryEventPacket::POICauldronUsed out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.interaction_type = static_cast<v776::MinecraftEventing::POIBlockInteractionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.item_id = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<v776::LegacyTelemetryEventPacket::ComposterUsed>::serialize(BinaryWriter &stream, const v776::LegacyTelemetryEventPacket::ComposterUsed &value)
{
    stream.write<std::uint8_t>(value.interaction_type);
    stream.writeVarInt<std::int32_t>(value.item_id);
}

auto Serializer<v776::LegacyTelemetryEventPacket::ComposterUsed>::deserialize(BinaryReader &stream) -> std::expected<v776::LegacyTelemetryEventPacket::ComposterUsed, std::error_code>
{
    v776::LegacyTelemetryEventPacket::ComposterUsed out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.interaction_type = static_cast<v776::MinecraftEventing::POIBlockInteractionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.item_id = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<v800::LegacyTelemetryEventPacket::Achievement>::serialize(BinaryWriter &stream, const v800::LegacyTelemetryEventPacket::Achievement &value)
{
    stream.write<std::uint8_t>(value.achievement_id);
}

auto Serializer<v800::LegacyTelemetryEventPacket::Achievement>::deserialize(BinaryReader &stream) -> std::expected<v800::LegacyTelemetryEventPacket::Achievement, std::error_code>
{
    v800::LegacyTelemetryEventPacket::Achievement out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.achievement_id = static_cast<v776::MinecraftEventing::AchievementIds>(*v);
    }
    return out;
}

void Serializer<v800::LegacyTelemetryEventPacket::Interaction>::serialize(BinaryWriter &stream, const v800::LegacyTelemetryEventPacket::Interaction &value)
{
    stream.writeVarInt<std::int64_t>(value.interacted_entity_id);
    stream.write<std::uint8_t>(value.interaction_type);
    stream.writeVarInt<std::int32_t>(value.interacted_entity_type);
    stream.writeVarInt<std::int32_t>(value.interacted_entity_variant);
    stream.write<std::uint8_t>(value.interacted_entity_color);
}

auto Serializer<v800::LegacyTelemetryEventPacket::Interaction>::deserialize(BinaryReader &stream) -> std::expected<v800::LegacyTelemetryEventPacket::Interaction, std::error_code>
{
    v800::LegacyTelemetryEventPacket::Interaction out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.interacted_entity_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.interaction_type = static_cast<v776::MinecraftEventing::InteractionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.interacted_entity_type = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.interacted_entity_variant = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.interacted_entity_color = static_cast<std::uint8_t>(*v);
    }
    return out;
}

void Serializer<v800::LegacyTelemetryEventPacket::MobKilled>::serialize(BinaryWriter &stream, const v800::LegacyTelemetryEventPacket::MobKilled &value)
{
    stream.writeVarInt<std::int64_t>(value.killer_entity_id);
    stream.writeVarInt<std::int64_t>(value.killed_mob_id);
    stream.writeVarInt<std::int32_t>(value.damage_child_type);
    stream.writeVarInt<std::int32_t>(value.damage_source);
    stream.writeVarInt<std::int32_t>(value.trader_tier);
    stream.write(value.trader_name);
}

auto Serializer<v800::LegacyTelemetryEventPacket::MobKilled>::deserialize(BinaryReader &stream) -> std::expected<v800::LegacyTelemetryEventPacket::MobKilled, std::error_code>
{
    v800::LegacyTelemetryEventPacket::MobKilled out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.killer_entity_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.killed_mob_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.damage_child_type = static_cast<v800::ActorType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.damage_source = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.trader_tier = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.trader_name = *v;
    }
    return out;
}

void Serializer<v800::LegacyTelemetryEventPacket::POICauldronUsed>::serialize(BinaryWriter &stream, const v800::LegacyTelemetryEventPacket::POICauldronUsed &value)
{
    stream.write<std::uint8_t>(value.interaction_type);
    stream.writeVarInt<std::int32_t>(value.item_id);
}

auto Serializer<v800::LegacyTelemetryEventPacket::POICauldronUsed>::deserialize(BinaryReader &stream) -> std::expected<v800::LegacyTelemetryEventPacket::POICauldronUsed, std::error_code>
{
    v800::LegacyTelemetryEventPacket::POICauldronUsed out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.interaction_type = static_cast<v776::MinecraftEventing::POIBlockInteractionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.item_id = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<v800::LegacyTelemetryEventPacket::ComposterUsed>::serialize(BinaryWriter &stream, const v800::LegacyTelemetryEventPacket::ComposterUsed &value)
{
    stream.write<std::uint8_t>(value.interaction_type);
    stream.writeVarInt<std::int32_t>(value.item_id);
}

auto Serializer<v800::LegacyTelemetryEventPacket::ComposterUsed>::deserialize(BinaryReader &stream) -> std::expected<v800::LegacyTelemetryEventPacket::ComposterUsed, std::error_code>
{
    v800::LegacyTelemetryEventPacket::ComposterUsed out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.interaction_type = static_cast<v776::MinecraftEventing::POIBlockInteractionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.item_id = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<v818::LegacyTelemetryEventPacket::Achievement>::serialize(BinaryWriter &stream, const v818::LegacyTelemetryEventPacket::Achievement &value)
{
    stream.write<std::uint8_t>(value.achievement_id);
}

auto Serializer<v818::LegacyTelemetryEventPacket::Achievement>::deserialize(BinaryReader &stream) -> std::expected<v818::LegacyTelemetryEventPacket::Achievement, std::error_code>
{
    v818::LegacyTelemetryEventPacket::Achievement out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.achievement_id = static_cast<v818::MinecraftEventing::AchievementIds>(*v);
    }
    return out;
}

void Serializer<v818::LegacyTelemetryEventPacket::Interaction>::serialize(BinaryWriter &stream, const v818::LegacyTelemetryEventPacket::Interaction &value)
{
    stream.writeVarInt<std::int64_t>(value.interacted_entity_id);
    stream.write<std::uint8_t>(value.interaction_type);
    stream.writeVarInt<std::int32_t>(value.interacted_entity_type);
    stream.writeVarInt<std::int32_t>(value.interacted_entity_variant);
    stream.write<std::uint8_t>(value.interacted_entity_color);
}

auto Serializer<v818::LegacyTelemetryEventPacket::Interaction>::deserialize(BinaryReader &stream) -> std::expected<v818::LegacyTelemetryEventPacket::Interaction, std::error_code>
{
    v818::LegacyTelemetryEventPacket::Interaction out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.interacted_entity_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.interaction_type = static_cast<v818::MinecraftEventing::InteractionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.interacted_entity_type = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.interacted_entity_variant = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.interacted_entity_color = static_cast<std::uint8_t>(*v);
    }
    return out;
}

void Serializer<v818::LegacyTelemetryEventPacket::MobKilled>::serialize(BinaryWriter &stream, const v818::LegacyTelemetryEventPacket::MobKilled &value)
{
    stream.writeVarInt<std::int64_t>(value.killer_entity_id);
    stream.writeVarInt<std::int64_t>(value.killed_mob_id);
    stream.writeVarInt<std::int32_t>(value.damage_child_type);
    stream.writeVarInt<std::int32_t>(value.damage_source);
    stream.writeVarInt<std::int32_t>(value.trader_tier);
    stream.write(value.trader_name);
}

auto Serializer<v818::LegacyTelemetryEventPacket::MobKilled>::deserialize(BinaryReader &stream) -> std::expected<v818::LegacyTelemetryEventPacket::MobKilled, std::error_code>
{
    v818::LegacyTelemetryEventPacket::MobKilled out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.killer_entity_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.killed_mob_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.damage_child_type = static_cast<v800::ActorType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.damage_source = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.trader_tier = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.trader_name = *v;
    }
    return out;
}

void Serializer<v818::LegacyTelemetryEventPacket::POICauldronUsed>::serialize(BinaryWriter &stream, const v818::LegacyTelemetryEventPacket::POICauldronUsed &value)
{
    stream.write<std::uint8_t>(value.interaction_type);
    stream.writeVarInt<std::int32_t>(value.item_id);
}

auto Serializer<v818::LegacyTelemetryEventPacket::POICauldronUsed>::deserialize(BinaryReader &stream) -> std::expected<v818::LegacyTelemetryEventPacket::POICauldronUsed, std::error_code>
{
    v818::LegacyTelemetryEventPacket::POICauldronUsed out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.interaction_type = static_cast<v818::MinecraftEventing::POIBlockInteractionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.item_id = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<v818::LegacyTelemetryEventPacket::ComposterUsed>::serialize(BinaryWriter &stream, const v818::LegacyTelemetryEventPacket::ComposterUsed &value)
{
    stream.write<std::uint8_t>(value.interaction_type);
    stream.writeVarInt<std::int32_t>(value.item_id);
}

auto Serializer<v818::LegacyTelemetryEventPacket::ComposterUsed>::deserialize(BinaryReader &stream) -> std::expected<v818::LegacyTelemetryEventPacket::ComposterUsed, std::error_code>
{
    v818::LegacyTelemetryEventPacket::ComposterUsed out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.interaction_type = static_cast<v818::MinecraftEventing::POIBlockInteractionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.item_id = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<v827::LegacyTelemetryEventPacket::Achievement>::serialize(BinaryWriter &stream, const v827::LegacyTelemetryEventPacket::Achievement &value)
{
    stream.write<std::uint8_t>(value.achievement_id);
}

auto Serializer<v827::LegacyTelemetryEventPacket::Achievement>::deserialize(BinaryReader &stream) -> std::expected<v827::LegacyTelemetryEventPacket::Achievement, std::error_code>
{
    v827::LegacyTelemetryEventPacket::Achievement out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.achievement_id = static_cast<v818::MinecraftEventing::AchievementIds>(*v);
    }
    return out;
}

void Serializer<v827::LegacyTelemetryEventPacket::Interaction>::serialize(BinaryWriter &stream, const v827::LegacyTelemetryEventPacket::Interaction &value)
{
    stream.writeVarInt<std::int64_t>(value.interacted_entity_id);
    stream.write<std::uint8_t>(value.interaction_type);
    stream.writeVarInt<std::int32_t>(value.interacted_entity_type);
    stream.writeVarInt<std::int32_t>(value.interacted_entity_variant);
    stream.write<std::uint8_t>(value.interacted_entity_color);
}

auto Serializer<v827::LegacyTelemetryEventPacket::Interaction>::deserialize(BinaryReader &stream) -> std::expected<v827::LegacyTelemetryEventPacket::Interaction, std::error_code>
{
    v827::LegacyTelemetryEventPacket::Interaction out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.interacted_entity_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.interaction_type = static_cast<v818::MinecraftEventing::InteractionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.interacted_entity_type = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.interacted_entity_variant = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.interacted_entity_color = static_cast<std::uint8_t>(*v);
    }
    return out;
}

void Serializer<v827::LegacyTelemetryEventPacket::MobKilled>::serialize(BinaryWriter &stream, const v827::LegacyTelemetryEventPacket::MobKilled &value)
{
    stream.writeVarInt<std::int64_t>(value.killer_entity_id);
    stream.writeVarInt<std::int64_t>(value.killed_mob_id);
    stream.writeVarInt<std::int32_t>(value.damage_child_type);
    stream.writeVarInt<std::int32_t>(value.damage_source);
    stream.writeVarInt<std::int32_t>(value.trader_tier);
    stream.write(value.trader_name);
}

auto Serializer<v827::LegacyTelemetryEventPacket::MobKilled>::deserialize(BinaryReader &stream) -> std::expected<v827::LegacyTelemetryEventPacket::MobKilled, std::error_code>
{
    v827::LegacyTelemetryEventPacket::MobKilled out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.killer_entity_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.killed_mob_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.damage_child_type = static_cast<v827::ActorType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.damage_source = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.trader_tier = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.trader_name = *v;
    }
    return out;
}

void Serializer<v827::LegacyTelemetryEventPacket::POICauldronUsed>::serialize(BinaryWriter &stream, const v827::LegacyTelemetryEventPacket::POICauldronUsed &value)
{
    stream.write<std::uint8_t>(value.interaction_type);
    stream.writeVarInt<std::int32_t>(value.item_id);
}

auto Serializer<v827::LegacyTelemetryEventPacket::POICauldronUsed>::deserialize(BinaryReader &stream) -> std::expected<v827::LegacyTelemetryEventPacket::POICauldronUsed, std::error_code>
{
    v827::LegacyTelemetryEventPacket::POICauldronUsed out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.interaction_type = static_cast<v818::MinecraftEventing::POIBlockInteractionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.item_id = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<v827::LegacyTelemetryEventPacket::ComposterUsed>::serialize(BinaryWriter &stream, const v827::LegacyTelemetryEventPacket::ComposterUsed &value)
{
    stream.write<std::uint8_t>(value.interaction_type);
    stream.writeVarInt<std::int32_t>(value.item_id);
}

auto Serializer<v827::LegacyTelemetryEventPacket::ComposterUsed>::deserialize(BinaryReader &stream) -> std::expected<v827::LegacyTelemetryEventPacket::ComposterUsed, std::error_code>
{
    v827::LegacyTelemetryEventPacket::ComposterUsed out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.interaction_type = static_cast<v818::MinecraftEventing::POIBlockInteractionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.item_id = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<v898::LegacyTelemetryEventPacket::Achievement>::serialize(BinaryWriter &stream, const v898::LegacyTelemetryEventPacket::Achievement &value)
{
    stream.write<std::uint8_t>(value.achievement_id);
}

auto Serializer<v898::LegacyTelemetryEventPacket::Achievement>::deserialize(BinaryReader &stream) -> std::expected<v898::LegacyTelemetryEventPacket::Achievement, std::error_code>
{
    v898::LegacyTelemetryEventPacket::Achievement out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.achievement_id = static_cast<v898::MinecraftEventing::AchievementIds>(*v);
    }
    return out;
}

void Serializer<v898::LegacyTelemetryEventPacket::Interaction>::serialize(BinaryWriter &stream, const v898::LegacyTelemetryEventPacket::Interaction &value)
{
    stream.writeVarInt<std::int64_t>(value.interacted_entity_id);
    stream.write<std::uint8_t>(value.interaction_type);
    stream.writeVarInt<std::int32_t>(value.interacted_entity_type);
    stream.writeVarInt<std::int32_t>(value.interacted_entity_variant);
    stream.write<std::uint8_t>(value.interacted_entity_color);
}

auto Serializer<v898::LegacyTelemetryEventPacket::Interaction>::deserialize(BinaryReader &stream) -> std::expected<v898::LegacyTelemetryEventPacket::Interaction, std::error_code>
{
    v898::LegacyTelemetryEventPacket::Interaction out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.interacted_entity_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.interaction_type = static_cast<v898::MinecraftEventing::InteractionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.interacted_entity_type = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.interacted_entity_variant = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.interacted_entity_color = static_cast<std::uint8_t>(*v);
    }
    return out;
}

void Serializer<v898::LegacyTelemetryEventPacket::MobKilled>::serialize(BinaryWriter &stream, const v898::LegacyTelemetryEventPacket::MobKilled &value)
{
    stream.writeVarInt<std::int64_t>(value.killer_entity_id);
    stream.writeVarInt<std::int64_t>(value.killed_mob_id);
    stream.writeVarInt<std::int32_t>(value.damage_child_type);
    stream.writeVarInt<std::int32_t>(value.damage_source);
    stream.writeVarInt<std::int32_t>(value.trader_tier);
    stream.write(value.trader_name);
}

auto Serializer<v898::LegacyTelemetryEventPacket::MobKilled>::deserialize(BinaryReader &stream) -> std::expected<v898::LegacyTelemetryEventPacket::MobKilled, std::error_code>
{
    v898::LegacyTelemetryEventPacket::MobKilled out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.killer_entity_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.killed_mob_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.damage_child_type = static_cast<v827::ActorType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.damage_source = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.trader_tier = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.trader_name = *v;
    }
    return out;
}

void Serializer<v898::LegacyTelemetryEventPacket::POICauldronUsed>::serialize(BinaryWriter &stream, const v898::LegacyTelemetryEventPacket::POICauldronUsed &value)
{
    stream.write<std::uint8_t>(value.interaction_type);
    stream.writeVarInt<std::int32_t>(value.item_id);
}

auto Serializer<v898::LegacyTelemetryEventPacket::POICauldronUsed>::deserialize(BinaryReader &stream) -> std::expected<v898::LegacyTelemetryEventPacket::POICauldronUsed, std::error_code>
{
    v898::LegacyTelemetryEventPacket::POICauldronUsed out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.interaction_type = static_cast<v898::MinecraftEventing::POIBlockInteractionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.item_id = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<v898::LegacyTelemetryEventPacket::ComposterUsed>::serialize(BinaryWriter &stream, const v898::LegacyTelemetryEventPacket::ComposterUsed &value)
{
    stream.write<std::uint8_t>(value.interaction_type);
    stream.writeVarInt<std::int32_t>(value.item_id);
}

auto Serializer<v898::LegacyTelemetryEventPacket::ComposterUsed>::deserialize(BinaryReader &stream) -> std::expected<v898::LegacyTelemetryEventPacket::ComposterUsed, std::error_code>
{
    v898::LegacyTelemetryEventPacket::ComposterUsed out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.interaction_type = static_cast<v898::MinecraftEventing::POIBlockInteractionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.item_id = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<v924::LegacyTelemetryEventPacket::Achievement>::serialize(BinaryWriter &stream, const v924::LegacyTelemetryEventPacket::Achievement &value)
{
    stream.write<std::uint8_t>(value.achievement_id);
}

auto Serializer<v924::LegacyTelemetryEventPacket::Achievement>::deserialize(BinaryReader &stream) -> std::expected<v924::LegacyTelemetryEventPacket::Achievement, std::error_code>
{
    v924::LegacyTelemetryEventPacket::Achievement out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.achievement_id = static_cast<v924::MinecraftEventing::AchievementIds>(*v);
    }
    return out;
}

void Serializer<v924::LegacyTelemetryEventPacket::Interaction>::serialize(BinaryWriter &stream, const v924::LegacyTelemetryEventPacket::Interaction &value)
{
    stream.writeVarInt<std::int64_t>(value.interacted_entity_id);
    stream.write<std::uint8_t>(value.interaction_type);
    stream.writeVarInt<std::int32_t>(value.interacted_entity_type);
    stream.writeVarInt<std::int32_t>(value.interacted_entity_variant);
    stream.write<std::uint8_t>(value.interacted_entity_color);
}

auto Serializer<v924::LegacyTelemetryEventPacket::Interaction>::deserialize(BinaryReader &stream) -> std::expected<v924::LegacyTelemetryEventPacket::Interaction, std::error_code>
{
    v924::LegacyTelemetryEventPacket::Interaction out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.interacted_entity_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.interaction_type = static_cast<v924::MinecraftEventing::InteractionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.interacted_entity_type = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.interacted_entity_variant = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.interacted_entity_color = static_cast<std::uint8_t>(*v);
    }
    return out;
}

void Serializer<v924::LegacyTelemetryEventPacket::MobKilled>::serialize(BinaryWriter &stream, const v924::LegacyTelemetryEventPacket::MobKilled &value)
{
    stream.writeVarInt<std::int64_t>(value.killer_entity_id);
    stream.writeVarInt<std::int64_t>(value.killed_mob_id);
    stream.writeVarInt<std::int32_t>(value.damage_child_type);
    stream.writeVarInt<std::int32_t>(value.damage_source);
    stream.writeVarInt<std::int32_t>(value.trader_tier);
    stream.write(value.trader_name);
}

auto Serializer<v924::LegacyTelemetryEventPacket::MobKilled>::deserialize(BinaryReader &stream) -> std::expected<v924::LegacyTelemetryEventPacket::MobKilled, std::error_code>
{
    v924::LegacyTelemetryEventPacket::MobKilled out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.killer_entity_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.killed_mob_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.damage_child_type = static_cast<v924::ActorType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.damage_source = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.trader_tier = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.trader_name = *v;
    }
    return out;
}

void Serializer<v924::LegacyTelemetryEventPacket::POICauldronUsed>::serialize(BinaryWriter &stream, const v924::LegacyTelemetryEventPacket::POICauldronUsed &value)
{
    stream.write<std::uint8_t>(value.interaction_type);
    stream.writeVarInt<std::int32_t>(value.item_id);
}

auto Serializer<v924::LegacyTelemetryEventPacket::POICauldronUsed>::deserialize(BinaryReader &stream) -> std::expected<v924::LegacyTelemetryEventPacket::POICauldronUsed, std::error_code>
{
    v924::LegacyTelemetryEventPacket::POICauldronUsed out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.interaction_type = static_cast<v924::MinecraftEventing::POIBlockInteractionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.item_id = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<v924::LegacyTelemetryEventPacket::ComposterUsed>::serialize(BinaryWriter &stream, const v924::LegacyTelemetryEventPacket::ComposterUsed &value)
{
    stream.write<std::uint8_t>(value.interaction_type);
    stream.writeVarInt<std::int32_t>(value.item_id);
}

auto Serializer<v924::LegacyTelemetryEventPacket::ComposterUsed>::deserialize(BinaryReader &stream) -> std::expected<v924::LegacyTelemetryEventPacket::ComposterUsed, std::error_code>
{
    v924::LegacyTelemetryEventPacket::ComposterUsed out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.interaction_type = static_cast<v924::MinecraftEventing::POIBlockInteractionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.item_id = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<v975::LegacyTelemetryEventPacket::Achievement>::serialize(BinaryWriter &stream, const v975::LegacyTelemetryEventPacket::Achievement &value)
{
    stream.write<std::uint8_t>(value.achievement_id);
}

auto Serializer<v975::LegacyTelemetryEventPacket::Achievement>::deserialize(BinaryReader &stream) -> std::expected<v975::LegacyTelemetryEventPacket::Achievement, std::error_code>
{
    v975::LegacyTelemetryEventPacket::Achievement out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.achievement_id = static_cast<v924::MinecraftEventing::AchievementIds>(*v);
    }
    return out;
}

void Serializer<v975::LegacyTelemetryEventPacket::Interaction>::serialize(BinaryWriter &stream, const v975::LegacyTelemetryEventPacket::Interaction &value)
{
    stream.writeVarInt<std::int64_t>(value.interacted_entity_id);
    stream.write<std::uint8_t>(value.interaction_type);
    stream.writeVarInt<std::int32_t>(value.interacted_entity_type);
    stream.writeVarInt<std::int32_t>(value.interacted_entity_variant);
    stream.write<std::uint8_t>(value.interacted_entity_color);
}

auto Serializer<v975::LegacyTelemetryEventPacket::Interaction>::deserialize(BinaryReader &stream) -> std::expected<v975::LegacyTelemetryEventPacket::Interaction, std::error_code>
{
    v975::LegacyTelemetryEventPacket::Interaction out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.interacted_entity_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.interaction_type = static_cast<v924::MinecraftEventing::InteractionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.interacted_entity_type = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.interacted_entity_variant = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.interacted_entity_color = static_cast<std::uint8_t>(*v);
    }
    return out;
}

void Serializer<v975::LegacyTelemetryEventPacket::MobKilled>::serialize(BinaryWriter &stream, const v975::LegacyTelemetryEventPacket::MobKilled &value)
{
    stream.writeVarInt<std::int64_t>(value.killer_entity_id);
    stream.writeVarInt<std::int64_t>(value.killed_mob_id);
    stream.writeVarInt<std::int32_t>(value.damage_child_type);
    stream.writeVarInt<std::int32_t>(value.damage_source);
    stream.writeVarInt<std::int32_t>(value.trader_tier);
    stream.write(value.trader_name);
}

auto Serializer<v975::LegacyTelemetryEventPacket::MobKilled>::deserialize(BinaryReader &stream) -> std::expected<v975::LegacyTelemetryEventPacket::MobKilled, std::error_code>
{
    v975::LegacyTelemetryEventPacket::MobKilled out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.killer_entity_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.killed_mob_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.damage_child_type = static_cast<v975::ActorType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.damage_source = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.trader_tier = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.trader_name = *v;
    }
    return out;
}

void Serializer<v975::LegacyTelemetryEventPacket::POICauldronUsed>::serialize(BinaryWriter &stream, const v975::LegacyTelemetryEventPacket::POICauldronUsed &value)
{
    stream.write<std::uint8_t>(value.interaction_type);
    stream.writeVarInt<std::int32_t>(value.item_id);
}

auto Serializer<v975::LegacyTelemetryEventPacket::POICauldronUsed>::deserialize(BinaryReader &stream) -> std::expected<v975::LegacyTelemetryEventPacket::POICauldronUsed, std::error_code>
{
    v975::LegacyTelemetryEventPacket::POICauldronUsed out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.interaction_type = static_cast<v924::MinecraftEventing::POIBlockInteractionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.item_id = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<v975::LegacyTelemetryEventPacket::ComposterUsed>::serialize(BinaryWriter &stream, const v975::LegacyTelemetryEventPacket::ComposterUsed &value)
{
    stream.write<std::uint8_t>(value.interaction_type);
    stream.writeVarInt<std::int32_t>(value.item_id);
}

auto Serializer<v975::LegacyTelemetryEventPacket::ComposterUsed>::deserialize(BinaryReader &stream) -> std::expected<v975::LegacyTelemetryEventPacket::ComposterUsed, std::error_code>
{
    v975::LegacyTelemetryEventPacket::ComposterUsed out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.interaction_type = static_cast<v924::MinecraftEventing::POIBlockInteractionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.item_id = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<v1001::LegacyTelemetryEventPacket::Achievement>::serialize(BinaryWriter &stream, const v1001::LegacyTelemetryEventPacket::Achievement &value)
{
    stream.write<std::uint8_t>(value.achievement_id);
}

auto Serializer<v1001::LegacyTelemetryEventPacket::Achievement>::deserialize(BinaryReader &stream) -> std::expected<v1001::LegacyTelemetryEventPacket::Achievement, std::error_code>
{
    v1001::LegacyTelemetryEventPacket::Achievement out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.achievement_id = static_cast<v1001::MinecraftEventing::AchievementIds>(*v);
    }
    return out;
}

void Serializer<v1001::LegacyTelemetryEventPacket::Interaction>::serialize(BinaryWriter &stream, const v1001::LegacyTelemetryEventPacket::Interaction &value)
{
    stream.writeVarInt<std::int64_t>(value.interacted_entity_id);
    stream.write<std::uint8_t>(value.interaction_type);
    stream.writeVarInt<std::int32_t>(value.interacted_entity_type);
    stream.writeVarInt<std::int32_t>(value.interacted_entity_variant);
    stream.write<std::uint8_t>(value.interacted_entity_color);
}

auto Serializer<v1001::LegacyTelemetryEventPacket::Interaction>::deserialize(BinaryReader &stream) -> std::expected<v1001::LegacyTelemetryEventPacket::Interaction, std::error_code>
{
    v1001::LegacyTelemetryEventPacket::Interaction out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.interacted_entity_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.interaction_type = static_cast<v1001::MinecraftEventing::InteractionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.interacted_entity_type = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.interacted_entity_variant = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.interacted_entity_color = static_cast<std::uint8_t>(*v);
    }
    return out;
}

void Serializer<v1001::LegacyTelemetryEventPacket::MobKilled>::serialize(BinaryWriter &stream, const v1001::LegacyTelemetryEventPacket::MobKilled &value)
{
    stream.writeVarInt<std::int64_t>(value.killer_entity_id);
    stream.writeVarInt<std::int64_t>(value.killed_mob_id);
    stream.writeVarInt<std::int32_t>(value.damage_child_type);
    stream.writeVarInt<std::int32_t>(value.damage_source);
    stream.writeVarInt<std::int32_t>(value.trader_tier);
    stream.write(value.trader_name);
}

auto Serializer<v1001::LegacyTelemetryEventPacket::MobKilled>::deserialize(BinaryReader &stream) -> std::expected<v1001::LegacyTelemetryEventPacket::MobKilled, std::error_code>
{
    v1001::LegacyTelemetryEventPacket::MobKilled out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.killer_entity_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.killed_mob_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.damage_child_type = static_cast<v975::ActorType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.damage_source = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.trader_tier = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.trader_name = *v;
    }
    return out;
}

void Serializer<v1001::LegacyTelemetryEventPacket::POICauldronUsed>::serialize(BinaryWriter &stream, const v1001::LegacyTelemetryEventPacket::POICauldronUsed &value)
{
    stream.write<std::uint8_t>(value.interaction_type);
    stream.writeVarInt<std::int32_t>(value.item_id);
}

auto Serializer<v1001::LegacyTelemetryEventPacket::POICauldronUsed>::deserialize(BinaryReader &stream) -> std::expected<v1001::LegacyTelemetryEventPacket::POICauldronUsed, std::error_code>
{
    v1001::LegacyTelemetryEventPacket::POICauldronUsed out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.interaction_type = static_cast<v1001::MinecraftEventing::POIBlockInteractionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.item_id = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<v1001::LegacyTelemetryEventPacket::ComposterUsed>::serialize(BinaryWriter &stream, const v1001::LegacyTelemetryEventPacket::ComposterUsed &value)
{
    stream.write<std::uint8_t>(value.interaction_type);
    stream.writeVarInt<std::int32_t>(value.item_id);
}

auto Serializer<v1001::LegacyTelemetryEventPacket::ComposterUsed>::deserialize(BinaryReader &stream) -> std::expected<v1001::LegacyTelemetryEventPacket::ComposterUsed, std::error_code>
{
    v1001::LegacyTelemetryEventPacket::ComposterUsed out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.interaction_type = static_cast<v1001::MinecraftEventing::POIBlockInteractionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.item_id = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<v2168::LegacyTelemetryEventPacket::Achievement>::serialize(BinaryWriter &stream, const v2168::LegacyTelemetryEventPacket::Achievement &value)
{
    stream.write<std::uint8_t>(value.achievement_id);
}

auto Serializer<v2168::LegacyTelemetryEventPacket::Achievement>::deserialize(BinaryReader &stream) -> std::expected<v2168::LegacyTelemetryEventPacket::Achievement, std::error_code>
{
    v2168::LegacyTelemetryEventPacket::Achievement out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.achievement_id = static_cast<v2168::MinecraftEventing::AchievementIds>(*v);
    }
    return out;
}

void Serializer<v2168::LegacyTelemetryEventPacket::Interaction>::serialize(BinaryWriter &stream, const v2168::LegacyTelemetryEventPacket::Interaction &value)
{
    stream.writeVarInt<std::int64_t>(value.interacted_entity_id);
    stream.write<std::uint8_t>(value.interaction_type);
    stream.writeVarInt<std::int32_t>(value.interacted_entity_type);
    stream.writeVarInt<std::int32_t>(value.interacted_entity_variant);
    stream.write<std::uint8_t>(value.interacted_entity_color);
}

auto Serializer<v2168::LegacyTelemetryEventPacket::Interaction>::deserialize(BinaryReader &stream) -> std::expected<v2168::LegacyTelemetryEventPacket::Interaction, std::error_code>
{
    v2168::LegacyTelemetryEventPacket::Interaction out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.interacted_entity_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.interaction_type = static_cast<v2168::MinecraftEventing::InteractionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.interacted_entity_type = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.interacted_entity_variant = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.interacted_entity_color = static_cast<std::uint8_t>(*v);
    }
    return out;
}

void Serializer<v2168::LegacyTelemetryEventPacket::MobKilled>::serialize(BinaryWriter &stream, const v2168::LegacyTelemetryEventPacket::MobKilled &value)
{
    stream.writeVarInt<std::int64_t>(value.killer_entity_id);
    stream.writeVarInt<std::int64_t>(value.killed_mob_id);
    stream.writeVarInt<std::int32_t>(value.damage_child_type);
    stream.writeVarInt<std::int32_t>(value.damage_source);
    stream.writeVarInt<std::int32_t>(value.trader_tier);
    stream.write(value.trader_name);
}

auto Serializer<v2168::LegacyTelemetryEventPacket::MobKilled>::deserialize(BinaryReader &stream) -> std::expected<v2168::LegacyTelemetryEventPacket::MobKilled, std::error_code>
{
    v2168::LegacyTelemetryEventPacket::MobKilled out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.killer_entity_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.killed_mob_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.damage_child_type = static_cast<v2168::ActorType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.damage_source = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.trader_tier = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.trader_name = *v;
    }
    return out;
}

void Serializer<v2168::LegacyTelemetryEventPacket::POICauldronUsed>::serialize(BinaryWriter &stream, const v2168::LegacyTelemetryEventPacket::POICauldronUsed &value)
{
    stream.write<std::uint8_t>(value.interaction_type);
    stream.writeVarInt<std::int32_t>(value.item_id);
}

auto Serializer<v2168::LegacyTelemetryEventPacket::POICauldronUsed>::deserialize(BinaryReader &stream) -> std::expected<v2168::LegacyTelemetryEventPacket::POICauldronUsed, std::error_code>
{
    v2168::LegacyTelemetryEventPacket::POICauldronUsed out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.interaction_type = static_cast<v2168::MinecraftEventing::POIBlockInteractionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.item_id = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<v2168::LegacyTelemetryEventPacket::ComposterUsed>::serialize(BinaryWriter &stream, const v2168::LegacyTelemetryEventPacket::ComposterUsed &value)
{
    stream.write<std::uint8_t>(value.interaction_type);
    stream.writeVarInt<std::int32_t>(value.item_id);
}

auto Serializer<v2168::LegacyTelemetryEventPacket::ComposterUsed>::deserialize(BinaryReader &stream) -> std::expected<v2168::LegacyTelemetryEventPacket::ComposterUsed, std::error_code>
{
    v2168::LegacyTelemetryEventPacket::ComposterUsed out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.interaction_type = static_cast<v2168::MinecraftEventing::POIBlockInteractionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.item_id = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<v2225::LegacyTelemetryEventPacket::Achievement>::serialize(BinaryWriter &stream, const v2225::LegacyTelemetryEventPacket::Achievement &value)
{
    stream.write<std::uint8_t>(value.achievement_id);
}

auto Serializer<v2225::LegacyTelemetryEventPacket::Achievement>::deserialize(BinaryReader &stream) -> std::expected<v2225::LegacyTelemetryEventPacket::Achievement, std::error_code>
{
    v2225::LegacyTelemetryEventPacket::Achievement out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.achievement_id = static_cast<v2225::MinecraftEventing::AchievementIds>(*v);
    }
    return out;
}

void Serializer<v2225::LegacyTelemetryEventPacket::Interaction>::serialize(BinaryWriter &stream, const v2225::LegacyTelemetryEventPacket::Interaction &value)
{
    stream.writeVarInt<std::int64_t>(value.interacted_entity_id);
    stream.write<std::uint8_t>(value.interaction_type);
    stream.writeVarInt<std::int32_t>(value.interacted_entity_type);
    stream.writeVarInt<std::int32_t>(value.interacted_entity_variant);
    stream.write<std::uint8_t>(value.interacted_entity_color);
}

auto Serializer<v2225::LegacyTelemetryEventPacket::Interaction>::deserialize(BinaryReader &stream) -> std::expected<v2225::LegacyTelemetryEventPacket::Interaction, std::error_code>
{
    v2225::LegacyTelemetryEventPacket::Interaction out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.interacted_entity_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.interaction_type = static_cast<v2225::MinecraftEventing::InteractionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.interacted_entity_type = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.interacted_entity_variant = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.interacted_entity_color = static_cast<std::uint8_t>(*v);
    }
    return out;
}

void Serializer<v2225::LegacyTelemetryEventPacket::MobKilled>::serialize(BinaryWriter &stream, const v2225::LegacyTelemetryEventPacket::MobKilled &value)
{
    stream.writeVarInt<std::int64_t>(value.killer_entity_id);
    stream.writeVarInt<std::int64_t>(value.killed_mob_id);
    stream.writeVarInt<std::int32_t>(value.damage_child_type);
    stream.writeVarInt<std::int32_t>(value.damage_source);
    stream.writeVarInt<std::int32_t>(value.trader_tier);
    stream.write(value.trader_name);
}

auto Serializer<v2225::LegacyTelemetryEventPacket::MobKilled>::deserialize(BinaryReader &stream) -> std::expected<v2225::LegacyTelemetryEventPacket::MobKilled, std::error_code>
{
    v2225::LegacyTelemetryEventPacket::MobKilled out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.killer_entity_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.killed_mob_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.damage_child_type = static_cast<v2225::ActorType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.damage_source = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.trader_tier = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.trader_name = *v;
    }
    return out;
}

void Serializer<v2225::LegacyTelemetryEventPacket::POICauldronUsed>::serialize(BinaryWriter &stream, const v2225::LegacyTelemetryEventPacket::POICauldronUsed &value)
{
    stream.write<std::uint8_t>(value.interaction_type);
    stream.writeVarInt<std::int32_t>(value.item_id);
}

auto Serializer<v2225::LegacyTelemetryEventPacket::POICauldronUsed>::deserialize(BinaryReader &stream) -> std::expected<v2225::LegacyTelemetryEventPacket::POICauldronUsed, std::error_code>
{
    v2225::LegacyTelemetryEventPacket::POICauldronUsed out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.interaction_type = static_cast<v2225::MinecraftEventing::POIBlockInteractionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.item_id = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<v2225::LegacyTelemetryEventPacket::ComposterUsed>::serialize(BinaryWriter &stream, const v2225::LegacyTelemetryEventPacket::ComposterUsed &value)
{
    stream.write<std::uint8_t>(value.interaction_type);
    stream.writeVarInt<std::int32_t>(value.item_id);
}

auto Serializer<v2225::LegacyTelemetryEventPacket::ComposterUsed>::deserialize(BinaryReader &stream) -> std::expected<v2225::LegacyTelemetryEventPacket::ComposterUsed, std::error_code>
{
    v2225::LegacyTelemetryEventPacket::ComposterUsed out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.interaction_type = static_cast<v2225::MinecraftEventing::POIBlockInteractionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.item_id = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<base::LegacyTelemetryEventPacket>::serialize(BinaryWriter &stream, const base::LegacyTelemetryEventPacket &value)
{
    stream.writeVarInt<std::int64_t>(value.player_unique_id);
    stream.writeVarInt<std::int32_t>(value.type);
    stream.write<bool>(value.use_player_id);
    stream.writeVarInt<std::uint32_t>((value.event_data).index());
    switch ((value.event_data).index()) {
        case 0: {
            Serializer<base::LegacyTelemetryEventPacket::Achievement>::serialize(stream, std::get<0>(value.event_data));
            break;
        }
        case 1: {
            Serializer<base::LegacyTelemetryEventPacket::Interaction>::serialize(stream, std::get<1>(value.event_data));
            break;
        }
        case 2: {
            Serializer<base::LegacyTelemetryEventPacket::PortalCreated>::serialize(stream, std::get<2>(value.event_data));
            break;
        }
        case 3: {
            Serializer<base::LegacyTelemetryEventPacket::PortalUsed>::serialize(stream, std::get<3>(value.event_data));
            break;
        }
        case 4: {
            Serializer<base::LegacyTelemetryEventPacket::MobKilled>::serialize(stream, std::get<4>(value.event_data));
            break;
        }
        case 5: {
            Serializer<base::LegacyTelemetryEventPacket::CauldronUsed>::serialize(stream, std::get<5>(value.event_data));
            break;
        }
        case 6: {
            Serializer<base::LegacyTelemetryEventPacket::PlayerDied>::serialize(stream, std::get<6>(value.event_data));
            break;
        }
        case 7: {
            Serializer<base::LegacyTelemetryEventPacket::BossKilled>::serialize(stream, std::get<7>(value.event_data));
            break;
        }
        case 8: {
            Serializer<base::LegacyTelemetryEventPacket::SlashCommand>::serialize(stream, std::get<8>(value.event_data));
            break;
        }
        case 9: {
            Serializer<base::LegacyTelemetryEventPacket::MobBorn>::serialize(stream, std::get<9>(value.event_data));
            break;
        }
        case 10: {
            Serializer<base::LegacyTelemetryEventPacket::POICauldronUsed>::serialize(stream, std::get<10>(value.event_data));
            break;
        }
        case 11: {
            Serializer<base::LegacyTelemetryEventPacket::ComposterUsed>::serialize(stream, std::get<11>(value.event_data));
            break;
        }
        case 12: {
            Serializer<base::LegacyTelemetryEventPacket::BellUsed>::serialize(stream, std::get<12>(value.event_data));
            break;
        }
        case 13: {
            Serializer<base::LegacyTelemetryEventPacket::ActorDefinition>::serialize(stream, std::get<13>(value.event_data));
            break;
        }
        case 14: {
            Serializer<base::LegacyTelemetryEventPacket::RaidUpdate>::serialize(stream, std::get<14>(value.event_data));
            break;
        }
        case 15: {
            Serializer<base::LegacyTelemetryEventPacket::TargetBlockHit>::serialize(stream, std::get<15>(value.event_data));
            break;
        }
        case 16: {
            Serializer<base::LegacyTelemetryEventPacket::PiglinBarter>::serialize(stream, std::get<16>(value.event_data));
            break;
        }
        case 17: {
            Serializer<base::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper>::serialize(stream, std::get<17>(value.event_data));
            break;
        }
        case 18: {
            Serializer<base::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction>::serialize(stream, std::get<18>(value.event_data));
            break;
        }
        case 19: {
            Serializer<base::LegacyTelemetryEventPacket::CodeBuilderScoreboard>::serialize(stream, std::get<19>(value.event_data));
            break;
        }
        case 20: {
            Serializer<base::LegacyTelemetryEventPacket::ItemUsed>::serialize(stream, std::get<20>(value.event_data));
            break;
        }
        case 21: {
            Serializer<base::LegacyTelemetryEventPacket::Empty>::serialize(stream, std::get<21>(value.event_data));
            break;
        }
    }
}

auto Serializer<base::LegacyTelemetryEventPacket>::deserialize(BinaryReader &stream) -> std::expected<base::LegacyTelemetryEventPacket, std::error_code>
{
    base::LegacyTelemetryEventPacket out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.player_unique_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<base::LegacyTelemetryEventPacket::Type>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.use_player_id = static_cast<bool>(*v);
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<base::LegacyTelemetryEventPacket::Achievement, base::LegacyTelemetryEventPacket::Interaction, base::LegacyTelemetryEventPacket::PortalCreated, base::LegacyTelemetryEventPacket::PortalUsed, base::LegacyTelemetryEventPacket::MobKilled, base::LegacyTelemetryEventPacket::CauldronUsed, base::LegacyTelemetryEventPacket::PlayerDied, base::LegacyTelemetryEventPacket::BossKilled, base::LegacyTelemetryEventPacket::SlashCommand, base::LegacyTelemetryEventPacket::MobBorn, base::LegacyTelemetryEventPacket::POICauldronUsed, base::LegacyTelemetryEventPacket::ComposterUsed, base::LegacyTelemetryEventPacket::BellUsed, base::LegacyTelemetryEventPacket::ActorDefinition, base::LegacyTelemetryEventPacket::RaidUpdate, base::LegacyTelemetryEventPacket::TargetBlockHit, base::LegacyTelemetryEventPacket::PiglinBarter, base::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, base::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, base::LegacyTelemetryEventPacket::CodeBuilderScoreboard, base::LegacyTelemetryEventPacket::ItemUsed, base::LegacyTelemetryEventPacket::Empty> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<base::LegacyTelemetryEventPacket::Achievement, base::LegacyTelemetryEventPacket::Interaction, base::LegacyTelemetryEventPacket::PortalCreated, base::LegacyTelemetryEventPacket::PortalUsed, base::LegacyTelemetryEventPacket::MobKilled, base::LegacyTelemetryEventPacket::CauldronUsed, base::LegacyTelemetryEventPacket::PlayerDied, base::LegacyTelemetryEventPacket::BossKilled, base::LegacyTelemetryEventPacket::SlashCommand, base::LegacyTelemetryEventPacket::MobBorn, base::LegacyTelemetryEventPacket::POICauldronUsed, base::LegacyTelemetryEventPacket::ComposterUsed, base::LegacyTelemetryEventPacket::BellUsed, base::LegacyTelemetryEventPacket::ActorDefinition, base::LegacyTelemetryEventPacket::RaidUpdate, base::LegacyTelemetryEventPacket::TargetBlockHit, base::LegacyTelemetryEventPacket::PiglinBarter, base::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, base::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, base::LegacyTelemetryEventPacket::CodeBuilderScoreboard, base::LegacyTelemetryEventPacket::ItemUsed, base::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<base::LegacyTelemetryEventPacket::Achievement>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<base::LegacyTelemetryEventPacket::Achievement, base::LegacyTelemetryEventPacket::Interaction, base::LegacyTelemetryEventPacket::PortalCreated, base::LegacyTelemetryEventPacket::PortalUsed, base::LegacyTelemetryEventPacket::MobKilled, base::LegacyTelemetryEventPacket::CauldronUsed, base::LegacyTelemetryEventPacket::PlayerDied, base::LegacyTelemetryEventPacket::BossKilled, base::LegacyTelemetryEventPacket::SlashCommand, base::LegacyTelemetryEventPacket::MobBorn, base::LegacyTelemetryEventPacket::POICauldronUsed, base::LegacyTelemetryEventPacket::ComposterUsed, base::LegacyTelemetryEventPacket::BellUsed, base::LegacyTelemetryEventPacket::ActorDefinition, base::LegacyTelemetryEventPacket::RaidUpdate, base::LegacyTelemetryEventPacket::TargetBlockHit, base::LegacyTelemetryEventPacket::PiglinBarter, base::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, base::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, base::LegacyTelemetryEventPacket::CodeBuilderScoreboard, base::LegacyTelemetryEventPacket::ItemUsed, base::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<base::LegacyTelemetryEventPacket::Interaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<base::LegacyTelemetryEventPacket::Achievement, base::LegacyTelemetryEventPacket::Interaction, base::LegacyTelemetryEventPacket::PortalCreated, base::LegacyTelemetryEventPacket::PortalUsed, base::LegacyTelemetryEventPacket::MobKilled, base::LegacyTelemetryEventPacket::CauldronUsed, base::LegacyTelemetryEventPacket::PlayerDied, base::LegacyTelemetryEventPacket::BossKilled, base::LegacyTelemetryEventPacket::SlashCommand, base::LegacyTelemetryEventPacket::MobBorn, base::LegacyTelemetryEventPacket::POICauldronUsed, base::LegacyTelemetryEventPacket::ComposterUsed, base::LegacyTelemetryEventPacket::BellUsed, base::LegacyTelemetryEventPacket::ActorDefinition, base::LegacyTelemetryEventPacket::RaidUpdate, base::LegacyTelemetryEventPacket::TargetBlockHit, base::LegacyTelemetryEventPacket::PiglinBarter, base::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, base::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, base::LegacyTelemetryEventPacket::CodeBuilderScoreboard, base::LegacyTelemetryEventPacket::ItemUsed, base::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<base::LegacyTelemetryEventPacket::PortalCreated>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<base::LegacyTelemetryEventPacket::Achievement, base::LegacyTelemetryEventPacket::Interaction, base::LegacyTelemetryEventPacket::PortalCreated, base::LegacyTelemetryEventPacket::PortalUsed, base::LegacyTelemetryEventPacket::MobKilled, base::LegacyTelemetryEventPacket::CauldronUsed, base::LegacyTelemetryEventPacket::PlayerDied, base::LegacyTelemetryEventPacket::BossKilled, base::LegacyTelemetryEventPacket::SlashCommand, base::LegacyTelemetryEventPacket::MobBorn, base::LegacyTelemetryEventPacket::POICauldronUsed, base::LegacyTelemetryEventPacket::ComposterUsed, base::LegacyTelemetryEventPacket::BellUsed, base::LegacyTelemetryEventPacket::ActorDefinition, base::LegacyTelemetryEventPacket::RaidUpdate, base::LegacyTelemetryEventPacket::TargetBlockHit, base::LegacyTelemetryEventPacket::PiglinBarter, base::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, base::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, base::LegacyTelemetryEventPacket::CodeBuilderScoreboard, base::LegacyTelemetryEventPacket::ItemUsed, base::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<base::LegacyTelemetryEventPacket::PortalUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            case 4: {
                std::variant_alternative_t<4, std::variant<base::LegacyTelemetryEventPacket::Achievement, base::LegacyTelemetryEventPacket::Interaction, base::LegacyTelemetryEventPacket::PortalCreated, base::LegacyTelemetryEventPacket::PortalUsed, base::LegacyTelemetryEventPacket::MobKilled, base::LegacyTelemetryEventPacket::CauldronUsed, base::LegacyTelemetryEventPacket::PlayerDied, base::LegacyTelemetryEventPacket::BossKilled, base::LegacyTelemetryEventPacket::SlashCommand, base::LegacyTelemetryEventPacket::MobBorn, base::LegacyTelemetryEventPacket::POICauldronUsed, base::LegacyTelemetryEventPacket::ComposterUsed, base::LegacyTelemetryEventPacket::BellUsed, base::LegacyTelemetryEventPacket::ActorDefinition, base::LegacyTelemetryEventPacket::RaidUpdate, base::LegacyTelemetryEventPacket::TargetBlockHit, base::LegacyTelemetryEventPacket::PiglinBarter, base::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, base::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, base::LegacyTelemetryEventPacket::CodeBuilderScoreboard, base::LegacyTelemetryEventPacket::ItemUsed, base::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<base::LegacyTelemetryEventPacket::MobKilled>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<4>(alt0);
                break;
            }
            case 5: {
                std::variant_alternative_t<5, std::variant<base::LegacyTelemetryEventPacket::Achievement, base::LegacyTelemetryEventPacket::Interaction, base::LegacyTelemetryEventPacket::PortalCreated, base::LegacyTelemetryEventPacket::PortalUsed, base::LegacyTelemetryEventPacket::MobKilled, base::LegacyTelemetryEventPacket::CauldronUsed, base::LegacyTelemetryEventPacket::PlayerDied, base::LegacyTelemetryEventPacket::BossKilled, base::LegacyTelemetryEventPacket::SlashCommand, base::LegacyTelemetryEventPacket::MobBorn, base::LegacyTelemetryEventPacket::POICauldronUsed, base::LegacyTelemetryEventPacket::ComposterUsed, base::LegacyTelemetryEventPacket::BellUsed, base::LegacyTelemetryEventPacket::ActorDefinition, base::LegacyTelemetryEventPacket::RaidUpdate, base::LegacyTelemetryEventPacket::TargetBlockHit, base::LegacyTelemetryEventPacket::PiglinBarter, base::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, base::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, base::LegacyTelemetryEventPacket::CodeBuilderScoreboard, base::LegacyTelemetryEventPacket::ItemUsed, base::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<base::LegacyTelemetryEventPacket::CauldronUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<5>(alt0);
                break;
            }
            case 6: {
                std::variant_alternative_t<6, std::variant<base::LegacyTelemetryEventPacket::Achievement, base::LegacyTelemetryEventPacket::Interaction, base::LegacyTelemetryEventPacket::PortalCreated, base::LegacyTelemetryEventPacket::PortalUsed, base::LegacyTelemetryEventPacket::MobKilled, base::LegacyTelemetryEventPacket::CauldronUsed, base::LegacyTelemetryEventPacket::PlayerDied, base::LegacyTelemetryEventPacket::BossKilled, base::LegacyTelemetryEventPacket::SlashCommand, base::LegacyTelemetryEventPacket::MobBorn, base::LegacyTelemetryEventPacket::POICauldronUsed, base::LegacyTelemetryEventPacket::ComposterUsed, base::LegacyTelemetryEventPacket::BellUsed, base::LegacyTelemetryEventPacket::ActorDefinition, base::LegacyTelemetryEventPacket::RaidUpdate, base::LegacyTelemetryEventPacket::TargetBlockHit, base::LegacyTelemetryEventPacket::PiglinBarter, base::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, base::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, base::LegacyTelemetryEventPacket::CodeBuilderScoreboard, base::LegacyTelemetryEventPacket::ItemUsed, base::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<base::LegacyTelemetryEventPacket::PlayerDied>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<6>(alt0);
                break;
            }
            case 7: {
                std::variant_alternative_t<7, std::variant<base::LegacyTelemetryEventPacket::Achievement, base::LegacyTelemetryEventPacket::Interaction, base::LegacyTelemetryEventPacket::PortalCreated, base::LegacyTelemetryEventPacket::PortalUsed, base::LegacyTelemetryEventPacket::MobKilled, base::LegacyTelemetryEventPacket::CauldronUsed, base::LegacyTelemetryEventPacket::PlayerDied, base::LegacyTelemetryEventPacket::BossKilled, base::LegacyTelemetryEventPacket::SlashCommand, base::LegacyTelemetryEventPacket::MobBorn, base::LegacyTelemetryEventPacket::POICauldronUsed, base::LegacyTelemetryEventPacket::ComposterUsed, base::LegacyTelemetryEventPacket::BellUsed, base::LegacyTelemetryEventPacket::ActorDefinition, base::LegacyTelemetryEventPacket::RaidUpdate, base::LegacyTelemetryEventPacket::TargetBlockHit, base::LegacyTelemetryEventPacket::PiglinBarter, base::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, base::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, base::LegacyTelemetryEventPacket::CodeBuilderScoreboard, base::LegacyTelemetryEventPacket::ItemUsed, base::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<base::LegacyTelemetryEventPacket::BossKilled>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<7>(alt0);
                break;
            }
            case 8: {
                std::variant_alternative_t<8, std::variant<base::LegacyTelemetryEventPacket::Achievement, base::LegacyTelemetryEventPacket::Interaction, base::LegacyTelemetryEventPacket::PortalCreated, base::LegacyTelemetryEventPacket::PortalUsed, base::LegacyTelemetryEventPacket::MobKilled, base::LegacyTelemetryEventPacket::CauldronUsed, base::LegacyTelemetryEventPacket::PlayerDied, base::LegacyTelemetryEventPacket::BossKilled, base::LegacyTelemetryEventPacket::SlashCommand, base::LegacyTelemetryEventPacket::MobBorn, base::LegacyTelemetryEventPacket::POICauldronUsed, base::LegacyTelemetryEventPacket::ComposterUsed, base::LegacyTelemetryEventPacket::BellUsed, base::LegacyTelemetryEventPacket::ActorDefinition, base::LegacyTelemetryEventPacket::RaidUpdate, base::LegacyTelemetryEventPacket::TargetBlockHit, base::LegacyTelemetryEventPacket::PiglinBarter, base::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, base::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, base::LegacyTelemetryEventPacket::CodeBuilderScoreboard, base::LegacyTelemetryEventPacket::ItemUsed, base::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<base::LegacyTelemetryEventPacket::SlashCommand>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<8>(alt0);
                break;
            }
            case 9: {
                std::variant_alternative_t<9, std::variant<base::LegacyTelemetryEventPacket::Achievement, base::LegacyTelemetryEventPacket::Interaction, base::LegacyTelemetryEventPacket::PortalCreated, base::LegacyTelemetryEventPacket::PortalUsed, base::LegacyTelemetryEventPacket::MobKilled, base::LegacyTelemetryEventPacket::CauldronUsed, base::LegacyTelemetryEventPacket::PlayerDied, base::LegacyTelemetryEventPacket::BossKilled, base::LegacyTelemetryEventPacket::SlashCommand, base::LegacyTelemetryEventPacket::MobBorn, base::LegacyTelemetryEventPacket::POICauldronUsed, base::LegacyTelemetryEventPacket::ComposterUsed, base::LegacyTelemetryEventPacket::BellUsed, base::LegacyTelemetryEventPacket::ActorDefinition, base::LegacyTelemetryEventPacket::RaidUpdate, base::LegacyTelemetryEventPacket::TargetBlockHit, base::LegacyTelemetryEventPacket::PiglinBarter, base::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, base::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, base::LegacyTelemetryEventPacket::CodeBuilderScoreboard, base::LegacyTelemetryEventPacket::ItemUsed, base::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<base::LegacyTelemetryEventPacket::MobBorn>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<9>(alt0);
                break;
            }
            case 10: {
                std::variant_alternative_t<10, std::variant<base::LegacyTelemetryEventPacket::Achievement, base::LegacyTelemetryEventPacket::Interaction, base::LegacyTelemetryEventPacket::PortalCreated, base::LegacyTelemetryEventPacket::PortalUsed, base::LegacyTelemetryEventPacket::MobKilled, base::LegacyTelemetryEventPacket::CauldronUsed, base::LegacyTelemetryEventPacket::PlayerDied, base::LegacyTelemetryEventPacket::BossKilled, base::LegacyTelemetryEventPacket::SlashCommand, base::LegacyTelemetryEventPacket::MobBorn, base::LegacyTelemetryEventPacket::POICauldronUsed, base::LegacyTelemetryEventPacket::ComposterUsed, base::LegacyTelemetryEventPacket::BellUsed, base::LegacyTelemetryEventPacket::ActorDefinition, base::LegacyTelemetryEventPacket::RaidUpdate, base::LegacyTelemetryEventPacket::TargetBlockHit, base::LegacyTelemetryEventPacket::PiglinBarter, base::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, base::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, base::LegacyTelemetryEventPacket::CodeBuilderScoreboard, base::LegacyTelemetryEventPacket::ItemUsed, base::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<base::LegacyTelemetryEventPacket::POICauldronUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<10>(alt0);
                break;
            }
            case 11: {
                std::variant_alternative_t<11, std::variant<base::LegacyTelemetryEventPacket::Achievement, base::LegacyTelemetryEventPacket::Interaction, base::LegacyTelemetryEventPacket::PortalCreated, base::LegacyTelemetryEventPacket::PortalUsed, base::LegacyTelemetryEventPacket::MobKilled, base::LegacyTelemetryEventPacket::CauldronUsed, base::LegacyTelemetryEventPacket::PlayerDied, base::LegacyTelemetryEventPacket::BossKilled, base::LegacyTelemetryEventPacket::SlashCommand, base::LegacyTelemetryEventPacket::MobBorn, base::LegacyTelemetryEventPacket::POICauldronUsed, base::LegacyTelemetryEventPacket::ComposterUsed, base::LegacyTelemetryEventPacket::BellUsed, base::LegacyTelemetryEventPacket::ActorDefinition, base::LegacyTelemetryEventPacket::RaidUpdate, base::LegacyTelemetryEventPacket::TargetBlockHit, base::LegacyTelemetryEventPacket::PiglinBarter, base::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, base::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, base::LegacyTelemetryEventPacket::CodeBuilderScoreboard, base::LegacyTelemetryEventPacket::ItemUsed, base::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<base::LegacyTelemetryEventPacket::ComposterUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<11>(alt0);
                break;
            }
            case 12: {
                std::variant_alternative_t<12, std::variant<base::LegacyTelemetryEventPacket::Achievement, base::LegacyTelemetryEventPacket::Interaction, base::LegacyTelemetryEventPacket::PortalCreated, base::LegacyTelemetryEventPacket::PortalUsed, base::LegacyTelemetryEventPacket::MobKilled, base::LegacyTelemetryEventPacket::CauldronUsed, base::LegacyTelemetryEventPacket::PlayerDied, base::LegacyTelemetryEventPacket::BossKilled, base::LegacyTelemetryEventPacket::SlashCommand, base::LegacyTelemetryEventPacket::MobBorn, base::LegacyTelemetryEventPacket::POICauldronUsed, base::LegacyTelemetryEventPacket::ComposterUsed, base::LegacyTelemetryEventPacket::BellUsed, base::LegacyTelemetryEventPacket::ActorDefinition, base::LegacyTelemetryEventPacket::RaidUpdate, base::LegacyTelemetryEventPacket::TargetBlockHit, base::LegacyTelemetryEventPacket::PiglinBarter, base::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, base::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, base::LegacyTelemetryEventPacket::CodeBuilderScoreboard, base::LegacyTelemetryEventPacket::ItemUsed, base::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<base::LegacyTelemetryEventPacket::BellUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<12>(alt0);
                break;
            }
            case 13: {
                std::variant_alternative_t<13, std::variant<base::LegacyTelemetryEventPacket::Achievement, base::LegacyTelemetryEventPacket::Interaction, base::LegacyTelemetryEventPacket::PortalCreated, base::LegacyTelemetryEventPacket::PortalUsed, base::LegacyTelemetryEventPacket::MobKilled, base::LegacyTelemetryEventPacket::CauldronUsed, base::LegacyTelemetryEventPacket::PlayerDied, base::LegacyTelemetryEventPacket::BossKilled, base::LegacyTelemetryEventPacket::SlashCommand, base::LegacyTelemetryEventPacket::MobBorn, base::LegacyTelemetryEventPacket::POICauldronUsed, base::LegacyTelemetryEventPacket::ComposterUsed, base::LegacyTelemetryEventPacket::BellUsed, base::LegacyTelemetryEventPacket::ActorDefinition, base::LegacyTelemetryEventPacket::RaidUpdate, base::LegacyTelemetryEventPacket::TargetBlockHit, base::LegacyTelemetryEventPacket::PiglinBarter, base::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, base::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, base::LegacyTelemetryEventPacket::CodeBuilderScoreboard, base::LegacyTelemetryEventPacket::ItemUsed, base::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<base::LegacyTelemetryEventPacket::ActorDefinition>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<13>(alt0);
                break;
            }
            case 14: {
                std::variant_alternative_t<14, std::variant<base::LegacyTelemetryEventPacket::Achievement, base::LegacyTelemetryEventPacket::Interaction, base::LegacyTelemetryEventPacket::PortalCreated, base::LegacyTelemetryEventPacket::PortalUsed, base::LegacyTelemetryEventPacket::MobKilled, base::LegacyTelemetryEventPacket::CauldronUsed, base::LegacyTelemetryEventPacket::PlayerDied, base::LegacyTelemetryEventPacket::BossKilled, base::LegacyTelemetryEventPacket::SlashCommand, base::LegacyTelemetryEventPacket::MobBorn, base::LegacyTelemetryEventPacket::POICauldronUsed, base::LegacyTelemetryEventPacket::ComposterUsed, base::LegacyTelemetryEventPacket::BellUsed, base::LegacyTelemetryEventPacket::ActorDefinition, base::LegacyTelemetryEventPacket::RaidUpdate, base::LegacyTelemetryEventPacket::TargetBlockHit, base::LegacyTelemetryEventPacket::PiglinBarter, base::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, base::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, base::LegacyTelemetryEventPacket::CodeBuilderScoreboard, base::LegacyTelemetryEventPacket::ItemUsed, base::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<base::LegacyTelemetryEventPacket::RaidUpdate>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<14>(alt0);
                break;
            }
            case 15: {
                std::variant_alternative_t<15, std::variant<base::LegacyTelemetryEventPacket::Achievement, base::LegacyTelemetryEventPacket::Interaction, base::LegacyTelemetryEventPacket::PortalCreated, base::LegacyTelemetryEventPacket::PortalUsed, base::LegacyTelemetryEventPacket::MobKilled, base::LegacyTelemetryEventPacket::CauldronUsed, base::LegacyTelemetryEventPacket::PlayerDied, base::LegacyTelemetryEventPacket::BossKilled, base::LegacyTelemetryEventPacket::SlashCommand, base::LegacyTelemetryEventPacket::MobBorn, base::LegacyTelemetryEventPacket::POICauldronUsed, base::LegacyTelemetryEventPacket::ComposterUsed, base::LegacyTelemetryEventPacket::BellUsed, base::LegacyTelemetryEventPacket::ActorDefinition, base::LegacyTelemetryEventPacket::RaidUpdate, base::LegacyTelemetryEventPacket::TargetBlockHit, base::LegacyTelemetryEventPacket::PiglinBarter, base::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, base::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, base::LegacyTelemetryEventPacket::CodeBuilderScoreboard, base::LegacyTelemetryEventPacket::ItemUsed, base::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<base::LegacyTelemetryEventPacket::TargetBlockHit>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<15>(alt0);
                break;
            }
            case 16: {
                std::variant_alternative_t<16, std::variant<base::LegacyTelemetryEventPacket::Achievement, base::LegacyTelemetryEventPacket::Interaction, base::LegacyTelemetryEventPacket::PortalCreated, base::LegacyTelemetryEventPacket::PortalUsed, base::LegacyTelemetryEventPacket::MobKilled, base::LegacyTelemetryEventPacket::CauldronUsed, base::LegacyTelemetryEventPacket::PlayerDied, base::LegacyTelemetryEventPacket::BossKilled, base::LegacyTelemetryEventPacket::SlashCommand, base::LegacyTelemetryEventPacket::MobBorn, base::LegacyTelemetryEventPacket::POICauldronUsed, base::LegacyTelemetryEventPacket::ComposterUsed, base::LegacyTelemetryEventPacket::BellUsed, base::LegacyTelemetryEventPacket::ActorDefinition, base::LegacyTelemetryEventPacket::RaidUpdate, base::LegacyTelemetryEventPacket::TargetBlockHit, base::LegacyTelemetryEventPacket::PiglinBarter, base::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, base::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, base::LegacyTelemetryEventPacket::CodeBuilderScoreboard, base::LegacyTelemetryEventPacket::ItemUsed, base::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<base::LegacyTelemetryEventPacket::PiglinBarter>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<16>(alt0);
                break;
            }
            case 17: {
                std::variant_alternative_t<17, std::variant<base::LegacyTelemetryEventPacket::Achievement, base::LegacyTelemetryEventPacket::Interaction, base::LegacyTelemetryEventPacket::PortalCreated, base::LegacyTelemetryEventPacket::PortalUsed, base::LegacyTelemetryEventPacket::MobKilled, base::LegacyTelemetryEventPacket::CauldronUsed, base::LegacyTelemetryEventPacket::PlayerDied, base::LegacyTelemetryEventPacket::BossKilled, base::LegacyTelemetryEventPacket::SlashCommand, base::LegacyTelemetryEventPacket::MobBorn, base::LegacyTelemetryEventPacket::POICauldronUsed, base::LegacyTelemetryEventPacket::ComposterUsed, base::LegacyTelemetryEventPacket::BellUsed, base::LegacyTelemetryEventPacket::ActorDefinition, base::LegacyTelemetryEventPacket::RaidUpdate, base::LegacyTelemetryEventPacket::TargetBlockHit, base::LegacyTelemetryEventPacket::PiglinBarter, base::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, base::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, base::LegacyTelemetryEventPacket::CodeBuilderScoreboard, base::LegacyTelemetryEventPacket::ItemUsed, base::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<base::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<17>(alt0);
                break;
            }
            case 18: {
                std::variant_alternative_t<18, std::variant<base::LegacyTelemetryEventPacket::Achievement, base::LegacyTelemetryEventPacket::Interaction, base::LegacyTelemetryEventPacket::PortalCreated, base::LegacyTelemetryEventPacket::PortalUsed, base::LegacyTelemetryEventPacket::MobKilled, base::LegacyTelemetryEventPacket::CauldronUsed, base::LegacyTelemetryEventPacket::PlayerDied, base::LegacyTelemetryEventPacket::BossKilled, base::LegacyTelemetryEventPacket::SlashCommand, base::LegacyTelemetryEventPacket::MobBorn, base::LegacyTelemetryEventPacket::POICauldronUsed, base::LegacyTelemetryEventPacket::ComposterUsed, base::LegacyTelemetryEventPacket::BellUsed, base::LegacyTelemetryEventPacket::ActorDefinition, base::LegacyTelemetryEventPacket::RaidUpdate, base::LegacyTelemetryEventPacket::TargetBlockHit, base::LegacyTelemetryEventPacket::PiglinBarter, base::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, base::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, base::LegacyTelemetryEventPacket::CodeBuilderScoreboard, base::LegacyTelemetryEventPacket::ItemUsed, base::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<base::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<18>(alt0);
                break;
            }
            case 19: {
                std::variant_alternative_t<19, std::variant<base::LegacyTelemetryEventPacket::Achievement, base::LegacyTelemetryEventPacket::Interaction, base::LegacyTelemetryEventPacket::PortalCreated, base::LegacyTelemetryEventPacket::PortalUsed, base::LegacyTelemetryEventPacket::MobKilled, base::LegacyTelemetryEventPacket::CauldronUsed, base::LegacyTelemetryEventPacket::PlayerDied, base::LegacyTelemetryEventPacket::BossKilled, base::LegacyTelemetryEventPacket::SlashCommand, base::LegacyTelemetryEventPacket::MobBorn, base::LegacyTelemetryEventPacket::POICauldronUsed, base::LegacyTelemetryEventPacket::ComposterUsed, base::LegacyTelemetryEventPacket::BellUsed, base::LegacyTelemetryEventPacket::ActorDefinition, base::LegacyTelemetryEventPacket::RaidUpdate, base::LegacyTelemetryEventPacket::TargetBlockHit, base::LegacyTelemetryEventPacket::PiglinBarter, base::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, base::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, base::LegacyTelemetryEventPacket::CodeBuilderScoreboard, base::LegacyTelemetryEventPacket::ItemUsed, base::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<base::LegacyTelemetryEventPacket::CodeBuilderScoreboard>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<19>(alt0);
                break;
            }
            case 20: {
                std::variant_alternative_t<20, std::variant<base::LegacyTelemetryEventPacket::Achievement, base::LegacyTelemetryEventPacket::Interaction, base::LegacyTelemetryEventPacket::PortalCreated, base::LegacyTelemetryEventPacket::PortalUsed, base::LegacyTelemetryEventPacket::MobKilled, base::LegacyTelemetryEventPacket::CauldronUsed, base::LegacyTelemetryEventPacket::PlayerDied, base::LegacyTelemetryEventPacket::BossKilled, base::LegacyTelemetryEventPacket::SlashCommand, base::LegacyTelemetryEventPacket::MobBorn, base::LegacyTelemetryEventPacket::POICauldronUsed, base::LegacyTelemetryEventPacket::ComposterUsed, base::LegacyTelemetryEventPacket::BellUsed, base::LegacyTelemetryEventPacket::ActorDefinition, base::LegacyTelemetryEventPacket::RaidUpdate, base::LegacyTelemetryEventPacket::TargetBlockHit, base::LegacyTelemetryEventPacket::PiglinBarter, base::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, base::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, base::LegacyTelemetryEventPacket::CodeBuilderScoreboard, base::LegacyTelemetryEventPacket::ItemUsed, base::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<base::LegacyTelemetryEventPacket::ItemUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<20>(alt0);
                break;
            }
            case 21: {
                std::variant_alternative_t<21, std::variant<base::LegacyTelemetryEventPacket::Achievement, base::LegacyTelemetryEventPacket::Interaction, base::LegacyTelemetryEventPacket::PortalCreated, base::LegacyTelemetryEventPacket::PortalUsed, base::LegacyTelemetryEventPacket::MobKilled, base::LegacyTelemetryEventPacket::CauldronUsed, base::LegacyTelemetryEventPacket::PlayerDied, base::LegacyTelemetryEventPacket::BossKilled, base::LegacyTelemetryEventPacket::SlashCommand, base::LegacyTelemetryEventPacket::MobBorn, base::LegacyTelemetryEventPacket::POICauldronUsed, base::LegacyTelemetryEventPacket::ComposterUsed, base::LegacyTelemetryEventPacket::BellUsed, base::LegacyTelemetryEventPacket::ActorDefinition, base::LegacyTelemetryEventPacket::RaidUpdate, base::LegacyTelemetryEventPacket::TargetBlockHit, base::LegacyTelemetryEventPacket::PiglinBarter, base::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, base::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, base::LegacyTelemetryEventPacket::CodeBuilderScoreboard, base::LegacyTelemetryEventPacket::ItemUsed, base::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<base::LegacyTelemetryEventPacket::Empty>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<21>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.event_data = var0;
    }
    return out;
}

void Serializer<v766::LegacyTelemetryEventPacket>::serialize(BinaryWriter &stream, const v766::LegacyTelemetryEventPacket &value)
{
    stream.writeVarInt<std::int64_t>(value.player_unique_id);
    stream.writeVarInt<std::int32_t>(value.type);
    stream.write<bool>(value.use_player_id);
    stream.writeVarInt<std::uint32_t>((value.event_data).index());
    switch ((value.event_data).index()) {
        case 0: {
            Serializer<v766::LegacyTelemetryEventPacket::Achievement>::serialize(stream, std::get<0>(value.event_data));
            break;
        }
        case 1: {
            Serializer<v766::LegacyTelemetryEventPacket::Interaction>::serialize(stream, std::get<1>(value.event_data));
            break;
        }
        case 2: {
            Serializer<v766::LegacyTelemetryEventPacket::PortalCreated>::serialize(stream, std::get<2>(value.event_data));
            break;
        }
        case 3: {
            Serializer<v766::LegacyTelemetryEventPacket::PortalUsed>::serialize(stream, std::get<3>(value.event_data));
            break;
        }
        case 4: {
            Serializer<v766::LegacyTelemetryEventPacket::MobKilled>::serialize(stream, std::get<4>(value.event_data));
            break;
        }
        case 5: {
            Serializer<v766::LegacyTelemetryEventPacket::CauldronUsed>::serialize(stream, std::get<5>(value.event_data));
            break;
        }
        case 6: {
            Serializer<v766::LegacyTelemetryEventPacket::PlayerDied>::serialize(stream, std::get<6>(value.event_data));
            break;
        }
        case 7: {
            Serializer<v766::LegacyTelemetryEventPacket::BossKilled>::serialize(stream, std::get<7>(value.event_data));
            break;
        }
        case 8: {
            Serializer<v766::LegacyTelemetryEventPacket::SlashCommand>::serialize(stream, std::get<8>(value.event_data));
            break;
        }
        case 9: {
            Serializer<v766::LegacyTelemetryEventPacket::MobBorn>::serialize(stream, std::get<9>(value.event_data));
            break;
        }
        case 10: {
            Serializer<v766::LegacyTelemetryEventPacket::POICauldronUsed>::serialize(stream, std::get<10>(value.event_data));
            break;
        }
        case 11: {
            Serializer<v766::LegacyTelemetryEventPacket::ComposterUsed>::serialize(stream, std::get<11>(value.event_data));
            break;
        }
        case 12: {
            Serializer<v766::LegacyTelemetryEventPacket::BellUsed>::serialize(stream, std::get<12>(value.event_data));
            break;
        }
        case 13: {
            Serializer<v766::LegacyTelemetryEventPacket::ActorDefinition>::serialize(stream, std::get<13>(value.event_data));
            break;
        }
        case 14: {
            Serializer<v766::LegacyTelemetryEventPacket::RaidUpdate>::serialize(stream, std::get<14>(value.event_data));
            break;
        }
        case 15: {
            Serializer<v766::LegacyTelemetryEventPacket::TargetBlockHit>::serialize(stream, std::get<15>(value.event_data));
            break;
        }
        case 16: {
            Serializer<v766::LegacyTelemetryEventPacket::PiglinBarter>::serialize(stream, std::get<16>(value.event_data));
            break;
        }
        case 17: {
            Serializer<v766::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper>::serialize(stream, std::get<17>(value.event_data));
            break;
        }
        case 18: {
            Serializer<v766::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction>::serialize(stream, std::get<18>(value.event_data));
            break;
        }
        case 19: {
            Serializer<v766::LegacyTelemetryEventPacket::CodeBuilderScoreboard>::serialize(stream, std::get<19>(value.event_data));
            break;
        }
        case 20: {
            Serializer<v766::LegacyTelemetryEventPacket::ItemUsed>::serialize(stream, std::get<20>(value.event_data));
            break;
        }
        case 21: {
            Serializer<v766::LegacyTelemetryEventPacket::Empty>::serialize(stream, std::get<21>(value.event_data));
            break;
        }
    }
}

auto Serializer<v766::LegacyTelemetryEventPacket>::deserialize(BinaryReader &stream) -> std::expected<v766::LegacyTelemetryEventPacket, std::error_code>
{
    v766::LegacyTelemetryEventPacket out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.player_unique_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<v766::LegacyTelemetryEventPacket::Type>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.use_player_id = static_cast<bool>(*v);
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v766::LegacyTelemetryEventPacket::Achievement, v766::LegacyTelemetryEventPacket::Interaction, v766::LegacyTelemetryEventPacket::PortalCreated, v766::LegacyTelemetryEventPacket::PortalUsed, v766::LegacyTelemetryEventPacket::MobKilled, v766::LegacyTelemetryEventPacket::CauldronUsed, v766::LegacyTelemetryEventPacket::PlayerDied, v766::LegacyTelemetryEventPacket::BossKilled, v766::LegacyTelemetryEventPacket::SlashCommand, v766::LegacyTelemetryEventPacket::MobBorn, v766::LegacyTelemetryEventPacket::POICauldronUsed, v766::LegacyTelemetryEventPacket::ComposterUsed, v766::LegacyTelemetryEventPacket::BellUsed, v766::LegacyTelemetryEventPacket::ActorDefinition, v766::LegacyTelemetryEventPacket::RaidUpdate, v766::LegacyTelemetryEventPacket::TargetBlockHit, v766::LegacyTelemetryEventPacket::PiglinBarter, v766::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v766::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v766::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v766::LegacyTelemetryEventPacket::ItemUsed, v766::LegacyTelemetryEventPacket::Empty> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v766::LegacyTelemetryEventPacket::Achievement, v766::LegacyTelemetryEventPacket::Interaction, v766::LegacyTelemetryEventPacket::PortalCreated, v766::LegacyTelemetryEventPacket::PortalUsed, v766::LegacyTelemetryEventPacket::MobKilled, v766::LegacyTelemetryEventPacket::CauldronUsed, v766::LegacyTelemetryEventPacket::PlayerDied, v766::LegacyTelemetryEventPacket::BossKilled, v766::LegacyTelemetryEventPacket::SlashCommand, v766::LegacyTelemetryEventPacket::MobBorn, v766::LegacyTelemetryEventPacket::POICauldronUsed, v766::LegacyTelemetryEventPacket::ComposterUsed, v766::LegacyTelemetryEventPacket::BellUsed, v766::LegacyTelemetryEventPacket::ActorDefinition, v766::LegacyTelemetryEventPacket::RaidUpdate, v766::LegacyTelemetryEventPacket::TargetBlockHit, v766::LegacyTelemetryEventPacket::PiglinBarter, v766::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v766::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v766::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v766::LegacyTelemetryEventPacket::ItemUsed, v766::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v766::LegacyTelemetryEventPacket::Achievement>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v766::LegacyTelemetryEventPacket::Achievement, v766::LegacyTelemetryEventPacket::Interaction, v766::LegacyTelemetryEventPacket::PortalCreated, v766::LegacyTelemetryEventPacket::PortalUsed, v766::LegacyTelemetryEventPacket::MobKilled, v766::LegacyTelemetryEventPacket::CauldronUsed, v766::LegacyTelemetryEventPacket::PlayerDied, v766::LegacyTelemetryEventPacket::BossKilled, v766::LegacyTelemetryEventPacket::SlashCommand, v766::LegacyTelemetryEventPacket::MobBorn, v766::LegacyTelemetryEventPacket::POICauldronUsed, v766::LegacyTelemetryEventPacket::ComposterUsed, v766::LegacyTelemetryEventPacket::BellUsed, v766::LegacyTelemetryEventPacket::ActorDefinition, v766::LegacyTelemetryEventPacket::RaidUpdate, v766::LegacyTelemetryEventPacket::TargetBlockHit, v766::LegacyTelemetryEventPacket::PiglinBarter, v766::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v766::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v766::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v766::LegacyTelemetryEventPacket::ItemUsed, v766::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v766::LegacyTelemetryEventPacket::Interaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<v766::LegacyTelemetryEventPacket::Achievement, v766::LegacyTelemetryEventPacket::Interaction, v766::LegacyTelemetryEventPacket::PortalCreated, v766::LegacyTelemetryEventPacket::PortalUsed, v766::LegacyTelemetryEventPacket::MobKilled, v766::LegacyTelemetryEventPacket::CauldronUsed, v766::LegacyTelemetryEventPacket::PlayerDied, v766::LegacyTelemetryEventPacket::BossKilled, v766::LegacyTelemetryEventPacket::SlashCommand, v766::LegacyTelemetryEventPacket::MobBorn, v766::LegacyTelemetryEventPacket::POICauldronUsed, v766::LegacyTelemetryEventPacket::ComposterUsed, v766::LegacyTelemetryEventPacket::BellUsed, v766::LegacyTelemetryEventPacket::ActorDefinition, v766::LegacyTelemetryEventPacket::RaidUpdate, v766::LegacyTelemetryEventPacket::TargetBlockHit, v766::LegacyTelemetryEventPacket::PiglinBarter, v766::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v766::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v766::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v766::LegacyTelemetryEventPacket::ItemUsed, v766::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v766::LegacyTelemetryEventPacket::PortalCreated>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<v766::LegacyTelemetryEventPacket::Achievement, v766::LegacyTelemetryEventPacket::Interaction, v766::LegacyTelemetryEventPacket::PortalCreated, v766::LegacyTelemetryEventPacket::PortalUsed, v766::LegacyTelemetryEventPacket::MobKilled, v766::LegacyTelemetryEventPacket::CauldronUsed, v766::LegacyTelemetryEventPacket::PlayerDied, v766::LegacyTelemetryEventPacket::BossKilled, v766::LegacyTelemetryEventPacket::SlashCommand, v766::LegacyTelemetryEventPacket::MobBorn, v766::LegacyTelemetryEventPacket::POICauldronUsed, v766::LegacyTelemetryEventPacket::ComposterUsed, v766::LegacyTelemetryEventPacket::BellUsed, v766::LegacyTelemetryEventPacket::ActorDefinition, v766::LegacyTelemetryEventPacket::RaidUpdate, v766::LegacyTelemetryEventPacket::TargetBlockHit, v766::LegacyTelemetryEventPacket::PiglinBarter, v766::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v766::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v766::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v766::LegacyTelemetryEventPacket::ItemUsed, v766::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v766::LegacyTelemetryEventPacket::PortalUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            case 4: {
                std::variant_alternative_t<4, std::variant<v766::LegacyTelemetryEventPacket::Achievement, v766::LegacyTelemetryEventPacket::Interaction, v766::LegacyTelemetryEventPacket::PortalCreated, v766::LegacyTelemetryEventPacket::PortalUsed, v766::LegacyTelemetryEventPacket::MobKilled, v766::LegacyTelemetryEventPacket::CauldronUsed, v766::LegacyTelemetryEventPacket::PlayerDied, v766::LegacyTelemetryEventPacket::BossKilled, v766::LegacyTelemetryEventPacket::SlashCommand, v766::LegacyTelemetryEventPacket::MobBorn, v766::LegacyTelemetryEventPacket::POICauldronUsed, v766::LegacyTelemetryEventPacket::ComposterUsed, v766::LegacyTelemetryEventPacket::BellUsed, v766::LegacyTelemetryEventPacket::ActorDefinition, v766::LegacyTelemetryEventPacket::RaidUpdate, v766::LegacyTelemetryEventPacket::TargetBlockHit, v766::LegacyTelemetryEventPacket::PiglinBarter, v766::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v766::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v766::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v766::LegacyTelemetryEventPacket::ItemUsed, v766::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v766::LegacyTelemetryEventPacket::MobKilled>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<4>(alt0);
                break;
            }
            case 5: {
                std::variant_alternative_t<5, std::variant<v766::LegacyTelemetryEventPacket::Achievement, v766::LegacyTelemetryEventPacket::Interaction, v766::LegacyTelemetryEventPacket::PortalCreated, v766::LegacyTelemetryEventPacket::PortalUsed, v766::LegacyTelemetryEventPacket::MobKilled, v766::LegacyTelemetryEventPacket::CauldronUsed, v766::LegacyTelemetryEventPacket::PlayerDied, v766::LegacyTelemetryEventPacket::BossKilled, v766::LegacyTelemetryEventPacket::SlashCommand, v766::LegacyTelemetryEventPacket::MobBorn, v766::LegacyTelemetryEventPacket::POICauldronUsed, v766::LegacyTelemetryEventPacket::ComposterUsed, v766::LegacyTelemetryEventPacket::BellUsed, v766::LegacyTelemetryEventPacket::ActorDefinition, v766::LegacyTelemetryEventPacket::RaidUpdate, v766::LegacyTelemetryEventPacket::TargetBlockHit, v766::LegacyTelemetryEventPacket::PiglinBarter, v766::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v766::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v766::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v766::LegacyTelemetryEventPacket::ItemUsed, v766::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v766::LegacyTelemetryEventPacket::CauldronUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<5>(alt0);
                break;
            }
            case 6: {
                std::variant_alternative_t<6, std::variant<v766::LegacyTelemetryEventPacket::Achievement, v766::LegacyTelemetryEventPacket::Interaction, v766::LegacyTelemetryEventPacket::PortalCreated, v766::LegacyTelemetryEventPacket::PortalUsed, v766::LegacyTelemetryEventPacket::MobKilled, v766::LegacyTelemetryEventPacket::CauldronUsed, v766::LegacyTelemetryEventPacket::PlayerDied, v766::LegacyTelemetryEventPacket::BossKilled, v766::LegacyTelemetryEventPacket::SlashCommand, v766::LegacyTelemetryEventPacket::MobBorn, v766::LegacyTelemetryEventPacket::POICauldronUsed, v766::LegacyTelemetryEventPacket::ComposterUsed, v766::LegacyTelemetryEventPacket::BellUsed, v766::LegacyTelemetryEventPacket::ActorDefinition, v766::LegacyTelemetryEventPacket::RaidUpdate, v766::LegacyTelemetryEventPacket::TargetBlockHit, v766::LegacyTelemetryEventPacket::PiglinBarter, v766::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v766::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v766::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v766::LegacyTelemetryEventPacket::ItemUsed, v766::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v766::LegacyTelemetryEventPacket::PlayerDied>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<6>(alt0);
                break;
            }
            case 7: {
                std::variant_alternative_t<7, std::variant<v766::LegacyTelemetryEventPacket::Achievement, v766::LegacyTelemetryEventPacket::Interaction, v766::LegacyTelemetryEventPacket::PortalCreated, v766::LegacyTelemetryEventPacket::PortalUsed, v766::LegacyTelemetryEventPacket::MobKilled, v766::LegacyTelemetryEventPacket::CauldronUsed, v766::LegacyTelemetryEventPacket::PlayerDied, v766::LegacyTelemetryEventPacket::BossKilled, v766::LegacyTelemetryEventPacket::SlashCommand, v766::LegacyTelemetryEventPacket::MobBorn, v766::LegacyTelemetryEventPacket::POICauldronUsed, v766::LegacyTelemetryEventPacket::ComposterUsed, v766::LegacyTelemetryEventPacket::BellUsed, v766::LegacyTelemetryEventPacket::ActorDefinition, v766::LegacyTelemetryEventPacket::RaidUpdate, v766::LegacyTelemetryEventPacket::TargetBlockHit, v766::LegacyTelemetryEventPacket::PiglinBarter, v766::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v766::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v766::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v766::LegacyTelemetryEventPacket::ItemUsed, v766::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v766::LegacyTelemetryEventPacket::BossKilled>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<7>(alt0);
                break;
            }
            case 8: {
                std::variant_alternative_t<8, std::variant<v766::LegacyTelemetryEventPacket::Achievement, v766::LegacyTelemetryEventPacket::Interaction, v766::LegacyTelemetryEventPacket::PortalCreated, v766::LegacyTelemetryEventPacket::PortalUsed, v766::LegacyTelemetryEventPacket::MobKilled, v766::LegacyTelemetryEventPacket::CauldronUsed, v766::LegacyTelemetryEventPacket::PlayerDied, v766::LegacyTelemetryEventPacket::BossKilled, v766::LegacyTelemetryEventPacket::SlashCommand, v766::LegacyTelemetryEventPacket::MobBorn, v766::LegacyTelemetryEventPacket::POICauldronUsed, v766::LegacyTelemetryEventPacket::ComposterUsed, v766::LegacyTelemetryEventPacket::BellUsed, v766::LegacyTelemetryEventPacket::ActorDefinition, v766::LegacyTelemetryEventPacket::RaidUpdate, v766::LegacyTelemetryEventPacket::TargetBlockHit, v766::LegacyTelemetryEventPacket::PiglinBarter, v766::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v766::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v766::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v766::LegacyTelemetryEventPacket::ItemUsed, v766::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v766::LegacyTelemetryEventPacket::SlashCommand>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<8>(alt0);
                break;
            }
            case 9: {
                std::variant_alternative_t<9, std::variant<v766::LegacyTelemetryEventPacket::Achievement, v766::LegacyTelemetryEventPacket::Interaction, v766::LegacyTelemetryEventPacket::PortalCreated, v766::LegacyTelemetryEventPacket::PortalUsed, v766::LegacyTelemetryEventPacket::MobKilled, v766::LegacyTelemetryEventPacket::CauldronUsed, v766::LegacyTelemetryEventPacket::PlayerDied, v766::LegacyTelemetryEventPacket::BossKilled, v766::LegacyTelemetryEventPacket::SlashCommand, v766::LegacyTelemetryEventPacket::MobBorn, v766::LegacyTelemetryEventPacket::POICauldronUsed, v766::LegacyTelemetryEventPacket::ComposterUsed, v766::LegacyTelemetryEventPacket::BellUsed, v766::LegacyTelemetryEventPacket::ActorDefinition, v766::LegacyTelemetryEventPacket::RaidUpdate, v766::LegacyTelemetryEventPacket::TargetBlockHit, v766::LegacyTelemetryEventPacket::PiglinBarter, v766::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v766::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v766::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v766::LegacyTelemetryEventPacket::ItemUsed, v766::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v766::LegacyTelemetryEventPacket::MobBorn>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<9>(alt0);
                break;
            }
            case 10: {
                std::variant_alternative_t<10, std::variant<v766::LegacyTelemetryEventPacket::Achievement, v766::LegacyTelemetryEventPacket::Interaction, v766::LegacyTelemetryEventPacket::PortalCreated, v766::LegacyTelemetryEventPacket::PortalUsed, v766::LegacyTelemetryEventPacket::MobKilled, v766::LegacyTelemetryEventPacket::CauldronUsed, v766::LegacyTelemetryEventPacket::PlayerDied, v766::LegacyTelemetryEventPacket::BossKilled, v766::LegacyTelemetryEventPacket::SlashCommand, v766::LegacyTelemetryEventPacket::MobBorn, v766::LegacyTelemetryEventPacket::POICauldronUsed, v766::LegacyTelemetryEventPacket::ComposterUsed, v766::LegacyTelemetryEventPacket::BellUsed, v766::LegacyTelemetryEventPacket::ActorDefinition, v766::LegacyTelemetryEventPacket::RaidUpdate, v766::LegacyTelemetryEventPacket::TargetBlockHit, v766::LegacyTelemetryEventPacket::PiglinBarter, v766::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v766::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v766::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v766::LegacyTelemetryEventPacket::ItemUsed, v766::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v766::LegacyTelemetryEventPacket::POICauldronUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<10>(alt0);
                break;
            }
            case 11: {
                std::variant_alternative_t<11, std::variant<v766::LegacyTelemetryEventPacket::Achievement, v766::LegacyTelemetryEventPacket::Interaction, v766::LegacyTelemetryEventPacket::PortalCreated, v766::LegacyTelemetryEventPacket::PortalUsed, v766::LegacyTelemetryEventPacket::MobKilled, v766::LegacyTelemetryEventPacket::CauldronUsed, v766::LegacyTelemetryEventPacket::PlayerDied, v766::LegacyTelemetryEventPacket::BossKilled, v766::LegacyTelemetryEventPacket::SlashCommand, v766::LegacyTelemetryEventPacket::MobBorn, v766::LegacyTelemetryEventPacket::POICauldronUsed, v766::LegacyTelemetryEventPacket::ComposterUsed, v766::LegacyTelemetryEventPacket::BellUsed, v766::LegacyTelemetryEventPacket::ActorDefinition, v766::LegacyTelemetryEventPacket::RaidUpdate, v766::LegacyTelemetryEventPacket::TargetBlockHit, v766::LegacyTelemetryEventPacket::PiglinBarter, v766::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v766::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v766::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v766::LegacyTelemetryEventPacket::ItemUsed, v766::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v766::LegacyTelemetryEventPacket::ComposterUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<11>(alt0);
                break;
            }
            case 12: {
                std::variant_alternative_t<12, std::variant<v766::LegacyTelemetryEventPacket::Achievement, v766::LegacyTelemetryEventPacket::Interaction, v766::LegacyTelemetryEventPacket::PortalCreated, v766::LegacyTelemetryEventPacket::PortalUsed, v766::LegacyTelemetryEventPacket::MobKilled, v766::LegacyTelemetryEventPacket::CauldronUsed, v766::LegacyTelemetryEventPacket::PlayerDied, v766::LegacyTelemetryEventPacket::BossKilled, v766::LegacyTelemetryEventPacket::SlashCommand, v766::LegacyTelemetryEventPacket::MobBorn, v766::LegacyTelemetryEventPacket::POICauldronUsed, v766::LegacyTelemetryEventPacket::ComposterUsed, v766::LegacyTelemetryEventPacket::BellUsed, v766::LegacyTelemetryEventPacket::ActorDefinition, v766::LegacyTelemetryEventPacket::RaidUpdate, v766::LegacyTelemetryEventPacket::TargetBlockHit, v766::LegacyTelemetryEventPacket::PiglinBarter, v766::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v766::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v766::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v766::LegacyTelemetryEventPacket::ItemUsed, v766::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v766::LegacyTelemetryEventPacket::BellUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<12>(alt0);
                break;
            }
            case 13: {
                std::variant_alternative_t<13, std::variant<v766::LegacyTelemetryEventPacket::Achievement, v766::LegacyTelemetryEventPacket::Interaction, v766::LegacyTelemetryEventPacket::PortalCreated, v766::LegacyTelemetryEventPacket::PortalUsed, v766::LegacyTelemetryEventPacket::MobKilled, v766::LegacyTelemetryEventPacket::CauldronUsed, v766::LegacyTelemetryEventPacket::PlayerDied, v766::LegacyTelemetryEventPacket::BossKilled, v766::LegacyTelemetryEventPacket::SlashCommand, v766::LegacyTelemetryEventPacket::MobBorn, v766::LegacyTelemetryEventPacket::POICauldronUsed, v766::LegacyTelemetryEventPacket::ComposterUsed, v766::LegacyTelemetryEventPacket::BellUsed, v766::LegacyTelemetryEventPacket::ActorDefinition, v766::LegacyTelemetryEventPacket::RaidUpdate, v766::LegacyTelemetryEventPacket::TargetBlockHit, v766::LegacyTelemetryEventPacket::PiglinBarter, v766::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v766::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v766::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v766::LegacyTelemetryEventPacket::ItemUsed, v766::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v766::LegacyTelemetryEventPacket::ActorDefinition>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<13>(alt0);
                break;
            }
            case 14: {
                std::variant_alternative_t<14, std::variant<v766::LegacyTelemetryEventPacket::Achievement, v766::LegacyTelemetryEventPacket::Interaction, v766::LegacyTelemetryEventPacket::PortalCreated, v766::LegacyTelemetryEventPacket::PortalUsed, v766::LegacyTelemetryEventPacket::MobKilled, v766::LegacyTelemetryEventPacket::CauldronUsed, v766::LegacyTelemetryEventPacket::PlayerDied, v766::LegacyTelemetryEventPacket::BossKilled, v766::LegacyTelemetryEventPacket::SlashCommand, v766::LegacyTelemetryEventPacket::MobBorn, v766::LegacyTelemetryEventPacket::POICauldronUsed, v766::LegacyTelemetryEventPacket::ComposterUsed, v766::LegacyTelemetryEventPacket::BellUsed, v766::LegacyTelemetryEventPacket::ActorDefinition, v766::LegacyTelemetryEventPacket::RaidUpdate, v766::LegacyTelemetryEventPacket::TargetBlockHit, v766::LegacyTelemetryEventPacket::PiglinBarter, v766::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v766::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v766::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v766::LegacyTelemetryEventPacket::ItemUsed, v766::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v766::LegacyTelemetryEventPacket::RaidUpdate>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<14>(alt0);
                break;
            }
            case 15: {
                std::variant_alternative_t<15, std::variant<v766::LegacyTelemetryEventPacket::Achievement, v766::LegacyTelemetryEventPacket::Interaction, v766::LegacyTelemetryEventPacket::PortalCreated, v766::LegacyTelemetryEventPacket::PortalUsed, v766::LegacyTelemetryEventPacket::MobKilled, v766::LegacyTelemetryEventPacket::CauldronUsed, v766::LegacyTelemetryEventPacket::PlayerDied, v766::LegacyTelemetryEventPacket::BossKilled, v766::LegacyTelemetryEventPacket::SlashCommand, v766::LegacyTelemetryEventPacket::MobBorn, v766::LegacyTelemetryEventPacket::POICauldronUsed, v766::LegacyTelemetryEventPacket::ComposterUsed, v766::LegacyTelemetryEventPacket::BellUsed, v766::LegacyTelemetryEventPacket::ActorDefinition, v766::LegacyTelemetryEventPacket::RaidUpdate, v766::LegacyTelemetryEventPacket::TargetBlockHit, v766::LegacyTelemetryEventPacket::PiglinBarter, v766::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v766::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v766::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v766::LegacyTelemetryEventPacket::ItemUsed, v766::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v766::LegacyTelemetryEventPacket::TargetBlockHit>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<15>(alt0);
                break;
            }
            case 16: {
                std::variant_alternative_t<16, std::variant<v766::LegacyTelemetryEventPacket::Achievement, v766::LegacyTelemetryEventPacket::Interaction, v766::LegacyTelemetryEventPacket::PortalCreated, v766::LegacyTelemetryEventPacket::PortalUsed, v766::LegacyTelemetryEventPacket::MobKilled, v766::LegacyTelemetryEventPacket::CauldronUsed, v766::LegacyTelemetryEventPacket::PlayerDied, v766::LegacyTelemetryEventPacket::BossKilled, v766::LegacyTelemetryEventPacket::SlashCommand, v766::LegacyTelemetryEventPacket::MobBorn, v766::LegacyTelemetryEventPacket::POICauldronUsed, v766::LegacyTelemetryEventPacket::ComposterUsed, v766::LegacyTelemetryEventPacket::BellUsed, v766::LegacyTelemetryEventPacket::ActorDefinition, v766::LegacyTelemetryEventPacket::RaidUpdate, v766::LegacyTelemetryEventPacket::TargetBlockHit, v766::LegacyTelemetryEventPacket::PiglinBarter, v766::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v766::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v766::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v766::LegacyTelemetryEventPacket::ItemUsed, v766::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v766::LegacyTelemetryEventPacket::PiglinBarter>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<16>(alt0);
                break;
            }
            case 17: {
                std::variant_alternative_t<17, std::variant<v766::LegacyTelemetryEventPacket::Achievement, v766::LegacyTelemetryEventPacket::Interaction, v766::LegacyTelemetryEventPacket::PortalCreated, v766::LegacyTelemetryEventPacket::PortalUsed, v766::LegacyTelemetryEventPacket::MobKilled, v766::LegacyTelemetryEventPacket::CauldronUsed, v766::LegacyTelemetryEventPacket::PlayerDied, v766::LegacyTelemetryEventPacket::BossKilled, v766::LegacyTelemetryEventPacket::SlashCommand, v766::LegacyTelemetryEventPacket::MobBorn, v766::LegacyTelemetryEventPacket::POICauldronUsed, v766::LegacyTelemetryEventPacket::ComposterUsed, v766::LegacyTelemetryEventPacket::BellUsed, v766::LegacyTelemetryEventPacket::ActorDefinition, v766::LegacyTelemetryEventPacket::RaidUpdate, v766::LegacyTelemetryEventPacket::TargetBlockHit, v766::LegacyTelemetryEventPacket::PiglinBarter, v766::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v766::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v766::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v766::LegacyTelemetryEventPacket::ItemUsed, v766::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v766::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<17>(alt0);
                break;
            }
            case 18: {
                std::variant_alternative_t<18, std::variant<v766::LegacyTelemetryEventPacket::Achievement, v766::LegacyTelemetryEventPacket::Interaction, v766::LegacyTelemetryEventPacket::PortalCreated, v766::LegacyTelemetryEventPacket::PortalUsed, v766::LegacyTelemetryEventPacket::MobKilled, v766::LegacyTelemetryEventPacket::CauldronUsed, v766::LegacyTelemetryEventPacket::PlayerDied, v766::LegacyTelemetryEventPacket::BossKilled, v766::LegacyTelemetryEventPacket::SlashCommand, v766::LegacyTelemetryEventPacket::MobBorn, v766::LegacyTelemetryEventPacket::POICauldronUsed, v766::LegacyTelemetryEventPacket::ComposterUsed, v766::LegacyTelemetryEventPacket::BellUsed, v766::LegacyTelemetryEventPacket::ActorDefinition, v766::LegacyTelemetryEventPacket::RaidUpdate, v766::LegacyTelemetryEventPacket::TargetBlockHit, v766::LegacyTelemetryEventPacket::PiglinBarter, v766::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v766::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v766::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v766::LegacyTelemetryEventPacket::ItemUsed, v766::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v766::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<18>(alt0);
                break;
            }
            case 19: {
                std::variant_alternative_t<19, std::variant<v766::LegacyTelemetryEventPacket::Achievement, v766::LegacyTelemetryEventPacket::Interaction, v766::LegacyTelemetryEventPacket::PortalCreated, v766::LegacyTelemetryEventPacket::PortalUsed, v766::LegacyTelemetryEventPacket::MobKilled, v766::LegacyTelemetryEventPacket::CauldronUsed, v766::LegacyTelemetryEventPacket::PlayerDied, v766::LegacyTelemetryEventPacket::BossKilled, v766::LegacyTelemetryEventPacket::SlashCommand, v766::LegacyTelemetryEventPacket::MobBorn, v766::LegacyTelemetryEventPacket::POICauldronUsed, v766::LegacyTelemetryEventPacket::ComposterUsed, v766::LegacyTelemetryEventPacket::BellUsed, v766::LegacyTelemetryEventPacket::ActorDefinition, v766::LegacyTelemetryEventPacket::RaidUpdate, v766::LegacyTelemetryEventPacket::TargetBlockHit, v766::LegacyTelemetryEventPacket::PiglinBarter, v766::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v766::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v766::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v766::LegacyTelemetryEventPacket::ItemUsed, v766::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v766::LegacyTelemetryEventPacket::CodeBuilderScoreboard>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<19>(alt0);
                break;
            }
            case 20: {
                std::variant_alternative_t<20, std::variant<v766::LegacyTelemetryEventPacket::Achievement, v766::LegacyTelemetryEventPacket::Interaction, v766::LegacyTelemetryEventPacket::PortalCreated, v766::LegacyTelemetryEventPacket::PortalUsed, v766::LegacyTelemetryEventPacket::MobKilled, v766::LegacyTelemetryEventPacket::CauldronUsed, v766::LegacyTelemetryEventPacket::PlayerDied, v766::LegacyTelemetryEventPacket::BossKilled, v766::LegacyTelemetryEventPacket::SlashCommand, v766::LegacyTelemetryEventPacket::MobBorn, v766::LegacyTelemetryEventPacket::POICauldronUsed, v766::LegacyTelemetryEventPacket::ComposterUsed, v766::LegacyTelemetryEventPacket::BellUsed, v766::LegacyTelemetryEventPacket::ActorDefinition, v766::LegacyTelemetryEventPacket::RaidUpdate, v766::LegacyTelemetryEventPacket::TargetBlockHit, v766::LegacyTelemetryEventPacket::PiglinBarter, v766::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v766::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v766::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v766::LegacyTelemetryEventPacket::ItemUsed, v766::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v766::LegacyTelemetryEventPacket::ItemUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<20>(alt0);
                break;
            }
            case 21: {
                std::variant_alternative_t<21, std::variant<v766::LegacyTelemetryEventPacket::Achievement, v766::LegacyTelemetryEventPacket::Interaction, v766::LegacyTelemetryEventPacket::PortalCreated, v766::LegacyTelemetryEventPacket::PortalUsed, v766::LegacyTelemetryEventPacket::MobKilled, v766::LegacyTelemetryEventPacket::CauldronUsed, v766::LegacyTelemetryEventPacket::PlayerDied, v766::LegacyTelemetryEventPacket::BossKilled, v766::LegacyTelemetryEventPacket::SlashCommand, v766::LegacyTelemetryEventPacket::MobBorn, v766::LegacyTelemetryEventPacket::POICauldronUsed, v766::LegacyTelemetryEventPacket::ComposterUsed, v766::LegacyTelemetryEventPacket::BellUsed, v766::LegacyTelemetryEventPacket::ActorDefinition, v766::LegacyTelemetryEventPacket::RaidUpdate, v766::LegacyTelemetryEventPacket::TargetBlockHit, v766::LegacyTelemetryEventPacket::PiglinBarter, v766::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v766::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v766::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v766::LegacyTelemetryEventPacket::ItemUsed, v766::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v766::LegacyTelemetryEventPacket::Empty>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<21>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.event_data = var0;
    }
    return out;
}

void Serializer<v776::LegacyTelemetryEventPacket>::serialize(BinaryWriter &stream, const v776::LegacyTelemetryEventPacket &value)
{
    stream.writeVarInt<std::int64_t>(value.player_unique_id);
    stream.writeVarInt<std::int32_t>(value.type);
    stream.write<bool>(value.use_player_id);
    stream.writeVarInt<std::uint32_t>((value.event_data).index());
    switch ((value.event_data).index()) {
        case 0: {
            Serializer<v776::LegacyTelemetryEventPacket::Achievement>::serialize(stream, std::get<0>(value.event_data));
            break;
        }
        case 1: {
            Serializer<v776::LegacyTelemetryEventPacket::Interaction>::serialize(stream, std::get<1>(value.event_data));
            break;
        }
        case 2: {
            Serializer<v776::LegacyTelemetryEventPacket::PortalCreated>::serialize(stream, std::get<2>(value.event_data));
            break;
        }
        case 3: {
            Serializer<v776::LegacyTelemetryEventPacket::PortalUsed>::serialize(stream, std::get<3>(value.event_data));
            break;
        }
        case 4: {
            Serializer<v776::LegacyTelemetryEventPacket::MobKilled>::serialize(stream, std::get<4>(value.event_data));
            break;
        }
        case 5: {
            Serializer<v776::LegacyTelemetryEventPacket::CauldronUsed>::serialize(stream, std::get<5>(value.event_data));
            break;
        }
        case 6: {
            Serializer<v776::LegacyTelemetryEventPacket::PlayerDied>::serialize(stream, std::get<6>(value.event_data));
            break;
        }
        case 7: {
            Serializer<v776::LegacyTelemetryEventPacket::BossKilled>::serialize(stream, std::get<7>(value.event_data));
            break;
        }
        case 8: {
            Serializer<v776::LegacyTelemetryEventPacket::SlashCommand>::serialize(stream, std::get<8>(value.event_data));
            break;
        }
        case 9: {
            Serializer<v776::LegacyTelemetryEventPacket::MobBorn>::serialize(stream, std::get<9>(value.event_data));
            break;
        }
        case 10: {
            Serializer<v776::LegacyTelemetryEventPacket::POICauldronUsed>::serialize(stream, std::get<10>(value.event_data));
            break;
        }
        case 11: {
            Serializer<v776::LegacyTelemetryEventPacket::ComposterUsed>::serialize(stream, std::get<11>(value.event_data));
            break;
        }
        case 12: {
            Serializer<v776::LegacyTelemetryEventPacket::BellUsed>::serialize(stream, std::get<12>(value.event_data));
            break;
        }
        case 13: {
            Serializer<v776::LegacyTelemetryEventPacket::ActorDefinition>::serialize(stream, std::get<13>(value.event_data));
            break;
        }
        case 14: {
            Serializer<v776::LegacyTelemetryEventPacket::RaidUpdate>::serialize(stream, std::get<14>(value.event_data));
            break;
        }
        case 15: {
            Serializer<v776::LegacyTelemetryEventPacket::TargetBlockHit>::serialize(stream, std::get<15>(value.event_data));
            break;
        }
        case 16: {
            Serializer<v776::LegacyTelemetryEventPacket::PiglinBarter>::serialize(stream, std::get<16>(value.event_data));
            break;
        }
        case 17: {
            Serializer<v776::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper>::serialize(stream, std::get<17>(value.event_data));
            break;
        }
        case 18: {
            Serializer<v776::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction>::serialize(stream, std::get<18>(value.event_data));
            break;
        }
        case 19: {
            Serializer<v776::LegacyTelemetryEventPacket::CodeBuilderScoreboard>::serialize(stream, std::get<19>(value.event_data));
            break;
        }
        case 20: {
            Serializer<v776::LegacyTelemetryEventPacket::ItemUsed>::serialize(stream, std::get<20>(value.event_data));
            break;
        }
        case 21: {
            Serializer<v776::LegacyTelemetryEventPacket::Empty>::serialize(stream, std::get<21>(value.event_data));
            break;
        }
    }
}

auto Serializer<v776::LegacyTelemetryEventPacket>::deserialize(BinaryReader &stream) -> std::expected<v776::LegacyTelemetryEventPacket, std::error_code>
{
    v776::LegacyTelemetryEventPacket out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.player_unique_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<v776::LegacyTelemetryEventPacket::Type>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.use_player_id = static_cast<bool>(*v);
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v776::LegacyTelemetryEventPacket::Achievement, v776::LegacyTelemetryEventPacket::Interaction, v776::LegacyTelemetryEventPacket::PortalCreated, v776::LegacyTelemetryEventPacket::PortalUsed, v776::LegacyTelemetryEventPacket::MobKilled, v776::LegacyTelemetryEventPacket::CauldronUsed, v776::LegacyTelemetryEventPacket::PlayerDied, v776::LegacyTelemetryEventPacket::BossKilled, v776::LegacyTelemetryEventPacket::SlashCommand, v776::LegacyTelemetryEventPacket::MobBorn, v776::LegacyTelemetryEventPacket::POICauldronUsed, v776::LegacyTelemetryEventPacket::ComposterUsed, v776::LegacyTelemetryEventPacket::BellUsed, v776::LegacyTelemetryEventPacket::ActorDefinition, v776::LegacyTelemetryEventPacket::RaidUpdate, v776::LegacyTelemetryEventPacket::TargetBlockHit, v776::LegacyTelemetryEventPacket::PiglinBarter, v776::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v776::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v776::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v776::LegacyTelemetryEventPacket::ItemUsed, v776::LegacyTelemetryEventPacket::Empty> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v776::LegacyTelemetryEventPacket::Achievement, v776::LegacyTelemetryEventPacket::Interaction, v776::LegacyTelemetryEventPacket::PortalCreated, v776::LegacyTelemetryEventPacket::PortalUsed, v776::LegacyTelemetryEventPacket::MobKilled, v776::LegacyTelemetryEventPacket::CauldronUsed, v776::LegacyTelemetryEventPacket::PlayerDied, v776::LegacyTelemetryEventPacket::BossKilled, v776::LegacyTelemetryEventPacket::SlashCommand, v776::LegacyTelemetryEventPacket::MobBorn, v776::LegacyTelemetryEventPacket::POICauldronUsed, v776::LegacyTelemetryEventPacket::ComposterUsed, v776::LegacyTelemetryEventPacket::BellUsed, v776::LegacyTelemetryEventPacket::ActorDefinition, v776::LegacyTelemetryEventPacket::RaidUpdate, v776::LegacyTelemetryEventPacket::TargetBlockHit, v776::LegacyTelemetryEventPacket::PiglinBarter, v776::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v776::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v776::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v776::LegacyTelemetryEventPacket::ItemUsed, v776::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v776::LegacyTelemetryEventPacket::Achievement>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v776::LegacyTelemetryEventPacket::Achievement, v776::LegacyTelemetryEventPacket::Interaction, v776::LegacyTelemetryEventPacket::PortalCreated, v776::LegacyTelemetryEventPacket::PortalUsed, v776::LegacyTelemetryEventPacket::MobKilled, v776::LegacyTelemetryEventPacket::CauldronUsed, v776::LegacyTelemetryEventPacket::PlayerDied, v776::LegacyTelemetryEventPacket::BossKilled, v776::LegacyTelemetryEventPacket::SlashCommand, v776::LegacyTelemetryEventPacket::MobBorn, v776::LegacyTelemetryEventPacket::POICauldronUsed, v776::LegacyTelemetryEventPacket::ComposterUsed, v776::LegacyTelemetryEventPacket::BellUsed, v776::LegacyTelemetryEventPacket::ActorDefinition, v776::LegacyTelemetryEventPacket::RaidUpdate, v776::LegacyTelemetryEventPacket::TargetBlockHit, v776::LegacyTelemetryEventPacket::PiglinBarter, v776::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v776::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v776::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v776::LegacyTelemetryEventPacket::ItemUsed, v776::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v776::LegacyTelemetryEventPacket::Interaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<v776::LegacyTelemetryEventPacket::Achievement, v776::LegacyTelemetryEventPacket::Interaction, v776::LegacyTelemetryEventPacket::PortalCreated, v776::LegacyTelemetryEventPacket::PortalUsed, v776::LegacyTelemetryEventPacket::MobKilled, v776::LegacyTelemetryEventPacket::CauldronUsed, v776::LegacyTelemetryEventPacket::PlayerDied, v776::LegacyTelemetryEventPacket::BossKilled, v776::LegacyTelemetryEventPacket::SlashCommand, v776::LegacyTelemetryEventPacket::MobBorn, v776::LegacyTelemetryEventPacket::POICauldronUsed, v776::LegacyTelemetryEventPacket::ComposterUsed, v776::LegacyTelemetryEventPacket::BellUsed, v776::LegacyTelemetryEventPacket::ActorDefinition, v776::LegacyTelemetryEventPacket::RaidUpdate, v776::LegacyTelemetryEventPacket::TargetBlockHit, v776::LegacyTelemetryEventPacket::PiglinBarter, v776::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v776::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v776::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v776::LegacyTelemetryEventPacket::ItemUsed, v776::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v776::LegacyTelemetryEventPacket::PortalCreated>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<v776::LegacyTelemetryEventPacket::Achievement, v776::LegacyTelemetryEventPacket::Interaction, v776::LegacyTelemetryEventPacket::PortalCreated, v776::LegacyTelemetryEventPacket::PortalUsed, v776::LegacyTelemetryEventPacket::MobKilled, v776::LegacyTelemetryEventPacket::CauldronUsed, v776::LegacyTelemetryEventPacket::PlayerDied, v776::LegacyTelemetryEventPacket::BossKilled, v776::LegacyTelemetryEventPacket::SlashCommand, v776::LegacyTelemetryEventPacket::MobBorn, v776::LegacyTelemetryEventPacket::POICauldronUsed, v776::LegacyTelemetryEventPacket::ComposterUsed, v776::LegacyTelemetryEventPacket::BellUsed, v776::LegacyTelemetryEventPacket::ActorDefinition, v776::LegacyTelemetryEventPacket::RaidUpdate, v776::LegacyTelemetryEventPacket::TargetBlockHit, v776::LegacyTelemetryEventPacket::PiglinBarter, v776::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v776::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v776::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v776::LegacyTelemetryEventPacket::ItemUsed, v776::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v776::LegacyTelemetryEventPacket::PortalUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            case 4: {
                std::variant_alternative_t<4, std::variant<v776::LegacyTelemetryEventPacket::Achievement, v776::LegacyTelemetryEventPacket::Interaction, v776::LegacyTelemetryEventPacket::PortalCreated, v776::LegacyTelemetryEventPacket::PortalUsed, v776::LegacyTelemetryEventPacket::MobKilled, v776::LegacyTelemetryEventPacket::CauldronUsed, v776::LegacyTelemetryEventPacket::PlayerDied, v776::LegacyTelemetryEventPacket::BossKilled, v776::LegacyTelemetryEventPacket::SlashCommand, v776::LegacyTelemetryEventPacket::MobBorn, v776::LegacyTelemetryEventPacket::POICauldronUsed, v776::LegacyTelemetryEventPacket::ComposterUsed, v776::LegacyTelemetryEventPacket::BellUsed, v776::LegacyTelemetryEventPacket::ActorDefinition, v776::LegacyTelemetryEventPacket::RaidUpdate, v776::LegacyTelemetryEventPacket::TargetBlockHit, v776::LegacyTelemetryEventPacket::PiglinBarter, v776::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v776::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v776::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v776::LegacyTelemetryEventPacket::ItemUsed, v776::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v776::LegacyTelemetryEventPacket::MobKilled>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<4>(alt0);
                break;
            }
            case 5: {
                std::variant_alternative_t<5, std::variant<v776::LegacyTelemetryEventPacket::Achievement, v776::LegacyTelemetryEventPacket::Interaction, v776::LegacyTelemetryEventPacket::PortalCreated, v776::LegacyTelemetryEventPacket::PortalUsed, v776::LegacyTelemetryEventPacket::MobKilled, v776::LegacyTelemetryEventPacket::CauldronUsed, v776::LegacyTelemetryEventPacket::PlayerDied, v776::LegacyTelemetryEventPacket::BossKilled, v776::LegacyTelemetryEventPacket::SlashCommand, v776::LegacyTelemetryEventPacket::MobBorn, v776::LegacyTelemetryEventPacket::POICauldronUsed, v776::LegacyTelemetryEventPacket::ComposterUsed, v776::LegacyTelemetryEventPacket::BellUsed, v776::LegacyTelemetryEventPacket::ActorDefinition, v776::LegacyTelemetryEventPacket::RaidUpdate, v776::LegacyTelemetryEventPacket::TargetBlockHit, v776::LegacyTelemetryEventPacket::PiglinBarter, v776::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v776::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v776::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v776::LegacyTelemetryEventPacket::ItemUsed, v776::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v776::LegacyTelemetryEventPacket::CauldronUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<5>(alt0);
                break;
            }
            case 6: {
                std::variant_alternative_t<6, std::variant<v776::LegacyTelemetryEventPacket::Achievement, v776::LegacyTelemetryEventPacket::Interaction, v776::LegacyTelemetryEventPacket::PortalCreated, v776::LegacyTelemetryEventPacket::PortalUsed, v776::LegacyTelemetryEventPacket::MobKilled, v776::LegacyTelemetryEventPacket::CauldronUsed, v776::LegacyTelemetryEventPacket::PlayerDied, v776::LegacyTelemetryEventPacket::BossKilled, v776::LegacyTelemetryEventPacket::SlashCommand, v776::LegacyTelemetryEventPacket::MobBorn, v776::LegacyTelemetryEventPacket::POICauldronUsed, v776::LegacyTelemetryEventPacket::ComposterUsed, v776::LegacyTelemetryEventPacket::BellUsed, v776::LegacyTelemetryEventPacket::ActorDefinition, v776::LegacyTelemetryEventPacket::RaidUpdate, v776::LegacyTelemetryEventPacket::TargetBlockHit, v776::LegacyTelemetryEventPacket::PiglinBarter, v776::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v776::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v776::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v776::LegacyTelemetryEventPacket::ItemUsed, v776::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v776::LegacyTelemetryEventPacket::PlayerDied>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<6>(alt0);
                break;
            }
            case 7: {
                std::variant_alternative_t<7, std::variant<v776::LegacyTelemetryEventPacket::Achievement, v776::LegacyTelemetryEventPacket::Interaction, v776::LegacyTelemetryEventPacket::PortalCreated, v776::LegacyTelemetryEventPacket::PortalUsed, v776::LegacyTelemetryEventPacket::MobKilled, v776::LegacyTelemetryEventPacket::CauldronUsed, v776::LegacyTelemetryEventPacket::PlayerDied, v776::LegacyTelemetryEventPacket::BossKilled, v776::LegacyTelemetryEventPacket::SlashCommand, v776::LegacyTelemetryEventPacket::MobBorn, v776::LegacyTelemetryEventPacket::POICauldronUsed, v776::LegacyTelemetryEventPacket::ComposterUsed, v776::LegacyTelemetryEventPacket::BellUsed, v776::LegacyTelemetryEventPacket::ActorDefinition, v776::LegacyTelemetryEventPacket::RaidUpdate, v776::LegacyTelemetryEventPacket::TargetBlockHit, v776::LegacyTelemetryEventPacket::PiglinBarter, v776::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v776::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v776::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v776::LegacyTelemetryEventPacket::ItemUsed, v776::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v776::LegacyTelemetryEventPacket::BossKilled>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<7>(alt0);
                break;
            }
            case 8: {
                std::variant_alternative_t<8, std::variant<v776::LegacyTelemetryEventPacket::Achievement, v776::LegacyTelemetryEventPacket::Interaction, v776::LegacyTelemetryEventPacket::PortalCreated, v776::LegacyTelemetryEventPacket::PortalUsed, v776::LegacyTelemetryEventPacket::MobKilled, v776::LegacyTelemetryEventPacket::CauldronUsed, v776::LegacyTelemetryEventPacket::PlayerDied, v776::LegacyTelemetryEventPacket::BossKilled, v776::LegacyTelemetryEventPacket::SlashCommand, v776::LegacyTelemetryEventPacket::MobBorn, v776::LegacyTelemetryEventPacket::POICauldronUsed, v776::LegacyTelemetryEventPacket::ComposterUsed, v776::LegacyTelemetryEventPacket::BellUsed, v776::LegacyTelemetryEventPacket::ActorDefinition, v776::LegacyTelemetryEventPacket::RaidUpdate, v776::LegacyTelemetryEventPacket::TargetBlockHit, v776::LegacyTelemetryEventPacket::PiglinBarter, v776::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v776::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v776::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v776::LegacyTelemetryEventPacket::ItemUsed, v776::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v776::LegacyTelemetryEventPacket::SlashCommand>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<8>(alt0);
                break;
            }
            case 9: {
                std::variant_alternative_t<9, std::variant<v776::LegacyTelemetryEventPacket::Achievement, v776::LegacyTelemetryEventPacket::Interaction, v776::LegacyTelemetryEventPacket::PortalCreated, v776::LegacyTelemetryEventPacket::PortalUsed, v776::LegacyTelemetryEventPacket::MobKilled, v776::LegacyTelemetryEventPacket::CauldronUsed, v776::LegacyTelemetryEventPacket::PlayerDied, v776::LegacyTelemetryEventPacket::BossKilled, v776::LegacyTelemetryEventPacket::SlashCommand, v776::LegacyTelemetryEventPacket::MobBorn, v776::LegacyTelemetryEventPacket::POICauldronUsed, v776::LegacyTelemetryEventPacket::ComposterUsed, v776::LegacyTelemetryEventPacket::BellUsed, v776::LegacyTelemetryEventPacket::ActorDefinition, v776::LegacyTelemetryEventPacket::RaidUpdate, v776::LegacyTelemetryEventPacket::TargetBlockHit, v776::LegacyTelemetryEventPacket::PiglinBarter, v776::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v776::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v776::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v776::LegacyTelemetryEventPacket::ItemUsed, v776::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v776::LegacyTelemetryEventPacket::MobBorn>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<9>(alt0);
                break;
            }
            case 10: {
                std::variant_alternative_t<10, std::variant<v776::LegacyTelemetryEventPacket::Achievement, v776::LegacyTelemetryEventPacket::Interaction, v776::LegacyTelemetryEventPacket::PortalCreated, v776::LegacyTelemetryEventPacket::PortalUsed, v776::LegacyTelemetryEventPacket::MobKilled, v776::LegacyTelemetryEventPacket::CauldronUsed, v776::LegacyTelemetryEventPacket::PlayerDied, v776::LegacyTelemetryEventPacket::BossKilled, v776::LegacyTelemetryEventPacket::SlashCommand, v776::LegacyTelemetryEventPacket::MobBorn, v776::LegacyTelemetryEventPacket::POICauldronUsed, v776::LegacyTelemetryEventPacket::ComposterUsed, v776::LegacyTelemetryEventPacket::BellUsed, v776::LegacyTelemetryEventPacket::ActorDefinition, v776::LegacyTelemetryEventPacket::RaidUpdate, v776::LegacyTelemetryEventPacket::TargetBlockHit, v776::LegacyTelemetryEventPacket::PiglinBarter, v776::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v776::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v776::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v776::LegacyTelemetryEventPacket::ItemUsed, v776::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v776::LegacyTelemetryEventPacket::POICauldronUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<10>(alt0);
                break;
            }
            case 11: {
                std::variant_alternative_t<11, std::variant<v776::LegacyTelemetryEventPacket::Achievement, v776::LegacyTelemetryEventPacket::Interaction, v776::LegacyTelemetryEventPacket::PortalCreated, v776::LegacyTelemetryEventPacket::PortalUsed, v776::LegacyTelemetryEventPacket::MobKilled, v776::LegacyTelemetryEventPacket::CauldronUsed, v776::LegacyTelemetryEventPacket::PlayerDied, v776::LegacyTelemetryEventPacket::BossKilled, v776::LegacyTelemetryEventPacket::SlashCommand, v776::LegacyTelemetryEventPacket::MobBorn, v776::LegacyTelemetryEventPacket::POICauldronUsed, v776::LegacyTelemetryEventPacket::ComposterUsed, v776::LegacyTelemetryEventPacket::BellUsed, v776::LegacyTelemetryEventPacket::ActorDefinition, v776::LegacyTelemetryEventPacket::RaidUpdate, v776::LegacyTelemetryEventPacket::TargetBlockHit, v776::LegacyTelemetryEventPacket::PiglinBarter, v776::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v776::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v776::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v776::LegacyTelemetryEventPacket::ItemUsed, v776::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v776::LegacyTelemetryEventPacket::ComposterUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<11>(alt0);
                break;
            }
            case 12: {
                std::variant_alternative_t<12, std::variant<v776::LegacyTelemetryEventPacket::Achievement, v776::LegacyTelemetryEventPacket::Interaction, v776::LegacyTelemetryEventPacket::PortalCreated, v776::LegacyTelemetryEventPacket::PortalUsed, v776::LegacyTelemetryEventPacket::MobKilled, v776::LegacyTelemetryEventPacket::CauldronUsed, v776::LegacyTelemetryEventPacket::PlayerDied, v776::LegacyTelemetryEventPacket::BossKilled, v776::LegacyTelemetryEventPacket::SlashCommand, v776::LegacyTelemetryEventPacket::MobBorn, v776::LegacyTelemetryEventPacket::POICauldronUsed, v776::LegacyTelemetryEventPacket::ComposterUsed, v776::LegacyTelemetryEventPacket::BellUsed, v776::LegacyTelemetryEventPacket::ActorDefinition, v776::LegacyTelemetryEventPacket::RaidUpdate, v776::LegacyTelemetryEventPacket::TargetBlockHit, v776::LegacyTelemetryEventPacket::PiglinBarter, v776::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v776::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v776::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v776::LegacyTelemetryEventPacket::ItemUsed, v776::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v776::LegacyTelemetryEventPacket::BellUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<12>(alt0);
                break;
            }
            case 13: {
                std::variant_alternative_t<13, std::variant<v776::LegacyTelemetryEventPacket::Achievement, v776::LegacyTelemetryEventPacket::Interaction, v776::LegacyTelemetryEventPacket::PortalCreated, v776::LegacyTelemetryEventPacket::PortalUsed, v776::LegacyTelemetryEventPacket::MobKilled, v776::LegacyTelemetryEventPacket::CauldronUsed, v776::LegacyTelemetryEventPacket::PlayerDied, v776::LegacyTelemetryEventPacket::BossKilled, v776::LegacyTelemetryEventPacket::SlashCommand, v776::LegacyTelemetryEventPacket::MobBorn, v776::LegacyTelemetryEventPacket::POICauldronUsed, v776::LegacyTelemetryEventPacket::ComposterUsed, v776::LegacyTelemetryEventPacket::BellUsed, v776::LegacyTelemetryEventPacket::ActorDefinition, v776::LegacyTelemetryEventPacket::RaidUpdate, v776::LegacyTelemetryEventPacket::TargetBlockHit, v776::LegacyTelemetryEventPacket::PiglinBarter, v776::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v776::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v776::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v776::LegacyTelemetryEventPacket::ItemUsed, v776::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v776::LegacyTelemetryEventPacket::ActorDefinition>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<13>(alt0);
                break;
            }
            case 14: {
                std::variant_alternative_t<14, std::variant<v776::LegacyTelemetryEventPacket::Achievement, v776::LegacyTelemetryEventPacket::Interaction, v776::LegacyTelemetryEventPacket::PortalCreated, v776::LegacyTelemetryEventPacket::PortalUsed, v776::LegacyTelemetryEventPacket::MobKilled, v776::LegacyTelemetryEventPacket::CauldronUsed, v776::LegacyTelemetryEventPacket::PlayerDied, v776::LegacyTelemetryEventPacket::BossKilled, v776::LegacyTelemetryEventPacket::SlashCommand, v776::LegacyTelemetryEventPacket::MobBorn, v776::LegacyTelemetryEventPacket::POICauldronUsed, v776::LegacyTelemetryEventPacket::ComposterUsed, v776::LegacyTelemetryEventPacket::BellUsed, v776::LegacyTelemetryEventPacket::ActorDefinition, v776::LegacyTelemetryEventPacket::RaidUpdate, v776::LegacyTelemetryEventPacket::TargetBlockHit, v776::LegacyTelemetryEventPacket::PiglinBarter, v776::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v776::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v776::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v776::LegacyTelemetryEventPacket::ItemUsed, v776::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v776::LegacyTelemetryEventPacket::RaidUpdate>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<14>(alt0);
                break;
            }
            case 15: {
                std::variant_alternative_t<15, std::variant<v776::LegacyTelemetryEventPacket::Achievement, v776::LegacyTelemetryEventPacket::Interaction, v776::LegacyTelemetryEventPacket::PortalCreated, v776::LegacyTelemetryEventPacket::PortalUsed, v776::LegacyTelemetryEventPacket::MobKilled, v776::LegacyTelemetryEventPacket::CauldronUsed, v776::LegacyTelemetryEventPacket::PlayerDied, v776::LegacyTelemetryEventPacket::BossKilled, v776::LegacyTelemetryEventPacket::SlashCommand, v776::LegacyTelemetryEventPacket::MobBorn, v776::LegacyTelemetryEventPacket::POICauldronUsed, v776::LegacyTelemetryEventPacket::ComposterUsed, v776::LegacyTelemetryEventPacket::BellUsed, v776::LegacyTelemetryEventPacket::ActorDefinition, v776::LegacyTelemetryEventPacket::RaidUpdate, v776::LegacyTelemetryEventPacket::TargetBlockHit, v776::LegacyTelemetryEventPacket::PiglinBarter, v776::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v776::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v776::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v776::LegacyTelemetryEventPacket::ItemUsed, v776::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v776::LegacyTelemetryEventPacket::TargetBlockHit>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<15>(alt0);
                break;
            }
            case 16: {
                std::variant_alternative_t<16, std::variant<v776::LegacyTelemetryEventPacket::Achievement, v776::LegacyTelemetryEventPacket::Interaction, v776::LegacyTelemetryEventPacket::PortalCreated, v776::LegacyTelemetryEventPacket::PortalUsed, v776::LegacyTelemetryEventPacket::MobKilled, v776::LegacyTelemetryEventPacket::CauldronUsed, v776::LegacyTelemetryEventPacket::PlayerDied, v776::LegacyTelemetryEventPacket::BossKilled, v776::LegacyTelemetryEventPacket::SlashCommand, v776::LegacyTelemetryEventPacket::MobBorn, v776::LegacyTelemetryEventPacket::POICauldronUsed, v776::LegacyTelemetryEventPacket::ComposterUsed, v776::LegacyTelemetryEventPacket::BellUsed, v776::LegacyTelemetryEventPacket::ActorDefinition, v776::LegacyTelemetryEventPacket::RaidUpdate, v776::LegacyTelemetryEventPacket::TargetBlockHit, v776::LegacyTelemetryEventPacket::PiglinBarter, v776::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v776::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v776::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v776::LegacyTelemetryEventPacket::ItemUsed, v776::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v776::LegacyTelemetryEventPacket::PiglinBarter>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<16>(alt0);
                break;
            }
            case 17: {
                std::variant_alternative_t<17, std::variant<v776::LegacyTelemetryEventPacket::Achievement, v776::LegacyTelemetryEventPacket::Interaction, v776::LegacyTelemetryEventPacket::PortalCreated, v776::LegacyTelemetryEventPacket::PortalUsed, v776::LegacyTelemetryEventPacket::MobKilled, v776::LegacyTelemetryEventPacket::CauldronUsed, v776::LegacyTelemetryEventPacket::PlayerDied, v776::LegacyTelemetryEventPacket::BossKilled, v776::LegacyTelemetryEventPacket::SlashCommand, v776::LegacyTelemetryEventPacket::MobBorn, v776::LegacyTelemetryEventPacket::POICauldronUsed, v776::LegacyTelemetryEventPacket::ComposterUsed, v776::LegacyTelemetryEventPacket::BellUsed, v776::LegacyTelemetryEventPacket::ActorDefinition, v776::LegacyTelemetryEventPacket::RaidUpdate, v776::LegacyTelemetryEventPacket::TargetBlockHit, v776::LegacyTelemetryEventPacket::PiglinBarter, v776::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v776::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v776::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v776::LegacyTelemetryEventPacket::ItemUsed, v776::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v776::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<17>(alt0);
                break;
            }
            case 18: {
                std::variant_alternative_t<18, std::variant<v776::LegacyTelemetryEventPacket::Achievement, v776::LegacyTelemetryEventPacket::Interaction, v776::LegacyTelemetryEventPacket::PortalCreated, v776::LegacyTelemetryEventPacket::PortalUsed, v776::LegacyTelemetryEventPacket::MobKilled, v776::LegacyTelemetryEventPacket::CauldronUsed, v776::LegacyTelemetryEventPacket::PlayerDied, v776::LegacyTelemetryEventPacket::BossKilled, v776::LegacyTelemetryEventPacket::SlashCommand, v776::LegacyTelemetryEventPacket::MobBorn, v776::LegacyTelemetryEventPacket::POICauldronUsed, v776::LegacyTelemetryEventPacket::ComposterUsed, v776::LegacyTelemetryEventPacket::BellUsed, v776::LegacyTelemetryEventPacket::ActorDefinition, v776::LegacyTelemetryEventPacket::RaidUpdate, v776::LegacyTelemetryEventPacket::TargetBlockHit, v776::LegacyTelemetryEventPacket::PiglinBarter, v776::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v776::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v776::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v776::LegacyTelemetryEventPacket::ItemUsed, v776::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v776::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<18>(alt0);
                break;
            }
            case 19: {
                std::variant_alternative_t<19, std::variant<v776::LegacyTelemetryEventPacket::Achievement, v776::LegacyTelemetryEventPacket::Interaction, v776::LegacyTelemetryEventPacket::PortalCreated, v776::LegacyTelemetryEventPacket::PortalUsed, v776::LegacyTelemetryEventPacket::MobKilled, v776::LegacyTelemetryEventPacket::CauldronUsed, v776::LegacyTelemetryEventPacket::PlayerDied, v776::LegacyTelemetryEventPacket::BossKilled, v776::LegacyTelemetryEventPacket::SlashCommand, v776::LegacyTelemetryEventPacket::MobBorn, v776::LegacyTelemetryEventPacket::POICauldronUsed, v776::LegacyTelemetryEventPacket::ComposterUsed, v776::LegacyTelemetryEventPacket::BellUsed, v776::LegacyTelemetryEventPacket::ActorDefinition, v776::LegacyTelemetryEventPacket::RaidUpdate, v776::LegacyTelemetryEventPacket::TargetBlockHit, v776::LegacyTelemetryEventPacket::PiglinBarter, v776::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v776::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v776::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v776::LegacyTelemetryEventPacket::ItemUsed, v776::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v776::LegacyTelemetryEventPacket::CodeBuilderScoreboard>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<19>(alt0);
                break;
            }
            case 20: {
                std::variant_alternative_t<20, std::variant<v776::LegacyTelemetryEventPacket::Achievement, v776::LegacyTelemetryEventPacket::Interaction, v776::LegacyTelemetryEventPacket::PortalCreated, v776::LegacyTelemetryEventPacket::PortalUsed, v776::LegacyTelemetryEventPacket::MobKilled, v776::LegacyTelemetryEventPacket::CauldronUsed, v776::LegacyTelemetryEventPacket::PlayerDied, v776::LegacyTelemetryEventPacket::BossKilled, v776::LegacyTelemetryEventPacket::SlashCommand, v776::LegacyTelemetryEventPacket::MobBorn, v776::LegacyTelemetryEventPacket::POICauldronUsed, v776::LegacyTelemetryEventPacket::ComposterUsed, v776::LegacyTelemetryEventPacket::BellUsed, v776::LegacyTelemetryEventPacket::ActorDefinition, v776::LegacyTelemetryEventPacket::RaidUpdate, v776::LegacyTelemetryEventPacket::TargetBlockHit, v776::LegacyTelemetryEventPacket::PiglinBarter, v776::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v776::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v776::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v776::LegacyTelemetryEventPacket::ItemUsed, v776::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v776::LegacyTelemetryEventPacket::ItemUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<20>(alt0);
                break;
            }
            case 21: {
                std::variant_alternative_t<21, std::variant<v776::LegacyTelemetryEventPacket::Achievement, v776::LegacyTelemetryEventPacket::Interaction, v776::LegacyTelemetryEventPacket::PortalCreated, v776::LegacyTelemetryEventPacket::PortalUsed, v776::LegacyTelemetryEventPacket::MobKilled, v776::LegacyTelemetryEventPacket::CauldronUsed, v776::LegacyTelemetryEventPacket::PlayerDied, v776::LegacyTelemetryEventPacket::BossKilled, v776::LegacyTelemetryEventPacket::SlashCommand, v776::LegacyTelemetryEventPacket::MobBorn, v776::LegacyTelemetryEventPacket::POICauldronUsed, v776::LegacyTelemetryEventPacket::ComposterUsed, v776::LegacyTelemetryEventPacket::BellUsed, v776::LegacyTelemetryEventPacket::ActorDefinition, v776::LegacyTelemetryEventPacket::RaidUpdate, v776::LegacyTelemetryEventPacket::TargetBlockHit, v776::LegacyTelemetryEventPacket::PiglinBarter, v776::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v776::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v776::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v776::LegacyTelemetryEventPacket::ItemUsed, v776::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v776::LegacyTelemetryEventPacket::Empty>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<21>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.event_data = var0;
    }
    return out;
}

void Serializer<v800::LegacyTelemetryEventPacket>::serialize(BinaryWriter &stream, const v800::LegacyTelemetryEventPacket &value)
{
    stream.writeVarInt<std::int64_t>(value.player_unique_id);
    stream.writeVarInt<std::int32_t>(value.type);
    stream.write<bool>(value.use_player_id);
    stream.writeVarInt<std::uint32_t>((value.event_data).index());
    switch ((value.event_data).index()) {
        case 0: {
            Serializer<v800::LegacyTelemetryEventPacket::Achievement>::serialize(stream, std::get<0>(value.event_data));
            break;
        }
        case 1: {
            Serializer<v800::LegacyTelemetryEventPacket::Interaction>::serialize(stream, std::get<1>(value.event_data));
            break;
        }
        case 2: {
            Serializer<v800::LegacyTelemetryEventPacket::PortalCreated>::serialize(stream, std::get<2>(value.event_data));
            break;
        }
        case 3: {
            Serializer<v800::LegacyTelemetryEventPacket::PortalUsed>::serialize(stream, std::get<3>(value.event_data));
            break;
        }
        case 4: {
            Serializer<v800::LegacyTelemetryEventPacket::MobKilled>::serialize(stream, std::get<4>(value.event_data));
            break;
        }
        case 5: {
            Serializer<v800::LegacyTelemetryEventPacket::CauldronUsed>::serialize(stream, std::get<5>(value.event_data));
            break;
        }
        case 6: {
            Serializer<v800::LegacyTelemetryEventPacket::PlayerDied>::serialize(stream, std::get<6>(value.event_data));
            break;
        }
        case 7: {
            Serializer<v800::LegacyTelemetryEventPacket::BossKilled>::serialize(stream, std::get<7>(value.event_data));
            break;
        }
        case 8: {
            Serializer<v800::LegacyTelemetryEventPacket::SlashCommand>::serialize(stream, std::get<8>(value.event_data));
            break;
        }
        case 9: {
            Serializer<v800::LegacyTelemetryEventPacket::MobBorn>::serialize(stream, std::get<9>(value.event_data));
            break;
        }
        case 10: {
            Serializer<v800::LegacyTelemetryEventPacket::POICauldronUsed>::serialize(stream, std::get<10>(value.event_data));
            break;
        }
        case 11: {
            Serializer<v800::LegacyTelemetryEventPacket::ComposterUsed>::serialize(stream, std::get<11>(value.event_data));
            break;
        }
        case 12: {
            Serializer<v800::LegacyTelemetryEventPacket::BellUsed>::serialize(stream, std::get<12>(value.event_data));
            break;
        }
        case 13: {
            Serializer<v800::LegacyTelemetryEventPacket::ActorDefinition>::serialize(stream, std::get<13>(value.event_data));
            break;
        }
        case 14: {
            Serializer<v800::LegacyTelemetryEventPacket::RaidUpdate>::serialize(stream, std::get<14>(value.event_data));
            break;
        }
        case 15: {
            Serializer<v800::LegacyTelemetryEventPacket::TargetBlockHit>::serialize(stream, std::get<15>(value.event_data));
            break;
        }
        case 16: {
            Serializer<v800::LegacyTelemetryEventPacket::PiglinBarter>::serialize(stream, std::get<16>(value.event_data));
            break;
        }
        case 17: {
            Serializer<v800::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper>::serialize(stream, std::get<17>(value.event_data));
            break;
        }
        case 18: {
            Serializer<v800::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction>::serialize(stream, std::get<18>(value.event_data));
            break;
        }
        case 19: {
            Serializer<v800::LegacyTelemetryEventPacket::CodeBuilderScoreboard>::serialize(stream, std::get<19>(value.event_data));
            break;
        }
        case 20: {
            Serializer<v800::LegacyTelemetryEventPacket::ItemUsed>::serialize(stream, std::get<20>(value.event_data));
            break;
        }
        case 21: {
            Serializer<v800::LegacyTelemetryEventPacket::Empty>::serialize(stream, std::get<21>(value.event_data));
            break;
        }
    }
}

auto Serializer<v800::LegacyTelemetryEventPacket>::deserialize(BinaryReader &stream) -> std::expected<v800::LegacyTelemetryEventPacket, std::error_code>
{
    v800::LegacyTelemetryEventPacket out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.player_unique_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<v800::LegacyTelemetryEventPacket::Type>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.use_player_id = static_cast<bool>(*v);
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v800::LegacyTelemetryEventPacket::Achievement, v800::LegacyTelemetryEventPacket::Interaction, v800::LegacyTelemetryEventPacket::PortalCreated, v800::LegacyTelemetryEventPacket::PortalUsed, v800::LegacyTelemetryEventPacket::MobKilled, v800::LegacyTelemetryEventPacket::CauldronUsed, v800::LegacyTelemetryEventPacket::PlayerDied, v800::LegacyTelemetryEventPacket::BossKilled, v800::LegacyTelemetryEventPacket::SlashCommand, v800::LegacyTelemetryEventPacket::MobBorn, v800::LegacyTelemetryEventPacket::POICauldronUsed, v800::LegacyTelemetryEventPacket::ComposterUsed, v800::LegacyTelemetryEventPacket::BellUsed, v800::LegacyTelemetryEventPacket::ActorDefinition, v800::LegacyTelemetryEventPacket::RaidUpdate, v800::LegacyTelemetryEventPacket::TargetBlockHit, v800::LegacyTelemetryEventPacket::PiglinBarter, v800::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v800::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v800::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v800::LegacyTelemetryEventPacket::ItemUsed, v800::LegacyTelemetryEventPacket::Empty> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v800::LegacyTelemetryEventPacket::Achievement, v800::LegacyTelemetryEventPacket::Interaction, v800::LegacyTelemetryEventPacket::PortalCreated, v800::LegacyTelemetryEventPacket::PortalUsed, v800::LegacyTelemetryEventPacket::MobKilled, v800::LegacyTelemetryEventPacket::CauldronUsed, v800::LegacyTelemetryEventPacket::PlayerDied, v800::LegacyTelemetryEventPacket::BossKilled, v800::LegacyTelemetryEventPacket::SlashCommand, v800::LegacyTelemetryEventPacket::MobBorn, v800::LegacyTelemetryEventPacket::POICauldronUsed, v800::LegacyTelemetryEventPacket::ComposterUsed, v800::LegacyTelemetryEventPacket::BellUsed, v800::LegacyTelemetryEventPacket::ActorDefinition, v800::LegacyTelemetryEventPacket::RaidUpdate, v800::LegacyTelemetryEventPacket::TargetBlockHit, v800::LegacyTelemetryEventPacket::PiglinBarter, v800::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v800::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v800::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v800::LegacyTelemetryEventPacket::ItemUsed, v800::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v800::LegacyTelemetryEventPacket::Achievement>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v800::LegacyTelemetryEventPacket::Achievement, v800::LegacyTelemetryEventPacket::Interaction, v800::LegacyTelemetryEventPacket::PortalCreated, v800::LegacyTelemetryEventPacket::PortalUsed, v800::LegacyTelemetryEventPacket::MobKilled, v800::LegacyTelemetryEventPacket::CauldronUsed, v800::LegacyTelemetryEventPacket::PlayerDied, v800::LegacyTelemetryEventPacket::BossKilled, v800::LegacyTelemetryEventPacket::SlashCommand, v800::LegacyTelemetryEventPacket::MobBorn, v800::LegacyTelemetryEventPacket::POICauldronUsed, v800::LegacyTelemetryEventPacket::ComposterUsed, v800::LegacyTelemetryEventPacket::BellUsed, v800::LegacyTelemetryEventPacket::ActorDefinition, v800::LegacyTelemetryEventPacket::RaidUpdate, v800::LegacyTelemetryEventPacket::TargetBlockHit, v800::LegacyTelemetryEventPacket::PiglinBarter, v800::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v800::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v800::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v800::LegacyTelemetryEventPacket::ItemUsed, v800::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v800::LegacyTelemetryEventPacket::Interaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<v800::LegacyTelemetryEventPacket::Achievement, v800::LegacyTelemetryEventPacket::Interaction, v800::LegacyTelemetryEventPacket::PortalCreated, v800::LegacyTelemetryEventPacket::PortalUsed, v800::LegacyTelemetryEventPacket::MobKilled, v800::LegacyTelemetryEventPacket::CauldronUsed, v800::LegacyTelemetryEventPacket::PlayerDied, v800::LegacyTelemetryEventPacket::BossKilled, v800::LegacyTelemetryEventPacket::SlashCommand, v800::LegacyTelemetryEventPacket::MobBorn, v800::LegacyTelemetryEventPacket::POICauldronUsed, v800::LegacyTelemetryEventPacket::ComposterUsed, v800::LegacyTelemetryEventPacket::BellUsed, v800::LegacyTelemetryEventPacket::ActorDefinition, v800::LegacyTelemetryEventPacket::RaidUpdate, v800::LegacyTelemetryEventPacket::TargetBlockHit, v800::LegacyTelemetryEventPacket::PiglinBarter, v800::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v800::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v800::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v800::LegacyTelemetryEventPacket::ItemUsed, v800::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v800::LegacyTelemetryEventPacket::PortalCreated>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<v800::LegacyTelemetryEventPacket::Achievement, v800::LegacyTelemetryEventPacket::Interaction, v800::LegacyTelemetryEventPacket::PortalCreated, v800::LegacyTelemetryEventPacket::PortalUsed, v800::LegacyTelemetryEventPacket::MobKilled, v800::LegacyTelemetryEventPacket::CauldronUsed, v800::LegacyTelemetryEventPacket::PlayerDied, v800::LegacyTelemetryEventPacket::BossKilled, v800::LegacyTelemetryEventPacket::SlashCommand, v800::LegacyTelemetryEventPacket::MobBorn, v800::LegacyTelemetryEventPacket::POICauldronUsed, v800::LegacyTelemetryEventPacket::ComposterUsed, v800::LegacyTelemetryEventPacket::BellUsed, v800::LegacyTelemetryEventPacket::ActorDefinition, v800::LegacyTelemetryEventPacket::RaidUpdate, v800::LegacyTelemetryEventPacket::TargetBlockHit, v800::LegacyTelemetryEventPacket::PiglinBarter, v800::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v800::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v800::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v800::LegacyTelemetryEventPacket::ItemUsed, v800::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v800::LegacyTelemetryEventPacket::PortalUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            case 4: {
                std::variant_alternative_t<4, std::variant<v800::LegacyTelemetryEventPacket::Achievement, v800::LegacyTelemetryEventPacket::Interaction, v800::LegacyTelemetryEventPacket::PortalCreated, v800::LegacyTelemetryEventPacket::PortalUsed, v800::LegacyTelemetryEventPacket::MobKilled, v800::LegacyTelemetryEventPacket::CauldronUsed, v800::LegacyTelemetryEventPacket::PlayerDied, v800::LegacyTelemetryEventPacket::BossKilled, v800::LegacyTelemetryEventPacket::SlashCommand, v800::LegacyTelemetryEventPacket::MobBorn, v800::LegacyTelemetryEventPacket::POICauldronUsed, v800::LegacyTelemetryEventPacket::ComposterUsed, v800::LegacyTelemetryEventPacket::BellUsed, v800::LegacyTelemetryEventPacket::ActorDefinition, v800::LegacyTelemetryEventPacket::RaidUpdate, v800::LegacyTelemetryEventPacket::TargetBlockHit, v800::LegacyTelemetryEventPacket::PiglinBarter, v800::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v800::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v800::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v800::LegacyTelemetryEventPacket::ItemUsed, v800::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v800::LegacyTelemetryEventPacket::MobKilled>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<4>(alt0);
                break;
            }
            case 5: {
                std::variant_alternative_t<5, std::variant<v800::LegacyTelemetryEventPacket::Achievement, v800::LegacyTelemetryEventPacket::Interaction, v800::LegacyTelemetryEventPacket::PortalCreated, v800::LegacyTelemetryEventPacket::PortalUsed, v800::LegacyTelemetryEventPacket::MobKilled, v800::LegacyTelemetryEventPacket::CauldronUsed, v800::LegacyTelemetryEventPacket::PlayerDied, v800::LegacyTelemetryEventPacket::BossKilled, v800::LegacyTelemetryEventPacket::SlashCommand, v800::LegacyTelemetryEventPacket::MobBorn, v800::LegacyTelemetryEventPacket::POICauldronUsed, v800::LegacyTelemetryEventPacket::ComposterUsed, v800::LegacyTelemetryEventPacket::BellUsed, v800::LegacyTelemetryEventPacket::ActorDefinition, v800::LegacyTelemetryEventPacket::RaidUpdate, v800::LegacyTelemetryEventPacket::TargetBlockHit, v800::LegacyTelemetryEventPacket::PiglinBarter, v800::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v800::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v800::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v800::LegacyTelemetryEventPacket::ItemUsed, v800::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v800::LegacyTelemetryEventPacket::CauldronUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<5>(alt0);
                break;
            }
            case 6: {
                std::variant_alternative_t<6, std::variant<v800::LegacyTelemetryEventPacket::Achievement, v800::LegacyTelemetryEventPacket::Interaction, v800::LegacyTelemetryEventPacket::PortalCreated, v800::LegacyTelemetryEventPacket::PortalUsed, v800::LegacyTelemetryEventPacket::MobKilled, v800::LegacyTelemetryEventPacket::CauldronUsed, v800::LegacyTelemetryEventPacket::PlayerDied, v800::LegacyTelemetryEventPacket::BossKilled, v800::LegacyTelemetryEventPacket::SlashCommand, v800::LegacyTelemetryEventPacket::MobBorn, v800::LegacyTelemetryEventPacket::POICauldronUsed, v800::LegacyTelemetryEventPacket::ComposterUsed, v800::LegacyTelemetryEventPacket::BellUsed, v800::LegacyTelemetryEventPacket::ActorDefinition, v800::LegacyTelemetryEventPacket::RaidUpdate, v800::LegacyTelemetryEventPacket::TargetBlockHit, v800::LegacyTelemetryEventPacket::PiglinBarter, v800::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v800::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v800::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v800::LegacyTelemetryEventPacket::ItemUsed, v800::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v800::LegacyTelemetryEventPacket::PlayerDied>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<6>(alt0);
                break;
            }
            case 7: {
                std::variant_alternative_t<7, std::variant<v800::LegacyTelemetryEventPacket::Achievement, v800::LegacyTelemetryEventPacket::Interaction, v800::LegacyTelemetryEventPacket::PortalCreated, v800::LegacyTelemetryEventPacket::PortalUsed, v800::LegacyTelemetryEventPacket::MobKilled, v800::LegacyTelemetryEventPacket::CauldronUsed, v800::LegacyTelemetryEventPacket::PlayerDied, v800::LegacyTelemetryEventPacket::BossKilled, v800::LegacyTelemetryEventPacket::SlashCommand, v800::LegacyTelemetryEventPacket::MobBorn, v800::LegacyTelemetryEventPacket::POICauldronUsed, v800::LegacyTelemetryEventPacket::ComposterUsed, v800::LegacyTelemetryEventPacket::BellUsed, v800::LegacyTelemetryEventPacket::ActorDefinition, v800::LegacyTelemetryEventPacket::RaidUpdate, v800::LegacyTelemetryEventPacket::TargetBlockHit, v800::LegacyTelemetryEventPacket::PiglinBarter, v800::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v800::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v800::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v800::LegacyTelemetryEventPacket::ItemUsed, v800::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v800::LegacyTelemetryEventPacket::BossKilled>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<7>(alt0);
                break;
            }
            case 8: {
                std::variant_alternative_t<8, std::variant<v800::LegacyTelemetryEventPacket::Achievement, v800::LegacyTelemetryEventPacket::Interaction, v800::LegacyTelemetryEventPacket::PortalCreated, v800::LegacyTelemetryEventPacket::PortalUsed, v800::LegacyTelemetryEventPacket::MobKilled, v800::LegacyTelemetryEventPacket::CauldronUsed, v800::LegacyTelemetryEventPacket::PlayerDied, v800::LegacyTelemetryEventPacket::BossKilled, v800::LegacyTelemetryEventPacket::SlashCommand, v800::LegacyTelemetryEventPacket::MobBorn, v800::LegacyTelemetryEventPacket::POICauldronUsed, v800::LegacyTelemetryEventPacket::ComposterUsed, v800::LegacyTelemetryEventPacket::BellUsed, v800::LegacyTelemetryEventPacket::ActorDefinition, v800::LegacyTelemetryEventPacket::RaidUpdate, v800::LegacyTelemetryEventPacket::TargetBlockHit, v800::LegacyTelemetryEventPacket::PiglinBarter, v800::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v800::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v800::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v800::LegacyTelemetryEventPacket::ItemUsed, v800::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v800::LegacyTelemetryEventPacket::SlashCommand>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<8>(alt0);
                break;
            }
            case 9: {
                std::variant_alternative_t<9, std::variant<v800::LegacyTelemetryEventPacket::Achievement, v800::LegacyTelemetryEventPacket::Interaction, v800::LegacyTelemetryEventPacket::PortalCreated, v800::LegacyTelemetryEventPacket::PortalUsed, v800::LegacyTelemetryEventPacket::MobKilled, v800::LegacyTelemetryEventPacket::CauldronUsed, v800::LegacyTelemetryEventPacket::PlayerDied, v800::LegacyTelemetryEventPacket::BossKilled, v800::LegacyTelemetryEventPacket::SlashCommand, v800::LegacyTelemetryEventPacket::MobBorn, v800::LegacyTelemetryEventPacket::POICauldronUsed, v800::LegacyTelemetryEventPacket::ComposterUsed, v800::LegacyTelemetryEventPacket::BellUsed, v800::LegacyTelemetryEventPacket::ActorDefinition, v800::LegacyTelemetryEventPacket::RaidUpdate, v800::LegacyTelemetryEventPacket::TargetBlockHit, v800::LegacyTelemetryEventPacket::PiglinBarter, v800::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v800::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v800::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v800::LegacyTelemetryEventPacket::ItemUsed, v800::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v800::LegacyTelemetryEventPacket::MobBorn>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<9>(alt0);
                break;
            }
            case 10: {
                std::variant_alternative_t<10, std::variant<v800::LegacyTelemetryEventPacket::Achievement, v800::LegacyTelemetryEventPacket::Interaction, v800::LegacyTelemetryEventPacket::PortalCreated, v800::LegacyTelemetryEventPacket::PortalUsed, v800::LegacyTelemetryEventPacket::MobKilled, v800::LegacyTelemetryEventPacket::CauldronUsed, v800::LegacyTelemetryEventPacket::PlayerDied, v800::LegacyTelemetryEventPacket::BossKilled, v800::LegacyTelemetryEventPacket::SlashCommand, v800::LegacyTelemetryEventPacket::MobBorn, v800::LegacyTelemetryEventPacket::POICauldronUsed, v800::LegacyTelemetryEventPacket::ComposterUsed, v800::LegacyTelemetryEventPacket::BellUsed, v800::LegacyTelemetryEventPacket::ActorDefinition, v800::LegacyTelemetryEventPacket::RaidUpdate, v800::LegacyTelemetryEventPacket::TargetBlockHit, v800::LegacyTelemetryEventPacket::PiglinBarter, v800::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v800::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v800::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v800::LegacyTelemetryEventPacket::ItemUsed, v800::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v800::LegacyTelemetryEventPacket::POICauldronUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<10>(alt0);
                break;
            }
            case 11: {
                std::variant_alternative_t<11, std::variant<v800::LegacyTelemetryEventPacket::Achievement, v800::LegacyTelemetryEventPacket::Interaction, v800::LegacyTelemetryEventPacket::PortalCreated, v800::LegacyTelemetryEventPacket::PortalUsed, v800::LegacyTelemetryEventPacket::MobKilled, v800::LegacyTelemetryEventPacket::CauldronUsed, v800::LegacyTelemetryEventPacket::PlayerDied, v800::LegacyTelemetryEventPacket::BossKilled, v800::LegacyTelemetryEventPacket::SlashCommand, v800::LegacyTelemetryEventPacket::MobBorn, v800::LegacyTelemetryEventPacket::POICauldronUsed, v800::LegacyTelemetryEventPacket::ComposterUsed, v800::LegacyTelemetryEventPacket::BellUsed, v800::LegacyTelemetryEventPacket::ActorDefinition, v800::LegacyTelemetryEventPacket::RaidUpdate, v800::LegacyTelemetryEventPacket::TargetBlockHit, v800::LegacyTelemetryEventPacket::PiglinBarter, v800::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v800::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v800::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v800::LegacyTelemetryEventPacket::ItemUsed, v800::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v800::LegacyTelemetryEventPacket::ComposterUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<11>(alt0);
                break;
            }
            case 12: {
                std::variant_alternative_t<12, std::variant<v800::LegacyTelemetryEventPacket::Achievement, v800::LegacyTelemetryEventPacket::Interaction, v800::LegacyTelemetryEventPacket::PortalCreated, v800::LegacyTelemetryEventPacket::PortalUsed, v800::LegacyTelemetryEventPacket::MobKilled, v800::LegacyTelemetryEventPacket::CauldronUsed, v800::LegacyTelemetryEventPacket::PlayerDied, v800::LegacyTelemetryEventPacket::BossKilled, v800::LegacyTelemetryEventPacket::SlashCommand, v800::LegacyTelemetryEventPacket::MobBorn, v800::LegacyTelemetryEventPacket::POICauldronUsed, v800::LegacyTelemetryEventPacket::ComposterUsed, v800::LegacyTelemetryEventPacket::BellUsed, v800::LegacyTelemetryEventPacket::ActorDefinition, v800::LegacyTelemetryEventPacket::RaidUpdate, v800::LegacyTelemetryEventPacket::TargetBlockHit, v800::LegacyTelemetryEventPacket::PiglinBarter, v800::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v800::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v800::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v800::LegacyTelemetryEventPacket::ItemUsed, v800::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v800::LegacyTelemetryEventPacket::BellUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<12>(alt0);
                break;
            }
            case 13: {
                std::variant_alternative_t<13, std::variant<v800::LegacyTelemetryEventPacket::Achievement, v800::LegacyTelemetryEventPacket::Interaction, v800::LegacyTelemetryEventPacket::PortalCreated, v800::LegacyTelemetryEventPacket::PortalUsed, v800::LegacyTelemetryEventPacket::MobKilled, v800::LegacyTelemetryEventPacket::CauldronUsed, v800::LegacyTelemetryEventPacket::PlayerDied, v800::LegacyTelemetryEventPacket::BossKilled, v800::LegacyTelemetryEventPacket::SlashCommand, v800::LegacyTelemetryEventPacket::MobBorn, v800::LegacyTelemetryEventPacket::POICauldronUsed, v800::LegacyTelemetryEventPacket::ComposterUsed, v800::LegacyTelemetryEventPacket::BellUsed, v800::LegacyTelemetryEventPacket::ActorDefinition, v800::LegacyTelemetryEventPacket::RaidUpdate, v800::LegacyTelemetryEventPacket::TargetBlockHit, v800::LegacyTelemetryEventPacket::PiglinBarter, v800::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v800::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v800::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v800::LegacyTelemetryEventPacket::ItemUsed, v800::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v800::LegacyTelemetryEventPacket::ActorDefinition>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<13>(alt0);
                break;
            }
            case 14: {
                std::variant_alternative_t<14, std::variant<v800::LegacyTelemetryEventPacket::Achievement, v800::LegacyTelemetryEventPacket::Interaction, v800::LegacyTelemetryEventPacket::PortalCreated, v800::LegacyTelemetryEventPacket::PortalUsed, v800::LegacyTelemetryEventPacket::MobKilled, v800::LegacyTelemetryEventPacket::CauldronUsed, v800::LegacyTelemetryEventPacket::PlayerDied, v800::LegacyTelemetryEventPacket::BossKilled, v800::LegacyTelemetryEventPacket::SlashCommand, v800::LegacyTelemetryEventPacket::MobBorn, v800::LegacyTelemetryEventPacket::POICauldronUsed, v800::LegacyTelemetryEventPacket::ComposterUsed, v800::LegacyTelemetryEventPacket::BellUsed, v800::LegacyTelemetryEventPacket::ActorDefinition, v800::LegacyTelemetryEventPacket::RaidUpdate, v800::LegacyTelemetryEventPacket::TargetBlockHit, v800::LegacyTelemetryEventPacket::PiglinBarter, v800::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v800::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v800::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v800::LegacyTelemetryEventPacket::ItemUsed, v800::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v800::LegacyTelemetryEventPacket::RaidUpdate>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<14>(alt0);
                break;
            }
            case 15: {
                std::variant_alternative_t<15, std::variant<v800::LegacyTelemetryEventPacket::Achievement, v800::LegacyTelemetryEventPacket::Interaction, v800::LegacyTelemetryEventPacket::PortalCreated, v800::LegacyTelemetryEventPacket::PortalUsed, v800::LegacyTelemetryEventPacket::MobKilled, v800::LegacyTelemetryEventPacket::CauldronUsed, v800::LegacyTelemetryEventPacket::PlayerDied, v800::LegacyTelemetryEventPacket::BossKilled, v800::LegacyTelemetryEventPacket::SlashCommand, v800::LegacyTelemetryEventPacket::MobBorn, v800::LegacyTelemetryEventPacket::POICauldronUsed, v800::LegacyTelemetryEventPacket::ComposterUsed, v800::LegacyTelemetryEventPacket::BellUsed, v800::LegacyTelemetryEventPacket::ActorDefinition, v800::LegacyTelemetryEventPacket::RaidUpdate, v800::LegacyTelemetryEventPacket::TargetBlockHit, v800::LegacyTelemetryEventPacket::PiglinBarter, v800::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v800::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v800::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v800::LegacyTelemetryEventPacket::ItemUsed, v800::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v800::LegacyTelemetryEventPacket::TargetBlockHit>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<15>(alt0);
                break;
            }
            case 16: {
                std::variant_alternative_t<16, std::variant<v800::LegacyTelemetryEventPacket::Achievement, v800::LegacyTelemetryEventPacket::Interaction, v800::LegacyTelemetryEventPacket::PortalCreated, v800::LegacyTelemetryEventPacket::PortalUsed, v800::LegacyTelemetryEventPacket::MobKilled, v800::LegacyTelemetryEventPacket::CauldronUsed, v800::LegacyTelemetryEventPacket::PlayerDied, v800::LegacyTelemetryEventPacket::BossKilled, v800::LegacyTelemetryEventPacket::SlashCommand, v800::LegacyTelemetryEventPacket::MobBorn, v800::LegacyTelemetryEventPacket::POICauldronUsed, v800::LegacyTelemetryEventPacket::ComposterUsed, v800::LegacyTelemetryEventPacket::BellUsed, v800::LegacyTelemetryEventPacket::ActorDefinition, v800::LegacyTelemetryEventPacket::RaidUpdate, v800::LegacyTelemetryEventPacket::TargetBlockHit, v800::LegacyTelemetryEventPacket::PiglinBarter, v800::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v800::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v800::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v800::LegacyTelemetryEventPacket::ItemUsed, v800::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v800::LegacyTelemetryEventPacket::PiglinBarter>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<16>(alt0);
                break;
            }
            case 17: {
                std::variant_alternative_t<17, std::variant<v800::LegacyTelemetryEventPacket::Achievement, v800::LegacyTelemetryEventPacket::Interaction, v800::LegacyTelemetryEventPacket::PortalCreated, v800::LegacyTelemetryEventPacket::PortalUsed, v800::LegacyTelemetryEventPacket::MobKilled, v800::LegacyTelemetryEventPacket::CauldronUsed, v800::LegacyTelemetryEventPacket::PlayerDied, v800::LegacyTelemetryEventPacket::BossKilled, v800::LegacyTelemetryEventPacket::SlashCommand, v800::LegacyTelemetryEventPacket::MobBorn, v800::LegacyTelemetryEventPacket::POICauldronUsed, v800::LegacyTelemetryEventPacket::ComposterUsed, v800::LegacyTelemetryEventPacket::BellUsed, v800::LegacyTelemetryEventPacket::ActorDefinition, v800::LegacyTelemetryEventPacket::RaidUpdate, v800::LegacyTelemetryEventPacket::TargetBlockHit, v800::LegacyTelemetryEventPacket::PiglinBarter, v800::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v800::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v800::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v800::LegacyTelemetryEventPacket::ItemUsed, v800::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v800::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<17>(alt0);
                break;
            }
            case 18: {
                std::variant_alternative_t<18, std::variant<v800::LegacyTelemetryEventPacket::Achievement, v800::LegacyTelemetryEventPacket::Interaction, v800::LegacyTelemetryEventPacket::PortalCreated, v800::LegacyTelemetryEventPacket::PortalUsed, v800::LegacyTelemetryEventPacket::MobKilled, v800::LegacyTelemetryEventPacket::CauldronUsed, v800::LegacyTelemetryEventPacket::PlayerDied, v800::LegacyTelemetryEventPacket::BossKilled, v800::LegacyTelemetryEventPacket::SlashCommand, v800::LegacyTelemetryEventPacket::MobBorn, v800::LegacyTelemetryEventPacket::POICauldronUsed, v800::LegacyTelemetryEventPacket::ComposterUsed, v800::LegacyTelemetryEventPacket::BellUsed, v800::LegacyTelemetryEventPacket::ActorDefinition, v800::LegacyTelemetryEventPacket::RaidUpdate, v800::LegacyTelemetryEventPacket::TargetBlockHit, v800::LegacyTelemetryEventPacket::PiglinBarter, v800::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v800::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v800::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v800::LegacyTelemetryEventPacket::ItemUsed, v800::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v800::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<18>(alt0);
                break;
            }
            case 19: {
                std::variant_alternative_t<19, std::variant<v800::LegacyTelemetryEventPacket::Achievement, v800::LegacyTelemetryEventPacket::Interaction, v800::LegacyTelemetryEventPacket::PortalCreated, v800::LegacyTelemetryEventPacket::PortalUsed, v800::LegacyTelemetryEventPacket::MobKilled, v800::LegacyTelemetryEventPacket::CauldronUsed, v800::LegacyTelemetryEventPacket::PlayerDied, v800::LegacyTelemetryEventPacket::BossKilled, v800::LegacyTelemetryEventPacket::SlashCommand, v800::LegacyTelemetryEventPacket::MobBorn, v800::LegacyTelemetryEventPacket::POICauldronUsed, v800::LegacyTelemetryEventPacket::ComposterUsed, v800::LegacyTelemetryEventPacket::BellUsed, v800::LegacyTelemetryEventPacket::ActorDefinition, v800::LegacyTelemetryEventPacket::RaidUpdate, v800::LegacyTelemetryEventPacket::TargetBlockHit, v800::LegacyTelemetryEventPacket::PiglinBarter, v800::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v800::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v800::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v800::LegacyTelemetryEventPacket::ItemUsed, v800::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v800::LegacyTelemetryEventPacket::CodeBuilderScoreboard>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<19>(alt0);
                break;
            }
            case 20: {
                std::variant_alternative_t<20, std::variant<v800::LegacyTelemetryEventPacket::Achievement, v800::LegacyTelemetryEventPacket::Interaction, v800::LegacyTelemetryEventPacket::PortalCreated, v800::LegacyTelemetryEventPacket::PortalUsed, v800::LegacyTelemetryEventPacket::MobKilled, v800::LegacyTelemetryEventPacket::CauldronUsed, v800::LegacyTelemetryEventPacket::PlayerDied, v800::LegacyTelemetryEventPacket::BossKilled, v800::LegacyTelemetryEventPacket::SlashCommand, v800::LegacyTelemetryEventPacket::MobBorn, v800::LegacyTelemetryEventPacket::POICauldronUsed, v800::LegacyTelemetryEventPacket::ComposterUsed, v800::LegacyTelemetryEventPacket::BellUsed, v800::LegacyTelemetryEventPacket::ActorDefinition, v800::LegacyTelemetryEventPacket::RaidUpdate, v800::LegacyTelemetryEventPacket::TargetBlockHit, v800::LegacyTelemetryEventPacket::PiglinBarter, v800::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v800::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v800::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v800::LegacyTelemetryEventPacket::ItemUsed, v800::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v800::LegacyTelemetryEventPacket::ItemUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<20>(alt0);
                break;
            }
            case 21: {
                std::variant_alternative_t<21, std::variant<v800::LegacyTelemetryEventPacket::Achievement, v800::LegacyTelemetryEventPacket::Interaction, v800::LegacyTelemetryEventPacket::PortalCreated, v800::LegacyTelemetryEventPacket::PortalUsed, v800::LegacyTelemetryEventPacket::MobKilled, v800::LegacyTelemetryEventPacket::CauldronUsed, v800::LegacyTelemetryEventPacket::PlayerDied, v800::LegacyTelemetryEventPacket::BossKilled, v800::LegacyTelemetryEventPacket::SlashCommand, v800::LegacyTelemetryEventPacket::MobBorn, v800::LegacyTelemetryEventPacket::POICauldronUsed, v800::LegacyTelemetryEventPacket::ComposterUsed, v800::LegacyTelemetryEventPacket::BellUsed, v800::LegacyTelemetryEventPacket::ActorDefinition, v800::LegacyTelemetryEventPacket::RaidUpdate, v800::LegacyTelemetryEventPacket::TargetBlockHit, v800::LegacyTelemetryEventPacket::PiglinBarter, v800::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v800::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v800::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v800::LegacyTelemetryEventPacket::ItemUsed, v800::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v800::LegacyTelemetryEventPacket::Empty>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<21>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.event_data = var0;
    }
    return out;
}

void Serializer<v818::LegacyTelemetryEventPacket>::serialize(BinaryWriter &stream, const v818::LegacyTelemetryEventPacket &value)
{
    stream.writeVarInt<std::int64_t>(value.player_unique_id);
    stream.writeVarInt<std::int32_t>(value.type);
    stream.write<bool>(value.use_player_id);
    stream.writeVarInt<std::uint32_t>((value.event_data).index());
    switch ((value.event_data).index()) {
        case 0: {
            Serializer<v818::LegacyTelemetryEventPacket::Achievement>::serialize(stream, std::get<0>(value.event_data));
            break;
        }
        case 1: {
            Serializer<v818::LegacyTelemetryEventPacket::Interaction>::serialize(stream, std::get<1>(value.event_data));
            break;
        }
        case 2: {
            Serializer<v818::LegacyTelemetryEventPacket::PortalCreated>::serialize(stream, std::get<2>(value.event_data));
            break;
        }
        case 3: {
            Serializer<v818::LegacyTelemetryEventPacket::PortalUsed>::serialize(stream, std::get<3>(value.event_data));
            break;
        }
        case 4: {
            Serializer<v818::LegacyTelemetryEventPacket::MobKilled>::serialize(stream, std::get<4>(value.event_data));
            break;
        }
        case 5: {
            Serializer<v818::LegacyTelemetryEventPacket::CauldronUsed>::serialize(stream, std::get<5>(value.event_data));
            break;
        }
        case 6: {
            Serializer<v818::LegacyTelemetryEventPacket::PlayerDied>::serialize(stream, std::get<6>(value.event_data));
            break;
        }
        case 7: {
            Serializer<v818::LegacyTelemetryEventPacket::BossKilled>::serialize(stream, std::get<7>(value.event_data));
            break;
        }
        case 8: {
            Serializer<v818::LegacyTelemetryEventPacket::SlashCommand>::serialize(stream, std::get<8>(value.event_data));
            break;
        }
        case 9: {
            Serializer<v818::LegacyTelemetryEventPacket::MobBorn>::serialize(stream, std::get<9>(value.event_data));
            break;
        }
        case 10: {
            Serializer<v818::LegacyTelemetryEventPacket::POICauldronUsed>::serialize(stream, std::get<10>(value.event_data));
            break;
        }
        case 11: {
            Serializer<v818::LegacyTelemetryEventPacket::ComposterUsed>::serialize(stream, std::get<11>(value.event_data));
            break;
        }
        case 12: {
            Serializer<v818::LegacyTelemetryEventPacket::BellUsed>::serialize(stream, std::get<12>(value.event_data));
            break;
        }
        case 13: {
            Serializer<v818::LegacyTelemetryEventPacket::ActorDefinition>::serialize(stream, std::get<13>(value.event_data));
            break;
        }
        case 14: {
            Serializer<v818::LegacyTelemetryEventPacket::RaidUpdate>::serialize(stream, std::get<14>(value.event_data));
            break;
        }
        case 15: {
            Serializer<v818::LegacyTelemetryEventPacket::TargetBlockHit>::serialize(stream, std::get<15>(value.event_data));
            break;
        }
        case 16: {
            Serializer<v818::LegacyTelemetryEventPacket::PiglinBarter>::serialize(stream, std::get<16>(value.event_data));
            break;
        }
        case 17: {
            Serializer<v818::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper>::serialize(stream, std::get<17>(value.event_data));
            break;
        }
        case 18: {
            Serializer<v818::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction>::serialize(stream, std::get<18>(value.event_data));
            break;
        }
        case 19: {
            Serializer<v818::LegacyTelemetryEventPacket::CodeBuilderScoreboard>::serialize(stream, std::get<19>(value.event_data));
            break;
        }
        case 20: {
            Serializer<v818::LegacyTelemetryEventPacket::ItemUsed>::serialize(stream, std::get<20>(value.event_data));
            break;
        }
        case 21: {
            Serializer<v818::LegacyTelemetryEventPacket::Empty>::serialize(stream, std::get<21>(value.event_data));
            break;
        }
    }
}

auto Serializer<v818::LegacyTelemetryEventPacket>::deserialize(BinaryReader &stream) -> std::expected<v818::LegacyTelemetryEventPacket, std::error_code>
{
    v818::LegacyTelemetryEventPacket out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.player_unique_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<v818::LegacyTelemetryEventPacket::Type>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.use_player_id = static_cast<bool>(*v);
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v818::LegacyTelemetryEventPacket::Achievement, v818::LegacyTelemetryEventPacket::Interaction, v818::LegacyTelemetryEventPacket::PortalCreated, v818::LegacyTelemetryEventPacket::PortalUsed, v818::LegacyTelemetryEventPacket::MobKilled, v818::LegacyTelemetryEventPacket::CauldronUsed, v818::LegacyTelemetryEventPacket::PlayerDied, v818::LegacyTelemetryEventPacket::BossKilled, v818::LegacyTelemetryEventPacket::SlashCommand, v818::LegacyTelemetryEventPacket::MobBorn, v818::LegacyTelemetryEventPacket::POICauldronUsed, v818::LegacyTelemetryEventPacket::ComposterUsed, v818::LegacyTelemetryEventPacket::BellUsed, v818::LegacyTelemetryEventPacket::ActorDefinition, v818::LegacyTelemetryEventPacket::RaidUpdate, v818::LegacyTelemetryEventPacket::TargetBlockHit, v818::LegacyTelemetryEventPacket::PiglinBarter, v818::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v818::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v818::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v818::LegacyTelemetryEventPacket::ItemUsed, v818::LegacyTelemetryEventPacket::Empty> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v818::LegacyTelemetryEventPacket::Achievement, v818::LegacyTelemetryEventPacket::Interaction, v818::LegacyTelemetryEventPacket::PortalCreated, v818::LegacyTelemetryEventPacket::PortalUsed, v818::LegacyTelemetryEventPacket::MobKilled, v818::LegacyTelemetryEventPacket::CauldronUsed, v818::LegacyTelemetryEventPacket::PlayerDied, v818::LegacyTelemetryEventPacket::BossKilled, v818::LegacyTelemetryEventPacket::SlashCommand, v818::LegacyTelemetryEventPacket::MobBorn, v818::LegacyTelemetryEventPacket::POICauldronUsed, v818::LegacyTelemetryEventPacket::ComposterUsed, v818::LegacyTelemetryEventPacket::BellUsed, v818::LegacyTelemetryEventPacket::ActorDefinition, v818::LegacyTelemetryEventPacket::RaidUpdate, v818::LegacyTelemetryEventPacket::TargetBlockHit, v818::LegacyTelemetryEventPacket::PiglinBarter, v818::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v818::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v818::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v818::LegacyTelemetryEventPacket::ItemUsed, v818::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v818::LegacyTelemetryEventPacket::Achievement>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v818::LegacyTelemetryEventPacket::Achievement, v818::LegacyTelemetryEventPacket::Interaction, v818::LegacyTelemetryEventPacket::PortalCreated, v818::LegacyTelemetryEventPacket::PortalUsed, v818::LegacyTelemetryEventPacket::MobKilled, v818::LegacyTelemetryEventPacket::CauldronUsed, v818::LegacyTelemetryEventPacket::PlayerDied, v818::LegacyTelemetryEventPacket::BossKilled, v818::LegacyTelemetryEventPacket::SlashCommand, v818::LegacyTelemetryEventPacket::MobBorn, v818::LegacyTelemetryEventPacket::POICauldronUsed, v818::LegacyTelemetryEventPacket::ComposterUsed, v818::LegacyTelemetryEventPacket::BellUsed, v818::LegacyTelemetryEventPacket::ActorDefinition, v818::LegacyTelemetryEventPacket::RaidUpdate, v818::LegacyTelemetryEventPacket::TargetBlockHit, v818::LegacyTelemetryEventPacket::PiglinBarter, v818::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v818::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v818::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v818::LegacyTelemetryEventPacket::ItemUsed, v818::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v818::LegacyTelemetryEventPacket::Interaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<v818::LegacyTelemetryEventPacket::Achievement, v818::LegacyTelemetryEventPacket::Interaction, v818::LegacyTelemetryEventPacket::PortalCreated, v818::LegacyTelemetryEventPacket::PortalUsed, v818::LegacyTelemetryEventPacket::MobKilled, v818::LegacyTelemetryEventPacket::CauldronUsed, v818::LegacyTelemetryEventPacket::PlayerDied, v818::LegacyTelemetryEventPacket::BossKilled, v818::LegacyTelemetryEventPacket::SlashCommand, v818::LegacyTelemetryEventPacket::MobBorn, v818::LegacyTelemetryEventPacket::POICauldronUsed, v818::LegacyTelemetryEventPacket::ComposterUsed, v818::LegacyTelemetryEventPacket::BellUsed, v818::LegacyTelemetryEventPacket::ActorDefinition, v818::LegacyTelemetryEventPacket::RaidUpdate, v818::LegacyTelemetryEventPacket::TargetBlockHit, v818::LegacyTelemetryEventPacket::PiglinBarter, v818::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v818::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v818::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v818::LegacyTelemetryEventPacket::ItemUsed, v818::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v818::LegacyTelemetryEventPacket::PortalCreated>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<v818::LegacyTelemetryEventPacket::Achievement, v818::LegacyTelemetryEventPacket::Interaction, v818::LegacyTelemetryEventPacket::PortalCreated, v818::LegacyTelemetryEventPacket::PortalUsed, v818::LegacyTelemetryEventPacket::MobKilled, v818::LegacyTelemetryEventPacket::CauldronUsed, v818::LegacyTelemetryEventPacket::PlayerDied, v818::LegacyTelemetryEventPacket::BossKilled, v818::LegacyTelemetryEventPacket::SlashCommand, v818::LegacyTelemetryEventPacket::MobBorn, v818::LegacyTelemetryEventPacket::POICauldronUsed, v818::LegacyTelemetryEventPacket::ComposterUsed, v818::LegacyTelemetryEventPacket::BellUsed, v818::LegacyTelemetryEventPacket::ActorDefinition, v818::LegacyTelemetryEventPacket::RaidUpdate, v818::LegacyTelemetryEventPacket::TargetBlockHit, v818::LegacyTelemetryEventPacket::PiglinBarter, v818::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v818::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v818::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v818::LegacyTelemetryEventPacket::ItemUsed, v818::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v818::LegacyTelemetryEventPacket::PortalUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            case 4: {
                std::variant_alternative_t<4, std::variant<v818::LegacyTelemetryEventPacket::Achievement, v818::LegacyTelemetryEventPacket::Interaction, v818::LegacyTelemetryEventPacket::PortalCreated, v818::LegacyTelemetryEventPacket::PortalUsed, v818::LegacyTelemetryEventPacket::MobKilled, v818::LegacyTelemetryEventPacket::CauldronUsed, v818::LegacyTelemetryEventPacket::PlayerDied, v818::LegacyTelemetryEventPacket::BossKilled, v818::LegacyTelemetryEventPacket::SlashCommand, v818::LegacyTelemetryEventPacket::MobBorn, v818::LegacyTelemetryEventPacket::POICauldronUsed, v818::LegacyTelemetryEventPacket::ComposterUsed, v818::LegacyTelemetryEventPacket::BellUsed, v818::LegacyTelemetryEventPacket::ActorDefinition, v818::LegacyTelemetryEventPacket::RaidUpdate, v818::LegacyTelemetryEventPacket::TargetBlockHit, v818::LegacyTelemetryEventPacket::PiglinBarter, v818::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v818::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v818::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v818::LegacyTelemetryEventPacket::ItemUsed, v818::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v818::LegacyTelemetryEventPacket::MobKilled>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<4>(alt0);
                break;
            }
            case 5: {
                std::variant_alternative_t<5, std::variant<v818::LegacyTelemetryEventPacket::Achievement, v818::LegacyTelemetryEventPacket::Interaction, v818::LegacyTelemetryEventPacket::PortalCreated, v818::LegacyTelemetryEventPacket::PortalUsed, v818::LegacyTelemetryEventPacket::MobKilled, v818::LegacyTelemetryEventPacket::CauldronUsed, v818::LegacyTelemetryEventPacket::PlayerDied, v818::LegacyTelemetryEventPacket::BossKilled, v818::LegacyTelemetryEventPacket::SlashCommand, v818::LegacyTelemetryEventPacket::MobBorn, v818::LegacyTelemetryEventPacket::POICauldronUsed, v818::LegacyTelemetryEventPacket::ComposterUsed, v818::LegacyTelemetryEventPacket::BellUsed, v818::LegacyTelemetryEventPacket::ActorDefinition, v818::LegacyTelemetryEventPacket::RaidUpdate, v818::LegacyTelemetryEventPacket::TargetBlockHit, v818::LegacyTelemetryEventPacket::PiglinBarter, v818::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v818::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v818::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v818::LegacyTelemetryEventPacket::ItemUsed, v818::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v818::LegacyTelemetryEventPacket::CauldronUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<5>(alt0);
                break;
            }
            case 6: {
                std::variant_alternative_t<6, std::variant<v818::LegacyTelemetryEventPacket::Achievement, v818::LegacyTelemetryEventPacket::Interaction, v818::LegacyTelemetryEventPacket::PortalCreated, v818::LegacyTelemetryEventPacket::PortalUsed, v818::LegacyTelemetryEventPacket::MobKilled, v818::LegacyTelemetryEventPacket::CauldronUsed, v818::LegacyTelemetryEventPacket::PlayerDied, v818::LegacyTelemetryEventPacket::BossKilled, v818::LegacyTelemetryEventPacket::SlashCommand, v818::LegacyTelemetryEventPacket::MobBorn, v818::LegacyTelemetryEventPacket::POICauldronUsed, v818::LegacyTelemetryEventPacket::ComposterUsed, v818::LegacyTelemetryEventPacket::BellUsed, v818::LegacyTelemetryEventPacket::ActorDefinition, v818::LegacyTelemetryEventPacket::RaidUpdate, v818::LegacyTelemetryEventPacket::TargetBlockHit, v818::LegacyTelemetryEventPacket::PiglinBarter, v818::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v818::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v818::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v818::LegacyTelemetryEventPacket::ItemUsed, v818::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v818::LegacyTelemetryEventPacket::PlayerDied>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<6>(alt0);
                break;
            }
            case 7: {
                std::variant_alternative_t<7, std::variant<v818::LegacyTelemetryEventPacket::Achievement, v818::LegacyTelemetryEventPacket::Interaction, v818::LegacyTelemetryEventPacket::PortalCreated, v818::LegacyTelemetryEventPacket::PortalUsed, v818::LegacyTelemetryEventPacket::MobKilled, v818::LegacyTelemetryEventPacket::CauldronUsed, v818::LegacyTelemetryEventPacket::PlayerDied, v818::LegacyTelemetryEventPacket::BossKilled, v818::LegacyTelemetryEventPacket::SlashCommand, v818::LegacyTelemetryEventPacket::MobBorn, v818::LegacyTelemetryEventPacket::POICauldronUsed, v818::LegacyTelemetryEventPacket::ComposterUsed, v818::LegacyTelemetryEventPacket::BellUsed, v818::LegacyTelemetryEventPacket::ActorDefinition, v818::LegacyTelemetryEventPacket::RaidUpdate, v818::LegacyTelemetryEventPacket::TargetBlockHit, v818::LegacyTelemetryEventPacket::PiglinBarter, v818::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v818::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v818::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v818::LegacyTelemetryEventPacket::ItemUsed, v818::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v818::LegacyTelemetryEventPacket::BossKilled>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<7>(alt0);
                break;
            }
            case 8: {
                std::variant_alternative_t<8, std::variant<v818::LegacyTelemetryEventPacket::Achievement, v818::LegacyTelemetryEventPacket::Interaction, v818::LegacyTelemetryEventPacket::PortalCreated, v818::LegacyTelemetryEventPacket::PortalUsed, v818::LegacyTelemetryEventPacket::MobKilled, v818::LegacyTelemetryEventPacket::CauldronUsed, v818::LegacyTelemetryEventPacket::PlayerDied, v818::LegacyTelemetryEventPacket::BossKilled, v818::LegacyTelemetryEventPacket::SlashCommand, v818::LegacyTelemetryEventPacket::MobBorn, v818::LegacyTelemetryEventPacket::POICauldronUsed, v818::LegacyTelemetryEventPacket::ComposterUsed, v818::LegacyTelemetryEventPacket::BellUsed, v818::LegacyTelemetryEventPacket::ActorDefinition, v818::LegacyTelemetryEventPacket::RaidUpdate, v818::LegacyTelemetryEventPacket::TargetBlockHit, v818::LegacyTelemetryEventPacket::PiglinBarter, v818::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v818::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v818::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v818::LegacyTelemetryEventPacket::ItemUsed, v818::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v818::LegacyTelemetryEventPacket::SlashCommand>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<8>(alt0);
                break;
            }
            case 9: {
                std::variant_alternative_t<9, std::variant<v818::LegacyTelemetryEventPacket::Achievement, v818::LegacyTelemetryEventPacket::Interaction, v818::LegacyTelemetryEventPacket::PortalCreated, v818::LegacyTelemetryEventPacket::PortalUsed, v818::LegacyTelemetryEventPacket::MobKilled, v818::LegacyTelemetryEventPacket::CauldronUsed, v818::LegacyTelemetryEventPacket::PlayerDied, v818::LegacyTelemetryEventPacket::BossKilled, v818::LegacyTelemetryEventPacket::SlashCommand, v818::LegacyTelemetryEventPacket::MobBorn, v818::LegacyTelemetryEventPacket::POICauldronUsed, v818::LegacyTelemetryEventPacket::ComposterUsed, v818::LegacyTelemetryEventPacket::BellUsed, v818::LegacyTelemetryEventPacket::ActorDefinition, v818::LegacyTelemetryEventPacket::RaidUpdate, v818::LegacyTelemetryEventPacket::TargetBlockHit, v818::LegacyTelemetryEventPacket::PiglinBarter, v818::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v818::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v818::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v818::LegacyTelemetryEventPacket::ItemUsed, v818::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v818::LegacyTelemetryEventPacket::MobBorn>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<9>(alt0);
                break;
            }
            case 10: {
                std::variant_alternative_t<10, std::variant<v818::LegacyTelemetryEventPacket::Achievement, v818::LegacyTelemetryEventPacket::Interaction, v818::LegacyTelemetryEventPacket::PortalCreated, v818::LegacyTelemetryEventPacket::PortalUsed, v818::LegacyTelemetryEventPacket::MobKilled, v818::LegacyTelemetryEventPacket::CauldronUsed, v818::LegacyTelemetryEventPacket::PlayerDied, v818::LegacyTelemetryEventPacket::BossKilled, v818::LegacyTelemetryEventPacket::SlashCommand, v818::LegacyTelemetryEventPacket::MobBorn, v818::LegacyTelemetryEventPacket::POICauldronUsed, v818::LegacyTelemetryEventPacket::ComposterUsed, v818::LegacyTelemetryEventPacket::BellUsed, v818::LegacyTelemetryEventPacket::ActorDefinition, v818::LegacyTelemetryEventPacket::RaidUpdate, v818::LegacyTelemetryEventPacket::TargetBlockHit, v818::LegacyTelemetryEventPacket::PiglinBarter, v818::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v818::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v818::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v818::LegacyTelemetryEventPacket::ItemUsed, v818::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v818::LegacyTelemetryEventPacket::POICauldronUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<10>(alt0);
                break;
            }
            case 11: {
                std::variant_alternative_t<11, std::variant<v818::LegacyTelemetryEventPacket::Achievement, v818::LegacyTelemetryEventPacket::Interaction, v818::LegacyTelemetryEventPacket::PortalCreated, v818::LegacyTelemetryEventPacket::PortalUsed, v818::LegacyTelemetryEventPacket::MobKilled, v818::LegacyTelemetryEventPacket::CauldronUsed, v818::LegacyTelemetryEventPacket::PlayerDied, v818::LegacyTelemetryEventPacket::BossKilled, v818::LegacyTelemetryEventPacket::SlashCommand, v818::LegacyTelemetryEventPacket::MobBorn, v818::LegacyTelemetryEventPacket::POICauldronUsed, v818::LegacyTelemetryEventPacket::ComposterUsed, v818::LegacyTelemetryEventPacket::BellUsed, v818::LegacyTelemetryEventPacket::ActorDefinition, v818::LegacyTelemetryEventPacket::RaidUpdate, v818::LegacyTelemetryEventPacket::TargetBlockHit, v818::LegacyTelemetryEventPacket::PiglinBarter, v818::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v818::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v818::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v818::LegacyTelemetryEventPacket::ItemUsed, v818::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v818::LegacyTelemetryEventPacket::ComposterUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<11>(alt0);
                break;
            }
            case 12: {
                std::variant_alternative_t<12, std::variant<v818::LegacyTelemetryEventPacket::Achievement, v818::LegacyTelemetryEventPacket::Interaction, v818::LegacyTelemetryEventPacket::PortalCreated, v818::LegacyTelemetryEventPacket::PortalUsed, v818::LegacyTelemetryEventPacket::MobKilled, v818::LegacyTelemetryEventPacket::CauldronUsed, v818::LegacyTelemetryEventPacket::PlayerDied, v818::LegacyTelemetryEventPacket::BossKilled, v818::LegacyTelemetryEventPacket::SlashCommand, v818::LegacyTelemetryEventPacket::MobBorn, v818::LegacyTelemetryEventPacket::POICauldronUsed, v818::LegacyTelemetryEventPacket::ComposterUsed, v818::LegacyTelemetryEventPacket::BellUsed, v818::LegacyTelemetryEventPacket::ActorDefinition, v818::LegacyTelemetryEventPacket::RaidUpdate, v818::LegacyTelemetryEventPacket::TargetBlockHit, v818::LegacyTelemetryEventPacket::PiglinBarter, v818::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v818::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v818::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v818::LegacyTelemetryEventPacket::ItemUsed, v818::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v818::LegacyTelemetryEventPacket::BellUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<12>(alt0);
                break;
            }
            case 13: {
                std::variant_alternative_t<13, std::variant<v818::LegacyTelemetryEventPacket::Achievement, v818::LegacyTelemetryEventPacket::Interaction, v818::LegacyTelemetryEventPacket::PortalCreated, v818::LegacyTelemetryEventPacket::PortalUsed, v818::LegacyTelemetryEventPacket::MobKilled, v818::LegacyTelemetryEventPacket::CauldronUsed, v818::LegacyTelemetryEventPacket::PlayerDied, v818::LegacyTelemetryEventPacket::BossKilled, v818::LegacyTelemetryEventPacket::SlashCommand, v818::LegacyTelemetryEventPacket::MobBorn, v818::LegacyTelemetryEventPacket::POICauldronUsed, v818::LegacyTelemetryEventPacket::ComposterUsed, v818::LegacyTelemetryEventPacket::BellUsed, v818::LegacyTelemetryEventPacket::ActorDefinition, v818::LegacyTelemetryEventPacket::RaidUpdate, v818::LegacyTelemetryEventPacket::TargetBlockHit, v818::LegacyTelemetryEventPacket::PiglinBarter, v818::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v818::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v818::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v818::LegacyTelemetryEventPacket::ItemUsed, v818::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v818::LegacyTelemetryEventPacket::ActorDefinition>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<13>(alt0);
                break;
            }
            case 14: {
                std::variant_alternative_t<14, std::variant<v818::LegacyTelemetryEventPacket::Achievement, v818::LegacyTelemetryEventPacket::Interaction, v818::LegacyTelemetryEventPacket::PortalCreated, v818::LegacyTelemetryEventPacket::PortalUsed, v818::LegacyTelemetryEventPacket::MobKilled, v818::LegacyTelemetryEventPacket::CauldronUsed, v818::LegacyTelemetryEventPacket::PlayerDied, v818::LegacyTelemetryEventPacket::BossKilled, v818::LegacyTelemetryEventPacket::SlashCommand, v818::LegacyTelemetryEventPacket::MobBorn, v818::LegacyTelemetryEventPacket::POICauldronUsed, v818::LegacyTelemetryEventPacket::ComposterUsed, v818::LegacyTelemetryEventPacket::BellUsed, v818::LegacyTelemetryEventPacket::ActorDefinition, v818::LegacyTelemetryEventPacket::RaidUpdate, v818::LegacyTelemetryEventPacket::TargetBlockHit, v818::LegacyTelemetryEventPacket::PiglinBarter, v818::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v818::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v818::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v818::LegacyTelemetryEventPacket::ItemUsed, v818::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v818::LegacyTelemetryEventPacket::RaidUpdate>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<14>(alt0);
                break;
            }
            case 15: {
                std::variant_alternative_t<15, std::variant<v818::LegacyTelemetryEventPacket::Achievement, v818::LegacyTelemetryEventPacket::Interaction, v818::LegacyTelemetryEventPacket::PortalCreated, v818::LegacyTelemetryEventPacket::PortalUsed, v818::LegacyTelemetryEventPacket::MobKilled, v818::LegacyTelemetryEventPacket::CauldronUsed, v818::LegacyTelemetryEventPacket::PlayerDied, v818::LegacyTelemetryEventPacket::BossKilled, v818::LegacyTelemetryEventPacket::SlashCommand, v818::LegacyTelemetryEventPacket::MobBorn, v818::LegacyTelemetryEventPacket::POICauldronUsed, v818::LegacyTelemetryEventPacket::ComposterUsed, v818::LegacyTelemetryEventPacket::BellUsed, v818::LegacyTelemetryEventPacket::ActorDefinition, v818::LegacyTelemetryEventPacket::RaidUpdate, v818::LegacyTelemetryEventPacket::TargetBlockHit, v818::LegacyTelemetryEventPacket::PiglinBarter, v818::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v818::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v818::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v818::LegacyTelemetryEventPacket::ItemUsed, v818::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v818::LegacyTelemetryEventPacket::TargetBlockHit>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<15>(alt0);
                break;
            }
            case 16: {
                std::variant_alternative_t<16, std::variant<v818::LegacyTelemetryEventPacket::Achievement, v818::LegacyTelemetryEventPacket::Interaction, v818::LegacyTelemetryEventPacket::PortalCreated, v818::LegacyTelemetryEventPacket::PortalUsed, v818::LegacyTelemetryEventPacket::MobKilled, v818::LegacyTelemetryEventPacket::CauldronUsed, v818::LegacyTelemetryEventPacket::PlayerDied, v818::LegacyTelemetryEventPacket::BossKilled, v818::LegacyTelemetryEventPacket::SlashCommand, v818::LegacyTelemetryEventPacket::MobBorn, v818::LegacyTelemetryEventPacket::POICauldronUsed, v818::LegacyTelemetryEventPacket::ComposterUsed, v818::LegacyTelemetryEventPacket::BellUsed, v818::LegacyTelemetryEventPacket::ActorDefinition, v818::LegacyTelemetryEventPacket::RaidUpdate, v818::LegacyTelemetryEventPacket::TargetBlockHit, v818::LegacyTelemetryEventPacket::PiglinBarter, v818::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v818::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v818::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v818::LegacyTelemetryEventPacket::ItemUsed, v818::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v818::LegacyTelemetryEventPacket::PiglinBarter>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<16>(alt0);
                break;
            }
            case 17: {
                std::variant_alternative_t<17, std::variant<v818::LegacyTelemetryEventPacket::Achievement, v818::LegacyTelemetryEventPacket::Interaction, v818::LegacyTelemetryEventPacket::PortalCreated, v818::LegacyTelemetryEventPacket::PortalUsed, v818::LegacyTelemetryEventPacket::MobKilled, v818::LegacyTelemetryEventPacket::CauldronUsed, v818::LegacyTelemetryEventPacket::PlayerDied, v818::LegacyTelemetryEventPacket::BossKilled, v818::LegacyTelemetryEventPacket::SlashCommand, v818::LegacyTelemetryEventPacket::MobBorn, v818::LegacyTelemetryEventPacket::POICauldronUsed, v818::LegacyTelemetryEventPacket::ComposterUsed, v818::LegacyTelemetryEventPacket::BellUsed, v818::LegacyTelemetryEventPacket::ActorDefinition, v818::LegacyTelemetryEventPacket::RaidUpdate, v818::LegacyTelemetryEventPacket::TargetBlockHit, v818::LegacyTelemetryEventPacket::PiglinBarter, v818::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v818::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v818::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v818::LegacyTelemetryEventPacket::ItemUsed, v818::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v818::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<17>(alt0);
                break;
            }
            case 18: {
                std::variant_alternative_t<18, std::variant<v818::LegacyTelemetryEventPacket::Achievement, v818::LegacyTelemetryEventPacket::Interaction, v818::LegacyTelemetryEventPacket::PortalCreated, v818::LegacyTelemetryEventPacket::PortalUsed, v818::LegacyTelemetryEventPacket::MobKilled, v818::LegacyTelemetryEventPacket::CauldronUsed, v818::LegacyTelemetryEventPacket::PlayerDied, v818::LegacyTelemetryEventPacket::BossKilled, v818::LegacyTelemetryEventPacket::SlashCommand, v818::LegacyTelemetryEventPacket::MobBorn, v818::LegacyTelemetryEventPacket::POICauldronUsed, v818::LegacyTelemetryEventPacket::ComposterUsed, v818::LegacyTelemetryEventPacket::BellUsed, v818::LegacyTelemetryEventPacket::ActorDefinition, v818::LegacyTelemetryEventPacket::RaidUpdate, v818::LegacyTelemetryEventPacket::TargetBlockHit, v818::LegacyTelemetryEventPacket::PiglinBarter, v818::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v818::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v818::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v818::LegacyTelemetryEventPacket::ItemUsed, v818::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v818::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<18>(alt0);
                break;
            }
            case 19: {
                std::variant_alternative_t<19, std::variant<v818::LegacyTelemetryEventPacket::Achievement, v818::LegacyTelemetryEventPacket::Interaction, v818::LegacyTelemetryEventPacket::PortalCreated, v818::LegacyTelemetryEventPacket::PortalUsed, v818::LegacyTelemetryEventPacket::MobKilled, v818::LegacyTelemetryEventPacket::CauldronUsed, v818::LegacyTelemetryEventPacket::PlayerDied, v818::LegacyTelemetryEventPacket::BossKilled, v818::LegacyTelemetryEventPacket::SlashCommand, v818::LegacyTelemetryEventPacket::MobBorn, v818::LegacyTelemetryEventPacket::POICauldronUsed, v818::LegacyTelemetryEventPacket::ComposterUsed, v818::LegacyTelemetryEventPacket::BellUsed, v818::LegacyTelemetryEventPacket::ActorDefinition, v818::LegacyTelemetryEventPacket::RaidUpdate, v818::LegacyTelemetryEventPacket::TargetBlockHit, v818::LegacyTelemetryEventPacket::PiglinBarter, v818::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v818::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v818::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v818::LegacyTelemetryEventPacket::ItemUsed, v818::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v818::LegacyTelemetryEventPacket::CodeBuilderScoreboard>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<19>(alt0);
                break;
            }
            case 20: {
                std::variant_alternative_t<20, std::variant<v818::LegacyTelemetryEventPacket::Achievement, v818::LegacyTelemetryEventPacket::Interaction, v818::LegacyTelemetryEventPacket::PortalCreated, v818::LegacyTelemetryEventPacket::PortalUsed, v818::LegacyTelemetryEventPacket::MobKilled, v818::LegacyTelemetryEventPacket::CauldronUsed, v818::LegacyTelemetryEventPacket::PlayerDied, v818::LegacyTelemetryEventPacket::BossKilled, v818::LegacyTelemetryEventPacket::SlashCommand, v818::LegacyTelemetryEventPacket::MobBorn, v818::LegacyTelemetryEventPacket::POICauldronUsed, v818::LegacyTelemetryEventPacket::ComposterUsed, v818::LegacyTelemetryEventPacket::BellUsed, v818::LegacyTelemetryEventPacket::ActorDefinition, v818::LegacyTelemetryEventPacket::RaidUpdate, v818::LegacyTelemetryEventPacket::TargetBlockHit, v818::LegacyTelemetryEventPacket::PiglinBarter, v818::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v818::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v818::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v818::LegacyTelemetryEventPacket::ItemUsed, v818::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v818::LegacyTelemetryEventPacket::ItemUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<20>(alt0);
                break;
            }
            case 21: {
                std::variant_alternative_t<21, std::variant<v818::LegacyTelemetryEventPacket::Achievement, v818::LegacyTelemetryEventPacket::Interaction, v818::LegacyTelemetryEventPacket::PortalCreated, v818::LegacyTelemetryEventPacket::PortalUsed, v818::LegacyTelemetryEventPacket::MobKilled, v818::LegacyTelemetryEventPacket::CauldronUsed, v818::LegacyTelemetryEventPacket::PlayerDied, v818::LegacyTelemetryEventPacket::BossKilled, v818::LegacyTelemetryEventPacket::SlashCommand, v818::LegacyTelemetryEventPacket::MobBorn, v818::LegacyTelemetryEventPacket::POICauldronUsed, v818::LegacyTelemetryEventPacket::ComposterUsed, v818::LegacyTelemetryEventPacket::BellUsed, v818::LegacyTelemetryEventPacket::ActorDefinition, v818::LegacyTelemetryEventPacket::RaidUpdate, v818::LegacyTelemetryEventPacket::TargetBlockHit, v818::LegacyTelemetryEventPacket::PiglinBarter, v818::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v818::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v818::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v818::LegacyTelemetryEventPacket::ItemUsed, v818::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v818::LegacyTelemetryEventPacket::Empty>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<21>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.event_data = var0;
    }
    return out;
}

void Serializer<v827::LegacyTelemetryEventPacket>::serialize(BinaryWriter &stream, const v827::LegacyTelemetryEventPacket &value)
{
    stream.writeVarInt<std::int64_t>(value.player_unique_id);
    stream.writeVarInt<std::int32_t>(value.type);
    stream.write<bool>(value.use_player_id);
    stream.writeVarInt<std::uint32_t>((value.event_data).index());
    switch ((value.event_data).index()) {
        case 0: {
            Serializer<v827::LegacyTelemetryEventPacket::Achievement>::serialize(stream, std::get<0>(value.event_data));
            break;
        }
        case 1: {
            Serializer<v827::LegacyTelemetryEventPacket::Interaction>::serialize(stream, std::get<1>(value.event_data));
            break;
        }
        case 2: {
            Serializer<v827::LegacyTelemetryEventPacket::PortalCreated>::serialize(stream, std::get<2>(value.event_data));
            break;
        }
        case 3: {
            Serializer<v827::LegacyTelemetryEventPacket::PortalUsed>::serialize(stream, std::get<3>(value.event_data));
            break;
        }
        case 4: {
            Serializer<v827::LegacyTelemetryEventPacket::MobKilled>::serialize(stream, std::get<4>(value.event_data));
            break;
        }
        case 5: {
            Serializer<v827::LegacyTelemetryEventPacket::CauldronUsed>::serialize(stream, std::get<5>(value.event_data));
            break;
        }
        case 6: {
            Serializer<v827::LegacyTelemetryEventPacket::PlayerDied>::serialize(stream, std::get<6>(value.event_data));
            break;
        }
        case 7: {
            Serializer<v827::LegacyTelemetryEventPacket::BossKilled>::serialize(stream, std::get<7>(value.event_data));
            break;
        }
        case 8: {
            Serializer<v827::LegacyTelemetryEventPacket::SlashCommand>::serialize(stream, std::get<8>(value.event_data));
            break;
        }
        case 9: {
            Serializer<v827::LegacyTelemetryEventPacket::MobBorn>::serialize(stream, std::get<9>(value.event_data));
            break;
        }
        case 10: {
            Serializer<v827::LegacyTelemetryEventPacket::POICauldronUsed>::serialize(stream, std::get<10>(value.event_data));
            break;
        }
        case 11: {
            Serializer<v827::LegacyTelemetryEventPacket::ComposterUsed>::serialize(stream, std::get<11>(value.event_data));
            break;
        }
        case 12: {
            Serializer<v827::LegacyTelemetryEventPacket::BellUsed>::serialize(stream, std::get<12>(value.event_data));
            break;
        }
        case 13: {
            Serializer<v827::LegacyTelemetryEventPacket::ActorDefinition>::serialize(stream, std::get<13>(value.event_data));
            break;
        }
        case 14: {
            Serializer<v827::LegacyTelemetryEventPacket::RaidUpdate>::serialize(stream, std::get<14>(value.event_data));
            break;
        }
        case 15: {
            Serializer<v827::LegacyTelemetryEventPacket::TargetBlockHit>::serialize(stream, std::get<15>(value.event_data));
            break;
        }
        case 16: {
            Serializer<v827::LegacyTelemetryEventPacket::PiglinBarter>::serialize(stream, std::get<16>(value.event_data));
            break;
        }
        case 17: {
            Serializer<v827::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper>::serialize(stream, std::get<17>(value.event_data));
            break;
        }
        case 18: {
            Serializer<v827::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction>::serialize(stream, std::get<18>(value.event_data));
            break;
        }
        case 19: {
            Serializer<v827::LegacyTelemetryEventPacket::CodeBuilderScoreboard>::serialize(stream, std::get<19>(value.event_data));
            break;
        }
        case 20: {
            Serializer<v827::LegacyTelemetryEventPacket::ItemUsed>::serialize(stream, std::get<20>(value.event_data));
            break;
        }
        case 21: {
            Serializer<v827::LegacyTelemetryEventPacket::Empty>::serialize(stream, std::get<21>(value.event_data));
            break;
        }
    }
}

auto Serializer<v827::LegacyTelemetryEventPacket>::deserialize(BinaryReader &stream) -> std::expected<v827::LegacyTelemetryEventPacket, std::error_code>
{
    v827::LegacyTelemetryEventPacket out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.player_unique_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<v827::LegacyTelemetryEventPacket::Type>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.use_player_id = static_cast<bool>(*v);
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v827::LegacyTelemetryEventPacket::Achievement, v827::LegacyTelemetryEventPacket::Interaction, v827::LegacyTelemetryEventPacket::PortalCreated, v827::LegacyTelemetryEventPacket::PortalUsed, v827::LegacyTelemetryEventPacket::MobKilled, v827::LegacyTelemetryEventPacket::CauldronUsed, v827::LegacyTelemetryEventPacket::PlayerDied, v827::LegacyTelemetryEventPacket::BossKilled, v827::LegacyTelemetryEventPacket::SlashCommand, v827::LegacyTelemetryEventPacket::MobBorn, v827::LegacyTelemetryEventPacket::POICauldronUsed, v827::LegacyTelemetryEventPacket::ComposterUsed, v827::LegacyTelemetryEventPacket::BellUsed, v827::LegacyTelemetryEventPacket::ActorDefinition, v827::LegacyTelemetryEventPacket::RaidUpdate, v827::LegacyTelemetryEventPacket::TargetBlockHit, v827::LegacyTelemetryEventPacket::PiglinBarter, v827::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v827::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v827::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v827::LegacyTelemetryEventPacket::ItemUsed, v827::LegacyTelemetryEventPacket::Empty> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v827::LegacyTelemetryEventPacket::Achievement, v827::LegacyTelemetryEventPacket::Interaction, v827::LegacyTelemetryEventPacket::PortalCreated, v827::LegacyTelemetryEventPacket::PortalUsed, v827::LegacyTelemetryEventPacket::MobKilled, v827::LegacyTelemetryEventPacket::CauldronUsed, v827::LegacyTelemetryEventPacket::PlayerDied, v827::LegacyTelemetryEventPacket::BossKilled, v827::LegacyTelemetryEventPacket::SlashCommand, v827::LegacyTelemetryEventPacket::MobBorn, v827::LegacyTelemetryEventPacket::POICauldronUsed, v827::LegacyTelemetryEventPacket::ComposterUsed, v827::LegacyTelemetryEventPacket::BellUsed, v827::LegacyTelemetryEventPacket::ActorDefinition, v827::LegacyTelemetryEventPacket::RaidUpdate, v827::LegacyTelemetryEventPacket::TargetBlockHit, v827::LegacyTelemetryEventPacket::PiglinBarter, v827::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v827::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v827::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v827::LegacyTelemetryEventPacket::ItemUsed, v827::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v827::LegacyTelemetryEventPacket::Achievement>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v827::LegacyTelemetryEventPacket::Achievement, v827::LegacyTelemetryEventPacket::Interaction, v827::LegacyTelemetryEventPacket::PortalCreated, v827::LegacyTelemetryEventPacket::PortalUsed, v827::LegacyTelemetryEventPacket::MobKilled, v827::LegacyTelemetryEventPacket::CauldronUsed, v827::LegacyTelemetryEventPacket::PlayerDied, v827::LegacyTelemetryEventPacket::BossKilled, v827::LegacyTelemetryEventPacket::SlashCommand, v827::LegacyTelemetryEventPacket::MobBorn, v827::LegacyTelemetryEventPacket::POICauldronUsed, v827::LegacyTelemetryEventPacket::ComposterUsed, v827::LegacyTelemetryEventPacket::BellUsed, v827::LegacyTelemetryEventPacket::ActorDefinition, v827::LegacyTelemetryEventPacket::RaidUpdate, v827::LegacyTelemetryEventPacket::TargetBlockHit, v827::LegacyTelemetryEventPacket::PiglinBarter, v827::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v827::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v827::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v827::LegacyTelemetryEventPacket::ItemUsed, v827::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v827::LegacyTelemetryEventPacket::Interaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<v827::LegacyTelemetryEventPacket::Achievement, v827::LegacyTelemetryEventPacket::Interaction, v827::LegacyTelemetryEventPacket::PortalCreated, v827::LegacyTelemetryEventPacket::PortalUsed, v827::LegacyTelemetryEventPacket::MobKilled, v827::LegacyTelemetryEventPacket::CauldronUsed, v827::LegacyTelemetryEventPacket::PlayerDied, v827::LegacyTelemetryEventPacket::BossKilled, v827::LegacyTelemetryEventPacket::SlashCommand, v827::LegacyTelemetryEventPacket::MobBorn, v827::LegacyTelemetryEventPacket::POICauldronUsed, v827::LegacyTelemetryEventPacket::ComposterUsed, v827::LegacyTelemetryEventPacket::BellUsed, v827::LegacyTelemetryEventPacket::ActorDefinition, v827::LegacyTelemetryEventPacket::RaidUpdate, v827::LegacyTelemetryEventPacket::TargetBlockHit, v827::LegacyTelemetryEventPacket::PiglinBarter, v827::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v827::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v827::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v827::LegacyTelemetryEventPacket::ItemUsed, v827::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v827::LegacyTelemetryEventPacket::PortalCreated>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<v827::LegacyTelemetryEventPacket::Achievement, v827::LegacyTelemetryEventPacket::Interaction, v827::LegacyTelemetryEventPacket::PortalCreated, v827::LegacyTelemetryEventPacket::PortalUsed, v827::LegacyTelemetryEventPacket::MobKilled, v827::LegacyTelemetryEventPacket::CauldronUsed, v827::LegacyTelemetryEventPacket::PlayerDied, v827::LegacyTelemetryEventPacket::BossKilled, v827::LegacyTelemetryEventPacket::SlashCommand, v827::LegacyTelemetryEventPacket::MobBorn, v827::LegacyTelemetryEventPacket::POICauldronUsed, v827::LegacyTelemetryEventPacket::ComposterUsed, v827::LegacyTelemetryEventPacket::BellUsed, v827::LegacyTelemetryEventPacket::ActorDefinition, v827::LegacyTelemetryEventPacket::RaidUpdate, v827::LegacyTelemetryEventPacket::TargetBlockHit, v827::LegacyTelemetryEventPacket::PiglinBarter, v827::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v827::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v827::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v827::LegacyTelemetryEventPacket::ItemUsed, v827::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v827::LegacyTelemetryEventPacket::PortalUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            case 4: {
                std::variant_alternative_t<4, std::variant<v827::LegacyTelemetryEventPacket::Achievement, v827::LegacyTelemetryEventPacket::Interaction, v827::LegacyTelemetryEventPacket::PortalCreated, v827::LegacyTelemetryEventPacket::PortalUsed, v827::LegacyTelemetryEventPacket::MobKilled, v827::LegacyTelemetryEventPacket::CauldronUsed, v827::LegacyTelemetryEventPacket::PlayerDied, v827::LegacyTelemetryEventPacket::BossKilled, v827::LegacyTelemetryEventPacket::SlashCommand, v827::LegacyTelemetryEventPacket::MobBorn, v827::LegacyTelemetryEventPacket::POICauldronUsed, v827::LegacyTelemetryEventPacket::ComposterUsed, v827::LegacyTelemetryEventPacket::BellUsed, v827::LegacyTelemetryEventPacket::ActorDefinition, v827::LegacyTelemetryEventPacket::RaidUpdate, v827::LegacyTelemetryEventPacket::TargetBlockHit, v827::LegacyTelemetryEventPacket::PiglinBarter, v827::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v827::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v827::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v827::LegacyTelemetryEventPacket::ItemUsed, v827::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v827::LegacyTelemetryEventPacket::MobKilled>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<4>(alt0);
                break;
            }
            case 5: {
                std::variant_alternative_t<5, std::variant<v827::LegacyTelemetryEventPacket::Achievement, v827::LegacyTelemetryEventPacket::Interaction, v827::LegacyTelemetryEventPacket::PortalCreated, v827::LegacyTelemetryEventPacket::PortalUsed, v827::LegacyTelemetryEventPacket::MobKilled, v827::LegacyTelemetryEventPacket::CauldronUsed, v827::LegacyTelemetryEventPacket::PlayerDied, v827::LegacyTelemetryEventPacket::BossKilled, v827::LegacyTelemetryEventPacket::SlashCommand, v827::LegacyTelemetryEventPacket::MobBorn, v827::LegacyTelemetryEventPacket::POICauldronUsed, v827::LegacyTelemetryEventPacket::ComposterUsed, v827::LegacyTelemetryEventPacket::BellUsed, v827::LegacyTelemetryEventPacket::ActorDefinition, v827::LegacyTelemetryEventPacket::RaidUpdate, v827::LegacyTelemetryEventPacket::TargetBlockHit, v827::LegacyTelemetryEventPacket::PiglinBarter, v827::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v827::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v827::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v827::LegacyTelemetryEventPacket::ItemUsed, v827::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v827::LegacyTelemetryEventPacket::CauldronUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<5>(alt0);
                break;
            }
            case 6: {
                std::variant_alternative_t<6, std::variant<v827::LegacyTelemetryEventPacket::Achievement, v827::LegacyTelemetryEventPacket::Interaction, v827::LegacyTelemetryEventPacket::PortalCreated, v827::LegacyTelemetryEventPacket::PortalUsed, v827::LegacyTelemetryEventPacket::MobKilled, v827::LegacyTelemetryEventPacket::CauldronUsed, v827::LegacyTelemetryEventPacket::PlayerDied, v827::LegacyTelemetryEventPacket::BossKilled, v827::LegacyTelemetryEventPacket::SlashCommand, v827::LegacyTelemetryEventPacket::MobBorn, v827::LegacyTelemetryEventPacket::POICauldronUsed, v827::LegacyTelemetryEventPacket::ComposterUsed, v827::LegacyTelemetryEventPacket::BellUsed, v827::LegacyTelemetryEventPacket::ActorDefinition, v827::LegacyTelemetryEventPacket::RaidUpdate, v827::LegacyTelemetryEventPacket::TargetBlockHit, v827::LegacyTelemetryEventPacket::PiglinBarter, v827::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v827::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v827::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v827::LegacyTelemetryEventPacket::ItemUsed, v827::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v827::LegacyTelemetryEventPacket::PlayerDied>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<6>(alt0);
                break;
            }
            case 7: {
                std::variant_alternative_t<7, std::variant<v827::LegacyTelemetryEventPacket::Achievement, v827::LegacyTelemetryEventPacket::Interaction, v827::LegacyTelemetryEventPacket::PortalCreated, v827::LegacyTelemetryEventPacket::PortalUsed, v827::LegacyTelemetryEventPacket::MobKilled, v827::LegacyTelemetryEventPacket::CauldronUsed, v827::LegacyTelemetryEventPacket::PlayerDied, v827::LegacyTelemetryEventPacket::BossKilled, v827::LegacyTelemetryEventPacket::SlashCommand, v827::LegacyTelemetryEventPacket::MobBorn, v827::LegacyTelemetryEventPacket::POICauldronUsed, v827::LegacyTelemetryEventPacket::ComposterUsed, v827::LegacyTelemetryEventPacket::BellUsed, v827::LegacyTelemetryEventPacket::ActorDefinition, v827::LegacyTelemetryEventPacket::RaidUpdate, v827::LegacyTelemetryEventPacket::TargetBlockHit, v827::LegacyTelemetryEventPacket::PiglinBarter, v827::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v827::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v827::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v827::LegacyTelemetryEventPacket::ItemUsed, v827::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v827::LegacyTelemetryEventPacket::BossKilled>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<7>(alt0);
                break;
            }
            case 8: {
                std::variant_alternative_t<8, std::variant<v827::LegacyTelemetryEventPacket::Achievement, v827::LegacyTelemetryEventPacket::Interaction, v827::LegacyTelemetryEventPacket::PortalCreated, v827::LegacyTelemetryEventPacket::PortalUsed, v827::LegacyTelemetryEventPacket::MobKilled, v827::LegacyTelemetryEventPacket::CauldronUsed, v827::LegacyTelemetryEventPacket::PlayerDied, v827::LegacyTelemetryEventPacket::BossKilled, v827::LegacyTelemetryEventPacket::SlashCommand, v827::LegacyTelemetryEventPacket::MobBorn, v827::LegacyTelemetryEventPacket::POICauldronUsed, v827::LegacyTelemetryEventPacket::ComposterUsed, v827::LegacyTelemetryEventPacket::BellUsed, v827::LegacyTelemetryEventPacket::ActorDefinition, v827::LegacyTelemetryEventPacket::RaidUpdate, v827::LegacyTelemetryEventPacket::TargetBlockHit, v827::LegacyTelemetryEventPacket::PiglinBarter, v827::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v827::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v827::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v827::LegacyTelemetryEventPacket::ItemUsed, v827::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v827::LegacyTelemetryEventPacket::SlashCommand>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<8>(alt0);
                break;
            }
            case 9: {
                std::variant_alternative_t<9, std::variant<v827::LegacyTelemetryEventPacket::Achievement, v827::LegacyTelemetryEventPacket::Interaction, v827::LegacyTelemetryEventPacket::PortalCreated, v827::LegacyTelemetryEventPacket::PortalUsed, v827::LegacyTelemetryEventPacket::MobKilled, v827::LegacyTelemetryEventPacket::CauldronUsed, v827::LegacyTelemetryEventPacket::PlayerDied, v827::LegacyTelemetryEventPacket::BossKilled, v827::LegacyTelemetryEventPacket::SlashCommand, v827::LegacyTelemetryEventPacket::MobBorn, v827::LegacyTelemetryEventPacket::POICauldronUsed, v827::LegacyTelemetryEventPacket::ComposterUsed, v827::LegacyTelemetryEventPacket::BellUsed, v827::LegacyTelemetryEventPacket::ActorDefinition, v827::LegacyTelemetryEventPacket::RaidUpdate, v827::LegacyTelemetryEventPacket::TargetBlockHit, v827::LegacyTelemetryEventPacket::PiglinBarter, v827::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v827::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v827::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v827::LegacyTelemetryEventPacket::ItemUsed, v827::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v827::LegacyTelemetryEventPacket::MobBorn>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<9>(alt0);
                break;
            }
            case 10: {
                std::variant_alternative_t<10, std::variant<v827::LegacyTelemetryEventPacket::Achievement, v827::LegacyTelemetryEventPacket::Interaction, v827::LegacyTelemetryEventPacket::PortalCreated, v827::LegacyTelemetryEventPacket::PortalUsed, v827::LegacyTelemetryEventPacket::MobKilled, v827::LegacyTelemetryEventPacket::CauldronUsed, v827::LegacyTelemetryEventPacket::PlayerDied, v827::LegacyTelemetryEventPacket::BossKilled, v827::LegacyTelemetryEventPacket::SlashCommand, v827::LegacyTelemetryEventPacket::MobBorn, v827::LegacyTelemetryEventPacket::POICauldronUsed, v827::LegacyTelemetryEventPacket::ComposterUsed, v827::LegacyTelemetryEventPacket::BellUsed, v827::LegacyTelemetryEventPacket::ActorDefinition, v827::LegacyTelemetryEventPacket::RaidUpdate, v827::LegacyTelemetryEventPacket::TargetBlockHit, v827::LegacyTelemetryEventPacket::PiglinBarter, v827::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v827::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v827::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v827::LegacyTelemetryEventPacket::ItemUsed, v827::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v827::LegacyTelemetryEventPacket::POICauldronUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<10>(alt0);
                break;
            }
            case 11: {
                std::variant_alternative_t<11, std::variant<v827::LegacyTelemetryEventPacket::Achievement, v827::LegacyTelemetryEventPacket::Interaction, v827::LegacyTelemetryEventPacket::PortalCreated, v827::LegacyTelemetryEventPacket::PortalUsed, v827::LegacyTelemetryEventPacket::MobKilled, v827::LegacyTelemetryEventPacket::CauldronUsed, v827::LegacyTelemetryEventPacket::PlayerDied, v827::LegacyTelemetryEventPacket::BossKilled, v827::LegacyTelemetryEventPacket::SlashCommand, v827::LegacyTelemetryEventPacket::MobBorn, v827::LegacyTelemetryEventPacket::POICauldronUsed, v827::LegacyTelemetryEventPacket::ComposterUsed, v827::LegacyTelemetryEventPacket::BellUsed, v827::LegacyTelemetryEventPacket::ActorDefinition, v827::LegacyTelemetryEventPacket::RaidUpdate, v827::LegacyTelemetryEventPacket::TargetBlockHit, v827::LegacyTelemetryEventPacket::PiglinBarter, v827::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v827::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v827::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v827::LegacyTelemetryEventPacket::ItemUsed, v827::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v827::LegacyTelemetryEventPacket::ComposterUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<11>(alt0);
                break;
            }
            case 12: {
                std::variant_alternative_t<12, std::variant<v827::LegacyTelemetryEventPacket::Achievement, v827::LegacyTelemetryEventPacket::Interaction, v827::LegacyTelemetryEventPacket::PortalCreated, v827::LegacyTelemetryEventPacket::PortalUsed, v827::LegacyTelemetryEventPacket::MobKilled, v827::LegacyTelemetryEventPacket::CauldronUsed, v827::LegacyTelemetryEventPacket::PlayerDied, v827::LegacyTelemetryEventPacket::BossKilled, v827::LegacyTelemetryEventPacket::SlashCommand, v827::LegacyTelemetryEventPacket::MobBorn, v827::LegacyTelemetryEventPacket::POICauldronUsed, v827::LegacyTelemetryEventPacket::ComposterUsed, v827::LegacyTelemetryEventPacket::BellUsed, v827::LegacyTelemetryEventPacket::ActorDefinition, v827::LegacyTelemetryEventPacket::RaidUpdate, v827::LegacyTelemetryEventPacket::TargetBlockHit, v827::LegacyTelemetryEventPacket::PiglinBarter, v827::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v827::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v827::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v827::LegacyTelemetryEventPacket::ItemUsed, v827::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v827::LegacyTelemetryEventPacket::BellUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<12>(alt0);
                break;
            }
            case 13: {
                std::variant_alternative_t<13, std::variant<v827::LegacyTelemetryEventPacket::Achievement, v827::LegacyTelemetryEventPacket::Interaction, v827::LegacyTelemetryEventPacket::PortalCreated, v827::LegacyTelemetryEventPacket::PortalUsed, v827::LegacyTelemetryEventPacket::MobKilled, v827::LegacyTelemetryEventPacket::CauldronUsed, v827::LegacyTelemetryEventPacket::PlayerDied, v827::LegacyTelemetryEventPacket::BossKilled, v827::LegacyTelemetryEventPacket::SlashCommand, v827::LegacyTelemetryEventPacket::MobBorn, v827::LegacyTelemetryEventPacket::POICauldronUsed, v827::LegacyTelemetryEventPacket::ComposterUsed, v827::LegacyTelemetryEventPacket::BellUsed, v827::LegacyTelemetryEventPacket::ActorDefinition, v827::LegacyTelemetryEventPacket::RaidUpdate, v827::LegacyTelemetryEventPacket::TargetBlockHit, v827::LegacyTelemetryEventPacket::PiglinBarter, v827::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v827::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v827::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v827::LegacyTelemetryEventPacket::ItemUsed, v827::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v827::LegacyTelemetryEventPacket::ActorDefinition>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<13>(alt0);
                break;
            }
            case 14: {
                std::variant_alternative_t<14, std::variant<v827::LegacyTelemetryEventPacket::Achievement, v827::LegacyTelemetryEventPacket::Interaction, v827::LegacyTelemetryEventPacket::PortalCreated, v827::LegacyTelemetryEventPacket::PortalUsed, v827::LegacyTelemetryEventPacket::MobKilled, v827::LegacyTelemetryEventPacket::CauldronUsed, v827::LegacyTelemetryEventPacket::PlayerDied, v827::LegacyTelemetryEventPacket::BossKilled, v827::LegacyTelemetryEventPacket::SlashCommand, v827::LegacyTelemetryEventPacket::MobBorn, v827::LegacyTelemetryEventPacket::POICauldronUsed, v827::LegacyTelemetryEventPacket::ComposterUsed, v827::LegacyTelemetryEventPacket::BellUsed, v827::LegacyTelemetryEventPacket::ActorDefinition, v827::LegacyTelemetryEventPacket::RaidUpdate, v827::LegacyTelemetryEventPacket::TargetBlockHit, v827::LegacyTelemetryEventPacket::PiglinBarter, v827::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v827::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v827::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v827::LegacyTelemetryEventPacket::ItemUsed, v827::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v827::LegacyTelemetryEventPacket::RaidUpdate>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<14>(alt0);
                break;
            }
            case 15: {
                std::variant_alternative_t<15, std::variant<v827::LegacyTelemetryEventPacket::Achievement, v827::LegacyTelemetryEventPacket::Interaction, v827::LegacyTelemetryEventPacket::PortalCreated, v827::LegacyTelemetryEventPacket::PortalUsed, v827::LegacyTelemetryEventPacket::MobKilled, v827::LegacyTelemetryEventPacket::CauldronUsed, v827::LegacyTelemetryEventPacket::PlayerDied, v827::LegacyTelemetryEventPacket::BossKilled, v827::LegacyTelemetryEventPacket::SlashCommand, v827::LegacyTelemetryEventPacket::MobBorn, v827::LegacyTelemetryEventPacket::POICauldronUsed, v827::LegacyTelemetryEventPacket::ComposterUsed, v827::LegacyTelemetryEventPacket::BellUsed, v827::LegacyTelemetryEventPacket::ActorDefinition, v827::LegacyTelemetryEventPacket::RaidUpdate, v827::LegacyTelemetryEventPacket::TargetBlockHit, v827::LegacyTelemetryEventPacket::PiglinBarter, v827::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v827::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v827::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v827::LegacyTelemetryEventPacket::ItemUsed, v827::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v827::LegacyTelemetryEventPacket::TargetBlockHit>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<15>(alt0);
                break;
            }
            case 16: {
                std::variant_alternative_t<16, std::variant<v827::LegacyTelemetryEventPacket::Achievement, v827::LegacyTelemetryEventPacket::Interaction, v827::LegacyTelemetryEventPacket::PortalCreated, v827::LegacyTelemetryEventPacket::PortalUsed, v827::LegacyTelemetryEventPacket::MobKilled, v827::LegacyTelemetryEventPacket::CauldronUsed, v827::LegacyTelemetryEventPacket::PlayerDied, v827::LegacyTelemetryEventPacket::BossKilled, v827::LegacyTelemetryEventPacket::SlashCommand, v827::LegacyTelemetryEventPacket::MobBorn, v827::LegacyTelemetryEventPacket::POICauldronUsed, v827::LegacyTelemetryEventPacket::ComposterUsed, v827::LegacyTelemetryEventPacket::BellUsed, v827::LegacyTelemetryEventPacket::ActorDefinition, v827::LegacyTelemetryEventPacket::RaidUpdate, v827::LegacyTelemetryEventPacket::TargetBlockHit, v827::LegacyTelemetryEventPacket::PiglinBarter, v827::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v827::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v827::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v827::LegacyTelemetryEventPacket::ItemUsed, v827::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v827::LegacyTelemetryEventPacket::PiglinBarter>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<16>(alt0);
                break;
            }
            case 17: {
                std::variant_alternative_t<17, std::variant<v827::LegacyTelemetryEventPacket::Achievement, v827::LegacyTelemetryEventPacket::Interaction, v827::LegacyTelemetryEventPacket::PortalCreated, v827::LegacyTelemetryEventPacket::PortalUsed, v827::LegacyTelemetryEventPacket::MobKilled, v827::LegacyTelemetryEventPacket::CauldronUsed, v827::LegacyTelemetryEventPacket::PlayerDied, v827::LegacyTelemetryEventPacket::BossKilled, v827::LegacyTelemetryEventPacket::SlashCommand, v827::LegacyTelemetryEventPacket::MobBorn, v827::LegacyTelemetryEventPacket::POICauldronUsed, v827::LegacyTelemetryEventPacket::ComposterUsed, v827::LegacyTelemetryEventPacket::BellUsed, v827::LegacyTelemetryEventPacket::ActorDefinition, v827::LegacyTelemetryEventPacket::RaidUpdate, v827::LegacyTelemetryEventPacket::TargetBlockHit, v827::LegacyTelemetryEventPacket::PiglinBarter, v827::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v827::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v827::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v827::LegacyTelemetryEventPacket::ItemUsed, v827::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v827::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<17>(alt0);
                break;
            }
            case 18: {
                std::variant_alternative_t<18, std::variant<v827::LegacyTelemetryEventPacket::Achievement, v827::LegacyTelemetryEventPacket::Interaction, v827::LegacyTelemetryEventPacket::PortalCreated, v827::LegacyTelemetryEventPacket::PortalUsed, v827::LegacyTelemetryEventPacket::MobKilled, v827::LegacyTelemetryEventPacket::CauldronUsed, v827::LegacyTelemetryEventPacket::PlayerDied, v827::LegacyTelemetryEventPacket::BossKilled, v827::LegacyTelemetryEventPacket::SlashCommand, v827::LegacyTelemetryEventPacket::MobBorn, v827::LegacyTelemetryEventPacket::POICauldronUsed, v827::LegacyTelemetryEventPacket::ComposterUsed, v827::LegacyTelemetryEventPacket::BellUsed, v827::LegacyTelemetryEventPacket::ActorDefinition, v827::LegacyTelemetryEventPacket::RaidUpdate, v827::LegacyTelemetryEventPacket::TargetBlockHit, v827::LegacyTelemetryEventPacket::PiglinBarter, v827::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v827::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v827::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v827::LegacyTelemetryEventPacket::ItemUsed, v827::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v827::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<18>(alt0);
                break;
            }
            case 19: {
                std::variant_alternative_t<19, std::variant<v827::LegacyTelemetryEventPacket::Achievement, v827::LegacyTelemetryEventPacket::Interaction, v827::LegacyTelemetryEventPacket::PortalCreated, v827::LegacyTelemetryEventPacket::PortalUsed, v827::LegacyTelemetryEventPacket::MobKilled, v827::LegacyTelemetryEventPacket::CauldronUsed, v827::LegacyTelemetryEventPacket::PlayerDied, v827::LegacyTelemetryEventPacket::BossKilled, v827::LegacyTelemetryEventPacket::SlashCommand, v827::LegacyTelemetryEventPacket::MobBorn, v827::LegacyTelemetryEventPacket::POICauldronUsed, v827::LegacyTelemetryEventPacket::ComposterUsed, v827::LegacyTelemetryEventPacket::BellUsed, v827::LegacyTelemetryEventPacket::ActorDefinition, v827::LegacyTelemetryEventPacket::RaidUpdate, v827::LegacyTelemetryEventPacket::TargetBlockHit, v827::LegacyTelemetryEventPacket::PiglinBarter, v827::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v827::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v827::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v827::LegacyTelemetryEventPacket::ItemUsed, v827::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v827::LegacyTelemetryEventPacket::CodeBuilderScoreboard>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<19>(alt0);
                break;
            }
            case 20: {
                std::variant_alternative_t<20, std::variant<v827::LegacyTelemetryEventPacket::Achievement, v827::LegacyTelemetryEventPacket::Interaction, v827::LegacyTelemetryEventPacket::PortalCreated, v827::LegacyTelemetryEventPacket::PortalUsed, v827::LegacyTelemetryEventPacket::MobKilled, v827::LegacyTelemetryEventPacket::CauldronUsed, v827::LegacyTelemetryEventPacket::PlayerDied, v827::LegacyTelemetryEventPacket::BossKilled, v827::LegacyTelemetryEventPacket::SlashCommand, v827::LegacyTelemetryEventPacket::MobBorn, v827::LegacyTelemetryEventPacket::POICauldronUsed, v827::LegacyTelemetryEventPacket::ComposterUsed, v827::LegacyTelemetryEventPacket::BellUsed, v827::LegacyTelemetryEventPacket::ActorDefinition, v827::LegacyTelemetryEventPacket::RaidUpdate, v827::LegacyTelemetryEventPacket::TargetBlockHit, v827::LegacyTelemetryEventPacket::PiglinBarter, v827::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v827::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v827::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v827::LegacyTelemetryEventPacket::ItemUsed, v827::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v827::LegacyTelemetryEventPacket::ItemUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<20>(alt0);
                break;
            }
            case 21: {
                std::variant_alternative_t<21, std::variant<v827::LegacyTelemetryEventPacket::Achievement, v827::LegacyTelemetryEventPacket::Interaction, v827::LegacyTelemetryEventPacket::PortalCreated, v827::LegacyTelemetryEventPacket::PortalUsed, v827::LegacyTelemetryEventPacket::MobKilled, v827::LegacyTelemetryEventPacket::CauldronUsed, v827::LegacyTelemetryEventPacket::PlayerDied, v827::LegacyTelemetryEventPacket::BossKilled, v827::LegacyTelemetryEventPacket::SlashCommand, v827::LegacyTelemetryEventPacket::MobBorn, v827::LegacyTelemetryEventPacket::POICauldronUsed, v827::LegacyTelemetryEventPacket::ComposterUsed, v827::LegacyTelemetryEventPacket::BellUsed, v827::LegacyTelemetryEventPacket::ActorDefinition, v827::LegacyTelemetryEventPacket::RaidUpdate, v827::LegacyTelemetryEventPacket::TargetBlockHit, v827::LegacyTelemetryEventPacket::PiglinBarter, v827::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v827::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v827::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v827::LegacyTelemetryEventPacket::ItemUsed, v827::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v827::LegacyTelemetryEventPacket::Empty>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<21>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.event_data = var0;
    }
    return out;
}

void Serializer<v898::LegacyTelemetryEventPacket>::serialize(BinaryWriter &stream, const v898::LegacyTelemetryEventPacket &value)
{
    stream.writeVarInt<std::int64_t>(value.player_unique_id);
    stream.writeVarInt<std::int32_t>(value.type);
    stream.write<bool>(value.use_player_id);
    stream.writeVarInt<std::uint32_t>((value.event_data).index());
    switch ((value.event_data).index()) {
        case 0: {
            Serializer<v898::LegacyTelemetryEventPacket::Achievement>::serialize(stream, std::get<0>(value.event_data));
            break;
        }
        case 1: {
            Serializer<v898::LegacyTelemetryEventPacket::Interaction>::serialize(stream, std::get<1>(value.event_data));
            break;
        }
        case 2: {
            Serializer<v898::LegacyTelemetryEventPacket::PortalCreated>::serialize(stream, std::get<2>(value.event_data));
            break;
        }
        case 3: {
            Serializer<v898::LegacyTelemetryEventPacket::PortalUsed>::serialize(stream, std::get<3>(value.event_data));
            break;
        }
        case 4: {
            Serializer<v898::LegacyTelemetryEventPacket::MobKilled>::serialize(stream, std::get<4>(value.event_data));
            break;
        }
        case 5: {
            Serializer<v898::LegacyTelemetryEventPacket::CauldronUsed>::serialize(stream, std::get<5>(value.event_data));
            break;
        }
        case 6: {
            Serializer<v898::LegacyTelemetryEventPacket::PlayerDied>::serialize(stream, std::get<6>(value.event_data));
            break;
        }
        case 7: {
            Serializer<v898::LegacyTelemetryEventPacket::BossKilled>::serialize(stream, std::get<7>(value.event_data));
            break;
        }
        case 8: {
            Serializer<v898::LegacyTelemetryEventPacket::SlashCommand>::serialize(stream, std::get<8>(value.event_data));
            break;
        }
        case 9: {
            Serializer<v898::LegacyTelemetryEventPacket::MobBorn>::serialize(stream, std::get<9>(value.event_data));
            break;
        }
        case 10: {
            Serializer<v898::LegacyTelemetryEventPacket::POICauldronUsed>::serialize(stream, std::get<10>(value.event_data));
            break;
        }
        case 11: {
            Serializer<v898::LegacyTelemetryEventPacket::ComposterUsed>::serialize(stream, std::get<11>(value.event_data));
            break;
        }
        case 12: {
            Serializer<v898::LegacyTelemetryEventPacket::BellUsed>::serialize(stream, std::get<12>(value.event_data));
            break;
        }
        case 13: {
            Serializer<v898::LegacyTelemetryEventPacket::ActorDefinition>::serialize(stream, std::get<13>(value.event_data));
            break;
        }
        case 14: {
            Serializer<v898::LegacyTelemetryEventPacket::RaidUpdate>::serialize(stream, std::get<14>(value.event_data));
            break;
        }
        case 15: {
            Serializer<v898::LegacyTelemetryEventPacket::TargetBlockHit>::serialize(stream, std::get<15>(value.event_data));
            break;
        }
        case 16: {
            Serializer<v898::LegacyTelemetryEventPacket::PiglinBarter>::serialize(stream, std::get<16>(value.event_data));
            break;
        }
        case 17: {
            Serializer<v898::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper>::serialize(stream, std::get<17>(value.event_data));
            break;
        }
        case 18: {
            Serializer<v898::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction>::serialize(stream, std::get<18>(value.event_data));
            break;
        }
        case 19: {
            Serializer<v898::LegacyTelemetryEventPacket::CodeBuilderScoreboard>::serialize(stream, std::get<19>(value.event_data));
            break;
        }
        case 20: {
            Serializer<v898::LegacyTelemetryEventPacket::ItemUsed>::serialize(stream, std::get<20>(value.event_data));
            break;
        }
        case 21: {
            Serializer<v898::LegacyTelemetryEventPacket::Empty>::serialize(stream, std::get<21>(value.event_data));
            break;
        }
    }
}

auto Serializer<v898::LegacyTelemetryEventPacket>::deserialize(BinaryReader &stream) -> std::expected<v898::LegacyTelemetryEventPacket, std::error_code>
{
    v898::LegacyTelemetryEventPacket out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.player_unique_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<v898::LegacyTelemetryEventPacket::Type>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.use_player_id = static_cast<bool>(*v);
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v898::LegacyTelemetryEventPacket::Achievement, v898::LegacyTelemetryEventPacket::Interaction, v898::LegacyTelemetryEventPacket::PortalCreated, v898::LegacyTelemetryEventPacket::PortalUsed, v898::LegacyTelemetryEventPacket::MobKilled, v898::LegacyTelemetryEventPacket::CauldronUsed, v898::LegacyTelemetryEventPacket::PlayerDied, v898::LegacyTelemetryEventPacket::BossKilled, v898::LegacyTelemetryEventPacket::SlashCommand, v898::LegacyTelemetryEventPacket::MobBorn, v898::LegacyTelemetryEventPacket::POICauldronUsed, v898::LegacyTelemetryEventPacket::ComposterUsed, v898::LegacyTelemetryEventPacket::BellUsed, v898::LegacyTelemetryEventPacket::ActorDefinition, v898::LegacyTelemetryEventPacket::RaidUpdate, v898::LegacyTelemetryEventPacket::TargetBlockHit, v898::LegacyTelemetryEventPacket::PiglinBarter, v898::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v898::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v898::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v898::LegacyTelemetryEventPacket::ItemUsed, v898::LegacyTelemetryEventPacket::Empty> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v898::LegacyTelemetryEventPacket::Achievement, v898::LegacyTelemetryEventPacket::Interaction, v898::LegacyTelemetryEventPacket::PortalCreated, v898::LegacyTelemetryEventPacket::PortalUsed, v898::LegacyTelemetryEventPacket::MobKilled, v898::LegacyTelemetryEventPacket::CauldronUsed, v898::LegacyTelemetryEventPacket::PlayerDied, v898::LegacyTelemetryEventPacket::BossKilled, v898::LegacyTelemetryEventPacket::SlashCommand, v898::LegacyTelemetryEventPacket::MobBorn, v898::LegacyTelemetryEventPacket::POICauldronUsed, v898::LegacyTelemetryEventPacket::ComposterUsed, v898::LegacyTelemetryEventPacket::BellUsed, v898::LegacyTelemetryEventPacket::ActorDefinition, v898::LegacyTelemetryEventPacket::RaidUpdate, v898::LegacyTelemetryEventPacket::TargetBlockHit, v898::LegacyTelemetryEventPacket::PiglinBarter, v898::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v898::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v898::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v898::LegacyTelemetryEventPacket::ItemUsed, v898::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v898::LegacyTelemetryEventPacket::Achievement>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v898::LegacyTelemetryEventPacket::Achievement, v898::LegacyTelemetryEventPacket::Interaction, v898::LegacyTelemetryEventPacket::PortalCreated, v898::LegacyTelemetryEventPacket::PortalUsed, v898::LegacyTelemetryEventPacket::MobKilled, v898::LegacyTelemetryEventPacket::CauldronUsed, v898::LegacyTelemetryEventPacket::PlayerDied, v898::LegacyTelemetryEventPacket::BossKilled, v898::LegacyTelemetryEventPacket::SlashCommand, v898::LegacyTelemetryEventPacket::MobBorn, v898::LegacyTelemetryEventPacket::POICauldronUsed, v898::LegacyTelemetryEventPacket::ComposterUsed, v898::LegacyTelemetryEventPacket::BellUsed, v898::LegacyTelemetryEventPacket::ActorDefinition, v898::LegacyTelemetryEventPacket::RaidUpdate, v898::LegacyTelemetryEventPacket::TargetBlockHit, v898::LegacyTelemetryEventPacket::PiglinBarter, v898::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v898::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v898::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v898::LegacyTelemetryEventPacket::ItemUsed, v898::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v898::LegacyTelemetryEventPacket::Interaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<v898::LegacyTelemetryEventPacket::Achievement, v898::LegacyTelemetryEventPacket::Interaction, v898::LegacyTelemetryEventPacket::PortalCreated, v898::LegacyTelemetryEventPacket::PortalUsed, v898::LegacyTelemetryEventPacket::MobKilled, v898::LegacyTelemetryEventPacket::CauldronUsed, v898::LegacyTelemetryEventPacket::PlayerDied, v898::LegacyTelemetryEventPacket::BossKilled, v898::LegacyTelemetryEventPacket::SlashCommand, v898::LegacyTelemetryEventPacket::MobBorn, v898::LegacyTelemetryEventPacket::POICauldronUsed, v898::LegacyTelemetryEventPacket::ComposterUsed, v898::LegacyTelemetryEventPacket::BellUsed, v898::LegacyTelemetryEventPacket::ActorDefinition, v898::LegacyTelemetryEventPacket::RaidUpdate, v898::LegacyTelemetryEventPacket::TargetBlockHit, v898::LegacyTelemetryEventPacket::PiglinBarter, v898::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v898::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v898::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v898::LegacyTelemetryEventPacket::ItemUsed, v898::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v898::LegacyTelemetryEventPacket::PortalCreated>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<v898::LegacyTelemetryEventPacket::Achievement, v898::LegacyTelemetryEventPacket::Interaction, v898::LegacyTelemetryEventPacket::PortalCreated, v898::LegacyTelemetryEventPacket::PortalUsed, v898::LegacyTelemetryEventPacket::MobKilled, v898::LegacyTelemetryEventPacket::CauldronUsed, v898::LegacyTelemetryEventPacket::PlayerDied, v898::LegacyTelemetryEventPacket::BossKilled, v898::LegacyTelemetryEventPacket::SlashCommand, v898::LegacyTelemetryEventPacket::MobBorn, v898::LegacyTelemetryEventPacket::POICauldronUsed, v898::LegacyTelemetryEventPacket::ComposterUsed, v898::LegacyTelemetryEventPacket::BellUsed, v898::LegacyTelemetryEventPacket::ActorDefinition, v898::LegacyTelemetryEventPacket::RaidUpdate, v898::LegacyTelemetryEventPacket::TargetBlockHit, v898::LegacyTelemetryEventPacket::PiglinBarter, v898::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v898::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v898::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v898::LegacyTelemetryEventPacket::ItemUsed, v898::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v898::LegacyTelemetryEventPacket::PortalUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            case 4: {
                std::variant_alternative_t<4, std::variant<v898::LegacyTelemetryEventPacket::Achievement, v898::LegacyTelemetryEventPacket::Interaction, v898::LegacyTelemetryEventPacket::PortalCreated, v898::LegacyTelemetryEventPacket::PortalUsed, v898::LegacyTelemetryEventPacket::MobKilled, v898::LegacyTelemetryEventPacket::CauldronUsed, v898::LegacyTelemetryEventPacket::PlayerDied, v898::LegacyTelemetryEventPacket::BossKilled, v898::LegacyTelemetryEventPacket::SlashCommand, v898::LegacyTelemetryEventPacket::MobBorn, v898::LegacyTelemetryEventPacket::POICauldronUsed, v898::LegacyTelemetryEventPacket::ComposterUsed, v898::LegacyTelemetryEventPacket::BellUsed, v898::LegacyTelemetryEventPacket::ActorDefinition, v898::LegacyTelemetryEventPacket::RaidUpdate, v898::LegacyTelemetryEventPacket::TargetBlockHit, v898::LegacyTelemetryEventPacket::PiglinBarter, v898::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v898::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v898::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v898::LegacyTelemetryEventPacket::ItemUsed, v898::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v898::LegacyTelemetryEventPacket::MobKilled>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<4>(alt0);
                break;
            }
            case 5: {
                std::variant_alternative_t<5, std::variant<v898::LegacyTelemetryEventPacket::Achievement, v898::LegacyTelemetryEventPacket::Interaction, v898::LegacyTelemetryEventPacket::PortalCreated, v898::LegacyTelemetryEventPacket::PortalUsed, v898::LegacyTelemetryEventPacket::MobKilled, v898::LegacyTelemetryEventPacket::CauldronUsed, v898::LegacyTelemetryEventPacket::PlayerDied, v898::LegacyTelemetryEventPacket::BossKilled, v898::LegacyTelemetryEventPacket::SlashCommand, v898::LegacyTelemetryEventPacket::MobBorn, v898::LegacyTelemetryEventPacket::POICauldronUsed, v898::LegacyTelemetryEventPacket::ComposterUsed, v898::LegacyTelemetryEventPacket::BellUsed, v898::LegacyTelemetryEventPacket::ActorDefinition, v898::LegacyTelemetryEventPacket::RaidUpdate, v898::LegacyTelemetryEventPacket::TargetBlockHit, v898::LegacyTelemetryEventPacket::PiglinBarter, v898::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v898::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v898::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v898::LegacyTelemetryEventPacket::ItemUsed, v898::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v898::LegacyTelemetryEventPacket::CauldronUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<5>(alt0);
                break;
            }
            case 6: {
                std::variant_alternative_t<6, std::variant<v898::LegacyTelemetryEventPacket::Achievement, v898::LegacyTelemetryEventPacket::Interaction, v898::LegacyTelemetryEventPacket::PortalCreated, v898::LegacyTelemetryEventPacket::PortalUsed, v898::LegacyTelemetryEventPacket::MobKilled, v898::LegacyTelemetryEventPacket::CauldronUsed, v898::LegacyTelemetryEventPacket::PlayerDied, v898::LegacyTelemetryEventPacket::BossKilled, v898::LegacyTelemetryEventPacket::SlashCommand, v898::LegacyTelemetryEventPacket::MobBorn, v898::LegacyTelemetryEventPacket::POICauldronUsed, v898::LegacyTelemetryEventPacket::ComposterUsed, v898::LegacyTelemetryEventPacket::BellUsed, v898::LegacyTelemetryEventPacket::ActorDefinition, v898::LegacyTelemetryEventPacket::RaidUpdate, v898::LegacyTelemetryEventPacket::TargetBlockHit, v898::LegacyTelemetryEventPacket::PiglinBarter, v898::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v898::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v898::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v898::LegacyTelemetryEventPacket::ItemUsed, v898::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v898::LegacyTelemetryEventPacket::PlayerDied>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<6>(alt0);
                break;
            }
            case 7: {
                std::variant_alternative_t<7, std::variant<v898::LegacyTelemetryEventPacket::Achievement, v898::LegacyTelemetryEventPacket::Interaction, v898::LegacyTelemetryEventPacket::PortalCreated, v898::LegacyTelemetryEventPacket::PortalUsed, v898::LegacyTelemetryEventPacket::MobKilled, v898::LegacyTelemetryEventPacket::CauldronUsed, v898::LegacyTelemetryEventPacket::PlayerDied, v898::LegacyTelemetryEventPacket::BossKilled, v898::LegacyTelemetryEventPacket::SlashCommand, v898::LegacyTelemetryEventPacket::MobBorn, v898::LegacyTelemetryEventPacket::POICauldronUsed, v898::LegacyTelemetryEventPacket::ComposterUsed, v898::LegacyTelemetryEventPacket::BellUsed, v898::LegacyTelemetryEventPacket::ActorDefinition, v898::LegacyTelemetryEventPacket::RaidUpdate, v898::LegacyTelemetryEventPacket::TargetBlockHit, v898::LegacyTelemetryEventPacket::PiglinBarter, v898::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v898::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v898::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v898::LegacyTelemetryEventPacket::ItemUsed, v898::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v898::LegacyTelemetryEventPacket::BossKilled>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<7>(alt0);
                break;
            }
            case 8: {
                std::variant_alternative_t<8, std::variant<v898::LegacyTelemetryEventPacket::Achievement, v898::LegacyTelemetryEventPacket::Interaction, v898::LegacyTelemetryEventPacket::PortalCreated, v898::LegacyTelemetryEventPacket::PortalUsed, v898::LegacyTelemetryEventPacket::MobKilled, v898::LegacyTelemetryEventPacket::CauldronUsed, v898::LegacyTelemetryEventPacket::PlayerDied, v898::LegacyTelemetryEventPacket::BossKilled, v898::LegacyTelemetryEventPacket::SlashCommand, v898::LegacyTelemetryEventPacket::MobBorn, v898::LegacyTelemetryEventPacket::POICauldronUsed, v898::LegacyTelemetryEventPacket::ComposterUsed, v898::LegacyTelemetryEventPacket::BellUsed, v898::LegacyTelemetryEventPacket::ActorDefinition, v898::LegacyTelemetryEventPacket::RaidUpdate, v898::LegacyTelemetryEventPacket::TargetBlockHit, v898::LegacyTelemetryEventPacket::PiglinBarter, v898::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v898::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v898::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v898::LegacyTelemetryEventPacket::ItemUsed, v898::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v898::LegacyTelemetryEventPacket::SlashCommand>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<8>(alt0);
                break;
            }
            case 9: {
                std::variant_alternative_t<9, std::variant<v898::LegacyTelemetryEventPacket::Achievement, v898::LegacyTelemetryEventPacket::Interaction, v898::LegacyTelemetryEventPacket::PortalCreated, v898::LegacyTelemetryEventPacket::PortalUsed, v898::LegacyTelemetryEventPacket::MobKilled, v898::LegacyTelemetryEventPacket::CauldronUsed, v898::LegacyTelemetryEventPacket::PlayerDied, v898::LegacyTelemetryEventPacket::BossKilled, v898::LegacyTelemetryEventPacket::SlashCommand, v898::LegacyTelemetryEventPacket::MobBorn, v898::LegacyTelemetryEventPacket::POICauldronUsed, v898::LegacyTelemetryEventPacket::ComposterUsed, v898::LegacyTelemetryEventPacket::BellUsed, v898::LegacyTelemetryEventPacket::ActorDefinition, v898::LegacyTelemetryEventPacket::RaidUpdate, v898::LegacyTelemetryEventPacket::TargetBlockHit, v898::LegacyTelemetryEventPacket::PiglinBarter, v898::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v898::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v898::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v898::LegacyTelemetryEventPacket::ItemUsed, v898::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v898::LegacyTelemetryEventPacket::MobBorn>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<9>(alt0);
                break;
            }
            case 10: {
                std::variant_alternative_t<10, std::variant<v898::LegacyTelemetryEventPacket::Achievement, v898::LegacyTelemetryEventPacket::Interaction, v898::LegacyTelemetryEventPacket::PortalCreated, v898::LegacyTelemetryEventPacket::PortalUsed, v898::LegacyTelemetryEventPacket::MobKilled, v898::LegacyTelemetryEventPacket::CauldronUsed, v898::LegacyTelemetryEventPacket::PlayerDied, v898::LegacyTelemetryEventPacket::BossKilled, v898::LegacyTelemetryEventPacket::SlashCommand, v898::LegacyTelemetryEventPacket::MobBorn, v898::LegacyTelemetryEventPacket::POICauldronUsed, v898::LegacyTelemetryEventPacket::ComposterUsed, v898::LegacyTelemetryEventPacket::BellUsed, v898::LegacyTelemetryEventPacket::ActorDefinition, v898::LegacyTelemetryEventPacket::RaidUpdate, v898::LegacyTelemetryEventPacket::TargetBlockHit, v898::LegacyTelemetryEventPacket::PiglinBarter, v898::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v898::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v898::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v898::LegacyTelemetryEventPacket::ItemUsed, v898::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v898::LegacyTelemetryEventPacket::POICauldronUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<10>(alt0);
                break;
            }
            case 11: {
                std::variant_alternative_t<11, std::variant<v898::LegacyTelemetryEventPacket::Achievement, v898::LegacyTelemetryEventPacket::Interaction, v898::LegacyTelemetryEventPacket::PortalCreated, v898::LegacyTelemetryEventPacket::PortalUsed, v898::LegacyTelemetryEventPacket::MobKilled, v898::LegacyTelemetryEventPacket::CauldronUsed, v898::LegacyTelemetryEventPacket::PlayerDied, v898::LegacyTelemetryEventPacket::BossKilled, v898::LegacyTelemetryEventPacket::SlashCommand, v898::LegacyTelemetryEventPacket::MobBorn, v898::LegacyTelemetryEventPacket::POICauldronUsed, v898::LegacyTelemetryEventPacket::ComposterUsed, v898::LegacyTelemetryEventPacket::BellUsed, v898::LegacyTelemetryEventPacket::ActorDefinition, v898::LegacyTelemetryEventPacket::RaidUpdate, v898::LegacyTelemetryEventPacket::TargetBlockHit, v898::LegacyTelemetryEventPacket::PiglinBarter, v898::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v898::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v898::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v898::LegacyTelemetryEventPacket::ItemUsed, v898::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v898::LegacyTelemetryEventPacket::ComposterUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<11>(alt0);
                break;
            }
            case 12: {
                std::variant_alternative_t<12, std::variant<v898::LegacyTelemetryEventPacket::Achievement, v898::LegacyTelemetryEventPacket::Interaction, v898::LegacyTelemetryEventPacket::PortalCreated, v898::LegacyTelemetryEventPacket::PortalUsed, v898::LegacyTelemetryEventPacket::MobKilled, v898::LegacyTelemetryEventPacket::CauldronUsed, v898::LegacyTelemetryEventPacket::PlayerDied, v898::LegacyTelemetryEventPacket::BossKilled, v898::LegacyTelemetryEventPacket::SlashCommand, v898::LegacyTelemetryEventPacket::MobBorn, v898::LegacyTelemetryEventPacket::POICauldronUsed, v898::LegacyTelemetryEventPacket::ComposterUsed, v898::LegacyTelemetryEventPacket::BellUsed, v898::LegacyTelemetryEventPacket::ActorDefinition, v898::LegacyTelemetryEventPacket::RaidUpdate, v898::LegacyTelemetryEventPacket::TargetBlockHit, v898::LegacyTelemetryEventPacket::PiglinBarter, v898::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v898::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v898::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v898::LegacyTelemetryEventPacket::ItemUsed, v898::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v898::LegacyTelemetryEventPacket::BellUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<12>(alt0);
                break;
            }
            case 13: {
                std::variant_alternative_t<13, std::variant<v898::LegacyTelemetryEventPacket::Achievement, v898::LegacyTelemetryEventPacket::Interaction, v898::LegacyTelemetryEventPacket::PortalCreated, v898::LegacyTelemetryEventPacket::PortalUsed, v898::LegacyTelemetryEventPacket::MobKilled, v898::LegacyTelemetryEventPacket::CauldronUsed, v898::LegacyTelemetryEventPacket::PlayerDied, v898::LegacyTelemetryEventPacket::BossKilled, v898::LegacyTelemetryEventPacket::SlashCommand, v898::LegacyTelemetryEventPacket::MobBorn, v898::LegacyTelemetryEventPacket::POICauldronUsed, v898::LegacyTelemetryEventPacket::ComposterUsed, v898::LegacyTelemetryEventPacket::BellUsed, v898::LegacyTelemetryEventPacket::ActorDefinition, v898::LegacyTelemetryEventPacket::RaidUpdate, v898::LegacyTelemetryEventPacket::TargetBlockHit, v898::LegacyTelemetryEventPacket::PiglinBarter, v898::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v898::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v898::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v898::LegacyTelemetryEventPacket::ItemUsed, v898::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v898::LegacyTelemetryEventPacket::ActorDefinition>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<13>(alt0);
                break;
            }
            case 14: {
                std::variant_alternative_t<14, std::variant<v898::LegacyTelemetryEventPacket::Achievement, v898::LegacyTelemetryEventPacket::Interaction, v898::LegacyTelemetryEventPacket::PortalCreated, v898::LegacyTelemetryEventPacket::PortalUsed, v898::LegacyTelemetryEventPacket::MobKilled, v898::LegacyTelemetryEventPacket::CauldronUsed, v898::LegacyTelemetryEventPacket::PlayerDied, v898::LegacyTelemetryEventPacket::BossKilled, v898::LegacyTelemetryEventPacket::SlashCommand, v898::LegacyTelemetryEventPacket::MobBorn, v898::LegacyTelemetryEventPacket::POICauldronUsed, v898::LegacyTelemetryEventPacket::ComposterUsed, v898::LegacyTelemetryEventPacket::BellUsed, v898::LegacyTelemetryEventPacket::ActorDefinition, v898::LegacyTelemetryEventPacket::RaidUpdate, v898::LegacyTelemetryEventPacket::TargetBlockHit, v898::LegacyTelemetryEventPacket::PiglinBarter, v898::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v898::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v898::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v898::LegacyTelemetryEventPacket::ItemUsed, v898::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v898::LegacyTelemetryEventPacket::RaidUpdate>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<14>(alt0);
                break;
            }
            case 15: {
                std::variant_alternative_t<15, std::variant<v898::LegacyTelemetryEventPacket::Achievement, v898::LegacyTelemetryEventPacket::Interaction, v898::LegacyTelemetryEventPacket::PortalCreated, v898::LegacyTelemetryEventPacket::PortalUsed, v898::LegacyTelemetryEventPacket::MobKilled, v898::LegacyTelemetryEventPacket::CauldronUsed, v898::LegacyTelemetryEventPacket::PlayerDied, v898::LegacyTelemetryEventPacket::BossKilled, v898::LegacyTelemetryEventPacket::SlashCommand, v898::LegacyTelemetryEventPacket::MobBorn, v898::LegacyTelemetryEventPacket::POICauldronUsed, v898::LegacyTelemetryEventPacket::ComposterUsed, v898::LegacyTelemetryEventPacket::BellUsed, v898::LegacyTelemetryEventPacket::ActorDefinition, v898::LegacyTelemetryEventPacket::RaidUpdate, v898::LegacyTelemetryEventPacket::TargetBlockHit, v898::LegacyTelemetryEventPacket::PiglinBarter, v898::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v898::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v898::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v898::LegacyTelemetryEventPacket::ItemUsed, v898::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v898::LegacyTelemetryEventPacket::TargetBlockHit>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<15>(alt0);
                break;
            }
            case 16: {
                std::variant_alternative_t<16, std::variant<v898::LegacyTelemetryEventPacket::Achievement, v898::LegacyTelemetryEventPacket::Interaction, v898::LegacyTelemetryEventPacket::PortalCreated, v898::LegacyTelemetryEventPacket::PortalUsed, v898::LegacyTelemetryEventPacket::MobKilled, v898::LegacyTelemetryEventPacket::CauldronUsed, v898::LegacyTelemetryEventPacket::PlayerDied, v898::LegacyTelemetryEventPacket::BossKilled, v898::LegacyTelemetryEventPacket::SlashCommand, v898::LegacyTelemetryEventPacket::MobBorn, v898::LegacyTelemetryEventPacket::POICauldronUsed, v898::LegacyTelemetryEventPacket::ComposterUsed, v898::LegacyTelemetryEventPacket::BellUsed, v898::LegacyTelemetryEventPacket::ActorDefinition, v898::LegacyTelemetryEventPacket::RaidUpdate, v898::LegacyTelemetryEventPacket::TargetBlockHit, v898::LegacyTelemetryEventPacket::PiglinBarter, v898::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v898::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v898::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v898::LegacyTelemetryEventPacket::ItemUsed, v898::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v898::LegacyTelemetryEventPacket::PiglinBarter>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<16>(alt0);
                break;
            }
            case 17: {
                std::variant_alternative_t<17, std::variant<v898::LegacyTelemetryEventPacket::Achievement, v898::LegacyTelemetryEventPacket::Interaction, v898::LegacyTelemetryEventPacket::PortalCreated, v898::LegacyTelemetryEventPacket::PortalUsed, v898::LegacyTelemetryEventPacket::MobKilled, v898::LegacyTelemetryEventPacket::CauldronUsed, v898::LegacyTelemetryEventPacket::PlayerDied, v898::LegacyTelemetryEventPacket::BossKilled, v898::LegacyTelemetryEventPacket::SlashCommand, v898::LegacyTelemetryEventPacket::MobBorn, v898::LegacyTelemetryEventPacket::POICauldronUsed, v898::LegacyTelemetryEventPacket::ComposterUsed, v898::LegacyTelemetryEventPacket::BellUsed, v898::LegacyTelemetryEventPacket::ActorDefinition, v898::LegacyTelemetryEventPacket::RaidUpdate, v898::LegacyTelemetryEventPacket::TargetBlockHit, v898::LegacyTelemetryEventPacket::PiglinBarter, v898::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v898::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v898::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v898::LegacyTelemetryEventPacket::ItemUsed, v898::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v898::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<17>(alt0);
                break;
            }
            case 18: {
                std::variant_alternative_t<18, std::variant<v898::LegacyTelemetryEventPacket::Achievement, v898::LegacyTelemetryEventPacket::Interaction, v898::LegacyTelemetryEventPacket::PortalCreated, v898::LegacyTelemetryEventPacket::PortalUsed, v898::LegacyTelemetryEventPacket::MobKilled, v898::LegacyTelemetryEventPacket::CauldronUsed, v898::LegacyTelemetryEventPacket::PlayerDied, v898::LegacyTelemetryEventPacket::BossKilled, v898::LegacyTelemetryEventPacket::SlashCommand, v898::LegacyTelemetryEventPacket::MobBorn, v898::LegacyTelemetryEventPacket::POICauldronUsed, v898::LegacyTelemetryEventPacket::ComposterUsed, v898::LegacyTelemetryEventPacket::BellUsed, v898::LegacyTelemetryEventPacket::ActorDefinition, v898::LegacyTelemetryEventPacket::RaidUpdate, v898::LegacyTelemetryEventPacket::TargetBlockHit, v898::LegacyTelemetryEventPacket::PiglinBarter, v898::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v898::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v898::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v898::LegacyTelemetryEventPacket::ItemUsed, v898::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v898::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<18>(alt0);
                break;
            }
            case 19: {
                std::variant_alternative_t<19, std::variant<v898::LegacyTelemetryEventPacket::Achievement, v898::LegacyTelemetryEventPacket::Interaction, v898::LegacyTelemetryEventPacket::PortalCreated, v898::LegacyTelemetryEventPacket::PortalUsed, v898::LegacyTelemetryEventPacket::MobKilled, v898::LegacyTelemetryEventPacket::CauldronUsed, v898::LegacyTelemetryEventPacket::PlayerDied, v898::LegacyTelemetryEventPacket::BossKilled, v898::LegacyTelemetryEventPacket::SlashCommand, v898::LegacyTelemetryEventPacket::MobBorn, v898::LegacyTelemetryEventPacket::POICauldronUsed, v898::LegacyTelemetryEventPacket::ComposterUsed, v898::LegacyTelemetryEventPacket::BellUsed, v898::LegacyTelemetryEventPacket::ActorDefinition, v898::LegacyTelemetryEventPacket::RaidUpdate, v898::LegacyTelemetryEventPacket::TargetBlockHit, v898::LegacyTelemetryEventPacket::PiglinBarter, v898::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v898::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v898::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v898::LegacyTelemetryEventPacket::ItemUsed, v898::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v898::LegacyTelemetryEventPacket::CodeBuilderScoreboard>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<19>(alt0);
                break;
            }
            case 20: {
                std::variant_alternative_t<20, std::variant<v898::LegacyTelemetryEventPacket::Achievement, v898::LegacyTelemetryEventPacket::Interaction, v898::LegacyTelemetryEventPacket::PortalCreated, v898::LegacyTelemetryEventPacket::PortalUsed, v898::LegacyTelemetryEventPacket::MobKilled, v898::LegacyTelemetryEventPacket::CauldronUsed, v898::LegacyTelemetryEventPacket::PlayerDied, v898::LegacyTelemetryEventPacket::BossKilled, v898::LegacyTelemetryEventPacket::SlashCommand, v898::LegacyTelemetryEventPacket::MobBorn, v898::LegacyTelemetryEventPacket::POICauldronUsed, v898::LegacyTelemetryEventPacket::ComposterUsed, v898::LegacyTelemetryEventPacket::BellUsed, v898::LegacyTelemetryEventPacket::ActorDefinition, v898::LegacyTelemetryEventPacket::RaidUpdate, v898::LegacyTelemetryEventPacket::TargetBlockHit, v898::LegacyTelemetryEventPacket::PiglinBarter, v898::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v898::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v898::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v898::LegacyTelemetryEventPacket::ItemUsed, v898::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v898::LegacyTelemetryEventPacket::ItemUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<20>(alt0);
                break;
            }
            case 21: {
                std::variant_alternative_t<21, std::variant<v898::LegacyTelemetryEventPacket::Achievement, v898::LegacyTelemetryEventPacket::Interaction, v898::LegacyTelemetryEventPacket::PortalCreated, v898::LegacyTelemetryEventPacket::PortalUsed, v898::LegacyTelemetryEventPacket::MobKilled, v898::LegacyTelemetryEventPacket::CauldronUsed, v898::LegacyTelemetryEventPacket::PlayerDied, v898::LegacyTelemetryEventPacket::BossKilled, v898::LegacyTelemetryEventPacket::SlashCommand, v898::LegacyTelemetryEventPacket::MobBorn, v898::LegacyTelemetryEventPacket::POICauldronUsed, v898::LegacyTelemetryEventPacket::ComposterUsed, v898::LegacyTelemetryEventPacket::BellUsed, v898::LegacyTelemetryEventPacket::ActorDefinition, v898::LegacyTelemetryEventPacket::RaidUpdate, v898::LegacyTelemetryEventPacket::TargetBlockHit, v898::LegacyTelemetryEventPacket::PiglinBarter, v898::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v898::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v898::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v898::LegacyTelemetryEventPacket::ItemUsed, v898::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v898::LegacyTelemetryEventPacket::Empty>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<21>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.event_data = var0;
    }
    return out;
}

void Serializer<v924::LegacyTelemetryEventPacket>::serialize(BinaryWriter &stream, const v924::LegacyTelemetryEventPacket &value)
{
    stream.writeVarInt<std::int64_t>(value.player_unique_id);
    stream.writeVarInt<std::int32_t>(value.type);
    stream.write<bool>(value.use_player_id);
    stream.writeVarInt<std::uint32_t>((value.event_data).index());
    switch ((value.event_data).index()) {
        case 0: {
            Serializer<v924::LegacyTelemetryEventPacket::Achievement>::serialize(stream, std::get<0>(value.event_data));
            break;
        }
        case 1: {
            Serializer<v924::LegacyTelemetryEventPacket::Interaction>::serialize(stream, std::get<1>(value.event_data));
            break;
        }
        case 2: {
            Serializer<v924::LegacyTelemetryEventPacket::PortalCreated>::serialize(stream, std::get<2>(value.event_data));
            break;
        }
        case 3: {
            Serializer<v924::LegacyTelemetryEventPacket::PortalUsed>::serialize(stream, std::get<3>(value.event_data));
            break;
        }
        case 4: {
            Serializer<v924::LegacyTelemetryEventPacket::MobKilled>::serialize(stream, std::get<4>(value.event_data));
            break;
        }
        case 5: {
            Serializer<v924::LegacyTelemetryEventPacket::CauldronUsed>::serialize(stream, std::get<5>(value.event_data));
            break;
        }
        case 6: {
            Serializer<v924::LegacyTelemetryEventPacket::PlayerDied>::serialize(stream, std::get<6>(value.event_data));
            break;
        }
        case 7: {
            Serializer<v924::LegacyTelemetryEventPacket::BossKilled>::serialize(stream, std::get<7>(value.event_data));
            break;
        }
        case 8: {
            Serializer<v924::LegacyTelemetryEventPacket::SlashCommand>::serialize(stream, std::get<8>(value.event_data));
            break;
        }
        case 9: {
            Serializer<v924::LegacyTelemetryEventPacket::MobBorn>::serialize(stream, std::get<9>(value.event_data));
            break;
        }
        case 10: {
            Serializer<v924::LegacyTelemetryEventPacket::POICauldronUsed>::serialize(stream, std::get<10>(value.event_data));
            break;
        }
        case 11: {
            Serializer<v924::LegacyTelemetryEventPacket::ComposterUsed>::serialize(stream, std::get<11>(value.event_data));
            break;
        }
        case 12: {
            Serializer<v924::LegacyTelemetryEventPacket::BellUsed>::serialize(stream, std::get<12>(value.event_data));
            break;
        }
        case 13: {
            Serializer<v924::LegacyTelemetryEventPacket::ActorDefinition>::serialize(stream, std::get<13>(value.event_data));
            break;
        }
        case 14: {
            Serializer<v924::LegacyTelemetryEventPacket::RaidUpdate>::serialize(stream, std::get<14>(value.event_data));
            break;
        }
        case 15: {
            Serializer<v924::LegacyTelemetryEventPacket::TargetBlockHit>::serialize(stream, std::get<15>(value.event_data));
            break;
        }
        case 16: {
            Serializer<v924::LegacyTelemetryEventPacket::PiglinBarter>::serialize(stream, std::get<16>(value.event_data));
            break;
        }
        case 17: {
            Serializer<v924::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper>::serialize(stream, std::get<17>(value.event_data));
            break;
        }
        case 18: {
            Serializer<v924::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction>::serialize(stream, std::get<18>(value.event_data));
            break;
        }
        case 19: {
            Serializer<v924::LegacyTelemetryEventPacket::CodeBuilderScoreboard>::serialize(stream, std::get<19>(value.event_data));
            break;
        }
        case 20: {
            Serializer<v924::LegacyTelemetryEventPacket::ItemUsed>::serialize(stream, std::get<20>(value.event_data));
            break;
        }
        case 21: {
            Serializer<v924::LegacyTelemetryEventPacket::Empty>::serialize(stream, std::get<21>(value.event_data));
            break;
        }
    }
}

auto Serializer<v924::LegacyTelemetryEventPacket>::deserialize(BinaryReader &stream) -> std::expected<v924::LegacyTelemetryEventPacket, std::error_code>
{
    v924::LegacyTelemetryEventPacket out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.player_unique_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<v924::LegacyTelemetryEventPacket::Type>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.use_player_id = static_cast<bool>(*v);
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v924::LegacyTelemetryEventPacket::Achievement, v924::LegacyTelemetryEventPacket::Interaction, v924::LegacyTelemetryEventPacket::PortalCreated, v924::LegacyTelemetryEventPacket::PortalUsed, v924::LegacyTelemetryEventPacket::MobKilled, v924::LegacyTelemetryEventPacket::CauldronUsed, v924::LegacyTelemetryEventPacket::PlayerDied, v924::LegacyTelemetryEventPacket::BossKilled, v924::LegacyTelemetryEventPacket::SlashCommand, v924::LegacyTelemetryEventPacket::MobBorn, v924::LegacyTelemetryEventPacket::POICauldronUsed, v924::LegacyTelemetryEventPacket::ComposterUsed, v924::LegacyTelemetryEventPacket::BellUsed, v924::LegacyTelemetryEventPacket::ActorDefinition, v924::LegacyTelemetryEventPacket::RaidUpdate, v924::LegacyTelemetryEventPacket::TargetBlockHit, v924::LegacyTelemetryEventPacket::PiglinBarter, v924::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v924::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v924::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v924::LegacyTelemetryEventPacket::ItemUsed, v924::LegacyTelemetryEventPacket::Empty> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v924::LegacyTelemetryEventPacket::Achievement, v924::LegacyTelemetryEventPacket::Interaction, v924::LegacyTelemetryEventPacket::PortalCreated, v924::LegacyTelemetryEventPacket::PortalUsed, v924::LegacyTelemetryEventPacket::MobKilled, v924::LegacyTelemetryEventPacket::CauldronUsed, v924::LegacyTelemetryEventPacket::PlayerDied, v924::LegacyTelemetryEventPacket::BossKilled, v924::LegacyTelemetryEventPacket::SlashCommand, v924::LegacyTelemetryEventPacket::MobBorn, v924::LegacyTelemetryEventPacket::POICauldronUsed, v924::LegacyTelemetryEventPacket::ComposterUsed, v924::LegacyTelemetryEventPacket::BellUsed, v924::LegacyTelemetryEventPacket::ActorDefinition, v924::LegacyTelemetryEventPacket::RaidUpdate, v924::LegacyTelemetryEventPacket::TargetBlockHit, v924::LegacyTelemetryEventPacket::PiglinBarter, v924::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v924::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v924::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v924::LegacyTelemetryEventPacket::ItemUsed, v924::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v924::LegacyTelemetryEventPacket::Achievement>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v924::LegacyTelemetryEventPacket::Achievement, v924::LegacyTelemetryEventPacket::Interaction, v924::LegacyTelemetryEventPacket::PortalCreated, v924::LegacyTelemetryEventPacket::PortalUsed, v924::LegacyTelemetryEventPacket::MobKilled, v924::LegacyTelemetryEventPacket::CauldronUsed, v924::LegacyTelemetryEventPacket::PlayerDied, v924::LegacyTelemetryEventPacket::BossKilled, v924::LegacyTelemetryEventPacket::SlashCommand, v924::LegacyTelemetryEventPacket::MobBorn, v924::LegacyTelemetryEventPacket::POICauldronUsed, v924::LegacyTelemetryEventPacket::ComposterUsed, v924::LegacyTelemetryEventPacket::BellUsed, v924::LegacyTelemetryEventPacket::ActorDefinition, v924::LegacyTelemetryEventPacket::RaidUpdate, v924::LegacyTelemetryEventPacket::TargetBlockHit, v924::LegacyTelemetryEventPacket::PiglinBarter, v924::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v924::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v924::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v924::LegacyTelemetryEventPacket::ItemUsed, v924::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v924::LegacyTelemetryEventPacket::Interaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<v924::LegacyTelemetryEventPacket::Achievement, v924::LegacyTelemetryEventPacket::Interaction, v924::LegacyTelemetryEventPacket::PortalCreated, v924::LegacyTelemetryEventPacket::PortalUsed, v924::LegacyTelemetryEventPacket::MobKilled, v924::LegacyTelemetryEventPacket::CauldronUsed, v924::LegacyTelemetryEventPacket::PlayerDied, v924::LegacyTelemetryEventPacket::BossKilled, v924::LegacyTelemetryEventPacket::SlashCommand, v924::LegacyTelemetryEventPacket::MobBorn, v924::LegacyTelemetryEventPacket::POICauldronUsed, v924::LegacyTelemetryEventPacket::ComposterUsed, v924::LegacyTelemetryEventPacket::BellUsed, v924::LegacyTelemetryEventPacket::ActorDefinition, v924::LegacyTelemetryEventPacket::RaidUpdate, v924::LegacyTelemetryEventPacket::TargetBlockHit, v924::LegacyTelemetryEventPacket::PiglinBarter, v924::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v924::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v924::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v924::LegacyTelemetryEventPacket::ItemUsed, v924::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v924::LegacyTelemetryEventPacket::PortalCreated>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<v924::LegacyTelemetryEventPacket::Achievement, v924::LegacyTelemetryEventPacket::Interaction, v924::LegacyTelemetryEventPacket::PortalCreated, v924::LegacyTelemetryEventPacket::PortalUsed, v924::LegacyTelemetryEventPacket::MobKilled, v924::LegacyTelemetryEventPacket::CauldronUsed, v924::LegacyTelemetryEventPacket::PlayerDied, v924::LegacyTelemetryEventPacket::BossKilled, v924::LegacyTelemetryEventPacket::SlashCommand, v924::LegacyTelemetryEventPacket::MobBorn, v924::LegacyTelemetryEventPacket::POICauldronUsed, v924::LegacyTelemetryEventPacket::ComposterUsed, v924::LegacyTelemetryEventPacket::BellUsed, v924::LegacyTelemetryEventPacket::ActorDefinition, v924::LegacyTelemetryEventPacket::RaidUpdate, v924::LegacyTelemetryEventPacket::TargetBlockHit, v924::LegacyTelemetryEventPacket::PiglinBarter, v924::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v924::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v924::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v924::LegacyTelemetryEventPacket::ItemUsed, v924::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v924::LegacyTelemetryEventPacket::PortalUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            case 4: {
                std::variant_alternative_t<4, std::variant<v924::LegacyTelemetryEventPacket::Achievement, v924::LegacyTelemetryEventPacket::Interaction, v924::LegacyTelemetryEventPacket::PortalCreated, v924::LegacyTelemetryEventPacket::PortalUsed, v924::LegacyTelemetryEventPacket::MobKilled, v924::LegacyTelemetryEventPacket::CauldronUsed, v924::LegacyTelemetryEventPacket::PlayerDied, v924::LegacyTelemetryEventPacket::BossKilled, v924::LegacyTelemetryEventPacket::SlashCommand, v924::LegacyTelemetryEventPacket::MobBorn, v924::LegacyTelemetryEventPacket::POICauldronUsed, v924::LegacyTelemetryEventPacket::ComposterUsed, v924::LegacyTelemetryEventPacket::BellUsed, v924::LegacyTelemetryEventPacket::ActorDefinition, v924::LegacyTelemetryEventPacket::RaidUpdate, v924::LegacyTelemetryEventPacket::TargetBlockHit, v924::LegacyTelemetryEventPacket::PiglinBarter, v924::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v924::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v924::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v924::LegacyTelemetryEventPacket::ItemUsed, v924::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v924::LegacyTelemetryEventPacket::MobKilled>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<4>(alt0);
                break;
            }
            case 5: {
                std::variant_alternative_t<5, std::variant<v924::LegacyTelemetryEventPacket::Achievement, v924::LegacyTelemetryEventPacket::Interaction, v924::LegacyTelemetryEventPacket::PortalCreated, v924::LegacyTelemetryEventPacket::PortalUsed, v924::LegacyTelemetryEventPacket::MobKilled, v924::LegacyTelemetryEventPacket::CauldronUsed, v924::LegacyTelemetryEventPacket::PlayerDied, v924::LegacyTelemetryEventPacket::BossKilled, v924::LegacyTelemetryEventPacket::SlashCommand, v924::LegacyTelemetryEventPacket::MobBorn, v924::LegacyTelemetryEventPacket::POICauldronUsed, v924::LegacyTelemetryEventPacket::ComposterUsed, v924::LegacyTelemetryEventPacket::BellUsed, v924::LegacyTelemetryEventPacket::ActorDefinition, v924::LegacyTelemetryEventPacket::RaidUpdate, v924::LegacyTelemetryEventPacket::TargetBlockHit, v924::LegacyTelemetryEventPacket::PiglinBarter, v924::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v924::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v924::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v924::LegacyTelemetryEventPacket::ItemUsed, v924::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v924::LegacyTelemetryEventPacket::CauldronUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<5>(alt0);
                break;
            }
            case 6: {
                std::variant_alternative_t<6, std::variant<v924::LegacyTelemetryEventPacket::Achievement, v924::LegacyTelemetryEventPacket::Interaction, v924::LegacyTelemetryEventPacket::PortalCreated, v924::LegacyTelemetryEventPacket::PortalUsed, v924::LegacyTelemetryEventPacket::MobKilled, v924::LegacyTelemetryEventPacket::CauldronUsed, v924::LegacyTelemetryEventPacket::PlayerDied, v924::LegacyTelemetryEventPacket::BossKilled, v924::LegacyTelemetryEventPacket::SlashCommand, v924::LegacyTelemetryEventPacket::MobBorn, v924::LegacyTelemetryEventPacket::POICauldronUsed, v924::LegacyTelemetryEventPacket::ComposterUsed, v924::LegacyTelemetryEventPacket::BellUsed, v924::LegacyTelemetryEventPacket::ActorDefinition, v924::LegacyTelemetryEventPacket::RaidUpdate, v924::LegacyTelemetryEventPacket::TargetBlockHit, v924::LegacyTelemetryEventPacket::PiglinBarter, v924::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v924::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v924::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v924::LegacyTelemetryEventPacket::ItemUsed, v924::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v924::LegacyTelemetryEventPacket::PlayerDied>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<6>(alt0);
                break;
            }
            case 7: {
                std::variant_alternative_t<7, std::variant<v924::LegacyTelemetryEventPacket::Achievement, v924::LegacyTelemetryEventPacket::Interaction, v924::LegacyTelemetryEventPacket::PortalCreated, v924::LegacyTelemetryEventPacket::PortalUsed, v924::LegacyTelemetryEventPacket::MobKilled, v924::LegacyTelemetryEventPacket::CauldronUsed, v924::LegacyTelemetryEventPacket::PlayerDied, v924::LegacyTelemetryEventPacket::BossKilled, v924::LegacyTelemetryEventPacket::SlashCommand, v924::LegacyTelemetryEventPacket::MobBorn, v924::LegacyTelemetryEventPacket::POICauldronUsed, v924::LegacyTelemetryEventPacket::ComposterUsed, v924::LegacyTelemetryEventPacket::BellUsed, v924::LegacyTelemetryEventPacket::ActorDefinition, v924::LegacyTelemetryEventPacket::RaidUpdate, v924::LegacyTelemetryEventPacket::TargetBlockHit, v924::LegacyTelemetryEventPacket::PiglinBarter, v924::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v924::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v924::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v924::LegacyTelemetryEventPacket::ItemUsed, v924::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v924::LegacyTelemetryEventPacket::BossKilled>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<7>(alt0);
                break;
            }
            case 8: {
                std::variant_alternative_t<8, std::variant<v924::LegacyTelemetryEventPacket::Achievement, v924::LegacyTelemetryEventPacket::Interaction, v924::LegacyTelemetryEventPacket::PortalCreated, v924::LegacyTelemetryEventPacket::PortalUsed, v924::LegacyTelemetryEventPacket::MobKilled, v924::LegacyTelemetryEventPacket::CauldronUsed, v924::LegacyTelemetryEventPacket::PlayerDied, v924::LegacyTelemetryEventPacket::BossKilled, v924::LegacyTelemetryEventPacket::SlashCommand, v924::LegacyTelemetryEventPacket::MobBorn, v924::LegacyTelemetryEventPacket::POICauldronUsed, v924::LegacyTelemetryEventPacket::ComposterUsed, v924::LegacyTelemetryEventPacket::BellUsed, v924::LegacyTelemetryEventPacket::ActorDefinition, v924::LegacyTelemetryEventPacket::RaidUpdate, v924::LegacyTelemetryEventPacket::TargetBlockHit, v924::LegacyTelemetryEventPacket::PiglinBarter, v924::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v924::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v924::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v924::LegacyTelemetryEventPacket::ItemUsed, v924::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v924::LegacyTelemetryEventPacket::SlashCommand>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<8>(alt0);
                break;
            }
            case 9: {
                std::variant_alternative_t<9, std::variant<v924::LegacyTelemetryEventPacket::Achievement, v924::LegacyTelemetryEventPacket::Interaction, v924::LegacyTelemetryEventPacket::PortalCreated, v924::LegacyTelemetryEventPacket::PortalUsed, v924::LegacyTelemetryEventPacket::MobKilled, v924::LegacyTelemetryEventPacket::CauldronUsed, v924::LegacyTelemetryEventPacket::PlayerDied, v924::LegacyTelemetryEventPacket::BossKilled, v924::LegacyTelemetryEventPacket::SlashCommand, v924::LegacyTelemetryEventPacket::MobBorn, v924::LegacyTelemetryEventPacket::POICauldronUsed, v924::LegacyTelemetryEventPacket::ComposterUsed, v924::LegacyTelemetryEventPacket::BellUsed, v924::LegacyTelemetryEventPacket::ActorDefinition, v924::LegacyTelemetryEventPacket::RaidUpdate, v924::LegacyTelemetryEventPacket::TargetBlockHit, v924::LegacyTelemetryEventPacket::PiglinBarter, v924::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v924::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v924::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v924::LegacyTelemetryEventPacket::ItemUsed, v924::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v924::LegacyTelemetryEventPacket::MobBorn>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<9>(alt0);
                break;
            }
            case 10: {
                std::variant_alternative_t<10, std::variant<v924::LegacyTelemetryEventPacket::Achievement, v924::LegacyTelemetryEventPacket::Interaction, v924::LegacyTelemetryEventPacket::PortalCreated, v924::LegacyTelemetryEventPacket::PortalUsed, v924::LegacyTelemetryEventPacket::MobKilled, v924::LegacyTelemetryEventPacket::CauldronUsed, v924::LegacyTelemetryEventPacket::PlayerDied, v924::LegacyTelemetryEventPacket::BossKilled, v924::LegacyTelemetryEventPacket::SlashCommand, v924::LegacyTelemetryEventPacket::MobBorn, v924::LegacyTelemetryEventPacket::POICauldronUsed, v924::LegacyTelemetryEventPacket::ComposterUsed, v924::LegacyTelemetryEventPacket::BellUsed, v924::LegacyTelemetryEventPacket::ActorDefinition, v924::LegacyTelemetryEventPacket::RaidUpdate, v924::LegacyTelemetryEventPacket::TargetBlockHit, v924::LegacyTelemetryEventPacket::PiglinBarter, v924::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v924::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v924::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v924::LegacyTelemetryEventPacket::ItemUsed, v924::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v924::LegacyTelemetryEventPacket::POICauldronUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<10>(alt0);
                break;
            }
            case 11: {
                std::variant_alternative_t<11, std::variant<v924::LegacyTelemetryEventPacket::Achievement, v924::LegacyTelemetryEventPacket::Interaction, v924::LegacyTelemetryEventPacket::PortalCreated, v924::LegacyTelemetryEventPacket::PortalUsed, v924::LegacyTelemetryEventPacket::MobKilled, v924::LegacyTelemetryEventPacket::CauldronUsed, v924::LegacyTelemetryEventPacket::PlayerDied, v924::LegacyTelemetryEventPacket::BossKilled, v924::LegacyTelemetryEventPacket::SlashCommand, v924::LegacyTelemetryEventPacket::MobBorn, v924::LegacyTelemetryEventPacket::POICauldronUsed, v924::LegacyTelemetryEventPacket::ComposterUsed, v924::LegacyTelemetryEventPacket::BellUsed, v924::LegacyTelemetryEventPacket::ActorDefinition, v924::LegacyTelemetryEventPacket::RaidUpdate, v924::LegacyTelemetryEventPacket::TargetBlockHit, v924::LegacyTelemetryEventPacket::PiglinBarter, v924::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v924::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v924::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v924::LegacyTelemetryEventPacket::ItemUsed, v924::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v924::LegacyTelemetryEventPacket::ComposterUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<11>(alt0);
                break;
            }
            case 12: {
                std::variant_alternative_t<12, std::variant<v924::LegacyTelemetryEventPacket::Achievement, v924::LegacyTelemetryEventPacket::Interaction, v924::LegacyTelemetryEventPacket::PortalCreated, v924::LegacyTelemetryEventPacket::PortalUsed, v924::LegacyTelemetryEventPacket::MobKilled, v924::LegacyTelemetryEventPacket::CauldronUsed, v924::LegacyTelemetryEventPacket::PlayerDied, v924::LegacyTelemetryEventPacket::BossKilled, v924::LegacyTelemetryEventPacket::SlashCommand, v924::LegacyTelemetryEventPacket::MobBorn, v924::LegacyTelemetryEventPacket::POICauldronUsed, v924::LegacyTelemetryEventPacket::ComposterUsed, v924::LegacyTelemetryEventPacket::BellUsed, v924::LegacyTelemetryEventPacket::ActorDefinition, v924::LegacyTelemetryEventPacket::RaidUpdate, v924::LegacyTelemetryEventPacket::TargetBlockHit, v924::LegacyTelemetryEventPacket::PiglinBarter, v924::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v924::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v924::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v924::LegacyTelemetryEventPacket::ItemUsed, v924::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v924::LegacyTelemetryEventPacket::BellUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<12>(alt0);
                break;
            }
            case 13: {
                std::variant_alternative_t<13, std::variant<v924::LegacyTelemetryEventPacket::Achievement, v924::LegacyTelemetryEventPacket::Interaction, v924::LegacyTelemetryEventPacket::PortalCreated, v924::LegacyTelemetryEventPacket::PortalUsed, v924::LegacyTelemetryEventPacket::MobKilled, v924::LegacyTelemetryEventPacket::CauldronUsed, v924::LegacyTelemetryEventPacket::PlayerDied, v924::LegacyTelemetryEventPacket::BossKilled, v924::LegacyTelemetryEventPacket::SlashCommand, v924::LegacyTelemetryEventPacket::MobBorn, v924::LegacyTelemetryEventPacket::POICauldronUsed, v924::LegacyTelemetryEventPacket::ComposterUsed, v924::LegacyTelemetryEventPacket::BellUsed, v924::LegacyTelemetryEventPacket::ActorDefinition, v924::LegacyTelemetryEventPacket::RaidUpdate, v924::LegacyTelemetryEventPacket::TargetBlockHit, v924::LegacyTelemetryEventPacket::PiglinBarter, v924::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v924::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v924::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v924::LegacyTelemetryEventPacket::ItemUsed, v924::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v924::LegacyTelemetryEventPacket::ActorDefinition>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<13>(alt0);
                break;
            }
            case 14: {
                std::variant_alternative_t<14, std::variant<v924::LegacyTelemetryEventPacket::Achievement, v924::LegacyTelemetryEventPacket::Interaction, v924::LegacyTelemetryEventPacket::PortalCreated, v924::LegacyTelemetryEventPacket::PortalUsed, v924::LegacyTelemetryEventPacket::MobKilled, v924::LegacyTelemetryEventPacket::CauldronUsed, v924::LegacyTelemetryEventPacket::PlayerDied, v924::LegacyTelemetryEventPacket::BossKilled, v924::LegacyTelemetryEventPacket::SlashCommand, v924::LegacyTelemetryEventPacket::MobBorn, v924::LegacyTelemetryEventPacket::POICauldronUsed, v924::LegacyTelemetryEventPacket::ComposterUsed, v924::LegacyTelemetryEventPacket::BellUsed, v924::LegacyTelemetryEventPacket::ActorDefinition, v924::LegacyTelemetryEventPacket::RaidUpdate, v924::LegacyTelemetryEventPacket::TargetBlockHit, v924::LegacyTelemetryEventPacket::PiglinBarter, v924::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v924::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v924::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v924::LegacyTelemetryEventPacket::ItemUsed, v924::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v924::LegacyTelemetryEventPacket::RaidUpdate>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<14>(alt0);
                break;
            }
            case 15: {
                std::variant_alternative_t<15, std::variant<v924::LegacyTelemetryEventPacket::Achievement, v924::LegacyTelemetryEventPacket::Interaction, v924::LegacyTelemetryEventPacket::PortalCreated, v924::LegacyTelemetryEventPacket::PortalUsed, v924::LegacyTelemetryEventPacket::MobKilled, v924::LegacyTelemetryEventPacket::CauldronUsed, v924::LegacyTelemetryEventPacket::PlayerDied, v924::LegacyTelemetryEventPacket::BossKilled, v924::LegacyTelemetryEventPacket::SlashCommand, v924::LegacyTelemetryEventPacket::MobBorn, v924::LegacyTelemetryEventPacket::POICauldronUsed, v924::LegacyTelemetryEventPacket::ComposterUsed, v924::LegacyTelemetryEventPacket::BellUsed, v924::LegacyTelemetryEventPacket::ActorDefinition, v924::LegacyTelemetryEventPacket::RaidUpdate, v924::LegacyTelemetryEventPacket::TargetBlockHit, v924::LegacyTelemetryEventPacket::PiglinBarter, v924::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v924::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v924::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v924::LegacyTelemetryEventPacket::ItemUsed, v924::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v924::LegacyTelemetryEventPacket::TargetBlockHit>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<15>(alt0);
                break;
            }
            case 16: {
                std::variant_alternative_t<16, std::variant<v924::LegacyTelemetryEventPacket::Achievement, v924::LegacyTelemetryEventPacket::Interaction, v924::LegacyTelemetryEventPacket::PortalCreated, v924::LegacyTelemetryEventPacket::PortalUsed, v924::LegacyTelemetryEventPacket::MobKilled, v924::LegacyTelemetryEventPacket::CauldronUsed, v924::LegacyTelemetryEventPacket::PlayerDied, v924::LegacyTelemetryEventPacket::BossKilled, v924::LegacyTelemetryEventPacket::SlashCommand, v924::LegacyTelemetryEventPacket::MobBorn, v924::LegacyTelemetryEventPacket::POICauldronUsed, v924::LegacyTelemetryEventPacket::ComposterUsed, v924::LegacyTelemetryEventPacket::BellUsed, v924::LegacyTelemetryEventPacket::ActorDefinition, v924::LegacyTelemetryEventPacket::RaidUpdate, v924::LegacyTelemetryEventPacket::TargetBlockHit, v924::LegacyTelemetryEventPacket::PiglinBarter, v924::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v924::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v924::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v924::LegacyTelemetryEventPacket::ItemUsed, v924::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v924::LegacyTelemetryEventPacket::PiglinBarter>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<16>(alt0);
                break;
            }
            case 17: {
                std::variant_alternative_t<17, std::variant<v924::LegacyTelemetryEventPacket::Achievement, v924::LegacyTelemetryEventPacket::Interaction, v924::LegacyTelemetryEventPacket::PortalCreated, v924::LegacyTelemetryEventPacket::PortalUsed, v924::LegacyTelemetryEventPacket::MobKilled, v924::LegacyTelemetryEventPacket::CauldronUsed, v924::LegacyTelemetryEventPacket::PlayerDied, v924::LegacyTelemetryEventPacket::BossKilled, v924::LegacyTelemetryEventPacket::SlashCommand, v924::LegacyTelemetryEventPacket::MobBorn, v924::LegacyTelemetryEventPacket::POICauldronUsed, v924::LegacyTelemetryEventPacket::ComposterUsed, v924::LegacyTelemetryEventPacket::BellUsed, v924::LegacyTelemetryEventPacket::ActorDefinition, v924::LegacyTelemetryEventPacket::RaidUpdate, v924::LegacyTelemetryEventPacket::TargetBlockHit, v924::LegacyTelemetryEventPacket::PiglinBarter, v924::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v924::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v924::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v924::LegacyTelemetryEventPacket::ItemUsed, v924::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v924::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<17>(alt0);
                break;
            }
            case 18: {
                std::variant_alternative_t<18, std::variant<v924::LegacyTelemetryEventPacket::Achievement, v924::LegacyTelemetryEventPacket::Interaction, v924::LegacyTelemetryEventPacket::PortalCreated, v924::LegacyTelemetryEventPacket::PortalUsed, v924::LegacyTelemetryEventPacket::MobKilled, v924::LegacyTelemetryEventPacket::CauldronUsed, v924::LegacyTelemetryEventPacket::PlayerDied, v924::LegacyTelemetryEventPacket::BossKilled, v924::LegacyTelemetryEventPacket::SlashCommand, v924::LegacyTelemetryEventPacket::MobBorn, v924::LegacyTelemetryEventPacket::POICauldronUsed, v924::LegacyTelemetryEventPacket::ComposterUsed, v924::LegacyTelemetryEventPacket::BellUsed, v924::LegacyTelemetryEventPacket::ActorDefinition, v924::LegacyTelemetryEventPacket::RaidUpdate, v924::LegacyTelemetryEventPacket::TargetBlockHit, v924::LegacyTelemetryEventPacket::PiglinBarter, v924::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v924::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v924::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v924::LegacyTelemetryEventPacket::ItemUsed, v924::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v924::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<18>(alt0);
                break;
            }
            case 19: {
                std::variant_alternative_t<19, std::variant<v924::LegacyTelemetryEventPacket::Achievement, v924::LegacyTelemetryEventPacket::Interaction, v924::LegacyTelemetryEventPacket::PortalCreated, v924::LegacyTelemetryEventPacket::PortalUsed, v924::LegacyTelemetryEventPacket::MobKilled, v924::LegacyTelemetryEventPacket::CauldronUsed, v924::LegacyTelemetryEventPacket::PlayerDied, v924::LegacyTelemetryEventPacket::BossKilled, v924::LegacyTelemetryEventPacket::SlashCommand, v924::LegacyTelemetryEventPacket::MobBorn, v924::LegacyTelemetryEventPacket::POICauldronUsed, v924::LegacyTelemetryEventPacket::ComposterUsed, v924::LegacyTelemetryEventPacket::BellUsed, v924::LegacyTelemetryEventPacket::ActorDefinition, v924::LegacyTelemetryEventPacket::RaidUpdate, v924::LegacyTelemetryEventPacket::TargetBlockHit, v924::LegacyTelemetryEventPacket::PiglinBarter, v924::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v924::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v924::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v924::LegacyTelemetryEventPacket::ItemUsed, v924::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v924::LegacyTelemetryEventPacket::CodeBuilderScoreboard>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<19>(alt0);
                break;
            }
            case 20: {
                std::variant_alternative_t<20, std::variant<v924::LegacyTelemetryEventPacket::Achievement, v924::LegacyTelemetryEventPacket::Interaction, v924::LegacyTelemetryEventPacket::PortalCreated, v924::LegacyTelemetryEventPacket::PortalUsed, v924::LegacyTelemetryEventPacket::MobKilled, v924::LegacyTelemetryEventPacket::CauldronUsed, v924::LegacyTelemetryEventPacket::PlayerDied, v924::LegacyTelemetryEventPacket::BossKilled, v924::LegacyTelemetryEventPacket::SlashCommand, v924::LegacyTelemetryEventPacket::MobBorn, v924::LegacyTelemetryEventPacket::POICauldronUsed, v924::LegacyTelemetryEventPacket::ComposterUsed, v924::LegacyTelemetryEventPacket::BellUsed, v924::LegacyTelemetryEventPacket::ActorDefinition, v924::LegacyTelemetryEventPacket::RaidUpdate, v924::LegacyTelemetryEventPacket::TargetBlockHit, v924::LegacyTelemetryEventPacket::PiglinBarter, v924::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v924::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v924::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v924::LegacyTelemetryEventPacket::ItemUsed, v924::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v924::LegacyTelemetryEventPacket::ItemUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<20>(alt0);
                break;
            }
            case 21: {
                std::variant_alternative_t<21, std::variant<v924::LegacyTelemetryEventPacket::Achievement, v924::LegacyTelemetryEventPacket::Interaction, v924::LegacyTelemetryEventPacket::PortalCreated, v924::LegacyTelemetryEventPacket::PortalUsed, v924::LegacyTelemetryEventPacket::MobKilled, v924::LegacyTelemetryEventPacket::CauldronUsed, v924::LegacyTelemetryEventPacket::PlayerDied, v924::LegacyTelemetryEventPacket::BossKilled, v924::LegacyTelemetryEventPacket::SlashCommand, v924::LegacyTelemetryEventPacket::MobBorn, v924::LegacyTelemetryEventPacket::POICauldronUsed, v924::LegacyTelemetryEventPacket::ComposterUsed, v924::LegacyTelemetryEventPacket::BellUsed, v924::LegacyTelemetryEventPacket::ActorDefinition, v924::LegacyTelemetryEventPacket::RaidUpdate, v924::LegacyTelemetryEventPacket::TargetBlockHit, v924::LegacyTelemetryEventPacket::PiglinBarter, v924::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v924::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v924::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v924::LegacyTelemetryEventPacket::ItemUsed, v924::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v924::LegacyTelemetryEventPacket::Empty>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<21>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.event_data = var0;
    }
    return out;
}

void Serializer<v975::LegacyTelemetryEventPacket>::serialize(BinaryWriter &stream, const v975::LegacyTelemetryEventPacket &value)
{
    stream.writeVarInt<std::int64_t>(value.player_unique_id);
    stream.writeVarInt<std::int32_t>(value.type);
    stream.write<bool>(value.use_player_id);
    stream.writeVarInt<std::uint32_t>((value.event_data).index());
    switch ((value.event_data).index()) {
        case 0: {
            Serializer<v975::LegacyTelemetryEventPacket::Achievement>::serialize(stream, std::get<0>(value.event_data));
            break;
        }
        case 1: {
            Serializer<v975::LegacyTelemetryEventPacket::Interaction>::serialize(stream, std::get<1>(value.event_data));
            break;
        }
        case 2: {
            Serializer<v975::LegacyTelemetryEventPacket::PortalCreated>::serialize(stream, std::get<2>(value.event_data));
            break;
        }
        case 3: {
            Serializer<v975::LegacyTelemetryEventPacket::PortalUsed>::serialize(stream, std::get<3>(value.event_data));
            break;
        }
        case 4: {
            Serializer<v975::LegacyTelemetryEventPacket::MobKilled>::serialize(stream, std::get<4>(value.event_data));
            break;
        }
        case 5: {
            Serializer<v975::LegacyTelemetryEventPacket::CauldronUsed>::serialize(stream, std::get<5>(value.event_data));
            break;
        }
        case 6: {
            Serializer<v975::LegacyTelemetryEventPacket::PlayerDied>::serialize(stream, std::get<6>(value.event_data));
            break;
        }
        case 7: {
            Serializer<v975::LegacyTelemetryEventPacket::BossKilled>::serialize(stream, std::get<7>(value.event_data));
            break;
        }
        case 8: {
            Serializer<v975::LegacyTelemetryEventPacket::SlashCommand>::serialize(stream, std::get<8>(value.event_data));
            break;
        }
        case 9: {
            Serializer<v975::LegacyTelemetryEventPacket::MobBorn>::serialize(stream, std::get<9>(value.event_data));
            break;
        }
        case 10: {
            Serializer<v975::LegacyTelemetryEventPacket::POICauldronUsed>::serialize(stream, std::get<10>(value.event_data));
            break;
        }
        case 11: {
            Serializer<v975::LegacyTelemetryEventPacket::ComposterUsed>::serialize(stream, std::get<11>(value.event_data));
            break;
        }
        case 12: {
            Serializer<v975::LegacyTelemetryEventPacket::BellUsed>::serialize(stream, std::get<12>(value.event_data));
            break;
        }
        case 13: {
            Serializer<v975::LegacyTelemetryEventPacket::ActorDefinition>::serialize(stream, std::get<13>(value.event_data));
            break;
        }
        case 14: {
            Serializer<v975::LegacyTelemetryEventPacket::RaidUpdate>::serialize(stream, std::get<14>(value.event_data));
            break;
        }
        case 15: {
            Serializer<v975::LegacyTelemetryEventPacket::TargetBlockHit>::serialize(stream, std::get<15>(value.event_data));
            break;
        }
        case 16: {
            Serializer<v975::LegacyTelemetryEventPacket::PiglinBarter>::serialize(stream, std::get<16>(value.event_data));
            break;
        }
        case 17: {
            Serializer<v975::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper>::serialize(stream, std::get<17>(value.event_data));
            break;
        }
        case 18: {
            Serializer<v975::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction>::serialize(stream, std::get<18>(value.event_data));
            break;
        }
        case 19: {
            Serializer<v975::LegacyTelemetryEventPacket::CodeBuilderScoreboard>::serialize(stream, std::get<19>(value.event_data));
            break;
        }
        case 20: {
            Serializer<v975::LegacyTelemetryEventPacket::ItemUsed>::serialize(stream, std::get<20>(value.event_data));
            break;
        }
        case 21: {
            Serializer<v975::LegacyTelemetryEventPacket::Empty>::serialize(stream, std::get<21>(value.event_data));
            break;
        }
    }
}

auto Serializer<v975::LegacyTelemetryEventPacket>::deserialize(BinaryReader &stream) -> std::expected<v975::LegacyTelemetryEventPacket, std::error_code>
{
    v975::LegacyTelemetryEventPacket out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.player_unique_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<v975::LegacyTelemetryEventPacket::Type>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.use_player_id = static_cast<bool>(*v);
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v975::LegacyTelemetryEventPacket::Achievement, v975::LegacyTelemetryEventPacket::Interaction, v975::LegacyTelemetryEventPacket::PortalCreated, v975::LegacyTelemetryEventPacket::PortalUsed, v975::LegacyTelemetryEventPacket::MobKilled, v975::LegacyTelemetryEventPacket::CauldronUsed, v975::LegacyTelemetryEventPacket::PlayerDied, v975::LegacyTelemetryEventPacket::BossKilled, v975::LegacyTelemetryEventPacket::SlashCommand, v975::LegacyTelemetryEventPacket::MobBorn, v975::LegacyTelemetryEventPacket::POICauldronUsed, v975::LegacyTelemetryEventPacket::ComposterUsed, v975::LegacyTelemetryEventPacket::BellUsed, v975::LegacyTelemetryEventPacket::ActorDefinition, v975::LegacyTelemetryEventPacket::RaidUpdate, v975::LegacyTelemetryEventPacket::TargetBlockHit, v975::LegacyTelemetryEventPacket::PiglinBarter, v975::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v975::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v975::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v975::LegacyTelemetryEventPacket::ItemUsed, v975::LegacyTelemetryEventPacket::Empty> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v975::LegacyTelemetryEventPacket::Achievement, v975::LegacyTelemetryEventPacket::Interaction, v975::LegacyTelemetryEventPacket::PortalCreated, v975::LegacyTelemetryEventPacket::PortalUsed, v975::LegacyTelemetryEventPacket::MobKilled, v975::LegacyTelemetryEventPacket::CauldronUsed, v975::LegacyTelemetryEventPacket::PlayerDied, v975::LegacyTelemetryEventPacket::BossKilled, v975::LegacyTelemetryEventPacket::SlashCommand, v975::LegacyTelemetryEventPacket::MobBorn, v975::LegacyTelemetryEventPacket::POICauldronUsed, v975::LegacyTelemetryEventPacket::ComposterUsed, v975::LegacyTelemetryEventPacket::BellUsed, v975::LegacyTelemetryEventPacket::ActorDefinition, v975::LegacyTelemetryEventPacket::RaidUpdate, v975::LegacyTelemetryEventPacket::TargetBlockHit, v975::LegacyTelemetryEventPacket::PiglinBarter, v975::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v975::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v975::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v975::LegacyTelemetryEventPacket::ItemUsed, v975::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v975::LegacyTelemetryEventPacket::Achievement>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v975::LegacyTelemetryEventPacket::Achievement, v975::LegacyTelemetryEventPacket::Interaction, v975::LegacyTelemetryEventPacket::PortalCreated, v975::LegacyTelemetryEventPacket::PortalUsed, v975::LegacyTelemetryEventPacket::MobKilled, v975::LegacyTelemetryEventPacket::CauldronUsed, v975::LegacyTelemetryEventPacket::PlayerDied, v975::LegacyTelemetryEventPacket::BossKilled, v975::LegacyTelemetryEventPacket::SlashCommand, v975::LegacyTelemetryEventPacket::MobBorn, v975::LegacyTelemetryEventPacket::POICauldronUsed, v975::LegacyTelemetryEventPacket::ComposterUsed, v975::LegacyTelemetryEventPacket::BellUsed, v975::LegacyTelemetryEventPacket::ActorDefinition, v975::LegacyTelemetryEventPacket::RaidUpdate, v975::LegacyTelemetryEventPacket::TargetBlockHit, v975::LegacyTelemetryEventPacket::PiglinBarter, v975::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v975::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v975::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v975::LegacyTelemetryEventPacket::ItemUsed, v975::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v975::LegacyTelemetryEventPacket::Interaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<v975::LegacyTelemetryEventPacket::Achievement, v975::LegacyTelemetryEventPacket::Interaction, v975::LegacyTelemetryEventPacket::PortalCreated, v975::LegacyTelemetryEventPacket::PortalUsed, v975::LegacyTelemetryEventPacket::MobKilled, v975::LegacyTelemetryEventPacket::CauldronUsed, v975::LegacyTelemetryEventPacket::PlayerDied, v975::LegacyTelemetryEventPacket::BossKilled, v975::LegacyTelemetryEventPacket::SlashCommand, v975::LegacyTelemetryEventPacket::MobBorn, v975::LegacyTelemetryEventPacket::POICauldronUsed, v975::LegacyTelemetryEventPacket::ComposterUsed, v975::LegacyTelemetryEventPacket::BellUsed, v975::LegacyTelemetryEventPacket::ActorDefinition, v975::LegacyTelemetryEventPacket::RaidUpdate, v975::LegacyTelemetryEventPacket::TargetBlockHit, v975::LegacyTelemetryEventPacket::PiglinBarter, v975::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v975::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v975::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v975::LegacyTelemetryEventPacket::ItemUsed, v975::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v975::LegacyTelemetryEventPacket::PortalCreated>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<v975::LegacyTelemetryEventPacket::Achievement, v975::LegacyTelemetryEventPacket::Interaction, v975::LegacyTelemetryEventPacket::PortalCreated, v975::LegacyTelemetryEventPacket::PortalUsed, v975::LegacyTelemetryEventPacket::MobKilled, v975::LegacyTelemetryEventPacket::CauldronUsed, v975::LegacyTelemetryEventPacket::PlayerDied, v975::LegacyTelemetryEventPacket::BossKilled, v975::LegacyTelemetryEventPacket::SlashCommand, v975::LegacyTelemetryEventPacket::MobBorn, v975::LegacyTelemetryEventPacket::POICauldronUsed, v975::LegacyTelemetryEventPacket::ComposterUsed, v975::LegacyTelemetryEventPacket::BellUsed, v975::LegacyTelemetryEventPacket::ActorDefinition, v975::LegacyTelemetryEventPacket::RaidUpdate, v975::LegacyTelemetryEventPacket::TargetBlockHit, v975::LegacyTelemetryEventPacket::PiglinBarter, v975::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v975::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v975::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v975::LegacyTelemetryEventPacket::ItemUsed, v975::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v975::LegacyTelemetryEventPacket::PortalUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            case 4: {
                std::variant_alternative_t<4, std::variant<v975::LegacyTelemetryEventPacket::Achievement, v975::LegacyTelemetryEventPacket::Interaction, v975::LegacyTelemetryEventPacket::PortalCreated, v975::LegacyTelemetryEventPacket::PortalUsed, v975::LegacyTelemetryEventPacket::MobKilled, v975::LegacyTelemetryEventPacket::CauldronUsed, v975::LegacyTelemetryEventPacket::PlayerDied, v975::LegacyTelemetryEventPacket::BossKilled, v975::LegacyTelemetryEventPacket::SlashCommand, v975::LegacyTelemetryEventPacket::MobBorn, v975::LegacyTelemetryEventPacket::POICauldronUsed, v975::LegacyTelemetryEventPacket::ComposterUsed, v975::LegacyTelemetryEventPacket::BellUsed, v975::LegacyTelemetryEventPacket::ActorDefinition, v975::LegacyTelemetryEventPacket::RaidUpdate, v975::LegacyTelemetryEventPacket::TargetBlockHit, v975::LegacyTelemetryEventPacket::PiglinBarter, v975::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v975::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v975::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v975::LegacyTelemetryEventPacket::ItemUsed, v975::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v975::LegacyTelemetryEventPacket::MobKilled>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<4>(alt0);
                break;
            }
            case 5: {
                std::variant_alternative_t<5, std::variant<v975::LegacyTelemetryEventPacket::Achievement, v975::LegacyTelemetryEventPacket::Interaction, v975::LegacyTelemetryEventPacket::PortalCreated, v975::LegacyTelemetryEventPacket::PortalUsed, v975::LegacyTelemetryEventPacket::MobKilled, v975::LegacyTelemetryEventPacket::CauldronUsed, v975::LegacyTelemetryEventPacket::PlayerDied, v975::LegacyTelemetryEventPacket::BossKilled, v975::LegacyTelemetryEventPacket::SlashCommand, v975::LegacyTelemetryEventPacket::MobBorn, v975::LegacyTelemetryEventPacket::POICauldronUsed, v975::LegacyTelemetryEventPacket::ComposterUsed, v975::LegacyTelemetryEventPacket::BellUsed, v975::LegacyTelemetryEventPacket::ActorDefinition, v975::LegacyTelemetryEventPacket::RaidUpdate, v975::LegacyTelemetryEventPacket::TargetBlockHit, v975::LegacyTelemetryEventPacket::PiglinBarter, v975::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v975::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v975::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v975::LegacyTelemetryEventPacket::ItemUsed, v975::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v975::LegacyTelemetryEventPacket::CauldronUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<5>(alt0);
                break;
            }
            case 6: {
                std::variant_alternative_t<6, std::variant<v975::LegacyTelemetryEventPacket::Achievement, v975::LegacyTelemetryEventPacket::Interaction, v975::LegacyTelemetryEventPacket::PortalCreated, v975::LegacyTelemetryEventPacket::PortalUsed, v975::LegacyTelemetryEventPacket::MobKilled, v975::LegacyTelemetryEventPacket::CauldronUsed, v975::LegacyTelemetryEventPacket::PlayerDied, v975::LegacyTelemetryEventPacket::BossKilled, v975::LegacyTelemetryEventPacket::SlashCommand, v975::LegacyTelemetryEventPacket::MobBorn, v975::LegacyTelemetryEventPacket::POICauldronUsed, v975::LegacyTelemetryEventPacket::ComposterUsed, v975::LegacyTelemetryEventPacket::BellUsed, v975::LegacyTelemetryEventPacket::ActorDefinition, v975::LegacyTelemetryEventPacket::RaidUpdate, v975::LegacyTelemetryEventPacket::TargetBlockHit, v975::LegacyTelemetryEventPacket::PiglinBarter, v975::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v975::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v975::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v975::LegacyTelemetryEventPacket::ItemUsed, v975::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v975::LegacyTelemetryEventPacket::PlayerDied>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<6>(alt0);
                break;
            }
            case 7: {
                std::variant_alternative_t<7, std::variant<v975::LegacyTelemetryEventPacket::Achievement, v975::LegacyTelemetryEventPacket::Interaction, v975::LegacyTelemetryEventPacket::PortalCreated, v975::LegacyTelemetryEventPacket::PortalUsed, v975::LegacyTelemetryEventPacket::MobKilled, v975::LegacyTelemetryEventPacket::CauldronUsed, v975::LegacyTelemetryEventPacket::PlayerDied, v975::LegacyTelemetryEventPacket::BossKilled, v975::LegacyTelemetryEventPacket::SlashCommand, v975::LegacyTelemetryEventPacket::MobBorn, v975::LegacyTelemetryEventPacket::POICauldronUsed, v975::LegacyTelemetryEventPacket::ComposterUsed, v975::LegacyTelemetryEventPacket::BellUsed, v975::LegacyTelemetryEventPacket::ActorDefinition, v975::LegacyTelemetryEventPacket::RaidUpdate, v975::LegacyTelemetryEventPacket::TargetBlockHit, v975::LegacyTelemetryEventPacket::PiglinBarter, v975::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v975::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v975::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v975::LegacyTelemetryEventPacket::ItemUsed, v975::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v975::LegacyTelemetryEventPacket::BossKilled>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<7>(alt0);
                break;
            }
            case 8: {
                std::variant_alternative_t<8, std::variant<v975::LegacyTelemetryEventPacket::Achievement, v975::LegacyTelemetryEventPacket::Interaction, v975::LegacyTelemetryEventPacket::PortalCreated, v975::LegacyTelemetryEventPacket::PortalUsed, v975::LegacyTelemetryEventPacket::MobKilled, v975::LegacyTelemetryEventPacket::CauldronUsed, v975::LegacyTelemetryEventPacket::PlayerDied, v975::LegacyTelemetryEventPacket::BossKilled, v975::LegacyTelemetryEventPacket::SlashCommand, v975::LegacyTelemetryEventPacket::MobBorn, v975::LegacyTelemetryEventPacket::POICauldronUsed, v975::LegacyTelemetryEventPacket::ComposterUsed, v975::LegacyTelemetryEventPacket::BellUsed, v975::LegacyTelemetryEventPacket::ActorDefinition, v975::LegacyTelemetryEventPacket::RaidUpdate, v975::LegacyTelemetryEventPacket::TargetBlockHit, v975::LegacyTelemetryEventPacket::PiglinBarter, v975::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v975::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v975::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v975::LegacyTelemetryEventPacket::ItemUsed, v975::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v975::LegacyTelemetryEventPacket::SlashCommand>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<8>(alt0);
                break;
            }
            case 9: {
                std::variant_alternative_t<9, std::variant<v975::LegacyTelemetryEventPacket::Achievement, v975::LegacyTelemetryEventPacket::Interaction, v975::LegacyTelemetryEventPacket::PortalCreated, v975::LegacyTelemetryEventPacket::PortalUsed, v975::LegacyTelemetryEventPacket::MobKilled, v975::LegacyTelemetryEventPacket::CauldronUsed, v975::LegacyTelemetryEventPacket::PlayerDied, v975::LegacyTelemetryEventPacket::BossKilled, v975::LegacyTelemetryEventPacket::SlashCommand, v975::LegacyTelemetryEventPacket::MobBorn, v975::LegacyTelemetryEventPacket::POICauldronUsed, v975::LegacyTelemetryEventPacket::ComposterUsed, v975::LegacyTelemetryEventPacket::BellUsed, v975::LegacyTelemetryEventPacket::ActorDefinition, v975::LegacyTelemetryEventPacket::RaidUpdate, v975::LegacyTelemetryEventPacket::TargetBlockHit, v975::LegacyTelemetryEventPacket::PiglinBarter, v975::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v975::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v975::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v975::LegacyTelemetryEventPacket::ItemUsed, v975::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v975::LegacyTelemetryEventPacket::MobBorn>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<9>(alt0);
                break;
            }
            case 10: {
                std::variant_alternative_t<10, std::variant<v975::LegacyTelemetryEventPacket::Achievement, v975::LegacyTelemetryEventPacket::Interaction, v975::LegacyTelemetryEventPacket::PortalCreated, v975::LegacyTelemetryEventPacket::PortalUsed, v975::LegacyTelemetryEventPacket::MobKilled, v975::LegacyTelemetryEventPacket::CauldronUsed, v975::LegacyTelemetryEventPacket::PlayerDied, v975::LegacyTelemetryEventPacket::BossKilled, v975::LegacyTelemetryEventPacket::SlashCommand, v975::LegacyTelemetryEventPacket::MobBorn, v975::LegacyTelemetryEventPacket::POICauldronUsed, v975::LegacyTelemetryEventPacket::ComposterUsed, v975::LegacyTelemetryEventPacket::BellUsed, v975::LegacyTelemetryEventPacket::ActorDefinition, v975::LegacyTelemetryEventPacket::RaidUpdate, v975::LegacyTelemetryEventPacket::TargetBlockHit, v975::LegacyTelemetryEventPacket::PiglinBarter, v975::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v975::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v975::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v975::LegacyTelemetryEventPacket::ItemUsed, v975::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v975::LegacyTelemetryEventPacket::POICauldronUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<10>(alt0);
                break;
            }
            case 11: {
                std::variant_alternative_t<11, std::variant<v975::LegacyTelemetryEventPacket::Achievement, v975::LegacyTelemetryEventPacket::Interaction, v975::LegacyTelemetryEventPacket::PortalCreated, v975::LegacyTelemetryEventPacket::PortalUsed, v975::LegacyTelemetryEventPacket::MobKilled, v975::LegacyTelemetryEventPacket::CauldronUsed, v975::LegacyTelemetryEventPacket::PlayerDied, v975::LegacyTelemetryEventPacket::BossKilled, v975::LegacyTelemetryEventPacket::SlashCommand, v975::LegacyTelemetryEventPacket::MobBorn, v975::LegacyTelemetryEventPacket::POICauldronUsed, v975::LegacyTelemetryEventPacket::ComposterUsed, v975::LegacyTelemetryEventPacket::BellUsed, v975::LegacyTelemetryEventPacket::ActorDefinition, v975::LegacyTelemetryEventPacket::RaidUpdate, v975::LegacyTelemetryEventPacket::TargetBlockHit, v975::LegacyTelemetryEventPacket::PiglinBarter, v975::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v975::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v975::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v975::LegacyTelemetryEventPacket::ItemUsed, v975::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v975::LegacyTelemetryEventPacket::ComposterUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<11>(alt0);
                break;
            }
            case 12: {
                std::variant_alternative_t<12, std::variant<v975::LegacyTelemetryEventPacket::Achievement, v975::LegacyTelemetryEventPacket::Interaction, v975::LegacyTelemetryEventPacket::PortalCreated, v975::LegacyTelemetryEventPacket::PortalUsed, v975::LegacyTelemetryEventPacket::MobKilled, v975::LegacyTelemetryEventPacket::CauldronUsed, v975::LegacyTelemetryEventPacket::PlayerDied, v975::LegacyTelemetryEventPacket::BossKilled, v975::LegacyTelemetryEventPacket::SlashCommand, v975::LegacyTelemetryEventPacket::MobBorn, v975::LegacyTelemetryEventPacket::POICauldronUsed, v975::LegacyTelemetryEventPacket::ComposterUsed, v975::LegacyTelemetryEventPacket::BellUsed, v975::LegacyTelemetryEventPacket::ActorDefinition, v975::LegacyTelemetryEventPacket::RaidUpdate, v975::LegacyTelemetryEventPacket::TargetBlockHit, v975::LegacyTelemetryEventPacket::PiglinBarter, v975::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v975::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v975::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v975::LegacyTelemetryEventPacket::ItemUsed, v975::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v975::LegacyTelemetryEventPacket::BellUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<12>(alt0);
                break;
            }
            case 13: {
                std::variant_alternative_t<13, std::variant<v975::LegacyTelemetryEventPacket::Achievement, v975::LegacyTelemetryEventPacket::Interaction, v975::LegacyTelemetryEventPacket::PortalCreated, v975::LegacyTelemetryEventPacket::PortalUsed, v975::LegacyTelemetryEventPacket::MobKilled, v975::LegacyTelemetryEventPacket::CauldronUsed, v975::LegacyTelemetryEventPacket::PlayerDied, v975::LegacyTelemetryEventPacket::BossKilled, v975::LegacyTelemetryEventPacket::SlashCommand, v975::LegacyTelemetryEventPacket::MobBorn, v975::LegacyTelemetryEventPacket::POICauldronUsed, v975::LegacyTelemetryEventPacket::ComposterUsed, v975::LegacyTelemetryEventPacket::BellUsed, v975::LegacyTelemetryEventPacket::ActorDefinition, v975::LegacyTelemetryEventPacket::RaidUpdate, v975::LegacyTelemetryEventPacket::TargetBlockHit, v975::LegacyTelemetryEventPacket::PiglinBarter, v975::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v975::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v975::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v975::LegacyTelemetryEventPacket::ItemUsed, v975::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v975::LegacyTelemetryEventPacket::ActorDefinition>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<13>(alt0);
                break;
            }
            case 14: {
                std::variant_alternative_t<14, std::variant<v975::LegacyTelemetryEventPacket::Achievement, v975::LegacyTelemetryEventPacket::Interaction, v975::LegacyTelemetryEventPacket::PortalCreated, v975::LegacyTelemetryEventPacket::PortalUsed, v975::LegacyTelemetryEventPacket::MobKilled, v975::LegacyTelemetryEventPacket::CauldronUsed, v975::LegacyTelemetryEventPacket::PlayerDied, v975::LegacyTelemetryEventPacket::BossKilled, v975::LegacyTelemetryEventPacket::SlashCommand, v975::LegacyTelemetryEventPacket::MobBorn, v975::LegacyTelemetryEventPacket::POICauldronUsed, v975::LegacyTelemetryEventPacket::ComposterUsed, v975::LegacyTelemetryEventPacket::BellUsed, v975::LegacyTelemetryEventPacket::ActorDefinition, v975::LegacyTelemetryEventPacket::RaidUpdate, v975::LegacyTelemetryEventPacket::TargetBlockHit, v975::LegacyTelemetryEventPacket::PiglinBarter, v975::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v975::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v975::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v975::LegacyTelemetryEventPacket::ItemUsed, v975::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v975::LegacyTelemetryEventPacket::RaidUpdate>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<14>(alt0);
                break;
            }
            case 15: {
                std::variant_alternative_t<15, std::variant<v975::LegacyTelemetryEventPacket::Achievement, v975::LegacyTelemetryEventPacket::Interaction, v975::LegacyTelemetryEventPacket::PortalCreated, v975::LegacyTelemetryEventPacket::PortalUsed, v975::LegacyTelemetryEventPacket::MobKilled, v975::LegacyTelemetryEventPacket::CauldronUsed, v975::LegacyTelemetryEventPacket::PlayerDied, v975::LegacyTelemetryEventPacket::BossKilled, v975::LegacyTelemetryEventPacket::SlashCommand, v975::LegacyTelemetryEventPacket::MobBorn, v975::LegacyTelemetryEventPacket::POICauldronUsed, v975::LegacyTelemetryEventPacket::ComposterUsed, v975::LegacyTelemetryEventPacket::BellUsed, v975::LegacyTelemetryEventPacket::ActorDefinition, v975::LegacyTelemetryEventPacket::RaidUpdate, v975::LegacyTelemetryEventPacket::TargetBlockHit, v975::LegacyTelemetryEventPacket::PiglinBarter, v975::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v975::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v975::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v975::LegacyTelemetryEventPacket::ItemUsed, v975::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v975::LegacyTelemetryEventPacket::TargetBlockHit>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<15>(alt0);
                break;
            }
            case 16: {
                std::variant_alternative_t<16, std::variant<v975::LegacyTelemetryEventPacket::Achievement, v975::LegacyTelemetryEventPacket::Interaction, v975::LegacyTelemetryEventPacket::PortalCreated, v975::LegacyTelemetryEventPacket::PortalUsed, v975::LegacyTelemetryEventPacket::MobKilled, v975::LegacyTelemetryEventPacket::CauldronUsed, v975::LegacyTelemetryEventPacket::PlayerDied, v975::LegacyTelemetryEventPacket::BossKilled, v975::LegacyTelemetryEventPacket::SlashCommand, v975::LegacyTelemetryEventPacket::MobBorn, v975::LegacyTelemetryEventPacket::POICauldronUsed, v975::LegacyTelemetryEventPacket::ComposterUsed, v975::LegacyTelemetryEventPacket::BellUsed, v975::LegacyTelemetryEventPacket::ActorDefinition, v975::LegacyTelemetryEventPacket::RaidUpdate, v975::LegacyTelemetryEventPacket::TargetBlockHit, v975::LegacyTelemetryEventPacket::PiglinBarter, v975::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v975::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v975::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v975::LegacyTelemetryEventPacket::ItemUsed, v975::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v975::LegacyTelemetryEventPacket::PiglinBarter>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<16>(alt0);
                break;
            }
            case 17: {
                std::variant_alternative_t<17, std::variant<v975::LegacyTelemetryEventPacket::Achievement, v975::LegacyTelemetryEventPacket::Interaction, v975::LegacyTelemetryEventPacket::PortalCreated, v975::LegacyTelemetryEventPacket::PortalUsed, v975::LegacyTelemetryEventPacket::MobKilled, v975::LegacyTelemetryEventPacket::CauldronUsed, v975::LegacyTelemetryEventPacket::PlayerDied, v975::LegacyTelemetryEventPacket::BossKilled, v975::LegacyTelemetryEventPacket::SlashCommand, v975::LegacyTelemetryEventPacket::MobBorn, v975::LegacyTelemetryEventPacket::POICauldronUsed, v975::LegacyTelemetryEventPacket::ComposterUsed, v975::LegacyTelemetryEventPacket::BellUsed, v975::LegacyTelemetryEventPacket::ActorDefinition, v975::LegacyTelemetryEventPacket::RaidUpdate, v975::LegacyTelemetryEventPacket::TargetBlockHit, v975::LegacyTelemetryEventPacket::PiglinBarter, v975::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v975::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v975::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v975::LegacyTelemetryEventPacket::ItemUsed, v975::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v975::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<17>(alt0);
                break;
            }
            case 18: {
                std::variant_alternative_t<18, std::variant<v975::LegacyTelemetryEventPacket::Achievement, v975::LegacyTelemetryEventPacket::Interaction, v975::LegacyTelemetryEventPacket::PortalCreated, v975::LegacyTelemetryEventPacket::PortalUsed, v975::LegacyTelemetryEventPacket::MobKilled, v975::LegacyTelemetryEventPacket::CauldronUsed, v975::LegacyTelemetryEventPacket::PlayerDied, v975::LegacyTelemetryEventPacket::BossKilled, v975::LegacyTelemetryEventPacket::SlashCommand, v975::LegacyTelemetryEventPacket::MobBorn, v975::LegacyTelemetryEventPacket::POICauldronUsed, v975::LegacyTelemetryEventPacket::ComposterUsed, v975::LegacyTelemetryEventPacket::BellUsed, v975::LegacyTelemetryEventPacket::ActorDefinition, v975::LegacyTelemetryEventPacket::RaidUpdate, v975::LegacyTelemetryEventPacket::TargetBlockHit, v975::LegacyTelemetryEventPacket::PiglinBarter, v975::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v975::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v975::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v975::LegacyTelemetryEventPacket::ItemUsed, v975::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v975::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<18>(alt0);
                break;
            }
            case 19: {
                std::variant_alternative_t<19, std::variant<v975::LegacyTelemetryEventPacket::Achievement, v975::LegacyTelemetryEventPacket::Interaction, v975::LegacyTelemetryEventPacket::PortalCreated, v975::LegacyTelemetryEventPacket::PortalUsed, v975::LegacyTelemetryEventPacket::MobKilled, v975::LegacyTelemetryEventPacket::CauldronUsed, v975::LegacyTelemetryEventPacket::PlayerDied, v975::LegacyTelemetryEventPacket::BossKilled, v975::LegacyTelemetryEventPacket::SlashCommand, v975::LegacyTelemetryEventPacket::MobBorn, v975::LegacyTelemetryEventPacket::POICauldronUsed, v975::LegacyTelemetryEventPacket::ComposterUsed, v975::LegacyTelemetryEventPacket::BellUsed, v975::LegacyTelemetryEventPacket::ActorDefinition, v975::LegacyTelemetryEventPacket::RaidUpdate, v975::LegacyTelemetryEventPacket::TargetBlockHit, v975::LegacyTelemetryEventPacket::PiglinBarter, v975::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v975::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v975::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v975::LegacyTelemetryEventPacket::ItemUsed, v975::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v975::LegacyTelemetryEventPacket::CodeBuilderScoreboard>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<19>(alt0);
                break;
            }
            case 20: {
                std::variant_alternative_t<20, std::variant<v975::LegacyTelemetryEventPacket::Achievement, v975::LegacyTelemetryEventPacket::Interaction, v975::LegacyTelemetryEventPacket::PortalCreated, v975::LegacyTelemetryEventPacket::PortalUsed, v975::LegacyTelemetryEventPacket::MobKilled, v975::LegacyTelemetryEventPacket::CauldronUsed, v975::LegacyTelemetryEventPacket::PlayerDied, v975::LegacyTelemetryEventPacket::BossKilled, v975::LegacyTelemetryEventPacket::SlashCommand, v975::LegacyTelemetryEventPacket::MobBorn, v975::LegacyTelemetryEventPacket::POICauldronUsed, v975::LegacyTelemetryEventPacket::ComposterUsed, v975::LegacyTelemetryEventPacket::BellUsed, v975::LegacyTelemetryEventPacket::ActorDefinition, v975::LegacyTelemetryEventPacket::RaidUpdate, v975::LegacyTelemetryEventPacket::TargetBlockHit, v975::LegacyTelemetryEventPacket::PiglinBarter, v975::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v975::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v975::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v975::LegacyTelemetryEventPacket::ItemUsed, v975::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v975::LegacyTelemetryEventPacket::ItemUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<20>(alt0);
                break;
            }
            case 21: {
                std::variant_alternative_t<21, std::variant<v975::LegacyTelemetryEventPacket::Achievement, v975::LegacyTelemetryEventPacket::Interaction, v975::LegacyTelemetryEventPacket::PortalCreated, v975::LegacyTelemetryEventPacket::PortalUsed, v975::LegacyTelemetryEventPacket::MobKilled, v975::LegacyTelemetryEventPacket::CauldronUsed, v975::LegacyTelemetryEventPacket::PlayerDied, v975::LegacyTelemetryEventPacket::BossKilled, v975::LegacyTelemetryEventPacket::SlashCommand, v975::LegacyTelemetryEventPacket::MobBorn, v975::LegacyTelemetryEventPacket::POICauldronUsed, v975::LegacyTelemetryEventPacket::ComposterUsed, v975::LegacyTelemetryEventPacket::BellUsed, v975::LegacyTelemetryEventPacket::ActorDefinition, v975::LegacyTelemetryEventPacket::RaidUpdate, v975::LegacyTelemetryEventPacket::TargetBlockHit, v975::LegacyTelemetryEventPacket::PiglinBarter, v975::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v975::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v975::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v975::LegacyTelemetryEventPacket::ItemUsed, v975::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v975::LegacyTelemetryEventPacket::Empty>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<21>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.event_data = var0;
    }
    return out;
}

void Serializer<v1001::LegacyTelemetryEventPacket>::serialize(BinaryWriter &stream, const v1001::LegacyTelemetryEventPacket &value)
{
    stream.writeVarInt<std::int64_t>(value.player_unique_id);
    stream.writeVarInt<std::int32_t>(value.type);
    stream.write<bool>(value.use_player_id);
    stream.writeVarInt<std::uint32_t>((value.event_data).index());
    switch ((value.event_data).index()) {
        case 0: {
            Serializer<v1001::LegacyTelemetryEventPacket::Achievement>::serialize(stream, std::get<0>(value.event_data));
            break;
        }
        case 1: {
            Serializer<v1001::LegacyTelemetryEventPacket::Interaction>::serialize(stream, std::get<1>(value.event_data));
            break;
        }
        case 2: {
            Serializer<v1001::LegacyTelemetryEventPacket::PortalCreated>::serialize(stream, std::get<2>(value.event_data));
            break;
        }
        case 3: {
            Serializer<v1001::LegacyTelemetryEventPacket::PortalUsed>::serialize(stream, std::get<3>(value.event_data));
            break;
        }
        case 4: {
            Serializer<v1001::LegacyTelemetryEventPacket::MobKilled>::serialize(stream, std::get<4>(value.event_data));
            break;
        }
        case 5: {
            Serializer<v1001::LegacyTelemetryEventPacket::CauldronUsed>::serialize(stream, std::get<5>(value.event_data));
            break;
        }
        case 6: {
            Serializer<v1001::LegacyTelemetryEventPacket::PlayerDied>::serialize(stream, std::get<6>(value.event_data));
            break;
        }
        case 7: {
            Serializer<v1001::LegacyTelemetryEventPacket::BossKilled>::serialize(stream, std::get<7>(value.event_data));
            break;
        }
        case 8: {
            Serializer<v1001::LegacyTelemetryEventPacket::SlashCommand>::serialize(stream, std::get<8>(value.event_data));
            break;
        }
        case 9: {
            Serializer<v1001::LegacyTelemetryEventPacket::MobBorn>::serialize(stream, std::get<9>(value.event_data));
            break;
        }
        case 10: {
            Serializer<v1001::LegacyTelemetryEventPacket::POICauldronUsed>::serialize(stream, std::get<10>(value.event_data));
            break;
        }
        case 11: {
            Serializer<v1001::LegacyTelemetryEventPacket::ComposterUsed>::serialize(stream, std::get<11>(value.event_data));
            break;
        }
        case 12: {
            Serializer<v1001::LegacyTelemetryEventPacket::BellUsed>::serialize(stream, std::get<12>(value.event_data));
            break;
        }
        case 13: {
            Serializer<v1001::LegacyTelemetryEventPacket::ActorDefinition>::serialize(stream, std::get<13>(value.event_data));
            break;
        }
        case 14: {
            Serializer<v1001::LegacyTelemetryEventPacket::RaidUpdate>::serialize(stream, std::get<14>(value.event_data));
            break;
        }
        case 15: {
            Serializer<v1001::LegacyTelemetryEventPacket::TargetBlockHit>::serialize(stream, std::get<15>(value.event_data));
            break;
        }
        case 16: {
            Serializer<v1001::LegacyTelemetryEventPacket::PiglinBarter>::serialize(stream, std::get<16>(value.event_data));
            break;
        }
        case 17: {
            Serializer<v1001::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper>::serialize(stream, std::get<17>(value.event_data));
            break;
        }
        case 18: {
            Serializer<v1001::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction>::serialize(stream, std::get<18>(value.event_data));
            break;
        }
        case 19: {
            Serializer<v1001::LegacyTelemetryEventPacket::CodeBuilderScoreboard>::serialize(stream, std::get<19>(value.event_data));
            break;
        }
        case 20: {
            Serializer<v1001::LegacyTelemetryEventPacket::ItemUsed>::serialize(stream, std::get<20>(value.event_data));
            break;
        }
        case 21: {
            Serializer<v1001::LegacyTelemetryEventPacket::Empty>::serialize(stream, std::get<21>(value.event_data));
            break;
        }
    }
}

auto Serializer<v1001::LegacyTelemetryEventPacket>::deserialize(BinaryReader &stream) -> std::expected<v1001::LegacyTelemetryEventPacket, std::error_code>
{
    v1001::LegacyTelemetryEventPacket out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.player_unique_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<v1001::LegacyTelemetryEventPacket::Type>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.use_player_id = static_cast<bool>(*v);
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v1001::LegacyTelemetryEventPacket::Achievement, v1001::LegacyTelemetryEventPacket::Interaction, v1001::LegacyTelemetryEventPacket::PortalCreated, v1001::LegacyTelemetryEventPacket::PortalUsed, v1001::LegacyTelemetryEventPacket::MobKilled, v1001::LegacyTelemetryEventPacket::CauldronUsed, v1001::LegacyTelemetryEventPacket::PlayerDied, v1001::LegacyTelemetryEventPacket::BossKilled, v1001::LegacyTelemetryEventPacket::SlashCommand, v1001::LegacyTelemetryEventPacket::MobBorn, v1001::LegacyTelemetryEventPacket::POICauldronUsed, v1001::LegacyTelemetryEventPacket::ComposterUsed, v1001::LegacyTelemetryEventPacket::BellUsed, v1001::LegacyTelemetryEventPacket::ActorDefinition, v1001::LegacyTelemetryEventPacket::RaidUpdate, v1001::LegacyTelemetryEventPacket::TargetBlockHit, v1001::LegacyTelemetryEventPacket::PiglinBarter, v1001::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v1001::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v1001::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v1001::LegacyTelemetryEventPacket::ItemUsed, v1001::LegacyTelemetryEventPacket::Empty> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v1001::LegacyTelemetryEventPacket::Achievement, v1001::LegacyTelemetryEventPacket::Interaction, v1001::LegacyTelemetryEventPacket::PortalCreated, v1001::LegacyTelemetryEventPacket::PortalUsed, v1001::LegacyTelemetryEventPacket::MobKilled, v1001::LegacyTelemetryEventPacket::CauldronUsed, v1001::LegacyTelemetryEventPacket::PlayerDied, v1001::LegacyTelemetryEventPacket::BossKilled, v1001::LegacyTelemetryEventPacket::SlashCommand, v1001::LegacyTelemetryEventPacket::MobBorn, v1001::LegacyTelemetryEventPacket::POICauldronUsed, v1001::LegacyTelemetryEventPacket::ComposterUsed, v1001::LegacyTelemetryEventPacket::BellUsed, v1001::LegacyTelemetryEventPacket::ActorDefinition, v1001::LegacyTelemetryEventPacket::RaidUpdate, v1001::LegacyTelemetryEventPacket::TargetBlockHit, v1001::LegacyTelemetryEventPacket::PiglinBarter, v1001::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v1001::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v1001::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v1001::LegacyTelemetryEventPacket::ItemUsed, v1001::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v1001::LegacyTelemetryEventPacket::Achievement>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v1001::LegacyTelemetryEventPacket::Achievement, v1001::LegacyTelemetryEventPacket::Interaction, v1001::LegacyTelemetryEventPacket::PortalCreated, v1001::LegacyTelemetryEventPacket::PortalUsed, v1001::LegacyTelemetryEventPacket::MobKilled, v1001::LegacyTelemetryEventPacket::CauldronUsed, v1001::LegacyTelemetryEventPacket::PlayerDied, v1001::LegacyTelemetryEventPacket::BossKilled, v1001::LegacyTelemetryEventPacket::SlashCommand, v1001::LegacyTelemetryEventPacket::MobBorn, v1001::LegacyTelemetryEventPacket::POICauldronUsed, v1001::LegacyTelemetryEventPacket::ComposterUsed, v1001::LegacyTelemetryEventPacket::BellUsed, v1001::LegacyTelemetryEventPacket::ActorDefinition, v1001::LegacyTelemetryEventPacket::RaidUpdate, v1001::LegacyTelemetryEventPacket::TargetBlockHit, v1001::LegacyTelemetryEventPacket::PiglinBarter, v1001::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v1001::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v1001::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v1001::LegacyTelemetryEventPacket::ItemUsed, v1001::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v1001::LegacyTelemetryEventPacket::Interaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<v1001::LegacyTelemetryEventPacket::Achievement, v1001::LegacyTelemetryEventPacket::Interaction, v1001::LegacyTelemetryEventPacket::PortalCreated, v1001::LegacyTelemetryEventPacket::PortalUsed, v1001::LegacyTelemetryEventPacket::MobKilled, v1001::LegacyTelemetryEventPacket::CauldronUsed, v1001::LegacyTelemetryEventPacket::PlayerDied, v1001::LegacyTelemetryEventPacket::BossKilled, v1001::LegacyTelemetryEventPacket::SlashCommand, v1001::LegacyTelemetryEventPacket::MobBorn, v1001::LegacyTelemetryEventPacket::POICauldronUsed, v1001::LegacyTelemetryEventPacket::ComposterUsed, v1001::LegacyTelemetryEventPacket::BellUsed, v1001::LegacyTelemetryEventPacket::ActorDefinition, v1001::LegacyTelemetryEventPacket::RaidUpdate, v1001::LegacyTelemetryEventPacket::TargetBlockHit, v1001::LegacyTelemetryEventPacket::PiglinBarter, v1001::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v1001::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v1001::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v1001::LegacyTelemetryEventPacket::ItemUsed, v1001::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v1001::LegacyTelemetryEventPacket::PortalCreated>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<v1001::LegacyTelemetryEventPacket::Achievement, v1001::LegacyTelemetryEventPacket::Interaction, v1001::LegacyTelemetryEventPacket::PortalCreated, v1001::LegacyTelemetryEventPacket::PortalUsed, v1001::LegacyTelemetryEventPacket::MobKilled, v1001::LegacyTelemetryEventPacket::CauldronUsed, v1001::LegacyTelemetryEventPacket::PlayerDied, v1001::LegacyTelemetryEventPacket::BossKilled, v1001::LegacyTelemetryEventPacket::SlashCommand, v1001::LegacyTelemetryEventPacket::MobBorn, v1001::LegacyTelemetryEventPacket::POICauldronUsed, v1001::LegacyTelemetryEventPacket::ComposterUsed, v1001::LegacyTelemetryEventPacket::BellUsed, v1001::LegacyTelemetryEventPacket::ActorDefinition, v1001::LegacyTelemetryEventPacket::RaidUpdate, v1001::LegacyTelemetryEventPacket::TargetBlockHit, v1001::LegacyTelemetryEventPacket::PiglinBarter, v1001::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v1001::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v1001::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v1001::LegacyTelemetryEventPacket::ItemUsed, v1001::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v1001::LegacyTelemetryEventPacket::PortalUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            case 4: {
                std::variant_alternative_t<4, std::variant<v1001::LegacyTelemetryEventPacket::Achievement, v1001::LegacyTelemetryEventPacket::Interaction, v1001::LegacyTelemetryEventPacket::PortalCreated, v1001::LegacyTelemetryEventPacket::PortalUsed, v1001::LegacyTelemetryEventPacket::MobKilled, v1001::LegacyTelemetryEventPacket::CauldronUsed, v1001::LegacyTelemetryEventPacket::PlayerDied, v1001::LegacyTelemetryEventPacket::BossKilled, v1001::LegacyTelemetryEventPacket::SlashCommand, v1001::LegacyTelemetryEventPacket::MobBorn, v1001::LegacyTelemetryEventPacket::POICauldronUsed, v1001::LegacyTelemetryEventPacket::ComposterUsed, v1001::LegacyTelemetryEventPacket::BellUsed, v1001::LegacyTelemetryEventPacket::ActorDefinition, v1001::LegacyTelemetryEventPacket::RaidUpdate, v1001::LegacyTelemetryEventPacket::TargetBlockHit, v1001::LegacyTelemetryEventPacket::PiglinBarter, v1001::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v1001::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v1001::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v1001::LegacyTelemetryEventPacket::ItemUsed, v1001::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v1001::LegacyTelemetryEventPacket::MobKilled>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<4>(alt0);
                break;
            }
            case 5: {
                std::variant_alternative_t<5, std::variant<v1001::LegacyTelemetryEventPacket::Achievement, v1001::LegacyTelemetryEventPacket::Interaction, v1001::LegacyTelemetryEventPacket::PortalCreated, v1001::LegacyTelemetryEventPacket::PortalUsed, v1001::LegacyTelemetryEventPacket::MobKilled, v1001::LegacyTelemetryEventPacket::CauldronUsed, v1001::LegacyTelemetryEventPacket::PlayerDied, v1001::LegacyTelemetryEventPacket::BossKilled, v1001::LegacyTelemetryEventPacket::SlashCommand, v1001::LegacyTelemetryEventPacket::MobBorn, v1001::LegacyTelemetryEventPacket::POICauldronUsed, v1001::LegacyTelemetryEventPacket::ComposterUsed, v1001::LegacyTelemetryEventPacket::BellUsed, v1001::LegacyTelemetryEventPacket::ActorDefinition, v1001::LegacyTelemetryEventPacket::RaidUpdate, v1001::LegacyTelemetryEventPacket::TargetBlockHit, v1001::LegacyTelemetryEventPacket::PiglinBarter, v1001::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v1001::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v1001::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v1001::LegacyTelemetryEventPacket::ItemUsed, v1001::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v1001::LegacyTelemetryEventPacket::CauldronUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<5>(alt0);
                break;
            }
            case 6: {
                std::variant_alternative_t<6, std::variant<v1001::LegacyTelemetryEventPacket::Achievement, v1001::LegacyTelemetryEventPacket::Interaction, v1001::LegacyTelemetryEventPacket::PortalCreated, v1001::LegacyTelemetryEventPacket::PortalUsed, v1001::LegacyTelemetryEventPacket::MobKilled, v1001::LegacyTelemetryEventPacket::CauldronUsed, v1001::LegacyTelemetryEventPacket::PlayerDied, v1001::LegacyTelemetryEventPacket::BossKilled, v1001::LegacyTelemetryEventPacket::SlashCommand, v1001::LegacyTelemetryEventPacket::MobBorn, v1001::LegacyTelemetryEventPacket::POICauldronUsed, v1001::LegacyTelemetryEventPacket::ComposterUsed, v1001::LegacyTelemetryEventPacket::BellUsed, v1001::LegacyTelemetryEventPacket::ActorDefinition, v1001::LegacyTelemetryEventPacket::RaidUpdate, v1001::LegacyTelemetryEventPacket::TargetBlockHit, v1001::LegacyTelemetryEventPacket::PiglinBarter, v1001::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v1001::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v1001::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v1001::LegacyTelemetryEventPacket::ItemUsed, v1001::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v1001::LegacyTelemetryEventPacket::PlayerDied>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<6>(alt0);
                break;
            }
            case 7: {
                std::variant_alternative_t<7, std::variant<v1001::LegacyTelemetryEventPacket::Achievement, v1001::LegacyTelemetryEventPacket::Interaction, v1001::LegacyTelemetryEventPacket::PortalCreated, v1001::LegacyTelemetryEventPacket::PortalUsed, v1001::LegacyTelemetryEventPacket::MobKilled, v1001::LegacyTelemetryEventPacket::CauldronUsed, v1001::LegacyTelemetryEventPacket::PlayerDied, v1001::LegacyTelemetryEventPacket::BossKilled, v1001::LegacyTelemetryEventPacket::SlashCommand, v1001::LegacyTelemetryEventPacket::MobBorn, v1001::LegacyTelemetryEventPacket::POICauldronUsed, v1001::LegacyTelemetryEventPacket::ComposterUsed, v1001::LegacyTelemetryEventPacket::BellUsed, v1001::LegacyTelemetryEventPacket::ActorDefinition, v1001::LegacyTelemetryEventPacket::RaidUpdate, v1001::LegacyTelemetryEventPacket::TargetBlockHit, v1001::LegacyTelemetryEventPacket::PiglinBarter, v1001::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v1001::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v1001::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v1001::LegacyTelemetryEventPacket::ItemUsed, v1001::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v1001::LegacyTelemetryEventPacket::BossKilled>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<7>(alt0);
                break;
            }
            case 8: {
                std::variant_alternative_t<8, std::variant<v1001::LegacyTelemetryEventPacket::Achievement, v1001::LegacyTelemetryEventPacket::Interaction, v1001::LegacyTelemetryEventPacket::PortalCreated, v1001::LegacyTelemetryEventPacket::PortalUsed, v1001::LegacyTelemetryEventPacket::MobKilled, v1001::LegacyTelemetryEventPacket::CauldronUsed, v1001::LegacyTelemetryEventPacket::PlayerDied, v1001::LegacyTelemetryEventPacket::BossKilled, v1001::LegacyTelemetryEventPacket::SlashCommand, v1001::LegacyTelemetryEventPacket::MobBorn, v1001::LegacyTelemetryEventPacket::POICauldronUsed, v1001::LegacyTelemetryEventPacket::ComposterUsed, v1001::LegacyTelemetryEventPacket::BellUsed, v1001::LegacyTelemetryEventPacket::ActorDefinition, v1001::LegacyTelemetryEventPacket::RaidUpdate, v1001::LegacyTelemetryEventPacket::TargetBlockHit, v1001::LegacyTelemetryEventPacket::PiglinBarter, v1001::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v1001::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v1001::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v1001::LegacyTelemetryEventPacket::ItemUsed, v1001::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v1001::LegacyTelemetryEventPacket::SlashCommand>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<8>(alt0);
                break;
            }
            case 9: {
                std::variant_alternative_t<9, std::variant<v1001::LegacyTelemetryEventPacket::Achievement, v1001::LegacyTelemetryEventPacket::Interaction, v1001::LegacyTelemetryEventPacket::PortalCreated, v1001::LegacyTelemetryEventPacket::PortalUsed, v1001::LegacyTelemetryEventPacket::MobKilled, v1001::LegacyTelemetryEventPacket::CauldronUsed, v1001::LegacyTelemetryEventPacket::PlayerDied, v1001::LegacyTelemetryEventPacket::BossKilled, v1001::LegacyTelemetryEventPacket::SlashCommand, v1001::LegacyTelemetryEventPacket::MobBorn, v1001::LegacyTelemetryEventPacket::POICauldronUsed, v1001::LegacyTelemetryEventPacket::ComposterUsed, v1001::LegacyTelemetryEventPacket::BellUsed, v1001::LegacyTelemetryEventPacket::ActorDefinition, v1001::LegacyTelemetryEventPacket::RaidUpdate, v1001::LegacyTelemetryEventPacket::TargetBlockHit, v1001::LegacyTelemetryEventPacket::PiglinBarter, v1001::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v1001::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v1001::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v1001::LegacyTelemetryEventPacket::ItemUsed, v1001::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v1001::LegacyTelemetryEventPacket::MobBorn>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<9>(alt0);
                break;
            }
            case 10: {
                std::variant_alternative_t<10, std::variant<v1001::LegacyTelemetryEventPacket::Achievement, v1001::LegacyTelemetryEventPacket::Interaction, v1001::LegacyTelemetryEventPacket::PortalCreated, v1001::LegacyTelemetryEventPacket::PortalUsed, v1001::LegacyTelemetryEventPacket::MobKilled, v1001::LegacyTelemetryEventPacket::CauldronUsed, v1001::LegacyTelemetryEventPacket::PlayerDied, v1001::LegacyTelemetryEventPacket::BossKilled, v1001::LegacyTelemetryEventPacket::SlashCommand, v1001::LegacyTelemetryEventPacket::MobBorn, v1001::LegacyTelemetryEventPacket::POICauldronUsed, v1001::LegacyTelemetryEventPacket::ComposterUsed, v1001::LegacyTelemetryEventPacket::BellUsed, v1001::LegacyTelemetryEventPacket::ActorDefinition, v1001::LegacyTelemetryEventPacket::RaidUpdate, v1001::LegacyTelemetryEventPacket::TargetBlockHit, v1001::LegacyTelemetryEventPacket::PiglinBarter, v1001::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v1001::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v1001::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v1001::LegacyTelemetryEventPacket::ItemUsed, v1001::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v1001::LegacyTelemetryEventPacket::POICauldronUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<10>(alt0);
                break;
            }
            case 11: {
                std::variant_alternative_t<11, std::variant<v1001::LegacyTelemetryEventPacket::Achievement, v1001::LegacyTelemetryEventPacket::Interaction, v1001::LegacyTelemetryEventPacket::PortalCreated, v1001::LegacyTelemetryEventPacket::PortalUsed, v1001::LegacyTelemetryEventPacket::MobKilled, v1001::LegacyTelemetryEventPacket::CauldronUsed, v1001::LegacyTelemetryEventPacket::PlayerDied, v1001::LegacyTelemetryEventPacket::BossKilled, v1001::LegacyTelemetryEventPacket::SlashCommand, v1001::LegacyTelemetryEventPacket::MobBorn, v1001::LegacyTelemetryEventPacket::POICauldronUsed, v1001::LegacyTelemetryEventPacket::ComposterUsed, v1001::LegacyTelemetryEventPacket::BellUsed, v1001::LegacyTelemetryEventPacket::ActorDefinition, v1001::LegacyTelemetryEventPacket::RaidUpdate, v1001::LegacyTelemetryEventPacket::TargetBlockHit, v1001::LegacyTelemetryEventPacket::PiglinBarter, v1001::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v1001::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v1001::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v1001::LegacyTelemetryEventPacket::ItemUsed, v1001::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v1001::LegacyTelemetryEventPacket::ComposterUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<11>(alt0);
                break;
            }
            case 12: {
                std::variant_alternative_t<12, std::variant<v1001::LegacyTelemetryEventPacket::Achievement, v1001::LegacyTelemetryEventPacket::Interaction, v1001::LegacyTelemetryEventPacket::PortalCreated, v1001::LegacyTelemetryEventPacket::PortalUsed, v1001::LegacyTelemetryEventPacket::MobKilled, v1001::LegacyTelemetryEventPacket::CauldronUsed, v1001::LegacyTelemetryEventPacket::PlayerDied, v1001::LegacyTelemetryEventPacket::BossKilled, v1001::LegacyTelemetryEventPacket::SlashCommand, v1001::LegacyTelemetryEventPacket::MobBorn, v1001::LegacyTelemetryEventPacket::POICauldronUsed, v1001::LegacyTelemetryEventPacket::ComposterUsed, v1001::LegacyTelemetryEventPacket::BellUsed, v1001::LegacyTelemetryEventPacket::ActorDefinition, v1001::LegacyTelemetryEventPacket::RaidUpdate, v1001::LegacyTelemetryEventPacket::TargetBlockHit, v1001::LegacyTelemetryEventPacket::PiglinBarter, v1001::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v1001::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v1001::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v1001::LegacyTelemetryEventPacket::ItemUsed, v1001::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v1001::LegacyTelemetryEventPacket::BellUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<12>(alt0);
                break;
            }
            case 13: {
                std::variant_alternative_t<13, std::variant<v1001::LegacyTelemetryEventPacket::Achievement, v1001::LegacyTelemetryEventPacket::Interaction, v1001::LegacyTelemetryEventPacket::PortalCreated, v1001::LegacyTelemetryEventPacket::PortalUsed, v1001::LegacyTelemetryEventPacket::MobKilled, v1001::LegacyTelemetryEventPacket::CauldronUsed, v1001::LegacyTelemetryEventPacket::PlayerDied, v1001::LegacyTelemetryEventPacket::BossKilled, v1001::LegacyTelemetryEventPacket::SlashCommand, v1001::LegacyTelemetryEventPacket::MobBorn, v1001::LegacyTelemetryEventPacket::POICauldronUsed, v1001::LegacyTelemetryEventPacket::ComposterUsed, v1001::LegacyTelemetryEventPacket::BellUsed, v1001::LegacyTelemetryEventPacket::ActorDefinition, v1001::LegacyTelemetryEventPacket::RaidUpdate, v1001::LegacyTelemetryEventPacket::TargetBlockHit, v1001::LegacyTelemetryEventPacket::PiglinBarter, v1001::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v1001::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v1001::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v1001::LegacyTelemetryEventPacket::ItemUsed, v1001::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v1001::LegacyTelemetryEventPacket::ActorDefinition>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<13>(alt0);
                break;
            }
            case 14: {
                std::variant_alternative_t<14, std::variant<v1001::LegacyTelemetryEventPacket::Achievement, v1001::LegacyTelemetryEventPacket::Interaction, v1001::LegacyTelemetryEventPacket::PortalCreated, v1001::LegacyTelemetryEventPacket::PortalUsed, v1001::LegacyTelemetryEventPacket::MobKilled, v1001::LegacyTelemetryEventPacket::CauldronUsed, v1001::LegacyTelemetryEventPacket::PlayerDied, v1001::LegacyTelemetryEventPacket::BossKilled, v1001::LegacyTelemetryEventPacket::SlashCommand, v1001::LegacyTelemetryEventPacket::MobBorn, v1001::LegacyTelemetryEventPacket::POICauldronUsed, v1001::LegacyTelemetryEventPacket::ComposterUsed, v1001::LegacyTelemetryEventPacket::BellUsed, v1001::LegacyTelemetryEventPacket::ActorDefinition, v1001::LegacyTelemetryEventPacket::RaidUpdate, v1001::LegacyTelemetryEventPacket::TargetBlockHit, v1001::LegacyTelemetryEventPacket::PiglinBarter, v1001::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v1001::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v1001::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v1001::LegacyTelemetryEventPacket::ItemUsed, v1001::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v1001::LegacyTelemetryEventPacket::RaidUpdate>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<14>(alt0);
                break;
            }
            case 15: {
                std::variant_alternative_t<15, std::variant<v1001::LegacyTelemetryEventPacket::Achievement, v1001::LegacyTelemetryEventPacket::Interaction, v1001::LegacyTelemetryEventPacket::PortalCreated, v1001::LegacyTelemetryEventPacket::PortalUsed, v1001::LegacyTelemetryEventPacket::MobKilled, v1001::LegacyTelemetryEventPacket::CauldronUsed, v1001::LegacyTelemetryEventPacket::PlayerDied, v1001::LegacyTelemetryEventPacket::BossKilled, v1001::LegacyTelemetryEventPacket::SlashCommand, v1001::LegacyTelemetryEventPacket::MobBorn, v1001::LegacyTelemetryEventPacket::POICauldronUsed, v1001::LegacyTelemetryEventPacket::ComposterUsed, v1001::LegacyTelemetryEventPacket::BellUsed, v1001::LegacyTelemetryEventPacket::ActorDefinition, v1001::LegacyTelemetryEventPacket::RaidUpdate, v1001::LegacyTelemetryEventPacket::TargetBlockHit, v1001::LegacyTelemetryEventPacket::PiglinBarter, v1001::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v1001::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v1001::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v1001::LegacyTelemetryEventPacket::ItemUsed, v1001::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v1001::LegacyTelemetryEventPacket::TargetBlockHit>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<15>(alt0);
                break;
            }
            case 16: {
                std::variant_alternative_t<16, std::variant<v1001::LegacyTelemetryEventPacket::Achievement, v1001::LegacyTelemetryEventPacket::Interaction, v1001::LegacyTelemetryEventPacket::PortalCreated, v1001::LegacyTelemetryEventPacket::PortalUsed, v1001::LegacyTelemetryEventPacket::MobKilled, v1001::LegacyTelemetryEventPacket::CauldronUsed, v1001::LegacyTelemetryEventPacket::PlayerDied, v1001::LegacyTelemetryEventPacket::BossKilled, v1001::LegacyTelemetryEventPacket::SlashCommand, v1001::LegacyTelemetryEventPacket::MobBorn, v1001::LegacyTelemetryEventPacket::POICauldronUsed, v1001::LegacyTelemetryEventPacket::ComposterUsed, v1001::LegacyTelemetryEventPacket::BellUsed, v1001::LegacyTelemetryEventPacket::ActorDefinition, v1001::LegacyTelemetryEventPacket::RaidUpdate, v1001::LegacyTelemetryEventPacket::TargetBlockHit, v1001::LegacyTelemetryEventPacket::PiglinBarter, v1001::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v1001::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v1001::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v1001::LegacyTelemetryEventPacket::ItemUsed, v1001::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v1001::LegacyTelemetryEventPacket::PiglinBarter>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<16>(alt0);
                break;
            }
            case 17: {
                std::variant_alternative_t<17, std::variant<v1001::LegacyTelemetryEventPacket::Achievement, v1001::LegacyTelemetryEventPacket::Interaction, v1001::LegacyTelemetryEventPacket::PortalCreated, v1001::LegacyTelemetryEventPacket::PortalUsed, v1001::LegacyTelemetryEventPacket::MobKilled, v1001::LegacyTelemetryEventPacket::CauldronUsed, v1001::LegacyTelemetryEventPacket::PlayerDied, v1001::LegacyTelemetryEventPacket::BossKilled, v1001::LegacyTelemetryEventPacket::SlashCommand, v1001::LegacyTelemetryEventPacket::MobBorn, v1001::LegacyTelemetryEventPacket::POICauldronUsed, v1001::LegacyTelemetryEventPacket::ComposterUsed, v1001::LegacyTelemetryEventPacket::BellUsed, v1001::LegacyTelemetryEventPacket::ActorDefinition, v1001::LegacyTelemetryEventPacket::RaidUpdate, v1001::LegacyTelemetryEventPacket::TargetBlockHit, v1001::LegacyTelemetryEventPacket::PiglinBarter, v1001::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v1001::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v1001::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v1001::LegacyTelemetryEventPacket::ItemUsed, v1001::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v1001::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<17>(alt0);
                break;
            }
            case 18: {
                std::variant_alternative_t<18, std::variant<v1001::LegacyTelemetryEventPacket::Achievement, v1001::LegacyTelemetryEventPacket::Interaction, v1001::LegacyTelemetryEventPacket::PortalCreated, v1001::LegacyTelemetryEventPacket::PortalUsed, v1001::LegacyTelemetryEventPacket::MobKilled, v1001::LegacyTelemetryEventPacket::CauldronUsed, v1001::LegacyTelemetryEventPacket::PlayerDied, v1001::LegacyTelemetryEventPacket::BossKilled, v1001::LegacyTelemetryEventPacket::SlashCommand, v1001::LegacyTelemetryEventPacket::MobBorn, v1001::LegacyTelemetryEventPacket::POICauldronUsed, v1001::LegacyTelemetryEventPacket::ComposterUsed, v1001::LegacyTelemetryEventPacket::BellUsed, v1001::LegacyTelemetryEventPacket::ActorDefinition, v1001::LegacyTelemetryEventPacket::RaidUpdate, v1001::LegacyTelemetryEventPacket::TargetBlockHit, v1001::LegacyTelemetryEventPacket::PiglinBarter, v1001::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v1001::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v1001::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v1001::LegacyTelemetryEventPacket::ItemUsed, v1001::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v1001::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<18>(alt0);
                break;
            }
            case 19: {
                std::variant_alternative_t<19, std::variant<v1001::LegacyTelemetryEventPacket::Achievement, v1001::LegacyTelemetryEventPacket::Interaction, v1001::LegacyTelemetryEventPacket::PortalCreated, v1001::LegacyTelemetryEventPacket::PortalUsed, v1001::LegacyTelemetryEventPacket::MobKilled, v1001::LegacyTelemetryEventPacket::CauldronUsed, v1001::LegacyTelemetryEventPacket::PlayerDied, v1001::LegacyTelemetryEventPacket::BossKilled, v1001::LegacyTelemetryEventPacket::SlashCommand, v1001::LegacyTelemetryEventPacket::MobBorn, v1001::LegacyTelemetryEventPacket::POICauldronUsed, v1001::LegacyTelemetryEventPacket::ComposterUsed, v1001::LegacyTelemetryEventPacket::BellUsed, v1001::LegacyTelemetryEventPacket::ActorDefinition, v1001::LegacyTelemetryEventPacket::RaidUpdate, v1001::LegacyTelemetryEventPacket::TargetBlockHit, v1001::LegacyTelemetryEventPacket::PiglinBarter, v1001::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v1001::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v1001::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v1001::LegacyTelemetryEventPacket::ItemUsed, v1001::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v1001::LegacyTelemetryEventPacket::CodeBuilderScoreboard>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<19>(alt0);
                break;
            }
            case 20: {
                std::variant_alternative_t<20, std::variant<v1001::LegacyTelemetryEventPacket::Achievement, v1001::LegacyTelemetryEventPacket::Interaction, v1001::LegacyTelemetryEventPacket::PortalCreated, v1001::LegacyTelemetryEventPacket::PortalUsed, v1001::LegacyTelemetryEventPacket::MobKilled, v1001::LegacyTelemetryEventPacket::CauldronUsed, v1001::LegacyTelemetryEventPacket::PlayerDied, v1001::LegacyTelemetryEventPacket::BossKilled, v1001::LegacyTelemetryEventPacket::SlashCommand, v1001::LegacyTelemetryEventPacket::MobBorn, v1001::LegacyTelemetryEventPacket::POICauldronUsed, v1001::LegacyTelemetryEventPacket::ComposterUsed, v1001::LegacyTelemetryEventPacket::BellUsed, v1001::LegacyTelemetryEventPacket::ActorDefinition, v1001::LegacyTelemetryEventPacket::RaidUpdate, v1001::LegacyTelemetryEventPacket::TargetBlockHit, v1001::LegacyTelemetryEventPacket::PiglinBarter, v1001::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v1001::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v1001::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v1001::LegacyTelemetryEventPacket::ItemUsed, v1001::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v1001::LegacyTelemetryEventPacket::ItemUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<20>(alt0);
                break;
            }
            case 21: {
                std::variant_alternative_t<21, std::variant<v1001::LegacyTelemetryEventPacket::Achievement, v1001::LegacyTelemetryEventPacket::Interaction, v1001::LegacyTelemetryEventPacket::PortalCreated, v1001::LegacyTelemetryEventPacket::PortalUsed, v1001::LegacyTelemetryEventPacket::MobKilled, v1001::LegacyTelemetryEventPacket::CauldronUsed, v1001::LegacyTelemetryEventPacket::PlayerDied, v1001::LegacyTelemetryEventPacket::BossKilled, v1001::LegacyTelemetryEventPacket::SlashCommand, v1001::LegacyTelemetryEventPacket::MobBorn, v1001::LegacyTelemetryEventPacket::POICauldronUsed, v1001::LegacyTelemetryEventPacket::ComposterUsed, v1001::LegacyTelemetryEventPacket::BellUsed, v1001::LegacyTelemetryEventPacket::ActorDefinition, v1001::LegacyTelemetryEventPacket::RaidUpdate, v1001::LegacyTelemetryEventPacket::TargetBlockHit, v1001::LegacyTelemetryEventPacket::PiglinBarter, v1001::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v1001::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v1001::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v1001::LegacyTelemetryEventPacket::ItemUsed, v1001::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v1001::LegacyTelemetryEventPacket::Empty>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<21>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.event_data = var0;
    }
    return out;
}

void Serializer<v2168::LegacyTelemetryEventPacket>::serialize(BinaryWriter &stream, const v2168::LegacyTelemetryEventPacket &value)
{
    stream.writeVarInt<std::int64_t>(value.player_unique_id);
    stream.writeVarInt<std::int32_t>(value.type);
    stream.write<bool>(value.use_player_id);
    stream.writeVarInt<std::uint32_t>((value.event_data).index());
    switch ((value.event_data).index()) {
        case 0: {
            Serializer<v2168::LegacyTelemetryEventPacket::Achievement>::serialize(stream, std::get<0>(value.event_data));
            break;
        }
        case 1: {
            Serializer<v2168::LegacyTelemetryEventPacket::Interaction>::serialize(stream, std::get<1>(value.event_data));
            break;
        }
        case 2: {
            Serializer<v2168::LegacyTelemetryEventPacket::PortalCreated>::serialize(stream, std::get<2>(value.event_data));
            break;
        }
        case 3: {
            Serializer<v2168::LegacyTelemetryEventPacket::PortalUsed>::serialize(stream, std::get<3>(value.event_data));
            break;
        }
        case 4: {
            Serializer<v2168::LegacyTelemetryEventPacket::MobKilled>::serialize(stream, std::get<4>(value.event_data));
            break;
        }
        case 5: {
            Serializer<v2168::LegacyTelemetryEventPacket::CauldronUsed>::serialize(stream, std::get<5>(value.event_data));
            break;
        }
        case 6: {
            Serializer<v2168::LegacyTelemetryEventPacket::PlayerDied>::serialize(stream, std::get<6>(value.event_data));
            break;
        }
        case 7: {
            Serializer<v2168::LegacyTelemetryEventPacket::BossKilled>::serialize(stream, std::get<7>(value.event_data));
            break;
        }
        case 8: {
            Serializer<v2168::LegacyTelemetryEventPacket::SlashCommand>::serialize(stream, std::get<8>(value.event_data));
            break;
        }
        case 9: {
            Serializer<v2168::LegacyTelemetryEventPacket::MobBorn>::serialize(stream, std::get<9>(value.event_data));
            break;
        }
        case 10: {
            Serializer<v2168::LegacyTelemetryEventPacket::POICauldronUsed>::serialize(stream, std::get<10>(value.event_data));
            break;
        }
        case 11: {
            Serializer<v2168::LegacyTelemetryEventPacket::ComposterUsed>::serialize(stream, std::get<11>(value.event_data));
            break;
        }
        case 12: {
            Serializer<v2168::LegacyTelemetryEventPacket::BellUsed>::serialize(stream, std::get<12>(value.event_data));
            break;
        }
        case 13: {
            Serializer<v2168::LegacyTelemetryEventPacket::ActorDefinition>::serialize(stream, std::get<13>(value.event_data));
            break;
        }
        case 14: {
            Serializer<v2168::LegacyTelemetryEventPacket::RaidUpdate>::serialize(stream, std::get<14>(value.event_data));
            break;
        }
        case 15: {
            Serializer<v2168::LegacyTelemetryEventPacket::TargetBlockHit>::serialize(stream, std::get<15>(value.event_data));
            break;
        }
        case 16: {
            Serializer<v2168::LegacyTelemetryEventPacket::PiglinBarter>::serialize(stream, std::get<16>(value.event_data));
            break;
        }
        case 17: {
            Serializer<v2168::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper>::serialize(stream, std::get<17>(value.event_data));
            break;
        }
        case 18: {
            Serializer<v2168::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction>::serialize(stream, std::get<18>(value.event_data));
            break;
        }
        case 19: {
            Serializer<v2168::LegacyTelemetryEventPacket::CodeBuilderScoreboard>::serialize(stream, std::get<19>(value.event_data));
            break;
        }
        case 20: {
            Serializer<v2168::LegacyTelemetryEventPacket::ItemUsed>::serialize(stream, std::get<20>(value.event_data));
            break;
        }
        case 21: {
            Serializer<v2168::LegacyTelemetryEventPacket::Empty>::serialize(stream, std::get<21>(value.event_data));
            break;
        }
    }
}

auto Serializer<v2168::LegacyTelemetryEventPacket>::deserialize(BinaryReader &stream) -> std::expected<v2168::LegacyTelemetryEventPacket, std::error_code>
{
    v2168::LegacyTelemetryEventPacket out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.player_unique_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<v2168::LegacyTelemetryEventPacket::Type>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.use_player_id = static_cast<bool>(*v);
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v2168::LegacyTelemetryEventPacket::Achievement, v2168::LegacyTelemetryEventPacket::Interaction, v2168::LegacyTelemetryEventPacket::PortalCreated, v2168::LegacyTelemetryEventPacket::PortalUsed, v2168::LegacyTelemetryEventPacket::MobKilled, v2168::LegacyTelemetryEventPacket::CauldronUsed, v2168::LegacyTelemetryEventPacket::PlayerDied, v2168::LegacyTelemetryEventPacket::BossKilled, v2168::LegacyTelemetryEventPacket::SlashCommand, v2168::LegacyTelemetryEventPacket::MobBorn, v2168::LegacyTelemetryEventPacket::POICauldronUsed, v2168::LegacyTelemetryEventPacket::ComposterUsed, v2168::LegacyTelemetryEventPacket::BellUsed, v2168::LegacyTelemetryEventPacket::ActorDefinition, v2168::LegacyTelemetryEventPacket::RaidUpdate, v2168::LegacyTelemetryEventPacket::TargetBlockHit, v2168::LegacyTelemetryEventPacket::PiglinBarter, v2168::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v2168::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v2168::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v2168::LegacyTelemetryEventPacket::ItemUsed, v2168::LegacyTelemetryEventPacket::Empty> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v2168::LegacyTelemetryEventPacket::Achievement, v2168::LegacyTelemetryEventPacket::Interaction, v2168::LegacyTelemetryEventPacket::PortalCreated, v2168::LegacyTelemetryEventPacket::PortalUsed, v2168::LegacyTelemetryEventPacket::MobKilled, v2168::LegacyTelemetryEventPacket::CauldronUsed, v2168::LegacyTelemetryEventPacket::PlayerDied, v2168::LegacyTelemetryEventPacket::BossKilled, v2168::LegacyTelemetryEventPacket::SlashCommand, v2168::LegacyTelemetryEventPacket::MobBorn, v2168::LegacyTelemetryEventPacket::POICauldronUsed, v2168::LegacyTelemetryEventPacket::ComposterUsed, v2168::LegacyTelemetryEventPacket::BellUsed, v2168::LegacyTelemetryEventPacket::ActorDefinition, v2168::LegacyTelemetryEventPacket::RaidUpdate, v2168::LegacyTelemetryEventPacket::TargetBlockHit, v2168::LegacyTelemetryEventPacket::PiglinBarter, v2168::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v2168::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v2168::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v2168::LegacyTelemetryEventPacket::ItemUsed, v2168::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v2168::LegacyTelemetryEventPacket::Achievement>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v2168::LegacyTelemetryEventPacket::Achievement, v2168::LegacyTelemetryEventPacket::Interaction, v2168::LegacyTelemetryEventPacket::PortalCreated, v2168::LegacyTelemetryEventPacket::PortalUsed, v2168::LegacyTelemetryEventPacket::MobKilled, v2168::LegacyTelemetryEventPacket::CauldronUsed, v2168::LegacyTelemetryEventPacket::PlayerDied, v2168::LegacyTelemetryEventPacket::BossKilled, v2168::LegacyTelemetryEventPacket::SlashCommand, v2168::LegacyTelemetryEventPacket::MobBorn, v2168::LegacyTelemetryEventPacket::POICauldronUsed, v2168::LegacyTelemetryEventPacket::ComposterUsed, v2168::LegacyTelemetryEventPacket::BellUsed, v2168::LegacyTelemetryEventPacket::ActorDefinition, v2168::LegacyTelemetryEventPacket::RaidUpdate, v2168::LegacyTelemetryEventPacket::TargetBlockHit, v2168::LegacyTelemetryEventPacket::PiglinBarter, v2168::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v2168::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v2168::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v2168::LegacyTelemetryEventPacket::ItemUsed, v2168::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v2168::LegacyTelemetryEventPacket::Interaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<v2168::LegacyTelemetryEventPacket::Achievement, v2168::LegacyTelemetryEventPacket::Interaction, v2168::LegacyTelemetryEventPacket::PortalCreated, v2168::LegacyTelemetryEventPacket::PortalUsed, v2168::LegacyTelemetryEventPacket::MobKilled, v2168::LegacyTelemetryEventPacket::CauldronUsed, v2168::LegacyTelemetryEventPacket::PlayerDied, v2168::LegacyTelemetryEventPacket::BossKilled, v2168::LegacyTelemetryEventPacket::SlashCommand, v2168::LegacyTelemetryEventPacket::MobBorn, v2168::LegacyTelemetryEventPacket::POICauldronUsed, v2168::LegacyTelemetryEventPacket::ComposterUsed, v2168::LegacyTelemetryEventPacket::BellUsed, v2168::LegacyTelemetryEventPacket::ActorDefinition, v2168::LegacyTelemetryEventPacket::RaidUpdate, v2168::LegacyTelemetryEventPacket::TargetBlockHit, v2168::LegacyTelemetryEventPacket::PiglinBarter, v2168::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v2168::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v2168::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v2168::LegacyTelemetryEventPacket::ItemUsed, v2168::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v2168::LegacyTelemetryEventPacket::PortalCreated>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<v2168::LegacyTelemetryEventPacket::Achievement, v2168::LegacyTelemetryEventPacket::Interaction, v2168::LegacyTelemetryEventPacket::PortalCreated, v2168::LegacyTelemetryEventPacket::PortalUsed, v2168::LegacyTelemetryEventPacket::MobKilled, v2168::LegacyTelemetryEventPacket::CauldronUsed, v2168::LegacyTelemetryEventPacket::PlayerDied, v2168::LegacyTelemetryEventPacket::BossKilled, v2168::LegacyTelemetryEventPacket::SlashCommand, v2168::LegacyTelemetryEventPacket::MobBorn, v2168::LegacyTelemetryEventPacket::POICauldronUsed, v2168::LegacyTelemetryEventPacket::ComposterUsed, v2168::LegacyTelemetryEventPacket::BellUsed, v2168::LegacyTelemetryEventPacket::ActorDefinition, v2168::LegacyTelemetryEventPacket::RaidUpdate, v2168::LegacyTelemetryEventPacket::TargetBlockHit, v2168::LegacyTelemetryEventPacket::PiglinBarter, v2168::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v2168::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v2168::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v2168::LegacyTelemetryEventPacket::ItemUsed, v2168::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v2168::LegacyTelemetryEventPacket::PortalUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            case 4: {
                std::variant_alternative_t<4, std::variant<v2168::LegacyTelemetryEventPacket::Achievement, v2168::LegacyTelemetryEventPacket::Interaction, v2168::LegacyTelemetryEventPacket::PortalCreated, v2168::LegacyTelemetryEventPacket::PortalUsed, v2168::LegacyTelemetryEventPacket::MobKilled, v2168::LegacyTelemetryEventPacket::CauldronUsed, v2168::LegacyTelemetryEventPacket::PlayerDied, v2168::LegacyTelemetryEventPacket::BossKilled, v2168::LegacyTelemetryEventPacket::SlashCommand, v2168::LegacyTelemetryEventPacket::MobBorn, v2168::LegacyTelemetryEventPacket::POICauldronUsed, v2168::LegacyTelemetryEventPacket::ComposterUsed, v2168::LegacyTelemetryEventPacket::BellUsed, v2168::LegacyTelemetryEventPacket::ActorDefinition, v2168::LegacyTelemetryEventPacket::RaidUpdate, v2168::LegacyTelemetryEventPacket::TargetBlockHit, v2168::LegacyTelemetryEventPacket::PiglinBarter, v2168::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v2168::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v2168::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v2168::LegacyTelemetryEventPacket::ItemUsed, v2168::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v2168::LegacyTelemetryEventPacket::MobKilled>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<4>(alt0);
                break;
            }
            case 5: {
                std::variant_alternative_t<5, std::variant<v2168::LegacyTelemetryEventPacket::Achievement, v2168::LegacyTelemetryEventPacket::Interaction, v2168::LegacyTelemetryEventPacket::PortalCreated, v2168::LegacyTelemetryEventPacket::PortalUsed, v2168::LegacyTelemetryEventPacket::MobKilled, v2168::LegacyTelemetryEventPacket::CauldronUsed, v2168::LegacyTelemetryEventPacket::PlayerDied, v2168::LegacyTelemetryEventPacket::BossKilled, v2168::LegacyTelemetryEventPacket::SlashCommand, v2168::LegacyTelemetryEventPacket::MobBorn, v2168::LegacyTelemetryEventPacket::POICauldronUsed, v2168::LegacyTelemetryEventPacket::ComposterUsed, v2168::LegacyTelemetryEventPacket::BellUsed, v2168::LegacyTelemetryEventPacket::ActorDefinition, v2168::LegacyTelemetryEventPacket::RaidUpdate, v2168::LegacyTelemetryEventPacket::TargetBlockHit, v2168::LegacyTelemetryEventPacket::PiglinBarter, v2168::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v2168::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v2168::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v2168::LegacyTelemetryEventPacket::ItemUsed, v2168::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v2168::LegacyTelemetryEventPacket::CauldronUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<5>(alt0);
                break;
            }
            case 6: {
                std::variant_alternative_t<6, std::variant<v2168::LegacyTelemetryEventPacket::Achievement, v2168::LegacyTelemetryEventPacket::Interaction, v2168::LegacyTelemetryEventPacket::PortalCreated, v2168::LegacyTelemetryEventPacket::PortalUsed, v2168::LegacyTelemetryEventPacket::MobKilled, v2168::LegacyTelemetryEventPacket::CauldronUsed, v2168::LegacyTelemetryEventPacket::PlayerDied, v2168::LegacyTelemetryEventPacket::BossKilled, v2168::LegacyTelemetryEventPacket::SlashCommand, v2168::LegacyTelemetryEventPacket::MobBorn, v2168::LegacyTelemetryEventPacket::POICauldronUsed, v2168::LegacyTelemetryEventPacket::ComposterUsed, v2168::LegacyTelemetryEventPacket::BellUsed, v2168::LegacyTelemetryEventPacket::ActorDefinition, v2168::LegacyTelemetryEventPacket::RaidUpdate, v2168::LegacyTelemetryEventPacket::TargetBlockHit, v2168::LegacyTelemetryEventPacket::PiglinBarter, v2168::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v2168::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v2168::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v2168::LegacyTelemetryEventPacket::ItemUsed, v2168::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v2168::LegacyTelemetryEventPacket::PlayerDied>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<6>(alt0);
                break;
            }
            case 7: {
                std::variant_alternative_t<7, std::variant<v2168::LegacyTelemetryEventPacket::Achievement, v2168::LegacyTelemetryEventPacket::Interaction, v2168::LegacyTelemetryEventPacket::PortalCreated, v2168::LegacyTelemetryEventPacket::PortalUsed, v2168::LegacyTelemetryEventPacket::MobKilled, v2168::LegacyTelemetryEventPacket::CauldronUsed, v2168::LegacyTelemetryEventPacket::PlayerDied, v2168::LegacyTelemetryEventPacket::BossKilled, v2168::LegacyTelemetryEventPacket::SlashCommand, v2168::LegacyTelemetryEventPacket::MobBorn, v2168::LegacyTelemetryEventPacket::POICauldronUsed, v2168::LegacyTelemetryEventPacket::ComposterUsed, v2168::LegacyTelemetryEventPacket::BellUsed, v2168::LegacyTelemetryEventPacket::ActorDefinition, v2168::LegacyTelemetryEventPacket::RaidUpdate, v2168::LegacyTelemetryEventPacket::TargetBlockHit, v2168::LegacyTelemetryEventPacket::PiglinBarter, v2168::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v2168::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v2168::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v2168::LegacyTelemetryEventPacket::ItemUsed, v2168::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v2168::LegacyTelemetryEventPacket::BossKilled>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<7>(alt0);
                break;
            }
            case 8: {
                std::variant_alternative_t<8, std::variant<v2168::LegacyTelemetryEventPacket::Achievement, v2168::LegacyTelemetryEventPacket::Interaction, v2168::LegacyTelemetryEventPacket::PortalCreated, v2168::LegacyTelemetryEventPacket::PortalUsed, v2168::LegacyTelemetryEventPacket::MobKilled, v2168::LegacyTelemetryEventPacket::CauldronUsed, v2168::LegacyTelemetryEventPacket::PlayerDied, v2168::LegacyTelemetryEventPacket::BossKilled, v2168::LegacyTelemetryEventPacket::SlashCommand, v2168::LegacyTelemetryEventPacket::MobBorn, v2168::LegacyTelemetryEventPacket::POICauldronUsed, v2168::LegacyTelemetryEventPacket::ComposterUsed, v2168::LegacyTelemetryEventPacket::BellUsed, v2168::LegacyTelemetryEventPacket::ActorDefinition, v2168::LegacyTelemetryEventPacket::RaidUpdate, v2168::LegacyTelemetryEventPacket::TargetBlockHit, v2168::LegacyTelemetryEventPacket::PiglinBarter, v2168::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v2168::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v2168::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v2168::LegacyTelemetryEventPacket::ItemUsed, v2168::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v2168::LegacyTelemetryEventPacket::SlashCommand>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<8>(alt0);
                break;
            }
            case 9: {
                std::variant_alternative_t<9, std::variant<v2168::LegacyTelemetryEventPacket::Achievement, v2168::LegacyTelemetryEventPacket::Interaction, v2168::LegacyTelemetryEventPacket::PortalCreated, v2168::LegacyTelemetryEventPacket::PortalUsed, v2168::LegacyTelemetryEventPacket::MobKilled, v2168::LegacyTelemetryEventPacket::CauldronUsed, v2168::LegacyTelemetryEventPacket::PlayerDied, v2168::LegacyTelemetryEventPacket::BossKilled, v2168::LegacyTelemetryEventPacket::SlashCommand, v2168::LegacyTelemetryEventPacket::MobBorn, v2168::LegacyTelemetryEventPacket::POICauldronUsed, v2168::LegacyTelemetryEventPacket::ComposterUsed, v2168::LegacyTelemetryEventPacket::BellUsed, v2168::LegacyTelemetryEventPacket::ActorDefinition, v2168::LegacyTelemetryEventPacket::RaidUpdate, v2168::LegacyTelemetryEventPacket::TargetBlockHit, v2168::LegacyTelemetryEventPacket::PiglinBarter, v2168::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v2168::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v2168::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v2168::LegacyTelemetryEventPacket::ItemUsed, v2168::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v2168::LegacyTelemetryEventPacket::MobBorn>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<9>(alt0);
                break;
            }
            case 10: {
                std::variant_alternative_t<10, std::variant<v2168::LegacyTelemetryEventPacket::Achievement, v2168::LegacyTelemetryEventPacket::Interaction, v2168::LegacyTelemetryEventPacket::PortalCreated, v2168::LegacyTelemetryEventPacket::PortalUsed, v2168::LegacyTelemetryEventPacket::MobKilled, v2168::LegacyTelemetryEventPacket::CauldronUsed, v2168::LegacyTelemetryEventPacket::PlayerDied, v2168::LegacyTelemetryEventPacket::BossKilled, v2168::LegacyTelemetryEventPacket::SlashCommand, v2168::LegacyTelemetryEventPacket::MobBorn, v2168::LegacyTelemetryEventPacket::POICauldronUsed, v2168::LegacyTelemetryEventPacket::ComposterUsed, v2168::LegacyTelemetryEventPacket::BellUsed, v2168::LegacyTelemetryEventPacket::ActorDefinition, v2168::LegacyTelemetryEventPacket::RaidUpdate, v2168::LegacyTelemetryEventPacket::TargetBlockHit, v2168::LegacyTelemetryEventPacket::PiglinBarter, v2168::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v2168::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v2168::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v2168::LegacyTelemetryEventPacket::ItemUsed, v2168::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v2168::LegacyTelemetryEventPacket::POICauldronUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<10>(alt0);
                break;
            }
            case 11: {
                std::variant_alternative_t<11, std::variant<v2168::LegacyTelemetryEventPacket::Achievement, v2168::LegacyTelemetryEventPacket::Interaction, v2168::LegacyTelemetryEventPacket::PortalCreated, v2168::LegacyTelemetryEventPacket::PortalUsed, v2168::LegacyTelemetryEventPacket::MobKilled, v2168::LegacyTelemetryEventPacket::CauldronUsed, v2168::LegacyTelemetryEventPacket::PlayerDied, v2168::LegacyTelemetryEventPacket::BossKilled, v2168::LegacyTelemetryEventPacket::SlashCommand, v2168::LegacyTelemetryEventPacket::MobBorn, v2168::LegacyTelemetryEventPacket::POICauldronUsed, v2168::LegacyTelemetryEventPacket::ComposterUsed, v2168::LegacyTelemetryEventPacket::BellUsed, v2168::LegacyTelemetryEventPacket::ActorDefinition, v2168::LegacyTelemetryEventPacket::RaidUpdate, v2168::LegacyTelemetryEventPacket::TargetBlockHit, v2168::LegacyTelemetryEventPacket::PiglinBarter, v2168::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v2168::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v2168::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v2168::LegacyTelemetryEventPacket::ItemUsed, v2168::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v2168::LegacyTelemetryEventPacket::ComposterUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<11>(alt0);
                break;
            }
            case 12: {
                std::variant_alternative_t<12, std::variant<v2168::LegacyTelemetryEventPacket::Achievement, v2168::LegacyTelemetryEventPacket::Interaction, v2168::LegacyTelemetryEventPacket::PortalCreated, v2168::LegacyTelemetryEventPacket::PortalUsed, v2168::LegacyTelemetryEventPacket::MobKilled, v2168::LegacyTelemetryEventPacket::CauldronUsed, v2168::LegacyTelemetryEventPacket::PlayerDied, v2168::LegacyTelemetryEventPacket::BossKilled, v2168::LegacyTelemetryEventPacket::SlashCommand, v2168::LegacyTelemetryEventPacket::MobBorn, v2168::LegacyTelemetryEventPacket::POICauldronUsed, v2168::LegacyTelemetryEventPacket::ComposterUsed, v2168::LegacyTelemetryEventPacket::BellUsed, v2168::LegacyTelemetryEventPacket::ActorDefinition, v2168::LegacyTelemetryEventPacket::RaidUpdate, v2168::LegacyTelemetryEventPacket::TargetBlockHit, v2168::LegacyTelemetryEventPacket::PiglinBarter, v2168::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v2168::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v2168::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v2168::LegacyTelemetryEventPacket::ItemUsed, v2168::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v2168::LegacyTelemetryEventPacket::BellUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<12>(alt0);
                break;
            }
            case 13: {
                std::variant_alternative_t<13, std::variant<v2168::LegacyTelemetryEventPacket::Achievement, v2168::LegacyTelemetryEventPacket::Interaction, v2168::LegacyTelemetryEventPacket::PortalCreated, v2168::LegacyTelemetryEventPacket::PortalUsed, v2168::LegacyTelemetryEventPacket::MobKilled, v2168::LegacyTelemetryEventPacket::CauldronUsed, v2168::LegacyTelemetryEventPacket::PlayerDied, v2168::LegacyTelemetryEventPacket::BossKilled, v2168::LegacyTelemetryEventPacket::SlashCommand, v2168::LegacyTelemetryEventPacket::MobBorn, v2168::LegacyTelemetryEventPacket::POICauldronUsed, v2168::LegacyTelemetryEventPacket::ComposterUsed, v2168::LegacyTelemetryEventPacket::BellUsed, v2168::LegacyTelemetryEventPacket::ActorDefinition, v2168::LegacyTelemetryEventPacket::RaidUpdate, v2168::LegacyTelemetryEventPacket::TargetBlockHit, v2168::LegacyTelemetryEventPacket::PiglinBarter, v2168::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v2168::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v2168::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v2168::LegacyTelemetryEventPacket::ItemUsed, v2168::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v2168::LegacyTelemetryEventPacket::ActorDefinition>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<13>(alt0);
                break;
            }
            case 14: {
                std::variant_alternative_t<14, std::variant<v2168::LegacyTelemetryEventPacket::Achievement, v2168::LegacyTelemetryEventPacket::Interaction, v2168::LegacyTelemetryEventPacket::PortalCreated, v2168::LegacyTelemetryEventPacket::PortalUsed, v2168::LegacyTelemetryEventPacket::MobKilled, v2168::LegacyTelemetryEventPacket::CauldronUsed, v2168::LegacyTelemetryEventPacket::PlayerDied, v2168::LegacyTelemetryEventPacket::BossKilled, v2168::LegacyTelemetryEventPacket::SlashCommand, v2168::LegacyTelemetryEventPacket::MobBorn, v2168::LegacyTelemetryEventPacket::POICauldronUsed, v2168::LegacyTelemetryEventPacket::ComposterUsed, v2168::LegacyTelemetryEventPacket::BellUsed, v2168::LegacyTelemetryEventPacket::ActorDefinition, v2168::LegacyTelemetryEventPacket::RaidUpdate, v2168::LegacyTelemetryEventPacket::TargetBlockHit, v2168::LegacyTelemetryEventPacket::PiglinBarter, v2168::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v2168::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v2168::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v2168::LegacyTelemetryEventPacket::ItemUsed, v2168::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v2168::LegacyTelemetryEventPacket::RaidUpdate>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<14>(alt0);
                break;
            }
            case 15: {
                std::variant_alternative_t<15, std::variant<v2168::LegacyTelemetryEventPacket::Achievement, v2168::LegacyTelemetryEventPacket::Interaction, v2168::LegacyTelemetryEventPacket::PortalCreated, v2168::LegacyTelemetryEventPacket::PortalUsed, v2168::LegacyTelemetryEventPacket::MobKilled, v2168::LegacyTelemetryEventPacket::CauldronUsed, v2168::LegacyTelemetryEventPacket::PlayerDied, v2168::LegacyTelemetryEventPacket::BossKilled, v2168::LegacyTelemetryEventPacket::SlashCommand, v2168::LegacyTelemetryEventPacket::MobBorn, v2168::LegacyTelemetryEventPacket::POICauldronUsed, v2168::LegacyTelemetryEventPacket::ComposterUsed, v2168::LegacyTelemetryEventPacket::BellUsed, v2168::LegacyTelemetryEventPacket::ActorDefinition, v2168::LegacyTelemetryEventPacket::RaidUpdate, v2168::LegacyTelemetryEventPacket::TargetBlockHit, v2168::LegacyTelemetryEventPacket::PiglinBarter, v2168::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v2168::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v2168::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v2168::LegacyTelemetryEventPacket::ItemUsed, v2168::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v2168::LegacyTelemetryEventPacket::TargetBlockHit>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<15>(alt0);
                break;
            }
            case 16: {
                std::variant_alternative_t<16, std::variant<v2168::LegacyTelemetryEventPacket::Achievement, v2168::LegacyTelemetryEventPacket::Interaction, v2168::LegacyTelemetryEventPacket::PortalCreated, v2168::LegacyTelemetryEventPacket::PortalUsed, v2168::LegacyTelemetryEventPacket::MobKilled, v2168::LegacyTelemetryEventPacket::CauldronUsed, v2168::LegacyTelemetryEventPacket::PlayerDied, v2168::LegacyTelemetryEventPacket::BossKilled, v2168::LegacyTelemetryEventPacket::SlashCommand, v2168::LegacyTelemetryEventPacket::MobBorn, v2168::LegacyTelemetryEventPacket::POICauldronUsed, v2168::LegacyTelemetryEventPacket::ComposterUsed, v2168::LegacyTelemetryEventPacket::BellUsed, v2168::LegacyTelemetryEventPacket::ActorDefinition, v2168::LegacyTelemetryEventPacket::RaidUpdate, v2168::LegacyTelemetryEventPacket::TargetBlockHit, v2168::LegacyTelemetryEventPacket::PiglinBarter, v2168::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v2168::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v2168::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v2168::LegacyTelemetryEventPacket::ItemUsed, v2168::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v2168::LegacyTelemetryEventPacket::PiglinBarter>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<16>(alt0);
                break;
            }
            case 17: {
                std::variant_alternative_t<17, std::variant<v2168::LegacyTelemetryEventPacket::Achievement, v2168::LegacyTelemetryEventPacket::Interaction, v2168::LegacyTelemetryEventPacket::PortalCreated, v2168::LegacyTelemetryEventPacket::PortalUsed, v2168::LegacyTelemetryEventPacket::MobKilled, v2168::LegacyTelemetryEventPacket::CauldronUsed, v2168::LegacyTelemetryEventPacket::PlayerDied, v2168::LegacyTelemetryEventPacket::BossKilled, v2168::LegacyTelemetryEventPacket::SlashCommand, v2168::LegacyTelemetryEventPacket::MobBorn, v2168::LegacyTelemetryEventPacket::POICauldronUsed, v2168::LegacyTelemetryEventPacket::ComposterUsed, v2168::LegacyTelemetryEventPacket::BellUsed, v2168::LegacyTelemetryEventPacket::ActorDefinition, v2168::LegacyTelemetryEventPacket::RaidUpdate, v2168::LegacyTelemetryEventPacket::TargetBlockHit, v2168::LegacyTelemetryEventPacket::PiglinBarter, v2168::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v2168::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v2168::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v2168::LegacyTelemetryEventPacket::ItemUsed, v2168::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v2168::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<17>(alt0);
                break;
            }
            case 18: {
                std::variant_alternative_t<18, std::variant<v2168::LegacyTelemetryEventPacket::Achievement, v2168::LegacyTelemetryEventPacket::Interaction, v2168::LegacyTelemetryEventPacket::PortalCreated, v2168::LegacyTelemetryEventPacket::PortalUsed, v2168::LegacyTelemetryEventPacket::MobKilled, v2168::LegacyTelemetryEventPacket::CauldronUsed, v2168::LegacyTelemetryEventPacket::PlayerDied, v2168::LegacyTelemetryEventPacket::BossKilled, v2168::LegacyTelemetryEventPacket::SlashCommand, v2168::LegacyTelemetryEventPacket::MobBorn, v2168::LegacyTelemetryEventPacket::POICauldronUsed, v2168::LegacyTelemetryEventPacket::ComposterUsed, v2168::LegacyTelemetryEventPacket::BellUsed, v2168::LegacyTelemetryEventPacket::ActorDefinition, v2168::LegacyTelemetryEventPacket::RaidUpdate, v2168::LegacyTelemetryEventPacket::TargetBlockHit, v2168::LegacyTelemetryEventPacket::PiglinBarter, v2168::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v2168::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v2168::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v2168::LegacyTelemetryEventPacket::ItemUsed, v2168::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v2168::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<18>(alt0);
                break;
            }
            case 19: {
                std::variant_alternative_t<19, std::variant<v2168::LegacyTelemetryEventPacket::Achievement, v2168::LegacyTelemetryEventPacket::Interaction, v2168::LegacyTelemetryEventPacket::PortalCreated, v2168::LegacyTelemetryEventPacket::PortalUsed, v2168::LegacyTelemetryEventPacket::MobKilled, v2168::LegacyTelemetryEventPacket::CauldronUsed, v2168::LegacyTelemetryEventPacket::PlayerDied, v2168::LegacyTelemetryEventPacket::BossKilled, v2168::LegacyTelemetryEventPacket::SlashCommand, v2168::LegacyTelemetryEventPacket::MobBorn, v2168::LegacyTelemetryEventPacket::POICauldronUsed, v2168::LegacyTelemetryEventPacket::ComposterUsed, v2168::LegacyTelemetryEventPacket::BellUsed, v2168::LegacyTelemetryEventPacket::ActorDefinition, v2168::LegacyTelemetryEventPacket::RaidUpdate, v2168::LegacyTelemetryEventPacket::TargetBlockHit, v2168::LegacyTelemetryEventPacket::PiglinBarter, v2168::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v2168::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v2168::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v2168::LegacyTelemetryEventPacket::ItemUsed, v2168::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v2168::LegacyTelemetryEventPacket::CodeBuilderScoreboard>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<19>(alt0);
                break;
            }
            case 20: {
                std::variant_alternative_t<20, std::variant<v2168::LegacyTelemetryEventPacket::Achievement, v2168::LegacyTelemetryEventPacket::Interaction, v2168::LegacyTelemetryEventPacket::PortalCreated, v2168::LegacyTelemetryEventPacket::PortalUsed, v2168::LegacyTelemetryEventPacket::MobKilled, v2168::LegacyTelemetryEventPacket::CauldronUsed, v2168::LegacyTelemetryEventPacket::PlayerDied, v2168::LegacyTelemetryEventPacket::BossKilled, v2168::LegacyTelemetryEventPacket::SlashCommand, v2168::LegacyTelemetryEventPacket::MobBorn, v2168::LegacyTelemetryEventPacket::POICauldronUsed, v2168::LegacyTelemetryEventPacket::ComposterUsed, v2168::LegacyTelemetryEventPacket::BellUsed, v2168::LegacyTelemetryEventPacket::ActorDefinition, v2168::LegacyTelemetryEventPacket::RaidUpdate, v2168::LegacyTelemetryEventPacket::TargetBlockHit, v2168::LegacyTelemetryEventPacket::PiglinBarter, v2168::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v2168::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v2168::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v2168::LegacyTelemetryEventPacket::ItemUsed, v2168::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v2168::LegacyTelemetryEventPacket::ItemUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<20>(alt0);
                break;
            }
            case 21: {
                std::variant_alternative_t<21, std::variant<v2168::LegacyTelemetryEventPacket::Achievement, v2168::LegacyTelemetryEventPacket::Interaction, v2168::LegacyTelemetryEventPacket::PortalCreated, v2168::LegacyTelemetryEventPacket::PortalUsed, v2168::LegacyTelemetryEventPacket::MobKilled, v2168::LegacyTelemetryEventPacket::CauldronUsed, v2168::LegacyTelemetryEventPacket::PlayerDied, v2168::LegacyTelemetryEventPacket::BossKilled, v2168::LegacyTelemetryEventPacket::SlashCommand, v2168::LegacyTelemetryEventPacket::MobBorn, v2168::LegacyTelemetryEventPacket::POICauldronUsed, v2168::LegacyTelemetryEventPacket::ComposterUsed, v2168::LegacyTelemetryEventPacket::BellUsed, v2168::LegacyTelemetryEventPacket::ActorDefinition, v2168::LegacyTelemetryEventPacket::RaidUpdate, v2168::LegacyTelemetryEventPacket::TargetBlockHit, v2168::LegacyTelemetryEventPacket::PiglinBarter, v2168::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v2168::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v2168::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v2168::LegacyTelemetryEventPacket::ItemUsed, v2168::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v2168::LegacyTelemetryEventPacket::Empty>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<21>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.event_data = var0;
    }
    return out;
}

void Serializer<v2225::LegacyTelemetryEventPacket>::serialize(BinaryWriter &stream, const v2225::LegacyTelemetryEventPacket &value)
{
    stream.writeVarInt<std::int64_t>(value.player_unique_id);
    stream.writeVarInt<std::int32_t>(value.type);
    stream.write<bool>(value.use_player_id);
    stream.writeVarInt<std::uint32_t>((value.event_data).index());
    switch ((value.event_data).index()) {
        case 0: {
            Serializer<v2225::LegacyTelemetryEventPacket::Achievement>::serialize(stream, std::get<0>(value.event_data));
            break;
        }
        case 1: {
            Serializer<v2225::LegacyTelemetryEventPacket::Interaction>::serialize(stream, std::get<1>(value.event_data));
            break;
        }
        case 2: {
            Serializer<v2225::LegacyTelemetryEventPacket::PortalCreated>::serialize(stream, std::get<2>(value.event_data));
            break;
        }
        case 3: {
            Serializer<v2225::LegacyTelemetryEventPacket::PortalUsed>::serialize(stream, std::get<3>(value.event_data));
            break;
        }
        case 4: {
            Serializer<v2225::LegacyTelemetryEventPacket::MobKilled>::serialize(stream, std::get<4>(value.event_data));
            break;
        }
        case 5: {
            Serializer<v2225::LegacyTelemetryEventPacket::CauldronUsed>::serialize(stream, std::get<5>(value.event_data));
            break;
        }
        case 6: {
            Serializer<v2225::LegacyTelemetryEventPacket::PlayerDied>::serialize(stream, std::get<6>(value.event_data));
            break;
        }
        case 7: {
            Serializer<v2225::LegacyTelemetryEventPacket::BossKilled>::serialize(stream, std::get<7>(value.event_data));
            break;
        }
        case 8: {
            Serializer<v2225::LegacyTelemetryEventPacket::SlashCommand>::serialize(stream, std::get<8>(value.event_data));
            break;
        }
        case 9: {
            Serializer<v2225::LegacyTelemetryEventPacket::MobBorn>::serialize(stream, std::get<9>(value.event_data));
            break;
        }
        case 10: {
            Serializer<v2225::LegacyTelemetryEventPacket::POICauldronUsed>::serialize(stream, std::get<10>(value.event_data));
            break;
        }
        case 11: {
            Serializer<v2225::LegacyTelemetryEventPacket::ComposterUsed>::serialize(stream, std::get<11>(value.event_data));
            break;
        }
        case 12: {
            Serializer<v2225::LegacyTelemetryEventPacket::BellUsed>::serialize(stream, std::get<12>(value.event_data));
            break;
        }
        case 13: {
            Serializer<v2225::LegacyTelemetryEventPacket::ActorDefinition>::serialize(stream, std::get<13>(value.event_data));
            break;
        }
        case 14: {
            Serializer<v2225::LegacyTelemetryEventPacket::RaidUpdate>::serialize(stream, std::get<14>(value.event_data));
            break;
        }
        case 15: {
            Serializer<v2225::LegacyTelemetryEventPacket::TargetBlockHit>::serialize(stream, std::get<15>(value.event_data));
            break;
        }
        case 16: {
            Serializer<v2225::LegacyTelemetryEventPacket::PiglinBarter>::serialize(stream, std::get<16>(value.event_data));
            break;
        }
        case 17: {
            Serializer<v2225::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper>::serialize(stream, std::get<17>(value.event_data));
            break;
        }
        case 18: {
            Serializer<v2225::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction>::serialize(stream, std::get<18>(value.event_data));
            break;
        }
        case 19: {
            Serializer<v2225::LegacyTelemetryEventPacket::CodeBuilderScoreboard>::serialize(stream, std::get<19>(value.event_data));
            break;
        }
        case 20: {
            Serializer<v2225::LegacyTelemetryEventPacket::ItemUsed>::serialize(stream, std::get<20>(value.event_data));
            break;
        }
        case 21: {
            Serializer<v2225::LegacyTelemetryEventPacket::Empty>::serialize(stream, std::get<21>(value.event_data));
            break;
        }
    }
}

auto Serializer<v2225::LegacyTelemetryEventPacket>::deserialize(BinaryReader &stream) -> std::expected<v2225::LegacyTelemetryEventPacket, std::error_code>
{
    v2225::LegacyTelemetryEventPacket out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.player_unique_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<v2225::LegacyTelemetryEventPacket::Type>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.use_player_id = static_cast<bool>(*v);
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v2225::LegacyTelemetryEventPacket::Achievement, v2225::LegacyTelemetryEventPacket::Interaction, v2225::LegacyTelemetryEventPacket::PortalCreated, v2225::LegacyTelemetryEventPacket::PortalUsed, v2225::LegacyTelemetryEventPacket::MobKilled, v2225::LegacyTelemetryEventPacket::CauldronUsed, v2225::LegacyTelemetryEventPacket::PlayerDied, v2225::LegacyTelemetryEventPacket::BossKilled, v2225::LegacyTelemetryEventPacket::SlashCommand, v2225::LegacyTelemetryEventPacket::MobBorn, v2225::LegacyTelemetryEventPacket::POICauldronUsed, v2225::LegacyTelemetryEventPacket::ComposterUsed, v2225::LegacyTelemetryEventPacket::BellUsed, v2225::LegacyTelemetryEventPacket::ActorDefinition, v2225::LegacyTelemetryEventPacket::RaidUpdate, v2225::LegacyTelemetryEventPacket::TargetBlockHit, v2225::LegacyTelemetryEventPacket::PiglinBarter, v2225::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v2225::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v2225::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v2225::LegacyTelemetryEventPacket::ItemUsed, v2225::LegacyTelemetryEventPacket::Empty> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v2225::LegacyTelemetryEventPacket::Achievement, v2225::LegacyTelemetryEventPacket::Interaction, v2225::LegacyTelemetryEventPacket::PortalCreated, v2225::LegacyTelemetryEventPacket::PortalUsed, v2225::LegacyTelemetryEventPacket::MobKilled, v2225::LegacyTelemetryEventPacket::CauldronUsed, v2225::LegacyTelemetryEventPacket::PlayerDied, v2225::LegacyTelemetryEventPacket::BossKilled, v2225::LegacyTelemetryEventPacket::SlashCommand, v2225::LegacyTelemetryEventPacket::MobBorn, v2225::LegacyTelemetryEventPacket::POICauldronUsed, v2225::LegacyTelemetryEventPacket::ComposterUsed, v2225::LegacyTelemetryEventPacket::BellUsed, v2225::LegacyTelemetryEventPacket::ActorDefinition, v2225::LegacyTelemetryEventPacket::RaidUpdate, v2225::LegacyTelemetryEventPacket::TargetBlockHit, v2225::LegacyTelemetryEventPacket::PiglinBarter, v2225::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v2225::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v2225::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v2225::LegacyTelemetryEventPacket::ItemUsed, v2225::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v2225::LegacyTelemetryEventPacket::Achievement>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v2225::LegacyTelemetryEventPacket::Achievement, v2225::LegacyTelemetryEventPacket::Interaction, v2225::LegacyTelemetryEventPacket::PortalCreated, v2225::LegacyTelemetryEventPacket::PortalUsed, v2225::LegacyTelemetryEventPacket::MobKilled, v2225::LegacyTelemetryEventPacket::CauldronUsed, v2225::LegacyTelemetryEventPacket::PlayerDied, v2225::LegacyTelemetryEventPacket::BossKilled, v2225::LegacyTelemetryEventPacket::SlashCommand, v2225::LegacyTelemetryEventPacket::MobBorn, v2225::LegacyTelemetryEventPacket::POICauldronUsed, v2225::LegacyTelemetryEventPacket::ComposterUsed, v2225::LegacyTelemetryEventPacket::BellUsed, v2225::LegacyTelemetryEventPacket::ActorDefinition, v2225::LegacyTelemetryEventPacket::RaidUpdate, v2225::LegacyTelemetryEventPacket::TargetBlockHit, v2225::LegacyTelemetryEventPacket::PiglinBarter, v2225::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v2225::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v2225::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v2225::LegacyTelemetryEventPacket::ItemUsed, v2225::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v2225::LegacyTelemetryEventPacket::Interaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<v2225::LegacyTelemetryEventPacket::Achievement, v2225::LegacyTelemetryEventPacket::Interaction, v2225::LegacyTelemetryEventPacket::PortalCreated, v2225::LegacyTelemetryEventPacket::PortalUsed, v2225::LegacyTelemetryEventPacket::MobKilled, v2225::LegacyTelemetryEventPacket::CauldronUsed, v2225::LegacyTelemetryEventPacket::PlayerDied, v2225::LegacyTelemetryEventPacket::BossKilled, v2225::LegacyTelemetryEventPacket::SlashCommand, v2225::LegacyTelemetryEventPacket::MobBorn, v2225::LegacyTelemetryEventPacket::POICauldronUsed, v2225::LegacyTelemetryEventPacket::ComposterUsed, v2225::LegacyTelemetryEventPacket::BellUsed, v2225::LegacyTelemetryEventPacket::ActorDefinition, v2225::LegacyTelemetryEventPacket::RaidUpdate, v2225::LegacyTelemetryEventPacket::TargetBlockHit, v2225::LegacyTelemetryEventPacket::PiglinBarter, v2225::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v2225::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v2225::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v2225::LegacyTelemetryEventPacket::ItemUsed, v2225::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v2225::LegacyTelemetryEventPacket::PortalCreated>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<v2225::LegacyTelemetryEventPacket::Achievement, v2225::LegacyTelemetryEventPacket::Interaction, v2225::LegacyTelemetryEventPacket::PortalCreated, v2225::LegacyTelemetryEventPacket::PortalUsed, v2225::LegacyTelemetryEventPacket::MobKilled, v2225::LegacyTelemetryEventPacket::CauldronUsed, v2225::LegacyTelemetryEventPacket::PlayerDied, v2225::LegacyTelemetryEventPacket::BossKilled, v2225::LegacyTelemetryEventPacket::SlashCommand, v2225::LegacyTelemetryEventPacket::MobBorn, v2225::LegacyTelemetryEventPacket::POICauldronUsed, v2225::LegacyTelemetryEventPacket::ComposterUsed, v2225::LegacyTelemetryEventPacket::BellUsed, v2225::LegacyTelemetryEventPacket::ActorDefinition, v2225::LegacyTelemetryEventPacket::RaidUpdate, v2225::LegacyTelemetryEventPacket::TargetBlockHit, v2225::LegacyTelemetryEventPacket::PiglinBarter, v2225::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v2225::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v2225::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v2225::LegacyTelemetryEventPacket::ItemUsed, v2225::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v2225::LegacyTelemetryEventPacket::PortalUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            case 4: {
                std::variant_alternative_t<4, std::variant<v2225::LegacyTelemetryEventPacket::Achievement, v2225::LegacyTelemetryEventPacket::Interaction, v2225::LegacyTelemetryEventPacket::PortalCreated, v2225::LegacyTelemetryEventPacket::PortalUsed, v2225::LegacyTelemetryEventPacket::MobKilled, v2225::LegacyTelemetryEventPacket::CauldronUsed, v2225::LegacyTelemetryEventPacket::PlayerDied, v2225::LegacyTelemetryEventPacket::BossKilled, v2225::LegacyTelemetryEventPacket::SlashCommand, v2225::LegacyTelemetryEventPacket::MobBorn, v2225::LegacyTelemetryEventPacket::POICauldronUsed, v2225::LegacyTelemetryEventPacket::ComposterUsed, v2225::LegacyTelemetryEventPacket::BellUsed, v2225::LegacyTelemetryEventPacket::ActorDefinition, v2225::LegacyTelemetryEventPacket::RaidUpdate, v2225::LegacyTelemetryEventPacket::TargetBlockHit, v2225::LegacyTelemetryEventPacket::PiglinBarter, v2225::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v2225::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v2225::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v2225::LegacyTelemetryEventPacket::ItemUsed, v2225::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v2225::LegacyTelemetryEventPacket::MobKilled>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<4>(alt0);
                break;
            }
            case 5: {
                std::variant_alternative_t<5, std::variant<v2225::LegacyTelemetryEventPacket::Achievement, v2225::LegacyTelemetryEventPacket::Interaction, v2225::LegacyTelemetryEventPacket::PortalCreated, v2225::LegacyTelemetryEventPacket::PortalUsed, v2225::LegacyTelemetryEventPacket::MobKilled, v2225::LegacyTelemetryEventPacket::CauldronUsed, v2225::LegacyTelemetryEventPacket::PlayerDied, v2225::LegacyTelemetryEventPacket::BossKilled, v2225::LegacyTelemetryEventPacket::SlashCommand, v2225::LegacyTelemetryEventPacket::MobBorn, v2225::LegacyTelemetryEventPacket::POICauldronUsed, v2225::LegacyTelemetryEventPacket::ComposterUsed, v2225::LegacyTelemetryEventPacket::BellUsed, v2225::LegacyTelemetryEventPacket::ActorDefinition, v2225::LegacyTelemetryEventPacket::RaidUpdate, v2225::LegacyTelemetryEventPacket::TargetBlockHit, v2225::LegacyTelemetryEventPacket::PiglinBarter, v2225::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v2225::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v2225::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v2225::LegacyTelemetryEventPacket::ItemUsed, v2225::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v2225::LegacyTelemetryEventPacket::CauldronUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<5>(alt0);
                break;
            }
            case 6: {
                std::variant_alternative_t<6, std::variant<v2225::LegacyTelemetryEventPacket::Achievement, v2225::LegacyTelemetryEventPacket::Interaction, v2225::LegacyTelemetryEventPacket::PortalCreated, v2225::LegacyTelemetryEventPacket::PortalUsed, v2225::LegacyTelemetryEventPacket::MobKilled, v2225::LegacyTelemetryEventPacket::CauldronUsed, v2225::LegacyTelemetryEventPacket::PlayerDied, v2225::LegacyTelemetryEventPacket::BossKilled, v2225::LegacyTelemetryEventPacket::SlashCommand, v2225::LegacyTelemetryEventPacket::MobBorn, v2225::LegacyTelemetryEventPacket::POICauldronUsed, v2225::LegacyTelemetryEventPacket::ComposterUsed, v2225::LegacyTelemetryEventPacket::BellUsed, v2225::LegacyTelemetryEventPacket::ActorDefinition, v2225::LegacyTelemetryEventPacket::RaidUpdate, v2225::LegacyTelemetryEventPacket::TargetBlockHit, v2225::LegacyTelemetryEventPacket::PiglinBarter, v2225::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v2225::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v2225::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v2225::LegacyTelemetryEventPacket::ItemUsed, v2225::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v2225::LegacyTelemetryEventPacket::PlayerDied>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<6>(alt0);
                break;
            }
            case 7: {
                std::variant_alternative_t<7, std::variant<v2225::LegacyTelemetryEventPacket::Achievement, v2225::LegacyTelemetryEventPacket::Interaction, v2225::LegacyTelemetryEventPacket::PortalCreated, v2225::LegacyTelemetryEventPacket::PortalUsed, v2225::LegacyTelemetryEventPacket::MobKilled, v2225::LegacyTelemetryEventPacket::CauldronUsed, v2225::LegacyTelemetryEventPacket::PlayerDied, v2225::LegacyTelemetryEventPacket::BossKilled, v2225::LegacyTelemetryEventPacket::SlashCommand, v2225::LegacyTelemetryEventPacket::MobBorn, v2225::LegacyTelemetryEventPacket::POICauldronUsed, v2225::LegacyTelemetryEventPacket::ComposterUsed, v2225::LegacyTelemetryEventPacket::BellUsed, v2225::LegacyTelemetryEventPacket::ActorDefinition, v2225::LegacyTelemetryEventPacket::RaidUpdate, v2225::LegacyTelemetryEventPacket::TargetBlockHit, v2225::LegacyTelemetryEventPacket::PiglinBarter, v2225::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v2225::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v2225::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v2225::LegacyTelemetryEventPacket::ItemUsed, v2225::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v2225::LegacyTelemetryEventPacket::BossKilled>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<7>(alt0);
                break;
            }
            case 8: {
                std::variant_alternative_t<8, std::variant<v2225::LegacyTelemetryEventPacket::Achievement, v2225::LegacyTelemetryEventPacket::Interaction, v2225::LegacyTelemetryEventPacket::PortalCreated, v2225::LegacyTelemetryEventPacket::PortalUsed, v2225::LegacyTelemetryEventPacket::MobKilled, v2225::LegacyTelemetryEventPacket::CauldronUsed, v2225::LegacyTelemetryEventPacket::PlayerDied, v2225::LegacyTelemetryEventPacket::BossKilled, v2225::LegacyTelemetryEventPacket::SlashCommand, v2225::LegacyTelemetryEventPacket::MobBorn, v2225::LegacyTelemetryEventPacket::POICauldronUsed, v2225::LegacyTelemetryEventPacket::ComposterUsed, v2225::LegacyTelemetryEventPacket::BellUsed, v2225::LegacyTelemetryEventPacket::ActorDefinition, v2225::LegacyTelemetryEventPacket::RaidUpdate, v2225::LegacyTelemetryEventPacket::TargetBlockHit, v2225::LegacyTelemetryEventPacket::PiglinBarter, v2225::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v2225::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v2225::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v2225::LegacyTelemetryEventPacket::ItemUsed, v2225::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v2225::LegacyTelemetryEventPacket::SlashCommand>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<8>(alt0);
                break;
            }
            case 9: {
                std::variant_alternative_t<9, std::variant<v2225::LegacyTelemetryEventPacket::Achievement, v2225::LegacyTelemetryEventPacket::Interaction, v2225::LegacyTelemetryEventPacket::PortalCreated, v2225::LegacyTelemetryEventPacket::PortalUsed, v2225::LegacyTelemetryEventPacket::MobKilled, v2225::LegacyTelemetryEventPacket::CauldronUsed, v2225::LegacyTelemetryEventPacket::PlayerDied, v2225::LegacyTelemetryEventPacket::BossKilled, v2225::LegacyTelemetryEventPacket::SlashCommand, v2225::LegacyTelemetryEventPacket::MobBorn, v2225::LegacyTelemetryEventPacket::POICauldronUsed, v2225::LegacyTelemetryEventPacket::ComposterUsed, v2225::LegacyTelemetryEventPacket::BellUsed, v2225::LegacyTelemetryEventPacket::ActorDefinition, v2225::LegacyTelemetryEventPacket::RaidUpdate, v2225::LegacyTelemetryEventPacket::TargetBlockHit, v2225::LegacyTelemetryEventPacket::PiglinBarter, v2225::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v2225::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v2225::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v2225::LegacyTelemetryEventPacket::ItemUsed, v2225::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v2225::LegacyTelemetryEventPacket::MobBorn>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<9>(alt0);
                break;
            }
            case 10: {
                std::variant_alternative_t<10, std::variant<v2225::LegacyTelemetryEventPacket::Achievement, v2225::LegacyTelemetryEventPacket::Interaction, v2225::LegacyTelemetryEventPacket::PortalCreated, v2225::LegacyTelemetryEventPacket::PortalUsed, v2225::LegacyTelemetryEventPacket::MobKilled, v2225::LegacyTelemetryEventPacket::CauldronUsed, v2225::LegacyTelemetryEventPacket::PlayerDied, v2225::LegacyTelemetryEventPacket::BossKilled, v2225::LegacyTelemetryEventPacket::SlashCommand, v2225::LegacyTelemetryEventPacket::MobBorn, v2225::LegacyTelemetryEventPacket::POICauldronUsed, v2225::LegacyTelemetryEventPacket::ComposterUsed, v2225::LegacyTelemetryEventPacket::BellUsed, v2225::LegacyTelemetryEventPacket::ActorDefinition, v2225::LegacyTelemetryEventPacket::RaidUpdate, v2225::LegacyTelemetryEventPacket::TargetBlockHit, v2225::LegacyTelemetryEventPacket::PiglinBarter, v2225::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v2225::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v2225::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v2225::LegacyTelemetryEventPacket::ItemUsed, v2225::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v2225::LegacyTelemetryEventPacket::POICauldronUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<10>(alt0);
                break;
            }
            case 11: {
                std::variant_alternative_t<11, std::variant<v2225::LegacyTelemetryEventPacket::Achievement, v2225::LegacyTelemetryEventPacket::Interaction, v2225::LegacyTelemetryEventPacket::PortalCreated, v2225::LegacyTelemetryEventPacket::PortalUsed, v2225::LegacyTelemetryEventPacket::MobKilled, v2225::LegacyTelemetryEventPacket::CauldronUsed, v2225::LegacyTelemetryEventPacket::PlayerDied, v2225::LegacyTelemetryEventPacket::BossKilled, v2225::LegacyTelemetryEventPacket::SlashCommand, v2225::LegacyTelemetryEventPacket::MobBorn, v2225::LegacyTelemetryEventPacket::POICauldronUsed, v2225::LegacyTelemetryEventPacket::ComposterUsed, v2225::LegacyTelemetryEventPacket::BellUsed, v2225::LegacyTelemetryEventPacket::ActorDefinition, v2225::LegacyTelemetryEventPacket::RaidUpdate, v2225::LegacyTelemetryEventPacket::TargetBlockHit, v2225::LegacyTelemetryEventPacket::PiglinBarter, v2225::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v2225::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v2225::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v2225::LegacyTelemetryEventPacket::ItemUsed, v2225::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v2225::LegacyTelemetryEventPacket::ComposterUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<11>(alt0);
                break;
            }
            case 12: {
                std::variant_alternative_t<12, std::variant<v2225::LegacyTelemetryEventPacket::Achievement, v2225::LegacyTelemetryEventPacket::Interaction, v2225::LegacyTelemetryEventPacket::PortalCreated, v2225::LegacyTelemetryEventPacket::PortalUsed, v2225::LegacyTelemetryEventPacket::MobKilled, v2225::LegacyTelemetryEventPacket::CauldronUsed, v2225::LegacyTelemetryEventPacket::PlayerDied, v2225::LegacyTelemetryEventPacket::BossKilled, v2225::LegacyTelemetryEventPacket::SlashCommand, v2225::LegacyTelemetryEventPacket::MobBorn, v2225::LegacyTelemetryEventPacket::POICauldronUsed, v2225::LegacyTelemetryEventPacket::ComposterUsed, v2225::LegacyTelemetryEventPacket::BellUsed, v2225::LegacyTelemetryEventPacket::ActorDefinition, v2225::LegacyTelemetryEventPacket::RaidUpdate, v2225::LegacyTelemetryEventPacket::TargetBlockHit, v2225::LegacyTelemetryEventPacket::PiglinBarter, v2225::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v2225::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v2225::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v2225::LegacyTelemetryEventPacket::ItemUsed, v2225::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v2225::LegacyTelemetryEventPacket::BellUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<12>(alt0);
                break;
            }
            case 13: {
                std::variant_alternative_t<13, std::variant<v2225::LegacyTelemetryEventPacket::Achievement, v2225::LegacyTelemetryEventPacket::Interaction, v2225::LegacyTelemetryEventPacket::PortalCreated, v2225::LegacyTelemetryEventPacket::PortalUsed, v2225::LegacyTelemetryEventPacket::MobKilled, v2225::LegacyTelemetryEventPacket::CauldronUsed, v2225::LegacyTelemetryEventPacket::PlayerDied, v2225::LegacyTelemetryEventPacket::BossKilled, v2225::LegacyTelemetryEventPacket::SlashCommand, v2225::LegacyTelemetryEventPacket::MobBorn, v2225::LegacyTelemetryEventPacket::POICauldronUsed, v2225::LegacyTelemetryEventPacket::ComposterUsed, v2225::LegacyTelemetryEventPacket::BellUsed, v2225::LegacyTelemetryEventPacket::ActorDefinition, v2225::LegacyTelemetryEventPacket::RaidUpdate, v2225::LegacyTelemetryEventPacket::TargetBlockHit, v2225::LegacyTelemetryEventPacket::PiglinBarter, v2225::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v2225::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v2225::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v2225::LegacyTelemetryEventPacket::ItemUsed, v2225::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v2225::LegacyTelemetryEventPacket::ActorDefinition>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<13>(alt0);
                break;
            }
            case 14: {
                std::variant_alternative_t<14, std::variant<v2225::LegacyTelemetryEventPacket::Achievement, v2225::LegacyTelemetryEventPacket::Interaction, v2225::LegacyTelemetryEventPacket::PortalCreated, v2225::LegacyTelemetryEventPacket::PortalUsed, v2225::LegacyTelemetryEventPacket::MobKilled, v2225::LegacyTelemetryEventPacket::CauldronUsed, v2225::LegacyTelemetryEventPacket::PlayerDied, v2225::LegacyTelemetryEventPacket::BossKilled, v2225::LegacyTelemetryEventPacket::SlashCommand, v2225::LegacyTelemetryEventPacket::MobBorn, v2225::LegacyTelemetryEventPacket::POICauldronUsed, v2225::LegacyTelemetryEventPacket::ComposterUsed, v2225::LegacyTelemetryEventPacket::BellUsed, v2225::LegacyTelemetryEventPacket::ActorDefinition, v2225::LegacyTelemetryEventPacket::RaidUpdate, v2225::LegacyTelemetryEventPacket::TargetBlockHit, v2225::LegacyTelemetryEventPacket::PiglinBarter, v2225::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v2225::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v2225::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v2225::LegacyTelemetryEventPacket::ItemUsed, v2225::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v2225::LegacyTelemetryEventPacket::RaidUpdate>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<14>(alt0);
                break;
            }
            case 15: {
                std::variant_alternative_t<15, std::variant<v2225::LegacyTelemetryEventPacket::Achievement, v2225::LegacyTelemetryEventPacket::Interaction, v2225::LegacyTelemetryEventPacket::PortalCreated, v2225::LegacyTelemetryEventPacket::PortalUsed, v2225::LegacyTelemetryEventPacket::MobKilled, v2225::LegacyTelemetryEventPacket::CauldronUsed, v2225::LegacyTelemetryEventPacket::PlayerDied, v2225::LegacyTelemetryEventPacket::BossKilled, v2225::LegacyTelemetryEventPacket::SlashCommand, v2225::LegacyTelemetryEventPacket::MobBorn, v2225::LegacyTelemetryEventPacket::POICauldronUsed, v2225::LegacyTelemetryEventPacket::ComposterUsed, v2225::LegacyTelemetryEventPacket::BellUsed, v2225::LegacyTelemetryEventPacket::ActorDefinition, v2225::LegacyTelemetryEventPacket::RaidUpdate, v2225::LegacyTelemetryEventPacket::TargetBlockHit, v2225::LegacyTelemetryEventPacket::PiglinBarter, v2225::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v2225::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v2225::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v2225::LegacyTelemetryEventPacket::ItemUsed, v2225::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v2225::LegacyTelemetryEventPacket::TargetBlockHit>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<15>(alt0);
                break;
            }
            case 16: {
                std::variant_alternative_t<16, std::variant<v2225::LegacyTelemetryEventPacket::Achievement, v2225::LegacyTelemetryEventPacket::Interaction, v2225::LegacyTelemetryEventPacket::PortalCreated, v2225::LegacyTelemetryEventPacket::PortalUsed, v2225::LegacyTelemetryEventPacket::MobKilled, v2225::LegacyTelemetryEventPacket::CauldronUsed, v2225::LegacyTelemetryEventPacket::PlayerDied, v2225::LegacyTelemetryEventPacket::BossKilled, v2225::LegacyTelemetryEventPacket::SlashCommand, v2225::LegacyTelemetryEventPacket::MobBorn, v2225::LegacyTelemetryEventPacket::POICauldronUsed, v2225::LegacyTelemetryEventPacket::ComposterUsed, v2225::LegacyTelemetryEventPacket::BellUsed, v2225::LegacyTelemetryEventPacket::ActorDefinition, v2225::LegacyTelemetryEventPacket::RaidUpdate, v2225::LegacyTelemetryEventPacket::TargetBlockHit, v2225::LegacyTelemetryEventPacket::PiglinBarter, v2225::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v2225::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v2225::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v2225::LegacyTelemetryEventPacket::ItemUsed, v2225::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v2225::LegacyTelemetryEventPacket::PiglinBarter>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<16>(alt0);
                break;
            }
            case 17: {
                std::variant_alternative_t<17, std::variant<v2225::LegacyTelemetryEventPacket::Achievement, v2225::LegacyTelemetryEventPacket::Interaction, v2225::LegacyTelemetryEventPacket::PortalCreated, v2225::LegacyTelemetryEventPacket::PortalUsed, v2225::LegacyTelemetryEventPacket::MobKilled, v2225::LegacyTelemetryEventPacket::CauldronUsed, v2225::LegacyTelemetryEventPacket::PlayerDied, v2225::LegacyTelemetryEventPacket::BossKilled, v2225::LegacyTelemetryEventPacket::SlashCommand, v2225::LegacyTelemetryEventPacket::MobBorn, v2225::LegacyTelemetryEventPacket::POICauldronUsed, v2225::LegacyTelemetryEventPacket::ComposterUsed, v2225::LegacyTelemetryEventPacket::BellUsed, v2225::LegacyTelemetryEventPacket::ActorDefinition, v2225::LegacyTelemetryEventPacket::RaidUpdate, v2225::LegacyTelemetryEventPacket::TargetBlockHit, v2225::LegacyTelemetryEventPacket::PiglinBarter, v2225::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v2225::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v2225::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v2225::LegacyTelemetryEventPacket::ItemUsed, v2225::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v2225::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<17>(alt0);
                break;
            }
            case 18: {
                std::variant_alternative_t<18, std::variant<v2225::LegacyTelemetryEventPacket::Achievement, v2225::LegacyTelemetryEventPacket::Interaction, v2225::LegacyTelemetryEventPacket::PortalCreated, v2225::LegacyTelemetryEventPacket::PortalUsed, v2225::LegacyTelemetryEventPacket::MobKilled, v2225::LegacyTelemetryEventPacket::CauldronUsed, v2225::LegacyTelemetryEventPacket::PlayerDied, v2225::LegacyTelemetryEventPacket::BossKilled, v2225::LegacyTelemetryEventPacket::SlashCommand, v2225::LegacyTelemetryEventPacket::MobBorn, v2225::LegacyTelemetryEventPacket::POICauldronUsed, v2225::LegacyTelemetryEventPacket::ComposterUsed, v2225::LegacyTelemetryEventPacket::BellUsed, v2225::LegacyTelemetryEventPacket::ActorDefinition, v2225::LegacyTelemetryEventPacket::RaidUpdate, v2225::LegacyTelemetryEventPacket::TargetBlockHit, v2225::LegacyTelemetryEventPacket::PiglinBarter, v2225::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v2225::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v2225::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v2225::LegacyTelemetryEventPacket::ItemUsed, v2225::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v2225::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<18>(alt0);
                break;
            }
            case 19: {
                std::variant_alternative_t<19, std::variant<v2225::LegacyTelemetryEventPacket::Achievement, v2225::LegacyTelemetryEventPacket::Interaction, v2225::LegacyTelemetryEventPacket::PortalCreated, v2225::LegacyTelemetryEventPacket::PortalUsed, v2225::LegacyTelemetryEventPacket::MobKilled, v2225::LegacyTelemetryEventPacket::CauldronUsed, v2225::LegacyTelemetryEventPacket::PlayerDied, v2225::LegacyTelemetryEventPacket::BossKilled, v2225::LegacyTelemetryEventPacket::SlashCommand, v2225::LegacyTelemetryEventPacket::MobBorn, v2225::LegacyTelemetryEventPacket::POICauldronUsed, v2225::LegacyTelemetryEventPacket::ComposterUsed, v2225::LegacyTelemetryEventPacket::BellUsed, v2225::LegacyTelemetryEventPacket::ActorDefinition, v2225::LegacyTelemetryEventPacket::RaidUpdate, v2225::LegacyTelemetryEventPacket::TargetBlockHit, v2225::LegacyTelemetryEventPacket::PiglinBarter, v2225::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v2225::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v2225::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v2225::LegacyTelemetryEventPacket::ItemUsed, v2225::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v2225::LegacyTelemetryEventPacket::CodeBuilderScoreboard>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<19>(alt0);
                break;
            }
            case 20: {
                std::variant_alternative_t<20, std::variant<v2225::LegacyTelemetryEventPacket::Achievement, v2225::LegacyTelemetryEventPacket::Interaction, v2225::LegacyTelemetryEventPacket::PortalCreated, v2225::LegacyTelemetryEventPacket::PortalUsed, v2225::LegacyTelemetryEventPacket::MobKilled, v2225::LegacyTelemetryEventPacket::CauldronUsed, v2225::LegacyTelemetryEventPacket::PlayerDied, v2225::LegacyTelemetryEventPacket::BossKilled, v2225::LegacyTelemetryEventPacket::SlashCommand, v2225::LegacyTelemetryEventPacket::MobBorn, v2225::LegacyTelemetryEventPacket::POICauldronUsed, v2225::LegacyTelemetryEventPacket::ComposterUsed, v2225::LegacyTelemetryEventPacket::BellUsed, v2225::LegacyTelemetryEventPacket::ActorDefinition, v2225::LegacyTelemetryEventPacket::RaidUpdate, v2225::LegacyTelemetryEventPacket::TargetBlockHit, v2225::LegacyTelemetryEventPacket::PiglinBarter, v2225::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v2225::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v2225::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v2225::LegacyTelemetryEventPacket::ItemUsed, v2225::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v2225::LegacyTelemetryEventPacket::ItemUsed>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<20>(alt0);
                break;
            }
            case 21: {
                std::variant_alternative_t<21, std::variant<v2225::LegacyTelemetryEventPacket::Achievement, v2225::LegacyTelemetryEventPacket::Interaction, v2225::LegacyTelemetryEventPacket::PortalCreated, v2225::LegacyTelemetryEventPacket::PortalUsed, v2225::LegacyTelemetryEventPacket::MobKilled, v2225::LegacyTelemetryEventPacket::CauldronUsed, v2225::LegacyTelemetryEventPacket::PlayerDied, v2225::LegacyTelemetryEventPacket::BossKilled, v2225::LegacyTelemetryEventPacket::SlashCommand, v2225::LegacyTelemetryEventPacket::MobBorn, v2225::LegacyTelemetryEventPacket::POICauldronUsed, v2225::LegacyTelemetryEventPacket::ComposterUsed, v2225::LegacyTelemetryEventPacket::BellUsed, v2225::LegacyTelemetryEventPacket::ActorDefinition, v2225::LegacyTelemetryEventPacket::RaidUpdate, v2225::LegacyTelemetryEventPacket::TargetBlockHit, v2225::LegacyTelemetryEventPacket::PiglinBarter, v2225::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v2225::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v2225::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v2225::LegacyTelemetryEventPacket::ItemUsed, v2225::LegacyTelemetryEventPacket::Empty>> alt0{};
                {
                    auto v = Serializer<v2225::LegacyTelemetryEventPacket::Empty>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<21>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.event_data = var0;
    }
    return out;
}

}  // namespace bedrock::protocol
