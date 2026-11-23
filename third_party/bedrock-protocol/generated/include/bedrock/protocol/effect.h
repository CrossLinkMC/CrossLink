#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <expected>
#include <string_view>
#include <system_error>

#include <bedrock/protocol/detail/reflect.hpp>
#include <bedrock/protocol/enum.hpp>
#include <bedrock/protocol/packet.hpp>
#include <bedrock/protocol/serializer.hpp>
#include <bedrock/protocol/stream.hpp>

#include <bedrock/protocol/actor.h>

namespace bedrock::protocol {

namespace base {

enum class MovementEffectType : int {
    Invalid = -1,
    GlideBoost = 0,
    Count = 1,
};

namespace MobEffectPacket_nested {

enum class Event : std::uint8_t {
    Invalid = 0,
    Add = 1,
    Update = 2,
    Remove = 3,
};

}  // namespace MobEffectPacket_nested

struct MobEffectPacket {
    using Event = MobEffectPacket_nested::Event;

    static constexpr int Id = 28;
    ActorRuntimeID runtime_id{};
    base::MobEffectPacket::Event event_id{};
    std::int32_t effect_id{};
    std::int32_t effect_amplifier{};
    bool show_particles{};
    std::int32_t effect_duration_ticks{};
    PlayerInputTick tick{};
};

}  // namespace base

namespace v748 {

using MovementEffectType = base::MovementEffectType;

namespace MobEffectPacket_nested {

using Event = base::MobEffectPacket::Event;

}  // namespace MobEffectPacket_nested

struct MobEffectPacket {
    using Event = MobEffectPacket_nested::Event;

    static constexpr int Id = 28;
    ActorRuntimeID runtime_id{};
    v748::MobEffectPacket::Event event_id{};
    std::int32_t effect_id{};
    std::int32_t effect_amplifier{};
    bool show_particles{};
    std::int32_t effect_duration_ticks{};
    PlayerInputTick tick{};
};

struct MovementEffectPacket {
    static constexpr int Id = 318;
    ActorRuntimeID target_runtime_id{};
    base::MovementEffectType effect_id{};
    std::int32_t effect_duration{};
    PlayerInputTick tick{};
};

}  // namespace v748

namespace v766 {

using MovementEffectType = base::MovementEffectType;

using MobEffectPacket = v748::MobEffectPacket;

using MovementEffectPacket = v748::MovementEffectPacket;

}  // namespace v766

namespace v776 {

enum class MovementEffectType : int {
    Invalid = -1,
    GlideBoost = 0,
    DolphinBoost = 1,
    Count = 2,
};

using MobEffectPacket = v748::MobEffectPacket;

struct MovementEffectPacket {
    static constexpr int Id = 318;
    ActorRuntimeID target_runtime_id{};
    v776::MovementEffectType effect_id{};
    std::int32_t effect_duration{};
    PlayerInputTick tick{};
};

}  // namespace v776

namespace v786 {

using MovementEffectType = v776::MovementEffectType;

using MobEffectPacket = v748::MobEffectPacket;

using MovementEffectPacket = v776::MovementEffectPacket;

}  // namespace v786

namespace v800 {

using MovementEffectType = v776::MovementEffectType;

using MobEffectPacket = v748::MobEffectPacket;

using MovementEffectPacket = v776::MovementEffectPacket;

}  // namespace v800

namespace v818 {

using MovementEffectType = v776::MovementEffectType;

using MobEffectPacket = v748::MobEffectPacket;

using MovementEffectPacket = v776::MovementEffectPacket;

}  // namespace v818

namespace v827 {

using MovementEffectType = v776::MovementEffectType;

using MobEffectPacket = v748::MobEffectPacket;

using MovementEffectPacket = v776::MovementEffectPacket;

}  // namespace v827

namespace v844 {

using MovementEffectType = v776::MovementEffectType;

using MobEffectPacket = v748::MobEffectPacket;

using MovementEffectPacket = v776::MovementEffectPacket;

}  // namespace v844

namespace v859 {

using MovementEffectType = v776::MovementEffectType;

using MobEffectPacket = v748::MobEffectPacket;

using MovementEffectPacket = v776::MovementEffectPacket;

}  // namespace v859

namespace v898 {

using MovementEffectType = v776::MovementEffectType;

namespace MobEffectPacket_nested {

using Event = base::MobEffectPacket::Event;

}  // namespace MobEffectPacket_nested

struct MobEffectPacket {
    using Event = MobEffectPacket_nested::Event;

    static constexpr int Id = 28;
    ActorRuntimeID runtime_id{};
    v898::MobEffectPacket::Event event_id{};
    std::int32_t effect_id{};
    std::int32_t effect_amplifier{};
    bool show_particles{};
    std::int32_t effect_duration_ticks{};
    PlayerInputTick tick{};
    bool ambient{};
};

using MovementEffectPacket = v776::MovementEffectPacket;

}  // namespace v898

namespace v924 {

using MovementEffectType = v776::MovementEffectType;

using MobEffectPacket = v898::MobEffectPacket;

using MovementEffectPacket = v776::MovementEffectPacket;

}  // namespace v924

namespace v975 {

using MovementEffectType = v776::MovementEffectType;

using MobEffectPacket = v898::MobEffectPacket;

using MovementEffectPacket = v776::MovementEffectPacket;

}  // namespace v975

namespace v1001 {

enum class MovementEffectType : int {
    Invalid = -1,
    GlideBoost = 0,
    DolphinBoost = 1,
    GeyserBoost = 2,
    Count = 3,
};

using MobEffectPacket = v898::MobEffectPacket;

struct MovementEffectPacket {
    static constexpr int Id = 318;
    ActorRuntimeID target_runtime_id{};
    v1001::MovementEffectType effect_id{};
    std::int32_t effect_duration{};
    PlayerInputTick tick{};
};

}  // namespace v1001

namespace v2168 {

using MovementEffectType = v1001::MovementEffectType;

using MobEffectPacket = v898::MobEffectPacket;

using MovementEffectPacket = v1001::MovementEffectPacket;

}  // namespace v2168

namespace v2225 {

using MovementEffectType = v1001::MovementEffectType;

using MobEffectPacket = v898::MobEffectPacket;

using MovementEffectPacket = v1001::MovementEffectPacket;

}  // namespace v2225

namespace detail {

template <int V>
struct MovementEffectType_;

template <int V> requires (V < 776)
struct MovementEffectType_<V> { using type = base::MovementEffectType; };

template <int V> requires (V >= 776 && V < 1001)
struct MovementEffectType_<V> { using type = v776::MovementEffectType; };

template <int V> requires (V >= 1001)
struct MovementEffectType_<V> { using type = v1001::MovementEffectType; };

template <int V>
struct MobEffectPacket_;

template <int V> requires (V < 748)
struct MobEffectPacket_<V> { using type = base::MobEffectPacket; };

template <int V> requires (V >= 748 && V < 898)
struct MobEffectPacket_<V> { using type = v748::MobEffectPacket; };

template <int V> requires (V >= 898)
struct MobEffectPacket_<V> { using type = v898::MobEffectPacket; };

template <int V>
struct MovementEffectPacket_;

template <int V> requires (V >= 748 && V < 776)
struct MovementEffectPacket_<V> { using type = v748::MovementEffectPacket; };

template <int V> requires (V >= 776 && V < 1001)
struct MovementEffectPacket_<V> { using type = v776::MovementEffectPacket; };

template <int V> requires (V >= 1001)
struct MovementEffectPacket_<V> { using type = v1001::MovementEffectPacket; };

}  // namespace detail

template <int V> using MovementEffectType_ = typename detail::MovementEffectType_<V>::type;
template <int V> using MobEffectPacket_ = typename detail::MobEffectPacket_<V>::type;
template <int V> using MovementEffectPacket_ = typename detail::MovementEffectPacket_<V>::type;

template <int V>
struct packet_of<V, 28> { using type = MobEffectPacket_<V>; };

template <int V> requires (V >= 748)
struct packet_of<V, 318> { using type = MovementEffectPacket_<V>; };

namespace detail {

template <>
inline constexpr std::array<base::MovementEffectType, 3> values_v<base::MovementEffectType>{{
    base::MovementEffectType::Invalid,
    base::MovementEffectType::GlideBoost,
    base::MovementEffectType::Count,
}};

template <>
inline constexpr std::array<std::string_view, 3> names_v<base::MovementEffectType>{{
    "invalid",
    "glideboost",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<base::MovementEffectType>{"MovementEffectType"};

template <>
inline constexpr std::array<v776::MovementEffectType, 4> values_v<v776::MovementEffectType>{{
    v776::MovementEffectType::Invalid,
    v776::MovementEffectType::GlideBoost,
    v776::MovementEffectType::DolphinBoost,
    v776::MovementEffectType::Count,
}};

template <>
inline constexpr std::array<std::string_view, 4> names_v<v776::MovementEffectType>{{
    "invalid",
    "glideboost",
    "dolphinboost",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<v776::MovementEffectType>{"MovementEffectType"};

template <>
inline constexpr std::array<v1001::MovementEffectType, 5> values_v<v1001::MovementEffectType>{{
    v1001::MovementEffectType::Invalid,
    v1001::MovementEffectType::GlideBoost,
    v1001::MovementEffectType::DolphinBoost,
    v1001::MovementEffectType::GeyserBoost,
    v1001::MovementEffectType::Count,
}};

template <>
inline constexpr std::array<std::string_view, 5> names_v<v1001::MovementEffectType>{{
    "invalid",
    "glideboost",
    "dolphinboost",
    "geyserboost",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<v1001::MovementEffectType>{"MovementEffectType"};

template <>
inline constexpr std::array<base::MobEffectPacket::Event, 4> values_v<base::MobEffectPacket::Event>{{
    base::MobEffectPacket::Event::Invalid,
    base::MobEffectPacket::Event::Add,
    base::MobEffectPacket::Event::Update,
    base::MobEffectPacket::Event::Remove,
}};

template <>
inline constexpr std::array<std::string_view, 4> names_v<base::MobEffectPacket::Event>{{
    "invalid",
    "add",
    "update",
    "remove",
}};

template <>
inline constexpr std::string_view type_name_v<base::MobEffectPacket::Event>{"MobEffectPacket::Event"};

}  // namespace detail

namespace detail {

template <>
inline constexpr bool is_reflected_struct_v<base::MobEffectPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::MobEffectPacket>{"MobEffectPacket"};

template <>
inline constexpr std::array<std::string_view, 7> field_names_v<base::MobEffectPacket>{{
    "runtime_id",
    "event_id",
    "effect_id",
    "effect_amplifier",
    "show_particles",
    "effect_duration_ticks",
    "tick",
}};

template <>
struct field_accessor<base::MobEffectPacket> {
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
            return value.effect_id;
        }
        else if constexpr (I == 3) {
            return value.effect_amplifier;
        }
        else if constexpr (I == 4) {
            return value.show_particles;
        }
        else if constexpr (I == 5) {
            return value.effect_duration_ticks;
        }
        else {
            return value.tick;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v748::MobEffectPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v748::MobEffectPacket>{"MobEffectPacket"};

template <>
inline constexpr std::array<std::string_view, 7> field_names_v<v748::MobEffectPacket>{{
    "runtime_id",
    "event_id",
    "effect_id",
    "effect_amplifier",
    "show_particles",
    "effect_duration_ticks",
    "tick",
}};

template <>
struct field_accessor<v748::MobEffectPacket> {
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
            return value.effect_id;
        }
        else if constexpr (I == 3) {
            return value.effect_amplifier;
        }
        else if constexpr (I == 4) {
            return value.show_particles;
        }
        else if constexpr (I == 5) {
            return value.effect_duration_ticks;
        }
        else {
            return value.tick;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v898::MobEffectPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v898::MobEffectPacket>{"MobEffectPacket"};

template <>
inline constexpr std::array<std::string_view, 8> field_names_v<v898::MobEffectPacket>{{
    "runtime_id",
    "event_id",
    "effect_id",
    "effect_amplifier",
    "show_particles",
    "effect_duration_ticks",
    "tick",
    "ambient",
}};

template <>
struct field_accessor<v898::MobEffectPacket> {
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
            return value.effect_id;
        }
        else if constexpr (I == 3) {
            return value.effect_amplifier;
        }
        else if constexpr (I == 4) {
            return value.show_particles;
        }
        else if constexpr (I == 5) {
            return value.effect_duration_ticks;
        }
        else if constexpr (I == 6) {
            return value.tick;
        }
        else {
            return value.ambient;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v748::MovementEffectPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v748::MovementEffectPacket>{"MovementEffectPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v748::MovementEffectPacket>{{
    "target_runtime_id",
    "effect_id",
    "effect_duration",
    "tick",
}};

template <>
struct field_accessor<v748::MovementEffectPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.target_runtime_id;
        }
        else if constexpr (I == 1) {
            return value.effect_id;
        }
        else if constexpr (I == 2) {
            return value.effect_duration;
        }
        else {
            return value.tick;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v776::MovementEffectPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v776::MovementEffectPacket>{"MovementEffectPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v776::MovementEffectPacket>{{
    "target_runtime_id",
    "effect_id",
    "effect_duration",
    "tick",
}};

template <>
struct field_accessor<v776::MovementEffectPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.target_runtime_id;
        }
        else if constexpr (I == 1) {
            return value.effect_id;
        }
        else if constexpr (I == 2) {
            return value.effect_duration;
        }
        else {
            return value.tick;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::MovementEffectPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::MovementEffectPacket>{"MovementEffectPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v1001::MovementEffectPacket>{{
    "target_runtime_id",
    "effect_id",
    "effect_duration",
    "tick",
}};

template <>
struct field_accessor<v1001::MovementEffectPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.target_runtime_id;
        }
        else if constexpr (I == 1) {
            return value.effect_id;
        }
        else if constexpr (I == 2) {
            return value.effect_duration;
        }
        else {
            return value.tick;
        }
    }
};

}  // namespace detail


template <>
struct Serializer<base::MobEffectPacket> {
    static void serialize(BinaryWriter &stream, const base::MobEffectPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::MobEffectPacket, std::error_code>;
};

template <>
struct Serializer<v748::MobEffectPacket> {
    static void serialize(BinaryWriter &stream, const v748::MobEffectPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v748::MobEffectPacket, std::error_code>;
};

template <>
struct Serializer<v898::MobEffectPacket> {
    static void serialize(BinaryWriter &stream, const v898::MobEffectPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v898::MobEffectPacket, std::error_code>;
};

template <>
struct Serializer<v748::MovementEffectPacket> {
    static void serialize(BinaryWriter &stream, const v748::MovementEffectPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v748::MovementEffectPacket, std::error_code>;
};

template <>
struct Serializer<v776::MovementEffectPacket> {
    static void serialize(BinaryWriter &stream, const v776::MovementEffectPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v776::MovementEffectPacket, std::error_code>;
};

template <>
struct Serializer<v1001::MovementEffectPacket> {
    static void serialize(BinaryWriter &stream, const v1001::MovementEffectPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::MovementEffectPacket, std::error_code>;
};
using MovementEffectType = MovementEffectType_<2225>;
using MobEffectPacket = MobEffectPacket_<2225>;
using MovementEffectPacket = MovementEffectPacket_<2225>;

}  // namespace bedrock::protocol
