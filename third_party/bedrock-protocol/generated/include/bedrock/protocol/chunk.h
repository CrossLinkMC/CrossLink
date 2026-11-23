#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <expected>
#include <optional>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>

#include <bedrock/protocol/detail/reflect.hpp>
#include <bedrock/protocol/enum.hpp>
#include <bedrock/protocol/packet.hpp>
#include <bedrock/protocol/serializer.hpp>
#include <bedrock/protocol/stream.hpp>

#include <bedrock/protocol/common.h>

namespace bedrock::protocol {

struct ChunkPos {
    std::int32_t x{};
    std::int32_t z{};
};

struct RequestChunkRadiusPacket {
    static constexpr int Id = 69;
    std::int32_t chunk_radius{};
    std::uint8_t max_chunk_radius{};
};

struct ChunkRadiusUpdatedPacket {
    static constexpr int Id = 70;
    std::int32_t chunk_radius{};
};

struct NetworkChunkPublisherUpdatePacket {
    static constexpr int Id = 121;
    BlockPos position{};
    std::uint32_t radius{};
    std::vector<ChunkPos> server_built_chunks{};
};

namespace base {

namespace LevelChunkPacket_nested {

struct SubChunkMetadata {
    std::uint64_t blob_id{};
};

}  // namespace LevelChunkPacket_nested

struct LevelChunkPacket {
    using SubChunkMetadata = LevelChunkPacket_nested::SubChunkMetadata;

    static constexpr int Id = 58;
    ChunkPos pos{};
    DimensionType dimension_id{};
    std::uint32_t sub_chunks_count{};
    std::uint16_t client_request_sub_chunk_limit{};
    bool cache_enabled{};
    std::vector<base::LevelChunkPacket::SubChunkMetadata> cache_metadata{};
    std::string serialized_chunk{};
};

struct SubChunkPos {
    std::int32_t x{};
    std::int32_t y{};
    std::int32_t z{};
};

}  // namespace base

namespace legacy {

namespace base {

struct SubChunkPos {
    std::int32_t x{};
    std::int32_t y{};
    std::int32_t z{};
};

}  // namespace base

}  // namespace legacy

namespace base {

namespace SubChunkPacket_nested {

enum class HeightMapDataType : std::uint8_t {
    NoData = 0,
    HasData = 1,
    AllTooHigh = 2,
    AllTooLow = 3,
};

enum class SubChunkRequestResult : std::uint8_t {
    Undefined = 0,
    Success = 1,
    LevelChunkDoesntExist = 2,
    WrongDimension = 3,
    PlayerDoesntExist = 4,
    IndexOutOfBounds = 5,
    SuccessAllAir = 6,
};

struct HeightmapData {
    HeightMapDataType height_map_type{};
    std::array<std::array<std::int8_t, 16>, 16> subchunk_height_map{};
};

struct SubChunkPosOffset {
    std::int8_t x{};
    std::int8_t y{};
    std::int8_t z{};
};

struct SubChunkPacketData {
    SubChunkPosOffset sub_chunk_pos_offset{};
    SubChunkRequestResult result{};
    std::string serialized_sub_chunk{};
    HeightmapData height_map_data{};
    std::uint64_t blob_id{};
};

struct UncachedSubChunkPacketData {
    SubChunkPosOffset sub_chunk_pos_offset{};
    SubChunkRequestResult result{};
    std::string serialized_sub_chunk{};
    HeightmapData height_map_data{};
};

}  // namespace SubChunkPacket_nested

struct SubChunkPacket {
    using HeightMapDataType = SubChunkPacket_nested::HeightMapDataType;
    using SubChunkRequestResult = SubChunkPacket_nested::SubChunkRequestResult;
    using HeightmapData = SubChunkPacket_nested::HeightmapData;
    using SubChunkPosOffset = SubChunkPacket_nested::SubChunkPosOffset;
    using SubChunkPacketData = SubChunkPacket_nested::SubChunkPacketData;
    using UncachedSubChunkPacketData = SubChunkPacket_nested::UncachedSubChunkPacketData;

    static constexpr int Id = 174;
    bool cache_enabled{};
    DimensionType dimension_type{};
    legacy::base::SubChunkPos center_pos{};
    std::vector<base::SubChunkPacket::SubChunkPacketData> sub_chunk_data{};
    std::vector<base::SubChunkPacket::UncachedSubChunkPacketData> uncached_sub_chunk_data{};
};

struct SubChunkRequestPacket {
    static constexpr int Id = 175;
    DimensionType dimension_type{};
    base::SubChunkPos center_pos{};
    std::vector<base::SubChunkPacket::SubChunkPosOffset> sub_chunk_pos_offsets{};
};

}  // namespace base

namespace v818 {

using LevelChunkPacket = base::LevelChunkPacket;

using SubChunkPos = base::SubChunkPos;

}  // namespace v818

namespace legacy {

namespace v818 {

using SubChunkPos = base::SubChunkPos;

}  // namespace v818

}  // namespace legacy

namespace v818 {

namespace SubChunkPacket_nested {

enum class HeightMapDataType : std::uint8_t {
    NoData = 0,
    HasData = 1,
    AllTooHigh = 2,
    AllTooLow = 3,
    AllCopied = 4,
};

using SubChunkRequestResult = base::SubChunkPacket::SubChunkRequestResult;

struct HeightmapData {
    HeightMapDataType height_map_type{};
    std::array<std::array<std::int8_t, 16>, 16> subchunk_height_map{};
    HeightMapDataType render_height_map_type{};
    std::array<std::array<std::int8_t, 16>, 16> subchunk_render_height_map{};
};

using SubChunkPosOffset = base::SubChunkPacket::SubChunkPosOffset;

struct SubChunkPacketData {
    SubChunkPosOffset sub_chunk_pos_offset{};
    SubChunkRequestResult result{};
    std::string serialized_sub_chunk{};
    HeightmapData height_map_data{};
    std::uint64_t blob_id{};
};

struct UncachedSubChunkPacketData {
    SubChunkPosOffset sub_chunk_pos_offset{};
    SubChunkRequestResult result{};
    std::string serialized_sub_chunk{};
    HeightmapData height_map_data{};
};

}  // namespace SubChunkPacket_nested

struct SubChunkPacket {
    using HeightMapDataType = SubChunkPacket_nested::HeightMapDataType;
    using SubChunkRequestResult = SubChunkPacket_nested::SubChunkRequestResult;
    using HeightmapData = SubChunkPacket_nested::HeightmapData;
    using SubChunkPosOffset = SubChunkPacket_nested::SubChunkPosOffset;
    using SubChunkPacketData = SubChunkPacket_nested::SubChunkPacketData;
    using UncachedSubChunkPacketData = SubChunkPacket_nested::UncachedSubChunkPacketData;

    static constexpr int Id = 174;
    bool cache_enabled{};
    DimensionType dimension_type{};
    legacy::base::SubChunkPos center_pos{};
    std::vector<v818::SubChunkPacket::SubChunkPacketData> sub_chunk_data{};
    std::vector<v818::SubChunkPacket::UncachedSubChunkPacketData> uncached_sub_chunk_data{};
};

struct SubChunkRequestPacket {
    static constexpr int Id = 175;
    DimensionType dimension_type{};
    base::SubChunkPos center_pos{};
    std::vector<v818::SubChunkPacket::SubChunkPosOffset> sub_chunk_pos_offsets{};
};

}  // namespace v818

namespace v1001 {

using LevelChunkPacket = base::LevelChunkPacket;

struct SubChunkPos {
    std::int32_t x{};
    std::int32_t y{};
    std::int32_t z{};
};

}  // namespace v1001

namespace legacy {

namespace v1001 {

using SubChunkPos = base::SubChunkPos;

}  // namespace v1001

}  // namespace legacy

namespace v1001 {

namespace SubChunkPacket_nested {

enum class HeightMapDataType : std::uint8_t {
    NoData = 0,
    HasData = 1,
    AllTooHigh = 2,
    AllTooLow = 3,
    AllCopied = 4,
};

using SubChunkRequestResult = base::SubChunkPacket::SubChunkRequestResult;

struct HeightmapData {
    HeightMapDataType height_map_type{};
    std::array<std::array<std::int8_t, 16>, 16> subchunk_height_map{};
    HeightMapDataType render_height_map_type{};
    std::array<std::array<std::int8_t, 16>, 16> subchunk_render_height_map{};
};

using SubChunkPosOffset = base::SubChunkPacket::SubChunkPosOffset;

struct SubChunkPacketData {
    SubChunkPosOffset sub_chunk_pos_offset{};
    SubChunkRequestResult result{};
    std::string serialized_sub_chunk{};
    HeightmapData height_map_data{};
    std::uint64_t blob_id{};
};

struct UncachedSubChunkPacketData {
    SubChunkPosOffset sub_chunk_pos_offset{};
    SubChunkRequestResult result{};
    std::string serialized_sub_chunk{};
    HeightmapData height_map_data{};
};

}  // namespace SubChunkPacket_nested

struct SubChunkPacket {
    using HeightMapDataType = SubChunkPacket_nested::HeightMapDataType;
    using SubChunkRequestResult = SubChunkPacket_nested::SubChunkRequestResult;
    using HeightmapData = SubChunkPacket_nested::HeightmapData;
    using SubChunkPosOffset = SubChunkPacket_nested::SubChunkPosOffset;
    using SubChunkPacketData = SubChunkPacket_nested::SubChunkPacketData;
    using UncachedSubChunkPacketData = SubChunkPacket_nested::UncachedSubChunkPacketData;

    static constexpr int Id = 174;
    bool cache_enabled{};
    DimensionType dimension_type{};
    legacy::base::SubChunkPos center_pos{};
    std::vector<v1001::SubChunkPacket::SubChunkPacketData> sub_chunk_data{};
    std::vector<v1001::SubChunkPacket::UncachedSubChunkPacketData> uncached_sub_chunk_data{};
};

struct SubChunkRequestPacket {
    static constexpr int Id = 175;
    DimensionType dimension_type{};
    std::vector<v1001::SubChunkPacket::SubChunkPosOffset> sub_chunk_pos_offsets{};
    v1001::SubChunkPos center_pos{};
};

}  // namespace v1001

namespace v2168 {

namespace LevelChunkPacket_nested {

using SubChunkMetadata = base::LevelChunkPacket::SubChunkMetadata;

}  // namespace LevelChunkPacket_nested

struct LevelChunkPacket {
    using SubChunkMetadata = LevelChunkPacket_nested::SubChunkMetadata;

    static constexpr int Id = 58;
    ChunkPos pos{};
    DimensionType dimension_id{};
    std::uint32_t sub_chunks_count{};
    std::optional<std::int32_t> client_request_sub_chunk_limit{};
    bool cache_enabled{};
    std::vector<v2168::LevelChunkPacket::SubChunkMetadata> cache_metadata{};
    std::string serialized_chunk{};
};

using SubChunkPos = v1001::SubChunkPos;

namespace SubChunkPacket_nested {

enum class HeightMapDataType : std::uint8_t {
    NoData = 0,
    HasData = 1,
    AllTooHigh = 2,
    AllTooLow = 3,
    AllCopied = 4,
};

using SubChunkRequestResult = base::SubChunkPacket::SubChunkRequestResult;

struct HeightmapData {
    HeightMapDataType height_map_type{};
    std::optional<std::array<std::array<std::int8_t, 16>, 16>> subchunk_height_map{};
    HeightMapDataType render_height_map_type{};
    std::optional<std::array<std::array<std::int8_t, 16>, 16>> subchunk_render_height_map{};
};

using SubChunkPosOffset = base::SubChunkPacket::SubChunkPosOffset;

struct SubChunkPacketData {
    SubChunkPosOffset sub_chunk_pos_offset{};
    SubChunkRequestResult result{};
    std::optional<std::string> serialized_sub_chunk{};
    HeightmapData height_map_data{};
    std::optional<std::uint64_t> blob_id{};
};

}  // namespace SubChunkPacket_nested

struct SubChunkPacket {
    using HeightMapDataType = SubChunkPacket_nested::HeightMapDataType;
    using SubChunkRequestResult = SubChunkPacket_nested::SubChunkRequestResult;
    using HeightmapData = SubChunkPacket_nested::HeightmapData;
    using SubChunkPosOffset = SubChunkPacket_nested::SubChunkPosOffset;
    using SubChunkPacketData = SubChunkPacket_nested::SubChunkPacketData;

    static constexpr int Id = 174;
    bool cache_enabled{};
    DimensionType dimension_type{};
    v1001::SubChunkPos center_pos{};
    std::vector<v2168::SubChunkPacket::SubChunkPacketData> sub_chunk_data{};
};

struct SubChunkRequestPacket {
    static constexpr int Id = 175;
    DimensionType dimension_type{};
    std::vector<v2168::SubChunkPacket::SubChunkPosOffset> sub_chunk_pos_offsets{};
    v1001::SubChunkPos center_pos{};
};

}  // namespace v2168

namespace v2193 {

using LevelChunkPacket = v2168::LevelChunkPacket;

using SubChunkPos = v1001::SubChunkPos;

namespace SubChunkPacket_nested {

enum class HeightMapDataType : std::uint8_t {
    NoData = 0,
    HasData = 1,
    AllTooHigh = 2,
    AllTooLow = 3,
    AllCopied = 4,
};

using SubChunkRequestResult = base::SubChunkPacket::SubChunkRequestResult;

struct HeightmapData {
    HeightMapDataType height_map_type{};
    std::optional<std::array<std::vector<std::int8_t>, 16>> subchunk_height_map{};
    HeightMapDataType render_height_map_type{};
    std::optional<std::array<std::vector<std::int8_t>, 16>> subchunk_render_height_map{};
};

using SubChunkPosOffset = base::SubChunkPacket::SubChunkPosOffset;

struct SubChunkPacketData {
    SubChunkPosOffset sub_chunk_pos_offset{};
    SubChunkRequestResult result{};
    std::optional<std::string> serialized_sub_chunk{};
    HeightmapData height_map_data{};
    std::optional<std::uint64_t> blob_id{};
};

}  // namespace SubChunkPacket_nested

struct SubChunkPacket {
    using HeightMapDataType = SubChunkPacket_nested::HeightMapDataType;
    using SubChunkRequestResult = SubChunkPacket_nested::SubChunkRequestResult;
    using HeightmapData = SubChunkPacket_nested::HeightmapData;
    using SubChunkPosOffset = SubChunkPacket_nested::SubChunkPosOffset;
    using SubChunkPacketData = SubChunkPacket_nested::SubChunkPacketData;

    static constexpr int Id = 174;
    bool cache_enabled{};
    DimensionType dimension_type{};
    v1001::SubChunkPos center_pos{};
    std::vector<v2193::SubChunkPacket::SubChunkPacketData> sub_chunk_data{};
};

struct SubChunkRequestPacket {
    static constexpr int Id = 175;
    DimensionType dimension_type{};
    std::vector<v2193::SubChunkPacket::SubChunkPosOffset> sub_chunk_pos_offsets{};
    v1001::SubChunkPos center_pos{};
};

}  // namespace v2193

namespace v2225 {

namespace LevelChunkPacket_nested {

using SubChunkMetadata = base::LevelChunkPacket::SubChunkMetadata;

}  // namespace LevelChunkPacket_nested

struct LevelChunkPacket {
    using SubChunkMetadata = LevelChunkPacket_nested::SubChunkMetadata;

    static constexpr int Id = 58;
    ChunkPos pos{};
    DimensionType dimension_id{};
    std::uint32_t sub_chunks_count{};
    std::optional<std::int32_t> client_request_sub_chunk_limit{};
    bool cache_enabled{};
    std::vector<v2225::LevelChunkPacket::SubChunkMetadata> cache_metadata{};
    std::string serialized_chunk{};
    bool is_client_biome_update{};
};

using SubChunkPos = v1001::SubChunkPos;

using SubChunkPacket = v2193::SubChunkPacket;

using SubChunkRequestPacket = v2193::SubChunkRequestPacket;

}  // namespace v2225

namespace detail {

template <int V>
struct LevelChunkPacket_;

template <int V> requires (V < 2168)
struct LevelChunkPacket_<V> { using type = base::LevelChunkPacket; };

template <int V> requires (V >= 2168 && V < 2225)
struct LevelChunkPacket_<V> { using type = v2168::LevelChunkPacket; };

template <int V> requires (V >= 2225)
struct LevelChunkPacket_<V> { using type = v2225::LevelChunkPacket; };

template <int V>
struct SubChunkPos_;

template <int V> requires (V < 1001)
struct SubChunkPos_<V> { using type = base::SubChunkPos; };

template <int V> requires (V >= 1001)
struct SubChunkPos_<V> { using type = v1001::SubChunkPos; };

template <int V>
struct SubChunkPacket_;

template <int V> requires (V < 818)
struct SubChunkPacket_<V> { using type = base::SubChunkPacket; };

template <int V> requires (V >= 818 && V < 1001)
struct SubChunkPacket_<V> { using type = v818::SubChunkPacket; };

template <int V> requires (V >= 1001 && V < 2168)
struct SubChunkPacket_<V> { using type = v1001::SubChunkPacket; };

template <int V> requires (V >= 2168 && V < 2193)
struct SubChunkPacket_<V> { using type = v2168::SubChunkPacket; };

template <int V> requires (V >= 2193)
struct SubChunkPacket_<V> { using type = v2193::SubChunkPacket; };

template <int V>
struct SubChunkRequestPacket_;

template <int V> requires (V < 818)
struct SubChunkRequestPacket_<V> { using type = base::SubChunkRequestPacket; };

template <int V> requires (V >= 818 && V < 1001)
struct SubChunkRequestPacket_<V> { using type = v818::SubChunkRequestPacket; };

template <int V> requires (V >= 1001 && V < 2168)
struct SubChunkRequestPacket_<V> { using type = v1001::SubChunkRequestPacket; };

template <int V> requires (V >= 2168 && V < 2193)
struct SubChunkRequestPacket_<V> { using type = v2168::SubChunkRequestPacket; };

template <int V> requires (V >= 2193)
struct SubChunkRequestPacket_<V> { using type = v2193::SubChunkRequestPacket; };

}  // namespace detail

template <int V> using LevelChunkPacket_ = typename detail::LevelChunkPacket_<V>::type;
template <int V> using SubChunkPos_ = typename detail::SubChunkPos_<V>::type;
template <int V> using SubChunkPacket_ = typename detail::SubChunkPacket_<V>::type;
template <int V> using SubChunkRequestPacket_ = typename detail::SubChunkRequestPacket_<V>::type;

namespace legacy {

namespace detail {

template <int V>
struct SubChunkPos_;

template <int V> requires (V < 2168)
struct SubChunkPos_<V> { using type = base::SubChunkPos; };

}  // namespace detail

template <int V> using SubChunkPos_ = typename detail::SubChunkPos_<V>::type;

}  // namespace legacy

template <int V>
struct packet_of<V, 58> { using type = LevelChunkPacket_<V>; };

template <int V>
struct packet_of<V, 69> { using type = RequestChunkRadiusPacket; };

template <int V>
struct packet_of<V, 70> { using type = ChunkRadiusUpdatedPacket; };

template <int V>
struct packet_of<V, 121> { using type = NetworkChunkPublisherUpdatePacket; };

template <int V>
struct packet_of<V, 174> { using type = SubChunkPacket_<V>; };

template <int V>
struct packet_of<V, 175> { using type = SubChunkRequestPacket_<V>; };

namespace detail {

template <>
inline constexpr std::array<base::SubChunkPacket::HeightMapDataType, 4> values_v<base::SubChunkPacket::HeightMapDataType>{{
    base::SubChunkPacket::HeightMapDataType::NoData,
    base::SubChunkPacket::HeightMapDataType::HasData,
    base::SubChunkPacket::HeightMapDataType::AllTooHigh,
    base::SubChunkPacket::HeightMapDataType::AllTooLow,
}};

template <>
inline constexpr std::array<std::string_view, 4> names_v<base::SubChunkPacket::HeightMapDataType>{{
    "nodata",
    "hasdata",
    "alltoohigh",
    "alltoolow",
}};

template <>
inline constexpr std::string_view type_name_v<base::SubChunkPacket::HeightMapDataType>{"SubChunkPacket::HeightMapDataType"};

template <>
inline constexpr std::array<base::SubChunkPacket::SubChunkRequestResult, 7> values_v<base::SubChunkPacket::SubChunkRequestResult>{{
    base::SubChunkPacket::SubChunkRequestResult::Undefined,
    base::SubChunkPacket::SubChunkRequestResult::Success,
    base::SubChunkPacket::SubChunkRequestResult::LevelChunkDoesntExist,
    base::SubChunkPacket::SubChunkRequestResult::WrongDimension,
    base::SubChunkPacket::SubChunkRequestResult::PlayerDoesntExist,
    base::SubChunkPacket::SubChunkRequestResult::IndexOutOfBounds,
    base::SubChunkPacket::SubChunkRequestResult::SuccessAllAir,
}};

template <>
inline constexpr std::array<std::string_view, 7> names_v<base::SubChunkPacket::SubChunkRequestResult>{{
    "undefined",
    "success",
    "levelchunkdoesntexist",
    "wrongdimension",
    "playerdoesntexist",
    "indexoutofbounds",
    "successallair",
}};

template <>
inline constexpr std::string_view type_name_v<base::SubChunkPacket::SubChunkRequestResult>{"SubChunkPacket::SubChunkRequestResult"};

template <>
inline constexpr std::array<v818::SubChunkPacket::HeightMapDataType, 5> values_v<v818::SubChunkPacket::HeightMapDataType>{{
    v818::SubChunkPacket::HeightMapDataType::NoData,
    v818::SubChunkPacket::HeightMapDataType::HasData,
    v818::SubChunkPacket::HeightMapDataType::AllTooHigh,
    v818::SubChunkPacket::HeightMapDataType::AllTooLow,
    v818::SubChunkPacket::HeightMapDataType::AllCopied,
}};

template <>
inline constexpr std::array<std::string_view, 5> names_v<v818::SubChunkPacket::HeightMapDataType>{{
    "nodata",
    "hasdata",
    "alltoohigh",
    "alltoolow",
    "allcopied",
}};

template <>
inline constexpr std::string_view type_name_v<v818::SubChunkPacket::HeightMapDataType>{"SubChunkPacket::HeightMapDataType"};

template <>
inline constexpr std::array<v1001::SubChunkPacket::HeightMapDataType, 5> values_v<v1001::SubChunkPacket::HeightMapDataType>{{
    v1001::SubChunkPacket::HeightMapDataType::NoData,
    v1001::SubChunkPacket::HeightMapDataType::HasData,
    v1001::SubChunkPacket::HeightMapDataType::AllTooHigh,
    v1001::SubChunkPacket::HeightMapDataType::AllTooLow,
    v1001::SubChunkPacket::HeightMapDataType::AllCopied,
}};

template <>
inline constexpr std::array<std::string_view, 5> names_v<v1001::SubChunkPacket::HeightMapDataType>{{
    "nodata",
    "hasdata",
    "alltoohigh",
    "alltoolow",
    "allcopied",
}};

template <>
inline constexpr std::string_view type_name_v<v1001::SubChunkPacket::HeightMapDataType>{"SubChunkPacket::HeightMapDataType"};

template <>
inline constexpr std::array<v2168::SubChunkPacket::HeightMapDataType, 5> values_v<v2168::SubChunkPacket::HeightMapDataType>{{
    v2168::SubChunkPacket::HeightMapDataType::NoData,
    v2168::SubChunkPacket::HeightMapDataType::HasData,
    v2168::SubChunkPacket::HeightMapDataType::AllTooHigh,
    v2168::SubChunkPacket::HeightMapDataType::AllTooLow,
    v2168::SubChunkPacket::HeightMapDataType::AllCopied,
}};

template <>
inline constexpr std::array<std::string_view, 5> names_v<v2168::SubChunkPacket::HeightMapDataType>{{
    "nodata",
    "hasdata",
    "alltoohigh",
    "alltoolow",
    "allcopied",
}};

template <>
inline constexpr std::string_view type_name_v<v2168::SubChunkPacket::HeightMapDataType>{"SubChunkPacket::HeightMapDataType"};

template <>
inline constexpr std::array<v2193::SubChunkPacket::HeightMapDataType, 5> values_v<v2193::SubChunkPacket::HeightMapDataType>{{
    v2193::SubChunkPacket::HeightMapDataType::NoData,
    v2193::SubChunkPacket::HeightMapDataType::HasData,
    v2193::SubChunkPacket::HeightMapDataType::AllTooHigh,
    v2193::SubChunkPacket::HeightMapDataType::AllTooLow,
    v2193::SubChunkPacket::HeightMapDataType::AllCopied,
}};

template <>
inline constexpr std::array<std::string_view, 5> names_v<v2193::SubChunkPacket::HeightMapDataType>{{
    "nodata",
    "hasdata",
    "alltoohigh",
    "alltoolow",
    "allcopied",
}};

template <>
inline constexpr std::string_view type_name_v<v2193::SubChunkPacket::HeightMapDataType>{"SubChunkPacket::HeightMapDataType"};

}  // namespace detail

namespace detail {

template <>
inline constexpr bool is_reflected_struct_v<ChunkPos> = true;

template <>
inline constexpr std::string_view struct_name_v<ChunkPos>{"ChunkPos"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<ChunkPos>{{
    "x",
    "z",
}};

template <>
struct field_accessor<ChunkPos> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.x;
        }
        else {
            return value.z;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::LevelChunkPacket::SubChunkMetadata> = true;

template <>
inline constexpr std::string_view struct_name_v<base::LevelChunkPacket::SubChunkMetadata>{"LevelChunkPacket::SubChunkMetadata"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::LevelChunkPacket::SubChunkMetadata>{{
    "blob_id",
}};

template <>
struct field_accessor<base::LevelChunkPacket::SubChunkMetadata> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.blob_id;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::LevelChunkPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::LevelChunkPacket>{"LevelChunkPacket"};

template <>
inline constexpr std::array<std::string_view, 7> field_names_v<base::LevelChunkPacket>{{
    "pos",
    "dimension_id",
    "sub_chunks_count",
    "client_request_sub_chunk_limit",
    "cache_enabled",
    "cache_metadata",
    "serialized_chunk",
}};

template <>
struct field_accessor<base::LevelChunkPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.pos;
        }
        else if constexpr (I == 1) {
            return value.dimension_id;
        }
        else if constexpr (I == 2) {
            return value.sub_chunks_count;
        }
        else if constexpr (I == 3) {
            return value.client_request_sub_chunk_limit;
        }
        else if constexpr (I == 4) {
            return value.cache_enabled;
        }
        else if constexpr (I == 5) {
            return value.cache_metadata;
        }
        else {
            return value.serialized_chunk;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::LevelChunkPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::LevelChunkPacket>{"LevelChunkPacket"};

template <>
inline constexpr std::array<std::string_view, 7> field_names_v<v2168::LevelChunkPacket>{{
    "pos",
    "dimension_id",
    "sub_chunks_count",
    "client_request_sub_chunk_limit",
    "cache_enabled",
    "cache_metadata",
    "serialized_chunk",
}};

template <>
struct field_accessor<v2168::LevelChunkPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.pos;
        }
        else if constexpr (I == 1) {
            return value.dimension_id;
        }
        else if constexpr (I == 2) {
            return value.sub_chunks_count;
        }
        else if constexpr (I == 3) {
            return value.client_request_sub_chunk_limit;
        }
        else if constexpr (I == 4) {
            return value.cache_enabled;
        }
        else if constexpr (I == 5) {
            return value.cache_metadata;
        }
        else {
            return value.serialized_chunk;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::LevelChunkPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::LevelChunkPacket>{"LevelChunkPacket"};

template <>
inline constexpr std::array<std::string_view, 8> field_names_v<v2225::LevelChunkPacket>{{
    "pos",
    "dimension_id",
    "sub_chunks_count",
    "client_request_sub_chunk_limit",
    "cache_enabled",
    "cache_metadata",
    "serialized_chunk",
    "is_client_biome_update",
}};

template <>
struct field_accessor<v2225::LevelChunkPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.pos;
        }
        else if constexpr (I == 1) {
            return value.dimension_id;
        }
        else if constexpr (I == 2) {
            return value.sub_chunks_count;
        }
        else if constexpr (I == 3) {
            return value.client_request_sub_chunk_limit;
        }
        else if constexpr (I == 4) {
            return value.cache_enabled;
        }
        else if constexpr (I == 5) {
            return value.cache_metadata;
        }
        else if constexpr (I == 6) {
            return value.serialized_chunk;
        }
        else {
            return value.is_client_biome_update;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::SubChunkPos> = true;

template <>
inline constexpr std::string_view struct_name_v<base::SubChunkPos>{"SubChunkPos"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<base::SubChunkPos>{{
    "x",
    "y",
    "z",
}};

template <>
struct field_accessor<base::SubChunkPos> {
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
inline constexpr bool is_reflected_struct_v<v1001::SubChunkPos> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::SubChunkPos>{"SubChunkPos"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v1001::SubChunkPos>{{
    "x",
    "y",
    "z",
}};

template <>
struct field_accessor<v1001::SubChunkPos> {
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
inline constexpr bool is_reflected_struct_v<legacy::base::SubChunkPos> = true;

template <>
inline constexpr std::string_view struct_name_v<legacy::base::SubChunkPos>{"SubChunkPos"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<legacy::base::SubChunkPos>{{
    "x",
    "y",
    "z",
}};

template <>
struct field_accessor<legacy::base::SubChunkPos> {
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
inline constexpr bool is_reflected_struct_v<base::SubChunkPacket::HeightmapData> = true;

template <>
inline constexpr std::string_view struct_name_v<base::SubChunkPacket::HeightmapData>{"SubChunkPacket::HeightmapData"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<base::SubChunkPacket::HeightmapData>{{
    "height_map_type",
    "subchunk_height_map",
}};

template <>
struct field_accessor<base::SubChunkPacket::HeightmapData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.height_map_type;
        }
        else {
            return value.subchunk_height_map;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::SubChunkPacket::SubChunkPosOffset> = true;

template <>
inline constexpr std::string_view struct_name_v<base::SubChunkPacket::SubChunkPosOffset>{"SubChunkPacket::SubChunkPosOffset"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<base::SubChunkPacket::SubChunkPosOffset>{{
    "x",
    "y",
    "z",
}};

template <>
struct field_accessor<base::SubChunkPacket::SubChunkPosOffset> {
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
inline constexpr bool is_reflected_struct_v<base::SubChunkPacket::SubChunkPacketData> = true;

template <>
inline constexpr std::string_view struct_name_v<base::SubChunkPacket::SubChunkPacketData>{"SubChunkPacket::SubChunkPacketData"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<base::SubChunkPacket::SubChunkPacketData>{{
    "sub_chunk_pos_offset",
    "result",
    "serialized_sub_chunk",
    "height_map_data",
    "blob_id",
}};

template <>
struct field_accessor<base::SubChunkPacket::SubChunkPacketData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.sub_chunk_pos_offset;
        }
        else if constexpr (I == 1) {
            return value.result;
        }
        else if constexpr (I == 2) {
            return value.serialized_sub_chunk;
        }
        else if constexpr (I == 3) {
            return value.height_map_data;
        }
        else {
            return value.blob_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::SubChunkPacket::UncachedSubChunkPacketData> = true;

template <>
inline constexpr std::string_view struct_name_v<base::SubChunkPacket::UncachedSubChunkPacketData>{"SubChunkPacket::UncachedSubChunkPacketData"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<base::SubChunkPacket::UncachedSubChunkPacketData>{{
    "sub_chunk_pos_offset",
    "result",
    "serialized_sub_chunk",
    "height_map_data",
}};

template <>
struct field_accessor<base::SubChunkPacket::UncachedSubChunkPacketData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.sub_chunk_pos_offset;
        }
        else if constexpr (I == 1) {
            return value.result;
        }
        else if constexpr (I == 2) {
            return value.serialized_sub_chunk;
        }
        else {
            return value.height_map_data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v818::SubChunkPacket::HeightmapData> = true;

template <>
inline constexpr std::string_view struct_name_v<v818::SubChunkPacket::HeightmapData>{"SubChunkPacket::HeightmapData"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v818::SubChunkPacket::HeightmapData>{{
    "height_map_type",
    "subchunk_height_map",
    "render_height_map_type",
    "subchunk_render_height_map",
}};

template <>
struct field_accessor<v818::SubChunkPacket::HeightmapData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.height_map_type;
        }
        else if constexpr (I == 1) {
            return value.subchunk_height_map;
        }
        else if constexpr (I == 2) {
            return value.render_height_map_type;
        }
        else {
            return value.subchunk_render_height_map;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v818::SubChunkPacket::SubChunkPacketData> = true;

template <>
inline constexpr std::string_view struct_name_v<v818::SubChunkPacket::SubChunkPacketData>{"SubChunkPacket::SubChunkPacketData"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v818::SubChunkPacket::SubChunkPacketData>{{
    "sub_chunk_pos_offset",
    "result",
    "serialized_sub_chunk",
    "height_map_data",
    "blob_id",
}};

template <>
struct field_accessor<v818::SubChunkPacket::SubChunkPacketData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.sub_chunk_pos_offset;
        }
        else if constexpr (I == 1) {
            return value.result;
        }
        else if constexpr (I == 2) {
            return value.serialized_sub_chunk;
        }
        else if constexpr (I == 3) {
            return value.height_map_data;
        }
        else {
            return value.blob_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v818::SubChunkPacket::UncachedSubChunkPacketData> = true;

template <>
inline constexpr std::string_view struct_name_v<v818::SubChunkPacket::UncachedSubChunkPacketData>{"SubChunkPacket::UncachedSubChunkPacketData"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v818::SubChunkPacket::UncachedSubChunkPacketData>{{
    "sub_chunk_pos_offset",
    "result",
    "serialized_sub_chunk",
    "height_map_data",
}};

template <>
struct field_accessor<v818::SubChunkPacket::UncachedSubChunkPacketData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.sub_chunk_pos_offset;
        }
        else if constexpr (I == 1) {
            return value.result;
        }
        else if constexpr (I == 2) {
            return value.serialized_sub_chunk;
        }
        else {
            return value.height_map_data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::SubChunkPacket::HeightmapData> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::SubChunkPacket::HeightmapData>{"SubChunkPacket::HeightmapData"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v1001::SubChunkPacket::HeightmapData>{{
    "height_map_type",
    "subchunk_height_map",
    "render_height_map_type",
    "subchunk_render_height_map",
}};

template <>
struct field_accessor<v1001::SubChunkPacket::HeightmapData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.height_map_type;
        }
        else if constexpr (I == 1) {
            return value.subchunk_height_map;
        }
        else if constexpr (I == 2) {
            return value.render_height_map_type;
        }
        else {
            return value.subchunk_render_height_map;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::SubChunkPacket::SubChunkPacketData> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::SubChunkPacket::SubChunkPacketData>{"SubChunkPacket::SubChunkPacketData"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v1001::SubChunkPacket::SubChunkPacketData>{{
    "sub_chunk_pos_offset",
    "result",
    "serialized_sub_chunk",
    "height_map_data",
    "blob_id",
}};

template <>
struct field_accessor<v1001::SubChunkPacket::SubChunkPacketData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.sub_chunk_pos_offset;
        }
        else if constexpr (I == 1) {
            return value.result;
        }
        else if constexpr (I == 2) {
            return value.serialized_sub_chunk;
        }
        else if constexpr (I == 3) {
            return value.height_map_data;
        }
        else {
            return value.blob_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::SubChunkPacket::UncachedSubChunkPacketData> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::SubChunkPacket::UncachedSubChunkPacketData>{"SubChunkPacket::UncachedSubChunkPacketData"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v1001::SubChunkPacket::UncachedSubChunkPacketData>{{
    "sub_chunk_pos_offset",
    "result",
    "serialized_sub_chunk",
    "height_map_data",
}};

template <>
struct field_accessor<v1001::SubChunkPacket::UncachedSubChunkPacketData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.sub_chunk_pos_offset;
        }
        else if constexpr (I == 1) {
            return value.result;
        }
        else if constexpr (I == 2) {
            return value.serialized_sub_chunk;
        }
        else {
            return value.height_map_data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::SubChunkPacket::HeightmapData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::SubChunkPacket::HeightmapData>{"SubChunkPacket::HeightmapData"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v2168::SubChunkPacket::HeightmapData>{{
    "height_map_type",
    "subchunk_height_map",
    "render_height_map_type",
    "subchunk_render_height_map",
}};

template <>
struct field_accessor<v2168::SubChunkPacket::HeightmapData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.height_map_type;
        }
        else if constexpr (I == 1) {
            return value.subchunk_height_map;
        }
        else if constexpr (I == 2) {
            return value.render_height_map_type;
        }
        else {
            return value.subchunk_render_height_map;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::SubChunkPacket::SubChunkPacketData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::SubChunkPacket::SubChunkPacketData>{"SubChunkPacket::SubChunkPacketData"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v2168::SubChunkPacket::SubChunkPacketData>{{
    "sub_chunk_pos_offset",
    "result",
    "serialized_sub_chunk",
    "height_map_data",
    "blob_id",
}};

template <>
struct field_accessor<v2168::SubChunkPacket::SubChunkPacketData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.sub_chunk_pos_offset;
        }
        else if constexpr (I == 1) {
            return value.result;
        }
        else if constexpr (I == 2) {
            return value.serialized_sub_chunk;
        }
        else if constexpr (I == 3) {
            return value.height_map_data;
        }
        else {
            return value.blob_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2193::SubChunkPacket::HeightmapData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2193::SubChunkPacket::HeightmapData>{"SubChunkPacket::HeightmapData"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v2193::SubChunkPacket::HeightmapData>{{
    "height_map_type",
    "subchunk_height_map",
    "render_height_map_type",
    "subchunk_render_height_map",
}};

template <>
struct field_accessor<v2193::SubChunkPacket::HeightmapData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.height_map_type;
        }
        else if constexpr (I == 1) {
            return value.subchunk_height_map;
        }
        else if constexpr (I == 2) {
            return value.render_height_map_type;
        }
        else {
            return value.subchunk_render_height_map;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2193::SubChunkPacket::SubChunkPacketData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2193::SubChunkPacket::SubChunkPacketData>{"SubChunkPacket::SubChunkPacketData"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v2193::SubChunkPacket::SubChunkPacketData>{{
    "sub_chunk_pos_offset",
    "result",
    "serialized_sub_chunk",
    "height_map_data",
    "blob_id",
}};

template <>
struct field_accessor<v2193::SubChunkPacket::SubChunkPacketData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.sub_chunk_pos_offset;
        }
        else if constexpr (I == 1) {
            return value.result;
        }
        else if constexpr (I == 2) {
            return value.serialized_sub_chunk;
        }
        else if constexpr (I == 3) {
            return value.height_map_data;
        }
        else {
            return value.blob_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::SubChunkPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::SubChunkPacket>{"SubChunkPacket"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<base::SubChunkPacket>{{
    "cache_enabled",
    "dimension_type",
    "center_pos",
    "sub_chunk_data",
    "uncached_sub_chunk_data",
}};

template <>
struct field_accessor<base::SubChunkPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.cache_enabled;
        }
        else if constexpr (I == 1) {
            return value.dimension_type;
        }
        else if constexpr (I == 2) {
            return value.center_pos;
        }
        else if constexpr (I == 3) {
            return value.sub_chunk_data;
        }
        else {
            return value.uncached_sub_chunk_data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v818::SubChunkPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v818::SubChunkPacket>{"SubChunkPacket"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v818::SubChunkPacket>{{
    "cache_enabled",
    "dimension_type",
    "center_pos",
    "sub_chunk_data",
    "uncached_sub_chunk_data",
}};

template <>
struct field_accessor<v818::SubChunkPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.cache_enabled;
        }
        else if constexpr (I == 1) {
            return value.dimension_type;
        }
        else if constexpr (I == 2) {
            return value.center_pos;
        }
        else if constexpr (I == 3) {
            return value.sub_chunk_data;
        }
        else {
            return value.uncached_sub_chunk_data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::SubChunkPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::SubChunkPacket>{"SubChunkPacket"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v1001::SubChunkPacket>{{
    "cache_enabled",
    "dimension_type",
    "center_pos",
    "sub_chunk_data",
    "uncached_sub_chunk_data",
}};

template <>
struct field_accessor<v1001::SubChunkPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.cache_enabled;
        }
        else if constexpr (I == 1) {
            return value.dimension_type;
        }
        else if constexpr (I == 2) {
            return value.center_pos;
        }
        else if constexpr (I == 3) {
            return value.sub_chunk_data;
        }
        else {
            return value.uncached_sub_chunk_data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::SubChunkPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::SubChunkPacket>{"SubChunkPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v2168::SubChunkPacket>{{
    "cache_enabled",
    "dimension_type",
    "center_pos",
    "sub_chunk_data",
}};

template <>
struct field_accessor<v2168::SubChunkPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.cache_enabled;
        }
        else if constexpr (I == 1) {
            return value.dimension_type;
        }
        else if constexpr (I == 2) {
            return value.center_pos;
        }
        else {
            return value.sub_chunk_data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2193::SubChunkPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2193::SubChunkPacket>{"SubChunkPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v2193::SubChunkPacket>{{
    "cache_enabled",
    "dimension_type",
    "center_pos",
    "sub_chunk_data",
}};

template <>
struct field_accessor<v2193::SubChunkPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.cache_enabled;
        }
        else if constexpr (I == 1) {
            return value.dimension_type;
        }
        else if constexpr (I == 2) {
            return value.center_pos;
        }
        else {
            return value.sub_chunk_data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::SubChunkRequestPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::SubChunkRequestPacket>{"SubChunkRequestPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<base::SubChunkRequestPacket>{{
    "dimension_type",
    "center_pos",
    "sub_chunk_pos_offsets",
}};

template <>
struct field_accessor<base::SubChunkRequestPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.dimension_type;
        }
        else if constexpr (I == 1) {
            return value.center_pos;
        }
        else {
            return value.sub_chunk_pos_offsets;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v818::SubChunkRequestPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v818::SubChunkRequestPacket>{"SubChunkRequestPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v818::SubChunkRequestPacket>{{
    "dimension_type",
    "center_pos",
    "sub_chunk_pos_offsets",
}};

template <>
struct field_accessor<v818::SubChunkRequestPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.dimension_type;
        }
        else if constexpr (I == 1) {
            return value.center_pos;
        }
        else {
            return value.sub_chunk_pos_offsets;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::SubChunkRequestPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::SubChunkRequestPacket>{"SubChunkRequestPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v1001::SubChunkRequestPacket>{{
    "dimension_type",
    "sub_chunk_pos_offsets",
    "center_pos",
}};

template <>
struct field_accessor<v1001::SubChunkRequestPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.dimension_type;
        }
        else if constexpr (I == 1) {
            return value.sub_chunk_pos_offsets;
        }
        else {
            return value.center_pos;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::SubChunkRequestPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::SubChunkRequestPacket>{"SubChunkRequestPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v2168::SubChunkRequestPacket>{{
    "dimension_type",
    "sub_chunk_pos_offsets",
    "center_pos",
}};

template <>
struct field_accessor<v2168::SubChunkRequestPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.dimension_type;
        }
        else if constexpr (I == 1) {
            return value.sub_chunk_pos_offsets;
        }
        else {
            return value.center_pos;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2193::SubChunkRequestPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2193::SubChunkRequestPacket>{"SubChunkRequestPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v2193::SubChunkRequestPacket>{{
    "dimension_type",
    "sub_chunk_pos_offsets",
    "center_pos",
}};

template <>
struct field_accessor<v2193::SubChunkRequestPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.dimension_type;
        }
        else if constexpr (I == 1) {
            return value.sub_chunk_pos_offsets;
        }
        else {
            return value.center_pos;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<RequestChunkRadiusPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<RequestChunkRadiusPacket>{"RequestChunkRadiusPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<RequestChunkRadiusPacket>{{
    "chunk_radius",
    "max_chunk_radius",
}};

template <>
struct field_accessor<RequestChunkRadiusPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.chunk_radius;
        }
        else {
            return value.max_chunk_radius;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<ChunkRadiusUpdatedPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<ChunkRadiusUpdatedPacket>{"ChunkRadiusUpdatedPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<ChunkRadiusUpdatedPacket>{{
    "chunk_radius",
}};

template <>
struct field_accessor<ChunkRadiusUpdatedPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.chunk_radius;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<NetworkChunkPublisherUpdatePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<NetworkChunkPublisherUpdatePacket>{"NetworkChunkPublisherUpdatePacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<NetworkChunkPublisherUpdatePacket>{{
    "position",
    "radius",
    "server_built_chunks",
}};

template <>
struct field_accessor<NetworkChunkPublisherUpdatePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.position;
        }
        else if constexpr (I == 1) {
            return value.radius;
        }
        else {
            return value.server_built_chunks;
        }
    }
};

}  // namespace detail


template <>
struct Serializer<ChunkPos> {
    static void serialize(BinaryWriter &stream, const ChunkPos &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<ChunkPos, std::error_code>;
};

template <>
struct Serializer<base::LevelChunkPacket::SubChunkMetadata> {
    static void serialize(BinaryWriter &stream, const base::LevelChunkPacket::SubChunkMetadata &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::LevelChunkPacket::SubChunkMetadata, std::error_code>;
};

template <>
struct Serializer<base::LevelChunkPacket> {
    static void serialize(BinaryWriter &stream, const base::LevelChunkPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::LevelChunkPacket, std::error_code>;
};

template <>
struct Serializer<v2168::LevelChunkPacket> {
    static void serialize(BinaryWriter &stream, const v2168::LevelChunkPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::LevelChunkPacket, std::error_code>;
};

template <>
struct Serializer<v2225::LevelChunkPacket> {
    static void serialize(BinaryWriter &stream, const v2225::LevelChunkPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::LevelChunkPacket, std::error_code>;
};

template <>
struct Serializer<base::SubChunkPos> {
    static void serialize(BinaryWriter &stream, const base::SubChunkPos &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::SubChunkPos, std::error_code>;
};

template <>
struct Serializer<v1001::SubChunkPos> {
    static void serialize(BinaryWriter &stream, const v1001::SubChunkPos &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::SubChunkPos, std::error_code>;
};

template <>
struct Serializer<legacy::base::SubChunkPos> {
    static void serialize(BinaryWriter &stream, const legacy::base::SubChunkPos &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<legacy::base::SubChunkPos, std::error_code>;
};

template <>
struct Serializer<base::SubChunkPacket::HeightmapData> {
    static void serialize(BinaryWriter &stream, const base::SubChunkPacket::HeightmapData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::SubChunkPacket::HeightmapData, std::error_code>;
};

template <>
struct Serializer<base::SubChunkPacket::SubChunkPosOffset> {
    static void serialize(BinaryWriter &stream, const base::SubChunkPacket::SubChunkPosOffset &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::SubChunkPacket::SubChunkPosOffset, std::error_code>;
};

template <>
struct Serializer<base::SubChunkPacket::SubChunkPacketData> {
    static void serialize(BinaryWriter &stream, const base::SubChunkPacket::SubChunkPacketData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::SubChunkPacket::SubChunkPacketData, std::error_code>;
};

template <>
struct Serializer<base::SubChunkPacket::UncachedSubChunkPacketData> {
    static void serialize(BinaryWriter &stream, const base::SubChunkPacket::UncachedSubChunkPacketData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::SubChunkPacket::UncachedSubChunkPacketData, std::error_code>;
};

template <>
struct Serializer<v818::SubChunkPacket::HeightmapData> {
    static void serialize(BinaryWriter &stream, const v818::SubChunkPacket::HeightmapData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v818::SubChunkPacket::HeightmapData, std::error_code>;
};

template <>
struct Serializer<v818::SubChunkPacket::SubChunkPacketData> {
    static void serialize(BinaryWriter &stream, const v818::SubChunkPacket::SubChunkPacketData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v818::SubChunkPacket::SubChunkPacketData, std::error_code>;
};

template <>
struct Serializer<v818::SubChunkPacket::UncachedSubChunkPacketData> {
    static void serialize(BinaryWriter &stream, const v818::SubChunkPacket::UncachedSubChunkPacketData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v818::SubChunkPacket::UncachedSubChunkPacketData, std::error_code>;
};

template <>
struct Serializer<v1001::SubChunkPacket::HeightmapData> {
    static void serialize(BinaryWriter &stream, const v1001::SubChunkPacket::HeightmapData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::SubChunkPacket::HeightmapData, std::error_code>;
};

template <>
struct Serializer<v1001::SubChunkPacket::SubChunkPacketData> {
    static void serialize(BinaryWriter &stream, const v1001::SubChunkPacket::SubChunkPacketData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::SubChunkPacket::SubChunkPacketData, std::error_code>;
};

template <>
struct Serializer<v1001::SubChunkPacket::UncachedSubChunkPacketData> {
    static void serialize(BinaryWriter &stream, const v1001::SubChunkPacket::UncachedSubChunkPacketData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::SubChunkPacket::UncachedSubChunkPacketData, std::error_code>;
};

template <>
struct Serializer<v2168::SubChunkPacket::HeightmapData> {
    static void serialize(BinaryWriter &stream, const v2168::SubChunkPacket::HeightmapData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::SubChunkPacket::HeightmapData, std::error_code>;
};

template <>
struct Serializer<v2168::SubChunkPacket::SubChunkPacketData> {
    static void serialize(BinaryWriter &stream, const v2168::SubChunkPacket::SubChunkPacketData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::SubChunkPacket::SubChunkPacketData, std::error_code>;
};

template <>
struct Serializer<v2193::SubChunkPacket::HeightmapData> {
    static void serialize(BinaryWriter &stream, const v2193::SubChunkPacket::HeightmapData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::SubChunkPacket::HeightmapData, std::error_code>;
};

template <>
struct Serializer<v2193::SubChunkPacket::SubChunkPacketData> {
    static void serialize(BinaryWriter &stream, const v2193::SubChunkPacket::SubChunkPacketData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::SubChunkPacket::SubChunkPacketData, std::error_code>;
};

template <>
struct Serializer<base::SubChunkPacket> {
    static void serialize(BinaryWriter &stream, const base::SubChunkPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::SubChunkPacket, std::error_code>;
};

template <>
struct Serializer<v818::SubChunkPacket> {
    static void serialize(BinaryWriter &stream, const v818::SubChunkPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v818::SubChunkPacket, std::error_code>;
};

template <>
struct Serializer<v1001::SubChunkPacket> {
    static void serialize(BinaryWriter &stream, const v1001::SubChunkPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::SubChunkPacket, std::error_code>;
};

template <>
struct Serializer<v2168::SubChunkPacket> {
    static void serialize(BinaryWriter &stream, const v2168::SubChunkPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::SubChunkPacket, std::error_code>;
};

template <>
struct Serializer<v2193::SubChunkPacket> {
    static void serialize(BinaryWriter &stream, const v2193::SubChunkPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::SubChunkPacket, std::error_code>;
};

template <>
struct Serializer<base::SubChunkRequestPacket> {
    static void serialize(BinaryWriter &stream, const base::SubChunkRequestPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::SubChunkRequestPacket, std::error_code>;
};

template <>
struct Serializer<v818::SubChunkRequestPacket> {
    static void serialize(BinaryWriter &stream, const v818::SubChunkRequestPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v818::SubChunkRequestPacket, std::error_code>;
};

template <>
struct Serializer<v1001::SubChunkRequestPacket> {
    static void serialize(BinaryWriter &stream, const v1001::SubChunkRequestPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::SubChunkRequestPacket, std::error_code>;
};

template <>
struct Serializer<v2168::SubChunkRequestPacket> {
    static void serialize(BinaryWriter &stream, const v2168::SubChunkRequestPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::SubChunkRequestPacket, std::error_code>;
};

template <>
struct Serializer<v2193::SubChunkRequestPacket> {
    static void serialize(BinaryWriter &stream, const v2193::SubChunkRequestPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::SubChunkRequestPacket, std::error_code>;
};

template <>
struct Serializer<RequestChunkRadiusPacket> {
    static void serialize(BinaryWriter &stream, const RequestChunkRadiusPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<RequestChunkRadiusPacket, std::error_code>;
};

template <>
struct Serializer<ChunkRadiusUpdatedPacket> {
    static void serialize(BinaryWriter &stream, const ChunkRadiusUpdatedPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<ChunkRadiusUpdatedPacket, std::error_code>;
};

template <>
struct Serializer<NetworkChunkPublisherUpdatePacket> {
    static void serialize(BinaryWriter &stream, const NetworkChunkPublisherUpdatePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<NetworkChunkPublisherUpdatePacket, std::error_code>;
};
using LevelChunkPacket = LevelChunkPacket_<2225>;
using SubChunkPos = SubChunkPos_<2225>;
using SubChunkPacket = SubChunkPacket_<2225>;
using SubChunkRequestPacket = SubChunkRequestPacket_<2225>;

}  // namespace bedrock::protocol
