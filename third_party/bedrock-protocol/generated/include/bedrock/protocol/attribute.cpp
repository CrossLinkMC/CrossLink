#include <bedrock/protocol/attribute.h>

namespace bedrock::protocol {


void Serializer<AttributeModifier>::serialize(BinaryWriter &stream, const AttributeModifier &value)
{
    stream.write(value.id);
    stream.write(value.name);
    stream.write<float>(value.amount);
    stream.write<std::int32_t>(value.operation);
    stream.write<std::int32_t>(value.operand);
    stream.write<bool>(value.serialize);
}

auto Serializer<AttributeModifier>::deserialize(BinaryReader &stream) -> std::expected<AttributeModifier, std::error_code>
{
    AttributeModifier out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.amount = static_cast<float>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.operation = static_cast<AttributeModifierOperation>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.operand = static_cast<AttributeOperands>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.serialize = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<AttributeData>::serialize(BinaryWriter &stream, const AttributeData &value)
{
    stream.write<float>(value.min_value);
    stream.write<float>(value.max_value);
    stream.write<float>(value.current_value);
    stream.write<float>(value.default_min_value);
    stream.write<float>(value.default_max_value);
    stream.write<float>(value.default_value);
    stream.write(value.name);
    stream.writeVarInt<std::uint32_t>(value.modifiers.size());
    for (const auto &e0 : value.modifiers) {
        Serializer<AttributeModifier>::serialize(stream, e0);
    }
}

auto Serializer<AttributeData>::deserialize(BinaryReader &stream) -> std::expected<AttributeData, std::error_code>
{
    AttributeData out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.min_value = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.max_value = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.current_value = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.default_min_value = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.default_max_value = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.default_value = static_cast<float>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.modifiers.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.modifiers.emplace_back();
            auto v = Serializer<AttributeModifier>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.modifiers.back() = *v;
        }
    }
    return out;
}

void Serializer<UpdateAttributesPacket>::serialize(BinaryWriter &stream, const UpdateAttributesPacket &value)
{
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    stream.writeVarInt<std::uint32_t>(value.attribute_data.size());
    for (const auto &e0 : value.attribute_data) {
        Serializer<AttributeData>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint64_t>(value.tick);
}

auto Serializer<UpdateAttributesPacket>::deserialize(BinaryReader &stream) -> std::expected<UpdateAttributesPacket, std::error_code>
{
    UpdateAttributesPacket out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.attribute_data.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.attribute_data.emplace_back();
            auto v = Serializer<AttributeData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.attribute_data.back() = *v;
        }
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.tick = static_cast<PlayerInputTick>(*v);
    }
    return out;
}

}  // namespace bedrock::protocol
