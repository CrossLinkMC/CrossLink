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
#include <bedrock/protocol/packet.hpp>
#include <bedrock/protocol/serializer.hpp>
#include <bedrock/protocol/stream.hpp>
#include <bedrock/protocol/uuid.hpp>

#include <bedrock/protocol/actor.h>
#include <bedrock/protocol/common.h>
#include <bedrock/protocol/network.h>

namespace bedrock::protocol {

enum class CommandPermissionLevel : std::uint8_t {
    Any = 0,
    GameDirectors = 1,
    Admin = 2,
    Host = 3,
    Owner = 4,
    Internal = 5,
};

struct SettingsCommandPacket {
    static constexpr int Id = 140;
    std::string command_string{};
    bool suppress_output{};
};

namespace AvailableCommandsPacket_nested {

struct EnumData {
    std::string name{};
    std::vector<std::uint32_t> values{};
};

struct ChainedSubcommandRelationship {
    std::uint32_t sub_command_first_value{};
    std::uint32_t sub_command_second_value{};
};

struct ChainedSubcommandData {
    std::string name{};
    std::vector<ChainedSubcommandRelationship> values{};
};

struct SoftEnumData {
    std::string name{};
    std::vector<std::string> values{};
};

struct ConstrainedValueData {
    std::uint32_t enum_value_symbol{};
    std::uint32_t enum_symbol{};
    std::vector<std::uint8_t> constraints{};
};

struct ParamData {
    std::string name{};
    std::uint32_t parse_symbol{};
    bool optional{};
    std::uint8_t param_options{};
};

struct OverloadData {
    bool is_chaining{};
    std::vector<ParamData> params{};
};

struct CommandData {
    std::string name{};
    std::string description{};
    std::uint16_t flags{};
    CommandPermissionLevel permission{};
    std::int32_t alias_enum{};
    std::vector<std::uint32_t> chained_subcommand_indexes{};
    std::vector<OverloadData> overloads{};
};

}  // namespace AvailableCommandsPacket_nested

struct AvailableCommandsPacket {
    using EnumData = AvailableCommandsPacket_nested::EnumData;
    using ChainedSubcommandRelationship = AvailableCommandsPacket_nested::ChainedSubcommandRelationship;
    using ChainedSubcommandData = AvailableCommandsPacket_nested::ChainedSubcommandData;
    using SoftEnumData = AvailableCommandsPacket_nested::SoftEnumData;
    using ConstrainedValueData = AvailableCommandsPacket_nested::ConstrainedValueData;
    using ParamData = AvailableCommandsPacket_nested::ParamData;
    using OverloadData = AvailableCommandsPacket_nested::OverloadData;
    using CommandData = AvailableCommandsPacket_nested::CommandData;

    static constexpr int Id = 76;
    std::vector<std::string> enum_values{};
    std::vector<std::string> chained_subcommand_values{};
    std::vector<std::string> postfixes{};
    std::vector<AvailableCommandsPacket::EnumData> enums{};
    std::vector<AvailableCommandsPacket::ChainedSubcommandData> chained_subcommands{};
    std::vector<AvailableCommandsPacket::CommandData> commands{};
    std::vector<AvailableCommandsPacket::SoftEnumData> soft_enums{};
    std::vector<AvailableCommandsPacket::ConstrainedValueData> constraints{};
};

enum class CommandBlockMode : std::uint16_t {
    Normal = 0,
    Repeating = 1,
    Chain = 2,
};

enum class CommandOriginType : std::uint8_t {
    Player = 0,
    CommandBlock = 1,
    MinecartCommandBlock = 2,
    DevConsole = 3,
    Test = 4,
    AutomationPlayer = 5,
    ClientAutomation = 6,
    DedicatedServer = 7,
    Entity = 8,
    Virtual = 9,
    GameArgument = 10,
    EntityServer = 11,
    Precompiled = 12,
    GameDirectorEntityServer = 13,
    Scripting = 14,
    ExecuteContext = 15,
};

struct CommandOriginData {
    CommandOriginType type{};
    UUID uuid{};
    std::string request_id{};
    ActorUniqueID player_id{};
};

enum class CommandOutputType : int {
    None = 0,
    LastOutput = 1,
    Silent = 2,
    AllOutput = 3,
    DataSet = 4,
};

struct CommandOutputMessage {
    std::string message_id{};
    bool successful{};
    std::vector<std::string> params{};
};

struct CommandOutput {
    CommandOutputType type{};
    std::uint32_t success_count{};
    std::vector<CommandOutputMessage> messages{};
    std::optional<std::string> data{};
};

struct CommandOutputPacket {
    static constexpr int Id = 79;
    CommandOriginData origin_data{};
    CommandOutput output{};
};

enum class SoftEnumUpdateType : std::uint8_t {
    Add = 0,
    Remove = 1,
    Replace = 2,
};

struct UpdateSoftEnumPacket {
    static constexpr int Id = 114;
    std::string enum_name{};
    std::vector<std::string> values{};
    SoftEnumUpdateType type{};
};

enum class PlayerPermissionLevel : std::int8_t {
    Visitor = 0,
    Member = 1,
    Operator = 2,
    Custom = 3,
};

namespace base {

namespace CommandBlockUpdatePacket_nested {

struct EntityCommandTarget {
    ActorRuntimeID entity_id{};
};

struct BlockCommandData {
    base::NetworkBlockPosition block_pos{};
    CommandBlockMode mode{};
    bool redstone_mode{};
    bool is_conditional{};
};

}  // namespace CommandBlockUpdatePacket_nested

struct CommandBlockUpdatePacket {
    using EntityCommandTarget = CommandBlockUpdatePacket_nested::EntityCommandTarget;
    using BlockCommandData = CommandBlockUpdatePacket_nested::BlockCommandData;

    static constexpr int Id = 78;
    std::variant<base::CommandBlockUpdatePacket::EntityCommandTarget, base::CommandBlockUpdatePacket::BlockCommandData> target{};
    std::string command{};
    std::string last_output{};
    std::string name{};
    bool track_output{};
    std::uint32_t tick_delay{};
    bool execute_on_first_tick{};
};

enum class CurrentCmdVersion : int {
    Invalid = -1,
    Initial = 1,
    TpRotationClamping = 2,
    NewBedrockCmdSystem = 3,
    ExecuteUsesVec3 = 4,
    CloneFixes = 5,
    UpdateAquatic = 6,
    EntitySelectorUsesVec3 = 7,
    ContainersDontDropItemsAnymore = 8,
    FiltersObeyDimensions = 9,
    ExecuteAndBlockCommandAndSelfSelectorFixes = 10,
    InstantEffectsUseTicks = 11,
    DontRegisterBrokenFunctionCommands = 12,
    ClearSpawnPointCommand = 13,
    CloneAndTeleportRotationFixes = 14,
    TeleportDimensionFixes = 15,
    CloneUpdateBlockAndTimeFixes = 16,
    CloneIntersectFix = 17,
    FunctionExecuteOrderAndChestSlotFix = 18,
    NonTickingAreasNoLongerConsideredLoaded = 19,
    SpreadplayersHazardAndResolvePlayerByNameFix = 20,
    NewExecuteCommandSyntaxExperimentAndChestLootTableFixAndTeleportFacingVerticalUnclampedAndLocateBiomeAndFeatureMerged = 21,
    WaterloggingAddedToStructureCommand = 22,
    SelectorDistanceFilteredAndRelativeRotationFix = 23,
    NewSummonCommandAddedRotationOptionsAndBubbleColumnCloneFixAndExecuteInDimensionTeleportFixAndNewExecuteRotationFix = 24,
    NewExecuteCommandReleaseEnchantCommandLevelFixAndHasItemDataFixAndCommandDeferral = 25,
    ExecuteIfScoreFixes = 26,
    ReplaceItemAndLootReplaceBlockCommandsDoNotPlaceItemsIntoCauldronsFix = 27,
    ChangesToCommandOriginRotation = 28,
    RemoveAuxValueParameterFromBlockCommands = 29,
    VolumeSelectorFixes = 30,
    EnableSummonRotation = 31,
    SummonCommandDefaultRotation = 32,
    PositionalDimensionFiltering = 33,
    CommandSelectorHasItemFilterNoLongerCallsSameItemFunction = 34,
    AgentSweepingBlockTest = 34,
    BlockStateEquals = 35,
    CommandPositionFix = 35,
    CommandSelectorHasItemFilterUsesDataAsDamageForSelectingDamageableItems = 36,
    ExecuteDetectConditionSubcommandNotAllowNonLoadedBlocks = 37,
    RemoveSuicideKeyword = 38,
    CloneContainerBlockEntityRemovalFix = 39,
    StopSoundMusicFix = 40,
    SpreadPlayersStuckInGroundFixAndMaxHeightParameter = 41,
    LocateStructureOutput = 42,
    Count = 43,
    Latest = Count - 1,
};

struct CommandRequestPacket {
    static constexpr int Id = 77;
    std::string command{};
    CommandOriginData origin{};
    bool internal_source{};
    base::CurrentCmdVersion version{};
};

}  // namespace base

namespace v748 {

using CommandBlockUpdatePacket = base::CommandBlockUpdatePacket;

using CurrentCmdVersion = base::CurrentCmdVersion;

using CommandRequestPacket = base::CommandRequestPacket;

}  // namespace v748

namespace v766 {

using CommandBlockUpdatePacket = base::CommandBlockUpdatePacket;

using CurrentCmdVersion = base::CurrentCmdVersion;

using CommandRequestPacket = base::CommandRequestPacket;

}  // namespace v766

namespace v776 {

namespace CommandBlockUpdatePacket_nested {

using EntityCommandTarget = base::CommandBlockUpdatePacket::EntityCommandTarget;

struct BlockCommandData {
    base::NetworkBlockPosition block_pos{};
    CommandBlockMode mode{};
    bool redstone_mode{};
    bool is_conditional{};
};

}  // namespace CommandBlockUpdatePacket_nested

struct CommandBlockUpdatePacket {
    using EntityCommandTarget = CommandBlockUpdatePacket_nested::EntityCommandTarget;
    using BlockCommandData = CommandBlockUpdatePacket_nested::BlockCommandData;

    static constexpr int Id = 78;
    std::variant<v776::CommandBlockUpdatePacket::EntityCommandTarget, v776::CommandBlockUpdatePacket::BlockCommandData> target{};
    std::string command{};
    std::string last_output{};
    std::string name{};
    std::string filtered_name{};
    bool track_output{};
    std::uint32_t tick_delay{};
    bool execute_on_first_tick{};
};

using CurrentCmdVersion = base::CurrentCmdVersion;

using CommandRequestPacket = base::CommandRequestPacket;

}  // namespace v776

namespace v786 {

using CommandBlockUpdatePacket = v776::CommandBlockUpdatePacket;

enum class CurrentCmdVersion : int {
    Invalid = -1,
    Initial = 1,
    TpRotationClamping = 2,
    NewBedrockCmdSystem = 3,
    ExecuteUsesVec3 = 4,
    CloneFixes = 5,
    UpdateAquatic = 6,
    EntitySelectorUsesVec3 = 7,
    ContainersDontDropItemsAnymore = 8,
    FiltersObeyDimensions = 9,
    ExecuteAndBlockCommandAndSelfSelectorFixes = 10,
    InstantEffectsUseTicks = 11,
    DontRegisterBrokenFunctionCommands = 12,
    ClearSpawnPointCommand = 13,
    CloneAndTeleportRotationFixes = 14,
    TeleportDimensionFixes = 15,
    CloneUpdateBlockAndTimeFixes = 16,
    CloneIntersectFix = 17,
    FunctionExecuteOrderAndChestSlotFix = 18,
    NonTickingAreasNoLongerConsideredLoaded = 19,
    SpreadplayersHazardAndResolvePlayerByNameFix = 20,
    NewExecuteCommandSyntaxExperimentAndChestLootTableFixAndTeleportFacingVerticalUnclampedAndLocateBiomeAndFeatureMerged = 21,
    WaterloggingAddedToStructureCommand = 22,
    SelectorDistanceFilteredAndRelativeRotationFix = 23,
    NewSummonCommandAddedRotationOptionsAndBubbleColumnCloneFixAndExecuteInDimensionTeleportFixAndNewExecuteRotationFix = 24,
    NewExecuteCommandReleaseEnchantCommandLevelFixAndHasItemDataFixAndCommandDeferral = 25,
    ExecuteIfScoreFixes = 26,
    ReplaceItemAndLootReplaceBlockCommandsDoNotPlaceItemsIntoCauldronsFix = 27,
    ChangesToCommandOriginRotation = 28,
    RemoveAuxValueParameterFromBlockCommands = 29,
    VolumeSelectorFixes = 30,
    EnableSummonRotation = 31,
    SummonCommandDefaultRotation = 32,
    PositionalDimensionFiltering = 33,
    CommandSelectorHasItemFilterNoLongerCallsSameItemFunction = 34,
    AgentSweepingBlockTest = 34,
    BlockStateEquals = 35,
    CommandPositionFix = 35,
    CommandSelectorHasItemFilterUsesDataAsDamageForSelectingDamageableItems = 36,
    ExecuteDetectConditionSubcommandNotAllowNonLoadedBlocks = 37,
    RemoveSuicideKeyword = 38,
    CloneContainerBlockEntityRemovalFix = 39,
    StopSoundMusicFix = 40,
    SpreadPlayersStuckInGroundFixAndMaxHeightParameter = 41,
    LocateStructureOutput = 42,
    PostBlockFlattening = 43,
    Count = 44,
    Latest = Count - 1,
};

struct CommandRequestPacket {
    static constexpr int Id = 77;
    std::string command{};
    CommandOriginData origin{};
    bool internal_source{};
    v786::CurrentCmdVersion version{};
};

}  // namespace v786

namespace v800 {

using CommandBlockUpdatePacket = v776::CommandBlockUpdatePacket;

using CurrentCmdVersion = v786::CurrentCmdVersion;

using CommandRequestPacket = v786::CommandRequestPacket;

}  // namespace v800

namespace v818 {

using CommandBlockUpdatePacket = v776::CommandBlockUpdatePacket;

enum class CurrentCmdVersion : int {
    Invalid = -1,
    Initial = 1,
    TpRotationClamping = 2,
    NewBedrockCmdSystem = 3,
    ExecuteUsesVec3 = 4,
    CloneFixes = 5,
    UpdateAquatic = 6,
    EntitySelectorUsesVec3 = 7,
    ContainersDontDropItemsAnymore = 8,
    FiltersObeyDimensions = 9,
    ExecuteAndBlockCommandAndSelfSelectorFixes = 10,
    InstantEffectsUseTicks = 11,
    DontRegisterBrokenFunctionCommands = 12,
    ClearSpawnPointCommand = 13,
    CloneAndTeleportRotationFixes = 14,
    TeleportDimensionFixes = 15,
    CloneUpdateBlockAndTimeFixes = 16,
    CloneIntersectFix = 17,
    FunctionExecuteOrderAndChestSlotFix = 18,
    NonTickingAreasNoLongerConsideredLoaded = 19,
    SpreadplayersHazardAndResolvePlayerByNameFix = 20,
    NewExecuteCommandSyntaxExperimentAndChestLootTableFixAndTeleportFacingVerticalUnclampedAndLocateBiomeAndFeatureMerged = 21,
    WaterloggingAddedToStructureCommand = 22,
    SelectorDistanceFilteredAndRelativeRotationFix = 23,
    NewSummonCommandAddedRotationOptionsAndBubbleColumnCloneFixAndExecuteInDimensionTeleportFixAndNewExecuteRotationFix = 24,
    NewExecuteCommandReleaseEnchantCommandLevelFixAndHasItemDataFixAndCommandDeferral = 25,
    ExecuteIfScoreFixes = 26,
    ReplaceItemAndLootReplaceBlockCommandsDoNotPlaceItemsIntoCauldronsFix = 27,
    ChangesToCommandOriginRotation = 28,
    RemoveAuxValueParameterFromBlockCommands = 29,
    VolumeSelectorFixes = 30,
    EnableSummonRotation = 31,
    SummonCommandDefaultRotation = 32,
    PositionalDimensionFiltering = 33,
    CommandSelectorHasItemFilterNoLongerCallsSameItemFunction = 34,
    AgentSweepingBlockTest = 34,
    BlockStateEquals = 35,
    CommandPositionFix = 35,
    CommandSelectorHasItemFilterUsesDataAsDamageForSelectingDamageableItems = 36,
    ExecuteDetectConditionSubcommandNotAllowNonLoadedBlocks = 37,
    RemoveSuicideKeyword = 38,
    CloneContainerBlockEntityRemovalFix = 39,
    StopSoundMusicFix = 40,
    SpreadPlayersStuckInGroundFixAndMaxHeightParameter = 41,
    LocateStructureOutput = 42,
    PostBlockFlattening = 43,
    TestForBlockCommandDoesNotIgnoreBlockState = 44,
    Count = 45,
    Latest = Count - 1,
};

struct CommandRequestPacket {
    static constexpr int Id = 77;
    std::string command{};
    CommandOriginData origin{};
    bool internal_source{};
    v818::CurrentCmdVersion version{};
};

}  // namespace v818

namespace v827 {

using CommandBlockUpdatePacket = v776::CommandBlockUpdatePacket;

using CurrentCmdVersion = v818::CurrentCmdVersion;

using CommandRequestPacket = v818::CommandRequestPacket;

}  // namespace v827

namespace v844 {

using CommandBlockUpdatePacket = v776::CommandBlockUpdatePacket;

using CurrentCmdVersion = v818::CurrentCmdVersion;

using CommandRequestPacket = v818::CommandRequestPacket;

}  // namespace v844

namespace v859 {

using CommandBlockUpdatePacket = v776::CommandBlockUpdatePacket;

using CurrentCmdVersion = v818::CurrentCmdVersion;

using CommandRequestPacket = v818::CommandRequestPacket;

}  // namespace v859

namespace v898 {

using CommandBlockUpdatePacket = v776::CommandBlockUpdatePacket;

enum class CurrentCmdVersion : int {
    Invalid = -1,
    Initial = 1,
    TpRotationClamping = 2,
    NewBedrockCmdSystem = 3,
    ExecuteUsesVec3 = 4,
    CloneFixes = 5,
    UpdateAquatic = 6,
    EntitySelectorUsesVec3 = 7,
    ContainersDontDropItemsAnymore = 8,
    FiltersObeyDimensions = 9,
    ExecuteAndBlockCommandAndSelfSelectorFixes = 10,
    InstantEffectsUseTicks = 11,
    DontRegisterBrokenFunctionCommands = 12,
    ClearSpawnPointCommand = 13,
    CloneAndTeleportRotationFixes = 14,
    TeleportDimensionFixes = 15,
    CloneUpdateBlockAndTimeFixes = 16,
    CloneIntersectFix = 17,
    FunctionExecuteOrderAndChestSlotFix = 18,
    NonTickingAreasNoLongerConsideredLoaded = 19,
    SpreadplayersHazardAndResolvePlayerByNameFix = 20,
    NewExecuteCommandSyntaxExperimentAndChestLootTableFixAndTeleportFacingVerticalUnclampedAndLocateBiomeAndFeatureMerged = 21,
    WaterloggingAddedToStructureCommand = 22,
    SelectorDistanceFilteredAndRelativeRotationFix = 23,
    NewSummonCommandAddedRotationOptionsAndBubbleColumnCloneFixAndExecuteInDimensionTeleportFixAndNewExecuteRotationFix = 24,
    NewExecuteCommandReleaseEnchantCommandLevelFixAndHasItemDataFixAndCommandDeferral = 25,
    ExecuteIfScoreFixes = 26,
    ReplaceItemAndLootReplaceBlockCommandsDoNotPlaceItemsIntoCauldronsFix = 27,
    ChangesToCommandOriginRotation = 28,
    RemoveAuxValueParameterFromBlockCommands = 29,
    VolumeSelectorFixes = 30,
    EnableSummonRotation = 31,
    SummonCommandDefaultRotation = 32,
    PositionalDimensionFiltering = 33,
    CommandSelectorHasItemFilterNoLongerCallsSameItemFunction = 34,
    AgentSweepingBlockTest = 34,
    BlockStateEquals = 35,
    CommandPositionFix = 35,
    CommandSelectorHasItemFilterUsesDataAsDamageForSelectingDamageableItems = 36,
    ExecuteDetectConditionSubcommandNotAllowNonLoadedBlocks = 37,
    RemoveSuicideKeyword = 38,
    CloneContainerBlockEntityRemovalFix = 39,
    StopSoundMusicFix = 40,
    SpreadPlayersStuckInGroundFixAndMaxHeightParameter = 41,
    LocateStructureOutput = 42,
    PostBlockFlattening = 43,
    TestForBlockCommandDoesNotIgnoreBlockState = 44,
    CloneExtraBlockFilterFix = 45,
    Count = 46,
    Latest = Count - 1,
};

struct CommandRequestPacket {
    static constexpr int Id = 77;
    std::string command{};
    CommandOriginData origin{};
    bool internal_source{};
    v898::CurrentCmdVersion version{};
};

}  // namespace v898

namespace v924 {

using CommandBlockUpdatePacket = v776::CommandBlockUpdatePacket;

using CurrentCmdVersion = v898::CurrentCmdVersion;

using CommandRequestPacket = v898::CommandRequestPacket;

}  // namespace v924

namespace v944 {

namespace CommandBlockUpdatePacket_nested {

using EntityCommandTarget = base::CommandBlockUpdatePacket::EntityCommandTarget;

struct BlockCommandData {
    BlockPos block_pos{};
    CommandBlockMode mode{};
    bool redstone_mode{};
    bool is_conditional{};
};

}  // namespace CommandBlockUpdatePacket_nested

struct CommandBlockUpdatePacket {
    using EntityCommandTarget = CommandBlockUpdatePacket_nested::EntityCommandTarget;
    using BlockCommandData = CommandBlockUpdatePacket_nested::BlockCommandData;

    static constexpr int Id = 78;
    std::variant<v944::CommandBlockUpdatePacket::EntityCommandTarget, v944::CommandBlockUpdatePacket::BlockCommandData> target{};
    std::string command{};
    std::string last_output{};
    std::string name{};
    std::string filtered_name{};
    bool track_output{};
    std::uint32_t tick_delay{};
    bool execute_on_first_tick{};
};

using CurrentCmdVersion = v898::CurrentCmdVersion;

using CommandRequestPacket = v898::CommandRequestPacket;

}  // namespace v944

namespace v975 {

using CommandBlockUpdatePacket = v944::CommandBlockUpdatePacket;

enum class CurrentCmdVersion : int {
    Invalid = -1,
    Initial = 1,
    TpRotationClamping = 2,
    NewBedrockCmdSystem = 3,
    ExecuteUsesVec3 = 4,
    CloneFixes = 5,
    UpdateAquatic = 6,
    EntitySelectorUsesVec3 = 7,
    ContainersDontDropItemsAnymore = 8,
    FiltersObeyDimensions = 9,
    ExecuteAndBlockCommandAndSelfSelectorFixes = 10,
    InstantEffectsUseTicks = 11,
    DontRegisterBrokenFunctionCommands = 12,
    ClearSpawnPointCommand = 13,
    CloneAndTeleportRotationFixes = 14,
    TeleportDimensionFixes = 15,
    CloneUpdateBlockAndTimeFixes = 16,
    CloneIntersectFix = 17,
    FunctionExecuteOrderAndChestSlotFix = 18,
    NonTickingAreasNoLongerConsideredLoaded = 19,
    SpreadplayersHazardAndResolvePlayerByNameFix = 20,
    NewExecuteCommandSyntaxExperimentAndChestLootTableFixAndTeleportFacingVerticalUnclampedAndLocateBiomeAndFeatureMerged = 21,
    WaterloggingAddedToStructureCommand = 22,
    SelectorDistanceFilteredAndRelativeRotationFix = 23,
    NewSummonCommandAddedRotationOptionsAndBubbleColumnCloneFixAndExecuteInDimensionTeleportFixAndNewExecuteRotationFix = 24,
    NewExecuteCommandReleaseEnchantCommandLevelFixAndHasItemDataFixAndCommandDeferral = 25,
    ExecuteIfScoreFixes = 26,
    ReplaceItemAndLootReplaceBlockCommandsDoNotPlaceItemsIntoCauldronsFix = 27,
    ChangesToCommandOriginRotation = 28,
    RemoveAuxValueParameterFromBlockCommands = 29,
    VolumeSelectorFixes = 30,
    EnableSummonRotation = 31,
    SummonCommandDefaultRotation = 32,
    PositionalDimensionFiltering = 33,
    CommandSelectorHasItemFilterNoLongerCallsSameItemFunction = 34,
    AgentSweepingBlockTest = 34,
    BlockStateEquals = 35,
    CommandPositionFix = 35,
    CommandSelectorHasItemFilterUsesDataAsDamageForSelectingDamageableItems = 36,
    ExecuteDetectConditionSubcommandNotAllowNonLoadedBlocks = 37,
    RemoveSuicideKeyword = 38,
    CloneContainerBlockEntityRemovalFix = 39,
    StopSoundMusicFix = 40,
    SpreadPlayersStuckInGroundFixAndMaxHeightParameter = 41,
    LocateStructureOutput = 42,
    PostBlockFlattening = 43,
    TestForBlockCommandDoesNotIgnoreBlockState = 44,
    CloneExtraBlockFilterFix = 45,
    FillCommandUnfillableErrorOutput = 46,
    Count = 47,
    Latest = Count - 1,
};

struct CommandRequestPacket {
    static constexpr int Id = 77;
    std::string command{};
    CommandOriginData origin{};
    bool internal_source{};
    v975::CurrentCmdVersion version{};
};

}  // namespace v975

namespace v1001 {

using CommandBlockUpdatePacket = v944::CommandBlockUpdatePacket;

enum class CurrentCmdVersion : int {
    Invalid = -1,
    Initial = 1,
    TpRotationClamping = 2,
    NewBedrockCmdSystem = 3,
    ExecuteUsesVec3 = 4,
    CloneFixes = 5,
    UpdateAquatic = 6,
    EntitySelectorUsesVec3 = 7,
    ContainersDontDropItemsAnymore = 8,
    FiltersObeyDimensions = 9,
    ExecuteAndBlockCommandAndSelfSelectorFixes = 10,
    InstantEffectsUseTicks = 11,
    DontRegisterBrokenFunctionCommands = 12,
    ClearSpawnPointCommand = 13,
    CloneAndTeleportRotationFixes = 14,
    TeleportDimensionFixes = 15,
    CloneUpdateBlockAndTimeFixes = 16,
    CloneIntersectFix = 17,
    FunctionExecuteOrderAndChestSlotFix = 18,
    NonTickingAreasNoLongerConsideredLoaded = 19,
    SpreadplayersHazardAndResolvePlayerByNameFix = 20,
    NewExecuteCommandSyntaxExperimentAndChestLootTableFixAndTeleportFacingVerticalUnclampedAndLocateBiomeAndFeatureMerged = 21,
    WaterloggingAddedToStructureCommand = 22,
    SelectorDistanceFilteredAndRelativeRotationFix = 23,
    NewSummonCommandAddedRotationOptionsAndBubbleColumnCloneFixAndExecuteInDimensionTeleportFixAndNewExecuteRotationFix = 24,
    NewExecuteCommandReleaseEnchantCommandLevelFixAndHasItemDataFixAndCommandDeferral = 25,
    ExecuteIfScoreFixes = 26,
    ReplaceItemAndLootReplaceBlockCommandsDoNotPlaceItemsIntoCauldronsFix = 27,
    ChangesToCommandOriginRotation = 28,
    RemoveAuxValueParameterFromBlockCommands = 29,
    VolumeSelectorFixes = 30,
    EnableSummonRotation = 31,
    SummonCommandDefaultRotation = 32,
    PositionalDimensionFiltering = 33,
    CommandSelectorHasItemFilterNoLongerCallsSameItemFunction = 34,
    AgentSweepingBlockTest = 34,
    BlockStateEquals = 35,
    CommandPositionFix = 35,
    CommandSelectorHasItemFilterUsesDataAsDamageForSelectingDamageableItems = 36,
    ExecuteDetectConditionSubcommandNotAllowNonLoadedBlocks = 37,
    RemoveSuicideKeyword = 38,
    CloneContainerBlockEntityRemovalFix = 39,
    StopSoundMusicFix = 40,
    SpreadPlayersStuckInGroundFixAndMaxHeightParameter = 41,
    LocateStructureOutput = 42,
    PostBlockFlattening = 43,
    TestForBlockCommandDoesNotIgnoreBlockState = 44,
    CloneExtraBlockFilterFix = 45,
    FillCommandUnfillableErrorOutput = 46,
    StopSoundOutputFix = 47,
    PlaySoundOutputFix = 48,
    PlayerWaypointsGamerule = 49,
    Count = 50,
    Latest = Count - 1,
};

struct CommandRequestPacket {
    static constexpr int Id = 77;
    std::string command{};
    CommandOriginData origin{};
    bool internal_source{};
    v1001::CurrentCmdVersion version{};
};

}  // namespace v1001

namespace v2168 {

namespace CommandBlockUpdatePacket_nested {

using EntityCommandTarget = base::CommandBlockUpdatePacket::EntityCommandTarget;

struct BlockCommandData {
    BlockPos block_pos{};
    CommandBlockMode mode{};
    bool redstone_mode{};
    bool is_conditional{};
};

}  // namespace CommandBlockUpdatePacket_nested

struct CommandBlockUpdatePacket {
    using EntityCommandTarget = CommandBlockUpdatePacket_nested::EntityCommandTarget;
    using BlockCommandData = CommandBlockUpdatePacket_nested::BlockCommandData;

    static constexpr int Id = 78;
    std::variant<v2168::CommandBlockUpdatePacket::EntityCommandTarget, v2168::CommandBlockUpdatePacket::BlockCommandData> target{};
    std::string command{};
    std::string last_output{};
    std::string name{};
    std::string filtered_name{};
    bool track_output{};
    std::int32_t tick_delay{};
    bool execute_on_first_tick{};
};

enum class CurrentCmdVersion : int {
    Invalid = -1,
    Initial = 1,
    TpRotationClamping = 2,
    NewBedrockCmdSystem = 3,
    ExecuteUsesVec3 = 4,
    CloneFixes = 5,
    UpdateAquatic = 6,
    EntitySelectorUsesVec3 = 7,
    ContainersDontDropItemsAnymore = 8,
    FiltersObeyDimensions = 9,
    ExecuteAndBlockCommandAndSelfSelectorFixes = 10,
    InstantEffectsUseTicks = 11,
    DontRegisterBrokenFunctionCommands = 12,
    ClearSpawnPointCommand = 13,
    CloneAndTeleportRotationFixes = 14,
    TeleportDimensionFixes = 15,
    CloneUpdateBlockAndTimeFixes = 16,
    CloneIntersectFix = 17,
    FunctionExecuteOrderAndChestSlotFix = 18,
    NonTickingAreasNoLongerConsideredLoaded = 19,
    SpreadplayersHazardAndResolvePlayerByNameFix = 20,
    NewExecuteCommandSyntaxExperimentAndChestLootTableFixAndTeleportFacingVerticalUnclampedAndLocateBiomeAndFeatureMerged = 21,
    WaterloggingAddedToStructureCommand = 22,
    SelectorDistanceFilteredAndRelativeRotationFix = 23,
    NewSummonCommandAddedRotationOptionsAndBubbleColumnCloneFixAndExecuteInDimensionTeleportFixAndNewExecuteRotationFix = 24,
    NewExecuteCommandReleaseEnchantCommandLevelFixAndHasItemDataFixAndCommandDeferral = 25,
    ExecuteIfScoreFixes = 26,
    ReplaceItemAndLootReplaceBlockCommandsDoNotPlaceItemsIntoCauldronsFix = 27,
    ChangesToCommandOriginRotation = 28,
    RemoveAuxValueParameterFromBlockCommands = 29,
    VolumeSelectorFixes = 30,
    EnableSummonRotation = 31,
    SummonCommandDefaultRotation = 32,
    PositionalDimensionFiltering = 33,
    CommandSelectorHasItemFilterNoLongerCallsSameItemFunction = 34,
    AgentSweepingBlockTest = 34,
    BlockStateEquals = 35,
    CommandPositionFix = 35,
    CommandSelectorHasItemFilterUsesDataAsDamageForSelectingDamageableItems = 36,
    ExecuteDetectConditionSubcommandNotAllowNonLoadedBlocks = 37,
    RemoveSuicideKeyword = 38,
    CloneContainerBlockEntityRemovalFix = 39,
    StopSoundMusicFix = 40,
    SpreadPlayersStuckInGroundFixAndMaxHeightParameter = 41,
    LocateStructureOutput = 42,
    PostBlockFlattening = 43,
    TestForBlockCommandDoesNotIgnoreBlockState = 44,
    CloneExtraBlockFilterFix = 45,
    FillCommandUnfillableErrorOutput = 46,
    StopSoundOutputFix = 47,
    PlaySoundOutputFix = 48,
    PlayerWaypointsGamerule = 49,
    ClonePartialBedBlockFix = 50,
    Count = 51,
    Latest = Count - 1,
};

struct CommandRequestPacket {
    static constexpr int Id = 77;
    std::string command{};
    CommandOriginData origin{};
    bool internal_source{};
    v2168::CurrentCmdVersion version{};
};

}  // namespace v2168

namespace v2193 {

using CommandBlockUpdatePacket = v2168::CommandBlockUpdatePacket;

enum class CurrentCmdVersion : int {
    Invalid = -1,
    Initial = 1,
    TpRotationClamping = 2,
    NewBedrockCmdSystem = 3,
    ExecuteUsesVec3 = 4,
    CloneFixes = 5,
    UpdateAquatic = 6,
    EntitySelectorUsesVec3 = 7,
    ContainersDontDropItemsAnymore = 8,
    FiltersObeyDimensions = 9,
    ExecuteAndBlockCommandAndSelfSelectorFixes = 10,
    InstantEffectsUseTicks = 11,
    DontRegisterBrokenFunctionCommands = 12,
    ClearSpawnPointCommand = 13,
    CloneAndTeleportRotationFixes = 14,
    TeleportDimensionFixes = 15,
    CloneUpdateBlockAndTimeFixes = 16,
    CloneIntersectFix = 17,
    FunctionExecuteOrderAndChestSlotFix = 18,
    NonTickingAreasNoLongerConsideredLoaded = 19,
    SpreadplayersHazardAndResolvePlayerByNameFix = 20,
    NewExecuteCommandSyntaxExperimentAndChestLootTableFixAndTeleportFacingVerticalUnclampedAndLocateBiomeAndFeatureMerged = 21,
    WaterloggingAddedToStructureCommand = 22,
    SelectorDistanceFilteredAndRelativeRotationFix = 23,
    NewSummonCommandAddedRotationOptionsAndBubbleColumnCloneFixAndExecuteInDimensionTeleportFixAndNewExecuteRotationFix = 24,
    NewExecuteCommandReleaseEnchantCommandLevelFixAndHasItemDataFixAndCommandDeferral = 25,
    ExecuteIfScoreFixes = 26,
    ReplaceItemAndLootReplaceBlockCommandsDoNotPlaceItemsIntoCauldronsFix = 27,
    ChangesToCommandOriginRotation = 28,
    RemoveAuxValueParameterFromBlockCommands = 29,
    VolumeSelectorFixes = 30,
    EnableSummonRotation = 31,
    SummonCommandDefaultRotation = 32,
    PositionalDimensionFiltering = 33,
    CommandSelectorHasItemFilterNoLongerCallsSameItemFunction = 34,
    AgentSweepingBlockTest = 34,
    BlockStateEquals = 35,
    CommandPositionFix = 35,
    CommandSelectorHasItemFilterUsesDataAsDamageForSelectingDamageableItems = 36,
    ExecuteDetectConditionSubcommandNotAllowNonLoadedBlocks = 37,
    RemoveSuicideKeyword = 38,
    CloneContainerBlockEntityRemovalFix = 39,
    StopSoundMusicFix = 40,
    SpreadPlayersStuckInGroundFixAndMaxHeightParameter = 41,
    LocateStructureOutput = 42,
    PostBlockFlattening = 43,
    TestForBlockCommandDoesNotIgnoreBlockState = 44,
    CloneExtraBlockFilterFix = 45,
    FillCommandUnfillableErrorOutput = 46,
    StopSoundOutputFix = 47,
    PlaySoundOutputFix = 48,
    PlayerWaypointsGamerule = 49,
    ClonePartialBedBlockFix = 50,
    TeleportEntityDimensionPositionFix = 51,
    TimeOfCommandOverloads = 52,
    Count = 53,
    Latest = Count - 1,
};

struct CommandRequestPacket {
    static constexpr int Id = 77;
    std::string command{};
    CommandOriginData origin{};
    bool internal_source{};
    v2193::CurrentCmdVersion version{};
};

}  // namespace v2193

namespace v2225 {

using CommandBlockUpdatePacket = v2168::CommandBlockUpdatePacket;

enum class CurrentCmdVersion : int {
    Invalid = -1,
    Initial = 1,
    TpRotationClamping = 2,
    NewBedrockCmdSystem = 3,
    ExecuteUsesVec3 = 4,
    CloneFixes = 5,
    UpdateAquatic = 6,
    EntitySelectorUsesVec3 = 7,
    ContainersDontDropItemsAnymore = 8,
    FiltersObeyDimensions = 9,
    ExecuteAndBlockCommandAndSelfSelectorFixes = 10,
    InstantEffectsUseTicks = 11,
    DontRegisterBrokenFunctionCommands = 12,
    ClearSpawnPointCommand = 13,
    CloneAndTeleportRotationFixes = 14,
    TeleportDimensionFixes = 15,
    CloneUpdateBlockAndTimeFixes = 16,
    CloneIntersectFix = 17,
    FunctionExecuteOrderAndChestSlotFix = 18,
    NonTickingAreasNoLongerConsideredLoaded = 19,
    SpreadplayersHazardAndResolvePlayerByNameFix = 20,
    NewExecuteCommandSyntaxExperimentAndChestLootTableFixAndTeleportFacingVerticalUnclampedAndLocateBiomeAndFeatureMerged = 21,
    WaterloggingAddedToStructureCommand = 22,
    SelectorDistanceFilteredAndRelativeRotationFix = 23,
    NewSummonCommandAddedRotationOptionsAndBubbleColumnCloneFixAndExecuteInDimensionTeleportFixAndNewExecuteRotationFix = 24,
    NewExecuteCommandReleaseEnchantCommandLevelFixAndHasItemDataFixAndCommandDeferral = 25,
    ExecuteIfScoreFixes = 26,
    ReplaceItemAndLootReplaceBlockCommandsDoNotPlaceItemsIntoCauldronsFix = 27,
    ChangesToCommandOriginRotation = 28,
    RemoveAuxValueParameterFromBlockCommands = 29,
    VolumeSelectorFixes = 30,
    EnableSummonRotation = 31,
    SummonCommandDefaultRotation = 32,
    PositionalDimensionFiltering = 33,
    CommandSelectorHasItemFilterNoLongerCallsSameItemFunction = 34,
    AgentSweepingBlockTest = 34,
    BlockStateEquals = 35,
    CommandPositionFix = 35,
    CommandSelectorHasItemFilterUsesDataAsDamageForSelectingDamageableItems = 36,
    ExecuteDetectConditionSubcommandNotAllowNonLoadedBlocks = 37,
    RemoveSuicideKeyword = 38,
    CloneContainerBlockEntityRemovalFix = 39,
    StopSoundMusicFix = 40,
    SpreadPlayersStuckInGroundFixAndMaxHeightParameter = 41,
    LocateStructureOutput = 42,
    PostBlockFlattening = 43,
    TestForBlockCommandDoesNotIgnoreBlockState = 44,
    CloneExtraBlockFilterFix = 45,
    FillCommandUnfillableErrorOutput = 46,
    StopSoundOutputFix = 47,
    PlaySoundOutputFix = 48,
    PlayerWaypointsGamerule = 49,
    ClonePartialBedBlockFix = 50,
    TeleportEntityDimensionPositionFix = 51,
    TimeOfCommandOverloads = 52,
    Unknown053 = 53,
    Unknown054 = 54,
    Unknown055 = 55,
    Count = 56,
    Latest = Count - 1,
};

struct CommandRequestPacket {
    static constexpr int Id = 77;
    std::string command{};
    CommandOriginData origin{};
    bool internal_source{};
    v2225::CurrentCmdVersion version{};
};

}  // namespace v2225

namespace detail {

template <int V>
struct CommandBlockUpdatePacket_;

template <int V> requires (V < 776)
struct CommandBlockUpdatePacket_<V> { using type = base::CommandBlockUpdatePacket; };

template <int V> requires (V >= 776 && V < 944)
struct CommandBlockUpdatePacket_<V> { using type = v776::CommandBlockUpdatePacket; };

template <int V> requires (V >= 944 && V < 2168)
struct CommandBlockUpdatePacket_<V> { using type = v944::CommandBlockUpdatePacket; };

template <int V> requires (V >= 2168)
struct CommandBlockUpdatePacket_<V> { using type = v2168::CommandBlockUpdatePacket; };

template <int V>
struct CurrentCmdVersion_;

template <int V> requires (V < 786)
struct CurrentCmdVersion_<V> { using type = base::CurrentCmdVersion; };

template <int V> requires (V >= 786 && V < 818)
struct CurrentCmdVersion_<V> { using type = v786::CurrentCmdVersion; };

template <int V> requires (V >= 818 && V < 898)
struct CurrentCmdVersion_<V> { using type = v818::CurrentCmdVersion; };

template <int V> requires (V >= 898 && V < 975)
struct CurrentCmdVersion_<V> { using type = v898::CurrentCmdVersion; };

template <int V> requires (V >= 975 && V < 1001)
struct CurrentCmdVersion_<V> { using type = v975::CurrentCmdVersion; };

template <int V> requires (V >= 1001 && V < 2168)
struct CurrentCmdVersion_<V> { using type = v1001::CurrentCmdVersion; };

template <int V> requires (V >= 2168 && V < 2193)
struct CurrentCmdVersion_<V> { using type = v2168::CurrentCmdVersion; };

template <int V> requires (V >= 2193 && V < 2225)
struct CurrentCmdVersion_<V> { using type = v2193::CurrentCmdVersion; };

template <int V> requires (V >= 2225)
struct CurrentCmdVersion_<V> { using type = v2225::CurrentCmdVersion; };

template <int V>
struct CommandRequestPacket_;

template <int V> requires (V < 786)
struct CommandRequestPacket_<V> { using type = base::CommandRequestPacket; };

template <int V> requires (V >= 786 && V < 818)
struct CommandRequestPacket_<V> { using type = v786::CommandRequestPacket; };

template <int V> requires (V >= 818 && V < 898)
struct CommandRequestPacket_<V> { using type = v818::CommandRequestPacket; };

template <int V> requires (V >= 898 && V < 975)
struct CommandRequestPacket_<V> { using type = v898::CommandRequestPacket; };

template <int V> requires (V >= 975 && V < 1001)
struct CommandRequestPacket_<V> { using type = v975::CommandRequestPacket; };

template <int V> requires (V >= 1001 && V < 2168)
struct CommandRequestPacket_<V> { using type = v1001::CommandRequestPacket; };

template <int V> requires (V >= 2168 && V < 2193)
struct CommandRequestPacket_<V> { using type = v2168::CommandRequestPacket; };

template <int V> requires (V >= 2193 && V < 2225)
struct CommandRequestPacket_<V> { using type = v2193::CommandRequestPacket; };

template <int V> requires (V >= 2225)
struct CommandRequestPacket_<V> { using type = v2225::CommandRequestPacket; };

}  // namespace detail

template <int V> using CommandBlockUpdatePacket_ = typename detail::CommandBlockUpdatePacket_<V>::type;
template <int V> using CurrentCmdVersion_ = typename detail::CurrentCmdVersion_<V>::type;
template <int V> using CommandRequestPacket_ = typename detail::CommandRequestPacket_<V>::type;

template <int V>
struct packet_of<V, 76> { using type = AvailableCommandsPacket; };

template <int V>
struct packet_of<V, 77> { using type = CommandRequestPacket_<V>; };

template <int V>
struct packet_of<V, 78> { using type = CommandBlockUpdatePacket_<V>; };

template <int V>
struct packet_of<V, 79> { using type = CommandOutputPacket; };

template <int V>
struct packet_of<V, 114> { using type = UpdateSoftEnumPacket; };

template <int V>
struct packet_of<V, 140> { using type = SettingsCommandPacket; };

namespace detail {

template <>
inline constexpr std::array<CommandPermissionLevel, 6> values_v<CommandPermissionLevel>{{
    CommandPermissionLevel::Any,
    CommandPermissionLevel::GameDirectors,
    CommandPermissionLevel::Admin,
    CommandPermissionLevel::Host,
    CommandPermissionLevel::Owner,
    CommandPermissionLevel::Internal,
}};

template <>
inline constexpr std::array<std::string_view, 6> names_v<CommandPermissionLevel>{{
    "any",
    "gamedirectors",
    "admin",
    "host",
    "owner",
    "internal",
}};

template <>
inline constexpr std::string_view type_name_v<CommandPermissionLevel>{"CommandPermissionLevel"};

template <>
inline constexpr std::array<CommandBlockMode, 3> values_v<CommandBlockMode>{{
    CommandBlockMode::Normal,
    CommandBlockMode::Repeating,
    CommandBlockMode::Chain,
}};

template <>
inline constexpr std::array<std::string_view, 3> names_v<CommandBlockMode>{{
    "normal",
    "repeating",
    "chain",
}};

template <>
inline constexpr std::string_view type_name_v<CommandBlockMode>{"CommandBlockMode"};

template <>
inline constexpr std::array<CommandOriginType, 16> values_v<CommandOriginType>{{
    CommandOriginType::Player,
    CommandOriginType::CommandBlock,
    CommandOriginType::MinecartCommandBlock,
    CommandOriginType::DevConsole,
    CommandOriginType::Test,
    CommandOriginType::AutomationPlayer,
    CommandOriginType::ClientAutomation,
    CommandOriginType::DedicatedServer,
    CommandOriginType::Entity,
    CommandOriginType::Virtual,
    CommandOriginType::GameArgument,
    CommandOriginType::EntityServer,
    CommandOriginType::Precompiled,
    CommandOriginType::GameDirectorEntityServer,
    CommandOriginType::Scripting,
    CommandOriginType::ExecuteContext,
}};

template <>
inline constexpr std::array<std::string_view, 16> names_v<CommandOriginType>{{
    "player",
    "commandblock",
    "minecartcommandblock",
    "devconsole",
    "test",
    "automationplayer",
    "clientautomation",
    "dedicatedserver",
    "entity",
    "virtual",
    "gameargument",
    "entityserver",
    "precompiled",
    "gamedirectorentityserver",
    "scripting",
    "executecontext",
}};

template <>
inline constexpr std::string_view type_name_v<CommandOriginType>{"CommandOriginType"};

template <>
inline constexpr std::array<base::CurrentCmdVersion, 47> values_v<base::CurrentCmdVersion>{{
    base::CurrentCmdVersion::Latest,
    base::CurrentCmdVersion::Invalid,
    base::CurrentCmdVersion::Initial,
    base::CurrentCmdVersion::TpRotationClamping,
    base::CurrentCmdVersion::NewBedrockCmdSystem,
    base::CurrentCmdVersion::ExecuteUsesVec3,
    base::CurrentCmdVersion::CloneFixes,
    base::CurrentCmdVersion::UpdateAquatic,
    base::CurrentCmdVersion::EntitySelectorUsesVec3,
    base::CurrentCmdVersion::ContainersDontDropItemsAnymore,
    base::CurrentCmdVersion::FiltersObeyDimensions,
    base::CurrentCmdVersion::ExecuteAndBlockCommandAndSelfSelectorFixes,
    base::CurrentCmdVersion::InstantEffectsUseTicks,
    base::CurrentCmdVersion::DontRegisterBrokenFunctionCommands,
    base::CurrentCmdVersion::ClearSpawnPointCommand,
    base::CurrentCmdVersion::CloneAndTeleportRotationFixes,
    base::CurrentCmdVersion::TeleportDimensionFixes,
    base::CurrentCmdVersion::CloneUpdateBlockAndTimeFixes,
    base::CurrentCmdVersion::CloneIntersectFix,
    base::CurrentCmdVersion::FunctionExecuteOrderAndChestSlotFix,
    base::CurrentCmdVersion::NonTickingAreasNoLongerConsideredLoaded,
    base::CurrentCmdVersion::SpreadplayersHazardAndResolvePlayerByNameFix,
    base::CurrentCmdVersion::NewExecuteCommandSyntaxExperimentAndChestLootTableFixAndTeleportFacingVerticalUnclampedAndLocateBiomeAndFeatureMerged,
    base::CurrentCmdVersion::WaterloggingAddedToStructureCommand,
    base::CurrentCmdVersion::SelectorDistanceFilteredAndRelativeRotationFix,
    base::CurrentCmdVersion::NewSummonCommandAddedRotationOptionsAndBubbleColumnCloneFixAndExecuteInDimensionTeleportFixAndNewExecuteRotationFix,
    base::CurrentCmdVersion::NewExecuteCommandReleaseEnchantCommandLevelFixAndHasItemDataFixAndCommandDeferral,
    base::CurrentCmdVersion::ExecuteIfScoreFixes,
    base::CurrentCmdVersion::ReplaceItemAndLootReplaceBlockCommandsDoNotPlaceItemsIntoCauldronsFix,
    base::CurrentCmdVersion::ChangesToCommandOriginRotation,
    base::CurrentCmdVersion::RemoveAuxValueParameterFromBlockCommands,
    base::CurrentCmdVersion::VolumeSelectorFixes,
    base::CurrentCmdVersion::EnableSummonRotation,
    base::CurrentCmdVersion::SummonCommandDefaultRotation,
    base::CurrentCmdVersion::PositionalDimensionFiltering,
    base::CurrentCmdVersion::CommandSelectorHasItemFilterNoLongerCallsSameItemFunction,
    base::CurrentCmdVersion::AgentSweepingBlockTest,
    base::CurrentCmdVersion::BlockStateEquals,
    base::CurrentCmdVersion::CommandPositionFix,
    base::CurrentCmdVersion::CommandSelectorHasItemFilterUsesDataAsDamageForSelectingDamageableItems,
    base::CurrentCmdVersion::ExecuteDetectConditionSubcommandNotAllowNonLoadedBlocks,
    base::CurrentCmdVersion::RemoveSuicideKeyword,
    base::CurrentCmdVersion::CloneContainerBlockEntityRemovalFix,
    base::CurrentCmdVersion::StopSoundMusicFix,
    base::CurrentCmdVersion::SpreadPlayersStuckInGroundFixAndMaxHeightParameter,
    base::CurrentCmdVersion::LocateStructureOutput,
    base::CurrentCmdVersion::Count,
}};

template <>
inline constexpr std::array<std::string_view, 47> names_v<base::CurrentCmdVersion>{{
    "latest",
    "invalid",
    "initial",
    "tprotationclamping",
    "newbedrockcmdsystem",
    "executeusesvec3",
    "clonefixes",
    "updateaquatic",
    "entityselectorusesvec3",
    "containersdontdropitemsanymore",
    "filtersobeydimensions",
    "executeandblockcommandandselfselectorfixes",
    "instanteffectsuseticks",
    "dontregisterbrokenfunctioncommands",
    "clearspawnpointcommand",
    "cloneandteleportrotationfixes",
    "teleportdimensionfixes",
    "cloneupdateblockandtimefixes",
    "cloneintersectfix",
    "functionexecuteorderandchestslotfix",
    "nontickingareasnolongerconsideredloaded",
    "spreadplayershazardandresolveplayerbynamefix",
    "newexecutecommandsyntaxexperimentandchestloottablefixandteleportfacingverticalunclampedandlocatebiomeandfeaturemerged",
    "waterloggingaddedtostructurecommand",
    "selectordistancefilteredandrelativerotationfix",
    "newsummoncommandaddedrotationoptionsandbubblecolumnclonefixandexecuteindimensionteleportfixandnewexecuterotationfix",
    "newexecutecommandreleaseenchantcommandlevelfixandhasitemdatafixandcommanddeferral",
    "executeifscorefixes",
    "replaceitemandlootreplaceblockcommandsdonotplaceitemsintocauldronsfix",
    "changestocommandoriginrotation",
    "removeauxvalueparameterfromblockcommands",
    "volumeselectorfixes",
    "enablesummonrotation",
    "summoncommanddefaultrotation",
    "positionaldimensionfiltering",
    "commandselectorhasitemfilternolongercallssameitemfunction",
    "agentsweepingblocktest",
    "blockstateequals",
    "commandpositionfix",
    "commandselectorhasitemfilterusesdataasdamageforselectingdamageableitems",
    "executedetectconditionsubcommandnotallownonloadedblocks",
    "removesuicidekeyword",
    "clonecontainerblockentityremovalfix",
    "stopsoundmusicfix",
    "spreadplayersstuckingroundfixandmaxheightparameter",
    "locatestructureoutput",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<base::CurrentCmdVersion>{"CurrentCmdVersion"};

template <>
inline constexpr std::array<v786::CurrentCmdVersion, 48> values_v<v786::CurrentCmdVersion>{{
    v786::CurrentCmdVersion::Latest,
    v786::CurrentCmdVersion::Invalid,
    v786::CurrentCmdVersion::Initial,
    v786::CurrentCmdVersion::TpRotationClamping,
    v786::CurrentCmdVersion::NewBedrockCmdSystem,
    v786::CurrentCmdVersion::ExecuteUsesVec3,
    v786::CurrentCmdVersion::CloneFixes,
    v786::CurrentCmdVersion::UpdateAquatic,
    v786::CurrentCmdVersion::EntitySelectorUsesVec3,
    v786::CurrentCmdVersion::ContainersDontDropItemsAnymore,
    v786::CurrentCmdVersion::FiltersObeyDimensions,
    v786::CurrentCmdVersion::ExecuteAndBlockCommandAndSelfSelectorFixes,
    v786::CurrentCmdVersion::InstantEffectsUseTicks,
    v786::CurrentCmdVersion::DontRegisterBrokenFunctionCommands,
    v786::CurrentCmdVersion::ClearSpawnPointCommand,
    v786::CurrentCmdVersion::CloneAndTeleportRotationFixes,
    v786::CurrentCmdVersion::TeleportDimensionFixes,
    v786::CurrentCmdVersion::CloneUpdateBlockAndTimeFixes,
    v786::CurrentCmdVersion::CloneIntersectFix,
    v786::CurrentCmdVersion::FunctionExecuteOrderAndChestSlotFix,
    v786::CurrentCmdVersion::NonTickingAreasNoLongerConsideredLoaded,
    v786::CurrentCmdVersion::SpreadplayersHazardAndResolvePlayerByNameFix,
    v786::CurrentCmdVersion::NewExecuteCommandSyntaxExperimentAndChestLootTableFixAndTeleportFacingVerticalUnclampedAndLocateBiomeAndFeatureMerged,
    v786::CurrentCmdVersion::WaterloggingAddedToStructureCommand,
    v786::CurrentCmdVersion::SelectorDistanceFilteredAndRelativeRotationFix,
    v786::CurrentCmdVersion::NewSummonCommandAddedRotationOptionsAndBubbleColumnCloneFixAndExecuteInDimensionTeleportFixAndNewExecuteRotationFix,
    v786::CurrentCmdVersion::NewExecuteCommandReleaseEnchantCommandLevelFixAndHasItemDataFixAndCommandDeferral,
    v786::CurrentCmdVersion::ExecuteIfScoreFixes,
    v786::CurrentCmdVersion::ReplaceItemAndLootReplaceBlockCommandsDoNotPlaceItemsIntoCauldronsFix,
    v786::CurrentCmdVersion::ChangesToCommandOriginRotation,
    v786::CurrentCmdVersion::RemoveAuxValueParameterFromBlockCommands,
    v786::CurrentCmdVersion::VolumeSelectorFixes,
    v786::CurrentCmdVersion::EnableSummonRotation,
    v786::CurrentCmdVersion::SummonCommandDefaultRotation,
    v786::CurrentCmdVersion::PositionalDimensionFiltering,
    v786::CurrentCmdVersion::CommandSelectorHasItemFilterNoLongerCallsSameItemFunction,
    v786::CurrentCmdVersion::AgentSweepingBlockTest,
    v786::CurrentCmdVersion::BlockStateEquals,
    v786::CurrentCmdVersion::CommandPositionFix,
    v786::CurrentCmdVersion::CommandSelectorHasItemFilterUsesDataAsDamageForSelectingDamageableItems,
    v786::CurrentCmdVersion::ExecuteDetectConditionSubcommandNotAllowNonLoadedBlocks,
    v786::CurrentCmdVersion::RemoveSuicideKeyword,
    v786::CurrentCmdVersion::CloneContainerBlockEntityRemovalFix,
    v786::CurrentCmdVersion::StopSoundMusicFix,
    v786::CurrentCmdVersion::SpreadPlayersStuckInGroundFixAndMaxHeightParameter,
    v786::CurrentCmdVersion::LocateStructureOutput,
    v786::CurrentCmdVersion::PostBlockFlattening,
    v786::CurrentCmdVersion::Count,
}};

template <>
inline constexpr std::array<std::string_view, 48> names_v<v786::CurrentCmdVersion>{{
    "latest",
    "invalid",
    "initial",
    "tprotationclamping",
    "newbedrockcmdsystem",
    "executeusesvec3",
    "clonefixes",
    "updateaquatic",
    "entityselectorusesvec3",
    "containersdontdropitemsanymore",
    "filtersobeydimensions",
    "executeandblockcommandandselfselectorfixes",
    "instanteffectsuseticks",
    "dontregisterbrokenfunctioncommands",
    "clearspawnpointcommand",
    "cloneandteleportrotationfixes",
    "teleportdimensionfixes",
    "cloneupdateblockandtimefixes",
    "cloneintersectfix",
    "functionexecuteorderandchestslotfix",
    "nontickingareasnolongerconsideredloaded",
    "spreadplayershazardandresolveplayerbynamefix",
    "newexecutecommandsyntaxexperimentandchestloottablefixandteleportfacingverticalunclampedandlocatebiomeandfeaturemerged",
    "waterloggingaddedtostructurecommand",
    "selectordistancefilteredandrelativerotationfix",
    "newsummoncommandaddedrotationoptionsandbubblecolumnclonefixandexecuteindimensionteleportfixandnewexecuterotationfix",
    "newexecutecommandreleaseenchantcommandlevelfixandhasitemdatafixandcommanddeferral",
    "executeifscorefixes",
    "replaceitemandlootreplaceblockcommandsdonotplaceitemsintocauldronsfix",
    "changestocommandoriginrotation",
    "removeauxvalueparameterfromblockcommands",
    "volumeselectorfixes",
    "enablesummonrotation",
    "summoncommanddefaultrotation",
    "positionaldimensionfiltering",
    "commandselectorhasitemfilternolongercallssameitemfunction",
    "agentsweepingblocktest",
    "blockstateequals",
    "commandpositionfix",
    "commandselectorhasitemfilterusesdataasdamageforselectingdamageableitems",
    "executedetectconditionsubcommandnotallownonloadedblocks",
    "removesuicidekeyword",
    "clonecontainerblockentityremovalfix",
    "stopsoundmusicfix",
    "spreadplayersstuckingroundfixandmaxheightparameter",
    "locatestructureoutput",
    "postblockflattening",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<v786::CurrentCmdVersion>{"CurrentCmdVersion"};

template <>
inline constexpr std::array<v818::CurrentCmdVersion, 49> values_v<v818::CurrentCmdVersion>{{
    v818::CurrentCmdVersion::Latest,
    v818::CurrentCmdVersion::Invalid,
    v818::CurrentCmdVersion::Initial,
    v818::CurrentCmdVersion::TpRotationClamping,
    v818::CurrentCmdVersion::NewBedrockCmdSystem,
    v818::CurrentCmdVersion::ExecuteUsesVec3,
    v818::CurrentCmdVersion::CloneFixes,
    v818::CurrentCmdVersion::UpdateAquatic,
    v818::CurrentCmdVersion::EntitySelectorUsesVec3,
    v818::CurrentCmdVersion::ContainersDontDropItemsAnymore,
    v818::CurrentCmdVersion::FiltersObeyDimensions,
    v818::CurrentCmdVersion::ExecuteAndBlockCommandAndSelfSelectorFixes,
    v818::CurrentCmdVersion::InstantEffectsUseTicks,
    v818::CurrentCmdVersion::DontRegisterBrokenFunctionCommands,
    v818::CurrentCmdVersion::ClearSpawnPointCommand,
    v818::CurrentCmdVersion::CloneAndTeleportRotationFixes,
    v818::CurrentCmdVersion::TeleportDimensionFixes,
    v818::CurrentCmdVersion::CloneUpdateBlockAndTimeFixes,
    v818::CurrentCmdVersion::CloneIntersectFix,
    v818::CurrentCmdVersion::FunctionExecuteOrderAndChestSlotFix,
    v818::CurrentCmdVersion::NonTickingAreasNoLongerConsideredLoaded,
    v818::CurrentCmdVersion::SpreadplayersHazardAndResolvePlayerByNameFix,
    v818::CurrentCmdVersion::NewExecuteCommandSyntaxExperimentAndChestLootTableFixAndTeleportFacingVerticalUnclampedAndLocateBiomeAndFeatureMerged,
    v818::CurrentCmdVersion::WaterloggingAddedToStructureCommand,
    v818::CurrentCmdVersion::SelectorDistanceFilteredAndRelativeRotationFix,
    v818::CurrentCmdVersion::NewSummonCommandAddedRotationOptionsAndBubbleColumnCloneFixAndExecuteInDimensionTeleportFixAndNewExecuteRotationFix,
    v818::CurrentCmdVersion::NewExecuteCommandReleaseEnchantCommandLevelFixAndHasItemDataFixAndCommandDeferral,
    v818::CurrentCmdVersion::ExecuteIfScoreFixes,
    v818::CurrentCmdVersion::ReplaceItemAndLootReplaceBlockCommandsDoNotPlaceItemsIntoCauldronsFix,
    v818::CurrentCmdVersion::ChangesToCommandOriginRotation,
    v818::CurrentCmdVersion::RemoveAuxValueParameterFromBlockCommands,
    v818::CurrentCmdVersion::VolumeSelectorFixes,
    v818::CurrentCmdVersion::EnableSummonRotation,
    v818::CurrentCmdVersion::SummonCommandDefaultRotation,
    v818::CurrentCmdVersion::PositionalDimensionFiltering,
    v818::CurrentCmdVersion::CommandSelectorHasItemFilterNoLongerCallsSameItemFunction,
    v818::CurrentCmdVersion::AgentSweepingBlockTest,
    v818::CurrentCmdVersion::BlockStateEquals,
    v818::CurrentCmdVersion::CommandPositionFix,
    v818::CurrentCmdVersion::CommandSelectorHasItemFilterUsesDataAsDamageForSelectingDamageableItems,
    v818::CurrentCmdVersion::ExecuteDetectConditionSubcommandNotAllowNonLoadedBlocks,
    v818::CurrentCmdVersion::RemoveSuicideKeyword,
    v818::CurrentCmdVersion::CloneContainerBlockEntityRemovalFix,
    v818::CurrentCmdVersion::StopSoundMusicFix,
    v818::CurrentCmdVersion::SpreadPlayersStuckInGroundFixAndMaxHeightParameter,
    v818::CurrentCmdVersion::LocateStructureOutput,
    v818::CurrentCmdVersion::PostBlockFlattening,
    v818::CurrentCmdVersion::TestForBlockCommandDoesNotIgnoreBlockState,
    v818::CurrentCmdVersion::Count,
}};

template <>
inline constexpr std::array<std::string_view, 49> names_v<v818::CurrentCmdVersion>{{
    "latest",
    "invalid",
    "initial",
    "tprotationclamping",
    "newbedrockcmdsystem",
    "executeusesvec3",
    "clonefixes",
    "updateaquatic",
    "entityselectorusesvec3",
    "containersdontdropitemsanymore",
    "filtersobeydimensions",
    "executeandblockcommandandselfselectorfixes",
    "instanteffectsuseticks",
    "dontregisterbrokenfunctioncommands",
    "clearspawnpointcommand",
    "cloneandteleportrotationfixes",
    "teleportdimensionfixes",
    "cloneupdateblockandtimefixes",
    "cloneintersectfix",
    "functionexecuteorderandchestslotfix",
    "nontickingareasnolongerconsideredloaded",
    "spreadplayershazardandresolveplayerbynamefix",
    "newexecutecommandsyntaxexperimentandchestloottablefixandteleportfacingverticalunclampedandlocatebiomeandfeaturemerged",
    "waterloggingaddedtostructurecommand",
    "selectordistancefilteredandrelativerotationfix",
    "newsummoncommandaddedrotationoptionsandbubblecolumnclonefixandexecuteindimensionteleportfixandnewexecuterotationfix",
    "newexecutecommandreleaseenchantcommandlevelfixandhasitemdatafixandcommanddeferral",
    "executeifscorefixes",
    "replaceitemandlootreplaceblockcommandsdonotplaceitemsintocauldronsfix",
    "changestocommandoriginrotation",
    "removeauxvalueparameterfromblockcommands",
    "volumeselectorfixes",
    "enablesummonrotation",
    "summoncommanddefaultrotation",
    "positionaldimensionfiltering",
    "commandselectorhasitemfilternolongercallssameitemfunction",
    "agentsweepingblocktest",
    "blockstateequals",
    "commandpositionfix",
    "commandselectorhasitemfilterusesdataasdamageforselectingdamageableitems",
    "executedetectconditionsubcommandnotallownonloadedblocks",
    "removesuicidekeyword",
    "clonecontainerblockentityremovalfix",
    "stopsoundmusicfix",
    "spreadplayersstuckingroundfixandmaxheightparameter",
    "locatestructureoutput",
    "postblockflattening",
    "testforblockcommanddoesnotignoreblockstate",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<v818::CurrentCmdVersion>{"CurrentCmdVersion"};

template <>
inline constexpr std::array<v898::CurrentCmdVersion, 50> values_v<v898::CurrentCmdVersion>{{
    v898::CurrentCmdVersion::Latest,
    v898::CurrentCmdVersion::Invalid,
    v898::CurrentCmdVersion::Initial,
    v898::CurrentCmdVersion::TpRotationClamping,
    v898::CurrentCmdVersion::NewBedrockCmdSystem,
    v898::CurrentCmdVersion::ExecuteUsesVec3,
    v898::CurrentCmdVersion::CloneFixes,
    v898::CurrentCmdVersion::UpdateAquatic,
    v898::CurrentCmdVersion::EntitySelectorUsesVec3,
    v898::CurrentCmdVersion::ContainersDontDropItemsAnymore,
    v898::CurrentCmdVersion::FiltersObeyDimensions,
    v898::CurrentCmdVersion::ExecuteAndBlockCommandAndSelfSelectorFixes,
    v898::CurrentCmdVersion::InstantEffectsUseTicks,
    v898::CurrentCmdVersion::DontRegisterBrokenFunctionCommands,
    v898::CurrentCmdVersion::ClearSpawnPointCommand,
    v898::CurrentCmdVersion::CloneAndTeleportRotationFixes,
    v898::CurrentCmdVersion::TeleportDimensionFixes,
    v898::CurrentCmdVersion::CloneUpdateBlockAndTimeFixes,
    v898::CurrentCmdVersion::CloneIntersectFix,
    v898::CurrentCmdVersion::FunctionExecuteOrderAndChestSlotFix,
    v898::CurrentCmdVersion::NonTickingAreasNoLongerConsideredLoaded,
    v898::CurrentCmdVersion::SpreadplayersHazardAndResolvePlayerByNameFix,
    v898::CurrentCmdVersion::NewExecuteCommandSyntaxExperimentAndChestLootTableFixAndTeleportFacingVerticalUnclampedAndLocateBiomeAndFeatureMerged,
    v898::CurrentCmdVersion::WaterloggingAddedToStructureCommand,
    v898::CurrentCmdVersion::SelectorDistanceFilteredAndRelativeRotationFix,
    v898::CurrentCmdVersion::NewSummonCommandAddedRotationOptionsAndBubbleColumnCloneFixAndExecuteInDimensionTeleportFixAndNewExecuteRotationFix,
    v898::CurrentCmdVersion::NewExecuteCommandReleaseEnchantCommandLevelFixAndHasItemDataFixAndCommandDeferral,
    v898::CurrentCmdVersion::ExecuteIfScoreFixes,
    v898::CurrentCmdVersion::ReplaceItemAndLootReplaceBlockCommandsDoNotPlaceItemsIntoCauldronsFix,
    v898::CurrentCmdVersion::ChangesToCommandOriginRotation,
    v898::CurrentCmdVersion::RemoveAuxValueParameterFromBlockCommands,
    v898::CurrentCmdVersion::VolumeSelectorFixes,
    v898::CurrentCmdVersion::EnableSummonRotation,
    v898::CurrentCmdVersion::SummonCommandDefaultRotation,
    v898::CurrentCmdVersion::PositionalDimensionFiltering,
    v898::CurrentCmdVersion::CommandSelectorHasItemFilterNoLongerCallsSameItemFunction,
    v898::CurrentCmdVersion::AgentSweepingBlockTest,
    v898::CurrentCmdVersion::BlockStateEquals,
    v898::CurrentCmdVersion::CommandPositionFix,
    v898::CurrentCmdVersion::CommandSelectorHasItemFilterUsesDataAsDamageForSelectingDamageableItems,
    v898::CurrentCmdVersion::ExecuteDetectConditionSubcommandNotAllowNonLoadedBlocks,
    v898::CurrentCmdVersion::RemoveSuicideKeyword,
    v898::CurrentCmdVersion::CloneContainerBlockEntityRemovalFix,
    v898::CurrentCmdVersion::StopSoundMusicFix,
    v898::CurrentCmdVersion::SpreadPlayersStuckInGroundFixAndMaxHeightParameter,
    v898::CurrentCmdVersion::LocateStructureOutput,
    v898::CurrentCmdVersion::PostBlockFlattening,
    v898::CurrentCmdVersion::TestForBlockCommandDoesNotIgnoreBlockState,
    v898::CurrentCmdVersion::CloneExtraBlockFilterFix,
    v898::CurrentCmdVersion::Count,
}};

template <>
inline constexpr std::array<std::string_view, 50> names_v<v898::CurrentCmdVersion>{{
    "latest",
    "invalid",
    "initial",
    "tprotationclamping",
    "newbedrockcmdsystem",
    "executeusesvec3",
    "clonefixes",
    "updateaquatic",
    "entityselectorusesvec3",
    "containersdontdropitemsanymore",
    "filtersobeydimensions",
    "executeandblockcommandandselfselectorfixes",
    "instanteffectsuseticks",
    "dontregisterbrokenfunctioncommands",
    "clearspawnpointcommand",
    "cloneandteleportrotationfixes",
    "teleportdimensionfixes",
    "cloneupdateblockandtimefixes",
    "cloneintersectfix",
    "functionexecuteorderandchestslotfix",
    "nontickingareasnolongerconsideredloaded",
    "spreadplayershazardandresolveplayerbynamefix",
    "newexecutecommandsyntaxexperimentandchestloottablefixandteleportfacingverticalunclampedandlocatebiomeandfeaturemerged",
    "waterloggingaddedtostructurecommand",
    "selectordistancefilteredandrelativerotationfix",
    "newsummoncommandaddedrotationoptionsandbubblecolumnclonefixandexecuteindimensionteleportfixandnewexecuterotationfix",
    "newexecutecommandreleaseenchantcommandlevelfixandhasitemdatafixandcommanddeferral",
    "executeifscorefixes",
    "replaceitemandlootreplaceblockcommandsdonotplaceitemsintocauldronsfix",
    "changestocommandoriginrotation",
    "removeauxvalueparameterfromblockcommands",
    "volumeselectorfixes",
    "enablesummonrotation",
    "summoncommanddefaultrotation",
    "positionaldimensionfiltering",
    "commandselectorhasitemfilternolongercallssameitemfunction",
    "agentsweepingblocktest",
    "blockstateequals",
    "commandpositionfix",
    "commandselectorhasitemfilterusesdataasdamageforselectingdamageableitems",
    "executedetectconditionsubcommandnotallownonloadedblocks",
    "removesuicidekeyword",
    "clonecontainerblockentityremovalfix",
    "stopsoundmusicfix",
    "spreadplayersstuckingroundfixandmaxheightparameter",
    "locatestructureoutput",
    "postblockflattening",
    "testforblockcommanddoesnotignoreblockstate",
    "cloneextrablockfilterfix",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<v898::CurrentCmdVersion>{"CurrentCmdVersion"};

template <>
inline constexpr std::array<v975::CurrentCmdVersion, 51> values_v<v975::CurrentCmdVersion>{{
    v975::CurrentCmdVersion::Latest,
    v975::CurrentCmdVersion::Invalid,
    v975::CurrentCmdVersion::Initial,
    v975::CurrentCmdVersion::TpRotationClamping,
    v975::CurrentCmdVersion::NewBedrockCmdSystem,
    v975::CurrentCmdVersion::ExecuteUsesVec3,
    v975::CurrentCmdVersion::CloneFixes,
    v975::CurrentCmdVersion::UpdateAquatic,
    v975::CurrentCmdVersion::EntitySelectorUsesVec3,
    v975::CurrentCmdVersion::ContainersDontDropItemsAnymore,
    v975::CurrentCmdVersion::FiltersObeyDimensions,
    v975::CurrentCmdVersion::ExecuteAndBlockCommandAndSelfSelectorFixes,
    v975::CurrentCmdVersion::InstantEffectsUseTicks,
    v975::CurrentCmdVersion::DontRegisterBrokenFunctionCommands,
    v975::CurrentCmdVersion::ClearSpawnPointCommand,
    v975::CurrentCmdVersion::CloneAndTeleportRotationFixes,
    v975::CurrentCmdVersion::TeleportDimensionFixes,
    v975::CurrentCmdVersion::CloneUpdateBlockAndTimeFixes,
    v975::CurrentCmdVersion::CloneIntersectFix,
    v975::CurrentCmdVersion::FunctionExecuteOrderAndChestSlotFix,
    v975::CurrentCmdVersion::NonTickingAreasNoLongerConsideredLoaded,
    v975::CurrentCmdVersion::SpreadplayersHazardAndResolvePlayerByNameFix,
    v975::CurrentCmdVersion::NewExecuteCommandSyntaxExperimentAndChestLootTableFixAndTeleportFacingVerticalUnclampedAndLocateBiomeAndFeatureMerged,
    v975::CurrentCmdVersion::WaterloggingAddedToStructureCommand,
    v975::CurrentCmdVersion::SelectorDistanceFilteredAndRelativeRotationFix,
    v975::CurrentCmdVersion::NewSummonCommandAddedRotationOptionsAndBubbleColumnCloneFixAndExecuteInDimensionTeleportFixAndNewExecuteRotationFix,
    v975::CurrentCmdVersion::NewExecuteCommandReleaseEnchantCommandLevelFixAndHasItemDataFixAndCommandDeferral,
    v975::CurrentCmdVersion::ExecuteIfScoreFixes,
    v975::CurrentCmdVersion::ReplaceItemAndLootReplaceBlockCommandsDoNotPlaceItemsIntoCauldronsFix,
    v975::CurrentCmdVersion::ChangesToCommandOriginRotation,
    v975::CurrentCmdVersion::RemoveAuxValueParameterFromBlockCommands,
    v975::CurrentCmdVersion::VolumeSelectorFixes,
    v975::CurrentCmdVersion::EnableSummonRotation,
    v975::CurrentCmdVersion::SummonCommandDefaultRotation,
    v975::CurrentCmdVersion::PositionalDimensionFiltering,
    v975::CurrentCmdVersion::CommandSelectorHasItemFilterNoLongerCallsSameItemFunction,
    v975::CurrentCmdVersion::AgentSweepingBlockTest,
    v975::CurrentCmdVersion::BlockStateEquals,
    v975::CurrentCmdVersion::CommandPositionFix,
    v975::CurrentCmdVersion::CommandSelectorHasItemFilterUsesDataAsDamageForSelectingDamageableItems,
    v975::CurrentCmdVersion::ExecuteDetectConditionSubcommandNotAllowNonLoadedBlocks,
    v975::CurrentCmdVersion::RemoveSuicideKeyword,
    v975::CurrentCmdVersion::CloneContainerBlockEntityRemovalFix,
    v975::CurrentCmdVersion::StopSoundMusicFix,
    v975::CurrentCmdVersion::SpreadPlayersStuckInGroundFixAndMaxHeightParameter,
    v975::CurrentCmdVersion::LocateStructureOutput,
    v975::CurrentCmdVersion::PostBlockFlattening,
    v975::CurrentCmdVersion::TestForBlockCommandDoesNotIgnoreBlockState,
    v975::CurrentCmdVersion::CloneExtraBlockFilterFix,
    v975::CurrentCmdVersion::FillCommandUnfillableErrorOutput,
    v975::CurrentCmdVersion::Count,
}};

template <>
inline constexpr std::array<std::string_view, 51> names_v<v975::CurrentCmdVersion>{{
    "latest",
    "invalid",
    "initial",
    "tprotationclamping",
    "newbedrockcmdsystem",
    "executeusesvec3",
    "clonefixes",
    "updateaquatic",
    "entityselectorusesvec3",
    "containersdontdropitemsanymore",
    "filtersobeydimensions",
    "executeandblockcommandandselfselectorfixes",
    "instanteffectsuseticks",
    "dontregisterbrokenfunctioncommands",
    "clearspawnpointcommand",
    "cloneandteleportrotationfixes",
    "teleportdimensionfixes",
    "cloneupdateblockandtimefixes",
    "cloneintersectfix",
    "functionexecuteorderandchestslotfix",
    "nontickingareasnolongerconsideredloaded",
    "spreadplayershazardandresolveplayerbynamefix",
    "newexecutecommandsyntaxexperimentandchestloottablefixandteleportfacingverticalunclampedandlocatebiomeandfeaturemerged",
    "waterloggingaddedtostructurecommand",
    "selectordistancefilteredandrelativerotationfix",
    "newsummoncommandaddedrotationoptionsandbubblecolumnclonefixandexecuteindimensionteleportfixandnewexecuterotationfix",
    "newexecutecommandreleaseenchantcommandlevelfixandhasitemdatafixandcommanddeferral",
    "executeifscorefixes",
    "replaceitemandlootreplaceblockcommandsdonotplaceitemsintocauldronsfix",
    "changestocommandoriginrotation",
    "removeauxvalueparameterfromblockcommands",
    "volumeselectorfixes",
    "enablesummonrotation",
    "summoncommanddefaultrotation",
    "positionaldimensionfiltering",
    "commandselectorhasitemfilternolongercallssameitemfunction",
    "agentsweepingblocktest",
    "blockstateequals",
    "commandpositionfix",
    "commandselectorhasitemfilterusesdataasdamageforselectingdamageableitems",
    "executedetectconditionsubcommandnotallownonloadedblocks",
    "removesuicidekeyword",
    "clonecontainerblockentityremovalfix",
    "stopsoundmusicfix",
    "spreadplayersstuckingroundfixandmaxheightparameter",
    "locatestructureoutput",
    "postblockflattening",
    "testforblockcommanddoesnotignoreblockstate",
    "cloneextrablockfilterfix",
    "fillcommandunfillableerroroutput",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<v975::CurrentCmdVersion>{"CurrentCmdVersion"};

template <>
inline constexpr std::array<v1001::CurrentCmdVersion, 54> values_v<v1001::CurrentCmdVersion>{{
    v1001::CurrentCmdVersion::Latest,
    v1001::CurrentCmdVersion::Invalid,
    v1001::CurrentCmdVersion::Initial,
    v1001::CurrentCmdVersion::TpRotationClamping,
    v1001::CurrentCmdVersion::NewBedrockCmdSystem,
    v1001::CurrentCmdVersion::ExecuteUsesVec3,
    v1001::CurrentCmdVersion::CloneFixes,
    v1001::CurrentCmdVersion::UpdateAquatic,
    v1001::CurrentCmdVersion::EntitySelectorUsesVec3,
    v1001::CurrentCmdVersion::ContainersDontDropItemsAnymore,
    v1001::CurrentCmdVersion::FiltersObeyDimensions,
    v1001::CurrentCmdVersion::ExecuteAndBlockCommandAndSelfSelectorFixes,
    v1001::CurrentCmdVersion::InstantEffectsUseTicks,
    v1001::CurrentCmdVersion::DontRegisterBrokenFunctionCommands,
    v1001::CurrentCmdVersion::ClearSpawnPointCommand,
    v1001::CurrentCmdVersion::CloneAndTeleportRotationFixes,
    v1001::CurrentCmdVersion::TeleportDimensionFixes,
    v1001::CurrentCmdVersion::CloneUpdateBlockAndTimeFixes,
    v1001::CurrentCmdVersion::CloneIntersectFix,
    v1001::CurrentCmdVersion::FunctionExecuteOrderAndChestSlotFix,
    v1001::CurrentCmdVersion::NonTickingAreasNoLongerConsideredLoaded,
    v1001::CurrentCmdVersion::SpreadplayersHazardAndResolvePlayerByNameFix,
    v1001::CurrentCmdVersion::NewExecuteCommandSyntaxExperimentAndChestLootTableFixAndTeleportFacingVerticalUnclampedAndLocateBiomeAndFeatureMerged,
    v1001::CurrentCmdVersion::WaterloggingAddedToStructureCommand,
    v1001::CurrentCmdVersion::SelectorDistanceFilteredAndRelativeRotationFix,
    v1001::CurrentCmdVersion::NewSummonCommandAddedRotationOptionsAndBubbleColumnCloneFixAndExecuteInDimensionTeleportFixAndNewExecuteRotationFix,
    v1001::CurrentCmdVersion::NewExecuteCommandReleaseEnchantCommandLevelFixAndHasItemDataFixAndCommandDeferral,
    v1001::CurrentCmdVersion::ExecuteIfScoreFixes,
    v1001::CurrentCmdVersion::ReplaceItemAndLootReplaceBlockCommandsDoNotPlaceItemsIntoCauldronsFix,
    v1001::CurrentCmdVersion::ChangesToCommandOriginRotation,
    v1001::CurrentCmdVersion::RemoveAuxValueParameterFromBlockCommands,
    v1001::CurrentCmdVersion::VolumeSelectorFixes,
    v1001::CurrentCmdVersion::EnableSummonRotation,
    v1001::CurrentCmdVersion::SummonCommandDefaultRotation,
    v1001::CurrentCmdVersion::PositionalDimensionFiltering,
    v1001::CurrentCmdVersion::CommandSelectorHasItemFilterNoLongerCallsSameItemFunction,
    v1001::CurrentCmdVersion::AgentSweepingBlockTest,
    v1001::CurrentCmdVersion::BlockStateEquals,
    v1001::CurrentCmdVersion::CommandPositionFix,
    v1001::CurrentCmdVersion::CommandSelectorHasItemFilterUsesDataAsDamageForSelectingDamageableItems,
    v1001::CurrentCmdVersion::ExecuteDetectConditionSubcommandNotAllowNonLoadedBlocks,
    v1001::CurrentCmdVersion::RemoveSuicideKeyword,
    v1001::CurrentCmdVersion::CloneContainerBlockEntityRemovalFix,
    v1001::CurrentCmdVersion::StopSoundMusicFix,
    v1001::CurrentCmdVersion::SpreadPlayersStuckInGroundFixAndMaxHeightParameter,
    v1001::CurrentCmdVersion::LocateStructureOutput,
    v1001::CurrentCmdVersion::PostBlockFlattening,
    v1001::CurrentCmdVersion::TestForBlockCommandDoesNotIgnoreBlockState,
    v1001::CurrentCmdVersion::CloneExtraBlockFilterFix,
    v1001::CurrentCmdVersion::FillCommandUnfillableErrorOutput,
    v1001::CurrentCmdVersion::StopSoundOutputFix,
    v1001::CurrentCmdVersion::PlaySoundOutputFix,
    v1001::CurrentCmdVersion::PlayerWaypointsGamerule,
    v1001::CurrentCmdVersion::Count,
}};

template <>
inline constexpr std::array<std::string_view, 54> names_v<v1001::CurrentCmdVersion>{{
    "latest",
    "invalid",
    "initial",
    "tprotationclamping",
    "newbedrockcmdsystem",
    "executeusesvec3",
    "clonefixes",
    "updateaquatic",
    "entityselectorusesvec3",
    "containersdontdropitemsanymore",
    "filtersobeydimensions",
    "executeandblockcommandandselfselectorfixes",
    "instanteffectsuseticks",
    "dontregisterbrokenfunctioncommands",
    "clearspawnpointcommand",
    "cloneandteleportrotationfixes",
    "teleportdimensionfixes",
    "cloneupdateblockandtimefixes",
    "cloneintersectfix",
    "functionexecuteorderandchestslotfix",
    "nontickingareasnolongerconsideredloaded",
    "spreadplayershazardandresolveplayerbynamefix",
    "newexecutecommandsyntaxexperimentandchestloottablefixandteleportfacingverticalunclampedandlocatebiomeandfeaturemerged",
    "waterloggingaddedtostructurecommand",
    "selectordistancefilteredandrelativerotationfix",
    "newsummoncommandaddedrotationoptionsandbubblecolumnclonefixandexecuteindimensionteleportfixandnewexecuterotationfix",
    "newexecutecommandreleaseenchantcommandlevelfixandhasitemdatafixandcommanddeferral",
    "executeifscorefixes",
    "replaceitemandlootreplaceblockcommandsdonotplaceitemsintocauldronsfix",
    "changestocommandoriginrotation",
    "removeauxvalueparameterfromblockcommands",
    "volumeselectorfixes",
    "enablesummonrotation",
    "summoncommanddefaultrotation",
    "positionaldimensionfiltering",
    "commandselectorhasitemfilternolongercallssameitemfunction",
    "agentsweepingblocktest",
    "blockstateequals",
    "commandpositionfix",
    "commandselectorhasitemfilterusesdataasdamageforselectingdamageableitems",
    "executedetectconditionsubcommandnotallownonloadedblocks",
    "removesuicidekeyword",
    "clonecontainerblockentityremovalfix",
    "stopsoundmusicfix",
    "spreadplayersstuckingroundfixandmaxheightparameter",
    "locatestructureoutput",
    "postblockflattening",
    "testforblockcommanddoesnotignoreblockstate",
    "cloneextrablockfilterfix",
    "fillcommandunfillableerroroutput",
    "stopsoundoutputfix",
    "playsoundoutputfix",
    "playerwaypointsgamerule",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<v1001::CurrentCmdVersion>{"CurrentCmdVersion"};

template <>
inline constexpr std::array<v2168::CurrentCmdVersion, 55> values_v<v2168::CurrentCmdVersion>{{
    v2168::CurrentCmdVersion::Latest,
    v2168::CurrentCmdVersion::Invalid,
    v2168::CurrentCmdVersion::Initial,
    v2168::CurrentCmdVersion::TpRotationClamping,
    v2168::CurrentCmdVersion::NewBedrockCmdSystem,
    v2168::CurrentCmdVersion::ExecuteUsesVec3,
    v2168::CurrentCmdVersion::CloneFixes,
    v2168::CurrentCmdVersion::UpdateAquatic,
    v2168::CurrentCmdVersion::EntitySelectorUsesVec3,
    v2168::CurrentCmdVersion::ContainersDontDropItemsAnymore,
    v2168::CurrentCmdVersion::FiltersObeyDimensions,
    v2168::CurrentCmdVersion::ExecuteAndBlockCommandAndSelfSelectorFixes,
    v2168::CurrentCmdVersion::InstantEffectsUseTicks,
    v2168::CurrentCmdVersion::DontRegisterBrokenFunctionCommands,
    v2168::CurrentCmdVersion::ClearSpawnPointCommand,
    v2168::CurrentCmdVersion::CloneAndTeleportRotationFixes,
    v2168::CurrentCmdVersion::TeleportDimensionFixes,
    v2168::CurrentCmdVersion::CloneUpdateBlockAndTimeFixes,
    v2168::CurrentCmdVersion::CloneIntersectFix,
    v2168::CurrentCmdVersion::FunctionExecuteOrderAndChestSlotFix,
    v2168::CurrentCmdVersion::NonTickingAreasNoLongerConsideredLoaded,
    v2168::CurrentCmdVersion::SpreadplayersHazardAndResolvePlayerByNameFix,
    v2168::CurrentCmdVersion::NewExecuteCommandSyntaxExperimentAndChestLootTableFixAndTeleportFacingVerticalUnclampedAndLocateBiomeAndFeatureMerged,
    v2168::CurrentCmdVersion::WaterloggingAddedToStructureCommand,
    v2168::CurrentCmdVersion::SelectorDistanceFilteredAndRelativeRotationFix,
    v2168::CurrentCmdVersion::NewSummonCommandAddedRotationOptionsAndBubbleColumnCloneFixAndExecuteInDimensionTeleportFixAndNewExecuteRotationFix,
    v2168::CurrentCmdVersion::NewExecuteCommandReleaseEnchantCommandLevelFixAndHasItemDataFixAndCommandDeferral,
    v2168::CurrentCmdVersion::ExecuteIfScoreFixes,
    v2168::CurrentCmdVersion::ReplaceItemAndLootReplaceBlockCommandsDoNotPlaceItemsIntoCauldronsFix,
    v2168::CurrentCmdVersion::ChangesToCommandOriginRotation,
    v2168::CurrentCmdVersion::RemoveAuxValueParameterFromBlockCommands,
    v2168::CurrentCmdVersion::VolumeSelectorFixes,
    v2168::CurrentCmdVersion::EnableSummonRotation,
    v2168::CurrentCmdVersion::SummonCommandDefaultRotation,
    v2168::CurrentCmdVersion::PositionalDimensionFiltering,
    v2168::CurrentCmdVersion::CommandSelectorHasItemFilterNoLongerCallsSameItemFunction,
    v2168::CurrentCmdVersion::AgentSweepingBlockTest,
    v2168::CurrentCmdVersion::BlockStateEquals,
    v2168::CurrentCmdVersion::CommandPositionFix,
    v2168::CurrentCmdVersion::CommandSelectorHasItemFilterUsesDataAsDamageForSelectingDamageableItems,
    v2168::CurrentCmdVersion::ExecuteDetectConditionSubcommandNotAllowNonLoadedBlocks,
    v2168::CurrentCmdVersion::RemoveSuicideKeyword,
    v2168::CurrentCmdVersion::CloneContainerBlockEntityRemovalFix,
    v2168::CurrentCmdVersion::StopSoundMusicFix,
    v2168::CurrentCmdVersion::SpreadPlayersStuckInGroundFixAndMaxHeightParameter,
    v2168::CurrentCmdVersion::LocateStructureOutput,
    v2168::CurrentCmdVersion::PostBlockFlattening,
    v2168::CurrentCmdVersion::TestForBlockCommandDoesNotIgnoreBlockState,
    v2168::CurrentCmdVersion::CloneExtraBlockFilterFix,
    v2168::CurrentCmdVersion::FillCommandUnfillableErrorOutput,
    v2168::CurrentCmdVersion::StopSoundOutputFix,
    v2168::CurrentCmdVersion::PlaySoundOutputFix,
    v2168::CurrentCmdVersion::PlayerWaypointsGamerule,
    v2168::CurrentCmdVersion::ClonePartialBedBlockFix,
    v2168::CurrentCmdVersion::Count,
}};

template <>
inline constexpr std::array<std::string_view, 55> names_v<v2168::CurrentCmdVersion>{{
    "latest",
    "invalid",
    "initial",
    "tprotationclamping",
    "newbedrockcmdsystem",
    "executeusesvec3",
    "clonefixes",
    "updateaquatic",
    "entityselectorusesvec3",
    "containersdontdropitemsanymore",
    "filtersobeydimensions",
    "executeandblockcommandandselfselectorfixes",
    "instanteffectsuseticks",
    "dontregisterbrokenfunctioncommands",
    "clearspawnpointcommand",
    "cloneandteleportrotationfixes",
    "teleportdimensionfixes",
    "cloneupdateblockandtimefixes",
    "cloneintersectfix",
    "functionexecuteorderandchestslotfix",
    "nontickingareasnolongerconsideredloaded",
    "spreadplayershazardandresolveplayerbynamefix",
    "newexecutecommandsyntaxexperimentandchestloottablefixandteleportfacingverticalunclampedandlocatebiomeandfeaturemerged",
    "waterloggingaddedtostructurecommand",
    "selectordistancefilteredandrelativerotationfix",
    "newsummoncommandaddedrotationoptionsandbubblecolumnclonefixandexecuteindimensionteleportfixandnewexecuterotationfix",
    "newexecutecommandreleaseenchantcommandlevelfixandhasitemdatafixandcommanddeferral",
    "executeifscorefixes",
    "replaceitemandlootreplaceblockcommandsdonotplaceitemsintocauldronsfix",
    "changestocommandoriginrotation",
    "removeauxvalueparameterfromblockcommands",
    "volumeselectorfixes",
    "enablesummonrotation",
    "summoncommanddefaultrotation",
    "positionaldimensionfiltering",
    "commandselectorhasitemfilternolongercallssameitemfunction",
    "agentsweepingblocktest",
    "blockstateequals",
    "commandpositionfix",
    "commandselectorhasitemfilterusesdataasdamageforselectingdamageableitems",
    "executedetectconditionsubcommandnotallownonloadedblocks",
    "removesuicidekeyword",
    "clonecontainerblockentityremovalfix",
    "stopsoundmusicfix",
    "spreadplayersstuckingroundfixandmaxheightparameter",
    "locatestructureoutput",
    "postblockflattening",
    "testforblockcommanddoesnotignoreblockstate",
    "cloneextrablockfilterfix",
    "fillcommandunfillableerroroutput",
    "stopsoundoutputfix",
    "playsoundoutputfix",
    "playerwaypointsgamerule",
    "clonepartialbedblockfix",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<v2168::CurrentCmdVersion>{"CurrentCmdVersion"};

template <>
inline constexpr std::array<v2193::CurrentCmdVersion, 57> values_v<v2193::CurrentCmdVersion>{{
    v2193::CurrentCmdVersion::Latest,
    v2193::CurrentCmdVersion::Invalid,
    v2193::CurrentCmdVersion::Initial,
    v2193::CurrentCmdVersion::TpRotationClamping,
    v2193::CurrentCmdVersion::NewBedrockCmdSystem,
    v2193::CurrentCmdVersion::ExecuteUsesVec3,
    v2193::CurrentCmdVersion::CloneFixes,
    v2193::CurrentCmdVersion::UpdateAquatic,
    v2193::CurrentCmdVersion::EntitySelectorUsesVec3,
    v2193::CurrentCmdVersion::ContainersDontDropItemsAnymore,
    v2193::CurrentCmdVersion::FiltersObeyDimensions,
    v2193::CurrentCmdVersion::ExecuteAndBlockCommandAndSelfSelectorFixes,
    v2193::CurrentCmdVersion::InstantEffectsUseTicks,
    v2193::CurrentCmdVersion::DontRegisterBrokenFunctionCommands,
    v2193::CurrentCmdVersion::ClearSpawnPointCommand,
    v2193::CurrentCmdVersion::CloneAndTeleportRotationFixes,
    v2193::CurrentCmdVersion::TeleportDimensionFixes,
    v2193::CurrentCmdVersion::CloneUpdateBlockAndTimeFixes,
    v2193::CurrentCmdVersion::CloneIntersectFix,
    v2193::CurrentCmdVersion::FunctionExecuteOrderAndChestSlotFix,
    v2193::CurrentCmdVersion::NonTickingAreasNoLongerConsideredLoaded,
    v2193::CurrentCmdVersion::SpreadplayersHazardAndResolvePlayerByNameFix,
    v2193::CurrentCmdVersion::NewExecuteCommandSyntaxExperimentAndChestLootTableFixAndTeleportFacingVerticalUnclampedAndLocateBiomeAndFeatureMerged,
    v2193::CurrentCmdVersion::WaterloggingAddedToStructureCommand,
    v2193::CurrentCmdVersion::SelectorDistanceFilteredAndRelativeRotationFix,
    v2193::CurrentCmdVersion::NewSummonCommandAddedRotationOptionsAndBubbleColumnCloneFixAndExecuteInDimensionTeleportFixAndNewExecuteRotationFix,
    v2193::CurrentCmdVersion::NewExecuteCommandReleaseEnchantCommandLevelFixAndHasItemDataFixAndCommandDeferral,
    v2193::CurrentCmdVersion::ExecuteIfScoreFixes,
    v2193::CurrentCmdVersion::ReplaceItemAndLootReplaceBlockCommandsDoNotPlaceItemsIntoCauldronsFix,
    v2193::CurrentCmdVersion::ChangesToCommandOriginRotation,
    v2193::CurrentCmdVersion::RemoveAuxValueParameterFromBlockCommands,
    v2193::CurrentCmdVersion::VolumeSelectorFixes,
    v2193::CurrentCmdVersion::EnableSummonRotation,
    v2193::CurrentCmdVersion::SummonCommandDefaultRotation,
    v2193::CurrentCmdVersion::PositionalDimensionFiltering,
    v2193::CurrentCmdVersion::CommandSelectorHasItemFilterNoLongerCallsSameItemFunction,
    v2193::CurrentCmdVersion::AgentSweepingBlockTest,
    v2193::CurrentCmdVersion::BlockStateEquals,
    v2193::CurrentCmdVersion::CommandPositionFix,
    v2193::CurrentCmdVersion::CommandSelectorHasItemFilterUsesDataAsDamageForSelectingDamageableItems,
    v2193::CurrentCmdVersion::ExecuteDetectConditionSubcommandNotAllowNonLoadedBlocks,
    v2193::CurrentCmdVersion::RemoveSuicideKeyword,
    v2193::CurrentCmdVersion::CloneContainerBlockEntityRemovalFix,
    v2193::CurrentCmdVersion::StopSoundMusicFix,
    v2193::CurrentCmdVersion::SpreadPlayersStuckInGroundFixAndMaxHeightParameter,
    v2193::CurrentCmdVersion::LocateStructureOutput,
    v2193::CurrentCmdVersion::PostBlockFlattening,
    v2193::CurrentCmdVersion::TestForBlockCommandDoesNotIgnoreBlockState,
    v2193::CurrentCmdVersion::CloneExtraBlockFilterFix,
    v2193::CurrentCmdVersion::FillCommandUnfillableErrorOutput,
    v2193::CurrentCmdVersion::StopSoundOutputFix,
    v2193::CurrentCmdVersion::PlaySoundOutputFix,
    v2193::CurrentCmdVersion::PlayerWaypointsGamerule,
    v2193::CurrentCmdVersion::ClonePartialBedBlockFix,
    v2193::CurrentCmdVersion::TeleportEntityDimensionPositionFix,
    v2193::CurrentCmdVersion::TimeOfCommandOverloads,
    v2193::CurrentCmdVersion::Count,
}};

template <>
inline constexpr std::array<std::string_view, 57> names_v<v2193::CurrentCmdVersion>{{
    "latest",
    "invalid",
    "initial",
    "tprotationclamping",
    "newbedrockcmdsystem",
    "executeusesvec3",
    "clonefixes",
    "updateaquatic",
    "entityselectorusesvec3",
    "containersdontdropitemsanymore",
    "filtersobeydimensions",
    "executeandblockcommandandselfselectorfixes",
    "instanteffectsuseticks",
    "dontregisterbrokenfunctioncommands",
    "clearspawnpointcommand",
    "cloneandteleportrotationfixes",
    "teleportdimensionfixes",
    "cloneupdateblockandtimefixes",
    "cloneintersectfix",
    "functionexecuteorderandchestslotfix",
    "nontickingareasnolongerconsideredloaded",
    "spreadplayershazardandresolveplayerbynamefix",
    "newexecutecommandsyntaxexperimentandchestloottablefixandteleportfacingverticalunclampedandlocatebiomeandfeaturemerged",
    "waterloggingaddedtostructurecommand",
    "selectordistancefilteredandrelativerotationfix",
    "newsummoncommandaddedrotationoptionsandbubblecolumnclonefixandexecuteindimensionteleportfixandnewexecuterotationfix",
    "newexecutecommandreleaseenchantcommandlevelfixandhasitemdatafixandcommanddeferral",
    "executeifscorefixes",
    "replaceitemandlootreplaceblockcommandsdonotplaceitemsintocauldronsfix",
    "changestocommandoriginrotation",
    "removeauxvalueparameterfromblockcommands",
    "volumeselectorfixes",
    "enablesummonrotation",
    "summoncommanddefaultrotation",
    "positionaldimensionfiltering",
    "commandselectorhasitemfilternolongercallssameitemfunction",
    "agentsweepingblocktest",
    "blockstateequals",
    "commandpositionfix",
    "commandselectorhasitemfilterusesdataasdamageforselectingdamageableitems",
    "executedetectconditionsubcommandnotallownonloadedblocks",
    "removesuicidekeyword",
    "clonecontainerblockentityremovalfix",
    "stopsoundmusicfix",
    "spreadplayersstuckingroundfixandmaxheightparameter",
    "locatestructureoutput",
    "postblockflattening",
    "testforblockcommanddoesnotignoreblockstate",
    "cloneextrablockfilterfix",
    "fillcommandunfillableerroroutput",
    "stopsoundoutputfix",
    "playsoundoutputfix",
    "playerwaypointsgamerule",
    "clonepartialbedblockfix",
    "teleportentitydimensionpositionfix",
    "timeofcommandoverloads",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<v2193::CurrentCmdVersion>{"CurrentCmdVersion"};

template <>
inline constexpr std::array<v2225::CurrentCmdVersion, 60> values_v<v2225::CurrentCmdVersion>{{
    v2225::CurrentCmdVersion::Latest,
    v2225::CurrentCmdVersion::Invalid,
    v2225::CurrentCmdVersion::Initial,
    v2225::CurrentCmdVersion::TpRotationClamping,
    v2225::CurrentCmdVersion::NewBedrockCmdSystem,
    v2225::CurrentCmdVersion::ExecuteUsesVec3,
    v2225::CurrentCmdVersion::CloneFixes,
    v2225::CurrentCmdVersion::UpdateAquatic,
    v2225::CurrentCmdVersion::EntitySelectorUsesVec3,
    v2225::CurrentCmdVersion::ContainersDontDropItemsAnymore,
    v2225::CurrentCmdVersion::FiltersObeyDimensions,
    v2225::CurrentCmdVersion::ExecuteAndBlockCommandAndSelfSelectorFixes,
    v2225::CurrentCmdVersion::InstantEffectsUseTicks,
    v2225::CurrentCmdVersion::DontRegisterBrokenFunctionCommands,
    v2225::CurrentCmdVersion::ClearSpawnPointCommand,
    v2225::CurrentCmdVersion::CloneAndTeleportRotationFixes,
    v2225::CurrentCmdVersion::TeleportDimensionFixes,
    v2225::CurrentCmdVersion::CloneUpdateBlockAndTimeFixes,
    v2225::CurrentCmdVersion::CloneIntersectFix,
    v2225::CurrentCmdVersion::FunctionExecuteOrderAndChestSlotFix,
    v2225::CurrentCmdVersion::NonTickingAreasNoLongerConsideredLoaded,
    v2225::CurrentCmdVersion::SpreadplayersHazardAndResolvePlayerByNameFix,
    v2225::CurrentCmdVersion::NewExecuteCommandSyntaxExperimentAndChestLootTableFixAndTeleportFacingVerticalUnclampedAndLocateBiomeAndFeatureMerged,
    v2225::CurrentCmdVersion::WaterloggingAddedToStructureCommand,
    v2225::CurrentCmdVersion::SelectorDistanceFilteredAndRelativeRotationFix,
    v2225::CurrentCmdVersion::NewSummonCommandAddedRotationOptionsAndBubbleColumnCloneFixAndExecuteInDimensionTeleportFixAndNewExecuteRotationFix,
    v2225::CurrentCmdVersion::NewExecuteCommandReleaseEnchantCommandLevelFixAndHasItemDataFixAndCommandDeferral,
    v2225::CurrentCmdVersion::ExecuteIfScoreFixes,
    v2225::CurrentCmdVersion::ReplaceItemAndLootReplaceBlockCommandsDoNotPlaceItemsIntoCauldronsFix,
    v2225::CurrentCmdVersion::ChangesToCommandOriginRotation,
    v2225::CurrentCmdVersion::RemoveAuxValueParameterFromBlockCommands,
    v2225::CurrentCmdVersion::VolumeSelectorFixes,
    v2225::CurrentCmdVersion::EnableSummonRotation,
    v2225::CurrentCmdVersion::SummonCommandDefaultRotation,
    v2225::CurrentCmdVersion::PositionalDimensionFiltering,
    v2225::CurrentCmdVersion::CommandSelectorHasItemFilterNoLongerCallsSameItemFunction,
    v2225::CurrentCmdVersion::AgentSweepingBlockTest,
    v2225::CurrentCmdVersion::BlockStateEquals,
    v2225::CurrentCmdVersion::CommandPositionFix,
    v2225::CurrentCmdVersion::CommandSelectorHasItemFilterUsesDataAsDamageForSelectingDamageableItems,
    v2225::CurrentCmdVersion::ExecuteDetectConditionSubcommandNotAllowNonLoadedBlocks,
    v2225::CurrentCmdVersion::RemoveSuicideKeyword,
    v2225::CurrentCmdVersion::CloneContainerBlockEntityRemovalFix,
    v2225::CurrentCmdVersion::StopSoundMusicFix,
    v2225::CurrentCmdVersion::SpreadPlayersStuckInGroundFixAndMaxHeightParameter,
    v2225::CurrentCmdVersion::LocateStructureOutput,
    v2225::CurrentCmdVersion::PostBlockFlattening,
    v2225::CurrentCmdVersion::TestForBlockCommandDoesNotIgnoreBlockState,
    v2225::CurrentCmdVersion::CloneExtraBlockFilterFix,
    v2225::CurrentCmdVersion::FillCommandUnfillableErrorOutput,
    v2225::CurrentCmdVersion::StopSoundOutputFix,
    v2225::CurrentCmdVersion::PlaySoundOutputFix,
    v2225::CurrentCmdVersion::PlayerWaypointsGamerule,
    v2225::CurrentCmdVersion::ClonePartialBedBlockFix,
    v2225::CurrentCmdVersion::TeleportEntityDimensionPositionFix,
    v2225::CurrentCmdVersion::TimeOfCommandOverloads,
    v2225::CurrentCmdVersion::Unknown053,
    v2225::CurrentCmdVersion::Unknown054,
    v2225::CurrentCmdVersion::Unknown055,
    v2225::CurrentCmdVersion::Count,
}};

template <>
inline constexpr std::array<std::string_view, 60> names_v<v2225::CurrentCmdVersion>{{
    "latest",
    "invalid",
    "initial",
    "tprotationclamping",
    "newbedrockcmdsystem",
    "executeusesvec3",
    "clonefixes",
    "updateaquatic",
    "entityselectorusesvec3",
    "containersdontdropitemsanymore",
    "filtersobeydimensions",
    "executeandblockcommandandselfselectorfixes",
    "instanteffectsuseticks",
    "dontregisterbrokenfunctioncommands",
    "clearspawnpointcommand",
    "cloneandteleportrotationfixes",
    "teleportdimensionfixes",
    "cloneupdateblockandtimefixes",
    "cloneintersectfix",
    "functionexecuteorderandchestslotfix",
    "nontickingareasnolongerconsideredloaded",
    "spreadplayershazardandresolveplayerbynamefix",
    "newexecutecommandsyntaxexperimentandchestloottablefixandteleportfacingverticalunclampedandlocatebiomeandfeaturemerged",
    "waterloggingaddedtostructurecommand",
    "selectordistancefilteredandrelativerotationfix",
    "newsummoncommandaddedrotationoptionsandbubblecolumnclonefixandexecuteindimensionteleportfixandnewexecuterotationfix",
    "newexecutecommandreleaseenchantcommandlevelfixandhasitemdatafixandcommanddeferral",
    "executeifscorefixes",
    "replaceitemandlootreplaceblockcommandsdonotplaceitemsintocauldronsfix",
    "changestocommandoriginrotation",
    "removeauxvalueparameterfromblockcommands",
    "volumeselectorfixes",
    "enablesummonrotation",
    "summoncommanddefaultrotation",
    "positionaldimensionfiltering",
    "commandselectorhasitemfilternolongercallssameitemfunction",
    "agentsweepingblocktest",
    "blockstateequals",
    "commandpositionfix",
    "commandselectorhasitemfilterusesdataasdamageforselectingdamageableitems",
    "executedetectconditionsubcommandnotallownonloadedblocks",
    "removesuicidekeyword",
    "clonecontainerblockentityremovalfix",
    "stopsoundmusicfix",
    "spreadplayersstuckingroundfixandmaxheightparameter",
    "locatestructureoutput",
    "postblockflattening",
    "testforblockcommanddoesnotignoreblockstate",
    "cloneextrablockfilterfix",
    "fillcommandunfillableerroroutput",
    "stopsoundoutputfix",
    "playsoundoutputfix",
    "playerwaypointsgamerule",
    "clonepartialbedblockfix",
    "teleportentitydimensionpositionfix",
    "timeofcommandoverloads",
    "unknown053",
    "unknown054",
    "unknown055",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<v2225::CurrentCmdVersion>{"CurrentCmdVersion"};

template <>
inline constexpr std::array<CommandOutputType, 5> values_v<CommandOutputType>{{
    CommandOutputType::None,
    CommandOutputType::LastOutput,
    CommandOutputType::Silent,
    CommandOutputType::AllOutput,
    CommandOutputType::DataSet,
}};

template <>
inline constexpr std::array<std::string_view, 5> names_v<CommandOutputType>{{
    "none",
    "lastoutput",
    "silent",
    "alloutput",
    "dataset",
}};

template <>
inline constexpr std::string_view type_name_v<CommandOutputType>{"CommandOutputType"};

template <>
inline constexpr std::array<SoftEnumUpdateType, 3> values_v<SoftEnumUpdateType>{{
    SoftEnumUpdateType::Add,
    SoftEnumUpdateType::Remove,
    SoftEnumUpdateType::Replace,
}};

template <>
inline constexpr std::array<std::string_view, 3> names_v<SoftEnumUpdateType>{{
    "add",
    "remove",
    "replace",
}};

template <>
inline constexpr std::string_view type_name_v<SoftEnumUpdateType>{"SoftEnumUpdateType"};

template <>
inline constexpr std::array<PlayerPermissionLevel, 4> values_v<PlayerPermissionLevel>{{
    PlayerPermissionLevel::Visitor,
    PlayerPermissionLevel::Member,
    PlayerPermissionLevel::Operator,
    PlayerPermissionLevel::Custom,
}};

template <>
inline constexpr std::array<std::string_view, 4> names_v<PlayerPermissionLevel>{{
    "visitor",
    "member",
    "operator",
    "custom",
}};

template <>
inline constexpr std::string_view type_name_v<PlayerPermissionLevel>{"PlayerPermissionLevel"};

}  // namespace detail

namespace detail {

template <>
inline constexpr bool is_reflected_struct_v<SettingsCommandPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<SettingsCommandPacket>{"SettingsCommandPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<SettingsCommandPacket>{{
    "command_string",
    "suppress_output",
}};

template <>
struct field_accessor<SettingsCommandPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.command_string;
        }
        else {
            return value.suppress_output;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<AvailableCommandsPacket::EnumData> = true;

template <>
inline constexpr std::string_view struct_name_v<AvailableCommandsPacket::EnumData>{"AvailableCommandsPacket::EnumData"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<AvailableCommandsPacket::EnumData>{{
    "name",
    "values",
}};

template <>
struct field_accessor<AvailableCommandsPacket::EnumData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.name;
        }
        else {
            return value.values;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<AvailableCommandsPacket::ChainedSubcommandRelationship> = true;

template <>
inline constexpr std::string_view struct_name_v<AvailableCommandsPacket::ChainedSubcommandRelationship>{"AvailableCommandsPacket::ChainedSubcommandRelationship"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<AvailableCommandsPacket::ChainedSubcommandRelationship>{{
    "sub_command_first_value",
    "sub_command_second_value",
}};

template <>
struct field_accessor<AvailableCommandsPacket::ChainedSubcommandRelationship> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.sub_command_first_value;
        }
        else {
            return value.sub_command_second_value;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<AvailableCommandsPacket::ChainedSubcommandData> = true;

template <>
inline constexpr std::string_view struct_name_v<AvailableCommandsPacket::ChainedSubcommandData>{"AvailableCommandsPacket::ChainedSubcommandData"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<AvailableCommandsPacket::ChainedSubcommandData>{{
    "name",
    "values",
}};

template <>
struct field_accessor<AvailableCommandsPacket::ChainedSubcommandData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.name;
        }
        else {
            return value.values;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<AvailableCommandsPacket::SoftEnumData> = true;

template <>
inline constexpr std::string_view struct_name_v<AvailableCommandsPacket::SoftEnumData>{"AvailableCommandsPacket::SoftEnumData"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<AvailableCommandsPacket::SoftEnumData>{{
    "name",
    "values",
}};

template <>
struct field_accessor<AvailableCommandsPacket::SoftEnumData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.name;
        }
        else {
            return value.values;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<AvailableCommandsPacket::ConstrainedValueData> = true;

template <>
inline constexpr std::string_view struct_name_v<AvailableCommandsPacket::ConstrainedValueData>{"AvailableCommandsPacket::ConstrainedValueData"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<AvailableCommandsPacket::ConstrainedValueData>{{
    "enum_value_symbol",
    "enum_symbol",
    "constraints",
}};

template <>
struct field_accessor<AvailableCommandsPacket::ConstrainedValueData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.enum_value_symbol;
        }
        else if constexpr (I == 1) {
            return value.enum_symbol;
        }
        else {
            return value.constraints;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<AvailableCommandsPacket::ParamData> = true;

template <>
inline constexpr std::string_view struct_name_v<AvailableCommandsPacket::ParamData>{"AvailableCommandsPacket::ParamData"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<AvailableCommandsPacket::ParamData>{{
    "name",
    "parse_symbol",
    "optional",
    "param_options",
}};

template <>
struct field_accessor<AvailableCommandsPacket::ParamData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.name;
        }
        else if constexpr (I == 1) {
            return value.parse_symbol;
        }
        else if constexpr (I == 2) {
            return value.optional;
        }
        else {
            return value.param_options;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<AvailableCommandsPacket::OverloadData> = true;

template <>
inline constexpr std::string_view struct_name_v<AvailableCommandsPacket::OverloadData>{"AvailableCommandsPacket::OverloadData"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<AvailableCommandsPacket::OverloadData>{{
    "is_chaining",
    "params",
}};

template <>
struct field_accessor<AvailableCommandsPacket::OverloadData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.is_chaining;
        }
        else {
            return value.params;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<AvailableCommandsPacket::CommandData> = true;

template <>
inline constexpr std::string_view struct_name_v<AvailableCommandsPacket::CommandData>{"AvailableCommandsPacket::CommandData"};

template <>
inline constexpr std::array<std::string_view, 7> field_names_v<AvailableCommandsPacket::CommandData>{{
    "name",
    "description",
    "flags",
    "permission",
    "alias_enum",
    "chained_subcommand_indexes",
    "overloads",
}};

template <>
struct field_accessor<AvailableCommandsPacket::CommandData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.name;
        }
        else if constexpr (I == 1) {
            return value.description;
        }
        else if constexpr (I == 2) {
            return value.flags;
        }
        else if constexpr (I == 3) {
            return value.permission;
        }
        else if constexpr (I == 4) {
            return value.alias_enum;
        }
        else if constexpr (I == 5) {
            return value.chained_subcommand_indexes;
        }
        else {
            return value.overloads;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<AvailableCommandsPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<AvailableCommandsPacket>{"AvailableCommandsPacket"};

template <>
inline constexpr std::array<std::string_view, 8> field_names_v<AvailableCommandsPacket>{{
    "enum_values",
    "chained_subcommand_values",
    "postfixes",
    "enums",
    "chained_subcommands",
    "commands",
    "soft_enums",
    "constraints",
}};

template <>
struct field_accessor<AvailableCommandsPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.enum_values;
        }
        else if constexpr (I == 1) {
            return value.chained_subcommand_values;
        }
        else if constexpr (I == 2) {
            return value.postfixes;
        }
        else if constexpr (I == 3) {
            return value.enums;
        }
        else if constexpr (I == 4) {
            return value.chained_subcommands;
        }
        else if constexpr (I == 5) {
            return value.commands;
        }
        else if constexpr (I == 6) {
            return value.soft_enums;
        }
        else {
            return value.constraints;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::CommandBlockUpdatePacket::EntityCommandTarget> = true;

template <>
inline constexpr std::string_view struct_name_v<base::CommandBlockUpdatePacket::EntityCommandTarget>{"CommandBlockUpdatePacket::EntityCommandTarget"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::CommandBlockUpdatePacket::EntityCommandTarget>{{
    "entity_id",
}};

template <>
struct field_accessor<base::CommandBlockUpdatePacket::EntityCommandTarget> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.entity_id;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::CommandBlockUpdatePacket::BlockCommandData> = true;

template <>
inline constexpr std::string_view struct_name_v<base::CommandBlockUpdatePacket::BlockCommandData>{"CommandBlockUpdatePacket::BlockCommandData"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<base::CommandBlockUpdatePacket::BlockCommandData>{{
    "block_pos",
    "mode",
    "redstone_mode",
    "is_conditional",
}};

template <>
struct field_accessor<base::CommandBlockUpdatePacket::BlockCommandData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.block_pos;
        }
        else if constexpr (I == 1) {
            return value.mode;
        }
        else if constexpr (I == 2) {
            return value.redstone_mode;
        }
        else {
            return value.is_conditional;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v776::CommandBlockUpdatePacket::BlockCommandData> = true;

template <>
inline constexpr std::string_view struct_name_v<v776::CommandBlockUpdatePacket::BlockCommandData>{"CommandBlockUpdatePacket::BlockCommandData"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v776::CommandBlockUpdatePacket::BlockCommandData>{{
    "block_pos",
    "mode",
    "redstone_mode",
    "is_conditional",
}};

template <>
struct field_accessor<v776::CommandBlockUpdatePacket::BlockCommandData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.block_pos;
        }
        else if constexpr (I == 1) {
            return value.mode;
        }
        else if constexpr (I == 2) {
            return value.redstone_mode;
        }
        else {
            return value.is_conditional;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::CommandBlockUpdatePacket::BlockCommandData> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::CommandBlockUpdatePacket::BlockCommandData>{"CommandBlockUpdatePacket::BlockCommandData"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v944::CommandBlockUpdatePacket::BlockCommandData>{{
    "block_pos",
    "mode",
    "redstone_mode",
    "is_conditional",
}};

template <>
struct field_accessor<v944::CommandBlockUpdatePacket::BlockCommandData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.block_pos;
        }
        else if constexpr (I == 1) {
            return value.mode;
        }
        else if constexpr (I == 2) {
            return value.redstone_mode;
        }
        else {
            return value.is_conditional;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::CommandBlockUpdatePacket::BlockCommandData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::CommandBlockUpdatePacket::BlockCommandData>{"CommandBlockUpdatePacket::BlockCommandData"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v2168::CommandBlockUpdatePacket::BlockCommandData>{{
    "block_pos",
    "mode",
    "redstone_mode",
    "is_conditional",
}};

template <>
struct field_accessor<v2168::CommandBlockUpdatePacket::BlockCommandData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.block_pos;
        }
        else if constexpr (I == 1) {
            return value.mode;
        }
        else if constexpr (I == 2) {
            return value.redstone_mode;
        }
        else {
            return value.is_conditional;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::CommandBlockUpdatePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::CommandBlockUpdatePacket>{"CommandBlockUpdatePacket"};

template <>
inline constexpr std::array<std::string_view, 7> field_names_v<base::CommandBlockUpdatePacket>{{
    "target",
    "command",
    "last_output",
    "name",
    "track_output",
    "tick_delay",
    "execute_on_first_tick",
}};

template <>
struct field_accessor<base::CommandBlockUpdatePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.target;
        }
        else if constexpr (I == 1) {
            return value.command;
        }
        else if constexpr (I == 2) {
            return value.last_output;
        }
        else if constexpr (I == 3) {
            return value.name;
        }
        else if constexpr (I == 4) {
            return value.track_output;
        }
        else if constexpr (I == 5) {
            return value.tick_delay;
        }
        else {
            return value.execute_on_first_tick;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v776::CommandBlockUpdatePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v776::CommandBlockUpdatePacket>{"CommandBlockUpdatePacket"};

template <>
inline constexpr std::array<std::string_view, 8> field_names_v<v776::CommandBlockUpdatePacket>{{
    "target",
    "command",
    "last_output",
    "name",
    "filtered_name",
    "track_output",
    "tick_delay",
    "execute_on_first_tick",
}};

template <>
struct field_accessor<v776::CommandBlockUpdatePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.target;
        }
        else if constexpr (I == 1) {
            return value.command;
        }
        else if constexpr (I == 2) {
            return value.last_output;
        }
        else if constexpr (I == 3) {
            return value.name;
        }
        else if constexpr (I == 4) {
            return value.filtered_name;
        }
        else if constexpr (I == 5) {
            return value.track_output;
        }
        else if constexpr (I == 6) {
            return value.tick_delay;
        }
        else {
            return value.execute_on_first_tick;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::CommandBlockUpdatePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::CommandBlockUpdatePacket>{"CommandBlockUpdatePacket"};

template <>
inline constexpr std::array<std::string_view, 8> field_names_v<v944::CommandBlockUpdatePacket>{{
    "target",
    "command",
    "last_output",
    "name",
    "filtered_name",
    "track_output",
    "tick_delay",
    "execute_on_first_tick",
}};

template <>
struct field_accessor<v944::CommandBlockUpdatePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.target;
        }
        else if constexpr (I == 1) {
            return value.command;
        }
        else if constexpr (I == 2) {
            return value.last_output;
        }
        else if constexpr (I == 3) {
            return value.name;
        }
        else if constexpr (I == 4) {
            return value.filtered_name;
        }
        else if constexpr (I == 5) {
            return value.track_output;
        }
        else if constexpr (I == 6) {
            return value.tick_delay;
        }
        else {
            return value.execute_on_first_tick;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::CommandBlockUpdatePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::CommandBlockUpdatePacket>{"CommandBlockUpdatePacket"};

template <>
inline constexpr std::array<std::string_view, 8> field_names_v<v2168::CommandBlockUpdatePacket>{{
    "target",
    "command",
    "last_output",
    "name",
    "filtered_name",
    "track_output",
    "tick_delay",
    "execute_on_first_tick",
}};

template <>
struct field_accessor<v2168::CommandBlockUpdatePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.target;
        }
        else if constexpr (I == 1) {
            return value.command;
        }
        else if constexpr (I == 2) {
            return value.last_output;
        }
        else if constexpr (I == 3) {
            return value.name;
        }
        else if constexpr (I == 4) {
            return value.filtered_name;
        }
        else if constexpr (I == 5) {
            return value.track_output;
        }
        else if constexpr (I == 6) {
            return value.tick_delay;
        }
        else {
            return value.execute_on_first_tick;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<CommandOriginData> = true;

template <>
inline constexpr std::string_view struct_name_v<CommandOriginData>{"CommandOriginData"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<CommandOriginData>{{
    "type",
    "uuid",
    "request_id",
    "player_id",
}};

template <>
struct field_accessor<CommandOriginData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.type;
        }
        else if constexpr (I == 1) {
            return value.uuid;
        }
        else if constexpr (I == 2) {
            return value.request_id;
        }
        else {
            return value.player_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::CommandRequestPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::CommandRequestPacket>{"CommandRequestPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<base::CommandRequestPacket>{{
    "command",
    "origin",
    "internal_source",
    "version",
}};

template <>
struct field_accessor<base::CommandRequestPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.command;
        }
        else if constexpr (I == 1) {
            return value.origin;
        }
        else if constexpr (I == 2) {
            return value.internal_source;
        }
        else {
            return value.version;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v786::CommandRequestPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v786::CommandRequestPacket>{"CommandRequestPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v786::CommandRequestPacket>{{
    "command",
    "origin",
    "internal_source",
    "version",
}};

template <>
struct field_accessor<v786::CommandRequestPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.command;
        }
        else if constexpr (I == 1) {
            return value.origin;
        }
        else if constexpr (I == 2) {
            return value.internal_source;
        }
        else {
            return value.version;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v818::CommandRequestPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v818::CommandRequestPacket>{"CommandRequestPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v818::CommandRequestPacket>{{
    "command",
    "origin",
    "internal_source",
    "version",
}};

template <>
struct field_accessor<v818::CommandRequestPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.command;
        }
        else if constexpr (I == 1) {
            return value.origin;
        }
        else if constexpr (I == 2) {
            return value.internal_source;
        }
        else {
            return value.version;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v898::CommandRequestPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v898::CommandRequestPacket>{"CommandRequestPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v898::CommandRequestPacket>{{
    "command",
    "origin",
    "internal_source",
    "version",
}};

template <>
struct field_accessor<v898::CommandRequestPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.command;
        }
        else if constexpr (I == 1) {
            return value.origin;
        }
        else if constexpr (I == 2) {
            return value.internal_source;
        }
        else {
            return value.version;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v975::CommandRequestPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v975::CommandRequestPacket>{"CommandRequestPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v975::CommandRequestPacket>{{
    "command",
    "origin",
    "internal_source",
    "version",
}};

template <>
struct field_accessor<v975::CommandRequestPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.command;
        }
        else if constexpr (I == 1) {
            return value.origin;
        }
        else if constexpr (I == 2) {
            return value.internal_source;
        }
        else {
            return value.version;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::CommandRequestPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::CommandRequestPacket>{"CommandRequestPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v1001::CommandRequestPacket>{{
    "command",
    "origin",
    "internal_source",
    "version",
}};

template <>
struct field_accessor<v1001::CommandRequestPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.command;
        }
        else if constexpr (I == 1) {
            return value.origin;
        }
        else if constexpr (I == 2) {
            return value.internal_source;
        }
        else {
            return value.version;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::CommandRequestPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::CommandRequestPacket>{"CommandRequestPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v2168::CommandRequestPacket>{{
    "command",
    "origin",
    "internal_source",
    "version",
}};

template <>
struct field_accessor<v2168::CommandRequestPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.command;
        }
        else if constexpr (I == 1) {
            return value.origin;
        }
        else if constexpr (I == 2) {
            return value.internal_source;
        }
        else {
            return value.version;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2193::CommandRequestPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2193::CommandRequestPacket>{"CommandRequestPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v2193::CommandRequestPacket>{{
    "command",
    "origin",
    "internal_source",
    "version",
}};

template <>
struct field_accessor<v2193::CommandRequestPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.command;
        }
        else if constexpr (I == 1) {
            return value.origin;
        }
        else if constexpr (I == 2) {
            return value.internal_source;
        }
        else {
            return value.version;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::CommandRequestPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::CommandRequestPacket>{"CommandRequestPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v2225::CommandRequestPacket>{{
    "command",
    "origin",
    "internal_source",
    "version",
}};

template <>
struct field_accessor<v2225::CommandRequestPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.command;
        }
        else if constexpr (I == 1) {
            return value.origin;
        }
        else if constexpr (I == 2) {
            return value.internal_source;
        }
        else {
            return value.version;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<CommandOutputMessage> = true;

template <>
inline constexpr std::string_view struct_name_v<CommandOutputMessage>{"CommandOutputMessage"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<CommandOutputMessage>{{
    "message_id",
    "successful",
    "params",
}};

template <>
struct field_accessor<CommandOutputMessage> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.message_id;
        }
        else if constexpr (I == 1) {
            return value.successful;
        }
        else {
            return value.params;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<CommandOutput> = true;

template <>
inline constexpr std::string_view struct_name_v<CommandOutput>{"CommandOutput"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<CommandOutput>{{
    "type",
    "success_count",
    "messages",
    "data",
}};

template <>
struct field_accessor<CommandOutput> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.type;
        }
        else if constexpr (I == 1) {
            return value.success_count;
        }
        else if constexpr (I == 2) {
            return value.messages;
        }
        else {
            return value.data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<CommandOutputPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<CommandOutputPacket>{"CommandOutputPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<CommandOutputPacket>{{
    "origin_data",
    "output",
}};

template <>
struct field_accessor<CommandOutputPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.origin_data;
        }
        else {
            return value.output;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<UpdateSoftEnumPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<UpdateSoftEnumPacket>{"UpdateSoftEnumPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<UpdateSoftEnumPacket>{{
    "enum_name",
    "values",
    "type",
}};

template <>
struct field_accessor<UpdateSoftEnumPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.enum_name;
        }
        else if constexpr (I == 1) {
            return value.values;
        }
        else {
            return value.type;
        }
    }
};

}  // namespace detail


template <>
struct Serializer<CommandPermissionLevel> {
    static void serialize(BinaryWriter &stream, CommandPermissionLevel value);
    static auto deserialize(BinaryReader &stream) -> std::expected<CommandPermissionLevel, std::error_code>;
};

template <>
struct Serializer<SettingsCommandPacket> {
    static void serialize(BinaryWriter &stream, const SettingsCommandPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<SettingsCommandPacket, std::error_code>;
};

template <>
struct Serializer<AvailableCommandsPacket::EnumData> {
    static void serialize(BinaryWriter &stream, const AvailableCommandsPacket::EnumData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<AvailableCommandsPacket::EnumData, std::error_code>;
};

template <>
struct Serializer<AvailableCommandsPacket::ChainedSubcommandRelationship> {
    static void serialize(BinaryWriter &stream, const AvailableCommandsPacket::ChainedSubcommandRelationship &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<AvailableCommandsPacket::ChainedSubcommandRelationship, std::error_code>;
};

template <>
struct Serializer<AvailableCommandsPacket::ChainedSubcommandData> {
    static void serialize(BinaryWriter &stream, const AvailableCommandsPacket::ChainedSubcommandData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<AvailableCommandsPacket::ChainedSubcommandData, std::error_code>;
};

template <>
struct Serializer<AvailableCommandsPacket::SoftEnumData> {
    static void serialize(BinaryWriter &stream, const AvailableCommandsPacket::SoftEnumData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<AvailableCommandsPacket::SoftEnumData, std::error_code>;
};

template <>
struct Serializer<AvailableCommandsPacket::ConstrainedValueData> {
    static void serialize(BinaryWriter &stream, const AvailableCommandsPacket::ConstrainedValueData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<AvailableCommandsPacket::ConstrainedValueData, std::error_code>;
};

template <>
struct Serializer<AvailableCommandsPacket::ParamData> {
    static void serialize(BinaryWriter &stream, const AvailableCommandsPacket::ParamData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<AvailableCommandsPacket::ParamData, std::error_code>;
};

template <>
struct Serializer<AvailableCommandsPacket::OverloadData> {
    static void serialize(BinaryWriter &stream, const AvailableCommandsPacket::OverloadData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<AvailableCommandsPacket::OverloadData, std::error_code>;
};

template <>
struct Serializer<AvailableCommandsPacket::CommandData> {
    static void serialize(BinaryWriter &stream, const AvailableCommandsPacket::CommandData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<AvailableCommandsPacket::CommandData, std::error_code>;
};

template <>
struct Serializer<AvailableCommandsPacket> {
    static void serialize(BinaryWriter &stream, const AvailableCommandsPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<AvailableCommandsPacket, std::error_code>;
};

template <>
struct Serializer<base::CommandBlockUpdatePacket::EntityCommandTarget> {
    static void serialize(BinaryWriter &stream, const base::CommandBlockUpdatePacket::EntityCommandTarget &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::CommandBlockUpdatePacket::EntityCommandTarget, std::error_code>;
};

template <>
struct Serializer<base::CommandBlockUpdatePacket::BlockCommandData> {
    static void serialize(BinaryWriter &stream, const base::CommandBlockUpdatePacket::BlockCommandData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::CommandBlockUpdatePacket::BlockCommandData, std::error_code>;
};

template <>
struct Serializer<v776::CommandBlockUpdatePacket::BlockCommandData> {
    static void serialize(BinaryWriter &stream, const v776::CommandBlockUpdatePacket::BlockCommandData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v776::CommandBlockUpdatePacket::BlockCommandData, std::error_code>;
};

template <>
struct Serializer<v944::CommandBlockUpdatePacket::BlockCommandData> {
    static void serialize(BinaryWriter &stream, const v944::CommandBlockUpdatePacket::BlockCommandData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::CommandBlockUpdatePacket::BlockCommandData, std::error_code>;
};

template <>
struct Serializer<v2168::CommandBlockUpdatePacket::BlockCommandData> {
    static void serialize(BinaryWriter &stream, const v2168::CommandBlockUpdatePacket::BlockCommandData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::CommandBlockUpdatePacket::BlockCommandData, std::error_code>;
};

template <>
struct Serializer<base::CommandBlockUpdatePacket> {
    static void serialize(BinaryWriter &stream, const base::CommandBlockUpdatePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::CommandBlockUpdatePacket, std::error_code>;
};

template <>
struct Serializer<v776::CommandBlockUpdatePacket> {
    static void serialize(BinaryWriter &stream, const v776::CommandBlockUpdatePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v776::CommandBlockUpdatePacket, std::error_code>;
};

template <>
struct Serializer<v944::CommandBlockUpdatePacket> {
    static void serialize(BinaryWriter &stream, const v944::CommandBlockUpdatePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::CommandBlockUpdatePacket, std::error_code>;
};

template <>
struct Serializer<v2168::CommandBlockUpdatePacket> {
    static void serialize(BinaryWriter &stream, const v2168::CommandBlockUpdatePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::CommandBlockUpdatePacket, std::error_code>;
};

template <>
struct Serializer<CommandOriginType> {
    static void serialize(BinaryWriter &stream, CommandOriginType value);
    static auto deserialize(BinaryReader &stream) -> std::expected<CommandOriginType, std::error_code>;
};

template <>
struct Serializer<CommandOriginData> {
    static void serialize(BinaryWriter &stream, const CommandOriginData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<CommandOriginData, std::error_code>;
};

template <>
struct Serializer<base::CurrentCmdVersion> {
    static void serialize(BinaryWriter &stream, base::CurrentCmdVersion value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::CurrentCmdVersion, std::error_code>;
};

template <>
struct Serializer<v786::CurrentCmdVersion> {
    static void serialize(BinaryWriter &stream, v786::CurrentCmdVersion value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v786::CurrentCmdVersion, std::error_code>;
};

template <>
struct Serializer<v818::CurrentCmdVersion> {
    static void serialize(BinaryWriter &stream, v818::CurrentCmdVersion value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v818::CurrentCmdVersion, std::error_code>;
};

template <>
struct Serializer<v898::CurrentCmdVersion> {
    static void serialize(BinaryWriter &stream, v898::CurrentCmdVersion value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v898::CurrentCmdVersion, std::error_code>;
};

template <>
struct Serializer<v975::CurrentCmdVersion> {
    static void serialize(BinaryWriter &stream, v975::CurrentCmdVersion value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v975::CurrentCmdVersion, std::error_code>;
};

template <>
struct Serializer<v1001::CurrentCmdVersion> {
    static void serialize(BinaryWriter &stream, v1001::CurrentCmdVersion value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::CurrentCmdVersion, std::error_code>;
};

template <>
struct Serializer<v2168::CurrentCmdVersion> {
    static void serialize(BinaryWriter &stream, v2168::CurrentCmdVersion value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::CurrentCmdVersion, std::error_code>;
};

template <>
struct Serializer<v2193::CurrentCmdVersion> {
    static void serialize(BinaryWriter &stream, v2193::CurrentCmdVersion value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::CurrentCmdVersion, std::error_code>;
};

template <>
struct Serializer<v2225::CurrentCmdVersion> {
    static void serialize(BinaryWriter &stream, v2225::CurrentCmdVersion value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::CurrentCmdVersion, std::error_code>;
};

template <>
struct Serializer<base::CommandRequestPacket> {
    static void serialize(BinaryWriter &stream, const base::CommandRequestPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::CommandRequestPacket, std::error_code>;
};

template <>
struct Serializer<v786::CommandRequestPacket> {
    static void serialize(BinaryWriter &stream, const v786::CommandRequestPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v786::CommandRequestPacket, std::error_code>;
};

template <>
struct Serializer<v818::CommandRequestPacket> {
    static void serialize(BinaryWriter &stream, const v818::CommandRequestPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v818::CommandRequestPacket, std::error_code>;
};

template <>
struct Serializer<v898::CommandRequestPacket> {
    static void serialize(BinaryWriter &stream, const v898::CommandRequestPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v898::CommandRequestPacket, std::error_code>;
};

template <>
struct Serializer<v975::CommandRequestPacket> {
    static void serialize(BinaryWriter &stream, const v975::CommandRequestPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v975::CommandRequestPacket, std::error_code>;
};

template <>
struct Serializer<v1001::CommandRequestPacket> {
    static void serialize(BinaryWriter &stream, const v1001::CommandRequestPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::CommandRequestPacket, std::error_code>;
};

template <>
struct Serializer<v2168::CommandRequestPacket> {
    static void serialize(BinaryWriter &stream, const v2168::CommandRequestPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::CommandRequestPacket, std::error_code>;
};

template <>
struct Serializer<v2193::CommandRequestPacket> {
    static void serialize(BinaryWriter &stream, const v2193::CommandRequestPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::CommandRequestPacket, std::error_code>;
};

template <>
struct Serializer<v2225::CommandRequestPacket> {
    static void serialize(BinaryWriter &stream, const v2225::CommandRequestPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::CommandRequestPacket, std::error_code>;
};

template <>
struct Serializer<CommandOutputType> {
    static void serialize(BinaryWriter &stream, CommandOutputType value);
    static auto deserialize(BinaryReader &stream) -> std::expected<CommandOutputType, std::error_code>;
};

template <>
struct Serializer<CommandOutputMessage> {
    static void serialize(BinaryWriter &stream, const CommandOutputMessage &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<CommandOutputMessage, std::error_code>;
};

template <>
struct Serializer<CommandOutput> {
    static void serialize(BinaryWriter &stream, const CommandOutput &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<CommandOutput, std::error_code>;
};

template <>
struct Serializer<CommandOutputPacket> {
    static void serialize(BinaryWriter &stream, const CommandOutputPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<CommandOutputPacket, std::error_code>;
};

template <>
struct Serializer<UpdateSoftEnumPacket> {
    static void serialize(BinaryWriter &stream, const UpdateSoftEnumPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<UpdateSoftEnumPacket, std::error_code>;
};
using CommandBlockUpdatePacket = CommandBlockUpdatePacket_<2225>;
using CurrentCmdVersion = CurrentCmdVersion_<2225>;
using CommandRequestPacket = CommandRequestPacket_<2225>;

}  // namespace bedrock::protocol
