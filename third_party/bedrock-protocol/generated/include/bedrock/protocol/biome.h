#pragma once

#include <array>
#include <compare>
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
#include <bedrock/protocol/nbt.hpp>
#include <bedrock/protocol/packet.hpp>
#include <bedrock/protocol/serializer.hpp>
#include <bedrock/protocol/stream.hpp>

#include <bedrock/protocol/common.h>
#include <bedrock/protocol/molang.h>

namespace bedrock::protocol {

struct BiomeStringIndex {
    constexpr BiomeStringIndex() = default;
    explicit constexpr BiomeStringIndex(std::uint16_t value) : value_(value) {}
    constexpr operator std::uint16_t() const { return value_; }
    friend constexpr bool operator==(const BiomeStringIndex &, const BiomeStringIndex &) = default;
    friend constexpr auto operator<=>(const BiomeStringIndex &, const BiomeStringIndex &) = default;

  private:
    std::uint16_t value_{};
};

enum class VillageType : std::uint8_t {
    Desert = 0,
    Ice = 1,
    Savanna = 2,
    Taiga = 3,
    Default = 4,
};

enum class BiomeTemperatureCategory : std::uint8_t {
    Medium = 0,
    Warm = 1,
    Lukewarm = 2,
    Cold = 3,
    Frozen = 4,
    Count = 5,
};

enum class CoordinateEvaluationOrder : int {
    XYZ = 0,
    XZY = 1,
    YXZ = 2,
    YZX = 3,
    ZXY = 4,
    ZYX = 5,
};

enum class RandomDistributionType : int {
    SingleValued = 0,
    Uniform = 1,
    Gaussian = 2,
    InverseGaussian = 3,
    FixedGrid = 4,
    JitteredGrid = 5,
    Triangle = 6,
};

struct FloatRange {
    float min{};
    float max{};
};

struct BiomeSurfaceMaterialData {
    BlockRuntimeId top_block{};
    BlockRuntimeId mid_block{};
    BlockRuntimeId sea_floor_block{};
    BlockRuntimeId foundation_block{};
    BlockRuntimeId sea_block{};
    std::int32_t sea_floor_depth{};
};

struct BiomeMesaSurfaceData {
    BlockRuntimeId clay_material{};
    BlockRuntimeId hard_clay_material{};
    bool bryce_pillars{};
    bool has_forest{};
};

struct BiomeCappedSurfaceData {
    std::vector<std::uint32_t> floor_blocks{};
    std::vector<std::uint32_t> ceiling_blocks{};
    std::optional<std::uint32_t> sea_block{};
    std::optional<std::uint32_t> foundation_block{};
    std::optional<std::uint32_t> beach_block{};
};

struct BiomeMountainParamsData {
    BlockRuntimeId steep_block{};
    bool north_slopes{};
    bool south_slopes{};
    bool west_slopes{};
    bool east_slopes{};
    bool top_slide_enabled{};
};

struct BiomeWeightedData {
    BiomeStringIndex biome_identifier{};
    std::uint32_t weight{};
};

struct BiomeConditionalTransformationData {
    std::vector<BiomeWeightedData> transforms_into{};
    BiomeStringIndex condition_json{};
    std::uint32_t min_passing_neighbors{};
};

struct BiomeWeightedTemperatureData {
    BiomeTemperatureCategory temperature{};
    std::uint32_t weight{};
};

struct BiomeOverworldGenRulesData {
    std::vector<BiomeWeightedData> hills_transformations{};
    std::vector<BiomeWeightedData> mutate_transformations{};
    std::vector<BiomeWeightedData> river_transformations{};
    std::vector<BiomeWeightedData> shore_transformations{};
    std::vector<BiomeConditionalTransformationData> pre_hills_edge{};
    std::vector<BiomeConditionalTransformationData> post_shore_edge{};
    std::vector<BiomeWeightedTemperatureData> climate{};
};

struct BiomeMultinoiseGenRulesData {
    float temperature{};
    float humidity{};
    float altitude{};
    float weirdness{};
    float weight{};
};

struct BiomeLegacyWorldGenRulesData {
    std::vector<BiomeConditionalTransformationData> legacy_pre_hills_edge{};
};

struct BiomeReplacementData {
    BiomeStringIndex replacement_biome{};
    BiomeStringIndex dimension{};
    std::vector<std::uint16_t> target_biomes{};
    float amount{};
    float noise_frequency_scale{};
    std::uint32_t replacement_index{};
};

struct BiomeReplacementsData {
    std::vector<BiomeReplacementData> biome_replacements{};
};

struct BiomeTagsData {
    std::vector<std::uint16_t> tags{};
};

struct BiomeStringList {
    std::vector<std::string> strings{};
};

namespace base {

struct BiomeNoiseGradientSurfaceData {
    std::vector<std::uint32_t> non_replaceable_blocks{};
    std::vector<std::uint32_t> gradient_blocks{};
    std::string noise_seed_string{};
    std::int32_t first_octave{};
    std::vector<float> amplitudes{};
};

struct BiomeSurfaceBuilderData {
    std::optional<BiomeSurfaceMaterialData> surface_materials{};
    bool has_default_overworld_surface{};
    bool has_swamp_surface{};
    bool has_frozen_ocean_surface{};
    bool has_the_end_surface{};
    std::optional<BiomeMesaSurfaceData> mesa_surface{};
    std::optional<BiomeCappedSurfaceData> capped_surface{};
    std::optional<base::BiomeNoiseGradientSurfaceData> noise_gradient_surface{};
};

struct BiomeClimateData {
    float temperature{};
    float downfall{};
    float red_spore_density{};
    float blue_spore_density{};
    float ash_density{};
    float white_ash_density{};
    float snow_accumulation_min{};
    float snow_accumulation_max{};
};

struct BiomeCoordinateData {
    base::ExpressionOp min_value_type{};
    BiomeStringIndex min_value{};
    base::ExpressionOp max_value_type{};
    BiomeStringIndex max_value{};
    std::uint32_t grid_offset{};
    std::uint32_t grid_step_size{};
    RandomDistributionType distribution{};
};

struct BiomeScatterParamData {
    std::vector<base::BiomeCoordinateData> coordinates{};
    CoordinateEvaluationOrder eval_order{};
    base::ExpressionOp chance_percent_type{};
    BiomeStringIndex chance_percent{};
    std::int32_t chance_numerator{};
    std::int32_t chance_denominator{};
    base::ExpressionOp iterations_type{};
    BiomeStringIndex iterations{};
};

struct BiomeConsolidatedFeatureData {
    base::BiomeScatterParamData scatter{};
    BiomeStringIndex feature{};
    BiomeStringIndex identifier{};
    BiomeStringIndex pass{};
    bool can_use_internal_feature{};
};

struct BiomeConsolidatedFeaturesData {
    std::vector<base::BiomeConsolidatedFeatureData> features{};
};

struct BiomeElementData {
    float noise_freq_scale{};
    float noise_lower_bound{};
    float noise_upper_bound{};
    base::ExpressionOp height_min_type{};
    BiomeStringIndex height_min{};
    base::ExpressionOp height_max_type{};
    BiomeStringIndex height_max{};
    BiomeSurfaceMaterialData adjusted_materials{};
};

struct BiomeSurfaceMaterialAdjustmentData {
    std::vector<base::BiomeElementData> adjustments{};
};

struct BiomeDefinitionChunkGenData {
    std::optional<base::BiomeClimateData> climate{};
    std::optional<base::BiomeConsolidatedFeaturesData> consolidated_features{};
    std::optional<BiomeMountainParamsData> mountain_params{};
    std::optional<base::BiomeSurfaceMaterialAdjustmentData> surface_material_adjustments{};
    std::optional<BiomeSurfaceMaterialData> surface_materials{};
    bool has_swamp_surface{};
    bool has_frozen_ocean_surface{};
    bool has_the_end_surface{};
    std::optional<BiomeMesaSurfaceData> mesa_surface{};
    std::optional<BiomeCappedSurfaceData> capped_surface{};
    std::optional<BiomeOverworldGenRulesData> overworld_gen_rules{};
    std::optional<BiomeMultinoiseGenRulesData> multinoise_gen_rules{};
    std::optional<BiomeLegacyWorldGenRulesData> legacy_world_gen_rules{};
};

struct BiomeDefinitionData {
    std::optional<std::uint16_t> id{};
    float temperature{};
    float downfall{};
    float red_spore_density{};
    float blue_spore_density{};
    float ash_density{};
    float white_ash_density{};
    float depth{};
    float scale{};
    std::int32_t map_water_color_argb{};
    bool rain{};
    std::optional<BiomeTagsData> tags{};
    std::optional<base::BiomeDefinitionChunkGenData> chunk_gen_data{};
};

struct BiomeDefinitionListPacket {
    static constexpr int Id = 122;
    CompoundTag biome_data{};
};

struct CompressedBiomeDefinitionListPacket {
    static constexpr int Id = 301;
    std::string compressed_biome_data{};
};

}  // namespace base

namespace v800 {

using BiomeNoiseGradientSurfaceData = base::BiomeNoiseGradientSurfaceData;

using BiomeSurfaceBuilderData = base::BiomeSurfaceBuilderData;

using BiomeClimateData = base::BiomeClimateData;

struct BiomeCoordinateData {
    v800::ExpressionOp min_value_type{};
    BiomeStringIndex min_value{};
    v800::ExpressionOp max_value_type{};
    BiomeStringIndex max_value{};
    std::uint32_t grid_offset{};
    std::uint32_t grid_step_size{};
    RandomDistributionType distribution{};
};

struct BiomeScatterParamData {
    std::vector<v800::BiomeCoordinateData> coordinates{};
    CoordinateEvaluationOrder eval_order{};
    v800::ExpressionOp chance_percent_type{};
    BiomeStringIndex chance_percent{};
    std::int32_t chance_numerator{};
    std::int32_t chance_denominator{};
    v800::ExpressionOp iterations_type{};
    BiomeStringIndex iterations{};
};

struct BiomeConsolidatedFeatureData {
    v800::BiomeScatterParamData scatter{};
    BiomeStringIndex feature{};
    BiomeStringIndex identifier{};
    BiomeStringIndex pass{};
    bool can_use_internal_feature{};
};

struct BiomeConsolidatedFeaturesData {
    std::vector<v800::BiomeConsolidatedFeatureData> features{};
};

struct BiomeElementData {
    float noise_freq_scale{};
    float noise_lower_bound{};
    float noise_upper_bound{};
    v800::ExpressionOp height_min_type{};
    BiomeStringIndex height_min{};
    v800::ExpressionOp height_max_type{};
    BiomeStringIndex height_max{};
    BiomeSurfaceMaterialData adjusted_materials{};
};

struct BiomeSurfaceMaterialAdjustmentData {
    std::vector<v800::BiomeElementData> adjustments{};
};

struct BiomeDefinitionChunkGenData {
    std::optional<base::BiomeClimateData> climate{};
    std::optional<v800::BiomeConsolidatedFeaturesData> consolidated_features{};
    std::optional<BiomeMountainParamsData> mountain_params{};
    std::optional<v800::BiomeSurfaceMaterialAdjustmentData> surface_material_adjustments{};
    std::optional<BiomeSurfaceMaterialData> surface_materials{};
    bool has_swamp_surface{};
    bool has_frozen_ocean_surface{};
    bool has_the_end_surface{};
    std::optional<BiomeMesaSurfaceData> mesa_surface{};
    std::optional<BiomeCappedSurfaceData> capped_surface{};
    std::optional<BiomeOverworldGenRulesData> overworld_gen_rules{};
    std::optional<BiomeMultinoiseGenRulesData> multinoise_gen_rules{};
    std::optional<BiomeLegacyWorldGenRulesData> legacy_world_gen_rules{};
    std::optional<BiomeReplacementsData> replace_biomes{};
};

struct BiomeDefinitionData {
    std::optional<std::uint16_t> id{};
    float temperature{};
    float downfall{};
    float red_spore_density{};
    float blue_spore_density{};
    float ash_density{};
    float white_ash_density{};
    float depth{};
    float scale{};
    std::int32_t map_water_color_argb{};
    bool rain{};
    std::optional<BiomeTagsData> tags{};
    std::optional<v800::BiomeDefinitionChunkGenData> chunk_gen_data{};
};

struct BiomeDefinitionListPacket {
    static constexpr int Id = 122;
    std::map<BiomeStringIndex, v800::BiomeDefinitionData> biome_data{};
    BiomeStringList string_list{};
};

}  // namespace v800

namespace v827 {

using BiomeNoiseGradientSurfaceData = base::BiomeNoiseGradientSurfaceData;

using BiomeSurfaceBuilderData = base::BiomeSurfaceBuilderData;

using BiomeClimateData = base::BiomeClimateData;

using BiomeCoordinateData = v800::BiomeCoordinateData;

using BiomeScatterParamData = v800::BiomeScatterParamData;

using BiomeConsolidatedFeatureData = v800::BiomeConsolidatedFeatureData;

using BiomeConsolidatedFeaturesData = v800::BiomeConsolidatedFeaturesData;

using BiomeElementData = v800::BiomeElementData;

using BiomeSurfaceMaterialAdjustmentData = v800::BiomeSurfaceMaterialAdjustmentData;

using BiomeDefinitionChunkGenData = v800::BiomeDefinitionChunkGenData;

struct BiomeDefinitionData {
    std::uint16_t id{};
    float temperature{};
    float downfall{};
    float red_spore_density{};
    float blue_spore_density{};
    float ash_density{};
    float white_ash_density{};
    float depth{};
    float scale{};
    std::int32_t map_water_color_argb{};
    bool rain{};
    std::optional<BiomeTagsData> tags{};
    std::optional<v800::BiomeDefinitionChunkGenData> chunk_gen_data{};
};

struct BiomeDefinitionListPacket {
    static constexpr int Id = 122;
    std::map<BiomeStringIndex, v827::BiomeDefinitionData> biome_data{};
    BiomeStringList string_list{};
};

}  // namespace v827

namespace v844 {

using BiomeNoiseGradientSurfaceData = base::BiomeNoiseGradientSurfaceData;

using BiomeSurfaceBuilderData = base::BiomeSurfaceBuilderData;

struct BiomeClimateData {
    float temperature{};
    float downfall{};
    float snow_accumulation_min{};
    float snow_accumulation_max{};
};

using BiomeCoordinateData = v800::BiomeCoordinateData;

using BiomeScatterParamData = v800::BiomeScatterParamData;

using BiomeConsolidatedFeatureData = v800::BiomeConsolidatedFeatureData;

using BiomeConsolidatedFeaturesData = v800::BiomeConsolidatedFeaturesData;

using BiomeElementData = v800::BiomeElementData;

using BiomeSurfaceMaterialAdjustmentData = v800::BiomeSurfaceMaterialAdjustmentData;

struct BiomeDefinitionChunkGenData {
    std::optional<v844::BiomeClimateData> climate{};
    std::optional<v800::BiomeConsolidatedFeaturesData> consolidated_features{};
    std::optional<BiomeMountainParamsData> mountain_params{};
    std::optional<v800::BiomeSurfaceMaterialAdjustmentData> surface_material_adjustments{};
    std::optional<BiomeSurfaceMaterialData> surface_materials{};
    bool has_default_overworld_surface{};
    bool has_swamp_surface{};
    bool has_frozen_ocean_surface{};
    bool has_the_end_surface{};
    std::optional<BiomeMesaSurfaceData> mesa_surface{};
    std::optional<BiomeCappedSurfaceData> capped_surface{};
    std::optional<BiomeOverworldGenRulesData> overworld_gen_rules{};
    std::optional<BiomeMultinoiseGenRulesData> multinoise_gen_rules{};
    std::optional<BiomeLegacyWorldGenRulesData> legacy_world_gen_rules{};
    std::optional<BiomeReplacementsData> replace_biomes{};
};

struct BiomeDefinitionData {
    std::uint16_t id{};
    float temperature{};
    float downfall{};
    float foliage_snow{};
    float depth{};
    float scale{};
    std::int32_t map_water_color_argb{};
    bool rain{};
    std::optional<BiomeTagsData> tags{};
    std::optional<v844::BiomeDefinitionChunkGenData> chunk_gen_data{};
};

struct BiomeDefinitionListPacket {
    static constexpr int Id = 122;
    std::map<BiomeStringIndex, v844::BiomeDefinitionData> biome_data{};
    BiomeStringList string_list{};
};

}  // namespace v844

namespace v859 {

using BiomeNoiseGradientSurfaceData = base::BiomeNoiseGradientSurfaceData;

using BiomeSurfaceBuilderData = base::BiomeSurfaceBuilderData;

using BiomeClimateData = v844::BiomeClimateData;

struct BiomeCoordinateData {
    v859::ExpressionOp min_value_type{};
    BiomeStringIndex min_value{};
    v859::ExpressionOp max_value_type{};
    BiomeStringIndex max_value{};
    std::uint32_t grid_offset{};
    std::uint32_t grid_step_size{};
    RandomDistributionType distribution{};
};

struct BiomeScatterParamData {
    std::vector<v859::BiomeCoordinateData> coordinates{};
    CoordinateEvaluationOrder eval_order{};
    v859::ExpressionOp chance_percent_type{};
    BiomeStringIndex chance_percent{};
    std::int32_t chance_numerator{};
    std::int32_t chance_denominator{};
    v859::ExpressionOp iterations_type{};
    BiomeStringIndex iterations{};
};

struct BiomeConsolidatedFeatureData {
    v859::BiomeScatterParamData scatter{};
    BiomeStringIndex feature{};
    BiomeStringIndex identifier{};
    BiomeStringIndex pass{};
    bool can_use_internal_feature{};
};

struct BiomeConsolidatedFeaturesData {
    std::vector<v859::BiomeConsolidatedFeatureData> features{};
};

struct BiomeElementData {
    float noise_freq_scale{};
    float noise_lower_bound{};
    float noise_upper_bound{};
    v859::ExpressionOp height_min_type{};
    BiomeStringIndex height_min{};
    v859::ExpressionOp height_max_type{};
    BiomeStringIndex height_max{};
    BiomeSurfaceMaterialData adjusted_materials{};
};

struct BiomeSurfaceMaterialAdjustmentData {
    std::vector<v859::BiomeElementData> adjustments{};
};

struct BiomeDefinitionChunkGenData {
    std::optional<v844::BiomeClimateData> climate{};
    std::optional<v859::BiomeConsolidatedFeaturesData> consolidated_features{};
    std::optional<BiomeMountainParamsData> mountain_params{};
    std::optional<v859::BiomeSurfaceMaterialAdjustmentData> surface_material_adjustments{};
    std::optional<BiomeSurfaceMaterialData> surface_materials{};
    bool has_default_overworld_surface{};
    bool has_swamp_surface{};
    bool has_frozen_ocean_surface{};
    bool has_the_end_surface{};
    std::optional<BiomeMesaSurfaceData> mesa_surface{};
    std::optional<BiomeCappedSurfaceData> capped_surface{};
    std::optional<BiomeOverworldGenRulesData> overworld_gen_rules{};
    std::optional<BiomeMultinoiseGenRulesData> multinoise_gen_rules{};
    std::optional<BiomeLegacyWorldGenRulesData> legacy_world_gen_rules{};
    std::optional<BiomeReplacementsData> replace_biomes{};
};

struct BiomeDefinitionData {
    std::uint16_t id{};
    float temperature{};
    float downfall{};
    float foliage_snow{};
    float depth{};
    float scale{};
    std::int32_t map_water_color_argb{};
    bool rain{};
    std::optional<BiomeTagsData> tags{};
    std::optional<v859::BiomeDefinitionChunkGenData> chunk_gen_data{};
};

struct BiomeDefinitionListPacket {
    static constexpr int Id = 122;
    std::map<BiomeStringIndex, v859::BiomeDefinitionData> biome_data{};
    BiomeStringList string_list{};
};

}  // namespace v859

namespace v924 {

using BiomeNoiseGradientSurfaceData = base::BiomeNoiseGradientSurfaceData;

using BiomeSurfaceBuilderData = base::BiomeSurfaceBuilderData;

using BiomeClimateData = v844::BiomeClimateData;

using BiomeCoordinateData = v859::BiomeCoordinateData;

using BiomeScatterParamData = v859::BiomeScatterParamData;

using BiomeConsolidatedFeatureData = v859::BiomeConsolidatedFeatureData;

using BiomeConsolidatedFeaturesData = v859::BiomeConsolidatedFeaturesData;

using BiomeElementData = v859::BiomeElementData;

using BiomeSurfaceMaterialAdjustmentData = v859::BiomeSurfaceMaterialAdjustmentData;

struct BiomeDefinitionChunkGenData {
    std::optional<v844::BiomeClimateData> climate{};
    std::optional<v859::BiomeConsolidatedFeaturesData> consolidated_features{};
    std::optional<BiomeMountainParamsData> mountain_params{};
    std::optional<v859::BiomeSurfaceMaterialAdjustmentData> surface_material_adjustments{};
    std::optional<BiomeSurfaceMaterialData> surface_materials{};
    bool has_default_overworld_surface{};
    bool has_swamp_surface{};
    bool has_frozen_ocean_surface{};
    bool has_the_end_surface{};
    std::optional<BiomeMesaSurfaceData> mesa_surface{};
    std::optional<BiomeCappedSurfaceData> capped_surface{};
    std::optional<BiomeOverworldGenRulesData> overworld_gen_rules{};
    std::optional<BiomeMultinoiseGenRulesData> multinoise_gen_rules{};
    std::optional<BiomeLegacyWorldGenRulesData> legacy_world_gen_rules{};
    std::optional<BiomeReplacementsData> replace_biomes{};
    std::optional<VillageType> village_type{};
};

struct BiomeDefinitionData {
    std::uint16_t id{};
    float temperature{};
    float downfall{};
    float foliage_snow{};
    float depth{};
    float scale{};
    std::int32_t map_water_color_argb{};
    bool rain{};
    std::optional<BiomeTagsData> tags{};
    std::optional<v924::BiomeDefinitionChunkGenData> chunk_gen_data{};
};

struct BiomeDefinitionListPacket {
    static constexpr int Id = 122;
    std::map<BiomeStringIndex, v924::BiomeDefinitionData> biome_data{};
    BiomeStringList string_list{};
};

}  // namespace v924

namespace v975 {

using BiomeNoiseGradientSurfaceData = base::BiomeNoiseGradientSurfaceData;

using BiomeSurfaceBuilderData = base::BiomeSurfaceBuilderData;

using BiomeClimateData = v844::BiomeClimateData;

using BiomeCoordinateData = v859::BiomeCoordinateData;

using BiomeScatterParamData = v859::BiomeScatterParamData;

using BiomeConsolidatedFeatureData = v859::BiomeConsolidatedFeatureData;

using BiomeConsolidatedFeaturesData = v859::BiomeConsolidatedFeaturesData;

using BiomeElementData = v859::BiomeElementData;

using BiomeSurfaceMaterialAdjustmentData = v859::BiomeSurfaceMaterialAdjustmentData;

struct BiomeDefinitionChunkGenData {
    std::optional<v844::BiomeClimateData> climate{};
    std::optional<v859::BiomeConsolidatedFeaturesData> consolidated_features{};
    std::optional<BiomeMountainParamsData> mountain_params{};
    std::optional<v859::BiomeSurfaceMaterialAdjustmentData> surface_material_adjustments{};
    std::optional<BiomeOverworldGenRulesData> overworld_gen_rules{};
    std::optional<BiomeMultinoiseGenRulesData> multinoise_gen_rules{};
    std::optional<BiomeLegacyWorldGenRulesData> legacy_world_gen_rules{};
    std::optional<BiomeReplacementsData> replace_biomes{};
    std::optional<VillageType> village_type{};
    std::optional<base::BiomeSurfaceBuilderData> surface_builder_data{};
    std::optional<base::BiomeSurfaceBuilderData> subsurface_builder_data{};
};

struct BiomeDefinitionData {
    std::uint16_t id{};
    float temperature{};
    float downfall{};
    float foliage_snow{};
    float depth{};
    float scale{};
    std::int32_t map_water_color_argb{};
    bool rain{};
    std::optional<BiomeTagsData> tags{};
    std::optional<v975::BiomeDefinitionChunkGenData> chunk_gen_data{};
};

struct BiomeDefinitionListPacket {
    static constexpr int Id = 122;
    std::map<BiomeStringIndex, v975::BiomeDefinitionData> biome_data{};
    BiomeStringList string_list{};
};

}  // namespace v975

namespace v1001 {

struct NoiseDescriptor {
    std::string name{};
    std::int32_t first_octave{};
    std::vector<float> amplitudes{};
};

struct SerializedNoiseBlockSpecifier {
    std::string noise{};
    float threshold{};
    FloatRange range{};
    BlockRuntimeId block_runtime_id{};
};

struct BiomeNoiseGradientSurfaceData {
    std::vector<std::uint32_t> non_replaceable_blocks{};
    std::vector<v1001::SerializedNoiseBlockSpecifier> gradient_block_ranges{};
    v1001::NoiseDescriptor noise_descriptor{};
};

struct BiomeSurfaceBuilderData {
    std::optional<BiomeSurfaceMaterialData> surface_materials{};
    bool has_default_overworld_surface{};
    bool has_swamp_surface{};
    bool has_frozen_ocean_surface{};
    bool has_the_end_surface{};
    std::optional<BiomeMesaSurfaceData> mesa_surface{};
    std::optional<BiomeCappedSurfaceData> capped_surface{};
    std::optional<v1001::BiomeNoiseGradientSurfaceData> noise_gradient_surface{};
};

using BiomeClimateData = v844::BiomeClimateData;

using BiomeCoordinateData = v859::BiomeCoordinateData;

using BiomeScatterParamData = v859::BiomeScatterParamData;

using BiomeConsolidatedFeatureData = v859::BiomeConsolidatedFeatureData;

using BiomeConsolidatedFeaturesData = v859::BiomeConsolidatedFeaturesData;

using BiomeElementData = v859::BiomeElementData;

using BiomeSurfaceMaterialAdjustmentData = v859::BiomeSurfaceMaterialAdjustmentData;

struct BiomeDefinitionChunkGenData {
    std::optional<v844::BiomeClimateData> climate{};
    std::optional<v859::BiomeConsolidatedFeaturesData> consolidated_features{};
    std::optional<BiomeMountainParamsData> mountain_params{};
    std::optional<v859::BiomeSurfaceMaterialAdjustmentData> surface_material_adjustments{};
    std::optional<BiomeOverworldGenRulesData> overworld_gen_rules{};
    std::optional<BiomeMultinoiseGenRulesData> multinoise_gen_rules{};
    std::optional<BiomeLegacyWorldGenRulesData> legacy_world_gen_rules{};
    std::optional<BiomeReplacementsData> replace_biomes{};
    std::optional<VillageType> village_type{};
    std::optional<v1001::BiomeSurfaceBuilderData> surface_builder_data{};
    std::optional<v1001::BiomeSurfaceBuilderData> subsurface_builder_data{};
};

struct BiomeDefinitionData {
    std::uint16_t id{};
    float temperature{};
    float downfall{};
    float foliage_snow{};
    float depth{};
    float scale{};
    std::int32_t map_water_color_argb{};
    bool rain{};
    std::optional<BiomeTagsData> tags{};
    std::optional<v1001::BiomeDefinitionChunkGenData> chunk_gen_data{};
};

struct BiomeDefinitionListPacket {
    static constexpr int Id = 122;
    std::map<BiomeStringIndex, v1001::BiomeDefinitionData> biome_data{};
    BiomeStringList string_list{};
};

}  // namespace v1001

namespace detail {

template <int V>
struct NoiseDescriptor_;

template <int V> requires (V >= 1001)
struct NoiseDescriptor_<V> { using type = v1001::NoiseDescriptor; };

template <int V>
struct SerializedNoiseBlockSpecifier_;

template <int V> requires (V >= 1001)
struct SerializedNoiseBlockSpecifier_<V> { using type = v1001::SerializedNoiseBlockSpecifier; };

template <int V>
struct BiomeNoiseGradientSurfaceData_;

template <int V> requires (V < 1001)
struct BiomeNoiseGradientSurfaceData_<V> { using type = base::BiomeNoiseGradientSurfaceData; };

template <int V> requires (V >= 1001)
struct BiomeNoiseGradientSurfaceData_<V> { using type = v1001::BiomeNoiseGradientSurfaceData; };

template <int V>
struct BiomeSurfaceBuilderData_;

template <int V> requires (V < 1001)
struct BiomeSurfaceBuilderData_<V> { using type = base::BiomeSurfaceBuilderData; };

template <int V> requires (V >= 1001)
struct BiomeSurfaceBuilderData_<V> { using type = v1001::BiomeSurfaceBuilderData; };

template <int V>
struct BiomeClimateData_;

template <int V> requires (V < 844)
struct BiomeClimateData_<V> { using type = base::BiomeClimateData; };

template <int V> requires (V >= 844)
struct BiomeClimateData_<V> { using type = v844::BiomeClimateData; };

template <int V>
struct BiomeCoordinateData_;

template <int V> requires (V < 800)
struct BiomeCoordinateData_<V> { using type = base::BiomeCoordinateData; };

template <int V> requires (V >= 800 && V < 859)
struct BiomeCoordinateData_<V> { using type = v800::BiomeCoordinateData; };

template <int V> requires (V >= 859)
struct BiomeCoordinateData_<V> { using type = v859::BiomeCoordinateData; };

template <int V>
struct BiomeScatterParamData_;

template <int V> requires (V < 800)
struct BiomeScatterParamData_<V> { using type = base::BiomeScatterParamData; };

template <int V> requires (V >= 800 && V < 859)
struct BiomeScatterParamData_<V> { using type = v800::BiomeScatterParamData; };

template <int V> requires (V >= 859)
struct BiomeScatterParamData_<V> { using type = v859::BiomeScatterParamData; };

template <int V>
struct BiomeConsolidatedFeatureData_;

template <int V> requires (V < 800)
struct BiomeConsolidatedFeatureData_<V> { using type = base::BiomeConsolidatedFeatureData; };

template <int V> requires (V >= 800 && V < 859)
struct BiomeConsolidatedFeatureData_<V> { using type = v800::BiomeConsolidatedFeatureData; };

template <int V> requires (V >= 859)
struct BiomeConsolidatedFeatureData_<V> { using type = v859::BiomeConsolidatedFeatureData; };

template <int V>
struct BiomeConsolidatedFeaturesData_;

template <int V> requires (V < 800)
struct BiomeConsolidatedFeaturesData_<V> { using type = base::BiomeConsolidatedFeaturesData; };

template <int V> requires (V >= 800 && V < 859)
struct BiomeConsolidatedFeaturesData_<V> { using type = v800::BiomeConsolidatedFeaturesData; };

template <int V> requires (V >= 859)
struct BiomeConsolidatedFeaturesData_<V> { using type = v859::BiomeConsolidatedFeaturesData; };

template <int V>
struct BiomeElementData_;

template <int V> requires (V < 800)
struct BiomeElementData_<V> { using type = base::BiomeElementData; };

template <int V> requires (V >= 800 && V < 859)
struct BiomeElementData_<V> { using type = v800::BiomeElementData; };

template <int V> requires (V >= 859)
struct BiomeElementData_<V> { using type = v859::BiomeElementData; };

template <int V>
struct BiomeSurfaceMaterialAdjustmentData_;

template <int V> requires (V < 800)
struct BiomeSurfaceMaterialAdjustmentData_<V> { using type = base::BiomeSurfaceMaterialAdjustmentData; };

template <int V> requires (V >= 800 && V < 859)
struct BiomeSurfaceMaterialAdjustmentData_<V> { using type = v800::BiomeSurfaceMaterialAdjustmentData; };

template <int V> requires (V >= 859)
struct BiomeSurfaceMaterialAdjustmentData_<V> { using type = v859::BiomeSurfaceMaterialAdjustmentData; };

template <int V>
struct BiomeDefinitionChunkGenData_;

template <int V> requires (V < 800)
struct BiomeDefinitionChunkGenData_<V> { using type = base::BiomeDefinitionChunkGenData; };

template <int V> requires (V >= 800 && V < 844)
struct BiomeDefinitionChunkGenData_<V> { using type = v800::BiomeDefinitionChunkGenData; };

template <int V> requires (V >= 844 && V < 859)
struct BiomeDefinitionChunkGenData_<V> { using type = v844::BiomeDefinitionChunkGenData; };

template <int V> requires (V >= 859 && V < 924)
struct BiomeDefinitionChunkGenData_<V> { using type = v859::BiomeDefinitionChunkGenData; };

template <int V> requires (V >= 924 && V < 975)
struct BiomeDefinitionChunkGenData_<V> { using type = v924::BiomeDefinitionChunkGenData; };

template <int V> requires (V >= 975 && V < 1001)
struct BiomeDefinitionChunkGenData_<V> { using type = v975::BiomeDefinitionChunkGenData; };

template <int V> requires (V >= 1001)
struct BiomeDefinitionChunkGenData_<V> { using type = v1001::BiomeDefinitionChunkGenData; };

template <int V>
struct BiomeDefinitionData_;

template <int V> requires (V < 800)
struct BiomeDefinitionData_<V> { using type = base::BiomeDefinitionData; };

template <int V> requires (V >= 800 && V < 827)
struct BiomeDefinitionData_<V> { using type = v800::BiomeDefinitionData; };

template <int V> requires (V >= 827 && V < 844)
struct BiomeDefinitionData_<V> { using type = v827::BiomeDefinitionData; };

template <int V> requires (V >= 844 && V < 859)
struct BiomeDefinitionData_<V> { using type = v844::BiomeDefinitionData; };

template <int V> requires (V >= 859 && V < 924)
struct BiomeDefinitionData_<V> { using type = v859::BiomeDefinitionData; };

template <int V> requires (V >= 924 && V < 975)
struct BiomeDefinitionData_<V> { using type = v924::BiomeDefinitionData; };

template <int V> requires (V >= 975 && V < 1001)
struct BiomeDefinitionData_<V> { using type = v975::BiomeDefinitionData; };

template <int V> requires (V >= 1001)
struct BiomeDefinitionData_<V> { using type = v1001::BiomeDefinitionData; };

template <int V>
struct BiomeDefinitionListPacket_;

template <int V> requires (V < 800)
struct BiomeDefinitionListPacket_<V> { using type = base::BiomeDefinitionListPacket; };

template <int V> requires (V >= 800 && V < 827)
struct BiomeDefinitionListPacket_<V> { using type = v800::BiomeDefinitionListPacket; };

template <int V> requires (V >= 827 && V < 844)
struct BiomeDefinitionListPacket_<V> { using type = v827::BiomeDefinitionListPacket; };

template <int V> requires (V >= 844 && V < 859)
struct BiomeDefinitionListPacket_<V> { using type = v844::BiomeDefinitionListPacket; };

template <int V> requires (V >= 859 && V < 924)
struct BiomeDefinitionListPacket_<V> { using type = v859::BiomeDefinitionListPacket; };

template <int V> requires (V >= 924 && V < 975)
struct BiomeDefinitionListPacket_<V> { using type = v924::BiomeDefinitionListPacket; };

template <int V> requires (V >= 975 && V < 1001)
struct BiomeDefinitionListPacket_<V> { using type = v975::BiomeDefinitionListPacket; };

template <int V> requires (V >= 1001)
struct BiomeDefinitionListPacket_<V> { using type = v1001::BiomeDefinitionListPacket; };

template <int V>
struct CompressedBiomeDefinitionListPacket_;

template <int V> requires (V < 800)
struct CompressedBiomeDefinitionListPacket_<V> { using type = base::CompressedBiomeDefinitionListPacket; };

}  // namespace detail

template <int V> using NoiseDescriptor_ = typename detail::NoiseDescriptor_<V>::type;
template <int V> using SerializedNoiseBlockSpecifier_ = typename detail::SerializedNoiseBlockSpecifier_<V>::type;
template <int V> using BiomeNoiseGradientSurfaceData_ = typename detail::BiomeNoiseGradientSurfaceData_<V>::type;
template <int V> using BiomeSurfaceBuilderData_ = typename detail::BiomeSurfaceBuilderData_<V>::type;
template <int V> using BiomeClimateData_ = typename detail::BiomeClimateData_<V>::type;
template <int V> using BiomeCoordinateData_ = typename detail::BiomeCoordinateData_<V>::type;
template <int V> using BiomeScatterParamData_ = typename detail::BiomeScatterParamData_<V>::type;
template <int V> using BiomeConsolidatedFeatureData_ = typename detail::BiomeConsolidatedFeatureData_<V>::type;
template <int V> using BiomeConsolidatedFeaturesData_ = typename detail::BiomeConsolidatedFeaturesData_<V>::type;
template <int V> using BiomeElementData_ = typename detail::BiomeElementData_<V>::type;
template <int V> using BiomeSurfaceMaterialAdjustmentData_ = typename detail::BiomeSurfaceMaterialAdjustmentData_<V>::type;
template <int V> using BiomeDefinitionChunkGenData_ = typename detail::BiomeDefinitionChunkGenData_<V>::type;
template <int V> using BiomeDefinitionData_ = typename detail::BiomeDefinitionData_<V>::type;
template <int V> using BiomeDefinitionListPacket_ = typename detail::BiomeDefinitionListPacket_<V>::type;
template <int V> using CompressedBiomeDefinitionListPacket_ = typename detail::CompressedBiomeDefinitionListPacket_<V>::type;

template <int V>
struct packet_of<V, 122> { using type = BiomeDefinitionListPacket_<V>; };

template <int V> requires (V < 800)
struct packet_of<V, 301> { using type = CompressedBiomeDefinitionListPacket_<V>; };

namespace detail {

template <>
inline constexpr std::array<VillageType, 5> values_v<VillageType>{{
    VillageType::Desert,
    VillageType::Ice,
    VillageType::Savanna,
    VillageType::Taiga,
    VillageType::Default,
}};

template <>
inline constexpr std::array<std::string_view, 5> names_v<VillageType>{{
    "desert",
    "ice",
    "savanna",
    "taiga",
    "default",
}};

template <>
inline constexpr std::string_view type_name_v<VillageType>{"VillageType"};

template <>
inline constexpr std::array<BiomeTemperatureCategory, 6> values_v<BiomeTemperatureCategory>{{
    BiomeTemperatureCategory::Medium,
    BiomeTemperatureCategory::Warm,
    BiomeTemperatureCategory::Lukewarm,
    BiomeTemperatureCategory::Cold,
    BiomeTemperatureCategory::Frozen,
    BiomeTemperatureCategory::Count,
}};

template <>
inline constexpr std::array<std::string_view, 6> names_v<BiomeTemperatureCategory>{{
    "medium",
    "warm",
    "lukewarm",
    "cold",
    "frozen",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<BiomeTemperatureCategory>{"BiomeTemperatureCategory"};

template <>
inline constexpr std::array<CoordinateEvaluationOrder, 6> values_v<CoordinateEvaluationOrder>{{
    CoordinateEvaluationOrder::XYZ,
    CoordinateEvaluationOrder::XZY,
    CoordinateEvaluationOrder::YXZ,
    CoordinateEvaluationOrder::YZX,
    CoordinateEvaluationOrder::ZXY,
    CoordinateEvaluationOrder::ZYX,
}};

template <>
inline constexpr std::array<std::string_view, 6> names_v<CoordinateEvaluationOrder>{{
    "xyz",
    "xzy",
    "yxz",
    "yzx",
    "zxy",
    "zyx",
}};

template <>
inline constexpr std::string_view type_name_v<CoordinateEvaluationOrder>{"CoordinateEvaluationOrder"};

template <>
inline constexpr std::array<RandomDistributionType, 7> values_v<RandomDistributionType>{{
    RandomDistributionType::SingleValued,
    RandomDistributionType::Uniform,
    RandomDistributionType::Gaussian,
    RandomDistributionType::InverseGaussian,
    RandomDistributionType::FixedGrid,
    RandomDistributionType::JitteredGrid,
    RandomDistributionType::Triangle,
}};

template <>
inline constexpr std::array<std::string_view, 7> names_v<RandomDistributionType>{{
    "singlevalued",
    "uniform",
    "gaussian",
    "inversegaussian",
    "fixedgrid",
    "jitteredgrid",
    "triangle",
}};

template <>
inline constexpr std::string_view type_name_v<RandomDistributionType>{"RandomDistributionType"};

}  // namespace detail

namespace detail {

template <>
inline constexpr bool is_reflected_struct_v<FloatRange> = true;

template <>
inline constexpr std::string_view struct_name_v<FloatRange>{"FloatRange"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<FloatRange>{{
    "min",
    "max",
}};

template <>
struct field_accessor<FloatRange> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.min;
        }
        else {
            return value.max;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::NoiseDescriptor> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::NoiseDescriptor>{"NoiseDescriptor"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v1001::NoiseDescriptor>{{
    "name",
    "first_octave",
    "amplitudes",
}};

template <>
struct field_accessor<v1001::NoiseDescriptor> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.name;
        }
        else if constexpr (I == 1) {
            return value.first_octave;
        }
        else {
            return value.amplitudes;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::SerializedNoiseBlockSpecifier> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::SerializedNoiseBlockSpecifier>{"SerializedNoiseBlockSpecifier"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v1001::SerializedNoiseBlockSpecifier>{{
    "noise",
    "threshold",
    "range",
    "block_runtime_id",
}};

template <>
struct field_accessor<v1001::SerializedNoiseBlockSpecifier> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.noise;
        }
        else if constexpr (I == 1) {
            return value.threshold;
        }
        else if constexpr (I == 2) {
            return value.range;
        }
        else {
            return value.block_runtime_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::BiomeNoiseGradientSurfaceData> = true;

template <>
inline constexpr std::string_view struct_name_v<base::BiomeNoiseGradientSurfaceData>{"BiomeNoiseGradientSurfaceData"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<base::BiomeNoiseGradientSurfaceData>{{
    "non_replaceable_blocks",
    "gradient_blocks",
    "noise_seed_string",
    "first_octave",
    "amplitudes",
}};

template <>
struct field_accessor<base::BiomeNoiseGradientSurfaceData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.non_replaceable_blocks;
        }
        else if constexpr (I == 1) {
            return value.gradient_blocks;
        }
        else if constexpr (I == 2) {
            return value.noise_seed_string;
        }
        else if constexpr (I == 3) {
            return value.first_octave;
        }
        else {
            return value.amplitudes;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::BiomeNoiseGradientSurfaceData> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::BiomeNoiseGradientSurfaceData>{"BiomeNoiseGradientSurfaceData"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v1001::BiomeNoiseGradientSurfaceData>{{
    "non_replaceable_blocks",
    "gradient_block_ranges",
    "noise_descriptor",
}};

template <>
struct field_accessor<v1001::BiomeNoiseGradientSurfaceData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.non_replaceable_blocks;
        }
        else if constexpr (I == 1) {
            return value.gradient_block_ranges;
        }
        else {
            return value.noise_descriptor;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<BiomeSurfaceMaterialData> = true;

template <>
inline constexpr std::string_view struct_name_v<BiomeSurfaceMaterialData>{"BiomeSurfaceMaterialData"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<BiomeSurfaceMaterialData>{{
    "top_block",
    "mid_block",
    "sea_floor_block",
    "foundation_block",
    "sea_block",
    "sea_floor_depth",
}};

template <>
struct field_accessor<BiomeSurfaceMaterialData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.top_block;
        }
        else if constexpr (I == 1) {
            return value.mid_block;
        }
        else if constexpr (I == 2) {
            return value.sea_floor_block;
        }
        else if constexpr (I == 3) {
            return value.foundation_block;
        }
        else if constexpr (I == 4) {
            return value.sea_block;
        }
        else {
            return value.sea_floor_depth;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<BiomeMesaSurfaceData> = true;

template <>
inline constexpr std::string_view struct_name_v<BiomeMesaSurfaceData>{"BiomeMesaSurfaceData"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<BiomeMesaSurfaceData>{{
    "clay_material",
    "hard_clay_material",
    "bryce_pillars",
    "has_forest",
}};

template <>
struct field_accessor<BiomeMesaSurfaceData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.clay_material;
        }
        else if constexpr (I == 1) {
            return value.hard_clay_material;
        }
        else if constexpr (I == 2) {
            return value.bryce_pillars;
        }
        else {
            return value.has_forest;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<BiomeCappedSurfaceData> = true;

template <>
inline constexpr std::string_view struct_name_v<BiomeCappedSurfaceData>{"BiomeCappedSurfaceData"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<BiomeCappedSurfaceData>{{
    "floor_blocks",
    "ceiling_blocks",
    "sea_block",
    "foundation_block",
    "beach_block",
}};

template <>
struct field_accessor<BiomeCappedSurfaceData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.floor_blocks;
        }
        else if constexpr (I == 1) {
            return value.ceiling_blocks;
        }
        else if constexpr (I == 2) {
            return value.sea_block;
        }
        else if constexpr (I == 3) {
            return value.foundation_block;
        }
        else {
            return value.beach_block;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::BiomeSurfaceBuilderData> = true;

template <>
inline constexpr std::string_view struct_name_v<base::BiomeSurfaceBuilderData>{"BiomeSurfaceBuilderData"};

template <>
inline constexpr std::array<std::string_view, 8> field_names_v<base::BiomeSurfaceBuilderData>{{
    "surface_materials",
    "has_default_overworld_surface",
    "has_swamp_surface",
    "has_frozen_ocean_surface",
    "has_the_end_surface",
    "mesa_surface",
    "capped_surface",
    "noise_gradient_surface",
}};

template <>
struct field_accessor<base::BiomeSurfaceBuilderData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.surface_materials;
        }
        else if constexpr (I == 1) {
            return value.has_default_overworld_surface;
        }
        else if constexpr (I == 2) {
            return value.has_swamp_surface;
        }
        else if constexpr (I == 3) {
            return value.has_frozen_ocean_surface;
        }
        else if constexpr (I == 4) {
            return value.has_the_end_surface;
        }
        else if constexpr (I == 5) {
            return value.mesa_surface;
        }
        else if constexpr (I == 6) {
            return value.capped_surface;
        }
        else {
            return value.noise_gradient_surface;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::BiomeSurfaceBuilderData> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::BiomeSurfaceBuilderData>{"BiomeSurfaceBuilderData"};

template <>
inline constexpr std::array<std::string_view, 8> field_names_v<v1001::BiomeSurfaceBuilderData>{{
    "surface_materials",
    "has_default_overworld_surface",
    "has_swamp_surface",
    "has_frozen_ocean_surface",
    "has_the_end_surface",
    "mesa_surface",
    "capped_surface",
    "noise_gradient_surface",
}};

template <>
struct field_accessor<v1001::BiomeSurfaceBuilderData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.surface_materials;
        }
        else if constexpr (I == 1) {
            return value.has_default_overworld_surface;
        }
        else if constexpr (I == 2) {
            return value.has_swamp_surface;
        }
        else if constexpr (I == 3) {
            return value.has_frozen_ocean_surface;
        }
        else if constexpr (I == 4) {
            return value.has_the_end_surface;
        }
        else if constexpr (I == 5) {
            return value.mesa_surface;
        }
        else if constexpr (I == 6) {
            return value.capped_surface;
        }
        else {
            return value.noise_gradient_surface;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::BiomeClimateData> = true;

template <>
inline constexpr std::string_view struct_name_v<base::BiomeClimateData>{"BiomeClimateData"};

template <>
inline constexpr std::array<std::string_view, 8> field_names_v<base::BiomeClimateData>{{
    "temperature",
    "downfall",
    "red_spore_density",
    "blue_spore_density",
    "ash_density",
    "white_ash_density",
    "snow_accumulation_min",
    "snow_accumulation_max",
}};

template <>
struct field_accessor<base::BiomeClimateData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.temperature;
        }
        else if constexpr (I == 1) {
            return value.downfall;
        }
        else if constexpr (I == 2) {
            return value.red_spore_density;
        }
        else if constexpr (I == 3) {
            return value.blue_spore_density;
        }
        else if constexpr (I == 4) {
            return value.ash_density;
        }
        else if constexpr (I == 5) {
            return value.white_ash_density;
        }
        else if constexpr (I == 6) {
            return value.snow_accumulation_min;
        }
        else {
            return value.snow_accumulation_max;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v844::BiomeClimateData> = true;

template <>
inline constexpr std::string_view struct_name_v<v844::BiomeClimateData>{"BiomeClimateData"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v844::BiomeClimateData>{{
    "temperature",
    "downfall",
    "snow_accumulation_min",
    "snow_accumulation_max",
}};

template <>
struct field_accessor<v844::BiomeClimateData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.temperature;
        }
        else if constexpr (I == 1) {
            return value.downfall;
        }
        else if constexpr (I == 2) {
            return value.snow_accumulation_min;
        }
        else {
            return value.snow_accumulation_max;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::BiomeCoordinateData> = true;

template <>
inline constexpr std::string_view struct_name_v<base::BiomeCoordinateData>{"BiomeCoordinateData"};

template <>
inline constexpr std::array<std::string_view, 7> field_names_v<base::BiomeCoordinateData>{{
    "min_value_type",
    "min_value",
    "max_value_type",
    "max_value",
    "grid_offset",
    "grid_step_size",
    "distribution",
}};

template <>
struct field_accessor<base::BiomeCoordinateData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.min_value_type;
        }
        else if constexpr (I == 1) {
            return value.min_value;
        }
        else if constexpr (I == 2) {
            return value.max_value_type;
        }
        else if constexpr (I == 3) {
            return value.max_value;
        }
        else if constexpr (I == 4) {
            return value.grid_offset;
        }
        else if constexpr (I == 5) {
            return value.grid_step_size;
        }
        else {
            return value.distribution;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v800::BiomeCoordinateData> = true;

template <>
inline constexpr std::string_view struct_name_v<v800::BiomeCoordinateData>{"BiomeCoordinateData"};

template <>
inline constexpr std::array<std::string_view, 7> field_names_v<v800::BiomeCoordinateData>{{
    "min_value_type",
    "min_value",
    "max_value_type",
    "max_value",
    "grid_offset",
    "grid_step_size",
    "distribution",
}};

template <>
struct field_accessor<v800::BiomeCoordinateData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.min_value_type;
        }
        else if constexpr (I == 1) {
            return value.min_value;
        }
        else if constexpr (I == 2) {
            return value.max_value_type;
        }
        else if constexpr (I == 3) {
            return value.max_value;
        }
        else if constexpr (I == 4) {
            return value.grid_offset;
        }
        else if constexpr (I == 5) {
            return value.grid_step_size;
        }
        else {
            return value.distribution;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v859::BiomeCoordinateData> = true;

template <>
inline constexpr std::string_view struct_name_v<v859::BiomeCoordinateData>{"BiomeCoordinateData"};

template <>
inline constexpr std::array<std::string_view, 7> field_names_v<v859::BiomeCoordinateData>{{
    "min_value_type",
    "min_value",
    "max_value_type",
    "max_value",
    "grid_offset",
    "grid_step_size",
    "distribution",
}};

template <>
struct field_accessor<v859::BiomeCoordinateData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.min_value_type;
        }
        else if constexpr (I == 1) {
            return value.min_value;
        }
        else if constexpr (I == 2) {
            return value.max_value_type;
        }
        else if constexpr (I == 3) {
            return value.max_value;
        }
        else if constexpr (I == 4) {
            return value.grid_offset;
        }
        else if constexpr (I == 5) {
            return value.grid_step_size;
        }
        else {
            return value.distribution;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::BiomeScatterParamData> = true;

template <>
inline constexpr std::string_view struct_name_v<base::BiomeScatterParamData>{"BiomeScatterParamData"};

template <>
inline constexpr std::array<std::string_view, 8> field_names_v<base::BiomeScatterParamData>{{
    "coordinates",
    "eval_order",
    "chance_percent_type",
    "chance_percent",
    "chance_numerator",
    "chance_denominator",
    "iterations_type",
    "iterations",
}};

template <>
struct field_accessor<base::BiomeScatterParamData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.coordinates;
        }
        else if constexpr (I == 1) {
            return value.eval_order;
        }
        else if constexpr (I == 2) {
            return value.chance_percent_type;
        }
        else if constexpr (I == 3) {
            return value.chance_percent;
        }
        else if constexpr (I == 4) {
            return value.chance_numerator;
        }
        else if constexpr (I == 5) {
            return value.chance_denominator;
        }
        else if constexpr (I == 6) {
            return value.iterations_type;
        }
        else {
            return value.iterations;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v800::BiomeScatterParamData> = true;

template <>
inline constexpr std::string_view struct_name_v<v800::BiomeScatterParamData>{"BiomeScatterParamData"};

template <>
inline constexpr std::array<std::string_view, 8> field_names_v<v800::BiomeScatterParamData>{{
    "coordinates",
    "eval_order",
    "chance_percent_type",
    "chance_percent",
    "chance_numerator",
    "chance_denominator",
    "iterations_type",
    "iterations",
}};

template <>
struct field_accessor<v800::BiomeScatterParamData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.coordinates;
        }
        else if constexpr (I == 1) {
            return value.eval_order;
        }
        else if constexpr (I == 2) {
            return value.chance_percent_type;
        }
        else if constexpr (I == 3) {
            return value.chance_percent;
        }
        else if constexpr (I == 4) {
            return value.chance_numerator;
        }
        else if constexpr (I == 5) {
            return value.chance_denominator;
        }
        else if constexpr (I == 6) {
            return value.iterations_type;
        }
        else {
            return value.iterations;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v859::BiomeScatterParamData> = true;

template <>
inline constexpr std::string_view struct_name_v<v859::BiomeScatterParamData>{"BiomeScatterParamData"};

template <>
inline constexpr std::array<std::string_view, 8> field_names_v<v859::BiomeScatterParamData>{{
    "coordinates",
    "eval_order",
    "chance_percent_type",
    "chance_percent",
    "chance_numerator",
    "chance_denominator",
    "iterations_type",
    "iterations",
}};

template <>
struct field_accessor<v859::BiomeScatterParamData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.coordinates;
        }
        else if constexpr (I == 1) {
            return value.eval_order;
        }
        else if constexpr (I == 2) {
            return value.chance_percent_type;
        }
        else if constexpr (I == 3) {
            return value.chance_percent;
        }
        else if constexpr (I == 4) {
            return value.chance_numerator;
        }
        else if constexpr (I == 5) {
            return value.chance_denominator;
        }
        else if constexpr (I == 6) {
            return value.iterations_type;
        }
        else {
            return value.iterations;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::BiomeConsolidatedFeatureData> = true;

template <>
inline constexpr std::string_view struct_name_v<base::BiomeConsolidatedFeatureData>{"BiomeConsolidatedFeatureData"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<base::BiomeConsolidatedFeatureData>{{
    "scatter",
    "feature",
    "identifier",
    "pass",
    "can_use_internal_feature",
}};

template <>
struct field_accessor<base::BiomeConsolidatedFeatureData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.scatter;
        }
        else if constexpr (I == 1) {
            return value.feature;
        }
        else if constexpr (I == 2) {
            return value.identifier;
        }
        else if constexpr (I == 3) {
            return value.pass;
        }
        else {
            return value.can_use_internal_feature;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v800::BiomeConsolidatedFeatureData> = true;

template <>
inline constexpr std::string_view struct_name_v<v800::BiomeConsolidatedFeatureData>{"BiomeConsolidatedFeatureData"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v800::BiomeConsolidatedFeatureData>{{
    "scatter",
    "feature",
    "identifier",
    "pass",
    "can_use_internal_feature",
}};

template <>
struct field_accessor<v800::BiomeConsolidatedFeatureData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.scatter;
        }
        else if constexpr (I == 1) {
            return value.feature;
        }
        else if constexpr (I == 2) {
            return value.identifier;
        }
        else if constexpr (I == 3) {
            return value.pass;
        }
        else {
            return value.can_use_internal_feature;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v859::BiomeConsolidatedFeatureData> = true;

template <>
inline constexpr std::string_view struct_name_v<v859::BiomeConsolidatedFeatureData>{"BiomeConsolidatedFeatureData"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v859::BiomeConsolidatedFeatureData>{{
    "scatter",
    "feature",
    "identifier",
    "pass",
    "can_use_internal_feature",
}};

template <>
struct field_accessor<v859::BiomeConsolidatedFeatureData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.scatter;
        }
        else if constexpr (I == 1) {
            return value.feature;
        }
        else if constexpr (I == 2) {
            return value.identifier;
        }
        else if constexpr (I == 3) {
            return value.pass;
        }
        else {
            return value.can_use_internal_feature;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::BiomeConsolidatedFeaturesData> = true;

template <>
inline constexpr std::string_view struct_name_v<base::BiomeConsolidatedFeaturesData>{"BiomeConsolidatedFeaturesData"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::BiomeConsolidatedFeaturesData>{{
    "features",
}};

template <>
struct field_accessor<base::BiomeConsolidatedFeaturesData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.features;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v800::BiomeConsolidatedFeaturesData> = true;

template <>
inline constexpr std::string_view struct_name_v<v800::BiomeConsolidatedFeaturesData>{"BiomeConsolidatedFeaturesData"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v800::BiomeConsolidatedFeaturesData>{{
    "features",
}};

template <>
struct field_accessor<v800::BiomeConsolidatedFeaturesData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.features;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v859::BiomeConsolidatedFeaturesData> = true;

template <>
inline constexpr std::string_view struct_name_v<v859::BiomeConsolidatedFeaturesData>{"BiomeConsolidatedFeaturesData"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v859::BiomeConsolidatedFeaturesData>{{
    "features",
}};

template <>
struct field_accessor<v859::BiomeConsolidatedFeaturesData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.features;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<BiomeMountainParamsData> = true;

template <>
inline constexpr std::string_view struct_name_v<BiomeMountainParamsData>{"BiomeMountainParamsData"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<BiomeMountainParamsData>{{
    "steep_block",
    "north_slopes",
    "south_slopes",
    "west_slopes",
    "east_slopes",
    "top_slide_enabled",
}};

template <>
struct field_accessor<BiomeMountainParamsData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.steep_block;
        }
        else if constexpr (I == 1) {
            return value.north_slopes;
        }
        else if constexpr (I == 2) {
            return value.south_slopes;
        }
        else if constexpr (I == 3) {
            return value.west_slopes;
        }
        else if constexpr (I == 4) {
            return value.east_slopes;
        }
        else {
            return value.top_slide_enabled;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::BiomeElementData> = true;

template <>
inline constexpr std::string_view struct_name_v<base::BiomeElementData>{"BiomeElementData"};

template <>
inline constexpr std::array<std::string_view, 8> field_names_v<base::BiomeElementData>{{
    "noise_freq_scale",
    "noise_lower_bound",
    "noise_upper_bound",
    "height_min_type",
    "height_min",
    "height_max_type",
    "height_max",
    "adjusted_materials",
}};

template <>
struct field_accessor<base::BiomeElementData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.noise_freq_scale;
        }
        else if constexpr (I == 1) {
            return value.noise_lower_bound;
        }
        else if constexpr (I == 2) {
            return value.noise_upper_bound;
        }
        else if constexpr (I == 3) {
            return value.height_min_type;
        }
        else if constexpr (I == 4) {
            return value.height_min;
        }
        else if constexpr (I == 5) {
            return value.height_max_type;
        }
        else if constexpr (I == 6) {
            return value.height_max;
        }
        else {
            return value.adjusted_materials;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v800::BiomeElementData> = true;

template <>
inline constexpr std::string_view struct_name_v<v800::BiomeElementData>{"BiomeElementData"};

template <>
inline constexpr std::array<std::string_view, 8> field_names_v<v800::BiomeElementData>{{
    "noise_freq_scale",
    "noise_lower_bound",
    "noise_upper_bound",
    "height_min_type",
    "height_min",
    "height_max_type",
    "height_max",
    "adjusted_materials",
}};

template <>
struct field_accessor<v800::BiomeElementData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.noise_freq_scale;
        }
        else if constexpr (I == 1) {
            return value.noise_lower_bound;
        }
        else if constexpr (I == 2) {
            return value.noise_upper_bound;
        }
        else if constexpr (I == 3) {
            return value.height_min_type;
        }
        else if constexpr (I == 4) {
            return value.height_min;
        }
        else if constexpr (I == 5) {
            return value.height_max_type;
        }
        else if constexpr (I == 6) {
            return value.height_max;
        }
        else {
            return value.adjusted_materials;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v859::BiomeElementData> = true;

template <>
inline constexpr std::string_view struct_name_v<v859::BiomeElementData>{"BiomeElementData"};

template <>
inline constexpr std::array<std::string_view, 8> field_names_v<v859::BiomeElementData>{{
    "noise_freq_scale",
    "noise_lower_bound",
    "noise_upper_bound",
    "height_min_type",
    "height_min",
    "height_max_type",
    "height_max",
    "adjusted_materials",
}};

template <>
struct field_accessor<v859::BiomeElementData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.noise_freq_scale;
        }
        else if constexpr (I == 1) {
            return value.noise_lower_bound;
        }
        else if constexpr (I == 2) {
            return value.noise_upper_bound;
        }
        else if constexpr (I == 3) {
            return value.height_min_type;
        }
        else if constexpr (I == 4) {
            return value.height_min;
        }
        else if constexpr (I == 5) {
            return value.height_max_type;
        }
        else if constexpr (I == 6) {
            return value.height_max;
        }
        else {
            return value.adjusted_materials;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::BiomeSurfaceMaterialAdjustmentData> = true;

template <>
inline constexpr std::string_view struct_name_v<base::BiomeSurfaceMaterialAdjustmentData>{"BiomeSurfaceMaterialAdjustmentData"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::BiomeSurfaceMaterialAdjustmentData>{{
    "adjustments",
}};

template <>
struct field_accessor<base::BiomeSurfaceMaterialAdjustmentData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.adjustments;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v800::BiomeSurfaceMaterialAdjustmentData> = true;

template <>
inline constexpr std::string_view struct_name_v<v800::BiomeSurfaceMaterialAdjustmentData>{"BiomeSurfaceMaterialAdjustmentData"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v800::BiomeSurfaceMaterialAdjustmentData>{{
    "adjustments",
}};

template <>
struct field_accessor<v800::BiomeSurfaceMaterialAdjustmentData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.adjustments;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v859::BiomeSurfaceMaterialAdjustmentData> = true;

template <>
inline constexpr std::string_view struct_name_v<v859::BiomeSurfaceMaterialAdjustmentData>{"BiomeSurfaceMaterialAdjustmentData"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v859::BiomeSurfaceMaterialAdjustmentData>{{
    "adjustments",
}};

template <>
struct field_accessor<v859::BiomeSurfaceMaterialAdjustmentData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.adjustments;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<BiomeWeightedData> = true;

template <>
inline constexpr std::string_view struct_name_v<BiomeWeightedData>{"BiomeWeightedData"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<BiomeWeightedData>{{
    "biome_identifier",
    "weight",
}};

template <>
struct field_accessor<BiomeWeightedData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.biome_identifier;
        }
        else {
            return value.weight;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<BiomeConditionalTransformationData> = true;

template <>
inline constexpr std::string_view struct_name_v<BiomeConditionalTransformationData>{"BiomeConditionalTransformationData"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<BiomeConditionalTransformationData>{{
    "transforms_into",
    "condition_json",
    "min_passing_neighbors",
}};

template <>
struct field_accessor<BiomeConditionalTransformationData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.transforms_into;
        }
        else if constexpr (I == 1) {
            return value.condition_json;
        }
        else {
            return value.min_passing_neighbors;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<BiomeWeightedTemperatureData> = true;

template <>
inline constexpr std::string_view struct_name_v<BiomeWeightedTemperatureData>{"BiomeWeightedTemperatureData"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<BiomeWeightedTemperatureData>{{
    "temperature",
    "weight",
}};

template <>
struct field_accessor<BiomeWeightedTemperatureData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.temperature;
        }
        else {
            return value.weight;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<BiomeOverworldGenRulesData> = true;

template <>
inline constexpr std::string_view struct_name_v<BiomeOverworldGenRulesData>{"BiomeOverworldGenRulesData"};

template <>
inline constexpr std::array<std::string_view, 7> field_names_v<BiomeOverworldGenRulesData>{{
    "hills_transformations",
    "mutate_transformations",
    "river_transformations",
    "shore_transformations",
    "pre_hills_edge",
    "post_shore_edge",
    "climate",
}};

template <>
struct field_accessor<BiomeOverworldGenRulesData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.hills_transformations;
        }
        else if constexpr (I == 1) {
            return value.mutate_transformations;
        }
        else if constexpr (I == 2) {
            return value.river_transformations;
        }
        else if constexpr (I == 3) {
            return value.shore_transformations;
        }
        else if constexpr (I == 4) {
            return value.pre_hills_edge;
        }
        else if constexpr (I == 5) {
            return value.post_shore_edge;
        }
        else {
            return value.climate;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<BiomeMultinoiseGenRulesData> = true;

template <>
inline constexpr std::string_view struct_name_v<BiomeMultinoiseGenRulesData>{"BiomeMultinoiseGenRulesData"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<BiomeMultinoiseGenRulesData>{{
    "temperature",
    "humidity",
    "altitude",
    "weirdness",
    "weight",
}};

template <>
struct field_accessor<BiomeMultinoiseGenRulesData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.temperature;
        }
        else if constexpr (I == 1) {
            return value.humidity;
        }
        else if constexpr (I == 2) {
            return value.altitude;
        }
        else if constexpr (I == 3) {
            return value.weirdness;
        }
        else {
            return value.weight;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<BiomeLegacyWorldGenRulesData> = true;

template <>
inline constexpr std::string_view struct_name_v<BiomeLegacyWorldGenRulesData>{"BiomeLegacyWorldGenRulesData"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<BiomeLegacyWorldGenRulesData>{{
    "legacy_pre_hills_edge",
}};

template <>
struct field_accessor<BiomeLegacyWorldGenRulesData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.legacy_pre_hills_edge;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<BiomeReplacementData> = true;

template <>
inline constexpr std::string_view struct_name_v<BiomeReplacementData>{"BiomeReplacementData"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<BiomeReplacementData>{{
    "replacement_biome",
    "dimension",
    "target_biomes",
    "amount",
    "noise_frequency_scale",
    "replacement_index",
}};

template <>
struct field_accessor<BiomeReplacementData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.replacement_biome;
        }
        else if constexpr (I == 1) {
            return value.dimension;
        }
        else if constexpr (I == 2) {
            return value.target_biomes;
        }
        else if constexpr (I == 3) {
            return value.amount;
        }
        else if constexpr (I == 4) {
            return value.noise_frequency_scale;
        }
        else {
            return value.replacement_index;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<BiomeReplacementsData> = true;

template <>
inline constexpr std::string_view struct_name_v<BiomeReplacementsData>{"BiomeReplacementsData"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<BiomeReplacementsData>{{
    "biome_replacements",
}};

template <>
struct field_accessor<BiomeReplacementsData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.biome_replacements;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<BiomeTagsData> = true;

template <>
inline constexpr std::string_view struct_name_v<BiomeTagsData>{"BiomeTagsData"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<BiomeTagsData>{{
    "tags",
}};

template <>
struct field_accessor<BiomeTagsData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.tags;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::BiomeDefinitionChunkGenData> = true;

template <>
inline constexpr std::string_view struct_name_v<base::BiomeDefinitionChunkGenData>{"BiomeDefinitionChunkGenData"};

template <>
inline constexpr std::array<std::string_view, 13> field_names_v<base::BiomeDefinitionChunkGenData>{{
    "climate",
    "consolidated_features",
    "mountain_params",
    "surface_material_adjustments",
    "surface_materials",
    "has_swamp_surface",
    "has_frozen_ocean_surface",
    "has_the_end_surface",
    "mesa_surface",
    "capped_surface",
    "overworld_gen_rules",
    "multinoise_gen_rules",
    "legacy_world_gen_rules",
}};

template <>
struct field_accessor<base::BiomeDefinitionChunkGenData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.climate;
        }
        else if constexpr (I == 1) {
            return value.consolidated_features;
        }
        else if constexpr (I == 2) {
            return value.mountain_params;
        }
        else if constexpr (I == 3) {
            return value.surface_material_adjustments;
        }
        else if constexpr (I == 4) {
            return value.surface_materials;
        }
        else if constexpr (I == 5) {
            return value.has_swamp_surface;
        }
        else if constexpr (I == 6) {
            return value.has_frozen_ocean_surface;
        }
        else if constexpr (I == 7) {
            return value.has_the_end_surface;
        }
        else if constexpr (I == 8) {
            return value.mesa_surface;
        }
        else if constexpr (I == 9) {
            return value.capped_surface;
        }
        else if constexpr (I == 10) {
            return value.overworld_gen_rules;
        }
        else if constexpr (I == 11) {
            return value.multinoise_gen_rules;
        }
        else {
            return value.legacy_world_gen_rules;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v800::BiomeDefinitionChunkGenData> = true;

template <>
inline constexpr std::string_view struct_name_v<v800::BiomeDefinitionChunkGenData>{"BiomeDefinitionChunkGenData"};

template <>
inline constexpr std::array<std::string_view, 14> field_names_v<v800::BiomeDefinitionChunkGenData>{{
    "climate",
    "consolidated_features",
    "mountain_params",
    "surface_material_adjustments",
    "surface_materials",
    "has_swamp_surface",
    "has_frozen_ocean_surface",
    "has_the_end_surface",
    "mesa_surface",
    "capped_surface",
    "overworld_gen_rules",
    "multinoise_gen_rules",
    "legacy_world_gen_rules",
    "replace_biomes",
}};

template <>
struct field_accessor<v800::BiomeDefinitionChunkGenData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.climate;
        }
        else if constexpr (I == 1) {
            return value.consolidated_features;
        }
        else if constexpr (I == 2) {
            return value.mountain_params;
        }
        else if constexpr (I == 3) {
            return value.surface_material_adjustments;
        }
        else if constexpr (I == 4) {
            return value.surface_materials;
        }
        else if constexpr (I == 5) {
            return value.has_swamp_surface;
        }
        else if constexpr (I == 6) {
            return value.has_frozen_ocean_surface;
        }
        else if constexpr (I == 7) {
            return value.has_the_end_surface;
        }
        else if constexpr (I == 8) {
            return value.mesa_surface;
        }
        else if constexpr (I == 9) {
            return value.capped_surface;
        }
        else if constexpr (I == 10) {
            return value.overworld_gen_rules;
        }
        else if constexpr (I == 11) {
            return value.multinoise_gen_rules;
        }
        else if constexpr (I == 12) {
            return value.legacy_world_gen_rules;
        }
        else {
            return value.replace_biomes;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v844::BiomeDefinitionChunkGenData> = true;

template <>
inline constexpr std::string_view struct_name_v<v844::BiomeDefinitionChunkGenData>{"BiomeDefinitionChunkGenData"};

template <>
inline constexpr std::array<std::string_view, 15> field_names_v<v844::BiomeDefinitionChunkGenData>{{
    "climate",
    "consolidated_features",
    "mountain_params",
    "surface_material_adjustments",
    "surface_materials",
    "has_default_overworld_surface",
    "has_swamp_surface",
    "has_frozen_ocean_surface",
    "has_the_end_surface",
    "mesa_surface",
    "capped_surface",
    "overworld_gen_rules",
    "multinoise_gen_rules",
    "legacy_world_gen_rules",
    "replace_biomes",
}};

template <>
struct field_accessor<v844::BiomeDefinitionChunkGenData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.climate;
        }
        else if constexpr (I == 1) {
            return value.consolidated_features;
        }
        else if constexpr (I == 2) {
            return value.mountain_params;
        }
        else if constexpr (I == 3) {
            return value.surface_material_adjustments;
        }
        else if constexpr (I == 4) {
            return value.surface_materials;
        }
        else if constexpr (I == 5) {
            return value.has_default_overworld_surface;
        }
        else if constexpr (I == 6) {
            return value.has_swamp_surface;
        }
        else if constexpr (I == 7) {
            return value.has_frozen_ocean_surface;
        }
        else if constexpr (I == 8) {
            return value.has_the_end_surface;
        }
        else if constexpr (I == 9) {
            return value.mesa_surface;
        }
        else if constexpr (I == 10) {
            return value.capped_surface;
        }
        else if constexpr (I == 11) {
            return value.overworld_gen_rules;
        }
        else if constexpr (I == 12) {
            return value.multinoise_gen_rules;
        }
        else if constexpr (I == 13) {
            return value.legacy_world_gen_rules;
        }
        else {
            return value.replace_biomes;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v859::BiomeDefinitionChunkGenData> = true;

template <>
inline constexpr std::string_view struct_name_v<v859::BiomeDefinitionChunkGenData>{"BiomeDefinitionChunkGenData"};

template <>
inline constexpr std::array<std::string_view, 15> field_names_v<v859::BiomeDefinitionChunkGenData>{{
    "climate",
    "consolidated_features",
    "mountain_params",
    "surface_material_adjustments",
    "surface_materials",
    "has_default_overworld_surface",
    "has_swamp_surface",
    "has_frozen_ocean_surface",
    "has_the_end_surface",
    "mesa_surface",
    "capped_surface",
    "overworld_gen_rules",
    "multinoise_gen_rules",
    "legacy_world_gen_rules",
    "replace_biomes",
}};

template <>
struct field_accessor<v859::BiomeDefinitionChunkGenData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.climate;
        }
        else if constexpr (I == 1) {
            return value.consolidated_features;
        }
        else if constexpr (I == 2) {
            return value.mountain_params;
        }
        else if constexpr (I == 3) {
            return value.surface_material_adjustments;
        }
        else if constexpr (I == 4) {
            return value.surface_materials;
        }
        else if constexpr (I == 5) {
            return value.has_default_overworld_surface;
        }
        else if constexpr (I == 6) {
            return value.has_swamp_surface;
        }
        else if constexpr (I == 7) {
            return value.has_frozen_ocean_surface;
        }
        else if constexpr (I == 8) {
            return value.has_the_end_surface;
        }
        else if constexpr (I == 9) {
            return value.mesa_surface;
        }
        else if constexpr (I == 10) {
            return value.capped_surface;
        }
        else if constexpr (I == 11) {
            return value.overworld_gen_rules;
        }
        else if constexpr (I == 12) {
            return value.multinoise_gen_rules;
        }
        else if constexpr (I == 13) {
            return value.legacy_world_gen_rules;
        }
        else {
            return value.replace_biomes;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::BiomeDefinitionChunkGenData> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::BiomeDefinitionChunkGenData>{"BiomeDefinitionChunkGenData"};

template <>
inline constexpr std::array<std::string_view, 16> field_names_v<v924::BiomeDefinitionChunkGenData>{{
    "climate",
    "consolidated_features",
    "mountain_params",
    "surface_material_adjustments",
    "surface_materials",
    "has_default_overworld_surface",
    "has_swamp_surface",
    "has_frozen_ocean_surface",
    "has_the_end_surface",
    "mesa_surface",
    "capped_surface",
    "overworld_gen_rules",
    "multinoise_gen_rules",
    "legacy_world_gen_rules",
    "replace_biomes",
    "village_type",
}};

template <>
struct field_accessor<v924::BiomeDefinitionChunkGenData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.climate;
        }
        else if constexpr (I == 1) {
            return value.consolidated_features;
        }
        else if constexpr (I == 2) {
            return value.mountain_params;
        }
        else if constexpr (I == 3) {
            return value.surface_material_adjustments;
        }
        else if constexpr (I == 4) {
            return value.surface_materials;
        }
        else if constexpr (I == 5) {
            return value.has_default_overworld_surface;
        }
        else if constexpr (I == 6) {
            return value.has_swamp_surface;
        }
        else if constexpr (I == 7) {
            return value.has_frozen_ocean_surface;
        }
        else if constexpr (I == 8) {
            return value.has_the_end_surface;
        }
        else if constexpr (I == 9) {
            return value.mesa_surface;
        }
        else if constexpr (I == 10) {
            return value.capped_surface;
        }
        else if constexpr (I == 11) {
            return value.overworld_gen_rules;
        }
        else if constexpr (I == 12) {
            return value.multinoise_gen_rules;
        }
        else if constexpr (I == 13) {
            return value.legacy_world_gen_rules;
        }
        else if constexpr (I == 14) {
            return value.replace_biomes;
        }
        else {
            return value.village_type;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v975::BiomeDefinitionChunkGenData> = true;

template <>
inline constexpr std::string_view struct_name_v<v975::BiomeDefinitionChunkGenData>{"BiomeDefinitionChunkGenData"};

template <>
inline constexpr std::array<std::string_view, 11> field_names_v<v975::BiomeDefinitionChunkGenData>{{
    "climate",
    "consolidated_features",
    "mountain_params",
    "surface_material_adjustments",
    "overworld_gen_rules",
    "multinoise_gen_rules",
    "legacy_world_gen_rules",
    "replace_biomes",
    "village_type",
    "surface_builder_data",
    "subsurface_builder_data",
}};

template <>
struct field_accessor<v975::BiomeDefinitionChunkGenData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.climate;
        }
        else if constexpr (I == 1) {
            return value.consolidated_features;
        }
        else if constexpr (I == 2) {
            return value.mountain_params;
        }
        else if constexpr (I == 3) {
            return value.surface_material_adjustments;
        }
        else if constexpr (I == 4) {
            return value.overworld_gen_rules;
        }
        else if constexpr (I == 5) {
            return value.multinoise_gen_rules;
        }
        else if constexpr (I == 6) {
            return value.legacy_world_gen_rules;
        }
        else if constexpr (I == 7) {
            return value.replace_biomes;
        }
        else if constexpr (I == 8) {
            return value.village_type;
        }
        else if constexpr (I == 9) {
            return value.surface_builder_data;
        }
        else {
            return value.subsurface_builder_data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::BiomeDefinitionChunkGenData> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::BiomeDefinitionChunkGenData>{"BiomeDefinitionChunkGenData"};

template <>
inline constexpr std::array<std::string_view, 11> field_names_v<v1001::BiomeDefinitionChunkGenData>{{
    "climate",
    "consolidated_features",
    "mountain_params",
    "surface_material_adjustments",
    "overworld_gen_rules",
    "multinoise_gen_rules",
    "legacy_world_gen_rules",
    "replace_biomes",
    "village_type",
    "surface_builder_data",
    "subsurface_builder_data",
}};

template <>
struct field_accessor<v1001::BiomeDefinitionChunkGenData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.climate;
        }
        else if constexpr (I == 1) {
            return value.consolidated_features;
        }
        else if constexpr (I == 2) {
            return value.mountain_params;
        }
        else if constexpr (I == 3) {
            return value.surface_material_adjustments;
        }
        else if constexpr (I == 4) {
            return value.overworld_gen_rules;
        }
        else if constexpr (I == 5) {
            return value.multinoise_gen_rules;
        }
        else if constexpr (I == 6) {
            return value.legacy_world_gen_rules;
        }
        else if constexpr (I == 7) {
            return value.replace_biomes;
        }
        else if constexpr (I == 8) {
            return value.village_type;
        }
        else if constexpr (I == 9) {
            return value.surface_builder_data;
        }
        else {
            return value.subsurface_builder_data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::BiomeDefinitionData> = true;

template <>
inline constexpr std::string_view struct_name_v<base::BiomeDefinitionData>{"BiomeDefinitionData"};

template <>
inline constexpr std::array<std::string_view, 13> field_names_v<base::BiomeDefinitionData>{{
    "id",
    "temperature",
    "downfall",
    "red_spore_density",
    "blue_spore_density",
    "ash_density",
    "white_ash_density",
    "depth",
    "scale",
    "map_water_color_argb",
    "rain",
    "tags",
    "chunk_gen_data",
}};

template <>
struct field_accessor<base::BiomeDefinitionData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.id;
        }
        else if constexpr (I == 1) {
            return value.temperature;
        }
        else if constexpr (I == 2) {
            return value.downfall;
        }
        else if constexpr (I == 3) {
            return value.red_spore_density;
        }
        else if constexpr (I == 4) {
            return value.blue_spore_density;
        }
        else if constexpr (I == 5) {
            return value.ash_density;
        }
        else if constexpr (I == 6) {
            return value.white_ash_density;
        }
        else if constexpr (I == 7) {
            return value.depth;
        }
        else if constexpr (I == 8) {
            return value.scale;
        }
        else if constexpr (I == 9) {
            return value.map_water_color_argb;
        }
        else if constexpr (I == 10) {
            return value.rain;
        }
        else if constexpr (I == 11) {
            return value.tags;
        }
        else {
            return value.chunk_gen_data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v800::BiomeDefinitionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v800::BiomeDefinitionData>{"BiomeDefinitionData"};

template <>
inline constexpr std::array<std::string_view, 13> field_names_v<v800::BiomeDefinitionData>{{
    "id",
    "temperature",
    "downfall",
    "red_spore_density",
    "blue_spore_density",
    "ash_density",
    "white_ash_density",
    "depth",
    "scale",
    "map_water_color_argb",
    "rain",
    "tags",
    "chunk_gen_data",
}};

template <>
struct field_accessor<v800::BiomeDefinitionData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.id;
        }
        else if constexpr (I == 1) {
            return value.temperature;
        }
        else if constexpr (I == 2) {
            return value.downfall;
        }
        else if constexpr (I == 3) {
            return value.red_spore_density;
        }
        else if constexpr (I == 4) {
            return value.blue_spore_density;
        }
        else if constexpr (I == 5) {
            return value.ash_density;
        }
        else if constexpr (I == 6) {
            return value.white_ash_density;
        }
        else if constexpr (I == 7) {
            return value.depth;
        }
        else if constexpr (I == 8) {
            return value.scale;
        }
        else if constexpr (I == 9) {
            return value.map_water_color_argb;
        }
        else if constexpr (I == 10) {
            return value.rain;
        }
        else if constexpr (I == 11) {
            return value.tags;
        }
        else {
            return value.chunk_gen_data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v827::BiomeDefinitionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v827::BiomeDefinitionData>{"BiomeDefinitionData"};

template <>
inline constexpr std::array<std::string_view, 13> field_names_v<v827::BiomeDefinitionData>{{
    "id",
    "temperature",
    "downfall",
    "red_spore_density",
    "blue_spore_density",
    "ash_density",
    "white_ash_density",
    "depth",
    "scale",
    "map_water_color_argb",
    "rain",
    "tags",
    "chunk_gen_data",
}};

template <>
struct field_accessor<v827::BiomeDefinitionData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.id;
        }
        else if constexpr (I == 1) {
            return value.temperature;
        }
        else if constexpr (I == 2) {
            return value.downfall;
        }
        else if constexpr (I == 3) {
            return value.red_spore_density;
        }
        else if constexpr (I == 4) {
            return value.blue_spore_density;
        }
        else if constexpr (I == 5) {
            return value.ash_density;
        }
        else if constexpr (I == 6) {
            return value.white_ash_density;
        }
        else if constexpr (I == 7) {
            return value.depth;
        }
        else if constexpr (I == 8) {
            return value.scale;
        }
        else if constexpr (I == 9) {
            return value.map_water_color_argb;
        }
        else if constexpr (I == 10) {
            return value.rain;
        }
        else if constexpr (I == 11) {
            return value.tags;
        }
        else {
            return value.chunk_gen_data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v844::BiomeDefinitionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v844::BiomeDefinitionData>{"BiomeDefinitionData"};

template <>
inline constexpr std::array<std::string_view, 10> field_names_v<v844::BiomeDefinitionData>{{
    "id",
    "temperature",
    "downfall",
    "foliage_snow",
    "depth",
    "scale",
    "map_water_color_argb",
    "rain",
    "tags",
    "chunk_gen_data",
}};

template <>
struct field_accessor<v844::BiomeDefinitionData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.id;
        }
        else if constexpr (I == 1) {
            return value.temperature;
        }
        else if constexpr (I == 2) {
            return value.downfall;
        }
        else if constexpr (I == 3) {
            return value.foliage_snow;
        }
        else if constexpr (I == 4) {
            return value.depth;
        }
        else if constexpr (I == 5) {
            return value.scale;
        }
        else if constexpr (I == 6) {
            return value.map_water_color_argb;
        }
        else if constexpr (I == 7) {
            return value.rain;
        }
        else if constexpr (I == 8) {
            return value.tags;
        }
        else {
            return value.chunk_gen_data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v859::BiomeDefinitionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v859::BiomeDefinitionData>{"BiomeDefinitionData"};

template <>
inline constexpr std::array<std::string_view, 10> field_names_v<v859::BiomeDefinitionData>{{
    "id",
    "temperature",
    "downfall",
    "foliage_snow",
    "depth",
    "scale",
    "map_water_color_argb",
    "rain",
    "tags",
    "chunk_gen_data",
}};

template <>
struct field_accessor<v859::BiomeDefinitionData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.id;
        }
        else if constexpr (I == 1) {
            return value.temperature;
        }
        else if constexpr (I == 2) {
            return value.downfall;
        }
        else if constexpr (I == 3) {
            return value.foliage_snow;
        }
        else if constexpr (I == 4) {
            return value.depth;
        }
        else if constexpr (I == 5) {
            return value.scale;
        }
        else if constexpr (I == 6) {
            return value.map_water_color_argb;
        }
        else if constexpr (I == 7) {
            return value.rain;
        }
        else if constexpr (I == 8) {
            return value.tags;
        }
        else {
            return value.chunk_gen_data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::BiomeDefinitionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::BiomeDefinitionData>{"BiomeDefinitionData"};

template <>
inline constexpr std::array<std::string_view, 10> field_names_v<v924::BiomeDefinitionData>{{
    "id",
    "temperature",
    "downfall",
    "foliage_snow",
    "depth",
    "scale",
    "map_water_color_argb",
    "rain",
    "tags",
    "chunk_gen_data",
}};

template <>
struct field_accessor<v924::BiomeDefinitionData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.id;
        }
        else if constexpr (I == 1) {
            return value.temperature;
        }
        else if constexpr (I == 2) {
            return value.downfall;
        }
        else if constexpr (I == 3) {
            return value.foliage_snow;
        }
        else if constexpr (I == 4) {
            return value.depth;
        }
        else if constexpr (I == 5) {
            return value.scale;
        }
        else if constexpr (I == 6) {
            return value.map_water_color_argb;
        }
        else if constexpr (I == 7) {
            return value.rain;
        }
        else if constexpr (I == 8) {
            return value.tags;
        }
        else {
            return value.chunk_gen_data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v975::BiomeDefinitionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v975::BiomeDefinitionData>{"BiomeDefinitionData"};

template <>
inline constexpr std::array<std::string_view, 10> field_names_v<v975::BiomeDefinitionData>{{
    "id",
    "temperature",
    "downfall",
    "foliage_snow",
    "depth",
    "scale",
    "map_water_color_argb",
    "rain",
    "tags",
    "chunk_gen_data",
}};

template <>
struct field_accessor<v975::BiomeDefinitionData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.id;
        }
        else if constexpr (I == 1) {
            return value.temperature;
        }
        else if constexpr (I == 2) {
            return value.downfall;
        }
        else if constexpr (I == 3) {
            return value.foliage_snow;
        }
        else if constexpr (I == 4) {
            return value.depth;
        }
        else if constexpr (I == 5) {
            return value.scale;
        }
        else if constexpr (I == 6) {
            return value.map_water_color_argb;
        }
        else if constexpr (I == 7) {
            return value.rain;
        }
        else if constexpr (I == 8) {
            return value.tags;
        }
        else {
            return value.chunk_gen_data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::BiomeDefinitionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::BiomeDefinitionData>{"BiomeDefinitionData"};

template <>
inline constexpr std::array<std::string_view, 10> field_names_v<v1001::BiomeDefinitionData>{{
    "id",
    "temperature",
    "downfall",
    "foliage_snow",
    "depth",
    "scale",
    "map_water_color_argb",
    "rain",
    "tags",
    "chunk_gen_data",
}};

template <>
struct field_accessor<v1001::BiomeDefinitionData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.id;
        }
        else if constexpr (I == 1) {
            return value.temperature;
        }
        else if constexpr (I == 2) {
            return value.downfall;
        }
        else if constexpr (I == 3) {
            return value.foliage_snow;
        }
        else if constexpr (I == 4) {
            return value.depth;
        }
        else if constexpr (I == 5) {
            return value.scale;
        }
        else if constexpr (I == 6) {
            return value.map_water_color_argb;
        }
        else if constexpr (I == 7) {
            return value.rain;
        }
        else if constexpr (I == 8) {
            return value.tags;
        }
        else {
            return value.chunk_gen_data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<BiomeStringList> = true;

template <>
inline constexpr std::string_view struct_name_v<BiomeStringList>{"BiomeStringList"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<BiomeStringList>{{
    "strings",
}};

template <>
struct field_accessor<BiomeStringList> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.strings;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::BiomeDefinitionListPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::BiomeDefinitionListPacket>{"BiomeDefinitionListPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::BiomeDefinitionListPacket>{{
    "biome_data",
}};

template <>
struct field_accessor<base::BiomeDefinitionListPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.biome_data;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v800::BiomeDefinitionListPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v800::BiomeDefinitionListPacket>{"BiomeDefinitionListPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v800::BiomeDefinitionListPacket>{{
    "biome_data",
    "string_list",
}};

template <>
struct field_accessor<v800::BiomeDefinitionListPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.biome_data;
        }
        else {
            return value.string_list;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v827::BiomeDefinitionListPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v827::BiomeDefinitionListPacket>{"BiomeDefinitionListPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v827::BiomeDefinitionListPacket>{{
    "biome_data",
    "string_list",
}};

template <>
struct field_accessor<v827::BiomeDefinitionListPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.biome_data;
        }
        else {
            return value.string_list;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v844::BiomeDefinitionListPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v844::BiomeDefinitionListPacket>{"BiomeDefinitionListPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v844::BiomeDefinitionListPacket>{{
    "biome_data",
    "string_list",
}};

template <>
struct field_accessor<v844::BiomeDefinitionListPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.biome_data;
        }
        else {
            return value.string_list;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v859::BiomeDefinitionListPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v859::BiomeDefinitionListPacket>{"BiomeDefinitionListPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v859::BiomeDefinitionListPacket>{{
    "biome_data",
    "string_list",
}};

template <>
struct field_accessor<v859::BiomeDefinitionListPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.biome_data;
        }
        else {
            return value.string_list;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::BiomeDefinitionListPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::BiomeDefinitionListPacket>{"BiomeDefinitionListPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v924::BiomeDefinitionListPacket>{{
    "biome_data",
    "string_list",
}};

template <>
struct field_accessor<v924::BiomeDefinitionListPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.biome_data;
        }
        else {
            return value.string_list;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v975::BiomeDefinitionListPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v975::BiomeDefinitionListPacket>{"BiomeDefinitionListPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v975::BiomeDefinitionListPacket>{{
    "biome_data",
    "string_list",
}};

template <>
struct field_accessor<v975::BiomeDefinitionListPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.biome_data;
        }
        else {
            return value.string_list;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::BiomeDefinitionListPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::BiomeDefinitionListPacket>{"BiomeDefinitionListPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v1001::BiomeDefinitionListPacket>{{
    "biome_data",
    "string_list",
}};

template <>
struct field_accessor<v1001::BiomeDefinitionListPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.biome_data;
        }
        else {
            return value.string_list;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::CompressedBiomeDefinitionListPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::CompressedBiomeDefinitionListPacket>{"CompressedBiomeDefinitionListPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::CompressedBiomeDefinitionListPacket>{{
    "compressed_biome_data",
}};

template <>
struct field_accessor<base::CompressedBiomeDefinitionListPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.compressed_biome_data;
    }
};

}  // namespace detail


template <>
struct Serializer<FloatRange> {
    static void serialize(BinaryWriter &stream, const FloatRange &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<FloatRange, std::error_code>;
};

template <>
struct Serializer<v1001::NoiseDescriptor> {
    static void serialize(BinaryWriter &stream, const v1001::NoiseDescriptor &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::NoiseDescriptor, std::error_code>;
};

template <>
struct Serializer<v1001::SerializedNoiseBlockSpecifier> {
    static void serialize(BinaryWriter &stream, const v1001::SerializedNoiseBlockSpecifier &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::SerializedNoiseBlockSpecifier, std::error_code>;
};

template <>
struct Serializer<base::BiomeNoiseGradientSurfaceData> {
    static void serialize(BinaryWriter &stream, const base::BiomeNoiseGradientSurfaceData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::BiomeNoiseGradientSurfaceData, std::error_code>;
};

template <>
struct Serializer<v1001::BiomeNoiseGradientSurfaceData> {
    static void serialize(BinaryWriter &stream, const v1001::BiomeNoiseGradientSurfaceData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::BiomeNoiseGradientSurfaceData, std::error_code>;
};

template <>
struct Serializer<BiomeSurfaceMaterialData> {
    static void serialize(BinaryWriter &stream, const BiomeSurfaceMaterialData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<BiomeSurfaceMaterialData, std::error_code>;
};

template <>
struct Serializer<BiomeMesaSurfaceData> {
    static void serialize(BinaryWriter &stream, const BiomeMesaSurfaceData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<BiomeMesaSurfaceData, std::error_code>;
};

template <>
struct Serializer<BiomeCappedSurfaceData> {
    static void serialize(BinaryWriter &stream, const BiomeCappedSurfaceData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<BiomeCappedSurfaceData, std::error_code>;
};

template <>
struct Serializer<base::BiomeSurfaceBuilderData> {
    static void serialize(BinaryWriter &stream, const base::BiomeSurfaceBuilderData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::BiomeSurfaceBuilderData, std::error_code>;
};

template <>
struct Serializer<v1001::BiomeSurfaceBuilderData> {
    static void serialize(BinaryWriter &stream, const v1001::BiomeSurfaceBuilderData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::BiomeSurfaceBuilderData, std::error_code>;
};

template <>
struct Serializer<base::BiomeClimateData> {
    static void serialize(BinaryWriter &stream, const base::BiomeClimateData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::BiomeClimateData, std::error_code>;
};

template <>
struct Serializer<v844::BiomeClimateData> {
    static void serialize(BinaryWriter &stream, const v844::BiomeClimateData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v844::BiomeClimateData, std::error_code>;
};

template <>
struct Serializer<base::BiomeCoordinateData> {
    static void serialize(BinaryWriter &stream, const base::BiomeCoordinateData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::BiomeCoordinateData, std::error_code>;
};

template <>
struct Serializer<v800::BiomeCoordinateData> {
    static void serialize(BinaryWriter &stream, const v800::BiomeCoordinateData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v800::BiomeCoordinateData, std::error_code>;
};

template <>
struct Serializer<v859::BiomeCoordinateData> {
    static void serialize(BinaryWriter &stream, const v859::BiomeCoordinateData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v859::BiomeCoordinateData, std::error_code>;
};

template <>
struct Serializer<base::BiomeScatterParamData> {
    static void serialize(BinaryWriter &stream, const base::BiomeScatterParamData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::BiomeScatterParamData, std::error_code>;
};

template <>
struct Serializer<v800::BiomeScatterParamData> {
    static void serialize(BinaryWriter &stream, const v800::BiomeScatterParamData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v800::BiomeScatterParamData, std::error_code>;
};

template <>
struct Serializer<v859::BiomeScatterParamData> {
    static void serialize(BinaryWriter &stream, const v859::BiomeScatterParamData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v859::BiomeScatterParamData, std::error_code>;
};

template <>
struct Serializer<base::BiomeConsolidatedFeatureData> {
    static void serialize(BinaryWriter &stream, const base::BiomeConsolidatedFeatureData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::BiomeConsolidatedFeatureData, std::error_code>;
};

template <>
struct Serializer<v800::BiomeConsolidatedFeatureData> {
    static void serialize(BinaryWriter &stream, const v800::BiomeConsolidatedFeatureData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v800::BiomeConsolidatedFeatureData, std::error_code>;
};

template <>
struct Serializer<v859::BiomeConsolidatedFeatureData> {
    static void serialize(BinaryWriter &stream, const v859::BiomeConsolidatedFeatureData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v859::BiomeConsolidatedFeatureData, std::error_code>;
};

template <>
struct Serializer<base::BiomeConsolidatedFeaturesData> {
    static void serialize(BinaryWriter &stream, const base::BiomeConsolidatedFeaturesData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::BiomeConsolidatedFeaturesData, std::error_code>;
};

template <>
struct Serializer<v800::BiomeConsolidatedFeaturesData> {
    static void serialize(BinaryWriter &stream, const v800::BiomeConsolidatedFeaturesData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v800::BiomeConsolidatedFeaturesData, std::error_code>;
};

template <>
struct Serializer<v859::BiomeConsolidatedFeaturesData> {
    static void serialize(BinaryWriter &stream, const v859::BiomeConsolidatedFeaturesData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v859::BiomeConsolidatedFeaturesData, std::error_code>;
};

template <>
struct Serializer<BiomeMountainParamsData> {
    static void serialize(BinaryWriter &stream, const BiomeMountainParamsData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<BiomeMountainParamsData, std::error_code>;
};

template <>
struct Serializer<base::BiomeElementData> {
    static void serialize(BinaryWriter &stream, const base::BiomeElementData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::BiomeElementData, std::error_code>;
};

template <>
struct Serializer<v800::BiomeElementData> {
    static void serialize(BinaryWriter &stream, const v800::BiomeElementData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v800::BiomeElementData, std::error_code>;
};

template <>
struct Serializer<v859::BiomeElementData> {
    static void serialize(BinaryWriter &stream, const v859::BiomeElementData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v859::BiomeElementData, std::error_code>;
};

template <>
struct Serializer<base::BiomeSurfaceMaterialAdjustmentData> {
    static void serialize(BinaryWriter &stream, const base::BiomeSurfaceMaterialAdjustmentData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::BiomeSurfaceMaterialAdjustmentData, std::error_code>;
};

template <>
struct Serializer<v800::BiomeSurfaceMaterialAdjustmentData> {
    static void serialize(BinaryWriter &stream, const v800::BiomeSurfaceMaterialAdjustmentData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v800::BiomeSurfaceMaterialAdjustmentData, std::error_code>;
};

template <>
struct Serializer<v859::BiomeSurfaceMaterialAdjustmentData> {
    static void serialize(BinaryWriter &stream, const v859::BiomeSurfaceMaterialAdjustmentData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v859::BiomeSurfaceMaterialAdjustmentData, std::error_code>;
};

template <>
struct Serializer<BiomeWeightedData> {
    static void serialize(BinaryWriter &stream, const BiomeWeightedData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<BiomeWeightedData, std::error_code>;
};

template <>
struct Serializer<BiomeConditionalTransformationData> {
    static void serialize(BinaryWriter &stream, const BiomeConditionalTransformationData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<BiomeConditionalTransformationData, std::error_code>;
};

template <>
struct Serializer<BiomeWeightedTemperatureData> {
    static void serialize(BinaryWriter &stream, const BiomeWeightedTemperatureData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<BiomeWeightedTemperatureData, std::error_code>;
};

template <>
struct Serializer<BiomeOverworldGenRulesData> {
    static void serialize(BinaryWriter &stream, const BiomeOverworldGenRulesData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<BiomeOverworldGenRulesData, std::error_code>;
};

template <>
struct Serializer<BiomeMultinoiseGenRulesData> {
    static void serialize(BinaryWriter &stream, const BiomeMultinoiseGenRulesData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<BiomeMultinoiseGenRulesData, std::error_code>;
};

template <>
struct Serializer<BiomeLegacyWorldGenRulesData> {
    static void serialize(BinaryWriter &stream, const BiomeLegacyWorldGenRulesData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<BiomeLegacyWorldGenRulesData, std::error_code>;
};

template <>
struct Serializer<BiomeReplacementData> {
    static void serialize(BinaryWriter &stream, const BiomeReplacementData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<BiomeReplacementData, std::error_code>;
};

template <>
struct Serializer<BiomeReplacementsData> {
    static void serialize(BinaryWriter &stream, const BiomeReplacementsData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<BiomeReplacementsData, std::error_code>;
};

template <>
struct Serializer<BiomeTagsData> {
    static void serialize(BinaryWriter &stream, const BiomeTagsData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<BiomeTagsData, std::error_code>;
};

template <>
struct Serializer<base::BiomeDefinitionChunkGenData> {
    static void serialize(BinaryWriter &stream, const base::BiomeDefinitionChunkGenData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::BiomeDefinitionChunkGenData, std::error_code>;
};

template <>
struct Serializer<v800::BiomeDefinitionChunkGenData> {
    static void serialize(BinaryWriter &stream, const v800::BiomeDefinitionChunkGenData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v800::BiomeDefinitionChunkGenData, std::error_code>;
};

template <>
struct Serializer<v844::BiomeDefinitionChunkGenData> {
    static void serialize(BinaryWriter &stream, const v844::BiomeDefinitionChunkGenData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v844::BiomeDefinitionChunkGenData, std::error_code>;
};

template <>
struct Serializer<v859::BiomeDefinitionChunkGenData> {
    static void serialize(BinaryWriter &stream, const v859::BiomeDefinitionChunkGenData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v859::BiomeDefinitionChunkGenData, std::error_code>;
};

template <>
struct Serializer<v924::BiomeDefinitionChunkGenData> {
    static void serialize(BinaryWriter &stream, const v924::BiomeDefinitionChunkGenData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::BiomeDefinitionChunkGenData, std::error_code>;
};

template <>
struct Serializer<v975::BiomeDefinitionChunkGenData> {
    static void serialize(BinaryWriter &stream, const v975::BiomeDefinitionChunkGenData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v975::BiomeDefinitionChunkGenData, std::error_code>;
};

template <>
struct Serializer<v1001::BiomeDefinitionChunkGenData> {
    static void serialize(BinaryWriter &stream, const v1001::BiomeDefinitionChunkGenData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::BiomeDefinitionChunkGenData, std::error_code>;
};

template <>
struct Serializer<base::BiomeDefinitionData> {
    static void serialize(BinaryWriter &stream, const base::BiomeDefinitionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::BiomeDefinitionData, std::error_code>;
};

template <>
struct Serializer<v800::BiomeDefinitionData> {
    static void serialize(BinaryWriter &stream, const v800::BiomeDefinitionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v800::BiomeDefinitionData, std::error_code>;
};

template <>
struct Serializer<v827::BiomeDefinitionData> {
    static void serialize(BinaryWriter &stream, const v827::BiomeDefinitionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v827::BiomeDefinitionData, std::error_code>;
};

template <>
struct Serializer<v844::BiomeDefinitionData> {
    static void serialize(BinaryWriter &stream, const v844::BiomeDefinitionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v844::BiomeDefinitionData, std::error_code>;
};

template <>
struct Serializer<v859::BiomeDefinitionData> {
    static void serialize(BinaryWriter &stream, const v859::BiomeDefinitionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v859::BiomeDefinitionData, std::error_code>;
};

template <>
struct Serializer<v924::BiomeDefinitionData> {
    static void serialize(BinaryWriter &stream, const v924::BiomeDefinitionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::BiomeDefinitionData, std::error_code>;
};

template <>
struct Serializer<v975::BiomeDefinitionData> {
    static void serialize(BinaryWriter &stream, const v975::BiomeDefinitionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v975::BiomeDefinitionData, std::error_code>;
};

template <>
struct Serializer<v1001::BiomeDefinitionData> {
    static void serialize(BinaryWriter &stream, const v1001::BiomeDefinitionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::BiomeDefinitionData, std::error_code>;
};

template <>
struct Serializer<BiomeStringList> {
    static void serialize(BinaryWriter &stream, const BiomeStringList &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<BiomeStringList, std::error_code>;
};

template <>
struct Serializer<base::BiomeDefinitionListPacket> {
    static void serialize(BinaryWriter &stream, const base::BiomeDefinitionListPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::BiomeDefinitionListPacket, std::error_code>;
};

template <>
struct Serializer<v800::BiomeDefinitionListPacket> {
    static void serialize(BinaryWriter &stream, const v800::BiomeDefinitionListPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v800::BiomeDefinitionListPacket, std::error_code>;
};

template <>
struct Serializer<v827::BiomeDefinitionListPacket> {
    static void serialize(BinaryWriter &stream, const v827::BiomeDefinitionListPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v827::BiomeDefinitionListPacket, std::error_code>;
};

template <>
struct Serializer<v844::BiomeDefinitionListPacket> {
    static void serialize(BinaryWriter &stream, const v844::BiomeDefinitionListPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v844::BiomeDefinitionListPacket, std::error_code>;
};

template <>
struct Serializer<v859::BiomeDefinitionListPacket> {
    static void serialize(BinaryWriter &stream, const v859::BiomeDefinitionListPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v859::BiomeDefinitionListPacket, std::error_code>;
};

template <>
struct Serializer<v924::BiomeDefinitionListPacket> {
    static void serialize(BinaryWriter &stream, const v924::BiomeDefinitionListPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::BiomeDefinitionListPacket, std::error_code>;
};

template <>
struct Serializer<v975::BiomeDefinitionListPacket> {
    static void serialize(BinaryWriter &stream, const v975::BiomeDefinitionListPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v975::BiomeDefinitionListPacket, std::error_code>;
};

template <>
struct Serializer<v1001::BiomeDefinitionListPacket> {
    static void serialize(BinaryWriter &stream, const v1001::BiomeDefinitionListPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::BiomeDefinitionListPacket, std::error_code>;
};

template <>
struct Serializer<base::CompressedBiomeDefinitionListPacket> {
    static void serialize(BinaryWriter &stream, const base::CompressedBiomeDefinitionListPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::CompressedBiomeDefinitionListPacket, std::error_code>;
};
using NoiseDescriptor = NoiseDescriptor_<2225>;
using SerializedNoiseBlockSpecifier = SerializedNoiseBlockSpecifier_<2225>;
using BiomeNoiseGradientSurfaceData = BiomeNoiseGradientSurfaceData_<2225>;
using BiomeSurfaceBuilderData = BiomeSurfaceBuilderData_<2225>;
using BiomeClimateData = BiomeClimateData_<2225>;
using BiomeCoordinateData = BiomeCoordinateData_<2225>;
using BiomeScatterParamData = BiomeScatterParamData_<2225>;
using BiomeConsolidatedFeatureData = BiomeConsolidatedFeatureData_<2225>;
using BiomeConsolidatedFeaturesData = BiomeConsolidatedFeaturesData_<2225>;
using BiomeElementData = BiomeElementData_<2225>;
using BiomeSurfaceMaterialAdjustmentData = BiomeSurfaceMaterialAdjustmentData_<2225>;
using BiomeDefinitionChunkGenData = BiomeDefinitionChunkGenData_<2225>;
using BiomeDefinitionData = BiomeDefinitionData_<2225>;
using BiomeDefinitionListPacket = BiomeDefinitionListPacket_<2225>;

}  // namespace bedrock::protocol
