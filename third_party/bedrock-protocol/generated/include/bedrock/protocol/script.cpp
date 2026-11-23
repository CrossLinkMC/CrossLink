#include <bedrock/protocol/script.h>

namespace bedrock::protocol {


void Serializer<ScriptMessagePacket>::serialize(BinaryWriter &stream, const ScriptMessagePacket &value)
{
    stream.write(value.message_id);
    stream.write(value.message_value);
}

auto Serializer<ScriptMessagePacket>::deserialize(BinaryReader &stream) -> std::expected<ScriptMessagePacket, std::error_code>
{
    ScriptMessagePacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.message_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.message_value = *v;
    }
    return out;
}

void Serializer<SimpleEventPacket>::serialize(BinaryWriter &stream, const SimpleEventPacket &value)
{
    stream.write<std::uint16_t>(value.subtype);
}

auto Serializer<SimpleEventPacket>::deserialize(BinaryReader &stream) -> std::expected<SimpleEventPacket, std::error_code>
{
    SimpleEventPacket out;
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.subtype = static_cast<SimpleEventPacket::Subtype>(*v);
    }
    return out;
}

void Serializer<ArrowDataPayload>::serialize(BinaryWriter &stream, const ArrowDataPayload &value)
{
    stream.write<bool>(value.end_location.has_value());
    if (value.end_location.has_value()) {
        Serializer<Vec3>::serialize(stream, (*value.end_location));
    }
    stream.write<bool>(value.arrow_head_length.has_value());
    if (value.arrow_head_length.has_value()) {
        stream.write<float>((*value.arrow_head_length));
    }
    stream.write<bool>(value.arrow_head_radius.has_value());
    if (value.arrow_head_radius.has_value()) {
        stream.write<float>((*value.arrow_head_radius));
    }
    stream.write<bool>(value.num_segments.has_value());
    if (value.num_segments.has_value()) {
        stream.write<std::uint8_t>((*value.num_segments));
    }
}

auto Serializer<ArrowDataPayload>::deserialize(BinaryReader &stream) -> std::expected<ArrowDataPayload, std::error_code>
{
    ArrowDataPayload out;
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec3 staged{};
            auto v = Serializer<Vec3>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.end_location = std::move(staged);
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
            out.arrow_head_length = std::move(staged);
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
            out.arrow_head_radius = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::uint8_t staged{};
            auto v = stream.read<std::uint8_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<std::uint8_t>(*v);
            out.num_segments = std::move(staged);
        }
    }
    return out;
}

void Serializer<base::TextDataPayload>::serialize(BinaryWriter &stream, const base::TextDataPayload &value)
{
    stream.write(value.text);
}

auto Serializer<base::TextDataPayload>::deserialize(BinaryReader &stream) -> std::expected<base::TextDataPayload, std::error_code>
{
    base::TextDataPayload out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.text = *v;
    }
    return out;
}

void Serializer<v975::TextDataPayload>::serialize(BinaryWriter &stream, const v975::TextDataPayload &value)
{
    stream.write(value.text);
    stream.write<bool>(value.use_rotation);
    stream.write<bool>(value.background_color.has_value());
    if (value.background_color.has_value()) {
        stream.write<std::int32_t>((*value.background_color));
    }
    stream.write<bool>(value.depth_test);
    stream.write<bool>(value.show_backface);
    stream.write<bool>(value.show_text_backface);
}

auto Serializer<v975::TextDataPayload>::deserialize(BinaryReader &stream) -> std::expected<v975::TextDataPayload, std::error_code>
{
    v975::TextDataPayload out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.text = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.use_rotation = static_cast<bool>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Color staged{};
            auto v = stream.read<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<Color>(*v);
            out.background_color = std::move(staged);
        }
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.depth_test = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.show_backface = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.show_text_backface = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v2193::TextDataPayload>::serialize(BinaryWriter &stream, const v2193::TextDataPayload &value)
{
    stream.write(value.text);
    stream.write<bool>(value.use_rotation);
    stream.write<bool>(value.background_color.has_value());
    if (value.background_color.has_value()) {
        stream.write<std::int32_t>((*value.background_color));
    }
    stream.write<float>(value.line_gap_height);
    stream.write<bool>(value.depth_test);
    stream.write<bool>(value.show_backface);
    stream.write<bool>(value.show_text_backface);
}

auto Serializer<v2193::TextDataPayload>::deserialize(BinaryReader &stream) -> std::expected<v2193::TextDataPayload, std::error_code>
{
    v2193::TextDataPayload out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.text = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.use_rotation = static_cast<bool>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Color staged{};
            auto v = stream.read<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<Color>(*v);
            out.background_color = std::move(staged);
        }
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.line_gap_height = static_cast<float>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.depth_test = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.show_backface = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.show_text_backface = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<BoxDataPayload>::serialize(BinaryWriter &stream, const BoxDataPayload &value)
{
    Serializer<Vec3>::serialize(stream, value.box_bound);
}

auto Serializer<BoxDataPayload>::deserialize(BinaryReader &stream) -> std::expected<BoxDataPayload, std::error_code>
{
    BoxDataPayload out;
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.box_bound = *v;
    }
    return out;
}

void Serializer<LineDataPayload>::serialize(BinaryWriter &stream, const LineDataPayload &value)
{
    Serializer<Vec3>::serialize(stream, value.end_location);
}

auto Serializer<LineDataPayload>::deserialize(BinaryReader &stream) -> std::expected<LineDataPayload, std::error_code>
{
    LineDataPayload out;
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.end_location = *v;
    }
    return out;
}

void Serializer<SphereDataPayload>::serialize(BinaryWriter &stream, const SphereDataPayload &value)
{
    stream.write<std::uint8_t>(value.num_segments);
}

auto Serializer<SphereDataPayload>::deserialize(BinaryReader &stream) -> std::expected<SphereDataPayload, std::error_code>
{
    SphereDataPayload out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.num_segments = static_cast<std::uint8_t>(*v);
    }
    return out;
}

void Serializer<v1001::CylinderDataPayload>::serialize(BinaryWriter &stream, const v1001::CylinderDataPayload &value)
{
    Serializer<Vec2>::serialize(stream, value.radius_x);
    Serializer<Vec2>::serialize(stream, value.radius_z);
    stream.write<float>(value.height);
    stream.write<std::uint8_t>(value.num_segments);
}

auto Serializer<v1001::CylinderDataPayload>::deserialize(BinaryReader &stream) -> std::expected<v1001::CylinderDataPayload, std::error_code>
{
    v1001::CylinderDataPayload out;
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.radius_x = *v;
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.radius_z = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.height = static_cast<float>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.num_segments = static_cast<std::uint8_t>(*v);
    }
    return out;
}

void Serializer<v1001::PyramidDataPayload>::serialize(BinaryWriter &stream, const v1001::PyramidDataPayload &value)
{
    stream.write<float>(value.width);
    stream.write<bool>(value.depth.has_value());
    if (value.depth.has_value()) {
        stream.write<float>((*value.depth));
    }
    stream.write<float>(value.height);
}

auto Serializer<v1001::PyramidDataPayload>::deserialize(BinaryReader &stream) -> std::expected<v1001::PyramidDataPayload, std::error_code>
{
    v1001::PyramidDataPayload out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.width = static_cast<float>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.depth = std::move(staged);
        }
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.height = static_cast<float>(*v);
    }
    return out;
}

void Serializer<v1001::EllipsoidDataPayload>::serialize(BinaryWriter &stream, const v1001::EllipsoidDataPayload &value)
{
    Serializer<Vec3>::serialize(stream, value.radii);
    stream.write<std::uint8_t>(value.segments_per_axis);
}

auto Serializer<v1001::EllipsoidDataPayload>::deserialize(BinaryReader &stream) -> std::expected<v1001::EllipsoidDataPayload, std::error_code>
{
    v1001::EllipsoidDataPayload out;
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.radii = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.segments_per_axis = static_cast<std::uint8_t>(*v);
    }
    return out;
}

void Serializer<v1001::ConeDataPayload>::serialize(BinaryWriter &stream, const v1001::ConeDataPayload &value)
{
    Serializer<Vec2>::serialize(stream, value.radii);
    stream.write<float>(value.height);
    stream.write<std::uint8_t>(value.num_segments);
}

auto Serializer<v1001::ConeDataPayload>::deserialize(BinaryReader &stream) -> std::expected<v1001::ConeDataPayload, std::error_code>
{
    v1001::ConeDataPayload out;
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.radii = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.height = static_cast<float>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.num_segments = static_cast<std::uint8_t>(*v);
    }
    return out;
}

void Serializer<v859::PrimitiveShapeDataPayload>::serialize(BinaryWriter &stream, const v859::PrimitiveShapeDataPayload &value)
{
    stream.writeVarInt<std::uint64_t>(value.network_id);
    stream.write<bool>(value.shape_type.has_value());
    if (value.shape_type.has_value()) {
        stream.write<std::uint8_t>((*value.shape_type));
    }
    stream.write<bool>(value.location.has_value());
    if (value.location.has_value()) {
        Serializer<Vec3>::serialize(stream, (*value.location));
    }
    stream.write<bool>(value.scale.has_value());
    if (value.scale.has_value()) {
        stream.write<float>((*value.scale));
    }
    stream.write<bool>(value.rotation.has_value());
    if (value.rotation.has_value()) {
        Serializer<Vec3>::serialize(stream, (*value.rotation));
    }
    stream.write<bool>(value.time_left_total_sec.has_value());
    if (value.time_left_total_sec.has_value()) {
        stream.write<float>((*value.time_left_total_sec));
    }
    stream.write<bool>(value.color.has_value());
    if (value.color.has_value()) {
        stream.write<std::int32_t>((*value.color));
    }
    stream.writeVarInt<std::int32_t>(value.dimension_id);
    stream.writeVarInt<std::uint32_t>((value.extra_data_payload).index());
    switch ((value.extra_data_payload).index()) {
        case 0: {
            break;
        }
        case 1: {
            Serializer<ArrowDataPayload>::serialize(stream, std::get<1>(value.extra_data_payload));
            break;
        }
        case 2: {
            Serializer<base::TextDataPayload>::serialize(stream, std::get<2>(value.extra_data_payload));
            break;
        }
        case 3: {
            Serializer<BoxDataPayload>::serialize(stream, std::get<3>(value.extra_data_payload));
            break;
        }
        case 4: {
            Serializer<LineDataPayload>::serialize(stream, std::get<4>(value.extra_data_payload));
            break;
        }
        case 5: {
            Serializer<SphereDataPayload>::serialize(stream, std::get<5>(value.extra_data_payload));
            break;
        }
    }
}

auto Serializer<v859::PrimitiveShapeDataPayload>::deserialize(BinaryReader &stream) -> std::expected<v859::PrimitiveShapeDataPayload, std::error_code>
{
    v859::PrimitiveShapeDataPayload out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.network_id = static_cast<std::uint64_t>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            base::ScriptPrimitiveShapeType staged{};
            auto v = stream.read<std::uint8_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<base::ScriptPrimitiveShapeType>(*v);
            out.shape_type = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec3 staged{};
            auto v = Serializer<Vec3>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.location = std::move(staged);
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
            out.scale = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec3 staged{};
            auto v = Serializer<Vec3>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.rotation = std::move(staged);
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
            out.time_left_total_sec = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Color staged{};
            auto v = stream.read<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<Color>(*v);
            out.color = std::move(staged);
        }
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.dimension_id = static_cast<DimensionType>(*v);
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<std::monostate, ArrowDataPayload, base::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<std::monostate, ArrowDataPayload, base::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload>> alt0{};
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<std::monostate, ArrowDataPayload, base::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload>> alt0{};
                {
                    auto v = Serializer<ArrowDataPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<std::monostate, ArrowDataPayload, base::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload>> alt0{};
                {
                    auto v = Serializer<base::TextDataPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<std::monostate, ArrowDataPayload, base::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload>> alt0{};
                {
                    auto v = Serializer<BoxDataPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            case 4: {
                std::variant_alternative_t<4, std::variant<std::monostate, ArrowDataPayload, base::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload>> alt0{};
                {
                    auto v = Serializer<LineDataPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<4>(alt0);
                break;
            }
            case 5: {
                std::variant_alternative_t<5, std::variant<std::monostate, ArrowDataPayload, base::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload>> alt0{};
                {
                    auto v = Serializer<SphereDataPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<5>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.extra_data_payload = var0;
    }
    return out;
}

void Serializer<v898::PrimitiveShapeDataPayload>::serialize(BinaryWriter &stream, const v898::PrimitiveShapeDataPayload &value)
{
    stream.writeVarInt<std::uint64_t>(value.network_id);
    stream.write<bool>(value.shape_type.has_value());
    if (value.shape_type.has_value()) {
        stream.write<std::uint8_t>((*value.shape_type));
    }
    stream.write<bool>(value.location.has_value());
    if (value.location.has_value()) {
        Serializer<Vec3>::serialize(stream, (*value.location));
    }
    stream.write<bool>(value.scale.has_value());
    if (value.scale.has_value()) {
        stream.write<float>((*value.scale));
    }
    stream.write<bool>(value.rotation.has_value());
    if (value.rotation.has_value()) {
        Serializer<Vec3>::serialize(stream, (*value.rotation));
    }
    stream.write<bool>(value.time_left_total_sec.has_value());
    if (value.time_left_total_sec.has_value()) {
        stream.write<float>((*value.time_left_total_sec));
    }
    stream.write<bool>(value.color.has_value());
    if (value.color.has_value()) {
        stream.write<std::int32_t>((*value.color));
    }
    stream.write<bool>(value.dimension_id.has_value());
    if (value.dimension_id.has_value()) {
        stream.writeVarInt<std::int32_t>((*value.dimension_id));
    }
    stream.writeVarInt<std::uint32_t>((value.extra_data_payload).index());
    switch ((value.extra_data_payload).index()) {
        case 0: {
            break;
        }
        case 1: {
            Serializer<ArrowDataPayload>::serialize(stream, std::get<1>(value.extra_data_payload));
            break;
        }
        case 2: {
            Serializer<base::TextDataPayload>::serialize(stream, std::get<2>(value.extra_data_payload));
            break;
        }
        case 3: {
            Serializer<BoxDataPayload>::serialize(stream, std::get<3>(value.extra_data_payload));
            break;
        }
        case 4: {
            Serializer<LineDataPayload>::serialize(stream, std::get<4>(value.extra_data_payload));
            break;
        }
        case 5: {
            Serializer<SphereDataPayload>::serialize(stream, std::get<5>(value.extra_data_payload));
            break;
        }
    }
}

auto Serializer<v898::PrimitiveShapeDataPayload>::deserialize(BinaryReader &stream) -> std::expected<v898::PrimitiveShapeDataPayload, std::error_code>
{
    v898::PrimitiveShapeDataPayload out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.network_id = static_cast<std::uint64_t>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            base::ScriptPrimitiveShapeType staged{};
            auto v = stream.read<std::uint8_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<base::ScriptPrimitiveShapeType>(*v);
            out.shape_type = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec3 staged{};
            auto v = Serializer<Vec3>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.location = std::move(staged);
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
            out.scale = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec3 staged{};
            auto v = Serializer<Vec3>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.rotation = std::move(staged);
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
            out.time_left_total_sec = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Color staged{};
            auto v = stream.read<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<Color>(*v);
            out.color = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            DimensionType staged{};
            auto v = stream.readVarInt<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<DimensionType>(*v);
            out.dimension_id = std::move(staged);
        }
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<std::monostate, ArrowDataPayload, base::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<std::monostate, ArrowDataPayload, base::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload>> alt0{};
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<std::monostate, ArrowDataPayload, base::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload>> alt0{};
                {
                    auto v = Serializer<ArrowDataPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<std::monostate, ArrowDataPayload, base::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload>> alt0{};
                {
                    auto v = Serializer<base::TextDataPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<std::monostate, ArrowDataPayload, base::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload>> alt0{};
                {
                    auto v = Serializer<BoxDataPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            case 4: {
                std::variant_alternative_t<4, std::variant<std::monostate, ArrowDataPayload, base::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload>> alt0{};
                {
                    auto v = Serializer<LineDataPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<4>(alt0);
                break;
            }
            case 5: {
                std::variant_alternative_t<5, std::variant<std::monostate, ArrowDataPayload, base::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload>> alt0{};
                {
                    auto v = Serializer<SphereDataPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<5>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.extra_data_payload = var0;
    }
    return out;
}

void Serializer<v924::PrimitiveShapeDataPayload>::serialize(BinaryWriter &stream, const v924::PrimitiveShapeDataPayload &value)
{
    stream.writeVarInt<std::uint64_t>(value.network_id);
    stream.write<bool>(value.shape_type.has_value());
    if (value.shape_type.has_value()) {
        stream.write<std::uint8_t>((*value.shape_type));
    }
    stream.write<bool>(value.location.has_value());
    if (value.location.has_value()) {
        Serializer<Vec3>::serialize(stream, (*value.location));
    }
    stream.write<bool>(value.scale.has_value());
    if (value.scale.has_value()) {
        stream.write<float>((*value.scale));
    }
    stream.write<bool>(value.rotation.has_value());
    if (value.rotation.has_value()) {
        Serializer<Vec3>::serialize(stream, (*value.rotation));
    }
    stream.write<bool>(value.time_left_total_sec.has_value());
    if (value.time_left_total_sec.has_value()) {
        stream.write<float>((*value.time_left_total_sec));
    }
    stream.write<bool>(value.color.has_value());
    if (value.color.has_value()) {
        stream.write<std::int32_t>((*value.color));
    }
    stream.write<bool>(value.dimension_id.has_value());
    if (value.dimension_id.has_value()) {
        stream.writeVarInt<std::int32_t>((*value.dimension_id));
    }
    stream.write<bool>(value.attached_to_id.has_value());
    if (value.attached_to_id.has_value()) {
        stream.writeVarInt<std::uint64_t>((*value.attached_to_id));
    }
    stream.writeVarInt<std::uint32_t>((value.extra_data_payload).index());
    switch ((value.extra_data_payload).index()) {
        case 0: {
            break;
        }
        case 1: {
            Serializer<ArrowDataPayload>::serialize(stream, std::get<1>(value.extra_data_payload));
            break;
        }
        case 2: {
            Serializer<base::TextDataPayload>::serialize(stream, std::get<2>(value.extra_data_payload));
            break;
        }
        case 3: {
            Serializer<BoxDataPayload>::serialize(stream, std::get<3>(value.extra_data_payload));
            break;
        }
        case 4: {
            Serializer<LineDataPayload>::serialize(stream, std::get<4>(value.extra_data_payload));
            break;
        }
        case 5: {
            Serializer<SphereDataPayload>::serialize(stream, std::get<5>(value.extra_data_payload));
            break;
        }
    }
}

auto Serializer<v924::PrimitiveShapeDataPayload>::deserialize(BinaryReader &stream) -> std::expected<v924::PrimitiveShapeDataPayload, std::error_code>
{
    v924::PrimitiveShapeDataPayload out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.network_id = static_cast<std::uint64_t>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            base::ScriptPrimitiveShapeType staged{};
            auto v = stream.read<std::uint8_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<base::ScriptPrimitiveShapeType>(*v);
            out.shape_type = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec3 staged{};
            auto v = Serializer<Vec3>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.location = std::move(staged);
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
            out.scale = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec3 staged{};
            auto v = Serializer<Vec3>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.rotation = std::move(staged);
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
            out.time_left_total_sec = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Color staged{};
            auto v = stream.read<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<Color>(*v);
            out.color = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            DimensionType staged{};
            auto v = stream.readVarInt<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<DimensionType>(*v);
            out.dimension_id = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            ActorRuntimeID staged{};
            auto v = stream.readVarInt<std::uint64_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<ActorRuntimeID>(*v);
            out.attached_to_id = std::move(staged);
        }
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<std::monostate, ArrowDataPayload, base::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<std::monostate, ArrowDataPayload, base::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload>> alt0{};
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<std::monostate, ArrowDataPayload, base::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload>> alt0{};
                {
                    auto v = Serializer<ArrowDataPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<std::monostate, ArrowDataPayload, base::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload>> alt0{};
                {
                    auto v = Serializer<base::TextDataPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<std::monostate, ArrowDataPayload, base::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload>> alt0{};
                {
                    auto v = Serializer<BoxDataPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            case 4: {
                std::variant_alternative_t<4, std::variant<std::monostate, ArrowDataPayload, base::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload>> alt0{};
                {
                    auto v = Serializer<LineDataPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<4>(alt0);
                break;
            }
            case 5: {
                std::variant_alternative_t<5, std::variant<std::monostate, ArrowDataPayload, base::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload>> alt0{};
                {
                    auto v = Serializer<SphereDataPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<5>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.extra_data_payload = var0;
    }
    return out;
}

void Serializer<v975::PrimitiveShapeDataPayload>::serialize(BinaryWriter &stream, const v975::PrimitiveShapeDataPayload &value)
{
    stream.writeVarInt<std::uint64_t>(value.network_id);
    stream.write<bool>(value.shape_type.has_value());
    if (value.shape_type.has_value()) {
        stream.write<std::uint8_t>((*value.shape_type));
    }
    stream.write<bool>(value.location.has_value());
    if (value.location.has_value()) {
        Serializer<Vec3>::serialize(stream, (*value.location));
    }
    stream.write<bool>(value.scale.has_value());
    if (value.scale.has_value()) {
        stream.write<float>((*value.scale));
    }
    stream.write<bool>(value.rotation.has_value());
    if (value.rotation.has_value()) {
        Serializer<Vec3>::serialize(stream, (*value.rotation));
    }
    stream.write<bool>(value.time_left_total_sec.has_value());
    if (value.time_left_total_sec.has_value()) {
        stream.write<float>((*value.time_left_total_sec));
    }
    stream.write<bool>(value.max_render_distance.has_value());
    if (value.max_render_distance.has_value()) {
        stream.write<float>((*value.max_render_distance));
    }
    stream.write<bool>(value.color.has_value());
    if (value.color.has_value()) {
        stream.write<std::int32_t>((*value.color));
    }
    stream.write<bool>(value.dimension_id.has_value());
    if (value.dimension_id.has_value()) {
        stream.writeVarInt<std::int32_t>((*value.dimension_id));
    }
    stream.write<bool>(value.attached_to_id.has_value());
    if (value.attached_to_id.has_value()) {
        stream.writeVarInt<std::int64_t>((*value.attached_to_id));
    }
    stream.writeVarInt<std::uint32_t>((value.extra_data_payload).index());
    switch ((value.extra_data_payload).index()) {
        case 0: {
            break;
        }
        case 1: {
            Serializer<ArrowDataPayload>::serialize(stream, std::get<1>(value.extra_data_payload));
            break;
        }
        case 2: {
            Serializer<v975::TextDataPayload>::serialize(stream, std::get<2>(value.extra_data_payload));
            break;
        }
        case 3: {
            Serializer<BoxDataPayload>::serialize(stream, std::get<3>(value.extra_data_payload));
            break;
        }
        case 4: {
            Serializer<LineDataPayload>::serialize(stream, std::get<4>(value.extra_data_payload));
            break;
        }
        case 5: {
            Serializer<SphereDataPayload>::serialize(stream, std::get<5>(value.extra_data_payload));
            break;
        }
    }
}

auto Serializer<v975::PrimitiveShapeDataPayload>::deserialize(BinaryReader &stream) -> std::expected<v975::PrimitiveShapeDataPayload, std::error_code>
{
    v975::PrimitiveShapeDataPayload out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.network_id = static_cast<std::uint64_t>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            base::ScriptPrimitiveShapeType staged{};
            auto v = stream.read<std::uint8_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<base::ScriptPrimitiveShapeType>(*v);
            out.shape_type = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec3 staged{};
            auto v = Serializer<Vec3>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.location = std::move(staged);
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
            out.scale = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec3 staged{};
            auto v = Serializer<Vec3>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.rotation = std::move(staged);
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
            out.time_left_total_sec = std::move(staged);
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
            out.max_render_distance = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Color staged{};
            auto v = stream.read<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<Color>(*v);
            out.color = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            DimensionType staged{};
            auto v = stream.readVarInt<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<DimensionType>(*v);
            out.dimension_id = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            ActorUniqueID staged{};
            auto v = stream.readVarInt<std::int64_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<ActorUniqueID>(*v);
            out.attached_to_id = std::move(staged);
        }
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<std::monostate, ArrowDataPayload, v975::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<std::monostate, ArrowDataPayload, v975::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload>> alt0{};
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<std::monostate, ArrowDataPayload, v975::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload>> alt0{};
                {
                    auto v = Serializer<ArrowDataPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<std::monostate, ArrowDataPayload, v975::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload>> alt0{};
                {
                    auto v = Serializer<v975::TextDataPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<std::monostate, ArrowDataPayload, v975::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload>> alt0{};
                {
                    auto v = Serializer<BoxDataPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            case 4: {
                std::variant_alternative_t<4, std::variant<std::monostate, ArrowDataPayload, v975::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload>> alt0{};
                {
                    auto v = Serializer<LineDataPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<4>(alt0);
                break;
            }
            case 5: {
                std::variant_alternative_t<5, std::variant<std::monostate, ArrowDataPayload, v975::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload>> alt0{};
                {
                    auto v = Serializer<SphereDataPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<5>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.extra_data_payload = var0;
    }
    return out;
}

void Serializer<v1001::PrimitiveShapeDataPayload>::serialize(BinaryWriter &stream, const v1001::PrimitiveShapeDataPayload &value)
{
    stream.writeVarInt<std::uint64_t>(value.network_id);
    stream.write<bool>(value.shape_type.has_value());
    if (value.shape_type.has_value()) {
        stream.write<std::uint8_t>((*value.shape_type));
    }
    stream.write<bool>(value.location.has_value());
    if (value.location.has_value()) {
        Serializer<Vec3>::serialize(stream, (*value.location));
    }
    stream.write<bool>(value.scale.has_value());
    if (value.scale.has_value()) {
        stream.write<float>((*value.scale));
    }
    stream.write<bool>(value.rotation.has_value());
    if (value.rotation.has_value()) {
        Serializer<Vec3>::serialize(stream, (*value.rotation));
    }
    stream.write<bool>(value.time_left_total_sec.has_value());
    if (value.time_left_total_sec.has_value()) {
        stream.write<float>((*value.time_left_total_sec));
    }
    stream.write<bool>(value.max_render_distance.has_value());
    if (value.max_render_distance.has_value()) {
        stream.write<float>((*value.max_render_distance));
    }
    stream.write<bool>(value.color.has_value());
    if (value.color.has_value()) {
        stream.write<std::int32_t>((*value.color));
    }
    stream.write<bool>(value.dimension_id.has_value());
    if (value.dimension_id.has_value()) {
        stream.writeVarInt<std::int32_t>((*value.dimension_id));
    }
    stream.write<bool>(value.attached_to_id.has_value());
    if (value.attached_to_id.has_value()) {
        stream.writeVarInt<std::int64_t>((*value.attached_to_id));
    }
    stream.writeVarInt<std::uint32_t>((value.extra_data_payload).index());
    switch ((value.extra_data_payload).index()) {
        case 0: {
            break;
        }
        case 1: {
            Serializer<ArrowDataPayload>::serialize(stream, std::get<1>(value.extra_data_payload));
            break;
        }
        case 2: {
            Serializer<v975::TextDataPayload>::serialize(stream, std::get<2>(value.extra_data_payload));
            break;
        }
        case 3: {
            Serializer<BoxDataPayload>::serialize(stream, std::get<3>(value.extra_data_payload));
            break;
        }
        case 4: {
            Serializer<LineDataPayload>::serialize(stream, std::get<4>(value.extra_data_payload));
            break;
        }
        case 5: {
            Serializer<SphereDataPayload>::serialize(stream, std::get<5>(value.extra_data_payload));
            break;
        }
        case 6: {
            Serializer<v1001::CylinderDataPayload>::serialize(stream, std::get<6>(value.extra_data_payload));
            break;
        }
        case 7: {
            Serializer<v1001::PyramidDataPayload>::serialize(stream, std::get<7>(value.extra_data_payload));
            break;
        }
        case 8: {
            Serializer<v1001::EllipsoidDataPayload>::serialize(stream, std::get<8>(value.extra_data_payload));
            break;
        }
        case 9: {
            Serializer<v1001::ConeDataPayload>::serialize(stream, std::get<9>(value.extra_data_payload));
            break;
        }
    }
}

auto Serializer<v1001::PrimitiveShapeDataPayload>::deserialize(BinaryReader &stream) -> std::expected<v1001::PrimitiveShapeDataPayload, std::error_code>
{
    v1001::PrimitiveShapeDataPayload out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.network_id = static_cast<std::uint64_t>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v1001::ScriptPrimitiveShapeType staged{};
            auto v = stream.read<std::uint8_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<v1001::ScriptPrimitiveShapeType>(*v);
            out.shape_type = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec3 staged{};
            auto v = Serializer<Vec3>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.location = std::move(staged);
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
            out.scale = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec3 staged{};
            auto v = Serializer<Vec3>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.rotation = std::move(staged);
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
            out.time_left_total_sec = std::move(staged);
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
            out.max_render_distance = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Color staged{};
            auto v = stream.read<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<Color>(*v);
            out.color = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            DimensionType staged{};
            auto v = stream.readVarInt<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<DimensionType>(*v);
            out.dimension_id = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            ActorUniqueID staged{};
            auto v = stream.readVarInt<std::int64_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<ActorUniqueID>(*v);
            out.attached_to_id = std::move(staged);
        }
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<std::monostate, ArrowDataPayload, v975::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload, v1001::CylinderDataPayload, v1001::PyramidDataPayload, v1001::EllipsoidDataPayload, v1001::ConeDataPayload> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<std::monostate, ArrowDataPayload, v975::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload, v1001::CylinderDataPayload, v1001::PyramidDataPayload, v1001::EllipsoidDataPayload, v1001::ConeDataPayload>> alt0{};
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<std::monostate, ArrowDataPayload, v975::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload, v1001::CylinderDataPayload, v1001::PyramidDataPayload, v1001::EllipsoidDataPayload, v1001::ConeDataPayload>> alt0{};
                {
                    auto v = Serializer<ArrowDataPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<std::monostate, ArrowDataPayload, v975::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload, v1001::CylinderDataPayload, v1001::PyramidDataPayload, v1001::EllipsoidDataPayload, v1001::ConeDataPayload>> alt0{};
                {
                    auto v = Serializer<v975::TextDataPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<std::monostate, ArrowDataPayload, v975::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload, v1001::CylinderDataPayload, v1001::PyramidDataPayload, v1001::EllipsoidDataPayload, v1001::ConeDataPayload>> alt0{};
                {
                    auto v = Serializer<BoxDataPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            case 4: {
                std::variant_alternative_t<4, std::variant<std::monostate, ArrowDataPayload, v975::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload, v1001::CylinderDataPayload, v1001::PyramidDataPayload, v1001::EllipsoidDataPayload, v1001::ConeDataPayload>> alt0{};
                {
                    auto v = Serializer<LineDataPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<4>(alt0);
                break;
            }
            case 5: {
                std::variant_alternative_t<5, std::variant<std::monostate, ArrowDataPayload, v975::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload, v1001::CylinderDataPayload, v1001::PyramidDataPayload, v1001::EllipsoidDataPayload, v1001::ConeDataPayload>> alt0{};
                {
                    auto v = Serializer<SphereDataPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<5>(alt0);
                break;
            }
            case 6: {
                std::variant_alternative_t<6, std::variant<std::monostate, ArrowDataPayload, v975::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload, v1001::CylinderDataPayload, v1001::PyramidDataPayload, v1001::EllipsoidDataPayload, v1001::ConeDataPayload>> alt0{};
                {
                    auto v = Serializer<v1001::CylinderDataPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<6>(alt0);
                break;
            }
            case 7: {
                std::variant_alternative_t<7, std::variant<std::monostate, ArrowDataPayload, v975::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload, v1001::CylinderDataPayload, v1001::PyramidDataPayload, v1001::EllipsoidDataPayload, v1001::ConeDataPayload>> alt0{};
                {
                    auto v = Serializer<v1001::PyramidDataPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<7>(alt0);
                break;
            }
            case 8: {
                std::variant_alternative_t<8, std::variant<std::monostate, ArrowDataPayload, v975::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload, v1001::CylinderDataPayload, v1001::PyramidDataPayload, v1001::EllipsoidDataPayload, v1001::ConeDataPayload>> alt0{};
                {
                    auto v = Serializer<v1001::EllipsoidDataPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<8>(alt0);
                break;
            }
            case 9: {
                std::variant_alternative_t<9, std::variant<std::monostate, ArrowDataPayload, v975::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload, v1001::CylinderDataPayload, v1001::PyramidDataPayload, v1001::EllipsoidDataPayload, v1001::ConeDataPayload>> alt0{};
                {
                    auto v = Serializer<v1001::ConeDataPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<9>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.extra_data_payload = var0;
    }
    return out;
}

void Serializer<v2193::PrimitiveShapeDataPayload>::serialize(BinaryWriter &stream, const v2193::PrimitiveShapeDataPayload &value)
{
    stream.writeVarInt<std::uint64_t>(value.network_id);
    stream.write<bool>(value.shape_type.has_value());
    if (value.shape_type.has_value()) {
        stream.write<std::uint8_t>((*value.shape_type));
    }
    stream.write<bool>(value.location.has_value());
    if (value.location.has_value()) {
        Serializer<Vec3>::serialize(stream, (*value.location));
    }
    stream.write<bool>(value.scale.has_value());
    if (value.scale.has_value()) {
        stream.write<float>((*value.scale));
    }
    stream.write<bool>(value.rotation.has_value());
    if (value.rotation.has_value()) {
        Serializer<Vec3>::serialize(stream, (*value.rotation));
    }
    stream.write<bool>(value.time_left_total_sec.has_value());
    if (value.time_left_total_sec.has_value()) {
        stream.write<float>((*value.time_left_total_sec));
    }
    stream.write<bool>(value.max_render_distance.has_value());
    if (value.max_render_distance.has_value()) {
        stream.write<float>((*value.max_render_distance));
    }
    stream.write<bool>(value.color.has_value());
    if (value.color.has_value()) {
        stream.write<std::int32_t>((*value.color));
    }
    stream.write<bool>(value.dimension_id.has_value());
    if (value.dimension_id.has_value()) {
        stream.writeVarInt<std::int32_t>((*value.dimension_id));
    }
    stream.write<bool>(value.attached_to_id.has_value());
    if (value.attached_to_id.has_value()) {
        stream.writeVarInt<std::int64_t>((*value.attached_to_id));
    }
    stream.writeVarInt<std::uint32_t>((value.extra_data_payload).index());
    switch ((value.extra_data_payload).index()) {
        case 0: {
            break;
        }
        case 1: {
            Serializer<ArrowDataPayload>::serialize(stream, std::get<1>(value.extra_data_payload));
            break;
        }
        case 2: {
            Serializer<v2193::TextDataPayload>::serialize(stream, std::get<2>(value.extra_data_payload));
            break;
        }
        case 3: {
            Serializer<BoxDataPayload>::serialize(stream, std::get<3>(value.extra_data_payload));
            break;
        }
        case 4: {
            Serializer<LineDataPayload>::serialize(stream, std::get<4>(value.extra_data_payload));
            break;
        }
        case 5: {
            Serializer<SphereDataPayload>::serialize(stream, std::get<5>(value.extra_data_payload));
            break;
        }
        case 6: {
            Serializer<v1001::CylinderDataPayload>::serialize(stream, std::get<6>(value.extra_data_payload));
            break;
        }
        case 7: {
            Serializer<v1001::PyramidDataPayload>::serialize(stream, std::get<7>(value.extra_data_payload));
            break;
        }
        case 8: {
            Serializer<v1001::EllipsoidDataPayload>::serialize(stream, std::get<8>(value.extra_data_payload));
            break;
        }
        case 9: {
            Serializer<v1001::ConeDataPayload>::serialize(stream, std::get<9>(value.extra_data_payload));
            break;
        }
    }
}

auto Serializer<v2193::PrimitiveShapeDataPayload>::deserialize(BinaryReader &stream) -> std::expected<v2193::PrimitiveShapeDataPayload, std::error_code>
{
    v2193::PrimitiveShapeDataPayload out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.network_id = static_cast<std::uint64_t>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v1001::ScriptPrimitiveShapeType staged{};
            auto v = stream.read<std::uint8_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<v1001::ScriptPrimitiveShapeType>(*v);
            out.shape_type = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec3 staged{};
            auto v = Serializer<Vec3>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.location = std::move(staged);
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
            out.scale = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec3 staged{};
            auto v = Serializer<Vec3>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.rotation = std::move(staged);
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
            out.time_left_total_sec = std::move(staged);
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
            out.max_render_distance = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Color staged{};
            auto v = stream.read<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<Color>(*v);
            out.color = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            DimensionType staged{};
            auto v = stream.readVarInt<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<DimensionType>(*v);
            out.dimension_id = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            ActorUniqueID staged{};
            auto v = stream.readVarInt<std::int64_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<ActorUniqueID>(*v);
            out.attached_to_id = std::move(staged);
        }
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<std::monostate, ArrowDataPayload, v2193::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload, v1001::CylinderDataPayload, v1001::PyramidDataPayload, v1001::EllipsoidDataPayload, v1001::ConeDataPayload> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<std::monostate, ArrowDataPayload, v2193::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload, v1001::CylinderDataPayload, v1001::PyramidDataPayload, v1001::EllipsoidDataPayload, v1001::ConeDataPayload>> alt0{};
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<std::monostate, ArrowDataPayload, v2193::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload, v1001::CylinderDataPayload, v1001::PyramidDataPayload, v1001::EllipsoidDataPayload, v1001::ConeDataPayload>> alt0{};
                {
                    auto v = Serializer<ArrowDataPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<std::monostate, ArrowDataPayload, v2193::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload, v1001::CylinderDataPayload, v1001::PyramidDataPayload, v1001::EllipsoidDataPayload, v1001::ConeDataPayload>> alt0{};
                {
                    auto v = Serializer<v2193::TextDataPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<std::monostate, ArrowDataPayload, v2193::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload, v1001::CylinderDataPayload, v1001::PyramidDataPayload, v1001::EllipsoidDataPayload, v1001::ConeDataPayload>> alt0{};
                {
                    auto v = Serializer<BoxDataPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            case 4: {
                std::variant_alternative_t<4, std::variant<std::monostate, ArrowDataPayload, v2193::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload, v1001::CylinderDataPayload, v1001::PyramidDataPayload, v1001::EllipsoidDataPayload, v1001::ConeDataPayload>> alt0{};
                {
                    auto v = Serializer<LineDataPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<4>(alt0);
                break;
            }
            case 5: {
                std::variant_alternative_t<5, std::variant<std::monostate, ArrowDataPayload, v2193::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload, v1001::CylinderDataPayload, v1001::PyramidDataPayload, v1001::EllipsoidDataPayload, v1001::ConeDataPayload>> alt0{};
                {
                    auto v = Serializer<SphereDataPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<5>(alt0);
                break;
            }
            case 6: {
                std::variant_alternative_t<6, std::variant<std::monostate, ArrowDataPayload, v2193::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload, v1001::CylinderDataPayload, v1001::PyramidDataPayload, v1001::EllipsoidDataPayload, v1001::ConeDataPayload>> alt0{};
                {
                    auto v = Serializer<v1001::CylinderDataPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<6>(alt0);
                break;
            }
            case 7: {
                std::variant_alternative_t<7, std::variant<std::monostate, ArrowDataPayload, v2193::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload, v1001::CylinderDataPayload, v1001::PyramidDataPayload, v1001::EllipsoidDataPayload, v1001::ConeDataPayload>> alt0{};
                {
                    auto v = Serializer<v1001::PyramidDataPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<7>(alt0);
                break;
            }
            case 8: {
                std::variant_alternative_t<8, std::variant<std::monostate, ArrowDataPayload, v2193::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload, v1001::CylinderDataPayload, v1001::PyramidDataPayload, v1001::EllipsoidDataPayload, v1001::ConeDataPayload>> alt0{};
                {
                    auto v = Serializer<v1001::EllipsoidDataPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<8>(alt0);
                break;
            }
            case 9: {
                std::variant_alternative_t<9, std::variant<std::monostate, ArrowDataPayload, v2193::TextDataPayload, BoxDataPayload, LineDataPayload, SphereDataPayload, v1001::CylinderDataPayload, v1001::PyramidDataPayload, v1001::EllipsoidDataPayload, v1001::ConeDataPayload>> alt0{};
                {
                    auto v = Serializer<v1001::ConeDataPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<9>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.extra_data_payload = var0;
    }
    return out;
}

void Serializer<v975::PrimitiveShapesPacket>::serialize(BinaryWriter &stream, const v975::PrimitiveShapesPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.shapes.size());
    for (const auto &e0 : value.shapes) {
        Serializer<v975::PrimitiveShapeDataPayload>::serialize(stream, e0);
    }
}

auto Serializer<v975::PrimitiveShapesPacket>::deserialize(BinaryReader &stream) -> std::expected<v975::PrimitiveShapesPacket, std::error_code>
{
    v975::PrimitiveShapesPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.shapes.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.shapes.emplace_back();
            auto v = Serializer<v975::PrimitiveShapeDataPayload>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.shapes.back() = *v;
        }
    }
    return out;
}

void Serializer<v1001::PrimitiveShapesPacket>::serialize(BinaryWriter &stream, const v1001::PrimitiveShapesPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.shapes.size());
    for (const auto &e0 : value.shapes) {
        Serializer<v1001::PrimitiveShapeDataPayload>::serialize(stream, e0);
    }
}

auto Serializer<v1001::PrimitiveShapesPacket>::deserialize(BinaryReader &stream) -> std::expected<v1001::PrimitiveShapesPacket, std::error_code>
{
    v1001::PrimitiveShapesPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.shapes.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.shapes.emplace_back();
            auto v = Serializer<v1001::PrimitiveShapeDataPayload>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.shapes.back() = *v;
        }
    }
    return out;
}

void Serializer<v2193::PrimitiveShapesPacket>::serialize(BinaryWriter &stream, const v2193::PrimitiveShapesPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.shapes.size());
    for (const auto &e0 : value.shapes) {
        Serializer<v2193::PrimitiveShapeDataPayload>::serialize(stream, e0);
    }
}

auto Serializer<v2193::PrimitiveShapesPacket>::deserialize(BinaryReader &stream) -> std::expected<v2193::PrimitiveShapesPacket, std::error_code>
{
    v2193::PrimitiveShapesPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.shapes.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.shapes.emplace_back();
            auto v = Serializer<v2193::PrimitiveShapeDataPayload>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.shapes.back() = *v;
        }
    }
    return out;
}

void Serializer<v859::DebugDrawerPacket>::serialize(BinaryWriter &stream, const v859::DebugDrawerPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.shapes.size());
    for (const auto &e0 : value.shapes) {
        Serializer<v859::PrimitiveShapeDataPayload>::serialize(stream, e0);
    }
}

auto Serializer<v859::DebugDrawerPacket>::deserialize(BinaryReader &stream) -> std::expected<v859::DebugDrawerPacket, std::error_code>
{
    v859::DebugDrawerPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.shapes.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.shapes.emplace_back();
            auto v = Serializer<v859::PrimitiveShapeDataPayload>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.shapes.back() = *v;
        }
    }
    return out;
}

void Serializer<v898::DebugDrawerPacket>::serialize(BinaryWriter &stream, const v898::DebugDrawerPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.shapes.size());
    for (const auto &e0 : value.shapes) {
        Serializer<v898::PrimitiveShapeDataPayload>::serialize(stream, e0);
    }
}

auto Serializer<v898::DebugDrawerPacket>::deserialize(BinaryReader &stream) -> std::expected<v898::DebugDrawerPacket, std::error_code>
{
    v898::DebugDrawerPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.shapes.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.shapes.emplace_back();
            auto v = Serializer<v898::PrimitiveShapeDataPayload>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.shapes.back() = *v;
        }
    }
    return out;
}

void Serializer<v924::DebugDrawerPacket>::serialize(BinaryWriter &stream, const v924::DebugDrawerPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.shapes.size());
    for (const auto &e0 : value.shapes) {
        Serializer<v924::PrimitiveShapeDataPayload>::serialize(stream, e0);
    }
}

auto Serializer<v924::DebugDrawerPacket>::deserialize(BinaryReader &stream) -> std::expected<v924::DebugDrawerPacket, std::error_code>
{
    v924::DebugDrawerPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.shapes.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.shapes.emplace_back();
            auto v = Serializer<v924::PrimitiveShapeDataPayload>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.shapes.back() = *v;
        }
    }
    return out;
}

void Serializer<base::PacketShapeData>::serialize(BinaryWriter &stream, const base::PacketShapeData &value)
{
    stream.writeVarInt<std::uint64_t>(value.network_id);
    stream.write<bool>(value.shape_type.has_value());
    if (value.shape_type.has_value()) {
        stream.write<std::uint8_t>((*value.shape_type));
    }
    stream.write<bool>(value.location.has_value());
    if (value.location.has_value()) {
        Serializer<Vec3>::serialize(stream, (*value.location));
    }
    stream.write<bool>(value.scale.has_value());
    if (value.scale.has_value()) {
        stream.write<float>((*value.scale));
    }
    stream.write<bool>(value.rotation.has_value());
    if (value.rotation.has_value()) {
        Serializer<Vec3>::serialize(stream, (*value.rotation));
    }
    stream.write<bool>(value.time_left_total_sec.has_value());
    if (value.time_left_total_sec.has_value()) {
        stream.write<float>((*value.time_left_total_sec));
    }
    stream.write<bool>(value.color.has_value());
    if (value.color.has_value()) {
        stream.write<std::int32_t>((*value.color));
    }
    stream.write<bool>(value.text.has_value());
    if (value.text.has_value()) {
        stream.write((*value.text));
    }
    stream.write<bool>(value.box_bound.has_value());
    if (value.box_bound.has_value()) {
        Serializer<Vec3>::serialize(stream, (*value.box_bound));
    }
    stream.write<bool>(value.end_location.has_value());
    if (value.end_location.has_value()) {
        Serializer<Vec3>::serialize(stream, (*value.end_location));
    }
    stream.write<bool>(value.arrow_head_length.has_value());
    if (value.arrow_head_length.has_value()) {
        stream.write<float>((*value.arrow_head_length));
    }
    stream.write<bool>(value.arrow_head_radius.has_value());
    if (value.arrow_head_radius.has_value()) {
        stream.write<float>((*value.arrow_head_radius));
    }
    stream.write<bool>(value.num_segments.has_value());
    if (value.num_segments.has_value()) {
        stream.write<std::uint8_t>((*value.num_segments));
    }
}

auto Serializer<base::PacketShapeData>::deserialize(BinaryReader &stream) -> std::expected<base::PacketShapeData, std::error_code>
{
    base::PacketShapeData out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.network_id = static_cast<std::uint64_t>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            base::ScriptPrimitiveShapeType staged{};
            auto v = stream.read<std::uint8_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<base::ScriptPrimitiveShapeType>(*v);
            out.shape_type = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec3 staged{};
            auto v = Serializer<Vec3>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.location = std::move(staged);
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
            out.scale = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec3 staged{};
            auto v = Serializer<Vec3>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.rotation = std::move(staged);
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
            out.time_left_total_sec = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Color staged{};
            auto v = stream.read<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<Color>(*v);
            out.color = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::string staged{};
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.text = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec3 staged{};
            auto v = Serializer<Vec3>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.box_bound = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec3 staged{};
            auto v = Serializer<Vec3>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.end_location = std::move(staged);
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
            out.arrow_head_length = std::move(staged);
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
            out.arrow_head_radius = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::uint8_t staged{};
            auto v = stream.read<std::uint8_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<std::uint8_t>(*v);
            out.num_segments = std::move(staged);
        }
    }
    return out;
}

void Serializer<v818::ServerScriptDebugDrawerPacket>::serialize(BinaryWriter &stream, const v818::ServerScriptDebugDrawerPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.shapes.size());
    for (const auto &e0 : value.shapes) {
        Serializer<base::PacketShapeData>::serialize(stream, e0);
    }
}

auto Serializer<v818::ServerScriptDebugDrawerPacket>::deserialize(BinaryReader &stream) -> std::expected<v818::ServerScriptDebugDrawerPacket, std::error_code>
{
    v818::ServerScriptDebugDrawerPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.shapes.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.shapes.emplace_back();
            auto v = Serializer<base::PacketShapeData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.shapes.back() = *v;
        }
    }
    return out;
}

}  // namespace bedrock::protocol
