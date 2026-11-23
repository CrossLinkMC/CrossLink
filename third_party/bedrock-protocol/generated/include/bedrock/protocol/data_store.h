#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <expected>
#include <string>
#include <string_view>
#include <system_error>
#include <variant>
#include <vector>

#include <bedrock/protocol/data_store.hpp>
#include <bedrock/protocol/detail/reflect.hpp>
#include <bedrock/protocol/packet.hpp>
#include <bedrock/protocol/serializer.hpp>
#include <bedrock/protocol/stream.hpp>

namespace bedrock::protocol {

struct DataStoreChange {
    std::string data_store_name{};
    std::string property{};
    std::uint32_t update_count{};
    DynamicValue new_data{};
};

struct DataStoreRemoval {
    std::string data_store_name{};
};

namespace v859 {

struct DataStoreSyncPacket {
    static constexpr int Id = 330;
    std::vector<std::variant<DataStoreChange, DataStoreRemoval>> updates{};
};

}  // namespace v859

namespace v898 {

struct DataStoreUpdate {
    std::string data_store_name{};
    std::string property{};
    std::string path{};
    std::variant<double, bool, std::string> data{};
    std::uint32_t update_count{};
};

struct ClientboundDataStorePacket {
    static constexpr int Id = 330;
    std::vector<std::variant<v898::DataStoreUpdate, DataStoreChange, DataStoreRemoval>> updates{};
};

struct ServerboundDataStorePacket {
    static constexpr int Id = 332;
    v898::DataStoreUpdate update{};
};

}  // namespace v898

namespace v924 {

struct DataStoreUpdate {
    std::string data_store_name{};
    std::string property{};
    std::string path{};
    std::variant<double, bool, std::string> data{};
    std::uint32_t property_update_count{};
    std::uint32_t path_update_count{};
};

struct ClientboundDataStorePacket {
    static constexpr int Id = 330;
    std::vector<std::variant<v924::DataStoreUpdate, DataStoreChange, DataStoreRemoval>> updates{};
};

struct ServerboundDataStorePacket {
    static constexpr int Id = 332;
    v924::DataStoreUpdate update{};
};

}  // namespace v924

namespace detail {

template <int V>
struct DataStoreUpdate_;

template <int V> requires (V >= 898 && V < 924)
struct DataStoreUpdate_<V> { using type = v898::DataStoreUpdate; };

template <int V> requires (V >= 924)
struct DataStoreUpdate_<V> { using type = v924::DataStoreUpdate; };

template <int V>
struct ClientboundDataStorePacket_;

template <int V> requires (V >= 898 && V < 924)
struct ClientboundDataStorePacket_<V> { using type = v898::ClientboundDataStorePacket; };

template <int V> requires (V >= 924)
struct ClientboundDataStorePacket_<V> { using type = v924::ClientboundDataStorePacket; };

template <int V>
struct ServerboundDataStorePacket_;

template <int V> requires (V >= 898 && V < 924)
struct ServerboundDataStorePacket_<V> { using type = v898::ServerboundDataStorePacket; };

template <int V> requires (V >= 924)
struct ServerboundDataStorePacket_<V> { using type = v924::ServerboundDataStorePacket; };

template <int V>
struct DataStoreSyncPacket_;

template <int V> requires (V >= 859 && V < 898)
struct DataStoreSyncPacket_<V> { using type = v859::DataStoreSyncPacket; };

}  // namespace detail

template <int V> using DataStoreUpdate_ = typename detail::DataStoreUpdate_<V>::type;
template <int V> using ClientboundDataStorePacket_ = typename detail::ClientboundDataStorePacket_<V>::type;
template <int V> using ServerboundDataStorePacket_ = typename detail::ServerboundDataStorePacket_<V>::type;
template <int V> using DataStoreSyncPacket_ = typename detail::DataStoreSyncPacket_<V>::type;

template <int V> requires (V >= 898)
struct packet_of<V, 330> { using type = ClientboundDataStorePacket_<V>; };

template <int V> requires (V >= 859 && V < 898)
struct packet_of<V, 330> { using type = DataStoreSyncPacket_<V>; };

template <int V> requires (V >= 898)
struct packet_of<V, 332> { using type = ServerboundDataStorePacket_<V>; };

namespace detail {

template <>
inline constexpr bool is_reflected_struct_v<v898::DataStoreUpdate> = true;

template <>
inline constexpr std::string_view struct_name_v<v898::DataStoreUpdate>{"DataStoreUpdate"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v898::DataStoreUpdate>{{
    "data_store_name",
    "property",
    "path",
    "data",
    "update_count",
}};

template <>
struct field_accessor<v898::DataStoreUpdate> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.data_store_name;
        }
        else if constexpr (I == 1) {
            return value.property;
        }
        else if constexpr (I == 2) {
            return value.path;
        }
        else if constexpr (I == 3) {
            return value.data;
        }
        else {
            return value.update_count;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::DataStoreUpdate> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::DataStoreUpdate>{"DataStoreUpdate"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<v924::DataStoreUpdate>{{
    "data_store_name",
    "property",
    "path",
    "data",
    "property_update_count",
    "path_update_count",
}};

template <>
struct field_accessor<v924::DataStoreUpdate> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.data_store_name;
        }
        else if constexpr (I == 1) {
            return value.property;
        }
        else if constexpr (I == 2) {
            return value.path;
        }
        else if constexpr (I == 3) {
            return value.data;
        }
        else if constexpr (I == 4) {
            return value.property_update_count;
        }
        else {
            return value.path_update_count;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<DataStoreChange> = true;

template <>
inline constexpr std::string_view struct_name_v<DataStoreChange>{"DataStoreChange"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<DataStoreChange>{{
    "data_store_name",
    "property",
    "update_count",
    "new_data",
}};

template <>
struct field_accessor<DataStoreChange> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.data_store_name;
        }
        else if constexpr (I == 1) {
            return value.property;
        }
        else if constexpr (I == 2) {
            return value.update_count;
        }
        else {
            return value.new_data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<DataStoreRemoval> = true;

template <>
inline constexpr std::string_view struct_name_v<DataStoreRemoval>{"DataStoreRemoval"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<DataStoreRemoval>{{
    "data_store_name",
}};

template <>
struct field_accessor<DataStoreRemoval> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.data_store_name;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v898::ClientboundDataStorePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v898::ClientboundDataStorePacket>{"ClientboundDataStorePacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v898::ClientboundDataStorePacket>{{
    "updates",
}};

template <>
struct field_accessor<v898::ClientboundDataStorePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.updates;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::ClientboundDataStorePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::ClientboundDataStorePacket>{"ClientboundDataStorePacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v924::ClientboundDataStorePacket>{{
    "updates",
}};

template <>
struct field_accessor<v924::ClientboundDataStorePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.updates;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v898::ServerboundDataStorePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v898::ServerboundDataStorePacket>{"ServerboundDataStorePacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v898::ServerboundDataStorePacket>{{
    "update",
}};

template <>
struct field_accessor<v898::ServerboundDataStorePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.update;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::ServerboundDataStorePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::ServerboundDataStorePacket>{"ServerboundDataStorePacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v924::ServerboundDataStorePacket>{{
    "update",
}};

template <>
struct field_accessor<v924::ServerboundDataStorePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.update;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v859::DataStoreSyncPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v859::DataStoreSyncPacket>{"DataStoreSyncPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v859::DataStoreSyncPacket>{{
    "updates",
}};

template <>
struct field_accessor<v859::DataStoreSyncPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.updates;
    }
};

}  // namespace detail


template <>
struct Serializer<v898::DataStoreUpdate> {
    static void serialize(BinaryWriter &stream, const v898::DataStoreUpdate &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v898::DataStoreUpdate, std::error_code>;
};

template <>
struct Serializer<v924::DataStoreUpdate> {
    static void serialize(BinaryWriter &stream, const v924::DataStoreUpdate &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::DataStoreUpdate, std::error_code>;
};

template <>
struct Serializer<DataStoreChange> {
    static void serialize(BinaryWriter &stream, const DataStoreChange &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<DataStoreChange, std::error_code>;
};

template <>
struct Serializer<DataStoreRemoval> {
    static void serialize(BinaryWriter &stream, const DataStoreRemoval &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<DataStoreRemoval, std::error_code>;
};

template <>
struct Serializer<v898::ClientboundDataStorePacket> {
    static void serialize(BinaryWriter &stream, const v898::ClientboundDataStorePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v898::ClientboundDataStorePacket, std::error_code>;
};

template <>
struct Serializer<v924::ClientboundDataStorePacket> {
    static void serialize(BinaryWriter &stream, const v924::ClientboundDataStorePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::ClientboundDataStorePacket, std::error_code>;
};

template <>
struct Serializer<v898::ServerboundDataStorePacket> {
    static void serialize(BinaryWriter &stream, const v898::ServerboundDataStorePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v898::ServerboundDataStorePacket, std::error_code>;
};

template <>
struct Serializer<v924::ServerboundDataStorePacket> {
    static void serialize(BinaryWriter &stream, const v924::ServerboundDataStorePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::ServerboundDataStorePacket, std::error_code>;
};

template <>
struct Serializer<v859::DataStoreSyncPacket> {
    static void serialize(BinaryWriter &stream, const v859::DataStoreSyncPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v859::DataStoreSyncPacket, std::error_code>;
};
using DataStoreUpdate = DataStoreUpdate_<2225>;
using ClientboundDataStorePacket = ClientboundDataStorePacket_<2225>;
using ServerboundDataStorePacket = ServerboundDataStorePacket_<2225>;

}  // namespace bedrock::protocol
