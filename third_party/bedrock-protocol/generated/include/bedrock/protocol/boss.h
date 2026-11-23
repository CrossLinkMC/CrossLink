#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <expected>
#include <string>
#include <string_view>
#include <system_error>

#include <bedrock/protocol/detail/reflect.hpp>
#include <bedrock/protocol/enum.hpp>
#include <bedrock/protocol/packet.hpp>
#include <bedrock/protocol/serializer.hpp>
#include <bedrock/protocol/stream.hpp>

#include <bedrock/protocol/actor.h>

namespace bedrock::protocol {

enum class BossEventUpdateType : std::uint8_t {
    Add = 0,
    PlayerAdded = 1,
    Remove = 2,
    PlayerRemoved = 3,
    UpdatePercent = 4,
    UpdateName = 5,
    UpdateProperties = 6,
    UpdateStyle = 7,
    Query = 8,
};

enum class BossBarColor : std::uint8_t {
    Pink = 0,
    Blue = 1,
    Red = 2,
    Green = 3,
    Yellow = 4,
    Purple = 5,
    RebeccaPurple = 6,
    White = 7,
};

enum class BossBarOverlay : std::uint8_t {
    Progress = 0,
    Notched6 = 1,
    Notched10 = 2,
    Notched12 = 3,
    Notched20 = 4,
};

namespace base {

struct BossEventPacket {
    static constexpr int Id = 74;
    ActorUniqueID boss_id{};
    BossEventUpdateType event_type{};
    ActorUniqueID player_id{};
    std::string name{};
    float health_percent{};
    std::uint8_t darken_screen{};
    std::uint8_t create_world_fog{};
    BossBarColor color{};
    BossBarOverlay overlay{};
};

}  // namespace base

namespace v766 {

using BossEventPacket = base::BossEventPacket;

}  // namespace v766

namespace v776 {

struct BossEventPacket {
    static constexpr int Id = 74;
    ActorUniqueID boss_id{};
    BossEventUpdateType event_type{};
    ActorUniqueID player_id{};
    std::string name{};
    std::string filtered_name{};
    float health_percent{};
    std::uint8_t darken_screen{};
    std::uint8_t create_world_fog{};
    BossBarColor color{};
    BossBarOverlay overlay{};
};

}  // namespace v776

namespace v786 {

using BossEventPacket = v776::BossEventPacket;

}  // namespace v786

namespace v800 {

using BossEventPacket = v776::BossEventPacket;

}  // namespace v800

namespace v818 {

using BossEventPacket = v776::BossEventPacket;

}  // namespace v818

namespace v827 {

using BossEventPacket = v776::BossEventPacket;

}  // namespace v827

namespace v844 {

using BossEventPacket = v776::BossEventPacket;

}  // namespace v844

namespace v859 {

using BossEventPacket = v776::BossEventPacket;

}  // namespace v859

namespace v898 {

using BossEventPacket = v776::BossEventPacket;

}  // namespace v898

namespace v924 {

using BossEventPacket = v776::BossEventPacket;

}  // namespace v924

namespace v975 {

using BossEventPacket = v776::BossEventPacket;

}  // namespace v975

namespace v1001 {

struct BossEventPacket {
    static constexpr int Id = 74;
    ActorUniqueID boss_id{};
    ActorUniqueID player_id{};
    BossEventUpdateType event_type{};
    std::string name{};
    std::string filtered_name{};
    float health_percent{};
    BossBarColor color{};
    BossBarOverlay overlay{};
};

}  // namespace v1001

namespace v2168 {

using BossEventPacket = v1001::BossEventPacket;

}  // namespace v2168

namespace v2193 {

struct BossEventPacket {
    static constexpr int Id = 74;
    ActorUniqueID boss_id{};
    BossEventUpdateType event_type{};
    std::string name{};
    std::string filtered_name{};
    float health_percent{};
    BossBarColor color{};
    BossBarOverlay overlay{};
};

}  // namespace v2193

namespace v2225 {

using BossEventPacket = v2193::BossEventPacket;

}  // namespace v2225

namespace detail {

template <int V>
struct BossEventPacket_;

template <int V> requires (V < 776)
struct BossEventPacket_<V> { using type = base::BossEventPacket; };

template <int V> requires (V >= 776 && V < 1001)
struct BossEventPacket_<V> { using type = v776::BossEventPacket; };

template <int V> requires (V >= 1001 && V < 2193)
struct BossEventPacket_<V> { using type = v1001::BossEventPacket; };

template <int V> requires (V >= 2193)
struct BossEventPacket_<V> { using type = v2193::BossEventPacket; };

}  // namespace detail

template <int V> using BossEventPacket_ = typename detail::BossEventPacket_<V>::type;

template <int V>
struct packet_of<V, 74> { using type = BossEventPacket_<V>; };

namespace detail {

template <>
inline constexpr std::array<BossEventUpdateType, 9> values_v<BossEventUpdateType>{{
    BossEventUpdateType::Add,
    BossEventUpdateType::PlayerAdded,
    BossEventUpdateType::Remove,
    BossEventUpdateType::PlayerRemoved,
    BossEventUpdateType::UpdatePercent,
    BossEventUpdateType::UpdateName,
    BossEventUpdateType::UpdateProperties,
    BossEventUpdateType::UpdateStyle,
    BossEventUpdateType::Query,
}};

template <>
inline constexpr std::array<std::string_view, 9> names_v<BossEventUpdateType>{{
    "add",
    "playeradded",
    "remove",
    "playerremoved",
    "updatepercent",
    "updatename",
    "updateproperties",
    "updatestyle",
    "query",
}};

template <>
inline constexpr std::string_view type_name_v<BossEventUpdateType>{"BossEventUpdateType"};

template <>
inline constexpr std::array<BossBarColor, 8> values_v<BossBarColor>{{
    BossBarColor::Pink,
    BossBarColor::Blue,
    BossBarColor::Red,
    BossBarColor::Green,
    BossBarColor::Yellow,
    BossBarColor::Purple,
    BossBarColor::RebeccaPurple,
    BossBarColor::White,
}};

template <>
inline constexpr std::array<std::string_view, 8> names_v<BossBarColor>{{
    "pink",
    "blue",
    "red",
    "green",
    "yellow",
    "purple",
    "rebeccapurple",
    "white",
}};

template <>
inline constexpr std::string_view type_name_v<BossBarColor>{"BossBarColor"};

template <>
inline constexpr std::array<BossBarOverlay, 5> values_v<BossBarOverlay>{{
    BossBarOverlay::Progress,
    BossBarOverlay::Notched6,
    BossBarOverlay::Notched10,
    BossBarOverlay::Notched12,
    BossBarOverlay::Notched20,
}};

template <>
inline constexpr std::array<std::string_view, 5> names_v<BossBarOverlay>{{
    "progress",
    "notched6",
    "notched10",
    "notched12",
    "notched20",
}};

template <>
inline constexpr std::string_view type_name_v<BossBarOverlay>{"BossBarOverlay"};

}  // namespace detail

namespace detail {

template <>
inline constexpr bool is_reflected_struct_v<base::BossEventPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::BossEventPacket>{"BossEventPacket"};

template <>
inline constexpr std::array<std::string_view, 9> field_names_v<base::BossEventPacket>{{
    "boss_id",
    "event_type",
    "player_id",
    "name",
    "health_percent",
    "darken_screen",
    "create_world_fog",
    "color",
    "overlay",
}};

template <>
struct field_accessor<base::BossEventPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.boss_id;
        }
        else if constexpr (I == 1) {
            return value.event_type;
        }
        else if constexpr (I == 2) {
            return value.player_id;
        }
        else if constexpr (I == 3) {
            return value.name;
        }
        else if constexpr (I == 4) {
            return value.health_percent;
        }
        else if constexpr (I == 5) {
            return value.darken_screen;
        }
        else if constexpr (I == 6) {
            return value.create_world_fog;
        }
        else if constexpr (I == 7) {
            return value.color;
        }
        else {
            return value.overlay;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v776::BossEventPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v776::BossEventPacket>{"BossEventPacket"};

template <>
inline constexpr std::array<std::string_view, 10> field_names_v<v776::BossEventPacket>{{
    "boss_id",
    "event_type",
    "player_id",
    "name",
    "filtered_name",
    "health_percent",
    "darken_screen",
    "create_world_fog",
    "color",
    "overlay",
}};

template <>
struct field_accessor<v776::BossEventPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.boss_id;
        }
        else if constexpr (I == 1) {
            return value.event_type;
        }
        else if constexpr (I == 2) {
            return value.player_id;
        }
        else if constexpr (I == 3) {
            return value.name;
        }
        else if constexpr (I == 4) {
            return value.filtered_name;
        }
        else if constexpr (I == 5) {
            return value.health_percent;
        }
        else if constexpr (I == 6) {
            return value.darken_screen;
        }
        else if constexpr (I == 7) {
            return value.create_world_fog;
        }
        else if constexpr (I == 8) {
            return value.color;
        }
        else {
            return value.overlay;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::BossEventPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::BossEventPacket>{"BossEventPacket"};

template <>
inline constexpr std::array<std::string_view, 8> field_names_v<v1001::BossEventPacket>{{
    "boss_id",
    "player_id",
    "event_type",
    "name",
    "filtered_name",
    "health_percent",
    "color",
    "overlay",
}};

template <>
struct field_accessor<v1001::BossEventPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.boss_id;
        }
        else if constexpr (I == 1) {
            return value.player_id;
        }
        else if constexpr (I == 2) {
            return value.event_type;
        }
        else if constexpr (I == 3) {
            return value.name;
        }
        else if constexpr (I == 4) {
            return value.filtered_name;
        }
        else if constexpr (I == 5) {
            return value.health_percent;
        }
        else if constexpr (I == 6) {
            return value.color;
        }
        else {
            return value.overlay;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2193::BossEventPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2193::BossEventPacket>{"BossEventPacket"};

template <>
inline constexpr std::array<std::string_view, 7> field_names_v<v2193::BossEventPacket>{{
    "boss_id",
    "event_type",
    "name",
    "filtered_name",
    "health_percent",
    "color",
    "overlay",
}};

template <>
struct field_accessor<v2193::BossEventPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.boss_id;
        }
        else if constexpr (I == 1) {
            return value.event_type;
        }
        else if constexpr (I == 2) {
            return value.name;
        }
        else if constexpr (I == 3) {
            return value.filtered_name;
        }
        else if constexpr (I == 4) {
            return value.health_percent;
        }
        else if constexpr (I == 5) {
            return value.color;
        }
        else {
            return value.overlay;
        }
    }
};

}  // namespace detail


template <>
struct Serializer<base::BossEventPacket> {
    static void serialize(BinaryWriter &stream, const base::BossEventPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::BossEventPacket, std::error_code>;
};

template <>
struct Serializer<v776::BossEventPacket> {
    static void serialize(BinaryWriter &stream, const v776::BossEventPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v776::BossEventPacket, std::error_code>;
};

template <>
struct Serializer<v1001::BossEventPacket> {
    static void serialize(BinaryWriter &stream, const v1001::BossEventPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::BossEventPacket, std::error_code>;
};

template <>
struct Serializer<v2193::BossEventPacket> {
    static void serialize(BinaryWriter &stream, const v2193::BossEventPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::BossEventPacket, std::error_code>;
};
using BossEventPacket = BossEventPacket_<2225>;

}  // namespace bedrock::protocol
