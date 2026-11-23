#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <expected>
#include <optional>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>

#include <bedrock/protocol/detail/reflect.hpp>
#include <bedrock/protocol/enum.hpp>
#include <bedrock/protocol/nbt.hpp>
#include <bedrock/protocol/packet.hpp>
#include <bedrock/protocol/serializer.hpp>
#include <bedrock/protocol/stream.hpp>

#include <bedrock/protocol/actor.h>
#include <bedrock/protocol/common.h>
#include <bedrock/protocol/item.h>
#include <bedrock/protocol/network.h>

namespace bedrock::protocol {

struct GuiDataPickItemPacket {
    static constexpr int Id = 54;
    std::string item_name{};
    std::string item_effect_name{};
    std::int32_t slot{};
};

struct CompletedUsingItemPacket {
    static constexpr int Id = 142;
    std::int16_t item_id{};
    std::int32_t item_use_method{};
};

struct PlayerToggleCrafterSlotRequestPacket {
    static constexpr int Id = 306;
    std::int32_t pos_x{};
    std::int32_t pos_y{};
    std::int32_t pos_z{};
    std::int32_t slot_index{};
    bool is_disabled{};
};

enum class InventoryLayout : int {
    None = 0,
    InventoryOnly = 1,
    Default = 2,
    RecipeBookOnly = 3,
    Count = 4,
};

enum class InventoryLeftTabIndex : int {
    None = 0,
    RecipeConstruction = 1,
    RecipeEquipment = 2,
    RecipeItems = 3,
    RecipeNature = 4,
    RecipeSearch = 5,
    Survival = 6,
    Count = 7,
};

enum class InventoryRightTabIndex : int {
    None = 0,
    FullScreen = 1,
    Crafting = 2,
    Armor = 3,
    Count = 4,
};

struct InventoryOptions {
    InventoryLeftTabIndex left_inventory_tab{};
    InventoryRightTabIndex right_inventory_tab{};
    bool filtering{};
    InventoryLayout layout_inv{};
    InventoryLayout layout_craft{};
};

struct SetPlayerInventoryOptionsPacket {
    static constexpr int Id = 307;
    InventoryOptions inventory_options{};
};

enum class FurnaceLeftTabIndex : int {
    None = 0,
    RecipeFood = 1,
    RecipeItems = 2,
    RecipeBlocks = 3,
    RecipeSearch = 4,
    Inventory = 5,
    Count = 6,
};

enum class FurnaceLayout : int {
    None = 0,
    InventoryOnly = 1,
    Default = 2,
    Count = 3,
};

struct FurnaceOptions {
    FurnaceLeftTabIndex left_furnace_tab{};
    bool filtering{};
    FurnaceLayout layout{};
};

enum class CursorItemDragState : std::uint8_t {
    Start = 0,
    Stop = 1,
};

namespace base {

enum class ContainerID : std::int8_t {
    None = -1,
    Inventory = 0,
    First = 1,
    Last = 100,
    Offhand = 119,
    Armor = 120,
    SelectionSlots = 122,
    PlayerOnlyUi = 124,
    Registry = 125,
    RegistryInventory = 126,
};

enum class ContainerEnumName : std::uint8_t {
    AnvilInputContainer = 0,
    AnvilMaterialContainer = 1,
    AnvilResultPreviewContainer = 2,
    SmithingTableInputContainer = 3,
    SmithingTableMaterialContainer = 4,
    SmithingTableResultPreviewContainer = 5,
    ArmorContainer = 6,
    LevelEntityContainer = 7,
    BeaconPaymentContainer = 8,
    BrewingStandInputContainer = 9,
    BrewingStandResultContainer = 10,
    BrewingStandFuelContainer = 11,
    CombinedHotbarAndInventoryContainer = 12,
    CraftingInputContainer = 13,
    CraftingOutputPreviewContainer = 14,
    RecipeConstructionContainer = 15,
    RecipeNatureContainer = 16,
    RecipeItemsContainer = 17,
    RecipeSearchContainer = 18,
    RecipeSearchBarContainer = 19,
    RecipeEquipmentContainer = 20,
    RecipeBookContainer = 21,
    EnchantingInputContainer = 22,
    EnchantingMaterialContainer = 23,
    FurnaceFuelContainer = 24,
    FurnaceIngredientContainer = 25,
    FurnaceResultContainer = 26,
    HorseEquipContainer = 27,
    HotbarContainer = 28,
    InventoryContainer = 29,
    ShulkerBoxContainer = 30,
    TradeIngredient1Container = 31,
    TradeIngredient2Container = 32,
    TradeResultPreviewContainer = 33,
    OffhandContainer = 34,
    CompoundCreatorInput = 35,
    CompoundCreatorOutputPreview = 36,
    ElementConstructorOutputPreview = 37,
    MaterialReducerInput = 38,
    MaterialReducerOutput = 39,
    LabTableInput = 40,
    LoomInputContainer = 41,
    LoomDyeContainer = 42,
    LoomMaterialContainer = 43,
    LoomResultPreviewContainer = 44,
    BlastFurnaceIngredientContainer = 45,
    SmokerIngredientContainer = 46,
    Trade2Ingredient1Container = 47,
    Trade2Ingredient2Container = 48,
    Trade2ResultPreviewContainer = 49,
    GrindstoneInputContainer = 50,
    GrindstoneAdditionalContainer = 51,
    GrindstoneResultPreviewContainer = 52,
    StonecutterInputContainer = 53,
    StonecutterResultPreviewContainer = 54,
    CartographyInputContainer = 55,
    CartographyAdditionalContainer = 56,
    CartographyResultPreviewContainer = 57,
    BarrelContainer = 58,
    CursorContainer = 59,
    CreatedOutputContainer = 60,
    SmithingTableTemplateContainer = 61,
    CrafterLevelEntityContainer = 62,
    DynamicContainer = 63,
};

struct FullContainerName {
    base::ContainerEnumName name{};
    std::optional<std::uint32_t> dynamic_id{};
};

struct InventoryContentPacket {
    static constexpr int Id = 49;
    base::ContainerID inventory_id{};
    std::vector<NetworkItemStackDescriptor> slots{};
    base::FullContainerName full_container_name{};
    std::uint32_t dynamic_container_size{};
};

struct InventorySlotPacket {
    static constexpr int Id = 50;
    base::ContainerID inventory_id{};
    std::uint32_t slot{};
    base::FullContainerName full_container_name{};
    std::uint32_t dynamic_container_size{};
    NetworkItemStackDescriptor item{};
};

enum class ContainerType : std::int8_t {
    None = -9,
    Inventory = -1,
    Container = 0,
    Workbench = 1,
    Furnace = 2,
    Enchantment = 3,
    BrewingStand = 4,
    Anvil = 5,
    Dispenser = 6,
    Dropper = 7,
    Hopper = 8,
    Cauldron = 9,
    MinecartChest = 10,
    MinecartHopper = 11,
    Horse = 12,
    Beacon = 13,
    StructureEditor = 14,
    Trade = 15,
    CommandBlock = 16,
    Jukebox = 17,
    Armor = 18,
    Hand = 19,
    CompoundCreator = 20,
    ElementConstructor = 21,
    MaterialReducer = 22,
    LabTable = 23,
    Loom = 24,
    Lectern = 25,
    Grindstone = 26,
    BlastFurnace = 27,
    Smoker = 28,
    Stonecutter = 29,
    Cartography = 30,
    Hud = 31,
    JigsawEditor = 32,
    SmithingTable = 33,
    ChestBoat = 34,
    DecoratedPot = 35,
    Crafter = 36,
};

struct ContainerClosePacket {
    static constexpr int Id = 47;
    base::ContainerID container_id{};
    base::ContainerType container_type{};
    bool server_initiated_close{};
};

struct PlayerHotbarPacket {
    static constexpr int Id = 48;
    std::uint32_t selected_slot{};
    base::ContainerID container_id{};
    bool should_select_slot{};
};

struct ContainerSetDataPacket {
    static constexpr int Id = 51;
    base::ContainerID container_id{};
    std::int32_t id{};
    std::int32_t value{};
};

struct ContainerOpenPacket {
    static constexpr int Id = 46;
    base::ContainerID container_id{};
    base::ContainerType type{};
    base::NetworkBlockPosition pos{};
    ActorUniqueID entity_unique_id{};
};

struct ContainerRegistryCleanupPacket {
    static constexpr int Id = 317;
    std::vector<base::FullContainerName> removed_containers{};
};

struct UpdateTradePacket {
    static constexpr int Id = 80;
    base::ContainerID container_id{};
    base::ContainerType type{};
    std::int32_t size{};
    std::int32_t trader_tier{};
    ActorUniqueID entity_unique_id{};
    ActorUniqueID last_trading_player{};
    std::string display_name{};
    bool use_new_trade_screen{};
    bool using_economy_trade{};
    CompoundTag data{};
};

struct UpdateEquipPacket {
    static constexpr int Id = 81;
    base::ContainerID container_id{};
    base::ContainerType type{};
    std::int32_t size{};
    ActorUniqueID entity_unique_id{};
    CompoundTag data{};
};

struct MobEquipmentPacket {
    static constexpr int Id = 31;
    ActorRuntimeID runtime_id{};
    NetworkItemStackDescriptor item{};
    std::int32_t slot{};
    std::int32_t selected_slot{};
    base::ContainerID container_id{};
};

struct MobArmorEquipmentPacket {
    static constexpr int Id = 32;
    ActorRuntimeID runtime_id{};
    NetworkItemStackDescriptor head{};
    NetworkItemStackDescriptor torso{};
    NetworkItemStackDescriptor legs{};
    NetworkItemStackDescriptor feet{};
    NetworkItemStackDescriptor body{};
};

}  // namespace base

namespace v748 {

enum class ContainerID : std::int8_t {
    None = -1,
    Inventory = 0,
    First = 1,
    Last = 100,
    Offhand = 119,
    Armor = 120,
    SelectionSlots = 122,
    PlayerOnlyUi = 124,
    Registry = 125,
};

using ContainerEnumName = base::ContainerEnumName;

using FullContainerName = base::FullContainerName;

struct InventoryContentPacket {
    static constexpr int Id = 49;
    v748::ContainerID inventory_id{};
    std::vector<NetworkItemStackDescriptor> slots{};
    base::FullContainerName full_container_name{};
    NetworkItemStackDescriptor storage_item{};
};

struct InventorySlotPacket {
    static constexpr int Id = 50;
    v748::ContainerID inventory_id{};
    std::uint32_t slot{};
    base::FullContainerName full_container_name{};
    NetworkItemStackDescriptor storage_item{};
    NetworkItemStackDescriptor item{};
};

using ContainerType = base::ContainerType;

struct ContainerClosePacket {
    static constexpr int Id = 47;
    v748::ContainerID container_id{};
    base::ContainerType container_type{};
    bool server_initiated_close{};
};

struct PlayerHotbarPacket {
    static constexpr int Id = 48;
    std::uint32_t selected_slot{};
    v748::ContainerID container_id{};
    bool should_select_slot{};
};

struct ContainerSetDataPacket {
    static constexpr int Id = 51;
    v748::ContainerID container_id{};
    std::int32_t id{};
    std::int32_t value{};
};

struct ContainerOpenPacket {
    static constexpr int Id = 46;
    v748::ContainerID container_id{};
    base::ContainerType type{};
    base::NetworkBlockPosition pos{};
    ActorUniqueID entity_unique_id{};
};

using ContainerRegistryCleanupPacket = base::ContainerRegistryCleanupPacket;

struct UpdateTradePacket {
    static constexpr int Id = 80;
    v748::ContainerID container_id{};
    base::ContainerType type{};
    std::int32_t size{};
    std::int32_t trader_tier{};
    ActorUniqueID entity_unique_id{};
    ActorUniqueID last_trading_player{};
    std::string display_name{};
    bool use_new_trade_screen{};
    bool using_economy_trade{};
    CompoundTag data{};
};

struct UpdateEquipPacket {
    static constexpr int Id = 81;
    v748::ContainerID container_id{};
    base::ContainerType type{};
    std::int32_t size{};
    ActorUniqueID entity_unique_id{};
    CompoundTag data{};
};

struct MobEquipmentPacket {
    static constexpr int Id = 31;
    ActorRuntimeID runtime_id{};
    NetworkItemStackDescriptor item{};
    std::int32_t slot{};
    std::int32_t selected_slot{};
    v748::ContainerID container_id{};
};

using MobArmorEquipmentPacket = base::MobArmorEquipmentPacket;

}  // namespace v748

namespace v766 {

using ContainerID = v748::ContainerID;

using ContainerEnumName = base::ContainerEnumName;

using FullContainerName = base::FullContainerName;

using InventoryContentPacket = v748::InventoryContentPacket;

using InventorySlotPacket = v748::InventorySlotPacket;

using ContainerType = base::ContainerType;

using ContainerClosePacket = v748::ContainerClosePacket;

using PlayerHotbarPacket = v748::PlayerHotbarPacket;

using ContainerSetDataPacket = v748::ContainerSetDataPacket;

using ContainerOpenPacket = v748::ContainerOpenPacket;

using ContainerRegistryCleanupPacket = base::ContainerRegistryCleanupPacket;

using UpdateTradePacket = v748::UpdateTradePacket;

using UpdateEquipPacket = v748::UpdateEquipPacket;

using MobEquipmentPacket = v748::MobEquipmentPacket;

using MobArmorEquipmentPacket = base::MobArmorEquipmentPacket;

}  // namespace v766

namespace v776 {

using ContainerID = v748::ContainerID;

using ContainerEnumName = base::ContainerEnumName;

using FullContainerName = base::FullContainerName;

using InventoryContentPacket = v748::InventoryContentPacket;

using InventorySlotPacket = v748::InventorySlotPacket;

using ContainerType = base::ContainerType;

using ContainerClosePacket = v748::ContainerClosePacket;

using PlayerHotbarPacket = v748::PlayerHotbarPacket;

using ContainerSetDataPacket = v748::ContainerSetDataPacket;

using ContainerOpenPacket = v748::ContainerOpenPacket;

using ContainerRegistryCleanupPacket = base::ContainerRegistryCleanupPacket;

using UpdateTradePacket = v748::UpdateTradePacket;

using UpdateEquipPacket = v748::UpdateEquipPacket;

using MobEquipmentPacket = v748::MobEquipmentPacket;

using MobArmorEquipmentPacket = base::MobArmorEquipmentPacket;

}  // namespace v776

namespace v786 {

using ContainerID = v748::ContainerID;

using ContainerEnumName = base::ContainerEnumName;

using FullContainerName = base::FullContainerName;

using InventoryContentPacket = v748::InventoryContentPacket;

using InventorySlotPacket = v748::InventorySlotPacket;

using ContainerType = base::ContainerType;

using ContainerClosePacket = v748::ContainerClosePacket;

using PlayerHotbarPacket = v748::PlayerHotbarPacket;

using ContainerSetDataPacket = v748::ContainerSetDataPacket;

using ContainerOpenPacket = v748::ContainerOpenPacket;

using ContainerRegistryCleanupPacket = base::ContainerRegistryCleanupPacket;

using UpdateTradePacket = v748::UpdateTradePacket;

using UpdateEquipPacket = v748::UpdateEquipPacket;

using MobEquipmentPacket = v748::MobEquipmentPacket;

using MobArmorEquipmentPacket = base::MobArmorEquipmentPacket;

}  // namespace v786

namespace v800 {

using ContainerID = v748::ContainerID;

using ContainerEnumName = base::ContainerEnumName;

using FullContainerName = base::FullContainerName;

using InventoryContentPacket = v748::InventoryContentPacket;

using InventorySlotPacket = v748::InventorySlotPacket;

using ContainerType = base::ContainerType;

using ContainerClosePacket = v748::ContainerClosePacket;

using PlayerHotbarPacket = v748::PlayerHotbarPacket;

using ContainerSetDataPacket = v748::ContainerSetDataPacket;

using ContainerOpenPacket = v748::ContainerOpenPacket;

using ContainerRegistryCleanupPacket = base::ContainerRegistryCleanupPacket;

using UpdateTradePacket = v748::UpdateTradePacket;

using UpdateEquipPacket = v748::UpdateEquipPacket;

using MobEquipmentPacket = v748::MobEquipmentPacket;

using MobArmorEquipmentPacket = base::MobArmorEquipmentPacket;

}  // namespace v800

namespace v818 {

using ContainerID = v748::ContainerID;

using ContainerEnumName = base::ContainerEnumName;

using FullContainerName = base::FullContainerName;

using InventoryContentPacket = v748::InventoryContentPacket;

using InventorySlotPacket = v748::InventorySlotPacket;

using ContainerType = base::ContainerType;

using ContainerClosePacket = v748::ContainerClosePacket;

using PlayerHotbarPacket = v748::PlayerHotbarPacket;

using ContainerSetDataPacket = v748::ContainerSetDataPacket;

using ContainerOpenPacket = v748::ContainerOpenPacket;

using ContainerRegistryCleanupPacket = base::ContainerRegistryCleanupPacket;

using UpdateTradePacket = v748::UpdateTradePacket;

using UpdateEquipPacket = v748::UpdateEquipPacket;

using MobEquipmentPacket = v748::MobEquipmentPacket;

using MobArmorEquipmentPacket = base::MobArmorEquipmentPacket;

}  // namespace v818

namespace v827 {

using ContainerID = v748::ContainerID;

using ContainerEnumName = base::ContainerEnumName;

using FullContainerName = base::FullContainerName;

using InventoryContentPacket = v748::InventoryContentPacket;

using InventorySlotPacket = v748::InventorySlotPacket;

using ContainerType = base::ContainerType;

using ContainerClosePacket = v748::ContainerClosePacket;

using PlayerHotbarPacket = v748::PlayerHotbarPacket;

using ContainerSetDataPacket = v748::ContainerSetDataPacket;

using ContainerOpenPacket = v748::ContainerOpenPacket;

using ContainerRegistryCleanupPacket = base::ContainerRegistryCleanupPacket;

using UpdateTradePacket = v748::UpdateTradePacket;

using UpdateEquipPacket = v748::UpdateEquipPacket;

using MobEquipmentPacket = v748::MobEquipmentPacket;

using MobArmorEquipmentPacket = base::MobArmorEquipmentPacket;

}  // namespace v827

namespace v844 {

using ContainerID = v748::ContainerID;

using ContainerEnumName = base::ContainerEnumName;

using FullContainerName = base::FullContainerName;

using InventoryContentPacket = v748::InventoryContentPacket;

using InventorySlotPacket = v748::InventorySlotPacket;

using ContainerType = base::ContainerType;

using ContainerClosePacket = v748::ContainerClosePacket;

using PlayerHotbarPacket = v748::PlayerHotbarPacket;

using ContainerSetDataPacket = v748::ContainerSetDataPacket;

using ContainerOpenPacket = v748::ContainerOpenPacket;

using ContainerRegistryCleanupPacket = base::ContainerRegistryCleanupPacket;

using UpdateTradePacket = v748::UpdateTradePacket;

using UpdateEquipPacket = v748::UpdateEquipPacket;

using MobEquipmentPacket = v748::MobEquipmentPacket;

using MobArmorEquipmentPacket = base::MobArmorEquipmentPacket;

}  // namespace v844

namespace v859 {

using ContainerID = v748::ContainerID;

using ContainerEnumName = base::ContainerEnumName;

using FullContainerName = base::FullContainerName;

using InventoryContentPacket = v748::InventoryContentPacket;

using InventorySlotPacket = v748::InventorySlotPacket;

using ContainerType = base::ContainerType;

using ContainerClosePacket = v748::ContainerClosePacket;

using PlayerHotbarPacket = v748::PlayerHotbarPacket;

using ContainerSetDataPacket = v748::ContainerSetDataPacket;

using ContainerOpenPacket = v748::ContainerOpenPacket;

using ContainerRegistryCleanupPacket = base::ContainerRegistryCleanupPacket;

using UpdateTradePacket = v748::UpdateTradePacket;

using UpdateEquipPacket = v748::UpdateEquipPacket;

using MobEquipmentPacket = v748::MobEquipmentPacket;

using MobArmorEquipmentPacket = base::MobArmorEquipmentPacket;

}  // namespace v859

namespace v898 {

using ContainerID = v748::ContainerID;

using ContainerEnumName = base::ContainerEnumName;

using FullContainerName = base::FullContainerName;

using InventoryContentPacket = v748::InventoryContentPacket;

using InventorySlotPacket = v748::InventorySlotPacket;

using ContainerType = base::ContainerType;

using ContainerClosePacket = v748::ContainerClosePacket;

using PlayerHotbarPacket = v748::PlayerHotbarPacket;

using ContainerSetDataPacket = v748::ContainerSetDataPacket;

using ContainerOpenPacket = v748::ContainerOpenPacket;

using ContainerRegistryCleanupPacket = base::ContainerRegistryCleanupPacket;

using UpdateTradePacket = v748::UpdateTradePacket;

using UpdateEquipPacket = v748::UpdateEquipPacket;

using MobEquipmentPacket = v748::MobEquipmentPacket;

using MobArmorEquipmentPacket = base::MobArmorEquipmentPacket;

}  // namespace v898

namespace v924 {

using ContainerID = v748::ContainerID;

enum class ContainerEnumName : std::uint8_t {
    AnvilInputContainer = 0,
    AnvilMaterialContainer = 1,
    AnvilResultPreviewContainer = 2,
    SmithingTableInputContainer = 3,
    SmithingTableMaterialContainer = 4,
    SmithingTableResultPreviewContainer = 5,
    ArmorContainer = 6,
    LevelEntityContainer = 7,
    BeaconPaymentContainer = 8,
    BrewingStandInputContainer = 9,
    BrewingStandResultContainer = 10,
    BrewingStandFuelContainer = 11,
    CombinedHotbarAndInventoryContainer = 12,
    CraftingInputContainer = 13,
    CraftingOutputPreviewContainer = 14,
    RecipeConstructionContainer = 15,
    RecipeNatureContainer = 16,
    RecipeItemsContainer = 17,
    RecipeSearchContainer = 18,
    RecipeSearchBarContainer = 19,
    RecipeEquipmentContainer = 20,
    RecipeBookContainer = 21,
    EnchantingInputContainer = 22,
    EnchantingMaterialContainer = 23,
    FurnaceFuelContainer = 24,
    FurnaceIngredientContainer = 25,
    FurnaceResultContainer = 26,
    HorseEquipContainer = 27,
    HotbarContainer = 28,
    InventoryContainer = 29,
    ShulkerBoxContainer = 30,
    TradeIngredient1Container = 31,
    TradeIngredient2Container = 32,
    TradeResultPreviewContainer = 33,
    OffhandContainer = 34,
    CompoundCreatorInput = 35,
    CompoundCreatorOutputPreview = 36,
    ElementConstructorOutputPreview = 37,
    MaterialReducerInput = 38,
    MaterialReducerOutput = 39,
    LabTableInput = 40,
    LoomInputContainer = 41,
    LoomDyeContainer = 42,
    LoomMaterialContainer = 43,
    LoomResultPreviewContainer = 44,
    BlastFurnaceIngredientContainer = 45,
    SmokerIngredientContainer = 46,
    Trade2Ingredient1Container = 47,
    Trade2Ingredient2Container = 48,
    Trade2ResultPreviewContainer = 49,
    GrindstoneInputContainer = 50,
    GrindstoneAdditionalContainer = 51,
    GrindstoneResultPreviewContainer = 52,
    StonecutterInputContainer = 53,
    StonecutterResultPreviewContainer = 54,
    CartographyInputContainer = 55,
    CartographyAdditionalContainer = 56,
    CartographyResultPreviewContainer = 57,
    BarrelContainer = 58,
    CursorContainer = 59,
    CreatedOutputContainer = 60,
    SmithingTableTemplateContainer = 61,
    CrafterLevelEntityContainer = 62,
    DynamicContainer = 63,
    RecipeFoodContainer = 64,
    RecipeBlocksContainer = 65,
    RecipeFurnaceItemsContainer = 66,
};

struct FullContainerName {
    v924::ContainerEnumName name{};
    std::optional<std::uint32_t> dynamic_id{};
};

struct InventoryContentPacket {
    static constexpr int Id = 49;
    v748::ContainerID inventory_id{};
    std::vector<NetworkItemStackDescriptor> slots{};
    v924::FullContainerName full_container_name{};
    NetworkItemStackDescriptor storage_item{};
};

struct InventorySlotPacket {
    static constexpr int Id = 50;
    v748::ContainerID inventory_id{};
    std::uint32_t slot{};
    v924::FullContainerName full_container_name{};
    NetworkItemStackDescriptor storage_item{};
    NetworkItemStackDescriptor item{};
};

using ContainerType = base::ContainerType;

using ContainerClosePacket = v748::ContainerClosePacket;

using PlayerHotbarPacket = v748::PlayerHotbarPacket;

using ContainerSetDataPacket = v748::ContainerSetDataPacket;

using ContainerOpenPacket = v748::ContainerOpenPacket;

struct ContainerRegistryCleanupPacket {
    static constexpr int Id = 317;
    std::vector<v924::FullContainerName> removed_containers{};
};

using UpdateTradePacket = v748::UpdateTradePacket;

using UpdateEquipPacket = v748::UpdateEquipPacket;

using MobEquipmentPacket = v748::MobEquipmentPacket;

using MobArmorEquipmentPacket = base::MobArmorEquipmentPacket;

}  // namespace v924

namespace v944 {

using ContainerID = v748::ContainerID;

using ContainerEnumName = v924::ContainerEnumName;

using FullContainerName = v924::FullContainerName;

using InventoryContentPacket = v924::InventoryContentPacket;

using InventorySlotPacket = v924::InventorySlotPacket;

using ContainerType = base::ContainerType;

using ContainerClosePacket = v748::ContainerClosePacket;

using PlayerHotbarPacket = v748::PlayerHotbarPacket;

using ContainerSetDataPacket = v748::ContainerSetDataPacket;

struct ContainerOpenPacket {
    static constexpr int Id = 46;
    v748::ContainerID container_id{};
    base::ContainerType type{};
    BlockPos pos{};
    ActorUniqueID entity_unique_id{};
};

using ContainerRegistryCleanupPacket = v924::ContainerRegistryCleanupPacket;

using UpdateTradePacket = v748::UpdateTradePacket;

using UpdateEquipPacket = v748::UpdateEquipPacket;

using MobEquipmentPacket = v748::MobEquipmentPacket;

using MobArmorEquipmentPacket = base::MobArmorEquipmentPacket;

}  // namespace v944

namespace v975 {

using ContainerID = v748::ContainerID;

using ContainerEnumName = v924::ContainerEnumName;

using FullContainerName = v924::FullContainerName;

using InventoryContentPacket = v924::InventoryContentPacket;

struct InventorySlotPacket {
    static constexpr int Id = 50;
    v748::ContainerID inventory_id{};
    std::uint32_t slot{};
    std::optional<v924::FullContainerName> full_container_name{};
    std::optional<base::SerializedNetworkItemStackDescriptor> storage_item{};
    base::SerializedNetworkItemStackDescriptor item{};
};

using ContainerType = base::ContainerType;

using ContainerClosePacket = v748::ContainerClosePacket;

using PlayerHotbarPacket = v748::PlayerHotbarPacket;

using ContainerSetDataPacket = v748::ContainerSetDataPacket;

using ContainerOpenPacket = v944::ContainerOpenPacket;

using ContainerRegistryCleanupPacket = v924::ContainerRegistryCleanupPacket;

using UpdateTradePacket = v748::UpdateTradePacket;

using UpdateEquipPacket = v748::UpdateEquipPacket;

struct MobEquipmentPacket {
    static constexpr int Id = 31;
    ActorRuntimeID runtime_id{};
    base::SerializedNetworkItemStackDescriptor item{};
    std::int32_t slot{};
    std::int32_t selected_slot{};
    v748::ContainerID container_id{};
};

using MobArmorEquipmentPacket = base::MobArmorEquipmentPacket;

}  // namespace v975

namespace v1001 {

using ContainerID = v748::ContainerID;

using ContainerEnumName = v924::ContainerEnumName;

using FullContainerName = v924::FullContainerName;

struct InventoryContentPacket {
    static constexpr int Id = 49;
    v748::ContainerID inventory_id{};
    std::vector<base::SerializedNetworkItemStackDescriptor> slots{};
    v924::FullContainerName full_container_name{};
    base::SerializedNetworkItemStackDescriptor storage_item{};
};

using InventorySlotPacket = v975::InventorySlotPacket;

using ContainerType = base::ContainerType;

using ContainerClosePacket = v748::ContainerClosePacket;

using PlayerHotbarPacket = v748::PlayerHotbarPacket;

using ContainerSetDataPacket = v748::ContainerSetDataPacket;

using ContainerOpenPacket = v944::ContainerOpenPacket;

using ContainerRegistryCleanupPacket = v924::ContainerRegistryCleanupPacket;

using UpdateTradePacket = v748::UpdateTradePacket;

using UpdateEquipPacket = v748::UpdateEquipPacket;

using MobEquipmentPacket = v975::MobEquipmentPacket;

struct MobArmorEquipmentPacket {
    static constexpr int Id = 32;
    ActorRuntimeID runtime_id{};
    base::SerializedNetworkItemStackDescriptor head{};
    base::SerializedNetworkItemStackDescriptor torso{};
    base::SerializedNetworkItemStackDescriptor legs{};
    base::SerializedNetworkItemStackDescriptor feet{};
    base::SerializedNetworkItemStackDescriptor body{};
};

}  // namespace v1001

namespace v2168 {

using ContainerID = v748::ContainerID;

using ContainerEnumName = v924::ContainerEnumName;

using FullContainerName = v924::FullContainerName;

struct InventoryContentPacket {
    static constexpr int Id = 49;
    v748::ContainerID inventory_id{};
    std::vector<v2168::SerializedNetworkItemStackDescriptor> slots{};
    v924::FullContainerName full_container_name{};
    v2168::SerializedNetworkItemStackDescriptor storage_item{};
};

struct InventorySlotPacket {
    static constexpr int Id = 50;
    v748::ContainerID inventory_id{};
    std::uint32_t slot{};
    std::optional<v924::FullContainerName> full_container_name{};
    std::optional<v2168::SerializedNetworkItemStackDescriptor> storage_item{};
    v2168::SerializedNetworkItemStackDescriptor item{};
};

using ContainerType = base::ContainerType;

using ContainerClosePacket = v748::ContainerClosePacket;

using PlayerHotbarPacket = v748::PlayerHotbarPacket;

using ContainerSetDataPacket = v748::ContainerSetDataPacket;

using ContainerOpenPacket = v944::ContainerOpenPacket;

using ContainerRegistryCleanupPacket = v924::ContainerRegistryCleanupPacket;

using UpdateTradePacket = v748::UpdateTradePacket;

using UpdateEquipPacket = v748::UpdateEquipPacket;

struct MobEquipmentPacket {
    static constexpr int Id = 31;
    ActorRuntimeID runtime_id{};
    v2168::SerializedNetworkItemStackDescriptor item{};
    std::int32_t slot{};
    std::int32_t selected_slot{};
    v748::ContainerID container_id{};
};

struct MobArmorEquipmentPacket {
    static constexpr int Id = 32;
    ActorRuntimeID runtime_id{};
    v2168::SerializedNetworkItemStackDescriptor head{};
    v2168::SerializedNetworkItemStackDescriptor torso{};
    v2168::SerializedNetworkItemStackDescriptor legs{};
    v2168::SerializedNetworkItemStackDescriptor feet{};
    v2168::SerializedNetworkItemStackDescriptor body{};
};

}  // namespace v2168

namespace v2193 {

using ContainerID = v748::ContainerID;

using ContainerEnumName = v924::ContainerEnumName;

using FullContainerName = v924::FullContainerName;

using InventoryContentPacket = v2168::InventoryContentPacket;

using InventorySlotPacket = v2168::InventorySlotPacket;

enum class ContainerType : std::int8_t {
    None = -9,
    Inventory = -1,
    Container = 0,
    Workbench = 1,
    Furnace = 2,
    Enchantment = 3,
    BrewingStand = 4,
    Anvil = 5,
    Dispenser = 6,
    Dropper = 7,
    Hopper = 8,
    Cauldron = 9,
    MinecartChest = 10,
    MinecartHopper = 11,
    Horse = 12,
    Beacon = 13,
    StructureEditor = 14,
    Trade = 15,
    CommandBlock = 16,
    Jukebox = 17,
    Armor = 18,
    Hand = 19,
    CompoundCreator = 20,
    ElementConstructor = 21,
    MaterialReducer = 22,
    LabTable = 23,
    Loom = 24,
    Lectern = 25,
    Grindstone = 26,
    BlastFurnace = 27,
    Smoker = 28,
    Stonecutter = 29,
    Cartography = 30,
    Hud = 31,
    JigsawEditor = 32,
    SmithingTable = 33,
    ChestBoat = 34,
    DecoratedPot = 35,
    Crafter = 36,
    DataDrivenContainer = 37,
};

struct ContainerClosePacket {
    static constexpr int Id = 47;
    v748::ContainerID container_id{};
    v2193::ContainerType container_type{};
    bool server_initiated_close{};
};

using PlayerHotbarPacket = v748::PlayerHotbarPacket;

using ContainerSetDataPacket = v748::ContainerSetDataPacket;

struct ContainerOpenPacket {
    static constexpr int Id = 46;
    v748::ContainerID container_id{};
    v2193::ContainerType type{};
    BlockPos pos{};
    ActorUniqueID entity_unique_id{};
};

using ContainerRegistryCleanupPacket = v924::ContainerRegistryCleanupPacket;

namespace SetPlayerFurnaceOptionsPacket_nested {

enum class FurnaceType : std::uint8_t {
    None = 0,
    Furnace = 1,
    BlastFurnace = 2,
    Smoker = 3,
    Count = 4,
};

}  // namespace SetPlayerFurnaceOptionsPacket_nested

struct SetPlayerFurnaceOptionsPacket {
    using FurnaceType = SetPlayerFurnaceOptionsPacket_nested::FurnaceType;

    static constexpr int Id = 351;
    v2193::SetPlayerFurnaceOptionsPacket::FurnaceType furnace_type{};
    FurnaceOptions furnace_options{};
};

struct UpdateTradePacket {
    static constexpr int Id = 80;
    v748::ContainerID container_id{};
    v2193::ContainerType type{};
    std::int32_t size{};
    std::int32_t trader_tier{};
    ActorUniqueID entity_unique_id{};
    ActorUniqueID last_trading_player{};
    std::string display_name{};
    bool use_new_trade_screen{};
    bool using_economy_trade{};
    CompoundTag data{};
};

struct UpdateEquipPacket {
    static constexpr int Id = 81;
    v748::ContainerID container_id{};
    v2193::ContainerType type{};
    std::int32_t size{};
    ActorUniqueID entity_unique_id{};
    CompoundTag data{};
};

using MobEquipmentPacket = v2168::MobEquipmentPacket;

using MobArmorEquipmentPacket = v2168::MobArmorEquipmentPacket;

}  // namespace v2193

namespace v2225 {

using ContainerID = v748::ContainerID;

enum class ContainerEnumName : std::uint8_t {
    AnvilInputContainer = 0,
    AnvilMaterialContainer = 1,
    AnvilResultPreviewContainer = 2,
    SmithingTableInputContainer = 3,
    SmithingTableMaterialContainer = 4,
    SmithingTableResultPreviewContainer = 5,
    ArmorContainer = 6,
    LevelEntityContainer = 7,
    BeaconPaymentContainer = 8,
    BrewingStandInputContainer = 9,
    BrewingStandResultContainer = 10,
    BrewingStandFuelContainer = 11,
    CombinedHotbarAndInventoryContainer = 12,
    CraftingInputContainer = 13,
    CraftingOutputPreviewContainer = 14,
    RecipeConstructionContainer = 15,
    RecipeNatureContainer = 16,
    RecipeItemsContainer = 17,
    RecipeSearchContainer = 18,
    RecipeSearchBarContainer = 19,
    RecipeEquipmentContainer = 20,
    RecipeBookContainer = 21,
    EnchantingInputContainer = 22,
    EnchantingMaterialContainer = 23,
    FurnaceFuelContainer = 24,
    FurnaceIngredientContainer = 25,
    FurnaceResultContainer = 26,
    HorseEquipContainer = 27,
    HotbarContainer = 28,
    InventoryContainer = 29,
    ShulkerBoxContainer = 30,
    TradeIngredient1Container = 31,
    TradeIngredient2Container = 32,
    TradeResultPreviewContainer = 33,
    OffhandContainer = 34,
    CompoundCreatorInput = 35,
    CompoundCreatorOutputPreview = 36,
    ElementConstructorOutputPreview = 37,
    MaterialReducerInput = 38,
    MaterialReducerOutput = 39,
    LabTableInput = 40,
    LoomInputContainer = 41,
    LoomDyeContainer = 42,
    LoomMaterialContainer = 43,
    LoomResultPreviewContainer = 44,
    BlastFurnaceIngredientContainer = 45,
    SmokerIngredientContainer = 46,
    Trade2Ingredient1Container = 47,
    Trade2Ingredient2Container = 48,
    Trade2ResultPreviewContainer = 49,
    GrindstoneInputContainer = 50,
    GrindstoneAdditionalContainer = 51,
    GrindstoneResultPreviewContainer = 52,
    StonecutterInputContainer = 53,
    StonecutterResultPreviewContainer = 54,
    CartographyInputContainer = 55,
    CartographyAdditionalContainer = 56,
    CartographyResultPreviewContainer = 57,
    BarrelContainer = 58,
    CursorContainer = 59,
    CreatedOutputContainer = 60,
    SmithingTableTemplateContainer = 61,
    CrafterLevelEntityContainer = 62,
    DynamicContainer = 63,
    ReservedContainerA = 67,
    ReservedContainerB = 68,
    ReservedContainerC = 69,
    ReservedContainerD = 70,
    RecipeFoodContainer = 64,
    RecipeBlocksContainer = 65,
    RecipeFurnaceItemsContainer = 66,
};

struct FullContainerName {
    v2225::ContainerEnumName name{};
    std::optional<std::uint32_t> dynamic_id{};
};

struct InventoryContentPacket {
    static constexpr int Id = 49;
    v748::ContainerID inventory_id{};
    std::vector<v2168::SerializedNetworkItemStackDescriptor> slots{};
    v2225::FullContainerName full_container_name{};
    v2168::SerializedNetworkItemStackDescriptor storage_item{};
};

struct InventorySlotPacket {
    static constexpr int Id = 50;
    v748::ContainerID inventory_id{};
    std::uint32_t slot{};
    std::optional<v2225::FullContainerName> full_container_name{};
    std::optional<v2168::SerializedNetworkItemStackDescriptor> storage_item{};
    v2168::SerializedNetworkItemStackDescriptor item{};
};

enum class ContainerType : std::int8_t {
    None = -9,
    Inventory = -1,
    Container = 0,
    Workbench = 1,
    Furnace = 2,
    Enchantment = 3,
    BrewingStand = 4,
    Anvil = 5,
    Dispenser = 6,
    Dropper = 7,
    Hopper = 8,
    Cauldron = 9,
    MinecartChest = 10,
    MinecartHopper = 11,
    Horse = 12,
    Beacon = 13,
    StructureEditor = 14,
    Trade = 15,
    CommandBlock = 16,
    Jukebox = 17,
    Armor = 18,
    Hand = 19,
    CompoundCreator = 20,
    ElementConstructor = 21,
    MaterialReducer = 22,
    LabTable = 23,
    Loom = 24,
    Lectern = 25,
    Grindstone = 26,
    BlastFurnace = 27,
    Smoker = 28,
    Stonecutter = 29,
    Cartography = 30,
    Hud = 31,
    JigsawEditor = 32,
    SmithingTable = 33,
    ChestBoat = 34,
    DecoratedPot = 35,
    Crafter = 36,
    DataDrivenContainer = 37,
    ReservedContainerType = 38,
};

struct ContainerClosePacket {
    static constexpr int Id = 47;
    v748::ContainerID container_id{};
    v2225::ContainerType container_type{};
    bool server_initiated_close{};
};

using PlayerHotbarPacket = v748::PlayerHotbarPacket;

using ContainerSetDataPacket = v748::ContainerSetDataPacket;

struct ContainerOpenPacket {
    static constexpr int Id = 46;
    v748::ContainerID container_id{};
    v2225::ContainerType type{};
    BlockPos pos{};
    ActorUniqueID entity_unique_id{};
};

struct ContainerRegistryCleanupPacket {
    static constexpr int Id = 317;
    std::vector<v2225::FullContainerName> removed_containers{};
};

using SetPlayerFurnaceOptionsPacket = v2193::SetPlayerFurnaceOptionsPacket;

struct ServerboundStonecutterSetRecipePacket {
    static constexpr int Id = 354;
    v748::ContainerID container_id{};
    std::int32_t recipe_index{};
};

struct ClientboundStonecutterSetRecipePacket {
    static constexpr int Id = 355;
    ActorUniqueID player_id{};
    v748::ContainerID container_id{};
    std::int32_t recipe_index{};
};

struct ServerboundCursorItemDragPacket {
    static constexpr int Id = 358;
    CursorItemDragState state{};
};

struct UpdateTradePacket {
    static constexpr int Id = 80;
    v748::ContainerID container_id{};
    v2225::ContainerType type{};
    std::int32_t size{};
    std::int32_t trader_tier{};
    ActorUniqueID entity_unique_id{};
    ActorUniqueID last_trading_player{};
    std::string display_name{};
    bool use_new_trade_screen{};
    bool using_economy_trade{};
    CompoundTag data{};
};

struct UpdateEquipPacket {
    static constexpr int Id = 81;
    v748::ContainerID container_id{};
    v2225::ContainerType type{};
    std::int32_t size{};
    ActorUniqueID entity_unique_id{};
    CompoundTag data{};
};

using MobEquipmentPacket = v2168::MobEquipmentPacket;

using MobArmorEquipmentPacket = v2168::MobArmorEquipmentPacket;

}  // namespace v2225

namespace detail {

template <int V>
struct ContainerID_;

template <int V> requires (V < 748)
struct ContainerID_<V> { using type = base::ContainerID; };

template <int V> requires (V >= 748)
struct ContainerID_<V> { using type = v748::ContainerID; };

template <int V>
struct ContainerEnumName_;

template <int V> requires (V < 924)
struct ContainerEnumName_<V> { using type = base::ContainerEnumName; };

template <int V> requires (V >= 924 && V < 2225)
struct ContainerEnumName_<V> { using type = v924::ContainerEnumName; };

template <int V> requires (V >= 2225)
struct ContainerEnumName_<V> { using type = v2225::ContainerEnumName; };

template <int V>
struct FullContainerName_;

template <int V> requires (V < 924)
struct FullContainerName_<V> { using type = base::FullContainerName; };

template <int V> requires (V >= 924 && V < 2225)
struct FullContainerName_<V> { using type = v924::FullContainerName; };

template <int V> requires (V >= 2225)
struct FullContainerName_<V> { using type = v2225::FullContainerName; };

template <int V>
struct InventoryContentPacket_;

template <int V> requires (V < 748)
struct InventoryContentPacket_<V> { using type = base::InventoryContentPacket; };

template <int V> requires (V >= 748 && V < 924)
struct InventoryContentPacket_<V> { using type = v748::InventoryContentPacket; };

template <int V> requires (V >= 924 && V < 1001)
struct InventoryContentPacket_<V> { using type = v924::InventoryContentPacket; };

template <int V> requires (V >= 1001 && V < 2168)
struct InventoryContentPacket_<V> { using type = v1001::InventoryContentPacket; };

template <int V> requires (V >= 2168 && V < 2225)
struct InventoryContentPacket_<V> { using type = v2168::InventoryContentPacket; };

template <int V> requires (V >= 2225)
struct InventoryContentPacket_<V> { using type = v2225::InventoryContentPacket; };

template <int V>
struct InventorySlotPacket_;

template <int V> requires (V < 748)
struct InventorySlotPacket_<V> { using type = base::InventorySlotPacket; };

template <int V> requires (V >= 748 && V < 924)
struct InventorySlotPacket_<V> { using type = v748::InventorySlotPacket; };

template <int V> requires (V >= 924 && V < 975)
struct InventorySlotPacket_<V> { using type = v924::InventorySlotPacket; };

template <int V> requires (V >= 975 && V < 2168)
struct InventorySlotPacket_<V> { using type = v975::InventorySlotPacket; };

template <int V> requires (V >= 2168 && V < 2225)
struct InventorySlotPacket_<V> { using type = v2168::InventorySlotPacket; };

template <int V> requires (V >= 2225)
struct InventorySlotPacket_<V> { using type = v2225::InventorySlotPacket; };

template <int V>
struct ContainerType_;

template <int V> requires (V < 2193)
struct ContainerType_<V> { using type = base::ContainerType; };

template <int V> requires (V >= 2193 && V < 2225)
struct ContainerType_<V> { using type = v2193::ContainerType; };

template <int V> requires (V >= 2225)
struct ContainerType_<V> { using type = v2225::ContainerType; };

template <int V>
struct ContainerClosePacket_;

template <int V> requires (V < 748)
struct ContainerClosePacket_<V> { using type = base::ContainerClosePacket; };

template <int V> requires (V >= 748 && V < 2193)
struct ContainerClosePacket_<V> { using type = v748::ContainerClosePacket; };

template <int V> requires (V >= 2193 && V < 2225)
struct ContainerClosePacket_<V> { using type = v2193::ContainerClosePacket; };

template <int V> requires (V >= 2225)
struct ContainerClosePacket_<V> { using type = v2225::ContainerClosePacket; };

template <int V>
struct PlayerHotbarPacket_;

template <int V> requires (V < 748)
struct PlayerHotbarPacket_<V> { using type = base::PlayerHotbarPacket; };

template <int V> requires (V >= 748)
struct PlayerHotbarPacket_<V> { using type = v748::PlayerHotbarPacket; };

template <int V>
struct ContainerSetDataPacket_;

template <int V> requires (V < 748)
struct ContainerSetDataPacket_<V> { using type = base::ContainerSetDataPacket; };

template <int V> requires (V >= 748)
struct ContainerSetDataPacket_<V> { using type = v748::ContainerSetDataPacket; };

template <int V>
struct ContainerOpenPacket_;

template <int V> requires (V < 748)
struct ContainerOpenPacket_<V> { using type = base::ContainerOpenPacket; };

template <int V> requires (V >= 748 && V < 944)
struct ContainerOpenPacket_<V> { using type = v748::ContainerOpenPacket; };

template <int V> requires (V >= 944 && V < 2193)
struct ContainerOpenPacket_<V> { using type = v944::ContainerOpenPacket; };

template <int V> requires (V >= 2193 && V < 2225)
struct ContainerOpenPacket_<V> { using type = v2193::ContainerOpenPacket; };

template <int V> requires (V >= 2225)
struct ContainerOpenPacket_<V> { using type = v2225::ContainerOpenPacket; };

template <int V>
struct ContainerRegistryCleanupPacket_;

template <int V> requires (V < 924)
struct ContainerRegistryCleanupPacket_<V> { using type = base::ContainerRegistryCleanupPacket; };

template <int V> requires (V >= 924 && V < 2225)
struct ContainerRegistryCleanupPacket_<V> { using type = v924::ContainerRegistryCleanupPacket; };

template <int V> requires (V >= 2225)
struct ContainerRegistryCleanupPacket_<V> { using type = v2225::ContainerRegistryCleanupPacket; };

template <int V>
struct SetPlayerFurnaceOptionsPacket_;

template <int V> requires (V >= 2193)
struct SetPlayerFurnaceOptionsPacket_<V> { using type = v2193::SetPlayerFurnaceOptionsPacket; };

template <int V>
struct ServerboundStonecutterSetRecipePacket_;

template <int V> requires (V >= 2225)
struct ServerboundStonecutterSetRecipePacket_<V> { using type = v2225::ServerboundStonecutterSetRecipePacket; };

template <int V>
struct ClientboundStonecutterSetRecipePacket_;

template <int V> requires (V >= 2225)
struct ClientboundStonecutterSetRecipePacket_<V> { using type = v2225::ClientboundStonecutterSetRecipePacket; };

template <int V>
struct ServerboundCursorItemDragPacket_;

template <int V> requires (V >= 2225)
struct ServerboundCursorItemDragPacket_<V> { using type = v2225::ServerboundCursorItemDragPacket; };

template <int V>
struct UpdateTradePacket_;

template <int V> requires (V < 748)
struct UpdateTradePacket_<V> { using type = base::UpdateTradePacket; };

template <int V> requires (V >= 748 && V < 2193)
struct UpdateTradePacket_<V> { using type = v748::UpdateTradePacket; };

template <int V> requires (V >= 2193 && V < 2225)
struct UpdateTradePacket_<V> { using type = v2193::UpdateTradePacket; };

template <int V> requires (V >= 2225)
struct UpdateTradePacket_<V> { using type = v2225::UpdateTradePacket; };

template <int V>
struct UpdateEquipPacket_;

template <int V> requires (V < 748)
struct UpdateEquipPacket_<V> { using type = base::UpdateEquipPacket; };

template <int V> requires (V >= 748 && V < 2193)
struct UpdateEquipPacket_<V> { using type = v748::UpdateEquipPacket; };

template <int V> requires (V >= 2193 && V < 2225)
struct UpdateEquipPacket_<V> { using type = v2193::UpdateEquipPacket; };

template <int V> requires (V >= 2225)
struct UpdateEquipPacket_<V> { using type = v2225::UpdateEquipPacket; };

template <int V>
struct MobEquipmentPacket_;

template <int V> requires (V < 748)
struct MobEquipmentPacket_<V> { using type = base::MobEquipmentPacket; };

template <int V> requires (V >= 748 && V < 975)
struct MobEquipmentPacket_<V> { using type = v748::MobEquipmentPacket; };

template <int V> requires (V >= 975 && V < 2168)
struct MobEquipmentPacket_<V> { using type = v975::MobEquipmentPacket; };

template <int V> requires (V >= 2168)
struct MobEquipmentPacket_<V> { using type = v2168::MobEquipmentPacket; };

template <int V>
struct MobArmorEquipmentPacket_;

template <int V> requires (V < 1001)
struct MobArmorEquipmentPacket_<V> { using type = base::MobArmorEquipmentPacket; };

template <int V> requires (V >= 1001 && V < 2168)
struct MobArmorEquipmentPacket_<V> { using type = v1001::MobArmorEquipmentPacket; };

template <int V> requires (V >= 2168)
struct MobArmorEquipmentPacket_<V> { using type = v2168::MobArmorEquipmentPacket; };

}  // namespace detail

template <int V> using ContainerID_ = typename detail::ContainerID_<V>::type;
template <int V> using ContainerEnumName_ = typename detail::ContainerEnumName_<V>::type;
template <int V> using FullContainerName_ = typename detail::FullContainerName_<V>::type;
template <int V> using InventoryContentPacket_ = typename detail::InventoryContentPacket_<V>::type;
template <int V> using InventorySlotPacket_ = typename detail::InventorySlotPacket_<V>::type;
template <int V> using ContainerType_ = typename detail::ContainerType_<V>::type;
template <int V> using ContainerClosePacket_ = typename detail::ContainerClosePacket_<V>::type;
template <int V> using PlayerHotbarPacket_ = typename detail::PlayerHotbarPacket_<V>::type;
template <int V> using ContainerSetDataPacket_ = typename detail::ContainerSetDataPacket_<V>::type;
template <int V> using ContainerOpenPacket_ = typename detail::ContainerOpenPacket_<V>::type;
template <int V> using ContainerRegistryCleanupPacket_ = typename detail::ContainerRegistryCleanupPacket_<V>::type;
template <int V> using SetPlayerFurnaceOptionsPacket_ = typename detail::SetPlayerFurnaceOptionsPacket_<V>::type;
template <int V> using ServerboundStonecutterSetRecipePacket_ = typename detail::ServerboundStonecutterSetRecipePacket_<V>::type;
template <int V> using ClientboundStonecutterSetRecipePacket_ = typename detail::ClientboundStonecutterSetRecipePacket_<V>::type;
template <int V> using ServerboundCursorItemDragPacket_ = typename detail::ServerboundCursorItemDragPacket_<V>::type;
template <int V> using UpdateTradePacket_ = typename detail::UpdateTradePacket_<V>::type;
template <int V> using UpdateEquipPacket_ = typename detail::UpdateEquipPacket_<V>::type;
template <int V> using MobEquipmentPacket_ = typename detail::MobEquipmentPacket_<V>::type;
template <int V> using MobArmorEquipmentPacket_ = typename detail::MobArmorEquipmentPacket_<V>::type;

template <int V>
struct packet_of<V, 31> { using type = MobEquipmentPacket_<V>; };

template <int V>
struct packet_of<V, 32> { using type = MobArmorEquipmentPacket_<V>; };

template <int V>
struct packet_of<V, 46> { using type = ContainerOpenPacket_<V>; };

template <int V>
struct packet_of<V, 47> { using type = ContainerClosePacket_<V>; };

template <int V>
struct packet_of<V, 48> { using type = PlayerHotbarPacket_<V>; };

template <int V>
struct packet_of<V, 49> { using type = InventoryContentPacket_<V>; };

template <int V>
struct packet_of<V, 50> { using type = InventorySlotPacket_<V>; };

template <int V>
struct packet_of<V, 51> { using type = ContainerSetDataPacket_<V>; };

template <int V>
struct packet_of<V, 54> { using type = GuiDataPickItemPacket; };

template <int V>
struct packet_of<V, 80> { using type = UpdateTradePacket_<V>; };

template <int V>
struct packet_of<V, 81> { using type = UpdateEquipPacket_<V>; };

template <int V>
struct packet_of<V, 142> { using type = CompletedUsingItemPacket; };

template <int V>
struct packet_of<V, 306> { using type = PlayerToggleCrafterSlotRequestPacket; };

template <int V>
struct packet_of<V, 307> { using type = SetPlayerInventoryOptionsPacket; };

template <int V>
struct packet_of<V, 317> { using type = ContainerRegistryCleanupPacket_<V>; };

template <int V> requires (V >= 2193)
struct packet_of<V, 351> { using type = SetPlayerFurnaceOptionsPacket_<V>; };

template <int V> requires (V >= 2225)
struct packet_of<V, 354> { using type = ServerboundStonecutterSetRecipePacket_<V>; };

template <int V> requires (V >= 2225)
struct packet_of<V, 355> { using type = ClientboundStonecutterSetRecipePacket_<V>; };

template <int V> requires (V >= 2225)
struct packet_of<V, 358> { using type = ServerboundCursorItemDragPacket_<V>; };

namespace detail {

template <>
inline constexpr std::array<base::ContainerID, 10> values_v<base::ContainerID>{{
    base::ContainerID::None,
    base::ContainerID::Inventory,
    base::ContainerID::First,
    base::ContainerID::Last,
    base::ContainerID::Offhand,
    base::ContainerID::Armor,
    base::ContainerID::SelectionSlots,
    base::ContainerID::PlayerOnlyUi,
    base::ContainerID::Registry,
    base::ContainerID::RegistryInventory,
}};

template <>
inline constexpr std::array<std::string_view, 10> names_v<base::ContainerID>{{
    "none",
    "inventory",
    "first",
    "last",
    "offhand",
    "armor",
    "selectionslots",
    "playeronlyui",
    "registry",
    "registryinventory",
}};

template <>
inline constexpr std::string_view type_name_v<base::ContainerID>{"ContainerID"};

template <>
inline constexpr std::array<v748::ContainerID, 9> values_v<v748::ContainerID>{{
    v748::ContainerID::None,
    v748::ContainerID::Inventory,
    v748::ContainerID::First,
    v748::ContainerID::Last,
    v748::ContainerID::Offhand,
    v748::ContainerID::Armor,
    v748::ContainerID::SelectionSlots,
    v748::ContainerID::PlayerOnlyUi,
    v748::ContainerID::Registry,
}};

template <>
inline constexpr std::array<std::string_view, 9> names_v<v748::ContainerID>{{
    "none",
    "inventory",
    "first",
    "last",
    "offhand",
    "armor",
    "selectionslots",
    "playeronlyui",
    "registry",
}};

template <>
inline constexpr std::string_view type_name_v<v748::ContainerID>{"ContainerID"};

template <>
inline constexpr std::array<base::ContainerEnumName, 64> values_v<base::ContainerEnumName>{{
    base::ContainerEnumName::AnvilInputContainer,
    base::ContainerEnumName::AnvilMaterialContainer,
    base::ContainerEnumName::AnvilResultPreviewContainer,
    base::ContainerEnumName::SmithingTableInputContainer,
    base::ContainerEnumName::SmithingTableMaterialContainer,
    base::ContainerEnumName::SmithingTableResultPreviewContainer,
    base::ContainerEnumName::ArmorContainer,
    base::ContainerEnumName::LevelEntityContainer,
    base::ContainerEnumName::BeaconPaymentContainer,
    base::ContainerEnumName::BrewingStandInputContainer,
    base::ContainerEnumName::BrewingStandResultContainer,
    base::ContainerEnumName::BrewingStandFuelContainer,
    base::ContainerEnumName::CombinedHotbarAndInventoryContainer,
    base::ContainerEnumName::CraftingInputContainer,
    base::ContainerEnumName::CraftingOutputPreviewContainer,
    base::ContainerEnumName::RecipeConstructionContainer,
    base::ContainerEnumName::RecipeNatureContainer,
    base::ContainerEnumName::RecipeItemsContainer,
    base::ContainerEnumName::RecipeSearchContainer,
    base::ContainerEnumName::RecipeSearchBarContainer,
    base::ContainerEnumName::RecipeEquipmentContainer,
    base::ContainerEnumName::RecipeBookContainer,
    base::ContainerEnumName::EnchantingInputContainer,
    base::ContainerEnumName::EnchantingMaterialContainer,
    base::ContainerEnumName::FurnaceFuelContainer,
    base::ContainerEnumName::FurnaceIngredientContainer,
    base::ContainerEnumName::FurnaceResultContainer,
    base::ContainerEnumName::HorseEquipContainer,
    base::ContainerEnumName::HotbarContainer,
    base::ContainerEnumName::InventoryContainer,
    base::ContainerEnumName::ShulkerBoxContainer,
    base::ContainerEnumName::TradeIngredient1Container,
    base::ContainerEnumName::TradeIngredient2Container,
    base::ContainerEnumName::TradeResultPreviewContainer,
    base::ContainerEnumName::OffhandContainer,
    base::ContainerEnumName::CompoundCreatorInput,
    base::ContainerEnumName::CompoundCreatorOutputPreview,
    base::ContainerEnumName::ElementConstructorOutputPreview,
    base::ContainerEnumName::MaterialReducerInput,
    base::ContainerEnumName::MaterialReducerOutput,
    base::ContainerEnumName::LabTableInput,
    base::ContainerEnumName::LoomInputContainer,
    base::ContainerEnumName::LoomDyeContainer,
    base::ContainerEnumName::LoomMaterialContainer,
    base::ContainerEnumName::LoomResultPreviewContainer,
    base::ContainerEnumName::BlastFurnaceIngredientContainer,
    base::ContainerEnumName::SmokerIngredientContainer,
    base::ContainerEnumName::Trade2Ingredient1Container,
    base::ContainerEnumName::Trade2Ingredient2Container,
    base::ContainerEnumName::Trade2ResultPreviewContainer,
    base::ContainerEnumName::GrindstoneInputContainer,
    base::ContainerEnumName::GrindstoneAdditionalContainer,
    base::ContainerEnumName::GrindstoneResultPreviewContainer,
    base::ContainerEnumName::StonecutterInputContainer,
    base::ContainerEnumName::StonecutterResultPreviewContainer,
    base::ContainerEnumName::CartographyInputContainer,
    base::ContainerEnumName::CartographyAdditionalContainer,
    base::ContainerEnumName::CartographyResultPreviewContainer,
    base::ContainerEnumName::BarrelContainer,
    base::ContainerEnumName::CursorContainer,
    base::ContainerEnumName::CreatedOutputContainer,
    base::ContainerEnumName::SmithingTableTemplateContainer,
    base::ContainerEnumName::CrafterLevelEntityContainer,
    base::ContainerEnumName::DynamicContainer,
}};

template <>
inline constexpr std::array<std::string_view, 64> names_v<base::ContainerEnumName>{{
    "anvilinputcontainer",
    "anvilmaterialcontainer",
    "anvilresultpreviewcontainer",
    "smithingtableinputcontainer",
    "smithingtablematerialcontainer",
    "smithingtableresultpreviewcontainer",
    "armorcontainer",
    "levelentitycontainer",
    "beaconpaymentcontainer",
    "brewingstandinputcontainer",
    "brewingstandresultcontainer",
    "brewingstandfuelcontainer",
    "combinedhotbarandinventorycontainer",
    "craftinginputcontainer",
    "craftingoutputpreviewcontainer",
    "recipeconstructioncontainer",
    "recipenaturecontainer",
    "recipeitemscontainer",
    "recipesearchcontainer",
    "recipesearchbarcontainer",
    "recipeequipmentcontainer",
    "recipebookcontainer",
    "enchantinginputcontainer",
    "enchantingmaterialcontainer",
    "furnacefuelcontainer",
    "furnaceingredientcontainer",
    "furnaceresultcontainer",
    "horseequipcontainer",
    "hotbarcontainer",
    "inventorycontainer",
    "shulkerboxcontainer",
    "tradeingredient1container",
    "tradeingredient2container",
    "traderesultpreviewcontainer",
    "offhandcontainer",
    "compoundcreatorinput",
    "compoundcreatoroutputpreview",
    "elementconstructoroutputpreview",
    "materialreducerinput",
    "materialreduceroutput",
    "labtableinput",
    "loominputcontainer",
    "loomdyecontainer",
    "loommaterialcontainer",
    "loomresultpreviewcontainer",
    "blastfurnaceingredientcontainer",
    "smokeringredientcontainer",
    "trade2ingredient1container",
    "trade2ingredient2container",
    "trade2resultpreviewcontainer",
    "grindstoneinputcontainer",
    "grindstoneadditionalcontainer",
    "grindstoneresultpreviewcontainer",
    "stonecutterinputcontainer",
    "stonecutterresultpreviewcontainer",
    "cartographyinputcontainer",
    "cartographyadditionalcontainer",
    "cartographyresultpreviewcontainer",
    "barrelcontainer",
    "cursorcontainer",
    "createdoutputcontainer",
    "smithingtabletemplatecontainer",
    "crafterlevelentitycontainer",
    "dynamiccontainer",
}};

template <>
inline constexpr std::string_view type_name_v<base::ContainerEnumName>{"ContainerEnumName"};

template <>
inline constexpr std::array<v924::ContainerEnumName, 67> values_v<v924::ContainerEnumName>{{
    v924::ContainerEnumName::AnvilInputContainer,
    v924::ContainerEnumName::AnvilMaterialContainer,
    v924::ContainerEnumName::AnvilResultPreviewContainer,
    v924::ContainerEnumName::SmithingTableInputContainer,
    v924::ContainerEnumName::SmithingTableMaterialContainer,
    v924::ContainerEnumName::SmithingTableResultPreviewContainer,
    v924::ContainerEnumName::ArmorContainer,
    v924::ContainerEnumName::LevelEntityContainer,
    v924::ContainerEnumName::BeaconPaymentContainer,
    v924::ContainerEnumName::BrewingStandInputContainer,
    v924::ContainerEnumName::BrewingStandResultContainer,
    v924::ContainerEnumName::BrewingStandFuelContainer,
    v924::ContainerEnumName::CombinedHotbarAndInventoryContainer,
    v924::ContainerEnumName::CraftingInputContainer,
    v924::ContainerEnumName::CraftingOutputPreviewContainer,
    v924::ContainerEnumName::RecipeConstructionContainer,
    v924::ContainerEnumName::RecipeNatureContainer,
    v924::ContainerEnumName::RecipeItemsContainer,
    v924::ContainerEnumName::RecipeSearchContainer,
    v924::ContainerEnumName::RecipeSearchBarContainer,
    v924::ContainerEnumName::RecipeEquipmentContainer,
    v924::ContainerEnumName::RecipeBookContainer,
    v924::ContainerEnumName::EnchantingInputContainer,
    v924::ContainerEnumName::EnchantingMaterialContainer,
    v924::ContainerEnumName::FurnaceFuelContainer,
    v924::ContainerEnumName::FurnaceIngredientContainer,
    v924::ContainerEnumName::FurnaceResultContainer,
    v924::ContainerEnumName::HorseEquipContainer,
    v924::ContainerEnumName::HotbarContainer,
    v924::ContainerEnumName::InventoryContainer,
    v924::ContainerEnumName::ShulkerBoxContainer,
    v924::ContainerEnumName::TradeIngredient1Container,
    v924::ContainerEnumName::TradeIngredient2Container,
    v924::ContainerEnumName::TradeResultPreviewContainer,
    v924::ContainerEnumName::OffhandContainer,
    v924::ContainerEnumName::CompoundCreatorInput,
    v924::ContainerEnumName::CompoundCreatorOutputPreview,
    v924::ContainerEnumName::ElementConstructorOutputPreview,
    v924::ContainerEnumName::MaterialReducerInput,
    v924::ContainerEnumName::MaterialReducerOutput,
    v924::ContainerEnumName::LabTableInput,
    v924::ContainerEnumName::LoomInputContainer,
    v924::ContainerEnumName::LoomDyeContainer,
    v924::ContainerEnumName::LoomMaterialContainer,
    v924::ContainerEnumName::LoomResultPreviewContainer,
    v924::ContainerEnumName::BlastFurnaceIngredientContainer,
    v924::ContainerEnumName::SmokerIngredientContainer,
    v924::ContainerEnumName::Trade2Ingredient1Container,
    v924::ContainerEnumName::Trade2Ingredient2Container,
    v924::ContainerEnumName::Trade2ResultPreviewContainer,
    v924::ContainerEnumName::GrindstoneInputContainer,
    v924::ContainerEnumName::GrindstoneAdditionalContainer,
    v924::ContainerEnumName::GrindstoneResultPreviewContainer,
    v924::ContainerEnumName::StonecutterInputContainer,
    v924::ContainerEnumName::StonecutterResultPreviewContainer,
    v924::ContainerEnumName::CartographyInputContainer,
    v924::ContainerEnumName::CartographyAdditionalContainer,
    v924::ContainerEnumName::CartographyResultPreviewContainer,
    v924::ContainerEnumName::BarrelContainer,
    v924::ContainerEnumName::CursorContainer,
    v924::ContainerEnumName::CreatedOutputContainer,
    v924::ContainerEnumName::SmithingTableTemplateContainer,
    v924::ContainerEnumName::CrafterLevelEntityContainer,
    v924::ContainerEnumName::DynamicContainer,
    v924::ContainerEnumName::RecipeFoodContainer,
    v924::ContainerEnumName::RecipeBlocksContainer,
    v924::ContainerEnumName::RecipeFurnaceItemsContainer,
}};

template <>
inline constexpr std::array<std::string_view, 67> names_v<v924::ContainerEnumName>{{
    "anvilinputcontainer",
    "anvilmaterialcontainer",
    "anvilresultpreviewcontainer",
    "smithingtableinputcontainer",
    "smithingtablematerialcontainer",
    "smithingtableresultpreviewcontainer",
    "armorcontainer",
    "levelentitycontainer",
    "beaconpaymentcontainer",
    "brewingstandinputcontainer",
    "brewingstandresultcontainer",
    "brewingstandfuelcontainer",
    "combinedhotbarandinventorycontainer",
    "craftinginputcontainer",
    "craftingoutputpreviewcontainer",
    "recipeconstructioncontainer",
    "recipenaturecontainer",
    "recipeitemscontainer",
    "recipesearchcontainer",
    "recipesearchbarcontainer",
    "recipeequipmentcontainer",
    "recipebookcontainer",
    "enchantinginputcontainer",
    "enchantingmaterialcontainer",
    "furnacefuelcontainer",
    "furnaceingredientcontainer",
    "furnaceresultcontainer",
    "horseequipcontainer",
    "hotbarcontainer",
    "inventorycontainer",
    "shulkerboxcontainer",
    "tradeingredient1container",
    "tradeingredient2container",
    "traderesultpreviewcontainer",
    "offhandcontainer",
    "compoundcreatorinput",
    "compoundcreatoroutputpreview",
    "elementconstructoroutputpreview",
    "materialreducerinput",
    "materialreduceroutput",
    "labtableinput",
    "loominputcontainer",
    "loomdyecontainer",
    "loommaterialcontainer",
    "loomresultpreviewcontainer",
    "blastfurnaceingredientcontainer",
    "smokeringredientcontainer",
    "trade2ingredient1container",
    "trade2ingredient2container",
    "trade2resultpreviewcontainer",
    "grindstoneinputcontainer",
    "grindstoneadditionalcontainer",
    "grindstoneresultpreviewcontainer",
    "stonecutterinputcontainer",
    "stonecutterresultpreviewcontainer",
    "cartographyinputcontainer",
    "cartographyadditionalcontainer",
    "cartographyresultpreviewcontainer",
    "barrelcontainer",
    "cursorcontainer",
    "createdoutputcontainer",
    "smithingtabletemplatecontainer",
    "crafterlevelentitycontainer",
    "dynamiccontainer",
    "recipefoodcontainer",
    "recipeblockscontainer",
    "recipefurnaceitemscontainer",
}};

template <>
inline constexpr std::string_view type_name_v<v924::ContainerEnumName>{"ContainerEnumName"};

template <>
inline constexpr std::array<v2225::ContainerEnumName, 71> values_v<v2225::ContainerEnumName>{{
    v2225::ContainerEnumName::AnvilInputContainer,
    v2225::ContainerEnumName::AnvilMaterialContainer,
    v2225::ContainerEnumName::AnvilResultPreviewContainer,
    v2225::ContainerEnumName::SmithingTableInputContainer,
    v2225::ContainerEnumName::SmithingTableMaterialContainer,
    v2225::ContainerEnumName::SmithingTableResultPreviewContainer,
    v2225::ContainerEnumName::ArmorContainer,
    v2225::ContainerEnumName::LevelEntityContainer,
    v2225::ContainerEnumName::BeaconPaymentContainer,
    v2225::ContainerEnumName::BrewingStandInputContainer,
    v2225::ContainerEnumName::BrewingStandResultContainer,
    v2225::ContainerEnumName::BrewingStandFuelContainer,
    v2225::ContainerEnumName::CombinedHotbarAndInventoryContainer,
    v2225::ContainerEnumName::CraftingInputContainer,
    v2225::ContainerEnumName::CraftingOutputPreviewContainer,
    v2225::ContainerEnumName::RecipeConstructionContainer,
    v2225::ContainerEnumName::RecipeNatureContainer,
    v2225::ContainerEnumName::RecipeItemsContainer,
    v2225::ContainerEnumName::RecipeSearchContainer,
    v2225::ContainerEnumName::RecipeSearchBarContainer,
    v2225::ContainerEnumName::RecipeEquipmentContainer,
    v2225::ContainerEnumName::RecipeBookContainer,
    v2225::ContainerEnumName::EnchantingInputContainer,
    v2225::ContainerEnumName::EnchantingMaterialContainer,
    v2225::ContainerEnumName::FurnaceFuelContainer,
    v2225::ContainerEnumName::FurnaceIngredientContainer,
    v2225::ContainerEnumName::FurnaceResultContainer,
    v2225::ContainerEnumName::HorseEquipContainer,
    v2225::ContainerEnumName::HotbarContainer,
    v2225::ContainerEnumName::InventoryContainer,
    v2225::ContainerEnumName::ShulkerBoxContainer,
    v2225::ContainerEnumName::TradeIngredient1Container,
    v2225::ContainerEnumName::TradeIngredient2Container,
    v2225::ContainerEnumName::TradeResultPreviewContainer,
    v2225::ContainerEnumName::OffhandContainer,
    v2225::ContainerEnumName::CompoundCreatorInput,
    v2225::ContainerEnumName::CompoundCreatorOutputPreview,
    v2225::ContainerEnumName::ElementConstructorOutputPreview,
    v2225::ContainerEnumName::MaterialReducerInput,
    v2225::ContainerEnumName::MaterialReducerOutput,
    v2225::ContainerEnumName::LabTableInput,
    v2225::ContainerEnumName::LoomInputContainer,
    v2225::ContainerEnumName::LoomDyeContainer,
    v2225::ContainerEnumName::LoomMaterialContainer,
    v2225::ContainerEnumName::LoomResultPreviewContainer,
    v2225::ContainerEnumName::BlastFurnaceIngredientContainer,
    v2225::ContainerEnumName::SmokerIngredientContainer,
    v2225::ContainerEnumName::Trade2Ingredient1Container,
    v2225::ContainerEnumName::Trade2Ingredient2Container,
    v2225::ContainerEnumName::Trade2ResultPreviewContainer,
    v2225::ContainerEnumName::GrindstoneInputContainer,
    v2225::ContainerEnumName::GrindstoneAdditionalContainer,
    v2225::ContainerEnumName::GrindstoneResultPreviewContainer,
    v2225::ContainerEnumName::StonecutterInputContainer,
    v2225::ContainerEnumName::StonecutterResultPreviewContainer,
    v2225::ContainerEnumName::CartographyInputContainer,
    v2225::ContainerEnumName::CartographyAdditionalContainer,
    v2225::ContainerEnumName::CartographyResultPreviewContainer,
    v2225::ContainerEnumName::BarrelContainer,
    v2225::ContainerEnumName::CursorContainer,
    v2225::ContainerEnumName::CreatedOutputContainer,
    v2225::ContainerEnumName::SmithingTableTemplateContainer,
    v2225::ContainerEnumName::CrafterLevelEntityContainer,
    v2225::ContainerEnumName::DynamicContainer,
    v2225::ContainerEnumName::ReservedContainerA,
    v2225::ContainerEnumName::ReservedContainerB,
    v2225::ContainerEnumName::ReservedContainerC,
    v2225::ContainerEnumName::ReservedContainerD,
    v2225::ContainerEnumName::RecipeFoodContainer,
    v2225::ContainerEnumName::RecipeBlocksContainer,
    v2225::ContainerEnumName::RecipeFurnaceItemsContainer,
}};

template <>
inline constexpr std::array<std::string_view, 71> names_v<v2225::ContainerEnumName>{{
    "anvilinputcontainer",
    "anvilmaterialcontainer",
    "anvilresultpreviewcontainer",
    "smithingtableinputcontainer",
    "smithingtablematerialcontainer",
    "smithingtableresultpreviewcontainer",
    "armorcontainer",
    "levelentitycontainer",
    "beaconpaymentcontainer",
    "brewingstandinputcontainer",
    "brewingstandresultcontainer",
    "brewingstandfuelcontainer",
    "combinedhotbarandinventorycontainer",
    "craftinginputcontainer",
    "craftingoutputpreviewcontainer",
    "recipeconstructioncontainer",
    "recipenaturecontainer",
    "recipeitemscontainer",
    "recipesearchcontainer",
    "recipesearchbarcontainer",
    "recipeequipmentcontainer",
    "recipebookcontainer",
    "enchantinginputcontainer",
    "enchantingmaterialcontainer",
    "furnacefuelcontainer",
    "furnaceingredientcontainer",
    "furnaceresultcontainer",
    "horseequipcontainer",
    "hotbarcontainer",
    "inventorycontainer",
    "shulkerboxcontainer",
    "tradeingredient1container",
    "tradeingredient2container",
    "traderesultpreviewcontainer",
    "offhandcontainer",
    "compoundcreatorinput",
    "compoundcreatoroutputpreview",
    "elementconstructoroutputpreview",
    "materialreducerinput",
    "materialreduceroutput",
    "labtableinput",
    "loominputcontainer",
    "loomdyecontainer",
    "loommaterialcontainer",
    "loomresultpreviewcontainer",
    "blastfurnaceingredientcontainer",
    "smokeringredientcontainer",
    "trade2ingredient1container",
    "trade2ingredient2container",
    "trade2resultpreviewcontainer",
    "grindstoneinputcontainer",
    "grindstoneadditionalcontainer",
    "grindstoneresultpreviewcontainer",
    "stonecutterinputcontainer",
    "stonecutterresultpreviewcontainer",
    "cartographyinputcontainer",
    "cartographyadditionalcontainer",
    "cartographyresultpreviewcontainer",
    "barrelcontainer",
    "cursorcontainer",
    "createdoutputcontainer",
    "smithingtabletemplatecontainer",
    "crafterlevelentitycontainer",
    "dynamiccontainer",
    "reservedcontainera",
    "reservedcontainerb",
    "reservedcontainerc",
    "reservedcontainerd",
    "recipefoodcontainer",
    "recipeblockscontainer",
    "recipefurnaceitemscontainer",
}};

template <>
inline constexpr std::string_view type_name_v<v2225::ContainerEnumName>{"ContainerEnumName"};

template <>
inline constexpr std::array<base::ContainerType, 39> values_v<base::ContainerType>{{
    base::ContainerType::None,
    base::ContainerType::Inventory,
    base::ContainerType::Container,
    base::ContainerType::Workbench,
    base::ContainerType::Furnace,
    base::ContainerType::Enchantment,
    base::ContainerType::BrewingStand,
    base::ContainerType::Anvil,
    base::ContainerType::Dispenser,
    base::ContainerType::Dropper,
    base::ContainerType::Hopper,
    base::ContainerType::Cauldron,
    base::ContainerType::MinecartChest,
    base::ContainerType::MinecartHopper,
    base::ContainerType::Horse,
    base::ContainerType::Beacon,
    base::ContainerType::StructureEditor,
    base::ContainerType::Trade,
    base::ContainerType::CommandBlock,
    base::ContainerType::Jukebox,
    base::ContainerType::Armor,
    base::ContainerType::Hand,
    base::ContainerType::CompoundCreator,
    base::ContainerType::ElementConstructor,
    base::ContainerType::MaterialReducer,
    base::ContainerType::LabTable,
    base::ContainerType::Loom,
    base::ContainerType::Lectern,
    base::ContainerType::Grindstone,
    base::ContainerType::BlastFurnace,
    base::ContainerType::Smoker,
    base::ContainerType::Stonecutter,
    base::ContainerType::Cartography,
    base::ContainerType::Hud,
    base::ContainerType::JigsawEditor,
    base::ContainerType::SmithingTable,
    base::ContainerType::ChestBoat,
    base::ContainerType::DecoratedPot,
    base::ContainerType::Crafter,
}};

template <>
inline constexpr std::array<std::string_view, 39> names_v<base::ContainerType>{{
    "none",
    "inventory",
    "container",
    "workbench",
    "furnace",
    "enchantment",
    "brewingstand",
    "anvil",
    "dispenser",
    "dropper",
    "hopper",
    "cauldron",
    "minecartchest",
    "minecarthopper",
    "horse",
    "beacon",
    "structureeditor",
    "trade",
    "commandblock",
    "jukebox",
    "armor",
    "hand",
    "compoundcreator",
    "elementconstructor",
    "materialreducer",
    "labtable",
    "loom",
    "lectern",
    "grindstone",
    "blastfurnace",
    "smoker",
    "stonecutter",
    "cartography",
    "hud",
    "jigsaweditor",
    "smithingtable",
    "chestboat",
    "decoratedpot",
    "crafter",
}};

template <>
inline constexpr std::string_view type_name_v<base::ContainerType>{"ContainerType"};

template <>
inline constexpr std::array<v2193::ContainerType, 40> values_v<v2193::ContainerType>{{
    v2193::ContainerType::None,
    v2193::ContainerType::Inventory,
    v2193::ContainerType::Container,
    v2193::ContainerType::Workbench,
    v2193::ContainerType::Furnace,
    v2193::ContainerType::Enchantment,
    v2193::ContainerType::BrewingStand,
    v2193::ContainerType::Anvil,
    v2193::ContainerType::Dispenser,
    v2193::ContainerType::Dropper,
    v2193::ContainerType::Hopper,
    v2193::ContainerType::Cauldron,
    v2193::ContainerType::MinecartChest,
    v2193::ContainerType::MinecartHopper,
    v2193::ContainerType::Horse,
    v2193::ContainerType::Beacon,
    v2193::ContainerType::StructureEditor,
    v2193::ContainerType::Trade,
    v2193::ContainerType::CommandBlock,
    v2193::ContainerType::Jukebox,
    v2193::ContainerType::Armor,
    v2193::ContainerType::Hand,
    v2193::ContainerType::CompoundCreator,
    v2193::ContainerType::ElementConstructor,
    v2193::ContainerType::MaterialReducer,
    v2193::ContainerType::LabTable,
    v2193::ContainerType::Loom,
    v2193::ContainerType::Lectern,
    v2193::ContainerType::Grindstone,
    v2193::ContainerType::BlastFurnace,
    v2193::ContainerType::Smoker,
    v2193::ContainerType::Stonecutter,
    v2193::ContainerType::Cartography,
    v2193::ContainerType::Hud,
    v2193::ContainerType::JigsawEditor,
    v2193::ContainerType::SmithingTable,
    v2193::ContainerType::ChestBoat,
    v2193::ContainerType::DecoratedPot,
    v2193::ContainerType::Crafter,
    v2193::ContainerType::DataDrivenContainer,
}};

template <>
inline constexpr std::array<std::string_view, 40> names_v<v2193::ContainerType>{{
    "none",
    "inventory",
    "container",
    "workbench",
    "furnace",
    "enchantment",
    "brewingstand",
    "anvil",
    "dispenser",
    "dropper",
    "hopper",
    "cauldron",
    "minecartchest",
    "minecarthopper",
    "horse",
    "beacon",
    "structureeditor",
    "trade",
    "commandblock",
    "jukebox",
    "armor",
    "hand",
    "compoundcreator",
    "elementconstructor",
    "materialreducer",
    "labtable",
    "loom",
    "lectern",
    "grindstone",
    "blastfurnace",
    "smoker",
    "stonecutter",
    "cartography",
    "hud",
    "jigsaweditor",
    "smithingtable",
    "chestboat",
    "decoratedpot",
    "crafter",
    "datadrivencontainer",
}};

template <>
inline constexpr std::string_view type_name_v<v2193::ContainerType>{"ContainerType"};

template <>
inline constexpr std::array<v2225::ContainerType, 41> values_v<v2225::ContainerType>{{
    v2225::ContainerType::None,
    v2225::ContainerType::Inventory,
    v2225::ContainerType::Container,
    v2225::ContainerType::Workbench,
    v2225::ContainerType::Furnace,
    v2225::ContainerType::Enchantment,
    v2225::ContainerType::BrewingStand,
    v2225::ContainerType::Anvil,
    v2225::ContainerType::Dispenser,
    v2225::ContainerType::Dropper,
    v2225::ContainerType::Hopper,
    v2225::ContainerType::Cauldron,
    v2225::ContainerType::MinecartChest,
    v2225::ContainerType::MinecartHopper,
    v2225::ContainerType::Horse,
    v2225::ContainerType::Beacon,
    v2225::ContainerType::StructureEditor,
    v2225::ContainerType::Trade,
    v2225::ContainerType::CommandBlock,
    v2225::ContainerType::Jukebox,
    v2225::ContainerType::Armor,
    v2225::ContainerType::Hand,
    v2225::ContainerType::CompoundCreator,
    v2225::ContainerType::ElementConstructor,
    v2225::ContainerType::MaterialReducer,
    v2225::ContainerType::LabTable,
    v2225::ContainerType::Loom,
    v2225::ContainerType::Lectern,
    v2225::ContainerType::Grindstone,
    v2225::ContainerType::BlastFurnace,
    v2225::ContainerType::Smoker,
    v2225::ContainerType::Stonecutter,
    v2225::ContainerType::Cartography,
    v2225::ContainerType::Hud,
    v2225::ContainerType::JigsawEditor,
    v2225::ContainerType::SmithingTable,
    v2225::ContainerType::ChestBoat,
    v2225::ContainerType::DecoratedPot,
    v2225::ContainerType::Crafter,
    v2225::ContainerType::DataDrivenContainer,
    v2225::ContainerType::ReservedContainerType,
}};

template <>
inline constexpr std::array<std::string_view, 41> names_v<v2225::ContainerType>{{
    "none",
    "inventory",
    "container",
    "workbench",
    "furnace",
    "enchantment",
    "brewingstand",
    "anvil",
    "dispenser",
    "dropper",
    "hopper",
    "cauldron",
    "minecartchest",
    "minecarthopper",
    "horse",
    "beacon",
    "structureeditor",
    "trade",
    "commandblock",
    "jukebox",
    "armor",
    "hand",
    "compoundcreator",
    "elementconstructor",
    "materialreducer",
    "labtable",
    "loom",
    "lectern",
    "grindstone",
    "blastfurnace",
    "smoker",
    "stonecutter",
    "cartography",
    "hud",
    "jigsaweditor",
    "smithingtable",
    "chestboat",
    "decoratedpot",
    "crafter",
    "datadrivencontainer",
    "reservedcontainertype",
}};

template <>
inline constexpr std::string_view type_name_v<v2225::ContainerType>{"ContainerType"};

template <>
inline constexpr std::array<InventoryLayout, 5> values_v<InventoryLayout>{{
    InventoryLayout::None,
    InventoryLayout::InventoryOnly,
    InventoryLayout::Default,
    InventoryLayout::RecipeBookOnly,
    InventoryLayout::Count,
}};

template <>
inline constexpr std::array<std::string_view, 5> names_v<InventoryLayout>{{
    "none",
    "inventoryonly",
    "default",
    "recipebookonly",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<InventoryLayout>{"InventoryLayout"};

template <>
inline constexpr std::array<InventoryLeftTabIndex, 8> values_v<InventoryLeftTabIndex>{{
    InventoryLeftTabIndex::None,
    InventoryLeftTabIndex::RecipeConstruction,
    InventoryLeftTabIndex::RecipeEquipment,
    InventoryLeftTabIndex::RecipeItems,
    InventoryLeftTabIndex::RecipeNature,
    InventoryLeftTabIndex::RecipeSearch,
    InventoryLeftTabIndex::Survival,
    InventoryLeftTabIndex::Count,
}};

template <>
inline constexpr std::array<std::string_view, 8> names_v<InventoryLeftTabIndex>{{
    "none",
    "recipeconstruction",
    "recipeequipment",
    "recipeitems",
    "recipenature",
    "recipesearch",
    "survival",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<InventoryLeftTabIndex>{"InventoryLeftTabIndex"};

template <>
inline constexpr std::array<InventoryRightTabIndex, 5> values_v<InventoryRightTabIndex>{{
    InventoryRightTabIndex::None,
    InventoryRightTabIndex::FullScreen,
    InventoryRightTabIndex::Crafting,
    InventoryRightTabIndex::Armor,
    InventoryRightTabIndex::Count,
}};

template <>
inline constexpr std::array<std::string_view, 5> names_v<InventoryRightTabIndex>{{
    "none",
    "fullscreen",
    "crafting",
    "armor",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<InventoryRightTabIndex>{"InventoryRightTabIndex"};

template <>
inline constexpr std::array<FurnaceLeftTabIndex, 7> values_v<FurnaceLeftTabIndex>{{
    FurnaceLeftTabIndex::None,
    FurnaceLeftTabIndex::RecipeFood,
    FurnaceLeftTabIndex::RecipeItems,
    FurnaceLeftTabIndex::RecipeBlocks,
    FurnaceLeftTabIndex::RecipeSearch,
    FurnaceLeftTabIndex::Inventory,
    FurnaceLeftTabIndex::Count,
}};

template <>
inline constexpr std::array<std::string_view, 7> names_v<FurnaceLeftTabIndex>{{
    "none",
    "recipefood",
    "recipeitems",
    "recipeblocks",
    "recipesearch",
    "inventory",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<FurnaceLeftTabIndex>{"FurnaceLeftTabIndex"};

template <>
inline constexpr std::array<FurnaceLayout, 4> values_v<FurnaceLayout>{{
    FurnaceLayout::None,
    FurnaceLayout::InventoryOnly,
    FurnaceLayout::Default,
    FurnaceLayout::Count,
}};

template <>
inline constexpr std::array<std::string_view, 4> names_v<FurnaceLayout>{{
    "none",
    "inventoryonly",
    "default",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<FurnaceLayout>{"FurnaceLayout"};

template <>
inline constexpr std::array<v2193::SetPlayerFurnaceOptionsPacket::FurnaceType, 5> values_v<v2193::SetPlayerFurnaceOptionsPacket::FurnaceType>{{
    v2193::SetPlayerFurnaceOptionsPacket::FurnaceType::None,
    v2193::SetPlayerFurnaceOptionsPacket::FurnaceType::Furnace,
    v2193::SetPlayerFurnaceOptionsPacket::FurnaceType::BlastFurnace,
    v2193::SetPlayerFurnaceOptionsPacket::FurnaceType::Smoker,
    v2193::SetPlayerFurnaceOptionsPacket::FurnaceType::Count,
}};

template <>
inline constexpr std::array<std::string_view, 5> names_v<v2193::SetPlayerFurnaceOptionsPacket::FurnaceType>{{
    "none",
    "furnace",
    "blastfurnace",
    "smoker",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<v2193::SetPlayerFurnaceOptionsPacket::FurnaceType>{"SetPlayerFurnaceOptionsPacket::FurnaceType"};

template <>
inline constexpr std::array<CursorItemDragState, 2> values_v<CursorItemDragState>{{
    CursorItemDragState::Start,
    CursorItemDragState::Stop,
}};

template <>
inline constexpr std::array<std::string_view, 2> names_v<CursorItemDragState>{{
    "start",
    "stop",
}};

template <>
inline constexpr std::string_view type_name_v<CursorItemDragState>{"CursorItemDragState"};

}  // namespace detail

namespace detail {

template <>
inline constexpr bool is_reflected_struct_v<base::FullContainerName> = true;

template <>
inline constexpr std::string_view struct_name_v<base::FullContainerName>{"FullContainerName"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<base::FullContainerName>{{
    "name",
    "dynamic_id",
}};

template <>
struct field_accessor<base::FullContainerName> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.name;
        }
        else {
            return value.dynamic_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::FullContainerName> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::FullContainerName>{"FullContainerName"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v924::FullContainerName>{{
    "name",
    "dynamic_id",
}};

template <>
struct field_accessor<v924::FullContainerName> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.name;
        }
        else {
            return value.dynamic_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::FullContainerName> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::FullContainerName>{"FullContainerName"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2225::FullContainerName>{{
    "name",
    "dynamic_id",
}};

template <>
struct field_accessor<v2225::FullContainerName> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.name;
        }
        else {
            return value.dynamic_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::InventoryContentPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::InventoryContentPacket>{"InventoryContentPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<base::InventoryContentPacket>{{
    "inventory_id",
    "slots",
    "full_container_name",
    "dynamic_container_size",
}};

template <>
struct field_accessor<base::InventoryContentPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.inventory_id;
        }
        else if constexpr (I == 1) {
            return value.slots;
        }
        else if constexpr (I == 2) {
            return value.full_container_name;
        }
        else {
            return value.dynamic_container_size;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v748::InventoryContentPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v748::InventoryContentPacket>{"InventoryContentPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v748::InventoryContentPacket>{{
    "inventory_id",
    "slots",
    "full_container_name",
    "storage_item",
}};

template <>
struct field_accessor<v748::InventoryContentPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.inventory_id;
        }
        else if constexpr (I == 1) {
            return value.slots;
        }
        else if constexpr (I == 2) {
            return value.full_container_name;
        }
        else {
            return value.storage_item;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::InventoryContentPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::InventoryContentPacket>{"InventoryContentPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v924::InventoryContentPacket>{{
    "inventory_id",
    "slots",
    "full_container_name",
    "storage_item",
}};

template <>
struct field_accessor<v924::InventoryContentPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.inventory_id;
        }
        else if constexpr (I == 1) {
            return value.slots;
        }
        else if constexpr (I == 2) {
            return value.full_container_name;
        }
        else {
            return value.storage_item;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::InventoryContentPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::InventoryContentPacket>{"InventoryContentPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v1001::InventoryContentPacket>{{
    "inventory_id",
    "slots",
    "full_container_name",
    "storage_item",
}};

template <>
struct field_accessor<v1001::InventoryContentPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.inventory_id;
        }
        else if constexpr (I == 1) {
            return value.slots;
        }
        else if constexpr (I == 2) {
            return value.full_container_name;
        }
        else {
            return value.storage_item;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::InventoryContentPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::InventoryContentPacket>{"InventoryContentPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v2168::InventoryContentPacket>{{
    "inventory_id",
    "slots",
    "full_container_name",
    "storage_item",
}};

template <>
struct field_accessor<v2168::InventoryContentPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.inventory_id;
        }
        else if constexpr (I == 1) {
            return value.slots;
        }
        else if constexpr (I == 2) {
            return value.full_container_name;
        }
        else {
            return value.storage_item;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::InventoryContentPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::InventoryContentPacket>{"InventoryContentPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v2225::InventoryContentPacket>{{
    "inventory_id",
    "slots",
    "full_container_name",
    "storage_item",
}};

template <>
struct field_accessor<v2225::InventoryContentPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.inventory_id;
        }
        else if constexpr (I == 1) {
            return value.slots;
        }
        else if constexpr (I == 2) {
            return value.full_container_name;
        }
        else {
            return value.storage_item;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::InventorySlotPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::InventorySlotPacket>{"InventorySlotPacket"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<base::InventorySlotPacket>{{
    "inventory_id",
    "slot",
    "full_container_name",
    "dynamic_container_size",
    "item",
}};

template <>
struct field_accessor<base::InventorySlotPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.inventory_id;
        }
        else if constexpr (I == 1) {
            return value.slot;
        }
        else if constexpr (I == 2) {
            return value.full_container_name;
        }
        else if constexpr (I == 3) {
            return value.dynamic_container_size;
        }
        else {
            return value.item;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v748::InventorySlotPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v748::InventorySlotPacket>{"InventorySlotPacket"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v748::InventorySlotPacket>{{
    "inventory_id",
    "slot",
    "full_container_name",
    "storage_item",
    "item",
}};

template <>
struct field_accessor<v748::InventorySlotPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.inventory_id;
        }
        else if constexpr (I == 1) {
            return value.slot;
        }
        else if constexpr (I == 2) {
            return value.full_container_name;
        }
        else if constexpr (I == 3) {
            return value.storage_item;
        }
        else {
            return value.item;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::InventorySlotPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::InventorySlotPacket>{"InventorySlotPacket"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v924::InventorySlotPacket>{{
    "inventory_id",
    "slot",
    "full_container_name",
    "storage_item",
    "item",
}};

template <>
struct field_accessor<v924::InventorySlotPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.inventory_id;
        }
        else if constexpr (I == 1) {
            return value.slot;
        }
        else if constexpr (I == 2) {
            return value.full_container_name;
        }
        else if constexpr (I == 3) {
            return value.storage_item;
        }
        else {
            return value.item;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v975::InventorySlotPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v975::InventorySlotPacket>{"InventorySlotPacket"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v975::InventorySlotPacket>{{
    "inventory_id",
    "slot",
    "full_container_name",
    "storage_item",
    "item",
}};

template <>
struct field_accessor<v975::InventorySlotPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.inventory_id;
        }
        else if constexpr (I == 1) {
            return value.slot;
        }
        else if constexpr (I == 2) {
            return value.full_container_name;
        }
        else if constexpr (I == 3) {
            return value.storage_item;
        }
        else {
            return value.item;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::InventorySlotPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::InventorySlotPacket>{"InventorySlotPacket"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v2168::InventorySlotPacket>{{
    "inventory_id",
    "slot",
    "full_container_name",
    "storage_item",
    "item",
}};

template <>
struct field_accessor<v2168::InventorySlotPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.inventory_id;
        }
        else if constexpr (I == 1) {
            return value.slot;
        }
        else if constexpr (I == 2) {
            return value.full_container_name;
        }
        else if constexpr (I == 3) {
            return value.storage_item;
        }
        else {
            return value.item;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::InventorySlotPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::InventorySlotPacket>{"InventorySlotPacket"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v2225::InventorySlotPacket>{{
    "inventory_id",
    "slot",
    "full_container_name",
    "storage_item",
    "item",
}};

template <>
struct field_accessor<v2225::InventorySlotPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.inventory_id;
        }
        else if constexpr (I == 1) {
            return value.slot;
        }
        else if constexpr (I == 2) {
            return value.full_container_name;
        }
        else if constexpr (I == 3) {
            return value.storage_item;
        }
        else {
            return value.item;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::ContainerClosePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ContainerClosePacket>{"ContainerClosePacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<base::ContainerClosePacket>{{
    "container_id",
    "container_type",
    "server_initiated_close",
}};

template <>
struct field_accessor<base::ContainerClosePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.container_id;
        }
        else if constexpr (I == 1) {
            return value.container_type;
        }
        else {
            return value.server_initiated_close;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v748::ContainerClosePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v748::ContainerClosePacket>{"ContainerClosePacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v748::ContainerClosePacket>{{
    "container_id",
    "container_type",
    "server_initiated_close",
}};

template <>
struct field_accessor<v748::ContainerClosePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.container_id;
        }
        else if constexpr (I == 1) {
            return value.container_type;
        }
        else {
            return value.server_initiated_close;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2193::ContainerClosePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2193::ContainerClosePacket>{"ContainerClosePacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v2193::ContainerClosePacket>{{
    "container_id",
    "container_type",
    "server_initiated_close",
}};

template <>
struct field_accessor<v2193::ContainerClosePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.container_id;
        }
        else if constexpr (I == 1) {
            return value.container_type;
        }
        else {
            return value.server_initiated_close;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::ContainerClosePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::ContainerClosePacket>{"ContainerClosePacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v2225::ContainerClosePacket>{{
    "container_id",
    "container_type",
    "server_initiated_close",
}};

template <>
struct field_accessor<v2225::ContainerClosePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.container_id;
        }
        else if constexpr (I == 1) {
            return value.container_type;
        }
        else {
            return value.server_initiated_close;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::PlayerHotbarPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::PlayerHotbarPacket>{"PlayerHotbarPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<base::PlayerHotbarPacket>{{
    "selected_slot",
    "container_id",
    "should_select_slot",
}};

template <>
struct field_accessor<base::PlayerHotbarPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.selected_slot;
        }
        else if constexpr (I == 1) {
            return value.container_id;
        }
        else {
            return value.should_select_slot;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v748::PlayerHotbarPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v748::PlayerHotbarPacket>{"PlayerHotbarPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v748::PlayerHotbarPacket>{{
    "selected_slot",
    "container_id",
    "should_select_slot",
}};

template <>
struct field_accessor<v748::PlayerHotbarPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.selected_slot;
        }
        else if constexpr (I == 1) {
            return value.container_id;
        }
        else {
            return value.should_select_slot;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::ContainerSetDataPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ContainerSetDataPacket>{"ContainerSetDataPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<base::ContainerSetDataPacket>{{
    "container_id",
    "id",
    "value",
}};

template <>
struct field_accessor<base::ContainerSetDataPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.container_id;
        }
        else if constexpr (I == 1) {
            return value.id;
        }
        else {
            return value.value;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v748::ContainerSetDataPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v748::ContainerSetDataPacket>{"ContainerSetDataPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v748::ContainerSetDataPacket>{{
    "container_id",
    "id",
    "value",
}};

template <>
struct field_accessor<v748::ContainerSetDataPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.container_id;
        }
        else if constexpr (I == 1) {
            return value.id;
        }
        else {
            return value.value;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<GuiDataPickItemPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<GuiDataPickItemPacket>{"GuiDataPickItemPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<GuiDataPickItemPacket>{{
    "item_name",
    "item_effect_name",
    "slot",
}};

template <>
struct field_accessor<GuiDataPickItemPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.item_name;
        }
        else if constexpr (I == 1) {
            return value.item_effect_name;
        }
        else {
            return value.slot;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<CompletedUsingItemPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<CompletedUsingItemPacket>{"CompletedUsingItemPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<CompletedUsingItemPacket>{{
    "item_id",
    "item_use_method",
}};

template <>
struct field_accessor<CompletedUsingItemPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.item_id;
        }
        else {
            return value.item_use_method;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<PlayerToggleCrafterSlotRequestPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<PlayerToggleCrafterSlotRequestPacket>{"PlayerToggleCrafterSlotRequestPacket"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<PlayerToggleCrafterSlotRequestPacket>{{
    "pos_x",
    "pos_y",
    "pos_z",
    "slot_index",
    "is_disabled",
}};

template <>
struct field_accessor<PlayerToggleCrafterSlotRequestPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.pos_x;
        }
        else if constexpr (I == 1) {
            return value.pos_y;
        }
        else if constexpr (I == 2) {
            return value.pos_z;
        }
        else if constexpr (I == 3) {
            return value.slot_index;
        }
        else {
            return value.is_disabled;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::ContainerOpenPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ContainerOpenPacket>{"ContainerOpenPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<base::ContainerOpenPacket>{{
    "container_id",
    "type",
    "pos",
    "entity_unique_id",
}};

template <>
struct field_accessor<base::ContainerOpenPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.container_id;
        }
        else if constexpr (I == 1) {
            return value.type;
        }
        else if constexpr (I == 2) {
            return value.pos;
        }
        else {
            return value.entity_unique_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v748::ContainerOpenPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v748::ContainerOpenPacket>{"ContainerOpenPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v748::ContainerOpenPacket>{{
    "container_id",
    "type",
    "pos",
    "entity_unique_id",
}};

template <>
struct field_accessor<v748::ContainerOpenPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.container_id;
        }
        else if constexpr (I == 1) {
            return value.type;
        }
        else if constexpr (I == 2) {
            return value.pos;
        }
        else {
            return value.entity_unique_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::ContainerOpenPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::ContainerOpenPacket>{"ContainerOpenPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v944::ContainerOpenPacket>{{
    "container_id",
    "type",
    "pos",
    "entity_unique_id",
}};

template <>
struct field_accessor<v944::ContainerOpenPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.container_id;
        }
        else if constexpr (I == 1) {
            return value.type;
        }
        else if constexpr (I == 2) {
            return value.pos;
        }
        else {
            return value.entity_unique_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2193::ContainerOpenPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2193::ContainerOpenPacket>{"ContainerOpenPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v2193::ContainerOpenPacket>{{
    "container_id",
    "type",
    "pos",
    "entity_unique_id",
}};

template <>
struct field_accessor<v2193::ContainerOpenPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.container_id;
        }
        else if constexpr (I == 1) {
            return value.type;
        }
        else if constexpr (I == 2) {
            return value.pos;
        }
        else {
            return value.entity_unique_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::ContainerOpenPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::ContainerOpenPacket>{"ContainerOpenPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v2225::ContainerOpenPacket>{{
    "container_id",
    "type",
    "pos",
    "entity_unique_id",
}};

template <>
struct field_accessor<v2225::ContainerOpenPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.container_id;
        }
        else if constexpr (I == 1) {
            return value.type;
        }
        else if constexpr (I == 2) {
            return value.pos;
        }
        else {
            return value.entity_unique_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::ContainerRegistryCleanupPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ContainerRegistryCleanupPacket>{"ContainerRegistryCleanupPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::ContainerRegistryCleanupPacket>{{
    "removed_containers",
}};

template <>
struct field_accessor<base::ContainerRegistryCleanupPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.removed_containers;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::ContainerRegistryCleanupPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::ContainerRegistryCleanupPacket>{"ContainerRegistryCleanupPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v924::ContainerRegistryCleanupPacket>{{
    "removed_containers",
}};

template <>
struct field_accessor<v924::ContainerRegistryCleanupPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.removed_containers;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::ContainerRegistryCleanupPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::ContainerRegistryCleanupPacket>{"ContainerRegistryCleanupPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2225::ContainerRegistryCleanupPacket>{{
    "removed_containers",
}};

template <>
struct field_accessor<v2225::ContainerRegistryCleanupPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.removed_containers;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<InventoryOptions> = true;

template <>
inline constexpr std::string_view struct_name_v<InventoryOptions>{"InventoryOptions"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<InventoryOptions>{{
    "left_inventory_tab",
    "right_inventory_tab",
    "filtering",
    "layout_inv",
    "layout_craft",
}};

template <>
struct field_accessor<InventoryOptions> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.left_inventory_tab;
        }
        else if constexpr (I == 1) {
            return value.right_inventory_tab;
        }
        else if constexpr (I == 2) {
            return value.filtering;
        }
        else if constexpr (I == 3) {
            return value.layout_inv;
        }
        else {
            return value.layout_craft;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<SetPlayerInventoryOptionsPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<SetPlayerInventoryOptionsPacket>{"SetPlayerInventoryOptionsPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<SetPlayerInventoryOptionsPacket>{{
    "inventory_options",
}};

template <>
struct field_accessor<SetPlayerInventoryOptionsPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.inventory_options;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<FurnaceOptions> = true;

template <>
inline constexpr std::string_view struct_name_v<FurnaceOptions>{"FurnaceOptions"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<FurnaceOptions>{{
    "left_furnace_tab",
    "filtering",
    "layout",
}};

template <>
struct field_accessor<FurnaceOptions> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.left_furnace_tab;
        }
        else if constexpr (I == 1) {
            return value.filtering;
        }
        else {
            return value.layout;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2193::SetPlayerFurnaceOptionsPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2193::SetPlayerFurnaceOptionsPacket>{"SetPlayerFurnaceOptionsPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2193::SetPlayerFurnaceOptionsPacket>{{
    "furnace_type",
    "furnace_options",
}};

template <>
struct field_accessor<v2193::SetPlayerFurnaceOptionsPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.furnace_type;
        }
        else {
            return value.furnace_options;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::ServerboundStonecutterSetRecipePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::ServerboundStonecutterSetRecipePacket>{"ServerboundStonecutterSetRecipePacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2225::ServerboundStonecutterSetRecipePacket>{{
    "container_id",
    "recipe_index",
}};

template <>
struct field_accessor<v2225::ServerboundStonecutterSetRecipePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.container_id;
        }
        else {
            return value.recipe_index;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::ClientboundStonecutterSetRecipePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::ClientboundStonecutterSetRecipePacket>{"ClientboundStonecutterSetRecipePacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v2225::ClientboundStonecutterSetRecipePacket>{{
    "player_id",
    "container_id",
    "recipe_index",
}};

template <>
struct field_accessor<v2225::ClientboundStonecutterSetRecipePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.player_id;
        }
        else if constexpr (I == 1) {
            return value.container_id;
        }
        else {
            return value.recipe_index;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::ServerboundCursorItemDragPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::ServerboundCursorItemDragPacket>{"ServerboundCursorItemDragPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2225::ServerboundCursorItemDragPacket>{{
    "state",
}};

template <>
struct field_accessor<v2225::ServerboundCursorItemDragPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.state;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::UpdateTradePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::UpdateTradePacket>{"UpdateTradePacket"};

template <>
inline constexpr std::array<std::string_view, 10> field_names_v<base::UpdateTradePacket>{{
    "container_id",
    "type",
    "size",
    "trader_tier",
    "entity_unique_id",
    "last_trading_player",
    "display_name",
    "use_new_trade_screen",
    "using_economy_trade",
    "data",
}};

template <>
struct field_accessor<base::UpdateTradePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.container_id;
        }
        else if constexpr (I == 1) {
            return value.type;
        }
        else if constexpr (I == 2) {
            return value.size;
        }
        else if constexpr (I == 3) {
            return value.trader_tier;
        }
        else if constexpr (I == 4) {
            return value.entity_unique_id;
        }
        else if constexpr (I == 5) {
            return value.last_trading_player;
        }
        else if constexpr (I == 6) {
            return value.display_name;
        }
        else if constexpr (I == 7) {
            return value.use_new_trade_screen;
        }
        else if constexpr (I == 8) {
            return value.using_economy_trade;
        }
        else {
            return value.data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v748::UpdateTradePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v748::UpdateTradePacket>{"UpdateTradePacket"};

template <>
inline constexpr std::array<std::string_view, 10> field_names_v<v748::UpdateTradePacket>{{
    "container_id",
    "type",
    "size",
    "trader_tier",
    "entity_unique_id",
    "last_trading_player",
    "display_name",
    "use_new_trade_screen",
    "using_economy_trade",
    "data",
}};

template <>
struct field_accessor<v748::UpdateTradePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.container_id;
        }
        else if constexpr (I == 1) {
            return value.type;
        }
        else if constexpr (I == 2) {
            return value.size;
        }
        else if constexpr (I == 3) {
            return value.trader_tier;
        }
        else if constexpr (I == 4) {
            return value.entity_unique_id;
        }
        else if constexpr (I == 5) {
            return value.last_trading_player;
        }
        else if constexpr (I == 6) {
            return value.display_name;
        }
        else if constexpr (I == 7) {
            return value.use_new_trade_screen;
        }
        else if constexpr (I == 8) {
            return value.using_economy_trade;
        }
        else {
            return value.data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2193::UpdateTradePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2193::UpdateTradePacket>{"UpdateTradePacket"};

template <>
inline constexpr std::array<std::string_view, 10> field_names_v<v2193::UpdateTradePacket>{{
    "container_id",
    "type",
    "size",
    "trader_tier",
    "entity_unique_id",
    "last_trading_player",
    "display_name",
    "use_new_trade_screen",
    "using_economy_trade",
    "data",
}};

template <>
struct field_accessor<v2193::UpdateTradePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.container_id;
        }
        else if constexpr (I == 1) {
            return value.type;
        }
        else if constexpr (I == 2) {
            return value.size;
        }
        else if constexpr (I == 3) {
            return value.trader_tier;
        }
        else if constexpr (I == 4) {
            return value.entity_unique_id;
        }
        else if constexpr (I == 5) {
            return value.last_trading_player;
        }
        else if constexpr (I == 6) {
            return value.display_name;
        }
        else if constexpr (I == 7) {
            return value.use_new_trade_screen;
        }
        else if constexpr (I == 8) {
            return value.using_economy_trade;
        }
        else {
            return value.data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::UpdateTradePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::UpdateTradePacket>{"UpdateTradePacket"};

template <>
inline constexpr std::array<std::string_view, 10> field_names_v<v2225::UpdateTradePacket>{{
    "container_id",
    "type",
    "size",
    "trader_tier",
    "entity_unique_id",
    "last_trading_player",
    "display_name",
    "use_new_trade_screen",
    "using_economy_trade",
    "data",
}};

template <>
struct field_accessor<v2225::UpdateTradePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.container_id;
        }
        else if constexpr (I == 1) {
            return value.type;
        }
        else if constexpr (I == 2) {
            return value.size;
        }
        else if constexpr (I == 3) {
            return value.trader_tier;
        }
        else if constexpr (I == 4) {
            return value.entity_unique_id;
        }
        else if constexpr (I == 5) {
            return value.last_trading_player;
        }
        else if constexpr (I == 6) {
            return value.display_name;
        }
        else if constexpr (I == 7) {
            return value.use_new_trade_screen;
        }
        else if constexpr (I == 8) {
            return value.using_economy_trade;
        }
        else {
            return value.data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::UpdateEquipPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::UpdateEquipPacket>{"UpdateEquipPacket"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<base::UpdateEquipPacket>{{
    "container_id",
    "type",
    "size",
    "entity_unique_id",
    "data",
}};

template <>
struct field_accessor<base::UpdateEquipPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.container_id;
        }
        else if constexpr (I == 1) {
            return value.type;
        }
        else if constexpr (I == 2) {
            return value.size;
        }
        else if constexpr (I == 3) {
            return value.entity_unique_id;
        }
        else {
            return value.data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v748::UpdateEquipPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v748::UpdateEquipPacket>{"UpdateEquipPacket"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v748::UpdateEquipPacket>{{
    "container_id",
    "type",
    "size",
    "entity_unique_id",
    "data",
}};

template <>
struct field_accessor<v748::UpdateEquipPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.container_id;
        }
        else if constexpr (I == 1) {
            return value.type;
        }
        else if constexpr (I == 2) {
            return value.size;
        }
        else if constexpr (I == 3) {
            return value.entity_unique_id;
        }
        else {
            return value.data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2193::UpdateEquipPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2193::UpdateEquipPacket>{"UpdateEquipPacket"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v2193::UpdateEquipPacket>{{
    "container_id",
    "type",
    "size",
    "entity_unique_id",
    "data",
}};

template <>
struct field_accessor<v2193::UpdateEquipPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.container_id;
        }
        else if constexpr (I == 1) {
            return value.type;
        }
        else if constexpr (I == 2) {
            return value.size;
        }
        else if constexpr (I == 3) {
            return value.entity_unique_id;
        }
        else {
            return value.data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::UpdateEquipPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::UpdateEquipPacket>{"UpdateEquipPacket"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v2225::UpdateEquipPacket>{{
    "container_id",
    "type",
    "size",
    "entity_unique_id",
    "data",
}};

template <>
struct field_accessor<v2225::UpdateEquipPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.container_id;
        }
        else if constexpr (I == 1) {
            return value.type;
        }
        else if constexpr (I == 2) {
            return value.size;
        }
        else if constexpr (I == 3) {
            return value.entity_unique_id;
        }
        else {
            return value.data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::MobEquipmentPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::MobEquipmentPacket>{"MobEquipmentPacket"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<base::MobEquipmentPacket>{{
    "runtime_id",
    "item",
    "slot",
    "selected_slot",
    "container_id",
}};

template <>
struct field_accessor<base::MobEquipmentPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.runtime_id;
        }
        else if constexpr (I == 1) {
            return value.item;
        }
        else if constexpr (I == 2) {
            return value.slot;
        }
        else if constexpr (I == 3) {
            return value.selected_slot;
        }
        else {
            return value.container_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v748::MobEquipmentPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v748::MobEquipmentPacket>{"MobEquipmentPacket"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v748::MobEquipmentPacket>{{
    "runtime_id",
    "item",
    "slot",
    "selected_slot",
    "container_id",
}};

template <>
struct field_accessor<v748::MobEquipmentPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.runtime_id;
        }
        else if constexpr (I == 1) {
            return value.item;
        }
        else if constexpr (I == 2) {
            return value.slot;
        }
        else if constexpr (I == 3) {
            return value.selected_slot;
        }
        else {
            return value.container_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v975::MobEquipmentPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v975::MobEquipmentPacket>{"MobEquipmentPacket"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v975::MobEquipmentPacket>{{
    "runtime_id",
    "item",
    "slot",
    "selected_slot",
    "container_id",
}};

template <>
struct field_accessor<v975::MobEquipmentPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.runtime_id;
        }
        else if constexpr (I == 1) {
            return value.item;
        }
        else if constexpr (I == 2) {
            return value.slot;
        }
        else if constexpr (I == 3) {
            return value.selected_slot;
        }
        else {
            return value.container_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::MobEquipmentPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::MobEquipmentPacket>{"MobEquipmentPacket"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v2168::MobEquipmentPacket>{{
    "runtime_id",
    "item",
    "slot",
    "selected_slot",
    "container_id",
}};

template <>
struct field_accessor<v2168::MobEquipmentPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.runtime_id;
        }
        else if constexpr (I == 1) {
            return value.item;
        }
        else if constexpr (I == 2) {
            return value.slot;
        }
        else if constexpr (I == 3) {
            return value.selected_slot;
        }
        else {
            return value.container_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::MobArmorEquipmentPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::MobArmorEquipmentPacket>{"MobArmorEquipmentPacket"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<base::MobArmorEquipmentPacket>{{
    "runtime_id",
    "head",
    "torso",
    "legs",
    "feet",
    "body",
}};

template <>
struct field_accessor<base::MobArmorEquipmentPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.runtime_id;
        }
        else if constexpr (I == 1) {
            return value.head;
        }
        else if constexpr (I == 2) {
            return value.torso;
        }
        else if constexpr (I == 3) {
            return value.legs;
        }
        else if constexpr (I == 4) {
            return value.feet;
        }
        else {
            return value.body;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::MobArmorEquipmentPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::MobArmorEquipmentPacket>{"MobArmorEquipmentPacket"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<v1001::MobArmorEquipmentPacket>{{
    "runtime_id",
    "head",
    "torso",
    "legs",
    "feet",
    "body",
}};

template <>
struct field_accessor<v1001::MobArmorEquipmentPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.runtime_id;
        }
        else if constexpr (I == 1) {
            return value.head;
        }
        else if constexpr (I == 2) {
            return value.torso;
        }
        else if constexpr (I == 3) {
            return value.legs;
        }
        else if constexpr (I == 4) {
            return value.feet;
        }
        else {
            return value.body;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::MobArmorEquipmentPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::MobArmorEquipmentPacket>{"MobArmorEquipmentPacket"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<v2168::MobArmorEquipmentPacket>{{
    "runtime_id",
    "head",
    "torso",
    "legs",
    "feet",
    "body",
}};

template <>
struct field_accessor<v2168::MobArmorEquipmentPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.runtime_id;
        }
        else if constexpr (I == 1) {
            return value.head;
        }
        else if constexpr (I == 2) {
            return value.torso;
        }
        else if constexpr (I == 3) {
            return value.legs;
        }
        else if constexpr (I == 4) {
            return value.feet;
        }
        else {
            return value.body;
        }
    }
};

}  // namespace detail


template <>
struct Serializer<base::FullContainerName> {
    static void serialize(BinaryWriter &stream, const base::FullContainerName &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::FullContainerName, std::error_code>;
};

template <>
struct Serializer<v924::FullContainerName> {
    static void serialize(BinaryWriter &stream, const v924::FullContainerName &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::FullContainerName, std::error_code>;
};

template <>
struct Serializer<v2225::FullContainerName> {
    static void serialize(BinaryWriter &stream, const v2225::FullContainerName &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::FullContainerName, std::error_code>;
};

template <>
struct Serializer<base::InventoryContentPacket> {
    static void serialize(BinaryWriter &stream, const base::InventoryContentPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::InventoryContentPacket, std::error_code>;
};

template <>
struct Serializer<v748::InventoryContentPacket> {
    static void serialize(BinaryWriter &stream, const v748::InventoryContentPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v748::InventoryContentPacket, std::error_code>;
};

template <>
struct Serializer<v924::InventoryContentPacket> {
    static void serialize(BinaryWriter &stream, const v924::InventoryContentPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::InventoryContentPacket, std::error_code>;
};

template <>
struct Serializer<v1001::InventoryContentPacket> {
    static void serialize(BinaryWriter &stream, const v1001::InventoryContentPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::InventoryContentPacket, std::error_code>;
};

template <>
struct Serializer<v2168::InventoryContentPacket> {
    static void serialize(BinaryWriter &stream, const v2168::InventoryContentPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::InventoryContentPacket, std::error_code>;
};

template <>
struct Serializer<v2225::InventoryContentPacket> {
    static void serialize(BinaryWriter &stream, const v2225::InventoryContentPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::InventoryContentPacket, std::error_code>;
};

template <>
struct Serializer<base::InventorySlotPacket> {
    static void serialize(BinaryWriter &stream, const base::InventorySlotPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::InventorySlotPacket, std::error_code>;
};

template <>
struct Serializer<v748::InventorySlotPacket> {
    static void serialize(BinaryWriter &stream, const v748::InventorySlotPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v748::InventorySlotPacket, std::error_code>;
};

template <>
struct Serializer<v924::InventorySlotPacket> {
    static void serialize(BinaryWriter &stream, const v924::InventorySlotPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::InventorySlotPacket, std::error_code>;
};

template <>
struct Serializer<v975::InventorySlotPacket> {
    static void serialize(BinaryWriter &stream, const v975::InventorySlotPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v975::InventorySlotPacket, std::error_code>;
};

template <>
struct Serializer<v2168::InventorySlotPacket> {
    static void serialize(BinaryWriter &stream, const v2168::InventorySlotPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::InventorySlotPacket, std::error_code>;
};

template <>
struct Serializer<v2225::InventorySlotPacket> {
    static void serialize(BinaryWriter &stream, const v2225::InventorySlotPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::InventorySlotPacket, std::error_code>;
};

template <>
struct Serializer<base::ContainerClosePacket> {
    static void serialize(BinaryWriter &stream, const base::ContainerClosePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ContainerClosePacket, std::error_code>;
};

template <>
struct Serializer<v748::ContainerClosePacket> {
    static void serialize(BinaryWriter &stream, const v748::ContainerClosePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v748::ContainerClosePacket, std::error_code>;
};

template <>
struct Serializer<v2193::ContainerClosePacket> {
    static void serialize(BinaryWriter &stream, const v2193::ContainerClosePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::ContainerClosePacket, std::error_code>;
};

template <>
struct Serializer<v2225::ContainerClosePacket> {
    static void serialize(BinaryWriter &stream, const v2225::ContainerClosePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::ContainerClosePacket, std::error_code>;
};

template <>
struct Serializer<base::PlayerHotbarPacket> {
    static void serialize(BinaryWriter &stream, const base::PlayerHotbarPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::PlayerHotbarPacket, std::error_code>;
};

template <>
struct Serializer<v748::PlayerHotbarPacket> {
    static void serialize(BinaryWriter &stream, const v748::PlayerHotbarPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v748::PlayerHotbarPacket, std::error_code>;
};

template <>
struct Serializer<base::ContainerSetDataPacket> {
    static void serialize(BinaryWriter &stream, const base::ContainerSetDataPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ContainerSetDataPacket, std::error_code>;
};

template <>
struct Serializer<v748::ContainerSetDataPacket> {
    static void serialize(BinaryWriter &stream, const v748::ContainerSetDataPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v748::ContainerSetDataPacket, std::error_code>;
};

template <>
struct Serializer<GuiDataPickItemPacket> {
    static void serialize(BinaryWriter &stream, const GuiDataPickItemPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<GuiDataPickItemPacket, std::error_code>;
};

template <>
struct Serializer<CompletedUsingItemPacket> {
    static void serialize(BinaryWriter &stream, const CompletedUsingItemPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<CompletedUsingItemPacket, std::error_code>;
};

template <>
struct Serializer<PlayerToggleCrafterSlotRequestPacket> {
    static void serialize(BinaryWriter &stream, const PlayerToggleCrafterSlotRequestPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<PlayerToggleCrafterSlotRequestPacket, std::error_code>;
};

template <>
struct Serializer<base::ContainerOpenPacket> {
    static void serialize(BinaryWriter &stream, const base::ContainerOpenPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ContainerOpenPacket, std::error_code>;
};

template <>
struct Serializer<v748::ContainerOpenPacket> {
    static void serialize(BinaryWriter &stream, const v748::ContainerOpenPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v748::ContainerOpenPacket, std::error_code>;
};

template <>
struct Serializer<v944::ContainerOpenPacket> {
    static void serialize(BinaryWriter &stream, const v944::ContainerOpenPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::ContainerOpenPacket, std::error_code>;
};

template <>
struct Serializer<v2193::ContainerOpenPacket> {
    static void serialize(BinaryWriter &stream, const v2193::ContainerOpenPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::ContainerOpenPacket, std::error_code>;
};

template <>
struct Serializer<v2225::ContainerOpenPacket> {
    static void serialize(BinaryWriter &stream, const v2225::ContainerOpenPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::ContainerOpenPacket, std::error_code>;
};

template <>
struct Serializer<base::ContainerRegistryCleanupPacket> {
    static void serialize(BinaryWriter &stream, const base::ContainerRegistryCleanupPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ContainerRegistryCleanupPacket, std::error_code>;
};

template <>
struct Serializer<v924::ContainerRegistryCleanupPacket> {
    static void serialize(BinaryWriter &stream, const v924::ContainerRegistryCleanupPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::ContainerRegistryCleanupPacket, std::error_code>;
};

template <>
struct Serializer<v2225::ContainerRegistryCleanupPacket> {
    static void serialize(BinaryWriter &stream, const v2225::ContainerRegistryCleanupPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::ContainerRegistryCleanupPacket, std::error_code>;
};

template <>
struct Serializer<InventoryOptions> {
    static void serialize(BinaryWriter &stream, const InventoryOptions &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<InventoryOptions, std::error_code>;
};

template <>
struct Serializer<SetPlayerInventoryOptionsPacket> {
    static void serialize(BinaryWriter &stream, const SetPlayerInventoryOptionsPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<SetPlayerInventoryOptionsPacket, std::error_code>;
};

template <>
struct Serializer<FurnaceOptions> {
    static void serialize(BinaryWriter &stream, const FurnaceOptions &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<FurnaceOptions, std::error_code>;
};

template <>
struct Serializer<v2193::SetPlayerFurnaceOptionsPacket> {
    static void serialize(BinaryWriter &stream, const v2193::SetPlayerFurnaceOptionsPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::SetPlayerFurnaceOptionsPacket, std::error_code>;
};

template <>
struct Serializer<v2225::ServerboundStonecutterSetRecipePacket> {
    static void serialize(BinaryWriter &stream, const v2225::ServerboundStonecutterSetRecipePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::ServerboundStonecutterSetRecipePacket, std::error_code>;
};

template <>
struct Serializer<v2225::ClientboundStonecutterSetRecipePacket> {
    static void serialize(BinaryWriter &stream, const v2225::ClientboundStonecutterSetRecipePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::ClientboundStonecutterSetRecipePacket, std::error_code>;
};

template <>
struct Serializer<v2225::ServerboundCursorItemDragPacket> {
    static void serialize(BinaryWriter &stream, const v2225::ServerboundCursorItemDragPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::ServerboundCursorItemDragPacket, std::error_code>;
};

template <>
struct Serializer<base::UpdateTradePacket> {
    static void serialize(BinaryWriter &stream, const base::UpdateTradePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::UpdateTradePacket, std::error_code>;
};

template <>
struct Serializer<v748::UpdateTradePacket> {
    static void serialize(BinaryWriter &stream, const v748::UpdateTradePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v748::UpdateTradePacket, std::error_code>;
};

template <>
struct Serializer<v2193::UpdateTradePacket> {
    static void serialize(BinaryWriter &stream, const v2193::UpdateTradePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::UpdateTradePacket, std::error_code>;
};

template <>
struct Serializer<v2225::UpdateTradePacket> {
    static void serialize(BinaryWriter &stream, const v2225::UpdateTradePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::UpdateTradePacket, std::error_code>;
};

template <>
struct Serializer<base::UpdateEquipPacket> {
    static void serialize(BinaryWriter &stream, const base::UpdateEquipPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::UpdateEquipPacket, std::error_code>;
};

template <>
struct Serializer<v748::UpdateEquipPacket> {
    static void serialize(BinaryWriter &stream, const v748::UpdateEquipPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v748::UpdateEquipPacket, std::error_code>;
};

template <>
struct Serializer<v2193::UpdateEquipPacket> {
    static void serialize(BinaryWriter &stream, const v2193::UpdateEquipPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::UpdateEquipPacket, std::error_code>;
};

template <>
struct Serializer<v2225::UpdateEquipPacket> {
    static void serialize(BinaryWriter &stream, const v2225::UpdateEquipPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::UpdateEquipPacket, std::error_code>;
};

template <>
struct Serializer<base::MobEquipmentPacket> {
    static void serialize(BinaryWriter &stream, const base::MobEquipmentPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::MobEquipmentPacket, std::error_code>;
};

template <>
struct Serializer<v748::MobEquipmentPacket> {
    static void serialize(BinaryWriter &stream, const v748::MobEquipmentPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v748::MobEquipmentPacket, std::error_code>;
};

template <>
struct Serializer<v975::MobEquipmentPacket> {
    static void serialize(BinaryWriter &stream, const v975::MobEquipmentPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v975::MobEquipmentPacket, std::error_code>;
};

template <>
struct Serializer<v2168::MobEquipmentPacket> {
    static void serialize(BinaryWriter &stream, const v2168::MobEquipmentPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::MobEquipmentPacket, std::error_code>;
};

template <>
struct Serializer<base::MobArmorEquipmentPacket> {
    static void serialize(BinaryWriter &stream, const base::MobArmorEquipmentPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::MobArmorEquipmentPacket, std::error_code>;
};

template <>
struct Serializer<v1001::MobArmorEquipmentPacket> {
    static void serialize(BinaryWriter &stream, const v1001::MobArmorEquipmentPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::MobArmorEquipmentPacket, std::error_code>;
};

template <>
struct Serializer<v2168::MobArmorEquipmentPacket> {
    static void serialize(BinaryWriter &stream, const v2168::MobArmorEquipmentPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::MobArmorEquipmentPacket, std::error_code>;
};
using ContainerID = ContainerID_<2225>;
using ContainerEnumName = ContainerEnumName_<2225>;
using FullContainerName = FullContainerName_<2225>;
using InventoryContentPacket = InventoryContentPacket_<2225>;
using InventorySlotPacket = InventorySlotPacket_<2225>;
using ContainerType = ContainerType_<2225>;
using ContainerClosePacket = ContainerClosePacket_<2225>;
using PlayerHotbarPacket = PlayerHotbarPacket_<2225>;
using ContainerSetDataPacket = ContainerSetDataPacket_<2225>;
using ContainerOpenPacket = ContainerOpenPacket_<2225>;
using ContainerRegistryCleanupPacket = ContainerRegistryCleanupPacket_<2225>;
using SetPlayerFurnaceOptionsPacket = SetPlayerFurnaceOptionsPacket_<2225>;
using ServerboundStonecutterSetRecipePacket = ServerboundStonecutterSetRecipePacket_<2225>;
using ClientboundStonecutterSetRecipePacket = ClientboundStonecutterSetRecipePacket_<2225>;
using ServerboundCursorItemDragPacket = ServerboundCursorItemDragPacket_<2225>;
using UpdateTradePacket = UpdateTradePacket_<2225>;
using UpdateEquipPacket = UpdateEquipPacket_<2225>;
using MobEquipmentPacket = MobEquipmentPacket_<2225>;
using MobArmorEquipmentPacket = MobArmorEquipmentPacket_<2225>;

}  // namespace bedrock::protocol
