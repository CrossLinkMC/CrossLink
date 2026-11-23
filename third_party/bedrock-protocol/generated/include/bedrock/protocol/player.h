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

#include <bedrock/protocol/ability.h>
#include <bedrock/protocol/actor.h>
#include <bedrock/protocol/common.h>
#include <bedrock/protocol/game.h>
#include <bedrock/protocol/item.h>
#include <bedrock/protocol/network.h>
#include <bedrock/protocol/skin.h>

namespace bedrock::protocol {

enum class PlayerRespawnState : std::uint8_t {
    SearchingForSpawn = 0,
    ReadyToSpawn = 1,
    ClientReadyToSpawn = 2,
};

struct RespawnPacket {
    static constexpr int Id = 45;
    Vec3 pos{};
    PlayerRespawnState state{};
    ActorRuntimeID runtime_id{};
};

struct SetHealthPacket {
    static constexpr int Id = 42;
    std::int32_t health{};
};

struct AwardAchievementPacket {
    static constexpr int Id = 309;
    std::int32_t achievement_id{};
};

namespace InteractPacket_nested {

enum class Action : std::uint8_t {
    Invalid = 0,
    StopRiding = 3,
    InteractUpdate = 4,
    NpcOpen = 5,
    OpenInventory = 6,
};

}  // namespace InteractPacket_nested

struct InteractPacket {
    using Action = InteractPacket_nested::Action;

    static constexpr int Id = 33;
    InteractPacket::Action action{};
    ActorRuntimeID target_id{};
    std::optional<Vec3> pos{};
};

enum class SpawnPositionType : int {
    PlayerRespawn = 0,
    WorldSpawn = 1,
};

struct SetLocalPlayerAsInitializedPacket {
    static constexpr int Id = 113;
    ActorRuntimeID player_id{};
};

enum class ArmorSlot : int {
    Head = 0,
    Torso = 1,
    Legs = 2,
    Feet = 3,
    Body = 4,
    HumanoidCount = 4,
    Count = 5,
};

struct ArmorSlotAndDamagePair {
    ArmorSlot armor_slot{};
    std::int16_t damage{};
};

struct PlayerFogPacket {
    static constexpr int Id = 160;
    std::vector<std::string> fog_stack{};
};

enum class GraphicsMode : std::uint8_t {
    Simple = 0,
    Fancy = 1,
    Advanced = 2,
    RayTraced = 3,
};

enum class PlayerListPacketType : std::uint8_t {
    Add = 0,
    Remove = 1,
};

enum class BuildPlatform : int {
    Unknown = -1,
    Google = 1,
    IOS = 2,
    OSX = 3,
    Amazon = 4,
    GearVRDeprecated = 5,
    UWPDeprecated = 7,
    Win32 = 8,
    Dedicated = 9,
    TvOSDeprecated = 10,
    Sony = 11,
    Nintendo = 12,
    Xbox = 13,
    WindowsPhoneDeprecated = 14,
    Linux = 15,
};

enum class UpdateType : std::uint8_t {
    ClearOverrides = 0,
    RemoveOverride = 1,
    SetIntOverride = 2,
    SetFloatOverride = 3,
};

namespace base {

enum class ActorDamageCause : int {
    None = -1,
    Override = 0,
    Contact = 1,
    EntityAttack = 2,
    Projectile = 3,
    Suffocation = 4,
    Fall = 5,
    Fire = 6,
    FireTick = 7,
    Lava = 8,
    Drowning = 9,
    BlockExplosion = 10,
    EntityExplosion = 11,
    Void = 12,
    SelfDestruct = 13,
    Magic = 14,
    Wither = 15,
    Starve = 16,
    Anvil = 17,
    Thorns = 18,
    FallingBlock = 19,
    Piston = 20,
    FlyIntoWall = 21,
    Magma = 22,
    Fireworks = 23,
    Lightning = 24,
    Charging = 25,
    Temperature = 26,
    Freezing = 27,
    Stalactite = 28,
    Stalagmite = 29,
    RamAttack = 30,
    SonicBoom = 31,
    Campfire = 32,
    SoulCampfire = 33,
    MaceSmash = 34,
    All = 35,
};

struct HurtArmorPacket {
    static constexpr int Id = 38;
    base::ActorDamageCause cause{};
    std::int32_t dmg{};
    std::uint64_t armor_slots{};
};

struct SetSpawnPositionPacket {
    static constexpr int Id = 43;
    SpawnPositionType spawn_pos_type{};
    base::NetworkBlockPosition pos{};
    DimensionType dimension_type{};
    base::NetworkBlockPosition spawn_block_pos{};
};

struct PlayerArmorDamagePacket {
    static constexpr int Id = 149;
    std::uint8_t slots{};
    std::int32_t head_damage{};
    std::int32_t torso_damage{};
    std::int32_t legs_damage{};
    std::int32_t feet_damage{};
    std::int32_t body_damage{};
};

struct PlayerListEntry {
    UUID uuid{};
    ActorUniqueID id{};
    std::string name{};
    std::string xuid{};
    std::string platform_online_id{};
    BuildPlatform build_platform{};
    legacy::SerializedSkinRef skin{};
    bool is_teacher{};
    bool is_host{};
    bool is_sub_client{};
};

namespace PlayerListPacket_nested {

struct RemoveEntry {
    PlayerListPacketType action{};
    UUID uuid{};
};

struct AddEntry {
    PlayerListPacketType action{};
    UUID uuid{};
    ActorUniqueID id{};
    std::string name{};
    std::string xuid{};
    std::string platform_online_id{};
    BuildPlatform build_platform{};
    base::SerializedSkinRef skin{};
    bool is_teacher{};
    bool is_host{};
    bool is_sub_client{};
    Color color{};
};

}  // namespace PlayerListPacket_nested

struct PlayerListPacket {
    using RemoveEntry = PlayerListPacket_nested::RemoveEntry;
    using AddEntry = PlayerListPacket_nested::AddEntry;

    static constexpr int Id = 63;
    PlayerListPacketType action{};
    std::vector<base::PlayerListEntry> entries{};
    std::vector<UUID> removed_entries{};
    std::vector<bool> trusted_skins{};
};

struct AddPlayerPacket {
    static constexpr int Id = 12;
    UUID uuid{};
    std::string name{};
    ActorRuntimeID runtime_id{};
    std::string platform_online_id{};
    Vec3 pos{};
    Vec3 velocity{};
    Vec2 rot{};
    float y_head_rot{};
    NetworkItemStackDescriptor carried_item{};
    GameType player_game_type{};
    base::SynchedActorData::CopyableDataList unpack{};
    PropertySyncData synched_properties{};
    base::SerializedAbilitiesData abilities_data{};
    std::vector<ActorLink> links{};
    std::string device_id{};
    BuildPlatform build_platform{};
};

}  // namespace base

namespace v748 {

using ActorDamageCause = base::ActorDamageCause;

using HurtArmorPacket = base::HurtArmorPacket;

using SetSpawnPositionPacket = base::SetSpawnPositionPacket;

using PlayerArmorDamagePacket = base::PlayerArmorDamagePacket;

using PlayerListEntry = base::PlayerListEntry;

using PlayerListPacket = base::PlayerListPacket;

using AddPlayerPacket = base::AddPlayerPacket;

}  // namespace v748

namespace v766 {

using ActorDamageCause = base::ActorDamageCause;

using HurtArmorPacket = base::HurtArmorPacket;

using SetSpawnPositionPacket = base::SetSpawnPositionPacket;

using PlayerArmorDamagePacket = base::PlayerArmorDamagePacket;

using PlayerListEntry = base::PlayerListEntry;

using PlayerListPacket = base::PlayerListPacket;

using AddPlayerPacket = base::AddPlayerPacket;

}  // namespace v766

namespace v776 {

using ActorDamageCause = base::ActorDamageCause;

using HurtArmorPacket = base::HurtArmorPacket;

using SetSpawnPositionPacket = base::SetSpawnPositionPacket;

using PlayerArmorDamagePacket = base::PlayerArmorDamagePacket;

using PlayerListEntry = base::PlayerListEntry;

using PlayerListPacket = base::PlayerListPacket;

struct AddPlayerPacket {
    static constexpr int Id = 12;
    UUID uuid{};
    std::string name{};
    ActorRuntimeID runtime_id{};
    std::string platform_online_id{};
    Vec3 pos{};
    Vec3 velocity{};
    Vec2 rot{};
    float y_head_rot{};
    NetworkItemStackDescriptor carried_item{};
    GameType player_game_type{};
    base::SynchedActorData::CopyableDataList unpack{};
    PropertySyncData synched_properties{};
    v776::SerializedAbilitiesData abilities_data{};
    std::vector<ActorLink> links{};
    std::string device_id{};
    BuildPlatform build_platform{};
};

}  // namespace v776

namespace v786 {

using ActorDamageCause = base::ActorDamageCause;

using HurtArmorPacket = base::HurtArmorPacket;

using SetSpawnPositionPacket = base::SetSpawnPositionPacket;

using PlayerArmorDamagePacket = base::PlayerArmorDamagePacket;

struct UpdateClientOptionsPacket {
    static constexpr int Id = 323;
    std::optional<GraphicsMode> graphics_mode{};
};

using PlayerListEntry = base::PlayerListEntry;

using PlayerListPacket = base::PlayerListPacket;

namespace PlayerUpdateEntityOverridesPacket_nested {

struct ClearOverride {
};

struct RemoveOverride {
};

struct IntOverride {
    std::int32_t value{};
};

struct FloatOverride {
    float value{};
};

}  // namespace PlayerUpdateEntityOverridesPacket_nested

struct PlayerUpdateEntityOverridesPacket {
    using ClearOverride = PlayerUpdateEntityOverridesPacket_nested::ClearOverride;
    using RemoveOverride = PlayerUpdateEntityOverridesPacket_nested::RemoveOverride;
    using IntOverride = PlayerUpdateEntityOverridesPacket_nested::IntOverride;
    using FloatOverride = PlayerUpdateEntityOverridesPacket_nested::FloatOverride;

    static constexpr int Id = 325;
    ActorUniqueID id{};
    std::uint32_t property_index{};
    UpdateType update_type{};
    std::int32_t int_value{};
    float float_value{};
};

using AddPlayerPacket = v776::AddPlayerPacket;

}  // namespace v786

namespace v800 {

using ActorDamageCause = base::ActorDamageCause;

using HurtArmorPacket = base::HurtArmorPacket;

using SetSpawnPositionPacket = base::SetSpawnPositionPacket;

using PlayerArmorDamagePacket = base::PlayerArmorDamagePacket;

using UpdateClientOptionsPacket = v786::UpdateClientOptionsPacket;

struct PlayerListEntry {
    UUID uuid{};
    ActorUniqueID id{};
    std::string name{};
    std::string xuid{};
    std::string platform_online_id{};
    BuildPlatform build_platform{};
    legacy::SerializedSkinRef skin{};
    bool is_teacher{};
    bool is_host{};
    bool is_sub_client{};
    Color color{};
};

namespace PlayerListPacket_nested {

using RemoveEntry = base::PlayerListPacket::RemoveEntry;

struct AddEntry {
    PlayerListPacketType action{};
    UUID uuid{};
    ActorUniqueID id{};
    std::string name{};
    std::string xuid{};
    std::string platform_online_id{};
    BuildPlatform build_platform{};
    base::SerializedSkinRef skin{};
    bool is_teacher{};
    bool is_host{};
    bool is_sub_client{};
    Color color{};
};

}  // namespace PlayerListPacket_nested

struct PlayerListPacket {
    using RemoveEntry = PlayerListPacket_nested::RemoveEntry;
    using AddEntry = PlayerListPacket_nested::AddEntry;

    static constexpr int Id = 63;
    PlayerListPacketType action{};
    std::vector<v800::PlayerListEntry> entries{};
    std::vector<UUID> removed_entries{};
    std::vector<bool> trusted_skins{};
};

using PlayerUpdateEntityOverridesPacket = v786::PlayerUpdateEntityOverridesPacket;

namespace PlayerLocationPacket_nested {

enum class Type : int {
    PlayerLocationCoordinates = 0,
    PlayerLocationHide = 1,
};

struct CoordinatesLocation {
    Type type{};
    Vec3 pos{};
};

struct HiddenLocation {
    Type type{};
};

}  // namespace PlayerLocationPacket_nested

struct PlayerLocationPacket {
    using Type = PlayerLocationPacket_nested::Type;
    using CoordinatesLocation = PlayerLocationPacket_nested::CoordinatesLocation;
    using HiddenLocation = PlayerLocationPacket_nested::HiddenLocation;

    static constexpr int Id = 326;
    v800::PlayerLocationPacket::Type type{};
    ActorUniqueID id{};
    Vec3 pos{};
};

using AddPlayerPacket = v776::AddPlayerPacket;

}  // namespace v800

namespace v818 {

using ActorDamageCause = base::ActorDamageCause;

using HurtArmorPacket = base::HurtArmorPacket;

using SetSpawnPositionPacket = base::SetSpawnPositionPacket;

using PlayerArmorDamagePacket = base::PlayerArmorDamagePacket;

using UpdateClientOptionsPacket = v786::UpdateClientOptionsPacket;

using PlayerListEntry = v800::PlayerListEntry;

using PlayerListPacket = v800::PlayerListPacket;

using PlayerUpdateEntityOverridesPacket = v786::PlayerUpdateEntityOverridesPacket;

using PlayerLocationPacket = v800::PlayerLocationPacket;

using AddPlayerPacket = v776::AddPlayerPacket;

}  // namespace v818

namespace v827 {

using ActorDamageCause = base::ActorDamageCause;

using HurtArmorPacket = base::HurtArmorPacket;

using SetSpawnPositionPacket = base::SetSpawnPositionPacket;

using PlayerArmorDamagePacket = base::PlayerArmorDamagePacket;

using UpdateClientOptionsPacket = v786::UpdateClientOptionsPacket;

using PlayerListEntry = v800::PlayerListEntry;

using PlayerListPacket = v800::PlayerListPacket;

using PlayerUpdateEntityOverridesPacket = v786::PlayerUpdateEntityOverridesPacket;

using PlayerLocationPacket = v800::PlayerLocationPacket;

using AddPlayerPacket = v776::AddPlayerPacket;

}  // namespace v827

namespace v844 {

using ActorDamageCause = base::ActorDamageCause;

using HurtArmorPacket = base::HurtArmorPacket;

using SetSpawnPositionPacket = base::SetSpawnPositionPacket;

struct PlayerArmorDamagePacket {
    static constexpr int Id = 149;
    std::vector<ArmorSlotAndDamagePair> slot_and_damage_pairs{};
};

using UpdateClientOptionsPacket = v786::UpdateClientOptionsPacket;

using PlayerListEntry = v800::PlayerListEntry;

using PlayerListPacket = v800::PlayerListPacket;

using PlayerUpdateEntityOverridesPacket = v786::PlayerUpdateEntityOverridesPacket;

using PlayerLocationPacket = v800::PlayerLocationPacket;

using AddPlayerPacket = v776::AddPlayerPacket;

}  // namespace v844

namespace v859 {

using ActorDamageCause = base::ActorDamageCause;

using HurtArmorPacket = base::HurtArmorPacket;

using SetSpawnPositionPacket = base::SetSpawnPositionPacket;

using PlayerArmorDamagePacket = v844::PlayerArmorDamagePacket;

using UpdateClientOptionsPacket = v786::UpdateClientOptionsPacket;

using PlayerListEntry = v800::PlayerListEntry;

using PlayerListPacket = v800::PlayerListPacket;

using PlayerUpdateEntityOverridesPacket = v786::PlayerUpdateEntityOverridesPacket;

using PlayerLocationPacket = v800::PlayerLocationPacket;

using AddPlayerPacket = v776::AddPlayerPacket;

}  // namespace v859

namespace v898 {

enum class ActorDamageCause : int {
    None = -1,
    Override = 0,
    Contact = 1,
    EntityAttack = 2,
    Projectile = 3,
    Suffocation = 4,
    Fall = 5,
    Fire = 6,
    FireTick = 7,
    Lava = 8,
    Drowning = 9,
    BlockExplosion = 10,
    EntityExplosion = 11,
    Void = 12,
    SelfDestruct = 13,
    Magic = 14,
    Wither = 15,
    Starve = 16,
    Anvil = 17,
    Thorns = 18,
    FallingBlock = 19,
    Piston = 20,
    FlyIntoWall = 21,
    Magma = 22,
    Fireworks = 23,
    Lightning = 24,
    Charging = 25,
    Temperature = 26,
    Freezing = 27,
    Stalactite = 28,
    Stalagmite = 29,
    RamAttack = 30,
    SonicBoom = 31,
    Campfire = 32,
    SoulCampfire = 33,
    MaceSmash = 34,
    Dehydration = 35,
    All = 36,
};

struct HurtArmorPacket {
    static constexpr int Id = 38;
    v898::ActorDamageCause cause{};
    std::int32_t dmg{};
    std::uint64_t armor_slots{};
};

using SetSpawnPositionPacket = base::SetSpawnPositionPacket;

using PlayerArmorDamagePacket = v844::PlayerArmorDamagePacket;

using UpdateClientOptionsPacket = v786::UpdateClientOptionsPacket;

using PlayerListEntry = v800::PlayerListEntry;

using PlayerListPacket = v800::PlayerListPacket;

using PlayerUpdateEntityOverridesPacket = v786::PlayerUpdateEntityOverridesPacket;

using PlayerLocationPacket = v800::PlayerLocationPacket;

using AddPlayerPacket = v776::AddPlayerPacket;

}  // namespace v898

namespace v924 {

enum class ActorDamageCause : int {
    None = -1,
    Override = 0,
    Contact = 1,
    EntityAttack = 2,
    Projectile = 3,
    Suffocation = 4,
    Fall = 5,
    Fire = 6,
    FireTick = 7,
    Lava = 8,
    Drowning = 9,
    BlockExplosion = 10,
    EntityExplosion = 11,
    Void = 12,
    SelfDestruct = 13,
    Magic = 14,
    Wither = 15,
    Starve = 16,
    Anvil = 17,
    Thorns = 18,
    FallingBlock = 19,
    Piston = 20,
    FlyIntoWall = 21,
    Magma = 22,
    Fireworks = 23,
    Lightning = 24,
    Charging = 25,
    Temperature = 26,
    Freezing = 27,
    Stalactite = 28,
    Stalagmite = 29,
    RamAttack = 30,
    SonicBoom = 31,
    Campfire = 32,
    SoulCampfire = 33,
    MaceSmash = 34,
    All = 35,
};

struct HurtArmorPacket {
    static constexpr int Id = 38;
    v924::ActorDamageCause cause{};
    std::int32_t dmg{};
    std::uint64_t armor_slots{};
};

using SetSpawnPositionPacket = base::SetSpawnPositionPacket;

using PlayerArmorDamagePacket = v844::PlayerArmorDamagePacket;

using UpdateClientOptionsPacket = v786::UpdateClientOptionsPacket;

using PlayerListEntry = v800::PlayerListEntry;

using PlayerListPacket = v800::PlayerListPacket;

using PlayerUpdateEntityOverridesPacket = v786::PlayerUpdateEntityOverridesPacket;

using PlayerLocationPacket = v800::PlayerLocationPacket;

using AddPlayerPacket = v776::AddPlayerPacket;

}  // namespace v924

namespace v944 {

using ActorDamageCause = v924::ActorDamageCause;

using HurtArmorPacket = v924::HurtArmorPacket;

struct SetSpawnPositionPacket {
    static constexpr int Id = 43;
    SpawnPositionType spawn_pos_type{};
    BlockPos pos{};
    DimensionType dimension_type{};
    BlockPos spawn_block_pos{};
};

using PlayerArmorDamagePacket = v844::PlayerArmorDamagePacket;

using UpdateClientOptionsPacket = v786::UpdateClientOptionsPacket;

using PlayerListEntry = v800::PlayerListEntry;

using PlayerListPacket = v800::PlayerListPacket;

using PlayerUpdateEntityOverridesPacket = v786::PlayerUpdateEntityOverridesPacket;

using PlayerLocationPacket = v800::PlayerLocationPacket;

using AddPlayerPacket = v776::AddPlayerPacket;

}  // namespace v944

namespace v975 {

using ActorDamageCause = v924::ActorDamageCause;

using HurtArmorPacket = v924::HurtArmorPacket;

using SetSpawnPositionPacket = v944::SetSpawnPositionPacket;

using PlayerArmorDamagePacket = v844::PlayerArmorDamagePacket;

struct UpdateClientOptionsPacket {
    static constexpr int Id = 323;
    std::optional<GraphicsMode> graphics_mode{};
    std::optional<bool> filter_profanity{};
};

using PlayerListEntry = v800::PlayerListEntry;

using PlayerListPacket = v800::PlayerListPacket;

using PlayerUpdateEntityOverridesPacket = v786::PlayerUpdateEntityOverridesPacket;

using PlayerLocationPacket = v800::PlayerLocationPacket;

using AddPlayerPacket = v776::AddPlayerPacket;

}  // namespace v975

namespace v1001 {

using ActorDamageCause = v924::ActorDamageCause;

using HurtArmorPacket = v924::HurtArmorPacket;

using SetSpawnPositionPacket = v944::SetSpawnPositionPacket;

using PlayerArmorDamagePacket = v844::PlayerArmorDamagePacket;

using UpdateClientOptionsPacket = v975::UpdateClientOptionsPacket;

using PlayerListEntry = v800::PlayerListEntry;

using PlayerListPacket = v800::PlayerListPacket;

using PlayerUpdateEntityOverridesPacket = v786::PlayerUpdateEntityOverridesPacket;

using PlayerLocationPacket = v800::PlayerLocationPacket;

using AddPlayerPacket = v776::AddPlayerPacket;

}  // namespace v1001

namespace v2168 {

using ActorDamageCause = v924::ActorDamageCause;

using HurtArmorPacket = v924::HurtArmorPacket;

using SetSpawnPositionPacket = v944::SetSpawnPositionPacket;

using PlayerArmorDamagePacket = v844::PlayerArmorDamagePacket;

using UpdateClientOptionsPacket = v975::UpdateClientOptionsPacket;

namespace PlayerListPacket_nested {

using RemoveEntry = base::PlayerListPacket::RemoveEntry;

struct AddEntry {
    PlayerListPacketType action{};
    UUID uuid{};
    ActorUniqueID id{};
    std::string name{};
    std::string xuid{};
    std::string platform_online_id{};
    BuildPlatform build_platform{};
    v2168::SerializedSkinRef skin{};
    bool is_teacher{};
    bool is_host{};
    bool is_sub_client{};
    Color color{};
};

}  // namespace PlayerListPacket_nested

struct PlayerListPacket {
    using RemoveEntry = PlayerListPacket_nested::RemoveEntry;
    using AddEntry = PlayerListPacket_nested::AddEntry;

    static constexpr int Id = 63;
    std::vector<std::variant<v2168::PlayerListPacket::RemoveEntry, v2168::PlayerListPacket::AddEntry>> entries{};
};

namespace PlayerUpdateEntityOverridesPacket_nested {

using ClearOverride = v786::PlayerUpdateEntityOverridesPacket::ClearOverride;
using RemoveOverride = v786::PlayerUpdateEntityOverridesPacket::RemoveOverride;
using IntOverride = v786::PlayerUpdateEntityOverridesPacket::IntOverride;
using FloatOverride = v786::PlayerUpdateEntityOverridesPacket::FloatOverride;

}  // namespace PlayerUpdateEntityOverridesPacket_nested

struct PlayerUpdateEntityOverridesPacket {
    using ClearOverride = PlayerUpdateEntityOverridesPacket_nested::ClearOverride;
    using RemoveOverride = PlayerUpdateEntityOverridesPacket_nested::RemoveOverride;
    using IntOverride = PlayerUpdateEntityOverridesPacket_nested::IntOverride;
    using FloatOverride = PlayerUpdateEntityOverridesPacket_nested::FloatOverride;

    static constexpr int Id = 325;
    ActorUniqueID id{};
    std::uint32_t property_index{};
    std::variant<v2168::PlayerUpdateEntityOverridesPacket::ClearOverride, v2168::PlayerUpdateEntityOverridesPacket::RemoveOverride, v2168::PlayerUpdateEntityOverridesPacket::IntOverride, v2168::PlayerUpdateEntityOverridesPacket::FloatOverride> update{};
};

namespace PlayerLocationPacket_nested {

using Type = v800::PlayerLocationPacket::Type;
using CoordinatesLocation = v800::PlayerLocationPacket::CoordinatesLocation;
using HiddenLocation = v800::PlayerLocationPacket::HiddenLocation;

}  // namespace PlayerLocationPacket_nested

struct PlayerLocationPacket {
    using Type = PlayerLocationPacket_nested::Type;
    using CoordinatesLocation = PlayerLocationPacket_nested::CoordinatesLocation;
    using HiddenLocation = PlayerLocationPacket_nested::HiddenLocation;

    static constexpr int Id = 326;
    ActorUniqueID id{};
    std::variant<v2168::PlayerLocationPacket::CoordinatesLocation, v2168::PlayerLocationPacket::HiddenLocation> location{};
};

struct AddPlayerPacket {
    static constexpr int Id = 12;
    UUID uuid{};
    std::string name{};
    ActorRuntimeID runtime_id{};
    std::string platform_online_id{};
    Vec3 pos{};
    Vec3 velocity{};
    Vec2 rot{};
    float y_head_rot{};
    v2168::SerializedNetworkItemStackDescriptor carried_item{};
    GameType player_game_type{};
    v2168::SynchedActorData::CopyableDataList unpack{};
    PropertySyncData synched_properties{};
    v776::SerializedAbilitiesData abilities_data{};
    std::vector<ActorLink> links{};
    std::string device_id{};
    BuildPlatform build_platform{};
};

}  // namespace v2168

namespace v2193 {

using ActorDamageCause = v924::ActorDamageCause;

using HurtArmorPacket = v924::HurtArmorPacket;

using SetSpawnPositionPacket = v944::SetSpawnPositionPacket;

using PlayerArmorDamagePacket = v844::PlayerArmorDamagePacket;

using UpdateClientOptionsPacket = v975::UpdateClientOptionsPacket;

using PlayerListPacket = v2168::PlayerListPacket;

using PlayerUpdateEntityOverridesPacket = v2168::PlayerUpdateEntityOverridesPacket;

using PlayerLocationPacket = v2168::PlayerLocationPacket;

using AddPlayerPacket = v2168::AddPlayerPacket;

}  // namespace v2193

namespace v2225 {

using ActorDamageCause = v924::ActorDamageCause;

using HurtArmorPacket = v924::HurtArmorPacket;

using SetSpawnPositionPacket = v944::SetSpawnPositionPacket;

using PlayerArmorDamagePacket = v844::PlayerArmorDamagePacket;

using UpdateClientOptionsPacket = v975::UpdateClientOptionsPacket;

namespace PlayerListPacket_nested {

using RemoveEntry = base::PlayerListPacket::RemoveEntry;

struct AddEntry {
    PlayerListPacketType action{};
    UUID uuid{};
    ActorUniqueID id{};
    std::string name{};
    std::string xuid{};
    std::string play_fab_id{};
    std::string platform_online_id{};
    BuildPlatform build_platform{};
    v2225::SerializedSkinRef skin{};
    bool is_teacher{};
    bool is_host{};
    bool is_sub_client{};
    Color color{};
};

}  // namespace PlayerListPacket_nested

struct PlayerListPacket {
    using RemoveEntry = PlayerListPacket_nested::RemoveEntry;
    using AddEntry = PlayerListPacket_nested::AddEntry;

    static constexpr int Id = 63;
    std::vector<std::variant<v2225::PlayerListPacket::RemoveEntry, v2225::PlayerListPacket::AddEntry>> entries{};
};

using PlayerUpdateEntityOverridesPacket = v2168::PlayerUpdateEntityOverridesPacket;

using PlayerLocationPacket = v2168::PlayerLocationPacket;

struct AddPlayerPacket {
    static constexpr int Id = 12;
    UUID uuid{};
    std::string name{};
    ActorRuntimeID runtime_id{};
    std::string platform_online_id{};
    Vec3 pos{};
    Vec3 velocity{};
    Vec2 rot{};
    float y_head_rot{};
    v2168::SerializedNetworkItemStackDescriptor carried_item{};
    GameType player_game_type{};
    v2168::SynchedActorData::CopyableDataList unpack{};
    PropertySyncData synched_properties{};
    v776::SerializedAbilitiesData abilities_data{};
    std::vector<ActorLink> links{};
    std::optional<PassengerOfBlockArguments> passenger_block_data{};
    std::string device_id{};
    BuildPlatform build_platform{};
};

}  // namespace v2225

namespace detail {

template <int V>
struct ActorDamageCause_;

template <int V> requires (V < 898)
struct ActorDamageCause_<V> { using type = base::ActorDamageCause; };

template <int V> requires (V >= 898 && V < 924)
struct ActorDamageCause_<V> { using type = v898::ActorDamageCause; };

template <int V> requires (V >= 924)
struct ActorDamageCause_<V> { using type = v924::ActorDamageCause; };

template <int V>
struct HurtArmorPacket_;

template <int V> requires (V < 898)
struct HurtArmorPacket_<V> { using type = base::HurtArmorPacket; };

template <int V> requires (V >= 898 && V < 924)
struct HurtArmorPacket_<V> { using type = v898::HurtArmorPacket; };

template <int V> requires (V >= 924)
struct HurtArmorPacket_<V> { using type = v924::HurtArmorPacket; };

template <int V>
struct SetSpawnPositionPacket_;

template <int V> requires (V < 944)
struct SetSpawnPositionPacket_<V> { using type = base::SetSpawnPositionPacket; };

template <int V> requires (V >= 944)
struct SetSpawnPositionPacket_<V> { using type = v944::SetSpawnPositionPacket; };

template <int V>
struct PlayerArmorDamagePacket_;

template <int V> requires (V < 844)
struct PlayerArmorDamagePacket_<V> { using type = base::PlayerArmorDamagePacket; };

template <int V> requires (V >= 844)
struct PlayerArmorDamagePacket_<V> { using type = v844::PlayerArmorDamagePacket; };

template <int V>
struct UpdateClientOptionsPacket_;

template <int V> requires (V >= 786 && V < 975)
struct UpdateClientOptionsPacket_<V> { using type = v786::UpdateClientOptionsPacket; };

template <int V> requires (V >= 975)
struct UpdateClientOptionsPacket_<V> { using type = v975::UpdateClientOptionsPacket; };

template <int V>
struct PlayerListEntry_;

template <int V> requires (V < 800)
struct PlayerListEntry_<V> { using type = base::PlayerListEntry; };

template <int V> requires (V >= 800 && V < 2168)
struct PlayerListEntry_<V> { using type = v800::PlayerListEntry; };

template <int V>
struct PlayerListPacket_;

template <int V> requires (V < 800)
struct PlayerListPacket_<V> { using type = base::PlayerListPacket; };

template <int V> requires (V >= 800 && V < 2168)
struct PlayerListPacket_<V> { using type = v800::PlayerListPacket; };

template <int V> requires (V >= 2168 && V < 2225)
struct PlayerListPacket_<V> { using type = v2168::PlayerListPacket; };

template <int V> requires (V >= 2225)
struct PlayerListPacket_<V> { using type = v2225::PlayerListPacket; };

template <int V>
struct PlayerUpdateEntityOverridesPacket_;

template <int V> requires (V >= 786 && V < 2168)
struct PlayerUpdateEntityOverridesPacket_<V> { using type = v786::PlayerUpdateEntityOverridesPacket; };

template <int V> requires (V >= 2168)
struct PlayerUpdateEntityOverridesPacket_<V> { using type = v2168::PlayerUpdateEntityOverridesPacket; };

template <int V>
struct PlayerLocationPacket_;

template <int V> requires (V >= 800 && V < 2168)
struct PlayerLocationPacket_<V> { using type = v800::PlayerLocationPacket; };

template <int V> requires (V >= 2168)
struct PlayerLocationPacket_<V> { using type = v2168::PlayerLocationPacket; };

template <int V>
struct AddPlayerPacket_;

template <int V> requires (V < 776)
struct AddPlayerPacket_<V> { using type = base::AddPlayerPacket; };

template <int V> requires (V >= 776 && V < 2168)
struct AddPlayerPacket_<V> { using type = v776::AddPlayerPacket; };

template <int V> requires (V >= 2168 && V < 2225)
struct AddPlayerPacket_<V> { using type = v2168::AddPlayerPacket; };

template <int V> requires (V >= 2225)
struct AddPlayerPacket_<V> { using type = v2225::AddPlayerPacket; };

}  // namespace detail

template <int V> using ActorDamageCause_ = typename detail::ActorDamageCause_<V>::type;
template <int V> using HurtArmorPacket_ = typename detail::HurtArmorPacket_<V>::type;
template <int V> using SetSpawnPositionPacket_ = typename detail::SetSpawnPositionPacket_<V>::type;
template <int V> using PlayerArmorDamagePacket_ = typename detail::PlayerArmorDamagePacket_<V>::type;
template <int V> using UpdateClientOptionsPacket_ = typename detail::UpdateClientOptionsPacket_<V>::type;
template <int V> using PlayerListEntry_ = typename detail::PlayerListEntry_<V>::type;
template <int V> using PlayerListPacket_ = typename detail::PlayerListPacket_<V>::type;
template <int V> using PlayerUpdateEntityOverridesPacket_ = typename detail::PlayerUpdateEntityOverridesPacket_<V>::type;
template <int V> using PlayerLocationPacket_ = typename detail::PlayerLocationPacket_<V>::type;
template <int V> using AddPlayerPacket_ = typename detail::AddPlayerPacket_<V>::type;

template <int V>
struct packet_of<V, 12> { using type = AddPlayerPacket_<V>; };

template <int V>
struct packet_of<V, 33> { using type = InteractPacket; };

template <int V>
struct packet_of<V, 38> { using type = HurtArmorPacket_<V>; };

template <int V>
struct packet_of<V, 42> { using type = SetHealthPacket; };

template <int V>
struct packet_of<V, 43> { using type = SetSpawnPositionPacket_<V>; };

template <int V>
struct packet_of<V, 45> { using type = RespawnPacket; };

template <int V>
struct packet_of<V, 63> { using type = PlayerListPacket_<V>; };

template <int V>
struct packet_of<V, 113> { using type = SetLocalPlayerAsInitializedPacket; };

template <int V>
struct packet_of<V, 149> { using type = PlayerArmorDamagePacket_<V>; };

template <int V>
struct packet_of<V, 160> { using type = PlayerFogPacket; };

template <int V>
struct packet_of<V, 309> { using type = AwardAchievementPacket; };

template <int V> requires (V >= 786)
struct packet_of<V, 323> { using type = UpdateClientOptionsPacket_<V>; };

template <int V> requires (V >= 786)
struct packet_of<V, 325> { using type = PlayerUpdateEntityOverridesPacket_<V>; };

template <int V> requires (V >= 800)
struct packet_of<V, 326> { using type = PlayerLocationPacket_<V>; };

namespace detail {

template <>
inline constexpr std::array<PlayerRespawnState, 3> values_v<PlayerRespawnState>{{
    PlayerRespawnState::SearchingForSpawn,
    PlayerRespawnState::ReadyToSpawn,
    PlayerRespawnState::ClientReadyToSpawn,
}};

template <>
inline constexpr std::array<std::string_view, 3> names_v<PlayerRespawnState>{{
    "searchingforspawn",
    "readytospawn",
    "clientreadytospawn",
}};

template <>
inline constexpr std::string_view type_name_v<PlayerRespawnState>{"PlayerRespawnState"};

template <>
inline constexpr std::array<base::ActorDamageCause, 37> values_v<base::ActorDamageCause>{{
    base::ActorDamageCause::None,
    base::ActorDamageCause::Override,
    base::ActorDamageCause::Contact,
    base::ActorDamageCause::EntityAttack,
    base::ActorDamageCause::Projectile,
    base::ActorDamageCause::Suffocation,
    base::ActorDamageCause::Fall,
    base::ActorDamageCause::Fire,
    base::ActorDamageCause::FireTick,
    base::ActorDamageCause::Lava,
    base::ActorDamageCause::Drowning,
    base::ActorDamageCause::BlockExplosion,
    base::ActorDamageCause::EntityExplosion,
    base::ActorDamageCause::Void,
    base::ActorDamageCause::SelfDestruct,
    base::ActorDamageCause::Magic,
    base::ActorDamageCause::Wither,
    base::ActorDamageCause::Starve,
    base::ActorDamageCause::Anvil,
    base::ActorDamageCause::Thorns,
    base::ActorDamageCause::FallingBlock,
    base::ActorDamageCause::Piston,
    base::ActorDamageCause::FlyIntoWall,
    base::ActorDamageCause::Magma,
    base::ActorDamageCause::Fireworks,
    base::ActorDamageCause::Lightning,
    base::ActorDamageCause::Charging,
    base::ActorDamageCause::Temperature,
    base::ActorDamageCause::Freezing,
    base::ActorDamageCause::Stalactite,
    base::ActorDamageCause::Stalagmite,
    base::ActorDamageCause::RamAttack,
    base::ActorDamageCause::SonicBoom,
    base::ActorDamageCause::Campfire,
    base::ActorDamageCause::SoulCampfire,
    base::ActorDamageCause::MaceSmash,
    base::ActorDamageCause::All,
}};

template <>
inline constexpr std::array<std::string_view, 37> names_v<base::ActorDamageCause>{{
    "none",
    "override",
    "contact",
    "entityattack",
    "projectile",
    "suffocation",
    "fall",
    "fire",
    "firetick",
    "lava",
    "drowning",
    "blockexplosion",
    "entityexplosion",
    "void",
    "selfdestruct",
    "magic",
    "wither",
    "starve",
    "anvil",
    "thorns",
    "fallingblock",
    "piston",
    "flyintowall",
    "magma",
    "fireworks",
    "lightning",
    "charging",
    "temperature",
    "freezing",
    "stalactite",
    "stalagmite",
    "ramattack",
    "sonicboom",
    "campfire",
    "soulcampfire",
    "macesmash",
    "all",
}};

template <>
inline constexpr std::string_view type_name_v<base::ActorDamageCause>{"ActorDamageCause"};

template <>
inline constexpr std::array<v898::ActorDamageCause, 38> values_v<v898::ActorDamageCause>{{
    v898::ActorDamageCause::None,
    v898::ActorDamageCause::Override,
    v898::ActorDamageCause::Contact,
    v898::ActorDamageCause::EntityAttack,
    v898::ActorDamageCause::Projectile,
    v898::ActorDamageCause::Suffocation,
    v898::ActorDamageCause::Fall,
    v898::ActorDamageCause::Fire,
    v898::ActorDamageCause::FireTick,
    v898::ActorDamageCause::Lava,
    v898::ActorDamageCause::Drowning,
    v898::ActorDamageCause::BlockExplosion,
    v898::ActorDamageCause::EntityExplosion,
    v898::ActorDamageCause::Void,
    v898::ActorDamageCause::SelfDestruct,
    v898::ActorDamageCause::Magic,
    v898::ActorDamageCause::Wither,
    v898::ActorDamageCause::Starve,
    v898::ActorDamageCause::Anvil,
    v898::ActorDamageCause::Thorns,
    v898::ActorDamageCause::FallingBlock,
    v898::ActorDamageCause::Piston,
    v898::ActorDamageCause::FlyIntoWall,
    v898::ActorDamageCause::Magma,
    v898::ActorDamageCause::Fireworks,
    v898::ActorDamageCause::Lightning,
    v898::ActorDamageCause::Charging,
    v898::ActorDamageCause::Temperature,
    v898::ActorDamageCause::Freezing,
    v898::ActorDamageCause::Stalactite,
    v898::ActorDamageCause::Stalagmite,
    v898::ActorDamageCause::RamAttack,
    v898::ActorDamageCause::SonicBoom,
    v898::ActorDamageCause::Campfire,
    v898::ActorDamageCause::SoulCampfire,
    v898::ActorDamageCause::MaceSmash,
    v898::ActorDamageCause::Dehydration,
    v898::ActorDamageCause::All,
}};

template <>
inline constexpr std::array<std::string_view, 38> names_v<v898::ActorDamageCause>{{
    "none",
    "override",
    "contact",
    "entityattack",
    "projectile",
    "suffocation",
    "fall",
    "fire",
    "firetick",
    "lava",
    "drowning",
    "blockexplosion",
    "entityexplosion",
    "void",
    "selfdestruct",
    "magic",
    "wither",
    "starve",
    "anvil",
    "thorns",
    "fallingblock",
    "piston",
    "flyintowall",
    "magma",
    "fireworks",
    "lightning",
    "charging",
    "temperature",
    "freezing",
    "stalactite",
    "stalagmite",
    "ramattack",
    "sonicboom",
    "campfire",
    "soulcampfire",
    "macesmash",
    "dehydration",
    "all",
}};

template <>
inline constexpr std::string_view type_name_v<v898::ActorDamageCause>{"ActorDamageCause"};

template <>
inline constexpr std::array<v924::ActorDamageCause, 37> values_v<v924::ActorDamageCause>{{
    v924::ActorDamageCause::None,
    v924::ActorDamageCause::Override,
    v924::ActorDamageCause::Contact,
    v924::ActorDamageCause::EntityAttack,
    v924::ActorDamageCause::Projectile,
    v924::ActorDamageCause::Suffocation,
    v924::ActorDamageCause::Fall,
    v924::ActorDamageCause::Fire,
    v924::ActorDamageCause::FireTick,
    v924::ActorDamageCause::Lava,
    v924::ActorDamageCause::Drowning,
    v924::ActorDamageCause::BlockExplosion,
    v924::ActorDamageCause::EntityExplosion,
    v924::ActorDamageCause::Void,
    v924::ActorDamageCause::SelfDestruct,
    v924::ActorDamageCause::Magic,
    v924::ActorDamageCause::Wither,
    v924::ActorDamageCause::Starve,
    v924::ActorDamageCause::Anvil,
    v924::ActorDamageCause::Thorns,
    v924::ActorDamageCause::FallingBlock,
    v924::ActorDamageCause::Piston,
    v924::ActorDamageCause::FlyIntoWall,
    v924::ActorDamageCause::Magma,
    v924::ActorDamageCause::Fireworks,
    v924::ActorDamageCause::Lightning,
    v924::ActorDamageCause::Charging,
    v924::ActorDamageCause::Temperature,
    v924::ActorDamageCause::Freezing,
    v924::ActorDamageCause::Stalactite,
    v924::ActorDamageCause::Stalagmite,
    v924::ActorDamageCause::RamAttack,
    v924::ActorDamageCause::SonicBoom,
    v924::ActorDamageCause::Campfire,
    v924::ActorDamageCause::SoulCampfire,
    v924::ActorDamageCause::MaceSmash,
    v924::ActorDamageCause::All,
}};

template <>
inline constexpr std::array<std::string_view, 37> names_v<v924::ActorDamageCause>{{
    "none",
    "override",
    "contact",
    "entityattack",
    "projectile",
    "suffocation",
    "fall",
    "fire",
    "firetick",
    "lava",
    "drowning",
    "blockexplosion",
    "entityexplosion",
    "void",
    "selfdestruct",
    "magic",
    "wither",
    "starve",
    "anvil",
    "thorns",
    "fallingblock",
    "piston",
    "flyintowall",
    "magma",
    "fireworks",
    "lightning",
    "charging",
    "temperature",
    "freezing",
    "stalactite",
    "stalagmite",
    "ramattack",
    "sonicboom",
    "campfire",
    "soulcampfire",
    "macesmash",
    "all",
}};

template <>
inline constexpr std::string_view type_name_v<v924::ActorDamageCause>{"ActorDamageCause"};

template <>
inline constexpr std::array<InteractPacket::Action, 5> values_v<InteractPacket::Action>{{
    InteractPacket::Action::Invalid,
    InteractPacket::Action::StopRiding,
    InteractPacket::Action::InteractUpdate,
    InteractPacket::Action::NpcOpen,
    InteractPacket::Action::OpenInventory,
}};

template <>
inline constexpr std::array<std::string_view, 5> names_v<InteractPacket::Action>{{
    "invalid",
    "stopriding",
    "interactupdate",
    "npcopen",
    "openinventory",
}};

template <>
inline constexpr std::string_view type_name_v<InteractPacket::Action>{"InteractPacket::Action"};

template <>
inline constexpr std::array<SpawnPositionType, 2> values_v<SpawnPositionType>{{
    SpawnPositionType::PlayerRespawn,
    SpawnPositionType::WorldSpawn,
}};

template <>
inline constexpr std::array<std::string_view, 2> names_v<SpawnPositionType>{{
    "playerrespawn",
    "worldspawn",
}};

template <>
inline constexpr std::string_view type_name_v<SpawnPositionType>{"SpawnPositionType"};

template <>
inline constexpr std::array<ArmorSlot, 7> values_v<ArmorSlot>{{
    ArmorSlot::Head,
    ArmorSlot::Torso,
    ArmorSlot::Legs,
    ArmorSlot::Feet,
    ArmorSlot::Body,
    ArmorSlot::HumanoidCount,
    ArmorSlot::Count,
}};

template <>
inline constexpr std::array<std::string_view, 7> names_v<ArmorSlot>{{
    "head",
    "torso",
    "legs",
    "feet",
    "body",
    "humanoidcount",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<ArmorSlot>{"ArmorSlot"};

template <>
inline constexpr std::array<GraphicsMode, 4> values_v<GraphicsMode>{{
    GraphicsMode::Simple,
    GraphicsMode::Fancy,
    GraphicsMode::Advanced,
    GraphicsMode::RayTraced,
}};

template <>
inline constexpr std::array<std::string_view, 4> names_v<GraphicsMode>{{
    "simple",
    "fancy",
    "advanced",
    "raytraced",
}};

template <>
inline constexpr std::string_view type_name_v<GraphicsMode>{"GraphicsMode"};

template <>
inline constexpr std::array<PlayerListPacketType, 2> values_v<PlayerListPacketType>{{
    PlayerListPacketType::Add,
    PlayerListPacketType::Remove,
}};

template <>
inline constexpr std::array<std::string_view, 2> names_v<PlayerListPacketType>{{
    "add",
    "remove",
}};

template <>
inline constexpr std::string_view type_name_v<PlayerListPacketType>{"PlayerListPacketType"};

template <>
inline constexpr std::array<BuildPlatform, 15> values_v<BuildPlatform>{{
    BuildPlatform::Unknown,
    BuildPlatform::Google,
    BuildPlatform::IOS,
    BuildPlatform::OSX,
    BuildPlatform::Amazon,
    BuildPlatform::GearVRDeprecated,
    BuildPlatform::UWPDeprecated,
    BuildPlatform::Win32,
    BuildPlatform::Dedicated,
    BuildPlatform::TvOSDeprecated,
    BuildPlatform::Sony,
    BuildPlatform::Nintendo,
    BuildPlatform::Xbox,
    BuildPlatform::WindowsPhoneDeprecated,
    BuildPlatform::Linux,
}};

template <>
inline constexpr std::array<std::string_view, 15> names_v<BuildPlatform>{{
    "unknown",
    "google",
    "ios",
    "osx",
    "amazon",
    "gearvrdeprecated",
    "uwpdeprecated",
    "win32",
    "dedicated",
    "tvosdeprecated",
    "sony",
    "nintendo",
    "xbox",
    "windowsphonedeprecated",
    "linux",
}};

template <>
inline constexpr std::string_view type_name_v<BuildPlatform>{"BuildPlatform"};

template <>
inline constexpr std::array<UpdateType, 4> values_v<UpdateType>{{
    UpdateType::ClearOverrides,
    UpdateType::RemoveOverride,
    UpdateType::SetIntOverride,
    UpdateType::SetFloatOverride,
}};

template <>
inline constexpr std::array<std::string_view, 4> names_v<UpdateType>{{
    "clearoverrides",
    "removeoverride",
    "setintoverride",
    "setfloatoverride",
}};

template <>
inline constexpr std::string_view type_name_v<UpdateType>{"UpdateType"};

template <>
inline constexpr std::array<v800::PlayerLocationPacket::Type, 2> values_v<v800::PlayerLocationPacket::Type>{{
    v800::PlayerLocationPacket::Type::PlayerLocationCoordinates,
    v800::PlayerLocationPacket::Type::PlayerLocationHide,
}};

template <>
inline constexpr std::array<std::string_view, 2> names_v<v800::PlayerLocationPacket::Type>{{
    "playerlocationcoordinates",
    "playerlocationhide",
}};

template <>
inline constexpr std::string_view type_name_v<v800::PlayerLocationPacket::Type>{"PlayerLocationPacket::Type"};

}  // namespace detail

namespace detail {

template <>
inline constexpr bool is_reflected_struct_v<RespawnPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<RespawnPacket>{"RespawnPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<RespawnPacket>{{
    "pos",
    "state",
    "runtime_id",
}};

template <>
struct field_accessor<RespawnPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.pos;
        }
        else if constexpr (I == 1) {
            return value.state;
        }
        else {
            return value.runtime_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::HurtArmorPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::HurtArmorPacket>{"HurtArmorPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<base::HurtArmorPacket>{{
    "cause",
    "dmg",
    "armor_slots",
}};

template <>
struct field_accessor<base::HurtArmorPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.cause;
        }
        else if constexpr (I == 1) {
            return value.dmg;
        }
        else {
            return value.armor_slots;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v898::HurtArmorPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v898::HurtArmorPacket>{"HurtArmorPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v898::HurtArmorPacket>{{
    "cause",
    "dmg",
    "armor_slots",
}};

template <>
struct field_accessor<v898::HurtArmorPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.cause;
        }
        else if constexpr (I == 1) {
            return value.dmg;
        }
        else {
            return value.armor_slots;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::HurtArmorPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::HurtArmorPacket>{"HurtArmorPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v924::HurtArmorPacket>{{
    "cause",
    "dmg",
    "armor_slots",
}};

template <>
struct field_accessor<v924::HurtArmorPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.cause;
        }
        else if constexpr (I == 1) {
            return value.dmg;
        }
        else {
            return value.armor_slots;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<SetHealthPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<SetHealthPacket>{"SetHealthPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<SetHealthPacket>{{
    "health",
}};

template <>
struct field_accessor<SetHealthPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.health;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<AwardAchievementPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<AwardAchievementPacket>{"AwardAchievementPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<AwardAchievementPacket>{{
    "achievement_id",
}};

template <>
struct field_accessor<AwardAchievementPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.achievement_id;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<InteractPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<InteractPacket>{"InteractPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<InteractPacket>{{
    "action",
    "target_id",
    "pos",
}};

template <>
struct field_accessor<InteractPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.action;
        }
        else if constexpr (I == 1) {
            return value.target_id;
        }
        else {
            return value.pos;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::SetSpawnPositionPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::SetSpawnPositionPacket>{"SetSpawnPositionPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<base::SetSpawnPositionPacket>{{
    "spawn_pos_type",
    "pos",
    "dimension_type",
    "spawn_block_pos",
}};

template <>
struct field_accessor<base::SetSpawnPositionPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.spawn_pos_type;
        }
        else if constexpr (I == 1) {
            return value.pos;
        }
        else if constexpr (I == 2) {
            return value.dimension_type;
        }
        else {
            return value.spawn_block_pos;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::SetSpawnPositionPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::SetSpawnPositionPacket>{"SetSpawnPositionPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v944::SetSpawnPositionPacket>{{
    "spawn_pos_type",
    "pos",
    "dimension_type",
    "spawn_block_pos",
}};

template <>
struct field_accessor<v944::SetSpawnPositionPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.spawn_pos_type;
        }
        else if constexpr (I == 1) {
            return value.pos;
        }
        else if constexpr (I == 2) {
            return value.dimension_type;
        }
        else {
            return value.spawn_block_pos;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<SetLocalPlayerAsInitializedPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<SetLocalPlayerAsInitializedPacket>{"SetLocalPlayerAsInitializedPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<SetLocalPlayerAsInitializedPacket>{{
    "player_id",
}};

template <>
struct field_accessor<SetLocalPlayerAsInitializedPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.player_id;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<ArmorSlotAndDamagePair> = true;

template <>
inline constexpr std::string_view struct_name_v<ArmorSlotAndDamagePair>{"ArmorSlotAndDamagePair"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<ArmorSlotAndDamagePair>{{
    "armor_slot",
    "damage",
}};

template <>
struct field_accessor<ArmorSlotAndDamagePair> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.armor_slot;
        }
        else {
            return value.damage;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::PlayerArmorDamagePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::PlayerArmorDamagePacket>{"PlayerArmorDamagePacket"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<base::PlayerArmorDamagePacket>{{
    "slots",
    "head_damage",
    "torso_damage",
    "legs_damage",
    "feet_damage",
    "body_damage",
}};

template <>
struct field_accessor<base::PlayerArmorDamagePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.slots;
        }
        else if constexpr (I == 1) {
            return value.head_damage;
        }
        else if constexpr (I == 2) {
            return value.torso_damage;
        }
        else if constexpr (I == 3) {
            return value.legs_damage;
        }
        else if constexpr (I == 4) {
            return value.feet_damage;
        }
        else {
            return value.body_damage;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v844::PlayerArmorDamagePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v844::PlayerArmorDamagePacket>{"PlayerArmorDamagePacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v844::PlayerArmorDamagePacket>{{
    "slot_and_damage_pairs",
}};

template <>
struct field_accessor<v844::PlayerArmorDamagePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.slot_and_damage_pairs;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<PlayerFogPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<PlayerFogPacket>{"PlayerFogPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<PlayerFogPacket>{{
    "fog_stack",
}};

template <>
struct field_accessor<PlayerFogPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.fog_stack;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v786::UpdateClientOptionsPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v786::UpdateClientOptionsPacket>{"UpdateClientOptionsPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v786::UpdateClientOptionsPacket>{{
    "graphics_mode",
}};

template <>
struct field_accessor<v786::UpdateClientOptionsPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.graphics_mode;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v975::UpdateClientOptionsPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v975::UpdateClientOptionsPacket>{"UpdateClientOptionsPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v975::UpdateClientOptionsPacket>{{
    "graphics_mode",
    "filter_profanity",
}};

template <>
struct field_accessor<v975::UpdateClientOptionsPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.graphics_mode;
        }
        else {
            return value.filter_profanity;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::PlayerListEntry> = true;

template <>
inline constexpr std::string_view struct_name_v<base::PlayerListEntry>{"PlayerListEntry"};

template <>
inline constexpr std::array<std::string_view, 10> field_names_v<base::PlayerListEntry>{{
    "uuid",
    "id",
    "name",
    "xuid",
    "platform_online_id",
    "build_platform",
    "skin",
    "is_teacher",
    "is_host",
    "is_sub_client",
}};

template <>
struct field_accessor<base::PlayerListEntry> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.uuid;
        }
        else if constexpr (I == 1) {
            return value.id;
        }
        else if constexpr (I == 2) {
            return value.name;
        }
        else if constexpr (I == 3) {
            return value.xuid;
        }
        else if constexpr (I == 4) {
            return value.platform_online_id;
        }
        else if constexpr (I == 5) {
            return value.build_platform;
        }
        else if constexpr (I == 6) {
            return value.skin;
        }
        else if constexpr (I == 7) {
            return value.is_teacher;
        }
        else if constexpr (I == 8) {
            return value.is_host;
        }
        else {
            return value.is_sub_client;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v800::PlayerListEntry> = true;

template <>
inline constexpr std::string_view struct_name_v<v800::PlayerListEntry>{"PlayerListEntry"};

template <>
inline constexpr std::array<std::string_view, 11> field_names_v<v800::PlayerListEntry>{{
    "uuid",
    "id",
    "name",
    "xuid",
    "platform_online_id",
    "build_platform",
    "skin",
    "is_teacher",
    "is_host",
    "is_sub_client",
    "color",
}};

template <>
struct field_accessor<v800::PlayerListEntry> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.uuid;
        }
        else if constexpr (I == 1) {
            return value.id;
        }
        else if constexpr (I == 2) {
            return value.name;
        }
        else if constexpr (I == 3) {
            return value.xuid;
        }
        else if constexpr (I == 4) {
            return value.platform_online_id;
        }
        else if constexpr (I == 5) {
            return value.build_platform;
        }
        else if constexpr (I == 6) {
            return value.skin;
        }
        else if constexpr (I == 7) {
            return value.is_teacher;
        }
        else if constexpr (I == 8) {
            return value.is_host;
        }
        else if constexpr (I == 9) {
            return value.is_sub_client;
        }
        else {
            return value.color;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::PlayerListPacket::RemoveEntry> = true;

template <>
inline constexpr std::string_view struct_name_v<base::PlayerListPacket::RemoveEntry>{"PlayerListPacket::RemoveEntry"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<base::PlayerListPacket::RemoveEntry>{{
    "action",
    "uuid",
}};

template <>
struct field_accessor<base::PlayerListPacket::RemoveEntry> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.action;
        }
        else {
            return value.uuid;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::PlayerListPacket::AddEntry> = true;

template <>
inline constexpr std::string_view struct_name_v<base::PlayerListPacket::AddEntry>{"PlayerListPacket::AddEntry"};

template <>
inline constexpr std::array<std::string_view, 12> field_names_v<base::PlayerListPacket::AddEntry>{{
    "action",
    "uuid",
    "id",
    "name",
    "xuid",
    "platform_online_id",
    "build_platform",
    "skin",
    "is_teacher",
    "is_host",
    "is_sub_client",
    "color",
}};

template <>
struct field_accessor<base::PlayerListPacket::AddEntry> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.action;
        }
        else if constexpr (I == 1) {
            return value.uuid;
        }
        else if constexpr (I == 2) {
            return value.id;
        }
        else if constexpr (I == 3) {
            return value.name;
        }
        else if constexpr (I == 4) {
            return value.xuid;
        }
        else if constexpr (I == 5) {
            return value.platform_online_id;
        }
        else if constexpr (I == 6) {
            return value.build_platform;
        }
        else if constexpr (I == 7) {
            return value.skin;
        }
        else if constexpr (I == 8) {
            return value.is_teacher;
        }
        else if constexpr (I == 9) {
            return value.is_host;
        }
        else if constexpr (I == 10) {
            return value.is_sub_client;
        }
        else {
            return value.color;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v800::PlayerListPacket::AddEntry> = true;

template <>
inline constexpr std::string_view struct_name_v<v800::PlayerListPacket::AddEntry>{"PlayerListPacket::AddEntry"};

template <>
inline constexpr std::array<std::string_view, 12> field_names_v<v800::PlayerListPacket::AddEntry>{{
    "action",
    "uuid",
    "id",
    "name",
    "xuid",
    "platform_online_id",
    "build_platform",
    "skin",
    "is_teacher",
    "is_host",
    "is_sub_client",
    "color",
}};

template <>
struct field_accessor<v800::PlayerListPacket::AddEntry> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.action;
        }
        else if constexpr (I == 1) {
            return value.uuid;
        }
        else if constexpr (I == 2) {
            return value.id;
        }
        else if constexpr (I == 3) {
            return value.name;
        }
        else if constexpr (I == 4) {
            return value.xuid;
        }
        else if constexpr (I == 5) {
            return value.platform_online_id;
        }
        else if constexpr (I == 6) {
            return value.build_platform;
        }
        else if constexpr (I == 7) {
            return value.skin;
        }
        else if constexpr (I == 8) {
            return value.is_teacher;
        }
        else if constexpr (I == 9) {
            return value.is_host;
        }
        else if constexpr (I == 10) {
            return value.is_sub_client;
        }
        else {
            return value.color;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::PlayerListPacket::AddEntry> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::PlayerListPacket::AddEntry>{"PlayerListPacket::AddEntry"};

template <>
inline constexpr std::array<std::string_view, 12> field_names_v<v2168::PlayerListPacket::AddEntry>{{
    "action",
    "uuid",
    "id",
    "name",
    "xuid",
    "platform_online_id",
    "build_platform",
    "skin",
    "is_teacher",
    "is_host",
    "is_sub_client",
    "color",
}};

template <>
struct field_accessor<v2168::PlayerListPacket::AddEntry> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.action;
        }
        else if constexpr (I == 1) {
            return value.uuid;
        }
        else if constexpr (I == 2) {
            return value.id;
        }
        else if constexpr (I == 3) {
            return value.name;
        }
        else if constexpr (I == 4) {
            return value.xuid;
        }
        else if constexpr (I == 5) {
            return value.platform_online_id;
        }
        else if constexpr (I == 6) {
            return value.build_platform;
        }
        else if constexpr (I == 7) {
            return value.skin;
        }
        else if constexpr (I == 8) {
            return value.is_teacher;
        }
        else if constexpr (I == 9) {
            return value.is_host;
        }
        else if constexpr (I == 10) {
            return value.is_sub_client;
        }
        else {
            return value.color;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::PlayerListPacket::AddEntry> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::PlayerListPacket::AddEntry>{"PlayerListPacket::AddEntry"};

template <>
inline constexpr std::array<std::string_view, 13> field_names_v<v2225::PlayerListPacket::AddEntry>{{
    "action",
    "uuid",
    "id",
    "name",
    "xuid",
    "play_fab_id",
    "platform_online_id",
    "build_platform",
    "skin",
    "is_teacher",
    "is_host",
    "is_sub_client",
    "color",
}};

template <>
struct field_accessor<v2225::PlayerListPacket::AddEntry> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.action;
        }
        else if constexpr (I == 1) {
            return value.uuid;
        }
        else if constexpr (I == 2) {
            return value.id;
        }
        else if constexpr (I == 3) {
            return value.name;
        }
        else if constexpr (I == 4) {
            return value.xuid;
        }
        else if constexpr (I == 5) {
            return value.play_fab_id;
        }
        else if constexpr (I == 6) {
            return value.platform_online_id;
        }
        else if constexpr (I == 7) {
            return value.build_platform;
        }
        else if constexpr (I == 8) {
            return value.skin;
        }
        else if constexpr (I == 9) {
            return value.is_teacher;
        }
        else if constexpr (I == 10) {
            return value.is_host;
        }
        else if constexpr (I == 11) {
            return value.is_sub_client;
        }
        else {
            return value.color;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::PlayerListPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::PlayerListPacket>{"PlayerListPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<base::PlayerListPacket>{{
    "action",
    "entries",
    "removed_entries",
    "trusted_skins",
}};

template <>
struct field_accessor<base::PlayerListPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.action;
        }
        else if constexpr (I == 1) {
            return value.entries;
        }
        else if constexpr (I == 2) {
            return value.removed_entries;
        }
        else {
            return value.trusted_skins;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v800::PlayerListPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v800::PlayerListPacket>{"PlayerListPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v800::PlayerListPacket>{{
    "action",
    "entries",
    "removed_entries",
    "trusted_skins",
}};

template <>
struct field_accessor<v800::PlayerListPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.action;
        }
        else if constexpr (I == 1) {
            return value.entries;
        }
        else if constexpr (I == 2) {
            return value.removed_entries;
        }
        else {
            return value.trusted_skins;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::PlayerListPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::PlayerListPacket>{"PlayerListPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2168::PlayerListPacket>{{
    "entries",
}};

template <>
struct field_accessor<v2168::PlayerListPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.entries;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::PlayerListPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::PlayerListPacket>{"PlayerListPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2225::PlayerListPacket>{{
    "entries",
}};

template <>
struct field_accessor<v2225::PlayerListPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.entries;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v786::PlayerUpdateEntityOverridesPacket::ClearOverride> = true;

template <>
inline constexpr std::string_view struct_name_v<v786::PlayerUpdateEntityOverridesPacket::ClearOverride>{"PlayerUpdateEntityOverridesPacket::ClearOverride"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<v786::PlayerUpdateEntityOverridesPacket::ClearOverride>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<v786::PlayerUpdateEntityOverridesPacket::RemoveOverride> = true;

template <>
inline constexpr std::string_view struct_name_v<v786::PlayerUpdateEntityOverridesPacket::RemoveOverride>{"PlayerUpdateEntityOverridesPacket::RemoveOverride"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<v786::PlayerUpdateEntityOverridesPacket::RemoveOverride>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<v786::PlayerUpdateEntityOverridesPacket::IntOverride> = true;

template <>
inline constexpr std::string_view struct_name_v<v786::PlayerUpdateEntityOverridesPacket::IntOverride>{"PlayerUpdateEntityOverridesPacket::IntOverride"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v786::PlayerUpdateEntityOverridesPacket::IntOverride>{{
    "value",
}};

template <>
struct field_accessor<v786::PlayerUpdateEntityOverridesPacket::IntOverride> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.value;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v786::PlayerUpdateEntityOverridesPacket::FloatOverride> = true;

template <>
inline constexpr std::string_view struct_name_v<v786::PlayerUpdateEntityOverridesPacket::FloatOverride>{"PlayerUpdateEntityOverridesPacket::FloatOverride"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v786::PlayerUpdateEntityOverridesPacket::FloatOverride>{{
    "value",
}};

template <>
struct field_accessor<v786::PlayerUpdateEntityOverridesPacket::FloatOverride> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.value;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v786::PlayerUpdateEntityOverridesPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v786::PlayerUpdateEntityOverridesPacket>{"PlayerUpdateEntityOverridesPacket"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v786::PlayerUpdateEntityOverridesPacket>{{
    "id",
    "property_index",
    "update_type",
    "int_value",
    "float_value",
}};

template <>
struct field_accessor<v786::PlayerUpdateEntityOverridesPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.id;
        }
        else if constexpr (I == 1) {
            return value.property_index;
        }
        else if constexpr (I == 2) {
            return value.update_type;
        }
        else if constexpr (I == 3) {
            return value.int_value;
        }
        else {
            return value.float_value;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::PlayerUpdateEntityOverridesPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::PlayerUpdateEntityOverridesPacket>{"PlayerUpdateEntityOverridesPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v2168::PlayerUpdateEntityOverridesPacket>{{
    "id",
    "property_index",
    "update",
}};

template <>
struct field_accessor<v2168::PlayerUpdateEntityOverridesPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.id;
        }
        else if constexpr (I == 1) {
            return value.property_index;
        }
        else {
            return value.update;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v800::PlayerLocationPacket::CoordinatesLocation> = true;

template <>
inline constexpr std::string_view struct_name_v<v800::PlayerLocationPacket::CoordinatesLocation>{"PlayerLocationPacket::CoordinatesLocation"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v800::PlayerLocationPacket::CoordinatesLocation>{{
    "type",
    "pos",
}};

template <>
struct field_accessor<v800::PlayerLocationPacket::CoordinatesLocation> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.type;
        }
        else {
            return value.pos;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v800::PlayerLocationPacket::HiddenLocation> = true;

template <>
inline constexpr std::string_view struct_name_v<v800::PlayerLocationPacket::HiddenLocation>{"PlayerLocationPacket::HiddenLocation"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v800::PlayerLocationPacket::HiddenLocation>{{
    "type",
}};

template <>
struct field_accessor<v800::PlayerLocationPacket::HiddenLocation> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.type;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v800::PlayerLocationPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v800::PlayerLocationPacket>{"PlayerLocationPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v800::PlayerLocationPacket>{{
    "type",
    "id",
    "pos",
}};

template <>
struct field_accessor<v800::PlayerLocationPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.type;
        }
        else if constexpr (I == 1) {
            return value.id;
        }
        else {
            return value.pos;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::PlayerLocationPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::PlayerLocationPacket>{"PlayerLocationPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2168::PlayerLocationPacket>{{
    "id",
    "location",
}};

template <>
struct field_accessor<v2168::PlayerLocationPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.id;
        }
        else {
            return value.location;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::AddPlayerPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::AddPlayerPacket>{"AddPlayerPacket"};

template <>
inline constexpr std::array<std::string_view, 16> field_names_v<base::AddPlayerPacket>{{
    "uuid",
    "name",
    "runtime_id",
    "platform_online_id",
    "pos",
    "velocity",
    "rot",
    "y_head_rot",
    "carried_item",
    "player_game_type",
    "unpack",
    "synched_properties",
    "abilities_data",
    "links",
    "device_id",
    "build_platform",
}};

template <>
struct field_accessor<base::AddPlayerPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.uuid;
        }
        else if constexpr (I == 1) {
            return value.name;
        }
        else if constexpr (I == 2) {
            return value.runtime_id;
        }
        else if constexpr (I == 3) {
            return value.platform_online_id;
        }
        else if constexpr (I == 4) {
            return value.pos;
        }
        else if constexpr (I == 5) {
            return value.velocity;
        }
        else if constexpr (I == 6) {
            return value.rot;
        }
        else if constexpr (I == 7) {
            return value.y_head_rot;
        }
        else if constexpr (I == 8) {
            return value.carried_item;
        }
        else if constexpr (I == 9) {
            return value.player_game_type;
        }
        else if constexpr (I == 10) {
            return value.unpack;
        }
        else if constexpr (I == 11) {
            return value.synched_properties;
        }
        else if constexpr (I == 12) {
            return value.abilities_data;
        }
        else if constexpr (I == 13) {
            return value.links;
        }
        else if constexpr (I == 14) {
            return value.device_id;
        }
        else {
            return value.build_platform;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v776::AddPlayerPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v776::AddPlayerPacket>{"AddPlayerPacket"};

template <>
inline constexpr std::array<std::string_view, 16> field_names_v<v776::AddPlayerPacket>{{
    "uuid",
    "name",
    "runtime_id",
    "platform_online_id",
    "pos",
    "velocity",
    "rot",
    "y_head_rot",
    "carried_item",
    "player_game_type",
    "unpack",
    "synched_properties",
    "abilities_data",
    "links",
    "device_id",
    "build_platform",
}};

template <>
struct field_accessor<v776::AddPlayerPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.uuid;
        }
        else if constexpr (I == 1) {
            return value.name;
        }
        else if constexpr (I == 2) {
            return value.runtime_id;
        }
        else if constexpr (I == 3) {
            return value.platform_online_id;
        }
        else if constexpr (I == 4) {
            return value.pos;
        }
        else if constexpr (I == 5) {
            return value.velocity;
        }
        else if constexpr (I == 6) {
            return value.rot;
        }
        else if constexpr (I == 7) {
            return value.y_head_rot;
        }
        else if constexpr (I == 8) {
            return value.carried_item;
        }
        else if constexpr (I == 9) {
            return value.player_game_type;
        }
        else if constexpr (I == 10) {
            return value.unpack;
        }
        else if constexpr (I == 11) {
            return value.synched_properties;
        }
        else if constexpr (I == 12) {
            return value.abilities_data;
        }
        else if constexpr (I == 13) {
            return value.links;
        }
        else if constexpr (I == 14) {
            return value.device_id;
        }
        else {
            return value.build_platform;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::AddPlayerPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::AddPlayerPacket>{"AddPlayerPacket"};

template <>
inline constexpr std::array<std::string_view, 16> field_names_v<v2168::AddPlayerPacket>{{
    "uuid",
    "name",
    "runtime_id",
    "platform_online_id",
    "pos",
    "velocity",
    "rot",
    "y_head_rot",
    "carried_item",
    "player_game_type",
    "unpack",
    "synched_properties",
    "abilities_data",
    "links",
    "device_id",
    "build_platform",
}};

template <>
struct field_accessor<v2168::AddPlayerPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.uuid;
        }
        else if constexpr (I == 1) {
            return value.name;
        }
        else if constexpr (I == 2) {
            return value.runtime_id;
        }
        else if constexpr (I == 3) {
            return value.platform_online_id;
        }
        else if constexpr (I == 4) {
            return value.pos;
        }
        else if constexpr (I == 5) {
            return value.velocity;
        }
        else if constexpr (I == 6) {
            return value.rot;
        }
        else if constexpr (I == 7) {
            return value.y_head_rot;
        }
        else if constexpr (I == 8) {
            return value.carried_item;
        }
        else if constexpr (I == 9) {
            return value.player_game_type;
        }
        else if constexpr (I == 10) {
            return value.unpack;
        }
        else if constexpr (I == 11) {
            return value.synched_properties;
        }
        else if constexpr (I == 12) {
            return value.abilities_data;
        }
        else if constexpr (I == 13) {
            return value.links;
        }
        else if constexpr (I == 14) {
            return value.device_id;
        }
        else {
            return value.build_platform;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::AddPlayerPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::AddPlayerPacket>{"AddPlayerPacket"};

template <>
inline constexpr std::array<std::string_view, 17> field_names_v<v2225::AddPlayerPacket>{{
    "uuid",
    "name",
    "runtime_id",
    "platform_online_id",
    "pos",
    "velocity",
    "rot",
    "y_head_rot",
    "carried_item",
    "player_game_type",
    "unpack",
    "synched_properties",
    "abilities_data",
    "links",
    "passenger_block_data",
    "device_id",
    "build_platform",
}};

template <>
struct field_accessor<v2225::AddPlayerPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.uuid;
        }
        else if constexpr (I == 1) {
            return value.name;
        }
        else if constexpr (I == 2) {
            return value.runtime_id;
        }
        else if constexpr (I == 3) {
            return value.platform_online_id;
        }
        else if constexpr (I == 4) {
            return value.pos;
        }
        else if constexpr (I == 5) {
            return value.velocity;
        }
        else if constexpr (I == 6) {
            return value.rot;
        }
        else if constexpr (I == 7) {
            return value.y_head_rot;
        }
        else if constexpr (I == 8) {
            return value.carried_item;
        }
        else if constexpr (I == 9) {
            return value.player_game_type;
        }
        else if constexpr (I == 10) {
            return value.unpack;
        }
        else if constexpr (I == 11) {
            return value.synched_properties;
        }
        else if constexpr (I == 12) {
            return value.abilities_data;
        }
        else if constexpr (I == 13) {
            return value.links;
        }
        else if constexpr (I == 14) {
            return value.passenger_block_data;
        }
        else if constexpr (I == 15) {
            return value.device_id;
        }
        else {
            return value.build_platform;
        }
    }
};

}  // namespace detail


template <>
struct Serializer<RespawnPacket> {
    static void serialize(BinaryWriter &stream, const RespawnPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<RespawnPacket, std::error_code>;
};

template <>
struct Serializer<base::HurtArmorPacket> {
    static void serialize(BinaryWriter &stream, const base::HurtArmorPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::HurtArmorPacket, std::error_code>;
};

template <>
struct Serializer<v898::HurtArmorPacket> {
    static void serialize(BinaryWriter &stream, const v898::HurtArmorPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v898::HurtArmorPacket, std::error_code>;
};

template <>
struct Serializer<v924::HurtArmorPacket> {
    static void serialize(BinaryWriter &stream, const v924::HurtArmorPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::HurtArmorPacket, std::error_code>;
};

template <>
struct Serializer<SetHealthPacket> {
    static void serialize(BinaryWriter &stream, const SetHealthPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<SetHealthPacket, std::error_code>;
};

template <>
struct Serializer<AwardAchievementPacket> {
    static void serialize(BinaryWriter &stream, const AwardAchievementPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<AwardAchievementPacket, std::error_code>;
};

template <>
struct Serializer<InteractPacket> {
    static void serialize(BinaryWriter &stream, const InteractPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<InteractPacket, std::error_code>;
};

template <>
struct Serializer<base::SetSpawnPositionPacket> {
    static void serialize(BinaryWriter &stream, const base::SetSpawnPositionPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::SetSpawnPositionPacket, std::error_code>;
};

template <>
struct Serializer<v944::SetSpawnPositionPacket> {
    static void serialize(BinaryWriter &stream, const v944::SetSpawnPositionPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::SetSpawnPositionPacket, std::error_code>;
};

template <>
struct Serializer<SetLocalPlayerAsInitializedPacket> {
    static void serialize(BinaryWriter &stream, const SetLocalPlayerAsInitializedPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<SetLocalPlayerAsInitializedPacket, std::error_code>;
};

template <>
struct Serializer<ArmorSlotAndDamagePair> {
    static void serialize(BinaryWriter &stream, const ArmorSlotAndDamagePair &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<ArmorSlotAndDamagePair, std::error_code>;
};

template <>
struct Serializer<base::PlayerArmorDamagePacket> {
    static void serialize(BinaryWriter &stream, const base::PlayerArmorDamagePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::PlayerArmorDamagePacket, std::error_code>;
};

template <>
struct Serializer<v844::PlayerArmorDamagePacket> {
    static void serialize(BinaryWriter &stream, const v844::PlayerArmorDamagePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v844::PlayerArmorDamagePacket, std::error_code>;
};

template <>
struct Serializer<PlayerFogPacket> {
    static void serialize(BinaryWriter &stream, const PlayerFogPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<PlayerFogPacket, std::error_code>;
};

template <>
struct Serializer<v786::UpdateClientOptionsPacket> {
    static void serialize(BinaryWriter &stream, const v786::UpdateClientOptionsPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v786::UpdateClientOptionsPacket, std::error_code>;
};

template <>
struct Serializer<v975::UpdateClientOptionsPacket> {
    static void serialize(BinaryWriter &stream, const v975::UpdateClientOptionsPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v975::UpdateClientOptionsPacket, std::error_code>;
};

template <>
struct Serializer<base::PlayerListEntry> {
    static void serialize(BinaryWriter &stream, const base::PlayerListEntry &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::PlayerListEntry, std::error_code>;
};

template <>
struct Serializer<v800::PlayerListEntry> {
    static void serialize(BinaryWriter &stream, const v800::PlayerListEntry &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v800::PlayerListEntry, std::error_code>;
};

template <>
struct Serializer<base::PlayerListPacket::RemoveEntry> {
    static void serialize(BinaryWriter &stream, const base::PlayerListPacket::RemoveEntry &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::PlayerListPacket::RemoveEntry, std::error_code>;
};

template <>
struct Serializer<base::PlayerListPacket::AddEntry> {
    static void serialize(BinaryWriter &stream, const base::PlayerListPacket::AddEntry &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::PlayerListPacket::AddEntry, std::error_code>;
};

template <>
struct Serializer<v800::PlayerListPacket::AddEntry> {
    static void serialize(BinaryWriter &stream, const v800::PlayerListPacket::AddEntry &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v800::PlayerListPacket::AddEntry, std::error_code>;
};

template <>
struct Serializer<v2168::PlayerListPacket::AddEntry> {
    static void serialize(BinaryWriter &stream, const v2168::PlayerListPacket::AddEntry &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::PlayerListPacket::AddEntry, std::error_code>;
};

template <>
struct Serializer<v2225::PlayerListPacket::AddEntry> {
    static void serialize(BinaryWriter &stream, const v2225::PlayerListPacket::AddEntry &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::PlayerListPacket::AddEntry, std::error_code>;
};

template <>
struct Serializer<base::PlayerListPacket> {
    static void serialize(BinaryWriter &stream, const base::PlayerListPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::PlayerListPacket, std::error_code>;
};

template <>
struct Serializer<v800::PlayerListPacket> {
    static void serialize(BinaryWriter &stream, const v800::PlayerListPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v800::PlayerListPacket, std::error_code>;
};

template <>
struct Serializer<v2168::PlayerListPacket> {
    static void serialize(BinaryWriter &stream, const v2168::PlayerListPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::PlayerListPacket, std::error_code>;
};

template <>
struct Serializer<v2225::PlayerListPacket> {
    static void serialize(BinaryWriter &stream, const v2225::PlayerListPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::PlayerListPacket, std::error_code>;
};

template <>
struct Serializer<v786::PlayerUpdateEntityOverridesPacket::ClearOverride> {
    static void serialize(BinaryWriter &stream, const v786::PlayerUpdateEntityOverridesPacket::ClearOverride &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v786::PlayerUpdateEntityOverridesPacket::ClearOverride, std::error_code>;
};

template <>
struct Serializer<v786::PlayerUpdateEntityOverridesPacket::RemoveOverride> {
    static void serialize(BinaryWriter &stream, const v786::PlayerUpdateEntityOverridesPacket::RemoveOverride &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v786::PlayerUpdateEntityOverridesPacket::RemoveOverride, std::error_code>;
};

template <>
struct Serializer<v786::PlayerUpdateEntityOverridesPacket::IntOverride> {
    static void serialize(BinaryWriter &stream, const v786::PlayerUpdateEntityOverridesPacket::IntOverride &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v786::PlayerUpdateEntityOverridesPacket::IntOverride, std::error_code>;
};

template <>
struct Serializer<v786::PlayerUpdateEntityOverridesPacket::FloatOverride> {
    static void serialize(BinaryWriter &stream, const v786::PlayerUpdateEntityOverridesPacket::FloatOverride &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v786::PlayerUpdateEntityOverridesPacket::FloatOverride, std::error_code>;
};

template <>
struct Serializer<v786::PlayerUpdateEntityOverridesPacket> {
    static void serialize(BinaryWriter &stream, const v786::PlayerUpdateEntityOverridesPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v786::PlayerUpdateEntityOverridesPacket, std::error_code>;
};

template <>
struct Serializer<v2168::PlayerUpdateEntityOverridesPacket> {
    static void serialize(BinaryWriter &stream, const v2168::PlayerUpdateEntityOverridesPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::PlayerUpdateEntityOverridesPacket, std::error_code>;
};

template <>
struct Serializer<v800::PlayerLocationPacket::CoordinatesLocation> {
    static void serialize(BinaryWriter &stream, const v800::PlayerLocationPacket::CoordinatesLocation &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v800::PlayerLocationPacket::CoordinatesLocation, std::error_code>;
};

template <>
struct Serializer<v800::PlayerLocationPacket::HiddenLocation> {
    static void serialize(BinaryWriter &stream, const v800::PlayerLocationPacket::HiddenLocation &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v800::PlayerLocationPacket::HiddenLocation, std::error_code>;
};

template <>
struct Serializer<v800::PlayerLocationPacket> {
    static void serialize(BinaryWriter &stream, const v800::PlayerLocationPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v800::PlayerLocationPacket, std::error_code>;
};

template <>
struct Serializer<v2168::PlayerLocationPacket> {
    static void serialize(BinaryWriter &stream, const v2168::PlayerLocationPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::PlayerLocationPacket, std::error_code>;
};

template <>
struct Serializer<base::AddPlayerPacket> {
    static void serialize(BinaryWriter &stream, const base::AddPlayerPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::AddPlayerPacket, std::error_code>;
};

template <>
struct Serializer<v776::AddPlayerPacket> {
    static void serialize(BinaryWriter &stream, const v776::AddPlayerPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v776::AddPlayerPacket, std::error_code>;
};

template <>
struct Serializer<v2168::AddPlayerPacket> {
    static void serialize(BinaryWriter &stream, const v2168::AddPlayerPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::AddPlayerPacket, std::error_code>;
};

template <>
struct Serializer<v2225::AddPlayerPacket> {
    static void serialize(BinaryWriter &stream, const v2225::AddPlayerPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::AddPlayerPacket, std::error_code>;
};
using ActorDamageCause = ActorDamageCause_<2225>;
using HurtArmorPacket = HurtArmorPacket_<2225>;
using SetSpawnPositionPacket = SetSpawnPositionPacket_<2225>;
using PlayerArmorDamagePacket = PlayerArmorDamagePacket_<2225>;
using UpdateClientOptionsPacket = UpdateClientOptionsPacket_<2225>;
using PlayerListPacket = PlayerListPacket_<2225>;
using PlayerUpdateEntityOverridesPacket = PlayerUpdateEntityOverridesPacket_<2225>;
using PlayerLocationPacket = PlayerLocationPacket_<2225>;
using AddPlayerPacket = AddPlayerPacket_<2225>;

}  // namespace bedrock::protocol
