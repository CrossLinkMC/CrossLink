#include <bedrock/protocol/common.h>

namespace bedrock::protocol {


void Serializer<Vec2>::serialize(BinaryWriter &stream, const Vec2 &value)
{
    stream.write<float>(value.x);
    stream.write<float>(value.y);
}

auto Serializer<Vec2>::deserialize(BinaryReader &stream) -> std::expected<Vec2, std::error_code>
{
    Vec2 out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.x = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.y = static_cast<float>(*v);
    }
    return out;
}

void Serializer<Vec3>::serialize(BinaryWriter &stream, const Vec3 &value)
{
    stream.write<float>(value.x);
    stream.write<float>(value.y);
    stream.write<float>(value.z);
}

auto Serializer<Vec3>::deserialize(BinaryReader &stream) -> std::expected<Vec3, std::error_code>
{
    Vec3 out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.x = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.y = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.z = static_cast<float>(*v);
    }
    return out;
}

void Serializer<BlockPos>::serialize(BinaryWriter &stream, const BlockPos &value)
{
    stream.writeVarInt<std::int32_t>(value.x);
    stream.writeVarInt<std::int32_t>(value.y);
    stream.writeVarInt<std::int32_t>(value.z);
}

auto Serializer<BlockPos>::deserialize(BinaryReader &stream) -> std::expected<BlockPos, std::error_code>
{
    BlockPos out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.x = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.y = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.z = static_cast<std::int32_t>(*v);
    }
    return out;
}

}  // namespace bedrock::protocol
