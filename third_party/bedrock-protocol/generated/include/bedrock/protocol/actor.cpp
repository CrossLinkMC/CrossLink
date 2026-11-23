#include <bedrock/protocol/actor.h>

namespace bedrock::protocol {


void Serializer<base::DataItemBytePayload>::serialize(BinaryWriter &stream, const base::DataItemBytePayload &value)
{
    stream.write<std::int8_t>(value.value);
}

auto Serializer<base::DataItemBytePayload>::deserialize(BinaryReader &stream) -> std::expected<base::DataItemBytePayload, std::error_code>
{
    base::DataItemBytePayload out;
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.value = static_cast<std::int8_t>(*v);
    }
    return out;
}

void Serializer<v2168::DataItemBytePayload>::serialize(BinaryWriter &stream, const v2168::DataItemBytePayload &value)
{
    stream.write<std::uint8_t>(0);
    stream.write<std::int8_t>(value.value);
}

auto Serializer<v2168::DataItemBytePayload>::deserialize(BinaryReader &stream) -> std::expected<v2168::DataItemBytePayload, std::error_code>
{
    v2168::DataItemBytePayload out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 0) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.value = static_cast<std::int8_t>(*v);
    }
    return out;
}

void Serializer<base::DataItemShortPayload>::serialize(BinaryWriter &stream, const base::DataItemShortPayload &value)
{
    stream.write<std::int16_t>(value.value);
}

auto Serializer<base::DataItemShortPayload>::deserialize(BinaryReader &stream) -> std::expected<base::DataItemShortPayload, std::error_code>
{
    base::DataItemShortPayload out;
    {
        auto v = stream.read<std::int16_t>();
        if (!v) return std::unexpected(v.error());
        out.value = static_cast<std::int16_t>(*v);
    }
    return out;
}

void Serializer<v2168::DataItemShortPayload>::serialize(BinaryWriter &stream, const v2168::DataItemShortPayload &value)
{
    stream.write<std::uint8_t>(1);
    stream.write<std::int16_t>(value.value);
}

auto Serializer<v2168::DataItemShortPayload>::deserialize(BinaryReader &stream) -> std::expected<v2168::DataItemShortPayload, std::error_code>
{
    v2168::DataItemShortPayload out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 1) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.read<std::int16_t>();
        if (!v) return std::unexpected(v.error());
        out.value = static_cast<std::int16_t>(*v);
    }
    return out;
}

void Serializer<base::DataItemIntPayload>::serialize(BinaryWriter &stream, const base::DataItemIntPayload &value)
{
    stream.writeVarInt<std::int32_t>(value.value);
}

auto Serializer<base::DataItemIntPayload>::deserialize(BinaryReader &stream) -> std::expected<base::DataItemIntPayload, std::error_code>
{
    base::DataItemIntPayload out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.value = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<v2168::DataItemIntPayload>::serialize(BinaryWriter &stream, const v2168::DataItemIntPayload &value)
{
    stream.write<std::uint8_t>(2);
    stream.writeVarInt<std::int32_t>(value.value);
}

auto Serializer<v2168::DataItemIntPayload>::deserialize(BinaryReader &stream) -> std::expected<v2168::DataItemIntPayload, std::error_code>
{
    v2168::DataItemIntPayload out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 2) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.value = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<base::DataItemFloatPayload>::serialize(BinaryWriter &stream, const base::DataItemFloatPayload &value)
{
    stream.write<float>(value.value);
}

auto Serializer<base::DataItemFloatPayload>::deserialize(BinaryReader &stream) -> std::expected<base::DataItemFloatPayload, std::error_code>
{
    base::DataItemFloatPayload out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.value = static_cast<float>(*v);
    }
    return out;
}

void Serializer<v2168::DataItemFloatPayload>::serialize(BinaryWriter &stream, const v2168::DataItemFloatPayload &value)
{
    stream.write<std::uint8_t>(3);
    stream.write<float>(value.value);
}

auto Serializer<v2168::DataItemFloatPayload>::deserialize(BinaryReader &stream) -> std::expected<v2168::DataItemFloatPayload, std::error_code>
{
    v2168::DataItemFloatPayload out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 3) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.value = static_cast<float>(*v);
    }
    return out;
}

void Serializer<base::DataItemStringPayload>::serialize(BinaryWriter &stream, const base::DataItemStringPayload &value)
{
    stream.write(value.value);
}

auto Serializer<base::DataItemStringPayload>::deserialize(BinaryReader &stream) -> std::expected<base::DataItemStringPayload, std::error_code>
{
    base::DataItemStringPayload out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.value = *v;
    }
    return out;
}

void Serializer<v2168::DataItemStringPayload>::serialize(BinaryWriter &stream, const v2168::DataItemStringPayload &value)
{
    stream.write<std::uint8_t>(4);
    stream.write(value.value);
}

auto Serializer<v2168::DataItemStringPayload>::deserialize(BinaryReader &stream) -> std::expected<v2168::DataItemStringPayload, std::error_code>
{
    v2168::DataItemStringPayload out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 4) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.value = *v;
    }
    return out;
}

void Serializer<base::DataItemCompoundTagPayload>::serialize(BinaryWriter &stream, const base::DataItemCompoundTagPayload &value)
{
    Serializer<CompoundTag>::serialize(stream, value.value);
}

auto Serializer<base::DataItemCompoundTagPayload>::deserialize(BinaryReader &stream) -> std::expected<base::DataItemCompoundTagPayload, std::error_code>
{
    base::DataItemCompoundTagPayload out;
    {
        auto v = Serializer<CompoundTag>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.value = *v;
    }
    return out;
}

void Serializer<v2168::DataItemCompoundTagPayload>::serialize(BinaryWriter &stream, const v2168::DataItemCompoundTagPayload &value)
{
    stream.write<std::uint8_t>(5);
    Serializer<CompoundTag>::serialize(stream, value.value);
}

auto Serializer<v2168::DataItemCompoundTagPayload>::deserialize(BinaryReader &stream) -> std::expected<v2168::DataItemCompoundTagPayload, std::error_code>
{
    v2168::DataItemCompoundTagPayload out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 5) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = Serializer<CompoundTag>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.value = *v;
    }
    return out;
}

void Serializer<base::DataItemPosPayload>::serialize(BinaryWriter &stream, const base::DataItemPosPayload &value)
{
    Serializer<BlockPos>::serialize(stream, value.value);
}

auto Serializer<base::DataItemPosPayload>::deserialize(BinaryReader &stream) -> std::expected<base::DataItemPosPayload, std::error_code>
{
    base::DataItemPosPayload out;
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.value = *v;
    }
    return out;
}

void Serializer<v2168::DataItemPosPayload>::serialize(BinaryWriter &stream, const v2168::DataItemPosPayload &value)
{
    stream.write<std::uint8_t>(6);
    Serializer<BlockPos>::serialize(stream, value.value);
}

auto Serializer<v2168::DataItemPosPayload>::deserialize(BinaryReader &stream) -> std::expected<v2168::DataItemPosPayload, std::error_code>
{
    v2168::DataItemPosPayload out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 6) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.value = *v;
    }
    return out;
}

void Serializer<base::DataItemInt64Payload>::serialize(BinaryWriter &stream, const base::DataItemInt64Payload &value)
{
    stream.writeVarInt<std::int64_t>(value.value);
}

auto Serializer<base::DataItemInt64Payload>::deserialize(BinaryReader &stream) -> std::expected<base::DataItemInt64Payload, std::error_code>
{
    base::DataItemInt64Payload out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.value = static_cast<std::int64_t>(*v);
    }
    return out;
}

void Serializer<v2168::DataItemInt64Payload>::serialize(BinaryWriter &stream, const v2168::DataItemInt64Payload &value)
{
    stream.write<std::uint8_t>(7);
    stream.writeVarInt<std::int64_t>(value.value);
}

auto Serializer<v2168::DataItemInt64Payload>::deserialize(BinaryReader &stream) -> std::expected<v2168::DataItemInt64Payload, std::error_code>
{
    v2168::DataItemInt64Payload out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 7) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.value = static_cast<std::int64_t>(*v);
    }
    return out;
}

void Serializer<base::DataItemVec3Payload>::serialize(BinaryWriter &stream, const base::DataItemVec3Payload &value)
{
    Serializer<Vec3>::serialize(stream, value.value);
}

auto Serializer<base::DataItemVec3Payload>::deserialize(BinaryReader &stream) -> std::expected<base::DataItemVec3Payload, std::error_code>
{
    base::DataItemVec3Payload out;
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.value = *v;
    }
    return out;
}

void Serializer<v2168::DataItemVec3Payload>::serialize(BinaryWriter &stream, const v2168::DataItemVec3Payload &value)
{
    stream.write<std::uint8_t>(8);
    Serializer<Vec3>::serialize(stream, value.value);
}

auto Serializer<v2168::DataItemVec3Payload>::deserialize(BinaryReader &stream) -> std::expected<v2168::DataItemVec3Payload, std::error_code>
{
    v2168::DataItemVec3Payload out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 8) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.value = *v;
    }
    return out;
}

void Serializer<base::DataItemEntry>::serialize(BinaryWriter &stream, const base::DataItemEntry &value)
{
    stream.writeVarInt<std::uint32_t>(value.id);
    stream.writeVarInt<std::uint32_t>((value.payload).index());
    switch ((value.payload).index()) {
        case 0: {
            Serializer<base::DataItemBytePayload>::serialize(stream, std::get<0>(value.payload));
            break;
        }
        case 1: {
            Serializer<base::DataItemShortPayload>::serialize(stream, std::get<1>(value.payload));
            break;
        }
        case 2: {
            Serializer<base::DataItemIntPayload>::serialize(stream, std::get<2>(value.payload));
            break;
        }
        case 3: {
            Serializer<base::DataItemFloatPayload>::serialize(stream, std::get<3>(value.payload));
            break;
        }
        case 4: {
            Serializer<base::DataItemStringPayload>::serialize(stream, std::get<4>(value.payload));
            break;
        }
        case 5: {
            Serializer<base::DataItemCompoundTagPayload>::serialize(stream, std::get<5>(value.payload));
            break;
        }
        case 6: {
            Serializer<base::DataItemPosPayload>::serialize(stream, std::get<6>(value.payload));
            break;
        }
        case 7: {
            Serializer<base::DataItemInt64Payload>::serialize(stream, std::get<7>(value.payload));
            break;
        }
        case 8: {
            Serializer<base::DataItemVec3Payload>::serialize(stream, std::get<8>(value.payload));
            break;
        }
    }
}

auto Serializer<base::DataItemEntry>::deserialize(BinaryReader &stream) -> std::expected<base::DataItemEntry, std::error_code>
{
    base::DataItemEntry out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.id = static_cast<std::uint32_t>(*v);
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<base::DataItemBytePayload, base::DataItemShortPayload, base::DataItemIntPayload, base::DataItemFloatPayload, base::DataItemStringPayload, base::DataItemCompoundTagPayload, base::DataItemPosPayload, base::DataItemInt64Payload, base::DataItemVec3Payload> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<base::DataItemBytePayload, base::DataItemShortPayload, base::DataItemIntPayload, base::DataItemFloatPayload, base::DataItemStringPayload, base::DataItemCompoundTagPayload, base::DataItemPosPayload, base::DataItemInt64Payload, base::DataItemVec3Payload>> alt0{};
                {
                    auto v = Serializer<base::DataItemBytePayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<base::DataItemBytePayload, base::DataItemShortPayload, base::DataItemIntPayload, base::DataItemFloatPayload, base::DataItemStringPayload, base::DataItemCompoundTagPayload, base::DataItemPosPayload, base::DataItemInt64Payload, base::DataItemVec3Payload>> alt0{};
                {
                    auto v = Serializer<base::DataItemShortPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<base::DataItemBytePayload, base::DataItemShortPayload, base::DataItemIntPayload, base::DataItemFloatPayload, base::DataItemStringPayload, base::DataItemCompoundTagPayload, base::DataItemPosPayload, base::DataItemInt64Payload, base::DataItemVec3Payload>> alt0{};
                {
                    auto v = Serializer<base::DataItemIntPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<base::DataItemBytePayload, base::DataItemShortPayload, base::DataItemIntPayload, base::DataItemFloatPayload, base::DataItemStringPayload, base::DataItemCompoundTagPayload, base::DataItemPosPayload, base::DataItemInt64Payload, base::DataItemVec3Payload>> alt0{};
                {
                    auto v = Serializer<base::DataItemFloatPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            case 4: {
                std::variant_alternative_t<4, std::variant<base::DataItemBytePayload, base::DataItemShortPayload, base::DataItemIntPayload, base::DataItemFloatPayload, base::DataItemStringPayload, base::DataItemCompoundTagPayload, base::DataItemPosPayload, base::DataItemInt64Payload, base::DataItemVec3Payload>> alt0{};
                {
                    auto v = Serializer<base::DataItemStringPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<4>(alt0);
                break;
            }
            case 5: {
                std::variant_alternative_t<5, std::variant<base::DataItemBytePayload, base::DataItemShortPayload, base::DataItemIntPayload, base::DataItemFloatPayload, base::DataItemStringPayload, base::DataItemCompoundTagPayload, base::DataItemPosPayload, base::DataItemInt64Payload, base::DataItemVec3Payload>> alt0{};
                {
                    auto v = Serializer<base::DataItemCompoundTagPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<5>(alt0);
                break;
            }
            case 6: {
                std::variant_alternative_t<6, std::variant<base::DataItemBytePayload, base::DataItemShortPayload, base::DataItemIntPayload, base::DataItemFloatPayload, base::DataItemStringPayload, base::DataItemCompoundTagPayload, base::DataItemPosPayload, base::DataItemInt64Payload, base::DataItemVec3Payload>> alt0{};
                {
                    auto v = Serializer<base::DataItemPosPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<6>(alt0);
                break;
            }
            case 7: {
                std::variant_alternative_t<7, std::variant<base::DataItemBytePayload, base::DataItemShortPayload, base::DataItemIntPayload, base::DataItemFloatPayload, base::DataItemStringPayload, base::DataItemCompoundTagPayload, base::DataItemPosPayload, base::DataItemInt64Payload, base::DataItemVec3Payload>> alt0{};
                {
                    auto v = Serializer<base::DataItemInt64Payload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<7>(alt0);
                break;
            }
            case 8: {
                std::variant_alternative_t<8, std::variant<base::DataItemBytePayload, base::DataItemShortPayload, base::DataItemIntPayload, base::DataItemFloatPayload, base::DataItemStringPayload, base::DataItemCompoundTagPayload, base::DataItemPosPayload, base::DataItemInt64Payload, base::DataItemVec3Payload>> alt0{};
                {
                    auto v = Serializer<base::DataItemVec3Payload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<8>(alt0);
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

void Serializer<v2168::DataItemEntry>::serialize(BinaryWriter &stream, const v2168::DataItemEntry &value)
{
    stream.writeVarInt<std::uint32_t>(value.id);
    stream.writeVarInt<std::uint32_t>((value.payload).index());
    switch ((value.payload).index()) {
        case 0: {
            Serializer<v2168::DataItemBytePayload>::serialize(stream, std::get<0>(value.payload));
            break;
        }
        case 1: {
            Serializer<v2168::DataItemShortPayload>::serialize(stream, std::get<1>(value.payload));
            break;
        }
        case 2: {
            Serializer<v2168::DataItemIntPayload>::serialize(stream, std::get<2>(value.payload));
            break;
        }
        case 3: {
            Serializer<v2168::DataItemFloatPayload>::serialize(stream, std::get<3>(value.payload));
            break;
        }
        case 4: {
            Serializer<v2168::DataItemStringPayload>::serialize(stream, std::get<4>(value.payload));
            break;
        }
        case 5: {
            Serializer<v2168::DataItemCompoundTagPayload>::serialize(stream, std::get<5>(value.payload));
            break;
        }
        case 6: {
            Serializer<v2168::DataItemPosPayload>::serialize(stream, std::get<6>(value.payload));
            break;
        }
        case 7: {
            Serializer<v2168::DataItemInt64Payload>::serialize(stream, std::get<7>(value.payload));
            break;
        }
        case 8: {
            Serializer<v2168::DataItemVec3Payload>::serialize(stream, std::get<8>(value.payload));
            break;
        }
    }
}

auto Serializer<v2168::DataItemEntry>::deserialize(BinaryReader &stream) -> std::expected<v2168::DataItemEntry, std::error_code>
{
    v2168::DataItemEntry out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.id = static_cast<std::uint32_t>(*v);
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v2168::DataItemBytePayload, v2168::DataItemShortPayload, v2168::DataItemIntPayload, v2168::DataItemFloatPayload, v2168::DataItemStringPayload, v2168::DataItemCompoundTagPayload, v2168::DataItemPosPayload, v2168::DataItemInt64Payload, v2168::DataItemVec3Payload> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v2168::DataItemBytePayload, v2168::DataItemShortPayload, v2168::DataItemIntPayload, v2168::DataItemFloatPayload, v2168::DataItemStringPayload, v2168::DataItemCompoundTagPayload, v2168::DataItemPosPayload, v2168::DataItemInt64Payload, v2168::DataItemVec3Payload>> alt0{};
                {
                    auto v = Serializer<v2168::DataItemBytePayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v2168::DataItemBytePayload, v2168::DataItemShortPayload, v2168::DataItemIntPayload, v2168::DataItemFloatPayload, v2168::DataItemStringPayload, v2168::DataItemCompoundTagPayload, v2168::DataItemPosPayload, v2168::DataItemInt64Payload, v2168::DataItemVec3Payload>> alt0{};
                {
                    auto v = Serializer<v2168::DataItemShortPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<v2168::DataItemBytePayload, v2168::DataItemShortPayload, v2168::DataItemIntPayload, v2168::DataItemFloatPayload, v2168::DataItemStringPayload, v2168::DataItemCompoundTagPayload, v2168::DataItemPosPayload, v2168::DataItemInt64Payload, v2168::DataItemVec3Payload>> alt0{};
                {
                    auto v = Serializer<v2168::DataItemIntPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<v2168::DataItemBytePayload, v2168::DataItemShortPayload, v2168::DataItemIntPayload, v2168::DataItemFloatPayload, v2168::DataItemStringPayload, v2168::DataItemCompoundTagPayload, v2168::DataItemPosPayload, v2168::DataItemInt64Payload, v2168::DataItemVec3Payload>> alt0{};
                {
                    auto v = Serializer<v2168::DataItemFloatPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            case 4: {
                std::variant_alternative_t<4, std::variant<v2168::DataItemBytePayload, v2168::DataItemShortPayload, v2168::DataItemIntPayload, v2168::DataItemFloatPayload, v2168::DataItemStringPayload, v2168::DataItemCompoundTagPayload, v2168::DataItemPosPayload, v2168::DataItemInt64Payload, v2168::DataItemVec3Payload>> alt0{};
                {
                    auto v = Serializer<v2168::DataItemStringPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<4>(alt0);
                break;
            }
            case 5: {
                std::variant_alternative_t<5, std::variant<v2168::DataItemBytePayload, v2168::DataItemShortPayload, v2168::DataItemIntPayload, v2168::DataItemFloatPayload, v2168::DataItemStringPayload, v2168::DataItemCompoundTagPayload, v2168::DataItemPosPayload, v2168::DataItemInt64Payload, v2168::DataItemVec3Payload>> alt0{};
                {
                    auto v = Serializer<v2168::DataItemCompoundTagPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<5>(alt0);
                break;
            }
            case 6: {
                std::variant_alternative_t<6, std::variant<v2168::DataItemBytePayload, v2168::DataItemShortPayload, v2168::DataItemIntPayload, v2168::DataItemFloatPayload, v2168::DataItemStringPayload, v2168::DataItemCompoundTagPayload, v2168::DataItemPosPayload, v2168::DataItemInt64Payload, v2168::DataItemVec3Payload>> alt0{};
                {
                    auto v = Serializer<v2168::DataItemPosPayload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<6>(alt0);
                break;
            }
            case 7: {
                std::variant_alternative_t<7, std::variant<v2168::DataItemBytePayload, v2168::DataItemShortPayload, v2168::DataItemIntPayload, v2168::DataItemFloatPayload, v2168::DataItemStringPayload, v2168::DataItemCompoundTagPayload, v2168::DataItemPosPayload, v2168::DataItemInt64Payload, v2168::DataItemVec3Payload>> alt0{};
                {
                    auto v = Serializer<v2168::DataItemInt64Payload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<7>(alt0);
                break;
            }
            case 8: {
                std::variant_alternative_t<8, std::variant<v2168::DataItemBytePayload, v2168::DataItemShortPayload, v2168::DataItemIntPayload, v2168::DataItemFloatPayload, v2168::DataItemStringPayload, v2168::DataItemCompoundTagPayload, v2168::DataItemPosPayload, v2168::DataItemInt64Payload, v2168::DataItemVec3Payload>> alt0{};
                {
                    auto v = Serializer<v2168::DataItemVec3Payload>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<8>(alt0);
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

void Serializer<base::SynchedActorData::CopyableDataList>::serialize(BinaryWriter &stream, const base::SynchedActorData::CopyableDataList &value)
{
    stream.writeVarInt<std::uint32_t>(value.data.size());
    for (const auto &e0 : value.data) {
        Serializer<base::DataItemEntry>::serialize(stream, e0);
    }
}

auto Serializer<base::SynchedActorData::CopyableDataList>::deserialize(BinaryReader &stream) -> std::expected<base::SynchedActorData::CopyableDataList, std::error_code>
{
    base::SynchedActorData::CopyableDataList out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.data.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.data.emplace_back();
            auto v = Serializer<base::DataItemEntry>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.data.back() = *v;
        }
    }
    return out;
}

void Serializer<v2168::SynchedActorData::CopyableDataList>::serialize(BinaryWriter &stream, const v2168::SynchedActorData::CopyableDataList &value)
{
    stream.writeVarInt<std::uint32_t>(value.data.size());
    for (const auto &e0 : value.data) {
        Serializer<v2168::DataItemEntry>::serialize(stream, e0);
    }
}

auto Serializer<v2168::SynchedActorData::CopyableDataList>::deserialize(BinaryReader &stream) -> std::expected<v2168::SynchedActorData::CopyableDataList, std::error_code>
{
    v2168::SynchedActorData::CopyableDataList out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.data.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.data.emplace_back();
            auto v = Serializer<v2168::DataItemEntry>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.data.back() = *v;
        }
    }
    return out;
}

void Serializer<PropertySyncData::PropertySyncIntEntry>::serialize(BinaryWriter &stream, const PropertySyncData::PropertySyncIntEntry &value)
{
    stream.writeVarInt<std::uint32_t>(value.property_index);
    stream.writeVarInt<std::int32_t>(value.data);
}

auto Serializer<PropertySyncData::PropertySyncIntEntry>::deserialize(BinaryReader &stream) -> std::expected<PropertySyncData::PropertySyncIntEntry, std::error_code>
{
    PropertySyncData::PropertySyncIntEntry out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.property_index = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.data = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<PropertySyncData::PropertySyncFloatEntry>::serialize(BinaryWriter &stream, const PropertySyncData::PropertySyncFloatEntry &value)
{
    stream.writeVarInt<std::uint32_t>(value.property_index);
    stream.write<float>(value.data);
}

auto Serializer<PropertySyncData::PropertySyncFloatEntry>::deserialize(BinaryReader &stream) -> std::expected<PropertySyncData::PropertySyncFloatEntry, std::error_code>
{
    PropertySyncData::PropertySyncFloatEntry out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.property_index = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.data = static_cast<float>(*v);
    }
    return out;
}

void Serializer<PropertySyncData>::serialize(BinaryWriter &stream, const PropertySyncData &value)
{
    stream.writeVarInt<std::uint32_t>(value.int_entries.size());
    for (const auto &e0 : value.int_entries) {
        Serializer<PropertySyncData::PropertySyncIntEntry>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.float_entries.size());
    for (const auto &e0 : value.float_entries) {
        Serializer<PropertySyncData::PropertySyncFloatEntry>::serialize(stream, e0);
    }
}

auto Serializer<PropertySyncData>::deserialize(BinaryReader &stream) -> std::expected<PropertySyncData, std::error_code>
{
    PropertySyncData out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.int_entries.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.int_entries.emplace_back();
            auto v = Serializer<PropertySyncData::PropertySyncIntEntry>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.int_entries.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.float_entries.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.float_entries.emplace_back();
            auto v = Serializer<PropertySyncData::PropertySyncFloatEntry>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.float_entries.back() = *v;
        }
    }
    return out;
}

void Serializer<SyncedAttribute>::serialize(BinaryWriter &stream, const SyncedAttribute &value)
{
    stream.write(value.name);
    stream.write<float>(value.min_value);
    stream.write<float>(value.current_value);
    stream.write<float>(value.max_value);
}

auto Serializer<SyncedAttribute>::deserialize(BinaryReader &stream) -> std::expected<SyncedAttribute, std::error_code>
{
    SyncedAttribute out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.min_value = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.current_value = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.max_value = static_cast<float>(*v);
    }
    return out;
}

void Serializer<ActorLink>::serialize(BinaryWriter &stream, const ActorLink &value)
{
    stream.writeVarInt<std::int64_t>(value.a);
    stream.writeVarInt<std::int64_t>(value.b);
    stream.write<std::uint8_t>(value.type);
    stream.write<bool>(value.immediate);
    stream.write<bool>(value.passenger_initiated);
    stream.write<float>(value.vehicle_angular_velocity);
}

auto Serializer<ActorLink>::deserialize(BinaryReader &stream) -> std::expected<ActorLink, std::error_code>
{
    ActorLink out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.a = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.b = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<ActorLinkType>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.immediate = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.passenger_initiated = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.vehicle_angular_velocity = static_cast<float>(*v);
    }
    return out;
}

void Serializer<PassengerOfBlockArguments>::serialize(BinaryWriter &stream, const PassengerOfBlockArguments &value)
{
    Serializer<BlockPos>::serialize(stream, value.block_pos);
    Serializer<Vec3>::serialize(stream, value.offset);
    stream.write<float>(value.rotation);
    stream.write<float>(value.rotation_limit);
    stream.write<std::uint8_t>(value.emote_type);
}

auto Serializer<PassengerOfBlockArguments>::deserialize(BinaryReader &stream) -> std::expected<PassengerOfBlockArguments, std::error_code>
{
    PassengerOfBlockArguments out;
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.block_pos = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.offset = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.rotation = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.rotation_limit = static_cast<float>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.emote_type = static_cast<PassengerOfBlockArguments::EmoteType>(*v);
    }
    return out;
}

void Serializer<base::AddActorPacket>::serialize(BinaryWriter &stream, const base::AddActorPacket &value)
{
    stream.writeVarInt<std::int64_t>(value.entity_id);
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    stream.write(value.actor_type);
    Serializer<Vec3>::serialize(stream, value.pos);
    Serializer<Vec3>::serialize(stream, value.velocity);
    Serializer<Vec2>::serialize(stream, value.rot);
    stream.write<float>(value.y_head_rotation);
    stream.write<float>(value.y_body_rotation);
    stream.writeVarInt<std::uint32_t>(value.attributes.size());
    for (const auto &e0 : value.attributes) {
        Serializer<SyncedAttribute>::serialize(stream, e0);
    }
    Serializer<base::SynchedActorData::CopyableDataList>::serialize(stream, value.data);
    Serializer<PropertySyncData>::serialize(stream, value.synched_properties);
    stream.writeVarInt<std::uint32_t>(value.links.size());
    for (const auto &e0 : value.links) {
        Serializer<ActorLink>::serialize(stream, e0);
    }
}

auto Serializer<base::AddActorPacket>::deserialize(BinaryReader &stream) -> std::expected<base::AddActorPacket, std::error_code>
{
    base::AddActorPacket out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.actor_type = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.velocity = *v;
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.rot = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.y_head_rotation = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.y_body_rotation = static_cast<float>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.attributes.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.attributes.emplace_back();
            auto v = Serializer<SyncedAttribute>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.attributes.back() = *v;
        }
    }
    {
        auto v = Serializer<base::SynchedActorData::CopyableDataList>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.data = *v;
    }
    {
        auto v = Serializer<PropertySyncData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.synched_properties = *v;
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.links.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.links.emplace_back();
            auto v = Serializer<ActorLink>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.links.back() = *v;
        }
    }
    return out;
}

void Serializer<v2168::AddActorPacket>::serialize(BinaryWriter &stream, const v2168::AddActorPacket &value)
{
    stream.writeVarInt<std::int64_t>(value.entity_id);
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    stream.write(value.actor_type);
    Serializer<Vec3>::serialize(stream, value.pos);
    Serializer<Vec3>::serialize(stream, value.velocity);
    Serializer<Vec2>::serialize(stream, value.rot);
    stream.write<float>(value.y_head_rotation);
    stream.write<float>(value.y_body_rotation);
    stream.writeVarInt<std::uint32_t>(value.attributes.size());
    for (const auto &e0 : value.attributes) {
        Serializer<SyncedAttribute>::serialize(stream, e0);
    }
    Serializer<v2168::SynchedActorData::CopyableDataList>::serialize(stream, value.data);
    Serializer<PropertySyncData>::serialize(stream, value.synched_properties);
    stream.writeVarInt<std::uint32_t>(value.links.size());
    for (const auto &e0 : value.links) {
        Serializer<ActorLink>::serialize(stream, e0);
    }
}

auto Serializer<v2168::AddActorPacket>::deserialize(BinaryReader &stream) -> std::expected<v2168::AddActorPacket, std::error_code>
{
    v2168::AddActorPacket out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.actor_type = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.velocity = *v;
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.rot = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.y_head_rotation = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.y_body_rotation = static_cast<float>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.attributes.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.attributes.emplace_back();
            auto v = Serializer<SyncedAttribute>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.attributes.back() = *v;
        }
    }
    {
        auto v = Serializer<v2168::SynchedActorData::CopyableDataList>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.data = *v;
    }
    {
        auto v = Serializer<PropertySyncData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.synched_properties = *v;
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.links.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.links.emplace_back();
            auto v = Serializer<ActorLink>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.links.back() = *v;
        }
    }
    return out;
}

void Serializer<v2225::AddActorPacket>::serialize(BinaryWriter &stream, const v2225::AddActorPacket &value)
{
    stream.writeVarInt<std::int64_t>(value.entity_id);
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    stream.write(value.actor_type);
    Serializer<Vec3>::serialize(stream, value.pos);
    Serializer<Vec3>::serialize(stream, value.velocity);
    Serializer<Vec2>::serialize(stream, value.rot);
    stream.write<float>(value.y_head_rotation);
    stream.write<float>(value.y_body_rotation);
    stream.writeVarInt<std::uint32_t>(value.attributes.size());
    for (const auto &e0 : value.attributes) {
        Serializer<SyncedAttribute>::serialize(stream, e0);
    }
    Serializer<v2168::SynchedActorData::CopyableDataList>::serialize(stream, value.data);
    Serializer<PropertySyncData>::serialize(stream, value.synched_properties);
    stream.writeVarInt<std::uint32_t>(value.links.size());
    for (const auto &e0 : value.links) {
        Serializer<ActorLink>::serialize(stream, e0);
    }
    stream.write<bool>(value.passenger_block_data.has_value());
    if (value.passenger_block_data.has_value()) {
        Serializer<PassengerOfBlockArguments>::serialize(stream, (*value.passenger_block_data));
    }
}

auto Serializer<v2225::AddActorPacket>::deserialize(BinaryReader &stream) -> std::expected<v2225::AddActorPacket, std::error_code>
{
    v2225::AddActorPacket out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.actor_type = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.velocity = *v;
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.rot = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.y_head_rotation = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.y_body_rotation = static_cast<float>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.attributes.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.attributes.emplace_back();
            auto v = Serializer<SyncedAttribute>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.attributes.back() = *v;
        }
    }
    {
        auto v = Serializer<v2168::SynchedActorData::CopyableDataList>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.data = *v;
    }
    {
        auto v = Serializer<PropertySyncData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.synched_properties = *v;
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.links.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.links.emplace_back();
            auto v = Serializer<ActorLink>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.links.back() = *v;
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            PassengerOfBlockArguments staged{};
            auto v = Serializer<PassengerOfBlockArguments>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.passenger_block_data = std::move(staged);
        }
    }
    return out;
}

void Serializer<base::SetActorDataPacket>::serialize(BinaryWriter &stream, const base::SetActorDataPacket &value)
{
    stream.writeVarInt<std::uint64_t>(value.id);
    Serializer<base::SynchedActorData::CopyableDataList>::serialize(stream, value.packed_items);
    Serializer<PropertySyncData>::serialize(stream, value.synched_properties);
    stream.writeVarInt<std::uint64_t>(value.tick);
}

auto Serializer<base::SetActorDataPacket>::deserialize(BinaryReader &stream) -> std::expected<base::SetActorDataPacket, std::error_code>
{
    base::SetActorDataPacket out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = Serializer<base::SynchedActorData::CopyableDataList>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.packed_items = *v;
    }
    {
        auto v = Serializer<PropertySyncData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.synched_properties = *v;
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.tick = static_cast<PlayerInputTick>(*v);
    }
    return out;
}

void Serializer<v2168::SetActorDataPacket>::serialize(BinaryWriter &stream, const v2168::SetActorDataPacket &value)
{
    stream.writeVarInt<std::uint64_t>(value.id);
    Serializer<v2168::SynchedActorData::CopyableDataList>::serialize(stream, value.packed_items);
    Serializer<PropertySyncData>::serialize(stream, value.synched_properties);
    stream.writeVarInt<std::uint64_t>(value.tick);
}

auto Serializer<v2168::SetActorDataPacket>::deserialize(BinaryReader &stream) -> std::expected<v2168::SetActorDataPacket, std::error_code>
{
    v2168::SetActorDataPacket out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = Serializer<v2168::SynchedActorData::CopyableDataList>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.packed_items = *v;
    }
    {
        auto v = Serializer<PropertySyncData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.synched_properties = *v;
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.tick = static_cast<PlayerInputTick>(*v);
    }
    return out;
}

void Serializer<base::SetLastHurtByPacket>::serialize(BinaryWriter &stream, const base::SetLastHurtByPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.last_hurt_by);
}

auto Serializer<base::SetLastHurtByPacket>::deserialize(BinaryReader &stream) -> std::expected<base::SetLastHurtByPacket, std::error_code>
{
    base::SetLastHurtByPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.last_hurt_by = static_cast<base::ActorType>(*v);
    }
    return out;
}

void Serializer<v766::SetLastHurtByPacket>::serialize(BinaryWriter &stream, const v766::SetLastHurtByPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.last_hurt_by);
}

auto Serializer<v766::SetLastHurtByPacket>::deserialize(BinaryReader &stream) -> std::expected<v766::SetLastHurtByPacket, std::error_code>
{
    v766::SetLastHurtByPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.last_hurt_by = static_cast<v766::ActorType>(*v);
    }
    return out;
}

void Serializer<v800::SetLastHurtByPacket>::serialize(BinaryWriter &stream, const v800::SetLastHurtByPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.last_hurt_by);
}

auto Serializer<v800::SetLastHurtByPacket>::deserialize(BinaryReader &stream) -> std::expected<v800::SetLastHurtByPacket, std::error_code>
{
    v800::SetLastHurtByPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.last_hurt_by = static_cast<v800::ActorType>(*v);
    }
    return out;
}

void Serializer<v827::SetLastHurtByPacket>::serialize(BinaryWriter &stream, const v827::SetLastHurtByPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.last_hurt_by);
}

auto Serializer<v827::SetLastHurtByPacket>::deserialize(BinaryReader &stream) -> std::expected<v827::SetLastHurtByPacket, std::error_code>
{
    v827::SetLastHurtByPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.last_hurt_by = static_cast<v827::ActorType>(*v);
    }
    return out;
}

void Serializer<v924::SetLastHurtByPacket>::serialize(BinaryWriter &stream, const v924::SetLastHurtByPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.last_hurt_by);
}

auto Serializer<v924::SetLastHurtByPacket>::deserialize(BinaryReader &stream) -> std::expected<v924::SetLastHurtByPacket, std::error_code>
{
    v924::SetLastHurtByPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.last_hurt_by = static_cast<v924::ActorType>(*v);
    }
    return out;
}

void Serializer<v975::SetLastHurtByPacket>::serialize(BinaryWriter &stream, const v975::SetLastHurtByPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.last_hurt_by);
}

auto Serializer<v975::SetLastHurtByPacket>::deserialize(BinaryReader &stream) -> std::expected<v975::SetLastHurtByPacket, std::error_code>
{
    v975::SetLastHurtByPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.last_hurt_by = static_cast<v975::ActorType>(*v);
    }
    return out;
}

void Serializer<v2168::SetLastHurtByPacket>::serialize(BinaryWriter &stream, const v2168::SetLastHurtByPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.last_hurt_by);
}

auto Serializer<v2168::SetLastHurtByPacket>::deserialize(BinaryReader &stream) -> std::expected<v2168::SetLastHurtByPacket, std::error_code>
{
    v2168::SetLastHurtByPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.last_hurt_by = static_cast<v2168::ActorType>(*v);
    }
    return out;
}

void Serializer<v2225::SetLastHurtByPacket>::serialize(BinaryWriter &stream, const v2225::SetLastHurtByPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.last_hurt_by);
}

auto Serializer<v2225::SetLastHurtByPacket>::deserialize(BinaryReader &stream) -> std::expected<v2225::SetLastHurtByPacket, std::error_code>
{
    v2225::SetLastHurtByPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.last_hurt_by = static_cast<v2225::ActorType>(*v);
    }
    return out;
}

void Serializer<RemoveActorPacket>::serialize(BinaryWriter &stream, const RemoveActorPacket &value)
{
    stream.writeVarInt<std::int64_t>(value.entity_id);
}

auto Serializer<RemoveActorPacket>::deserialize(BinaryReader &stream) -> std::expected<RemoveActorPacket, std::error_code>
{
    RemoveActorPacket out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_id = static_cast<ActorUniqueID>(*v);
    }
    return out;
}

void Serializer<ActorPickRequestPacket>::serialize(BinaryWriter &stream, const ActorPickRequestPacket &value)
{
    stream.write<std::int64_t>(value.id);
    stream.write<std::uint8_t>(value.max_slots);
    stream.write<bool>(value.with_data);
}

auto Serializer<ActorPickRequestPacket>::deserialize(BinaryReader &stream) -> std::expected<ActorPickRequestPacket, std::error_code>
{
    ActorPickRequestPacket out;
    {
        auto v = stream.read<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.max_slots = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.with_data = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<AddBehaviorTreePacket>::serialize(BinaryWriter &stream, const AddBehaviorTreePacket &value)
{
    stream.write(value.json_input);
}

auto Serializer<AddBehaviorTreePacket>::deserialize(BinaryReader &stream) -> std::expected<AddBehaviorTreePacket, std::error_code>
{
    AddBehaviorTreePacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.json_input = *v;
    }
    return out;
}

void Serializer<TakeItemActorPacket>::serialize(BinaryWriter &stream, const TakeItemActorPacket &value)
{
    stream.writeVarInt<std::uint64_t>(value.item_id);
    stream.writeVarInt<std::uint64_t>(value.actor_id);
}

auto Serializer<TakeItemActorPacket>::deserialize(BinaryReader &stream) -> std::expected<TakeItemActorPacket, std::error_code>
{
    TakeItemActorPacket out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.item_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.actor_id = static_cast<ActorRuntimeID>(*v);
    }
    return out;
}

void Serializer<MoveActorAbsoluteData>::serialize(BinaryWriter &stream, const MoveActorAbsoluteData &value)
{
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    stream.write<std::uint8_t>(value.header);
    Serializer<Vec3>::serialize(stream, value.pos);
    stream.write<std::uint8_t>(value.rot_x);
    stream.write<std::uint8_t>(value.rot_y);
    stream.write<std::uint8_t>(value.rot_y_head);
}

auto Serializer<MoveActorAbsoluteData>::deserialize(BinaryReader &stream) -> std::expected<MoveActorAbsoluteData, std::error_code>
{
    MoveActorAbsoluteData out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.header = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.rot_x = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.rot_y = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.rot_y_head = static_cast<std::uint8_t>(*v);
    }
    return out;
}

void Serializer<MoveActorAbsolutePacket>::serialize(BinaryWriter &stream, const MoveActorAbsolutePacket &value)
{
    Serializer<MoveActorAbsoluteData>::serialize(stream, value.move_data);
}

auto Serializer<MoveActorAbsolutePacket>::deserialize(BinaryReader &stream) -> std::expected<MoveActorAbsolutePacket, std::error_code>
{
    MoveActorAbsolutePacket out;
    {
        auto v = Serializer<MoveActorAbsoluteData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.move_data = *v;
    }
    return out;
}

void Serializer<AddPaintingPacket>::serialize(BinaryWriter &stream, const AddPaintingPacket &value)
{
    stream.writeVarInt<std::int64_t>(value.entity_id);
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    Serializer<Vec3>::serialize(stream, value.pos);
    stream.writeVarInt<std::int32_t>(value.dir);
    stream.write(value.motif);
}

auto Serializer<AddPaintingPacket>::deserialize(BinaryReader &stream) -> std::expected<AddPaintingPacket, std::error_code>
{
    AddPaintingPacket out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.dir = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.motif = *v;
    }
    return out;
}

void Serializer<base::ActorEventPacket>::serialize(BinaryWriter &stream, const base::ActorEventPacket &value)
{
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    stream.write<std::uint8_t>(value.event_id);
    stream.writeVarInt<std::int32_t>(value.data);
}

auto Serializer<base::ActorEventPacket>::deserialize(BinaryReader &stream) -> std::expected<base::ActorEventPacket, std::error_code>
{
    base::ActorEventPacket out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.event_id = static_cast<base::ActorEvent>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.data = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<v859::ActorEventPacket>::serialize(BinaryWriter &stream, const v859::ActorEventPacket &value)
{
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    stream.write<std::uint8_t>(value.event_id);
    stream.writeVarInt<std::int32_t>(value.data);
}

auto Serializer<v859::ActorEventPacket>::deserialize(BinaryReader &stream) -> std::expected<v859::ActorEventPacket, std::error_code>
{
    v859::ActorEventPacket out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.event_id = static_cast<v859::ActorEvent>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.data = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<v898::ActorEventPacket>::serialize(BinaryWriter &stream, const v898::ActorEventPacket &value)
{
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    stream.write<std::uint8_t>(value.event_id);
    stream.writeVarInt<std::int32_t>(value.data);
}

auto Serializer<v898::ActorEventPacket>::deserialize(BinaryReader &stream) -> std::expected<v898::ActorEventPacket, std::error_code>
{
    v898::ActorEventPacket out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.event_id = static_cast<v898::ActorEvent>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.data = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<v975::ActorEventPacket>::serialize(BinaryWriter &stream, const v975::ActorEventPacket &value)
{
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    stream.write<std::uint8_t>(value.event_id);
    stream.writeVarInt<std::int32_t>(value.data);
    stream.write<bool>(value.fire_at_position.has_value());
    if (value.fire_at_position.has_value()) {
        Serializer<Vec3>::serialize(stream, (*value.fire_at_position));
    }
}

auto Serializer<v975::ActorEventPacket>::deserialize(BinaryReader &stream) -> std::expected<v975::ActorEventPacket, std::error_code>
{
    v975::ActorEventPacket out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.event_id = static_cast<v975::ActorEvent>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.data = static_cast<std::int32_t>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec3 staged{};
            auto v = Serializer<Vec3>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.fire_at_position = std::move(staged);
        }
    }
    return out;
}

void Serializer<SetActorMotionPacket>::serialize(BinaryWriter &stream, const SetActorMotionPacket &value)
{
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    Serializer<Vec3>::serialize(stream, value.motion);
    stream.writeVarInt<std::uint64_t>(value.tick);
}

auto Serializer<SetActorMotionPacket>::deserialize(BinaryReader &stream) -> std::expected<SetActorMotionPacket, std::error_code>
{
    SetActorMotionPacket out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.motion = *v;
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.tick = static_cast<PlayerInputTick>(*v);
    }
    return out;
}

void Serializer<SetActorLinkPacket>::serialize(BinaryWriter &stream, const SetActorLinkPacket &value)
{
    Serializer<ActorLink>::serialize(stream, value.link);
}

auto Serializer<SetActorLinkPacket>::deserialize(BinaryReader &stream) -> std::expected<SetActorLinkPacket, std::error_code>
{
    SetActorLinkPacket out;
    {
        auto v = Serializer<ActorLink>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.link = *v;
    }
    return out;
}

void Serializer<v2225::SetPassengerOfBlockPacket>::serialize(BinaryWriter &stream, const v2225::SetPassengerOfBlockPacket &value)
{
    stream.writeVarInt<std::int64_t>(value.passenger);
    stream.write<bool>(value.passenger_of_block_data.has_value());
    if (value.passenger_of_block_data.has_value()) {
        Serializer<PassengerOfBlockArguments>::serialize(stream, (*value.passenger_of_block_data));
    }
}

auto Serializer<v2225::SetPassengerOfBlockPacket>::deserialize(BinaryReader &stream) -> std::expected<v2225::SetPassengerOfBlockPacket, std::error_code>
{
    v2225::SetPassengerOfBlockPacket out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.passenger = static_cast<ActorUniqueID>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            PassengerOfBlockArguments staged{};
            auto v = Serializer<PassengerOfBlockArguments>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.passenger_of_block_data = std::move(staged);
        }
    }
    return out;
}

void Serializer<ActorSwingSource>::serialize(BinaryWriter &stream, ActorSwingSource value)
{
    stream.write(enum_name(value));
}

auto Serializer<ActorSwingSource>::deserialize(BinaryReader &stream) -> std::expected<ActorSwingSource, std::error_code>
{
    auto v = stream.read<std::string>();
    if (!v) return std::unexpected(v.error());
    const auto value = enum_cast<ActorSwingSource>(*v);
    if (!value) return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
    return *value;
}

void Serializer<base::AnimatePacket>::serialize(BinaryWriter &stream, const base::AnimatePacket &value)
{
    stream.writeVarInt<std::int32_t>(value.action);
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    if (((value.action) & (128)) != (0)) {
        stream.write<float>(value.data);
    }
}

auto Serializer<base::AnimatePacket>::deserialize(BinaryReader &stream) -> std::expected<base::AnimatePacket, std::error_code>
{
    base::AnimatePacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.action = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    if (((out.action) & (128)) != (0)) {
        {
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            out.data = static_cast<float>(*v);
        }
    }
    return out;
}

void Serializer<v800::AnimatePacket>::serialize(BinaryWriter &stream, const v800::AnimatePacket &value)
{
    stream.writeVarInt<std::int32_t>(value.action);
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    if (((value.action) & (128)) != (0)) {
        stream.write<float>(value.data);
    }
}

auto Serializer<v800::AnimatePacket>::deserialize(BinaryReader &stream) -> std::expected<v800::AnimatePacket, std::error_code>
{
    v800::AnimatePacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.action = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    if (((out.action) & (128)) != (0)) {
        {
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            out.data = static_cast<float>(*v);
        }
    }
    return out;
}

void Serializer<v859::AnimatePacket>::serialize(BinaryWriter &stream, const v859::AnimatePacket &value)
{
    stream.writeVarInt<std::int32_t>(value.action);
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    stream.write<float>(value.data);
    if (((value.action) & (128)) != (0)) {
        stream.write<float>(value.rowing_time);
    }
}

auto Serializer<v859::AnimatePacket>::deserialize(BinaryReader &stream) -> std::expected<v859::AnimatePacket, std::error_code>
{
    v859::AnimatePacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.action = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.data = static_cast<float>(*v);
    }
    if (((out.action) & (128)) != (0)) {
        {
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            out.rowing_time = static_cast<float>(*v);
        }
    }
    return out;
}

void Serializer<v898::AnimatePacket>::serialize(BinaryWriter &stream, const v898::AnimatePacket &value)
{
    stream.write<std::uint8_t>(value.action);
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    stream.write<float>(value.data);
    stream.write<bool>(value.swing_source.has_value());
    if (value.swing_source.has_value()) {
        Serializer<ActorSwingSource>::serialize(stream, (*value.swing_source));
    }
}

auto Serializer<v898::AnimatePacket>::deserialize(BinaryReader &stream) -> std::expected<v898::AnimatePacket, std::error_code>
{
    v898::AnimatePacket out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.action = static_cast<v898::AnimatePacket::Action>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.data = static_cast<float>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            ActorSwingSource staged{};
            auto v = Serializer<ActorSwingSource>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.swing_source = std::move(staged);
        }
    }
    return out;
}

void Serializer<v2225::AnimatePacket>::serialize(BinaryWriter &stream, const v2225::AnimatePacket &value)
{
    stream.write<std::uint8_t>(value.action);
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    stream.write<float>(value.data);
    stream.write<bool>(value.swing_source.has_value());
    if (value.swing_source.has_value()) {
        Serializer<ActorSwingSource>::serialize(stream, (*value.swing_source));
    }
    stream.write<std::uint8_t>(value.hand);
}

auto Serializer<v2225::AnimatePacket>::deserialize(BinaryReader &stream) -> std::expected<v2225::AnimatePacket, std::error_code>
{
    v2225::AnimatePacket out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.action = static_cast<v2225::AnimatePacket::Action>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.data = static_cast<float>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            ActorSwingSource staged{};
            auto v = Serializer<ActorSwingSource>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.swing_source = std::move(staged);
        }
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.hand = static_cast<HandSlot>(*v);
    }
    return out;
}

void Serializer<SpawnExperienceOrbPacket>::serialize(BinaryWriter &stream, const SpawnExperienceOrbPacket &value)
{
    Serializer<Vec3>::serialize(stream, value.pos);
    stream.writeVarInt<std::int32_t>(value.xp_value);
}

auto Serializer<SpawnExperienceOrbPacket>::deserialize(BinaryReader &stream) -> std::expected<SpawnExperienceOrbPacket, std::error_code>
{
    SpawnExperienceOrbPacket out;
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.xp_value = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<AvailableActorIdentifiersPacket>::serialize(BinaryWriter &stream, const AvailableActorIdentifiersPacket &value)
{
    Serializer<CompoundTag>::serialize(stream, value.identifier_list);
}

auto Serializer<AvailableActorIdentifiersPacket>::deserialize(BinaryReader &stream) -> std::expected<AvailableActorIdentifiersPacket, std::error_code>
{
    AvailableActorIdentifiersPacket out;
    {
        auto v = Serializer<CompoundTag>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.identifier_list = *v;
    }
    return out;
}

void Serializer<MotionPredictionHintsPacket>::serialize(BinaryWriter &stream, const MotionPredictionHintsPacket &value)
{
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    Serializer<Vec3>::serialize(stream, value.motion);
    stream.write<bool>(value.on_ground);
}

auto Serializer<MotionPredictionHintsPacket>::deserialize(BinaryReader &stream) -> std::expected<MotionPredictionHintsPacket, std::error_code>
{
    MotionPredictionHintsPacket out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.motion = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.on_ground = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<DeathInfoPacket>::serialize(BinaryWriter &stream, const DeathInfoPacket &value)
{
    stream.write(value.death_cause_attack_name);
    stream.writeVarInt<std::uint32_t>(value.death_cause_message_list.size());
    for (const auto &e0 : value.death_cause_message_list) {
        stream.write(e0);
    }
}

auto Serializer<DeathInfoPacket>::deserialize(BinaryReader &stream) -> std::expected<DeathInfoPacket, std::error_code>
{
    DeathInfoPacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.death_cause_attack_name = *v;
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.death_cause_message_list.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.death_cause_message_list.emplace_back();
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.death_cause_message_list.back() = *v;
        }
    }
    return out;
}

void Serializer<SyncActorPropertyPacket>::serialize(BinaryWriter &stream, const SyncActorPropertyPacket &value)
{
    Serializer<CompoundTag>::serialize(stream, value.property_data);
}

auto Serializer<SyncActorPropertyPacket>::deserialize(BinaryReader &stream) -> std::expected<SyncActorPropertyPacket, std::error_code>
{
    SyncActorPropertyPacket out;
    {
        auto v = Serializer<CompoundTag>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.property_data = *v;
    }
    return out;
}

void Serializer<ChangeMobPropertyPacket>::serialize(BinaryWriter &stream, const ChangeMobPropertyPacket &value)
{
    stream.writeVarInt<std::int64_t>(value.actor_id);
    stream.write(value.prop_name);
    stream.write<bool>(value.bool_component_val);
    stream.write(value.string_component_val);
    stream.writeVarInt<std::int32_t>(value.int_component_val);
    stream.write<float>(value.float_component_val);
}

auto Serializer<ChangeMobPropertyPacket>::deserialize(BinaryReader &stream) -> std::expected<ChangeMobPropertyPacket, std::error_code>
{
    ChangeMobPropertyPacket out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.actor_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.prop_name = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.bool_component_val = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.string_component_val = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.int_component_val = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.float_component_val = static_cast<float>(*v);
    }
    return out;
}

void Serializer<AnimateEntityPacket>::serialize(BinaryWriter &stream, const AnimateEntityPacket &value)
{
    stream.write(value.animation);
    stream.write(value.next_state);
    stream.write(value.stop_expression);
    stream.write<std::int32_t>(value.stop_expression_version);
    stream.write(value.controller);
    stream.write<float>(value.blend_out_time);
    stream.writeVarInt<std::uint32_t>(value.runtime_ids.size());
    for (const auto &e0 : value.runtime_ids) {
        stream.writeVarInt<std::uint64_t>(e0);
    }
}

auto Serializer<AnimateEntityPacket>::deserialize(BinaryReader &stream) -> std::expected<AnimateEntityPacket, std::error_code>
{
    AnimateEntityPacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.animation = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.next_state = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.stop_expression = *v;
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.stop_expression_version = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.controller = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.blend_out_time = static_cast<float>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.runtime_ids.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.runtime_ids.emplace_back();
            auto v = stream.readVarInt<std::uint64_t>();
            if (!v) return std::unexpected(v.error());
            out.runtime_ids.back() = static_cast<ActorRuntimeID>(*v);
        }
    }
    return out;
}

void Serializer<NpcRequestPacket>::serialize(BinaryWriter &stream, const NpcRequestPacket &value)
{
    stream.writeVarInt<std::uint64_t>(value.id);
    stream.write<std::uint8_t>(value.type);
    stream.write(value.actions);
    stream.write<std::uint8_t>(value.action_index);
    stream.write(value.scene_name);
}

auto Serializer<NpcRequestPacket>::deserialize(BinaryReader &stream) -> std::expected<NpcRequestPacket, std::error_code>
{
    NpcRequestPacket out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<NpcRequestPacket::RequestType>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.actions = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.action_index = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.scene_name = *v;
    }
    return out;
}

void Serializer<NpcDialoguePacket>::serialize(BinaryWriter &stream, const NpcDialoguePacket &value)
{
    stream.write<std::uint64_t>(value.npc_id);
    stream.writeVarInt<std::int32_t>(value.npc_dialogue_action_type);
    stream.write(value.dialogue);
    stream.write(value.scene_name);
    stream.write(value.npc_name);
    stream.write(value.action_json);
}

auto Serializer<NpcDialoguePacket>::deserialize(BinaryReader &stream) -> std::expected<NpcDialoguePacket, std::error_code>
{
    NpcDialoguePacket out;
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.npc_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.npc_dialogue_action_type = static_cast<NpcDialoguePacket::NpcDialogueActionType>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.dialogue = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.scene_name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.npc_name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.action_json = *v;
    }
    return out;
}

void Serializer<base::AddItemActorPacket>::serialize(BinaryWriter &stream, const base::AddItemActorPacket &value)
{
    stream.writeVarInt<std::int64_t>(value.id);
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    Serializer<NetworkItemStackDescriptor>::serialize(stream, value.item);
    Serializer<Vec3>::serialize(stream, value.pos);
    Serializer<Vec3>::serialize(stream, value.velocity);
    Serializer<base::SynchedActorData::CopyableDataList>::serialize(stream, value.data);
    stream.write<bool>(value.is_from_fishing);
}

auto Serializer<base::AddItemActorPacket>::deserialize(BinaryReader &stream) -> std::expected<base::AddItemActorPacket, std::error_code>
{
    base::AddItemActorPacket out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = Serializer<NetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.item = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.velocity = *v;
    }
    {
        auto v = Serializer<base::SynchedActorData::CopyableDataList>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.data = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_from_fishing = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v2168::AddItemActorPacket>::serialize(BinaryWriter &stream, const v2168::AddItemActorPacket &value)
{
    stream.writeVarInt<std::int64_t>(value.id);
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    Serializer<v2168::SerializedNetworkItemStackDescriptor>::serialize(stream, value.item);
    Serializer<Vec3>::serialize(stream, value.pos);
    Serializer<Vec3>::serialize(stream, value.velocity);
    Serializer<v2168::SynchedActorData::CopyableDataList>::serialize(stream, value.data);
    stream.write<bool>(value.is_from_fishing);
}

auto Serializer<v2168::AddItemActorPacket>::deserialize(BinaryReader &stream) -> std::expected<v2168::AddItemActorPacket, std::error_code>
{
    v2168::AddItemActorPacket out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = Serializer<v2168::SerializedNetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.item = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.velocity = *v;
    }
    {
        auto v = Serializer<v2168::SynchedActorData::CopyableDataList>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.data = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_from_fishing = static_cast<bool>(*v);
    }
    return out;
}

}  // namespace bedrock::protocol
