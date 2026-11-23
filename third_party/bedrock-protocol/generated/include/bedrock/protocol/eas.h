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

#include <bedrock/protocol/common.h>

namespace bedrock::protocol {

struct Color255RGBA {
    std::int32_t r{};
    std::int32_t g{};
    std::int32_t b{};
    std::int32_t a{};
};

enum class BoolAttributeOperation : int {
    Override = 0,
    AlphaBlend = 1,
    And = 2,
    Nand = 3,
    Or = 4,
    Nor = 5,
    Xor = 6,
    Xnor = 7,
};

enum class FloatAttributeOperation : int {
    Override = 0,
    AlphaBlend = 1,
    Add = 2,
    Subtract = 3,
    Multiply = 4,
    Minimum = 5,
    Maximum = 6,
};

enum class ColorAttributeOperation : int {
    Override = 0,
    AlphaBlend = 1,
    Add = 2,
    Subtract = 3,
    Multiply = 4,
};

enum class EasingType : std::uint32_t {
    Linear = 0,
    Spring = 1,
    InQuad = 2,
    OutQuad = 3,
    InOutQuad = 4,
    InCubic = 5,
    OutCubic = 6,
    InOutCubic = 7,
    InQuart = 8,
    OutQuart = 9,
    InOutQuart = 10,
    InQuint = 11,
    OutQuint = 12,
    InOutQuint = 13,
    InSine = 14,
    OutSine = 15,
    InOutSine = 16,
    InExpo = 17,
    OutExpo = 18,
    InOutExpo = 19,
    InCirc = 20,
    OutCirc = 21,
    InOutCirc = 22,
    InBounce = 23,
    OutBounce = 24,
    InOutBounce = 25,
    InBack = 26,
    OutBack = 27,
    InOutBack = 28,
    InElastic = 29,
    OutElastic = 30,
    InOutElastic = 31,
};

struct BoolAttributeData {
    bool value{};
    BoolAttributeOperation operation{};
};

struct FloatAttributeData {
    float value{};
    FloatAttributeOperation operation{};
    std::optional<float> constraint_min_value{};
    std::optional<float> constraint_max_value{};
};

struct ColorAttributeData {
    Color255RGBA value{};
    ColorAttributeOperation operation{};
};

struct RemoveEnvironmentAttributesData {
    std::string layer_name{};
    DimensionType layer_dimension_id{};
    std::vector<std::string> attributes{};
};

using AttributeDataVariant = std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>;

namespace base {

struct EnvironmentAttributeData {
    std::string name{};
    std::optional<std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> from_attribute{};
    std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData> attribute{};
    std::optional<std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> to_attribute{};
    std::uint32_t current_transition_ticks{};
    std::uint32_t total_transition_ticks{};
    EasingType easing{};
};

struct AttributeLayerSettings {
    std::int32_t priority{};
    std::variant<float, std::string> weight{};
    bool enabled{};
    bool transitions_paused{};
};

struct AttributeLayerData {
    std::string name{};
    DimensionType dimension_id{};
    base::AttributeLayerSettings settings{};
    std::vector<base::EnvironmentAttributeData> attributes{};
};

struct UpdateAttributeLayersData {
    std::vector<base::AttributeLayerData> attribute_layers{};
};

struct UpdateAttributeLayerSettingsData {
    std::string layer_name{};
    DimensionType layer_dimension_id{};
    base::AttributeLayerSettings attribute_layer_settings{};
};

struct UpdateEnvironmentAttributesData {
    std::string layer_name{};
    DimensionType layer_dimension_id{};
    std::vector<base::EnvironmentAttributeData> attributes{};
};

}  // namespace base

namespace v944 {

using EnvironmentAttributeData = base::EnvironmentAttributeData;

using AttributeLayerSettings = base::AttributeLayerSettings;

using AttributeLayerData = base::AttributeLayerData;

using UpdateAttributeLayersData = base::UpdateAttributeLayersData;

using UpdateAttributeLayerSettingsData = base::UpdateAttributeLayerSettingsData;

using UpdateEnvironmentAttributesData = base::UpdateEnvironmentAttributesData;

struct ClientboundAttributeLayerSyncPacket {
    static constexpr int Id = 345;
    std::variant<base::UpdateAttributeLayersData, base::UpdateAttributeLayerSettingsData, base::UpdateEnvironmentAttributesData, RemoveEnvironmentAttributesData> data{};
};

}  // namespace v944

namespace v975 {

using EnvironmentAttributeData = base::EnvironmentAttributeData;

struct AttributeLayerSettings {
    std::int32_t priority{};
    float weight{};
    bool enabled{};
    bool transitions_paused{};
};

struct AttributeLayerData {
    std::string name{};
    DimensionType dimension_id{};
    v975::AttributeLayerSettings settings{};
    std::vector<base::EnvironmentAttributeData> attributes{};
};

struct UpdateAttributeLayersData {
    std::vector<v975::AttributeLayerData> attribute_layers{};
};

struct UpdateAttributeLayerSettingsData {
    std::string layer_name{};
    DimensionType layer_dimension_id{};
    v975::AttributeLayerSettings attribute_layer_settings{};
};

using UpdateEnvironmentAttributesData = base::UpdateEnvironmentAttributesData;

struct ClientboundAttributeLayerSyncPacket {
    static constexpr int Id = 345;
    std::variant<v975::UpdateAttributeLayersData, v975::UpdateAttributeLayerSettingsData, base::UpdateEnvironmentAttributesData, RemoveEnvironmentAttributesData> data{};
};

}  // namespace v975

namespace v1001 {

struct EnvironmentAttributeData {
    std::string name{};
    std::optional<std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> from_attribute{};
    std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData> attribute{};
    std::optional<std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> to_attribute{};
    std::uint32_t current_transition_ticks{};
    std::uint32_t total_transition_ticks{};
    EasingType easing{};
    std::uint32_t local_transition_ticks{};
    bool noise_transition{};
};

using AttributeLayerSettings = v975::AttributeLayerSettings;

struct AttributeLayerData {
    std::string name{};
    std::optional<std::string> noise_name{};
    DimensionType dimension_id{};
    v975::AttributeLayerSettings settings{};
    std::vector<v1001::EnvironmentAttributeData> attributes{};
};

struct UpdateAttributeLayersData {
    std::vector<v1001::AttributeLayerData> attribute_layers{};
};

using UpdateAttributeLayerSettingsData = v975::UpdateAttributeLayerSettingsData;

struct UpdateEnvironmentAttributesData {
    std::string layer_name{};
    DimensionType layer_dimension_id{};
    std::vector<v1001::EnvironmentAttributeData> attributes{};
};

struct ClientboundAttributeLayerSyncPacket {
    static constexpr int Id = 345;
    std::variant<v1001::UpdateAttributeLayersData, v975::UpdateAttributeLayerSettingsData, v1001::UpdateEnvironmentAttributesData, RemoveEnvironmentAttributesData> data{};
};

}  // namespace v1001

namespace v2193 {

enum class NoiseAlignmentType : std::uint8_t {
    MinLocalTransitionEnd = 0,
};

struct NoiseAlignment {
    v2193::NoiseAlignmentType type{};
    std::uint32_t value{};
};

struct EnvironmentAttributeData {
    std::string name{};
    std::optional<std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> from_attribute{};
    std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData> attribute{};
    std::optional<std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> to_attribute{};
    std::uint32_t current_transition_ticks{};
    std::uint32_t total_transition_ticks{};
    EasingType easing{};
    std::uint32_t local_transition_ticks{};
    bool noise_transition{};
    v2193::NoiseAlignment noise_alignment{};
};

using AttributeLayerSettings = v975::AttributeLayerSettings;

struct AttributeLayerData {
    std::string name{};
    std::optional<std::string> noise_name{};
    DimensionType dimension_id{};
    v975::AttributeLayerSettings settings{};
    std::vector<v2193::EnvironmentAttributeData> attributes{};
};

struct UpdateAttributeLayersData {
    std::vector<v2193::AttributeLayerData> attribute_layers{};
};

using UpdateAttributeLayerSettingsData = v975::UpdateAttributeLayerSettingsData;

struct UpdateEnvironmentAttributesData {
    std::string layer_name{};
    DimensionType layer_dimension_id{};
    std::vector<v2193::EnvironmentAttributeData> attributes{};
};

struct ClientboundAttributeLayerSyncPacket {
    static constexpr int Id = 345;
    std::variant<v2193::UpdateAttributeLayersData, v975::UpdateAttributeLayerSettingsData, v2193::UpdateEnvironmentAttributesData, RemoveEnvironmentAttributesData> data{};
};

}  // namespace v2193

namespace v2225 {

using NoiseAlignmentType = v2193::NoiseAlignmentType;

using NoiseAlignment = v2193::NoiseAlignment;

struct ConstantAttributeData {
    std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData> attribute{};
};

struct TransitionSettingsData {
    std::uint32_t total_transition_ticks{};
    std::uint32_t current_transition_ticks{};
    EasingType easing{};
    std::string clock_name{};
};

struct TransitionAttributeData {
    std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData> from_attribute{};
    std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData> to_attribute{};
    v2225::TransitionSettingsData settings{};
};

struct NoiseTransitionSettingsData {
    std::uint32_t total_transition_ticks{};
    std::uint32_t current_transition_ticks{};
    EasingType easing{};
    std::string clock_name{};
    std::uint32_t local_transition_ticks{};
    std::string noise_name{};
    v2193::NoiseAlignment noise_alignment{};
};

struct NoiseTransitionAttributeData {
    std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData> from_attribute{};
    std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData> to_attribute{};
    v2225::NoiseTransitionSettingsData settings{};
};

struct EnvironmentAttributeData {
    std::string name{};
    std::variant<v2225::ConstantAttributeData, v2225::TransitionAttributeData, v2225::NoiseTransitionAttributeData> payload{};
};

using AttributeLayerSettings = v975::AttributeLayerSettings;

struct AttributeLayerData {
    std::string name{};
    DimensionType dimension_id{};
    v975::AttributeLayerSettings settings{};
    std::vector<v2225::EnvironmentAttributeData> attributes{};
};

struct UpdateAttributeLayersData {
    std::vector<v2225::AttributeLayerData> attribute_layers{};
};

using UpdateAttributeLayerSettingsData = v975::UpdateAttributeLayerSettingsData;

struct UpdateEnvironmentAttributesData {
    std::string layer_name{};
    DimensionType layer_dimension_id{};
    std::vector<v2225::EnvironmentAttributeData> attributes{};
};

struct ClientboundAttributeLayerSyncPacket {
    static constexpr int Id = 345;
    std::variant<v2225::UpdateAttributeLayersData, v975::UpdateAttributeLayerSettingsData, v2225::UpdateEnvironmentAttributesData, RemoveEnvironmentAttributesData> data{};
};

using AttributeDataPayload = std::variant<v2225::ConstantAttributeData, v2225::TransitionAttributeData, v2225::NoiseTransitionAttributeData>;

}  // namespace v2225

namespace detail {

template <int V>
struct NoiseAlignmentType_;

template <int V> requires (V >= 2193)
struct NoiseAlignmentType_<V> { using type = v2193::NoiseAlignmentType; };

template <int V>
struct NoiseAlignment_;

template <int V> requires (V >= 2193)
struct NoiseAlignment_<V> { using type = v2193::NoiseAlignment; };

template <int V>
struct ConstantAttributeData_;

template <int V> requires (V >= 2225)
struct ConstantAttributeData_<V> { using type = v2225::ConstantAttributeData; };

template <int V>
struct TransitionSettingsData_;

template <int V> requires (V >= 2225)
struct TransitionSettingsData_<V> { using type = v2225::TransitionSettingsData; };

template <int V>
struct TransitionAttributeData_;

template <int V> requires (V >= 2225)
struct TransitionAttributeData_<V> { using type = v2225::TransitionAttributeData; };

template <int V>
struct NoiseTransitionSettingsData_;

template <int V> requires (V >= 2225)
struct NoiseTransitionSettingsData_<V> { using type = v2225::NoiseTransitionSettingsData; };

template <int V>
struct NoiseTransitionAttributeData_;

template <int V> requires (V >= 2225)
struct NoiseTransitionAttributeData_<V> { using type = v2225::NoiseTransitionAttributeData; };

template <int V>
struct EnvironmentAttributeData_;

template <int V> requires (V < 1001)
struct EnvironmentAttributeData_<V> { using type = base::EnvironmentAttributeData; };

template <int V> requires (V >= 1001 && V < 2193)
struct EnvironmentAttributeData_<V> { using type = v1001::EnvironmentAttributeData; };

template <int V> requires (V >= 2193 && V < 2225)
struct EnvironmentAttributeData_<V> { using type = v2193::EnvironmentAttributeData; };

template <int V> requires (V >= 2225)
struct EnvironmentAttributeData_<V> { using type = v2225::EnvironmentAttributeData; };

template <int V>
struct AttributeLayerSettings_;

template <int V> requires (V < 975)
struct AttributeLayerSettings_<V> { using type = base::AttributeLayerSettings; };

template <int V> requires (V >= 975)
struct AttributeLayerSettings_<V> { using type = v975::AttributeLayerSettings; };

template <int V>
struct AttributeLayerData_;

template <int V> requires (V < 975)
struct AttributeLayerData_<V> { using type = base::AttributeLayerData; };

template <int V> requires (V >= 975 && V < 1001)
struct AttributeLayerData_<V> { using type = v975::AttributeLayerData; };

template <int V> requires (V >= 1001 && V < 2193)
struct AttributeLayerData_<V> { using type = v1001::AttributeLayerData; };

template <int V> requires (V >= 2193 && V < 2225)
struct AttributeLayerData_<V> { using type = v2193::AttributeLayerData; };

template <int V> requires (V >= 2225)
struct AttributeLayerData_<V> { using type = v2225::AttributeLayerData; };

template <int V>
struct UpdateAttributeLayersData_;

template <int V> requires (V < 975)
struct UpdateAttributeLayersData_<V> { using type = base::UpdateAttributeLayersData; };

template <int V> requires (V >= 975 && V < 1001)
struct UpdateAttributeLayersData_<V> { using type = v975::UpdateAttributeLayersData; };

template <int V> requires (V >= 1001 && V < 2193)
struct UpdateAttributeLayersData_<V> { using type = v1001::UpdateAttributeLayersData; };

template <int V> requires (V >= 2193 && V < 2225)
struct UpdateAttributeLayersData_<V> { using type = v2193::UpdateAttributeLayersData; };

template <int V> requires (V >= 2225)
struct UpdateAttributeLayersData_<V> { using type = v2225::UpdateAttributeLayersData; };

template <int V>
struct UpdateAttributeLayerSettingsData_;

template <int V> requires (V < 975)
struct UpdateAttributeLayerSettingsData_<V> { using type = base::UpdateAttributeLayerSettingsData; };

template <int V> requires (V >= 975)
struct UpdateAttributeLayerSettingsData_<V> { using type = v975::UpdateAttributeLayerSettingsData; };

template <int V>
struct UpdateEnvironmentAttributesData_;

template <int V> requires (V < 1001)
struct UpdateEnvironmentAttributesData_<V> { using type = base::UpdateEnvironmentAttributesData; };

template <int V> requires (V >= 1001 && V < 2193)
struct UpdateEnvironmentAttributesData_<V> { using type = v1001::UpdateEnvironmentAttributesData; };

template <int V> requires (V >= 2193 && V < 2225)
struct UpdateEnvironmentAttributesData_<V> { using type = v2193::UpdateEnvironmentAttributesData; };

template <int V> requires (V >= 2225)
struct UpdateEnvironmentAttributesData_<V> { using type = v2225::UpdateEnvironmentAttributesData; };

template <int V>
struct ClientboundAttributeLayerSyncPacket_;

template <int V> requires (V >= 944 && V < 975)
struct ClientboundAttributeLayerSyncPacket_<V> { using type = v944::ClientboundAttributeLayerSyncPacket; };

template <int V> requires (V >= 975 && V < 1001)
struct ClientboundAttributeLayerSyncPacket_<V> { using type = v975::ClientboundAttributeLayerSyncPacket; };

template <int V> requires (V >= 1001 && V < 2193)
struct ClientboundAttributeLayerSyncPacket_<V> { using type = v1001::ClientboundAttributeLayerSyncPacket; };

template <int V> requires (V >= 2193 && V < 2225)
struct ClientboundAttributeLayerSyncPacket_<V> { using type = v2193::ClientboundAttributeLayerSyncPacket; };

template <int V> requires (V >= 2225)
struct ClientboundAttributeLayerSyncPacket_<V> { using type = v2225::ClientboundAttributeLayerSyncPacket; };

template <int V>
struct AttributeDataPayload_;

template <int V> requires (V >= 2225)
struct AttributeDataPayload_<V> { using type = v2225::AttributeDataPayload; };

}  // namespace detail

template <int V> using NoiseAlignmentType_ = typename detail::NoiseAlignmentType_<V>::type;
template <int V> using NoiseAlignment_ = typename detail::NoiseAlignment_<V>::type;
template <int V> using ConstantAttributeData_ = typename detail::ConstantAttributeData_<V>::type;
template <int V> using TransitionSettingsData_ = typename detail::TransitionSettingsData_<V>::type;
template <int V> using TransitionAttributeData_ = typename detail::TransitionAttributeData_<V>::type;
template <int V> using NoiseTransitionSettingsData_ = typename detail::NoiseTransitionSettingsData_<V>::type;
template <int V> using NoiseTransitionAttributeData_ = typename detail::NoiseTransitionAttributeData_<V>::type;
template <int V> using EnvironmentAttributeData_ = typename detail::EnvironmentAttributeData_<V>::type;
template <int V> using AttributeLayerSettings_ = typename detail::AttributeLayerSettings_<V>::type;
template <int V> using AttributeLayerData_ = typename detail::AttributeLayerData_<V>::type;
template <int V> using UpdateAttributeLayersData_ = typename detail::UpdateAttributeLayersData_<V>::type;
template <int V> using UpdateAttributeLayerSettingsData_ = typename detail::UpdateAttributeLayerSettingsData_<V>::type;
template <int V> using UpdateEnvironmentAttributesData_ = typename detail::UpdateEnvironmentAttributesData_<V>::type;
template <int V> using ClientboundAttributeLayerSyncPacket_ = typename detail::ClientboundAttributeLayerSyncPacket_<V>::type;
template <int V> using AttributeDataPayload_ = typename detail::AttributeDataPayload_<V>::type;

template <int V> requires (V >= 944)
struct packet_of<V, 345> { using type = ClientboundAttributeLayerSyncPacket_<V>; };

namespace detail {

template <>
inline constexpr std::array<BoolAttributeOperation, 8> values_v<BoolAttributeOperation>{{
    BoolAttributeOperation::Override,
    BoolAttributeOperation::AlphaBlend,
    BoolAttributeOperation::And,
    BoolAttributeOperation::Nand,
    BoolAttributeOperation::Or,
    BoolAttributeOperation::Nor,
    BoolAttributeOperation::Xor,
    BoolAttributeOperation::Xnor,
}};

template <>
inline constexpr std::array<std::string_view, 8> names_v<BoolAttributeOperation>{{
    "override",
    "alpha_blend",
    "and",
    "nand",
    "or",
    "nor",
    "xor",
    "xnor",
}};

template <>
inline constexpr std::string_view type_name_v<BoolAttributeOperation>{"BoolAttributeOperation"};

template <>
inline constexpr std::array<FloatAttributeOperation, 7> values_v<FloatAttributeOperation>{{
    FloatAttributeOperation::Override,
    FloatAttributeOperation::AlphaBlend,
    FloatAttributeOperation::Add,
    FloatAttributeOperation::Subtract,
    FloatAttributeOperation::Multiply,
    FloatAttributeOperation::Minimum,
    FloatAttributeOperation::Maximum,
}};

template <>
inline constexpr std::array<std::string_view, 7> names_v<FloatAttributeOperation>{{
    "override",
    "alpha_blend",
    "add",
    "subtract",
    "multiply",
    "minimum",
    "maximum",
}};

template <>
inline constexpr std::string_view type_name_v<FloatAttributeOperation>{"FloatAttributeOperation"};

template <>
inline constexpr std::array<ColorAttributeOperation, 5> values_v<ColorAttributeOperation>{{
    ColorAttributeOperation::Override,
    ColorAttributeOperation::AlphaBlend,
    ColorAttributeOperation::Add,
    ColorAttributeOperation::Subtract,
    ColorAttributeOperation::Multiply,
}};

template <>
inline constexpr std::array<std::string_view, 5> names_v<ColorAttributeOperation>{{
    "override",
    "alpha_blend",
    "add",
    "subtract",
    "multiply",
}};

template <>
inline constexpr std::string_view type_name_v<ColorAttributeOperation>{"ColorAttributeOperation"};

template <>
inline constexpr std::array<EasingType, 32> values_v<EasingType>{{
    EasingType::Linear,
    EasingType::Spring,
    EasingType::InQuad,
    EasingType::OutQuad,
    EasingType::InOutQuad,
    EasingType::InCubic,
    EasingType::OutCubic,
    EasingType::InOutCubic,
    EasingType::InQuart,
    EasingType::OutQuart,
    EasingType::InOutQuart,
    EasingType::InQuint,
    EasingType::OutQuint,
    EasingType::InOutQuint,
    EasingType::InSine,
    EasingType::OutSine,
    EasingType::InOutSine,
    EasingType::InExpo,
    EasingType::OutExpo,
    EasingType::InOutExpo,
    EasingType::InCirc,
    EasingType::OutCirc,
    EasingType::InOutCirc,
    EasingType::InBounce,
    EasingType::OutBounce,
    EasingType::InOutBounce,
    EasingType::InBack,
    EasingType::OutBack,
    EasingType::InOutBack,
    EasingType::InElastic,
    EasingType::OutElastic,
    EasingType::InOutElastic,
}};

template <>
inline constexpr std::array<std::string_view, 32> names_v<EasingType>{{
    "linear",
    "spring",
    "in_quad",
    "out_quad",
    "in_out_quad",
    "in_cubic",
    "out_cubic",
    "in_out_cubic",
    "in_quart",
    "out_quart",
    "in_out_quart",
    "in_quint",
    "out_quint",
    "in_out_quint",
    "in_sine",
    "out_sine",
    "in_out_sine",
    "in_expo",
    "out_expo",
    "in_out_expo",
    "in_circ",
    "out_circ",
    "in_out_circ",
    "in_bounce",
    "out_bounce",
    "in_out_bounce",
    "in_back",
    "out_back",
    "in_out_back",
    "in_elastic",
    "out_elastic",
    "in_out_elastic",
}};

template <>
inline constexpr std::string_view type_name_v<EasingType>{"EasingType"};

template <>
inline constexpr std::array<v2193::NoiseAlignmentType, 1> values_v<v2193::NoiseAlignmentType>{{
    v2193::NoiseAlignmentType::MinLocalTransitionEnd,
}};

template <>
inline constexpr std::array<std::string_view, 1> names_v<v2193::NoiseAlignmentType>{{
    "minlocaltransitionend",
}};

template <>
inline constexpr std::string_view type_name_v<v2193::NoiseAlignmentType>{"NoiseAlignmentType"};

}  // namespace detail

namespace detail {

template <>
inline constexpr bool is_reflected_struct_v<Color255RGBA> = true;

template <>
inline constexpr std::string_view struct_name_v<Color255RGBA>{"Color255RGBA"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<Color255RGBA>{{
    "r",
    "g",
    "b",
    "a",
}};

template <>
struct field_accessor<Color255RGBA> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.r;
        }
        else if constexpr (I == 1) {
            return value.g;
        }
        else if constexpr (I == 2) {
            return value.b;
        }
        else {
            return value.a;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2193::NoiseAlignment> = true;

template <>
inline constexpr std::string_view struct_name_v<v2193::NoiseAlignment>{"NoiseAlignment"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2193::NoiseAlignment>{{
    "type",
    "value",
}};

template <>
struct field_accessor<v2193::NoiseAlignment> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.type;
        }
        else {
            return value.value;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<BoolAttributeData> = true;

template <>
inline constexpr std::string_view struct_name_v<BoolAttributeData>{"BoolAttributeData"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<BoolAttributeData>{{
    "value",
    "operation",
}};

template <>
struct field_accessor<BoolAttributeData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.value;
        }
        else {
            return value.operation;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<FloatAttributeData> = true;

template <>
inline constexpr std::string_view struct_name_v<FloatAttributeData>{"FloatAttributeData"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<FloatAttributeData>{{
    "value",
    "operation",
    "constraint_min_value",
    "constraint_max_value",
}};

template <>
struct field_accessor<FloatAttributeData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.value;
        }
        else if constexpr (I == 1) {
            return value.operation;
        }
        else if constexpr (I == 2) {
            return value.constraint_min_value;
        }
        else {
            return value.constraint_max_value;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<ColorAttributeData> = true;

template <>
inline constexpr std::string_view struct_name_v<ColorAttributeData>{"ColorAttributeData"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<ColorAttributeData>{{
    "value",
    "operation",
}};

template <>
struct field_accessor<ColorAttributeData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.value;
        }
        else {
            return value.operation;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::ConstantAttributeData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::ConstantAttributeData>{"ConstantAttributeData"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2225::ConstantAttributeData>{{
    "attribute",
}};

template <>
struct field_accessor<v2225::ConstantAttributeData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.attribute;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::TransitionSettingsData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::TransitionSettingsData>{"TransitionSettingsData"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v2225::TransitionSettingsData>{{
    "total_transition_ticks",
    "current_transition_ticks",
    "easing",
    "clock_name",
}};

template <>
struct field_accessor<v2225::TransitionSettingsData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.total_transition_ticks;
        }
        else if constexpr (I == 1) {
            return value.current_transition_ticks;
        }
        else if constexpr (I == 2) {
            return value.easing;
        }
        else {
            return value.clock_name;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::TransitionAttributeData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::TransitionAttributeData>{"TransitionAttributeData"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v2225::TransitionAttributeData>{{
    "from_attribute",
    "to_attribute",
    "settings",
}};

template <>
struct field_accessor<v2225::TransitionAttributeData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.from_attribute;
        }
        else if constexpr (I == 1) {
            return value.to_attribute;
        }
        else {
            return value.settings;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::NoiseTransitionSettingsData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::NoiseTransitionSettingsData>{"NoiseTransitionSettingsData"};

template <>
inline constexpr std::array<std::string_view, 7> field_names_v<v2225::NoiseTransitionSettingsData>{{
    "total_transition_ticks",
    "current_transition_ticks",
    "easing",
    "clock_name",
    "local_transition_ticks",
    "noise_name",
    "noise_alignment",
}};

template <>
struct field_accessor<v2225::NoiseTransitionSettingsData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.total_transition_ticks;
        }
        else if constexpr (I == 1) {
            return value.current_transition_ticks;
        }
        else if constexpr (I == 2) {
            return value.easing;
        }
        else if constexpr (I == 3) {
            return value.clock_name;
        }
        else if constexpr (I == 4) {
            return value.local_transition_ticks;
        }
        else if constexpr (I == 5) {
            return value.noise_name;
        }
        else {
            return value.noise_alignment;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::NoiseTransitionAttributeData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::NoiseTransitionAttributeData>{"NoiseTransitionAttributeData"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v2225::NoiseTransitionAttributeData>{{
    "from_attribute",
    "to_attribute",
    "settings",
}};

template <>
struct field_accessor<v2225::NoiseTransitionAttributeData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.from_attribute;
        }
        else if constexpr (I == 1) {
            return value.to_attribute;
        }
        else {
            return value.settings;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::EnvironmentAttributeData> = true;

template <>
inline constexpr std::string_view struct_name_v<base::EnvironmentAttributeData>{"EnvironmentAttributeData"};

template <>
inline constexpr std::array<std::string_view, 7> field_names_v<base::EnvironmentAttributeData>{{
    "name",
    "from_attribute",
    "attribute",
    "to_attribute",
    "current_transition_ticks",
    "total_transition_ticks",
    "easing",
}};

template <>
struct field_accessor<base::EnvironmentAttributeData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.name;
        }
        else if constexpr (I == 1) {
            return value.from_attribute;
        }
        else if constexpr (I == 2) {
            return value.attribute;
        }
        else if constexpr (I == 3) {
            return value.to_attribute;
        }
        else if constexpr (I == 4) {
            return value.current_transition_ticks;
        }
        else if constexpr (I == 5) {
            return value.total_transition_ticks;
        }
        else {
            return value.easing;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::EnvironmentAttributeData> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::EnvironmentAttributeData>{"EnvironmentAttributeData"};

template <>
inline constexpr std::array<std::string_view, 9> field_names_v<v1001::EnvironmentAttributeData>{{
    "name",
    "from_attribute",
    "attribute",
    "to_attribute",
    "current_transition_ticks",
    "total_transition_ticks",
    "easing",
    "local_transition_ticks",
    "noise_transition",
}};

template <>
struct field_accessor<v1001::EnvironmentAttributeData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.name;
        }
        else if constexpr (I == 1) {
            return value.from_attribute;
        }
        else if constexpr (I == 2) {
            return value.attribute;
        }
        else if constexpr (I == 3) {
            return value.to_attribute;
        }
        else if constexpr (I == 4) {
            return value.current_transition_ticks;
        }
        else if constexpr (I == 5) {
            return value.total_transition_ticks;
        }
        else if constexpr (I == 6) {
            return value.easing;
        }
        else if constexpr (I == 7) {
            return value.local_transition_ticks;
        }
        else {
            return value.noise_transition;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2193::EnvironmentAttributeData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2193::EnvironmentAttributeData>{"EnvironmentAttributeData"};

template <>
inline constexpr std::array<std::string_view, 10> field_names_v<v2193::EnvironmentAttributeData>{{
    "name",
    "from_attribute",
    "attribute",
    "to_attribute",
    "current_transition_ticks",
    "total_transition_ticks",
    "easing",
    "local_transition_ticks",
    "noise_transition",
    "noise_alignment",
}};

template <>
struct field_accessor<v2193::EnvironmentAttributeData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.name;
        }
        else if constexpr (I == 1) {
            return value.from_attribute;
        }
        else if constexpr (I == 2) {
            return value.attribute;
        }
        else if constexpr (I == 3) {
            return value.to_attribute;
        }
        else if constexpr (I == 4) {
            return value.current_transition_ticks;
        }
        else if constexpr (I == 5) {
            return value.total_transition_ticks;
        }
        else if constexpr (I == 6) {
            return value.easing;
        }
        else if constexpr (I == 7) {
            return value.local_transition_ticks;
        }
        else if constexpr (I == 8) {
            return value.noise_transition;
        }
        else {
            return value.noise_alignment;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::EnvironmentAttributeData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::EnvironmentAttributeData>{"EnvironmentAttributeData"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2225::EnvironmentAttributeData>{{
    "name",
    "payload",
}};

template <>
struct field_accessor<v2225::EnvironmentAttributeData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.name;
        }
        else {
            return value.payload;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::AttributeLayerSettings> = true;

template <>
inline constexpr std::string_view struct_name_v<base::AttributeLayerSettings>{"AttributeLayerSettings"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<base::AttributeLayerSettings>{{
    "priority",
    "weight",
    "enabled",
    "transitions_paused",
}};

template <>
struct field_accessor<base::AttributeLayerSettings> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.priority;
        }
        else if constexpr (I == 1) {
            return value.weight;
        }
        else if constexpr (I == 2) {
            return value.enabled;
        }
        else {
            return value.transitions_paused;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v975::AttributeLayerSettings> = true;

template <>
inline constexpr std::string_view struct_name_v<v975::AttributeLayerSettings>{"AttributeLayerSettings"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v975::AttributeLayerSettings>{{
    "priority",
    "weight",
    "enabled",
    "transitions_paused",
}};

template <>
struct field_accessor<v975::AttributeLayerSettings> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.priority;
        }
        else if constexpr (I == 1) {
            return value.weight;
        }
        else if constexpr (I == 2) {
            return value.enabled;
        }
        else {
            return value.transitions_paused;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::AttributeLayerData> = true;

template <>
inline constexpr std::string_view struct_name_v<base::AttributeLayerData>{"AttributeLayerData"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<base::AttributeLayerData>{{
    "name",
    "dimension_id",
    "settings",
    "attributes",
}};

template <>
struct field_accessor<base::AttributeLayerData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.name;
        }
        else if constexpr (I == 1) {
            return value.dimension_id;
        }
        else if constexpr (I == 2) {
            return value.settings;
        }
        else {
            return value.attributes;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v975::AttributeLayerData> = true;

template <>
inline constexpr std::string_view struct_name_v<v975::AttributeLayerData>{"AttributeLayerData"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v975::AttributeLayerData>{{
    "name",
    "dimension_id",
    "settings",
    "attributes",
}};

template <>
struct field_accessor<v975::AttributeLayerData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.name;
        }
        else if constexpr (I == 1) {
            return value.dimension_id;
        }
        else if constexpr (I == 2) {
            return value.settings;
        }
        else {
            return value.attributes;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::AttributeLayerData> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::AttributeLayerData>{"AttributeLayerData"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v1001::AttributeLayerData>{{
    "name",
    "noise_name",
    "dimension_id",
    "settings",
    "attributes",
}};

template <>
struct field_accessor<v1001::AttributeLayerData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.name;
        }
        else if constexpr (I == 1) {
            return value.noise_name;
        }
        else if constexpr (I == 2) {
            return value.dimension_id;
        }
        else if constexpr (I == 3) {
            return value.settings;
        }
        else {
            return value.attributes;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2193::AttributeLayerData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2193::AttributeLayerData>{"AttributeLayerData"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v2193::AttributeLayerData>{{
    "name",
    "noise_name",
    "dimension_id",
    "settings",
    "attributes",
}};

template <>
struct field_accessor<v2193::AttributeLayerData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.name;
        }
        else if constexpr (I == 1) {
            return value.noise_name;
        }
        else if constexpr (I == 2) {
            return value.dimension_id;
        }
        else if constexpr (I == 3) {
            return value.settings;
        }
        else {
            return value.attributes;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::AttributeLayerData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::AttributeLayerData>{"AttributeLayerData"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v2225::AttributeLayerData>{{
    "name",
    "dimension_id",
    "settings",
    "attributes",
}};

template <>
struct field_accessor<v2225::AttributeLayerData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.name;
        }
        else if constexpr (I == 1) {
            return value.dimension_id;
        }
        else if constexpr (I == 2) {
            return value.settings;
        }
        else {
            return value.attributes;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::UpdateAttributeLayersData> = true;

template <>
inline constexpr std::string_view struct_name_v<base::UpdateAttributeLayersData>{"UpdateAttributeLayersData"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::UpdateAttributeLayersData>{{
    "attribute_layers",
}};

template <>
struct field_accessor<base::UpdateAttributeLayersData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.attribute_layers;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v975::UpdateAttributeLayersData> = true;

template <>
inline constexpr std::string_view struct_name_v<v975::UpdateAttributeLayersData>{"UpdateAttributeLayersData"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v975::UpdateAttributeLayersData>{{
    "attribute_layers",
}};

template <>
struct field_accessor<v975::UpdateAttributeLayersData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.attribute_layers;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::UpdateAttributeLayersData> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::UpdateAttributeLayersData>{"UpdateAttributeLayersData"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v1001::UpdateAttributeLayersData>{{
    "attribute_layers",
}};

template <>
struct field_accessor<v1001::UpdateAttributeLayersData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.attribute_layers;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2193::UpdateAttributeLayersData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2193::UpdateAttributeLayersData>{"UpdateAttributeLayersData"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2193::UpdateAttributeLayersData>{{
    "attribute_layers",
}};

template <>
struct field_accessor<v2193::UpdateAttributeLayersData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.attribute_layers;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::UpdateAttributeLayersData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::UpdateAttributeLayersData>{"UpdateAttributeLayersData"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2225::UpdateAttributeLayersData>{{
    "attribute_layers",
}};

template <>
struct field_accessor<v2225::UpdateAttributeLayersData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.attribute_layers;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::UpdateAttributeLayerSettingsData> = true;

template <>
inline constexpr std::string_view struct_name_v<base::UpdateAttributeLayerSettingsData>{"UpdateAttributeLayerSettingsData"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<base::UpdateAttributeLayerSettingsData>{{
    "layer_name",
    "layer_dimension_id",
    "attribute_layer_settings",
}};

template <>
struct field_accessor<base::UpdateAttributeLayerSettingsData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.layer_name;
        }
        else if constexpr (I == 1) {
            return value.layer_dimension_id;
        }
        else {
            return value.attribute_layer_settings;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v975::UpdateAttributeLayerSettingsData> = true;

template <>
inline constexpr std::string_view struct_name_v<v975::UpdateAttributeLayerSettingsData>{"UpdateAttributeLayerSettingsData"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v975::UpdateAttributeLayerSettingsData>{{
    "layer_name",
    "layer_dimension_id",
    "attribute_layer_settings",
}};

template <>
struct field_accessor<v975::UpdateAttributeLayerSettingsData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.layer_name;
        }
        else if constexpr (I == 1) {
            return value.layer_dimension_id;
        }
        else {
            return value.attribute_layer_settings;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::UpdateEnvironmentAttributesData> = true;

template <>
inline constexpr std::string_view struct_name_v<base::UpdateEnvironmentAttributesData>{"UpdateEnvironmentAttributesData"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<base::UpdateEnvironmentAttributesData>{{
    "layer_name",
    "layer_dimension_id",
    "attributes",
}};

template <>
struct field_accessor<base::UpdateEnvironmentAttributesData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.layer_name;
        }
        else if constexpr (I == 1) {
            return value.layer_dimension_id;
        }
        else {
            return value.attributes;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::UpdateEnvironmentAttributesData> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::UpdateEnvironmentAttributesData>{"UpdateEnvironmentAttributesData"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v1001::UpdateEnvironmentAttributesData>{{
    "layer_name",
    "layer_dimension_id",
    "attributes",
}};

template <>
struct field_accessor<v1001::UpdateEnvironmentAttributesData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.layer_name;
        }
        else if constexpr (I == 1) {
            return value.layer_dimension_id;
        }
        else {
            return value.attributes;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2193::UpdateEnvironmentAttributesData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2193::UpdateEnvironmentAttributesData>{"UpdateEnvironmentAttributesData"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v2193::UpdateEnvironmentAttributesData>{{
    "layer_name",
    "layer_dimension_id",
    "attributes",
}};

template <>
struct field_accessor<v2193::UpdateEnvironmentAttributesData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.layer_name;
        }
        else if constexpr (I == 1) {
            return value.layer_dimension_id;
        }
        else {
            return value.attributes;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::UpdateEnvironmentAttributesData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::UpdateEnvironmentAttributesData>{"UpdateEnvironmentAttributesData"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v2225::UpdateEnvironmentAttributesData>{{
    "layer_name",
    "layer_dimension_id",
    "attributes",
}};

template <>
struct field_accessor<v2225::UpdateEnvironmentAttributesData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.layer_name;
        }
        else if constexpr (I == 1) {
            return value.layer_dimension_id;
        }
        else {
            return value.attributes;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<RemoveEnvironmentAttributesData> = true;

template <>
inline constexpr std::string_view struct_name_v<RemoveEnvironmentAttributesData>{"RemoveEnvironmentAttributesData"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<RemoveEnvironmentAttributesData>{{
    "layer_name",
    "layer_dimension_id",
    "attributes",
}};

template <>
struct field_accessor<RemoveEnvironmentAttributesData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.layer_name;
        }
        else if constexpr (I == 1) {
            return value.layer_dimension_id;
        }
        else {
            return value.attributes;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::ClientboundAttributeLayerSyncPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::ClientboundAttributeLayerSyncPacket>{"ClientboundAttributeLayerSyncPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v944::ClientboundAttributeLayerSyncPacket>{{
    "data",
}};

template <>
struct field_accessor<v944::ClientboundAttributeLayerSyncPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.data;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v975::ClientboundAttributeLayerSyncPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v975::ClientboundAttributeLayerSyncPacket>{"ClientboundAttributeLayerSyncPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v975::ClientboundAttributeLayerSyncPacket>{{
    "data",
}};

template <>
struct field_accessor<v975::ClientboundAttributeLayerSyncPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.data;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::ClientboundAttributeLayerSyncPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::ClientboundAttributeLayerSyncPacket>{"ClientboundAttributeLayerSyncPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v1001::ClientboundAttributeLayerSyncPacket>{{
    "data",
}};

template <>
struct field_accessor<v1001::ClientboundAttributeLayerSyncPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.data;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2193::ClientboundAttributeLayerSyncPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2193::ClientboundAttributeLayerSyncPacket>{"ClientboundAttributeLayerSyncPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2193::ClientboundAttributeLayerSyncPacket>{{
    "data",
}};

template <>
struct field_accessor<v2193::ClientboundAttributeLayerSyncPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.data;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::ClientboundAttributeLayerSyncPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::ClientboundAttributeLayerSyncPacket>{"ClientboundAttributeLayerSyncPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2225::ClientboundAttributeLayerSyncPacket>{{
    "data",
}};

template <>
struct field_accessor<v2225::ClientboundAttributeLayerSyncPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.data;
    }
};

}  // namespace detail


template <>
struct Serializer<Color255RGBA> {
    static void serialize(BinaryWriter &stream, const Color255RGBA &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<Color255RGBA, std::error_code>;
};

template <>
struct Serializer<BoolAttributeOperation> {
    static void serialize(BinaryWriter &stream, BoolAttributeOperation value);
    static auto deserialize(BinaryReader &stream) -> std::expected<BoolAttributeOperation, std::error_code>;
};

template <>
struct Serializer<FloatAttributeOperation> {
    static void serialize(BinaryWriter &stream, FloatAttributeOperation value);
    static auto deserialize(BinaryReader &stream) -> std::expected<FloatAttributeOperation, std::error_code>;
};

template <>
struct Serializer<ColorAttributeOperation> {
    static void serialize(BinaryWriter &stream, ColorAttributeOperation value);
    static auto deserialize(BinaryReader &stream) -> std::expected<ColorAttributeOperation, std::error_code>;
};

template <>
struct Serializer<EasingType> {
    static void serialize(BinaryWriter &stream, EasingType value);
    static auto deserialize(BinaryReader &stream) -> std::expected<EasingType, std::error_code>;
};

template <>
struct Serializer<v2193::NoiseAlignment> {
    static void serialize(BinaryWriter &stream, const v2193::NoiseAlignment &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::NoiseAlignment, std::error_code>;
};

template <>
struct Serializer<BoolAttributeData> {
    static void serialize(BinaryWriter &stream, const BoolAttributeData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<BoolAttributeData, std::error_code>;
};

template <>
struct Serializer<FloatAttributeData> {
    static void serialize(BinaryWriter &stream, const FloatAttributeData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<FloatAttributeData, std::error_code>;
};

template <>
struct Serializer<ColorAttributeData> {
    static void serialize(BinaryWriter &stream, const ColorAttributeData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<ColorAttributeData, std::error_code>;
};

template <>
struct Serializer<v2225::ConstantAttributeData> {
    static void serialize(BinaryWriter &stream, const v2225::ConstantAttributeData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::ConstantAttributeData, std::error_code>;
};

template <>
struct Serializer<v2225::TransitionSettingsData> {
    static void serialize(BinaryWriter &stream, const v2225::TransitionSettingsData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::TransitionSettingsData, std::error_code>;
};

template <>
struct Serializer<v2225::TransitionAttributeData> {
    static void serialize(BinaryWriter &stream, const v2225::TransitionAttributeData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::TransitionAttributeData, std::error_code>;
};

template <>
struct Serializer<v2225::NoiseTransitionSettingsData> {
    static void serialize(BinaryWriter &stream, const v2225::NoiseTransitionSettingsData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::NoiseTransitionSettingsData, std::error_code>;
};

template <>
struct Serializer<v2225::NoiseTransitionAttributeData> {
    static void serialize(BinaryWriter &stream, const v2225::NoiseTransitionAttributeData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::NoiseTransitionAttributeData, std::error_code>;
};

template <>
struct Serializer<base::EnvironmentAttributeData> {
    static void serialize(BinaryWriter &stream, const base::EnvironmentAttributeData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::EnvironmentAttributeData, std::error_code>;
};

template <>
struct Serializer<v1001::EnvironmentAttributeData> {
    static void serialize(BinaryWriter &stream, const v1001::EnvironmentAttributeData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::EnvironmentAttributeData, std::error_code>;
};

template <>
struct Serializer<v2193::EnvironmentAttributeData> {
    static void serialize(BinaryWriter &stream, const v2193::EnvironmentAttributeData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::EnvironmentAttributeData, std::error_code>;
};

template <>
struct Serializer<v2225::EnvironmentAttributeData> {
    static void serialize(BinaryWriter &stream, const v2225::EnvironmentAttributeData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::EnvironmentAttributeData, std::error_code>;
};

template <>
struct Serializer<base::AttributeLayerSettings> {
    static void serialize(BinaryWriter &stream, const base::AttributeLayerSettings &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::AttributeLayerSettings, std::error_code>;
};

template <>
struct Serializer<v975::AttributeLayerSettings> {
    static void serialize(BinaryWriter &stream, const v975::AttributeLayerSettings &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v975::AttributeLayerSettings, std::error_code>;
};

template <>
struct Serializer<base::AttributeLayerData> {
    static void serialize(BinaryWriter &stream, const base::AttributeLayerData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::AttributeLayerData, std::error_code>;
};

template <>
struct Serializer<v975::AttributeLayerData> {
    static void serialize(BinaryWriter &stream, const v975::AttributeLayerData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v975::AttributeLayerData, std::error_code>;
};

template <>
struct Serializer<v1001::AttributeLayerData> {
    static void serialize(BinaryWriter &stream, const v1001::AttributeLayerData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::AttributeLayerData, std::error_code>;
};

template <>
struct Serializer<v2193::AttributeLayerData> {
    static void serialize(BinaryWriter &stream, const v2193::AttributeLayerData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::AttributeLayerData, std::error_code>;
};

template <>
struct Serializer<v2225::AttributeLayerData> {
    static void serialize(BinaryWriter &stream, const v2225::AttributeLayerData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::AttributeLayerData, std::error_code>;
};

template <>
struct Serializer<base::UpdateAttributeLayersData> {
    static void serialize(BinaryWriter &stream, const base::UpdateAttributeLayersData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::UpdateAttributeLayersData, std::error_code>;
};

template <>
struct Serializer<v975::UpdateAttributeLayersData> {
    static void serialize(BinaryWriter &stream, const v975::UpdateAttributeLayersData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v975::UpdateAttributeLayersData, std::error_code>;
};

template <>
struct Serializer<v1001::UpdateAttributeLayersData> {
    static void serialize(BinaryWriter &stream, const v1001::UpdateAttributeLayersData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::UpdateAttributeLayersData, std::error_code>;
};

template <>
struct Serializer<v2193::UpdateAttributeLayersData> {
    static void serialize(BinaryWriter &stream, const v2193::UpdateAttributeLayersData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::UpdateAttributeLayersData, std::error_code>;
};

template <>
struct Serializer<v2225::UpdateAttributeLayersData> {
    static void serialize(BinaryWriter &stream, const v2225::UpdateAttributeLayersData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::UpdateAttributeLayersData, std::error_code>;
};

template <>
struct Serializer<base::UpdateAttributeLayerSettingsData> {
    static void serialize(BinaryWriter &stream, const base::UpdateAttributeLayerSettingsData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::UpdateAttributeLayerSettingsData, std::error_code>;
};

template <>
struct Serializer<v975::UpdateAttributeLayerSettingsData> {
    static void serialize(BinaryWriter &stream, const v975::UpdateAttributeLayerSettingsData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v975::UpdateAttributeLayerSettingsData, std::error_code>;
};

template <>
struct Serializer<base::UpdateEnvironmentAttributesData> {
    static void serialize(BinaryWriter &stream, const base::UpdateEnvironmentAttributesData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::UpdateEnvironmentAttributesData, std::error_code>;
};

template <>
struct Serializer<v1001::UpdateEnvironmentAttributesData> {
    static void serialize(BinaryWriter &stream, const v1001::UpdateEnvironmentAttributesData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::UpdateEnvironmentAttributesData, std::error_code>;
};

template <>
struct Serializer<v2193::UpdateEnvironmentAttributesData> {
    static void serialize(BinaryWriter &stream, const v2193::UpdateEnvironmentAttributesData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::UpdateEnvironmentAttributesData, std::error_code>;
};

template <>
struct Serializer<v2225::UpdateEnvironmentAttributesData> {
    static void serialize(BinaryWriter &stream, const v2225::UpdateEnvironmentAttributesData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::UpdateEnvironmentAttributesData, std::error_code>;
};

template <>
struct Serializer<RemoveEnvironmentAttributesData> {
    static void serialize(BinaryWriter &stream, const RemoveEnvironmentAttributesData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<RemoveEnvironmentAttributesData, std::error_code>;
};

template <>
struct Serializer<v944::ClientboundAttributeLayerSyncPacket> {
    static void serialize(BinaryWriter &stream, const v944::ClientboundAttributeLayerSyncPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::ClientboundAttributeLayerSyncPacket, std::error_code>;
};

template <>
struct Serializer<v975::ClientboundAttributeLayerSyncPacket> {
    static void serialize(BinaryWriter &stream, const v975::ClientboundAttributeLayerSyncPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v975::ClientboundAttributeLayerSyncPacket, std::error_code>;
};

template <>
struct Serializer<v1001::ClientboundAttributeLayerSyncPacket> {
    static void serialize(BinaryWriter &stream, const v1001::ClientboundAttributeLayerSyncPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::ClientboundAttributeLayerSyncPacket, std::error_code>;
};

template <>
struct Serializer<v2193::ClientboundAttributeLayerSyncPacket> {
    static void serialize(BinaryWriter &stream, const v2193::ClientboundAttributeLayerSyncPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::ClientboundAttributeLayerSyncPacket, std::error_code>;
};

template <>
struct Serializer<v2225::ClientboundAttributeLayerSyncPacket> {
    static void serialize(BinaryWriter &stream, const v2225::ClientboundAttributeLayerSyncPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::ClientboundAttributeLayerSyncPacket, std::error_code>;
};

template <>
struct Serializer<AttributeDataVariant> {
    static void serialize(BinaryWriter &stream, const AttributeDataVariant &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<AttributeDataVariant, std::error_code>;
};

template <>
struct Serializer<v2225::AttributeDataPayload> {
    static void serialize(BinaryWriter &stream, const v2225::AttributeDataPayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::AttributeDataPayload, std::error_code>;
};
using NoiseAlignmentType = NoiseAlignmentType_<2225>;
using NoiseAlignment = NoiseAlignment_<2225>;
using ConstantAttributeData = ConstantAttributeData_<2225>;
using TransitionSettingsData = TransitionSettingsData_<2225>;
using TransitionAttributeData = TransitionAttributeData_<2225>;
using NoiseTransitionSettingsData = NoiseTransitionSettingsData_<2225>;
using NoiseTransitionAttributeData = NoiseTransitionAttributeData_<2225>;
using EnvironmentAttributeData = EnvironmentAttributeData_<2225>;
using AttributeLayerSettings = AttributeLayerSettings_<2225>;
using AttributeLayerData = AttributeLayerData_<2225>;
using UpdateAttributeLayersData = UpdateAttributeLayersData_<2225>;
using UpdateAttributeLayerSettingsData = UpdateAttributeLayerSettingsData_<2225>;
using UpdateEnvironmentAttributesData = UpdateEnvironmentAttributesData_<2225>;
using ClientboundAttributeLayerSyncPacket = ClientboundAttributeLayerSyncPacket_<2225>;
using AttributeDataPayload = AttributeDataPayload_<2225>;

}  // namespace bedrock::protocol
