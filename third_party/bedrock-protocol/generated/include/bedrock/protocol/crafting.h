#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <expected>
#include <map>
#include <optional>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>

#include <bedrock/protocol/detail/reflect.hpp>
#include <bedrock/protocol/enum.hpp>
#include <bedrock/protocol/packet.hpp>
#include <bedrock/protocol/serializer.hpp>
#include <bedrock/protocol/stream.hpp>
#include <bedrock/protocol/uuid.hpp>

#include <bedrock/protocol/common.h>

namespace bedrock::protocol {

enum class CreativeItemCategory : std::uint8_t {
    All = 0,
    Construction = 1,
    Nature = 2,
    Equipment = 3,
    Items = 4,
    ItemCommandOnly = 5,
    Undefined = 6,
    NumCategories = 7,
};

struct RecipeNetId {
    std::uint32_t raw_id{};
};

struct CreativeItemNetId {
    std::uint32_t raw_id{};
};

struct MultiRecipePayload {
    UUID uuid{};
    RecipeNetId net_id{};
};

struct PotionMixDataEntry {
    std::int32_t from_item_id{};
    std::int32_t from_item_aux{};
    std::int32_t reagent_item_id{};
    std::int32_t reagent_item_aux{};
    std::int32_t to_item_id{};
    std::int32_t to_item_aux{};
};

struct ContainerMixDataEntry {
    std::int32_t from_item_id{};
    std::int32_t reagent_item_id{};
    std::int32_t to_item_id{};
};

struct MaterialReducerEntryOutput {
    std::int32_t item_id{};
    std::int32_t item_count{};
};

struct MaterialReducerDataEntry {
    std::int32_t from_item_key{};
    std::vector<MaterialReducerEntryOutput> to_item_ids_and_counts{};
};

enum class LabTableReactionType : std::uint8_t {
    None = 0,
    IceBomb = 1,
    Bleach = 2,
    ElephantToothpaste = 3,
    Fertilizer = 4,
    HeatBlock = 5,
    MagnesiumSalts = 6,
    MiscFire = 7,
    MiscExplosion = 8,
    MiscLava = 9,
    MiscMystical = 10,
    MiscSmoke = 11,
    MiscLargeSmoke = 12,
};

namespace LabTablePacket_nested {

enum class Type : std::uint8_t {
    StartCombine = 0,
    StartReaction = 1,
    Reset = 2,
};

}  // namespace LabTablePacket_nested

struct LabTablePacket {
    using Type = LabTablePacket_nested::Type;

    static constexpr int Id = 109;
    LabTablePacket::Type type{};
    BlockPos pos{};
    LabTableReactionType reaction{};
};

namespace UnlockedRecipesPacket_nested {

enum class PacketType : std::uint32_t {
    Empty = 0,
    InitiallyUnlockedRecipes = 1,
    NewlyUnlockedRecipes = 2,
    RemoveUnlockedRecipes = 3,
    RemoveAllUnlockedRecipes = 4,
};

}  // namespace UnlockedRecipesPacket_nested

struct UnlockedRecipesPacket {
    using PacketType = UnlockedRecipesPacket_nested::PacketType;

    static constexpr int Id = 199;
    UnlockedRecipesPacket::PacketType packet_type{};
    std::vector<std::string> unlocked_recipes{};
};

namespace base {

enum class CraftingDataEntryType : int {
    ShapelessRecipe = 0,
    ShapedRecipe = 1,
    FurnaceRecipe = 2,
    FurnaceAuxRecipe = 3,
    MultiRecipe = 4,
    UserDataShapelessRecipe = 5,
    ShapelessChemistryRecipe = 6,
    ShapedChemistryRecipe = 7,
    SmithingTransformRecipe = 8,
    SmithingTrimRecipe = 9,
    Count = 10,
};

struct SerializedNetworkItemInstanceDescriptor {
    std::int32_t id{};
    std::uint16_t stack_size{};
    std::uint32_t aux_value{};
    BlockRuntimeId block_runtime_id{};
    std::string user_data_buffer{};
};

namespace ItemDescriptor_nested {

enum class InternalType : std::uint8_t {
    Invalid = 0,
    Default = 1,
    Molang = 2,
    ItemTag = 3,
    Deferred = 4,
    ComplexAlias = 5,
};

}  // namespace ItemDescriptor_nested

struct ItemDescriptor {
    using InternalType = ItemDescriptor_nested::InternalType;

    base::ItemDescriptor::InternalType internal_type{};
    std::int16_t id{};
    std::string name{};
    std::uint8_t molang_version{};
    std::int16_t aux_value{};
};

struct SerializedRecipeIngredient {
    base::ItemDescriptor descriptor{};
    std::uint16_t stack_size{};
};

namespace SerializedRecipeUnlockingRequirement_nested {

enum class UnlockingContext : int {
    None = 0,
    AlwaysUnlocked = 1,
    PlayerInWater = 2,
    PlayerHasManyItems = 3,
};

}  // namespace SerializedRecipeUnlockingRequirement_nested

struct SerializedRecipeUnlockingRequirement {
    using UnlockingContext = SerializedRecipeUnlockingRequirement_nested::UnlockingContext;

    base::SerializedRecipeUnlockingRequirement::UnlockingContext context{};
    std::vector<base::SerializedRecipeIngredient> ingredients{};
};

struct ShapedRecipePayload {
    std::string recipe_id{};
    std::int32_t width{};
    std::int32_t height{};
    std::vector<base::SerializedRecipeIngredient> ingredients{};
    std::vector<base::SerializedNetworkItemInstanceDescriptor> results{};
    UUID uuid{};
    std::string tag{};
    std::int32_t priority{};
    bool assume_symmetry{};
    base::SerializedRecipeUnlockingRequirement unlocking_requirement{};
    RecipeNetId net_id{};
};

struct ShapelessRecipePayload {
    std::string recipe_id{};
    std::vector<base::SerializedRecipeIngredient> ingredients{};
    std::vector<base::SerializedNetworkItemInstanceDescriptor> results{};
    UUID uuid{};
    std::string tag{};
    std::int32_t priority{};
    base::SerializedRecipeUnlockingRequirement unlocking_requirement{};
    RecipeNetId net_id{};
};

struct SmithingTransformRecipePayload {
    std::string recipe_id{};
    base::SerializedRecipeIngredient template_ingredient{};
    base::SerializedRecipeIngredient base_ingredient{};
    base::SerializedRecipeIngredient addition_ingredient{};
    base::SerializedNetworkItemInstanceDescriptor result{};
    std::string tag{};
    RecipeNetId net_id{};
};

struct SmithingTrimRecipePayload {
    std::string recipe_id{};
    base::SerializedRecipeIngredient template_ingredient{};
    base::SerializedRecipeIngredient base_ingredient{};
    base::SerializedRecipeIngredient addition_ingredient{};
    std::string tag{};
    RecipeNetId net_id{};
};

struct ShapedChemistryRecipePayload {
    std::string recipe_id{};
    std::int32_t width{};
    std::int32_t height{};
    std::vector<base::SerializedRecipeIngredient> ingredients{};
    std::vector<base::SerializedNetworkItemInstanceDescriptor> results{};
    UUID uuid{};
    std::string tag{};
    std::int32_t priority{};
    bool assume_symmetry{};
    RecipeNetId net_id{};
};

struct ShapelessChemistryRecipePayload {
    std::string recipe_id{};
    std::vector<base::SerializedRecipeIngredient> ingredients{};
    std::vector<base::SerializedNetworkItemInstanceDescriptor> results{};
    UUID uuid{};
    std::string tag{};
    std::int32_t priority{};
    RecipeNetId net_id{};
};

struct CraftingDataEntry {
    base::CraftingDataEntryType entry_type{};
    base::ShapelessRecipePayload shapeless_recipe{};
    base::ShapelessChemistryRecipePayload shapeless_chemistry_recipe{};
    base::ShapedRecipePayload shaped_recipe{};
    base::ShapedChemistryRecipePayload shaped_chemistry_recipe{};
    MultiRecipePayload multi_recipe{};
    base::SmithingTransformRecipePayload smithing_transform_recipe{};
    base::SmithingTrimRecipePayload smithing_trim_recipe{};
    std::int32_t item_data{};
    std::int32_t item_aux{};
    base::SerializedNetworkItemInstanceDescriptor item_result{};
    std::string tag{};
};

struct CraftingDataPacket {
    static constexpr int Id = 52;
    std::vector<base::CraftingDataEntry> crafting_entries{};
    std::vector<PotionMixDataEntry> potion_mix_entries{};
    std::vector<ContainerMixDataEntry> container_mix_entries{};
    std::vector<MaterialReducerDataEntry> material_reducer_entries{};
    bool clear_recipes{};
};

struct CreativeItemEntryPayload {
    CreativeItemNetId creative_item_net_id{};
    base::SerializedNetworkItemInstanceDescriptor item_descriptor{};
};

struct CreativeContentPacket {
    static constexpr int Id = 145;
    std::vector<base::CreativeItemEntryPayload> entries{};
};

}  // namespace base

namespace v748 {

using CraftingDataEntryType = base::CraftingDataEntryType;

using SerializedNetworkItemInstanceDescriptor = base::SerializedNetworkItemInstanceDescriptor;

using ItemDescriptor = base::ItemDescriptor;

using SerializedRecipeIngredient = base::SerializedRecipeIngredient;

using SerializedRecipeUnlockingRequirement = base::SerializedRecipeUnlockingRequirement;

using ShapedRecipePayload = base::ShapedRecipePayload;

using ShapelessRecipePayload = base::ShapelessRecipePayload;

using SmithingTransformRecipePayload = base::SmithingTransformRecipePayload;

using SmithingTrimRecipePayload = base::SmithingTrimRecipePayload;

using ShapedChemistryRecipePayload = base::ShapedChemistryRecipePayload;

using ShapelessChemistryRecipePayload = base::ShapelessChemistryRecipePayload;

struct CraftingDataEntry {
    base::CraftingDataEntryType entry_type{};
    base::ShapelessRecipePayload shapeless_recipe{};
    base::ShapelessChemistryRecipePayload shapeless_chemistry_recipe{};
    base::ShapedRecipePayload shaped_recipe{};
    base::ShapedChemistryRecipePayload shaped_chemistry_recipe{};
    MultiRecipePayload multi_recipe{};
    base::SmithingTransformRecipePayload smithing_transform_recipe{};
    base::SmithingTrimRecipePayload smithing_trim_recipe{};
    std::int32_t item_data{};
    std::int32_t item_aux{};
    base::SerializedNetworkItemInstanceDescriptor item_result{};
    std::string tag{};
};

struct CraftingDataPacket {
    static constexpr int Id = 52;
    std::vector<v748::CraftingDataEntry> crafting_entries{};
    std::vector<PotionMixDataEntry> potion_mix_entries{};
    std::vector<ContainerMixDataEntry> container_mix_entries{};
    std::vector<MaterialReducerDataEntry> material_reducer_entries{};
    bool clear_recipes{};
};

using CreativeItemEntryPayload = base::CreativeItemEntryPayload;

using CreativeContentPacket = base::CreativeContentPacket;

}  // namespace v748

namespace v776 {

using CraftingDataEntryType = base::CraftingDataEntryType;

using SerializedNetworkItemInstanceDescriptor = base::SerializedNetworkItemInstanceDescriptor;

using ItemDescriptor = base::ItemDescriptor;

using SerializedRecipeIngredient = base::SerializedRecipeIngredient;

using SerializedRecipeUnlockingRequirement = base::SerializedRecipeUnlockingRequirement;

using ShapedRecipePayload = base::ShapedRecipePayload;

using ShapelessRecipePayload = base::ShapelessRecipePayload;

using SmithingTransformRecipePayload = base::SmithingTransformRecipePayload;

using SmithingTrimRecipePayload = base::SmithingTrimRecipePayload;

using ShapedChemistryRecipePayload = base::ShapedChemistryRecipePayload;

using ShapelessChemistryRecipePayload = base::ShapelessChemistryRecipePayload;

using CraftingDataEntry = v748::CraftingDataEntry;

using CraftingDataPacket = v748::CraftingDataPacket;

struct CreativeGroupInfoPayload {
    CreativeItemCategory creative_item_category{};
    std::string name{};
    base::SerializedNetworkItemInstanceDescriptor icon{};
};

struct CreativeItemEntryPayload {
    CreativeItemNetId creative_item_net_id{};
    base::SerializedNetworkItemInstanceDescriptor item_descriptor{};
    std::uint32_t group_index{};
};

struct CreativeContentPacket {
    static constexpr int Id = 145;
    std::vector<v776::CreativeGroupInfoPayload> groups{};
    std::vector<v776::CreativeItemEntryPayload> entries{};
};

}  // namespace v776

namespace v975 {

enum class CraftingDataEntryType : int {
    ShapelessRecipe = 0,
    ShapedRecipe = 1,
    MultiRecipe = 4,
    UserDataShapelessRecipe = 5,
    ShapelessChemistryRecipe = 6,
    ShapedChemistryRecipe = 7,
    SmithingTransformRecipe = 8,
    SmithingTrimRecipe = 9,
    Count = 10,
};

using SerializedNetworkItemInstanceDescriptor = base::SerializedNetworkItemInstanceDescriptor;

using ItemDescriptor = base::ItemDescriptor;

using SerializedRecipeIngredient = base::SerializedRecipeIngredient;

using SerializedRecipeUnlockingRequirement = base::SerializedRecipeUnlockingRequirement;

using ShapedRecipePayload = base::ShapedRecipePayload;

using ShapelessRecipePayload = base::ShapelessRecipePayload;

using SmithingTransformRecipePayload = base::SmithingTransformRecipePayload;

using SmithingTrimRecipePayload = base::SmithingTrimRecipePayload;

using ShapedChemistryRecipePayload = base::ShapedChemistryRecipePayload;

using ShapelessChemistryRecipePayload = base::ShapelessChemistryRecipePayload;

struct CraftingDataEntry {
    v975::CraftingDataEntryType entry_type{};
    base::ShapelessRecipePayload shapeless_recipe{};
    base::ShapelessChemistryRecipePayload shapeless_chemistry_recipe{};
    base::ShapedRecipePayload shaped_recipe{};
    base::ShapedChemistryRecipePayload shaped_chemistry_recipe{};
    MultiRecipePayload multi_recipe{};
    base::SmithingTransformRecipePayload smithing_transform_recipe{};
    base::SmithingTrimRecipePayload smithing_trim_recipe{};
};

struct CraftingDataPacket {
    static constexpr int Id = 52;
    std::vector<v975::CraftingDataEntry> crafting_entries{};
    std::vector<PotionMixDataEntry> potion_mix_entries{};
    std::vector<ContainerMixDataEntry> container_mix_entries{};
    std::vector<MaterialReducerDataEntry> material_reducer_entries{};
    bool clear_recipes{};
};

using CreativeGroupInfoPayload = v776::CreativeGroupInfoPayload;

using CreativeItemEntryPayload = v776::CreativeItemEntryPayload;

using CreativeContentPacket = v776::CreativeContentPacket;

}  // namespace v975

namespace v2168 {

using CraftingDataEntryType = v975::CraftingDataEntryType;

struct SerializedNetworkItemInstanceDescriptor {
    std::int32_t id{};
    std::uint16_t stack_size{};
    std::uint32_t aux_value{};
    std::int32_t block_runtime_id{};
    std::string user_data_buffer{};
};

struct SerializedRecipeIngredient {
    std::map<std::string, std::string> descriptor{};
    std::int16_t aux_value{};
    std::uint16_t stack_size{};
};

namespace SerializedRecipeUnlockingRequirement_nested {

using UnlockingContext = base::SerializedRecipeUnlockingRequirement::UnlockingContext;

}  // namespace SerializedRecipeUnlockingRequirement_nested

struct SerializedRecipeUnlockingRequirement {
    using UnlockingContext = SerializedRecipeUnlockingRequirement_nested::UnlockingContext;

    v2168::SerializedRecipeUnlockingRequirement::UnlockingContext context{};
    std::optional<std::vector<v2168::SerializedRecipeIngredient>> ingredients{};
};

struct ShapedRecipePayload {
    std::string recipe_id{};
    std::int32_t width{};
    std::int32_t height{};
    std::vector<v2168::SerializedRecipeIngredient> ingredients{};
    std::vector<v2168::SerializedNetworkItemInstanceDescriptor> results{};
    UUID uuid{};
    std::string tag{};
    std::int32_t priority{};
    bool assume_symmetry{};
    std::optional<v2168::SerializedRecipeUnlockingRequirement> unlocking_requirement{};
    RecipeNetId net_id{};
};

struct ShapelessRecipePayload {
    std::string recipe_id{};
    std::vector<v2168::SerializedRecipeIngredient> ingredients{};
    std::vector<v2168::SerializedNetworkItemInstanceDescriptor> results{};
    UUID uuid{};
    std::string tag{};
    std::int32_t priority{};
    std::optional<v2168::SerializedRecipeUnlockingRequirement> unlocking_requirement{};
    RecipeNetId net_id{};
};

struct SmithingTransformRecipePayload {
    std::string recipe_id{};
    v2168::SerializedRecipeIngredient template_ingredient{};
    v2168::SerializedRecipeIngredient base_ingredient{};
    v2168::SerializedRecipeIngredient addition_ingredient{};
    v2168::SerializedNetworkItemInstanceDescriptor result{};
    std::string tag{};
    RecipeNetId net_id{};
};

struct SmithingTrimRecipePayload {
    std::string recipe_id{};
    v2168::SerializedRecipeIngredient template_ingredient{};
    v2168::SerializedRecipeIngredient base_ingredient{};
    v2168::SerializedRecipeIngredient addition_ingredient{};
    std::string tag{};
    RecipeNetId net_id{};
};

struct CraftingDataPacket {
    static constexpr int Id = 52;
    std::vector<v2168::ShapedRecipePayload> shaped_recipes{};
    std::vector<v2168::ShapelessRecipePayload> shapeless_recipes{};
    std::vector<MultiRecipePayload> multi_recipes{};
    std::vector<v2168::ShapelessRecipePayload> user_data_shapeless_recipes{};
    std::vector<v2168::ShapelessRecipePayload> shapeless_chemistry_recipes{};
    std::vector<v2168::ShapedRecipePayload> shaped_chemistry_recipes{};
    std::vector<v2168::SmithingTransformRecipePayload> smithing_transform_recipes{};
    std::vector<v2168::SmithingTrimRecipePayload> smithing_trim_recipes{};
    std::vector<PotionMixDataEntry> potion_mix_entries{};
    std::vector<ContainerMixDataEntry> container_mix_entries{};
    std::vector<MaterialReducerDataEntry> material_reducer_entries{};
    bool clear_recipes{};
};

struct CreativeGroupInfoPayload {
    CreativeItemCategory creative_item_category{};
    std::string name{};
    v2168::SerializedNetworkItemInstanceDescriptor icon{};
};

struct CreativeItemEntryPayload {
    CreativeItemNetId creative_item_net_id{};
    v2168::SerializedNetworkItemInstanceDescriptor item_descriptor{};
    std::uint32_t group_index{};
};

struct CreativeContentPacket {
    static constexpr int Id = 145;
    std::vector<v2168::CreativeGroupInfoPayload> groups{};
    std::vector<v2168::CreativeItemEntryPayload> entries{};
};

}  // namespace v2168

namespace detail {

template <int V>
struct CraftingDataEntryType_;

template <int V> requires (V < 975)
struct CraftingDataEntryType_<V> { using type = base::CraftingDataEntryType; };

template <int V> requires (V >= 975)
struct CraftingDataEntryType_<V> { using type = v975::CraftingDataEntryType; };

template <int V>
struct SerializedNetworkItemInstanceDescriptor_;

template <int V> requires (V < 2168)
struct SerializedNetworkItemInstanceDescriptor_<V> { using type = base::SerializedNetworkItemInstanceDescriptor; };

template <int V> requires (V >= 2168)
struct SerializedNetworkItemInstanceDescriptor_<V> { using type = v2168::SerializedNetworkItemInstanceDescriptor; };

template <int V>
struct ItemDescriptor_;

template <int V> requires (V < 2168)
struct ItemDescriptor_<V> { using type = base::ItemDescriptor; };

template <int V>
struct SerializedRecipeIngredient_;

template <int V> requires (V < 2168)
struct SerializedRecipeIngredient_<V> { using type = base::SerializedRecipeIngredient; };

template <int V> requires (V >= 2168)
struct SerializedRecipeIngredient_<V> { using type = v2168::SerializedRecipeIngredient; };

template <int V>
struct SerializedRecipeUnlockingRequirement_;

template <int V> requires (V < 2168)
struct SerializedRecipeUnlockingRequirement_<V> { using type = base::SerializedRecipeUnlockingRequirement; };

template <int V> requires (V >= 2168)
struct SerializedRecipeUnlockingRequirement_<V> { using type = v2168::SerializedRecipeUnlockingRequirement; };

template <int V>
struct ShapedRecipePayload_;

template <int V> requires (V < 2168)
struct ShapedRecipePayload_<V> { using type = base::ShapedRecipePayload; };

template <int V> requires (V >= 2168)
struct ShapedRecipePayload_<V> { using type = v2168::ShapedRecipePayload; };

template <int V>
struct ShapelessRecipePayload_;

template <int V> requires (V < 2168)
struct ShapelessRecipePayload_<V> { using type = base::ShapelessRecipePayload; };

template <int V> requires (V >= 2168)
struct ShapelessRecipePayload_<V> { using type = v2168::ShapelessRecipePayload; };

template <int V>
struct SmithingTransformRecipePayload_;

template <int V> requires (V < 2168)
struct SmithingTransformRecipePayload_<V> { using type = base::SmithingTransformRecipePayload; };

template <int V> requires (V >= 2168)
struct SmithingTransformRecipePayload_<V> { using type = v2168::SmithingTransformRecipePayload; };

template <int V>
struct SmithingTrimRecipePayload_;

template <int V> requires (V < 2168)
struct SmithingTrimRecipePayload_<V> { using type = base::SmithingTrimRecipePayload; };

template <int V> requires (V >= 2168)
struct SmithingTrimRecipePayload_<V> { using type = v2168::SmithingTrimRecipePayload; };

template <int V>
struct ShapedChemistryRecipePayload_;

template <int V> requires (V < 2168)
struct ShapedChemistryRecipePayload_<V> { using type = base::ShapedChemistryRecipePayload; };

template <int V>
struct ShapelessChemistryRecipePayload_;

template <int V> requires (V < 2168)
struct ShapelessChemistryRecipePayload_<V> { using type = base::ShapelessChemistryRecipePayload; };

template <int V>
struct CraftingDataEntry_;

template <int V> requires (V < 748)
struct CraftingDataEntry_<V> { using type = base::CraftingDataEntry; };

template <int V> requires (V >= 748 && V < 975)
struct CraftingDataEntry_<V> { using type = v748::CraftingDataEntry; };

template <int V> requires (V >= 975 && V < 2168)
struct CraftingDataEntry_<V> { using type = v975::CraftingDataEntry; };

template <int V>
struct CraftingDataPacket_;

template <int V> requires (V < 748)
struct CraftingDataPacket_<V> { using type = base::CraftingDataPacket; };

template <int V> requires (V >= 748 && V < 975)
struct CraftingDataPacket_<V> { using type = v748::CraftingDataPacket; };

template <int V> requires (V >= 975 && V < 2168)
struct CraftingDataPacket_<V> { using type = v975::CraftingDataPacket; };

template <int V> requires (V >= 2168)
struct CraftingDataPacket_<V> { using type = v2168::CraftingDataPacket; };

template <int V>
struct CreativeGroupInfoPayload_;

template <int V> requires (V >= 776 && V < 2168)
struct CreativeGroupInfoPayload_<V> { using type = v776::CreativeGroupInfoPayload; };

template <int V> requires (V >= 2168)
struct CreativeGroupInfoPayload_<V> { using type = v2168::CreativeGroupInfoPayload; };

template <int V>
struct CreativeItemEntryPayload_;

template <int V> requires (V < 776)
struct CreativeItemEntryPayload_<V> { using type = base::CreativeItemEntryPayload; };

template <int V> requires (V >= 776 && V < 2168)
struct CreativeItemEntryPayload_<V> { using type = v776::CreativeItemEntryPayload; };

template <int V> requires (V >= 2168)
struct CreativeItemEntryPayload_<V> { using type = v2168::CreativeItemEntryPayload; };

template <int V>
struct CreativeContentPacket_;

template <int V> requires (V < 776)
struct CreativeContentPacket_<V> { using type = base::CreativeContentPacket; };

template <int V> requires (V >= 776 && V < 2168)
struct CreativeContentPacket_<V> { using type = v776::CreativeContentPacket; };

template <int V> requires (V >= 2168)
struct CreativeContentPacket_<V> { using type = v2168::CreativeContentPacket; };

}  // namespace detail

template <int V> using CraftingDataEntryType_ = typename detail::CraftingDataEntryType_<V>::type;
template <int V> using SerializedNetworkItemInstanceDescriptor_ = typename detail::SerializedNetworkItemInstanceDescriptor_<V>::type;
template <int V> using ItemDescriptor_ = typename detail::ItemDescriptor_<V>::type;
template <int V> using SerializedRecipeIngredient_ = typename detail::SerializedRecipeIngredient_<V>::type;
template <int V> using SerializedRecipeUnlockingRequirement_ = typename detail::SerializedRecipeUnlockingRequirement_<V>::type;
template <int V> using ShapedRecipePayload_ = typename detail::ShapedRecipePayload_<V>::type;
template <int V> using ShapelessRecipePayload_ = typename detail::ShapelessRecipePayload_<V>::type;
template <int V> using SmithingTransformRecipePayload_ = typename detail::SmithingTransformRecipePayload_<V>::type;
template <int V> using SmithingTrimRecipePayload_ = typename detail::SmithingTrimRecipePayload_<V>::type;
template <int V> using ShapedChemistryRecipePayload_ = typename detail::ShapedChemistryRecipePayload_<V>::type;
template <int V> using ShapelessChemistryRecipePayload_ = typename detail::ShapelessChemistryRecipePayload_<V>::type;
template <int V> using CraftingDataEntry_ = typename detail::CraftingDataEntry_<V>::type;
template <int V> using CraftingDataPacket_ = typename detail::CraftingDataPacket_<V>::type;
template <int V> using CreativeGroupInfoPayload_ = typename detail::CreativeGroupInfoPayload_<V>::type;
template <int V> using CreativeItemEntryPayload_ = typename detail::CreativeItemEntryPayload_<V>::type;
template <int V> using CreativeContentPacket_ = typename detail::CreativeContentPacket_<V>::type;

template <int V>
struct packet_of<V, 52> { using type = CraftingDataPacket_<V>; };

template <int V>
struct packet_of<V, 109> { using type = LabTablePacket; };

template <int V>
struct packet_of<V, 145> { using type = CreativeContentPacket_<V>; };

template <int V>
struct packet_of<V, 199> { using type = UnlockedRecipesPacket; };

namespace detail {

template <>
inline constexpr std::array<CreativeItemCategory, 8> values_v<CreativeItemCategory>{{
    CreativeItemCategory::All,
    CreativeItemCategory::Construction,
    CreativeItemCategory::Nature,
    CreativeItemCategory::Equipment,
    CreativeItemCategory::Items,
    CreativeItemCategory::ItemCommandOnly,
    CreativeItemCategory::Undefined,
    CreativeItemCategory::NumCategories,
}};

template <>
inline constexpr std::array<std::string_view, 8> names_v<CreativeItemCategory>{{
    "all",
    "construction",
    "nature",
    "equipment",
    "items",
    "itemcommandonly",
    "undefined",
    "numcategories",
}};

template <>
inline constexpr std::string_view type_name_v<CreativeItemCategory>{"CreativeItemCategory"};

template <>
inline constexpr std::array<base::CraftingDataEntryType, 11> values_v<base::CraftingDataEntryType>{{
    base::CraftingDataEntryType::ShapelessRecipe,
    base::CraftingDataEntryType::ShapedRecipe,
    base::CraftingDataEntryType::FurnaceRecipe,
    base::CraftingDataEntryType::FurnaceAuxRecipe,
    base::CraftingDataEntryType::MultiRecipe,
    base::CraftingDataEntryType::UserDataShapelessRecipe,
    base::CraftingDataEntryType::ShapelessChemistryRecipe,
    base::CraftingDataEntryType::ShapedChemistryRecipe,
    base::CraftingDataEntryType::SmithingTransformRecipe,
    base::CraftingDataEntryType::SmithingTrimRecipe,
    base::CraftingDataEntryType::Count,
}};

template <>
inline constexpr std::array<std::string_view, 11> names_v<base::CraftingDataEntryType>{{
    "shapelessrecipe",
    "shapedrecipe",
    "furnacerecipe",
    "furnaceauxrecipe",
    "multirecipe",
    "userdatashapelessrecipe",
    "shapelesschemistryrecipe",
    "shapedchemistryrecipe",
    "smithingtransformrecipe",
    "smithingtrimrecipe",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<base::CraftingDataEntryType>{"CraftingDataEntryType"};

template <>
inline constexpr std::array<v975::CraftingDataEntryType, 9> values_v<v975::CraftingDataEntryType>{{
    v975::CraftingDataEntryType::ShapelessRecipe,
    v975::CraftingDataEntryType::ShapedRecipe,
    v975::CraftingDataEntryType::MultiRecipe,
    v975::CraftingDataEntryType::UserDataShapelessRecipe,
    v975::CraftingDataEntryType::ShapelessChemistryRecipe,
    v975::CraftingDataEntryType::ShapedChemistryRecipe,
    v975::CraftingDataEntryType::SmithingTransformRecipe,
    v975::CraftingDataEntryType::SmithingTrimRecipe,
    v975::CraftingDataEntryType::Count,
}};

template <>
inline constexpr std::array<std::string_view, 9> names_v<v975::CraftingDataEntryType>{{
    "shapelessrecipe",
    "shapedrecipe",
    "multirecipe",
    "userdatashapelessrecipe",
    "shapelesschemistryrecipe",
    "shapedchemistryrecipe",
    "smithingtransformrecipe",
    "smithingtrimrecipe",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<v975::CraftingDataEntryType>{"CraftingDataEntryType"};

template <>
inline constexpr std::array<base::ItemDescriptor::InternalType, 6> values_v<base::ItemDescriptor::InternalType>{{
    base::ItemDescriptor::InternalType::Invalid,
    base::ItemDescriptor::InternalType::Default,
    base::ItemDescriptor::InternalType::Molang,
    base::ItemDescriptor::InternalType::ItemTag,
    base::ItemDescriptor::InternalType::Deferred,
    base::ItemDescriptor::InternalType::ComplexAlias,
}};

template <>
inline constexpr std::array<std::string_view, 6> names_v<base::ItemDescriptor::InternalType>{{
    "invalid",
    "default",
    "molang",
    "itemtag",
    "deferred",
    "complexalias",
}};

template <>
inline constexpr std::string_view type_name_v<base::ItemDescriptor::InternalType>{"ItemDescriptor::InternalType"};

template <>
inline constexpr std::array<base::SerializedRecipeUnlockingRequirement::UnlockingContext, 4> values_v<base::SerializedRecipeUnlockingRequirement::UnlockingContext>{{
    base::SerializedRecipeUnlockingRequirement::UnlockingContext::None,
    base::SerializedRecipeUnlockingRequirement::UnlockingContext::AlwaysUnlocked,
    base::SerializedRecipeUnlockingRequirement::UnlockingContext::PlayerInWater,
    base::SerializedRecipeUnlockingRequirement::UnlockingContext::PlayerHasManyItems,
}};

template <>
inline constexpr std::array<std::string_view, 4> names_v<base::SerializedRecipeUnlockingRequirement::UnlockingContext>{{
    "none",
    "alwaysunlocked",
    "playerinwater",
    "playerhasmanyitems",
}};

template <>
inline constexpr std::string_view type_name_v<base::SerializedRecipeUnlockingRequirement::UnlockingContext>{"SerializedRecipeUnlockingRequirement::UnlockingContext"};

template <>
inline constexpr std::array<LabTableReactionType, 13> values_v<LabTableReactionType>{{
    LabTableReactionType::None,
    LabTableReactionType::IceBomb,
    LabTableReactionType::Bleach,
    LabTableReactionType::ElephantToothpaste,
    LabTableReactionType::Fertilizer,
    LabTableReactionType::HeatBlock,
    LabTableReactionType::MagnesiumSalts,
    LabTableReactionType::MiscFire,
    LabTableReactionType::MiscExplosion,
    LabTableReactionType::MiscLava,
    LabTableReactionType::MiscMystical,
    LabTableReactionType::MiscSmoke,
    LabTableReactionType::MiscLargeSmoke,
}};

template <>
inline constexpr std::array<std::string_view, 13> names_v<LabTableReactionType>{{
    "none",
    "icebomb",
    "bleach",
    "elephanttoothpaste",
    "fertilizer",
    "heatblock",
    "magnesiumsalts",
    "miscfire",
    "miscexplosion",
    "misclava",
    "miscmystical",
    "miscsmoke",
    "misclargesmoke",
}};

template <>
inline constexpr std::string_view type_name_v<LabTableReactionType>{"LabTableReactionType"};

template <>
inline constexpr std::array<LabTablePacket::Type, 3> values_v<LabTablePacket::Type>{{
    LabTablePacket::Type::StartCombine,
    LabTablePacket::Type::StartReaction,
    LabTablePacket::Type::Reset,
}};

template <>
inline constexpr std::array<std::string_view, 3> names_v<LabTablePacket::Type>{{
    "startcombine",
    "startreaction",
    "reset",
}};

template <>
inline constexpr std::string_view type_name_v<LabTablePacket::Type>{"LabTablePacket::Type"};

template <>
inline constexpr std::array<UnlockedRecipesPacket::PacketType, 5> values_v<UnlockedRecipesPacket::PacketType>{{
    UnlockedRecipesPacket::PacketType::Empty,
    UnlockedRecipesPacket::PacketType::InitiallyUnlockedRecipes,
    UnlockedRecipesPacket::PacketType::NewlyUnlockedRecipes,
    UnlockedRecipesPacket::PacketType::RemoveUnlockedRecipes,
    UnlockedRecipesPacket::PacketType::RemoveAllUnlockedRecipes,
}};

template <>
inline constexpr std::array<std::string_view, 5> names_v<UnlockedRecipesPacket::PacketType>{{
    "empty",
    "initiallyunlockedrecipes",
    "newlyunlockedrecipes",
    "removeunlockedrecipes",
    "removeallunlockedrecipes",
}};

template <>
inline constexpr std::string_view type_name_v<UnlockedRecipesPacket::PacketType>{"UnlockedRecipesPacket::PacketType"};

}  // namespace detail

namespace detail {

template <>
inline constexpr bool is_reflected_struct_v<RecipeNetId> = true;

template <>
inline constexpr std::string_view struct_name_v<RecipeNetId>{"RecipeNetId"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<RecipeNetId>{{
    "raw_id",
}};

template <>
struct field_accessor<RecipeNetId> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.raw_id;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<CreativeItemNetId> = true;

template <>
inline constexpr std::string_view struct_name_v<CreativeItemNetId>{"CreativeItemNetId"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<CreativeItemNetId>{{
    "raw_id",
}};

template <>
struct field_accessor<CreativeItemNetId> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.raw_id;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::SerializedNetworkItemInstanceDescriptor> = true;

template <>
inline constexpr std::string_view struct_name_v<base::SerializedNetworkItemInstanceDescriptor>{"SerializedNetworkItemInstanceDescriptor"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<base::SerializedNetworkItemInstanceDescriptor>{{
    "id",
    "stack_size",
    "aux_value",
    "block_runtime_id",
    "user_data_buffer",
}};

template <>
struct field_accessor<base::SerializedNetworkItemInstanceDescriptor> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.id;
        }
        else if constexpr (I == 1) {
            return value.stack_size;
        }
        else if constexpr (I == 2) {
            return value.aux_value;
        }
        else if constexpr (I == 3) {
            return value.block_runtime_id;
        }
        else {
            return value.user_data_buffer;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::SerializedNetworkItemInstanceDescriptor> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::SerializedNetworkItemInstanceDescriptor>{"SerializedNetworkItemInstanceDescriptor"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v2168::SerializedNetworkItemInstanceDescriptor>{{
    "id",
    "stack_size",
    "aux_value",
    "block_runtime_id",
    "user_data_buffer",
}};

template <>
struct field_accessor<v2168::SerializedNetworkItemInstanceDescriptor> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.id;
        }
        else if constexpr (I == 1) {
            return value.stack_size;
        }
        else if constexpr (I == 2) {
            return value.aux_value;
        }
        else if constexpr (I == 3) {
            return value.block_runtime_id;
        }
        else {
            return value.user_data_buffer;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::ItemDescriptor> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ItemDescriptor>{"ItemDescriptor"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<base::ItemDescriptor>{{
    "internal_type",
    "id",
    "name",
    "molang_version",
    "aux_value",
}};

template <>
struct field_accessor<base::ItemDescriptor> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.internal_type;
        }
        else if constexpr (I == 1) {
            return value.id;
        }
        else if constexpr (I == 2) {
            return value.name;
        }
        else if constexpr (I == 3) {
            return value.molang_version;
        }
        else {
            return value.aux_value;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::SerializedRecipeIngredient> = true;

template <>
inline constexpr std::string_view struct_name_v<base::SerializedRecipeIngredient>{"SerializedRecipeIngredient"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<base::SerializedRecipeIngredient>{{
    "descriptor",
    "stack_size",
}};

template <>
struct field_accessor<base::SerializedRecipeIngredient> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.descriptor;
        }
        else {
            return value.stack_size;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::SerializedRecipeIngredient> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::SerializedRecipeIngredient>{"SerializedRecipeIngredient"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v2168::SerializedRecipeIngredient>{{
    "descriptor",
    "aux_value",
    "stack_size",
}};

template <>
struct field_accessor<v2168::SerializedRecipeIngredient> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.descriptor;
        }
        else if constexpr (I == 1) {
            return value.aux_value;
        }
        else {
            return value.stack_size;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::SerializedRecipeUnlockingRequirement> = true;

template <>
inline constexpr std::string_view struct_name_v<base::SerializedRecipeUnlockingRequirement>{"SerializedRecipeUnlockingRequirement"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<base::SerializedRecipeUnlockingRequirement>{{
    "context",
    "ingredients",
}};

template <>
struct field_accessor<base::SerializedRecipeUnlockingRequirement> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.context;
        }
        else {
            return value.ingredients;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::SerializedRecipeUnlockingRequirement> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::SerializedRecipeUnlockingRequirement>{"SerializedRecipeUnlockingRequirement"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2168::SerializedRecipeUnlockingRequirement>{{
    "context",
    "ingredients",
}};

template <>
struct field_accessor<v2168::SerializedRecipeUnlockingRequirement> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.context;
        }
        else {
            return value.ingredients;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::ShapedRecipePayload> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ShapedRecipePayload>{"ShapedRecipePayload"};

template <>
inline constexpr std::array<std::string_view, 11> field_names_v<base::ShapedRecipePayload>{{
    "recipe_id",
    "width",
    "height",
    "ingredients",
    "results",
    "uuid",
    "tag",
    "priority",
    "assume_symmetry",
    "unlocking_requirement",
    "net_id",
}};

template <>
struct field_accessor<base::ShapedRecipePayload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.recipe_id;
        }
        else if constexpr (I == 1) {
            return value.width;
        }
        else if constexpr (I == 2) {
            return value.height;
        }
        else if constexpr (I == 3) {
            return value.ingredients;
        }
        else if constexpr (I == 4) {
            return value.results;
        }
        else if constexpr (I == 5) {
            return value.uuid;
        }
        else if constexpr (I == 6) {
            return value.tag;
        }
        else if constexpr (I == 7) {
            return value.priority;
        }
        else if constexpr (I == 8) {
            return value.assume_symmetry;
        }
        else if constexpr (I == 9) {
            return value.unlocking_requirement;
        }
        else {
            return value.net_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ShapedRecipePayload> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ShapedRecipePayload>{"ShapedRecipePayload"};

template <>
inline constexpr std::array<std::string_view, 11> field_names_v<v2168::ShapedRecipePayload>{{
    "recipe_id",
    "width",
    "height",
    "ingredients",
    "results",
    "uuid",
    "tag",
    "priority",
    "assume_symmetry",
    "unlocking_requirement",
    "net_id",
}};

template <>
struct field_accessor<v2168::ShapedRecipePayload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.recipe_id;
        }
        else if constexpr (I == 1) {
            return value.width;
        }
        else if constexpr (I == 2) {
            return value.height;
        }
        else if constexpr (I == 3) {
            return value.ingredients;
        }
        else if constexpr (I == 4) {
            return value.results;
        }
        else if constexpr (I == 5) {
            return value.uuid;
        }
        else if constexpr (I == 6) {
            return value.tag;
        }
        else if constexpr (I == 7) {
            return value.priority;
        }
        else if constexpr (I == 8) {
            return value.assume_symmetry;
        }
        else if constexpr (I == 9) {
            return value.unlocking_requirement;
        }
        else {
            return value.net_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::ShapelessRecipePayload> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ShapelessRecipePayload>{"ShapelessRecipePayload"};

template <>
inline constexpr std::array<std::string_view, 8> field_names_v<base::ShapelessRecipePayload>{{
    "recipe_id",
    "ingredients",
    "results",
    "uuid",
    "tag",
    "priority",
    "unlocking_requirement",
    "net_id",
}};

template <>
struct field_accessor<base::ShapelessRecipePayload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.recipe_id;
        }
        else if constexpr (I == 1) {
            return value.ingredients;
        }
        else if constexpr (I == 2) {
            return value.results;
        }
        else if constexpr (I == 3) {
            return value.uuid;
        }
        else if constexpr (I == 4) {
            return value.tag;
        }
        else if constexpr (I == 5) {
            return value.priority;
        }
        else if constexpr (I == 6) {
            return value.unlocking_requirement;
        }
        else {
            return value.net_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ShapelessRecipePayload> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ShapelessRecipePayload>{"ShapelessRecipePayload"};

template <>
inline constexpr std::array<std::string_view, 8> field_names_v<v2168::ShapelessRecipePayload>{{
    "recipe_id",
    "ingredients",
    "results",
    "uuid",
    "tag",
    "priority",
    "unlocking_requirement",
    "net_id",
}};

template <>
struct field_accessor<v2168::ShapelessRecipePayload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.recipe_id;
        }
        else if constexpr (I == 1) {
            return value.ingredients;
        }
        else if constexpr (I == 2) {
            return value.results;
        }
        else if constexpr (I == 3) {
            return value.uuid;
        }
        else if constexpr (I == 4) {
            return value.tag;
        }
        else if constexpr (I == 5) {
            return value.priority;
        }
        else if constexpr (I == 6) {
            return value.unlocking_requirement;
        }
        else {
            return value.net_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<MultiRecipePayload> = true;

template <>
inline constexpr std::string_view struct_name_v<MultiRecipePayload>{"MultiRecipePayload"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<MultiRecipePayload>{{
    "uuid",
    "net_id",
}};

template <>
struct field_accessor<MultiRecipePayload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.uuid;
        }
        else {
            return value.net_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::SmithingTransformRecipePayload> = true;

template <>
inline constexpr std::string_view struct_name_v<base::SmithingTransformRecipePayload>{"SmithingTransformRecipePayload"};

template <>
inline constexpr std::array<std::string_view, 7> field_names_v<base::SmithingTransformRecipePayload>{{
    "recipe_id",
    "template_ingredient",
    "base_ingredient",
    "addition_ingredient",
    "result",
    "tag",
    "net_id",
}};

template <>
struct field_accessor<base::SmithingTransformRecipePayload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.recipe_id;
        }
        else if constexpr (I == 1) {
            return value.template_ingredient;
        }
        else if constexpr (I == 2) {
            return value.base_ingredient;
        }
        else if constexpr (I == 3) {
            return value.addition_ingredient;
        }
        else if constexpr (I == 4) {
            return value.result;
        }
        else if constexpr (I == 5) {
            return value.tag;
        }
        else {
            return value.net_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::SmithingTransformRecipePayload> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::SmithingTransformRecipePayload>{"SmithingTransformRecipePayload"};

template <>
inline constexpr std::array<std::string_view, 7> field_names_v<v2168::SmithingTransformRecipePayload>{{
    "recipe_id",
    "template_ingredient",
    "base_ingredient",
    "addition_ingredient",
    "result",
    "tag",
    "net_id",
}};

template <>
struct field_accessor<v2168::SmithingTransformRecipePayload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.recipe_id;
        }
        else if constexpr (I == 1) {
            return value.template_ingredient;
        }
        else if constexpr (I == 2) {
            return value.base_ingredient;
        }
        else if constexpr (I == 3) {
            return value.addition_ingredient;
        }
        else if constexpr (I == 4) {
            return value.result;
        }
        else if constexpr (I == 5) {
            return value.tag;
        }
        else {
            return value.net_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::SmithingTrimRecipePayload> = true;

template <>
inline constexpr std::string_view struct_name_v<base::SmithingTrimRecipePayload>{"SmithingTrimRecipePayload"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<base::SmithingTrimRecipePayload>{{
    "recipe_id",
    "template_ingredient",
    "base_ingredient",
    "addition_ingredient",
    "tag",
    "net_id",
}};

template <>
struct field_accessor<base::SmithingTrimRecipePayload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.recipe_id;
        }
        else if constexpr (I == 1) {
            return value.template_ingredient;
        }
        else if constexpr (I == 2) {
            return value.base_ingredient;
        }
        else if constexpr (I == 3) {
            return value.addition_ingredient;
        }
        else if constexpr (I == 4) {
            return value.tag;
        }
        else {
            return value.net_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::SmithingTrimRecipePayload> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::SmithingTrimRecipePayload>{"SmithingTrimRecipePayload"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<v2168::SmithingTrimRecipePayload>{{
    "recipe_id",
    "template_ingredient",
    "base_ingredient",
    "addition_ingredient",
    "tag",
    "net_id",
}};

template <>
struct field_accessor<v2168::SmithingTrimRecipePayload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.recipe_id;
        }
        else if constexpr (I == 1) {
            return value.template_ingredient;
        }
        else if constexpr (I == 2) {
            return value.base_ingredient;
        }
        else if constexpr (I == 3) {
            return value.addition_ingredient;
        }
        else if constexpr (I == 4) {
            return value.tag;
        }
        else {
            return value.net_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<PotionMixDataEntry> = true;

template <>
inline constexpr std::string_view struct_name_v<PotionMixDataEntry>{"PotionMixDataEntry"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<PotionMixDataEntry>{{
    "from_item_id",
    "from_item_aux",
    "reagent_item_id",
    "reagent_item_aux",
    "to_item_id",
    "to_item_aux",
}};

template <>
struct field_accessor<PotionMixDataEntry> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.from_item_id;
        }
        else if constexpr (I == 1) {
            return value.from_item_aux;
        }
        else if constexpr (I == 2) {
            return value.reagent_item_id;
        }
        else if constexpr (I == 3) {
            return value.reagent_item_aux;
        }
        else if constexpr (I == 4) {
            return value.to_item_id;
        }
        else {
            return value.to_item_aux;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<ContainerMixDataEntry> = true;

template <>
inline constexpr std::string_view struct_name_v<ContainerMixDataEntry>{"ContainerMixDataEntry"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<ContainerMixDataEntry>{{
    "from_item_id",
    "reagent_item_id",
    "to_item_id",
}};

template <>
struct field_accessor<ContainerMixDataEntry> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.from_item_id;
        }
        else if constexpr (I == 1) {
            return value.reagent_item_id;
        }
        else {
            return value.to_item_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<MaterialReducerEntryOutput> = true;

template <>
inline constexpr std::string_view struct_name_v<MaterialReducerEntryOutput>{"MaterialReducerEntryOutput"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<MaterialReducerEntryOutput>{{
    "item_id",
    "item_count",
}};

template <>
struct field_accessor<MaterialReducerEntryOutput> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.item_id;
        }
        else {
            return value.item_count;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<MaterialReducerDataEntry> = true;

template <>
inline constexpr std::string_view struct_name_v<MaterialReducerDataEntry>{"MaterialReducerDataEntry"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<MaterialReducerDataEntry>{{
    "from_item_key",
    "to_item_ids_and_counts",
}};

template <>
struct field_accessor<MaterialReducerDataEntry> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.from_item_key;
        }
        else {
            return value.to_item_ids_and_counts;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::ShapedChemistryRecipePayload> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ShapedChemistryRecipePayload>{"ShapedChemistryRecipePayload"};

template <>
inline constexpr std::array<std::string_view, 10> field_names_v<base::ShapedChemistryRecipePayload>{{
    "recipe_id",
    "width",
    "height",
    "ingredients",
    "results",
    "uuid",
    "tag",
    "priority",
    "assume_symmetry",
    "net_id",
}};

template <>
struct field_accessor<base::ShapedChemistryRecipePayload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.recipe_id;
        }
        else if constexpr (I == 1) {
            return value.width;
        }
        else if constexpr (I == 2) {
            return value.height;
        }
        else if constexpr (I == 3) {
            return value.ingredients;
        }
        else if constexpr (I == 4) {
            return value.results;
        }
        else if constexpr (I == 5) {
            return value.uuid;
        }
        else if constexpr (I == 6) {
            return value.tag;
        }
        else if constexpr (I == 7) {
            return value.priority;
        }
        else if constexpr (I == 8) {
            return value.assume_symmetry;
        }
        else {
            return value.net_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::ShapelessChemistryRecipePayload> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ShapelessChemistryRecipePayload>{"ShapelessChemistryRecipePayload"};

template <>
inline constexpr std::array<std::string_view, 7> field_names_v<base::ShapelessChemistryRecipePayload>{{
    "recipe_id",
    "ingredients",
    "results",
    "uuid",
    "tag",
    "priority",
    "net_id",
}};

template <>
struct field_accessor<base::ShapelessChemistryRecipePayload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.recipe_id;
        }
        else if constexpr (I == 1) {
            return value.ingredients;
        }
        else if constexpr (I == 2) {
            return value.results;
        }
        else if constexpr (I == 3) {
            return value.uuid;
        }
        else if constexpr (I == 4) {
            return value.tag;
        }
        else if constexpr (I == 5) {
            return value.priority;
        }
        else {
            return value.net_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::CraftingDataEntry> = true;

template <>
inline constexpr std::string_view struct_name_v<base::CraftingDataEntry>{"CraftingDataEntry"};

template <>
inline constexpr std::array<std::string_view, 12> field_names_v<base::CraftingDataEntry>{{
    "entry_type",
    "shapeless_recipe",
    "shapeless_chemistry_recipe",
    "shaped_recipe",
    "shaped_chemistry_recipe",
    "multi_recipe",
    "smithing_transform_recipe",
    "smithing_trim_recipe",
    "item_data",
    "item_aux",
    "item_result",
    "tag",
}};

template <>
struct field_accessor<base::CraftingDataEntry> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.entry_type;
        }
        else if constexpr (I == 1) {
            return value.shapeless_recipe;
        }
        else if constexpr (I == 2) {
            return value.shapeless_chemistry_recipe;
        }
        else if constexpr (I == 3) {
            return value.shaped_recipe;
        }
        else if constexpr (I == 4) {
            return value.shaped_chemistry_recipe;
        }
        else if constexpr (I == 5) {
            return value.multi_recipe;
        }
        else if constexpr (I == 6) {
            return value.smithing_transform_recipe;
        }
        else if constexpr (I == 7) {
            return value.smithing_trim_recipe;
        }
        else if constexpr (I == 8) {
            return value.item_data;
        }
        else if constexpr (I == 9) {
            return value.item_aux;
        }
        else if constexpr (I == 10) {
            return value.item_result;
        }
        else {
            return value.tag;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v748::CraftingDataEntry> = true;

template <>
inline constexpr std::string_view struct_name_v<v748::CraftingDataEntry>{"CraftingDataEntry"};

template <>
inline constexpr std::array<std::string_view, 12> field_names_v<v748::CraftingDataEntry>{{
    "entry_type",
    "shapeless_recipe",
    "shapeless_chemistry_recipe",
    "shaped_recipe",
    "shaped_chemistry_recipe",
    "multi_recipe",
    "smithing_transform_recipe",
    "smithing_trim_recipe",
    "item_data",
    "item_aux",
    "item_result",
    "tag",
}};

template <>
struct field_accessor<v748::CraftingDataEntry> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.entry_type;
        }
        else if constexpr (I == 1) {
            return value.shapeless_recipe;
        }
        else if constexpr (I == 2) {
            return value.shapeless_chemistry_recipe;
        }
        else if constexpr (I == 3) {
            return value.shaped_recipe;
        }
        else if constexpr (I == 4) {
            return value.shaped_chemistry_recipe;
        }
        else if constexpr (I == 5) {
            return value.multi_recipe;
        }
        else if constexpr (I == 6) {
            return value.smithing_transform_recipe;
        }
        else if constexpr (I == 7) {
            return value.smithing_trim_recipe;
        }
        else if constexpr (I == 8) {
            return value.item_data;
        }
        else if constexpr (I == 9) {
            return value.item_aux;
        }
        else if constexpr (I == 10) {
            return value.item_result;
        }
        else {
            return value.tag;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v975::CraftingDataEntry> = true;

template <>
inline constexpr std::string_view struct_name_v<v975::CraftingDataEntry>{"CraftingDataEntry"};

template <>
inline constexpr std::array<std::string_view, 8> field_names_v<v975::CraftingDataEntry>{{
    "entry_type",
    "shapeless_recipe",
    "shapeless_chemistry_recipe",
    "shaped_recipe",
    "shaped_chemistry_recipe",
    "multi_recipe",
    "smithing_transform_recipe",
    "smithing_trim_recipe",
}};

template <>
struct field_accessor<v975::CraftingDataEntry> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.entry_type;
        }
        else if constexpr (I == 1) {
            return value.shapeless_recipe;
        }
        else if constexpr (I == 2) {
            return value.shapeless_chemistry_recipe;
        }
        else if constexpr (I == 3) {
            return value.shaped_recipe;
        }
        else if constexpr (I == 4) {
            return value.shaped_chemistry_recipe;
        }
        else if constexpr (I == 5) {
            return value.multi_recipe;
        }
        else if constexpr (I == 6) {
            return value.smithing_transform_recipe;
        }
        else {
            return value.smithing_trim_recipe;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::CraftingDataPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::CraftingDataPacket>{"CraftingDataPacket"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<base::CraftingDataPacket>{{
    "crafting_entries",
    "potion_mix_entries",
    "container_mix_entries",
    "material_reducer_entries",
    "clear_recipes",
}};

template <>
struct field_accessor<base::CraftingDataPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.crafting_entries;
        }
        else if constexpr (I == 1) {
            return value.potion_mix_entries;
        }
        else if constexpr (I == 2) {
            return value.container_mix_entries;
        }
        else if constexpr (I == 3) {
            return value.material_reducer_entries;
        }
        else {
            return value.clear_recipes;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v748::CraftingDataPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v748::CraftingDataPacket>{"CraftingDataPacket"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v748::CraftingDataPacket>{{
    "crafting_entries",
    "potion_mix_entries",
    "container_mix_entries",
    "material_reducer_entries",
    "clear_recipes",
}};

template <>
struct field_accessor<v748::CraftingDataPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.crafting_entries;
        }
        else if constexpr (I == 1) {
            return value.potion_mix_entries;
        }
        else if constexpr (I == 2) {
            return value.container_mix_entries;
        }
        else if constexpr (I == 3) {
            return value.material_reducer_entries;
        }
        else {
            return value.clear_recipes;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v975::CraftingDataPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v975::CraftingDataPacket>{"CraftingDataPacket"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v975::CraftingDataPacket>{{
    "crafting_entries",
    "potion_mix_entries",
    "container_mix_entries",
    "material_reducer_entries",
    "clear_recipes",
}};

template <>
struct field_accessor<v975::CraftingDataPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.crafting_entries;
        }
        else if constexpr (I == 1) {
            return value.potion_mix_entries;
        }
        else if constexpr (I == 2) {
            return value.container_mix_entries;
        }
        else if constexpr (I == 3) {
            return value.material_reducer_entries;
        }
        else {
            return value.clear_recipes;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::CraftingDataPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::CraftingDataPacket>{"CraftingDataPacket"};

template <>
inline constexpr std::array<std::string_view, 12> field_names_v<v2168::CraftingDataPacket>{{
    "shaped_recipes",
    "shapeless_recipes",
    "multi_recipes",
    "user_data_shapeless_recipes",
    "shapeless_chemistry_recipes",
    "shaped_chemistry_recipes",
    "smithing_transform_recipes",
    "smithing_trim_recipes",
    "potion_mix_entries",
    "container_mix_entries",
    "material_reducer_entries",
    "clear_recipes",
}};

template <>
struct field_accessor<v2168::CraftingDataPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.shaped_recipes;
        }
        else if constexpr (I == 1) {
            return value.shapeless_recipes;
        }
        else if constexpr (I == 2) {
            return value.multi_recipes;
        }
        else if constexpr (I == 3) {
            return value.user_data_shapeless_recipes;
        }
        else if constexpr (I == 4) {
            return value.shapeless_chemistry_recipes;
        }
        else if constexpr (I == 5) {
            return value.shaped_chemistry_recipes;
        }
        else if constexpr (I == 6) {
            return value.smithing_transform_recipes;
        }
        else if constexpr (I == 7) {
            return value.smithing_trim_recipes;
        }
        else if constexpr (I == 8) {
            return value.potion_mix_entries;
        }
        else if constexpr (I == 9) {
            return value.container_mix_entries;
        }
        else if constexpr (I == 10) {
            return value.material_reducer_entries;
        }
        else {
            return value.clear_recipes;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v776::CreativeGroupInfoPayload> = true;

template <>
inline constexpr std::string_view struct_name_v<v776::CreativeGroupInfoPayload>{"CreativeGroupInfoPayload"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v776::CreativeGroupInfoPayload>{{
    "creative_item_category",
    "name",
    "icon",
}};

template <>
struct field_accessor<v776::CreativeGroupInfoPayload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.creative_item_category;
        }
        else if constexpr (I == 1) {
            return value.name;
        }
        else {
            return value.icon;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::CreativeGroupInfoPayload> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::CreativeGroupInfoPayload>{"CreativeGroupInfoPayload"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v2168::CreativeGroupInfoPayload>{{
    "creative_item_category",
    "name",
    "icon",
}};

template <>
struct field_accessor<v2168::CreativeGroupInfoPayload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.creative_item_category;
        }
        else if constexpr (I == 1) {
            return value.name;
        }
        else {
            return value.icon;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::CreativeItemEntryPayload> = true;

template <>
inline constexpr std::string_view struct_name_v<base::CreativeItemEntryPayload>{"CreativeItemEntryPayload"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<base::CreativeItemEntryPayload>{{
    "creative_item_net_id",
    "item_descriptor",
}};

template <>
struct field_accessor<base::CreativeItemEntryPayload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.creative_item_net_id;
        }
        else {
            return value.item_descriptor;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v776::CreativeItemEntryPayload> = true;

template <>
inline constexpr std::string_view struct_name_v<v776::CreativeItemEntryPayload>{"CreativeItemEntryPayload"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v776::CreativeItemEntryPayload>{{
    "creative_item_net_id",
    "item_descriptor",
    "group_index",
}};

template <>
struct field_accessor<v776::CreativeItemEntryPayload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.creative_item_net_id;
        }
        else if constexpr (I == 1) {
            return value.item_descriptor;
        }
        else {
            return value.group_index;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::CreativeItemEntryPayload> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::CreativeItemEntryPayload>{"CreativeItemEntryPayload"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v2168::CreativeItemEntryPayload>{{
    "creative_item_net_id",
    "item_descriptor",
    "group_index",
}};

template <>
struct field_accessor<v2168::CreativeItemEntryPayload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.creative_item_net_id;
        }
        else if constexpr (I == 1) {
            return value.item_descriptor;
        }
        else {
            return value.group_index;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::CreativeContentPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::CreativeContentPacket>{"CreativeContentPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::CreativeContentPacket>{{
    "entries",
}};

template <>
struct field_accessor<base::CreativeContentPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.entries;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v776::CreativeContentPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v776::CreativeContentPacket>{"CreativeContentPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v776::CreativeContentPacket>{{
    "groups",
    "entries",
}};

template <>
struct field_accessor<v776::CreativeContentPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.groups;
        }
        else {
            return value.entries;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::CreativeContentPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::CreativeContentPacket>{"CreativeContentPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2168::CreativeContentPacket>{{
    "groups",
    "entries",
}};

template <>
struct field_accessor<v2168::CreativeContentPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.groups;
        }
        else {
            return value.entries;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<LabTablePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<LabTablePacket>{"LabTablePacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<LabTablePacket>{{
    "type",
    "pos",
    "reaction",
}};

template <>
struct field_accessor<LabTablePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.type;
        }
        else if constexpr (I == 1) {
            return value.pos;
        }
        else {
            return value.reaction;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<UnlockedRecipesPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<UnlockedRecipesPacket>{"UnlockedRecipesPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<UnlockedRecipesPacket>{{
    "packet_type",
    "unlocked_recipes",
}};

template <>
struct field_accessor<UnlockedRecipesPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.packet_type;
        }
        else {
            return value.unlocked_recipes;
        }
    }
};

}  // namespace detail


template <>
struct Serializer<RecipeNetId> {
    static void serialize(BinaryWriter &stream, const RecipeNetId &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<RecipeNetId, std::error_code>;
};

template <>
struct Serializer<CreativeItemNetId> {
    static void serialize(BinaryWriter &stream, const CreativeItemNetId &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<CreativeItemNetId, std::error_code>;
};

template <>
struct Serializer<base::SerializedNetworkItemInstanceDescriptor> {
    static void serialize(BinaryWriter &stream, const base::SerializedNetworkItemInstanceDescriptor &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::SerializedNetworkItemInstanceDescriptor, std::error_code>;
};

template <>
struct Serializer<v2168::SerializedNetworkItemInstanceDescriptor> {
    static void serialize(BinaryWriter &stream, const v2168::SerializedNetworkItemInstanceDescriptor &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::SerializedNetworkItemInstanceDescriptor, std::error_code>;
};

template <>
struct Serializer<base::ItemDescriptor> {
    static void serialize(BinaryWriter &stream, const base::ItemDescriptor &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ItemDescriptor, std::error_code>;
};

template <>
struct Serializer<base::SerializedRecipeIngredient> {
    static void serialize(BinaryWriter &stream, const base::SerializedRecipeIngredient &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::SerializedRecipeIngredient, std::error_code>;
};

template <>
struct Serializer<v2168::SerializedRecipeIngredient> {
    static void serialize(BinaryWriter &stream, const v2168::SerializedRecipeIngredient &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::SerializedRecipeIngredient, std::error_code>;
};

template <>
struct Serializer<base::SerializedRecipeUnlockingRequirement> {
    static void serialize(BinaryWriter &stream, const base::SerializedRecipeUnlockingRequirement &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::SerializedRecipeUnlockingRequirement, std::error_code>;
};

template <>
struct Serializer<v2168::SerializedRecipeUnlockingRequirement> {
    static void serialize(BinaryWriter &stream, const v2168::SerializedRecipeUnlockingRequirement &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::SerializedRecipeUnlockingRequirement, std::error_code>;
};

template <>
struct Serializer<base::ShapedRecipePayload> {
    static void serialize(BinaryWriter &stream, const base::ShapedRecipePayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ShapedRecipePayload, std::error_code>;
};

template <>
struct Serializer<v2168::ShapedRecipePayload> {
    static void serialize(BinaryWriter &stream, const v2168::ShapedRecipePayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ShapedRecipePayload, std::error_code>;
};

template <>
struct Serializer<base::ShapelessRecipePayload> {
    static void serialize(BinaryWriter &stream, const base::ShapelessRecipePayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ShapelessRecipePayload, std::error_code>;
};

template <>
struct Serializer<v2168::ShapelessRecipePayload> {
    static void serialize(BinaryWriter &stream, const v2168::ShapelessRecipePayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ShapelessRecipePayload, std::error_code>;
};

template <>
struct Serializer<MultiRecipePayload> {
    static void serialize(BinaryWriter &stream, const MultiRecipePayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<MultiRecipePayload, std::error_code>;
};

template <>
struct Serializer<base::SmithingTransformRecipePayload> {
    static void serialize(BinaryWriter &stream, const base::SmithingTransformRecipePayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::SmithingTransformRecipePayload, std::error_code>;
};

template <>
struct Serializer<v2168::SmithingTransformRecipePayload> {
    static void serialize(BinaryWriter &stream, const v2168::SmithingTransformRecipePayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::SmithingTransformRecipePayload, std::error_code>;
};

template <>
struct Serializer<base::SmithingTrimRecipePayload> {
    static void serialize(BinaryWriter &stream, const base::SmithingTrimRecipePayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::SmithingTrimRecipePayload, std::error_code>;
};

template <>
struct Serializer<v2168::SmithingTrimRecipePayload> {
    static void serialize(BinaryWriter &stream, const v2168::SmithingTrimRecipePayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::SmithingTrimRecipePayload, std::error_code>;
};

template <>
struct Serializer<PotionMixDataEntry> {
    static void serialize(BinaryWriter &stream, const PotionMixDataEntry &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<PotionMixDataEntry, std::error_code>;
};

template <>
struct Serializer<ContainerMixDataEntry> {
    static void serialize(BinaryWriter &stream, const ContainerMixDataEntry &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<ContainerMixDataEntry, std::error_code>;
};

template <>
struct Serializer<MaterialReducerEntryOutput> {
    static void serialize(BinaryWriter &stream, const MaterialReducerEntryOutput &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<MaterialReducerEntryOutput, std::error_code>;
};

template <>
struct Serializer<MaterialReducerDataEntry> {
    static void serialize(BinaryWriter &stream, const MaterialReducerDataEntry &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<MaterialReducerDataEntry, std::error_code>;
};

template <>
struct Serializer<base::ShapedChemistryRecipePayload> {
    static void serialize(BinaryWriter &stream, const base::ShapedChemistryRecipePayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ShapedChemistryRecipePayload, std::error_code>;
};

template <>
struct Serializer<base::ShapelessChemistryRecipePayload> {
    static void serialize(BinaryWriter &stream, const base::ShapelessChemistryRecipePayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ShapelessChemistryRecipePayload, std::error_code>;
};

template <>
struct Serializer<base::CraftingDataEntry> {
    static void serialize(BinaryWriter &stream, const base::CraftingDataEntry &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::CraftingDataEntry, std::error_code>;
};

template <>
struct Serializer<v748::CraftingDataEntry> {
    static void serialize(BinaryWriter &stream, const v748::CraftingDataEntry &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v748::CraftingDataEntry, std::error_code>;
};

template <>
struct Serializer<v975::CraftingDataEntry> {
    static void serialize(BinaryWriter &stream, const v975::CraftingDataEntry &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v975::CraftingDataEntry, std::error_code>;
};

template <>
struct Serializer<base::CraftingDataPacket> {
    static void serialize(BinaryWriter &stream, const base::CraftingDataPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::CraftingDataPacket, std::error_code>;
};

template <>
struct Serializer<v748::CraftingDataPacket> {
    static void serialize(BinaryWriter &stream, const v748::CraftingDataPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v748::CraftingDataPacket, std::error_code>;
};

template <>
struct Serializer<v975::CraftingDataPacket> {
    static void serialize(BinaryWriter &stream, const v975::CraftingDataPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v975::CraftingDataPacket, std::error_code>;
};

template <>
struct Serializer<v2168::CraftingDataPacket> {
    static void serialize(BinaryWriter &stream, const v2168::CraftingDataPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::CraftingDataPacket, std::error_code>;
};

template <>
struct Serializer<v776::CreativeGroupInfoPayload> {
    static void serialize(BinaryWriter &stream, const v776::CreativeGroupInfoPayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v776::CreativeGroupInfoPayload, std::error_code>;
};

template <>
struct Serializer<v2168::CreativeGroupInfoPayload> {
    static void serialize(BinaryWriter &stream, const v2168::CreativeGroupInfoPayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::CreativeGroupInfoPayload, std::error_code>;
};

template <>
struct Serializer<base::CreativeItemEntryPayload> {
    static void serialize(BinaryWriter &stream, const base::CreativeItemEntryPayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::CreativeItemEntryPayload, std::error_code>;
};

template <>
struct Serializer<v776::CreativeItemEntryPayload> {
    static void serialize(BinaryWriter &stream, const v776::CreativeItemEntryPayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v776::CreativeItemEntryPayload, std::error_code>;
};

template <>
struct Serializer<v2168::CreativeItemEntryPayload> {
    static void serialize(BinaryWriter &stream, const v2168::CreativeItemEntryPayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::CreativeItemEntryPayload, std::error_code>;
};

template <>
struct Serializer<base::CreativeContentPacket> {
    static void serialize(BinaryWriter &stream, const base::CreativeContentPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::CreativeContentPacket, std::error_code>;
};

template <>
struct Serializer<v776::CreativeContentPacket> {
    static void serialize(BinaryWriter &stream, const v776::CreativeContentPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v776::CreativeContentPacket, std::error_code>;
};

template <>
struct Serializer<v2168::CreativeContentPacket> {
    static void serialize(BinaryWriter &stream, const v2168::CreativeContentPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::CreativeContentPacket, std::error_code>;
};

template <>
struct Serializer<LabTablePacket> {
    static void serialize(BinaryWriter &stream, const LabTablePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<LabTablePacket, std::error_code>;
};

template <>
struct Serializer<UnlockedRecipesPacket> {
    static void serialize(BinaryWriter &stream, const UnlockedRecipesPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<UnlockedRecipesPacket, std::error_code>;
};
using CraftingDataEntryType = CraftingDataEntryType_<2225>;
using SerializedNetworkItemInstanceDescriptor = SerializedNetworkItemInstanceDescriptor_<2225>;
using SerializedRecipeIngredient = SerializedRecipeIngredient_<2225>;
using SerializedRecipeUnlockingRequirement = SerializedRecipeUnlockingRequirement_<2225>;
using ShapedRecipePayload = ShapedRecipePayload_<2225>;
using ShapelessRecipePayload = ShapelessRecipePayload_<2225>;
using SmithingTransformRecipePayload = SmithingTransformRecipePayload_<2225>;
using SmithingTrimRecipePayload = SmithingTrimRecipePayload_<2225>;
using CraftingDataPacket = CraftingDataPacket_<2225>;
using CreativeGroupInfoPayload = CreativeGroupInfoPayload_<2225>;
using CreativeItemEntryPayload = CreativeItemEntryPayload_<2225>;
using CreativeContentPacket = CreativeContentPacket_<2225>;

}  // namespace bedrock::protocol
