#include "crosslink/api/proto/packets/PlayerInitPackets.hpp"

#include "proto/SculkBridge.hpp"

#include <sculk/protocol/codec/packet/ClientCacheStatusPacket.hpp>
#include <sculk/protocol/codec/packet/SetLocalPlayerAsInitializedPacket.hpp>
#include <sculk/protocol/codec/packet/SetPlayerGameTypePacket.hpp>
#include <sculk/protocol/codec/packet/SetPlayerInventoryOptionsPacket.hpp>

namespace crosslink::proto {
namespace {

namespace bp = bridge::bp;

template <typename Enum>
std::int32_t enumToInt(Enum value) noexcept {
    return static_cast<std::int32_t>(value);
}

template <typename Enum>
Enum intToEnum(std::int32_t value) noexcept {
    return static_cast<Enum>(value);
}

} // namespace

// ---- SetLocalPlayerAsInitialized --------------------------------------

SetLocalPlayerAsInitializedPacket::SetLocalPlayerAsInitializedPacket(std::uint64_t runtimeId) : mRuntimeId(runtimeId) {}

std::uint64_t SetLocalPlayerAsInitializedPacket::runtimeId() const { return mRuntimeId; }

void SetLocalPlayerAsInitializedPacket::setRuntimeId(std::uint64_t runtimeId) {
    mRuntimeId = runtimeId;
    markDirty();
}

Result<> SetLocalPlayerAsInitializedPacket::decodeImpl() {
    auto packet = bridge::decode<bp::SetLocalPlayerAsInitializedPacket>(payload());
    if (!packet) return std::unexpected(packet.error());
    mRuntimeId = packet->mRuntimeId;
    return {};
}

Result<> SetLocalPlayerAsInitializedPacket::encodeImpl() {
    bp::SetLocalPlayerAsInitializedPacket packet;
    packet.mRuntimeId = mRuntimeId;
    setSerialized(bridge::serialize(header(), packet), bridge::serializedHeaderSize(header()));
    return {};
}

// ---- ClientCacheStatus -------------------------------------------------

ClientCacheStatusPacket::ClientCacheStatusPacket(bool cacheSupported) : mCacheSupported(cacheSupported) {}

bool ClientCacheStatusPacket::cacheSupported() const { return mCacheSupported; }

void ClientCacheStatusPacket::setCacheSupported(bool cacheSupported) {
    mCacheSupported = cacheSupported;
    markDirty();
}

Result<> ClientCacheStatusPacket::decodeImpl() {
    auto packet = bridge::decode<bp::ClientCacheStatusPacket>(payload());
    if (!packet) return std::unexpected(packet.error());
    mCacheSupported = packet->mIsCacheSupport;
    return {};
}

Result<> ClientCacheStatusPacket::encodeImpl() {
    bp::ClientCacheStatusPacket packet;
    packet.mIsCacheSupport = mCacheSupported;
    setSerialized(bridge::serialize(header(), packet), bridge::serializedHeaderSize(header()));
    return {};
}

// ---- SetPlayerGameType -------------------------------------------------

SetPlayerGameTypePacket::SetPlayerGameTypePacket(GameType gameType) : mGameType(gameType) {}

GameType SetPlayerGameTypePacket::gameType() const { return mGameType; }

void SetPlayerGameTypePacket::setGameType(GameType gameType) {
    mGameType = gameType;
    markDirty();
}

Result<> SetPlayerGameTypePacket::decodeImpl() {
    auto packet = bridge::decode<bp::SetPlayerGameTypePacket>(payload());
    if (!packet) return std::unexpected(packet.error());
    mGameType = bridge::fromSculk(packet->mGameType);
    return {};
}

Result<> SetPlayerGameTypePacket::encodeImpl() {
    bp::SetPlayerGameTypePacket packet;
    packet.mGameType = bridge::toSculk(mGameType);
    setSerialized(bridge::serialize(header(), packet), bridge::serializedHeaderSize(header()));
    return {};
}

// ---- SetPlayerInventoryOptions -----------------------------------------

SetPlayerInventoryOptionsPacket::SetPlayerInventoryOptionsPacket(
    std::int32_t leftTab,
    std::int32_t rightTab,
    std::int32_t layout,
    std::int32_t craftLayout
)
: mLeftTab(leftTab), mRightTab(rightTab), mLayout(layout), mCraftLayout(craftLayout) {}

namespace {

std::int32_t leftTabFor(GameType gameType) {
    const bool survivalLike = gameType == GameType::Survival || gameType == GameType::Adventure;
    return survivalLike ? enumToInt(bp::InventoryLeftTabIndex::Survival) : enumToInt(bp::InventoryLeftTabIndex::RecipeSearch);
}

} // namespace

SetPlayerInventoryOptionsPacket::SetPlayerInventoryOptionsPacket(GameType gameType)
: SetPlayerInventoryOptionsPacket(
      leftTabFor(gameType),
      enumToInt(bp::InventoryRightTabIndex::FullScreen),
      enumToInt(bp::InventoryLayout::Default),
      enumToInt(bp::InventoryLayout::Default)
  ) {}

std::int32_t SetPlayerInventoryOptionsPacket::leftTab() const { return mLeftTab; }

std::int32_t SetPlayerInventoryOptionsPacket::rightTab() const { return mRightTab; }

std::int32_t SetPlayerInventoryOptionsPacket::layout() const { return mLayout; }

std::int32_t SetPlayerInventoryOptionsPacket::craftLayout() const { return mCraftLayout; }

Result<> SetPlayerInventoryOptionsPacket::decodeImpl() {
    auto packet = bridge::decode<bp::SetPlayerInventoryOptionsPacket>(payload());
    if (!packet) return std::unexpected(packet.error());
    mLeftTab = enumToInt(packet->mLeftInventoryTab);
    mRightTab = enumToInt(packet->mRightInventoryTab);
    mLayout = enumToInt(packet->mLayoutInventory);
    mCraftLayout = enumToInt(packet->mLayoutCraft);
    return {};
}

Result<> SetPlayerInventoryOptionsPacket::encodeImpl() {
    bp::SetPlayerInventoryOptionsPacket packet;
    packet.mLeftInventoryTab = intToEnum<bp::InventoryLeftTabIndex>(mLeftTab);
    packet.mRightInventoryTab = intToEnum<bp::InventoryRightTabIndex>(mRightTab);
    packet.mLayoutInventory = intToEnum<bp::InventoryLayout>(mLayout);
    packet.mLayoutCraft = intToEnum<bp::InventoryLayout>(mCraftLayout);
    setSerialized(bridge::serialize(header(), packet), bridge::serializedHeaderSize(header()));
    return {};
}

} // namespace crosslink::proto
