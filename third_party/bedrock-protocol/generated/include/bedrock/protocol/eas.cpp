#include <bedrock/protocol/eas.h>

namespace bedrock::protocol {


void Serializer<Color255RGBA>::serialize(BinaryWriter &stream, const Color255RGBA &value)
{
    stream.write<std::int32_t>(value.r);
    stream.write<std::int32_t>(value.g);
    stream.write<std::int32_t>(value.b);
    stream.write<std::int32_t>(value.a);
}

auto Serializer<Color255RGBA>::deserialize(BinaryReader &stream) -> std::expected<Color255RGBA, std::error_code>
{
    Color255RGBA out;
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.r = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.g = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.b = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.a = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<BoolAttributeOperation>::serialize(BinaryWriter &stream, BoolAttributeOperation value)
{
    stream.write(enum_name(value));
}

auto Serializer<BoolAttributeOperation>::deserialize(BinaryReader &stream) -> std::expected<BoolAttributeOperation, std::error_code>
{
    auto v = stream.read<std::string>();
    if (!v) return std::unexpected(v.error());
    const auto value = enum_cast<BoolAttributeOperation>(*v);
    if (!value) return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
    return *value;
}

void Serializer<FloatAttributeOperation>::serialize(BinaryWriter &stream, FloatAttributeOperation value)
{
    stream.write(enum_name(value));
}

auto Serializer<FloatAttributeOperation>::deserialize(BinaryReader &stream) -> std::expected<FloatAttributeOperation, std::error_code>
{
    auto v = stream.read<std::string>();
    if (!v) return std::unexpected(v.error());
    const auto value = enum_cast<FloatAttributeOperation>(*v);
    if (!value) return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
    return *value;
}

void Serializer<ColorAttributeOperation>::serialize(BinaryWriter &stream, ColorAttributeOperation value)
{
    stream.write(enum_name(value));
}

auto Serializer<ColorAttributeOperation>::deserialize(BinaryReader &stream) -> std::expected<ColorAttributeOperation, std::error_code>
{
    auto v = stream.read<std::string>();
    if (!v) return std::unexpected(v.error());
    const auto value = enum_cast<ColorAttributeOperation>(*v);
    if (!value) return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
    return *value;
}

void Serializer<EasingType>::serialize(BinaryWriter &stream, EasingType value)
{
    stream.write(enum_name(value));
}

auto Serializer<EasingType>::deserialize(BinaryReader &stream) -> std::expected<EasingType, std::error_code>
{
    auto v = stream.read<std::string>();
    if (!v) return std::unexpected(v.error());
    const auto value = enum_cast<EasingType>(*v);
    if (!value) return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
    return *value;
}

void Serializer<v2193::NoiseAlignment>::serialize(BinaryWriter &stream, const v2193::NoiseAlignment &value)
{
    stream.write<std::uint8_t>(value.type);
    stream.writeVarInt<std::uint32_t>(value.value);
}

auto Serializer<v2193::NoiseAlignment>::deserialize(BinaryReader &stream) -> std::expected<v2193::NoiseAlignment, std::error_code>
{
    v2193::NoiseAlignment out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<v2193::NoiseAlignmentType>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.value = static_cast<std::uint32_t>(*v);
    }
    return out;
}

void Serializer<BoolAttributeData>::serialize(BinaryWriter &stream, const BoolAttributeData &value)
{
    stream.write<bool>(value.value);
    Serializer<BoolAttributeOperation>::serialize(stream, value.operation);
}

auto Serializer<BoolAttributeData>::deserialize(BinaryReader &stream) -> std::expected<BoolAttributeData, std::error_code>
{
    BoolAttributeData out;
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.value = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<BoolAttributeOperation>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.operation = *v;
    }
    return out;
}

void Serializer<FloatAttributeData>::serialize(BinaryWriter &stream, const FloatAttributeData &value)
{
    stream.write<float>(value.value);
    Serializer<FloatAttributeOperation>::serialize(stream, value.operation);
    stream.write<bool>(value.constraint_min_value.has_value());
    if (value.constraint_min_value.has_value()) {
        stream.write<float>((*value.constraint_min_value));
    }
    stream.write<bool>(value.constraint_max_value.has_value());
    if (value.constraint_max_value.has_value()) {
        stream.write<float>((*value.constraint_max_value));
    }
}

auto Serializer<FloatAttributeData>::deserialize(BinaryReader &stream) -> std::expected<FloatAttributeData, std::error_code>
{
    FloatAttributeData out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.value = static_cast<float>(*v);
    }
    {
        auto v = Serializer<FloatAttributeOperation>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.operation = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.constraint_min_value = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.constraint_max_value = std::move(staged);
        }
    }
    return out;
}

void Serializer<ColorAttributeData>::serialize(BinaryWriter &stream, const ColorAttributeData &value)
{
    Serializer<Color255RGBA>::serialize(stream, value.value);
    Serializer<ColorAttributeOperation>::serialize(stream, value.operation);
}

auto Serializer<ColorAttributeData>::deserialize(BinaryReader &stream) -> std::expected<ColorAttributeData, std::error_code>
{
    ColorAttributeData out;
    {
        auto v = Serializer<Color255RGBA>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.value = *v;
    }
    {
        auto v = Serializer<ColorAttributeOperation>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.operation = *v;
    }
    return out;
}

void Serializer<v2225::ConstantAttributeData>::serialize(BinaryWriter &stream, const v2225::ConstantAttributeData &value)
{
    stream.writeVarInt<std::uint32_t>((value.attribute).index());
    switch ((value.attribute).index()) {
        case 0: {
            Serializer<BoolAttributeData>::serialize(stream, std::get<0>(value.attribute));
            break;
        }
        case 1: {
            Serializer<FloatAttributeData>::serialize(stream, std::get<1>(value.attribute));
            break;
        }
        case 2: {
            Serializer<ColorAttributeData>::serialize(stream, std::get<2>(value.attribute));
            break;
        }
    }
}

auto Serializer<v2225::ConstantAttributeData>::deserialize(BinaryReader &stream) -> std::expected<v2225::ConstantAttributeData, std::error_code>
{
    v2225::ConstantAttributeData out;
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> alt0{};
                {
                    auto v = Serializer<BoolAttributeData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> alt0{};
                {
                    auto v = Serializer<FloatAttributeData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> alt0{};
                {
                    auto v = Serializer<ColorAttributeData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.attribute = var0;
    }
    return out;
}

void Serializer<v2225::TransitionSettingsData>::serialize(BinaryWriter &stream, const v2225::TransitionSettingsData &value)
{
    stream.writeVarInt<std::uint32_t>(value.total_transition_ticks);
    stream.writeVarInt<std::uint32_t>(value.current_transition_ticks);
    stream.writeVarInt<std::uint32_t>(value.easing);
    stream.write(value.clock_name);
}

auto Serializer<v2225::TransitionSettingsData>::deserialize(BinaryReader &stream) -> std::expected<v2225::TransitionSettingsData, std::error_code>
{
    v2225::TransitionSettingsData out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.total_transition_ticks = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.current_transition_ticks = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.easing = static_cast<EasingType>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.clock_name = *v;
    }
    return out;
}

void Serializer<v2225::TransitionAttributeData>::serialize(BinaryWriter &stream, const v2225::TransitionAttributeData &value)
{
    stream.writeVarInt<std::uint32_t>((value.from_attribute).index());
    switch ((value.from_attribute).index()) {
        case 0: {
            Serializer<BoolAttributeData>::serialize(stream, std::get<0>(value.from_attribute));
            break;
        }
        case 1: {
            Serializer<FloatAttributeData>::serialize(stream, std::get<1>(value.from_attribute));
            break;
        }
        case 2: {
            Serializer<ColorAttributeData>::serialize(stream, std::get<2>(value.from_attribute));
            break;
        }
    }
    stream.writeVarInt<std::uint32_t>((value.to_attribute).index());
    switch ((value.to_attribute).index()) {
        case 0: {
            Serializer<BoolAttributeData>::serialize(stream, std::get<0>(value.to_attribute));
            break;
        }
        case 1: {
            Serializer<FloatAttributeData>::serialize(stream, std::get<1>(value.to_attribute));
            break;
        }
        case 2: {
            Serializer<ColorAttributeData>::serialize(stream, std::get<2>(value.to_attribute));
            break;
        }
    }
    Serializer<v2225::TransitionSettingsData>::serialize(stream, value.settings);
}

auto Serializer<v2225::TransitionAttributeData>::deserialize(BinaryReader &stream) -> std::expected<v2225::TransitionAttributeData, std::error_code>
{
    v2225::TransitionAttributeData out;
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> alt0{};
                {
                    auto v = Serializer<BoolAttributeData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> alt0{};
                {
                    auto v = Serializer<FloatAttributeData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> alt0{};
                {
                    auto v = Serializer<ColorAttributeData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.from_attribute = var0;
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> alt0{};
                {
                    auto v = Serializer<BoolAttributeData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> alt0{};
                {
                    auto v = Serializer<FloatAttributeData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> alt0{};
                {
                    auto v = Serializer<ColorAttributeData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.to_attribute = var0;
    }
    {
        auto v = Serializer<v2225::TransitionSettingsData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.settings = *v;
    }
    return out;
}

void Serializer<v2225::NoiseTransitionSettingsData>::serialize(BinaryWriter &stream, const v2225::NoiseTransitionSettingsData &value)
{
    stream.writeVarInt<std::uint32_t>(value.total_transition_ticks);
    stream.writeVarInt<std::uint32_t>(value.current_transition_ticks);
    stream.writeVarInt<std::uint32_t>(value.easing);
    stream.write(value.clock_name);
    stream.writeVarInt<std::uint32_t>(value.local_transition_ticks);
    stream.write(value.noise_name);
    Serializer<v2193::NoiseAlignment>::serialize(stream, value.noise_alignment);
}

auto Serializer<v2225::NoiseTransitionSettingsData>::deserialize(BinaryReader &stream) -> std::expected<v2225::NoiseTransitionSettingsData, std::error_code>
{
    v2225::NoiseTransitionSettingsData out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.total_transition_ticks = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.current_transition_ticks = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.easing = static_cast<EasingType>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.clock_name = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.local_transition_ticks = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.noise_name = *v;
    }
    {
        auto v = Serializer<v2193::NoiseAlignment>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.noise_alignment = *v;
    }
    return out;
}

void Serializer<v2225::NoiseTransitionAttributeData>::serialize(BinaryWriter &stream, const v2225::NoiseTransitionAttributeData &value)
{
    stream.writeVarInt<std::uint32_t>((value.from_attribute).index());
    switch ((value.from_attribute).index()) {
        case 0: {
            Serializer<BoolAttributeData>::serialize(stream, std::get<0>(value.from_attribute));
            break;
        }
        case 1: {
            Serializer<FloatAttributeData>::serialize(stream, std::get<1>(value.from_attribute));
            break;
        }
        case 2: {
            Serializer<ColorAttributeData>::serialize(stream, std::get<2>(value.from_attribute));
            break;
        }
    }
    stream.writeVarInt<std::uint32_t>((value.to_attribute).index());
    switch ((value.to_attribute).index()) {
        case 0: {
            Serializer<BoolAttributeData>::serialize(stream, std::get<0>(value.to_attribute));
            break;
        }
        case 1: {
            Serializer<FloatAttributeData>::serialize(stream, std::get<1>(value.to_attribute));
            break;
        }
        case 2: {
            Serializer<ColorAttributeData>::serialize(stream, std::get<2>(value.to_attribute));
            break;
        }
    }
    Serializer<v2225::NoiseTransitionSettingsData>::serialize(stream, value.settings);
}

auto Serializer<v2225::NoiseTransitionAttributeData>::deserialize(BinaryReader &stream) -> std::expected<v2225::NoiseTransitionAttributeData, std::error_code>
{
    v2225::NoiseTransitionAttributeData out;
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> alt0{};
                {
                    auto v = Serializer<BoolAttributeData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> alt0{};
                {
                    auto v = Serializer<FloatAttributeData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> alt0{};
                {
                    auto v = Serializer<ColorAttributeData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.from_attribute = var0;
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> alt0{};
                {
                    auto v = Serializer<BoolAttributeData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> alt0{};
                {
                    auto v = Serializer<FloatAttributeData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> alt0{};
                {
                    auto v = Serializer<ColorAttributeData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.to_attribute = var0;
    }
    {
        auto v = Serializer<v2225::NoiseTransitionSettingsData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.settings = *v;
    }
    return out;
}

void Serializer<base::EnvironmentAttributeData>::serialize(BinaryWriter &stream, const base::EnvironmentAttributeData &value)
{
    stream.write(value.name);
    stream.write<bool>(value.from_attribute.has_value());
    if (value.from_attribute.has_value()) {
        stream.writeVarInt<std::uint32_t>(((*value.from_attribute)).index());
        switch (((*value.from_attribute)).index()) {
            case 0: {
                Serializer<BoolAttributeData>::serialize(stream, std::get<0>((*value.from_attribute)));
                break;
            }
            case 1: {
                Serializer<FloatAttributeData>::serialize(stream, std::get<1>((*value.from_attribute)));
                break;
            }
            case 2: {
                Serializer<ColorAttributeData>::serialize(stream, std::get<2>((*value.from_attribute)));
                break;
            }
        }
    }
    stream.writeVarInt<std::uint32_t>((value.attribute).index());
    switch ((value.attribute).index()) {
        case 0: {
            Serializer<BoolAttributeData>::serialize(stream, std::get<0>(value.attribute));
            break;
        }
        case 1: {
            Serializer<FloatAttributeData>::serialize(stream, std::get<1>(value.attribute));
            break;
        }
        case 2: {
            Serializer<ColorAttributeData>::serialize(stream, std::get<2>(value.attribute));
            break;
        }
    }
    stream.write<bool>(value.to_attribute.has_value());
    if (value.to_attribute.has_value()) {
        stream.writeVarInt<std::uint32_t>(((*value.to_attribute)).index());
        switch (((*value.to_attribute)).index()) {
            case 0: {
                Serializer<BoolAttributeData>::serialize(stream, std::get<0>((*value.to_attribute)));
                break;
            }
            case 1: {
                Serializer<FloatAttributeData>::serialize(stream, std::get<1>((*value.to_attribute)));
                break;
            }
            case 2: {
                Serializer<ColorAttributeData>::serialize(stream, std::get<2>((*value.to_attribute)));
                break;
            }
        }
    }
    stream.write<std::uint32_t>(value.current_transition_ticks);
    stream.write<std::uint32_t>(value.total_transition_ticks);
    Serializer<EasingType>::serialize(stream, value.easing);
}

auto Serializer<base::EnvironmentAttributeData>::deserialize(BinaryReader &stream) -> std::expected<base::EnvironmentAttributeData, std::error_code>
{
    base::EnvironmentAttributeData out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData> staged{};
            auto tag0 = stream.readVarInt<std::uint32_t>();
            if (!tag0) return std::unexpected(tag0.error());
            std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData> var0{};
            switch (*tag0) {
                case 0: {
                    std::variant_alternative_t<0, std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> alt0{};
                    {
                        auto v = Serializer<BoolAttributeData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt0 = *v;
                    }
                    var0.emplace<0>(alt0);
                    break;
                }
                case 1: {
                    std::variant_alternative_t<1, std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> alt0{};
                    {
                        auto v = Serializer<FloatAttributeData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt0 = *v;
                    }
                    var0.emplace<1>(alt0);
                    break;
                }
                case 2: {
                    std::variant_alternative_t<2, std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> alt0{};
                    {
                        auto v = Serializer<ColorAttributeData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt0 = *v;
                    }
                    var0.emplace<2>(alt0);
                    break;
                }
                default: {
                    return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
                }
            }
            staged = var0;
            out.from_attribute = std::move(staged);
        }
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> alt0{};
                {
                    auto v = Serializer<BoolAttributeData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> alt0{};
                {
                    auto v = Serializer<FloatAttributeData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> alt0{};
                {
                    auto v = Serializer<ColorAttributeData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.attribute = var0;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData> staged{};
            auto tag0 = stream.readVarInt<std::uint32_t>();
            if (!tag0) return std::unexpected(tag0.error());
            std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData> var0{};
            switch (*tag0) {
                case 0: {
                    std::variant_alternative_t<0, std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> alt0{};
                    {
                        auto v = Serializer<BoolAttributeData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt0 = *v;
                    }
                    var0.emplace<0>(alt0);
                    break;
                }
                case 1: {
                    std::variant_alternative_t<1, std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> alt0{};
                    {
                        auto v = Serializer<FloatAttributeData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt0 = *v;
                    }
                    var0.emplace<1>(alt0);
                    break;
                }
                case 2: {
                    std::variant_alternative_t<2, std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> alt0{};
                    {
                        auto v = Serializer<ColorAttributeData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt0 = *v;
                    }
                    var0.emplace<2>(alt0);
                    break;
                }
                default: {
                    return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
                }
            }
            staged = var0;
            out.to_attribute = std::move(staged);
        }
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.current_transition_ticks = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.total_transition_ticks = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = Serializer<EasingType>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.easing = *v;
    }
    return out;
}

void Serializer<v1001::EnvironmentAttributeData>::serialize(BinaryWriter &stream, const v1001::EnvironmentAttributeData &value)
{
    stream.write(value.name);
    stream.write<bool>(value.from_attribute.has_value());
    if (value.from_attribute.has_value()) {
        stream.writeVarInt<std::uint32_t>(((*value.from_attribute)).index());
        switch (((*value.from_attribute)).index()) {
            case 0: {
                Serializer<BoolAttributeData>::serialize(stream, std::get<0>((*value.from_attribute)));
                break;
            }
            case 1: {
                Serializer<FloatAttributeData>::serialize(stream, std::get<1>((*value.from_attribute)));
                break;
            }
            case 2: {
                Serializer<ColorAttributeData>::serialize(stream, std::get<2>((*value.from_attribute)));
                break;
            }
        }
    }
    stream.writeVarInt<std::uint32_t>((value.attribute).index());
    switch ((value.attribute).index()) {
        case 0: {
            Serializer<BoolAttributeData>::serialize(stream, std::get<0>(value.attribute));
            break;
        }
        case 1: {
            Serializer<FloatAttributeData>::serialize(stream, std::get<1>(value.attribute));
            break;
        }
        case 2: {
            Serializer<ColorAttributeData>::serialize(stream, std::get<2>(value.attribute));
            break;
        }
    }
    stream.write<bool>(value.to_attribute.has_value());
    if (value.to_attribute.has_value()) {
        stream.writeVarInt<std::uint32_t>(((*value.to_attribute)).index());
        switch (((*value.to_attribute)).index()) {
            case 0: {
                Serializer<BoolAttributeData>::serialize(stream, std::get<0>((*value.to_attribute)));
                break;
            }
            case 1: {
                Serializer<FloatAttributeData>::serialize(stream, std::get<1>((*value.to_attribute)));
                break;
            }
            case 2: {
                Serializer<ColorAttributeData>::serialize(stream, std::get<2>((*value.to_attribute)));
                break;
            }
        }
    }
    stream.write<std::uint32_t>(value.current_transition_ticks);
    stream.write<std::uint32_t>(value.total_transition_ticks);
    Serializer<EasingType>::serialize(stream, value.easing);
    stream.write<std::uint32_t>(value.local_transition_ticks);
    stream.write<bool>(value.noise_transition);
}

auto Serializer<v1001::EnvironmentAttributeData>::deserialize(BinaryReader &stream) -> std::expected<v1001::EnvironmentAttributeData, std::error_code>
{
    v1001::EnvironmentAttributeData out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData> staged{};
            auto tag0 = stream.readVarInt<std::uint32_t>();
            if (!tag0) return std::unexpected(tag0.error());
            std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData> var0{};
            switch (*tag0) {
                case 0: {
                    std::variant_alternative_t<0, std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> alt0{};
                    {
                        auto v = Serializer<BoolAttributeData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt0 = *v;
                    }
                    var0.emplace<0>(alt0);
                    break;
                }
                case 1: {
                    std::variant_alternative_t<1, std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> alt0{};
                    {
                        auto v = Serializer<FloatAttributeData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt0 = *v;
                    }
                    var0.emplace<1>(alt0);
                    break;
                }
                case 2: {
                    std::variant_alternative_t<2, std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> alt0{};
                    {
                        auto v = Serializer<ColorAttributeData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt0 = *v;
                    }
                    var0.emplace<2>(alt0);
                    break;
                }
                default: {
                    return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
                }
            }
            staged = var0;
            out.from_attribute = std::move(staged);
        }
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> alt0{};
                {
                    auto v = Serializer<BoolAttributeData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> alt0{};
                {
                    auto v = Serializer<FloatAttributeData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> alt0{};
                {
                    auto v = Serializer<ColorAttributeData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.attribute = var0;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData> staged{};
            auto tag0 = stream.readVarInt<std::uint32_t>();
            if (!tag0) return std::unexpected(tag0.error());
            std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData> var0{};
            switch (*tag0) {
                case 0: {
                    std::variant_alternative_t<0, std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> alt0{};
                    {
                        auto v = Serializer<BoolAttributeData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt0 = *v;
                    }
                    var0.emplace<0>(alt0);
                    break;
                }
                case 1: {
                    std::variant_alternative_t<1, std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> alt0{};
                    {
                        auto v = Serializer<FloatAttributeData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt0 = *v;
                    }
                    var0.emplace<1>(alt0);
                    break;
                }
                case 2: {
                    std::variant_alternative_t<2, std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> alt0{};
                    {
                        auto v = Serializer<ColorAttributeData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt0 = *v;
                    }
                    var0.emplace<2>(alt0);
                    break;
                }
                default: {
                    return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
                }
            }
            staged = var0;
            out.to_attribute = std::move(staged);
        }
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.current_transition_ticks = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.total_transition_ticks = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = Serializer<EasingType>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.easing = *v;
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.local_transition_ticks = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.noise_transition = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v2193::EnvironmentAttributeData>::serialize(BinaryWriter &stream, const v2193::EnvironmentAttributeData &value)
{
    stream.write(value.name);
    stream.write<bool>(value.from_attribute.has_value());
    if (value.from_attribute.has_value()) {
        stream.writeVarInt<std::uint32_t>(((*value.from_attribute)).index());
        switch (((*value.from_attribute)).index()) {
            case 0: {
                Serializer<BoolAttributeData>::serialize(stream, std::get<0>((*value.from_attribute)));
                break;
            }
            case 1: {
                Serializer<FloatAttributeData>::serialize(stream, std::get<1>((*value.from_attribute)));
                break;
            }
            case 2: {
                Serializer<ColorAttributeData>::serialize(stream, std::get<2>((*value.from_attribute)));
                break;
            }
        }
    }
    stream.writeVarInt<std::uint32_t>((value.attribute).index());
    switch ((value.attribute).index()) {
        case 0: {
            Serializer<BoolAttributeData>::serialize(stream, std::get<0>(value.attribute));
            break;
        }
        case 1: {
            Serializer<FloatAttributeData>::serialize(stream, std::get<1>(value.attribute));
            break;
        }
        case 2: {
            Serializer<ColorAttributeData>::serialize(stream, std::get<2>(value.attribute));
            break;
        }
    }
    stream.write<bool>(value.to_attribute.has_value());
    if (value.to_attribute.has_value()) {
        stream.writeVarInt<std::uint32_t>(((*value.to_attribute)).index());
        switch (((*value.to_attribute)).index()) {
            case 0: {
                Serializer<BoolAttributeData>::serialize(stream, std::get<0>((*value.to_attribute)));
                break;
            }
            case 1: {
                Serializer<FloatAttributeData>::serialize(stream, std::get<1>((*value.to_attribute)));
                break;
            }
            case 2: {
                Serializer<ColorAttributeData>::serialize(stream, std::get<2>((*value.to_attribute)));
                break;
            }
        }
    }
    stream.write<std::uint32_t>(value.current_transition_ticks);
    stream.write<std::uint32_t>(value.total_transition_ticks);
    Serializer<EasingType>::serialize(stream, value.easing);
    stream.write<std::uint32_t>(value.local_transition_ticks);
    stream.write<bool>(value.noise_transition);
    Serializer<v2193::NoiseAlignment>::serialize(stream, value.noise_alignment);
}

auto Serializer<v2193::EnvironmentAttributeData>::deserialize(BinaryReader &stream) -> std::expected<v2193::EnvironmentAttributeData, std::error_code>
{
    v2193::EnvironmentAttributeData out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData> staged{};
            auto tag0 = stream.readVarInt<std::uint32_t>();
            if (!tag0) return std::unexpected(tag0.error());
            std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData> var0{};
            switch (*tag0) {
                case 0: {
                    std::variant_alternative_t<0, std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> alt0{};
                    {
                        auto v = Serializer<BoolAttributeData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt0 = *v;
                    }
                    var0.emplace<0>(alt0);
                    break;
                }
                case 1: {
                    std::variant_alternative_t<1, std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> alt0{};
                    {
                        auto v = Serializer<FloatAttributeData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt0 = *v;
                    }
                    var0.emplace<1>(alt0);
                    break;
                }
                case 2: {
                    std::variant_alternative_t<2, std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> alt0{};
                    {
                        auto v = Serializer<ColorAttributeData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt0 = *v;
                    }
                    var0.emplace<2>(alt0);
                    break;
                }
                default: {
                    return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
                }
            }
            staged = var0;
            out.from_attribute = std::move(staged);
        }
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> alt0{};
                {
                    auto v = Serializer<BoolAttributeData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> alt0{};
                {
                    auto v = Serializer<FloatAttributeData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> alt0{};
                {
                    auto v = Serializer<ColorAttributeData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.attribute = var0;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData> staged{};
            auto tag0 = stream.readVarInt<std::uint32_t>();
            if (!tag0) return std::unexpected(tag0.error());
            std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData> var0{};
            switch (*tag0) {
                case 0: {
                    std::variant_alternative_t<0, std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> alt0{};
                    {
                        auto v = Serializer<BoolAttributeData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt0 = *v;
                    }
                    var0.emplace<0>(alt0);
                    break;
                }
                case 1: {
                    std::variant_alternative_t<1, std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> alt0{};
                    {
                        auto v = Serializer<FloatAttributeData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt0 = *v;
                    }
                    var0.emplace<1>(alt0);
                    break;
                }
                case 2: {
                    std::variant_alternative_t<2, std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> alt0{};
                    {
                        auto v = Serializer<ColorAttributeData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt0 = *v;
                    }
                    var0.emplace<2>(alt0);
                    break;
                }
                default: {
                    return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
                }
            }
            staged = var0;
            out.to_attribute = std::move(staged);
        }
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.current_transition_ticks = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.total_transition_ticks = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = Serializer<EasingType>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.easing = *v;
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.local_transition_ticks = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.noise_transition = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<v2193::NoiseAlignment>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.noise_alignment = *v;
    }
    return out;
}

void Serializer<v2225::EnvironmentAttributeData>::serialize(BinaryWriter &stream, const v2225::EnvironmentAttributeData &value)
{
    stream.write(value.name);
    stream.writeVarInt<std::uint32_t>((value.payload).index());
    switch ((value.payload).index()) {
        case 0: {
            Serializer<v2225::ConstantAttributeData>::serialize(stream, std::get<0>(value.payload));
            break;
        }
        case 1: {
            Serializer<v2225::TransitionAttributeData>::serialize(stream, std::get<1>(value.payload));
            break;
        }
        case 2: {
            Serializer<v2225::NoiseTransitionAttributeData>::serialize(stream, std::get<2>(value.payload));
            break;
        }
    }
}

auto Serializer<v2225::EnvironmentAttributeData>::deserialize(BinaryReader &stream) -> std::expected<v2225::EnvironmentAttributeData, std::error_code>
{
    v2225::EnvironmentAttributeData out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v2225::ConstantAttributeData, v2225::TransitionAttributeData, v2225::NoiseTransitionAttributeData> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v2225::ConstantAttributeData, v2225::TransitionAttributeData, v2225::NoiseTransitionAttributeData>> alt0{};
                {
                    auto v = Serializer<v2225::ConstantAttributeData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v2225::ConstantAttributeData, v2225::TransitionAttributeData, v2225::NoiseTransitionAttributeData>> alt0{};
                {
                    auto v = Serializer<v2225::TransitionAttributeData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<v2225::ConstantAttributeData, v2225::TransitionAttributeData, v2225::NoiseTransitionAttributeData>> alt0{};
                {
                    auto v = Serializer<v2225::NoiseTransitionAttributeData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.payload = var0;
    }
    return out;
}

void Serializer<base::AttributeLayerSettings>::serialize(BinaryWriter &stream, const base::AttributeLayerSettings &value)
{
    stream.write<std::int32_t>(value.priority);
    stream.writeVarInt<std::uint32_t>((value.weight).index());
    switch ((value.weight).index()) {
        case 0: {
            stream.write<float>(std::get<0>(value.weight));
            break;
        }
        case 1: {
            stream.write(std::get<1>(value.weight));
            break;
        }
    }
    stream.write<bool>(value.enabled);
    stream.write<bool>(value.transitions_paused);
}

auto Serializer<base::AttributeLayerSettings>::deserialize(BinaryReader &stream) -> std::expected<base::AttributeLayerSettings, std::error_code>
{
    base::AttributeLayerSettings out;
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.priority = static_cast<std::int32_t>(*v);
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<float, std::string> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<float, std::string>> alt0{};
                {
                    auto v = stream.read<float>();
                    if (!v) return std::unexpected(v.error());
                    alt0 = static_cast<float>(*v);
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<float, std::string>> alt0{};
                {
                    auto v = stream.read<std::string>();
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.weight = var0;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.enabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.transitions_paused = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v975::AttributeLayerSettings>::serialize(BinaryWriter &stream, const v975::AttributeLayerSettings &value)
{
    stream.write<std::int32_t>(value.priority);
    stream.write<float>(value.weight);
    stream.write<bool>(value.enabled);
    stream.write<bool>(value.transitions_paused);
}

auto Serializer<v975::AttributeLayerSettings>::deserialize(BinaryReader &stream) -> std::expected<v975::AttributeLayerSettings, std::error_code>
{
    v975::AttributeLayerSettings out;
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.priority = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.weight = static_cast<float>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.enabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.transitions_paused = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<base::AttributeLayerData>::serialize(BinaryWriter &stream, const base::AttributeLayerData &value)
{
    stream.write(value.name);
    stream.writeVarInt<std::int32_t>(value.dimension_id);
    Serializer<base::AttributeLayerSettings>::serialize(stream, value.settings);
    stream.writeVarInt<std::uint32_t>(value.attributes.size());
    for (const auto &e0 : value.attributes) {
        Serializer<base::EnvironmentAttributeData>::serialize(stream, e0);
    }
}

auto Serializer<base::AttributeLayerData>::deserialize(BinaryReader &stream) -> std::expected<base::AttributeLayerData, std::error_code>
{
    base::AttributeLayerData out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.dimension_id = static_cast<DimensionType>(*v);
    }
    {
        auto v = Serializer<base::AttributeLayerSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.settings = *v;
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.attributes.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.attributes.emplace_back();
            auto v = Serializer<base::EnvironmentAttributeData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.attributes.back() = *v;
        }
    }
    return out;
}

void Serializer<v975::AttributeLayerData>::serialize(BinaryWriter &stream, const v975::AttributeLayerData &value)
{
    stream.write(value.name);
    stream.writeVarInt<std::int32_t>(value.dimension_id);
    Serializer<v975::AttributeLayerSettings>::serialize(stream, value.settings);
    stream.writeVarInt<std::uint32_t>(value.attributes.size());
    for (const auto &e0 : value.attributes) {
        Serializer<base::EnvironmentAttributeData>::serialize(stream, e0);
    }
}

auto Serializer<v975::AttributeLayerData>::deserialize(BinaryReader &stream) -> std::expected<v975::AttributeLayerData, std::error_code>
{
    v975::AttributeLayerData out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.dimension_id = static_cast<DimensionType>(*v);
    }
    {
        auto v = Serializer<v975::AttributeLayerSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.settings = *v;
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.attributes.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.attributes.emplace_back();
            auto v = Serializer<base::EnvironmentAttributeData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.attributes.back() = *v;
        }
    }
    return out;
}

void Serializer<v1001::AttributeLayerData>::serialize(BinaryWriter &stream, const v1001::AttributeLayerData &value)
{
    stream.write(value.name);
    stream.write<bool>(value.noise_name.has_value());
    if (value.noise_name.has_value()) {
        stream.write((*value.noise_name));
    }
    stream.writeVarInt<std::int32_t>(value.dimension_id);
    Serializer<v975::AttributeLayerSettings>::serialize(stream, value.settings);
    stream.writeVarInt<std::uint32_t>(value.attributes.size());
    for (const auto &e0 : value.attributes) {
        Serializer<v1001::EnvironmentAttributeData>::serialize(stream, e0);
    }
}

auto Serializer<v1001::AttributeLayerData>::deserialize(BinaryReader &stream) -> std::expected<v1001::AttributeLayerData, std::error_code>
{
    v1001::AttributeLayerData out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::string staged{};
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.noise_name = std::move(staged);
        }
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.dimension_id = static_cast<DimensionType>(*v);
    }
    {
        auto v = Serializer<v975::AttributeLayerSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.settings = *v;
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.attributes.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.attributes.emplace_back();
            auto v = Serializer<v1001::EnvironmentAttributeData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.attributes.back() = *v;
        }
    }
    return out;
}

void Serializer<v2193::AttributeLayerData>::serialize(BinaryWriter &stream, const v2193::AttributeLayerData &value)
{
    stream.write(value.name);
    stream.write<bool>(value.noise_name.has_value());
    if (value.noise_name.has_value()) {
        stream.write((*value.noise_name));
    }
    stream.writeVarInt<std::int32_t>(value.dimension_id);
    Serializer<v975::AttributeLayerSettings>::serialize(stream, value.settings);
    stream.writeVarInt<std::uint32_t>(value.attributes.size());
    for (const auto &e0 : value.attributes) {
        Serializer<v2193::EnvironmentAttributeData>::serialize(stream, e0);
    }
}

auto Serializer<v2193::AttributeLayerData>::deserialize(BinaryReader &stream) -> std::expected<v2193::AttributeLayerData, std::error_code>
{
    v2193::AttributeLayerData out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::string staged{};
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.noise_name = std::move(staged);
        }
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.dimension_id = static_cast<DimensionType>(*v);
    }
    {
        auto v = Serializer<v975::AttributeLayerSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.settings = *v;
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.attributes.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.attributes.emplace_back();
            auto v = Serializer<v2193::EnvironmentAttributeData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.attributes.back() = *v;
        }
    }
    return out;
}

void Serializer<v2225::AttributeLayerData>::serialize(BinaryWriter &stream, const v2225::AttributeLayerData &value)
{
    stream.write(value.name);
    stream.writeVarInt<std::int32_t>(value.dimension_id);
    Serializer<v975::AttributeLayerSettings>::serialize(stream, value.settings);
    stream.writeVarInt<std::uint32_t>(value.attributes.size());
    for (const auto &e0 : value.attributes) {
        Serializer<v2225::EnvironmentAttributeData>::serialize(stream, e0);
    }
}

auto Serializer<v2225::AttributeLayerData>::deserialize(BinaryReader &stream) -> std::expected<v2225::AttributeLayerData, std::error_code>
{
    v2225::AttributeLayerData out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.dimension_id = static_cast<DimensionType>(*v);
    }
    {
        auto v = Serializer<v975::AttributeLayerSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.settings = *v;
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.attributes.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.attributes.emplace_back();
            auto v = Serializer<v2225::EnvironmentAttributeData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.attributes.back() = *v;
        }
    }
    return out;
}

void Serializer<base::UpdateAttributeLayersData>::serialize(BinaryWriter &stream, const base::UpdateAttributeLayersData &value)
{
    stream.writeVarInt<std::uint32_t>(value.attribute_layers.size());
    for (const auto &e0 : value.attribute_layers) {
        Serializer<base::AttributeLayerData>::serialize(stream, e0);
    }
}

auto Serializer<base::UpdateAttributeLayersData>::deserialize(BinaryReader &stream) -> std::expected<base::UpdateAttributeLayersData, std::error_code>
{
    base::UpdateAttributeLayersData out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.attribute_layers.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.attribute_layers.emplace_back();
            auto v = Serializer<base::AttributeLayerData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.attribute_layers.back() = *v;
        }
    }
    return out;
}

void Serializer<v975::UpdateAttributeLayersData>::serialize(BinaryWriter &stream, const v975::UpdateAttributeLayersData &value)
{
    stream.writeVarInt<std::uint32_t>(value.attribute_layers.size());
    for (const auto &e0 : value.attribute_layers) {
        Serializer<v975::AttributeLayerData>::serialize(stream, e0);
    }
}

auto Serializer<v975::UpdateAttributeLayersData>::deserialize(BinaryReader &stream) -> std::expected<v975::UpdateAttributeLayersData, std::error_code>
{
    v975::UpdateAttributeLayersData out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.attribute_layers.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.attribute_layers.emplace_back();
            auto v = Serializer<v975::AttributeLayerData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.attribute_layers.back() = *v;
        }
    }
    return out;
}

void Serializer<v1001::UpdateAttributeLayersData>::serialize(BinaryWriter &stream, const v1001::UpdateAttributeLayersData &value)
{
    stream.writeVarInt<std::uint32_t>(value.attribute_layers.size());
    for (const auto &e0 : value.attribute_layers) {
        Serializer<v1001::AttributeLayerData>::serialize(stream, e0);
    }
}

auto Serializer<v1001::UpdateAttributeLayersData>::deserialize(BinaryReader &stream) -> std::expected<v1001::UpdateAttributeLayersData, std::error_code>
{
    v1001::UpdateAttributeLayersData out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.attribute_layers.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.attribute_layers.emplace_back();
            auto v = Serializer<v1001::AttributeLayerData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.attribute_layers.back() = *v;
        }
    }
    return out;
}

void Serializer<v2193::UpdateAttributeLayersData>::serialize(BinaryWriter &stream, const v2193::UpdateAttributeLayersData &value)
{
    stream.writeVarInt<std::uint32_t>(value.attribute_layers.size());
    for (const auto &e0 : value.attribute_layers) {
        Serializer<v2193::AttributeLayerData>::serialize(stream, e0);
    }
}

auto Serializer<v2193::UpdateAttributeLayersData>::deserialize(BinaryReader &stream) -> std::expected<v2193::UpdateAttributeLayersData, std::error_code>
{
    v2193::UpdateAttributeLayersData out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.attribute_layers.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.attribute_layers.emplace_back();
            auto v = Serializer<v2193::AttributeLayerData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.attribute_layers.back() = *v;
        }
    }
    return out;
}

void Serializer<v2225::UpdateAttributeLayersData>::serialize(BinaryWriter &stream, const v2225::UpdateAttributeLayersData &value)
{
    stream.writeVarInt<std::uint32_t>(value.attribute_layers.size());
    for (const auto &e0 : value.attribute_layers) {
        Serializer<v2225::AttributeLayerData>::serialize(stream, e0);
    }
}

auto Serializer<v2225::UpdateAttributeLayersData>::deserialize(BinaryReader &stream) -> std::expected<v2225::UpdateAttributeLayersData, std::error_code>
{
    v2225::UpdateAttributeLayersData out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.attribute_layers.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.attribute_layers.emplace_back();
            auto v = Serializer<v2225::AttributeLayerData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.attribute_layers.back() = *v;
        }
    }
    return out;
}

void Serializer<base::UpdateAttributeLayerSettingsData>::serialize(BinaryWriter &stream, const base::UpdateAttributeLayerSettingsData &value)
{
    stream.write(value.layer_name);
    stream.writeVarInt<std::int32_t>(value.layer_dimension_id);
    Serializer<base::AttributeLayerSettings>::serialize(stream, value.attribute_layer_settings);
}

auto Serializer<base::UpdateAttributeLayerSettingsData>::deserialize(BinaryReader &stream) -> std::expected<base::UpdateAttributeLayerSettingsData, std::error_code>
{
    base::UpdateAttributeLayerSettingsData out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.layer_name = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.layer_dimension_id = static_cast<DimensionType>(*v);
    }
    {
        auto v = Serializer<base::AttributeLayerSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.attribute_layer_settings = *v;
    }
    return out;
}

void Serializer<v975::UpdateAttributeLayerSettingsData>::serialize(BinaryWriter &stream, const v975::UpdateAttributeLayerSettingsData &value)
{
    stream.write(value.layer_name);
    stream.writeVarInt<std::int32_t>(value.layer_dimension_id);
    Serializer<v975::AttributeLayerSettings>::serialize(stream, value.attribute_layer_settings);
}

auto Serializer<v975::UpdateAttributeLayerSettingsData>::deserialize(BinaryReader &stream) -> std::expected<v975::UpdateAttributeLayerSettingsData, std::error_code>
{
    v975::UpdateAttributeLayerSettingsData out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.layer_name = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.layer_dimension_id = static_cast<DimensionType>(*v);
    }
    {
        auto v = Serializer<v975::AttributeLayerSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.attribute_layer_settings = *v;
    }
    return out;
}

void Serializer<base::UpdateEnvironmentAttributesData>::serialize(BinaryWriter &stream, const base::UpdateEnvironmentAttributesData &value)
{
    stream.write(value.layer_name);
    stream.writeVarInt<std::int32_t>(value.layer_dimension_id);
    stream.writeVarInt<std::uint32_t>(value.attributes.size());
    for (const auto &e0 : value.attributes) {
        Serializer<base::EnvironmentAttributeData>::serialize(stream, e0);
    }
}

auto Serializer<base::UpdateEnvironmentAttributesData>::deserialize(BinaryReader &stream) -> std::expected<base::UpdateEnvironmentAttributesData, std::error_code>
{
    base::UpdateEnvironmentAttributesData out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.layer_name = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.layer_dimension_id = static_cast<DimensionType>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.attributes.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.attributes.emplace_back();
            auto v = Serializer<base::EnvironmentAttributeData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.attributes.back() = *v;
        }
    }
    return out;
}

void Serializer<v1001::UpdateEnvironmentAttributesData>::serialize(BinaryWriter &stream, const v1001::UpdateEnvironmentAttributesData &value)
{
    stream.write(value.layer_name);
    stream.writeVarInt<std::int32_t>(value.layer_dimension_id);
    stream.writeVarInt<std::uint32_t>(value.attributes.size());
    for (const auto &e0 : value.attributes) {
        Serializer<v1001::EnvironmentAttributeData>::serialize(stream, e0);
    }
}

auto Serializer<v1001::UpdateEnvironmentAttributesData>::deserialize(BinaryReader &stream) -> std::expected<v1001::UpdateEnvironmentAttributesData, std::error_code>
{
    v1001::UpdateEnvironmentAttributesData out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.layer_name = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.layer_dimension_id = static_cast<DimensionType>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.attributes.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.attributes.emplace_back();
            auto v = Serializer<v1001::EnvironmentAttributeData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.attributes.back() = *v;
        }
    }
    return out;
}

void Serializer<v2193::UpdateEnvironmentAttributesData>::serialize(BinaryWriter &stream, const v2193::UpdateEnvironmentAttributesData &value)
{
    stream.write(value.layer_name);
    stream.writeVarInt<std::int32_t>(value.layer_dimension_id);
    stream.writeVarInt<std::uint32_t>(value.attributes.size());
    for (const auto &e0 : value.attributes) {
        Serializer<v2193::EnvironmentAttributeData>::serialize(stream, e0);
    }
}

auto Serializer<v2193::UpdateEnvironmentAttributesData>::deserialize(BinaryReader &stream) -> std::expected<v2193::UpdateEnvironmentAttributesData, std::error_code>
{
    v2193::UpdateEnvironmentAttributesData out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.layer_name = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.layer_dimension_id = static_cast<DimensionType>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.attributes.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.attributes.emplace_back();
            auto v = Serializer<v2193::EnvironmentAttributeData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.attributes.back() = *v;
        }
    }
    return out;
}

void Serializer<v2225::UpdateEnvironmentAttributesData>::serialize(BinaryWriter &stream, const v2225::UpdateEnvironmentAttributesData &value)
{
    stream.write(value.layer_name);
    stream.writeVarInt<std::int32_t>(value.layer_dimension_id);
    stream.writeVarInt<std::uint32_t>(value.attributes.size());
    for (const auto &e0 : value.attributes) {
        Serializer<v2225::EnvironmentAttributeData>::serialize(stream, e0);
    }
}

auto Serializer<v2225::UpdateEnvironmentAttributesData>::deserialize(BinaryReader &stream) -> std::expected<v2225::UpdateEnvironmentAttributesData, std::error_code>
{
    v2225::UpdateEnvironmentAttributesData out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.layer_name = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.layer_dimension_id = static_cast<DimensionType>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.attributes.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.attributes.emplace_back();
            auto v = Serializer<v2225::EnvironmentAttributeData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.attributes.back() = *v;
        }
    }
    return out;
}

void Serializer<RemoveEnvironmentAttributesData>::serialize(BinaryWriter &stream, const RemoveEnvironmentAttributesData &value)
{
    stream.write(value.layer_name);
    stream.writeVarInt<std::int32_t>(value.layer_dimension_id);
    stream.writeVarInt<std::uint32_t>(value.attributes.size());
    for (const auto &e0 : value.attributes) {
        stream.write(e0);
    }
}

auto Serializer<RemoveEnvironmentAttributesData>::deserialize(BinaryReader &stream) -> std::expected<RemoveEnvironmentAttributesData, std::error_code>
{
    RemoveEnvironmentAttributesData out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.layer_name = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.layer_dimension_id = static_cast<DimensionType>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.attributes.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.attributes.emplace_back();
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.attributes.back() = *v;
        }
    }
    return out;
}

void Serializer<v944::ClientboundAttributeLayerSyncPacket>::serialize(BinaryWriter &stream, const v944::ClientboundAttributeLayerSyncPacket &value)
{
    stream.writeVarInt<std::uint32_t>((value.data).index());
    switch ((value.data).index()) {
        case 0: {
            Serializer<base::UpdateAttributeLayersData>::serialize(stream, std::get<0>(value.data));
            break;
        }
        case 1: {
            Serializer<base::UpdateAttributeLayerSettingsData>::serialize(stream, std::get<1>(value.data));
            break;
        }
        case 2: {
            Serializer<base::UpdateEnvironmentAttributesData>::serialize(stream, std::get<2>(value.data));
            break;
        }
        case 3: {
            Serializer<RemoveEnvironmentAttributesData>::serialize(stream, std::get<3>(value.data));
            break;
        }
    }
}

auto Serializer<v944::ClientboundAttributeLayerSyncPacket>::deserialize(BinaryReader &stream) -> std::expected<v944::ClientboundAttributeLayerSyncPacket, std::error_code>
{
    v944::ClientboundAttributeLayerSyncPacket out;
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<base::UpdateAttributeLayersData, base::UpdateAttributeLayerSettingsData, base::UpdateEnvironmentAttributesData, RemoveEnvironmentAttributesData> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<base::UpdateAttributeLayersData, base::UpdateAttributeLayerSettingsData, base::UpdateEnvironmentAttributesData, RemoveEnvironmentAttributesData>> alt0{};
                {
                    auto v = Serializer<base::UpdateAttributeLayersData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<base::UpdateAttributeLayersData, base::UpdateAttributeLayerSettingsData, base::UpdateEnvironmentAttributesData, RemoveEnvironmentAttributesData>> alt0{};
                {
                    auto v = Serializer<base::UpdateAttributeLayerSettingsData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<base::UpdateAttributeLayersData, base::UpdateAttributeLayerSettingsData, base::UpdateEnvironmentAttributesData, RemoveEnvironmentAttributesData>> alt0{};
                {
                    auto v = Serializer<base::UpdateEnvironmentAttributesData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<base::UpdateAttributeLayersData, base::UpdateAttributeLayerSettingsData, base::UpdateEnvironmentAttributesData, RemoveEnvironmentAttributesData>> alt0{};
                {
                    auto v = Serializer<RemoveEnvironmentAttributesData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.data = var0;
    }
    return out;
}

void Serializer<v975::ClientboundAttributeLayerSyncPacket>::serialize(BinaryWriter &stream, const v975::ClientboundAttributeLayerSyncPacket &value)
{
    stream.writeVarInt<std::uint32_t>((value.data).index());
    switch ((value.data).index()) {
        case 0: {
            Serializer<v975::UpdateAttributeLayersData>::serialize(stream, std::get<0>(value.data));
            break;
        }
        case 1: {
            Serializer<v975::UpdateAttributeLayerSettingsData>::serialize(stream, std::get<1>(value.data));
            break;
        }
        case 2: {
            Serializer<base::UpdateEnvironmentAttributesData>::serialize(stream, std::get<2>(value.data));
            break;
        }
        case 3: {
            Serializer<RemoveEnvironmentAttributesData>::serialize(stream, std::get<3>(value.data));
            break;
        }
    }
}

auto Serializer<v975::ClientboundAttributeLayerSyncPacket>::deserialize(BinaryReader &stream) -> std::expected<v975::ClientboundAttributeLayerSyncPacket, std::error_code>
{
    v975::ClientboundAttributeLayerSyncPacket out;
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v975::UpdateAttributeLayersData, v975::UpdateAttributeLayerSettingsData, base::UpdateEnvironmentAttributesData, RemoveEnvironmentAttributesData> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v975::UpdateAttributeLayersData, v975::UpdateAttributeLayerSettingsData, base::UpdateEnvironmentAttributesData, RemoveEnvironmentAttributesData>> alt0{};
                {
                    auto v = Serializer<v975::UpdateAttributeLayersData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v975::UpdateAttributeLayersData, v975::UpdateAttributeLayerSettingsData, base::UpdateEnvironmentAttributesData, RemoveEnvironmentAttributesData>> alt0{};
                {
                    auto v = Serializer<v975::UpdateAttributeLayerSettingsData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<v975::UpdateAttributeLayersData, v975::UpdateAttributeLayerSettingsData, base::UpdateEnvironmentAttributesData, RemoveEnvironmentAttributesData>> alt0{};
                {
                    auto v = Serializer<base::UpdateEnvironmentAttributesData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<v975::UpdateAttributeLayersData, v975::UpdateAttributeLayerSettingsData, base::UpdateEnvironmentAttributesData, RemoveEnvironmentAttributesData>> alt0{};
                {
                    auto v = Serializer<RemoveEnvironmentAttributesData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.data = var0;
    }
    return out;
}

void Serializer<v1001::ClientboundAttributeLayerSyncPacket>::serialize(BinaryWriter &stream, const v1001::ClientboundAttributeLayerSyncPacket &value)
{
    stream.writeVarInt<std::uint32_t>((value.data).index());
    switch ((value.data).index()) {
        case 0: {
            Serializer<v1001::UpdateAttributeLayersData>::serialize(stream, std::get<0>(value.data));
            break;
        }
        case 1: {
            Serializer<v975::UpdateAttributeLayerSettingsData>::serialize(stream, std::get<1>(value.data));
            break;
        }
        case 2: {
            Serializer<v1001::UpdateEnvironmentAttributesData>::serialize(stream, std::get<2>(value.data));
            break;
        }
        case 3: {
            Serializer<RemoveEnvironmentAttributesData>::serialize(stream, std::get<3>(value.data));
            break;
        }
    }
}

auto Serializer<v1001::ClientboundAttributeLayerSyncPacket>::deserialize(BinaryReader &stream) -> std::expected<v1001::ClientboundAttributeLayerSyncPacket, std::error_code>
{
    v1001::ClientboundAttributeLayerSyncPacket out;
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v1001::UpdateAttributeLayersData, v975::UpdateAttributeLayerSettingsData, v1001::UpdateEnvironmentAttributesData, RemoveEnvironmentAttributesData> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v1001::UpdateAttributeLayersData, v975::UpdateAttributeLayerSettingsData, v1001::UpdateEnvironmentAttributesData, RemoveEnvironmentAttributesData>> alt0{};
                {
                    auto v = Serializer<v1001::UpdateAttributeLayersData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v1001::UpdateAttributeLayersData, v975::UpdateAttributeLayerSettingsData, v1001::UpdateEnvironmentAttributesData, RemoveEnvironmentAttributesData>> alt0{};
                {
                    auto v = Serializer<v975::UpdateAttributeLayerSettingsData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<v1001::UpdateAttributeLayersData, v975::UpdateAttributeLayerSettingsData, v1001::UpdateEnvironmentAttributesData, RemoveEnvironmentAttributesData>> alt0{};
                {
                    auto v = Serializer<v1001::UpdateEnvironmentAttributesData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<v1001::UpdateAttributeLayersData, v975::UpdateAttributeLayerSettingsData, v1001::UpdateEnvironmentAttributesData, RemoveEnvironmentAttributesData>> alt0{};
                {
                    auto v = Serializer<RemoveEnvironmentAttributesData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.data = var0;
    }
    return out;
}

void Serializer<v2193::ClientboundAttributeLayerSyncPacket>::serialize(BinaryWriter &stream, const v2193::ClientboundAttributeLayerSyncPacket &value)
{
    stream.writeVarInt<std::uint32_t>((value.data).index());
    switch ((value.data).index()) {
        case 0: {
            Serializer<v2193::UpdateAttributeLayersData>::serialize(stream, std::get<0>(value.data));
            break;
        }
        case 1: {
            Serializer<v975::UpdateAttributeLayerSettingsData>::serialize(stream, std::get<1>(value.data));
            break;
        }
        case 2: {
            Serializer<v2193::UpdateEnvironmentAttributesData>::serialize(stream, std::get<2>(value.data));
            break;
        }
        case 3: {
            Serializer<RemoveEnvironmentAttributesData>::serialize(stream, std::get<3>(value.data));
            break;
        }
    }
}

auto Serializer<v2193::ClientboundAttributeLayerSyncPacket>::deserialize(BinaryReader &stream) -> std::expected<v2193::ClientboundAttributeLayerSyncPacket, std::error_code>
{
    v2193::ClientboundAttributeLayerSyncPacket out;
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v2193::UpdateAttributeLayersData, v975::UpdateAttributeLayerSettingsData, v2193::UpdateEnvironmentAttributesData, RemoveEnvironmentAttributesData> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v2193::UpdateAttributeLayersData, v975::UpdateAttributeLayerSettingsData, v2193::UpdateEnvironmentAttributesData, RemoveEnvironmentAttributesData>> alt0{};
                {
                    auto v = Serializer<v2193::UpdateAttributeLayersData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v2193::UpdateAttributeLayersData, v975::UpdateAttributeLayerSettingsData, v2193::UpdateEnvironmentAttributesData, RemoveEnvironmentAttributesData>> alt0{};
                {
                    auto v = Serializer<v975::UpdateAttributeLayerSettingsData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<v2193::UpdateAttributeLayersData, v975::UpdateAttributeLayerSettingsData, v2193::UpdateEnvironmentAttributesData, RemoveEnvironmentAttributesData>> alt0{};
                {
                    auto v = Serializer<v2193::UpdateEnvironmentAttributesData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<v2193::UpdateAttributeLayersData, v975::UpdateAttributeLayerSettingsData, v2193::UpdateEnvironmentAttributesData, RemoveEnvironmentAttributesData>> alt0{};
                {
                    auto v = Serializer<RemoveEnvironmentAttributesData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.data = var0;
    }
    return out;
}

void Serializer<v2225::ClientboundAttributeLayerSyncPacket>::serialize(BinaryWriter &stream, const v2225::ClientboundAttributeLayerSyncPacket &value)
{
    stream.writeVarInt<std::uint32_t>((value.data).index());
    switch ((value.data).index()) {
        case 0: {
            Serializer<v2225::UpdateAttributeLayersData>::serialize(stream, std::get<0>(value.data));
            break;
        }
        case 1: {
            Serializer<v975::UpdateAttributeLayerSettingsData>::serialize(stream, std::get<1>(value.data));
            break;
        }
        case 2: {
            Serializer<v2225::UpdateEnvironmentAttributesData>::serialize(stream, std::get<2>(value.data));
            break;
        }
        case 3: {
            Serializer<RemoveEnvironmentAttributesData>::serialize(stream, std::get<3>(value.data));
            break;
        }
    }
}

auto Serializer<v2225::ClientboundAttributeLayerSyncPacket>::deserialize(BinaryReader &stream) -> std::expected<v2225::ClientboundAttributeLayerSyncPacket, std::error_code>
{
    v2225::ClientboundAttributeLayerSyncPacket out;
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v2225::UpdateAttributeLayersData, v975::UpdateAttributeLayerSettingsData, v2225::UpdateEnvironmentAttributesData, RemoveEnvironmentAttributesData> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v2225::UpdateAttributeLayersData, v975::UpdateAttributeLayerSettingsData, v2225::UpdateEnvironmentAttributesData, RemoveEnvironmentAttributesData>> alt0{};
                {
                    auto v = Serializer<v2225::UpdateAttributeLayersData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v2225::UpdateAttributeLayersData, v975::UpdateAttributeLayerSettingsData, v2225::UpdateEnvironmentAttributesData, RemoveEnvironmentAttributesData>> alt0{};
                {
                    auto v = Serializer<v975::UpdateAttributeLayerSettingsData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<v2225::UpdateAttributeLayersData, v975::UpdateAttributeLayerSettingsData, v2225::UpdateEnvironmentAttributesData, RemoveEnvironmentAttributesData>> alt0{};
                {
                    auto v = Serializer<v2225::UpdateEnvironmentAttributesData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<v2225::UpdateAttributeLayersData, v975::UpdateAttributeLayerSettingsData, v2225::UpdateEnvironmentAttributesData, RemoveEnvironmentAttributesData>> alt0{};
                {
                    auto v = Serializer<RemoveEnvironmentAttributesData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.data = var0;
    }
    return out;
}

void Serializer<AttributeDataVariant>::serialize(BinaryWriter &stream, const AttributeDataVariant &value)
{
    stream.writeVarInt<std::uint32_t>((value).index());
    switch ((value).index()) {
        case 0: {
            Serializer<BoolAttributeData>::serialize(stream, std::get<0>(value));
            break;
        }
        case 1: {
            Serializer<FloatAttributeData>::serialize(stream, std::get<1>(value));
            break;
        }
        case 2: {
            Serializer<ColorAttributeData>::serialize(stream, std::get<2>(value));
            break;
        }
    }
}

auto Serializer<AttributeDataVariant>::deserialize(BinaryReader &stream) -> std::expected<AttributeDataVariant, std::error_code>
{
    AttributeDataVariant out;
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> alt0{};
                {
                    auto v = Serializer<BoolAttributeData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> alt0{};
                {
                    auto v = Serializer<FloatAttributeData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<BoolAttributeData, FloatAttributeData, ColorAttributeData>> alt0{};
                {
                    auto v = Serializer<ColorAttributeData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out = var0;
    }
    return out;
}

void Serializer<v2225::AttributeDataPayload>::serialize(BinaryWriter &stream, const v2225::AttributeDataPayload &value)
{
    stream.writeVarInt<std::uint32_t>((value).index());
    switch ((value).index()) {
        case 0: {
            Serializer<v2225::ConstantAttributeData>::serialize(stream, std::get<0>(value));
            break;
        }
        case 1: {
            Serializer<v2225::TransitionAttributeData>::serialize(stream, std::get<1>(value));
            break;
        }
        case 2: {
            Serializer<v2225::NoiseTransitionAttributeData>::serialize(stream, std::get<2>(value));
            break;
        }
    }
}

auto Serializer<v2225::AttributeDataPayload>::deserialize(BinaryReader &stream) -> std::expected<v2225::AttributeDataPayload, std::error_code>
{
    v2225::AttributeDataPayload out;
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v2225::ConstantAttributeData, v2225::TransitionAttributeData, v2225::NoiseTransitionAttributeData> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v2225::ConstantAttributeData, v2225::TransitionAttributeData, v2225::NoiseTransitionAttributeData>> alt0{};
                {
                    auto v = Serializer<v2225::ConstantAttributeData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v2225::ConstantAttributeData, v2225::TransitionAttributeData, v2225::NoiseTransitionAttributeData>> alt0{};
                {
                    auto v = Serializer<v2225::TransitionAttributeData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<v2225::ConstantAttributeData, v2225::TransitionAttributeData, v2225::NoiseTransitionAttributeData>> alt0{};
                {
                    auto v = Serializer<v2225::NoiseTransitionAttributeData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out = var0;
    }
    return out;
}

}  // namespace bedrock::protocol
