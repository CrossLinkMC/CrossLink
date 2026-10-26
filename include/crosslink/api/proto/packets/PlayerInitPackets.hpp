#pragma once

#include "crosslink/api/proto/TypedPacket.hpp"

#include <cstdint>
#include <string_view>

namespace crosslink::proto {

/// Tells a backend that the client finished spawning. A handoff replays it for
/// every backend it attaches, using that backend's own runtime id.
class CROSSLINK_API SetLocalPlayerAsInitializedPacket final
: public TypedPacket<SetLocalPlayerAsInitializedPacket, PacketId::SetLocalPlayerAsInitialized> {
public:
    static constexpr std::string_view staticName = "SetLocalPlayerAsInitializedPacket";

    using TypedPacket::TypedPacket;

    explicit SetLocalPlayerAsInitializedPacket(std::uint64_t runtimeId);

    [[nodiscard]] std::uint64_t runtimeId() const;
    void                        setRuntimeId(std::uint64_t runtimeId);

protected:
    Result<> decodeImpl() override;
    Result<> encodeImpl() override;

private:
    std::uint64_t mRuntimeId{};
};

/// Client blob cache support. The gateway forces this off towards backends: a
/// cache built against one server's chunks must not be replayed by another.
class CROSSLINK_API ClientCacheStatusPacket final
: public TypedPacket<ClientCacheStatusPacket, PacketId::ClientCacheStatus> {
public:
    static constexpr std::string_view staticName = "ClientCacheStatusPacket";

    using TypedPacket::TypedPacket;

    explicit ClientCacheStatusPacket(bool cacheSupported);

    [[nodiscard]] bool cacheSupported() const;
    void               setCacheSupported(bool cacheSupported);

protected:
    Result<> decodeImpl() override;
    Result<> encodeImpl() override;

private:
    bool mCacheSupported{};
};

class CROSSLINK_API SetPlayerGameTypePacket final
: public TypedPacket<SetPlayerGameTypePacket, PacketId::SetPlayerGameType> {
public:
    static constexpr std::string_view staticName = "SetPlayerGameTypePacket";

    using TypedPacket::TypedPacket;

    explicit SetPlayerGameTypePacket(GameType gameType);

    [[nodiscard]] GameType gameType() const;
    void                   setGameType(GameType gameType);

protected:
    Result<> decodeImpl() override;
    Result<> encodeImpl() override;

private:
    GameType mGameType{GameType::Undefined};
};

/// Inventory tab and layout selection. Sub servers routinely disagree about it,
/// and a stale value leaves the client with an unusable inventory screen after a
/// handoff, so the gateway re-syncs it whenever the game type changes.
class CROSSLINK_API SetPlayerInventoryOptionsPacket final
: public TypedPacket<SetPlayerInventoryOptionsPacket, PacketId::SetPlayerInventoryOptions> {
public:
    static constexpr std::string_view staticName = "SetPlayerInventoryOptionsPacket";

    using TypedPacket::TypedPacket;

    SetPlayerInventoryOptionsPacket(std::int32_t leftTab, std::int32_t rightTab, std::int32_t layout, std::int32_t craftLayout);

    /// Picks the tabs and layouts a vanilla client would choose for a game type.
    explicit SetPlayerInventoryOptionsPacket(GameType gameType);

    [[nodiscard]] std::int32_t leftTab() const;
    [[nodiscard]] std::int32_t rightTab() const;
    [[nodiscard]] std::int32_t layout() const;
    [[nodiscard]] std::int32_t craftLayout() const;

protected:
    Result<> decodeImpl() override;
    Result<> encodeImpl() override;

private:
    std::int32_t mLeftTab{};
    std::int32_t mRightTab{};
    std::int32_t mLayout{};
    std::int32_t mCraftLayout{};
};

} // namespace crosslink::proto
