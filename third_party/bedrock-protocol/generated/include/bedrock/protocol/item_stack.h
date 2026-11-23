#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <expected>
#include <optional>
#include <string>
#include <string_view>
#include <system_error>
#include <variant>
#include <vector>

#include <bedrock/protocol/detail/reflect.hpp>
#include <bedrock/protocol/enum.hpp>
#include <bedrock/protocol/packet.hpp>
#include <bedrock/protocol/serializer.hpp>
#include <bedrock/protocol/stream.hpp>

#include <bedrock/protocol/common.h>
#include <bedrock/protocol/crafting.h>
#include <bedrock/protocol/inventory.h>
#include <bedrock/protocol/item.h>
#include <bedrock/protocol/molang.h>

namespace bedrock::protocol {

enum class ItemStackNetResult : std::uint8_t {
    Success = 0,
    Error = 1,
    InvalidRequestActionType = 2,
    ActionRequestNotAllowed = 3,
    ScreenHandlerEndRequestFailed = 4,
    ItemRequestActionHandlerCommitFailed = 5,
    InvalidRequestCraftActionType = 6,
    InvalidCraftRequest = 7,
    InvalidCraftRequestScreen = 8,
    InvalidCraftResult = 9,
    InvalidCraftResultIndex = 10,
    InvalidCraftResultItem = 11,
    InvalidItemNetId = 12,
    MissingCreatedOutputContainer = 13,
    FailedToSetCreatedItemOutputSlot = 14,
    RequestAlreadyInProgress = 15,
    FailedToInitSparseContainer = 16,
    ResultTransferFailed = 17,
    ExpectedItemSlotNotFullyConsumed = 18,
    ExpectedAnywhereItemNotFullyConsumed = 19,
    ItemAlreadyConsumedFromSlot = 20,
    ConsumedTooMuchFromSlot = 21,
    MismatchSlotExpectedConsumedItem = 22,
    MismatchSlotExpectedConsumedItemNetIdVariant = 23,
    FailedToMatchExpectedSlotConsumedItem = 24,
    FailedToMatchExpectedAllowedAnywhereConsumedItem = 25,
    ConsumedItemOutOfAllowedSlotRange = 26,
    ConsumedItemNotAllowed = 27,
    PlayerNotInCreativeMode = 28,
    InvalidExperimentalRecipeRequest = 29,
    FailedToCraftCreative = 30,
    FailedToGetLevelRecipe = 31,
    FailedToFindRecipeByNetId = 32,
    MismatchedCraftingSize = 33,
    MissingInputSparseContainer = 34,
    MismatchedRecipeForInputGridItems = 35,
    EmptyCraftResults = 36,
    FailedToEnchant = 37,
    MissingInputItem = 38,
    InsufficientPlayerLevelToEnchant = 39,
    MissingMaterialItem = 40,
    MissingActor = 41,
    UnknownPrimaryEffect = 42,
    PrimaryEffectOutOfRange = 43,
    PrimaryEffectUnavailable = 44,
    SecondaryEffectOutOfRange = 45,
    SecondaryEffectUnavailable = 46,
    DstContainerEqualToCreatedOutputContainer = 47,
    DstContainerAndSlotEqualToSrcContainerAndSlot = 48,
    FailedToValidateSrcSlot = 49,
    FailedToValidateDstSlot = 50,
    InvalidAdjustedAmount = 51,
    InvalidItemSetType = 52,
    InvalidTransferAmount = 53,
    CannotSwapItem = 54,
    CannotPlaceItem = 55,
    UnhandledItemSetType = 56,
    InvalidRemovedAmount = 57,
    InvalidRegion = 58,
    CannotDropItem = 59,
    CannotDestroyItem = 60,
    InvalidSourceContainer = 61,
    ItemNotConsumed = 62,
    InvalidNumCrafts = 63,
    InvalidCraftResultStackSize = 64,
    CannotRemoveItem = 65,
    CannotConsumeItem = 66,
    ScreenStackError = 67,
};

namespace base {

enum class ItemStackRequestActionType : std::uint8_t {
    Take = 0,
    Place = 1,
    Swap = 2,
    Drop = 3,
    Destroy = 4,
    Consume = 5,
    Create = 6,
    PlaceInItemContainerDeprecated = 7,
    TakeFromItemContainerDeprecated = 8,
    ScreenLabTableCombine = 9,
    ScreenBeaconPayment = 10,
    ScreenHUDMineBlock = 11,
    CraftRecipe = 12,
    CraftRecipeAuto = 13,
    CraftCreative = 14,
    CraftRecipeOptional = 15,
    CraftRepairAndDisenchant = 16,
    CraftLoom = 17,
    CraftNonImplementedDeprecatedasktylaing = 18,
    CraftResultsDeprecatedasktylaing = 19,
};

enum class TextProcessingEventOrigin : int {
    Unknown = -1,
    ServerChatPublic = 0,
    ServerChatWhisper = 1,
    SignText = 2,
    AnvilText = 3,
    BookAndQuillText = 4,
    CommandBlockText = 5,
    BlockActorDataText = 6,
    JoinEventText = 7,
    LeaveEventText = 8,
    SlashCommandChat = 9,
    CartographyText = 10,
    KickCommand = 11,
    TitleCommand = 12,
    SummonCommand = 13,
    ServerForm = 14,
    Count = 15,
};

struct ItemStackResponseSlotInfo {
    std::uint8_t requested_slot{};
    std::uint8_t slot{};
    std::uint8_t amount{};
    ItemStackNetId item_stack_net_id{};
    std::string custom_name{};
    std::int16_t durability_correction{};
};

struct ItemStackResponseContainerInfo {
    base::FullContainerName full_container_name{};
    std::vector<base::ItemStackResponseSlotInfo> slots{};
};

struct ItemStackResponseInfo {
    ItemStackNetResult result{};
    ItemStackRequestId client_request_id{};
    std::vector<base::ItemStackResponseContainerInfo> containers{};
};

struct ItemStackResponsePacket {
    static constexpr int Id = 148;
    std::vector<base::ItemStackResponseInfo> responses{};
};

struct ItemStackRequestSlotInfo {
    base::FullContainerName full_container_name{};
    std::uint8_t slot{};
    std::int32_t net_id_variant{};
};

struct ItemStackRequestActionTake {
    std::uint8_t amount{};
    base::ItemStackRequestSlotInfo src{};
    base::ItemStackRequestSlotInfo dst{};
};

struct ItemStackRequestActionPlace {
    std::uint8_t amount{};
    base::ItemStackRequestSlotInfo src{};
    base::ItemStackRequestSlotInfo dst{};
};

struct ItemStackRequestActionSwap {
    base::ItemStackRequestSlotInfo src{};
    base::ItemStackRequestSlotInfo dst{};
};

struct ItemStackRequestActionDrop {
    std::uint8_t amount{};
    base::ItemStackRequestSlotInfo src{};
    bool randomly{};
};

struct ItemStackRequestActionDestroy {
    std::uint8_t amount{};
    base::ItemStackRequestSlotInfo src{};
};

struct ItemStackRequestActionConsume {
    std::uint8_t amount{};
    base::ItemStackRequestSlotInfo src{};
};

struct ItemStackRequestActionCreate {
    std::uint8_t results_index{};
};

struct ItemStackRequestActionLabTableCombine {
};

struct ItemStackRequestActionBeaconPayment {
    std::int32_t primary_effect_id{};
    std::int32_t secondary_effect_id{};
};

struct ItemStackRequestActionMineBlock {
    std::int32_t slot{};
    std::int32_t predicted_durability{};
    std::int32_t net_id_variant{};
};

struct ItemStackRequestActionCraftRecipe {
    RecipeNetId recipe_net_id{};
    std::uint8_t num_crafts{};
};

struct ItemStackRequestActionCraftRecipeAuto {
    RecipeNetId recipe_net_id{};
    std::uint8_t num_crafts{};
    std::uint8_t num_ingredients{};
    std::vector<base::SerializedRecipeIngredient> ingredients{};
};

struct ItemStackRequestActionCraftCreative {
    CreativeItemNetId creative_item_net_id{};
    std::uint8_t num_crafts{};
};

struct ItemStackRequestActionCraftRecipeOptional {
    RecipeNetId recipe_net_id{};
    std::int32_t filtered_string_index{};
};

struct ItemStackRequestActionCraftGrindstone {
    std::uint32_t recipe_net_id{};
    std::uint8_t num_crafts{};
    std::int32_t repair_cost{};
};

struct ItemStackRequestActionCraftLoom {
    std::string pattern_name_id{};
    std::uint8_t num_crafts{};
};

struct ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING {
};

struct ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING {
    std::vector<base::SerializedNetworkItemInstanceDescriptor> craft_results{};
    std::uint8_t num_crafts{};
};

struct ItemStackRequestData {
    ItemStackRequestId client_request_id{};
    std::vector<std::variant<base::ItemStackRequestActionTake, base::ItemStackRequestActionPlace, base::ItemStackRequestActionSwap, base::ItemStackRequestActionDrop, base::ItemStackRequestActionDestroy, base::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> actions{};
    std::vector<std::string> strings_to_filter{};
    base::TextProcessingEventOrigin strings_to_filter_origin{};
};

struct ItemStackRequestPacket {
    static constexpr int Id = 147;
    std::vector<base::ItemStackRequestData> requests{};
};

}  // namespace base

namespace v748 {

using ItemStackRequestActionType = base::ItemStackRequestActionType;

using TextProcessingEventOrigin = base::TextProcessingEventOrigin;

using ItemStackResponseSlotInfo = base::ItemStackResponseSlotInfo;

using ItemStackResponseContainerInfo = base::ItemStackResponseContainerInfo;

using ItemStackResponseInfo = base::ItemStackResponseInfo;

using ItemStackResponsePacket = base::ItemStackResponsePacket;

using ItemStackRequestSlotInfo = base::ItemStackRequestSlotInfo;

using ItemStackRequestActionTake = base::ItemStackRequestActionTake;

using ItemStackRequestActionPlace = base::ItemStackRequestActionPlace;

using ItemStackRequestActionSwap = base::ItemStackRequestActionSwap;

using ItemStackRequestActionDrop = base::ItemStackRequestActionDrop;

using ItemStackRequestActionDestroy = base::ItemStackRequestActionDestroy;

using ItemStackRequestActionConsume = base::ItemStackRequestActionConsume;

using ItemStackRequestActionCreate = base::ItemStackRequestActionCreate;

using ItemStackRequestActionLabTableCombine = base::ItemStackRequestActionLabTableCombine;

using ItemStackRequestActionBeaconPayment = base::ItemStackRequestActionBeaconPayment;

using ItemStackRequestActionMineBlock = base::ItemStackRequestActionMineBlock;

using ItemStackRequestActionCraftRecipe = base::ItemStackRequestActionCraftRecipe;

using ItemStackRequestActionCraftRecipeAuto = base::ItemStackRequestActionCraftRecipeAuto;

using ItemStackRequestActionCraftCreative = base::ItemStackRequestActionCraftCreative;

using ItemStackRequestActionCraftRecipeOptional = base::ItemStackRequestActionCraftRecipeOptional;

using ItemStackRequestActionCraftGrindstone = base::ItemStackRequestActionCraftGrindstone;

using ItemStackRequestActionCraftLoom = base::ItemStackRequestActionCraftLoom;

using ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING = base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING;

using ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING = base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING;

using ItemStackRequestData = base::ItemStackRequestData;

using ItemStackRequestPacket = base::ItemStackRequestPacket;

}  // namespace v748

namespace v766 {

using ItemStackRequestActionType = base::ItemStackRequestActionType;

using TextProcessingEventOrigin = base::TextProcessingEventOrigin;

struct RedactableString {
    std::string unredacted_string{};
    std::string redacted_string{};
};

struct ItemStackResponseSlotInfo {
    std::uint8_t requested_slot{};
    std::uint8_t slot{};
    std::uint8_t amount{};
    ItemStackNetId item_stack_net_id{};
    v766::RedactableString custom_name{};
    std::int16_t durability_correction{};
};

struct ItemStackResponseContainerInfo {
    base::FullContainerName full_container_name{};
    std::vector<v766::ItemStackResponseSlotInfo> slots{};
};

struct ItemStackResponseInfo {
    ItemStackNetResult result{};
    ItemStackRequestId client_request_id{};
    std::vector<v766::ItemStackResponseContainerInfo> containers{};
};

struct ItemStackResponsePacket {
    static constexpr int Id = 148;
    std::vector<v766::ItemStackResponseInfo> responses{};
};

using ItemStackRequestSlotInfo = base::ItemStackRequestSlotInfo;

using ItemStackRequestActionTake = base::ItemStackRequestActionTake;

using ItemStackRequestActionPlace = base::ItemStackRequestActionPlace;

using ItemStackRequestActionSwap = base::ItemStackRequestActionSwap;

using ItemStackRequestActionDrop = base::ItemStackRequestActionDrop;

using ItemStackRequestActionDestroy = base::ItemStackRequestActionDestroy;

using ItemStackRequestActionConsume = base::ItemStackRequestActionConsume;

using ItemStackRequestActionCreate = base::ItemStackRequestActionCreate;

using ItemStackRequestActionLabTableCombine = base::ItemStackRequestActionLabTableCombine;

using ItemStackRequestActionBeaconPayment = base::ItemStackRequestActionBeaconPayment;

using ItemStackRequestActionMineBlock = base::ItemStackRequestActionMineBlock;

using ItemStackRequestActionCraftRecipe = base::ItemStackRequestActionCraftRecipe;

using ItemStackRequestActionCraftRecipeAuto = base::ItemStackRequestActionCraftRecipeAuto;

using ItemStackRequestActionCraftCreative = base::ItemStackRequestActionCraftCreative;

using ItemStackRequestActionCraftRecipeOptional = base::ItemStackRequestActionCraftRecipeOptional;

using ItemStackRequestActionCraftGrindstone = base::ItemStackRequestActionCraftGrindstone;

using ItemStackRequestActionCraftLoom = base::ItemStackRequestActionCraftLoom;

using ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING = base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING;

using ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING = base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING;

using ItemStackRequestData = base::ItemStackRequestData;

using ItemStackRequestPacket = base::ItemStackRequestPacket;

}  // namespace v766

namespace v776 {

enum class ItemStackRequestActionType : std::uint8_t {
    Take = 0,
    Place = 1,
    Swap = 2,
    Drop = 3,
    Destroy = 4,
    Consume = 5,
    Create = 6,
    PlaceInItemContainerDeprecated = 7,
    TakeFromItemContainerDeprecated = 8,
    ScreenLabTableCombine = 9,
    ScreenBeaconPayment = 10,
    ScreenHUDMineBlock = 11,
    CraftRecipe = 12,
    CraftRecipeAuto = 13,
    CraftCreative = 14,
    CraftRecipeOptional = 15,
    CraftRepairAndDisenchant = 16,
    CraftLoom = 17,
    CraftNonImplementedDeprecatedasktylaing = 18,
    CraftResultsDeprecatedasktylaing = 19,
    Test = 20,
};

using TextProcessingEventOrigin = base::TextProcessingEventOrigin;

using RedactableString = v766::RedactableString;

using ItemStackResponseSlotInfo = v766::ItemStackResponseSlotInfo;

using ItemStackResponseContainerInfo = v766::ItemStackResponseContainerInfo;

using ItemStackResponseInfo = v766::ItemStackResponseInfo;

using ItemStackResponsePacket = v766::ItemStackResponsePacket;

using ItemStackRequestSlotInfo = base::ItemStackRequestSlotInfo;

using ItemStackRequestActionTake = base::ItemStackRequestActionTake;

using ItemStackRequestActionPlace = base::ItemStackRequestActionPlace;

using ItemStackRequestActionSwap = base::ItemStackRequestActionSwap;

using ItemStackRequestActionDrop = base::ItemStackRequestActionDrop;

using ItemStackRequestActionDestroy = base::ItemStackRequestActionDestroy;

using ItemStackRequestActionConsume = base::ItemStackRequestActionConsume;

using ItemStackRequestActionCreate = base::ItemStackRequestActionCreate;

using ItemStackRequestActionLabTableCombine = base::ItemStackRequestActionLabTableCombine;

using ItemStackRequestActionBeaconPayment = base::ItemStackRequestActionBeaconPayment;

using ItemStackRequestActionMineBlock = base::ItemStackRequestActionMineBlock;

using ItemStackRequestActionCraftRecipe = base::ItemStackRequestActionCraftRecipe;

using ItemStackRequestActionCraftRecipeAuto = base::ItemStackRequestActionCraftRecipeAuto;

using ItemStackRequestActionCraftCreative = base::ItemStackRequestActionCraftCreative;

using ItemStackRequestActionCraftRecipeOptional = base::ItemStackRequestActionCraftRecipeOptional;

using ItemStackRequestActionCraftGrindstone = base::ItemStackRequestActionCraftGrindstone;

using ItemStackRequestActionCraftLoom = base::ItemStackRequestActionCraftLoom;

using ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING = base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING;

using ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING = base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING;

using ItemStackRequestData = base::ItemStackRequestData;

using ItemStackRequestPacket = base::ItemStackRequestPacket;

}  // namespace v776

namespace v786 {

enum class ItemStackRequestActionType : std::uint8_t {
    Take = 0,
    Place = 1,
    Swap = 2,
    Drop = 3,
    Destroy = 4,
    Consume = 5,
    Create = 6,
    PlaceInItemContainerDeprecated = 7,
    TakeFromItemContainerDeprecated = 8,
    ScreenLabTableCombine = 9,
    ScreenBeaconPayment = 10,
    ScreenHUDMineBlock = 11,
    CraftRecipe = 12,
    CraftRecipeAuto = 13,
    CraftCreative = 14,
    CraftRecipeOptional = 15,
    CraftRepairAndDisenchant = 16,
    CraftLoom = 17,
    CraftNonImplementedDeprecatedasktylaing = 18,
    CraftResultsDeprecatedasktylaing = 19,
};

using TextProcessingEventOrigin = base::TextProcessingEventOrigin;

using RedactableString = v766::RedactableString;

using ItemStackResponseSlotInfo = v766::ItemStackResponseSlotInfo;

using ItemStackResponseContainerInfo = v766::ItemStackResponseContainerInfo;

using ItemStackResponseInfo = v766::ItemStackResponseInfo;

using ItemStackResponsePacket = v766::ItemStackResponsePacket;

using ItemStackRequestSlotInfo = base::ItemStackRequestSlotInfo;

using ItemStackRequestActionTake = base::ItemStackRequestActionTake;

using ItemStackRequestActionPlace = base::ItemStackRequestActionPlace;

using ItemStackRequestActionSwap = base::ItemStackRequestActionSwap;

using ItemStackRequestActionDrop = base::ItemStackRequestActionDrop;

using ItemStackRequestActionDestroy = base::ItemStackRequestActionDestroy;

using ItemStackRequestActionConsume = base::ItemStackRequestActionConsume;

using ItemStackRequestActionCreate = base::ItemStackRequestActionCreate;

using ItemStackRequestActionLabTableCombine = base::ItemStackRequestActionLabTableCombine;

using ItemStackRequestActionBeaconPayment = base::ItemStackRequestActionBeaconPayment;

using ItemStackRequestActionMineBlock = base::ItemStackRequestActionMineBlock;

using ItemStackRequestActionCraftRecipe = base::ItemStackRequestActionCraftRecipe;

using ItemStackRequestActionCraftRecipeAuto = base::ItemStackRequestActionCraftRecipeAuto;

using ItemStackRequestActionCraftCreative = base::ItemStackRequestActionCraftCreative;

using ItemStackRequestActionCraftRecipeOptional = base::ItemStackRequestActionCraftRecipeOptional;

using ItemStackRequestActionCraftGrindstone = base::ItemStackRequestActionCraftGrindstone;

using ItemStackRequestActionCraftLoom = base::ItemStackRequestActionCraftLoom;

using ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING = base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING;

using ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING = base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING;

using ItemStackRequestData = base::ItemStackRequestData;

using ItemStackRequestPacket = base::ItemStackRequestPacket;

}  // namespace v786

namespace v800 {

using ItemStackRequestActionType = v786::ItemStackRequestActionType;

using TextProcessingEventOrigin = base::TextProcessingEventOrigin;

using RedactableString = v766::RedactableString;

using ItemStackResponseSlotInfo = v766::ItemStackResponseSlotInfo;

using ItemStackResponseContainerInfo = v766::ItemStackResponseContainerInfo;

using ItemStackResponseInfo = v766::ItemStackResponseInfo;

using ItemStackResponsePacket = v766::ItemStackResponsePacket;

using ItemStackRequestSlotInfo = base::ItemStackRequestSlotInfo;

using ItemStackRequestActionTake = base::ItemStackRequestActionTake;

using ItemStackRequestActionPlace = base::ItemStackRequestActionPlace;

using ItemStackRequestActionSwap = base::ItemStackRequestActionSwap;

using ItemStackRequestActionDrop = base::ItemStackRequestActionDrop;

using ItemStackRequestActionDestroy = base::ItemStackRequestActionDestroy;

using ItemStackRequestActionConsume = base::ItemStackRequestActionConsume;

using ItemStackRequestActionCreate = base::ItemStackRequestActionCreate;

using ItemStackRequestActionLabTableCombine = base::ItemStackRequestActionLabTableCombine;

using ItemStackRequestActionBeaconPayment = base::ItemStackRequestActionBeaconPayment;

using ItemStackRequestActionMineBlock = base::ItemStackRequestActionMineBlock;

using ItemStackRequestActionCraftRecipe = base::ItemStackRequestActionCraftRecipe;

using ItemStackRequestActionCraftRecipeAuto = base::ItemStackRequestActionCraftRecipeAuto;

using ItemStackRequestActionCraftCreative = base::ItemStackRequestActionCraftCreative;

using ItemStackRequestActionCraftRecipeOptional = base::ItemStackRequestActionCraftRecipeOptional;

using ItemStackRequestActionCraftGrindstone = base::ItemStackRequestActionCraftGrindstone;

using ItemStackRequestActionCraftLoom = base::ItemStackRequestActionCraftLoom;

using ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING = base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING;

using ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING = base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING;

using ItemStackRequestData = base::ItemStackRequestData;

using ItemStackRequestPacket = base::ItemStackRequestPacket;

}  // namespace v800

namespace v818 {

using ItemStackRequestActionType = v786::ItemStackRequestActionType;

using TextProcessingEventOrigin = base::TextProcessingEventOrigin;

using RedactableString = v766::RedactableString;

using ItemStackResponseSlotInfo = v766::ItemStackResponseSlotInfo;

using ItemStackResponseContainerInfo = v766::ItemStackResponseContainerInfo;

using ItemStackResponseInfo = v766::ItemStackResponseInfo;

using ItemStackResponsePacket = v766::ItemStackResponsePacket;

using ItemStackRequestSlotInfo = base::ItemStackRequestSlotInfo;

using ItemStackRequestActionTake = base::ItemStackRequestActionTake;

using ItemStackRequestActionPlace = base::ItemStackRequestActionPlace;

using ItemStackRequestActionSwap = base::ItemStackRequestActionSwap;

using ItemStackRequestActionDrop = base::ItemStackRequestActionDrop;

using ItemStackRequestActionDestroy = base::ItemStackRequestActionDestroy;

using ItemStackRequestActionConsume = base::ItemStackRequestActionConsume;

using ItemStackRequestActionCreate = base::ItemStackRequestActionCreate;

using ItemStackRequestActionLabTableCombine = base::ItemStackRequestActionLabTableCombine;

using ItemStackRequestActionBeaconPayment = base::ItemStackRequestActionBeaconPayment;

using ItemStackRequestActionMineBlock = base::ItemStackRequestActionMineBlock;

using ItemStackRequestActionCraftRecipe = base::ItemStackRequestActionCraftRecipe;

using ItemStackRequestActionCraftRecipeAuto = base::ItemStackRequestActionCraftRecipeAuto;

using ItemStackRequestActionCraftCreative = base::ItemStackRequestActionCraftCreative;

using ItemStackRequestActionCraftRecipeOptional = base::ItemStackRequestActionCraftRecipeOptional;

using ItemStackRequestActionCraftGrindstone = base::ItemStackRequestActionCraftGrindstone;

using ItemStackRequestActionCraftLoom = base::ItemStackRequestActionCraftLoom;

using ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING = base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING;

using ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING = base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING;

using ItemStackRequestData = base::ItemStackRequestData;

using ItemStackRequestPacket = base::ItemStackRequestPacket;

}  // namespace v818

namespace v827 {

using ItemStackRequestActionType = v786::ItemStackRequestActionType;

using TextProcessingEventOrigin = base::TextProcessingEventOrigin;

using RedactableString = v766::RedactableString;

using ItemStackResponseSlotInfo = v766::ItemStackResponseSlotInfo;

using ItemStackResponseContainerInfo = v766::ItemStackResponseContainerInfo;

using ItemStackResponseInfo = v766::ItemStackResponseInfo;

using ItemStackResponsePacket = v766::ItemStackResponsePacket;

using ItemStackRequestSlotInfo = base::ItemStackRequestSlotInfo;

using ItemStackRequestActionTake = base::ItemStackRequestActionTake;

using ItemStackRequestActionPlace = base::ItemStackRequestActionPlace;

using ItemStackRequestActionSwap = base::ItemStackRequestActionSwap;

using ItemStackRequestActionDrop = base::ItemStackRequestActionDrop;

using ItemStackRequestActionDestroy = base::ItemStackRequestActionDestroy;

using ItemStackRequestActionConsume = base::ItemStackRequestActionConsume;

using ItemStackRequestActionCreate = base::ItemStackRequestActionCreate;

using ItemStackRequestActionLabTableCombine = base::ItemStackRequestActionLabTableCombine;

using ItemStackRequestActionBeaconPayment = base::ItemStackRequestActionBeaconPayment;

using ItemStackRequestActionMineBlock = base::ItemStackRequestActionMineBlock;

using ItemStackRequestActionCraftRecipe = base::ItemStackRequestActionCraftRecipe;

using ItemStackRequestActionCraftRecipeAuto = base::ItemStackRequestActionCraftRecipeAuto;

using ItemStackRequestActionCraftCreative = base::ItemStackRequestActionCraftCreative;

using ItemStackRequestActionCraftRecipeOptional = base::ItemStackRequestActionCraftRecipeOptional;

using ItemStackRequestActionCraftGrindstone = base::ItemStackRequestActionCraftGrindstone;

using ItemStackRequestActionCraftLoom = base::ItemStackRequestActionCraftLoom;

using ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING = base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING;

using ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING = base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING;

using ItemStackRequestData = base::ItemStackRequestData;

using ItemStackRequestPacket = base::ItemStackRequestPacket;

}  // namespace v827

namespace v844 {

using ItemStackRequestActionType = v786::ItemStackRequestActionType;

using TextProcessingEventOrigin = base::TextProcessingEventOrigin;

using RedactableString = v766::RedactableString;

using ItemStackResponseSlotInfo = v766::ItemStackResponseSlotInfo;

using ItemStackResponseContainerInfo = v766::ItemStackResponseContainerInfo;

using ItemStackResponseInfo = v766::ItemStackResponseInfo;

using ItemStackResponsePacket = v766::ItemStackResponsePacket;

using ItemStackRequestSlotInfo = base::ItemStackRequestSlotInfo;

using ItemStackRequestActionTake = base::ItemStackRequestActionTake;

using ItemStackRequestActionPlace = base::ItemStackRequestActionPlace;

using ItemStackRequestActionSwap = base::ItemStackRequestActionSwap;

using ItemStackRequestActionDrop = base::ItemStackRequestActionDrop;

using ItemStackRequestActionDestroy = base::ItemStackRequestActionDestroy;

using ItemStackRequestActionConsume = base::ItemStackRequestActionConsume;

using ItemStackRequestActionCreate = base::ItemStackRequestActionCreate;

using ItemStackRequestActionLabTableCombine = base::ItemStackRequestActionLabTableCombine;

using ItemStackRequestActionBeaconPayment = base::ItemStackRequestActionBeaconPayment;

using ItemStackRequestActionMineBlock = base::ItemStackRequestActionMineBlock;

using ItemStackRequestActionCraftRecipe = base::ItemStackRequestActionCraftRecipe;

using ItemStackRequestActionCraftRecipeAuto = base::ItemStackRequestActionCraftRecipeAuto;

using ItemStackRequestActionCraftCreative = base::ItemStackRequestActionCraftCreative;

using ItemStackRequestActionCraftRecipeOptional = base::ItemStackRequestActionCraftRecipeOptional;

using ItemStackRequestActionCraftGrindstone = base::ItemStackRequestActionCraftGrindstone;

using ItemStackRequestActionCraftLoom = base::ItemStackRequestActionCraftLoom;

using ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING = base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING;

using ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING = base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING;

using ItemStackRequestData = base::ItemStackRequestData;

using ItemStackRequestPacket = base::ItemStackRequestPacket;

}  // namespace v844

namespace v859 {

using ItemStackRequestActionType = v786::ItemStackRequestActionType;

using TextProcessingEventOrigin = base::TextProcessingEventOrigin;

using RedactableString = v766::RedactableString;

using ItemStackResponseSlotInfo = v766::ItemStackResponseSlotInfo;

using ItemStackResponseContainerInfo = v766::ItemStackResponseContainerInfo;

using ItemStackResponseInfo = v766::ItemStackResponseInfo;

using ItemStackResponsePacket = v766::ItemStackResponsePacket;

using ItemStackRequestSlotInfo = base::ItemStackRequestSlotInfo;

using ItemStackRequestActionTake = base::ItemStackRequestActionTake;

using ItemStackRequestActionPlace = base::ItemStackRequestActionPlace;

using ItemStackRequestActionSwap = base::ItemStackRequestActionSwap;

using ItemStackRequestActionDrop = base::ItemStackRequestActionDrop;

using ItemStackRequestActionDestroy = base::ItemStackRequestActionDestroy;

using ItemStackRequestActionConsume = base::ItemStackRequestActionConsume;

using ItemStackRequestActionCreate = base::ItemStackRequestActionCreate;

using ItemStackRequestActionLabTableCombine = base::ItemStackRequestActionLabTableCombine;

using ItemStackRequestActionBeaconPayment = base::ItemStackRequestActionBeaconPayment;

using ItemStackRequestActionMineBlock = base::ItemStackRequestActionMineBlock;

using ItemStackRequestActionCraftRecipe = base::ItemStackRequestActionCraftRecipe;

using ItemStackRequestActionCraftRecipeAuto = base::ItemStackRequestActionCraftRecipeAuto;

using ItemStackRequestActionCraftCreative = base::ItemStackRequestActionCraftCreative;

using ItemStackRequestActionCraftRecipeOptional = base::ItemStackRequestActionCraftRecipeOptional;

using ItemStackRequestActionCraftGrindstone = base::ItemStackRequestActionCraftGrindstone;

using ItemStackRequestActionCraftLoom = base::ItemStackRequestActionCraftLoom;

using ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING = base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING;

using ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING = base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING;

using ItemStackRequestData = base::ItemStackRequestData;

using ItemStackRequestPacket = base::ItemStackRequestPacket;

}  // namespace v859

namespace v898 {

using ItemStackRequestActionType = v786::ItemStackRequestActionType;

using TextProcessingEventOrigin = base::TextProcessingEventOrigin;

using RedactableString = v766::RedactableString;

using ItemStackResponseSlotInfo = v766::ItemStackResponseSlotInfo;

using ItemStackResponseContainerInfo = v766::ItemStackResponseContainerInfo;

using ItemStackResponseInfo = v766::ItemStackResponseInfo;

using ItemStackResponsePacket = v766::ItemStackResponsePacket;

using ItemStackRequestSlotInfo = base::ItemStackRequestSlotInfo;

using ItemStackRequestActionTake = base::ItemStackRequestActionTake;

using ItemStackRequestActionPlace = base::ItemStackRequestActionPlace;

using ItemStackRequestActionSwap = base::ItemStackRequestActionSwap;

using ItemStackRequestActionDrop = base::ItemStackRequestActionDrop;

using ItemStackRequestActionDestroy = base::ItemStackRequestActionDestroy;

using ItemStackRequestActionConsume = base::ItemStackRequestActionConsume;

using ItemStackRequestActionCreate = base::ItemStackRequestActionCreate;

using ItemStackRequestActionLabTableCombine = base::ItemStackRequestActionLabTableCombine;

using ItemStackRequestActionBeaconPayment = base::ItemStackRequestActionBeaconPayment;

using ItemStackRequestActionMineBlock = base::ItemStackRequestActionMineBlock;

using ItemStackRequestActionCraftRecipe = base::ItemStackRequestActionCraftRecipe;

using ItemStackRequestActionCraftRecipeAuto = base::ItemStackRequestActionCraftRecipeAuto;

using ItemStackRequestActionCraftCreative = base::ItemStackRequestActionCraftCreative;

using ItemStackRequestActionCraftRecipeOptional = base::ItemStackRequestActionCraftRecipeOptional;

using ItemStackRequestActionCraftGrindstone = base::ItemStackRequestActionCraftGrindstone;

using ItemStackRequestActionCraftLoom = base::ItemStackRequestActionCraftLoom;

using ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING = base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING;

using ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING = base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING;

using ItemStackRequestData = base::ItemStackRequestData;

using ItemStackRequestPacket = base::ItemStackRequestPacket;

}  // namespace v898

namespace v924 {

using ItemStackRequestActionType = v786::ItemStackRequestActionType;

using TextProcessingEventOrigin = base::TextProcessingEventOrigin;

using RedactableString = v766::RedactableString;

using ItemStackResponseSlotInfo = v766::ItemStackResponseSlotInfo;

struct ItemStackResponseContainerInfo {
    v924::FullContainerName full_container_name{};
    std::vector<v766::ItemStackResponseSlotInfo> slots{};
};

struct ItemStackResponseInfo {
    ItemStackNetResult result{};
    ItemStackRequestId client_request_id{};
    std::vector<v924::ItemStackResponseContainerInfo> containers{};
};

struct ItemStackResponsePacket {
    static constexpr int Id = 148;
    std::vector<v924::ItemStackResponseInfo> responses{};
};

struct ItemStackRequestSlotInfo {
    v924::FullContainerName full_container_name{};
    std::uint8_t slot{};
    std::int32_t net_id_variant{};
};

struct ItemStackRequestActionTake {
    std::uint8_t amount{};
    v924::ItemStackRequestSlotInfo src{};
    v924::ItemStackRequestSlotInfo dst{};
};

struct ItemStackRequestActionPlace {
    std::uint8_t amount{};
    v924::ItemStackRequestSlotInfo src{};
    v924::ItemStackRequestSlotInfo dst{};
};

struct ItemStackRequestActionSwap {
    v924::ItemStackRequestSlotInfo src{};
    v924::ItemStackRequestSlotInfo dst{};
};

struct ItemStackRequestActionDrop {
    std::uint8_t amount{};
    v924::ItemStackRequestSlotInfo src{};
    bool randomly{};
};

struct ItemStackRequestActionDestroy {
    std::uint8_t amount{};
    v924::ItemStackRequestSlotInfo src{};
};

struct ItemStackRequestActionConsume {
    std::uint8_t amount{};
    v924::ItemStackRequestSlotInfo src{};
};

using ItemStackRequestActionCreate = base::ItemStackRequestActionCreate;

using ItemStackRequestActionLabTableCombine = base::ItemStackRequestActionLabTableCombine;

using ItemStackRequestActionBeaconPayment = base::ItemStackRequestActionBeaconPayment;

using ItemStackRequestActionMineBlock = base::ItemStackRequestActionMineBlock;

using ItemStackRequestActionCraftRecipe = base::ItemStackRequestActionCraftRecipe;

using ItemStackRequestActionCraftRecipeAuto = base::ItemStackRequestActionCraftRecipeAuto;

using ItemStackRequestActionCraftCreative = base::ItemStackRequestActionCraftCreative;

using ItemStackRequestActionCraftRecipeOptional = base::ItemStackRequestActionCraftRecipeOptional;

using ItemStackRequestActionCraftGrindstone = base::ItemStackRequestActionCraftGrindstone;

using ItemStackRequestActionCraftLoom = base::ItemStackRequestActionCraftLoom;

using ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING = base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING;

using ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING = base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING;

struct ItemStackRequestData {
    ItemStackRequestId client_request_id{};
    std::vector<std::variant<v924::ItemStackRequestActionTake, v924::ItemStackRequestActionPlace, v924::ItemStackRequestActionSwap, v924::ItemStackRequestActionDrop, v924::ItemStackRequestActionDestroy, v924::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> actions{};
    std::vector<std::string> strings_to_filter{};
    base::TextProcessingEventOrigin strings_to_filter_origin{};
};

struct ItemStackRequestPacket {
    static constexpr int Id = 147;
    std::vector<v924::ItemStackRequestData> requests{};
};

}  // namespace v924

namespace v944 {

using ItemStackRequestActionType = v786::ItemStackRequestActionType;

using TextProcessingEventOrigin = base::TextProcessingEventOrigin;

using RedactableString = v766::RedactableString;

using ItemStackResponseSlotInfo = v766::ItemStackResponseSlotInfo;

using ItemStackResponseContainerInfo = v924::ItemStackResponseContainerInfo;

using ItemStackResponseInfo = v924::ItemStackResponseInfo;

using ItemStackResponsePacket = v924::ItemStackResponsePacket;

using ItemStackRequestSlotInfo = v924::ItemStackRequestSlotInfo;

using ItemStackRequestActionTake = v924::ItemStackRequestActionTake;

using ItemStackRequestActionPlace = v924::ItemStackRequestActionPlace;

using ItemStackRequestActionSwap = v924::ItemStackRequestActionSwap;

using ItemStackRequestActionDrop = v924::ItemStackRequestActionDrop;

using ItemStackRequestActionDestroy = v924::ItemStackRequestActionDestroy;

using ItemStackRequestActionConsume = v924::ItemStackRequestActionConsume;

using ItemStackRequestActionCreate = base::ItemStackRequestActionCreate;

using ItemStackRequestActionLabTableCombine = base::ItemStackRequestActionLabTableCombine;

using ItemStackRequestActionBeaconPayment = base::ItemStackRequestActionBeaconPayment;

using ItemStackRequestActionMineBlock = base::ItemStackRequestActionMineBlock;

using ItemStackRequestActionCraftRecipe = base::ItemStackRequestActionCraftRecipe;

using ItemStackRequestActionCraftRecipeAuto = base::ItemStackRequestActionCraftRecipeAuto;

using ItemStackRequestActionCraftCreative = base::ItemStackRequestActionCraftCreative;

using ItemStackRequestActionCraftRecipeOptional = base::ItemStackRequestActionCraftRecipeOptional;

using ItemStackRequestActionCraftGrindstone = base::ItemStackRequestActionCraftGrindstone;

using ItemStackRequestActionCraftLoom = base::ItemStackRequestActionCraftLoom;

using ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING = base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING;

using ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING = base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING;

using ItemStackRequestData = v924::ItemStackRequestData;

using ItemStackRequestPacket = v924::ItemStackRequestPacket;

}  // namespace v944

namespace v975 {

using ItemStackRequestActionType = v786::ItemStackRequestActionType;

enum class TextProcessingEventOrigin : int {
    Unknown = -1,
    ServerChatPublic = 0,
    ServerChatWhisper = 1,
    SignText = 2,
    AnvilText = 3,
    BookAndQuillText = 4,
    CommandBlockText = 5,
    BlockActorDataText = 6,
    JoinEventText = 7,
    LeaveEventText = 8,
    SlashCommandChat = 9,
    CartographyText = 10,
    KickCommand = 11,
    TitleCommand = 12,
    SummonCommand = 13,
    ServerForm = 14,
    DataDrivenUI = 15,
    Count = 16,
};

using RedactableString = v766::RedactableString;

using ItemStackResponseSlotInfo = v766::ItemStackResponseSlotInfo;

using ItemStackResponseContainerInfo = v924::ItemStackResponseContainerInfo;

using ItemStackResponseInfo = v924::ItemStackResponseInfo;

using ItemStackResponsePacket = v924::ItemStackResponsePacket;

using ItemStackRequestSlotInfo = v924::ItemStackRequestSlotInfo;

using ItemStackRequestActionTake = v924::ItemStackRequestActionTake;

using ItemStackRequestActionPlace = v924::ItemStackRequestActionPlace;

using ItemStackRequestActionSwap = v924::ItemStackRequestActionSwap;

using ItemStackRequestActionDrop = v924::ItemStackRequestActionDrop;

using ItemStackRequestActionDestroy = v924::ItemStackRequestActionDestroy;

using ItemStackRequestActionConsume = v924::ItemStackRequestActionConsume;

using ItemStackRequestActionCreate = base::ItemStackRequestActionCreate;

using ItemStackRequestActionLabTableCombine = base::ItemStackRequestActionLabTableCombine;

using ItemStackRequestActionBeaconPayment = base::ItemStackRequestActionBeaconPayment;

using ItemStackRequestActionMineBlock = base::ItemStackRequestActionMineBlock;

using ItemStackRequestActionCraftRecipe = base::ItemStackRequestActionCraftRecipe;

using ItemStackRequestActionCraftRecipeAuto = base::ItemStackRequestActionCraftRecipeAuto;

using ItemStackRequestActionCraftCreative = base::ItemStackRequestActionCraftCreative;

using ItemStackRequestActionCraftRecipeOptional = base::ItemStackRequestActionCraftRecipeOptional;

using ItemStackRequestActionCraftGrindstone = base::ItemStackRequestActionCraftGrindstone;

using ItemStackRequestActionCraftLoom = base::ItemStackRequestActionCraftLoom;

using ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING = base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING;

using ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING = base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING;

struct ItemStackRequestData {
    ItemStackRequestId client_request_id{};
    std::vector<std::variant<v924::ItemStackRequestActionTake, v924::ItemStackRequestActionPlace, v924::ItemStackRequestActionSwap, v924::ItemStackRequestActionDrop, v924::ItemStackRequestActionDestroy, v924::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> actions{};
    std::vector<std::string> strings_to_filter{};
    v975::TextProcessingEventOrigin strings_to_filter_origin{};
};

struct ItemStackRequestPacket {
    static constexpr int Id = 147;
    std::vector<v975::ItemStackRequestData> requests{};
};

}  // namespace v975

namespace v1001 {

using ItemStackRequestActionType = v786::ItemStackRequestActionType;

using TextProcessingEventOrigin = v975::TextProcessingEventOrigin;

using RedactableString = v766::RedactableString;

using ItemStackResponseSlotInfo = v766::ItemStackResponseSlotInfo;

using ItemStackResponseContainerInfo = v924::ItemStackResponseContainerInfo;

using ItemStackResponseInfo = v924::ItemStackResponseInfo;

using ItemStackResponsePacket = v924::ItemStackResponsePacket;

using ItemStackRequestSlotInfo = v924::ItemStackRequestSlotInfo;

using ItemStackRequestActionTake = v924::ItemStackRequestActionTake;

using ItemStackRequestActionPlace = v924::ItemStackRequestActionPlace;

using ItemStackRequestActionSwap = v924::ItemStackRequestActionSwap;

using ItemStackRequestActionDrop = v924::ItemStackRequestActionDrop;

using ItemStackRequestActionDestroy = v924::ItemStackRequestActionDestroy;

using ItemStackRequestActionConsume = v924::ItemStackRequestActionConsume;

using ItemStackRequestActionCreate = base::ItemStackRequestActionCreate;

using ItemStackRequestActionLabTableCombine = base::ItemStackRequestActionLabTableCombine;

using ItemStackRequestActionBeaconPayment = base::ItemStackRequestActionBeaconPayment;

using ItemStackRequestActionMineBlock = base::ItemStackRequestActionMineBlock;

using ItemStackRequestActionCraftRecipe = base::ItemStackRequestActionCraftRecipe;

using ItemStackRequestActionCraftRecipeAuto = base::ItemStackRequestActionCraftRecipeAuto;

using ItemStackRequestActionCraftCreative = base::ItemStackRequestActionCraftCreative;

using ItemStackRequestActionCraftRecipeOptional = base::ItemStackRequestActionCraftRecipeOptional;

using ItemStackRequestActionCraftGrindstone = base::ItemStackRequestActionCraftGrindstone;

using ItemStackRequestActionCraftLoom = base::ItemStackRequestActionCraftLoom;

using ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING = base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING;

using ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING = base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING;

using ItemStackRequestData = v975::ItemStackRequestData;

using ItemStackRequestPacket = v975::ItemStackRequestPacket;

}  // namespace v1001

namespace v2168 {

using ItemStackRequestActionType = v786::ItemStackRequestActionType;

using TextProcessingEventOrigin = v975::TextProcessingEventOrigin;

struct RedactableString {
    std::string unredacted_string{};
    std::optional<std::string> redacted_string{};
};

struct ItemStackResponseSlotInfo {
    std::uint8_t requested_slot{};
    std::uint8_t slot{};
    std::uint8_t amount{};
    std::optional<ItemStackNetId> item_stack_net_id{};
    v2168::RedactableString custom_name{};
    std::int16_t durability_correction{};
};

struct ItemStackResponseContainerInfo {
    v924::FullContainerName full_container_name{};
    std::vector<v2168::ItemStackResponseSlotInfo> slots{};
};

struct ItemStackResponseInfo {
    ItemStackNetResult result{};
    ItemStackRequestId client_request_id{};
    std::optional<std::vector<v2168::ItemStackResponseContainerInfo>> containers{};
};

struct ItemStackResponsePacket {
    static constexpr int Id = 148;
    std::vector<v2168::ItemStackResponseInfo> responses{};
};

namespace ItemStackRequestCereal_nested {

enum class ItemDescriptorType : std::uint8_t {
    Empty = 0,
    ItemName = 1,
    Molang = 2,
    ItemTag = 3,
};

struct EmptyItemDescriptorData {
};

struct ItemNameDescriptorData {
    std::string full_name{};
    std::int32_t aux_value{};
};

struct MolangItemDescriptorData {
    std::string tag_expression{};
    v827::MolangVersion molang_version{};
};

struct ItemTagDescriptorData {
    std::string item_tag{};
};

struct NetworkItemInstanceDescriptorData {
    std::variant<EmptyItemDescriptorData, ItemNameDescriptorData, MolangItemDescriptorData, ItemTagDescriptorData> item_descriptor{};
    std::uint16_t stack_size{};
    BlockRuntimeId block_runtime_id{};
    std::string user_data_buffer{};
};

struct RecipeIngredientData {
    std::variant<EmptyItemDescriptorData, ItemNameDescriptorData, MolangItemDescriptorData, ItemTagDescriptorData> item_descriptor{};
    std::uint16_t stack_size{};
};

struct SlotInfoData {
    v924::FullContainerName full_container_name{};
    std::uint8_t slot{};
    std::int32_t net_id_variant{};
};

struct TakeActionData {
    std::uint8_t amount{};
    SlotInfoData source{};
    SlotInfoData destination{};
};

struct PlaceActionData {
    std::uint8_t amount{};
    SlotInfoData source{};
    SlotInfoData destination{};
};

struct SwapActionData {
    SlotInfoData source{};
    SlotInfoData destination{};
};

struct DropActionData {
    std::uint8_t amount{};
    SlotInfoData source{};
    bool randomly{};
};

struct DestroyActionData {
    std::uint8_t amount{};
    SlotInfoData source{};
};

struct ConsumeActionData {
    std::uint8_t amount{};
    SlotInfoData source{};
};

struct CreateActionData {
    std::uint8_t results_index{};
};

struct LabTableCombineActionData {
};

struct BeaconPaymentActionData {
    std::int32_t primary_effect_id{};
    std::int32_t secondary_effect_id{};
};

struct MineBlockActionData {
    std::int32_t slot{};
    std::int32_t predicted_durability{};
    std::int32_t net_id_variant{};
};

struct CraftRecipeActionData {
    RecipeNetId recipe_net_id{};
    std::uint8_t num_crafts{};
};

struct CraftRecipeAutoActionData {
    RecipeNetId recipe_net_id{};
    std::uint8_t num_crafts{};
    std::vector<RecipeIngredientData> ingredients{};
};

struct CraftCreativeActionData {
    std::uint32_t creative_item_net_id{};
    std::uint8_t num_crafts{};
};

struct CraftRecipeOptionalActionData {
    RecipeNetId recipe_net_id{};
    std::int32_t filtered_string_index{};
};

struct CraftRepairAndDisenchantActionData {
    std::int32_t recipe_net_id{};
    std::uint8_t num_crafts{};
    std::int32_t repair_cost{};
};

struct CraftLoomActionData {
    std::string pattern_name_id{};
    std::uint8_t num_crafts{};
};

struct CraftNonImplementedActionData {
};

struct CraftResultsActionData {
    std::vector<NetworkItemInstanceDescriptorData> craft_results{};
    std::uint8_t num_crafts{};
};

struct RequestData {
    ItemStackRequestId client_request_id{};
    std::vector<std::variant<TakeActionData, PlaceActionData, SwapActionData, DropActionData, DestroyActionData, ConsumeActionData, CreateActionData, LabTableCombineActionData, BeaconPaymentActionData, MineBlockActionData, CraftRecipeActionData, CraftRecipeAutoActionData, CraftCreativeActionData, CraftRecipeOptionalActionData, CraftRepairAndDisenchantActionData, CraftLoomActionData, CraftNonImplementedActionData, CraftResultsActionData>> actions{};
    std::vector<std::string> strings_to_filter{};
    v975::TextProcessingEventOrigin strings_to_filter_origin{};
};

}  // namespace ItemStackRequestCereal_nested

struct ItemStackRequestCereal {
    using ItemDescriptorType = ItemStackRequestCereal_nested::ItemDescriptorType;
    using EmptyItemDescriptorData = ItemStackRequestCereal_nested::EmptyItemDescriptorData;
    using ItemNameDescriptorData = ItemStackRequestCereal_nested::ItemNameDescriptorData;
    using MolangItemDescriptorData = ItemStackRequestCereal_nested::MolangItemDescriptorData;
    using ItemTagDescriptorData = ItemStackRequestCereal_nested::ItemTagDescriptorData;
    using NetworkItemInstanceDescriptorData = ItemStackRequestCereal_nested::NetworkItemInstanceDescriptorData;
    using RecipeIngredientData = ItemStackRequestCereal_nested::RecipeIngredientData;
    using SlotInfoData = ItemStackRequestCereal_nested::SlotInfoData;
    using TakeActionData = ItemStackRequestCereal_nested::TakeActionData;
    using PlaceActionData = ItemStackRequestCereal_nested::PlaceActionData;
    using SwapActionData = ItemStackRequestCereal_nested::SwapActionData;
    using DropActionData = ItemStackRequestCereal_nested::DropActionData;
    using DestroyActionData = ItemStackRequestCereal_nested::DestroyActionData;
    using ConsumeActionData = ItemStackRequestCereal_nested::ConsumeActionData;
    using CreateActionData = ItemStackRequestCereal_nested::CreateActionData;
    using LabTableCombineActionData = ItemStackRequestCereal_nested::LabTableCombineActionData;
    using BeaconPaymentActionData = ItemStackRequestCereal_nested::BeaconPaymentActionData;
    using MineBlockActionData = ItemStackRequestCereal_nested::MineBlockActionData;
    using CraftRecipeActionData = ItemStackRequestCereal_nested::CraftRecipeActionData;
    using CraftRecipeAutoActionData = ItemStackRequestCereal_nested::CraftRecipeAutoActionData;
    using CraftCreativeActionData = ItemStackRequestCereal_nested::CraftCreativeActionData;
    using CraftRecipeOptionalActionData = ItemStackRequestCereal_nested::CraftRecipeOptionalActionData;
    using CraftRepairAndDisenchantActionData = ItemStackRequestCereal_nested::CraftRepairAndDisenchantActionData;
    using CraftLoomActionData = ItemStackRequestCereal_nested::CraftLoomActionData;
    using CraftNonImplementedActionData = ItemStackRequestCereal_nested::CraftNonImplementedActionData;
    using CraftResultsActionData = ItemStackRequestCereal_nested::CraftResultsActionData;
    using RequestData = ItemStackRequestCereal_nested::RequestData;
};

struct ItemStackRequestPacket {
    static constexpr int Id = 147;
    std::vector<v2168::ItemStackRequestCereal::RequestData> requests{};
};

}  // namespace v2168

namespace v2193 {

using ItemStackRequestActionType = v786::ItemStackRequestActionType;

using TextProcessingEventOrigin = v975::TextProcessingEventOrigin;

using RedactableString = v2168::RedactableString;

struct ItemStackResponseSlotInfo {
    std::uint8_t requested_slot{};
    std::uint8_t slot{};
    std::uint8_t amount{};
    std::optional<ItemStackNetId> item_stack_net_id{};
    v2168::RedactableString custom_name{};
    std::int16_t durability_correction{};
};

struct ItemStackResponseContainerInfo {
    v924::FullContainerName full_container_name{};
    std::vector<v2193::ItemStackResponseSlotInfo> slots{};
};

struct ItemStackResponseInfo {
    ItemStackNetResult result{};
    ItemStackRequestId client_request_id{};
    std::optional<std::vector<v2193::ItemStackResponseContainerInfo>> containers{};
};

struct ItemStackResponsePacket {
    static constexpr int Id = 148;
    std::vector<v2193::ItemStackResponseInfo> responses{};
};

using ItemStackRequestCereal = v2168::ItemStackRequestCereal;

using ItemStackRequestPacket = v2168::ItemStackRequestPacket;

}  // namespace v2193

namespace v2225 {

enum class ItemStackRequestActionType : std::uint8_t {
    Take = 0,
    Place = 1,
    Swap = 2,
    Drop = 3,
    Destroy = 4,
    Consume = 5,
    Create = 6,
    PlaceInItemContainerDeprecated = 7,
    TakeFromItemContainerDeprecated = 8,
    ScreenLabTableCombine = 9,
    ScreenBeaconPayment = 10,
    ScreenHUDMineBlock = 11,
    CraftRecipe = 12,
    CraftRecipeAuto = 13,
    CraftCreative = 14,
    CraftRecipeOptional = 15,
    CraftRepairAndDisenchant = 16,
    CraftLoom = 17,
    CraftReservedAction = 18,
    CraftNonImplementedDeprecatedasktylaing = 19,
    CraftResultsDeprecatedasktylaing = 20,
};

using TextProcessingEventOrigin = v975::TextProcessingEventOrigin;

using RedactableString = v2168::RedactableString;

using ItemStackResponseSlotInfo = v2193::ItemStackResponseSlotInfo;

struct ItemStackResponseContainerInfo {
    v2225::FullContainerName full_container_name{};
    std::vector<v2193::ItemStackResponseSlotInfo> slots{};
};

struct ItemStackResponseInfo {
    ItemStackNetResult result{};
    ItemStackRequestId client_request_id{};
    std::optional<std::vector<v2225::ItemStackResponseContainerInfo>> containers{};
};

struct ItemStackResponsePacket {
    static constexpr int Id = 148;
    std::vector<v2225::ItemStackResponseInfo> responses{};
};

namespace ItemStackRequestCereal_nested {

using ItemDescriptorType = v2168::ItemStackRequestCereal::ItemDescriptorType;
using EmptyItemDescriptorData = v2168::ItemStackRequestCereal::EmptyItemDescriptorData;
using ItemNameDescriptorData = v2168::ItemStackRequestCereal::ItemNameDescriptorData;

struct MolangItemDescriptorData {
    std::string tag_expression{};
    v827::MolangVersion molang_version{};
};

using ItemTagDescriptorData = v2168::ItemStackRequestCereal::ItemTagDescriptorData;
using NetworkItemInstanceDescriptorData = v2168::ItemStackRequestCereal::NetworkItemInstanceDescriptorData;
using RecipeIngredientData = v2168::ItemStackRequestCereal::RecipeIngredientData;

struct SlotInfoData {
    v2225::FullContainerName full_container_name{};
    std::uint8_t slot{};
    std::int32_t net_id_variant{};
};

struct TakeActionData {
    std::uint8_t amount{};
    SlotInfoData source{};
    SlotInfoData destination{};
};

struct PlaceActionData {
    std::uint8_t amount{};
    SlotInfoData source{};
    SlotInfoData destination{};
};

struct SwapActionData {
    SlotInfoData source{};
    SlotInfoData destination{};
};

struct DropActionData {
    std::uint8_t amount{};
    SlotInfoData source{};
    bool randomly{};
};

struct DestroyActionData {
    std::uint8_t amount{};
    SlotInfoData source{};
};

struct ConsumeActionData {
    std::uint8_t amount{};
    SlotInfoData source{};
};

struct CreateActionData {
    std::uint8_t results_index{};
};

struct LabTableCombineActionData {
};

struct BeaconPaymentActionData {
    std::int32_t primary_effect_id{};
    std::int32_t secondary_effect_id{};
};

struct MineBlockActionData {
    std::int32_t slot{};
    std::int32_t predicted_durability{};
    std::int32_t net_id_variant{};
};

struct CraftRecipeActionData {
    RecipeNetId recipe_net_id{};
    std::uint8_t num_crafts{};
};

struct CraftRecipeAutoActionData {
    RecipeNetId recipe_net_id{};
    std::uint8_t num_crafts{};
    std::vector<RecipeIngredientData> ingredients{};
};

struct CraftCreativeActionData {
    std::uint32_t creative_item_net_id{};
    std::uint8_t num_crafts{};
};

struct CraftRecipeOptionalActionData {
    RecipeNetId recipe_net_id{};
    std::int32_t filtered_string_index{};
};

struct CraftRepairAndDisenchantActionData {
    std::int32_t recipe_net_id{};
    std::uint8_t num_crafts{};
    std::int32_t repair_cost{};
};

struct CraftLoomActionData {
    std::string pattern_name_id{};
    std::uint8_t num_crafts{};
};

struct CraftDiscPressActionData {
    std::string reserved_id{};
    std::uint8_t num_crafts{};
};

struct CraftNonImplementedActionData {
};

struct CraftResultsActionData {
    std::vector<NetworkItemInstanceDescriptorData> craft_results{};
    std::uint8_t num_crafts{};
};

struct RequestData {
    ItemStackRequestId client_request_id{};
    std::vector<std::variant<TakeActionData, PlaceActionData, SwapActionData, DropActionData, DestroyActionData, ConsumeActionData, CreateActionData, LabTableCombineActionData, BeaconPaymentActionData, MineBlockActionData, CraftRecipeActionData, CraftRecipeAutoActionData, CraftCreativeActionData, CraftRecipeOptionalActionData, CraftRepairAndDisenchantActionData, CraftLoomActionData, CraftDiscPressActionData, CraftNonImplementedActionData, CraftResultsActionData>> actions{};
    std::vector<std::string> strings_to_filter{};
    v975::TextProcessingEventOrigin strings_to_filter_origin{};
};

}  // namespace ItemStackRequestCereal_nested

struct ItemStackRequestCereal {
    using ItemDescriptorType = ItemStackRequestCereal_nested::ItemDescriptorType;
    using EmptyItemDescriptorData = ItemStackRequestCereal_nested::EmptyItemDescriptorData;
    using ItemNameDescriptorData = ItemStackRequestCereal_nested::ItemNameDescriptorData;
    using MolangItemDescriptorData = ItemStackRequestCereal_nested::MolangItemDescriptorData;
    using ItemTagDescriptorData = ItemStackRequestCereal_nested::ItemTagDescriptorData;
    using NetworkItemInstanceDescriptorData = ItemStackRequestCereal_nested::NetworkItemInstanceDescriptorData;
    using RecipeIngredientData = ItemStackRequestCereal_nested::RecipeIngredientData;
    using SlotInfoData = ItemStackRequestCereal_nested::SlotInfoData;
    using TakeActionData = ItemStackRequestCereal_nested::TakeActionData;
    using PlaceActionData = ItemStackRequestCereal_nested::PlaceActionData;
    using SwapActionData = ItemStackRequestCereal_nested::SwapActionData;
    using DropActionData = ItemStackRequestCereal_nested::DropActionData;
    using DestroyActionData = ItemStackRequestCereal_nested::DestroyActionData;
    using ConsumeActionData = ItemStackRequestCereal_nested::ConsumeActionData;
    using CreateActionData = ItemStackRequestCereal_nested::CreateActionData;
    using LabTableCombineActionData = ItemStackRequestCereal_nested::LabTableCombineActionData;
    using BeaconPaymentActionData = ItemStackRequestCereal_nested::BeaconPaymentActionData;
    using MineBlockActionData = ItemStackRequestCereal_nested::MineBlockActionData;
    using CraftRecipeActionData = ItemStackRequestCereal_nested::CraftRecipeActionData;
    using CraftRecipeAutoActionData = ItemStackRequestCereal_nested::CraftRecipeAutoActionData;
    using CraftCreativeActionData = ItemStackRequestCereal_nested::CraftCreativeActionData;
    using CraftRecipeOptionalActionData = ItemStackRequestCereal_nested::CraftRecipeOptionalActionData;
    using CraftRepairAndDisenchantActionData = ItemStackRequestCereal_nested::CraftRepairAndDisenchantActionData;
    using CraftLoomActionData = ItemStackRequestCereal_nested::CraftLoomActionData;
    using CraftDiscPressActionData = ItemStackRequestCereal_nested::CraftDiscPressActionData;
    using CraftNonImplementedActionData = ItemStackRequestCereal_nested::CraftNonImplementedActionData;
    using CraftResultsActionData = ItemStackRequestCereal_nested::CraftResultsActionData;
    using RequestData = ItemStackRequestCereal_nested::RequestData;
};

struct ItemStackRequestPacket {
    static constexpr int Id = 147;
    std::vector<v2225::ItemStackRequestCereal::RequestData> requests{};
};

}  // namespace v2225

namespace detail {

template <int V>
struct ItemStackRequestActionType_;

template <int V> requires (V < 776)
struct ItemStackRequestActionType_<V> { using type = base::ItemStackRequestActionType; };

template <int V> requires (V >= 776 && V < 786)
struct ItemStackRequestActionType_<V> { using type = v776::ItemStackRequestActionType; };

template <int V> requires (V >= 786 && V < 2225)
struct ItemStackRequestActionType_<V> { using type = v786::ItemStackRequestActionType; };

template <int V> requires (V >= 2225)
struct ItemStackRequestActionType_<V> { using type = v2225::ItemStackRequestActionType; };

template <int V>
struct TextProcessingEventOrigin_;

template <int V> requires (V < 975)
struct TextProcessingEventOrigin_<V> { using type = base::TextProcessingEventOrigin; };

template <int V> requires (V >= 975)
struct TextProcessingEventOrigin_<V> { using type = v975::TextProcessingEventOrigin; };

template <int V>
struct RedactableString_;

template <int V> requires (V >= 766 && V < 2168)
struct RedactableString_<V> { using type = v766::RedactableString; };

template <int V> requires (V >= 2168)
struct RedactableString_<V> { using type = v2168::RedactableString; };

template <int V>
struct ItemStackResponseSlotInfo_;

template <int V> requires (V < 766)
struct ItemStackResponseSlotInfo_<V> { using type = base::ItemStackResponseSlotInfo; };

template <int V> requires (V >= 766 && V < 2168)
struct ItemStackResponseSlotInfo_<V> { using type = v766::ItemStackResponseSlotInfo; };

template <int V> requires (V >= 2168 && V < 2193)
struct ItemStackResponseSlotInfo_<V> { using type = v2168::ItemStackResponseSlotInfo; };

template <int V> requires (V >= 2193)
struct ItemStackResponseSlotInfo_<V> { using type = v2193::ItemStackResponseSlotInfo; };

template <int V>
struct ItemStackResponseContainerInfo_;

template <int V> requires (V < 766)
struct ItemStackResponseContainerInfo_<V> { using type = base::ItemStackResponseContainerInfo; };

template <int V> requires (V >= 766 && V < 924)
struct ItemStackResponseContainerInfo_<V> { using type = v766::ItemStackResponseContainerInfo; };

template <int V> requires (V >= 924 && V < 2168)
struct ItemStackResponseContainerInfo_<V> { using type = v924::ItemStackResponseContainerInfo; };

template <int V> requires (V >= 2168 && V < 2193)
struct ItemStackResponseContainerInfo_<V> { using type = v2168::ItemStackResponseContainerInfo; };

template <int V> requires (V >= 2193 && V < 2225)
struct ItemStackResponseContainerInfo_<V> { using type = v2193::ItemStackResponseContainerInfo; };

template <int V> requires (V >= 2225)
struct ItemStackResponseContainerInfo_<V> { using type = v2225::ItemStackResponseContainerInfo; };

template <int V>
struct ItemStackResponseInfo_;

template <int V> requires (V < 766)
struct ItemStackResponseInfo_<V> { using type = base::ItemStackResponseInfo; };

template <int V> requires (V >= 766 && V < 924)
struct ItemStackResponseInfo_<V> { using type = v766::ItemStackResponseInfo; };

template <int V> requires (V >= 924 && V < 2168)
struct ItemStackResponseInfo_<V> { using type = v924::ItemStackResponseInfo; };

template <int V> requires (V >= 2168 && V < 2193)
struct ItemStackResponseInfo_<V> { using type = v2168::ItemStackResponseInfo; };

template <int V> requires (V >= 2193 && V < 2225)
struct ItemStackResponseInfo_<V> { using type = v2193::ItemStackResponseInfo; };

template <int V> requires (V >= 2225)
struct ItemStackResponseInfo_<V> { using type = v2225::ItemStackResponseInfo; };

template <int V>
struct ItemStackResponsePacket_;

template <int V> requires (V < 766)
struct ItemStackResponsePacket_<V> { using type = base::ItemStackResponsePacket; };

template <int V> requires (V >= 766 && V < 924)
struct ItemStackResponsePacket_<V> { using type = v766::ItemStackResponsePacket; };

template <int V> requires (V >= 924 && V < 2168)
struct ItemStackResponsePacket_<V> { using type = v924::ItemStackResponsePacket; };

template <int V> requires (V >= 2168 && V < 2193)
struct ItemStackResponsePacket_<V> { using type = v2168::ItemStackResponsePacket; };

template <int V> requires (V >= 2193 && V < 2225)
struct ItemStackResponsePacket_<V> { using type = v2193::ItemStackResponsePacket; };

template <int V> requires (V >= 2225)
struct ItemStackResponsePacket_<V> { using type = v2225::ItemStackResponsePacket; };

template <int V>
struct ItemStackRequestCereal_;

template <int V> requires (V >= 2168 && V < 2225)
struct ItemStackRequestCereal_<V> { using type = v2168::ItemStackRequestCereal; };

template <int V> requires (V >= 2225)
struct ItemStackRequestCereal_<V> { using type = v2225::ItemStackRequestCereal; };

template <int V>
struct ItemStackRequestSlotInfo_;

template <int V> requires (V < 924)
struct ItemStackRequestSlotInfo_<V> { using type = base::ItemStackRequestSlotInfo; };

template <int V> requires (V >= 924 && V < 2168)
struct ItemStackRequestSlotInfo_<V> { using type = v924::ItemStackRequestSlotInfo; };

template <int V>
struct ItemStackRequestActionTake_;

template <int V> requires (V < 924)
struct ItemStackRequestActionTake_<V> { using type = base::ItemStackRequestActionTake; };

template <int V> requires (V >= 924 && V < 2168)
struct ItemStackRequestActionTake_<V> { using type = v924::ItemStackRequestActionTake; };

template <int V>
struct ItemStackRequestActionPlace_;

template <int V> requires (V < 924)
struct ItemStackRequestActionPlace_<V> { using type = base::ItemStackRequestActionPlace; };

template <int V> requires (V >= 924 && V < 2168)
struct ItemStackRequestActionPlace_<V> { using type = v924::ItemStackRequestActionPlace; };

template <int V>
struct ItemStackRequestActionSwap_;

template <int V> requires (V < 924)
struct ItemStackRequestActionSwap_<V> { using type = base::ItemStackRequestActionSwap; };

template <int V> requires (V >= 924 && V < 2168)
struct ItemStackRequestActionSwap_<V> { using type = v924::ItemStackRequestActionSwap; };

template <int V>
struct ItemStackRequestActionDrop_;

template <int V> requires (V < 924)
struct ItemStackRequestActionDrop_<V> { using type = base::ItemStackRequestActionDrop; };

template <int V> requires (V >= 924 && V < 2168)
struct ItemStackRequestActionDrop_<V> { using type = v924::ItemStackRequestActionDrop; };

template <int V>
struct ItemStackRequestActionDestroy_;

template <int V> requires (V < 924)
struct ItemStackRequestActionDestroy_<V> { using type = base::ItemStackRequestActionDestroy; };

template <int V> requires (V >= 924 && V < 2168)
struct ItemStackRequestActionDestroy_<V> { using type = v924::ItemStackRequestActionDestroy; };

template <int V>
struct ItemStackRequestActionConsume_;

template <int V> requires (V < 924)
struct ItemStackRequestActionConsume_<V> { using type = base::ItemStackRequestActionConsume; };

template <int V> requires (V >= 924 && V < 2168)
struct ItemStackRequestActionConsume_<V> { using type = v924::ItemStackRequestActionConsume; };

template <int V>
struct ItemStackRequestActionCreate_;

template <int V> requires (V < 2168)
struct ItemStackRequestActionCreate_<V> { using type = base::ItemStackRequestActionCreate; };

template <int V>
struct ItemStackRequestActionLabTableCombine_;

template <int V> requires (V < 2168)
struct ItemStackRequestActionLabTableCombine_<V> { using type = base::ItemStackRequestActionLabTableCombine; };

template <int V>
struct ItemStackRequestActionBeaconPayment_;

template <int V> requires (V < 2168)
struct ItemStackRequestActionBeaconPayment_<V> { using type = base::ItemStackRequestActionBeaconPayment; };

template <int V>
struct ItemStackRequestActionMineBlock_;

template <int V> requires (V < 2168)
struct ItemStackRequestActionMineBlock_<V> { using type = base::ItemStackRequestActionMineBlock; };

template <int V>
struct ItemStackRequestActionCraftRecipe_;

template <int V> requires (V < 2168)
struct ItemStackRequestActionCraftRecipe_<V> { using type = base::ItemStackRequestActionCraftRecipe; };

template <int V>
struct ItemStackRequestActionCraftRecipeAuto_;

template <int V> requires (V < 2168)
struct ItemStackRequestActionCraftRecipeAuto_<V> { using type = base::ItemStackRequestActionCraftRecipeAuto; };

template <int V>
struct ItemStackRequestActionCraftCreative_;

template <int V> requires (V < 2168)
struct ItemStackRequestActionCraftCreative_<V> { using type = base::ItemStackRequestActionCraftCreative; };

template <int V>
struct ItemStackRequestActionCraftRecipeOptional_;

template <int V> requires (V < 2168)
struct ItemStackRequestActionCraftRecipeOptional_<V> { using type = base::ItemStackRequestActionCraftRecipeOptional; };

template <int V>
struct ItemStackRequestActionCraftGrindstone_;

template <int V> requires (V < 2168)
struct ItemStackRequestActionCraftGrindstone_<V> { using type = base::ItemStackRequestActionCraftGrindstone; };

template <int V>
struct ItemStackRequestActionCraftLoom_;

template <int V> requires (V < 2168)
struct ItemStackRequestActionCraftLoom_<V> { using type = base::ItemStackRequestActionCraftLoom; };

template <int V>
struct ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING_;

template <int V> requires (V < 2168)
struct ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING_<V> { using type = base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING; };

template <int V>
struct ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING_;

template <int V> requires (V < 2168)
struct ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING_<V> { using type = base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING; };

template <int V>
struct ItemStackRequestData_;

template <int V> requires (V < 924)
struct ItemStackRequestData_<V> { using type = base::ItemStackRequestData; };

template <int V> requires (V >= 924 && V < 975)
struct ItemStackRequestData_<V> { using type = v924::ItemStackRequestData; };

template <int V> requires (V >= 975 && V < 2168)
struct ItemStackRequestData_<V> { using type = v975::ItemStackRequestData; };

template <int V>
struct ItemStackRequestPacket_;

template <int V> requires (V < 924)
struct ItemStackRequestPacket_<V> { using type = base::ItemStackRequestPacket; };

template <int V> requires (V >= 924 && V < 975)
struct ItemStackRequestPacket_<V> { using type = v924::ItemStackRequestPacket; };

template <int V> requires (V >= 975 && V < 2168)
struct ItemStackRequestPacket_<V> { using type = v975::ItemStackRequestPacket; };

template <int V> requires (V >= 2168 && V < 2225)
struct ItemStackRequestPacket_<V> { using type = v2168::ItemStackRequestPacket; };

template <int V> requires (V >= 2225)
struct ItemStackRequestPacket_<V> { using type = v2225::ItemStackRequestPacket; };

}  // namespace detail

template <int V> using ItemStackRequestActionType_ = typename detail::ItemStackRequestActionType_<V>::type;
template <int V> using TextProcessingEventOrigin_ = typename detail::TextProcessingEventOrigin_<V>::type;
template <int V> using RedactableString_ = typename detail::RedactableString_<V>::type;
template <int V> using ItemStackResponseSlotInfo_ = typename detail::ItemStackResponseSlotInfo_<V>::type;
template <int V> using ItemStackResponseContainerInfo_ = typename detail::ItemStackResponseContainerInfo_<V>::type;
template <int V> using ItemStackResponseInfo_ = typename detail::ItemStackResponseInfo_<V>::type;
template <int V> using ItemStackResponsePacket_ = typename detail::ItemStackResponsePacket_<V>::type;
template <int V> using ItemStackRequestCereal_ = typename detail::ItemStackRequestCereal_<V>::type;
template <int V> using ItemStackRequestSlotInfo_ = typename detail::ItemStackRequestSlotInfo_<V>::type;
template <int V> using ItemStackRequestActionTake_ = typename detail::ItemStackRequestActionTake_<V>::type;
template <int V> using ItemStackRequestActionPlace_ = typename detail::ItemStackRequestActionPlace_<V>::type;
template <int V> using ItemStackRequestActionSwap_ = typename detail::ItemStackRequestActionSwap_<V>::type;
template <int V> using ItemStackRequestActionDrop_ = typename detail::ItemStackRequestActionDrop_<V>::type;
template <int V> using ItemStackRequestActionDestroy_ = typename detail::ItemStackRequestActionDestroy_<V>::type;
template <int V> using ItemStackRequestActionConsume_ = typename detail::ItemStackRequestActionConsume_<V>::type;
template <int V> using ItemStackRequestActionCreate_ = typename detail::ItemStackRequestActionCreate_<V>::type;
template <int V> using ItemStackRequestActionLabTableCombine_ = typename detail::ItemStackRequestActionLabTableCombine_<V>::type;
template <int V> using ItemStackRequestActionBeaconPayment_ = typename detail::ItemStackRequestActionBeaconPayment_<V>::type;
template <int V> using ItemStackRequestActionMineBlock_ = typename detail::ItemStackRequestActionMineBlock_<V>::type;
template <int V> using ItemStackRequestActionCraftRecipe_ = typename detail::ItemStackRequestActionCraftRecipe_<V>::type;
template <int V> using ItemStackRequestActionCraftRecipeAuto_ = typename detail::ItemStackRequestActionCraftRecipeAuto_<V>::type;
template <int V> using ItemStackRequestActionCraftCreative_ = typename detail::ItemStackRequestActionCraftCreative_<V>::type;
template <int V> using ItemStackRequestActionCraftRecipeOptional_ = typename detail::ItemStackRequestActionCraftRecipeOptional_<V>::type;
template <int V> using ItemStackRequestActionCraftGrindstone_ = typename detail::ItemStackRequestActionCraftGrindstone_<V>::type;
template <int V> using ItemStackRequestActionCraftLoom_ = typename detail::ItemStackRequestActionCraftLoom_<V>::type;
template <int V> using ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING_ = typename detail::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING_<V>::type;
template <int V> using ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING_ = typename detail::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING_<V>::type;
template <int V> using ItemStackRequestData_ = typename detail::ItemStackRequestData_<V>::type;
template <int V> using ItemStackRequestPacket_ = typename detail::ItemStackRequestPacket_<V>::type;

template <int V>
struct packet_of<V, 147> { using type = ItemStackRequestPacket_<V>; };

template <int V>
struct packet_of<V, 148> { using type = ItemStackResponsePacket_<V>; };

namespace detail {

template <>
inline constexpr std::array<base::ItemStackRequestActionType, 20> values_v<base::ItemStackRequestActionType>{{
    base::ItemStackRequestActionType::Take,
    base::ItemStackRequestActionType::Place,
    base::ItemStackRequestActionType::Swap,
    base::ItemStackRequestActionType::Drop,
    base::ItemStackRequestActionType::Destroy,
    base::ItemStackRequestActionType::Consume,
    base::ItemStackRequestActionType::Create,
    base::ItemStackRequestActionType::PlaceInItemContainerDeprecated,
    base::ItemStackRequestActionType::TakeFromItemContainerDeprecated,
    base::ItemStackRequestActionType::ScreenLabTableCombine,
    base::ItemStackRequestActionType::ScreenBeaconPayment,
    base::ItemStackRequestActionType::ScreenHUDMineBlock,
    base::ItemStackRequestActionType::CraftRecipe,
    base::ItemStackRequestActionType::CraftRecipeAuto,
    base::ItemStackRequestActionType::CraftCreative,
    base::ItemStackRequestActionType::CraftRecipeOptional,
    base::ItemStackRequestActionType::CraftRepairAndDisenchant,
    base::ItemStackRequestActionType::CraftLoom,
    base::ItemStackRequestActionType::CraftNonImplementedDeprecatedasktylaing,
    base::ItemStackRequestActionType::CraftResultsDeprecatedasktylaing,
}};

template <>
inline constexpr std::array<std::string_view, 20> names_v<base::ItemStackRequestActionType>{{
    "take",
    "place",
    "swap",
    "drop",
    "destroy",
    "consume",
    "create",
    "placeinitemcontainerdeprecated",
    "takefromitemcontainerdeprecated",
    "screenlabtablecombine",
    "screenbeaconpayment",
    "screenhudmineblock",
    "craftrecipe",
    "craftrecipeauto",
    "craftcreative",
    "craftrecipeoptional",
    "craftrepairanddisenchant",
    "craftloom",
    "craftnonimplementeddeprecatedasktylaing",
    "craftresultsdeprecatedasktylaing",
}};

template <>
inline constexpr std::string_view type_name_v<base::ItemStackRequestActionType>{"ItemStackRequestActionType"};

template <>
inline constexpr std::array<v776::ItemStackRequestActionType, 21> values_v<v776::ItemStackRequestActionType>{{
    v776::ItemStackRequestActionType::Take,
    v776::ItemStackRequestActionType::Place,
    v776::ItemStackRequestActionType::Swap,
    v776::ItemStackRequestActionType::Drop,
    v776::ItemStackRequestActionType::Destroy,
    v776::ItemStackRequestActionType::Consume,
    v776::ItemStackRequestActionType::Create,
    v776::ItemStackRequestActionType::PlaceInItemContainerDeprecated,
    v776::ItemStackRequestActionType::TakeFromItemContainerDeprecated,
    v776::ItemStackRequestActionType::ScreenLabTableCombine,
    v776::ItemStackRequestActionType::ScreenBeaconPayment,
    v776::ItemStackRequestActionType::ScreenHUDMineBlock,
    v776::ItemStackRequestActionType::CraftRecipe,
    v776::ItemStackRequestActionType::CraftRecipeAuto,
    v776::ItemStackRequestActionType::CraftCreative,
    v776::ItemStackRequestActionType::CraftRecipeOptional,
    v776::ItemStackRequestActionType::CraftRepairAndDisenchant,
    v776::ItemStackRequestActionType::CraftLoom,
    v776::ItemStackRequestActionType::CraftNonImplementedDeprecatedasktylaing,
    v776::ItemStackRequestActionType::CraftResultsDeprecatedasktylaing,
    v776::ItemStackRequestActionType::Test,
}};

template <>
inline constexpr std::array<std::string_view, 21> names_v<v776::ItemStackRequestActionType>{{
    "take",
    "place",
    "swap",
    "drop",
    "destroy",
    "consume",
    "create",
    "placeinitemcontainerdeprecated",
    "takefromitemcontainerdeprecated",
    "screenlabtablecombine",
    "screenbeaconpayment",
    "screenhudmineblock",
    "craftrecipe",
    "craftrecipeauto",
    "craftcreative",
    "craftrecipeoptional",
    "craftrepairanddisenchant",
    "craftloom",
    "craftnonimplementeddeprecatedasktylaing",
    "craftresultsdeprecatedasktylaing",
    "test",
}};

template <>
inline constexpr std::string_view type_name_v<v776::ItemStackRequestActionType>{"ItemStackRequestActionType"};

template <>
inline constexpr std::array<v786::ItemStackRequestActionType, 20> values_v<v786::ItemStackRequestActionType>{{
    v786::ItemStackRequestActionType::Take,
    v786::ItemStackRequestActionType::Place,
    v786::ItemStackRequestActionType::Swap,
    v786::ItemStackRequestActionType::Drop,
    v786::ItemStackRequestActionType::Destroy,
    v786::ItemStackRequestActionType::Consume,
    v786::ItemStackRequestActionType::Create,
    v786::ItemStackRequestActionType::PlaceInItemContainerDeprecated,
    v786::ItemStackRequestActionType::TakeFromItemContainerDeprecated,
    v786::ItemStackRequestActionType::ScreenLabTableCombine,
    v786::ItemStackRequestActionType::ScreenBeaconPayment,
    v786::ItemStackRequestActionType::ScreenHUDMineBlock,
    v786::ItemStackRequestActionType::CraftRecipe,
    v786::ItemStackRequestActionType::CraftRecipeAuto,
    v786::ItemStackRequestActionType::CraftCreative,
    v786::ItemStackRequestActionType::CraftRecipeOptional,
    v786::ItemStackRequestActionType::CraftRepairAndDisenchant,
    v786::ItemStackRequestActionType::CraftLoom,
    v786::ItemStackRequestActionType::CraftNonImplementedDeprecatedasktylaing,
    v786::ItemStackRequestActionType::CraftResultsDeprecatedasktylaing,
}};

template <>
inline constexpr std::array<std::string_view, 20> names_v<v786::ItemStackRequestActionType>{{
    "take",
    "place",
    "swap",
    "drop",
    "destroy",
    "consume",
    "create",
    "placeinitemcontainerdeprecated",
    "takefromitemcontainerdeprecated",
    "screenlabtablecombine",
    "screenbeaconpayment",
    "screenhudmineblock",
    "craftrecipe",
    "craftrecipeauto",
    "craftcreative",
    "craftrecipeoptional",
    "craftrepairanddisenchant",
    "craftloom",
    "craftnonimplementeddeprecatedasktylaing",
    "craftresultsdeprecatedasktylaing",
}};

template <>
inline constexpr std::string_view type_name_v<v786::ItemStackRequestActionType>{"ItemStackRequestActionType"};

template <>
inline constexpr std::array<v2225::ItemStackRequestActionType, 21> values_v<v2225::ItemStackRequestActionType>{{
    v2225::ItemStackRequestActionType::Take,
    v2225::ItemStackRequestActionType::Place,
    v2225::ItemStackRequestActionType::Swap,
    v2225::ItemStackRequestActionType::Drop,
    v2225::ItemStackRequestActionType::Destroy,
    v2225::ItemStackRequestActionType::Consume,
    v2225::ItemStackRequestActionType::Create,
    v2225::ItemStackRequestActionType::PlaceInItemContainerDeprecated,
    v2225::ItemStackRequestActionType::TakeFromItemContainerDeprecated,
    v2225::ItemStackRequestActionType::ScreenLabTableCombine,
    v2225::ItemStackRequestActionType::ScreenBeaconPayment,
    v2225::ItemStackRequestActionType::ScreenHUDMineBlock,
    v2225::ItemStackRequestActionType::CraftRecipe,
    v2225::ItemStackRequestActionType::CraftRecipeAuto,
    v2225::ItemStackRequestActionType::CraftCreative,
    v2225::ItemStackRequestActionType::CraftRecipeOptional,
    v2225::ItemStackRequestActionType::CraftRepairAndDisenchant,
    v2225::ItemStackRequestActionType::CraftLoom,
    v2225::ItemStackRequestActionType::CraftReservedAction,
    v2225::ItemStackRequestActionType::CraftNonImplementedDeprecatedasktylaing,
    v2225::ItemStackRequestActionType::CraftResultsDeprecatedasktylaing,
}};

template <>
inline constexpr std::array<std::string_view, 21> names_v<v2225::ItemStackRequestActionType>{{
    "take",
    "place",
    "swap",
    "drop",
    "destroy",
    "consume",
    "create",
    "placeinitemcontainerdeprecated",
    "takefromitemcontainerdeprecated",
    "screenlabtablecombine",
    "screenbeaconpayment",
    "screenhudmineblock",
    "craftrecipe",
    "craftrecipeauto",
    "craftcreative",
    "craftrecipeoptional",
    "craftrepairanddisenchant",
    "craftloom",
    "craftreservedaction",
    "craftnonimplementeddeprecatedasktylaing",
    "craftresultsdeprecatedasktylaing",
}};

template <>
inline constexpr std::string_view type_name_v<v2225::ItemStackRequestActionType>{"ItemStackRequestActionType"};

template <>
inline constexpr std::array<ItemStackNetResult, 68> values_v<ItemStackNetResult>{{
    ItemStackNetResult::Success,
    ItemStackNetResult::Error,
    ItemStackNetResult::InvalidRequestActionType,
    ItemStackNetResult::ActionRequestNotAllowed,
    ItemStackNetResult::ScreenHandlerEndRequestFailed,
    ItemStackNetResult::ItemRequestActionHandlerCommitFailed,
    ItemStackNetResult::InvalidRequestCraftActionType,
    ItemStackNetResult::InvalidCraftRequest,
    ItemStackNetResult::InvalidCraftRequestScreen,
    ItemStackNetResult::InvalidCraftResult,
    ItemStackNetResult::InvalidCraftResultIndex,
    ItemStackNetResult::InvalidCraftResultItem,
    ItemStackNetResult::InvalidItemNetId,
    ItemStackNetResult::MissingCreatedOutputContainer,
    ItemStackNetResult::FailedToSetCreatedItemOutputSlot,
    ItemStackNetResult::RequestAlreadyInProgress,
    ItemStackNetResult::FailedToInitSparseContainer,
    ItemStackNetResult::ResultTransferFailed,
    ItemStackNetResult::ExpectedItemSlotNotFullyConsumed,
    ItemStackNetResult::ExpectedAnywhereItemNotFullyConsumed,
    ItemStackNetResult::ItemAlreadyConsumedFromSlot,
    ItemStackNetResult::ConsumedTooMuchFromSlot,
    ItemStackNetResult::MismatchSlotExpectedConsumedItem,
    ItemStackNetResult::MismatchSlotExpectedConsumedItemNetIdVariant,
    ItemStackNetResult::FailedToMatchExpectedSlotConsumedItem,
    ItemStackNetResult::FailedToMatchExpectedAllowedAnywhereConsumedItem,
    ItemStackNetResult::ConsumedItemOutOfAllowedSlotRange,
    ItemStackNetResult::ConsumedItemNotAllowed,
    ItemStackNetResult::PlayerNotInCreativeMode,
    ItemStackNetResult::InvalidExperimentalRecipeRequest,
    ItemStackNetResult::FailedToCraftCreative,
    ItemStackNetResult::FailedToGetLevelRecipe,
    ItemStackNetResult::FailedToFindRecipeByNetId,
    ItemStackNetResult::MismatchedCraftingSize,
    ItemStackNetResult::MissingInputSparseContainer,
    ItemStackNetResult::MismatchedRecipeForInputGridItems,
    ItemStackNetResult::EmptyCraftResults,
    ItemStackNetResult::FailedToEnchant,
    ItemStackNetResult::MissingInputItem,
    ItemStackNetResult::InsufficientPlayerLevelToEnchant,
    ItemStackNetResult::MissingMaterialItem,
    ItemStackNetResult::MissingActor,
    ItemStackNetResult::UnknownPrimaryEffect,
    ItemStackNetResult::PrimaryEffectOutOfRange,
    ItemStackNetResult::PrimaryEffectUnavailable,
    ItemStackNetResult::SecondaryEffectOutOfRange,
    ItemStackNetResult::SecondaryEffectUnavailable,
    ItemStackNetResult::DstContainerEqualToCreatedOutputContainer,
    ItemStackNetResult::DstContainerAndSlotEqualToSrcContainerAndSlot,
    ItemStackNetResult::FailedToValidateSrcSlot,
    ItemStackNetResult::FailedToValidateDstSlot,
    ItemStackNetResult::InvalidAdjustedAmount,
    ItemStackNetResult::InvalidItemSetType,
    ItemStackNetResult::InvalidTransferAmount,
    ItemStackNetResult::CannotSwapItem,
    ItemStackNetResult::CannotPlaceItem,
    ItemStackNetResult::UnhandledItemSetType,
    ItemStackNetResult::InvalidRemovedAmount,
    ItemStackNetResult::InvalidRegion,
    ItemStackNetResult::CannotDropItem,
    ItemStackNetResult::CannotDestroyItem,
    ItemStackNetResult::InvalidSourceContainer,
    ItemStackNetResult::ItemNotConsumed,
    ItemStackNetResult::InvalidNumCrafts,
    ItemStackNetResult::InvalidCraftResultStackSize,
    ItemStackNetResult::CannotRemoveItem,
    ItemStackNetResult::CannotConsumeItem,
    ItemStackNetResult::ScreenStackError,
}};

template <>
inline constexpr std::array<std::string_view, 68> names_v<ItemStackNetResult>{{
    "success",
    "error",
    "invalidrequestactiontype",
    "actionrequestnotallowed",
    "screenhandlerendrequestfailed",
    "itemrequestactionhandlercommitfailed",
    "invalidrequestcraftactiontype",
    "invalidcraftrequest",
    "invalidcraftrequestscreen",
    "invalidcraftresult",
    "invalidcraftresultindex",
    "invalidcraftresultitem",
    "invaliditemnetid",
    "missingcreatedoutputcontainer",
    "failedtosetcreateditemoutputslot",
    "requestalreadyinprogress",
    "failedtoinitsparsecontainer",
    "resulttransferfailed",
    "expecteditemslotnotfullyconsumed",
    "expectedanywhereitemnotfullyconsumed",
    "itemalreadyconsumedfromslot",
    "consumedtoomuchfromslot",
    "mismatchslotexpectedconsumeditem",
    "mismatchslotexpectedconsumeditemnetidvariant",
    "failedtomatchexpectedslotconsumeditem",
    "failedtomatchexpectedallowedanywhereconsumeditem",
    "consumeditemoutofallowedslotrange",
    "consumeditemnotallowed",
    "playernotincreativemode",
    "invalidexperimentalreciperequest",
    "failedtocraftcreative",
    "failedtogetlevelrecipe",
    "failedtofindrecipebynetid",
    "mismatchedcraftingsize",
    "missinginputsparsecontainer",
    "mismatchedrecipeforinputgriditems",
    "emptycraftresults",
    "failedtoenchant",
    "missinginputitem",
    "insufficientplayerleveltoenchant",
    "missingmaterialitem",
    "missingactor",
    "unknownprimaryeffect",
    "primaryeffectoutofrange",
    "primaryeffectunavailable",
    "secondaryeffectoutofrange",
    "secondaryeffectunavailable",
    "dstcontainerequaltocreatedoutputcontainer",
    "dstcontainerandslotequaltosrccontainerandslot",
    "failedtovalidatesrcslot",
    "failedtovalidatedstslot",
    "invalidadjustedamount",
    "invaliditemsettype",
    "invalidtransferamount",
    "cannotswapitem",
    "cannotplaceitem",
    "unhandleditemsettype",
    "invalidremovedamount",
    "invalidregion",
    "cannotdropitem",
    "cannotdestroyitem",
    "invalidsourcecontainer",
    "itemnotconsumed",
    "invalidnumcrafts",
    "invalidcraftresultstacksize",
    "cannotremoveitem",
    "cannotconsumeitem",
    "screenstackerror",
}};

template <>
inline constexpr std::string_view type_name_v<ItemStackNetResult>{"ItemStackNetResult"};

template <>
inline constexpr std::array<base::TextProcessingEventOrigin, 17> values_v<base::TextProcessingEventOrigin>{{
    base::TextProcessingEventOrigin::Unknown,
    base::TextProcessingEventOrigin::ServerChatPublic,
    base::TextProcessingEventOrigin::ServerChatWhisper,
    base::TextProcessingEventOrigin::SignText,
    base::TextProcessingEventOrigin::AnvilText,
    base::TextProcessingEventOrigin::BookAndQuillText,
    base::TextProcessingEventOrigin::CommandBlockText,
    base::TextProcessingEventOrigin::BlockActorDataText,
    base::TextProcessingEventOrigin::JoinEventText,
    base::TextProcessingEventOrigin::LeaveEventText,
    base::TextProcessingEventOrigin::SlashCommandChat,
    base::TextProcessingEventOrigin::CartographyText,
    base::TextProcessingEventOrigin::KickCommand,
    base::TextProcessingEventOrigin::TitleCommand,
    base::TextProcessingEventOrigin::SummonCommand,
    base::TextProcessingEventOrigin::ServerForm,
    base::TextProcessingEventOrigin::Count,
}};

template <>
inline constexpr std::array<std::string_view, 17> names_v<base::TextProcessingEventOrigin>{{
    "unknown",
    "serverchatpublic",
    "serverchatwhisper",
    "signtext",
    "anviltext",
    "bookandquilltext",
    "commandblocktext",
    "blockactordatatext",
    "joineventtext",
    "leaveeventtext",
    "slashcommandchat",
    "cartographytext",
    "kickcommand",
    "titlecommand",
    "summoncommand",
    "serverform",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<base::TextProcessingEventOrigin>{"TextProcessingEventOrigin"};

template <>
inline constexpr std::array<v975::TextProcessingEventOrigin, 18> values_v<v975::TextProcessingEventOrigin>{{
    v975::TextProcessingEventOrigin::Unknown,
    v975::TextProcessingEventOrigin::ServerChatPublic,
    v975::TextProcessingEventOrigin::ServerChatWhisper,
    v975::TextProcessingEventOrigin::SignText,
    v975::TextProcessingEventOrigin::AnvilText,
    v975::TextProcessingEventOrigin::BookAndQuillText,
    v975::TextProcessingEventOrigin::CommandBlockText,
    v975::TextProcessingEventOrigin::BlockActorDataText,
    v975::TextProcessingEventOrigin::JoinEventText,
    v975::TextProcessingEventOrigin::LeaveEventText,
    v975::TextProcessingEventOrigin::SlashCommandChat,
    v975::TextProcessingEventOrigin::CartographyText,
    v975::TextProcessingEventOrigin::KickCommand,
    v975::TextProcessingEventOrigin::TitleCommand,
    v975::TextProcessingEventOrigin::SummonCommand,
    v975::TextProcessingEventOrigin::ServerForm,
    v975::TextProcessingEventOrigin::DataDrivenUI,
    v975::TextProcessingEventOrigin::Count,
}};

template <>
inline constexpr std::array<std::string_view, 18> names_v<v975::TextProcessingEventOrigin>{{
    "unknown",
    "serverchatpublic",
    "serverchatwhisper",
    "signtext",
    "anviltext",
    "bookandquilltext",
    "commandblocktext",
    "blockactordatatext",
    "joineventtext",
    "leaveeventtext",
    "slashcommandchat",
    "cartographytext",
    "kickcommand",
    "titlecommand",
    "summoncommand",
    "serverform",
    "datadrivenui",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<v975::TextProcessingEventOrigin>{"TextProcessingEventOrigin"};

template <>
inline constexpr std::array<v2168::ItemStackRequestCereal::ItemDescriptorType, 4> values_v<v2168::ItemStackRequestCereal::ItemDescriptorType>{{
    v2168::ItemStackRequestCereal::ItemDescriptorType::Empty,
    v2168::ItemStackRequestCereal::ItemDescriptorType::ItemName,
    v2168::ItemStackRequestCereal::ItemDescriptorType::Molang,
    v2168::ItemStackRequestCereal::ItemDescriptorType::ItemTag,
}};

template <>
inline constexpr std::array<std::string_view, 4> names_v<v2168::ItemStackRequestCereal::ItemDescriptorType>{{
    "empty",
    "itemname",
    "molang",
    "itemtag",
}};

template <>
inline constexpr std::string_view type_name_v<v2168::ItemStackRequestCereal::ItemDescriptorType>{"ItemStackRequestCereal::ItemDescriptorType"};

}  // namespace detail

namespace detail {

template <>
inline constexpr bool is_reflected_struct_v<v766::RedactableString> = true;

template <>
inline constexpr std::string_view struct_name_v<v766::RedactableString>{"RedactableString"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v766::RedactableString>{{
    "unredacted_string",
    "redacted_string",
}};

template <>
struct field_accessor<v766::RedactableString> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.unredacted_string;
        }
        else {
            return value.redacted_string;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::RedactableString> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::RedactableString>{"RedactableString"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2168::RedactableString>{{
    "unredacted_string",
    "redacted_string",
}};

template <>
struct field_accessor<v2168::RedactableString> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.unredacted_string;
        }
        else {
            return value.redacted_string;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::ItemStackResponseSlotInfo> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ItemStackResponseSlotInfo>{"ItemStackResponseSlotInfo"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<base::ItemStackResponseSlotInfo>{{
    "requested_slot",
    "slot",
    "amount",
    "item_stack_net_id",
    "custom_name",
    "durability_correction",
}};

template <>
struct field_accessor<base::ItemStackResponseSlotInfo> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.requested_slot;
        }
        else if constexpr (I == 1) {
            return value.slot;
        }
        else if constexpr (I == 2) {
            return value.amount;
        }
        else if constexpr (I == 3) {
            return value.item_stack_net_id;
        }
        else if constexpr (I == 4) {
            return value.custom_name;
        }
        else {
            return value.durability_correction;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v766::ItemStackResponseSlotInfo> = true;

template <>
inline constexpr std::string_view struct_name_v<v766::ItemStackResponseSlotInfo>{"ItemStackResponseSlotInfo"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<v766::ItemStackResponseSlotInfo>{{
    "requested_slot",
    "slot",
    "amount",
    "item_stack_net_id",
    "custom_name",
    "durability_correction",
}};

template <>
struct field_accessor<v766::ItemStackResponseSlotInfo> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.requested_slot;
        }
        else if constexpr (I == 1) {
            return value.slot;
        }
        else if constexpr (I == 2) {
            return value.amount;
        }
        else if constexpr (I == 3) {
            return value.item_stack_net_id;
        }
        else if constexpr (I == 4) {
            return value.custom_name;
        }
        else {
            return value.durability_correction;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ItemStackResponseSlotInfo> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ItemStackResponseSlotInfo>{"ItemStackResponseSlotInfo"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<v2168::ItemStackResponseSlotInfo>{{
    "requested_slot",
    "slot",
    "amount",
    "item_stack_net_id",
    "custom_name",
    "durability_correction",
}};

template <>
struct field_accessor<v2168::ItemStackResponseSlotInfo> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.requested_slot;
        }
        else if constexpr (I == 1) {
            return value.slot;
        }
        else if constexpr (I == 2) {
            return value.amount;
        }
        else if constexpr (I == 3) {
            return value.item_stack_net_id;
        }
        else if constexpr (I == 4) {
            return value.custom_name;
        }
        else {
            return value.durability_correction;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2193::ItemStackResponseSlotInfo> = true;

template <>
inline constexpr std::string_view struct_name_v<v2193::ItemStackResponseSlotInfo>{"ItemStackResponseSlotInfo"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<v2193::ItemStackResponseSlotInfo>{{
    "requested_slot",
    "slot",
    "amount",
    "item_stack_net_id",
    "custom_name",
    "durability_correction",
}};

template <>
struct field_accessor<v2193::ItemStackResponseSlotInfo> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.requested_slot;
        }
        else if constexpr (I == 1) {
            return value.slot;
        }
        else if constexpr (I == 2) {
            return value.amount;
        }
        else if constexpr (I == 3) {
            return value.item_stack_net_id;
        }
        else if constexpr (I == 4) {
            return value.custom_name;
        }
        else {
            return value.durability_correction;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::ItemStackResponseContainerInfo> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ItemStackResponseContainerInfo>{"ItemStackResponseContainerInfo"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<base::ItemStackResponseContainerInfo>{{
    "full_container_name",
    "slots",
}};

template <>
struct field_accessor<base::ItemStackResponseContainerInfo> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.full_container_name;
        }
        else {
            return value.slots;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v766::ItemStackResponseContainerInfo> = true;

template <>
inline constexpr std::string_view struct_name_v<v766::ItemStackResponseContainerInfo>{"ItemStackResponseContainerInfo"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v766::ItemStackResponseContainerInfo>{{
    "full_container_name",
    "slots",
}};

template <>
struct field_accessor<v766::ItemStackResponseContainerInfo> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.full_container_name;
        }
        else {
            return value.slots;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::ItemStackResponseContainerInfo> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::ItemStackResponseContainerInfo>{"ItemStackResponseContainerInfo"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v924::ItemStackResponseContainerInfo>{{
    "full_container_name",
    "slots",
}};

template <>
struct field_accessor<v924::ItemStackResponseContainerInfo> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.full_container_name;
        }
        else {
            return value.slots;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ItemStackResponseContainerInfo> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ItemStackResponseContainerInfo>{"ItemStackResponseContainerInfo"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2168::ItemStackResponseContainerInfo>{{
    "full_container_name",
    "slots",
}};

template <>
struct field_accessor<v2168::ItemStackResponseContainerInfo> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.full_container_name;
        }
        else {
            return value.slots;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2193::ItemStackResponseContainerInfo> = true;

template <>
inline constexpr std::string_view struct_name_v<v2193::ItemStackResponseContainerInfo>{"ItemStackResponseContainerInfo"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2193::ItemStackResponseContainerInfo>{{
    "full_container_name",
    "slots",
}};

template <>
struct field_accessor<v2193::ItemStackResponseContainerInfo> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.full_container_name;
        }
        else {
            return value.slots;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::ItemStackResponseContainerInfo> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::ItemStackResponseContainerInfo>{"ItemStackResponseContainerInfo"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2225::ItemStackResponseContainerInfo>{{
    "full_container_name",
    "slots",
}};

template <>
struct field_accessor<v2225::ItemStackResponseContainerInfo> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.full_container_name;
        }
        else {
            return value.slots;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::ItemStackResponseInfo> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ItemStackResponseInfo>{"ItemStackResponseInfo"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<base::ItemStackResponseInfo>{{
    "result",
    "client_request_id",
    "containers",
}};

template <>
struct field_accessor<base::ItemStackResponseInfo> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.result;
        }
        else if constexpr (I == 1) {
            return value.client_request_id;
        }
        else {
            return value.containers;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v766::ItemStackResponseInfo> = true;

template <>
inline constexpr std::string_view struct_name_v<v766::ItemStackResponseInfo>{"ItemStackResponseInfo"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v766::ItemStackResponseInfo>{{
    "result",
    "client_request_id",
    "containers",
}};

template <>
struct field_accessor<v766::ItemStackResponseInfo> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.result;
        }
        else if constexpr (I == 1) {
            return value.client_request_id;
        }
        else {
            return value.containers;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::ItemStackResponseInfo> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::ItemStackResponseInfo>{"ItemStackResponseInfo"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v924::ItemStackResponseInfo>{{
    "result",
    "client_request_id",
    "containers",
}};

template <>
struct field_accessor<v924::ItemStackResponseInfo> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.result;
        }
        else if constexpr (I == 1) {
            return value.client_request_id;
        }
        else {
            return value.containers;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ItemStackResponseInfo> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ItemStackResponseInfo>{"ItemStackResponseInfo"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v2168::ItemStackResponseInfo>{{
    "result",
    "client_request_id",
    "containers",
}};

template <>
struct field_accessor<v2168::ItemStackResponseInfo> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.result;
        }
        else if constexpr (I == 1) {
            return value.client_request_id;
        }
        else {
            return value.containers;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2193::ItemStackResponseInfo> = true;

template <>
inline constexpr std::string_view struct_name_v<v2193::ItemStackResponseInfo>{"ItemStackResponseInfo"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v2193::ItemStackResponseInfo>{{
    "result",
    "client_request_id",
    "containers",
}};

template <>
struct field_accessor<v2193::ItemStackResponseInfo> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.result;
        }
        else if constexpr (I == 1) {
            return value.client_request_id;
        }
        else {
            return value.containers;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::ItemStackResponseInfo> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::ItemStackResponseInfo>{"ItemStackResponseInfo"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v2225::ItemStackResponseInfo>{{
    "result",
    "client_request_id",
    "containers",
}};

template <>
struct field_accessor<v2225::ItemStackResponseInfo> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.result;
        }
        else if constexpr (I == 1) {
            return value.client_request_id;
        }
        else {
            return value.containers;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::ItemStackResponsePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ItemStackResponsePacket>{"ItemStackResponsePacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::ItemStackResponsePacket>{{
    "responses",
}};

template <>
struct field_accessor<base::ItemStackResponsePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.responses;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v766::ItemStackResponsePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v766::ItemStackResponsePacket>{"ItemStackResponsePacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v766::ItemStackResponsePacket>{{
    "responses",
}};

template <>
struct field_accessor<v766::ItemStackResponsePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.responses;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::ItemStackResponsePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::ItemStackResponsePacket>{"ItemStackResponsePacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v924::ItemStackResponsePacket>{{
    "responses",
}};

template <>
struct field_accessor<v924::ItemStackResponsePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.responses;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ItemStackResponsePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ItemStackResponsePacket>{"ItemStackResponsePacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2168::ItemStackResponsePacket>{{
    "responses",
}};

template <>
struct field_accessor<v2168::ItemStackResponsePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.responses;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2193::ItemStackResponsePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2193::ItemStackResponsePacket>{"ItemStackResponsePacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2193::ItemStackResponsePacket>{{
    "responses",
}};

template <>
struct field_accessor<v2193::ItemStackResponsePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.responses;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::ItemStackResponsePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::ItemStackResponsePacket>{"ItemStackResponsePacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2225::ItemStackResponsePacket>{{
    "responses",
}};

template <>
struct field_accessor<v2225::ItemStackResponsePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.responses;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ItemStackRequestCereal::EmptyItemDescriptorData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ItemStackRequestCereal::EmptyItemDescriptorData>{"ItemStackRequestCereal::EmptyItemDescriptorData"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<v2168::ItemStackRequestCereal::EmptyItemDescriptorData>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ItemStackRequestCereal::ItemNameDescriptorData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ItemStackRequestCereal::ItemNameDescriptorData>{"ItemStackRequestCereal::ItemNameDescriptorData"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2168::ItemStackRequestCereal::ItemNameDescriptorData>{{
    "full_name",
    "aux_value",
}};

template <>
struct field_accessor<v2168::ItemStackRequestCereal::ItemNameDescriptorData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.full_name;
        }
        else {
            return value.aux_value;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ItemStackRequestCereal::MolangItemDescriptorData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ItemStackRequestCereal::MolangItemDescriptorData>{"ItemStackRequestCereal::MolangItemDescriptorData"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2168::ItemStackRequestCereal::MolangItemDescriptorData>{{
    "tag_expression",
    "molang_version",
}};

template <>
struct field_accessor<v2168::ItemStackRequestCereal::MolangItemDescriptorData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.tag_expression;
        }
        else {
            return value.molang_version;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ItemStackRequestCereal::ItemTagDescriptorData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ItemStackRequestCereal::ItemTagDescriptorData>{"ItemStackRequestCereal::ItemTagDescriptorData"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2168::ItemStackRequestCereal::ItemTagDescriptorData>{{
    "item_tag",
}};

template <>
struct field_accessor<v2168::ItemStackRequestCereal::ItemTagDescriptorData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.item_tag;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ItemStackRequestCereal::NetworkItemInstanceDescriptorData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ItemStackRequestCereal::NetworkItemInstanceDescriptorData>{"ItemStackRequestCereal::NetworkItemInstanceDescriptorData"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v2168::ItemStackRequestCereal::NetworkItemInstanceDescriptorData>{{
    "item_descriptor",
    "stack_size",
    "block_runtime_id",
    "user_data_buffer",
}};

template <>
struct field_accessor<v2168::ItemStackRequestCereal::NetworkItemInstanceDescriptorData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.item_descriptor;
        }
        else if constexpr (I == 1) {
            return value.stack_size;
        }
        else if constexpr (I == 2) {
            return value.block_runtime_id;
        }
        else {
            return value.user_data_buffer;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ItemStackRequestCereal::RecipeIngredientData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ItemStackRequestCereal::RecipeIngredientData>{"ItemStackRequestCereal::RecipeIngredientData"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2168::ItemStackRequestCereal::RecipeIngredientData>{{
    "item_descriptor",
    "stack_size",
}};

template <>
struct field_accessor<v2168::ItemStackRequestCereal::RecipeIngredientData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.item_descriptor;
        }
        else {
            return value.stack_size;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ItemStackRequestCereal::SlotInfoData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ItemStackRequestCereal::SlotInfoData>{"ItemStackRequestCereal::SlotInfoData"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v2168::ItemStackRequestCereal::SlotInfoData>{{
    "full_container_name",
    "slot",
    "net_id_variant",
}};

template <>
struct field_accessor<v2168::ItemStackRequestCereal::SlotInfoData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.full_container_name;
        }
        else if constexpr (I == 1) {
            return value.slot;
        }
        else {
            return value.net_id_variant;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ItemStackRequestCereal::TakeActionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ItemStackRequestCereal::TakeActionData>{"ItemStackRequestCereal::TakeActionData"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v2168::ItemStackRequestCereal::TakeActionData>{{
    "amount",
    "source",
    "destination",
}};

template <>
struct field_accessor<v2168::ItemStackRequestCereal::TakeActionData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.amount;
        }
        else if constexpr (I == 1) {
            return value.source;
        }
        else {
            return value.destination;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ItemStackRequestCereal::PlaceActionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ItemStackRequestCereal::PlaceActionData>{"ItemStackRequestCereal::PlaceActionData"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v2168::ItemStackRequestCereal::PlaceActionData>{{
    "amount",
    "source",
    "destination",
}};

template <>
struct field_accessor<v2168::ItemStackRequestCereal::PlaceActionData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.amount;
        }
        else if constexpr (I == 1) {
            return value.source;
        }
        else {
            return value.destination;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ItemStackRequestCereal::SwapActionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ItemStackRequestCereal::SwapActionData>{"ItemStackRequestCereal::SwapActionData"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2168::ItemStackRequestCereal::SwapActionData>{{
    "source",
    "destination",
}};

template <>
struct field_accessor<v2168::ItemStackRequestCereal::SwapActionData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.source;
        }
        else {
            return value.destination;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ItemStackRequestCereal::DropActionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ItemStackRequestCereal::DropActionData>{"ItemStackRequestCereal::DropActionData"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v2168::ItemStackRequestCereal::DropActionData>{{
    "amount",
    "source",
    "randomly",
}};

template <>
struct field_accessor<v2168::ItemStackRequestCereal::DropActionData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.amount;
        }
        else if constexpr (I == 1) {
            return value.source;
        }
        else {
            return value.randomly;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ItemStackRequestCereal::DestroyActionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ItemStackRequestCereal::DestroyActionData>{"ItemStackRequestCereal::DestroyActionData"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2168::ItemStackRequestCereal::DestroyActionData>{{
    "amount",
    "source",
}};

template <>
struct field_accessor<v2168::ItemStackRequestCereal::DestroyActionData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.amount;
        }
        else {
            return value.source;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ItemStackRequestCereal::ConsumeActionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ItemStackRequestCereal::ConsumeActionData>{"ItemStackRequestCereal::ConsumeActionData"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2168::ItemStackRequestCereal::ConsumeActionData>{{
    "amount",
    "source",
}};

template <>
struct field_accessor<v2168::ItemStackRequestCereal::ConsumeActionData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.amount;
        }
        else {
            return value.source;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ItemStackRequestCereal::CreateActionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ItemStackRequestCereal::CreateActionData>{"ItemStackRequestCereal::CreateActionData"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2168::ItemStackRequestCereal::CreateActionData>{{
    "results_index",
}};

template <>
struct field_accessor<v2168::ItemStackRequestCereal::CreateActionData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.results_index;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ItemStackRequestCereal::LabTableCombineActionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ItemStackRequestCereal::LabTableCombineActionData>{"ItemStackRequestCereal::LabTableCombineActionData"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<v2168::ItemStackRequestCereal::LabTableCombineActionData>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ItemStackRequestCereal::BeaconPaymentActionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ItemStackRequestCereal::BeaconPaymentActionData>{"ItemStackRequestCereal::BeaconPaymentActionData"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2168::ItemStackRequestCereal::BeaconPaymentActionData>{{
    "primary_effect_id",
    "secondary_effect_id",
}};

template <>
struct field_accessor<v2168::ItemStackRequestCereal::BeaconPaymentActionData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.primary_effect_id;
        }
        else {
            return value.secondary_effect_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ItemStackRequestCereal::MineBlockActionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ItemStackRequestCereal::MineBlockActionData>{"ItemStackRequestCereal::MineBlockActionData"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v2168::ItemStackRequestCereal::MineBlockActionData>{{
    "slot",
    "predicted_durability",
    "net_id_variant",
}};

template <>
struct field_accessor<v2168::ItemStackRequestCereal::MineBlockActionData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.slot;
        }
        else if constexpr (I == 1) {
            return value.predicted_durability;
        }
        else {
            return value.net_id_variant;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ItemStackRequestCereal::CraftRecipeActionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ItemStackRequestCereal::CraftRecipeActionData>{"ItemStackRequestCereal::CraftRecipeActionData"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2168::ItemStackRequestCereal::CraftRecipeActionData>{{
    "recipe_net_id",
    "num_crafts",
}};

template <>
struct field_accessor<v2168::ItemStackRequestCereal::CraftRecipeActionData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.recipe_net_id;
        }
        else {
            return value.num_crafts;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ItemStackRequestCereal::CraftRecipeAutoActionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ItemStackRequestCereal::CraftRecipeAutoActionData>{"ItemStackRequestCereal::CraftRecipeAutoActionData"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v2168::ItemStackRequestCereal::CraftRecipeAutoActionData>{{
    "recipe_net_id",
    "num_crafts",
    "ingredients",
}};

template <>
struct field_accessor<v2168::ItemStackRequestCereal::CraftRecipeAutoActionData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.recipe_net_id;
        }
        else if constexpr (I == 1) {
            return value.num_crafts;
        }
        else {
            return value.ingredients;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ItemStackRequestCereal::CraftCreativeActionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ItemStackRequestCereal::CraftCreativeActionData>{"ItemStackRequestCereal::CraftCreativeActionData"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2168::ItemStackRequestCereal::CraftCreativeActionData>{{
    "creative_item_net_id",
    "num_crafts",
}};

template <>
struct field_accessor<v2168::ItemStackRequestCereal::CraftCreativeActionData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.creative_item_net_id;
        }
        else {
            return value.num_crafts;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ItemStackRequestCereal::CraftRecipeOptionalActionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ItemStackRequestCereal::CraftRecipeOptionalActionData>{"ItemStackRequestCereal::CraftRecipeOptionalActionData"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2168::ItemStackRequestCereal::CraftRecipeOptionalActionData>{{
    "recipe_net_id",
    "filtered_string_index",
}};

template <>
struct field_accessor<v2168::ItemStackRequestCereal::CraftRecipeOptionalActionData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.recipe_net_id;
        }
        else {
            return value.filtered_string_index;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ItemStackRequestCereal::CraftRepairAndDisenchantActionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ItemStackRequestCereal::CraftRepairAndDisenchantActionData>{"ItemStackRequestCereal::CraftRepairAndDisenchantActionData"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v2168::ItemStackRequestCereal::CraftRepairAndDisenchantActionData>{{
    "recipe_net_id",
    "num_crafts",
    "repair_cost",
}};

template <>
struct field_accessor<v2168::ItemStackRequestCereal::CraftRepairAndDisenchantActionData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.recipe_net_id;
        }
        else if constexpr (I == 1) {
            return value.num_crafts;
        }
        else {
            return value.repair_cost;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ItemStackRequestCereal::CraftLoomActionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ItemStackRequestCereal::CraftLoomActionData>{"ItemStackRequestCereal::CraftLoomActionData"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2168::ItemStackRequestCereal::CraftLoomActionData>{{
    "pattern_name_id",
    "num_crafts",
}};

template <>
struct field_accessor<v2168::ItemStackRequestCereal::CraftLoomActionData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.pattern_name_id;
        }
        else {
            return value.num_crafts;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ItemStackRequestCereal::CraftNonImplementedActionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ItemStackRequestCereal::CraftNonImplementedActionData>{"ItemStackRequestCereal::CraftNonImplementedActionData"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<v2168::ItemStackRequestCereal::CraftNonImplementedActionData>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ItemStackRequestCereal::CraftResultsActionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ItemStackRequestCereal::CraftResultsActionData>{"ItemStackRequestCereal::CraftResultsActionData"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2168::ItemStackRequestCereal::CraftResultsActionData>{{
    "craft_results",
    "num_crafts",
}};

template <>
struct field_accessor<v2168::ItemStackRequestCereal::CraftResultsActionData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.craft_results;
        }
        else {
            return value.num_crafts;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ItemStackRequestCereal::RequestData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ItemStackRequestCereal::RequestData>{"ItemStackRequestCereal::RequestData"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v2168::ItemStackRequestCereal::RequestData>{{
    "client_request_id",
    "actions",
    "strings_to_filter",
    "strings_to_filter_origin",
}};

template <>
struct field_accessor<v2168::ItemStackRequestCereal::RequestData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.client_request_id;
        }
        else if constexpr (I == 1) {
            return value.actions;
        }
        else if constexpr (I == 2) {
            return value.strings_to_filter;
        }
        else {
            return value.strings_to_filter_origin;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::ItemStackRequestCereal::MolangItemDescriptorData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::ItemStackRequestCereal::MolangItemDescriptorData>{"ItemStackRequestCereal::MolangItemDescriptorData"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2225::ItemStackRequestCereal::MolangItemDescriptorData>{{
    "tag_expression",
    "molang_version",
}};

template <>
struct field_accessor<v2225::ItemStackRequestCereal::MolangItemDescriptorData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.tag_expression;
        }
        else {
            return value.molang_version;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::ItemStackRequestCereal::SlotInfoData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::ItemStackRequestCereal::SlotInfoData>{"ItemStackRequestCereal::SlotInfoData"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v2225::ItemStackRequestCereal::SlotInfoData>{{
    "full_container_name",
    "slot",
    "net_id_variant",
}};

template <>
struct field_accessor<v2225::ItemStackRequestCereal::SlotInfoData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.full_container_name;
        }
        else if constexpr (I == 1) {
            return value.slot;
        }
        else {
            return value.net_id_variant;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::ItemStackRequestCereal::TakeActionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::ItemStackRequestCereal::TakeActionData>{"ItemStackRequestCereal::TakeActionData"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v2225::ItemStackRequestCereal::TakeActionData>{{
    "amount",
    "source",
    "destination",
}};

template <>
struct field_accessor<v2225::ItemStackRequestCereal::TakeActionData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.amount;
        }
        else if constexpr (I == 1) {
            return value.source;
        }
        else {
            return value.destination;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::ItemStackRequestCereal::PlaceActionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::ItemStackRequestCereal::PlaceActionData>{"ItemStackRequestCereal::PlaceActionData"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v2225::ItemStackRequestCereal::PlaceActionData>{{
    "amount",
    "source",
    "destination",
}};

template <>
struct field_accessor<v2225::ItemStackRequestCereal::PlaceActionData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.amount;
        }
        else if constexpr (I == 1) {
            return value.source;
        }
        else {
            return value.destination;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::ItemStackRequestCereal::SwapActionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::ItemStackRequestCereal::SwapActionData>{"ItemStackRequestCereal::SwapActionData"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2225::ItemStackRequestCereal::SwapActionData>{{
    "source",
    "destination",
}};

template <>
struct field_accessor<v2225::ItemStackRequestCereal::SwapActionData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.source;
        }
        else {
            return value.destination;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::ItemStackRequestCereal::DropActionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::ItemStackRequestCereal::DropActionData>{"ItemStackRequestCereal::DropActionData"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v2225::ItemStackRequestCereal::DropActionData>{{
    "amount",
    "source",
    "randomly",
}};

template <>
struct field_accessor<v2225::ItemStackRequestCereal::DropActionData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.amount;
        }
        else if constexpr (I == 1) {
            return value.source;
        }
        else {
            return value.randomly;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::ItemStackRequestCereal::DestroyActionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::ItemStackRequestCereal::DestroyActionData>{"ItemStackRequestCereal::DestroyActionData"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2225::ItemStackRequestCereal::DestroyActionData>{{
    "amount",
    "source",
}};

template <>
struct field_accessor<v2225::ItemStackRequestCereal::DestroyActionData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.amount;
        }
        else {
            return value.source;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::ItemStackRequestCereal::ConsumeActionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::ItemStackRequestCereal::ConsumeActionData>{"ItemStackRequestCereal::ConsumeActionData"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2225::ItemStackRequestCereal::ConsumeActionData>{{
    "amount",
    "source",
}};

template <>
struct field_accessor<v2225::ItemStackRequestCereal::ConsumeActionData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.amount;
        }
        else {
            return value.source;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::ItemStackRequestCereal::CreateActionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::ItemStackRequestCereal::CreateActionData>{"ItemStackRequestCereal::CreateActionData"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2225::ItemStackRequestCereal::CreateActionData>{{
    "results_index",
}};

template <>
struct field_accessor<v2225::ItemStackRequestCereal::CreateActionData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.results_index;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::ItemStackRequestCereal::LabTableCombineActionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::ItemStackRequestCereal::LabTableCombineActionData>{"ItemStackRequestCereal::LabTableCombineActionData"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<v2225::ItemStackRequestCereal::LabTableCombineActionData>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<v2225::ItemStackRequestCereal::BeaconPaymentActionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::ItemStackRequestCereal::BeaconPaymentActionData>{"ItemStackRequestCereal::BeaconPaymentActionData"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2225::ItemStackRequestCereal::BeaconPaymentActionData>{{
    "primary_effect_id",
    "secondary_effect_id",
}};

template <>
struct field_accessor<v2225::ItemStackRequestCereal::BeaconPaymentActionData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.primary_effect_id;
        }
        else {
            return value.secondary_effect_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::ItemStackRequestCereal::MineBlockActionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::ItemStackRequestCereal::MineBlockActionData>{"ItemStackRequestCereal::MineBlockActionData"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v2225::ItemStackRequestCereal::MineBlockActionData>{{
    "slot",
    "predicted_durability",
    "net_id_variant",
}};

template <>
struct field_accessor<v2225::ItemStackRequestCereal::MineBlockActionData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.slot;
        }
        else if constexpr (I == 1) {
            return value.predicted_durability;
        }
        else {
            return value.net_id_variant;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::ItemStackRequestCereal::CraftRecipeActionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::ItemStackRequestCereal::CraftRecipeActionData>{"ItemStackRequestCereal::CraftRecipeActionData"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2225::ItemStackRequestCereal::CraftRecipeActionData>{{
    "recipe_net_id",
    "num_crafts",
}};

template <>
struct field_accessor<v2225::ItemStackRequestCereal::CraftRecipeActionData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.recipe_net_id;
        }
        else {
            return value.num_crafts;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::ItemStackRequestCereal::CraftRecipeAutoActionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::ItemStackRequestCereal::CraftRecipeAutoActionData>{"ItemStackRequestCereal::CraftRecipeAutoActionData"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v2225::ItemStackRequestCereal::CraftRecipeAutoActionData>{{
    "recipe_net_id",
    "num_crafts",
    "ingredients",
}};

template <>
struct field_accessor<v2225::ItemStackRequestCereal::CraftRecipeAutoActionData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.recipe_net_id;
        }
        else if constexpr (I == 1) {
            return value.num_crafts;
        }
        else {
            return value.ingredients;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::ItemStackRequestCereal::CraftCreativeActionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::ItemStackRequestCereal::CraftCreativeActionData>{"ItemStackRequestCereal::CraftCreativeActionData"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2225::ItemStackRequestCereal::CraftCreativeActionData>{{
    "creative_item_net_id",
    "num_crafts",
}};

template <>
struct field_accessor<v2225::ItemStackRequestCereal::CraftCreativeActionData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.creative_item_net_id;
        }
        else {
            return value.num_crafts;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::ItemStackRequestCereal::CraftRecipeOptionalActionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::ItemStackRequestCereal::CraftRecipeOptionalActionData>{"ItemStackRequestCereal::CraftRecipeOptionalActionData"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2225::ItemStackRequestCereal::CraftRecipeOptionalActionData>{{
    "recipe_net_id",
    "filtered_string_index",
}};

template <>
struct field_accessor<v2225::ItemStackRequestCereal::CraftRecipeOptionalActionData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.recipe_net_id;
        }
        else {
            return value.filtered_string_index;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::ItemStackRequestCereal::CraftRepairAndDisenchantActionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::ItemStackRequestCereal::CraftRepairAndDisenchantActionData>{"ItemStackRequestCereal::CraftRepairAndDisenchantActionData"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v2225::ItemStackRequestCereal::CraftRepairAndDisenchantActionData>{{
    "recipe_net_id",
    "num_crafts",
    "repair_cost",
}};

template <>
struct field_accessor<v2225::ItemStackRequestCereal::CraftRepairAndDisenchantActionData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.recipe_net_id;
        }
        else if constexpr (I == 1) {
            return value.num_crafts;
        }
        else {
            return value.repair_cost;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::ItemStackRequestCereal::CraftLoomActionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::ItemStackRequestCereal::CraftLoomActionData>{"ItemStackRequestCereal::CraftLoomActionData"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2225::ItemStackRequestCereal::CraftLoomActionData>{{
    "pattern_name_id",
    "num_crafts",
}};

template <>
struct field_accessor<v2225::ItemStackRequestCereal::CraftLoomActionData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.pattern_name_id;
        }
        else {
            return value.num_crafts;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::ItemStackRequestCereal::CraftDiscPressActionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::ItemStackRequestCereal::CraftDiscPressActionData>{"ItemStackRequestCereal::CraftDiscPressActionData"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2225::ItemStackRequestCereal::CraftDiscPressActionData>{{
    "reserved_id",
    "num_crafts",
}};

template <>
struct field_accessor<v2225::ItemStackRequestCereal::CraftDiscPressActionData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.reserved_id;
        }
        else {
            return value.num_crafts;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::ItemStackRequestCereal::CraftNonImplementedActionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::ItemStackRequestCereal::CraftNonImplementedActionData>{"ItemStackRequestCereal::CraftNonImplementedActionData"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<v2225::ItemStackRequestCereal::CraftNonImplementedActionData>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<v2225::ItemStackRequestCereal::CraftResultsActionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::ItemStackRequestCereal::CraftResultsActionData>{"ItemStackRequestCereal::CraftResultsActionData"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2225::ItemStackRequestCereal::CraftResultsActionData>{{
    "craft_results",
    "num_crafts",
}};

template <>
struct field_accessor<v2225::ItemStackRequestCereal::CraftResultsActionData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.craft_results;
        }
        else {
            return value.num_crafts;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::ItemStackRequestCereal::RequestData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::ItemStackRequestCereal::RequestData>{"ItemStackRequestCereal::RequestData"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v2225::ItemStackRequestCereal::RequestData>{{
    "client_request_id",
    "actions",
    "strings_to_filter",
    "strings_to_filter_origin",
}};

template <>
struct field_accessor<v2225::ItemStackRequestCereal::RequestData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.client_request_id;
        }
        else if constexpr (I == 1) {
            return value.actions;
        }
        else if constexpr (I == 2) {
            return value.strings_to_filter;
        }
        else {
            return value.strings_to_filter_origin;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ItemStackRequestCereal> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ItemStackRequestCereal>{"ItemStackRequestCereal"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<v2168::ItemStackRequestCereal>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<v2225::ItemStackRequestCereal> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::ItemStackRequestCereal>{"ItemStackRequestCereal"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<v2225::ItemStackRequestCereal>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<base::ItemStackRequestSlotInfo> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ItemStackRequestSlotInfo>{"ItemStackRequestSlotInfo"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<base::ItemStackRequestSlotInfo>{{
    "full_container_name",
    "slot",
    "net_id_variant",
}};

template <>
struct field_accessor<base::ItemStackRequestSlotInfo> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.full_container_name;
        }
        else if constexpr (I == 1) {
            return value.slot;
        }
        else {
            return value.net_id_variant;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::ItemStackRequestSlotInfo> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::ItemStackRequestSlotInfo>{"ItemStackRequestSlotInfo"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v924::ItemStackRequestSlotInfo>{{
    "full_container_name",
    "slot",
    "net_id_variant",
}};

template <>
struct field_accessor<v924::ItemStackRequestSlotInfo> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.full_container_name;
        }
        else if constexpr (I == 1) {
            return value.slot;
        }
        else {
            return value.net_id_variant;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::ItemStackRequestActionTake> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ItemStackRequestActionTake>{"ItemStackRequestActionTake"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<base::ItemStackRequestActionTake>{{
    "amount",
    "src",
    "dst",
}};

template <>
struct field_accessor<base::ItemStackRequestActionTake> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.amount;
        }
        else if constexpr (I == 1) {
            return value.src;
        }
        else {
            return value.dst;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::ItemStackRequestActionTake> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::ItemStackRequestActionTake>{"ItemStackRequestActionTake"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v924::ItemStackRequestActionTake>{{
    "amount",
    "src",
    "dst",
}};

template <>
struct field_accessor<v924::ItemStackRequestActionTake> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.amount;
        }
        else if constexpr (I == 1) {
            return value.src;
        }
        else {
            return value.dst;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::ItemStackRequestActionPlace> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ItemStackRequestActionPlace>{"ItemStackRequestActionPlace"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<base::ItemStackRequestActionPlace>{{
    "amount",
    "src",
    "dst",
}};

template <>
struct field_accessor<base::ItemStackRequestActionPlace> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.amount;
        }
        else if constexpr (I == 1) {
            return value.src;
        }
        else {
            return value.dst;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::ItemStackRequestActionPlace> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::ItemStackRequestActionPlace>{"ItemStackRequestActionPlace"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v924::ItemStackRequestActionPlace>{{
    "amount",
    "src",
    "dst",
}};

template <>
struct field_accessor<v924::ItemStackRequestActionPlace> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.amount;
        }
        else if constexpr (I == 1) {
            return value.src;
        }
        else {
            return value.dst;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::ItemStackRequestActionSwap> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ItemStackRequestActionSwap>{"ItemStackRequestActionSwap"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<base::ItemStackRequestActionSwap>{{
    "src",
    "dst",
}};

template <>
struct field_accessor<base::ItemStackRequestActionSwap> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.src;
        }
        else {
            return value.dst;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::ItemStackRequestActionSwap> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::ItemStackRequestActionSwap>{"ItemStackRequestActionSwap"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v924::ItemStackRequestActionSwap>{{
    "src",
    "dst",
}};

template <>
struct field_accessor<v924::ItemStackRequestActionSwap> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.src;
        }
        else {
            return value.dst;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::ItemStackRequestActionDrop> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ItemStackRequestActionDrop>{"ItemStackRequestActionDrop"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<base::ItemStackRequestActionDrop>{{
    "amount",
    "src",
    "randomly",
}};

template <>
struct field_accessor<base::ItemStackRequestActionDrop> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.amount;
        }
        else if constexpr (I == 1) {
            return value.src;
        }
        else {
            return value.randomly;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::ItemStackRequestActionDrop> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::ItemStackRequestActionDrop>{"ItemStackRequestActionDrop"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v924::ItemStackRequestActionDrop>{{
    "amount",
    "src",
    "randomly",
}};

template <>
struct field_accessor<v924::ItemStackRequestActionDrop> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.amount;
        }
        else if constexpr (I == 1) {
            return value.src;
        }
        else {
            return value.randomly;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::ItemStackRequestActionDestroy> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ItemStackRequestActionDestroy>{"ItemStackRequestActionDestroy"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<base::ItemStackRequestActionDestroy>{{
    "amount",
    "src",
}};

template <>
struct field_accessor<base::ItemStackRequestActionDestroy> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.amount;
        }
        else {
            return value.src;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::ItemStackRequestActionDestroy> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::ItemStackRequestActionDestroy>{"ItemStackRequestActionDestroy"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v924::ItemStackRequestActionDestroy>{{
    "amount",
    "src",
}};

template <>
struct field_accessor<v924::ItemStackRequestActionDestroy> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.amount;
        }
        else {
            return value.src;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::ItemStackRequestActionConsume> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ItemStackRequestActionConsume>{"ItemStackRequestActionConsume"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<base::ItemStackRequestActionConsume>{{
    "amount",
    "src",
}};

template <>
struct field_accessor<base::ItemStackRequestActionConsume> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.amount;
        }
        else {
            return value.src;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::ItemStackRequestActionConsume> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::ItemStackRequestActionConsume>{"ItemStackRequestActionConsume"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v924::ItemStackRequestActionConsume>{{
    "amount",
    "src",
}};

template <>
struct field_accessor<v924::ItemStackRequestActionConsume> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.amount;
        }
        else {
            return value.src;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::ItemStackRequestActionCreate> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ItemStackRequestActionCreate>{"ItemStackRequestActionCreate"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::ItemStackRequestActionCreate>{{
    "results_index",
}};

template <>
struct field_accessor<base::ItemStackRequestActionCreate> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.results_index;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::ItemStackRequestActionLabTableCombine> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ItemStackRequestActionLabTableCombine>{"ItemStackRequestActionLabTableCombine"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<base::ItemStackRequestActionLabTableCombine>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<base::ItemStackRequestActionBeaconPayment> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ItemStackRequestActionBeaconPayment>{"ItemStackRequestActionBeaconPayment"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<base::ItemStackRequestActionBeaconPayment>{{
    "primary_effect_id",
    "secondary_effect_id",
}};

template <>
struct field_accessor<base::ItemStackRequestActionBeaconPayment> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.primary_effect_id;
        }
        else {
            return value.secondary_effect_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::ItemStackRequestActionMineBlock> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ItemStackRequestActionMineBlock>{"ItemStackRequestActionMineBlock"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<base::ItemStackRequestActionMineBlock>{{
    "slot",
    "predicted_durability",
    "net_id_variant",
}};

template <>
struct field_accessor<base::ItemStackRequestActionMineBlock> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.slot;
        }
        else if constexpr (I == 1) {
            return value.predicted_durability;
        }
        else {
            return value.net_id_variant;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::ItemStackRequestActionCraftRecipe> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ItemStackRequestActionCraftRecipe>{"ItemStackRequestActionCraftRecipe"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<base::ItemStackRequestActionCraftRecipe>{{
    "recipe_net_id",
    "num_crafts",
}};

template <>
struct field_accessor<base::ItemStackRequestActionCraftRecipe> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.recipe_net_id;
        }
        else {
            return value.num_crafts;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::ItemStackRequestActionCraftRecipeAuto> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ItemStackRequestActionCraftRecipeAuto>{"ItemStackRequestActionCraftRecipeAuto"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<base::ItemStackRequestActionCraftRecipeAuto>{{
    "recipe_net_id",
    "num_crafts",
    "num_ingredients",
    "ingredients",
}};

template <>
struct field_accessor<base::ItemStackRequestActionCraftRecipeAuto> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.recipe_net_id;
        }
        else if constexpr (I == 1) {
            return value.num_crafts;
        }
        else if constexpr (I == 2) {
            return value.num_ingredients;
        }
        else {
            return value.ingredients;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::ItemStackRequestActionCraftCreative> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ItemStackRequestActionCraftCreative>{"ItemStackRequestActionCraftCreative"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<base::ItemStackRequestActionCraftCreative>{{
    "creative_item_net_id",
    "num_crafts",
}};

template <>
struct field_accessor<base::ItemStackRequestActionCraftCreative> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.creative_item_net_id;
        }
        else {
            return value.num_crafts;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::ItemStackRequestActionCraftRecipeOptional> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ItemStackRequestActionCraftRecipeOptional>{"ItemStackRequestActionCraftRecipeOptional"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<base::ItemStackRequestActionCraftRecipeOptional>{{
    "recipe_net_id",
    "filtered_string_index",
}};

template <>
struct field_accessor<base::ItemStackRequestActionCraftRecipeOptional> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.recipe_net_id;
        }
        else {
            return value.filtered_string_index;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::ItemStackRequestActionCraftGrindstone> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ItemStackRequestActionCraftGrindstone>{"ItemStackRequestActionCraftGrindstone"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<base::ItemStackRequestActionCraftGrindstone>{{
    "recipe_net_id",
    "num_crafts",
    "repair_cost",
}};

template <>
struct field_accessor<base::ItemStackRequestActionCraftGrindstone> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.recipe_net_id;
        }
        else if constexpr (I == 1) {
            return value.num_crafts;
        }
        else {
            return value.repair_cost;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::ItemStackRequestActionCraftLoom> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ItemStackRequestActionCraftLoom>{"ItemStackRequestActionCraftLoom"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<base::ItemStackRequestActionCraftLoom>{{
    "pattern_name_id",
    "num_crafts",
}};

template <>
struct field_accessor<base::ItemStackRequestActionCraftLoom> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.pattern_name_id;
        }
        else {
            return value.num_crafts;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING>{"ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>{"ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>{{
    "craft_results",
    "num_crafts",
}};

template <>
struct field_accessor<base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.craft_results;
        }
        else {
            return value.num_crafts;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::ItemStackRequestData> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ItemStackRequestData>{"ItemStackRequestData"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<base::ItemStackRequestData>{{
    "client_request_id",
    "actions",
    "strings_to_filter",
    "strings_to_filter_origin",
}};

template <>
struct field_accessor<base::ItemStackRequestData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.client_request_id;
        }
        else if constexpr (I == 1) {
            return value.actions;
        }
        else if constexpr (I == 2) {
            return value.strings_to_filter;
        }
        else {
            return value.strings_to_filter_origin;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::ItemStackRequestData> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::ItemStackRequestData>{"ItemStackRequestData"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v924::ItemStackRequestData>{{
    "client_request_id",
    "actions",
    "strings_to_filter",
    "strings_to_filter_origin",
}};

template <>
struct field_accessor<v924::ItemStackRequestData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.client_request_id;
        }
        else if constexpr (I == 1) {
            return value.actions;
        }
        else if constexpr (I == 2) {
            return value.strings_to_filter;
        }
        else {
            return value.strings_to_filter_origin;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v975::ItemStackRequestData> = true;

template <>
inline constexpr std::string_view struct_name_v<v975::ItemStackRequestData>{"ItemStackRequestData"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v975::ItemStackRequestData>{{
    "client_request_id",
    "actions",
    "strings_to_filter",
    "strings_to_filter_origin",
}};

template <>
struct field_accessor<v975::ItemStackRequestData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.client_request_id;
        }
        else if constexpr (I == 1) {
            return value.actions;
        }
        else if constexpr (I == 2) {
            return value.strings_to_filter;
        }
        else {
            return value.strings_to_filter_origin;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::ItemStackRequestPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ItemStackRequestPacket>{"ItemStackRequestPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::ItemStackRequestPacket>{{
    "requests",
}};

template <>
struct field_accessor<base::ItemStackRequestPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.requests;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::ItemStackRequestPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::ItemStackRequestPacket>{"ItemStackRequestPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v924::ItemStackRequestPacket>{{
    "requests",
}};

template <>
struct field_accessor<v924::ItemStackRequestPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.requests;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v975::ItemStackRequestPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v975::ItemStackRequestPacket>{"ItemStackRequestPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v975::ItemStackRequestPacket>{{
    "requests",
}};

template <>
struct field_accessor<v975::ItemStackRequestPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.requests;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ItemStackRequestPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ItemStackRequestPacket>{"ItemStackRequestPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2168::ItemStackRequestPacket>{{
    "requests",
}};

template <>
struct field_accessor<v2168::ItemStackRequestPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.requests;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::ItemStackRequestPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::ItemStackRequestPacket>{"ItemStackRequestPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2225::ItemStackRequestPacket>{{
    "requests",
}};

template <>
struct field_accessor<v2225::ItemStackRequestPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.requests;
    }
};

}  // namespace detail


template <>
struct Serializer<v766::RedactableString> {
    static void serialize(BinaryWriter &stream, const v766::RedactableString &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v766::RedactableString, std::error_code>;
};

template <>
struct Serializer<v2168::RedactableString> {
    static void serialize(BinaryWriter &stream, const v2168::RedactableString &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::RedactableString, std::error_code>;
};

template <>
struct Serializer<base::ItemStackResponseSlotInfo> {
    static void serialize(BinaryWriter &stream, const base::ItemStackResponseSlotInfo &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ItemStackResponseSlotInfo, std::error_code>;
};

template <>
struct Serializer<v766::ItemStackResponseSlotInfo> {
    static void serialize(BinaryWriter &stream, const v766::ItemStackResponseSlotInfo &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v766::ItemStackResponseSlotInfo, std::error_code>;
};

template <>
struct Serializer<v2168::ItemStackResponseSlotInfo> {
    static void serialize(BinaryWriter &stream, const v2168::ItemStackResponseSlotInfo &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackResponseSlotInfo, std::error_code>;
};

template <>
struct Serializer<v2193::ItemStackResponseSlotInfo> {
    static void serialize(BinaryWriter &stream, const v2193::ItemStackResponseSlotInfo &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::ItemStackResponseSlotInfo, std::error_code>;
};

template <>
struct Serializer<base::ItemStackResponseContainerInfo> {
    static void serialize(BinaryWriter &stream, const base::ItemStackResponseContainerInfo &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ItemStackResponseContainerInfo, std::error_code>;
};

template <>
struct Serializer<v766::ItemStackResponseContainerInfo> {
    static void serialize(BinaryWriter &stream, const v766::ItemStackResponseContainerInfo &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v766::ItemStackResponseContainerInfo, std::error_code>;
};

template <>
struct Serializer<v924::ItemStackResponseContainerInfo> {
    static void serialize(BinaryWriter &stream, const v924::ItemStackResponseContainerInfo &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::ItemStackResponseContainerInfo, std::error_code>;
};

template <>
struct Serializer<v2168::ItemStackResponseContainerInfo> {
    static void serialize(BinaryWriter &stream, const v2168::ItemStackResponseContainerInfo &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackResponseContainerInfo, std::error_code>;
};

template <>
struct Serializer<v2193::ItemStackResponseContainerInfo> {
    static void serialize(BinaryWriter &stream, const v2193::ItemStackResponseContainerInfo &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::ItemStackResponseContainerInfo, std::error_code>;
};

template <>
struct Serializer<v2225::ItemStackResponseContainerInfo> {
    static void serialize(BinaryWriter &stream, const v2225::ItemStackResponseContainerInfo &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackResponseContainerInfo, std::error_code>;
};

template <>
struct Serializer<base::ItemStackResponseInfo> {
    static void serialize(BinaryWriter &stream, const base::ItemStackResponseInfo &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ItemStackResponseInfo, std::error_code>;
};

template <>
struct Serializer<v766::ItemStackResponseInfo> {
    static void serialize(BinaryWriter &stream, const v766::ItemStackResponseInfo &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v766::ItemStackResponseInfo, std::error_code>;
};

template <>
struct Serializer<v924::ItemStackResponseInfo> {
    static void serialize(BinaryWriter &stream, const v924::ItemStackResponseInfo &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::ItemStackResponseInfo, std::error_code>;
};

template <>
struct Serializer<v2168::ItemStackResponseInfo> {
    static void serialize(BinaryWriter &stream, const v2168::ItemStackResponseInfo &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackResponseInfo, std::error_code>;
};

template <>
struct Serializer<v2193::ItemStackResponseInfo> {
    static void serialize(BinaryWriter &stream, const v2193::ItemStackResponseInfo &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::ItemStackResponseInfo, std::error_code>;
};

template <>
struct Serializer<v2225::ItemStackResponseInfo> {
    static void serialize(BinaryWriter &stream, const v2225::ItemStackResponseInfo &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackResponseInfo, std::error_code>;
};

template <>
struct Serializer<base::ItemStackResponsePacket> {
    static void serialize(BinaryWriter &stream, const base::ItemStackResponsePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ItemStackResponsePacket, std::error_code>;
};

template <>
struct Serializer<v766::ItemStackResponsePacket> {
    static void serialize(BinaryWriter &stream, const v766::ItemStackResponsePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v766::ItemStackResponsePacket, std::error_code>;
};

template <>
struct Serializer<v924::ItemStackResponsePacket> {
    static void serialize(BinaryWriter &stream, const v924::ItemStackResponsePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::ItemStackResponsePacket, std::error_code>;
};

template <>
struct Serializer<v2168::ItemStackResponsePacket> {
    static void serialize(BinaryWriter &stream, const v2168::ItemStackResponsePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackResponsePacket, std::error_code>;
};

template <>
struct Serializer<v2193::ItemStackResponsePacket> {
    static void serialize(BinaryWriter &stream, const v2193::ItemStackResponsePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::ItemStackResponsePacket, std::error_code>;
};

template <>
struct Serializer<v2225::ItemStackResponsePacket> {
    static void serialize(BinaryWriter &stream, const v2225::ItemStackResponsePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackResponsePacket, std::error_code>;
};

template <>
struct Serializer<v2168::ItemStackRequestCereal::EmptyItemDescriptorData> {
    static void serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::EmptyItemDescriptorData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::EmptyItemDescriptorData, std::error_code>;
};

template <>
struct Serializer<v2168::ItemStackRequestCereal::ItemNameDescriptorData> {
    static void serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::ItemNameDescriptorData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::ItemNameDescriptorData, std::error_code>;
};

template <>
struct Serializer<v2168::ItemStackRequestCereal::MolangItemDescriptorData> {
    static void serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::MolangItemDescriptorData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::MolangItemDescriptorData, std::error_code>;
};

template <>
struct Serializer<v2168::ItemStackRequestCereal::ItemTagDescriptorData> {
    static void serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::ItemTagDescriptorData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::ItemTagDescriptorData, std::error_code>;
};

template <>
struct Serializer<v2168::ItemStackRequestCereal::NetworkItemInstanceDescriptorData> {
    static void serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::NetworkItemInstanceDescriptorData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::NetworkItemInstanceDescriptorData, std::error_code>;
};

template <>
struct Serializer<v2168::ItemStackRequestCereal::RecipeIngredientData> {
    static void serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::RecipeIngredientData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::RecipeIngredientData, std::error_code>;
};

template <>
struct Serializer<v2168::ItemStackRequestCereal::SlotInfoData> {
    static void serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::SlotInfoData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::SlotInfoData, std::error_code>;
};

template <>
struct Serializer<v2168::ItemStackRequestCereal::TakeActionData> {
    static void serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::TakeActionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::TakeActionData, std::error_code>;
};

template <>
struct Serializer<v2168::ItemStackRequestCereal::PlaceActionData> {
    static void serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::PlaceActionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::PlaceActionData, std::error_code>;
};

template <>
struct Serializer<v2168::ItemStackRequestCereal::SwapActionData> {
    static void serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::SwapActionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::SwapActionData, std::error_code>;
};

template <>
struct Serializer<v2168::ItemStackRequestCereal::DropActionData> {
    static void serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::DropActionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::DropActionData, std::error_code>;
};

template <>
struct Serializer<v2168::ItemStackRequestCereal::DestroyActionData> {
    static void serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::DestroyActionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::DestroyActionData, std::error_code>;
};

template <>
struct Serializer<v2168::ItemStackRequestCereal::ConsumeActionData> {
    static void serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::ConsumeActionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::ConsumeActionData, std::error_code>;
};

template <>
struct Serializer<v2168::ItemStackRequestCereal::CreateActionData> {
    static void serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::CreateActionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::CreateActionData, std::error_code>;
};

template <>
struct Serializer<v2168::ItemStackRequestCereal::LabTableCombineActionData> {
    static void serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::LabTableCombineActionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::LabTableCombineActionData, std::error_code>;
};

template <>
struct Serializer<v2168::ItemStackRequestCereal::BeaconPaymentActionData> {
    static void serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::BeaconPaymentActionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::BeaconPaymentActionData, std::error_code>;
};

template <>
struct Serializer<v2168::ItemStackRequestCereal::MineBlockActionData> {
    static void serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::MineBlockActionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::MineBlockActionData, std::error_code>;
};

template <>
struct Serializer<v2168::ItemStackRequestCereal::CraftRecipeActionData> {
    static void serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::CraftRecipeActionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::CraftRecipeActionData, std::error_code>;
};

template <>
struct Serializer<v2168::ItemStackRequestCereal::CraftRecipeAutoActionData> {
    static void serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::CraftRecipeAutoActionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::CraftRecipeAutoActionData, std::error_code>;
};

template <>
struct Serializer<v2168::ItemStackRequestCereal::CraftCreativeActionData> {
    static void serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::CraftCreativeActionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::CraftCreativeActionData, std::error_code>;
};

template <>
struct Serializer<v2168::ItemStackRequestCereal::CraftRecipeOptionalActionData> {
    static void serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::CraftRecipeOptionalActionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::CraftRecipeOptionalActionData, std::error_code>;
};

template <>
struct Serializer<v2168::ItemStackRequestCereal::CraftRepairAndDisenchantActionData> {
    static void serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::CraftRepairAndDisenchantActionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::CraftRepairAndDisenchantActionData, std::error_code>;
};

template <>
struct Serializer<v2168::ItemStackRequestCereal::CraftLoomActionData> {
    static void serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::CraftLoomActionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::CraftLoomActionData, std::error_code>;
};

template <>
struct Serializer<v2168::ItemStackRequestCereal::CraftNonImplementedActionData> {
    static void serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::CraftNonImplementedActionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::CraftNonImplementedActionData, std::error_code>;
};

template <>
struct Serializer<v2168::ItemStackRequestCereal::CraftResultsActionData> {
    static void serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::CraftResultsActionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::CraftResultsActionData, std::error_code>;
};

template <>
struct Serializer<v2168::ItemStackRequestCereal::RequestData> {
    static void serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::RequestData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::RequestData, std::error_code>;
};

template <>
struct Serializer<v2225::ItemStackRequestCereal::MolangItemDescriptorData> {
    static void serialize(BinaryWriter &stream, const v2225::ItemStackRequestCereal::MolangItemDescriptorData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackRequestCereal::MolangItemDescriptorData, std::error_code>;
};

template <>
struct Serializer<v2225::ItemStackRequestCereal::SlotInfoData> {
    static void serialize(BinaryWriter &stream, const v2225::ItemStackRequestCereal::SlotInfoData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackRequestCereal::SlotInfoData, std::error_code>;
};

template <>
struct Serializer<v2225::ItemStackRequestCereal::TakeActionData> {
    static void serialize(BinaryWriter &stream, const v2225::ItemStackRequestCereal::TakeActionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackRequestCereal::TakeActionData, std::error_code>;
};

template <>
struct Serializer<v2225::ItemStackRequestCereal::PlaceActionData> {
    static void serialize(BinaryWriter &stream, const v2225::ItemStackRequestCereal::PlaceActionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackRequestCereal::PlaceActionData, std::error_code>;
};

template <>
struct Serializer<v2225::ItemStackRequestCereal::SwapActionData> {
    static void serialize(BinaryWriter &stream, const v2225::ItemStackRequestCereal::SwapActionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackRequestCereal::SwapActionData, std::error_code>;
};

template <>
struct Serializer<v2225::ItemStackRequestCereal::DropActionData> {
    static void serialize(BinaryWriter &stream, const v2225::ItemStackRequestCereal::DropActionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackRequestCereal::DropActionData, std::error_code>;
};

template <>
struct Serializer<v2225::ItemStackRequestCereal::DestroyActionData> {
    static void serialize(BinaryWriter &stream, const v2225::ItemStackRequestCereal::DestroyActionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackRequestCereal::DestroyActionData, std::error_code>;
};

template <>
struct Serializer<v2225::ItemStackRequestCereal::ConsumeActionData> {
    static void serialize(BinaryWriter &stream, const v2225::ItemStackRequestCereal::ConsumeActionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackRequestCereal::ConsumeActionData, std::error_code>;
};

template <>
struct Serializer<v2225::ItemStackRequestCereal::CreateActionData> {
    static void serialize(BinaryWriter &stream, const v2225::ItemStackRequestCereal::CreateActionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackRequestCereal::CreateActionData, std::error_code>;
};

template <>
struct Serializer<v2225::ItemStackRequestCereal::LabTableCombineActionData> {
    static void serialize(BinaryWriter &stream, const v2225::ItemStackRequestCereal::LabTableCombineActionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackRequestCereal::LabTableCombineActionData, std::error_code>;
};

template <>
struct Serializer<v2225::ItemStackRequestCereal::BeaconPaymentActionData> {
    static void serialize(BinaryWriter &stream, const v2225::ItemStackRequestCereal::BeaconPaymentActionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackRequestCereal::BeaconPaymentActionData, std::error_code>;
};

template <>
struct Serializer<v2225::ItemStackRequestCereal::MineBlockActionData> {
    static void serialize(BinaryWriter &stream, const v2225::ItemStackRequestCereal::MineBlockActionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackRequestCereal::MineBlockActionData, std::error_code>;
};

template <>
struct Serializer<v2225::ItemStackRequestCereal::CraftRecipeActionData> {
    static void serialize(BinaryWriter &stream, const v2225::ItemStackRequestCereal::CraftRecipeActionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackRequestCereal::CraftRecipeActionData, std::error_code>;
};

template <>
struct Serializer<v2225::ItemStackRequestCereal::CraftRecipeAutoActionData> {
    static void serialize(BinaryWriter &stream, const v2225::ItemStackRequestCereal::CraftRecipeAutoActionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackRequestCereal::CraftRecipeAutoActionData, std::error_code>;
};

template <>
struct Serializer<v2225::ItemStackRequestCereal::CraftCreativeActionData> {
    static void serialize(BinaryWriter &stream, const v2225::ItemStackRequestCereal::CraftCreativeActionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackRequestCereal::CraftCreativeActionData, std::error_code>;
};

template <>
struct Serializer<v2225::ItemStackRequestCereal::CraftRecipeOptionalActionData> {
    static void serialize(BinaryWriter &stream, const v2225::ItemStackRequestCereal::CraftRecipeOptionalActionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackRequestCereal::CraftRecipeOptionalActionData, std::error_code>;
};

template <>
struct Serializer<v2225::ItemStackRequestCereal::CraftRepairAndDisenchantActionData> {
    static void serialize(BinaryWriter &stream, const v2225::ItemStackRequestCereal::CraftRepairAndDisenchantActionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackRequestCereal::CraftRepairAndDisenchantActionData, std::error_code>;
};

template <>
struct Serializer<v2225::ItemStackRequestCereal::CraftLoomActionData> {
    static void serialize(BinaryWriter &stream, const v2225::ItemStackRequestCereal::CraftLoomActionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackRequestCereal::CraftLoomActionData, std::error_code>;
};

template <>
struct Serializer<v2225::ItemStackRequestCereal::CraftDiscPressActionData> {
    static void serialize(BinaryWriter &stream, const v2225::ItemStackRequestCereal::CraftDiscPressActionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackRequestCereal::CraftDiscPressActionData, std::error_code>;
};

template <>
struct Serializer<v2225::ItemStackRequestCereal::CraftNonImplementedActionData> {
    static void serialize(BinaryWriter &stream, const v2225::ItemStackRequestCereal::CraftNonImplementedActionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackRequestCereal::CraftNonImplementedActionData, std::error_code>;
};

template <>
struct Serializer<v2225::ItemStackRequestCereal::CraftResultsActionData> {
    static void serialize(BinaryWriter &stream, const v2225::ItemStackRequestCereal::CraftResultsActionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackRequestCereal::CraftResultsActionData, std::error_code>;
};

template <>
struct Serializer<v2225::ItemStackRequestCereal::RequestData> {
    static void serialize(BinaryWriter &stream, const v2225::ItemStackRequestCereal::RequestData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackRequestCereal::RequestData, std::error_code>;
};

template <>
struct Serializer<base::ItemStackRequestSlotInfo> {
    static void serialize(BinaryWriter &stream, const base::ItemStackRequestSlotInfo &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ItemStackRequestSlotInfo, std::error_code>;
};

template <>
struct Serializer<v924::ItemStackRequestSlotInfo> {
    static void serialize(BinaryWriter &stream, const v924::ItemStackRequestSlotInfo &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::ItemStackRequestSlotInfo, std::error_code>;
};

template <>
struct Serializer<base::ItemStackRequestActionTake> {
    static void serialize(BinaryWriter &stream, const base::ItemStackRequestActionTake &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ItemStackRequestActionTake, std::error_code>;
};

template <>
struct Serializer<v924::ItemStackRequestActionTake> {
    static void serialize(BinaryWriter &stream, const v924::ItemStackRequestActionTake &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::ItemStackRequestActionTake, std::error_code>;
};

template <>
struct Serializer<base::ItemStackRequestActionPlace> {
    static void serialize(BinaryWriter &stream, const base::ItemStackRequestActionPlace &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ItemStackRequestActionPlace, std::error_code>;
};

template <>
struct Serializer<v924::ItemStackRequestActionPlace> {
    static void serialize(BinaryWriter &stream, const v924::ItemStackRequestActionPlace &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::ItemStackRequestActionPlace, std::error_code>;
};

template <>
struct Serializer<base::ItemStackRequestActionSwap> {
    static void serialize(BinaryWriter &stream, const base::ItemStackRequestActionSwap &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ItemStackRequestActionSwap, std::error_code>;
};

template <>
struct Serializer<v924::ItemStackRequestActionSwap> {
    static void serialize(BinaryWriter &stream, const v924::ItemStackRequestActionSwap &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::ItemStackRequestActionSwap, std::error_code>;
};

template <>
struct Serializer<base::ItemStackRequestActionDrop> {
    static void serialize(BinaryWriter &stream, const base::ItemStackRequestActionDrop &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ItemStackRequestActionDrop, std::error_code>;
};

template <>
struct Serializer<v924::ItemStackRequestActionDrop> {
    static void serialize(BinaryWriter &stream, const v924::ItemStackRequestActionDrop &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::ItemStackRequestActionDrop, std::error_code>;
};

template <>
struct Serializer<base::ItemStackRequestActionDestroy> {
    static void serialize(BinaryWriter &stream, const base::ItemStackRequestActionDestroy &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ItemStackRequestActionDestroy, std::error_code>;
};

template <>
struct Serializer<v924::ItemStackRequestActionDestroy> {
    static void serialize(BinaryWriter &stream, const v924::ItemStackRequestActionDestroy &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::ItemStackRequestActionDestroy, std::error_code>;
};

template <>
struct Serializer<base::ItemStackRequestActionConsume> {
    static void serialize(BinaryWriter &stream, const base::ItemStackRequestActionConsume &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ItemStackRequestActionConsume, std::error_code>;
};

template <>
struct Serializer<v924::ItemStackRequestActionConsume> {
    static void serialize(BinaryWriter &stream, const v924::ItemStackRequestActionConsume &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::ItemStackRequestActionConsume, std::error_code>;
};

template <>
struct Serializer<base::ItemStackRequestActionCreate> {
    static void serialize(BinaryWriter &stream, const base::ItemStackRequestActionCreate &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ItemStackRequestActionCreate, std::error_code>;
};

template <>
struct Serializer<base::ItemStackRequestActionLabTableCombine> {
    static void serialize(BinaryWriter &stream, const base::ItemStackRequestActionLabTableCombine &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ItemStackRequestActionLabTableCombine, std::error_code>;
};

template <>
struct Serializer<base::ItemStackRequestActionBeaconPayment> {
    static void serialize(BinaryWriter &stream, const base::ItemStackRequestActionBeaconPayment &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ItemStackRequestActionBeaconPayment, std::error_code>;
};

template <>
struct Serializer<base::ItemStackRequestActionMineBlock> {
    static void serialize(BinaryWriter &stream, const base::ItemStackRequestActionMineBlock &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ItemStackRequestActionMineBlock, std::error_code>;
};

template <>
struct Serializer<base::ItemStackRequestActionCraftRecipe> {
    static void serialize(BinaryWriter &stream, const base::ItemStackRequestActionCraftRecipe &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ItemStackRequestActionCraftRecipe, std::error_code>;
};

template <>
struct Serializer<base::ItemStackRequestActionCraftRecipeAuto> {
    static void serialize(BinaryWriter &stream, const base::ItemStackRequestActionCraftRecipeAuto &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ItemStackRequestActionCraftRecipeAuto, std::error_code>;
};

template <>
struct Serializer<base::ItemStackRequestActionCraftCreative> {
    static void serialize(BinaryWriter &stream, const base::ItemStackRequestActionCraftCreative &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ItemStackRequestActionCraftCreative, std::error_code>;
};

template <>
struct Serializer<base::ItemStackRequestActionCraftRecipeOptional> {
    static void serialize(BinaryWriter &stream, const base::ItemStackRequestActionCraftRecipeOptional &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ItemStackRequestActionCraftRecipeOptional, std::error_code>;
};

template <>
struct Serializer<base::ItemStackRequestActionCraftGrindstone> {
    static void serialize(BinaryWriter &stream, const base::ItemStackRequestActionCraftGrindstone &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ItemStackRequestActionCraftGrindstone, std::error_code>;
};

template <>
struct Serializer<base::ItemStackRequestActionCraftLoom> {
    static void serialize(BinaryWriter &stream, const base::ItemStackRequestActionCraftLoom &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ItemStackRequestActionCraftLoom, std::error_code>;
};

template <>
struct Serializer<base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING> {
    static void serialize(BinaryWriter &stream, const base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, std::error_code>;
};

template <>
struct Serializer<base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING> {
    static void serialize(BinaryWriter &stream, const base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING, std::error_code>;
};

template <>
struct Serializer<base::ItemStackRequestData> {
    static void serialize(BinaryWriter &stream, const base::ItemStackRequestData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ItemStackRequestData, std::error_code>;
};

template <>
struct Serializer<v924::ItemStackRequestData> {
    static void serialize(BinaryWriter &stream, const v924::ItemStackRequestData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::ItemStackRequestData, std::error_code>;
};

template <>
struct Serializer<v975::ItemStackRequestData> {
    static void serialize(BinaryWriter &stream, const v975::ItemStackRequestData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v975::ItemStackRequestData, std::error_code>;
};

template <>
struct Serializer<base::ItemStackRequestPacket> {
    static void serialize(BinaryWriter &stream, const base::ItemStackRequestPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ItemStackRequestPacket, std::error_code>;
};

template <>
struct Serializer<v924::ItemStackRequestPacket> {
    static void serialize(BinaryWriter &stream, const v924::ItemStackRequestPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::ItemStackRequestPacket, std::error_code>;
};

template <>
struct Serializer<v975::ItemStackRequestPacket> {
    static void serialize(BinaryWriter &stream, const v975::ItemStackRequestPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v975::ItemStackRequestPacket, std::error_code>;
};

template <>
struct Serializer<v2168::ItemStackRequestPacket> {
    static void serialize(BinaryWriter &stream, const v2168::ItemStackRequestPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestPacket, std::error_code>;
};

template <>
struct Serializer<v2225::ItemStackRequestPacket> {
    static void serialize(BinaryWriter &stream, const v2225::ItemStackRequestPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackRequestPacket, std::error_code>;
};
using ItemStackRequestActionType = ItemStackRequestActionType_<2225>;
using TextProcessingEventOrigin = TextProcessingEventOrigin_<2225>;
using RedactableString = RedactableString_<2225>;
using ItemStackResponseSlotInfo = ItemStackResponseSlotInfo_<2225>;
using ItemStackResponseContainerInfo = ItemStackResponseContainerInfo_<2225>;
using ItemStackResponseInfo = ItemStackResponseInfo_<2225>;
using ItemStackResponsePacket = ItemStackResponsePacket_<2225>;
using ItemStackRequestCereal = ItemStackRequestCereal_<2225>;
using ItemStackRequestPacket = ItemStackRequestPacket_<2225>;

}  // namespace bedrock::protocol
