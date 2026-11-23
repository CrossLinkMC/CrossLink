#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <expected>
#include <string>
#include <string_view>
#include <system_error>
#include <variant>

#include <bedrock/protocol/detail/reflect.hpp>
#include <bedrock/protocol/enum.hpp>
#include <bedrock/protocol/packet.hpp>
#include <bedrock/protocol/serializer.hpp>
#include <bedrock/protocol/stream.hpp>

#include <bedrock/protocol/actor.h>

namespace bedrock::protocol {

namespace base {

namespace MinecraftEventing_nested {

enum class InteractionType : std::uint8_t {
    Breeding = 1,
    Taming = 2,
    Curing = 3,
    Crafted = 4,
    Shearing = 5,
    Milking = 6,
    Trading = 7,
    Feeding = 8,
    Igniting = 9,
    Coloring = 10,
    Naming = 11,
    Leashing = 12,
    Unleashing = 13,
    PetSleep = 14,
    Trusting = 15,
    Commanding = 16,
};

enum class AchievementIds : std::uint8_t {
    ChestFullOfCobblestone = 7,
    DiamondForYou = 10,
    IronBelly = 20,
    IronMan = 21,
    OnARail = 29,
    Overkill = 30,
    ReturnToSender = 37,
    SniperDuel = 38,
    StayinFrosty = 39,
    TakeInventory = 40,
    MapRoom = 50,
    FreightStation = 52,
    SmeltEverything = 53,
    TasteOfYourOwnMedicine = 54,
    WhenPigsFly = 56,
    Inception = 58,
    ArtificialSelection = 60,
    FreeDiver = 61,
    SpawnTheWither = 62,
    Beaconator = 63,
    GreatView = 64,
    SuperSonic = 65,
    TheEndAgain = 66,
    TreasureHunter = 67,
    ShootingStar = 68,
    FashionShow = 69,
    Brilliance = 70,
    SelfPublishedAuthor = 71,
    AlternativeFuel = 72,
    SleepWithTheFishes = 73,
    Castaway = 74,
    ImAMarineBiologist = 75,
    SailThe7Seas = 76,
    MeGold = 77,
    Ahoy = 78,
    Atlantis = 79,
    OnePickleTwoPickleSeaPickleFour = 80,
    DoaBarrelRoll = 81,
    Moskstraumen = 82,
    Echolocation = 83,
    WhereHaveYouBeen = 84,
    TopOfTheWorld = 85,
    FruitOnTheLoom = 86,
    SoundTheAlarm = 87,
    BuyLowSellHigh = 88,
    Disenchanted = 89,
    TimeForStew = 90,
    BeeOurGuest = 91,
    TotalBeeLocation = 92,
    StickySituation = 93,
    CoverMeInDebris = 94,
    FloatYourGoat = 95,
    Friend = 96,
    WaxOnWaxOff = 97,
    StriderRiddenInLavaInOverworld = 98,
    GoatHornAcquired = 99,
    JukeboxUsedInMeadows = 100,
    TradedAtWorldHeight = 101,
    SurvivedFallFromWorldHeight = 102,
    SneakCloseToSculkSensor = 103,
    ItSpreads = 104,
    BirthdaySong = 105,
    WithOurPowersCombined = 106,
    PlantingThePast = 107,
    CarefulRestoration = 108,
    Revaulting = 109,
    CraftersCraftingCrafters = 110,
    WhoNeedsRockets = 111,
    OverOverkill = 112,
    Count = 113,
};

enum class POIBlockInteractionType : std::uint8_t {
    None = 0,
    Extend = 1,
    Clone = 2,
    Lock = 3,
    Create = 4,
    CreateLocator = 5,
    Rename = 6,
    ItemPlaced = 7,
    ItemRemoved = 8,
    Cooking = 9,
    Dousing = 10,
    Lighting = 11,
    Haystack = 12,
    Filled = 13,
    Emptied = 14,
    AddDye = 15,
    DyeItem = 16,
    ClearItem = 17,
    EnchantArrow = 18,
    CompostItemPlaced = 19,
    RecoveredBonemeal = 20,
    BookPlaced = 21,
    BookOpened = 22,
    Disenchant = 23,
    Repair = 24,
    DisenchantAndRepair = 25,
};

}  // namespace MinecraftEventing_nested

struct MinecraftEventing {
    using InteractionType = MinecraftEventing_nested::InteractionType;
    using AchievementIds = MinecraftEventing_nested::AchievementIds;
    using POIBlockInteractionType = MinecraftEventing_nested::POIBlockInteractionType;
};

namespace LegacyTelemetryEventPacket_nested {

enum class Type : int {
    Achievement = 0,
    Interaction = 1,
    PortalCreated = 2,
    PortalUsed = 3,
    MobKilled = 4,
    CauldronUsed = 5,
    PlayerDied = 6,
    BossKilled = 7,
    AgentCommandObsolete = 8,
    AgentCreated = 9,
    PatternRemovedObsolete = 10,
    SlashCommand = 11,
    FishBucketedObsolete = 12,
    MobBorn = 13,
    PetDiedObsolete = 14,
    POICauldronUsed = 15,
    ComposterUsed = 16,
    BellUsed = 17,
    ActorDefinition = 18,
    RaidUpdate = 19,
    PlayerMovementAnomalyObsolete = 20,
    PlayerMovementCorrectedObsolete = 21,
    HoneyHarvested = 22,
    TargetBlockHit = 23,
    PiglinBarter = 24,
    PlayerWaxedOrUnwaxedCopper = 25,
    CodeBuilderRuntimeAction = 26,
    CodeBuilderScoreboard = 27,
    StriderRiddenInLavaInOverworld = 28,
    SneakCloseToSculkSensor = 29,
    CarefulRestoration = 30,
    ItemUsed = 31,
};

struct Achievement {
    base::MinecraftEventing::AchievementIds achievement_id{};
};

struct Interaction {
    ActorUniqueID interacted_entity_id{};
    base::MinecraftEventing::InteractionType interaction_type{};
    std::int32_t interacted_entity_type{};
    std::int32_t interacted_entity_variant{};
    std::uint8_t interacted_entity_color{};
};

struct PortalCreated {
    std::int32_t built_in_dimension{};
};

struct PortalUsed {
    std::int32_t from_dimension{};
    std::int32_t to_dimension{};
};

struct MobKilled {
    ActorUniqueID killer_entity_id{};
    ActorUniqueID killed_mob_id{};
    base::ActorType damage_child_type{};
    std::int32_t damage_source{};
    std::int32_t trader_tier{};
    std::string trader_name{};
};

struct CauldronUsed {
    std::uint32_t contents_color{};
    std::int32_t contents_type{};
    std::int32_t fill_level{};
};

struct PlayerDied {
    std::int32_t killer_id{};
    std::int32_t killer_variant{};
    std::int32_t damage_source{};
    bool in_raid{};
};

struct BossKilled {
    ActorUniqueID boss_unique_id{};
    std::int32_t party_size{};
    std::int32_t boss_type{};
};

struct SlashCommand {
    std::int32_t success_count{};
    std::int32_t error_count{};
    std::string command_name{};
    std::string error_list{};
};

struct MobBorn {
    std::int32_t baby_type{};
    std::int32_t baby_variant{};
    std::uint8_t baby_color{};
};

struct POICauldronUsed {
    base::MinecraftEventing::POIBlockInteractionType interaction_type{};
    std::int32_t item_id{};
};

struct ComposterUsed {
    base::MinecraftEventing::POIBlockInteractionType interaction_type{};
    std::int32_t item_id{};
};

struct BellUsed {
    std::int32_t item_id{};
};

struct ActorDefinition {
    std::string event_name{};
};

struct RaidUpdate {
    std::int32_t current_wave{};
    std::int32_t total_waves{};
    bool success{};
};

struct TargetBlockHit {
    std::int32_t redstone_level{};
};

struct PiglinBarter {
    std::int32_t item_id{};
    bool was_targeting_bartering_player{};
};

struct PlayerWaxedOrUnwaxedCopper {
    std::int32_t block_id{};
};

struct CodeBuilderRuntimeAction {
    std::string runtime_action{};
};

struct CodeBuilderScoreboard {
    std::string objective_name{};
    std::int32_t score{};
};

struct ItemUsed {
    std::int16_t item_id{};
    std::int32_t item_aux{};
    std::int32_t use_method{};
    std::int32_t count{};
};

struct Empty {
};

}  // namespace LegacyTelemetryEventPacket_nested

struct LegacyTelemetryEventPacket {
    using Type = LegacyTelemetryEventPacket_nested::Type;
    using Achievement = LegacyTelemetryEventPacket_nested::Achievement;
    using Interaction = LegacyTelemetryEventPacket_nested::Interaction;
    using PortalCreated = LegacyTelemetryEventPacket_nested::PortalCreated;
    using PortalUsed = LegacyTelemetryEventPacket_nested::PortalUsed;
    using MobKilled = LegacyTelemetryEventPacket_nested::MobKilled;
    using CauldronUsed = LegacyTelemetryEventPacket_nested::CauldronUsed;
    using PlayerDied = LegacyTelemetryEventPacket_nested::PlayerDied;
    using BossKilled = LegacyTelemetryEventPacket_nested::BossKilled;
    using SlashCommand = LegacyTelemetryEventPacket_nested::SlashCommand;
    using MobBorn = LegacyTelemetryEventPacket_nested::MobBorn;
    using POICauldronUsed = LegacyTelemetryEventPacket_nested::POICauldronUsed;
    using ComposterUsed = LegacyTelemetryEventPacket_nested::ComposterUsed;
    using BellUsed = LegacyTelemetryEventPacket_nested::BellUsed;
    using ActorDefinition = LegacyTelemetryEventPacket_nested::ActorDefinition;
    using RaidUpdate = LegacyTelemetryEventPacket_nested::RaidUpdate;
    using TargetBlockHit = LegacyTelemetryEventPacket_nested::TargetBlockHit;
    using PiglinBarter = LegacyTelemetryEventPacket_nested::PiglinBarter;
    using PlayerWaxedOrUnwaxedCopper = LegacyTelemetryEventPacket_nested::PlayerWaxedOrUnwaxedCopper;
    using CodeBuilderRuntimeAction = LegacyTelemetryEventPacket_nested::CodeBuilderRuntimeAction;
    using CodeBuilderScoreboard = LegacyTelemetryEventPacket_nested::CodeBuilderScoreboard;
    using ItemUsed = LegacyTelemetryEventPacket_nested::ItemUsed;
    using Empty = LegacyTelemetryEventPacket_nested::Empty;

    static constexpr int Id = 65;
    ActorUniqueID player_unique_id{};
    base::LegacyTelemetryEventPacket::Type type{};
    bool use_player_id{};
    std::variant<base::LegacyTelemetryEventPacket::Achievement, base::LegacyTelemetryEventPacket::Interaction, base::LegacyTelemetryEventPacket::PortalCreated, base::LegacyTelemetryEventPacket::PortalUsed, base::LegacyTelemetryEventPacket::MobKilled, base::LegacyTelemetryEventPacket::CauldronUsed, base::LegacyTelemetryEventPacket::PlayerDied, base::LegacyTelemetryEventPacket::BossKilled, base::LegacyTelemetryEventPacket::SlashCommand, base::LegacyTelemetryEventPacket::MobBorn, base::LegacyTelemetryEventPacket::POICauldronUsed, base::LegacyTelemetryEventPacket::ComposterUsed, base::LegacyTelemetryEventPacket::BellUsed, base::LegacyTelemetryEventPacket::ActorDefinition, base::LegacyTelemetryEventPacket::RaidUpdate, base::LegacyTelemetryEventPacket::TargetBlockHit, base::LegacyTelemetryEventPacket::PiglinBarter, base::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, base::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, base::LegacyTelemetryEventPacket::CodeBuilderScoreboard, base::LegacyTelemetryEventPacket::ItemUsed, base::LegacyTelemetryEventPacket::Empty> event_data{};
};

}  // namespace base

namespace v766 {

namespace MinecraftEventing_nested {

enum class InteractionType : std::uint8_t {
    Breeding = 1,
    Taming = 2,
    Curing = 3,
    Crafted = 4,
    Shearing = 5,
    Milking = 6,
    Trading = 7,
    Feeding = 8,
    Igniting = 9,
    Coloring = 10,
    Naming = 11,
    Leashing = 12,
    Unleashing = 13,
    PetSleep = 14,
    Trusting = 15,
    Commanding = 16,
};

enum class AchievementIds : std::uint8_t {
    ChestFullOfCobblestone = 7,
    DiamondForYou = 10,
    IronBelly = 20,
    IronMan = 21,
    OnARail = 29,
    Overkill = 30,
    ReturnToSender = 37,
    SniperDuel = 38,
    StayinFrosty = 39,
    TakeInventory = 40,
    MapRoom = 50,
    FreightStation = 52,
    SmeltEverything = 53,
    TasteOfYourOwnMedicine = 54,
    WhenPigsFly = 56,
    Inception = 58,
    ArtificialSelection = 60,
    FreeDiver = 61,
    SpawnTheWither = 62,
    Beaconator = 63,
    GreatView = 64,
    SuperSonic = 65,
    TheEndAgain = 66,
    TreasureHunter = 67,
    ShootingStar = 68,
    FashionShow = 69,
    Brilliance = 70,
    SelfPublishedAuthor = 71,
    AlternativeFuel = 72,
    SleepWithTheFishes = 73,
    Castaway = 74,
    ImAMarineBiologist = 75,
    SailThe7Seas = 76,
    MeGold = 77,
    Ahoy = 78,
    Atlantis = 79,
    OnePickleTwoPickleSeaPickleFour = 80,
    DoaBarrelRoll = 81,
    Moskstraumen = 82,
    Echolocation = 83,
    WhereHaveYouBeen = 84,
    TopOfTheWorld = 85,
    FruitOnTheLoom = 86,
    SoundTheAlarm = 87,
    BuyLowSellHigh = 88,
    Disenchanted = 89,
    TimeForStew = 90,
    BeeOurGuest = 91,
    TotalBeeLocation = 92,
    StickySituation = 93,
    CoverMeInDebris = 94,
    FloatYourGoat = 95,
    Friend = 96,
    WaxOnWaxOff = 97,
    StriderRiddenInLavaInOverworld = 98,
    GoatHornAcquired = 99,
    JukeboxUsedInMeadows = 100,
    TradedAtWorldHeight = 101,
    SurvivedFallFromWorldHeight = 102,
    SneakCloseToSculkSensor = 103,
    ItSpreads = 104,
    BirthdaySong = 105,
    WithOurPowersCombined = 106,
    PlantingThePast = 107,
    CarefulRestoration = 108,
    Revaulting = 109,
    CraftersCraftingCrafters = 110,
    WhoNeedsRockets = 111,
    OverOverkill = 112,
    HeartTransplanter = 113,
    Count = 114,
};

using POIBlockInteractionType = base::MinecraftEventing::POIBlockInteractionType;

}  // namespace MinecraftEventing_nested

struct MinecraftEventing {
    using InteractionType = MinecraftEventing_nested::InteractionType;
    using AchievementIds = MinecraftEventing_nested::AchievementIds;
    using POIBlockInteractionType = MinecraftEventing_nested::POIBlockInteractionType;
};

namespace LegacyTelemetryEventPacket_nested {

using Type = base::LegacyTelemetryEventPacket::Type;

struct Achievement {
    v766::MinecraftEventing::AchievementIds achievement_id{};
};

struct Interaction {
    ActorUniqueID interacted_entity_id{};
    v766::MinecraftEventing::InteractionType interaction_type{};
    std::int32_t interacted_entity_type{};
    std::int32_t interacted_entity_variant{};
    std::uint8_t interacted_entity_color{};
};

using PortalCreated = base::LegacyTelemetryEventPacket::PortalCreated;
using PortalUsed = base::LegacyTelemetryEventPacket::PortalUsed;

struct MobKilled {
    ActorUniqueID killer_entity_id{};
    ActorUniqueID killed_mob_id{};
    v766::ActorType damage_child_type{};
    std::int32_t damage_source{};
    std::int32_t trader_tier{};
    std::string trader_name{};
};

using CauldronUsed = base::LegacyTelemetryEventPacket::CauldronUsed;
using PlayerDied = base::LegacyTelemetryEventPacket::PlayerDied;
using BossKilled = base::LegacyTelemetryEventPacket::BossKilled;
using SlashCommand = base::LegacyTelemetryEventPacket::SlashCommand;
using MobBorn = base::LegacyTelemetryEventPacket::MobBorn;

struct POICauldronUsed {
    v766::MinecraftEventing::POIBlockInteractionType interaction_type{};
    std::int32_t item_id{};
};

struct ComposterUsed {
    v766::MinecraftEventing::POIBlockInteractionType interaction_type{};
    std::int32_t item_id{};
};

using BellUsed = base::LegacyTelemetryEventPacket::BellUsed;
using ActorDefinition = base::LegacyTelemetryEventPacket::ActorDefinition;
using RaidUpdate = base::LegacyTelemetryEventPacket::RaidUpdate;
using TargetBlockHit = base::LegacyTelemetryEventPacket::TargetBlockHit;
using PiglinBarter = base::LegacyTelemetryEventPacket::PiglinBarter;
using PlayerWaxedOrUnwaxedCopper = base::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper;
using CodeBuilderRuntimeAction = base::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction;
using CodeBuilderScoreboard = base::LegacyTelemetryEventPacket::CodeBuilderScoreboard;
using ItemUsed = base::LegacyTelemetryEventPacket::ItemUsed;
using Empty = base::LegacyTelemetryEventPacket::Empty;

}  // namespace LegacyTelemetryEventPacket_nested

struct LegacyTelemetryEventPacket {
    using Type = LegacyTelemetryEventPacket_nested::Type;
    using Achievement = LegacyTelemetryEventPacket_nested::Achievement;
    using Interaction = LegacyTelemetryEventPacket_nested::Interaction;
    using PortalCreated = LegacyTelemetryEventPacket_nested::PortalCreated;
    using PortalUsed = LegacyTelemetryEventPacket_nested::PortalUsed;
    using MobKilled = LegacyTelemetryEventPacket_nested::MobKilled;
    using CauldronUsed = LegacyTelemetryEventPacket_nested::CauldronUsed;
    using PlayerDied = LegacyTelemetryEventPacket_nested::PlayerDied;
    using BossKilled = LegacyTelemetryEventPacket_nested::BossKilled;
    using SlashCommand = LegacyTelemetryEventPacket_nested::SlashCommand;
    using MobBorn = LegacyTelemetryEventPacket_nested::MobBorn;
    using POICauldronUsed = LegacyTelemetryEventPacket_nested::POICauldronUsed;
    using ComposterUsed = LegacyTelemetryEventPacket_nested::ComposterUsed;
    using BellUsed = LegacyTelemetryEventPacket_nested::BellUsed;
    using ActorDefinition = LegacyTelemetryEventPacket_nested::ActorDefinition;
    using RaidUpdate = LegacyTelemetryEventPacket_nested::RaidUpdate;
    using TargetBlockHit = LegacyTelemetryEventPacket_nested::TargetBlockHit;
    using PiglinBarter = LegacyTelemetryEventPacket_nested::PiglinBarter;
    using PlayerWaxedOrUnwaxedCopper = LegacyTelemetryEventPacket_nested::PlayerWaxedOrUnwaxedCopper;
    using CodeBuilderRuntimeAction = LegacyTelemetryEventPacket_nested::CodeBuilderRuntimeAction;
    using CodeBuilderScoreboard = LegacyTelemetryEventPacket_nested::CodeBuilderScoreboard;
    using ItemUsed = LegacyTelemetryEventPacket_nested::ItemUsed;
    using Empty = LegacyTelemetryEventPacket_nested::Empty;

    static constexpr int Id = 65;
    ActorUniqueID player_unique_id{};
    v766::LegacyTelemetryEventPacket::Type type{};
    bool use_player_id{};
    std::variant<v766::LegacyTelemetryEventPacket::Achievement, v766::LegacyTelemetryEventPacket::Interaction, v766::LegacyTelemetryEventPacket::PortalCreated, v766::LegacyTelemetryEventPacket::PortalUsed, v766::LegacyTelemetryEventPacket::MobKilled, v766::LegacyTelemetryEventPacket::CauldronUsed, v766::LegacyTelemetryEventPacket::PlayerDied, v766::LegacyTelemetryEventPacket::BossKilled, v766::LegacyTelemetryEventPacket::SlashCommand, v766::LegacyTelemetryEventPacket::MobBorn, v766::LegacyTelemetryEventPacket::POICauldronUsed, v766::LegacyTelemetryEventPacket::ComposterUsed, v766::LegacyTelemetryEventPacket::BellUsed, v766::LegacyTelemetryEventPacket::ActorDefinition, v766::LegacyTelemetryEventPacket::RaidUpdate, v766::LegacyTelemetryEventPacket::TargetBlockHit, v766::LegacyTelemetryEventPacket::PiglinBarter, v766::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v766::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v766::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v766::LegacyTelemetryEventPacket::ItemUsed, v766::LegacyTelemetryEventPacket::Empty> event_data{};
};

}  // namespace v766

namespace v776 {

namespace MinecraftEventing_nested {

enum class InteractionType : std::uint8_t {
    Breeding = 1,
    Taming = 2,
    Curing = 3,
    Crafted = 4,
    Shearing = 5,
    Milking = 6,
    Trading = 7,
    Feeding = 8,
    Igniting = 9,
    Coloring = 10,
    Naming = 11,
    Leashing = 12,
    Unleashing = 13,
    PetSleep = 14,
    Trusting = 15,
    Commanding = 16,
};

enum class AchievementIds : std::uint8_t {
    ChestFullOfCobblestone = 7,
    DiamondForYou = 10,
    IronBelly = 20,
    IronMan = 21,
    OnARail = 29,
    Overkill = 30,
    ReturnToSender = 37,
    SniperDuel = 38,
    StayinFrosty = 39,
    TakeInventory = 40,
    MapRoom = 50,
    FreightStation = 52,
    SmeltEverything = 53,
    TasteOfYourOwnMedicine = 54,
    WhenPigsFly = 56,
    Inception = 58,
    ArtificialSelection = 60,
    FreeDiver = 61,
    SpawnTheWither = 62,
    Beaconator = 63,
    GreatView = 64,
    SuperSonic = 65,
    TheEndAgain = 66,
    TreasureHunter = 67,
    ShootingStar = 68,
    FashionShow = 69,
    SelfPublishedAuthor = 71,
    AlternativeFuel = 72,
    SleepWithTheFishes = 73,
    Castaway = 74,
    ImAMarineBiologist = 75,
    SailThe7Seas = 76,
    MeGold = 77,
    Ahoy = 78,
    Atlantis = 79,
    OnePickleTwoPickleSeaPickleFour = 80,
    DoaBarrelRoll = 81,
    Moskstraumen = 82,
    Echolocation = 83,
    WhereHaveYouBeen = 84,
    TopOfTheWorld = 85,
    FruitOnTheLoom = 86,
    SoundTheAlarm = 87,
    BuyLowSellHigh = 88,
    Disenchanted = 89,
    TimeForStew = 90,
    BeeOurGuest = 91,
    TotalBeeLocation = 92,
    StickySituation = 93,
    CoverMeInDebris = 94,
    FloatYourGoat = 95,
    Friend = 96,
    WaxOnWaxOff = 97,
    StriderRiddenInLavaInOverworld = 98,
    GoatHornAcquired = 99,
    JukeboxUsedInMeadows = 100,
    TradedAtWorldHeight = 101,
    SurvivedFallFromWorldHeight = 102,
    SneakCloseToSculkSensor = 103,
    ItSpreads = 104,
    BirthdaySong = 105,
    WithOurPowersCombined = 106,
    PlantingThePast = 107,
    CarefulRestoration = 108,
    Revaulting = 109,
    CraftersCraftingCrafters = 110,
    WhoNeedsRockets = 111,
    OverOverkill = 112,
    HeartTransplanter = 113,
    Count = 114,
};

using POIBlockInteractionType = base::MinecraftEventing::POIBlockInteractionType;

}  // namespace MinecraftEventing_nested

struct MinecraftEventing {
    using InteractionType = MinecraftEventing_nested::InteractionType;
    using AchievementIds = MinecraftEventing_nested::AchievementIds;
    using POIBlockInteractionType = MinecraftEventing_nested::POIBlockInteractionType;
};

namespace LegacyTelemetryEventPacket_nested {

using Type = base::LegacyTelemetryEventPacket::Type;

struct Achievement {
    v776::MinecraftEventing::AchievementIds achievement_id{};
};

struct Interaction {
    ActorUniqueID interacted_entity_id{};
    v776::MinecraftEventing::InteractionType interaction_type{};
    std::int32_t interacted_entity_type{};
    std::int32_t interacted_entity_variant{};
    std::uint8_t interacted_entity_color{};
};

using PortalCreated = base::LegacyTelemetryEventPacket::PortalCreated;
using PortalUsed = base::LegacyTelemetryEventPacket::PortalUsed;

struct MobKilled {
    ActorUniqueID killer_entity_id{};
    ActorUniqueID killed_mob_id{};
    v766::ActorType damage_child_type{};
    std::int32_t damage_source{};
    std::int32_t trader_tier{};
    std::string trader_name{};
};

using CauldronUsed = base::LegacyTelemetryEventPacket::CauldronUsed;
using PlayerDied = base::LegacyTelemetryEventPacket::PlayerDied;
using BossKilled = base::LegacyTelemetryEventPacket::BossKilled;
using SlashCommand = base::LegacyTelemetryEventPacket::SlashCommand;
using MobBorn = base::LegacyTelemetryEventPacket::MobBorn;

struct POICauldronUsed {
    v776::MinecraftEventing::POIBlockInteractionType interaction_type{};
    std::int32_t item_id{};
};

struct ComposterUsed {
    v776::MinecraftEventing::POIBlockInteractionType interaction_type{};
    std::int32_t item_id{};
};

using BellUsed = base::LegacyTelemetryEventPacket::BellUsed;
using ActorDefinition = base::LegacyTelemetryEventPacket::ActorDefinition;
using RaidUpdate = base::LegacyTelemetryEventPacket::RaidUpdate;
using TargetBlockHit = base::LegacyTelemetryEventPacket::TargetBlockHit;
using PiglinBarter = base::LegacyTelemetryEventPacket::PiglinBarter;
using PlayerWaxedOrUnwaxedCopper = base::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper;
using CodeBuilderRuntimeAction = base::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction;
using CodeBuilderScoreboard = base::LegacyTelemetryEventPacket::CodeBuilderScoreboard;
using ItemUsed = base::LegacyTelemetryEventPacket::ItemUsed;
using Empty = base::LegacyTelemetryEventPacket::Empty;

}  // namespace LegacyTelemetryEventPacket_nested

struct LegacyTelemetryEventPacket {
    using Type = LegacyTelemetryEventPacket_nested::Type;
    using Achievement = LegacyTelemetryEventPacket_nested::Achievement;
    using Interaction = LegacyTelemetryEventPacket_nested::Interaction;
    using PortalCreated = LegacyTelemetryEventPacket_nested::PortalCreated;
    using PortalUsed = LegacyTelemetryEventPacket_nested::PortalUsed;
    using MobKilled = LegacyTelemetryEventPacket_nested::MobKilled;
    using CauldronUsed = LegacyTelemetryEventPacket_nested::CauldronUsed;
    using PlayerDied = LegacyTelemetryEventPacket_nested::PlayerDied;
    using BossKilled = LegacyTelemetryEventPacket_nested::BossKilled;
    using SlashCommand = LegacyTelemetryEventPacket_nested::SlashCommand;
    using MobBorn = LegacyTelemetryEventPacket_nested::MobBorn;
    using POICauldronUsed = LegacyTelemetryEventPacket_nested::POICauldronUsed;
    using ComposterUsed = LegacyTelemetryEventPacket_nested::ComposterUsed;
    using BellUsed = LegacyTelemetryEventPacket_nested::BellUsed;
    using ActorDefinition = LegacyTelemetryEventPacket_nested::ActorDefinition;
    using RaidUpdate = LegacyTelemetryEventPacket_nested::RaidUpdate;
    using TargetBlockHit = LegacyTelemetryEventPacket_nested::TargetBlockHit;
    using PiglinBarter = LegacyTelemetryEventPacket_nested::PiglinBarter;
    using PlayerWaxedOrUnwaxedCopper = LegacyTelemetryEventPacket_nested::PlayerWaxedOrUnwaxedCopper;
    using CodeBuilderRuntimeAction = LegacyTelemetryEventPacket_nested::CodeBuilderRuntimeAction;
    using CodeBuilderScoreboard = LegacyTelemetryEventPacket_nested::CodeBuilderScoreboard;
    using ItemUsed = LegacyTelemetryEventPacket_nested::ItemUsed;
    using Empty = LegacyTelemetryEventPacket_nested::Empty;

    static constexpr int Id = 65;
    ActorUniqueID player_unique_id{};
    v776::LegacyTelemetryEventPacket::Type type{};
    bool use_player_id{};
    std::variant<v776::LegacyTelemetryEventPacket::Achievement, v776::LegacyTelemetryEventPacket::Interaction, v776::LegacyTelemetryEventPacket::PortalCreated, v776::LegacyTelemetryEventPacket::PortalUsed, v776::LegacyTelemetryEventPacket::MobKilled, v776::LegacyTelemetryEventPacket::CauldronUsed, v776::LegacyTelemetryEventPacket::PlayerDied, v776::LegacyTelemetryEventPacket::BossKilled, v776::LegacyTelemetryEventPacket::SlashCommand, v776::LegacyTelemetryEventPacket::MobBorn, v776::LegacyTelemetryEventPacket::POICauldronUsed, v776::LegacyTelemetryEventPacket::ComposterUsed, v776::LegacyTelemetryEventPacket::BellUsed, v776::LegacyTelemetryEventPacket::ActorDefinition, v776::LegacyTelemetryEventPacket::RaidUpdate, v776::LegacyTelemetryEventPacket::TargetBlockHit, v776::LegacyTelemetryEventPacket::PiglinBarter, v776::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v776::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v776::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v776::LegacyTelemetryEventPacket::ItemUsed, v776::LegacyTelemetryEventPacket::Empty> event_data{};
};

}  // namespace v776

namespace v786 {

using MinecraftEventing = v776::MinecraftEventing;

using LegacyTelemetryEventPacket = v776::LegacyTelemetryEventPacket;

}  // namespace v786

namespace v800 {

using MinecraftEventing = v776::MinecraftEventing;

namespace LegacyTelemetryEventPacket_nested {

using Type = base::LegacyTelemetryEventPacket::Type;

struct Achievement {
    v776::MinecraftEventing::AchievementIds achievement_id{};
};

struct Interaction {
    ActorUniqueID interacted_entity_id{};
    v776::MinecraftEventing::InteractionType interaction_type{};
    std::int32_t interacted_entity_type{};
    std::int32_t interacted_entity_variant{};
    std::uint8_t interacted_entity_color{};
};

using PortalCreated = base::LegacyTelemetryEventPacket::PortalCreated;
using PortalUsed = base::LegacyTelemetryEventPacket::PortalUsed;

struct MobKilled {
    ActorUniqueID killer_entity_id{};
    ActorUniqueID killed_mob_id{};
    v800::ActorType damage_child_type{};
    std::int32_t damage_source{};
    std::int32_t trader_tier{};
    std::string trader_name{};
};

using CauldronUsed = base::LegacyTelemetryEventPacket::CauldronUsed;
using PlayerDied = base::LegacyTelemetryEventPacket::PlayerDied;
using BossKilled = base::LegacyTelemetryEventPacket::BossKilled;
using SlashCommand = base::LegacyTelemetryEventPacket::SlashCommand;
using MobBorn = base::LegacyTelemetryEventPacket::MobBorn;

struct POICauldronUsed {
    v776::MinecraftEventing::POIBlockInteractionType interaction_type{};
    std::int32_t item_id{};
};

struct ComposterUsed {
    v776::MinecraftEventing::POIBlockInteractionType interaction_type{};
    std::int32_t item_id{};
};

using BellUsed = base::LegacyTelemetryEventPacket::BellUsed;
using ActorDefinition = base::LegacyTelemetryEventPacket::ActorDefinition;
using RaidUpdate = base::LegacyTelemetryEventPacket::RaidUpdate;
using TargetBlockHit = base::LegacyTelemetryEventPacket::TargetBlockHit;
using PiglinBarter = base::LegacyTelemetryEventPacket::PiglinBarter;
using PlayerWaxedOrUnwaxedCopper = base::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper;
using CodeBuilderRuntimeAction = base::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction;
using CodeBuilderScoreboard = base::LegacyTelemetryEventPacket::CodeBuilderScoreboard;
using ItemUsed = base::LegacyTelemetryEventPacket::ItemUsed;
using Empty = base::LegacyTelemetryEventPacket::Empty;

}  // namespace LegacyTelemetryEventPacket_nested

struct LegacyTelemetryEventPacket {
    using Type = LegacyTelemetryEventPacket_nested::Type;
    using Achievement = LegacyTelemetryEventPacket_nested::Achievement;
    using Interaction = LegacyTelemetryEventPacket_nested::Interaction;
    using PortalCreated = LegacyTelemetryEventPacket_nested::PortalCreated;
    using PortalUsed = LegacyTelemetryEventPacket_nested::PortalUsed;
    using MobKilled = LegacyTelemetryEventPacket_nested::MobKilled;
    using CauldronUsed = LegacyTelemetryEventPacket_nested::CauldronUsed;
    using PlayerDied = LegacyTelemetryEventPacket_nested::PlayerDied;
    using BossKilled = LegacyTelemetryEventPacket_nested::BossKilled;
    using SlashCommand = LegacyTelemetryEventPacket_nested::SlashCommand;
    using MobBorn = LegacyTelemetryEventPacket_nested::MobBorn;
    using POICauldronUsed = LegacyTelemetryEventPacket_nested::POICauldronUsed;
    using ComposterUsed = LegacyTelemetryEventPacket_nested::ComposterUsed;
    using BellUsed = LegacyTelemetryEventPacket_nested::BellUsed;
    using ActorDefinition = LegacyTelemetryEventPacket_nested::ActorDefinition;
    using RaidUpdate = LegacyTelemetryEventPacket_nested::RaidUpdate;
    using TargetBlockHit = LegacyTelemetryEventPacket_nested::TargetBlockHit;
    using PiglinBarter = LegacyTelemetryEventPacket_nested::PiglinBarter;
    using PlayerWaxedOrUnwaxedCopper = LegacyTelemetryEventPacket_nested::PlayerWaxedOrUnwaxedCopper;
    using CodeBuilderRuntimeAction = LegacyTelemetryEventPacket_nested::CodeBuilderRuntimeAction;
    using CodeBuilderScoreboard = LegacyTelemetryEventPacket_nested::CodeBuilderScoreboard;
    using ItemUsed = LegacyTelemetryEventPacket_nested::ItemUsed;
    using Empty = LegacyTelemetryEventPacket_nested::Empty;

    static constexpr int Id = 65;
    ActorUniqueID player_unique_id{};
    v800::LegacyTelemetryEventPacket::Type type{};
    bool use_player_id{};
    std::variant<v800::LegacyTelemetryEventPacket::Achievement, v800::LegacyTelemetryEventPacket::Interaction, v800::LegacyTelemetryEventPacket::PortalCreated, v800::LegacyTelemetryEventPacket::PortalUsed, v800::LegacyTelemetryEventPacket::MobKilled, v800::LegacyTelemetryEventPacket::CauldronUsed, v800::LegacyTelemetryEventPacket::PlayerDied, v800::LegacyTelemetryEventPacket::BossKilled, v800::LegacyTelemetryEventPacket::SlashCommand, v800::LegacyTelemetryEventPacket::MobBorn, v800::LegacyTelemetryEventPacket::POICauldronUsed, v800::LegacyTelemetryEventPacket::ComposterUsed, v800::LegacyTelemetryEventPacket::BellUsed, v800::LegacyTelemetryEventPacket::ActorDefinition, v800::LegacyTelemetryEventPacket::RaidUpdate, v800::LegacyTelemetryEventPacket::TargetBlockHit, v800::LegacyTelemetryEventPacket::PiglinBarter, v800::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v800::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v800::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v800::LegacyTelemetryEventPacket::ItemUsed, v800::LegacyTelemetryEventPacket::Empty> event_data{};
};

}  // namespace v800

namespace v818 {

namespace MinecraftEventing_nested {

enum class InteractionType : std::uint8_t {
    Breeding = 1,
    Taming = 2,
    Curing = 3,
    Crafted = 4,
    Shearing = 5,
    Milking = 6,
    Trading = 7,
    Feeding = 8,
    Igniting = 9,
    Coloring = 10,
    Naming = 11,
    Leashing = 12,
    Unleashing = 13,
    PetSleep = 14,
    Trusting = 15,
    Commanding = 16,
};

enum class AchievementIds : std::uint8_t {
    ChestFullOfCobblestone = 7,
    DiamondForYou = 10,
    IronBelly = 20,
    IronMan = 21,
    OnARail = 29,
    Overkill = 30,
    ReturnToSender = 37,
    SniperDuel = 38,
    StayinFrosty = 39,
    TakeInventory = 40,
    MapRoom = 50,
    FreightStation = 52,
    SmeltEverything = 53,
    TasteOfYourOwnMedicine = 54,
    WhenPigsFly = 56,
    Inception = 58,
    ArtificialSelection = 60,
    FreeDiver = 61,
    SpawnTheWither = 62,
    Beaconator = 63,
    GreatView = 64,
    SuperSonic = 65,
    TheEndAgain = 66,
    TreasureHunter = 67,
    ShootingStar = 68,
    FashionShow = 69,
    SelfPublishedAuthor = 71,
    AlternativeFuel = 72,
    SleepWithTheFishes = 73,
    Castaway = 74,
    ImAMarineBiologist = 75,
    SailThe7Seas = 76,
    MeGold = 77,
    Ahoy = 78,
    Atlantis = 79,
    OnePickleTwoPickleSeaPickleFour = 80,
    DoaBarrelRoll = 81,
    Moskstraumen = 82,
    Echolocation = 83,
    WhereHaveYouBeen = 84,
    TopOfTheWorld = 85,
    FruitOnTheLoom = 86,
    SoundTheAlarm = 87,
    BuyLowSellHigh = 88,
    Disenchanted = 89,
    TimeForStew = 90,
    BeeOurGuest = 91,
    TotalBeeLocation = 92,
    StickySituation = 93,
    CoverMeInDebris = 94,
    FloatYourGoat = 95,
    Friend = 96,
    WaxOnWaxOff = 97,
    StriderRiddenInLavaInOverworld = 98,
    GoatHornAcquired = 99,
    JukeboxUsedInMeadows = 100,
    TradedAtWorldHeight = 101,
    SurvivedFallFromWorldHeight = 102,
    SneakCloseToSculkSensor = 103,
    ItSpreads = 104,
    BirthdaySong = 105,
    WithOurPowersCombined = 106,
    PlantingThePast = 107,
    CarefulRestoration = 108,
    Revaulting = 109,
    CraftersCraftingCrafters = 110,
    WhoNeedsRockets = 111,
    OverOverkill = 112,
    HeartTransplanter = 113,
    StayHydrated = 114,
    Count = 115,
};

using POIBlockInteractionType = base::MinecraftEventing::POIBlockInteractionType;

}  // namespace MinecraftEventing_nested

struct MinecraftEventing {
    using InteractionType = MinecraftEventing_nested::InteractionType;
    using AchievementIds = MinecraftEventing_nested::AchievementIds;
    using POIBlockInteractionType = MinecraftEventing_nested::POIBlockInteractionType;
};

namespace LegacyTelemetryEventPacket_nested {

using Type = base::LegacyTelemetryEventPacket::Type;

struct Achievement {
    v818::MinecraftEventing::AchievementIds achievement_id{};
};

struct Interaction {
    ActorUniqueID interacted_entity_id{};
    v818::MinecraftEventing::InteractionType interaction_type{};
    std::int32_t interacted_entity_type{};
    std::int32_t interacted_entity_variant{};
    std::uint8_t interacted_entity_color{};
};

using PortalCreated = base::LegacyTelemetryEventPacket::PortalCreated;
using PortalUsed = base::LegacyTelemetryEventPacket::PortalUsed;

struct MobKilled {
    ActorUniqueID killer_entity_id{};
    ActorUniqueID killed_mob_id{};
    v800::ActorType damage_child_type{};
    std::int32_t damage_source{};
    std::int32_t trader_tier{};
    std::string trader_name{};
};

using CauldronUsed = base::LegacyTelemetryEventPacket::CauldronUsed;
using PlayerDied = base::LegacyTelemetryEventPacket::PlayerDied;
using BossKilled = base::LegacyTelemetryEventPacket::BossKilled;
using SlashCommand = base::LegacyTelemetryEventPacket::SlashCommand;
using MobBorn = base::LegacyTelemetryEventPacket::MobBorn;

struct POICauldronUsed {
    v818::MinecraftEventing::POIBlockInteractionType interaction_type{};
    std::int32_t item_id{};
};

struct ComposterUsed {
    v818::MinecraftEventing::POIBlockInteractionType interaction_type{};
    std::int32_t item_id{};
};

using BellUsed = base::LegacyTelemetryEventPacket::BellUsed;
using ActorDefinition = base::LegacyTelemetryEventPacket::ActorDefinition;
using RaidUpdate = base::LegacyTelemetryEventPacket::RaidUpdate;
using TargetBlockHit = base::LegacyTelemetryEventPacket::TargetBlockHit;
using PiglinBarter = base::LegacyTelemetryEventPacket::PiglinBarter;
using PlayerWaxedOrUnwaxedCopper = base::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper;
using CodeBuilderRuntimeAction = base::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction;
using CodeBuilderScoreboard = base::LegacyTelemetryEventPacket::CodeBuilderScoreboard;
using ItemUsed = base::LegacyTelemetryEventPacket::ItemUsed;
using Empty = base::LegacyTelemetryEventPacket::Empty;

}  // namespace LegacyTelemetryEventPacket_nested

struct LegacyTelemetryEventPacket {
    using Type = LegacyTelemetryEventPacket_nested::Type;
    using Achievement = LegacyTelemetryEventPacket_nested::Achievement;
    using Interaction = LegacyTelemetryEventPacket_nested::Interaction;
    using PortalCreated = LegacyTelemetryEventPacket_nested::PortalCreated;
    using PortalUsed = LegacyTelemetryEventPacket_nested::PortalUsed;
    using MobKilled = LegacyTelemetryEventPacket_nested::MobKilled;
    using CauldronUsed = LegacyTelemetryEventPacket_nested::CauldronUsed;
    using PlayerDied = LegacyTelemetryEventPacket_nested::PlayerDied;
    using BossKilled = LegacyTelemetryEventPacket_nested::BossKilled;
    using SlashCommand = LegacyTelemetryEventPacket_nested::SlashCommand;
    using MobBorn = LegacyTelemetryEventPacket_nested::MobBorn;
    using POICauldronUsed = LegacyTelemetryEventPacket_nested::POICauldronUsed;
    using ComposterUsed = LegacyTelemetryEventPacket_nested::ComposterUsed;
    using BellUsed = LegacyTelemetryEventPacket_nested::BellUsed;
    using ActorDefinition = LegacyTelemetryEventPacket_nested::ActorDefinition;
    using RaidUpdate = LegacyTelemetryEventPacket_nested::RaidUpdate;
    using TargetBlockHit = LegacyTelemetryEventPacket_nested::TargetBlockHit;
    using PiglinBarter = LegacyTelemetryEventPacket_nested::PiglinBarter;
    using PlayerWaxedOrUnwaxedCopper = LegacyTelemetryEventPacket_nested::PlayerWaxedOrUnwaxedCopper;
    using CodeBuilderRuntimeAction = LegacyTelemetryEventPacket_nested::CodeBuilderRuntimeAction;
    using CodeBuilderScoreboard = LegacyTelemetryEventPacket_nested::CodeBuilderScoreboard;
    using ItemUsed = LegacyTelemetryEventPacket_nested::ItemUsed;
    using Empty = LegacyTelemetryEventPacket_nested::Empty;

    static constexpr int Id = 65;
    ActorUniqueID player_unique_id{};
    v818::LegacyTelemetryEventPacket::Type type{};
    bool use_player_id{};
    std::variant<v818::LegacyTelemetryEventPacket::Achievement, v818::LegacyTelemetryEventPacket::Interaction, v818::LegacyTelemetryEventPacket::PortalCreated, v818::LegacyTelemetryEventPacket::PortalUsed, v818::LegacyTelemetryEventPacket::MobKilled, v818::LegacyTelemetryEventPacket::CauldronUsed, v818::LegacyTelemetryEventPacket::PlayerDied, v818::LegacyTelemetryEventPacket::BossKilled, v818::LegacyTelemetryEventPacket::SlashCommand, v818::LegacyTelemetryEventPacket::MobBorn, v818::LegacyTelemetryEventPacket::POICauldronUsed, v818::LegacyTelemetryEventPacket::ComposterUsed, v818::LegacyTelemetryEventPacket::BellUsed, v818::LegacyTelemetryEventPacket::ActorDefinition, v818::LegacyTelemetryEventPacket::RaidUpdate, v818::LegacyTelemetryEventPacket::TargetBlockHit, v818::LegacyTelemetryEventPacket::PiglinBarter, v818::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v818::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v818::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v818::LegacyTelemetryEventPacket::ItemUsed, v818::LegacyTelemetryEventPacket::Empty> event_data{};
};

}  // namespace v818

namespace v827 {

using MinecraftEventing = v818::MinecraftEventing;

namespace LegacyTelemetryEventPacket_nested {

using Type = base::LegacyTelemetryEventPacket::Type;

struct Achievement {
    v818::MinecraftEventing::AchievementIds achievement_id{};
};

struct Interaction {
    ActorUniqueID interacted_entity_id{};
    v818::MinecraftEventing::InteractionType interaction_type{};
    std::int32_t interacted_entity_type{};
    std::int32_t interacted_entity_variant{};
    std::uint8_t interacted_entity_color{};
};

using PortalCreated = base::LegacyTelemetryEventPacket::PortalCreated;
using PortalUsed = base::LegacyTelemetryEventPacket::PortalUsed;

struct MobKilled {
    ActorUniqueID killer_entity_id{};
    ActorUniqueID killed_mob_id{};
    v827::ActorType damage_child_type{};
    std::int32_t damage_source{};
    std::int32_t trader_tier{};
    std::string trader_name{};
};

using CauldronUsed = base::LegacyTelemetryEventPacket::CauldronUsed;
using PlayerDied = base::LegacyTelemetryEventPacket::PlayerDied;
using BossKilled = base::LegacyTelemetryEventPacket::BossKilled;
using SlashCommand = base::LegacyTelemetryEventPacket::SlashCommand;
using MobBorn = base::LegacyTelemetryEventPacket::MobBorn;

struct POICauldronUsed {
    v818::MinecraftEventing::POIBlockInteractionType interaction_type{};
    std::int32_t item_id{};
};

struct ComposterUsed {
    v818::MinecraftEventing::POIBlockInteractionType interaction_type{};
    std::int32_t item_id{};
};

using BellUsed = base::LegacyTelemetryEventPacket::BellUsed;
using ActorDefinition = base::LegacyTelemetryEventPacket::ActorDefinition;
using RaidUpdate = base::LegacyTelemetryEventPacket::RaidUpdate;
using TargetBlockHit = base::LegacyTelemetryEventPacket::TargetBlockHit;
using PiglinBarter = base::LegacyTelemetryEventPacket::PiglinBarter;
using PlayerWaxedOrUnwaxedCopper = base::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper;
using CodeBuilderRuntimeAction = base::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction;
using CodeBuilderScoreboard = base::LegacyTelemetryEventPacket::CodeBuilderScoreboard;
using ItemUsed = base::LegacyTelemetryEventPacket::ItemUsed;
using Empty = base::LegacyTelemetryEventPacket::Empty;

}  // namespace LegacyTelemetryEventPacket_nested

struct LegacyTelemetryEventPacket {
    using Type = LegacyTelemetryEventPacket_nested::Type;
    using Achievement = LegacyTelemetryEventPacket_nested::Achievement;
    using Interaction = LegacyTelemetryEventPacket_nested::Interaction;
    using PortalCreated = LegacyTelemetryEventPacket_nested::PortalCreated;
    using PortalUsed = LegacyTelemetryEventPacket_nested::PortalUsed;
    using MobKilled = LegacyTelemetryEventPacket_nested::MobKilled;
    using CauldronUsed = LegacyTelemetryEventPacket_nested::CauldronUsed;
    using PlayerDied = LegacyTelemetryEventPacket_nested::PlayerDied;
    using BossKilled = LegacyTelemetryEventPacket_nested::BossKilled;
    using SlashCommand = LegacyTelemetryEventPacket_nested::SlashCommand;
    using MobBorn = LegacyTelemetryEventPacket_nested::MobBorn;
    using POICauldronUsed = LegacyTelemetryEventPacket_nested::POICauldronUsed;
    using ComposterUsed = LegacyTelemetryEventPacket_nested::ComposterUsed;
    using BellUsed = LegacyTelemetryEventPacket_nested::BellUsed;
    using ActorDefinition = LegacyTelemetryEventPacket_nested::ActorDefinition;
    using RaidUpdate = LegacyTelemetryEventPacket_nested::RaidUpdate;
    using TargetBlockHit = LegacyTelemetryEventPacket_nested::TargetBlockHit;
    using PiglinBarter = LegacyTelemetryEventPacket_nested::PiglinBarter;
    using PlayerWaxedOrUnwaxedCopper = LegacyTelemetryEventPacket_nested::PlayerWaxedOrUnwaxedCopper;
    using CodeBuilderRuntimeAction = LegacyTelemetryEventPacket_nested::CodeBuilderRuntimeAction;
    using CodeBuilderScoreboard = LegacyTelemetryEventPacket_nested::CodeBuilderScoreboard;
    using ItemUsed = LegacyTelemetryEventPacket_nested::ItemUsed;
    using Empty = LegacyTelemetryEventPacket_nested::Empty;

    static constexpr int Id = 65;
    ActorUniqueID player_unique_id{};
    v827::LegacyTelemetryEventPacket::Type type{};
    bool use_player_id{};
    std::variant<v827::LegacyTelemetryEventPacket::Achievement, v827::LegacyTelemetryEventPacket::Interaction, v827::LegacyTelemetryEventPacket::PortalCreated, v827::LegacyTelemetryEventPacket::PortalUsed, v827::LegacyTelemetryEventPacket::MobKilled, v827::LegacyTelemetryEventPacket::CauldronUsed, v827::LegacyTelemetryEventPacket::PlayerDied, v827::LegacyTelemetryEventPacket::BossKilled, v827::LegacyTelemetryEventPacket::SlashCommand, v827::LegacyTelemetryEventPacket::MobBorn, v827::LegacyTelemetryEventPacket::POICauldronUsed, v827::LegacyTelemetryEventPacket::ComposterUsed, v827::LegacyTelemetryEventPacket::BellUsed, v827::LegacyTelemetryEventPacket::ActorDefinition, v827::LegacyTelemetryEventPacket::RaidUpdate, v827::LegacyTelemetryEventPacket::TargetBlockHit, v827::LegacyTelemetryEventPacket::PiglinBarter, v827::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v827::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v827::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v827::LegacyTelemetryEventPacket::ItemUsed, v827::LegacyTelemetryEventPacket::Empty> event_data{};
};

}  // namespace v827

namespace v844 {

using MinecraftEventing = v818::MinecraftEventing;

using LegacyTelemetryEventPacket = v827::LegacyTelemetryEventPacket;

}  // namespace v844

namespace v859 {

using MinecraftEventing = v818::MinecraftEventing;

using LegacyTelemetryEventPacket = v827::LegacyTelemetryEventPacket;

}  // namespace v859

namespace v898 {

namespace MinecraftEventing_nested {

enum class InteractionType : std::uint8_t {
    Breeding = 1,
    Taming = 2,
    Curing = 3,
    Crafted = 4,
    Shearing = 5,
    Milking = 6,
    Trading = 7,
    Feeding = 8,
    Igniting = 9,
    Coloring = 10,
    Naming = 11,
    Leashing = 12,
    Unleashing = 13,
    PetSleep = 14,
    Trusting = 15,
    Commanding = 16,
};

enum class AchievementIds : std::uint8_t {
    ChestFullOfCobblestone = 7,
    DiamondForYou = 10,
    IronBelly = 20,
    IronMan = 21,
    OnARail = 29,
    Overkill = 30,
    ReturnToSender = 37,
    SniperDuel = 38,
    StayinFrosty = 39,
    TakeInventory = 40,
    MapRoom = 50,
    FreightStation = 52,
    SmeltEverything = 53,
    TasteOfYourOwnMedicine = 54,
    WhenPigsFly = 56,
    Inception = 58,
    ArtificialSelection = 60,
    FreeDiver = 61,
    SpawnTheWither = 62,
    Beaconator = 63,
    GreatView = 64,
    SuperSonic = 65,
    TheEndAgain = 66,
    TreasureHunter = 67,
    ShootingStar = 68,
    FashionShow = 69,
    SelfPublishedAuthor = 71,
    AlternativeFuel = 72,
    SleepWithTheFishes = 73,
    Castaway = 74,
    ImAMarineBiologist = 75,
    SailThe7Seas = 76,
    MeGold = 77,
    Ahoy = 78,
    Atlantis = 79,
    OnePickleTwoPickleSeaPickleFour = 80,
    DoaBarrelRoll = 81,
    Moskstraumen = 82,
    Echolocation = 83,
    WhereHaveYouBeen = 84,
    TopOfTheWorld = 85,
    FruitOnTheLoom = 86,
    SoundTheAlarm = 87,
    BuyLowSellHigh = 88,
    Disenchanted = 89,
    TimeForStew = 90,
    BeeOurGuest = 91,
    TotalBeeLocation = 92,
    StickySituation = 93,
    CoverMeInDebris = 94,
    FloatYourGoat = 95,
    Friend = 96,
    WaxOnWaxOff = 97,
    StriderRiddenInLavaInOverworld = 98,
    GoatHornAcquired = 99,
    JukeboxUsedInMeadows = 100,
    TradedAtWorldHeight = 101,
    SurvivedFallFromWorldHeight = 102,
    SneakCloseToSculkSensor = 103,
    ItSpreads = 104,
    BirthdaySong = 105,
    WithOurPowersCombined = 106,
    PlantingThePast = 107,
    CarefulRestoration = 108,
    Revaulting = 109,
    CraftersCraftingCrafters = 110,
    WhoNeedsRockets = 111,
    OverOverkill = 112,
    HeartTransplanter = 113,
    StayHydrated = 114,
    MobKabob = 115,
    Count = 116,
};

using POIBlockInteractionType = base::MinecraftEventing::POIBlockInteractionType;

}  // namespace MinecraftEventing_nested

struct MinecraftEventing {
    using InteractionType = MinecraftEventing_nested::InteractionType;
    using AchievementIds = MinecraftEventing_nested::AchievementIds;
    using POIBlockInteractionType = MinecraftEventing_nested::POIBlockInteractionType;
};

namespace LegacyTelemetryEventPacket_nested {

using Type = base::LegacyTelemetryEventPacket::Type;

struct Achievement {
    v898::MinecraftEventing::AchievementIds achievement_id{};
};

struct Interaction {
    ActorUniqueID interacted_entity_id{};
    v898::MinecraftEventing::InteractionType interaction_type{};
    std::int32_t interacted_entity_type{};
    std::int32_t interacted_entity_variant{};
    std::uint8_t interacted_entity_color{};
};

using PortalCreated = base::LegacyTelemetryEventPacket::PortalCreated;
using PortalUsed = base::LegacyTelemetryEventPacket::PortalUsed;

struct MobKilled {
    ActorUniqueID killer_entity_id{};
    ActorUniqueID killed_mob_id{};
    v827::ActorType damage_child_type{};
    std::int32_t damage_source{};
    std::int32_t trader_tier{};
    std::string trader_name{};
};

using CauldronUsed = base::LegacyTelemetryEventPacket::CauldronUsed;
using PlayerDied = base::LegacyTelemetryEventPacket::PlayerDied;
using BossKilled = base::LegacyTelemetryEventPacket::BossKilled;
using SlashCommand = base::LegacyTelemetryEventPacket::SlashCommand;
using MobBorn = base::LegacyTelemetryEventPacket::MobBorn;

struct POICauldronUsed {
    v898::MinecraftEventing::POIBlockInteractionType interaction_type{};
    std::int32_t item_id{};
};

struct ComposterUsed {
    v898::MinecraftEventing::POIBlockInteractionType interaction_type{};
    std::int32_t item_id{};
};

using BellUsed = base::LegacyTelemetryEventPacket::BellUsed;
using ActorDefinition = base::LegacyTelemetryEventPacket::ActorDefinition;
using RaidUpdate = base::LegacyTelemetryEventPacket::RaidUpdate;
using TargetBlockHit = base::LegacyTelemetryEventPacket::TargetBlockHit;
using PiglinBarter = base::LegacyTelemetryEventPacket::PiglinBarter;
using PlayerWaxedOrUnwaxedCopper = base::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper;
using CodeBuilderRuntimeAction = base::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction;
using CodeBuilderScoreboard = base::LegacyTelemetryEventPacket::CodeBuilderScoreboard;
using ItemUsed = base::LegacyTelemetryEventPacket::ItemUsed;
using Empty = base::LegacyTelemetryEventPacket::Empty;

}  // namespace LegacyTelemetryEventPacket_nested

struct LegacyTelemetryEventPacket {
    using Type = LegacyTelemetryEventPacket_nested::Type;
    using Achievement = LegacyTelemetryEventPacket_nested::Achievement;
    using Interaction = LegacyTelemetryEventPacket_nested::Interaction;
    using PortalCreated = LegacyTelemetryEventPacket_nested::PortalCreated;
    using PortalUsed = LegacyTelemetryEventPacket_nested::PortalUsed;
    using MobKilled = LegacyTelemetryEventPacket_nested::MobKilled;
    using CauldronUsed = LegacyTelemetryEventPacket_nested::CauldronUsed;
    using PlayerDied = LegacyTelemetryEventPacket_nested::PlayerDied;
    using BossKilled = LegacyTelemetryEventPacket_nested::BossKilled;
    using SlashCommand = LegacyTelemetryEventPacket_nested::SlashCommand;
    using MobBorn = LegacyTelemetryEventPacket_nested::MobBorn;
    using POICauldronUsed = LegacyTelemetryEventPacket_nested::POICauldronUsed;
    using ComposterUsed = LegacyTelemetryEventPacket_nested::ComposterUsed;
    using BellUsed = LegacyTelemetryEventPacket_nested::BellUsed;
    using ActorDefinition = LegacyTelemetryEventPacket_nested::ActorDefinition;
    using RaidUpdate = LegacyTelemetryEventPacket_nested::RaidUpdate;
    using TargetBlockHit = LegacyTelemetryEventPacket_nested::TargetBlockHit;
    using PiglinBarter = LegacyTelemetryEventPacket_nested::PiglinBarter;
    using PlayerWaxedOrUnwaxedCopper = LegacyTelemetryEventPacket_nested::PlayerWaxedOrUnwaxedCopper;
    using CodeBuilderRuntimeAction = LegacyTelemetryEventPacket_nested::CodeBuilderRuntimeAction;
    using CodeBuilderScoreboard = LegacyTelemetryEventPacket_nested::CodeBuilderScoreboard;
    using ItemUsed = LegacyTelemetryEventPacket_nested::ItemUsed;
    using Empty = LegacyTelemetryEventPacket_nested::Empty;

    static constexpr int Id = 65;
    ActorUniqueID player_unique_id{};
    v898::LegacyTelemetryEventPacket::Type type{};
    bool use_player_id{};
    std::variant<v898::LegacyTelemetryEventPacket::Achievement, v898::LegacyTelemetryEventPacket::Interaction, v898::LegacyTelemetryEventPacket::PortalCreated, v898::LegacyTelemetryEventPacket::PortalUsed, v898::LegacyTelemetryEventPacket::MobKilled, v898::LegacyTelemetryEventPacket::CauldronUsed, v898::LegacyTelemetryEventPacket::PlayerDied, v898::LegacyTelemetryEventPacket::BossKilled, v898::LegacyTelemetryEventPacket::SlashCommand, v898::LegacyTelemetryEventPacket::MobBorn, v898::LegacyTelemetryEventPacket::POICauldronUsed, v898::LegacyTelemetryEventPacket::ComposterUsed, v898::LegacyTelemetryEventPacket::BellUsed, v898::LegacyTelemetryEventPacket::ActorDefinition, v898::LegacyTelemetryEventPacket::RaidUpdate, v898::LegacyTelemetryEventPacket::TargetBlockHit, v898::LegacyTelemetryEventPacket::PiglinBarter, v898::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v898::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v898::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v898::LegacyTelemetryEventPacket::ItemUsed, v898::LegacyTelemetryEventPacket::Empty> event_data{};
};

}  // namespace v898

namespace v924 {

namespace MinecraftEventing_nested {

enum class InteractionType : std::uint8_t {
    Breeding = 1,
    Taming = 2,
    Curing = 3,
    Crafted = 4,
    Shearing = 5,
    Milking = 6,
    Trading = 7,
    Feeding = 8,
    Igniting = 9,
    Coloring = 10,
    Naming = 11,
    Leashing = 12,
    Unleashing = 13,
    PetSleep = 14,
    Trusting = 15,
    Commanding = 16,
};

enum class AchievementIds : std::uint8_t {
    ChestFullOfCobblestone = 7,
    DiamondForYou = 10,
    IronBelly = 20,
    IronMan = 21,
    OnARail = 29,
    Overkill = 30,
    ReturnToSender = 37,
    SniperDuel = 38,
    StayinFrosty = 39,
    TakeInventory = 40,
    MapRoom = 50,
    FreightStation = 52,
    SmeltEverything = 53,
    TasteOfYourOwnMedicine = 54,
    WhenPigsFly = 56,
    Inception = 58,
    ArtificialSelection = 60,
    FreeDiver = 61,
    SpawnTheWither = 62,
    Beaconator = 63,
    GreatView = 64,
    SuperSonic = 65,
    TheEndAgain = 66,
    TreasureHunter = 67,
    ShootingStar = 68,
    FashionShow = 69,
    SelfPublishedAuthor = 71,
    AlternativeFuel = 72,
    SleepWithTheFishes = 73,
    Castaway = 74,
    ImAMarineBiologist = 75,
    SailThe7Seas = 76,
    MeGold = 77,
    Ahoy = 78,
    Atlantis = 79,
    OnePickleTwoPickleSeaPickleFour = 80,
    DoaBarrelRoll = 81,
    Moskstraumen = 82,
    Echolocation = 83,
    WhereHaveYouBeen = 84,
    TopOfTheWorld = 85,
    FruitOnTheLoom = 86,
    SoundTheAlarm = 87,
    BuyLowSellHigh = 88,
    Disenchanted = 89,
    TimeForStew = 90,
    BeeOurGuest = 91,
    TotalBeeLocation = 92,
    StickySituation = 93,
    CoverMeInDebris = 94,
    FloatYourGoat = 95,
    Friend = 96,
    WaxOnWaxOff = 97,
    StriderRiddenInLavaInOverworld = 98,
    GoatHornAcquired = 99,
    JukeboxUsedInMeadows = 100,
    TradedAtWorldHeight = 101,
    SurvivedFallFromWorldHeight = 102,
    SneakCloseToSculkSensor = 103,
    ItSpreads = 104,
    BirthdaySong = 105,
    WithOurPowersCombined = 106,
    PlantingThePast = 107,
    CarefulRestoration = 108,
    Revaulting = 109,
    CraftersCraftingCrafters = 110,
    WhoNeedsRockets = 111,
    OverOverkill = 112,
    HeartTransplanter = 113,
    StayHydrated = 114,
    MobKabob = 115,
    AdventuringTime = 116,
    Count = 117,
};

using POIBlockInteractionType = base::MinecraftEventing::POIBlockInteractionType;

}  // namespace MinecraftEventing_nested

struct MinecraftEventing {
    using InteractionType = MinecraftEventing_nested::InteractionType;
    using AchievementIds = MinecraftEventing_nested::AchievementIds;
    using POIBlockInteractionType = MinecraftEventing_nested::POIBlockInteractionType;
};

namespace LegacyTelemetryEventPacket_nested {

using Type = base::LegacyTelemetryEventPacket::Type;

struct Achievement {
    v924::MinecraftEventing::AchievementIds achievement_id{};
};

struct Interaction {
    ActorUniqueID interacted_entity_id{};
    v924::MinecraftEventing::InteractionType interaction_type{};
    std::int32_t interacted_entity_type{};
    std::int32_t interacted_entity_variant{};
    std::uint8_t interacted_entity_color{};
};

using PortalCreated = base::LegacyTelemetryEventPacket::PortalCreated;
using PortalUsed = base::LegacyTelemetryEventPacket::PortalUsed;

struct MobKilled {
    ActorUniqueID killer_entity_id{};
    ActorUniqueID killed_mob_id{};
    v924::ActorType damage_child_type{};
    std::int32_t damage_source{};
    std::int32_t trader_tier{};
    std::string trader_name{};
};

using CauldronUsed = base::LegacyTelemetryEventPacket::CauldronUsed;
using PlayerDied = base::LegacyTelemetryEventPacket::PlayerDied;
using BossKilled = base::LegacyTelemetryEventPacket::BossKilled;
using SlashCommand = base::LegacyTelemetryEventPacket::SlashCommand;
using MobBorn = base::LegacyTelemetryEventPacket::MobBorn;

struct POICauldronUsed {
    v924::MinecraftEventing::POIBlockInteractionType interaction_type{};
    std::int32_t item_id{};
};

struct ComposterUsed {
    v924::MinecraftEventing::POIBlockInteractionType interaction_type{};
    std::int32_t item_id{};
};

using BellUsed = base::LegacyTelemetryEventPacket::BellUsed;
using ActorDefinition = base::LegacyTelemetryEventPacket::ActorDefinition;
using RaidUpdate = base::LegacyTelemetryEventPacket::RaidUpdate;
using TargetBlockHit = base::LegacyTelemetryEventPacket::TargetBlockHit;
using PiglinBarter = base::LegacyTelemetryEventPacket::PiglinBarter;
using PlayerWaxedOrUnwaxedCopper = base::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper;
using CodeBuilderRuntimeAction = base::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction;
using CodeBuilderScoreboard = base::LegacyTelemetryEventPacket::CodeBuilderScoreboard;
using ItemUsed = base::LegacyTelemetryEventPacket::ItemUsed;
using Empty = base::LegacyTelemetryEventPacket::Empty;

}  // namespace LegacyTelemetryEventPacket_nested

struct LegacyTelemetryEventPacket {
    using Type = LegacyTelemetryEventPacket_nested::Type;
    using Achievement = LegacyTelemetryEventPacket_nested::Achievement;
    using Interaction = LegacyTelemetryEventPacket_nested::Interaction;
    using PortalCreated = LegacyTelemetryEventPacket_nested::PortalCreated;
    using PortalUsed = LegacyTelemetryEventPacket_nested::PortalUsed;
    using MobKilled = LegacyTelemetryEventPacket_nested::MobKilled;
    using CauldronUsed = LegacyTelemetryEventPacket_nested::CauldronUsed;
    using PlayerDied = LegacyTelemetryEventPacket_nested::PlayerDied;
    using BossKilled = LegacyTelemetryEventPacket_nested::BossKilled;
    using SlashCommand = LegacyTelemetryEventPacket_nested::SlashCommand;
    using MobBorn = LegacyTelemetryEventPacket_nested::MobBorn;
    using POICauldronUsed = LegacyTelemetryEventPacket_nested::POICauldronUsed;
    using ComposterUsed = LegacyTelemetryEventPacket_nested::ComposterUsed;
    using BellUsed = LegacyTelemetryEventPacket_nested::BellUsed;
    using ActorDefinition = LegacyTelemetryEventPacket_nested::ActorDefinition;
    using RaidUpdate = LegacyTelemetryEventPacket_nested::RaidUpdate;
    using TargetBlockHit = LegacyTelemetryEventPacket_nested::TargetBlockHit;
    using PiglinBarter = LegacyTelemetryEventPacket_nested::PiglinBarter;
    using PlayerWaxedOrUnwaxedCopper = LegacyTelemetryEventPacket_nested::PlayerWaxedOrUnwaxedCopper;
    using CodeBuilderRuntimeAction = LegacyTelemetryEventPacket_nested::CodeBuilderRuntimeAction;
    using CodeBuilderScoreboard = LegacyTelemetryEventPacket_nested::CodeBuilderScoreboard;
    using ItemUsed = LegacyTelemetryEventPacket_nested::ItemUsed;
    using Empty = LegacyTelemetryEventPacket_nested::Empty;

    static constexpr int Id = 65;
    ActorUniqueID player_unique_id{};
    v924::LegacyTelemetryEventPacket::Type type{};
    bool use_player_id{};
    std::variant<v924::LegacyTelemetryEventPacket::Achievement, v924::LegacyTelemetryEventPacket::Interaction, v924::LegacyTelemetryEventPacket::PortalCreated, v924::LegacyTelemetryEventPacket::PortalUsed, v924::LegacyTelemetryEventPacket::MobKilled, v924::LegacyTelemetryEventPacket::CauldronUsed, v924::LegacyTelemetryEventPacket::PlayerDied, v924::LegacyTelemetryEventPacket::BossKilled, v924::LegacyTelemetryEventPacket::SlashCommand, v924::LegacyTelemetryEventPacket::MobBorn, v924::LegacyTelemetryEventPacket::POICauldronUsed, v924::LegacyTelemetryEventPacket::ComposterUsed, v924::LegacyTelemetryEventPacket::BellUsed, v924::LegacyTelemetryEventPacket::ActorDefinition, v924::LegacyTelemetryEventPacket::RaidUpdate, v924::LegacyTelemetryEventPacket::TargetBlockHit, v924::LegacyTelemetryEventPacket::PiglinBarter, v924::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v924::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v924::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v924::LegacyTelemetryEventPacket::ItemUsed, v924::LegacyTelemetryEventPacket::Empty> event_data{};
};

}  // namespace v924

namespace v975 {

using MinecraftEventing = v924::MinecraftEventing;

namespace LegacyTelemetryEventPacket_nested {

using Type = base::LegacyTelemetryEventPacket::Type;

struct Achievement {
    v924::MinecraftEventing::AchievementIds achievement_id{};
};

struct Interaction {
    ActorUniqueID interacted_entity_id{};
    v924::MinecraftEventing::InteractionType interaction_type{};
    std::int32_t interacted_entity_type{};
    std::int32_t interacted_entity_variant{};
    std::uint8_t interacted_entity_color{};
};

using PortalCreated = base::LegacyTelemetryEventPacket::PortalCreated;
using PortalUsed = base::LegacyTelemetryEventPacket::PortalUsed;

struct MobKilled {
    ActorUniqueID killer_entity_id{};
    ActorUniqueID killed_mob_id{};
    v975::ActorType damage_child_type{};
    std::int32_t damage_source{};
    std::int32_t trader_tier{};
    std::string trader_name{};
};

using CauldronUsed = base::LegacyTelemetryEventPacket::CauldronUsed;
using PlayerDied = base::LegacyTelemetryEventPacket::PlayerDied;
using BossKilled = base::LegacyTelemetryEventPacket::BossKilled;
using SlashCommand = base::LegacyTelemetryEventPacket::SlashCommand;
using MobBorn = base::LegacyTelemetryEventPacket::MobBorn;

struct POICauldronUsed {
    v924::MinecraftEventing::POIBlockInteractionType interaction_type{};
    std::int32_t item_id{};
};

struct ComposterUsed {
    v924::MinecraftEventing::POIBlockInteractionType interaction_type{};
    std::int32_t item_id{};
};

using BellUsed = base::LegacyTelemetryEventPacket::BellUsed;
using ActorDefinition = base::LegacyTelemetryEventPacket::ActorDefinition;
using RaidUpdate = base::LegacyTelemetryEventPacket::RaidUpdate;
using TargetBlockHit = base::LegacyTelemetryEventPacket::TargetBlockHit;
using PiglinBarter = base::LegacyTelemetryEventPacket::PiglinBarter;
using PlayerWaxedOrUnwaxedCopper = base::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper;
using CodeBuilderRuntimeAction = base::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction;
using CodeBuilderScoreboard = base::LegacyTelemetryEventPacket::CodeBuilderScoreboard;
using ItemUsed = base::LegacyTelemetryEventPacket::ItemUsed;
using Empty = base::LegacyTelemetryEventPacket::Empty;

}  // namespace LegacyTelemetryEventPacket_nested

struct LegacyTelemetryEventPacket {
    using Type = LegacyTelemetryEventPacket_nested::Type;
    using Achievement = LegacyTelemetryEventPacket_nested::Achievement;
    using Interaction = LegacyTelemetryEventPacket_nested::Interaction;
    using PortalCreated = LegacyTelemetryEventPacket_nested::PortalCreated;
    using PortalUsed = LegacyTelemetryEventPacket_nested::PortalUsed;
    using MobKilled = LegacyTelemetryEventPacket_nested::MobKilled;
    using CauldronUsed = LegacyTelemetryEventPacket_nested::CauldronUsed;
    using PlayerDied = LegacyTelemetryEventPacket_nested::PlayerDied;
    using BossKilled = LegacyTelemetryEventPacket_nested::BossKilled;
    using SlashCommand = LegacyTelemetryEventPacket_nested::SlashCommand;
    using MobBorn = LegacyTelemetryEventPacket_nested::MobBorn;
    using POICauldronUsed = LegacyTelemetryEventPacket_nested::POICauldronUsed;
    using ComposterUsed = LegacyTelemetryEventPacket_nested::ComposterUsed;
    using BellUsed = LegacyTelemetryEventPacket_nested::BellUsed;
    using ActorDefinition = LegacyTelemetryEventPacket_nested::ActorDefinition;
    using RaidUpdate = LegacyTelemetryEventPacket_nested::RaidUpdate;
    using TargetBlockHit = LegacyTelemetryEventPacket_nested::TargetBlockHit;
    using PiglinBarter = LegacyTelemetryEventPacket_nested::PiglinBarter;
    using PlayerWaxedOrUnwaxedCopper = LegacyTelemetryEventPacket_nested::PlayerWaxedOrUnwaxedCopper;
    using CodeBuilderRuntimeAction = LegacyTelemetryEventPacket_nested::CodeBuilderRuntimeAction;
    using CodeBuilderScoreboard = LegacyTelemetryEventPacket_nested::CodeBuilderScoreboard;
    using ItemUsed = LegacyTelemetryEventPacket_nested::ItemUsed;
    using Empty = LegacyTelemetryEventPacket_nested::Empty;

    static constexpr int Id = 65;
    ActorUniqueID player_unique_id{};
    v975::LegacyTelemetryEventPacket::Type type{};
    bool use_player_id{};
    std::variant<v975::LegacyTelemetryEventPacket::Achievement, v975::LegacyTelemetryEventPacket::Interaction, v975::LegacyTelemetryEventPacket::PortalCreated, v975::LegacyTelemetryEventPacket::PortalUsed, v975::LegacyTelemetryEventPacket::MobKilled, v975::LegacyTelemetryEventPacket::CauldronUsed, v975::LegacyTelemetryEventPacket::PlayerDied, v975::LegacyTelemetryEventPacket::BossKilled, v975::LegacyTelemetryEventPacket::SlashCommand, v975::LegacyTelemetryEventPacket::MobBorn, v975::LegacyTelemetryEventPacket::POICauldronUsed, v975::LegacyTelemetryEventPacket::ComposterUsed, v975::LegacyTelemetryEventPacket::BellUsed, v975::LegacyTelemetryEventPacket::ActorDefinition, v975::LegacyTelemetryEventPacket::RaidUpdate, v975::LegacyTelemetryEventPacket::TargetBlockHit, v975::LegacyTelemetryEventPacket::PiglinBarter, v975::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v975::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v975::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v975::LegacyTelemetryEventPacket::ItemUsed, v975::LegacyTelemetryEventPacket::Empty> event_data{};
};

}  // namespace v975

namespace v1001 {

namespace MinecraftEventing_nested {

enum class InteractionType : std::uint8_t {
    Breeding = 1,
    Taming = 2,
    Curing = 3,
    Crafted = 4,
    Shearing = 5,
    Milking = 6,
    Trading = 7,
    Feeding = 8,
    Igniting = 9,
    Coloring = 10,
    Naming = 11,
    Leashing = 12,
    Unleashing = 13,
    PetSleep = 14,
    Trusting = 15,
    Commanding = 16,
    Equipping = 17,
};

enum class AchievementIds : std::uint8_t {
    ChestFullOfCobblestone = 7,
    DiamondForYou = 10,
    IronBelly = 20,
    IronMan = 21,
    OnARail = 29,
    Overkill = 30,
    ReturnToSender = 37,
    SniperDuel = 38,
    StayinFrosty = 39,
    TakeInventory = 40,
    MapRoom = 50,
    FreightStation = 52,
    SmeltEverything = 53,
    TasteOfYourOwnMedicine = 54,
    WhenPigsFly = 56,
    Inception = 58,
    ArtificialSelection = 60,
    FreeDiver = 61,
    SpawnTheWither = 62,
    Beaconator = 63,
    GreatView = 64,
    SuperSonic = 65,
    TheEndAgain = 66,
    TreasureHunter = 67,
    ShootingStar = 68,
    FashionShow = 69,
    SelfPublishedAuthor = 71,
    AlternativeFuel = 72,
    SleepWithTheFishes = 73,
    Castaway = 74,
    ImAMarineBiologist = 75,
    SailThe7Seas = 76,
    MeGold = 77,
    Ahoy = 78,
    Atlantis = 79,
    OnePickleTwoPickleSeaPickleFour = 80,
    DoaBarrelRoll = 81,
    Moskstraumen = 82,
    Echolocation = 83,
    WhereHaveYouBeen = 84,
    TopOfTheWorld = 85,
    FruitOnTheLoom = 86,
    SoundTheAlarm = 87,
    BuyLowSellHigh = 88,
    Disenchanted = 89,
    TimeForStew = 90,
    BeeOurGuest = 91,
    TotalBeeLocation = 92,
    StickySituation = 93,
    CoverMeInDebris = 94,
    FloatYourGoat = 95,
    Friend = 96,
    WaxOnWaxOff = 97,
    StriderRiddenInLavaInOverworld = 98,
    GoatHornAcquired = 99,
    JukeboxUsedInMeadows = 100,
    TradedAtWorldHeight = 101,
    SurvivedFallFromWorldHeight = 102,
    SneakCloseToSculkSensor = 103,
    ItSpreads = 104,
    BirthdaySong = 105,
    WithOurPowersCombined = 106,
    PlantingThePast = 107,
    CarefulRestoration = 108,
    Revaulting = 109,
    CraftersCraftingCrafters = 110,
    WhoNeedsRockets = 111,
    OverOverkill = 112,
    HeartTransplanter = 113,
    StayHydrated = 114,
    MobKabob = 115,
    AdventuringTime = 116,
    UhOh = 117,
    Count = 118,
};

using POIBlockInteractionType = base::MinecraftEventing::POIBlockInteractionType;

}  // namespace MinecraftEventing_nested

struct MinecraftEventing {
    using InteractionType = MinecraftEventing_nested::InteractionType;
    using AchievementIds = MinecraftEventing_nested::AchievementIds;
    using POIBlockInteractionType = MinecraftEventing_nested::POIBlockInteractionType;
};

namespace LegacyTelemetryEventPacket_nested {

using Type = base::LegacyTelemetryEventPacket::Type;

struct Achievement {
    v1001::MinecraftEventing::AchievementIds achievement_id{};
};

struct Interaction {
    ActorUniqueID interacted_entity_id{};
    v1001::MinecraftEventing::InteractionType interaction_type{};
    std::int32_t interacted_entity_type{};
    std::int32_t interacted_entity_variant{};
    std::uint8_t interacted_entity_color{};
};

using PortalCreated = base::LegacyTelemetryEventPacket::PortalCreated;
using PortalUsed = base::LegacyTelemetryEventPacket::PortalUsed;

struct MobKilled {
    ActorUniqueID killer_entity_id{};
    ActorUniqueID killed_mob_id{};
    v975::ActorType damage_child_type{};
    std::int32_t damage_source{};
    std::int32_t trader_tier{};
    std::string trader_name{};
};

using CauldronUsed = base::LegacyTelemetryEventPacket::CauldronUsed;
using PlayerDied = base::LegacyTelemetryEventPacket::PlayerDied;
using BossKilled = base::LegacyTelemetryEventPacket::BossKilled;
using SlashCommand = base::LegacyTelemetryEventPacket::SlashCommand;
using MobBorn = base::LegacyTelemetryEventPacket::MobBorn;

struct POICauldronUsed {
    v1001::MinecraftEventing::POIBlockInteractionType interaction_type{};
    std::int32_t item_id{};
};

struct ComposterUsed {
    v1001::MinecraftEventing::POIBlockInteractionType interaction_type{};
    std::int32_t item_id{};
};

using BellUsed = base::LegacyTelemetryEventPacket::BellUsed;
using ActorDefinition = base::LegacyTelemetryEventPacket::ActorDefinition;
using RaidUpdate = base::LegacyTelemetryEventPacket::RaidUpdate;
using TargetBlockHit = base::LegacyTelemetryEventPacket::TargetBlockHit;
using PiglinBarter = base::LegacyTelemetryEventPacket::PiglinBarter;
using PlayerWaxedOrUnwaxedCopper = base::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper;
using CodeBuilderRuntimeAction = base::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction;
using CodeBuilderScoreboard = base::LegacyTelemetryEventPacket::CodeBuilderScoreboard;
using ItemUsed = base::LegacyTelemetryEventPacket::ItemUsed;
using Empty = base::LegacyTelemetryEventPacket::Empty;

}  // namespace LegacyTelemetryEventPacket_nested

struct LegacyTelemetryEventPacket {
    using Type = LegacyTelemetryEventPacket_nested::Type;
    using Achievement = LegacyTelemetryEventPacket_nested::Achievement;
    using Interaction = LegacyTelemetryEventPacket_nested::Interaction;
    using PortalCreated = LegacyTelemetryEventPacket_nested::PortalCreated;
    using PortalUsed = LegacyTelemetryEventPacket_nested::PortalUsed;
    using MobKilled = LegacyTelemetryEventPacket_nested::MobKilled;
    using CauldronUsed = LegacyTelemetryEventPacket_nested::CauldronUsed;
    using PlayerDied = LegacyTelemetryEventPacket_nested::PlayerDied;
    using BossKilled = LegacyTelemetryEventPacket_nested::BossKilled;
    using SlashCommand = LegacyTelemetryEventPacket_nested::SlashCommand;
    using MobBorn = LegacyTelemetryEventPacket_nested::MobBorn;
    using POICauldronUsed = LegacyTelemetryEventPacket_nested::POICauldronUsed;
    using ComposterUsed = LegacyTelemetryEventPacket_nested::ComposterUsed;
    using BellUsed = LegacyTelemetryEventPacket_nested::BellUsed;
    using ActorDefinition = LegacyTelemetryEventPacket_nested::ActorDefinition;
    using RaidUpdate = LegacyTelemetryEventPacket_nested::RaidUpdate;
    using TargetBlockHit = LegacyTelemetryEventPacket_nested::TargetBlockHit;
    using PiglinBarter = LegacyTelemetryEventPacket_nested::PiglinBarter;
    using PlayerWaxedOrUnwaxedCopper = LegacyTelemetryEventPacket_nested::PlayerWaxedOrUnwaxedCopper;
    using CodeBuilderRuntimeAction = LegacyTelemetryEventPacket_nested::CodeBuilderRuntimeAction;
    using CodeBuilderScoreboard = LegacyTelemetryEventPacket_nested::CodeBuilderScoreboard;
    using ItemUsed = LegacyTelemetryEventPacket_nested::ItemUsed;
    using Empty = LegacyTelemetryEventPacket_nested::Empty;

    static constexpr int Id = 65;
    ActorUniqueID player_unique_id{};
    v1001::LegacyTelemetryEventPacket::Type type{};
    bool use_player_id{};
    std::variant<v1001::LegacyTelemetryEventPacket::Achievement, v1001::LegacyTelemetryEventPacket::Interaction, v1001::LegacyTelemetryEventPacket::PortalCreated, v1001::LegacyTelemetryEventPacket::PortalUsed, v1001::LegacyTelemetryEventPacket::MobKilled, v1001::LegacyTelemetryEventPacket::CauldronUsed, v1001::LegacyTelemetryEventPacket::PlayerDied, v1001::LegacyTelemetryEventPacket::BossKilled, v1001::LegacyTelemetryEventPacket::SlashCommand, v1001::LegacyTelemetryEventPacket::MobBorn, v1001::LegacyTelemetryEventPacket::POICauldronUsed, v1001::LegacyTelemetryEventPacket::ComposterUsed, v1001::LegacyTelemetryEventPacket::BellUsed, v1001::LegacyTelemetryEventPacket::ActorDefinition, v1001::LegacyTelemetryEventPacket::RaidUpdate, v1001::LegacyTelemetryEventPacket::TargetBlockHit, v1001::LegacyTelemetryEventPacket::PiglinBarter, v1001::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v1001::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v1001::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v1001::LegacyTelemetryEventPacket::ItemUsed, v1001::LegacyTelemetryEventPacket::Empty> event_data{};
};

}  // namespace v1001

namespace v2168 {

namespace MinecraftEventing_nested {

enum class InteractionType : std::uint8_t {
    Breeding = 1,
    Taming = 2,
    Curing = 3,
    Crafted = 4,
    Shearing = 5,
    Milking = 6,
    Trading = 7,
    Feeding = 8,
    Igniting = 9,
    Coloring = 10,
    Naming = 11,
    Leashing = 12,
    Unleashing = 13,
    PetSleep = 14,
    Trusting = 15,
    Commanding = 16,
    Equipping = 17,
};

enum class AchievementIds : std::uint8_t {
    ChestFullOfCobblestone = 7,
    DiamondForYou = 10,
    IronBelly = 20,
    IronMan = 21,
    OnARail = 29,
    Overkill = 30,
    ReturnToSender = 37,
    SniperDuel = 38,
    StayinFrosty = 39,
    TakeInventory = 40,
    MapRoom = 50,
    FreightStation = 52,
    SmeltEverything = 53,
    TasteOfYourOwnMedicine = 54,
    WhenPigsFly = 56,
    Inception = 58,
    ArtificialSelection = 60,
    FreeDiver = 61,
    SpawnTheWither = 62,
    Beaconator = 63,
    GreatView = 64,
    SuperSonic = 65,
    TheEndAgain = 66,
    TreasureHunter = 67,
    ShootingStar = 68,
    FashionShow = 69,
    SelfPublishedAuthor = 71,
    AlternativeFuel = 72,
    SleepWithTheFishes = 73,
    Castaway = 74,
    ImAMarineBiologist = 75,
    SailThe7Seas = 76,
    MeGold = 77,
    Ahoy = 78,
    Atlantis = 79,
    OnePickleTwoPickleSeaPickleFour = 80,
    DoaBarrelRoll = 81,
    Moskstraumen = 82,
    Echolocation = 83,
    WhereHaveYouBeen = 84,
    TopOfTheWorld = 85,
    FruitOnTheLoom = 86,
    SoundTheAlarm = 87,
    BuyLowSellHigh = 88,
    Disenchanted = 89,
    TimeForStew = 90,
    BeeOurGuest = 91,
    TotalBeeLocation = 92,
    StickySituation = 93,
    CoverMeInDebris = 94,
    FloatYourGoat = 95,
    Friend = 96,
    WaxOnWaxOff = 97,
    StriderRiddenInLavaInOverworld = 98,
    GoatHornAcquired = 99,
    JukeboxUsedInMeadows = 100,
    TradedAtWorldHeight = 101,
    SurvivedFallFromWorldHeight = 102,
    SneakCloseToSculkSensor = 103,
    ItSpreads = 104,
    BirthdaySong = 105,
    WithOurPowersCombined = 106,
    PlantingThePast = 107,
    CarefulRestoration = 108,
    Revaulting = 109,
    CraftersCraftingCrafters = 110,
    WhoNeedsRockets = 111,
    OverOverkill = 112,
    HeartTransplanter = 113,
    StayHydrated = 114,
    MobKabob = 115,
    AdventuringTime = 116,
    UhOh = 117,
    GettingWood = 118,
    BenchMaking = 119,
    TimeToMine = 120,
    HotTopic = 121,
    AcquireHardware = 122,
    GettingAnUpgrade = 123,
    MonsterHunter = 124,
    Diamonds = 125,
    PlethoraOfCats = 126,
    Count = 127,
};

using POIBlockInteractionType = base::MinecraftEventing::POIBlockInteractionType;

}  // namespace MinecraftEventing_nested

struct MinecraftEventing {
    using InteractionType = MinecraftEventing_nested::InteractionType;
    using AchievementIds = MinecraftEventing_nested::AchievementIds;
    using POIBlockInteractionType = MinecraftEventing_nested::POIBlockInteractionType;
};

namespace LegacyTelemetryEventPacket_nested {

using Type = base::LegacyTelemetryEventPacket::Type;

struct Achievement {
    v2168::MinecraftEventing::AchievementIds achievement_id{};
};

struct Interaction {
    ActorUniqueID interacted_entity_id{};
    v2168::MinecraftEventing::InteractionType interaction_type{};
    std::int32_t interacted_entity_type{};
    std::int32_t interacted_entity_variant{};
    std::uint8_t interacted_entity_color{};
};

using PortalCreated = base::LegacyTelemetryEventPacket::PortalCreated;
using PortalUsed = base::LegacyTelemetryEventPacket::PortalUsed;

struct MobKilled {
    ActorUniqueID killer_entity_id{};
    ActorUniqueID killed_mob_id{};
    v2168::ActorType damage_child_type{};
    std::int32_t damage_source{};
    std::int32_t trader_tier{};
    std::string trader_name{};
};

using CauldronUsed = base::LegacyTelemetryEventPacket::CauldronUsed;
using PlayerDied = base::LegacyTelemetryEventPacket::PlayerDied;
using BossKilled = base::LegacyTelemetryEventPacket::BossKilled;
using SlashCommand = base::LegacyTelemetryEventPacket::SlashCommand;
using MobBorn = base::LegacyTelemetryEventPacket::MobBorn;

struct POICauldronUsed {
    v2168::MinecraftEventing::POIBlockInteractionType interaction_type{};
    std::int32_t item_id{};
};

struct ComposterUsed {
    v2168::MinecraftEventing::POIBlockInteractionType interaction_type{};
    std::int32_t item_id{};
};

using BellUsed = base::LegacyTelemetryEventPacket::BellUsed;
using ActorDefinition = base::LegacyTelemetryEventPacket::ActorDefinition;
using RaidUpdate = base::LegacyTelemetryEventPacket::RaidUpdate;
using TargetBlockHit = base::LegacyTelemetryEventPacket::TargetBlockHit;
using PiglinBarter = base::LegacyTelemetryEventPacket::PiglinBarter;
using PlayerWaxedOrUnwaxedCopper = base::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper;
using CodeBuilderRuntimeAction = base::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction;
using CodeBuilderScoreboard = base::LegacyTelemetryEventPacket::CodeBuilderScoreboard;
using ItemUsed = base::LegacyTelemetryEventPacket::ItemUsed;
using Empty = base::LegacyTelemetryEventPacket::Empty;

}  // namespace LegacyTelemetryEventPacket_nested

struct LegacyTelemetryEventPacket {
    using Type = LegacyTelemetryEventPacket_nested::Type;
    using Achievement = LegacyTelemetryEventPacket_nested::Achievement;
    using Interaction = LegacyTelemetryEventPacket_nested::Interaction;
    using PortalCreated = LegacyTelemetryEventPacket_nested::PortalCreated;
    using PortalUsed = LegacyTelemetryEventPacket_nested::PortalUsed;
    using MobKilled = LegacyTelemetryEventPacket_nested::MobKilled;
    using CauldronUsed = LegacyTelemetryEventPacket_nested::CauldronUsed;
    using PlayerDied = LegacyTelemetryEventPacket_nested::PlayerDied;
    using BossKilled = LegacyTelemetryEventPacket_nested::BossKilled;
    using SlashCommand = LegacyTelemetryEventPacket_nested::SlashCommand;
    using MobBorn = LegacyTelemetryEventPacket_nested::MobBorn;
    using POICauldronUsed = LegacyTelemetryEventPacket_nested::POICauldronUsed;
    using ComposterUsed = LegacyTelemetryEventPacket_nested::ComposterUsed;
    using BellUsed = LegacyTelemetryEventPacket_nested::BellUsed;
    using ActorDefinition = LegacyTelemetryEventPacket_nested::ActorDefinition;
    using RaidUpdate = LegacyTelemetryEventPacket_nested::RaidUpdate;
    using TargetBlockHit = LegacyTelemetryEventPacket_nested::TargetBlockHit;
    using PiglinBarter = LegacyTelemetryEventPacket_nested::PiglinBarter;
    using PlayerWaxedOrUnwaxedCopper = LegacyTelemetryEventPacket_nested::PlayerWaxedOrUnwaxedCopper;
    using CodeBuilderRuntimeAction = LegacyTelemetryEventPacket_nested::CodeBuilderRuntimeAction;
    using CodeBuilderScoreboard = LegacyTelemetryEventPacket_nested::CodeBuilderScoreboard;
    using ItemUsed = LegacyTelemetryEventPacket_nested::ItemUsed;
    using Empty = LegacyTelemetryEventPacket_nested::Empty;

    static constexpr int Id = 65;
    ActorUniqueID player_unique_id{};
    v2168::LegacyTelemetryEventPacket::Type type{};
    bool use_player_id{};
    std::variant<v2168::LegacyTelemetryEventPacket::Achievement, v2168::LegacyTelemetryEventPacket::Interaction, v2168::LegacyTelemetryEventPacket::PortalCreated, v2168::LegacyTelemetryEventPacket::PortalUsed, v2168::LegacyTelemetryEventPacket::MobKilled, v2168::LegacyTelemetryEventPacket::CauldronUsed, v2168::LegacyTelemetryEventPacket::PlayerDied, v2168::LegacyTelemetryEventPacket::BossKilled, v2168::LegacyTelemetryEventPacket::SlashCommand, v2168::LegacyTelemetryEventPacket::MobBorn, v2168::LegacyTelemetryEventPacket::POICauldronUsed, v2168::LegacyTelemetryEventPacket::ComposterUsed, v2168::LegacyTelemetryEventPacket::BellUsed, v2168::LegacyTelemetryEventPacket::ActorDefinition, v2168::LegacyTelemetryEventPacket::RaidUpdate, v2168::LegacyTelemetryEventPacket::TargetBlockHit, v2168::LegacyTelemetryEventPacket::PiglinBarter, v2168::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v2168::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v2168::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v2168::LegacyTelemetryEventPacket::ItemUsed, v2168::LegacyTelemetryEventPacket::Empty> event_data{};
};

}  // namespace v2168

namespace v2225 {

namespace MinecraftEventing_nested {

enum class InteractionType : std::uint8_t {
    Breeding = 1,
    Taming = 2,
    Curing = 3,
    Crafted = 4,
    Shearing = 5,
    Milking = 6,
    Trading = 7,
    Feeding = 8,
    Igniting = 9,
    Coloring = 10,
    Naming = 11,
    Leashing = 12,
    Unleashing = 13,
    PetSleep = 14,
    Trusting = 15,
    Commanding = 16,
    Equipping = 17,
};

enum class AchievementIds : std::uint8_t {
    ChestFullOfCobblestone = 7,
    DiamondForYou = 10,
    IronBelly = 20,
    IronMan = 21,
    OnARail = 29,
    Overkill = 30,
    ReturnToSender = 37,
    SniperDuel = 38,
    StayinFrosty = 39,
    TakeInventory = 40,
    MapRoom = 50,
    FreightStation = 52,
    SmeltEverything = 53,
    TasteOfYourOwnMedicine = 54,
    WhenPigsFly = 56,
    Inception = 58,
    ArtificialSelection = 60,
    FreeDiver = 61,
    SpawnTheWither = 62,
    Beaconator = 63,
    GreatView = 64,
    SuperSonic = 65,
    TheEndAgain = 66,
    TreasureHunter = 67,
    ShootingStar = 68,
    FashionShow = 69,
    SelfPublishedAuthor = 71,
    AlternativeFuel = 72,
    SleepWithTheFishes = 73,
    Castaway = 74,
    ImAMarineBiologist = 75,
    SailThe7Seas = 76,
    MeGold = 77,
    Ahoy = 78,
    Atlantis = 79,
    OnePickleTwoPickleSeaPickleFour = 80,
    DoaBarrelRoll = 81,
    Moskstraumen = 82,
    Echolocation = 83,
    WhereHaveYouBeen = 84,
    TopOfTheWorld = 85,
    FruitOnTheLoom = 86,
    SoundTheAlarm = 87,
    BuyLowSellHigh = 88,
    Disenchanted = 89,
    TimeForStew = 90,
    BeeOurGuest = 91,
    TotalBeeLocation = 92,
    StickySituation = 93,
    CoverMeInDebris = 94,
    FloatYourGoat = 95,
    Friend = 96,
    WaxOnWaxOff = 97,
    StriderRiddenInLavaInOverworld = 98,
    GoatHornAcquired = 99,
    JukeboxUsedInMeadows = 100,
    TradedAtWorldHeight = 101,
    SurvivedFallFromWorldHeight = 102,
    SneakCloseToSculkSensor = 103,
    ItSpreads = 104,
    BirthdaySong = 105,
    WithOurPowersCombined = 106,
    PlantingThePast = 107,
    CarefulRestoration = 108,
    Revaulting = 109,
    CraftersCraftingCrafters = 110,
    WhoNeedsRockets = 111,
    OverOverkill = 112,
    HeartTransplanter = 113,
    StayHydrated = 114,
    MobKabob = 115,
    AdventuringTime = 116,
    UhOh = 117,
    GettingWood = 118,
    BenchMaking = 119,
    TimeToMine = 120,
    HotTopic = 121,
    AcquireHardware = 122,
    GettingAnUpgrade = 123,
    MonsterHunter = 124,
    Diamonds = 125,
    PlethoraOfCats = 126,
    WhatGoesAroundComesAround = 127,
    Count = 128,
};

using POIBlockInteractionType = base::MinecraftEventing::POIBlockInteractionType;

}  // namespace MinecraftEventing_nested

struct MinecraftEventing {
    using InteractionType = MinecraftEventing_nested::InteractionType;
    using AchievementIds = MinecraftEventing_nested::AchievementIds;
    using POIBlockInteractionType = MinecraftEventing_nested::POIBlockInteractionType;
};

namespace LegacyTelemetryEventPacket_nested {

using Type = base::LegacyTelemetryEventPacket::Type;

struct Achievement {
    v2225::MinecraftEventing::AchievementIds achievement_id{};
};

struct Interaction {
    ActorUniqueID interacted_entity_id{};
    v2225::MinecraftEventing::InteractionType interaction_type{};
    std::int32_t interacted_entity_type{};
    std::int32_t interacted_entity_variant{};
    std::uint8_t interacted_entity_color{};
};

using PortalCreated = base::LegacyTelemetryEventPacket::PortalCreated;
using PortalUsed = base::LegacyTelemetryEventPacket::PortalUsed;

struct MobKilled {
    ActorUniqueID killer_entity_id{};
    ActorUniqueID killed_mob_id{};
    v2225::ActorType damage_child_type{};
    std::int32_t damage_source{};
    std::int32_t trader_tier{};
    std::string trader_name{};
};

using CauldronUsed = base::LegacyTelemetryEventPacket::CauldronUsed;
using PlayerDied = base::LegacyTelemetryEventPacket::PlayerDied;
using BossKilled = base::LegacyTelemetryEventPacket::BossKilled;
using SlashCommand = base::LegacyTelemetryEventPacket::SlashCommand;
using MobBorn = base::LegacyTelemetryEventPacket::MobBorn;

struct POICauldronUsed {
    v2225::MinecraftEventing::POIBlockInteractionType interaction_type{};
    std::int32_t item_id{};
};

struct ComposterUsed {
    v2225::MinecraftEventing::POIBlockInteractionType interaction_type{};
    std::int32_t item_id{};
};

using BellUsed = base::LegacyTelemetryEventPacket::BellUsed;
using ActorDefinition = base::LegacyTelemetryEventPacket::ActorDefinition;
using RaidUpdate = base::LegacyTelemetryEventPacket::RaidUpdate;
using TargetBlockHit = base::LegacyTelemetryEventPacket::TargetBlockHit;
using PiglinBarter = base::LegacyTelemetryEventPacket::PiglinBarter;
using PlayerWaxedOrUnwaxedCopper = base::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper;
using CodeBuilderRuntimeAction = base::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction;
using CodeBuilderScoreboard = base::LegacyTelemetryEventPacket::CodeBuilderScoreboard;
using ItemUsed = base::LegacyTelemetryEventPacket::ItemUsed;
using Empty = base::LegacyTelemetryEventPacket::Empty;

}  // namespace LegacyTelemetryEventPacket_nested

struct LegacyTelemetryEventPacket {
    using Type = LegacyTelemetryEventPacket_nested::Type;
    using Achievement = LegacyTelemetryEventPacket_nested::Achievement;
    using Interaction = LegacyTelemetryEventPacket_nested::Interaction;
    using PortalCreated = LegacyTelemetryEventPacket_nested::PortalCreated;
    using PortalUsed = LegacyTelemetryEventPacket_nested::PortalUsed;
    using MobKilled = LegacyTelemetryEventPacket_nested::MobKilled;
    using CauldronUsed = LegacyTelemetryEventPacket_nested::CauldronUsed;
    using PlayerDied = LegacyTelemetryEventPacket_nested::PlayerDied;
    using BossKilled = LegacyTelemetryEventPacket_nested::BossKilled;
    using SlashCommand = LegacyTelemetryEventPacket_nested::SlashCommand;
    using MobBorn = LegacyTelemetryEventPacket_nested::MobBorn;
    using POICauldronUsed = LegacyTelemetryEventPacket_nested::POICauldronUsed;
    using ComposterUsed = LegacyTelemetryEventPacket_nested::ComposterUsed;
    using BellUsed = LegacyTelemetryEventPacket_nested::BellUsed;
    using ActorDefinition = LegacyTelemetryEventPacket_nested::ActorDefinition;
    using RaidUpdate = LegacyTelemetryEventPacket_nested::RaidUpdate;
    using TargetBlockHit = LegacyTelemetryEventPacket_nested::TargetBlockHit;
    using PiglinBarter = LegacyTelemetryEventPacket_nested::PiglinBarter;
    using PlayerWaxedOrUnwaxedCopper = LegacyTelemetryEventPacket_nested::PlayerWaxedOrUnwaxedCopper;
    using CodeBuilderRuntimeAction = LegacyTelemetryEventPacket_nested::CodeBuilderRuntimeAction;
    using CodeBuilderScoreboard = LegacyTelemetryEventPacket_nested::CodeBuilderScoreboard;
    using ItemUsed = LegacyTelemetryEventPacket_nested::ItemUsed;
    using Empty = LegacyTelemetryEventPacket_nested::Empty;

    static constexpr int Id = 65;
    ActorUniqueID player_unique_id{};
    v2225::LegacyTelemetryEventPacket::Type type{};
    bool use_player_id{};
    std::variant<v2225::LegacyTelemetryEventPacket::Achievement, v2225::LegacyTelemetryEventPacket::Interaction, v2225::LegacyTelemetryEventPacket::PortalCreated, v2225::LegacyTelemetryEventPacket::PortalUsed, v2225::LegacyTelemetryEventPacket::MobKilled, v2225::LegacyTelemetryEventPacket::CauldronUsed, v2225::LegacyTelemetryEventPacket::PlayerDied, v2225::LegacyTelemetryEventPacket::BossKilled, v2225::LegacyTelemetryEventPacket::SlashCommand, v2225::LegacyTelemetryEventPacket::MobBorn, v2225::LegacyTelemetryEventPacket::POICauldronUsed, v2225::LegacyTelemetryEventPacket::ComposterUsed, v2225::LegacyTelemetryEventPacket::BellUsed, v2225::LegacyTelemetryEventPacket::ActorDefinition, v2225::LegacyTelemetryEventPacket::RaidUpdate, v2225::LegacyTelemetryEventPacket::TargetBlockHit, v2225::LegacyTelemetryEventPacket::PiglinBarter, v2225::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, v2225::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, v2225::LegacyTelemetryEventPacket::CodeBuilderScoreboard, v2225::LegacyTelemetryEventPacket::ItemUsed, v2225::LegacyTelemetryEventPacket::Empty> event_data{};
};

}  // namespace v2225

namespace detail {

template <int V>
struct MinecraftEventing_;

template <int V> requires (V < 766)
struct MinecraftEventing_<V> { using type = base::MinecraftEventing; };

template <int V> requires (V >= 766 && V < 776)
struct MinecraftEventing_<V> { using type = v766::MinecraftEventing; };

template <int V> requires (V >= 776 && V < 818)
struct MinecraftEventing_<V> { using type = v776::MinecraftEventing; };

template <int V> requires (V >= 818 && V < 898)
struct MinecraftEventing_<V> { using type = v818::MinecraftEventing; };

template <int V> requires (V >= 898 && V < 924)
struct MinecraftEventing_<V> { using type = v898::MinecraftEventing; };

template <int V> requires (V >= 924 && V < 1001)
struct MinecraftEventing_<V> { using type = v924::MinecraftEventing; };

template <int V> requires (V >= 1001 && V < 2168)
struct MinecraftEventing_<V> { using type = v1001::MinecraftEventing; };

template <int V> requires (V >= 2168 && V < 2225)
struct MinecraftEventing_<V> { using type = v2168::MinecraftEventing; };

template <int V> requires (V >= 2225)
struct MinecraftEventing_<V> { using type = v2225::MinecraftEventing; };

template <int V>
struct LegacyTelemetryEventPacket_;

template <int V> requires (V < 766)
struct LegacyTelemetryEventPacket_<V> { using type = base::LegacyTelemetryEventPacket; };

template <int V> requires (V >= 766 && V < 776)
struct LegacyTelemetryEventPacket_<V> { using type = v766::LegacyTelemetryEventPacket; };

template <int V> requires (V >= 776 && V < 800)
struct LegacyTelemetryEventPacket_<V> { using type = v776::LegacyTelemetryEventPacket; };

template <int V> requires (V >= 800 && V < 818)
struct LegacyTelemetryEventPacket_<V> { using type = v800::LegacyTelemetryEventPacket; };

template <int V> requires (V >= 818 && V < 827)
struct LegacyTelemetryEventPacket_<V> { using type = v818::LegacyTelemetryEventPacket; };

template <int V> requires (V >= 827 && V < 898)
struct LegacyTelemetryEventPacket_<V> { using type = v827::LegacyTelemetryEventPacket; };

template <int V> requires (V >= 898 && V < 924)
struct LegacyTelemetryEventPacket_<V> { using type = v898::LegacyTelemetryEventPacket; };

template <int V> requires (V >= 924 && V < 975)
struct LegacyTelemetryEventPacket_<V> { using type = v924::LegacyTelemetryEventPacket; };

template <int V> requires (V >= 975 && V < 1001)
struct LegacyTelemetryEventPacket_<V> { using type = v975::LegacyTelemetryEventPacket; };

template <int V> requires (V >= 1001 && V < 2168)
struct LegacyTelemetryEventPacket_<V> { using type = v1001::LegacyTelemetryEventPacket; };

template <int V> requires (V >= 2168 && V < 2225)
struct LegacyTelemetryEventPacket_<V> { using type = v2168::LegacyTelemetryEventPacket; };

template <int V> requires (V >= 2225)
struct LegacyTelemetryEventPacket_<V> { using type = v2225::LegacyTelemetryEventPacket; };

}  // namespace detail

template <int V> using MinecraftEventing_ = typename detail::MinecraftEventing_<V>::type;
template <int V> using LegacyTelemetryEventPacket_ = typename detail::LegacyTelemetryEventPacket_<V>::type;

template <int V>
struct packet_of<V, 65> { using type = LegacyTelemetryEventPacket_<V>; };

namespace detail {

template <>
inline constexpr std::array<base::MinecraftEventing::InteractionType, 16> values_v<base::MinecraftEventing::InteractionType>{{
    base::MinecraftEventing::InteractionType::Breeding,
    base::MinecraftEventing::InteractionType::Taming,
    base::MinecraftEventing::InteractionType::Curing,
    base::MinecraftEventing::InteractionType::Crafted,
    base::MinecraftEventing::InteractionType::Shearing,
    base::MinecraftEventing::InteractionType::Milking,
    base::MinecraftEventing::InteractionType::Trading,
    base::MinecraftEventing::InteractionType::Feeding,
    base::MinecraftEventing::InteractionType::Igniting,
    base::MinecraftEventing::InteractionType::Coloring,
    base::MinecraftEventing::InteractionType::Naming,
    base::MinecraftEventing::InteractionType::Leashing,
    base::MinecraftEventing::InteractionType::Unleashing,
    base::MinecraftEventing::InteractionType::PetSleep,
    base::MinecraftEventing::InteractionType::Trusting,
    base::MinecraftEventing::InteractionType::Commanding,
}};

template <>
inline constexpr std::array<std::string_view, 16> names_v<base::MinecraftEventing::InteractionType>{{
    "breeding",
    "taming",
    "curing",
    "crafted",
    "shearing",
    "milking",
    "trading",
    "feeding",
    "igniting",
    "coloring",
    "naming",
    "leashing",
    "unleashing",
    "petsleep",
    "trusting",
    "commanding",
}};

template <>
inline constexpr std::string_view type_name_v<base::MinecraftEventing::InteractionType>{"MinecraftEventing::InteractionType"};

template <>
inline constexpr std::array<base::MinecraftEventing::AchievementIds, 70> values_v<base::MinecraftEventing::AchievementIds>{{
    base::MinecraftEventing::AchievementIds::ChestFullOfCobblestone,
    base::MinecraftEventing::AchievementIds::DiamondForYou,
    base::MinecraftEventing::AchievementIds::IronBelly,
    base::MinecraftEventing::AchievementIds::IronMan,
    base::MinecraftEventing::AchievementIds::OnARail,
    base::MinecraftEventing::AchievementIds::Overkill,
    base::MinecraftEventing::AchievementIds::ReturnToSender,
    base::MinecraftEventing::AchievementIds::SniperDuel,
    base::MinecraftEventing::AchievementIds::StayinFrosty,
    base::MinecraftEventing::AchievementIds::TakeInventory,
    base::MinecraftEventing::AchievementIds::MapRoom,
    base::MinecraftEventing::AchievementIds::FreightStation,
    base::MinecraftEventing::AchievementIds::SmeltEverything,
    base::MinecraftEventing::AchievementIds::TasteOfYourOwnMedicine,
    base::MinecraftEventing::AchievementIds::WhenPigsFly,
    base::MinecraftEventing::AchievementIds::Inception,
    base::MinecraftEventing::AchievementIds::ArtificialSelection,
    base::MinecraftEventing::AchievementIds::FreeDiver,
    base::MinecraftEventing::AchievementIds::SpawnTheWither,
    base::MinecraftEventing::AchievementIds::Beaconator,
    base::MinecraftEventing::AchievementIds::GreatView,
    base::MinecraftEventing::AchievementIds::SuperSonic,
    base::MinecraftEventing::AchievementIds::TheEndAgain,
    base::MinecraftEventing::AchievementIds::TreasureHunter,
    base::MinecraftEventing::AchievementIds::ShootingStar,
    base::MinecraftEventing::AchievementIds::FashionShow,
    base::MinecraftEventing::AchievementIds::Brilliance,
    base::MinecraftEventing::AchievementIds::SelfPublishedAuthor,
    base::MinecraftEventing::AchievementIds::AlternativeFuel,
    base::MinecraftEventing::AchievementIds::SleepWithTheFishes,
    base::MinecraftEventing::AchievementIds::Castaway,
    base::MinecraftEventing::AchievementIds::ImAMarineBiologist,
    base::MinecraftEventing::AchievementIds::SailThe7Seas,
    base::MinecraftEventing::AchievementIds::MeGold,
    base::MinecraftEventing::AchievementIds::Ahoy,
    base::MinecraftEventing::AchievementIds::Atlantis,
    base::MinecraftEventing::AchievementIds::OnePickleTwoPickleSeaPickleFour,
    base::MinecraftEventing::AchievementIds::DoaBarrelRoll,
    base::MinecraftEventing::AchievementIds::Moskstraumen,
    base::MinecraftEventing::AchievementIds::Echolocation,
    base::MinecraftEventing::AchievementIds::WhereHaveYouBeen,
    base::MinecraftEventing::AchievementIds::TopOfTheWorld,
    base::MinecraftEventing::AchievementIds::FruitOnTheLoom,
    base::MinecraftEventing::AchievementIds::SoundTheAlarm,
    base::MinecraftEventing::AchievementIds::BuyLowSellHigh,
    base::MinecraftEventing::AchievementIds::Disenchanted,
    base::MinecraftEventing::AchievementIds::TimeForStew,
    base::MinecraftEventing::AchievementIds::BeeOurGuest,
    base::MinecraftEventing::AchievementIds::TotalBeeLocation,
    base::MinecraftEventing::AchievementIds::StickySituation,
    base::MinecraftEventing::AchievementIds::CoverMeInDebris,
    base::MinecraftEventing::AchievementIds::FloatYourGoat,
    base::MinecraftEventing::AchievementIds::Friend,
    base::MinecraftEventing::AchievementIds::WaxOnWaxOff,
    base::MinecraftEventing::AchievementIds::StriderRiddenInLavaInOverworld,
    base::MinecraftEventing::AchievementIds::GoatHornAcquired,
    base::MinecraftEventing::AchievementIds::JukeboxUsedInMeadows,
    base::MinecraftEventing::AchievementIds::TradedAtWorldHeight,
    base::MinecraftEventing::AchievementIds::SurvivedFallFromWorldHeight,
    base::MinecraftEventing::AchievementIds::SneakCloseToSculkSensor,
    base::MinecraftEventing::AchievementIds::ItSpreads,
    base::MinecraftEventing::AchievementIds::BirthdaySong,
    base::MinecraftEventing::AchievementIds::WithOurPowersCombined,
    base::MinecraftEventing::AchievementIds::PlantingThePast,
    base::MinecraftEventing::AchievementIds::CarefulRestoration,
    base::MinecraftEventing::AchievementIds::Revaulting,
    base::MinecraftEventing::AchievementIds::CraftersCraftingCrafters,
    base::MinecraftEventing::AchievementIds::WhoNeedsRockets,
    base::MinecraftEventing::AchievementIds::OverOverkill,
    base::MinecraftEventing::AchievementIds::Count,
}};

template <>
inline constexpr std::array<std::string_view, 70> names_v<base::MinecraftEventing::AchievementIds>{{
    "chestfullofcobblestone",
    "diamondforyou",
    "ironbelly",
    "ironman",
    "onarail",
    "overkill",
    "returntosender",
    "sniperduel",
    "stayinfrosty",
    "takeinventory",
    "maproom",
    "freightstation",
    "smelteverything",
    "tasteofyourownmedicine",
    "whenpigsfly",
    "inception",
    "artificialselection",
    "freediver",
    "spawnthewither",
    "beaconator",
    "greatview",
    "supersonic",
    "theendagain",
    "treasurehunter",
    "shootingstar",
    "fashionshow",
    "brilliance",
    "selfpublishedauthor",
    "alternativefuel",
    "sleepwiththefishes",
    "castaway",
    "imamarinebiologist",
    "sailthe7seas",
    "megold",
    "ahoy",
    "atlantis",
    "onepickletwopickleseapicklefour",
    "doabarrelroll",
    "moskstraumen",
    "echolocation",
    "wherehaveyoubeen",
    "topoftheworld",
    "fruitontheloom",
    "soundthealarm",
    "buylowsellhigh",
    "disenchanted",
    "timeforstew",
    "beeourguest",
    "totalbeelocation",
    "stickysituation",
    "covermeindebris",
    "floatyourgoat",
    "friend",
    "waxonwaxoff",
    "striderriddeninlavainoverworld",
    "goathornacquired",
    "jukeboxusedinmeadows",
    "tradedatworldheight",
    "survivedfallfromworldheight",
    "sneakclosetosculksensor",
    "itspreads",
    "birthdaysong",
    "withourpowerscombined",
    "plantingthepast",
    "carefulrestoration",
    "revaulting",
    "crafterscraftingcrafters",
    "whoneedsrockets",
    "overoverkill",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<base::MinecraftEventing::AchievementIds>{"MinecraftEventing::AchievementIds"};

template <>
inline constexpr std::array<base::MinecraftEventing::POIBlockInteractionType, 26> values_v<base::MinecraftEventing::POIBlockInteractionType>{{
    base::MinecraftEventing::POIBlockInteractionType::None,
    base::MinecraftEventing::POIBlockInteractionType::Extend,
    base::MinecraftEventing::POIBlockInteractionType::Clone,
    base::MinecraftEventing::POIBlockInteractionType::Lock,
    base::MinecraftEventing::POIBlockInteractionType::Create,
    base::MinecraftEventing::POIBlockInteractionType::CreateLocator,
    base::MinecraftEventing::POIBlockInteractionType::Rename,
    base::MinecraftEventing::POIBlockInteractionType::ItemPlaced,
    base::MinecraftEventing::POIBlockInteractionType::ItemRemoved,
    base::MinecraftEventing::POIBlockInteractionType::Cooking,
    base::MinecraftEventing::POIBlockInteractionType::Dousing,
    base::MinecraftEventing::POIBlockInteractionType::Lighting,
    base::MinecraftEventing::POIBlockInteractionType::Haystack,
    base::MinecraftEventing::POIBlockInteractionType::Filled,
    base::MinecraftEventing::POIBlockInteractionType::Emptied,
    base::MinecraftEventing::POIBlockInteractionType::AddDye,
    base::MinecraftEventing::POIBlockInteractionType::DyeItem,
    base::MinecraftEventing::POIBlockInteractionType::ClearItem,
    base::MinecraftEventing::POIBlockInteractionType::EnchantArrow,
    base::MinecraftEventing::POIBlockInteractionType::CompostItemPlaced,
    base::MinecraftEventing::POIBlockInteractionType::RecoveredBonemeal,
    base::MinecraftEventing::POIBlockInteractionType::BookPlaced,
    base::MinecraftEventing::POIBlockInteractionType::BookOpened,
    base::MinecraftEventing::POIBlockInteractionType::Disenchant,
    base::MinecraftEventing::POIBlockInteractionType::Repair,
    base::MinecraftEventing::POIBlockInteractionType::DisenchantAndRepair,
}};

template <>
inline constexpr std::array<std::string_view, 26> names_v<base::MinecraftEventing::POIBlockInteractionType>{{
    "none",
    "extend",
    "clone",
    "lock",
    "create",
    "createlocator",
    "rename",
    "itemplaced",
    "itemremoved",
    "cooking",
    "dousing",
    "lighting",
    "haystack",
    "filled",
    "emptied",
    "adddye",
    "dyeitem",
    "clearitem",
    "enchantarrow",
    "compostitemplaced",
    "recoveredbonemeal",
    "bookplaced",
    "bookopened",
    "disenchant",
    "repair",
    "disenchantandrepair",
}};

template <>
inline constexpr std::string_view type_name_v<base::MinecraftEventing::POIBlockInteractionType>{"MinecraftEventing::POIBlockInteractionType"};

template <>
inline constexpr std::array<v766::MinecraftEventing::InteractionType, 16> values_v<v766::MinecraftEventing::InteractionType>{{
    v766::MinecraftEventing::InteractionType::Breeding,
    v766::MinecraftEventing::InteractionType::Taming,
    v766::MinecraftEventing::InteractionType::Curing,
    v766::MinecraftEventing::InteractionType::Crafted,
    v766::MinecraftEventing::InteractionType::Shearing,
    v766::MinecraftEventing::InteractionType::Milking,
    v766::MinecraftEventing::InteractionType::Trading,
    v766::MinecraftEventing::InteractionType::Feeding,
    v766::MinecraftEventing::InteractionType::Igniting,
    v766::MinecraftEventing::InteractionType::Coloring,
    v766::MinecraftEventing::InteractionType::Naming,
    v766::MinecraftEventing::InteractionType::Leashing,
    v766::MinecraftEventing::InteractionType::Unleashing,
    v766::MinecraftEventing::InteractionType::PetSleep,
    v766::MinecraftEventing::InteractionType::Trusting,
    v766::MinecraftEventing::InteractionType::Commanding,
}};

template <>
inline constexpr std::array<std::string_view, 16> names_v<v766::MinecraftEventing::InteractionType>{{
    "breeding",
    "taming",
    "curing",
    "crafted",
    "shearing",
    "milking",
    "trading",
    "feeding",
    "igniting",
    "coloring",
    "naming",
    "leashing",
    "unleashing",
    "petsleep",
    "trusting",
    "commanding",
}};

template <>
inline constexpr std::string_view type_name_v<v766::MinecraftEventing::InteractionType>{"MinecraftEventing::InteractionType"};

template <>
inline constexpr std::array<v766::MinecraftEventing::AchievementIds, 71> values_v<v766::MinecraftEventing::AchievementIds>{{
    v766::MinecraftEventing::AchievementIds::ChestFullOfCobblestone,
    v766::MinecraftEventing::AchievementIds::DiamondForYou,
    v766::MinecraftEventing::AchievementIds::IronBelly,
    v766::MinecraftEventing::AchievementIds::IronMan,
    v766::MinecraftEventing::AchievementIds::OnARail,
    v766::MinecraftEventing::AchievementIds::Overkill,
    v766::MinecraftEventing::AchievementIds::ReturnToSender,
    v766::MinecraftEventing::AchievementIds::SniperDuel,
    v766::MinecraftEventing::AchievementIds::StayinFrosty,
    v766::MinecraftEventing::AchievementIds::TakeInventory,
    v766::MinecraftEventing::AchievementIds::MapRoom,
    v766::MinecraftEventing::AchievementIds::FreightStation,
    v766::MinecraftEventing::AchievementIds::SmeltEverything,
    v766::MinecraftEventing::AchievementIds::TasteOfYourOwnMedicine,
    v766::MinecraftEventing::AchievementIds::WhenPigsFly,
    v766::MinecraftEventing::AchievementIds::Inception,
    v766::MinecraftEventing::AchievementIds::ArtificialSelection,
    v766::MinecraftEventing::AchievementIds::FreeDiver,
    v766::MinecraftEventing::AchievementIds::SpawnTheWither,
    v766::MinecraftEventing::AchievementIds::Beaconator,
    v766::MinecraftEventing::AchievementIds::GreatView,
    v766::MinecraftEventing::AchievementIds::SuperSonic,
    v766::MinecraftEventing::AchievementIds::TheEndAgain,
    v766::MinecraftEventing::AchievementIds::TreasureHunter,
    v766::MinecraftEventing::AchievementIds::ShootingStar,
    v766::MinecraftEventing::AchievementIds::FashionShow,
    v766::MinecraftEventing::AchievementIds::Brilliance,
    v766::MinecraftEventing::AchievementIds::SelfPublishedAuthor,
    v766::MinecraftEventing::AchievementIds::AlternativeFuel,
    v766::MinecraftEventing::AchievementIds::SleepWithTheFishes,
    v766::MinecraftEventing::AchievementIds::Castaway,
    v766::MinecraftEventing::AchievementIds::ImAMarineBiologist,
    v766::MinecraftEventing::AchievementIds::SailThe7Seas,
    v766::MinecraftEventing::AchievementIds::MeGold,
    v766::MinecraftEventing::AchievementIds::Ahoy,
    v766::MinecraftEventing::AchievementIds::Atlantis,
    v766::MinecraftEventing::AchievementIds::OnePickleTwoPickleSeaPickleFour,
    v766::MinecraftEventing::AchievementIds::DoaBarrelRoll,
    v766::MinecraftEventing::AchievementIds::Moskstraumen,
    v766::MinecraftEventing::AchievementIds::Echolocation,
    v766::MinecraftEventing::AchievementIds::WhereHaveYouBeen,
    v766::MinecraftEventing::AchievementIds::TopOfTheWorld,
    v766::MinecraftEventing::AchievementIds::FruitOnTheLoom,
    v766::MinecraftEventing::AchievementIds::SoundTheAlarm,
    v766::MinecraftEventing::AchievementIds::BuyLowSellHigh,
    v766::MinecraftEventing::AchievementIds::Disenchanted,
    v766::MinecraftEventing::AchievementIds::TimeForStew,
    v766::MinecraftEventing::AchievementIds::BeeOurGuest,
    v766::MinecraftEventing::AchievementIds::TotalBeeLocation,
    v766::MinecraftEventing::AchievementIds::StickySituation,
    v766::MinecraftEventing::AchievementIds::CoverMeInDebris,
    v766::MinecraftEventing::AchievementIds::FloatYourGoat,
    v766::MinecraftEventing::AchievementIds::Friend,
    v766::MinecraftEventing::AchievementIds::WaxOnWaxOff,
    v766::MinecraftEventing::AchievementIds::StriderRiddenInLavaInOverworld,
    v766::MinecraftEventing::AchievementIds::GoatHornAcquired,
    v766::MinecraftEventing::AchievementIds::JukeboxUsedInMeadows,
    v766::MinecraftEventing::AchievementIds::TradedAtWorldHeight,
    v766::MinecraftEventing::AchievementIds::SurvivedFallFromWorldHeight,
    v766::MinecraftEventing::AchievementIds::SneakCloseToSculkSensor,
    v766::MinecraftEventing::AchievementIds::ItSpreads,
    v766::MinecraftEventing::AchievementIds::BirthdaySong,
    v766::MinecraftEventing::AchievementIds::WithOurPowersCombined,
    v766::MinecraftEventing::AchievementIds::PlantingThePast,
    v766::MinecraftEventing::AchievementIds::CarefulRestoration,
    v766::MinecraftEventing::AchievementIds::Revaulting,
    v766::MinecraftEventing::AchievementIds::CraftersCraftingCrafters,
    v766::MinecraftEventing::AchievementIds::WhoNeedsRockets,
    v766::MinecraftEventing::AchievementIds::OverOverkill,
    v766::MinecraftEventing::AchievementIds::HeartTransplanter,
    v766::MinecraftEventing::AchievementIds::Count,
}};

template <>
inline constexpr std::array<std::string_view, 71> names_v<v766::MinecraftEventing::AchievementIds>{{
    "chestfullofcobblestone",
    "diamondforyou",
    "ironbelly",
    "ironman",
    "onarail",
    "overkill",
    "returntosender",
    "sniperduel",
    "stayinfrosty",
    "takeinventory",
    "maproom",
    "freightstation",
    "smelteverything",
    "tasteofyourownmedicine",
    "whenpigsfly",
    "inception",
    "artificialselection",
    "freediver",
    "spawnthewither",
    "beaconator",
    "greatview",
    "supersonic",
    "theendagain",
    "treasurehunter",
    "shootingstar",
    "fashionshow",
    "brilliance",
    "selfpublishedauthor",
    "alternativefuel",
    "sleepwiththefishes",
    "castaway",
    "imamarinebiologist",
    "sailthe7seas",
    "megold",
    "ahoy",
    "atlantis",
    "onepickletwopickleseapicklefour",
    "doabarrelroll",
    "moskstraumen",
    "echolocation",
    "wherehaveyoubeen",
    "topoftheworld",
    "fruitontheloom",
    "soundthealarm",
    "buylowsellhigh",
    "disenchanted",
    "timeforstew",
    "beeourguest",
    "totalbeelocation",
    "stickysituation",
    "covermeindebris",
    "floatyourgoat",
    "friend",
    "waxonwaxoff",
    "striderriddeninlavainoverworld",
    "goathornacquired",
    "jukeboxusedinmeadows",
    "tradedatworldheight",
    "survivedfallfromworldheight",
    "sneakclosetosculksensor",
    "itspreads",
    "birthdaysong",
    "withourpowerscombined",
    "plantingthepast",
    "carefulrestoration",
    "revaulting",
    "crafterscraftingcrafters",
    "whoneedsrockets",
    "overoverkill",
    "hearttransplanter",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<v766::MinecraftEventing::AchievementIds>{"MinecraftEventing::AchievementIds"};

template <>
inline constexpr std::array<v776::MinecraftEventing::InteractionType, 16> values_v<v776::MinecraftEventing::InteractionType>{{
    v776::MinecraftEventing::InteractionType::Breeding,
    v776::MinecraftEventing::InteractionType::Taming,
    v776::MinecraftEventing::InteractionType::Curing,
    v776::MinecraftEventing::InteractionType::Crafted,
    v776::MinecraftEventing::InteractionType::Shearing,
    v776::MinecraftEventing::InteractionType::Milking,
    v776::MinecraftEventing::InteractionType::Trading,
    v776::MinecraftEventing::InteractionType::Feeding,
    v776::MinecraftEventing::InteractionType::Igniting,
    v776::MinecraftEventing::InteractionType::Coloring,
    v776::MinecraftEventing::InteractionType::Naming,
    v776::MinecraftEventing::InteractionType::Leashing,
    v776::MinecraftEventing::InteractionType::Unleashing,
    v776::MinecraftEventing::InteractionType::PetSleep,
    v776::MinecraftEventing::InteractionType::Trusting,
    v776::MinecraftEventing::InteractionType::Commanding,
}};

template <>
inline constexpr std::array<std::string_view, 16> names_v<v776::MinecraftEventing::InteractionType>{{
    "breeding",
    "taming",
    "curing",
    "crafted",
    "shearing",
    "milking",
    "trading",
    "feeding",
    "igniting",
    "coloring",
    "naming",
    "leashing",
    "unleashing",
    "petsleep",
    "trusting",
    "commanding",
}};

template <>
inline constexpr std::string_view type_name_v<v776::MinecraftEventing::InteractionType>{"MinecraftEventing::InteractionType"};

template <>
inline constexpr std::array<v776::MinecraftEventing::AchievementIds, 70> values_v<v776::MinecraftEventing::AchievementIds>{{
    v776::MinecraftEventing::AchievementIds::ChestFullOfCobblestone,
    v776::MinecraftEventing::AchievementIds::DiamondForYou,
    v776::MinecraftEventing::AchievementIds::IronBelly,
    v776::MinecraftEventing::AchievementIds::IronMan,
    v776::MinecraftEventing::AchievementIds::OnARail,
    v776::MinecraftEventing::AchievementIds::Overkill,
    v776::MinecraftEventing::AchievementIds::ReturnToSender,
    v776::MinecraftEventing::AchievementIds::SniperDuel,
    v776::MinecraftEventing::AchievementIds::StayinFrosty,
    v776::MinecraftEventing::AchievementIds::TakeInventory,
    v776::MinecraftEventing::AchievementIds::MapRoom,
    v776::MinecraftEventing::AchievementIds::FreightStation,
    v776::MinecraftEventing::AchievementIds::SmeltEverything,
    v776::MinecraftEventing::AchievementIds::TasteOfYourOwnMedicine,
    v776::MinecraftEventing::AchievementIds::WhenPigsFly,
    v776::MinecraftEventing::AchievementIds::Inception,
    v776::MinecraftEventing::AchievementIds::ArtificialSelection,
    v776::MinecraftEventing::AchievementIds::FreeDiver,
    v776::MinecraftEventing::AchievementIds::SpawnTheWither,
    v776::MinecraftEventing::AchievementIds::Beaconator,
    v776::MinecraftEventing::AchievementIds::GreatView,
    v776::MinecraftEventing::AchievementIds::SuperSonic,
    v776::MinecraftEventing::AchievementIds::TheEndAgain,
    v776::MinecraftEventing::AchievementIds::TreasureHunter,
    v776::MinecraftEventing::AchievementIds::ShootingStar,
    v776::MinecraftEventing::AchievementIds::FashionShow,
    v776::MinecraftEventing::AchievementIds::SelfPublishedAuthor,
    v776::MinecraftEventing::AchievementIds::AlternativeFuel,
    v776::MinecraftEventing::AchievementIds::SleepWithTheFishes,
    v776::MinecraftEventing::AchievementIds::Castaway,
    v776::MinecraftEventing::AchievementIds::ImAMarineBiologist,
    v776::MinecraftEventing::AchievementIds::SailThe7Seas,
    v776::MinecraftEventing::AchievementIds::MeGold,
    v776::MinecraftEventing::AchievementIds::Ahoy,
    v776::MinecraftEventing::AchievementIds::Atlantis,
    v776::MinecraftEventing::AchievementIds::OnePickleTwoPickleSeaPickleFour,
    v776::MinecraftEventing::AchievementIds::DoaBarrelRoll,
    v776::MinecraftEventing::AchievementIds::Moskstraumen,
    v776::MinecraftEventing::AchievementIds::Echolocation,
    v776::MinecraftEventing::AchievementIds::WhereHaveYouBeen,
    v776::MinecraftEventing::AchievementIds::TopOfTheWorld,
    v776::MinecraftEventing::AchievementIds::FruitOnTheLoom,
    v776::MinecraftEventing::AchievementIds::SoundTheAlarm,
    v776::MinecraftEventing::AchievementIds::BuyLowSellHigh,
    v776::MinecraftEventing::AchievementIds::Disenchanted,
    v776::MinecraftEventing::AchievementIds::TimeForStew,
    v776::MinecraftEventing::AchievementIds::BeeOurGuest,
    v776::MinecraftEventing::AchievementIds::TotalBeeLocation,
    v776::MinecraftEventing::AchievementIds::StickySituation,
    v776::MinecraftEventing::AchievementIds::CoverMeInDebris,
    v776::MinecraftEventing::AchievementIds::FloatYourGoat,
    v776::MinecraftEventing::AchievementIds::Friend,
    v776::MinecraftEventing::AchievementIds::WaxOnWaxOff,
    v776::MinecraftEventing::AchievementIds::StriderRiddenInLavaInOverworld,
    v776::MinecraftEventing::AchievementIds::GoatHornAcquired,
    v776::MinecraftEventing::AchievementIds::JukeboxUsedInMeadows,
    v776::MinecraftEventing::AchievementIds::TradedAtWorldHeight,
    v776::MinecraftEventing::AchievementIds::SurvivedFallFromWorldHeight,
    v776::MinecraftEventing::AchievementIds::SneakCloseToSculkSensor,
    v776::MinecraftEventing::AchievementIds::ItSpreads,
    v776::MinecraftEventing::AchievementIds::BirthdaySong,
    v776::MinecraftEventing::AchievementIds::WithOurPowersCombined,
    v776::MinecraftEventing::AchievementIds::PlantingThePast,
    v776::MinecraftEventing::AchievementIds::CarefulRestoration,
    v776::MinecraftEventing::AchievementIds::Revaulting,
    v776::MinecraftEventing::AchievementIds::CraftersCraftingCrafters,
    v776::MinecraftEventing::AchievementIds::WhoNeedsRockets,
    v776::MinecraftEventing::AchievementIds::OverOverkill,
    v776::MinecraftEventing::AchievementIds::HeartTransplanter,
    v776::MinecraftEventing::AchievementIds::Count,
}};

template <>
inline constexpr std::array<std::string_view, 70> names_v<v776::MinecraftEventing::AchievementIds>{{
    "chestfullofcobblestone",
    "diamondforyou",
    "ironbelly",
    "ironman",
    "onarail",
    "overkill",
    "returntosender",
    "sniperduel",
    "stayinfrosty",
    "takeinventory",
    "maproom",
    "freightstation",
    "smelteverything",
    "tasteofyourownmedicine",
    "whenpigsfly",
    "inception",
    "artificialselection",
    "freediver",
    "spawnthewither",
    "beaconator",
    "greatview",
    "supersonic",
    "theendagain",
    "treasurehunter",
    "shootingstar",
    "fashionshow",
    "selfpublishedauthor",
    "alternativefuel",
    "sleepwiththefishes",
    "castaway",
    "imamarinebiologist",
    "sailthe7seas",
    "megold",
    "ahoy",
    "atlantis",
    "onepickletwopickleseapicklefour",
    "doabarrelroll",
    "moskstraumen",
    "echolocation",
    "wherehaveyoubeen",
    "topoftheworld",
    "fruitontheloom",
    "soundthealarm",
    "buylowsellhigh",
    "disenchanted",
    "timeforstew",
    "beeourguest",
    "totalbeelocation",
    "stickysituation",
    "covermeindebris",
    "floatyourgoat",
    "friend",
    "waxonwaxoff",
    "striderriddeninlavainoverworld",
    "goathornacquired",
    "jukeboxusedinmeadows",
    "tradedatworldheight",
    "survivedfallfromworldheight",
    "sneakclosetosculksensor",
    "itspreads",
    "birthdaysong",
    "withourpowerscombined",
    "plantingthepast",
    "carefulrestoration",
    "revaulting",
    "crafterscraftingcrafters",
    "whoneedsrockets",
    "overoverkill",
    "hearttransplanter",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<v776::MinecraftEventing::AchievementIds>{"MinecraftEventing::AchievementIds"};

template <>
inline constexpr std::array<v818::MinecraftEventing::InteractionType, 16> values_v<v818::MinecraftEventing::InteractionType>{{
    v818::MinecraftEventing::InteractionType::Breeding,
    v818::MinecraftEventing::InteractionType::Taming,
    v818::MinecraftEventing::InteractionType::Curing,
    v818::MinecraftEventing::InteractionType::Crafted,
    v818::MinecraftEventing::InteractionType::Shearing,
    v818::MinecraftEventing::InteractionType::Milking,
    v818::MinecraftEventing::InteractionType::Trading,
    v818::MinecraftEventing::InteractionType::Feeding,
    v818::MinecraftEventing::InteractionType::Igniting,
    v818::MinecraftEventing::InteractionType::Coloring,
    v818::MinecraftEventing::InteractionType::Naming,
    v818::MinecraftEventing::InteractionType::Leashing,
    v818::MinecraftEventing::InteractionType::Unleashing,
    v818::MinecraftEventing::InteractionType::PetSleep,
    v818::MinecraftEventing::InteractionType::Trusting,
    v818::MinecraftEventing::InteractionType::Commanding,
}};

template <>
inline constexpr std::array<std::string_view, 16> names_v<v818::MinecraftEventing::InteractionType>{{
    "breeding",
    "taming",
    "curing",
    "crafted",
    "shearing",
    "milking",
    "trading",
    "feeding",
    "igniting",
    "coloring",
    "naming",
    "leashing",
    "unleashing",
    "petsleep",
    "trusting",
    "commanding",
}};

template <>
inline constexpr std::string_view type_name_v<v818::MinecraftEventing::InteractionType>{"MinecraftEventing::InteractionType"};

template <>
inline constexpr std::array<v818::MinecraftEventing::AchievementIds, 71> values_v<v818::MinecraftEventing::AchievementIds>{{
    v818::MinecraftEventing::AchievementIds::ChestFullOfCobblestone,
    v818::MinecraftEventing::AchievementIds::DiamondForYou,
    v818::MinecraftEventing::AchievementIds::IronBelly,
    v818::MinecraftEventing::AchievementIds::IronMan,
    v818::MinecraftEventing::AchievementIds::OnARail,
    v818::MinecraftEventing::AchievementIds::Overkill,
    v818::MinecraftEventing::AchievementIds::ReturnToSender,
    v818::MinecraftEventing::AchievementIds::SniperDuel,
    v818::MinecraftEventing::AchievementIds::StayinFrosty,
    v818::MinecraftEventing::AchievementIds::TakeInventory,
    v818::MinecraftEventing::AchievementIds::MapRoom,
    v818::MinecraftEventing::AchievementIds::FreightStation,
    v818::MinecraftEventing::AchievementIds::SmeltEverything,
    v818::MinecraftEventing::AchievementIds::TasteOfYourOwnMedicine,
    v818::MinecraftEventing::AchievementIds::WhenPigsFly,
    v818::MinecraftEventing::AchievementIds::Inception,
    v818::MinecraftEventing::AchievementIds::ArtificialSelection,
    v818::MinecraftEventing::AchievementIds::FreeDiver,
    v818::MinecraftEventing::AchievementIds::SpawnTheWither,
    v818::MinecraftEventing::AchievementIds::Beaconator,
    v818::MinecraftEventing::AchievementIds::GreatView,
    v818::MinecraftEventing::AchievementIds::SuperSonic,
    v818::MinecraftEventing::AchievementIds::TheEndAgain,
    v818::MinecraftEventing::AchievementIds::TreasureHunter,
    v818::MinecraftEventing::AchievementIds::ShootingStar,
    v818::MinecraftEventing::AchievementIds::FashionShow,
    v818::MinecraftEventing::AchievementIds::SelfPublishedAuthor,
    v818::MinecraftEventing::AchievementIds::AlternativeFuel,
    v818::MinecraftEventing::AchievementIds::SleepWithTheFishes,
    v818::MinecraftEventing::AchievementIds::Castaway,
    v818::MinecraftEventing::AchievementIds::ImAMarineBiologist,
    v818::MinecraftEventing::AchievementIds::SailThe7Seas,
    v818::MinecraftEventing::AchievementIds::MeGold,
    v818::MinecraftEventing::AchievementIds::Ahoy,
    v818::MinecraftEventing::AchievementIds::Atlantis,
    v818::MinecraftEventing::AchievementIds::OnePickleTwoPickleSeaPickleFour,
    v818::MinecraftEventing::AchievementIds::DoaBarrelRoll,
    v818::MinecraftEventing::AchievementIds::Moskstraumen,
    v818::MinecraftEventing::AchievementIds::Echolocation,
    v818::MinecraftEventing::AchievementIds::WhereHaveYouBeen,
    v818::MinecraftEventing::AchievementIds::TopOfTheWorld,
    v818::MinecraftEventing::AchievementIds::FruitOnTheLoom,
    v818::MinecraftEventing::AchievementIds::SoundTheAlarm,
    v818::MinecraftEventing::AchievementIds::BuyLowSellHigh,
    v818::MinecraftEventing::AchievementIds::Disenchanted,
    v818::MinecraftEventing::AchievementIds::TimeForStew,
    v818::MinecraftEventing::AchievementIds::BeeOurGuest,
    v818::MinecraftEventing::AchievementIds::TotalBeeLocation,
    v818::MinecraftEventing::AchievementIds::StickySituation,
    v818::MinecraftEventing::AchievementIds::CoverMeInDebris,
    v818::MinecraftEventing::AchievementIds::FloatYourGoat,
    v818::MinecraftEventing::AchievementIds::Friend,
    v818::MinecraftEventing::AchievementIds::WaxOnWaxOff,
    v818::MinecraftEventing::AchievementIds::StriderRiddenInLavaInOverworld,
    v818::MinecraftEventing::AchievementIds::GoatHornAcquired,
    v818::MinecraftEventing::AchievementIds::JukeboxUsedInMeadows,
    v818::MinecraftEventing::AchievementIds::TradedAtWorldHeight,
    v818::MinecraftEventing::AchievementIds::SurvivedFallFromWorldHeight,
    v818::MinecraftEventing::AchievementIds::SneakCloseToSculkSensor,
    v818::MinecraftEventing::AchievementIds::ItSpreads,
    v818::MinecraftEventing::AchievementIds::BirthdaySong,
    v818::MinecraftEventing::AchievementIds::WithOurPowersCombined,
    v818::MinecraftEventing::AchievementIds::PlantingThePast,
    v818::MinecraftEventing::AchievementIds::CarefulRestoration,
    v818::MinecraftEventing::AchievementIds::Revaulting,
    v818::MinecraftEventing::AchievementIds::CraftersCraftingCrafters,
    v818::MinecraftEventing::AchievementIds::WhoNeedsRockets,
    v818::MinecraftEventing::AchievementIds::OverOverkill,
    v818::MinecraftEventing::AchievementIds::HeartTransplanter,
    v818::MinecraftEventing::AchievementIds::StayHydrated,
    v818::MinecraftEventing::AchievementIds::Count,
}};

template <>
inline constexpr std::array<std::string_view, 71> names_v<v818::MinecraftEventing::AchievementIds>{{
    "chestfullofcobblestone",
    "diamondforyou",
    "ironbelly",
    "ironman",
    "onarail",
    "overkill",
    "returntosender",
    "sniperduel",
    "stayinfrosty",
    "takeinventory",
    "maproom",
    "freightstation",
    "smelteverything",
    "tasteofyourownmedicine",
    "whenpigsfly",
    "inception",
    "artificialselection",
    "freediver",
    "spawnthewither",
    "beaconator",
    "greatview",
    "supersonic",
    "theendagain",
    "treasurehunter",
    "shootingstar",
    "fashionshow",
    "selfpublishedauthor",
    "alternativefuel",
    "sleepwiththefishes",
    "castaway",
    "imamarinebiologist",
    "sailthe7seas",
    "megold",
    "ahoy",
    "atlantis",
    "onepickletwopickleseapicklefour",
    "doabarrelroll",
    "moskstraumen",
    "echolocation",
    "wherehaveyoubeen",
    "topoftheworld",
    "fruitontheloom",
    "soundthealarm",
    "buylowsellhigh",
    "disenchanted",
    "timeforstew",
    "beeourguest",
    "totalbeelocation",
    "stickysituation",
    "covermeindebris",
    "floatyourgoat",
    "friend",
    "waxonwaxoff",
    "striderriddeninlavainoverworld",
    "goathornacquired",
    "jukeboxusedinmeadows",
    "tradedatworldheight",
    "survivedfallfromworldheight",
    "sneakclosetosculksensor",
    "itspreads",
    "birthdaysong",
    "withourpowerscombined",
    "plantingthepast",
    "carefulrestoration",
    "revaulting",
    "crafterscraftingcrafters",
    "whoneedsrockets",
    "overoverkill",
    "hearttransplanter",
    "stayhydrated",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<v818::MinecraftEventing::AchievementIds>{"MinecraftEventing::AchievementIds"};

template <>
inline constexpr std::array<v898::MinecraftEventing::InteractionType, 16> values_v<v898::MinecraftEventing::InteractionType>{{
    v898::MinecraftEventing::InteractionType::Breeding,
    v898::MinecraftEventing::InteractionType::Taming,
    v898::MinecraftEventing::InteractionType::Curing,
    v898::MinecraftEventing::InteractionType::Crafted,
    v898::MinecraftEventing::InteractionType::Shearing,
    v898::MinecraftEventing::InteractionType::Milking,
    v898::MinecraftEventing::InteractionType::Trading,
    v898::MinecraftEventing::InteractionType::Feeding,
    v898::MinecraftEventing::InteractionType::Igniting,
    v898::MinecraftEventing::InteractionType::Coloring,
    v898::MinecraftEventing::InteractionType::Naming,
    v898::MinecraftEventing::InteractionType::Leashing,
    v898::MinecraftEventing::InteractionType::Unleashing,
    v898::MinecraftEventing::InteractionType::PetSleep,
    v898::MinecraftEventing::InteractionType::Trusting,
    v898::MinecraftEventing::InteractionType::Commanding,
}};

template <>
inline constexpr std::array<std::string_view, 16> names_v<v898::MinecraftEventing::InteractionType>{{
    "breeding",
    "taming",
    "curing",
    "crafted",
    "shearing",
    "milking",
    "trading",
    "feeding",
    "igniting",
    "coloring",
    "naming",
    "leashing",
    "unleashing",
    "petsleep",
    "trusting",
    "commanding",
}};

template <>
inline constexpr std::string_view type_name_v<v898::MinecraftEventing::InteractionType>{"MinecraftEventing::InteractionType"};

template <>
inline constexpr std::array<v898::MinecraftEventing::AchievementIds, 72> values_v<v898::MinecraftEventing::AchievementIds>{{
    v898::MinecraftEventing::AchievementIds::ChestFullOfCobblestone,
    v898::MinecraftEventing::AchievementIds::DiamondForYou,
    v898::MinecraftEventing::AchievementIds::IronBelly,
    v898::MinecraftEventing::AchievementIds::IronMan,
    v898::MinecraftEventing::AchievementIds::OnARail,
    v898::MinecraftEventing::AchievementIds::Overkill,
    v898::MinecraftEventing::AchievementIds::ReturnToSender,
    v898::MinecraftEventing::AchievementIds::SniperDuel,
    v898::MinecraftEventing::AchievementIds::StayinFrosty,
    v898::MinecraftEventing::AchievementIds::TakeInventory,
    v898::MinecraftEventing::AchievementIds::MapRoom,
    v898::MinecraftEventing::AchievementIds::FreightStation,
    v898::MinecraftEventing::AchievementIds::SmeltEverything,
    v898::MinecraftEventing::AchievementIds::TasteOfYourOwnMedicine,
    v898::MinecraftEventing::AchievementIds::WhenPigsFly,
    v898::MinecraftEventing::AchievementIds::Inception,
    v898::MinecraftEventing::AchievementIds::ArtificialSelection,
    v898::MinecraftEventing::AchievementIds::FreeDiver,
    v898::MinecraftEventing::AchievementIds::SpawnTheWither,
    v898::MinecraftEventing::AchievementIds::Beaconator,
    v898::MinecraftEventing::AchievementIds::GreatView,
    v898::MinecraftEventing::AchievementIds::SuperSonic,
    v898::MinecraftEventing::AchievementIds::TheEndAgain,
    v898::MinecraftEventing::AchievementIds::TreasureHunter,
    v898::MinecraftEventing::AchievementIds::ShootingStar,
    v898::MinecraftEventing::AchievementIds::FashionShow,
    v898::MinecraftEventing::AchievementIds::SelfPublishedAuthor,
    v898::MinecraftEventing::AchievementIds::AlternativeFuel,
    v898::MinecraftEventing::AchievementIds::SleepWithTheFishes,
    v898::MinecraftEventing::AchievementIds::Castaway,
    v898::MinecraftEventing::AchievementIds::ImAMarineBiologist,
    v898::MinecraftEventing::AchievementIds::SailThe7Seas,
    v898::MinecraftEventing::AchievementIds::MeGold,
    v898::MinecraftEventing::AchievementIds::Ahoy,
    v898::MinecraftEventing::AchievementIds::Atlantis,
    v898::MinecraftEventing::AchievementIds::OnePickleTwoPickleSeaPickleFour,
    v898::MinecraftEventing::AchievementIds::DoaBarrelRoll,
    v898::MinecraftEventing::AchievementIds::Moskstraumen,
    v898::MinecraftEventing::AchievementIds::Echolocation,
    v898::MinecraftEventing::AchievementIds::WhereHaveYouBeen,
    v898::MinecraftEventing::AchievementIds::TopOfTheWorld,
    v898::MinecraftEventing::AchievementIds::FruitOnTheLoom,
    v898::MinecraftEventing::AchievementIds::SoundTheAlarm,
    v898::MinecraftEventing::AchievementIds::BuyLowSellHigh,
    v898::MinecraftEventing::AchievementIds::Disenchanted,
    v898::MinecraftEventing::AchievementIds::TimeForStew,
    v898::MinecraftEventing::AchievementIds::BeeOurGuest,
    v898::MinecraftEventing::AchievementIds::TotalBeeLocation,
    v898::MinecraftEventing::AchievementIds::StickySituation,
    v898::MinecraftEventing::AchievementIds::CoverMeInDebris,
    v898::MinecraftEventing::AchievementIds::FloatYourGoat,
    v898::MinecraftEventing::AchievementIds::Friend,
    v898::MinecraftEventing::AchievementIds::WaxOnWaxOff,
    v898::MinecraftEventing::AchievementIds::StriderRiddenInLavaInOverworld,
    v898::MinecraftEventing::AchievementIds::GoatHornAcquired,
    v898::MinecraftEventing::AchievementIds::JukeboxUsedInMeadows,
    v898::MinecraftEventing::AchievementIds::TradedAtWorldHeight,
    v898::MinecraftEventing::AchievementIds::SurvivedFallFromWorldHeight,
    v898::MinecraftEventing::AchievementIds::SneakCloseToSculkSensor,
    v898::MinecraftEventing::AchievementIds::ItSpreads,
    v898::MinecraftEventing::AchievementIds::BirthdaySong,
    v898::MinecraftEventing::AchievementIds::WithOurPowersCombined,
    v898::MinecraftEventing::AchievementIds::PlantingThePast,
    v898::MinecraftEventing::AchievementIds::CarefulRestoration,
    v898::MinecraftEventing::AchievementIds::Revaulting,
    v898::MinecraftEventing::AchievementIds::CraftersCraftingCrafters,
    v898::MinecraftEventing::AchievementIds::WhoNeedsRockets,
    v898::MinecraftEventing::AchievementIds::OverOverkill,
    v898::MinecraftEventing::AchievementIds::HeartTransplanter,
    v898::MinecraftEventing::AchievementIds::StayHydrated,
    v898::MinecraftEventing::AchievementIds::MobKabob,
    v898::MinecraftEventing::AchievementIds::Count,
}};

template <>
inline constexpr std::array<std::string_view, 72> names_v<v898::MinecraftEventing::AchievementIds>{{
    "chestfullofcobblestone",
    "diamondforyou",
    "ironbelly",
    "ironman",
    "onarail",
    "overkill",
    "returntosender",
    "sniperduel",
    "stayinfrosty",
    "takeinventory",
    "maproom",
    "freightstation",
    "smelteverything",
    "tasteofyourownmedicine",
    "whenpigsfly",
    "inception",
    "artificialselection",
    "freediver",
    "spawnthewither",
    "beaconator",
    "greatview",
    "supersonic",
    "theendagain",
    "treasurehunter",
    "shootingstar",
    "fashionshow",
    "selfpublishedauthor",
    "alternativefuel",
    "sleepwiththefishes",
    "castaway",
    "imamarinebiologist",
    "sailthe7seas",
    "megold",
    "ahoy",
    "atlantis",
    "onepickletwopickleseapicklefour",
    "doabarrelroll",
    "moskstraumen",
    "echolocation",
    "wherehaveyoubeen",
    "topoftheworld",
    "fruitontheloom",
    "soundthealarm",
    "buylowsellhigh",
    "disenchanted",
    "timeforstew",
    "beeourguest",
    "totalbeelocation",
    "stickysituation",
    "covermeindebris",
    "floatyourgoat",
    "friend",
    "waxonwaxoff",
    "striderriddeninlavainoverworld",
    "goathornacquired",
    "jukeboxusedinmeadows",
    "tradedatworldheight",
    "survivedfallfromworldheight",
    "sneakclosetosculksensor",
    "itspreads",
    "birthdaysong",
    "withourpowerscombined",
    "plantingthepast",
    "carefulrestoration",
    "revaulting",
    "crafterscraftingcrafters",
    "whoneedsrockets",
    "overoverkill",
    "hearttransplanter",
    "stayhydrated",
    "mobkabob",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<v898::MinecraftEventing::AchievementIds>{"MinecraftEventing::AchievementIds"};

template <>
inline constexpr std::array<v924::MinecraftEventing::InteractionType, 16> values_v<v924::MinecraftEventing::InteractionType>{{
    v924::MinecraftEventing::InteractionType::Breeding,
    v924::MinecraftEventing::InteractionType::Taming,
    v924::MinecraftEventing::InteractionType::Curing,
    v924::MinecraftEventing::InteractionType::Crafted,
    v924::MinecraftEventing::InteractionType::Shearing,
    v924::MinecraftEventing::InteractionType::Milking,
    v924::MinecraftEventing::InteractionType::Trading,
    v924::MinecraftEventing::InteractionType::Feeding,
    v924::MinecraftEventing::InteractionType::Igniting,
    v924::MinecraftEventing::InteractionType::Coloring,
    v924::MinecraftEventing::InteractionType::Naming,
    v924::MinecraftEventing::InteractionType::Leashing,
    v924::MinecraftEventing::InteractionType::Unleashing,
    v924::MinecraftEventing::InteractionType::PetSleep,
    v924::MinecraftEventing::InteractionType::Trusting,
    v924::MinecraftEventing::InteractionType::Commanding,
}};

template <>
inline constexpr std::array<std::string_view, 16> names_v<v924::MinecraftEventing::InteractionType>{{
    "breeding",
    "taming",
    "curing",
    "crafted",
    "shearing",
    "milking",
    "trading",
    "feeding",
    "igniting",
    "coloring",
    "naming",
    "leashing",
    "unleashing",
    "petsleep",
    "trusting",
    "commanding",
}};

template <>
inline constexpr std::string_view type_name_v<v924::MinecraftEventing::InteractionType>{"MinecraftEventing::InteractionType"};

template <>
inline constexpr std::array<v924::MinecraftEventing::AchievementIds, 73> values_v<v924::MinecraftEventing::AchievementIds>{{
    v924::MinecraftEventing::AchievementIds::ChestFullOfCobblestone,
    v924::MinecraftEventing::AchievementIds::DiamondForYou,
    v924::MinecraftEventing::AchievementIds::IronBelly,
    v924::MinecraftEventing::AchievementIds::IronMan,
    v924::MinecraftEventing::AchievementIds::OnARail,
    v924::MinecraftEventing::AchievementIds::Overkill,
    v924::MinecraftEventing::AchievementIds::ReturnToSender,
    v924::MinecraftEventing::AchievementIds::SniperDuel,
    v924::MinecraftEventing::AchievementIds::StayinFrosty,
    v924::MinecraftEventing::AchievementIds::TakeInventory,
    v924::MinecraftEventing::AchievementIds::MapRoom,
    v924::MinecraftEventing::AchievementIds::FreightStation,
    v924::MinecraftEventing::AchievementIds::SmeltEverything,
    v924::MinecraftEventing::AchievementIds::TasteOfYourOwnMedicine,
    v924::MinecraftEventing::AchievementIds::WhenPigsFly,
    v924::MinecraftEventing::AchievementIds::Inception,
    v924::MinecraftEventing::AchievementIds::ArtificialSelection,
    v924::MinecraftEventing::AchievementIds::FreeDiver,
    v924::MinecraftEventing::AchievementIds::SpawnTheWither,
    v924::MinecraftEventing::AchievementIds::Beaconator,
    v924::MinecraftEventing::AchievementIds::GreatView,
    v924::MinecraftEventing::AchievementIds::SuperSonic,
    v924::MinecraftEventing::AchievementIds::TheEndAgain,
    v924::MinecraftEventing::AchievementIds::TreasureHunter,
    v924::MinecraftEventing::AchievementIds::ShootingStar,
    v924::MinecraftEventing::AchievementIds::FashionShow,
    v924::MinecraftEventing::AchievementIds::SelfPublishedAuthor,
    v924::MinecraftEventing::AchievementIds::AlternativeFuel,
    v924::MinecraftEventing::AchievementIds::SleepWithTheFishes,
    v924::MinecraftEventing::AchievementIds::Castaway,
    v924::MinecraftEventing::AchievementIds::ImAMarineBiologist,
    v924::MinecraftEventing::AchievementIds::SailThe7Seas,
    v924::MinecraftEventing::AchievementIds::MeGold,
    v924::MinecraftEventing::AchievementIds::Ahoy,
    v924::MinecraftEventing::AchievementIds::Atlantis,
    v924::MinecraftEventing::AchievementIds::OnePickleTwoPickleSeaPickleFour,
    v924::MinecraftEventing::AchievementIds::DoaBarrelRoll,
    v924::MinecraftEventing::AchievementIds::Moskstraumen,
    v924::MinecraftEventing::AchievementIds::Echolocation,
    v924::MinecraftEventing::AchievementIds::WhereHaveYouBeen,
    v924::MinecraftEventing::AchievementIds::TopOfTheWorld,
    v924::MinecraftEventing::AchievementIds::FruitOnTheLoom,
    v924::MinecraftEventing::AchievementIds::SoundTheAlarm,
    v924::MinecraftEventing::AchievementIds::BuyLowSellHigh,
    v924::MinecraftEventing::AchievementIds::Disenchanted,
    v924::MinecraftEventing::AchievementIds::TimeForStew,
    v924::MinecraftEventing::AchievementIds::BeeOurGuest,
    v924::MinecraftEventing::AchievementIds::TotalBeeLocation,
    v924::MinecraftEventing::AchievementIds::StickySituation,
    v924::MinecraftEventing::AchievementIds::CoverMeInDebris,
    v924::MinecraftEventing::AchievementIds::FloatYourGoat,
    v924::MinecraftEventing::AchievementIds::Friend,
    v924::MinecraftEventing::AchievementIds::WaxOnWaxOff,
    v924::MinecraftEventing::AchievementIds::StriderRiddenInLavaInOverworld,
    v924::MinecraftEventing::AchievementIds::GoatHornAcquired,
    v924::MinecraftEventing::AchievementIds::JukeboxUsedInMeadows,
    v924::MinecraftEventing::AchievementIds::TradedAtWorldHeight,
    v924::MinecraftEventing::AchievementIds::SurvivedFallFromWorldHeight,
    v924::MinecraftEventing::AchievementIds::SneakCloseToSculkSensor,
    v924::MinecraftEventing::AchievementIds::ItSpreads,
    v924::MinecraftEventing::AchievementIds::BirthdaySong,
    v924::MinecraftEventing::AchievementIds::WithOurPowersCombined,
    v924::MinecraftEventing::AchievementIds::PlantingThePast,
    v924::MinecraftEventing::AchievementIds::CarefulRestoration,
    v924::MinecraftEventing::AchievementIds::Revaulting,
    v924::MinecraftEventing::AchievementIds::CraftersCraftingCrafters,
    v924::MinecraftEventing::AchievementIds::WhoNeedsRockets,
    v924::MinecraftEventing::AchievementIds::OverOverkill,
    v924::MinecraftEventing::AchievementIds::HeartTransplanter,
    v924::MinecraftEventing::AchievementIds::StayHydrated,
    v924::MinecraftEventing::AchievementIds::MobKabob,
    v924::MinecraftEventing::AchievementIds::AdventuringTime,
    v924::MinecraftEventing::AchievementIds::Count,
}};

template <>
inline constexpr std::array<std::string_view, 73> names_v<v924::MinecraftEventing::AchievementIds>{{
    "chestfullofcobblestone",
    "diamondforyou",
    "ironbelly",
    "ironman",
    "onarail",
    "overkill",
    "returntosender",
    "sniperduel",
    "stayinfrosty",
    "takeinventory",
    "maproom",
    "freightstation",
    "smelteverything",
    "tasteofyourownmedicine",
    "whenpigsfly",
    "inception",
    "artificialselection",
    "freediver",
    "spawnthewither",
    "beaconator",
    "greatview",
    "supersonic",
    "theendagain",
    "treasurehunter",
    "shootingstar",
    "fashionshow",
    "selfpublishedauthor",
    "alternativefuel",
    "sleepwiththefishes",
    "castaway",
    "imamarinebiologist",
    "sailthe7seas",
    "megold",
    "ahoy",
    "atlantis",
    "onepickletwopickleseapicklefour",
    "doabarrelroll",
    "moskstraumen",
    "echolocation",
    "wherehaveyoubeen",
    "topoftheworld",
    "fruitontheloom",
    "soundthealarm",
    "buylowsellhigh",
    "disenchanted",
    "timeforstew",
    "beeourguest",
    "totalbeelocation",
    "stickysituation",
    "covermeindebris",
    "floatyourgoat",
    "friend",
    "waxonwaxoff",
    "striderriddeninlavainoverworld",
    "goathornacquired",
    "jukeboxusedinmeadows",
    "tradedatworldheight",
    "survivedfallfromworldheight",
    "sneakclosetosculksensor",
    "itspreads",
    "birthdaysong",
    "withourpowerscombined",
    "plantingthepast",
    "carefulrestoration",
    "revaulting",
    "crafterscraftingcrafters",
    "whoneedsrockets",
    "overoverkill",
    "hearttransplanter",
    "stayhydrated",
    "mobkabob",
    "adventuringtime",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<v924::MinecraftEventing::AchievementIds>{"MinecraftEventing::AchievementIds"};

template <>
inline constexpr std::array<v1001::MinecraftEventing::InteractionType, 17> values_v<v1001::MinecraftEventing::InteractionType>{{
    v1001::MinecraftEventing::InteractionType::Breeding,
    v1001::MinecraftEventing::InteractionType::Taming,
    v1001::MinecraftEventing::InteractionType::Curing,
    v1001::MinecraftEventing::InteractionType::Crafted,
    v1001::MinecraftEventing::InteractionType::Shearing,
    v1001::MinecraftEventing::InteractionType::Milking,
    v1001::MinecraftEventing::InteractionType::Trading,
    v1001::MinecraftEventing::InteractionType::Feeding,
    v1001::MinecraftEventing::InteractionType::Igniting,
    v1001::MinecraftEventing::InteractionType::Coloring,
    v1001::MinecraftEventing::InteractionType::Naming,
    v1001::MinecraftEventing::InteractionType::Leashing,
    v1001::MinecraftEventing::InteractionType::Unleashing,
    v1001::MinecraftEventing::InteractionType::PetSleep,
    v1001::MinecraftEventing::InteractionType::Trusting,
    v1001::MinecraftEventing::InteractionType::Commanding,
    v1001::MinecraftEventing::InteractionType::Equipping,
}};

template <>
inline constexpr std::array<std::string_view, 17> names_v<v1001::MinecraftEventing::InteractionType>{{
    "breeding",
    "taming",
    "curing",
    "crafted",
    "shearing",
    "milking",
    "trading",
    "feeding",
    "igniting",
    "coloring",
    "naming",
    "leashing",
    "unleashing",
    "petsleep",
    "trusting",
    "commanding",
    "equipping",
}};

template <>
inline constexpr std::string_view type_name_v<v1001::MinecraftEventing::InteractionType>{"MinecraftEventing::InteractionType"};

template <>
inline constexpr std::array<v1001::MinecraftEventing::AchievementIds, 74> values_v<v1001::MinecraftEventing::AchievementIds>{{
    v1001::MinecraftEventing::AchievementIds::ChestFullOfCobblestone,
    v1001::MinecraftEventing::AchievementIds::DiamondForYou,
    v1001::MinecraftEventing::AchievementIds::IronBelly,
    v1001::MinecraftEventing::AchievementIds::IronMan,
    v1001::MinecraftEventing::AchievementIds::OnARail,
    v1001::MinecraftEventing::AchievementIds::Overkill,
    v1001::MinecraftEventing::AchievementIds::ReturnToSender,
    v1001::MinecraftEventing::AchievementIds::SniperDuel,
    v1001::MinecraftEventing::AchievementIds::StayinFrosty,
    v1001::MinecraftEventing::AchievementIds::TakeInventory,
    v1001::MinecraftEventing::AchievementIds::MapRoom,
    v1001::MinecraftEventing::AchievementIds::FreightStation,
    v1001::MinecraftEventing::AchievementIds::SmeltEverything,
    v1001::MinecraftEventing::AchievementIds::TasteOfYourOwnMedicine,
    v1001::MinecraftEventing::AchievementIds::WhenPigsFly,
    v1001::MinecraftEventing::AchievementIds::Inception,
    v1001::MinecraftEventing::AchievementIds::ArtificialSelection,
    v1001::MinecraftEventing::AchievementIds::FreeDiver,
    v1001::MinecraftEventing::AchievementIds::SpawnTheWither,
    v1001::MinecraftEventing::AchievementIds::Beaconator,
    v1001::MinecraftEventing::AchievementIds::GreatView,
    v1001::MinecraftEventing::AchievementIds::SuperSonic,
    v1001::MinecraftEventing::AchievementIds::TheEndAgain,
    v1001::MinecraftEventing::AchievementIds::TreasureHunter,
    v1001::MinecraftEventing::AchievementIds::ShootingStar,
    v1001::MinecraftEventing::AchievementIds::FashionShow,
    v1001::MinecraftEventing::AchievementIds::SelfPublishedAuthor,
    v1001::MinecraftEventing::AchievementIds::AlternativeFuel,
    v1001::MinecraftEventing::AchievementIds::SleepWithTheFishes,
    v1001::MinecraftEventing::AchievementIds::Castaway,
    v1001::MinecraftEventing::AchievementIds::ImAMarineBiologist,
    v1001::MinecraftEventing::AchievementIds::SailThe7Seas,
    v1001::MinecraftEventing::AchievementIds::MeGold,
    v1001::MinecraftEventing::AchievementIds::Ahoy,
    v1001::MinecraftEventing::AchievementIds::Atlantis,
    v1001::MinecraftEventing::AchievementIds::OnePickleTwoPickleSeaPickleFour,
    v1001::MinecraftEventing::AchievementIds::DoaBarrelRoll,
    v1001::MinecraftEventing::AchievementIds::Moskstraumen,
    v1001::MinecraftEventing::AchievementIds::Echolocation,
    v1001::MinecraftEventing::AchievementIds::WhereHaveYouBeen,
    v1001::MinecraftEventing::AchievementIds::TopOfTheWorld,
    v1001::MinecraftEventing::AchievementIds::FruitOnTheLoom,
    v1001::MinecraftEventing::AchievementIds::SoundTheAlarm,
    v1001::MinecraftEventing::AchievementIds::BuyLowSellHigh,
    v1001::MinecraftEventing::AchievementIds::Disenchanted,
    v1001::MinecraftEventing::AchievementIds::TimeForStew,
    v1001::MinecraftEventing::AchievementIds::BeeOurGuest,
    v1001::MinecraftEventing::AchievementIds::TotalBeeLocation,
    v1001::MinecraftEventing::AchievementIds::StickySituation,
    v1001::MinecraftEventing::AchievementIds::CoverMeInDebris,
    v1001::MinecraftEventing::AchievementIds::FloatYourGoat,
    v1001::MinecraftEventing::AchievementIds::Friend,
    v1001::MinecraftEventing::AchievementIds::WaxOnWaxOff,
    v1001::MinecraftEventing::AchievementIds::StriderRiddenInLavaInOverworld,
    v1001::MinecraftEventing::AchievementIds::GoatHornAcquired,
    v1001::MinecraftEventing::AchievementIds::JukeboxUsedInMeadows,
    v1001::MinecraftEventing::AchievementIds::TradedAtWorldHeight,
    v1001::MinecraftEventing::AchievementIds::SurvivedFallFromWorldHeight,
    v1001::MinecraftEventing::AchievementIds::SneakCloseToSculkSensor,
    v1001::MinecraftEventing::AchievementIds::ItSpreads,
    v1001::MinecraftEventing::AchievementIds::BirthdaySong,
    v1001::MinecraftEventing::AchievementIds::WithOurPowersCombined,
    v1001::MinecraftEventing::AchievementIds::PlantingThePast,
    v1001::MinecraftEventing::AchievementIds::CarefulRestoration,
    v1001::MinecraftEventing::AchievementIds::Revaulting,
    v1001::MinecraftEventing::AchievementIds::CraftersCraftingCrafters,
    v1001::MinecraftEventing::AchievementIds::WhoNeedsRockets,
    v1001::MinecraftEventing::AchievementIds::OverOverkill,
    v1001::MinecraftEventing::AchievementIds::HeartTransplanter,
    v1001::MinecraftEventing::AchievementIds::StayHydrated,
    v1001::MinecraftEventing::AchievementIds::MobKabob,
    v1001::MinecraftEventing::AchievementIds::AdventuringTime,
    v1001::MinecraftEventing::AchievementIds::UhOh,
    v1001::MinecraftEventing::AchievementIds::Count,
}};

template <>
inline constexpr std::array<std::string_view, 74> names_v<v1001::MinecraftEventing::AchievementIds>{{
    "chestfullofcobblestone",
    "diamondforyou",
    "ironbelly",
    "ironman",
    "onarail",
    "overkill",
    "returntosender",
    "sniperduel",
    "stayinfrosty",
    "takeinventory",
    "maproom",
    "freightstation",
    "smelteverything",
    "tasteofyourownmedicine",
    "whenpigsfly",
    "inception",
    "artificialselection",
    "freediver",
    "spawnthewither",
    "beaconator",
    "greatview",
    "supersonic",
    "theendagain",
    "treasurehunter",
    "shootingstar",
    "fashionshow",
    "selfpublishedauthor",
    "alternativefuel",
    "sleepwiththefishes",
    "castaway",
    "imamarinebiologist",
    "sailthe7seas",
    "megold",
    "ahoy",
    "atlantis",
    "onepickletwopickleseapicklefour",
    "doabarrelroll",
    "moskstraumen",
    "echolocation",
    "wherehaveyoubeen",
    "topoftheworld",
    "fruitontheloom",
    "soundthealarm",
    "buylowsellhigh",
    "disenchanted",
    "timeforstew",
    "beeourguest",
    "totalbeelocation",
    "stickysituation",
    "covermeindebris",
    "floatyourgoat",
    "friend",
    "waxonwaxoff",
    "striderriddeninlavainoverworld",
    "goathornacquired",
    "jukeboxusedinmeadows",
    "tradedatworldheight",
    "survivedfallfromworldheight",
    "sneakclosetosculksensor",
    "itspreads",
    "birthdaysong",
    "withourpowerscombined",
    "plantingthepast",
    "carefulrestoration",
    "revaulting",
    "crafterscraftingcrafters",
    "whoneedsrockets",
    "overoverkill",
    "hearttransplanter",
    "stayhydrated",
    "mobkabob",
    "adventuringtime",
    "uhoh",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<v1001::MinecraftEventing::AchievementIds>{"MinecraftEventing::AchievementIds"};

template <>
inline constexpr std::array<v2168::MinecraftEventing::InteractionType, 17> values_v<v2168::MinecraftEventing::InteractionType>{{
    v2168::MinecraftEventing::InteractionType::Breeding,
    v2168::MinecraftEventing::InteractionType::Taming,
    v2168::MinecraftEventing::InteractionType::Curing,
    v2168::MinecraftEventing::InteractionType::Crafted,
    v2168::MinecraftEventing::InteractionType::Shearing,
    v2168::MinecraftEventing::InteractionType::Milking,
    v2168::MinecraftEventing::InteractionType::Trading,
    v2168::MinecraftEventing::InteractionType::Feeding,
    v2168::MinecraftEventing::InteractionType::Igniting,
    v2168::MinecraftEventing::InteractionType::Coloring,
    v2168::MinecraftEventing::InteractionType::Naming,
    v2168::MinecraftEventing::InteractionType::Leashing,
    v2168::MinecraftEventing::InteractionType::Unleashing,
    v2168::MinecraftEventing::InteractionType::PetSleep,
    v2168::MinecraftEventing::InteractionType::Trusting,
    v2168::MinecraftEventing::InteractionType::Commanding,
    v2168::MinecraftEventing::InteractionType::Equipping,
}};

template <>
inline constexpr std::array<std::string_view, 17> names_v<v2168::MinecraftEventing::InteractionType>{{
    "breeding",
    "taming",
    "curing",
    "crafted",
    "shearing",
    "milking",
    "trading",
    "feeding",
    "igniting",
    "coloring",
    "naming",
    "leashing",
    "unleashing",
    "petsleep",
    "trusting",
    "commanding",
    "equipping",
}};

template <>
inline constexpr std::string_view type_name_v<v2168::MinecraftEventing::InteractionType>{"MinecraftEventing::InteractionType"};

template <>
inline constexpr std::array<v2168::MinecraftEventing::AchievementIds, 83> values_v<v2168::MinecraftEventing::AchievementIds>{{
    v2168::MinecraftEventing::AchievementIds::ChestFullOfCobblestone,
    v2168::MinecraftEventing::AchievementIds::DiamondForYou,
    v2168::MinecraftEventing::AchievementIds::IronBelly,
    v2168::MinecraftEventing::AchievementIds::IronMan,
    v2168::MinecraftEventing::AchievementIds::OnARail,
    v2168::MinecraftEventing::AchievementIds::Overkill,
    v2168::MinecraftEventing::AchievementIds::ReturnToSender,
    v2168::MinecraftEventing::AchievementIds::SniperDuel,
    v2168::MinecraftEventing::AchievementIds::StayinFrosty,
    v2168::MinecraftEventing::AchievementIds::TakeInventory,
    v2168::MinecraftEventing::AchievementIds::MapRoom,
    v2168::MinecraftEventing::AchievementIds::FreightStation,
    v2168::MinecraftEventing::AchievementIds::SmeltEverything,
    v2168::MinecraftEventing::AchievementIds::TasteOfYourOwnMedicine,
    v2168::MinecraftEventing::AchievementIds::WhenPigsFly,
    v2168::MinecraftEventing::AchievementIds::Inception,
    v2168::MinecraftEventing::AchievementIds::ArtificialSelection,
    v2168::MinecraftEventing::AchievementIds::FreeDiver,
    v2168::MinecraftEventing::AchievementIds::SpawnTheWither,
    v2168::MinecraftEventing::AchievementIds::Beaconator,
    v2168::MinecraftEventing::AchievementIds::GreatView,
    v2168::MinecraftEventing::AchievementIds::SuperSonic,
    v2168::MinecraftEventing::AchievementIds::TheEndAgain,
    v2168::MinecraftEventing::AchievementIds::TreasureHunter,
    v2168::MinecraftEventing::AchievementIds::ShootingStar,
    v2168::MinecraftEventing::AchievementIds::FashionShow,
    v2168::MinecraftEventing::AchievementIds::SelfPublishedAuthor,
    v2168::MinecraftEventing::AchievementIds::AlternativeFuel,
    v2168::MinecraftEventing::AchievementIds::SleepWithTheFishes,
    v2168::MinecraftEventing::AchievementIds::Castaway,
    v2168::MinecraftEventing::AchievementIds::ImAMarineBiologist,
    v2168::MinecraftEventing::AchievementIds::SailThe7Seas,
    v2168::MinecraftEventing::AchievementIds::MeGold,
    v2168::MinecraftEventing::AchievementIds::Ahoy,
    v2168::MinecraftEventing::AchievementIds::Atlantis,
    v2168::MinecraftEventing::AchievementIds::OnePickleTwoPickleSeaPickleFour,
    v2168::MinecraftEventing::AchievementIds::DoaBarrelRoll,
    v2168::MinecraftEventing::AchievementIds::Moskstraumen,
    v2168::MinecraftEventing::AchievementIds::Echolocation,
    v2168::MinecraftEventing::AchievementIds::WhereHaveYouBeen,
    v2168::MinecraftEventing::AchievementIds::TopOfTheWorld,
    v2168::MinecraftEventing::AchievementIds::FruitOnTheLoom,
    v2168::MinecraftEventing::AchievementIds::SoundTheAlarm,
    v2168::MinecraftEventing::AchievementIds::BuyLowSellHigh,
    v2168::MinecraftEventing::AchievementIds::Disenchanted,
    v2168::MinecraftEventing::AchievementIds::TimeForStew,
    v2168::MinecraftEventing::AchievementIds::BeeOurGuest,
    v2168::MinecraftEventing::AchievementIds::TotalBeeLocation,
    v2168::MinecraftEventing::AchievementIds::StickySituation,
    v2168::MinecraftEventing::AchievementIds::CoverMeInDebris,
    v2168::MinecraftEventing::AchievementIds::FloatYourGoat,
    v2168::MinecraftEventing::AchievementIds::Friend,
    v2168::MinecraftEventing::AchievementIds::WaxOnWaxOff,
    v2168::MinecraftEventing::AchievementIds::StriderRiddenInLavaInOverworld,
    v2168::MinecraftEventing::AchievementIds::GoatHornAcquired,
    v2168::MinecraftEventing::AchievementIds::JukeboxUsedInMeadows,
    v2168::MinecraftEventing::AchievementIds::TradedAtWorldHeight,
    v2168::MinecraftEventing::AchievementIds::SurvivedFallFromWorldHeight,
    v2168::MinecraftEventing::AchievementIds::SneakCloseToSculkSensor,
    v2168::MinecraftEventing::AchievementIds::ItSpreads,
    v2168::MinecraftEventing::AchievementIds::BirthdaySong,
    v2168::MinecraftEventing::AchievementIds::WithOurPowersCombined,
    v2168::MinecraftEventing::AchievementIds::PlantingThePast,
    v2168::MinecraftEventing::AchievementIds::CarefulRestoration,
    v2168::MinecraftEventing::AchievementIds::Revaulting,
    v2168::MinecraftEventing::AchievementIds::CraftersCraftingCrafters,
    v2168::MinecraftEventing::AchievementIds::WhoNeedsRockets,
    v2168::MinecraftEventing::AchievementIds::OverOverkill,
    v2168::MinecraftEventing::AchievementIds::HeartTransplanter,
    v2168::MinecraftEventing::AchievementIds::StayHydrated,
    v2168::MinecraftEventing::AchievementIds::MobKabob,
    v2168::MinecraftEventing::AchievementIds::AdventuringTime,
    v2168::MinecraftEventing::AchievementIds::UhOh,
    v2168::MinecraftEventing::AchievementIds::GettingWood,
    v2168::MinecraftEventing::AchievementIds::BenchMaking,
    v2168::MinecraftEventing::AchievementIds::TimeToMine,
    v2168::MinecraftEventing::AchievementIds::HotTopic,
    v2168::MinecraftEventing::AchievementIds::AcquireHardware,
    v2168::MinecraftEventing::AchievementIds::GettingAnUpgrade,
    v2168::MinecraftEventing::AchievementIds::MonsterHunter,
    v2168::MinecraftEventing::AchievementIds::Diamonds,
    v2168::MinecraftEventing::AchievementIds::PlethoraOfCats,
    v2168::MinecraftEventing::AchievementIds::Count,
}};

template <>
inline constexpr std::array<std::string_view, 83> names_v<v2168::MinecraftEventing::AchievementIds>{{
    "chestfullofcobblestone",
    "diamondforyou",
    "ironbelly",
    "ironman",
    "onarail",
    "overkill",
    "returntosender",
    "sniperduel",
    "stayinfrosty",
    "takeinventory",
    "maproom",
    "freightstation",
    "smelteverything",
    "tasteofyourownmedicine",
    "whenpigsfly",
    "inception",
    "artificialselection",
    "freediver",
    "spawnthewither",
    "beaconator",
    "greatview",
    "supersonic",
    "theendagain",
    "treasurehunter",
    "shootingstar",
    "fashionshow",
    "selfpublishedauthor",
    "alternativefuel",
    "sleepwiththefishes",
    "castaway",
    "imamarinebiologist",
    "sailthe7seas",
    "megold",
    "ahoy",
    "atlantis",
    "onepickletwopickleseapicklefour",
    "doabarrelroll",
    "moskstraumen",
    "echolocation",
    "wherehaveyoubeen",
    "topoftheworld",
    "fruitontheloom",
    "soundthealarm",
    "buylowsellhigh",
    "disenchanted",
    "timeforstew",
    "beeourguest",
    "totalbeelocation",
    "stickysituation",
    "covermeindebris",
    "floatyourgoat",
    "friend",
    "waxonwaxoff",
    "striderriddeninlavainoverworld",
    "goathornacquired",
    "jukeboxusedinmeadows",
    "tradedatworldheight",
    "survivedfallfromworldheight",
    "sneakclosetosculksensor",
    "itspreads",
    "birthdaysong",
    "withourpowerscombined",
    "plantingthepast",
    "carefulrestoration",
    "revaulting",
    "crafterscraftingcrafters",
    "whoneedsrockets",
    "overoverkill",
    "hearttransplanter",
    "stayhydrated",
    "mobkabob",
    "adventuringtime",
    "uhoh",
    "gettingwood",
    "benchmaking",
    "timetomine",
    "hottopic",
    "acquirehardware",
    "gettinganupgrade",
    "monsterhunter",
    "diamonds",
    "plethoraofcats",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<v2168::MinecraftEventing::AchievementIds>{"MinecraftEventing::AchievementIds"};

template <>
inline constexpr std::array<v2225::MinecraftEventing::InteractionType, 17> values_v<v2225::MinecraftEventing::InteractionType>{{
    v2225::MinecraftEventing::InteractionType::Breeding,
    v2225::MinecraftEventing::InteractionType::Taming,
    v2225::MinecraftEventing::InteractionType::Curing,
    v2225::MinecraftEventing::InteractionType::Crafted,
    v2225::MinecraftEventing::InteractionType::Shearing,
    v2225::MinecraftEventing::InteractionType::Milking,
    v2225::MinecraftEventing::InteractionType::Trading,
    v2225::MinecraftEventing::InteractionType::Feeding,
    v2225::MinecraftEventing::InteractionType::Igniting,
    v2225::MinecraftEventing::InteractionType::Coloring,
    v2225::MinecraftEventing::InteractionType::Naming,
    v2225::MinecraftEventing::InteractionType::Leashing,
    v2225::MinecraftEventing::InteractionType::Unleashing,
    v2225::MinecraftEventing::InteractionType::PetSleep,
    v2225::MinecraftEventing::InteractionType::Trusting,
    v2225::MinecraftEventing::InteractionType::Commanding,
    v2225::MinecraftEventing::InteractionType::Equipping,
}};

template <>
inline constexpr std::array<std::string_view, 17> names_v<v2225::MinecraftEventing::InteractionType>{{
    "breeding",
    "taming",
    "curing",
    "crafted",
    "shearing",
    "milking",
    "trading",
    "feeding",
    "igniting",
    "coloring",
    "naming",
    "leashing",
    "unleashing",
    "petsleep",
    "trusting",
    "commanding",
    "equipping",
}};

template <>
inline constexpr std::string_view type_name_v<v2225::MinecraftEventing::InteractionType>{"MinecraftEventing::InteractionType"};

template <>
inline constexpr std::array<v2225::MinecraftEventing::AchievementIds, 84> values_v<v2225::MinecraftEventing::AchievementIds>{{
    v2225::MinecraftEventing::AchievementIds::ChestFullOfCobblestone,
    v2225::MinecraftEventing::AchievementIds::DiamondForYou,
    v2225::MinecraftEventing::AchievementIds::IronBelly,
    v2225::MinecraftEventing::AchievementIds::IronMan,
    v2225::MinecraftEventing::AchievementIds::OnARail,
    v2225::MinecraftEventing::AchievementIds::Overkill,
    v2225::MinecraftEventing::AchievementIds::ReturnToSender,
    v2225::MinecraftEventing::AchievementIds::SniperDuel,
    v2225::MinecraftEventing::AchievementIds::StayinFrosty,
    v2225::MinecraftEventing::AchievementIds::TakeInventory,
    v2225::MinecraftEventing::AchievementIds::MapRoom,
    v2225::MinecraftEventing::AchievementIds::FreightStation,
    v2225::MinecraftEventing::AchievementIds::SmeltEverything,
    v2225::MinecraftEventing::AchievementIds::TasteOfYourOwnMedicine,
    v2225::MinecraftEventing::AchievementIds::WhenPigsFly,
    v2225::MinecraftEventing::AchievementIds::Inception,
    v2225::MinecraftEventing::AchievementIds::ArtificialSelection,
    v2225::MinecraftEventing::AchievementIds::FreeDiver,
    v2225::MinecraftEventing::AchievementIds::SpawnTheWither,
    v2225::MinecraftEventing::AchievementIds::Beaconator,
    v2225::MinecraftEventing::AchievementIds::GreatView,
    v2225::MinecraftEventing::AchievementIds::SuperSonic,
    v2225::MinecraftEventing::AchievementIds::TheEndAgain,
    v2225::MinecraftEventing::AchievementIds::TreasureHunter,
    v2225::MinecraftEventing::AchievementIds::ShootingStar,
    v2225::MinecraftEventing::AchievementIds::FashionShow,
    v2225::MinecraftEventing::AchievementIds::SelfPublishedAuthor,
    v2225::MinecraftEventing::AchievementIds::AlternativeFuel,
    v2225::MinecraftEventing::AchievementIds::SleepWithTheFishes,
    v2225::MinecraftEventing::AchievementIds::Castaway,
    v2225::MinecraftEventing::AchievementIds::ImAMarineBiologist,
    v2225::MinecraftEventing::AchievementIds::SailThe7Seas,
    v2225::MinecraftEventing::AchievementIds::MeGold,
    v2225::MinecraftEventing::AchievementIds::Ahoy,
    v2225::MinecraftEventing::AchievementIds::Atlantis,
    v2225::MinecraftEventing::AchievementIds::OnePickleTwoPickleSeaPickleFour,
    v2225::MinecraftEventing::AchievementIds::DoaBarrelRoll,
    v2225::MinecraftEventing::AchievementIds::Moskstraumen,
    v2225::MinecraftEventing::AchievementIds::Echolocation,
    v2225::MinecraftEventing::AchievementIds::WhereHaveYouBeen,
    v2225::MinecraftEventing::AchievementIds::TopOfTheWorld,
    v2225::MinecraftEventing::AchievementIds::FruitOnTheLoom,
    v2225::MinecraftEventing::AchievementIds::SoundTheAlarm,
    v2225::MinecraftEventing::AchievementIds::BuyLowSellHigh,
    v2225::MinecraftEventing::AchievementIds::Disenchanted,
    v2225::MinecraftEventing::AchievementIds::TimeForStew,
    v2225::MinecraftEventing::AchievementIds::BeeOurGuest,
    v2225::MinecraftEventing::AchievementIds::TotalBeeLocation,
    v2225::MinecraftEventing::AchievementIds::StickySituation,
    v2225::MinecraftEventing::AchievementIds::CoverMeInDebris,
    v2225::MinecraftEventing::AchievementIds::FloatYourGoat,
    v2225::MinecraftEventing::AchievementIds::Friend,
    v2225::MinecraftEventing::AchievementIds::WaxOnWaxOff,
    v2225::MinecraftEventing::AchievementIds::StriderRiddenInLavaInOverworld,
    v2225::MinecraftEventing::AchievementIds::GoatHornAcquired,
    v2225::MinecraftEventing::AchievementIds::JukeboxUsedInMeadows,
    v2225::MinecraftEventing::AchievementIds::TradedAtWorldHeight,
    v2225::MinecraftEventing::AchievementIds::SurvivedFallFromWorldHeight,
    v2225::MinecraftEventing::AchievementIds::SneakCloseToSculkSensor,
    v2225::MinecraftEventing::AchievementIds::ItSpreads,
    v2225::MinecraftEventing::AchievementIds::BirthdaySong,
    v2225::MinecraftEventing::AchievementIds::WithOurPowersCombined,
    v2225::MinecraftEventing::AchievementIds::PlantingThePast,
    v2225::MinecraftEventing::AchievementIds::CarefulRestoration,
    v2225::MinecraftEventing::AchievementIds::Revaulting,
    v2225::MinecraftEventing::AchievementIds::CraftersCraftingCrafters,
    v2225::MinecraftEventing::AchievementIds::WhoNeedsRockets,
    v2225::MinecraftEventing::AchievementIds::OverOverkill,
    v2225::MinecraftEventing::AchievementIds::HeartTransplanter,
    v2225::MinecraftEventing::AchievementIds::StayHydrated,
    v2225::MinecraftEventing::AchievementIds::MobKabob,
    v2225::MinecraftEventing::AchievementIds::AdventuringTime,
    v2225::MinecraftEventing::AchievementIds::UhOh,
    v2225::MinecraftEventing::AchievementIds::GettingWood,
    v2225::MinecraftEventing::AchievementIds::BenchMaking,
    v2225::MinecraftEventing::AchievementIds::TimeToMine,
    v2225::MinecraftEventing::AchievementIds::HotTopic,
    v2225::MinecraftEventing::AchievementIds::AcquireHardware,
    v2225::MinecraftEventing::AchievementIds::GettingAnUpgrade,
    v2225::MinecraftEventing::AchievementIds::MonsterHunter,
    v2225::MinecraftEventing::AchievementIds::Diamonds,
    v2225::MinecraftEventing::AchievementIds::PlethoraOfCats,
    v2225::MinecraftEventing::AchievementIds::WhatGoesAroundComesAround,
    v2225::MinecraftEventing::AchievementIds::Count,
}};

template <>
inline constexpr std::array<std::string_view, 84> names_v<v2225::MinecraftEventing::AchievementIds>{{
    "chestfullofcobblestone",
    "diamondforyou",
    "ironbelly",
    "ironman",
    "onarail",
    "overkill",
    "returntosender",
    "sniperduel",
    "stayinfrosty",
    "takeinventory",
    "maproom",
    "freightstation",
    "smelteverything",
    "tasteofyourownmedicine",
    "whenpigsfly",
    "inception",
    "artificialselection",
    "freediver",
    "spawnthewither",
    "beaconator",
    "greatview",
    "supersonic",
    "theendagain",
    "treasurehunter",
    "shootingstar",
    "fashionshow",
    "selfpublishedauthor",
    "alternativefuel",
    "sleepwiththefishes",
    "castaway",
    "imamarinebiologist",
    "sailthe7seas",
    "megold",
    "ahoy",
    "atlantis",
    "onepickletwopickleseapicklefour",
    "doabarrelroll",
    "moskstraumen",
    "echolocation",
    "wherehaveyoubeen",
    "topoftheworld",
    "fruitontheloom",
    "soundthealarm",
    "buylowsellhigh",
    "disenchanted",
    "timeforstew",
    "beeourguest",
    "totalbeelocation",
    "stickysituation",
    "covermeindebris",
    "floatyourgoat",
    "friend",
    "waxonwaxoff",
    "striderriddeninlavainoverworld",
    "goathornacquired",
    "jukeboxusedinmeadows",
    "tradedatworldheight",
    "survivedfallfromworldheight",
    "sneakclosetosculksensor",
    "itspreads",
    "birthdaysong",
    "withourpowerscombined",
    "plantingthepast",
    "carefulrestoration",
    "revaulting",
    "crafterscraftingcrafters",
    "whoneedsrockets",
    "overoverkill",
    "hearttransplanter",
    "stayhydrated",
    "mobkabob",
    "adventuringtime",
    "uhoh",
    "gettingwood",
    "benchmaking",
    "timetomine",
    "hottopic",
    "acquirehardware",
    "gettinganupgrade",
    "monsterhunter",
    "diamonds",
    "plethoraofcats",
    "whatgoesaroundcomesaround",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<v2225::MinecraftEventing::AchievementIds>{"MinecraftEventing::AchievementIds"};

template <>
inline constexpr std::array<base::LegacyTelemetryEventPacket::Type, 32> values_v<base::LegacyTelemetryEventPacket::Type>{{
    base::LegacyTelemetryEventPacket::Type::Achievement,
    base::LegacyTelemetryEventPacket::Type::Interaction,
    base::LegacyTelemetryEventPacket::Type::PortalCreated,
    base::LegacyTelemetryEventPacket::Type::PortalUsed,
    base::LegacyTelemetryEventPacket::Type::MobKilled,
    base::LegacyTelemetryEventPacket::Type::CauldronUsed,
    base::LegacyTelemetryEventPacket::Type::PlayerDied,
    base::LegacyTelemetryEventPacket::Type::BossKilled,
    base::LegacyTelemetryEventPacket::Type::AgentCommandObsolete,
    base::LegacyTelemetryEventPacket::Type::AgentCreated,
    base::LegacyTelemetryEventPacket::Type::PatternRemovedObsolete,
    base::LegacyTelemetryEventPacket::Type::SlashCommand,
    base::LegacyTelemetryEventPacket::Type::FishBucketedObsolete,
    base::LegacyTelemetryEventPacket::Type::MobBorn,
    base::LegacyTelemetryEventPacket::Type::PetDiedObsolete,
    base::LegacyTelemetryEventPacket::Type::POICauldronUsed,
    base::LegacyTelemetryEventPacket::Type::ComposterUsed,
    base::LegacyTelemetryEventPacket::Type::BellUsed,
    base::LegacyTelemetryEventPacket::Type::ActorDefinition,
    base::LegacyTelemetryEventPacket::Type::RaidUpdate,
    base::LegacyTelemetryEventPacket::Type::PlayerMovementAnomalyObsolete,
    base::LegacyTelemetryEventPacket::Type::PlayerMovementCorrectedObsolete,
    base::LegacyTelemetryEventPacket::Type::HoneyHarvested,
    base::LegacyTelemetryEventPacket::Type::TargetBlockHit,
    base::LegacyTelemetryEventPacket::Type::PiglinBarter,
    base::LegacyTelemetryEventPacket::Type::PlayerWaxedOrUnwaxedCopper,
    base::LegacyTelemetryEventPacket::Type::CodeBuilderRuntimeAction,
    base::LegacyTelemetryEventPacket::Type::CodeBuilderScoreboard,
    base::LegacyTelemetryEventPacket::Type::StriderRiddenInLavaInOverworld,
    base::LegacyTelemetryEventPacket::Type::SneakCloseToSculkSensor,
    base::LegacyTelemetryEventPacket::Type::CarefulRestoration,
    base::LegacyTelemetryEventPacket::Type::ItemUsed,
}};

template <>
inline constexpr std::array<std::string_view, 32> names_v<base::LegacyTelemetryEventPacket::Type>{{
    "achievement",
    "interaction",
    "portalcreated",
    "portalused",
    "mobkilled",
    "cauldronused",
    "playerdied",
    "bosskilled",
    "agentcommandobsolete",
    "agentcreated",
    "patternremovedobsolete",
    "slashcommand",
    "fishbucketedobsolete",
    "mobborn",
    "petdiedobsolete",
    "poicauldronused",
    "composterused",
    "bellused",
    "actordefinition",
    "raidupdate",
    "playermovementanomalyobsolete",
    "playermovementcorrectedobsolete",
    "honeyharvested",
    "targetblockhit",
    "piglinbarter",
    "playerwaxedorunwaxedcopper",
    "codebuilderruntimeaction",
    "codebuilderscoreboard",
    "striderriddeninlavainoverworld",
    "sneakclosetosculksensor",
    "carefulrestoration",
    "itemused",
}};

template <>
inline constexpr std::string_view type_name_v<base::LegacyTelemetryEventPacket::Type>{"LegacyTelemetryEventPacket::Type"};

}  // namespace detail

namespace detail {

template <>
inline constexpr bool is_reflected_struct_v<base::MinecraftEventing> = true;

template <>
inline constexpr std::string_view struct_name_v<base::MinecraftEventing>{"MinecraftEventing"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<base::MinecraftEventing>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<v766::MinecraftEventing> = true;

template <>
inline constexpr std::string_view struct_name_v<v766::MinecraftEventing>{"MinecraftEventing"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<v766::MinecraftEventing>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<v776::MinecraftEventing> = true;

template <>
inline constexpr std::string_view struct_name_v<v776::MinecraftEventing>{"MinecraftEventing"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<v776::MinecraftEventing>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<v818::MinecraftEventing> = true;

template <>
inline constexpr std::string_view struct_name_v<v818::MinecraftEventing>{"MinecraftEventing"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<v818::MinecraftEventing>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<v898::MinecraftEventing> = true;

template <>
inline constexpr std::string_view struct_name_v<v898::MinecraftEventing>{"MinecraftEventing"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<v898::MinecraftEventing>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<v924::MinecraftEventing> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::MinecraftEventing>{"MinecraftEventing"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<v924::MinecraftEventing>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<v1001::MinecraftEventing> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::MinecraftEventing>{"MinecraftEventing"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<v1001::MinecraftEventing>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<v2168::MinecraftEventing> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::MinecraftEventing>{"MinecraftEventing"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<v2168::MinecraftEventing>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<v2225::MinecraftEventing> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::MinecraftEventing>{"MinecraftEventing"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<v2225::MinecraftEventing>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<base::LegacyTelemetryEventPacket::Achievement> = true;

template <>
inline constexpr std::string_view struct_name_v<base::LegacyTelemetryEventPacket::Achievement>{"LegacyTelemetryEventPacket::Achievement"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::LegacyTelemetryEventPacket::Achievement>{{
    "achievement_id",
}};

template <>
struct field_accessor<base::LegacyTelemetryEventPacket::Achievement> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.achievement_id;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::LegacyTelemetryEventPacket::Interaction> = true;

template <>
inline constexpr std::string_view struct_name_v<base::LegacyTelemetryEventPacket::Interaction>{"LegacyTelemetryEventPacket::Interaction"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<base::LegacyTelemetryEventPacket::Interaction>{{
    "interacted_entity_id",
    "interaction_type",
    "interacted_entity_type",
    "interacted_entity_variant",
    "interacted_entity_color",
}};

template <>
struct field_accessor<base::LegacyTelemetryEventPacket::Interaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.interacted_entity_id;
        }
        else if constexpr (I == 1) {
            return value.interaction_type;
        }
        else if constexpr (I == 2) {
            return value.interacted_entity_type;
        }
        else if constexpr (I == 3) {
            return value.interacted_entity_variant;
        }
        else {
            return value.interacted_entity_color;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::LegacyTelemetryEventPacket::PortalCreated> = true;

template <>
inline constexpr std::string_view struct_name_v<base::LegacyTelemetryEventPacket::PortalCreated>{"LegacyTelemetryEventPacket::PortalCreated"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::LegacyTelemetryEventPacket::PortalCreated>{{
    "built_in_dimension",
}};

template <>
struct field_accessor<base::LegacyTelemetryEventPacket::PortalCreated> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.built_in_dimension;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::LegacyTelemetryEventPacket::PortalUsed> = true;

template <>
inline constexpr std::string_view struct_name_v<base::LegacyTelemetryEventPacket::PortalUsed>{"LegacyTelemetryEventPacket::PortalUsed"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<base::LegacyTelemetryEventPacket::PortalUsed>{{
    "from_dimension",
    "to_dimension",
}};

template <>
struct field_accessor<base::LegacyTelemetryEventPacket::PortalUsed> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.from_dimension;
        }
        else {
            return value.to_dimension;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::LegacyTelemetryEventPacket::MobKilled> = true;

template <>
inline constexpr std::string_view struct_name_v<base::LegacyTelemetryEventPacket::MobKilled>{"LegacyTelemetryEventPacket::MobKilled"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<base::LegacyTelemetryEventPacket::MobKilled>{{
    "killer_entity_id",
    "killed_mob_id",
    "damage_child_type",
    "damage_source",
    "trader_tier",
    "trader_name",
}};

template <>
struct field_accessor<base::LegacyTelemetryEventPacket::MobKilled> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.killer_entity_id;
        }
        else if constexpr (I == 1) {
            return value.killed_mob_id;
        }
        else if constexpr (I == 2) {
            return value.damage_child_type;
        }
        else if constexpr (I == 3) {
            return value.damage_source;
        }
        else if constexpr (I == 4) {
            return value.trader_tier;
        }
        else {
            return value.trader_name;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::LegacyTelemetryEventPacket::CauldronUsed> = true;

template <>
inline constexpr std::string_view struct_name_v<base::LegacyTelemetryEventPacket::CauldronUsed>{"LegacyTelemetryEventPacket::CauldronUsed"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<base::LegacyTelemetryEventPacket::CauldronUsed>{{
    "contents_color",
    "contents_type",
    "fill_level",
}};

template <>
struct field_accessor<base::LegacyTelemetryEventPacket::CauldronUsed> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.contents_color;
        }
        else if constexpr (I == 1) {
            return value.contents_type;
        }
        else {
            return value.fill_level;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::LegacyTelemetryEventPacket::PlayerDied> = true;

template <>
inline constexpr std::string_view struct_name_v<base::LegacyTelemetryEventPacket::PlayerDied>{"LegacyTelemetryEventPacket::PlayerDied"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<base::LegacyTelemetryEventPacket::PlayerDied>{{
    "killer_id",
    "killer_variant",
    "damage_source",
    "in_raid",
}};

template <>
struct field_accessor<base::LegacyTelemetryEventPacket::PlayerDied> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.killer_id;
        }
        else if constexpr (I == 1) {
            return value.killer_variant;
        }
        else if constexpr (I == 2) {
            return value.damage_source;
        }
        else {
            return value.in_raid;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::LegacyTelemetryEventPacket::BossKilled> = true;

template <>
inline constexpr std::string_view struct_name_v<base::LegacyTelemetryEventPacket::BossKilled>{"LegacyTelemetryEventPacket::BossKilled"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<base::LegacyTelemetryEventPacket::BossKilled>{{
    "boss_unique_id",
    "party_size",
    "boss_type",
}};

template <>
struct field_accessor<base::LegacyTelemetryEventPacket::BossKilled> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.boss_unique_id;
        }
        else if constexpr (I == 1) {
            return value.party_size;
        }
        else {
            return value.boss_type;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::LegacyTelemetryEventPacket::SlashCommand> = true;

template <>
inline constexpr std::string_view struct_name_v<base::LegacyTelemetryEventPacket::SlashCommand>{"LegacyTelemetryEventPacket::SlashCommand"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<base::LegacyTelemetryEventPacket::SlashCommand>{{
    "success_count",
    "error_count",
    "command_name",
    "error_list",
}};

template <>
struct field_accessor<base::LegacyTelemetryEventPacket::SlashCommand> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.success_count;
        }
        else if constexpr (I == 1) {
            return value.error_count;
        }
        else if constexpr (I == 2) {
            return value.command_name;
        }
        else {
            return value.error_list;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::LegacyTelemetryEventPacket::MobBorn> = true;

template <>
inline constexpr std::string_view struct_name_v<base::LegacyTelemetryEventPacket::MobBorn>{"LegacyTelemetryEventPacket::MobBorn"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<base::LegacyTelemetryEventPacket::MobBorn>{{
    "baby_type",
    "baby_variant",
    "baby_color",
}};

template <>
struct field_accessor<base::LegacyTelemetryEventPacket::MobBorn> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.baby_type;
        }
        else if constexpr (I == 1) {
            return value.baby_variant;
        }
        else {
            return value.baby_color;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::LegacyTelemetryEventPacket::POICauldronUsed> = true;

template <>
inline constexpr std::string_view struct_name_v<base::LegacyTelemetryEventPacket::POICauldronUsed>{"LegacyTelemetryEventPacket::POICauldronUsed"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<base::LegacyTelemetryEventPacket::POICauldronUsed>{{
    "interaction_type",
    "item_id",
}};

template <>
struct field_accessor<base::LegacyTelemetryEventPacket::POICauldronUsed> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.interaction_type;
        }
        else {
            return value.item_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::LegacyTelemetryEventPacket::ComposterUsed> = true;

template <>
inline constexpr std::string_view struct_name_v<base::LegacyTelemetryEventPacket::ComposterUsed>{"LegacyTelemetryEventPacket::ComposterUsed"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<base::LegacyTelemetryEventPacket::ComposterUsed>{{
    "interaction_type",
    "item_id",
}};

template <>
struct field_accessor<base::LegacyTelemetryEventPacket::ComposterUsed> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.interaction_type;
        }
        else {
            return value.item_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::LegacyTelemetryEventPacket::BellUsed> = true;

template <>
inline constexpr std::string_view struct_name_v<base::LegacyTelemetryEventPacket::BellUsed>{"LegacyTelemetryEventPacket::BellUsed"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::LegacyTelemetryEventPacket::BellUsed>{{
    "item_id",
}};

template <>
struct field_accessor<base::LegacyTelemetryEventPacket::BellUsed> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.item_id;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::LegacyTelemetryEventPacket::ActorDefinition> = true;

template <>
inline constexpr std::string_view struct_name_v<base::LegacyTelemetryEventPacket::ActorDefinition>{"LegacyTelemetryEventPacket::ActorDefinition"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::LegacyTelemetryEventPacket::ActorDefinition>{{
    "event_name",
}};

template <>
struct field_accessor<base::LegacyTelemetryEventPacket::ActorDefinition> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.event_name;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::LegacyTelemetryEventPacket::RaidUpdate> = true;

template <>
inline constexpr std::string_view struct_name_v<base::LegacyTelemetryEventPacket::RaidUpdate>{"LegacyTelemetryEventPacket::RaidUpdate"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<base::LegacyTelemetryEventPacket::RaidUpdate>{{
    "current_wave",
    "total_waves",
    "success",
}};

template <>
struct field_accessor<base::LegacyTelemetryEventPacket::RaidUpdate> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.current_wave;
        }
        else if constexpr (I == 1) {
            return value.total_waves;
        }
        else {
            return value.success;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::LegacyTelemetryEventPacket::TargetBlockHit> = true;

template <>
inline constexpr std::string_view struct_name_v<base::LegacyTelemetryEventPacket::TargetBlockHit>{"LegacyTelemetryEventPacket::TargetBlockHit"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::LegacyTelemetryEventPacket::TargetBlockHit>{{
    "redstone_level",
}};

template <>
struct field_accessor<base::LegacyTelemetryEventPacket::TargetBlockHit> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.redstone_level;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::LegacyTelemetryEventPacket::PiglinBarter> = true;

template <>
inline constexpr std::string_view struct_name_v<base::LegacyTelemetryEventPacket::PiglinBarter>{"LegacyTelemetryEventPacket::PiglinBarter"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<base::LegacyTelemetryEventPacket::PiglinBarter>{{
    "item_id",
    "was_targeting_bartering_player",
}};

template <>
struct field_accessor<base::LegacyTelemetryEventPacket::PiglinBarter> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.item_id;
        }
        else {
            return value.was_targeting_bartering_player;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper> = true;

template <>
inline constexpr std::string_view struct_name_v<base::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper>{"LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper>{{
    "block_id",
}};

template <>
struct field_accessor<base::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.block_id;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction> = true;

template <>
inline constexpr std::string_view struct_name_v<base::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction>{"LegacyTelemetryEventPacket::CodeBuilderRuntimeAction"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction>{{
    "runtime_action",
}};

template <>
struct field_accessor<base::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.runtime_action;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::LegacyTelemetryEventPacket::CodeBuilderScoreboard> = true;

template <>
inline constexpr std::string_view struct_name_v<base::LegacyTelemetryEventPacket::CodeBuilderScoreboard>{"LegacyTelemetryEventPacket::CodeBuilderScoreboard"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<base::LegacyTelemetryEventPacket::CodeBuilderScoreboard>{{
    "objective_name",
    "score",
}};

template <>
struct field_accessor<base::LegacyTelemetryEventPacket::CodeBuilderScoreboard> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.objective_name;
        }
        else {
            return value.score;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::LegacyTelemetryEventPacket::ItemUsed> = true;

template <>
inline constexpr std::string_view struct_name_v<base::LegacyTelemetryEventPacket::ItemUsed>{"LegacyTelemetryEventPacket::ItemUsed"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<base::LegacyTelemetryEventPacket::ItemUsed>{{
    "item_id",
    "item_aux",
    "use_method",
    "count",
}};

template <>
struct field_accessor<base::LegacyTelemetryEventPacket::ItemUsed> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.item_id;
        }
        else if constexpr (I == 1) {
            return value.item_aux;
        }
        else if constexpr (I == 2) {
            return value.use_method;
        }
        else {
            return value.count;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::LegacyTelemetryEventPacket::Empty> = true;

template <>
inline constexpr std::string_view struct_name_v<base::LegacyTelemetryEventPacket::Empty>{"LegacyTelemetryEventPacket::Empty"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<base::LegacyTelemetryEventPacket::Empty>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<v766::LegacyTelemetryEventPacket::Achievement> = true;

template <>
inline constexpr std::string_view struct_name_v<v766::LegacyTelemetryEventPacket::Achievement>{"LegacyTelemetryEventPacket::Achievement"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v766::LegacyTelemetryEventPacket::Achievement>{{
    "achievement_id",
}};

template <>
struct field_accessor<v766::LegacyTelemetryEventPacket::Achievement> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.achievement_id;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v766::LegacyTelemetryEventPacket::Interaction> = true;

template <>
inline constexpr std::string_view struct_name_v<v766::LegacyTelemetryEventPacket::Interaction>{"LegacyTelemetryEventPacket::Interaction"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v766::LegacyTelemetryEventPacket::Interaction>{{
    "interacted_entity_id",
    "interaction_type",
    "interacted_entity_type",
    "interacted_entity_variant",
    "interacted_entity_color",
}};

template <>
struct field_accessor<v766::LegacyTelemetryEventPacket::Interaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.interacted_entity_id;
        }
        else if constexpr (I == 1) {
            return value.interaction_type;
        }
        else if constexpr (I == 2) {
            return value.interacted_entity_type;
        }
        else if constexpr (I == 3) {
            return value.interacted_entity_variant;
        }
        else {
            return value.interacted_entity_color;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v766::LegacyTelemetryEventPacket::MobKilled> = true;

template <>
inline constexpr std::string_view struct_name_v<v766::LegacyTelemetryEventPacket::MobKilled>{"LegacyTelemetryEventPacket::MobKilled"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<v766::LegacyTelemetryEventPacket::MobKilled>{{
    "killer_entity_id",
    "killed_mob_id",
    "damage_child_type",
    "damage_source",
    "trader_tier",
    "trader_name",
}};

template <>
struct field_accessor<v766::LegacyTelemetryEventPacket::MobKilled> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.killer_entity_id;
        }
        else if constexpr (I == 1) {
            return value.killed_mob_id;
        }
        else if constexpr (I == 2) {
            return value.damage_child_type;
        }
        else if constexpr (I == 3) {
            return value.damage_source;
        }
        else if constexpr (I == 4) {
            return value.trader_tier;
        }
        else {
            return value.trader_name;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v766::LegacyTelemetryEventPacket::POICauldronUsed> = true;

template <>
inline constexpr std::string_view struct_name_v<v766::LegacyTelemetryEventPacket::POICauldronUsed>{"LegacyTelemetryEventPacket::POICauldronUsed"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v766::LegacyTelemetryEventPacket::POICauldronUsed>{{
    "interaction_type",
    "item_id",
}};

template <>
struct field_accessor<v766::LegacyTelemetryEventPacket::POICauldronUsed> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.interaction_type;
        }
        else {
            return value.item_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v766::LegacyTelemetryEventPacket::ComposterUsed> = true;

template <>
inline constexpr std::string_view struct_name_v<v766::LegacyTelemetryEventPacket::ComposterUsed>{"LegacyTelemetryEventPacket::ComposterUsed"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v766::LegacyTelemetryEventPacket::ComposterUsed>{{
    "interaction_type",
    "item_id",
}};

template <>
struct field_accessor<v766::LegacyTelemetryEventPacket::ComposterUsed> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.interaction_type;
        }
        else {
            return value.item_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v776::LegacyTelemetryEventPacket::Achievement> = true;

template <>
inline constexpr std::string_view struct_name_v<v776::LegacyTelemetryEventPacket::Achievement>{"LegacyTelemetryEventPacket::Achievement"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v776::LegacyTelemetryEventPacket::Achievement>{{
    "achievement_id",
}};

template <>
struct field_accessor<v776::LegacyTelemetryEventPacket::Achievement> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.achievement_id;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v776::LegacyTelemetryEventPacket::Interaction> = true;

template <>
inline constexpr std::string_view struct_name_v<v776::LegacyTelemetryEventPacket::Interaction>{"LegacyTelemetryEventPacket::Interaction"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v776::LegacyTelemetryEventPacket::Interaction>{{
    "interacted_entity_id",
    "interaction_type",
    "interacted_entity_type",
    "interacted_entity_variant",
    "interacted_entity_color",
}};

template <>
struct field_accessor<v776::LegacyTelemetryEventPacket::Interaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.interacted_entity_id;
        }
        else if constexpr (I == 1) {
            return value.interaction_type;
        }
        else if constexpr (I == 2) {
            return value.interacted_entity_type;
        }
        else if constexpr (I == 3) {
            return value.interacted_entity_variant;
        }
        else {
            return value.interacted_entity_color;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v776::LegacyTelemetryEventPacket::MobKilled> = true;

template <>
inline constexpr std::string_view struct_name_v<v776::LegacyTelemetryEventPacket::MobKilled>{"LegacyTelemetryEventPacket::MobKilled"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<v776::LegacyTelemetryEventPacket::MobKilled>{{
    "killer_entity_id",
    "killed_mob_id",
    "damage_child_type",
    "damage_source",
    "trader_tier",
    "trader_name",
}};

template <>
struct field_accessor<v776::LegacyTelemetryEventPacket::MobKilled> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.killer_entity_id;
        }
        else if constexpr (I == 1) {
            return value.killed_mob_id;
        }
        else if constexpr (I == 2) {
            return value.damage_child_type;
        }
        else if constexpr (I == 3) {
            return value.damage_source;
        }
        else if constexpr (I == 4) {
            return value.trader_tier;
        }
        else {
            return value.trader_name;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v776::LegacyTelemetryEventPacket::POICauldronUsed> = true;

template <>
inline constexpr std::string_view struct_name_v<v776::LegacyTelemetryEventPacket::POICauldronUsed>{"LegacyTelemetryEventPacket::POICauldronUsed"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v776::LegacyTelemetryEventPacket::POICauldronUsed>{{
    "interaction_type",
    "item_id",
}};

template <>
struct field_accessor<v776::LegacyTelemetryEventPacket::POICauldronUsed> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.interaction_type;
        }
        else {
            return value.item_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v776::LegacyTelemetryEventPacket::ComposterUsed> = true;

template <>
inline constexpr std::string_view struct_name_v<v776::LegacyTelemetryEventPacket::ComposterUsed>{"LegacyTelemetryEventPacket::ComposterUsed"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v776::LegacyTelemetryEventPacket::ComposterUsed>{{
    "interaction_type",
    "item_id",
}};

template <>
struct field_accessor<v776::LegacyTelemetryEventPacket::ComposterUsed> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.interaction_type;
        }
        else {
            return value.item_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v800::LegacyTelemetryEventPacket::Achievement> = true;

template <>
inline constexpr std::string_view struct_name_v<v800::LegacyTelemetryEventPacket::Achievement>{"LegacyTelemetryEventPacket::Achievement"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v800::LegacyTelemetryEventPacket::Achievement>{{
    "achievement_id",
}};

template <>
struct field_accessor<v800::LegacyTelemetryEventPacket::Achievement> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.achievement_id;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v800::LegacyTelemetryEventPacket::Interaction> = true;

template <>
inline constexpr std::string_view struct_name_v<v800::LegacyTelemetryEventPacket::Interaction>{"LegacyTelemetryEventPacket::Interaction"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v800::LegacyTelemetryEventPacket::Interaction>{{
    "interacted_entity_id",
    "interaction_type",
    "interacted_entity_type",
    "interacted_entity_variant",
    "interacted_entity_color",
}};

template <>
struct field_accessor<v800::LegacyTelemetryEventPacket::Interaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.interacted_entity_id;
        }
        else if constexpr (I == 1) {
            return value.interaction_type;
        }
        else if constexpr (I == 2) {
            return value.interacted_entity_type;
        }
        else if constexpr (I == 3) {
            return value.interacted_entity_variant;
        }
        else {
            return value.interacted_entity_color;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v800::LegacyTelemetryEventPacket::MobKilled> = true;

template <>
inline constexpr std::string_view struct_name_v<v800::LegacyTelemetryEventPacket::MobKilled>{"LegacyTelemetryEventPacket::MobKilled"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<v800::LegacyTelemetryEventPacket::MobKilled>{{
    "killer_entity_id",
    "killed_mob_id",
    "damage_child_type",
    "damage_source",
    "trader_tier",
    "trader_name",
}};

template <>
struct field_accessor<v800::LegacyTelemetryEventPacket::MobKilled> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.killer_entity_id;
        }
        else if constexpr (I == 1) {
            return value.killed_mob_id;
        }
        else if constexpr (I == 2) {
            return value.damage_child_type;
        }
        else if constexpr (I == 3) {
            return value.damage_source;
        }
        else if constexpr (I == 4) {
            return value.trader_tier;
        }
        else {
            return value.trader_name;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v800::LegacyTelemetryEventPacket::POICauldronUsed> = true;

template <>
inline constexpr std::string_view struct_name_v<v800::LegacyTelemetryEventPacket::POICauldronUsed>{"LegacyTelemetryEventPacket::POICauldronUsed"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v800::LegacyTelemetryEventPacket::POICauldronUsed>{{
    "interaction_type",
    "item_id",
}};

template <>
struct field_accessor<v800::LegacyTelemetryEventPacket::POICauldronUsed> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.interaction_type;
        }
        else {
            return value.item_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v800::LegacyTelemetryEventPacket::ComposterUsed> = true;

template <>
inline constexpr std::string_view struct_name_v<v800::LegacyTelemetryEventPacket::ComposterUsed>{"LegacyTelemetryEventPacket::ComposterUsed"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v800::LegacyTelemetryEventPacket::ComposterUsed>{{
    "interaction_type",
    "item_id",
}};

template <>
struct field_accessor<v800::LegacyTelemetryEventPacket::ComposterUsed> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.interaction_type;
        }
        else {
            return value.item_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v818::LegacyTelemetryEventPacket::Achievement> = true;

template <>
inline constexpr std::string_view struct_name_v<v818::LegacyTelemetryEventPacket::Achievement>{"LegacyTelemetryEventPacket::Achievement"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v818::LegacyTelemetryEventPacket::Achievement>{{
    "achievement_id",
}};

template <>
struct field_accessor<v818::LegacyTelemetryEventPacket::Achievement> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.achievement_id;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v818::LegacyTelemetryEventPacket::Interaction> = true;

template <>
inline constexpr std::string_view struct_name_v<v818::LegacyTelemetryEventPacket::Interaction>{"LegacyTelemetryEventPacket::Interaction"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v818::LegacyTelemetryEventPacket::Interaction>{{
    "interacted_entity_id",
    "interaction_type",
    "interacted_entity_type",
    "interacted_entity_variant",
    "interacted_entity_color",
}};

template <>
struct field_accessor<v818::LegacyTelemetryEventPacket::Interaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.interacted_entity_id;
        }
        else if constexpr (I == 1) {
            return value.interaction_type;
        }
        else if constexpr (I == 2) {
            return value.interacted_entity_type;
        }
        else if constexpr (I == 3) {
            return value.interacted_entity_variant;
        }
        else {
            return value.interacted_entity_color;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v818::LegacyTelemetryEventPacket::MobKilled> = true;

template <>
inline constexpr std::string_view struct_name_v<v818::LegacyTelemetryEventPacket::MobKilled>{"LegacyTelemetryEventPacket::MobKilled"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<v818::LegacyTelemetryEventPacket::MobKilled>{{
    "killer_entity_id",
    "killed_mob_id",
    "damage_child_type",
    "damage_source",
    "trader_tier",
    "trader_name",
}};

template <>
struct field_accessor<v818::LegacyTelemetryEventPacket::MobKilled> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.killer_entity_id;
        }
        else if constexpr (I == 1) {
            return value.killed_mob_id;
        }
        else if constexpr (I == 2) {
            return value.damage_child_type;
        }
        else if constexpr (I == 3) {
            return value.damage_source;
        }
        else if constexpr (I == 4) {
            return value.trader_tier;
        }
        else {
            return value.trader_name;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v818::LegacyTelemetryEventPacket::POICauldronUsed> = true;

template <>
inline constexpr std::string_view struct_name_v<v818::LegacyTelemetryEventPacket::POICauldronUsed>{"LegacyTelemetryEventPacket::POICauldronUsed"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v818::LegacyTelemetryEventPacket::POICauldronUsed>{{
    "interaction_type",
    "item_id",
}};

template <>
struct field_accessor<v818::LegacyTelemetryEventPacket::POICauldronUsed> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.interaction_type;
        }
        else {
            return value.item_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v818::LegacyTelemetryEventPacket::ComposterUsed> = true;

template <>
inline constexpr std::string_view struct_name_v<v818::LegacyTelemetryEventPacket::ComposterUsed>{"LegacyTelemetryEventPacket::ComposterUsed"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v818::LegacyTelemetryEventPacket::ComposterUsed>{{
    "interaction_type",
    "item_id",
}};

template <>
struct field_accessor<v818::LegacyTelemetryEventPacket::ComposterUsed> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.interaction_type;
        }
        else {
            return value.item_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v827::LegacyTelemetryEventPacket::Achievement> = true;

template <>
inline constexpr std::string_view struct_name_v<v827::LegacyTelemetryEventPacket::Achievement>{"LegacyTelemetryEventPacket::Achievement"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v827::LegacyTelemetryEventPacket::Achievement>{{
    "achievement_id",
}};

template <>
struct field_accessor<v827::LegacyTelemetryEventPacket::Achievement> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.achievement_id;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v827::LegacyTelemetryEventPacket::Interaction> = true;

template <>
inline constexpr std::string_view struct_name_v<v827::LegacyTelemetryEventPacket::Interaction>{"LegacyTelemetryEventPacket::Interaction"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v827::LegacyTelemetryEventPacket::Interaction>{{
    "interacted_entity_id",
    "interaction_type",
    "interacted_entity_type",
    "interacted_entity_variant",
    "interacted_entity_color",
}};

template <>
struct field_accessor<v827::LegacyTelemetryEventPacket::Interaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.interacted_entity_id;
        }
        else if constexpr (I == 1) {
            return value.interaction_type;
        }
        else if constexpr (I == 2) {
            return value.interacted_entity_type;
        }
        else if constexpr (I == 3) {
            return value.interacted_entity_variant;
        }
        else {
            return value.interacted_entity_color;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v827::LegacyTelemetryEventPacket::MobKilled> = true;

template <>
inline constexpr std::string_view struct_name_v<v827::LegacyTelemetryEventPacket::MobKilled>{"LegacyTelemetryEventPacket::MobKilled"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<v827::LegacyTelemetryEventPacket::MobKilled>{{
    "killer_entity_id",
    "killed_mob_id",
    "damage_child_type",
    "damage_source",
    "trader_tier",
    "trader_name",
}};

template <>
struct field_accessor<v827::LegacyTelemetryEventPacket::MobKilled> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.killer_entity_id;
        }
        else if constexpr (I == 1) {
            return value.killed_mob_id;
        }
        else if constexpr (I == 2) {
            return value.damage_child_type;
        }
        else if constexpr (I == 3) {
            return value.damage_source;
        }
        else if constexpr (I == 4) {
            return value.trader_tier;
        }
        else {
            return value.trader_name;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v827::LegacyTelemetryEventPacket::POICauldronUsed> = true;

template <>
inline constexpr std::string_view struct_name_v<v827::LegacyTelemetryEventPacket::POICauldronUsed>{"LegacyTelemetryEventPacket::POICauldronUsed"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v827::LegacyTelemetryEventPacket::POICauldronUsed>{{
    "interaction_type",
    "item_id",
}};

template <>
struct field_accessor<v827::LegacyTelemetryEventPacket::POICauldronUsed> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.interaction_type;
        }
        else {
            return value.item_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v827::LegacyTelemetryEventPacket::ComposterUsed> = true;

template <>
inline constexpr std::string_view struct_name_v<v827::LegacyTelemetryEventPacket::ComposterUsed>{"LegacyTelemetryEventPacket::ComposterUsed"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v827::LegacyTelemetryEventPacket::ComposterUsed>{{
    "interaction_type",
    "item_id",
}};

template <>
struct field_accessor<v827::LegacyTelemetryEventPacket::ComposterUsed> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.interaction_type;
        }
        else {
            return value.item_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v898::LegacyTelemetryEventPacket::Achievement> = true;

template <>
inline constexpr std::string_view struct_name_v<v898::LegacyTelemetryEventPacket::Achievement>{"LegacyTelemetryEventPacket::Achievement"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v898::LegacyTelemetryEventPacket::Achievement>{{
    "achievement_id",
}};

template <>
struct field_accessor<v898::LegacyTelemetryEventPacket::Achievement> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.achievement_id;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v898::LegacyTelemetryEventPacket::Interaction> = true;

template <>
inline constexpr std::string_view struct_name_v<v898::LegacyTelemetryEventPacket::Interaction>{"LegacyTelemetryEventPacket::Interaction"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v898::LegacyTelemetryEventPacket::Interaction>{{
    "interacted_entity_id",
    "interaction_type",
    "interacted_entity_type",
    "interacted_entity_variant",
    "interacted_entity_color",
}};

template <>
struct field_accessor<v898::LegacyTelemetryEventPacket::Interaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.interacted_entity_id;
        }
        else if constexpr (I == 1) {
            return value.interaction_type;
        }
        else if constexpr (I == 2) {
            return value.interacted_entity_type;
        }
        else if constexpr (I == 3) {
            return value.interacted_entity_variant;
        }
        else {
            return value.interacted_entity_color;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v898::LegacyTelemetryEventPacket::MobKilled> = true;

template <>
inline constexpr std::string_view struct_name_v<v898::LegacyTelemetryEventPacket::MobKilled>{"LegacyTelemetryEventPacket::MobKilled"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<v898::LegacyTelemetryEventPacket::MobKilled>{{
    "killer_entity_id",
    "killed_mob_id",
    "damage_child_type",
    "damage_source",
    "trader_tier",
    "trader_name",
}};

template <>
struct field_accessor<v898::LegacyTelemetryEventPacket::MobKilled> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.killer_entity_id;
        }
        else if constexpr (I == 1) {
            return value.killed_mob_id;
        }
        else if constexpr (I == 2) {
            return value.damage_child_type;
        }
        else if constexpr (I == 3) {
            return value.damage_source;
        }
        else if constexpr (I == 4) {
            return value.trader_tier;
        }
        else {
            return value.trader_name;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v898::LegacyTelemetryEventPacket::POICauldronUsed> = true;

template <>
inline constexpr std::string_view struct_name_v<v898::LegacyTelemetryEventPacket::POICauldronUsed>{"LegacyTelemetryEventPacket::POICauldronUsed"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v898::LegacyTelemetryEventPacket::POICauldronUsed>{{
    "interaction_type",
    "item_id",
}};

template <>
struct field_accessor<v898::LegacyTelemetryEventPacket::POICauldronUsed> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.interaction_type;
        }
        else {
            return value.item_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v898::LegacyTelemetryEventPacket::ComposterUsed> = true;

template <>
inline constexpr std::string_view struct_name_v<v898::LegacyTelemetryEventPacket::ComposterUsed>{"LegacyTelemetryEventPacket::ComposterUsed"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v898::LegacyTelemetryEventPacket::ComposterUsed>{{
    "interaction_type",
    "item_id",
}};

template <>
struct field_accessor<v898::LegacyTelemetryEventPacket::ComposterUsed> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.interaction_type;
        }
        else {
            return value.item_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::LegacyTelemetryEventPacket::Achievement> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::LegacyTelemetryEventPacket::Achievement>{"LegacyTelemetryEventPacket::Achievement"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v924::LegacyTelemetryEventPacket::Achievement>{{
    "achievement_id",
}};

template <>
struct field_accessor<v924::LegacyTelemetryEventPacket::Achievement> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.achievement_id;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::LegacyTelemetryEventPacket::Interaction> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::LegacyTelemetryEventPacket::Interaction>{"LegacyTelemetryEventPacket::Interaction"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v924::LegacyTelemetryEventPacket::Interaction>{{
    "interacted_entity_id",
    "interaction_type",
    "interacted_entity_type",
    "interacted_entity_variant",
    "interacted_entity_color",
}};

template <>
struct field_accessor<v924::LegacyTelemetryEventPacket::Interaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.interacted_entity_id;
        }
        else if constexpr (I == 1) {
            return value.interaction_type;
        }
        else if constexpr (I == 2) {
            return value.interacted_entity_type;
        }
        else if constexpr (I == 3) {
            return value.interacted_entity_variant;
        }
        else {
            return value.interacted_entity_color;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::LegacyTelemetryEventPacket::MobKilled> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::LegacyTelemetryEventPacket::MobKilled>{"LegacyTelemetryEventPacket::MobKilled"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<v924::LegacyTelemetryEventPacket::MobKilled>{{
    "killer_entity_id",
    "killed_mob_id",
    "damage_child_type",
    "damage_source",
    "trader_tier",
    "trader_name",
}};

template <>
struct field_accessor<v924::LegacyTelemetryEventPacket::MobKilled> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.killer_entity_id;
        }
        else if constexpr (I == 1) {
            return value.killed_mob_id;
        }
        else if constexpr (I == 2) {
            return value.damage_child_type;
        }
        else if constexpr (I == 3) {
            return value.damage_source;
        }
        else if constexpr (I == 4) {
            return value.trader_tier;
        }
        else {
            return value.trader_name;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::LegacyTelemetryEventPacket::POICauldronUsed> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::LegacyTelemetryEventPacket::POICauldronUsed>{"LegacyTelemetryEventPacket::POICauldronUsed"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v924::LegacyTelemetryEventPacket::POICauldronUsed>{{
    "interaction_type",
    "item_id",
}};

template <>
struct field_accessor<v924::LegacyTelemetryEventPacket::POICauldronUsed> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.interaction_type;
        }
        else {
            return value.item_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::LegacyTelemetryEventPacket::ComposterUsed> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::LegacyTelemetryEventPacket::ComposterUsed>{"LegacyTelemetryEventPacket::ComposterUsed"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v924::LegacyTelemetryEventPacket::ComposterUsed>{{
    "interaction_type",
    "item_id",
}};

template <>
struct field_accessor<v924::LegacyTelemetryEventPacket::ComposterUsed> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.interaction_type;
        }
        else {
            return value.item_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v975::LegacyTelemetryEventPacket::Achievement> = true;

template <>
inline constexpr std::string_view struct_name_v<v975::LegacyTelemetryEventPacket::Achievement>{"LegacyTelemetryEventPacket::Achievement"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v975::LegacyTelemetryEventPacket::Achievement>{{
    "achievement_id",
}};

template <>
struct field_accessor<v975::LegacyTelemetryEventPacket::Achievement> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.achievement_id;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v975::LegacyTelemetryEventPacket::Interaction> = true;

template <>
inline constexpr std::string_view struct_name_v<v975::LegacyTelemetryEventPacket::Interaction>{"LegacyTelemetryEventPacket::Interaction"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v975::LegacyTelemetryEventPacket::Interaction>{{
    "interacted_entity_id",
    "interaction_type",
    "interacted_entity_type",
    "interacted_entity_variant",
    "interacted_entity_color",
}};

template <>
struct field_accessor<v975::LegacyTelemetryEventPacket::Interaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.interacted_entity_id;
        }
        else if constexpr (I == 1) {
            return value.interaction_type;
        }
        else if constexpr (I == 2) {
            return value.interacted_entity_type;
        }
        else if constexpr (I == 3) {
            return value.interacted_entity_variant;
        }
        else {
            return value.interacted_entity_color;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v975::LegacyTelemetryEventPacket::MobKilled> = true;

template <>
inline constexpr std::string_view struct_name_v<v975::LegacyTelemetryEventPacket::MobKilled>{"LegacyTelemetryEventPacket::MobKilled"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<v975::LegacyTelemetryEventPacket::MobKilled>{{
    "killer_entity_id",
    "killed_mob_id",
    "damage_child_type",
    "damage_source",
    "trader_tier",
    "trader_name",
}};

template <>
struct field_accessor<v975::LegacyTelemetryEventPacket::MobKilled> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.killer_entity_id;
        }
        else if constexpr (I == 1) {
            return value.killed_mob_id;
        }
        else if constexpr (I == 2) {
            return value.damage_child_type;
        }
        else if constexpr (I == 3) {
            return value.damage_source;
        }
        else if constexpr (I == 4) {
            return value.trader_tier;
        }
        else {
            return value.trader_name;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v975::LegacyTelemetryEventPacket::POICauldronUsed> = true;

template <>
inline constexpr std::string_view struct_name_v<v975::LegacyTelemetryEventPacket::POICauldronUsed>{"LegacyTelemetryEventPacket::POICauldronUsed"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v975::LegacyTelemetryEventPacket::POICauldronUsed>{{
    "interaction_type",
    "item_id",
}};

template <>
struct field_accessor<v975::LegacyTelemetryEventPacket::POICauldronUsed> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.interaction_type;
        }
        else {
            return value.item_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v975::LegacyTelemetryEventPacket::ComposterUsed> = true;

template <>
inline constexpr std::string_view struct_name_v<v975::LegacyTelemetryEventPacket::ComposterUsed>{"LegacyTelemetryEventPacket::ComposterUsed"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v975::LegacyTelemetryEventPacket::ComposterUsed>{{
    "interaction_type",
    "item_id",
}};

template <>
struct field_accessor<v975::LegacyTelemetryEventPacket::ComposterUsed> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.interaction_type;
        }
        else {
            return value.item_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::LegacyTelemetryEventPacket::Achievement> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::LegacyTelemetryEventPacket::Achievement>{"LegacyTelemetryEventPacket::Achievement"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v1001::LegacyTelemetryEventPacket::Achievement>{{
    "achievement_id",
}};

template <>
struct field_accessor<v1001::LegacyTelemetryEventPacket::Achievement> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.achievement_id;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::LegacyTelemetryEventPacket::Interaction> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::LegacyTelemetryEventPacket::Interaction>{"LegacyTelemetryEventPacket::Interaction"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v1001::LegacyTelemetryEventPacket::Interaction>{{
    "interacted_entity_id",
    "interaction_type",
    "interacted_entity_type",
    "interacted_entity_variant",
    "interacted_entity_color",
}};

template <>
struct field_accessor<v1001::LegacyTelemetryEventPacket::Interaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.interacted_entity_id;
        }
        else if constexpr (I == 1) {
            return value.interaction_type;
        }
        else if constexpr (I == 2) {
            return value.interacted_entity_type;
        }
        else if constexpr (I == 3) {
            return value.interacted_entity_variant;
        }
        else {
            return value.interacted_entity_color;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::LegacyTelemetryEventPacket::MobKilled> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::LegacyTelemetryEventPacket::MobKilled>{"LegacyTelemetryEventPacket::MobKilled"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<v1001::LegacyTelemetryEventPacket::MobKilled>{{
    "killer_entity_id",
    "killed_mob_id",
    "damage_child_type",
    "damage_source",
    "trader_tier",
    "trader_name",
}};

template <>
struct field_accessor<v1001::LegacyTelemetryEventPacket::MobKilled> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.killer_entity_id;
        }
        else if constexpr (I == 1) {
            return value.killed_mob_id;
        }
        else if constexpr (I == 2) {
            return value.damage_child_type;
        }
        else if constexpr (I == 3) {
            return value.damage_source;
        }
        else if constexpr (I == 4) {
            return value.trader_tier;
        }
        else {
            return value.trader_name;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::LegacyTelemetryEventPacket::POICauldronUsed> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::LegacyTelemetryEventPacket::POICauldronUsed>{"LegacyTelemetryEventPacket::POICauldronUsed"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v1001::LegacyTelemetryEventPacket::POICauldronUsed>{{
    "interaction_type",
    "item_id",
}};

template <>
struct field_accessor<v1001::LegacyTelemetryEventPacket::POICauldronUsed> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.interaction_type;
        }
        else {
            return value.item_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::LegacyTelemetryEventPacket::ComposterUsed> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::LegacyTelemetryEventPacket::ComposterUsed>{"LegacyTelemetryEventPacket::ComposterUsed"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v1001::LegacyTelemetryEventPacket::ComposterUsed>{{
    "interaction_type",
    "item_id",
}};

template <>
struct field_accessor<v1001::LegacyTelemetryEventPacket::ComposterUsed> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.interaction_type;
        }
        else {
            return value.item_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::LegacyTelemetryEventPacket::Achievement> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::LegacyTelemetryEventPacket::Achievement>{"LegacyTelemetryEventPacket::Achievement"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2168::LegacyTelemetryEventPacket::Achievement>{{
    "achievement_id",
}};

template <>
struct field_accessor<v2168::LegacyTelemetryEventPacket::Achievement> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.achievement_id;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::LegacyTelemetryEventPacket::Interaction> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::LegacyTelemetryEventPacket::Interaction>{"LegacyTelemetryEventPacket::Interaction"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v2168::LegacyTelemetryEventPacket::Interaction>{{
    "interacted_entity_id",
    "interaction_type",
    "interacted_entity_type",
    "interacted_entity_variant",
    "interacted_entity_color",
}};

template <>
struct field_accessor<v2168::LegacyTelemetryEventPacket::Interaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.interacted_entity_id;
        }
        else if constexpr (I == 1) {
            return value.interaction_type;
        }
        else if constexpr (I == 2) {
            return value.interacted_entity_type;
        }
        else if constexpr (I == 3) {
            return value.interacted_entity_variant;
        }
        else {
            return value.interacted_entity_color;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::LegacyTelemetryEventPacket::MobKilled> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::LegacyTelemetryEventPacket::MobKilled>{"LegacyTelemetryEventPacket::MobKilled"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<v2168::LegacyTelemetryEventPacket::MobKilled>{{
    "killer_entity_id",
    "killed_mob_id",
    "damage_child_type",
    "damage_source",
    "trader_tier",
    "trader_name",
}};

template <>
struct field_accessor<v2168::LegacyTelemetryEventPacket::MobKilled> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.killer_entity_id;
        }
        else if constexpr (I == 1) {
            return value.killed_mob_id;
        }
        else if constexpr (I == 2) {
            return value.damage_child_type;
        }
        else if constexpr (I == 3) {
            return value.damage_source;
        }
        else if constexpr (I == 4) {
            return value.trader_tier;
        }
        else {
            return value.trader_name;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::LegacyTelemetryEventPacket::POICauldronUsed> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::LegacyTelemetryEventPacket::POICauldronUsed>{"LegacyTelemetryEventPacket::POICauldronUsed"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2168::LegacyTelemetryEventPacket::POICauldronUsed>{{
    "interaction_type",
    "item_id",
}};

template <>
struct field_accessor<v2168::LegacyTelemetryEventPacket::POICauldronUsed> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.interaction_type;
        }
        else {
            return value.item_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::LegacyTelemetryEventPacket::ComposterUsed> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::LegacyTelemetryEventPacket::ComposterUsed>{"LegacyTelemetryEventPacket::ComposterUsed"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2168::LegacyTelemetryEventPacket::ComposterUsed>{{
    "interaction_type",
    "item_id",
}};

template <>
struct field_accessor<v2168::LegacyTelemetryEventPacket::ComposterUsed> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.interaction_type;
        }
        else {
            return value.item_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::LegacyTelemetryEventPacket::Achievement> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::LegacyTelemetryEventPacket::Achievement>{"LegacyTelemetryEventPacket::Achievement"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2225::LegacyTelemetryEventPacket::Achievement>{{
    "achievement_id",
}};

template <>
struct field_accessor<v2225::LegacyTelemetryEventPacket::Achievement> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.achievement_id;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::LegacyTelemetryEventPacket::Interaction> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::LegacyTelemetryEventPacket::Interaction>{"LegacyTelemetryEventPacket::Interaction"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v2225::LegacyTelemetryEventPacket::Interaction>{{
    "interacted_entity_id",
    "interaction_type",
    "interacted_entity_type",
    "interacted_entity_variant",
    "interacted_entity_color",
}};

template <>
struct field_accessor<v2225::LegacyTelemetryEventPacket::Interaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.interacted_entity_id;
        }
        else if constexpr (I == 1) {
            return value.interaction_type;
        }
        else if constexpr (I == 2) {
            return value.interacted_entity_type;
        }
        else if constexpr (I == 3) {
            return value.interacted_entity_variant;
        }
        else {
            return value.interacted_entity_color;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::LegacyTelemetryEventPacket::MobKilled> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::LegacyTelemetryEventPacket::MobKilled>{"LegacyTelemetryEventPacket::MobKilled"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<v2225::LegacyTelemetryEventPacket::MobKilled>{{
    "killer_entity_id",
    "killed_mob_id",
    "damage_child_type",
    "damage_source",
    "trader_tier",
    "trader_name",
}};

template <>
struct field_accessor<v2225::LegacyTelemetryEventPacket::MobKilled> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.killer_entity_id;
        }
        else if constexpr (I == 1) {
            return value.killed_mob_id;
        }
        else if constexpr (I == 2) {
            return value.damage_child_type;
        }
        else if constexpr (I == 3) {
            return value.damage_source;
        }
        else if constexpr (I == 4) {
            return value.trader_tier;
        }
        else {
            return value.trader_name;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::LegacyTelemetryEventPacket::POICauldronUsed> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::LegacyTelemetryEventPacket::POICauldronUsed>{"LegacyTelemetryEventPacket::POICauldronUsed"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2225::LegacyTelemetryEventPacket::POICauldronUsed>{{
    "interaction_type",
    "item_id",
}};

template <>
struct field_accessor<v2225::LegacyTelemetryEventPacket::POICauldronUsed> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.interaction_type;
        }
        else {
            return value.item_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::LegacyTelemetryEventPacket::ComposterUsed> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::LegacyTelemetryEventPacket::ComposterUsed>{"LegacyTelemetryEventPacket::ComposterUsed"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2225::LegacyTelemetryEventPacket::ComposterUsed>{{
    "interaction_type",
    "item_id",
}};

template <>
struct field_accessor<v2225::LegacyTelemetryEventPacket::ComposterUsed> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.interaction_type;
        }
        else {
            return value.item_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::LegacyTelemetryEventPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::LegacyTelemetryEventPacket>{"LegacyTelemetryEventPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<base::LegacyTelemetryEventPacket>{{
    "player_unique_id",
    "type",
    "use_player_id",
    "event_data",
}};

template <>
struct field_accessor<base::LegacyTelemetryEventPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.player_unique_id;
        }
        else if constexpr (I == 1) {
            return value.type;
        }
        else if constexpr (I == 2) {
            return value.use_player_id;
        }
        else {
            return value.event_data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v766::LegacyTelemetryEventPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v766::LegacyTelemetryEventPacket>{"LegacyTelemetryEventPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v766::LegacyTelemetryEventPacket>{{
    "player_unique_id",
    "type",
    "use_player_id",
    "event_data",
}};

template <>
struct field_accessor<v766::LegacyTelemetryEventPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.player_unique_id;
        }
        else if constexpr (I == 1) {
            return value.type;
        }
        else if constexpr (I == 2) {
            return value.use_player_id;
        }
        else {
            return value.event_data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v776::LegacyTelemetryEventPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v776::LegacyTelemetryEventPacket>{"LegacyTelemetryEventPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v776::LegacyTelemetryEventPacket>{{
    "player_unique_id",
    "type",
    "use_player_id",
    "event_data",
}};

template <>
struct field_accessor<v776::LegacyTelemetryEventPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.player_unique_id;
        }
        else if constexpr (I == 1) {
            return value.type;
        }
        else if constexpr (I == 2) {
            return value.use_player_id;
        }
        else {
            return value.event_data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v800::LegacyTelemetryEventPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v800::LegacyTelemetryEventPacket>{"LegacyTelemetryEventPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v800::LegacyTelemetryEventPacket>{{
    "player_unique_id",
    "type",
    "use_player_id",
    "event_data",
}};

template <>
struct field_accessor<v800::LegacyTelemetryEventPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.player_unique_id;
        }
        else if constexpr (I == 1) {
            return value.type;
        }
        else if constexpr (I == 2) {
            return value.use_player_id;
        }
        else {
            return value.event_data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v818::LegacyTelemetryEventPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v818::LegacyTelemetryEventPacket>{"LegacyTelemetryEventPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v818::LegacyTelemetryEventPacket>{{
    "player_unique_id",
    "type",
    "use_player_id",
    "event_data",
}};

template <>
struct field_accessor<v818::LegacyTelemetryEventPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.player_unique_id;
        }
        else if constexpr (I == 1) {
            return value.type;
        }
        else if constexpr (I == 2) {
            return value.use_player_id;
        }
        else {
            return value.event_data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v827::LegacyTelemetryEventPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v827::LegacyTelemetryEventPacket>{"LegacyTelemetryEventPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v827::LegacyTelemetryEventPacket>{{
    "player_unique_id",
    "type",
    "use_player_id",
    "event_data",
}};

template <>
struct field_accessor<v827::LegacyTelemetryEventPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.player_unique_id;
        }
        else if constexpr (I == 1) {
            return value.type;
        }
        else if constexpr (I == 2) {
            return value.use_player_id;
        }
        else {
            return value.event_data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v898::LegacyTelemetryEventPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v898::LegacyTelemetryEventPacket>{"LegacyTelemetryEventPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v898::LegacyTelemetryEventPacket>{{
    "player_unique_id",
    "type",
    "use_player_id",
    "event_data",
}};

template <>
struct field_accessor<v898::LegacyTelemetryEventPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.player_unique_id;
        }
        else if constexpr (I == 1) {
            return value.type;
        }
        else if constexpr (I == 2) {
            return value.use_player_id;
        }
        else {
            return value.event_data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::LegacyTelemetryEventPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::LegacyTelemetryEventPacket>{"LegacyTelemetryEventPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v924::LegacyTelemetryEventPacket>{{
    "player_unique_id",
    "type",
    "use_player_id",
    "event_data",
}};

template <>
struct field_accessor<v924::LegacyTelemetryEventPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.player_unique_id;
        }
        else if constexpr (I == 1) {
            return value.type;
        }
        else if constexpr (I == 2) {
            return value.use_player_id;
        }
        else {
            return value.event_data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v975::LegacyTelemetryEventPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v975::LegacyTelemetryEventPacket>{"LegacyTelemetryEventPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v975::LegacyTelemetryEventPacket>{{
    "player_unique_id",
    "type",
    "use_player_id",
    "event_data",
}};

template <>
struct field_accessor<v975::LegacyTelemetryEventPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.player_unique_id;
        }
        else if constexpr (I == 1) {
            return value.type;
        }
        else if constexpr (I == 2) {
            return value.use_player_id;
        }
        else {
            return value.event_data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::LegacyTelemetryEventPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::LegacyTelemetryEventPacket>{"LegacyTelemetryEventPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v1001::LegacyTelemetryEventPacket>{{
    "player_unique_id",
    "type",
    "use_player_id",
    "event_data",
}};

template <>
struct field_accessor<v1001::LegacyTelemetryEventPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.player_unique_id;
        }
        else if constexpr (I == 1) {
            return value.type;
        }
        else if constexpr (I == 2) {
            return value.use_player_id;
        }
        else {
            return value.event_data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::LegacyTelemetryEventPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::LegacyTelemetryEventPacket>{"LegacyTelemetryEventPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v2168::LegacyTelemetryEventPacket>{{
    "player_unique_id",
    "type",
    "use_player_id",
    "event_data",
}};

template <>
struct field_accessor<v2168::LegacyTelemetryEventPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.player_unique_id;
        }
        else if constexpr (I == 1) {
            return value.type;
        }
        else if constexpr (I == 2) {
            return value.use_player_id;
        }
        else {
            return value.event_data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::LegacyTelemetryEventPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::LegacyTelemetryEventPacket>{"LegacyTelemetryEventPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v2225::LegacyTelemetryEventPacket>{{
    "player_unique_id",
    "type",
    "use_player_id",
    "event_data",
}};

template <>
struct field_accessor<v2225::LegacyTelemetryEventPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.player_unique_id;
        }
        else if constexpr (I == 1) {
            return value.type;
        }
        else if constexpr (I == 2) {
            return value.use_player_id;
        }
        else {
            return value.event_data;
        }
    }
};

}  // namespace detail


template <>
struct Serializer<base::LegacyTelemetryEventPacket::Achievement> {
    static void serialize(BinaryWriter &stream, const base::LegacyTelemetryEventPacket::Achievement &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::LegacyTelemetryEventPacket::Achievement, std::error_code>;
};

template <>
struct Serializer<base::LegacyTelemetryEventPacket::Interaction> {
    static void serialize(BinaryWriter &stream, const base::LegacyTelemetryEventPacket::Interaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::LegacyTelemetryEventPacket::Interaction, std::error_code>;
};

template <>
struct Serializer<base::LegacyTelemetryEventPacket::PortalCreated> {
    static void serialize(BinaryWriter &stream, const base::LegacyTelemetryEventPacket::PortalCreated &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::LegacyTelemetryEventPacket::PortalCreated, std::error_code>;
};

template <>
struct Serializer<base::LegacyTelemetryEventPacket::PortalUsed> {
    static void serialize(BinaryWriter &stream, const base::LegacyTelemetryEventPacket::PortalUsed &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::LegacyTelemetryEventPacket::PortalUsed, std::error_code>;
};

template <>
struct Serializer<base::LegacyTelemetryEventPacket::MobKilled> {
    static void serialize(BinaryWriter &stream, const base::LegacyTelemetryEventPacket::MobKilled &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::LegacyTelemetryEventPacket::MobKilled, std::error_code>;
};

template <>
struct Serializer<base::LegacyTelemetryEventPacket::CauldronUsed> {
    static void serialize(BinaryWriter &stream, const base::LegacyTelemetryEventPacket::CauldronUsed &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::LegacyTelemetryEventPacket::CauldronUsed, std::error_code>;
};

template <>
struct Serializer<base::LegacyTelemetryEventPacket::PlayerDied> {
    static void serialize(BinaryWriter &stream, const base::LegacyTelemetryEventPacket::PlayerDied &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::LegacyTelemetryEventPacket::PlayerDied, std::error_code>;
};

template <>
struct Serializer<base::LegacyTelemetryEventPacket::BossKilled> {
    static void serialize(BinaryWriter &stream, const base::LegacyTelemetryEventPacket::BossKilled &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::LegacyTelemetryEventPacket::BossKilled, std::error_code>;
};

template <>
struct Serializer<base::LegacyTelemetryEventPacket::SlashCommand> {
    static void serialize(BinaryWriter &stream, const base::LegacyTelemetryEventPacket::SlashCommand &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::LegacyTelemetryEventPacket::SlashCommand, std::error_code>;
};

template <>
struct Serializer<base::LegacyTelemetryEventPacket::MobBorn> {
    static void serialize(BinaryWriter &stream, const base::LegacyTelemetryEventPacket::MobBorn &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::LegacyTelemetryEventPacket::MobBorn, std::error_code>;
};

template <>
struct Serializer<base::LegacyTelemetryEventPacket::POICauldronUsed> {
    static void serialize(BinaryWriter &stream, const base::LegacyTelemetryEventPacket::POICauldronUsed &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::LegacyTelemetryEventPacket::POICauldronUsed, std::error_code>;
};

template <>
struct Serializer<base::LegacyTelemetryEventPacket::ComposterUsed> {
    static void serialize(BinaryWriter &stream, const base::LegacyTelemetryEventPacket::ComposterUsed &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::LegacyTelemetryEventPacket::ComposterUsed, std::error_code>;
};

template <>
struct Serializer<base::LegacyTelemetryEventPacket::BellUsed> {
    static void serialize(BinaryWriter &stream, const base::LegacyTelemetryEventPacket::BellUsed &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::LegacyTelemetryEventPacket::BellUsed, std::error_code>;
};

template <>
struct Serializer<base::LegacyTelemetryEventPacket::ActorDefinition> {
    static void serialize(BinaryWriter &stream, const base::LegacyTelemetryEventPacket::ActorDefinition &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::LegacyTelemetryEventPacket::ActorDefinition, std::error_code>;
};

template <>
struct Serializer<base::LegacyTelemetryEventPacket::RaidUpdate> {
    static void serialize(BinaryWriter &stream, const base::LegacyTelemetryEventPacket::RaidUpdate &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::LegacyTelemetryEventPacket::RaidUpdate, std::error_code>;
};

template <>
struct Serializer<base::LegacyTelemetryEventPacket::TargetBlockHit> {
    static void serialize(BinaryWriter &stream, const base::LegacyTelemetryEventPacket::TargetBlockHit &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::LegacyTelemetryEventPacket::TargetBlockHit, std::error_code>;
};

template <>
struct Serializer<base::LegacyTelemetryEventPacket::PiglinBarter> {
    static void serialize(BinaryWriter &stream, const base::LegacyTelemetryEventPacket::PiglinBarter &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::LegacyTelemetryEventPacket::PiglinBarter, std::error_code>;
};

template <>
struct Serializer<base::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper> {
    static void serialize(BinaryWriter &stream, const base::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::LegacyTelemetryEventPacket::PlayerWaxedOrUnwaxedCopper, std::error_code>;
};

template <>
struct Serializer<base::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction> {
    static void serialize(BinaryWriter &stream, const base::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::LegacyTelemetryEventPacket::CodeBuilderRuntimeAction, std::error_code>;
};

template <>
struct Serializer<base::LegacyTelemetryEventPacket::CodeBuilderScoreboard> {
    static void serialize(BinaryWriter &stream, const base::LegacyTelemetryEventPacket::CodeBuilderScoreboard &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::LegacyTelemetryEventPacket::CodeBuilderScoreboard, std::error_code>;
};

template <>
struct Serializer<base::LegacyTelemetryEventPacket::ItemUsed> {
    static void serialize(BinaryWriter &stream, const base::LegacyTelemetryEventPacket::ItemUsed &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::LegacyTelemetryEventPacket::ItemUsed, std::error_code>;
};

template <>
struct Serializer<base::LegacyTelemetryEventPacket::Empty> {
    static void serialize(BinaryWriter &stream, const base::LegacyTelemetryEventPacket::Empty &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::LegacyTelemetryEventPacket::Empty, std::error_code>;
};

template <>
struct Serializer<v766::LegacyTelemetryEventPacket::Achievement> {
    static void serialize(BinaryWriter &stream, const v766::LegacyTelemetryEventPacket::Achievement &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v766::LegacyTelemetryEventPacket::Achievement, std::error_code>;
};

template <>
struct Serializer<v766::LegacyTelemetryEventPacket::Interaction> {
    static void serialize(BinaryWriter &stream, const v766::LegacyTelemetryEventPacket::Interaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v766::LegacyTelemetryEventPacket::Interaction, std::error_code>;
};

template <>
struct Serializer<v766::LegacyTelemetryEventPacket::MobKilled> {
    static void serialize(BinaryWriter &stream, const v766::LegacyTelemetryEventPacket::MobKilled &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v766::LegacyTelemetryEventPacket::MobKilled, std::error_code>;
};

template <>
struct Serializer<v766::LegacyTelemetryEventPacket::POICauldronUsed> {
    static void serialize(BinaryWriter &stream, const v766::LegacyTelemetryEventPacket::POICauldronUsed &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v766::LegacyTelemetryEventPacket::POICauldronUsed, std::error_code>;
};

template <>
struct Serializer<v766::LegacyTelemetryEventPacket::ComposterUsed> {
    static void serialize(BinaryWriter &stream, const v766::LegacyTelemetryEventPacket::ComposterUsed &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v766::LegacyTelemetryEventPacket::ComposterUsed, std::error_code>;
};

template <>
struct Serializer<v776::LegacyTelemetryEventPacket::Achievement> {
    static void serialize(BinaryWriter &stream, const v776::LegacyTelemetryEventPacket::Achievement &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v776::LegacyTelemetryEventPacket::Achievement, std::error_code>;
};

template <>
struct Serializer<v776::LegacyTelemetryEventPacket::Interaction> {
    static void serialize(BinaryWriter &stream, const v776::LegacyTelemetryEventPacket::Interaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v776::LegacyTelemetryEventPacket::Interaction, std::error_code>;
};

template <>
struct Serializer<v776::LegacyTelemetryEventPacket::MobKilled> {
    static void serialize(BinaryWriter &stream, const v776::LegacyTelemetryEventPacket::MobKilled &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v776::LegacyTelemetryEventPacket::MobKilled, std::error_code>;
};

template <>
struct Serializer<v776::LegacyTelemetryEventPacket::POICauldronUsed> {
    static void serialize(BinaryWriter &stream, const v776::LegacyTelemetryEventPacket::POICauldronUsed &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v776::LegacyTelemetryEventPacket::POICauldronUsed, std::error_code>;
};

template <>
struct Serializer<v776::LegacyTelemetryEventPacket::ComposterUsed> {
    static void serialize(BinaryWriter &stream, const v776::LegacyTelemetryEventPacket::ComposterUsed &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v776::LegacyTelemetryEventPacket::ComposterUsed, std::error_code>;
};

template <>
struct Serializer<v800::LegacyTelemetryEventPacket::Achievement> {
    static void serialize(BinaryWriter &stream, const v800::LegacyTelemetryEventPacket::Achievement &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v800::LegacyTelemetryEventPacket::Achievement, std::error_code>;
};

template <>
struct Serializer<v800::LegacyTelemetryEventPacket::Interaction> {
    static void serialize(BinaryWriter &stream, const v800::LegacyTelemetryEventPacket::Interaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v800::LegacyTelemetryEventPacket::Interaction, std::error_code>;
};

template <>
struct Serializer<v800::LegacyTelemetryEventPacket::MobKilled> {
    static void serialize(BinaryWriter &stream, const v800::LegacyTelemetryEventPacket::MobKilled &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v800::LegacyTelemetryEventPacket::MobKilled, std::error_code>;
};

template <>
struct Serializer<v800::LegacyTelemetryEventPacket::POICauldronUsed> {
    static void serialize(BinaryWriter &stream, const v800::LegacyTelemetryEventPacket::POICauldronUsed &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v800::LegacyTelemetryEventPacket::POICauldronUsed, std::error_code>;
};

template <>
struct Serializer<v800::LegacyTelemetryEventPacket::ComposterUsed> {
    static void serialize(BinaryWriter &stream, const v800::LegacyTelemetryEventPacket::ComposterUsed &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v800::LegacyTelemetryEventPacket::ComposterUsed, std::error_code>;
};

template <>
struct Serializer<v818::LegacyTelemetryEventPacket::Achievement> {
    static void serialize(BinaryWriter &stream, const v818::LegacyTelemetryEventPacket::Achievement &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v818::LegacyTelemetryEventPacket::Achievement, std::error_code>;
};

template <>
struct Serializer<v818::LegacyTelemetryEventPacket::Interaction> {
    static void serialize(BinaryWriter &stream, const v818::LegacyTelemetryEventPacket::Interaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v818::LegacyTelemetryEventPacket::Interaction, std::error_code>;
};

template <>
struct Serializer<v818::LegacyTelemetryEventPacket::MobKilled> {
    static void serialize(BinaryWriter &stream, const v818::LegacyTelemetryEventPacket::MobKilled &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v818::LegacyTelemetryEventPacket::MobKilled, std::error_code>;
};

template <>
struct Serializer<v818::LegacyTelemetryEventPacket::POICauldronUsed> {
    static void serialize(BinaryWriter &stream, const v818::LegacyTelemetryEventPacket::POICauldronUsed &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v818::LegacyTelemetryEventPacket::POICauldronUsed, std::error_code>;
};

template <>
struct Serializer<v818::LegacyTelemetryEventPacket::ComposterUsed> {
    static void serialize(BinaryWriter &stream, const v818::LegacyTelemetryEventPacket::ComposterUsed &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v818::LegacyTelemetryEventPacket::ComposterUsed, std::error_code>;
};

template <>
struct Serializer<v827::LegacyTelemetryEventPacket::Achievement> {
    static void serialize(BinaryWriter &stream, const v827::LegacyTelemetryEventPacket::Achievement &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v827::LegacyTelemetryEventPacket::Achievement, std::error_code>;
};

template <>
struct Serializer<v827::LegacyTelemetryEventPacket::Interaction> {
    static void serialize(BinaryWriter &stream, const v827::LegacyTelemetryEventPacket::Interaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v827::LegacyTelemetryEventPacket::Interaction, std::error_code>;
};

template <>
struct Serializer<v827::LegacyTelemetryEventPacket::MobKilled> {
    static void serialize(BinaryWriter &stream, const v827::LegacyTelemetryEventPacket::MobKilled &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v827::LegacyTelemetryEventPacket::MobKilled, std::error_code>;
};

template <>
struct Serializer<v827::LegacyTelemetryEventPacket::POICauldronUsed> {
    static void serialize(BinaryWriter &stream, const v827::LegacyTelemetryEventPacket::POICauldronUsed &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v827::LegacyTelemetryEventPacket::POICauldronUsed, std::error_code>;
};

template <>
struct Serializer<v827::LegacyTelemetryEventPacket::ComposterUsed> {
    static void serialize(BinaryWriter &stream, const v827::LegacyTelemetryEventPacket::ComposterUsed &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v827::LegacyTelemetryEventPacket::ComposterUsed, std::error_code>;
};

template <>
struct Serializer<v898::LegacyTelemetryEventPacket::Achievement> {
    static void serialize(BinaryWriter &stream, const v898::LegacyTelemetryEventPacket::Achievement &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v898::LegacyTelemetryEventPacket::Achievement, std::error_code>;
};

template <>
struct Serializer<v898::LegacyTelemetryEventPacket::Interaction> {
    static void serialize(BinaryWriter &stream, const v898::LegacyTelemetryEventPacket::Interaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v898::LegacyTelemetryEventPacket::Interaction, std::error_code>;
};

template <>
struct Serializer<v898::LegacyTelemetryEventPacket::MobKilled> {
    static void serialize(BinaryWriter &stream, const v898::LegacyTelemetryEventPacket::MobKilled &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v898::LegacyTelemetryEventPacket::MobKilled, std::error_code>;
};

template <>
struct Serializer<v898::LegacyTelemetryEventPacket::POICauldronUsed> {
    static void serialize(BinaryWriter &stream, const v898::LegacyTelemetryEventPacket::POICauldronUsed &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v898::LegacyTelemetryEventPacket::POICauldronUsed, std::error_code>;
};

template <>
struct Serializer<v898::LegacyTelemetryEventPacket::ComposterUsed> {
    static void serialize(BinaryWriter &stream, const v898::LegacyTelemetryEventPacket::ComposterUsed &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v898::LegacyTelemetryEventPacket::ComposterUsed, std::error_code>;
};

template <>
struct Serializer<v924::LegacyTelemetryEventPacket::Achievement> {
    static void serialize(BinaryWriter &stream, const v924::LegacyTelemetryEventPacket::Achievement &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::LegacyTelemetryEventPacket::Achievement, std::error_code>;
};

template <>
struct Serializer<v924::LegacyTelemetryEventPacket::Interaction> {
    static void serialize(BinaryWriter &stream, const v924::LegacyTelemetryEventPacket::Interaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::LegacyTelemetryEventPacket::Interaction, std::error_code>;
};

template <>
struct Serializer<v924::LegacyTelemetryEventPacket::MobKilled> {
    static void serialize(BinaryWriter &stream, const v924::LegacyTelemetryEventPacket::MobKilled &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::LegacyTelemetryEventPacket::MobKilled, std::error_code>;
};

template <>
struct Serializer<v924::LegacyTelemetryEventPacket::POICauldronUsed> {
    static void serialize(BinaryWriter &stream, const v924::LegacyTelemetryEventPacket::POICauldronUsed &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::LegacyTelemetryEventPacket::POICauldronUsed, std::error_code>;
};

template <>
struct Serializer<v924::LegacyTelemetryEventPacket::ComposterUsed> {
    static void serialize(BinaryWriter &stream, const v924::LegacyTelemetryEventPacket::ComposterUsed &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::LegacyTelemetryEventPacket::ComposterUsed, std::error_code>;
};

template <>
struct Serializer<v975::LegacyTelemetryEventPacket::Achievement> {
    static void serialize(BinaryWriter &stream, const v975::LegacyTelemetryEventPacket::Achievement &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v975::LegacyTelemetryEventPacket::Achievement, std::error_code>;
};

template <>
struct Serializer<v975::LegacyTelemetryEventPacket::Interaction> {
    static void serialize(BinaryWriter &stream, const v975::LegacyTelemetryEventPacket::Interaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v975::LegacyTelemetryEventPacket::Interaction, std::error_code>;
};

template <>
struct Serializer<v975::LegacyTelemetryEventPacket::MobKilled> {
    static void serialize(BinaryWriter &stream, const v975::LegacyTelemetryEventPacket::MobKilled &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v975::LegacyTelemetryEventPacket::MobKilled, std::error_code>;
};

template <>
struct Serializer<v975::LegacyTelemetryEventPacket::POICauldronUsed> {
    static void serialize(BinaryWriter &stream, const v975::LegacyTelemetryEventPacket::POICauldronUsed &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v975::LegacyTelemetryEventPacket::POICauldronUsed, std::error_code>;
};

template <>
struct Serializer<v975::LegacyTelemetryEventPacket::ComposterUsed> {
    static void serialize(BinaryWriter &stream, const v975::LegacyTelemetryEventPacket::ComposterUsed &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v975::LegacyTelemetryEventPacket::ComposterUsed, std::error_code>;
};

template <>
struct Serializer<v1001::LegacyTelemetryEventPacket::Achievement> {
    static void serialize(BinaryWriter &stream, const v1001::LegacyTelemetryEventPacket::Achievement &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::LegacyTelemetryEventPacket::Achievement, std::error_code>;
};

template <>
struct Serializer<v1001::LegacyTelemetryEventPacket::Interaction> {
    static void serialize(BinaryWriter &stream, const v1001::LegacyTelemetryEventPacket::Interaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::LegacyTelemetryEventPacket::Interaction, std::error_code>;
};

template <>
struct Serializer<v1001::LegacyTelemetryEventPacket::MobKilled> {
    static void serialize(BinaryWriter &stream, const v1001::LegacyTelemetryEventPacket::MobKilled &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::LegacyTelemetryEventPacket::MobKilled, std::error_code>;
};

template <>
struct Serializer<v1001::LegacyTelemetryEventPacket::POICauldronUsed> {
    static void serialize(BinaryWriter &stream, const v1001::LegacyTelemetryEventPacket::POICauldronUsed &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::LegacyTelemetryEventPacket::POICauldronUsed, std::error_code>;
};

template <>
struct Serializer<v1001::LegacyTelemetryEventPacket::ComposterUsed> {
    static void serialize(BinaryWriter &stream, const v1001::LegacyTelemetryEventPacket::ComposterUsed &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::LegacyTelemetryEventPacket::ComposterUsed, std::error_code>;
};

template <>
struct Serializer<v2168::LegacyTelemetryEventPacket::Achievement> {
    static void serialize(BinaryWriter &stream, const v2168::LegacyTelemetryEventPacket::Achievement &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::LegacyTelemetryEventPacket::Achievement, std::error_code>;
};

template <>
struct Serializer<v2168::LegacyTelemetryEventPacket::Interaction> {
    static void serialize(BinaryWriter &stream, const v2168::LegacyTelemetryEventPacket::Interaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::LegacyTelemetryEventPacket::Interaction, std::error_code>;
};

template <>
struct Serializer<v2168::LegacyTelemetryEventPacket::MobKilled> {
    static void serialize(BinaryWriter &stream, const v2168::LegacyTelemetryEventPacket::MobKilled &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::LegacyTelemetryEventPacket::MobKilled, std::error_code>;
};

template <>
struct Serializer<v2168::LegacyTelemetryEventPacket::POICauldronUsed> {
    static void serialize(BinaryWriter &stream, const v2168::LegacyTelemetryEventPacket::POICauldronUsed &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::LegacyTelemetryEventPacket::POICauldronUsed, std::error_code>;
};

template <>
struct Serializer<v2168::LegacyTelemetryEventPacket::ComposterUsed> {
    static void serialize(BinaryWriter &stream, const v2168::LegacyTelemetryEventPacket::ComposterUsed &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::LegacyTelemetryEventPacket::ComposterUsed, std::error_code>;
};

template <>
struct Serializer<v2225::LegacyTelemetryEventPacket::Achievement> {
    static void serialize(BinaryWriter &stream, const v2225::LegacyTelemetryEventPacket::Achievement &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::LegacyTelemetryEventPacket::Achievement, std::error_code>;
};

template <>
struct Serializer<v2225::LegacyTelemetryEventPacket::Interaction> {
    static void serialize(BinaryWriter &stream, const v2225::LegacyTelemetryEventPacket::Interaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::LegacyTelemetryEventPacket::Interaction, std::error_code>;
};

template <>
struct Serializer<v2225::LegacyTelemetryEventPacket::MobKilled> {
    static void serialize(BinaryWriter &stream, const v2225::LegacyTelemetryEventPacket::MobKilled &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::LegacyTelemetryEventPacket::MobKilled, std::error_code>;
};

template <>
struct Serializer<v2225::LegacyTelemetryEventPacket::POICauldronUsed> {
    static void serialize(BinaryWriter &stream, const v2225::LegacyTelemetryEventPacket::POICauldronUsed &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::LegacyTelemetryEventPacket::POICauldronUsed, std::error_code>;
};

template <>
struct Serializer<v2225::LegacyTelemetryEventPacket::ComposterUsed> {
    static void serialize(BinaryWriter &stream, const v2225::LegacyTelemetryEventPacket::ComposterUsed &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::LegacyTelemetryEventPacket::ComposterUsed, std::error_code>;
};

template <>
struct Serializer<base::LegacyTelemetryEventPacket> {
    static void serialize(BinaryWriter &stream, const base::LegacyTelemetryEventPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::LegacyTelemetryEventPacket, std::error_code>;
};

template <>
struct Serializer<v766::LegacyTelemetryEventPacket> {
    static void serialize(BinaryWriter &stream, const v766::LegacyTelemetryEventPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v766::LegacyTelemetryEventPacket, std::error_code>;
};

template <>
struct Serializer<v776::LegacyTelemetryEventPacket> {
    static void serialize(BinaryWriter &stream, const v776::LegacyTelemetryEventPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v776::LegacyTelemetryEventPacket, std::error_code>;
};

template <>
struct Serializer<v800::LegacyTelemetryEventPacket> {
    static void serialize(BinaryWriter &stream, const v800::LegacyTelemetryEventPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v800::LegacyTelemetryEventPacket, std::error_code>;
};

template <>
struct Serializer<v818::LegacyTelemetryEventPacket> {
    static void serialize(BinaryWriter &stream, const v818::LegacyTelemetryEventPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v818::LegacyTelemetryEventPacket, std::error_code>;
};

template <>
struct Serializer<v827::LegacyTelemetryEventPacket> {
    static void serialize(BinaryWriter &stream, const v827::LegacyTelemetryEventPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v827::LegacyTelemetryEventPacket, std::error_code>;
};

template <>
struct Serializer<v898::LegacyTelemetryEventPacket> {
    static void serialize(BinaryWriter &stream, const v898::LegacyTelemetryEventPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v898::LegacyTelemetryEventPacket, std::error_code>;
};

template <>
struct Serializer<v924::LegacyTelemetryEventPacket> {
    static void serialize(BinaryWriter &stream, const v924::LegacyTelemetryEventPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::LegacyTelemetryEventPacket, std::error_code>;
};

template <>
struct Serializer<v975::LegacyTelemetryEventPacket> {
    static void serialize(BinaryWriter &stream, const v975::LegacyTelemetryEventPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v975::LegacyTelemetryEventPacket, std::error_code>;
};

template <>
struct Serializer<v1001::LegacyTelemetryEventPacket> {
    static void serialize(BinaryWriter &stream, const v1001::LegacyTelemetryEventPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::LegacyTelemetryEventPacket, std::error_code>;
};

template <>
struct Serializer<v2168::LegacyTelemetryEventPacket> {
    static void serialize(BinaryWriter &stream, const v2168::LegacyTelemetryEventPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::LegacyTelemetryEventPacket, std::error_code>;
};

template <>
struct Serializer<v2225::LegacyTelemetryEventPacket> {
    static void serialize(BinaryWriter &stream, const v2225::LegacyTelemetryEventPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::LegacyTelemetryEventPacket, std::error_code>;
};
using MinecraftEventing = MinecraftEventing_<2225>;
using LegacyTelemetryEventPacket = LegacyTelemetryEventPacket_<2225>;

}  // namespace bedrock::protocol
