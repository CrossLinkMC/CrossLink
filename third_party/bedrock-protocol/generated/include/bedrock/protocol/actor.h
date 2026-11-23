#pragma once

#include <array>
#include <compare>
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

#include <bedrock/protocol/common.h>
#include <bedrock/protocol/item.h>

namespace bedrock::protocol {

struct ActorUniqueID {
    constexpr ActorUniqueID() = default;
    explicit constexpr ActorUniqueID(std::int64_t value) : value_(value) {}
    constexpr operator std::int64_t() const { return value_; }
    friend constexpr bool operator==(const ActorUniqueID &, const ActorUniqueID &) = default;
    friend constexpr auto operator<=>(const ActorUniqueID &, const ActorUniqueID &) = default;

  private:
    std::int64_t value_{};
};

struct ActorRuntimeID {
    constexpr ActorRuntimeID() = default;
    explicit constexpr ActorRuntimeID(std::uint64_t value) : value_(value) {}
    constexpr operator std::uint64_t() const { return value_; }
    friend constexpr bool operator==(const ActorRuntimeID &, const ActorRuntimeID &) = default;
    friend constexpr auto operator<=>(const ActorRuntimeID &, const ActorRuntimeID &) = default;

  private:
    std::uint64_t value_{};
};

struct PlayerInputTick {
    constexpr PlayerInputTick() = default;
    explicit constexpr PlayerInputTick(std::uint64_t value) : value_(value) {}
    constexpr operator std::uint64_t() const { return value_; }
    friend constexpr bool operator==(const PlayerInputTick &, const PlayerInputTick &) = default;
    friend constexpr auto operator<=>(const PlayerInputTick &, const PlayerInputTick &) = default;

  private:
    std::uint64_t value_{};
};

enum class DataItemType : std::uint8_t {
    Byte = 0,
    Short = 1,
    Int = 2,
    Float = 3,
    String = 4,
    CompoundTag = 5,
    Pos = 6,
    Int64 = 7,
    Vec3 = 8,
    Unknown = 9,
};

namespace PropertySyncData_nested {

struct PropertySyncIntEntry {
    std::uint32_t property_index{};
    std::int32_t data{};
};

struct PropertySyncFloatEntry {
    std::uint32_t property_index{};
    float data{};
};

}  // namespace PropertySyncData_nested

struct PropertySyncData {
    using PropertySyncIntEntry = PropertySyncData_nested::PropertySyncIntEntry;
    using PropertySyncFloatEntry = PropertySyncData_nested::PropertySyncFloatEntry;

    std::vector<PropertySyncData::PropertySyncIntEntry> int_entries{};
    std::vector<PropertySyncData::PropertySyncFloatEntry> float_entries{};
};

struct SyncedAttribute {
    std::string name{};
    float min_value{};
    float current_value{};
    float max_value{};
};

enum class ActorLinkType : std::uint8_t {
    None = 0,
    Riding = 1,
    Passenger = 2,
};

struct ActorLink {
    ActorUniqueID a{};
    ActorUniqueID b{};
    ActorLinkType type{};
    bool immediate{};
    bool passenger_initiated{};
    float vehicle_angular_velocity{};
};

namespace PassengerOfBlockArguments_nested {

enum class EmoteType : std::uint8_t {
    Standing = 0,
    Riding = 1,
    Laying = 2,
};

}  // namespace PassengerOfBlockArguments_nested

struct PassengerOfBlockArguments {
    using EmoteType = PassengerOfBlockArguments_nested::EmoteType;

    BlockPos block_pos{};
    Vec3 offset{};
    float rotation{};
    float rotation_limit{};
    PassengerOfBlockArguments::EmoteType emote_type{};
};

struct RemoveActorPacket {
    static constexpr int Id = 14;
    ActorUniqueID entity_id{};
};

struct ActorPickRequestPacket {
    static constexpr int Id = 35;
    ActorUniqueID id{};
    std::uint8_t max_slots{};
    bool with_data{};
};

struct AddBehaviorTreePacket {
    static constexpr int Id = 89;
    std::string json_input{};
};

struct TakeItemActorPacket {
    static constexpr int Id = 17;
    ActorRuntimeID item_id{};
    ActorRuntimeID actor_id{};
};

struct MoveActorAbsoluteData {
    ActorRuntimeID runtime_id{};
    std::uint8_t header{};
    Vec3 pos{};
    std::uint8_t rot_x{};
    std::uint8_t rot_y{};
    std::uint8_t rot_y_head{};
};

struct MoveActorAbsolutePacket {
    static constexpr int Id = 18;
    MoveActorAbsoluteData move_data{};
};

struct AddPaintingPacket {
    static constexpr int Id = 22;
    ActorUniqueID entity_id{};
    ActorRuntimeID runtime_id{};
    Vec3 pos{};
    std::int32_t dir{};
    std::string motif{};
};

struct SetActorMotionPacket {
    static constexpr int Id = 40;
    ActorRuntimeID runtime_id{};
    Vec3 motion{};
    PlayerInputTick tick{};
};

struct SetActorLinkPacket {
    static constexpr int Id = 41;
    ActorLink link{};
};

enum class ActorSwingSource : std::uint8_t {
    None = 0,
    Build = 1,
    Mine = 2,
    Interact = 3,
    Attack = 4,
    UseItem = 5,
    ThrowItem = 6,
    DropItem = 7,
    Event = 8,
};

struct SpawnExperienceOrbPacket {
    static constexpr int Id = 66;
    Vec3 pos{};
    std::int32_t xp_value{};
};

struct AvailableActorIdentifiersPacket {
    static constexpr int Id = 119;
    CompoundTag identifier_list{};
};

struct MotionPredictionHintsPacket {
    static constexpr int Id = 157;
    ActorRuntimeID runtime_id{};
    Vec3 motion{};
    bool on_ground{};
};

struct DeathInfoPacket {
    static constexpr int Id = 189;
    std::string death_cause_attack_name{};
    std::vector<std::string> death_cause_message_list{};
};

struct SyncActorPropertyPacket {
    static constexpr int Id = 165;
    CompoundTag property_data{};
};

struct ChangeMobPropertyPacket {
    static constexpr int Id = 182;
    ActorUniqueID actor_id{};
    std::string prop_name{};
    bool bool_component_val{};
    std::string string_component_val{};
    std::int32_t int_component_val{};
    float float_component_val{};
};

struct AnimateEntityPacket {
    static constexpr int Id = 158;
    std::string animation{};
    std::string next_state{};
    std::string stop_expression{};
    std::int32_t stop_expression_version{};
    std::string controller{};
    float blend_out_time{};
    std::vector<ActorRuntimeID> runtime_ids{};
};

namespace NpcRequestPacket_nested {

enum class RequestType : std::uint8_t {
    SetActions = 0,
    ExecuteAction = 1,
    ExecuteClosingCommands = 2,
    SetName = 3,
    SetSkin = 4,
    SetInteractText = 5,
    ExecuteOpeningCommands = 6,
};

}  // namespace NpcRequestPacket_nested

struct NpcRequestPacket {
    using RequestType = NpcRequestPacket_nested::RequestType;

    static constexpr int Id = 98;
    ActorRuntimeID id{};
    NpcRequestPacket::RequestType type{};
    std::string actions{};
    std::uint8_t action_index{};
    std::string scene_name{};
};

namespace NpcDialoguePacket_nested {

enum class NpcDialogueActionType : int {
    Open = 0,
    Close = 1,
};

}  // namespace NpcDialoguePacket_nested

struct NpcDialoguePacket {
    using NpcDialogueActionType = NpcDialoguePacket_nested::NpcDialogueActionType;

    static constexpr int Id = 169;
    ActorUniqueID npc_id{};
    NpcDialoguePacket::NpcDialogueActionType npc_dialogue_action_type{};
    std::string dialogue{};
    std::string scene_name{};
    std::string npc_name{};
    std::string action_json{};
};

namespace base {

enum class ActorFlags : int {
    Onfire = 0,
    Sneaking = 1,
    Riding = 2,
    Sprinting = 3,
    Usingitem = 4,
    Invisible = 5,
    Tempted = 6,
    Inlove = 7,
    Saddled = 8,
    Powered = 9,
    Ignited = 10,
    Baby = 11,
    Converting = 12,
    Critical = 13,
    CanShowName = 14,
    AlwaysShowName = 15,
    Noai = 16,
    Silent = 17,
    Wallclimbing = 18,
    Canclimb = 19,
    Canswim = 20,
    Canfly = 21,
    Canwalk = 22,
    Resting = 23,
    Sitting = 24,
    Angry = 25,
    Interested = 26,
    Charged = 27,
    Tamed = 28,
    Orphaned = 29,
    Leashed = 30,
    Sheared = 31,
    Gliding = 32,
    Elder = 33,
    Moving = 34,
    Breathing = 35,
    Chested = 36,
    Stackable = 37,
    ShowBottom = 38,
    Standing = 39,
    Shaking = 40,
    Idling = 41,
    Casting = 42,
    Charging = 43,
    WasdControlled = 44,
    CanPowerJump = 45,
    CanDash = 46,
    Lingering = 47,
    HasCollision = 48,
    HasGravity = 49,
    FireImmune = 50,
    Dancing = 51,
    Enchanted = 52,
    Returntrident = 53,
    ContainerIsPrivate = 54,
    IsTransforming = 55,
    Damagenearbymobs = 56,
    Swimming = 57,
    Bribed = 58,
    IsPregnant = 59,
    LayingEgg = 60,
    PassengerCanPick = 61,
    TransitionSitting = 62,
    Eating = 63,
    LayingDown = 64,
    Sneezing = 65,
    Trusting = 66,
    Rolling = 67,
    Scared = 68,
    InScaffolding = 69,
    OverScaffolding = 70,
    DescendThroughBlock = 71,
    Blocking = 72,
    TransitionBlocking = 73,
    BlockedUsingShield = 74,
    BlockedUsingDamagedShield = 75,
    Sleeping = 76,
    WantsToWake = 77,
    TradeInterest = 78,
    DoorBreaker = 79,
    BreakingObstruction = 80,
    DoorOpener = 81,
    IsIllagerCaptain = 82,
    Stunned = 83,
    Roaring = 84,
    DelayedAttack = 85,
    IsAvoidingMobs = 86,
    IsAvoidingBlock = 87,
    FacingTargetToRangeAttack = 88,
    HiddenWhenInvisible = 89,
    IsInUi = 90,
    Stalking = 91,
    Emoting = 92,
    Celebrating = 93,
    Admiring = 94,
    CelebratingSpecial = 95,
    OutOfControl = 96,
    RamAttack = 97,
    PlayingDead = 98,
    InAscendableBlock = 99,
    OverDescendableBlock = 100,
    Croaking = 101,
    EatMob = 102,
    JumpGoalJump = 103,
    Emerging = 104,
    Sniffing = 105,
    Digging = 106,
    SonicBoom = 107,
    HasDashCooldown = 108,
    PushTowardsClosestSpace = 109,
    Deprecated1 = 110,
    Deprecated2 = 111,
    Deprecated3 = 112,
    Searching = 113,
    Crawling = 114,
    TimerFlag1 = 115,
    TimerFlag2 = 116,
    TimerFlag3 = 117,
    BodyRotationBlocked = 118,
    Count = 119,
};

enum class ActorDataIDs : std::uint8_t {
    Reserved0 = 0,
    StructuralIntegrity = 1,
    Variant = 2,
    ColorIndex = 3,
    Name = 4,
    Owner = 5,
    Target = 6,
    AirSupply = 7,
    EffectColor = 8,
    Reserved009 = 9,
    Reserved010 = 10,
    Hurt = 11,
    HurtDir = 12,
    RowTimeLeft = 13,
    RowTimeRight = 14,
    Value = 15,
    DisplayTileRuntimeId = 16,
    DisplayOffset = 17,
    CustomDisplay = 18,
    Swell = 19,
    OldSwell = 20,
    SwellDir = 21,
    ChargeAmount = 22,
    DeprecatedCarryBlockRuntimeId = 23,
    ClientEvent = 24,
    UsingItem = 25,
    PlayerFlags = 26,
    PlayerIndex = 27,
    BedPosition = 28,
    XPower = 29,
    YPower = 30,
    ZPower = 31,
    AuxPower = 32,
    Fishx = 33,
    Fishz = 34,
    Fishangle = 35,
    AuxValueData = 36,
    LeashHolder = 37,
    Reserved038 = 38,
    HasNpc = 39,
    NpcData = 40,
    Actions = 41,
    AirSupplyMax = 42,
    MarkVariant = 43,
    ContainerType = 44,
    ContainerSize = 45,
    ContainerStrengthModifier = 46,
    BlockTarget = 47,
    Inv = 48,
    TargetA = 49,
    TargetB = 50,
    TargetC = 51,
    AerialAttack = 52,
    Reserved053 = 53,
    Reserved054 = 54,
    FuseTime = 55,
    Reserved056 = 56,
    SeatLockPassengerRotation = 57,
    SeatLockPassengerRotationDegrees = 58,
    SeatRotationOffset = 59,
    SeatRotationOffsetDegrees = 60,
    DataRadius = 61,
    DataWaiting = 62,
    DataParticle = 63,
    PeekId = 64,
    AttachFace = 65,
    Attached = 66,
    AttachPos = 67,
    TradeTarget = 68,
    Career = 69,
    HasCommandBlock = 70,
    CommandName = 71,
    LastCommandOutput = 72,
    TrackCommandOutput = 73,
    Reserved074 = 74,
    Strength = 75,
    StrengthMax = 76,
    DataSpellCastingColor = 77,
    DataLifetimeTicks = 78,
    PoseIndex = 79,
    DataTickOffset = 80,
    NametagAlwaysShow = 81,
    Color2Index = 82,
    NameAuthor = 83,
    Score = 84,
    BalloonAnchor = 85,
    PuffedState = 86,
    BubbleTime = 87,
    Agent = 88,
    SittingAmount = 89,
    SittingAmountPrevious = 90,
    EatingCounter = 91,
    Reserved092 = 92,
    LayingAmount = 93,
    LayingAmountPrevious = 94,
    DataDuration = 95,
    DataSpawnTimeDeprecated = 96,
    DataChangeRate = 97,
    DataChangeOnPickup = 98,
    DataPickupCount = 99,
    InteractText = 100,
    TradeTier = 101,
    MaxTradeTier = 102,
    TradeExperience = 103,
    SkinId = 104,
    SpawningFrames = 105,
    CommandBlockTickDelay = 106,
    CommandBlockExecuteOnFirstTick = 107,
    AmbientSoundInterval = 108,
    AmbientSoundIntervalRange = 109,
    AmbientSoundEventName = 110,
    FallDamageMultiplier = 111,
    NameRawText = 112,
    CanRideTarget = 113,
    LowTierCuredTradeDiscount = 114,
    HighTierCuredTradeDiscount = 115,
    NearbyCuredTradeDiscount = 116,
    NearbyCuredDiscountTimeStamp = 117,
    Hitbox = 118,
    IsBuoyant = 119,
    FreezingEffectStrength = 120,
    BuoyancyData = 121,
    GoatHornCount = 122,
    BaseRuntimeId = 123,
    MovementSoundDistanceOffset = 124,
    HeartbeatIntervalTicks = 125,
    HeartbeatSoundEvent = 126,
    PlayerLastDeathPos = 127,
    PlayerLastDeathDimension = 128,
    PlayerHasDied = 129,
    CollisionBox = 130,
    VisibleMobEffects = 131,
    Count = 132,
};

struct DataItemBytePayload {
    std::int8_t value{};
};

struct DataItemShortPayload {
    std::int16_t value{};
};

struct DataItemIntPayload {
    std::int32_t value{};
};

struct DataItemFloatPayload {
    float value{};
};

struct DataItemStringPayload {
    std::string value{};
};

struct DataItemCompoundTagPayload {
    CompoundTag value{};
};

struct DataItemPosPayload {
    BlockPos value{};
};

struct DataItemInt64Payload {
    std::int64_t value{};
};

struct DataItemVec3Payload {
    Vec3 value{};
};

struct DataItemEntry {
    std::uint32_t id{};
    std::variant<base::DataItemBytePayload, base::DataItemShortPayload, base::DataItemIntPayload, base::DataItemFloatPayload, base::DataItemStringPayload, base::DataItemCompoundTagPayload, base::DataItemPosPayload, base::DataItemInt64Payload, base::DataItemVec3Payload> payload{};
};

namespace SynchedActorData_nested {

struct CopyableDataList {
    std::vector<base::DataItemEntry> data{};
};

}  // namespace SynchedActorData_nested

struct SynchedActorData {
    using CopyableDataList = SynchedActorData_nested::CopyableDataList;
};

struct AddActorPacket {
    static constexpr int Id = 13;
    ActorUniqueID entity_id{};
    ActorRuntimeID runtime_id{};
    std::string actor_type{};
    Vec3 pos{};
    Vec3 velocity{};
    Vec2 rot{};
    float y_head_rotation{};
    float y_body_rotation{};
    std::vector<SyncedAttribute> attributes{};
    base::SynchedActorData::CopyableDataList data{};
    PropertySyncData synched_properties{};
    std::vector<ActorLink> links{};
};

struct SetActorDataPacket {
    static constexpr int Id = 39;
    ActorRuntimeID id{};
    base::SynchedActorData::CopyableDataList packed_items{};
    PropertySyncData synched_properties{};
    PlayerInputTick tick{};
};

enum class ActorType : int {
    Undefined = 1,
    TypeMask = 255,
    Mob = 256,
    PathfinderMob = 768,
    Monster = 2816,
    Animal = 4864,
    TamableAnimal = 21248,
    Ambient = 33024,
    UndeadMonster = 68352,
    ZombieMonster = 199424,
    Arthropod = 264960,
    Minecart = 524288,
    SkeletonMonster = 1116928,
    EquineAnimal = 2118400,
    Projectile = 4194304,
    AbstractArrow = 8388608,
    WaterAnimal = 8960,
    VillagerBase = 16777984,
    Chicken = 4874,
    Cow = 4875,
    Pig = 4876,
    Sheep = 4877,
    Wolf = 21262,
    Villager = 16777999,
    MushroomCow = 4880,
    Squid = 8977,
    Rabbit = 4882,
    Bat = 33043,
    IronGolem = 788,
    SnowGolem = 789,
    Ocelot = 21270,
    Horse = 2118423,
    PolarBear = 4892,
    Llama = 4893,
    Parrot = 21278,
    Dolphin = 8991,
    Donkey = 2118424,
    Mule = 2118425,
    SkeletonHorse = 2186010,
    ZombieHorse = 2186011,
    Zombie = 199456,
    Creeper = 2849,
    Skeleton = 1116962,
    Spider = 264995,
    PigZombie = 68388,
    Slime = 2853,
    EnderMan = 2854,
    Silverfish = 264999,
    CaveSpider = 265000,
    Ghast = 2857,
    LavaSlime = 2858,
    Blaze = 2859,
    ZombieVillager = 199468,
    Witch = 2861,
    Stray = 1116974,
    Husk = 199471,
    WitherSkeleton = 1116976,
    Guardian = 2865,
    ElderGuardian = 2866,
    Npc = 307,
    WitherBoss = 68404,
    Dragon = 2869,
    Shulker = 2870,
    Endermite = 265015,
    Agent = 312,
    Vindicator = 2873,
    Phantom = 68410,
    IllagerBeast = 2875,
    ArmorStand = 317,
    TripodCamera = 318,
    Player = 319,
    ItemEntity = 64,
    PrimedTnt = 65,
    FallingBlock = 66,
    MovingBlock = 67,
    ExperiencePotion = 4194372,
    Experience = 69,
    EyeOfEnder = 70,
    EnderCrystal = 71,
    FireworksRocket = 72,
    Trident = 12582985,
    Turtle = 4938,
    Cat = 21323,
    ShulkerBullet = 4194380,
    FishingHook = 77,
    Chalkboard = 78,
    DragonFireball = 4194383,
    Arrow = 12582992,
    Snowball = 4194385,
    ThrownEgg = 4194386,
    Painting = 83,
    LargeFireball = 4194389,
    ThrownPotion = 4194390,
    Enderpearl = 4194391,
    LeashKnot = 88,
    WitherSkull = 4194393,
    BoatRideable = 90,
    WitherSkullDangerous = 4194395,
    LightningBolt = 93,
    SmallFireball = 4194398,
    AreaEffectCloud = 95,
    LingeringPotion = 4194405,
    LlamaSpit = 4194406,
    EvocationFang = 4194407,
    EvocationIllager = 2920,
    Vex = 2921,
    MinecartRideable = 524372,
    MinecartHopper = 524384,
    MinecartTNT = 524385,
    MinecartChest = 524386,
    MinecartFurnace = 524387,
    MinecartCommandBlock = 524388,
    IceBomb = 4194410,
    Balloon = 107,
    Pufferfish = 9068,
    Salmon = 9069,
    Drowned = 199534,
    Tropicalfish = 9071,
    Fish = 9072,
    Panda = 4977,
    Pillager = 2930,
    VillagerV2 = 16778099,
    ZombieVillagerV2 = 199540,
    Shield = 117,
    WanderingTrader = 886,
    Lectern = 119,
    ElderGuardianGhost = 2936,
    Fox = 4985,
    Bee = 378,
    Piglin = 379,
    Hoglin = 4988,
    Strider = 4989,
    Zoglin = 68478,
    PiglinBrute = 383,
    Goat = 4992,
    GlowSquid = 9089,
    Axolotl = 4994,
    Warden = 2947,
    Frog = 4996,
    Tadpole = 9093,
    Allay = 390,
    ChestBoatRideable = 218,
    TraderLlama = 5021,
    Camel = 5002,
    Sniffer = 5003,
    Breeze = 2956,
    BreezeWindChargeProjectile = 4194445,
    Armadillo = 5006,
    WindChargeProjectile = 4194447,
    Bogged = 1117072,
    OminousItemSpawner = 145,
    Nautilus = 9109,
    ZombieNautilus = 76694,
    Parched = 1117079,
    CamelHusk = 68504,
};

struct SetLastHurtByPacket {
    static constexpr int Id = 96;
    base::ActorType last_hurt_by{};
};

enum class ActorEvent : std::uint8_t {
    None = 0,
    Jump = 1,
    Hurt = 2,
    Death = 3,
    StartAttacking = 4,
    StopAttacking = 5,
    TamingFailed = 6,
    TamingSucceeded = 7,
    ShakeWetness = 8,
    EatGrass = 10,
    FishhookBubble = 11,
    FishhookFishpos = 12,
    FishhookHooktime = 13,
    FishhookTease = 14,
    SquidFleeing = 15,
    ZombieConverting = 16,
    PlayAmbient = 17,
    SpawnAlive = 18,
    StartOfferFlower = 19,
    StopOfferFlower = 20,
    LoveHearts = 21,
    VillagerAngry = 22,
    VillagerHappy = 23,
    WitchHatMagic = 24,
    FireworksExplode = 25,
    InLoveHearts = 26,
    SilverfishMergeAnim = 27,
    GuardianAttackSound = 28,
    DrinkPotion = 29,
    ThrowPotion = 30,
    PrimeTntcart = 31,
    PrimeCreeper = 32,
    AirSupply = 33,
    DeprecatedAddPlayerLevels = 34,
    GuardianMiningFatigue = 35,
    AgentSwingArm = 36,
    DragonStartDeathAnim = 37,
    GroundDust = 38,
    Shake = 39,
    Feed = 57,
    BabyAge = 60,
    InstantDeath = 61,
    NotifyTrade = 62,
    LeashDestroyed = 63,
    CaravanUpdated = 64,
    TalismanActivate = 65,
    DeprecatedUpdateStructureFeature = 66,
    PlayerSpawnedMob = 67,
    Puke = 68,
    UpdateStackSize = 69,
    StartSwimming = 70,
    BalloonPop = 71,
    TreasureHunt = 72,
    SummonAgent = 73,
    FinishedChargingItem = 74,
    ActorGrowUp = 76,
    VibrationDetected = 77,
    DrinkMilk = 78,
};

struct ActorEventPacket {
    static constexpr int Id = 27;
    ActorRuntimeID runtime_id{};
    base::ActorEvent event_id{};
    std::int32_t data{};
};

namespace AnimatePacket_nested {

enum class Action : std::uint8_t {
    NoAction = 0,
    Swing = 1,
    WakeUp = 3,
    CriticalHit = 4,
    MagicCriticalHit = 5,
    RowRight = 128,
    RowLeft = 129,
};

}  // namespace AnimatePacket_nested

struct AnimatePacket {
    using Action = AnimatePacket_nested::Action;

    static constexpr int Id = 44;
    std::int32_t action{};
    ActorRuntimeID runtime_id{};
    float data{};
};

struct AddItemActorPacket {
    static constexpr int Id = 15;
    ActorUniqueID id{};
    ActorRuntimeID runtime_id{};
    NetworkItemStackDescriptor item{};
    Vec3 pos{};
    Vec3 velocity{};
    base::SynchedActorData::CopyableDataList data{};
    bool is_from_fishing{};
};

}  // namespace base

namespace v766 {

using ActorFlags = base::ActorFlags;

using ActorDataIDs = base::ActorDataIDs;

using DataItemBytePayload = base::DataItemBytePayload;

using DataItemShortPayload = base::DataItemShortPayload;

using DataItemIntPayload = base::DataItemIntPayload;

using DataItemFloatPayload = base::DataItemFloatPayload;

using DataItemStringPayload = base::DataItemStringPayload;

using DataItemCompoundTagPayload = base::DataItemCompoundTagPayload;

using DataItemPosPayload = base::DataItemPosPayload;

using DataItemInt64Payload = base::DataItemInt64Payload;

using DataItemVec3Payload = base::DataItemVec3Payload;

using DataItemEntry = base::DataItemEntry;

using SynchedActorData = base::SynchedActorData;

using AddActorPacket = base::AddActorPacket;

using SetActorDataPacket = base::SetActorDataPacket;

enum class ActorType : int {
    Undefined = 1,
    TypeMask = 255,
    Mob = 256,
    PathfinderMob = 768,
    Monster = 2816,
    Animal = 4864,
    TamableAnimal = 21248,
    Ambient = 33024,
    UndeadMonster = 68352,
    ZombieMonster = 199424,
    Arthropod = 264960,
    Minecart = 524288,
    SkeletonMonster = 1116928,
    EquineAnimal = 2118400,
    Projectile = 4194304,
    AbstractArrow = 8388608,
    WaterAnimal = 8960,
    VillagerBase = 16777984,
    Chicken = 4874,
    Cow = 4875,
    Pig = 4876,
    Sheep = 4877,
    Wolf = 21262,
    Villager = 16777999,
    MushroomCow = 4880,
    Squid = 8977,
    Rabbit = 4882,
    Bat = 33043,
    IronGolem = 788,
    SnowGolem = 789,
    Ocelot = 21270,
    Horse = 2118423,
    PolarBear = 4892,
    Llama = 4893,
    Parrot = 21278,
    Dolphin = 8991,
    Donkey = 2118424,
    Mule = 2118425,
    SkeletonHorse = 2186010,
    ZombieHorse = 2186011,
    Zombie = 199456,
    Creeper = 2849,
    Skeleton = 1116962,
    Spider = 264995,
    PigZombie = 68388,
    Slime = 2853,
    EnderMan = 2854,
    Silverfish = 264999,
    CaveSpider = 265000,
    Ghast = 2857,
    LavaSlime = 2858,
    Blaze = 2859,
    ZombieVillager = 199468,
    Witch = 2861,
    Stray = 1116974,
    Husk = 199471,
    WitherSkeleton = 1116976,
    Guardian = 2865,
    ElderGuardian = 2866,
    Npc = 307,
    WitherBoss = 68404,
    Dragon = 2869,
    Shulker = 2870,
    Endermite = 265015,
    Agent = 312,
    Vindicator = 2873,
    Phantom = 68410,
    IllagerBeast = 2875,
    ArmorStand = 317,
    TripodCamera = 318,
    Player = 319,
    ItemEntity = 64,
    PrimedTnt = 65,
    FallingBlock = 66,
    MovingBlock = 67,
    ExperiencePotion = 4194372,
    Experience = 69,
    EyeOfEnder = 70,
    EnderCrystal = 71,
    FireworksRocket = 72,
    Trident = 12582985,
    Turtle = 4938,
    Cat = 21323,
    ShulkerBullet = 4194380,
    FishingHook = 77,
    Chalkboard = 78,
    DragonFireball = 4194383,
    Arrow = 12582992,
    Snowball = 4194385,
    ThrownEgg = 4194386,
    Painting = 83,
    LargeFireball = 4194389,
    ThrownPotion = 4194390,
    Enderpearl = 4194391,
    LeashKnot = 88,
    WitherSkull = 4194393,
    BoatRideable = 90,
    WitherSkullDangerous = 4194395,
    LightningBolt = 93,
    SmallFireball = 4194398,
    AreaEffectCloud = 95,
    LingeringPotion = 4194405,
    LlamaSpit = 4194406,
    EvocationFang = 4194407,
    EvocationIllager = 2920,
    Vex = 2921,
    MinecartRideable = 524372,
    MinecartHopper = 524384,
    MinecartTNT = 524385,
    MinecartChest = 524386,
    MinecartFurnace = 524387,
    MinecartCommandBlock = 524388,
    IceBomb = 4194410,
    Balloon = 107,
    Pufferfish = 9068,
    Salmon = 9069,
    Drowned = 199534,
    Tropicalfish = 9071,
    Fish = 9072,
    Panda = 4977,
    Pillager = 2930,
    VillagerV2 = 16778099,
    ZombieVillagerV2 = 199540,
    Shield = 117,
    WanderingTrader = 886,
    Lectern = 119,
    ElderGuardianGhost = 2936,
    Fox = 4985,
    Bee = 378,
    Piglin = 379,
    Hoglin = 4988,
    Strider = 4989,
    Zoglin = 68478,
    PiglinBrute = 383,
    Goat = 4992,
    GlowSquid = 9089,
    Axolotl = 4994,
    Warden = 2947,
    Frog = 4996,
    Tadpole = 9093,
    Allay = 390,
    ChestBoatRideable = 218,
    TraderLlama = 5021,
    Camel = 5002,
    Sniffer = 5003,
    Breeze = 2956,
    BreezeWindChargeProjectile = 4194445,
    Armadillo = 5006,
    WindChargeProjectile = 4194447,
    Bogged = 1117072,
    OminousItemSpawner = 145,
    Creaking = 2962,
    Nautilus = 9109,
    ZombieNautilus = 76694,
    Parched = 1117079,
    CamelHusk = 68504,
};

struct SetLastHurtByPacket {
    static constexpr int Id = 96;
    v766::ActorType last_hurt_by{};
};

using ActorEvent = base::ActorEvent;

using ActorEventPacket = base::ActorEventPacket;

using AnimatePacket = base::AnimatePacket;

using AddItemActorPacket = base::AddItemActorPacket;

}  // namespace v766

namespace v776 {

enum class ActorFlags : int {
    Onfire = 0,
    Sneaking = 1,
    Riding = 2,
    Sprinting = 3,
    Usingitem = 4,
    Invisible = 5,
    Tempted = 6,
    Inlove = 7,
    Saddled = 8,
    Powered = 9,
    Ignited = 10,
    Baby = 11,
    Converting = 12,
    Critical = 13,
    CanShowName = 14,
    AlwaysShowName = 15,
    Noai = 16,
    Silent = 17,
    Wallclimbing = 18,
    Canclimb = 19,
    Canswim = 20,
    Canfly = 21,
    Canwalk = 22,
    Resting = 23,
    Sitting = 24,
    Angry = 25,
    Interested = 26,
    Charged = 27,
    Tamed = 28,
    Orphaned = 29,
    Leashed = 30,
    Sheared = 31,
    Gliding = 32,
    Elder = 33,
    Moving = 34,
    Breathing = 35,
    Chested = 36,
    Stackable = 37,
    ShowBottom = 38,
    Standing = 39,
    Shaking = 40,
    Idling = 41,
    Casting = 42,
    Charging = 43,
    WasdControlled = 44,
    CanPowerJump = 45,
    CanDash = 46,
    Lingering = 47,
    HasCollision = 48,
    HasGravity = 49,
    FireImmune = 50,
    Dancing = 51,
    Enchanted = 52,
    Returntrident = 53,
    ContainerIsPrivate = 54,
    IsTransforming = 55,
    Damagenearbymobs = 56,
    Swimming = 57,
    Bribed = 58,
    IsPregnant = 59,
    LayingEgg = 60,
    PassengerCanPick = 61,
    TransitionSitting = 62,
    Eating = 63,
    LayingDown = 64,
    Sneezing = 65,
    Trusting = 66,
    Rolling = 67,
    Scared = 68,
    InScaffolding = 69,
    OverScaffolding = 70,
    DescendThroughBlock = 71,
    Blocking = 72,
    TransitionBlocking = 73,
    BlockedUsingShield = 74,
    BlockedUsingDamagedShield = 75,
    Sleeping = 76,
    WantsToWake = 77,
    TradeInterest = 78,
    DoorBreaker = 79,
    BreakingObstruction = 80,
    DoorOpener = 81,
    IsIllagerCaptain = 82,
    Stunned = 83,
    Roaring = 84,
    DelayedAttack = 85,
    IsAvoidingMobs = 86,
    IsAvoidingBlock = 87,
    FacingTargetToRangeAttack = 88,
    HiddenWhenInvisible = 89,
    IsInUi = 90,
    Stalking = 91,
    Emoting = 92,
    Celebrating = 93,
    Admiring = 94,
    CelebratingSpecial = 95,
    OutOfControl = 96,
    RamAttack = 97,
    PlayingDead = 98,
    InAscendableBlock = 99,
    OverDescendableBlock = 100,
    Croaking = 101,
    EatMob = 102,
    JumpGoalJump = 103,
    Emerging = 104,
    Sniffing = 105,
    Digging = 106,
    SonicBoom = 107,
    HasDashCooldown = 108,
    PushTowardsClosestSpace = 109,
    Deprecated1 = 110,
    Deprecated2 = 111,
    Deprecated3 = 112,
    Searching = 113,
    Crawling = 114,
    TimerFlag1 = 115,
    TimerFlag2 = 116,
    TimerFlag3 = 117,
    BodyRotationBlocked = 118,
    RendersWhenInvisible = 119,
    Count = 120,
};

enum class ActorDataIDs : std::uint8_t {
    Reserved0 = 0,
    StructuralIntegrity = 1,
    Variant = 2,
    ColorIndex = 3,
    Name = 4,
    Owner = 5,
    Target = 6,
    AirSupply = 7,
    EffectColor = 8,
    Reserved009 = 9,
    Reserved010 = 10,
    Hurt = 11,
    HurtDir = 12,
    RowTimeLeft = 13,
    RowTimeRight = 14,
    Value = 15,
    DisplayTileRuntimeId = 16,
    DisplayOffset = 17,
    CustomDisplay = 18,
    Swell = 19,
    OldSwell = 20,
    SwellDir = 21,
    ChargeAmount = 22,
    DeprecatedCarryBlockRuntimeId = 23,
    ClientEvent = 24,
    UsingItem = 25,
    PlayerFlags = 26,
    PlayerIndex = 27,
    BedPosition = 28,
    XPower = 29,
    YPower = 30,
    ZPower = 31,
    AuxPower = 32,
    Fishx = 33,
    Fishz = 34,
    Fishangle = 35,
    AuxValueData = 36,
    LeashHolder = 37,
    Reserved038 = 38,
    HasNpc = 39,
    NpcData = 40,
    Actions = 41,
    AirSupplyMax = 42,
    MarkVariant = 43,
    ContainerType = 44,
    ContainerSize = 45,
    ContainerStrengthModifier = 46,
    BlockTarget = 47,
    Inv = 48,
    TargetA = 49,
    TargetB = 50,
    TargetC = 51,
    AerialAttack = 52,
    Reserved053 = 53,
    Reserved054 = 54,
    FuseTime = 55,
    Reserved056 = 56,
    SeatLockPassengerRotation = 57,
    SeatLockPassengerRotationDegrees = 58,
    SeatRotationOffset = 59,
    SeatRotationOffsetDegrees = 60,
    DataRadius = 61,
    DataWaiting = 62,
    DataParticle = 63,
    PeekId = 64,
    AttachFace = 65,
    Attached = 66,
    AttachPos = 67,
    TradeTarget = 68,
    Career = 69,
    HasCommandBlock = 70,
    CommandName = 71,
    LastCommandOutput = 72,
    TrackCommandOutput = 73,
    Reserved074 = 74,
    Strength = 75,
    StrengthMax = 76,
    DataSpellCastingColor = 77,
    DataLifetimeTicks = 78,
    PoseIndex = 79,
    DataTickOffset = 80,
    NametagAlwaysShow = 81,
    Color2Index = 82,
    NameAuthor = 83,
    Score = 84,
    BalloonAnchor = 85,
    PuffedState = 86,
    BubbleTime = 87,
    Agent = 88,
    SittingAmount = 89,
    SittingAmountPrevious = 90,
    EatingCounter = 91,
    Reserved092 = 92,
    LayingAmount = 93,
    LayingAmountPrevious = 94,
    DataDuration = 95,
    DataSpawnTimeDeprecated = 96,
    DataChangeRate = 97,
    DataChangeOnPickup = 98,
    DataPickupCount = 99,
    InteractText = 100,
    TradeTier = 101,
    MaxTradeTier = 102,
    TradeExperience = 103,
    SkinId = 104,
    SpawningFrames = 105,
    CommandBlockTickDelay = 106,
    CommandBlockExecuteOnFirstTick = 107,
    AmbientSoundInterval = 108,
    AmbientSoundIntervalRange = 109,
    AmbientSoundEventName = 110,
    FallDamageMultiplier = 111,
    NameRawText = 112,
    CanRideTarget = 113,
    LowTierCuredTradeDiscount = 114,
    HighTierCuredTradeDiscount = 115,
    NearbyCuredTradeDiscount = 116,
    NearbyCuredDiscountTimeStamp = 117,
    Hitbox = 118,
    IsBuoyant = 119,
    FreezingEffectStrength = 120,
    BuoyancyData = 121,
    GoatHornCount = 122,
    BaseRuntimeId = 123,
    MovementSoundDistanceOffset = 124,
    HeartbeatIntervalTicks = 125,
    HeartbeatSoundEvent = 126,
    PlayerLastDeathPos = 127,
    PlayerLastDeathDimension = 128,
    PlayerHasDied = 129,
    CollisionBox = 130,
    VisibleMobEffects = 131,
    FilteredName = 132,
    EnterBedPosition = 133,
    Count = 134,
};

using DataItemBytePayload = base::DataItemBytePayload;

using DataItemShortPayload = base::DataItemShortPayload;

using DataItemIntPayload = base::DataItemIntPayload;

using DataItemFloatPayload = base::DataItemFloatPayload;

using DataItemStringPayload = base::DataItemStringPayload;

using DataItemCompoundTagPayload = base::DataItemCompoundTagPayload;

using DataItemPosPayload = base::DataItemPosPayload;

using DataItemInt64Payload = base::DataItemInt64Payload;

using DataItemVec3Payload = base::DataItemVec3Payload;

using DataItemEntry = base::DataItemEntry;

using SynchedActorData = base::SynchedActorData;

using AddActorPacket = base::AddActorPacket;

using SetActorDataPacket = base::SetActorDataPacket;

using ActorType = v766::ActorType;

using SetLastHurtByPacket = v766::SetLastHurtByPacket;

using ActorEvent = base::ActorEvent;

using ActorEventPacket = base::ActorEventPacket;

using AnimatePacket = base::AnimatePacket;

using AddItemActorPacket = base::AddItemActorPacket;

}  // namespace v776

namespace v786 {

enum class ActorFlags : int {
    Onfire = 0,
    Sneaking = 1,
    Riding = 2,
    Sprinting = 3,
    Usingitem = 4,
    Invisible = 5,
    Tempted = 6,
    Inlove = 7,
    Saddled = 8,
    Powered = 9,
    Ignited = 10,
    Baby = 11,
    Converting = 12,
    Critical = 13,
    CanShowName = 14,
    AlwaysShowName = 15,
    Noai = 16,
    Silent = 17,
    Wallclimbing = 18,
    Canclimb = 19,
    Canswim = 20,
    Canfly = 21,
    Canwalk = 22,
    Resting = 23,
    Sitting = 24,
    Angry = 25,
    Interested = 26,
    Charged = 27,
    Tamed = 28,
    Orphaned = 29,
    Leashed = 30,
    Sheared = 31,
    Gliding = 32,
    Elder = 33,
    Moving = 34,
    Breathing = 35,
    Chested = 36,
    Stackable = 37,
    ShowBottom = 38,
    Standing = 39,
    Shaking = 40,
    Idling = 41,
    Casting = 42,
    Charging = 43,
    WasdControlled = 44,
    CanPowerJump = 45,
    CanDash = 46,
    Lingering = 47,
    HasCollision = 48,
    HasGravity = 49,
    FireImmune = 50,
    Dancing = 51,
    Enchanted = 52,
    Returntrident = 53,
    ContainerIsPrivate = 54,
    IsTransforming = 55,
    Damagenearbymobs = 56,
    Swimming = 57,
    Bribed = 58,
    IsPregnant = 59,
    LayingEgg = 60,
    PassengerCanPick = 61,
    TransitionSitting = 62,
    Eating = 63,
    LayingDown = 64,
    Sneezing = 65,
    Trusting = 66,
    Rolling = 67,
    Scared = 68,
    InScaffolding = 69,
    OverScaffolding = 70,
    DescendThroughBlock = 71,
    Blocking = 72,
    TransitionBlocking = 73,
    BlockedUsingShield = 74,
    BlockedUsingDamagedShield = 75,
    Sleeping = 76,
    WantsToWake = 77,
    TradeInterest = 78,
    DoorBreaker = 79,
    BreakingObstruction = 80,
    DoorOpener = 81,
    IsIllagerCaptain = 82,
    Stunned = 83,
    Roaring = 84,
    DelayedAttack = 85,
    IsAvoidingMobs = 86,
    IsAvoidingBlock = 87,
    FacingTargetToRangeAttack = 88,
    HiddenWhenInvisible = 89,
    IsInUi = 90,
    Stalking = 91,
    Emoting = 92,
    Celebrating = 93,
    Admiring = 94,
    CelebratingSpecial = 95,
    OutOfControl = 96,
    RamAttack = 97,
    PlayingDead = 98,
    InAscendableBlock = 99,
    OverDescendableBlock = 100,
    Croaking = 101,
    EatMob = 102,
    JumpGoalJump = 103,
    Emerging = 104,
    Sniffing = 105,
    Digging = 106,
    SonicBoom = 107,
    HasDashCooldown = 108,
    PushTowardsClosestSpace = 109,
    Deprecated1 = 110,
    Deprecated2 = 111,
    Deprecated3 = 112,
    Searching = 113,
    Crawling = 114,
    TimerFlag1 = 115,
    TimerFlag2 = 116,
    TimerFlag3 = 117,
    BodyRotationBlocked = 118,
    RendersWhenInvisible = 119,
    RotationAxisAligned = 120,
    Collidable = 121,
    WasdFreeCameraControlled = 122,
    Count = 123,
};

using ActorDataIDs = v776::ActorDataIDs;

using DataItemBytePayload = base::DataItemBytePayload;

using DataItemShortPayload = base::DataItemShortPayload;

using DataItemIntPayload = base::DataItemIntPayload;

using DataItemFloatPayload = base::DataItemFloatPayload;

using DataItemStringPayload = base::DataItemStringPayload;

using DataItemCompoundTagPayload = base::DataItemCompoundTagPayload;

using DataItemPosPayload = base::DataItemPosPayload;

using DataItemInt64Payload = base::DataItemInt64Payload;

using DataItemVec3Payload = base::DataItemVec3Payload;

using DataItemEntry = base::DataItemEntry;

using SynchedActorData = base::SynchedActorData;

using AddActorPacket = base::AddActorPacket;

using SetActorDataPacket = base::SetActorDataPacket;

using ActorType = v766::ActorType;

using SetLastHurtByPacket = v766::SetLastHurtByPacket;

using ActorEvent = base::ActorEvent;

using ActorEventPacket = base::ActorEventPacket;

using AnimatePacket = base::AnimatePacket;

using AddItemActorPacket = base::AddItemActorPacket;

}  // namespace v786

namespace v800 {

enum class ActorFlags : int {
    Onfire = 0,
    Sneaking = 1,
    Riding = 2,
    Sprinting = 3,
    Usingitem = 4,
    Invisible = 5,
    Tempted = 6,
    Inlove = 7,
    Saddled = 8,
    Powered = 9,
    Ignited = 10,
    Baby = 11,
    Converting = 12,
    Critical = 13,
    CanShowName = 14,
    AlwaysShowName = 15,
    Noai = 16,
    Silent = 17,
    Wallclimbing = 18,
    Canclimb = 19,
    Canswim = 20,
    Canfly = 21,
    Canwalk = 22,
    Resting = 23,
    Sitting = 24,
    Angry = 25,
    Interested = 26,
    Charged = 27,
    Tamed = 28,
    Orphaned = 29,
    Leashed = 30,
    Sheared = 31,
    Gliding = 32,
    Elder = 33,
    Moving = 34,
    Breathing = 35,
    Chested = 36,
    Stackable = 37,
    ShowBottom = 38,
    Standing = 39,
    Shaking = 40,
    Idling = 41,
    Casting = 42,
    Charging = 43,
    WasdControlled = 44,
    CanPowerJump = 45,
    CanDash = 46,
    Lingering = 47,
    HasCollision = 48,
    HasGravity = 49,
    FireImmune = 50,
    Dancing = 51,
    Enchanted = 52,
    Returntrident = 53,
    ContainerIsPrivate = 54,
    IsTransforming = 55,
    Damagenearbymobs = 56,
    Swimming = 57,
    Bribed = 58,
    IsPregnant = 59,
    LayingEgg = 60,
    PassengerCanPick = 61,
    TransitionSitting = 62,
    Eating = 63,
    LayingDown = 64,
    Sneezing = 65,
    Trusting = 66,
    Rolling = 67,
    Scared = 68,
    InScaffolding = 69,
    OverScaffolding = 70,
    DescendThroughBlock = 71,
    Blocking = 72,
    TransitionBlocking = 73,
    BlockedUsingShield = 74,
    BlockedUsingDamagedShield = 75,
    Sleeping = 76,
    WantsToWake = 77,
    TradeInterest = 78,
    DoorBreaker = 79,
    BreakingObstruction = 80,
    DoorOpener = 81,
    IsIllagerCaptain = 82,
    Stunned = 83,
    Roaring = 84,
    DelayedAttack = 85,
    IsAvoidingMobs = 86,
    IsAvoidingBlock = 87,
    FacingTargetToRangeAttack = 88,
    HiddenWhenInvisible = 89,
    IsInUi = 90,
    Stalking = 91,
    Emoting = 92,
    Celebrating = 93,
    Admiring = 94,
    CelebratingSpecial = 95,
    OutOfControl = 96,
    RamAttack = 97,
    PlayingDead = 98,
    InAscendableBlock = 99,
    OverDescendableBlock = 100,
    Croaking = 101,
    EatMob = 102,
    JumpGoalJump = 103,
    Emerging = 104,
    Sniffing = 105,
    Digging = 106,
    SonicBoom = 107,
    HasDashCooldown = 108,
    PushTowardsClosestSpace = 109,
    Deprecated1 = 110,
    Deprecated2 = 111,
    Deprecated3 = 112,
    Searching = 113,
    Crawling = 114,
    TimerFlag1 = 115,
    TimerFlag2 = 116,
    TimerFlag3 = 117,
    BodyRotationBlocked = 118,
    RendersWhenInvisible = 119,
    RotationAxisAligned = 120,
    Collidable = 121,
    WasdFreeCameraControlled = 122,
    DoesServerAuthOnlyDismount = 123,
    Count = 124,
};

enum class ActorDataIDs : std::uint8_t {
    Reserved0 = 0,
    StructuralIntegrity = 1,
    Variant = 2,
    ColorIndex = 3,
    Name = 4,
    Owner = 5,
    Target = 6,
    AirSupply = 7,
    EffectColor = 8,
    Reserved009 = 9,
    Reserved010 = 10,
    Hurt = 11,
    HurtDir = 12,
    RowTimeLeft = 13,
    RowTimeRight = 14,
    Value = 15,
    DisplayTileRuntimeId = 16,
    DisplayOffset = 17,
    CustomDisplay = 18,
    Swell = 19,
    OldSwell = 20,
    SwellDir = 21,
    ChargeAmount = 22,
    DeprecatedCarryBlockRuntimeId = 23,
    ClientEvent = 24,
    UsingItem = 25,
    PlayerFlags = 26,
    PlayerIndex = 27,
    BedPosition = 28,
    XPower = 29,
    YPower = 30,
    ZPower = 31,
    AuxPower = 32,
    Fishx = 33,
    Fishz = 34,
    Fishangle = 35,
    AuxValueData = 36,
    LeashHolder = 37,
    Reserved038 = 38,
    HasNpc = 39,
    NpcData = 40,
    Actions = 41,
    AirSupplyMax = 42,
    MarkVariant = 43,
    ContainerType = 44,
    ContainerSize = 45,
    ContainerStrengthModifier = 46,
    BlockTarget = 47,
    Inv = 48,
    TargetA = 49,
    TargetB = 50,
    TargetC = 51,
    AerialAttack = 52,
    Reserved053 = 53,
    Reserved054 = 54,
    FuseTime = 55,
    Reserved056 = 56,
    SeatLockPassengerRotation = 57,
    SeatLockPassengerRotationDegrees = 58,
    SeatRotationOffset = 59,
    SeatRotationOffsetDegrees = 60,
    DataRadius = 61,
    DataWaiting = 62,
    DataParticle = 63,
    PeekId = 64,
    AttachFace = 65,
    Attached = 66,
    AttachPos = 67,
    TradeTarget = 68,
    Career = 69,
    HasCommandBlock = 70,
    CommandName = 71,
    LastCommandOutput = 72,
    TrackCommandOutput = 73,
    Reserved074 = 74,
    Strength = 75,
    StrengthMax = 76,
    DataSpellCastingColor = 77,
    DataLifetimeTicks = 78,
    PoseIndex = 79,
    DataTickOffset = 80,
    NametagAlwaysShow = 81,
    Color2Index = 82,
    NameAuthor = 83,
    Score = 84,
    BalloonAnchor = 85,
    PuffedState = 86,
    BubbleTime = 87,
    Agent = 88,
    SittingAmount = 89,
    SittingAmountPrevious = 90,
    EatingCounter = 91,
    Reserved092 = 92,
    LayingAmount = 93,
    LayingAmountPrevious = 94,
    DataDuration = 95,
    DataSpawnTimeDeprecated = 96,
    DataChangeRate = 97,
    DataChangeOnPickup = 98,
    DataPickupCount = 99,
    InteractText = 100,
    TradeTier = 101,
    MaxTradeTier = 102,
    TradeExperience = 103,
    SkinId = 104,
    SpawningFrames = 105,
    CommandBlockTickDelay = 106,
    CommandBlockExecuteOnFirstTick = 107,
    AmbientSoundInterval = 108,
    AmbientSoundIntervalRange = 109,
    AmbientSoundEventName = 110,
    FallDamageMultiplier = 111,
    NameRawText = 112,
    CanRideTarget = 113,
    LowTierCuredTradeDiscount = 114,
    HighTierCuredTradeDiscount = 115,
    NearbyCuredTradeDiscount = 116,
    NearbyCuredDiscountTimeStamp = 117,
    Hitbox = 118,
    IsBuoyant = 119,
    FreezingEffectStrength = 120,
    BuoyancyData = 121,
    GoatHornCount = 122,
    BaseRuntimeId = 123,
    MovementSoundDistanceOffset = 124,
    HeartbeatIntervalTicks = 125,
    HeartbeatSoundEvent = 126,
    PlayerLastDeathPos = 127,
    PlayerLastDeathDimension = 128,
    PlayerHasDied = 129,
    CollisionBox = 130,
    VisibleMobEffects = 131,
    FilteredName = 132,
    EnterBedPosition = 133,
    SeatThirdPersonCameraRadius = 134,
    SeatCameraRelaxDistanceSmoothing = 135,
    Count = 136,
};

using DataItemBytePayload = base::DataItemBytePayload;

using DataItemShortPayload = base::DataItemShortPayload;

using DataItemIntPayload = base::DataItemIntPayload;

using DataItemFloatPayload = base::DataItemFloatPayload;

using DataItemStringPayload = base::DataItemStringPayload;

using DataItemCompoundTagPayload = base::DataItemCompoundTagPayload;

using DataItemPosPayload = base::DataItemPosPayload;

using DataItemInt64Payload = base::DataItemInt64Payload;

using DataItemVec3Payload = base::DataItemVec3Payload;

using DataItemEntry = base::DataItemEntry;

using SynchedActorData = base::SynchedActorData;

using AddActorPacket = base::AddActorPacket;

using SetActorDataPacket = base::SetActorDataPacket;

enum class ActorType : int {
    Undefined = 1,
    TypeMask = 255,
    Mob = 256,
    PathfinderMob = 768,
    Monster = 2816,
    Animal = 4864,
    TamableAnimal = 21248,
    Ambient = 33024,
    UndeadMonster = 68352,
    ZombieMonster = 199424,
    Arthropod = 264960,
    Minecart = 524288,
    SkeletonMonster = 1116928,
    EquineAnimal = 2118400,
    Projectile = 4194304,
    AbstractArrow = 8388608,
    WaterAnimal = 8960,
    VillagerBase = 16777984,
    Chicken = 4874,
    Cow = 4875,
    Pig = 4876,
    Sheep = 4877,
    Wolf = 21262,
    Villager = 16777999,
    MushroomCow = 4880,
    Squid = 8977,
    Rabbit = 4882,
    Bat = 33043,
    IronGolem = 788,
    SnowGolem = 789,
    Ocelot = 21270,
    Horse = 2118423,
    PolarBear = 4892,
    Llama = 4893,
    Parrot = 21278,
    Dolphin = 8991,
    Donkey = 2118424,
    Mule = 2118425,
    SkeletonHorse = 2186010,
    ZombieHorse = 2186011,
    Zombie = 199456,
    Creeper = 2849,
    Skeleton = 1116962,
    Spider = 264995,
    PigZombie = 68388,
    Slime = 2853,
    EnderMan = 2854,
    Silverfish = 264999,
    CaveSpider = 265000,
    Ghast = 2857,
    LavaSlime = 2858,
    Blaze = 2859,
    ZombieVillager = 199468,
    Witch = 2861,
    Stray = 1116974,
    Husk = 199471,
    WitherSkeleton = 1116976,
    Guardian = 2865,
    ElderGuardian = 2866,
    Npc = 307,
    WitherBoss = 68404,
    Dragon = 2869,
    Shulker = 2870,
    Endermite = 265015,
    Agent = 312,
    Vindicator = 2873,
    Phantom = 68410,
    IllagerBeast = 2875,
    ArmorStand = 317,
    TripodCamera = 318,
    Player = 319,
    ItemEntity = 64,
    PrimedTnt = 65,
    FallingBlock = 66,
    MovingBlock = 67,
    ExperiencePotion = 4194372,
    Experience = 69,
    EyeOfEnder = 70,
    EnderCrystal = 71,
    FireworksRocket = 72,
    Trident = 12582985,
    Turtle = 4938,
    Cat = 21323,
    ShulkerBullet = 4194380,
    FishingHook = 77,
    Chalkboard = 78,
    DragonFireball = 4194383,
    Arrow = 12582992,
    Snowball = 4194385,
    ThrownEgg = 4194386,
    Painting = 83,
    LargeFireball = 4194389,
    ThrownPotion = 4194390,
    Enderpearl = 4194391,
    LeashKnot = 88,
    WitherSkull = 4194393,
    BoatRideable = 90,
    WitherSkullDangerous = 4194395,
    LightningBolt = 93,
    SmallFireball = 4194398,
    AreaEffectCloud = 95,
    LingeringPotion = 4194405,
    LlamaSpit = 4194406,
    EvocationFang = 4194407,
    EvocationIllager = 2920,
    Vex = 2921,
    MinecartRideable = 524372,
    MinecartHopper = 524384,
    MinecartTNT = 524385,
    MinecartChest = 524386,
    MinecartFurnace = 524387,
    MinecartCommandBlock = 524388,
    IceBomb = 4194410,
    Balloon = 107,
    Pufferfish = 9068,
    Salmon = 9069,
    Drowned = 199534,
    Tropicalfish = 9071,
    Fish = 9072,
    Panda = 4977,
    Pillager = 2930,
    VillagerV2 = 16778099,
    ZombieVillagerV2 = 199540,
    Shield = 117,
    WanderingTrader = 886,
    Lectern = 119,
    ElderGuardianGhost = 2936,
    Fox = 4985,
    Bee = 378,
    Piglin = 379,
    Hoglin = 4988,
    Strider = 4989,
    Zoglin = 68478,
    PiglinBrute = 383,
    Goat = 4992,
    GlowSquid = 9089,
    Axolotl = 4994,
    Warden = 2947,
    Frog = 4996,
    Tadpole = 9093,
    Allay = 390,
    ChestBoatRideable = 218,
    TraderLlama = 5021,
    Camel = 5002,
    Sniffer = 5003,
    Breeze = 2956,
    BreezeWindChargeProjectile = 4194445,
    Armadillo = 5006,
    WindChargeProjectile = 4194447,
    Bogged = 1117072,
    OminousItemSpawner = 145,
    Creaking = 2962,
    HappyGhast = 5011,
    Nautilus = 9109,
    ZombieNautilus = 76694,
    Parched = 1117079,
    CamelHusk = 68504,
};

struct SetLastHurtByPacket {
    static constexpr int Id = 96;
    v800::ActorType last_hurt_by{};
};

using ActorEvent = base::ActorEvent;

using ActorEventPacket = base::ActorEventPacket;

namespace AnimatePacket_nested {

enum class Action : std::uint8_t {
    NoAction = 0,
    Swing = 1,
    WakeUp = 3,
    CriticalHit = 4,
    MagicCriticalHit = 5,
};

}  // namespace AnimatePacket_nested

struct AnimatePacket {
    using Action = AnimatePacket_nested::Action;

    static constexpr int Id = 44;
    std::int32_t action{};
    ActorRuntimeID runtime_id{};
    float data{};
};

using AddItemActorPacket = base::AddItemActorPacket;

}  // namespace v800

namespace v818 {

enum class ActorFlags : int {
    Onfire = 0,
    Sneaking = 1,
    Riding = 2,
    Sprinting = 3,
    Usingitem = 4,
    Invisible = 5,
    Tempted = 6,
    Inlove = 7,
    Saddled = 8,
    Powered = 9,
    Ignited = 10,
    Baby = 11,
    Converting = 12,
    Critical = 13,
    CanShowName = 14,
    AlwaysShowName = 15,
    Noai = 16,
    Silent = 17,
    Wallclimbing = 18,
    Canclimb = 19,
    Canswim = 20,
    Canfly = 21,
    Canwalk = 22,
    Resting = 23,
    Sitting = 24,
    Angry = 25,
    Interested = 26,
    Charged = 27,
    Tamed = 28,
    Orphaned = 29,
    Leashed = 30,
    Sheared = 31,
    Gliding = 32,
    Elder = 33,
    Moving = 34,
    Breathing = 35,
    Chested = 36,
    Stackable = 37,
    ShowBottom = 38,
    Standing = 39,
    Shaking = 40,
    Idling = 41,
    Casting = 42,
    Charging = 43,
    WasdControlled = 44,
    CanPowerJump = 45,
    CanDash = 46,
    Lingering = 47,
    HasCollision = 48,
    HasGravity = 49,
    FireImmune = 50,
    Dancing = 51,
    Enchanted = 52,
    Returntrident = 53,
    ContainerIsPrivate = 54,
    IsTransforming = 55,
    Damagenearbymobs = 56,
    Swimming = 57,
    Bribed = 58,
    IsPregnant = 59,
    LayingEgg = 60,
    PassengerCanPick = 61,
    TransitionSitting = 62,
    Eating = 63,
    LayingDown = 64,
    Sneezing = 65,
    Trusting = 66,
    Rolling = 67,
    Scared = 68,
    InScaffolding = 69,
    OverScaffolding = 70,
    DescendThroughBlock = 71,
    Blocking = 72,
    TransitionBlocking = 73,
    BlockedUsingShield = 74,
    BlockedUsingDamagedShield = 75,
    Sleeping = 76,
    WantsToWake = 77,
    TradeInterest = 78,
    DoorBreaker = 79,
    BreakingObstruction = 80,
    DoorOpener = 81,
    IsIllagerCaptain = 82,
    Stunned = 83,
    Roaring = 84,
    DelayedAttack = 85,
    IsAvoidingMobs = 86,
    IsAvoidingBlock = 87,
    FacingTargetToRangeAttack = 88,
    HiddenWhenInvisible = 89,
    IsInUi = 90,
    Stalking = 91,
    Emoting = 92,
    Celebrating = 93,
    Admiring = 94,
    CelebratingSpecial = 95,
    OutOfControl = 96,
    RamAttack = 97,
    PlayingDead = 98,
    InAscendableBlock = 99,
    OverDescendableBlock = 100,
    Croaking = 101,
    EatMob = 102,
    JumpGoalJump = 103,
    Emerging = 104,
    Sniffing = 105,
    Digging = 106,
    SonicBoom = 107,
    HasDashCooldown = 108,
    PushTowardsClosestSpace = 109,
    Deprecated1 = 110,
    Deprecated2 = 111,
    Deprecated3 = 112,
    Searching = 113,
    Crawling = 114,
    TimerFlag1 = 115,
    TimerFlag2 = 116,
    TimerFlag3 = 117,
    BodyRotationBlocked = 118,
    RendersWhenInvisible = 119,
    RotationAxisAligned = 120,
    Collidable = 121,
    WasdFreeCameraControlled = 122,
    DoesServerAuthOnlyDismount = 123,
    BodyRotationAlwaysFollowsHead = 124,
    Count = 125,
};

using ActorDataIDs = v800::ActorDataIDs;

using DataItemBytePayload = base::DataItemBytePayload;

using DataItemShortPayload = base::DataItemShortPayload;

using DataItemIntPayload = base::DataItemIntPayload;

using DataItemFloatPayload = base::DataItemFloatPayload;

using DataItemStringPayload = base::DataItemStringPayload;

using DataItemCompoundTagPayload = base::DataItemCompoundTagPayload;

using DataItemPosPayload = base::DataItemPosPayload;

using DataItemInt64Payload = base::DataItemInt64Payload;

using DataItemVec3Payload = base::DataItemVec3Payload;

using DataItemEntry = base::DataItemEntry;

using SynchedActorData = base::SynchedActorData;

using AddActorPacket = base::AddActorPacket;

using SetActorDataPacket = base::SetActorDataPacket;

using ActorType = v800::ActorType;

using SetLastHurtByPacket = v800::SetLastHurtByPacket;

using ActorEvent = base::ActorEvent;

using ActorEventPacket = base::ActorEventPacket;

using AnimatePacket = v800::AnimatePacket;

using AddItemActorPacket = base::AddItemActorPacket;

}  // namespace v818

namespace v827 {

using ActorFlags = v818::ActorFlags;

using ActorDataIDs = v800::ActorDataIDs;

using DataItemBytePayload = base::DataItemBytePayload;

using DataItemShortPayload = base::DataItemShortPayload;

using DataItemIntPayload = base::DataItemIntPayload;

using DataItemFloatPayload = base::DataItemFloatPayload;

using DataItemStringPayload = base::DataItemStringPayload;

using DataItemCompoundTagPayload = base::DataItemCompoundTagPayload;

using DataItemPosPayload = base::DataItemPosPayload;

using DataItemInt64Payload = base::DataItemInt64Payload;

using DataItemVec3Payload = base::DataItemVec3Payload;

using DataItemEntry = base::DataItemEntry;

using SynchedActorData = base::SynchedActorData;

using AddActorPacket = base::AddActorPacket;

using SetActorDataPacket = base::SetActorDataPacket;

enum class ActorType : int {
    Undefined = 1,
    TypeMask = 255,
    Mob = 256,
    PathfinderMob = 768,
    Monster = 2816,
    Animal = 4864,
    TamableAnimal = 21248,
    Ambient = 33024,
    UndeadMonster = 68352,
    ZombieMonster = 199424,
    Arthropod = 264960,
    Minecart = 524288,
    SkeletonMonster = 1116928,
    EquineAnimal = 2118400,
    Projectile = 4194304,
    AbstractArrow = 8388608,
    WaterAnimal = 8960,
    VillagerBase = 16777984,
    Chicken = 4874,
    Cow = 4875,
    Pig = 4876,
    Sheep = 4877,
    Wolf = 21262,
    Villager = 16777999,
    MushroomCow = 4880,
    Squid = 8977,
    Rabbit = 4882,
    Bat = 33043,
    IronGolem = 788,
    SnowGolem = 789,
    Ocelot = 21270,
    Horse = 2118423,
    PolarBear = 4892,
    Llama = 4893,
    Parrot = 21278,
    Dolphin = 8991,
    Donkey = 2118424,
    Mule = 2118425,
    SkeletonHorse = 2186010,
    ZombieHorse = 2186011,
    Zombie = 199456,
    Creeper = 2849,
    Skeleton = 1116962,
    Spider = 264995,
    PigZombie = 68388,
    Slime = 2853,
    EnderMan = 2854,
    Silverfish = 264999,
    CaveSpider = 265000,
    Ghast = 2857,
    LavaSlime = 2858,
    Blaze = 2859,
    ZombieVillager = 199468,
    Witch = 2861,
    Stray = 1116974,
    Husk = 199471,
    WitherSkeleton = 1116976,
    Guardian = 2865,
    ElderGuardian = 2866,
    Npc = 307,
    WitherBoss = 68404,
    Dragon = 2869,
    Shulker = 2870,
    Endermite = 265015,
    Agent = 312,
    Vindicator = 2873,
    Phantom = 68410,
    IllagerBeast = 2875,
    ArmorStand = 317,
    TripodCamera = 318,
    Player = 319,
    ItemEntity = 64,
    PrimedTnt = 65,
    FallingBlock = 66,
    MovingBlock = 67,
    ExperiencePotion = 4194372,
    Experience = 69,
    EyeOfEnder = 70,
    EnderCrystal = 71,
    FireworksRocket = 72,
    Trident = 12582985,
    Turtle = 4938,
    Cat = 21323,
    ShulkerBullet = 4194380,
    FishingHook = 77,
    Chalkboard = 78,
    DragonFireball = 4194383,
    Arrow = 12582992,
    Snowball = 4194385,
    ThrownEgg = 4194386,
    Painting = 83,
    LargeFireball = 4194389,
    ThrownPotion = 4194390,
    Enderpearl = 4194391,
    LeashKnot = 88,
    WitherSkull = 4194393,
    BoatRideable = 90,
    WitherSkullDangerous = 4194395,
    LightningBolt = 93,
    SmallFireball = 4194398,
    AreaEffectCloud = 95,
    LingeringPotion = 4194405,
    LlamaSpit = 4194406,
    EvocationFang = 4194407,
    EvocationIllager = 2920,
    Vex = 2921,
    MinecartRideable = 524372,
    MinecartHopper = 524384,
    MinecartTNT = 524385,
    MinecartChest = 524386,
    MinecartFurnace = 524387,
    MinecartCommandBlock = 524388,
    IceBomb = 4194410,
    Balloon = 107,
    Pufferfish = 9068,
    Salmon = 9069,
    Drowned = 199534,
    Tropicalfish = 9071,
    Fish = 9072,
    Panda = 4977,
    Pillager = 2930,
    VillagerV2 = 16778099,
    ZombieVillagerV2 = 199540,
    Shield = 117,
    WanderingTrader = 886,
    Lectern = 119,
    ElderGuardianGhost = 2936,
    Fox = 4985,
    Bee = 378,
    Piglin = 379,
    Hoglin = 4988,
    Strider = 4989,
    Zoglin = 68478,
    PiglinBrute = 383,
    Goat = 4992,
    GlowSquid = 9089,
    Axolotl = 4994,
    Warden = 2947,
    Frog = 4996,
    Tadpole = 9093,
    Allay = 390,
    ChestBoatRideable = 218,
    TraderLlama = 5021,
    Camel = 5002,
    Sniffer = 5003,
    Breeze = 2956,
    BreezeWindChargeProjectile = 4194445,
    Armadillo = 5006,
    WindChargeProjectile = 4194447,
    Bogged = 1117072,
    OminousItemSpawner = 145,
    Creaking = 2962,
    HappyGhast = 5011,
    CopperGolem = 916,
    Nautilus = 9109,
    ZombieNautilus = 76694,
    Parched = 1117079,
    CamelHusk = 68504,
};

struct SetLastHurtByPacket {
    static constexpr int Id = 96;
    v827::ActorType last_hurt_by{};
};

using ActorEvent = base::ActorEvent;

using ActorEventPacket = base::ActorEventPacket;

using AnimatePacket = v800::AnimatePacket;

using AddItemActorPacket = base::AddItemActorPacket;

}  // namespace v827

namespace v844 {

enum class ActorFlags : int {
    Onfire = 0,
    Sneaking = 1,
    Riding = 2,
    Sprinting = 3,
    Usingitem = 4,
    Invisible = 5,
    Tempted = 6,
    Inlove = 7,
    Saddled = 8,
    Powered = 9,
    Ignited = 10,
    Baby = 11,
    Converting = 12,
    Critical = 13,
    CanShowName = 14,
    AlwaysShowName = 15,
    Noai = 16,
    Silent = 17,
    Wallclimbing = 18,
    Canclimb = 19,
    Canswim = 20,
    Canfly = 21,
    Canwalk = 22,
    Resting = 23,
    Sitting = 24,
    Angry = 25,
    Interested = 26,
    Charged = 27,
    Tamed = 28,
    Orphaned = 29,
    Leashed = 30,
    Sheared = 31,
    Gliding = 32,
    Elder = 33,
    Moving = 34,
    Breathing = 35,
    Chested = 36,
    Stackable = 37,
    ShowBottom = 38,
    Standing = 39,
    Shaking = 40,
    Idling = 41,
    Casting = 42,
    Charging = 43,
    WasdControlled = 44,
    CanPowerJump = 45,
    CanDash = 46,
    Lingering = 47,
    HasCollision = 48,
    HasGravity = 49,
    FireImmune = 50,
    Dancing = 51,
    Enchanted = 52,
    Returntrident = 53,
    ContainerIsPrivate = 54,
    IsTransforming = 55,
    Damagenearbymobs = 56,
    Swimming = 57,
    Bribed = 58,
    IsPregnant = 59,
    LayingEgg = 60,
    PassengerCanPick = 61,
    TransitionSitting = 62,
    Eating = 63,
    LayingDown = 64,
    Sneezing = 65,
    Trusting = 66,
    Rolling = 67,
    Scared = 68,
    InScaffolding = 69,
    OverScaffolding = 70,
    DescendThroughBlock = 71,
    Blocking = 72,
    TransitionBlocking = 73,
    BlockedUsingShield = 74,
    BlockedUsingDamagedShield = 75,
    Sleeping = 76,
    WantsToWake = 77,
    TradeInterest = 78,
    DoorBreaker = 79,
    BreakingObstruction = 80,
    DoorOpener = 81,
    IsIllagerCaptain = 82,
    Stunned = 83,
    Roaring = 84,
    DelayedAttack = 85,
    IsAvoidingMobs = 86,
    IsAvoidingBlock = 87,
    FacingTargetToRangeAttack = 88,
    HiddenWhenInvisible = 89,
    IsInUi = 90,
    Stalking = 91,
    Emoting = 92,
    Celebrating = 93,
    Admiring = 94,
    CelebratingSpecial = 95,
    OutOfControl = 96,
    RamAttack = 97,
    PlayingDead = 98,
    InAscendableBlock = 99,
    OverDescendableBlock = 100,
    Croaking = 101,
    EatMob = 102,
    JumpGoalJump = 103,
    Emerging = 104,
    Sniffing = 105,
    Digging = 106,
    SonicBoom = 107,
    HasDashCooldown = 108,
    PushTowardsClosestSpace = 109,
    Deprecated1 = 110,
    Deprecated2 = 111,
    Deprecated3 = 112,
    Searching = 113,
    Crawling = 114,
    TimerFlag1 = 115,
    TimerFlag2 = 116,
    TimerFlag3 = 117,
    BodyRotationBlocked = 118,
    RendersWhenInvisible = 119,
    RotationAxisAligned = 120,
    Collidable = 121,
    WasdFreeCameraControlled = 122,
    DoesServerAuthOnlyDismount = 123,
    BodyRotationAlwaysFollowsHead = 124,
    CanUseVerticalMovementAction = 125,
    Count = 126,
};

using ActorDataIDs = v800::ActorDataIDs;

using DataItemBytePayload = base::DataItemBytePayload;

using DataItemShortPayload = base::DataItemShortPayload;

using DataItemIntPayload = base::DataItemIntPayload;

using DataItemFloatPayload = base::DataItemFloatPayload;

using DataItemStringPayload = base::DataItemStringPayload;

using DataItemCompoundTagPayload = base::DataItemCompoundTagPayload;

using DataItemPosPayload = base::DataItemPosPayload;

using DataItemInt64Payload = base::DataItemInt64Payload;

using DataItemVec3Payload = base::DataItemVec3Payload;

using DataItemEntry = base::DataItemEntry;

using SynchedActorData = base::SynchedActorData;

using AddActorPacket = base::AddActorPacket;

using SetActorDataPacket = base::SetActorDataPacket;

using ActorType = v827::ActorType;

using SetLastHurtByPacket = v827::SetLastHurtByPacket;

using ActorEvent = base::ActorEvent;

using ActorEventPacket = base::ActorEventPacket;

using AnimatePacket = v800::AnimatePacket;

using AddItemActorPacket = base::AddItemActorPacket;

}  // namespace v844

namespace v859 {

using ActorFlags = v844::ActorFlags;

using ActorDataIDs = v800::ActorDataIDs;

using DataItemBytePayload = base::DataItemBytePayload;

using DataItemShortPayload = base::DataItemShortPayload;

using DataItemIntPayload = base::DataItemIntPayload;

using DataItemFloatPayload = base::DataItemFloatPayload;

using DataItemStringPayload = base::DataItemStringPayload;

using DataItemCompoundTagPayload = base::DataItemCompoundTagPayload;

using DataItemPosPayload = base::DataItemPosPayload;

using DataItemInt64Payload = base::DataItemInt64Payload;

using DataItemVec3Payload = base::DataItemVec3Payload;

using DataItemEntry = base::DataItemEntry;

using SynchedActorData = base::SynchedActorData;

using AddActorPacket = base::AddActorPacket;

using SetActorDataPacket = base::SetActorDataPacket;

using ActorType = v827::ActorType;

using SetLastHurtByPacket = v827::SetLastHurtByPacket;

enum class ActorEvent : std::uint8_t {
    None = 0,
    Jump = 1,
    Hurt = 2,
    Death = 3,
    StartAttacking = 4,
    StopAttacking = 5,
    TamingFailed = 6,
    TamingSucceeded = 7,
    ShakeWetness = 8,
    EatGrass = 10,
    FishhookBubble = 11,
    FishhookFishpos = 12,
    FishhookHooktime = 13,
    FishhookTease = 14,
    SquidFleeing = 15,
    ZombieConverting = 16,
    PlayAmbient = 17,
    SpawnAlive = 18,
    StartOfferFlower = 19,
    StopOfferFlower = 20,
    LoveHearts = 21,
    VillagerAngry = 22,
    VillagerHappy = 23,
    WitchHatMagic = 24,
    FireworksExplode = 25,
    InLoveHearts = 26,
    SilverfishMergeAnim = 27,
    GuardianAttackSound = 28,
    DrinkPotion = 29,
    ThrowPotion = 30,
    PrimeTntcart = 31,
    PrimeCreeper = 32,
    AirSupply = 33,
    DeprecatedAddPlayerLevels = 34,
    GuardianMiningFatigue = 35,
    AgentSwingArm = 36,
    DragonStartDeathAnim = 37,
    GroundDust = 38,
    Shake = 39,
    Feed = 57,
    BabyAge = 60,
    InstantDeath = 61,
    NotifyTrade = 62,
    LeashDestroyed = 63,
    CaravanUpdated = 64,
    TalismanActivate = 65,
    DeprecatedUpdateStructureFeature = 66,
    PlayerSpawnedMob = 67,
    Puke = 68,
    UpdateStackSize = 69,
    StartSwimming = 70,
    BalloonPop = 71,
    TreasureHunt = 72,
    SummonAgent = 73,
    FinishedChargingItem = 74,
    ActorGrowUp = 76,
    VibrationDetected = 77,
    DrinkMilk = 78,
    ShakeWetnessStop = 79,
};

struct ActorEventPacket {
    static constexpr int Id = 27;
    ActorRuntimeID runtime_id{};
    v859::ActorEvent event_id{};
    std::int32_t data{};
};

namespace AnimatePacket_nested {

enum class Action : std::uint8_t {
    NoAction = 0,
    Swing = 1,
    WakeUp = 3,
    CriticalHit = 4,
    MagicCriticalHit = 5,
};

}  // namespace AnimatePacket_nested

struct AnimatePacket {
    using Action = AnimatePacket_nested::Action;

    static constexpr int Id = 44;
    std::int32_t action{};
    ActorRuntimeID runtime_id{};
    float data{};
    float rowing_time{};
};

using AddItemActorPacket = base::AddItemActorPacket;

}  // namespace v859

namespace v898 {

enum class ActorFlags : int {
    Onfire = 0,
    Sneaking = 1,
    Riding = 2,
    Sprinting = 3,
    Usingitem = 4,
    Invisible = 5,
    Tempted = 6,
    Inlove = 7,
    Saddled = 8,
    Powered = 9,
    Ignited = 10,
    Baby = 11,
    Converting = 12,
    Critical = 13,
    CanShowName = 14,
    AlwaysShowName = 15,
    Noai = 16,
    Silent = 17,
    Wallclimbing = 18,
    Canclimb = 19,
    Canswim = 20,
    Canfly = 21,
    Canwalk = 22,
    Resting = 23,
    Sitting = 24,
    Angry = 25,
    Interested = 26,
    Charged = 27,
    Tamed = 28,
    Orphaned = 29,
    Leashed = 30,
    Sheared = 31,
    Gliding = 32,
    Elder = 33,
    Moving = 34,
    Breathing = 35,
    Chested = 36,
    Stackable = 37,
    ShowBottom = 38,
    Standing = 39,
    Shaking = 40,
    Idling = 41,
    Casting = 42,
    Charging = 43,
    WasdControlled = 44,
    CanPowerJump = 45,
    CanDash = 46,
    Lingering = 47,
    HasCollision = 48,
    HasGravity = 49,
    FireImmune = 50,
    Dancing = 51,
    Enchanted = 52,
    Returntrident = 53,
    ContainerIsPrivate = 54,
    IsTransforming = 55,
    Damagenearbymobs = 56,
    Swimming = 57,
    Bribed = 58,
    IsPregnant = 59,
    LayingEgg = 60,
    PassengerCanPick = 61,
    TransitionSitting = 62,
    Eating = 63,
    LayingDown = 64,
    Sneezing = 65,
    Trusting = 66,
    Rolling = 67,
    Scared = 68,
    InScaffolding = 69,
    OverScaffolding = 70,
    DescendThroughBlock = 71,
    Blocking = 72,
    TransitionBlocking = 73,
    BlockedUsingShield = 74,
    BlockedUsingDamagedShield = 75,
    Sleeping = 76,
    WantsToWake = 77,
    TradeInterest = 78,
    DoorBreaker = 79,
    BreakingObstruction = 80,
    DoorOpener = 81,
    IsIllagerCaptain = 82,
    Stunned = 83,
    Roaring = 84,
    DelayedAttack = 85,
    IsAvoidingMobs = 86,
    IsAvoidingBlock = 87,
    FacingTargetToRangeAttack = 88,
    HiddenWhenInvisible = 89,
    IsInUi = 90,
    Stalking = 91,
    Emoting = 92,
    Celebrating = 93,
    Admiring = 94,
    CelebratingSpecial = 95,
    OutOfControl = 96,
    RamAttack = 97,
    PlayingDead = 98,
    InAscendableBlock = 99,
    OverDescendableBlock = 100,
    Croaking = 101,
    EatMob = 102,
    JumpGoalJump = 103,
    Emerging = 104,
    Sniffing = 105,
    Digging = 106,
    SonicBoom = 107,
    HasDashCooldown = 108,
    PushTowardsClosestSpace = 109,
    Deprecated1 = 110,
    Deprecated2 = 111,
    Deprecated3 = 112,
    Searching = 113,
    Crawling = 114,
    TimerFlag1 = 115,
    TimerFlag2 = 116,
    TimerFlag3 = 117,
    BodyRotationBlocked = 118,
    RendersWhenInvisible = 119,
    RotationAxisAligned = 120,
    Collidable = 121,
    WasdFreeCameraControlled = 122,
    DoesServerAuthOnlyDismount = 123,
    BodyRotationAlwaysFollowsHead = 124,
    CanUseVerticalMovementAction = 125,
    RotationLockedToVehicle = 126,
    Count = 127,
};

using ActorDataIDs = v800::ActorDataIDs;

using DataItemBytePayload = base::DataItemBytePayload;

using DataItemShortPayload = base::DataItemShortPayload;

using DataItemIntPayload = base::DataItemIntPayload;

using DataItemFloatPayload = base::DataItemFloatPayload;

using DataItemStringPayload = base::DataItemStringPayload;

using DataItemCompoundTagPayload = base::DataItemCompoundTagPayload;

using DataItemPosPayload = base::DataItemPosPayload;

using DataItemInt64Payload = base::DataItemInt64Payload;

using DataItemVec3Payload = base::DataItemVec3Payload;

using DataItemEntry = base::DataItemEntry;

using SynchedActorData = base::SynchedActorData;

using AddActorPacket = base::AddActorPacket;

using SetActorDataPacket = base::SetActorDataPacket;

using ActorType = v827::ActorType;

using SetLastHurtByPacket = v827::SetLastHurtByPacket;

enum class ActorEvent : std::uint8_t {
    None = 0,
    Jump = 1,
    Hurt = 2,
    Death = 3,
    StartAttacking = 4,
    StopAttacking = 5,
    TamingFailed = 6,
    TamingSucceeded = 7,
    ShakeWetness = 8,
    EatGrass = 10,
    FishhookBubble = 11,
    FishhookFishpos = 12,
    FishhookHooktime = 13,
    FishhookTease = 14,
    SquidFleeing = 15,
    ZombieConverting = 16,
    PlayAmbient = 17,
    SpawnAlive = 18,
    StartOfferFlower = 19,
    StopOfferFlower = 20,
    LoveHearts = 21,
    VillagerAngry = 22,
    VillagerHappy = 23,
    WitchHatMagic = 24,
    FireworksExplode = 25,
    InLoveHearts = 26,
    SilverfishMergeAnim = 27,
    GuardianAttackSound = 28,
    DrinkPotion = 29,
    ThrowPotion = 30,
    PrimeTntcart = 31,
    PrimeCreeper = 32,
    AirSupply = 33,
    DeprecatedAddPlayerLevels = 34,
    GuardianMiningFatigue = 35,
    AgentSwingArm = 36,
    DragonStartDeathAnim = 37,
    GroundDust = 38,
    Shake = 39,
    Feed = 57,
    BabyAge = 60,
    InstantDeath = 61,
    NotifyTrade = 62,
    LeashDestroyed = 63,
    CaravanUpdated = 64,
    TalismanActivate = 65,
    DeprecatedUpdateStructureFeature = 66,
    PlayerSpawnedMob = 67,
    Puke = 68,
    UpdateStackSize = 69,
    StartSwimming = 70,
    BalloonPop = 71,
    TreasureHunt = 72,
    SummonAgent = 73,
    FinishedChargingItem = 74,
    ActorGrowUp = 76,
    VibrationDetected = 77,
    DrinkMilk = 78,
    ShakeWetnessStop = 79,
    KineticDamageDealt = 80,
};

struct ActorEventPacket {
    static constexpr int Id = 27;
    ActorRuntimeID runtime_id{};
    v898::ActorEvent event_id{};
    std::int32_t data{};
};

namespace AnimatePacket_nested {

enum class Action : std::uint8_t {
    NoAction = 0,
    Swing = 1,
    WakeUp = 3,
    CriticalHit = 4,
    MagicCriticalHit = 5,
};

}  // namespace AnimatePacket_nested

struct AnimatePacket {
    using Action = AnimatePacket_nested::Action;

    static constexpr int Id = 44;
    v898::AnimatePacket::Action action{};
    ActorRuntimeID runtime_id{};
    float data{};
    std::optional<ActorSwingSource> swing_source{};
};

using AddItemActorPacket = base::AddItemActorPacket;

}  // namespace v898

namespace v924 {

using ActorFlags = v898::ActorFlags;

enum class ActorDataIDs : std::uint8_t {
    Reserved0 = 0,
    StructuralIntegrity = 1,
    Variant = 2,
    ColorIndex = 3,
    Name = 4,
    Owner = 5,
    Target = 6,
    AirSupply = 7,
    EffectColor = 8,
    Reserved009 = 9,
    Reserved010 = 10,
    Hurt = 11,
    HurtDir = 12,
    RowTimeLeft = 13,
    RowTimeRight = 14,
    Value = 15,
    DisplayTileRuntimeId = 16,
    DisplayOffset = 17,
    CustomDisplay = 18,
    Swell = 19,
    OldSwell = 20,
    SwellDir = 21,
    ChargeAmount = 22,
    DeprecatedCarryBlockRuntimeId = 23,
    ClientEvent = 24,
    UsingItem = 25,
    PlayerFlags = 26,
    PlayerIndex = 27,
    BedPosition = 28,
    XPower = 29,
    YPower = 30,
    ZPower = 31,
    AuxPower = 32,
    Fishx = 33,
    Fishz = 34,
    Fishangle = 35,
    AuxValueData = 36,
    LeashHolder = 37,
    Reserved038 = 38,
    HasNpc = 39,
    NpcData = 40,
    Actions = 41,
    AirSupplyMax = 42,
    MarkVariant = 43,
    ContainerType = 44,
    ContainerSize = 45,
    ContainerStrengthModifier = 46,
    BlockTarget = 47,
    Inv = 48,
    TargetA = 49,
    TargetB = 50,
    TargetC = 51,
    AerialAttack = 52,
    Reserved053 = 53,
    Reserved054 = 54,
    FuseTime = 55,
    Reserved056 = 56,
    SeatLockPassengerRotation = 57,
    SeatLockPassengerRotationDegrees = 58,
    SeatRotationOffset = 59,
    SeatRotationOffsetDegrees = 60,
    DataRadius = 61,
    DataWaiting = 62,
    DataParticle = 63,
    PeekId = 64,
    AttachFace = 65,
    Attached = 66,
    AttachPos = 67,
    TradeTarget = 68,
    Career = 69,
    HasCommandBlock = 70,
    CommandName = 71,
    LastCommandOutput = 72,
    TrackCommandOutput = 73,
    Reserved074 = 74,
    Strength = 75,
    StrengthMax = 76,
    DataSpellCastingColor = 77,
    DataLifetimeTicks = 78,
    PoseIndex = 79,
    DataTickOffset = 80,
    NametagAlwaysShow = 81,
    Color2Index = 82,
    NameAuthor = 83,
    Score = 84,
    BalloonAnchor = 85,
    PuffedState = 86,
    BubbleTime = 87,
    Agent = 88,
    SittingAmount = 89,
    SittingAmountPrevious = 90,
    EatingCounter = 91,
    Reserved092 = 92,
    LayingAmount = 93,
    LayingAmountPrevious = 94,
    DataDuration = 95,
    DataSpawnTimeDeprecated = 96,
    DataChangeRate = 97,
    DataChangeOnPickup = 98,
    DataPickupCount = 99,
    InteractText = 100,
    TradeTier = 101,
    MaxTradeTier = 102,
    TradeExperience = 103,
    SkinId = 104,
    SpawningFrames = 105,
    CommandBlockTickDelay = 106,
    CommandBlockExecuteOnFirstTick = 107,
    AmbientSoundInterval = 108,
    AmbientSoundIntervalRange = 109,
    AmbientSoundEventName = 110,
    FallDamageMultiplier = 111,
    NameRawText = 112,
    CanRideTarget = 113,
    LowTierCuredTradeDiscount = 114,
    HighTierCuredTradeDiscount = 115,
    NearbyCuredTradeDiscount = 116,
    NearbyCuredDiscountTimeStamp = 117,
    Hitbox = 118,
    IsBuoyant = 119,
    FreezingEffectStrength = 120,
    BuoyancyData = 121,
    GoatHornCount = 122,
    BaseRuntimeId = 123,
    MovementSoundDistanceOffset = 124,
    HeartbeatIntervalTicks = 125,
    HeartbeatSoundEvent = 126,
    PlayerLastDeathPos = 127,
    PlayerLastDeathDimension = 128,
    PlayerHasDied = 129,
    CollisionBox = 130,
    VisibleMobEffects = 131,
    FilteredName = 132,
    EnterBedPosition = 133,
    SeatThirdPersonCameraRadius = 134,
    SeatCameraRelaxDistanceSmoothing = 135,
    AimAssistPriorityPresetId = 136,
    AimAssistPriorityCategoryId = 137,
    AimAssistPriorityActorId = 138,
    Count = 139,
};

using DataItemBytePayload = base::DataItemBytePayload;

using DataItemShortPayload = base::DataItemShortPayload;

using DataItemIntPayload = base::DataItemIntPayload;

using DataItemFloatPayload = base::DataItemFloatPayload;

using DataItemStringPayload = base::DataItemStringPayload;

using DataItemCompoundTagPayload = base::DataItemCompoundTagPayload;

using DataItemPosPayload = base::DataItemPosPayload;

using DataItemInt64Payload = base::DataItemInt64Payload;

using DataItemVec3Payload = base::DataItemVec3Payload;

using DataItemEntry = base::DataItemEntry;

using SynchedActorData = base::SynchedActorData;

using AddActorPacket = base::AddActorPacket;

using SetActorDataPacket = base::SetActorDataPacket;

enum class ActorType : int {
    Undefined = 1,
    TypeMask = 255,
    Mob = 256,
    PathfinderMob = 768,
    Monster = 2816,
    Animal = 4864,
    TamableAnimal = 21248,
    Ambient = 33024,
    Undead = 65792,
    UndeadMonster = 68352,
    ZombieMonster = 199424,
    Arthropod = 264960,
    Minecart = 524288,
    SkeletonMonster = 1116928,
    EquineAnimal = 2118400,
    Projectile = 4194304,
    AbstractArrow = 8388608,
    WaterAnimal = 8960,
    VillagerBase = 16777984,
    Chicken = 4874,
    Cow = 4875,
    Pig = 4876,
    Sheep = 4877,
    Wolf = 21262,
    Villager = 16777999,
    MushroomCow = 4880,
    Squid = 8977,
    Rabbit = 4882,
    Bat = 33043,
    IronGolem = 788,
    SnowGolem = 789,
    Ocelot = 21270,
    Horse = 2118423,
    PolarBear = 4892,
    Llama = 4893,
    Parrot = 21278,
    Dolphin = 8991,
    Donkey = 2118424,
    Mule = 2118425,
    SkeletonHorse = 2183962,
    ZombieHorse = 2183963,
    Zombie = 199456,
    Creeper = 2849,
    Skeleton = 1116962,
    Spider = 264995,
    PigZombie = 68388,
    Slime = 2853,
    EnderMan = 2854,
    Silverfish = 264999,
    CaveSpider = 265000,
    Ghast = 2857,
    LavaSlime = 2858,
    Blaze = 2859,
    ZombieVillager = 199468,
    Witch = 2861,
    Stray = 1116974,
    Husk = 199471,
    WitherSkeleton = 1116976,
    Guardian = 2865,
    ElderGuardian = 2866,
    Npc = 307,
    WitherBoss = 68404,
    Dragon = 2869,
    Shulker = 2870,
    Endermite = 265015,
    Agent = 312,
    Vindicator = 2873,
    Phantom = 68410,
    IllagerBeast = 2875,
    ArmorStand = 317,
    TripodCamera = 318,
    Player = 319,
    ItemEntity = 64,
    PrimedTnt = 65,
    FallingBlock = 66,
    MovingBlock = 67,
    ExperiencePotion = 4194372,
    Experience = 69,
    EyeOfEnder = 70,
    EnderCrystal = 71,
    FireworksRocket = 72,
    Trident = 12582985,
    Turtle = 4938,
    Cat = 21323,
    ShulkerBullet = 4194380,
    FishingHook = 77,
    Chalkboard = 78,
    DragonFireball = 4194383,
    Arrow = 12582992,
    Snowball = 4194385,
    ThrownEgg = 4194386,
    Painting = 83,
    LargeFireball = 4194389,
    ThrownPotion = 4194390,
    Enderpearl = 4194391,
    LeashKnot = 88,
    WitherSkull = 4194393,
    BoatRideable = 90,
    WitherSkullDangerous = 4194395,
    LightningBolt = 93,
    SmallFireball = 4194398,
    AreaEffectCloud = 95,
    LingeringPotion = 4194405,
    LlamaSpit = 4194406,
    EvocationFang = 4194407,
    EvocationIllager = 2920,
    Vex = 2921,
    MinecartRideable = 524372,
    MinecartHopper = 524384,
    MinecartTNT = 524385,
    MinecartChest = 524386,
    MinecartFurnace = 524387,
    MinecartCommandBlock = 524388,
    IceBomb = 4194410,
    Balloon = 107,
    Pufferfish = 9068,
    Salmon = 9069,
    Drowned = 199534,
    Tropicalfish = 9071,
    Fish = 9072,
    Panda = 4977,
    Pillager = 2930,
    VillagerV2 = 16778099,
    ZombieVillagerV2 = 199540,
    Shield = 117,
    WanderingTrader = 886,
    Lectern = 119,
    ElderGuardianGhost = 2936,
    Fox = 4985,
    Bee = 378,
    Piglin = 379,
    Hoglin = 4988,
    Strider = 4989,
    Zoglin = 68478,
    PiglinBrute = 383,
    Goat = 4992,
    GlowSquid = 9089,
    Axolotl = 4994,
    Warden = 2947,
    Frog = 4996,
    Tadpole = 9093,
    Allay = 390,
    ChestBoatRideable = 218,
    TraderLlama = 5021,
    Camel = 5002,
    Sniffer = 5003,
    Breeze = 2956,
    BreezeWindChargeProjectile = 4194445,
    Armadillo = 5006,
    WindChargeProjectile = 4194447,
    Bogged = 1117072,
    OminousItemSpawner = 145,
    Creaking = 2962,
    HappyGhast = 5011,
    CopperGolem = 916,
    Nautilus = 9109,
    ZombieNautilus = 74646,
    Parched = 1117079,
    CamelHusk = 70552,
};

struct SetLastHurtByPacket {
    static constexpr int Id = 96;
    v924::ActorType last_hurt_by{};
};

using ActorEvent = v898::ActorEvent;

using ActorEventPacket = v898::ActorEventPacket;

using AnimatePacket = v898::AnimatePacket;

using AddItemActorPacket = base::AddItemActorPacket;

}  // namespace v924

namespace v975 {

enum class ActorFlags : int {
    Onfire = 0,
    Sneaking = 1,
    Riding = 2,
    Sprinting = 3,
    Usingitem = 4,
    Invisible = 5,
    Tempted = 6,
    Inlove = 7,
    Saddled = 8,
    Powered = 9,
    Ignited = 10,
    Baby = 11,
    Converting = 12,
    Critical = 13,
    CanShowName = 14,
    AlwaysShowName = 15,
    Noai = 16,
    Silent = 17,
    Wallclimbing = 18,
    Canclimb = 19,
    Canswim = 20,
    Canfly = 21,
    Canwalk = 22,
    Resting = 23,
    Sitting = 24,
    Angry = 25,
    Interested = 26,
    Charged = 27,
    Tamed = 28,
    Orphaned = 29,
    Leashed = 30,
    Sheared = 31,
    Gliding = 32,
    Elder = 33,
    Moving = 34,
    Breathing = 35,
    Chested = 36,
    Stackable = 37,
    ShowBottom = 38,
    Standing = 39,
    Shaking = 40,
    Idling = 41,
    Casting = 42,
    Charging = 43,
    WasdControlled = 44,
    CanPowerJump = 45,
    CanDash = 46,
    Lingering = 47,
    HasCollision = 48,
    HasGravity = 49,
    FireImmune = 50,
    Dancing = 51,
    Enchanted = 52,
    Returntrident = 53,
    ContainerIsPrivate = 54,
    IsTransforming = 55,
    Damagenearbymobs = 56,
    Swimming = 57,
    Bribed = 58,
    IsPregnant = 59,
    LayingEgg = 60,
    PassengerCanPick = 61,
    TransitionSitting = 62,
    Eating = 63,
    LayingDown = 64,
    Sneezing = 65,
    Trusting = 66,
    Rolling = 67,
    Scared = 68,
    InScaffolding = 69,
    OverScaffolding = 70,
    DescendThroughBlock = 71,
    Blocking = 72,
    TransitionBlocking = 73,
    BlockedUsingShield = 74,
    BlockedUsingDamagedShield = 75,
    Sleeping = 76,
    WantsToWake = 77,
    TradeInterest = 78,
    DoorBreaker = 79,
    BreakingObstruction = 80,
    DoorOpener = 81,
    IsIllagerCaptain = 82,
    Stunned = 83,
    Roaring = 84,
    DelayedAttack = 85,
    IsAvoidingMobs = 86,
    IsAvoidingBlock = 87,
    FacingTargetToRangeAttack = 88,
    HiddenWhenInvisible = 89,
    IsInUi = 90,
    Stalking = 91,
    Emoting = 92,
    Celebrating = 93,
    Admiring = 94,
    CelebratingSpecial = 95,
    OutOfControl = 96,
    RamAttack = 97,
    PlayingDead = 98,
    InAscendableBlock = 99,
    OverDescendableBlock = 100,
    Croaking = 101,
    EatMob = 102,
    JumpGoalJump = 103,
    Emerging = 104,
    Sniffing = 105,
    Digging = 106,
    SonicBoom = 107,
    HasDashCooldown = 108,
    PushTowardsClosestSpace = 109,
    Deprecated1 = 110,
    Deprecated2 = 111,
    Deprecated3 = 112,
    Searching = 113,
    Crawling = 114,
    TimerFlag1 = 115,
    TimerFlag2 = 116,
    TimerFlag3 = 117,
    BodyRotationBlocked = 118,
    RendersWhenInvisible = 119,
    RotationAxisAligned = 120,
    Collidable = 121,
    WasdFreeCameraControlled = 122,
    DoesServerAuthOnlyDismount = 123,
    BodyRotationAlwaysFollowsHead = 124,
    CanUseVerticalMovementAction = 125,
    RotationLockedToVehicle = 126,
    UsesLegacyFriction = 127,
    UsesUniformAirDrag = 128,
    NameplateDepthTested = 129,
    Count = 130,
};

enum class ActorDataIDs : std::uint8_t {
    Reserved0 = 0,
    StructuralIntegrity = 1,
    Variant = 2,
    ColorIndex = 3,
    Name = 4,
    Owner = 5,
    Target = 6,
    AirSupply = 7,
    EffectColor = 8,
    Reserved009 = 9,
    Reserved010 = 10,
    Hurt = 11,
    HurtDir = 12,
    RowTimeLeft = 13,
    RowTimeRight = 14,
    Value = 15,
    DisplayTileRuntimeId = 16,
    DisplayOffset = 17,
    CustomDisplay = 18,
    Swell = 19,
    OldSwell = 20,
    SwellDir = 21,
    ChargeAmount = 22,
    DeprecatedCarryBlockRuntimeId = 23,
    ClientEvent = 24,
    UsingItem = 25,
    PlayerFlags = 26,
    PlayerIndex = 27,
    BedPosition = 28,
    XPower = 29,
    YPower = 30,
    ZPower = 31,
    AuxPower = 32,
    Fishx = 33,
    Fishz = 34,
    Fishangle = 35,
    AuxValueData = 36,
    LeashHolder = 37,
    Reserved038 = 38,
    HasNpc = 39,
    NpcData = 40,
    Actions = 41,
    AirSupplyMax = 42,
    MarkVariant = 43,
    ContainerType = 44,
    ContainerSize = 45,
    ContainerStrengthModifier = 46,
    BlockTarget = 47,
    Inv = 48,
    TargetA = 49,
    TargetB = 50,
    TargetC = 51,
    AerialAttack = 52,
    Reserved053 = 53,
    Reserved054 = 54,
    FuseTime = 55,
    Reserved056 = 56,
    SeatLockPassengerRotation = 57,
    SeatLockPassengerRotationDegrees = 58,
    SeatRotationOffset = 59,
    SeatRotationOffsetDegrees = 60,
    DataRadius = 61,
    DataWaiting = 62,
    DataParticle = 63,
    PeekId = 64,
    AttachFace = 65,
    Attached = 66,
    AttachPos = 67,
    TradeTarget = 68,
    Career = 69,
    HasCommandBlock = 70,
    CommandName = 71,
    LastCommandOutput = 72,
    TrackCommandOutput = 73,
    Reserved074 = 74,
    Strength = 75,
    StrengthMax = 76,
    DataSpellCastingColor = 77,
    DataLifetimeTicks = 78,
    PoseIndex = 79,
    DataTickOffset = 80,
    NametagAlwaysShow = 81,
    Color2Index = 82,
    NameAuthor = 83,
    Score = 84,
    BalloonAnchor = 85,
    PuffedState = 86,
    BubbleTime = 87,
    Agent = 88,
    SittingAmount = 89,
    SittingAmountPrevious = 90,
    EatingCounter = 91,
    Reserved092 = 92,
    LayingAmount = 93,
    LayingAmountPrevious = 94,
    DataDuration = 95,
    DataSpawnTimeDeprecated = 96,
    DataChangeRate = 97,
    DataChangeOnPickup = 98,
    DataPickupCount = 99,
    InteractText = 100,
    TradeTier = 101,
    MaxTradeTier = 102,
    TradeExperience = 103,
    SkinId = 104,
    SpawningFrames = 105,
    CommandBlockTickDelay = 106,
    CommandBlockExecuteOnFirstTick = 107,
    AmbientSoundInterval = 108,
    AmbientSoundIntervalRange = 109,
    AmbientSoundEventName = 110,
    FallDamageMultiplier = 111,
    NameRawText = 112,
    CanRideTarget = 113,
    LowTierCuredTradeDiscount = 114,
    HighTierCuredTradeDiscount = 115,
    NearbyCuredTradeDiscount = 116,
    NearbyCuredDiscountTimeStamp = 117,
    Hitbox = 118,
    IsBuoyant = 119,
    FreezingEffectStrength = 120,
    BuoyancyData = 121,
    GoatHornCount = 122,
    BaseRuntimeId = 123,
    MovementSoundDistanceOffset = 124,
    HeartbeatIntervalTicks = 125,
    HeartbeatSoundEvent = 126,
    PlayerLastDeathPos = 127,
    PlayerLastDeathDimension = 128,
    PlayerHasDied = 129,
    CollisionBox = 130,
    VisibleMobEffects = 131,
    FilteredName = 132,
    EnterBedPosition = 133,
    SeatThirdPersonCameraRadius = 134,
    SeatCameraRelaxDistanceSmoothing = 135,
    AimAssistPriorityPresetId = 136,
    AimAssistPriorityCategoryId = 137,
    AimAssistPriorityActorId = 138,
    Reserved139 = 139,
    NameplateRenderDistanceMax = 140,
    Count = 141,
};

using DataItemBytePayload = base::DataItemBytePayload;

using DataItemShortPayload = base::DataItemShortPayload;

using DataItemIntPayload = base::DataItemIntPayload;

using DataItemFloatPayload = base::DataItemFloatPayload;

using DataItemStringPayload = base::DataItemStringPayload;

using DataItemCompoundTagPayload = base::DataItemCompoundTagPayload;

using DataItemPosPayload = base::DataItemPosPayload;

using DataItemInt64Payload = base::DataItemInt64Payload;

using DataItemVec3Payload = base::DataItemVec3Payload;

using DataItemEntry = base::DataItemEntry;

using SynchedActorData = base::SynchedActorData;

using AddActorPacket = base::AddActorPacket;

using SetActorDataPacket = base::SetActorDataPacket;

enum class ActorType : int {
    Undefined = 1,
    TypeMask = 255,
    Mob = 256,
    PathfinderMob = 768,
    Monster = 2816,
    Animal = 4864,
    TamableAnimal = 21248,
    Ambient = 33024,
    Undead = 65792,
    UndeadMonster = 68352,
    ZombieMonster = 199424,
    Arthropod = 264960,
    Minecart = 524288,
    SkeletonMonster = 1116928,
    EquineAnimal = 2118400,
    Projectile = 4194304,
    AbstractArrow = 8388608,
    WaterAnimal = 8960,
    VillagerBase = 16777984,
    Chicken = 4874,
    Cow = 4875,
    Pig = 4876,
    Sheep = 4877,
    Wolf = 21262,
    Villager = 16777999,
    MushroomCow = 4880,
    Squid = 8977,
    Rabbit = 4882,
    Bat = 33043,
    IronGolem = 788,
    SnowGolem = 789,
    Ocelot = 21270,
    Horse = 2118423,
    PolarBear = 4892,
    Llama = 4893,
    Parrot = 21278,
    Dolphin = 8991,
    Donkey = 2118424,
    Mule = 2118425,
    SkeletonHorse = 2183962,
    ZombieHorse = 2183963,
    Zombie = 199456,
    Creeper = 2849,
    Skeleton = 1116962,
    Spider = 264995,
    PigZombie = 68388,
    Slime = 2853,
    EnderMan = 2854,
    Silverfish = 264999,
    CaveSpider = 265000,
    Ghast = 2857,
    LavaSlime = 2858,
    Blaze = 2859,
    ZombieVillager = 199468,
    Witch = 2861,
    Stray = 1116974,
    Husk = 199471,
    WitherSkeleton = 1116976,
    Guardian = 2865,
    ElderGuardian = 2866,
    Npc = 307,
    WitherBoss = 68404,
    Dragon = 2869,
    Shulker = 2870,
    Endermite = 265015,
    Agent = 312,
    Vindicator = 2873,
    Phantom = 68410,
    IllagerBeast = 2875,
    ArmorStand = 317,
    TripodCamera = 318,
    Player = 319,
    ItemEntity = 64,
    PrimedTnt = 65,
    FallingBlock = 66,
    MovingBlock = 67,
    ExperiencePotion = 4194372,
    Experience = 69,
    EyeOfEnder = 70,
    EnderCrystal = 71,
    FireworksRocket = 72,
    Trident = 12582985,
    Turtle = 4938,
    Cat = 21323,
    ShulkerBullet = 4194380,
    FishingHook = 77,
    Chalkboard = 78,
    DragonFireball = 4194383,
    Arrow = 12582992,
    Snowball = 4194385,
    ThrownEgg = 4194386,
    Painting = 83,
    LargeFireball = 4194389,
    ThrownPotion = 4194390,
    Enderpearl = 4194391,
    LeashKnot = 88,
    WitherSkull = 4194393,
    BoatRideable = 90,
    WitherSkullDangerous = 4194395,
    LightningBolt = 93,
    SmallFireball = 4194398,
    AreaEffectCloud = 95,
    LingeringPotion = 4194405,
    LlamaSpit = 4194406,
    EvocationFang = 4194407,
    EvocationIllager = 2920,
    Vex = 2921,
    MinecartRideable = 524372,
    MinecartHopper = 524384,
    MinecartTNT = 524385,
    MinecartChest = 524386,
    MinecartFurnace = 524387,
    MinecartCommandBlock = 524388,
    IceBomb = 4194410,
    Balloon = 107,
    Pufferfish = 9068,
    Salmon = 9069,
    Drowned = 199534,
    Tropicalfish = 9071,
    Fish = 9072,
    Panda = 4977,
    Pillager = 2930,
    VillagerV2 = 16778099,
    ZombieVillagerV2 = 199540,
    Shield = 117,
    WanderingTrader = 886,
    Lectern = 119,
    ElderGuardianGhost = 2936,
    Fox = 4985,
    Bee = 378,
    Piglin = 379,
    Hoglin = 4988,
    Strider = 4989,
    Zoglin = 68478,
    PiglinBrute = 383,
    Goat = 4992,
    GlowSquid = 9089,
    Axolotl = 4994,
    Warden = 2947,
    Frog = 4996,
    Tadpole = 9093,
    Allay = 390,
    ChestBoatRideable = 218,
    TraderLlama = 5021,
    Camel = 5002,
    Sniffer = 5003,
    Breeze = 2956,
    BreezeWindChargeProjectile = 4194445,
    Armadillo = 5006,
    WindChargeProjectile = 4194447,
    Bogged = 1117072,
    OminousItemSpawner = 145,
    Creaking = 2962,
    HappyGhast = 5011,
    CopperGolem = 916,
    Nautilus = 9109,
    ZombieNautilus = 74646,
    Parched = 1117079,
    CamelHusk = 70552,
    SulfurCube = 2969,
};

struct SetLastHurtByPacket {
    static constexpr int Id = 96;
    v975::ActorType last_hurt_by{};
};

enum class ActorEvent : std::uint8_t {
    None = 0,
    Jump = 1,
    Hurt = 2,
    Death = 3,
    StartAttacking = 4,
    StopAttacking = 5,
    TamingFailed = 6,
    TamingSucceeded = 7,
    ShakeWetness = 8,
    EatGrass = 10,
    FishhookBubble = 11,
    FishhookFishpos = 12,
    FishhookHooktime = 13,
    FishhookTease = 14,
    SquidFleeing = 15,
    ZombieConverting = 16,
    PlayAmbient = 17,
    SpawnAlive = 18,
    StartOfferFlower = 19,
    StopOfferFlower = 20,
    LoveHearts = 21,
    VillagerAngry = 22,
    VillagerHappy = 23,
    WitchHatMagic = 24,
    FireworksExplode = 25,
    InLoveHearts = 26,
    SilverfishMergeAnim = 27,
    GuardianAttackSound = 28,
    DrinkPotion = 29,
    ThrowPotion = 30,
    PrimeTntcart = 31,
    PrimeCreeper = 32,
    AirSupply = 33,
    DeprecatedAddPlayerLevels = 34,
    GuardianMiningFatigue = 35,
    AgentSwingArm = 36,
    DragonStartDeathAnim = 37,
    GroundDust = 38,
    Shake = 39,
    Feed = 57,
    BabyAge = 60,
    InstantDeath = 61,
    NotifyTrade = 62,
    LeashDestroyed = 63,
    CaravanUpdated = 64,
    TalismanActivate = 65,
    DeprecatedUpdateStructureFeature = 66,
    PlayerSpawnedMob = 67,
    Puke = 68,
    UpdateStackSize = 69,
    StartSwimming = 70,
    BalloonPop = 71,
    TreasureHunt = 72,
    SummonAgent = 73,
    FinishedChargingItem = 74,
    ActorGrowUp = 76,
    VibrationDetected = 77,
    DrinkMilk = 78,
    ShakeWetnessStop = 79,
    KineticDamageDealt = 80,
    HurtWithoutReceivingDamage = 81,
};

struct ActorEventPacket {
    static constexpr int Id = 27;
    ActorRuntimeID runtime_id{};
    v975::ActorEvent event_id{};
    std::int32_t data{};
    std::optional<Vec3> fire_at_position{};
};

using AnimatePacket = v898::AnimatePacket;

using AddItemActorPacket = base::AddItemActorPacket;

}  // namespace v975

namespace v2168 {

enum class ActorFlags : int {
    Onfire = 0,
    Sneaking = 1,
    Riding = 2,
    Sprinting = 3,
    Usingitem = 4,
    Invisible = 5,
    Tempted = 6,
    Inlove = 7,
    Saddled = 8,
    Powered = 9,
    Ignited = 10,
    Baby = 11,
    Converting = 12,
    Critical = 13,
    CanShowName = 14,
    AlwaysShowName = 15,
    Noai = 16,
    Silent = 17,
    Wallclimbing = 18,
    Canclimb = 19,
    Canswim = 20,
    Canfly = 21,
    Canwalk = 22,
    Resting = 23,
    Sitting = 24,
    Angry = 25,
    Interested = 26,
    Charged = 27,
    Tamed = 28,
    Orphaned = 29,
    Leashed = 30,
    Sheared = 31,
    Gliding = 32,
    Elder = 33,
    Moving = 34,
    Breathing = 35,
    Chested = 36,
    Stackable = 37,
    ShowBottom = 38,
    Standing = 39,
    Shaking = 40,
    Idling = 41,
    Casting = 42,
    Charging = 43,
    WasdControlled = 44,
    CanPowerJump = 45,
    CanDash = 46,
    Lingering = 47,
    HasCollision = 48,
    HasGravity = 49,
    FireImmune = 50,
    Dancing = 51,
    Enchanted = 52,
    Returntrident = 53,
    ContainerIsPrivate = 54,
    IsTransforming = 55,
    Damagenearbymobs = 56,
    Swimming = 57,
    Bribed = 58,
    IsPregnant = 59,
    LayingEgg = 60,
    PassengerCanPick = 61,
    TransitionSitting = 62,
    Eating = 63,
    LayingDown = 64,
    Sneezing = 65,
    Trusting = 66,
    Rolling = 67,
    Scared = 68,
    InScaffolding = 69,
    OverScaffolding = 70,
    DescendThroughBlock = 71,
    Blocking = 72,
    TransitionBlocking = 73,
    BlockedUsingShield = 74,
    BlockedUsingDamagedShield = 75,
    Sleeping = 76,
    WantsToWake = 77,
    TradeInterest = 78,
    DoorBreaker = 79,
    BreakingObstruction = 80,
    DoorOpener = 81,
    IsIllagerCaptain = 82,
    Stunned = 83,
    Roaring = 84,
    DelayedAttack = 85,
    IsAvoidingMobs = 86,
    IsAvoidingBlock = 87,
    FacingTargetToRangeAttack = 88,
    HiddenWhenInvisible = 89,
    IsInUi = 90,
    Stalking = 91,
    Emoting = 92,
    Celebrating = 93,
    Admiring = 94,
    CelebratingSpecial = 95,
    OutOfControl = 96,
    RamAttack = 97,
    PlayingDead = 98,
    InAscendableBlock = 99,
    OverDescendableBlock = 100,
    Croaking = 101,
    EatMob = 102,
    JumpGoalJump = 103,
    Emerging = 104,
    Sniffing = 105,
    Digging = 106,
    SonicBoom = 107,
    HasDashCooldown = 108,
    PushTowardsClosestSpace = 109,
    Deprecated1 = 110,
    Deprecated2 = 111,
    Deprecated3 = 112,
    Searching = 113,
    Crawling = 114,
    TimerFlag1 = 115,
    TimerFlag2 = 116,
    TimerFlag3 = 117,
    BodyRotationBlocked = 118,
    RendersWhenInvisible = 119,
    RotationAxisAligned = 120,
    Collidable = 121,
    WasdFreeCameraControlled = 122,
    DoesServerAuthOnlyDismount = 123,
    BodyRotationAlwaysFollowsHead = 124,
    CanUseVerticalMovementAction = 125,
    RotationLockedToVehicle = 126,
    UsesLegacyFriction = 127,
    UsesUniformAirDrag = 128,
    NameplateDepthTested = 129,
    NotPickableFromInside = 130,
    Count = 131,
};

using ActorDataIDs = v975::ActorDataIDs;

struct DataItemBytePayload {
    std::int8_t value{};
};

struct DataItemShortPayload {
    std::int16_t value{};
};

struct DataItemIntPayload {
    std::int32_t value{};
};

struct DataItemFloatPayload {
    float value{};
};

struct DataItemStringPayload {
    std::string value{};
};

struct DataItemCompoundTagPayload {
    CompoundTag value{};
};

struct DataItemPosPayload {
    BlockPos value{};
};

struct DataItemInt64Payload {
    std::int64_t value{};
};

struct DataItemVec3Payload {
    Vec3 value{};
};

struct DataItemEntry {
    std::uint32_t id{};
    std::variant<v2168::DataItemBytePayload, v2168::DataItemShortPayload, v2168::DataItemIntPayload, v2168::DataItemFloatPayload, v2168::DataItemStringPayload, v2168::DataItemCompoundTagPayload, v2168::DataItemPosPayload, v2168::DataItemInt64Payload, v2168::DataItemVec3Payload> payload{};
};

namespace SynchedActorData_nested {

struct CopyableDataList {
    std::vector<v2168::DataItemEntry> data{};
};

}  // namespace SynchedActorData_nested

struct SynchedActorData {
    using CopyableDataList = SynchedActorData_nested::CopyableDataList;
};

struct AddActorPacket {
    static constexpr int Id = 13;
    ActorUniqueID entity_id{};
    ActorRuntimeID runtime_id{};
    std::string actor_type{};
    Vec3 pos{};
    Vec3 velocity{};
    Vec2 rot{};
    float y_head_rotation{};
    float y_body_rotation{};
    std::vector<SyncedAttribute> attributes{};
    v2168::SynchedActorData::CopyableDataList data{};
    PropertySyncData synched_properties{};
    std::vector<ActorLink> links{};
};

struct SetActorDataPacket {
    static constexpr int Id = 39;
    ActorRuntimeID id{};
    v2168::SynchedActorData::CopyableDataList packed_items{};
    PropertySyncData synched_properties{};
    PlayerInputTick tick{};
};

enum class ActorType : int {
    Undefined = 1,
    TypeMask = 255,
    Mob = 256,
    PathfinderMob = 768,
    Monster = 2816,
    Animal = 4864,
    TamableAnimal = 21248,
    Ambient = 33024,
    Undead = 65792,
    UndeadMonster = 68352,
    ZombieMonster = 199424,
    Arthropod = 264960,
    Minecart = 524288,
    SkeletonMonster = 1116928,
    EquineAnimal = 2118400,
    Projectile = 4194304,
    AbstractArrow = 8388608,
    WaterAnimal = 8960,
    VillagerBase = 16777984,
    Chicken = 4874,
    Cow = 4875,
    Pig = 4876,
    Sheep = 4877,
    Wolf = 21262,
    Villager = 16777999,
    MushroomCow = 4880,
    Squid = 8977,
    Rabbit = 4882,
    Bat = 33043,
    IronGolem = 788,
    SnowGolem = 789,
    Ocelot = 21270,
    Horse = 2118423,
    PolarBear = 4892,
    Llama = 4893,
    Parrot = 21278,
    Dolphin = 8991,
    Donkey = 2118424,
    Mule = 2118425,
    SkeletonHorse = 2183962,
    ZombieHorse = 2183963,
    Zombie = 199456,
    Creeper = 2849,
    Skeleton = 1116962,
    Spider = 264995,
    PigZombie = 68388,
    Slime = 2853,
    EnderMan = 2854,
    Silverfish = 264999,
    CaveSpider = 265000,
    Ghast = 2857,
    LavaSlime = 2858,
    Blaze = 2859,
    ZombieVillager = 199468,
    Witch = 2861,
    Stray = 1116974,
    Husk = 199471,
    WitherSkeleton = 1116976,
    Guardian = 2865,
    ElderGuardian = 2866,
    Npc = 307,
    WitherBoss = 68404,
    Dragon = 2869,
    Shulker = 2870,
    Endermite = 265015,
    Agent = 312,
    Vindicator = 2873,
    Phantom = 68410,
    IllagerBeast = 2875,
    ArmorStand = 317,
    TripodCamera = 318,
    Player = 319,
    ItemEntity = 64,
    PrimedTnt = 65,
    FallingBlock = 66,
    MovingBlock = 67,
    ExperiencePotion = 4194372,
    Experience = 69,
    EyeOfEnder = 70,
    EnderCrystal = 71,
    FireworksRocket = 72,
    Trident = 12582985,
    Turtle = 4938,
    Cat = 21323,
    ShulkerBullet = 4194380,
    FishingHook = 77,
    Chalkboard = 78,
    DragonFireball = 4194383,
    Arrow = 12582992,
    Snowball = 4194385,
    ThrownEgg = 4194386,
    Painting = 83,
    LargeFireball = 4194389,
    ThrownPotion = 4194390,
    Enderpearl = 4194391,
    LeashKnot = 88,
    WitherSkull = 4194393,
    BoatRideable = 90,
    WitherSkullDangerous = 4194395,
    LightningBolt = 93,
    SmallFireball = 4194398,
    AreaEffectCloud = 95,
    LingeringPotion = 4194405,
    LlamaSpit = 4194406,
    EvocationFang = 4194407,
    EvocationIllager = 2920,
    Vex = 2921,
    MinecartRideable = 524372,
    MinecartHopper = 524384,
    MinecartTNT = 524385,
    MinecartChest = 524386,
    MinecartFurnace = 524387,
    MinecartCommandBlock = 524388,
    IceBomb = 4194410,
    Balloon = 107,
    Pufferfish = 9068,
    Salmon = 9069,
    Drowned = 199534,
    Tropicalfish = 9071,
    Fish = 9072,
    Panda = 4977,
    Pillager = 2930,
    VillagerV2 = 16778099,
    ZombieVillagerV2 = 199540,
    Shield = 117,
    WanderingTrader = 886,
    Lectern = 119,
    ElderGuardianGhost = 2936,
    Fox = 4985,
    Bee = 378,
    Piglin = 379,
    Hoglin = 4988,
    Strider = 4989,
    Zoglin = 68478,
    PiglinBrute = 383,
    Goat = 4992,
    GlowSquid = 9089,
    Axolotl = 4994,
    Warden = 2947,
    Frog = 4996,
    Tadpole = 9093,
    Allay = 390,
    ChestBoatRideable = 218,
    TraderLlama = 5021,
    Camel = 5002,
    Sniffer = 5003,
    Breeze = 2956,
    BreezeWindChargeProjectile = 4194445,
    Armadillo = 5006,
    WindChargeProjectile = 4194447,
    Bogged = 1117072,
    OminousItemSpawner = 145,
    Creaking = 2962,
    HappyGhast = 5011,
    CopperGolem = 916,
    Nautilus = 9109,
    ZombieNautilus = 74646,
    Parched = 1117079,
    CamelHusk = 70552,
    SulfurCube = 921,
    Cushion = 154,
};

struct SetLastHurtByPacket {
    static constexpr int Id = 96;
    v2168::ActorType last_hurt_by{};
};

using ActorEvent = v975::ActorEvent;

using ActorEventPacket = v975::ActorEventPacket;

using AnimatePacket = v898::AnimatePacket;

struct AddItemActorPacket {
    static constexpr int Id = 15;
    ActorUniqueID id{};
    ActorRuntimeID runtime_id{};
    v2168::SerializedNetworkItemStackDescriptor item{};
    Vec3 pos{};
    Vec3 velocity{};
    v2168::SynchedActorData::CopyableDataList data{};
    bool is_from_fishing{};
};

}  // namespace v2168

namespace v2225 {

using ActorFlags = v2168::ActorFlags;

using ActorDataIDs = v975::ActorDataIDs;

using DataItemBytePayload = v2168::DataItemBytePayload;

using DataItemShortPayload = v2168::DataItemShortPayload;

using DataItemIntPayload = v2168::DataItemIntPayload;

using DataItemFloatPayload = v2168::DataItemFloatPayload;

using DataItemStringPayload = v2168::DataItemStringPayload;

using DataItemCompoundTagPayload = v2168::DataItemCompoundTagPayload;

using DataItemPosPayload = v2168::DataItemPosPayload;

using DataItemInt64Payload = v2168::DataItemInt64Payload;

using DataItemVec3Payload = v2168::DataItemVec3Payload;

using DataItemEntry = v2168::DataItemEntry;

using SynchedActorData = v2168::SynchedActorData;

struct AddActorPacket {
    static constexpr int Id = 13;
    ActorUniqueID entity_id{};
    ActorRuntimeID runtime_id{};
    std::string actor_type{};
    Vec3 pos{};
    Vec3 velocity{};
    Vec2 rot{};
    float y_head_rotation{};
    float y_body_rotation{};
    std::vector<SyncedAttribute> attributes{};
    v2168::SynchedActorData::CopyableDataList data{};
    PropertySyncData synched_properties{};
    std::vector<ActorLink> links{};
    std::optional<PassengerOfBlockArguments> passenger_block_data{};
};

using SetActorDataPacket = v2168::SetActorDataPacket;

enum class ActorType : int {
    Undefined = 1,
    TypeMask = 255,
    Mob = 256,
    PathfinderMob = 768,
    Monster = 2816,
    Animal = 4864,
    TamableAnimal = 21248,
    Ambient = 33024,
    Undead = 65792,
    UndeadMonster = 68352,
    ZombieMonster = 199424,
    Arthropod = 264960,
    Minecart = 524288,
    SkeletonMonster = 1116928,
    EquineAnimal = 2118400,
    Projectile = 4194304,
    AbstractArrow = 8388608,
    WaterAnimal = 8960,
    VillagerBase = 16777984,
    Chicken = 4874,
    Cow = 4875,
    Pig = 4876,
    Sheep = 4877,
    Wolf = 21262,
    Villager = 16777999,
    MushroomCow = 4880,
    Squid = 8977,
    Rabbit = 4882,
    Bat = 33043,
    IronGolem = 788,
    SnowGolem = 789,
    Ocelot = 21270,
    Horse = 2118423,
    PolarBear = 4892,
    Llama = 4893,
    Parrot = 21278,
    Dolphin = 8991,
    Donkey = 2118424,
    Mule = 2118425,
    SkeletonHorse = 2183962,
    ZombieHorse = 2183963,
    Zombie = 199456,
    Creeper = 2849,
    Skeleton = 1116962,
    Spider = 264995,
    PigZombie = 68388,
    Slime = 2853,
    EnderMan = 2854,
    Silverfish = 264999,
    CaveSpider = 265000,
    Ghast = 2857,
    LavaSlime = 2858,
    Blaze = 2859,
    ZombieVillager = 199468,
    Witch = 2861,
    Stray = 1116974,
    Husk = 199471,
    WitherSkeleton = 1116976,
    Guardian = 2865,
    ElderGuardian = 2866,
    Npc = 307,
    WitherBoss = 68404,
    Dragon = 2869,
    Shulker = 2870,
    Endermite = 265015,
    Agent = 312,
    Vindicator = 2873,
    Phantom = 68410,
    IllagerBeast = 2875,
    ArmorStand = 317,
    TripodCamera = 318,
    Player = 319,
    ItemEntity = 64,
    PrimedTnt = 65,
    FallingBlock = 66,
    MovingBlock = 67,
    ExperiencePotion = 4194372,
    Experience = 69,
    EyeOfEnder = 70,
    EnderCrystal = 71,
    FireworksRocket = 72,
    Trident = 12582985,
    Turtle = 4938,
    Cat = 21323,
    ShulkerBullet = 4194380,
    FishingHook = 77,
    Chalkboard = 78,
    DragonFireball = 4194383,
    Arrow = 12582992,
    Snowball = 4194385,
    ThrownEgg = 4194386,
    Painting = 83,
    LargeFireball = 4194389,
    ThrownPotion = 4194390,
    Enderpearl = 4194391,
    LeashKnot = 88,
    WitherSkull = 4194393,
    BoatRideable = 90,
    WitherSkullDangerous = 4194395,
    LightningBolt = 93,
    SmallFireball = 4194398,
    AreaEffectCloud = 95,
    LingeringPotion = 4194405,
    LlamaSpit = 4194406,
    EvocationFang = 4194407,
    EvocationIllager = 2920,
    Vex = 2921,
    MinecartRideable = 524372,
    MinecartHopper = 524384,
    MinecartTNT = 524385,
    MinecartChest = 524386,
    MinecartFurnace = 524387,
    MinecartCommandBlock = 524388,
    IceBomb = 4194410,
    Balloon = 107,
    Pufferfish = 9068,
    Salmon = 9069,
    Drowned = 199534,
    Tropicalfish = 9071,
    Fish = 9072,
    Panda = 4977,
    Pillager = 2930,
    VillagerV2 = 16778099,
    ZombieVillagerV2 = 199540,
    Shield = 117,
    WanderingTrader = 886,
    Lectern = 119,
    ElderGuardianGhost = 2936,
    Fox = 4985,
    Bee = 378,
    Piglin = 379,
    Hoglin = 4988,
    Strider = 4989,
    Zoglin = 68478,
    PiglinBrute = 383,
    Goat = 4992,
    GlowSquid = 9089,
    Axolotl = 4994,
    Warden = 2947,
    Frog = 4996,
    Tadpole = 9093,
    Allay = 390,
    ChestBoatRideable = 218,
    TraderLlama = 5021,
    Camel = 5002,
    Sniffer = 5003,
    Breeze = 2956,
    BreezeWindChargeProjectile = 4194445,
    Armadillo = 5006,
    WindChargeProjectile = 4194447,
    Bogged = 1117072,
    OminousItemSpawner = 145,
    Creaking = 2962,
    HappyGhast = 5011,
    CopperGolem = 916,
    Nautilus = 9109,
    ZombieNautilus = 74646,
    Parched = 1117079,
    CamelHusk = 70552,
    SulfurCube = 921,
    Cushion = 154,
    Frostbite = 199579,
    IceBall = 4194460,
};

struct SetLastHurtByPacket {
    static constexpr int Id = 96;
    v2225::ActorType last_hurt_by{};
};

using ActorEvent = v975::ActorEvent;

using ActorEventPacket = v975::ActorEventPacket;

struct SetPassengerOfBlockPacket {
    static constexpr int Id = 357;
    ActorUniqueID passenger{};
    std::optional<PassengerOfBlockArguments> passenger_of_block_data{};
};

namespace AnimatePacket_nested {

enum class Action : std::uint8_t {
    NoAction = 0,
    Swing = 1,
    WakeUp = 3,
    CriticalHit = 4,
    MagicCriticalHit = 5,
};

}  // namespace AnimatePacket_nested

struct AnimatePacket {
    using Action = AnimatePacket_nested::Action;

    static constexpr int Id = 44;
    v2225::AnimatePacket::Action action{};
    ActorRuntimeID runtime_id{};
    float data{};
    std::optional<ActorSwingSource> swing_source{};
    HandSlot hand{};
};

using AddItemActorPacket = v2168::AddItemActorPacket;

}  // namespace v2225

namespace detail {

template <int V>
struct ActorFlags_;

template <int V> requires (V < 776)
struct ActorFlags_<V> { using type = base::ActorFlags; };

template <int V> requires (V >= 776 && V < 786)
struct ActorFlags_<V> { using type = v776::ActorFlags; };

template <int V> requires (V >= 786 && V < 800)
struct ActorFlags_<V> { using type = v786::ActorFlags; };

template <int V> requires (V >= 800 && V < 818)
struct ActorFlags_<V> { using type = v800::ActorFlags; };

template <int V> requires (V >= 818 && V < 844)
struct ActorFlags_<V> { using type = v818::ActorFlags; };

template <int V> requires (V >= 844 && V < 898)
struct ActorFlags_<V> { using type = v844::ActorFlags; };

template <int V> requires (V >= 898 && V < 975)
struct ActorFlags_<V> { using type = v898::ActorFlags; };

template <int V> requires (V >= 975 && V < 2168)
struct ActorFlags_<V> { using type = v975::ActorFlags; };

template <int V> requires (V >= 2168)
struct ActorFlags_<V> { using type = v2168::ActorFlags; };

template <int V>
struct ActorDataIDs_;

template <int V> requires (V < 776)
struct ActorDataIDs_<V> { using type = base::ActorDataIDs; };

template <int V> requires (V >= 776 && V < 800)
struct ActorDataIDs_<V> { using type = v776::ActorDataIDs; };

template <int V> requires (V >= 800 && V < 924)
struct ActorDataIDs_<V> { using type = v800::ActorDataIDs; };

template <int V> requires (V >= 924 && V < 975)
struct ActorDataIDs_<V> { using type = v924::ActorDataIDs; };

template <int V> requires (V >= 975)
struct ActorDataIDs_<V> { using type = v975::ActorDataIDs; };

template <int V>
struct DataItemBytePayload_;

template <int V> requires (V < 2168)
struct DataItemBytePayload_<V> { using type = base::DataItemBytePayload; };

template <int V> requires (V >= 2168)
struct DataItemBytePayload_<V> { using type = v2168::DataItemBytePayload; };

template <int V>
struct DataItemShortPayload_;

template <int V> requires (V < 2168)
struct DataItemShortPayload_<V> { using type = base::DataItemShortPayload; };

template <int V> requires (V >= 2168)
struct DataItemShortPayload_<V> { using type = v2168::DataItemShortPayload; };

template <int V>
struct DataItemIntPayload_;

template <int V> requires (V < 2168)
struct DataItemIntPayload_<V> { using type = base::DataItemIntPayload; };

template <int V> requires (V >= 2168)
struct DataItemIntPayload_<V> { using type = v2168::DataItemIntPayload; };

template <int V>
struct DataItemFloatPayload_;

template <int V> requires (V < 2168)
struct DataItemFloatPayload_<V> { using type = base::DataItemFloatPayload; };

template <int V> requires (V >= 2168)
struct DataItemFloatPayload_<V> { using type = v2168::DataItemFloatPayload; };

template <int V>
struct DataItemStringPayload_;

template <int V> requires (V < 2168)
struct DataItemStringPayload_<V> { using type = base::DataItemStringPayload; };

template <int V> requires (V >= 2168)
struct DataItemStringPayload_<V> { using type = v2168::DataItemStringPayload; };

template <int V>
struct DataItemCompoundTagPayload_;

template <int V> requires (V < 2168)
struct DataItemCompoundTagPayload_<V> { using type = base::DataItemCompoundTagPayload; };

template <int V> requires (V >= 2168)
struct DataItemCompoundTagPayload_<V> { using type = v2168::DataItemCompoundTagPayload; };

template <int V>
struct DataItemPosPayload_;

template <int V> requires (V < 2168)
struct DataItemPosPayload_<V> { using type = base::DataItemPosPayload; };

template <int V> requires (V >= 2168)
struct DataItemPosPayload_<V> { using type = v2168::DataItemPosPayload; };

template <int V>
struct DataItemInt64Payload_;

template <int V> requires (V < 2168)
struct DataItemInt64Payload_<V> { using type = base::DataItemInt64Payload; };

template <int V> requires (V >= 2168)
struct DataItemInt64Payload_<V> { using type = v2168::DataItemInt64Payload; };

template <int V>
struct DataItemVec3Payload_;

template <int V> requires (V < 2168)
struct DataItemVec3Payload_<V> { using type = base::DataItemVec3Payload; };

template <int V> requires (V >= 2168)
struct DataItemVec3Payload_<V> { using type = v2168::DataItemVec3Payload; };

template <int V>
struct DataItemEntry_;

template <int V> requires (V < 2168)
struct DataItemEntry_<V> { using type = base::DataItemEntry; };

template <int V> requires (V >= 2168)
struct DataItemEntry_<V> { using type = v2168::DataItemEntry; };

template <int V>
struct SynchedActorData_;

template <int V> requires (V < 2168)
struct SynchedActorData_<V> { using type = base::SynchedActorData; };

template <int V> requires (V >= 2168)
struct SynchedActorData_<V> { using type = v2168::SynchedActorData; };

template <int V>
struct AddActorPacket_;

template <int V> requires (V < 2168)
struct AddActorPacket_<V> { using type = base::AddActorPacket; };

template <int V> requires (V >= 2168 && V < 2225)
struct AddActorPacket_<V> { using type = v2168::AddActorPacket; };

template <int V> requires (V >= 2225)
struct AddActorPacket_<V> { using type = v2225::AddActorPacket; };

template <int V>
struct SetActorDataPacket_;

template <int V> requires (V < 2168)
struct SetActorDataPacket_<V> { using type = base::SetActorDataPacket; };

template <int V> requires (V >= 2168)
struct SetActorDataPacket_<V> { using type = v2168::SetActorDataPacket; };

template <int V>
struct ActorType_;

template <int V> requires (V < 766)
struct ActorType_<V> { using type = base::ActorType; };

template <int V> requires (V >= 766 && V < 800)
struct ActorType_<V> { using type = v766::ActorType; };

template <int V> requires (V >= 800 && V < 827)
struct ActorType_<V> { using type = v800::ActorType; };

template <int V> requires (V >= 827 && V < 924)
struct ActorType_<V> { using type = v827::ActorType; };

template <int V> requires (V >= 924 && V < 975)
struct ActorType_<V> { using type = v924::ActorType; };

template <int V> requires (V >= 975 && V < 2168)
struct ActorType_<V> { using type = v975::ActorType; };

template <int V> requires (V >= 2168 && V < 2225)
struct ActorType_<V> { using type = v2168::ActorType; };

template <int V> requires (V >= 2225)
struct ActorType_<V> { using type = v2225::ActorType; };

template <int V>
struct SetLastHurtByPacket_;

template <int V> requires (V < 766)
struct SetLastHurtByPacket_<V> { using type = base::SetLastHurtByPacket; };

template <int V> requires (V >= 766 && V < 800)
struct SetLastHurtByPacket_<V> { using type = v766::SetLastHurtByPacket; };

template <int V> requires (V >= 800 && V < 827)
struct SetLastHurtByPacket_<V> { using type = v800::SetLastHurtByPacket; };

template <int V> requires (V >= 827 && V < 924)
struct SetLastHurtByPacket_<V> { using type = v827::SetLastHurtByPacket; };

template <int V> requires (V >= 924 && V < 975)
struct SetLastHurtByPacket_<V> { using type = v924::SetLastHurtByPacket; };

template <int V> requires (V >= 975 && V < 2168)
struct SetLastHurtByPacket_<V> { using type = v975::SetLastHurtByPacket; };

template <int V> requires (V >= 2168 && V < 2225)
struct SetLastHurtByPacket_<V> { using type = v2168::SetLastHurtByPacket; };

template <int V> requires (V >= 2225)
struct SetLastHurtByPacket_<V> { using type = v2225::SetLastHurtByPacket; };

template <int V>
struct ActorEvent_;

template <int V> requires (V < 859)
struct ActorEvent_<V> { using type = base::ActorEvent; };

template <int V> requires (V >= 859 && V < 898)
struct ActorEvent_<V> { using type = v859::ActorEvent; };

template <int V> requires (V >= 898 && V < 975)
struct ActorEvent_<V> { using type = v898::ActorEvent; };

template <int V> requires (V >= 975)
struct ActorEvent_<V> { using type = v975::ActorEvent; };

template <int V>
struct ActorEventPacket_;

template <int V> requires (V < 859)
struct ActorEventPacket_<V> { using type = base::ActorEventPacket; };

template <int V> requires (V >= 859 && V < 898)
struct ActorEventPacket_<V> { using type = v859::ActorEventPacket; };

template <int V> requires (V >= 898 && V < 975)
struct ActorEventPacket_<V> { using type = v898::ActorEventPacket; };

template <int V> requires (V >= 975)
struct ActorEventPacket_<V> { using type = v975::ActorEventPacket; };

template <int V>
struct SetPassengerOfBlockPacket_;

template <int V> requires (V >= 2225)
struct SetPassengerOfBlockPacket_<V> { using type = v2225::SetPassengerOfBlockPacket; };

template <int V>
struct AnimatePacket_;

template <int V> requires (V < 800)
struct AnimatePacket_<V> { using type = base::AnimatePacket; };

template <int V> requires (V >= 800 && V < 859)
struct AnimatePacket_<V> { using type = v800::AnimatePacket; };

template <int V> requires (V >= 859 && V < 898)
struct AnimatePacket_<V> { using type = v859::AnimatePacket; };

template <int V> requires (V >= 898 && V < 2225)
struct AnimatePacket_<V> { using type = v898::AnimatePacket; };

template <int V> requires (V >= 2225)
struct AnimatePacket_<V> { using type = v2225::AnimatePacket; };

template <int V>
struct AddItemActorPacket_;

template <int V> requires (V < 2168)
struct AddItemActorPacket_<V> { using type = base::AddItemActorPacket; };

template <int V> requires (V >= 2168)
struct AddItemActorPacket_<V> { using type = v2168::AddItemActorPacket; };

}  // namespace detail

template <int V> using ActorFlags_ = typename detail::ActorFlags_<V>::type;
template <int V> using ActorDataIDs_ = typename detail::ActorDataIDs_<V>::type;
template <int V> using DataItemBytePayload_ = typename detail::DataItemBytePayload_<V>::type;
template <int V> using DataItemShortPayload_ = typename detail::DataItemShortPayload_<V>::type;
template <int V> using DataItemIntPayload_ = typename detail::DataItemIntPayload_<V>::type;
template <int V> using DataItemFloatPayload_ = typename detail::DataItemFloatPayload_<V>::type;
template <int V> using DataItemStringPayload_ = typename detail::DataItemStringPayload_<V>::type;
template <int V> using DataItemCompoundTagPayload_ = typename detail::DataItemCompoundTagPayload_<V>::type;
template <int V> using DataItemPosPayload_ = typename detail::DataItemPosPayload_<V>::type;
template <int V> using DataItemInt64Payload_ = typename detail::DataItemInt64Payload_<V>::type;
template <int V> using DataItemVec3Payload_ = typename detail::DataItemVec3Payload_<V>::type;
template <int V> using DataItemEntry_ = typename detail::DataItemEntry_<V>::type;
template <int V> using SynchedActorData_ = typename detail::SynchedActorData_<V>::type;
template <int V> using AddActorPacket_ = typename detail::AddActorPacket_<V>::type;
template <int V> using SetActorDataPacket_ = typename detail::SetActorDataPacket_<V>::type;
template <int V> using ActorType_ = typename detail::ActorType_<V>::type;
template <int V> using SetLastHurtByPacket_ = typename detail::SetLastHurtByPacket_<V>::type;
template <int V> using ActorEvent_ = typename detail::ActorEvent_<V>::type;
template <int V> using ActorEventPacket_ = typename detail::ActorEventPacket_<V>::type;
template <int V> using SetPassengerOfBlockPacket_ = typename detail::SetPassengerOfBlockPacket_<V>::type;
template <int V> using AnimatePacket_ = typename detail::AnimatePacket_<V>::type;
template <int V> using AddItemActorPacket_ = typename detail::AddItemActorPacket_<V>::type;

template <int V>
struct packet_of<V, 13> { using type = AddActorPacket_<V>; };

template <int V>
struct packet_of<V, 14> { using type = RemoveActorPacket; };

template <int V>
struct packet_of<V, 15> { using type = AddItemActorPacket_<V>; };

template <int V>
struct packet_of<V, 17> { using type = TakeItemActorPacket; };

template <int V>
struct packet_of<V, 18> { using type = MoveActorAbsolutePacket; };

template <int V>
struct packet_of<V, 22> { using type = AddPaintingPacket; };

template <int V>
struct packet_of<V, 27> { using type = ActorEventPacket_<V>; };

template <int V>
struct packet_of<V, 35> { using type = ActorPickRequestPacket; };

template <int V>
struct packet_of<V, 39> { using type = SetActorDataPacket_<V>; };

template <int V>
struct packet_of<V, 40> { using type = SetActorMotionPacket; };

template <int V>
struct packet_of<V, 41> { using type = SetActorLinkPacket; };

template <int V>
struct packet_of<V, 44> { using type = AnimatePacket_<V>; };

template <int V>
struct packet_of<V, 66> { using type = SpawnExperienceOrbPacket; };

template <int V>
struct packet_of<V, 89> { using type = AddBehaviorTreePacket; };

template <int V>
struct packet_of<V, 96> { using type = SetLastHurtByPacket_<V>; };

template <int V>
struct packet_of<V, 98> { using type = NpcRequestPacket; };

template <int V>
struct packet_of<V, 119> { using type = AvailableActorIdentifiersPacket; };

template <int V>
struct packet_of<V, 157> { using type = MotionPredictionHintsPacket; };

template <int V>
struct packet_of<V, 158> { using type = AnimateEntityPacket; };

template <int V>
struct packet_of<V, 165> { using type = SyncActorPropertyPacket; };

template <int V>
struct packet_of<V, 169> { using type = NpcDialoguePacket; };

template <int V>
struct packet_of<V, 182> { using type = ChangeMobPropertyPacket; };

template <int V>
struct packet_of<V, 189> { using type = DeathInfoPacket; };

template <int V> requires (V >= 2225)
struct packet_of<V, 357> { using type = SetPassengerOfBlockPacket_<V>; };

namespace detail {

template <>
inline constexpr std::array<base::ActorFlags, 120> values_v<base::ActorFlags>{{
    base::ActorFlags::Onfire,
    base::ActorFlags::Sneaking,
    base::ActorFlags::Riding,
    base::ActorFlags::Sprinting,
    base::ActorFlags::Usingitem,
    base::ActorFlags::Invisible,
    base::ActorFlags::Tempted,
    base::ActorFlags::Inlove,
    base::ActorFlags::Saddled,
    base::ActorFlags::Powered,
    base::ActorFlags::Ignited,
    base::ActorFlags::Baby,
    base::ActorFlags::Converting,
    base::ActorFlags::Critical,
    base::ActorFlags::CanShowName,
    base::ActorFlags::AlwaysShowName,
    base::ActorFlags::Noai,
    base::ActorFlags::Silent,
    base::ActorFlags::Wallclimbing,
    base::ActorFlags::Canclimb,
    base::ActorFlags::Canswim,
    base::ActorFlags::Canfly,
    base::ActorFlags::Canwalk,
    base::ActorFlags::Resting,
    base::ActorFlags::Sitting,
    base::ActorFlags::Angry,
    base::ActorFlags::Interested,
    base::ActorFlags::Charged,
    base::ActorFlags::Tamed,
    base::ActorFlags::Orphaned,
    base::ActorFlags::Leashed,
    base::ActorFlags::Sheared,
    base::ActorFlags::Gliding,
    base::ActorFlags::Elder,
    base::ActorFlags::Moving,
    base::ActorFlags::Breathing,
    base::ActorFlags::Chested,
    base::ActorFlags::Stackable,
    base::ActorFlags::ShowBottom,
    base::ActorFlags::Standing,
    base::ActorFlags::Shaking,
    base::ActorFlags::Idling,
    base::ActorFlags::Casting,
    base::ActorFlags::Charging,
    base::ActorFlags::WasdControlled,
    base::ActorFlags::CanPowerJump,
    base::ActorFlags::CanDash,
    base::ActorFlags::Lingering,
    base::ActorFlags::HasCollision,
    base::ActorFlags::HasGravity,
    base::ActorFlags::FireImmune,
    base::ActorFlags::Dancing,
    base::ActorFlags::Enchanted,
    base::ActorFlags::Returntrident,
    base::ActorFlags::ContainerIsPrivate,
    base::ActorFlags::IsTransforming,
    base::ActorFlags::Damagenearbymobs,
    base::ActorFlags::Swimming,
    base::ActorFlags::Bribed,
    base::ActorFlags::IsPregnant,
    base::ActorFlags::LayingEgg,
    base::ActorFlags::PassengerCanPick,
    base::ActorFlags::TransitionSitting,
    base::ActorFlags::Eating,
    base::ActorFlags::LayingDown,
    base::ActorFlags::Sneezing,
    base::ActorFlags::Trusting,
    base::ActorFlags::Rolling,
    base::ActorFlags::Scared,
    base::ActorFlags::InScaffolding,
    base::ActorFlags::OverScaffolding,
    base::ActorFlags::DescendThroughBlock,
    base::ActorFlags::Blocking,
    base::ActorFlags::TransitionBlocking,
    base::ActorFlags::BlockedUsingShield,
    base::ActorFlags::BlockedUsingDamagedShield,
    base::ActorFlags::Sleeping,
    base::ActorFlags::WantsToWake,
    base::ActorFlags::TradeInterest,
    base::ActorFlags::DoorBreaker,
    base::ActorFlags::BreakingObstruction,
    base::ActorFlags::DoorOpener,
    base::ActorFlags::IsIllagerCaptain,
    base::ActorFlags::Stunned,
    base::ActorFlags::Roaring,
    base::ActorFlags::DelayedAttack,
    base::ActorFlags::IsAvoidingMobs,
    base::ActorFlags::IsAvoidingBlock,
    base::ActorFlags::FacingTargetToRangeAttack,
    base::ActorFlags::HiddenWhenInvisible,
    base::ActorFlags::IsInUi,
    base::ActorFlags::Stalking,
    base::ActorFlags::Emoting,
    base::ActorFlags::Celebrating,
    base::ActorFlags::Admiring,
    base::ActorFlags::CelebratingSpecial,
    base::ActorFlags::OutOfControl,
    base::ActorFlags::RamAttack,
    base::ActorFlags::PlayingDead,
    base::ActorFlags::InAscendableBlock,
    base::ActorFlags::OverDescendableBlock,
    base::ActorFlags::Croaking,
    base::ActorFlags::EatMob,
    base::ActorFlags::JumpGoalJump,
    base::ActorFlags::Emerging,
    base::ActorFlags::Sniffing,
    base::ActorFlags::Digging,
    base::ActorFlags::SonicBoom,
    base::ActorFlags::HasDashCooldown,
    base::ActorFlags::PushTowardsClosestSpace,
    base::ActorFlags::Deprecated1,
    base::ActorFlags::Deprecated2,
    base::ActorFlags::Deprecated3,
    base::ActorFlags::Searching,
    base::ActorFlags::Crawling,
    base::ActorFlags::TimerFlag1,
    base::ActorFlags::TimerFlag2,
    base::ActorFlags::TimerFlag3,
    base::ActorFlags::BodyRotationBlocked,
    base::ActorFlags::Count,
}};

template <>
inline constexpr std::array<std::string_view, 120> names_v<base::ActorFlags>{{
    "onfire",
    "sneaking",
    "riding",
    "sprinting",
    "usingitem",
    "invisible",
    "tempted",
    "inlove",
    "saddled",
    "powered",
    "ignited",
    "baby",
    "converting",
    "critical",
    "canshowname",
    "alwaysshowname",
    "noai",
    "silent",
    "wallclimbing",
    "canclimb",
    "canswim",
    "canfly",
    "canwalk",
    "resting",
    "sitting",
    "angry",
    "interested",
    "charged",
    "tamed",
    "orphaned",
    "leashed",
    "sheared",
    "gliding",
    "elder",
    "moving",
    "breathing",
    "chested",
    "stackable",
    "showbottom",
    "standing",
    "shaking",
    "idling",
    "casting",
    "charging",
    "wasdcontrolled",
    "canpowerjump",
    "candash",
    "lingering",
    "hascollision",
    "hasgravity",
    "fireimmune",
    "dancing",
    "enchanted",
    "returntrident",
    "containerisprivate",
    "istransforming",
    "damagenearbymobs",
    "swimming",
    "bribed",
    "ispregnant",
    "layingegg",
    "passengercanpick",
    "transitionsitting",
    "eating",
    "layingdown",
    "sneezing",
    "trusting",
    "rolling",
    "scared",
    "inscaffolding",
    "overscaffolding",
    "descendthroughblock",
    "blocking",
    "transitionblocking",
    "blockedusingshield",
    "blockedusingdamagedshield",
    "sleeping",
    "wantstowake",
    "tradeinterest",
    "doorbreaker",
    "breakingobstruction",
    "dooropener",
    "isillagercaptain",
    "stunned",
    "roaring",
    "delayedattack",
    "isavoidingmobs",
    "isavoidingblock",
    "facingtargettorangeattack",
    "hiddenwheninvisible",
    "isinui",
    "stalking",
    "emoting",
    "celebrating",
    "admiring",
    "celebratingspecial",
    "outofcontrol",
    "ramattack",
    "playingdead",
    "inascendableblock",
    "overdescendableblock",
    "croaking",
    "eatmob",
    "jumpgoaljump",
    "emerging",
    "sniffing",
    "digging",
    "sonicboom",
    "hasdashcooldown",
    "pushtowardsclosestspace",
    "deprecated1",
    "deprecated2",
    "deprecated3",
    "searching",
    "crawling",
    "timerflag1",
    "timerflag2",
    "timerflag3",
    "bodyrotationblocked",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<base::ActorFlags>{"ActorFlags"};

template <>
inline constexpr std::array<v776::ActorFlags, 121> values_v<v776::ActorFlags>{{
    v776::ActorFlags::Onfire,
    v776::ActorFlags::Sneaking,
    v776::ActorFlags::Riding,
    v776::ActorFlags::Sprinting,
    v776::ActorFlags::Usingitem,
    v776::ActorFlags::Invisible,
    v776::ActorFlags::Tempted,
    v776::ActorFlags::Inlove,
    v776::ActorFlags::Saddled,
    v776::ActorFlags::Powered,
    v776::ActorFlags::Ignited,
    v776::ActorFlags::Baby,
    v776::ActorFlags::Converting,
    v776::ActorFlags::Critical,
    v776::ActorFlags::CanShowName,
    v776::ActorFlags::AlwaysShowName,
    v776::ActorFlags::Noai,
    v776::ActorFlags::Silent,
    v776::ActorFlags::Wallclimbing,
    v776::ActorFlags::Canclimb,
    v776::ActorFlags::Canswim,
    v776::ActorFlags::Canfly,
    v776::ActorFlags::Canwalk,
    v776::ActorFlags::Resting,
    v776::ActorFlags::Sitting,
    v776::ActorFlags::Angry,
    v776::ActorFlags::Interested,
    v776::ActorFlags::Charged,
    v776::ActorFlags::Tamed,
    v776::ActorFlags::Orphaned,
    v776::ActorFlags::Leashed,
    v776::ActorFlags::Sheared,
    v776::ActorFlags::Gliding,
    v776::ActorFlags::Elder,
    v776::ActorFlags::Moving,
    v776::ActorFlags::Breathing,
    v776::ActorFlags::Chested,
    v776::ActorFlags::Stackable,
    v776::ActorFlags::ShowBottom,
    v776::ActorFlags::Standing,
    v776::ActorFlags::Shaking,
    v776::ActorFlags::Idling,
    v776::ActorFlags::Casting,
    v776::ActorFlags::Charging,
    v776::ActorFlags::WasdControlled,
    v776::ActorFlags::CanPowerJump,
    v776::ActorFlags::CanDash,
    v776::ActorFlags::Lingering,
    v776::ActorFlags::HasCollision,
    v776::ActorFlags::HasGravity,
    v776::ActorFlags::FireImmune,
    v776::ActorFlags::Dancing,
    v776::ActorFlags::Enchanted,
    v776::ActorFlags::Returntrident,
    v776::ActorFlags::ContainerIsPrivate,
    v776::ActorFlags::IsTransforming,
    v776::ActorFlags::Damagenearbymobs,
    v776::ActorFlags::Swimming,
    v776::ActorFlags::Bribed,
    v776::ActorFlags::IsPregnant,
    v776::ActorFlags::LayingEgg,
    v776::ActorFlags::PassengerCanPick,
    v776::ActorFlags::TransitionSitting,
    v776::ActorFlags::Eating,
    v776::ActorFlags::LayingDown,
    v776::ActorFlags::Sneezing,
    v776::ActorFlags::Trusting,
    v776::ActorFlags::Rolling,
    v776::ActorFlags::Scared,
    v776::ActorFlags::InScaffolding,
    v776::ActorFlags::OverScaffolding,
    v776::ActorFlags::DescendThroughBlock,
    v776::ActorFlags::Blocking,
    v776::ActorFlags::TransitionBlocking,
    v776::ActorFlags::BlockedUsingShield,
    v776::ActorFlags::BlockedUsingDamagedShield,
    v776::ActorFlags::Sleeping,
    v776::ActorFlags::WantsToWake,
    v776::ActorFlags::TradeInterest,
    v776::ActorFlags::DoorBreaker,
    v776::ActorFlags::BreakingObstruction,
    v776::ActorFlags::DoorOpener,
    v776::ActorFlags::IsIllagerCaptain,
    v776::ActorFlags::Stunned,
    v776::ActorFlags::Roaring,
    v776::ActorFlags::DelayedAttack,
    v776::ActorFlags::IsAvoidingMobs,
    v776::ActorFlags::IsAvoidingBlock,
    v776::ActorFlags::FacingTargetToRangeAttack,
    v776::ActorFlags::HiddenWhenInvisible,
    v776::ActorFlags::IsInUi,
    v776::ActorFlags::Stalking,
    v776::ActorFlags::Emoting,
    v776::ActorFlags::Celebrating,
    v776::ActorFlags::Admiring,
    v776::ActorFlags::CelebratingSpecial,
    v776::ActorFlags::OutOfControl,
    v776::ActorFlags::RamAttack,
    v776::ActorFlags::PlayingDead,
    v776::ActorFlags::InAscendableBlock,
    v776::ActorFlags::OverDescendableBlock,
    v776::ActorFlags::Croaking,
    v776::ActorFlags::EatMob,
    v776::ActorFlags::JumpGoalJump,
    v776::ActorFlags::Emerging,
    v776::ActorFlags::Sniffing,
    v776::ActorFlags::Digging,
    v776::ActorFlags::SonicBoom,
    v776::ActorFlags::HasDashCooldown,
    v776::ActorFlags::PushTowardsClosestSpace,
    v776::ActorFlags::Deprecated1,
    v776::ActorFlags::Deprecated2,
    v776::ActorFlags::Deprecated3,
    v776::ActorFlags::Searching,
    v776::ActorFlags::Crawling,
    v776::ActorFlags::TimerFlag1,
    v776::ActorFlags::TimerFlag2,
    v776::ActorFlags::TimerFlag3,
    v776::ActorFlags::BodyRotationBlocked,
    v776::ActorFlags::RendersWhenInvisible,
    v776::ActorFlags::Count,
}};

template <>
inline constexpr std::array<std::string_view, 121> names_v<v776::ActorFlags>{{
    "onfire",
    "sneaking",
    "riding",
    "sprinting",
    "usingitem",
    "invisible",
    "tempted",
    "inlove",
    "saddled",
    "powered",
    "ignited",
    "baby",
    "converting",
    "critical",
    "canshowname",
    "alwaysshowname",
    "noai",
    "silent",
    "wallclimbing",
    "canclimb",
    "canswim",
    "canfly",
    "canwalk",
    "resting",
    "sitting",
    "angry",
    "interested",
    "charged",
    "tamed",
    "orphaned",
    "leashed",
    "sheared",
    "gliding",
    "elder",
    "moving",
    "breathing",
    "chested",
    "stackable",
    "showbottom",
    "standing",
    "shaking",
    "idling",
    "casting",
    "charging",
    "wasdcontrolled",
    "canpowerjump",
    "candash",
    "lingering",
    "hascollision",
    "hasgravity",
    "fireimmune",
    "dancing",
    "enchanted",
    "returntrident",
    "containerisprivate",
    "istransforming",
    "damagenearbymobs",
    "swimming",
    "bribed",
    "ispregnant",
    "layingegg",
    "passengercanpick",
    "transitionsitting",
    "eating",
    "layingdown",
    "sneezing",
    "trusting",
    "rolling",
    "scared",
    "inscaffolding",
    "overscaffolding",
    "descendthroughblock",
    "blocking",
    "transitionblocking",
    "blockedusingshield",
    "blockedusingdamagedshield",
    "sleeping",
    "wantstowake",
    "tradeinterest",
    "doorbreaker",
    "breakingobstruction",
    "dooropener",
    "isillagercaptain",
    "stunned",
    "roaring",
    "delayedattack",
    "isavoidingmobs",
    "isavoidingblock",
    "facingtargettorangeattack",
    "hiddenwheninvisible",
    "isinui",
    "stalking",
    "emoting",
    "celebrating",
    "admiring",
    "celebratingspecial",
    "outofcontrol",
    "ramattack",
    "playingdead",
    "inascendableblock",
    "overdescendableblock",
    "croaking",
    "eatmob",
    "jumpgoaljump",
    "emerging",
    "sniffing",
    "digging",
    "sonicboom",
    "hasdashcooldown",
    "pushtowardsclosestspace",
    "deprecated1",
    "deprecated2",
    "deprecated3",
    "searching",
    "crawling",
    "timerflag1",
    "timerflag2",
    "timerflag3",
    "bodyrotationblocked",
    "renderswheninvisible",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<v776::ActorFlags>{"ActorFlags"};

template <>
inline constexpr std::array<v786::ActorFlags, 124> values_v<v786::ActorFlags>{{
    v786::ActorFlags::Onfire,
    v786::ActorFlags::Sneaking,
    v786::ActorFlags::Riding,
    v786::ActorFlags::Sprinting,
    v786::ActorFlags::Usingitem,
    v786::ActorFlags::Invisible,
    v786::ActorFlags::Tempted,
    v786::ActorFlags::Inlove,
    v786::ActorFlags::Saddled,
    v786::ActorFlags::Powered,
    v786::ActorFlags::Ignited,
    v786::ActorFlags::Baby,
    v786::ActorFlags::Converting,
    v786::ActorFlags::Critical,
    v786::ActorFlags::CanShowName,
    v786::ActorFlags::AlwaysShowName,
    v786::ActorFlags::Noai,
    v786::ActorFlags::Silent,
    v786::ActorFlags::Wallclimbing,
    v786::ActorFlags::Canclimb,
    v786::ActorFlags::Canswim,
    v786::ActorFlags::Canfly,
    v786::ActorFlags::Canwalk,
    v786::ActorFlags::Resting,
    v786::ActorFlags::Sitting,
    v786::ActorFlags::Angry,
    v786::ActorFlags::Interested,
    v786::ActorFlags::Charged,
    v786::ActorFlags::Tamed,
    v786::ActorFlags::Orphaned,
    v786::ActorFlags::Leashed,
    v786::ActorFlags::Sheared,
    v786::ActorFlags::Gliding,
    v786::ActorFlags::Elder,
    v786::ActorFlags::Moving,
    v786::ActorFlags::Breathing,
    v786::ActorFlags::Chested,
    v786::ActorFlags::Stackable,
    v786::ActorFlags::ShowBottom,
    v786::ActorFlags::Standing,
    v786::ActorFlags::Shaking,
    v786::ActorFlags::Idling,
    v786::ActorFlags::Casting,
    v786::ActorFlags::Charging,
    v786::ActorFlags::WasdControlled,
    v786::ActorFlags::CanPowerJump,
    v786::ActorFlags::CanDash,
    v786::ActorFlags::Lingering,
    v786::ActorFlags::HasCollision,
    v786::ActorFlags::HasGravity,
    v786::ActorFlags::FireImmune,
    v786::ActorFlags::Dancing,
    v786::ActorFlags::Enchanted,
    v786::ActorFlags::Returntrident,
    v786::ActorFlags::ContainerIsPrivate,
    v786::ActorFlags::IsTransforming,
    v786::ActorFlags::Damagenearbymobs,
    v786::ActorFlags::Swimming,
    v786::ActorFlags::Bribed,
    v786::ActorFlags::IsPregnant,
    v786::ActorFlags::LayingEgg,
    v786::ActorFlags::PassengerCanPick,
    v786::ActorFlags::TransitionSitting,
    v786::ActorFlags::Eating,
    v786::ActorFlags::LayingDown,
    v786::ActorFlags::Sneezing,
    v786::ActorFlags::Trusting,
    v786::ActorFlags::Rolling,
    v786::ActorFlags::Scared,
    v786::ActorFlags::InScaffolding,
    v786::ActorFlags::OverScaffolding,
    v786::ActorFlags::DescendThroughBlock,
    v786::ActorFlags::Blocking,
    v786::ActorFlags::TransitionBlocking,
    v786::ActorFlags::BlockedUsingShield,
    v786::ActorFlags::BlockedUsingDamagedShield,
    v786::ActorFlags::Sleeping,
    v786::ActorFlags::WantsToWake,
    v786::ActorFlags::TradeInterest,
    v786::ActorFlags::DoorBreaker,
    v786::ActorFlags::BreakingObstruction,
    v786::ActorFlags::DoorOpener,
    v786::ActorFlags::IsIllagerCaptain,
    v786::ActorFlags::Stunned,
    v786::ActorFlags::Roaring,
    v786::ActorFlags::DelayedAttack,
    v786::ActorFlags::IsAvoidingMobs,
    v786::ActorFlags::IsAvoidingBlock,
    v786::ActorFlags::FacingTargetToRangeAttack,
    v786::ActorFlags::HiddenWhenInvisible,
    v786::ActorFlags::IsInUi,
    v786::ActorFlags::Stalking,
    v786::ActorFlags::Emoting,
    v786::ActorFlags::Celebrating,
    v786::ActorFlags::Admiring,
    v786::ActorFlags::CelebratingSpecial,
    v786::ActorFlags::OutOfControl,
    v786::ActorFlags::RamAttack,
    v786::ActorFlags::PlayingDead,
    v786::ActorFlags::InAscendableBlock,
    v786::ActorFlags::OverDescendableBlock,
    v786::ActorFlags::Croaking,
    v786::ActorFlags::EatMob,
    v786::ActorFlags::JumpGoalJump,
    v786::ActorFlags::Emerging,
    v786::ActorFlags::Sniffing,
    v786::ActorFlags::Digging,
    v786::ActorFlags::SonicBoom,
    v786::ActorFlags::HasDashCooldown,
    v786::ActorFlags::PushTowardsClosestSpace,
    v786::ActorFlags::Deprecated1,
    v786::ActorFlags::Deprecated2,
    v786::ActorFlags::Deprecated3,
    v786::ActorFlags::Searching,
    v786::ActorFlags::Crawling,
    v786::ActorFlags::TimerFlag1,
    v786::ActorFlags::TimerFlag2,
    v786::ActorFlags::TimerFlag3,
    v786::ActorFlags::BodyRotationBlocked,
    v786::ActorFlags::RendersWhenInvisible,
    v786::ActorFlags::RotationAxisAligned,
    v786::ActorFlags::Collidable,
    v786::ActorFlags::WasdFreeCameraControlled,
    v786::ActorFlags::Count,
}};

template <>
inline constexpr std::array<std::string_view, 124> names_v<v786::ActorFlags>{{
    "onfire",
    "sneaking",
    "riding",
    "sprinting",
    "usingitem",
    "invisible",
    "tempted",
    "inlove",
    "saddled",
    "powered",
    "ignited",
    "baby",
    "converting",
    "critical",
    "canshowname",
    "alwaysshowname",
    "noai",
    "silent",
    "wallclimbing",
    "canclimb",
    "canswim",
    "canfly",
    "canwalk",
    "resting",
    "sitting",
    "angry",
    "interested",
    "charged",
    "tamed",
    "orphaned",
    "leashed",
    "sheared",
    "gliding",
    "elder",
    "moving",
    "breathing",
    "chested",
    "stackable",
    "showbottom",
    "standing",
    "shaking",
    "idling",
    "casting",
    "charging",
    "wasdcontrolled",
    "canpowerjump",
    "candash",
    "lingering",
    "hascollision",
    "hasgravity",
    "fireimmune",
    "dancing",
    "enchanted",
    "returntrident",
    "containerisprivate",
    "istransforming",
    "damagenearbymobs",
    "swimming",
    "bribed",
    "ispregnant",
    "layingegg",
    "passengercanpick",
    "transitionsitting",
    "eating",
    "layingdown",
    "sneezing",
    "trusting",
    "rolling",
    "scared",
    "inscaffolding",
    "overscaffolding",
    "descendthroughblock",
    "blocking",
    "transitionblocking",
    "blockedusingshield",
    "blockedusingdamagedshield",
    "sleeping",
    "wantstowake",
    "tradeinterest",
    "doorbreaker",
    "breakingobstruction",
    "dooropener",
    "isillagercaptain",
    "stunned",
    "roaring",
    "delayedattack",
    "isavoidingmobs",
    "isavoidingblock",
    "facingtargettorangeattack",
    "hiddenwheninvisible",
    "isinui",
    "stalking",
    "emoting",
    "celebrating",
    "admiring",
    "celebratingspecial",
    "outofcontrol",
    "ramattack",
    "playingdead",
    "inascendableblock",
    "overdescendableblock",
    "croaking",
    "eatmob",
    "jumpgoaljump",
    "emerging",
    "sniffing",
    "digging",
    "sonicboom",
    "hasdashcooldown",
    "pushtowardsclosestspace",
    "deprecated1",
    "deprecated2",
    "deprecated3",
    "searching",
    "crawling",
    "timerflag1",
    "timerflag2",
    "timerflag3",
    "bodyrotationblocked",
    "renderswheninvisible",
    "rotationaxisaligned",
    "collidable",
    "wasdfreecameracontrolled",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<v786::ActorFlags>{"ActorFlags"};

template <>
inline constexpr std::array<v800::ActorFlags, 125> values_v<v800::ActorFlags>{{
    v800::ActorFlags::Onfire,
    v800::ActorFlags::Sneaking,
    v800::ActorFlags::Riding,
    v800::ActorFlags::Sprinting,
    v800::ActorFlags::Usingitem,
    v800::ActorFlags::Invisible,
    v800::ActorFlags::Tempted,
    v800::ActorFlags::Inlove,
    v800::ActorFlags::Saddled,
    v800::ActorFlags::Powered,
    v800::ActorFlags::Ignited,
    v800::ActorFlags::Baby,
    v800::ActorFlags::Converting,
    v800::ActorFlags::Critical,
    v800::ActorFlags::CanShowName,
    v800::ActorFlags::AlwaysShowName,
    v800::ActorFlags::Noai,
    v800::ActorFlags::Silent,
    v800::ActorFlags::Wallclimbing,
    v800::ActorFlags::Canclimb,
    v800::ActorFlags::Canswim,
    v800::ActorFlags::Canfly,
    v800::ActorFlags::Canwalk,
    v800::ActorFlags::Resting,
    v800::ActorFlags::Sitting,
    v800::ActorFlags::Angry,
    v800::ActorFlags::Interested,
    v800::ActorFlags::Charged,
    v800::ActorFlags::Tamed,
    v800::ActorFlags::Orphaned,
    v800::ActorFlags::Leashed,
    v800::ActorFlags::Sheared,
    v800::ActorFlags::Gliding,
    v800::ActorFlags::Elder,
    v800::ActorFlags::Moving,
    v800::ActorFlags::Breathing,
    v800::ActorFlags::Chested,
    v800::ActorFlags::Stackable,
    v800::ActorFlags::ShowBottom,
    v800::ActorFlags::Standing,
    v800::ActorFlags::Shaking,
    v800::ActorFlags::Idling,
    v800::ActorFlags::Casting,
    v800::ActorFlags::Charging,
    v800::ActorFlags::WasdControlled,
    v800::ActorFlags::CanPowerJump,
    v800::ActorFlags::CanDash,
    v800::ActorFlags::Lingering,
    v800::ActorFlags::HasCollision,
    v800::ActorFlags::HasGravity,
    v800::ActorFlags::FireImmune,
    v800::ActorFlags::Dancing,
    v800::ActorFlags::Enchanted,
    v800::ActorFlags::Returntrident,
    v800::ActorFlags::ContainerIsPrivate,
    v800::ActorFlags::IsTransforming,
    v800::ActorFlags::Damagenearbymobs,
    v800::ActorFlags::Swimming,
    v800::ActorFlags::Bribed,
    v800::ActorFlags::IsPregnant,
    v800::ActorFlags::LayingEgg,
    v800::ActorFlags::PassengerCanPick,
    v800::ActorFlags::TransitionSitting,
    v800::ActorFlags::Eating,
    v800::ActorFlags::LayingDown,
    v800::ActorFlags::Sneezing,
    v800::ActorFlags::Trusting,
    v800::ActorFlags::Rolling,
    v800::ActorFlags::Scared,
    v800::ActorFlags::InScaffolding,
    v800::ActorFlags::OverScaffolding,
    v800::ActorFlags::DescendThroughBlock,
    v800::ActorFlags::Blocking,
    v800::ActorFlags::TransitionBlocking,
    v800::ActorFlags::BlockedUsingShield,
    v800::ActorFlags::BlockedUsingDamagedShield,
    v800::ActorFlags::Sleeping,
    v800::ActorFlags::WantsToWake,
    v800::ActorFlags::TradeInterest,
    v800::ActorFlags::DoorBreaker,
    v800::ActorFlags::BreakingObstruction,
    v800::ActorFlags::DoorOpener,
    v800::ActorFlags::IsIllagerCaptain,
    v800::ActorFlags::Stunned,
    v800::ActorFlags::Roaring,
    v800::ActorFlags::DelayedAttack,
    v800::ActorFlags::IsAvoidingMobs,
    v800::ActorFlags::IsAvoidingBlock,
    v800::ActorFlags::FacingTargetToRangeAttack,
    v800::ActorFlags::HiddenWhenInvisible,
    v800::ActorFlags::IsInUi,
    v800::ActorFlags::Stalking,
    v800::ActorFlags::Emoting,
    v800::ActorFlags::Celebrating,
    v800::ActorFlags::Admiring,
    v800::ActorFlags::CelebratingSpecial,
    v800::ActorFlags::OutOfControl,
    v800::ActorFlags::RamAttack,
    v800::ActorFlags::PlayingDead,
    v800::ActorFlags::InAscendableBlock,
    v800::ActorFlags::OverDescendableBlock,
    v800::ActorFlags::Croaking,
    v800::ActorFlags::EatMob,
    v800::ActorFlags::JumpGoalJump,
    v800::ActorFlags::Emerging,
    v800::ActorFlags::Sniffing,
    v800::ActorFlags::Digging,
    v800::ActorFlags::SonicBoom,
    v800::ActorFlags::HasDashCooldown,
    v800::ActorFlags::PushTowardsClosestSpace,
    v800::ActorFlags::Deprecated1,
    v800::ActorFlags::Deprecated2,
    v800::ActorFlags::Deprecated3,
    v800::ActorFlags::Searching,
    v800::ActorFlags::Crawling,
    v800::ActorFlags::TimerFlag1,
    v800::ActorFlags::TimerFlag2,
    v800::ActorFlags::TimerFlag3,
    v800::ActorFlags::BodyRotationBlocked,
    v800::ActorFlags::RendersWhenInvisible,
    v800::ActorFlags::RotationAxisAligned,
    v800::ActorFlags::Collidable,
    v800::ActorFlags::WasdFreeCameraControlled,
    v800::ActorFlags::DoesServerAuthOnlyDismount,
    v800::ActorFlags::Count,
}};

template <>
inline constexpr std::array<std::string_view, 125> names_v<v800::ActorFlags>{{
    "onfire",
    "sneaking",
    "riding",
    "sprinting",
    "usingitem",
    "invisible",
    "tempted",
    "inlove",
    "saddled",
    "powered",
    "ignited",
    "baby",
    "converting",
    "critical",
    "canshowname",
    "alwaysshowname",
    "noai",
    "silent",
    "wallclimbing",
    "canclimb",
    "canswim",
    "canfly",
    "canwalk",
    "resting",
    "sitting",
    "angry",
    "interested",
    "charged",
    "tamed",
    "orphaned",
    "leashed",
    "sheared",
    "gliding",
    "elder",
    "moving",
    "breathing",
    "chested",
    "stackable",
    "showbottom",
    "standing",
    "shaking",
    "idling",
    "casting",
    "charging",
    "wasdcontrolled",
    "canpowerjump",
    "candash",
    "lingering",
    "hascollision",
    "hasgravity",
    "fireimmune",
    "dancing",
    "enchanted",
    "returntrident",
    "containerisprivate",
    "istransforming",
    "damagenearbymobs",
    "swimming",
    "bribed",
    "ispregnant",
    "layingegg",
    "passengercanpick",
    "transitionsitting",
    "eating",
    "layingdown",
    "sneezing",
    "trusting",
    "rolling",
    "scared",
    "inscaffolding",
    "overscaffolding",
    "descendthroughblock",
    "blocking",
    "transitionblocking",
    "blockedusingshield",
    "blockedusingdamagedshield",
    "sleeping",
    "wantstowake",
    "tradeinterest",
    "doorbreaker",
    "breakingobstruction",
    "dooropener",
    "isillagercaptain",
    "stunned",
    "roaring",
    "delayedattack",
    "isavoidingmobs",
    "isavoidingblock",
    "facingtargettorangeattack",
    "hiddenwheninvisible",
    "isinui",
    "stalking",
    "emoting",
    "celebrating",
    "admiring",
    "celebratingspecial",
    "outofcontrol",
    "ramattack",
    "playingdead",
    "inascendableblock",
    "overdescendableblock",
    "croaking",
    "eatmob",
    "jumpgoaljump",
    "emerging",
    "sniffing",
    "digging",
    "sonicboom",
    "hasdashcooldown",
    "pushtowardsclosestspace",
    "deprecated1",
    "deprecated2",
    "deprecated3",
    "searching",
    "crawling",
    "timerflag1",
    "timerflag2",
    "timerflag3",
    "bodyrotationblocked",
    "renderswheninvisible",
    "rotationaxisaligned",
    "collidable",
    "wasdfreecameracontrolled",
    "doesserverauthonlydismount",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<v800::ActorFlags>{"ActorFlags"};

template <>
inline constexpr std::array<v818::ActorFlags, 126> values_v<v818::ActorFlags>{{
    v818::ActorFlags::Onfire,
    v818::ActorFlags::Sneaking,
    v818::ActorFlags::Riding,
    v818::ActorFlags::Sprinting,
    v818::ActorFlags::Usingitem,
    v818::ActorFlags::Invisible,
    v818::ActorFlags::Tempted,
    v818::ActorFlags::Inlove,
    v818::ActorFlags::Saddled,
    v818::ActorFlags::Powered,
    v818::ActorFlags::Ignited,
    v818::ActorFlags::Baby,
    v818::ActorFlags::Converting,
    v818::ActorFlags::Critical,
    v818::ActorFlags::CanShowName,
    v818::ActorFlags::AlwaysShowName,
    v818::ActorFlags::Noai,
    v818::ActorFlags::Silent,
    v818::ActorFlags::Wallclimbing,
    v818::ActorFlags::Canclimb,
    v818::ActorFlags::Canswim,
    v818::ActorFlags::Canfly,
    v818::ActorFlags::Canwalk,
    v818::ActorFlags::Resting,
    v818::ActorFlags::Sitting,
    v818::ActorFlags::Angry,
    v818::ActorFlags::Interested,
    v818::ActorFlags::Charged,
    v818::ActorFlags::Tamed,
    v818::ActorFlags::Orphaned,
    v818::ActorFlags::Leashed,
    v818::ActorFlags::Sheared,
    v818::ActorFlags::Gliding,
    v818::ActorFlags::Elder,
    v818::ActorFlags::Moving,
    v818::ActorFlags::Breathing,
    v818::ActorFlags::Chested,
    v818::ActorFlags::Stackable,
    v818::ActorFlags::ShowBottom,
    v818::ActorFlags::Standing,
    v818::ActorFlags::Shaking,
    v818::ActorFlags::Idling,
    v818::ActorFlags::Casting,
    v818::ActorFlags::Charging,
    v818::ActorFlags::WasdControlled,
    v818::ActorFlags::CanPowerJump,
    v818::ActorFlags::CanDash,
    v818::ActorFlags::Lingering,
    v818::ActorFlags::HasCollision,
    v818::ActorFlags::HasGravity,
    v818::ActorFlags::FireImmune,
    v818::ActorFlags::Dancing,
    v818::ActorFlags::Enchanted,
    v818::ActorFlags::Returntrident,
    v818::ActorFlags::ContainerIsPrivate,
    v818::ActorFlags::IsTransforming,
    v818::ActorFlags::Damagenearbymobs,
    v818::ActorFlags::Swimming,
    v818::ActorFlags::Bribed,
    v818::ActorFlags::IsPregnant,
    v818::ActorFlags::LayingEgg,
    v818::ActorFlags::PassengerCanPick,
    v818::ActorFlags::TransitionSitting,
    v818::ActorFlags::Eating,
    v818::ActorFlags::LayingDown,
    v818::ActorFlags::Sneezing,
    v818::ActorFlags::Trusting,
    v818::ActorFlags::Rolling,
    v818::ActorFlags::Scared,
    v818::ActorFlags::InScaffolding,
    v818::ActorFlags::OverScaffolding,
    v818::ActorFlags::DescendThroughBlock,
    v818::ActorFlags::Blocking,
    v818::ActorFlags::TransitionBlocking,
    v818::ActorFlags::BlockedUsingShield,
    v818::ActorFlags::BlockedUsingDamagedShield,
    v818::ActorFlags::Sleeping,
    v818::ActorFlags::WantsToWake,
    v818::ActorFlags::TradeInterest,
    v818::ActorFlags::DoorBreaker,
    v818::ActorFlags::BreakingObstruction,
    v818::ActorFlags::DoorOpener,
    v818::ActorFlags::IsIllagerCaptain,
    v818::ActorFlags::Stunned,
    v818::ActorFlags::Roaring,
    v818::ActorFlags::DelayedAttack,
    v818::ActorFlags::IsAvoidingMobs,
    v818::ActorFlags::IsAvoidingBlock,
    v818::ActorFlags::FacingTargetToRangeAttack,
    v818::ActorFlags::HiddenWhenInvisible,
    v818::ActorFlags::IsInUi,
    v818::ActorFlags::Stalking,
    v818::ActorFlags::Emoting,
    v818::ActorFlags::Celebrating,
    v818::ActorFlags::Admiring,
    v818::ActorFlags::CelebratingSpecial,
    v818::ActorFlags::OutOfControl,
    v818::ActorFlags::RamAttack,
    v818::ActorFlags::PlayingDead,
    v818::ActorFlags::InAscendableBlock,
    v818::ActorFlags::OverDescendableBlock,
    v818::ActorFlags::Croaking,
    v818::ActorFlags::EatMob,
    v818::ActorFlags::JumpGoalJump,
    v818::ActorFlags::Emerging,
    v818::ActorFlags::Sniffing,
    v818::ActorFlags::Digging,
    v818::ActorFlags::SonicBoom,
    v818::ActorFlags::HasDashCooldown,
    v818::ActorFlags::PushTowardsClosestSpace,
    v818::ActorFlags::Deprecated1,
    v818::ActorFlags::Deprecated2,
    v818::ActorFlags::Deprecated3,
    v818::ActorFlags::Searching,
    v818::ActorFlags::Crawling,
    v818::ActorFlags::TimerFlag1,
    v818::ActorFlags::TimerFlag2,
    v818::ActorFlags::TimerFlag3,
    v818::ActorFlags::BodyRotationBlocked,
    v818::ActorFlags::RendersWhenInvisible,
    v818::ActorFlags::RotationAxisAligned,
    v818::ActorFlags::Collidable,
    v818::ActorFlags::WasdFreeCameraControlled,
    v818::ActorFlags::DoesServerAuthOnlyDismount,
    v818::ActorFlags::BodyRotationAlwaysFollowsHead,
    v818::ActorFlags::Count,
}};

template <>
inline constexpr std::array<std::string_view, 126> names_v<v818::ActorFlags>{{
    "onfire",
    "sneaking",
    "riding",
    "sprinting",
    "usingitem",
    "invisible",
    "tempted",
    "inlove",
    "saddled",
    "powered",
    "ignited",
    "baby",
    "converting",
    "critical",
    "canshowname",
    "alwaysshowname",
    "noai",
    "silent",
    "wallclimbing",
    "canclimb",
    "canswim",
    "canfly",
    "canwalk",
    "resting",
    "sitting",
    "angry",
    "interested",
    "charged",
    "tamed",
    "orphaned",
    "leashed",
    "sheared",
    "gliding",
    "elder",
    "moving",
    "breathing",
    "chested",
    "stackable",
    "showbottom",
    "standing",
    "shaking",
    "idling",
    "casting",
    "charging",
    "wasdcontrolled",
    "canpowerjump",
    "candash",
    "lingering",
    "hascollision",
    "hasgravity",
    "fireimmune",
    "dancing",
    "enchanted",
    "returntrident",
    "containerisprivate",
    "istransforming",
    "damagenearbymobs",
    "swimming",
    "bribed",
    "ispregnant",
    "layingegg",
    "passengercanpick",
    "transitionsitting",
    "eating",
    "layingdown",
    "sneezing",
    "trusting",
    "rolling",
    "scared",
    "inscaffolding",
    "overscaffolding",
    "descendthroughblock",
    "blocking",
    "transitionblocking",
    "blockedusingshield",
    "blockedusingdamagedshield",
    "sleeping",
    "wantstowake",
    "tradeinterest",
    "doorbreaker",
    "breakingobstruction",
    "dooropener",
    "isillagercaptain",
    "stunned",
    "roaring",
    "delayedattack",
    "isavoidingmobs",
    "isavoidingblock",
    "facingtargettorangeattack",
    "hiddenwheninvisible",
    "isinui",
    "stalking",
    "emoting",
    "celebrating",
    "admiring",
    "celebratingspecial",
    "outofcontrol",
    "ramattack",
    "playingdead",
    "inascendableblock",
    "overdescendableblock",
    "croaking",
    "eatmob",
    "jumpgoaljump",
    "emerging",
    "sniffing",
    "digging",
    "sonicboom",
    "hasdashcooldown",
    "pushtowardsclosestspace",
    "deprecated1",
    "deprecated2",
    "deprecated3",
    "searching",
    "crawling",
    "timerflag1",
    "timerflag2",
    "timerflag3",
    "bodyrotationblocked",
    "renderswheninvisible",
    "rotationaxisaligned",
    "collidable",
    "wasdfreecameracontrolled",
    "doesserverauthonlydismount",
    "bodyrotationalwaysfollowshead",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<v818::ActorFlags>{"ActorFlags"};

template <>
inline constexpr std::array<v844::ActorFlags, 127> values_v<v844::ActorFlags>{{
    v844::ActorFlags::Onfire,
    v844::ActorFlags::Sneaking,
    v844::ActorFlags::Riding,
    v844::ActorFlags::Sprinting,
    v844::ActorFlags::Usingitem,
    v844::ActorFlags::Invisible,
    v844::ActorFlags::Tempted,
    v844::ActorFlags::Inlove,
    v844::ActorFlags::Saddled,
    v844::ActorFlags::Powered,
    v844::ActorFlags::Ignited,
    v844::ActorFlags::Baby,
    v844::ActorFlags::Converting,
    v844::ActorFlags::Critical,
    v844::ActorFlags::CanShowName,
    v844::ActorFlags::AlwaysShowName,
    v844::ActorFlags::Noai,
    v844::ActorFlags::Silent,
    v844::ActorFlags::Wallclimbing,
    v844::ActorFlags::Canclimb,
    v844::ActorFlags::Canswim,
    v844::ActorFlags::Canfly,
    v844::ActorFlags::Canwalk,
    v844::ActorFlags::Resting,
    v844::ActorFlags::Sitting,
    v844::ActorFlags::Angry,
    v844::ActorFlags::Interested,
    v844::ActorFlags::Charged,
    v844::ActorFlags::Tamed,
    v844::ActorFlags::Orphaned,
    v844::ActorFlags::Leashed,
    v844::ActorFlags::Sheared,
    v844::ActorFlags::Gliding,
    v844::ActorFlags::Elder,
    v844::ActorFlags::Moving,
    v844::ActorFlags::Breathing,
    v844::ActorFlags::Chested,
    v844::ActorFlags::Stackable,
    v844::ActorFlags::ShowBottom,
    v844::ActorFlags::Standing,
    v844::ActorFlags::Shaking,
    v844::ActorFlags::Idling,
    v844::ActorFlags::Casting,
    v844::ActorFlags::Charging,
    v844::ActorFlags::WasdControlled,
    v844::ActorFlags::CanPowerJump,
    v844::ActorFlags::CanDash,
    v844::ActorFlags::Lingering,
    v844::ActorFlags::HasCollision,
    v844::ActorFlags::HasGravity,
    v844::ActorFlags::FireImmune,
    v844::ActorFlags::Dancing,
    v844::ActorFlags::Enchanted,
    v844::ActorFlags::Returntrident,
    v844::ActorFlags::ContainerIsPrivate,
    v844::ActorFlags::IsTransforming,
    v844::ActorFlags::Damagenearbymobs,
    v844::ActorFlags::Swimming,
    v844::ActorFlags::Bribed,
    v844::ActorFlags::IsPregnant,
    v844::ActorFlags::LayingEgg,
    v844::ActorFlags::PassengerCanPick,
    v844::ActorFlags::TransitionSitting,
    v844::ActorFlags::Eating,
    v844::ActorFlags::LayingDown,
    v844::ActorFlags::Sneezing,
    v844::ActorFlags::Trusting,
    v844::ActorFlags::Rolling,
    v844::ActorFlags::Scared,
    v844::ActorFlags::InScaffolding,
    v844::ActorFlags::OverScaffolding,
    v844::ActorFlags::DescendThroughBlock,
    v844::ActorFlags::Blocking,
    v844::ActorFlags::TransitionBlocking,
    v844::ActorFlags::BlockedUsingShield,
    v844::ActorFlags::BlockedUsingDamagedShield,
    v844::ActorFlags::Sleeping,
    v844::ActorFlags::WantsToWake,
    v844::ActorFlags::TradeInterest,
    v844::ActorFlags::DoorBreaker,
    v844::ActorFlags::BreakingObstruction,
    v844::ActorFlags::DoorOpener,
    v844::ActorFlags::IsIllagerCaptain,
    v844::ActorFlags::Stunned,
    v844::ActorFlags::Roaring,
    v844::ActorFlags::DelayedAttack,
    v844::ActorFlags::IsAvoidingMobs,
    v844::ActorFlags::IsAvoidingBlock,
    v844::ActorFlags::FacingTargetToRangeAttack,
    v844::ActorFlags::HiddenWhenInvisible,
    v844::ActorFlags::IsInUi,
    v844::ActorFlags::Stalking,
    v844::ActorFlags::Emoting,
    v844::ActorFlags::Celebrating,
    v844::ActorFlags::Admiring,
    v844::ActorFlags::CelebratingSpecial,
    v844::ActorFlags::OutOfControl,
    v844::ActorFlags::RamAttack,
    v844::ActorFlags::PlayingDead,
    v844::ActorFlags::InAscendableBlock,
    v844::ActorFlags::OverDescendableBlock,
    v844::ActorFlags::Croaking,
    v844::ActorFlags::EatMob,
    v844::ActorFlags::JumpGoalJump,
    v844::ActorFlags::Emerging,
    v844::ActorFlags::Sniffing,
    v844::ActorFlags::Digging,
    v844::ActorFlags::SonicBoom,
    v844::ActorFlags::HasDashCooldown,
    v844::ActorFlags::PushTowardsClosestSpace,
    v844::ActorFlags::Deprecated1,
    v844::ActorFlags::Deprecated2,
    v844::ActorFlags::Deprecated3,
    v844::ActorFlags::Searching,
    v844::ActorFlags::Crawling,
    v844::ActorFlags::TimerFlag1,
    v844::ActorFlags::TimerFlag2,
    v844::ActorFlags::TimerFlag3,
    v844::ActorFlags::BodyRotationBlocked,
    v844::ActorFlags::RendersWhenInvisible,
    v844::ActorFlags::RotationAxisAligned,
    v844::ActorFlags::Collidable,
    v844::ActorFlags::WasdFreeCameraControlled,
    v844::ActorFlags::DoesServerAuthOnlyDismount,
    v844::ActorFlags::BodyRotationAlwaysFollowsHead,
    v844::ActorFlags::CanUseVerticalMovementAction,
    v844::ActorFlags::Count,
}};

template <>
inline constexpr std::array<std::string_view, 127> names_v<v844::ActorFlags>{{
    "onfire",
    "sneaking",
    "riding",
    "sprinting",
    "usingitem",
    "invisible",
    "tempted",
    "inlove",
    "saddled",
    "powered",
    "ignited",
    "baby",
    "converting",
    "critical",
    "canshowname",
    "alwaysshowname",
    "noai",
    "silent",
    "wallclimbing",
    "canclimb",
    "canswim",
    "canfly",
    "canwalk",
    "resting",
    "sitting",
    "angry",
    "interested",
    "charged",
    "tamed",
    "orphaned",
    "leashed",
    "sheared",
    "gliding",
    "elder",
    "moving",
    "breathing",
    "chested",
    "stackable",
    "showbottom",
    "standing",
    "shaking",
    "idling",
    "casting",
    "charging",
    "wasdcontrolled",
    "canpowerjump",
    "candash",
    "lingering",
    "hascollision",
    "hasgravity",
    "fireimmune",
    "dancing",
    "enchanted",
    "returntrident",
    "containerisprivate",
    "istransforming",
    "damagenearbymobs",
    "swimming",
    "bribed",
    "ispregnant",
    "layingegg",
    "passengercanpick",
    "transitionsitting",
    "eating",
    "layingdown",
    "sneezing",
    "trusting",
    "rolling",
    "scared",
    "inscaffolding",
    "overscaffolding",
    "descendthroughblock",
    "blocking",
    "transitionblocking",
    "blockedusingshield",
    "blockedusingdamagedshield",
    "sleeping",
    "wantstowake",
    "tradeinterest",
    "doorbreaker",
    "breakingobstruction",
    "dooropener",
    "isillagercaptain",
    "stunned",
    "roaring",
    "delayedattack",
    "isavoidingmobs",
    "isavoidingblock",
    "facingtargettorangeattack",
    "hiddenwheninvisible",
    "isinui",
    "stalking",
    "emoting",
    "celebrating",
    "admiring",
    "celebratingspecial",
    "outofcontrol",
    "ramattack",
    "playingdead",
    "inascendableblock",
    "overdescendableblock",
    "croaking",
    "eatmob",
    "jumpgoaljump",
    "emerging",
    "sniffing",
    "digging",
    "sonicboom",
    "hasdashcooldown",
    "pushtowardsclosestspace",
    "deprecated1",
    "deprecated2",
    "deprecated3",
    "searching",
    "crawling",
    "timerflag1",
    "timerflag2",
    "timerflag3",
    "bodyrotationblocked",
    "renderswheninvisible",
    "rotationaxisaligned",
    "collidable",
    "wasdfreecameracontrolled",
    "doesserverauthonlydismount",
    "bodyrotationalwaysfollowshead",
    "canuseverticalmovementaction",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<v844::ActorFlags>{"ActorFlags"};

template <>
inline constexpr std::array<v898::ActorFlags, 128> values_v<v898::ActorFlags>{{
    v898::ActorFlags::Onfire,
    v898::ActorFlags::Sneaking,
    v898::ActorFlags::Riding,
    v898::ActorFlags::Sprinting,
    v898::ActorFlags::Usingitem,
    v898::ActorFlags::Invisible,
    v898::ActorFlags::Tempted,
    v898::ActorFlags::Inlove,
    v898::ActorFlags::Saddled,
    v898::ActorFlags::Powered,
    v898::ActorFlags::Ignited,
    v898::ActorFlags::Baby,
    v898::ActorFlags::Converting,
    v898::ActorFlags::Critical,
    v898::ActorFlags::CanShowName,
    v898::ActorFlags::AlwaysShowName,
    v898::ActorFlags::Noai,
    v898::ActorFlags::Silent,
    v898::ActorFlags::Wallclimbing,
    v898::ActorFlags::Canclimb,
    v898::ActorFlags::Canswim,
    v898::ActorFlags::Canfly,
    v898::ActorFlags::Canwalk,
    v898::ActorFlags::Resting,
    v898::ActorFlags::Sitting,
    v898::ActorFlags::Angry,
    v898::ActorFlags::Interested,
    v898::ActorFlags::Charged,
    v898::ActorFlags::Tamed,
    v898::ActorFlags::Orphaned,
    v898::ActorFlags::Leashed,
    v898::ActorFlags::Sheared,
    v898::ActorFlags::Gliding,
    v898::ActorFlags::Elder,
    v898::ActorFlags::Moving,
    v898::ActorFlags::Breathing,
    v898::ActorFlags::Chested,
    v898::ActorFlags::Stackable,
    v898::ActorFlags::ShowBottom,
    v898::ActorFlags::Standing,
    v898::ActorFlags::Shaking,
    v898::ActorFlags::Idling,
    v898::ActorFlags::Casting,
    v898::ActorFlags::Charging,
    v898::ActorFlags::WasdControlled,
    v898::ActorFlags::CanPowerJump,
    v898::ActorFlags::CanDash,
    v898::ActorFlags::Lingering,
    v898::ActorFlags::HasCollision,
    v898::ActorFlags::HasGravity,
    v898::ActorFlags::FireImmune,
    v898::ActorFlags::Dancing,
    v898::ActorFlags::Enchanted,
    v898::ActorFlags::Returntrident,
    v898::ActorFlags::ContainerIsPrivate,
    v898::ActorFlags::IsTransforming,
    v898::ActorFlags::Damagenearbymobs,
    v898::ActorFlags::Swimming,
    v898::ActorFlags::Bribed,
    v898::ActorFlags::IsPregnant,
    v898::ActorFlags::LayingEgg,
    v898::ActorFlags::PassengerCanPick,
    v898::ActorFlags::TransitionSitting,
    v898::ActorFlags::Eating,
    v898::ActorFlags::LayingDown,
    v898::ActorFlags::Sneezing,
    v898::ActorFlags::Trusting,
    v898::ActorFlags::Rolling,
    v898::ActorFlags::Scared,
    v898::ActorFlags::InScaffolding,
    v898::ActorFlags::OverScaffolding,
    v898::ActorFlags::DescendThroughBlock,
    v898::ActorFlags::Blocking,
    v898::ActorFlags::TransitionBlocking,
    v898::ActorFlags::BlockedUsingShield,
    v898::ActorFlags::BlockedUsingDamagedShield,
    v898::ActorFlags::Sleeping,
    v898::ActorFlags::WantsToWake,
    v898::ActorFlags::TradeInterest,
    v898::ActorFlags::DoorBreaker,
    v898::ActorFlags::BreakingObstruction,
    v898::ActorFlags::DoorOpener,
    v898::ActorFlags::IsIllagerCaptain,
    v898::ActorFlags::Stunned,
    v898::ActorFlags::Roaring,
    v898::ActorFlags::DelayedAttack,
    v898::ActorFlags::IsAvoidingMobs,
    v898::ActorFlags::IsAvoidingBlock,
    v898::ActorFlags::FacingTargetToRangeAttack,
    v898::ActorFlags::HiddenWhenInvisible,
    v898::ActorFlags::IsInUi,
    v898::ActorFlags::Stalking,
    v898::ActorFlags::Emoting,
    v898::ActorFlags::Celebrating,
    v898::ActorFlags::Admiring,
    v898::ActorFlags::CelebratingSpecial,
    v898::ActorFlags::OutOfControl,
    v898::ActorFlags::RamAttack,
    v898::ActorFlags::PlayingDead,
    v898::ActorFlags::InAscendableBlock,
    v898::ActorFlags::OverDescendableBlock,
    v898::ActorFlags::Croaking,
    v898::ActorFlags::EatMob,
    v898::ActorFlags::JumpGoalJump,
    v898::ActorFlags::Emerging,
    v898::ActorFlags::Sniffing,
    v898::ActorFlags::Digging,
    v898::ActorFlags::SonicBoom,
    v898::ActorFlags::HasDashCooldown,
    v898::ActorFlags::PushTowardsClosestSpace,
    v898::ActorFlags::Deprecated1,
    v898::ActorFlags::Deprecated2,
    v898::ActorFlags::Deprecated3,
    v898::ActorFlags::Searching,
    v898::ActorFlags::Crawling,
    v898::ActorFlags::TimerFlag1,
    v898::ActorFlags::TimerFlag2,
    v898::ActorFlags::TimerFlag3,
    v898::ActorFlags::BodyRotationBlocked,
    v898::ActorFlags::RendersWhenInvisible,
    v898::ActorFlags::RotationAxisAligned,
    v898::ActorFlags::Collidable,
    v898::ActorFlags::WasdFreeCameraControlled,
    v898::ActorFlags::DoesServerAuthOnlyDismount,
    v898::ActorFlags::BodyRotationAlwaysFollowsHead,
    v898::ActorFlags::CanUseVerticalMovementAction,
    v898::ActorFlags::RotationLockedToVehicle,
    v898::ActorFlags::Count,
}};

template <>
inline constexpr std::array<std::string_view, 128> names_v<v898::ActorFlags>{{
    "onfire",
    "sneaking",
    "riding",
    "sprinting",
    "usingitem",
    "invisible",
    "tempted",
    "inlove",
    "saddled",
    "powered",
    "ignited",
    "baby",
    "converting",
    "critical",
    "canshowname",
    "alwaysshowname",
    "noai",
    "silent",
    "wallclimbing",
    "canclimb",
    "canswim",
    "canfly",
    "canwalk",
    "resting",
    "sitting",
    "angry",
    "interested",
    "charged",
    "tamed",
    "orphaned",
    "leashed",
    "sheared",
    "gliding",
    "elder",
    "moving",
    "breathing",
    "chested",
    "stackable",
    "showbottom",
    "standing",
    "shaking",
    "idling",
    "casting",
    "charging",
    "wasdcontrolled",
    "canpowerjump",
    "candash",
    "lingering",
    "hascollision",
    "hasgravity",
    "fireimmune",
    "dancing",
    "enchanted",
    "returntrident",
    "containerisprivate",
    "istransforming",
    "damagenearbymobs",
    "swimming",
    "bribed",
    "ispregnant",
    "layingegg",
    "passengercanpick",
    "transitionsitting",
    "eating",
    "layingdown",
    "sneezing",
    "trusting",
    "rolling",
    "scared",
    "inscaffolding",
    "overscaffolding",
    "descendthroughblock",
    "blocking",
    "transitionblocking",
    "blockedusingshield",
    "blockedusingdamagedshield",
    "sleeping",
    "wantstowake",
    "tradeinterest",
    "doorbreaker",
    "breakingobstruction",
    "dooropener",
    "isillagercaptain",
    "stunned",
    "roaring",
    "delayedattack",
    "isavoidingmobs",
    "isavoidingblock",
    "facingtargettorangeattack",
    "hiddenwheninvisible",
    "isinui",
    "stalking",
    "emoting",
    "celebrating",
    "admiring",
    "celebratingspecial",
    "outofcontrol",
    "ramattack",
    "playingdead",
    "inascendableblock",
    "overdescendableblock",
    "croaking",
    "eatmob",
    "jumpgoaljump",
    "emerging",
    "sniffing",
    "digging",
    "sonicboom",
    "hasdashcooldown",
    "pushtowardsclosestspace",
    "deprecated1",
    "deprecated2",
    "deprecated3",
    "searching",
    "crawling",
    "timerflag1",
    "timerflag2",
    "timerflag3",
    "bodyrotationblocked",
    "renderswheninvisible",
    "rotationaxisaligned",
    "collidable",
    "wasdfreecameracontrolled",
    "doesserverauthonlydismount",
    "bodyrotationalwaysfollowshead",
    "canuseverticalmovementaction",
    "rotationlockedtovehicle",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<v898::ActorFlags>{"ActorFlags"};

template <>
inline constexpr std::array<v975::ActorFlags, 131> values_v<v975::ActorFlags>{{
    v975::ActorFlags::Onfire,
    v975::ActorFlags::Sneaking,
    v975::ActorFlags::Riding,
    v975::ActorFlags::Sprinting,
    v975::ActorFlags::Usingitem,
    v975::ActorFlags::Invisible,
    v975::ActorFlags::Tempted,
    v975::ActorFlags::Inlove,
    v975::ActorFlags::Saddled,
    v975::ActorFlags::Powered,
    v975::ActorFlags::Ignited,
    v975::ActorFlags::Baby,
    v975::ActorFlags::Converting,
    v975::ActorFlags::Critical,
    v975::ActorFlags::CanShowName,
    v975::ActorFlags::AlwaysShowName,
    v975::ActorFlags::Noai,
    v975::ActorFlags::Silent,
    v975::ActorFlags::Wallclimbing,
    v975::ActorFlags::Canclimb,
    v975::ActorFlags::Canswim,
    v975::ActorFlags::Canfly,
    v975::ActorFlags::Canwalk,
    v975::ActorFlags::Resting,
    v975::ActorFlags::Sitting,
    v975::ActorFlags::Angry,
    v975::ActorFlags::Interested,
    v975::ActorFlags::Charged,
    v975::ActorFlags::Tamed,
    v975::ActorFlags::Orphaned,
    v975::ActorFlags::Leashed,
    v975::ActorFlags::Sheared,
    v975::ActorFlags::Gliding,
    v975::ActorFlags::Elder,
    v975::ActorFlags::Moving,
    v975::ActorFlags::Breathing,
    v975::ActorFlags::Chested,
    v975::ActorFlags::Stackable,
    v975::ActorFlags::ShowBottom,
    v975::ActorFlags::Standing,
    v975::ActorFlags::Shaking,
    v975::ActorFlags::Idling,
    v975::ActorFlags::Casting,
    v975::ActorFlags::Charging,
    v975::ActorFlags::WasdControlled,
    v975::ActorFlags::CanPowerJump,
    v975::ActorFlags::CanDash,
    v975::ActorFlags::Lingering,
    v975::ActorFlags::HasCollision,
    v975::ActorFlags::HasGravity,
    v975::ActorFlags::FireImmune,
    v975::ActorFlags::Dancing,
    v975::ActorFlags::Enchanted,
    v975::ActorFlags::Returntrident,
    v975::ActorFlags::ContainerIsPrivate,
    v975::ActorFlags::IsTransforming,
    v975::ActorFlags::Damagenearbymobs,
    v975::ActorFlags::Swimming,
    v975::ActorFlags::Bribed,
    v975::ActorFlags::IsPregnant,
    v975::ActorFlags::LayingEgg,
    v975::ActorFlags::PassengerCanPick,
    v975::ActorFlags::TransitionSitting,
    v975::ActorFlags::Eating,
    v975::ActorFlags::LayingDown,
    v975::ActorFlags::Sneezing,
    v975::ActorFlags::Trusting,
    v975::ActorFlags::Rolling,
    v975::ActorFlags::Scared,
    v975::ActorFlags::InScaffolding,
    v975::ActorFlags::OverScaffolding,
    v975::ActorFlags::DescendThroughBlock,
    v975::ActorFlags::Blocking,
    v975::ActorFlags::TransitionBlocking,
    v975::ActorFlags::BlockedUsingShield,
    v975::ActorFlags::BlockedUsingDamagedShield,
    v975::ActorFlags::Sleeping,
    v975::ActorFlags::WantsToWake,
    v975::ActorFlags::TradeInterest,
    v975::ActorFlags::DoorBreaker,
    v975::ActorFlags::BreakingObstruction,
    v975::ActorFlags::DoorOpener,
    v975::ActorFlags::IsIllagerCaptain,
    v975::ActorFlags::Stunned,
    v975::ActorFlags::Roaring,
    v975::ActorFlags::DelayedAttack,
    v975::ActorFlags::IsAvoidingMobs,
    v975::ActorFlags::IsAvoidingBlock,
    v975::ActorFlags::FacingTargetToRangeAttack,
    v975::ActorFlags::HiddenWhenInvisible,
    v975::ActorFlags::IsInUi,
    v975::ActorFlags::Stalking,
    v975::ActorFlags::Emoting,
    v975::ActorFlags::Celebrating,
    v975::ActorFlags::Admiring,
    v975::ActorFlags::CelebratingSpecial,
    v975::ActorFlags::OutOfControl,
    v975::ActorFlags::RamAttack,
    v975::ActorFlags::PlayingDead,
    v975::ActorFlags::InAscendableBlock,
    v975::ActorFlags::OverDescendableBlock,
    v975::ActorFlags::Croaking,
    v975::ActorFlags::EatMob,
    v975::ActorFlags::JumpGoalJump,
    v975::ActorFlags::Emerging,
    v975::ActorFlags::Sniffing,
    v975::ActorFlags::Digging,
    v975::ActorFlags::SonicBoom,
    v975::ActorFlags::HasDashCooldown,
    v975::ActorFlags::PushTowardsClosestSpace,
    v975::ActorFlags::Deprecated1,
    v975::ActorFlags::Deprecated2,
    v975::ActorFlags::Deprecated3,
    v975::ActorFlags::Searching,
    v975::ActorFlags::Crawling,
    v975::ActorFlags::TimerFlag1,
    v975::ActorFlags::TimerFlag2,
    v975::ActorFlags::TimerFlag3,
    v975::ActorFlags::BodyRotationBlocked,
    v975::ActorFlags::RendersWhenInvisible,
    v975::ActorFlags::RotationAxisAligned,
    v975::ActorFlags::Collidable,
    v975::ActorFlags::WasdFreeCameraControlled,
    v975::ActorFlags::DoesServerAuthOnlyDismount,
    v975::ActorFlags::BodyRotationAlwaysFollowsHead,
    v975::ActorFlags::CanUseVerticalMovementAction,
    v975::ActorFlags::RotationLockedToVehicle,
    v975::ActorFlags::UsesLegacyFriction,
    v975::ActorFlags::UsesUniformAirDrag,
    v975::ActorFlags::NameplateDepthTested,
    v975::ActorFlags::Count,
}};

template <>
inline constexpr std::array<std::string_view, 131> names_v<v975::ActorFlags>{{
    "onfire",
    "sneaking",
    "riding",
    "sprinting",
    "usingitem",
    "invisible",
    "tempted",
    "inlove",
    "saddled",
    "powered",
    "ignited",
    "baby",
    "converting",
    "critical",
    "canshowname",
    "alwaysshowname",
    "noai",
    "silent",
    "wallclimbing",
    "canclimb",
    "canswim",
    "canfly",
    "canwalk",
    "resting",
    "sitting",
    "angry",
    "interested",
    "charged",
    "tamed",
    "orphaned",
    "leashed",
    "sheared",
    "gliding",
    "elder",
    "moving",
    "breathing",
    "chested",
    "stackable",
    "showbottom",
    "standing",
    "shaking",
    "idling",
    "casting",
    "charging",
    "wasdcontrolled",
    "canpowerjump",
    "candash",
    "lingering",
    "hascollision",
    "hasgravity",
    "fireimmune",
    "dancing",
    "enchanted",
    "returntrident",
    "containerisprivate",
    "istransforming",
    "damagenearbymobs",
    "swimming",
    "bribed",
    "ispregnant",
    "layingegg",
    "passengercanpick",
    "transitionsitting",
    "eating",
    "layingdown",
    "sneezing",
    "trusting",
    "rolling",
    "scared",
    "inscaffolding",
    "overscaffolding",
    "descendthroughblock",
    "blocking",
    "transitionblocking",
    "blockedusingshield",
    "blockedusingdamagedshield",
    "sleeping",
    "wantstowake",
    "tradeinterest",
    "doorbreaker",
    "breakingobstruction",
    "dooropener",
    "isillagercaptain",
    "stunned",
    "roaring",
    "delayedattack",
    "isavoidingmobs",
    "isavoidingblock",
    "facingtargettorangeattack",
    "hiddenwheninvisible",
    "isinui",
    "stalking",
    "emoting",
    "celebrating",
    "admiring",
    "celebratingspecial",
    "outofcontrol",
    "ramattack",
    "playingdead",
    "inascendableblock",
    "overdescendableblock",
    "croaking",
    "eatmob",
    "jumpgoaljump",
    "emerging",
    "sniffing",
    "digging",
    "sonicboom",
    "hasdashcooldown",
    "pushtowardsclosestspace",
    "deprecated1",
    "deprecated2",
    "deprecated3",
    "searching",
    "crawling",
    "timerflag1",
    "timerflag2",
    "timerflag3",
    "bodyrotationblocked",
    "renderswheninvisible",
    "rotationaxisaligned",
    "collidable",
    "wasdfreecameracontrolled",
    "doesserverauthonlydismount",
    "bodyrotationalwaysfollowshead",
    "canuseverticalmovementaction",
    "rotationlockedtovehicle",
    "useslegacyfriction",
    "usesuniformairdrag",
    "nameplatedepthtested",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<v975::ActorFlags>{"ActorFlags"};

template <>
inline constexpr std::array<v2168::ActorFlags, 132> values_v<v2168::ActorFlags>{{
    v2168::ActorFlags::Onfire,
    v2168::ActorFlags::Sneaking,
    v2168::ActorFlags::Riding,
    v2168::ActorFlags::Sprinting,
    v2168::ActorFlags::Usingitem,
    v2168::ActorFlags::Invisible,
    v2168::ActorFlags::Tempted,
    v2168::ActorFlags::Inlove,
    v2168::ActorFlags::Saddled,
    v2168::ActorFlags::Powered,
    v2168::ActorFlags::Ignited,
    v2168::ActorFlags::Baby,
    v2168::ActorFlags::Converting,
    v2168::ActorFlags::Critical,
    v2168::ActorFlags::CanShowName,
    v2168::ActorFlags::AlwaysShowName,
    v2168::ActorFlags::Noai,
    v2168::ActorFlags::Silent,
    v2168::ActorFlags::Wallclimbing,
    v2168::ActorFlags::Canclimb,
    v2168::ActorFlags::Canswim,
    v2168::ActorFlags::Canfly,
    v2168::ActorFlags::Canwalk,
    v2168::ActorFlags::Resting,
    v2168::ActorFlags::Sitting,
    v2168::ActorFlags::Angry,
    v2168::ActorFlags::Interested,
    v2168::ActorFlags::Charged,
    v2168::ActorFlags::Tamed,
    v2168::ActorFlags::Orphaned,
    v2168::ActorFlags::Leashed,
    v2168::ActorFlags::Sheared,
    v2168::ActorFlags::Gliding,
    v2168::ActorFlags::Elder,
    v2168::ActorFlags::Moving,
    v2168::ActorFlags::Breathing,
    v2168::ActorFlags::Chested,
    v2168::ActorFlags::Stackable,
    v2168::ActorFlags::ShowBottom,
    v2168::ActorFlags::Standing,
    v2168::ActorFlags::Shaking,
    v2168::ActorFlags::Idling,
    v2168::ActorFlags::Casting,
    v2168::ActorFlags::Charging,
    v2168::ActorFlags::WasdControlled,
    v2168::ActorFlags::CanPowerJump,
    v2168::ActorFlags::CanDash,
    v2168::ActorFlags::Lingering,
    v2168::ActorFlags::HasCollision,
    v2168::ActorFlags::HasGravity,
    v2168::ActorFlags::FireImmune,
    v2168::ActorFlags::Dancing,
    v2168::ActorFlags::Enchanted,
    v2168::ActorFlags::Returntrident,
    v2168::ActorFlags::ContainerIsPrivate,
    v2168::ActorFlags::IsTransforming,
    v2168::ActorFlags::Damagenearbymobs,
    v2168::ActorFlags::Swimming,
    v2168::ActorFlags::Bribed,
    v2168::ActorFlags::IsPregnant,
    v2168::ActorFlags::LayingEgg,
    v2168::ActorFlags::PassengerCanPick,
    v2168::ActorFlags::TransitionSitting,
    v2168::ActorFlags::Eating,
    v2168::ActorFlags::LayingDown,
    v2168::ActorFlags::Sneezing,
    v2168::ActorFlags::Trusting,
    v2168::ActorFlags::Rolling,
    v2168::ActorFlags::Scared,
    v2168::ActorFlags::InScaffolding,
    v2168::ActorFlags::OverScaffolding,
    v2168::ActorFlags::DescendThroughBlock,
    v2168::ActorFlags::Blocking,
    v2168::ActorFlags::TransitionBlocking,
    v2168::ActorFlags::BlockedUsingShield,
    v2168::ActorFlags::BlockedUsingDamagedShield,
    v2168::ActorFlags::Sleeping,
    v2168::ActorFlags::WantsToWake,
    v2168::ActorFlags::TradeInterest,
    v2168::ActorFlags::DoorBreaker,
    v2168::ActorFlags::BreakingObstruction,
    v2168::ActorFlags::DoorOpener,
    v2168::ActorFlags::IsIllagerCaptain,
    v2168::ActorFlags::Stunned,
    v2168::ActorFlags::Roaring,
    v2168::ActorFlags::DelayedAttack,
    v2168::ActorFlags::IsAvoidingMobs,
    v2168::ActorFlags::IsAvoidingBlock,
    v2168::ActorFlags::FacingTargetToRangeAttack,
    v2168::ActorFlags::HiddenWhenInvisible,
    v2168::ActorFlags::IsInUi,
    v2168::ActorFlags::Stalking,
    v2168::ActorFlags::Emoting,
    v2168::ActorFlags::Celebrating,
    v2168::ActorFlags::Admiring,
    v2168::ActorFlags::CelebratingSpecial,
    v2168::ActorFlags::OutOfControl,
    v2168::ActorFlags::RamAttack,
    v2168::ActorFlags::PlayingDead,
    v2168::ActorFlags::InAscendableBlock,
    v2168::ActorFlags::OverDescendableBlock,
    v2168::ActorFlags::Croaking,
    v2168::ActorFlags::EatMob,
    v2168::ActorFlags::JumpGoalJump,
    v2168::ActorFlags::Emerging,
    v2168::ActorFlags::Sniffing,
    v2168::ActorFlags::Digging,
    v2168::ActorFlags::SonicBoom,
    v2168::ActorFlags::HasDashCooldown,
    v2168::ActorFlags::PushTowardsClosestSpace,
    v2168::ActorFlags::Deprecated1,
    v2168::ActorFlags::Deprecated2,
    v2168::ActorFlags::Deprecated3,
    v2168::ActorFlags::Searching,
    v2168::ActorFlags::Crawling,
    v2168::ActorFlags::TimerFlag1,
    v2168::ActorFlags::TimerFlag2,
    v2168::ActorFlags::TimerFlag3,
    v2168::ActorFlags::BodyRotationBlocked,
    v2168::ActorFlags::RendersWhenInvisible,
    v2168::ActorFlags::RotationAxisAligned,
    v2168::ActorFlags::Collidable,
    v2168::ActorFlags::WasdFreeCameraControlled,
    v2168::ActorFlags::DoesServerAuthOnlyDismount,
    v2168::ActorFlags::BodyRotationAlwaysFollowsHead,
    v2168::ActorFlags::CanUseVerticalMovementAction,
    v2168::ActorFlags::RotationLockedToVehicle,
    v2168::ActorFlags::UsesLegacyFriction,
    v2168::ActorFlags::UsesUniformAirDrag,
    v2168::ActorFlags::NameplateDepthTested,
    v2168::ActorFlags::NotPickableFromInside,
    v2168::ActorFlags::Count,
}};

template <>
inline constexpr std::array<std::string_view, 132> names_v<v2168::ActorFlags>{{
    "onfire",
    "sneaking",
    "riding",
    "sprinting",
    "usingitem",
    "invisible",
    "tempted",
    "inlove",
    "saddled",
    "powered",
    "ignited",
    "baby",
    "converting",
    "critical",
    "canshowname",
    "alwaysshowname",
    "noai",
    "silent",
    "wallclimbing",
    "canclimb",
    "canswim",
    "canfly",
    "canwalk",
    "resting",
    "sitting",
    "angry",
    "interested",
    "charged",
    "tamed",
    "orphaned",
    "leashed",
    "sheared",
    "gliding",
    "elder",
    "moving",
    "breathing",
    "chested",
    "stackable",
    "showbottom",
    "standing",
    "shaking",
    "idling",
    "casting",
    "charging",
    "wasdcontrolled",
    "canpowerjump",
    "candash",
    "lingering",
    "hascollision",
    "hasgravity",
    "fireimmune",
    "dancing",
    "enchanted",
    "returntrident",
    "containerisprivate",
    "istransforming",
    "damagenearbymobs",
    "swimming",
    "bribed",
    "ispregnant",
    "layingegg",
    "passengercanpick",
    "transitionsitting",
    "eating",
    "layingdown",
    "sneezing",
    "trusting",
    "rolling",
    "scared",
    "inscaffolding",
    "overscaffolding",
    "descendthroughblock",
    "blocking",
    "transitionblocking",
    "blockedusingshield",
    "blockedusingdamagedshield",
    "sleeping",
    "wantstowake",
    "tradeinterest",
    "doorbreaker",
    "breakingobstruction",
    "dooropener",
    "isillagercaptain",
    "stunned",
    "roaring",
    "delayedattack",
    "isavoidingmobs",
    "isavoidingblock",
    "facingtargettorangeattack",
    "hiddenwheninvisible",
    "isinui",
    "stalking",
    "emoting",
    "celebrating",
    "admiring",
    "celebratingspecial",
    "outofcontrol",
    "ramattack",
    "playingdead",
    "inascendableblock",
    "overdescendableblock",
    "croaking",
    "eatmob",
    "jumpgoaljump",
    "emerging",
    "sniffing",
    "digging",
    "sonicboom",
    "hasdashcooldown",
    "pushtowardsclosestspace",
    "deprecated1",
    "deprecated2",
    "deprecated3",
    "searching",
    "crawling",
    "timerflag1",
    "timerflag2",
    "timerflag3",
    "bodyrotationblocked",
    "renderswheninvisible",
    "rotationaxisaligned",
    "collidable",
    "wasdfreecameracontrolled",
    "doesserverauthonlydismount",
    "bodyrotationalwaysfollowshead",
    "canuseverticalmovementaction",
    "rotationlockedtovehicle",
    "useslegacyfriction",
    "usesuniformairdrag",
    "nameplatedepthtested",
    "notpickablefrominside",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<v2168::ActorFlags>{"ActorFlags"};

template <>
inline constexpr std::array<base::ActorDataIDs, 133> values_v<base::ActorDataIDs>{{
    base::ActorDataIDs::Reserved0,
    base::ActorDataIDs::StructuralIntegrity,
    base::ActorDataIDs::Variant,
    base::ActorDataIDs::ColorIndex,
    base::ActorDataIDs::Name,
    base::ActorDataIDs::Owner,
    base::ActorDataIDs::Target,
    base::ActorDataIDs::AirSupply,
    base::ActorDataIDs::EffectColor,
    base::ActorDataIDs::Reserved009,
    base::ActorDataIDs::Reserved010,
    base::ActorDataIDs::Hurt,
    base::ActorDataIDs::HurtDir,
    base::ActorDataIDs::RowTimeLeft,
    base::ActorDataIDs::RowTimeRight,
    base::ActorDataIDs::Value,
    base::ActorDataIDs::DisplayTileRuntimeId,
    base::ActorDataIDs::DisplayOffset,
    base::ActorDataIDs::CustomDisplay,
    base::ActorDataIDs::Swell,
    base::ActorDataIDs::OldSwell,
    base::ActorDataIDs::SwellDir,
    base::ActorDataIDs::ChargeAmount,
    base::ActorDataIDs::DeprecatedCarryBlockRuntimeId,
    base::ActorDataIDs::ClientEvent,
    base::ActorDataIDs::UsingItem,
    base::ActorDataIDs::PlayerFlags,
    base::ActorDataIDs::PlayerIndex,
    base::ActorDataIDs::BedPosition,
    base::ActorDataIDs::XPower,
    base::ActorDataIDs::YPower,
    base::ActorDataIDs::ZPower,
    base::ActorDataIDs::AuxPower,
    base::ActorDataIDs::Fishx,
    base::ActorDataIDs::Fishz,
    base::ActorDataIDs::Fishangle,
    base::ActorDataIDs::AuxValueData,
    base::ActorDataIDs::LeashHolder,
    base::ActorDataIDs::Reserved038,
    base::ActorDataIDs::HasNpc,
    base::ActorDataIDs::NpcData,
    base::ActorDataIDs::Actions,
    base::ActorDataIDs::AirSupplyMax,
    base::ActorDataIDs::MarkVariant,
    base::ActorDataIDs::ContainerType,
    base::ActorDataIDs::ContainerSize,
    base::ActorDataIDs::ContainerStrengthModifier,
    base::ActorDataIDs::BlockTarget,
    base::ActorDataIDs::Inv,
    base::ActorDataIDs::TargetA,
    base::ActorDataIDs::TargetB,
    base::ActorDataIDs::TargetC,
    base::ActorDataIDs::AerialAttack,
    base::ActorDataIDs::Reserved053,
    base::ActorDataIDs::Reserved054,
    base::ActorDataIDs::FuseTime,
    base::ActorDataIDs::Reserved056,
    base::ActorDataIDs::SeatLockPassengerRotation,
    base::ActorDataIDs::SeatLockPassengerRotationDegrees,
    base::ActorDataIDs::SeatRotationOffset,
    base::ActorDataIDs::SeatRotationOffsetDegrees,
    base::ActorDataIDs::DataRadius,
    base::ActorDataIDs::DataWaiting,
    base::ActorDataIDs::DataParticle,
    base::ActorDataIDs::PeekId,
    base::ActorDataIDs::AttachFace,
    base::ActorDataIDs::Attached,
    base::ActorDataIDs::AttachPos,
    base::ActorDataIDs::TradeTarget,
    base::ActorDataIDs::Career,
    base::ActorDataIDs::HasCommandBlock,
    base::ActorDataIDs::CommandName,
    base::ActorDataIDs::LastCommandOutput,
    base::ActorDataIDs::TrackCommandOutput,
    base::ActorDataIDs::Reserved074,
    base::ActorDataIDs::Strength,
    base::ActorDataIDs::StrengthMax,
    base::ActorDataIDs::DataSpellCastingColor,
    base::ActorDataIDs::DataLifetimeTicks,
    base::ActorDataIDs::PoseIndex,
    base::ActorDataIDs::DataTickOffset,
    base::ActorDataIDs::NametagAlwaysShow,
    base::ActorDataIDs::Color2Index,
    base::ActorDataIDs::NameAuthor,
    base::ActorDataIDs::Score,
    base::ActorDataIDs::BalloonAnchor,
    base::ActorDataIDs::PuffedState,
    base::ActorDataIDs::BubbleTime,
    base::ActorDataIDs::Agent,
    base::ActorDataIDs::SittingAmount,
    base::ActorDataIDs::SittingAmountPrevious,
    base::ActorDataIDs::EatingCounter,
    base::ActorDataIDs::Reserved092,
    base::ActorDataIDs::LayingAmount,
    base::ActorDataIDs::LayingAmountPrevious,
    base::ActorDataIDs::DataDuration,
    base::ActorDataIDs::DataSpawnTimeDeprecated,
    base::ActorDataIDs::DataChangeRate,
    base::ActorDataIDs::DataChangeOnPickup,
    base::ActorDataIDs::DataPickupCount,
    base::ActorDataIDs::InteractText,
    base::ActorDataIDs::TradeTier,
    base::ActorDataIDs::MaxTradeTier,
    base::ActorDataIDs::TradeExperience,
    base::ActorDataIDs::SkinId,
    base::ActorDataIDs::SpawningFrames,
    base::ActorDataIDs::CommandBlockTickDelay,
    base::ActorDataIDs::CommandBlockExecuteOnFirstTick,
    base::ActorDataIDs::AmbientSoundInterval,
    base::ActorDataIDs::AmbientSoundIntervalRange,
    base::ActorDataIDs::AmbientSoundEventName,
    base::ActorDataIDs::FallDamageMultiplier,
    base::ActorDataIDs::NameRawText,
    base::ActorDataIDs::CanRideTarget,
    base::ActorDataIDs::LowTierCuredTradeDiscount,
    base::ActorDataIDs::HighTierCuredTradeDiscount,
    base::ActorDataIDs::NearbyCuredTradeDiscount,
    base::ActorDataIDs::NearbyCuredDiscountTimeStamp,
    base::ActorDataIDs::Hitbox,
    base::ActorDataIDs::IsBuoyant,
    base::ActorDataIDs::FreezingEffectStrength,
    base::ActorDataIDs::BuoyancyData,
    base::ActorDataIDs::GoatHornCount,
    base::ActorDataIDs::BaseRuntimeId,
    base::ActorDataIDs::MovementSoundDistanceOffset,
    base::ActorDataIDs::HeartbeatIntervalTicks,
    base::ActorDataIDs::HeartbeatSoundEvent,
    base::ActorDataIDs::PlayerLastDeathPos,
    base::ActorDataIDs::PlayerLastDeathDimension,
    base::ActorDataIDs::PlayerHasDied,
    base::ActorDataIDs::CollisionBox,
    base::ActorDataIDs::VisibleMobEffects,
    base::ActorDataIDs::Count,
}};

template <>
inline constexpr std::array<std::string_view, 133> names_v<base::ActorDataIDs>{{
    "reserved0",
    "structuralintegrity",
    "variant",
    "colorindex",
    "name",
    "owner",
    "target",
    "airsupply",
    "effectcolor",
    "reserved009",
    "reserved010",
    "hurt",
    "hurtdir",
    "rowtimeleft",
    "rowtimeright",
    "value",
    "displaytileruntimeid",
    "displayoffset",
    "customdisplay",
    "swell",
    "oldswell",
    "swelldir",
    "chargeamount",
    "deprecatedcarryblockruntimeid",
    "clientevent",
    "usingitem",
    "playerflags",
    "playerindex",
    "bedposition",
    "xpower",
    "ypower",
    "zpower",
    "auxpower",
    "fishx",
    "fishz",
    "fishangle",
    "auxvaluedata",
    "leashholder",
    "reserved038",
    "hasnpc",
    "npcdata",
    "actions",
    "airsupplymax",
    "markvariant",
    "containertype",
    "containersize",
    "containerstrengthmodifier",
    "blocktarget",
    "inv",
    "targeta",
    "targetb",
    "targetc",
    "aerialattack",
    "reserved053",
    "reserved054",
    "fusetime",
    "reserved056",
    "seatlockpassengerrotation",
    "seatlockpassengerrotationdegrees",
    "seatrotationoffset",
    "seatrotationoffsetdegrees",
    "dataradius",
    "datawaiting",
    "dataparticle",
    "peekid",
    "attachface",
    "attached",
    "attachpos",
    "tradetarget",
    "career",
    "hascommandblock",
    "commandname",
    "lastcommandoutput",
    "trackcommandoutput",
    "reserved074",
    "strength",
    "strengthmax",
    "dataspellcastingcolor",
    "datalifetimeticks",
    "poseindex",
    "datatickoffset",
    "nametagalwaysshow",
    "color2index",
    "nameauthor",
    "score",
    "balloonanchor",
    "puffedstate",
    "bubbletime",
    "agent",
    "sittingamount",
    "sittingamountprevious",
    "eatingcounter",
    "reserved092",
    "layingamount",
    "layingamountprevious",
    "dataduration",
    "dataspawntimedeprecated",
    "datachangerate",
    "datachangeonpickup",
    "datapickupcount",
    "interacttext",
    "tradetier",
    "maxtradetier",
    "tradeexperience",
    "skinid",
    "spawningframes",
    "commandblocktickdelay",
    "commandblockexecuteonfirsttick",
    "ambientsoundinterval",
    "ambientsoundintervalrange",
    "ambientsoundeventname",
    "falldamagemultiplier",
    "namerawtext",
    "canridetarget",
    "lowtiercuredtradediscount",
    "hightiercuredtradediscount",
    "nearbycuredtradediscount",
    "nearbycureddiscounttimestamp",
    "hitbox",
    "isbuoyant",
    "freezingeffectstrength",
    "buoyancydata",
    "goathorncount",
    "baseruntimeid",
    "movementsounddistanceoffset",
    "heartbeatintervalticks",
    "heartbeatsoundevent",
    "playerlastdeathpos",
    "playerlastdeathdimension",
    "playerhasdied",
    "collisionbox",
    "visiblemobeffects",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<base::ActorDataIDs>{"ActorDataIDs"};

template <>
inline constexpr std::array<v776::ActorDataIDs, 135> values_v<v776::ActorDataIDs>{{
    v776::ActorDataIDs::Reserved0,
    v776::ActorDataIDs::StructuralIntegrity,
    v776::ActorDataIDs::Variant,
    v776::ActorDataIDs::ColorIndex,
    v776::ActorDataIDs::Name,
    v776::ActorDataIDs::Owner,
    v776::ActorDataIDs::Target,
    v776::ActorDataIDs::AirSupply,
    v776::ActorDataIDs::EffectColor,
    v776::ActorDataIDs::Reserved009,
    v776::ActorDataIDs::Reserved010,
    v776::ActorDataIDs::Hurt,
    v776::ActorDataIDs::HurtDir,
    v776::ActorDataIDs::RowTimeLeft,
    v776::ActorDataIDs::RowTimeRight,
    v776::ActorDataIDs::Value,
    v776::ActorDataIDs::DisplayTileRuntimeId,
    v776::ActorDataIDs::DisplayOffset,
    v776::ActorDataIDs::CustomDisplay,
    v776::ActorDataIDs::Swell,
    v776::ActorDataIDs::OldSwell,
    v776::ActorDataIDs::SwellDir,
    v776::ActorDataIDs::ChargeAmount,
    v776::ActorDataIDs::DeprecatedCarryBlockRuntimeId,
    v776::ActorDataIDs::ClientEvent,
    v776::ActorDataIDs::UsingItem,
    v776::ActorDataIDs::PlayerFlags,
    v776::ActorDataIDs::PlayerIndex,
    v776::ActorDataIDs::BedPosition,
    v776::ActorDataIDs::XPower,
    v776::ActorDataIDs::YPower,
    v776::ActorDataIDs::ZPower,
    v776::ActorDataIDs::AuxPower,
    v776::ActorDataIDs::Fishx,
    v776::ActorDataIDs::Fishz,
    v776::ActorDataIDs::Fishangle,
    v776::ActorDataIDs::AuxValueData,
    v776::ActorDataIDs::LeashHolder,
    v776::ActorDataIDs::Reserved038,
    v776::ActorDataIDs::HasNpc,
    v776::ActorDataIDs::NpcData,
    v776::ActorDataIDs::Actions,
    v776::ActorDataIDs::AirSupplyMax,
    v776::ActorDataIDs::MarkVariant,
    v776::ActorDataIDs::ContainerType,
    v776::ActorDataIDs::ContainerSize,
    v776::ActorDataIDs::ContainerStrengthModifier,
    v776::ActorDataIDs::BlockTarget,
    v776::ActorDataIDs::Inv,
    v776::ActorDataIDs::TargetA,
    v776::ActorDataIDs::TargetB,
    v776::ActorDataIDs::TargetC,
    v776::ActorDataIDs::AerialAttack,
    v776::ActorDataIDs::Reserved053,
    v776::ActorDataIDs::Reserved054,
    v776::ActorDataIDs::FuseTime,
    v776::ActorDataIDs::Reserved056,
    v776::ActorDataIDs::SeatLockPassengerRotation,
    v776::ActorDataIDs::SeatLockPassengerRotationDegrees,
    v776::ActorDataIDs::SeatRotationOffset,
    v776::ActorDataIDs::SeatRotationOffsetDegrees,
    v776::ActorDataIDs::DataRadius,
    v776::ActorDataIDs::DataWaiting,
    v776::ActorDataIDs::DataParticle,
    v776::ActorDataIDs::PeekId,
    v776::ActorDataIDs::AttachFace,
    v776::ActorDataIDs::Attached,
    v776::ActorDataIDs::AttachPos,
    v776::ActorDataIDs::TradeTarget,
    v776::ActorDataIDs::Career,
    v776::ActorDataIDs::HasCommandBlock,
    v776::ActorDataIDs::CommandName,
    v776::ActorDataIDs::LastCommandOutput,
    v776::ActorDataIDs::TrackCommandOutput,
    v776::ActorDataIDs::Reserved074,
    v776::ActorDataIDs::Strength,
    v776::ActorDataIDs::StrengthMax,
    v776::ActorDataIDs::DataSpellCastingColor,
    v776::ActorDataIDs::DataLifetimeTicks,
    v776::ActorDataIDs::PoseIndex,
    v776::ActorDataIDs::DataTickOffset,
    v776::ActorDataIDs::NametagAlwaysShow,
    v776::ActorDataIDs::Color2Index,
    v776::ActorDataIDs::NameAuthor,
    v776::ActorDataIDs::Score,
    v776::ActorDataIDs::BalloonAnchor,
    v776::ActorDataIDs::PuffedState,
    v776::ActorDataIDs::BubbleTime,
    v776::ActorDataIDs::Agent,
    v776::ActorDataIDs::SittingAmount,
    v776::ActorDataIDs::SittingAmountPrevious,
    v776::ActorDataIDs::EatingCounter,
    v776::ActorDataIDs::Reserved092,
    v776::ActorDataIDs::LayingAmount,
    v776::ActorDataIDs::LayingAmountPrevious,
    v776::ActorDataIDs::DataDuration,
    v776::ActorDataIDs::DataSpawnTimeDeprecated,
    v776::ActorDataIDs::DataChangeRate,
    v776::ActorDataIDs::DataChangeOnPickup,
    v776::ActorDataIDs::DataPickupCount,
    v776::ActorDataIDs::InteractText,
    v776::ActorDataIDs::TradeTier,
    v776::ActorDataIDs::MaxTradeTier,
    v776::ActorDataIDs::TradeExperience,
    v776::ActorDataIDs::SkinId,
    v776::ActorDataIDs::SpawningFrames,
    v776::ActorDataIDs::CommandBlockTickDelay,
    v776::ActorDataIDs::CommandBlockExecuteOnFirstTick,
    v776::ActorDataIDs::AmbientSoundInterval,
    v776::ActorDataIDs::AmbientSoundIntervalRange,
    v776::ActorDataIDs::AmbientSoundEventName,
    v776::ActorDataIDs::FallDamageMultiplier,
    v776::ActorDataIDs::NameRawText,
    v776::ActorDataIDs::CanRideTarget,
    v776::ActorDataIDs::LowTierCuredTradeDiscount,
    v776::ActorDataIDs::HighTierCuredTradeDiscount,
    v776::ActorDataIDs::NearbyCuredTradeDiscount,
    v776::ActorDataIDs::NearbyCuredDiscountTimeStamp,
    v776::ActorDataIDs::Hitbox,
    v776::ActorDataIDs::IsBuoyant,
    v776::ActorDataIDs::FreezingEffectStrength,
    v776::ActorDataIDs::BuoyancyData,
    v776::ActorDataIDs::GoatHornCount,
    v776::ActorDataIDs::BaseRuntimeId,
    v776::ActorDataIDs::MovementSoundDistanceOffset,
    v776::ActorDataIDs::HeartbeatIntervalTicks,
    v776::ActorDataIDs::HeartbeatSoundEvent,
    v776::ActorDataIDs::PlayerLastDeathPos,
    v776::ActorDataIDs::PlayerLastDeathDimension,
    v776::ActorDataIDs::PlayerHasDied,
    v776::ActorDataIDs::CollisionBox,
    v776::ActorDataIDs::VisibleMobEffects,
    v776::ActorDataIDs::FilteredName,
    v776::ActorDataIDs::EnterBedPosition,
    v776::ActorDataIDs::Count,
}};

template <>
inline constexpr std::array<std::string_view, 135> names_v<v776::ActorDataIDs>{{
    "reserved0",
    "structuralintegrity",
    "variant",
    "colorindex",
    "name",
    "owner",
    "target",
    "airsupply",
    "effectcolor",
    "reserved009",
    "reserved010",
    "hurt",
    "hurtdir",
    "rowtimeleft",
    "rowtimeright",
    "value",
    "displaytileruntimeid",
    "displayoffset",
    "customdisplay",
    "swell",
    "oldswell",
    "swelldir",
    "chargeamount",
    "deprecatedcarryblockruntimeid",
    "clientevent",
    "usingitem",
    "playerflags",
    "playerindex",
    "bedposition",
    "xpower",
    "ypower",
    "zpower",
    "auxpower",
    "fishx",
    "fishz",
    "fishangle",
    "auxvaluedata",
    "leashholder",
    "reserved038",
    "hasnpc",
    "npcdata",
    "actions",
    "airsupplymax",
    "markvariant",
    "containertype",
    "containersize",
    "containerstrengthmodifier",
    "blocktarget",
    "inv",
    "targeta",
    "targetb",
    "targetc",
    "aerialattack",
    "reserved053",
    "reserved054",
    "fusetime",
    "reserved056",
    "seatlockpassengerrotation",
    "seatlockpassengerrotationdegrees",
    "seatrotationoffset",
    "seatrotationoffsetdegrees",
    "dataradius",
    "datawaiting",
    "dataparticle",
    "peekid",
    "attachface",
    "attached",
    "attachpos",
    "tradetarget",
    "career",
    "hascommandblock",
    "commandname",
    "lastcommandoutput",
    "trackcommandoutput",
    "reserved074",
    "strength",
    "strengthmax",
    "dataspellcastingcolor",
    "datalifetimeticks",
    "poseindex",
    "datatickoffset",
    "nametagalwaysshow",
    "color2index",
    "nameauthor",
    "score",
    "balloonanchor",
    "puffedstate",
    "bubbletime",
    "agent",
    "sittingamount",
    "sittingamountprevious",
    "eatingcounter",
    "reserved092",
    "layingamount",
    "layingamountprevious",
    "dataduration",
    "dataspawntimedeprecated",
    "datachangerate",
    "datachangeonpickup",
    "datapickupcount",
    "interacttext",
    "tradetier",
    "maxtradetier",
    "tradeexperience",
    "skinid",
    "spawningframes",
    "commandblocktickdelay",
    "commandblockexecuteonfirsttick",
    "ambientsoundinterval",
    "ambientsoundintervalrange",
    "ambientsoundeventname",
    "falldamagemultiplier",
    "namerawtext",
    "canridetarget",
    "lowtiercuredtradediscount",
    "hightiercuredtradediscount",
    "nearbycuredtradediscount",
    "nearbycureddiscounttimestamp",
    "hitbox",
    "isbuoyant",
    "freezingeffectstrength",
    "buoyancydata",
    "goathorncount",
    "baseruntimeid",
    "movementsounddistanceoffset",
    "heartbeatintervalticks",
    "heartbeatsoundevent",
    "playerlastdeathpos",
    "playerlastdeathdimension",
    "playerhasdied",
    "collisionbox",
    "visiblemobeffects",
    "filteredname",
    "enterbedposition",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<v776::ActorDataIDs>{"ActorDataIDs"};

template <>
inline constexpr std::array<v800::ActorDataIDs, 137> values_v<v800::ActorDataIDs>{{
    v800::ActorDataIDs::Reserved0,
    v800::ActorDataIDs::StructuralIntegrity,
    v800::ActorDataIDs::Variant,
    v800::ActorDataIDs::ColorIndex,
    v800::ActorDataIDs::Name,
    v800::ActorDataIDs::Owner,
    v800::ActorDataIDs::Target,
    v800::ActorDataIDs::AirSupply,
    v800::ActorDataIDs::EffectColor,
    v800::ActorDataIDs::Reserved009,
    v800::ActorDataIDs::Reserved010,
    v800::ActorDataIDs::Hurt,
    v800::ActorDataIDs::HurtDir,
    v800::ActorDataIDs::RowTimeLeft,
    v800::ActorDataIDs::RowTimeRight,
    v800::ActorDataIDs::Value,
    v800::ActorDataIDs::DisplayTileRuntimeId,
    v800::ActorDataIDs::DisplayOffset,
    v800::ActorDataIDs::CustomDisplay,
    v800::ActorDataIDs::Swell,
    v800::ActorDataIDs::OldSwell,
    v800::ActorDataIDs::SwellDir,
    v800::ActorDataIDs::ChargeAmount,
    v800::ActorDataIDs::DeprecatedCarryBlockRuntimeId,
    v800::ActorDataIDs::ClientEvent,
    v800::ActorDataIDs::UsingItem,
    v800::ActorDataIDs::PlayerFlags,
    v800::ActorDataIDs::PlayerIndex,
    v800::ActorDataIDs::BedPosition,
    v800::ActorDataIDs::XPower,
    v800::ActorDataIDs::YPower,
    v800::ActorDataIDs::ZPower,
    v800::ActorDataIDs::AuxPower,
    v800::ActorDataIDs::Fishx,
    v800::ActorDataIDs::Fishz,
    v800::ActorDataIDs::Fishangle,
    v800::ActorDataIDs::AuxValueData,
    v800::ActorDataIDs::LeashHolder,
    v800::ActorDataIDs::Reserved038,
    v800::ActorDataIDs::HasNpc,
    v800::ActorDataIDs::NpcData,
    v800::ActorDataIDs::Actions,
    v800::ActorDataIDs::AirSupplyMax,
    v800::ActorDataIDs::MarkVariant,
    v800::ActorDataIDs::ContainerType,
    v800::ActorDataIDs::ContainerSize,
    v800::ActorDataIDs::ContainerStrengthModifier,
    v800::ActorDataIDs::BlockTarget,
    v800::ActorDataIDs::Inv,
    v800::ActorDataIDs::TargetA,
    v800::ActorDataIDs::TargetB,
    v800::ActorDataIDs::TargetC,
    v800::ActorDataIDs::AerialAttack,
    v800::ActorDataIDs::Reserved053,
    v800::ActorDataIDs::Reserved054,
    v800::ActorDataIDs::FuseTime,
    v800::ActorDataIDs::Reserved056,
    v800::ActorDataIDs::SeatLockPassengerRotation,
    v800::ActorDataIDs::SeatLockPassengerRotationDegrees,
    v800::ActorDataIDs::SeatRotationOffset,
    v800::ActorDataIDs::SeatRotationOffsetDegrees,
    v800::ActorDataIDs::DataRadius,
    v800::ActorDataIDs::DataWaiting,
    v800::ActorDataIDs::DataParticle,
    v800::ActorDataIDs::PeekId,
    v800::ActorDataIDs::AttachFace,
    v800::ActorDataIDs::Attached,
    v800::ActorDataIDs::AttachPos,
    v800::ActorDataIDs::TradeTarget,
    v800::ActorDataIDs::Career,
    v800::ActorDataIDs::HasCommandBlock,
    v800::ActorDataIDs::CommandName,
    v800::ActorDataIDs::LastCommandOutput,
    v800::ActorDataIDs::TrackCommandOutput,
    v800::ActorDataIDs::Reserved074,
    v800::ActorDataIDs::Strength,
    v800::ActorDataIDs::StrengthMax,
    v800::ActorDataIDs::DataSpellCastingColor,
    v800::ActorDataIDs::DataLifetimeTicks,
    v800::ActorDataIDs::PoseIndex,
    v800::ActorDataIDs::DataTickOffset,
    v800::ActorDataIDs::NametagAlwaysShow,
    v800::ActorDataIDs::Color2Index,
    v800::ActorDataIDs::NameAuthor,
    v800::ActorDataIDs::Score,
    v800::ActorDataIDs::BalloonAnchor,
    v800::ActorDataIDs::PuffedState,
    v800::ActorDataIDs::BubbleTime,
    v800::ActorDataIDs::Agent,
    v800::ActorDataIDs::SittingAmount,
    v800::ActorDataIDs::SittingAmountPrevious,
    v800::ActorDataIDs::EatingCounter,
    v800::ActorDataIDs::Reserved092,
    v800::ActorDataIDs::LayingAmount,
    v800::ActorDataIDs::LayingAmountPrevious,
    v800::ActorDataIDs::DataDuration,
    v800::ActorDataIDs::DataSpawnTimeDeprecated,
    v800::ActorDataIDs::DataChangeRate,
    v800::ActorDataIDs::DataChangeOnPickup,
    v800::ActorDataIDs::DataPickupCount,
    v800::ActorDataIDs::InteractText,
    v800::ActorDataIDs::TradeTier,
    v800::ActorDataIDs::MaxTradeTier,
    v800::ActorDataIDs::TradeExperience,
    v800::ActorDataIDs::SkinId,
    v800::ActorDataIDs::SpawningFrames,
    v800::ActorDataIDs::CommandBlockTickDelay,
    v800::ActorDataIDs::CommandBlockExecuteOnFirstTick,
    v800::ActorDataIDs::AmbientSoundInterval,
    v800::ActorDataIDs::AmbientSoundIntervalRange,
    v800::ActorDataIDs::AmbientSoundEventName,
    v800::ActorDataIDs::FallDamageMultiplier,
    v800::ActorDataIDs::NameRawText,
    v800::ActorDataIDs::CanRideTarget,
    v800::ActorDataIDs::LowTierCuredTradeDiscount,
    v800::ActorDataIDs::HighTierCuredTradeDiscount,
    v800::ActorDataIDs::NearbyCuredTradeDiscount,
    v800::ActorDataIDs::NearbyCuredDiscountTimeStamp,
    v800::ActorDataIDs::Hitbox,
    v800::ActorDataIDs::IsBuoyant,
    v800::ActorDataIDs::FreezingEffectStrength,
    v800::ActorDataIDs::BuoyancyData,
    v800::ActorDataIDs::GoatHornCount,
    v800::ActorDataIDs::BaseRuntimeId,
    v800::ActorDataIDs::MovementSoundDistanceOffset,
    v800::ActorDataIDs::HeartbeatIntervalTicks,
    v800::ActorDataIDs::HeartbeatSoundEvent,
    v800::ActorDataIDs::PlayerLastDeathPos,
    v800::ActorDataIDs::PlayerLastDeathDimension,
    v800::ActorDataIDs::PlayerHasDied,
    v800::ActorDataIDs::CollisionBox,
    v800::ActorDataIDs::VisibleMobEffects,
    v800::ActorDataIDs::FilteredName,
    v800::ActorDataIDs::EnterBedPosition,
    v800::ActorDataIDs::SeatThirdPersonCameraRadius,
    v800::ActorDataIDs::SeatCameraRelaxDistanceSmoothing,
    v800::ActorDataIDs::Count,
}};

template <>
inline constexpr std::array<std::string_view, 137> names_v<v800::ActorDataIDs>{{
    "reserved0",
    "structuralintegrity",
    "variant",
    "colorindex",
    "name",
    "owner",
    "target",
    "airsupply",
    "effectcolor",
    "reserved009",
    "reserved010",
    "hurt",
    "hurtdir",
    "rowtimeleft",
    "rowtimeright",
    "value",
    "displaytileruntimeid",
    "displayoffset",
    "customdisplay",
    "swell",
    "oldswell",
    "swelldir",
    "chargeamount",
    "deprecatedcarryblockruntimeid",
    "clientevent",
    "usingitem",
    "playerflags",
    "playerindex",
    "bedposition",
    "xpower",
    "ypower",
    "zpower",
    "auxpower",
    "fishx",
    "fishz",
    "fishangle",
    "auxvaluedata",
    "leashholder",
    "reserved038",
    "hasnpc",
    "npcdata",
    "actions",
    "airsupplymax",
    "markvariant",
    "containertype",
    "containersize",
    "containerstrengthmodifier",
    "blocktarget",
    "inv",
    "targeta",
    "targetb",
    "targetc",
    "aerialattack",
    "reserved053",
    "reserved054",
    "fusetime",
    "reserved056",
    "seatlockpassengerrotation",
    "seatlockpassengerrotationdegrees",
    "seatrotationoffset",
    "seatrotationoffsetdegrees",
    "dataradius",
    "datawaiting",
    "dataparticle",
    "peekid",
    "attachface",
    "attached",
    "attachpos",
    "tradetarget",
    "career",
    "hascommandblock",
    "commandname",
    "lastcommandoutput",
    "trackcommandoutput",
    "reserved074",
    "strength",
    "strengthmax",
    "dataspellcastingcolor",
    "datalifetimeticks",
    "poseindex",
    "datatickoffset",
    "nametagalwaysshow",
    "color2index",
    "nameauthor",
    "score",
    "balloonanchor",
    "puffedstate",
    "bubbletime",
    "agent",
    "sittingamount",
    "sittingamountprevious",
    "eatingcounter",
    "reserved092",
    "layingamount",
    "layingamountprevious",
    "dataduration",
    "dataspawntimedeprecated",
    "datachangerate",
    "datachangeonpickup",
    "datapickupcount",
    "interacttext",
    "tradetier",
    "maxtradetier",
    "tradeexperience",
    "skinid",
    "spawningframes",
    "commandblocktickdelay",
    "commandblockexecuteonfirsttick",
    "ambientsoundinterval",
    "ambientsoundintervalrange",
    "ambientsoundeventname",
    "falldamagemultiplier",
    "namerawtext",
    "canridetarget",
    "lowtiercuredtradediscount",
    "hightiercuredtradediscount",
    "nearbycuredtradediscount",
    "nearbycureddiscounttimestamp",
    "hitbox",
    "isbuoyant",
    "freezingeffectstrength",
    "buoyancydata",
    "goathorncount",
    "baseruntimeid",
    "movementsounddistanceoffset",
    "heartbeatintervalticks",
    "heartbeatsoundevent",
    "playerlastdeathpos",
    "playerlastdeathdimension",
    "playerhasdied",
    "collisionbox",
    "visiblemobeffects",
    "filteredname",
    "enterbedposition",
    "seatthirdpersoncameraradius",
    "seatcamerarelaxdistancesmoothing",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<v800::ActorDataIDs>{"ActorDataIDs"};

template <>
inline constexpr std::array<v924::ActorDataIDs, 140> values_v<v924::ActorDataIDs>{{
    v924::ActorDataIDs::Reserved0,
    v924::ActorDataIDs::StructuralIntegrity,
    v924::ActorDataIDs::Variant,
    v924::ActorDataIDs::ColorIndex,
    v924::ActorDataIDs::Name,
    v924::ActorDataIDs::Owner,
    v924::ActorDataIDs::Target,
    v924::ActorDataIDs::AirSupply,
    v924::ActorDataIDs::EffectColor,
    v924::ActorDataIDs::Reserved009,
    v924::ActorDataIDs::Reserved010,
    v924::ActorDataIDs::Hurt,
    v924::ActorDataIDs::HurtDir,
    v924::ActorDataIDs::RowTimeLeft,
    v924::ActorDataIDs::RowTimeRight,
    v924::ActorDataIDs::Value,
    v924::ActorDataIDs::DisplayTileRuntimeId,
    v924::ActorDataIDs::DisplayOffset,
    v924::ActorDataIDs::CustomDisplay,
    v924::ActorDataIDs::Swell,
    v924::ActorDataIDs::OldSwell,
    v924::ActorDataIDs::SwellDir,
    v924::ActorDataIDs::ChargeAmount,
    v924::ActorDataIDs::DeprecatedCarryBlockRuntimeId,
    v924::ActorDataIDs::ClientEvent,
    v924::ActorDataIDs::UsingItem,
    v924::ActorDataIDs::PlayerFlags,
    v924::ActorDataIDs::PlayerIndex,
    v924::ActorDataIDs::BedPosition,
    v924::ActorDataIDs::XPower,
    v924::ActorDataIDs::YPower,
    v924::ActorDataIDs::ZPower,
    v924::ActorDataIDs::AuxPower,
    v924::ActorDataIDs::Fishx,
    v924::ActorDataIDs::Fishz,
    v924::ActorDataIDs::Fishangle,
    v924::ActorDataIDs::AuxValueData,
    v924::ActorDataIDs::LeashHolder,
    v924::ActorDataIDs::Reserved038,
    v924::ActorDataIDs::HasNpc,
    v924::ActorDataIDs::NpcData,
    v924::ActorDataIDs::Actions,
    v924::ActorDataIDs::AirSupplyMax,
    v924::ActorDataIDs::MarkVariant,
    v924::ActorDataIDs::ContainerType,
    v924::ActorDataIDs::ContainerSize,
    v924::ActorDataIDs::ContainerStrengthModifier,
    v924::ActorDataIDs::BlockTarget,
    v924::ActorDataIDs::Inv,
    v924::ActorDataIDs::TargetA,
    v924::ActorDataIDs::TargetB,
    v924::ActorDataIDs::TargetC,
    v924::ActorDataIDs::AerialAttack,
    v924::ActorDataIDs::Reserved053,
    v924::ActorDataIDs::Reserved054,
    v924::ActorDataIDs::FuseTime,
    v924::ActorDataIDs::Reserved056,
    v924::ActorDataIDs::SeatLockPassengerRotation,
    v924::ActorDataIDs::SeatLockPassengerRotationDegrees,
    v924::ActorDataIDs::SeatRotationOffset,
    v924::ActorDataIDs::SeatRotationOffsetDegrees,
    v924::ActorDataIDs::DataRadius,
    v924::ActorDataIDs::DataWaiting,
    v924::ActorDataIDs::DataParticle,
    v924::ActorDataIDs::PeekId,
    v924::ActorDataIDs::AttachFace,
    v924::ActorDataIDs::Attached,
    v924::ActorDataIDs::AttachPos,
    v924::ActorDataIDs::TradeTarget,
    v924::ActorDataIDs::Career,
    v924::ActorDataIDs::HasCommandBlock,
    v924::ActorDataIDs::CommandName,
    v924::ActorDataIDs::LastCommandOutput,
    v924::ActorDataIDs::TrackCommandOutput,
    v924::ActorDataIDs::Reserved074,
    v924::ActorDataIDs::Strength,
    v924::ActorDataIDs::StrengthMax,
    v924::ActorDataIDs::DataSpellCastingColor,
    v924::ActorDataIDs::DataLifetimeTicks,
    v924::ActorDataIDs::PoseIndex,
    v924::ActorDataIDs::DataTickOffset,
    v924::ActorDataIDs::NametagAlwaysShow,
    v924::ActorDataIDs::Color2Index,
    v924::ActorDataIDs::NameAuthor,
    v924::ActorDataIDs::Score,
    v924::ActorDataIDs::BalloonAnchor,
    v924::ActorDataIDs::PuffedState,
    v924::ActorDataIDs::BubbleTime,
    v924::ActorDataIDs::Agent,
    v924::ActorDataIDs::SittingAmount,
    v924::ActorDataIDs::SittingAmountPrevious,
    v924::ActorDataIDs::EatingCounter,
    v924::ActorDataIDs::Reserved092,
    v924::ActorDataIDs::LayingAmount,
    v924::ActorDataIDs::LayingAmountPrevious,
    v924::ActorDataIDs::DataDuration,
    v924::ActorDataIDs::DataSpawnTimeDeprecated,
    v924::ActorDataIDs::DataChangeRate,
    v924::ActorDataIDs::DataChangeOnPickup,
    v924::ActorDataIDs::DataPickupCount,
    v924::ActorDataIDs::InteractText,
    v924::ActorDataIDs::TradeTier,
    v924::ActorDataIDs::MaxTradeTier,
    v924::ActorDataIDs::TradeExperience,
    v924::ActorDataIDs::SkinId,
    v924::ActorDataIDs::SpawningFrames,
    v924::ActorDataIDs::CommandBlockTickDelay,
    v924::ActorDataIDs::CommandBlockExecuteOnFirstTick,
    v924::ActorDataIDs::AmbientSoundInterval,
    v924::ActorDataIDs::AmbientSoundIntervalRange,
    v924::ActorDataIDs::AmbientSoundEventName,
    v924::ActorDataIDs::FallDamageMultiplier,
    v924::ActorDataIDs::NameRawText,
    v924::ActorDataIDs::CanRideTarget,
    v924::ActorDataIDs::LowTierCuredTradeDiscount,
    v924::ActorDataIDs::HighTierCuredTradeDiscount,
    v924::ActorDataIDs::NearbyCuredTradeDiscount,
    v924::ActorDataIDs::NearbyCuredDiscountTimeStamp,
    v924::ActorDataIDs::Hitbox,
    v924::ActorDataIDs::IsBuoyant,
    v924::ActorDataIDs::FreezingEffectStrength,
    v924::ActorDataIDs::BuoyancyData,
    v924::ActorDataIDs::GoatHornCount,
    v924::ActorDataIDs::BaseRuntimeId,
    v924::ActorDataIDs::MovementSoundDistanceOffset,
    v924::ActorDataIDs::HeartbeatIntervalTicks,
    v924::ActorDataIDs::HeartbeatSoundEvent,
    v924::ActorDataIDs::PlayerLastDeathPos,
    v924::ActorDataIDs::PlayerLastDeathDimension,
    v924::ActorDataIDs::PlayerHasDied,
    v924::ActorDataIDs::CollisionBox,
    v924::ActorDataIDs::VisibleMobEffects,
    v924::ActorDataIDs::FilteredName,
    v924::ActorDataIDs::EnterBedPosition,
    v924::ActorDataIDs::SeatThirdPersonCameraRadius,
    v924::ActorDataIDs::SeatCameraRelaxDistanceSmoothing,
    v924::ActorDataIDs::AimAssistPriorityPresetId,
    v924::ActorDataIDs::AimAssistPriorityCategoryId,
    v924::ActorDataIDs::AimAssistPriorityActorId,
    v924::ActorDataIDs::Count,
}};

template <>
inline constexpr std::array<std::string_view, 140> names_v<v924::ActorDataIDs>{{
    "reserved0",
    "structuralintegrity",
    "variant",
    "colorindex",
    "name",
    "owner",
    "target",
    "airsupply",
    "effectcolor",
    "reserved009",
    "reserved010",
    "hurt",
    "hurtdir",
    "rowtimeleft",
    "rowtimeright",
    "value",
    "displaytileruntimeid",
    "displayoffset",
    "customdisplay",
    "swell",
    "oldswell",
    "swelldir",
    "chargeamount",
    "deprecatedcarryblockruntimeid",
    "clientevent",
    "usingitem",
    "playerflags",
    "playerindex",
    "bedposition",
    "xpower",
    "ypower",
    "zpower",
    "auxpower",
    "fishx",
    "fishz",
    "fishangle",
    "auxvaluedata",
    "leashholder",
    "reserved038",
    "hasnpc",
    "npcdata",
    "actions",
    "airsupplymax",
    "markvariant",
    "containertype",
    "containersize",
    "containerstrengthmodifier",
    "blocktarget",
    "inv",
    "targeta",
    "targetb",
    "targetc",
    "aerialattack",
    "reserved053",
    "reserved054",
    "fusetime",
    "reserved056",
    "seatlockpassengerrotation",
    "seatlockpassengerrotationdegrees",
    "seatrotationoffset",
    "seatrotationoffsetdegrees",
    "dataradius",
    "datawaiting",
    "dataparticle",
    "peekid",
    "attachface",
    "attached",
    "attachpos",
    "tradetarget",
    "career",
    "hascommandblock",
    "commandname",
    "lastcommandoutput",
    "trackcommandoutput",
    "reserved074",
    "strength",
    "strengthmax",
    "dataspellcastingcolor",
    "datalifetimeticks",
    "poseindex",
    "datatickoffset",
    "nametagalwaysshow",
    "color2index",
    "nameauthor",
    "score",
    "balloonanchor",
    "puffedstate",
    "bubbletime",
    "agent",
    "sittingamount",
    "sittingamountprevious",
    "eatingcounter",
    "reserved092",
    "layingamount",
    "layingamountprevious",
    "dataduration",
    "dataspawntimedeprecated",
    "datachangerate",
    "datachangeonpickup",
    "datapickupcount",
    "interacttext",
    "tradetier",
    "maxtradetier",
    "tradeexperience",
    "skinid",
    "spawningframes",
    "commandblocktickdelay",
    "commandblockexecuteonfirsttick",
    "ambientsoundinterval",
    "ambientsoundintervalrange",
    "ambientsoundeventname",
    "falldamagemultiplier",
    "namerawtext",
    "canridetarget",
    "lowtiercuredtradediscount",
    "hightiercuredtradediscount",
    "nearbycuredtradediscount",
    "nearbycureddiscounttimestamp",
    "hitbox",
    "isbuoyant",
    "freezingeffectstrength",
    "buoyancydata",
    "goathorncount",
    "baseruntimeid",
    "movementsounddistanceoffset",
    "heartbeatintervalticks",
    "heartbeatsoundevent",
    "playerlastdeathpos",
    "playerlastdeathdimension",
    "playerhasdied",
    "collisionbox",
    "visiblemobeffects",
    "filteredname",
    "enterbedposition",
    "seatthirdpersoncameraradius",
    "seatcamerarelaxdistancesmoothing",
    "aimassistprioritypresetid",
    "aimassistprioritycategoryid",
    "aimassistpriorityactorid",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<v924::ActorDataIDs>{"ActorDataIDs"};

template <>
inline constexpr std::array<v975::ActorDataIDs, 142> values_v<v975::ActorDataIDs>{{
    v975::ActorDataIDs::Reserved0,
    v975::ActorDataIDs::StructuralIntegrity,
    v975::ActorDataIDs::Variant,
    v975::ActorDataIDs::ColorIndex,
    v975::ActorDataIDs::Name,
    v975::ActorDataIDs::Owner,
    v975::ActorDataIDs::Target,
    v975::ActorDataIDs::AirSupply,
    v975::ActorDataIDs::EffectColor,
    v975::ActorDataIDs::Reserved009,
    v975::ActorDataIDs::Reserved010,
    v975::ActorDataIDs::Hurt,
    v975::ActorDataIDs::HurtDir,
    v975::ActorDataIDs::RowTimeLeft,
    v975::ActorDataIDs::RowTimeRight,
    v975::ActorDataIDs::Value,
    v975::ActorDataIDs::DisplayTileRuntimeId,
    v975::ActorDataIDs::DisplayOffset,
    v975::ActorDataIDs::CustomDisplay,
    v975::ActorDataIDs::Swell,
    v975::ActorDataIDs::OldSwell,
    v975::ActorDataIDs::SwellDir,
    v975::ActorDataIDs::ChargeAmount,
    v975::ActorDataIDs::DeprecatedCarryBlockRuntimeId,
    v975::ActorDataIDs::ClientEvent,
    v975::ActorDataIDs::UsingItem,
    v975::ActorDataIDs::PlayerFlags,
    v975::ActorDataIDs::PlayerIndex,
    v975::ActorDataIDs::BedPosition,
    v975::ActorDataIDs::XPower,
    v975::ActorDataIDs::YPower,
    v975::ActorDataIDs::ZPower,
    v975::ActorDataIDs::AuxPower,
    v975::ActorDataIDs::Fishx,
    v975::ActorDataIDs::Fishz,
    v975::ActorDataIDs::Fishangle,
    v975::ActorDataIDs::AuxValueData,
    v975::ActorDataIDs::LeashHolder,
    v975::ActorDataIDs::Reserved038,
    v975::ActorDataIDs::HasNpc,
    v975::ActorDataIDs::NpcData,
    v975::ActorDataIDs::Actions,
    v975::ActorDataIDs::AirSupplyMax,
    v975::ActorDataIDs::MarkVariant,
    v975::ActorDataIDs::ContainerType,
    v975::ActorDataIDs::ContainerSize,
    v975::ActorDataIDs::ContainerStrengthModifier,
    v975::ActorDataIDs::BlockTarget,
    v975::ActorDataIDs::Inv,
    v975::ActorDataIDs::TargetA,
    v975::ActorDataIDs::TargetB,
    v975::ActorDataIDs::TargetC,
    v975::ActorDataIDs::AerialAttack,
    v975::ActorDataIDs::Reserved053,
    v975::ActorDataIDs::Reserved054,
    v975::ActorDataIDs::FuseTime,
    v975::ActorDataIDs::Reserved056,
    v975::ActorDataIDs::SeatLockPassengerRotation,
    v975::ActorDataIDs::SeatLockPassengerRotationDegrees,
    v975::ActorDataIDs::SeatRotationOffset,
    v975::ActorDataIDs::SeatRotationOffsetDegrees,
    v975::ActorDataIDs::DataRadius,
    v975::ActorDataIDs::DataWaiting,
    v975::ActorDataIDs::DataParticle,
    v975::ActorDataIDs::PeekId,
    v975::ActorDataIDs::AttachFace,
    v975::ActorDataIDs::Attached,
    v975::ActorDataIDs::AttachPos,
    v975::ActorDataIDs::TradeTarget,
    v975::ActorDataIDs::Career,
    v975::ActorDataIDs::HasCommandBlock,
    v975::ActorDataIDs::CommandName,
    v975::ActorDataIDs::LastCommandOutput,
    v975::ActorDataIDs::TrackCommandOutput,
    v975::ActorDataIDs::Reserved074,
    v975::ActorDataIDs::Strength,
    v975::ActorDataIDs::StrengthMax,
    v975::ActorDataIDs::DataSpellCastingColor,
    v975::ActorDataIDs::DataLifetimeTicks,
    v975::ActorDataIDs::PoseIndex,
    v975::ActorDataIDs::DataTickOffset,
    v975::ActorDataIDs::NametagAlwaysShow,
    v975::ActorDataIDs::Color2Index,
    v975::ActorDataIDs::NameAuthor,
    v975::ActorDataIDs::Score,
    v975::ActorDataIDs::BalloonAnchor,
    v975::ActorDataIDs::PuffedState,
    v975::ActorDataIDs::BubbleTime,
    v975::ActorDataIDs::Agent,
    v975::ActorDataIDs::SittingAmount,
    v975::ActorDataIDs::SittingAmountPrevious,
    v975::ActorDataIDs::EatingCounter,
    v975::ActorDataIDs::Reserved092,
    v975::ActorDataIDs::LayingAmount,
    v975::ActorDataIDs::LayingAmountPrevious,
    v975::ActorDataIDs::DataDuration,
    v975::ActorDataIDs::DataSpawnTimeDeprecated,
    v975::ActorDataIDs::DataChangeRate,
    v975::ActorDataIDs::DataChangeOnPickup,
    v975::ActorDataIDs::DataPickupCount,
    v975::ActorDataIDs::InteractText,
    v975::ActorDataIDs::TradeTier,
    v975::ActorDataIDs::MaxTradeTier,
    v975::ActorDataIDs::TradeExperience,
    v975::ActorDataIDs::SkinId,
    v975::ActorDataIDs::SpawningFrames,
    v975::ActorDataIDs::CommandBlockTickDelay,
    v975::ActorDataIDs::CommandBlockExecuteOnFirstTick,
    v975::ActorDataIDs::AmbientSoundInterval,
    v975::ActorDataIDs::AmbientSoundIntervalRange,
    v975::ActorDataIDs::AmbientSoundEventName,
    v975::ActorDataIDs::FallDamageMultiplier,
    v975::ActorDataIDs::NameRawText,
    v975::ActorDataIDs::CanRideTarget,
    v975::ActorDataIDs::LowTierCuredTradeDiscount,
    v975::ActorDataIDs::HighTierCuredTradeDiscount,
    v975::ActorDataIDs::NearbyCuredTradeDiscount,
    v975::ActorDataIDs::NearbyCuredDiscountTimeStamp,
    v975::ActorDataIDs::Hitbox,
    v975::ActorDataIDs::IsBuoyant,
    v975::ActorDataIDs::FreezingEffectStrength,
    v975::ActorDataIDs::BuoyancyData,
    v975::ActorDataIDs::GoatHornCount,
    v975::ActorDataIDs::BaseRuntimeId,
    v975::ActorDataIDs::MovementSoundDistanceOffset,
    v975::ActorDataIDs::HeartbeatIntervalTicks,
    v975::ActorDataIDs::HeartbeatSoundEvent,
    v975::ActorDataIDs::PlayerLastDeathPos,
    v975::ActorDataIDs::PlayerLastDeathDimension,
    v975::ActorDataIDs::PlayerHasDied,
    v975::ActorDataIDs::CollisionBox,
    v975::ActorDataIDs::VisibleMobEffects,
    v975::ActorDataIDs::FilteredName,
    v975::ActorDataIDs::EnterBedPosition,
    v975::ActorDataIDs::SeatThirdPersonCameraRadius,
    v975::ActorDataIDs::SeatCameraRelaxDistanceSmoothing,
    v975::ActorDataIDs::AimAssistPriorityPresetId,
    v975::ActorDataIDs::AimAssistPriorityCategoryId,
    v975::ActorDataIDs::AimAssistPriorityActorId,
    v975::ActorDataIDs::Reserved139,
    v975::ActorDataIDs::NameplateRenderDistanceMax,
    v975::ActorDataIDs::Count,
}};

template <>
inline constexpr std::array<std::string_view, 142> names_v<v975::ActorDataIDs>{{
    "reserved0",
    "structuralintegrity",
    "variant",
    "colorindex",
    "name",
    "owner",
    "target",
    "airsupply",
    "effectcolor",
    "reserved009",
    "reserved010",
    "hurt",
    "hurtdir",
    "rowtimeleft",
    "rowtimeright",
    "value",
    "displaytileruntimeid",
    "displayoffset",
    "customdisplay",
    "swell",
    "oldswell",
    "swelldir",
    "chargeamount",
    "deprecatedcarryblockruntimeid",
    "clientevent",
    "usingitem",
    "playerflags",
    "playerindex",
    "bedposition",
    "xpower",
    "ypower",
    "zpower",
    "auxpower",
    "fishx",
    "fishz",
    "fishangle",
    "auxvaluedata",
    "leashholder",
    "reserved038",
    "hasnpc",
    "npcdata",
    "actions",
    "airsupplymax",
    "markvariant",
    "containertype",
    "containersize",
    "containerstrengthmodifier",
    "blocktarget",
    "inv",
    "targeta",
    "targetb",
    "targetc",
    "aerialattack",
    "reserved053",
    "reserved054",
    "fusetime",
    "reserved056",
    "seatlockpassengerrotation",
    "seatlockpassengerrotationdegrees",
    "seatrotationoffset",
    "seatrotationoffsetdegrees",
    "dataradius",
    "datawaiting",
    "dataparticle",
    "peekid",
    "attachface",
    "attached",
    "attachpos",
    "tradetarget",
    "career",
    "hascommandblock",
    "commandname",
    "lastcommandoutput",
    "trackcommandoutput",
    "reserved074",
    "strength",
    "strengthmax",
    "dataspellcastingcolor",
    "datalifetimeticks",
    "poseindex",
    "datatickoffset",
    "nametagalwaysshow",
    "color2index",
    "nameauthor",
    "score",
    "balloonanchor",
    "puffedstate",
    "bubbletime",
    "agent",
    "sittingamount",
    "sittingamountprevious",
    "eatingcounter",
    "reserved092",
    "layingamount",
    "layingamountprevious",
    "dataduration",
    "dataspawntimedeprecated",
    "datachangerate",
    "datachangeonpickup",
    "datapickupcount",
    "interacttext",
    "tradetier",
    "maxtradetier",
    "tradeexperience",
    "skinid",
    "spawningframes",
    "commandblocktickdelay",
    "commandblockexecuteonfirsttick",
    "ambientsoundinterval",
    "ambientsoundintervalrange",
    "ambientsoundeventname",
    "falldamagemultiplier",
    "namerawtext",
    "canridetarget",
    "lowtiercuredtradediscount",
    "hightiercuredtradediscount",
    "nearbycuredtradediscount",
    "nearbycureddiscounttimestamp",
    "hitbox",
    "isbuoyant",
    "freezingeffectstrength",
    "buoyancydata",
    "goathorncount",
    "baseruntimeid",
    "movementsounddistanceoffset",
    "heartbeatintervalticks",
    "heartbeatsoundevent",
    "playerlastdeathpos",
    "playerlastdeathdimension",
    "playerhasdied",
    "collisionbox",
    "visiblemobeffects",
    "filteredname",
    "enterbedposition",
    "seatthirdpersoncameraradius",
    "seatcamerarelaxdistancesmoothing",
    "aimassistprioritypresetid",
    "aimassistprioritycategoryid",
    "aimassistpriorityactorid",
    "reserved139",
    "nameplaterenderdistancemax",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<v975::ActorDataIDs>{"ActorDataIDs"};

template <>
inline constexpr std::array<DataItemType, 10> values_v<DataItemType>{{
    DataItemType::Byte,
    DataItemType::Short,
    DataItemType::Int,
    DataItemType::Float,
    DataItemType::String,
    DataItemType::CompoundTag,
    DataItemType::Pos,
    DataItemType::Int64,
    DataItemType::Vec3,
    DataItemType::Unknown,
}};

template <>
inline constexpr std::array<std::string_view, 10> names_v<DataItemType>{{
    "byte",
    "short",
    "int",
    "float",
    "string",
    "compoundtag",
    "pos",
    "int64",
    "vec3",
    "unknown",
}};

template <>
inline constexpr std::string_view type_name_v<DataItemType>{"DataItemType"};

template <>
inline constexpr std::array<ActorLinkType, 3> values_v<ActorLinkType>{{
    ActorLinkType::None,
    ActorLinkType::Riding,
    ActorLinkType::Passenger,
}};

template <>
inline constexpr std::array<std::string_view, 3> names_v<ActorLinkType>{{
    "none",
    "riding",
    "passenger",
}};

template <>
inline constexpr std::string_view type_name_v<ActorLinkType>{"ActorLinkType"};

template <>
inline constexpr std::array<PassengerOfBlockArguments::EmoteType, 3> values_v<PassengerOfBlockArguments::EmoteType>{{
    PassengerOfBlockArguments::EmoteType::Standing,
    PassengerOfBlockArguments::EmoteType::Riding,
    PassengerOfBlockArguments::EmoteType::Laying,
}};

template <>
inline constexpr std::array<std::string_view, 3> names_v<PassengerOfBlockArguments::EmoteType>{{
    "standing",
    "riding",
    "laying",
}};

template <>
inline constexpr std::string_view type_name_v<PassengerOfBlockArguments::EmoteType>{"PassengerOfBlockArguments::EmoteType"};

template <>
inline constexpr std::array<base::ActorType, 155> values_v<base::ActorType>{{
    base::ActorType::Undefined,
    base::ActorType::TypeMask,
    base::ActorType::Mob,
    base::ActorType::PathfinderMob,
    base::ActorType::Monster,
    base::ActorType::Animal,
    base::ActorType::TamableAnimal,
    base::ActorType::Ambient,
    base::ActorType::UndeadMonster,
    base::ActorType::ZombieMonster,
    base::ActorType::Arthropod,
    base::ActorType::Minecart,
    base::ActorType::SkeletonMonster,
    base::ActorType::EquineAnimal,
    base::ActorType::Projectile,
    base::ActorType::AbstractArrow,
    base::ActorType::WaterAnimal,
    base::ActorType::VillagerBase,
    base::ActorType::Chicken,
    base::ActorType::Cow,
    base::ActorType::Pig,
    base::ActorType::Sheep,
    base::ActorType::Wolf,
    base::ActorType::Villager,
    base::ActorType::MushroomCow,
    base::ActorType::Squid,
    base::ActorType::Rabbit,
    base::ActorType::Bat,
    base::ActorType::IronGolem,
    base::ActorType::SnowGolem,
    base::ActorType::Ocelot,
    base::ActorType::Horse,
    base::ActorType::PolarBear,
    base::ActorType::Llama,
    base::ActorType::Parrot,
    base::ActorType::Dolphin,
    base::ActorType::Donkey,
    base::ActorType::Mule,
    base::ActorType::SkeletonHorse,
    base::ActorType::ZombieHorse,
    base::ActorType::Zombie,
    base::ActorType::Creeper,
    base::ActorType::Skeleton,
    base::ActorType::Spider,
    base::ActorType::PigZombie,
    base::ActorType::Slime,
    base::ActorType::EnderMan,
    base::ActorType::Silverfish,
    base::ActorType::CaveSpider,
    base::ActorType::Ghast,
    base::ActorType::LavaSlime,
    base::ActorType::Blaze,
    base::ActorType::ZombieVillager,
    base::ActorType::Witch,
    base::ActorType::Stray,
    base::ActorType::Husk,
    base::ActorType::WitherSkeleton,
    base::ActorType::Guardian,
    base::ActorType::ElderGuardian,
    base::ActorType::Npc,
    base::ActorType::WitherBoss,
    base::ActorType::Dragon,
    base::ActorType::Shulker,
    base::ActorType::Endermite,
    base::ActorType::Agent,
    base::ActorType::Vindicator,
    base::ActorType::Phantom,
    base::ActorType::IllagerBeast,
    base::ActorType::ArmorStand,
    base::ActorType::TripodCamera,
    base::ActorType::Player,
    base::ActorType::ItemEntity,
    base::ActorType::PrimedTnt,
    base::ActorType::FallingBlock,
    base::ActorType::MovingBlock,
    base::ActorType::ExperiencePotion,
    base::ActorType::Experience,
    base::ActorType::EyeOfEnder,
    base::ActorType::EnderCrystal,
    base::ActorType::FireworksRocket,
    base::ActorType::Trident,
    base::ActorType::Turtle,
    base::ActorType::Cat,
    base::ActorType::ShulkerBullet,
    base::ActorType::FishingHook,
    base::ActorType::Chalkboard,
    base::ActorType::DragonFireball,
    base::ActorType::Arrow,
    base::ActorType::Snowball,
    base::ActorType::ThrownEgg,
    base::ActorType::Painting,
    base::ActorType::LargeFireball,
    base::ActorType::ThrownPotion,
    base::ActorType::Enderpearl,
    base::ActorType::LeashKnot,
    base::ActorType::WitherSkull,
    base::ActorType::BoatRideable,
    base::ActorType::WitherSkullDangerous,
    base::ActorType::LightningBolt,
    base::ActorType::SmallFireball,
    base::ActorType::AreaEffectCloud,
    base::ActorType::LingeringPotion,
    base::ActorType::LlamaSpit,
    base::ActorType::EvocationFang,
    base::ActorType::EvocationIllager,
    base::ActorType::Vex,
    base::ActorType::MinecartRideable,
    base::ActorType::MinecartHopper,
    base::ActorType::MinecartTNT,
    base::ActorType::MinecartChest,
    base::ActorType::MinecartFurnace,
    base::ActorType::MinecartCommandBlock,
    base::ActorType::IceBomb,
    base::ActorType::Balloon,
    base::ActorType::Pufferfish,
    base::ActorType::Salmon,
    base::ActorType::Drowned,
    base::ActorType::Tropicalfish,
    base::ActorType::Fish,
    base::ActorType::Panda,
    base::ActorType::Pillager,
    base::ActorType::VillagerV2,
    base::ActorType::ZombieVillagerV2,
    base::ActorType::Shield,
    base::ActorType::WanderingTrader,
    base::ActorType::Lectern,
    base::ActorType::ElderGuardianGhost,
    base::ActorType::Fox,
    base::ActorType::Bee,
    base::ActorType::Piglin,
    base::ActorType::Hoglin,
    base::ActorType::Strider,
    base::ActorType::Zoglin,
    base::ActorType::PiglinBrute,
    base::ActorType::Goat,
    base::ActorType::GlowSquid,
    base::ActorType::Axolotl,
    base::ActorType::Warden,
    base::ActorType::Frog,
    base::ActorType::Tadpole,
    base::ActorType::Allay,
    base::ActorType::ChestBoatRideable,
    base::ActorType::TraderLlama,
    base::ActorType::Camel,
    base::ActorType::Sniffer,
    base::ActorType::Breeze,
    base::ActorType::BreezeWindChargeProjectile,
    base::ActorType::Armadillo,
    base::ActorType::WindChargeProjectile,
    base::ActorType::Bogged,
    base::ActorType::OminousItemSpawner,
    base::ActorType::Nautilus,
    base::ActorType::ZombieNautilus,
    base::ActorType::Parched,
    base::ActorType::CamelHusk,
}};

template <>
inline constexpr std::array<std::string_view, 155> names_v<base::ActorType>{{
    "undefined",
    "typemask",
    "mob",
    "pathfindermob",
    "monster",
    "animal",
    "tamableanimal",
    "ambient",
    "undeadmonster",
    "zombiemonster",
    "arthropod",
    "minecart",
    "skeletonmonster",
    "equineanimal",
    "projectile",
    "abstractarrow",
    "wateranimal",
    "villagerbase",
    "chicken",
    "cow",
    "pig",
    "sheep",
    "wolf",
    "villager",
    "mushroomcow",
    "squid",
    "rabbit",
    "bat",
    "irongolem",
    "snowgolem",
    "ocelot",
    "horse",
    "polarbear",
    "llama",
    "parrot",
    "dolphin",
    "donkey",
    "mule",
    "skeletonhorse",
    "zombiehorse",
    "zombie",
    "creeper",
    "skeleton",
    "spider",
    "pigzombie",
    "slime",
    "enderman",
    "silverfish",
    "cavespider",
    "ghast",
    "lavaslime",
    "blaze",
    "zombievillager",
    "witch",
    "stray",
    "husk",
    "witherskeleton",
    "guardian",
    "elderguardian",
    "npc",
    "witherboss",
    "dragon",
    "shulker",
    "endermite",
    "agent",
    "vindicator",
    "phantom",
    "illagerbeast",
    "armorstand",
    "tripodcamera",
    "player",
    "itementity",
    "primedtnt",
    "fallingblock",
    "movingblock",
    "experiencepotion",
    "experience",
    "eyeofender",
    "endercrystal",
    "fireworksrocket",
    "trident",
    "turtle",
    "cat",
    "shulkerbullet",
    "fishinghook",
    "chalkboard",
    "dragonfireball",
    "arrow",
    "snowball",
    "thrownegg",
    "painting",
    "largefireball",
    "thrownpotion",
    "enderpearl",
    "leashknot",
    "witherskull",
    "boatrideable",
    "witherskulldangerous",
    "lightningbolt",
    "smallfireball",
    "areaeffectcloud",
    "lingeringpotion",
    "llamaspit",
    "evocationfang",
    "evocationillager",
    "vex",
    "minecartrideable",
    "minecarthopper",
    "minecarttnt",
    "minecartchest",
    "minecartfurnace",
    "minecartcommandblock",
    "icebomb",
    "balloon",
    "pufferfish",
    "salmon",
    "drowned",
    "tropicalfish",
    "fish",
    "panda",
    "pillager",
    "villagerv2",
    "zombievillagerv2",
    "shield",
    "wanderingtrader",
    "lectern",
    "elderguardianghost",
    "fox",
    "bee",
    "piglin",
    "hoglin",
    "strider",
    "zoglin",
    "piglinbrute",
    "goat",
    "glowsquid",
    "axolotl",
    "warden",
    "frog",
    "tadpole",
    "allay",
    "chestboatrideable",
    "traderllama",
    "camel",
    "sniffer",
    "breeze",
    "breezewindchargeprojectile",
    "armadillo",
    "windchargeprojectile",
    "bogged",
    "ominousitemspawner",
    "nautilus",
    "zombienautilus",
    "parched",
    "camelhusk",
}};

template <>
inline constexpr std::string_view type_name_v<base::ActorType>{"ActorType"};

template <>
inline constexpr std::array<v766::ActorType, 156> values_v<v766::ActorType>{{
    v766::ActorType::Undefined,
    v766::ActorType::TypeMask,
    v766::ActorType::Mob,
    v766::ActorType::PathfinderMob,
    v766::ActorType::Monster,
    v766::ActorType::Animal,
    v766::ActorType::TamableAnimal,
    v766::ActorType::Ambient,
    v766::ActorType::UndeadMonster,
    v766::ActorType::ZombieMonster,
    v766::ActorType::Arthropod,
    v766::ActorType::Minecart,
    v766::ActorType::SkeletonMonster,
    v766::ActorType::EquineAnimal,
    v766::ActorType::Projectile,
    v766::ActorType::AbstractArrow,
    v766::ActorType::WaterAnimal,
    v766::ActorType::VillagerBase,
    v766::ActorType::Chicken,
    v766::ActorType::Cow,
    v766::ActorType::Pig,
    v766::ActorType::Sheep,
    v766::ActorType::Wolf,
    v766::ActorType::Villager,
    v766::ActorType::MushroomCow,
    v766::ActorType::Squid,
    v766::ActorType::Rabbit,
    v766::ActorType::Bat,
    v766::ActorType::IronGolem,
    v766::ActorType::SnowGolem,
    v766::ActorType::Ocelot,
    v766::ActorType::Horse,
    v766::ActorType::PolarBear,
    v766::ActorType::Llama,
    v766::ActorType::Parrot,
    v766::ActorType::Dolphin,
    v766::ActorType::Donkey,
    v766::ActorType::Mule,
    v766::ActorType::SkeletonHorse,
    v766::ActorType::ZombieHorse,
    v766::ActorType::Zombie,
    v766::ActorType::Creeper,
    v766::ActorType::Skeleton,
    v766::ActorType::Spider,
    v766::ActorType::PigZombie,
    v766::ActorType::Slime,
    v766::ActorType::EnderMan,
    v766::ActorType::Silverfish,
    v766::ActorType::CaveSpider,
    v766::ActorType::Ghast,
    v766::ActorType::LavaSlime,
    v766::ActorType::Blaze,
    v766::ActorType::ZombieVillager,
    v766::ActorType::Witch,
    v766::ActorType::Stray,
    v766::ActorType::Husk,
    v766::ActorType::WitherSkeleton,
    v766::ActorType::Guardian,
    v766::ActorType::ElderGuardian,
    v766::ActorType::Npc,
    v766::ActorType::WitherBoss,
    v766::ActorType::Dragon,
    v766::ActorType::Shulker,
    v766::ActorType::Endermite,
    v766::ActorType::Agent,
    v766::ActorType::Vindicator,
    v766::ActorType::Phantom,
    v766::ActorType::IllagerBeast,
    v766::ActorType::ArmorStand,
    v766::ActorType::TripodCamera,
    v766::ActorType::Player,
    v766::ActorType::ItemEntity,
    v766::ActorType::PrimedTnt,
    v766::ActorType::FallingBlock,
    v766::ActorType::MovingBlock,
    v766::ActorType::ExperiencePotion,
    v766::ActorType::Experience,
    v766::ActorType::EyeOfEnder,
    v766::ActorType::EnderCrystal,
    v766::ActorType::FireworksRocket,
    v766::ActorType::Trident,
    v766::ActorType::Turtle,
    v766::ActorType::Cat,
    v766::ActorType::ShulkerBullet,
    v766::ActorType::FishingHook,
    v766::ActorType::Chalkboard,
    v766::ActorType::DragonFireball,
    v766::ActorType::Arrow,
    v766::ActorType::Snowball,
    v766::ActorType::ThrownEgg,
    v766::ActorType::Painting,
    v766::ActorType::LargeFireball,
    v766::ActorType::ThrownPotion,
    v766::ActorType::Enderpearl,
    v766::ActorType::LeashKnot,
    v766::ActorType::WitherSkull,
    v766::ActorType::BoatRideable,
    v766::ActorType::WitherSkullDangerous,
    v766::ActorType::LightningBolt,
    v766::ActorType::SmallFireball,
    v766::ActorType::AreaEffectCloud,
    v766::ActorType::LingeringPotion,
    v766::ActorType::LlamaSpit,
    v766::ActorType::EvocationFang,
    v766::ActorType::EvocationIllager,
    v766::ActorType::Vex,
    v766::ActorType::MinecartRideable,
    v766::ActorType::MinecartHopper,
    v766::ActorType::MinecartTNT,
    v766::ActorType::MinecartChest,
    v766::ActorType::MinecartFurnace,
    v766::ActorType::MinecartCommandBlock,
    v766::ActorType::IceBomb,
    v766::ActorType::Balloon,
    v766::ActorType::Pufferfish,
    v766::ActorType::Salmon,
    v766::ActorType::Drowned,
    v766::ActorType::Tropicalfish,
    v766::ActorType::Fish,
    v766::ActorType::Panda,
    v766::ActorType::Pillager,
    v766::ActorType::VillagerV2,
    v766::ActorType::ZombieVillagerV2,
    v766::ActorType::Shield,
    v766::ActorType::WanderingTrader,
    v766::ActorType::Lectern,
    v766::ActorType::ElderGuardianGhost,
    v766::ActorType::Fox,
    v766::ActorType::Bee,
    v766::ActorType::Piglin,
    v766::ActorType::Hoglin,
    v766::ActorType::Strider,
    v766::ActorType::Zoglin,
    v766::ActorType::PiglinBrute,
    v766::ActorType::Goat,
    v766::ActorType::GlowSquid,
    v766::ActorType::Axolotl,
    v766::ActorType::Warden,
    v766::ActorType::Frog,
    v766::ActorType::Tadpole,
    v766::ActorType::Allay,
    v766::ActorType::ChestBoatRideable,
    v766::ActorType::TraderLlama,
    v766::ActorType::Camel,
    v766::ActorType::Sniffer,
    v766::ActorType::Breeze,
    v766::ActorType::BreezeWindChargeProjectile,
    v766::ActorType::Armadillo,
    v766::ActorType::WindChargeProjectile,
    v766::ActorType::Bogged,
    v766::ActorType::OminousItemSpawner,
    v766::ActorType::Creaking,
    v766::ActorType::Nautilus,
    v766::ActorType::ZombieNautilus,
    v766::ActorType::Parched,
    v766::ActorType::CamelHusk,
}};

template <>
inline constexpr std::array<std::string_view, 156> names_v<v766::ActorType>{{
    "undefined",
    "typemask",
    "mob",
    "pathfindermob",
    "monster",
    "animal",
    "tamableanimal",
    "ambient",
    "undeadmonster",
    "zombiemonster",
    "arthropod",
    "minecart",
    "skeletonmonster",
    "equineanimal",
    "projectile",
    "abstractarrow",
    "wateranimal",
    "villagerbase",
    "chicken",
    "cow",
    "pig",
    "sheep",
    "wolf",
    "villager",
    "mushroomcow",
    "squid",
    "rabbit",
    "bat",
    "irongolem",
    "snowgolem",
    "ocelot",
    "horse",
    "polarbear",
    "llama",
    "parrot",
    "dolphin",
    "donkey",
    "mule",
    "skeletonhorse",
    "zombiehorse",
    "zombie",
    "creeper",
    "skeleton",
    "spider",
    "pigzombie",
    "slime",
    "enderman",
    "silverfish",
    "cavespider",
    "ghast",
    "lavaslime",
    "blaze",
    "zombievillager",
    "witch",
    "stray",
    "husk",
    "witherskeleton",
    "guardian",
    "elderguardian",
    "npc",
    "witherboss",
    "dragon",
    "shulker",
    "endermite",
    "agent",
    "vindicator",
    "phantom",
    "illagerbeast",
    "armorstand",
    "tripodcamera",
    "player",
    "itementity",
    "primedtnt",
    "fallingblock",
    "movingblock",
    "experiencepotion",
    "experience",
    "eyeofender",
    "endercrystal",
    "fireworksrocket",
    "trident",
    "turtle",
    "cat",
    "shulkerbullet",
    "fishinghook",
    "chalkboard",
    "dragonfireball",
    "arrow",
    "snowball",
    "thrownegg",
    "painting",
    "largefireball",
    "thrownpotion",
    "enderpearl",
    "leashknot",
    "witherskull",
    "boatrideable",
    "witherskulldangerous",
    "lightningbolt",
    "smallfireball",
    "areaeffectcloud",
    "lingeringpotion",
    "llamaspit",
    "evocationfang",
    "evocationillager",
    "vex",
    "minecartrideable",
    "minecarthopper",
    "minecarttnt",
    "minecartchest",
    "minecartfurnace",
    "minecartcommandblock",
    "icebomb",
    "balloon",
    "pufferfish",
    "salmon",
    "drowned",
    "tropicalfish",
    "fish",
    "panda",
    "pillager",
    "villagerv2",
    "zombievillagerv2",
    "shield",
    "wanderingtrader",
    "lectern",
    "elderguardianghost",
    "fox",
    "bee",
    "piglin",
    "hoglin",
    "strider",
    "zoglin",
    "piglinbrute",
    "goat",
    "glowsquid",
    "axolotl",
    "warden",
    "frog",
    "tadpole",
    "allay",
    "chestboatrideable",
    "traderllama",
    "camel",
    "sniffer",
    "breeze",
    "breezewindchargeprojectile",
    "armadillo",
    "windchargeprojectile",
    "bogged",
    "ominousitemspawner",
    "creaking",
    "nautilus",
    "zombienautilus",
    "parched",
    "camelhusk",
}};

template <>
inline constexpr std::string_view type_name_v<v766::ActorType>{"ActorType"};

template <>
inline constexpr std::array<v800::ActorType, 157> values_v<v800::ActorType>{{
    v800::ActorType::Undefined,
    v800::ActorType::TypeMask,
    v800::ActorType::Mob,
    v800::ActorType::PathfinderMob,
    v800::ActorType::Monster,
    v800::ActorType::Animal,
    v800::ActorType::TamableAnimal,
    v800::ActorType::Ambient,
    v800::ActorType::UndeadMonster,
    v800::ActorType::ZombieMonster,
    v800::ActorType::Arthropod,
    v800::ActorType::Minecart,
    v800::ActorType::SkeletonMonster,
    v800::ActorType::EquineAnimal,
    v800::ActorType::Projectile,
    v800::ActorType::AbstractArrow,
    v800::ActorType::WaterAnimal,
    v800::ActorType::VillagerBase,
    v800::ActorType::Chicken,
    v800::ActorType::Cow,
    v800::ActorType::Pig,
    v800::ActorType::Sheep,
    v800::ActorType::Wolf,
    v800::ActorType::Villager,
    v800::ActorType::MushroomCow,
    v800::ActorType::Squid,
    v800::ActorType::Rabbit,
    v800::ActorType::Bat,
    v800::ActorType::IronGolem,
    v800::ActorType::SnowGolem,
    v800::ActorType::Ocelot,
    v800::ActorType::Horse,
    v800::ActorType::PolarBear,
    v800::ActorType::Llama,
    v800::ActorType::Parrot,
    v800::ActorType::Dolphin,
    v800::ActorType::Donkey,
    v800::ActorType::Mule,
    v800::ActorType::SkeletonHorse,
    v800::ActorType::ZombieHorse,
    v800::ActorType::Zombie,
    v800::ActorType::Creeper,
    v800::ActorType::Skeleton,
    v800::ActorType::Spider,
    v800::ActorType::PigZombie,
    v800::ActorType::Slime,
    v800::ActorType::EnderMan,
    v800::ActorType::Silverfish,
    v800::ActorType::CaveSpider,
    v800::ActorType::Ghast,
    v800::ActorType::LavaSlime,
    v800::ActorType::Blaze,
    v800::ActorType::ZombieVillager,
    v800::ActorType::Witch,
    v800::ActorType::Stray,
    v800::ActorType::Husk,
    v800::ActorType::WitherSkeleton,
    v800::ActorType::Guardian,
    v800::ActorType::ElderGuardian,
    v800::ActorType::Npc,
    v800::ActorType::WitherBoss,
    v800::ActorType::Dragon,
    v800::ActorType::Shulker,
    v800::ActorType::Endermite,
    v800::ActorType::Agent,
    v800::ActorType::Vindicator,
    v800::ActorType::Phantom,
    v800::ActorType::IllagerBeast,
    v800::ActorType::ArmorStand,
    v800::ActorType::TripodCamera,
    v800::ActorType::Player,
    v800::ActorType::ItemEntity,
    v800::ActorType::PrimedTnt,
    v800::ActorType::FallingBlock,
    v800::ActorType::MovingBlock,
    v800::ActorType::ExperiencePotion,
    v800::ActorType::Experience,
    v800::ActorType::EyeOfEnder,
    v800::ActorType::EnderCrystal,
    v800::ActorType::FireworksRocket,
    v800::ActorType::Trident,
    v800::ActorType::Turtle,
    v800::ActorType::Cat,
    v800::ActorType::ShulkerBullet,
    v800::ActorType::FishingHook,
    v800::ActorType::Chalkboard,
    v800::ActorType::DragonFireball,
    v800::ActorType::Arrow,
    v800::ActorType::Snowball,
    v800::ActorType::ThrownEgg,
    v800::ActorType::Painting,
    v800::ActorType::LargeFireball,
    v800::ActorType::ThrownPotion,
    v800::ActorType::Enderpearl,
    v800::ActorType::LeashKnot,
    v800::ActorType::WitherSkull,
    v800::ActorType::BoatRideable,
    v800::ActorType::WitherSkullDangerous,
    v800::ActorType::LightningBolt,
    v800::ActorType::SmallFireball,
    v800::ActorType::AreaEffectCloud,
    v800::ActorType::LingeringPotion,
    v800::ActorType::LlamaSpit,
    v800::ActorType::EvocationFang,
    v800::ActorType::EvocationIllager,
    v800::ActorType::Vex,
    v800::ActorType::MinecartRideable,
    v800::ActorType::MinecartHopper,
    v800::ActorType::MinecartTNT,
    v800::ActorType::MinecartChest,
    v800::ActorType::MinecartFurnace,
    v800::ActorType::MinecartCommandBlock,
    v800::ActorType::IceBomb,
    v800::ActorType::Balloon,
    v800::ActorType::Pufferfish,
    v800::ActorType::Salmon,
    v800::ActorType::Drowned,
    v800::ActorType::Tropicalfish,
    v800::ActorType::Fish,
    v800::ActorType::Panda,
    v800::ActorType::Pillager,
    v800::ActorType::VillagerV2,
    v800::ActorType::ZombieVillagerV2,
    v800::ActorType::Shield,
    v800::ActorType::WanderingTrader,
    v800::ActorType::Lectern,
    v800::ActorType::ElderGuardianGhost,
    v800::ActorType::Fox,
    v800::ActorType::Bee,
    v800::ActorType::Piglin,
    v800::ActorType::Hoglin,
    v800::ActorType::Strider,
    v800::ActorType::Zoglin,
    v800::ActorType::PiglinBrute,
    v800::ActorType::Goat,
    v800::ActorType::GlowSquid,
    v800::ActorType::Axolotl,
    v800::ActorType::Warden,
    v800::ActorType::Frog,
    v800::ActorType::Tadpole,
    v800::ActorType::Allay,
    v800::ActorType::ChestBoatRideable,
    v800::ActorType::TraderLlama,
    v800::ActorType::Camel,
    v800::ActorType::Sniffer,
    v800::ActorType::Breeze,
    v800::ActorType::BreezeWindChargeProjectile,
    v800::ActorType::Armadillo,
    v800::ActorType::WindChargeProjectile,
    v800::ActorType::Bogged,
    v800::ActorType::OminousItemSpawner,
    v800::ActorType::Creaking,
    v800::ActorType::HappyGhast,
    v800::ActorType::Nautilus,
    v800::ActorType::ZombieNautilus,
    v800::ActorType::Parched,
    v800::ActorType::CamelHusk,
}};

template <>
inline constexpr std::array<std::string_view, 157> names_v<v800::ActorType>{{
    "undefined",
    "typemask",
    "mob",
    "pathfindermob",
    "monster",
    "animal",
    "tamableanimal",
    "ambient",
    "undeadmonster",
    "zombiemonster",
    "arthropod",
    "minecart",
    "skeletonmonster",
    "equineanimal",
    "projectile",
    "abstractarrow",
    "wateranimal",
    "villagerbase",
    "chicken",
    "cow",
    "pig",
    "sheep",
    "wolf",
    "villager",
    "mushroomcow",
    "squid",
    "rabbit",
    "bat",
    "irongolem",
    "snowgolem",
    "ocelot",
    "horse",
    "polarbear",
    "llama",
    "parrot",
    "dolphin",
    "donkey",
    "mule",
    "skeletonhorse",
    "zombiehorse",
    "zombie",
    "creeper",
    "skeleton",
    "spider",
    "pigzombie",
    "slime",
    "enderman",
    "silverfish",
    "cavespider",
    "ghast",
    "lavaslime",
    "blaze",
    "zombievillager",
    "witch",
    "stray",
    "husk",
    "witherskeleton",
    "guardian",
    "elderguardian",
    "npc",
    "witherboss",
    "dragon",
    "shulker",
    "endermite",
    "agent",
    "vindicator",
    "phantom",
    "illagerbeast",
    "armorstand",
    "tripodcamera",
    "player",
    "itementity",
    "primedtnt",
    "fallingblock",
    "movingblock",
    "experiencepotion",
    "experience",
    "eyeofender",
    "endercrystal",
    "fireworksrocket",
    "trident",
    "turtle",
    "cat",
    "shulkerbullet",
    "fishinghook",
    "chalkboard",
    "dragonfireball",
    "arrow",
    "snowball",
    "thrownegg",
    "painting",
    "largefireball",
    "thrownpotion",
    "enderpearl",
    "leashknot",
    "witherskull",
    "boatrideable",
    "witherskulldangerous",
    "lightningbolt",
    "smallfireball",
    "areaeffectcloud",
    "lingeringpotion",
    "llamaspit",
    "evocationfang",
    "evocationillager",
    "vex",
    "minecartrideable",
    "minecarthopper",
    "minecarttnt",
    "minecartchest",
    "minecartfurnace",
    "minecartcommandblock",
    "icebomb",
    "balloon",
    "pufferfish",
    "salmon",
    "drowned",
    "tropicalfish",
    "fish",
    "panda",
    "pillager",
    "villagerv2",
    "zombievillagerv2",
    "shield",
    "wanderingtrader",
    "lectern",
    "elderguardianghost",
    "fox",
    "bee",
    "piglin",
    "hoglin",
    "strider",
    "zoglin",
    "piglinbrute",
    "goat",
    "glowsquid",
    "axolotl",
    "warden",
    "frog",
    "tadpole",
    "allay",
    "chestboatrideable",
    "traderllama",
    "camel",
    "sniffer",
    "breeze",
    "breezewindchargeprojectile",
    "armadillo",
    "windchargeprojectile",
    "bogged",
    "ominousitemspawner",
    "creaking",
    "happyghast",
    "nautilus",
    "zombienautilus",
    "parched",
    "camelhusk",
}};

template <>
inline constexpr std::string_view type_name_v<v800::ActorType>{"ActorType"};

template <>
inline constexpr std::array<v827::ActorType, 158> values_v<v827::ActorType>{{
    v827::ActorType::Undefined,
    v827::ActorType::TypeMask,
    v827::ActorType::Mob,
    v827::ActorType::PathfinderMob,
    v827::ActorType::Monster,
    v827::ActorType::Animal,
    v827::ActorType::TamableAnimal,
    v827::ActorType::Ambient,
    v827::ActorType::UndeadMonster,
    v827::ActorType::ZombieMonster,
    v827::ActorType::Arthropod,
    v827::ActorType::Minecart,
    v827::ActorType::SkeletonMonster,
    v827::ActorType::EquineAnimal,
    v827::ActorType::Projectile,
    v827::ActorType::AbstractArrow,
    v827::ActorType::WaterAnimal,
    v827::ActorType::VillagerBase,
    v827::ActorType::Chicken,
    v827::ActorType::Cow,
    v827::ActorType::Pig,
    v827::ActorType::Sheep,
    v827::ActorType::Wolf,
    v827::ActorType::Villager,
    v827::ActorType::MushroomCow,
    v827::ActorType::Squid,
    v827::ActorType::Rabbit,
    v827::ActorType::Bat,
    v827::ActorType::IronGolem,
    v827::ActorType::SnowGolem,
    v827::ActorType::Ocelot,
    v827::ActorType::Horse,
    v827::ActorType::PolarBear,
    v827::ActorType::Llama,
    v827::ActorType::Parrot,
    v827::ActorType::Dolphin,
    v827::ActorType::Donkey,
    v827::ActorType::Mule,
    v827::ActorType::SkeletonHorse,
    v827::ActorType::ZombieHorse,
    v827::ActorType::Zombie,
    v827::ActorType::Creeper,
    v827::ActorType::Skeleton,
    v827::ActorType::Spider,
    v827::ActorType::PigZombie,
    v827::ActorType::Slime,
    v827::ActorType::EnderMan,
    v827::ActorType::Silverfish,
    v827::ActorType::CaveSpider,
    v827::ActorType::Ghast,
    v827::ActorType::LavaSlime,
    v827::ActorType::Blaze,
    v827::ActorType::ZombieVillager,
    v827::ActorType::Witch,
    v827::ActorType::Stray,
    v827::ActorType::Husk,
    v827::ActorType::WitherSkeleton,
    v827::ActorType::Guardian,
    v827::ActorType::ElderGuardian,
    v827::ActorType::Npc,
    v827::ActorType::WitherBoss,
    v827::ActorType::Dragon,
    v827::ActorType::Shulker,
    v827::ActorType::Endermite,
    v827::ActorType::Agent,
    v827::ActorType::Vindicator,
    v827::ActorType::Phantom,
    v827::ActorType::IllagerBeast,
    v827::ActorType::ArmorStand,
    v827::ActorType::TripodCamera,
    v827::ActorType::Player,
    v827::ActorType::ItemEntity,
    v827::ActorType::PrimedTnt,
    v827::ActorType::FallingBlock,
    v827::ActorType::MovingBlock,
    v827::ActorType::ExperiencePotion,
    v827::ActorType::Experience,
    v827::ActorType::EyeOfEnder,
    v827::ActorType::EnderCrystal,
    v827::ActorType::FireworksRocket,
    v827::ActorType::Trident,
    v827::ActorType::Turtle,
    v827::ActorType::Cat,
    v827::ActorType::ShulkerBullet,
    v827::ActorType::FishingHook,
    v827::ActorType::Chalkboard,
    v827::ActorType::DragonFireball,
    v827::ActorType::Arrow,
    v827::ActorType::Snowball,
    v827::ActorType::ThrownEgg,
    v827::ActorType::Painting,
    v827::ActorType::LargeFireball,
    v827::ActorType::ThrownPotion,
    v827::ActorType::Enderpearl,
    v827::ActorType::LeashKnot,
    v827::ActorType::WitherSkull,
    v827::ActorType::BoatRideable,
    v827::ActorType::WitherSkullDangerous,
    v827::ActorType::LightningBolt,
    v827::ActorType::SmallFireball,
    v827::ActorType::AreaEffectCloud,
    v827::ActorType::LingeringPotion,
    v827::ActorType::LlamaSpit,
    v827::ActorType::EvocationFang,
    v827::ActorType::EvocationIllager,
    v827::ActorType::Vex,
    v827::ActorType::MinecartRideable,
    v827::ActorType::MinecartHopper,
    v827::ActorType::MinecartTNT,
    v827::ActorType::MinecartChest,
    v827::ActorType::MinecartFurnace,
    v827::ActorType::MinecartCommandBlock,
    v827::ActorType::IceBomb,
    v827::ActorType::Balloon,
    v827::ActorType::Pufferfish,
    v827::ActorType::Salmon,
    v827::ActorType::Drowned,
    v827::ActorType::Tropicalfish,
    v827::ActorType::Fish,
    v827::ActorType::Panda,
    v827::ActorType::Pillager,
    v827::ActorType::VillagerV2,
    v827::ActorType::ZombieVillagerV2,
    v827::ActorType::Shield,
    v827::ActorType::WanderingTrader,
    v827::ActorType::Lectern,
    v827::ActorType::ElderGuardianGhost,
    v827::ActorType::Fox,
    v827::ActorType::Bee,
    v827::ActorType::Piglin,
    v827::ActorType::Hoglin,
    v827::ActorType::Strider,
    v827::ActorType::Zoglin,
    v827::ActorType::PiglinBrute,
    v827::ActorType::Goat,
    v827::ActorType::GlowSquid,
    v827::ActorType::Axolotl,
    v827::ActorType::Warden,
    v827::ActorType::Frog,
    v827::ActorType::Tadpole,
    v827::ActorType::Allay,
    v827::ActorType::ChestBoatRideable,
    v827::ActorType::TraderLlama,
    v827::ActorType::Camel,
    v827::ActorType::Sniffer,
    v827::ActorType::Breeze,
    v827::ActorType::BreezeWindChargeProjectile,
    v827::ActorType::Armadillo,
    v827::ActorType::WindChargeProjectile,
    v827::ActorType::Bogged,
    v827::ActorType::OminousItemSpawner,
    v827::ActorType::Creaking,
    v827::ActorType::HappyGhast,
    v827::ActorType::CopperGolem,
    v827::ActorType::Nautilus,
    v827::ActorType::ZombieNautilus,
    v827::ActorType::Parched,
    v827::ActorType::CamelHusk,
}};

template <>
inline constexpr std::array<std::string_view, 158> names_v<v827::ActorType>{{
    "undefined",
    "typemask",
    "mob",
    "pathfindermob",
    "monster",
    "animal",
    "tamableanimal",
    "ambient",
    "undeadmonster",
    "zombiemonster",
    "arthropod",
    "minecart",
    "skeletonmonster",
    "equineanimal",
    "projectile",
    "abstractarrow",
    "wateranimal",
    "villagerbase",
    "chicken",
    "cow",
    "pig",
    "sheep",
    "wolf",
    "villager",
    "mushroomcow",
    "squid",
    "rabbit",
    "bat",
    "irongolem",
    "snowgolem",
    "ocelot",
    "horse",
    "polarbear",
    "llama",
    "parrot",
    "dolphin",
    "donkey",
    "mule",
    "skeletonhorse",
    "zombiehorse",
    "zombie",
    "creeper",
    "skeleton",
    "spider",
    "pigzombie",
    "slime",
    "enderman",
    "silverfish",
    "cavespider",
    "ghast",
    "lavaslime",
    "blaze",
    "zombievillager",
    "witch",
    "stray",
    "husk",
    "witherskeleton",
    "guardian",
    "elderguardian",
    "npc",
    "witherboss",
    "dragon",
    "shulker",
    "endermite",
    "agent",
    "vindicator",
    "phantom",
    "illagerbeast",
    "armorstand",
    "tripodcamera",
    "player",
    "itementity",
    "primedtnt",
    "fallingblock",
    "movingblock",
    "experiencepotion",
    "experience",
    "eyeofender",
    "endercrystal",
    "fireworksrocket",
    "trident",
    "turtle",
    "cat",
    "shulkerbullet",
    "fishinghook",
    "chalkboard",
    "dragonfireball",
    "arrow",
    "snowball",
    "thrownegg",
    "painting",
    "largefireball",
    "thrownpotion",
    "enderpearl",
    "leashknot",
    "witherskull",
    "boatrideable",
    "witherskulldangerous",
    "lightningbolt",
    "smallfireball",
    "areaeffectcloud",
    "lingeringpotion",
    "llamaspit",
    "evocationfang",
    "evocationillager",
    "vex",
    "minecartrideable",
    "minecarthopper",
    "minecarttnt",
    "minecartchest",
    "minecartfurnace",
    "minecartcommandblock",
    "icebomb",
    "balloon",
    "pufferfish",
    "salmon",
    "drowned",
    "tropicalfish",
    "fish",
    "panda",
    "pillager",
    "villagerv2",
    "zombievillagerv2",
    "shield",
    "wanderingtrader",
    "lectern",
    "elderguardianghost",
    "fox",
    "bee",
    "piglin",
    "hoglin",
    "strider",
    "zoglin",
    "piglinbrute",
    "goat",
    "glowsquid",
    "axolotl",
    "warden",
    "frog",
    "tadpole",
    "allay",
    "chestboatrideable",
    "traderllama",
    "camel",
    "sniffer",
    "breeze",
    "breezewindchargeprojectile",
    "armadillo",
    "windchargeprojectile",
    "bogged",
    "ominousitemspawner",
    "creaking",
    "happyghast",
    "coppergolem",
    "nautilus",
    "zombienautilus",
    "parched",
    "camelhusk",
}};

template <>
inline constexpr std::string_view type_name_v<v827::ActorType>{"ActorType"};

template <>
inline constexpr std::array<v924::ActorType, 159> values_v<v924::ActorType>{{
    v924::ActorType::Undefined,
    v924::ActorType::TypeMask,
    v924::ActorType::Mob,
    v924::ActorType::PathfinderMob,
    v924::ActorType::Monster,
    v924::ActorType::Animal,
    v924::ActorType::TamableAnimal,
    v924::ActorType::Ambient,
    v924::ActorType::Undead,
    v924::ActorType::UndeadMonster,
    v924::ActorType::ZombieMonster,
    v924::ActorType::Arthropod,
    v924::ActorType::Minecart,
    v924::ActorType::SkeletonMonster,
    v924::ActorType::EquineAnimal,
    v924::ActorType::Projectile,
    v924::ActorType::AbstractArrow,
    v924::ActorType::WaterAnimal,
    v924::ActorType::VillagerBase,
    v924::ActorType::Chicken,
    v924::ActorType::Cow,
    v924::ActorType::Pig,
    v924::ActorType::Sheep,
    v924::ActorType::Wolf,
    v924::ActorType::Villager,
    v924::ActorType::MushroomCow,
    v924::ActorType::Squid,
    v924::ActorType::Rabbit,
    v924::ActorType::Bat,
    v924::ActorType::IronGolem,
    v924::ActorType::SnowGolem,
    v924::ActorType::Ocelot,
    v924::ActorType::Horse,
    v924::ActorType::PolarBear,
    v924::ActorType::Llama,
    v924::ActorType::Parrot,
    v924::ActorType::Dolphin,
    v924::ActorType::Donkey,
    v924::ActorType::Mule,
    v924::ActorType::SkeletonHorse,
    v924::ActorType::ZombieHorse,
    v924::ActorType::Zombie,
    v924::ActorType::Creeper,
    v924::ActorType::Skeleton,
    v924::ActorType::Spider,
    v924::ActorType::PigZombie,
    v924::ActorType::Slime,
    v924::ActorType::EnderMan,
    v924::ActorType::Silverfish,
    v924::ActorType::CaveSpider,
    v924::ActorType::Ghast,
    v924::ActorType::LavaSlime,
    v924::ActorType::Blaze,
    v924::ActorType::ZombieVillager,
    v924::ActorType::Witch,
    v924::ActorType::Stray,
    v924::ActorType::Husk,
    v924::ActorType::WitherSkeleton,
    v924::ActorType::Guardian,
    v924::ActorType::ElderGuardian,
    v924::ActorType::Npc,
    v924::ActorType::WitherBoss,
    v924::ActorType::Dragon,
    v924::ActorType::Shulker,
    v924::ActorType::Endermite,
    v924::ActorType::Agent,
    v924::ActorType::Vindicator,
    v924::ActorType::Phantom,
    v924::ActorType::IllagerBeast,
    v924::ActorType::ArmorStand,
    v924::ActorType::TripodCamera,
    v924::ActorType::Player,
    v924::ActorType::ItemEntity,
    v924::ActorType::PrimedTnt,
    v924::ActorType::FallingBlock,
    v924::ActorType::MovingBlock,
    v924::ActorType::ExperiencePotion,
    v924::ActorType::Experience,
    v924::ActorType::EyeOfEnder,
    v924::ActorType::EnderCrystal,
    v924::ActorType::FireworksRocket,
    v924::ActorType::Trident,
    v924::ActorType::Turtle,
    v924::ActorType::Cat,
    v924::ActorType::ShulkerBullet,
    v924::ActorType::FishingHook,
    v924::ActorType::Chalkboard,
    v924::ActorType::DragonFireball,
    v924::ActorType::Arrow,
    v924::ActorType::Snowball,
    v924::ActorType::ThrownEgg,
    v924::ActorType::Painting,
    v924::ActorType::LargeFireball,
    v924::ActorType::ThrownPotion,
    v924::ActorType::Enderpearl,
    v924::ActorType::LeashKnot,
    v924::ActorType::WitherSkull,
    v924::ActorType::BoatRideable,
    v924::ActorType::WitherSkullDangerous,
    v924::ActorType::LightningBolt,
    v924::ActorType::SmallFireball,
    v924::ActorType::AreaEffectCloud,
    v924::ActorType::LingeringPotion,
    v924::ActorType::LlamaSpit,
    v924::ActorType::EvocationFang,
    v924::ActorType::EvocationIllager,
    v924::ActorType::Vex,
    v924::ActorType::MinecartRideable,
    v924::ActorType::MinecartHopper,
    v924::ActorType::MinecartTNT,
    v924::ActorType::MinecartChest,
    v924::ActorType::MinecartFurnace,
    v924::ActorType::MinecartCommandBlock,
    v924::ActorType::IceBomb,
    v924::ActorType::Balloon,
    v924::ActorType::Pufferfish,
    v924::ActorType::Salmon,
    v924::ActorType::Drowned,
    v924::ActorType::Tropicalfish,
    v924::ActorType::Fish,
    v924::ActorType::Panda,
    v924::ActorType::Pillager,
    v924::ActorType::VillagerV2,
    v924::ActorType::ZombieVillagerV2,
    v924::ActorType::Shield,
    v924::ActorType::WanderingTrader,
    v924::ActorType::Lectern,
    v924::ActorType::ElderGuardianGhost,
    v924::ActorType::Fox,
    v924::ActorType::Bee,
    v924::ActorType::Piglin,
    v924::ActorType::Hoglin,
    v924::ActorType::Strider,
    v924::ActorType::Zoglin,
    v924::ActorType::PiglinBrute,
    v924::ActorType::Goat,
    v924::ActorType::GlowSquid,
    v924::ActorType::Axolotl,
    v924::ActorType::Warden,
    v924::ActorType::Frog,
    v924::ActorType::Tadpole,
    v924::ActorType::Allay,
    v924::ActorType::ChestBoatRideable,
    v924::ActorType::TraderLlama,
    v924::ActorType::Camel,
    v924::ActorType::Sniffer,
    v924::ActorType::Breeze,
    v924::ActorType::BreezeWindChargeProjectile,
    v924::ActorType::Armadillo,
    v924::ActorType::WindChargeProjectile,
    v924::ActorType::Bogged,
    v924::ActorType::OminousItemSpawner,
    v924::ActorType::Creaking,
    v924::ActorType::HappyGhast,
    v924::ActorType::CopperGolem,
    v924::ActorType::Nautilus,
    v924::ActorType::ZombieNautilus,
    v924::ActorType::Parched,
    v924::ActorType::CamelHusk,
}};

template <>
inline constexpr std::array<std::string_view, 159> names_v<v924::ActorType>{{
    "undefined",
    "typemask",
    "mob",
    "pathfindermob",
    "monster",
    "animal",
    "tamableanimal",
    "ambient",
    "undead",
    "undeadmonster",
    "zombiemonster",
    "arthropod",
    "minecart",
    "skeletonmonster",
    "equineanimal",
    "projectile",
    "abstractarrow",
    "wateranimal",
    "villagerbase",
    "chicken",
    "cow",
    "pig",
    "sheep",
    "wolf",
    "villager",
    "mushroomcow",
    "squid",
    "rabbit",
    "bat",
    "irongolem",
    "snowgolem",
    "ocelot",
    "horse",
    "polarbear",
    "llama",
    "parrot",
    "dolphin",
    "donkey",
    "mule",
    "skeletonhorse",
    "zombiehorse",
    "zombie",
    "creeper",
    "skeleton",
    "spider",
    "pigzombie",
    "slime",
    "enderman",
    "silverfish",
    "cavespider",
    "ghast",
    "lavaslime",
    "blaze",
    "zombievillager",
    "witch",
    "stray",
    "husk",
    "witherskeleton",
    "guardian",
    "elderguardian",
    "npc",
    "witherboss",
    "dragon",
    "shulker",
    "endermite",
    "agent",
    "vindicator",
    "phantom",
    "illagerbeast",
    "armorstand",
    "tripodcamera",
    "player",
    "itementity",
    "primedtnt",
    "fallingblock",
    "movingblock",
    "experiencepotion",
    "experience",
    "eyeofender",
    "endercrystal",
    "fireworksrocket",
    "trident",
    "turtle",
    "cat",
    "shulkerbullet",
    "fishinghook",
    "chalkboard",
    "dragonfireball",
    "arrow",
    "snowball",
    "thrownegg",
    "painting",
    "largefireball",
    "thrownpotion",
    "enderpearl",
    "leashknot",
    "witherskull",
    "boatrideable",
    "witherskulldangerous",
    "lightningbolt",
    "smallfireball",
    "areaeffectcloud",
    "lingeringpotion",
    "llamaspit",
    "evocationfang",
    "evocationillager",
    "vex",
    "minecartrideable",
    "minecarthopper",
    "minecarttnt",
    "minecartchest",
    "minecartfurnace",
    "minecartcommandblock",
    "icebomb",
    "balloon",
    "pufferfish",
    "salmon",
    "drowned",
    "tropicalfish",
    "fish",
    "panda",
    "pillager",
    "villagerv2",
    "zombievillagerv2",
    "shield",
    "wanderingtrader",
    "lectern",
    "elderguardianghost",
    "fox",
    "bee",
    "piglin",
    "hoglin",
    "strider",
    "zoglin",
    "piglinbrute",
    "goat",
    "glowsquid",
    "axolotl",
    "warden",
    "frog",
    "tadpole",
    "allay",
    "chestboatrideable",
    "traderllama",
    "camel",
    "sniffer",
    "breeze",
    "breezewindchargeprojectile",
    "armadillo",
    "windchargeprojectile",
    "bogged",
    "ominousitemspawner",
    "creaking",
    "happyghast",
    "coppergolem",
    "nautilus",
    "zombienautilus",
    "parched",
    "camelhusk",
}};

template <>
inline constexpr std::string_view type_name_v<v924::ActorType>{"ActorType"};

template <>
inline constexpr std::array<v975::ActorType, 160> values_v<v975::ActorType>{{
    v975::ActorType::Undefined,
    v975::ActorType::TypeMask,
    v975::ActorType::Mob,
    v975::ActorType::PathfinderMob,
    v975::ActorType::Monster,
    v975::ActorType::Animal,
    v975::ActorType::TamableAnimal,
    v975::ActorType::Ambient,
    v975::ActorType::Undead,
    v975::ActorType::UndeadMonster,
    v975::ActorType::ZombieMonster,
    v975::ActorType::Arthropod,
    v975::ActorType::Minecart,
    v975::ActorType::SkeletonMonster,
    v975::ActorType::EquineAnimal,
    v975::ActorType::Projectile,
    v975::ActorType::AbstractArrow,
    v975::ActorType::WaterAnimal,
    v975::ActorType::VillagerBase,
    v975::ActorType::Chicken,
    v975::ActorType::Cow,
    v975::ActorType::Pig,
    v975::ActorType::Sheep,
    v975::ActorType::Wolf,
    v975::ActorType::Villager,
    v975::ActorType::MushroomCow,
    v975::ActorType::Squid,
    v975::ActorType::Rabbit,
    v975::ActorType::Bat,
    v975::ActorType::IronGolem,
    v975::ActorType::SnowGolem,
    v975::ActorType::Ocelot,
    v975::ActorType::Horse,
    v975::ActorType::PolarBear,
    v975::ActorType::Llama,
    v975::ActorType::Parrot,
    v975::ActorType::Dolphin,
    v975::ActorType::Donkey,
    v975::ActorType::Mule,
    v975::ActorType::SkeletonHorse,
    v975::ActorType::ZombieHorse,
    v975::ActorType::Zombie,
    v975::ActorType::Creeper,
    v975::ActorType::Skeleton,
    v975::ActorType::Spider,
    v975::ActorType::PigZombie,
    v975::ActorType::Slime,
    v975::ActorType::EnderMan,
    v975::ActorType::Silverfish,
    v975::ActorType::CaveSpider,
    v975::ActorType::Ghast,
    v975::ActorType::LavaSlime,
    v975::ActorType::Blaze,
    v975::ActorType::ZombieVillager,
    v975::ActorType::Witch,
    v975::ActorType::Stray,
    v975::ActorType::Husk,
    v975::ActorType::WitherSkeleton,
    v975::ActorType::Guardian,
    v975::ActorType::ElderGuardian,
    v975::ActorType::Npc,
    v975::ActorType::WitherBoss,
    v975::ActorType::Dragon,
    v975::ActorType::Shulker,
    v975::ActorType::Endermite,
    v975::ActorType::Agent,
    v975::ActorType::Vindicator,
    v975::ActorType::Phantom,
    v975::ActorType::IllagerBeast,
    v975::ActorType::ArmorStand,
    v975::ActorType::TripodCamera,
    v975::ActorType::Player,
    v975::ActorType::ItemEntity,
    v975::ActorType::PrimedTnt,
    v975::ActorType::FallingBlock,
    v975::ActorType::MovingBlock,
    v975::ActorType::ExperiencePotion,
    v975::ActorType::Experience,
    v975::ActorType::EyeOfEnder,
    v975::ActorType::EnderCrystal,
    v975::ActorType::FireworksRocket,
    v975::ActorType::Trident,
    v975::ActorType::Turtle,
    v975::ActorType::Cat,
    v975::ActorType::ShulkerBullet,
    v975::ActorType::FishingHook,
    v975::ActorType::Chalkboard,
    v975::ActorType::DragonFireball,
    v975::ActorType::Arrow,
    v975::ActorType::Snowball,
    v975::ActorType::ThrownEgg,
    v975::ActorType::Painting,
    v975::ActorType::LargeFireball,
    v975::ActorType::ThrownPotion,
    v975::ActorType::Enderpearl,
    v975::ActorType::LeashKnot,
    v975::ActorType::WitherSkull,
    v975::ActorType::BoatRideable,
    v975::ActorType::WitherSkullDangerous,
    v975::ActorType::LightningBolt,
    v975::ActorType::SmallFireball,
    v975::ActorType::AreaEffectCloud,
    v975::ActorType::LingeringPotion,
    v975::ActorType::LlamaSpit,
    v975::ActorType::EvocationFang,
    v975::ActorType::EvocationIllager,
    v975::ActorType::Vex,
    v975::ActorType::MinecartRideable,
    v975::ActorType::MinecartHopper,
    v975::ActorType::MinecartTNT,
    v975::ActorType::MinecartChest,
    v975::ActorType::MinecartFurnace,
    v975::ActorType::MinecartCommandBlock,
    v975::ActorType::IceBomb,
    v975::ActorType::Balloon,
    v975::ActorType::Pufferfish,
    v975::ActorType::Salmon,
    v975::ActorType::Drowned,
    v975::ActorType::Tropicalfish,
    v975::ActorType::Fish,
    v975::ActorType::Panda,
    v975::ActorType::Pillager,
    v975::ActorType::VillagerV2,
    v975::ActorType::ZombieVillagerV2,
    v975::ActorType::Shield,
    v975::ActorType::WanderingTrader,
    v975::ActorType::Lectern,
    v975::ActorType::ElderGuardianGhost,
    v975::ActorType::Fox,
    v975::ActorType::Bee,
    v975::ActorType::Piglin,
    v975::ActorType::Hoglin,
    v975::ActorType::Strider,
    v975::ActorType::Zoglin,
    v975::ActorType::PiglinBrute,
    v975::ActorType::Goat,
    v975::ActorType::GlowSquid,
    v975::ActorType::Axolotl,
    v975::ActorType::Warden,
    v975::ActorType::Frog,
    v975::ActorType::Tadpole,
    v975::ActorType::Allay,
    v975::ActorType::ChestBoatRideable,
    v975::ActorType::TraderLlama,
    v975::ActorType::Camel,
    v975::ActorType::Sniffer,
    v975::ActorType::Breeze,
    v975::ActorType::BreezeWindChargeProjectile,
    v975::ActorType::Armadillo,
    v975::ActorType::WindChargeProjectile,
    v975::ActorType::Bogged,
    v975::ActorType::OminousItemSpawner,
    v975::ActorType::Creaking,
    v975::ActorType::HappyGhast,
    v975::ActorType::CopperGolem,
    v975::ActorType::Nautilus,
    v975::ActorType::ZombieNautilus,
    v975::ActorType::Parched,
    v975::ActorType::CamelHusk,
    v975::ActorType::SulfurCube,
}};

template <>
inline constexpr std::array<std::string_view, 160> names_v<v975::ActorType>{{
    "undefined",
    "typemask",
    "mob",
    "pathfindermob",
    "monster",
    "animal",
    "tamableanimal",
    "ambient",
    "undead",
    "undeadmonster",
    "zombiemonster",
    "arthropod",
    "minecart",
    "skeletonmonster",
    "equineanimal",
    "projectile",
    "abstractarrow",
    "wateranimal",
    "villagerbase",
    "chicken",
    "cow",
    "pig",
    "sheep",
    "wolf",
    "villager",
    "mushroomcow",
    "squid",
    "rabbit",
    "bat",
    "irongolem",
    "snowgolem",
    "ocelot",
    "horse",
    "polarbear",
    "llama",
    "parrot",
    "dolphin",
    "donkey",
    "mule",
    "skeletonhorse",
    "zombiehorse",
    "zombie",
    "creeper",
    "skeleton",
    "spider",
    "pigzombie",
    "slime",
    "enderman",
    "silverfish",
    "cavespider",
    "ghast",
    "lavaslime",
    "blaze",
    "zombievillager",
    "witch",
    "stray",
    "husk",
    "witherskeleton",
    "guardian",
    "elderguardian",
    "npc",
    "witherboss",
    "dragon",
    "shulker",
    "endermite",
    "agent",
    "vindicator",
    "phantom",
    "illagerbeast",
    "armorstand",
    "tripodcamera",
    "player",
    "itementity",
    "primedtnt",
    "fallingblock",
    "movingblock",
    "experiencepotion",
    "experience",
    "eyeofender",
    "endercrystal",
    "fireworksrocket",
    "trident",
    "turtle",
    "cat",
    "shulkerbullet",
    "fishinghook",
    "chalkboard",
    "dragonfireball",
    "arrow",
    "snowball",
    "thrownegg",
    "painting",
    "largefireball",
    "thrownpotion",
    "enderpearl",
    "leashknot",
    "witherskull",
    "boatrideable",
    "witherskulldangerous",
    "lightningbolt",
    "smallfireball",
    "areaeffectcloud",
    "lingeringpotion",
    "llamaspit",
    "evocationfang",
    "evocationillager",
    "vex",
    "minecartrideable",
    "minecarthopper",
    "minecarttnt",
    "minecartchest",
    "minecartfurnace",
    "minecartcommandblock",
    "icebomb",
    "balloon",
    "pufferfish",
    "salmon",
    "drowned",
    "tropicalfish",
    "fish",
    "panda",
    "pillager",
    "villagerv2",
    "zombievillagerv2",
    "shield",
    "wanderingtrader",
    "lectern",
    "elderguardianghost",
    "fox",
    "bee",
    "piglin",
    "hoglin",
    "strider",
    "zoglin",
    "piglinbrute",
    "goat",
    "glowsquid",
    "axolotl",
    "warden",
    "frog",
    "tadpole",
    "allay",
    "chestboatrideable",
    "traderllama",
    "camel",
    "sniffer",
    "breeze",
    "breezewindchargeprojectile",
    "armadillo",
    "windchargeprojectile",
    "bogged",
    "ominousitemspawner",
    "creaking",
    "happyghast",
    "coppergolem",
    "nautilus",
    "zombienautilus",
    "parched",
    "camelhusk",
    "sulfurcube",
}};

template <>
inline constexpr std::string_view type_name_v<v975::ActorType>{"ActorType"};

template <>
inline constexpr std::array<v2168::ActorType, 161> values_v<v2168::ActorType>{{
    v2168::ActorType::Undefined,
    v2168::ActorType::TypeMask,
    v2168::ActorType::Mob,
    v2168::ActorType::PathfinderMob,
    v2168::ActorType::Monster,
    v2168::ActorType::Animal,
    v2168::ActorType::TamableAnimal,
    v2168::ActorType::Ambient,
    v2168::ActorType::Undead,
    v2168::ActorType::UndeadMonster,
    v2168::ActorType::ZombieMonster,
    v2168::ActorType::Arthropod,
    v2168::ActorType::Minecart,
    v2168::ActorType::SkeletonMonster,
    v2168::ActorType::EquineAnimal,
    v2168::ActorType::Projectile,
    v2168::ActorType::AbstractArrow,
    v2168::ActorType::WaterAnimal,
    v2168::ActorType::VillagerBase,
    v2168::ActorType::Chicken,
    v2168::ActorType::Cow,
    v2168::ActorType::Pig,
    v2168::ActorType::Sheep,
    v2168::ActorType::Wolf,
    v2168::ActorType::Villager,
    v2168::ActorType::MushroomCow,
    v2168::ActorType::Squid,
    v2168::ActorType::Rabbit,
    v2168::ActorType::Bat,
    v2168::ActorType::IronGolem,
    v2168::ActorType::SnowGolem,
    v2168::ActorType::Ocelot,
    v2168::ActorType::Horse,
    v2168::ActorType::PolarBear,
    v2168::ActorType::Llama,
    v2168::ActorType::Parrot,
    v2168::ActorType::Dolphin,
    v2168::ActorType::Donkey,
    v2168::ActorType::Mule,
    v2168::ActorType::SkeletonHorse,
    v2168::ActorType::ZombieHorse,
    v2168::ActorType::Zombie,
    v2168::ActorType::Creeper,
    v2168::ActorType::Skeleton,
    v2168::ActorType::Spider,
    v2168::ActorType::PigZombie,
    v2168::ActorType::Slime,
    v2168::ActorType::EnderMan,
    v2168::ActorType::Silverfish,
    v2168::ActorType::CaveSpider,
    v2168::ActorType::Ghast,
    v2168::ActorType::LavaSlime,
    v2168::ActorType::Blaze,
    v2168::ActorType::ZombieVillager,
    v2168::ActorType::Witch,
    v2168::ActorType::Stray,
    v2168::ActorType::Husk,
    v2168::ActorType::WitherSkeleton,
    v2168::ActorType::Guardian,
    v2168::ActorType::ElderGuardian,
    v2168::ActorType::Npc,
    v2168::ActorType::WitherBoss,
    v2168::ActorType::Dragon,
    v2168::ActorType::Shulker,
    v2168::ActorType::Endermite,
    v2168::ActorType::Agent,
    v2168::ActorType::Vindicator,
    v2168::ActorType::Phantom,
    v2168::ActorType::IllagerBeast,
    v2168::ActorType::ArmorStand,
    v2168::ActorType::TripodCamera,
    v2168::ActorType::Player,
    v2168::ActorType::ItemEntity,
    v2168::ActorType::PrimedTnt,
    v2168::ActorType::FallingBlock,
    v2168::ActorType::MovingBlock,
    v2168::ActorType::ExperiencePotion,
    v2168::ActorType::Experience,
    v2168::ActorType::EyeOfEnder,
    v2168::ActorType::EnderCrystal,
    v2168::ActorType::FireworksRocket,
    v2168::ActorType::Trident,
    v2168::ActorType::Turtle,
    v2168::ActorType::Cat,
    v2168::ActorType::ShulkerBullet,
    v2168::ActorType::FishingHook,
    v2168::ActorType::Chalkboard,
    v2168::ActorType::DragonFireball,
    v2168::ActorType::Arrow,
    v2168::ActorType::Snowball,
    v2168::ActorType::ThrownEgg,
    v2168::ActorType::Painting,
    v2168::ActorType::LargeFireball,
    v2168::ActorType::ThrownPotion,
    v2168::ActorType::Enderpearl,
    v2168::ActorType::LeashKnot,
    v2168::ActorType::WitherSkull,
    v2168::ActorType::BoatRideable,
    v2168::ActorType::WitherSkullDangerous,
    v2168::ActorType::LightningBolt,
    v2168::ActorType::SmallFireball,
    v2168::ActorType::AreaEffectCloud,
    v2168::ActorType::LingeringPotion,
    v2168::ActorType::LlamaSpit,
    v2168::ActorType::EvocationFang,
    v2168::ActorType::EvocationIllager,
    v2168::ActorType::Vex,
    v2168::ActorType::MinecartRideable,
    v2168::ActorType::MinecartHopper,
    v2168::ActorType::MinecartTNT,
    v2168::ActorType::MinecartChest,
    v2168::ActorType::MinecartFurnace,
    v2168::ActorType::MinecartCommandBlock,
    v2168::ActorType::IceBomb,
    v2168::ActorType::Balloon,
    v2168::ActorType::Pufferfish,
    v2168::ActorType::Salmon,
    v2168::ActorType::Drowned,
    v2168::ActorType::Tropicalfish,
    v2168::ActorType::Fish,
    v2168::ActorType::Panda,
    v2168::ActorType::Pillager,
    v2168::ActorType::VillagerV2,
    v2168::ActorType::ZombieVillagerV2,
    v2168::ActorType::Shield,
    v2168::ActorType::WanderingTrader,
    v2168::ActorType::Lectern,
    v2168::ActorType::ElderGuardianGhost,
    v2168::ActorType::Fox,
    v2168::ActorType::Bee,
    v2168::ActorType::Piglin,
    v2168::ActorType::Hoglin,
    v2168::ActorType::Strider,
    v2168::ActorType::Zoglin,
    v2168::ActorType::PiglinBrute,
    v2168::ActorType::Goat,
    v2168::ActorType::GlowSquid,
    v2168::ActorType::Axolotl,
    v2168::ActorType::Warden,
    v2168::ActorType::Frog,
    v2168::ActorType::Tadpole,
    v2168::ActorType::Allay,
    v2168::ActorType::ChestBoatRideable,
    v2168::ActorType::TraderLlama,
    v2168::ActorType::Camel,
    v2168::ActorType::Sniffer,
    v2168::ActorType::Breeze,
    v2168::ActorType::BreezeWindChargeProjectile,
    v2168::ActorType::Armadillo,
    v2168::ActorType::WindChargeProjectile,
    v2168::ActorType::Bogged,
    v2168::ActorType::OminousItemSpawner,
    v2168::ActorType::Creaking,
    v2168::ActorType::HappyGhast,
    v2168::ActorType::CopperGolem,
    v2168::ActorType::Nautilus,
    v2168::ActorType::ZombieNautilus,
    v2168::ActorType::Parched,
    v2168::ActorType::CamelHusk,
    v2168::ActorType::SulfurCube,
    v2168::ActorType::Cushion,
}};

template <>
inline constexpr std::array<std::string_view, 161> names_v<v2168::ActorType>{{
    "undefined",
    "typemask",
    "mob",
    "pathfindermob",
    "monster",
    "animal",
    "tamableanimal",
    "ambient",
    "undead",
    "undeadmonster",
    "zombiemonster",
    "arthropod",
    "minecart",
    "skeletonmonster",
    "equineanimal",
    "projectile",
    "abstractarrow",
    "wateranimal",
    "villagerbase",
    "chicken",
    "cow",
    "pig",
    "sheep",
    "wolf",
    "villager",
    "mushroomcow",
    "squid",
    "rabbit",
    "bat",
    "irongolem",
    "snowgolem",
    "ocelot",
    "horse",
    "polarbear",
    "llama",
    "parrot",
    "dolphin",
    "donkey",
    "mule",
    "skeletonhorse",
    "zombiehorse",
    "zombie",
    "creeper",
    "skeleton",
    "spider",
    "pigzombie",
    "slime",
    "enderman",
    "silverfish",
    "cavespider",
    "ghast",
    "lavaslime",
    "blaze",
    "zombievillager",
    "witch",
    "stray",
    "husk",
    "witherskeleton",
    "guardian",
    "elderguardian",
    "npc",
    "witherboss",
    "dragon",
    "shulker",
    "endermite",
    "agent",
    "vindicator",
    "phantom",
    "illagerbeast",
    "armorstand",
    "tripodcamera",
    "player",
    "itementity",
    "primedtnt",
    "fallingblock",
    "movingblock",
    "experiencepotion",
    "experience",
    "eyeofender",
    "endercrystal",
    "fireworksrocket",
    "trident",
    "turtle",
    "cat",
    "shulkerbullet",
    "fishinghook",
    "chalkboard",
    "dragonfireball",
    "arrow",
    "snowball",
    "thrownegg",
    "painting",
    "largefireball",
    "thrownpotion",
    "enderpearl",
    "leashknot",
    "witherskull",
    "boatrideable",
    "witherskulldangerous",
    "lightningbolt",
    "smallfireball",
    "areaeffectcloud",
    "lingeringpotion",
    "llamaspit",
    "evocationfang",
    "evocationillager",
    "vex",
    "minecartrideable",
    "minecarthopper",
    "minecarttnt",
    "minecartchest",
    "minecartfurnace",
    "minecartcommandblock",
    "icebomb",
    "balloon",
    "pufferfish",
    "salmon",
    "drowned",
    "tropicalfish",
    "fish",
    "panda",
    "pillager",
    "villagerv2",
    "zombievillagerv2",
    "shield",
    "wanderingtrader",
    "lectern",
    "elderguardianghost",
    "fox",
    "bee",
    "piglin",
    "hoglin",
    "strider",
    "zoglin",
    "piglinbrute",
    "goat",
    "glowsquid",
    "axolotl",
    "warden",
    "frog",
    "tadpole",
    "allay",
    "chestboatrideable",
    "traderllama",
    "camel",
    "sniffer",
    "breeze",
    "breezewindchargeprojectile",
    "armadillo",
    "windchargeprojectile",
    "bogged",
    "ominousitemspawner",
    "creaking",
    "happyghast",
    "coppergolem",
    "nautilus",
    "zombienautilus",
    "parched",
    "camelhusk",
    "sulfurcube",
    "cushion",
}};

template <>
inline constexpr std::string_view type_name_v<v2168::ActorType>{"ActorType"};

template <>
inline constexpr std::array<v2225::ActorType, 163> values_v<v2225::ActorType>{{
    v2225::ActorType::Undefined,
    v2225::ActorType::TypeMask,
    v2225::ActorType::Mob,
    v2225::ActorType::PathfinderMob,
    v2225::ActorType::Monster,
    v2225::ActorType::Animal,
    v2225::ActorType::TamableAnimal,
    v2225::ActorType::Ambient,
    v2225::ActorType::Undead,
    v2225::ActorType::UndeadMonster,
    v2225::ActorType::ZombieMonster,
    v2225::ActorType::Arthropod,
    v2225::ActorType::Minecart,
    v2225::ActorType::SkeletonMonster,
    v2225::ActorType::EquineAnimal,
    v2225::ActorType::Projectile,
    v2225::ActorType::AbstractArrow,
    v2225::ActorType::WaterAnimal,
    v2225::ActorType::VillagerBase,
    v2225::ActorType::Chicken,
    v2225::ActorType::Cow,
    v2225::ActorType::Pig,
    v2225::ActorType::Sheep,
    v2225::ActorType::Wolf,
    v2225::ActorType::Villager,
    v2225::ActorType::MushroomCow,
    v2225::ActorType::Squid,
    v2225::ActorType::Rabbit,
    v2225::ActorType::Bat,
    v2225::ActorType::IronGolem,
    v2225::ActorType::SnowGolem,
    v2225::ActorType::Ocelot,
    v2225::ActorType::Horse,
    v2225::ActorType::PolarBear,
    v2225::ActorType::Llama,
    v2225::ActorType::Parrot,
    v2225::ActorType::Dolphin,
    v2225::ActorType::Donkey,
    v2225::ActorType::Mule,
    v2225::ActorType::SkeletonHorse,
    v2225::ActorType::ZombieHorse,
    v2225::ActorType::Zombie,
    v2225::ActorType::Creeper,
    v2225::ActorType::Skeleton,
    v2225::ActorType::Spider,
    v2225::ActorType::PigZombie,
    v2225::ActorType::Slime,
    v2225::ActorType::EnderMan,
    v2225::ActorType::Silverfish,
    v2225::ActorType::CaveSpider,
    v2225::ActorType::Ghast,
    v2225::ActorType::LavaSlime,
    v2225::ActorType::Blaze,
    v2225::ActorType::ZombieVillager,
    v2225::ActorType::Witch,
    v2225::ActorType::Stray,
    v2225::ActorType::Husk,
    v2225::ActorType::WitherSkeleton,
    v2225::ActorType::Guardian,
    v2225::ActorType::ElderGuardian,
    v2225::ActorType::Npc,
    v2225::ActorType::WitherBoss,
    v2225::ActorType::Dragon,
    v2225::ActorType::Shulker,
    v2225::ActorType::Endermite,
    v2225::ActorType::Agent,
    v2225::ActorType::Vindicator,
    v2225::ActorType::Phantom,
    v2225::ActorType::IllagerBeast,
    v2225::ActorType::ArmorStand,
    v2225::ActorType::TripodCamera,
    v2225::ActorType::Player,
    v2225::ActorType::ItemEntity,
    v2225::ActorType::PrimedTnt,
    v2225::ActorType::FallingBlock,
    v2225::ActorType::MovingBlock,
    v2225::ActorType::ExperiencePotion,
    v2225::ActorType::Experience,
    v2225::ActorType::EyeOfEnder,
    v2225::ActorType::EnderCrystal,
    v2225::ActorType::FireworksRocket,
    v2225::ActorType::Trident,
    v2225::ActorType::Turtle,
    v2225::ActorType::Cat,
    v2225::ActorType::ShulkerBullet,
    v2225::ActorType::FishingHook,
    v2225::ActorType::Chalkboard,
    v2225::ActorType::DragonFireball,
    v2225::ActorType::Arrow,
    v2225::ActorType::Snowball,
    v2225::ActorType::ThrownEgg,
    v2225::ActorType::Painting,
    v2225::ActorType::LargeFireball,
    v2225::ActorType::ThrownPotion,
    v2225::ActorType::Enderpearl,
    v2225::ActorType::LeashKnot,
    v2225::ActorType::WitherSkull,
    v2225::ActorType::BoatRideable,
    v2225::ActorType::WitherSkullDangerous,
    v2225::ActorType::LightningBolt,
    v2225::ActorType::SmallFireball,
    v2225::ActorType::AreaEffectCloud,
    v2225::ActorType::LingeringPotion,
    v2225::ActorType::LlamaSpit,
    v2225::ActorType::EvocationFang,
    v2225::ActorType::EvocationIllager,
    v2225::ActorType::Vex,
    v2225::ActorType::MinecartRideable,
    v2225::ActorType::MinecartHopper,
    v2225::ActorType::MinecartTNT,
    v2225::ActorType::MinecartChest,
    v2225::ActorType::MinecartFurnace,
    v2225::ActorType::MinecartCommandBlock,
    v2225::ActorType::IceBomb,
    v2225::ActorType::Balloon,
    v2225::ActorType::Pufferfish,
    v2225::ActorType::Salmon,
    v2225::ActorType::Drowned,
    v2225::ActorType::Tropicalfish,
    v2225::ActorType::Fish,
    v2225::ActorType::Panda,
    v2225::ActorType::Pillager,
    v2225::ActorType::VillagerV2,
    v2225::ActorType::ZombieVillagerV2,
    v2225::ActorType::Shield,
    v2225::ActorType::WanderingTrader,
    v2225::ActorType::Lectern,
    v2225::ActorType::ElderGuardianGhost,
    v2225::ActorType::Fox,
    v2225::ActorType::Bee,
    v2225::ActorType::Piglin,
    v2225::ActorType::Hoglin,
    v2225::ActorType::Strider,
    v2225::ActorType::Zoglin,
    v2225::ActorType::PiglinBrute,
    v2225::ActorType::Goat,
    v2225::ActorType::GlowSquid,
    v2225::ActorType::Axolotl,
    v2225::ActorType::Warden,
    v2225::ActorType::Frog,
    v2225::ActorType::Tadpole,
    v2225::ActorType::Allay,
    v2225::ActorType::ChestBoatRideable,
    v2225::ActorType::TraderLlama,
    v2225::ActorType::Camel,
    v2225::ActorType::Sniffer,
    v2225::ActorType::Breeze,
    v2225::ActorType::BreezeWindChargeProjectile,
    v2225::ActorType::Armadillo,
    v2225::ActorType::WindChargeProjectile,
    v2225::ActorType::Bogged,
    v2225::ActorType::OminousItemSpawner,
    v2225::ActorType::Creaking,
    v2225::ActorType::HappyGhast,
    v2225::ActorType::CopperGolem,
    v2225::ActorType::Nautilus,
    v2225::ActorType::ZombieNautilus,
    v2225::ActorType::Parched,
    v2225::ActorType::CamelHusk,
    v2225::ActorType::SulfurCube,
    v2225::ActorType::Cushion,
    v2225::ActorType::Frostbite,
    v2225::ActorType::IceBall,
}};

template <>
inline constexpr std::array<std::string_view, 163> names_v<v2225::ActorType>{{
    "undefined",
    "typemask",
    "mob",
    "pathfindermob",
    "monster",
    "animal",
    "tamableanimal",
    "ambient",
    "undead",
    "undeadmonster",
    "zombiemonster",
    "arthropod",
    "minecart",
    "skeletonmonster",
    "equineanimal",
    "projectile",
    "abstractarrow",
    "wateranimal",
    "villagerbase",
    "chicken",
    "cow",
    "pig",
    "sheep",
    "wolf",
    "villager",
    "mushroomcow",
    "squid",
    "rabbit",
    "bat",
    "irongolem",
    "snowgolem",
    "ocelot",
    "horse",
    "polarbear",
    "llama",
    "parrot",
    "dolphin",
    "donkey",
    "mule",
    "skeletonhorse",
    "zombiehorse",
    "zombie",
    "creeper",
    "skeleton",
    "spider",
    "pigzombie",
    "slime",
    "enderman",
    "silverfish",
    "cavespider",
    "ghast",
    "lavaslime",
    "blaze",
    "zombievillager",
    "witch",
    "stray",
    "husk",
    "witherskeleton",
    "guardian",
    "elderguardian",
    "npc",
    "witherboss",
    "dragon",
    "shulker",
    "endermite",
    "agent",
    "vindicator",
    "phantom",
    "illagerbeast",
    "armorstand",
    "tripodcamera",
    "player",
    "itementity",
    "primedtnt",
    "fallingblock",
    "movingblock",
    "experiencepotion",
    "experience",
    "eyeofender",
    "endercrystal",
    "fireworksrocket",
    "trident",
    "turtle",
    "cat",
    "shulkerbullet",
    "fishinghook",
    "chalkboard",
    "dragonfireball",
    "arrow",
    "snowball",
    "thrownegg",
    "painting",
    "largefireball",
    "thrownpotion",
    "enderpearl",
    "leashknot",
    "witherskull",
    "boatrideable",
    "witherskulldangerous",
    "lightningbolt",
    "smallfireball",
    "areaeffectcloud",
    "lingeringpotion",
    "llamaspit",
    "evocationfang",
    "evocationillager",
    "vex",
    "minecartrideable",
    "minecarthopper",
    "minecarttnt",
    "minecartchest",
    "minecartfurnace",
    "minecartcommandblock",
    "icebomb",
    "balloon",
    "pufferfish",
    "salmon",
    "drowned",
    "tropicalfish",
    "fish",
    "panda",
    "pillager",
    "villagerv2",
    "zombievillagerv2",
    "shield",
    "wanderingtrader",
    "lectern",
    "elderguardianghost",
    "fox",
    "bee",
    "piglin",
    "hoglin",
    "strider",
    "zoglin",
    "piglinbrute",
    "goat",
    "glowsquid",
    "axolotl",
    "warden",
    "frog",
    "tadpole",
    "allay",
    "chestboatrideable",
    "traderllama",
    "camel",
    "sniffer",
    "breeze",
    "breezewindchargeprojectile",
    "armadillo",
    "windchargeprojectile",
    "bogged",
    "ominousitemspawner",
    "creaking",
    "happyghast",
    "coppergolem",
    "nautilus",
    "zombienautilus",
    "parched",
    "camelhusk",
    "sulfurcube",
    "cushion",
    "frostbite",
    "iceball",
}};

template <>
inline constexpr std::string_view type_name_v<v2225::ActorType>{"ActorType"};

template <>
inline constexpr std::array<base::ActorEvent, 58> values_v<base::ActorEvent>{{
    base::ActorEvent::None,
    base::ActorEvent::Jump,
    base::ActorEvent::Hurt,
    base::ActorEvent::Death,
    base::ActorEvent::StartAttacking,
    base::ActorEvent::StopAttacking,
    base::ActorEvent::TamingFailed,
    base::ActorEvent::TamingSucceeded,
    base::ActorEvent::ShakeWetness,
    base::ActorEvent::EatGrass,
    base::ActorEvent::FishhookBubble,
    base::ActorEvent::FishhookFishpos,
    base::ActorEvent::FishhookHooktime,
    base::ActorEvent::FishhookTease,
    base::ActorEvent::SquidFleeing,
    base::ActorEvent::ZombieConverting,
    base::ActorEvent::PlayAmbient,
    base::ActorEvent::SpawnAlive,
    base::ActorEvent::StartOfferFlower,
    base::ActorEvent::StopOfferFlower,
    base::ActorEvent::LoveHearts,
    base::ActorEvent::VillagerAngry,
    base::ActorEvent::VillagerHappy,
    base::ActorEvent::WitchHatMagic,
    base::ActorEvent::FireworksExplode,
    base::ActorEvent::InLoveHearts,
    base::ActorEvent::SilverfishMergeAnim,
    base::ActorEvent::GuardianAttackSound,
    base::ActorEvent::DrinkPotion,
    base::ActorEvent::ThrowPotion,
    base::ActorEvent::PrimeTntcart,
    base::ActorEvent::PrimeCreeper,
    base::ActorEvent::AirSupply,
    base::ActorEvent::DeprecatedAddPlayerLevels,
    base::ActorEvent::GuardianMiningFatigue,
    base::ActorEvent::AgentSwingArm,
    base::ActorEvent::DragonStartDeathAnim,
    base::ActorEvent::GroundDust,
    base::ActorEvent::Shake,
    base::ActorEvent::Feed,
    base::ActorEvent::BabyAge,
    base::ActorEvent::InstantDeath,
    base::ActorEvent::NotifyTrade,
    base::ActorEvent::LeashDestroyed,
    base::ActorEvent::CaravanUpdated,
    base::ActorEvent::TalismanActivate,
    base::ActorEvent::DeprecatedUpdateStructureFeature,
    base::ActorEvent::PlayerSpawnedMob,
    base::ActorEvent::Puke,
    base::ActorEvent::UpdateStackSize,
    base::ActorEvent::StartSwimming,
    base::ActorEvent::BalloonPop,
    base::ActorEvent::TreasureHunt,
    base::ActorEvent::SummonAgent,
    base::ActorEvent::FinishedChargingItem,
    base::ActorEvent::ActorGrowUp,
    base::ActorEvent::VibrationDetected,
    base::ActorEvent::DrinkMilk,
}};

template <>
inline constexpr std::array<std::string_view, 58> names_v<base::ActorEvent>{{
    "none",
    "jump",
    "hurt",
    "death",
    "startattacking",
    "stopattacking",
    "tamingfailed",
    "tamingsucceeded",
    "shakewetness",
    "eatgrass",
    "fishhookbubble",
    "fishhookfishpos",
    "fishhookhooktime",
    "fishhooktease",
    "squidfleeing",
    "zombieconverting",
    "playambient",
    "spawnalive",
    "startofferflower",
    "stopofferflower",
    "lovehearts",
    "villagerangry",
    "villagerhappy",
    "witchhatmagic",
    "fireworksexplode",
    "inlovehearts",
    "silverfishmergeanim",
    "guardianattacksound",
    "drinkpotion",
    "throwpotion",
    "primetntcart",
    "primecreeper",
    "airsupply",
    "deprecatedaddplayerlevels",
    "guardianminingfatigue",
    "agentswingarm",
    "dragonstartdeathanim",
    "grounddust",
    "shake",
    "feed",
    "babyage",
    "instantdeath",
    "notifytrade",
    "leashdestroyed",
    "caravanupdated",
    "talismanactivate",
    "deprecatedupdatestructurefeature",
    "playerspawnedmob",
    "puke",
    "updatestacksize",
    "startswimming",
    "balloonpop",
    "treasurehunt",
    "summonagent",
    "finishedchargingitem",
    "actorgrowup",
    "vibrationdetected",
    "drinkmilk",
}};

template <>
inline constexpr std::string_view type_name_v<base::ActorEvent>{"ActorEvent"};

template <>
inline constexpr std::array<v859::ActorEvent, 59> values_v<v859::ActorEvent>{{
    v859::ActorEvent::None,
    v859::ActorEvent::Jump,
    v859::ActorEvent::Hurt,
    v859::ActorEvent::Death,
    v859::ActorEvent::StartAttacking,
    v859::ActorEvent::StopAttacking,
    v859::ActorEvent::TamingFailed,
    v859::ActorEvent::TamingSucceeded,
    v859::ActorEvent::ShakeWetness,
    v859::ActorEvent::EatGrass,
    v859::ActorEvent::FishhookBubble,
    v859::ActorEvent::FishhookFishpos,
    v859::ActorEvent::FishhookHooktime,
    v859::ActorEvent::FishhookTease,
    v859::ActorEvent::SquidFleeing,
    v859::ActorEvent::ZombieConverting,
    v859::ActorEvent::PlayAmbient,
    v859::ActorEvent::SpawnAlive,
    v859::ActorEvent::StartOfferFlower,
    v859::ActorEvent::StopOfferFlower,
    v859::ActorEvent::LoveHearts,
    v859::ActorEvent::VillagerAngry,
    v859::ActorEvent::VillagerHappy,
    v859::ActorEvent::WitchHatMagic,
    v859::ActorEvent::FireworksExplode,
    v859::ActorEvent::InLoveHearts,
    v859::ActorEvent::SilverfishMergeAnim,
    v859::ActorEvent::GuardianAttackSound,
    v859::ActorEvent::DrinkPotion,
    v859::ActorEvent::ThrowPotion,
    v859::ActorEvent::PrimeTntcart,
    v859::ActorEvent::PrimeCreeper,
    v859::ActorEvent::AirSupply,
    v859::ActorEvent::DeprecatedAddPlayerLevels,
    v859::ActorEvent::GuardianMiningFatigue,
    v859::ActorEvent::AgentSwingArm,
    v859::ActorEvent::DragonStartDeathAnim,
    v859::ActorEvent::GroundDust,
    v859::ActorEvent::Shake,
    v859::ActorEvent::Feed,
    v859::ActorEvent::BabyAge,
    v859::ActorEvent::InstantDeath,
    v859::ActorEvent::NotifyTrade,
    v859::ActorEvent::LeashDestroyed,
    v859::ActorEvent::CaravanUpdated,
    v859::ActorEvent::TalismanActivate,
    v859::ActorEvent::DeprecatedUpdateStructureFeature,
    v859::ActorEvent::PlayerSpawnedMob,
    v859::ActorEvent::Puke,
    v859::ActorEvent::UpdateStackSize,
    v859::ActorEvent::StartSwimming,
    v859::ActorEvent::BalloonPop,
    v859::ActorEvent::TreasureHunt,
    v859::ActorEvent::SummonAgent,
    v859::ActorEvent::FinishedChargingItem,
    v859::ActorEvent::ActorGrowUp,
    v859::ActorEvent::VibrationDetected,
    v859::ActorEvent::DrinkMilk,
    v859::ActorEvent::ShakeWetnessStop,
}};

template <>
inline constexpr std::array<std::string_view, 59> names_v<v859::ActorEvent>{{
    "none",
    "jump",
    "hurt",
    "death",
    "startattacking",
    "stopattacking",
    "tamingfailed",
    "tamingsucceeded",
    "shakewetness",
    "eatgrass",
    "fishhookbubble",
    "fishhookfishpos",
    "fishhookhooktime",
    "fishhooktease",
    "squidfleeing",
    "zombieconverting",
    "playambient",
    "spawnalive",
    "startofferflower",
    "stopofferflower",
    "lovehearts",
    "villagerangry",
    "villagerhappy",
    "witchhatmagic",
    "fireworksexplode",
    "inlovehearts",
    "silverfishmergeanim",
    "guardianattacksound",
    "drinkpotion",
    "throwpotion",
    "primetntcart",
    "primecreeper",
    "airsupply",
    "deprecatedaddplayerlevels",
    "guardianminingfatigue",
    "agentswingarm",
    "dragonstartdeathanim",
    "grounddust",
    "shake",
    "feed",
    "babyage",
    "instantdeath",
    "notifytrade",
    "leashdestroyed",
    "caravanupdated",
    "talismanactivate",
    "deprecatedupdatestructurefeature",
    "playerspawnedmob",
    "puke",
    "updatestacksize",
    "startswimming",
    "balloonpop",
    "treasurehunt",
    "summonagent",
    "finishedchargingitem",
    "actorgrowup",
    "vibrationdetected",
    "drinkmilk",
    "shakewetnessstop",
}};

template <>
inline constexpr std::string_view type_name_v<v859::ActorEvent>{"ActorEvent"};

template <>
inline constexpr std::array<v898::ActorEvent, 60> values_v<v898::ActorEvent>{{
    v898::ActorEvent::None,
    v898::ActorEvent::Jump,
    v898::ActorEvent::Hurt,
    v898::ActorEvent::Death,
    v898::ActorEvent::StartAttacking,
    v898::ActorEvent::StopAttacking,
    v898::ActorEvent::TamingFailed,
    v898::ActorEvent::TamingSucceeded,
    v898::ActorEvent::ShakeWetness,
    v898::ActorEvent::EatGrass,
    v898::ActorEvent::FishhookBubble,
    v898::ActorEvent::FishhookFishpos,
    v898::ActorEvent::FishhookHooktime,
    v898::ActorEvent::FishhookTease,
    v898::ActorEvent::SquidFleeing,
    v898::ActorEvent::ZombieConverting,
    v898::ActorEvent::PlayAmbient,
    v898::ActorEvent::SpawnAlive,
    v898::ActorEvent::StartOfferFlower,
    v898::ActorEvent::StopOfferFlower,
    v898::ActorEvent::LoveHearts,
    v898::ActorEvent::VillagerAngry,
    v898::ActorEvent::VillagerHappy,
    v898::ActorEvent::WitchHatMagic,
    v898::ActorEvent::FireworksExplode,
    v898::ActorEvent::InLoveHearts,
    v898::ActorEvent::SilverfishMergeAnim,
    v898::ActorEvent::GuardianAttackSound,
    v898::ActorEvent::DrinkPotion,
    v898::ActorEvent::ThrowPotion,
    v898::ActorEvent::PrimeTntcart,
    v898::ActorEvent::PrimeCreeper,
    v898::ActorEvent::AirSupply,
    v898::ActorEvent::DeprecatedAddPlayerLevels,
    v898::ActorEvent::GuardianMiningFatigue,
    v898::ActorEvent::AgentSwingArm,
    v898::ActorEvent::DragonStartDeathAnim,
    v898::ActorEvent::GroundDust,
    v898::ActorEvent::Shake,
    v898::ActorEvent::Feed,
    v898::ActorEvent::BabyAge,
    v898::ActorEvent::InstantDeath,
    v898::ActorEvent::NotifyTrade,
    v898::ActorEvent::LeashDestroyed,
    v898::ActorEvent::CaravanUpdated,
    v898::ActorEvent::TalismanActivate,
    v898::ActorEvent::DeprecatedUpdateStructureFeature,
    v898::ActorEvent::PlayerSpawnedMob,
    v898::ActorEvent::Puke,
    v898::ActorEvent::UpdateStackSize,
    v898::ActorEvent::StartSwimming,
    v898::ActorEvent::BalloonPop,
    v898::ActorEvent::TreasureHunt,
    v898::ActorEvent::SummonAgent,
    v898::ActorEvent::FinishedChargingItem,
    v898::ActorEvent::ActorGrowUp,
    v898::ActorEvent::VibrationDetected,
    v898::ActorEvent::DrinkMilk,
    v898::ActorEvent::ShakeWetnessStop,
    v898::ActorEvent::KineticDamageDealt,
}};

template <>
inline constexpr std::array<std::string_view, 60> names_v<v898::ActorEvent>{{
    "none",
    "jump",
    "hurt",
    "death",
    "startattacking",
    "stopattacking",
    "tamingfailed",
    "tamingsucceeded",
    "shakewetness",
    "eatgrass",
    "fishhookbubble",
    "fishhookfishpos",
    "fishhookhooktime",
    "fishhooktease",
    "squidfleeing",
    "zombieconverting",
    "playambient",
    "spawnalive",
    "startofferflower",
    "stopofferflower",
    "lovehearts",
    "villagerangry",
    "villagerhappy",
    "witchhatmagic",
    "fireworksexplode",
    "inlovehearts",
    "silverfishmergeanim",
    "guardianattacksound",
    "drinkpotion",
    "throwpotion",
    "primetntcart",
    "primecreeper",
    "airsupply",
    "deprecatedaddplayerlevels",
    "guardianminingfatigue",
    "agentswingarm",
    "dragonstartdeathanim",
    "grounddust",
    "shake",
    "feed",
    "babyage",
    "instantdeath",
    "notifytrade",
    "leashdestroyed",
    "caravanupdated",
    "talismanactivate",
    "deprecatedupdatestructurefeature",
    "playerspawnedmob",
    "puke",
    "updatestacksize",
    "startswimming",
    "balloonpop",
    "treasurehunt",
    "summonagent",
    "finishedchargingitem",
    "actorgrowup",
    "vibrationdetected",
    "drinkmilk",
    "shakewetnessstop",
    "kineticdamagedealt",
}};

template <>
inline constexpr std::string_view type_name_v<v898::ActorEvent>{"ActorEvent"};

template <>
inline constexpr std::array<v975::ActorEvent, 61> values_v<v975::ActorEvent>{{
    v975::ActorEvent::None,
    v975::ActorEvent::Jump,
    v975::ActorEvent::Hurt,
    v975::ActorEvent::Death,
    v975::ActorEvent::StartAttacking,
    v975::ActorEvent::StopAttacking,
    v975::ActorEvent::TamingFailed,
    v975::ActorEvent::TamingSucceeded,
    v975::ActorEvent::ShakeWetness,
    v975::ActorEvent::EatGrass,
    v975::ActorEvent::FishhookBubble,
    v975::ActorEvent::FishhookFishpos,
    v975::ActorEvent::FishhookHooktime,
    v975::ActorEvent::FishhookTease,
    v975::ActorEvent::SquidFleeing,
    v975::ActorEvent::ZombieConverting,
    v975::ActorEvent::PlayAmbient,
    v975::ActorEvent::SpawnAlive,
    v975::ActorEvent::StartOfferFlower,
    v975::ActorEvent::StopOfferFlower,
    v975::ActorEvent::LoveHearts,
    v975::ActorEvent::VillagerAngry,
    v975::ActorEvent::VillagerHappy,
    v975::ActorEvent::WitchHatMagic,
    v975::ActorEvent::FireworksExplode,
    v975::ActorEvent::InLoveHearts,
    v975::ActorEvent::SilverfishMergeAnim,
    v975::ActorEvent::GuardianAttackSound,
    v975::ActorEvent::DrinkPotion,
    v975::ActorEvent::ThrowPotion,
    v975::ActorEvent::PrimeTntcart,
    v975::ActorEvent::PrimeCreeper,
    v975::ActorEvent::AirSupply,
    v975::ActorEvent::DeprecatedAddPlayerLevels,
    v975::ActorEvent::GuardianMiningFatigue,
    v975::ActorEvent::AgentSwingArm,
    v975::ActorEvent::DragonStartDeathAnim,
    v975::ActorEvent::GroundDust,
    v975::ActorEvent::Shake,
    v975::ActorEvent::Feed,
    v975::ActorEvent::BabyAge,
    v975::ActorEvent::InstantDeath,
    v975::ActorEvent::NotifyTrade,
    v975::ActorEvent::LeashDestroyed,
    v975::ActorEvent::CaravanUpdated,
    v975::ActorEvent::TalismanActivate,
    v975::ActorEvent::DeprecatedUpdateStructureFeature,
    v975::ActorEvent::PlayerSpawnedMob,
    v975::ActorEvent::Puke,
    v975::ActorEvent::UpdateStackSize,
    v975::ActorEvent::StartSwimming,
    v975::ActorEvent::BalloonPop,
    v975::ActorEvent::TreasureHunt,
    v975::ActorEvent::SummonAgent,
    v975::ActorEvent::FinishedChargingItem,
    v975::ActorEvent::ActorGrowUp,
    v975::ActorEvent::VibrationDetected,
    v975::ActorEvent::DrinkMilk,
    v975::ActorEvent::ShakeWetnessStop,
    v975::ActorEvent::KineticDamageDealt,
    v975::ActorEvent::HurtWithoutReceivingDamage,
}};

template <>
inline constexpr std::array<std::string_view, 61> names_v<v975::ActorEvent>{{
    "none",
    "jump",
    "hurt",
    "death",
    "startattacking",
    "stopattacking",
    "tamingfailed",
    "tamingsucceeded",
    "shakewetness",
    "eatgrass",
    "fishhookbubble",
    "fishhookfishpos",
    "fishhookhooktime",
    "fishhooktease",
    "squidfleeing",
    "zombieconverting",
    "playambient",
    "spawnalive",
    "startofferflower",
    "stopofferflower",
    "lovehearts",
    "villagerangry",
    "villagerhappy",
    "witchhatmagic",
    "fireworksexplode",
    "inlovehearts",
    "silverfishmergeanim",
    "guardianattacksound",
    "drinkpotion",
    "throwpotion",
    "primetntcart",
    "primecreeper",
    "airsupply",
    "deprecatedaddplayerlevels",
    "guardianminingfatigue",
    "agentswingarm",
    "dragonstartdeathanim",
    "grounddust",
    "shake",
    "feed",
    "babyage",
    "instantdeath",
    "notifytrade",
    "leashdestroyed",
    "caravanupdated",
    "talismanactivate",
    "deprecatedupdatestructurefeature",
    "playerspawnedmob",
    "puke",
    "updatestacksize",
    "startswimming",
    "balloonpop",
    "treasurehunt",
    "summonagent",
    "finishedchargingitem",
    "actorgrowup",
    "vibrationdetected",
    "drinkmilk",
    "shakewetnessstop",
    "kineticdamagedealt",
    "hurtwithoutreceivingdamage",
}};

template <>
inline constexpr std::string_view type_name_v<v975::ActorEvent>{"ActorEvent"};

template <>
inline constexpr std::array<ActorSwingSource, 9> values_v<ActorSwingSource>{{
    ActorSwingSource::None,
    ActorSwingSource::Build,
    ActorSwingSource::Mine,
    ActorSwingSource::Interact,
    ActorSwingSource::Attack,
    ActorSwingSource::UseItem,
    ActorSwingSource::ThrowItem,
    ActorSwingSource::DropItem,
    ActorSwingSource::Event,
}};

template <>
inline constexpr std::array<std::string_view, 9> names_v<ActorSwingSource>{{
    "none",
    "build",
    "mine",
    "interact",
    "attack",
    "useitem",
    "throwitem",
    "dropitem",
    "event",
}};

template <>
inline constexpr std::string_view type_name_v<ActorSwingSource>{"ActorSwingSource"};

template <>
inline constexpr std::array<base::AnimatePacket::Action, 7> values_v<base::AnimatePacket::Action>{{
    base::AnimatePacket::Action::NoAction,
    base::AnimatePacket::Action::Swing,
    base::AnimatePacket::Action::WakeUp,
    base::AnimatePacket::Action::CriticalHit,
    base::AnimatePacket::Action::MagicCriticalHit,
    base::AnimatePacket::Action::RowRight,
    base::AnimatePacket::Action::RowLeft,
}};

template <>
inline constexpr std::array<std::string_view, 7> names_v<base::AnimatePacket::Action>{{
    "noaction",
    "swing",
    "wakeup",
    "criticalhit",
    "magiccriticalhit",
    "rowright",
    "rowleft",
}};

template <>
inline constexpr std::string_view type_name_v<base::AnimatePacket::Action>{"AnimatePacket::Action"};

template <>
inline constexpr std::array<v800::AnimatePacket::Action, 5> values_v<v800::AnimatePacket::Action>{{
    v800::AnimatePacket::Action::NoAction,
    v800::AnimatePacket::Action::Swing,
    v800::AnimatePacket::Action::WakeUp,
    v800::AnimatePacket::Action::CriticalHit,
    v800::AnimatePacket::Action::MagicCriticalHit,
}};

template <>
inline constexpr std::array<std::string_view, 5> names_v<v800::AnimatePacket::Action>{{
    "noaction",
    "swing",
    "wakeup",
    "criticalhit",
    "magiccriticalhit",
}};

template <>
inline constexpr std::string_view type_name_v<v800::AnimatePacket::Action>{"AnimatePacket::Action"};

template <>
inline constexpr std::array<v859::AnimatePacket::Action, 5> values_v<v859::AnimatePacket::Action>{{
    v859::AnimatePacket::Action::NoAction,
    v859::AnimatePacket::Action::Swing,
    v859::AnimatePacket::Action::WakeUp,
    v859::AnimatePacket::Action::CriticalHit,
    v859::AnimatePacket::Action::MagicCriticalHit,
}};

template <>
inline constexpr std::array<std::string_view, 5> names_v<v859::AnimatePacket::Action>{{
    "noaction",
    "swing",
    "wakeup",
    "criticalhit",
    "magiccriticalhit",
}};

template <>
inline constexpr std::string_view type_name_v<v859::AnimatePacket::Action>{"AnimatePacket::Action"};

template <>
inline constexpr std::array<v898::AnimatePacket::Action, 5> values_v<v898::AnimatePacket::Action>{{
    v898::AnimatePacket::Action::NoAction,
    v898::AnimatePacket::Action::Swing,
    v898::AnimatePacket::Action::WakeUp,
    v898::AnimatePacket::Action::CriticalHit,
    v898::AnimatePacket::Action::MagicCriticalHit,
}};

template <>
inline constexpr std::array<std::string_view, 5> names_v<v898::AnimatePacket::Action>{{
    "noaction",
    "swing",
    "wakeup",
    "criticalhit",
    "magiccriticalhit",
}};

template <>
inline constexpr std::string_view type_name_v<v898::AnimatePacket::Action>{"AnimatePacket::Action"};

template <>
inline constexpr std::array<v2225::AnimatePacket::Action, 5> values_v<v2225::AnimatePacket::Action>{{
    v2225::AnimatePacket::Action::NoAction,
    v2225::AnimatePacket::Action::Swing,
    v2225::AnimatePacket::Action::WakeUp,
    v2225::AnimatePacket::Action::CriticalHit,
    v2225::AnimatePacket::Action::MagicCriticalHit,
}};

template <>
inline constexpr std::array<std::string_view, 5> names_v<v2225::AnimatePacket::Action>{{
    "noaction",
    "swing",
    "wakeup",
    "criticalhit",
    "magiccriticalhit",
}};

template <>
inline constexpr std::string_view type_name_v<v2225::AnimatePacket::Action>{"AnimatePacket::Action"};

template <>
inline constexpr std::array<NpcRequestPacket::RequestType, 7> values_v<NpcRequestPacket::RequestType>{{
    NpcRequestPacket::RequestType::SetActions,
    NpcRequestPacket::RequestType::ExecuteAction,
    NpcRequestPacket::RequestType::ExecuteClosingCommands,
    NpcRequestPacket::RequestType::SetName,
    NpcRequestPacket::RequestType::SetSkin,
    NpcRequestPacket::RequestType::SetInteractText,
    NpcRequestPacket::RequestType::ExecuteOpeningCommands,
}};

template <>
inline constexpr std::array<std::string_view, 7> names_v<NpcRequestPacket::RequestType>{{
    "setactions",
    "executeaction",
    "executeclosingcommands",
    "setname",
    "setskin",
    "setinteracttext",
    "executeopeningcommands",
}};

template <>
inline constexpr std::string_view type_name_v<NpcRequestPacket::RequestType>{"NpcRequestPacket::RequestType"};

template <>
inline constexpr std::array<NpcDialoguePacket::NpcDialogueActionType, 2> values_v<NpcDialoguePacket::NpcDialogueActionType>{{
    NpcDialoguePacket::NpcDialogueActionType::Open,
    NpcDialoguePacket::NpcDialogueActionType::Close,
}};

template <>
inline constexpr std::array<std::string_view, 2> names_v<NpcDialoguePacket::NpcDialogueActionType>{{
    "open",
    "close",
}};

template <>
inline constexpr std::string_view type_name_v<NpcDialoguePacket::NpcDialogueActionType>{"NpcDialoguePacket::NpcDialogueActionType"};

}  // namespace detail

namespace detail {

template <>
inline constexpr bool is_reflected_struct_v<base::DataItemBytePayload> = true;

template <>
inline constexpr std::string_view struct_name_v<base::DataItemBytePayload>{"DataItemBytePayload"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::DataItemBytePayload>{{
    "value",
}};

template <>
struct field_accessor<base::DataItemBytePayload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.value;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::DataItemBytePayload> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::DataItemBytePayload>{"DataItemBytePayload"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2168::DataItemBytePayload>{{
    "value",
}};

template <>
struct field_accessor<v2168::DataItemBytePayload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.value;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::DataItemShortPayload> = true;

template <>
inline constexpr std::string_view struct_name_v<base::DataItemShortPayload>{"DataItemShortPayload"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::DataItemShortPayload>{{
    "value",
}};

template <>
struct field_accessor<base::DataItemShortPayload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.value;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::DataItemShortPayload> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::DataItemShortPayload>{"DataItemShortPayload"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2168::DataItemShortPayload>{{
    "value",
}};

template <>
struct field_accessor<v2168::DataItemShortPayload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.value;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::DataItemIntPayload> = true;

template <>
inline constexpr std::string_view struct_name_v<base::DataItemIntPayload>{"DataItemIntPayload"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::DataItemIntPayload>{{
    "value",
}};

template <>
struct field_accessor<base::DataItemIntPayload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.value;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::DataItemIntPayload> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::DataItemIntPayload>{"DataItemIntPayload"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2168::DataItemIntPayload>{{
    "value",
}};

template <>
struct field_accessor<v2168::DataItemIntPayload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.value;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::DataItemFloatPayload> = true;

template <>
inline constexpr std::string_view struct_name_v<base::DataItemFloatPayload>{"DataItemFloatPayload"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::DataItemFloatPayload>{{
    "value",
}};

template <>
struct field_accessor<base::DataItemFloatPayload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.value;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::DataItemFloatPayload> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::DataItemFloatPayload>{"DataItemFloatPayload"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2168::DataItemFloatPayload>{{
    "value",
}};

template <>
struct field_accessor<v2168::DataItemFloatPayload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.value;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::DataItemStringPayload> = true;

template <>
inline constexpr std::string_view struct_name_v<base::DataItemStringPayload>{"DataItemStringPayload"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::DataItemStringPayload>{{
    "value",
}};

template <>
struct field_accessor<base::DataItemStringPayload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.value;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::DataItemStringPayload> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::DataItemStringPayload>{"DataItemStringPayload"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2168::DataItemStringPayload>{{
    "value",
}};

template <>
struct field_accessor<v2168::DataItemStringPayload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.value;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::DataItemCompoundTagPayload> = true;

template <>
inline constexpr std::string_view struct_name_v<base::DataItemCompoundTagPayload>{"DataItemCompoundTagPayload"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::DataItemCompoundTagPayload>{{
    "value",
}};

template <>
struct field_accessor<base::DataItemCompoundTagPayload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.value;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::DataItemCompoundTagPayload> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::DataItemCompoundTagPayload>{"DataItemCompoundTagPayload"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2168::DataItemCompoundTagPayload>{{
    "value",
}};

template <>
struct field_accessor<v2168::DataItemCompoundTagPayload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.value;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::DataItemPosPayload> = true;

template <>
inline constexpr std::string_view struct_name_v<base::DataItemPosPayload>{"DataItemPosPayload"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::DataItemPosPayload>{{
    "value",
}};

template <>
struct field_accessor<base::DataItemPosPayload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.value;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::DataItemPosPayload> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::DataItemPosPayload>{"DataItemPosPayload"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2168::DataItemPosPayload>{{
    "value",
}};

template <>
struct field_accessor<v2168::DataItemPosPayload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.value;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::DataItemInt64Payload> = true;

template <>
inline constexpr std::string_view struct_name_v<base::DataItemInt64Payload>{"DataItemInt64Payload"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::DataItemInt64Payload>{{
    "value",
}};

template <>
struct field_accessor<base::DataItemInt64Payload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.value;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::DataItemInt64Payload> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::DataItemInt64Payload>{"DataItemInt64Payload"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2168::DataItemInt64Payload>{{
    "value",
}};

template <>
struct field_accessor<v2168::DataItemInt64Payload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.value;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::DataItemVec3Payload> = true;

template <>
inline constexpr std::string_view struct_name_v<base::DataItemVec3Payload>{"DataItemVec3Payload"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::DataItemVec3Payload>{{
    "value",
}};

template <>
struct field_accessor<base::DataItemVec3Payload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.value;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::DataItemVec3Payload> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::DataItemVec3Payload>{"DataItemVec3Payload"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2168::DataItemVec3Payload>{{
    "value",
}};

template <>
struct field_accessor<v2168::DataItemVec3Payload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.value;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::DataItemEntry> = true;

template <>
inline constexpr std::string_view struct_name_v<base::DataItemEntry>{"DataItemEntry"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<base::DataItemEntry>{{
    "id",
    "payload",
}};

template <>
struct field_accessor<base::DataItemEntry> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.id;
        }
        else {
            return value.payload;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::DataItemEntry> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::DataItemEntry>{"DataItemEntry"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2168::DataItemEntry>{{
    "id",
    "payload",
}};

template <>
struct field_accessor<v2168::DataItemEntry> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.id;
        }
        else {
            return value.payload;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::SynchedActorData::CopyableDataList> = true;

template <>
inline constexpr std::string_view struct_name_v<base::SynchedActorData::CopyableDataList>{"SynchedActorData::CopyableDataList"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::SynchedActorData::CopyableDataList>{{
    "data",
}};

template <>
struct field_accessor<base::SynchedActorData::CopyableDataList> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.data;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::SynchedActorData::CopyableDataList> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::SynchedActorData::CopyableDataList>{"SynchedActorData::CopyableDataList"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2168::SynchedActorData::CopyableDataList>{{
    "data",
}};

template <>
struct field_accessor<v2168::SynchedActorData::CopyableDataList> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.data;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::SynchedActorData> = true;

template <>
inline constexpr std::string_view struct_name_v<base::SynchedActorData>{"SynchedActorData"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<base::SynchedActorData>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<v2168::SynchedActorData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::SynchedActorData>{"SynchedActorData"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<v2168::SynchedActorData>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<PropertySyncData::PropertySyncIntEntry> = true;

template <>
inline constexpr std::string_view struct_name_v<PropertySyncData::PropertySyncIntEntry>{"PropertySyncData::PropertySyncIntEntry"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<PropertySyncData::PropertySyncIntEntry>{{
    "property_index",
    "data",
}};

template <>
struct field_accessor<PropertySyncData::PropertySyncIntEntry> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.property_index;
        }
        else {
            return value.data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<PropertySyncData::PropertySyncFloatEntry> = true;

template <>
inline constexpr std::string_view struct_name_v<PropertySyncData::PropertySyncFloatEntry>{"PropertySyncData::PropertySyncFloatEntry"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<PropertySyncData::PropertySyncFloatEntry>{{
    "property_index",
    "data",
}};

template <>
struct field_accessor<PropertySyncData::PropertySyncFloatEntry> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.property_index;
        }
        else {
            return value.data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<PropertySyncData> = true;

template <>
inline constexpr std::string_view struct_name_v<PropertySyncData>{"PropertySyncData"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<PropertySyncData>{{
    "int_entries",
    "float_entries",
}};

template <>
struct field_accessor<PropertySyncData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.int_entries;
        }
        else {
            return value.float_entries;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<SyncedAttribute> = true;

template <>
inline constexpr std::string_view struct_name_v<SyncedAttribute>{"SyncedAttribute"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<SyncedAttribute>{{
    "name",
    "min_value",
    "current_value",
    "max_value",
}};

template <>
struct field_accessor<SyncedAttribute> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.name;
        }
        else if constexpr (I == 1) {
            return value.min_value;
        }
        else if constexpr (I == 2) {
            return value.current_value;
        }
        else {
            return value.max_value;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<ActorLink> = true;

template <>
inline constexpr std::string_view struct_name_v<ActorLink>{"ActorLink"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<ActorLink>{{
    "a",
    "b",
    "type",
    "immediate",
    "passenger_initiated",
    "vehicle_angular_velocity",
}};

template <>
struct field_accessor<ActorLink> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.a;
        }
        else if constexpr (I == 1) {
            return value.b;
        }
        else if constexpr (I == 2) {
            return value.type;
        }
        else if constexpr (I == 3) {
            return value.immediate;
        }
        else if constexpr (I == 4) {
            return value.passenger_initiated;
        }
        else {
            return value.vehicle_angular_velocity;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<PassengerOfBlockArguments> = true;

template <>
inline constexpr std::string_view struct_name_v<PassengerOfBlockArguments>{"PassengerOfBlockArguments"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<PassengerOfBlockArguments>{{
    "block_pos",
    "offset",
    "rotation",
    "rotation_limit",
    "emote_type",
}};

template <>
struct field_accessor<PassengerOfBlockArguments> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.block_pos;
        }
        else if constexpr (I == 1) {
            return value.offset;
        }
        else if constexpr (I == 2) {
            return value.rotation;
        }
        else if constexpr (I == 3) {
            return value.rotation_limit;
        }
        else {
            return value.emote_type;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::AddActorPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::AddActorPacket>{"AddActorPacket"};

template <>
inline constexpr std::array<std::string_view, 12> field_names_v<base::AddActorPacket>{{
    "entity_id",
    "runtime_id",
    "actor_type",
    "pos",
    "velocity",
    "rot",
    "y_head_rotation",
    "y_body_rotation",
    "attributes",
    "data",
    "synched_properties",
    "links",
}};

template <>
struct field_accessor<base::AddActorPacket> {
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
            return value.actor_type;
        }
        else if constexpr (I == 3) {
            return value.pos;
        }
        else if constexpr (I == 4) {
            return value.velocity;
        }
        else if constexpr (I == 5) {
            return value.rot;
        }
        else if constexpr (I == 6) {
            return value.y_head_rotation;
        }
        else if constexpr (I == 7) {
            return value.y_body_rotation;
        }
        else if constexpr (I == 8) {
            return value.attributes;
        }
        else if constexpr (I == 9) {
            return value.data;
        }
        else if constexpr (I == 10) {
            return value.synched_properties;
        }
        else {
            return value.links;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::AddActorPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::AddActorPacket>{"AddActorPacket"};

template <>
inline constexpr std::array<std::string_view, 12> field_names_v<v2168::AddActorPacket>{{
    "entity_id",
    "runtime_id",
    "actor_type",
    "pos",
    "velocity",
    "rot",
    "y_head_rotation",
    "y_body_rotation",
    "attributes",
    "data",
    "synched_properties",
    "links",
}};

template <>
struct field_accessor<v2168::AddActorPacket> {
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
            return value.actor_type;
        }
        else if constexpr (I == 3) {
            return value.pos;
        }
        else if constexpr (I == 4) {
            return value.velocity;
        }
        else if constexpr (I == 5) {
            return value.rot;
        }
        else if constexpr (I == 6) {
            return value.y_head_rotation;
        }
        else if constexpr (I == 7) {
            return value.y_body_rotation;
        }
        else if constexpr (I == 8) {
            return value.attributes;
        }
        else if constexpr (I == 9) {
            return value.data;
        }
        else if constexpr (I == 10) {
            return value.synched_properties;
        }
        else {
            return value.links;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::AddActorPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::AddActorPacket>{"AddActorPacket"};

template <>
inline constexpr std::array<std::string_view, 13> field_names_v<v2225::AddActorPacket>{{
    "entity_id",
    "runtime_id",
    "actor_type",
    "pos",
    "velocity",
    "rot",
    "y_head_rotation",
    "y_body_rotation",
    "attributes",
    "data",
    "synched_properties",
    "links",
    "passenger_block_data",
}};

template <>
struct field_accessor<v2225::AddActorPacket> {
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
            return value.actor_type;
        }
        else if constexpr (I == 3) {
            return value.pos;
        }
        else if constexpr (I == 4) {
            return value.velocity;
        }
        else if constexpr (I == 5) {
            return value.rot;
        }
        else if constexpr (I == 6) {
            return value.y_head_rotation;
        }
        else if constexpr (I == 7) {
            return value.y_body_rotation;
        }
        else if constexpr (I == 8) {
            return value.attributes;
        }
        else if constexpr (I == 9) {
            return value.data;
        }
        else if constexpr (I == 10) {
            return value.synched_properties;
        }
        else if constexpr (I == 11) {
            return value.links;
        }
        else {
            return value.passenger_block_data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::SetActorDataPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::SetActorDataPacket>{"SetActorDataPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<base::SetActorDataPacket>{{
    "id",
    "packed_items",
    "synched_properties",
    "tick",
}};

template <>
struct field_accessor<base::SetActorDataPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.id;
        }
        else if constexpr (I == 1) {
            return value.packed_items;
        }
        else if constexpr (I == 2) {
            return value.synched_properties;
        }
        else {
            return value.tick;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::SetActorDataPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::SetActorDataPacket>{"SetActorDataPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v2168::SetActorDataPacket>{{
    "id",
    "packed_items",
    "synched_properties",
    "tick",
}};

template <>
struct field_accessor<v2168::SetActorDataPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.id;
        }
        else if constexpr (I == 1) {
            return value.packed_items;
        }
        else if constexpr (I == 2) {
            return value.synched_properties;
        }
        else {
            return value.tick;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::SetLastHurtByPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::SetLastHurtByPacket>{"SetLastHurtByPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::SetLastHurtByPacket>{{
    "last_hurt_by",
}};

template <>
struct field_accessor<base::SetLastHurtByPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.last_hurt_by;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v766::SetLastHurtByPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v766::SetLastHurtByPacket>{"SetLastHurtByPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v766::SetLastHurtByPacket>{{
    "last_hurt_by",
}};

template <>
struct field_accessor<v766::SetLastHurtByPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.last_hurt_by;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v800::SetLastHurtByPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v800::SetLastHurtByPacket>{"SetLastHurtByPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v800::SetLastHurtByPacket>{{
    "last_hurt_by",
}};

template <>
struct field_accessor<v800::SetLastHurtByPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.last_hurt_by;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v827::SetLastHurtByPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v827::SetLastHurtByPacket>{"SetLastHurtByPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v827::SetLastHurtByPacket>{{
    "last_hurt_by",
}};

template <>
struct field_accessor<v827::SetLastHurtByPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.last_hurt_by;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::SetLastHurtByPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::SetLastHurtByPacket>{"SetLastHurtByPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v924::SetLastHurtByPacket>{{
    "last_hurt_by",
}};

template <>
struct field_accessor<v924::SetLastHurtByPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.last_hurt_by;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v975::SetLastHurtByPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v975::SetLastHurtByPacket>{"SetLastHurtByPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v975::SetLastHurtByPacket>{{
    "last_hurt_by",
}};

template <>
struct field_accessor<v975::SetLastHurtByPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.last_hurt_by;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::SetLastHurtByPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::SetLastHurtByPacket>{"SetLastHurtByPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2168::SetLastHurtByPacket>{{
    "last_hurt_by",
}};

template <>
struct field_accessor<v2168::SetLastHurtByPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.last_hurt_by;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::SetLastHurtByPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::SetLastHurtByPacket>{"SetLastHurtByPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2225::SetLastHurtByPacket>{{
    "last_hurt_by",
}};

template <>
struct field_accessor<v2225::SetLastHurtByPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.last_hurt_by;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<RemoveActorPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<RemoveActorPacket>{"RemoveActorPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<RemoveActorPacket>{{
    "entity_id",
}};

template <>
struct field_accessor<RemoveActorPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.entity_id;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<ActorPickRequestPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<ActorPickRequestPacket>{"ActorPickRequestPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<ActorPickRequestPacket>{{
    "id",
    "max_slots",
    "with_data",
}};

template <>
struct field_accessor<ActorPickRequestPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.id;
        }
        else if constexpr (I == 1) {
            return value.max_slots;
        }
        else {
            return value.with_data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<AddBehaviorTreePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<AddBehaviorTreePacket>{"AddBehaviorTreePacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<AddBehaviorTreePacket>{{
    "json_input",
}};

template <>
struct field_accessor<AddBehaviorTreePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.json_input;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<TakeItemActorPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<TakeItemActorPacket>{"TakeItemActorPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<TakeItemActorPacket>{{
    "item_id",
    "actor_id",
}};

template <>
struct field_accessor<TakeItemActorPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.item_id;
        }
        else {
            return value.actor_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<MoveActorAbsoluteData> = true;

template <>
inline constexpr std::string_view struct_name_v<MoveActorAbsoluteData>{"MoveActorAbsoluteData"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<MoveActorAbsoluteData>{{
    "runtime_id",
    "header",
    "pos",
    "rot_x",
    "rot_y",
    "rot_y_head",
}};

template <>
struct field_accessor<MoveActorAbsoluteData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.runtime_id;
        }
        else if constexpr (I == 1) {
            return value.header;
        }
        else if constexpr (I == 2) {
            return value.pos;
        }
        else if constexpr (I == 3) {
            return value.rot_x;
        }
        else if constexpr (I == 4) {
            return value.rot_y;
        }
        else {
            return value.rot_y_head;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<MoveActorAbsolutePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<MoveActorAbsolutePacket>{"MoveActorAbsolutePacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<MoveActorAbsolutePacket>{{
    "move_data",
}};

template <>
struct field_accessor<MoveActorAbsolutePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.move_data;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<AddPaintingPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<AddPaintingPacket>{"AddPaintingPacket"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<AddPaintingPacket>{{
    "entity_id",
    "runtime_id",
    "pos",
    "dir",
    "motif",
}};

template <>
struct field_accessor<AddPaintingPacket> {
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
            return value.pos;
        }
        else if constexpr (I == 3) {
            return value.dir;
        }
        else {
            return value.motif;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::ActorEventPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ActorEventPacket>{"ActorEventPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<base::ActorEventPacket>{{
    "runtime_id",
    "event_id",
    "data",
}};

template <>
struct field_accessor<base::ActorEventPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.runtime_id;
        }
        else if constexpr (I == 1) {
            return value.event_id;
        }
        else {
            return value.data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v859::ActorEventPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v859::ActorEventPacket>{"ActorEventPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v859::ActorEventPacket>{{
    "runtime_id",
    "event_id",
    "data",
}};

template <>
struct field_accessor<v859::ActorEventPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.runtime_id;
        }
        else if constexpr (I == 1) {
            return value.event_id;
        }
        else {
            return value.data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v898::ActorEventPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v898::ActorEventPacket>{"ActorEventPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v898::ActorEventPacket>{{
    "runtime_id",
    "event_id",
    "data",
}};

template <>
struct field_accessor<v898::ActorEventPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.runtime_id;
        }
        else if constexpr (I == 1) {
            return value.event_id;
        }
        else {
            return value.data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v975::ActorEventPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v975::ActorEventPacket>{"ActorEventPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v975::ActorEventPacket>{{
    "runtime_id",
    "event_id",
    "data",
    "fire_at_position",
}};

template <>
struct field_accessor<v975::ActorEventPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.runtime_id;
        }
        else if constexpr (I == 1) {
            return value.event_id;
        }
        else if constexpr (I == 2) {
            return value.data;
        }
        else {
            return value.fire_at_position;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<SetActorMotionPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<SetActorMotionPacket>{"SetActorMotionPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<SetActorMotionPacket>{{
    "runtime_id",
    "motion",
    "tick",
}};

template <>
struct field_accessor<SetActorMotionPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.runtime_id;
        }
        else if constexpr (I == 1) {
            return value.motion;
        }
        else {
            return value.tick;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<SetActorLinkPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<SetActorLinkPacket>{"SetActorLinkPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<SetActorLinkPacket>{{
    "link",
}};

template <>
struct field_accessor<SetActorLinkPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.link;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::SetPassengerOfBlockPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::SetPassengerOfBlockPacket>{"SetPassengerOfBlockPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2225::SetPassengerOfBlockPacket>{{
    "passenger",
    "passenger_of_block_data",
}};

template <>
struct field_accessor<v2225::SetPassengerOfBlockPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.passenger;
        }
        else {
            return value.passenger_of_block_data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::AnimatePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::AnimatePacket>{"AnimatePacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<base::AnimatePacket>{{
    "action",
    "runtime_id",
    "data",
}};

template <>
struct field_accessor<base::AnimatePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.action;
        }
        else if constexpr (I == 1) {
            return value.runtime_id;
        }
        else {
            return value.data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v800::AnimatePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v800::AnimatePacket>{"AnimatePacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v800::AnimatePacket>{{
    "action",
    "runtime_id",
    "data",
}};

template <>
struct field_accessor<v800::AnimatePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.action;
        }
        else if constexpr (I == 1) {
            return value.runtime_id;
        }
        else {
            return value.data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v859::AnimatePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v859::AnimatePacket>{"AnimatePacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v859::AnimatePacket>{{
    "action",
    "runtime_id",
    "data",
    "rowing_time",
}};

template <>
struct field_accessor<v859::AnimatePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.action;
        }
        else if constexpr (I == 1) {
            return value.runtime_id;
        }
        else if constexpr (I == 2) {
            return value.data;
        }
        else {
            return value.rowing_time;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v898::AnimatePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v898::AnimatePacket>{"AnimatePacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v898::AnimatePacket>{{
    "action",
    "runtime_id",
    "data",
    "swing_source",
}};

template <>
struct field_accessor<v898::AnimatePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.action;
        }
        else if constexpr (I == 1) {
            return value.runtime_id;
        }
        else if constexpr (I == 2) {
            return value.data;
        }
        else {
            return value.swing_source;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::AnimatePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::AnimatePacket>{"AnimatePacket"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v2225::AnimatePacket>{{
    "action",
    "runtime_id",
    "data",
    "swing_source",
    "hand",
}};

template <>
struct field_accessor<v2225::AnimatePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.action;
        }
        else if constexpr (I == 1) {
            return value.runtime_id;
        }
        else if constexpr (I == 2) {
            return value.data;
        }
        else if constexpr (I == 3) {
            return value.swing_source;
        }
        else {
            return value.hand;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<SpawnExperienceOrbPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<SpawnExperienceOrbPacket>{"SpawnExperienceOrbPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<SpawnExperienceOrbPacket>{{
    "pos",
    "xp_value",
}};

template <>
struct field_accessor<SpawnExperienceOrbPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.pos;
        }
        else {
            return value.xp_value;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<AvailableActorIdentifiersPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<AvailableActorIdentifiersPacket>{"AvailableActorIdentifiersPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<AvailableActorIdentifiersPacket>{{
    "identifier_list",
}};

template <>
struct field_accessor<AvailableActorIdentifiersPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.identifier_list;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<MotionPredictionHintsPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<MotionPredictionHintsPacket>{"MotionPredictionHintsPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<MotionPredictionHintsPacket>{{
    "runtime_id",
    "motion",
    "on_ground",
}};

template <>
struct field_accessor<MotionPredictionHintsPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.runtime_id;
        }
        else if constexpr (I == 1) {
            return value.motion;
        }
        else {
            return value.on_ground;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<DeathInfoPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<DeathInfoPacket>{"DeathInfoPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<DeathInfoPacket>{{
    "death_cause_attack_name",
    "death_cause_message_list",
}};

template <>
struct field_accessor<DeathInfoPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.death_cause_attack_name;
        }
        else {
            return value.death_cause_message_list;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<SyncActorPropertyPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<SyncActorPropertyPacket>{"SyncActorPropertyPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<SyncActorPropertyPacket>{{
    "property_data",
}};

template <>
struct field_accessor<SyncActorPropertyPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.property_data;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<ChangeMobPropertyPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<ChangeMobPropertyPacket>{"ChangeMobPropertyPacket"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<ChangeMobPropertyPacket>{{
    "actor_id",
    "prop_name",
    "bool_component_val",
    "string_component_val",
    "int_component_val",
    "float_component_val",
}};

template <>
struct field_accessor<ChangeMobPropertyPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.actor_id;
        }
        else if constexpr (I == 1) {
            return value.prop_name;
        }
        else if constexpr (I == 2) {
            return value.bool_component_val;
        }
        else if constexpr (I == 3) {
            return value.string_component_val;
        }
        else if constexpr (I == 4) {
            return value.int_component_val;
        }
        else {
            return value.float_component_val;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<AnimateEntityPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<AnimateEntityPacket>{"AnimateEntityPacket"};

template <>
inline constexpr std::array<std::string_view, 7> field_names_v<AnimateEntityPacket>{{
    "animation",
    "next_state",
    "stop_expression",
    "stop_expression_version",
    "controller",
    "blend_out_time",
    "runtime_ids",
}};

template <>
struct field_accessor<AnimateEntityPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.animation;
        }
        else if constexpr (I == 1) {
            return value.next_state;
        }
        else if constexpr (I == 2) {
            return value.stop_expression;
        }
        else if constexpr (I == 3) {
            return value.stop_expression_version;
        }
        else if constexpr (I == 4) {
            return value.controller;
        }
        else if constexpr (I == 5) {
            return value.blend_out_time;
        }
        else {
            return value.runtime_ids;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<NpcRequestPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<NpcRequestPacket>{"NpcRequestPacket"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<NpcRequestPacket>{{
    "id",
    "type",
    "actions",
    "action_index",
    "scene_name",
}};

template <>
struct field_accessor<NpcRequestPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.id;
        }
        else if constexpr (I == 1) {
            return value.type;
        }
        else if constexpr (I == 2) {
            return value.actions;
        }
        else if constexpr (I == 3) {
            return value.action_index;
        }
        else {
            return value.scene_name;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<NpcDialoguePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<NpcDialoguePacket>{"NpcDialoguePacket"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<NpcDialoguePacket>{{
    "npc_id",
    "npc_dialogue_action_type",
    "dialogue",
    "scene_name",
    "npc_name",
    "action_json",
}};

template <>
struct field_accessor<NpcDialoguePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.npc_id;
        }
        else if constexpr (I == 1) {
            return value.npc_dialogue_action_type;
        }
        else if constexpr (I == 2) {
            return value.dialogue;
        }
        else if constexpr (I == 3) {
            return value.scene_name;
        }
        else if constexpr (I == 4) {
            return value.npc_name;
        }
        else {
            return value.action_json;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::AddItemActorPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::AddItemActorPacket>{"AddItemActorPacket"};

template <>
inline constexpr std::array<std::string_view, 7> field_names_v<base::AddItemActorPacket>{{
    "id",
    "runtime_id",
    "item",
    "pos",
    "velocity",
    "data",
    "is_from_fishing",
}};

template <>
struct field_accessor<base::AddItemActorPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.id;
        }
        else if constexpr (I == 1) {
            return value.runtime_id;
        }
        else if constexpr (I == 2) {
            return value.item;
        }
        else if constexpr (I == 3) {
            return value.pos;
        }
        else if constexpr (I == 4) {
            return value.velocity;
        }
        else if constexpr (I == 5) {
            return value.data;
        }
        else {
            return value.is_from_fishing;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::AddItemActorPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::AddItemActorPacket>{"AddItemActorPacket"};

template <>
inline constexpr std::array<std::string_view, 7> field_names_v<v2168::AddItemActorPacket>{{
    "id",
    "runtime_id",
    "item",
    "pos",
    "velocity",
    "data",
    "is_from_fishing",
}};

template <>
struct field_accessor<v2168::AddItemActorPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.id;
        }
        else if constexpr (I == 1) {
            return value.runtime_id;
        }
        else if constexpr (I == 2) {
            return value.item;
        }
        else if constexpr (I == 3) {
            return value.pos;
        }
        else if constexpr (I == 4) {
            return value.velocity;
        }
        else if constexpr (I == 5) {
            return value.data;
        }
        else {
            return value.is_from_fishing;
        }
    }
};

}  // namespace detail


template <>
struct Serializer<base::DataItemBytePayload> {
    static void serialize(BinaryWriter &stream, const base::DataItemBytePayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::DataItemBytePayload, std::error_code>;
};

template <>
struct Serializer<v2168::DataItemBytePayload> {
    static void serialize(BinaryWriter &stream, const v2168::DataItemBytePayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::DataItemBytePayload, std::error_code>;
};

template <>
struct Serializer<base::DataItemShortPayload> {
    static void serialize(BinaryWriter &stream, const base::DataItemShortPayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::DataItemShortPayload, std::error_code>;
};

template <>
struct Serializer<v2168::DataItemShortPayload> {
    static void serialize(BinaryWriter &stream, const v2168::DataItemShortPayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::DataItemShortPayload, std::error_code>;
};

template <>
struct Serializer<base::DataItemIntPayload> {
    static void serialize(BinaryWriter &stream, const base::DataItemIntPayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::DataItemIntPayload, std::error_code>;
};

template <>
struct Serializer<v2168::DataItemIntPayload> {
    static void serialize(BinaryWriter &stream, const v2168::DataItemIntPayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::DataItemIntPayload, std::error_code>;
};

template <>
struct Serializer<base::DataItemFloatPayload> {
    static void serialize(BinaryWriter &stream, const base::DataItemFloatPayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::DataItemFloatPayload, std::error_code>;
};

template <>
struct Serializer<v2168::DataItemFloatPayload> {
    static void serialize(BinaryWriter &stream, const v2168::DataItemFloatPayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::DataItemFloatPayload, std::error_code>;
};

template <>
struct Serializer<base::DataItemStringPayload> {
    static void serialize(BinaryWriter &stream, const base::DataItemStringPayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::DataItemStringPayload, std::error_code>;
};

template <>
struct Serializer<v2168::DataItemStringPayload> {
    static void serialize(BinaryWriter &stream, const v2168::DataItemStringPayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::DataItemStringPayload, std::error_code>;
};

template <>
struct Serializer<base::DataItemCompoundTagPayload> {
    static void serialize(BinaryWriter &stream, const base::DataItemCompoundTagPayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::DataItemCompoundTagPayload, std::error_code>;
};

template <>
struct Serializer<v2168::DataItemCompoundTagPayload> {
    static void serialize(BinaryWriter &stream, const v2168::DataItemCompoundTagPayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::DataItemCompoundTagPayload, std::error_code>;
};

template <>
struct Serializer<base::DataItemPosPayload> {
    static void serialize(BinaryWriter &stream, const base::DataItemPosPayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::DataItemPosPayload, std::error_code>;
};

template <>
struct Serializer<v2168::DataItemPosPayload> {
    static void serialize(BinaryWriter &stream, const v2168::DataItemPosPayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::DataItemPosPayload, std::error_code>;
};

template <>
struct Serializer<base::DataItemInt64Payload> {
    static void serialize(BinaryWriter &stream, const base::DataItemInt64Payload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::DataItemInt64Payload, std::error_code>;
};

template <>
struct Serializer<v2168::DataItemInt64Payload> {
    static void serialize(BinaryWriter &stream, const v2168::DataItemInt64Payload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::DataItemInt64Payload, std::error_code>;
};

template <>
struct Serializer<base::DataItemVec3Payload> {
    static void serialize(BinaryWriter &stream, const base::DataItemVec3Payload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::DataItemVec3Payload, std::error_code>;
};

template <>
struct Serializer<v2168::DataItemVec3Payload> {
    static void serialize(BinaryWriter &stream, const v2168::DataItemVec3Payload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::DataItemVec3Payload, std::error_code>;
};

template <>
struct Serializer<base::DataItemEntry> {
    static void serialize(BinaryWriter &stream, const base::DataItemEntry &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::DataItemEntry, std::error_code>;
};

template <>
struct Serializer<v2168::DataItemEntry> {
    static void serialize(BinaryWriter &stream, const v2168::DataItemEntry &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::DataItemEntry, std::error_code>;
};

template <>
struct Serializer<base::SynchedActorData::CopyableDataList> {
    static void serialize(BinaryWriter &stream, const base::SynchedActorData::CopyableDataList &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::SynchedActorData::CopyableDataList, std::error_code>;
};

template <>
struct Serializer<v2168::SynchedActorData::CopyableDataList> {
    static void serialize(BinaryWriter &stream, const v2168::SynchedActorData::CopyableDataList &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::SynchedActorData::CopyableDataList, std::error_code>;
};

template <>
struct Serializer<PropertySyncData::PropertySyncIntEntry> {
    static void serialize(BinaryWriter &stream, const PropertySyncData::PropertySyncIntEntry &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<PropertySyncData::PropertySyncIntEntry, std::error_code>;
};

template <>
struct Serializer<PropertySyncData::PropertySyncFloatEntry> {
    static void serialize(BinaryWriter &stream, const PropertySyncData::PropertySyncFloatEntry &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<PropertySyncData::PropertySyncFloatEntry, std::error_code>;
};

template <>
struct Serializer<PropertySyncData> {
    static void serialize(BinaryWriter &stream, const PropertySyncData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<PropertySyncData, std::error_code>;
};

template <>
struct Serializer<SyncedAttribute> {
    static void serialize(BinaryWriter &stream, const SyncedAttribute &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<SyncedAttribute, std::error_code>;
};

template <>
struct Serializer<ActorLink> {
    static void serialize(BinaryWriter &stream, const ActorLink &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<ActorLink, std::error_code>;
};

template <>
struct Serializer<PassengerOfBlockArguments> {
    static void serialize(BinaryWriter &stream, const PassengerOfBlockArguments &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<PassengerOfBlockArguments, std::error_code>;
};

template <>
struct Serializer<base::AddActorPacket> {
    static void serialize(BinaryWriter &stream, const base::AddActorPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::AddActorPacket, std::error_code>;
};

template <>
struct Serializer<v2168::AddActorPacket> {
    static void serialize(BinaryWriter &stream, const v2168::AddActorPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::AddActorPacket, std::error_code>;
};

template <>
struct Serializer<v2225::AddActorPacket> {
    static void serialize(BinaryWriter &stream, const v2225::AddActorPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::AddActorPacket, std::error_code>;
};

template <>
struct Serializer<base::SetActorDataPacket> {
    static void serialize(BinaryWriter &stream, const base::SetActorDataPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::SetActorDataPacket, std::error_code>;
};

template <>
struct Serializer<v2168::SetActorDataPacket> {
    static void serialize(BinaryWriter &stream, const v2168::SetActorDataPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::SetActorDataPacket, std::error_code>;
};

template <>
struct Serializer<base::SetLastHurtByPacket> {
    static void serialize(BinaryWriter &stream, const base::SetLastHurtByPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::SetLastHurtByPacket, std::error_code>;
};

template <>
struct Serializer<v766::SetLastHurtByPacket> {
    static void serialize(BinaryWriter &stream, const v766::SetLastHurtByPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v766::SetLastHurtByPacket, std::error_code>;
};

template <>
struct Serializer<v800::SetLastHurtByPacket> {
    static void serialize(BinaryWriter &stream, const v800::SetLastHurtByPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v800::SetLastHurtByPacket, std::error_code>;
};

template <>
struct Serializer<v827::SetLastHurtByPacket> {
    static void serialize(BinaryWriter &stream, const v827::SetLastHurtByPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v827::SetLastHurtByPacket, std::error_code>;
};

template <>
struct Serializer<v924::SetLastHurtByPacket> {
    static void serialize(BinaryWriter &stream, const v924::SetLastHurtByPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::SetLastHurtByPacket, std::error_code>;
};

template <>
struct Serializer<v975::SetLastHurtByPacket> {
    static void serialize(BinaryWriter &stream, const v975::SetLastHurtByPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v975::SetLastHurtByPacket, std::error_code>;
};

template <>
struct Serializer<v2168::SetLastHurtByPacket> {
    static void serialize(BinaryWriter &stream, const v2168::SetLastHurtByPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::SetLastHurtByPacket, std::error_code>;
};

template <>
struct Serializer<v2225::SetLastHurtByPacket> {
    static void serialize(BinaryWriter &stream, const v2225::SetLastHurtByPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::SetLastHurtByPacket, std::error_code>;
};

template <>
struct Serializer<RemoveActorPacket> {
    static void serialize(BinaryWriter &stream, const RemoveActorPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<RemoveActorPacket, std::error_code>;
};

template <>
struct Serializer<ActorPickRequestPacket> {
    static void serialize(BinaryWriter &stream, const ActorPickRequestPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<ActorPickRequestPacket, std::error_code>;
};

template <>
struct Serializer<AddBehaviorTreePacket> {
    static void serialize(BinaryWriter &stream, const AddBehaviorTreePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<AddBehaviorTreePacket, std::error_code>;
};

template <>
struct Serializer<TakeItemActorPacket> {
    static void serialize(BinaryWriter &stream, const TakeItemActorPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<TakeItemActorPacket, std::error_code>;
};

template <>
struct Serializer<MoveActorAbsoluteData> {
    static void serialize(BinaryWriter &stream, const MoveActorAbsoluteData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<MoveActorAbsoluteData, std::error_code>;
};

template <>
struct Serializer<MoveActorAbsolutePacket> {
    static void serialize(BinaryWriter &stream, const MoveActorAbsolutePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<MoveActorAbsolutePacket, std::error_code>;
};

template <>
struct Serializer<AddPaintingPacket> {
    static void serialize(BinaryWriter &stream, const AddPaintingPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<AddPaintingPacket, std::error_code>;
};

template <>
struct Serializer<base::ActorEventPacket> {
    static void serialize(BinaryWriter &stream, const base::ActorEventPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ActorEventPacket, std::error_code>;
};

template <>
struct Serializer<v859::ActorEventPacket> {
    static void serialize(BinaryWriter &stream, const v859::ActorEventPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v859::ActorEventPacket, std::error_code>;
};

template <>
struct Serializer<v898::ActorEventPacket> {
    static void serialize(BinaryWriter &stream, const v898::ActorEventPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v898::ActorEventPacket, std::error_code>;
};

template <>
struct Serializer<v975::ActorEventPacket> {
    static void serialize(BinaryWriter &stream, const v975::ActorEventPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v975::ActorEventPacket, std::error_code>;
};

template <>
struct Serializer<SetActorMotionPacket> {
    static void serialize(BinaryWriter &stream, const SetActorMotionPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<SetActorMotionPacket, std::error_code>;
};

template <>
struct Serializer<SetActorLinkPacket> {
    static void serialize(BinaryWriter &stream, const SetActorLinkPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<SetActorLinkPacket, std::error_code>;
};

template <>
struct Serializer<v2225::SetPassengerOfBlockPacket> {
    static void serialize(BinaryWriter &stream, const v2225::SetPassengerOfBlockPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::SetPassengerOfBlockPacket, std::error_code>;
};

template <>
struct Serializer<ActorSwingSource> {
    static void serialize(BinaryWriter &stream, ActorSwingSource value);
    static auto deserialize(BinaryReader &stream) -> std::expected<ActorSwingSource, std::error_code>;
};

template <>
struct Serializer<base::AnimatePacket> {
    static void serialize(BinaryWriter &stream, const base::AnimatePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::AnimatePacket, std::error_code>;
};

template <>
struct Serializer<v800::AnimatePacket> {
    static void serialize(BinaryWriter &stream, const v800::AnimatePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v800::AnimatePacket, std::error_code>;
};

template <>
struct Serializer<v859::AnimatePacket> {
    static void serialize(BinaryWriter &stream, const v859::AnimatePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v859::AnimatePacket, std::error_code>;
};

template <>
struct Serializer<v898::AnimatePacket> {
    static void serialize(BinaryWriter &stream, const v898::AnimatePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v898::AnimatePacket, std::error_code>;
};

template <>
struct Serializer<v2225::AnimatePacket> {
    static void serialize(BinaryWriter &stream, const v2225::AnimatePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::AnimatePacket, std::error_code>;
};

template <>
struct Serializer<SpawnExperienceOrbPacket> {
    static void serialize(BinaryWriter &stream, const SpawnExperienceOrbPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<SpawnExperienceOrbPacket, std::error_code>;
};

template <>
struct Serializer<AvailableActorIdentifiersPacket> {
    static void serialize(BinaryWriter &stream, const AvailableActorIdentifiersPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<AvailableActorIdentifiersPacket, std::error_code>;
};

template <>
struct Serializer<MotionPredictionHintsPacket> {
    static void serialize(BinaryWriter &stream, const MotionPredictionHintsPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<MotionPredictionHintsPacket, std::error_code>;
};

template <>
struct Serializer<DeathInfoPacket> {
    static void serialize(BinaryWriter &stream, const DeathInfoPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<DeathInfoPacket, std::error_code>;
};

template <>
struct Serializer<SyncActorPropertyPacket> {
    static void serialize(BinaryWriter &stream, const SyncActorPropertyPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<SyncActorPropertyPacket, std::error_code>;
};

template <>
struct Serializer<ChangeMobPropertyPacket> {
    static void serialize(BinaryWriter &stream, const ChangeMobPropertyPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<ChangeMobPropertyPacket, std::error_code>;
};

template <>
struct Serializer<AnimateEntityPacket> {
    static void serialize(BinaryWriter &stream, const AnimateEntityPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<AnimateEntityPacket, std::error_code>;
};

template <>
struct Serializer<NpcRequestPacket> {
    static void serialize(BinaryWriter &stream, const NpcRequestPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<NpcRequestPacket, std::error_code>;
};

template <>
struct Serializer<NpcDialoguePacket> {
    static void serialize(BinaryWriter &stream, const NpcDialoguePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<NpcDialoguePacket, std::error_code>;
};

template <>
struct Serializer<base::AddItemActorPacket> {
    static void serialize(BinaryWriter &stream, const base::AddItemActorPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::AddItemActorPacket, std::error_code>;
};

template <>
struct Serializer<v2168::AddItemActorPacket> {
    static void serialize(BinaryWriter &stream, const v2168::AddItemActorPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::AddItemActorPacket, std::error_code>;
};
using ActorFlags = ActorFlags_<2225>;
using ActorDataIDs = ActorDataIDs_<2225>;
using DataItemBytePayload = DataItemBytePayload_<2225>;
using DataItemShortPayload = DataItemShortPayload_<2225>;
using DataItemIntPayload = DataItemIntPayload_<2225>;
using DataItemFloatPayload = DataItemFloatPayload_<2225>;
using DataItemStringPayload = DataItemStringPayload_<2225>;
using DataItemCompoundTagPayload = DataItemCompoundTagPayload_<2225>;
using DataItemPosPayload = DataItemPosPayload_<2225>;
using DataItemInt64Payload = DataItemInt64Payload_<2225>;
using DataItemVec3Payload = DataItemVec3Payload_<2225>;
using DataItemEntry = DataItemEntry_<2225>;
using SynchedActorData = SynchedActorData_<2225>;
using AddActorPacket = AddActorPacket_<2225>;
using SetActorDataPacket = SetActorDataPacket_<2225>;
using ActorType = ActorType_<2225>;
using SetLastHurtByPacket = SetLastHurtByPacket_<2225>;
using ActorEvent = ActorEvent_<2225>;
using ActorEventPacket = ActorEventPacket_<2225>;
using SetPassengerOfBlockPacket = SetPassengerOfBlockPacket_<2225>;
using AnimatePacket = AnimatePacket_<2225>;
using AddItemActorPacket = AddItemActorPacket_<2225>;

}  // namespace bedrock::protocol
