#include "crosslink/api/proto/packets/ChunkPackets.hpp"

#include "proto/EndstoneBridge.hpp"

namespace crosslink::proto {
namespace {

namespace bp = bridge::bp;

} // namespace

// ---- LevelChunk --------------------------------------------------------

std::int32_t LevelChunkPacket::dimension() const { return mDimension; }

std::uint32_t LevelChunkPacket::subChunkCount() const { return mSubChunkCount; }

bool LevelChunkPacket::cacheEnabled() const { return mCacheEnabled; }

bool LevelChunkPacket::clientNeedsToRequestSubChunks() const { return mClientNeedsToRequestSubChunks; }

Result<> LevelChunkPacket::decodeImpl() {
    auto packet = bridge::decode<bp::LevelChunkPacket>(payload());
    if (!packet) return std::unexpected(packet.error());
    mDimension = packet->dimension_id;
    mSubChunkCount = packet->sub_chunks_count;
    mCacheEnabled = packet->cache_enabled;
    // The limit travels behind a presence flag; without it the client has to
    // fetch the remaining sub chunks with SubChunkRequestPacket.
    mClientNeedsToRequestSubChunks = !packet->client_request_sub_chunk_limit.has_value();
    return {};
}

// ---- SubChunk ----------------------------------------------------------

std::int32_t SubChunkPacket::dimension() const { return mDimension; }

bool SubChunkPacket::cacheEnabled() const { return mCacheEnabled; }

std::size_t SubChunkPacket::entryCount() const { return mEntryCount; }

Result<> SubChunkPacket::decodeImpl() {
    auto packet = bridge::decode<bp::SubChunkPacket>(payload());
    if (!packet) return std::unexpected(packet.error());
    mDimension = packet->dimension_type;
    mCacheEnabled = packet->cache_enabled;
    mEntryCount = packet->sub_chunk_data.size();
    return {};
}

// ---- SubChunkRequest ---------------------------------------------------

std::int32_t SubChunkRequestPacket::dimension() const { return mDimension; }

void SubChunkRequestPacket::setDimension(std::int32_t dimension) {
    mDimension = dimension;
    markDirty();
}

Result<> SubChunkRequestPacket::decodeImpl() {
    auto packet = bridge::decode<bp::SubChunkRequestPacket>(payload());
    if (!packet) return std::unexpected(packet.error());
    mDimension = packet->dimension_type;
    return {};
}

Result<> SubChunkRequestPacket::encodeImpl() {
    // Read-modify-write keeps the requested offsets intact.
    auto rewritten = bridge::modify<bp::SubChunkRequestPacket>(header(), payload(), [this](bp::SubChunkRequestPacket& packet) {
        packet.dimension_type = bp::DimensionType{mDimension};
    });
    if (!rewritten) return std::unexpected(rewritten.error());
    setSerialized(std::move(*rewritten), bridge::serializedHeaderSize(header()));
    return {};
}

} // namespace crosslink::proto
