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

namespace bedrock::protocol {

struct SetTimePacket {
    static constexpr int Id = 10;
    std::int32_t time{};
};

struct SyncWorldClockStateData {
    std::uint64_t clock_id{};
    std::int32_t time{};
    bool is_paused{};
};

struct TimeMarkerData {
    std::uint64_t id{};
    std::string name{};
    std::int32_t time{};
    std::optional<std::int32_t> period{};
};

struct WorldClockData {
    std::uint64_t id{};
    std::string name{};
    std::int32_t time{};
    bool is_paused{};
    std::vector<TimeMarkerData> time_markers{};
};

struct PositionTrackingId {
    std::int32_t raw_id{};
};

namespace PositionTrackingDBServerBroadcastPacket_nested {

enum class Action : std::uint8_t {
    Update = 0,
    Destroy = 1,
    NotFound = 2,
};

}  // namespace PositionTrackingDBServerBroadcastPacket_nested

struct PositionTrackingDBServerBroadcastPacket {
    using Action = PositionTrackingDBServerBroadcastPacket_nested::Action;

    static constexpr int Id = 153;
    PositionTrackingDBServerBroadcastPacket::Action action{};
    PositionTrackingId id{};
    CompoundTag data{};
};

namespace PositionTrackingDBClientRequestPacket_nested {

enum class Action : std::uint8_t {
    Query = 0,
};

}  // namespace PositionTrackingDBClientRequestPacket_nested

struct PositionTrackingDBClientRequestPacket {
    using Action = PositionTrackingDBClientRequestPacket_nested::Action;

    static constexpr int Id = 154;
    PositionTrackingDBClientRequestPacket::Action action{};
    PositionTrackingId id{};
};

namespace v944 {

namespace SyncWorldClocksPacket_nested {

struct SyncStateData {
    std::vector<SyncWorldClockStateData> clock_data{};
};

struct InitializeRegistryData {
    std::vector<WorldClockData> clock_data{};
};

struct AddTimeMarkerData {
    std::uint64_t clock_id{};
    std::vector<TimeMarkerData> time_markers{};
};

struct RemoveTimeMarkerData {
    std::uint64_t clock_id{};
    std::vector<std::uint64_t> time_marker_ids{};
};

}  // namespace SyncWorldClocksPacket_nested

struct SyncWorldClocksPacket {
    using SyncStateData = SyncWorldClocksPacket_nested::SyncStateData;
    using InitializeRegistryData = SyncWorldClocksPacket_nested::InitializeRegistryData;
    using AddTimeMarkerData = SyncWorldClocksPacket_nested::AddTimeMarkerData;
    using RemoveTimeMarkerData = SyncWorldClocksPacket_nested::RemoveTimeMarkerData;

    static constexpr int Id = 344;
    std::variant<v944::SyncWorldClocksPacket::SyncStateData, v944::SyncWorldClocksPacket::InitializeRegistryData, v944::SyncWorldClocksPacket::AddTimeMarkerData, v944::SyncWorldClocksPacket::RemoveTimeMarkerData> data{};
};

}  // namespace v944

namespace detail {

template <int V>
struct SyncWorldClocksPacket_;

template <int V> requires (V >= 944)
struct SyncWorldClocksPacket_<V> { using type = v944::SyncWorldClocksPacket; };

}  // namespace detail

template <int V> using SyncWorldClocksPacket_ = typename detail::SyncWorldClocksPacket_<V>::type;

template <int V>
struct packet_of<V, 10> { using type = SetTimePacket; };

template <int V>
struct packet_of<V, 153> { using type = PositionTrackingDBServerBroadcastPacket; };

template <int V>
struct packet_of<V, 154> { using type = PositionTrackingDBClientRequestPacket; };

template <int V> requires (V >= 944)
struct packet_of<V, 344> { using type = SyncWorldClocksPacket_<V>; };

namespace detail {

template <>
inline constexpr std::array<PositionTrackingDBServerBroadcastPacket::Action, 3> values_v<PositionTrackingDBServerBroadcastPacket::Action>{{
    PositionTrackingDBServerBroadcastPacket::Action::Update,
    PositionTrackingDBServerBroadcastPacket::Action::Destroy,
    PositionTrackingDBServerBroadcastPacket::Action::NotFound,
}};

template <>
inline constexpr std::array<std::string_view, 3> names_v<PositionTrackingDBServerBroadcastPacket::Action>{{
    "update",
    "destroy",
    "notfound",
}};

template <>
inline constexpr std::string_view type_name_v<PositionTrackingDBServerBroadcastPacket::Action>{"PositionTrackingDBServerBroadcastPacket::Action"};

template <>
inline constexpr std::array<PositionTrackingDBClientRequestPacket::Action, 1> values_v<PositionTrackingDBClientRequestPacket::Action>{{
    PositionTrackingDBClientRequestPacket::Action::Query,
}};

template <>
inline constexpr std::array<std::string_view, 1> names_v<PositionTrackingDBClientRequestPacket::Action>{{
    "query",
}};

template <>
inline constexpr std::string_view type_name_v<PositionTrackingDBClientRequestPacket::Action>{"PositionTrackingDBClientRequestPacket::Action"};

}  // namespace detail

namespace detail {

template <>
inline constexpr bool is_reflected_struct_v<SetTimePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<SetTimePacket>{"SetTimePacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<SetTimePacket>{{
    "time",
}};

template <>
struct field_accessor<SetTimePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.time;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<SyncWorldClockStateData> = true;

template <>
inline constexpr std::string_view struct_name_v<SyncWorldClockStateData>{"SyncWorldClockStateData"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<SyncWorldClockStateData>{{
    "clock_id",
    "time",
    "is_paused",
}};

template <>
struct field_accessor<SyncWorldClockStateData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.clock_id;
        }
        else if constexpr (I == 1) {
            return value.time;
        }
        else {
            return value.is_paused;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<TimeMarkerData> = true;

template <>
inline constexpr std::string_view struct_name_v<TimeMarkerData>{"TimeMarkerData"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<TimeMarkerData>{{
    "id",
    "name",
    "time",
    "period",
}};

template <>
struct field_accessor<TimeMarkerData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.id;
        }
        else if constexpr (I == 1) {
            return value.name;
        }
        else if constexpr (I == 2) {
            return value.time;
        }
        else {
            return value.period;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<WorldClockData> = true;

template <>
inline constexpr std::string_view struct_name_v<WorldClockData>{"WorldClockData"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<WorldClockData>{{
    "id",
    "name",
    "time",
    "is_paused",
    "time_markers",
}};

template <>
struct field_accessor<WorldClockData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.id;
        }
        else if constexpr (I == 1) {
            return value.name;
        }
        else if constexpr (I == 2) {
            return value.time;
        }
        else if constexpr (I == 3) {
            return value.is_paused;
        }
        else {
            return value.time_markers;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::SyncWorldClocksPacket::SyncStateData> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::SyncWorldClocksPacket::SyncStateData>{"SyncWorldClocksPacket::SyncStateData"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v944::SyncWorldClocksPacket::SyncStateData>{{
    "clock_data",
}};

template <>
struct field_accessor<v944::SyncWorldClocksPacket::SyncStateData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.clock_data;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::SyncWorldClocksPacket::InitializeRegistryData> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::SyncWorldClocksPacket::InitializeRegistryData>{"SyncWorldClocksPacket::InitializeRegistryData"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v944::SyncWorldClocksPacket::InitializeRegistryData>{{
    "clock_data",
}};

template <>
struct field_accessor<v944::SyncWorldClocksPacket::InitializeRegistryData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.clock_data;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::SyncWorldClocksPacket::AddTimeMarkerData> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::SyncWorldClocksPacket::AddTimeMarkerData>{"SyncWorldClocksPacket::AddTimeMarkerData"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v944::SyncWorldClocksPacket::AddTimeMarkerData>{{
    "clock_id",
    "time_markers",
}};

template <>
struct field_accessor<v944::SyncWorldClocksPacket::AddTimeMarkerData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.clock_id;
        }
        else {
            return value.time_markers;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::SyncWorldClocksPacket::RemoveTimeMarkerData> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::SyncWorldClocksPacket::RemoveTimeMarkerData>{"SyncWorldClocksPacket::RemoveTimeMarkerData"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v944::SyncWorldClocksPacket::RemoveTimeMarkerData>{{
    "clock_id",
    "time_marker_ids",
}};

template <>
struct field_accessor<v944::SyncWorldClocksPacket::RemoveTimeMarkerData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.clock_id;
        }
        else {
            return value.time_marker_ids;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::SyncWorldClocksPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::SyncWorldClocksPacket>{"SyncWorldClocksPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v944::SyncWorldClocksPacket>{{
    "data",
}};

template <>
struct field_accessor<v944::SyncWorldClocksPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.data;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<PositionTrackingId> = true;

template <>
inline constexpr std::string_view struct_name_v<PositionTrackingId>{"PositionTrackingId"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<PositionTrackingId>{{
    "raw_id",
}};

template <>
struct field_accessor<PositionTrackingId> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.raw_id;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<PositionTrackingDBServerBroadcastPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<PositionTrackingDBServerBroadcastPacket>{"PositionTrackingDBServerBroadcastPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<PositionTrackingDBServerBroadcastPacket>{{
    "action",
    "id",
    "data",
}};

template <>
struct field_accessor<PositionTrackingDBServerBroadcastPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.action;
        }
        else if constexpr (I == 1) {
            return value.id;
        }
        else {
            return value.data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<PositionTrackingDBClientRequestPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<PositionTrackingDBClientRequestPacket>{"PositionTrackingDBClientRequestPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<PositionTrackingDBClientRequestPacket>{{
    "action",
    "id",
}};

template <>
struct field_accessor<PositionTrackingDBClientRequestPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.action;
        }
        else {
            return value.id;
        }
    }
};

}  // namespace detail


template <>
struct Serializer<SetTimePacket> {
    static void serialize(BinaryWriter &stream, const SetTimePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<SetTimePacket, std::error_code>;
};

template <>
struct Serializer<SyncWorldClockStateData> {
    static void serialize(BinaryWriter &stream, const SyncWorldClockStateData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<SyncWorldClockStateData, std::error_code>;
};

template <>
struct Serializer<TimeMarkerData> {
    static void serialize(BinaryWriter &stream, const TimeMarkerData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<TimeMarkerData, std::error_code>;
};

template <>
struct Serializer<WorldClockData> {
    static void serialize(BinaryWriter &stream, const WorldClockData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<WorldClockData, std::error_code>;
};

template <>
struct Serializer<v944::SyncWorldClocksPacket::SyncStateData> {
    static void serialize(BinaryWriter &stream, const v944::SyncWorldClocksPacket::SyncStateData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::SyncWorldClocksPacket::SyncStateData, std::error_code>;
};

template <>
struct Serializer<v944::SyncWorldClocksPacket::InitializeRegistryData> {
    static void serialize(BinaryWriter &stream, const v944::SyncWorldClocksPacket::InitializeRegistryData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::SyncWorldClocksPacket::InitializeRegistryData, std::error_code>;
};

template <>
struct Serializer<v944::SyncWorldClocksPacket::AddTimeMarkerData> {
    static void serialize(BinaryWriter &stream, const v944::SyncWorldClocksPacket::AddTimeMarkerData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::SyncWorldClocksPacket::AddTimeMarkerData, std::error_code>;
};

template <>
struct Serializer<v944::SyncWorldClocksPacket::RemoveTimeMarkerData> {
    static void serialize(BinaryWriter &stream, const v944::SyncWorldClocksPacket::RemoveTimeMarkerData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::SyncWorldClocksPacket::RemoveTimeMarkerData, std::error_code>;
};

template <>
struct Serializer<v944::SyncWorldClocksPacket> {
    static void serialize(BinaryWriter &stream, const v944::SyncWorldClocksPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::SyncWorldClocksPacket, std::error_code>;
};

template <>
struct Serializer<PositionTrackingId> {
    static void serialize(BinaryWriter &stream, const PositionTrackingId &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<PositionTrackingId, std::error_code>;
};

template <>
struct Serializer<PositionTrackingDBServerBroadcastPacket> {
    static void serialize(BinaryWriter &stream, const PositionTrackingDBServerBroadcastPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<PositionTrackingDBServerBroadcastPacket, std::error_code>;
};

template <>
struct Serializer<PositionTrackingDBClientRequestPacket> {
    static void serialize(BinaryWriter &stream, const PositionTrackingDBClientRequestPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<PositionTrackingDBClientRequestPacket, std::error_code>;
};
using SyncWorldClocksPacket = SyncWorldClocksPacket_<2225>;

}  // namespace bedrock::protocol
