#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <expected>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>

#include <bedrock/protocol/detail/reflect.hpp>
#include <bedrock/protocol/enum.hpp>
#include <bedrock/protocol/packet.hpp>
#include <bedrock/protocol/serializer.hpp>
#include <bedrock/protocol/stream.hpp>

#include <bedrock/protocol/crafting.h>

namespace bedrock::protocol {

namespace base {

namespace Enchant_nested {

enum class Type : std::uint8_t {
    Protection = 0,
    FireProtection = 1,
    FeatherFalling = 2,
    BlastProtection = 3,
    ProjectileProtection = 4,
    Thorns = 5,
    Respiration = 6,
    DepthStrider = 7,
    AquaAffinity = 8,
    Sharpness = 9,
    Smite = 10,
    BaneOfArthropods = 11,
    Knockback = 12,
    FireAspect = 13,
    Looting = 14,
    Efficiency = 15,
    SilkTouch = 16,
    Unbreaking = 17,
    Fortune = 18,
    Power = 19,
    Punch = 20,
    Flame = 21,
    Infinity = 22,
    LuckOfTheSea = 23,
    Lure = 24,
    FrostWalker = 25,
    Mending = 26,
    CurseOfBinding = 27,
    CurseOfVanishing = 28,
    Impaling = 29,
    Riptide = 30,
    Loyalty = 31,
    Channeling = 32,
    Multishot = 33,
    Piercing = 34,
    QuickCharge = 35,
    SoulSpeed = 36,
    SwiftSneak = 37,
    WindBurst = 38,
    Density = 39,
    Breach = 40,
    NumEnchantments = 41,
    InvalidEnchantment = 42,
};

}  // namespace Enchant_nested

struct Enchant {
    using Type = Enchant_nested::Type;
};

struct EnchantmentInstance {
    base::Enchant::Type enchant_type{};
    std::uint8_t level{};
};

struct ItemEnchants {
    std::int32_t slot{};
    std::array<std::vector<base::EnchantmentInstance>, 3> item_enchants{};
};

struct ItemEnchantOption {
    std::uint32_t cost{};
    base::ItemEnchants enchants{};
    std::string enchant_name{};
    RecipeNetId enchant_net_id{};
};

struct PlayerEnchantOptionsPacket {
    static constexpr int Id = 146;
    std::vector<base::ItemEnchantOption> options{};
};

}  // namespace base

namespace v748 {

using Enchant = base::Enchant;

using EnchantmentInstance = base::EnchantmentInstance;

using ItemEnchants = base::ItemEnchants;

using ItemEnchantOption = base::ItemEnchantOption;

using PlayerEnchantOptionsPacket = base::PlayerEnchantOptionsPacket;

}  // namespace v748

namespace v776 {

using Enchant = base::Enchant;

using EnchantmentInstance = base::EnchantmentInstance;

using ItemEnchants = base::ItemEnchants;

using ItemEnchantOption = base::ItemEnchantOption;

using PlayerEnchantOptionsPacket = base::PlayerEnchantOptionsPacket;

}  // namespace v776

namespace v898 {

namespace Enchant_nested {

enum class Type : std::uint8_t {
    Protection = 0,
    FireProtection = 1,
    FeatherFalling = 2,
    BlastProtection = 3,
    ProjectileProtection = 4,
    Thorns = 5,
    Respiration = 6,
    DepthStrider = 7,
    AquaAffinity = 8,
    Sharpness = 9,
    Smite = 10,
    BaneOfArthropods = 11,
    Knockback = 12,
    FireAspect = 13,
    Looting = 14,
    Efficiency = 15,
    SilkTouch = 16,
    Unbreaking = 17,
    Fortune = 18,
    Power = 19,
    Punch = 20,
    Flame = 21,
    Infinity = 22,
    LuckOfTheSea = 23,
    Lure = 24,
    FrostWalker = 25,
    Mending = 26,
    CurseOfBinding = 27,
    CurseOfVanishing = 28,
    Impaling = 29,
    Riptide = 30,
    Loyalty = 31,
    Channeling = 32,
    Multishot = 33,
    Piercing = 34,
    QuickCharge = 35,
    SoulSpeed = 36,
    SwiftSneak = 37,
    WindBurst = 38,
    Density = 39,
    Breach = 40,
    Lunge = 41,
    NumEnchantments = 42,
    InvalidEnchantment = 43,
};

}  // namespace Enchant_nested

struct Enchant {
    using Type = Enchant_nested::Type;
};

struct EnchantmentInstance {
    v898::Enchant::Type enchant_type{};
    std::uint8_t level{};
};

struct ItemEnchants {
    std::int32_t slot{};
    std::array<std::vector<v898::EnchantmentInstance>, 3> item_enchants{};
};

struct ItemEnchantOption {
    std::uint32_t cost{};
    v898::ItemEnchants enchants{};
    std::string enchant_name{};
    RecipeNetId enchant_net_id{};
};

struct PlayerEnchantOptionsPacket {
    static constexpr int Id = 146;
    std::vector<v898::ItemEnchantOption> options{};
};

}  // namespace v898

namespace v975 {

using Enchant = v898::Enchant;

using EnchantmentInstance = v898::EnchantmentInstance;

using ItemEnchants = v898::ItemEnchants;

struct ItemEnchantOption {
    std::uint8_t cost{};
    v898::ItemEnchants enchants{};
    std::string enchant_name{};
    RecipeNetId enchant_net_id{};
};

struct PlayerEnchantOptionsPacket {
    static constexpr int Id = 146;
    std::vector<v975::ItemEnchantOption> options{};
};

}  // namespace v975

namespace v2168 {

using Enchant = v898::Enchant;

using EnchantmentInstance = v898::EnchantmentInstance;

using ItemEnchants = v898::ItemEnchants;

using ItemEnchantOption = v975::ItemEnchantOption;

using PlayerEnchantOptionsPacket = v975::PlayerEnchantOptionsPacket;

}  // namespace v2168

namespace detail {

template <int V>
struct Enchant_;

template <int V> requires (V < 898)
struct Enchant_<V> { using type = base::Enchant; };

template <int V> requires (V >= 898)
struct Enchant_<V> { using type = v898::Enchant; };

template <int V>
struct EnchantmentInstance_;

template <int V> requires (V < 898)
struct EnchantmentInstance_<V> { using type = base::EnchantmentInstance; };

template <int V> requires (V >= 898)
struct EnchantmentInstance_<V> { using type = v898::EnchantmentInstance; };

template <int V>
struct ItemEnchants_;

template <int V> requires (V < 898)
struct ItemEnchants_<V> { using type = base::ItemEnchants; };

template <int V> requires (V >= 898)
struct ItemEnchants_<V> { using type = v898::ItemEnchants; };

template <int V>
struct ItemEnchantOption_;

template <int V> requires (V < 898)
struct ItemEnchantOption_<V> { using type = base::ItemEnchantOption; };

template <int V> requires (V >= 898 && V < 975)
struct ItemEnchantOption_<V> { using type = v898::ItemEnchantOption; };

template <int V> requires (V >= 975)
struct ItemEnchantOption_<V> { using type = v975::ItemEnchantOption; };

template <int V>
struct PlayerEnchantOptionsPacket_;

template <int V> requires (V < 898)
struct PlayerEnchantOptionsPacket_<V> { using type = base::PlayerEnchantOptionsPacket; };

template <int V> requires (V >= 898 && V < 975)
struct PlayerEnchantOptionsPacket_<V> { using type = v898::PlayerEnchantOptionsPacket; };

template <int V> requires (V >= 975)
struct PlayerEnchantOptionsPacket_<V> { using type = v975::PlayerEnchantOptionsPacket; };

}  // namespace detail

template <int V> using Enchant_ = typename detail::Enchant_<V>::type;
template <int V> using EnchantmentInstance_ = typename detail::EnchantmentInstance_<V>::type;
template <int V> using ItemEnchants_ = typename detail::ItemEnchants_<V>::type;
template <int V> using ItemEnchantOption_ = typename detail::ItemEnchantOption_<V>::type;
template <int V> using PlayerEnchantOptionsPacket_ = typename detail::PlayerEnchantOptionsPacket_<V>::type;

template <int V>
struct packet_of<V, 146> { using type = PlayerEnchantOptionsPacket_<V>; };

namespace detail {

template <>
inline constexpr std::array<base::Enchant::Type, 43> values_v<base::Enchant::Type>{{
    base::Enchant::Type::Protection,
    base::Enchant::Type::FireProtection,
    base::Enchant::Type::FeatherFalling,
    base::Enchant::Type::BlastProtection,
    base::Enchant::Type::ProjectileProtection,
    base::Enchant::Type::Thorns,
    base::Enchant::Type::Respiration,
    base::Enchant::Type::DepthStrider,
    base::Enchant::Type::AquaAffinity,
    base::Enchant::Type::Sharpness,
    base::Enchant::Type::Smite,
    base::Enchant::Type::BaneOfArthropods,
    base::Enchant::Type::Knockback,
    base::Enchant::Type::FireAspect,
    base::Enchant::Type::Looting,
    base::Enchant::Type::Efficiency,
    base::Enchant::Type::SilkTouch,
    base::Enchant::Type::Unbreaking,
    base::Enchant::Type::Fortune,
    base::Enchant::Type::Power,
    base::Enchant::Type::Punch,
    base::Enchant::Type::Flame,
    base::Enchant::Type::Infinity,
    base::Enchant::Type::LuckOfTheSea,
    base::Enchant::Type::Lure,
    base::Enchant::Type::FrostWalker,
    base::Enchant::Type::Mending,
    base::Enchant::Type::CurseOfBinding,
    base::Enchant::Type::CurseOfVanishing,
    base::Enchant::Type::Impaling,
    base::Enchant::Type::Riptide,
    base::Enchant::Type::Loyalty,
    base::Enchant::Type::Channeling,
    base::Enchant::Type::Multishot,
    base::Enchant::Type::Piercing,
    base::Enchant::Type::QuickCharge,
    base::Enchant::Type::SoulSpeed,
    base::Enchant::Type::SwiftSneak,
    base::Enchant::Type::WindBurst,
    base::Enchant::Type::Density,
    base::Enchant::Type::Breach,
    base::Enchant::Type::NumEnchantments,
    base::Enchant::Type::InvalidEnchantment,
}};

template <>
inline constexpr std::array<std::string_view, 43> names_v<base::Enchant::Type>{{
    "protection",
    "fireprotection",
    "featherfalling",
    "blastprotection",
    "projectileprotection",
    "thorns",
    "respiration",
    "depthstrider",
    "aquaaffinity",
    "sharpness",
    "smite",
    "baneofarthropods",
    "knockback",
    "fireaspect",
    "looting",
    "efficiency",
    "silktouch",
    "unbreaking",
    "fortune",
    "power",
    "punch",
    "flame",
    "infinity",
    "luckofthesea",
    "lure",
    "frostwalker",
    "mending",
    "curseofbinding",
    "curseofvanishing",
    "impaling",
    "riptide",
    "loyalty",
    "channeling",
    "multishot",
    "piercing",
    "quickcharge",
    "soulspeed",
    "swiftsneak",
    "windburst",
    "density",
    "breach",
    "numenchantments",
    "invalidenchantment",
}};

template <>
inline constexpr std::string_view type_name_v<base::Enchant::Type>{"Enchant::Type"};

template <>
inline constexpr std::array<v898::Enchant::Type, 44> values_v<v898::Enchant::Type>{{
    v898::Enchant::Type::Protection,
    v898::Enchant::Type::FireProtection,
    v898::Enchant::Type::FeatherFalling,
    v898::Enchant::Type::BlastProtection,
    v898::Enchant::Type::ProjectileProtection,
    v898::Enchant::Type::Thorns,
    v898::Enchant::Type::Respiration,
    v898::Enchant::Type::DepthStrider,
    v898::Enchant::Type::AquaAffinity,
    v898::Enchant::Type::Sharpness,
    v898::Enchant::Type::Smite,
    v898::Enchant::Type::BaneOfArthropods,
    v898::Enchant::Type::Knockback,
    v898::Enchant::Type::FireAspect,
    v898::Enchant::Type::Looting,
    v898::Enchant::Type::Efficiency,
    v898::Enchant::Type::SilkTouch,
    v898::Enchant::Type::Unbreaking,
    v898::Enchant::Type::Fortune,
    v898::Enchant::Type::Power,
    v898::Enchant::Type::Punch,
    v898::Enchant::Type::Flame,
    v898::Enchant::Type::Infinity,
    v898::Enchant::Type::LuckOfTheSea,
    v898::Enchant::Type::Lure,
    v898::Enchant::Type::FrostWalker,
    v898::Enchant::Type::Mending,
    v898::Enchant::Type::CurseOfBinding,
    v898::Enchant::Type::CurseOfVanishing,
    v898::Enchant::Type::Impaling,
    v898::Enchant::Type::Riptide,
    v898::Enchant::Type::Loyalty,
    v898::Enchant::Type::Channeling,
    v898::Enchant::Type::Multishot,
    v898::Enchant::Type::Piercing,
    v898::Enchant::Type::QuickCharge,
    v898::Enchant::Type::SoulSpeed,
    v898::Enchant::Type::SwiftSneak,
    v898::Enchant::Type::WindBurst,
    v898::Enchant::Type::Density,
    v898::Enchant::Type::Breach,
    v898::Enchant::Type::Lunge,
    v898::Enchant::Type::NumEnchantments,
    v898::Enchant::Type::InvalidEnchantment,
}};

template <>
inline constexpr std::array<std::string_view, 44> names_v<v898::Enchant::Type>{{
    "protection",
    "fireprotection",
    "featherfalling",
    "blastprotection",
    "projectileprotection",
    "thorns",
    "respiration",
    "depthstrider",
    "aquaaffinity",
    "sharpness",
    "smite",
    "baneofarthropods",
    "knockback",
    "fireaspect",
    "looting",
    "efficiency",
    "silktouch",
    "unbreaking",
    "fortune",
    "power",
    "punch",
    "flame",
    "infinity",
    "luckofthesea",
    "lure",
    "frostwalker",
    "mending",
    "curseofbinding",
    "curseofvanishing",
    "impaling",
    "riptide",
    "loyalty",
    "channeling",
    "multishot",
    "piercing",
    "quickcharge",
    "soulspeed",
    "swiftsneak",
    "windburst",
    "density",
    "breach",
    "lunge",
    "numenchantments",
    "invalidenchantment",
}};

template <>
inline constexpr std::string_view type_name_v<v898::Enchant::Type>{"Enchant::Type"};

}  // namespace detail

namespace detail {

template <>
inline constexpr bool is_reflected_struct_v<base::Enchant> = true;

template <>
inline constexpr std::string_view struct_name_v<base::Enchant>{"Enchant"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<base::Enchant>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<v898::Enchant> = true;

template <>
inline constexpr std::string_view struct_name_v<v898::Enchant>{"Enchant"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<v898::Enchant>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<base::EnchantmentInstance> = true;

template <>
inline constexpr std::string_view struct_name_v<base::EnchantmentInstance>{"EnchantmentInstance"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<base::EnchantmentInstance>{{
    "enchant_type",
    "level",
}};

template <>
struct field_accessor<base::EnchantmentInstance> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.enchant_type;
        }
        else {
            return value.level;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v898::EnchantmentInstance> = true;

template <>
inline constexpr std::string_view struct_name_v<v898::EnchantmentInstance>{"EnchantmentInstance"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v898::EnchantmentInstance>{{
    "enchant_type",
    "level",
}};

template <>
struct field_accessor<v898::EnchantmentInstance> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.enchant_type;
        }
        else {
            return value.level;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::ItemEnchants> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ItemEnchants>{"ItemEnchants"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<base::ItemEnchants>{{
    "slot",
    "item_enchants",
}};

template <>
struct field_accessor<base::ItemEnchants> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.slot;
        }
        else {
            return value.item_enchants;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v898::ItemEnchants> = true;

template <>
inline constexpr std::string_view struct_name_v<v898::ItemEnchants>{"ItemEnchants"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v898::ItemEnchants>{{
    "slot",
    "item_enchants",
}};

template <>
struct field_accessor<v898::ItemEnchants> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.slot;
        }
        else {
            return value.item_enchants;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::ItemEnchantOption> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ItemEnchantOption>{"ItemEnchantOption"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<base::ItemEnchantOption>{{
    "cost",
    "enchants",
    "enchant_name",
    "enchant_net_id",
}};

template <>
struct field_accessor<base::ItemEnchantOption> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.cost;
        }
        else if constexpr (I == 1) {
            return value.enchants;
        }
        else if constexpr (I == 2) {
            return value.enchant_name;
        }
        else {
            return value.enchant_net_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v898::ItemEnchantOption> = true;

template <>
inline constexpr std::string_view struct_name_v<v898::ItemEnchantOption>{"ItemEnchantOption"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v898::ItemEnchantOption>{{
    "cost",
    "enchants",
    "enchant_name",
    "enchant_net_id",
}};

template <>
struct field_accessor<v898::ItemEnchantOption> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.cost;
        }
        else if constexpr (I == 1) {
            return value.enchants;
        }
        else if constexpr (I == 2) {
            return value.enchant_name;
        }
        else {
            return value.enchant_net_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v975::ItemEnchantOption> = true;

template <>
inline constexpr std::string_view struct_name_v<v975::ItemEnchantOption>{"ItemEnchantOption"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v975::ItemEnchantOption>{{
    "cost",
    "enchants",
    "enchant_name",
    "enchant_net_id",
}};

template <>
struct field_accessor<v975::ItemEnchantOption> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.cost;
        }
        else if constexpr (I == 1) {
            return value.enchants;
        }
        else if constexpr (I == 2) {
            return value.enchant_name;
        }
        else {
            return value.enchant_net_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::PlayerEnchantOptionsPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::PlayerEnchantOptionsPacket>{"PlayerEnchantOptionsPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::PlayerEnchantOptionsPacket>{{
    "options",
}};

template <>
struct field_accessor<base::PlayerEnchantOptionsPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.options;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v898::PlayerEnchantOptionsPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v898::PlayerEnchantOptionsPacket>{"PlayerEnchantOptionsPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v898::PlayerEnchantOptionsPacket>{{
    "options",
}};

template <>
struct field_accessor<v898::PlayerEnchantOptionsPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.options;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v975::PlayerEnchantOptionsPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v975::PlayerEnchantOptionsPacket>{"PlayerEnchantOptionsPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v975::PlayerEnchantOptionsPacket>{{
    "options",
}};

template <>
struct field_accessor<v975::PlayerEnchantOptionsPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.options;
    }
};

}  // namespace detail


template <>
struct Serializer<base::EnchantmentInstance> {
    static void serialize(BinaryWriter &stream, const base::EnchantmentInstance &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::EnchantmentInstance, std::error_code>;
};

template <>
struct Serializer<v898::EnchantmentInstance> {
    static void serialize(BinaryWriter &stream, const v898::EnchantmentInstance &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v898::EnchantmentInstance, std::error_code>;
};

template <>
struct Serializer<base::ItemEnchants> {
    static void serialize(BinaryWriter &stream, const base::ItemEnchants &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ItemEnchants, std::error_code>;
};

template <>
struct Serializer<v898::ItemEnchants> {
    static void serialize(BinaryWriter &stream, const v898::ItemEnchants &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v898::ItemEnchants, std::error_code>;
};

template <>
struct Serializer<base::ItemEnchantOption> {
    static void serialize(BinaryWriter &stream, const base::ItemEnchantOption &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ItemEnchantOption, std::error_code>;
};

template <>
struct Serializer<v898::ItemEnchantOption> {
    static void serialize(BinaryWriter &stream, const v898::ItemEnchantOption &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v898::ItemEnchantOption, std::error_code>;
};

template <>
struct Serializer<v975::ItemEnchantOption> {
    static void serialize(BinaryWriter &stream, const v975::ItemEnchantOption &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v975::ItemEnchantOption, std::error_code>;
};

template <>
struct Serializer<base::PlayerEnchantOptionsPacket> {
    static void serialize(BinaryWriter &stream, const base::PlayerEnchantOptionsPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::PlayerEnchantOptionsPacket, std::error_code>;
};

template <>
struct Serializer<v898::PlayerEnchantOptionsPacket> {
    static void serialize(BinaryWriter &stream, const v898::PlayerEnchantOptionsPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v898::PlayerEnchantOptionsPacket, std::error_code>;
};

template <>
struct Serializer<v975::PlayerEnchantOptionsPacket> {
    static void serialize(BinaryWriter &stream, const v975::PlayerEnchantOptionsPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v975::PlayerEnchantOptionsPacket, std::error_code>;
};
using Enchant = Enchant_<2225>;
using EnchantmentInstance = EnchantmentInstance_<2225>;
using ItemEnchants = ItemEnchants_<2225>;
using ItemEnchantOption = ItemEnchantOption_<2225>;
using PlayerEnchantOptionsPacket = PlayerEnchantOptionsPacket_<2225>;

}  // namespace bedrock::protocol
