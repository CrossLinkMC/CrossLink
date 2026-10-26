#pragma once

#include "crosslink/api/proto/TypedPacket.hpp"

#include <cstddef>
#include <cstdint>
#include <string_view>

namespace crosslink::proto {

/// Chunk payload. Read-only: the gateway inspects the dimension to decide
/// whether a chunk still belongs to the world the client is looking at, and
/// forwards the bytes untouched.
class CROSSLINK_API LevelChunkPacket final : public TypedPacket<LevelChunkPacket, PacketId::LevelChunk> {
public:
    static constexpr std::string_view staticName = "LevelChunkPacket";

    using TypedPacket::TypedPacket;

    [[nodiscard]] std::int32_t  dimension() const;
    [[nodiscard]] std::uint32_t subChunkCount() const;
    [[nodiscard]] bool          cacheEnabled() const;
    /// True when the client has to ask for sub chunks itself.
    [[nodiscard]] bool          clientNeedsToRequestSubChunks() const;

protected:
    Result<> decodeImpl() override;

private:
    std::int32_t  mDimension{};
    std::uint32_t mSubChunkCount{};
    bool          mCacheEnabled{};
    bool          mClientNeedsToRequestSubChunks{};
};

class CROSSLINK_API SubChunkPacket final : public TypedPacket<SubChunkPacket, PacketId::SubChunk> {
public:
    static constexpr std::string_view staticName = "SubChunkPacket";

    using TypedPacket::TypedPacket;

    [[nodiscard]] std::int32_t dimension() const;
    [[nodiscard]] bool         cacheEnabled() const;
    [[nodiscard]] std::size_t  entryCount() const;

protected:
    Result<> decodeImpl() override;

private:
    std::int32_t mDimension{};
    bool         mCacheEnabled{};
    std::size_t  mEntryCount{};
};

/// The client's request for sub chunks. Carries a dimension the gateway may have
/// to correct: a client that has not finished a dimension load still asks for the
/// dimension it believes it is in.
class CROSSLINK_API SubChunkRequestPacket final
: public TypedPacket<SubChunkRequestPacket, PacketId::SubChunkRequest> {
public:
    static constexpr std::string_view staticName = "SubChunkRequestPacket";

    using TypedPacket::TypedPacket;

    [[nodiscard]] std::int32_t dimension() const;
    void                       setDimension(std::int32_t dimension);

protected:
    Result<> decodeImpl() override;
    Result<> encodeImpl() override;

private:
    std::int32_t mDimension{};
};

} // namespace crosslink::proto
