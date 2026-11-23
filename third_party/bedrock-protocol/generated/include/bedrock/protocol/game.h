#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <expected>
#include <optional>
#include <string>
#include <string_view>
#include <system_error>
#include <variant>
#include <vector>

#include <bedrock/protocol/detail/reflect.hpp>
#include <bedrock/protocol/enum.hpp>
#include <bedrock/protocol/nbt.hpp>
#include <bedrock/protocol/packet.hpp>
#include <bedrock/protocol/serializer.hpp>
#include <bedrock/protocol/stream.hpp>
#include <bedrock/protocol/uuid.hpp>

#include <bedrock/protocol/actor.h>
#include <bedrock/protocol/command.h>
#include <bedrock/protocol/common.h>
#include <bedrock/protocol/edu.h>
#include <bedrock/protocol/movement.h>
#include <bedrock/protocol/network.h>
#include <bedrock/protocol/presence.h>

namespace bedrock::protocol {

enum class GameType : int {
    Undefined = -1,
    Survival = 0,
    Creative = 1,
    Adventure = 2,
    Default = 5,
    Spectator = 6,
    WorldDefault = 0,
};

enum class Difficulty : int {
    Peaceful = 0,
    Easy = 1,
    Normal = 2,
    Hard = 3,
    Count = 4,
    Unknown = 5,
};

enum class GeneratorType : int {
    Legacy = 0,
    Overworld = 1,
    Flat = 2,
    Nether = 3,
    TheEnd = 4,
    Void = 5,
    Undefined = 6,
};

enum class NetherWorldType : bool {
    Normal = 0,
    Flat = 1,
};

enum class SpawnBiomeType : std::int16_t {
    Default = 0,
    UserDefined = 1,
};

enum class EditorLevelMigrationVersion : std::int8_t {
    Legacy = 0,
    EditorAchievements = 1,
};

enum class EducationEditionOffer : std::uint32_t {
    None = 0,
    RestOfWorld = 1,
    ChinaDeprecated = 2,
};

enum class ChatRestrictionLevel : std::uint8_t {
    None = 0,
    Dropped = 1,
    Disabled = 2,
};

struct SpawnSettings {
    SpawnBiomeType type{};
    std::string user_defined_biome_name{};
    DimensionType dimension{};
};

struct ExperimentToggle {
    std::string name{};
    bool enabled{};
};

struct Experiments {
    std::vector<ExperimentToggle> toggles{};
    bool experiments_ever_toggled{};
};

struct BlockEntry {
    std::string name{};
    CompoundTag properties{};
};

struct SetCommandsEnabledPacket {
    static constexpr int Id = 59;
    bool commands_enabled{};
};

struct SetDifficultyPacket {
    static constexpr int Id = 60;
    Difficulty difficulty{};
};

struct SetPlayerGameTypePacket {
    static constexpr int Id = 62;
    GameType player_game_type{};
};

namespace ShowCreditsPacket_nested {

enum class CreditsState : int {
    Start = 0,
    Finished = 1,
};

}  // namespace ShowCreditsPacket_nested

struct ShowCreditsPacket {
    using CreditsState = ShowCreditsPacket_nested::CreditsState;

    static constexpr int Id = 75;
    ActorRuntimeID player_id{};
    ShowCreditsPacket::CreditsState credits_state{};
};

struct SetDefaultGameTypePacket {
    static constexpr int Id = 105;
    GameType default_game_type{};
};

enum class MultiplayerSettingsPacketType : int {
    EnableMultiplayer = 0,
    DisableMultiplayer = 1,
    RefreshJoincode = 2,
};

struct MultiplayerSettingsPacket {
    static constexpr int Id = 139;
    MultiplayerSettingsPacketType packet_type{};
};

struct UpdatePlayerGameTypePacket {
    static constexpr int Id = 151;
    GameType player_game_type{};
    ActorUniqueID target_player{};
    PlayerInputTick tick{};
};

enum class SimulationType : std::uint8_t {
    Game = 0,
    Editor = 1,
    Test = 2,
    Invalid = 3,
};

struct SimulationTypePacket {
    static constexpr int Id = 168;
    SimulationType sim_type{};
};

namespace base {

enum class WorldType : int {
    NonEditor = 0,
    EditorProject = 1,
    EditorTestLevel = 2,
};

struct GameRule {
    std::string name{};
    bool can_be_modified_by_player{};
    std::variant<std::monostate, bool, std::uint32_t, float> value{};
};

struct GameRulesChangedPacketData {
    std::vector<base::GameRule> rules{};
};

struct SyncedPlayerMovementSettings {
    ServerAuthMovementMode authority_mode{};
    std::int32_t rewind_history_size{};
    bool server_auth_block_breaking{};
};

}  // namespace base

namespace legacy {

namespace base {

struct GameRule {
    std::string name{};
    bool can_be_modified_by_player{};
    std::variant<std::monostate, bool, std::uint32_t, float> value{};
};

}  // namespace base

}  // namespace legacy

namespace base {

struct LevelSettings {
    std::uint64_t seed{};
    SpawnSettings spawn_settings{};
    GeneratorType generator{};
    GameType game_type{};
    bool is_hardcore{};
    Difficulty game_difficulty{};
    base::NetworkBlockPosition default_spawn{};
    bool achievements_disabled{};
    base::WorldType editor_world_type{};
    bool is_created_in_editor{};
    bool is_exported_from_editor{};
    std::int32_t time{};
    EducationEditionOffer education_edition_offer{};
    bool education_features_enabled{};
    std::string education_product_id{};
    float rain_level{};
    float lightning_level{};
    bool confirmed_platform_locked_content{};
    bool multiplayer_game_intent{};
    bool lan_broadcast_intent{};
    GamePublishSetting xbl_broadcast_intent{};
    GamePublishSetting platform_broadcast_intent{};
    bool commands_enabled{};
    bool texture_packs_required{};
    std::vector<legacy::base::GameRule> game_rules{};
    std::vector<ExperimentToggle> experiments{};
    bool experiments_ever_toggled{};
    bool bonus_chest_enabled{};
    bool start_with_map_enabled{};
    PlayerPermissionLevel default_permissions{};
    std::int32_t server_chunk_tick_range{};
    bool has_locked_behavior_pack{};
    bool has_locked_resource_pack{};
    bool is_from_locked_template{};
    bool use_msa_gamertags_only{};
    bool is_from_world_template{};
    bool is_world_template_option_locked{};
    bool spawn_v1_villagers{};
    bool persona_disabled{};
    bool custom_skins_disabled{};
    bool emote_chat_muted{};
    std::string base_game_version{};
    std::int32_t limited_world_width{};
    std::int32_t limited_world_depth{};
    NetherWorldType nether_type{};
    EduSharedUriResource edu_shared_uri_resource{};
    std::optional<bool> override_force_experimental_gameplay{};
    ChatRestrictionLevel chat_restriction_level{};
    bool disable_player_interactions{};
    std::string server_id{};
    std::string world_id{};
    std::string scenario_id{};
};

struct StartGameItemEntry {
    std::string name{};
    std::int16_t id{};
    bool is_component_based{};
};

struct StartGamePacket {
    static constexpr int Id = 11;
    ActorUniqueID entity_id{};
    ActorRuntimeID runtime_id{};
    GameType entity_game_type{};
    Vec3 pos{};
    Vec2 rot{};
    base::LevelSettings settings{};
    std::string level_id{};
    std::string level_name{};
    std::string template_content_identity{};
    bool is_trial{};
    base::SyncedPlayerMovementSettings movement_settings{};
    std::uint64_t level_current_time{};
    std::int32_t enchantment_seed{};
    std::vector<BlockEntry> block_properties{};
    std::vector<base::StartGameItemEntry> items{};
    std::string multiplayer_correlation_id{};
    bool enable_item_stack_net_manager{};
    std::string server_version{};
    CompoundTag player_property_data{};
    std::uint64_t server_block_type_registry_checksum{};
    UUID world_template_id{};
    bool server_enabled_client_side_generation{};
    bool block_network_ids_are_hashes{};
    NetworkPermissions network_permissions{};
};

struct GameRulesChangedPacket {
    static constexpr int Id = 72;
    base::GameRulesChangedPacketData rule_data{};
};

}  // namespace base

namespace v748 {

using WorldType = base::WorldType;

using GameRule = base::GameRule;

using GameRulesChangedPacketData = base::GameRulesChangedPacketData;

using SyncedPlayerMovementSettings = base::SyncedPlayerMovementSettings;

}  // namespace v748

namespace legacy {

namespace v748 {

using GameRule = base::GameRule;

}  // namespace v748

}  // namespace legacy

namespace v748 {

using LevelSettings = base::LevelSettings;

using StartGameItemEntry = base::StartGameItemEntry;

using StartGamePacket = base::StartGamePacket;

using GameRulesChangedPacket = base::GameRulesChangedPacket;

}  // namespace v748

namespace v766 {

using WorldType = base::WorldType;

using GameRule = base::GameRule;

using GameRulesChangedPacketData = base::GameRulesChangedPacketData;

using SyncedPlayerMovementSettings = base::SyncedPlayerMovementSettings;

}  // namespace v766

namespace legacy {

namespace v766 {

using GameRule = base::GameRule;

}  // namespace v766

}  // namespace legacy

namespace v766 {

using LevelSettings = base::LevelSettings;

using StartGameItemEntry = base::StartGameItemEntry;

using StartGamePacket = base::StartGamePacket;

using GameRulesChangedPacket = base::GameRulesChangedPacket;

}  // namespace v766

namespace v776 {

using WorldType = base::WorldType;

using GameRule = base::GameRule;

using GameRulesChangedPacketData = base::GameRulesChangedPacketData;

using SyncedPlayerMovementSettings = base::SyncedPlayerMovementSettings;

}  // namespace v776

namespace legacy {

namespace v776 {

using GameRule = base::GameRule;

}  // namespace v776

}  // namespace legacy

namespace v776 {

using LevelSettings = base::LevelSettings;

struct StartGamePacket {
    static constexpr int Id = 11;
    ActorUniqueID entity_id{};
    ActorRuntimeID runtime_id{};
    GameType entity_game_type{};
    Vec3 pos{};
    Vec2 rot{};
    base::LevelSettings settings{};
    std::string level_id{};
    std::string level_name{};
    std::string template_content_identity{};
    bool is_trial{};
    base::SyncedPlayerMovementSettings movement_settings{};
    std::uint64_t level_current_time{};
    std::int32_t enchantment_seed{};
    std::vector<BlockEntry> block_properties{};
    std::string multiplayer_correlation_id{};
    bool enable_item_stack_net_manager{};
    std::string server_version{};
    CompoundTag player_property_data{};
    std::uint64_t server_block_type_registry_checksum{};
    UUID world_template_id{};
    bool server_enabled_client_side_generation{};
    bool block_network_ids_are_hashes{};
    NetworkPermissions network_permissions{};
};

using GameRulesChangedPacket = base::GameRulesChangedPacket;

}  // namespace v776

namespace v786 {

using WorldType = base::WorldType;

using GameRule = base::GameRule;

using GameRulesChangedPacketData = base::GameRulesChangedPacketData;

using SyncedPlayerMovementSettings = base::SyncedPlayerMovementSettings;

}  // namespace v786

namespace legacy {

namespace v786 {

using GameRule = base::GameRule;

}  // namespace v786

}  // namespace legacy

namespace v786 {

using LevelSettings = base::LevelSettings;

using StartGamePacket = v776::StartGamePacket;

using GameRulesChangedPacket = base::GameRulesChangedPacket;

}  // namespace v786

namespace v800 {

enum class WorldType : int {
    NonEditor = 0,
    EditorProject = 1,
    EditorTestLevel = 2,
    EditorRealmsUpload = 3,
};

using GameRule = base::GameRule;

using GameRulesChangedPacketData = base::GameRulesChangedPacketData;

using SyncedPlayerMovementSettings = base::SyncedPlayerMovementSettings;

}  // namespace v800

namespace legacy {

namespace v800 {

using GameRule = base::GameRule;

}  // namespace v800

}  // namespace legacy

namespace v800 {

struct LevelSettings {
    std::uint64_t seed{};
    SpawnSettings spawn_settings{};
    GeneratorType generator{};
    GameType game_type{};
    bool is_hardcore{};
    Difficulty game_difficulty{};
    base::NetworkBlockPosition default_spawn{};
    bool achievements_disabled{};
    v800::WorldType editor_world_type{};
    bool is_created_in_editor{};
    bool is_exported_from_editor{};
    std::int32_t time{};
    EducationEditionOffer education_edition_offer{};
    bool education_features_enabled{};
    std::string education_product_id{};
    float rain_level{};
    float lightning_level{};
    bool confirmed_platform_locked_content{};
    bool multiplayer_game_intent{};
    bool lan_broadcast_intent{};
    GamePublishSetting xbl_broadcast_intent{};
    GamePublishSetting platform_broadcast_intent{};
    bool commands_enabled{};
    bool texture_packs_required{};
    std::vector<legacy::base::GameRule> game_rules{};
    std::vector<ExperimentToggle> experiments{};
    bool experiments_ever_toggled{};
    bool bonus_chest_enabled{};
    bool start_with_map_enabled{};
    PlayerPermissionLevel default_permissions{};
    std::int32_t server_chunk_tick_range{};
    bool has_locked_behavior_pack{};
    bool has_locked_resource_pack{};
    bool is_from_locked_template{};
    bool use_msa_gamertags_only{};
    bool is_from_world_template{};
    bool is_world_template_option_locked{};
    bool spawn_v1_villagers{};
    bool persona_disabled{};
    bool custom_skins_disabled{};
    bool emote_chat_muted{};
    std::string base_game_version{};
    std::int32_t limited_world_width{};
    std::int32_t limited_world_depth{};
    NetherWorldType nether_type{};
    EduSharedUriResource edu_shared_uri_resource{};
    std::optional<bool> override_force_experimental_gameplay{};
    ChatRestrictionLevel chat_restriction_level{};
    bool disable_player_interactions{};
    std::string server_id{};
    std::string world_id{};
    std::string scenario_id{};
};

struct StartGamePacket {
    static constexpr int Id = 11;
    ActorUniqueID entity_id{};
    ActorRuntimeID runtime_id{};
    GameType entity_game_type{};
    Vec3 pos{};
    Vec2 rot{};
    v800::LevelSettings settings{};
    std::string level_id{};
    std::string level_name{};
    std::string template_content_identity{};
    bool is_trial{};
    base::SyncedPlayerMovementSettings movement_settings{};
    std::uint64_t level_current_time{};
    std::int32_t enchantment_seed{};
    std::vector<BlockEntry> block_properties{};
    std::string multiplayer_correlation_id{};
    bool enable_item_stack_net_manager{};
    std::string server_version{};
    CompoundTag player_property_data{};
    std::uint64_t server_block_type_registry_checksum{};
    UUID world_template_id{};
    bool server_enabled_client_side_generation{};
    bool block_network_ids_are_hashes{};
    NetworkPermissions network_permissions{};
};

using GameRulesChangedPacket = base::GameRulesChangedPacket;

}  // namespace v800

namespace v818 {

using WorldType = v800::WorldType;

using GameRule = base::GameRule;

using GameRulesChangedPacketData = base::GameRulesChangedPacketData;

struct SyncedPlayerMovementSettings {
    std::int32_t rewind_history_size{};
    bool server_auth_block_breaking{};
};

}  // namespace v818

namespace legacy {

namespace v818 {

using GameRule = base::GameRule;

}  // namespace v818

}  // namespace legacy

namespace v818 {

struct LevelSettings {
    std::uint64_t seed{};
    SpawnSettings spawn_settings{};
    GeneratorType generator{};
    GameType game_type{};
    bool is_hardcore{};
    Difficulty game_difficulty{};
    base::NetworkBlockPosition default_spawn{};
    bool achievements_disabled{};
    v800::WorldType editor_world_type{};
    bool is_created_in_editor{};
    bool is_exported_from_editor{};
    std::int32_t time{};
    EducationEditionOffer education_edition_offer{};
    bool education_features_enabled{};
    std::string education_product_id{};
    float rain_level{};
    float lightning_level{};
    bool confirmed_platform_locked_content{};
    bool multiplayer_game_intent{};
    bool lan_broadcast_intent{};
    GamePublishSetting xbl_broadcast_intent{};
    GamePublishSetting platform_broadcast_intent{};
    bool commands_enabled{};
    bool texture_packs_required{};
    std::vector<legacy::base::GameRule> game_rules{};
    std::vector<ExperimentToggle> experiments{};
    bool experiments_ever_toggled{};
    bool bonus_chest_enabled{};
    bool start_with_map_enabled{};
    PlayerPermissionLevel default_permissions{};
    std::int32_t server_chunk_tick_range{};
    bool has_locked_behavior_pack{};
    bool has_locked_resource_pack{};
    bool is_from_locked_template{};
    bool use_msa_gamertags_only{};
    bool is_from_world_template{};
    bool is_world_template_option_locked{};
    bool spawn_v1_villagers{};
    bool persona_disabled{};
    bool custom_skins_disabled{};
    bool emote_chat_muted{};
    std::string base_game_version{};
    std::int32_t limited_world_width{};
    std::int32_t limited_world_depth{};
    NetherWorldType nether_type{};
    EduSharedUriResource edu_shared_uri_resource{};
    std::optional<bool> override_force_experimental_gameplay{};
    ChatRestrictionLevel chat_restriction_level{};
    bool disable_player_interactions{};
    std::string server_id{};
    std::string world_id{};
    std::string scenario_id{};
    std::string owner_id{};
};

struct StartGamePacket {
    static constexpr int Id = 11;
    ActorUniqueID entity_id{};
    ActorRuntimeID runtime_id{};
    GameType entity_game_type{};
    Vec3 pos{};
    Vec2 rot{};
    v818::LevelSettings settings{};
    std::string level_id{};
    std::string level_name{};
    std::string template_content_identity{};
    bool is_trial{};
    v818::SyncedPlayerMovementSettings movement_settings{};
    std::uint64_t level_current_time{};
    std::int32_t enchantment_seed{};
    std::vector<BlockEntry> block_properties{};
    std::string multiplayer_correlation_id{};
    bool enable_item_stack_net_manager{};
    std::string server_version{};
    CompoundTag player_property_data{};
    std::uint64_t server_block_type_registry_checksum{};
    UUID world_template_id{};
    bool server_enabled_client_side_generation{};
    bool block_network_ids_are_hashes{};
    NetworkPermissions network_permissions{};
};

using GameRulesChangedPacket = base::GameRulesChangedPacket;

}  // namespace v818

namespace v827 {

using WorldType = v800::WorldType;

using GameRule = base::GameRule;

using GameRulesChangedPacketData = base::GameRulesChangedPacketData;

using SyncedPlayerMovementSettings = v818::SyncedPlayerMovementSettings;

}  // namespace v827

namespace legacy {

namespace v827 {

using GameRule = base::GameRule;

}  // namespace v827

}  // namespace legacy

namespace v827 {

using LevelSettings = v818::LevelSettings;

struct StartGamePacket {
    static constexpr int Id = 11;
    ActorUniqueID entity_id{};
    ActorRuntimeID runtime_id{};
    GameType entity_game_type{};
    Vec3 pos{};
    Vec2 rot{};
    v818::LevelSettings settings{};
    std::string level_id{};
    std::string level_name{};
    std::string template_content_identity{};
    bool is_trial{};
    v818::SyncedPlayerMovementSettings movement_settings{};
    std::uint64_t level_current_time{};
    std::int32_t enchantment_seed{};
    std::vector<BlockEntry> block_properties{};
    std::string multiplayer_correlation_id{};
    bool enable_item_stack_net_manager{};
    std::string server_version{};
    CompoundTag player_property_data{};
    std::uint64_t server_block_type_registry_checksum{};
    UUID world_template_id{};
    bool server_enabled_client_side_generation{};
    bool block_network_ids_are_hashes{};
    bool tick_death_systems_enabled{};
    NetworkPermissions network_permissions{};
};

using GameRulesChangedPacket = base::GameRulesChangedPacket;

}  // namespace v827

namespace v844 {

using WorldType = v800::WorldType;

struct GameRule {
    std::string name{};
    bool can_be_modified_by_player{};
    std::variant<std::monostate, bool, std::int32_t, float> value{};
};

struct GameRulesChangedPacketData {
    std::vector<v844::GameRule> rules{};
};

using SyncedPlayerMovementSettings = v818::SyncedPlayerMovementSettings;

}  // namespace v844

namespace legacy {

namespace v844 {

using GameRule = base::GameRule;

}  // namespace v844

}  // namespace legacy

namespace v844 {

struct LevelSettings {
    std::uint64_t seed{};
    SpawnSettings spawn_settings{};
    GeneratorType generator{};
    GameType game_type{};
    bool is_hardcore{};
    Difficulty game_difficulty{};
    base::NetworkBlockPosition default_spawn{};
    bool achievements_disabled{};
    v800::WorldType editor_world_type{};
    bool is_created_in_editor{};
    bool is_exported_from_editor{};
    std::int32_t time{};
    EducationEditionOffer education_edition_offer{};
    bool education_features_enabled{};
    std::string education_product_id{};
    float rain_level{};
    float lightning_level{};
    bool confirmed_platform_locked_content{};
    bool multiplayer_game_intent{};
    bool lan_broadcast_intent{};
    GamePublishSetting xbl_broadcast_intent{};
    GamePublishSetting platform_broadcast_intent{};
    bool commands_enabled{};
    bool texture_packs_required{};
    std::vector<legacy::base::GameRule> game_rules{};
    std::vector<ExperimentToggle> experiments{};
    bool experiments_ever_toggled{};
    bool bonus_chest_enabled{};
    bool start_with_map_enabled{};
    PlayerPermissionLevel default_permissions{};
    std::int32_t server_chunk_tick_range{};
    bool has_locked_behavior_pack{};
    bool has_locked_resource_pack{};
    bool is_from_locked_template{};
    bool use_msa_gamertags_only{};
    bool is_from_world_template{};
    bool is_world_template_option_locked{};
    bool spawn_v1_villagers{};
    bool persona_disabled{};
    bool custom_skins_disabled{};
    bool emote_chat_muted{};
    std::string base_game_version{};
    std::int32_t limited_world_width{};
    std::int32_t limited_world_depth{};
    NetherWorldType nether_type{};
    EduSharedUriResource edu_shared_uri_resource{};
    std::optional<bool> override_force_experimental_gameplay{};
    ChatRestrictionLevel chat_restriction_level{};
    bool disable_player_interactions{};
    std::string server_id{};
    std::string world_id{};
    std::string scenario_id{};
    std::string owner_id{};
};

struct StartGamePacket {
    static constexpr int Id = 11;
    ActorUniqueID entity_id{};
    ActorRuntimeID runtime_id{};
    GameType entity_game_type{};
    Vec3 pos{};
    Vec2 rot{};
    v844::LevelSettings settings{};
    std::string level_id{};
    std::string level_name{};
    std::string template_content_identity{};
    bool is_trial{};
    v818::SyncedPlayerMovementSettings movement_settings{};
    std::uint64_t level_current_time{};
    std::int32_t enchantment_seed{};
    std::vector<BlockEntry> block_properties{};
    std::string multiplayer_correlation_id{};
    bool enable_item_stack_net_manager{};
    std::string server_version{};
    CompoundTag player_property_data{};
    std::uint64_t server_block_type_registry_checksum{};
    UUID world_template_id{};
    bool server_enabled_client_side_generation{};
    bool block_network_ids_are_hashes{};
    bool tick_death_systems_enabled{};
    NetworkPermissions network_permissions{};
};

struct GameRulesChangedPacket {
    static constexpr int Id = 72;
    v844::GameRulesChangedPacketData rule_data{};
};

}  // namespace v844

namespace v859 {

using WorldType = v800::WorldType;

using GameRule = v844::GameRule;

using GameRulesChangedPacketData = v844::GameRulesChangedPacketData;

using SyncedPlayerMovementSettings = v818::SyncedPlayerMovementSettings;

}  // namespace v859

namespace legacy {

namespace v859 {

using GameRule = base::GameRule;

}  // namespace v859

}  // namespace legacy

namespace v859 {

using LevelSettings = v844::LevelSettings;

using StartGamePacket = v844::StartGamePacket;

using GameRulesChangedPacket = v844::GameRulesChangedPacket;

}  // namespace v859

namespace v898 {

using WorldType = v800::WorldType;

using GameRule = v844::GameRule;

using GameRulesChangedPacketData = v844::GameRulesChangedPacketData;

using SyncedPlayerMovementSettings = v818::SyncedPlayerMovementSettings;

}  // namespace v898

namespace legacy {

namespace v898 {

using GameRule = base::GameRule;

}  // namespace v898

}  // namespace legacy

namespace v898 {

using LevelSettings = v844::LevelSettings;

struct StartGamePacket {
    static constexpr int Id = 11;
    ActorUniqueID entity_id{};
    ActorRuntimeID runtime_id{};
    GameType entity_game_type{};
    Vec3 pos{};
    Vec2 rot{};
    v844::LevelSettings settings{};
    std::string level_id{};
    std::string level_name{};
    std::string template_content_identity{};
    bool is_trial{};
    v818::SyncedPlayerMovementSettings movement_settings{};
    std::uint64_t level_current_time{};
    std::int32_t enchantment_seed{};
    std::vector<BlockEntry> block_properties{};
    std::string multiplayer_correlation_id{};
    bool enable_item_stack_net_manager{};
    std::string server_version{};
    CompoundTag player_property_data{};
    std::uint64_t server_block_type_registry_checksum{};
    UUID world_template_id{};
    bool server_enabled_client_side_generation{};
    bool block_network_ids_are_hashes{};
    NetworkPermissions network_permissions{};
};

using GameRulesChangedPacket = v844::GameRulesChangedPacket;

}  // namespace v898

namespace v924 {

using WorldType = v800::WorldType;

using GameRule = v844::GameRule;

using GameRulesChangedPacketData = v844::GameRulesChangedPacketData;

using SyncedPlayerMovementSettings = v818::SyncedPlayerMovementSettings;

}  // namespace v924

namespace legacy {

namespace v924 {

using GameRule = base::GameRule;

}  // namespace v924

}  // namespace legacy

namespace v924 {

struct LevelSettings {
    std::uint64_t seed{};
    SpawnSettings spawn_settings{};
    GeneratorType generator{};
    GameType game_type{};
    bool is_hardcore{};
    Difficulty game_difficulty{};
    base::NetworkBlockPosition default_spawn{};
    bool achievements_disabled{};
    v800::WorldType editor_world_type{};
    bool is_created_in_editor{};
    bool is_exported_from_editor{};
    std::int32_t time{};
    EducationEditionOffer education_edition_offer{};
    bool education_features_enabled{};
    std::string education_product_id{};
    float rain_level{};
    float lightning_level{};
    bool confirmed_platform_locked_content{};
    bool multiplayer_game_intent{};
    bool lan_broadcast_intent{};
    GamePublishSetting xbl_broadcast_intent{};
    GamePublishSetting platform_broadcast_intent{};
    bool commands_enabled{};
    bool texture_packs_required{};
    std::vector<legacy::base::GameRule> game_rules{};
    std::vector<ExperimentToggle> experiments{};
    bool experiments_ever_toggled{};
    bool bonus_chest_enabled{};
    bool start_with_map_enabled{};
    PlayerPermissionLevel default_permissions{};
    std::int32_t server_chunk_tick_range{};
    bool has_locked_behavior_pack{};
    bool has_locked_resource_pack{};
    bool is_from_locked_template{};
    bool use_msa_gamertags_only{};
    bool is_from_world_template{};
    bool is_world_template_option_locked{};
    bool spawn_v1_villagers{};
    bool persona_disabled{};
    bool custom_skins_disabled{};
    bool emote_chat_muted{};
    std::string base_game_version{};
    std::int32_t limited_world_width{};
    std::int32_t limited_world_depth{};
    NetherWorldType nether_type{};
    EduSharedUriResource edu_shared_uri_resource{};
    std::optional<bool> override_force_experimental_gameplay{};
    ChatRestrictionLevel chat_restriction_level{};
    bool disable_player_interactions{};
};

struct StartGamePacket {
    static constexpr int Id = 11;
    ActorUniqueID entity_id{};
    ActorRuntimeID runtime_id{};
    GameType entity_game_type{};
    Vec3 pos{};
    Vec2 rot{};
    v924::LevelSettings settings{};
    std::string level_id{};
    std::string level_name{};
    std::string template_content_identity{};
    bool is_trial{};
    v818::SyncedPlayerMovementSettings movement_settings{};
    std::uint64_t level_current_time{};
    std::int32_t enchantment_seed{};
    std::vector<BlockEntry> block_properties{};
    std::string multiplayer_correlation_id{};
    bool enable_item_stack_net_manager{};
    std::string server_version{};
    CompoundTag player_property_data{};
    std::uint64_t server_block_type_registry_checksum{};
    UUID world_template_id{};
    bool server_enabled_client_side_generation{};
    bool block_network_ids_are_hashes{};
    NetworkPermissions network_permissions{};
    std::optional<base::ServerConfigurationJoinInfo> server_configuration_join_info{};
    ServerTelemetryData server_telemetry_data{};
};

using GameRulesChangedPacket = v844::GameRulesChangedPacket;

}  // namespace v924

namespace v944 {

using WorldType = v800::WorldType;

using GameRule = v844::GameRule;

using GameRulesChangedPacketData = v844::GameRulesChangedPacketData;

using SyncedPlayerMovementSettings = v818::SyncedPlayerMovementSettings;

}  // namespace v944

namespace legacy {

namespace v944 {

using GameRule = base::GameRule;

}  // namespace v944

}  // namespace legacy

namespace v944 {

struct LevelSettings {
    std::uint64_t seed{};
    SpawnSettings spawn_settings{};
    GeneratorType generator{};
    GameType game_type{};
    bool is_hardcore{};
    Difficulty game_difficulty{};
    BlockPos default_spawn{};
    bool achievements_disabled{};
    v800::WorldType editor_world_type{};
    bool is_created_in_editor{};
    bool is_exported_from_editor{};
    std::int32_t time{};
    EducationEditionOffer education_edition_offer{};
    bool education_features_enabled{};
    std::string education_product_id{};
    float rain_level{};
    float lightning_level{};
    bool confirmed_platform_locked_content{};
    bool multiplayer_game_intent{};
    bool lan_broadcast_intent{};
    GamePublishSetting xbl_broadcast_intent{};
    GamePublishSetting platform_broadcast_intent{};
    bool commands_enabled{};
    bool texture_packs_required{};
    std::vector<legacy::base::GameRule> game_rules{};
    std::vector<ExperimentToggle> experiments{};
    bool experiments_ever_toggled{};
    bool bonus_chest_enabled{};
    bool start_with_map_enabled{};
    PlayerPermissionLevel default_permissions{};
    std::int32_t server_chunk_tick_range{};
    bool has_locked_behavior_pack{};
    bool has_locked_resource_pack{};
    bool is_from_locked_template{};
    bool use_msa_gamertags_only{};
    bool is_from_world_template{};
    bool is_world_template_option_locked{};
    bool spawn_v1_villagers{};
    bool persona_disabled{};
    bool custom_skins_disabled{};
    bool emote_chat_muted{};
    std::string base_game_version{};
    std::int32_t limited_world_width{};
    std::int32_t limited_world_depth{};
    NetherWorldType nether_type{};
    EduSharedUriResource edu_shared_uri_resource{};
    std::optional<bool> override_force_experimental_gameplay{};
    ChatRestrictionLevel chat_restriction_level{};
    bool disable_player_interactions{};
};

struct StartGamePacket {
    static constexpr int Id = 11;
    ActorUniqueID entity_id{};
    ActorRuntimeID runtime_id{};
    GameType entity_game_type{};
    Vec3 pos{};
    Vec2 rot{};
    v944::LevelSettings settings{};
    std::string level_id{};
    std::string level_name{};
    std::string template_content_identity{};
    bool is_trial{};
    v818::SyncedPlayerMovementSettings movement_settings{};
    std::uint64_t level_current_time{};
    std::int32_t enchantment_seed{};
    std::vector<BlockEntry> block_properties{};
    std::string multiplayer_correlation_id{};
    bool enable_item_stack_net_manager{};
    std::string server_version{};
    CompoundTag player_property_data{};
    std::uint64_t server_block_type_registry_checksum{};
    UUID world_template_id{};
    bool server_enabled_client_side_generation{};
    bool block_network_ids_are_hashes{};
    NetworkPermissions network_permissions{};
    std::optional<v944::ServerConfigurationJoinInfo> server_configuration_join_info{};
    ServerTelemetryData server_telemetry_data{};
};

using GameRulesChangedPacket = v844::GameRulesChangedPacket;

}  // namespace v944

namespace v975 {

using WorldType = v800::WorldType;

using GameRule = v844::GameRule;

using GameRulesChangedPacketData = v844::GameRulesChangedPacketData;

using SyncedPlayerMovementSettings = v818::SyncedPlayerMovementSettings;

}  // namespace v975

namespace legacy {

namespace v975 {

using GameRule = base::GameRule;

}  // namespace v975

}  // namespace legacy

namespace v975 {

using LevelSettings = v944::LevelSettings;

using StartGamePacket = v944::StartGamePacket;

using GameRulesChangedPacket = v844::GameRulesChangedPacket;

}  // namespace v975

namespace v1001 {

using WorldType = v800::WorldType;

using GameRule = v844::GameRule;

using GameRulesChangedPacketData = v844::GameRulesChangedPacketData;

using SyncedPlayerMovementSettings = v818::SyncedPlayerMovementSettings;

}  // namespace v1001

namespace legacy {

namespace v1001 {

using GameRule = base::GameRule;

}  // namespace v1001

}  // namespace legacy

namespace v1001 {

struct LevelSettings {
    std::uint64_t seed{};
    SpawnSettings spawn_settings{};
    GeneratorType generator{};
    GameType game_type{};
    bool is_hardcore{};
    Difficulty game_difficulty{};
    BlockPos default_spawn{};
    bool achievements_disabled{};
    v800::WorldType editor_world_type{};
    bool is_created_in_editor{};
    bool is_exported_from_editor{};
    std::int32_t time{};
    EducationEditionOffer education_edition_offer{};
    bool education_features_enabled{};
    std::string education_product_id{};
    float rain_level{};
    float lightning_level{};
    bool confirmed_platform_locked_content{};
    bool multiplayer_game_intent{};
    bool lan_broadcast_intent{};
    GamePublishSetting xbl_broadcast_intent{};
    GamePublishSetting platform_broadcast_intent{};
    bool commands_enabled{};
    bool texture_packs_required{};
    std::vector<legacy::base::GameRule> game_rules{};
    std::vector<ExperimentToggle> experiments{};
    bool experiments_ever_toggled{};
    bool bonus_chest_enabled{};
    bool start_with_map_enabled{};
    PlayerPermissionLevel default_permissions{};
    std::int32_t server_chunk_tick_range{};
    bool has_locked_behavior_pack{};
    bool has_locked_resource_pack{};
    bool is_from_locked_template{};
    bool use_msa_gamertags_only{};
    bool is_from_world_template{};
    bool is_world_template_option_locked{};
    bool spawn_v1_villagers{};
    bool persona_disabled{};
    bool custom_skins_disabled{};
    bool emote_chat_muted{};
    std::string base_game_version{};
    std::int32_t limited_world_width{};
    std::int32_t limited_world_depth{};
    NetherWorldType nether_type{};
    EduSharedUriResource edu_shared_uri_resource{};
    std::optional<bool> override_force_experimental_gameplay{};
    ChatRestrictionLevel chat_restriction_level{};
    bool disable_player_interactions{};
    ServerEditorConnectionPolicy server_editor_connection_policy{};
    bool allow_anonymous_block_drops_in_editor_worlds{};
};

struct StartGamePacket {
    static constexpr int Id = 11;
    ActorUniqueID entity_id{};
    ActorRuntimeID runtime_id{};
    GameType entity_game_type{};
    Vec3 pos{};
    Vec2 rot{};
    v1001::LevelSettings settings{};
    std::string level_id{};
    std::string level_name{};
    std::string template_content_identity{};
    bool is_trial{};
    v818::SyncedPlayerMovementSettings movement_settings{};
    std::uint64_t level_current_time{};
    std::int32_t enchantment_seed{};
    std::vector<BlockEntry> block_properties{};
    std::string multiplayer_correlation_id{};
    bool enable_item_stack_net_manager{};
    std::string server_version{};
    CompoundTag player_property_data{};
    std::uint64_t server_block_type_registry_checksum{};
    UUID world_template_id{};
    bool server_enabled_client_side_generation{};
    bool block_network_ids_are_hashes{};
    NetworkPermissions network_permissions{};
    bool is_logging_chat{};
    std::optional<v1001::ServerConfigurationJoinInfo> server_configuration_join_info{};
    ServerTelemetryData server_telemetry_data{};
};

using GameRulesChangedPacket = v844::GameRulesChangedPacket;

}  // namespace v1001

namespace v2168 {

using WorldType = v800::WorldType;

using GameRule = v844::GameRule;

using GameRulesChangedPacketData = v844::GameRulesChangedPacketData;

using SyncedPlayerMovementSettings = v818::SyncedPlayerMovementSettings;

struct ServerBlockProperty {
    std::string name{};
    CompoundTag tag{};
};

struct LevelSettings {
    std::uint64_t seed{};
    SpawnSettings spawn_settings{};
    GeneratorType generator{};
    GameType game_type{};
    bool is_hardcore{};
    Difficulty game_difficulty{};
    BlockPos default_spawn{};
    bool achievements_disabled{};
    v800::WorldType editor_world_type{};
    bool is_created_in_editor{};
    bool is_exported_from_editor{};
    std::int32_t time{};
    EducationEditionOffer education_edition_offer{};
    bool education_features_enabled{};
    std::string education_product_id{};
    float rain_level{};
    float lightning_level{};
    bool confirmed_platform_locked_content{};
    bool multiplayer_game_intent{};
    bool lan_broadcast_intent{};
    GamePublishSetting xbl_broadcast_intent{};
    GamePublishSetting platform_broadcast_intent{};
    bool commands_enabled{};
    bool texture_packs_required{};
    v844::GameRulesChangedPacketData rule_data{};
    Experiments experiments{};
    bool bonus_chest_enabled{};
    bool start_with_map_enabled{};
    PlayerPermissionLevel default_permissions{};
    std::int32_t server_chunk_tick_range{};
    bool has_locked_behavior_pack{};
    bool has_locked_resource_pack{};
    bool is_from_locked_template{};
    bool use_msa_gamertags_only{};
    bool is_from_world_template{};
    bool is_world_template_option_locked{};
    bool spawn_v1_villagers{};
    bool persona_disabled{};
    bool custom_skins_disabled{};
    bool emote_chat_muted{};
    std::string base_game_version{};
    std::int32_t limited_world_width{};
    std::int32_t limited_world_depth{};
    NetherWorldType nether_type{};
    EduSharedUriResource edu_shared_uri_resource{};
    std::optional<bool> override_force_experimental_gameplay{};
    ChatRestrictionLevel chat_restriction_level{};
    bool disable_player_interactions{};
    ServerEditorConnectionPolicy server_editor_connection_policy{};
    bool allow_anonymous_block_drops_in_editor_worlds{};
};

struct StartGamePacket {
    static constexpr int Id = 11;
    ActorUniqueID entity_id{};
    ActorRuntimeID runtime_id{};
    GameType entity_game_type{};
    Vec3 pos{};
    Vec2 rot{};
    v2168::LevelSettings settings{};
    std::string level_id{};
    std::string level_name{};
    std::string template_content_identity{};
    bool is_trial{};
    v818::SyncedPlayerMovementSettings movement_settings{};
    std::uint64_t level_current_time{};
    std::int32_t enchantment_seed{};
    std::vector<v2168::ServerBlockProperty> block_properties{};
    std::string multiplayer_correlation_id{};
    bool enable_item_stack_net_manager{};
    std::string server_version{};
    CompoundTag player_property_data{};
    std::uint64_t server_block_type_registry_checksum{};
    UUID world_template_id{};
    bool server_enabled_client_side_generation{};
    bool block_network_ids_are_hashes{};
    NetworkPermissions network_permissions{};
    std::optional<v2168::ServerConfigurationJoinInfo> server_configuration_join_info{};
    ServerTelemetryData server_telemetry_data{};
};

using GameRulesChangedPacket = v844::GameRulesChangedPacket;

}  // namespace v2168

namespace v2193 {

using WorldType = v800::WorldType;

using GameRule = v844::GameRule;

using GameRulesChangedPacketData = v844::GameRulesChangedPacketData;

using SyncedPlayerMovementSettings = v818::SyncedPlayerMovementSettings;

using ServerBlockProperty = v2168::ServerBlockProperty;

using LevelSettings = v2168::LevelSettings;

using StartGamePacket = v2168::StartGamePacket;

using GameRulesChangedPacket = v844::GameRulesChangedPacket;

}  // namespace v2193

namespace v2225 {

using WorldType = v800::WorldType;

using GameRule = v844::GameRule;

using GameRulesChangedPacketData = v844::GameRulesChangedPacketData;

using SyncedPlayerMovementSettings = v818::SyncedPlayerMovementSettings;

using ServerBlockProperty = v2168::ServerBlockProperty;

struct LevelSettings {
    std::uint64_t seed{};
    SpawnSettings spawn_settings{};
    GeneratorType generator{};
    GameType game_type{};
    bool is_hardcore{};
    Difficulty game_difficulty{};
    BlockPos default_spawn{};
    bool achievements_disabled{};
    v800::WorldType editor_world_type{};
    bool is_created_in_editor{};
    bool is_exported_from_editor{};
    EditorLevelMigrationVersion editor_level_migration_version{};
    std::int32_t time{};
    EducationEditionOffer education_edition_offer{};
    bool education_features_enabled{};
    std::string education_product_id{};
    float rain_level{};
    float lightning_level{};
    bool confirmed_platform_locked_content{};
    bool multiplayer_game_intent{};
    bool lan_broadcast_intent{};
    GamePublishSetting xbl_broadcast_intent{};
    GamePublishSetting platform_broadcast_intent{};
    bool commands_enabled{};
    bool texture_packs_required{};
    v844::GameRulesChangedPacketData rule_data{};
    Experiments experiments{};
    bool bonus_chest_enabled{};
    bool start_with_map_enabled{};
    PlayerPermissionLevel default_permissions{};
    std::int32_t server_chunk_tick_range{};
    bool has_locked_behavior_pack{};
    bool has_locked_resource_pack{};
    bool is_from_locked_template{};
    bool use_msa_gamertags_only{};
    bool is_from_world_template{};
    bool is_world_template_option_locked{};
    bool spawn_v1_villagers{};
    bool persona_disabled{};
    bool custom_skins_disabled{};
    bool emote_chat_muted{};
    std::string base_game_version{};
    std::int32_t limited_world_width{};
    std::int32_t limited_world_depth{};
    NetherWorldType nether_type{};
    EduSharedUriResource edu_shared_uri_resource{};
    std::optional<bool> override_force_experimental_gameplay{};
    ChatRestrictionLevel chat_restriction_level{};
    bool disable_player_interactions{};
    ServerEditorConnectionPolicy server_editor_connection_policy{};
    bool allow_anonymous_block_drops_in_editor_worlds{};
};

struct StartGamePacket {
    static constexpr int Id = 11;
    ActorUniqueID entity_id{};
    ActorRuntimeID runtime_id{};
    GameType entity_game_type{};
    Vec3 pos{};
    Vec2 rot{};
    v2225::LevelSettings settings{};
    std::string level_id{};
    std::string level_name{};
    std::string template_content_identity{};
    bool is_trial{};
    v818::SyncedPlayerMovementSettings movement_settings{};
    std::uint64_t level_current_time{};
    std::int32_t enchantment_seed{};
    std::vector<v2168::ServerBlockProperty> block_properties{};
    std::string multiplayer_correlation_id{};
    bool enable_item_stack_net_manager{};
    std::string server_version{};
    CompoundTag player_property_data{};
    std::uint64_t server_block_type_registry_checksum{};
    UUID world_template_id{};
    bool server_enabled_client_side_generation{};
    bool block_network_ids_are_hashes{};
    NetworkPermissions network_permissions{};
    std::optional<v2168::ServerConfigurationJoinInfo> server_configuration_join_info{};
    ServerTelemetryData server_telemetry_data{};
};

using GameRulesChangedPacket = v844::GameRulesChangedPacket;

}  // namespace v2225

namespace detail {

template <int V>
struct WorldType_;

template <int V> requires (V < 800)
struct WorldType_<V> { using type = base::WorldType; };

template <int V> requires (V >= 800)
struct WorldType_<V> { using type = v800::WorldType; };

template <int V>
struct GameRule_;

template <int V> requires (V < 844)
struct GameRule_<V> { using type = base::GameRule; };

template <int V> requires (V >= 844)
struct GameRule_<V> { using type = v844::GameRule; };

template <int V>
struct GameRulesChangedPacketData_;

template <int V> requires (V < 844)
struct GameRulesChangedPacketData_<V> { using type = base::GameRulesChangedPacketData; };

template <int V> requires (V >= 844)
struct GameRulesChangedPacketData_<V> { using type = v844::GameRulesChangedPacketData; };

template <int V>
struct SyncedPlayerMovementSettings_;

template <int V> requires (V < 818)
struct SyncedPlayerMovementSettings_<V> { using type = base::SyncedPlayerMovementSettings; };

template <int V> requires (V >= 818)
struct SyncedPlayerMovementSettings_<V> { using type = v818::SyncedPlayerMovementSettings; };

template <int V>
struct ServerBlockProperty_;

template <int V> requires (V >= 2168)
struct ServerBlockProperty_<V> { using type = v2168::ServerBlockProperty; };

template <int V>
struct LevelSettings_;

template <int V> requires (V < 800)
struct LevelSettings_<V> { using type = base::LevelSettings; };

template <int V> requires (V >= 800 && V < 818)
struct LevelSettings_<V> { using type = v800::LevelSettings; };

template <int V> requires (V >= 818 && V < 844)
struct LevelSettings_<V> { using type = v818::LevelSettings; };

template <int V> requires (V >= 844 && V < 924)
struct LevelSettings_<V> { using type = v844::LevelSettings; };

template <int V> requires (V >= 924 && V < 944)
struct LevelSettings_<V> { using type = v924::LevelSettings; };

template <int V> requires (V >= 944 && V < 1001)
struct LevelSettings_<V> { using type = v944::LevelSettings; };

template <int V> requires (V >= 1001 && V < 2168)
struct LevelSettings_<V> { using type = v1001::LevelSettings; };

template <int V> requires (V >= 2168 && V < 2225)
struct LevelSettings_<V> { using type = v2168::LevelSettings; };

template <int V> requires (V >= 2225)
struct LevelSettings_<V> { using type = v2225::LevelSettings; };

template <int V>
struct StartGameItemEntry_;

template <int V> requires (V < 776)
struct StartGameItemEntry_<V> { using type = base::StartGameItemEntry; };

template <int V>
struct StartGamePacket_;

template <int V> requires (V < 776)
struct StartGamePacket_<V> { using type = base::StartGamePacket; };

template <int V> requires (V >= 776 && V < 800)
struct StartGamePacket_<V> { using type = v776::StartGamePacket; };

template <int V> requires (V >= 800 && V < 818)
struct StartGamePacket_<V> { using type = v800::StartGamePacket; };

template <int V> requires (V >= 818 && V < 827)
struct StartGamePacket_<V> { using type = v818::StartGamePacket; };

template <int V> requires (V >= 827 && V < 844)
struct StartGamePacket_<V> { using type = v827::StartGamePacket; };

template <int V> requires (V >= 844 && V < 898)
struct StartGamePacket_<V> { using type = v844::StartGamePacket; };

template <int V> requires (V >= 898 && V < 924)
struct StartGamePacket_<V> { using type = v898::StartGamePacket; };

template <int V> requires (V >= 924 && V < 944)
struct StartGamePacket_<V> { using type = v924::StartGamePacket; };

template <int V> requires (V >= 944 && V < 1001)
struct StartGamePacket_<V> { using type = v944::StartGamePacket; };

template <int V> requires (V >= 1001 && V < 2168)
struct StartGamePacket_<V> { using type = v1001::StartGamePacket; };

template <int V> requires (V >= 2168 && V < 2225)
struct StartGamePacket_<V> { using type = v2168::StartGamePacket; };

template <int V> requires (V >= 2225)
struct StartGamePacket_<V> { using type = v2225::StartGamePacket; };

template <int V>
struct GameRulesChangedPacket_;

template <int V> requires (V < 844)
struct GameRulesChangedPacket_<V> { using type = base::GameRulesChangedPacket; };

template <int V> requires (V >= 844)
struct GameRulesChangedPacket_<V> { using type = v844::GameRulesChangedPacket; };

}  // namespace detail

template <int V> using WorldType_ = typename detail::WorldType_<V>::type;
template <int V> using GameRule_ = typename detail::GameRule_<V>::type;
template <int V> using GameRulesChangedPacketData_ = typename detail::GameRulesChangedPacketData_<V>::type;
template <int V> using SyncedPlayerMovementSettings_ = typename detail::SyncedPlayerMovementSettings_<V>::type;
template <int V> using ServerBlockProperty_ = typename detail::ServerBlockProperty_<V>::type;
template <int V> using LevelSettings_ = typename detail::LevelSettings_<V>::type;
template <int V> using StartGameItemEntry_ = typename detail::StartGameItemEntry_<V>::type;
template <int V> using StartGamePacket_ = typename detail::StartGamePacket_<V>::type;
template <int V> using GameRulesChangedPacket_ = typename detail::GameRulesChangedPacket_<V>::type;

namespace legacy {

namespace detail {

template <int V>
struct GameRule_;

template <int V> requires (V < 2168)
struct GameRule_<V> { using type = base::GameRule; };

}  // namespace detail

template <int V> using GameRule_ = typename detail::GameRule_<V>::type;

}  // namespace legacy

template <int V>
struct packet_of<V, 11> { using type = StartGamePacket_<V>; };

template <int V>
struct packet_of<V, 59> { using type = SetCommandsEnabledPacket; };

template <int V>
struct packet_of<V, 60> { using type = SetDifficultyPacket; };

template <int V>
struct packet_of<V, 62> { using type = SetPlayerGameTypePacket; };

template <int V>
struct packet_of<V, 72> { using type = GameRulesChangedPacket_<V>; };

template <int V>
struct packet_of<V, 75> { using type = ShowCreditsPacket; };

template <int V>
struct packet_of<V, 105> { using type = SetDefaultGameTypePacket; };

template <int V>
struct packet_of<V, 139> { using type = MultiplayerSettingsPacket; };

template <int V>
struct packet_of<V, 151> { using type = UpdatePlayerGameTypePacket; };

template <int V>
struct packet_of<V, 168> { using type = SimulationTypePacket; };

namespace detail {

template <>
inline constexpr std::array<GameType, 7> values_v<GameType>{{
    GameType::Undefined,
    GameType::Survival,
    GameType::Creative,
    GameType::Adventure,
    GameType::Default,
    GameType::Spectator,
    GameType::WorldDefault,
}};

template <>
inline constexpr std::array<std::string_view, 7> names_v<GameType>{{
    "undefined",
    "survival",
    "creative",
    "adventure",
    "default",
    "spectator",
    "worlddefault",
}};

template <>
inline constexpr std::string_view type_name_v<GameType>{"GameType"};

template <>
inline constexpr std::array<Difficulty, 6> values_v<Difficulty>{{
    Difficulty::Peaceful,
    Difficulty::Easy,
    Difficulty::Normal,
    Difficulty::Hard,
    Difficulty::Count,
    Difficulty::Unknown,
}};

template <>
inline constexpr std::array<std::string_view, 6> names_v<Difficulty>{{
    "peaceful",
    "easy",
    "normal",
    "hard",
    "count",
    "unknown",
}};

template <>
inline constexpr std::string_view type_name_v<Difficulty>{"Difficulty"};

template <>
inline constexpr std::array<GeneratorType, 7> values_v<GeneratorType>{{
    GeneratorType::Legacy,
    GeneratorType::Overworld,
    GeneratorType::Flat,
    GeneratorType::Nether,
    GeneratorType::TheEnd,
    GeneratorType::Void,
    GeneratorType::Undefined,
}};

template <>
inline constexpr std::array<std::string_view, 7> names_v<GeneratorType>{{
    "legacy",
    "overworld",
    "flat",
    "nether",
    "theend",
    "void",
    "undefined",
}};

template <>
inline constexpr std::string_view type_name_v<GeneratorType>{"GeneratorType"};

template <>
inline constexpr std::array<NetherWorldType, 2> values_v<NetherWorldType>{{
    NetherWorldType::Normal,
    NetherWorldType::Flat,
}};

template <>
inline constexpr std::array<std::string_view, 2> names_v<NetherWorldType>{{
    "normal",
    "flat",
}};

template <>
inline constexpr std::string_view type_name_v<NetherWorldType>{"NetherWorldType"};

template <>
inline constexpr std::array<SpawnBiomeType, 2> values_v<SpawnBiomeType>{{
    SpawnBiomeType::Default,
    SpawnBiomeType::UserDefined,
}};

template <>
inline constexpr std::array<std::string_view, 2> names_v<SpawnBiomeType>{{
    "default",
    "userdefined",
}};

template <>
inline constexpr std::string_view type_name_v<SpawnBiomeType>{"SpawnBiomeType"};

template <>
inline constexpr std::array<base::WorldType, 3> values_v<base::WorldType>{{
    base::WorldType::NonEditor,
    base::WorldType::EditorProject,
    base::WorldType::EditorTestLevel,
}};

template <>
inline constexpr std::array<std::string_view, 3> names_v<base::WorldType>{{
    "noneditor",
    "editorproject",
    "editortestlevel",
}};

template <>
inline constexpr std::string_view type_name_v<base::WorldType>{"WorldType"};

template <>
inline constexpr std::array<v800::WorldType, 4> values_v<v800::WorldType>{{
    v800::WorldType::NonEditor,
    v800::WorldType::EditorProject,
    v800::WorldType::EditorTestLevel,
    v800::WorldType::EditorRealmsUpload,
}};

template <>
inline constexpr std::array<std::string_view, 4> names_v<v800::WorldType>{{
    "noneditor",
    "editorproject",
    "editortestlevel",
    "editorrealmsupload",
}};

template <>
inline constexpr std::string_view type_name_v<v800::WorldType>{"WorldType"};

template <>
inline constexpr std::array<EditorLevelMigrationVersion, 2> values_v<EditorLevelMigrationVersion>{{
    EditorLevelMigrationVersion::Legacy,
    EditorLevelMigrationVersion::EditorAchievements,
}};

template <>
inline constexpr std::array<std::string_view, 2> names_v<EditorLevelMigrationVersion>{{
    "legacy",
    "editorachievements",
}};

template <>
inline constexpr std::string_view type_name_v<EditorLevelMigrationVersion>{"EditorLevelMigrationVersion"};

template <>
inline constexpr std::array<EducationEditionOffer, 3> values_v<EducationEditionOffer>{{
    EducationEditionOffer::None,
    EducationEditionOffer::RestOfWorld,
    EducationEditionOffer::ChinaDeprecated,
}};

template <>
inline constexpr std::array<std::string_view, 3> names_v<EducationEditionOffer>{{
    "none",
    "restofworld",
    "chinadeprecated",
}};

template <>
inline constexpr std::string_view type_name_v<EducationEditionOffer>{"EducationEditionOffer"};

template <>
inline constexpr std::array<ChatRestrictionLevel, 3> values_v<ChatRestrictionLevel>{{
    ChatRestrictionLevel::None,
    ChatRestrictionLevel::Dropped,
    ChatRestrictionLevel::Disabled,
}};

template <>
inline constexpr std::array<std::string_view, 3> names_v<ChatRestrictionLevel>{{
    "none",
    "dropped",
    "disabled",
}};

template <>
inline constexpr std::string_view type_name_v<ChatRestrictionLevel>{"ChatRestrictionLevel"};

template <>
inline constexpr std::array<ShowCreditsPacket::CreditsState, 2> values_v<ShowCreditsPacket::CreditsState>{{
    ShowCreditsPacket::CreditsState::Start,
    ShowCreditsPacket::CreditsState::Finished,
}};

template <>
inline constexpr std::array<std::string_view, 2> names_v<ShowCreditsPacket::CreditsState>{{
    "start",
    "finished",
}};

template <>
inline constexpr std::string_view type_name_v<ShowCreditsPacket::CreditsState>{"ShowCreditsPacket::CreditsState"};

template <>
inline constexpr std::array<MultiplayerSettingsPacketType, 3> values_v<MultiplayerSettingsPacketType>{{
    MultiplayerSettingsPacketType::EnableMultiplayer,
    MultiplayerSettingsPacketType::DisableMultiplayer,
    MultiplayerSettingsPacketType::RefreshJoincode,
}};

template <>
inline constexpr std::array<std::string_view, 3> names_v<MultiplayerSettingsPacketType>{{
    "enablemultiplayer",
    "disablemultiplayer",
    "refreshjoincode",
}};

template <>
inline constexpr std::string_view type_name_v<MultiplayerSettingsPacketType>{"MultiplayerSettingsPacketType"};

template <>
inline constexpr std::array<SimulationType, 4> values_v<SimulationType>{{
    SimulationType::Game,
    SimulationType::Editor,
    SimulationType::Test,
    SimulationType::Invalid,
}};

template <>
inline constexpr std::array<std::string_view, 4> names_v<SimulationType>{{
    "game",
    "editor",
    "test",
    "invalid",
}};

template <>
inline constexpr std::string_view type_name_v<SimulationType>{"SimulationType"};

}  // namespace detail

namespace detail {

template <>
inline constexpr bool is_reflected_struct_v<SpawnSettings> = true;

template <>
inline constexpr std::string_view struct_name_v<SpawnSettings>{"SpawnSettings"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<SpawnSettings>{{
    "type",
    "user_defined_biome_name",
    "dimension",
}};

template <>
struct field_accessor<SpawnSettings> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.type;
        }
        else if constexpr (I == 1) {
            return value.user_defined_biome_name;
        }
        else {
            return value.dimension;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::GameRule> = true;

template <>
inline constexpr std::string_view struct_name_v<base::GameRule>{"GameRule"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<base::GameRule>{{
    "name",
    "can_be_modified_by_player",
    "value",
}};

template <>
struct field_accessor<base::GameRule> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.name;
        }
        else if constexpr (I == 1) {
            return value.can_be_modified_by_player;
        }
        else {
            return value.value;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v844::GameRule> = true;

template <>
inline constexpr std::string_view struct_name_v<v844::GameRule>{"GameRule"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v844::GameRule>{{
    "name",
    "can_be_modified_by_player",
    "value",
}};

template <>
struct field_accessor<v844::GameRule> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.name;
        }
        else if constexpr (I == 1) {
            return value.can_be_modified_by_player;
        }
        else {
            return value.value;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::GameRulesChangedPacketData> = true;

template <>
inline constexpr std::string_view struct_name_v<base::GameRulesChangedPacketData>{"GameRulesChangedPacketData"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::GameRulesChangedPacketData>{{
    "rules",
}};

template <>
struct field_accessor<base::GameRulesChangedPacketData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.rules;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v844::GameRulesChangedPacketData> = true;

template <>
inline constexpr std::string_view struct_name_v<v844::GameRulesChangedPacketData>{"GameRulesChangedPacketData"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v844::GameRulesChangedPacketData>{{
    "rules",
}};

template <>
struct field_accessor<v844::GameRulesChangedPacketData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.rules;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<ExperimentToggle> = true;

template <>
inline constexpr std::string_view struct_name_v<ExperimentToggle>{"ExperimentToggle"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<ExperimentToggle>{{
    "name",
    "enabled",
}};

template <>
struct field_accessor<ExperimentToggle> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.name;
        }
        else {
            return value.enabled;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<Experiments> = true;

template <>
inline constexpr std::string_view struct_name_v<Experiments>{"Experiments"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<Experiments>{{
    "toggles",
    "experiments_ever_toggled",
}};

template <>
struct field_accessor<Experiments> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.toggles;
        }
        else {
            return value.experiments_ever_toggled;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::SyncedPlayerMovementSettings> = true;

template <>
inline constexpr std::string_view struct_name_v<base::SyncedPlayerMovementSettings>{"SyncedPlayerMovementSettings"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<base::SyncedPlayerMovementSettings>{{
    "authority_mode",
    "rewind_history_size",
    "server_auth_block_breaking",
}};

template <>
struct field_accessor<base::SyncedPlayerMovementSettings> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.authority_mode;
        }
        else if constexpr (I == 1) {
            return value.rewind_history_size;
        }
        else {
            return value.server_auth_block_breaking;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v818::SyncedPlayerMovementSettings> = true;

template <>
inline constexpr std::string_view struct_name_v<v818::SyncedPlayerMovementSettings>{"SyncedPlayerMovementSettings"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v818::SyncedPlayerMovementSettings>{{
    "rewind_history_size",
    "server_auth_block_breaking",
}};

template <>
struct field_accessor<v818::SyncedPlayerMovementSettings> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.rewind_history_size;
        }
        else {
            return value.server_auth_block_breaking;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<BlockEntry> = true;

template <>
inline constexpr std::string_view struct_name_v<BlockEntry>{"BlockEntry"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<BlockEntry>{{
    "name",
    "properties",
}};

template <>
struct field_accessor<BlockEntry> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.name;
        }
        else {
            return value.properties;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ServerBlockProperty> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ServerBlockProperty>{"ServerBlockProperty"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2168::ServerBlockProperty>{{
    "name",
    "tag",
}};

template <>
struct field_accessor<v2168::ServerBlockProperty> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.name;
        }
        else {
            return value.tag;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<legacy::base::GameRule> = true;

template <>
inline constexpr std::string_view struct_name_v<legacy::base::GameRule>{"GameRule"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<legacy::base::GameRule>{{
    "name",
    "can_be_modified_by_player",
    "value",
}};

template <>
struct field_accessor<legacy::base::GameRule> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.name;
        }
        else if constexpr (I == 1) {
            return value.can_be_modified_by_player;
        }
        else {
            return value.value;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::LevelSettings> = true;

template <>
inline constexpr std::string_view struct_name_v<base::LevelSettings>{"LevelSettings"};

template <>
inline constexpr std::array<std::string_view, 52> field_names_v<base::LevelSettings>{{
    "seed",
    "spawn_settings",
    "generator",
    "game_type",
    "is_hardcore",
    "game_difficulty",
    "default_spawn",
    "achievements_disabled",
    "editor_world_type",
    "is_created_in_editor",
    "is_exported_from_editor",
    "time",
    "education_edition_offer",
    "education_features_enabled",
    "education_product_id",
    "rain_level",
    "lightning_level",
    "confirmed_platform_locked_content",
    "multiplayer_game_intent",
    "lan_broadcast_intent",
    "xbl_broadcast_intent",
    "platform_broadcast_intent",
    "commands_enabled",
    "texture_packs_required",
    "game_rules",
    "experiments",
    "experiments_ever_toggled",
    "bonus_chest_enabled",
    "start_with_map_enabled",
    "default_permissions",
    "server_chunk_tick_range",
    "has_locked_behavior_pack",
    "has_locked_resource_pack",
    "is_from_locked_template",
    "use_msa_gamertags_only",
    "is_from_world_template",
    "is_world_template_option_locked",
    "spawn_v1_villagers",
    "persona_disabled",
    "custom_skins_disabled",
    "emote_chat_muted",
    "base_game_version",
    "limited_world_width",
    "limited_world_depth",
    "nether_type",
    "edu_shared_uri_resource",
    "override_force_experimental_gameplay",
    "chat_restriction_level",
    "disable_player_interactions",
    "server_id",
    "world_id",
    "scenario_id",
}};

template <>
struct field_accessor<base::LevelSettings> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.seed;
        }
        else if constexpr (I == 1) {
            return value.spawn_settings;
        }
        else if constexpr (I == 2) {
            return value.generator;
        }
        else if constexpr (I == 3) {
            return value.game_type;
        }
        else if constexpr (I == 4) {
            return value.is_hardcore;
        }
        else if constexpr (I == 5) {
            return value.game_difficulty;
        }
        else if constexpr (I == 6) {
            return value.default_spawn;
        }
        else if constexpr (I == 7) {
            return value.achievements_disabled;
        }
        else if constexpr (I == 8) {
            return value.editor_world_type;
        }
        else if constexpr (I == 9) {
            return value.is_created_in_editor;
        }
        else if constexpr (I == 10) {
            return value.is_exported_from_editor;
        }
        else if constexpr (I == 11) {
            return value.time;
        }
        else if constexpr (I == 12) {
            return value.education_edition_offer;
        }
        else if constexpr (I == 13) {
            return value.education_features_enabled;
        }
        else if constexpr (I == 14) {
            return value.education_product_id;
        }
        else if constexpr (I == 15) {
            return value.rain_level;
        }
        else if constexpr (I == 16) {
            return value.lightning_level;
        }
        else if constexpr (I == 17) {
            return value.confirmed_platform_locked_content;
        }
        else if constexpr (I == 18) {
            return value.multiplayer_game_intent;
        }
        else if constexpr (I == 19) {
            return value.lan_broadcast_intent;
        }
        else if constexpr (I == 20) {
            return value.xbl_broadcast_intent;
        }
        else if constexpr (I == 21) {
            return value.platform_broadcast_intent;
        }
        else if constexpr (I == 22) {
            return value.commands_enabled;
        }
        else if constexpr (I == 23) {
            return value.texture_packs_required;
        }
        else if constexpr (I == 24) {
            return value.game_rules;
        }
        else if constexpr (I == 25) {
            return value.experiments;
        }
        else if constexpr (I == 26) {
            return value.experiments_ever_toggled;
        }
        else if constexpr (I == 27) {
            return value.bonus_chest_enabled;
        }
        else if constexpr (I == 28) {
            return value.start_with_map_enabled;
        }
        else if constexpr (I == 29) {
            return value.default_permissions;
        }
        else if constexpr (I == 30) {
            return value.server_chunk_tick_range;
        }
        else if constexpr (I == 31) {
            return value.has_locked_behavior_pack;
        }
        else if constexpr (I == 32) {
            return value.has_locked_resource_pack;
        }
        else if constexpr (I == 33) {
            return value.is_from_locked_template;
        }
        else if constexpr (I == 34) {
            return value.use_msa_gamertags_only;
        }
        else if constexpr (I == 35) {
            return value.is_from_world_template;
        }
        else if constexpr (I == 36) {
            return value.is_world_template_option_locked;
        }
        else if constexpr (I == 37) {
            return value.spawn_v1_villagers;
        }
        else if constexpr (I == 38) {
            return value.persona_disabled;
        }
        else if constexpr (I == 39) {
            return value.custom_skins_disabled;
        }
        else if constexpr (I == 40) {
            return value.emote_chat_muted;
        }
        else if constexpr (I == 41) {
            return value.base_game_version;
        }
        else if constexpr (I == 42) {
            return value.limited_world_width;
        }
        else if constexpr (I == 43) {
            return value.limited_world_depth;
        }
        else if constexpr (I == 44) {
            return value.nether_type;
        }
        else if constexpr (I == 45) {
            return value.edu_shared_uri_resource;
        }
        else if constexpr (I == 46) {
            return value.override_force_experimental_gameplay;
        }
        else if constexpr (I == 47) {
            return value.chat_restriction_level;
        }
        else if constexpr (I == 48) {
            return value.disable_player_interactions;
        }
        else if constexpr (I == 49) {
            return value.server_id;
        }
        else if constexpr (I == 50) {
            return value.world_id;
        }
        else {
            return value.scenario_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v800::LevelSettings> = true;

template <>
inline constexpr std::string_view struct_name_v<v800::LevelSettings>{"LevelSettings"};

template <>
inline constexpr std::array<std::string_view, 52> field_names_v<v800::LevelSettings>{{
    "seed",
    "spawn_settings",
    "generator",
    "game_type",
    "is_hardcore",
    "game_difficulty",
    "default_spawn",
    "achievements_disabled",
    "editor_world_type",
    "is_created_in_editor",
    "is_exported_from_editor",
    "time",
    "education_edition_offer",
    "education_features_enabled",
    "education_product_id",
    "rain_level",
    "lightning_level",
    "confirmed_platform_locked_content",
    "multiplayer_game_intent",
    "lan_broadcast_intent",
    "xbl_broadcast_intent",
    "platform_broadcast_intent",
    "commands_enabled",
    "texture_packs_required",
    "game_rules",
    "experiments",
    "experiments_ever_toggled",
    "bonus_chest_enabled",
    "start_with_map_enabled",
    "default_permissions",
    "server_chunk_tick_range",
    "has_locked_behavior_pack",
    "has_locked_resource_pack",
    "is_from_locked_template",
    "use_msa_gamertags_only",
    "is_from_world_template",
    "is_world_template_option_locked",
    "spawn_v1_villagers",
    "persona_disabled",
    "custom_skins_disabled",
    "emote_chat_muted",
    "base_game_version",
    "limited_world_width",
    "limited_world_depth",
    "nether_type",
    "edu_shared_uri_resource",
    "override_force_experimental_gameplay",
    "chat_restriction_level",
    "disable_player_interactions",
    "server_id",
    "world_id",
    "scenario_id",
}};

template <>
struct field_accessor<v800::LevelSettings> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.seed;
        }
        else if constexpr (I == 1) {
            return value.spawn_settings;
        }
        else if constexpr (I == 2) {
            return value.generator;
        }
        else if constexpr (I == 3) {
            return value.game_type;
        }
        else if constexpr (I == 4) {
            return value.is_hardcore;
        }
        else if constexpr (I == 5) {
            return value.game_difficulty;
        }
        else if constexpr (I == 6) {
            return value.default_spawn;
        }
        else if constexpr (I == 7) {
            return value.achievements_disabled;
        }
        else if constexpr (I == 8) {
            return value.editor_world_type;
        }
        else if constexpr (I == 9) {
            return value.is_created_in_editor;
        }
        else if constexpr (I == 10) {
            return value.is_exported_from_editor;
        }
        else if constexpr (I == 11) {
            return value.time;
        }
        else if constexpr (I == 12) {
            return value.education_edition_offer;
        }
        else if constexpr (I == 13) {
            return value.education_features_enabled;
        }
        else if constexpr (I == 14) {
            return value.education_product_id;
        }
        else if constexpr (I == 15) {
            return value.rain_level;
        }
        else if constexpr (I == 16) {
            return value.lightning_level;
        }
        else if constexpr (I == 17) {
            return value.confirmed_platform_locked_content;
        }
        else if constexpr (I == 18) {
            return value.multiplayer_game_intent;
        }
        else if constexpr (I == 19) {
            return value.lan_broadcast_intent;
        }
        else if constexpr (I == 20) {
            return value.xbl_broadcast_intent;
        }
        else if constexpr (I == 21) {
            return value.platform_broadcast_intent;
        }
        else if constexpr (I == 22) {
            return value.commands_enabled;
        }
        else if constexpr (I == 23) {
            return value.texture_packs_required;
        }
        else if constexpr (I == 24) {
            return value.game_rules;
        }
        else if constexpr (I == 25) {
            return value.experiments;
        }
        else if constexpr (I == 26) {
            return value.experiments_ever_toggled;
        }
        else if constexpr (I == 27) {
            return value.bonus_chest_enabled;
        }
        else if constexpr (I == 28) {
            return value.start_with_map_enabled;
        }
        else if constexpr (I == 29) {
            return value.default_permissions;
        }
        else if constexpr (I == 30) {
            return value.server_chunk_tick_range;
        }
        else if constexpr (I == 31) {
            return value.has_locked_behavior_pack;
        }
        else if constexpr (I == 32) {
            return value.has_locked_resource_pack;
        }
        else if constexpr (I == 33) {
            return value.is_from_locked_template;
        }
        else if constexpr (I == 34) {
            return value.use_msa_gamertags_only;
        }
        else if constexpr (I == 35) {
            return value.is_from_world_template;
        }
        else if constexpr (I == 36) {
            return value.is_world_template_option_locked;
        }
        else if constexpr (I == 37) {
            return value.spawn_v1_villagers;
        }
        else if constexpr (I == 38) {
            return value.persona_disabled;
        }
        else if constexpr (I == 39) {
            return value.custom_skins_disabled;
        }
        else if constexpr (I == 40) {
            return value.emote_chat_muted;
        }
        else if constexpr (I == 41) {
            return value.base_game_version;
        }
        else if constexpr (I == 42) {
            return value.limited_world_width;
        }
        else if constexpr (I == 43) {
            return value.limited_world_depth;
        }
        else if constexpr (I == 44) {
            return value.nether_type;
        }
        else if constexpr (I == 45) {
            return value.edu_shared_uri_resource;
        }
        else if constexpr (I == 46) {
            return value.override_force_experimental_gameplay;
        }
        else if constexpr (I == 47) {
            return value.chat_restriction_level;
        }
        else if constexpr (I == 48) {
            return value.disable_player_interactions;
        }
        else if constexpr (I == 49) {
            return value.server_id;
        }
        else if constexpr (I == 50) {
            return value.world_id;
        }
        else {
            return value.scenario_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v818::LevelSettings> = true;

template <>
inline constexpr std::string_view struct_name_v<v818::LevelSettings>{"LevelSettings"};

template <>
inline constexpr std::array<std::string_view, 53> field_names_v<v818::LevelSettings>{{
    "seed",
    "spawn_settings",
    "generator",
    "game_type",
    "is_hardcore",
    "game_difficulty",
    "default_spawn",
    "achievements_disabled",
    "editor_world_type",
    "is_created_in_editor",
    "is_exported_from_editor",
    "time",
    "education_edition_offer",
    "education_features_enabled",
    "education_product_id",
    "rain_level",
    "lightning_level",
    "confirmed_platform_locked_content",
    "multiplayer_game_intent",
    "lan_broadcast_intent",
    "xbl_broadcast_intent",
    "platform_broadcast_intent",
    "commands_enabled",
    "texture_packs_required",
    "game_rules",
    "experiments",
    "experiments_ever_toggled",
    "bonus_chest_enabled",
    "start_with_map_enabled",
    "default_permissions",
    "server_chunk_tick_range",
    "has_locked_behavior_pack",
    "has_locked_resource_pack",
    "is_from_locked_template",
    "use_msa_gamertags_only",
    "is_from_world_template",
    "is_world_template_option_locked",
    "spawn_v1_villagers",
    "persona_disabled",
    "custom_skins_disabled",
    "emote_chat_muted",
    "base_game_version",
    "limited_world_width",
    "limited_world_depth",
    "nether_type",
    "edu_shared_uri_resource",
    "override_force_experimental_gameplay",
    "chat_restriction_level",
    "disable_player_interactions",
    "server_id",
    "world_id",
    "scenario_id",
    "owner_id",
}};

template <>
struct field_accessor<v818::LevelSettings> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.seed;
        }
        else if constexpr (I == 1) {
            return value.spawn_settings;
        }
        else if constexpr (I == 2) {
            return value.generator;
        }
        else if constexpr (I == 3) {
            return value.game_type;
        }
        else if constexpr (I == 4) {
            return value.is_hardcore;
        }
        else if constexpr (I == 5) {
            return value.game_difficulty;
        }
        else if constexpr (I == 6) {
            return value.default_spawn;
        }
        else if constexpr (I == 7) {
            return value.achievements_disabled;
        }
        else if constexpr (I == 8) {
            return value.editor_world_type;
        }
        else if constexpr (I == 9) {
            return value.is_created_in_editor;
        }
        else if constexpr (I == 10) {
            return value.is_exported_from_editor;
        }
        else if constexpr (I == 11) {
            return value.time;
        }
        else if constexpr (I == 12) {
            return value.education_edition_offer;
        }
        else if constexpr (I == 13) {
            return value.education_features_enabled;
        }
        else if constexpr (I == 14) {
            return value.education_product_id;
        }
        else if constexpr (I == 15) {
            return value.rain_level;
        }
        else if constexpr (I == 16) {
            return value.lightning_level;
        }
        else if constexpr (I == 17) {
            return value.confirmed_platform_locked_content;
        }
        else if constexpr (I == 18) {
            return value.multiplayer_game_intent;
        }
        else if constexpr (I == 19) {
            return value.lan_broadcast_intent;
        }
        else if constexpr (I == 20) {
            return value.xbl_broadcast_intent;
        }
        else if constexpr (I == 21) {
            return value.platform_broadcast_intent;
        }
        else if constexpr (I == 22) {
            return value.commands_enabled;
        }
        else if constexpr (I == 23) {
            return value.texture_packs_required;
        }
        else if constexpr (I == 24) {
            return value.game_rules;
        }
        else if constexpr (I == 25) {
            return value.experiments;
        }
        else if constexpr (I == 26) {
            return value.experiments_ever_toggled;
        }
        else if constexpr (I == 27) {
            return value.bonus_chest_enabled;
        }
        else if constexpr (I == 28) {
            return value.start_with_map_enabled;
        }
        else if constexpr (I == 29) {
            return value.default_permissions;
        }
        else if constexpr (I == 30) {
            return value.server_chunk_tick_range;
        }
        else if constexpr (I == 31) {
            return value.has_locked_behavior_pack;
        }
        else if constexpr (I == 32) {
            return value.has_locked_resource_pack;
        }
        else if constexpr (I == 33) {
            return value.is_from_locked_template;
        }
        else if constexpr (I == 34) {
            return value.use_msa_gamertags_only;
        }
        else if constexpr (I == 35) {
            return value.is_from_world_template;
        }
        else if constexpr (I == 36) {
            return value.is_world_template_option_locked;
        }
        else if constexpr (I == 37) {
            return value.spawn_v1_villagers;
        }
        else if constexpr (I == 38) {
            return value.persona_disabled;
        }
        else if constexpr (I == 39) {
            return value.custom_skins_disabled;
        }
        else if constexpr (I == 40) {
            return value.emote_chat_muted;
        }
        else if constexpr (I == 41) {
            return value.base_game_version;
        }
        else if constexpr (I == 42) {
            return value.limited_world_width;
        }
        else if constexpr (I == 43) {
            return value.limited_world_depth;
        }
        else if constexpr (I == 44) {
            return value.nether_type;
        }
        else if constexpr (I == 45) {
            return value.edu_shared_uri_resource;
        }
        else if constexpr (I == 46) {
            return value.override_force_experimental_gameplay;
        }
        else if constexpr (I == 47) {
            return value.chat_restriction_level;
        }
        else if constexpr (I == 48) {
            return value.disable_player_interactions;
        }
        else if constexpr (I == 49) {
            return value.server_id;
        }
        else if constexpr (I == 50) {
            return value.world_id;
        }
        else if constexpr (I == 51) {
            return value.scenario_id;
        }
        else {
            return value.owner_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v844::LevelSettings> = true;

template <>
inline constexpr std::string_view struct_name_v<v844::LevelSettings>{"LevelSettings"};

template <>
inline constexpr std::array<std::string_view, 53> field_names_v<v844::LevelSettings>{{
    "seed",
    "spawn_settings",
    "generator",
    "game_type",
    "is_hardcore",
    "game_difficulty",
    "default_spawn",
    "achievements_disabled",
    "editor_world_type",
    "is_created_in_editor",
    "is_exported_from_editor",
    "time",
    "education_edition_offer",
    "education_features_enabled",
    "education_product_id",
    "rain_level",
    "lightning_level",
    "confirmed_platform_locked_content",
    "multiplayer_game_intent",
    "lan_broadcast_intent",
    "xbl_broadcast_intent",
    "platform_broadcast_intent",
    "commands_enabled",
    "texture_packs_required",
    "game_rules",
    "experiments",
    "experiments_ever_toggled",
    "bonus_chest_enabled",
    "start_with_map_enabled",
    "default_permissions",
    "server_chunk_tick_range",
    "has_locked_behavior_pack",
    "has_locked_resource_pack",
    "is_from_locked_template",
    "use_msa_gamertags_only",
    "is_from_world_template",
    "is_world_template_option_locked",
    "spawn_v1_villagers",
    "persona_disabled",
    "custom_skins_disabled",
    "emote_chat_muted",
    "base_game_version",
    "limited_world_width",
    "limited_world_depth",
    "nether_type",
    "edu_shared_uri_resource",
    "override_force_experimental_gameplay",
    "chat_restriction_level",
    "disable_player_interactions",
    "server_id",
    "world_id",
    "scenario_id",
    "owner_id",
}};

template <>
struct field_accessor<v844::LevelSettings> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.seed;
        }
        else if constexpr (I == 1) {
            return value.spawn_settings;
        }
        else if constexpr (I == 2) {
            return value.generator;
        }
        else if constexpr (I == 3) {
            return value.game_type;
        }
        else if constexpr (I == 4) {
            return value.is_hardcore;
        }
        else if constexpr (I == 5) {
            return value.game_difficulty;
        }
        else if constexpr (I == 6) {
            return value.default_spawn;
        }
        else if constexpr (I == 7) {
            return value.achievements_disabled;
        }
        else if constexpr (I == 8) {
            return value.editor_world_type;
        }
        else if constexpr (I == 9) {
            return value.is_created_in_editor;
        }
        else if constexpr (I == 10) {
            return value.is_exported_from_editor;
        }
        else if constexpr (I == 11) {
            return value.time;
        }
        else if constexpr (I == 12) {
            return value.education_edition_offer;
        }
        else if constexpr (I == 13) {
            return value.education_features_enabled;
        }
        else if constexpr (I == 14) {
            return value.education_product_id;
        }
        else if constexpr (I == 15) {
            return value.rain_level;
        }
        else if constexpr (I == 16) {
            return value.lightning_level;
        }
        else if constexpr (I == 17) {
            return value.confirmed_platform_locked_content;
        }
        else if constexpr (I == 18) {
            return value.multiplayer_game_intent;
        }
        else if constexpr (I == 19) {
            return value.lan_broadcast_intent;
        }
        else if constexpr (I == 20) {
            return value.xbl_broadcast_intent;
        }
        else if constexpr (I == 21) {
            return value.platform_broadcast_intent;
        }
        else if constexpr (I == 22) {
            return value.commands_enabled;
        }
        else if constexpr (I == 23) {
            return value.texture_packs_required;
        }
        else if constexpr (I == 24) {
            return value.game_rules;
        }
        else if constexpr (I == 25) {
            return value.experiments;
        }
        else if constexpr (I == 26) {
            return value.experiments_ever_toggled;
        }
        else if constexpr (I == 27) {
            return value.bonus_chest_enabled;
        }
        else if constexpr (I == 28) {
            return value.start_with_map_enabled;
        }
        else if constexpr (I == 29) {
            return value.default_permissions;
        }
        else if constexpr (I == 30) {
            return value.server_chunk_tick_range;
        }
        else if constexpr (I == 31) {
            return value.has_locked_behavior_pack;
        }
        else if constexpr (I == 32) {
            return value.has_locked_resource_pack;
        }
        else if constexpr (I == 33) {
            return value.is_from_locked_template;
        }
        else if constexpr (I == 34) {
            return value.use_msa_gamertags_only;
        }
        else if constexpr (I == 35) {
            return value.is_from_world_template;
        }
        else if constexpr (I == 36) {
            return value.is_world_template_option_locked;
        }
        else if constexpr (I == 37) {
            return value.spawn_v1_villagers;
        }
        else if constexpr (I == 38) {
            return value.persona_disabled;
        }
        else if constexpr (I == 39) {
            return value.custom_skins_disabled;
        }
        else if constexpr (I == 40) {
            return value.emote_chat_muted;
        }
        else if constexpr (I == 41) {
            return value.base_game_version;
        }
        else if constexpr (I == 42) {
            return value.limited_world_width;
        }
        else if constexpr (I == 43) {
            return value.limited_world_depth;
        }
        else if constexpr (I == 44) {
            return value.nether_type;
        }
        else if constexpr (I == 45) {
            return value.edu_shared_uri_resource;
        }
        else if constexpr (I == 46) {
            return value.override_force_experimental_gameplay;
        }
        else if constexpr (I == 47) {
            return value.chat_restriction_level;
        }
        else if constexpr (I == 48) {
            return value.disable_player_interactions;
        }
        else if constexpr (I == 49) {
            return value.server_id;
        }
        else if constexpr (I == 50) {
            return value.world_id;
        }
        else if constexpr (I == 51) {
            return value.scenario_id;
        }
        else {
            return value.owner_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::LevelSettings> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::LevelSettings>{"LevelSettings"};

template <>
inline constexpr std::array<std::string_view, 49> field_names_v<v924::LevelSettings>{{
    "seed",
    "spawn_settings",
    "generator",
    "game_type",
    "is_hardcore",
    "game_difficulty",
    "default_spawn",
    "achievements_disabled",
    "editor_world_type",
    "is_created_in_editor",
    "is_exported_from_editor",
    "time",
    "education_edition_offer",
    "education_features_enabled",
    "education_product_id",
    "rain_level",
    "lightning_level",
    "confirmed_platform_locked_content",
    "multiplayer_game_intent",
    "lan_broadcast_intent",
    "xbl_broadcast_intent",
    "platform_broadcast_intent",
    "commands_enabled",
    "texture_packs_required",
    "game_rules",
    "experiments",
    "experiments_ever_toggled",
    "bonus_chest_enabled",
    "start_with_map_enabled",
    "default_permissions",
    "server_chunk_tick_range",
    "has_locked_behavior_pack",
    "has_locked_resource_pack",
    "is_from_locked_template",
    "use_msa_gamertags_only",
    "is_from_world_template",
    "is_world_template_option_locked",
    "spawn_v1_villagers",
    "persona_disabled",
    "custom_skins_disabled",
    "emote_chat_muted",
    "base_game_version",
    "limited_world_width",
    "limited_world_depth",
    "nether_type",
    "edu_shared_uri_resource",
    "override_force_experimental_gameplay",
    "chat_restriction_level",
    "disable_player_interactions",
}};

template <>
struct field_accessor<v924::LevelSettings> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.seed;
        }
        else if constexpr (I == 1) {
            return value.spawn_settings;
        }
        else if constexpr (I == 2) {
            return value.generator;
        }
        else if constexpr (I == 3) {
            return value.game_type;
        }
        else if constexpr (I == 4) {
            return value.is_hardcore;
        }
        else if constexpr (I == 5) {
            return value.game_difficulty;
        }
        else if constexpr (I == 6) {
            return value.default_spawn;
        }
        else if constexpr (I == 7) {
            return value.achievements_disabled;
        }
        else if constexpr (I == 8) {
            return value.editor_world_type;
        }
        else if constexpr (I == 9) {
            return value.is_created_in_editor;
        }
        else if constexpr (I == 10) {
            return value.is_exported_from_editor;
        }
        else if constexpr (I == 11) {
            return value.time;
        }
        else if constexpr (I == 12) {
            return value.education_edition_offer;
        }
        else if constexpr (I == 13) {
            return value.education_features_enabled;
        }
        else if constexpr (I == 14) {
            return value.education_product_id;
        }
        else if constexpr (I == 15) {
            return value.rain_level;
        }
        else if constexpr (I == 16) {
            return value.lightning_level;
        }
        else if constexpr (I == 17) {
            return value.confirmed_platform_locked_content;
        }
        else if constexpr (I == 18) {
            return value.multiplayer_game_intent;
        }
        else if constexpr (I == 19) {
            return value.lan_broadcast_intent;
        }
        else if constexpr (I == 20) {
            return value.xbl_broadcast_intent;
        }
        else if constexpr (I == 21) {
            return value.platform_broadcast_intent;
        }
        else if constexpr (I == 22) {
            return value.commands_enabled;
        }
        else if constexpr (I == 23) {
            return value.texture_packs_required;
        }
        else if constexpr (I == 24) {
            return value.game_rules;
        }
        else if constexpr (I == 25) {
            return value.experiments;
        }
        else if constexpr (I == 26) {
            return value.experiments_ever_toggled;
        }
        else if constexpr (I == 27) {
            return value.bonus_chest_enabled;
        }
        else if constexpr (I == 28) {
            return value.start_with_map_enabled;
        }
        else if constexpr (I == 29) {
            return value.default_permissions;
        }
        else if constexpr (I == 30) {
            return value.server_chunk_tick_range;
        }
        else if constexpr (I == 31) {
            return value.has_locked_behavior_pack;
        }
        else if constexpr (I == 32) {
            return value.has_locked_resource_pack;
        }
        else if constexpr (I == 33) {
            return value.is_from_locked_template;
        }
        else if constexpr (I == 34) {
            return value.use_msa_gamertags_only;
        }
        else if constexpr (I == 35) {
            return value.is_from_world_template;
        }
        else if constexpr (I == 36) {
            return value.is_world_template_option_locked;
        }
        else if constexpr (I == 37) {
            return value.spawn_v1_villagers;
        }
        else if constexpr (I == 38) {
            return value.persona_disabled;
        }
        else if constexpr (I == 39) {
            return value.custom_skins_disabled;
        }
        else if constexpr (I == 40) {
            return value.emote_chat_muted;
        }
        else if constexpr (I == 41) {
            return value.base_game_version;
        }
        else if constexpr (I == 42) {
            return value.limited_world_width;
        }
        else if constexpr (I == 43) {
            return value.limited_world_depth;
        }
        else if constexpr (I == 44) {
            return value.nether_type;
        }
        else if constexpr (I == 45) {
            return value.edu_shared_uri_resource;
        }
        else if constexpr (I == 46) {
            return value.override_force_experimental_gameplay;
        }
        else if constexpr (I == 47) {
            return value.chat_restriction_level;
        }
        else {
            return value.disable_player_interactions;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::LevelSettings> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::LevelSettings>{"LevelSettings"};

template <>
inline constexpr std::array<std::string_view, 49> field_names_v<v944::LevelSettings>{{
    "seed",
    "spawn_settings",
    "generator",
    "game_type",
    "is_hardcore",
    "game_difficulty",
    "default_spawn",
    "achievements_disabled",
    "editor_world_type",
    "is_created_in_editor",
    "is_exported_from_editor",
    "time",
    "education_edition_offer",
    "education_features_enabled",
    "education_product_id",
    "rain_level",
    "lightning_level",
    "confirmed_platform_locked_content",
    "multiplayer_game_intent",
    "lan_broadcast_intent",
    "xbl_broadcast_intent",
    "platform_broadcast_intent",
    "commands_enabled",
    "texture_packs_required",
    "game_rules",
    "experiments",
    "experiments_ever_toggled",
    "bonus_chest_enabled",
    "start_with_map_enabled",
    "default_permissions",
    "server_chunk_tick_range",
    "has_locked_behavior_pack",
    "has_locked_resource_pack",
    "is_from_locked_template",
    "use_msa_gamertags_only",
    "is_from_world_template",
    "is_world_template_option_locked",
    "spawn_v1_villagers",
    "persona_disabled",
    "custom_skins_disabled",
    "emote_chat_muted",
    "base_game_version",
    "limited_world_width",
    "limited_world_depth",
    "nether_type",
    "edu_shared_uri_resource",
    "override_force_experimental_gameplay",
    "chat_restriction_level",
    "disable_player_interactions",
}};

template <>
struct field_accessor<v944::LevelSettings> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.seed;
        }
        else if constexpr (I == 1) {
            return value.spawn_settings;
        }
        else if constexpr (I == 2) {
            return value.generator;
        }
        else if constexpr (I == 3) {
            return value.game_type;
        }
        else if constexpr (I == 4) {
            return value.is_hardcore;
        }
        else if constexpr (I == 5) {
            return value.game_difficulty;
        }
        else if constexpr (I == 6) {
            return value.default_spawn;
        }
        else if constexpr (I == 7) {
            return value.achievements_disabled;
        }
        else if constexpr (I == 8) {
            return value.editor_world_type;
        }
        else if constexpr (I == 9) {
            return value.is_created_in_editor;
        }
        else if constexpr (I == 10) {
            return value.is_exported_from_editor;
        }
        else if constexpr (I == 11) {
            return value.time;
        }
        else if constexpr (I == 12) {
            return value.education_edition_offer;
        }
        else if constexpr (I == 13) {
            return value.education_features_enabled;
        }
        else if constexpr (I == 14) {
            return value.education_product_id;
        }
        else if constexpr (I == 15) {
            return value.rain_level;
        }
        else if constexpr (I == 16) {
            return value.lightning_level;
        }
        else if constexpr (I == 17) {
            return value.confirmed_platform_locked_content;
        }
        else if constexpr (I == 18) {
            return value.multiplayer_game_intent;
        }
        else if constexpr (I == 19) {
            return value.lan_broadcast_intent;
        }
        else if constexpr (I == 20) {
            return value.xbl_broadcast_intent;
        }
        else if constexpr (I == 21) {
            return value.platform_broadcast_intent;
        }
        else if constexpr (I == 22) {
            return value.commands_enabled;
        }
        else if constexpr (I == 23) {
            return value.texture_packs_required;
        }
        else if constexpr (I == 24) {
            return value.game_rules;
        }
        else if constexpr (I == 25) {
            return value.experiments;
        }
        else if constexpr (I == 26) {
            return value.experiments_ever_toggled;
        }
        else if constexpr (I == 27) {
            return value.bonus_chest_enabled;
        }
        else if constexpr (I == 28) {
            return value.start_with_map_enabled;
        }
        else if constexpr (I == 29) {
            return value.default_permissions;
        }
        else if constexpr (I == 30) {
            return value.server_chunk_tick_range;
        }
        else if constexpr (I == 31) {
            return value.has_locked_behavior_pack;
        }
        else if constexpr (I == 32) {
            return value.has_locked_resource_pack;
        }
        else if constexpr (I == 33) {
            return value.is_from_locked_template;
        }
        else if constexpr (I == 34) {
            return value.use_msa_gamertags_only;
        }
        else if constexpr (I == 35) {
            return value.is_from_world_template;
        }
        else if constexpr (I == 36) {
            return value.is_world_template_option_locked;
        }
        else if constexpr (I == 37) {
            return value.spawn_v1_villagers;
        }
        else if constexpr (I == 38) {
            return value.persona_disabled;
        }
        else if constexpr (I == 39) {
            return value.custom_skins_disabled;
        }
        else if constexpr (I == 40) {
            return value.emote_chat_muted;
        }
        else if constexpr (I == 41) {
            return value.base_game_version;
        }
        else if constexpr (I == 42) {
            return value.limited_world_width;
        }
        else if constexpr (I == 43) {
            return value.limited_world_depth;
        }
        else if constexpr (I == 44) {
            return value.nether_type;
        }
        else if constexpr (I == 45) {
            return value.edu_shared_uri_resource;
        }
        else if constexpr (I == 46) {
            return value.override_force_experimental_gameplay;
        }
        else if constexpr (I == 47) {
            return value.chat_restriction_level;
        }
        else {
            return value.disable_player_interactions;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::LevelSettings> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::LevelSettings>{"LevelSettings"};

template <>
inline constexpr std::array<std::string_view, 51> field_names_v<v1001::LevelSettings>{{
    "seed",
    "spawn_settings",
    "generator",
    "game_type",
    "is_hardcore",
    "game_difficulty",
    "default_spawn",
    "achievements_disabled",
    "editor_world_type",
    "is_created_in_editor",
    "is_exported_from_editor",
    "time",
    "education_edition_offer",
    "education_features_enabled",
    "education_product_id",
    "rain_level",
    "lightning_level",
    "confirmed_platform_locked_content",
    "multiplayer_game_intent",
    "lan_broadcast_intent",
    "xbl_broadcast_intent",
    "platform_broadcast_intent",
    "commands_enabled",
    "texture_packs_required",
    "game_rules",
    "experiments",
    "experiments_ever_toggled",
    "bonus_chest_enabled",
    "start_with_map_enabled",
    "default_permissions",
    "server_chunk_tick_range",
    "has_locked_behavior_pack",
    "has_locked_resource_pack",
    "is_from_locked_template",
    "use_msa_gamertags_only",
    "is_from_world_template",
    "is_world_template_option_locked",
    "spawn_v1_villagers",
    "persona_disabled",
    "custom_skins_disabled",
    "emote_chat_muted",
    "base_game_version",
    "limited_world_width",
    "limited_world_depth",
    "nether_type",
    "edu_shared_uri_resource",
    "override_force_experimental_gameplay",
    "chat_restriction_level",
    "disable_player_interactions",
    "server_editor_connection_policy",
    "allow_anonymous_block_drops_in_editor_worlds",
}};

template <>
struct field_accessor<v1001::LevelSettings> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.seed;
        }
        else if constexpr (I == 1) {
            return value.spawn_settings;
        }
        else if constexpr (I == 2) {
            return value.generator;
        }
        else if constexpr (I == 3) {
            return value.game_type;
        }
        else if constexpr (I == 4) {
            return value.is_hardcore;
        }
        else if constexpr (I == 5) {
            return value.game_difficulty;
        }
        else if constexpr (I == 6) {
            return value.default_spawn;
        }
        else if constexpr (I == 7) {
            return value.achievements_disabled;
        }
        else if constexpr (I == 8) {
            return value.editor_world_type;
        }
        else if constexpr (I == 9) {
            return value.is_created_in_editor;
        }
        else if constexpr (I == 10) {
            return value.is_exported_from_editor;
        }
        else if constexpr (I == 11) {
            return value.time;
        }
        else if constexpr (I == 12) {
            return value.education_edition_offer;
        }
        else if constexpr (I == 13) {
            return value.education_features_enabled;
        }
        else if constexpr (I == 14) {
            return value.education_product_id;
        }
        else if constexpr (I == 15) {
            return value.rain_level;
        }
        else if constexpr (I == 16) {
            return value.lightning_level;
        }
        else if constexpr (I == 17) {
            return value.confirmed_platform_locked_content;
        }
        else if constexpr (I == 18) {
            return value.multiplayer_game_intent;
        }
        else if constexpr (I == 19) {
            return value.lan_broadcast_intent;
        }
        else if constexpr (I == 20) {
            return value.xbl_broadcast_intent;
        }
        else if constexpr (I == 21) {
            return value.platform_broadcast_intent;
        }
        else if constexpr (I == 22) {
            return value.commands_enabled;
        }
        else if constexpr (I == 23) {
            return value.texture_packs_required;
        }
        else if constexpr (I == 24) {
            return value.game_rules;
        }
        else if constexpr (I == 25) {
            return value.experiments;
        }
        else if constexpr (I == 26) {
            return value.experiments_ever_toggled;
        }
        else if constexpr (I == 27) {
            return value.bonus_chest_enabled;
        }
        else if constexpr (I == 28) {
            return value.start_with_map_enabled;
        }
        else if constexpr (I == 29) {
            return value.default_permissions;
        }
        else if constexpr (I == 30) {
            return value.server_chunk_tick_range;
        }
        else if constexpr (I == 31) {
            return value.has_locked_behavior_pack;
        }
        else if constexpr (I == 32) {
            return value.has_locked_resource_pack;
        }
        else if constexpr (I == 33) {
            return value.is_from_locked_template;
        }
        else if constexpr (I == 34) {
            return value.use_msa_gamertags_only;
        }
        else if constexpr (I == 35) {
            return value.is_from_world_template;
        }
        else if constexpr (I == 36) {
            return value.is_world_template_option_locked;
        }
        else if constexpr (I == 37) {
            return value.spawn_v1_villagers;
        }
        else if constexpr (I == 38) {
            return value.persona_disabled;
        }
        else if constexpr (I == 39) {
            return value.custom_skins_disabled;
        }
        else if constexpr (I == 40) {
            return value.emote_chat_muted;
        }
        else if constexpr (I == 41) {
            return value.base_game_version;
        }
        else if constexpr (I == 42) {
            return value.limited_world_width;
        }
        else if constexpr (I == 43) {
            return value.limited_world_depth;
        }
        else if constexpr (I == 44) {
            return value.nether_type;
        }
        else if constexpr (I == 45) {
            return value.edu_shared_uri_resource;
        }
        else if constexpr (I == 46) {
            return value.override_force_experimental_gameplay;
        }
        else if constexpr (I == 47) {
            return value.chat_restriction_level;
        }
        else if constexpr (I == 48) {
            return value.disable_player_interactions;
        }
        else if constexpr (I == 49) {
            return value.server_editor_connection_policy;
        }
        else {
            return value.allow_anonymous_block_drops_in_editor_worlds;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::LevelSettings> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::LevelSettings>{"LevelSettings"};

template <>
inline constexpr std::array<std::string_view, 50> field_names_v<v2168::LevelSettings>{{
    "seed",
    "spawn_settings",
    "generator",
    "game_type",
    "is_hardcore",
    "game_difficulty",
    "default_spawn",
    "achievements_disabled",
    "editor_world_type",
    "is_created_in_editor",
    "is_exported_from_editor",
    "time",
    "education_edition_offer",
    "education_features_enabled",
    "education_product_id",
    "rain_level",
    "lightning_level",
    "confirmed_platform_locked_content",
    "multiplayer_game_intent",
    "lan_broadcast_intent",
    "xbl_broadcast_intent",
    "platform_broadcast_intent",
    "commands_enabled",
    "texture_packs_required",
    "rule_data",
    "experiments",
    "bonus_chest_enabled",
    "start_with_map_enabled",
    "default_permissions",
    "server_chunk_tick_range",
    "has_locked_behavior_pack",
    "has_locked_resource_pack",
    "is_from_locked_template",
    "use_msa_gamertags_only",
    "is_from_world_template",
    "is_world_template_option_locked",
    "spawn_v1_villagers",
    "persona_disabled",
    "custom_skins_disabled",
    "emote_chat_muted",
    "base_game_version",
    "limited_world_width",
    "limited_world_depth",
    "nether_type",
    "edu_shared_uri_resource",
    "override_force_experimental_gameplay",
    "chat_restriction_level",
    "disable_player_interactions",
    "server_editor_connection_policy",
    "allow_anonymous_block_drops_in_editor_worlds",
}};

template <>
struct field_accessor<v2168::LevelSettings> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.seed;
        }
        else if constexpr (I == 1) {
            return value.spawn_settings;
        }
        else if constexpr (I == 2) {
            return value.generator;
        }
        else if constexpr (I == 3) {
            return value.game_type;
        }
        else if constexpr (I == 4) {
            return value.is_hardcore;
        }
        else if constexpr (I == 5) {
            return value.game_difficulty;
        }
        else if constexpr (I == 6) {
            return value.default_spawn;
        }
        else if constexpr (I == 7) {
            return value.achievements_disabled;
        }
        else if constexpr (I == 8) {
            return value.editor_world_type;
        }
        else if constexpr (I == 9) {
            return value.is_created_in_editor;
        }
        else if constexpr (I == 10) {
            return value.is_exported_from_editor;
        }
        else if constexpr (I == 11) {
            return value.time;
        }
        else if constexpr (I == 12) {
            return value.education_edition_offer;
        }
        else if constexpr (I == 13) {
            return value.education_features_enabled;
        }
        else if constexpr (I == 14) {
            return value.education_product_id;
        }
        else if constexpr (I == 15) {
            return value.rain_level;
        }
        else if constexpr (I == 16) {
            return value.lightning_level;
        }
        else if constexpr (I == 17) {
            return value.confirmed_platform_locked_content;
        }
        else if constexpr (I == 18) {
            return value.multiplayer_game_intent;
        }
        else if constexpr (I == 19) {
            return value.lan_broadcast_intent;
        }
        else if constexpr (I == 20) {
            return value.xbl_broadcast_intent;
        }
        else if constexpr (I == 21) {
            return value.platform_broadcast_intent;
        }
        else if constexpr (I == 22) {
            return value.commands_enabled;
        }
        else if constexpr (I == 23) {
            return value.texture_packs_required;
        }
        else if constexpr (I == 24) {
            return value.rule_data;
        }
        else if constexpr (I == 25) {
            return value.experiments;
        }
        else if constexpr (I == 26) {
            return value.bonus_chest_enabled;
        }
        else if constexpr (I == 27) {
            return value.start_with_map_enabled;
        }
        else if constexpr (I == 28) {
            return value.default_permissions;
        }
        else if constexpr (I == 29) {
            return value.server_chunk_tick_range;
        }
        else if constexpr (I == 30) {
            return value.has_locked_behavior_pack;
        }
        else if constexpr (I == 31) {
            return value.has_locked_resource_pack;
        }
        else if constexpr (I == 32) {
            return value.is_from_locked_template;
        }
        else if constexpr (I == 33) {
            return value.use_msa_gamertags_only;
        }
        else if constexpr (I == 34) {
            return value.is_from_world_template;
        }
        else if constexpr (I == 35) {
            return value.is_world_template_option_locked;
        }
        else if constexpr (I == 36) {
            return value.spawn_v1_villagers;
        }
        else if constexpr (I == 37) {
            return value.persona_disabled;
        }
        else if constexpr (I == 38) {
            return value.custom_skins_disabled;
        }
        else if constexpr (I == 39) {
            return value.emote_chat_muted;
        }
        else if constexpr (I == 40) {
            return value.base_game_version;
        }
        else if constexpr (I == 41) {
            return value.limited_world_width;
        }
        else if constexpr (I == 42) {
            return value.limited_world_depth;
        }
        else if constexpr (I == 43) {
            return value.nether_type;
        }
        else if constexpr (I == 44) {
            return value.edu_shared_uri_resource;
        }
        else if constexpr (I == 45) {
            return value.override_force_experimental_gameplay;
        }
        else if constexpr (I == 46) {
            return value.chat_restriction_level;
        }
        else if constexpr (I == 47) {
            return value.disable_player_interactions;
        }
        else if constexpr (I == 48) {
            return value.server_editor_connection_policy;
        }
        else {
            return value.allow_anonymous_block_drops_in_editor_worlds;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::LevelSettings> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::LevelSettings>{"LevelSettings"};

template <>
inline constexpr std::array<std::string_view, 51> field_names_v<v2225::LevelSettings>{{
    "seed",
    "spawn_settings",
    "generator",
    "game_type",
    "is_hardcore",
    "game_difficulty",
    "default_spawn",
    "achievements_disabled",
    "editor_world_type",
    "is_created_in_editor",
    "is_exported_from_editor",
    "editor_level_migration_version",
    "time",
    "education_edition_offer",
    "education_features_enabled",
    "education_product_id",
    "rain_level",
    "lightning_level",
    "confirmed_platform_locked_content",
    "multiplayer_game_intent",
    "lan_broadcast_intent",
    "xbl_broadcast_intent",
    "platform_broadcast_intent",
    "commands_enabled",
    "texture_packs_required",
    "rule_data",
    "experiments",
    "bonus_chest_enabled",
    "start_with_map_enabled",
    "default_permissions",
    "server_chunk_tick_range",
    "has_locked_behavior_pack",
    "has_locked_resource_pack",
    "is_from_locked_template",
    "use_msa_gamertags_only",
    "is_from_world_template",
    "is_world_template_option_locked",
    "spawn_v1_villagers",
    "persona_disabled",
    "custom_skins_disabled",
    "emote_chat_muted",
    "base_game_version",
    "limited_world_width",
    "limited_world_depth",
    "nether_type",
    "edu_shared_uri_resource",
    "override_force_experimental_gameplay",
    "chat_restriction_level",
    "disable_player_interactions",
    "server_editor_connection_policy",
    "allow_anonymous_block_drops_in_editor_worlds",
}};

template <>
struct field_accessor<v2225::LevelSettings> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.seed;
        }
        else if constexpr (I == 1) {
            return value.spawn_settings;
        }
        else if constexpr (I == 2) {
            return value.generator;
        }
        else if constexpr (I == 3) {
            return value.game_type;
        }
        else if constexpr (I == 4) {
            return value.is_hardcore;
        }
        else if constexpr (I == 5) {
            return value.game_difficulty;
        }
        else if constexpr (I == 6) {
            return value.default_spawn;
        }
        else if constexpr (I == 7) {
            return value.achievements_disabled;
        }
        else if constexpr (I == 8) {
            return value.editor_world_type;
        }
        else if constexpr (I == 9) {
            return value.is_created_in_editor;
        }
        else if constexpr (I == 10) {
            return value.is_exported_from_editor;
        }
        else if constexpr (I == 11) {
            return value.editor_level_migration_version;
        }
        else if constexpr (I == 12) {
            return value.time;
        }
        else if constexpr (I == 13) {
            return value.education_edition_offer;
        }
        else if constexpr (I == 14) {
            return value.education_features_enabled;
        }
        else if constexpr (I == 15) {
            return value.education_product_id;
        }
        else if constexpr (I == 16) {
            return value.rain_level;
        }
        else if constexpr (I == 17) {
            return value.lightning_level;
        }
        else if constexpr (I == 18) {
            return value.confirmed_platform_locked_content;
        }
        else if constexpr (I == 19) {
            return value.multiplayer_game_intent;
        }
        else if constexpr (I == 20) {
            return value.lan_broadcast_intent;
        }
        else if constexpr (I == 21) {
            return value.xbl_broadcast_intent;
        }
        else if constexpr (I == 22) {
            return value.platform_broadcast_intent;
        }
        else if constexpr (I == 23) {
            return value.commands_enabled;
        }
        else if constexpr (I == 24) {
            return value.texture_packs_required;
        }
        else if constexpr (I == 25) {
            return value.rule_data;
        }
        else if constexpr (I == 26) {
            return value.experiments;
        }
        else if constexpr (I == 27) {
            return value.bonus_chest_enabled;
        }
        else if constexpr (I == 28) {
            return value.start_with_map_enabled;
        }
        else if constexpr (I == 29) {
            return value.default_permissions;
        }
        else if constexpr (I == 30) {
            return value.server_chunk_tick_range;
        }
        else if constexpr (I == 31) {
            return value.has_locked_behavior_pack;
        }
        else if constexpr (I == 32) {
            return value.has_locked_resource_pack;
        }
        else if constexpr (I == 33) {
            return value.is_from_locked_template;
        }
        else if constexpr (I == 34) {
            return value.use_msa_gamertags_only;
        }
        else if constexpr (I == 35) {
            return value.is_from_world_template;
        }
        else if constexpr (I == 36) {
            return value.is_world_template_option_locked;
        }
        else if constexpr (I == 37) {
            return value.spawn_v1_villagers;
        }
        else if constexpr (I == 38) {
            return value.persona_disabled;
        }
        else if constexpr (I == 39) {
            return value.custom_skins_disabled;
        }
        else if constexpr (I == 40) {
            return value.emote_chat_muted;
        }
        else if constexpr (I == 41) {
            return value.base_game_version;
        }
        else if constexpr (I == 42) {
            return value.limited_world_width;
        }
        else if constexpr (I == 43) {
            return value.limited_world_depth;
        }
        else if constexpr (I == 44) {
            return value.nether_type;
        }
        else if constexpr (I == 45) {
            return value.edu_shared_uri_resource;
        }
        else if constexpr (I == 46) {
            return value.override_force_experimental_gameplay;
        }
        else if constexpr (I == 47) {
            return value.chat_restriction_level;
        }
        else if constexpr (I == 48) {
            return value.disable_player_interactions;
        }
        else if constexpr (I == 49) {
            return value.server_editor_connection_policy;
        }
        else {
            return value.allow_anonymous_block_drops_in_editor_worlds;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::StartGameItemEntry> = true;

template <>
inline constexpr std::string_view struct_name_v<base::StartGameItemEntry>{"StartGameItemEntry"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<base::StartGameItemEntry>{{
    "name",
    "id",
    "is_component_based",
}};

template <>
struct field_accessor<base::StartGameItemEntry> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.name;
        }
        else if constexpr (I == 1) {
            return value.id;
        }
        else {
            return value.is_component_based;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::StartGamePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::StartGamePacket>{"StartGamePacket"};

template <>
inline constexpr std::array<std::string_view, 24> field_names_v<base::StartGamePacket>{{
    "entity_id",
    "runtime_id",
    "entity_game_type",
    "pos",
    "rot",
    "settings",
    "level_id",
    "level_name",
    "template_content_identity",
    "is_trial",
    "movement_settings",
    "level_current_time",
    "enchantment_seed",
    "block_properties",
    "items",
    "multiplayer_correlation_id",
    "enable_item_stack_net_manager",
    "server_version",
    "player_property_data",
    "server_block_type_registry_checksum",
    "world_template_id",
    "server_enabled_client_side_generation",
    "block_network_ids_are_hashes",
    "network_permissions",
}};

template <>
struct field_accessor<base::StartGamePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.entity_id;
        }
        else if constexpr (I == 1) {
            return value.runtime_id;
        }
        else if constexpr (I == 2) {
            return value.entity_game_type;
        }
        else if constexpr (I == 3) {
            return value.pos;
        }
        else if constexpr (I == 4) {
            return value.rot;
        }
        else if constexpr (I == 5) {
            return value.settings;
        }
        else if constexpr (I == 6) {
            return value.level_id;
        }
        else if constexpr (I == 7) {
            return value.level_name;
        }
        else if constexpr (I == 8) {
            return value.template_content_identity;
        }
        else if constexpr (I == 9) {
            return value.is_trial;
        }
        else if constexpr (I == 10) {
            return value.movement_settings;
        }
        else if constexpr (I == 11) {
            return value.level_current_time;
        }
        else if constexpr (I == 12) {
            return value.enchantment_seed;
        }
        else if constexpr (I == 13) {
            return value.block_properties;
        }
        else if constexpr (I == 14) {
            return value.items;
        }
        else if constexpr (I == 15) {
            return value.multiplayer_correlation_id;
        }
        else if constexpr (I == 16) {
            return value.enable_item_stack_net_manager;
        }
        else if constexpr (I == 17) {
            return value.server_version;
        }
        else if constexpr (I == 18) {
            return value.player_property_data;
        }
        else if constexpr (I == 19) {
            return value.server_block_type_registry_checksum;
        }
        else if constexpr (I == 20) {
            return value.world_template_id;
        }
        else if constexpr (I == 21) {
            return value.server_enabled_client_side_generation;
        }
        else if constexpr (I == 22) {
            return value.block_network_ids_are_hashes;
        }
        else {
            return value.network_permissions;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v776::StartGamePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v776::StartGamePacket>{"StartGamePacket"};

template <>
inline constexpr std::array<std::string_view, 23> field_names_v<v776::StartGamePacket>{{
    "entity_id",
    "runtime_id",
    "entity_game_type",
    "pos",
    "rot",
    "settings",
    "level_id",
    "level_name",
    "template_content_identity",
    "is_trial",
    "movement_settings",
    "level_current_time",
    "enchantment_seed",
    "block_properties",
    "multiplayer_correlation_id",
    "enable_item_stack_net_manager",
    "server_version",
    "player_property_data",
    "server_block_type_registry_checksum",
    "world_template_id",
    "server_enabled_client_side_generation",
    "block_network_ids_are_hashes",
    "network_permissions",
}};

template <>
struct field_accessor<v776::StartGamePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.entity_id;
        }
        else if constexpr (I == 1) {
            return value.runtime_id;
        }
        else if constexpr (I == 2) {
            return value.entity_game_type;
        }
        else if constexpr (I == 3) {
            return value.pos;
        }
        else if constexpr (I == 4) {
            return value.rot;
        }
        else if constexpr (I == 5) {
            return value.settings;
        }
        else if constexpr (I == 6) {
            return value.level_id;
        }
        else if constexpr (I == 7) {
            return value.level_name;
        }
        else if constexpr (I == 8) {
            return value.template_content_identity;
        }
        else if constexpr (I == 9) {
            return value.is_trial;
        }
        else if constexpr (I == 10) {
            return value.movement_settings;
        }
        else if constexpr (I == 11) {
            return value.level_current_time;
        }
        else if constexpr (I == 12) {
            return value.enchantment_seed;
        }
        else if constexpr (I == 13) {
            return value.block_properties;
        }
        else if constexpr (I == 14) {
            return value.multiplayer_correlation_id;
        }
        else if constexpr (I == 15) {
            return value.enable_item_stack_net_manager;
        }
        else if constexpr (I == 16) {
            return value.server_version;
        }
        else if constexpr (I == 17) {
            return value.player_property_data;
        }
        else if constexpr (I == 18) {
            return value.server_block_type_registry_checksum;
        }
        else if constexpr (I == 19) {
            return value.world_template_id;
        }
        else if constexpr (I == 20) {
            return value.server_enabled_client_side_generation;
        }
        else if constexpr (I == 21) {
            return value.block_network_ids_are_hashes;
        }
        else {
            return value.network_permissions;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v800::StartGamePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v800::StartGamePacket>{"StartGamePacket"};

template <>
inline constexpr std::array<std::string_view, 23> field_names_v<v800::StartGamePacket>{{
    "entity_id",
    "runtime_id",
    "entity_game_type",
    "pos",
    "rot",
    "settings",
    "level_id",
    "level_name",
    "template_content_identity",
    "is_trial",
    "movement_settings",
    "level_current_time",
    "enchantment_seed",
    "block_properties",
    "multiplayer_correlation_id",
    "enable_item_stack_net_manager",
    "server_version",
    "player_property_data",
    "server_block_type_registry_checksum",
    "world_template_id",
    "server_enabled_client_side_generation",
    "block_network_ids_are_hashes",
    "network_permissions",
}};

template <>
struct field_accessor<v800::StartGamePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.entity_id;
        }
        else if constexpr (I == 1) {
            return value.runtime_id;
        }
        else if constexpr (I == 2) {
            return value.entity_game_type;
        }
        else if constexpr (I == 3) {
            return value.pos;
        }
        else if constexpr (I == 4) {
            return value.rot;
        }
        else if constexpr (I == 5) {
            return value.settings;
        }
        else if constexpr (I == 6) {
            return value.level_id;
        }
        else if constexpr (I == 7) {
            return value.level_name;
        }
        else if constexpr (I == 8) {
            return value.template_content_identity;
        }
        else if constexpr (I == 9) {
            return value.is_trial;
        }
        else if constexpr (I == 10) {
            return value.movement_settings;
        }
        else if constexpr (I == 11) {
            return value.level_current_time;
        }
        else if constexpr (I == 12) {
            return value.enchantment_seed;
        }
        else if constexpr (I == 13) {
            return value.block_properties;
        }
        else if constexpr (I == 14) {
            return value.multiplayer_correlation_id;
        }
        else if constexpr (I == 15) {
            return value.enable_item_stack_net_manager;
        }
        else if constexpr (I == 16) {
            return value.server_version;
        }
        else if constexpr (I == 17) {
            return value.player_property_data;
        }
        else if constexpr (I == 18) {
            return value.server_block_type_registry_checksum;
        }
        else if constexpr (I == 19) {
            return value.world_template_id;
        }
        else if constexpr (I == 20) {
            return value.server_enabled_client_side_generation;
        }
        else if constexpr (I == 21) {
            return value.block_network_ids_are_hashes;
        }
        else {
            return value.network_permissions;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v818::StartGamePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v818::StartGamePacket>{"StartGamePacket"};

template <>
inline constexpr std::array<std::string_view, 23> field_names_v<v818::StartGamePacket>{{
    "entity_id",
    "runtime_id",
    "entity_game_type",
    "pos",
    "rot",
    "settings",
    "level_id",
    "level_name",
    "template_content_identity",
    "is_trial",
    "movement_settings",
    "level_current_time",
    "enchantment_seed",
    "block_properties",
    "multiplayer_correlation_id",
    "enable_item_stack_net_manager",
    "server_version",
    "player_property_data",
    "server_block_type_registry_checksum",
    "world_template_id",
    "server_enabled_client_side_generation",
    "block_network_ids_are_hashes",
    "network_permissions",
}};

template <>
struct field_accessor<v818::StartGamePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.entity_id;
        }
        else if constexpr (I == 1) {
            return value.runtime_id;
        }
        else if constexpr (I == 2) {
            return value.entity_game_type;
        }
        else if constexpr (I == 3) {
            return value.pos;
        }
        else if constexpr (I == 4) {
            return value.rot;
        }
        else if constexpr (I == 5) {
            return value.settings;
        }
        else if constexpr (I == 6) {
            return value.level_id;
        }
        else if constexpr (I == 7) {
            return value.level_name;
        }
        else if constexpr (I == 8) {
            return value.template_content_identity;
        }
        else if constexpr (I == 9) {
            return value.is_trial;
        }
        else if constexpr (I == 10) {
            return value.movement_settings;
        }
        else if constexpr (I == 11) {
            return value.level_current_time;
        }
        else if constexpr (I == 12) {
            return value.enchantment_seed;
        }
        else if constexpr (I == 13) {
            return value.block_properties;
        }
        else if constexpr (I == 14) {
            return value.multiplayer_correlation_id;
        }
        else if constexpr (I == 15) {
            return value.enable_item_stack_net_manager;
        }
        else if constexpr (I == 16) {
            return value.server_version;
        }
        else if constexpr (I == 17) {
            return value.player_property_data;
        }
        else if constexpr (I == 18) {
            return value.server_block_type_registry_checksum;
        }
        else if constexpr (I == 19) {
            return value.world_template_id;
        }
        else if constexpr (I == 20) {
            return value.server_enabled_client_side_generation;
        }
        else if constexpr (I == 21) {
            return value.block_network_ids_are_hashes;
        }
        else {
            return value.network_permissions;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v827::StartGamePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v827::StartGamePacket>{"StartGamePacket"};

template <>
inline constexpr std::array<std::string_view, 24> field_names_v<v827::StartGamePacket>{{
    "entity_id",
    "runtime_id",
    "entity_game_type",
    "pos",
    "rot",
    "settings",
    "level_id",
    "level_name",
    "template_content_identity",
    "is_trial",
    "movement_settings",
    "level_current_time",
    "enchantment_seed",
    "block_properties",
    "multiplayer_correlation_id",
    "enable_item_stack_net_manager",
    "server_version",
    "player_property_data",
    "server_block_type_registry_checksum",
    "world_template_id",
    "server_enabled_client_side_generation",
    "block_network_ids_are_hashes",
    "tick_death_systems_enabled",
    "network_permissions",
}};

template <>
struct field_accessor<v827::StartGamePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.entity_id;
        }
        else if constexpr (I == 1) {
            return value.runtime_id;
        }
        else if constexpr (I == 2) {
            return value.entity_game_type;
        }
        else if constexpr (I == 3) {
            return value.pos;
        }
        else if constexpr (I == 4) {
            return value.rot;
        }
        else if constexpr (I == 5) {
            return value.settings;
        }
        else if constexpr (I == 6) {
            return value.level_id;
        }
        else if constexpr (I == 7) {
            return value.level_name;
        }
        else if constexpr (I == 8) {
            return value.template_content_identity;
        }
        else if constexpr (I == 9) {
            return value.is_trial;
        }
        else if constexpr (I == 10) {
            return value.movement_settings;
        }
        else if constexpr (I == 11) {
            return value.level_current_time;
        }
        else if constexpr (I == 12) {
            return value.enchantment_seed;
        }
        else if constexpr (I == 13) {
            return value.block_properties;
        }
        else if constexpr (I == 14) {
            return value.multiplayer_correlation_id;
        }
        else if constexpr (I == 15) {
            return value.enable_item_stack_net_manager;
        }
        else if constexpr (I == 16) {
            return value.server_version;
        }
        else if constexpr (I == 17) {
            return value.player_property_data;
        }
        else if constexpr (I == 18) {
            return value.server_block_type_registry_checksum;
        }
        else if constexpr (I == 19) {
            return value.world_template_id;
        }
        else if constexpr (I == 20) {
            return value.server_enabled_client_side_generation;
        }
        else if constexpr (I == 21) {
            return value.block_network_ids_are_hashes;
        }
        else if constexpr (I == 22) {
            return value.tick_death_systems_enabled;
        }
        else {
            return value.network_permissions;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v844::StartGamePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v844::StartGamePacket>{"StartGamePacket"};

template <>
inline constexpr std::array<std::string_view, 24> field_names_v<v844::StartGamePacket>{{
    "entity_id",
    "runtime_id",
    "entity_game_type",
    "pos",
    "rot",
    "settings",
    "level_id",
    "level_name",
    "template_content_identity",
    "is_trial",
    "movement_settings",
    "level_current_time",
    "enchantment_seed",
    "block_properties",
    "multiplayer_correlation_id",
    "enable_item_stack_net_manager",
    "server_version",
    "player_property_data",
    "server_block_type_registry_checksum",
    "world_template_id",
    "server_enabled_client_side_generation",
    "block_network_ids_are_hashes",
    "tick_death_systems_enabled",
    "network_permissions",
}};

template <>
struct field_accessor<v844::StartGamePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.entity_id;
        }
        else if constexpr (I == 1) {
            return value.runtime_id;
        }
        else if constexpr (I == 2) {
            return value.entity_game_type;
        }
        else if constexpr (I == 3) {
            return value.pos;
        }
        else if constexpr (I == 4) {
            return value.rot;
        }
        else if constexpr (I == 5) {
            return value.settings;
        }
        else if constexpr (I == 6) {
            return value.level_id;
        }
        else if constexpr (I == 7) {
            return value.level_name;
        }
        else if constexpr (I == 8) {
            return value.template_content_identity;
        }
        else if constexpr (I == 9) {
            return value.is_trial;
        }
        else if constexpr (I == 10) {
            return value.movement_settings;
        }
        else if constexpr (I == 11) {
            return value.level_current_time;
        }
        else if constexpr (I == 12) {
            return value.enchantment_seed;
        }
        else if constexpr (I == 13) {
            return value.block_properties;
        }
        else if constexpr (I == 14) {
            return value.multiplayer_correlation_id;
        }
        else if constexpr (I == 15) {
            return value.enable_item_stack_net_manager;
        }
        else if constexpr (I == 16) {
            return value.server_version;
        }
        else if constexpr (I == 17) {
            return value.player_property_data;
        }
        else if constexpr (I == 18) {
            return value.server_block_type_registry_checksum;
        }
        else if constexpr (I == 19) {
            return value.world_template_id;
        }
        else if constexpr (I == 20) {
            return value.server_enabled_client_side_generation;
        }
        else if constexpr (I == 21) {
            return value.block_network_ids_are_hashes;
        }
        else if constexpr (I == 22) {
            return value.tick_death_systems_enabled;
        }
        else {
            return value.network_permissions;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v898::StartGamePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v898::StartGamePacket>{"StartGamePacket"};

template <>
inline constexpr std::array<std::string_view, 23> field_names_v<v898::StartGamePacket>{{
    "entity_id",
    "runtime_id",
    "entity_game_type",
    "pos",
    "rot",
    "settings",
    "level_id",
    "level_name",
    "template_content_identity",
    "is_trial",
    "movement_settings",
    "level_current_time",
    "enchantment_seed",
    "block_properties",
    "multiplayer_correlation_id",
    "enable_item_stack_net_manager",
    "server_version",
    "player_property_data",
    "server_block_type_registry_checksum",
    "world_template_id",
    "server_enabled_client_side_generation",
    "block_network_ids_are_hashes",
    "network_permissions",
}};

template <>
struct field_accessor<v898::StartGamePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.entity_id;
        }
        else if constexpr (I == 1) {
            return value.runtime_id;
        }
        else if constexpr (I == 2) {
            return value.entity_game_type;
        }
        else if constexpr (I == 3) {
            return value.pos;
        }
        else if constexpr (I == 4) {
            return value.rot;
        }
        else if constexpr (I == 5) {
            return value.settings;
        }
        else if constexpr (I == 6) {
            return value.level_id;
        }
        else if constexpr (I == 7) {
            return value.level_name;
        }
        else if constexpr (I == 8) {
            return value.template_content_identity;
        }
        else if constexpr (I == 9) {
            return value.is_trial;
        }
        else if constexpr (I == 10) {
            return value.movement_settings;
        }
        else if constexpr (I == 11) {
            return value.level_current_time;
        }
        else if constexpr (I == 12) {
            return value.enchantment_seed;
        }
        else if constexpr (I == 13) {
            return value.block_properties;
        }
        else if constexpr (I == 14) {
            return value.multiplayer_correlation_id;
        }
        else if constexpr (I == 15) {
            return value.enable_item_stack_net_manager;
        }
        else if constexpr (I == 16) {
            return value.server_version;
        }
        else if constexpr (I == 17) {
            return value.player_property_data;
        }
        else if constexpr (I == 18) {
            return value.server_block_type_registry_checksum;
        }
        else if constexpr (I == 19) {
            return value.world_template_id;
        }
        else if constexpr (I == 20) {
            return value.server_enabled_client_side_generation;
        }
        else if constexpr (I == 21) {
            return value.block_network_ids_are_hashes;
        }
        else {
            return value.network_permissions;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::StartGamePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::StartGamePacket>{"StartGamePacket"};

template <>
inline constexpr std::array<std::string_view, 25> field_names_v<v924::StartGamePacket>{{
    "entity_id",
    "runtime_id",
    "entity_game_type",
    "pos",
    "rot",
    "settings",
    "level_id",
    "level_name",
    "template_content_identity",
    "is_trial",
    "movement_settings",
    "level_current_time",
    "enchantment_seed",
    "block_properties",
    "multiplayer_correlation_id",
    "enable_item_stack_net_manager",
    "server_version",
    "player_property_data",
    "server_block_type_registry_checksum",
    "world_template_id",
    "server_enabled_client_side_generation",
    "block_network_ids_are_hashes",
    "network_permissions",
    "server_configuration_join_info",
    "server_telemetry_data",
}};

template <>
struct field_accessor<v924::StartGamePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.entity_id;
        }
        else if constexpr (I == 1) {
            return value.runtime_id;
        }
        else if constexpr (I == 2) {
            return value.entity_game_type;
        }
        else if constexpr (I == 3) {
            return value.pos;
        }
        else if constexpr (I == 4) {
            return value.rot;
        }
        else if constexpr (I == 5) {
            return value.settings;
        }
        else if constexpr (I == 6) {
            return value.level_id;
        }
        else if constexpr (I == 7) {
            return value.level_name;
        }
        else if constexpr (I == 8) {
            return value.template_content_identity;
        }
        else if constexpr (I == 9) {
            return value.is_trial;
        }
        else if constexpr (I == 10) {
            return value.movement_settings;
        }
        else if constexpr (I == 11) {
            return value.level_current_time;
        }
        else if constexpr (I == 12) {
            return value.enchantment_seed;
        }
        else if constexpr (I == 13) {
            return value.block_properties;
        }
        else if constexpr (I == 14) {
            return value.multiplayer_correlation_id;
        }
        else if constexpr (I == 15) {
            return value.enable_item_stack_net_manager;
        }
        else if constexpr (I == 16) {
            return value.server_version;
        }
        else if constexpr (I == 17) {
            return value.player_property_data;
        }
        else if constexpr (I == 18) {
            return value.server_block_type_registry_checksum;
        }
        else if constexpr (I == 19) {
            return value.world_template_id;
        }
        else if constexpr (I == 20) {
            return value.server_enabled_client_side_generation;
        }
        else if constexpr (I == 21) {
            return value.block_network_ids_are_hashes;
        }
        else if constexpr (I == 22) {
            return value.network_permissions;
        }
        else if constexpr (I == 23) {
            return value.server_configuration_join_info;
        }
        else {
            return value.server_telemetry_data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::StartGamePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::StartGamePacket>{"StartGamePacket"};

template <>
inline constexpr std::array<std::string_view, 25> field_names_v<v944::StartGamePacket>{{
    "entity_id",
    "runtime_id",
    "entity_game_type",
    "pos",
    "rot",
    "settings",
    "level_id",
    "level_name",
    "template_content_identity",
    "is_trial",
    "movement_settings",
    "level_current_time",
    "enchantment_seed",
    "block_properties",
    "multiplayer_correlation_id",
    "enable_item_stack_net_manager",
    "server_version",
    "player_property_data",
    "server_block_type_registry_checksum",
    "world_template_id",
    "server_enabled_client_side_generation",
    "block_network_ids_are_hashes",
    "network_permissions",
    "server_configuration_join_info",
    "server_telemetry_data",
}};

template <>
struct field_accessor<v944::StartGamePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.entity_id;
        }
        else if constexpr (I == 1) {
            return value.runtime_id;
        }
        else if constexpr (I == 2) {
            return value.entity_game_type;
        }
        else if constexpr (I == 3) {
            return value.pos;
        }
        else if constexpr (I == 4) {
            return value.rot;
        }
        else if constexpr (I == 5) {
            return value.settings;
        }
        else if constexpr (I == 6) {
            return value.level_id;
        }
        else if constexpr (I == 7) {
            return value.level_name;
        }
        else if constexpr (I == 8) {
            return value.template_content_identity;
        }
        else if constexpr (I == 9) {
            return value.is_trial;
        }
        else if constexpr (I == 10) {
            return value.movement_settings;
        }
        else if constexpr (I == 11) {
            return value.level_current_time;
        }
        else if constexpr (I == 12) {
            return value.enchantment_seed;
        }
        else if constexpr (I == 13) {
            return value.block_properties;
        }
        else if constexpr (I == 14) {
            return value.multiplayer_correlation_id;
        }
        else if constexpr (I == 15) {
            return value.enable_item_stack_net_manager;
        }
        else if constexpr (I == 16) {
            return value.server_version;
        }
        else if constexpr (I == 17) {
            return value.player_property_data;
        }
        else if constexpr (I == 18) {
            return value.server_block_type_registry_checksum;
        }
        else if constexpr (I == 19) {
            return value.world_template_id;
        }
        else if constexpr (I == 20) {
            return value.server_enabled_client_side_generation;
        }
        else if constexpr (I == 21) {
            return value.block_network_ids_are_hashes;
        }
        else if constexpr (I == 22) {
            return value.network_permissions;
        }
        else if constexpr (I == 23) {
            return value.server_configuration_join_info;
        }
        else {
            return value.server_telemetry_data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::StartGamePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::StartGamePacket>{"StartGamePacket"};

template <>
inline constexpr std::array<std::string_view, 26> field_names_v<v1001::StartGamePacket>{{
    "entity_id",
    "runtime_id",
    "entity_game_type",
    "pos",
    "rot",
    "settings",
    "level_id",
    "level_name",
    "template_content_identity",
    "is_trial",
    "movement_settings",
    "level_current_time",
    "enchantment_seed",
    "block_properties",
    "multiplayer_correlation_id",
    "enable_item_stack_net_manager",
    "server_version",
    "player_property_data",
    "server_block_type_registry_checksum",
    "world_template_id",
    "server_enabled_client_side_generation",
    "block_network_ids_are_hashes",
    "network_permissions",
    "is_logging_chat",
    "server_configuration_join_info",
    "server_telemetry_data",
}};

template <>
struct field_accessor<v1001::StartGamePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.entity_id;
        }
        else if constexpr (I == 1) {
            return value.runtime_id;
        }
        else if constexpr (I == 2) {
            return value.entity_game_type;
        }
        else if constexpr (I == 3) {
            return value.pos;
        }
        else if constexpr (I == 4) {
            return value.rot;
        }
        else if constexpr (I == 5) {
            return value.settings;
        }
        else if constexpr (I == 6) {
            return value.level_id;
        }
        else if constexpr (I == 7) {
            return value.level_name;
        }
        else if constexpr (I == 8) {
            return value.template_content_identity;
        }
        else if constexpr (I == 9) {
            return value.is_trial;
        }
        else if constexpr (I == 10) {
            return value.movement_settings;
        }
        else if constexpr (I == 11) {
            return value.level_current_time;
        }
        else if constexpr (I == 12) {
            return value.enchantment_seed;
        }
        else if constexpr (I == 13) {
            return value.block_properties;
        }
        else if constexpr (I == 14) {
            return value.multiplayer_correlation_id;
        }
        else if constexpr (I == 15) {
            return value.enable_item_stack_net_manager;
        }
        else if constexpr (I == 16) {
            return value.server_version;
        }
        else if constexpr (I == 17) {
            return value.player_property_data;
        }
        else if constexpr (I == 18) {
            return value.server_block_type_registry_checksum;
        }
        else if constexpr (I == 19) {
            return value.world_template_id;
        }
        else if constexpr (I == 20) {
            return value.server_enabled_client_side_generation;
        }
        else if constexpr (I == 21) {
            return value.block_network_ids_are_hashes;
        }
        else if constexpr (I == 22) {
            return value.network_permissions;
        }
        else if constexpr (I == 23) {
            return value.is_logging_chat;
        }
        else if constexpr (I == 24) {
            return value.server_configuration_join_info;
        }
        else {
            return value.server_telemetry_data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::StartGamePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::StartGamePacket>{"StartGamePacket"};

template <>
inline constexpr std::array<std::string_view, 25> field_names_v<v2168::StartGamePacket>{{
    "entity_id",
    "runtime_id",
    "entity_game_type",
    "pos",
    "rot",
    "settings",
    "level_id",
    "level_name",
    "template_content_identity",
    "is_trial",
    "movement_settings",
    "level_current_time",
    "enchantment_seed",
    "block_properties",
    "multiplayer_correlation_id",
    "enable_item_stack_net_manager",
    "server_version",
    "player_property_data",
    "server_block_type_registry_checksum",
    "world_template_id",
    "server_enabled_client_side_generation",
    "block_network_ids_are_hashes",
    "network_permissions",
    "server_configuration_join_info",
    "server_telemetry_data",
}};

template <>
struct field_accessor<v2168::StartGamePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.entity_id;
        }
        else if constexpr (I == 1) {
            return value.runtime_id;
        }
        else if constexpr (I == 2) {
            return value.entity_game_type;
        }
        else if constexpr (I == 3) {
            return value.pos;
        }
        else if constexpr (I == 4) {
            return value.rot;
        }
        else if constexpr (I == 5) {
            return value.settings;
        }
        else if constexpr (I == 6) {
            return value.level_id;
        }
        else if constexpr (I == 7) {
            return value.level_name;
        }
        else if constexpr (I == 8) {
            return value.template_content_identity;
        }
        else if constexpr (I == 9) {
            return value.is_trial;
        }
        else if constexpr (I == 10) {
            return value.movement_settings;
        }
        else if constexpr (I == 11) {
            return value.level_current_time;
        }
        else if constexpr (I == 12) {
            return value.enchantment_seed;
        }
        else if constexpr (I == 13) {
            return value.block_properties;
        }
        else if constexpr (I == 14) {
            return value.multiplayer_correlation_id;
        }
        else if constexpr (I == 15) {
            return value.enable_item_stack_net_manager;
        }
        else if constexpr (I == 16) {
            return value.server_version;
        }
        else if constexpr (I == 17) {
            return value.player_property_data;
        }
        else if constexpr (I == 18) {
            return value.server_block_type_registry_checksum;
        }
        else if constexpr (I == 19) {
            return value.world_template_id;
        }
        else if constexpr (I == 20) {
            return value.server_enabled_client_side_generation;
        }
        else if constexpr (I == 21) {
            return value.block_network_ids_are_hashes;
        }
        else if constexpr (I == 22) {
            return value.network_permissions;
        }
        else if constexpr (I == 23) {
            return value.server_configuration_join_info;
        }
        else {
            return value.server_telemetry_data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::StartGamePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::StartGamePacket>{"StartGamePacket"};

template <>
inline constexpr std::array<std::string_view, 25> field_names_v<v2225::StartGamePacket>{{
    "entity_id",
    "runtime_id",
    "entity_game_type",
    "pos",
    "rot",
    "settings",
    "level_id",
    "level_name",
    "template_content_identity",
    "is_trial",
    "movement_settings",
    "level_current_time",
    "enchantment_seed",
    "block_properties",
    "multiplayer_correlation_id",
    "enable_item_stack_net_manager",
    "server_version",
    "player_property_data",
    "server_block_type_registry_checksum",
    "world_template_id",
    "server_enabled_client_side_generation",
    "block_network_ids_are_hashes",
    "network_permissions",
    "server_configuration_join_info",
    "server_telemetry_data",
}};

template <>
struct field_accessor<v2225::StartGamePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.entity_id;
        }
        else if constexpr (I == 1) {
            return value.runtime_id;
        }
        else if constexpr (I == 2) {
            return value.entity_game_type;
        }
        else if constexpr (I == 3) {
            return value.pos;
        }
        else if constexpr (I == 4) {
            return value.rot;
        }
        else if constexpr (I == 5) {
            return value.settings;
        }
        else if constexpr (I == 6) {
            return value.level_id;
        }
        else if constexpr (I == 7) {
            return value.level_name;
        }
        else if constexpr (I == 8) {
            return value.template_content_identity;
        }
        else if constexpr (I == 9) {
            return value.is_trial;
        }
        else if constexpr (I == 10) {
            return value.movement_settings;
        }
        else if constexpr (I == 11) {
            return value.level_current_time;
        }
        else if constexpr (I == 12) {
            return value.enchantment_seed;
        }
        else if constexpr (I == 13) {
            return value.block_properties;
        }
        else if constexpr (I == 14) {
            return value.multiplayer_correlation_id;
        }
        else if constexpr (I == 15) {
            return value.enable_item_stack_net_manager;
        }
        else if constexpr (I == 16) {
            return value.server_version;
        }
        else if constexpr (I == 17) {
            return value.player_property_data;
        }
        else if constexpr (I == 18) {
            return value.server_block_type_registry_checksum;
        }
        else if constexpr (I == 19) {
            return value.world_template_id;
        }
        else if constexpr (I == 20) {
            return value.server_enabled_client_side_generation;
        }
        else if constexpr (I == 21) {
            return value.block_network_ids_are_hashes;
        }
        else if constexpr (I == 22) {
            return value.network_permissions;
        }
        else if constexpr (I == 23) {
            return value.server_configuration_join_info;
        }
        else {
            return value.server_telemetry_data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::GameRulesChangedPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::GameRulesChangedPacket>{"GameRulesChangedPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::GameRulesChangedPacket>{{
    "rule_data",
}};

template <>
struct field_accessor<base::GameRulesChangedPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.rule_data;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v844::GameRulesChangedPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v844::GameRulesChangedPacket>{"GameRulesChangedPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v844::GameRulesChangedPacket>{{
    "rule_data",
}};

template <>
struct field_accessor<v844::GameRulesChangedPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.rule_data;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<SetCommandsEnabledPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<SetCommandsEnabledPacket>{"SetCommandsEnabledPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<SetCommandsEnabledPacket>{{
    "commands_enabled",
}};

template <>
struct field_accessor<SetCommandsEnabledPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.commands_enabled;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<SetDifficultyPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<SetDifficultyPacket>{"SetDifficultyPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<SetDifficultyPacket>{{
    "difficulty",
}};

template <>
struct field_accessor<SetDifficultyPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.difficulty;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<SetPlayerGameTypePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<SetPlayerGameTypePacket>{"SetPlayerGameTypePacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<SetPlayerGameTypePacket>{{
    "player_game_type",
}};

template <>
struct field_accessor<SetPlayerGameTypePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.player_game_type;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<ShowCreditsPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<ShowCreditsPacket>{"ShowCreditsPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<ShowCreditsPacket>{{
    "player_id",
    "credits_state",
}};

template <>
struct field_accessor<ShowCreditsPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.player_id;
        }
        else {
            return value.credits_state;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<SetDefaultGameTypePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<SetDefaultGameTypePacket>{"SetDefaultGameTypePacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<SetDefaultGameTypePacket>{{
    "default_game_type",
}};

template <>
struct field_accessor<SetDefaultGameTypePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.default_game_type;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<MultiplayerSettingsPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<MultiplayerSettingsPacket>{"MultiplayerSettingsPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<MultiplayerSettingsPacket>{{
    "packet_type",
}};

template <>
struct field_accessor<MultiplayerSettingsPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.packet_type;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<UpdatePlayerGameTypePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<UpdatePlayerGameTypePacket>{"UpdatePlayerGameTypePacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<UpdatePlayerGameTypePacket>{{
    "player_game_type",
    "target_player",
    "tick",
}};

template <>
struct field_accessor<UpdatePlayerGameTypePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.player_game_type;
        }
        else if constexpr (I == 1) {
            return value.target_player;
        }
        else {
            return value.tick;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<SimulationTypePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<SimulationTypePacket>{"SimulationTypePacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<SimulationTypePacket>{{
    "sim_type",
}};

template <>
struct field_accessor<SimulationTypePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.sim_type;
    }
};

}  // namespace detail


template <>
struct Serializer<SpawnSettings> {
    static void serialize(BinaryWriter &stream, const SpawnSettings &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<SpawnSettings, std::error_code>;
};

template <>
struct Serializer<base::GameRule> {
    static void serialize(BinaryWriter &stream, const base::GameRule &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::GameRule, std::error_code>;
};

template <>
struct Serializer<v844::GameRule> {
    static void serialize(BinaryWriter &stream, const v844::GameRule &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v844::GameRule, std::error_code>;
};

template <>
struct Serializer<base::GameRulesChangedPacketData> {
    static void serialize(BinaryWriter &stream, const base::GameRulesChangedPacketData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::GameRulesChangedPacketData, std::error_code>;
};

template <>
struct Serializer<v844::GameRulesChangedPacketData> {
    static void serialize(BinaryWriter &stream, const v844::GameRulesChangedPacketData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v844::GameRulesChangedPacketData, std::error_code>;
};

template <>
struct Serializer<ExperimentToggle> {
    static void serialize(BinaryWriter &stream, const ExperimentToggle &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<ExperimentToggle, std::error_code>;
};

template <>
struct Serializer<Experiments> {
    static void serialize(BinaryWriter &stream, const Experiments &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<Experiments, std::error_code>;
};

template <>
struct Serializer<base::SyncedPlayerMovementSettings> {
    static void serialize(BinaryWriter &stream, const base::SyncedPlayerMovementSettings &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::SyncedPlayerMovementSettings, std::error_code>;
};

template <>
struct Serializer<v818::SyncedPlayerMovementSettings> {
    static void serialize(BinaryWriter &stream, const v818::SyncedPlayerMovementSettings &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v818::SyncedPlayerMovementSettings, std::error_code>;
};

template <>
struct Serializer<BlockEntry> {
    static void serialize(BinaryWriter &stream, const BlockEntry &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<BlockEntry, std::error_code>;
};

template <>
struct Serializer<v2168::ServerBlockProperty> {
    static void serialize(BinaryWriter &stream, const v2168::ServerBlockProperty &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ServerBlockProperty, std::error_code>;
};

template <>
struct Serializer<legacy::base::GameRule> {
    static void serialize(BinaryWriter &stream, const legacy::base::GameRule &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<legacy::base::GameRule, std::error_code>;
};

template <>
struct Serializer<base::LevelSettings> {
    static void serialize(BinaryWriter &stream, const base::LevelSettings &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::LevelSettings, std::error_code>;
};

template <>
struct Serializer<v800::LevelSettings> {
    static void serialize(BinaryWriter &stream, const v800::LevelSettings &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v800::LevelSettings, std::error_code>;
};

template <>
struct Serializer<v818::LevelSettings> {
    static void serialize(BinaryWriter &stream, const v818::LevelSettings &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v818::LevelSettings, std::error_code>;
};

template <>
struct Serializer<v844::LevelSettings> {
    static void serialize(BinaryWriter &stream, const v844::LevelSettings &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v844::LevelSettings, std::error_code>;
};

template <>
struct Serializer<v924::LevelSettings> {
    static void serialize(BinaryWriter &stream, const v924::LevelSettings &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::LevelSettings, std::error_code>;
};

template <>
struct Serializer<v944::LevelSettings> {
    static void serialize(BinaryWriter &stream, const v944::LevelSettings &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::LevelSettings, std::error_code>;
};

template <>
struct Serializer<v1001::LevelSettings> {
    static void serialize(BinaryWriter &stream, const v1001::LevelSettings &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::LevelSettings, std::error_code>;
};

template <>
struct Serializer<v2168::LevelSettings> {
    static void serialize(BinaryWriter &stream, const v2168::LevelSettings &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::LevelSettings, std::error_code>;
};

template <>
struct Serializer<v2225::LevelSettings> {
    static void serialize(BinaryWriter &stream, const v2225::LevelSettings &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::LevelSettings, std::error_code>;
};

template <>
struct Serializer<base::StartGameItemEntry> {
    static void serialize(BinaryWriter &stream, const base::StartGameItemEntry &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::StartGameItemEntry, std::error_code>;
};

template <>
struct Serializer<base::StartGamePacket> {
    static void serialize(BinaryWriter &stream, const base::StartGamePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::StartGamePacket, std::error_code>;
};

template <>
struct Serializer<v776::StartGamePacket> {
    static void serialize(BinaryWriter &stream, const v776::StartGamePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v776::StartGamePacket, std::error_code>;
};

template <>
struct Serializer<v800::StartGamePacket> {
    static void serialize(BinaryWriter &stream, const v800::StartGamePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v800::StartGamePacket, std::error_code>;
};

template <>
struct Serializer<v818::StartGamePacket> {
    static void serialize(BinaryWriter &stream, const v818::StartGamePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v818::StartGamePacket, std::error_code>;
};

template <>
struct Serializer<v827::StartGamePacket> {
    static void serialize(BinaryWriter &stream, const v827::StartGamePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v827::StartGamePacket, std::error_code>;
};

template <>
struct Serializer<v844::StartGamePacket> {
    static void serialize(BinaryWriter &stream, const v844::StartGamePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v844::StartGamePacket, std::error_code>;
};

template <>
struct Serializer<v898::StartGamePacket> {
    static void serialize(BinaryWriter &stream, const v898::StartGamePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v898::StartGamePacket, std::error_code>;
};

template <>
struct Serializer<v924::StartGamePacket> {
    static void serialize(BinaryWriter &stream, const v924::StartGamePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::StartGamePacket, std::error_code>;
};

template <>
struct Serializer<v944::StartGamePacket> {
    static void serialize(BinaryWriter &stream, const v944::StartGamePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::StartGamePacket, std::error_code>;
};

template <>
struct Serializer<v1001::StartGamePacket> {
    static void serialize(BinaryWriter &stream, const v1001::StartGamePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::StartGamePacket, std::error_code>;
};

template <>
struct Serializer<v2168::StartGamePacket> {
    static void serialize(BinaryWriter &stream, const v2168::StartGamePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::StartGamePacket, std::error_code>;
};

template <>
struct Serializer<v2225::StartGamePacket> {
    static void serialize(BinaryWriter &stream, const v2225::StartGamePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::StartGamePacket, std::error_code>;
};

template <>
struct Serializer<base::GameRulesChangedPacket> {
    static void serialize(BinaryWriter &stream, const base::GameRulesChangedPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::GameRulesChangedPacket, std::error_code>;
};

template <>
struct Serializer<v844::GameRulesChangedPacket> {
    static void serialize(BinaryWriter &stream, const v844::GameRulesChangedPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v844::GameRulesChangedPacket, std::error_code>;
};

template <>
struct Serializer<SetCommandsEnabledPacket> {
    static void serialize(BinaryWriter &stream, const SetCommandsEnabledPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<SetCommandsEnabledPacket, std::error_code>;
};

template <>
struct Serializer<SetDifficultyPacket> {
    static void serialize(BinaryWriter &stream, const SetDifficultyPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<SetDifficultyPacket, std::error_code>;
};

template <>
struct Serializer<SetPlayerGameTypePacket> {
    static void serialize(BinaryWriter &stream, const SetPlayerGameTypePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<SetPlayerGameTypePacket, std::error_code>;
};

template <>
struct Serializer<ShowCreditsPacket> {
    static void serialize(BinaryWriter &stream, const ShowCreditsPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<ShowCreditsPacket, std::error_code>;
};

template <>
struct Serializer<SetDefaultGameTypePacket> {
    static void serialize(BinaryWriter &stream, const SetDefaultGameTypePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<SetDefaultGameTypePacket, std::error_code>;
};

template <>
struct Serializer<MultiplayerSettingsPacket> {
    static void serialize(BinaryWriter &stream, const MultiplayerSettingsPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<MultiplayerSettingsPacket, std::error_code>;
};

template <>
struct Serializer<UpdatePlayerGameTypePacket> {
    static void serialize(BinaryWriter &stream, const UpdatePlayerGameTypePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<UpdatePlayerGameTypePacket, std::error_code>;
};

template <>
struct Serializer<SimulationTypePacket> {
    static void serialize(BinaryWriter &stream, const SimulationTypePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<SimulationTypePacket, std::error_code>;
};
using WorldType = WorldType_<2225>;
using GameRule = GameRule_<2225>;
using GameRulesChangedPacketData = GameRulesChangedPacketData_<2225>;
using SyncedPlayerMovementSettings = SyncedPlayerMovementSettings_<2225>;
using ServerBlockProperty = ServerBlockProperty_<2225>;
using LevelSettings = LevelSettings_<2225>;
using StartGamePacket = StartGamePacket_<2225>;
using GameRulesChangedPacket = GameRulesChangedPacket_<2225>;

}  // namespace bedrock::protocol
