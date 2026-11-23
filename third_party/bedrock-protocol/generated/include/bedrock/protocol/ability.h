#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <expected>
#include <string_view>
#include <system_error>
#include <vector>

#include <bedrock/protocol/detail/reflect.hpp>
#include <bedrock/protocol/enum.hpp>
#include <bedrock/protocol/packet.hpp>
#include <bedrock/protocol/serializer.hpp>
#include <bedrock/protocol/stream.hpp>

#include <bedrock/protocol/actor.h>
#include <bedrock/protocol/command.h>

namespace bedrock::protocol {

namespace RequestPermissionsPacket_nested {

enum class CustomPermissions : std::uint16_t {
    Build = 1,
    Mine = 2,
    DoorsAndSwitches = 4,
    OpenContainers = 8,
    AttackPlayers = 16,
    AttackMobs = 32,
    OperatorCommands = 64,
    Teleport = 128,
};

}  // namespace RequestPermissionsPacket_nested

struct RequestPermissionsPacket {
    using CustomPermissions = RequestPermissionsPacket_nested::CustomPermissions;

    static constexpr int Id = 185;
    ActorUniqueID target_player_id{};
    PlayerPermissionLevel player_permissions{};
    std::uint16_t custom_permission_flags{};
};

struct AdventureSettings {
    bool no_pv_m{};
    bool no_mv_p{};
    bool immutable_world{};
    bool show_name_tags{};
    bool auto_jump{};
};

struct UpdateAdventureSettingsPacket {
    static constexpr int Id = 188;
    AdventureSettings adventure_settings{};
};

namespace base {

enum class AbilitiesIndex : std::int8_t {
    Invalid = -1,
    Build = 0,
    Mine = 1,
    DoorsAndSwitches = 2,
    OpenContainers = 3,
    AttackPlayers = 4,
    AttackMobs = 5,
    OperatorCommands = 6,
    Teleport = 7,
    Invulnerable = 8,
    Flying = 9,
    MayFly = 10,
    Instabuild = 11,
    Lightning = 12,
    FlySpeed = 13,
    WalkSpeed = 14,
    Muted = 15,
    WorldBuilder = 16,
    NoClip = 17,
    PrivilegedBuilder = 18,
    AbilityCount = 19,
};

namespace RequestAbilityPacket_nested {

enum class Type : std::uint8_t {
    Unset = 0,
    Bool = 1,
    Float = 2,
};

}  // namespace RequestAbilityPacket_nested

struct RequestAbilityPacket {
    using Type = RequestAbilityPacket_nested::Type;

    static constexpr int Id = 184;
    base::AbilitiesIndex ability{};
    base::RequestAbilityPacket::Type value_type{};
    bool bool_{};
    float float_{};
};

namespace SerializedAbilitiesData_nested {

enum class SerializedAbilitiesLayer : std::uint16_t {
    CustomCache = 0,
    Base = 1,
    Spectator = 2,
    Commands = 3,
    Editor = 4,
    LoadingScreen = 5,
};

struct SerializedLayer {
    SerializedAbilitiesLayer serialized_layer{};
    std::uint32_t abilities_set{};
    std::uint32_t ability_values{};
    float fly_speed{};
    float walk_speed{};
};

}  // namespace SerializedAbilitiesData_nested

struct SerializedAbilitiesData {
    using SerializedAbilitiesLayer = SerializedAbilitiesData_nested::SerializedAbilitiesLayer;
    using SerializedLayer = SerializedAbilitiesData_nested::SerializedLayer;

    ActorUniqueID target_player{};
    PlayerPermissionLevel player_permissions{};
    CommandPermissionLevel command_permissions{};
    std::vector<base::SerializedAbilitiesData::SerializedLayer> layers{};
};

struct UpdateAbilitiesPacket {
    static constexpr int Id = 187;
    base::SerializedAbilitiesData data{};
};

}  // namespace base

namespace v748 {

using AbilitiesIndex = base::AbilitiesIndex;

using RequestAbilityPacket = base::RequestAbilityPacket;

using SerializedAbilitiesData = base::SerializedAbilitiesData;

using UpdateAbilitiesPacket = base::UpdateAbilitiesPacket;

}  // namespace v748

namespace v766 {

using AbilitiesIndex = base::AbilitiesIndex;

using RequestAbilityPacket = base::RequestAbilityPacket;

using SerializedAbilitiesData = base::SerializedAbilitiesData;

using UpdateAbilitiesPacket = base::UpdateAbilitiesPacket;

}  // namespace v766

namespace v776 {

enum class AbilitiesIndex : std::int8_t {
    Invalid = -1,
    Build = 0,
    Mine = 1,
    DoorsAndSwitches = 2,
    OpenContainers = 3,
    AttackPlayers = 4,
    AttackMobs = 5,
    OperatorCommands = 6,
    Teleport = 7,
    Invulnerable = 8,
    Flying = 9,
    MayFly = 10,
    Instabuild = 11,
    Lightning = 12,
    FlySpeed = 13,
    WalkSpeed = 14,
    Muted = 15,
    WorldBuilder = 16,
    NoClip = 17,
    PrivilegedBuilder = 18,
    VerticalFlySpeed = 19,
    AbilityCount = 20,
};

namespace RequestAbilityPacket_nested {

using Type = base::RequestAbilityPacket::Type;

}  // namespace RequestAbilityPacket_nested

struct RequestAbilityPacket {
    using Type = RequestAbilityPacket_nested::Type;

    static constexpr int Id = 184;
    v776::AbilitiesIndex ability{};
    v776::RequestAbilityPacket::Type value_type{};
    bool bool_{};
    float float_{};
};

namespace SerializedAbilitiesData_nested {

using SerializedAbilitiesLayer = base::SerializedAbilitiesData::SerializedAbilitiesLayer;

struct SerializedLayer {
    SerializedAbilitiesLayer serialized_layer{};
    std::uint32_t abilities_set{};
    std::uint32_t ability_values{};
    float fly_speed{};
    float vertical_fly_speed{};
    float walk_speed{};
};

}  // namespace SerializedAbilitiesData_nested

struct SerializedAbilitiesData {
    using SerializedAbilitiesLayer = SerializedAbilitiesData_nested::SerializedAbilitiesLayer;
    using SerializedLayer = SerializedAbilitiesData_nested::SerializedLayer;

    ActorUniqueID target_player{};
    PlayerPermissionLevel player_permissions{};
    CommandPermissionLevel command_permissions{};
    std::vector<v776::SerializedAbilitiesData::SerializedLayer> layers{};
};

struct UpdateAbilitiesPacket {
    static constexpr int Id = 187;
    v776::SerializedAbilitiesData data{};
};

}  // namespace v776

namespace v786 {

using AbilitiesIndex = v776::AbilitiesIndex;

using RequestAbilityPacket = v776::RequestAbilityPacket;

using SerializedAbilitiesData = v776::SerializedAbilitiesData;

using UpdateAbilitiesPacket = v776::UpdateAbilitiesPacket;

}  // namespace v786

namespace v800 {

using AbilitiesIndex = v776::AbilitiesIndex;

using RequestAbilityPacket = v776::RequestAbilityPacket;

using SerializedAbilitiesData = v776::SerializedAbilitiesData;

using UpdateAbilitiesPacket = v776::UpdateAbilitiesPacket;

}  // namespace v800

namespace v818 {

using AbilitiesIndex = v776::AbilitiesIndex;

using RequestAbilityPacket = v776::RequestAbilityPacket;

using SerializedAbilitiesData = v776::SerializedAbilitiesData;

using UpdateAbilitiesPacket = v776::UpdateAbilitiesPacket;

}  // namespace v818

namespace v827 {

using AbilitiesIndex = v776::AbilitiesIndex;

using RequestAbilityPacket = v776::RequestAbilityPacket;

using SerializedAbilitiesData = v776::SerializedAbilitiesData;

using UpdateAbilitiesPacket = v776::UpdateAbilitiesPacket;

}  // namespace v827

namespace v844 {

using AbilitiesIndex = v776::AbilitiesIndex;

using RequestAbilityPacket = v776::RequestAbilityPacket;

using SerializedAbilitiesData = v776::SerializedAbilitiesData;

using UpdateAbilitiesPacket = v776::UpdateAbilitiesPacket;

}  // namespace v844

namespace v859 {

using AbilitiesIndex = v776::AbilitiesIndex;

using RequestAbilityPacket = v776::RequestAbilityPacket;

using SerializedAbilitiesData = v776::SerializedAbilitiesData;

using UpdateAbilitiesPacket = v776::UpdateAbilitiesPacket;

}  // namespace v859

namespace v898 {

using AbilitiesIndex = v776::AbilitiesIndex;

using RequestAbilityPacket = v776::RequestAbilityPacket;

using SerializedAbilitiesData = v776::SerializedAbilitiesData;

using UpdateAbilitiesPacket = v776::UpdateAbilitiesPacket;

}  // namespace v898

namespace v924 {

using AbilitiesIndex = v776::AbilitiesIndex;

using RequestAbilityPacket = v776::RequestAbilityPacket;

using SerializedAbilitiesData = v776::SerializedAbilitiesData;

using UpdateAbilitiesPacket = v776::UpdateAbilitiesPacket;

}  // namespace v924

namespace v944 {

using AbilitiesIndex = v776::AbilitiesIndex;

using RequestAbilityPacket = v776::RequestAbilityPacket;

using SerializedAbilitiesData = v776::SerializedAbilitiesData;

using UpdateAbilitiesPacket = v776::UpdateAbilitiesPacket;

}  // namespace v944

namespace v975 {

using AbilitiesIndex = v776::AbilitiesIndex;

using RequestAbilityPacket = v776::RequestAbilityPacket;

using SerializedAbilitiesData = v776::SerializedAbilitiesData;

using UpdateAbilitiesPacket = v776::UpdateAbilitiesPacket;

}  // namespace v975

namespace v1001 {

using AbilitiesIndex = v776::AbilitiesIndex;

using RequestAbilityPacket = v776::RequestAbilityPacket;

using SerializedAbilitiesData = v776::SerializedAbilitiesData;

using UpdateAbilitiesPacket = v776::UpdateAbilitiesPacket;

}  // namespace v1001

namespace v2168 {

using AbilitiesIndex = v776::AbilitiesIndex;

using RequestAbilityPacket = v776::RequestAbilityPacket;

using SerializedAbilitiesData = v776::SerializedAbilitiesData;

using UpdateAbilitiesPacket = v776::UpdateAbilitiesPacket;

}  // namespace v2168

namespace v2193 {

using AbilitiesIndex = v776::AbilitiesIndex;

using RequestAbilityPacket = v776::RequestAbilityPacket;

using SerializedAbilitiesData = v776::SerializedAbilitiesData;

using UpdateAbilitiesPacket = v776::UpdateAbilitiesPacket;

}  // namespace v2193

namespace v2225 {

using AbilitiesIndex = v776::AbilitiesIndex;

using RequestAbilityPacket = v776::RequestAbilityPacket;

using SerializedAbilitiesData = v776::SerializedAbilitiesData;

using UpdateAbilitiesPacket = v776::UpdateAbilitiesPacket;

}  // namespace v2225

namespace detail {

template <int V>
struct AbilitiesIndex_;

template <int V> requires (V < 776)
struct AbilitiesIndex_<V> { using type = base::AbilitiesIndex; };

template <int V> requires (V >= 776)
struct AbilitiesIndex_<V> { using type = v776::AbilitiesIndex; };

template <int V>
struct RequestAbilityPacket_;

template <int V> requires (V < 776)
struct RequestAbilityPacket_<V> { using type = base::RequestAbilityPacket; };

template <int V> requires (V >= 776)
struct RequestAbilityPacket_<V> { using type = v776::RequestAbilityPacket; };

template <int V>
struct SerializedAbilitiesData_;

template <int V> requires (V < 776)
struct SerializedAbilitiesData_<V> { using type = base::SerializedAbilitiesData; };

template <int V> requires (V >= 776)
struct SerializedAbilitiesData_<V> { using type = v776::SerializedAbilitiesData; };

template <int V>
struct UpdateAbilitiesPacket_;

template <int V> requires (V < 776)
struct UpdateAbilitiesPacket_<V> { using type = base::UpdateAbilitiesPacket; };

template <int V> requires (V >= 776)
struct UpdateAbilitiesPacket_<V> { using type = v776::UpdateAbilitiesPacket; };

}  // namespace detail

template <int V> using AbilitiesIndex_ = typename detail::AbilitiesIndex_<V>::type;
template <int V> using RequestAbilityPacket_ = typename detail::RequestAbilityPacket_<V>::type;
template <int V> using SerializedAbilitiesData_ = typename detail::SerializedAbilitiesData_<V>::type;
template <int V> using UpdateAbilitiesPacket_ = typename detail::UpdateAbilitiesPacket_<V>::type;

template <int V>
struct packet_of<V, 184> { using type = RequestAbilityPacket_<V>; };

template <int V>
struct packet_of<V, 185> { using type = RequestPermissionsPacket; };

template <int V>
struct packet_of<V, 187> { using type = UpdateAbilitiesPacket_<V>; };

template <int V>
struct packet_of<V, 188> { using type = UpdateAdventureSettingsPacket; };

namespace detail {

template <>
inline constexpr std::array<RequestPermissionsPacket::CustomPermissions, 8> values_v<RequestPermissionsPacket::CustomPermissions>{{
    RequestPermissionsPacket::CustomPermissions::Build,
    RequestPermissionsPacket::CustomPermissions::Mine,
    RequestPermissionsPacket::CustomPermissions::DoorsAndSwitches,
    RequestPermissionsPacket::CustomPermissions::OpenContainers,
    RequestPermissionsPacket::CustomPermissions::AttackPlayers,
    RequestPermissionsPacket::CustomPermissions::AttackMobs,
    RequestPermissionsPacket::CustomPermissions::OperatorCommands,
    RequestPermissionsPacket::CustomPermissions::Teleport,
}};

template <>
inline constexpr std::array<std::string_view, 8> names_v<RequestPermissionsPacket::CustomPermissions>{{
    "build",
    "mine",
    "doorsandswitches",
    "opencontainers",
    "attackplayers",
    "attackmobs",
    "operatorcommands",
    "teleport",
}};

template <>
inline constexpr std::string_view type_name_v<RequestPermissionsPacket::CustomPermissions>{"RequestPermissionsPacket::CustomPermissions"};

template <>
inline constexpr std::array<base::AbilitiesIndex, 21> values_v<base::AbilitiesIndex>{{
    base::AbilitiesIndex::Invalid,
    base::AbilitiesIndex::Build,
    base::AbilitiesIndex::Mine,
    base::AbilitiesIndex::DoorsAndSwitches,
    base::AbilitiesIndex::OpenContainers,
    base::AbilitiesIndex::AttackPlayers,
    base::AbilitiesIndex::AttackMobs,
    base::AbilitiesIndex::OperatorCommands,
    base::AbilitiesIndex::Teleport,
    base::AbilitiesIndex::Invulnerable,
    base::AbilitiesIndex::Flying,
    base::AbilitiesIndex::MayFly,
    base::AbilitiesIndex::Instabuild,
    base::AbilitiesIndex::Lightning,
    base::AbilitiesIndex::FlySpeed,
    base::AbilitiesIndex::WalkSpeed,
    base::AbilitiesIndex::Muted,
    base::AbilitiesIndex::WorldBuilder,
    base::AbilitiesIndex::NoClip,
    base::AbilitiesIndex::PrivilegedBuilder,
    base::AbilitiesIndex::AbilityCount,
}};

template <>
inline constexpr std::array<std::string_view, 21> names_v<base::AbilitiesIndex>{{
    "invalid",
    "build",
    "mine",
    "doorsandswitches",
    "opencontainers",
    "attackplayers",
    "attackmobs",
    "operatorcommands",
    "teleport",
    "invulnerable",
    "flying",
    "mayfly",
    "instabuild",
    "lightning",
    "flyspeed",
    "walkspeed",
    "muted",
    "worldbuilder",
    "noclip",
    "privilegedbuilder",
    "abilitycount",
}};

template <>
inline constexpr std::string_view type_name_v<base::AbilitiesIndex>{"AbilitiesIndex"};

template <>
inline constexpr std::array<v776::AbilitiesIndex, 22> values_v<v776::AbilitiesIndex>{{
    v776::AbilitiesIndex::Invalid,
    v776::AbilitiesIndex::Build,
    v776::AbilitiesIndex::Mine,
    v776::AbilitiesIndex::DoorsAndSwitches,
    v776::AbilitiesIndex::OpenContainers,
    v776::AbilitiesIndex::AttackPlayers,
    v776::AbilitiesIndex::AttackMobs,
    v776::AbilitiesIndex::OperatorCommands,
    v776::AbilitiesIndex::Teleport,
    v776::AbilitiesIndex::Invulnerable,
    v776::AbilitiesIndex::Flying,
    v776::AbilitiesIndex::MayFly,
    v776::AbilitiesIndex::Instabuild,
    v776::AbilitiesIndex::Lightning,
    v776::AbilitiesIndex::FlySpeed,
    v776::AbilitiesIndex::WalkSpeed,
    v776::AbilitiesIndex::Muted,
    v776::AbilitiesIndex::WorldBuilder,
    v776::AbilitiesIndex::NoClip,
    v776::AbilitiesIndex::PrivilegedBuilder,
    v776::AbilitiesIndex::VerticalFlySpeed,
    v776::AbilitiesIndex::AbilityCount,
}};

template <>
inline constexpr std::array<std::string_view, 22> names_v<v776::AbilitiesIndex>{{
    "invalid",
    "build",
    "mine",
    "doorsandswitches",
    "opencontainers",
    "attackplayers",
    "attackmobs",
    "operatorcommands",
    "teleport",
    "invulnerable",
    "flying",
    "mayfly",
    "instabuild",
    "lightning",
    "flyspeed",
    "walkspeed",
    "muted",
    "worldbuilder",
    "noclip",
    "privilegedbuilder",
    "verticalflyspeed",
    "abilitycount",
}};

template <>
inline constexpr std::string_view type_name_v<v776::AbilitiesIndex>{"AbilitiesIndex"};

template <>
inline constexpr std::array<base::RequestAbilityPacket::Type, 3> values_v<base::RequestAbilityPacket::Type>{{
    base::RequestAbilityPacket::Type::Unset,
    base::RequestAbilityPacket::Type::Bool,
    base::RequestAbilityPacket::Type::Float,
}};

template <>
inline constexpr std::array<std::string_view, 3> names_v<base::RequestAbilityPacket::Type>{{
    "unset",
    "bool",
    "float",
}};

template <>
inline constexpr std::string_view type_name_v<base::RequestAbilityPacket::Type>{"RequestAbilityPacket::Type"};

template <>
inline constexpr std::array<base::SerializedAbilitiesData::SerializedAbilitiesLayer, 6> values_v<base::SerializedAbilitiesData::SerializedAbilitiesLayer>{{
    base::SerializedAbilitiesData::SerializedAbilitiesLayer::CustomCache,
    base::SerializedAbilitiesData::SerializedAbilitiesLayer::Base,
    base::SerializedAbilitiesData::SerializedAbilitiesLayer::Spectator,
    base::SerializedAbilitiesData::SerializedAbilitiesLayer::Commands,
    base::SerializedAbilitiesData::SerializedAbilitiesLayer::Editor,
    base::SerializedAbilitiesData::SerializedAbilitiesLayer::LoadingScreen,
}};

template <>
inline constexpr std::array<std::string_view, 6> names_v<base::SerializedAbilitiesData::SerializedAbilitiesLayer>{{
    "customcache",
    "base",
    "spectator",
    "commands",
    "editor",
    "loadingscreen",
}};

template <>
inline constexpr std::string_view type_name_v<base::SerializedAbilitiesData::SerializedAbilitiesLayer>{"SerializedAbilitiesData::SerializedAbilitiesLayer"};

}  // namespace detail

namespace detail {

template <>
inline constexpr bool is_reflected_struct_v<RequestPermissionsPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<RequestPermissionsPacket>{"RequestPermissionsPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<RequestPermissionsPacket>{{
    "target_player_id",
    "player_permissions",
    "custom_permission_flags",
}};

template <>
struct field_accessor<RequestPermissionsPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.target_player_id;
        }
        else if constexpr (I == 1) {
            return value.player_permissions;
        }
        else {
            return value.custom_permission_flags;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<AdventureSettings> = true;

template <>
inline constexpr std::string_view struct_name_v<AdventureSettings>{"AdventureSettings"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<AdventureSettings>{{
    "no_pv_m",
    "no_mv_p",
    "immutable_world",
    "show_name_tags",
    "auto_jump",
}};

template <>
struct field_accessor<AdventureSettings> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.no_pv_m;
        }
        else if constexpr (I == 1) {
            return value.no_mv_p;
        }
        else if constexpr (I == 2) {
            return value.immutable_world;
        }
        else if constexpr (I == 3) {
            return value.show_name_tags;
        }
        else {
            return value.auto_jump;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<UpdateAdventureSettingsPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<UpdateAdventureSettingsPacket>{"UpdateAdventureSettingsPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<UpdateAdventureSettingsPacket>{{
    "adventure_settings",
}};

template <>
struct field_accessor<UpdateAdventureSettingsPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.adventure_settings;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::RequestAbilityPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::RequestAbilityPacket>{"RequestAbilityPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<base::RequestAbilityPacket>{{
    "ability",
    "value_type",
    "bool_",
    "float_",
}};

template <>
struct field_accessor<base::RequestAbilityPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.ability;
        }
        else if constexpr (I == 1) {
            return value.value_type;
        }
        else if constexpr (I == 2) {
            return value.bool_;
        }
        else {
            return value.float_;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v776::RequestAbilityPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v776::RequestAbilityPacket>{"RequestAbilityPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v776::RequestAbilityPacket>{{
    "ability",
    "value_type",
    "bool_",
    "float_",
}};

template <>
struct field_accessor<v776::RequestAbilityPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.ability;
        }
        else if constexpr (I == 1) {
            return value.value_type;
        }
        else if constexpr (I == 2) {
            return value.bool_;
        }
        else {
            return value.float_;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::SerializedAbilitiesData::SerializedLayer> = true;

template <>
inline constexpr std::string_view struct_name_v<base::SerializedAbilitiesData::SerializedLayer>{"SerializedAbilitiesData::SerializedLayer"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<base::SerializedAbilitiesData::SerializedLayer>{{
    "serialized_layer",
    "abilities_set",
    "ability_values",
    "fly_speed",
    "walk_speed",
}};

template <>
struct field_accessor<base::SerializedAbilitiesData::SerializedLayer> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.serialized_layer;
        }
        else if constexpr (I == 1) {
            return value.abilities_set;
        }
        else if constexpr (I == 2) {
            return value.ability_values;
        }
        else if constexpr (I == 3) {
            return value.fly_speed;
        }
        else {
            return value.walk_speed;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v776::SerializedAbilitiesData::SerializedLayer> = true;

template <>
inline constexpr std::string_view struct_name_v<v776::SerializedAbilitiesData::SerializedLayer>{"SerializedAbilitiesData::SerializedLayer"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<v776::SerializedAbilitiesData::SerializedLayer>{{
    "serialized_layer",
    "abilities_set",
    "ability_values",
    "fly_speed",
    "vertical_fly_speed",
    "walk_speed",
}};

template <>
struct field_accessor<v776::SerializedAbilitiesData::SerializedLayer> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.serialized_layer;
        }
        else if constexpr (I == 1) {
            return value.abilities_set;
        }
        else if constexpr (I == 2) {
            return value.ability_values;
        }
        else if constexpr (I == 3) {
            return value.fly_speed;
        }
        else if constexpr (I == 4) {
            return value.vertical_fly_speed;
        }
        else {
            return value.walk_speed;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::SerializedAbilitiesData> = true;

template <>
inline constexpr std::string_view struct_name_v<base::SerializedAbilitiesData>{"SerializedAbilitiesData"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<base::SerializedAbilitiesData>{{
    "target_player",
    "player_permissions",
    "command_permissions",
    "layers",
}};

template <>
struct field_accessor<base::SerializedAbilitiesData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.target_player;
        }
        else if constexpr (I == 1) {
            return value.player_permissions;
        }
        else if constexpr (I == 2) {
            return value.command_permissions;
        }
        else {
            return value.layers;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v776::SerializedAbilitiesData> = true;

template <>
inline constexpr std::string_view struct_name_v<v776::SerializedAbilitiesData>{"SerializedAbilitiesData"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v776::SerializedAbilitiesData>{{
    "target_player",
    "player_permissions",
    "command_permissions",
    "layers",
}};

template <>
struct field_accessor<v776::SerializedAbilitiesData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.target_player;
        }
        else if constexpr (I == 1) {
            return value.player_permissions;
        }
        else if constexpr (I == 2) {
            return value.command_permissions;
        }
        else {
            return value.layers;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::UpdateAbilitiesPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::UpdateAbilitiesPacket>{"UpdateAbilitiesPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::UpdateAbilitiesPacket>{{
    "data",
}};

template <>
struct field_accessor<base::UpdateAbilitiesPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.data;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v776::UpdateAbilitiesPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v776::UpdateAbilitiesPacket>{"UpdateAbilitiesPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v776::UpdateAbilitiesPacket>{{
    "data",
}};

template <>
struct field_accessor<v776::UpdateAbilitiesPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.data;
    }
};

}  // namespace detail


template <>
struct Serializer<RequestPermissionsPacket> {
    static void serialize(BinaryWriter &stream, const RequestPermissionsPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<RequestPermissionsPacket, std::error_code>;
};

template <>
struct Serializer<AdventureSettings> {
    static void serialize(BinaryWriter &stream, const AdventureSettings &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<AdventureSettings, std::error_code>;
};

template <>
struct Serializer<UpdateAdventureSettingsPacket> {
    static void serialize(BinaryWriter &stream, const UpdateAdventureSettingsPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<UpdateAdventureSettingsPacket, std::error_code>;
};

template <>
struct Serializer<base::RequestAbilityPacket> {
    static void serialize(BinaryWriter &stream, const base::RequestAbilityPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::RequestAbilityPacket, std::error_code>;
};

template <>
struct Serializer<v776::RequestAbilityPacket> {
    static void serialize(BinaryWriter &stream, const v776::RequestAbilityPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v776::RequestAbilityPacket, std::error_code>;
};

template <>
struct Serializer<base::SerializedAbilitiesData::SerializedLayer> {
    static void serialize(BinaryWriter &stream, const base::SerializedAbilitiesData::SerializedLayer &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::SerializedAbilitiesData::SerializedLayer, std::error_code>;
};

template <>
struct Serializer<v776::SerializedAbilitiesData::SerializedLayer> {
    static void serialize(BinaryWriter &stream, const v776::SerializedAbilitiesData::SerializedLayer &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v776::SerializedAbilitiesData::SerializedLayer, std::error_code>;
};

template <>
struct Serializer<base::SerializedAbilitiesData> {
    static void serialize(BinaryWriter &stream, const base::SerializedAbilitiesData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::SerializedAbilitiesData, std::error_code>;
};

template <>
struct Serializer<v776::SerializedAbilitiesData> {
    static void serialize(BinaryWriter &stream, const v776::SerializedAbilitiesData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v776::SerializedAbilitiesData, std::error_code>;
};

template <>
struct Serializer<base::UpdateAbilitiesPacket> {
    static void serialize(BinaryWriter &stream, const base::UpdateAbilitiesPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::UpdateAbilitiesPacket, std::error_code>;
};

template <>
struct Serializer<v776::UpdateAbilitiesPacket> {
    static void serialize(BinaryWriter &stream, const v776::UpdateAbilitiesPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v776::UpdateAbilitiesPacket, std::error_code>;
};
using AbilitiesIndex = AbilitiesIndex_<2225>;
using RequestAbilityPacket = RequestAbilityPacket_<2225>;
using SerializedAbilitiesData = SerializedAbilitiesData_<2225>;
using UpdateAbilitiesPacket = UpdateAbilitiesPacket_<2225>;

}  // namespace bedrock::protocol
