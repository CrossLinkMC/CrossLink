#pragma once

#include <array>
#include <compare>
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
#include <bedrock/protocol/nbt.hpp>
#include <bedrock/protocol/packet.hpp>
#include <bedrock/protocol/serializer.hpp>
#include <bedrock/protocol/stream.hpp>

#include <bedrock/protocol/actor.h>
#include <bedrock/protocol/common.h>
#include <bedrock/protocol/item_stack.h>
#include <bedrock/protocol/network.h>

namespace bedrock::protocol {

struct RandomSeed {
    constexpr RandomSeed() = default;
    explicit constexpr RandomSeed(std::uint32_t value) : value_(value) {}
    constexpr operator std::uint32_t() const { return value_; }
    friend constexpr bool operator==(const RandomSeed &, const RandomSeed &) = default;
    friend constexpr auto operator<=>(const RandomSeed &, const RandomSeed &) = default;

  private:
    std::uint32_t value_{};
};

enum class StructureBlockType : int {
    Data = 0,
    Save = 1,
    Load = 2,
    Corner = 3,
    Invalid = 4,
    Export = 5,
    Count = 6,
};

enum class StructureRedstoneSaveMode : std::uint8_t {
    SavesToMemory = 0,
    SavesToDisk = 1,
};

enum class Rotation : std::uint8_t {
    None = 0,
    Rotate90 = 1,
    Rotate180 = 2,
    Rotate270 = 3,
    Clockwise90 = 1,
    Clockwise180 = 2,
    CounterClockwise90 = 3,
    Total = 4,
};

enum class Mirror : std::uint8_t {
    None = 0,
    X = 1,
    Z = 2,
    XZ = 3,
};

enum class AnimationMode : std::uint8_t {
    None = 0,
    Layers = 1,
    Blocks = 2,
};

struct TickingAreasLoadStatusPacket {
    static constexpr int Id = 179;
    bool waiting_for_preload{};
};

struct CurrentStructureFeaturePacket {
    static constexpr int Id = 314;
    std::string current_structure_feature{};
};

enum class StructureTemplateRequestOperation : std::uint8_t {
    None = 0,
    ExportFromSaveMode = 1,
    ExportFromLoadMode = 2,
    QuerySavedStructure = 3,
};

enum class StructureTemplateResponseType : std::uint8_t {
    None = 0,
    Export = 1,
    Query = 2,
};

struct StructureTemplateDataResponsePacket {
    static constexpr int Id = 133;
    std::string structure_name{};
    std::optional<CompoundTag> structure_tag{};
    StructureTemplateResponseType response_type{};
};

struct JigsawStructureDataPacket {
    static constexpr int Id = 313;
    CompoundTag jigsaw_structure_data_tag{};
};

namespace FeatureRegistry_nested {

struct FeatureBinaryJsonFormat {
    std::string feature_name{};
    std::string binary_json_output{};
};

}  // namespace FeatureRegistry_nested

struct FeatureRegistry {
    using FeatureBinaryJsonFormat = FeatureRegistry_nested::FeatureBinaryJsonFormat;
};

struct FeatureRegistryPacket {
    static constexpr int Id = 191;
    std::vector<FeatureRegistry::FeatureBinaryJsonFormat> features_data_list{};
};

struct GameTestResultsPacket {
    static constexpr int Id = 195;
    bool succeeded{};
    std::string error{};
    std::string test_name{};
};

struct GameTestRequestPacket {
    static constexpr int Id = 194;
    std::int32_t max_tests_per_batch{};
    std::int32_t repeat_count{};
    Rotation rotation{};
    bool stop_on_failure{};
    BlockPos test_pos{};
    std::int32_t tests_per_row{};
    std::string test_name{};
};

namespace base {

struct StructureSettings {
    std::string palette_name{};
    bool ignore_entities{};
    bool ignore_blocks{};
    bool allow_non_ticking_player_and_ticking_area_chunks{};
    base::NetworkBlockPosition structure_size{};
    base::NetworkBlockPosition structure_offset{};
    ActorUniqueID last_touched_by_player{};
    Rotation rotation{};
    Mirror mirror{};
    AnimationMode animation_mode{};
    float animation_seconds{};
    float integrity_value{};
    RandomSeed integrity_seed{};
    Vec3 pivot{};
};

struct StructureEditorData {
    std::string structure_name{};
    std::string data_field{};
    bool include_players{};
    bool show_bounding_box{};
    StructureBlockType type{};
    base::StructureSettings settings{};
    StructureRedstoneSaveMode redstone_save_mode{};
};

struct StructureBlockUpdatePacket {
    static constexpr int Id = 90;
    base::NetworkBlockPosition block_pos{};
    base::StructureEditorData data{};
    bool trigger{};
    bool is_waterlogged{};
};

struct StructureTemplateDataRequestPacket {
    static constexpr int Id = 132;
    std::string structure_name{};
    base::NetworkBlockPosition structure_block_pos{};
    base::StructureSettings structure_settings{};
    StructureTemplateRequestOperation request_operation{};
};

}  // namespace base

namespace v748 {

using StructureSettings = base::StructureSettings;

using StructureEditorData = base::StructureEditorData;

using StructureBlockUpdatePacket = base::StructureBlockUpdatePacket;

using StructureTemplateDataRequestPacket = base::StructureTemplateDataRequestPacket;

}  // namespace v748

namespace v766 {

using StructureSettings = base::StructureSettings;

struct StructureEditorData {
    std::string structure_name{};
    std::string data_field{};
    bool include_players{};
    bool show_bounding_box{};
    StructureBlockType type{};
    base::StructureSettings settings{};
    StructureRedstoneSaveMode redstone_save_mode{};
};

struct StructureBlockUpdatePacket {
    static constexpr int Id = 90;
    base::NetworkBlockPosition block_pos{};
    v766::StructureEditorData data{};
    bool trigger{};
    bool is_waterlogged{};
};

using StructureTemplateDataRequestPacket = base::StructureTemplateDataRequestPacket;

}  // namespace v766

namespace v776 {

using StructureSettings = base::StructureSettings;

struct StructureEditorData {
    v766::RedactableString structure_name{};
    std::string data_field{};
    bool include_players{};
    bool show_bounding_box{};
    StructureBlockType type{};
    base::StructureSettings settings{};
    StructureRedstoneSaveMode redstone_save_mode{};
};

struct StructureBlockUpdatePacket {
    static constexpr int Id = 90;
    base::NetworkBlockPosition block_pos{};
    v776::StructureEditorData data{};
    bool trigger{};
    bool is_waterlogged{};
};

using StructureTemplateDataRequestPacket = base::StructureTemplateDataRequestPacket;

}  // namespace v776

namespace v786 {

using StructureSettings = base::StructureSettings;

using StructureEditorData = v776::StructureEditorData;

using StructureBlockUpdatePacket = v776::StructureBlockUpdatePacket;

using StructureTemplateDataRequestPacket = base::StructureTemplateDataRequestPacket;

}  // namespace v786

namespace v800 {

using StructureSettings = base::StructureSettings;

using StructureEditorData = v776::StructureEditorData;

using StructureBlockUpdatePacket = v776::StructureBlockUpdatePacket;

using StructureTemplateDataRequestPacket = base::StructureTemplateDataRequestPacket;

}  // namespace v800

namespace v818 {

using StructureSettings = base::StructureSettings;

using StructureEditorData = v776::StructureEditorData;

using StructureBlockUpdatePacket = v776::StructureBlockUpdatePacket;

using StructureTemplateDataRequestPacket = base::StructureTemplateDataRequestPacket;

}  // namespace v818

namespace v827 {

using StructureSettings = base::StructureSettings;

using StructureEditorData = v776::StructureEditorData;

using StructureBlockUpdatePacket = v776::StructureBlockUpdatePacket;

using StructureTemplateDataRequestPacket = base::StructureTemplateDataRequestPacket;

}  // namespace v827

namespace v844 {

using StructureSettings = base::StructureSettings;

using StructureEditorData = v776::StructureEditorData;

using StructureBlockUpdatePacket = v776::StructureBlockUpdatePacket;

using StructureTemplateDataRequestPacket = base::StructureTemplateDataRequestPacket;

}  // namespace v844

namespace v859 {

using StructureSettings = base::StructureSettings;

using StructureEditorData = v776::StructureEditorData;

using StructureBlockUpdatePacket = v776::StructureBlockUpdatePacket;

using StructureTemplateDataRequestPacket = base::StructureTemplateDataRequestPacket;

}  // namespace v859

namespace v898 {

using StructureSettings = base::StructureSettings;

using StructureEditorData = v776::StructureEditorData;

using StructureBlockUpdatePacket = v776::StructureBlockUpdatePacket;

using StructureTemplateDataRequestPacket = base::StructureTemplateDataRequestPacket;

}  // namespace v898

namespace v924 {

using StructureSettings = base::StructureSettings;

using StructureEditorData = v776::StructureEditorData;

using StructureBlockUpdatePacket = v776::StructureBlockUpdatePacket;

using StructureTemplateDataRequestPacket = base::StructureTemplateDataRequestPacket;

}  // namespace v924

namespace v944 {

struct StructureSettings {
    std::string palette_name{};
    bool ignore_entities{};
    bool ignore_blocks{};
    bool allow_non_ticking_player_and_ticking_area_chunks{};
    BlockPos structure_size{};
    BlockPos structure_offset{};
    ActorUniqueID last_touched_by_player{};
    Rotation rotation{};
    Mirror mirror{};
    AnimationMode animation_mode{};
    float animation_seconds{};
    float integrity_value{};
    RandomSeed integrity_seed{};
    Vec3 pivot{};
};

struct StructureEditorData {
    v766::RedactableString structure_name{};
    std::string data_field{};
    bool include_players{};
    bool show_bounding_box{};
    StructureBlockType type{};
    v944::StructureSettings settings{};
    StructureRedstoneSaveMode redstone_save_mode{};
};

struct StructureBlockUpdatePacket {
    static constexpr int Id = 90;
    BlockPos block_pos{};
    v944::StructureEditorData data{};
    bool trigger{};
    bool is_waterlogged{};
};

struct StructureTemplateDataRequestPacket {
    static constexpr int Id = 132;
    std::string structure_name{};
    BlockPos structure_block_pos{};
    v944::StructureSettings structure_settings{};
    StructureTemplateRequestOperation request_operation{};
};

}  // namespace v944

namespace v975 {

using StructureSettings = v944::StructureSettings;

using StructureEditorData = v944::StructureEditorData;

using StructureBlockUpdatePacket = v944::StructureBlockUpdatePacket;

using StructureTemplateDataRequestPacket = v944::StructureTemplateDataRequestPacket;

}  // namespace v975

namespace v1001 {

using StructureSettings = v944::StructureSettings;

using StructureEditorData = v944::StructureEditorData;

using StructureBlockUpdatePacket = v944::StructureBlockUpdatePacket;

using StructureTemplateDataRequestPacket = v944::StructureTemplateDataRequestPacket;

}  // namespace v1001

namespace v2168 {

using StructureSettings = v944::StructureSettings;

struct StructureEditorData {
    v2168::RedactableString structure_name{};
    std::string data_field{};
    bool include_players{};
    bool show_bounding_box{};
    StructureBlockType type{};
    v944::StructureSettings settings{};
    StructureRedstoneSaveMode redstone_save_mode{};
};

struct StructureBlockUpdatePacket {
    static constexpr int Id = 90;
    BlockPos block_pos{};
    v2168::StructureEditorData data{};
    bool trigger{};
    bool is_waterlogged{};
};

using StructureTemplateDataRequestPacket = v944::StructureTemplateDataRequestPacket;

}  // namespace v2168

namespace v2193 {

using StructureSettings = v944::StructureSettings;

using StructureEditorData = v2168::StructureEditorData;

using StructureBlockUpdatePacket = v2168::StructureBlockUpdatePacket;

using StructureTemplateDataRequestPacket = v944::StructureTemplateDataRequestPacket;

}  // namespace v2193

namespace v2225 {

using StructureSettings = v944::StructureSettings;

using StructureEditorData = v2168::StructureEditorData;

using StructureBlockUpdatePacket = v2168::StructureBlockUpdatePacket;

using StructureTemplateDataRequestPacket = v944::StructureTemplateDataRequestPacket;

}  // namespace v2225

namespace detail {

template <int V>
struct StructureSettings_;

template <int V> requires (V < 944)
struct StructureSettings_<V> { using type = base::StructureSettings; };

template <int V> requires (V >= 944)
struct StructureSettings_<V> { using type = v944::StructureSettings; };

template <int V>
struct StructureEditorData_;

template <int V> requires (V < 766)
struct StructureEditorData_<V> { using type = base::StructureEditorData; };

template <int V> requires (V >= 766 && V < 776)
struct StructureEditorData_<V> { using type = v766::StructureEditorData; };

template <int V> requires (V >= 776 && V < 944)
struct StructureEditorData_<V> { using type = v776::StructureEditorData; };

template <int V> requires (V >= 944 && V < 2168)
struct StructureEditorData_<V> { using type = v944::StructureEditorData; };

template <int V> requires (V >= 2168)
struct StructureEditorData_<V> { using type = v2168::StructureEditorData; };

template <int V>
struct StructureBlockUpdatePacket_;

template <int V> requires (V < 766)
struct StructureBlockUpdatePacket_<V> { using type = base::StructureBlockUpdatePacket; };

template <int V> requires (V >= 766 && V < 776)
struct StructureBlockUpdatePacket_<V> { using type = v766::StructureBlockUpdatePacket; };

template <int V> requires (V >= 776 && V < 944)
struct StructureBlockUpdatePacket_<V> { using type = v776::StructureBlockUpdatePacket; };

template <int V> requires (V >= 944 && V < 2168)
struct StructureBlockUpdatePacket_<V> { using type = v944::StructureBlockUpdatePacket; };

template <int V> requires (V >= 2168)
struct StructureBlockUpdatePacket_<V> { using type = v2168::StructureBlockUpdatePacket; };

template <int V>
struct StructureTemplateDataRequestPacket_;

template <int V> requires (V < 944)
struct StructureTemplateDataRequestPacket_<V> { using type = base::StructureTemplateDataRequestPacket; };

template <int V> requires (V >= 944)
struct StructureTemplateDataRequestPacket_<V> { using type = v944::StructureTemplateDataRequestPacket; };

}  // namespace detail

template <int V> using StructureSettings_ = typename detail::StructureSettings_<V>::type;
template <int V> using StructureEditorData_ = typename detail::StructureEditorData_<V>::type;
template <int V> using StructureBlockUpdatePacket_ = typename detail::StructureBlockUpdatePacket_<V>::type;
template <int V> using StructureTemplateDataRequestPacket_ = typename detail::StructureTemplateDataRequestPacket_<V>::type;

template <int V>
struct packet_of<V, 90> { using type = StructureBlockUpdatePacket_<V>; };

template <int V>
struct packet_of<V, 132> { using type = StructureTemplateDataRequestPacket_<V>; };

template <int V>
struct packet_of<V, 133> { using type = StructureTemplateDataResponsePacket; };

template <int V>
struct packet_of<V, 179> { using type = TickingAreasLoadStatusPacket; };

template <int V>
struct packet_of<V, 191> { using type = FeatureRegistryPacket; };

template <int V>
struct packet_of<V, 194> { using type = GameTestRequestPacket; };

template <int V>
struct packet_of<V, 195> { using type = GameTestResultsPacket; };

template <int V>
struct packet_of<V, 313> { using type = JigsawStructureDataPacket; };

template <int V>
struct packet_of<V, 314> { using type = CurrentStructureFeaturePacket; };

namespace detail {

template <>
inline constexpr std::array<StructureBlockType, 7> values_v<StructureBlockType>{{
    StructureBlockType::Data,
    StructureBlockType::Save,
    StructureBlockType::Load,
    StructureBlockType::Corner,
    StructureBlockType::Invalid,
    StructureBlockType::Export,
    StructureBlockType::Count,
}};

template <>
inline constexpr std::array<std::string_view, 7> names_v<StructureBlockType>{{
    "data",
    "save",
    "load",
    "corner",
    "invalid",
    "export",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<StructureBlockType>{"StructureBlockType"};

template <>
inline constexpr std::array<StructureRedstoneSaveMode, 2> values_v<StructureRedstoneSaveMode>{{
    StructureRedstoneSaveMode::SavesToMemory,
    StructureRedstoneSaveMode::SavesToDisk,
}};

template <>
inline constexpr std::array<std::string_view, 2> names_v<StructureRedstoneSaveMode>{{
    "savestomemory",
    "savestodisk",
}};

template <>
inline constexpr std::string_view type_name_v<StructureRedstoneSaveMode>{"StructureRedstoneSaveMode"};

template <>
inline constexpr std::array<Rotation, 8> values_v<Rotation>{{
    Rotation::None,
    Rotation::Rotate90,
    Rotation::Rotate180,
    Rotation::Rotate270,
    Rotation::Clockwise90,
    Rotation::Clockwise180,
    Rotation::CounterClockwise90,
    Rotation::Total,
}};

template <>
inline constexpr std::array<std::string_view, 8> names_v<Rotation>{{
    "none",
    "rotate90",
    "rotate180",
    "rotate270",
    "clockwise90",
    "clockwise180",
    "counterclockwise90",
    "total",
}};

template <>
inline constexpr std::string_view type_name_v<Rotation>{"Rotation"};

template <>
inline constexpr std::array<Mirror, 4> values_v<Mirror>{{
    Mirror::None,
    Mirror::X,
    Mirror::Z,
    Mirror::XZ,
}};

template <>
inline constexpr std::array<std::string_view, 4> names_v<Mirror>{{
    "none",
    "x",
    "z",
    "xz",
}};

template <>
inline constexpr std::string_view type_name_v<Mirror>{"Mirror"};

template <>
inline constexpr std::array<AnimationMode, 3> values_v<AnimationMode>{{
    AnimationMode::None,
    AnimationMode::Layers,
    AnimationMode::Blocks,
}};

template <>
inline constexpr std::array<std::string_view, 3> names_v<AnimationMode>{{
    "none",
    "layers",
    "blocks",
}};

template <>
inline constexpr std::string_view type_name_v<AnimationMode>{"AnimationMode"};

template <>
inline constexpr std::array<StructureTemplateRequestOperation, 4> values_v<StructureTemplateRequestOperation>{{
    StructureTemplateRequestOperation::None,
    StructureTemplateRequestOperation::ExportFromSaveMode,
    StructureTemplateRequestOperation::ExportFromLoadMode,
    StructureTemplateRequestOperation::QuerySavedStructure,
}};

template <>
inline constexpr std::array<std::string_view, 4> names_v<StructureTemplateRequestOperation>{{
    "none",
    "exportfromsavemode",
    "exportfromloadmode",
    "querysavedstructure",
}};

template <>
inline constexpr std::string_view type_name_v<StructureTemplateRequestOperation>{"StructureTemplateRequestOperation"};

template <>
inline constexpr std::array<StructureTemplateResponseType, 3> values_v<StructureTemplateResponseType>{{
    StructureTemplateResponseType::None,
    StructureTemplateResponseType::Export,
    StructureTemplateResponseType::Query,
}};

template <>
inline constexpr std::array<std::string_view, 3> names_v<StructureTemplateResponseType>{{
    "none",
    "export",
    "query",
}};

template <>
inline constexpr std::string_view type_name_v<StructureTemplateResponseType>{"StructureTemplateResponseType"};

}  // namespace detail

namespace detail {

template <>
inline constexpr bool is_reflected_struct_v<base::StructureSettings> = true;

template <>
inline constexpr std::string_view struct_name_v<base::StructureSettings>{"StructureSettings"};

template <>
inline constexpr std::array<std::string_view, 14> field_names_v<base::StructureSettings>{{
    "palette_name",
    "ignore_entities",
    "ignore_blocks",
    "allow_non_ticking_player_and_ticking_area_chunks",
    "structure_size",
    "structure_offset",
    "last_touched_by_player",
    "rotation",
    "mirror",
    "animation_mode",
    "animation_seconds",
    "integrity_value",
    "integrity_seed",
    "pivot",
}};

template <>
struct field_accessor<base::StructureSettings> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.palette_name;
        }
        else if constexpr (I == 1) {
            return value.ignore_entities;
        }
        else if constexpr (I == 2) {
            return value.ignore_blocks;
        }
        else if constexpr (I == 3) {
            return value.allow_non_ticking_player_and_ticking_area_chunks;
        }
        else if constexpr (I == 4) {
            return value.structure_size;
        }
        else if constexpr (I == 5) {
            return value.structure_offset;
        }
        else if constexpr (I == 6) {
            return value.last_touched_by_player;
        }
        else if constexpr (I == 7) {
            return value.rotation;
        }
        else if constexpr (I == 8) {
            return value.mirror;
        }
        else if constexpr (I == 9) {
            return value.animation_mode;
        }
        else if constexpr (I == 10) {
            return value.animation_seconds;
        }
        else if constexpr (I == 11) {
            return value.integrity_value;
        }
        else if constexpr (I == 12) {
            return value.integrity_seed;
        }
        else {
            return value.pivot;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::StructureSettings> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::StructureSettings>{"StructureSettings"};

template <>
inline constexpr std::array<std::string_view, 14> field_names_v<v944::StructureSettings>{{
    "palette_name",
    "ignore_entities",
    "ignore_blocks",
    "allow_non_ticking_player_and_ticking_area_chunks",
    "structure_size",
    "structure_offset",
    "last_touched_by_player",
    "rotation",
    "mirror",
    "animation_mode",
    "animation_seconds",
    "integrity_value",
    "integrity_seed",
    "pivot",
}};

template <>
struct field_accessor<v944::StructureSettings> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.palette_name;
        }
        else if constexpr (I == 1) {
            return value.ignore_entities;
        }
        else if constexpr (I == 2) {
            return value.ignore_blocks;
        }
        else if constexpr (I == 3) {
            return value.allow_non_ticking_player_and_ticking_area_chunks;
        }
        else if constexpr (I == 4) {
            return value.structure_size;
        }
        else if constexpr (I == 5) {
            return value.structure_offset;
        }
        else if constexpr (I == 6) {
            return value.last_touched_by_player;
        }
        else if constexpr (I == 7) {
            return value.rotation;
        }
        else if constexpr (I == 8) {
            return value.mirror;
        }
        else if constexpr (I == 9) {
            return value.animation_mode;
        }
        else if constexpr (I == 10) {
            return value.animation_seconds;
        }
        else if constexpr (I == 11) {
            return value.integrity_value;
        }
        else if constexpr (I == 12) {
            return value.integrity_seed;
        }
        else {
            return value.pivot;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::StructureEditorData> = true;

template <>
inline constexpr std::string_view struct_name_v<base::StructureEditorData>{"StructureEditorData"};

template <>
inline constexpr std::array<std::string_view, 7> field_names_v<base::StructureEditorData>{{
    "structure_name",
    "data_field",
    "include_players",
    "show_bounding_box",
    "type",
    "settings",
    "redstone_save_mode",
}};

template <>
struct field_accessor<base::StructureEditorData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.structure_name;
        }
        else if constexpr (I == 1) {
            return value.data_field;
        }
        else if constexpr (I == 2) {
            return value.include_players;
        }
        else if constexpr (I == 3) {
            return value.show_bounding_box;
        }
        else if constexpr (I == 4) {
            return value.type;
        }
        else if constexpr (I == 5) {
            return value.settings;
        }
        else {
            return value.redstone_save_mode;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v766::StructureEditorData> = true;

template <>
inline constexpr std::string_view struct_name_v<v766::StructureEditorData>{"StructureEditorData"};

template <>
inline constexpr std::array<std::string_view, 7> field_names_v<v766::StructureEditorData>{{
    "structure_name",
    "data_field",
    "include_players",
    "show_bounding_box",
    "type",
    "settings",
    "redstone_save_mode",
}};

template <>
struct field_accessor<v766::StructureEditorData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.structure_name;
        }
        else if constexpr (I == 1) {
            return value.data_field;
        }
        else if constexpr (I == 2) {
            return value.include_players;
        }
        else if constexpr (I == 3) {
            return value.show_bounding_box;
        }
        else if constexpr (I == 4) {
            return value.type;
        }
        else if constexpr (I == 5) {
            return value.settings;
        }
        else {
            return value.redstone_save_mode;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v776::StructureEditorData> = true;

template <>
inline constexpr std::string_view struct_name_v<v776::StructureEditorData>{"StructureEditorData"};

template <>
inline constexpr std::array<std::string_view, 7> field_names_v<v776::StructureEditorData>{{
    "structure_name",
    "data_field",
    "include_players",
    "show_bounding_box",
    "type",
    "settings",
    "redstone_save_mode",
}};

template <>
struct field_accessor<v776::StructureEditorData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.structure_name;
        }
        else if constexpr (I == 1) {
            return value.data_field;
        }
        else if constexpr (I == 2) {
            return value.include_players;
        }
        else if constexpr (I == 3) {
            return value.show_bounding_box;
        }
        else if constexpr (I == 4) {
            return value.type;
        }
        else if constexpr (I == 5) {
            return value.settings;
        }
        else {
            return value.redstone_save_mode;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::StructureEditorData> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::StructureEditorData>{"StructureEditorData"};

template <>
inline constexpr std::array<std::string_view, 7> field_names_v<v944::StructureEditorData>{{
    "structure_name",
    "data_field",
    "include_players",
    "show_bounding_box",
    "type",
    "settings",
    "redstone_save_mode",
}};

template <>
struct field_accessor<v944::StructureEditorData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.structure_name;
        }
        else if constexpr (I == 1) {
            return value.data_field;
        }
        else if constexpr (I == 2) {
            return value.include_players;
        }
        else if constexpr (I == 3) {
            return value.show_bounding_box;
        }
        else if constexpr (I == 4) {
            return value.type;
        }
        else if constexpr (I == 5) {
            return value.settings;
        }
        else {
            return value.redstone_save_mode;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::StructureEditorData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::StructureEditorData>{"StructureEditorData"};

template <>
inline constexpr std::array<std::string_view, 7> field_names_v<v2168::StructureEditorData>{{
    "structure_name",
    "data_field",
    "include_players",
    "show_bounding_box",
    "type",
    "settings",
    "redstone_save_mode",
}};

template <>
struct field_accessor<v2168::StructureEditorData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.structure_name;
        }
        else if constexpr (I == 1) {
            return value.data_field;
        }
        else if constexpr (I == 2) {
            return value.include_players;
        }
        else if constexpr (I == 3) {
            return value.show_bounding_box;
        }
        else if constexpr (I == 4) {
            return value.type;
        }
        else if constexpr (I == 5) {
            return value.settings;
        }
        else {
            return value.redstone_save_mode;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::StructureBlockUpdatePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::StructureBlockUpdatePacket>{"StructureBlockUpdatePacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<base::StructureBlockUpdatePacket>{{
    "block_pos",
    "data",
    "trigger",
    "is_waterlogged",
}};

template <>
struct field_accessor<base::StructureBlockUpdatePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.block_pos;
        }
        else if constexpr (I == 1) {
            return value.data;
        }
        else if constexpr (I == 2) {
            return value.trigger;
        }
        else {
            return value.is_waterlogged;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v766::StructureBlockUpdatePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v766::StructureBlockUpdatePacket>{"StructureBlockUpdatePacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v766::StructureBlockUpdatePacket>{{
    "block_pos",
    "data",
    "trigger",
    "is_waterlogged",
}};

template <>
struct field_accessor<v766::StructureBlockUpdatePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.block_pos;
        }
        else if constexpr (I == 1) {
            return value.data;
        }
        else if constexpr (I == 2) {
            return value.trigger;
        }
        else {
            return value.is_waterlogged;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v776::StructureBlockUpdatePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v776::StructureBlockUpdatePacket>{"StructureBlockUpdatePacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v776::StructureBlockUpdatePacket>{{
    "block_pos",
    "data",
    "trigger",
    "is_waterlogged",
}};

template <>
struct field_accessor<v776::StructureBlockUpdatePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.block_pos;
        }
        else if constexpr (I == 1) {
            return value.data;
        }
        else if constexpr (I == 2) {
            return value.trigger;
        }
        else {
            return value.is_waterlogged;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::StructureBlockUpdatePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::StructureBlockUpdatePacket>{"StructureBlockUpdatePacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v944::StructureBlockUpdatePacket>{{
    "block_pos",
    "data",
    "trigger",
    "is_waterlogged",
}};

template <>
struct field_accessor<v944::StructureBlockUpdatePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.block_pos;
        }
        else if constexpr (I == 1) {
            return value.data;
        }
        else if constexpr (I == 2) {
            return value.trigger;
        }
        else {
            return value.is_waterlogged;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::StructureBlockUpdatePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::StructureBlockUpdatePacket>{"StructureBlockUpdatePacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v2168::StructureBlockUpdatePacket>{{
    "block_pos",
    "data",
    "trigger",
    "is_waterlogged",
}};

template <>
struct field_accessor<v2168::StructureBlockUpdatePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.block_pos;
        }
        else if constexpr (I == 1) {
            return value.data;
        }
        else if constexpr (I == 2) {
            return value.trigger;
        }
        else {
            return value.is_waterlogged;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<TickingAreasLoadStatusPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<TickingAreasLoadStatusPacket>{"TickingAreasLoadStatusPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<TickingAreasLoadStatusPacket>{{
    "waiting_for_preload",
}};

template <>
struct field_accessor<TickingAreasLoadStatusPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.waiting_for_preload;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<CurrentStructureFeaturePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<CurrentStructureFeaturePacket>{"CurrentStructureFeaturePacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<CurrentStructureFeaturePacket>{{
    "current_structure_feature",
}};

template <>
struct field_accessor<CurrentStructureFeaturePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.current_structure_feature;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::StructureTemplateDataRequestPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::StructureTemplateDataRequestPacket>{"StructureTemplateDataRequestPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<base::StructureTemplateDataRequestPacket>{{
    "structure_name",
    "structure_block_pos",
    "structure_settings",
    "request_operation",
}};

template <>
struct field_accessor<base::StructureTemplateDataRequestPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.structure_name;
        }
        else if constexpr (I == 1) {
            return value.structure_block_pos;
        }
        else if constexpr (I == 2) {
            return value.structure_settings;
        }
        else {
            return value.request_operation;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::StructureTemplateDataRequestPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::StructureTemplateDataRequestPacket>{"StructureTemplateDataRequestPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v944::StructureTemplateDataRequestPacket>{{
    "structure_name",
    "structure_block_pos",
    "structure_settings",
    "request_operation",
}};

template <>
struct field_accessor<v944::StructureTemplateDataRequestPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.structure_name;
        }
        else if constexpr (I == 1) {
            return value.structure_block_pos;
        }
        else if constexpr (I == 2) {
            return value.structure_settings;
        }
        else {
            return value.request_operation;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<StructureTemplateDataResponsePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<StructureTemplateDataResponsePacket>{"StructureTemplateDataResponsePacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<StructureTemplateDataResponsePacket>{{
    "structure_name",
    "structure_tag",
    "response_type",
}};

template <>
struct field_accessor<StructureTemplateDataResponsePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.structure_name;
        }
        else if constexpr (I == 1) {
            return value.structure_tag;
        }
        else {
            return value.response_type;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<JigsawStructureDataPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<JigsawStructureDataPacket>{"JigsawStructureDataPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<JigsawStructureDataPacket>{{
    "jigsaw_structure_data_tag",
}};

template <>
struct field_accessor<JigsawStructureDataPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.jigsaw_structure_data_tag;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<FeatureRegistry::FeatureBinaryJsonFormat> = true;

template <>
inline constexpr std::string_view struct_name_v<FeatureRegistry::FeatureBinaryJsonFormat>{"FeatureRegistry::FeatureBinaryJsonFormat"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<FeatureRegistry::FeatureBinaryJsonFormat>{{
    "feature_name",
    "binary_json_output",
}};

template <>
struct field_accessor<FeatureRegistry::FeatureBinaryJsonFormat> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.feature_name;
        }
        else {
            return value.binary_json_output;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<FeatureRegistry> = true;

template <>
inline constexpr std::string_view struct_name_v<FeatureRegistry>{"FeatureRegistry"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<FeatureRegistry>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<FeatureRegistryPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<FeatureRegistryPacket>{"FeatureRegistryPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<FeatureRegistryPacket>{{
    "features_data_list",
}};

template <>
struct field_accessor<FeatureRegistryPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.features_data_list;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<GameTestResultsPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<GameTestResultsPacket>{"GameTestResultsPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<GameTestResultsPacket>{{
    "succeeded",
    "error",
    "test_name",
}};

template <>
struct field_accessor<GameTestResultsPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.succeeded;
        }
        else if constexpr (I == 1) {
            return value.error;
        }
        else {
            return value.test_name;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<GameTestRequestPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<GameTestRequestPacket>{"GameTestRequestPacket"};

template <>
inline constexpr std::array<std::string_view, 7> field_names_v<GameTestRequestPacket>{{
    "max_tests_per_batch",
    "repeat_count",
    "rotation",
    "stop_on_failure",
    "test_pos",
    "tests_per_row",
    "test_name",
}};

template <>
struct field_accessor<GameTestRequestPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.max_tests_per_batch;
        }
        else if constexpr (I == 1) {
            return value.repeat_count;
        }
        else if constexpr (I == 2) {
            return value.rotation;
        }
        else if constexpr (I == 3) {
            return value.stop_on_failure;
        }
        else if constexpr (I == 4) {
            return value.test_pos;
        }
        else if constexpr (I == 5) {
            return value.tests_per_row;
        }
        else {
            return value.test_name;
        }
    }
};

}  // namespace detail


template <>
struct Serializer<base::StructureSettings> {
    static void serialize(BinaryWriter &stream, const base::StructureSettings &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::StructureSettings, std::error_code>;
};

template <>
struct Serializer<v944::StructureSettings> {
    static void serialize(BinaryWriter &stream, const v944::StructureSettings &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::StructureSettings, std::error_code>;
};

template <>
struct Serializer<base::StructureEditorData> {
    static void serialize(BinaryWriter &stream, const base::StructureEditorData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::StructureEditorData, std::error_code>;
};

template <>
struct Serializer<v766::StructureEditorData> {
    static void serialize(BinaryWriter &stream, const v766::StructureEditorData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v766::StructureEditorData, std::error_code>;
};

template <>
struct Serializer<v776::StructureEditorData> {
    static void serialize(BinaryWriter &stream, const v776::StructureEditorData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v776::StructureEditorData, std::error_code>;
};

template <>
struct Serializer<v944::StructureEditorData> {
    static void serialize(BinaryWriter &stream, const v944::StructureEditorData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::StructureEditorData, std::error_code>;
};

template <>
struct Serializer<v2168::StructureEditorData> {
    static void serialize(BinaryWriter &stream, const v2168::StructureEditorData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::StructureEditorData, std::error_code>;
};

template <>
struct Serializer<base::StructureBlockUpdatePacket> {
    static void serialize(BinaryWriter &stream, const base::StructureBlockUpdatePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::StructureBlockUpdatePacket, std::error_code>;
};

template <>
struct Serializer<v766::StructureBlockUpdatePacket> {
    static void serialize(BinaryWriter &stream, const v766::StructureBlockUpdatePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v766::StructureBlockUpdatePacket, std::error_code>;
};

template <>
struct Serializer<v776::StructureBlockUpdatePacket> {
    static void serialize(BinaryWriter &stream, const v776::StructureBlockUpdatePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v776::StructureBlockUpdatePacket, std::error_code>;
};

template <>
struct Serializer<v944::StructureBlockUpdatePacket> {
    static void serialize(BinaryWriter &stream, const v944::StructureBlockUpdatePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::StructureBlockUpdatePacket, std::error_code>;
};

template <>
struct Serializer<v2168::StructureBlockUpdatePacket> {
    static void serialize(BinaryWriter &stream, const v2168::StructureBlockUpdatePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::StructureBlockUpdatePacket, std::error_code>;
};

template <>
struct Serializer<TickingAreasLoadStatusPacket> {
    static void serialize(BinaryWriter &stream, const TickingAreasLoadStatusPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<TickingAreasLoadStatusPacket, std::error_code>;
};

template <>
struct Serializer<CurrentStructureFeaturePacket> {
    static void serialize(BinaryWriter &stream, const CurrentStructureFeaturePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<CurrentStructureFeaturePacket, std::error_code>;
};

template <>
struct Serializer<base::StructureTemplateDataRequestPacket> {
    static void serialize(BinaryWriter &stream, const base::StructureTemplateDataRequestPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::StructureTemplateDataRequestPacket, std::error_code>;
};

template <>
struct Serializer<v944::StructureTemplateDataRequestPacket> {
    static void serialize(BinaryWriter &stream, const v944::StructureTemplateDataRequestPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::StructureTemplateDataRequestPacket, std::error_code>;
};

template <>
struct Serializer<StructureTemplateDataResponsePacket> {
    static void serialize(BinaryWriter &stream, const StructureTemplateDataResponsePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<StructureTemplateDataResponsePacket, std::error_code>;
};

template <>
struct Serializer<JigsawStructureDataPacket> {
    static void serialize(BinaryWriter &stream, const JigsawStructureDataPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<JigsawStructureDataPacket, std::error_code>;
};

template <>
struct Serializer<FeatureRegistry::FeatureBinaryJsonFormat> {
    static void serialize(BinaryWriter &stream, const FeatureRegistry::FeatureBinaryJsonFormat &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<FeatureRegistry::FeatureBinaryJsonFormat, std::error_code>;
};

template <>
struct Serializer<FeatureRegistryPacket> {
    static void serialize(BinaryWriter &stream, const FeatureRegistryPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<FeatureRegistryPacket, std::error_code>;
};

template <>
struct Serializer<GameTestResultsPacket> {
    static void serialize(BinaryWriter &stream, const GameTestResultsPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<GameTestResultsPacket, std::error_code>;
};

template <>
struct Serializer<GameTestRequestPacket> {
    static void serialize(BinaryWriter &stream, const GameTestRequestPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<GameTestRequestPacket, std::error_code>;
};
using StructureSettings = StructureSettings_<2225>;
using StructureEditorData = StructureEditorData_<2225>;
using StructureBlockUpdatePacket = StructureBlockUpdatePacket_<2225>;
using StructureTemplateDataRequestPacket = StructureTemplateDataRequestPacket_<2225>;

}  // namespace bedrock::protocol
