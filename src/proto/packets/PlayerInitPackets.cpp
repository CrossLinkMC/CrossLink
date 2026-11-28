#include "crosslink/api/proto/packets/PlayerInitPackets.hpp"

#include "proto/EndstoneBridge.hpp"

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
    mRuntimeId = packet->player_id;
    return {};
}

Result<> SetLocalPlayerAsInitializedPacket::encodeImpl() {
    bp::SetLocalPlayerAsInitializedPacket packet;
    packet.player_id = bp::ActorRuntimeID{mRuntimeId};
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
    mCacheSupported = packet->enabled;
    return {};
}

Result<> ClientCacheStatusPacket::encodeImpl() {
    bp::ClientCacheStatusPacket packet;
    packet.enabled = mCacheSupported;
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
    mGameType = bridge::fromWire(packet->player_game_type);
    return {};
}

Result<> SetPlayerGameTypePacket::encodeImpl() {
    bp::SetPlayerGameTypePacket packet;
    packet.player_game_type = bridge::toWire(mGameType);
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

bool SetPlayerInventoryOptionsPacket::filtering() const { return mFiltering; }

void SetPlayerInventoryOptionsPacket::setGameType(GameType gameType) {
    if (gameType != GameType::Survival && gameType != GameType::Adventure && gameType != GameType::Creative) return;
    const auto tab = leftTabFor(gameType);
    if (mLeftTab == tab) return;
    mLeftTab = tab;
    markDirty();
}

Result<> SetPlayerInventoryOptionsPacket::decodeImpl() {
    auto packet = bridge::decode<bp::SetPlayerInventoryOptionsPacket>(payload());
    if (!packet) return std::unexpected(packet.error());
    auto const& options = packet->inventory_options;
    mLeftTab = enumToInt(options.left_inventory_tab);
    mRightTab = enumToInt(options.right_inventory_tab);
    mFiltering = options.filtering;
    mLayout = enumToInt(options.layout_inv);
    mCraftLayout = enumToInt(options.layout_craft);
    return {};
}

Result<> SetPlayerInventoryOptionsPacket::encodeImpl() {
    bp::SetPlayerInventoryOptionsPacket packet;
    packet.inventory_options.left_inventory_tab = intToEnum<bp::InventoryLeftTabIndex>(mLeftTab);
    packet.inventory_options.right_inventory_tab = intToEnum<bp::InventoryRightTabIndex>(mRightTab);
    packet.inventory_options.filtering = mFiltering;
    packet.inventory_options.layout_inv = intToEnum<bp::InventoryLayout>(mLayout);
    packet.inventory_options.layout_craft = intToEnum<bp::InventoryLayout>(mCraftLayout);
    setSerialized(bridge::serialize(header(), packet), bridge::serializedHeaderSize(header()));
    return {};
}

} // namespace crosslink::proto
