#include "crosslink/api/proto/packets/ChunkPackets.hpp"

#include "proto/SculkBridge.hpp"

#include <sculk/protocol/codec/packet/LevelChunkPacket.hpp>
#include <sculk/protocol/codec/packet/SubChunkPacket.hpp>
#include <sculk/protocol/codec/packet/SubChunkRequestPacket.hpp>

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
    mDimension = packet->mDimensionId;
    mSubChunkCount = packet->mSubChunksCount;
    mCacheEnabled = packet->mCacheBlobs.has_value();
    mClientNeedsToRequestSubChunks = packet->mClientNeedsToRequestSubchunks;
    return {};
}

// ---- SubChunk ----------------------------------------------------------

std::int32_t SubChunkPacket::dimension() const { return mDimension; }

bool SubChunkPacket::cacheEnabled() const { return mCacheEnabled; }

std::size_t SubChunkPacket::entryCount() const { return mEntryCount; }

Result<> SubChunkPacket::decodeImpl() {
    auto packet = bridge::decode<bp::SubChunkPacket>(payload());
    if (!packet) return std::unexpected(packet.error());
    mDimension = packet->mDimensionType;
    mCacheEnabled = packet->mCacheEnabled;
    mEntryCount = packet->mSubChunkData.size();
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
    mDimension = packet->mDimensionType;
    return {};
}

Result<> SubChunkRequestPacket::encodeImpl() {
    // Read-modify-write keeps the requested offsets intact.
    auto rewritten = bridge::modify<bp::SubChunkRequestPacket>(header(), payload(), [this](bp::SubChunkRequestPacket& packet) {
        packet.mDimensionType = mDimension;
    });
    if (!rewritten) return std::unexpected(rewritten.error());
    setSerialized(std::move(*rewritten), bridge::serializedHeaderSize(header()));
    return {};
}

} // namespace crosslink::proto
