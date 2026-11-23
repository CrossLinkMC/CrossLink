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
#include <bedrock/protocol/nbt.hpp>
#include <bedrock/protocol/packet.hpp>
#include <bedrock/protocol/serializer.hpp>
#include <bedrock/protocol/stream.hpp>

#include <bedrock/protocol/common.h>

namespace bedrock::protocol {

enum class HandSlot : std::uint8_t {
    Mainhand = 0,
    Offhand = 1,
    Count = 2,
};

struct ItemComponentEntry {
    std::string name{};
    CompoundTag component_data{};
};

struct PlayerStartItemCooldownPacket {
    static constexpr int Id = 176;
    std::string item_category{};
    std::int32_t duration_ticks{};
};

struct ReplacePage {
    std::int32_t page_index{};
    std::string page_text{};
    std::string photo_name{};
};

struct AddPage {
    std::int32_t page_index{};
    std::string page_text{};
    std::string photo_name{};
};

struct DeletePage {
    std::int32_t page_index{};
};

struct SwapPages {
    std::int32_t page_index{};
    std::int32_t swap_with_index{};
};

struct Finalize {
    std::string title{};
    std::string author{};
    std::string xuid{};
};

enum class BookEditAction : std::uint8_t {
    ReplacePage = 0,
    AddPage = 1,
    DeletePage = 2,
    SwapPages = 3,
    Finalize = 4,
};

struct TrimPattern {
    std::string item_name{};
    std::string pattern_id{};
};

struct TrimMaterial {
    std::string material_id{};
    std::string color{};
    std::string item_name{};
};

struct TrimDataPacket {
    static constexpr int Id = 302;
    std::vector<TrimPattern> trim_patterns{};
    std::vector<TrimMaterial> trim_materials{};
};

struct ItemStackNetId {
    std::int32_t raw_id{};
};

struct ItemStackRequestId {
    std::int32_t raw_id{};
};

struct ItemStackLegacyRequestId {
    std::int32_t raw_id{};
};

struct NetworkItemStackDescriptor {
    std::int32_t id{};
    std::uint16_t stack_size{};
    std::uint32_t aux_value{};
    std::optional<ItemStackNetId> net_id{};
    BlockRuntimeId block_runtime_id{};
    std::string user_data_buffer{};
};

using ItemStackNetIdVariant = std::variant<ItemStackNetId, ItemStackRequestId, ItemStackLegacyRequestId>;

namespace base {

enum class ItemVersion : int {
    Legacy = 0,
    DataDriven = 1,
};

struct ItemData {
    std::string name{};
    std::int16_t id{};
    bool is_component_based{};
    base::ItemVersion item_version{};
    CompoundTag component_data{};
};

struct BookEditPacket {
    static constexpr int Id = 97;
    BookEditAction action{};
    std::int32_t book_slot{};
    std::int32_t page_index{};
    std::int32_t swap_with_index{};
    std::string page_text{};
    std::string photo_name{};
    std::string title{};
    std::string author{};
    std::string xuid{};
};

struct SerializedNetworkItemStackDescriptor {
    std::int16_t id{};
    std::uint16_t stack_size{};
    std::uint32_t aux_value{};
    std::optional<std::variant<ItemStackNetId, ItemStackRequestId, ItemStackLegacyRequestId>> net_id_variant{};
    BlockRuntimeId block_runtime_id{};
    std::string user_data_buffer{};
};

struct ItemComponentPacket {
    static constexpr int Id = 162;
    std::vector<ItemComponentEntry> items{};
};

}  // namespace base

namespace v776 {

enum class ItemVersion : int {
    Legacy = 0,
    DataDriven = 1,
    None = 2,
};

struct ItemData {
    std::string name{};
    std::int16_t id{};
    bool is_component_based{};
    v776::ItemVersion item_version{};
    CompoundTag component_data{};
};

struct ItemRegistryPacket {
    static constexpr int Id = 162;
    std::vector<v776::ItemData> items{};
};

using BookEditPacket = base::BookEditPacket;

using SerializedNetworkItemStackDescriptor = base::SerializedNetworkItemStackDescriptor;

}  // namespace v776

namespace v924 {

using ItemVersion = v776::ItemVersion;

using ItemData = v776::ItemData;

using ItemRegistryPacket = v776::ItemRegistryPacket;

struct BookEditPacket {
    static constexpr int Id = 97;
    std::int32_t book_slot{};
    std::variant<ReplacePage, AddPage, DeletePage, SwapPages, Finalize> operation{};
};

using SerializedNetworkItemStackDescriptor = base::SerializedNetworkItemStackDescriptor;

}  // namespace v924

namespace v2168 {

using ItemVersion = v776::ItemVersion;

using ItemData = v776::ItemData;

using ItemRegistryPacket = v776::ItemRegistryPacket;

using BookEditPacket = v924::BookEditPacket;

struct SerializedNetworkItemStackDescriptor {
    std::int16_t id{};
    std::uint16_t stack_size{};
    std::uint32_t aux_value{};
    std::optional<std::int32_t> net_id_variant{};
    BlockRuntimeId block_runtime_id{};
    std::string user_data_buffer{};
};

}  // namespace v2168

namespace detail {

template <int V>
struct ItemVersion_;

template <int V> requires (V < 776)
struct ItemVersion_<V> { using type = base::ItemVersion; };

template <int V> requires (V >= 776)
struct ItemVersion_<V> { using type = v776::ItemVersion; };

template <int V>
struct ItemData_;

template <int V> requires (V < 776)
struct ItemData_<V> { using type = base::ItemData; };

template <int V> requires (V >= 776)
struct ItemData_<V> { using type = v776::ItemData; };

template <int V>
struct ItemRegistryPacket_;

template <int V> requires (V >= 776)
struct ItemRegistryPacket_<V> { using type = v776::ItemRegistryPacket; };

template <int V>
struct BookEditPacket_;

template <int V> requires (V < 924)
struct BookEditPacket_<V> { using type = base::BookEditPacket; };

template <int V> requires (V >= 924)
struct BookEditPacket_<V> { using type = v924::BookEditPacket; };

template <int V>
struct SerializedNetworkItemStackDescriptor_;

template <int V> requires (V < 2168)
struct SerializedNetworkItemStackDescriptor_<V> { using type = base::SerializedNetworkItemStackDescriptor; };

template <int V> requires (V >= 2168)
struct SerializedNetworkItemStackDescriptor_<V> { using type = v2168::SerializedNetworkItemStackDescriptor; };

template <int V>
struct ItemComponentPacket_;

template <int V> requires (V < 776)
struct ItemComponentPacket_<V> { using type = base::ItemComponentPacket; };

}  // namespace detail

template <int V> using ItemVersion_ = typename detail::ItemVersion_<V>::type;
template <int V> using ItemData_ = typename detail::ItemData_<V>::type;
template <int V> using ItemRegistryPacket_ = typename detail::ItemRegistryPacket_<V>::type;
template <int V> using BookEditPacket_ = typename detail::BookEditPacket_<V>::type;
template <int V> using SerializedNetworkItemStackDescriptor_ = typename detail::SerializedNetworkItemStackDescriptor_<V>::type;
template <int V> using ItemComponentPacket_ = typename detail::ItemComponentPacket_<V>::type;

template <int V>
struct packet_of<V, 97> { using type = BookEditPacket_<V>; };

template <int V> requires (V < 776)
struct packet_of<V, 162> { using type = ItemComponentPacket_<V>; };

template <int V> requires (V >= 776)
struct packet_of<V, 162> { using type = ItemRegistryPacket_<V>; };

template <int V>
struct packet_of<V, 176> { using type = PlayerStartItemCooldownPacket; };

template <int V>
struct packet_of<V, 302> { using type = TrimDataPacket; };

namespace detail {

template <>
inline constexpr std::array<HandSlot, 3> values_v<HandSlot>{{
    HandSlot::Mainhand,
    HandSlot::Offhand,
    HandSlot::Count,
}};

template <>
inline constexpr std::array<std::string_view, 3> names_v<HandSlot>{{
    "mainhand",
    "offhand",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<HandSlot>{"HandSlot"};

template <>
inline constexpr std::array<base::ItemVersion, 2> values_v<base::ItemVersion>{{
    base::ItemVersion::Legacy,
    base::ItemVersion::DataDriven,
}};

template <>
inline constexpr std::array<std::string_view, 2> names_v<base::ItemVersion>{{
    "legacy",
    "datadriven",
}};

template <>
inline constexpr std::string_view type_name_v<base::ItemVersion>{"ItemVersion"};

template <>
inline constexpr std::array<v776::ItemVersion, 3> values_v<v776::ItemVersion>{{
    v776::ItemVersion::Legacy,
    v776::ItemVersion::DataDriven,
    v776::ItemVersion::None,
}};

template <>
inline constexpr std::array<std::string_view, 3> names_v<v776::ItemVersion>{{
    "legacy",
    "datadriven",
    "none",
}};

template <>
inline constexpr std::string_view type_name_v<v776::ItemVersion>{"ItemVersion"};

template <>
inline constexpr std::array<BookEditAction, 5> values_v<BookEditAction>{{
    BookEditAction::ReplacePage,
    BookEditAction::AddPage,
    BookEditAction::DeletePage,
    BookEditAction::SwapPages,
    BookEditAction::Finalize,
}};

template <>
inline constexpr std::array<std::string_view, 5> names_v<BookEditAction>{{
    "replacepage",
    "addpage",
    "deletepage",
    "swappages",
    "finalize",
}};

template <>
inline constexpr std::string_view type_name_v<BookEditAction>{"BookEditAction"};

}  // namespace detail

namespace detail {

template <>
inline constexpr bool is_reflected_struct_v<base::ItemData> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ItemData>{"ItemData"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<base::ItemData>{{
    "name",
    "id",
    "is_component_based",
    "item_version",
    "component_data",
}};

template <>
struct field_accessor<base::ItemData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.name;
        }
        else if constexpr (I == 1) {
            return value.id;
        }
        else if constexpr (I == 2) {
            return value.is_component_based;
        }
        else if constexpr (I == 3) {
            return value.item_version;
        }
        else {
            return value.component_data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v776::ItemData> = true;

template <>
inline constexpr std::string_view struct_name_v<v776::ItemData>{"ItemData"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v776::ItemData>{{
    "name",
    "id",
    "is_component_based",
    "item_version",
    "component_data",
}};

template <>
struct field_accessor<v776::ItemData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.name;
        }
        else if constexpr (I == 1) {
            return value.id;
        }
        else if constexpr (I == 2) {
            return value.is_component_based;
        }
        else if constexpr (I == 3) {
            return value.item_version;
        }
        else {
            return value.component_data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<ItemComponentEntry> = true;

template <>
inline constexpr std::string_view struct_name_v<ItemComponentEntry>{"ItemComponentEntry"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<ItemComponentEntry>{{
    "name",
    "component_data",
}};

template <>
struct field_accessor<ItemComponentEntry> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.name;
        }
        else {
            return value.component_data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v776::ItemRegistryPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v776::ItemRegistryPacket>{"ItemRegistryPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v776::ItemRegistryPacket>{{
    "items",
}};

template <>
struct field_accessor<v776::ItemRegistryPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.items;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<PlayerStartItemCooldownPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<PlayerStartItemCooldownPacket>{"PlayerStartItemCooldownPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<PlayerStartItemCooldownPacket>{{
    "item_category",
    "duration_ticks",
}};

template <>
struct field_accessor<PlayerStartItemCooldownPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.item_category;
        }
        else {
            return value.duration_ticks;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<ReplacePage> = true;

template <>
inline constexpr std::string_view struct_name_v<ReplacePage>{"ReplacePage"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<ReplacePage>{{
    "page_index",
    "page_text",
    "photo_name",
}};

template <>
struct field_accessor<ReplacePage> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.page_index;
        }
        else if constexpr (I == 1) {
            return value.page_text;
        }
        else {
            return value.photo_name;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<AddPage> = true;

template <>
inline constexpr std::string_view struct_name_v<AddPage>{"AddPage"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<AddPage>{{
    "page_index",
    "page_text",
    "photo_name",
}};

template <>
struct field_accessor<AddPage> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.page_index;
        }
        else if constexpr (I == 1) {
            return value.page_text;
        }
        else {
            return value.photo_name;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<DeletePage> = true;

template <>
inline constexpr std::string_view struct_name_v<DeletePage>{"DeletePage"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<DeletePage>{{
    "page_index",
}};

template <>
struct field_accessor<DeletePage> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.page_index;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<SwapPages> = true;

template <>
inline constexpr std::string_view struct_name_v<SwapPages>{"SwapPages"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<SwapPages>{{
    "page_index",
    "swap_with_index",
}};

template <>
struct field_accessor<SwapPages> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.page_index;
        }
        else {
            return value.swap_with_index;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<Finalize> = true;

template <>
inline constexpr std::string_view struct_name_v<Finalize>{"Finalize"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<Finalize>{{
    "title",
    "author",
    "xuid",
}};

template <>
struct field_accessor<Finalize> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.title;
        }
        else if constexpr (I == 1) {
            return value.author;
        }
        else {
            return value.xuid;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::BookEditPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::BookEditPacket>{"BookEditPacket"};

template <>
inline constexpr std::array<std::string_view, 9> field_names_v<base::BookEditPacket>{{
    "action",
    "book_slot",
    "page_index",
    "swap_with_index",
    "page_text",
    "photo_name",
    "title",
    "author",
    "xuid",
}};

template <>
struct field_accessor<base::BookEditPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.action;
        }
        else if constexpr (I == 1) {
            return value.book_slot;
        }
        else if constexpr (I == 2) {
            return value.page_index;
        }
        else if constexpr (I == 3) {
            return value.swap_with_index;
        }
        else if constexpr (I == 4) {
            return value.page_text;
        }
        else if constexpr (I == 5) {
            return value.photo_name;
        }
        else if constexpr (I == 6) {
            return value.title;
        }
        else if constexpr (I == 7) {
            return value.author;
        }
        else {
            return value.xuid;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::BookEditPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::BookEditPacket>{"BookEditPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v924::BookEditPacket>{{
    "book_slot",
    "operation",
}};

template <>
struct field_accessor<v924::BookEditPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.book_slot;
        }
        else {
            return value.operation;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<TrimPattern> = true;

template <>
inline constexpr std::string_view struct_name_v<TrimPattern>{"TrimPattern"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<TrimPattern>{{
    "item_name",
    "pattern_id",
}};

template <>
struct field_accessor<TrimPattern> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.item_name;
        }
        else {
            return value.pattern_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<TrimMaterial> = true;

template <>
inline constexpr std::string_view struct_name_v<TrimMaterial>{"TrimMaterial"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<TrimMaterial>{{
    "material_id",
    "color",
    "item_name",
}};

template <>
struct field_accessor<TrimMaterial> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.material_id;
        }
        else if constexpr (I == 1) {
            return value.color;
        }
        else {
            return value.item_name;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<TrimDataPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<TrimDataPacket>{"TrimDataPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<TrimDataPacket>{{
    "trim_patterns",
    "trim_materials",
}};

template <>
struct field_accessor<TrimDataPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.trim_patterns;
        }
        else {
            return value.trim_materials;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<ItemStackNetId> = true;

template <>
inline constexpr std::string_view struct_name_v<ItemStackNetId>{"ItemStackNetId"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<ItemStackNetId>{{
    "raw_id",
}};

template <>
struct field_accessor<ItemStackNetId> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.raw_id;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<ItemStackRequestId> = true;

template <>
inline constexpr std::string_view struct_name_v<ItemStackRequestId>{"ItemStackRequestId"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<ItemStackRequestId>{{
    "raw_id",
}};

template <>
struct field_accessor<ItemStackRequestId> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.raw_id;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<ItemStackLegacyRequestId> = true;

template <>
inline constexpr std::string_view struct_name_v<ItemStackLegacyRequestId>{"ItemStackLegacyRequestId"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<ItemStackLegacyRequestId>{{
    "raw_id",
}};

template <>
struct field_accessor<ItemStackLegacyRequestId> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.raw_id;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<NetworkItemStackDescriptor> = true;

template <>
inline constexpr std::string_view struct_name_v<NetworkItemStackDescriptor>{"NetworkItemStackDescriptor"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<NetworkItemStackDescriptor>{{
    "id",
    "stack_size",
    "aux_value",
    "net_id",
    "block_runtime_id",
    "user_data_buffer",
}};

template <>
struct field_accessor<NetworkItemStackDescriptor> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.id;
        }
        else if constexpr (I == 1) {
            return value.stack_size;
        }
        else if constexpr (I == 2) {
            return value.aux_value;
        }
        else if constexpr (I == 3) {
            return value.net_id;
        }
        else if constexpr (I == 4) {
            return value.block_runtime_id;
        }
        else {
            return value.user_data_buffer;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::SerializedNetworkItemStackDescriptor> = true;

template <>
inline constexpr std::string_view struct_name_v<base::SerializedNetworkItemStackDescriptor>{"SerializedNetworkItemStackDescriptor"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<base::SerializedNetworkItemStackDescriptor>{{
    "id",
    "stack_size",
    "aux_value",
    "net_id_variant",
    "block_runtime_id",
    "user_data_buffer",
}};

template <>
struct field_accessor<base::SerializedNetworkItemStackDescriptor> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.id;
        }
        else if constexpr (I == 1) {
            return value.stack_size;
        }
        else if constexpr (I == 2) {
            return value.aux_value;
        }
        else if constexpr (I == 3) {
            return value.net_id_variant;
        }
        else if constexpr (I == 4) {
            return value.block_runtime_id;
        }
        else {
            return value.user_data_buffer;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::SerializedNetworkItemStackDescriptor> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::SerializedNetworkItemStackDescriptor>{"SerializedNetworkItemStackDescriptor"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<v2168::SerializedNetworkItemStackDescriptor>{{
    "id",
    "stack_size",
    "aux_value",
    "net_id_variant",
    "block_runtime_id",
    "user_data_buffer",
}};

template <>
struct field_accessor<v2168::SerializedNetworkItemStackDescriptor> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.id;
        }
        else if constexpr (I == 1) {
            return value.stack_size;
        }
        else if constexpr (I == 2) {
            return value.aux_value;
        }
        else if constexpr (I == 3) {
            return value.net_id_variant;
        }
        else if constexpr (I == 4) {
            return value.block_runtime_id;
        }
        else {
            return value.user_data_buffer;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::ItemComponentPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ItemComponentPacket>{"ItemComponentPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::ItemComponentPacket>{{
    "items",
}};

template <>
struct field_accessor<base::ItemComponentPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.items;
    }
};

}  // namespace detail


template <>
struct Serializer<base::ItemData> {
    static void serialize(BinaryWriter &stream, const base::ItemData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ItemData, std::error_code>;
};

template <>
struct Serializer<v776::ItemData> {
    static void serialize(BinaryWriter &stream, const v776::ItemData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v776::ItemData, std::error_code>;
};

template <>
struct Serializer<ItemComponentEntry> {
    static void serialize(BinaryWriter &stream, const ItemComponentEntry &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<ItemComponentEntry, std::error_code>;
};

template <>
struct Serializer<v776::ItemRegistryPacket> {
    static void serialize(BinaryWriter &stream, const v776::ItemRegistryPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v776::ItemRegistryPacket, std::error_code>;
};

template <>
struct Serializer<PlayerStartItemCooldownPacket> {
    static void serialize(BinaryWriter &stream, const PlayerStartItemCooldownPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<PlayerStartItemCooldownPacket, std::error_code>;
};

template <>
struct Serializer<ReplacePage> {
    static void serialize(BinaryWriter &stream, const ReplacePage &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<ReplacePage, std::error_code>;
};

template <>
struct Serializer<AddPage> {
    static void serialize(BinaryWriter &stream, const AddPage &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<AddPage, std::error_code>;
};

template <>
struct Serializer<DeletePage> {
    static void serialize(BinaryWriter &stream, const DeletePage &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<DeletePage, std::error_code>;
};

template <>
struct Serializer<SwapPages> {
    static void serialize(BinaryWriter &stream, const SwapPages &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<SwapPages, std::error_code>;
};

template <>
struct Serializer<Finalize> {
    static void serialize(BinaryWriter &stream, const Finalize &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<Finalize, std::error_code>;
};

template <>
struct Serializer<base::BookEditPacket> {
    static void serialize(BinaryWriter &stream, const base::BookEditPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::BookEditPacket, std::error_code>;
};

template <>
struct Serializer<v924::BookEditPacket> {
    static void serialize(BinaryWriter &stream, const v924::BookEditPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::BookEditPacket, std::error_code>;
};

template <>
struct Serializer<TrimPattern> {
    static void serialize(BinaryWriter &stream, const TrimPattern &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<TrimPattern, std::error_code>;
};

template <>
struct Serializer<TrimMaterial> {
    static void serialize(BinaryWriter &stream, const TrimMaterial &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<TrimMaterial, std::error_code>;
};

template <>
struct Serializer<TrimDataPacket> {
    static void serialize(BinaryWriter &stream, const TrimDataPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<TrimDataPacket, std::error_code>;
};

template <>
struct Serializer<ItemStackNetId> {
    static void serialize(BinaryWriter &stream, const ItemStackNetId &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<ItemStackNetId, std::error_code>;
};

template <>
struct Serializer<ItemStackRequestId> {
    static void serialize(BinaryWriter &stream, const ItemStackRequestId &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<ItemStackRequestId, std::error_code>;
};

template <>
struct Serializer<ItemStackLegacyRequestId> {
    static void serialize(BinaryWriter &stream, const ItemStackLegacyRequestId &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<ItemStackLegacyRequestId, std::error_code>;
};

template <>
struct Serializer<NetworkItemStackDescriptor> {
    static void serialize(BinaryWriter &stream, const NetworkItemStackDescriptor &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<NetworkItemStackDescriptor, std::error_code>;
};

template <>
struct Serializer<base::SerializedNetworkItemStackDescriptor> {
    static void serialize(BinaryWriter &stream, const base::SerializedNetworkItemStackDescriptor &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::SerializedNetworkItemStackDescriptor, std::error_code>;
};

template <>
struct Serializer<v2168::SerializedNetworkItemStackDescriptor> {
    static void serialize(BinaryWriter &stream, const v2168::SerializedNetworkItemStackDescriptor &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::SerializedNetworkItemStackDescriptor, std::error_code>;
};

template <>
struct Serializer<base::ItemComponentPacket> {
    static void serialize(BinaryWriter &stream, const base::ItemComponentPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ItemComponentPacket, std::error_code>;
};

template <>
struct Serializer<ItemStackNetIdVariant> {
    static void serialize(BinaryWriter &stream, const ItemStackNetIdVariant &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<ItemStackNetIdVariant, std::error_code>;
};
using ItemVersion = ItemVersion_<2225>;
using ItemData = ItemData_<2225>;
using ItemRegistryPacket = ItemRegistryPacket_<2225>;
using BookEditPacket = BookEditPacket_<2225>;
using SerializedNetworkItemStackDescriptor = SerializedNetworkItemStackDescriptor_<2225>;

}  // namespace bedrock::protocol
