#pragma once

#include <array>
#include <compare>
#include <cstddef>
#include <cstdint>
#include <expected>
#include <string_view>
#include <system_error>

#include <bedrock/protocol/detail/reflect.hpp>
#include <bedrock/protocol/serializer.hpp>
#include <bedrock/protocol/stream.hpp>

namespace bedrock::protocol {

struct BlockRuntimeId {
    constexpr BlockRuntimeId() = default;
    explicit constexpr BlockRuntimeId(std::uint32_t value) : value_(value) {}
    constexpr operator std::uint32_t() const { return value_; }
    friend constexpr bool operator==(const BlockRuntimeId &, const BlockRuntimeId &) = default;
    friend constexpr auto operator<=>(const BlockRuntimeId &, const BlockRuntimeId &) = default;

  private:
    std::uint32_t value_{};
};

struct Color {
    constexpr Color() = default;
    explicit constexpr Color(std::int32_t value) : value_(value) {}
    constexpr operator std::int32_t() const { return value_; }
    friend constexpr bool operator==(const Color &, const Color &) = default;
    friend constexpr auto operator<=>(const Color &, const Color &) = default;

  private:
    std::int32_t value_{};
};

struct DimensionType {
    constexpr DimensionType() = default;
    explicit constexpr DimensionType(std::int32_t value) : value_(value) {}
    constexpr operator std::int32_t() const { return value_; }
    friend constexpr bool operator==(const DimensionType &, const DimensionType &) = default;
    friend constexpr auto operator<=>(const DimensionType &, const DimensionType &) = default;

  private:
    std::int32_t value_{};
};

struct Vec2 {
    float x{};
    float y{};
};

struct Vec3 {
    float x{};
    float y{};
    float z{};
};

struct BlockPos {
    std::int32_t x{};
    std::int32_t y{};
    std::int32_t z{};
};

namespace detail {

template <>
inline constexpr bool is_reflected_struct_v<Vec2> = true;

template <>
inline constexpr std::string_view struct_name_v<Vec2>{"Vec2"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<Vec2>{{
    "x",
    "y",
}};

template <>
struct field_accessor<Vec2> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.x;
        }
        else {
            return value.y;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<Vec3> = true;

template <>
inline constexpr std::string_view struct_name_v<Vec3>{"Vec3"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<Vec3>{{
    "x",
    "y",
    "z",
}};

template <>
struct field_accessor<Vec3> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.x;
        }
        else if constexpr (I == 1) {
            return value.y;
        }
        else {
            return value.z;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<BlockPos> = true;

template <>
inline constexpr std::string_view struct_name_v<BlockPos>{"BlockPos"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<BlockPos>{{
    "x",
    "y",
    "z",
}};

template <>
struct field_accessor<BlockPos> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.x;
        }
        else if constexpr (I == 1) {
            return value.y;
        }
        else {
            return value.z;
        }
    }
};

}  // namespace detail


template <>
struct Serializer<Vec2> {
    static void serialize(BinaryWriter &stream, const Vec2 &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<Vec2, std::error_code>;
};

template <>
struct Serializer<Vec3> {
    static void serialize(BinaryWriter &stream, const Vec3 &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<Vec3, std::error_code>;
};

template <>
struct Serializer<BlockPos> {
    static void serialize(BinaryWriter &stream, const BlockPos &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<BlockPos, std::error_code>;
};

}  // namespace bedrock::protocol
