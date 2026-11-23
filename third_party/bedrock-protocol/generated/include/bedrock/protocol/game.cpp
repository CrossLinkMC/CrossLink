#include <bedrock/protocol/game.h>

namespace bedrock::protocol {


void Serializer<SpawnSettings>::serialize(BinaryWriter &stream, const SpawnSettings &value)
{
    stream.write<std::int16_t>(value.type);
    stream.write(value.user_defined_biome_name);
    stream.writeVarInt<std::int32_t>(value.dimension);
}

auto Serializer<SpawnSettings>::deserialize(BinaryReader &stream) -> std::expected<SpawnSettings, std::error_code>
{
    SpawnSettings out;
    {
        auto v = stream.read<std::int16_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<SpawnBiomeType>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.user_defined_biome_name = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.dimension = static_cast<DimensionType>(*v);
    }
    return out;
}

void Serializer<base::GameRule>::serialize(BinaryWriter &stream, const base::GameRule &value)
{
    stream.write(value.name);
    stream.write<bool>(value.can_be_modified_by_player);
    stream.writeVarInt<std::uint32_t>((value.value).index());
    switch ((value.value).index()) {
        case 0: {
            break;
        }
        case 1: {
            stream.write<bool>(std::get<1>(value.value));
            break;
        }
        case 2: {
            stream.writeVarInt<std::uint32_t>(std::get<2>(value.value));
            break;
        }
        case 3: {
            stream.write<float>(std::get<3>(value.value));
            break;
        }
    }
}

auto Serializer<base::GameRule>::deserialize(BinaryReader &stream) -> std::expected<base::GameRule, std::error_code>
{
    base::GameRule out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.can_be_modified_by_player = static_cast<bool>(*v);
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<std::monostate, bool, std::uint32_t, float> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<std::monostate, bool, std::uint32_t, float>> alt0{};
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<std::monostate, bool, std::uint32_t, float>> alt0{};
                {
                    auto v = stream.read<bool>();
                    if (!v) return std::unexpected(v.error());
                    alt0 = static_cast<bool>(*v);
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<std::monostate, bool, std::uint32_t, float>> alt0{};
                {
                    auto v = stream.readVarInt<std::uint32_t>();
                    if (!v) return std::unexpected(v.error());
                    alt0 = static_cast<std::uint32_t>(*v);
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<std::monostate, bool, std::uint32_t, float>> alt0{};
                {
                    auto v = stream.read<float>();
                    if (!v) return std::unexpected(v.error());
                    alt0 = static_cast<float>(*v);
                }
                var0.emplace<3>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.value = var0;
    }
    return out;
}

void Serializer<v844::GameRule>::serialize(BinaryWriter &stream, const v844::GameRule &value)
{
    stream.write(value.name);
    stream.write<bool>(value.can_be_modified_by_player);
    stream.writeVarInt<std::uint32_t>((value.value).index());
    switch ((value.value).index()) {
        case 0: {
            break;
        }
        case 1: {
            stream.write<bool>(std::get<1>(value.value));
            break;
        }
        case 2: {
            stream.write<std::int32_t>(std::get<2>(value.value));
            break;
        }
        case 3: {
            stream.write<float>(std::get<3>(value.value));
            break;
        }
    }
}

auto Serializer<v844::GameRule>::deserialize(BinaryReader &stream) -> std::expected<v844::GameRule, std::error_code>
{
    v844::GameRule out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.can_be_modified_by_player = static_cast<bool>(*v);
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<std::monostate, bool, std::int32_t, float> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<std::monostate, bool, std::int32_t, float>> alt0{};
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<std::monostate, bool, std::int32_t, float>> alt0{};
                {
                    auto v = stream.read<bool>();
                    if (!v) return std::unexpected(v.error());
                    alt0 = static_cast<bool>(*v);
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<std::monostate, bool, std::int32_t, float>> alt0{};
                {
                    auto v = stream.read<std::int32_t>();
                    if (!v) return std::unexpected(v.error());
                    alt0 = static_cast<std::int32_t>(*v);
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<std::monostate, bool, std::int32_t, float>> alt0{};
                {
                    auto v = stream.read<float>();
                    if (!v) return std::unexpected(v.error());
                    alt0 = static_cast<float>(*v);
                }
                var0.emplace<3>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.value = var0;
    }
    return out;
}

void Serializer<base::GameRulesChangedPacketData>::serialize(BinaryWriter &stream, const base::GameRulesChangedPacketData &value)
{
    stream.writeVarInt<std::uint32_t>(value.rules.size());
    for (const auto &e0 : value.rules) {
        Serializer<base::GameRule>::serialize(stream, e0);
    }
}

auto Serializer<base::GameRulesChangedPacketData>::deserialize(BinaryReader &stream) -> std::expected<base::GameRulesChangedPacketData, std::error_code>
{
    base::GameRulesChangedPacketData out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.rules.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.rules.emplace_back();
            auto v = Serializer<base::GameRule>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.rules.back() = *v;
        }
    }
    return out;
}

void Serializer<v844::GameRulesChangedPacketData>::serialize(BinaryWriter &stream, const v844::GameRulesChangedPacketData &value)
{
    stream.writeVarInt<std::uint32_t>(value.rules.size());
    for (const auto &e0 : value.rules) {
        Serializer<v844::GameRule>::serialize(stream, e0);
    }
}

auto Serializer<v844::GameRulesChangedPacketData>::deserialize(BinaryReader &stream) -> std::expected<v844::GameRulesChangedPacketData, std::error_code>
{
    v844::GameRulesChangedPacketData out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.rules.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.rules.emplace_back();
            auto v = Serializer<v844::GameRule>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.rules.back() = *v;
        }
    }
    return out;
}

void Serializer<ExperimentToggle>::serialize(BinaryWriter &stream, const ExperimentToggle &value)
{
    stream.write(value.name);
    stream.write<bool>(value.enabled);
}

auto Serializer<ExperimentToggle>::deserialize(BinaryReader &stream) -> std::expected<ExperimentToggle, std::error_code>
{
    ExperimentToggle out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.enabled = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<Experiments>::serialize(BinaryWriter &stream, const Experiments &value)
{
    stream.write<std::uint32_t>(value.toggles.size());
    for (const auto &e0 : value.toggles) {
        Serializer<ExperimentToggle>::serialize(stream, e0);
    }
    stream.write<bool>(value.experiments_ever_toggled);
}

auto Serializer<Experiments>::deserialize(BinaryReader &stream) -> std::expected<Experiments, std::error_code>
{
    Experiments out;
    {
        auto len0 = stream.read<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.toggles.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.toggles.emplace_back();
            auto v = Serializer<ExperimentToggle>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.toggles.back() = *v;
        }
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.experiments_ever_toggled = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<base::SyncedPlayerMovementSettings>::serialize(BinaryWriter &stream, const base::SyncedPlayerMovementSettings &value)
{
    stream.writeVarInt<std::int32_t>(value.authority_mode);
    stream.writeVarInt<std::int32_t>(value.rewind_history_size);
    stream.write<bool>(value.server_auth_block_breaking);
}

auto Serializer<base::SyncedPlayerMovementSettings>::deserialize(BinaryReader &stream) -> std::expected<base::SyncedPlayerMovementSettings, std::error_code>
{
    base::SyncedPlayerMovementSettings out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.authority_mode = static_cast<ServerAuthMovementMode>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.rewind_history_size = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.server_auth_block_breaking = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v818::SyncedPlayerMovementSettings>::serialize(BinaryWriter &stream, const v818::SyncedPlayerMovementSettings &value)
{
    stream.writeVarInt<std::int32_t>(value.rewind_history_size);
    stream.write<bool>(value.server_auth_block_breaking);
}

auto Serializer<v818::SyncedPlayerMovementSettings>::deserialize(BinaryReader &stream) -> std::expected<v818::SyncedPlayerMovementSettings, std::error_code>
{
    v818::SyncedPlayerMovementSettings out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.rewind_history_size = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.server_auth_block_breaking = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<BlockEntry>::serialize(BinaryWriter &stream, const BlockEntry &value)
{
    stream.write(value.name);
    Serializer<CompoundTag>::serialize(stream, value.properties);
}

auto Serializer<BlockEntry>::deserialize(BinaryReader &stream) -> std::expected<BlockEntry, std::error_code>
{
    BlockEntry out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = Serializer<CompoundTag>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.properties = *v;
    }
    return out;
}

void Serializer<v2168::ServerBlockProperty>::serialize(BinaryWriter &stream, const v2168::ServerBlockProperty &value)
{
    stream.write(value.name);
    Serializer<CompoundTag>::serialize(stream, value.tag);
}

auto Serializer<v2168::ServerBlockProperty>::deserialize(BinaryReader &stream) -> std::expected<v2168::ServerBlockProperty, std::error_code>
{
    v2168::ServerBlockProperty out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = Serializer<CompoundTag>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.tag = *v;
    }
    return out;
}

void Serializer<legacy::base::GameRule>::serialize(BinaryWriter &stream, const legacy::base::GameRule &value)
{
    stream.write(value.name);
    stream.write<bool>(value.can_be_modified_by_player);
    stream.writeVarInt<std::uint32_t>((value.value).index());
    switch ((value.value).index()) {
        case 0: {
            break;
        }
        case 1: {
            stream.write<bool>(std::get<1>(value.value));
            break;
        }
        case 2: {
            stream.writeVarInt<std::uint32_t>(std::get<2>(value.value));
            break;
        }
        case 3: {
            stream.write<float>(std::get<3>(value.value));
            break;
        }
    }
}

auto Serializer<legacy::base::GameRule>::deserialize(BinaryReader &stream) -> std::expected<legacy::base::GameRule, std::error_code>
{
    legacy::base::GameRule out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.can_be_modified_by_player = static_cast<bool>(*v);
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<std::monostate, bool, std::uint32_t, float> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<std::monostate, bool, std::uint32_t, float>> alt0{};
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<std::monostate, bool, std::uint32_t, float>> alt0{};
                {
                    auto v = stream.read<bool>();
                    if (!v) return std::unexpected(v.error());
                    alt0 = static_cast<bool>(*v);
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<std::monostate, bool, std::uint32_t, float>> alt0{};
                {
                    auto v = stream.readVarInt<std::uint32_t>();
                    if (!v) return std::unexpected(v.error());
                    alt0 = static_cast<std::uint32_t>(*v);
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<std::monostate, bool, std::uint32_t, float>> alt0{};
                {
                    auto v = stream.read<float>();
                    if (!v) return std::unexpected(v.error());
                    alt0 = static_cast<float>(*v);
                }
                var0.emplace<3>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.value = var0;
    }
    return out;
}

void Serializer<base::LevelSettings>::serialize(BinaryWriter &stream, const base::LevelSettings &value)
{
    stream.write<std::uint64_t>(value.seed);
    Serializer<SpawnSettings>::serialize(stream, value.spawn_settings);
    stream.writeVarInt<std::int32_t>(value.generator);
    stream.writeVarInt<std::int32_t>(value.game_type);
    stream.write<bool>(value.is_hardcore);
    stream.writeVarInt<std::int32_t>(value.game_difficulty);
    Serializer<base::NetworkBlockPosition>::serialize(stream, value.default_spawn);
    stream.write<bool>(value.achievements_disabled);
    stream.writeVarInt<std::int32_t>(value.editor_world_type);
    stream.write<bool>(value.is_created_in_editor);
    stream.write<bool>(value.is_exported_from_editor);
    stream.writeVarInt<std::int32_t>(value.time);
    stream.writeVarInt<std::int32_t>(value.education_edition_offer);
    stream.write<bool>(value.education_features_enabled);
    stream.write(value.education_product_id);
    stream.write<float>(value.rain_level);
    stream.write<float>(value.lightning_level);
    stream.write<bool>(value.confirmed_platform_locked_content);
    stream.write<bool>(value.multiplayer_game_intent);
    stream.write<bool>(value.lan_broadcast_intent);
    stream.writeVarInt<std::int32_t>(value.xbl_broadcast_intent);
    stream.writeVarInt<std::int32_t>(value.platform_broadcast_intent);
    stream.write<bool>(value.commands_enabled);
    stream.write<bool>(value.texture_packs_required);
    stream.writeVarInt<std::uint32_t>(value.game_rules.size());
    for (const auto &e0 : value.game_rules) {
        Serializer<legacy::base::GameRule>::serialize(stream, e0);
    }
    stream.write<std::uint32_t>(value.experiments.size());
    for (const auto &e0 : value.experiments) {
        Serializer<ExperimentToggle>::serialize(stream, e0);
    }
    stream.write<bool>(value.experiments_ever_toggled);
    stream.write<bool>(value.bonus_chest_enabled);
    stream.write<bool>(value.start_with_map_enabled);
    stream.writeVarInt<std::int32_t>(value.default_permissions);
    stream.write<std::int32_t>(value.server_chunk_tick_range);
    stream.write<bool>(value.has_locked_behavior_pack);
    stream.write<bool>(value.has_locked_resource_pack);
    stream.write<bool>(value.is_from_locked_template);
    stream.write<bool>(value.use_msa_gamertags_only);
    stream.write<bool>(value.is_from_world_template);
    stream.write<bool>(value.is_world_template_option_locked);
    stream.write<bool>(value.spawn_v1_villagers);
    stream.write<bool>(value.persona_disabled);
    stream.write<bool>(value.custom_skins_disabled);
    stream.write<bool>(value.emote_chat_muted);
    stream.write(value.base_game_version);
    stream.write<std::int32_t>(value.limited_world_width);
    stream.write<std::int32_t>(value.limited_world_depth);
    stream.write<bool>(value.nether_type);
    Serializer<EduSharedUriResource>::serialize(stream, value.edu_shared_uri_resource);
    stream.write<bool>(value.override_force_experimental_gameplay.has_value());
    if (value.override_force_experimental_gameplay.has_value()) {
        stream.write<bool>((*value.override_force_experimental_gameplay));
    }
    stream.write<std::uint8_t>(value.chat_restriction_level);
    stream.write<bool>(value.disable_player_interactions);
    stream.write(value.server_id);
    stream.write(value.world_id);
    stream.write(value.scenario_id);
}

auto Serializer<base::LevelSettings>::deserialize(BinaryReader &stream) -> std::expected<base::LevelSettings, std::error_code>
{
    base::LevelSettings out;
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.seed = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = Serializer<SpawnSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.spawn_settings = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.generator = static_cast<GeneratorType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.game_type = static_cast<GameType>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_hardcore = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.game_difficulty = static_cast<Difficulty>(*v);
    }
    {
        auto v = Serializer<base::NetworkBlockPosition>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.default_spawn = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.achievements_disabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.editor_world_type = static_cast<base::WorldType>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_created_in_editor = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_exported_from_editor = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.time = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.education_edition_offer = static_cast<EducationEditionOffer>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.education_features_enabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.education_product_id = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.rain_level = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.lightning_level = static_cast<float>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.confirmed_platform_locked_content = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.multiplayer_game_intent = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.lan_broadcast_intent = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.xbl_broadcast_intent = static_cast<GamePublishSetting>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.platform_broadcast_intent = static_cast<GamePublishSetting>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.commands_enabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.texture_packs_required = static_cast<bool>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.game_rules.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.game_rules.emplace_back();
            auto v = Serializer<legacy::base::GameRule>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.game_rules.back() = *v;
        }
    }
    {
        auto len0 = stream.read<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.experiments.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.experiments.emplace_back();
            auto v = Serializer<ExperimentToggle>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.experiments.back() = *v;
        }
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.experiments_ever_toggled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.bonus_chest_enabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.start_with_map_enabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.default_permissions = static_cast<PlayerPermissionLevel>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.server_chunk_tick_range = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_locked_behavior_pack = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_locked_resource_pack = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_from_locked_template = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.use_msa_gamertags_only = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_from_world_template = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_world_template_option_locked = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.spawn_v1_villagers = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.persona_disabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.custom_skins_disabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.emote_chat_muted = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.base_game_version = *v;
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.limited_world_width = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.limited_world_depth = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.nether_type = static_cast<NetherWorldType>(*v);
    }
    {
        auto v = Serializer<EduSharedUriResource>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.edu_shared_uri_resource = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.override_force_experimental_gameplay = std::move(staged);
        }
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.chat_restriction_level = static_cast<ChatRestrictionLevel>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.disable_player_interactions = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.server_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.world_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.scenario_id = *v;
    }
    return out;
}

void Serializer<v800::LevelSettings>::serialize(BinaryWriter &stream, const v800::LevelSettings &value)
{
    stream.write<std::uint64_t>(value.seed);
    Serializer<SpawnSettings>::serialize(stream, value.spawn_settings);
    stream.writeVarInt<std::int32_t>(value.generator);
    stream.writeVarInt<std::int32_t>(value.game_type);
    stream.write<bool>(value.is_hardcore);
    stream.writeVarInt<std::int32_t>(value.game_difficulty);
    Serializer<base::NetworkBlockPosition>::serialize(stream, value.default_spawn);
    stream.write<bool>(value.achievements_disabled);
    stream.writeVarInt<std::int32_t>(value.editor_world_type);
    stream.write<bool>(value.is_created_in_editor);
    stream.write<bool>(value.is_exported_from_editor);
    stream.writeVarInt<std::int32_t>(value.time);
    stream.writeVarInt<std::int32_t>(value.education_edition_offer);
    stream.write<bool>(value.education_features_enabled);
    stream.write(value.education_product_id);
    stream.write<float>(value.rain_level);
    stream.write<float>(value.lightning_level);
    stream.write<bool>(value.confirmed_platform_locked_content);
    stream.write<bool>(value.multiplayer_game_intent);
    stream.write<bool>(value.lan_broadcast_intent);
    stream.writeVarInt<std::int32_t>(value.xbl_broadcast_intent);
    stream.writeVarInt<std::int32_t>(value.platform_broadcast_intent);
    stream.write<bool>(value.commands_enabled);
    stream.write<bool>(value.texture_packs_required);
    stream.writeVarInt<std::uint32_t>(value.game_rules.size());
    for (const auto &e0 : value.game_rules) {
        Serializer<legacy::base::GameRule>::serialize(stream, e0);
    }
    stream.write<std::uint32_t>(value.experiments.size());
    for (const auto &e0 : value.experiments) {
        Serializer<ExperimentToggle>::serialize(stream, e0);
    }
    stream.write<bool>(value.experiments_ever_toggled);
    stream.write<bool>(value.bonus_chest_enabled);
    stream.write<bool>(value.start_with_map_enabled);
    stream.writeVarInt<std::int32_t>(value.default_permissions);
    stream.write<std::int32_t>(value.server_chunk_tick_range);
    stream.write<bool>(value.has_locked_behavior_pack);
    stream.write<bool>(value.has_locked_resource_pack);
    stream.write<bool>(value.is_from_locked_template);
    stream.write<bool>(value.use_msa_gamertags_only);
    stream.write<bool>(value.is_from_world_template);
    stream.write<bool>(value.is_world_template_option_locked);
    stream.write<bool>(value.spawn_v1_villagers);
    stream.write<bool>(value.persona_disabled);
    stream.write<bool>(value.custom_skins_disabled);
    stream.write<bool>(value.emote_chat_muted);
    stream.write(value.base_game_version);
    stream.write<std::int32_t>(value.limited_world_width);
    stream.write<std::int32_t>(value.limited_world_depth);
    stream.write<bool>(value.nether_type);
    Serializer<EduSharedUriResource>::serialize(stream, value.edu_shared_uri_resource);
    stream.write<bool>(value.override_force_experimental_gameplay.has_value());
    if (value.override_force_experimental_gameplay.has_value()) {
        stream.write<bool>((*value.override_force_experimental_gameplay));
    }
    stream.write<std::uint8_t>(value.chat_restriction_level);
    stream.write<bool>(value.disable_player_interactions);
    stream.write(value.server_id);
    stream.write(value.world_id);
    stream.write(value.scenario_id);
}

auto Serializer<v800::LevelSettings>::deserialize(BinaryReader &stream) -> std::expected<v800::LevelSettings, std::error_code>
{
    v800::LevelSettings out;
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.seed = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = Serializer<SpawnSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.spawn_settings = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.generator = static_cast<GeneratorType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.game_type = static_cast<GameType>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_hardcore = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.game_difficulty = static_cast<Difficulty>(*v);
    }
    {
        auto v = Serializer<base::NetworkBlockPosition>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.default_spawn = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.achievements_disabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.editor_world_type = static_cast<v800::WorldType>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_created_in_editor = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_exported_from_editor = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.time = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.education_edition_offer = static_cast<EducationEditionOffer>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.education_features_enabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.education_product_id = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.rain_level = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.lightning_level = static_cast<float>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.confirmed_platform_locked_content = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.multiplayer_game_intent = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.lan_broadcast_intent = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.xbl_broadcast_intent = static_cast<GamePublishSetting>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.platform_broadcast_intent = static_cast<GamePublishSetting>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.commands_enabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.texture_packs_required = static_cast<bool>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.game_rules.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.game_rules.emplace_back();
            auto v = Serializer<legacy::base::GameRule>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.game_rules.back() = *v;
        }
    }
    {
        auto len0 = stream.read<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.experiments.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.experiments.emplace_back();
            auto v = Serializer<ExperimentToggle>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.experiments.back() = *v;
        }
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.experiments_ever_toggled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.bonus_chest_enabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.start_with_map_enabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.default_permissions = static_cast<PlayerPermissionLevel>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.server_chunk_tick_range = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_locked_behavior_pack = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_locked_resource_pack = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_from_locked_template = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.use_msa_gamertags_only = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_from_world_template = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_world_template_option_locked = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.spawn_v1_villagers = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.persona_disabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.custom_skins_disabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.emote_chat_muted = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.base_game_version = *v;
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.limited_world_width = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.limited_world_depth = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.nether_type = static_cast<NetherWorldType>(*v);
    }
    {
        auto v = Serializer<EduSharedUriResource>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.edu_shared_uri_resource = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.override_force_experimental_gameplay = std::move(staged);
        }
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.chat_restriction_level = static_cast<ChatRestrictionLevel>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.disable_player_interactions = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.server_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.world_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.scenario_id = *v;
    }
    return out;
}

void Serializer<v818::LevelSettings>::serialize(BinaryWriter &stream, const v818::LevelSettings &value)
{
    stream.write<std::uint64_t>(value.seed);
    Serializer<SpawnSettings>::serialize(stream, value.spawn_settings);
    stream.writeVarInt<std::int32_t>(value.generator);
    stream.writeVarInt<std::int32_t>(value.game_type);
    stream.write<bool>(value.is_hardcore);
    stream.writeVarInt<std::int32_t>(value.game_difficulty);
    Serializer<base::NetworkBlockPosition>::serialize(stream, value.default_spawn);
    stream.write<bool>(value.achievements_disabled);
    stream.writeVarInt<std::int32_t>(value.editor_world_type);
    stream.write<bool>(value.is_created_in_editor);
    stream.write<bool>(value.is_exported_from_editor);
    stream.writeVarInt<std::int32_t>(value.time);
    stream.writeVarInt<std::int32_t>(value.education_edition_offer);
    stream.write<bool>(value.education_features_enabled);
    stream.write(value.education_product_id);
    stream.write<float>(value.rain_level);
    stream.write<float>(value.lightning_level);
    stream.write<bool>(value.confirmed_platform_locked_content);
    stream.write<bool>(value.multiplayer_game_intent);
    stream.write<bool>(value.lan_broadcast_intent);
    stream.writeVarInt<std::int32_t>(value.xbl_broadcast_intent);
    stream.writeVarInt<std::int32_t>(value.platform_broadcast_intent);
    stream.write<bool>(value.commands_enabled);
    stream.write<bool>(value.texture_packs_required);
    stream.writeVarInt<std::uint32_t>(value.game_rules.size());
    for (const auto &e0 : value.game_rules) {
        Serializer<legacy::base::GameRule>::serialize(stream, e0);
    }
    stream.write<std::uint32_t>(value.experiments.size());
    for (const auto &e0 : value.experiments) {
        Serializer<ExperimentToggle>::serialize(stream, e0);
    }
    stream.write<bool>(value.experiments_ever_toggled);
    stream.write<bool>(value.bonus_chest_enabled);
    stream.write<bool>(value.start_with_map_enabled);
    stream.writeVarInt<std::int32_t>(value.default_permissions);
    stream.write<std::int32_t>(value.server_chunk_tick_range);
    stream.write<bool>(value.has_locked_behavior_pack);
    stream.write<bool>(value.has_locked_resource_pack);
    stream.write<bool>(value.is_from_locked_template);
    stream.write<bool>(value.use_msa_gamertags_only);
    stream.write<bool>(value.is_from_world_template);
    stream.write<bool>(value.is_world_template_option_locked);
    stream.write<bool>(value.spawn_v1_villagers);
    stream.write<bool>(value.persona_disabled);
    stream.write<bool>(value.custom_skins_disabled);
    stream.write<bool>(value.emote_chat_muted);
    stream.write(value.base_game_version);
    stream.write<std::int32_t>(value.limited_world_width);
    stream.write<std::int32_t>(value.limited_world_depth);
    stream.write<bool>(value.nether_type);
    Serializer<EduSharedUriResource>::serialize(stream, value.edu_shared_uri_resource);
    stream.write<bool>(value.override_force_experimental_gameplay.has_value());
    if (value.override_force_experimental_gameplay.has_value()) {
        stream.write<bool>((*value.override_force_experimental_gameplay));
    }
    stream.write<std::uint8_t>(value.chat_restriction_level);
    stream.write<bool>(value.disable_player_interactions);
    stream.write(value.server_id);
    stream.write(value.world_id);
    stream.write(value.scenario_id);
    stream.write(value.owner_id);
}

auto Serializer<v818::LevelSettings>::deserialize(BinaryReader &stream) -> std::expected<v818::LevelSettings, std::error_code>
{
    v818::LevelSettings out;
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.seed = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = Serializer<SpawnSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.spawn_settings = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.generator = static_cast<GeneratorType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.game_type = static_cast<GameType>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_hardcore = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.game_difficulty = static_cast<Difficulty>(*v);
    }
    {
        auto v = Serializer<base::NetworkBlockPosition>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.default_spawn = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.achievements_disabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.editor_world_type = static_cast<v800::WorldType>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_created_in_editor = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_exported_from_editor = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.time = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.education_edition_offer = static_cast<EducationEditionOffer>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.education_features_enabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.education_product_id = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.rain_level = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.lightning_level = static_cast<float>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.confirmed_platform_locked_content = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.multiplayer_game_intent = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.lan_broadcast_intent = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.xbl_broadcast_intent = static_cast<GamePublishSetting>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.platform_broadcast_intent = static_cast<GamePublishSetting>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.commands_enabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.texture_packs_required = static_cast<bool>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.game_rules.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.game_rules.emplace_back();
            auto v = Serializer<legacy::base::GameRule>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.game_rules.back() = *v;
        }
    }
    {
        auto len0 = stream.read<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.experiments.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.experiments.emplace_back();
            auto v = Serializer<ExperimentToggle>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.experiments.back() = *v;
        }
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.experiments_ever_toggled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.bonus_chest_enabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.start_with_map_enabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.default_permissions = static_cast<PlayerPermissionLevel>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.server_chunk_tick_range = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_locked_behavior_pack = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_locked_resource_pack = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_from_locked_template = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.use_msa_gamertags_only = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_from_world_template = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_world_template_option_locked = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.spawn_v1_villagers = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.persona_disabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.custom_skins_disabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.emote_chat_muted = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.base_game_version = *v;
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.limited_world_width = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.limited_world_depth = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.nether_type = static_cast<NetherWorldType>(*v);
    }
    {
        auto v = Serializer<EduSharedUriResource>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.edu_shared_uri_resource = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.override_force_experimental_gameplay = std::move(staged);
        }
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.chat_restriction_level = static_cast<ChatRestrictionLevel>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.disable_player_interactions = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.server_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.world_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.scenario_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.owner_id = *v;
    }
    return out;
}

void Serializer<v844::LevelSettings>::serialize(BinaryWriter &stream, const v844::LevelSettings &value)
{
    stream.write<std::uint64_t>(value.seed);
    Serializer<SpawnSettings>::serialize(stream, value.spawn_settings);
    stream.writeVarInt<std::int32_t>(value.generator);
    stream.writeVarInt<std::int32_t>(value.game_type);
    stream.write<bool>(value.is_hardcore);
    stream.writeVarInt<std::int32_t>(value.game_difficulty);
    Serializer<base::NetworkBlockPosition>::serialize(stream, value.default_spawn);
    stream.write<bool>(value.achievements_disabled);
    stream.writeVarInt<std::int32_t>(value.editor_world_type);
    stream.write<bool>(value.is_created_in_editor);
    stream.write<bool>(value.is_exported_from_editor);
    stream.writeVarInt<std::int32_t>(value.time);
    stream.writeVarInt<std::int32_t>(value.education_edition_offer);
    stream.write<bool>(value.education_features_enabled);
    stream.write(value.education_product_id);
    stream.write<float>(value.rain_level);
    stream.write<float>(value.lightning_level);
    stream.write<bool>(value.confirmed_platform_locked_content);
    stream.write<bool>(value.multiplayer_game_intent);
    stream.write<bool>(value.lan_broadcast_intent);
    stream.writeVarInt<std::int32_t>(value.xbl_broadcast_intent);
    stream.writeVarInt<std::int32_t>(value.platform_broadcast_intent);
    stream.write<bool>(value.commands_enabled);
    stream.write<bool>(value.texture_packs_required);
    stream.writeVarInt<std::uint32_t>(value.game_rules.size());
    for (const auto &e0 : value.game_rules) {
        Serializer<legacy::base::GameRule>::serialize(stream, e0);
    }
    stream.write<std::uint32_t>(value.experiments.size());
    for (const auto &e0 : value.experiments) {
        Serializer<ExperimentToggle>::serialize(stream, e0);
    }
    stream.write<bool>(value.experiments_ever_toggled);
    stream.write<bool>(value.bonus_chest_enabled);
    stream.write<bool>(value.start_with_map_enabled);
    stream.writeVarInt<std::int32_t>(value.default_permissions);
    stream.write<std::int32_t>(value.server_chunk_tick_range);
    stream.write<bool>(value.has_locked_behavior_pack);
    stream.write<bool>(value.has_locked_resource_pack);
    stream.write<bool>(value.is_from_locked_template);
    stream.write<bool>(value.use_msa_gamertags_only);
    stream.write<bool>(value.is_from_world_template);
    stream.write<bool>(value.is_world_template_option_locked);
    stream.write<bool>(value.spawn_v1_villagers);
    stream.write<bool>(value.persona_disabled);
    stream.write<bool>(value.custom_skins_disabled);
    stream.write<bool>(value.emote_chat_muted);
    stream.write(value.base_game_version);
    stream.write<std::int32_t>(value.limited_world_width);
    stream.write<std::int32_t>(value.limited_world_depth);
    stream.write<bool>(value.nether_type);
    Serializer<EduSharedUriResource>::serialize(stream, value.edu_shared_uri_resource);
    stream.write<bool>(value.override_force_experimental_gameplay.has_value());
    if (value.override_force_experimental_gameplay.has_value()) {
        stream.write<bool>((*value.override_force_experimental_gameplay));
    }
    stream.write<std::uint8_t>(value.chat_restriction_level);
    stream.write<bool>(value.disable_player_interactions);
    stream.write(value.server_id);
    stream.write(value.world_id);
    stream.write(value.scenario_id);
    stream.write(value.owner_id);
}

auto Serializer<v844::LevelSettings>::deserialize(BinaryReader &stream) -> std::expected<v844::LevelSettings, std::error_code>
{
    v844::LevelSettings out;
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.seed = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = Serializer<SpawnSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.spawn_settings = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.generator = static_cast<GeneratorType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.game_type = static_cast<GameType>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_hardcore = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.game_difficulty = static_cast<Difficulty>(*v);
    }
    {
        auto v = Serializer<base::NetworkBlockPosition>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.default_spawn = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.achievements_disabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.editor_world_type = static_cast<v800::WorldType>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_created_in_editor = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_exported_from_editor = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.time = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.education_edition_offer = static_cast<EducationEditionOffer>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.education_features_enabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.education_product_id = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.rain_level = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.lightning_level = static_cast<float>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.confirmed_platform_locked_content = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.multiplayer_game_intent = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.lan_broadcast_intent = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.xbl_broadcast_intent = static_cast<GamePublishSetting>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.platform_broadcast_intent = static_cast<GamePublishSetting>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.commands_enabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.texture_packs_required = static_cast<bool>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.game_rules.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.game_rules.emplace_back();
            auto v = Serializer<legacy::base::GameRule>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.game_rules.back() = *v;
        }
    }
    {
        auto len0 = stream.read<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.experiments.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.experiments.emplace_back();
            auto v = Serializer<ExperimentToggle>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.experiments.back() = *v;
        }
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.experiments_ever_toggled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.bonus_chest_enabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.start_with_map_enabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.default_permissions = static_cast<PlayerPermissionLevel>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.server_chunk_tick_range = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_locked_behavior_pack = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_locked_resource_pack = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_from_locked_template = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.use_msa_gamertags_only = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_from_world_template = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_world_template_option_locked = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.spawn_v1_villagers = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.persona_disabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.custom_skins_disabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.emote_chat_muted = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.base_game_version = *v;
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.limited_world_width = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.limited_world_depth = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.nether_type = static_cast<NetherWorldType>(*v);
    }
    {
        auto v = Serializer<EduSharedUriResource>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.edu_shared_uri_resource = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.override_force_experimental_gameplay = std::move(staged);
        }
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.chat_restriction_level = static_cast<ChatRestrictionLevel>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.disable_player_interactions = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.server_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.world_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.scenario_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.owner_id = *v;
    }
    return out;
}

void Serializer<v924::LevelSettings>::serialize(BinaryWriter &stream, const v924::LevelSettings &value)
{
    stream.write<std::uint64_t>(value.seed);
    Serializer<SpawnSettings>::serialize(stream, value.spawn_settings);
    stream.writeVarInt<std::int32_t>(value.generator);
    stream.writeVarInt<std::int32_t>(value.game_type);
    stream.write<bool>(value.is_hardcore);
    stream.writeVarInt<std::int32_t>(value.game_difficulty);
    Serializer<base::NetworkBlockPosition>::serialize(stream, value.default_spawn);
    stream.write<bool>(value.achievements_disabled);
    stream.writeVarInt<std::int32_t>(value.editor_world_type);
    stream.write<bool>(value.is_created_in_editor);
    stream.write<bool>(value.is_exported_from_editor);
    stream.writeVarInt<std::int32_t>(value.time);
    stream.writeVarInt<std::int32_t>(value.education_edition_offer);
    stream.write<bool>(value.education_features_enabled);
    stream.write(value.education_product_id);
    stream.write<float>(value.rain_level);
    stream.write<float>(value.lightning_level);
    stream.write<bool>(value.confirmed_platform_locked_content);
    stream.write<bool>(value.multiplayer_game_intent);
    stream.write<bool>(value.lan_broadcast_intent);
    stream.writeVarInt<std::int32_t>(value.xbl_broadcast_intent);
    stream.writeVarInt<std::int32_t>(value.platform_broadcast_intent);
    stream.write<bool>(value.commands_enabled);
    stream.write<bool>(value.texture_packs_required);
    stream.writeVarInt<std::uint32_t>(value.game_rules.size());
    for (const auto &e0 : value.game_rules) {
        Serializer<legacy::base::GameRule>::serialize(stream, e0);
    }
    stream.write<std::uint32_t>(value.experiments.size());
    for (const auto &e0 : value.experiments) {
        Serializer<ExperimentToggle>::serialize(stream, e0);
    }
    stream.write<bool>(value.experiments_ever_toggled);
    stream.write<bool>(value.bonus_chest_enabled);
    stream.write<bool>(value.start_with_map_enabled);
    stream.writeVarInt<std::int32_t>(value.default_permissions);
    stream.write<std::int32_t>(value.server_chunk_tick_range);
    stream.write<bool>(value.has_locked_behavior_pack);
    stream.write<bool>(value.has_locked_resource_pack);
    stream.write<bool>(value.is_from_locked_template);
    stream.write<bool>(value.use_msa_gamertags_only);
    stream.write<bool>(value.is_from_world_template);
    stream.write<bool>(value.is_world_template_option_locked);
    stream.write<bool>(value.spawn_v1_villagers);
    stream.write<bool>(value.persona_disabled);
    stream.write<bool>(value.custom_skins_disabled);
    stream.write<bool>(value.emote_chat_muted);
    stream.write(value.base_game_version);
    stream.write<std::int32_t>(value.limited_world_width);
    stream.write<std::int32_t>(value.limited_world_depth);
    stream.write<bool>(value.nether_type);
    Serializer<EduSharedUriResource>::serialize(stream, value.edu_shared_uri_resource);
    stream.write<bool>(value.override_force_experimental_gameplay.has_value());
    if (value.override_force_experimental_gameplay.has_value()) {
        stream.write<bool>((*value.override_force_experimental_gameplay));
    }
    stream.write<std::uint8_t>(value.chat_restriction_level);
    stream.write<bool>(value.disable_player_interactions);
}

auto Serializer<v924::LevelSettings>::deserialize(BinaryReader &stream) -> std::expected<v924::LevelSettings, std::error_code>
{
    v924::LevelSettings out;
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.seed = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = Serializer<SpawnSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.spawn_settings = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.generator = static_cast<GeneratorType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.game_type = static_cast<GameType>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_hardcore = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.game_difficulty = static_cast<Difficulty>(*v);
    }
    {
        auto v = Serializer<base::NetworkBlockPosition>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.default_spawn = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.achievements_disabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.editor_world_type = static_cast<v800::WorldType>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_created_in_editor = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_exported_from_editor = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.time = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.education_edition_offer = static_cast<EducationEditionOffer>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.education_features_enabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.education_product_id = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.rain_level = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.lightning_level = static_cast<float>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.confirmed_platform_locked_content = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.multiplayer_game_intent = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.lan_broadcast_intent = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.xbl_broadcast_intent = static_cast<GamePublishSetting>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.platform_broadcast_intent = static_cast<GamePublishSetting>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.commands_enabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.texture_packs_required = static_cast<bool>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.game_rules.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.game_rules.emplace_back();
            auto v = Serializer<legacy::base::GameRule>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.game_rules.back() = *v;
        }
    }
    {
        auto len0 = stream.read<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.experiments.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.experiments.emplace_back();
            auto v = Serializer<ExperimentToggle>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.experiments.back() = *v;
        }
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.experiments_ever_toggled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.bonus_chest_enabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.start_with_map_enabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.default_permissions = static_cast<PlayerPermissionLevel>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.server_chunk_tick_range = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_locked_behavior_pack = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_locked_resource_pack = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_from_locked_template = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.use_msa_gamertags_only = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_from_world_template = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_world_template_option_locked = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.spawn_v1_villagers = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.persona_disabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.custom_skins_disabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.emote_chat_muted = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.base_game_version = *v;
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.limited_world_width = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.limited_world_depth = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.nether_type = static_cast<NetherWorldType>(*v);
    }
    {
        auto v = Serializer<EduSharedUriResource>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.edu_shared_uri_resource = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.override_force_experimental_gameplay = std::move(staged);
        }
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.chat_restriction_level = static_cast<ChatRestrictionLevel>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.disable_player_interactions = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v944::LevelSettings>::serialize(BinaryWriter &stream, const v944::LevelSettings &value)
{
    stream.write<std::uint64_t>(value.seed);
    Serializer<SpawnSettings>::serialize(stream, value.spawn_settings);
    stream.writeVarInt<std::int32_t>(value.generator);
    stream.writeVarInt<std::int32_t>(value.game_type);
    stream.write<bool>(value.is_hardcore);
    stream.writeVarInt<std::int32_t>(value.game_difficulty);
    Serializer<BlockPos>::serialize(stream, value.default_spawn);
    stream.write<bool>(value.achievements_disabled);
    stream.writeVarInt<std::int32_t>(value.editor_world_type);
    stream.write<bool>(value.is_created_in_editor);
    stream.write<bool>(value.is_exported_from_editor);
    stream.writeVarInt<std::int32_t>(value.time);
    stream.writeVarInt<std::int32_t>(value.education_edition_offer);
    stream.write<bool>(value.education_features_enabled);
    stream.write(value.education_product_id);
    stream.write<float>(value.rain_level);
    stream.write<float>(value.lightning_level);
    stream.write<bool>(value.confirmed_platform_locked_content);
    stream.write<bool>(value.multiplayer_game_intent);
    stream.write<bool>(value.lan_broadcast_intent);
    stream.writeVarInt<std::int32_t>(value.xbl_broadcast_intent);
    stream.writeVarInt<std::int32_t>(value.platform_broadcast_intent);
    stream.write<bool>(value.commands_enabled);
    stream.write<bool>(value.texture_packs_required);
    stream.writeVarInt<std::uint32_t>(value.game_rules.size());
    for (const auto &e0 : value.game_rules) {
        Serializer<legacy::base::GameRule>::serialize(stream, e0);
    }
    stream.write<std::uint32_t>(value.experiments.size());
    for (const auto &e0 : value.experiments) {
        Serializer<ExperimentToggle>::serialize(stream, e0);
    }
    stream.write<bool>(value.experiments_ever_toggled);
    stream.write<bool>(value.bonus_chest_enabled);
    stream.write<bool>(value.start_with_map_enabled);
    stream.writeVarInt<std::int32_t>(value.default_permissions);
    stream.write<std::int32_t>(value.server_chunk_tick_range);
    stream.write<bool>(value.has_locked_behavior_pack);
    stream.write<bool>(value.has_locked_resource_pack);
    stream.write<bool>(value.is_from_locked_template);
    stream.write<bool>(value.use_msa_gamertags_only);
    stream.write<bool>(value.is_from_world_template);
    stream.write<bool>(value.is_world_template_option_locked);
    stream.write<bool>(value.spawn_v1_villagers);
    stream.write<bool>(value.persona_disabled);
    stream.write<bool>(value.custom_skins_disabled);
    stream.write<bool>(value.emote_chat_muted);
    stream.write(value.base_game_version);
    stream.write<std::int32_t>(value.limited_world_width);
    stream.write<std::int32_t>(value.limited_world_depth);
    stream.write<bool>(value.nether_type);
    Serializer<EduSharedUriResource>::serialize(stream, value.edu_shared_uri_resource);
    stream.write<bool>(value.override_force_experimental_gameplay.has_value());
    if (value.override_force_experimental_gameplay.has_value()) {
        stream.write<bool>((*value.override_force_experimental_gameplay));
    }
    stream.write<std::uint8_t>(value.chat_restriction_level);
    stream.write<bool>(value.disable_player_interactions);
}

auto Serializer<v944::LevelSettings>::deserialize(BinaryReader &stream) -> std::expected<v944::LevelSettings, std::error_code>
{
    v944::LevelSettings out;
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.seed = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = Serializer<SpawnSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.spawn_settings = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.generator = static_cast<GeneratorType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.game_type = static_cast<GameType>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_hardcore = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.game_difficulty = static_cast<Difficulty>(*v);
    }
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.default_spawn = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.achievements_disabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.editor_world_type = static_cast<v800::WorldType>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_created_in_editor = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_exported_from_editor = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.time = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.education_edition_offer = static_cast<EducationEditionOffer>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.education_features_enabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.education_product_id = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.rain_level = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.lightning_level = static_cast<float>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.confirmed_platform_locked_content = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.multiplayer_game_intent = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.lan_broadcast_intent = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.xbl_broadcast_intent = static_cast<GamePublishSetting>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.platform_broadcast_intent = static_cast<GamePublishSetting>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.commands_enabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.texture_packs_required = static_cast<bool>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.game_rules.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.game_rules.emplace_back();
            auto v = Serializer<legacy::base::GameRule>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.game_rules.back() = *v;
        }
    }
    {
        auto len0 = stream.read<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.experiments.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.experiments.emplace_back();
            auto v = Serializer<ExperimentToggle>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.experiments.back() = *v;
        }
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.experiments_ever_toggled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.bonus_chest_enabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.start_with_map_enabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.default_permissions = static_cast<PlayerPermissionLevel>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.server_chunk_tick_range = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_locked_behavior_pack = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_locked_resource_pack = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_from_locked_template = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.use_msa_gamertags_only = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_from_world_template = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_world_template_option_locked = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.spawn_v1_villagers = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.persona_disabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.custom_skins_disabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.emote_chat_muted = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.base_game_version = *v;
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.limited_world_width = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.limited_world_depth = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.nether_type = static_cast<NetherWorldType>(*v);
    }
    {
        auto v = Serializer<EduSharedUriResource>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.edu_shared_uri_resource = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.override_force_experimental_gameplay = std::move(staged);
        }
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.chat_restriction_level = static_cast<ChatRestrictionLevel>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.disable_player_interactions = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v1001::LevelSettings>::serialize(BinaryWriter &stream, const v1001::LevelSettings &value)
{
    stream.write<std::uint64_t>(value.seed);
    Serializer<SpawnSettings>::serialize(stream, value.spawn_settings);
    stream.writeVarInt<std::int32_t>(value.generator);
    stream.writeVarInt<std::int32_t>(value.game_type);
    stream.write<bool>(value.is_hardcore);
    stream.writeVarInt<std::int32_t>(value.game_difficulty);
    Serializer<BlockPos>::serialize(stream, value.default_spawn);
    stream.write<bool>(value.achievements_disabled);
    stream.writeVarInt<std::int32_t>(value.editor_world_type);
    stream.write<bool>(value.is_created_in_editor);
    stream.write<bool>(value.is_exported_from_editor);
    stream.writeVarInt<std::int32_t>(value.time);
    stream.writeVarInt<std::int32_t>(value.education_edition_offer);
    stream.write<bool>(value.education_features_enabled);
    stream.write(value.education_product_id);
    stream.write<float>(value.rain_level);
    stream.write<float>(value.lightning_level);
    stream.write<bool>(value.confirmed_platform_locked_content);
    stream.write<bool>(value.multiplayer_game_intent);
    stream.write<bool>(value.lan_broadcast_intent);
    stream.writeVarInt<std::int32_t>(value.xbl_broadcast_intent);
    stream.writeVarInt<std::int32_t>(value.platform_broadcast_intent);
    stream.write<bool>(value.commands_enabled);
    stream.write<bool>(value.texture_packs_required);
    stream.writeVarInt<std::uint32_t>(value.game_rules.size());
    for (const auto &e0 : value.game_rules) {
        Serializer<legacy::base::GameRule>::serialize(stream, e0);
    }
    stream.write<std::uint32_t>(value.experiments.size());
    for (const auto &e0 : value.experiments) {
        Serializer<ExperimentToggle>::serialize(stream, e0);
    }
    stream.write<bool>(value.experiments_ever_toggled);
    stream.write<bool>(value.bonus_chest_enabled);
    stream.write<bool>(value.start_with_map_enabled);
    stream.writeVarInt<std::int32_t>(value.default_permissions);
    stream.write<std::int32_t>(value.server_chunk_tick_range);
    stream.write<bool>(value.has_locked_behavior_pack);
    stream.write<bool>(value.has_locked_resource_pack);
    stream.write<bool>(value.is_from_locked_template);
    stream.write<bool>(value.use_msa_gamertags_only);
    stream.write<bool>(value.is_from_world_template);
    stream.write<bool>(value.is_world_template_option_locked);
    stream.write<bool>(value.spawn_v1_villagers);
    stream.write<bool>(value.persona_disabled);
    stream.write<bool>(value.custom_skins_disabled);
    stream.write<bool>(value.emote_chat_muted);
    stream.write(value.base_game_version);
    stream.write<std::int32_t>(value.limited_world_width);
    stream.write<std::int32_t>(value.limited_world_depth);
    stream.write<bool>(value.nether_type);
    Serializer<EduSharedUriResource>::serialize(stream, value.edu_shared_uri_resource);
    stream.write<bool>(value.override_force_experimental_gameplay.has_value());
    if (value.override_force_experimental_gameplay.has_value()) {
        stream.write<bool>((*value.override_force_experimental_gameplay));
    }
    stream.write<std::uint8_t>(value.chat_restriction_level);
    stream.write<bool>(value.disable_player_interactions);
    stream.writeVarInt<std::int32_t>(value.server_editor_connection_policy);
    stream.write<bool>(value.allow_anonymous_block_drops_in_editor_worlds);
}

auto Serializer<v1001::LevelSettings>::deserialize(BinaryReader &stream) -> std::expected<v1001::LevelSettings, std::error_code>
{
    v1001::LevelSettings out;
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.seed = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = Serializer<SpawnSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.spawn_settings = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.generator = static_cast<GeneratorType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.game_type = static_cast<GameType>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_hardcore = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.game_difficulty = static_cast<Difficulty>(*v);
    }
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.default_spawn = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.achievements_disabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.editor_world_type = static_cast<v800::WorldType>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_created_in_editor = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_exported_from_editor = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.time = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.education_edition_offer = static_cast<EducationEditionOffer>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.education_features_enabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.education_product_id = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.rain_level = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.lightning_level = static_cast<float>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.confirmed_platform_locked_content = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.multiplayer_game_intent = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.lan_broadcast_intent = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.xbl_broadcast_intent = static_cast<GamePublishSetting>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.platform_broadcast_intent = static_cast<GamePublishSetting>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.commands_enabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.texture_packs_required = static_cast<bool>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.game_rules.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.game_rules.emplace_back();
            auto v = Serializer<legacy::base::GameRule>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.game_rules.back() = *v;
        }
    }
    {
        auto len0 = stream.read<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.experiments.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.experiments.emplace_back();
            auto v = Serializer<ExperimentToggle>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.experiments.back() = *v;
        }
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.experiments_ever_toggled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.bonus_chest_enabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.start_with_map_enabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.default_permissions = static_cast<PlayerPermissionLevel>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.server_chunk_tick_range = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_locked_behavior_pack = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_locked_resource_pack = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_from_locked_template = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.use_msa_gamertags_only = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_from_world_template = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_world_template_option_locked = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.spawn_v1_villagers = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.persona_disabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.custom_skins_disabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.emote_chat_muted = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.base_game_version = *v;
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.limited_world_width = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.limited_world_depth = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.nether_type = static_cast<NetherWorldType>(*v);
    }
    {
        auto v = Serializer<EduSharedUriResource>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.edu_shared_uri_resource = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.override_force_experimental_gameplay = std::move(staged);
        }
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.chat_restriction_level = static_cast<ChatRestrictionLevel>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.disable_player_interactions = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.server_editor_connection_policy = static_cast<ServerEditorConnectionPolicy>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.allow_anonymous_block_drops_in_editor_worlds = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v2168::LevelSettings>::serialize(BinaryWriter &stream, const v2168::LevelSettings &value)
{
    stream.write<std::uint64_t>(value.seed);
    Serializer<SpawnSettings>::serialize(stream, value.spawn_settings);
    stream.writeVarInt<std::int32_t>(value.generator);
    stream.writeVarInt<std::int32_t>(value.game_type);
    stream.write<bool>(value.is_hardcore);
    stream.writeVarInt<std::int32_t>(value.game_difficulty);
    Serializer<BlockPos>::serialize(stream, value.default_spawn);
    stream.write<bool>(value.achievements_disabled);
    stream.writeVarInt<std::int32_t>(value.editor_world_type);
    stream.write<bool>(value.is_created_in_editor);
    stream.write<bool>(value.is_exported_from_editor);
    stream.writeVarInt<std::int32_t>(value.time);
    stream.writeVarInt<std::uint32_t>(value.education_edition_offer);
    stream.write<bool>(value.education_features_enabled);
    stream.write(value.education_product_id);
    stream.write<float>(value.rain_level);
    stream.write<float>(value.lightning_level);
    stream.write<bool>(value.confirmed_platform_locked_content);
    stream.write<bool>(value.multiplayer_game_intent);
    stream.write<bool>(value.lan_broadcast_intent);
    stream.writeVarInt<std::int32_t>(value.xbl_broadcast_intent);
    stream.writeVarInt<std::int32_t>(value.platform_broadcast_intent);
    stream.write<bool>(value.commands_enabled);
    stream.write<bool>(value.texture_packs_required);
    Serializer<v844::GameRulesChangedPacketData>::serialize(stream, value.rule_data);
    Serializer<Experiments>::serialize(stream, value.experiments);
    stream.write<bool>(value.bonus_chest_enabled);
    stream.write<bool>(value.start_with_map_enabled);
    stream.write<std::int8_t>(value.default_permissions);
    stream.write<std::int32_t>(value.server_chunk_tick_range);
    stream.write<bool>(value.has_locked_behavior_pack);
    stream.write<bool>(value.has_locked_resource_pack);
    stream.write<bool>(value.is_from_locked_template);
    stream.write<bool>(value.use_msa_gamertags_only);
    stream.write<bool>(value.is_from_world_template);
    stream.write<bool>(value.is_world_template_option_locked);
    stream.write<bool>(value.spawn_v1_villagers);
    stream.write<bool>(value.persona_disabled);
    stream.write<bool>(value.custom_skins_disabled);
    stream.write<bool>(value.emote_chat_muted);
    stream.write(value.base_game_version);
    stream.write<std::int32_t>(value.limited_world_width);
    stream.write<std::int32_t>(value.limited_world_depth);
    stream.write<bool>(value.nether_type);
    Serializer<EduSharedUriResource>::serialize(stream, value.edu_shared_uri_resource);
    stream.write<bool>(value.override_force_experimental_gameplay.has_value());
    if (value.override_force_experimental_gameplay.has_value()) {
        stream.write<bool>((*value.override_force_experimental_gameplay));
    }
    stream.write<std::uint8_t>(value.chat_restriction_level);
    stream.write<bool>(value.disable_player_interactions);
    stream.writeVarInt<std::int32_t>(value.server_editor_connection_policy);
    stream.write<bool>(value.allow_anonymous_block_drops_in_editor_worlds);
}

auto Serializer<v2168::LevelSettings>::deserialize(BinaryReader &stream) -> std::expected<v2168::LevelSettings, std::error_code>
{
    v2168::LevelSettings out;
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.seed = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = Serializer<SpawnSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.spawn_settings = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.generator = static_cast<GeneratorType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.game_type = static_cast<GameType>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_hardcore = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.game_difficulty = static_cast<Difficulty>(*v);
    }
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.default_spawn = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.achievements_disabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.editor_world_type = static_cast<v800::WorldType>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_created_in_editor = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_exported_from_editor = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.time = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.education_edition_offer = static_cast<EducationEditionOffer>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.education_features_enabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.education_product_id = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.rain_level = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.lightning_level = static_cast<float>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.confirmed_platform_locked_content = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.multiplayer_game_intent = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.lan_broadcast_intent = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.xbl_broadcast_intent = static_cast<GamePublishSetting>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.platform_broadcast_intent = static_cast<GamePublishSetting>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.commands_enabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.texture_packs_required = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<v844::GameRulesChangedPacketData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.rule_data = *v;
    }
    {
        auto v = Serializer<Experiments>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.experiments = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.bonus_chest_enabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.start_with_map_enabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.default_permissions = static_cast<PlayerPermissionLevel>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.server_chunk_tick_range = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_locked_behavior_pack = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_locked_resource_pack = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_from_locked_template = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.use_msa_gamertags_only = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_from_world_template = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_world_template_option_locked = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.spawn_v1_villagers = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.persona_disabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.custom_skins_disabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.emote_chat_muted = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.base_game_version = *v;
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.limited_world_width = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.limited_world_depth = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.nether_type = static_cast<NetherWorldType>(*v);
    }
    {
        auto v = Serializer<EduSharedUriResource>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.edu_shared_uri_resource = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.override_force_experimental_gameplay = std::move(staged);
        }
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.chat_restriction_level = static_cast<ChatRestrictionLevel>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.disable_player_interactions = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.server_editor_connection_policy = static_cast<ServerEditorConnectionPolicy>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.allow_anonymous_block_drops_in_editor_worlds = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v2225::LevelSettings>::serialize(BinaryWriter &stream, const v2225::LevelSettings &value)
{
    stream.write<std::uint64_t>(value.seed);
    Serializer<SpawnSettings>::serialize(stream, value.spawn_settings);
    stream.writeVarInt<std::int32_t>(value.generator);
    stream.writeVarInt<std::int32_t>(value.game_type);
    stream.write<bool>(value.is_hardcore);
    stream.writeVarInt<std::int32_t>(value.game_difficulty);
    Serializer<BlockPos>::serialize(stream, value.default_spawn);
    stream.write<bool>(value.achievements_disabled);
    stream.writeVarInt<std::int32_t>(value.editor_world_type);
    stream.write<bool>(value.is_created_in_editor);
    stream.write<bool>(value.is_exported_from_editor);
    stream.write<std::int8_t>(value.editor_level_migration_version);
    stream.writeVarInt<std::int32_t>(value.time);
    stream.writeVarInt<std::uint32_t>(value.education_edition_offer);
    stream.write<bool>(value.education_features_enabled);
    stream.write(value.education_product_id);
    stream.write<float>(value.rain_level);
    stream.write<float>(value.lightning_level);
    stream.write<bool>(value.confirmed_platform_locked_content);
    stream.write<bool>(value.multiplayer_game_intent);
    stream.write<bool>(value.lan_broadcast_intent);
    stream.writeVarInt<std::int32_t>(value.xbl_broadcast_intent);
    stream.writeVarInt<std::int32_t>(value.platform_broadcast_intent);
    stream.write<bool>(value.commands_enabled);
    stream.write<bool>(value.texture_packs_required);
    Serializer<v844::GameRulesChangedPacketData>::serialize(stream, value.rule_data);
    Serializer<Experiments>::serialize(stream, value.experiments);
    stream.write<bool>(value.bonus_chest_enabled);
    stream.write<bool>(value.start_with_map_enabled);
    stream.write<std::int8_t>(value.default_permissions);
    stream.write<std::int32_t>(value.server_chunk_tick_range);
    stream.write<bool>(value.has_locked_behavior_pack);
    stream.write<bool>(value.has_locked_resource_pack);
    stream.write<bool>(value.is_from_locked_template);
    stream.write<bool>(value.use_msa_gamertags_only);
    stream.write<bool>(value.is_from_world_template);
    stream.write<bool>(value.is_world_template_option_locked);
    stream.write<bool>(value.spawn_v1_villagers);
    stream.write<bool>(value.persona_disabled);
    stream.write<bool>(value.custom_skins_disabled);
    stream.write<bool>(value.emote_chat_muted);
    stream.write(value.base_game_version);
    stream.write<std::int32_t>(value.limited_world_width);
    stream.write<std::int32_t>(value.limited_world_depth);
    stream.write<bool>(value.nether_type);
    Serializer<EduSharedUriResource>::serialize(stream, value.edu_shared_uri_resource);
    stream.write<bool>(value.override_force_experimental_gameplay.has_value());
    if (value.override_force_experimental_gameplay.has_value()) {
        stream.write<bool>((*value.override_force_experimental_gameplay));
    }
    stream.write<std::uint8_t>(value.chat_restriction_level);
    stream.write<bool>(value.disable_player_interactions);
    stream.writeVarInt<std::int32_t>(value.server_editor_connection_policy);
    stream.write<bool>(value.allow_anonymous_block_drops_in_editor_worlds);
}

auto Serializer<v2225::LevelSettings>::deserialize(BinaryReader &stream) -> std::expected<v2225::LevelSettings, std::error_code>
{
    v2225::LevelSettings out;
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.seed = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = Serializer<SpawnSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.spawn_settings = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.generator = static_cast<GeneratorType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.game_type = static_cast<GameType>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_hardcore = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.game_difficulty = static_cast<Difficulty>(*v);
    }
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.default_spawn = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.achievements_disabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.editor_world_type = static_cast<v800::WorldType>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_created_in_editor = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_exported_from_editor = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.editor_level_migration_version = static_cast<EditorLevelMigrationVersion>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.time = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.education_edition_offer = static_cast<EducationEditionOffer>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.education_features_enabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.education_product_id = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.rain_level = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.lightning_level = static_cast<float>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.confirmed_platform_locked_content = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.multiplayer_game_intent = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.lan_broadcast_intent = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.xbl_broadcast_intent = static_cast<GamePublishSetting>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.platform_broadcast_intent = static_cast<GamePublishSetting>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.commands_enabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.texture_packs_required = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<v844::GameRulesChangedPacketData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.rule_data = *v;
    }
    {
        auto v = Serializer<Experiments>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.experiments = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.bonus_chest_enabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.start_with_map_enabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.default_permissions = static_cast<PlayerPermissionLevel>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.server_chunk_tick_range = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_locked_behavior_pack = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_locked_resource_pack = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_from_locked_template = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.use_msa_gamertags_only = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_from_world_template = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_world_template_option_locked = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.spawn_v1_villagers = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.persona_disabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.custom_skins_disabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.emote_chat_muted = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.base_game_version = *v;
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.limited_world_width = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.limited_world_depth = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.nether_type = static_cast<NetherWorldType>(*v);
    }
    {
        auto v = Serializer<EduSharedUriResource>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.edu_shared_uri_resource = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.override_force_experimental_gameplay = std::move(staged);
        }
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.chat_restriction_level = static_cast<ChatRestrictionLevel>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.disable_player_interactions = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.server_editor_connection_policy = static_cast<ServerEditorConnectionPolicy>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.allow_anonymous_block_drops_in_editor_worlds = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<base::StartGameItemEntry>::serialize(BinaryWriter &stream, const base::StartGameItemEntry &value)
{
    stream.write(value.name);
    stream.write<std::int16_t>(value.id);
    stream.write<bool>(value.is_component_based);
}

auto Serializer<base::StartGameItemEntry>::deserialize(BinaryReader &stream) -> std::expected<base::StartGameItemEntry, std::error_code>
{
    base::StartGameItemEntry out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = stream.read<std::int16_t>();
        if (!v) return std::unexpected(v.error());
        out.id = static_cast<std::int16_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_component_based = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<base::StartGamePacket>::serialize(BinaryWriter &stream, const base::StartGamePacket &value)
{
    stream.writeVarInt<std::int64_t>(value.entity_id);
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    stream.writeVarInt<std::int32_t>(value.entity_game_type);
    Serializer<Vec3>::serialize(stream, value.pos);
    Serializer<Vec2>::serialize(stream, value.rot);
    Serializer<base::LevelSettings>::serialize(stream, value.settings);
    stream.write(value.level_id);
    stream.write(value.level_name);
    stream.write(value.template_content_identity);
    stream.write<bool>(value.is_trial);
    Serializer<base::SyncedPlayerMovementSettings>::serialize(stream, value.movement_settings);
    stream.write<std::uint64_t>(value.level_current_time);
    stream.writeVarInt<std::int32_t>(value.enchantment_seed);
    stream.writeVarInt<std::uint32_t>(value.block_properties.size());
    for (const auto &e0 : value.block_properties) {
        Serializer<BlockEntry>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.items.size());
    for (const auto &e0 : value.items) {
        Serializer<base::StartGameItemEntry>::serialize(stream, e0);
    }
    stream.write(value.multiplayer_correlation_id);
    stream.write<bool>(value.enable_item_stack_net_manager);
    stream.write(value.server_version);
    Serializer<CompoundTag>::serialize(stream, value.player_property_data);
    stream.write<std::uint64_t>(value.server_block_type_registry_checksum);
    Serializer<UUID>::serialize(stream, value.world_template_id);
    stream.write<bool>(value.server_enabled_client_side_generation);
    stream.write<bool>(value.block_network_ids_are_hashes);
    Serializer<NetworkPermissions>::serialize(stream, value.network_permissions);
}

auto Serializer<base::StartGamePacket>::deserialize(BinaryReader &stream) -> std::expected<base::StartGamePacket, std::error_code>
{
    base::StartGamePacket out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_game_type = static_cast<GameType>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.rot = *v;
    }
    {
        auto v = Serializer<base::LevelSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.settings = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.level_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.level_name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.template_content_identity = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_trial = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<base::SyncedPlayerMovementSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.movement_settings = *v;
    }
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.level_current_time = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.enchantment_seed = static_cast<std::int32_t>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.block_properties.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.block_properties.emplace_back();
            auto v = Serializer<BlockEntry>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.block_properties.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.items.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.items.emplace_back();
            auto v = Serializer<base::StartGameItemEntry>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.items.back() = *v;
        }
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.multiplayer_correlation_id = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.enable_item_stack_net_manager = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.server_version = *v;
    }
    {
        auto v = Serializer<CompoundTag>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.player_property_data = *v;
    }
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.server_block_type_registry_checksum = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = Serializer<UUID>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.world_template_id = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.server_enabled_client_side_generation = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.block_network_ids_are_hashes = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<NetworkPermissions>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.network_permissions = *v;
    }
    return out;
}

void Serializer<v776::StartGamePacket>::serialize(BinaryWriter &stream, const v776::StartGamePacket &value)
{
    stream.writeVarInt<std::int64_t>(value.entity_id);
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    stream.writeVarInt<std::int32_t>(value.entity_game_type);
    Serializer<Vec3>::serialize(stream, value.pos);
    Serializer<Vec2>::serialize(stream, value.rot);
    Serializer<base::LevelSettings>::serialize(stream, value.settings);
    stream.write(value.level_id);
    stream.write(value.level_name);
    stream.write(value.template_content_identity);
    stream.write<bool>(value.is_trial);
    Serializer<base::SyncedPlayerMovementSettings>::serialize(stream, value.movement_settings);
    stream.write<std::uint64_t>(value.level_current_time);
    stream.writeVarInt<std::int32_t>(value.enchantment_seed);
    stream.writeVarInt<std::uint32_t>(value.block_properties.size());
    for (const auto &e0 : value.block_properties) {
        Serializer<BlockEntry>::serialize(stream, e0);
    }
    stream.write(value.multiplayer_correlation_id);
    stream.write<bool>(value.enable_item_stack_net_manager);
    stream.write(value.server_version);
    Serializer<CompoundTag>::serialize(stream, value.player_property_data);
    stream.write<std::uint64_t>(value.server_block_type_registry_checksum);
    Serializer<UUID>::serialize(stream, value.world_template_id);
    stream.write<bool>(value.server_enabled_client_side_generation);
    stream.write<bool>(value.block_network_ids_are_hashes);
    Serializer<NetworkPermissions>::serialize(stream, value.network_permissions);
}

auto Serializer<v776::StartGamePacket>::deserialize(BinaryReader &stream) -> std::expected<v776::StartGamePacket, std::error_code>
{
    v776::StartGamePacket out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_game_type = static_cast<GameType>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.rot = *v;
    }
    {
        auto v = Serializer<base::LevelSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.settings = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.level_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.level_name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.template_content_identity = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_trial = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<base::SyncedPlayerMovementSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.movement_settings = *v;
    }
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.level_current_time = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.enchantment_seed = static_cast<std::int32_t>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.block_properties.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.block_properties.emplace_back();
            auto v = Serializer<BlockEntry>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.block_properties.back() = *v;
        }
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.multiplayer_correlation_id = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.enable_item_stack_net_manager = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.server_version = *v;
    }
    {
        auto v = Serializer<CompoundTag>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.player_property_data = *v;
    }
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.server_block_type_registry_checksum = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = Serializer<UUID>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.world_template_id = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.server_enabled_client_side_generation = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.block_network_ids_are_hashes = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<NetworkPermissions>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.network_permissions = *v;
    }
    return out;
}

void Serializer<v800::StartGamePacket>::serialize(BinaryWriter &stream, const v800::StartGamePacket &value)
{
    stream.writeVarInt<std::int64_t>(value.entity_id);
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    stream.writeVarInt<std::int32_t>(value.entity_game_type);
    Serializer<Vec3>::serialize(stream, value.pos);
    Serializer<Vec2>::serialize(stream, value.rot);
    Serializer<v800::LevelSettings>::serialize(stream, value.settings);
    stream.write(value.level_id);
    stream.write(value.level_name);
    stream.write(value.template_content_identity);
    stream.write<bool>(value.is_trial);
    Serializer<base::SyncedPlayerMovementSettings>::serialize(stream, value.movement_settings);
    stream.write<std::uint64_t>(value.level_current_time);
    stream.writeVarInt<std::int32_t>(value.enchantment_seed);
    stream.writeVarInt<std::uint32_t>(value.block_properties.size());
    for (const auto &e0 : value.block_properties) {
        Serializer<BlockEntry>::serialize(stream, e0);
    }
    stream.write(value.multiplayer_correlation_id);
    stream.write<bool>(value.enable_item_stack_net_manager);
    stream.write(value.server_version);
    Serializer<CompoundTag>::serialize(stream, value.player_property_data);
    stream.write<std::uint64_t>(value.server_block_type_registry_checksum);
    Serializer<UUID>::serialize(stream, value.world_template_id);
    stream.write<bool>(value.server_enabled_client_side_generation);
    stream.write<bool>(value.block_network_ids_are_hashes);
    Serializer<NetworkPermissions>::serialize(stream, value.network_permissions);
}

auto Serializer<v800::StartGamePacket>::deserialize(BinaryReader &stream) -> std::expected<v800::StartGamePacket, std::error_code>
{
    v800::StartGamePacket out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_game_type = static_cast<GameType>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.rot = *v;
    }
    {
        auto v = Serializer<v800::LevelSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.settings = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.level_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.level_name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.template_content_identity = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_trial = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<base::SyncedPlayerMovementSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.movement_settings = *v;
    }
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.level_current_time = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.enchantment_seed = static_cast<std::int32_t>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.block_properties.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.block_properties.emplace_back();
            auto v = Serializer<BlockEntry>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.block_properties.back() = *v;
        }
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.multiplayer_correlation_id = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.enable_item_stack_net_manager = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.server_version = *v;
    }
    {
        auto v = Serializer<CompoundTag>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.player_property_data = *v;
    }
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.server_block_type_registry_checksum = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = Serializer<UUID>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.world_template_id = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.server_enabled_client_side_generation = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.block_network_ids_are_hashes = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<NetworkPermissions>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.network_permissions = *v;
    }
    return out;
}

void Serializer<v818::StartGamePacket>::serialize(BinaryWriter &stream, const v818::StartGamePacket &value)
{
    stream.writeVarInt<std::int64_t>(value.entity_id);
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    stream.writeVarInt<std::int32_t>(value.entity_game_type);
    Serializer<Vec3>::serialize(stream, value.pos);
    Serializer<Vec2>::serialize(stream, value.rot);
    Serializer<v818::LevelSettings>::serialize(stream, value.settings);
    stream.write(value.level_id);
    stream.write(value.level_name);
    stream.write(value.template_content_identity);
    stream.write<bool>(value.is_trial);
    Serializer<v818::SyncedPlayerMovementSettings>::serialize(stream, value.movement_settings);
    stream.write<std::uint64_t>(value.level_current_time);
    stream.writeVarInt<std::int32_t>(value.enchantment_seed);
    stream.writeVarInt<std::uint32_t>(value.block_properties.size());
    for (const auto &e0 : value.block_properties) {
        Serializer<BlockEntry>::serialize(stream, e0);
    }
    stream.write(value.multiplayer_correlation_id);
    stream.write<bool>(value.enable_item_stack_net_manager);
    stream.write(value.server_version);
    Serializer<CompoundTag>::serialize(stream, value.player_property_data);
    stream.write<std::uint64_t>(value.server_block_type_registry_checksum);
    Serializer<UUID>::serialize(stream, value.world_template_id);
    stream.write<bool>(value.server_enabled_client_side_generation);
    stream.write<bool>(value.block_network_ids_are_hashes);
    Serializer<NetworkPermissions>::serialize(stream, value.network_permissions);
}

auto Serializer<v818::StartGamePacket>::deserialize(BinaryReader &stream) -> std::expected<v818::StartGamePacket, std::error_code>
{
    v818::StartGamePacket out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_game_type = static_cast<GameType>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.rot = *v;
    }
    {
        auto v = Serializer<v818::LevelSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.settings = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.level_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.level_name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.template_content_identity = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_trial = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<v818::SyncedPlayerMovementSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.movement_settings = *v;
    }
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.level_current_time = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.enchantment_seed = static_cast<std::int32_t>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.block_properties.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.block_properties.emplace_back();
            auto v = Serializer<BlockEntry>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.block_properties.back() = *v;
        }
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.multiplayer_correlation_id = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.enable_item_stack_net_manager = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.server_version = *v;
    }
    {
        auto v = Serializer<CompoundTag>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.player_property_data = *v;
    }
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.server_block_type_registry_checksum = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = Serializer<UUID>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.world_template_id = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.server_enabled_client_side_generation = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.block_network_ids_are_hashes = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<NetworkPermissions>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.network_permissions = *v;
    }
    return out;
}

void Serializer<v827::StartGamePacket>::serialize(BinaryWriter &stream, const v827::StartGamePacket &value)
{
    stream.writeVarInt<std::int64_t>(value.entity_id);
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    stream.writeVarInt<std::int32_t>(value.entity_game_type);
    Serializer<Vec3>::serialize(stream, value.pos);
    Serializer<Vec2>::serialize(stream, value.rot);
    Serializer<v818::LevelSettings>::serialize(stream, value.settings);
    stream.write(value.level_id);
    stream.write(value.level_name);
    stream.write(value.template_content_identity);
    stream.write<bool>(value.is_trial);
    Serializer<v818::SyncedPlayerMovementSettings>::serialize(stream, value.movement_settings);
    stream.write<std::uint64_t>(value.level_current_time);
    stream.writeVarInt<std::int32_t>(value.enchantment_seed);
    stream.writeVarInt<std::uint32_t>(value.block_properties.size());
    for (const auto &e0 : value.block_properties) {
        Serializer<BlockEntry>::serialize(stream, e0);
    }
    stream.write(value.multiplayer_correlation_id);
    stream.write<bool>(value.enable_item_stack_net_manager);
    stream.write(value.server_version);
    Serializer<CompoundTag>::serialize(stream, value.player_property_data);
    stream.write<std::uint64_t>(value.server_block_type_registry_checksum);
    Serializer<UUID>::serialize(stream, value.world_template_id);
    stream.write<bool>(value.server_enabled_client_side_generation);
    stream.write<bool>(value.block_network_ids_are_hashes);
    stream.write<bool>(value.tick_death_systems_enabled);
    Serializer<NetworkPermissions>::serialize(stream, value.network_permissions);
}

auto Serializer<v827::StartGamePacket>::deserialize(BinaryReader &stream) -> std::expected<v827::StartGamePacket, std::error_code>
{
    v827::StartGamePacket out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_game_type = static_cast<GameType>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.rot = *v;
    }
    {
        auto v = Serializer<v818::LevelSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.settings = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.level_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.level_name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.template_content_identity = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_trial = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<v818::SyncedPlayerMovementSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.movement_settings = *v;
    }
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.level_current_time = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.enchantment_seed = static_cast<std::int32_t>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.block_properties.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.block_properties.emplace_back();
            auto v = Serializer<BlockEntry>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.block_properties.back() = *v;
        }
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.multiplayer_correlation_id = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.enable_item_stack_net_manager = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.server_version = *v;
    }
    {
        auto v = Serializer<CompoundTag>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.player_property_data = *v;
    }
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.server_block_type_registry_checksum = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = Serializer<UUID>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.world_template_id = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.server_enabled_client_side_generation = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.block_network_ids_are_hashes = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.tick_death_systems_enabled = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<NetworkPermissions>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.network_permissions = *v;
    }
    return out;
}

void Serializer<v844::StartGamePacket>::serialize(BinaryWriter &stream, const v844::StartGamePacket &value)
{
    stream.writeVarInt<std::int64_t>(value.entity_id);
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    stream.writeVarInt<std::int32_t>(value.entity_game_type);
    Serializer<Vec3>::serialize(stream, value.pos);
    Serializer<Vec2>::serialize(stream, value.rot);
    Serializer<v844::LevelSettings>::serialize(stream, value.settings);
    stream.write(value.level_id);
    stream.write(value.level_name);
    stream.write(value.template_content_identity);
    stream.write<bool>(value.is_trial);
    Serializer<v818::SyncedPlayerMovementSettings>::serialize(stream, value.movement_settings);
    stream.write<std::uint64_t>(value.level_current_time);
    stream.writeVarInt<std::int32_t>(value.enchantment_seed);
    stream.writeVarInt<std::uint32_t>(value.block_properties.size());
    for (const auto &e0 : value.block_properties) {
        Serializer<BlockEntry>::serialize(stream, e0);
    }
    stream.write(value.multiplayer_correlation_id);
    stream.write<bool>(value.enable_item_stack_net_manager);
    stream.write(value.server_version);
    Serializer<CompoundTag>::serialize(stream, value.player_property_data);
    stream.write<std::uint64_t>(value.server_block_type_registry_checksum);
    Serializer<UUID>::serialize(stream, value.world_template_id);
    stream.write<bool>(value.server_enabled_client_side_generation);
    stream.write<bool>(value.block_network_ids_are_hashes);
    stream.write<bool>(value.tick_death_systems_enabled);
    Serializer<NetworkPermissions>::serialize(stream, value.network_permissions);
}

auto Serializer<v844::StartGamePacket>::deserialize(BinaryReader &stream) -> std::expected<v844::StartGamePacket, std::error_code>
{
    v844::StartGamePacket out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_game_type = static_cast<GameType>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.rot = *v;
    }
    {
        auto v = Serializer<v844::LevelSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.settings = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.level_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.level_name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.template_content_identity = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_trial = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<v818::SyncedPlayerMovementSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.movement_settings = *v;
    }
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.level_current_time = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.enchantment_seed = static_cast<std::int32_t>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.block_properties.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.block_properties.emplace_back();
            auto v = Serializer<BlockEntry>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.block_properties.back() = *v;
        }
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.multiplayer_correlation_id = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.enable_item_stack_net_manager = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.server_version = *v;
    }
    {
        auto v = Serializer<CompoundTag>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.player_property_data = *v;
    }
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.server_block_type_registry_checksum = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = Serializer<UUID>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.world_template_id = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.server_enabled_client_side_generation = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.block_network_ids_are_hashes = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.tick_death_systems_enabled = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<NetworkPermissions>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.network_permissions = *v;
    }
    return out;
}

void Serializer<v898::StartGamePacket>::serialize(BinaryWriter &stream, const v898::StartGamePacket &value)
{
    stream.writeVarInt<std::int64_t>(value.entity_id);
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    stream.writeVarInt<std::int32_t>(value.entity_game_type);
    Serializer<Vec3>::serialize(stream, value.pos);
    Serializer<Vec2>::serialize(stream, value.rot);
    Serializer<v844::LevelSettings>::serialize(stream, value.settings);
    stream.write(value.level_id);
    stream.write(value.level_name);
    stream.write(value.template_content_identity);
    stream.write<bool>(value.is_trial);
    Serializer<v818::SyncedPlayerMovementSettings>::serialize(stream, value.movement_settings);
    stream.write<std::uint64_t>(value.level_current_time);
    stream.writeVarInt<std::int32_t>(value.enchantment_seed);
    stream.writeVarInt<std::uint32_t>(value.block_properties.size());
    for (const auto &e0 : value.block_properties) {
        Serializer<BlockEntry>::serialize(stream, e0);
    }
    stream.write(value.multiplayer_correlation_id);
    stream.write<bool>(value.enable_item_stack_net_manager);
    stream.write(value.server_version);
    Serializer<CompoundTag>::serialize(stream, value.player_property_data);
    stream.write<std::uint64_t>(value.server_block_type_registry_checksum);
    Serializer<UUID>::serialize(stream, value.world_template_id);
    stream.write<bool>(value.server_enabled_client_side_generation);
    stream.write<bool>(value.block_network_ids_are_hashes);
    Serializer<NetworkPermissions>::serialize(stream, value.network_permissions);
}

auto Serializer<v898::StartGamePacket>::deserialize(BinaryReader &stream) -> std::expected<v898::StartGamePacket, std::error_code>
{
    v898::StartGamePacket out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_game_type = static_cast<GameType>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.rot = *v;
    }
    {
        auto v = Serializer<v844::LevelSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.settings = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.level_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.level_name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.template_content_identity = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_trial = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<v818::SyncedPlayerMovementSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.movement_settings = *v;
    }
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.level_current_time = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.enchantment_seed = static_cast<std::int32_t>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.block_properties.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.block_properties.emplace_back();
            auto v = Serializer<BlockEntry>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.block_properties.back() = *v;
        }
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.multiplayer_correlation_id = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.enable_item_stack_net_manager = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.server_version = *v;
    }
    {
        auto v = Serializer<CompoundTag>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.player_property_data = *v;
    }
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.server_block_type_registry_checksum = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = Serializer<UUID>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.world_template_id = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.server_enabled_client_side_generation = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.block_network_ids_are_hashes = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<NetworkPermissions>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.network_permissions = *v;
    }
    return out;
}

void Serializer<v924::StartGamePacket>::serialize(BinaryWriter &stream, const v924::StartGamePacket &value)
{
    stream.writeVarInt<std::int64_t>(value.entity_id);
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    stream.writeVarInt<std::int32_t>(value.entity_game_type);
    Serializer<Vec3>::serialize(stream, value.pos);
    Serializer<Vec2>::serialize(stream, value.rot);
    Serializer<v924::LevelSettings>::serialize(stream, value.settings);
    stream.write(value.level_id);
    stream.write(value.level_name);
    stream.write(value.template_content_identity);
    stream.write<bool>(value.is_trial);
    Serializer<v818::SyncedPlayerMovementSettings>::serialize(stream, value.movement_settings);
    stream.write<std::uint64_t>(value.level_current_time);
    stream.writeVarInt<std::int32_t>(value.enchantment_seed);
    stream.writeVarInt<std::uint32_t>(value.block_properties.size());
    for (const auto &e0 : value.block_properties) {
        Serializer<BlockEntry>::serialize(stream, e0);
    }
    stream.write(value.multiplayer_correlation_id);
    stream.write<bool>(value.enable_item_stack_net_manager);
    stream.write(value.server_version);
    Serializer<CompoundTag>::serialize(stream, value.player_property_data);
    stream.write<std::uint64_t>(value.server_block_type_registry_checksum);
    Serializer<UUID>::serialize(stream, value.world_template_id);
    stream.write<bool>(value.server_enabled_client_side_generation);
    stream.write<bool>(value.block_network_ids_are_hashes);
    Serializer<NetworkPermissions>::serialize(stream, value.network_permissions);
    stream.write<bool>(value.server_configuration_join_info.has_value());
    if (value.server_configuration_join_info.has_value()) {
        Serializer<base::ServerConfigurationJoinInfo>::serialize(stream, (*value.server_configuration_join_info));
    }
    Serializer<ServerTelemetryData>::serialize(stream, value.server_telemetry_data);
}

auto Serializer<v924::StartGamePacket>::deserialize(BinaryReader &stream) -> std::expected<v924::StartGamePacket, std::error_code>
{
    v924::StartGamePacket out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_game_type = static_cast<GameType>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.rot = *v;
    }
    {
        auto v = Serializer<v924::LevelSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.settings = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.level_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.level_name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.template_content_identity = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_trial = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<v818::SyncedPlayerMovementSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.movement_settings = *v;
    }
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.level_current_time = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.enchantment_seed = static_cast<std::int32_t>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.block_properties.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.block_properties.emplace_back();
            auto v = Serializer<BlockEntry>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.block_properties.back() = *v;
        }
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.multiplayer_correlation_id = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.enable_item_stack_net_manager = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.server_version = *v;
    }
    {
        auto v = Serializer<CompoundTag>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.player_property_data = *v;
    }
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.server_block_type_registry_checksum = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = Serializer<UUID>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.world_template_id = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.server_enabled_client_side_generation = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.block_network_ids_are_hashes = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<NetworkPermissions>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.network_permissions = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            base::ServerConfigurationJoinInfo staged{};
            auto v = Serializer<base::ServerConfigurationJoinInfo>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.server_configuration_join_info = std::move(staged);
        }
    }
    {
        auto v = Serializer<ServerTelemetryData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.server_telemetry_data = *v;
    }
    return out;
}

void Serializer<v944::StartGamePacket>::serialize(BinaryWriter &stream, const v944::StartGamePacket &value)
{
    stream.writeVarInt<std::int64_t>(value.entity_id);
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    stream.writeVarInt<std::int32_t>(value.entity_game_type);
    Serializer<Vec3>::serialize(stream, value.pos);
    Serializer<Vec2>::serialize(stream, value.rot);
    Serializer<v944::LevelSettings>::serialize(stream, value.settings);
    stream.write(value.level_id);
    stream.write(value.level_name);
    stream.write(value.template_content_identity);
    stream.write<bool>(value.is_trial);
    Serializer<v818::SyncedPlayerMovementSettings>::serialize(stream, value.movement_settings);
    stream.write<std::uint64_t>(value.level_current_time);
    stream.writeVarInt<std::int32_t>(value.enchantment_seed);
    stream.writeVarInt<std::uint32_t>(value.block_properties.size());
    for (const auto &e0 : value.block_properties) {
        Serializer<BlockEntry>::serialize(stream, e0);
    }
    stream.write(value.multiplayer_correlation_id);
    stream.write<bool>(value.enable_item_stack_net_manager);
    stream.write(value.server_version);
    Serializer<CompoundTag>::serialize(stream, value.player_property_data);
    stream.write<std::uint64_t>(value.server_block_type_registry_checksum);
    Serializer<UUID>::serialize(stream, value.world_template_id);
    stream.write<bool>(value.server_enabled_client_side_generation);
    stream.write<bool>(value.block_network_ids_are_hashes);
    Serializer<NetworkPermissions>::serialize(stream, value.network_permissions);
    stream.write<bool>(value.server_configuration_join_info.has_value());
    if (value.server_configuration_join_info.has_value()) {
        Serializer<v944::ServerConfigurationJoinInfo>::serialize(stream, (*value.server_configuration_join_info));
    }
    Serializer<ServerTelemetryData>::serialize(stream, value.server_telemetry_data);
}

auto Serializer<v944::StartGamePacket>::deserialize(BinaryReader &stream) -> std::expected<v944::StartGamePacket, std::error_code>
{
    v944::StartGamePacket out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_game_type = static_cast<GameType>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.rot = *v;
    }
    {
        auto v = Serializer<v944::LevelSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.settings = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.level_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.level_name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.template_content_identity = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_trial = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<v818::SyncedPlayerMovementSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.movement_settings = *v;
    }
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.level_current_time = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.enchantment_seed = static_cast<std::int32_t>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.block_properties.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.block_properties.emplace_back();
            auto v = Serializer<BlockEntry>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.block_properties.back() = *v;
        }
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.multiplayer_correlation_id = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.enable_item_stack_net_manager = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.server_version = *v;
    }
    {
        auto v = Serializer<CompoundTag>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.player_property_data = *v;
    }
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.server_block_type_registry_checksum = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = Serializer<UUID>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.world_template_id = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.server_enabled_client_side_generation = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.block_network_ids_are_hashes = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<NetworkPermissions>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.network_permissions = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v944::ServerConfigurationJoinInfo staged{};
            auto v = Serializer<v944::ServerConfigurationJoinInfo>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.server_configuration_join_info = std::move(staged);
        }
    }
    {
        auto v = Serializer<ServerTelemetryData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.server_telemetry_data = *v;
    }
    return out;
}

void Serializer<v1001::StartGamePacket>::serialize(BinaryWriter &stream, const v1001::StartGamePacket &value)
{
    stream.writeVarInt<std::int64_t>(value.entity_id);
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    stream.writeVarInt<std::int32_t>(value.entity_game_type);
    Serializer<Vec3>::serialize(stream, value.pos);
    Serializer<Vec2>::serialize(stream, value.rot);
    Serializer<v1001::LevelSettings>::serialize(stream, value.settings);
    stream.write(value.level_id);
    stream.write(value.level_name);
    stream.write(value.template_content_identity);
    stream.write<bool>(value.is_trial);
    Serializer<v818::SyncedPlayerMovementSettings>::serialize(stream, value.movement_settings);
    stream.write<std::uint64_t>(value.level_current_time);
    stream.writeVarInt<std::int32_t>(value.enchantment_seed);
    stream.writeVarInt<std::uint32_t>(value.block_properties.size());
    for (const auto &e0 : value.block_properties) {
        Serializer<BlockEntry>::serialize(stream, e0);
    }
    stream.write(value.multiplayer_correlation_id);
    stream.write<bool>(value.enable_item_stack_net_manager);
    stream.write(value.server_version);
    Serializer<CompoundTag>::serialize(stream, value.player_property_data);
    stream.write<std::uint64_t>(value.server_block_type_registry_checksum);
    Serializer<UUID>::serialize(stream, value.world_template_id);
    stream.write<bool>(value.server_enabled_client_side_generation);
    stream.write<bool>(value.block_network_ids_are_hashes);
    Serializer<NetworkPermissions>::serialize(stream, value.network_permissions);
    stream.write<bool>(value.is_logging_chat);
    stream.write<bool>(value.server_configuration_join_info.has_value());
    if (value.server_configuration_join_info.has_value()) {
        Serializer<v1001::ServerConfigurationJoinInfo>::serialize(stream, (*value.server_configuration_join_info));
    }
    Serializer<ServerTelemetryData>::serialize(stream, value.server_telemetry_data);
}

auto Serializer<v1001::StartGamePacket>::deserialize(BinaryReader &stream) -> std::expected<v1001::StartGamePacket, std::error_code>
{
    v1001::StartGamePacket out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_game_type = static_cast<GameType>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.rot = *v;
    }
    {
        auto v = Serializer<v1001::LevelSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.settings = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.level_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.level_name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.template_content_identity = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_trial = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<v818::SyncedPlayerMovementSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.movement_settings = *v;
    }
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.level_current_time = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.enchantment_seed = static_cast<std::int32_t>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.block_properties.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.block_properties.emplace_back();
            auto v = Serializer<BlockEntry>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.block_properties.back() = *v;
        }
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.multiplayer_correlation_id = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.enable_item_stack_net_manager = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.server_version = *v;
    }
    {
        auto v = Serializer<CompoundTag>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.player_property_data = *v;
    }
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.server_block_type_registry_checksum = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = Serializer<UUID>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.world_template_id = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.server_enabled_client_side_generation = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.block_network_ids_are_hashes = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<NetworkPermissions>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.network_permissions = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_logging_chat = static_cast<bool>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v1001::ServerConfigurationJoinInfo staged{};
            auto v = Serializer<v1001::ServerConfigurationJoinInfo>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.server_configuration_join_info = std::move(staged);
        }
    }
    {
        auto v = Serializer<ServerTelemetryData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.server_telemetry_data = *v;
    }
    return out;
}

void Serializer<v2168::StartGamePacket>::serialize(BinaryWriter &stream, const v2168::StartGamePacket &value)
{
    stream.writeVarInt<std::int64_t>(value.entity_id);
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    stream.writeVarInt<std::int32_t>(value.entity_game_type);
    Serializer<Vec3>::serialize(stream, value.pos);
    Serializer<Vec2>::serialize(stream, value.rot);
    Serializer<v2168::LevelSettings>::serialize(stream, value.settings);
    stream.write(value.level_id);
    stream.write(value.level_name);
    stream.write(value.template_content_identity);
    stream.write<bool>(value.is_trial);
    Serializer<v818::SyncedPlayerMovementSettings>::serialize(stream, value.movement_settings);
    stream.write<std::uint64_t>(value.level_current_time);
    stream.writeVarInt<std::int32_t>(value.enchantment_seed);
    stream.writeVarInt<std::uint32_t>(value.block_properties.size());
    for (const auto &e0 : value.block_properties) {
        Serializer<v2168::ServerBlockProperty>::serialize(stream, e0);
    }
    stream.write(value.multiplayer_correlation_id);
    stream.write<bool>(value.enable_item_stack_net_manager);
    stream.write(value.server_version);
    Serializer<CompoundTag>::serialize(stream, value.player_property_data);
    stream.write<std::uint64_t>(value.server_block_type_registry_checksum);
    Serializer<UUID>::serialize(stream, value.world_template_id);
    stream.write<bool>(value.server_enabled_client_side_generation);
    stream.write<bool>(value.block_network_ids_are_hashes);
    Serializer<NetworkPermissions>::serialize(stream, value.network_permissions);
    stream.write<bool>(value.server_configuration_join_info.has_value());
    if (value.server_configuration_join_info.has_value()) {
        Serializer<v2168::ServerConfigurationJoinInfo>::serialize(stream, (*value.server_configuration_join_info));
    }
    Serializer<ServerTelemetryData>::serialize(stream, value.server_telemetry_data);
}

auto Serializer<v2168::StartGamePacket>::deserialize(BinaryReader &stream) -> std::expected<v2168::StartGamePacket, std::error_code>
{
    v2168::StartGamePacket out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_game_type = static_cast<GameType>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.rot = *v;
    }
    {
        auto v = Serializer<v2168::LevelSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.settings = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.level_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.level_name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.template_content_identity = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_trial = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<v818::SyncedPlayerMovementSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.movement_settings = *v;
    }
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.level_current_time = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.enchantment_seed = static_cast<std::int32_t>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.block_properties.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.block_properties.emplace_back();
            auto v = Serializer<v2168::ServerBlockProperty>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.block_properties.back() = *v;
        }
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.multiplayer_correlation_id = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.enable_item_stack_net_manager = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.server_version = *v;
    }
    {
        auto v = Serializer<CompoundTag>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.player_property_data = *v;
    }
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.server_block_type_registry_checksum = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = Serializer<UUID>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.world_template_id = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.server_enabled_client_side_generation = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.block_network_ids_are_hashes = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<NetworkPermissions>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.network_permissions = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v2168::ServerConfigurationJoinInfo staged{};
            auto v = Serializer<v2168::ServerConfigurationJoinInfo>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.server_configuration_join_info = std::move(staged);
        }
    }
    {
        auto v = Serializer<ServerTelemetryData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.server_telemetry_data = *v;
    }
    return out;
}

void Serializer<v2225::StartGamePacket>::serialize(BinaryWriter &stream, const v2225::StartGamePacket &value)
{
    stream.writeVarInt<std::int64_t>(value.entity_id);
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    stream.writeVarInt<std::int32_t>(value.entity_game_type);
    Serializer<Vec3>::serialize(stream, value.pos);
    Serializer<Vec2>::serialize(stream, value.rot);
    Serializer<v2225::LevelSettings>::serialize(stream, value.settings);
    stream.write(value.level_id);
    stream.write(value.level_name);
    stream.write(value.template_content_identity);
    stream.write<bool>(value.is_trial);
    Serializer<v818::SyncedPlayerMovementSettings>::serialize(stream, value.movement_settings);
    stream.write<std::uint64_t>(value.level_current_time);
    stream.writeVarInt<std::int32_t>(value.enchantment_seed);
    stream.writeVarInt<std::uint32_t>(value.block_properties.size());
    for (const auto &e0 : value.block_properties) {
        Serializer<v2168::ServerBlockProperty>::serialize(stream, e0);
    }
    stream.write(value.multiplayer_correlation_id);
    stream.write<bool>(value.enable_item_stack_net_manager);
    stream.write(value.server_version);
    Serializer<CompoundTag>::serialize(stream, value.player_property_data);
    stream.write<std::uint64_t>(value.server_block_type_registry_checksum);
    Serializer<UUID>::serialize(stream, value.world_template_id);
    stream.write<bool>(value.server_enabled_client_side_generation);
    stream.write<bool>(value.block_network_ids_are_hashes);
    Serializer<NetworkPermissions>::serialize(stream, value.network_permissions);
    stream.write<bool>(value.server_configuration_join_info.has_value());
    if (value.server_configuration_join_info.has_value()) {
        Serializer<v2168::ServerConfigurationJoinInfo>::serialize(stream, (*value.server_configuration_join_info));
    }
    Serializer<ServerTelemetryData>::serialize(stream, value.server_telemetry_data);
}

auto Serializer<v2225::StartGamePacket>::deserialize(BinaryReader &stream) -> std::expected<v2225::StartGamePacket, std::error_code>
{
    v2225::StartGamePacket out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_game_type = static_cast<GameType>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.rot = *v;
    }
    {
        auto v = Serializer<v2225::LevelSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.settings = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.level_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.level_name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.template_content_identity = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_trial = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<v818::SyncedPlayerMovementSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.movement_settings = *v;
    }
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.level_current_time = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.enchantment_seed = static_cast<std::int32_t>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.block_properties.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.block_properties.emplace_back();
            auto v = Serializer<v2168::ServerBlockProperty>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.block_properties.back() = *v;
        }
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.multiplayer_correlation_id = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.enable_item_stack_net_manager = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.server_version = *v;
    }
    {
        auto v = Serializer<CompoundTag>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.player_property_data = *v;
    }
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.server_block_type_registry_checksum = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = Serializer<UUID>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.world_template_id = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.server_enabled_client_side_generation = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.block_network_ids_are_hashes = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<NetworkPermissions>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.network_permissions = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v2168::ServerConfigurationJoinInfo staged{};
            auto v = Serializer<v2168::ServerConfigurationJoinInfo>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.server_configuration_join_info = std::move(staged);
        }
    }
    {
        auto v = Serializer<ServerTelemetryData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.server_telemetry_data = *v;
    }
    return out;
}

void Serializer<base::GameRulesChangedPacket>::serialize(BinaryWriter &stream, const base::GameRulesChangedPacket &value)
{
    Serializer<base::GameRulesChangedPacketData>::serialize(stream, value.rule_data);
}

auto Serializer<base::GameRulesChangedPacket>::deserialize(BinaryReader &stream) -> std::expected<base::GameRulesChangedPacket, std::error_code>
{
    base::GameRulesChangedPacket out;
    {
        auto v = Serializer<base::GameRulesChangedPacketData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.rule_data = *v;
    }
    return out;
}

void Serializer<v844::GameRulesChangedPacket>::serialize(BinaryWriter &stream, const v844::GameRulesChangedPacket &value)
{
    Serializer<v844::GameRulesChangedPacketData>::serialize(stream, value.rule_data);
}

auto Serializer<v844::GameRulesChangedPacket>::deserialize(BinaryReader &stream) -> std::expected<v844::GameRulesChangedPacket, std::error_code>
{
    v844::GameRulesChangedPacket out;
    {
        auto v = Serializer<v844::GameRulesChangedPacketData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.rule_data = *v;
    }
    return out;
}

void Serializer<SetCommandsEnabledPacket>::serialize(BinaryWriter &stream, const SetCommandsEnabledPacket &value)
{
    stream.write<bool>(value.commands_enabled);
}

auto Serializer<SetCommandsEnabledPacket>::deserialize(BinaryReader &stream) -> std::expected<SetCommandsEnabledPacket, std::error_code>
{
    SetCommandsEnabledPacket out;
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.commands_enabled = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<SetDifficultyPacket>::serialize(BinaryWriter &stream, const SetDifficultyPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.difficulty);
}

auto Serializer<SetDifficultyPacket>::deserialize(BinaryReader &stream) -> std::expected<SetDifficultyPacket, std::error_code>
{
    SetDifficultyPacket out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.difficulty = static_cast<Difficulty>(*v);
    }
    return out;
}

void Serializer<SetPlayerGameTypePacket>::serialize(BinaryWriter &stream, const SetPlayerGameTypePacket &value)
{
    stream.writeVarInt<std::int32_t>(value.player_game_type);
}

auto Serializer<SetPlayerGameTypePacket>::deserialize(BinaryReader &stream) -> std::expected<SetPlayerGameTypePacket, std::error_code>
{
    SetPlayerGameTypePacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.player_game_type = static_cast<GameType>(*v);
    }
    return out;
}

void Serializer<ShowCreditsPacket>::serialize(BinaryWriter &stream, const ShowCreditsPacket &value)
{
    stream.writeVarInt<std::uint64_t>(value.player_id);
    stream.writeVarInt<std::int32_t>(value.credits_state);
}

auto Serializer<ShowCreditsPacket>::deserialize(BinaryReader &stream) -> std::expected<ShowCreditsPacket, std::error_code>
{
    ShowCreditsPacket out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.player_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.credits_state = static_cast<ShowCreditsPacket::CreditsState>(*v);
    }
    return out;
}

void Serializer<SetDefaultGameTypePacket>::serialize(BinaryWriter &stream, const SetDefaultGameTypePacket &value)
{
    stream.writeVarInt<std::int32_t>(value.default_game_type);
}

auto Serializer<SetDefaultGameTypePacket>::deserialize(BinaryReader &stream) -> std::expected<SetDefaultGameTypePacket, std::error_code>
{
    SetDefaultGameTypePacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.default_game_type = static_cast<GameType>(*v);
    }
    return out;
}

void Serializer<MultiplayerSettingsPacket>::serialize(BinaryWriter &stream, const MultiplayerSettingsPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.packet_type);
}

auto Serializer<MultiplayerSettingsPacket>::deserialize(BinaryReader &stream) -> std::expected<MultiplayerSettingsPacket, std::error_code>
{
    MultiplayerSettingsPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.packet_type = static_cast<MultiplayerSettingsPacketType>(*v);
    }
    return out;
}

void Serializer<UpdatePlayerGameTypePacket>::serialize(BinaryWriter &stream, const UpdatePlayerGameTypePacket &value)
{
    stream.writeVarInt<std::int32_t>(value.player_game_type);
    stream.writeVarInt<std::int64_t>(value.target_player);
    stream.writeVarInt<std::uint64_t>(value.tick);
}

auto Serializer<UpdatePlayerGameTypePacket>::deserialize(BinaryReader &stream) -> std::expected<UpdatePlayerGameTypePacket, std::error_code>
{
    UpdatePlayerGameTypePacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.player_game_type = static_cast<GameType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.target_player = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.tick = static_cast<PlayerInputTick>(*v);
    }
    return out;
}

void Serializer<SimulationTypePacket>::serialize(BinaryWriter &stream, const SimulationTypePacket &value)
{
    stream.write<std::uint8_t>(value.sim_type);
}

auto Serializer<SimulationTypePacket>::deserialize(BinaryReader &stream) -> std::expected<SimulationTypePacket, std::error_code>
{
    SimulationTypePacket out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.sim_type = static_cast<SimulationType>(*v);
    }
    return out;
}

}  // namespace bedrock::protocol
