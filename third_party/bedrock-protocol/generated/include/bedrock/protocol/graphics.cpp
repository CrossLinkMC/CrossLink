#include <bedrock/protocol/graphics.h>

namespace bedrock::protocol {


void Serializer<v859::GraphicsOverrideParameterPacket>::serialize(BinaryWriter &stream, const v859::GraphicsOverrideParameterPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.keyframes.size());
    for (const auto &[k0, v0] : value.keyframes) {
        stream.write<float>(k0);
        Serializer<Vec3>::serialize(stream, v0);
    }
    stream.write(value.biome_id);
    stream.write<std::uint8_t>(value.parameter_id);
    stream.write<bool>(value.reset_parameter);
}

auto Serializer<v859::GraphicsOverrideParameterPacket>::deserialize(BinaryReader &stream) -> std::expected<v859::GraphicsOverrideParameterPacket, std::error_code>
{
    v859::GraphicsOverrideParameterPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.keyframes.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            float key0{};
            {
                auto v = stream.read<float>();
                if (!v) return std::unexpected(v.error());
                key0 = static_cast<float>(*v);
            }
            auto v = Serializer<Vec3>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.keyframes[key0] = *v;
        }
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.biome_id = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.parameter_id = static_cast<base::GraphicsOverrideParameterType>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.reset_parameter = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v898::GraphicsOverrideParameterPacket>::serialize(BinaryWriter &stream, const v898::GraphicsOverrideParameterPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.keyframes.size());
    for (const auto &[k0, v0] : value.keyframes) {
        stream.write<float>(k0);
        Serializer<Vec3>::serialize(stream, v0);
    }
    stream.write(value.biome_id);
    stream.write<std::uint8_t>(value.parameter_id);
    stream.write<bool>(value.reset_parameter);
}

auto Serializer<v898::GraphicsOverrideParameterPacket>::deserialize(BinaryReader &stream) -> std::expected<v898::GraphicsOverrideParameterPacket, std::error_code>
{
    v898::GraphicsOverrideParameterPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.keyframes.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            float key0{};
            {
                auto v = stream.read<float>();
                if (!v) return std::unexpected(v.error());
                key0 = static_cast<float>(*v);
            }
            auto v = Serializer<Vec3>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.keyframes[key0] = *v;
        }
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.biome_id = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.parameter_id = static_cast<v898::GraphicsOverrideParameterType>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.reset_parameter = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v924::GraphicsOverrideParameterPacket>::serialize(BinaryWriter &stream, const v924::GraphicsOverrideParameterPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.keyframes.size());
    for (const auto &[k0, v0] : value.keyframes) {
        stream.write<float>(k0);
        Serializer<Vec3>::serialize(stream, v0);
    }
    stream.write<bool>(value.float_value.has_value());
    if (value.float_value.has_value()) {
        stream.write<float>((*value.float_value));
    }
    stream.write<bool>(value.vec3_value.has_value());
    if (value.vec3_value.has_value()) {
        Serializer<Vec3>::serialize(stream, (*value.vec3_value));
    }
    stream.write(value.biome_id);
    stream.write<std::uint8_t>(value.parameter_id);
    stream.write<bool>(value.reset_parameter);
}

auto Serializer<v924::GraphicsOverrideParameterPacket>::deserialize(BinaryReader &stream) -> std::expected<v924::GraphicsOverrideParameterPacket, std::error_code>
{
    v924::GraphicsOverrideParameterPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.keyframes.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            float key0{};
            {
                auto v = stream.read<float>();
                if (!v) return std::unexpected(v.error());
                key0 = static_cast<float>(*v);
            }
            auto v = Serializer<Vec3>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.keyframes[key0] = *v;
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
            out.float_value = std::move(staged);
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
            out.vec3_value = std::move(staged);
        }
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.biome_id = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.parameter_id = static_cast<v924::GraphicsOverrideParameterType>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.reset_parameter = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v944::GraphicsOverrideParameterPacket>::serialize(BinaryWriter &stream, const v944::GraphicsOverrideParameterPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.keyframes.size());
    for (const auto &[k0, v0] : value.keyframes) {
        stream.write<float>(k0);
        Serializer<Vec3>::serialize(stream, v0);
    }
    stream.write<bool>(value.float_value.has_value());
    if (value.float_value.has_value()) {
        stream.write<float>((*value.float_value));
    }
    stream.write<bool>(value.vec3_value.has_value());
    if (value.vec3_value.has_value()) {
        Serializer<Vec3>::serialize(stream, (*value.vec3_value));
    }
    stream.write(value.biome_id);
    stream.write<std::uint8_t>(value.parameter_id);
    stream.write<bool>(value.reset_parameter);
}

auto Serializer<v944::GraphicsOverrideParameterPacket>::deserialize(BinaryReader &stream) -> std::expected<v944::GraphicsOverrideParameterPacket, std::error_code>
{
    v944::GraphicsOverrideParameterPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.keyframes.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            float key0{};
            {
                auto v = stream.read<float>();
                if (!v) return std::unexpected(v.error());
                key0 = static_cast<float>(*v);
            }
            auto v = Serializer<Vec3>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.keyframes[key0] = *v;
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
            out.float_value = std::move(staged);
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
            out.vec3_value = std::move(staged);
        }
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.biome_id = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.parameter_id = static_cast<v944::GraphicsOverrideParameterType>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.reset_parameter = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v975::GraphicsOverrideParameterPacket>::serialize(BinaryWriter &stream, const v975::GraphicsOverrideParameterPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.keyframes.size());
    for (const auto &[k0, v0] : value.keyframes) {
        stream.write<float>(k0);
        Serializer<Vec3>::serialize(stream, v0);
    }
    stream.write<bool>(value.float_value.has_value());
    if (value.float_value.has_value()) {
        stream.write<float>((*value.float_value));
    }
    stream.write<bool>(value.vec3_value.has_value());
    if (value.vec3_value.has_value()) {
        Serializer<Vec3>::serialize(stream, (*value.vec3_value));
    }
    stream.write(value.biome_id);
    stream.write<std::uint8_t>(value.parameter_id);
    stream.write<bool>(value.reset_parameter);
}

auto Serializer<v975::GraphicsOverrideParameterPacket>::deserialize(BinaryReader &stream) -> std::expected<v975::GraphicsOverrideParameterPacket, std::error_code>
{
    v975::GraphicsOverrideParameterPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.keyframes.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            float key0{};
            {
                auto v = stream.read<float>();
                if (!v) return std::unexpected(v.error());
                key0 = static_cast<float>(*v);
            }
            auto v = Serializer<Vec3>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.keyframes[key0] = *v;
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
            out.float_value = std::move(staged);
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
            out.vec3_value = std::move(staged);
        }
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.biome_id = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.parameter_id = static_cast<v975::GraphicsOverrideParameterType>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.reset_parameter = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v1001::GraphicsOverrideParameterPacket>::serialize(BinaryWriter &stream, const v1001::GraphicsOverrideParameterPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.keyframes.size());
    for (const auto &[k0, v0] : value.keyframes) {
        stream.write<float>(k0);
        Serializer<Vec3>::serialize(stream, v0);
    }
    stream.write<bool>(value.float_value.has_value());
    if (value.float_value.has_value()) {
        stream.write<float>((*value.float_value));
    }
    stream.write<bool>(value.vec3_value.has_value());
    if (value.vec3_value.has_value()) {
        Serializer<Vec3>::serialize(stream, (*value.vec3_value));
    }
    stream.write(value.biome_id);
    stream.write<bool>(value.player_id.has_value());
    if (value.player_id.has_value()) {
        stream.write((*value.player_id));
    }
    stream.write<std::uint8_t>(value.parameter_id);
    stream.write<bool>(value.reset_parameter);
}

auto Serializer<v1001::GraphicsOverrideParameterPacket>::deserialize(BinaryReader &stream) -> std::expected<v1001::GraphicsOverrideParameterPacket, std::error_code>
{
    v1001::GraphicsOverrideParameterPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.keyframes.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            float key0{};
            {
                auto v = stream.read<float>();
                if (!v) return std::unexpected(v.error());
                key0 = static_cast<float>(*v);
            }
            auto v = Serializer<Vec3>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.keyframes[key0] = *v;
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
            out.float_value = std::move(staged);
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
            out.vec3_value = std::move(staged);
        }
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.biome_id = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::string staged{};
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.player_id = std::move(staged);
        }
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.parameter_id = static_cast<v975::GraphicsOverrideParameterType>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.reset_parameter = static_cast<bool>(*v);
    }
    return out;
}

}  // namespace bedrock::protocol
