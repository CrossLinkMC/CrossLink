#include <bedrock/protocol/map.h>

namespace bedrock::protocol {


void Serializer<base::MapItemTrackedActor::UniqueId>::serialize(BinaryWriter &stream, const base::MapItemTrackedActor::UniqueId &value)
{
    stream.write<std::int32_t>(value.type);
    if ((value.type) == (base::MapItemTrackedActor::Type::Entity)) {
        stream.writeVarInt<std::int64_t>(value.key_entity_id);
    }
    if ((value.type) == (base::MapItemTrackedActor::Type::BlockEntity)) {
        Serializer<base::NetworkBlockPosition>::serialize(stream, value.key_block_pos);
    }
}

auto Serializer<base::MapItemTrackedActor::UniqueId>::deserialize(BinaryReader &stream) -> std::expected<base::MapItemTrackedActor::UniqueId, std::error_code>
{
    base::MapItemTrackedActor::UniqueId out;
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<base::MapItemTrackedActor::Type>(*v);
    }
    if ((out.type) == (base::MapItemTrackedActor::Type::Entity)) {
        {
            auto v = stream.readVarInt<std::int64_t>();
            if (!v) return std::unexpected(v.error());
            out.key_entity_id = static_cast<ActorUniqueID>(*v);
        }
    }
    if ((out.type) == (base::MapItemTrackedActor::Type::BlockEntity)) {
        {
            auto v = Serializer<base::NetworkBlockPosition>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.key_block_pos = *v;
        }
    }
    return out;
}

void Serializer<v944::MapItemTrackedActor::UniqueId>::serialize(BinaryWriter &stream, const v944::MapItemTrackedActor::UniqueId &value)
{
    stream.write<std::int32_t>(value.type);
    if ((value.type) == (v944::MapItemTrackedActor::Type::Entity)) {
        stream.writeVarInt<std::int64_t>(value.key_entity_id);
    }
    if ((value.type) == (v944::MapItemTrackedActor::Type::BlockEntity)) {
        Serializer<BlockPos>::serialize(stream, value.key_block_pos);
    }
}

auto Serializer<v944::MapItemTrackedActor::UniqueId>::deserialize(BinaryReader &stream) -> std::expected<v944::MapItemTrackedActor::UniqueId, std::error_code>
{
    v944::MapItemTrackedActor::UniqueId out;
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<v944::MapItemTrackedActor::Type>(*v);
    }
    if ((out.type) == (v944::MapItemTrackedActor::Type::Entity)) {
        {
            auto v = stream.readVarInt<std::int64_t>();
            if (!v) return std::unexpected(v.error());
            out.key_entity_id = static_cast<ActorUniqueID>(*v);
        }
    }
    if ((out.type) == (v944::MapItemTrackedActor::Type::BlockEntity)) {
        {
            auto v = Serializer<BlockPos>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.key_block_pos = *v;
        }
    }
    return out;
}

void Serializer<v2168::MapItemTrackedActor::UniqueId>::serialize(BinaryWriter &stream, const v2168::MapItemTrackedActor::UniqueId &value)
{
    stream.write<std::int32_t>(value.type);
    stream.write<bool>(value.key_entity_id.has_value());
    if (value.key_entity_id.has_value()) {
        stream.writeVarInt<std::int64_t>((*value.key_entity_id));
    }
    stream.write<bool>(value.key_block_pos.has_value());
    if (value.key_block_pos.has_value()) {
        Serializer<BlockPos>::serialize(stream, (*value.key_block_pos));
    }
}

auto Serializer<v2168::MapItemTrackedActor::UniqueId>::deserialize(BinaryReader &stream) -> std::expected<v2168::MapItemTrackedActor::UniqueId, std::error_code>
{
    v2168::MapItemTrackedActor::UniqueId out;
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<v2168::MapItemTrackedActor::Type>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            ActorUniqueID staged{};
            auto v = stream.readVarInt<std::int64_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<ActorUniqueID>(*v);
            out.key_entity_id = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            BlockPos staged{};
            auto v = Serializer<BlockPos>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.key_block_pos = std::move(staged);
        }
    }
    return out;
}

void Serializer<base::MapDecoration>::serialize(BinaryWriter &stream, const base::MapDecoration &value)
{
    stream.write<std::int8_t>(value.image);
    stream.write<std::int8_t>(value.rotation);
    stream.write<std::int8_t>(value.x);
    stream.write<std::int8_t>(value.y);
    stream.write(value.label);
    stream.writeVarInt<std::uint32_t>(value.color);
}

auto Serializer<base::MapDecoration>::deserialize(BinaryReader &stream) -> std::expected<base::MapDecoration, std::error_code>
{
    base::MapDecoration out;
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.image = static_cast<base::MapDecoration::Type>(*v);
    }
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.rotation = static_cast<std::int8_t>(*v);
    }
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.x = static_cast<std::int8_t>(*v);
    }
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.y = static_cast<std::int8_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.label = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.color = static_cast<Color>(*v);
    }
    return out;
}

void Serializer<v2168::MapDecoration>::serialize(BinaryWriter &stream, const v2168::MapDecoration &value)
{
    stream.write<std::int8_t>(value.image);
    stream.write<std::int8_t>(value.rotation);
    stream.write<std::int8_t>(value.x);
    stream.write<std::int8_t>(value.y);
    stream.write(value.label);
    stream.write<std::int32_t>(value.color);
}

auto Serializer<v2168::MapDecoration>::deserialize(BinaryReader &stream) -> std::expected<v2168::MapDecoration, std::error_code>
{
    v2168::MapDecoration out;
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.image = static_cast<v2168::MapDecoration::Type>(*v);
    }
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.rotation = static_cast<std::int8_t>(*v);
    }
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.x = static_cast<std::int8_t>(*v);
    }
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.y = static_cast<std::int8_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.label = *v;
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.color = static_cast<Color>(*v);
    }
    return out;
}

void Serializer<v2193::MapDecoration>::serialize(BinaryWriter &stream, const v2193::MapDecoration &value)
{
    stream.write<std::int8_t>(value.image);
    stream.write<std::int8_t>(value.rotation);
    stream.write<std::int8_t>(value.x);
    stream.write<std::int8_t>(value.y);
    stream.write(value.label);
    stream.write<std::int32_t>(value.color);
}

auto Serializer<v2193::MapDecoration>::deserialize(BinaryReader &stream) -> std::expected<v2193::MapDecoration, std::error_code>
{
    v2193::MapDecoration out;
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.image = static_cast<v2193::MapDecoration::Type>(*v);
    }
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.rotation = static_cast<std::int8_t>(*v);
    }
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.x = static_cast<std::int8_t>(*v);
    }
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.y = static_cast<std::int8_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.label = *v;
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.color = static_cast<Color>(*v);
    }
    return out;
}

void Serializer<base::ClientboundMapItemDataPacket>::serialize(BinaryWriter &stream, const base::ClientboundMapItemDataPacket &value)
{
    stream.writeVarInt<std::int64_t>(value.map_id);
    stream.writeVarInt<std::uint32_t>(value.type);
    stream.write<std::uint8_t>(value.dimension);
    stream.write<bool>(value.locked);
    Serializer<BlockPos>::serialize(stream, value.map_origin);
    if (((value.type) & (8)) != (0)) {
        stream.writeVarInt<std::uint32_t>(value.map_ids.size());
        for (const auto &e0 : value.map_ids) {
            stream.writeVarInt<std::int64_t>(e0);
        }
    }
    if (((value.type) & (14)) != (0)) {
        stream.write<std::int8_t>(value.scale);
    }
    if (((value.type) & (4)) != (0)) {
        stream.writeVarInt<std::uint32_t>(value.unique_ids.size());
        for (const auto &e0 : value.unique_ids) {
            Serializer<base::MapItemTrackedActor::UniqueId>::serialize(stream, e0);
        }
        stream.writeVarInt<std::uint32_t>(value.decorations.size());
        for (const auto &e0 : value.decorations) {
            Serializer<base::MapDecoration>::serialize(stream, e0);
        }
    }
    if (((value.type) & (2)) != (0)) {
        stream.writeVarInt<std::int32_t>(value.width);
        stream.writeVarInt<std::int32_t>(value.height);
        stream.writeVarInt<std::int32_t>(value.start_x);
        stream.writeVarInt<std::int32_t>(value.start_y);
        stream.writeVarInt<std::uint32_t>(value.map_pixels.size());
        for (const auto &e0 : value.map_pixels) {
            stream.writeVarInt<std::uint32_t>(e0);
        }
    }
}

auto Serializer<base::ClientboundMapItemDataPacket>::deserialize(BinaryReader &stream) -> std::expected<base::ClientboundMapItemDataPacket, std::error_code>
{
    base::ClientboundMapItemDataPacket out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.map_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.dimension = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.locked = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.map_origin = *v;
    }
    if (((out.type) & (8)) != (0)) {
        {
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            out.map_ids.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                out.map_ids.emplace_back();
                auto v = stream.readVarInt<std::int64_t>();
                if (!v) return std::unexpected(v.error());
                out.map_ids.back() = static_cast<ActorUniqueID>(*v);
            }
        }
    }
    if (((out.type) & (14)) != (0)) {
        {
            auto v = stream.read<std::int8_t>();
            if (!v) return std::unexpected(v.error());
            out.scale = static_cast<std::int8_t>(*v);
        }
    }
    if (((out.type) & (4)) != (0)) {
        {
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            out.unique_ids.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                out.unique_ids.emplace_back();
                auto v = Serializer<base::MapItemTrackedActor::UniqueId>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                out.unique_ids.back() = *v;
            }
        }
        {
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            out.decorations.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                out.decorations.emplace_back();
                auto v = Serializer<base::MapDecoration>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                out.decorations.back() = *v;
            }
        }
    }
    if (((out.type) & (2)) != (0)) {
        {
            auto v = stream.readVarInt<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            out.width = static_cast<std::int32_t>(*v);
        }
        {
            auto v = stream.readVarInt<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            out.height = static_cast<std::int32_t>(*v);
        }
        {
            auto v = stream.readVarInt<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            out.start_x = static_cast<std::int32_t>(*v);
        }
        {
            auto v = stream.readVarInt<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            out.start_y = static_cast<std::int32_t>(*v);
        }
        {
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            out.map_pixels.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                out.map_pixels.emplace_back();
                auto v = stream.readVarInt<std::uint32_t>();
                if (!v) return std::unexpected(v.error());
                out.map_pixels.back() = static_cast<std::uint32_t>(*v);
            }
        }
    }
    return out;
}

void Serializer<v944::ClientboundMapItemDataPacket>::serialize(BinaryWriter &stream, const v944::ClientboundMapItemDataPacket &value)
{
    stream.writeVarInt<std::int64_t>(value.map_id);
    stream.writeVarInt<std::uint32_t>(value.type);
    stream.write<std::uint8_t>(value.dimension);
    stream.write<bool>(value.locked);
    Serializer<BlockPos>::serialize(stream, value.map_origin);
    if (((value.type) & (8)) != (0)) {
        stream.writeVarInt<std::uint32_t>(value.map_ids.size());
        for (const auto &e0 : value.map_ids) {
            stream.writeVarInt<std::int64_t>(e0);
        }
    }
    if (((value.type) & (14)) != (0)) {
        stream.write<std::int8_t>(value.scale);
    }
    if (((value.type) & (4)) != (0)) {
        stream.writeVarInt<std::uint32_t>(value.unique_ids.size());
        for (const auto &e0 : value.unique_ids) {
            Serializer<v944::MapItemTrackedActor::UniqueId>::serialize(stream, e0);
        }
        stream.writeVarInt<std::uint32_t>(value.decorations.size());
        for (const auto &e0 : value.decorations) {
            Serializer<base::MapDecoration>::serialize(stream, e0);
        }
    }
    if (((value.type) & (2)) != (0)) {
        stream.writeVarInt<std::int32_t>(value.width);
        stream.writeVarInt<std::int32_t>(value.height);
        stream.writeVarInt<std::int32_t>(value.start_x);
        stream.writeVarInt<std::int32_t>(value.start_y);
        stream.writeVarInt<std::uint32_t>(value.map_pixels.size());
        for (const auto &e0 : value.map_pixels) {
            stream.writeVarInt<std::uint32_t>(e0);
        }
    }
}

auto Serializer<v944::ClientboundMapItemDataPacket>::deserialize(BinaryReader &stream) -> std::expected<v944::ClientboundMapItemDataPacket, std::error_code>
{
    v944::ClientboundMapItemDataPacket out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.map_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.dimension = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.locked = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.map_origin = *v;
    }
    if (((out.type) & (8)) != (0)) {
        {
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            out.map_ids.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                out.map_ids.emplace_back();
                auto v = stream.readVarInt<std::int64_t>();
                if (!v) return std::unexpected(v.error());
                out.map_ids.back() = static_cast<ActorUniqueID>(*v);
            }
        }
    }
    if (((out.type) & (14)) != (0)) {
        {
            auto v = stream.read<std::int8_t>();
            if (!v) return std::unexpected(v.error());
            out.scale = static_cast<std::int8_t>(*v);
        }
    }
    if (((out.type) & (4)) != (0)) {
        {
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            out.unique_ids.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                out.unique_ids.emplace_back();
                auto v = Serializer<v944::MapItemTrackedActor::UniqueId>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                out.unique_ids.back() = *v;
            }
        }
        {
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            out.decorations.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                out.decorations.emplace_back();
                auto v = Serializer<base::MapDecoration>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                out.decorations.back() = *v;
            }
        }
    }
    if (((out.type) & (2)) != (0)) {
        {
            auto v = stream.readVarInt<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            out.width = static_cast<std::int32_t>(*v);
        }
        {
            auto v = stream.readVarInt<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            out.height = static_cast<std::int32_t>(*v);
        }
        {
            auto v = stream.readVarInt<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            out.start_x = static_cast<std::int32_t>(*v);
        }
        {
            auto v = stream.readVarInt<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            out.start_y = static_cast<std::int32_t>(*v);
        }
        {
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            out.map_pixels.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                out.map_pixels.emplace_back();
                auto v = stream.readVarInt<std::uint32_t>();
                if (!v) return std::unexpected(v.error());
                out.map_pixels.back() = static_cast<std::uint32_t>(*v);
            }
        }
    }
    return out;
}

void Serializer<v2168::ClientboundMapItemDataPacket>::serialize(BinaryWriter &stream, const v2168::ClientboundMapItemDataPacket &value)
{
    stream.writeVarInt<std::int64_t>(value.map_id);
    stream.write<std::uint8_t>(value.dimension);
    stream.write<bool>(value.locked);
    Serializer<BlockPos>::serialize(stream, value.map_origin);
    stream.write<bool>(value.creation_map_ids.has_value());
    if (value.creation_map_ids.has_value()) {
        stream.writeVarInt<std::uint32_t>((*value.creation_map_ids).size());
        for (const auto &e0 : (*value.creation_map_ids)) {
            stream.writeVarInt<std::int64_t>(e0);
        }
    }
    stream.write<bool>(value.scale.has_value());
    if (value.scale.has_value()) {
        stream.write<std::int8_t>((*value.scale));
    }
    stream.write<bool>(value.unique_ids.has_value());
    if (value.unique_ids.has_value()) {
        stream.writeVarInt<std::uint32_t>((*value.unique_ids).size());
        for (const auto &e0 : (*value.unique_ids)) {
            Serializer<v2168::MapItemTrackedActor::UniqueId>::serialize(stream, e0);
        }
    }
    stream.write<bool>(value.decorations.has_value());
    if (value.decorations.has_value()) {
        stream.writeVarInt<std::uint32_t>((*value.decorations).size());
        for (const auto &e0 : (*value.decorations)) {
            Serializer<v2168::MapDecoration>::serialize(stream, e0);
        }
    }
    stream.write<bool>(value.width.has_value());
    if (value.width.has_value()) {
        stream.writeVarInt<std::int32_t>((*value.width));
    }
    stream.write<bool>(value.height.has_value());
    if (value.height.has_value()) {
        stream.writeVarInt<std::int32_t>((*value.height));
    }
    stream.write<bool>(value.start_x.has_value());
    if (value.start_x.has_value()) {
        stream.writeVarInt<std::int32_t>((*value.start_x));
    }
    stream.write<bool>(value.start_y.has_value());
    if (value.start_y.has_value()) {
        stream.writeVarInt<std::int32_t>((*value.start_y));
    }
    stream.write<bool>(value.map_pixels.has_value());
    if (value.map_pixels.has_value()) {
        stream.writeVarInt<std::uint32_t>((*value.map_pixels).size());
        for (const auto &e0 : (*value.map_pixels)) {
            stream.write<std::uint32_t>(e0);
        }
    }
}

auto Serializer<v2168::ClientboundMapItemDataPacket>::deserialize(BinaryReader &stream) -> std::expected<v2168::ClientboundMapItemDataPacket, std::error_code>
{
    v2168::ClientboundMapItemDataPacket out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.map_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.dimension = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.locked = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.map_origin = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::vector<ActorUniqueID> staged{};
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            staged.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                staged.emplace_back();
                auto v = stream.readVarInt<std::int64_t>();
                if (!v) return std::unexpected(v.error());
                staged.back() = static_cast<ActorUniqueID>(*v);
            }
            out.creation_map_ids = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::int8_t staged{};
            auto v = stream.read<std::int8_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<std::int8_t>(*v);
            out.scale = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::vector<v2168::MapItemTrackedActor::UniqueId> staged{};
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            staged.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                staged.emplace_back();
                auto v = Serializer<v2168::MapItemTrackedActor::UniqueId>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                staged.back() = *v;
            }
            out.unique_ids = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::vector<v2168::MapDecoration> staged{};
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            staged.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                staged.emplace_back();
                auto v = Serializer<v2168::MapDecoration>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                staged.back() = *v;
            }
            out.decorations = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::int32_t staged{};
            auto v = stream.readVarInt<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<std::int32_t>(*v);
            out.width = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::int32_t staged{};
            auto v = stream.readVarInt<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<std::int32_t>(*v);
            out.height = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::int32_t staged{};
            auto v = stream.readVarInt<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<std::int32_t>(*v);
            out.start_x = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::int32_t staged{};
            auto v = stream.readVarInt<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<std::int32_t>(*v);
            out.start_y = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::vector<std::uint32_t> staged{};
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            staged.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                staged.emplace_back();
                auto v = stream.read<std::uint32_t>();
                if (!v) return std::unexpected(v.error());
                staged.back() = static_cast<std::uint32_t>(*v);
            }
            out.map_pixels = std::move(staged);
        }
    }
    return out;
}

void Serializer<v2193::ClientboundMapItemDataPacket>::serialize(BinaryWriter &stream, const v2193::ClientboundMapItemDataPacket &value)
{
    stream.writeVarInt<std::int64_t>(value.map_id);
    stream.write<std::uint8_t>(value.dimension);
    stream.write<bool>(value.locked);
    Serializer<BlockPos>::serialize(stream, value.map_origin);
    stream.write<bool>(value.creation_map_ids.has_value());
    if (value.creation_map_ids.has_value()) {
        stream.writeVarInt<std::uint32_t>((*value.creation_map_ids).size());
        for (const auto &e0 : (*value.creation_map_ids)) {
            stream.writeVarInt<std::int64_t>(e0);
        }
    }
    stream.write<bool>(value.scale.has_value());
    if (value.scale.has_value()) {
        stream.write<std::int8_t>((*value.scale));
    }
    stream.write<bool>(value.unique_ids.has_value());
    if (value.unique_ids.has_value()) {
        stream.writeVarInt<std::uint32_t>((*value.unique_ids).size());
        for (const auto &e0 : (*value.unique_ids)) {
            Serializer<v2168::MapItemTrackedActor::UniqueId>::serialize(stream, e0);
        }
    }
    stream.write<bool>(value.decorations.has_value());
    if (value.decorations.has_value()) {
        stream.writeVarInt<std::uint32_t>((*value.decorations).size());
        for (const auto &e0 : (*value.decorations)) {
            Serializer<v2193::MapDecoration>::serialize(stream, e0);
        }
    }
    stream.write<bool>(value.width.has_value());
    if (value.width.has_value()) {
        stream.writeVarInt<std::int32_t>((*value.width));
    }
    stream.write<bool>(value.height.has_value());
    if (value.height.has_value()) {
        stream.writeVarInt<std::int32_t>((*value.height));
    }
    stream.write<bool>(value.start_x.has_value());
    if (value.start_x.has_value()) {
        stream.writeVarInt<std::int32_t>((*value.start_x));
    }
    stream.write<bool>(value.start_y.has_value());
    if (value.start_y.has_value()) {
        stream.writeVarInt<std::int32_t>((*value.start_y));
    }
    stream.write<bool>(value.map_pixels.has_value());
    if (value.map_pixels.has_value()) {
        stream.writeVarInt<std::uint32_t>((*value.map_pixels).size());
        for (const auto &e0 : (*value.map_pixels)) {
            stream.write<std::uint32_t>(e0);
        }
    }
}

auto Serializer<v2193::ClientboundMapItemDataPacket>::deserialize(BinaryReader &stream) -> std::expected<v2193::ClientboundMapItemDataPacket, std::error_code>
{
    v2193::ClientboundMapItemDataPacket out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.map_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.dimension = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.locked = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.map_origin = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::vector<ActorUniqueID> staged{};
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            staged.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                staged.emplace_back();
                auto v = stream.readVarInt<std::int64_t>();
                if (!v) return std::unexpected(v.error());
                staged.back() = static_cast<ActorUniqueID>(*v);
            }
            out.creation_map_ids = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::int8_t staged{};
            auto v = stream.read<std::int8_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<std::int8_t>(*v);
            out.scale = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::vector<v2168::MapItemTrackedActor::UniqueId> staged{};
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            staged.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                staged.emplace_back();
                auto v = Serializer<v2168::MapItemTrackedActor::UniqueId>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                staged.back() = *v;
            }
            out.unique_ids = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::vector<v2193::MapDecoration> staged{};
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            staged.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                staged.emplace_back();
                auto v = Serializer<v2193::MapDecoration>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                staged.back() = *v;
            }
            out.decorations = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::int32_t staged{};
            auto v = stream.readVarInt<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<std::int32_t>(*v);
            out.width = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::int32_t staged{};
            auto v = stream.readVarInt<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<std::int32_t>(*v);
            out.height = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::int32_t staged{};
            auto v = stream.readVarInt<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<std::int32_t>(*v);
            out.start_x = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::int32_t staged{};
            auto v = stream.readVarInt<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<std::int32_t>(*v);
            out.start_y = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::vector<std::uint32_t> staged{};
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            staged.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                staged.emplace_back();
                auto v = stream.read<std::uint32_t>();
                if (!v) return std::unexpected(v.error());
                staged.back() = static_cast<std::uint32_t>(*v);
            }
            out.map_pixels = std::move(staged);
        }
    }
    return out;
}

void Serializer<MapInfoRequestPacket::ClientPixelsProxy>::serialize(BinaryWriter &stream, const MapInfoRequestPacket::ClientPixelsProxy &value)
{
    stream.write<std::uint32_t>(value.pixel);
    stream.write<std::uint16_t>(value.index);
}

auto Serializer<MapInfoRequestPacket::ClientPixelsProxy>::deserialize(BinaryReader &stream) -> std::expected<MapInfoRequestPacket::ClientPixelsProxy, std::error_code>
{
    MapInfoRequestPacket::ClientPixelsProxy out;
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.pixel = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.index = static_cast<std::uint16_t>(*v);
    }
    return out;
}

void Serializer<MapInfoRequestPacket>::serialize(BinaryWriter &stream, const MapInfoRequestPacket &value)
{
    stream.writeVarInt<std::int64_t>(value.map_id);
    stream.write<std::uint32_t>(value.client_pixels.size());
    for (const auto &e0 : value.client_pixels) {
        Serializer<MapInfoRequestPacket::ClientPixelsProxy>::serialize(stream, e0);
    }
}

auto Serializer<MapInfoRequestPacket>::deserialize(BinaryReader &stream) -> std::expected<MapInfoRequestPacket, std::error_code>
{
    MapInfoRequestPacket out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.map_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto len0 = stream.read<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.client_pixels.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.client_pixels.emplace_back();
            auto v = Serializer<MapInfoRequestPacket::ClientPixelsProxy>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.client_pixels.back() = *v;
        }
    }
    return out;
}

void Serializer<MapCreateLockedCopyPacket>::serialize(BinaryWriter &stream, const MapCreateLockedCopyPacket &value)
{
    stream.writeVarInt<std::int64_t>(value.original_map_id);
    stream.writeVarInt<std::int64_t>(value.new_map_id);
}

auto Serializer<MapCreateLockedCopyPacket>::deserialize(BinaryReader &stream) -> std::expected<MapCreateLockedCopyPacket, std::error_code>
{
    MapCreateLockedCopyPacket out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.original_map_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.new_map_id = static_cast<ActorUniqueID>(*v);
    }
    return out;
}

void Serializer<CreatePhotoPacket>::serialize(BinaryWriter &stream, const CreatePhotoPacket &value)
{
    stream.write<std::uint64_t>(value.id);
    stream.write(value.photo_name);
    stream.write(value.photo_item_name);
}

auto Serializer<CreatePhotoPacket>::deserialize(BinaryReader &stream) -> std::expected<CreatePhotoPacket, std::error_code>
{
    CreatePhotoPacket out;
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.photo_name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.photo_item_name = *v;
    }
    return out;
}

void Serializer<PhotoTransferPacket>::serialize(BinaryWriter &stream, const PhotoTransferPacket &value)
{
    stream.write(value.photo_name);
    stream.write(value.photo_data);
    stream.write(value.book_id);
    stream.write<std::uint8_t>(value.type);
    stream.write<std::uint8_t>(value.source_type);
    stream.write<std::int64_t>(value.owner_id);
    stream.write(value.new_photo_name);
}

auto Serializer<PhotoTransferPacket>::deserialize(BinaryReader &stream) -> std::expected<PhotoTransferPacket, std::error_code>
{
    PhotoTransferPacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.photo_name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.photo_data = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.book_id = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<PhotoType>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.source_type = static_cast<PhotoType>(*v);
    }
    {
        auto v = stream.read<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.owner_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.new_photo_name = *v;
    }
    return out;
}

void Serializer<v786::PlayerVideoCapturePacket::StartVideoCapture>::serialize(BinaryWriter &stream, const v786::PlayerVideoCapturePacket::StartVideoCapture &value)
{
    stream.write<std::uint32_t>(value.frame_rate);
    stream.write(value.file_prefix);
}

auto Serializer<v786::PlayerVideoCapturePacket::StartVideoCapture>::deserialize(BinaryReader &stream) -> std::expected<v786::PlayerVideoCapturePacket::StartVideoCapture, std::error_code>
{
    v786::PlayerVideoCapturePacket::StartVideoCapture out;
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.frame_rate = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.file_prefix = *v;
    }
    return out;
}

void Serializer<v786::PlayerVideoCapturePacket::StopVideoCapture>::serialize(BinaryWriter &stream, const v786::PlayerVideoCapturePacket::StopVideoCapture &value)
{
}

auto Serializer<v786::PlayerVideoCapturePacket::StopVideoCapture>::deserialize(BinaryReader &stream) -> std::expected<v786::PlayerVideoCapturePacket::StopVideoCapture, std::error_code>
{
    v786::PlayerVideoCapturePacket::StopVideoCapture out;
    return out;
}

void Serializer<v786::PlayerVideoCapturePacket>::serialize(BinaryWriter &stream, const v786::PlayerVideoCapturePacket &value)
{
    stream.writeVarInt<std::uint32_t>((value.start_video_capture).index());
    switch ((value.start_video_capture).index()) {
        case 0: {
            Serializer<v786::PlayerVideoCapturePacket::StartVideoCapture>::serialize(stream, std::get<0>(value.start_video_capture));
            break;
        }
        case 1: {
            Serializer<v786::PlayerVideoCapturePacket::StopVideoCapture>::serialize(stream, std::get<1>(value.start_video_capture));
            break;
        }
    }
    stream.writeVarInt<std::uint32_t>((value.stop_video_capture).index());
    switch ((value.stop_video_capture).index()) {
        case 0: {
            Serializer<v786::PlayerVideoCapturePacket::StartVideoCapture>::serialize(stream, std::get<0>(value.stop_video_capture));
            break;
        }
        case 1: {
            Serializer<v786::PlayerVideoCapturePacket::StopVideoCapture>::serialize(stream, std::get<1>(value.stop_video_capture));
            break;
        }
    }
}

auto Serializer<v786::PlayerVideoCapturePacket>::deserialize(BinaryReader &stream) -> std::expected<v786::PlayerVideoCapturePacket, std::error_code>
{
    v786::PlayerVideoCapturePacket out;
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v786::PlayerVideoCapturePacket::StartVideoCapture, v786::PlayerVideoCapturePacket::StopVideoCapture> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v786::PlayerVideoCapturePacket::StartVideoCapture, v786::PlayerVideoCapturePacket::StopVideoCapture>> alt0{};
                {
                    auto v = Serializer<v786::PlayerVideoCapturePacket::StartVideoCapture>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v786::PlayerVideoCapturePacket::StartVideoCapture, v786::PlayerVideoCapturePacket::StopVideoCapture>> alt0{};
                {
                    auto v = Serializer<v786::PlayerVideoCapturePacket::StopVideoCapture>::deserialize(stream);
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
        out.start_video_capture = var0;
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v786::PlayerVideoCapturePacket::StartVideoCapture, v786::PlayerVideoCapturePacket::StopVideoCapture> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v786::PlayerVideoCapturePacket::StartVideoCapture, v786::PlayerVideoCapturePacket::StopVideoCapture>> alt0{};
                {
                    auto v = Serializer<v786::PlayerVideoCapturePacket::StartVideoCapture>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v786::PlayerVideoCapturePacket::StartVideoCapture, v786::PlayerVideoCapturePacket::StopVideoCapture>> alt0{};
                {
                    auto v = Serializer<v786::PlayerVideoCapturePacket::StopVideoCapture>::deserialize(stream);
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
        out.stop_video_capture = var0;
    }
    return out;
}

}  // namespace bedrock::protocol
