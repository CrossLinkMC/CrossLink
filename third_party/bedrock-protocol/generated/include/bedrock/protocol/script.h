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
#include <bedrock/protocol/packet.hpp>
#include <bedrock/protocol/serializer.hpp>
#include <bedrock/protocol/stream.hpp>

#include <bedrock/protocol/actor.h>
#include <bedrock/protocol/common.h>

namespace bedrock::protocol {

struct ScriptMessagePacket {
    static constexpr int Id = 177;
    std::string message_id{};
    std::string message_value{};
};

namespace SimpleEventPacket_nested {

enum class Subtype : std::uint16_t {
    UninitializedSubtype = 0,
    EnableCommands = 1,
    DisableCommands = 2,
    UnlockWorldTemplateSettings = 3,
};

}  // namespace SimpleEventPacket_nested

struct SimpleEventPacket {
    using Subtype = SimpleEventPacket_nested::Subtype;

    static constexpr int Id = 64;
    SimpleEventPacket::Subtype subtype{};
};

struct ArrowDataPayload {
    std::optional<Vec3> end_location{};
    std::optional<float> arrow_head_length{};
    std::optional<float> arrow_head_radius{};
    std::optional<std::uint8_t> num_segments{};
};

struct BoxDataPayload {
    Vec3 box_bound{};
};

struct LineDataPayload {
    Vec3 end_location{};
};

struct SphereDataPayload {
    std::uint8_t num_segments{};
};

namespace base {

enum class ScriptPrimitiveShapeType : std::uint8_t {
    Line = 0,
    Box = 1,
    Sphere = 2,
    Circle = 3,
    Text = 4,
    Arrow = 5,
    NumShapeTypes = 6,
};

struct TextDataPayload {
    std::string text{};
};

struct PacketShapeData {
    std::uint64_t network_id{};
    std::optional<base::ScriptPrimitiveShapeType> shape_type{};
    std::optional<Vec3> location{};
    std::optional<float> scale{};
    std::optional<Vec3> rotation{};
    std::optional<float> time_left_total_sec{};
    std::optional<Color> color{};
    std::optional<std::string> text{};
    std::optional<Vec3> box_bound{};
    std::optional<Vec3> end_location{};
    std::optional<float> arrow_head_length{};
    std::optional<float> arrow_head_radius{};
    std::optional<std::uint8_t> num_segments{};
};

}  // namespace base

namespace v766 {

using ScriptPrimitiveShapeType = base::ScriptPrimitiveShapeType;

using TextDataPayload = base::TextDataPayload;

using PacketShapeData = base::PacketShapeData;

}  // namespace v766

namespace v776 {

using ScriptPrimitiveShapeType = base::ScriptPrimitiveShapeType;

using TextDataPayload = base::TextDataPayload;

using PacketShapeData = base::PacketShapeData;

}  // namespace v776

namespace v786 {

using ScriptPrimitiveShapeType = base::ScriptPrimitiveShapeType;

using TextDataPayload = base::TextDataPayload;

using PacketShapeData = base::PacketShapeData;

}  // namespace v786

namespace v800 {

using ScriptPrimitiveShapeType = base::ScriptPrimitiveShapeType;

using TextDataPayload = base::TextDataPayload;

using PacketShapeData = base::PacketShapeData;

}  // namespace v800

namespace v818 {

using ScriptPrimitiveShapeType = base::ScriptPrimitiveShapeType;

using TextDataPayload = base::TextDataPayload;

using PacketShapeData = base::PacketShapeData;

struct ServerScriptDebugDrawerPacket {
    static constexpr int Id = 328;
    std::vector<base::PacketShapeData> shapes{};
};

}  // namespace v818

namespace v827 {

using ScriptPrimitiveShapeType = base::ScriptPrimitiveShapeType;

using TextDataPayload = base::TextDataPayload;

using PacketShapeData = base::PacketShapeData;

using ServerScriptDebugDrawerPacket = v818::ServerScriptDebugDrawerPacket;

}  // namespace v827

namespace v844 {

using ScriptPrimitiveShapeType = base::ScriptPrimitiveShapeType;

using TextDataPayload = base::TextDataPayload;

using PacketShapeData = base::PacketShapeData;

using ServerScriptDebugDrawerPacket = v818::ServerScriptDebugDrawerPacket;

}  // namespace v844

namespace v859 {

using ScriptPrimitiveShapeType = base::ScriptPrimitiveShapeType;

using TextDataPayload = base::TextDataPayload;

struct PrimitiveShapeDataPayload {
    std::uint64_t network_id{};
    std::optional<base::ScriptPrimitiveShapeType> shape_type{};
    std::optional<Vec3> location{};
    std::optional<float> scale{};
    std::optional<Vec3> rotation{};
    std::optional<float> time_left_total_sec{};
    std::optional<Color> color{};
    DimensionType dimension_id{};
    std::variant<std::monostate, ArrowDataPayload, base::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload> extra_data_payload{};
};

struct DebugDrawerPacket {
    static constexpr int Id = 328;
    std::vector<v859::PrimitiveShapeDataPayload> shapes{};
};

}  // namespace v859

namespace v898 {

using ScriptPrimitiveShapeType = base::ScriptPrimitiveShapeType;

using TextDataPayload = base::TextDataPayload;

struct PrimitiveShapeDataPayload {
    std::uint64_t network_id{};
    std::optional<base::ScriptPrimitiveShapeType> shape_type{};
    std::optional<Vec3> location{};
    std::optional<float> scale{};
    std::optional<Vec3> rotation{};
    std::optional<float> time_left_total_sec{};
    std::optional<Color> color{};
    std::optional<DimensionType> dimension_id{};
    std::variant<std::monostate, ArrowDataPayload, base::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload> extra_data_payload{};
};

struct DebugDrawerPacket {
    static constexpr int Id = 328;
    std::vector<v898::PrimitiveShapeDataPayload> shapes{};
};

}  // namespace v898

namespace v924 {

using ScriptPrimitiveShapeType = base::ScriptPrimitiveShapeType;

using TextDataPayload = base::TextDataPayload;

struct PrimitiveShapeDataPayload {
    std::uint64_t network_id{};
    std::optional<base::ScriptPrimitiveShapeType> shape_type{};
    std::optional<Vec3> location{};
    std::optional<float> scale{};
    std::optional<Vec3> rotation{};
    std::optional<float> time_left_total_sec{};
    std::optional<Color> color{};
    std::optional<DimensionType> dimension_id{};
    std::optional<ActorRuntimeID> attached_to_id{};
    std::variant<std::monostate, ArrowDataPayload, base::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload> extra_data_payload{};
};

struct DebugDrawerPacket {
    static constexpr int Id = 328;
    std::vector<v924::PrimitiveShapeDataPayload> shapes{};
};

}  // namespace v924

namespace v975 {

using ScriptPrimitiveShapeType = base::ScriptPrimitiveShapeType;

struct TextDataPayload {
    std::string text{};
    bool use_rotation{};
    std::optional<Color> background_color{};
    bool depth_test{};
    bool show_backface{};
    bool show_text_backface{};
};

struct PrimitiveShapeDataPayload {
    std::uint64_t network_id{};
    std::optional<base::ScriptPrimitiveShapeType> shape_type{};
    std::optional<Vec3> location{};
    std::optional<float> scale{};
    std::optional<Vec3> rotation{};
    std::optional<float> time_left_total_sec{};
    std::optional<float> max_render_distance{};
    std::optional<Color> color{};
    std::optional<DimensionType> dimension_id{};
    std::optional<ActorUniqueID> attached_to_id{};
    std::variant<std::monostate, ArrowDataPayload, v975::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload> extra_data_payload{};
};

struct PrimitiveShapesPacket {
    static constexpr int Id = 328;
    std::vector<v975::PrimitiveShapeDataPayload> shapes{};
};

}  // namespace v975

namespace v1001 {

enum class ScriptPrimitiveShapeType : std::uint8_t {
    Line = 0,
    Box = 1,
    Sphere = 2,
    Circle = 3,
    Text = 4,
    Arrow = 5,
    Cylinder = 6,
    Pyramid = 7,
    Ellipsoid = 8,
    Cone = 9,
    NumShapeTypes = 10,
};

using TextDataPayload = v975::TextDataPayload;

struct CylinderDataPayload {
    Vec2 radius_x{};
    Vec2 radius_z{};
    float height{};
    std::uint8_t num_segments{};
};

struct PyramidDataPayload {
    float width{};
    std::optional<float> depth{};
    float height{};
};

struct EllipsoidDataPayload {
    Vec3 radii{};
    std::uint8_t segments_per_axis{};
};

struct ConeDataPayload {
    Vec2 radii{};
    float height{};
    std::uint8_t num_segments{};
};

struct PrimitiveShapeDataPayload {
    std::uint64_t network_id{};
    std::optional<v1001::ScriptPrimitiveShapeType> shape_type{};
    std::optional<Vec3> location{};
    std::optional<float> scale{};
    std::optional<Vec3> rotation{};
    std::optional<float> time_left_total_sec{};
    std::optional<float> max_render_distance{};
    std::optional<Color> color{};
    std::optional<DimensionType> dimension_id{};
    std::optional<ActorUniqueID> attached_to_id{};
    std::variant<std::monostate, ArrowDataPayload, v975::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload, v1001::CylinderDataPayload, v1001::PyramidDataPayload, v1001::EllipsoidDataPayload, v1001::ConeDataPayload> extra_data_payload{};
};

struct PrimitiveShapesPacket {
    static constexpr int Id = 328;
    std::vector<v1001::PrimitiveShapeDataPayload> shapes{};
};

}  // namespace v1001

namespace v2168 {

using ScriptPrimitiveShapeType = v1001::ScriptPrimitiveShapeType;

using TextDataPayload = v975::TextDataPayload;

using CylinderDataPayload = v1001::CylinderDataPayload;

using PyramidDataPayload = v1001::PyramidDataPayload;

using EllipsoidDataPayload = v1001::EllipsoidDataPayload;

using ConeDataPayload = v1001::ConeDataPayload;

using PrimitiveShapeDataPayload = v1001::PrimitiveShapeDataPayload;

using PrimitiveShapesPacket = v1001::PrimitiveShapesPacket;

}  // namespace v2168

namespace v2193 {

using ScriptPrimitiveShapeType = v1001::ScriptPrimitiveShapeType;

struct TextDataPayload {
    std::string text{};
    bool use_rotation{};
    std::optional<Color> background_color{};
    float line_gap_height{};
    bool depth_test{};
    bool show_backface{};
    bool show_text_backface{};
};

using CylinderDataPayload = v1001::CylinderDataPayload;

using PyramidDataPayload = v1001::PyramidDataPayload;

using EllipsoidDataPayload = v1001::EllipsoidDataPayload;

using ConeDataPayload = v1001::ConeDataPayload;

struct PrimitiveShapeDataPayload {
    std::uint64_t network_id{};
    std::optional<v1001::ScriptPrimitiveShapeType> shape_type{};
    std::optional<Vec3> location{};
    std::optional<float> scale{};
    std::optional<Vec3> rotation{};
    std::optional<float> time_left_total_sec{};
    std::optional<float> max_render_distance{};
    std::optional<Color> color{};
    std::optional<DimensionType> dimension_id{};
    std::optional<ActorUniqueID> attached_to_id{};
    std::variant<std::monostate, ArrowDataPayload, v2193::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload, v1001::CylinderDataPayload, v1001::PyramidDataPayload, v1001::EllipsoidDataPayload, v1001::ConeDataPayload> extra_data_payload{};
};

struct PrimitiveShapesPacket {
    static constexpr int Id = 328;
    std::vector<v2193::PrimitiveShapeDataPayload> shapes{};
};

}  // namespace v2193

namespace v2225 {

using ScriptPrimitiveShapeType = v1001::ScriptPrimitiveShapeType;

using TextDataPayload = v2193::TextDataPayload;

using CylinderDataPayload = v1001::CylinderDataPayload;

using PyramidDataPayload = v1001::PyramidDataPayload;

using EllipsoidDataPayload = v1001::EllipsoidDataPayload;

using ConeDataPayload = v1001::ConeDataPayload;

using PrimitiveShapeDataPayload = v2193::PrimitiveShapeDataPayload;

using PrimitiveShapesPacket = v2193::PrimitiveShapesPacket;

}  // namespace v2225

namespace detail {

template <int V>
struct ScriptPrimitiveShapeType_;

template <int V> requires (V < 1001)
struct ScriptPrimitiveShapeType_<V> { using type = base::ScriptPrimitiveShapeType; };

template <int V> requires (V >= 1001)
struct ScriptPrimitiveShapeType_<V> { using type = v1001::ScriptPrimitiveShapeType; };

template <int V>
struct TextDataPayload_;

template <int V> requires (V < 975)
struct TextDataPayload_<V> { using type = base::TextDataPayload; };

template <int V> requires (V >= 975 && V < 2193)
struct TextDataPayload_<V> { using type = v975::TextDataPayload; };

template <int V> requires (V >= 2193)
struct TextDataPayload_<V> { using type = v2193::TextDataPayload; };

template <int V>
struct CylinderDataPayload_;

template <int V> requires (V >= 1001)
struct CylinderDataPayload_<V> { using type = v1001::CylinderDataPayload; };

template <int V>
struct PyramidDataPayload_;

template <int V> requires (V >= 1001)
struct PyramidDataPayload_<V> { using type = v1001::PyramidDataPayload; };

template <int V>
struct EllipsoidDataPayload_;

template <int V> requires (V >= 1001)
struct EllipsoidDataPayload_<V> { using type = v1001::EllipsoidDataPayload; };

template <int V>
struct ConeDataPayload_;

template <int V> requires (V >= 1001)
struct ConeDataPayload_<V> { using type = v1001::ConeDataPayload; };

template <int V>
struct PrimitiveShapeDataPayload_;

template <int V> requires (V >= 859 && V < 898)
struct PrimitiveShapeDataPayload_<V> { using type = v859::PrimitiveShapeDataPayload; };

template <int V> requires (V >= 898 && V < 924)
struct PrimitiveShapeDataPayload_<V> { using type = v898::PrimitiveShapeDataPayload; };

template <int V> requires (V >= 924 && V < 975)
struct PrimitiveShapeDataPayload_<V> { using type = v924::PrimitiveShapeDataPayload; };

template <int V> requires (V >= 975 && V < 1001)
struct PrimitiveShapeDataPayload_<V> { using type = v975::PrimitiveShapeDataPayload; };

template <int V> requires (V >= 1001 && V < 2193)
struct PrimitiveShapeDataPayload_<V> { using type = v1001::PrimitiveShapeDataPayload; };

template <int V> requires (V >= 2193)
struct PrimitiveShapeDataPayload_<V> { using type = v2193::PrimitiveShapeDataPayload; };

template <int V>
struct PrimitiveShapesPacket_;

template <int V> requires (V >= 975 && V < 1001)
struct PrimitiveShapesPacket_<V> { using type = v975::PrimitiveShapesPacket; };

template <int V> requires (V >= 1001 && V < 2193)
struct PrimitiveShapesPacket_<V> { using type = v1001::PrimitiveShapesPacket; };

template <int V> requires (V >= 2193)
struct PrimitiveShapesPacket_<V> { using type = v2193::PrimitiveShapesPacket; };

template <int V>
struct DebugDrawerPacket_;

template <int V> requires (V >= 859 && V < 898)
struct DebugDrawerPacket_<V> { using type = v859::DebugDrawerPacket; };

template <int V> requires (V >= 898 && V < 924)
struct DebugDrawerPacket_<V> { using type = v898::DebugDrawerPacket; };

template <int V> requires (V >= 924 && V < 975)
struct DebugDrawerPacket_<V> { using type = v924::DebugDrawerPacket; };

template <int V>
struct PacketShapeData_;

template <int V> requires (V < 859)
struct PacketShapeData_<V> { using type = base::PacketShapeData; };

template <int V>
struct ServerScriptDebugDrawerPacket_;

template <int V> requires (V >= 818 && V < 859)
struct ServerScriptDebugDrawerPacket_<V> { using type = v818::ServerScriptDebugDrawerPacket; };

}  // namespace detail

template <int V> using ScriptPrimitiveShapeType_ = typename detail::ScriptPrimitiveShapeType_<V>::type;
template <int V> using TextDataPayload_ = typename detail::TextDataPayload_<V>::type;
template <int V> using CylinderDataPayload_ = typename detail::CylinderDataPayload_<V>::type;
template <int V> using PyramidDataPayload_ = typename detail::PyramidDataPayload_<V>::type;
template <int V> using EllipsoidDataPayload_ = typename detail::EllipsoidDataPayload_<V>::type;
template <int V> using ConeDataPayload_ = typename detail::ConeDataPayload_<V>::type;
template <int V> using PrimitiveShapeDataPayload_ = typename detail::PrimitiveShapeDataPayload_<V>::type;
template <int V> using PrimitiveShapesPacket_ = typename detail::PrimitiveShapesPacket_<V>::type;
template <int V> using DebugDrawerPacket_ = typename detail::DebugDrawerPacket_<V>::type;
template <int V> using PacketShapeData_ = typename detail::PacketShapeData_<V>::type;
template <int V> using ServerScriptDebugDrawerPacket_ = typename detail::ServerScriptDebugDrawerPacket_<V>::type;

template <int V>
struct packet_of<V, 64> { using type = SimpleEventPacket; };

template <int V>
struct packet_of<V, 177> { using type = ScriptMessagePacket; };

template <int V> requires (V >= 859 && V < 975)
struct packet_of<V, 328> { using type = DebugDrawerPacket_<V>; };

template <int V> requires (V >= 975)
struct packet_of<V, 328> { using type = PrimitiveShapesPacket_<V>; };

template <int V> requires (V >= 818 && V < 859)
struct packet_of<V, 328> { using type = ServerScriptDebugDrawerPacket_<V>; };

namespace detail {

template <>
inline constexpr std::array<SimpleEventPacket::Subtype, 4> values_v<SimpleEventPacket::Subtype>{{
    SimpleEventPacket::Subtype::UninitializedSubtype,
    SimpleEventPacket::Subtype::EnableCommands,
    SimpleEventPacket::Subtype::DisableCommands,
    SimpleEventPacket::Subtype::UnlockWorldTemplateSettings,
}};

template <>
inline constexpr std::array<std::string_view, 4> names_v<SimpleEventPacket::Subtype>{{
    "uninitializedsubtype",
    "enablecommands",
    "disablecommands",
    "unlockworldtemplatesettings",
}};

template <>
inline constexpr std::string_view type_name_v<SimpleEventPacket::Subtype>{"SimpleEventPacket::Subtype"};

template <>
inline constexpr std::array<base::ScriptPrimitiveShapeType, 7> values_v<base::ScriptPrimitiveShapeType>{{
    base::ScriptPrimitiveShapeType::Line,
    base::ScriptPrimitiveShapeType::Box,
    base::ScriptPrimitiveShapeType::Sphere,
    base::ScriptPrimitiveShapeType::Circle,
    base::ScriptPrimitiveShapeType::Text,
    base::ScriptPrimitiveShapeType::Arrow,
    base::ScriptPrimitiveShapeType::NumShapeTypes,
}};

template <>
inline constexpr std::array<std::string_view, 7> names_v<base::ScriptPrimitiveShapeType>{{
    "line",
    "box",
    "sphere",
    "circle",
    "text",
    "arrow",
    "numshapetypes",
}};

template <>
inline constexpr std::string_view type_name_v<base::ScriptPrimitiveShapeType>{"ScriptPrimitiveShapeType"};

template <>
inline constexpr std::array<v1001::ScriptPrimitiveShapeType, 11> values_v<v1001::ScriptPrimitiveShapeType>{{
    v1001::ScriptPrimitiveShapeType::Line,
    v1001::ScriptPrimitiveShapeType::Box,
    v1001::ScriptPrimitiveShapeType::Sphere,
    v1001::ScriptPrimitiveShapeType::Circle,
    v1001::ScriptPrimitiveShapeType::Text,
    v1001::ScriptPrimitiveShapeType::Arrow,
    v1001::ScriptPrimitiveShapeType::Cylinder,
    v1001::ScriptPrimitiveShapeType::Pyramid,
    v1001::ScriptPrimitiveShapeType::Ellipsoid,
    v1001::ScriptPrimitiveShapeType::Cone,
    v1001::ScriptPrimitiveShapeType::NumShapeTypes,
}};

template <>
inline constexpr std::array<std::string_view, 11> names_v<v1001::ScriptPrimitiveShapeType>{{
    "line",
    "box",
    "sphere",
    "circle",
    "text",
    "arrow",
    "cylinder",
    "pyramid",
    "ellipsoid",
    "cone",
    "numshapetypes",
}};

template <>
inline constexpr std::string_view type_name_v<v1001::ScriptPrimitiveShapeType>{"ScriptPrimitiveShapeType"};

}  // namespace detail

namespace detail {

template <>
inline constexpr bool is_reflected_struct_v<ScriptMessagePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<ScriptMessagePacket>{"ScriptMessagePacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<ScriptMessagePacket>{{
    "message_id",
    "message_value",
}};

template <>
struct field_accessor<ScriptMessagePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.message_id;
        }
        else {
            return value.message_value;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<SimpleEventPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<SimpleEventPacket>{"SimpleEventPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<SimpleEventPacket>{{
    "subtype",
}};

template <>
struct field_accessor<SimpleEventPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.subtype;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<ArrowDataPayload> = true;

template <>
inline constexpr std::string_view struct_name_v<ArrowDataPayload>{"ArrowDataPayload"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<ArrowDataPayload>{{
    "end_location",
    "arrow_head_length",
    "arrow_head_radius",
    "num_segments",
}};

template <>
struct field_accessor<ArrowDataPayload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.end_location;
        }
        else if constexpr (I == 1) {
            return value.arrow_head_length;
        }
        else if constexpr (I == 2) {
            return value.arrow_head_radius;
        }
        else {
            return value.num_segments;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::TextDataPayload> = true;

template <>
inline constexpr std::string_view struct_name_v<base::TextDataPayload>{"TextDataPayload"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::TextDataPayload>{{
    "text",
}};

template <>
struct field_accessor<base::TextDataPayload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.text;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v975::TextDataPayload> = true;

template <>
inline constexpr std::string_view struct_name_v<v975::TextDataPayload>{"TextDataPayload"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<v975::TextDataPayload>{{
    "text",
    "use_rotation",
    "background_color",
    "depth_test",
    "show_backface",
    "show_text_backface",
}};

template <>
struct field_accessor<v975::TextDataPayload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.text;
        }
        else if constexpr (I == 1) {
            return value.use_rotation;
        }
        else if constexpr (I == 2) {
            return value.background_color;
        }
        else if constexpr (I == 3) {
            return value.depth_test;
        }
        else if constexpr (I == 4) {
            return value.show_backface;
        }
        else {
            return value.show_text_backface;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2193::TextDataPayload> = true;

template <>
inline constexpr std::string_view struct_name_v<v2193::TextDataPayload>{"TextDataPayload"};

template <>
inline constexpr std::array<std::string_view, 7> field_names_v<v2193::TextDataPayload>{{
    "text",
    "use_rotation",
    "background_color",
    "line_gap_height",
    "depth_test",
    "show_backface",
    "show_text_backface",
}};

template <>
struct field_accessor<v2193::TextDataPayload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.text;
        }
        else if constexpr (I == 1) {
            return value.use_rotation;
        }
        else if constexpr (I == 2) {
            return value.background_color;
        }
        else if constexpr (I == 3) {
            return value.line_gap_height;
        }
        else if constexpr (I == 4) {
            return value.depth_test;
        }
        else if constexpr (I == 5) {
            return value.show_backface;
        }
        else {
            return value.show_text_backface;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<BoxDataPayload> = true;

template <>
inline constexpr std::string_view struct_name_v<BoxDataPayload>{"BoxDataPayload"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<BoxDataPayload>{{
    "box_bound",
}};

template <>
struct field_accessor<BoxDataPayload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.box_bound;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<LineDataPayload> = true;

template <>
inline constexpr std::string_view struct_name_v<LineDataPayload>{"LineDataPayload"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<LineDataPayload>{{
    "end_location",
}};

template <>
struct field_accessor<LineDataPayload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.end_location;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<SphereDataPayload> = true;

template <>
inline constexpr std::string_view struct_name_v<SphereDataPayload>{"SphereDataPayload"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<SphereDataPayload>{{
    "num_segments",
}};

template <>
struct field_accessor<SphereDataPayload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.num_segments;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::CylinderDataPayload> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::CylinderDataPayload>{"CylinderDataPayload"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v1001::CylinderDataPayload>{{
    "radius_x",
    "radius_z",
    "height",
    "num_segments",
}};

template <>
struct field_accessor<v1001::CylinderDataPayload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.radius_x;
        }
        else if constexpr (I == 1) {
            return value.radius_z;
        }
        else if constexpr (I == 2) {
            return value.height;
        }
        else {
            return value.num_segments;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::PyramidDataPayload> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::PyramidDataPayload>{"PyramidDataPayload"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v1001::PyramidDataPayload>{{
    "width",
    "depth",
    "height",
}};

template <>
struct field_accessor<v1001::PyramidDataPayload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.width;
        }
        else if constexpr (I == 1) {
            return value.depth;
        }
        else {
            return value.height;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::EllipsoidDataPayload> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::EllipsoidDataPayload>{"EllipsoidDataPayload"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v1001::EllipsoidDataPayload>{{
    "radii",
    "segments_per_axis",
}};

template <>
struct field_accessor<v1001::EllipsoidDataPayload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.radii;
        }
        else {
            return value.segments_per_axis;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::ConeDataPayload> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::ConeDataPayload>{"ConeDataPayload"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v1001::ConeDataPayload>{{
    "radii",
    "height",
    "num_segments",
}};

template <>
struct field_accessor<v1001::ConeDataPayload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.radii;
        }
        else if constexpr (I == 1) {
            return value.height;
        }
        else {
            return value.num_segments;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v859::PrimitiveShapeDataPayload> = true;

template <>
inline constexpr std::string_view struct_name_v<v859::PrimitiveShapeDataPayload>{"PrimitiveShapeDataPayload"};

template <>
inline constexpr std::array<std::string_view, 9> field_names_v<v859::PrimitiveShapeDataPayload>{{
    "network_id",
    "shape_type",
    "location",
    "scale",
    "rotation",
    "time_left_total_sec",
    "color",
    "dimension_id",
    "extra_data_payload",
}};

template <>
struct field_accessor<v859::PrimitiveShapeDataPayload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.network_id;
        }
        else if constexpr (I == 1) {
            return value.shape_type;
        }
        else if constexpr (I == 2) {
            return value.location;
        }
        else if constexpr (I == 3) {
            return value.scale;
        }
        else if constexpr (I == 4) {
            return value.rotation;
        }
        else if constexpr (I == 5) {
            return value.time_left_total_sec;
        }
        else if constexpr (I == 6) {
            return value.color;
        }
        else if constexpr (I == 7) {
            return value.dimension_id;
        }
        else {
            return value.extra_data_payload;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v898::PrimitiveShapeDataPayload> = true;

template <>
inline constexpr std::string_view struct_name_v<v898::PrimitiveShapeDataPayload>{"PrimitiveShapeDataPayload"};

template <>
inline constexpr std::array<std::string_view, 9> field_names_v<v898::PrimitiveShapeDataPayload>{{
    "network_id",
    "shape_type",
    "location",
    "scale",
    "rotation",
    "time_left_total_sec",
    "color",
    "dimension_id",
    "extra_data_payload",
}};

template <>
struct field_accessor<v898::PrimitiveShapeDataPayload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.network_id;
        }
        else if constexpr (I == 1) {
            return value.shape_type;
        }
        else if constexpr (I == 2) {
            return value.location;
        }
        else if constexpr (I == 3) {
            return value.scale;
        }
        else if constexpr (I == 4) {
            return value.rotation;
        }
        else if constexpr (I == 5) {
            return value.time_left_total_sec;
        }
        else if constexpr (I == 6) {
            return value.color;
        }
        else if constexpr (I == 7) {
            return value.dimension_id;
        }
        else {
            return value.extra_data_payload;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::PrimitiveShapeDataPayload> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::PrimitiveShapeDataPayload>{"PrimitiveShapeDataPayload"};

template <>
inline constexpr std::array<std::string_view, 10> field_names_v<v924::PrimitiveShapeDataPayload>{{
    "network_id",
    "shape_type",
    "location",
    "scale",
    "rotation",
    "time_left_total_sec",
    "color",
    "dimension_id",
    "attached_to_id",
    "extra_data_payload",
}};

template <>
struct field_accessor<v924::PrimitiveShapeDataPayload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.network_id;
        }
        else if constexpr (I == 1) {
            return value.shape_type;
        }
        else if constexpr (I == 2) {
            return value.location;
        }
        else if constexpr (I == 3) {
            return value.scale;
        }
        else if constexpr (I == 4) {
            return value.rotation;
        }
        else if constexpr (I == 5) {
            return value.time_left_total_sec;
        }
        else if constexpr (I == 6) {
            return value.color;
        }
        else if constexpr (I == 7) {
            return value.dimension_id;
        }
        else if constexpr (I == 8) {
            return value.attached_to_id;
        }
        else {
            return value.extra_data_payload;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v975::PrimitiveShapeDataPayload> = true;

template <>
inline constexpr std::string_view struct_name_v<v975::PrimitiveShapeDataPayload>{"PrimitiveShapeDataPayload"};

template <>
inline constexpr std::array<std::string_view, 11> field_names_v<v975::PrimitiveShapeDataPayload>{{
    "network_id",
    "shape_type",
    "location",
    "scale",
    "rotation",
    "time_left_total_sec",
    "max_render_distance",
    "color",
    "dimension_id",
    "attached_to_id",
    "extra_data_payload",
}};

template <>
struct field_accessor<v975::PrimitiveShapeDataPayload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.network_id;
        }
        else if constexpr (I == 1) {
            return value.shape_type;
        }
        else if constexpr (I == 2) {
            return value.location;
        }
        else if constexpr (I == 3) {
            return value.scale;
        }
        else if constexpr (I == 4) {
            return value.rotation;
        }
        else if constexpr (I == 5) {
            return value.time_left_total_sec;
        }
        else if constexpr (I == 6) {
            return value.max_render_distance;
        }
        else if constexpr (I == 7) {
            return value.color;
        }
        else if constexpr (I == 8) {
            return value.dimension_id;
        }
        else if constexpr (I == 9) {
            return value.attached_to_id;
        }
        else {
            return value.extra_data_payload;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::PrimitiveShapeDataPayload> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::PrimitiveShapeDataPayload>{"PrimitiveShapeDataPayload"};

template <>
inline constexpr std::array<std::string_view, 11> field_names_v<v1001::PrimitiveShapeDataPayload>{{
    "network_id",
    "shape_type",
    "location",
    "scale",
    "rotation",
    "time_left_total_sec",
    "max_render_distance",
    "color",
    "dimension_id",
    "attached_to_id",
    "extra_data_payload",
}};

template <>
struct field_accessor<v1001::PrimitiveShapeDataPayload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.network_id;
        }
        else if constexpr (I == 1) {
            return value.shape_type;
        }
        else if constexpr (I == 2) {
            return value.location;
        }
        else if constexpr (I == 3) {
            return value.scale;
        }
        else if constexpr (I == 4) {
            return value.rotation;
        }
        else if constexpr (I == 5) {
            return value.time_left_total_sec;
        }
        else if constexpr (I == 6) {
            return value.max_render_distance;
        }
        else if constexpr (I == 7) {
            return value.color;
        }
        else if constexpr (I == 8) {
            return value.dimension_id;
        }
        else if constexpr (I == 9) {
            return value.attached_to_id;
        }
        else {
            return value.extra_data_payload;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2193::PrimitiveShapeDataPayload> = true;

template <>
inline constexpr std::string_view struct_name_v<v2193::PrimitiveShapeDataPayload>{"PrimitiveShapeDataPayload"};

template <>
inline constexpr std::array<std::string_view, 11> field_names_v<v2193::PrimitiveShapeDataPayload>{{
    "network_id",
    "shape_type",
    "location",
    "scale",
    "rotation",
    "time_left_total_sec",
    "max_render_distance",
    "color",
    "dimension_id",
    "attached_to_id",
    "extra_data_payload",
}};

template <>
struct field_accessor<v2193::PrimitiveShapeDataPayload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.network_id;
        }
        else if constexpr (I == 1) {
            return value.shape_type;
        }
        else if constexpr (I == 2) {
            return value.location;
        }
        else if constexpr (I == 3) {
            return value.scale;
        }
        else if constexpr (I == 4) {
            return value.rotation;
        }
        else if constexpr (I == 5) {
            return value.time_left_total_sec;
        }
        else if constexpr (I == 6) {
            return value.max_render_distance;
        }
        else if constexpr (I == 7) {
            return value.color;
        }
        else if constexpr (I == 8) {
            return value.dimension_id;
        }
        else if constexpr (I == 9) {
            return value.attached_to_id;
        }
        else {
            return value.extra_data_payload;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v975::PrimitiveShapesPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v975::PrimitiveShapesPacket>{"PrimitiveShapesPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v975::PrimitiveShapesPacket>{{
    "shapes",
}};

template <>
struct field_accessor<v975::PrimitiveShapesPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.shapes;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::PrimitiveShapesPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::PrimitiveShapesPacket>{"PrimitiveShapesPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v1001::PrimitiveShapesPacket>{{
    "shapes",
}};

template <>
struct field_accessor<v1001::PrimitiveShapesPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.shapes;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2193::PrimitiveShapesPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2193::PrimitiveShapesPacket>{"PrimitiveShapesPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2193::PrimitiveShapesPacket>{{
    "shapes",
}};

template <>
struct field_accessor<v2193::PrimitiveShapesPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.shapes;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v859::DebugDrawerPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v859::DebugDrawerPacket>{"DebugDrawerPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v859::DebugDrawerPacket>{{
    "shapes",
}};

template <>
struct field_accessor<v859::DebugDrawerPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.shapes;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v898::DebugDrawerPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v898::DebugDrawerPacket>{"DebugDrawerPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v898::DebugDrawerPacket>{{
    "shapes",
}};

template <>
struct field_accessor<v898::DebugDrawerPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.shapes;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::DebugDrawerPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::DebugDrawerPacket>{"DebugDrawerPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v924::DebugDrawerPacket>{{
    "shapes",
}};

template <>
struct field_accessor<v924::DebugDrawerPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.shapes;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::PacketShapeData> = true;

template <>
inline constexpr std::string_view struct_name_v<base::PacketShapeData>{"PacketShapeData"};

template <>
inline constexpr std::array<std::string_view, 13> field_names_v<base::PacketShapeData>{{
    "network_id",
    "shape_type",
    "location",
    "scale",
    "rotation",
    "time_left_total_sec",
    "color",
    "text",
    "box_bound",
    "end_location",
    "arrow_head_length",
    "arrow_head_radius",
    "num_segments",
}};

template <>
struct field_accessor<base::PacketShapeData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.network_id;
        }
        else if constexpr (I == 1) {
            return value.shape_type;
        }
        else if constexpr (I == 2) {
            return value.location;
        }
        else if constexpr (I == 3) {
            return value.scale;
        }
        else if constexpr (I == 4) {
            return value.rotation;
        }
        else if constexpr (I == 5) {
            return value.time_left_total_sec;
        }
        else if constexpr (I == 6) {
            return value.color;
        }
        else if constexpr (I == 7) {
            return value.text;
        }
        else if constexpr (I == 8) {
            return value.box_bound;
        }
        else if constexpr (I == 9) {
            return value.end_location;
        }
        else if constexpr (I == 10) {
            return value.arrow_head_length;
        }
        else if constexpr (I == 11) {
            return value.arrow_head_radius;
        }
        else {
            return value.num_segments;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v818::ServerScriptDebugDrawerPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v818::ServerScriptDebugDrawerPacket>{"ServerScriptDebugDrawerPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v818::ServerScriptDebugDrawerPacket>{{
    "shapes",
}};

template <>
struct field_accessor<v818::ServerScriptDebugDrawerPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.shapes;
    }
};

}  // namespace detail


template <>
struct Serializer<ScriptMessagePacket> {
    static void serialize(BinaryWriter &stream, const ScriptMessagePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<ScriptMessagePacket, std::error_code>;
};

template <>
struct Serializer<SimpleEventPacket> {
    static void serialize(BinaryWriter &stream, const SimpleEventPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<SimpleEventPacket, std::error_code>;
};

template <>
struct Serializer<ArrowDataPayload> {
    static void serialize(BinaryWriter &stream, const ArrowDataPayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<ArrowDataPayload, std::error_code>;
};

template <>
struct Serializer<base::TextDataPayload> {
    static void serialize(BinaryWriter &stream, const base::TextDataPayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::TextDataPayload, std::error_code>;
};

template <>
struct Serializer<v975::TextDataPayload> {
    static void serialize(BinaryWriter &stream, const v975::TextDataPayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v975::TextDataPayload, std::error_code>;
};

template <>
struct Serializer<v2193::TextDataPayload> {
    static void serialize(BinaryWriter &stream, const v2193::TextDataPayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::TextDataPayload, std::error_code>;
};

template <>
struct Serializer<BoxDataPayload> {
    static void serialize(BinaryWriter &stream, const BoxDataPayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<BoxDataPayload, std::error_code>;
};

template <>
struct Serializer<LineDataPayload> {
    static void serialize(BinaryWriter &stream, const LineDataPayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<LineDataPayload, std::error_code>;
};

template <>
struct Serializer<SphereDataPayload> {
    static void serialize(BinaryWriter &stream, const SphereDataPayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<SphereDataPayload, std::error_code>;
};

template <>
struct Serializer<v1001::CylinderDataPayload> {
    static void serialize(BinaryWriter &stream, const v1001::CylinderDataPayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::CylinderDataPayload, std::error_code>;
};

template <>
struct Serializer<v1001::PyramidDataPayload> {
    static void serialize(BinaryWriter &stream, const v1001::PyramidDataPayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::PyramidDataPayload, std::error_code>;
};

template <>
struct Serializer<v1001::EllipsoidDataPayload> {
    static void serialize(BinaryWriter &stream, const v1001::EllipsoidDataPayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::EllipsoidDataPayload, std::error_code>;
};

template <>
struct Serializer<v1001::ConeDataPayload> {
    static void serialize(BinaryWriter &stream, const v1001::ConeDataPayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::ConeDataPayload, std::error_code>;
};

template <>
struct Serializer<v859::PrimitiveShapeDataPayload> {
    static void serialize(BinaryWriter &stream, const v859::PrimitiveShapeDataPayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v859::PrimitiveShapeDataPayload, std::error_code>;
};

template <>
struct Serializer<v898::PrimitiveShapeDataPayload> {
    static void serialize(BinaryWriter &stream, const v898::PrimitiveShapeDataPayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v898::PrimitiveShapeDataPayload, std::error_code>;
};

template <>
struct Serializer<v924::PrimitiveShapeDataPayload> {
    static void serialize(BinaryWriter &stream, const v924::PrimitiveShapeDataPayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::PrimitiveShapeDataPayload, std::error_code>;
};

template <>
struct Serializer<v975::PrimitiveShapeDataPayload> {
    static void serialize(BinaryWriter &stream, const v975::PrimitiveShapeDataPayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v975::PrimitiveShapeDataPayload, std::error_code>;
};

template <>
struct Serializer<v1001::PrimitiveShapeDataPayload> {
    static void serialize(BinaryWriter &stream, const v1001::PrimitiveShapeDataPayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::PrimitiveShapeDataPayload, std::error_code>;
};

template <>
struct Serializer<v2193::PrimitiveShapeDataPayload> {
    static void serialize(BinaryWriter &stream, const v2193::PrimitiveShapeDataPayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::PrimitiveShapeDataPayload, std::error_code>;
};

template <>
struct Serializer<v975::PrimitiveShapesPacket> {
    static void serialize(BinaryWriter &stream, const v975::PrimitiveShapesPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v975::PrimitiveShapesPacket, std::error_code>;
};

template <>
struct Serializer<v1001::PrimitiveShapesPacket> {
    static void serialize(BinaryWriter &stream, const v1001::PrimitiveShapesPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::PrimitiveShapesPacket, std::error_code>;
};

template <>
struct Serializer<v2193::PrimitiveShapesPacket> {
    static void serialize(BinaryWriter &stream, const v2193::PrimitiveShapesPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::PrimitiveShapesPacket, std::error_code>;
};

template <>
struct Serializer<v859::DebugDrawerPacket> {
    static void serialize(BinaryWriter &stream, const v859::DebugDrawerPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v859::DebugDrawerPacket, std::error_code>;
};

template <>
struct Serializer<v898::DebugDrawerPacket> {
    static void serialize(BinaryWriter &stream, const v898::DebugDrawerPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v898::DebugDrawerPacket, std::error_code>;
};

template <>
struct Serializer<v924::DebugDrawerPacket> {
    static void serialize(BinaryWriter &stream, const v924::DebugDrawerPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::DebugDrawerPacket, std::error_code>;
};

template <>
struct Serializer<base::PacketShapeData> {
    static void serialize(BinaryWriter &stream, const base::PacketShapeData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::PacketShapeData, std::error_code>;
};

template <>
struct Serializer<v818::ServerScriptDebugDrawerPacket> {
    static void serialize(BinaryWriter &stream, const v818::ServerScriptDebugDrawerPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v818::ServerScriptDebugDrawerPacket, std::error_code>;
};
using ScriptPrimitiveShapeType = ScriptPrimitiveShapeType_<2225>;
using TextDataPayload = TextDataPayload_<2225>;
using CylinderDataPayload = CylinderDataPayload_<2225>;
using PyramidDataPayload = PyramidDataPayload_<2225>;
using EllipsoidDataPayload = EllipsoidDataPayload_<2225>;
using ConeDataPayload = ConeDataPayload_<2225>;
using PrimitiveShapeDataPayload = PrimitiveShapeDataPayload_<2225>;
using PrimitiveShapesPacket = PrimitiveShapesPacket_<2225>;

}  // namespace bedrock::protocol
