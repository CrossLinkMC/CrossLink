#include <bedrock/protocol/enchanting.h>

namespace bedrock::protocol {


void Serializer<base::EnchantmentInstance>::serialize(BinaryWriter &stream, const base::EnchantmentInstance &value)
{
    stream.write<std::uint8_t>(value.enchant_type);
    stream.write<std::uint8_t>(value.level);
}

auto Serializer<base::EnchantmentInstance>::deserialize(BinaryReader &stream) -> std::expected<base::EnchantmentInstance, std::error_code>
{
    base::EnchantmentInstance out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.enchant_type = static_cast<base::Enchant::Type>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.level = static_cast<std::uint8_t>(*v);
    }
    return out;
}

void Serializer<v898::EnchantmentInstance>::serialize(BinaryWriter &stream, const v898::EnchantmentInstance &value)
{
    stream.write<std::uint8_t>(value.enchant_type);
    stream.write<std::uint8_t>(value.level);
}

auto Serializer<v898::EnchantmentInstance>::deserialize(BinaryReader &stream) -> std::expected<v898::EnchantmentInstance, std::error_code>
{
    v898::EnchantmentInstance out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.enchant_type = static_cast<v898::Enchant::Type>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.level = static_cast<std::uint8_t>(*v);
    }
    return out;
}

void Serializer<base::ItemEnchants>::serialize(BinaryWriter &stream, const base::ItemEnchants &value)
{
    stream.write<std::int32_t>(value.slot);
    for (const auto &e0 : value.item_enchants) {
        stream.writeVarInt<std::uint32_t>(e0.size());
        for (const auto &e1 : e0) {
            Serializer<base::EnchantmentInstance>::serialize(stream, e1);
        }
    }
}

auto Serializer<base::ItemEnchants>::deserialize(BinaryReader &stream) -> std::expected<base::ItemEnchants, std::error_code>
{
    base::ItemEnchants out;
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::int32_t>(*v);
    }
    {
        for (std::size_t i0 = 0; i0 < 3; ++i0) {
            auto len1 = stream.readVarInt<std::uint32_t>();
            if (!len1) return std::unexpected(len1.error());
            out.item_enchants[i0].clear();
            for (auto rep1 = *len1; rep1 > 0; --rep1) {
                out.item_enchants[i0].emplace_back();
                auto v = Serializer<base::EnchantmentInstance>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                out.item_enchants[i0].back() = *v;
            }
        }
    }
    return out;
}

void Serializer<v898::ItemEnchants>::serialize(BinaryWriter &stream, const v898::ItemEnchants &value)
{
    stream.write<std::int32_t>(value.slot);
    for (const auto &e0 : value.item_enchants) {
        stream.writeVarInt<std::uint32_t>(e0.size());
        for (const auto &e1 : e0) {
            Serializer<v898::EnchantmentInstance>::serialize(stream, e1);
        }
    }
}

auto Serializer<v898::ItemEnchants>::deserialize(BinaryReader &stream) -> std::expected<v898::ItemEnchants, std::error_code>
{
    v898::ItemEnchants out;
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::int32_t>(*v);
    }
    {
        for (std::size_t i0 = 0; i0 < 3; ++i0) {
            auto len1 = stream.readVarInt<std::uint32_t>();
            if (!len1) return std::unexpected(len1.error());
            out.item_enchants[i0].clear();
            for (auto rep1 = *len1; rep1 > 0; --rep1) {
                out.item_enchants[i0].emplace_back();
                auto v = Serializer<v898::EnchantmentInstance>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                out.item_enchants[i0].back() = *v;
            }
        }
    }
    return out;
}

void Serializer<base::ItemEnchantOption>::serialize(BinaryWriter &stream, const base::ItemEnchantOption &value)
{
    stream.writeVarInt<std::uint32_t>(value.cost);
    Serializer<base::ItemEnchants>::serialize(stream, value.enchants);
    stream.write(value.enchant_name);
    Serializer<RecipeNetId>::serialize(stream, value.enchant_net_id);
}

auto Serializer<base::ItemEnchantOption>::deserialize(BinaryReader &stream) -> std::expected<base::ItemEnchantOption, std::error_code>
{
    base::ItemEnchantOption out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.cost = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = Serializer<base::ItemEnchants>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.enchants = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.enchant_name = *v;
    }
    {
        auto v = Serializer<RecipeNetId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.enchant_net_id = *v;
    }
    return out;
}

void Serializer<v898::ItemEnchantOption>::serialize(BinaryWriter &stream, const v898::ItemEnchantOption &value)
{
    stream.writeVarInt<std::uint32_t>(value.cost);
    Serializer<v898::ItemEnchants>::serialize(stream, value.enchants);
    stream.write(value.enchant_name);
    Serializer<RecipeNetId>::serialize(stream, value.enchant_net_id);
}

auto Serializer<v898::ItemEnchantOption>::deserialize(BinaryReader &stream) -> std::expected<v898::ItemEnchantOption, std::error_code>
{
    v898::ItemEnchantOption out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.cost = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = Serializer<v898::ItemEnchants>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.enchants = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.enchant_name = *v;
    }
    {
        auto v = Serializer<RecipeNetId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.enchant_net_id = *v;
    }
    return out;
}

void Serializer<v975::ItemEnchantOption>::serialize(BinaryWriter &stream, const v975::ItemEnchantOption &value)
{
    stream.write<std::uint8_t>(value.cost);
    Serializer<v898::ItemEnchants>::serialize(stream, value.enchants);
    stream.write(value.enchant_name);
    Serializer<RecipeNetId>::serialize(stream, value.enchant_net_id);
}

auto Serializer<v975::ItemEnchantOption>::deserialize(BinaryReader &stream) -> std::expected<v975::ItemEnchantOption, std::error_code>
{
    v975::ItemEnchantOption out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.cost = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = Serializer<v898::ItemEnchants>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.enchants = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.enchant_name = *v;
    }
    {
        auto v = Serializer<RecipeNetId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.enchant_net_id = *v;
    }
    return out;
}

void Serializer<base::PlayerEnchantOptionsPacket>::serialize(BinaryWriter &stream, const base::PlayerEnchantOptionsPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.options.size());
    for (const auto &e0 : value.options) {
        Serializer<base::ItemEnchantOption>::serialize(stream, e0);
    }
}

auto Serializer<base::PlayerEnchantOptionsPacket>::deserialize(BinaryReader &stream) -> std::expected<base::PlayerEnchantOptionsPacket, std::error_code>
{
    base::PlayerEnchantOptionsPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.options.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.options.emplace_back();
            auto v = Serializer<base::ItemEnchantOption>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.options.back() = *v;
        }
    }
    return out;
}

void Serializer<v898::PlayerEnchantOptionsPacket>::serialize(BinaryWriter &stream, const v898::PlayerEnchantOptionsPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.options.size());
    for (const auto &e0 : value.options) {
        Serializer<v898::ItemEnchantOption>::serialize(stream, e0);
    }
}

auto Serializer<v898::PlayerEnchantOptionsPacket>::deserialize(BinaryReader &stream) -> std::expected<v898::PlayerEnchantOptionsPacket, std::error_code>
{
    v898::PlayerEnchantOptionsPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.options.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.options.emplace_back();
            auto v = Serializer<v898::ItemEnchantOption>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.options.back() = *v;
        }
    }
    return out;
}

void Serializer<v975::PlayerEnchantOptionsPacket>::serialize(BinaryWriter &stream, const v975::PlayerEnchantOptionsPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.options.size());
    for (const auto &e0 : value.options) {
        Serializer<v975::ItemEnchantOption>::serialize(stream, e0);
    }
}

auto Serializer<v975::PlayerEnchantOptionsPacket>::deserialize(BinaryReader &stream) -> std::expected<v975::PlayerEnchantOptionsPacket, std::error_code>
{
    v975::PlayerEnchantOptionsPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.options.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.options.emplace_back();
            auto v = Serializer<v975::ItemEnchantOption>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.options.back() = *v;
        }
    }
    return out;
}

}  // namespace bedrock::protocol
