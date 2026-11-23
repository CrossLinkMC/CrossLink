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
#include <bedrock/protocol/enum.hpp>
#include <bedrock/protocol/packet.hpp>
#include <bedrock/protocol/serializer.hpp>
#include <bedrock/protocol/stream.hpp>

#include <bedrock/protocol/common.h>

namespace bedrock::protocol {

namespace base {

enum class GraphicsOverrideParameterType : std::uint8_t {
    SkyZenithColor = 0,
};

}  // namespace base

namespace v859 {

using GraphicsOverrideParameterType = base::GraphicsOverrideParameterType;

struct GraphicsOverrideParameterPacket {
    static constexpr int Id = 331;
    std::map<float, Vec3> keyframes{};
    std::string biome_id{};
    base::GraphicsOverrideParameterType parameter_id{};
    bool reset_parameter{};
};

}  // namespace v859

namespace v898 {

enum class GraphicsOverrideParameterType : std::uint8_t {
    SkyZenithColor = 0,
    SkyHorizonColor = 1,
    HorizonBlendMin = 2,
    HorizonBlendMax = 3,
    HorizonBlendStart = 4,
    HorizonBlendMieStart = 5,
    RayleighStrength = 6,
    SunMieStrength = 7,
    MoonMieStrength = 8,
    SunGlareShape = 9,
};

struct GraphicsOverrideParameterPacket {
    static constexpr int Id = 331;
    std::map<float, Vec3> keyframes{};
    std::string biome_id{};
    v898::GraphicsOverrideParameterType parameter_id{};
    bool reset_parameter{};
};

}  // namespace v898

namespace v924 {

enum class GraphicsOverrideParameterType : std::uint8_t {
    SkyZenithColor = 0,
    SkyHorizonColor = 1,
    HorizonBlendMin = 2,
    HorizonBlendMax = 3,
    HorizonBlendStart = 4,
    HorizonBlendMieStart = 5,
    RayleighStrength = 6,
    SunMieStrength = 7,
    MoonMieStrength = 8,
    SunGlareShape = 9,
    Chlorophyll = 10,
    CDOM = 11,
    SuspendedSediment = 12,
    WavesDepth = 13,
    WavesFrequency = 14,
    WavesFrequencyScaling = 15,
    WavesSpeed = 16,
    WavesSpeedScaling = 17,
    WavesShape = 18,
    WavesOctaves = 19,
    WavesMix = 20,
    WavesPull = 21,
    WavesDirectionIncrement = 22,
    MidtonesContrast = 23,
    HighlightsContrast = 24,
    ShadowsContrast = 25,
};

struct GraphicsOverrideParameterPacket {
    static constexpr int Id = 331;
    std::map<float, Vec3> keyframes{};
    std::optional<float> float_value{};
    std::optional<Vec3> vec3_value{};
    std::string biome_id{};
    v924::GraphicsOverrideParameterType parameter_id{};
    bool reset_parameter{};
};

}  // namespace v924

namespace v944 {

enum class GraphicsOverrideParameterType : std::uint8_t {
    SkyZenithColor = 0,
    SkyHorizonColor = 1,
    HorizonBlendMin = 2,
    HorizonBlendMax = 3,
    HorizonBlendStart = 4,
    HorizonBlendMieStart = 5,
    RayleighStrength = 6,
    SunMieStrength = 7,
    MoonMieStrength = 8,
    SunGlareShape = 9,
    Chlorophyll = 10,
    CDOM = 11,
    SuspendedSediment = 12,
    WavesDepth = 13,
    WavesFrequency = 14,
    WavesFrequencyScaling = 15,
    WavesSpeed = 16,
    WavesSpeedScaling = 17,
    WavesShape = 18,
    WavesOctaves = 19,
    WavesMix = 20,
    WavesPull = 21,
    WavesDirectionIncrement = 22,
    MidtonesContrast = 23,
    HighlightsContrast = 24,
    ShadowsContrast = 25,
    HighlightsGain = 26,
    HighlightsGamma = 27,
    HighlightsOffset = 28,
    HighlightsSaturation = 29,
    MidtonesGain = 30,
    MidtonesGamma = 31,
    MidtonesOffset = 32,
    MidtonesSaturation = 33,
    ShadowsGain = 34,
    ShadowsGamma = 35,
    ShadowsOffset = 36,
    ShadowsSaturation = 37,
    HighlightsMin = 38,
    ShadowsMax = 39,
    Temperature = 40,
    SunColor = 41,
    SunIlluminance = 42,
    MoonColor = 43,
    MoonIlluminance = 44,
    FlashColor = 45,
    FlashIlluminance = 46,
    AmbientColor = 47,
    AmbientIlluminance = 48,
};

struct GraphicsOverrideParameterPacket {
    static constexpr int Id = 331;
    std::map<float, Vec3> keyframes{};
    std::optional<float> float_value{};
    std::optional<Vec3> vec3_value{};
    std::string biome_id{};
    v944::GraphicsOverrideParameterType parameter_id{};
    bool reset_parameter{};
};

}  // namespace v944

namespace v975 {

enum class GraphicsOverrideParameterType : std::uint8_t {
    SkyZenithColor = 0,
    SkyHorizonColor = 1,
    HorizonBlendMin = 2,
    HorizonBlendMax = 3,
    HorizonBlendStart = 4,
    HorizonBlendMieStart = 5,
    RayleighStrength = 6,
    SunMieStrength = 7,
    MoonMieStrength = 8,
    SunGlareShape = 9,
    Chlorophyll = 10,
    CDOM = 11,
    SuspendedSediment = 12,
    WavesDepth = 13,
    WavesFrequency = 14,
    WavesFrequencyScaling = 15,
    WavesSpeed = 16,
    WavesSpeedScaling = 17,
    WavesShape = 18,
    WavesOctaves = 19,
    WavesMix = 20,
    WavesPull = 21,
    WavesDirectionIncrement = 22,
    MidtonesContrast = 23,
    HighlightsContrast = 24,
    ShadowsContrast = 25,
    HighlightsGain = 26,
    HighlightsGamma = 27,
    HighlightsOffset = 28,
    HighlightsSaturation = 29,
    MidtonesGain = 30,
    MidtonesGamma = 31,
    MidtonesOffset = 32,
    MidtonesSaturation = 33,
    ShadowsGain = 34,
    ShadowsGamma = 35,
    ShadowsOffset = 36,
    ShadowsSaturation = 37,
    HighlightsMin = 38,
    ShadowsMax = 39,
    Temperature = 40,
    SunColor = 41,
    SunIlluminance = 42,
    MoonColor = 43,
    MoonIlluminance = 44,
    FlashColor = 45,
    FlashIlluminance = 46,
    AmbientColor = 47,
    AmbientIlluminance = 48,
    EmissiveDesaturation = 49,
    SkyIntensity = 50,
    OrbitalOffsetDegrees = 51,
};

struct GraphicsOverrideParameterPacket {
    static constexpr int Id = 331;
    std::map<float, Vec3> keyframes{};
    std::optional<float> float_value{};
    std::optional<Vec3> vec3_value{};
    std::string biome_id{};
    v975::GraphicsOverrideParameterType parameter_id{};
    bool reset_parameter{};
};

}  // namespace v975

namespace v1001 {

using GraphicsOverrideParameterType = v975::GraphicsOverrideParameterType;

struct GraphicsOverrideParameterPacket {
    static constexpr int Id = 331;
    std::map<float, Vec3> keyframes{};
    std::optional<float> float_value{};
    std::optional<Vec3> vec3_value{};
    std::string biome_id{};
    std::optional<std::string> player_id{};
    v975::GraphicsOverrideParameterType parameter_id{};
    bool reset_parameter{};
};

}  // namespace v1001

namespace detail {

template <int V>
struct GraphicsOverrideParameterType_;

template <int V> requires (V < 898)
struct GraphicsOverrideParameterType_<V> { using type = base::GraphicsOverrideParameterType; };

template <int V> requires (V >= 898 && V < 924)
struct GraphicsOverrideParameterType_<V> { using type = v898::GraphicsOverrideParameterType; };

template <int V> requires (V >= 924 && V < 944)
struct GraphicsOverrideParameterType_<V> { using type = v924::GraphicsOverrideParameterType; };

template <int V> requires (V >= 944 && V < 975)
struct GraphicsOverrideParameterType_<V> { using type = v944::GraphicsOverrideParameterType; };

template <int V> requires (V >= 975)
struct GraphicsOverrideParameterType_<V> { using type = v975::GraphicsOverrideParameterType; };

template <int V>
struct GraphicsOverrideParameterPacket_;

template <int V> requires (V >= 859 && V < 898)
struct GraphicsOverrideParameterPacket_<V> { using type = v859::GraphicsOverrideParameterPacket; };

template <int V> requires (V >= 898 && V < 924)
struct GraphicsOverrideParameterPacket_<V> { using type = v898::GraphicsOverrideParameterPacket; };

template <int V> requires (V >= 924 && V < 944)
struct GraphicsOverrideParameterPacket_<V> { using type = v924::GraphicsOverrideParameterPacket; };

template <int V> requires (V >= 944 && V < 975)
struct GraphicsOverrideParameterPacket_<V> { using type = v944::GraphicsOverrideParameterPacket; };

template <int V> requires (V >= 975 && V < 1001)
struct GraphicsOverrideParameterPacket_<V> { using type = v975::GraphicsOverrideParameterPacket; };

template <int V> requires (V >= 1001)
struct GraphicsOverrideParameterPacket_<V> { using type = v1001::GraphicsOverrideParameterPacket; };

}  // namespace detail

template <int V> using GraphicsOverrideParameterType_ = typename detail::GraphicsOverrideParameterType_<V>::type;
template <int V> using GraphicsOverrideParameterPacket_ = typename detail::GraphicsOverrideParameterPacket_<V>::type;

template <int V> requires (V >= 859)
struct packet_of<V, 331> { using type = GraphicsOverrideParameterPacket_<V>; };

namespace detail {

template <>
inline constexpr std::array<base::GraphicsOverrideParameterType, 1> values_v<base::GraphicsOverrideParameterType>{{
    base::GraphicsOverrideParameterType::SkyZenithColor,
}};

template <>
inline constexpr std::array<std::string_view, 1> names_v<base::GraphicsOverrideParameterType>{{
    "skyzenithcolor",
}};

template <>
inline constexpr std::string_view type_name_v<base::GraphicsOverrideParameterType>{"GraphicsOverrideParameterType"};

template <>
inline constexpr std::array<v898::GraphicsOverrideParameterType, 10> values_v<v898::GraphicsOverrideParameterType>{{
    v898::GraphicsOverrideParameterType::SkyZenithColor,
    v898::GraphicsOverrideParameterType::SkyHorizonColor,
    v898::GraphicsOverrideParameterType::HorizonBlendMin,
    v898::GraphicsOverrideParameterType::HorizonBlendMax,
    v898::GraphicsOverrideParameterType::HorizonBlendStart,
    v898::GraphicsOverrideParameterType::HorizonBlendMieStart,
    v898::GraphicsOverrideParameterType::RayleighStrength,
    v898::GraphicsOverrideParameterType::SunMieStrength,
    v898::GraphicsOverrideParameterType::MoonMieStrength,
    v898::GraphicsOverrideParameterType::SunGlareShape,
}};

template <>
inline constexpr std::array<std::string_view, 10> names_v<v898::GraphicsOverrideParameterType>{{
    "skyzenithcolor",
    "skyhorizoncolor",
    "horizonblendmin",
    "horizonblendmax",
    "horizonblendstart",
    "horizonblendmiestart",
    "rayleighstrength",
    "sunmiestrength",
    "moonmiestrength",
    "sunglareshape",
}};

template <>
inline constexpr std::string_view type_name_v<v898::GraphicsOverrideParameterType>{"GraphicsOverrideParameterType"};

template <>
inline constexpr std::array<v924::GraphicsOverrideParameterType, 26> values_v<v924::GraphicsOverrideParameterType>{{
    v924::GraphicsOverrideParameterType::SkyZenithColor,
    v924::GraphicsOverrideParameterType::SkyHorizonColor,
    v924::GraphicsOverrideParameterType::HorizonBlendMin,
    v924::GraphicsOverrideParameterType::HorizonBlendMax,
    v924::GraphicsOverrideParameterType::HorizonBlendStart,
    v924::GraphicsOverrideParameterType::HorizonBlendMieStart,
    v924::GraphicsOverrideParameterType::RayleighStrength,
    v924::GraphicsOverrideParameterType::SunMieStrength,
    v924::GraphicsOverrideParameterType::MoonMieStrength,
    v924::GraphicsOverrideParameterType::SunGlareShape,
    v924::GraphicsOverrideParameterType::Chlorophyll,
    v924::GraphicsOverrideParameterType::CDOM,
    v924::GraphicsOverrideParameterType::SuspendedSediment,
    v924::GraphicsOverrideParameterType::WavesDepth,
    v924::GraphicsOverrideParameterType::WavesFrequency,
    v924::GraphicsOverrideParameterType::WavesFrequencyScaling,
    v924::GraphicsOverrideParameterType::WavesSpeed,
    v924::GraphicsOverrideParameterType::WavesSpeedScaling,
    v924::GraphicsOverrideParameterType::WavesShape,
    v924::GraphicsOverrideParameterType::WavesOctaves,
    v924::GraphicsOverrideParameterType::WavesMix,
    v924::GraphicsOverrideParameterType::WavesPull,
    v924::GraphicsOverrideParameterType::WavesDirectionIncrement,
    v924::GraphicsOverrideParameterType::MidtonesContrast,
    v924::GraphicsOverrideParameterType::HighlightsContrast,
    v924::GraphicsOverrideParameterType::ShadowsContrast,
}};

template <>
inline constexpr std::array<std::string_view, 26> names_v<v924::GraphicsOverrideParameterType>{{
    "skyzenithcolor",
    "skyhorizoncolor",
    "horizonblendmin",
    "horizonblendmax",
    "horizonblendstart",
    "horizonblendmiestart",
    "rayleighstrength",
    "sunmiestrength",
    "moonmiestrength",
    "sunglareshape",
    "chlorophyll",
    "cdom",
    "suspendedsediment",
    "wavesdepth",
    "wavesfrequency",
    "wavesfrequencyscaling",
    "wavesspeed",
    "wavesspeedscaling",
    "wavesshape",
    "wavesoctaves",
    "wavesmix",
    "wavespull",
    "wavesdirectionincrement",
    "midtonescontrast",
    "highlightscontrast",
    "shadowscontrast",
}};

template <>
inline constexpr std::string_view type_name_v<v924::GraphicsOverrideParameterType>{"GraphicsOverrideParameterType"};

template <>
inline constexpr std::array<v944::GraphicsOverrideParameterType, 49> values_v<v944::GraphicsOverrideParameterType>{{
    v944::GraphicsOverrideParameterType::SkyZenithColor,
    v944::GraphicsOverrideParameterType::SkyHorizonColor,
    v944::GraphicsOverrideParameterType::HorizonBlendMin,
    v944::GraphicsOverrideParameterType::HorizonBlendMax,
    v944::GraphicsOverrideParameterType::HorizonBlendStart,
    v944::GraphicsOverrideParameterType::HorizonBlendMieStart,
    v944::GraphicsOverrideParameterType::RayleighStrength,
    v944::GraphicsOverrideParameterType::SunMieStrength,
    v944::GraphicsOverrideParameterType::MoonMieStrength,
    v944::GraphicsOverrideParameterType::SunGlareShape,
    v944::GraphicsOverrideParameterType::Chlorophyll,
    v944::GraphicsOverrideParameterType::CDOM,
    v944::GraphicsOverrideParameterType::SuspendedSediment,
    v944::GraphicsOverrideParameterType::WavesDepth,
    v944::GraphicsOverrideParameterType::WavesFrequency,
    v944::GraphicsOverrideParameterType::WavesFrequencyScaling,
    v944::GraphicsOverrideParameterType::WavesSpeed,
    v944::GraphicsOverrideParameterType::WavesSpeedScaling,
    v944::GraphicsOverrideParameterType::WavesShape,
    v944::GraphicsOverrideParameterType::WavesOctaves,
    v944::GraphicsOverrideParameterType::WavesMix,
    v944::GraphicsOverrideParameterType::WavesPull,
    v944::GraphicsOverrideParameterType::WavesDirectionIncrement,
    v944::GraphicsOverrideParameterType::MidtonesContrast,
    v944::GraphicsOverrideParameterType::HighlightsContrast,
    v944::GraphicsOverrideParameterType::ShadowsContrast,
    v944::GraphicsOverrideParameterType::HighlightsGain,
    v944::GraphicsOverrideParameterType::HighlightsGamma,
    v944::GraphicsOverrideParameterType::HighlightsOffset,
    v944::GraphicsOverrideParameterType::HighlightsSaturation,
    v944::GraphicsOverrideParameterType::MidtonesGain,
    v944::GraphicsOverrideParameterType::MidtonesGamma,
    v944::GraphicsOverrideParameterType::MidtonesOffset,
    v944::GraphicsOverrideParameterType::MidtonesSaturation,
    v944::GraphicsOverrideParameterType::ShadowsGain,
    v944::GraphicsOverrideParameterType::ShadowsGamma,
    v944::GraphicsOverrideParameterType::ShadowsOffset,
    v944::GraphicsOverrideParameterType::ShadowsSaturation,
    v944::GraphicsOverrideParameterType::HighlightsMin,
    v944::GraphicsOverrideParameterType::ShadowsMax,
    v944::GraphicsOverrideParameterType::Temperature,
    v944::GraphicsOverrideParameterType::SunColor,
    v944::GraphicsOverrideParameterType::SunIlluminance,
    v944::GraphicsOverrideParameterType::MoonColor,
    v944::GraphicsOverrideParameterType::MoonIlluminance,
    v944::GraphicsOverrideParameterType::FlashColor,
    v944::GraphicsOverrideParameterType::FlashIlluminance,
    v944::GraphicsOverrideParameterType::AmbientColor,
    v944::GraphicsOverrideParameterType::AmbientIlluminance,
}};

template <>
inline constexpr std::array<std::string_view, 49> names_v<v944::GraphicsOverrideParameterType>{{
    "skyzenithcolor",
    "skyhorizoncolor",
    "horizonblendmin",
    "horizonblendmax",
    "horizonblendstart",
    "horizonblendmiestart",
    "rayleighstrength",
    "sunmiestrength",
    "moonmiestrength",
    "sunglareshape",
    "chlorophyll",
    "cdom",
    "suspendedsediment",
    "wavesdepth",
    "wavesfrequency",
    "wavesfrequencyscaling",
    "wavesspeed",
    "wavesspeedscaling",
    "wavesshape",
    "wavesoctaves",
    "wavesmix",
    "wavespull",
    "wavesdirectionincrement",
    "midtonescontrast",
    "highlightscontrast",
    "shadowscontrast",
    "highlightsgain",
    "highlightsgamma",
    "highlightsoffset",
    "highlightssaturation",
    "midtonesgain",
    "midtonesgamma",
    "midtonesoffset",
    "midtonessaturation",
    "shadowsgain",
    "shadowsgamma",
    "shadowsoffset",
    "shadowssaturation",
    "highlightsmin",
    "shadowsmax",
    "temperature",
    "suncolor",
    "sunilluminance",
    "mooncolor",
    "moonilluminance",
    "flashcolor",
    "flashilluminance",
    "ambientcolor",
    "ambientilluminance",
}};

template <>
inline constexpr std::string_view type_name_v<v944::GraphicsOverrideParameterType>{"GraphicsOverrideParameterType"};

template <>
inline constexpr std::array<v975::GraphicsOverrideParameterType, 52> values_v<v975::GraphicsOverrideParameterType>{{
    v975::GraphicsOverrideParameterType::SkyZenithColor,
    v975::GraphicsOverrideParameterType::SkyHorizonColor,
    v975::GraphicsOverrideParameterType::HorizonBlendMin,
    v975::GraphicsOverrideParameterType::HorizonBlendMax,
    v975::GraphicsOverrideParameterType::HorizonBlendStart,
    v975::GraphicsOverrideParameterType::HorizonBlendMieStart,
    v975::GraphicsOverrideParameterType::RayleighStrength,
    v975::GraphicsOverrideParameterType::SunMieStrength,
    v975::GraphicsOverrideParameterType::MoonMieStrength,
    v975::GraphicsOverrideParameterType::SunGlareShape,
    v975::GraphicsOverrideParameterType::Chlorophyll,
    v975::GraphicsOverrideParameterType::CDOM,
    v975::GraphicsOverrideParameterType::SuspendedSediment,
    v975::GraphicsOverrideParameterType::WavesDepth,
    v975::GraphicsOverrideParameterType::WavesFrequency,
    v975::GraphicsOverrideParameterType::WavesFrequencyScaling,
    v975::GraphicsOverrideParameterType::WavesSpeed,
    v975::GraphicsOverrideParameterType::WavesSpeedScaling,
    v975::GraphicsOverrideParameterType::WavesShape,
    v975::GraphicsOverrideParameterType::WavesOctaves,
    v975::GraphicsOverrideParameterType::WavesMix,
    v975::GraphicsOverrideParameterType::WavesPull,
    v975::GraphicsOverrideParameterType::WavesDirectionIncrement,
    v975::GraphicsOverrideParameterType::MidtonesContrast,
    v975::GraphicsOverrideParameterType::HighlightsContrast,
    v975::GraphicsOverrideParameterType::ShadowsContrast,
    v975::GraphicsOverrideParameterType::HighlightsGain,
    v975::GraphicsOverrideParameterType::HighlightsGamma,
    v975::GraphicsOverrideParameterType::HighlightsOffset,
    v975::GraphicsOverrideParameterType::HighlightsSaturation,
    v975::GraphicsOverrideParameterType::MidtonesGain,
    v975::GraphicsOverrideParameterType::MidtonesGamma,
    v975::GraphicsOverrideParameterType::MidtonesOffset,
    v975::GraphicsOverrideParameterType::MidtonesSaturation,
    v975::GraphicsOverrideParameterType::ShadowsGain,
    v975::GraphicsOverrideParameterType::ShadowsGamma,
    v975::GraphicsOverrideParameterType::ShadowsOffset,
    v975::GraphicsOverrideParameterType::ShadowsSaturation,
    v975::GraphicsOverrideParameterType::HighlightsMin,
    v975::GraphicsOverrideParameterType::ShadowsMax,
    v975::GraphicsOverrideParameterType::Temperature,
    v975::GraphicsOverrideParameterType::SunColor,
    v975::GraphicsOverrideParameterType::SunIlluminance,
    v975::GraphicsOverrideParameterType::MoonColor,
    v975::GraphicsOverrideParameterType::MoonIlluminance,
    v975::GraphicsOverrideParameterType::FlashColor,
    v975::GraphicsOverrideParameterType::FlashIlluminance,
    v975::GraphicsOverrideParameterType::AmbientColor,
    v975::GraphicsOverrideParameterType::AmbientIlluminance,
    v975::GraphicsOverrideParameterType::EmissiveDesaturation,
    v975::GraphicsOverrideParameterType::SkyIntensity,
    v975::GraphicsOverrideParameterType::OrbitalOffsetDegrees,
}};

template <>
inline constexpr std::array<std::string_view, 52> names_v<v975::GraphicsOverrideParameterType>{{
    "skyzenithcolor",
    "skyhorizoncolor",
    "horizonblendmin",
    "horizonblendmax",
    "horizonblendstart",
    "horizonblendmiestart",
    "rayleighstrength",
    "sunmiestrength",
    "moonmiestrength",
    "sunglareshape",
    "chlorophyll",
    "cdom",
    "suspendedsediment",
    "wavesdepth",
    "wavesfrequency",
    "wavesfrequencyscaling",
    "wavesspeed",
    "wavesspeedscaling",
    "wavesshape",
    "wavesoctaves",
    "wavesmix",
    "wavespull",
    "wavesdirectionincrement",
    "midtonescontrast",
    "highlightscontrast",
    "shadowscontrast",
    "highlightsgain",
    "highlightsgamma",
    "highlightsoffset",
    "highlightssaturation",
    "midtonesgain",
    "midtonesgamma",
    "midtonesoffset",
    "midtonessaturation",
    "shadowsgain",
    "shadowsgamma",
    "shadowsoffset",
    "shadowssaturation",
    "highlightsmin",
    "shadowsmax",
    "temperature",
    "suncolor",
    "sunilluminance",
    "mooncolor",
    "moonilluminance",
    "flashcolor",
    "flashilluminance",
    "ambientcolor",
    "ambientilluminance",
    "emissivedesaturation",
    "skyintensity",
    "orbitaloffsetdegrees",
}};

template <>
inline constexpr std::string_view type_name_v<v975::GraphicsOverrideParameterType>{"GraphicsOverrideParameterType"};

}  // namespace detail

namespace detail {

template <>
inline constexpr bool is_reflected_struct_v<v859::GraphicsOverrideParameterPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v859::GraphicsOverrideParameterPacket>{"GraphicsOverrideParameterPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v859::GraphicsOverrideParameterPacket>{{
    "keyframes",
    "biome_id",
    "parameter_id",
    "reset_parameter",
}};

template <>
struct field_accessor<v859::GraphicsOverrideParameterPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.keyframes;
        }
        else if constexpr (I == 1) {
            return value.biome_id;
        }
        else if constexpr (I == 2) {
            return value.parameter_id;
        }
        else {
            return value.reset_parameter;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v898::GraphicsOverrideParameterPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v898::GraphicsOverrideParameterPacket>{"GraphicsOverrideParameterPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v898::GraphicsOverrideParameterPacket>{{
    "keyframes",
    "biome_id",
    "parameter_id",
    "reset_parameter",
}};

template <>
struct field_accessor<v898::GraphicsOverrideParameterPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.keyframes;
        }
        else if constexpr (I == 1) {
            return value.biome_id;
        }
        else if constexpr (I == 2) {
            return value.parameter_id;
        }
        else {
            return value.reset_parameter;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::GraphicsOverrideParameterPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::GraphicsOverrideParameterPacket>{"GraphicsOverrideParameterPacket"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<v924::GraphicsOverrideParameterPacket>{{
    "keyframes",
    "float_value",
    "vec3_value",
    "biome_id",
    "parameter_id",
    "reset_parameter",
}};

template <>
struct field_accessor<v924::GraphicsOverrideParameterPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.keyframes;
        }
        else if constexpr (I == 1) {
            return value.float_value;
        }
        else if constexpr (I == 2) {
            return value.vec3_value;
        }
        else if constexpr (I == 3) {
            return value.biome_id;
        }
        else if constexpr (I == 4) {
            return value.parameter_id;
        }
        else {
            return value.reset_parameter;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::GraphicsOverrideParameterPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::GraphicsOverrideParameterPacket>{"GraphicsOverrideParameterPacket"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<v944::GraphicsOverrideParameterPacket>{{
    "keyframes",
    "float_value",
    "vec3_value",
    "biome_id",
    "parameter_id",
    "reset_parameter",
}};

template <>
struct field_accessor<v944::GraphicsOverrideParameterPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.keyframes;
        }
        else if constexpr (I == 1) {
            return value.float_value;
        }
        else if constexpr (I == 2) {
            return value.vec3_value;
        }
        else if constexpr (I == 3) {
            return value.biome_id;
        }
        else if constexpr (I == 4) {
            return value.parameter_id;
        }
        else {
            return value.reset_parameter;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v975::GraphicsOverrideParameterPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v975::GraphicsOverrideParameterPacket>{"GraphicsOverrideParameterPacket"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<v975::GraphicsOverrideParameterPacket>{{
    "keyframes",
    "float_value",
    "vec3_value",
    "biome_id",
    "parameter_id",
    "reset_parameter",
}};

template <>
struct field_accessor<v975::GraphicsOverrideParameterPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.keyframes;
        }
        else if constexpr (I == 1) {
            return value.float_value;
        }
        else if constexpr (I == 2) {
            return value.vec3_value;
        }
        else if constexpr (I == 3) {
            return value.biome_id;
        }
        else if constexpr (I == 4) {
            return value.parameter_id;
        }
        else {
            return value.reset_parameter;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::GraphicsOverrideParameterPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::GraphicsOverrideParameterPacket>{"GraphicsOverrideParameterPacket"};

template <>
inline constexpr std::array<std::string_view, 7> field_names_v<v1001::GraphicsOverrideParameterPacket>{{
    "keyframes",
    "float_value",
    "vec3_value",
    "biome_id",
    "player_id",
    "parameter_id",
    "reset_parameter",
}};

template <>
struct field_accessor<v1001::GraphicsOverrideParameterPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.keyframes;
        }
        else if constexpr (I == 1) {
            return value.float_value;
        }
        else if constexpr (I == 2) {
            return value.vec3_value;
        }
        else if constexpr (I == 3) {
            return value.biome_id;
        }
        else if constexpr (I == 4) {
            return value.player_id;
        }
        else if constexpr (I == 5) {
            return value.parameter_id;
        }
        else {
            return value.reset_parameter;
        }
    }
};

}  // namespace detail


template <>
struct Serializer<v859::GraphicsOverrideParameterPacket> {
    static void serialize(BinaryWriter &stream, const v859::GraphicsOverrideParameterPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v859::GraphicsOverrideParameterPacket, std::error_code>;
};

template <>
struct Serializer<v898::GraphicsOverrideParameterPacket> {
    static void serialize(BinaryWriter &stream, const v898::GraphicsOverrideParameterPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v898::GraphicsOverrideParameterPacket, std::error_code>;
};

template <>
struct Serializer<v924::GraphicsOverrideParameterPacket> {
    static void serialize(BinaryWriter &stream, const v924::GraphicsOverrideParameterPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::GraphicsOverrideParameterPacket, std::error_code>;
};

template <>
struct Serializer<v944::GraphicsOverrideParameterPacket> {
    static void serialize(BinaryWriter &stream, const v944::GraphicsOverrideParameterPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::GraphicsOverrideParameterPacket, std::error_code>;
};

template <>
struct Serializer<v975::GraphicsOverrideParameterPacket> {
    static void serialize(BinaryWriter &stream, const v975::GraphicsOverrideParameterPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v975::GraphicsOverrideParameterPacket, std::error_code>;
};

template <>
struct Serializer<v1001::GraphicsOverrideParameterPacket> {
    static void serialize(BinaryWriter &stream, const v1001::GraphicsOverrideParameterPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::GraphicsOverrideParameterPacket, std::error_code>;
};
using GraphicsOverrideParameterType = GraphicsOverrideParameterType_<2225>;
using GraphicsOverrideParameterPacket = GraphicsOverrideParameterPacket_<2225>;

}  // namespace bedrock::protocol
