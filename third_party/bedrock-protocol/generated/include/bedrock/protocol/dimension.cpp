#include <bedrock/protocol/dimension.h>

namespace bedrock::protocol {


void Serializer<base::DimensionDefinitionGroup::DimensionDefinition>::serialize(BinaryWriter &stream, const base::DimensionDefinitionGroup::DimensionDefinition &value)
{
    stream.writeVarInt<std::int32_t>(value.height_maximum);
    stream.writeVarInt<std::int32_t>(value.height_minimum);
    stream.writeVarInt<std::int32_t>(value.generator_type);
}

auto Serializer<base::DimensionDefinitionGroup::DimensionDefinition>::deserialize(BinaryReader &stream) -> std::expected<base::DimensionDefinitionGroup::DimensionDefinition, std::error_code>
{
    base::DimensionDefinitionGroup::DimensionDefinition out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.height_maximum = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.height_minimum = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.generator_type = static_cast<GeneratorType>(*v);
    }
    return out;
}

void Serializer<v975::DimensionDefinitionGroup::DimensionDefinition>::serialize(BinaryWriter &stream, const v975::DimensionDefinitionGroup::DimensionDefinition &value)
{
    stream.writeVarInt<std::int32_t>(value.height_maximum);
    stream.writeVarInt<std::int32_t>(value.height_minimum);
    stream.writeVarInt<std::int32_t>(value.generator_type);
    stream.writeVarInt<std::int32_t>(value.dimension_type);
}

auto Serializer<v975::DimensionDefinitionGroup::DimensionDefinition>::deserialize(BinaryReader &stream) -> std::expected<v975::DimensionDefinitionGroup::DimensionDefinition, std::error_code>
{
    v975::DimensionDefinitionGroup::DimensionDefinition out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.height_maximum = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.height_minimum = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.generator_type = static_cast<GeneratorType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.dimension_type = static_cast<DimensionType>(*v);
    }
    return out;
}

void Serializer<v2168::DimensionDefinitionGroup::DimensionDefinition>::serialize(BinaryWriter &stream, const v2168::DimensionDefinitionGroup::DimensionDefinition &value)
{
    stream.writeVarInt<std::int32_t>(value.height_maximum);
    stream.writeVarInt<std::int32_t>(value.height_minimum);
    stream.writeVarInt<std::int32_t>(value.generator_type);
    stream.writeVarInt<std::int32_t>(value.dimension_type);
    Serializer<UUID>::serialize(stream, value.pack_id);
}

auto Serializer<v2168::DimensionDefinitionGroup::DimensionDefinition>::deserialize(BinaryReader &stream) -> std::expected<v2168::DimensionDefinitionGroup::DimensionDefinition, std::error_code>
{
    v2168::DimensionDefinitionGroup::DimensionDefinition out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.height_maximum = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.height_minimum = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.generator_type = static_cast<GeneratorType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.dimension_type = static_cast<DimensionType>(*v);
    }
    {
        auto v = Serializer<UUID>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pack_id = *v;
    }
    return out;
}

void Serializer<v2193::DimensionDefinitionGroup::DimensionDefinition>::serialize(BinaryWriter &stream, const v2193::DimensionDefinitionGroup::DimensionDefinition &value)
{
    stream.writeVarInt<std::int32_t>(value.min_y);
    stream.writeVarInt<std::int32_t>(value.height_range);
    stream.writeVarInt<std::int32_t>(value.generator_type);
    stream.writeVarInt<std::int32_t>(value.dimension_type);
    Serializer<UUID>::serialize(stream, value.pack_id);
    stream.write(value.default_biome);
}

auto Serializer<v2193::DimensionDefinitionGroup::DimensionDefinition>::deserialize(BinaryReader &stream) -> std::expected<v2193::DimensionDefinitionGroup::DimensionDefinition, std::error_code>
{
    v2193::DimensionDefinitionGroup::DimensionDefinition out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.min_y = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.height_range = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.generator_type = static_cast<GeneratorType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.dimension_type = static_cast<DimensionType>(*v);
    }
    {
        auto v = Serializer<UUID>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pack_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.default_biome = *v;
    }
    return out;
}

void Serializer<v2225::DimensionDefinitionGroup::DimensionDefinition>::serialize(BinaryWriter &stream, const v2225::DimensionDefinitionGroup::DimensionDefinition &value)
{
    stream.writeVarInt<std::int32_t>(value.min_y);
    stream.writeVarInt<std::int32_t>(value.height_range);
    stream.writeVarInt<std::int32_t>(value.generator_type);
    stream.writeVarInt<std::int32_t>(value.dimension_type);
    Serializer<UUID>::serialize(stream, value.pack_id);
    stream.write(value.default_biome);
    stream.writeVarInt<std::int32_t>(value.cloud_height);
    stream.write<bool>(value.render_clouds);
}

auto Serializer<v2225::DimensionDefinitionGroup::DimensionDefinition>::deserialize(BinaryReader &stream) -> std::expected<v2225::DimensionDefinitionGroup::DimensionDefinition, std::error_code>
{
    v2225::DimensionDefinitionGroup::DimensionDefinition out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.min_y = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.height_range = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.generator_type = static_cast<GeneratorType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.dimension_type = static_cast<DimensionType>(*v);
    }
    {
        auto v = Serializer<UUID>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pack_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.default_biome = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.cloud_height = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.render_clouds = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<base::DimensionDataPacket>::serialize(BinaryWriter &stream, const base::DimensionDataPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.dimension_definitions.size());
    for (const auto &[k0, v0] : value.dimension_definitions) {
        stream.write(k0);
        Serializer<base::DimensionDefinitionGroup::DimensionDefinition>::serialize(stream, v0);
    }
}

auto Serializer<base::DimensionDataPacket>::deserialize(BinaryReader &stream) -> std::expected<base::DimensionDataPacket, std::error_code>
{
    base::DimensionDataPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.dimension_definitions.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            std::string key0{};
            {
                auto v = stream.read<std::string>();
                if (!v) return std::unexpected(v.error());
                key0 = *v;
            }
            auto v = Serializer<base::DimensionDefinitionGroup::DimensionDefinition>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.dimension_definitions[key0] = *v;
        }
    }
    return out;
}

void Serializer<v975::DimensionDataPacket>::serialize(BinaryWriter &stream, const v975::DimensionDataPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.dimension_definitions.size());
    for (const auto &[k0, v0] : value.dimension_definitions) {
        stream.write(k0);
        Serializer<v975::DimensionDefinitionGroup::DimensionDefinition>::serialize(stream, v0);
    }
}

auto Serializer<v975::DimensionDataPacket>::deserialize(BinaryReader &stream) -> std::expected<v975::DimensionDataPacket, std::error_code>
{
    v975::DimensionDataPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.dimension_definitions.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            std::string key0{};
            {
                auto v = stream.read<std::string>();
                if (!v) return std::unexpected(v.error());
                key0 = *v;
            }
            auto v = Serializer<v975::DimensionDefinitionGroup::DimensionDefinition>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.dimension_definitions[key0] = *v;
        }
    }
    return out;
}

void Serializer<v2168::DimensionDataPacket>::serialize(BinaryWriter &stream, const v2168::DimensionDataPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.dimension_definitions.size());
    for (const auto &[k0, v0] : value.dimension_definitions) {
        stream.write(k0);
        Serializer<v2168::DimensionDefinitionGroup::DimensionDefinition>::serialize(stream, v0);
    }
}

auto Serializer<v2168::DimensionDataPacket>::deserialize(BinaryReader &stream) -> std::expected<v2168::DimensionDataPacket, std::error_code>
{
    v2168::DimensionDataPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.dimension_definitions.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            std::string key0{};
            {
                auto v = stream.read<std::string>();
                if (!v) return std::unexpected(v.error());
                key0 = *v;
            }
            auto v = Serializer<v2168::DimensionDefinitionGroup::DimensionDefinition>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.dimension_definitions[key0] = *v;
        }
    }
    return out;
}

void Serializer<v2193::DimensionDataPacket>::serialize(BinaryWriter &stream, const v2193::DimensionDataPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.dimension_definitions.size());
    for (const auto &[k0, v0] : value.dimension_definitions) {
        stream.write(k0);
        Serializer<v2193::DimensionDefinitionGroup::DimensionDefinition>::serialize(stream, v0);
    }
}

auto Serializer<v2193::DimensionDataPacket>::deserialize(BinaryReader &stream) -> std::expected<v2193::DimensionDataPacket, std::error_code>
{
    v2193::DimensionDataPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.dimension_definitions.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            std::string key0{};
            {
                auto v = stream.read<std::string>();
                if (!v) return std::unexpected(v.error());
                key0 = *v;
            }
            auto v = Serializer<v2193::DimensionDefinitionGroup::DimensionDefinition>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.dimension_definitions[key0] = *v;
        }
    }
    return out;
}

void Serializer<v2225::DimensionDataPacket>::serialize(BinaryWriter &stream, const v2225::DimensionDataPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.dimension_definitions.size());
    for (const auto &[k0, v0] : value.dimension_definitions) {
        stream.write(k0);
        Serializer<v2225::DimensionDefinitionGroup::DimensionDefinition>::serialize(stream, v0);
    }
}

auto Serializer<v2225::DimensionDataPacket>::deserialize(BinaryReader &stream) -> std::expected<v2225::DimensionDataPacket, std::error_code>
{
    v2225::DimensionDataPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.dimension_definitions.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            std::string key0{};
            {
                auto v = stream.read<std::string>();
                if (!v) return std::unexpected(v.error());
                key0 = *v;
            }
            auto v = Serializer<v2225::DimensionDefinitionGroup::DimensionDefinition>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.dimension_definitions[key0] = *v;
        }
    }
    return out;
}

void Serializer<ChangeDimensionPacket>::serialize(BinaryWriter &stream, const ChangeDimensionPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.dimension_id);
    Serializer<Vec3>::serialize(stream, value.pos);
    stream.write<bool>(value.respawn);
    stream.write<bool>(value.loading_screen_id.has_value());
    if (value.loading_screen_id.has_value()) {
        stream.write<std::uint32_t>((*value.loading_screen_id));
    }
}

auto Serializer<ChangeDimensionPacket>::deserialize(BinaryReader &stream) -> std::expected<ChangeDimensionPacket, std::error_code>
{
    ChangeDimensionPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.dimension_id = static_cast<DimensionType>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.respawn = static_cast<bool>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::uint32_t staged{};
            auto v = stream.read<std::uint32_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<std::uint32_t>(*v);
            out.loading_screen_id = std::move(staged);
        }
    }
    return out;
}

}  // namespace bedrock::protocol
