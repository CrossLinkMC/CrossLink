#include <bedrock/protocol/biome.h>

namespace bedrock::protocol {


void Serializer<FloatRange>::serialize(BinaryWriter &stream, const FloatRange &value)
{
    stream.write<float>(value.min);
    stream.write<float>(value.max);
}

auto Serializer<FloatRange>::deserialize(BinaryReader &stream) -> std::expected<FloatRange, std::error_code>
{
    FloatRange out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.min = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.max = static_cast<float>(*v);
    }
    return out;
}

void Serializer<v1001::NoiseDescriptor>::serialize(BinaryWriter &stream, const v1001::NoiseDescriptor &value)
{
    stream.write(value.name);
    stream.write<std::int32_t>(value.first_octave);
    stream.writeVarInt<std::uint32_t>(value.amplitudes.size());
    for (const auto &e0 : value.amplitudes) {
        stream.write<float>(e0);
    }
}

auto Serializer<v1001::NoiseDescriptor>::deserialize(BinaryReader &stream) -> std::expected<v1001::NoiseDescriptor, std::error_code>
{
    v1001::NoiseDescriptor out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.first_octave = static_cast<std::int32_t>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.amplitudes.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.amplitudes.emplace_back();
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            out.amplitudes.back() = static_cast<float>(*v);
        }
    }
    return out;
}

void Serializer<v1001::SerializedNoiseBlockSpecifier>::serialize(BinaryWriter &stream, const v1001::SerializedNoiseBlockSpecifier &value)
{
    stream.write(value.noise);
    stream.write<float>(value.threshold);
    Serializer<FloatRange>::serialize(stream, value.range);
    stream.write<std::uint32_t>(value.block_runtime_id);
}

auto Serializer<v1001::SerializedNoiseBlockSpecifier>::deserialize(BinaryReader &stream) -> std::expected<v1001::SerializedNoiseBlockSpecifier, std::error_code>
{
    v1001::SerializedNoiseBlockSpecifier out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.noise = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.threshold = static_cast<float>(*v);
    }
    {
        auto v = Serializer<FloatRange>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.range = *v;
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.block_runtime_id = static_cast<BlockRuntimeId>(*v);
    }
    return out;
}

void Serializer<base::BiomeNoiseGradientSurfaceData>::serialize(BinaryWriter &stream, const base::BiomeNoiseGradientSurfaceData &value)
{
    stream.writeVarInt<std::uint32_t>(value.non_replaceable_blocks.size());
    for (const auto &e0 : value.non_replaceable_blocks) {
        stream.write<std::uint32_t>(e0);
    }
    stream.writeVarInt<std::uint32_t>(value.gradient_blocks.size());
    for (const auto &e0 : value.gradient_blocks) {
        stream.write<std::uint32_t>(e0);
    }
    stream.write(value.noise_seed_string);
    stream.write<std::int32_t>(value.first_octave);
    stream.writeVarInt<std::uint32_t>(value.amplitudes.size());
    for (const auto &e0 : value.amplitudes) {
        stream.write<float>(e0);
    }
}

auto Serializer<base::BiomeNoiseGradientSurfaceData>::deserialize(BinaryReader &stream) -> std::expected<base::BiomeNoiseGradientSurfaceData, std::error_code>
{
    base::BiomeNoiseGradientSurfaceData out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.non_replaceable_blocks.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.non_replaceable_blocks.emplace_back();
            auto v = stream.read<std::uint32_t>();
            if (!v) return std::unexpected(v.error());
            out.non_replaceable_blocks.back() = static_cast<std::uint32_t>(*v);
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.gradient_blocks.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.gradient_blocks.emplace_back();
            auto v = stream.read<std::uint32_t>();
            if (!v) return std::unexpected(v.error());
            out.gradient_blocks.back() = static_cast<std::uint32_t>(*v);
        }
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.noise_seed_string = *v;
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.first_octave = static_cast<std::int32_t>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.amplitudes.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.amplitudes.emplace_back();
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            out.amplitudes.back() = static_cast<float>(*v);
        }
    }
    return out;
}

void Serializer<v1001::BiomeNoiseGradientSurfaceData>::serialize(BinaryWriter &stream, const v1001::BiomeNoiseGradientSurfaceData &value)
{
    stream.writeVarInt<std::uint32_t>(value.non_replaceable_blocks.size());
    for (const auto &e0 : value.non_replaceable_blocks) {
        stream.write<std::uint32_t>(e0);
    }
    stream.writeVarInt<std::uint32_t>(value.gradient_block_ranges.size());
    for (const auto &e0 : value.gradient_block_ranges) {
        Serializer<v1001::SerializedNoiseBlockSpecifier>::serialize(stream, e0);
    }
    Serializer<v1001::NoiseDescriptor>::serialize(stream, value.noise_descriptor);
}

auto Serializer<v1001::BiomeNoiseGradientSurfaceData>::deserialize(BinaryReader &stream) -> std::expected<v1001::BiomeNoiseGradientSurfaceData, std::error_code>
{
    v1001::BiomeNoiseGradientSurfaceData out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.non_replaceable_blocks.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.non_replaceable_blocks.emplace_back();
            auto v = stream.read<std::uint32_t>();
            if (!v) return std::unexpected(v.error());
            out.non_replaceable_blocks.back() = static_cast<std::uint32_t>(*v);
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.gradient_block_ranges.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.gradient_block_ranges.emplace_back();
            auto v = Serializer<v1001::SerializedNoiseBlockSpecifier>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.gradient_block_ranges.back() = *v;
        }
    }
    {
        auto v = Serializer<v1001::NoiseDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.noise_descriptor = *v;
    }
    return out;
}

void Serializer<BiomeSurfaceMaterialData>::serialize(BinaryWriter &stream, const BiomeSurfaceMaterialData &value)
{
    stream.write<std::uint32_t>(value.top_block);
    stream.write<std::uint32_t>(value.mid_block);
    stream.write<std::uint32_t>(value.sea_floor_block);
    stream.write<std::uint32_t>(value.foundation_block);
    stream.write<std::uint32_t>(value.sea_block);
    stream.write<std::int32_t>(value.sea_floor_depth);
}

auto Serializer<BiomeSurfaceMaterialData>::deserialize(BinaryReader &stream) -> std::expected<BiomeSurfaceMaterialData, std::error_code>
{
    BiomeSurfaceMaterialData out;
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.top_block = static_cast<BlockRuntimeId>(*v);
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.mid_block = static_cast<BlockRuntimeId>(*v);
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.sea_floor_block = static_cast<BlockRuntimeId>(*v);
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.foundation_block = static_cast<BlockRuntimeId>(*v);
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.sea_block = static_cast<BlockRuntimeId>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.sea_floor_depth = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<BiomeMesaSurfaceData>::serialize(BinaryWriter &stream, const BiomeMesaSurfaceData &value)
{
    stream.write<std::uint32_t>(value.clay_material);
    stream.write<std::uint32_t>(value.hard_clay_material);
    stream.write<bool>(value.bryce_pillars);
    stream.write<bool>(value.has_forest);
}

auto Serializer<BiomeMesaSurfaceData>::deserialize(BinaryReader &stream) -> std::expected<BiomeMesaSurfaceData, std::error_code>
{
    BiomeMesaSurfaceData out;
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.clay_material = static_cast<BlockRuntimeId>(*v);
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.hard_clay_material = static_cast<BlockRuntimeId>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.bryce_pillars = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_forest = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<BiomeCappedSurfaceData>::serialize(BinaryWriter &stream, const BiomeCappedSurfaceData &value)
{
    stream.writeVarInt<std::uint32_t>(value.floor_blocks.size());
    for (const auto &e0 : value.floor_blocks) {
        stream.write<std::uint32_t>(e0);
    }
    stream.writeVarInt<std::uint32_t>(value.ceiling_blocks.size());
    for (const auto &e0 : value.ceiling_blocks) {
        stream.write<std::uint32_t>(e0);
    }
    stream.write<bool>(value.sea_block.has_value());
    if (value.sea_block.has_value()) {
        stream.write<std::uint32_t>((*value.sea_block));
    }
    stream.write<bool>(value.foundation_block.has_value());
    if (value.foundation_block.has_value()) {
        stream.write<std::uint32_t>((*value.foundation_block));
    }
    stream.write<bool>(value.beach_block.has_value());
    if (value.beach_block.has_value()) {
        stream.write<std::uint32_t>((*value.beach_block));
    }
}

auto Serializer<BiomeCappedSurfaceData>::deserialize(BinaryReader &stream) -> std::expected<BiomeCappedSurfaceData, std::error_code>
{
    BiomeCappedSurfaceData out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.floor_blocks.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.floor_blocks.emplace_back();
            auto v = stream.read<std::uint32_t>();
            if (!v) return std::unexpected(v.error());
            out.floor_blocks.back() = static_cast<std::uint32_t>(*v);
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.ceiling_blocks.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.ceiling_blocks.emplace_back();
            auto v = stream.read<std::uint32_t>();
            if (!v) return std::unexpected(v.error());
            out.ceiling_blocks.back() = static_cast<std::uint32_t>(*v);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::uint32_t staged{};
            auto v = stream.read<std::uint32_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<std::uint32_t>(*v);
            out.sea_block = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::uint32_t staged{};
            auto v = stream.read<std::uint32_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<std::uint32_t>(*v);
            out.foundation_block = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::uint32_t staged{};
            auto v = stream.read<std::uint32_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<std::uint32_t>(*v);
            out.beach_block = std::move(staged);
        }
    }
    return out;
}

void Serializer<base::BiomeSurfaceBuilderData>::serialize(BinaryWriter &stream, const base::BiomeSurfaceBuilderData &value)
{
    stream.write<bool>(value.surface_materials.has_value());
    if (value.surface_materials.has_value()) {
        Serializer<BiomeSurfaceMaterialData>::serialize(stream, (*value.surface_materials));
    }
    stream.write<bool>(value.has_default_overworld_surface);
    stream.write<bool>(value.has_swamp_surface);
    stream.write<bool>(value.has_frozen_ocean_surface);
    stream.write<bool>(value.has_the_end_surface);
    stream.write<bool>(value.mesa_surface.has_value());
    if (value.mesa_surface.has_value()) {
        Serializer<BiomeMesaSurfaceData>::serialize(stream, (*value.mesa_surface));
    }
    stream.write<bool>(value.capped_surface.has_value());
    if (value.capped_surface.has_value()) {
        Serializer<BiomeCappedSurfaceData>::serialize(stream, (*value.capped_surface));
    }
    stream.write<bool>(value.noise_gradient_surface.has_value());
    if (value.noise_gradient_surface.has_value()) {
        Serializer<base::BiomeNoiseGradientSurfaceData>::serialize(stream, (*value.noise_gradient_surface));
    }
}

auto Serializer<base::BiomeSurfaceBuilderData>::deserialize(BinaryReader &stream) -> std::expected<base::BiomeSurfaceBuilderData, std::error_code>
{
    base::BiomeSurfaceBuilderData out;
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeSurfaceMaterialData staged{};
            auto v = Serializer<BiomeSurfaceMaterialData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.surface_materials = std::move(staged);
        }
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_default_overworld_surface = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_swamp_surface = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_frozen_ocean_surface = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_the_end_surface = static_cast<bool>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeMesaSurfaceData staged{};
            auto v = Serializer<BiomeMesaSurfaceData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.mesa_surface = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeCappedSurfaceData staged{};
            auto v = Serializer<BiomeCappedSurfaceData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.capped_surface = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            base::BiomeNoiseGradientSurfaceData staged{};
            auto v = Serializer<base::BiomeNoiseGradientSurfaceData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.noise_gradient_surface = std::move(staged);
        }
    }
    return out;
}

void Serializer<v1001::BiomeSurfaceBuilderData>::serialize(BinaryWriter &stream, const v1001::BiomeSurfaceBuilderData &value)
{
    stream.write<bool>(value.surface_materials.has_value());
    if (value.surface_materials.has_value()) {
        Serializer<BiomeSurfaceMaterialData>::serialize(stream, (*value.surface_materials));
    }
    stream.write<bool>(value.has_default_overworld_surface);
    stream.write<bool>(value.has_swamp_surface);
    stream.write<bool>(value.has_frozen_ocean_surface);
    stream.write<bool>(value.has_the_end_surface);
    stream.write<bool>(value.mesa_surface.has_value());
    if (value.mesa_surface.has_value()) {
        Serializer<BiomeMesaSurfaceData>::serialize(stream, (*value.mesa_surface));
    }
    stream.write<bool>(value.capped_surface.has_value());
    if (value.capped_surface.has_value()) {
        Serializer<BiomeCappedSurfaceData>::serialize(stream, (*value.capped_surface));
    }
    stream.write<bool>(value.noise_gradient_surface.has_value());
    if (value.noise_gradient_surface.has_value()) {
        Serializer<v1001::BiomeNoiseGradientSurfaceData>::serialize(stream, (*value.noise_gradient_surface));
    }
}

auto Serializer<v1001::BiomeSurfaceBuilderData>::deserialize(BinaryReader &stream) -> std::expected<v1001::BiomeSurfaceBuilderData, std::error_code>
{
    v1001::BiomeSurfaceBuilderData out;
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeSurfaceMaterialData staged{};
            auto v = Serializer<BiomeSurfaceMaterialData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.surface_materials = std::move(staged);
        }
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_default_overworld_surface = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_swamp_surface = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_frozen_ocean_surface = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_the_end_surface = static_cast<bool>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeMesaSurfaceData staged{};
            auto v = Serializer<BiomeMesaSurfaceData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.mesa_surface = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeCappedSurfaceData staged{};
            auto v = Serializer<BiomeCappedSurfaceData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.capped_surface = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v1001::BiomeNoiseGradientSurfaceData staged{};
            auto v = Serializer<v1001::BiomeNoiseGradientSurfaceData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.noise_gradient_surface = std::move(staged);
        }
    }
    return out;
}

void Serializer<base::BiomeClimateData>::serialize(BinaryWriter &stream, const base::BiomeClimateData &value)
{
    stream.write<float>(value.temperature);
    stream.write<float>(value.downfall);
    stream.write<float>(value.red_spore_density);
    stream.write<float>(value.blue_spore_density);
    stream.write<float>(value.ash_density);
    stream.write<float>(value.white_ash_density);
    stream.write<float>(value.snow_accumulation_min);
    stream.write<float>(value.snow_accumulation_max);
}

auto Serializer<base::BiomeClimateData>::deserialize(BinaryReader &stream) -> std::expected<base::BiomeClimateData, std::error_code>
{
    base::BiomeClimateData out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.temperature = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.downfall = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.red_spore_density = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.blue_spore_density = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.ash_density = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.white_ash_density = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.snow_accumulation_min = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.snow_accumulation_max = static_cast<float>(*v);
    }
    return out;
}

void Serializer<v844::BiomeClimateData>::serialize(BinaryWriter &stream, const v844::BiomeClimateData &value)
{
    stream.write<float>(value.temperature);
    stream.write<float>(value.downfall);
    stream.write<float>(value.snow_accumulation_min);
    stream.write<float>(value.snow_accumulation_max);
}

auto Serializer<v844::BiomeClimateData>::deserialize(BinaryReader &stream) -> std::expected<v844::BiomeClimateData, std::error_code>
{
    v844::BiomeClimateData out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.temperature = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.downfall = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.snow_accumulation_min = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.snow_accumulation_max = static_cast<float>(*v);
    }
    return out;
}

void Serializer<base::BiomeCoordinateData>::serialize(BinaryWriter &stream, const base::BiomeCoordinateData &value)
{
    stream.writeVarInt<std::int32_t>(value.min_value_type);
    stream.write<std::uint16_t>(value.min_value);
    stream.writeVarInt<std::int32_t>(value.max_value_type);
    stream.write<std::uint16_t>(value.max_value);
    stream.write<std::uint32_t>(value.grid_offset);
    stream.write<std::uint32_t>(value.grid_step_size);
    stream.writeVarInt<std::int32_t>(value.distribution);
}

auto Serializer<base::BiomeCoordinateData>::deserialize(BinaryReader &stream) -> std::expected<base::BiomeCoordinateData, std::error_code>
{
    base::BiomeCoordinateData out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.min_value_type = static_cast<base::ExpressionOp>(*v);
    }
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.min_value = static_cast<BiomeStringIndex>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.max_value_type = static_cast<base::ExpressionOp>(*v);
    }
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.max_value = static_cast<BiomeStringIndex>(*v);
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.grid_offset = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.grid_step_size = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.distribution = static_cast<RandomDistributionType>(*v);
    }
    return out;
}

void Serializer<v800::BiomeCoordinateData>::serialize(BinaryWriter &stream, const v800::BiomeCoordinateData &value)
{
    stream.writeVarInt<std::int32_t>(value.min_value_type);
    stream.write<std::uint16_t>(value.min_value);
    stream.writeVarInt<std::int32_t>(value.max_value_type);
    stream.write<std::uint16_t>(value.max_value);
    stream.write<std::uint32_t>(value.grid_offset);
    stream.write<std::uint32_t>(value.grid_step_size);
    stream.writeVarInt<std::int32_t>(value.distribution);
}

auto Serializer<v800::BiomeCoordinateData>::deserialize(BinaryReader &stream) -> std::expected<v800::BiomeCoordinateData, std::error_code>
{
    v800::BiomeCoordinateData out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.min_value_type = static_cast<v800::ExpressionOp>(*v);
    }
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.min_value = static_cast<BiomeStringIndex>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.max_value_type = static_cast<v800::ExpressionOp>(*v);
    }
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.max_value = static_cast<BiomeStringIndex>(*v);
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.grid_offset = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.grid_step_size = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.distribution = static_cast<RandomDistributionType>(*v);
    }
    return out;
}

void Serializer<v859::BiomeCoordinateData>::serialize(BinaryWriter &stream, const v859::BiomeCoordinateData &value)
{
    stream.writeVarInt<std::int32_t>(value.min_value_type);
    stream.write<std::uint16_t>(value.min_value);
    stream.writeVarInt<std::int32_t>(value.max_value_type);
    stream.write<std::uint16_t>(value.max_value);
    stream.write<std::uint32_t>(value.grid_offset);
    stream.write<std::uint32_t>(value.grid_step_size);
    stream.writeVarInt<std::int32_t>(value.distribution);
}

auto Serializer<v859::BiomeCoordinateData>::deserialize(BinaryReader &stream) -> std::expected<v859::BiomeCoordinateData, std::error_code>
{
    v859::BiomeCoordinateData out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.min_value_type = static_cast<v859::ExpressionOp>(*v);
    }
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.min_value = static_cast<BiomeStringIndex>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.max_value_type = static_cast<v859::ExpressionOp>(*v);
    }
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.max_value = static_cast<BiomeStringIndex>(*v);
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.grid_offset = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.grid_step_size = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.distribution = static_cast<RandomDistributionType>(*v);
    }
    return out;
}

void Serializer<base::BiomeScatterParamData>::serialize(BinaryWriter &stream, const base::BiomeScatterParamData &value)
{
    stream.writeVarInt<std::uint32_t>(value.coordinates.size());
    for (const auto &e0 : value.coordinates) {
        Serializer<base::BiomeCoordinateData>::serialize(stream, e0);
    }
    stream.writeVarInt<std::int32_t>(value.eval_order);
    stream.writeVarInt<std::int32_t>(value.chance_percent_type);
    stream.write<std::uint16_t>(value.chance_percent);
    stream.write<std::int32_t>(value.chance_numerator);
    stream.write<std::int32_t>(value.chance_denominator);
    stream.writeVarInt<std::int32_t>(value.iterations_type);
    stream.write<std::uint16_t>(value.iterations);
}

auto Serializer<base::BiomeScatterParamData>::deserialize(BinaryReader &stream) -> std::expected<base::BiomeScatterParamData, std::error_code>
{
    base::BiomeScatterParamData out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.coordinates.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.coordinates.emplace_back();
            auto v = Serializer<base::BiomeCoordinateData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.coordinates.back() = *v;
        }
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.eval_order = static_cast<CoordinateEvaluationOrder>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.chance_percent_type = static_cast<base::ExpressionOp>(*v);
    }
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.chance_percent = static_cast<BiomeStringIndex>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.chance_numerator = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.chance_denominator = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.iterations_type = static_cast<base::ExpressionOp>(*v);
    }
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.iterations = static_cast<BiomeStringIndex>(*v);
    }
    return out;
}

void Serializer<v800::BiomeScatterParamData>::serialize(BinaryWriter &stream, const v800::BiomeScatterParamData &value)
{
    stream.writeVarInt<std::uint32_t>(value.coordinates.size());
    for (const auto &e0 : value.coordinates) {
        Serializer<v800::BiomeCoordinateData>::serialize(stream, e0);
    }
    stream.writeVarInt<std::int32_t>(value.eval_order);
    stream.writeVarInt<std::int32_t>(value.chance_percent_type);
    stream.write<std::uint16_t>(value.chance_percent);
    stream.write<std::int32_t>(value.chance_numerator);
    stream.write<std::int32_t>(value.chance_denominator);
    stream.writeVarInt<std::int32_t>(value.iterations_type);
    stream.write<std::uint16_t>(value.iterations);
}

auto Serializer<v800::BiomeScatterParamData>::deserialize(BinaryReader &stream) -> std::expected<v800::BiomeScatterParamData, std::error_code>
{
    v800::BiomeScatterParamData out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.coordinates.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.coordinates.emplace_back();
            auto v = Serializer<v800::BiomeCoordinateData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.coordinates.back() = *v;
        }
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.eval_order = static_cast<CoordinateEvaluationOrder>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.chance_percent_type = static_cast<v800::ExpressionOp>(*v);
    }
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.chance_percent = static_cast<BiomeStringIndex>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.chance_numerator = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.chance_denominator = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.iterations_type = static_cast<v800::ExpressionOp>(*v);
    }
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.iterations = static_cast<BiomeStringIndex>(*v);
    }
    return out;
}

void Serializer<v859::BiomeScatterParamData>::serialize(BinaryWriter &stream, const v859::BiomeScatterParamData &value)
{
    stream.writeVarInt<std::uint32_t>(value.coordinates.size());
    for (const auto &e0 : value.coordinates) {
        Serializer<v859::BiomeCoordinateData>::serialize(stream, e0);
    }
    stream.writeVarInt<std::int32_t>(value.eval_order);
    stream.writeVarInt<std::int32_t>(value.chance_percent_type);
    stream.write<std::uint16_t>(value.chance_percent);
    stream.write<std::int32_t>(value.chance_numerator);
    stream.write<std::int32_t>(value.chance_denominator);
    stream.writeVarInt<std::int32_t>(value.iterations_type);
    stream.write<std::uint16_t>(value.iterations);
}

auto Serializer<v859::BiomeScatterParamData>::deserialize(BinaryReader &stream) -> std::expected<v859::BiomeScatterParamData, std::error_code>
{
    v859::BiomeScatterParamData out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.coordinates.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.coordinates.emplace_back();
            auto v = Serializer<v859::BiomeCoordinateData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.coordinates.back() = *v;
        }
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.eval_order = static_cast<CoordinateEvaluationOrder>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.chance_percent_type = static_cast<v859::ExpressionOp>(*v);
    }
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.chance_percent = static_cast<BiomeStringIndex>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.chance_numerator = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.chance_denominator = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.iterations_type = static_cast<v859::ExpressionOp>(*v);
    }
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.iterations = static_cast<BiomeStringIndex>(*v);
    }
    return out;
}

void Serializer<base::BiomeConsolidatedFeatureData>::serialize(BinaryWriter &stream, const base::BiomeConsolidatedFeatureData &value)
{
    Serializer<base::BiomeScatterParamData>::serialize(stream, value.scatter);
    stream.write<std::uint16_t>(value.feature);
    stream.write<std::uint16_t>(value.identifier);
    stream.write<std::uint16_t>(value.pass);
    stream.write<bool>(value.can_use_internal_feature);
}

auto Serializer<base::BiomeConsolidatedFeatureData>::deserialize(BinaryReader &stream) -> std::expected<base::BiomeConsolidatedFeatureData, std::error_code>
{
    base::BiomeConsolidatedFeatureData out;
    {
        auto v = Serializer<base::BiomeScatterParamData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.scatter = *v;
    }
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.feature = static_cast<BiomeStringIndex>(*v);
    }
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.identifier = static_cast<BiomeStringIndex>(*v);
    }
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.pass = static_cast<BiomeStringIndex>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.can_use_internal_feature = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v800::BiomeConsolidatedFeatureData>::serialize(BinaryWriter &stream, const v800::BiomeConsolidatedFeatureData &value)
{
    Serializer<v800::BiomeScatterParamData>::serialize(stream, value.scatter);
    stream.write<std::uint16_t>(value.feature);
    stream.write<std::uint16_t>(value.identifier);
    stream.write<std::uint16_t>(value.pass);
    stream.write<bool>(value.can_use_internal_feature);
}

auto Serializer<v800::BiomeConsolidatedFeatureData>::deserialize(BinaryReader &stream) -> std::expected<v800::BiomeConsolidatedFeatureData, std::error_code>
{
    v800::BiomeConsolidatedFeatureData out;
    {
        auto v = Serializer<v800::BiomeScatterParamData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.scatter = *v;
    }
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.feature = static_cast<BiomeStringIndex>(*v);
    }
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.identifier = static_cast<BiomeStringIndex>(*v);
    }
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.pass = static_cast<BiomeStringIndex>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.can_use_internal_feature = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v859::BiomeConsolidatedFeatureData>::serialize(BinaryWriter &stream, const v859::BiomeConsolidatedFeatureData &value)
{
    Serializer<v859::BiomeScatterParamData>::serialize(stream, value.scatter);
    stream.write<std::uint16_t>(value.feature);
    stream.write<std::uint16_t>(value.identifier);
    stream.write<std::uint16_t>(value.pass);
    stream.write<bool>(value.can_use_internal_feature);
}

auto Serializer<v859::BiomeConsolidatedFeatureData>::deserialize(BinaryReader &stream) -> std::expected<v859::BiomeConsolidatedFeatureData, std::error_code>
{
    v859::BiomeConsolidatedFeatureData out;
    {
        auto v = Serializer<v859::BiomeScatterParamData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.scatter = *v;
    }
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.feature = static_cast<BiomeStringIndex>(*v);
    }
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.identifier = static_cast<BiomeStringIndex>(*v);
    }
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.pass = static_cast<BiomeStringIndex>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.can_use_internal_feature = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<base::BiomeConsolidatedFeaturesData>::serialize(BinaryWriter &stream, const base::BiomeConsolidatedFeaturesData &value)
{
    stream.writeVarInt<std::uint32_t>(value.features.size());
    for (const auto &e0 : value.features) {
        Serializer<base::BiomeConsolidatedFeatureData>::serialize(stream, e0);
    }
}

auto Serializer<base::BiomeConsolidatedFeaturesData>::deserialize(BinaryReader &stream) -> std::expected<base::BiomeConsolidatedFeaturesData, std::error_code>
{
    base::BiomeConsolidatedFeaturesData out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.features.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.features.emplace_back();
            auto v = Serializer<base::BiomeConsolidatedFeatureData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.features.back() = *v;
        }
    }
    return out;
}

void Serializer<v800::BiomeConsolidatedFeaturesData>::serialize(BinaryWriter &stream, const v800::BiomeConsolidatedFeaturesData &value)
{
    stream.writeVarInt<std::uint32_t>(value.features.size());
    for (const auto &e0 : value.features) {
        Serializer<v800::BiomeConsolidatedFeatureData>::serialize(stream, e0);
    }
}

auto Serializer<v800::BiomeConsolidatedFeaturesData>::deserialize(BinaryReader &stream) -> std::expected<v800::BiomeConsolidatedFeaturesData, std::error_code>
{
    v800::BiomeConsolidatedFeaturesData out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.features.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.features.emplace_back();
            auto v = Serializer<v800::BiomeConsolidatedFeatureData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.features.back() = *v;
        }
    }
    return out;
}

void Serializer<v859::BiomeConsolidatedFeaturesData>::serialize(BinaryWriter &stream, const v859::BiomeConsolidatedFeaturesData &value)
{
    stream.writeVarInt<std::uint32_t>(value.features.size());
    for (const auto &e0 : value.features) {
        Serializer<v859::BiomeConsolidatedFeatureData>::serialize(stream, e0);
    }
}

auto Serializer<v859::BiomeConsolidatedFeaturesData>::deserialize(BinaryReader &stream) -> std::expected<v859::BiomeConsolidatedFeaturesData, std::error_code>
{
    v859::BiomeConsolidatedFeaturesData out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.features.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.features.emplace_back();
            auto v = Serializer<v859::BiomeConsolidatedFeatureData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.features.back() = *v;
        }
    }
    return out;
}

void Serializer<BiomeMountainParamsData>::serialize(BinaryWriter &stream, const BiomeMountainParamsData &value)
{
    stream.write<std::uint32_t>(value.steep_block);
    stream.write<bool>(value.north_slopes);
    stream.write<bool>(value.south_slopes);
    stream.write<bool>(value.west_slopes);
    stream.write<bool>(value.east_slopes);
    stream.write<bool>(value.top_slide_enabled);
}

auto Serializer<BiomeMountainParamsData>::deserialize(BinaryReader &stream) -> std::expected<BiomeMountainParamsData, std::error_code>
{
    BiomeMountainParamsData out;
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.steep_block = static_cast<BlockRuntimeId>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.north_slopes = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.south_slopes = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.west_slopes = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.east_slopes = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.top_slide_enabled = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<base::BiomeElementData>::serialize(BinaryWriter &stream, const base::BiomeElementData &value)
{
    stream.write<float>(value.noise_freq_scale);
    stream.write<float>(value.noise_lower_bound);
    stream.write<float>(value.noise_upper_bound);
    stream.writeVarInt<std::int32_t>(value.height_min_type);
    stream.write<std::uint16_t>(value.height_min);
    stream.writeVarInt<std::int32_t>(value.height_max_type);
    stream.write<std::uint16_t>(value.height_max);
    Serializer<BiomeSurfaceMaterialData>::serialize(stream, value.adjusted_materials);
}

auto Serializer<base::BiomeElementData>::deserialize(BinaryReader &stream) -> std::expected<base::BiomeElementData, std::error_code>
{
    base::BiomeElementData out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.noise_freq_scale = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.noise_lower_bound = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.noise_upper_bound = static_cast<float>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.height_min_type = static_cast<base::ExpressionOp>(*v);
    }
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.height_min = static_cast<BiomeStringIndex>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.height_max_type = static_cast<base::ExpressionOp>(*v);
    }
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.height_max = static_cast<BiomeStringIndex>(*v);
    }
    {
        auto v = Serializer<BiomeSurfaceMaterialData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.adjusted_materials = *v;
    }
    return out;
}

void Serializer<v800::BiomeElementData>::serialize(BinaryWriter &stream, const v800::BiomeElementData &value)
{
    stream.write<float>(value.noise_freq_scale);
    stream.write<float>(value.noise_lower_bound);
    stream.write<float>(value.noise_upper_bound);
    stream.writeVarInt<std::int32_t>(value.height_min_type);
    stream.write<std::uint16_t>(value.height_min);
    stream.writeVarInt<std::int32_t>(value.height_max_type);
    stream.write<std::uint16_t>(value.height_max);
    Serializer<BiomeSurfaceMaterialData>::serialize(stream, value.adjusted_materials);
}

auto Serializer<v800::BiomeElementData>::deserialize(BinaryReader &stream) -> std::expected<v800::BiomeElementData, std::error_code>
{
    v800::BiomeElementData out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.noise_freq_scale = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.noise_lower_bound = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.noise_upper_bound = static_cast<float>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.height_min_type = static_cast<v800::ExpressionOp>(*v);
    }
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.height_min = static_cast<BiomeStringIndex>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.height_max_type = static_cast<v800::ExpressionOp>(*v);
    }
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.height_max = static_cast<BiomeStringIndex>(*v);
    }
    {
        auto v = Serializer<BiomeSurfaceMaterialData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.adjusted_materials = *v;
    }
    return out;
}

void Serializer<v859::BiomeElementData>::serialize(BinaryWriter &stream, const v859::BiomeElementData &value)
{
    stream.write<float>(value.noise_freq_scale);
    stream.write<float>(value.noise_lower_bound);
    stream.write<float>(value.noise_upper_bound);
    stream.writeVarInt<std::int32_t>(value.height_min_type);
    stream.write<std::uint16_t>(value.height_min);
    stream.writeVarInt<std::int32_t>(value.height_max_type);
    stream.write<std::uint16_t>(value.height_max);
    Serializer<BiomeSurfaceMaterialData>::serialize(stream, value.adjusted_materials);
}

auto Serializer<v859::BiomeElementData>::deserialize(BinaryReader &stream) -> std::expected<v859::BiomeElementData, std::error_code>
{
    v859::BiomeElementData out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.noise_freq_scale = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.noise_lower_bound = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.noise_upper_bound = static_cast<float>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.height_min_type = static_cast<v859::ExpressionOp>(*v);
    }
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.height_min = static_cast<BiomeStringIndex>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.height_max_type = static_cast<v859::ExpressionOp>(*v);
    }
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.height_max = static_cast<BiomeStringIndex>(*v);
    }
    {
        auto v = Serializer<BiomeSurfaceMaterialData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.adjusted_materials = *v;
    }
    return out;
}

void Serializer<base::BiomeSurfaceMaterialAdjustmentData>::serialize(BinaryWriter &stream, const base::BiomeSurfaceMaterialAdjustmentData &value)
{
    stream.writeVarInt<std::uint32_t>(value.adjustments.size());
    for (const auto &e0 : value.adjustments) {
        Serializer<base::BiomeElementData>::serialize(stream, e0);
    }
}

auto Serializer<base::BiomeSurfaceMaterialAdjustmentData>::deserialize(BinaryReader &stream) -> std::expected<base::BiomeSurfaceMaterialAdjustmentData, std::error_code>
{
    base::BiomeSurfaceMaterialAdjustmentData out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.adjustments.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.adjustments.emplace_back();
            auto v = Serializer<base::BiomeElementData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.adjustments.back() = *v;
        }
    }
    return out;
}

void Serializer<v800::BiomeSurfaceMaterialAdjustmentData>::serialize(BinaryWriter &stream, const v800::BiomeSurfaceMaterialAdjustmentData &value)
{
    stream.writeVarInt<std::uint32_t>(value.adjustments.size());
    for (const auto &e0 : value.adjustments) {
        Serializer<v800::BiomeElementData>::serialize(stream, e0);
    }
}

auto Serializer<v800::BiomeSurfaceMaterialAdjustmentData>::deserialize(BinaryReader &stream) -> std::expected<v800::BiomeSurfaceMaterialAdjustmentData, std::error_code>
{
    v800::BiomeSurfaceMaterialAdjustmentData out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.adjustments.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.adjustments.emplace_back();
            auto v = Serializer<v800::BiomeElementData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.adjustments.back() = *v;
        }
    }
    return out;
}

void Serializer<v859::BiomeSurfaceMaterialAdjustmentData>::serialize(BinaryWriter &stream, const v859::BiomeSurfaceMaterialAdjustmentData &value)
{
    stream.writeVarInt<std::uint32_t>(value.adjustments.size());
    for (const auto &e0 : value.adjustments) {
        Serializer<v859::BiomeElementData>::serialize(stream, e0);
    }
}

auto Serializer<v859::BiomeSurfaceMaterialAdjustmentData>::deserialize(BinaryReader &stream) -> std::expected<v859::BiomeSurfaceMaterialAdjustmentData, std::error_code>
{
    v859::BiomeSurfaceMaterialAdjustmentData out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.adjustments.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.adjustments.emplace_back();
            auto v = Serializer<v859::BiomeElementData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.adjustments.back() = *v;
        }
    }
    return out;
}

void Serializer<BiomeWeightedData>::serialize(BinaryWriter &stream, const BiomeWeightedData &value)
{
    stream.write<std::uint16_t>(value.biome_identifier);
    stream.write<std::uint32_t>(value.weight);
}

auto Serializer<BiomeWeightedData>::deserialize(BinaryReader &stream) -> std::expected<BiomeWeightedData, std::error_code>
{
    BiomeWeightedData out;
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.biome_identifier = static_cast<BiomeStringIndex>(*v);
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.weight = static_cast<std::uint32_t>(*v);
    }
    return out;
}

void Serializer<BiomeConditionalTransformationData>::serialize(BinaryWriter &stream, const BiomeConditionalTransformationData &value)
{
    stream.writeVarInt<std::uint32_t>(value.transforms_into.size());
    for (const auto &e0 : value.transforms_into) {
        Serializer<BiomeWeightedData>::serialize(stream, e0);
    }
    stream.write<std::uint16_t>(value.condition_json);
    stream.write<std::uint32_t>(value.min_passing_neighbors);
}

auto Serializer<BiomeConditionalTransformationData>::deserialize(BinaryReader &stream) -> std::expected<BiomeConditionalTransformationData, std::error_code>
{
    BiomeConditionalTransformationData out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.transforms_into.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.transforms_into.emplace_back();
            auto v = Serializer<BiomeWeightedData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.transforms_into.back() = *v;
        }
    }
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.condition_json = static_cast<BiomeStringIndex>(*v);
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.min_passing_neighbors = static_cast<std::uint32_t>(*v);
    }
    return out;
}

void Serializer<BiomeWeightedTemperatureData>::serialize(BinaryWriter &stream, const BiomeWeightedTemperatureData &value)
{
    stream.writeVarInt<std::int32_t>(value.temperature);
    stream.write<std::uint32_t>(value.weight);
}

auto Serializer<BiomeWeightedTemperatureData>::deserialize(BinaryReader &stream) -> std::expected<BiomeWeightedTemperatureData, std::error_code>
{
    BiomeWeightedTemperatureData out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.temperature = static_cast<BiomeTemperatureCategory>(*v);
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.weight = static_cast<std::uint32_t>(*v);
    }
    return out;
}

void Serializer<BiomeOverworldGenRulesData>::serialize(BinaryWriter &stream, const BiomeOverworldGenRulesData &value)
{
    stream.writeVarInt<std::uint32_t>(value.hills_transformations.size());
    for (const auto &e0 : value.hills_transformations) {
        Serializer<BiomeWeightedData>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.mutate_transformations.size());
    for (const auto &e0 : value.mutate_transformations) {
        Serializer<BiomeWeightedData>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.river_transformations.size());
    for (const auto &e0 : value.river_transformations) {
        Serializer<BiomeWeightedData>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.shore_transformations.size());
    for (const auto &e0 : value.shore_transformations) {
        Serializer<BiomeWeightedData>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.pre_hills_edge.size());
    for (const auto &e0 : value.pre_hills_edge) {
        Serializer<BiomeConditionalTransformationData>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.post_shore_edge.size());
    for (const auto &e0 : value.post_shore_edge) {
        Serializer<BiomeConditionalTransformationData>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.climate.size());
    for (const auto &e0 : value.climate) {
        Serializer<BiomeWeightedTemperatureData>::serialize(stream, e0);
    }
}

auto Serializer<BiomeOverworldGenRulesData>::deserialize(BinaryReader &stream) -> std::expected<BiomeOverworldGenRulesData, std::error_code>
{
    BiomeOverworldGenRulesData out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.hills_transformations.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.hills_transformations.emplace_back();
            auto v = Serializer<BiomeWeightedData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.hills_transformations.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.mutate_transformations.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.mutate_transformations.emplace_back();
            auto v = Serializer<BiomeWeightedData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.mutate_transformations.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.river_transformations.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.river_transformations.emplace_back();
            auto v = Serializer<BiomeWeightedData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.river_transformations.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.shore_transformations.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.shore_transformations.emplace_back();
            auto v = Serializer<BiomeWeightedData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.shore_transformations.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.pre_hills_edge.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.pre_hills_edge.emplace_back();
            auto v = Serializer<BiomeConditionalTransformationData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.pre_hills_edge.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.post_shore_edge.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.post_shore_edge.emplace_back();
            auto v = Serializer<BiomeConditionalTransformationData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.post_shore_edge.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.climate.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.climate.emplace_back();
            auto v = Serializer<BiomeWeightedTemperatureData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.climate.back() = *v;
        }
    }
    return out;
}

void Serializer<BiomeMultinoiseGenRulesData>::serialize(BinaryWriter &stream, const BiomeMultinoiseGenRulesData &value)
{
    stream.write<float>(value.temperature);
    stream.write<float>(value.humidity);
    stream.write<float>(value.altitude);
    stream.write<float>(value.weirdness);
    stream.write<float>(value.weight);
}

auto Serializer<BiomeMultinoiseGenRulesData>::deserialize(BinaryReader &stream) -> std::expected<BiomeMultinoiseGenRulesData, std::error_code>
{
    BiomeMultinoiseGenRulesData out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.temperature = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.humidity = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.altitude = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.weirdness = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.weight = static_cast<float>(*v);
    }
    return out;
}

void Serializer<BiomeLegacyWorldGenRulesData>::serialize(BinaryWriter &stream, const BiomeLegacyWorldGenRulesData &value)
{
    stream.writeVarInt<std::uint32_t>(value.legacy_pre_hills_edge.size());
    for (const auto &e0 : value.legacy_pre_hills_edge) {
        Serializer<BiomeConditionalTransformationData>::serialize(stream, e0);
    }
}

auto Serializer<BiomeLegacyWorldGenRulesData>::deserialize(BinaryReader &stream) -> std::expected<BiomeLegacyWorldGenRulesData, std::error_code>
{
    BiomeLegacyWorldGenRulesData out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.legacy_pre_hills_edge.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.legacy_pre_hills_edge.emplace_back();
            auto v = Serializer<BiomeConditionalTransformationData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.legacy_pre_hills_edge.back() = *v;
        }
    }
    return out;
}

void Serializer<BiomeReplacementData>::serialize(BinaryWriter &stream, const BiomeReplacementData &value)
{
    stream.write<std::uint16_t>(value.replacement_biome);
    stream.write<std::uint16_t>(value.dimension);
    stream.writeVarInt<std::uint32_t>(value.target_biomes.size());
    for (const auto &e0 : value.target_biomes) {
        stream.write<std::uint16_t>(e0);
    }
    stream.write<float>(value.amount);
    stream.write<float>(value.noise_frequency_scale);
    stream.write<std::uint32_t>(value.replacement_index);
}

auto Serializer<BiomeReplacementData>::deserialize(BinaryReader &stream) -> std::expected<BiomeReplacementData, std::error_code>
{
    BiomeReplacementData out;
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.replacement_biome = static_cast<BiomeStringIndex>(*v);
    }
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.dimension = static_cast<BiomeStringIndex>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.target_biomes.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.target_biomes.emplace_back();
            auto v = stream.read<std::uint16_t>();
            if (!v) return std::unexpected(v.error());
            out.target_biomes.back() = static_cast<std::uint16_t>(*v);
        }
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.amount = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.noise_frequency_scale = static_cast<float>(*v);
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.replacement_index = static_cast<std::uint32_t>(*v);
    }
    return out;
}

void Serializer<BiomeReplacementsData>::serialize(BinaryWriter &stream, const BiomeReplacementsData &value)
{
    stream.writeVarInt<std::uint32_t>(value.biome_replacements.size());
    for (const auto &e0 : value.biome_replacements) {
        Serializer<BiomeReplacementData>::serialize(stream, e0);
    }
}

auto Serializer<BiomeReplacementsData>::deserialize(BinaryReader &stream) -> std::expected<BiomeReplacementsData, std::error_code>
{
    BiomeReplacementsData out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.biome_replacements.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.biome_replacements.emplace_back();
            auto v = Serializer<BiomeReplacementData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.biome_replacements.back() = *v;
        }
    }
    return out;
}

void Serializer<BiomeTagsData>::serialize(BinaryWriter &stream, const BiomeTagsData &value)
{
    stream.writeVarInt<std::uint32_t>(value.tags.size());
    for (const auto &e0 : value.tags) {
        stream.write<std::uint16_t>(e0);
    }
}

auto Serializer<BiomeTagsData>::deserialize(BinaryReader &stream) -> std::expected<BiomeTagsData, std::error_code>
{
    BiomeTagsData out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.tags.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.tags.emplace_back();
            auto v = stream.read<std::uint16_t>();
            if (!v) return std::unexpected(v.error());
            out.tags.back() = static_cast<std::uint16_t>(*v);
        }
    }
    return out;
}

void Serializer<base::BiomeDefinitionChunkGenData>::serialize(BinaryWriter &stream, const base::BiomeDefinitionChunkGenData &value)
{
    stream.write<bool>(value.climate.has_value());
    if (value.climate.has_value()) {
        Serializer<base::BiomeClimateData>::serialize(stream, (*value.climate));
    }
    stream.write<bool>(value.consolidated_features.has_value());
    if (value.consolidated_features.has_value()) {
        Serializer<base::BiomeConsolidatedFeaturesData>::serialize(stream, (*value.consolidated_features));
    }
    stream.write<bool>(value.mountain_params.has_value());
    if (value.mountain_params.has_value()) {
        Serializer<BiomeMountainParamsData>::serialize(stream, (*value.mountain_params));
    }
    stream.write<bool>(value.surface_material_adjustments.has_value());
    if (value.surface_material_adjustments.has_value()) {
        Serializer<base::BiomeSurfaceMaterialAdjustmentData>::serialize(stream, (*value.surface_material_adjustments));
    }
    stream.write<bool>(value.surface_materials.has_value());
    if (value.surface_materials.has_value()) {
        Serializer<BiomeSurfaceMaterialData>::serialize(stream, (*value.surface_materials));
    }
    stream.write<bool>(value.has_swamp_surface);
    stream.write<bool>(value.has_frozen_ocean_surface);
    stream.write<bool>(value.has_the_end_surface);
    stream.write<bool>(value.mesa_surface.has_value());
    if (value.mesa_surface.has_value()) {
        Serializer<BiomeMesaSurfaceData>::serialize(stream, (*value.mesa_surface));
    }
    stream.write<bool>(value.capped_surface.has_value());
    if (value.capped_surface.has_value()) {
        Serializer<BiomeCappedSurfaceData>::serialize(stream, (*value.capped_surface));
    }
    stream.write<bool>(value.overworld_gen_rules.has_value());
    if (value.overworld_gen_rules.has_value()) {
        Serializer<BiomeOverworldGenRulesData>::serialize(stream, (*value.overworld_gen_rules));
    }
    stream.write<bool>(value.multinoise_gen_rules.has_value());
    if (value.multinoise_gen_rules.has_value()) {
        Serializer<BiomeMultinoiseGenRulesData>::serialize(stream, (*value.multinoise_gen_rules));
    }
    stream.write<bool>(value.legacy_world_gen_rules.has_value());
    if (value.legacy_world_gen_rules.has_value()) {
        Serializer<BiomeLegacyWorldGenRulesData>::serialize(stream, (*value.legacy_world_gen_rules));
    }
}

auto Serializer<base::BiomeDefinitionChunkGenData>::deserialize(BinaryReader &stream) -> std::expected<base::BiomeDefinitionChunkGenData, std::error_code>
{
    base::BiomeDefinitionChunkGenData out;
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            base::BiomeClimateData staged{};
            auto v = Serializer<base::BiomeClimateData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.climate = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            base::BiomeConsolidatedFeaturesData staged{};
            auto v = Serializer<base::BiomeConsolidatedFeaturesData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.consolidated_features = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeMountainParamsData staged{};
            auto v = Serializer<BiomeMountainParamsData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.mountain_params = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            base::BiomeSurfaceMaterialAdjustmentData staged{};
            auto v = Serializer<base::BiomeSurfaceMaterialAdjustmentData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.surface_material_adjustments = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeSurfaceMaterialData staged{};
            auto v = Serializer<BiomeSurfaceMaterialData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.surface_materials = std::move(staged);
        }
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_swamp_surface = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_frozen_ocean_surface = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_the_end_surface = static_cast<bool>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeMesaSurfaceData staged{};
            auto v = Serializer<BiomeMesaSurfaceData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.mesa_surface = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeCappedSurfaceData staged{};
            auto v = Serializer<BiomeCappedSurfaceData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.capped_surface = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeOverworldGenRulesData staged{};
            auto v = Serializer<BiomeOverworldGenRulesData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.overworld_gen_rules = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeMultinoiseGenRulesData staged{};
            auto v = Serializer<BiomeMultinoiseGenRulesData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.multinoise_gen_rules = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeLegacyWorldGenRulesData staged{};
            auto v = Serializer<BiomeLegacyWorldGenRulesData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.legacy_world_gen_rules = std::move(staged);
        }
    }
    return out;
}

void Serializer<v800::BiomeDefinitionChunkGenData>::serialize(BinaryWriter &stream, const v800::BiomeDefinitionChunkGenData &value)
{
    stream.write<bool>(value.climate.has_value());
    if (value.climate.has_value()) {
        Serializer<base::BiomeClimateData>::serialize(stream, (*value.climate));
    }
    stream.write<bool>(value.consolidated_features.has_value());
    if (value.consolidated_features.has_value()) {
        Serializer<v800::BiomeConsolidatedFeaturesData>::serialize(stream, (*value.consolidated_features));
    }
    stream.write<bool>(value.mountain_params.has_value());
    if (value.mountain_params.has_value()) {
        Serializer<BiomeMountainParamsData>::serialize(stream, (*value.mountain_params));
    }
    stream.write<bool>(value.surface_material_adjustments.has_value());
    if (value.surface_material_adjustments.has_value()) {
        Serializer<v800::BiomeSurfaceMaterialAdjustmentData>::serialize(stream, (*value.surface_material_adjustments));
    }
    stream.write<bool>(value.surface_materials.has_value());
    if (value.surface_materials.has_value()) {
        Serializer<BiomeSurfaceMaterialData>::serialize(stream, (*value.surface_materials));
    }
    stream.write<bool>(value.has_swamp_surface);
    stream.write<bool>(value.has_frozen_ocean_surface);
    stream.write<bool>(value.has_the_end_surface);
    stream.write<bool>(value.mesa_surface.has_value());
    if (value.mesa_surface.has_value()) {
        Serializer<BiomeMesaSurfaceData>::serialize(stream, (*value.mesa_surface));
    }
    stream.write<bool>(value.capped_surface.has_value());
    if (value.capped_surface.has_value()) {
        Serializer<BiomeCappedSurfaceData>::serialize(stream, (*value.capped_surface));
    }
    stream.write<bool>(value.overworld_gen_rules.has_value());
    if (value.overworld_gen_rules.has_value()) {
        Serializer<BiomeOverworldGenRulesData>::serialize(stream, (*value.overworld_gen_rules));
    }
    stream.write<bool>(value.multinoise_gen_rules.has_value());
    if (value.multinoise_gen_rules.has_value()) {
        Serializer<BiomeMultinoiseGenRulesData>::serialize(stream, (*value.multinoise_gen_rules));
    }
    stream.write<bool>(value.legacy_world_gen_rules.has_value());
    if (value.legacy_world_gen_rules.has_value()) {
        Serializer<BiomeLegacyWorldGenRulesData>::serialize(stream, (*value.legacy_world_gen_rules));
    }
    stream.write<bool>(value.replace_biomes.has_value());
    if (value.replace_biomes.has_value()) {
        Serializer<BiomeReplacementsData>::serialize(stream, (*value.replace_biomes));
    }
}

auto Serializer<v800::BiomeDefinitionChunkGenData>::deserialize(BinaryReader &stream) -> std::expected<v800::BiomeDefinitionChunkGenData, std::error_code>
{
    v800::BiomeDefinitionChunkGenData out;
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            base::BiomeClimateData staged{};
            auto v = Serializer<base::BiomeClimateData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.climate = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v800::BiomeConsolidatedFeaturesData staged{};
            auto v = Serializer<v800::BiomeConsolidatedFeaturesData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.consolidated_features = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeMountainParamsData staged{};
            auto v = Serializer<BiomeMountainParamsData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.mountain_params = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v800::BiomeSurfaceMaterialAdjustmentData staged{};
            auto v = Serializer<v800::BiomeSurfaceMaterialAdjustmentData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.surface_material_adjustments = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeSurfaceMaterialData staged{};
            auto v = Serializer<BiomeSurfaceMaterialData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.surface_materials = std::move(staged);
        }
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_swamp_surface = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_frozen_ocean_surface = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_the_end_surface = static_cast<bool>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeMesaSurfaceData staged{};
            auto v = Serializer<BiomeMesaSurfaceData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.mesa_surface = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeCappedSurfaceData staged{};
            auto v = Serializer<BiomeCappedSurfaceData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.capped_surface = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeOverworldGenRulesData staged{};
            auto v = Serializer<BiomeOverworldGenRulesData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.overworld_gen_rules = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeMultinoiseGenRulesData staged{};
            auto v = Serializer<BiomeMultinoiseGenRulesData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.multinoise_gen_rules = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeLegacyWorldGenRulesData staged{};
            auto v = Serializer<BiomeLegacyWorldGenRulesData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.legacy_world_gen_rules = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeReplacementsData staged{};
            auto v = Serializer<BiomeReplacementsData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.replace_biomes = std::move(staged);
        }
    }
    return out;
}

void Serializer<v844::BiomeDefinitionChunkGenData>::serialize(BinaryWriter &stream, const v844::BiomeDefinitionChunkGenData &value)
{
    stream.write<bool>(value.climate.has_value());
    if (value.climate.has_value()) {
        Serializer<v844::BiomeClimateData>::serialize(stream, (*value.climate));
    }
    stream.write<bool>(value.consolidated_features.has_value());
    if (value.consolidated_features.has_value()) {
        Serializer<v800::BiomeConsolidatedFeaturesData>::serialize(stream, (*value.consolidated_features));
    }
    stream.write<bool>(value.mountain_params.has_value());
    if (value.mountain_params.has_value()) {
        Serializer<BiomeMountainParamsData>::serialize(stream, (*value.mountain_params));
    }
    stream.write<bool>(value.surface_material_adjustments.has_value());
    if (value.surface_material_adjustments.has_value()) {
        Serializer<v800::BiomeSurfaceMaterialAdjustmentData>::serialize(stream, (*value.surface_material_adjustments));
    }
    stream.write<bool>(value.surface_materials.has_value());
    if (value.surface_materials.has_value()) {
        Serializer<BiomeSurfaceMaterialData>::serialize(stream, (*value.surface_materials));
    }
    stream.write<bool>(value.has_default_overworld_surface);
    stream.write<bool>(value.has_swamp_surface);
    stream.write<bool>(value.has_frozen_ocean_surface);
    stream.write<bool>(value.has_the_end_surface);
    stream.write<bool>(value.mesa_surface.has_value());
    if (value.mesa_surface.has_value()) {
        Serializer<BiomeMesaSurfaceData>::serialize(stream, (*value.mesa_surface));
    }
    stream.write<bool>(value.capped_surface.has_value());
    if (value.capped_surface.has_value()) {
        Serializer<BiomeCappedSurfaceData>::serialize(stream, (*value.capped_surface));
    }
    stream.write<bool>(value.overworld_gen_rules.has_value());
    if (value.overworld_gen_rules.has_value()) {
        Serializer<BiomeOverworldGenRulesData>::serialize(stream, (*value.overworld_gen_rules));
    }
    stream.write<bool>(value.multinoise_gen_rules.has_value());
    if (value.multinoise_gen_rules.has_value()) {
        Serializer<BiomeMultinoiseGenRulesData>::serialize(stream, (*value.multinoise_gen_rules));
    }
    stream.write<bool>(value.legacy_world_gen_rules.has_value());
    if (value.legacy_world_gen_rules.has_value()) {
        Serializer<BiomeLegacyWorldGenRulesData>::serialize(stream, (*value.legacy_world_gen_rules));
    }
    stream.write<bool>(value.replace_biomes.has_value());
    if (value.replace_biomes.has_value()) {
        Serializer<BiomeReplacementsData>::serialize(stream, (*value.replace_biomes));
    }
}

auto Serializer<v844::BiomeDefinitionChunkGenData>::deserialize(BinaryReader &stream) -> std::expected<v844::BiomeDefinitionChunkGenData, std::error_code>
{
    v844::BiomeDefinitionChunkGenData out;
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v844::BiomeClimateData staged{};
            auto v = Serializer<v844::BiomeClimateData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.climate = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v800::BiomeConsolidatedFeaturesData staged{};
            auto v = Serializer<v800::BiomeConsolidatedFeaturesData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.consolidated_features = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeMountainParamsData staged{};
            auto v = Serializer<BiomeMountainParamsData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.mountain_params = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v800::BiomeSurfaceMaterialAdjustmentData staged{};
            auto v = Serializer<v800::BiomeSurfaceMaterialAdjustmentData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.surface_material_adjustments = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeSurfaceMaterialData staged{};
            auto v = Serializer<BiomeSurfaceMaterialData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.surface_materials = std::move(staged);
        }
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_default_overworld_surface = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_swamp_surface = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_frozen_ocean_surface = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_the_end_surface = static_cast<bool>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeMesaSurfaceData staged{};
            auto v = Serializer<BiomeMesaSurfaceData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.mesa_surface = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeCappedSurfaceData staged{};
            auto v = Serializer<BiomeCappedSurfaceData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.capped_surface = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeOverworldGenRulesData staged{};
            auto v = Serializer<BiomeOverworldGenRulesData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.overworld_gen_rules = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeMultinoiseGenRulesData staged{};
            auto v = Serializer<BiomeMultinoiseGenRulesData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.multinoise_gen_rules = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeLegacyWorldGenRulesData staged{};
            auto v = Serializer<BiomeLegacyWorldGenRulesData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.legacy_world_gen_rules = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeReplacementsData staged{};
            auto v = Serializer<BiomeReplacementsData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.replace_biomes = std::move(staged);
        }
    }
    return out;
}

void Serializer<v859::BiomeDefinitionChunkGenData>::serialize(BinaryWriter &stream, const v859::BiomeDefinitionChunkGenData &value)
{
    stream.write<bool>(value.climate.has_value());
    if (value.climate.has_value()) {
        Serializer<v844::BiomeClimateData>::serialize(stream, (*value.climate));
    }
    stream.write<bool>(value.consolidated_features.has_value());
    if (value.consolidated_features.has_value()) {
        Serializer<v859::BiomeConsolidatedFeaturesData>::serialize(stream, (*value.consolidated_features));
    }
    stream.write<bool>(value.mountain_params.has_value());
    if (value.mountain_params.has_value()) {
        Serializer<BiomeMountainParamsData>::serialize(stream, (*value.mountain_params));
    }
    stream.write<bool>(value.surface_material_adjustments.has_value());
    if (value.surface_material_adjustments.has_value()) {
        Serializer<v859::BiomeSurfaceMaterialAdjustmentData>::serialize(stream, (*value.surface_material_adjustments));
    }
    stream.write<bool>(value.surface_materials.has_value());
    if (value.surface_materials.has_value()) {
        Serializer<BiomeSurfaceMaterialData>::serialize(stream, (*value.surface_materials));
    }
    stream.write<bool>(value.has_default_overworld_surface);
    stream.write<bool>(value.has_swamp_surface);
    stream.write<bool>(value.has_frozen_ocean_surface);
    stream.write<bool>(value.has_the_end_surface);
    stream.write<bool>(value.mesa_surface.has_value());
    if (value.mesa_surface.has_value()) {
        Serializer<BiomeMesaSurfaceData>::serialize(stream, (*value.mesa_surface));
    }
    stream.write<bool>(value.capped_surface.has_value());
    if (value.capped_surface.has_value()) {
        Serializer<BiomeCappedSurfaceData>::serialize(stream, (*value.capped_surface));
    }
    stream.write<bool>(value.overworld_gen_rules.has_value());
    if (value.overworld_gen_rules.has_value()) {
        Serializer<BiomeOverworldGenRulesData>::serialize(stream, (*value.overworld_gen_rules));
    }
    stream.write<bool>(value.multinoise_gen_rules.has_value());
    if (value.multinoise_gen_rules.has_value()) {
        Serializer<BiomeMultinoiseGenRulesData>::serialize(stream, (*value.multinoise_gen_rules));
    }
    stream.write<bool>(value.legacy_world_gen_rules.has_value());
    if (value.legacy_world_gen_rules.has_value()) {
        Serializer<BiomeLegacyWorldGenRulesData>::serialize(stream, (*value.legacy_world_gen_rules));
    }
    stream.write<bool>(value.replace_biomes.has_value());
    if (value.replace_biomes.has_value()) {
        Serializer<BiomeReplacementsData>::serialize(stream, (*value.replace_biomes));
    }
}

auto Serializer<v859::BiomeDefinitionChunkGenData>::deserialize(BinaryReader &stream) -> std::expected<v859::BiomeDefinitionChunkGenData, std::error_code>
{
    v859::BiomeDefinitionChunkGenData out;
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v844::BiomeClimateData staged{};
            auto v = Serializer<v844::BiomeClimateData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.climate = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v859::BiomeConsolidatedFeaturesData staged{};
            auto v = Serializer<v859::BiomeConsolidatedFeaturesData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.consolidated_features = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeMountainParamsData staged{};
            auto v = Serializer<BiomeMountainParamsData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.mountain_params = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v859::BiomeSurfaceMaterialAdjustmentData staged{};
            auto v = Serializer<v859::BiomeSurfaceMaterialAdjustmentData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.surface_material_adjustments = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeSurfaceMaterialData staged{};
            auto v = Serializer<BiomeSurfaceMaterialData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.surface_materials = std::move(staged);
        }
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_default_overworld_surface = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_swamp_surface = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_frozen_ocean_surface = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_the_end_surface = static_cast<bool>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeMesaSurfaceData staged{};
            auto v = Serializer<BiomeMesaSurfaceData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.mesa_surface = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeCappedSurfaceData staged{};
            auto v = Serializer<BiomeCappedSurfaceData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.capped_surface = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeOverworldGenRulesData staged{};
            auto v = Serializer<BiomeOverworldGenRulesData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.overworld_gen_rules = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeMultinoiseGenRulesData staged{};
            auto v = Serializer<BiomeMultinoiseGenRulesData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.multinoise_gen_rules = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeLegacyWorldGenRulesData staged{};
            auto v = Serializer<BiomeLegacyWorldGenRulesData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.legacy_world_gen_rules = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeReplacementsData staged{};
            auto v = Serializer<BiomeReplacementsData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.replace_biomes = std::move(staged);
        }
    }
    return out;
}

void Serializer<v924::BiomeDefinitionChunkGenData>::serialize(BinaryWriter &stream, const v924::BiomeDefinitionChunkGenData &value)
{
    stream.write<bool>(value.climate.has_value());
    if (value.climate.has_value()) {
        Serializer<v844::BiomeClimateData>::serialize(stream, (*value.climate));
    }
    stream.write<bool>(value.consolidated_features.has_value());
    if (value.consolidated_features.has_value()) {
        Serializer<v859::BiomeConsolidatedFeaturesData>::serialize(stream, (*value.consolidated_features));
    }
    stream.write<bool>(value.mountain_params.has_value());
    if (value.mountain_params.has_value()) {
        Serializer<BiomeMountainParamsData>::serialize(stream, (*value.mountain_params));
    }
    stream.write<bool>(value.surface_material_adjustments.has_value());
    if (value.surface_material_adjustments.has_value()) {
        Serializer<v859::BiomeSurfaceMaterialAdjustmentData>::serialize(stream, (*value.surface_material_adjustments));
    }
    stream.write<bool>(value.surface_materials.has_value());
    if (value.surface_materials.has_value()) {
        Serializer<BiomeSurfaceMaterialData>::serialize(stream, (*value.surface_materials));
    }
    stream.write<bool>(value.has_default_overworld_surface);
    stream.write<bool>(value.has_swamp_surface);
    stream.write<bool>(value.has_frozen_ocean_surface);
    stream.write<bool>(value.has_the_end_surface);
    stream.write<bool>(value.mesa_surface.has_value());
    if (value.mesa_surface.has_value()) {
        Serializer<BiomeMesaSurfaceData>::serialize(stream, (*value.mesa_surface));
    }
    stream.write<bool>(value.capped_surface.has_value());
    if (value.capped_surface.has_value()) {
        Serializer<BiomeCappedSurfaceData>::serialize(stream, (*value.capped_surface));
    }
    stream.write<bool>(value.overworld_gen_rules.has_value());
    if (value.overworld_gen_rules.has_value()) {
        Serializer<BiomeOverworldGenRulesData>::serialize(stream, (*value.overworld_gen_rules));
    }
    stream.write<bool>(value.multinoise_gen_rules.has_value());
    if (value.multinoise_gen_rules.has_value()) {
        Serializer<BiomeMultinoiseGenRulesData>::serialize(stream, (*value.multinoise_gen_rules));
    }
    stream.write<bool>(value.legacy_world_gen_rules.has_value());
    if (value.legacy_world_gen_rules.has_value()) {
        Serializer<BiomeLegacyWorldGenRulesData>::serialize(stream, (*value.legacy_world_gen_rules));
    }
    stream.write<bool>(value.replace_biomes.has_value());
    if (value.replace_biomes.has_value()) {
        Serializer<BiomeReplacementsData>::serialize(stream, (*value.replace_biomes));
    }
    stream.write<bool>(value.village_type.has_value());
    if (value.village_type.has_value()) {
        stream.write<std::uint8_t>((*value.village_type));
    }
}

auto Serializer<v924::BiomeDefinitionChunkGenData>::deserialize(BinaryReader &stream) -> std::expected<v924::BiomeDefinitionChunkGenData, std::error_code>
{
    v924::BiomeDefinitionChunkGenData out;
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v844::BiomeClimateData staged{};
            auto v = Serializer<v844::BiomeClimateData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.climate = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v859::BiomeConsolidatedFeaturesData staged{};
            auto v = Serializer<v859::BiomeConsolidatedFeaturesData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.consolidated_features = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeMountainParamsData staged{};
            auto v = Serializer<BiomeMountainParamsData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.mountain_params = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v859::BiomeSurfaceMaterialAdjustmentData staged{};
            auto v = Serializer<v859::BiomeSurfaceMaterialAdjustmentData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.surface_material_adjustments = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeSurfaceMaterialData staged{};
            auto v = Serializer<BiomeSurfaceMaterialData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.surface_materials = std::move(staged);
        }
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_default_overworld_surface = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_swamp_surface = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_frozen_ocean_surface = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_the_end_surface = static_cast<bool>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeMesaSurfaceData staged{};
            auto v = Serializer<BiomeMesaSurfaceData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.mesa_surface = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeCappedSurfaceData staged{};
            auto v = Serializer<BiomeCappedSurfaceData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.capped_surface = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeOverworldGenRulesData staged{};
            auto v = Serializer<BiomeOverworldGenRulesData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.overworld_gen_rules = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeMultinoiseGenRulesData staged{};
            auto v = Serializer<BiomeMultinoiseGenRulesData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.multinoise_gen_rules = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeLegacyWorldGenRulesData staged{};
            auto v = Serializer<BiomeLegacyWorldGenRulesData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.legacy_world_gen_rules = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeReplacementsData staged{};
            auto v = Serializer<BiomeReplacementsData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.replace_biomes = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            VillageType staged{};
            auto v = stream.read<std::uint8_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<VillageType>(*v);
            out.village_type = std::move(staged);
        }
    }
    return out;
}

void Serializer<v975::BiomeDefinitionChunkGenData>::serialize(BinaryWriter &stream, const v975::BiomeDefinitionChunkGenData &value)
{
    stream.write<bool>(value.climate.has_value());
    if (value.climate.has_value()) {
        Serializer<v844::BiomeClimateData>::serialize(stream, (*value.climate));
    }
    stream.write<bool>(value.consolidated_features.has_value());
    if (value.consolidated_features.has_value()) {
        Serializer<v859::BiomeConsolidatedFeaturesData>::serialize(stream, (*value.consolidated_features));
    }
    stream.write<bool>(value.mountain_params.has_value());
    if (value.mountain_params.has_value()) {
        Serializer<BiomeMountainParamsData>::serialize(stream, (*value.mountain_params));
    }
    stream.write<bool>(value.surface_material_adjustments.has_value());
    if (value.surface_material_adjustments.has_value()) {
        Serializer<v859::BiomeSurfaceMaterialAdjustmentData>::serialize(stream, (*value.surface_material_adjustments));
    }
    stream.write<bool>(value.overworld_gen_rules.has_value());
    if (value.overworld_gen_rules.has_value()) {
        Serializer<BiomeOverworldGenRulesData>::serialize(stream, (*value.overworld_gen_rules));
    }
    stream.write<bool>(value.multinoise_gen_rules.has_value());
    if (value.multinoise_gen_rules.has_value()) {
        Serializer<BiomeMultinoiseGenRulesData>::serialize(stream, (*value.multinoise_gen_rules));
    }
    stream.write<bool>(value.legacy_world_gen_rules.has_value());
    if (value.legacy_world_gen_rules.has_value()) {
        Serializer<BiomeLegacyWorldGenRulesData>::serialize(stream, (*value.legacy_world_gen_rules));
    }
    stream.write<bool>(value.replace_biomes.has_value());
    if (value.replace_biomes.has_value()) {
        Serializer<BiomeReplacementsData>::serialize(stream, (*value.replace_biomes));
    }
    stream.write<bool>(value.village_type.has_value());
    if (value.village_type.has_value()) {
        stream.write<std::uint8_t>((*value.village_type));
    }
    stream.write<bool>(value.surface_builder_data.has_value());
    if (value.surface_builder_data.has_value()) {
        Serializer<base::BiomeSurfaceBuilderData>::serialize(stream, (*value.surface_builder_data));
    }
    stream.write<bool>(value.subsurface_builder_data.has_value());
    if (value.subsurface_builder_data.has_value()) {
        Serializer<base::BiomeSurfaceBuilderData>::serialize(stream, (*value.subsurface_builder_data));
    }
}

auto Serializer<v975::BiomeDefinitionChunkGenData>::deserialize(BinaryReader &stream) -> std::expected<v975::BiomeDefinitionChunkGenData, std::error_code>
{
    v975::BiomeDefinitionChunkGenData out;
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v844::BiomeClimateData staged{};
            auto v = Serializer<v844::BiomeClimateData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.climate = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v859::BiomeConsolidatedFeaturesData staged{};
            auto v = Serializer<v859::BiomeConsolidatedFeaturesData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.consolidated_features = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeMountainParamsData staged{};
            auto v = Serializer<BiomeMountainParamsData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.mountain_params = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v859::BiomeSurfaceMaterialAdjustmentData staged{};
            auto v = Serializer<v859::BiomeSurfaceMaterialAdjustmentData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.surface_material_adjustments = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeOverworldGenRulesData staged{};
            auto v = Serializer<BiomeOverworldGenRulesData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.overworld_gen_rules = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeMultinoiseGenRulesData staged{};
            auto v = Serializer<BiomeMultinoiseGenRulesData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.multinoise_gen_rules = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeLegacyWorldGenRulesData staged{};
            auto v = Serializer<BiomeLegacyWorldGenRulesData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.legacy_world_gen_rules = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeReplacementsData staged{};
            auto v = Serializer<BiomeReplacementsData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.replace_biomes = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            VillageType staged{};
            auto v = stream.read<std::uint8_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<VillageType>(*v);
            out.village_type = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            base::BiomeSurfaceBuilderData staged{};
            auto v = Serializer<base::BiomeSurfaceBuilderData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.surface_builder_data = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            base::BiomeSurfaceBuilderData staged{};
            auto v = Serializer<base::BiomeSurfaceBuilderData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.subsurface_builder_data = std::move(staged);
        }
    }
    return out;
}

void Serializer<v1001::BiomeDefinitionChunkGenData>::serialize(BinaryWriter &stream, const v1001::BiomeDefinitionChunkGenData &value)
{
    stream.write<bool>(value.climate.has_value());
    if (value.climate.has_value()) {
        Serializer<v844::BiomeClimateData>::serialize(stream, (*value.climate));
    }
    stream.write<bool>(value.consolidated_features.has_value());
    if (value.consolidated_features.has_value()) {
        Serializer<v859::BiomeConsolidatedFeaturesData>::serialize(stream, (*value.consolidated_features));
    }
    stream.write<bool>(value.mountain_params.has_value());
    if (value.mountain_params.has_value()) {
        Serializer<BiomeMountainParamsData>::serialize(stream, (*value.mountain_params));
    }
    stream.write<bool>(value.surface_material_adjustments.has_value());
    if (value.surface_material_adjustments.has_value()) {
        Serializer<v859::BiomeSurfaceMaterialAdjustmentData>::serialize(stream, (*value.surface_material_adjustments));
    }
    stream.write<bool>(value.overworld_gen_rules.has_value());
    if (value.overworld_gen_rules.has_value()) {
        Serializer<BiomeOverworldGenRulesData>::serialize(stream, (*value.overworld_gen_rules));
    }
    stream.write<bool>(value.multinoise_gen_rules.has_value());
    if (value.multinoise_gen_rules.has_value()) {
        Serializer<BiomeMultinoiseGenRulesData>::serialize(stream, (*value.multinoise_gen_rules));
    }
    stream.write<bool>(value.legacy_world_gen_rules.has_value());
    if (value.legacy_world_gen_rules.has_value()) {
        Serializer<BiomeLegacyWorldGenRulesData>::serialize(stream, (*value.legacy_world_gen_rules));
    }
    stream.write<bool>(value.replace_biomes.has_value());
    if (value.replace_biomes.has_value()) {
        Serializer<BiomeReplacementsData>::serialize(stream, (*value.replace_biomes));
    }
    stream.write<bool>(value.village_type.has_value());
    if (value.village_type.has_value()) {
        stream.write<std::uint8_t>((*value.village_type));
    }
    stream.write<bool>(value.surface_builder_data.has_value());
    if (value.surface_builder_data.has_value()) {
        Serializer<v1001::BiomeSurfaceBuilderData>::serialize(stream, (*value.surface_builder_data));
    }
    stream.write<bool>(value.subsurface_builder_data.has_value());
    if (value.subsurface_builder_data.has_value()) {
        Serializer<v1001::BiomeSurfaceBuilderData>::serialize(stream, (*value.subsurface_builder_data));
    }
}

auto Serializer<v1001::BiomeDefinitionChunkGenData>::deserialize(BinaryReader &stream) -> std::expected<v1001::BiomeDefinitionChunkGenData, std::error_code>
{
    v1001::BiomeDefinitionChunkGenData out;
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v844::BiomeClimateData staged{};
            auto v = Serializer<v844::BiomeClimateData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.climate = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v859::BiomeConsolidatedFeaturesData staged{};
            auto v = Serializer<v859::BiomeConsolidatedFeaturesData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.consolidated_features = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeMountainParamsData staged{};
            auto v = Serializer<BiomeMountainParamsData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.mountain_params = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v859::BiomeSurfaceMaterialAdjustmentData staged{};
            auto v = Serializer<v859::BiomeSurfaceMaterialAdjustmentData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.surface_material_adjustments = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeOverworldGenRulesData staged{};
            auto v = Serializer<BiomeOverworldGenRulesData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.overworld_gen_rules = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeMultinoiseGenRulesData staged{};
            auto v = Serializer<BiomeMultinoiseGenRulesData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.multinoise_gen_rules = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeLegacyWorldGenRulesData staged{};
            auto v = Serializer<BiomeLegacyWorldGenRulesData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.legacy_world_gen_rules = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeReplacementsData staged{};
            auto v = Serializer<BiomeReplacementsData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.replace_biomes = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            VillageType staged{};
            auto v = stream.read<std::uint8_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<VillageType>(*v);
            out.village_type = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v1001::BiomeSurfaceBuilderData staged{};
            auto v = Serializer<v1001::BiomeSurfaceBuilderData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.surface_builder_data = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v1001::BiomeSurfaceBuilderData staged{};
            auto v = Serializer<v1001::BiomeSurfaceBuilderData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.subsurface_builder_data = std::move(staged);
        }
    }
    return out;
}

void Serializer<base::BiomeDefinitionData>::serialize(BinaryWriter &stream, const base::BiomeDefinitionData &value)
{
    stream.write<bool>(value.id.has_value());
    if (value.id.has_value()) {
        stream.write<std::uint16_t>((*value.id));
    }
    stream.write<float>(value.temperature);
    stream.write<float>(value.downfall);
    stream.write<float>(value.red_spore_density);
    stream.write<float>(value.blue_spore_density);
    stream.write<float>(value.ash_density);
    stream.write<float>(value.white_ash_density);
    stream.write<float>(value.depth);
    stream.write<float>(value.scale);
    stream.write<std::int32_t>(value.map_water_color_argb);
    stream.write<bool>(value.rain);
    stream.write<bool>(value.tags.has_value());
    if (value.tags.has_value()) {
        Serializer<BiomeTagsData>::serialize(stream, (*value.tags));
    }
    stream.write<bool>(value.chunk_gen_data.has_value());
    if (value.chunk_gen_data.has_value()) {
        Serializer<base::BiomeDefinitionChunkGenData>::serialize(stream, (*value.chunk_gen_data));
    }
}

auto Serializer<base::BiomeDefinitionData>::deserialize(BinaryReader &stream) -> std::expected<base::BiomeDefinitionData, std::error_code>
{
    base::BiomeDefinitionData out;
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::uint16_t staged{};
            auto v = stream.read<std::uint16_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<std::uint16_t>(*v);
            out.id = std::move(staged);
        }
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.temperature = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.downfall = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.red_spore_density = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.blue_spore_density = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.ash_density = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.white_ash_density = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.depth = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.scale = static_cast<float>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.map_water_color_argb = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.rain = static_cast<bool>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeTagsData staged{};
            auto v = Serializer<BiomeTagsData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.tags = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            base::BiomeDefinitionChunkGenData staged{};
            auto v = Serializer<base::BiomeDefinitionChunkGenData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.chunk_gen_data = std::move(staged);
        }
    }
    return out;
}

void Serializer<v800::BiomeDefinitionData>::serialize(BinaryWriter &stream, const v800::BiomeDefinitionData &value)
{
    stream.write<bool>(value.id.has_value());
    if (value.id.has_value()) {
        stream.write<std::uint16_t>((*value.id));
    }
    stream.write<float>(value.temperature);
    stream.write<float>(value.downfall);
    stream.write<float>(value.red_spore_density);
    stream.write<float>(value.blue_spore_density);
    stream.write<float>(value.ash_density);
    stream.write<float>(value.white_ash_density);
    stream.write<float>(value.depth);
    stream.write<float>(value.scale);
    stream.write<std::int32_t>(value.map_water_color_argb);
    stream.write<bool>(value.rain);
    stream.write<bool>(value.tags.has_value());
    if (value.tags.has_value()) {
        Serializer<BiomeTagsData>::serialize(stream, (*value.tags));
    }
    stream.write<bool>(value.chunk_gen_data.has_value());
    if (value.chunk_gen_data.has_value()) {
        Serializer<v800::BiomeDefinitionChunkGenData>::serialize(stream, (*value.chunk_gen_data));
    }
}

auto Serializer<v800::BiomeDefinitionData>::deserialize(BinaryReader &stream) -> std::expected<v800::BiomeDefinitionData, std::error_code>
{
    v800::BiomeDefinitionData out;
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::uint16_t staged{};
            auto v = stream.read<std::uint16_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<std::uint16_t>(*v);
            out.id = std::move(staged);
        }
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.temperature = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.downfall = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.red_spore_density = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.blue_spore_density = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.ash_density = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.white_ash_density = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.depth = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.scale = static_cast<float>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.map_water_color_argb = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.rain = static_cast<bool>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeTagsData staged{};
            auto v = Serializer<BiomeTagsData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.tags = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v800::BiomeDefinitionChunkGenData staged{};
            auto v = Serializer<v800::BiomeDefinitionChunkGenData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.chunk_gen_data = std::move(staged);
        }
    }
    return out;
}

void Serializer<v827::BiomeDefinitionData>::serialize(BinaryWriter &stream, const v827::BiomeDefinitionData &value)
{
    stream.write<std::uint16_t>(value.id);
    stream.write<float>(value.temperature);
    stream.write<float>(value.downfall);
    stream.write<float>(value.red_spore_density);
    stream.write<float>(value.blue_spore_density);
    stream.write<float>(value.ash_density);
    stream.write<float>(value.white_ash_density);
    stream.write<float>(value.depth);
    stream.write<float>(value.scale);
    stream.write<std::int32_t>(value.map_water_color_argb);
    stream.write<bool>(value.rain);
    stream.write<bool>(value.tags.has_value());
    if (value.tags.has_value()) {
        Serializer<BiomeTagsData>::serialize(stream, (*value.tags));
    }
    stream.write<bool>(value.chunk_gen_data.has_value());
    if (value.chunk_gen_data.has_value()) {
        Serializer<v800::BiomeDefinitionChunkGenData>::serialize(stream, (*value.chunk_gen_data));
    }
}

auto Serializer<v827::BiomeDefinitionData>::deserialize(BinaryReader &stream) -> std::expected<v827::BiomeDefinitionData, std::error_code>
{
    v827::BiomeDefinitionData out;
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.id = static_cast<std::uint16_t>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.temperature = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.downfall = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.red_spore_density = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.blue_spore_density = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.ash_density = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.white_ash_density = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.depth = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.scale = static_cast<float>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.map_water_color_argb = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.rain = static_cast<bool>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeTagsData staged{};
            auto v = Serializer<BiomeTagsData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.tags = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v800::BiomeDefinitionChunkGenData staged{};
            auto v = Serializer<v800::BiomeDefinitionChunkGenData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.chunk_gen_data = std::move(staged);
        }
    }
    return out;
}

void Serializer<v844::BiomeDefinitionData>::serialize(BinaryWriter &stream, const v844::BiomeDefinitionData &value)
{
    stream.write<std::uint16_t>(value.id);
    stream.write<float>(value.temperature);
    stream.write<float>(value.downfall);
    stream.write<float>(value.foliage_snow);
    stream.write<float>(value.depth);
    stream.write<float>(value.scale);
    stream.write<std::int32_t>(value.map_water_color_argb);
    stream.write<bool>(value.rain);
    stream.write<bool>(value.tags.has_value());
    if (value.tags.has_value()) {
        Serializer<BiomeTagsData>::serialize(stream, (*value.tags));
    }
    stream.write<bool>(value.chunk_gen_data.has_value());
    if (value.chunk_gen_data.has_value()) {
        Serializer<v844::BiomeDefinitionChunkGenData>::serialize(stream, (*value.chunk_gen_data));
    }
}

auto Serializer<v844::BiomeDefinitionData>::deserialize(BinaryReader &stream) -> std::expected<v844::BiomeDefinitionData, std::error_code>
{
    v844::BiomeDefinitionData out;
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.id = static_cast<std::uint16_t>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.temperature = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.downfall = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.foliage_snow = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.depth = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.scale = static_cast<float>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.map_water_color_argb = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.rain = static_cast<bool>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeTagsData staged{};
            auto v = Serializer<BiomeTagsData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.tags = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v844::BiomeDefinitionChunkGenData staged{};
            auto v = Serializer<v844::BiomeDefinitionChunkGenData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.chunk_gen_data = std::move(staged);
        }
    }
    return out;
}

void Serializer<v859::BiomeDefinitionData>::serialize(BinaryWriter &stream, const v859::BiomeDefinitionData &value)
{
    stream.write<std::uint16_t>(value.id);
    stream.write<float>(value.temperature);
    stream.write<float>(value.downfall);
    stream.write<float>(value.foliage_snow);
    stream.write<float>(value.depth);
    stream.write<float>(value.scale);
    stream.write<std::int32_t>(value.map_water_color_argb);
    stream.write<bool>(value.rain);
    stream.write<bool>(value.tags.has_value());
    if (value.tags.has_value()) {
        Serializer<BiomeTagsData>::serialize(stream, (*value.tags));
    }
    stream.write<bool>(value.chunk_gen_data.has_value());
    if (value.chunk_gen_data.has_value()) {
        Serializer<v859::BiomeDefinitionChunkGenData>::serialize(stream, (*value.chunk_gen_data));
    }
}

auto Serializer<v859::BiomeDefinitionData>::deserialize(BinaryReader &stream) -> std::expected<v859::BiomeDefinitionData, std::error_code>
{
    v859::BiomeDefinitionData out;
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.id = static_cast<std::uint16_t>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.temperature = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.downfall = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.foliage_snow = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.depth = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.scale = static_cast<float>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.map_water_color_argb = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.rain = static_cast<bool>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeTagsData staged{};
            auto v = Serializer<BiomeTagsData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.tags = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v859::BiomeDefinitionChunkGenData staged{};
            auto v = Serializer<v859::BiomeDefinitionChunkGenData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.chunk_gen_data = std::move(staged);
        }
    }
    return out;
}

void Serializer<v924::BiomeDefinitionData>::serialize(BinaryWriter &stream, const v924::BiomeDefinitionData &value)
{
    stream.write<std::uint16_t>(value.id);
    stream.write<float>(value.temperature);
    stream.write<float>(value.downfall);
    stream.write<float>(value.foliage_snow);
    stream.write<float>(value.depth);
    stream.write<float>(value.scale);
    stream.write<std::int32_t>(value.map_water_color_argb);
    stream.write<bool>(value.rain);
    stream.write<bool>(value.tags.has_value());
    if (value.tags.has_value()) {
        Serializer<BiomeTagsData>::serialize(stream, (*value.tags));
    }
    stream.write<bool>(value.chunk_gen_data.has_value());
    if (value.chunk_gen_data.has_value()) {
        Serializer<v924::BiomeDefinitionChunkGenData>::serialize(stream, (*value.chunk_gen_data));
    }
}

auto Serializer<v924::BiomeDefinitionData>::deserialize(BinaryReader &stream) -> std::expected<v924::BiomeDefinitionData, std::error_code>
{
    v924::BiomeDefinitionData out;
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.id = static_cast<std::uint16_t>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.temperature = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.downfall = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.foliage_snow = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.depth = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.scale = static_cast<float>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.map_water_color_argb = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.rain = static_cast<bool>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeTagsData staged{};
            auto v = Serializer<BiomeTagsData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.tags = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v924::BiomeDefinitionChunkGenData staged{};
            auto v = Serializer<v924::BiomeDefinitionChunkGenData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.chunk_gen_data = std::move(staged);
        }
    }
    return out;
}

void Serializer<v975::BiomeDefinitionData>::serialize(BinaryWriter &stream, const v975::BiomeDefinitionData &value)
{
    stream.write<std::uint16_t>(value.id);
    stream.write<float>(value.temperature);
    stream.write<float>(value.downfall);
    stream.write<float>(value.foliage_snow);
    stream.write<float>(value.depth);
    stream.write<float>(value.scale);
    stream.write<std::int32_t>(value.map_water_color_argb);
    stream.write<bool>(value.rain);
    stream.write<bool>(value.tags.has_value());
    if (value.tags.has_value()) {
        Serializer<BiomeTagsData>::serialize(stream, (*value.tags));
    }
    stream.write<bool>(value.chunk_gen_data.has_value());
    if (value.chunk_gen_data.has_value()) {
        Serializer<v975::BiomeDefinitionChunkGenData>::serialize(stream, (*value.chunk_gen_data));
    }
}

auto Serializer<v975::BiomeDefinitionData>::deserialize(BinaryReader &stream) -> std::expected<v975::BiomeDefinitionData, std::error_code>
{
    v975::BiomeDefinitionData out;
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.id = static_cast<std::uint16_t>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.temperature = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.downfall = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.foliage_snow = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.depth = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.scale = static_cast<float>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.map_water_color_argb = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.rain = static_cast<bool>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeTagsData staged{};
            auto v = Serializer<BiomeTagsData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.tags = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v975::BiomeDefinitionChunkGenData staged{};
            auto v = Serializer<v975::BiomeDefinitionChunkGenData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.chunk_gen_data = std::move(staged);
        }
    }
    return out;
}

void Serializer<v1001::BiomeDefinitionData>::serialize(BinaryWriter &stream, const v1001::BiomeDefinitionData &value)
{
    stream.write<std::uint16_t>(value.id);
    stream.write<float>(value.temperature);
    stream.write<float>(value.downfall);
    stream.write<float>(value.foliage_snow);
    stream.write<float>(value.depth);
    stream.write<float>(value.scale);
    stream.write<std::int32_t>(value.map_water_color_argb);
    stream.write<bool>(value.rain);
    stream.write<bool>(value.tags.has_value());
    if (value.tags.has_value()) {
        Serializer<BiomeTagsData>::serialize(stream, (*value.tags));
    }
    stream.write<bool>(value.chunk_gen_data.has_value());
    if (value.chunk_gen_data.has_value()) {
        Serializer<v1001::BiomeDefinitionChunkGenData>::serialize(stream, (*value.chunk_gen_data));
    }
}

auto Serializer<v1001::BiomeDefinitionData>::deserialize(BinaryReader &stream) -> std::expected<v1001::BiomeDefinitionData, std::error_code>
{
    v1001::BiomeDefinitionData out;
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.id = static_cast<std::uint16_t>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.temperature = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.downfall = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.foliage_snow = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.depth = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.scale = static_cast<float>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.map_water_color_argb = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.rain = static_cast<bool>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BiomeTagsData staged{};
            auto v = Serializer<BiomeTagsData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.tags = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v1001::BiomeDefinitionChunkGenData staged{};
            auto v = Serializer<v1001::BiomeDefinitionChunkGenData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.chunk_gen_data = std::move(staged);
        }
    }
    return out;
}

void Serializer<BiomeStringList>::serialize(BinaryWriter &stream, const BiomeStringList &value)
{
    stream.writeVarInt<std::uint32_t>(value.strings.size());
    for (const auto &e0 : value.strings) {
        stream.write(e0);
    }
}

auto Serializer<BiomeStringList>::deserialize(BinaryReader &stream) -> std::expected<BiomeStringList, std::error_code>
{
    BiomeStringList out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.strings.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.strings.emplace_back();
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.strings.back() = *v;
        }
    }
    return out;
}

void Serializer<base::BiomeDefinitionListPacket>::serialize(BinaryWriter &stream, const base::BiomeDefinitionListPacket &value)
{
    Serializer<CompoundTag>::serialize(stream, value.biome_data);
}

auto Serializer<base::BiomeDefinitionListPacket>::deserialize(BinaryReader &stream) -> std::expected<base::BiomeDefinitionListPacket, std::error_code>
{
    base::BiomeDefinitionListPacket out;
    {
        auto v = Serializer<CompoundTag>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.biome_data = *v;
    }
    return out;
}

void Serializer<v800::BiomeDefinitionListPacket>::serialize(BinaryWriter &stream, const v800::BiomeDefinitionListPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.biome_data.size());
    for (const auto &[k0, v0] : value.biome_data) {
        stream.write<std::uint16_t>(k0);
        Serializer<v800::BiomeDefinitionData>::serialize(stream, v0);
    }
    Serializer<BiomeStringList>::serialize(stream, value.string_list);
}

auto Serializer<v800::BiomeDefinitionListPacket>::deserialize(BinaryReader &stream) -> std::expected<v800::BiomeDefinitionListPacket, std::error_code>
{
    v800::BiomeDefinitionListPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.biome_data.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            BiomeStringIndex key0{};
            {
                auto v = stream.read<std::uint16_t>();
                if (!v) return std::unexpected(v.error());
                key0 = static_cast<BiomeStringIndex>(*v);
            }
            auto v = Serializer<v800::BiomeDefinitionData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.biome_data[key0] = *v;
        }
    }
    {
        auto v = Serializer<BiomeStringList>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.string_list = *v;
    }
    return out;
}

void Serializer<v827::BiomeDefinitionListPacket>::serialize(BinaryWriter &stream, const v827::BiomeDefinitionListPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.biome_data.size());
    for (const auto &[k0, v0] : value.biome_data) {
        stream.write<std::uint16_t>(k0);
        Serializer<v827::BiomeDefinitionData>::serialize(stream, v0);
    }
    Serializer<BiomeStringList>::serialize(stream, value.string_list);
}

auto Serializer<v827::BiomeDefinitionListPacket>::deserialize(BinaryReader &stream) -> std::expected<v827::BiomeDefinitionListPacket, std::error_code>
{
    v827::BiomeDefinitionListPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.biome_data.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            BiomeStringIndex key0{};
            {
                auto v = stream.read<std::uint16_t>();
                if (!v) return std::unexpected(v.error());
                key0 = static_cast<BiomeStringIndex>(*v);
            }
            auto v = Serializer<v827::BiomeDefinitionData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.biome_data[key0] = *v;
        }
    }
    {
        auto v = Serializer<BiomeStringList>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.string_list = *v;
    }
    return out;
}

void Serializer<v844::BiomeDefinitionListPacket>::serialize(BinaryWriter &stream, const v844::BiomeDefinitionListPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.biome_data.size());
    for (const auto &[k0, v0] : value.biome_data) {
        stream.write<std::uint16_t>(k0);
        Serializer<v844::BiomeDefinitionData>::serialize(stream, v0);
    }
    Serializer<BiomeStringList>::serialize(stream, value.string_list);
}

auto Serializer<v844::BiomeDefinitionListPacket>::deserialize(BinaryReader &stream) -> std::expected<v844::BiomeDefinitionListPacket, std::error_code>
{
    v844::BiomeDefinitionListPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.biome_data.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            BiomeStringIndex key0{};
            {
                auto v = stream.read<std::uint16_t>();
                if (!v) return std::unexpected(v.error());
                key0 = static_cast<BiomeStringIndex>(*v);
            }
            auto v = Serializer<v844::BiomeDefinitionData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.biome_data[key0] = *v;
        }
    }
    {
        auto v = Serializer<BiomeStringList>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.string_list = *v;
    }
    return out;
}

void Serializer<v859::BiomeDefinitionListPacket>::serialize(BinaryWriter &stream, const v859::BiomeDefinitionListPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.biome_data.size());
    for (const auto &[k0, v0] : value.biome_data) {
        stream.write<std::uint16_t>(k0);
        Serializer<v859::BiomeDefinitionData>::serialize(stream, v0);
    }
    Serializer<BiomeStringList>::serialize(stream, value.string_list);
}

auto Serializer<v859::BiomeDefinitionListPacket>::deserialize(BinaryReader &stream) -> std::expected<v859::BiomeDefinitionListPacket, std::error_code>
{
    v859::BiomeDefinitionListPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.biome_data.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            BiomeStringIndex key0{};
            {
                auto v = stream.read<std::uint16_t>();
                if (!v) return std::unexpected(v.error());
                key0 = static_cast<BiomeStringIndex>(*v);
            }
            auto v = Serializer<v859::BiomeDefinitionData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.biome_data[key0] = *v;
        }
    }
    {
        auto v = Serializer<BiomeStringList>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.string_list = *v;
    }
    return out;
}

void Serializer<v924::BiomeDefinitionListPacket>::serialize(BinaryWriter &stream, const v924::BiomeDefinitionListPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.biome_data.size());
    for (const auto &[k0, v0] : value.biome_data) {
        stream.write<std::uint16_t>(k0);
        Serializer<v924::BiomeDefinitionData>::serialize(stream, v0);
    }
    Serializer<BiomeStringList>::serialize(stream, value.string_list);
}

auto Serializer<v924::BiomeDefinitionListPacket>::deserialize(BinaryReader &stream) -> std::expected<v924::BiomeDefinitionListPacket, std::error_code>
{
    v924::BiomeDefinitionListPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.biome_data.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            BiomeStringIndex key0{};
            {
                auto v = stream.read<std::uint16_t>();
                if (!v) return std::unexpected(v.error());
                key0 = static_cast<BiomeStringIndex>(*v);
            }
            auto v = Serializer<v924::BiomeDefinitionData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.biome_data[key0] = *v;
        }
    }
    {
        auto v = Serializer<BiomeStringList>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.string_list = *v;
    }
    return out;
}

void Serializer<v975::BiomeDefinitionListPacket>::serialize(BinaryWriter &stream, const v975::BiomeDefinitionListPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.biome_data.size());
    for (const auto &[k0, v0] : value.biome_data) {
        stream.write<std::uint16_t>(k0);
        Serializer<v975::BiomeDefinitionData>::serialize(stream, v0);
    }
    Serializer<BiomeStringList>::serialize(stream, value.string_list);
}

auto Serializer<v975::BiomeDefinitionListPacket>::deserialize(BinaryReader &stream) -> std::expected<v975::BiomeDefinitionListPacket, std::error_code>
{
    v975::BiomeDefinitionListPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.biome_data.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            BiomeStringIndex key0{};
            {
                auto v = stream.read<std::uint16_t>();
                if (!v) return std::unexpected(v.error());
                key0 = static_cast<BiomeStringIndex>(*v);
            }
            auto v = Serializer<v975::BiomeDefinitionData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.biome_data[key0] = *v;
        }
    }
    {
        auto v = Serializer<BiomeStringList>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.string_list = *v;
    }
    return out;
}

void Serializer<v1001::BiomeDefinitionListPacket>::serialize(BinaryWriter &stream, const v1001::BiomeDefinitionListPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.biome_data.size());
    for (const auto &[k0, v0] : value.biome_data) {
        stream.write<std::uint16_t>(k0);
        Serializer<v1001::BiomeDefinitionData>::serialize(stream, v0);
    }
    Serializer<BiomeStringList>::serialize(stream, value.string_list);
}

auto Serializer<v1001::BiomeDefinitionListPacket>::deserialize(BinaryReader &stream) -> std::expected<v1001::BiomeDefinitionListPacket, std::error_code>
{
    v1001::BiomeDefinitionListPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.biome_data.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            BiomeStringIndex key0{};
            {
                auto v = stream.read<std::uint16_t>();
                if (!v) return std::unexpected(v.error());
                key0 = static_cast<BiomeStringIndex>(*v);
            }
            auto v = Serializer<v1001::BiomeDefinitionData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.biome_data[key0] = *v;
        }
    }
    {
        auto v = Serializer<BiomeStringList>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.string_list = *v;
    }
    return out;
}

void Serializer<base::CompressedBiomeDefinitionListPacket>::serialize(BinaryWriter &stream, const base::CompressedBiomeDefinitionListPacket &value)
{
    stream.write(value.compressed_biome_data);
}

auto Serializer<base::CompressedBiomeDefinitionListPacket>::deserialize(BinaryReader &stream) -> std::expected<base::CompressedBiomeDefinitionListPacket, std::error_code>
{
    base::CompressedBiomeDefinitionListPacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.compressed_biome_data = *v;
    }
    return out;
}

}  // namespace bedrock::protocol
