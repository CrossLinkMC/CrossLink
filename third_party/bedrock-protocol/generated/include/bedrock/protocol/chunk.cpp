#include <bedrock/protocol/chunk.h>

namespace bedrock::protocol {


void Serializer<ChunkPos>::serialize(BinaryWriter &stream, const ChunkPos &value)
{
    stream.writeVarInt<std::int32_t>(value.x);
    stream.writeVarInt<std::int32_t>(value.z);
}

auto Serializer<ChunkPos>::deserialize(BinaryReader &stream) -> std::expected<ChunkPos, std::error_code>
{
    ChunkPos out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.x = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.z = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<base::LevelChunkPacket::SubChunkMetadata>::serialize(BinaryWriter &stream, const base::LevelChunkPacket::SubChunkMetadata &value)
{
    stream.write<std::uint64_t>(value.blob_id);
}

auto Serializer<base::LevelChunkPacket::SubChunkMetadata>::deserialize(BinaryReader &stream) -> std::expected<base::LevelChunkPacket::SubChunkMetadata, std::error_code>
{
    base::LevelChunkPacket::SubChunkMetadata out;
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.blob_id = static_cast<std::uint64_t>(*v);
    }
    return out;
}

void Serializer<base::LevelChunkPacket>::serialize(BinaryWriter &stream, const base::LevelChunkPacket &value)
{
    Serializer<ChunkPos>::serialize(stream, value.pos);
    stream.writeVarInt<std::int32_t>(value.dimension_id);
    stream.writeVarInt<std::uint32_t>(value.sub_chunks_count);
    if ((value.sub_chunks_count) == (4294967294)) {
        stream.write<std::uint16_t>(value.client_request_sub_chunk_limit);
    }
    stream.write<bool>(value.cache_enabled);
    if (value.cache_enabled) {
        stream.writeVarInt<std::uint32_t>(value.cache_metadata.size());
        for (const auto &e0 : value.cache_metadata) {
            Serializer<base::LevelChunkPacket::SubChunkMetadata>::serialize(stream, e0);
        }
    }
    stream.write(value.serialized_chunk);
}

auto Serializer<base::LevelChunkPacket>::deserialize(BinaryReader &stream) -> std::expected<base::LevelChunkPacket, std::error_code>
{
    base::LevelChunkPacket out;
    {
        auto v = Serializer<ChunkPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.dimension_id = static_cast<DimensionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.sub_chunks_count = static_cast<std::uint32_t>(*v);
    }
    if ((out.sub_chunks_count) == (4294967294)) {
        {
            auto v = stream.read<std::uint16_t>();
            if (!v) return std::unexpected(v.error());
            out.client_request_sub_chunk_limit = static_cast<std::uint16_t>(*v);
        }
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.cache_enabled = static_cast<bool>(*v);
    }
    if (out.cache_enabled) {
        {
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            out.cache_metadata.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                out.cache_metadata.emplace_back();
                auto v = Serializer<base::LevelChunkPacket::SubChunkMetadata>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                out.cache_metadata.back() = *v;
            }
        }
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.serialized_chunk = *v;
    }
    return out;
}

void Serializer<v2168::LevelChunkPacket>::serialize(BinaryWriter &stream, const v2168::LevelChunkPacket &value)
{
    Serializer<ChunkPos>::serialize(stream, value.pos);
    stream.writeVarInt<std::int32_t>(value.dimension_id);
    stream.writeVarInt<std::uint32_t>(value.sub_chunks_count);
    stream.write<bool>(value.client_request_sub_chunk_limit.has_value());
    if (value.client_request_sub_chunk_limit.has_value()) {
        stream.writeVarInt<std::int32_t>((*value.client_request_sub_chunk_limit));
    }
    stream.write<bool>(value.cache_enabled);
    stream.writeVarInt<std::uint32_t>(value.cache_metadata.size());
    for (const auto &e0 : value.cache_metadata) {
        Serializer<v2168::LevelChunkPacket::SubChunkMetadata>::serialize(stream, e0);
    }
    stream.write(value.serialized_chunk);
}

auto Serializer<v2168::LevelChunkPacket>::deserialize(BinaryReader &stream) -> std::expected<v2168::LevelChunkPacket, std::error_code>
{
    v2168::LevelChunkPacket out;
    {
        auto v = Serializer<ChunkPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.dimension_id = static_cast<DimensionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.sub_chunks_count = static_cast<std::uint32_t>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::int32_t staged{};
            auto v = stream.readVarInt<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<std::int32_t>(*v);
            out.client_request_sub_chunk_limit = std::move(staged);
        }
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.cache_enabled = static_cast<bool>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.cache_metadata.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.cache_metadata.emplace_back();
            auto v = Serializer<v2168::LevelChunkPacket::SubChunkMetadata>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.cache_metadata.back() = *v;
        }
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.serialized_chunk = *v;
    }
    return out;
}

void Serializer<v2225::LevelChunkPacket>::serialize(BinaryWriter &stream, const v2225::LevelChunkPacket &value)
{
    Serializer<ChunkPos>::serialize(stream, value.pos);
    stream.writeVarInt<std::int32_t>(value.dimension_id);
    stream.writeVarInt<std::uint32_t>(value.sub_chunks_count);
    stream.write<bool>(value.client_request_sub_chunk_limit.has_value());
    if (value.client_request_sub_chunk_limit.has_value()) {
        stream.writeVarInt<std::int32_t>((*value.client_request_sub_chunk_limit));
    }
    stream.write<bool>(value.cache_enabled);
    stream.writeVarInt<std::uint32_t>(value.cache_metadata.size());
    for (const auto &e0 : value.cache_metadata) {
        Serializer<v2225::LevelChunkPacket::SubChunkMetadata>::serialize(stream, e0);
    }
    stream.write(value.serialized_chunk);
    stream.write<bool>(value.is_client_biome_update);
}

auto Serializer<v2225::LevelChunkPacket>::deserialize(BinaryReader &stream) -> std::expected<v2225::LevelChunkPacket, std::error_code>
{
    v2225::LevelChunkPacket out;
    {
        auto v = Serializer<ChunkPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.dimension_id = static_cast<DimensionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.sub_chunks_count = static_cast<std::uint32_t>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::int32_t staged{};
            auto v = stream.readVarInt<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<std::int32_t>(*v);
            out.client_request_sub_chunk_limit = std::move(staged);
        }
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.cache_enabled = static_cast<bool>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.cache_metadata.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.cache_metadata.emplace_back();
            auto v = Serializer<v2225::LevelChunkPacket::SubChunkMetadata>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.cache_metadata.back() = *v;
        }
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.serialized_chunk = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_client_biome_update = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<base::SubChunkPos>::serialize(BinaryWriter &stream, const base::SubChunkPos &value)
{
    stream.writeVarInt<std::int32_t>(value.x);
    stream.writeVarInt<std::int32_t>(value.y);
    stream.writeVarInt<std::int32_t>(value.z);
}

auto Serializer<base::SubChunkPos>::deserialize(BinaryReader &stream) -> std::expected<base::SubChunkPos, std::error_code>
{
    base::SubChunkPos out;
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

void Serializer<v1001::SubChunkPos>::serialize(BinaryWriter &stream, const v1001::SubChunkPos &value)
{
    stream.write<std::int32_t>(value.x);
    stream.write<std::int32_t>(value.y);
    stream.write<std::int32_t>(value.z);
}

auto Serializer<v1001::SubChunkPos>::deserialize(BinaryReader &stream) -> std::expected<v1001::SubChunkPos, std::error_code>
{
    v1001::SubChunkPos out;
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.x = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.y = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.z = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<legacy::base::SubChunkPos>::serialize(BinaryWriter &stream, const legacy::base::SubChunkPos &value)
{
    stream.writeVarInt<std::int32_t>(value.x);
    stream.writeVarInt<std::int32_t>(value.y);
    stream.writeVarInt<std::int32_t>(value.z);
}

auto Serializer<legacy::base::SubChunkPos>::deserialize(BinaryReader &stream) -> std::expected<legacy::base::SubChunkPos, std::error_code>
{
    legacy::base::SubChunkPos out;
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

void Serializer<base::SubChunkPacket::HeightmapData>::serialize(BinaryWriter &stream, const base::SubChunkPacket::HeightmapData &value)
{
    stream.write<std::uint8_t>(value.height_map_type);
    if ((value.height_map_type) == (base::SubChunkPacket::HeightMapDataType::HasData)) {
        for (const auto &e0 : value.subchunk_height_map) {
            for (const auto &e1 : e0) {
                stream.write<std::int8_t>(e1);
            }
        }
    }
}

auto Serializer<base::SubChunkPacket::HeightmapData>::deserialize(BinaryReader &stream) -> std::expected<base::SubChunkPacket::HeightmapData, std::error_code>
{
    base::SubChunkPacket::HeightmapData out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.height_map_type = static_cast<base::SubChunkPacket::HeightMapDataType>(*v);
    }
    if ((out.height_map_type) == (base::SubChunkPacket::HeightMapDataType::HasData)) {
        {
            for (std::size_t i0 = 0; i0 < 16; ++i0) {
                for (std::size_t i1 = 0; i1 < 16; ++i1) {
                    auto v = stream.read<std::int8_t>();
                    if (!v) return std::unexpected(v.error());
                    out.subchunk_height_map[i0][i1] = static_cast<std::int8_t>(*v);
                }
            }
        }
    }
    return out;
}

void Serializer<base::SubChunkPacket::SubChunkPosOffset>::serialize(BinaryWriter &stream, const base::SubChunkPacket::SubChunkPosOffset &value)
{
    stream.write<std::int8_t>(value.x);
    stream.write<std::int8_t>(value.y);
    stream.write<std::int8_t>(value.z);
}

auto Serializer<base::SubChunkPacket::SubChunkPosOffset>::deserialize(BinaryReader &stream) -> std::expected<base::SubChunkPacket::SubChunkPosOffset, std::error_code>
{
    base::SubChunkPacket::SubChunkPosOffset out;
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
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.z = static_cast<std::int8_t>(*v);
    }
    return out;
}

void Serializer<base::SubChunkPacket::SubChunkPacketData>::serialize(BinaryWriter &stream, const base::SubChunkPacket::SubChunkPacketData &value)
{
    Serializer<base::SubChunkPacket::SubChunkPosOffset>::serialize(stream, value.sub_chunk_pos_offset);
    stream.write<std::uint8_t>(value.result);
    if ((value.result) != (base::SubChunkPacket::SubChunkRequestResult::SuccessAllAir)) {
        stream.write(value.serialized_sub_chunk);
    }
    Serializer<base::SubChunkPacket::HeightmapData>::serialize(stream, value.height_map_data);
    stream.write<std::uint64_t>(value.blob_id);
}

auto Serializer<base::SubChunkPacket::SubChunkPacketData>::deserialize(BinaryReader &stream) -> std::expected<base::SubChunkPacket::SubChunkPacketData, std::error_code>
{
    base::SubChunkPacket::SubChunkPacketData out;
    {
        auto v = Serializer<base::SubChunkPacket::SubChunkPosOffset>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.sub_chunk_pos_offset = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.result = static_cast<base::SubChunkPacket::SubChunkRequestResult>(*v);
    }
    if ((out.result) != (base::SubChunkPacket::SubChunkRequestResult::SuccessAllAir)) {
        {
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.serialized_sub_chunk = *v;
        }
    }
    {
        auto v = Serializer<base::SubChunkPacket::HeightmapData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.height_map_data = *v;
    }
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.blob_id = static_cast<std::uint64_t>(*v);
    }
    return out;
}

void Serializer<base::SubChunkPacket::UncachedSubChunkPacketData>::serialize(BinaryWriter &stream, const base::SubChunkPacket::UncachedSubChunkPacketData &value)
{
    Serializer<base::SubChunkPacket::SubChunkPosOffset>::serialize(stream, value.sub_chunk_pos_offset);
    stream.write<std::uint8_t>(value.result);
    stream.write(value.serialized_sub_chunk);
    Serializer<base::SubChunkPacket::HeightmapData>::serialize(stream, value.height_map_data);
}

auto Serializer<base::SubChunkPacket::UncachedSubChunkPacketData>::deserialize(BinaryReader &stream) -> std::expected<base::SubChunkPacket::UncachedSubChunkPacketData, std::error_code>
{
    base::SubChunkPacket::UncachedSubChunkPacketData out;
    {
        auto v = Serializer<base::SubChunkPacket::SubChunkPosOffset>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.sub_chunk_pos_offset = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.result = static_cast<base::SubChunkPacket::SubChunkRequestResult>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.serialized_sub_chunk = *v;
    }
    {
        auto v = Serializer<base::SubChunkPacket::HeightmapData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.height_map_data = *v;
    }
    return out;
}

void Serializer<v818::SubChunkPacket::HeightmapData>::serialize(BinaryWriter &stream, const v818::SubChunkPacket::HeightmapData &value)
{
    stream.write<std::uint8_t>(value.height_map_type);
    if ((value.height_map_type) == (v818::SubChunkPacket::HeightMapDataType::HasData)) {
        for (const auto &e0 : value.subchunk_height_map) {
            for (const auto &e1 : e0) {
                stream.write<std::int8_t>(e1);
            }
        }
    }
    stream.write<std::uint8_t>(value.render_height_map_type);
    if ((value.render_height_map_type) == (v818::SubChunkPacket::HeightMapDataType::HasData)) {
        for (const auto &e0 : value.subchunk_render_height_map) {
            for (const auto &e1 : e0) {
                stream.write<std::int8_t>(e1);
            }
        }
    }
}

auto Serializer<v818::SubChunkPacket::HeightmapData>::deserialize(BinaryReader &stream) -> std::expected<v818::SubChunkPacket::HeightmapData, std::error_code>
{
    v818::SubChunkPacket::HeightmapData out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.height_map_type = static_cast<v818::SubChunkPacket::HeightMapDataType>(*v);
    }
    if ((out.height_map_type) == (v818::SubChunkPacket::HeightMapDataType::HasData)) {
        {
            for (std::size_t i0 = 0; i0 < 16; ++i0) {
                for (std::size_t i1 = 0; i1 < 16; ++i1) {
                    auto v = stream.read<std::int8_t>();
                    if (!v) return std::unexpected(v.error());
                    out.subchunk_height_map[i0][i1] = static_cast<std::int8_t>(*v);
                }
            }
        }
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.render_height_map_type = static_cast<v818::SubChunkPacket::HeightMapDataType>(*v);
    }
    if ((out.render_height_map_type) == (v818::SubChunkPacket::HeightMapDataType::HasData)) {
        {
            for (std::size_t i0 = 0; i0 < 16; ++i0) {
                for (std::size_t i1 = 0; i1 < 16; ++i1) {
                    auto v = stream.read<std::int8_t>();
                    if (!v) return std::unexpected(v.error());
                    out.subchunk_render_height_map[i0][i1] = static_cast<std::int8_t>(*v);
                }
            }
        }
    }
    return out;
}

void Serializer<v818::SubChunkPacket::SubChunkPacketData>::serialize(BinaryWriter &stream, const v818::SubChunkPacket::SubChunkPacketData &value)
{
    Serializer<v818::SubChunkPacket::SubChunkPosOffset>::serialize(stream, value.sub_chunk_pos_offset);
    stream.write<std::uint8_t>(value.result);
    if ((value.result) != (v818::SubChunkPacket::SubChunkRequestResult::SuccessAllAir)) {
        stream.write(value.serialized_sub_chunk);
    }
    Serializer<v818::SubChunkPacket::HeightmapData>::serialize(stream, value.height_map_data);
    stream.write<std::uint64_t>(value.blob_id);
}

auto Serializer<v818::SubChunkPacket::SubChunkPacketData>::deserialize(BinaryReader &stream) -> std::expected<v818::SubChunkPacket::SubChunkPacketData, std::error_code>
{
    v818::SubChunkPacket::SubChunkPacketData out;
    {
        auto v = Serializer<v818::SubChunkPacket::SubChunkPosOffset>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.sub_chunk_pos_offset = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.result = static_cast<v818::SubChunkPacket::SubChunkRequestResult>(*v);
    }
    if ((out.result) != (v818::SubChunkPacket::SubChunkRequestResult::SuccessAllAir)) {
        {
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.serialized_sub_chunk = *v;
        }
    }
    {
        auto v = Serializer<v818::SubChunkPacket::HeightmapData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.height_map_data = *v;
    }
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.blob_id = static_cast<std::uint64_t>(*v);
    }
    return out;
}

void Serializer<v818::SubChunkPacket::UncachedSubChunkPacketData>::serialize(BinaryWriter &stream, const v818::SubChunkPacket::UncachedSubChunkPacketData &value)
{
    Serializer<v818::SubChunkPacket::SubChunkPosOffset>::serialize(stream, value.sub_chunk_pos_offset);
    stream.write<std::uint8_t>(value.result);
    stream.write(value.serialized_sub_chunk);
    Serializer<v818::SubChunkPacket::HeightmapData>::serialize(stream, value.height_map_data);
}

auto Serializer<v818::SubChunkPacket::UncachedSubChunkPacketData>::deserialize(BinaryReader &stream) -> std::expected<v818::SubChunkPacket::UncachedSubChunkPacketData, std::error_code>
{
    v818::SubChunkPacket::UncachedSubChunkPacketData out;
    {
        auto v = Serializer<v818::SubChunkPacket::SubChunkPosOffset>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.sub_chunk_pos_offset = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.result = static_cast<v818::SubChunkPacket::SubChunkRequestResult>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.serialized_sub_chunk = *v;
    }
    {
        auto v = Serializer<v818::SubChunkPacket::HeightmapData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.height_map_data = *v;
    }
    return out;
}

void Serializer<v1001::SubChunkPacket::HeightmapData>::serialize(BinaryWriter &stream, const v1001::SubChunkPacket::HeightmapData &value)
{
    stream.write<std::uint8_t>(value.height_map_type);
    if ((value.height_map_type) == (v1001::SubChunkPacket::HeightMapDataType::HasData)) {
        for (const auto &e0 : value.subchunk_height_map) {
            for (const auto &e1 : e0) {
                stream.write<std::int8_t>(e1);
            }
        }
    }
    stream.write<std::uint8_t>(value.render_height_map_type);
    if ((value.render_height_map_type) == (v1001::SubChunkPacket::HeightMapDataType::HasData)) {
        for (const auto &e0 : value.subchunk_render_height_map) {
            for (const auto &e1 : e0) {
                stream.write<std::int8_t>(e1);
            }
        }
    }
}

auto Serializer<v1001::SubChunkPacket::HeightmapData>::deserialize(BinaryReader &stream) -> std::expected<v1001::SubChunkPacket::HeightmapData, std::error_code>
{
    v1001::SubChunkPacket::HeightmapData out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.height_map_type = static_cast<v1001::SubChunkPacket::HeightMapDataType>(*v);
    }
    if ((out.height_map_type) == (v1001::SubChunkPacket::HeightMapDataType::HasData)) {
        {
            for (std::size_t i0 = 0; i0 < 16; ++i0) {
                for (std::size_t i1 = 0; i1 < 16; ++i1) {
                    auto v = stream.read<std::int8_t>();
                    if (!v) return std::unexpected(v.error());
                    out.subchunk_height_map[i0][i1] = static_cast<std::int8_t>(*v);
                }
            }
        }
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.render_height_map_type = static_cast<v1001::SubChunkPacket::HeightMapDataType>(*v);
    }
    if ((out.render_height_map_type) == (v1001::SubChunkPacket::HeightMapDataType::HasData)) {
        {
            for (std::size_t i0 = 0; i0 < 16; ++i0) {
                for (std::size_t i1 = 0; i1 < 16; ++i1) {
                    auto v = stream.read<std::int8_t>();
                    if (!v) return std::unexpected(v.error());
                    out.subchunk_render_height_map[i0][i1] = static_cast<std::int8_t>(*v);
                }
            }
        }
    }
    return out;
}

void Serializer<v1001::SubChunkPacket::SubChunkPacketData>::serialize(BinaryWriter &stream, const v1001::SubChunkPacket::SubChunkPacketData &value)
{
    Serializer<v1001::SubChunkPacket::SubChunkPosOffset>::serialize(stream, value.sub_chunk_pos_offset);
    stream.write<std::uint8_t>(value.result);
    if ((value.result) != (v1001::SubChunkPacket::SubChunkRequestResult::SuccessAllAir)) {
        stream.write(value.serialized_sub_chunk);
    }
    Serializer<v1001::SubChunkPacket::HeightmapData>::serialize(stream, value.height_map_data);
    stream.write<std::uint64_t>(value.blob_id);
}

auto Serializer<v1001::SubChunkPacket::SubChunkPacketData>::deserialize(BinaryReader &stream) -> std::expected<v1001::SubChunkPacket::SubChunkPacketData, std::error_code>
{
    v1001::SubChunkPacket::SubChunkPacketData out;
    {
        auto v = Serializer<v1001::SubChunkPacket::SubChunkPosOffset>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.sub_chunk_pos_offset = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.result = static_cast<v1001::SubChunkPacket::SubChunkRequestResult>(*v);
    }
    if ((out.result) != (v1001::SubChunkPacket::SubChunkRequestResult::SuccessAllAir)) {
        {
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.serialized_sub_chunk = *v;
        }
    }
    {
        auto v = Serializer<v1001::SubChunkPacket::HeightmapData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.height_map_data = *v;
    }
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.blob_id = static_cast<std::uint64_t>(*v);
    }
    return out;
}

void Serializer<v1001::SubChunkPacket::UncachedSubChunkPacketData>::serialize(BinaryWriter &stream, const v1001::SubChunkPacket::UncachedSubChunkPacketData &value)
{
    Serializer<v1001::SubChunkPacket::SubChunkPosOffset>::serialize(stream, value.sub_chunk_pos_offset);
    stream.write<std::uint8_t>(value.result);
    stream.write(value.serialized_sub_chunk);
    Serializer<v1001::SubChunkPacket::HeightmapData>::serialize(stream, value.height_map_data);
}

auto Serializer<v1001::SubChunkPacket::UncachedSubChunkPacketData>::deserialize(BinaryReader &stream) -> std::expected<v1001::SubChunkPacket::UncachedSubChunkPacketData, std::error_code>
{
    v1001::SubChunkPacket::UncachedSubChunkPacketData out;
    {
        auto v = Serializer<v1001::SubChunkPacket::SubChunkPosOffset>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.sub_chunk_pos_offset = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.result = static_cast<v1001::SubChunkPacket::SubChunkRequestResult>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.serialized_sub_chunk = *v;
    }
    {
        auto v = Serializer<v1001::SubChunkPacket::HeightmapData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.height_map_data = *v;
    }
    return out;
}

void Serializer<v2168::SubChunkPacket::HeightmapData>::serialize(BinaryWriter &stream, const v2168::SubChunkPacket::HeightmapData &value)
{
    stream.write<std::uint8_t>(value.height_map_type);
    stream.write<bool>(value.subchunk_height_map.has_value());
    if (value.subchunk_height_map.has_value()) {
        for (const auto &e0 : (*value.subchunk_height_map)) {
            for (const auto &e1 : e0) {
                stream.write<std::int8_t>(e1);
            }
        }
    }
    stream.write<std::uint8_t>(value.render_height_map_type);
    stream.write<bool>(value.subchunk_render_height_map.has_value());
    if (value.subchunk_render_height_map.has_value()) {
        for (const auto &e0 : (*value.subchunk_render_height_map)) {
            for (const auto &e1 : e0) {
                stream.write<std::int8_t>(e1);
            }
        }
    }
}

auto Serializer<v2168::SubChunkPacket::HeightmapData>::deserialize(BinaryReader &stream) -> std::expected<v2168::SubChunkPacket::HeightmapData, std::error_code>
{
    v2168::SubChunkPacket::HeightmapData out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.height_map_type = static_cast<v2168::SubChunkPacket::HeightMapDataType>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::array<std::array<std::int8_t, 16>, 16> staged{};
            for (std::size_t i0 = 0; i0 < 16; ++i0) {
                for (std::size_t i1 = 0; i1 < 16; ++i1) {
                    auto v = stream.read<std::int8_t>();
                    if (!v) return std::unexpected(v.error());
                    staged[i0][i1] = static_cast<std::int8_t>(*v);
                }
            }
            out.subchunk_height_map = std::move(staged);
        }
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.render_height_map_type = static_cast<v2168::SubChunkPacket::HeightMapDataType>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::array<std::array<std::int8_t, 16>, 16> staged{};
            for (std::size_t i0 = 0; i0 < 16; ++i0) {
                for (std::size_t i1 = 0; i1 < 16; ++i1) {
                    auto v = stream.read<std::int8_t>();
                    if (!v) return std::unexpected(v.error());
                    staged[i0][i1] = static_cast<std::int8_t>(*v);
                }
            }
            out.subchunk_render_height_map = std::move(staged);
        }
    }
    return out;
}

void Serializer<v2168::SubChunkPacket::SubChunkPacketData>::serialize(BinaryWriter &stream, const v2168::SubChunkPacket::SubChunkPacketData &value)
{
    Serializer<v2168::SubChunkPacket::SubChunkPosOffset>::serialize(stream, value.sub_chunk_pos_offset);
    stream.write<std::uint8_t>(value.result);
    stream.write<bool>(value.serialized_sub_chunk.has_value());
    if (value.serialized_sub_chunk.has_value()) {
        stream.write((*value.serialized_sub_chunk));
    }
    Serializer<v2168::SubChunkPacket::HeightmapData>::serialize(stream, value.height_map_data);
    stream.write<bool>(value.blob_id.has_value());
    if (value.blob_id.has_value()) {
        stream.write<std::uint64_t>((*value.blob_id));
    }
}

auto Serializer<v2168::SubChunkPacket::SubChunkPacketData>::deserialize(BinaryReader &stream) -> std::expected<v2168::SubChunkPacket::SubChunkPacketData, std::error_code>
{
    v2168::SubChunkPacket::SubChunkPacketData out;
    {
        auto v = Serializer<v2168::SubChunkPacket::SubChunkPosOffset>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.sub_chunk_pos_offset = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.result = static_cast<v2168::SubChunkPacket::SubChunkRequestResult>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::string staged{};
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.serialized_sub_chunk = std::move(staged);
        }
    }
    {
        auto v = Serializer<v2168::SubChunkPacket::HeightmapData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.height_map_data = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::uint64_t staged{};
            auto v = stream.read<std::uint64_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<std::uint64_t>(*v);
            out.blob_id = std::move(staged);
        }
    }
    return out;
}

void Serializer<v2193::SubChunkPacket::HeightmapData>::serialize(BinaryWriter &stream, const v2193::SubChunkPacket::HeightmapData &value)
{
    stream.write<std::uint8_t>(value.height_map_type);
    stream.write<bool>(value.subchunk_height_map.has_value());
    if (value.subchunk_height_map.has_value()) {
        for (const auto &e0 : (*value.subchunk_height_map)) {
            stream.writeVarInt<std::uint32_t>(e0.size());
            for (const auto &e1 : e0) {
                stream.write<std::int8_t>(e1);
            }
        }
    }
    stream.write<std::uint8_t>(value.render_height_map_type);
    stream.write<bool>(value.subchunk_render_height_map.has_value());
    if (value.subchunk_render_height_map.has_value()) {
        for (const auto &e0 : (*value.subchunk_render_height_map)) {
            stream.writeVarInt<std::uint32_t>(e0.size());
            for (const auto &e1 : e0) {
                stream.write<std::int8_t>(e1);
            }
        }
    }
}

auto Serializer<v2193::SubChunkPacket::HeightmapData>::deserialize(BinaryReader &stream) -> std::expected<v2193::SubChunkPacket::HeightmapData, std::error_code>
{
    v2193::SubChunkPacket::HeightmapData out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.height_map_type = static_cast<v2193::SubChunkPacket::HeightMapDataType>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::array<std::vector<std::int8_t>, 16> staged{};
            for (std::size_t i0 = 0; i0 < 16; ++i0) {
                auto len1 = stream.readVarInt<std::uint32_t>();
                if (!len1) return std::unexpected(len1.error());
                staged[i0].clear();
                for (auto rep1 = *len1; rep1 > 0; --rep1) {
                    staged[i0].emplace_back();
                    auto v = stream.read<std::int8_t>();
                    if (!v) return std::unexpected(v.error());
                    staged[i0].back() = static_cast<std::int8_t>(*v);
                }
            }
            out.subchunk_height_map = std::move(staged);
        }
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.render_height_map_type = static_cast<v2193::SubChunkPacket::HeightMapDataType>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::array<std::vector<std::int8_t>, 16> staged{};
            for (std::size_t i0 = 0; i0 < 16; ++i0) {
                auto len1 = stream.readVarInt<std::uint32_t>();
                if (!len1) return std::unexpected(len1.error());
                staged[i0].clear();
                for (auto rep1 = *len1; rep1 > 0; --rep1) {
                    staged[i0].emplace_back();
                    auto v = stream.read<std::int8_t>();
                    if (!v) return std::unexpected(v.error());
                    staged[i0].back() = static_cast<std::int8_t>(*v);
                }
            }
            out.subchunk_render_height_map = std::move(staged);
        }
    }
    return out;
}

void Serializer<v2193::SubChunkPacket::SubChunkPacketData>::serialize(BinaryWriter &stream, const v2193::SubChunkPacket::SubChunkPacketData &value)
{
    Serializer<v2193::SubChunkPacket::SubChunkPosOffset>::serialize(stream, value.sub_chunk_pos_offset);
    stream.write<std::uint8_t>(value.result);
    stream.write<bool>(value.serialized_sub_chunk.has_value());
    if (value.serialized_sub_chunk.has_value()) {
        stream.write((*value.serialized_sub_chunk));
    }
    Serializer<v2193::SubChunkPacket::HeightmapData>::serialize(stream, value.height_map_data);
    stream.write<bool>(value.blob_id.has_value());
    if (value.blob_id.has_value()) {
        stream.write<std::uint64_t>((*value.blob_id));
    }
}

auto Serializer<v2193::SubChunkPacket::SubChunkPacketData>::deserialize(BinaryReader &stream) -> std::expected<v2193::SubChunkPacket::SubChunkPacketData, std::error_code>
{
    v2193::SubChunkPacket::SubChunkPacketData out;
    {
        auto v = Serializer<v2193::SubChunkPacket::SubChunkPosOffset>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.sub_chunk_pos_offset = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.result = static_cast<v2193::SubChunkPacket::SubChunkRequestResult>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::string staged{};
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.serialized_sub_chunk = std::move(staged);
        }
    }
    {
        auto v = Serializer<v2193::SubChunkPacket::HeightmapData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.height_map_data = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::uint64_t staged{};
            auto v = stream.read<std::uint64_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<std::uint64_t>(*v);
            out.blob_id = std::move(staged);
        }
    }
    return out;
}

void Serializer<base::SubChunkPacket>::serialize(BinaryWriter &stream, const base::SubChunkPacket &value)
{
    stream.write<bool>(value.cache_enabled);
    stream.writeVarInt<std::int32_t>(value.dimension_type);
    Serializer<legacy::base::SubChunkPos>::serialize(stream, value.center_pos);
    if (value.cache_enabled) {
        stream.write<std::uint32_t>(value.sub_chunk_data.size());
        for (const auto &e0 : value.sub_chunk_data) {
            Serializer<base::SubChunkPacket::SubChunkPacketData>::serialize(stream, e0);
        }
    }
    if (!(value.cache_enabled)) {
        stream.write<std::uint32_t>(value.uncached_sub_chunk_data.size());
        for (const auto &e0 : value.uncached_sub_chunk_data) {
            Serializer<base::SubChunkPacket::UncachedSubChunkPacketData>::serialize(stream, e0);
        }
    }
}

auto Serializer<base::SubChunkPacket>::deserialize(BinaryReader &stream) -> std::expected<base::SubChunkPacket, std::error_code>
{
    base::SubChunkPacket out;
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.cache_enabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.dimension_type = static_cast<DimensionType>(*v);
    }
    {
        auto v = Serializer<legacy::base::SubChunkPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.center_pos = *v;
    }
    if (out.cache_enabled) {
        {
            auto len0 = stream.read<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            out.sub_chunk_data.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                out.sub_chunk_data.emplace_back();
                auto v = Serializer<base::SubChunkPacket::SubChunkPacketData>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                out.sub_chunk_data.back() = *v;
            }
        }
    }
    if (!(out.cache_enabled)) {
        {
            auto len0 = stream.read<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            out.uncached_sub_chunk_data.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                out.uncached_sub_chunk_data.emplace_back();
                auto v = Serializer<base::SubChunkPacket::UncachedSubChunkPacketData>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                out.uncached_sub_chunk_data.back() = *v;
            }
        }
    }
    return out;
}

void Serializer<v818::SubChunkPacket>::serialize(BinaryWriter &stream, const v818::SubChunkPacket &value)
{
    stream.write<bool>(value.cache_enabled);
    stream.writeVarInt<std::int32_t>(value.dimension_type);
    Serializer<legacy::base::SubChunkPos>::serialize(stream, value.center_pos);
    if (value.cache_enabled) {
        stream.write<std::uint32_t>(value.sub_chunk_data.size());
        for (const auto &e0 : value.sub_chunk_data) {
            Serializer<v818::SubChunkPacket::SubChunkPacketData>::serialize(stream, e0);
        }
    }
    if (!(value.cache_enabled)) {
        stream.write<std::uint32_t>(value.uncached_sub_chunk_data.size());
        for (const auto &e0 : value.uncached_sub_chunk_data) {
            Serializer<v818::SubChunkPacket::UncachedSubChunkPacketData>::serialize(stream, e0);
        }
    }
}

auto Serializer<v818::SubChunkPacket>::deserialize(BinaryReader &stream) -> std::expected<v818::SubChunkPacket, std::error_code>
{
    v818::SubChunkPacket out;
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.cache_enabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.dimension_type = static_cast<DimensionType>(*v);
    }
    {
        auto v = Serializer<legacy::base::SubChunkPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.center_pos = *v;
    }
    if (out.cache_enabled) {
        {
            auto len0 = stream.read<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            out.sub_chunk_data.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                out.sub_chunk_data.emplace_back();
                auto v = Serializer<v818::SubChunkPacket::SubChunkPacketData>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                out.sub_chunk_data.back() = *v;
            }
        }
    }
    if (!(out.cache_enabled)) {
        {
            auto len0 = stream.read<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            out.uncached_sub_chunk_data.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                out.uncached_sub_chunk_data.emplace_back();
                auto v = Serializer<v818::SubChunkPacket::UncachedSubChunkPacketData>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                out.uncached_sub_chunk_data.back() = *v;
            }
        }
    }
    return out;
}

void Serializer<v1001::SubChunkPacket>::serialize(BinaryWriter &stream, const v1001::SubChunkPacket &value)
{
    stream.write<bool>(value.cache_enabled);
    stream.writeVarInt<std::int32_t>(value.dimension_type);
    Serializer<legacy::base::SubChunkPos>::serialize(stream, value.center_pos);
    if (value.cache_enabled) {
        stream.write<std::uint32_t>(value.sub_chunk_data.size());
        for (const auto &e0 : value.sub_chunk_data) {
            Serializer<v1001::SubChunkPacket::SubChunkPacketData>::serialize(stream, e0);
        }
    }
    if (!(value.cache_enabled)) {
        stream.write<std::uint32_t>(value.uncached_sub_chunk_data.size());
        for (const auto &e0 : value.uncached_sub_chunk_data) {
            Serializer<v1001::SubChunkPacket::UncachedSubChunkPacketData>::serialize(stream, e0);
        }
    }
}

auto Serializer<v1001::SubChunkPacket>::deserialize(BinaryReader &stream) -> std::expected<v1001::SubChunkPacket, std::error_code>
{
    v1001::SubChunkPacket out;
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.cache_enabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.dimension_type = static_cast<DimensionType>(*v);
    }
    {
        auto v = Serializer<legacy::base::SubChunkPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.center_pos = *v;
    }
    if (out.cache_enabled) {
        {
            auto len0 = stream.read<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            out.sub_chunk_data.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                out.sub_chunk_data.emplace_back();
                auto v = Serializer<v1001::SubChunkPacket::SubChunkPacketData>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                out.sub_chunk_data.back() = *v;
            }
        }
    }
    if (!(out.cache_enabled)) {
        {
            auto len0 = stream.read<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            out.uncached_sub_chunk_data.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                out.uncached_sub_chunk_data.emplace_back();
                auto v = Serializer<v1001::SubChunkPacket::UncachedSubChunkPacketData>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                out.uncached_sub_chunk_data.back() = *v;
            }
        }
    }
    return out;
}

void Serializer<v2168::SubChunkPacket>::serialize(BinaryWriter &stream, const v2168::SubChunkPacket &value)
{
    stream.write<bool>(value.cache_enabled);
    stream.writeVarInt<std::int32_t>(value.dimension_type);
    Serializer<v1001::SubChunkPos>::serialize(stream, value.center_pos);
    stream.writeVarInt<std::uint32_t>(value.sub_chunk_data.size());
    for (const auto &e0 : value.sub_chunk_data) {
        Serializer<v2168::SubChunkPacket::SubChunkPacketData>::serialize(stream, e0);
    }
}

auto Serializer<v2168::SubChunkPacket>::deserialize(BinaryReader &stream) -> std::expected<v2168::SubChunkPacket, std::error_code>
{
    v2168::SubChunkPacket out;
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.cache_enabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.dimension_type = static_cast<DimensionType>(*v);
    }
    {
        auto v = Serializer<v1001::SubChunkPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.center_pos = *v;
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.sub_chunk_data.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.sub_chunk_data.emplace_back();
            auto v = Serializer<v2168::SubChunkPacket::SubChunkPacketData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.sub_chunk_data.back() = *v;
        }
    }
    return out;
}

void Serializer<v2193::SubChunkPacket>::serialize(BinaryWriter &stream, const v2193::SubChunkPacket &value)
{
    stream.write<bool>(value.cache_enabled);
    stream.writeVarInt<std::int32_t>(value.dimension_type);
    Serializer<v1001::SubChunkPos>::serialize(stream, value.center_pos);
    stream.writeVarInt<std::uint32_t>(value.sub_chunk_data.size());
    for (const auto &e0 : value.sub_chunk_data) {
        Serializer<v2193::SubChunkPacket::SubChunkPacketData>::serialize(stream, e0);
    }
}

auto Serializer<v2193::SubChunkPacket>::deserialize(BinaryReader &stream) -> std::expected<v2193::SubChunkPacket, std::error_code>
{
    v2193::SubChunkPacket out;
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.cache_enabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.dimension_type = static_cast<DimensionType>(*v);
    }
    {
        auto v = Serializer<v1001::SubChunkPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.center_pos = *v;
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.sub_chunk_data.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.sub_chunk_data.emplace_back();
            auto v = Serializer<v2193::SubChunkPacket::SubChunkPacketData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.sub_chunk_data.back() = *v;
        }
    }
    return out;
}

void Serializer<base::SubChunkRequestPacket>::serialize(BinaryWriter &stream, const base::SubChunkRequestPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.dimension_type);
    Serializer<base::SubChunkPos>::serialize(stream, value.center_pos);
    stream.write<std::uint32_t>(value.sub_chunk_pos_offsets.size());
    for (const auto &e0 : value.sub_chunk_pos_offsets) {
        Serializer<base::SubChunkPacket::SubChunkPosOffset>::serialize(stream, e0);
    }
}

auto Serializer<base::SubChunkRequestPacket>::deserialize(BinaryReader &stream) -> std::expected<base::SubChunkRequestPacket, std::error_code>
{
    base::SubChunkRequestPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.dimension_type = static_cast<DimensionType>(*v);
    }
    {
        auto v = Serializer<base::SubChunkPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.center_pos = *v;
    }
    {
        auto len0 = stream.read<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.sub_chunk_pos_offsets.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.sub_chunk_pos_offsets.emplace_back();
            auto v = Serializer<base::SubChunkPacket::SubChunkPosOffset>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.sub_chunk_pos_offsets.back() = *v;
        }
    }
    return out;
}

void Serializer<v818::SubChunkRequestPacket>::serialize(BinaryWriter &stream, const v818::SubChunkRequestPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.dimension_type);
    Serializer<base::SubChunkPos>::serialize(stream, value.center_pos);
    stream.write<std::uint32_t>(value.sub_chunk_pos_offsets.size());
    for (const auto &e0 : value.sub_chunk_pos_offsets) {
        Serializer<v818::SubChunkPacket::SubChunkPosOffset>::serialize(stream, e0);
    }
}

auto Serializer<v818::SubChunkRequestPacket>::deserialize(BinaryReader &stream) -> std::expected<v818::SubChunkRequestPacket, std::error_code>
{
    v818::SubChunkRequestPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.dimension_type = static_cast<DimensionType>(*v);
    }
    {
        auto v = Serializer<base::SubChunkPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.center_pos = *v;
    }
    {
        auto len0 = stream.read<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.sub_chunk_pos_offsets.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.sub_chunk_pos_offsets.emplace_back();
            auto v = Serializer<v818::SubChunkPacket::SubChunkPosOffset>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.sub_chunk_pos_offsets.back() = *v;
        }
    }
    return out;
}

void Serializer<v1001::SubChunkRequestPacket>::serialize(BinaryWriter &stream, const v1001::SubChunkRequestPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.dimension_type);
    stream.writeVarInt<std::uint32_t>(value.sub_chunk_pos_offsets.size());
    for (const auto &e0 : value.sub_chunk_pos_offsets) {
        Serializer<v1001::SubChunkPacket::SubChunkPosOffset>::serialize(stream, e0);
    }
    Serializer<v1001::SubChunkPos>::serialize(stream, value.center_pos);
}

auto Serializer<v1001::SubChunkRequestPacket>::deserialize(BinaryReader &stream) -> std::expected<v1001::SubChunkRequestPacket, std::error_code>
{
    v1001::SubChunkRequestPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.dimension_type = static_cast<DimensionType>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.sub_chunk_pos_offsets.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.sub_chunk_pos_offsets.emplace_back();
            auto v = Serializer<v1001::SubChunkPacket::SubChunkPosOffset>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.sub_chunk_pos_offsets.back() = *v;
        }
    }
    {
        auto v = Serializer<v1001::SubChunkPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.center_pos = *v;
    }
    return out;
}

void Serializer<v2168::SubChunkRequestPacket>::serialize(BinaryWriter &stream, const v2168::SubChunkRequestPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.dimension_type);
    stream.writeVarInt<std::uint32_t>(value.sub_chunk_pos_offsets.size());
    for (const auto &e0 : value.sub_chunk_pos_offsets) {
        Serializer<v2168::SubChunkPacket::SubChunkPosOffset>::serialize(stream, e0);
    }
    Serializer<v1001::SubChunkPos>::serialize(stream, value.center_pos);
}

auto Serializer<v2168::SubChunkRequestPacket>::deserialize(BinaryReader &stream) -> std::expected<v2168::SubChunkRequestPacket, std::error_code>
{
    v2168::SubChunkRequestPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.dimension_type = static_cast<DimensionType>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.sub_chunk_pos_offsets.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.sub_chunk_pos_offsets.emplace_back();
            auto v = Serializer<v2168::SubChunkPacket::SubChunkPosOffset>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.sub_chunk_pos_offsets.back() = *v;
        }
    }
    {
        auto v = Serializer<v1001::SubChunkPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.center_pos = *v;
    }
    return out;
}

void Serializer<v2193::SubChunkRequestPacket>::serialize(BinaryWriter &stream, const v2193::SubChunkRequestPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.dimension_type);
    stream.writeVarInt<std::uint32_t>(value.sub_chunk_pos_offsets.size());
    for (const auto &e0 : value.sub_chunk_pos_offsets) {
        Serializer<v2193::SubChunkPacket::SubChunkPosOffset>::serialize(stream, e0);
    }
    Serializer<v1001::SubChunkPos>::serialize(stream, value.center_pos);
}

auto Serializer<v2193::SubChunkRequestPacket>::deserialize(BinaryReader &stream) -> std::expected<v2193::SubChunkRequestPacket, std::error_code>
{
    v2193::SubChunkRequestPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.dimension_type = static_cast<DimensionType>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.sub_chunk_pos_offsets.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.sub_chunk_pos_offsets.emplace_back();
            auto v = Serializer<v2193::SubChunkPacket::SubChunkPosOffset>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.sub_chunk_pos_offsets.back() = *v;
        }
    }
    {
        auto v = Serializer<v1001::SubChunkPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.center_pos = *v;
    }
    return out;
}

void Serializer<RequestChunkRadiusPacket>::serialize(BinaryWriter &stream, const RequestChunkRadiusPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.chunk_radius);
    stream.write<std::uint8_t>(value.max_chunk_radius);
}

auto Serializer<RequestChunkRadiusPacket>::deserialize(BinaryReader &stream) -> std::expected<RequestChunkRadiusPacket, std::error_code>
{
    RequestChunkRadiusPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.chunk_radius = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.max_chunk_radius = static_cast<std::uint8_t>(*v);
    }
    return out;
}

void Serializer<ChunkRadiusUpdatedPacket>::serialize(BinaryWriter &stream, const ChunkRadiusUpdatedPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.chunk_radius);
}

auto Serializer<ChunkRadiusUpdatedPacket>::deserialize(BinaryReader &stream) -> std::expected<ChunkRadiusUpdatedPacket, std::error_code>
{
    ChunkRadiusUpdatedPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.chunk_radius = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<NetworkChunkPublisherUpdatePacket>::serialize(BinaryWriter &stream, const NetworkChunkPublisherUpdatePacket &value)
{
    Serializer<BlockPos>::serialize(stream, value.position);
    stream.writeVarInt<std::uint32_t>(value.radius);
    stream.write<std::uint32_t>(value.server_built_chunks.size());
    for (const auto &e0 : value.server_built_chunks) {
        Serializer<ChunkPos>::serialize(stream, e0);
    }
}

auto Serializer<NetworkChunkPublisherUpdatePacket>::deserialize(BinaryReader &stream) -> std::expected<NetworkChunkPublisherUpdatePacket, std::error_code>
{
    NetworkChunkPublisherUpdatePacket out;
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.position = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.radius = static_cast<std::uint32_t>(*v);
    }
    {
        auto len0 = stream.read<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.server_built_chunks.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.server_built_chunks.emplace_back();
            auto v = Serializer<ChunkPos>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.server_built_chunks.back() = *v;
        }
    }
    return out;
}

}  // namespace bedrock::protocol
