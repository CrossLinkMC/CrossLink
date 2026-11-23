#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <expected>
#include <map>
#include <optional>
#include <string>
#include <string_view>
#include <system_error>

#include <bedrock/protocol/detail/reflect.hpp>
#include <bedrock/protocol/packet.hpp>
#include <bedrock/protocol/serializer.hpp>
#include <bedrock/protocol/stream.hpp>
#include <bedrock/protocol/uuid.hpp>

#include <bedrock/protocol/common.h>
#include <bedrock/protocol/game.h>

namespace bedrock::protocol {

struct ChangeDimensionPacket {
    static constexpr int Id = 61;
    DimensionType dimension_id{};
    Vec3 pos{};
    bool respawn{};
    std::optional<std::uint32_t> loading_screen_id{};
};

namespace base {

namespace DimensionDefinitionGroup_nested {

struct DimensionDefinition {
    std::int32_t height_maximum{};
    std::int32_t height_minimum{};
    GeneratorType generator_type{};
};

}  // namespace DimensionDefinitionGroup_nested

struct DimensionDefinitionGroup {
    using DimensionDefinition = DimensionDefinitionGroup_nested::DimensionDefinition;
};

struct DimensionDataPacket {
    static constexpr int Id = 180;
    std::map<std::string, base::DimensionDefinitionGroup::DimensionDefinition> dimension_definitions{};
};

}  // namespace base

namespace v748 {

using DimensionDefinitionGroup = base::DimensionDefinitionGroup;

using DimensionDataPacket = base::DimensionDataPacket;

}  // namespace v748

namespace v766 {

using DimensionDefinitionGroup = base::DimensionDefinitionGroup;

using DimensionDataPacket = base::DimensionDataPacket;

}  // namespace v766

namespace v776 {

using DimensionDefinitionGroup = base::DimensionDefinitionGroup;

using DimensionDataPacket = base::DimensionDataPacket;

}  // namespace v776

namespace v786 {

using DimensionDefinitionGroup = base::DimensionDefinitionGroup;

using DimensionDataPacket = base::DimensionDataPacket;

}  // namespace v786

namespace v800 {

using DimensionDefinitionGroup = base::DimensionDefinitionGroup;

using DimensionDataPacket = base::DimensionDataPacket;

}  // namespace v800

namespace v818 {

using DimensionDefinitionGroup = base::DimensionDefinitionGroup;

using DimensionDataPacket = base::DimensionDataPacket;

}  // namespace v818

namespace v827 {

using DimensionDefinitionGroup = base::DimensionDefinitionGroup;

using DimensionDataPacket = base::DimensionDataPacket;

}  // namespace v827

namespace v844 {

using DimensionDefinitionGroup = base::DimensionDefinitionGroup;

using DimensionDataPacket = base::DimensionDataPacket;

}  // namespace v844

namespace v859 {

using DimensionDefinitionGroup = base::DimensionDefinitionGroup;

using DimensionDataPacket = base::DimensionDataPacket;

}  // namespace v859

namespace v898 {

using DimensionDefinitionGroup = base::DimensionDefinitionGroup;

using DimensionDataPacket = base::DimensionDataPacket;

}  // namespace v898

namespace v924 {

using DimensionDefinitionGroup = base::DimensionDefinitionGroup;

using DimensionDataPacket = base::DimensionDataPacket;

}  // namespace v924

namespace v944 {

using DimensionDefinitionGroup = base::DimensionDefinitionGroup;

using DimensionDataPacket = base::DimensionDataPacket;

}  // namespace v944

namespace v975 {

namespace DimensionDefinitionGroup_nested {

struct DimensionDefinition {
    std::int32_t height_maximum{};
    std::int32_t height_minimum{};
    GeneratorType generator_type{};
    DimensionType dimension_type{};
};

}  // namespace DimensionDefinitionGroup_nested

struct DimensionDefinitionGroup {
    using DimensionDefinition = DimensionDefinitionGroup_nested::DimensionDefinition;
};

struct DimensionDataPacket {
    static constexpr int Id = 180;
    std::map<std::string, v975::DimensionDefinitionGroup::DimensionDefinition> dimension_definitions{};
};

}  // namespace v975

namespace v1001 {

using DimensionDefinitionGroup = v975::DimensionDefinitionGroup;

using DimensionDataPacket = v975::DimensionDataPacket;

}  // namespace v1001

namespace v2168 {

namespace DimensionDefinitionGroup_nested {

struct DimensionDefinition {
    std::int32_t height_maximum{};
    std::int32_t height_minimum{};
    GeneratorType generator_type{};
    DimensionType dimension_type{};
    UUID pack_id{};
};

}  // namespace DimensionDefinitionGroup_nested

struct DimensionDefinitionGroup {
    using DimensionDefinition = DimensionDefinitionGroup_nested::DimensionDefinition;
};

struct DimensionDataPacket {
    static constexpr int Id = 180;
    std::map<std::string, v2168::DimensionDefinitionGroup::DimensionDefinition> dimension_definitions{};
};

}  // namespace v2168

namespace v2193 {

namespace DimensionDefinitionGroup_nested {

struct DimensionDefinition {
    std::int32_t min_y{};
    std::int32_t height_range{};
    GeneratorType generator_type{};
    DimensionType dimension_type{};
    UUID pack_id{};
    std::string default_biome{};
};

}  // namespace DimensionDefinitionGroup_nested

struct DimensionDefinitionGroup {
    using DimensionDefinition = DimensionDefinitionGroup_nested::DimensionDefinition;
};

struct DimensionDataPacket {
    static constexpr int Id = 180;
    std::map<std::string, v2193::DimensionDefinitionGroup::DimensionDefinition> dimension_definitions{};
};

}  // namespace v2193

namespace v2225 {

namespace DimensionDefinitionGroup_nested {

struct DimensionDefinition {
    std::int32_t min_y{};
    std::int32_t height_range{};
    GeneratorType generator_type{};
    DimensionType dimension_type{};
    UUID pack_id{};
    std::string default_biome{};
    std::int32_t cloud_height{};
    bool render_clouds{};
};

}  // namespace DimensionDefinitionGroup_nested

struct DimensionDefinitionGroup {
    using DimensionDefinition = DimensionDefinitionGroup_nested::DimensionDefinition;
};

struct DimensionDataPacket {
    static constexpr int Id = 180;
    std::map<std::string, v2225::DimensionDefinitionGroup::DimensionDefinition> dimension_definitions{};
};

}  // namespace v2225

namespace detail {

template <int V>
struct DimensionDefinitionGroup_;

template <int V> requires (V < 975)
struct DimensionDefinitionGroup_<V> { using type = base::DimensionDefinitionGroup; };

template <int V> requires (V >= 975 && V < 2168)
struct DimensionDefinitionGroup_<V> { using type = v975::DimensionDefinitionGroup; };

template <int V> requires (V >= 2168 && V < 2193)
struct DimensionDefinitionGroup_<V> { using type = v2168::DimensionDefinitionGroup; };

template <int V> requires (V >= 2193 && V < 2225)
struct DimensionDefinitionGroup_<V> { using type = v2193::DimensionDefinitionGroup; };

template <int V> requires (V >= 2225)
struct DimensionDefinitionGroup_<V> { using type = v2225::DimensionDefinitionGroup; };

template <int V>
struct DimensionDataPacket_;

template <int V> requires (V < 975)
struct DimensionDataPacket_<V> { using type = base::DimensionDataPacket; };

template <int V> requires (V >= 975 && V < 2168)
struct DimensionDataPacket_<V> { using type = v975::DimensionDataPacket; };

template <int V> requires (V >= 2168 && V < 2193)
struct DimensionDataPacket_<V> { using type = v2168::DimensionDataPacket; };

template <int V> requires (V >= 2193 && V < 2225)
struct DimensionDataPacket_<V> { using type = v2193::DimensionDataPacket; };

template <int V> requires (V >= 2225)
struct DimensionDataPacket_<V> { using type = v2225::DimensionDataPacket; };

}  // namespace detail

template <int V> using DimensionDefinitionGroup_ = typename detail::DimensionDefinitionGroup_<V>::type;
template <int V> using DimensionDataPacket_ = typename detail::DimensionDataPacket_<V>::type;

template <int V>
struct packet_of<V, 61> { using type = ChangeDimensionPacket; };

template <int V>
struct packet_of<V, 180> { using type = DimensionDataPacket_<V>; };

namespace detail {

template <>
inline constexpr bool is_reflected_struct_v<base::DimensionDefinitionGroup::DimensionDefinition> = true;

template <>
inline constexpr std::string_view struct_name_v<base::DimensionDefinitionGroup::DimensionDefinition>{"DimensionDefinitionGroup::DimensionDefinition"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<base::DimensionDefinitionGroup::DimensionDefinition>{{
    "height_maximum",
    "height_minimum",
    "generator_type",
}};

template <>
struct field_accessor<base::DimensionDefinitionGroup::DimensionDefinition> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.height_maximum;
        }
        else if constexpr (I == 1) {
            return value.height_minimum;
        }
        else {
            return value.generator_type;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v975::DimensionDefinitionGroup::DimensionDefinition> = true;

template <>
inline constexpr std::string_view struct_name_v<v975::DimensionDefinitionGroup::DimensionDefinition>{"DimensionDefinitionGroup::DimensionDefinition"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v975::DimensionDefinitionGroup::DimensionDefinition>{{
    "height_maximum",
    "height_minimum",
    "generator_type",
    "dimension_type",
}};

template <>
struct field_accessor<v975::DimensionDefinitionGroup::DimensionDefinition> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.height_maximum;
        }
        else if constexpr (I == 1) {
            return value.height_minimum;
        }
        else if constexpr (I == 2) {
            return value.generator_type;
        }
        else {
            return value.dimension_type;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::DimensionDefinitionGroup::DimensionDefinition> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::DimensionDefinitionGroup::DimensionDefinition>{"DimensionDefinitionGroup::DimensionDefinition"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v2168::DimensionDefinitionGroup::DimensionDefinition>{{
    "height_maximum",
    "height_minimum",
    "generator_type",
    "dimension_type",
    "pack_id",
}};

template <>
struct field_accessor<v2168::DimensionDefinitionGroup::DimensionDefinition> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.height_maximum;
        }
        else if constexpr (I == 1) {
            return value.height_minimum;
        }
        else if constexpr (I == 2) {
            return value.generator_type;
        }
        else if constexpr (I == 3) {
            return value.dimension_type;
        }
        else {
            return value.pack_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2193::DimensionDefinitionGroup::DimensionDefinition> = true;

template <>
inline constexpr std::string_view struct_name_v<v2193::DimensionDefinitionGroup::DimensionDefinition>{"DimensionDefinitionGroup::DimensionDefinition"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<v2193::DimensionDefinitionGroup::DimensionDefinition>{{
    "min_y",
    "height_range",
    "generator_type",
    "dimension_type",
    "pack_id",
    "default_biome",
}};

template <>
struct field_accessor<v2193::DimensionDefinitionGroup::DimensionDefinition> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.min_y;
        }
        else if constexpr (I == 1) {
            return value.height_range;
        }
        else if constexpr (I == 2) {
            return value.generator_type;
        }
        else if constexpr (I == 3) {
            return value.dimension_type;
        }
        else if constexpr (I == 4) {
            return value.pack_id;
        }
        else {
            return value.default_biome;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::DimensionDefinitionGroup::DimensionDefinition> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::DimensionDefinitionGroup::DimensionDefinition>{"DimensionDefinitionGroup::DimensionDefinition"};

template <>
inline constexpr std::array<std::string_view, 8> field_names_v<v2225::DimensionDefinitionGroup::DimensionDefinition>{{
    "min_y",
    "height_range",
    "generator_type",
    "dimension_type",
    "pack_id",
    "default_biome",
    "cloud_height",
    "render_clouds",
}};

template <>
struct field_accessor<v2225::DimensionDefinitionGroup::DimensionDefinition> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.min_y;
        }
        else if constexpr (I == 1) {
            return value.height_range;
        }
        else if constexpr (I == 2) {
            return value.generator_type;
        }
        else if constexpr (I == 3) {
            return value.dimension_type;
        }
        else if constexpr (I == 4) {
            return value.pack_id;
        }
        else if constexpr (I == 5) {
            return value.default_biome;
        }
        else if constexpr (I == 6) {
            return value.cloud_height;
        }
        else {
            return value.render_clouds;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::DimensionDefinitionGroup> = true;

template <>
inline constexpr std::string_view struct_name_v<base::DimensionDefinitionGroup>{"DimensionDefinitionGroup"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<base::DimensionDefinitionGroup>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<v975::DimensionDefinitionGroup> = true;

template <>
inline constexpr std::string_view struct_name_v<v975::DimensionDefinitionGroup>{"DimensionDefinitionGroup"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<v975::DimensionDefinitionGroup>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<v2168::DimensionDefinitionGroup> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::DimensionDefinitionGroup>{"DimensionDefinitionGroup"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<v2168::DimensionDefinitionGroup>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<v2193::DimensionDefinitionGroup> = true;

template <>
inline constexpr std::string_view struct_name_v<v2193::DimensionDefinitionGroup>{"DimensionDefinitionGroup"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<v2193::DimensionDefinitionGroup>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<v2225::DimensionDefinitionGroup> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::DimensionDefinitionGroup>{"DimensionDefinitionGroup"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<v2225::DimensionDefinitionGroup>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<base::DimensionDataPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::DimensionDataPacket>{"DimensionDataPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::DimensionDataPacket>{{
    "dimension_definitions",
}};

template <>
struct field_accessor<base::DimensionDataPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.dimension_definitions;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v975::DimensionDataPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v975::DimensionDataPacket>{"DimensionDataPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v975::DimensionDataPacket>{{
    "dimension_definitions",
}};

template <>
struct field_accessor<v975::DimensionDataPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.dimension_definitions;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::DimensionDataPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::DimensionDataPacket>{"DimensionDataPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2168::DimensionDataPacket>{{
    "dimension_definitions",
}};

template <>
struct field_accessor<v2168::DimensionDataPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.dimension_definitions;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2193::DimensionDataPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2193::DimensionDataPacket>{"DimensionDataPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2193::DimensionDataPacket>{{
    "dimension_definitions",
}};

template <>
struct field_accessor<v2193::DimensionDataPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.dimension_definitions;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::DimensionDataPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::DimensionDataPacket>{"DimensionDataPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2225::DimensionDataPacket>{{
    "dimension_definitions",
}};

template <>
struct field_accessor<v2225::DimensionDataPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.dimension_definitions;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<ChangeDimensionPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<ChangeDimensionPacket>{"ChangeDimensionPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<ChangeDimensionPacket>{{
    "dimension_id",
    "pos",
    "respawn",
    "loading_screen_id",
}};

template <>
struct field_accessor<ChangeDimensionPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.dimension_id;
        }
        else if constexpr (I == 1) {
            return value.pos;
        }
        else if constexpr (I == 2) {
            return value.respawn;
        }
        else {
            return value.loading_screen_id;
        }
    }
};

}  // namespace detail


template <>
struct Serializer<base::DimensionDefinitionGroup::DimensionDefinition> {
    static void serialize(BinaryWriter &stream, const base::DimensionDefinitionGroup::DimensionDefinition &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::DimensionDefinitionGroup::DimensionDefinition, std::error_code>;
};

template <>
struct Serializer<v975::DimensionDefinitionGroup::DimensionDefinition> {
    static void serialize(BinaryWriter &stream, const v975::DimensionDefinitionGroup::DimensionDefinition &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v975::DimensionDefinitionGroup::DimensionDefinition, std::error_code>;
};

template <>
struct Serializer<v2168::DimensionDefinitionGroup::DimensionDefinition> {
    static void serialize(BinaryWriter &stream, const v2168::DimensionDefinitionGroup::DimensionDefinition &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::DimensionDefinitionGroup::DimensionDefinition, std::error_code>;
};

template <>
struct Serializer<v2193::DimensionDefinitionGroup::DimensionDefinition> {
    static void serialize(BinaryWriter &stream, const v2193::DimensionDefinitionGroup::DimensionDefinition &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::DimensionDefinitionGroup::DimensionDefinition, std::error_code>;
};

template <>
struct Serializer<v2225::DimensionDefinitionGroup::DimensionDefinition> {
    static void serialize(BinaryWriter &stream, const v2225::DimensionDefinitionGroup::DimensionDefinition &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::DimensionDefinitionGroup::DimensionDefinition, std::error_code>;
};

template <>
struct Serializer<base::DimensionDataPacket> {
    static void serialize(BinaryWriter &stream, const base::DimensionDataPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::DimensionDataPacket, std::error_code>;
};

template <>
struct Serializer<v975::DimensionDataPacket> {
    static void serialize(BinaryWriter &stream, const v975::DimensionDataPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v975::DimensionDataPacket, std::error_code>;
};

template <>
struct Serializer<v2168::DimensionDataPacket> {
    static void serialize(BinaryWriter &stream, const v2168::DimensionDataPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::DimensionDataPacket, std::error_code>;
};

template <>
struct Serializer<v2193::DimensionDataPacket> {
    static void serialize(BinaryWriter &stream, const v2193::DimensionDataPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::DimensionDataPacket, std::error_code>;
};

template <>
struct Serializer<v2225::DimensionDataPacket> {
    static void serialize(BinaryWriter &stream, const v2225::DimensionDataPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::DimensionDataPacket, std::error_code>;
};

template <>
struct Serializer<ChangeDimensionPacket> {
    static void serialize(BinaryWriter &stream, const ChangeDimensionPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<ChangeDimensionPacket, std::error_code>;
};
using DimensionDefinitionGroup = DimensionDefinitionGroup_<2225>;
using DimensionDataPacket = DimensionDataPacket_<2225>;

}  // namespace bedrock::protocol
