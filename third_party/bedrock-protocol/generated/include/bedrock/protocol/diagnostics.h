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

namespace bedrock::protocol {

struct SystemDiagnosticTimingInfo {
    std::string display_name{};
    std::uint64_t system_index{};
    std::uint64_t time_in_ns{};
    std::uint8_t percent_of_total{};
};

struct ScopeDataSummary {
    std::string label{};
    std::string indentation{};
    std::uint64_t total_high_cost_ns{};
    std::uint64_t total_mid_cost_ns{};
    std::uint64_t total_low_cost_ns{};
};

struct DebugInfoPacket {
    static constexpr int Id = 155;
    ActorUniqueID actor_id{};
    std::string data{};
};

namespace ClientboundDebugRendererPacket_nested {

enum class PayloadType : std::uint8_t {
    Invalid = 0,
    ClearDebugMarkers = 1,
    AddDebugMarkerCube = 2,
};

struct DebugMarkerData {
    std::string text{};
    Vec3 position{};
    Color color{};
    std::uint64_t duration_ms{};
};

}  // namespace ClientboundDebugRendererPacket_nested

struct ClientboundDebugRendererPacket {
    using PayloadType = ClientboundDebugRendererPacket_nested::PayloadType;
    using DebugMarkerData = ClientboundDebugRendererPacket_nested::DebugMarkerData;

    static constexpr int Id = 164;
    ClientboundDebugRendererPacket::PayloadType type{};
    std::optional<ClientboundDebugRendererPacket::DebugMarkerData> debug_marker_data{};
};

namespace base {

enum class MemoryCategory : std::uint8_t {
    Unknown = 0,
    InvalidSizeUnknown = 1,
    Actor = 2,
    ActorAnimation = 3,
    ActorRendering = 4,
    Balancer = 5,
    BlockTickingQueues = 6,
    BiomeStorage = 7,
    Cereal = 8,
    CircuitSystem = 9,
    Client = 10,
    Commands = 11,
    DBStorage = 12,
    Debug = 13,
    Documentation = 14,
    ECSSystems = 15,
    FMOD = 16,
    Fonts = 17,
    ImGui = 18,
    Input = 19,
    JsonUI = 20,
    JsonUIControlFactoryJson = 21,
    JsonUIControlTree = 22,
    JsonUIControlTreeControlElement = 23,
    JsonUIControlTreePopulateDataBinding = 24,
    JsonUIControlTreePopulateFocus = 25,
    JsonUIControlTreePopulateLayout = 26,
    JsonUIControlTreePopulateOther = 27,
    JsonUIControlTreePopulateSprite = 28,
    JsonUIControlTreePopulateText = 29,
    JsonUIControlTreePopulateTTS = 30,
    JsonUIControlTreeVisibility = 31,
    JsonUICreateUI = 32,
    JsonUIDefs = 33,
    JsonUILayoutManager = 34,
    JsonUILayoutManagerRemoveDependencies = 35,
    JsonUILayoutManagerInitVariable = 36,
    Languages = 37,
    Level = 38,
    LevelStructures = 39,
    LevelChunk = 40,
    LevelChunkGen = 41,
    LevelChunkGenThreadLocal = 42,
    Network = 43,
    MaterialDragonCompiledDefinition = 44,
    MaterialDragonMaterial = 45,
    MaterialDragonResource = 46,
    MaterialDragonUniformMap = 47,
    MaterialRenderMaterial = 48,
    MaterialRenderMaterialGroup = 49,
    MaterialVariationManager = 50,
    Molang = 51,
    OreUI = 52,
    Persona = 53,
    Player = 54,
    RenderChunk = 55,
    RenderChunkIndexBuffer = 56,
    RenderChunkVertexBuffer = 57,
    Rendering = 58,
    RenderingLibrary = 59,
    ResourcePacks = 60,
    Sound = 61,
    SubChunkBiomeData = 62,
    SubChunkBlockData = 63,
    SubChunkLightData = 64,
    Textures = 65,
    Vr = 66,
    WeatherRenderer = 67,
    WorldGenerator = 68,
    Tasks = 69,
    Test = 70,
    Scripting = 71,
    ScriptingRuntime = 72,
    ScriptingContext = 73,
    ScriptingContextBindingsMC = 74,
    ScriptingContextBindingsGT = 75,
    ScriptingContextRun = 76,
    Count = 77,
};

struct EntityDiagnosticTimingInfo {
    std::string display_name{};
    std::string entity{};
    std::uint64_t time_in_ns{};
    std::uint8_t percent_of_total{};
};

struct ServerboundDiagnosticsPacket {
    static constexpr int Id = 315;
    float avg_fps{};
    float avg_server_sim_tick_time_ms{};
    float avg_client_sim_tick_time_ms{};
    float avg_begin_frame_time_ms{};
    float avg_input_time_ms{};
    float avg_render_time_ms{};
    float avg_end_frame_time_ms{};
    float avg_remainder_time_percent{};
    float avg_unaccounted_time_percent{};
};

struct EditorNetworkPacket {
    static constexpr int Id = 190;
    bool route_to_manager{};
    CompoundTag payload{};
};

}  // namespace base

namespace v766 {

using MemoryCategory = base::MemoryCategory;

using EntityDiagnosticTimingInfo = base::EntityDiagnosticTimingInfo;

using ServerboundDiagnosticsPacket = base::ServerboundDiagnosticsPacket;

using EditorNetworkPacket = base::EditorNetworkPacket;

}  // namespace v766

namespace v776 {

using MemoryCategory = base::MemoryCategory;

using EntityDiagnosticTimingInfo = base::EntityDiagnosticTimingInfo;

using ServerboundDiagnosticsPacket = base::ServerboundDiagnosticsPacket;

using EditorNetworkPacket = base::EditorNetworkPacket;

}  // namespace v776

namespace v786 {

using MemoryCategory = base::MemoryCategory;

using EntityDiagnosticTimingInfo = base::EntityDiagnosticTimingInfo;

using ServerboundDiagnosticsPacket = base::ServerboundDiagnosticsPacket;

using EditorNetworkPacket = base::EditorNetworkPacket;

}  // namespace v786

namespace v800 {

using MemoryCategory = base::MemoryCategory;

using EntityDiagnosticTimingInfo = base::EntityDiagnosticTimingInfo;

using ServerboundDiagnosticsPacket = base::ServerboundDiagnosticsPacket;

using EditorNetworkPacket = base::EditorNetworkPacket;

}  // namespace v800

namespace v818 {

using MemoryCategory = base::MemoryCategory;

using EntityDiagnosticTimingInfo = base::EntityDiagnosticTimingInfo;

using ServerboundDiagnosticsPacket = base::ServerboundDiagnosticsPacket;

using EditorNetworkPacket = base::EditorNetworkPacket;

}  // namespace v818

namespace v827 {

using MemoryCategory = base::MemoryCategory;

using EntityDiagnosticTimingInfo = base::EntityDiagnosticTimingInfo;

using ServerboundDiagnosticsPacket = base::ServerboundDiagnosticsPacket;

using EditorNetworkPacket = base::EditorNetworkPacket;

}  // namespace v827

namespace v844 {

enum class MemoryCategory : std::uint8_t {
    Unknown = 0,
    InvalidSizeUnknown = 1,
    Actor = 2,
    ActorAnimation = 3,
    ActorRendering = 4,
    Balancer = 5,
    BlockTickingQueues = 6,
    BiomeStorage = 7,
    Cereal = 8,
    CircuitSystem = 9,
    Client = 10,
    Commands = 11,
    DBStorage = 12,
    Debug = 13,
    Documentation = 14,
    ECSSystems = 15,
    FMOD = 16,
    Fonts = 17,
    ImGui = 18,
    Input = 19,
    JsonUI = 20,
    JsonUIControlFactoryJson = 21,
    JsonUIControlTree = 22,
    JsonUIControlTreeControlElement = 23,
    JsonUIControlTreePopulateDataBinding = 24,
    JsonUIControlTreePopulateFocus = 25,
    JsonUIControlTreePopulateLayout = 26,
    JsonUIControlTreePopulateOther = 27,
    JsonUIControlTreePopulateSprite = 28,
    JsonUIControlTreePopulateText = 29,
    JsonUIControlTreePopulateTTS = 30,
    JsonUIControlTreeVisibility = 31,
    JsonUICreateUI = 32,
    JsonUIDefs = 33,
    JsonUILayoutManager = 34,
    JsonUILayoutManagerRemoveDependencies = 35,
    JsonUILayoutManagerInitVariable = 36,
    Languages = 37,
    Level = 38,
    LevelStructures = 39,
    LevelChunk = 40,
    LevelChunkGen = 41,
    LevelChunkGenThreadLocal = 42,
    Network = 43,
    Marketplace = 44,
    MaterialDragonCompiledDefinition = 45,
    MaterialDragonMaterial = 46,
    MaterialDragonResource = 47,
    MaterialDragonUniformMap = 48,
    MaterialRenderMaterial = 49,
    MaterialRenderMaterialGroup = 50,
    MaterialVariationManager = 51,
    Molang = 52,
    OreUI = 53,
    Persona = 54,
    Player = 55,
    RenderChunk = 56,
    RenderChunkIndexBuffer = 57,
    RenderChunkVertexBuffer = 58,
    Rendering = 59,
    RenderingLibrary = 60,
    ResourcePacks = 61,
    Sound = 62,
    SubChunkBiomeData = 63,
    SubChunkBlockData = 64,
    SubChunkLightData = 65,
    Textures = 66,
    Vr = 67,
    WeatherRenderer = 68,
    WorldGenerator = 69,
    Tasks = 70,
    Test = 71,
    Scripting = 72,
    ScriptingRuntime = 73,
    ScriptingContext = 74,
    ScriptingContextBindingsMC = 75,
    ScriptingContextBindingsGT = 76,
    ScriptingContextRun = 77,
    Count = 78,
};

using EntityDiagnosticTimingInfo = base::EntityDiagnosticTimingInfo;

using ServerboundDiagnosticsPacket = base::ServerboundDiagnosticsPacket;

using EditorNetworkPacket = base::EditorNetworkPacket;

}  // namespace v844

namespace v859 {

using MemoryCategory = v844::MemoryCategory;

using EntityDiagnosticTimingInfo = base::EntityDiagnosticTimingInfo;

using ServerboundDiagnosticsPacket = base::ServerboundDiagnosticsPacket;

using EditorNetworkPacket = base::EditorNetworkPacket;

}  // namespace v859

namespace v898 {

enum class MemoryCategory : std::uint8_t {
    Unknown = 0,
    InvalidSizeUnknown = 1,
    Actor = 2,
    ActorAnimation = 3,
    ActorRendering = 4,
    Balancer = 5,
    BlockTickingQueues = 6,
    BiomeStorage = 7,
    Cereal = 8,
    CircuitSystem = 9,
    Client = 10,
    Commands = 11,
    DBStorage = 12,
    Debug = 13,
    Documentation = 14,
    ECSSystems = 15,
    FMOD = 16,
    Fonts = 17,
    ImGui = 18,
    Input = 19,
    JsonUI = 20,
    JsonUIControlFactoryJson = 21,
    JsonUIControlTree = 22,
    JsonUIControlTreeControlElement = 23,
    JsonUIControlTreePopulateDataBinding = 24,
    JsonUIControlTreePopulateFocus = 25,
    JsonUIControlTreePopulateLayout = 26,
    JsonUIControlTreePopulateOther = 27,
    JsonUIControlTreePopulateSprite = 28,
    JsonUIControlTreePopulateText = 29,
    JsonUIControlTreePopulateTTS = 30,
    JsonUIControlTreeVisibility = 31,
    JsonUICreateUI = 32,
    JsonUIDefs = 33,
    JsonUILayoutManager = 34,
    JsonUILayoutManagerRemoveDependencies = 35,
    JsonUILayoutManagerInitVariable = 36,
    Languages = 37,
    Level = 38,
    LevelStructures = 39,
    LevelChunk = 40,
    LevelChunkGen = 41,
    LevelChunkGenThreadLocal = 42,
    Network = 43,
    Marketplace = 44,
    MaterialDragonCompiledDefinition = 45,
    MaterialDragonMaterial = 46,
    MaterialDragonResource = 47,
    MaterialDragonUniformMap = 48,
    MaterialRenderMaterial = 49,
    MaterialRenderMaterialGroup = 50,
    MaterialVariationManager = 51,
    Molang = 52,
    OreUI = 53,
    Persona = 54,
    Player = 55,
    RenderChunk = 56,
    RenderChunkIndexBuffer = 57,
    RenderChunkVertexBuffer = 58,
    Rendering = 59,
    RenderingLibrary = 60,
    RequestLog = 61,
    ResourcePacks = 62,
    Sound = 63,
    SubChunkBiomeData = 64,
    SubChunkBlockData = 65,
    SubChunkLightData = 66,
    Textures = 67,
    Vr = 68,
    WeatherRenderer = 69,
    WorldGenerator = 70,
    Tasks = 71,
    Test = 72,
    Scripting = 73,
    ScriptingRuntime = 74,
    ScriptingContext = 75,
    ScriptingContextBindingsMC = 76,
    ScriptingContextBindingsGT = 77,
    ScriptingContextRun = 78,
    DataDrivenUI = 79,
    DataDrivenUIDefs = 80,
    Count = 81,
};

using EntityDiagnosticTimingInfo = base::EntityDiagnosticTimingInfo;

using ServerboundDiagnosticsPacket = base::ServerboundDiagnosticsPacket;

using EditorNetworkPacket = base::EditorNetworkPacket;

}  // namespace v898

namespace v924 {

using MemoryCategory = v898::MemoryCategory;

struct MemoryCategoryCounter {
    v898::MemoryCategory category{};
    std::uint64_t current_bytes{};
};

using EntityDiagnosticTimingInfo = base::EntityDiagnosticTimingInfo;

struct ServerboundDiagnosticsPacket {
    static constexpr int Id = 315;
    float avg_fps{};
    float avg_server_sim_tick_time_ms{};
    float avg_client_sim_tick_time_ms{};
    float avg_begin_frame_time_ms{};
    float avg_input_time_ms{};
    float avg_render_time_ms{};
    float avg_end_frame_time_ms{};
    float avg_remainder_time_percent{};
    float avg_unaccounted_time_percent{};
    std::vector<v924::MemoryCategoryCounter> category_counters{};
};

using EditorNetworkPacket = base::EditorNetworkPacket;

}  // namespace v924

namespace v944 {

enum class MemoryCategory : std::uint8_t {
    Unknown = 0,
    InvalidSizeUnknown = 1,
    Actor = 2,
    ActorAnimation = 3,
    ActorRendering = 4,
    BlockTickingQueues = 5,
    BiomeStorage = 6,
    Cereal = 7,
    CircuitSystem = 8,
    Client = 9,
    Commands = 10,
    DBStorage = 11,
    Debug = 12,
    Documentation = 13,
    ECSSystems = 14,
    FMOD = 15,
    Fonts = 16,
    ImGui = 17,
    Input = 18,
    JsonUI = 19,
    JsonUIControlFactoryJson = 20,
    JsonUIControlTree = 21,
    JsonUIControlTreeControlElement = 22,
    JsonUIControlTreePopulateDataBinding = 23,
    JsonUIControlTreePopulateFocus = 24,
    JsonUIControlTreePopulateLayout = 25,
    JsonUIControlTreePopulateOther = 26,
    JsonUIControlTreePopulateSprite = 27,
    JsonUIControlTreePopulateText = 28,
    JsonUIControlTreePopulateTTS = 29,
    JsonUIControlTreeVisibility = 30,
    JsonUICreateUI = 31,
    JsonUIDefs = 32,
    JsonUILayoutManager = 33,
    JsonUILayoutManagerRemoveDependencies = 34,
    JsonUILayoutManagerInitVariable = 35,
    Languages = 36,
    Level = 37,
    LevelStructures = 38,
    LevelChunk = 39,
    LevelChunkGen = 40,
    LevelChunkGenThreadLocal = 41,
    LightVolumeManager = 42,
    Network = 43,
    Marketplace = 44,
    MaterialDragonCompiledDefinition = 45,
    MaterialDragonMaterial = 46,
    MaterialDragonResource = 47,
    MaterialDragonUniformMap = 48,
    MaterialRenderMaterial = 49,
    MaterialRenderMaterialGroup = 50,
    MaterialVariationManager = 51,
    Molang = 52,
    OreUI = 53,
    Persona = 54,
    Player = 55,
    RenderChunk = 56,
    RenderChunkIndexBuffer = 57,
    RenderChunkVertexBuffer = 58,
    Rendering = 59,
    RenderingLibrary = 60,
    RequestLog = 61,
    ResourcePacks = 62,
    Sound = 63,
    SubChunkBiomeData = 64,
    SubChunkBlockData = 65,
    SubChunkLightData = 66,
    Textures = 67,
    Vr = 68,
    WeatherRenderer = 69,
    WorldGenerator = 70,
    Tasks = 71,
    Test = 72,
    Scripting = 73,
    ScriptingRuntime = 74,
    ScriptingContext = 75,
    ScriptingContextBindingsMC = 76,
    ScriptingContextBindingsGT = 77,
    ScriptingContextRun = 78,
    DataDrivenUI = 79,
    DataDrivenUIDefs = 80,
    Gameface = 81,
    GamefaceSystem = 82,
    GamefaceDOM = 83,
    GamefaceCSS = 84,
    GamefaceDisplay = 85,
    GamefaceTempAllocator = 86,
    GamefacePoolAllocator = 87,
    GamefaceDump = 88,
    GamefaceMedia = 89,
    GamefaceJSON = 90,
    GamefaceScriptEngine = 91,
    Count = 92,
};

struct MemoryCategoryCounter {
    v944::MemoryCategory category{};
    std::uint64_t current_bytes{};
};

using EntityDiagnosticTimingInfo = base::EntityDiagnosticTimingInfo;

struct ServerboundDiagnosticsPacket {
    static constexpr int Id = 315;
    float avg_fps{};
    float avg_server_sim_tick_time_ms{};
    float avg_client_sim_tick_time_ms{};
    float avg_begin_frame_time_ms{};
    float avg_input_time_ms{};
    float avg_render_time_ms{};
    float avg_end_frame_time_ms{};
    float avg_remainder_time_percent{};
    float avg_unaccounted_time_percent{};
    std::vector<v944::MemoryCategoryCounter> category_counters{};
};

struct EditorNetworkPacket {
    static constexpr int Id = 190;
    bool route_to_manager{};
    std::string raw_variant_name{};
    std::string raw_variant_data{};
};

}  // namespace v944

namespace v975 {

enum class MemoryCategory : std::uint8_t {
    Unknown = 0,
    InvalidSizeUnknown = 1,
    Actor = 2,
    ActorAnimation = 3,
    ActorRendering = 4,
    BlockTickingQueues = 5,
    BiomeStorage = 6,
    Cereal = 7,
    CircuitSystem = 8,
    Client = 9,
    Commands = 10,
    DBStorage = 11,
    Debug = 12,
    Documentation = 13,
    ECSSystems = 14,
    FMOD = 15,
    Fonts = 16,
    ImGui = 17,
    Input = 18,
    JsonUI = 19,
    JsonUIControlFactoryJson = 20,
    JsonUIControlTree = 21,
    JsonUIControlTreeControlElement = 22,
    JsonUIControlTreePopulateDataBinding = 23,
    JsonUIControlTreePopulateFocus = 24,
    JsonUIControlTreePopulateLayout = 25,
    JsonUIControlTreePopulateOther = 26,
    JsonUIControlTreePopulateSprite = 27,
    JsonUIControlTreePopulateText = 28,
    JsonUIControlTreePopulateTTS = 29,
    JsonUIControlTreeVisibility = 30,
    JsonUICreateUI = 31,
    JsonUIDefs = 32,
    JsonUILayoutManager = 33,
    JsonUILayoutManagerRemoveDependencies = 34,
    JsonUILayoutManagerInitVariable = 35,
    Languages = 36,
    Level = 37,
    LevelStructures = 38,
    LevelChunk = 39,
    LevelChunkGen = 40,
    LevelChunkGenThreadLocal = 41,
    LightVolumeManager = 42,
    Network = 43,
    Marketplace = 44,
    MaterialDragonCompiledDefinition = 45,
    MaterialDragonMaterial = 46,
    MaterialDragonResource = 47,
    MaterialDragonUniformMap = 48,
    MaterialRenderMaterial = 49,
    MaterialRenderMaterialGroup = 50,
    MaterialVariationManager = 51,
    Molang = 52,
    OreUI = 53,
    Persona = 54,
    Player = 55,
    RenderChunk = 56,
    RenderChunkIndexBuffer = 57,
    RenderChunkVertexBuffer = 58,
    Rendering = 59,
    RenderingRenderRegistry = 60,
    RenderingLibrary = 61,
    RequestLog = 62,
    ResourcePacks = 63,
    Sound = 64,
    SubChunkBiomeData = 65,
    SubChunkBlockData = 66,
    SubChunkLightData = 67,
    Textures = 68,
    WeatherRenderer = 69,
    WorldGenerator = 70,
    Tasks = 71,
    Test = 72,
    Scripting = 73,
    ScriptingRuntime = 74,
    ScriptingContext = 75,
    ScriptingContextBindingsMC = 76,
    ScriptingContextBindingsGT = 77,
    ScriptingContextRun = 78,
    DataDrivenUI = 79,
    DataDrivenUIDefs = 80,
    Gameface = 81,
    GamefaceSystem = 82,
    GamefaceDOM = 83,
    GamefaceCSS = 84,
    GamefaceDisplay = 85,
    GamefaceTempAllocator = 86,
    GamefacePoolAllocator = 87,
    GamefaceDump = 88,
    GamefaceMedia = 89,
    GamefaceJSON = 90,
    GamefaceScriptEngine = 91,
    Count = 92,
};

struct MemoryCategoryCounter {
    v975::MemoryCategory category{};
    std::uint64_t current_bytes{};
};

using EntityDiagnosticTimingInfo = base::EntityDiagnosticTimingInfo;

struct ServerboundDiagnosticsPacket {
    static constexpr int Id = 315;
    float avg_fps{};
    float avg_server_sim_tick_time_ms{};
    float avg_client_sim_tick_time_ms{};
    float avg_begin_frame_time_ms{};
    float avg_input_time_ms{};
    float avg_render_time_ms{};
    float avg_end_frame_time_ms{};
    float avg_remainder_time_percent{};
    float avg_unaccounted_time_percent{};
    std::vector<v975::MemoryCategoryCounter> category_counters{};
    std::vector<base::EntityDiagnosticTimingInfo> entity_timings{};
    std::vector<SystemDiagnosticTimingInfo> system_timings{};
};

using EditorNetworkPacket = v944::EditorNetworkPacket;

}  // namespace v975

namespace v1001 {

using MemoryCategory = v975::MemoryCategory;

using MemoryCategoryCounter = v975::MemoryCategoryCounter;

using EntityDiagnosticTimingInfo = base::EntityDiagnosticTimingInfo;

struct ServerboundDiagnosticsPacket {
    static constexpr int Id = 315;
    float avg_fps{};
    float avg_server_sim_tick_time_ms{};
    float avg_client_sim_tick_time_ms{};
    float avg_begin_frame_time_ms{};
    float avg_input_time_ms{};
    float avg_render_time_ms{};
    float avg_end_frame_time_ms{};
    float avg_remainder_time_percent{};
    float avg_unaccounted_time_percent{};
    std::vector<v975::MemoryCategoryCounter> category_counters{};
    std::vector<base::EntityDiagnosticTimingInfo> entity_timings{};
    std::vector<SystemDiagnosticTimingInfo> system_timings{};
    std::vector<ScopeDataSummary> whisker_data{};
};

using EditorNetworkPacket = v944::EditorNetworkPacket;

}  // namespace v1001

namespace v2168 {

enum class MemoryCategory : std::uint8_t {
    Unknown = 0,
    InvalidSizeUnknown = 1,
    Actor = 2,
    ActorAnimation = 3,
    ActorRendering = 4,
    BlockTickingQueues = 5,
    BiomeStorage = 6,
    Blobs = 7,
    Cereal = 8,
    CircuitSystem = 9,
    Client = 10,
    Commands = 11,
    DBStorage = 12,
    Debug = 13,
    Documentation = 14,
    ECSSystems = 15,
    FMOD = 16,
    Fonts = 17,
    ImGui = 18,
    Input = 19,
    JsonUI = 20,
    JsonUIControlFactoryJson = 21,
    JsonUIControlTree = 22,
    JsonUIControlTreeControlElement = 23,
    JsonUIControlTreePopulateDataBinding = 24,
    JsonUIControlTreePopulateFocus = 25,
    JsonUIControlTreePopulateLayout = 26,
    JsonUIControlTreePopulateOther = 27,
    JsonUIControlTreePopulateSprite = 28,
    JsonUIControlTreePopulateText = 29,
    JsonUIControlTreePopulateTTS = 30,
    JsonUIControlTreeVisibility = 31,
    JsonUICreateUI = 32,
    JsonUIDefs = 33,
    JsonUILayoutManager = 34,
    JsonUILayoutManagerRemoveDependencies = 35,
    JsonUILayoutManagerInitVariable = 36,
    Languages = 37,
    Level = 38,
    LevelStructures = 39,
    LevelChunk = 40,
    LevelChunkGen = 41,
    LevelChunkGenThreadLocal = 42,
    LightVolumeManager = 43,
    Network = 44,
    Marketplace = 45,
    MaterialDragonCompiledDefinition = 46,
    MaterialDragonMaterial = 47,
    MaterialDragonResource = 48,
    MaterialDragonUniformMap = 49,
    MaterialRenderMaterial = 50,
    MaterialRenderMaterialGroup = 51,
    MaterialVariationManager = 52,
    Molang = 53,
    OreUI = 54,
    OreUIClient = 55,
    PersonaPieces = 56,
    PersonaAnimations = 57,
    PersonaTextures = 58,
    PersonaCharacters = 59,
    PersonaSkinPacks = 60,
    PersonaRepo = 61,
    Player = 62,
    RenderChunk = 63,
    RenderChunkIndexBuffer = 64,
    RenderChunkVertexBuffer = 65,
    Rendering = 66,
    RenderingBgfxInit = 67,
    RenderingBgfxStartFrame = 68,
    RenderingBlockTessellator = 69,
    RenderingEndFrame = 70,
    RenderingGraphicsTasksInit = 71,
    RenderingLibrary = 72,
    RenderingPolygonOperatorPool = 73,
    RenderingPBRTextureData = 74,
    RenderingRenderRegistry = 75,
    RenderingSetup = 76,
    RenderingVertices = 77,
    RequestLog = 78,
    ResourcePacks = 79,
    Sound = 80,
    SubChunkBiomeData = 81,
    SubChunkBlockData = 82,
    SubChunkLightData = 83,
    Textures = 84,
    WeatherRenderer = 85,
    WorldGenerator = 86,
    Tasks = 87,
    Test = 88,
    TestLoadTestTags = 89,
    Scripting = 90,
    ScriptingRuntime = 91,
    ScriptingContext = 92,
    ScriptingContextBindingsMC = 93,
    ScriptingContextBindingsGT = 94,
    ScriptingContextRun = 95,
    DataDrivenUI = 96,
    DataDrivenUIDefs = 97,
    Gameface = 98,
    GamefaceSystem = 99,
    GamefaceDOM = 100,
    GamefaceCSS = 101,
    GamefaceDisplay = 102,
    GamefaceTempAllocator = 103,
    GamefacePoolAllocator = 104,
    GamefaceDump = 105,
    GamefaceMedia = 106,
    GamefaceJSON = 107,
    GamefaceScriptEngine = 108,
    GamefaceScript = 109,
    GamefaceLayout = 110,
    Count = 111,
};

struct MemoryCategoryCounter {
    v2168::MemoryCategory category{};
    std::uint64_t current_bytes{};
};

using EntityDiagnosticTimingInfo = base::EntityDiagnosticTimingInfo;

struct SystemCategory {
    std::string category_name{};
    std::uint64_t system_index{};
};

struct ServerboundDiagnosticsPacket {
    static constexpr int Id = 315;
    float avg_fps{};
    float avg_server_sim_tick_time_ms{};
    float avg_client_sim_tick_time_ms{};
    float avg_begin_frame_time_ms{};
    float avg_input_time_ms{};
    float avg_render_time_ms{};
    float avg_end_frame_time_ms{};
    float avg_remainder_time_percent{};
    float avg_unaccounted_time_percent{};
    std::vector<v2168::MemoryCategoryCounter> category_counters{};
    std::vector<base::EntityDiagnosticTimingInfo> entity_timings{};
    std::vector<SystemDiagnosticTimingInfo> system_timings{};
    std::optional<std::vector<v2168::SystemCategory>> system_categories{};
    std::vector<ScopeDataSummary> whisker_data{};
};

using EditorNetworkPacket = v944::EditorNetworkPacket;

}  // namespace v2168

namespace v2193 {

enum class MemoryCategory : std::uint8_t {
    Unknown = 0,
    InvalidSizeUnknown = 1,
    Actor = 2,
    ActorAnimation = 3,
    ActorRendering = 4,
    BlockTickingQueues = 5,
    BiomeStorage = 6,
    Blobs = 7,
    Cereal = 8,
    CircuitSystem = 9,
    Client = 10,
    Commands = 11,
    DBStorage = 12,
    Debug = 13,
    Documentation = 14,
    ECSSystems = 15,
    FMOD = 16,
    Fonts = 17,
    ImGui = 18,
    Input = 19,
    JsonUI = 20,
    JsonUIControlFactoryJson = 21,
    JsonUIControlTree = 22,
    JsonUIControlTreeControlElement = 23,
    JsonUIControlTreePopulateDataBinding = 24,
    JsonUIControlTreePopulateFocus = 25,
    JsonUIControlTreePopulateLayout = 26,
    JsonUIControlTreePopulateOther = 27,
    JsonUIControlTreePopulateSprite = 28,
    JsonUIControlTreePopulateText = 29,
    JsonUIControlTreePopulateTTS = 30,
    JsonUIControlTreeVisibility = 31,
    JsonUICreateUI = 32,
    JsonUIDefs = 33,
    JsonUILayoutManager = 34,
    JsonUILayoutManagerRemoveDependencies = 35,
    JsonUILayoutManagerInitVariable = 36,
    Languages = 37,
    Level = 38,
    LevelStructures = 39,
    LevelChunk = 40,
    LevelChunkGen = 41,
    LevelChunkGenThreadLocal = 42,
    LightVolumeManager = 43,
    Network = 44,
    Marketplace = 45,
    MaterialDragonCompiledDefinition = 46,
    MaterialDragonMaterial = 47,
    MaterialDragonResource = 48,
    MaterialDragonUniformMap = 49,
    MaterialRenderMaterial = 50,
    MaterialRenderMaterialGroup = 51,
    MaterialVariationManager = 52,
    Molang = 53,
    OreUI = 54,
    OreUIClient = 55,
    PersonaPieces = 56,
    PersonaAnimations = 57,
    PersonaCharacters = 58,
    PersonaSkinPacks = 59,
    PersonaRepo = 60,
    Player = 61,
    RenderChunk = 62,
    RenderChunkIndexBuffer = 63,
    RenderChunkVertexBuffer = 64,
    Rendering = 65,
    RenderingBgfxInit = 66,
    RenderingBgfxStartFrame = 67,
    RenderingBlockTessellator = 68,
    RenderingEndFrame = 69,
    RenderingGraphicsTasksInit = 70,
    RenderingLibrary = 71,
    RenderingPolygonOperatorPool = 72,
    RenderingPBRTextureData = 73,
    RenderingRenderRegistry = 74,
    RenderingSetup = 75,
    RenderingVertices = 76,
    RequestLog = 77,
    ResourcePacks = 78,
    Sound = 79,
    SubChunkBiomeData = 80,
    SubChunkBlockData = 81,
    SubChunkLightData = 82,
    Textures = 83,
    WeatherRenderer = 84,
    WorldGenerator = 85,
    Tasks = 86,
    Test = 87,
    TestLoadTestTags = 88,
    Scripting = 89,
    ScriptingRuntime = 90,
    ScriptingContext = 91,
    ScriptingContextBindingsMC = 92,
    ScriptingContextBindingsGT = 93,
    ScriptingContextRun = 94,
    DataDrivenUI = 95,
    DataDrivenUIDefs = 96,
    Gameface = 97,
    GamefaceSystem = 98,
    GamefaceDOM = 99,
    GamefaceCSS = 100,
    GamefaceDisplay = 101,
    GamefaceTempAllocator = 102,
    GamefacePoolAllocator = 103,
    GamefaceDump = 104,
    GamefaceMedia = 105,
    GamefaceJSON = 106,
    GamefaceScriptEngine = 107,
    GamefaceScript = 108,
    GamefaceLayout = 109,
    Count = 110,
};

struct MemoryCategoryCounter {
    v2193::MemoryCategory category{};
    std::uint64_t current_bytes{};
};

struct EntityDiagnosticTimingInfo {
    std::string display_name{};
    std::string entity{};
    std::uint64_t time_in_ns{};
    std::uint8_t percent_of_total{};
    std::optional<Vec3> position{};
    std::optional<std::string> dimension{};
};

using SystemCategory = v2168::SystemCategory;

struct ServerboundDiagnosticsPacket {
    static constexpr int Id = 315;
    float avg_fps{};
    float avg_server_sim_tick_time_ms{};
    float avg_client_sim_tick_time_ms{};
    float avg_begin_frame_time_ms{};
    float avg_input_time_ms{};
    float avg_render_time_ms{};
    float avg_end_frame_time_ms{};
    float avg_remainder_time_percent{};
    float avg_unaccounted_time_percent{};
    std::vector<v2193::MemoryCategoryCounter> category_counters{};
    std::vector<v2193::EntityDiagnosticTimingInfo> entity_timings{};
    std::vector<SystemDiagnosticTimingInfo> system_timings{};
    std::optional<std::vector<v2168::SystemCategory>> system_categories{};
    std::vector<ScopeDataSummary> whisker_data{};
};

using EditorNetworkPacket = v944::EditorNetworkPacket;

}  // namespace v2193

namespace v2225 {

enum class MemoryCategory : std::uint8_t {
    Unknown = 0,
    InvalidSizeUnknown = 1,
    Actor = 2,
    ActorAnimation = 3,
    ActorRendering = 4,
    BlockTickingQueues = 5,
    BiomeStorage = 6,
    Blobs = 7,
    Cereal = 8,
    CircuitSystem = 9,
    Client = 10,
    Commands = 11,
    DBStorage = 12,
    Debug = 13,
    Documentation = 14,
    ECSSystems = 15,
    FMOD = 16,
    Fonts = 17,
    ImGui = 18,
    Input = 19,
    JsonUI = 20,
    JsonUIControlFactoryJson = 21,
    JsonUIControlTree = 22,
    JsonUIControlTreeControlElement = 23,
    JsonUIControlTreePopulateDataBinding = 24,
    JsonUIControlTreePopulateFocus = 25,
    JsonUIControlTreePopulateLayout = 26,
    JsonUIControlTreePopulateOther = 27,
    JsonUIControlTreePopulateSprite = 28,
    JsonUIControlTreePopulateText = 29,
    JsonUIControlTreePopulateTTS = 30,
    JsonUIControlTreeVisibility = 31,
    JsonUICreateUI = 32,
    JsonUIDefs = 33,
    JsonUILayoutManager = 34,
    JsonUILayoutManagerRemoveDependencies = 35,
    JsonUILayoutManagerInitVariable = 36,
    Languages = 37,
    Level = 38,
    LevelStructures = 39,
    LevelChunk = 40,
    LevelChunkGen = 41,
    LevelChunkGenThreadLocal = 42,
    LightVolumeManager = 43,
    Network = 44,
    Marketplace = 45,
    MaterialDragonCompiledDefinition = 46,
    MaterialDragonMaterial = 47,
    MaterialDragonResource = 48,
    MaterialDragonUniformMap = 49,
    MaterialRenderMaterial = 50,
    MaterialRenderMaterialGroup = 51,
    MaterialVariationManager = 52,
    Molang = 53,
    OreUI = 54,
    OreUIClient = 55,
    PersonaPieces = 56,
    PersonaAnimations = 57,
    PersonaCharacters = 58,
    PersonaSkinPacks = 59,
    PersonaRepo = 60,
    Player = 61,
    RenderChunk = 62,
    RenderChunkIndexBuffer = 63,
    RenderChunkVertexBuffer = 64,
    Rendering = 65,
    RenderingBgfxInit = 66,
    RenderingBgfxStartFrame = 67,
    RenderingBlockTessellator = 68,
    RenderingEndFrame = 69,
    RenderingGraphicsTasksInit = 70,
    RenderingLibrary = 71,
    RenderingPolygonOperatorPool = 72,
    RenderingPBRTextureData = 73,
    RenderingRenderRegistry = 74,
    RenderingSetup = 75,
    RenderingVertices = 76,
    RequestLog = 77,
    ResourcePacks = 78,
    Sound = 79,
    SubChunkBiomeData = 80,
    SubChunkBlockData = 81,
    SubChunkLightData = 82,
    Textures = 83,
    WeatherRenderer = 84,
    WorldGenerator = 85,
    Tasks = 86,
    Test = 87,
    TestLoadTestTags = 88,
    Scripting = 89,
    ScriptingRuntime = 90,
    ScriptingContext = 91,
    ScriptingContextBindingsMC = 92,
    ScriptingContextBindingsGT = 93,
    ScriptingContextRun = 94,
    DataDrivenUI = 95,
    DataDrivenUIDefs = 96,
    Gameface = 97,
    GamefaceSystem = 98,
    GamefaceDOM = 99,
    GamefaceCSS = 100,
    GamefaceDisplay = 101,
    GamefaceTempAllocator = 102,
    GamefacePoolAllocator = 103,
    GamefaceDump = 104,
    GamefaceMedia = 105,
    GamefaceJSON = 106,
    GamefaceScriptEngine = 107,
    GamefaceScript = 108,
    GamefaceLayout = 109,
    Executable = 110,
    Count = 111,
};

struct MemoryCategoryCounter {
    v2225::MemoryCategory category{};
    std::uint64_t current_bytes{};
};

using EntityDiagnosticTimingInfo = v2193::EntityDiagnosticTimingInfo;

using SystemCategory = v2168::SystemCategory;

struct ServerboundDiagnosticsPacket {
    static constexpr int Id = 315;
    float avg_fps{};
    float avg_server_sim_tick_time_ms{};
    float avg_client_sim_tick_time_ms{};
    float avg_begin_frame_time_ms{};
    float avg_input_time_ms{};
    float avg_render_time_ms{};
    float avg_end_frame_time_ms{};
    float avg_remainder_time_percent{};
    float avg_unaccounted_time_percent{};
    std::vector<v2225::MemoryCategoryCounter> category_counters{};
    std::vector<v2193::EntityDiagnosticTimingInfo> entity_timings{};
    std::vector<SystemDiagnosticTimingInfo> system_timings{};
    std::optional<std::vector<v2168::SystemCategory>> system_categories{};
    std::vector<ScopeDataSummary> whisker_data{};
};

using EditorNetworkPacket = v944::EditorNetworkPacket;

}  // namespace v2225

namespace detail {

template <int V>
struct MemoryCategory_;

template <int V> requires (V < 844)
struct MemoryCategory_<V> { using type = base::MemoryCategory; };

template <int V> requires (V >= 844 && V < 898)
struct MemoryCategory_<V> { using type = v844::MemoryCategory; };

template <int V> requires (V >= 898 && V < 944)
struct MemoryCategory_<V> { using type = v898::MemoryCategory; };

template <int V> requires (V >= 944 && V < 975)
struct MemoryCategory_<V> { using type = v944::MemoryCategory; };

template <int V> requires (V >= 975 && V < 2168)
struct MemoryCategory_<V> { using type = v975::MemoryCategory; };

template <int V> requires (V >= 2168 && V < 2193)
struct MemoryCategory_<V> { using type = v2168::MemoryCategory; };

template <int V> requires (V >= 2193 && V < 2225)
struct MemoryCategory_<V> { using type = v2193::MemoryCategory; };

template <int V> requires (V >= 2225)
struct MemoryCategory_<V> { using type = v2225::MemoryCategory; };

template <int V>
struct MemoryCategoryCounter_;

template <int V> requires (V >= 924 && V < 944)
struct MemoryCategoryCounter_<V> { using type = v924::MemoryCategoryCounter; };

template <int V> requires (V >= 944 && V < 975)
struct MemoryCategoryCounter_<V> { using type = v944::MemoryCategoryCounter; };

template <int V> requires (V >= 975 && V < 2168)
struct MemoryCategoryCounter_<V> { using type = v975::MemoryCategoryCounter; };

template <int V> requires (V >= 2168 && V < 2193)
struct MemoryCategoryCounter_<V> { using type = v2168::MemoryCategoryCounter; };

template <int V> requires (V >= 2193 && V < 2225)
struct MemoryCategoryCounter_<V> { using type = v2193::MemoryCategoryCounter; };

template <int V> requires (V >= 2225)
struct MemoryCategoryCounter_<V> { using type = v2225::MemoryCategoryCounter; };

template <int V>
struct EntityDiagnosticTimingInfo_;

template <int V> requires (V < 2193)
struct EntityDiagnosticTimingInfo_<V> { using type = base::EntityDiagnosticTimingInfo; };

template <int V> requires (V >= 2193)
struct EntityDiagnosticTimingInfo_<V> { using type = v2193::EntityDiagnosticTimingInfo; };

template <int V>
struct SystemCategory_;

template <int V> requires (V >= 2168)
struct SystemCategory_<V> { using type = v2168::SystemCategory; };

template <int V>
struct ServerboundDiagnosticsPacket_;

template <int V> requires (V < 924)
struct ServerboundDiagnosticsPacket_<V> { using type = base::ServerboundDiagnosticsPacket; };

template <int V> requires (V >= 924 && V < 944)
struct ServerboundDiagnosticsPacket_<V> { using type = v924::ServerboundDiagnosticsPacket; };

template <int V> requires (V >= 944 && V < 975)
struct ServerboundDiagnosticsPacket_<V> { using type = v944::ServerboundDiagnosticsPacket; };

template <int V> requires (V >= 975 && V < 1001)
struct ServerboundDiagnosticsPacket_<V> { using type = v975::ServerboundDiagnosticsPacket; };

template <int V> requires (V >= 1001 && V < 2168)
struct ServerboundDiagnosticsPacket_<V> { using type = v1001::ServerboundDiagnosticsPacket; };

template <int V> requires (V >= 2168 && V < 2193)
struct ServerboundDiagnosticsPacket_<V> { using type = v2168::ServerboundDiagnosticsPacket; };

template <int V> requires (V >= 2193 && V < 2225)
struct ServerboundDiagnosticsPacket_<V> { using type = v2193::ServerboundDiagnosticsPacket; };

template <int V> requires (V >= 2225)
struct ServerboundDiagnosticsPacket_<V> { using type = v2225::ServerboundDiagnosticsPacket; };

template <int V>
struct EditorNetworkPacket_;

template <int V> requires (V < 944)
struct EditorNetworkPacket_<V> { using type = base::EditorNetworkPacket; };

template <int V> requires (V >= 944)
struct EditorNetworkPacket_<V> { using type = v944::EditorNetworkPacket; };

}  // namespace detail

template <int V> using MemoryCategory_ = typename detail::MemoryCategory_<V>::type;
template <int V> using MemoryCategoryCounter_ = typename detail::MemoryCategoryCounter_<V>::type;
template <int V> using EntityDiagnosticTimingInfo_ = typename detail::EntityDiagnosticTimingInfo_<V>::type;
template <int V> using SystemCategory_ = typename detail::SystemCategory_<V>::type;
template <int V> using ServerboundDiagnosticsPacket_ = typename detail::ServerboundDiagnosticsPacket_<V>::type;
template <int V> using EditorNetworkPacket_ = typename detail::EditorNetworkPacket_<V>::type;

template <int V>
struct packet_of<V, 155> { using type = DebugInfoPacket; };

template <int V>
struct packet_of<V, 164> { using type = ClientboundDebugRendererPacket; };

template <int V>
struct packet_of<V, 190> { using type = EditorNetworkPacket_<V>; };

template <int V>
struct packet_of<V, 315> { using type = ServerboundDiagnosticsPacket_<V>; };

namespace detail {

template <>
inline constexpr std::array<base::MemoryCategory, 78> values_v<base::MemoryCategory>{{
    base::MemoryCategory::Unknown,
    base::MemoryCategory::InvalidSizeUnknown,
    base::MemoryCategory::Actor,
    base::MemoryCategory::ActorAnimation,
    base::MemoryCategory::ActorRendering,
    base::MemoryCategory::Balancer,
    base::MemoryCategory::BlockTickingQueues,
    base::MemoryCategory::BiomeStorage,
    base::MemoryCategory::Cereal,
    base::MemoryCategory::CircuitSystem,
    base::MemoryCategory::Client,
    base::MemoryCategory::Commands,
    base::MemoryCategory::DBStorage,
    base::MemoryCategory::Debug,
    base::MemoryCategory::Documentation,
    base::MemoryCategory::ECSSystems,
    base::MemoryCategory::FMOD,
    base::MemoryCategory::Fonts,
    base::MemoryCategory::ImGui,
    base::MemoryCategory::Input,
    base::MemoryCategory::JsonUI,
    base::MemoryCategory::JsonUIControlFactoryJson,
    base::MemoryCategory::JsonUIControlTree,
    base::MemoryCategory::JsonUIControlTreeControlElement,
    base::MemoryCategory::JsonUIControlTreePopulateDataBinding,
    base::MemoryCategory::JsonUIControlTreePopulateFocus,
    base::MemoryCategory::JsonUIControlTreePopulateLayout,
    base::MemoryCategory::JsonUIControlTreePopulateOther,
    base::MemoryCategory::JsonUIControlTreePopulateSprite,
    base::MemoryCategory::JsonUIControlTreePopulateText,
    base::MemoryCategory::JsonUIControlTreePopulateTTS,
    base::MemoryCategory::JsonUIControlTreeVisibility,
    base::MemoryCategory::JsonUICreateUI,
    base::MemoryCategory::JsonUIDefs,
    base::MemoryCategory::JsonUILayoutManager,
    base::MemoryCategory::JsonUILayoutManagerRemoveDependencies,
    base::MemoryCategory::JsonUILayoutManagerInitVariable,
    base::MemoryCategory::Languages,
    base::MemoryCategory::Level,
    base::MemoryCategory::LevelStructures,
    base::MemoryCategory::LevelChunk,
    base::MemoryCategory::LevelChunkGen,
    base::MemoryCategory::LevelChunkGenThreadLocal,
    base::MemoryCategory::Network,
    base::MemoryCategory::MaterialDragonCompiledDefinition,
    base::MemoryCategory::MaterialDragonMaterial,
    base::MemoryCategory::MaterialDragonResource,
    base::MemoryCategory::MaterialDragonUniformMap,
    base::MemoryCategory::MaterialRenderMaterial,
    base::MemoryCategory::MaterialRenderMaterialGroup,
    base::MemoryCategory::MaterialVariationManager,
    base::MemoryCategory::Molang,
    base::MemoryCategory::OreUI,
    base::MemoryCategory::Persona,
    base::MemoryCategory::Player,
    base::MemoryCategory::RenderChunk,
    base::MemoryCategory::RenderChunkIndexBuffer,
    base::MemoryCategory::RenderChunkVertexBuffer,
    base::MemoryCategory::Rendering,
    base::MemoryCategory::RenderingLibrary,
    base::MemoryCategory::ResourcePacks,
    base::MemoryCategory::Sound,
    base::MemoryCategory::SubChunkBiomeData,
    base::MemoryCategory::SubChunkBlockData,
    base::MemoryCategory::SubChunkLightData,
    base::MemoryCategory::Textures,
    base::MemoryCategory::Vr,
    base::MemoryCategory::WeatherRenderer,
    base::MemoryCategory::WorldGenerator,
    base::MemoryCategory::Tasks,
    base::MemoryCategory::Test,
    base::MemoryCategory::Scripting,
    base::MemoryCategory::ScriptingRuntime,
    base::MemoryCategory::ScriptingContext,
    base::MemoryCategory::ScriptingContextBindingsMC,
    base::MemoryCategory::ScriptingContextBindingsGT,
    base::MemoryCategory::ScriptingContextRun,
    base::MemoryCategory::Count,
}};

template <>
inline constexpr std::array<std::string_view, 78> names_v<base::MemoryCategory>{{
    "unknown",
    "invalidsizeunknown",
    "actor",
    "actoranimation",
    "actorrendering",
    "balancer",
    "blocktickingqueues",
    "biomestorage",
    "cereal",
    "circuitsystem",
    "client",
    "commands",
    "dbstorage",
    "debug",
    "documentation",
    "ecssystems",
    "fmod",
    "fonts",
    "imgui",
    "input",
    "jsonui",
    "jsonuicontrolfactoryjson",
    "jsonuicontroltree",
    "jsonuicontroltreecontrolelement",
    "jsonuicontroltreepopulatedatabinding",
    "jsonuicontroltreepopulatefocus",
    "jsonuicontroltreepopulatelayout",
    "jsonuicontroltreepopulateother",
    "jsonuicontroltreepopulatesprite",
    "jsonuicontroltreepopulatetext",
    "jsonuicontroltreepopulatetts",
    "jsonuicontroltreevisibility",
    "jsonuicreateui",
    "jsonuidefs",
    "jsonuilayoutmanager",
    "jsonuilayoutmanagerremovedependencies",
    "jsonuilayoutmanagerinitvariable",
    "languages",
    "level",
    "levelstructures",
    "levelchunk",
    "levelchunkgen",
    "levelchunkgenthreadlocal",
    "network",
    "materialdragoncompileddefinition",
    "materialdragonmaterial",
    "materialdragonresource",
    "materialdragonuniformmap",
    "materialrendermaterial",
    "materialrendermaterialgroup",
    "materialvariationmanager",
    "molang",
    "oreui",
    "persona",
    "player",
    "renderchunk",
    "renderchunkindexbuffer",
    "renderchunkvertexbuffer",
    "rendering",
    "renderinglibrary",
    "resourcepacks",
    "sound",
    "subchunkbiomedata",
    "subchunkblockdata",
    "subchunklightdata",
    "textures",
    "vr",
    "weatherrenderer",
    "worldgenerator",
    "tasks",
    "test",
    "scripting",
    "scriptingruntime",
    "scriptingcontext",
    "scriptingcontextbindingsmc",
    "scriptingcontextbindingsgt",
    "scriptingcontextrun",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<base::MemoryCategory>{"MemoryCategory"};

template <>
inline constexpr std::array<v844::MemoryCategory, 79> values_v<v844::MemoryCategory>{{
    v844::MemoryCategory::Unknown,
    v844::MemoryCategory::InvalidSizeUnknown,
    v844::MemoryCategory::Actor,
    v844::MemoryCategory::ActorAnimation,
    v844::MemoryCategory::ActorRendering,
    v844::MemoryCategory::Balancer,
    v844::MemoryCategory::BlockTickingQueues,
    v844::MemoryCategory::BiomeStorage,
    v844::MemoryCategory::Cereal,
    v844::MemoryCategory::CircuitSystem,
    v844::MemoryCategory::Client,
    v844::MemoryCategory::Commands,
    v844::MemoryCategory::DBStorage,
    v844::MemoryCategory::Debug,
    v844::MemoryCategory::Documentation,
    v844::MemoryCategory::ECSSystems,
    v844::MemoryCategory::FMOD,
    v844::MemoryCategory::Fonts,
    v844::MemoryCategory::ImGui,
    v844::MemoryCategory::Input,
    v844::MemoryCategory::JsonUI,
    v844::MemoryCategory::JsonUIControlFactoryJson,
    v844::MemoryCategory::JsonUIControlTree,
    v844::MemoryCategory::JsonUIControlTreeControlElement,
    v844::MemoryCategory::JsonUIControlTreePopulateDataBinding,
    v844::MemoryCategory::JsonUIControlTreePopulateFocus,
    v844::MemoryCategory::JsonUIControlTreePopulateLayout,
    v844::MemoryCategory::JsonUIControlTreePopulateOther,
    v844::MemoryCategory::JsonUIControlTreePopulateSprite,
    v844::MemoryCategory::JsonUIControlTreePopulateText,
    v844::MemoryCategory::JsonUIControlTreePopulateTTS,
    v844::MemoryCategory::JsonUIControlTreeVisibility,
    v844::MemoryCategory::JsonUICreateUI,
    v844::MemoryCategory::JsonUIDefs,
    v844::MemoryCategory::JsonUILayoutManager,
    v844::MemoryCategory::JsonUILayoutManagerRemoveDependencies,
    v844::MemoryCategory::JsonUILayoutManagerInitVariable,
    v844::MemoryCategory::Languages,
    v844::MemoryCategory::Level,
    v844::MemoryCategory::LevelStructures,
    v844::MemoryCategory::LevelChunk,
    v844::MemoryCategory::LevelChunkGen,
    v844::MemoryCategory::LevelChunkGenThreadLocal,
    v844::MemoryCategory::Network,
    v844::MemoryCategory::Marketplace,
    v844::MemoryCategory::MaterialDragonCompiledDefinition,
    v844::MemoryCategory::MaterialDragonMaterial,
    v844::MemoryCategory::MaterialDragonResource,
    v844::MemoryCategory::MaterialDragonUniformMap,
    v844::MemoryCategory::MaterialRenderMaterial,
    v844::MemoryCategory::MaterialRenderMaterialGroup,
    v844::MemoryCategory::MaterialVariationManager,
    v844::MemoryCategory::Molang,
    v844::MemoryCategory::OreUI,
    v844::MemoryCategory::Persona,
    v844::MemoryCategory::Player,
    v844::MemoryCategory::RenderChunk,
    v844::MemoryCategory::RenderChunkIndexBuffer,
    v844::MemoryCategory::RenderChunkVertexBuffer,
    v844::MemoryCategory::Rendering,
    v844::MemoryCategory::RenderingLibrary,
    v844::MemoryCategory::ResourcePacks,
    v844::MemoryCategory::Sound,
    v844::MemoryCategory::SubChunkBiomeData,
    v844::MemoryCategory::SubChunkBlockData,
    v844::MemoryCategory::SubChunkLightData,
    v844::MemoryCategory::Textures,
    v844::MemoryCategory::Vr,
    v844::MemoryCategory::WeatherRenderer,
    v844::MemoryCategory::WorldGenerator,
    v844::MemoryCategory::Tasks,
    v844::MemoryCategory::Test,
    v844::MemoryCategory::Scripting,
    v844::MemoryCategory::ScriptingRuntime,
    v844::MemoryCategory::ScriptingContext,
    v844::MemoryCategory::ScriptingContextBindingsMC,
    v844::MemoryCategory::ScriptingContextBindingsGT,
    v844::MemoryCategory::ScriptingContextRun,
    v844::MemoryCategory::Count,
}};

template <>
inline constexpr std::array<std::string_view, 79> names_v<v844::MemoryCategory>{{
    "unknown",
    "invalidsizeunknown",
    "actor",
    "actoranimation",
    "actorrendering",
    "balancer",
    "blocktickingqueues",
    "biomestorage",
    "cereal",
    "circuitsystem",
    "client",
    "commands",
    "dbstorage",
    "debug",
    "documentation",
    "ecssystems",
    "fmod",
    "fonts",
    "imgui",
    "input",
    "jsonui",
    "jsonuicontrolfactoryjson",
    "jsonuicontroltree",
    "jsonuicontroltreecontrolelement",
    "jsonuicontroltreepopulatedatabinding",
    "jsonuicontroltreepopulatefocus",
    "jsonuicontroltreepopulatelayout",
    "jsonuicontroltreepopulateother",
    "jsonuicontroltreepopulatesprite",
    "jsonuicontroltreepopulatetext",
    "jsonuicontroltreepopulatetts",
    "jsonuicontroltreevisibility",
    "jsonuicreateui",
    "jsonuidefs",
    "jsonuilayoutmanager",
    "jsonuilayoutmanagerremovedependencies",
    "jsonuilayoutmanagerinitvariable",
    "languages",
    "level",
    "levelstructures",
    "levelchunk",
    "levelchunkgen",
    "levelchunkgenthreadlocal",
    "network",
    "marketplace",
    "materialdragoncompileddefinition",
    "materialdragonmaterial",
    "materialdragonresource",
    "materialdragonuniformmap",
    "materialrendermaterial",
    "materialrendermaterialgroup",
    "materialvariationmanager",
    "molang",
    "oreui",
    "persona",
    "player",
    "renderchunk",
    "renderchunkindexbuffer",
    "renderchunkvertexbuffer",
    "rendering",
    "renderinglibrary",
    "resourcepacks",
    "sound",
    "subchunkbiomedata",
    "subchunkblockdata",
    "subchunklightdata",
    "textures",
    "vr",
    "weatherrenderer",
    "worldgenerator",
    "tasks",
    "test",
    "scripting",
    "scriptingruntime",
    "scriptingcontext",
    "scriptingcontextbindingsmc",
    "scriptingcontextbindingsgt",
    "scriptingcontextrun",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<v844::MemoryCategory>{"MemoryCategory"};

template <>
inline constexpr std::array<v898::MemoryCategory, 82> values_v<v898::MemoryCategory>{{
    v898::MemoryCategory::Unknown,
    v898::MemoryCategory::InvalidSizeUnknown,
    v898::MemoryCategory::Actor,
    v898::MemoryCategory::ActorAnimation,
    v898::MemoryCategory::ActorRendering,
    v898::MemoryCategory::Balancer,
    v898::MemoryCategory::BlockTickingQueues,
    v898::MemoryCategory::BiomeStorage,
    v898::MemoryCategory::Cereal,
    v898::MemoryCategory::CircuitSystem,
    v898::MemoryCategory::Client,
    v898::MemoryCategory::Commands,
    v898::MemoryCategory::DBStorage,
    v898::MemoryCategory::Debug,
    v898::MemoryCategory::Documentation,
    v898::MemoryCategory::ECSSystems,
    v898::MemoryCategory::FMOD,
    v898::MemoryCategory::Fonts,
    v898::MemoryCategory::ImGui,
    v898::MemoryCategory::Input,
    v898::MemoryCategory::JsonUI,
    v898::MemoryCategory::JsonUIControlFactoryJson,
    v898::MemoryCategory::JsonUIControlTree,
    v898::MemoryCategory::JsonUIControlTreeControlElement,
    v898::MemoryCategory::JsonUIControlTreePopulateDataBinding,
    v898::MemoryCategory::JsonUIControlTreePopulateFocus,
    v898::MemoryCategory::JsonUIControlTreePopulateLayout,
    v898::MemoryCategory::JsonUIControlTreePopulateOther,
    v898::MemoryCategory::JsonUIControlTreePopulateSprite,
    v898::MemoryCategory::JsonUIControlTreePopulateText,
    v898::MemoryCategory::JsonUIControlTreePopulateTTS,
    v898::MemoryCategory::JsonUIControlTreeVisibility,
    v898::MemoryCategory::JsonUICreateUI,
    v898::MemoryCategory::JsonUIDefs,
    v898::MemoryCategory::JsonUILayoutManager,
    v898::MemoryCategory::JsonUILayoutManagerRemoveDependencies,
    v898::MemoryCategory::JsonUILayoutManagerInitVariable,
    v898::MemoryCategory::Languages,
    v898::MemoryCategory::Level,
    v898::MemoryCategory::LevelStructures,
    v898::MemoryCategory::LevelChunk,
    v898::MemoryCategory::LevelChunkGen,
    v898::MemoryCategory::LevelChunkGenThreadLocal,
    v898::MemoryCategory::Network,
    v898::MemoryCategory::Marketplace,
    v898::MemoryCategory::MaterialDragonCompiledDefinition,
    v898::MemoryCategory::MaterialDragonMaterial,
    v898::MemoryCategory::MaterialDragonResource,
    v898::MemoryCategory::MaterialDragonUniformMap,
    v898::MemoryCategory::MaterialRenderMaterial,
    v898::MemoryCategory::MaterialRenderMaterialGroup,
    v898::MemoryCategory::MaterialVariationManager,
    v898::MemoryCategory::Molang,
    v898::MemoryCategory::OreUI,
    v898::MemoryCategory::Persona,
    v898::MemoryCategory::Player,
    v898::MemoryCategory::RenderChunk,
    v898::MemoryCategory::RenderChunkIndexBuffer,
    v898::MemoryCategory::RenderChunkVertexBuffer,
    v898::MemoryCategory::Rendering,
    v898::MemoryCategory::RenderingLibrary,
    v898::MemoryCategory::RequestLog,
    v898::MemoryCategory::ResourcePacks,
    v898::MemoryCategory::Sound,
    v898::MemoryCategory::SubChunkBiomeData,
    v898::MemoryCategory::SubChunkBlockData,
    v898::MemoryCategory::SubChunkLightData,
    v898::MemoryCategory::Textures,
    v898::MemoryCategory::Vr,
    v898::MemoryCategory::WeatherRenderer,
    v898::MemoryCategory::WorldGenerator,
    v898::MemoryCategory::Tasks,
    v898::MemoryCategory::Test,
    v898::MemoryCategory::Scripting,
    v898::MemoryCategory::ScriptingRuntime,
    v898::MemoryCategory::ScriptingContext,
    v898::MemoryCategory::ScriptingContextBindingsMC,
    v898::MemoryCategory::ScriptingContextBindingsGT,
    v898::MemoryCategory::ScriptingContextRun,
    v898::MemoryCategory::DataDrivenUI,
    v898::MemoryCategory::DataDrivenUIDefs,
    v898::MemoryCategory::Count,
}};

template <>
inline constexpr std::array<std::string_view, 82> names_v<v898::MemoryCategory>{{
    "unknown",
    "invalidsizeunknown",
    "actor",
    "actoranimation",
    "actorrendering",
    "balancer",
    "blocktickingqueues",
    "biomestorage",
    "cereal",
    "circuitsystem",
    "client",
    "commands",
    "dbstorage",
    "debug",
    "documentation",
    "ecssystems",
    "fmod",
    "fonts",
    "imgui",
    "input",
    "jsonui",
    "jsonuicontrolfactoryjson",
    "jsonuicontroltree",
    "jsonuicontroltreecontrolelement",
    "jsonuicontroltreepopulatedatabinding",
    "jsonuicontroltreepopulatefocus",
    "jsonuicontroltreepopulatelayout",
    "jsonuicontroltreepopulateother",
    "jsonuicontroltreepopulatesprite",
    "jsonuicontroltreepopulatetext",
    "jsonuicontroltreepopulatetts",
    "jsonuicontroltreevisibility",
    "jsonuicreateui",
    "jsonuidefs",
    "jsonuilayoutmanager",
    "jsonuilayoutmanagerremovedependencies",
    "jsonuilayoutmanagerinitvariable",
    "languages",
    "level",
    "levelstructures",
    "levelchunk",
    "levelchunkgen",
    "levelchunkgenthreadlocal",
    "network",
    "marketplace",
    "materialdragoncompileddefinition",
    "materialdragonmaterial",
    "materialdragonresource",
    "materialdragonuniformmap",
    "materialrendermaterial",
    "materialrendermaterialgroup",
    "materialvariationmanager",
    "molang",
    "oreui",
    "persona",
    "player",
    "renderchunk",
    "renderchunkindexbuffer",
    "renderchunkvertexbuffer",
    "rendering",
    "renderinglibrary",
    "requestlog",
    "resourcepacks",
    "sound",
    "subchunkbiomedata",
    "subchunkblockdata",
    "subchunklightdata",
    "textures",
    "vr",
    "weatherrenderer",
    "worldgenerator",
    "tasks",
    "test",
    "scripting",
    "scriptingruntime",
    "scriptingcontext",
    "scriptingcontextbindingsmc",
    "scriptingcontextbindingsgt",
    "scriptingcontextrun",
    "datadrivenui",
    "datadrivenuidefs",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<v898::MemoryCategory>{"MemoryCategory"};

template <>
inline constexpr std::array<v944::MemoryCategory, 93> values_v<v944::MemoryCategory>{{
    v944::MemoryCategory::Unknown,
    v944::MemoryCategory::InvalidSizeUnknown,
    v944::MemoryCategory::Actor,
    v944::MemoryCategory::ActorAnimation,
    v944::MemoryCategory::ActorRendering,
    v944::MemoryCategory::BlockTickingQueues,
    v944::MemoryCategory::BiomeStorage,
    v944::MemoryCategory::Cereal,
    v944::MemoryCategory::CircuitSystem,
    v944::MemoryCategory::Client,
    v944::MemoryCategory::Commands,
    v944::MemoryCategory::DBStorage,
    v944::MemoryCategory::Debug,
    v944::MemoryCategory::Documentation,
    v944::MemoryCategory::ECSSystems,
    v944::MemoryCategory::FMOD,
    v944::MemoryCategory::Fonts,
    v944::MemoryCategory::ImGui,
    v944::MemoryCategory::Input,
    v944::MemoryCategory::JsonUI,
    v944::MemoryCategory::JsonUIControlFactoryJson,
    v944::MemoryCategory::JsonUIControlTree,
    v944::MemoryCategory::JsonUIControlTreeControlElement,
    v944::MemoryCategory::JsonUIControlTreePopulateDataBinding,
    v944::MemoryCategory::JsonUIControlTreePopulateFocus,
    v944::MemoryCategory::JsonUIControlTreePopulateLayout,
    v944::MemoryCategory::JsonUIControlTreePopulateOther,
    v944::MemoryCategory::JsonUIControlTreePopulateSprite,
    v944::MemoryCategory::JsonUIControlTreePopulateText,
    v944::MemoryCategory::JsonUIControlTreePopulateTTS,
    v944::MemoryCategory::JsonUIControlTreeVisibility,
    v944::MemoryCategory::JsonUICreateUI,
    v944::MemoryCategory::JsonUIDefs,
    v944::MemoryCategory::JsonUILayoutManager,
    v944::MemoryCategory::JsonUILayoutManagerRemoveDependencies,
    v944::MemoryCategory::JsonUILayoutManagerInitVariable,
    v944::MemoryCategory::Languages,
    v944::MemoryCategory::Level,
    v944::MemoryCategory::LevelStructures,
    v944::MemoryCategory::LevelChunk,
    v944::MemoryCategory::LevelChunkGen,
    v944::MemoryCategory::LevelChunkGenThreadLocal,
    v944::MemoryCategory::LightVolumeManager,
    v944::MemoryCategory::Network,
    v944::MemoryCategory::Marketplace,
    v944::MemoryCategory::MaterialDragonCompiledDefinition,
    v944::MemoryCategory::MaterialDragonMaterial,
    v944::MemoryCategory::MaterialDragonResource,
    v944::MemoryCategory::MaterialDragonUniformMap,
    v944::MemoryCategory::MaterialRenderMaterial,
    v944::MemoryCategory::MaterialRenderMaterialGroup,
    v944::MemoryCategory::MaterialVariationManager,
    v944::MemoryCategory::Molang,
    v944::MemoryCategory::OreUI,
    v944::MemoryCategory::Persona,
    v944::MemoryCategory::Player,
    v944::MemoryCategory::RenderChunk,
    v944::MemoryCategory::RenderChunkIndexBuffer,
    v944::MemoryCategory::RenderChunkVertexBuffer,
    v944::MemoryCategory::Rendering,
    v944::MemoryCategory::RenderingLibrary,
    v944::MemoryCategory::RequestLog,
    v944::MemoryCategory::ResourcePacks,
    v944::MemoryCategory::Sound,
    v944::MemoryCategory::SubChunkBiomeData,
    v944::MemoryCategory::SubChunkBlockData,
    v944::MemoryCategory::SubChunkLightData,
    v944::MemoryCategory::Textures,
    v944::MemoryCategory::Vr,
    v944::MemoryCategory::WeatherRenderer,
    v944::MemoryCategory::WorldGenerator,
    v944::MemoryCategory::Tasks,
    v944::MemoryCategory::Test,
    v944::MemoryCategory::Scripting,
    v944::MemoryCategory::ScriptingRuntime,
    v944::MemoryCategory::ScriptingContext,
    v944::MemoryCategory::ScriptingContextBindingsMC,
    v944::MemoryCategory::ScriptingContextBindingsGT,
    v944::MemoryCategory::ScriptingContextRun,
    v944::MemoryCategory::DataDrivenUI,
    v944::MemoryCategory::DataDrivenUIDefs,
    v944::MemoryCategory::Gameface,
    v944::MemoryCategory::GamefaceSystem,
    v944::MemoryCategory::GamefaceDOM,
    v944::MemoryCategory::GamefaceCSS,
    v944::MemoryCategory::GamefaceDisplay,
    v944::MemoryCategory::GamefaceTempAllocator,
    v944::MemoryCategory::GamefacePoolAllocator,
    v944::MemoryCategory::GamefaceDump,
    v944::MemoryCategory::GamefaceMedia,
    v944::MemoryCategory::GamefaceJSON,
    v944::MemoryCategory::GamefaceScriptEngine,
    v944::MemoryCategory::Count,
}};

template <>
inline constexpr std::array<std::string_view, 93> names_v<v944::MemoryCategory>{{
    "unknown",
    "invalidsizeunknown",
    "actor",
    "actoranimation",
    "actorrendering",
    "blocktickingqueues",
    "biomestorage",
    "cereal",
    "circuitsystem",
    "client",
    "commands",
    "dbstorage",
    "debug",
    "documentation",
    "ecssystems",
    "fmod",
    "fonts",
    "imgui",
    "input",
    "jsonui",
    "jsonuicontrolfactoryjson",
    "jsonuicontroltree",
    "jsonuicontroltreecontrolelement",
    "jsonuicontroltreepopulatedatabinding",
    "jsonuicontroltreepopulatefocus",
    "jsonuicontroltreepopulatelayout",
    "jsonuicontroltreepopulateother",
    "jsonuicontroltreepopulatesprite",
    "jsonuicontroltreepopulatetext",
    "jsonuicontroltreepopulatetts",
    "jsonuicontroltreevisibility",
    "jsonuicreateui",
    "jsonuidefs",
    "jsonuilayoutmanager",
    "jsonuilayoutmanagerremovedependencies",
    "jsonuilayoutmanagerinitvariable",
    "languages",
    "level",
    "levelstructures",
    "levelchunk",
    "levelchunkgen",
    "levelchunkgenthreadlocal",
    "lightvolumemanager",
    "network",
    "marketplace",
    "materialdragoncompileddefinition",
    "materialdragonmaterial",
    "materialdragonresource",
    "materialdragonuniformmap",
    "materialrendermaterial",
    "materialrendermaterialgroup",
    "materialvariationmanager",
    "molang",
    "oreui",
    "persona",
    "player",
    "renderchunk",
    "renderchunkindexbuffer",
    "renderchunkvertexbuffer",
    "rendering",
    "renderinglibrary",
    "requestlog",
    "resourcepacks",
    "sound",
    "subchunkbiomedata",
    "subchunkblockdata",
    "subchunklightdata",
    "textures",
    "vr",
    "weatherrenderer",
    "worldgenerator",
    "tasks",
    "test",
    "scripting",
    "scriptingruntime",
    "scriptingcontext",
    "scriptingcontextbindingsmc",
    "scriptingcontextbindingsgt",
    "scriptingcontextrun",
    "datadrivenui",
    "datadrivenuidefs",
    "gameface",
    "gamefacesystem",
    "gamefacedom",
    "gamefacecss",
    "gamefacedisplay",
    "gamefacetempallocator",
    "gamefacepoolallocator",
    "gamefacedump",
    "gamefacemedia",
    "gamefacejson",
    "gamefacescriptengine",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<v944::MemoryCategory>{"MemoryCategory"};

template <>
inline constexpr std::array<v975::MemoryCategory, 93> values_v<v975::MemoryCategory>{{
    v975::MemoryCategory::Unknown,
    v975::MemoryCategory::InvalidSizeUnknown,
    v975::MemoryCategory::Actor,
    v975::MemoryCategory::ActorAnimation,
    v975::MemoryCategory::ActorRendering,
    v975::MemoryCategory::BlockTickingQueues,
    v975::MemoryCategory::BiomeStorage,
    v975::MemoryCategory::Cereal,
    v975::MemoryCategory::CircuitSystem,
    v975::MemoryCategory::Client,
    v975::MemoryCategory::Commands,
    v975::MemoryCategory::DBStorage,
    v975::MemoryCategory::Debug,
    v975::MemoryCategory::Documentation,
    v975::MemoryCategory::ECSSystems,
    v975::MemoryCategory::FMOD,
    v975::MemoryCategory::Fonts,
    v975::MemoryCategory::ImGui,
    v975::MemoryCategory::Input,
    v975::MemoryCategory::JsonUI,
    v975::MemoryCategory::JsonUIControlFactoryJson,
    v975::MemoryCategory::JsonUIControlTree,
    v975::MemoryCategory::JsonUIControlTreeControlElement,
    v975::MemoryCategory::JsonUIControlTreePopulateDataBinding,
    v975::MemoryCategory::JsonUIControlTreePopulateFocus,
    v975::MemoryCategory::JsonUIControlTreePopulateLayout,
    v975::MemoryCategory::JsonUIControlTreePopulateOther,
    v975::MemoryCategory::JsonUIControlTreePopulateSprite,
    v975::MemoryCategory::JsonUIControlTreePopulateText,
    v975::MemoryCategory::JsonUIControlTreePopulateTTS,
    v975::MemoryCategory::JsonUIControlTreeVisibility,
    v975::MemoryCategory::JsonUICreateUI,
    v975::MemoryCategory::JsonUIDefs,
    v975::MemoryCategory::JsonUILayoutManager,
    v975::MemoryCategory::JsonUILayoutManagerRemoveDependencies,
    v975::MemoryCategory::JsonUILayoutManagerInitVariable,
    v975::MemoryCategory::Languages,
    v975::MemoryCategory::Level,
    v975::MemoryCategory::LevelStructures,
    v975::MemoryCategory::LevelChunk,
    v975::MemoryCategory::LevelChunkGen,
    v975::MemoryCategory::LevelChunkGenThreadLocal,
    v975::MemoryCategory::LightVolumeManager,
    v975::MemoryCategory::Network,
    v975::MemoryCategory::Marketplace,
    v975::MemoryCategory::MaterialDragonCompiledDefinition,
    v975::MemoryCategory::MaterialDragonMaterial,
    v975::MemoryCategory::MaterialDragonResource,
    v975::MemoryCategory::MaterialDragonUniformMap,
    v975::MemoryCategory::MaterialRenderMaterial,
    v975::MemoryCategory::MaterialRenderMaterialGroup,
    v975::MemoryCategory::MaterialVariationManager,
    v975::MemoryCategory::Molang,
    v975::MemoryCategory::OreUI,
    v975::MemoryCategory::Persona,
    v975::MemoryCategory::Player,
    v975::MemoryCategory::RenderChunk,
    v975::MemoryCategory::RenderChunkIndexBuffer,
    v975::MemoryCategory::RenderChunkVertexBuffer,
    v975::MemoryCategory::Rendering,
    v975::MemoryCategory::RenderingRenderRegistry,
    v975::MemoryCategory::RenderingLibrary,
    v975::MemoryCategory::RequestLog,
    v975::MemoryCategory::ResourcePacks,
    v975::MemoryCategory::Sound,
    v975::MemoryCategory::SubChunkBiomeData,
    v975::MemoryCategory::SubChunkBlockData,
    v975::MemoryCategory::SubChunkLightData,
    v975::MemoryCategory::Textures,
    v975::MemoryCategory::WeatherRenderer,
    v975::MemoryCategory::WorldGenerator,
    v975::MemoryCategory::Tasks,
    v975::MemoryCategory::Test,
    v975::MemoryCategory::Scripting,
    v975::MemoryCategory::ScriptingRuntime,
    v975::MemoryCategory::ScriptingContext,
    v975::MemoryCategory::ScriptingContextBindingsMC,
    v975::MemoryCategory::ScriptingContextBindingsGT,
    v975::MemoryCategory::ScriptingContextRun,
    v975::MemoryCategory::DataDrivenUI,
    v975::MemoryCategory::DataDrivenUIDefs,
    v975::MemoryCategory::Gameface,
    v975::MemoryCategory::GamefaceSystem,
    v975::MemoryCategory::GamefaceDOM,
    v975::MemoryCategory::GamefaceCSS,
    v975::MemoryCategory::GamefaceDisplay,
    v975::MemoryCategory::GamefaceTempAllocator,
    v975::MemoryCategory::GamefacePoolAllocator,
    v975::MemoryCategory::GamefaceDump,
    v975::MemoryCategory::GamefaceMedia,
    v975::MemoryCategory::GamefaceJSON,
    v975::MemoryCategory::GamefaceScriptEngine,
    v975::MemoryCategory::Count,
}};

template <>
inline constexpr std::array<std::string_view, 93> names_v<v975::MemoryCategory>{{
    "unknown",
    "invalidsizeunknown",
    "actor",
    "actoranimation",
    "actorrendering",
    "blocktickingqueues",
    "biomestorage",
    "cereal",
    "circuitsystem",
    "client",
    "commands",
    "dbstorage",
    "debug",
    "documentation",
    "ecssystems",
    "fmod",
    "fonts",
    "imgui",
    "input",
    "jsonui",
    "jsonuicontrolfactoryjson",
    "jsonuicontroltree",
    "jsonuicontroltreecontrolelement",
    "jsonuicontroltreepopulatedatabinding",
    "jsonuicontroltreepopulatefocus",
    "jsonuicontroltreepopulatelayout",
    "jsonuicontroltreepopulateother",
    "jsonuicontroltreepopulatesprite",
    "jsonuicontroltreepopulatetext",
    "jsonuicontroltreepopulatetts",
    "jsonuicontroltreevisibility",
    "jsonuicreateui",
    "jsonuidefs",
    "jsonuilayoutmanager",
    "jsonuilayoutmanagerremovedependencies",
    "jsonuilayoutmanagerinitvariable",
    "languages",
    "level",
    "levelstructures",
    "levelchunk",
    "levelchunkgen",
    "levelchunkgenthreadlocal",
    "lightvolumemanager",
    "network",
    "marketplace",
    "materialdragoncompileddefinition",
    "materialdragonmaterial",
    "materialdragonresource",
    "materialdragonuniformmap",
    "materialrendermaterial",
    "materialrendermaterialgroup",
    "materialvariationmanager",
    "molang",
    "oreui",
    "persona",
    "player",
    "renderchunk",
    "renderchunkindexbuffer",
    "renderchunkvertexbuffer",
    "rendering",
    "renderingrenderregistry",
    "renderinglibrary",
    "requestlog",
    "resourcepacks",
    "sound",
    "subchunkbiomedata",
    "subchunkblockdata",
    "subchunklightdata",
    "textures",
    "weatherrenderer",
    "worldgenerator",
    "tasks",
    "test",
    "scripting",
    "scriptingruntime",
    "scriptingcontext",
    "scriptingcontextbindingsmc",
    "scriptingcontextbindingsgt",
    "scriptingcontextrun",
    "datadrivenui",
    "datadrivenuidefs",
    "gameface",
    "gamefacesystem",
    "gamefacedom",
    "gamefacecss",
    "gamefacedisplay",
    "gamefacetempallocator",
    "gamefacepoolallocator",
    "gamefacedump",
    "gamefacemedia",
    "gamefacejson",
    "gamefacescriptengine",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<v975::MemoryCategory>{"MemoryCategory"};

template <>
inline constexpr std::array<v2168::MemoryCategory, 112> values_v<v2168::MemoryCategory>{{
    v2168::MemoryCategory::Unknown,
    v2168::MemoryCategory::InvalidSizeUnknown,
    v2168::MemoryCategory::Actor,
    v2168::MemoryCategory::ActorAnimation,
    v2168::MemoryCategory::ActorRendering,
    v2168::MemoryCategory::BlockTickingQueues,
    v2168::MemoryCategory::BiomeStorage,
    v2168::MemoryCategory::Blobs,
    v2168::MemoryCategory::Cereal,
    v2168::MemoryCategory::CircuitSystem,
    v2168::MemoryCategory::Client,
    v2168::MemoryCategory::Commands,
    v2168::MemoryCategory::DBStorage,
    v2168::MemoryCategory::Debug,
    v2168::MemoryCategory::Documentation,
    v2168::MemoryCategory::ECSSystems,
    v2168::MemoryCategory::FMOD,
    v2168::MemoryCategory::Fonts,
    v2168::MemoryCategory::ImGui,
    v2168::MemoryCategory::Input,
    v2168::MemoryCategory::JsonUI,
    v2168::MemoryCategory::JsonUIControlFactoryJson,
    v2168::MemoryCategory::JsonUIControlTree,
    v2168::MemoryCategory::JsonUIControlTreeControlElement,
    v2168::MemoryCategory::JsonUIControlTreePopulateDataBinding,
    v2168::MemoryCategory::JsonUIControlTreePopulateFocus,
    v2168::MemoryCategory::JsonUIControlTreePopulateLayout,
    v2168::MemoryCategory::JsonUIControlTreePopulateOther,
    v2168::MemoryCategory::JsonUIControlTreePopulateSprite,
    v2168::MemoryCategory::JsonUIControlTreePopulateText,
    v2168::MemoryCategory::JsonUIControlTreePopulateTTS,
    v2168::MemoryCategory::JsonUIControlTreeVisibility,
    v2168::MemoryCategory::JsonUICreateUI,
    v2168::MemoryCategory::JsonUIDefs,
    v2168::MemoryCategory::JsonUILayoutManager,
    v2168::MemoryCategory::JsonUILayoutManagerRemoveDependencies,
    v2168::MemoryCategory::JsonUILayoutManagerInitVariable,
    v2168::MemoryCategory::Languages,
    v2168::MemoryCategory::Level,
    v2168::MemoryCategory::LevelStructures,
    v2168::MemoryCategory::LevelChunk,
    v2168::MemoryCategory::LevelChunkGen,
    v2168::MemoryCategory::LevelChunkGenThreadLocal,
    v2168::MemoryCategory::LightVolumeManager,
    v2168::MemoryCategory::Network,
    v2168::MemoryCategory::Marketplace,
    v2168::MemoryCategory::MaterialDragonCompiledDefinition,
    v2168::MemoryCategory::MaterialDragonMaterial,
    v2168::MemoryCategory::MaterialDragonResource,
    v2168::MemoryCategory::MaterialDragonUniformMap,
    v2168::MemoryCategory::MaterialRenderMaterial,
    v2168::MemoryCategory::MaterialRenderMaterialGroup,
    v2168::MemoryCategory::MaterialVariationManager,
    v2168::MemoryCategory::Molang,
    v2168::MemoryCategory::OreUI,
    v2168::MemoryCategory::OreUIClient,
    v2168::MemoryCategory::PersonaPieces,
    v2168::MemoryCategory::PersonaAnimations,
    v2168::MemoryCategory::PersonaTextures,
    v2168::MemoryCategory::PersonaCharacters,
    v2168::MemoryCategory::PersonaSkinPacks,
    v2168::MemoryCategory::PersonaRepo,
    v2168::MemoryCategory::Player,
    v2168::MemoryCategory::RenderChunk,
    v2168::MemoryCategory::RenderChunkIndexBuffer,
    v2168::MemoryCategory::RenderChunkVertexBuffer,
    v2168::MemoryCategory::Rendering,
    v2168::MemoryCategory::RenderingBgfxInit,
    v2168::MemoryCategory::RenderingBgfxStartFrame,
    v2168::MemoryCategory::RenderingBlockTessellator,
    v2168::MemoryCategory::RenderingEndFrame,
    v2168::MemoryCategory::RenderingGraphicsTasksInit,
    v2168::MemoryCategory::RenderingLibrary,
    v2168::MemoryCategory::RenderingPolygonOperatorPool,
    v2168::MemoryCategory::RenderingPBRTextureData,
    v2168::MemoryCategory::RenderingRenderRegistry,
    v2168::MemoryCategory::RenderingSetup,
    v2168::MemoryCategory::RenderingVertices,
    v2168::MemoryCategory::RequestLog,
    v2168::MemoryCategory::ResourcePacks,
    v2168::MemoryCategory::Sound,
    v2168::MemoryCategory::SubChunkBiomeData,
    v2168::MemoryCategory::SubChunkBlockData,
    v2168::MemoryCategory::SubChunkLightData,
    v2168::MemoryCategory::Textures,
    v2168::MemoryCategory::WeatherRenderer,
    v2168::MemoryCategory::WorldGenerator,
    v2168::MemoryCategory::Tasks,
    v2168::MemoryCategory::Test,
    v2168::MemoryCategory::TestLoadTestTags,
    v2168::MemoryCategory::Scripting,
    v2168::MemoryCategory::ScriptingRuntime,
    v2168::MemoryCategory::ScriptingContext,
    v2168::MemoryCategory::ScriptingContextBindingsMC,
    v2168::MemoryCategory::ScriptingContextBindingsGT,
    v2168::MemoryCategory::ScriptingContextRun,
    v2168::MemoryCategory::DataDrivenUI,
    v2168::MemoryCategory::DataDrivenUIDefs,
    v2168::MemoryCategory::Gameface,
    v2168::MemoryCategory::GamefaceSystem,
    v2168::MemoryCategory::GamefaceDOM,
    v2168::MemoryCategory::GamefaceCSS,
    v2168::MemoryCategory::GamefaceDisplay,
    v2168::MemoryCategory::GamefaceTempAllocator,
    v2168::MemoryCategory::GamefacePoolAllocator,
    v2168::MemoryCategory::GamefaceDump,
    v2168::MemoryCategory::GamefaceMedia,
    v2168::MemoryCategory::GamefaceJSON,
    v2168::MemoryCategory::GamefaceScriptEngine,
    v2168::MemoryCategory::GamefaceScript,
    v2168::MemoryCategory::GamefaceLayout,
    v2168::MemoryCategory::Count,
}};

template <>
inline constexpr std::array<std::string_view, 112> names_v<v2168::MemoryCategory>{{
    "unknown",
    "invalidsizeunknown",
    "actor",
    "actoranimation",
    "actorrendering",
    "blocktickingqueues",
    "biomestorage",
    "blobs",
    "cereal",
    "circuitsystem",
    "client",
    "commands",
    "dbstorage",
    "debug",
    "documentation",
    "ecssystems",
    "fmod",
    "fonts",
    "imgui",
    "input",
    "jsonui",
    "jsonuicontrolfactoryjson",
    "jsonuicontroltree",
    "jsonuicontroltreecontrolelement",
    "jsonuicontroltreepopulatedatabinding",
    "jsonuicontroltreepopulatefocus",
    "jsonuicontroltreepopulatelayout",
    "jsonuicontroltreepopulateother",
    "jsonuicontroltreepopulatesprite",
    "jsonuicontroltreepopulatetext",
    "jsonuicontroltreepopulatetts",
    "jsonuicontroltreevisibility",
    "jsonuicreateui",
    "jsonuidefs",
    "jsonuilayoutmanager",
    "jsonuilayoutmanagerremovedependencies",
    "jsonuilayoutmanagerinitvariable",
    "languages",
    "level",
    "levelstructures",
    "levelchunk",
    "levelchunkgen",
    "levelchunkgenthreadlocal",
    "lightvolumemanager",
    "network",
    "marketplace",
    "materialdragoncompileddefinition",
    "materialdragonmaterial",
    "materialdragonresource",
    "materialdragonuniformmap",
    "materialrendermaterial",
    "materialrendermaterialgroup",
    "materialvariationmanager",
    "molang",
    "oreui",
    "oreuiclient",
    "personapieces",
    "personaanimations",
    "personatextures",
    "personacharacters",
    "personaskinpacks",
    "personarepo",
    "player",
    "renderchunk",
    "renderchunkindexbuffer",
    "renderchunkvertexbuffer",
    "rendering",
    "renderingbgfxinit",
    "renderingbgfxstartframe",
    "renderingblocktessellator",
    "renderingendframe",
    "renderinggraphicstasksinit",
    "renderinglibrary",
    "renderingpolygonoperatorpool",
    "renderingpbrtexturedata",
    "renderingrenderregistry",
    "renderingsetup",
    "renderingvertices",
    "requestlog",
    "resourcepacks",
    "sound",
    "subchunkbiomedata",
    "subchunkblockdata",
    "subchunklightdata",
    "textures",
    "weatherrenderer",
    "worldgenerator",
    "tasks",
    "test",
    "testloadtesttags",
    "scripting",
    "scriptingruntime",
    "scriptingcontext",
    "scriptingcontextbindingsmc",
    "scriptingcontextbindingsgt",
    "scriptingcontextrun",
    "datadrivenui",
    "datadrivenuidefs",
    "gameface",
    "gamefacesystem",
    "gamefacedom",
    "gamefacecss",
    "gamefacedisplay",
    "gamefacetempallocator",
    "gamefacepoolallocator",
    "gamefacedump",
    "gamefacemedia",
    "gamefacejson",
    "gamefacescriptengine",
    "gamefacescript",
    "gamefacelayout",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<v2168::MemoryCategory>{"MemoryCategory"};

template <>
inline constexpr std::array<v2193::MemoryCategory, 111> values_v<v2193::MemoryCategory>{{
    v2193::MemoryCategory::Unknown,
    v2193::MemoryCategory::InvalidSizeUnknown,
    v2193::MemoryCategory::Actor,
    v2193::MemoryCategory::ActorAnimation,
    v2193::MemoryCategory::ActorRendering,
    v2193::MemoryCategory::BlockTickingQueues,
    v2193::MemoryCategory::BiomeStorage,
    v2193::MemoryCategory::Blobs,
    v2193::MemoryCategory::Cereal,
    v2193::MemoryCategory::CircuitSystem,
    v2193::MemoryCategory::Client,
    v2193::MemoryCategory::Commands,
    v2193::MemoryCategory::DBStorage,
    v2193::MemoryCategory::Debug,
    v2193::MemoryCategory::Documentation,
    v2193::MemoryCategory::ECSSystems,
    v2193::MemoryCategory::FMOD,
    v2193::MemoryCategory::Fonts,
    v2193::MemoryCategory::ImGui,
    v2193::MemoryCategory::Input,
    v2193::MemoryCategory::JsonUI,
    v2193::MemoryCategory::JsonUIControlFactoryJson,
    v2193::MemoryCategory::JsonUIControlTree,
    v2193::MemoryCategory::JsonUIControlTreeControlElement,
    v2193::MemoryCategory::JsonUIControlTreePopulateDataBinding,
    v2193::MemoryCategory::JsonUIControlTreePopulateFocus,
    v2193::MemoryCategory::JsonUIControlTreePopulateLayout,
    v2193::MemoryCategory::JsonUIControlTreePopulateOther,
    v2193::MemoryCategory::JsonUIControlTreePopulateSprite,
    v2193::MemoryCategory::JsonUIControlTreePopulateText,
    v2193::MemoryCategory::JsonUIControlTreePopulateTTS,
    v2193::MemoryCategory::JsonUIControlTreeVisibility,
    v2193::MemoryCategory::JsonUICreateUI,
    v2193::MemoryCategory::JsonUIDefs,
    v2193::MemoryCategory::JsonUILayoutManager,
    v2193::MemoryCategory::JsonUILayoutManagerRemoveDependencies,
    v2193::MemoryCategory::JsonUILayoutManagerInitVariable,
    v2193::MemoryCategory::Languages,
    v2193::MemoryCategory::Level,
    v2193::MemoryCategory::LevelStructures,
    v2193::MemoryCategory::LevelChunk,
    v2193::MemoryCategory::LevelChunkGen,
    v2193::MemoryCategory::LevelChunkGenThreadLocal,
    v2193::MemoryCategory::LightVolumeManager,
    v2193::MemoryCategory::Network,
    v2193::MemoryCategory::Marketplace,
    v2193::MemoryCategory::MaterialDragonCompiledDefinition,
    v2193::MemoryCategory::MaterialDragonMaterial,
    v2193::MemoryCategory::MaterialDragonResource,
    v2193::MemoryCategory::MaterialDragonUniformMap,
    v2193::MemoryCategory::MaterialRenderMaterial,
    v2193::MemoryCategory::MaterialRenderMaterialGroup,
    v2193::MemoryCategory::MaterialVariationManager,
    v2193::MemoryCategory::Molang,
    v2193::MemoryCategory::OreUI,
    v2193::MemoryCategory::OreUIClient,
    v2193::MemoryCategory::PersonaPieces,
    v2193::MemoryCategory::PersonaAnimations,
    v2193::MemoryCategory::PersonaCharacters,
    v2193::MemoryCategory::PersonaSkinPacks,
    v2193::MemoryCategory::PersonaRepo,
    v2193::MemoryCategory::Player,
    v2193::MemoryCategory::RenderChunk,
    v2193::MemoryCategory::RenderChunkIndexBuffer,
    v2193::MemoryCategory::RenderChunkVertexBuffer,
    v2193::MemoryCategory::Rendering,
    v2193::MemoryCategory::RenderingBgfxInit,
    v2193::MemoryCategory::RenderingBgfxStartFrame,
    v2193::MemoryCategory::RenderingBlockTessellator,
    v2193::MemoryCategory::RenderingEndFrame,
    v2193::MemoryCategory::RenderingGraphicsTasksInit,
    v2193::MemoryCategory::RenderingLibrary,
    v2193::MemoryCategory::RenderingPolygonOperatorPool,
    v2193::MemoryCategory::RenderingPBRTextureData,
    v2193::MemoryCategory::RenderingRenderRegistry,
    v2193::MemoryCategory::RenderingSetup,
    v2193::MemoryCategory::RenderingVertices,
    v2193::MemoryCategory::RequestLog,
    v2193::MemoryCategory::ResourcePacks,
    v2193::MemoryCategory::Sound,
    v2193::MemoryCategory::SubChunkBiomeData,
    v2193::MemoryCategory::SubChunkBlockData,
    v2193::MemoryCategory::SubChunkLightData,
    v2193::MemoryCategory::Textures,
    v2193::MemoryCategory::WeatherRenderer,
    v2193::MemoryCategory::WorldGenerator,
    v2193::MemoryCategory::Tasks,
    v2193::MemoryCategory::Test,
    v2193::MemoryCategory::TestLoadTestTags,
    v2193::MemoryCategory::Scripting,
    v2193::MemoryCategory::ScriptingRuntime,
    v2193::MemoryCategory::ScriptingContext,
    v2193::MemoryCategory::ScriptingContextBindingsMC,
    v2193::MemoryCategory::ScriptingContextBindingsGT,
    v2193::MemoryCategory::ScriptingContextRun,
    v2193::MemoryCategory::DataDrivenUI,
    v2193::MemoryCategory::DataDrivenUIDefs,
    v2193::MemoryCategory::Gameface,
    v2193::MemoryCategory::GamefaceSystem,
    v2193::MemoryCategory::GamefaceDOM,
    v2193::MemoryCategory::GamefaceCSS,
    v2193::MemoryCategory::GamefaceDisplay,
    v2193::MemoryCategory::GamefaceTempAllocator,
    v2193::MemoryCategory::GamefacePoolAllocator,
    v2193::MemoryCategory::GamefaceDump,
    v2193::MemoryCategory::GamefaceMedia,
    v2193::MemoryCategory::GamefaceJSON,
    v2193::MemoryCategory::GamefaceScriptEngine,
    v2193::MemoryCategory::GamefaceScript,
    v2193::MemoryCategory::GamefaceLayout,
    v2193::MemoryCategory::Count,
}};

template <>
inline constexpr std::array<std::string_view, 111> names_v<v2193::MemoryCategory>{{
    "unknown",
    "invalidsizeunknown",
    "actor",
    "actoranimation",
    "actorrendering",
    "blocktickingqueues",
    "biomestorage",
    "blobs",
    "cereal",
    "circuitsystem",
    "client",
    "commands",
    "dbstorage",
    "debug",
    "documentation",
    "ecssystems",
    "fmod",
    "fonts",
    "imgui",
    "input",
    "jsonui",
    "jsonuicontrolfactoryjson",
    "jsonuicontroltree",
    "jsonuicontroltreecontrolelement",
    "jsonuicontroltreepopulatedatabinding",
    "jsonuicontroltreepopulatefocus",
    "jsonuicontroltreepopulatelayout",
    "jsonuicontroltreepopulateother",
    "jsonuicontroltreepopulatesprite",
    "jsonuicontroltreepopulatetext",
    "jsonuicontroltreepopulatetts",
    "jsonuicontroltreevisibility",
    "jsonuicreateui",
    "jsonuidefs",
    "jsonuilayoutmanager",
    "jsonuilayoutmanagerremovedependencies",
    "jsonuilayoutmanagerinitvariable",
    "languages",
    "level",
    "levelstructures",
    "levelchunk",
    "levelchunkgen",
    "levelchunkgenthreadlocal",
    "lightvolumemanager",
    "network",
    "marketplace",
    "materialdragoncompileddefinition",
    "materialdragonmaterial",
    "materialdragonresource",
    "materialdragonuniformmap",
    "materialrendermaterial",
    "materialrendermaterialgroup",
    "materialvariationmanager",
    "molang",
    "oreui",
    "oreuiclient",
    "personapieces",
    "personaanimations",
    "personacharacters",
    "personaskinpacks",
    "personarepo",
    "player",
    "renderchunk",
    "renderchunkindexbuffer",
    "renderchunkvertexbuffer",
    "rendering",
    "renderingbgfxinit",
    "renderingbgfxstartframe",
    "renderingblocktessellator",
    "renderingendframe",
    "renderinggraphicstasksinit",
    "renderinglibrary",
    "renderingpolygonoperatorpool",
    "renderingpbrtexturedata",
    "renderingrenderregistry",
    "renderingsetup",
    "renderingvertices",
    "requestlog",
    "resourcepacks",
    "sound",
    "subchunkbiomedata",
    "subchunkblockdata",
    "subchunklightdata",
    "textures",
    "weatherrenderer",
    "worldgenerator",
    "tasks",
    "test",
    "testloadtesttags",
    "scripting",
    "scriptingruntime",
    "scriptingcontext",
    "scriptingcontextbindingsmc",
    "scriptingcontextbindingsgt",
    "scriptingcontextrun",
    "datadrivenui",
    "datadrivenuidefs",
    "gameface",
    "gamefacesystem",
    "gamefacedom",
    "gamefacecss",
    "gamefacedisplay",
    "gamefacetempallocator",
    "gamefacepoolallocator",
    "gamefacedump",
    "gamefacemedia",
    "gamefacejson",
    "gamefacescriptengine",
    "gamefacescript",
    "gamefacelayout",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<v2193::MemoryCategory>{"MemoryCategory"};

template <>
inline constexpr std::array<v2225::MemoryCategory, 112> values_v<v2225::MemoryCategory>{{
    v2225::MemoryCategory::Unknown,
    v2225::MemoryCategory::InvalidSizeUnknown,
    v2225::MemoryCategory::Actor,
    v2225::MemoryCategory::ActorAnimation,
    v2225::MemoryCategory::ActorRendering,
    v2225::MemoryCategory::BlockTickingQueues,
    v2225::MemoryCategory::BiomeStorage,
    v2225::MemoryCategory::Blobs,
    v2225::MemoryCategory::Cereal,
    v2225::MemoryCategory::CircuitSystem,
    v2225::MemoryCategory::Client,
    v2225::MemoryCategory::Commands,
    v2225::MemoryCategory::DBStorage,
    v2225::MemoryCategory::Debug,
    v2225::MemoryCategory::Documentation,
    v2225::MemoryCategory::ECSSystems,
    v2225::MemoryCategory::FMOD,
    v2225::MemoryCategory::Fonts,
    v2225::MemoryCategory::ImGui,
    v2225::MemoryCategory::Input,
    v2225::MemoryCategory::JsonUI,
    v2225::MemoryCategory::JsonUIControlFactoryJson,
    v2225::MemoryCategory::JsonUIControlTree,
    v2225::MemoryCategory::JsonUIControlTreeControlElement,
    v2225::MemoryCategory::JsonUIControlTreePopulateDataBinding,
    v2225::MemoryCategory::JsonUIControlTreePopulateFocus,
    v2225::MemoryCategory::JsonUIControlTreePopulateLayout,
    v2225::MemoryCategory::JsonUIControlTreePopulateOther,
    v2225::MemoryCategory::JsonUIControlTreePopulateSprite,
    v2225::MemoryCategory::JsonUIControlTreePopulateText,
    v2225::MemoryCategory::JsonUIControlTreePopulateTTS,
    v2225::MemoryCategory::JsonUIControlTreeVisibility,
    v2225::MemoryCategory::JsonUICreateUI,
    v2225::MemoryCategory::JsonUIDefs,
    v2225::MemoryCategory::JsonUILayoutManager,
    v2225::MemoryCategory::JsonUILayoutManagerRemoveDependencies,
    v2225::MemoryCategory::JsonUILayoutManagerInitVariable,
    v2225::MemoryCategory::Languages,
    v2225::MemoryCategory::Level,
    v2225::MemoryCategory::LevelStructures,
    v2225::MemoryCategory::LevelChunk,
    v2225::MemoryCategory::LevelChunkGen,
    v2225::MemoryCategory::LevelChunkGenThreadLocal,
    v2225::MemoryCategory::LightVolumeManager,
    v2225::MemoryCategory::Network,
    v2225::MemoryCategory::Marketplace,
    v2225::MemoryCategory::MaterialDragonCompiledDefinition,
    v2225::MemoryCategory::MaterialDragonMaterial,
    v2225::MemoryCategory::MaterialDragonResource,
    v2225::MemoryCategory::MaterialDragonUniformMap,
    v2225::MemoryCategory::MaterialRenderMaterial,
    v2225::MemoryCategory::MaterialRenderMaterialGroup,
    v2225::MemoryCategory::MaterialVariationManager,
    v2225::MemoryCategory::Molang,
    v2225::MemoryCategory::OreUI,
    v2225::MemoryCategory::OreUIClient,
    v2225::MemoryCategory::PersonaPieces,
    v2225::MemoryCategory::PersonaAnimations,
    v2225::MemoryCategory::PersonaCharacters,
    v2225::MemoryCategory::PersonaSkinPacks,
    v2225::MemoryCategory::PersonaRepo,
    v2225::MemoryCategory::Player,
    v2225::MemoryCategory::RenderChunk,
    v2225::MemoryCategory::RenderChunkIndexBuffer,
    v2225::MemoryCategory::RenderChunkVertexBuffer,
    v2225::MemoryCategory::Rendering,
    v2225::MemoryCategory::RenderingBgfxInit,
    v2225::MemoryCategory::RenderingBgfxStartFrame,
    v2225::MemoryCategory::RenderingBlockTessellator,
    v2225::MemoryCategory::RenderingEndFrame,
    v2225::MemoryCategory::RenderingGraphicsTasksInit,
    v2225::MemoryCategory::RenderingLibrary,
    v2225::MemoryCategory::RenderingPolygonOperatorPool,
    v2225::MemoryCategory::RenderingPBRTextureData,
    v2225::MemoryCategory::RenderingRenderRegistry,
    v2225::MemoryCategory::RenderingSetup,
    v2225::MemoryCategory::RenderingVertices,
    v2225::MemoryCategory::RequestLog,
    v2225::MemoryCategory::ResourcePacks,
    v2225::MemoryCategory::Sound,
    v2225::MemoryCategory::SubChunkBiomeData,
    v2225::MemoryCategory::SubChunkBlockData,
    v2225::MemoryCategory::SubChunkLightData,
    v2225::MemoryCategory::Textures,
    v2225::MemoryCategory::WeatherRenderer,
    v2225::MemoryCategory::WorldGenerator,
    v2225::MemoryCategory::Tasks,
    v2225::MemoryCategory::Test,
    v2225::MemoryCategory::TestLoadTestTags,
    v2225::MemoryCategory::Scripting,
    v2225::MemoryCategory::ScriptingRuntime,
    v2225::MemoryCategory::ScriptingContext,
    v2225::MemoryCategory::ScriptingContextBindingsMC,
    v2225::MemoryCategory::ScriptingContextBindingsGT,
    v2225::MemoryCategory::ScriptingContextRun,
    v2225::MemoryCategory::DataDrivenUI,
    v2225::MemoryCategory::DataDrivenUIDefs,
    v2225::MemoryCategory::Gameface,
    v2225::MemoryCategory::GamefaceSystem,
    v2225::MemoryCategory::GamefaceDOM,
    v2225::MemoryCategory::GamefaceCSS,
    v2225::MemoryCategory::GamefaceDisplay,
    v2225::MemoryCategory::GamefaceTempAllocator,
    v2225::MemoryCategory::GamefacePoolAllocator,
    v2225::MemoryCategory::GamefaceDump,
    v2225::MemoryCategory::GamefaceMedia,
    v2225::MemoryCategory::GamefaceJSON,
    v2225::MemoryCategory::GamefaceScriptEngine,
    v2225::MemoryCategory::GamefaceScript,
    v2225::MemoryCategory::GamefaceLayout,
    v2225::MemoryCategory::Executable,
    v2225::MemoryCategory::Count,
}};

template <>
inline constexpr std::array<std::string_view, 112> names_v<v2225::MemoryCategory>{{
    "unknown",
    "invalidsizeunknown",
    "actor",
    "actoranimation",
    "actorrendering",
    "blocktickingqueues",
    "biomestorage",
    "blobs",
    "cereal",
    "circuitsystem",
    "client",
    "commands",
    "dbstorage",
    "debug",
    "documentation",
    "ecssystems",
    "fmod",
    "fonts",
    "imgui",
    "input",
    "jsonui",
    "jsonuicontrolfactoryjson",
    "jsonuicontroltree",
    "jsonuicontroltreecontrolelement",
    "jsonuicontroltreepopulatedatabinding",
    "jsonuicontroltreepopulatefocus",
    "jsonuicontroltreepopulatelayout",
    "jsonuicontroltreepopulateother",
    "jsonuicontroltreepopulatesprite",
    "jsonuicontroltreepopulatetext",
    "jsonuicontroltreepopulatetts",
    "jsonuicontroltreevisibility",
    "jsonuicreateui",
    "jsonuidefs",
    "jsonuilayoutmanager",
    "jsonuilayoutmanagerremovedependencies",
    "jsonuilayoutmanagerinitvariable",
    "languages",
    "level",
    "levelstructures",
    "levelchunk",
    "levelchunkgen",
    "levelchunkgenthreadlocal",
    "lightvolumemanager",
    "network",
    "marketplace",
    "materialdragoncompileddefinition",
    "materialdragonmaterial",
    "materialdragonresource",
    "materialdragonuniformmap",
    "materialrendermaterial",
    "materialrendermaterialgroup",
    "materialvariationmanager",
    "molang",
    "oreui",
    "oreuiclient",
    "personapieces",
    "personaanimations",
    "personacharacters",
    "personaskinpacks",
    "personarepo",
    "player",
    "renderchunk",
    "renderchunkindexbuffer",
    "renderchunkvertexbuffer",
    "rendering",
    "renderingbgfxinit",
    "renderingbgfxstartframe",
    "renderingblocktessellator",
    "renderingendframe",
    "renderinggraphicstasksinit",
    "renderinglibrary",
    "renderingpolygonoperatorpool",
    "renderingpbrtexturedata",
    "renderingrenderregistry",
    "renderingsetup",
    "renderingvertices",
    "requestlog",
    "resourcepacks",
    "sound",
    "subchunkbiomedata",
    "subchunkblockdata",
    "subchunklightdata",
    "textures",
    "weatherrenderer",
    "worldgenerator",
    "tasks",
    "test",
    "testloadtesttags",
    "scripting",
    "scriptingruntime",
    "scriptingcontext",
    "scriptingcontextbindingsmc",
    "scriptingcontextbindingsgt",
    "scriptingcontextrun",
    "datadrivenui",
    "datadrivenuidefs",
    "gameface",
    "gamefacesystem",
    "gamefacedom",
    "gamefacecss",
    "gamefacedisplay",
    "gamefacetempallocator",
    "gamefacepoolallocator",
    "gamefacedump",
    "gamefacemedia",
    "gamefacejson",
    "gamefacescriptengine",
    "gamefacescript",
    "gamefacelayout",
    "executable",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<v2225::MemoryCategory>{"MemoryCategory"};

template <>
inline constexpr std::array<ClientboundDebugRendererPacket::PayloadType, 3> values_v<ClientboundDebugRendererPacket::PayloadType>{{
    ClientboundDebugRendererPacket::PayloadType::Invalid,
    ClientboundDebugRendererPacket::PayloadType::ClearDebugMarkers,
    ClientboundDebugRendererPacket::PayloadType::AddDebugMarkerCube,
}};

template <>
inline constexpr std::array<std::string_view, 3> names_v<ClientboundDebugRendererPacket::PayloadType>{{
    "invalid",
    "cleardebugmarkers",
    "adddebugmarkercube",
}};

template <>
inline constexpr std::string_view type_name_v<ClientboundDebugRendererPacket::PayloadType>{"ClientboundDebugRendererPacket::PayloadType"};

}  // namespace detail

namespace detail {

template <>
inline constexpr bool is_reflected_struct_v<v924::MemoryCategoryCounter> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::MemoryCategoryCounter>{"MemoryCategoryCounter"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v924::MemoryCategoryCounter>{{
    "category",
    "current_bytes",
}};

template <>
struct field_accessor<v924::MemoryCategoryCounter> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.category;
        }
        else {
            return value.current_bytes;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::MemoryCategoryCounter> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::MemoryCategoryCounter>{"MemoryCategoryCounter"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v944::MemoryCategoryCounter>{{
    "category",
    "current_bytes",
}};

template <>
struct field_accessor<v944::MemoryCategoryCounter> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.category;
        }
        else {
            return value.current_bytes;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v975::MemoryCategoryCounter> = true;

template <>
inline constexpr std::string_view struct_name_v<v975::MemoryCategoryCounter>{"MemoryCategoryCounter"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v975::MemoryCategoryCounter>{{
    "category",
    "current_bytes",
}};

template <>
struct field_accessor<v975::MemoryCategoryCounter> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.category;
        }
        else {
            return value.current_bytes;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::MemoryCategoryCounter> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::MemoryCategoryCounter>{"MemoryCategoryCounter"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2168::MemoryCategoryCounter>{{
    "category",
    "current_bytes",
}};

template <>
struct field_accessor<v2168::MemoryCategoryCounter> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.category;
        }
        else {
            return value.current_bytes;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2193::MemoryCategoryCounter> = true;

template <>
inline constexpr std::string_view struct_name_v<v2193::MemoryCategoryCounter>{"MemoryCategoryCounter"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2193::MemoryCategoryCounter>{{
    "category",
    "current_bytes",
}};

template <>
struct field_accessor<v2193::MemoryCategoryCounter> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.category;
        }
        else {
            return value.current_bytes;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::MemoryCategoryCounter> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::MemoryCategoryCounter>{"MemoryCategoryCounter"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2225::MemoryCategoryCounter>{{
    "category",
    "current_bytes",
}};

template <>
struct field_accessor<v2225::MemoryCategoryCounter> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.category;
        }
        else {
            return value.current_bytes;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::EntityDiagnosticTimingInfo> = true;

template <>
inline constexpr std::string_view struct_name_v<base::EntityDiagnosticTimingInfo>{"EntityDiagnosticTimingInfo"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<base::EntityDiagnosticTimingInfo>{{
    "display_name",
    "entity",
    "time_in_ns",
    "percent_of_total",
}};

template <>
struct field_accessor<base::EntityDiagnosticTimingInfo> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.display_name;
        }
        else if constexpr (I == 1) {
            return value.entity;
        }
        else if constexpr (I == 2) {
            return value.time_in_ns;
        }
        else {
            return value.percent_of_total;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2193::EntityDiagnosticTimingInfo> = true;

template <>
inline constexpr std::string_view struct_name_v<v2193::EntityDiagnosticTimingInfo>{"EntityDiagnosticTimingInfo"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<v2193::EntityDiagnosticTimingInfo>{{
    "display_name",
    "entity",
    "time_in_ns",
    "percent_of_total",
    "position",
    "dimension",
}};

template <>
struct field_accessor<v2193::EntityDiagnosticTimingInfo> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.display_name;
        }
        else if constexpr (I == 1) {
            return value.entity;
        }
        else if constexpr (I == 2) {
            return value.time_in_ns;
        }
        else if constexpr (I == 3) {
            return value.percent_of_total;
        }
        else if constexpr (I == 4) {
            return value.position;
        }
        else {
            return value.dimension;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<SystemDiagnosticTimingInfo> = true;

template <>
inline constexpr std::string_view struct_name_v<SystemDiagnosticTimingInfo>{"SystemDiagnosticTimingInfo"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<SystemDiagnosticTimingInfo>{{
    "display_name",
    "system_index",
    "time_in_ns",
    "percent_of_total",
}};

template <>
struct field_accessor<SystemDiagnosticTimingInfo> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.display_name;
        }
        else if constexpr (I == 1) {
            return value.system_index;
        }
        else if constexpr (I == 2) {
            return value.time_in_ns;
        }
        else {
            return value.percent_of_total;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::SystemCategory> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::SystemCategory>{"SystemCategory"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2168::SystemCategory>{{
    "category_name",
    "system_index",
}};

template <>
struct field_accessor<v2168::SystemCategory> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.category_name;
        }
        else {
            return value.system_index;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<ScopeDataSummary> = true;

template <>
inline constexpr std::string_view struct_name_v<ScopeDataSummary>{"ScopeDataSummary"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<ScopeDataSummary>{{
    "label",
    "indentation",
    "total_high_cost_ns",
    "total_mid_cost_ns",
    "total_low_cost_ns",
}};

template <>
struct field_accessor<ScopeDataSummary> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.label;
        }
        else if constexpr (I == 1) {
            return value.indentation;
        }
        else if constexpr (I == 2) {
            return value.total_high_cost_ns;
        }
        else if constexpr (I == 3) {
            return value.total_mid_cost_ns;
        }
        else {
            return value.total_low_cost_ns;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::ServerboundDiagnosticsPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ServerboundDiagnosticsPacket>{"ServerboundDiagnosticsPacket"};

template <>
inline constexpr std::array<std::string_view, 9> field_names_v<base::ServerboundDiagnosticsPacket>{{
    "avg_fps",
    "avg_server_sim_tick_time_ms",
    "avg_client_sim_tick_time_ms",
    "avg_begin_frame_time_ms",
    "avg_input_time_ms",
    "avg_render_time_ms",
    "avg_end_frame_time_ms",
    "avg_remainder_time_percent",
    "avg_unaccounted_time_percent",
}};

template <>
struct field_accessor<base::ServerboundDiagnosticsPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.avg_fps;
        }
        else if constexpr (I == 1) {
            return value.avg_server_sim_tick_time_ms;
        }
        else if constexpr (I == 2) {
            return value.avg_client_sim_tick_time_ms;
        }
        else if constexpr (I == 3) {
            return value.avg_begin_frame_time_ms;
        }
        else if constexpr (I == 4) {
            return value.avg_input_time_ms;
        }
        else if constexpr (I == 5) {
            return value.avg_render_time_ms;
        }
        else if constexpr (I == 6) {
            return value.avg_end_frame_time_ms;
        }
        else if constexpr (I == 7) {
            return value.avg_remainder_time_percent;
        }
        else {
            return value.avg_unaccounted_time_percent;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::ServerboundDiagnosticsPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::ServerboundDiagnosticsPacket>{"ServerboundDiagnosticsPacket"};

template <>
inline constexpr std::array<std::string_view, 10> field_names_v<v924::ServerboundDiagnosticsPacket>{{
    "avg_fps",
    "avg_server_sim_tick_time_ms",
    "avg_client_sim_tick_time_ms",
    "avg_begin_frame_time_ms",
    "avg_input_time_ms",
    "avg_render_time_ms",
    "avg_end_frame_time_ms",
    "avg_remainder_time_percent",
    "avg_unaccounted_time_percent",
    "category_counters",
}};

template <>
struct field_accessor<v924::ServerboundDiagnosticsPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.avg_fps;
        }
        else if constexpr (I == 1) {
            return value.avg_server_sim_tick_time_ms;
        }
        else if constexpr (I == 2) {
            return value.avg_client_sim_tick_time_ms;
        }
        else if constexpr (I == 3) {
            return value.avg_begin_frame_time_ms;
        }
        else if constexpr (I == 4) {
            return value.avg_input_time_ms;
        }
        else if constexpr (I == 5) {
            return value.avg_render_time_ms;
        }
        else if constexpr (I == 6) {
            return value.avg_end_frame_time_ms;
        }
        else if constexpr (I == 7) {
            return value.avg_remainder_time_percent;
        }
        else if constexpr (I == 8) {
            return value.avg_unaccounted_time_percent;
        }
        else {
            return value.category_counters;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::ServerboundDiagnosticsPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::ServerboundDiagnosticsPacket>{"ServerboundDiagnosticsPacket"};

template <>
inline constexpr std::array<std::string_view, 10> field_names_v<v944::ServerboundDiagnosticsPacket>{{
    "avg_fps",
    "avg_server_sim_tick_time_ms",
    "avg_client_sim_tick_time_ms",
    "avg_begin_frame_time_ms",
    "avg_input_time_ms",
    "avg_render_time_ms",
    "avg_end_frame_time_ms",
    "avg_remainder_time_percent",
    "avg_unaccounted_time_percent",
    "category_counters",
}};

template <>
struct field_accessor<v944::ServerboundDiagnosticsPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.avg_fps;
        }
        else if constexpr (I == 1) {
            return value.avg_server_sim_tick_time_ms;
        }
        else if constexpr (I == 2) {
            return value.avg_client_sim_tick_time_ms;
        }
        else if constexpr (I == 3) {
            return value.avg_begin_frame_time_ms;
        }
        else if constexpr (I == 4) {
            return value.avg_input_time_ms;
        }
        else if constexpr (I == 5) {
            return value.avg_render_time_ms;
        }
        else if constexpr (I == 6) {
            return value.avg_end_frame_time_ms;
        }
        else if constexpr (I == 7) {
            return value.avg_remainder_time_percent;
        }
        else if constexpr (I == 8) {
            return value.avg_unaccounted_time_percent;
        }
        else {
            return value.category_counters;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v975::ServerboundDiagnosticsPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v975::ServerboundDiagnosticsPacket>{"ServerboundDiagnosticsPacket"};

template <>
inline constexpr std::array<std::string_view, 12> field_names_v<v975::ServerboundDiagnosticsPacket>{{
    "avg_fps",
    "avg_server_sim_tick_time_ms",
    "avg_client_sim_tick_time_ms",
    "avg_begin_frame_time_ms",
    "avg_input_time_ms",
    "avg_render_time_ms",
    "avg_end_frame_time_ms",
    "avg_remainder_time_percent",
    "avg_unaccounted_time_percent",
    "category_counters",
    "entity_timings",
    "system_timings",
}};

template <>
struct field_accessor<v975::ServerboundDiagnosticsPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.avg_fps;
        }
        else if constexpr (I == 1) {
            return value.avg_server_sim_tick_time_ms;
        }
        else if constexpr (I == 2) {
            return value.avg_client_sim_tick_time_ms;
        }
        else if constexpr (I == 3) {
            return value.avg_begin_frame_time_ms;
        }
        else if constexpr (I == 4) {
            return value.avg_input_time_ms;
        }
        else if constexpr (I == 5) {
            return value.avg_render_time_ms;
        }
        else if constexpr (I == 6) {
            return value.avg_end_frame_time_ms;
        }
        else if constexpr (I == 7) {
            return value.avg_remainder_time_percent;
        }
        else if constexpr (I == 8) {
            return value.avg_unaccounted_time_percent;
        }
        else if constexpr (I == 9) {
            return value.category_counters;
        }
        else if constexpr (I == 10) {
            return value.entity_timings;
        }
        else {
            return value.system_timings;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::ServerboundDiagnosticsPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::ServerboundDiagnosticsPacket>{"ServerboundDiagnosticsPacket"};

template <>
inline constexpr std::array<std::string_view, 13> field_names_v<v1001::ServerboundDiagnosticsPacket>{{
    "avg_fps",
    "avg_server_sim_tick_time_ms",
    "avg_client_sim_tick_time_ms",
    "avg_begin_frame_time_ms",
    "avg_input_time_ms",
    "avg_render_time_ms",
    "avg_end_frame_time_ms",
    "avg_remainder_time_percent",
    "avg_unaccounted_time_percent",
    "category_counters",
    "entity_timings",
    "system_timings",
    "whisker_data",
}};

template <>
struct field_accessor<v1001::ServerboundDiagnosticsPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.avg_fps;
        }
        else if constexpr (I == 1) {
            return value.avg_server_sim_tick_time_ms;
        }
        else if constexpr (I == 2) {
            return value.avg_client_sim_tick_time_ms;
        }
        else if constexpr (I == 3) {
            return value.avg_begin_frame_time_ms;
        }
        else if constexpr (I == 4) {
            return value.avg_input_time_ms;
        }
        else if constexpr (I == 5) {
            return value.avg_render_time_ms;
        }
        else if constexpr (I == 6) {
            return value.avg_end_frame_time_ms;
        }
        else if constexpr (I == 7) {
            return value.avg_remainder_time_percent;
        }
        else if constexpr (I == 8) {
            return value.avg_unaccounted_time_percent;
        }
        else if constexpr (I == 9) {
            return value.category_counters;
        }
        else if constexpr (I == 10) {
            return value.entity_timings;
        }
        else if constexpr (I == 11) {
            return value.system_timings;
        }
        else {
            return value.whisker_data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ServerboundDiagnosticsPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ServerboundDiagnosticsPacket>{"ServerboundDiagnosticsPacket"};

template <>
inline constexpr std::array<std::string_view, 14> field_names_v<v2168::ServerboundDiagnosticsPacket>{{
    "avg_fps",
    "avg_server_sim_tick_time_ms",
    "avg_client_sim_tick_time_ms",
    "avg_begin_frame_time_ms",
    "avg_input_time_ms",
    "avg_render_time_ms",
    "avg_end_frame_time_ms",
    "avg_remainder_time_percent",
    "avg_unaccounted_time_percent",
    "category_counters",
    "entity_timings",
    "system_timings",
    "system_categories",
    "whisker_data",
}};

template <>
struct field_accessor<v2168::ServerboundDiagnosticsPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.avg_fps;
        }
        else if constexpr (I == 1) {
            return value.avg_server_sim_tick_time_ms;
        }
        else if constexpr (I == 2) {
            return value.avg_client_sim_tick_time_ms;
        }
        else if constexpr (I == 3) {
            return value.avg_begin_frame_time_ms;
        }
        else if constexpr (I == 4) {
            return value.avg_input_time_ms;
        }
        else if constexpr (I == 5) {
            return value.avg_render_time_ms;
        }
        else if constexpr (I == 6) {
            return value.avg_end_frame_time_ms;
        }
        else if constexpr (I == 7) {
            return value.avg_remainder_time_percent;
        }
        else if constexpr (I == 8) {
            return value.avg_unaccounted_time_percent;
        }
        else if constexpr (I == 9) {
            return value.category_counters;
        }
        else if constexpr (I == 10) {
            return value.entity_timings;
        }
        else if constexpr (I == 11) {
            return value.system_timings;
        }
        else if constexpr (I == 12) {
            return value.system_categories;
        }
        else {
            return value.whisker_data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2193::ServerboundDiagnosticsPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2193::ServerboundDiagnosticsPacket>{"ServerboundDiagnosticsPacket"};

template <>
inline constexpr std::array<std::string_view, 14> field_names_v<v2193::ServerboundDiagnosticsPacket>{{
    "avg_fps",
    "avg_server_sim_tick_time_ms",
    "avg_client_sim_tick_time_ms",
    "avg_begin_frame_time_ms",
    "avg_input_time_ms",
    "avg_render_time_ms",
    "avg_end_frame_time_ms",
    "avg_remainder_time_percent",
    "avg_unaccounted_time_percent",
    "category_counters",
    "entity_timings",
    "system_timings",
    "system_categories",
    "whisker_data",
}};

template <>
struct field_accessor<v2193::ServerboundDiagnosticsPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.avg_fps;
        }
        else if constexpr (I == 1) {
            return value.avg_server_sim_tick_time_ms;
        }
        else if constexpr (I == 2) {
            return value.avg_client_sim_tick_time_ms;
        }
        else if constexpr (I == 3) {
            return value.avg_begin_frame_time_ms;
        }
        else if constexpr (I == 4) {
            return value.avg_input_time_ms;
        }
        else if constexpr (I == 5) {
            return value.avg_render_time_ms;
        }
        else if constexpr (I == 6) {
            return value.avg_end_frame_time_ms;
        }
        else if constexpr (I == 7) {
            return value.avg_remainder_time_percent;
        }
        else if constexpr (I == 8) {
            return value.avg_unaccounted_time_percent;
        }
        else if constexpr (I == 9) {
            return value.category_counters;
        }
        else if constexpr (I == 10) {
            return value.entity_timings;
        }
        else if constexpr (I == 11) {
            return value.system_timings;
        }
        else if constexpr (I == 12) {
            return value.system_categories;
        }
        else {
            return value.whisker_data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::ServerboundDiagnosticsPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::ServerboundDiagnosticsPacket>{"ServerboundDiagnosticsPacket"};

template <>
inline constexpr std::array<std::string_view, 14> field_names_v<v2225::ServerboundDiagnosticsPacket>{{
    "avg_fps",
    "avg_server_sim_tick_time_ms",
    "avg_client_sim_tick_time_ms",
    "avg_begin_frame_time_ms",
    "avg_input_time_ms",
    "avg_render_time_ms",
    "avg_end_frame_time_ms",
    "avg_remainder_time_percent",
    "avg_unaccounted_time_percent",
    "category_counters",
    "entity_timings",
    "system_timings",
    "system_categories",
    "whisker_data",
}};

template <>
struct field_accessor<v2225::ServerboundDiagnosticsPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.avg_fps;
        }
        else if constexpr (I == 1) {
            return value.avg_server_sim_tick_time_ms;
        }
        else if constexpr (I == 2) {
            return value.avg_client_sim_tick_time_ms;
        }
        else if constexpr (I == 3) {
            return value.avg_begin_frame_time_ms;
        }
        else if constexpr (I == 4) {
            return value.avg_input_time_ms;
        }
        else if constexpr (I == 5) {
            return value.avg_render_time_ms;
        }
        else if constexpr (I == 6) {
            return value.avg_end_frame_time_ms;
        }
        else if constexpr (I == 7) {
            return value.avg_remainder_time_percent;
        }
        else if constexpr (I == 8) {
            return value.avg_unaccounted_time_percent;
        }
        else if constexpr (I == 9) {
            return value.category_counters;
        }
        else if constexpr (I == 10) {
            return value.entity_timings;
        }
        else if constexpr (I == 11) {
            return value.system_timings;
        }
        else if constexpr (I == 12) {
            return value.system_categories;
        }
        else {
            return value.whisker_data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::EditorNetworkPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::EditorNetworkPacket>{"EditorNetworkPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<base::EditorNetworkPacket>{{
    "route_to_manager",
    "payload",
}};

template <>
struct field_accessor<base::EditorNetworkPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.route_to_manager;
        }
        else {
            return value.payload;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::EditorNetworkPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::EditorNetworkPacket>{"EditorNetworkPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v944::EditorNetworkPacket>{{
    "route_to_manager",
    "raw_variant_name",
    "raw_variant_data",
}};

template <>
struct field_accessor<v944::EditorNetworkPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.route_to_manager;
        }
        else if constexpr (I == 1) {
            return value.raw_variant_name;
        }
        else {
            return value.raw_variant_data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<DebugInfoPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<DebugInfoPacket>{"DebugInfoPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<DebugInfoPacket>{{
    "actor_id",
    "data",
}};

template <>
struct field_accessor<DebugInfoPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.actor_id;
        }
        else {
            return value.data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<ClientboundDebugRendererPacket::DebugMarkerData> = true;

template <>
inline constexpr std::string_view struct_name_v<ClientboundDebugRendererPacket::DebugMarkerData>{"ClientboundDebugRendererPacket::DebugMarkerData"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<ClientboundDebugRendererPacket::DebugMarkerData>{{
    "text",
    "position",
    "color",
    "duration_ms",
}};

template <>
struct field_accessor<ClientboundDebugRendererPacket::DebugMarkerData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.text;
        }
        else if constexpr (I == 1) {
            return value.position;
        }
        else if constexpr (I == 2) {
            return value.color;
        }
        else {
            return value.duration_ms;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<ClientboundDebugRendererPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<ClientboundDebugRendererPacket>{"ClientboundDebugRendererPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<ClientboundDebugRendererPacket>{{
    "type",
    "debug_marker_data",
}};

template <>
struct field_accessor<ClientboundDebugRendererPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.type;
        }
        else {
            return value.debug_marker_data;
        }
    }
};

}  // namespace detail


template <>
struct Serializer<v924::MemoryCategoryCounter> {
    static void serialize(BinaryWriter &stream, const v924::MemoryCategoryCounter &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::MemoryCategoryCounter, std::error_code>;
};

template <>
struct Serializer<v944::MemoryCategoryCounter> {
    static void serialize(BinaryWriter &stream, const v944::MemoryCategoryCounter &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::MemoryCategoryCounter, std::error_code>;
};

template <>
struct Serializer<v975::MemoryCategoryCounter> {
    static void serialize(BinaryWriter &stream, const v975::MemoryCategoryCounter &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v975::MemoryCategoryCounter, std::error_code>;
};

template <>
struct Serializer<v2168::MemoryCategoryCounter> {
    static void serialize(BinaryWriter &stream, const v2168::MemoryCategoryCounter &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::MemoryCategoryCounter, std::error_code>;
};

template <>
struct Serializer<v2193::MemoryCategoryCounter> {
    static void serialize(BinaryWriter &stream, const v2193::MemoryCategoryCounter &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::MemoryCategoryCounter, std::error_code>;
};

template <>
struct Serializer<v2225::MemoryCategoryCounter> {
    static void serialize(BinaryWriter &stream, const v2225::MemoryCategoryCounter &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::MemoryCategoryCounter, std::error_code>;
};

template <>
struct Serializer<base::EntityDiagnosticTimingInfo> {
    static void serialize(BinaryWriter &stream, const base::EntityDiagnosticTimingInfo &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::EntityDiagnosticTimingInfo, std::error_code>;
};

template <>
struct Serializer<v2193::EntityDiagnosticTimingInfo> {
    static void serialize(BinaryWriter &stream, const v2193::EntityDiagnosticTimingInfo &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::EntityDiagnosticTimingInfo, std::error_code>;
};

template <>
struct Serializer<SystemDiagnosticTimingInfo> {
    static void serialize(BinaryWriter &stream, const SystemDiagnosticTimingInfo &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<SystemDiagnosticTimingInfo, std::error_code>;
};

template <>
struct Serializer<v2168::SystemCategory> {
    static void serialize(BinaryWriter &stream, const v2168::SystemCategory &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::SystemCategory, std::error_code>;
};

template <>
struct Serializer<ScopeDataSummary> {
    static void serialize(BinaryWriter &stream, const ScopeDataSummary &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<ScopeDataSummary, std::error_code>;
};

template <>
struct Serializer<base::ServerboundDiagnosticsPacket> {
    static void serialize(BinaryWriter &stream, const base::ServerboundDiagnosticsPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ServerboundDiagnosticsPacket, std::error_code>;
};

template <>
struct Serializer<v924::ServerboundDiagnosticsPacket> {
    static void serialize(BinaryWriter &stream, const v924::ServerboundDiagnosticsPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::ServerboundDiagnosticsPacket, std::error_code>;
};

template <>
struct Serializer<v944::ServerboundDiagnosticsPacket> {
    static void serialize(BinaryWriter &stream, const v944::ServerboundDiagnosticsPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::ServerboundDiagnosticsPacket, std::error_code>;
};

template <>
struct Serializer<v975::ServerboundDiagnosticsPacket> {
    static void serialize(BinaryWriter &stream, const v975::ServerboundDiagnosticsPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v975::ServerboundDiagnosticsPacket, std::error_code>;
};

template <>
struct Serializer<v1001::ServerboundDiagnosticsPacket> {
    static void serialize(BinaryWriter &stream, const v1001::ServerboundDiagnosticsPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::ServerboundDiagnosticsPacket, std::error_code>;
};

template <>
struct Serializer<v2168::ServerboundDiagnosticsPacket> {
    static void serialize(BinaryWriter &stream, const v2168::ServerboundDiagnosticsPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ServerboundDiagnosticsPacket, std::error_code>;
};

template <>
struct Serializer<v2193::ServerboundDiagnosticsPacket> {
    static void serialize(BinaryWriter &stream, const v2193::ServerboundDiagnosticsPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::ServerboundDiagnosticsPacket, std::error_code>;
};

template <>
struct Serializer<v2225::ServerboundDiagnosticsPacket> {
    static void serialize(BinaryWriter &stream, const v2225::ServerboundDiagnosticsPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::ServerboundDiagnosticsPacket, std::error_code>;
};

template <>
struct Serializer<base::EditorNetworkPacket> {
    static void serialize(BinaryWriter &stream, const base::EditorNetworkPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::EditorNetworkPacket, std::error_code>;
};

template <>
struct Serializer<v944::EditorNetworkPacket> {
    static void serialize(BinaryWriter &stream, const v944::EditorNetworkPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::EditorNetworkPacket, std::error_code>;
};

template <>
struct Serializer<DebugInfoPacket> {
    static void serialize(BinaryWriter &stream, const DebugInfoPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<DebugInfoPacket, std::error_code>;
};

template <>
struct Serializer<ClientboundDebugRendererPacket::PayloadType> {
    static void serialize(BinaryWriter &stream, ClientboundDebugRendererPacket::PayloadType value);
    static auto deserialize(BinaryReader &stream) -> std::expected<ClientboundDebugRendererPacket::PayloadType, std::error_code>;
};

template <>
struct Serializer<ClientboundDebugRendererPacket::DebugMarkerData> {
    static void serialize(BinaryWriter &stream, const ClientboundDebugRendererPacket::DebugMarkerData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<ClientboundDebugRendererPacket::DebugMarkerData, std::error_code>;
};

template <>
struct Serializer<ClientboundDebugRendererPacket> {
    static void serialize(BinaryWriter &stream, const ClientboundDebugRendererPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<ClientboundDebugRendererPacket, std::error_code>;
};
using MemoryCategory = MemoryCategory_<2225>;
using MemoryCategoryCounter = MemoryCategoryCounter_<2225>;
using EntityDiagnosticTimingInfo = EntityDiagnosticTimingInfo_<2225>;
using SystemCategory = SystemCategory_<2225>;
using ServerboundDiagnosticsPacket = ServerboundDiagnosticsPacket_<2225>;
using EditorNetworkPacket = EditorNetworkPacket_<2225>;

}  // namespace bedrock::protocol
