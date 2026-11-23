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

#include <bedrock/protocol/actor.h>
#include <bedrock/protocol/common.h>
#include <bedrock/protocol/eas.h>

namespace bedrock::protocol {

enum class Scheme : std::uint8_t {
    LockedPlayerRelativeStrafe = 0,
    CameraRelative = 1,
    CameraRelativeStrafe = 2,
    PlayerRelative = 3,
    PlayerRelativeStrafe = 4,
};

struct CameraPacket {
    static constexpr int Id = 73;
    ActorUniqueID camera_id{};
    ActorUniqueID target_player_id{};
};

enum class CameraShakeType : std::uint8_t {
    Positional = 0,
    Rotational = 1,
};

enum class CameraShakeAction : std::uint8_t {
    Add = 0,
    Stop = 1,
};

struct CameraShakePacket {
    static constexpr int Id = 159;
    float intensity{};
    float seconds{};
    CameraShakeType shake_type{};
    CameraShakeAction shake_action{};
};

namespace CameraAimAssistActorPriority_nested {

struct PriorityData {
    std::int32_t preset_index{};
    std::int32_t category_index{};
    std::int32_t actor_index{};
    std::int32_t priority_value{};
};

}  // namespace CameraAimAssistActorPriority_nested

struct CameraAimAssistActorPriority {
    using PriorityData = CameraAimAssistActorPriority_nested::PriorityData;
};

enum class SplineType : std::uint8_t {
    CatmullRom = 0,
    Linear = 1,
};

struct CameraSplineControlPoint {
    Vec3 position{};
};

struct CameraSplineProgressKeyFrame {
    float alpha{};
    float time_seconds{};
    std::optional<EasingType> easing_type{};
};

struct CameraSplineRotationKeyFrame {
    Vec3 rotation{};
    float time_seconds{};
    std::optional<EasingType> easing_type{};
};

struct CameraSplineDefinition {
    std::string name{};
    float total_time{};
    std::string spline_type{};
    std::vector<CameraSplineControlPoint> spline_control_points{};
    std::vector<CameraSplineProgressKeyFrame> spline_progress_frames{};
    std::vector<CameraSplineRotationKeyFrame> spline_rotation_frames{};
};

namespace base {

namespace CameraPreset_nested {

enum class AudioListener : std::uint8_t {
    Camera = 0,
    Player = 1,
};

}  // namespace CameraPreset_nested

struct CameraPreset {
    using AudioListener = CameraPreset_nested::AudioListener;

    std::string name{};
    std::string inherit_from{};
    std::optional<float> pos_x{};
    std::optional<float> pos_y{};
    std::optional<float> pos_z{};
    std::optional<float> rot_x{};
    std::optional<float> rot_y{};
    std::optional<float> camera_rotation_speed{};
    std::optional<bool> snap_to_target{};
    std::optional<Vec2> view_offset{};
    std::optional<Vec3> entity_offset{};
    std::optional<float> radius{};
    std::optional<base::CameraPreset::AudioListener> listener{};
    std::optional<bool> player_effects{};
};

struct CameraPresets {
    std::vector<base::CameraPreset> presets{};
};

struct CameraPresetsPacket {
    static constexpr int Id = 198;
    base::CameraPresets camera_presets{};
};

namespace CameraAimAssistPacket_nested {

enum class Action : std::uint8_t {
    Set = 0,
    Clear = 1,
    Count = 2,
};

enum class TargetMode : std::uint8_t {
    Angle = 0,
    Distance = 1,
    Count = 2,
};

}  // namespace CameraAimAssistPacket_nested

struct CameraAimAssistPacket {
    using Action = CameraAimAssistPacket_nested::Action;
    using TargetMode = CameraAimAssistPacket_nested::TargetMode;

    static constexpr int Id = 316;
    Vec2 view_angle{};
    float distance{};
    base::CameraAimAssistPacket::TargetMode target_mode{};
    base::CameraAimAssistPacket::Action action{};
};

namespace CameraInstructionOptions_nested {

namespace SetInstruction_nested {

struct EaseOption {
    EasingType easing_type{};
    float easing_time{};
};

struct PosOption {
    Vec3 pos{};
};

struct RotOption {
    float rot_x{};
    float rot_y{};
};

struct FacingOption {
    Vec3 facing_pos{};
};

struct ViewOffsetOption {
    float view_offset_x{};
    float view_offset_y{};
};

struct EntityOffsetOption {
    float entity_offset_x{};
    float entity_offset_y{};
    float entity_offset_z{};
};

}  // namespace SetInstruction_nested

struct SetInstruction {
    using EaseOption = SetInstruction_nested::EaseOption;
    using PosOption = SetInstruction_nested::PosOption;
    using RotOption = SetInstruction_nested::RotOption;
    using FacingOption = SetInstruction_nested::FacingOption;
    using ViewOffsetOption = SetInstruction_nested::ViewOffsetOption;
    using EntityOffsetOption = SetInstruction_nested::EntityOffsetOption;

    std::uint32_t preset_index{};
    std::optional<SetInstruction::EaseOption> ease{};
    std::optional<SetInstruction::PosOption> pos{};
    std::optional<SetInstruction::RotOption> rot{};
    std::optional<SetInstruction::FacingOption> facing{};
    std::optional<SetInstruction::ViewOffsetOption> view_offset{};
    std::optional<bool> default_{};
};

namespace FadeInstruction_nested {

struct TimeOption {
    float fade_in_time{};
    float hold_time{};
    float fade_out_time{};
};

struct ColorOption {
    float red{};
    float green{};
    float blue{};
};

}  // namespace FadeInstruction_nested

struct FadeInstruction {
    using TimeOption = FadeInstruction_nested::TimeOption;
    using ColorOption = FadeInstruction_nested::ColorOption;

    std::optional<FadeInstruction::TimeOption> time{};
    std::optional<FadeInstruction::ColorOption> color{};
};

struct TargetInstruction {
    std::optional<Vec3> target_center_offset{};
    ActorUniqueID target_actor_id{};
};

struct FovInstruction {
    float fov{};
    float fov_ease_time{};
    EasingType fov_ease_type{};
    bool fov_clear{};
};

struct AttachToEntityInstruction {
    ActorUniqueID attach_to_entity_id{};
};

namespace SplineInstruction_nested {

struct SplineRotationOption {
    Vec3 rotation_key_frame_value{};
    float rotation_key_frame_time{};
};

struct SplineProgressOption {
    float progress_key_frame_value{};
    float progress_key_frame_time{};
    EasingType progress_key_frames_easing_func{};
};

}  // namespace SplineInstruction_nested

struct SplineInstruction {
    using SplineRotationOption = SplineInstruction_nested::SplineRotationOption;
    using SplineProgressOption = SplineInstruction_nested::SplineProgressOption;

    float total_time{};
    SplineType curve_type{};
    std::vector<Vec3> curve{};
    std::vector<Vec2> progress_key_frames{};
    std::vector<SplineInstruction::SplineRotationOption> spline_rotation_option{};
};

}  // namespace CameraInstructionOptions_nested

struct CameraInstructionOptions {
    using SetInstruction = CameraInstructionOptions_nested::SetInstruction;
    using FadeInstruction = CameraInstructionOptions_nested::FadeInstruction;
    using TargetInstruction = CameraInstructionOptions_nested::TargetInstruction;
    using FovInstruction = CameraInstructionOptions_nested::FovInstruction;
    using AttachToEntityInstruction = CameraInstructionOptions_nested::AttachToEntityInstruction;
    using SplineInstruction = CameraInstructionOptions_nested::SplineInstruction;
};

struct CameraInstruction {
    std::optional<base::CameraInstructionOptions::SetInstruction> set{};
    std::optional<bool> clear{};
    std::optional<base::CameraInstructionOptions::FadeInstruction> fade{};
    std::optional<base::CameraInstructionOptions::TargetInstruction> target{};
    std::optional<bool> remove_target{};
};

struct CameraInstructionPacket {
    static constexpr int Id = 300;
    base::CameraInstruction camera_instruction{};
};

}  // namespace base

namespace v748 {

namespace CameraPreset_nested {

using AudioListener = base::CameraPreset::AudioListener;

}  // namespace CameraPreset_nested

struct CameraPreset {
    using AudioListener = CameraPreset_nested::AudioListener;

    std::string name{};
    std::string inherit_from{};
    std::optional<float> pos_x{};
    std::optional<float> pos_y{};
    std::optional<float> pos_z{};
    std::optional<float> rot_x{};
    std::optional<float> rot_y{};
    std::optional<float> camera_rotation_speed{};
    std::optional<bool> snap_to_target{};
    std::optional<Vec2> horizontal_rotation_limit{};
    std::optional<Vec2> vertical_rotation_limit{};
    std::optional<bool> continue_targeting{};
    std::optional<Vec2> view_offset{};
    std::optional<Vec3> entity_offset{};
    std::optional<float> radius{};
    std::optional<v748::CameraPreset::AudioListener> listener{};
    std::optional<bool> player_effects{};
    std::optional<bool> align_target_and_camera_forward{};
};

struct CameraPresets {
    std::vector<v748::CameraPreset> presets{};
};

struct CameraPresetsPacket {
    static constexpr int Id = 198;
    v748::CameraPresets camera_presets{};
};

using CameraAimAssistPacket = base::CameraAimAssistPacket;

namespace CameraInstructionOptions_nested {

namespace SetInstruction_nested {

struct EaseOption {
    EasingType easing_type{};
    float easing_time{};
};

struct PosOption {
    Vec3 pos{};
};

struct RotOption {
    float rot_x{};
    float rot_y{};
};

struct FacingOption {
    Vec3 facing_pos{};
};

struct ViewOffsetOption {
    float view_offset_x{};
    float view_offset_y{};
};

struct EntityOffsetOption {
    float entity_offset_x{};
    float entity_offset_y{};
    float entity_offset_z{};
};

}  // namespace SetInstruction_nested

struct SetInstruction {
    using EaseOption = SetInstruction_nested::EaseOption;
    using PosOption = SetInstruction_nested::PosOption;
    using RotOption = SetInstruction_nested::RotOption;
    using FacingOption = SetInstruction_nested::FacingOption;
    using ViewOffsetOption = SetInstruction_nested::ViewOffsetOption;
    using EntityOffsetOption = SetInstruction_nested::EntityOffsetOption;

    std::uint32_t preset_index{};
    std::optional<SetInstruction::EaseOption> ease{};
    std::optional<SetInstruction::PosOption> pos{};
    std::optional<SetInstruction::RotOption> rot{};
    std::optional<SetInstruction::FacingOption> facing{};
    std::optional<SetInstruction::ViewOffsetOption> view_offset{};
    std::optional<SetInstruction::EntityOffsetOption> entity_offset{};
    std::optional<bool> default_{};
};

using FadeInstruction = base::CameraInstructionOptions::FadeInstruction;
using TargetInstruction = base::CameraInstructionOptions::TargetInstruction;
using FovInstruction = base::CameraInstructionOptions::FovInstruction;
using AttachToEntityInstruction = base::CameraInstructionOptions::AttachToEntityInstruction;

namespace SplineInstruction_nested {

struct SplineRotationOption {
    Vec3 rotation_key_frame_value{};
    float rotation_key_frame_time{};
};

struct SplineProgressOption {
    float progress_key_frame_value{};
    float progress_key_frame_time{};
    EasingType progress_key_frames_easing_func{};
};

}  // namespace SplineInstruction_nested

struct SplineInstruction {
    using SplineRotationOption = SplineInstruction_nested::SplineRotationOption;
    using SplineProgressOption = SplineInstruction_nested::SplineProgressOption;

    float total_time{};
    SplineType curve_type{};
    std::vector<Vec3> curve{};
    std::vector<Vec2> progress_key_frames{};
    std::vector<SplineInstruction::SplineRotationOption> spline_rotation_option{};
};

}  // namespace CameraInstructionOptions_nested

struct CameraInstructionOptions {
    using SetInstruction = CameraInstructionOptions_nested::SetInstruction;
    using FadeInstruction = CameraInstructionOptions_nested::FadeInstruction;
    using TargetInstruction = CameraInstructionOptions_nested::TargetInstruction;
    using FovInstruction = CameraInstructionOptions_nested::FovInstruction;
    using AttachToEntityInstruction = CameraInstructionOptions_nested::AttachToEntityInstruction;
    using SplineInstruction = CameraInstructionOptions_nested::SplineInstruction;
};

struct CameraInstruction {
    std::optional<v748::CameraInstructionOptions::SetInstruction> set{};
    std::optional<bool> clear{};
    std::optional<v748::CameraInstructionOptions::FadeInstruction> fade{};
    std::optional<v748::CameraInstructionOptions::TargetInstruction> target{};
    std::optional<bool> remove_target{};
};

struct CameraInstructionPacket {
    static constexpr int Id = 300;
    v748::CameraInstruction camera_instruction{};
};

}  // namespace v748

namespace v766 {

enum class TargetMode : std::uint8_t {
    Angle = 0,
    Distance = 1,
};

struct CameraAimAssistCommandPresetDefinition {
    std::optional<std::string> preset_id{};
    std::optional<v766::TargetMode> target_mode{};
    std::optional<Vec2> angle{};
    std::optional<float> distance{};
};

namespace CameraPreset_nested {

using AudioListener = base::CameraPreset::AudioListener;

}  // namespace CameraPreset_nested

struct CameraPreset {
    using AudioListener = CameraPreset_nested::AudioListener;

    std::string name{};
    std::string inherit_from{};
    std::optional<float> pos_x{};
    std::optional<float> pos_y{};
    std::optional<float> pos_z{};
    std::optional<float> rot_x{};
    std::optional<float> rot_y{};
    std::optional<float> camera_rotation_speed{};
    std::optional<bool> snap_to_target{};
    std::optional<Vec2> horizontal_rotation_limit{};
    std::optional<Vec2> vertical_rotation_limit{};
    std::optional<bool> continue_targeting{};
    std::optional<float> tracking_radius{};
    std::optional<Vec2> view_offset{};
    std::optional<Vec3> entity_offset{};
    std::optional<float> radius{};
    std::optional<v766::CameraPreset::AudioListener> listener{};
    std::optional<bool> player_effects{};
    std::optional<bool> align_target_and_camera_forward{};
    std::optional<v766::CameraAimAssistCommandPresetDefinition> aim_assist{};
};

struct CameraPresets {
    std::vector<v766::CameraPreset> presets{};
};

struct CameraPresetsPacket {
    static constexpr int Id = 198;
    v766::CameraPresets camera_presets{};
};

namespace CameraAimAssistPacket_nested {

using Action = base::CameraAimAssistPacket::Action;
using TargetMode = base::CameraAimAssistPacket::TargetMode;

}  // namespace CameraAimAssistPacket_nested

struct CameraAimAssistPacket {
    using Action = CameraAimAssistPacket_nested::Action;
    using TargetMode = CameraAimAssistPacket_nested::TargetMode;

    static constexpr int Id = 316;
    std::string preset_id{};
    Vec2 view_angle{};
    float distance{};
    v766::CameraAimAssistPacket::TargetMode target_mode{};
    v766::CameraAimAssistPacket::Action action{};
};

struct CameraAimAssistCategoryPriorities {
    std::map<std::string, std::int32_t> entities{};
    std::map<std::string, std::int32_t> blocks{};
    std::optional<std::int32_t> entity_default{};
    std::optional<std::int32_t> block_default{};
};

struct CameraAimAssistCategoryDefinition {
    std::string name{};
    v766::CameraAimAssistCategoryPriorities priorities{};
};

struct CameraAimAssistPresetDefinition {
    std::string identifier{};
    std::string categories{};
    std::vector<std::string> exclusion_list{};
    std::vector<std::string> liquid_targeting_list{};
    std::map<std::string, std::string> item_settings{};
    std::optional<std::string> default_item_settings{};
    std::optional<std::string> hand_settings{};
};

struct CameraAimAssistCategoriesDefinition {
    std::string identifier{};
    std::vector<v766::CameraAimAssistCategoryDefinition> categories{};
};

struct CameraAimAssistPresetsPacket {
    static constexpr int Id = 320;
    std::vector<v766::CameraAimAssistCategoriesDefinition> categories{};
    std::vector<v766::CameraAimAssistPresetDefinition> presets{};
};

using CameraInstructionOptions = v748::CameraInstructionOptions;

using CameraInstruction = v748::CameraInstruction;

using CameraInstructionPacket = v748::CameraInstructionPacket;

}  // namespace v766

namespace v776 {

using TargetMode = v766::TargetMode;

using CameraAimAssistCommandPresetDefinition = v766::CameraAimAssistCommandPresetDefinition;

namespace CameraPreset_nested {

using AudioListener = base::CameraPreset::AudioListener;

}  // namespace CameraPreset_nested

struct CameraPreset {
    using AudioListener = CameraPreset_nested::AudioListener;

    std::string name{};
    std::string inherit_from{};
    std::optional<float> pos_x{};
    std::optional<float> pos_y{};
    std::optional<float> pos_z{};
    std::optional<float> rot_x{};
    std::optional<float> rot_y{};
    std::optional<float> camera_rotation_speed{};
    std::optional<bool> snap_to_target{};
    std::optional<Vec2> horizontal_rotation_limit{};
    std::optional<Vec2> vertical_rotation_limit{};
    std::optional<bool> continue_targeting{};
    std::optional<float> tracking_radius{};
    std::optional<Vec2> view_offset{};
    std::optional<Vec3> entity_offset{};
    std::optional<float> radius{};
    std::optional<float> yaw_limit_min{};
    std::optional<float> yaw_limit_max{};
    std::optional<v776::CameraPreset::AudioListener> listener{};
    std::optional<bool> player_effects{};
    std::optional<bool> align_target_and_camera_forward{};
    std::optional<v766::CameraAimAssistCommandPresetDefinition> aim_assist{};
};

struct CameraPresets {
    std::vector<v776::CameraPreset> presets{};
};

struct CameraPresetsPacket {
    static constexpr int Id = 198;
    v776::CameraPresets camera_presets{};
};

enum class ClientCameraAimAssistPacketAction : std::uint8_t {
    SetFromCameraPreset = 0,
    Clear = 1,
    Count = 2,
};

struct ClientCameraAimAssistPacket {
    static constexpr int Id = 321;
    std::string camera_preset_id{};
    v776::ClientCameraAimAssistPacketAction action{};
    bool allow_aim_assist{};
};

using CameraAimAssistPacket = v766::CameraAimAssistPacket;

using CameraAimAssistCategoryPriorities = v766::CameraAimAssistCategoryPriorities;

using CameraAimAssistCategoryDefinition = v766::CameraAimAssistCategoryDefinition;

struct CameraAimAssistPresetDefinition {
    std::string identifier{};
    std::vector<std::string> exclusion_list{};
    std::vector<std::string> liquid_targeting_list{};
    std::map<std::string, std::string> item_settings{};
    std::optional<std::string> default_item_settings{};
    std::optional<std::string> hand_settings{};
};

enum class CameraAimAssistPresetsPacketOperation : std::uint8_t {
    Set = 0,
    AddToExisting = 1,
};

struct CameraAimAssistPresetsPacket {
    static constexpr int Id = 320;
    std::vector<v766::CameraAimAssistCategoryDefinition> categories{};
    std::vector<v776::CameraAimAssistPresetDefinition> presets{};
    v776::CameraAimAssistPresetsPacketOperation operation{};
};

using CameraInstructionOptions = v748::CameraInstructionOptions;

using CameraInstruction = v748::CameraInstruction;

using CameraInstructionPacket = v748::CameraInstructionPacket;

}  // namespace v776

namespace v786 {

using TargetMode = v766::TargetMode;

using CameraAimAssistCommandPresetDefinition = v766::CameraAimAssistCommandPresetDefinition;

using CameraPreset = v776::CameraPreset;

using CameraPresets = v776::CameraPresets;

using CameraPresetsPacket = v776::CameraPresetsPacket;

using ClientCameraAimAssistPacketAction = v776::ClientCameraAimAssistPacketAction;

using ClientCameraAimAssistPacket = v776::ClientCameraAimAssistPacket;

using CameraAimAssistPacket = v766::CameraAimAssistPacket;

using CameraAimAssistCategoryPriorities = v766::CameraAimAssistCategoryPriorities;

using CameraAimAssistCategoryDefinition = v766::CameraAimAssistCategoryDefinition;

using CameraAimAssistPresetDefinition = v776::CameraAimAssistPresetDefinition;

using CameraAimAssistPresetsPacketOperation = v776::CameraAimAssistPresetsPacketOperation;

using CameraAimAssistPresetsPacket = v776::CameraAimAssistPresetsPacket;

using CameraInstructionOptions = v748::CameraInstructionOptions;

using CameraInstruction = v748::CameraInstruction;

using CameraInstructionPacket = v748::CameraInstructionPacket;

}  // namespace v786

namespace v800 {

using TargetMode = v766::TargetMode;

using CameraAimAssistCommandPresetDefinition = v766::CameraAimAssistCommandPresetDefinition;

namespace CameraPreset_nested {

using AudioListener = base::CameraPreset::AudioListener;

}  // namespace CameraPreset_nested

struct CameraPreset {
    using AudioListener = CameraPreset_nested::AudioListener;

    std::string name{};
    std::string inherit_from{};
    std::optional<float> pos_x{};
    std::optional<float> pos_y{};
    std::optional<float> pos_z{};
    std::optional<float> rot_x{};
    std::optional<float> rot_y{};
    std::optional<float> camera_rotation_speed{};
    std::optional<bool> snap_to_target{};
    std::optional<Vec2> horizontal_rotation_limit{};
    std::optional<Vec2> vertical_rotation_limit{};
    std::optional<bool> continue_targeting{};
    std::optional<float> tracking_radius{};
    std::optional<Vec2> view_offset{};
    std::optional<Vec3> entity_offset{};
    std::optional<float> radius{};
    std::optional<float> yaw_limit_min{};
    std::optional<float> yaw_limit_max{};
    std::optional<v800::CameraPreset::AudioListener> listener{};
    std::optional<bool> player_effects{};
    std::optional<bool> align_target_and_camera_forward{};
    std::optional<v766::CameraAimAssistCommandPresetDefinition> aim_assist{};
    std::optional<Scheme> control_scheme{};
};

struct CameraPresets {
    std::vector<v800::CameraPreset> presets{};
};

struct CameraPresetsPacket {
    static constexpr int Id = 198;
    v800::CameraPresets camera_presets{};
};

using ClientCameraAimAssistPacketAction = v776::ClientCameraAimAssistPacketAction;

using ClientCameraAimAssistPacket = v776::ClientCameraAimAssistPacket;

using CameraAimAssistPacket = v766::CameraAimAssistPacket;

using CameraAimAssistCategoryPriorities = v766::CameraAimAssistCategoryPriorities;

using CameraAimAssistCategoryDefinition = v766::CameraAimAssistCategoryDefinition;

using CameraAimAssistPresetDefinition = v776::CameraAimAssistPresetDefinition;

using CameraAimAssistPresetsPacketOperation = v776::CameraAimAssistPresetsPacketOperation;

using CameraAimAssistPresetsPacket = v776::CameraAimAssistPresetsPacket;

using CameraInstructionOptions = v748::CameraInstructionOptions;

using CameraInstruction = v748::CameraInstruction;

using CameraInstructionPacket = v748::CameraInstructionPacket;

struct ClientboundControlSchemeSetPacket {
    static constexpr int Id = 327;
    Scheme control_scheme{};
};

}  // namespace v800

namespace v818 {

using TargetMode = v766::TargetMode;

using CameraAimAssistCommandPresetDefinition = v766::CameraAimAssistCommandPresetDefinition;

namespace CameraPreset_nested {

using AudioListener = base::CameraPreset::AudioListener;

}  // namespace CameraPreset_nested

struct CameraPreset {
    using AudioListener = CameraPreset_nested::AudioListener;

    std::string name{};
    std::string inherit_from{};
    std::optional<float> pos_x{};
    std::optional<float> pos_y{};
    std::optional<float> pos_z{};
    std::optional<float> rot_x{};
    std::optional<float> rot_y{};
    std::optional<float> camera_rotation_speed{};
    std::optional<bool> snap_to_target{};
    std::optional<Vec2> horizontal_rotation_limit{};
    std::optional<Vec2> vertical_rotation_limit{};
    std::optional<bool> continue_targeting{};
    std::optional<float> tracking_radius{};
    std::optional<Vec2> view_offset{};
    std::optional<Vec3> entity_offset{};
    std::optional<float> radius{};
    std::optional<float> yaw_limit_min{};
    std::optional<float> yaw_limit_max{};
    std::optional<v818::CameraPreset::AudioListener> listener{};
    std::optional<bool> player_effects{};
    std::optional<v766::CameraAimAssistCommandPresetDefinition> aim_assist{};
    std::optional<Scheme> control_scheme{};
};

struct CameraPresets {
    std::vector<v818::CameraPreset> presets{};
};

struct CameraPresetsPacket {
    static constexpr int Id = 198;
    v818::CameraPresets camera_presets{};
};

using ClientCameraAimAssistPacketAction = v776::ClientCameraAimAssistPacketAction;

using ClientCameraAimAssistPacket = v776::ClientCameraAimAssistPacket;

using CameraAimAssistPacket = v766::CameraAimAssistPacket;

using CameraAimAssistCategoryPriorities = v766::CameraAimAssistCategoryPriorities;

using CameraAimAssistCategoryDefinition = v766::CameraAimAssistCategoryDefinition;

using CameraAimAssistPresetDefinition = v776::CameraAimAssistPresetDefinition;

using CameraAimAssistPresetsPacketOperation = v776::CameraAimAssistPresetsPacketOperation;

using CameraAimAssistPresetsPacket = v776::CameraAimAssistPresetsPacket;

namespace CameraInstructionOptions_nested {

namespace SetInstruction_nested {

struct EaseOption {
    EasingType easing_type{};
    float easing_time{};
};

struct PosOption {
    Vec3 pos{};
};

struct RotOption {
    float rot_x{};
    float rot_y{};
};

struct FacingOption {
    Vec3 facing_pos{};
};

struct ViewOffsetOption {
    float view_offset_x{};
    float view_offset_y{};
};

struct EntityOffsetOption {
    float entity_offset_x{};
    float entity_offset_y{};
    float entity_offset_z{};
};

}  // namespace SetInstruction_nested

struct SetInstruction {
    using EaseOption = SetInstruction_nested::EaseOption;
    using PosOption = SetInstruction_nested::PosOption;
    using RotOption = SetInstruction_nested::RotOption;
    using FacingOption = SetInstruction_nested::FacingOption;
    using ViewOffsetOption = SetInstruction_nested::ViewOffsetOption;
    using EntityOffsetOption = SetInstruction_nested::EntityOffsetOption;

    std::uint32_t preset_index{};
    std::optional<SetInstruction::EaseOption> ease{};
    std::optional<SetInstruction::PosOption> pos{};
    std::optional<SetInstruction::RotOption> rot{};
    std::optional<SetInstruction::FacingOption> facing{};
    std::optional<SetInstruction::ViewOffsetOption> view_offset{};
    std::optional<SetInstruction::EntityOffsetOption> entity_offset{};
    std::optional<bool> default_{};
    bool remove_ignore_starting_values_component{};
};

using FadeInstruction = base::CameraInstructionOptions::FadeInstruction;
using TargetInstruction = base::CameraInstructionOptions::TargetInstruction;
using FovInstruction = base::CameraInstructionOptions::FovInstruction;
using AttachToEntityInstruction = base::CameraInstructionOptions::AttachToEntityInstruction;

namespace SplineInstruction_nested {

struct SplineRotationOption {
    Vec3 rotation_key_frame_value{};
    float rotation_key_frame_time{};
};

struct SplineProgressOption {
    float progress_key_frame_value{};
    float progress_key_frame_time{};
    EasingType progress_key_frames_easing_func{};
};

}  // namespace SplineInstruction_nested

struct SplineInstruction {
    using SplineRotationOption = SplineInstruction_nested::SplineRotationOption;
    using SplineProgressOption = SplineInstruction_nested::SplineProgressOption;

    float total_time{};
    SplineType curve_type{};
    std::vector<Vec3> curve{};
    std::vector<Vec2> progress_key_frames{};
    std::vector<SplineInstruction::SplineRotationOption> spline_rotation_option{};
};

}  // namespace CameraInstructionOptions_nested

struct CameraInstructionOptions {
    using SetInstruction = CameraInstructionOptions_nested::SetInstruction;
    using FadeInstruction = CameraInstructionOptions_nested::FadeInstruction;
    using TargetInstruction = CameraInstructionOptions_nested::TargetInstruction;
    using FovInstruction = CameraInstructionOptions_nested::FovInstruction;
    using AttachToEntityInstruction = CameraInstructionOptions_nested::AttachToEntityInstruction;
    using SplineInstruction = CameraInstructionOptions_nested::SplineInstruction;
};

struct CameraInstruction {
    std::optional<v818::CameraInstructionOptions::SetInstruction> set{};
    std::optional<bool> clear{};
    std::optional<v818::CameraInstructionOptions::FadeInstruction> fade{};
    std::optional<v818::CameraInstructionOptions::TargetInstruction> target{};
    std::optional<bool> remove_target{};
};

struct CameraInstructionPacket {
    static constexpr int Id = 300;
    v818::CameraInstruction camera_instruction{};
};

using ClientboundControlSchemeSetPacket = v800::ClientboundControlSchemeSetPacket;

}  // namespace v818

namespace v827 {

using TargetMode = v766::TargetMode;

using CameraAimAssistCommandPresetDefinition = v766::CameraAimAssistCommandPresetDefinition;

using CameraPreset = v818::CameraPreset;

using CameraPresets = v818::CameraPresets;

using CameraPresetsPacket = v818::CameraPresetsPacket;

using ClientCameraAimAssistPacketAction = v776::ClientCameraAimAssistPacketAction;

using ClientCameraAimAssistPacket = v776::ClientCameraAimAssistPacket;

namespace CameraAimAssistPacket_nested {

using Action = base::CameraAimAssistPacket::Action;
using TargetMode = base::CameraAimAssistPacket::TargetMode;

}  // namespace CameraAimAssistPacket_nested

struct CameraAimAssistPacket {
    using Action = CameraAimAssistPacket_nested::Action;
    using TargetMode = CameraAimAssistPacket_nested::TargetMode;

    static constexpr int Id = 316;
    std::string preset_id{};
    Vec2 view_angle{};
    float distance{};
    v827::CameraAimAssistPacket::TargetMode target_mode{};
    v827::CameraAimAssistPacket::Action action{};
    bool show_debug_render{};
};

using CameraAimAssistCategoryPriorities = v766::CameraAimAssistCategoryPriorities;

using CameraAimAssistCategoryDefinition = v766::CameraAimAssistCategoryDefinition;

using CameraAimAssistPresetDefinition = v776::CameraAimAssistPresetDefinition;

using CameraAimAssistPresetsPacketOperation = v776::CameraAimAssistPresetsPacketOperation;

using CameraAimAssistPresetsPacket = v776::CameraAimAssistPresetsPacket;

using CameraInstructionOptions = v818::CameraInstructionOptions;

struct CameraInstruction {
    std::optional<v818::CameraInstructionOptions::SetInstruction> set{};
    std::optional<bool> clear{};
    std::optional<v818::CameraInstructionOptions::FadeInstruction> fade{};
    std::optional<v818::CameraInstructionOptions::TargetInstruction> target{};
    std::optional<bool> remove_target{};
    std::optional<v818::CameraInstructionOptions::FovInstruction> field_of_view{};
};

struct CameraInstructionPacket {
    static constexpr int Id = 300;
    v827::CameraInstruction camera_instruction{};
};

using ClientboundControlSchemeSetPacket = v800::ClientboundControlSchemeSetPacket;

}  // namespace v827

namespace v844 {

using TargetMode = v766::TargetMode;

using CameraAimAssistCommandPresetDefinition = v766::CameraAimAssistCommandPresetDefinition;

using CameraPreset = v818::CameraPreset;

using CameraPresets = v818::CameraPresets;

using CameraPresetsPacket = v818::CameraPresetsPacket;

using ClientCameraAimAssistPacketAction = v776::ClientCameraAimAssistPacketAction;

using ClientCameraAimAssistPacket = v776::ClientCameraAimAssistPacket;

using CameraAimAssistPacket = v827::CameraAimAssistPacket;

using CameraAimAssistCategoryPriorities = v766::CameraAimAssistCategoryPriorities;

using CameraAimAssistCategoryDefinition = v766::CameraAimAssistCategoryDefinition;

using CameraAimAssistPresetDefinition = v776::CameraAimAssistPresetDefinition;

using CameraAimAssistPresetsPacketOperation = v776::CameraAimAssistPresetsPacketOperation;

using CameraAimAssistPresetsPacket = v776::CameraAimAssistPresetsPacket;

using CameraInstructionOptions = v818::CameraInstructionOptions;

using CameraInstruction = v827::CameraInstruction;

using CameraInstructionPacket = v827::CameraInstructionPacket;

using ClientboundControlSchemeSetPacket = v800::ClientboundControlSchemeSetPacket;

}  // namespace v844

namespace v859 {

using TargetMode = v766::TargetMode;

using CameraAimAssistCommandPresetDefinition = v766::CameraAimAssistCommandPresetDefinition;

using CameraPreset = v818::CameraPreset;

using CameraPresets = v818::CameraPresets;

using CameraPresetsPacket = v818::CameraPresetsPacket;

using ClientCameraAimAssistPacketAction = v776::ClientCameraAimAssistPacketAction;

using ClientCameraAimAssistPacket = v776::ClientCameraAimAssistPacket;

using CameraAimAssistPacket = v827::CameraAimAssistPacket;

using CameraAimAssistCategoryPriorities = v766::CameraAimAssistCategoryPriorities;

using CameraAimAssistCategoryDefinition = v766::CameraAimAssistCategoryDefinition;

using CameraAimAssistPresetDefinition = v776::CameraAimAssistPresetDefinition;

using CameraAimAssistPresetsPacketOperation = v776::CameraAimAssistPresetsPacketOperation;

using CameraAimAssistPresetsPacket = v776::CameraAimAssistPresetsPacket;

using CameraInstructionOptions = v818::CameraInstructionOptions;

struct CameraInstruction {
    std::optional<v818::CameraInstructionOptions::SetInstruction> set{};
    std::optional<bool> clear{};
    std::optional<v818::CameraInstructionOptions::FadeInstruction> fade{};
    std::optional<v818::CameraInstructionOptions::TargetInstruction> target{};
    std::optional<bool> remove_target{};
    std::optional<v818::CameraInstructionOptions::FovInstruction> field_of_view{};
    std::optional<v818::CameraInstructionOptions::SplineInstruction> spline{};
    std::optional<v818::CameraInstructionOptions::AttachToEntityInstruction> attach_to_entity{};
    std::optional<bool> detach_from_entity{};
};

struct CameraInstructionPacket {
    static constexpr int Id = 300;
    v859::CameraInstruction camera_instruction{};
};

using ClientboundControlSchemeSetPacket = v800::ClientboundControlSchemeSetPacket;

}  // namespace v859

namespace v898 {

using TargetMode = v766::TargetMode;

using CameraAimAssistCommandPresetDefinition = v766::CameraAimAssistCommandPresetDefinition;

using CameraPreset = v818::CameraPreset;

using CameraPresets = v818::CameraPresets;

using CameraPresetsPacket = v818::CameraPresetsPacket;

using ClientCameraAimAssistPacketAction = v776::ClientCameraAimAssistPacketAction;

using ClientCameraAimAssistPacket = v776::ClientCameraAimAssistPacket;

using CameraAimAssistPacket = v827::CameraAimAssistPacket;

struct CameraAimAssistCategoryPriorities {
    std::map<std::string, std::int32_t> entities{};
    std::map<std::string, std::int32_t> blocks{};
    std::map<std::string, std::int32_t> block_tags{};
    std::optional<std::int32_t> entity_default{};
    std::optional<std::int32_t> block_default{};
};

struct CameraAimAssistCategoryDefinition {
    std::string name{};
    v898::CameraAimAssistCategoryPriorities priorities{};
};

struct CameraAimAssistPresetExclusionDefinition {
    std::vector<std::string> block_exclusion_list{};
    std::vector<std::string> actor_exclusion_list{};
    std::vector<std::string> block_tag_exclusion_list{};
};

struct CameraAimAssistPresetDefinition {
    std::string identifier{};
    v898::CameraAimAssistPresetExclusionDefinition exclusion_settings{};
    std::vector<std::string> liquid_targeting_list{};
    std::map<std::string, std::string> item_settings{};
    std::optional<std::string> default_item_settings{};
    std::optional<std::string> hand_settings{};
};

using CameraAimAssistPresetsPacketOperation = v776::CameraAimAssistPresetsPacketOperation;

struct CameraAimAssistPresetsPacket {
    static constexpr int Id = 320;
    std::vector<v898::CameraAimAssistCategoryDefinition> categories{};
    std::vector<v898::CameraAimAssistPresetDefinition> presets{};
    v776::CameraAimAssistPresetsPacketOperation operation{};
};

using CameraInstructionOptions = v818::CameraInstructionOptions;

using CameraInstruction = v859::CameraInstruction;

using CameraInstructionPacket = v859::CameraInstructionPacket;

using ClientboundControlSchemeSetPacket = v800::ClientboundControlSchemeSetPacket;

}  // namespace v898

namespace v924 {

using TargetMode = v766::TargetMode;

using CameraAimAssistCommandPresetDefinition = v766::CameraAimAssistCommandPresetDefinition;

using CameraPreset = v818::CameraPreset;

using CameraPresets = v818::CameraPresets;

using CameraPresetsPacket = v818::CameraPresetsPacket;

struct CameraAimAssistActorPriorityPacket {
    static constexpr int Id = 339;
    std::vector<CameraAimAssistActorPriority::PriorityData> camera_aim_assist_actor_priority_list{};
};

using ClientCameraAimAssistPacketAction = v776::ClientCameraAimAssistPacketAction;

using ClientCameraAimAssistPacket = v776::ClientCameraAimAssistPacket;

using CameraAimAssistPacket = v827::CameraAimAssistPacket;

struct CameraAimAssistCategoryPriorities {
    std::map<std::string, std::int32_t> entities{};
    std::map<std::string, std::int32_t> blocks{};
    std::map<std::string, std::int32_t> block_tags{};
    std::map<std::string, std::int32_t> entity_type_families{};
    std::optional<std::int32_t> entity_default{};
    std::optional<std::int32_t> block_default{};
};

struct CameraAimAssistCategoryDefinition {
    std::string name{};
    v924::CameraAimAssistCategoryPriorities priorities{};
};

struct CameraAimAssistPresetExclusionDefinition {
    std::vector<std::string> block_exclusion_list{};
    std::vector<std::string> actor_exclusion_list{};
    std::vector<std::string> block_tag_exclusion_list{};
    std::vector<std::string> entity_type_family_exclusion_list{};
};

struct CameraAimAssistPresetDefinition {
    std::string identifier{};
    v924::CameraAimAssistPresetExclusionDefinition exclusion_settings{};
    std::vector<std::string> liquid_targeting_list{};
    std::map<std::string, std::string> item_settings{};
    std::optional<std::string> default_item_settings{};
    std::optional<std::string> hand_settings{};
};

using CameraAimAssistPresetsPacketOperation = v776::CameraAimAssistPresetsPacketOperation;

struct CameraAimAssistPresetsPacket {
    static constexpr int Id = 320;
    std::vector<v924::CameraAimAssistCategoryDefinition> categories{};
    std::vector<v924::CameraAimAssistPresetDefinition> presets{};
    v776::CameraAimAssistPresetsPacketOperation operation{};
};

namespace CameraInstructionOptions_nested {

namespace SetInstruction_nested {

struct EaseOption {
    EasingType easing_type{};
    float easing_time{};
};

struct PosOption {
    Vec3 pos{};
};

struct RotOption {
    float rot_x{};
    float rot_y{};
};

struct FacingOption {
    Vec3 facing_pos{};
};

struct ViewOffsetOption {
    float view_offset_x{};
    float view_offset_y{};
};

struct EntityOffsetOption {
    float entity_offset_x{};
    float entity_offset_y{};
    float entity_offset_z{};
};

}  // namespace SetInstruction_nested

struct SetInstruction {
    using EaseOption = SetInstruction_nested::EaseOption;
    using PosOption = SetInstruction_nested::PosOption;
    using RotOption = SetInstruction_nested::RotOption;
    using FacingOption = SetInstruction_nested::FacingOption;
    using ViewOffsetOption = SetInstruction_nested::ViewOffsetOption;
    using EntityOffsetOption = SetInstruction_nested::EntityOffsetOption;

    std::uint32_t preset_index{};
    std::optional<SetInstruction::EaseOption> ease{};
    std::optional<SetInstruction::PosOption> pos{};
    std::optional<SetInstruction::RotOption> rot{};
    std::optional<SetInstruction::FacingOption> facing{};
    std::optional<SetInstruction::ViewOffsetOption> view_offset{};
    std::optional<SetInstruction::EntityOffsetOption> entity_offset{};
    std::optional<bool> default_{};
    bool remove_ignore_starting_values_component{};
};

using FadeInstruction = base::CameraInstructionOptions::FadeInstruction;
using TargetInstruction = base::CameraInstructionOptions::TargetInstruction;
using FovInstruction = base::CameraInstructionOptions::FovInstruction;
using AttachToEntityInstruction = base::CameraInstructionOptions::AttachToEntityInstruction;

namespace SplineInstruction_nested {

struct SplineRotationOption {
    Vec3 rotation_key_frame_value{};
    float rotation_key_frame_time{};
    EasingType rotation_key_frames_easing_func{};
};

struct SplineProgressOption {
    float progress_key_frame_value{};
    float progress_key_frame_time{};
    EasingType progress_key_frames_easing_func{};
};

}  // namespace SplineInstruction_nested

struct SplineInstruction {
    using SplineRotationOption = SplineInstruction_nested::SplineRotationOption;
    using SplineProgressOption = SplineInstruction_nested::SplineProgressOption;

    float total_time{};
    SplineType curve_type{};
    std::vector<Vec3> curve{};
    std::vector<SplineInstruction::SplineProgressOption> progress_key_frames{};
    std::vector<SplineInstruction::SplineRotationOption> spline_rotation_option{};
};

}  // namespace CameraInstructionOptions_nested

struct CameraInstructionOptions {
    using SetInstruction = CameraInstructionOptions_nested::SetInstruction;
    using FadeInstruction = CameraInstructionOptions_nested::FadeInstruction;
    using TargetInstruction = CameraInstructionOptions_nested::TargetInstruction;
    using FovInstruction = CameraInstructionOptions_nested::FovInstruction;
    using AttachToEntityInstruction = CameraInstructionOptions_nested::AttachToEntityInstruction;
    using SplineInstruction = CameraInstructionOptions_nested::SplineInstruction;
};

struct CameraInstruction {
    std::optional<v924::CameraInstructionOptions::SetInstruction> set{};
    std::optional<bool> clear{};
    std::optional<v924::CameraInstructionOptions::FadeInstruction> fade{};
    std::optional<v924::CameraInstructionOptions::TargetInstruction> target{};
    std::optional<bool> remove_target{};
    std::optional<v924::CameraInstructionOptions::FovInstruction> field_of_view{};
    std::optional<v924::CameraInstructionOptions::SplineInstruction> spline{};
    std::optional<v924::CameraInstructionOptions::AttachToEntityInstruction> attach_to_entity{};
    std::optional<bool> detach_from_entity{};
};

struct CameraInstructionPacket {
    static constexpr int Id = 300;
    v924::CameraInstruction camera_instruction{};
};

struct CameraSplinePacket {
    static constexpr int Id = 338;
    std::vector<CameraSplineDefinition> splines{};
};

using ClientboundControlSchemeSetPacket = v800::ClientboundControlSchemeSetPacket;

}  // namespace v924

namespace v944 {

using TargetMode = v766::TargetMode;

using CameraAimAssistCommandPresetDefinition = v766::CameraAimAssistCommandPresetDefinition;

using CameraPreset = v818::CameraPreset;

using CameraPresets = v818::CameraPresets;

using CameraPresetsPacket = v818::CameraPresetsPacket;

using CameraAimAssistActorPriorityPacket = v924::CameraAimAssistActorPriorityPacket;

using ClientCameraAimAssistPacketAction = v776::ClientCameraAimAssistPacketAction;

using ClientCameraAimAssistPacket = v776::ClientCameraAimAssistPacket;

using CameraAimAssistPacket = v827::CameraAimAssistPacket;

using CameraAimAssistCategoryPriorities = v924::CameraAimAssistCategoryPriorities;

using CameraAimAssistCategoryDefinition = v924::CameraAimAssistCategoryDefinition;

using CameraAimAssistPresetExclusionDefinition = v924::CameraAimAssistPresetExclusionDefinition;

using CameraAimAssistPresetDefinition = v924::CameraAimAssistPresetDefinition;

using CameraAimAssistPresetsPacketOperation = v776::CameraAimAssistPresetsPacketOperation;

using CameraAimAssistPresetsPacket = v924::CameraAimAssistPresetsPacket;

namespace CameraInstructionOptions_nested {

namespace SetInstruction_nested {

struct EaseOption {
    EasingType easing_type{};
    float easing_time{};
};

struct PosOption {
    Vec3 pos{};
};

struct RotOption {
    float rot_x{};
    float rot_y{};
};

struct FacingOption {
    Vec3 facing_pos{};
};

struct ViewOffsetOption {
    float view_offset_x{};
    float view_offset_y{};
};

struct EntityOffsetOption {
    float entity_offset_x{};
    float entity_offset_y{};
    float entity_offset_z{};
};

}  // namespace SetInstruction_nested

struct SetInstruction {
    using EaseOption = SetInstruction_nested::EaseOption;
    using PosOption = SetInstruction_nested::PosOption;
    using RotOption = SetInstruction_nested::RotOption;
    using FacingOption = SetInstruction_nested::FacingOption;
    using ViewOffsetOption = SetInstruction_nested::ViewOffsetOption;
    using EntityOffsetOption = SetInstruction_nested::EntityOffsetOption;

    std::uint32_t preset_index{};
    std::optional<SetInstruction::EaseOption> ease{};
    std::optional<SetInstruction::PosOption> pos{};
    std::optional<SetInstruction::RotOption> rot{};
    std::optional<SetInstruction::FacingOption> facing{};
    std::optional<SetInstruction::ViewOffsetOption> view_offset{};
    std::optional<SetInstruction::EntityOffsetOption> entity_offset{};
    std::optional<bool> default_{};
    bool remove_ignore_starting_values_component{};
};

using FadeInstruction = base::CameraInstructionOptions::FadeInstruction;
using TargetInstruction = base::CameraInstructionOptions::TargetInstruction;
using FovInstruction = base::CameraInstructionOptions::FovInstruction;
using AttachToEntityInstruction = base::CameraInstructionOptions::AttachToEntityInstruction;

namespace SplineInstruction_nested {

struct SplineRotationOption {
    Vec3 rotation_key_frame_value{};
    float rotation_key_frame_time{};
    EasingType rotation_key_frames_easing_func{};
};

struct SplineProgressOption {
    float progress_key_frame_value{};
    float progress_key_frame_time{};
    EasingType progress_key_frames_easing_func{};
};

}  // namespace SplineInstruction_nested

struct SplineInstruction {
    using SplineRotationOption = SplineInstruction_nested::SplineRotationOption;
    using SplineProgressOption = SplineInstruction_nested::SplineProgressOption;

    float total_time{};
    SplineType curve_type{};
    std::vector<Vec3> curve{};
    std::vector<SplineInstruction::SplineProgressOption> progress_key_frames{};
    std::vector<SplineInstruction::SplineRotationOption> spline_rotation_option{};
    std::string spline_identifier{};
    bool load_from_json{};
};

}  // namespace CameraInstructionOptions_nested

struct CameraInstructionOptions {
    using SetInstruction = CameraInstructionOptions_nested::SetInstruction;
    using FadeInstruction = CameraInstructionOptions_nested::FadeInstruction;
    using TargetInstruction = CameraInstructionOptions_nested::TargetInstruction;
    using FovInstruction = CameraInstructionOptions_nested::FovInstruction;
    using AttachToEntityInstruction = CameraInstructionOptions_nested::AttachToEntityInstruction;
    using SplineInstruction = CameraInstructionOptions_nested::SplineInstruction;
};

struct CameraInstruction {
    std::optional<v944::CameraInstructionOptions::SetInstruction> set{};
    std::optional<bool> clear{};
    std::optional<v944::CameraInstructionOptions::FadeInstruction> fade{};
    std::optional<v944::CameraInstructionOptions::TargetInstruction> target{};
    std::optional<bool> remove_target{};
    std::optional<v944::CameraInstructionOptions::FovInstruction> field_of_view{};
    std::optional<v944::CameraInstructionOptions::SplineInstruction> spline{};
    std::optional<v944::CameraInstructionOptions::AttachToEntityInstruction> attach_to_entity{};
    std::optional<bool> detach_from_entity{};
};

struct CameraInstructionPacket {
    static constexpr int Id = 300;
    v944::CameraInstruction camera_instruction{};
};

using CameraSplinePacket = v924::CameraSplinePacket;

using ClientboundControlSchemeSetPacket = v800::ClientboundControlSchemeSetPacket;

}  // namespace v944

namespace v975 {

using TargetMode = v766::TargetMode;

using CameraAimAssistCommandPresetDefinition = v766::CameraAimAssistCommandPresetDefinition;

using CameraPreset = v818::CameraPreset;

using CameraPresets = v818::CameraPresets;

using CameraPresetsPacket = v818::CameraPresetsPacket;

using CameraAimAssistActorPriorityPacket = v924::CameraAimAssistActorPriorityPacket;

using ClientCameraAimAssistPacketAction = v776::ClientCameraAimAssistPacketAction;

using ClientCameraAimAssistPacket = v776::ClientCameraAimAssistPacket;

using CameraAimAssistPacket = v827::CameraAimAssistPacket;

using CameraAimAssistCategoryPriorities = v924::CameraAimAssistCategoryPriorities;

using CameraAimAssistCategoryDefinition = v924::CameraAimAssistCategoryDefinition;

using CameraAimAssistPresetExclusionDefinition = v924::CameraAimAssistPresetExclusionDefinition;

using CameraAimAssistPresetDefinition = v924::CameraAimAssistPresetDefinition;

using CameraAimAssistPresetsPacketOperation = v776::CameraAimAssistPresetsPacketOperation;

using CameraAimAssistPresetsPacket = v924::CameraAimAssistPresetsPacket;

using CameraInstructionOptions = v944::CameraInstructionOptions;

using CameraInstruction = v944::CameraInstruction;

using CameraInstructionPacket = v944::CameraInstructionPacket;

using CameraSplinePacket = v924::CameraSplinePacket;

using ClientboundControlSchemeSetPacket = v800::ClientboundControlSchemeSetPacket;

}  // namespace v975

namespace v1001 {

using TargetMode = v766::TargetMode;

using CameraAimAssistCommandPresetDefinition = v766::CameraAimAssistCommandPresetDefinition;

using CameraPreset = v818::CameraPreset;

using CameraPresets = v818::CameraPresets;

using CameraPresetsPacket = v818::CameraPresetsPacket;

using CameraAimAssistActorPriorityPacket = v924::CameraAimAssistActorPriorityPacket;

using ClientCameraAimAssistPacketAction = v776::ClientCameraAimAssistPacketAction;

using ClientCameraAimAssistPacket = v776::ClientCameraAimAssistPacket;

using CameraAimAssistPacket = v827::CameraAimAssistPacket;

using CameraAimAssistCategoryPriorities = v924::CameraAimAssistCategoryPriorities;

using CameraAimAssistCategoryDefinition = v924::CameraAimAssistCategoryDefinition;

using CameraAimAssistPresetExclusionDefinition = v924::CameraAimAssistPresetExclusionDefinition;

using CameraAimAssistPresetDefinition = v924::CameraAimAssistPresetDefinition;

using CameraAimAssistPresetsPacketOperation = v776::CameraAimAssistPresetsPacketOperation;

using CameraAimAssistPresetsPacket = v924::CameraAimAssistPresetsPacket;

using CameraInstructionOptions = v944::CameraInstructionOptions;

using CameraInstruction = v944::CameraInstruction;

using CameraInstructionPacket = v944::CameraInstructionPacket;

using CameraSplinePacket = v924::CameraSplinePacket;

using ClientboundControlSchemeSetPacket = v800::ClientboundControlSchemeSetPacket;

}  // namespace v1001

namespace v2168 {

using TargetMode = v766::TargetMode;

using CameraAimAssistCommandPresetDefinition = v766::CameraAimAssistCommandPresetDefinition;

using CameraPreset = v818::CameraPreset;

using CameraPresets = v818::CameraPresets;

using CameraPresetsPacket = v818::CameraPresetsPacket;

using CameraAimAssistActorPriorityPacket = v924::CameraAimAssistActorPriorityPacket;

using ClientCameraAimAssistPacketAction = v776::ClientCameraAimAssistPacketAction;

using ClientCameraAimAssistPacket = v776::ClientCameraAimAssistPacket;

using CameraAimAssistPacket = v827::CameraAimAssistPacket;

using CameraAimAssistCategoryPriorities = v924::CameraAimAssistCategoryPriorities;

using CameraAimAssistCategoryDefinition = v924::CameraAimAssistCategoryDefinition;

using CameraAimAssistPresetExclusionDefinition = v924::CameraAimAssistPresetExclusionDefinition;

using CameraAimAssistPresetDefinition = v924::CameraAimAssistPresetDefinition;

using CameraAimAssistPresetsPacketOperation = v776::CameraAimAssistPresetsPacketOperation;

using CameraAimAssistPresetsPacket = v924::CameraAimAssistPresetsPacket;

using CameraInstructionOptions = v944::CameraInstructionOptions;

using CameraInstruction = v944::CameraInstruction;

using CameraInstructionPacket = v944::CameraInstructionPacket;

using CameraSplinePacket = v924::CameraSplinePacket;

using ClientboundControlSchemeSetPacket = v800::ClientboundControlSchemeSetPacket;

}  // namespace v2168

namespace v2193 {

using TargetMode = v766::TargetMode;

using CameraAimAssistCommandPresetDefinition = v766::CameraAimAssistCommandPresetDefinition;

namespace CameraPreset_nested {

using AudioListener = base::CameraPreset::AudioListener;

}  // namespace CameraPreset_nested

struct CameraPreset {
    using AudioListener = CameraPreset_nested::AudioListener;

    std::string name{};
    std::string inherit_from{};
    std::optional<float> pos_x{};
    std::optional<float> pos_y{};
    std::optional<float> pos_z{};
    std::optional<float> rot_x{};
    std::optional<float> rot_y{};
    std::optional<float> camera_rotation_speed{};
    std::optional<bool> snap_to_target{};
    std::optional<Vec2> horizontal_rotation_limit{};
    std::optional<Vec2> vertical_rotation_limit{};
    std::optional<bool> continue_targeting{};
    std::optional<float> tracking_radius{};
    std::optional<Vec2> view_offset{};
    std::optional<Vec3> entity_offset{};
    std::optional<float> radius{};
    std::optional<float> yaw_limit_min{};
    std::optional<float> yaw_limit_max{};
    std::optional<v2193::CameraPreset::AudioListener> listener{};
    std::optional<bool> player_effects{};
    std::optional<v766::CameraAimAssistCommandPresetDefinition> aim_assist{};
    std::optional<Scheme> control_scheme{};
    bool apply_inherited_starting_rotation{};
    std::optional<Vec2> starting_rot{};
};

struct CameraPresets {
    std::vector<v2193::CameraPreset> presets{};
};

struct CameraPresetsPacket {
    static constexpr int Id = 198;
    v2193::CameraPresets camera_presets{};
};

using CameraAimAssistActorPriorityPacket = v924::CameraAimAssistActorPriorityPacket;

using ClientCameraAimAssistPacketAction = v776::ClientCameraAimAssistPacketAction;

using ClientCameraAimAssistPacket = v776::ClientCameraAimAssistPacket;

using CameraAimAssistPacket = v827::CameraAimAssistPacket;

using CameraAimAssistCategoryPriorities = v924::CameraAimAssistCategoryPriorities;

using CameraAimAssistCategoryDefinition = v924::CameraAimAssistCategoryDefinition;

using CameraAimAssistPresetExclusionDefinition = v924::CameraAimAssistPresetExclusionDefinition;

using CameraAimAssistPresetDefinition = v924::CameraAimAssistPresetDefinition;

using CameraAimAssistPresetsPacketOperation = v776::CameraAimAssistPresetsPacketOperation;

using CameraAimAssistPresetsPacket = v924::CameraAimAssistPresetsPacket;

using CameraInstructionOptions = v944::CameraInstructionOptions;

using CameraInstruction = v944::CameraInstruction;

using CameraInstructionPacket = v944::CameraInstructionPacket;

using CameraSplinePacket = v924::CameraSplinePacket;

using ClientboundControlSchemeSetPacket = v800::ClientboundControlSchemeSetPacket;

}  // namespace v2193

namespace v2225 {

using TargetMode = v766::TargetMode;

using CameraAimAssistCommandPresetDefinition = v766::CameraAimAssistCommandPresetDefinition;

using CameraPreset = v2193::CameraPreset;

using CameraPresets = v2193::CameraPresets;

using CameraPresetsPacket = v2193::CameraPresetsPacket;

using CameraAimAssistActorPriorityPacket = v924::CameraAimAssistActorPriorityPacket;

using ClientCameraAimAssistPacketAction = v776::ClientCameraAimAssistPacketAction;

using ClientCameraAimAssistPacket = v776::ClientCameraAimAssistPacket;

using CameraAimAssistPacket = v827::CameraAimAssistPacket;

using CameraAimAssistCategoryPriorities = v924::CameraAimAssistCategoryPriorities;

using CameraAimAssistCategoryDefinition = v924::CameraAimAssistCategoryDefinition;

using CameraAimAssistPresetExclusionDefinition = v924::CameraAimAssistPresetExclusionDefinition;

using CameraAimAssistPresetDefinition = v924::CameraAimAssistPresetDefinition;

using CameraAimAssistPresetsPacketOperation = v776::CameraAimAssistPresetsPacketOperation;

using CameraAimAssistPresetsPacket = v924::CameraAimAssistPresetsPacket;

using CameraInstructionOptions = v944::CameraInstructionOptions;

using CameraInstruction = v944::CameraInstruction;

using CameraInstructionPacket = v944::CameraInstructionPacket;

using CameraSplinePacket = v924::CameraSplinePacket;

using ClientboundControlSchemeSetPacket = v800::ClientboundControlSchemeSetPacket;

}  // namespace v2225

namespace detail {

template <int V>
struct TargetMode_;

template <int V> requires (V >= 766)
struct TargetMode_<V> { using type = v766::TargetMode; };

template <int V>
struct CameraAimAssistCommandPresetDefinition_;

template <int V> requires (V >= 766)
struct CameraAimAssistCommandPresetDefinition_<V> { using type = v766::CameraAimAssistCommandPresetDefinition; };

template <int V>
struct CameraPreset_;

template <int V> requires (V < 748)
struct CameraPreset_<V> { using type = base::CameraPreset; };

template <int V> requires (V >= 748 && V < 766)
struct CameraPreset_<V> { using type = v748::CameraPreset; };

template <int V> requires (V >= 766 && V < 776)
struct CameraPreset_<V> { using type = v766::CameraPreset; };

template <int V> requires (V >= 776 && V < 800)
struct CameraPreset_<V> { using type = v776::CameraPreset; };

template <int V> requires (V >= 800 && V < 818)
struct CameraPreset_<V> { using type = v800::CameraPreset; };

template <int V> requires (V >= 818 && V < 2193)
struct CameraPreset_<V> { using type = v818::CameraPreset; };

template <int V> requires (V >= 2193)
struct CameraPreset_<V> { using type = v2193::CameraPreset; };

template <int V>
struct CameraPresets_;

template <int V> requires (V < 748)
struct CameraPresets_<V> { using type = base::CameraPresets; };

template <int V> requires (V >= 748 && V < 766)
struct CameraPresets_<V> { using type = v748::CameraPresets; };

template <int V> requires (V >= 766 && V < 776)
struct CameraPresets_<V> { using type = v766::CameraPresets; };

template <int V> requires (V >= 776 && V < 800)
struct CameraPresets_<V> { using type = v776::CameraPresets; };

template <int V> requires (V >= 800 && V < 818)
struct CameraPresets_<V> { using type = v800::CameraPresets; };

template <int V> requires (V >= 818 && V < 2193)
struct CameraPresets_<V> { using type = v818::CameraPresets; };

template <int V> requires (V >= 2193)
struct CameraPresets_<V> { using type = v2193::CameraPresets; };

template <int V>
struct CameraPresetsPacket_;

template <int V> requires (V < 748)
struct CameraPresetsPacket_<V> { using type = base::CameraPresetsPacket; };

template <int V> requires (V >= 748 && V < 766)
struct CameraPresetsPacket_<V> { using type = v748::CameraPresetsPacket; };

template <int V> requires (V >= 766 && V < 776)
struct CameraPresetsPacket_<V> { using type = v766::CameraPresetsPacket; };

template <int V> requires (V >= 776 && V < 800)
struct CameraPresetsPacket_<V> { using type = v776::CameraPresetsPacket; };

template <int V> requires (V >= 800 && V < 818)
struct CameraPresetsPacket_<V> { using type = v800::CameraPresetsPacket; };

template <int V> requires (V >= 818 && V < 2193)
struct CameraPresetsPacket_<V> { using type = v818::CameraPresetsPacket; };

template <int V> requires (V >= 2193)
struct CameraPresetsPacket_<V> { using type = v2193::CameraPresetsPacket; };

template <int V>
struct CameraAimAssistActorPriorityPacket_;

template <int V> requires (V >= 924)
struct CameraAimAssistActorPriorityPacket_<V> { using type = v924::CameraAimAssistActorPriorityPacket; };

template <int V>
struct ClientCameraAimAssistPacketAction_;

template <int V> requires (V >= 776)
struct ClientCameraAimAssistPacketAction_<V> { using type = v776::ClientCameraAimAssistPacketAction; };

template <int V>
struct ClientCameraAimAssistPacket_;

template <int V> requires (V >= 776)
struct ClientCameraAimAssistPacket_<V> { using type = v776::ClientCameraAimAssistPacket; };

template <int V>
struct CameraAimAssistPacket_;

template <int V> requires (V < 766)
struct CameraAimAssistPacket_<V> { using type = base::CameraAimAssistPacket; };

template <int V> requires (V >= 766 && V < 827)
struct CameraAimAssistPacket_<V> { using type = v766::CameraAimAssistPacket; };

template <int V> requires (V >= 827)
struct CameraAimAssistPacket_<V> { using type = v827::CameraAimAssistPacket; };

template <int V>
struct CameraAimAssistCategoryPriorities_;

template <int V> requires (V >= 766 && V < 898)
struct CameraAimAssistCategoryPriorities_<V> { using type = v766::CameraAimAssistCategoryPriorities; };

template <int V> requires (V >= 898 && V < 924)
struct CameraAimAssistCategoryPriorities_<V> { using type = v898::CameraAimAssistCategoryPriorities; };

template <int V> requires (V >= 924)
struct CameraAimAssistCategoryPriorities_<V> { using type = v924::CameraAimAssistCategoryPriorities; };

template <int V>
struct CameraAimAssistCategoryDefinition_;

template <int V> requires (V >= 766 && V < 898)
struct CameraAimAssistCategoryDefinition_<V> { using type = v766::CameraAimAssistCategoryDefinition; };

template <int V> requires (V >= 898 && V < 924)
struct CameraAimAssistCategoryDefinition_<V> { using type = v898::CameraAimAssistCategoryDefinition; };

template <int V> requires (V >= 924)
struct CameraAimAssistCategoryDefinition_<V> { using type = v924::CameraAimAssistCategoryDefinition; };

template <int V>
struct CameraAimAssistPresetExclusionDefinition_;

template <int V> requires (V >= 898 && V < 924)
struct CameraAimAssistPresetExclusionDefinition_<V> { using type = v898::CameraAimAssistPresetExclusionDefinition; };

template <int V> requires (V >= 924)
struct CameraAimAssistPresetExclusionDefinition_<V> { using type = v924::CameraAimAssistPresetExclusionDefinition; };

template <int V>
struct CameraAimAssistPresetDefinition_;

template <int V> requires (V >= 766 && V < 776)
struct CameraAimAssistPresetDefinition_<V> { using type = v766::CameraAimAssistPresetDefinition; };

template <int V> requires (V >= 776 && V < 898)
struct CameraAimAssistPresetDefinition_<V> { using type = v776::CameraAimAssistPresetDefinition; };

template <int V> requires (V >= 898 && V < 924)
struct CameraAimAssistPresetDefinition_<V> { using type = v898::CameraAimAssistPresetDefinition; };

template <int V> requires (V >= 924)
struct CameraAimAssistPresetDefinition_<V> { using type = v924::CameraAimAssistPresetDefinition; };

template <int V>
struct CameraAimAssistPresetsPacketOperation_;

template <int V> requires (V >= 776)
struct CameraAimAssistPresetsPacketOperation_<V> { using type = v776::CameraAimAssistPresetsPacketOperation; };

template <int V>
struct CameraAimAssistCategoriesDefinition_;

template <int V> requires (V >= 766 && V < 776)
struct CameraAimAssistCategoriesDefinition_<V> { using type = v766::CameraAimAssistCategoriesDefinition; };

template <int V>
struct CameraAimAssistPresetsPacket_;

template <int V> requires (V >= 766 && V < 776)
struct CameraAimAssistPresetsPacket_<V> { using type = v766::CameraAimAssistPresetsPacket; };

template <int V> requires (V >= 776 && V < 898)
struct CameraAimAssistPresetsPacket_<V> { using type = v776::CameraAimAssistPresetsPacket; };

template <int V> requires (V >= 898 && V < 924)
struct CameraAimAssistPresetsPacket_<V> { using type = v898::CameraAimAssistPresetsPacket; };

template <int V> requires (V >= 924)
struct CameraAimAssistPresetsPacket_<V> { using type = v924::CameraAimAssistPresetsPacket; };

template <int V>
struct CameraInstructionOptions_;

template <int V> requires (V < 748)
struct CameraInstructionOptions_<V> { using type = base::CameraInstructionOptions; };

template <int V> requires (V >= 748 && V < 818)
struct CameraInstructionOptions_<V> { using type = v748::CameraInstructionOptions; };

template <int V> requires (V >= 818 && V < 924)
struct CameraInstructionOptions_<V> { using type = v818::CameraInstructionOptions; };

template <int V> requires (V >= 924 && V < 944)
struct CameraInstructionOptions_<V> { using type = v924::CameraInstructionOptions; };

template <int V> requires (V >= 944)
struct CameraInstructionOptions_<V> { using type = v944::CameraInstructionOptions; };

template <int V>
struct CameraInstruction_;

template <int V> requires (V < 748)
struct CameraInstruction_<V> { using type = base::CameraInstruction; };

template <int V> requires (V >= 748 && V < 818)
struct CameraInstruction_<V> { using type = v748::CameraInstruction; };

template <int V> requires (V >= 818 && V < 827)
struct CameraInstruction_<V> { using type = v818::CameraInstruction; };

template <int V> requires (V >= 827 && V < 859)
struct CameraInstruction_<V> { using type = v827::CameraInstruction; };

template <int V> requires (V >= 859 && V < 924)
struct CameraInstruction_<V> { using type = v859::CameraInstruction; };

template <int V> requires (V >= 924 && V < 944)
struct CameraInstruction_<V> { using type = v924::CameraInstruction; };

template <int V> requires (V >= 944)
struct CameraInstruction_<V> { using type = v944::CameraInstruction; };

template <int V>
struct CameraInstructionPacket_;

template <int V> requires (V < 748)
struct CameraInstructionPacket_<V> { using type = base::CameraInstructionPacket; };

template <int V> requires (V >= 748 && V < 818)
struct CameraInstructionPacket_<V> { using type = v748::CameraInstructionPacket; };

template <int V> requires (V >= 818 && V < 827)
struct CameraInstructionPacket_<V> { using type = v818::CameraInstructionPacket; };

template <int V> requires (V >= 827 && V < 859)
struct CameraInstructionPacket_<V> { using type = v827::CameraInstructionPacket; };

template <int V> requires (V >= 859 && V < 924)
struct CameraInstructionPacket_<V> { using type = v859::CameraInstructionPacket; };

template <int V> requires (V >= 924 && V < 944)
struct CameraInstructionPacket_<V> { using type = v924::CameraInstructionPacket; };

template <int V> requires (V >= 944)
struct CameraInstructionPacket_<V> { using type = v944::CameraInstructionPacket; };

template <int V>
struct CameraSplinePacket_;

template <int V> requires (V >= 924)
struct CameraSplinePacket_<V> { using type = v924::CameraSplinePacket; };

template <int V>
struct ClientboundControlSchemeSetPacket_;

template <int V> requires (V >= 800)
struct ClientboundControlSchemeSetPacket_<V> { using type = v800::ClientboundControlSchemeSetPacket; };

}  // namespace detail

template <int V> using TargetMode_ = typename detail::TargetMode_<V>::type;
template <int V> using CameraAimAssistCommandPresetDefinition_ = typename detail::CameraAimAssistCommandPresetDefinition_<V>::type;
template <int V> using CameraPreset_ = typename detail::CameraPreset_<V>::type;
template <int V> using CameraPresets_ = typename detail::CameraPresets_<V>::type;
template <int V> using CameraPresetsPacket_ = typename detail::CameraPresetsPacket_<V>::type;
template <int V> using CameraAimAssistActorPriorityPacket_ = typename detail::CameraAimAssistActorPriorityPacket_<V>::type;
template <int V> using ClientCameraAimAssistPacketAction_ = typename detail::ClientCameraAimAssistPacketAction_<V>::type;
template <int V> using ClientCameraAimAssistPacket_ = typename detail::ClientCameraAimAssistPacket_<V>::type;
template <int V> using CameraAimAssistPacket_ = typename detail::CameraAimAssistPacket_<V>::type;
template <int V> using CameraAimAssistCategoryPriorities_ = typename detail::CameraAimAssistCategoryPriorities_<V>::type;
template <int V> using CameraAimAssistCategoryDefinition_ = typename detail::CameraAimAssistCategoryDefinition_<V>::type;
template <int V> using CameraAimAssistPresetExclusionDefinition_ = typename detail::CameraAimAssistPresetExclusionDefinition_<V>::type;
template <int V> using CameraAimAssistPresetDefinition_ = typename detail::CameraAimAssistPresetDefinition_<V>::type;
template <int V> using CameraAimAssistPresetsPacketOperation_ = typename detail::CameraAimAssistPresetsPacketOperation_<V>::type;
template <int V> using CameraAimAssistCategoriesDefinition_ = typename detail::CameraAimAssistCategoriesDefinition_<V>::type;
template <int V> using CameraAimAssistPresetsPacket_ = typename detail::CameraAimAssistPresetsPacket_<V>::type;
template <int V> using CameraInstructionOptions_ = typename detail::CameraInstructionOptions_<V>::type;
template <int V> using CameraInstruction_ = typename detail::CameraInstruction_<V>::type;
template <int V> using CameraInstructionPacket_ = typename detail::CameraInstructionPacket_<V>::type;
template <int V> using CameraSplinePacket_ = typename detail::CameraSplinePacket_<V>::type;
template <int V> using ClientboundControlSchemeSetPacket_ = typename detail::ClientboundControlSchemeSetPacket_<V>::type;

template <int V>
struct packet_of<V, 73> { using type = CameraPacket; };

template <int V>
struct packet_of<V, 159> { using type = CameraShakePacket; };

template <int V>
struct packet_of<V, 198> { using type = CameraPresetsPacket_<V>; };

template <int V>
struct packet_of<V, 300> { using type = CameraInstructionPacket_<V>; };

template <int V>
struct packet_of<V, 316> { using type = CameraAimAssistPacket_<V>; };

template <int V> requires (V >= 766)
struct packet_of<V, 320> { using type = CameraAimAssistPresetsPacket_<V>; };

template <int V> requires (V >= 776)
struct packet_of<V, 321> { using type = ClientCameraAimAssistPacket_<V>; };

template <int V> requires (V >= 800)
struct packet_of<V, 327> { using type = ClientboundControlSchemeSetPacket_<V>; };

template <int V> requires (V >= 924)
struct packet_of<V, 338> { using type = CameraSplinePacket_<V>; };

template <int V> requires (V >= 924)
struct packet_of<V, 339> { using type = CameraAimAssistActorPriorityPacket_<V>; };

namespace detail {

template <>
inline constexpr std::array<Scheme, 5> values_v<Scheme>{{
    Scheme::LockedPlayerRelativeStrafe,
    Scheme::CameraRelative,
    Scheme::CameraRelativeStrafe,
    Scheme::PlayerRelative,
    Scheme::PlayerRelativeStrafe,
}};

template <>
inline constexpr std::array<std::string_view, 5> names_v<Scheme>{{
    "lockedplayerrelativestrafe",
    "camerarelative",
    "camerarelativestrafe",
    "playerrelative",
    "playerrelativestrafe",
}};

template <>
inline constexpr std::string_view type_name_v<Scheme>{"Scheme"};

template <>
inline constexpr std::array<v766::TargetMode, 2> values_v<v766::TargetMode>{{
    v766::TargetMode::Angle,
    v766::TargetMode::Distance,
}};

template <>
inline constexpr std::array<std::string_view, 2> names_v<v766::TargetMode>{{
    "angle",
    "distance",
}};

template <>
inline constexpr std::string_view type_name_v<v766::TargetMode>{"TargetMode"};

template <>
inline constexpr std::array<base::CameraPreset::AudioListener, 2> values_v<base::CameraPreset::AudioListener>{{
    base::CameraPreset::AudioListener::Camera,
    base::CameraPreset::AudioListener::Player,
}};

template <>
inline constexpr std::array<std::string_view, 2> names_v<base::CameraPreset::AudioListener>{{
    "camera",
    "player",
}};

template <>
inline constexpr std::string_view type_name_v<base::CameraPreset::AudioListener>{"CameraPreset::AudioListener"};

template <>
inline constexpr std::array<CameraShakeType, 2> values_v<CameraShakeType>{{
    CameraShakeType::Positional,
    CameraShakeType::Rotational,
}};

template <>
inline constexpr std::array<std::string_view, 2> names_v<CameraShakeType>{{
    "positional",
    "rotational",
}};

template <>
inline constexpr std::string_view type_name_v<CameraShakeType>{"CameraShakeType"};

template <>
inline constexpr std::array<CameraShakeAction, 2> values_v<CameraShakeAction>{{
    CameraShakeAction::Add,
    CameraShakeAction::Stop,
}};

template <>
inline constexpr std::array<std::string_view, 2> names_v<CameraShakeAction>{{
    "add",
    "stop",
}};

template <>
inline constexpr std::string_view type_name_v<CameraShakeAction>{"CameraShakeAction"};

template <>
inline constexpr std::array<v776::ClientCameraAimAssistPacketAction, 3> values_v<v776::ClientCameraAimAssistPacketAction>{{
    v776::ClientCameraAimAssistPacketAction::SetFromCameraPreset,
    v776::ClientCameraAimAssistPacketAction::Clear,
    v776::ClientCameraAimAssistPacketAction::Count,
}};

template <>
inline constexpr std::array<std::string_view, 3> names_v<v776::ClientCameraAimAssistPacketAction>{{
    "setfromcamerapreset",
    "clear",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<v776::ClientCameraAimAssistPacketAction>{"ClientCameraAimAssistPacketAction"};

template <>
inline constexpr std::array<base::CameraAimAssistPacket::Action, 3> values_v<base::CameraAimAssistPacket::Action>{{
    base::CameraAimAssistPacket::Action::Set,
    base::CameraAimAssistPacket::Action::Clear,
    base::CameraAimAssistPacket::Action::Count,
}};

template <>
inline constexpr std::array<std::string_view, 3> names_v<base::CameraAimAssistPacket::Action>{{
    "set",
    "clear",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<base::CameraAimAssistPacket::Action>{"CameraAimAssistPacket::Action"};

template <>
inline constexpr std::array<base::CameraAimAssistPacket::TargetMode, 3> values_v<base::CameraAimAssistPacket::TargetMode>{{
    base::CameraAimAssistPacket::TargetMode::Angle,
    base::CameraAimAssistPacket::TargetMode::Distance,
    base::CameraAimAssistPacket::TargetMode::Count,
}};

template <>
inline constexpr std::array<std::string_view, 3> names_v<base::CameraAimAssistPacket::TargetMode>{{
    "angle",
    "distance",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<base::CameraAimAssistPacket::TargetMode>{"CameraAimAssistPacket::TargetMode"};

template <>
inline constexpr std::array<v776::CameraAimAssistPresetsPacketOperation, 2> values_v<v776::CameraAimAssistPresetsPacketOperation>{{
    v776::CameraAimAssistPresetsPacketOperation::Set,
    v776::CameraAimAssistPresetsPacketOperation::AddToExisting,
}};

template <>
inline constexpr std::array<std::string_view, 2> names_v<v776::CameraAimAssistPresetsPacketOperation>{{
    "set",
    "addtoexisting",
}};

template <>
inline constexpr std::string_view type_name_v<v776::CameraAimAssistPresetsPacketOperation>{"CameraAimAssistPresetsPacketOperation"};

template <>
inline constexpr std::array<SplineType, 2> values_v<SplineType>{{
    SplineType::CatmullRom,
    SplineType::Linear,
}};

template <>
inline constexpr std::array<std::string_view, 2> names_v<SplineType>{{
    "catmullrom",
    "linear",
}};

template <>
inline constexpr std::string_view type_name_v<SplineType>{"SplineType"};

}  // namespace detail

namespace detail {

template <>
inline constexpr bool is_reflected_struct_v<v766::CameraAimAssistCommandPresetDefinition> = true;

template <>
inline constexpr std::string_view struct_name_v<v766::CameraAimAssistCommandPresetDefinition>{"CameraAimAssistCommandPresetDefinition"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v766::CameraAimAssistCommandPresetDefinition>{{
    "preset_id",
    "target_mode",
    "angle",
    "distance",
}};

template <>
struct field_accessor<v766::CameraAimAssistCommandPresetDefinition> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.preset_id;
        }
        else if constexpr (I == 1) {
            return value.target_mode;
        }
        else if constexpr (I == 2) {
            return value.angle;
        }
        else {
            return value.distance;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::CameraPreset> = true;

template <>
inline constexpr std::string_view struct_name_v<base::CameraPreset>{"CameraPreset"};

template <>
inline constexpr std::array<std::string_view, 14> field_names_v<base::CameraPreset>{{
    "name",
    "inherit_from",
    "pos_x",
    "pos_y",
    "pos_z",
    "rot_x",
    "rot_y",
    "camera_rotation_speed",
    "snap_to_target",
    "view_offset",
    "entity_offset",
    "radius",
    "listener",
    "player_effects",
}};

template <>
struct field_accessor<base::CameraPreset> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.name;
        }
        else if constexpr (I == 1) {
            return value.inherit_from;
        }
        else if constexpr (I == 2) {
            return value.pos_x;
        }
        else if constexpr (I == 3) {
            return value.pos_y;
        }
        else if constexpr (I == 4) {
            return value.pos_z;
        }
        else if constexpr (I == 5) {
            return value.rot_x;
        }
        else if constexpr (I == 6) {
            return value.rot_y;
        }
        else if constexpr (I == 7) {
            return value.camera_rotation_speed;
        }
        else if constexpr (I == 8) {
            return value.snap_to_target;
        }
        else if constexpr (I == 9) {
            return value.view_offset;
        }
        else if constexpr (I == 10) {
            return value.entity_offset;
        }
        else if constexpr (I == 11) {
            return value.radius;
        }
        else if constexpr (I == 12) {
            return value.listener;
        }
        else {
            return value.player_effects;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v748::CameraPreset> = true;

template <>
inline constexpr std::string_view struct_name_v<v748::CameraPreset>{"CameraPreset"};

template <>
inline constexpr std::array<std::string_view, 18> field_names_v<v748::CameraPreset>{{
    "name",
    "inherit_from",
    "pos_x",
    "pos_y",
    "pos_z",
    "rot_x",
    "rot_y",
    "camera_rotation_speed",
    "snap_to_target",
    "horizontal_rotation_limit",
    "vertical_rotation_limit",
    "continue_targeting",
    "view_offset",
    "entity_offset",
    "radius",
    "listener",
    "player_effects",
    "align_target_and_camera_forward",
}};

template <>
struct field_accessor<v748::CameraPreset> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.name;
        }
        else if constexpr (I == 1) {
            return value.inherit_from;
        }
        else if constexpr (I == 2) {
            return value.pos_x;
        }
        else if constexpr (I == 3) {
            return value.pos_y;
        }
        else if constexpr (I == 4) {
            return value.pos_z;
        }
        else if constexpr (I == 5) {
            return value.rot_x;
        }
        else if constexpr (I == 6) {
            return value.rot_y;
        }
        else if constexpr (I == 7) {
            return value.camera_rotation_speed;
        }
        else if constexpr (I == 8) {
            return value.snap_to_target;
        }
        else if constexpr (I == 9) {
            return value.horizontal_rotation_limit;
        }
        else if constexpr (I == 10) {
            return value.vertical_rotation_limit;
        }
        else if constexpr (I == 11) {
            return value.continue_targeting;
        }
        else if constexpr (I == 12) {
            return value.view_offset;
        }
        else if constexpr (I == 13) {
            return value.entity_offset;
        }
        else if constexpr (I == 14) {
            return value.radius;
        }
        else if constexpr (I == 15) {
            return value.listener;
        }
        else if constexpr (I == 16) {
            return value.player_effects;
        }
        else {
            return value.align_target_and_camera_forward;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v766::CameraPreset> = true;

template <>
inline constexpr std::string_view struct_name_v<v766::CameraPreset>{"CameraPreset"};

template <>
inline constexpr std::array<std::string_view, 20> field_names_v<v766::CameraPreset>{{
    "name",
    "inherit_from",
    "pos_x",
    "pos_y",
    "pos_z",
    "rot_x",
    "rot_y",
    "camera_rotation_speed",
    "snap_to_target",
    "horizontal_rotation_limit",
    "vertical_rotation_limit",
    "continue_targeting",
    "tracking_radius",
    "view_offset",
    "entity_offset",
    "radius",
    "listener",
    "player_effects",
    "align_target_and_camera_forward",
    "aim_assist",
}};

template <>
struct field_accessor<v766::CameraPreset> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.name;
        }
        else if constexpr (I == 1) {
            return value.inherit_from;
        }
        else if constexpr (I == 2) {
            return value.pos_x;
        }
        else if constexpr (I == 3) {
            return value.pos_y;
        }
        else if constexpr (I == 4) {
            return value.pos_z;
        }
        else if constexpr (I == 5) {
            return value.rot_x;
        }
        else if constexpr (I == 6) {
            return value.rot_y;
        }
        else if constexpr (I == 7) {
            return value.camera_rotation_speed;
        }
        else if constexpr (I == 8) {
            return value.snap_to_target;
        }
        else if constexpr (I == 9) {
            return value.horizontal_rotation_limit;
        }
        else if constexpr (I == 10) {
            return value.vertical_rotation_limit;
        }
        else if constexpr (I == 11) {
            return value.continue_targeting;
        }
        else if constexpr (I == 12) {
            return value.tracking_radius;
        }
        else if constexpr (I == 13) {
            return value.view_offset;
        }
        else if constexpr (I == 14) {
            return value.entity_offset;
        }
        else if constexpr (I == 15) {
            return value.radius;
        }
        else if constexpr (I == 16) {
            return value.listener;
        }
        else if constexpr (I == 17) {
            return value.player_effects;
        }
        else if constexpr (I == 18) {
            return value.align_target_and_camera_forward;
        }
        else {
            return value.aim_assist;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v776::CameraPreset> = true;

template <>
inline constexpr std::string_view struct_name_v<v776::CameraPreset>{"CameraPreset"};

template <>
inline constexpr std::array<std::string_view, 22> field_names_v<v776::CameraPreset>{{
    "name",
    "inherit_from",
    "pos_x",
    "pos_y",
    "pos_z",
    "rot_x",
    "rot_y",
    "camera_rotation_speed",
    "snap_to_target",
    "horizontal_rotation_limit",
    "vertical_rotation_limit",
    "continue_targeting",
    "tracking_radius",
    "view_offset",
    "entity_offset",
    "radius",
    "yaw_limit_min",
    "yaw_limit_max",
    "listener",
    "player_effects",
    "align_target_and_camera_forward",
    "aim_assist",
}};

template <>
struct field_accessor<v776::CameraPreset> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.name;
        }
        else if constexpr (I == 1) {
            return value.inherit_from;
        }
        else if constexpr (I == 2) {
            return value.pos_x;
        }
        else if constexpr (I == 3) {
            return value.pos_y;
        }
        else if constexpr (I == 4) {
            return value.pos_z;
        }
        else if constexpr (I == 5) {
            return value.rot_x;
        }
        else if constexpr (I == 6) {
            return value.rot_y;
        }
        else if constexpr (I == 7) {
            return value.camera_rotation_speed;
        }
        else if constexpr (I == 8) {
            return value.snap_to_target;
        }
        else if constexpr (I == 9) {
            return value.horizontal_rotation_limit;
        }
        else if constexpr (I == 10) {
            return value.vertical_rotation_limit;
        }
        else if constexpr (I == 11) {
            return value.continue_targeting;
        }
        else if constexpr (I == 12) {
            return value.tracking_radius;
        }
        else if constexpr (I == 13) {
            return value.view_offset;
        }
        else if constexpr (I == 14) {
            return value.entity_offset;
        }
        else if constexpr (I == 15) {
            return value.radius;
        }
        else if constexpr (I == 16) {
            return value.yaw_limit_min;
        }
        else if constexpr (I == 17) {
            return value.yaw_limit_max;
        }
        else if constexpr (I == 18) {
            return value.listener;
        }
        else if constexpr (I == 19) {
            return value.player_effects;
        }
        else if constexpr (I == 20) {
            return value.align_target_and_camera_forward;
        }
        else {
            return value.aim_assist;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v800::CameraPreset> = true;

template <>
inline constexpr std::string_view struct_name_v<v800::CameraPreset>{"CameraPreset"};

template <>
inline constexpr std::array<std::string_view, 23> field_names_v<v800::CameraPreset>{{
    "name",
    "inherit_from",
    "pos_x",
    "pos_y",
    "pos_z",
    "rot_x",
    "rot_y",
    "camera_rotation_speed",
    "snap_to_target",
    "horizontal_rotation_limit",
    "vertical_rotation_limit",
    "continue_targeting",
    "tracking_radius",
    "view_offset",
    "entity_offset",
    "radius",
    "yaw_limit_min",
    "yaw_limit_max",
    "listener",
    "player_effects",
    "align_target_and_camera_forward",
    "aim_assist",
    "control_scheme",
}};

template <>
struct field_accessor<v800::CameraPreset> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.name;
        }
        else if constexpr (I == 1) {
            return value.inherit_from;
        }
        else if constexpr (I == 2) {
            return value.pos_x;
        }
        else if constexpr (I == 3) {
            return value.pos_y;
        }
        else if constexpr (I == 4) {
            return value.pos_z;
        }
        else if constexpr (I == 5) {
            return value.rot_x;
        }
        else if constexpr (I == 6) {
            return value.rot_y;
        }
        else if constexpr (I == 7) {
            return value.camera_rotation_speed;
        }
        else if constexpr (I == 8) {
            return value.snap_to_target;
        }
        else if constexpr (I == 9) {
            return value.horizontal_rotation_limit;
        }
        else if constexpr (I == 10) {
            return value.vertical_rotation_limit;
        }
        else if constexpr (I == 11) {
            return value.continue_targeting;
        }
        else if constexpr (I == 12) {
            return value.tracking_radius;
        }
        else if constexpr (I == 13) {
            return value.view_offset;
        }
        else if constexpr (I == 14) {
            return value.entity_offset;
        }
        else if constexpr (I == 15) {
            return value.radius;
        }
        else if constexpr (I == 16) {
            return value.yaw_limit_min;
        }
        else if constexpr (I == 17) {
            return value.yaw_limit_max;
        }
        else if constexpr (I == 18) {
            return value.listener;
        }
        else if constexpr (I == 19) {
            return value.player_effects;
        }
        else if constexpr (I == 20) {
            return value.align_target_and_camera_forward;
        }
        else if constexpr (I == 21) {
            return value.aim_assist;
        }
        else {
            return value.control_scheme;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v818::CameraPreset> = true;

template <>
inline constexpr std::string_view struct_name_v<v818::CameraPreset>{"CameraPreset"};

template <>
inline constexpr std::array<std::string_view, 22> field_names_v<v818::CameraPreset>{{
    "name",
    "inherit_from",
    "pos_x",
    "pos_y",
    "pos_z",
    "rot_x",
    "rot_y",
    "camera_rotation_speed",
    "snap_to_target",
    "horizontal_rotation_limit",
    "vertical_rotation_limit",
    "continue_targeting",
    "tracking_radius",
    "view_offset",
    "entity_offset",
    "radius",
    "yaw_limit_min",
    "yaw_limit_max",
    "listener",
    "player_effects",
    "aim_assist",
    "control_scheme",
}};

template <>
struct field_accessor<v818::CameraPreset> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.name;
        }
        else if constexpr (I == 1) {
            return value.inherit_from;
        }
        else if constexpr (I == 2) {
            return value.pos_x;
        }
        else if constexpr (I == 3) {
            return value.pos_y;
        }
        else if constexpr (I == 4) {
            return value.pos_z;
        }
        else if constexpr (I == 5) {
            return value.rot_x;
        }
        else if constexpr (I == 6) {
            return value.rot_y;
        }
        else if constexpr (I == 7) {
            return value.camera_rotation_speed;
        }
        else if constexpr (I == 8) {
            return value.snap_to_target;
        }
        else if constexpr (I == 9) {
            return value.horizontal_rotation_limit;
        }
        else if constexpr (I == 10) {
            return value.vertical_rotation_limit;
        }
        else if constexpr (I == 11) {
            return value.continue_targeting;
        }
        else if constexpr (I == 12) {
            return value.tracking_radius;
        }
        else if constexpr (I == 13) {
            return value.view_offset;
        }
        else if constexpr (I == 14) {
            return value.entity_offset;
        }
        else if constexpr (I == 15) {
            return value.radius;
        }
        else if constexpr (I == 16) {
            return value.yaw_limit_min;
        }
        else if constexpr (I == 17) {
            return value.yaw_limit_max;
        }
        else if constexpr (I == 18) {
            return value.listener;
        }
        else if constexpr (I == 19) {
            return value.player_effects;
        }
        else if constexpr (I == 20) {
            return value.aim_assist;
        }
        else {
            return value.control_scheme;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2193::CameraPreset> = true;

template <>
inline constexpr std::string_view struct_name_v<v2193::CameraPreset>{"CameraPreset"};

template <>
inline constexpr std::array<std::string_view, 24> field_names_v<v2193::CameraPreset>{{
    "name",
    "inherit_from",
    "pos_x",
    "pos_y",
    "pos_z",
    "rot_x",
    "rot_y",
    "camera_rotation_speed",
    "snap_to_target",
    "horizontal_rotation_limit",
    "vertical_rotation_limit",
    "continue_targeting",
    "tracking_radius",
    "view_offset",
    "entity_offset",
    "radius",
    "yaw_limit_min",
    "yaw_limit_max",
    "listener",
    "player_effects",
    "aim_assist",
    "control_scheme",
    "apply_inherited_starting_rotation",
    "starting_rot",
}};

template <>
struct field_accessor<v2193::CameraPreset> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.name;
        }
        else if constexpr (I == 1) {
            return value.inherit_from;
        }
        else if constexpr (I == 2) {
            return value.pos_x;
        }
        else if constexpr (I == 3) {
            return value.pos_y;
        }
        else if constexpr (I == 4) {
            return value.pos_z;
        }
        else if constexpr (I == 5) {
            return value.rot_x;
        }
        else if constexpr (I == 6) {
            return value.rot_y;
        }
        else if constexpr (I == 7) {
            return value.camera_rotation_speed;
        }
        else if constexpr (I == 8) {
            return value.snap_to_target;
        }
        else if constexpr (I == 9) {
            return value.horizontal_rotation_limit;
        }
        else if constexpr (I == 10) {
            return value.vertical_rotation_limit;
        }
        else if constexpr (I == 11) {
            return value.continue_targeting;
        }
        else if constexpr (I == 12) {
            return value.tracking_radius;
        }
        else if constexpr (I == 13) {
            return value.view_offset;
        }
        else if constexpr (I == 14) {
            return value.entity_offset;
        }
        else if constexpr (I == 15) {
            return value.radius;
        }
        else if constexpr (I == 16) {
            return value.yaw_limit_min;
        }
        else if constexpr (I == 17) {
            return value.yaw_limit_max;
        }
        else if constexpr (I == 18) {
            return value.listener;
        }
        else if constexpr (I == 19) {
            return value.player_effects;
        }
        else if constexpr (I == 20) {
            return value.aim_assist;
        }
        else if constexpr (I == 21) {
            return value.control_scheme;
        }
        else if constexpr (I == 22) {
            return value.apply_inherited_starting_rotation;
        }
        else {
            return value.starting_rot;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::CameraPresets> = true;

template <>
inline constexpr std::string_view struct_name_v<base::CameraPresets>{"CameraPresets"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::CameraPresets>{{
    "presets",
}};

template <>
struct field_accessor<base::CameraPresets> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.presets;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v748::CameraPresets> = true;

template <>
inline constexpr std::string_view struct_name_v<v748::CameraPresets>{"CameraPresets"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v748::CameraPresets>{{
    "presets",
}};

template <>
struct field_accessor<v748::CameraPresets> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.presets;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v766::CameraPresets> = true;

template <>
inline constexpr std::string_view struct_name_v<v766::CameraPresets>{"CameraPresets"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v766::CameraPresets>{{
    "presets",
}};

template <>
struct field_accessor<v766::CameraPresets> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.presets;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v776::CameraPresets> = true;

template <>
inline constexpr std::string_view struct_name_v<v776::CameraPresets>{"CameraPresets"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v776::CameraPresets>{{
    "presets",
}};

template <>
struct field_accessor<v776::CameraPresets> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.presets;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v800::CameraPresets> = true;

template <>
inline constexpr std::string_view struct_name_v<v800::CameraPresets>{"CameraPresets"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v800::CameraPresets>{{
    "presets",
}};

template <>
struct field_accessor<v800::CameraPresets> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.presets;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v818::CameraPresets> = true;

template <>
inline constexpr std::string_view struct_name_v<v818::CameraPresets>{"CameraPresets"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v818::CameraPresets>{{
    "presets",
}};

template <>
struct field_accessor<v818::CameraPresets> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.presets;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2193::CameraPresets> = true;

template <>
inline constexpr std::string_view struct_name_v<v2193::CameraPresets>{"CameraPresets"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2193::CameraPresets>{{
    "presets",
}};

template <>
struct field_accessor<v2193::CameraPresets> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.presets;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::CameraPresetsPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::CameraPresetsPacket>{"CameraPresetsPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::CameraPresetsPacket>{{
    "camera_presets",
}};

template <>
struct field_accessor<base::CameraPresetsPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.camera_presets;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v748::CameraPresetsPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v748::CameraPresetsPacket>{"CameraPresetsPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v748::CameraPresetsPacket>{{
    "camera_presets",
}};

template <>
struct field_accessor<v748::CameraPresetsPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.camera_presets;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v766::CameraPresetsPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v766::CameraPresetsPacket>{"CameraPresetsPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v766::CameraPresetsPacket>{{
    "camera_presets",
}};

template <>
struct field_accessor<v766::CameraPresetsPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.camera_presets;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v776::CameraPresetsPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v776::CameraPresetsPacket>{"CameraPresetsPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v776::CameraPresetsPacket>{{
    "camera_presets",
}};

template <>
struct field_accessor<v776::CameraPresetsPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.camera_presets;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v800::CameraPresetsPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v800::CameraPresetsPacket>{"CameraPresetsPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v800::CameraPresetsPacket>{{
    "camera_presets",
}};

template <>
struct field_accessor<v800::CameraPresetsPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.camera_presets;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v818::CameraPresetsPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v818::CameraPresetsPacket>{"CameraPresetsPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v818::CameraPresetsPacket>{{
    "camera_presets",
}};

template <>
struct field_accessor<v818::CameraPresetsPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.camera_presets;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2193::CameraPresetsPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2193::CameraPresetsPacket>{"CameraPresetsPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2193::CameraPresetsPacket>{{
    "camera_presets",
}};

template <>
struct field_accessor<v2193::CameraPresetsPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.camera_presets;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<CameraPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<CameraPacket>{"CameraPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<CameraPacket>{{
    "camera_id",
    "target_player_id",
}};

template <>
struct field_accessor<CameraPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.camera_id;
        }
        else {
            return value.target_player_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<CameraShakePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<CameraShakePacket>{"CameraShakePacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<CameraShakePacket>{{
    "intensity",
    "seconds",
    "shake_type",
    "shake_action",
}};

template <>
struct field_accessor<CameraShakePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.intensity;
        }
        else if constexpr (I == 1) {
            return value.seconds;
        }
        else if constexpr (I == 2) {
            return value.shake_type;
        }
        else {
            return value.shake_action;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<CameraAimAssistActorPriority::PriorityData> = true;

template <>
inline constexpr std::string_view struct_name_v<CameraAimAssistActorPriority::PriorityData>{"CameraAimAssistActorPriority::PriorityData"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<CameraAimAssistActorPriority::PriorityData>{{
    "preset_index",
    "category_index",
    "actor_index",
    "priority_value",
}};

template <>
struct field_accessor<CameraAimAssistActorPriority::PriorityData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.preset_index;
        }
        else if constexpr (I == 1) {
            return value.category_index;
        }
        else if constexpr (I == 2) {
            return value.actor_index;
        }
        else {
            return value.priority_value;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<CameraAimAssistActorPriority> = true;

template <>
inline constexpr std::string_view struct_name_v<CameraAimAssistActorPriority>{"CameraAimAssistActorPriority"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<CameraAimAssistActorPriority>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<v924::CameraAimAssistActorPriorityPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::CameraAimAssistActorPriorityPacket>{"CameraAimAssistActorPriorityPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v924::CameraAimAssistActorPriorityPacket>{{
    "camera_aim_assist_actor_priority_list",
}};

template <>
struct field_accessor<v924::CameraAimAssistActorPriorityPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.camera_aim_assist_actor_priority_list;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v776::ClientCameraAimAssistPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v776::ClientCameraAimAssistPacket>{"ClientCameraAimAssistPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v776::ClientCameraAimAssistPacket>{{
    "camera_preset_id",
    "action",
    "allow_aim_assist",
}};

template <>
struct field_accessor<v776::ClientCameraAimAssistPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.camera_preset_id;
        }
        else if constexpr (I == 1) {
            return value.action;
        }
        else {
            return value.allow_aim_assist;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::CameraAimAssistPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::CameraAimAssistPacket>{"CameraAimAssistPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<base::CameraAimAssistPacket>{{
    "view_angle",
    "distance",
    "target_mode",
    "action",
}};

template <>
struct field_accessor<base::CameraAimAssistPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.view_angle;
        }
        else if constexpr (I == 1) {
            return value.distance;
        }
        else if constexpr (I == 2) {
            return value.target_mode;
        }
        else {
            return value.action;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v766::CameraAimAssistPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v766::CameraAimAssistPacket>{"CameraAimAssistPacket"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v766::CameraAimAssistPacket>{{
    "preset_id",
    "view_angle",
    "distance",
    "target_mode",
    "action",
}};

template <>
struct field_accessor<v766::CameraAimAssistPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.preset_id;
        }
        else if constexpr (I == 1) {
            return value.view_angle;
        }
        else if constexpr (I == 2) {
            return value.distance;
        }
        else if constexpr (I == 3) {
            return value.target_mode;
        }
        else {
            return value.action;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v827::CameraAimAssistPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v827::CameraAimAssistPacket>{"CameraAimAssistPacket"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<v827::CameraAimAssistPacket>{{
    "preset_id",
    "view_angle",
    "distance",
    "target_mode",
    "action",
    "show_debug_render",
}};

template <>
struct field_accessor<v827::CameraAimAssistPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.preset_id;
        }
        else if constexpr (I == 1) {
            return value.view_angle;
        }
        else if constexpr (I == 2) {
            return value.distance;
        }
        else if constexpr (I == 3) {
            return value.target_mode;
        }
        else if constexpr (I == 4) {
            return value.action;
        }
        else {
            return value.show_debug_render;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v766::CameraAimAssistCategoryPriorities> = true;

template <>
inline constexpr std::string_view struct_name_v<v766::CameraAimAssistCategoryPriorities>{"CameraAimAssistCategoryPriorities"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v766::CameraAimAssistCategoryPriorities>{{
    "entities",
    "blocks",
    "entity_default",
    "block_default",
}};

template <>
struct field_accessor<v766::CameraAimAssistCategoryPriorities> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.entities;
        }
        else if constexpr (I == 1) {
            return value.blocks;
        }
        else if constexpr (I == 2) {
            return value.entity_default;
        }
        else {
            return value.block_default;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v898::CameraAimAssistCategoryPriorities> = true;

template <>
inline constexpr std::string_view struct_name_v<v898::CameraAimAssistCategoryPriorities>{"CameraAimAssistCategoryPriorities"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v898::CameraAimAssistCategoryPriorities>{{
    "entities",
    "blocks",
    "block_tags",
    "entity_default",
    "block_default",
}};

template <>
struct field_accessor<v898::CameraAimAssistCategoryPriorities> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.entities;
        }
        else if constexpr (I == 1) {
            return value.blocks;
        }
        else if constexpr (I == 2) {
            return value.block_tags;
        }
        else if constexpr (I == 3) {
            return value.entity_default;
        }
        else {
            return value.block_default;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::CameraAimAssistCategoryPriorities> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::CameraAimAssistCategoryPriorities>{"CameraAimAssistCategoryPriorities"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<v924::CameraAimAssistCategoryPriorities>{{
    "entities",
    "blocks",
    "block_tags",
    "entity_type_families",
    "entity_default",
    "block_default",
}};

template <>
struct field_accessor<v924::CameraAimAssistCategoryPriorities> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.entities;
        }
        else if constexpr (I == 1) {
            return value.blocks;
        }
        else if constexpr (I == 2) {
            return value.block_tags;
        }
        else if constexpr (I == 3) {
            return value.entity_type_families;
        }
        else if constexpr (I == 4) {
            return value.entity_default;
        }
        else {
            return value.block_default;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v766::CameraAimAssistCategoryDefinition> = true;

template <>
inline constexpr std::string_view struct_name_v<v766::CameraAimAssistCategoryDefinition>{"CameraAimAssistCategoryDefinition"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v766::CameraAimAssistCategoryDefinition>{{
    "name",
    "priorities",
}};

template <>
struct field_accessor<v766::CameraAimAssistCategoryDefinition> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.name;
        }
        else {
            return value.priorities;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v898::CameraAimAssistCategoryDefinition> = true;

template <>
inline constexpr std::string_view struct_name_v<v898::CameraAimAssistCategoryDefinition>{"CameraAimAssistCategoryDefinition"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v898::CameraAimAssistCategoryDefinition>{{
    "name",
    "priorities",
}};

template <>
struct field_accessor<v898::CameraAimAssistCategoryDefinition> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.name;
        }
        else {
            return value.priorities;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::CameraAimAssistCategoryDefinition> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::CameraAimAssistCategoryDefinition>{"CameraAimAssistCategoryDefinition"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v924::CameraAimAssistCategoryDefinition>{{
    "name",
    "priorities",
}};

template <>
struct field_accessor<v924::CameraAimAssistCategoryDefinition> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.name;
        }
        else {
            return value.priorities;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v898::CameraAimAssistPresetExclusionDefinition> = true;

template <>
inline constexpr std::string_view struct_name_v<v898::CameraAimAssistPresetExclusionDefinition>{"CameraAimAssistPresetExclusionDefinition"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v898::CameraAimAssistPresetExclusionDefinition>{{
    "block_exclusion_list",
    "actor_exclusion_list",
    "block_tag_exclusion_list",
}};

template <>
struct field_accessor<v898::CameraAimAssistPresetExclusionDefinition> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.block_exclusion_list;
        }
        else if constexpr (I == 1) {
            return value.actor_exclusion_list;
        }
        else {
            return value.block_tag_exclusion_list;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::CameraAimAssistPresetExclusionDefinition> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::CameraAimAssistPresetExclusionDefinition>{"CameraAimAssistPresetExclusionDefinition"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v924::CameraAimAssistPresetExclusionDefinition>{{
    "block_exclusion_list",
    "actor_exclusion_list",
    "block_tag_exclusion_list",
    "entity_type_family_exclusion_list",
}};

template <>
struct field_accessor<v924::CameraAimAssistPresetExclusionDefinition> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.block_exclusion_list;
        }
        else if constexpr (I == 1) {
            return value.actor_exclusion_list;
        }
        else if constexpr (I == 2) {
            return value.block_tag_exclusion_list;
        }
        else {
            return value.entity_type_family_exclusion_list;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v766::CameraAimAssistPresetDefinition> = true;

template <>
inline constexpr std::string_view struct_name_v<v766::CameraAimAssistPresetDefinition>{"CameraAimAssistPresetDefinition"};

template <>
inline constexpr std::array<std::string_view, 7> field_names_v<v766::CameraAimAssistPresetDefinition>{{
    "identifier",
    "categories",
    "exclusion_list",
    "liquid_targeting_list",
    "item_settings",
    "default_item_settings",
    "hand_settings",
}};

template <>
struct field_accessor<v766::CameraAimAssistPresetDefinition> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.identifier;
        }
        else if constexpr (I == 1) {
            return value.categories;
        }
        else if constexpr (I == 2) {
            return value.exclusion_list;
        }
        else if constexpr (I == 3) {
            return value.liquid_targeting_list;
        }
        else if constexpr (I == 4) {
            return value.item_settings;
        }
        else if constexpr (I == 5) {
            return value.default_item_settings;
        }
        else {
            return value.hand_settings;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v776::CameraAimAssistPresetDefinition> = true;

template <>
inline constexpr std::string_view struct_name_v<v776::CameraAimAssistPresetDefinition>{"CameraAimAssistPresetDefinition"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<v776::CameraAimAssistPresetDefinition>{{
    "identifier",
    "exclusion_list",
    "liquid_targeting_list",
    "item_settings",
    "default_item_settings",
    "hand_settings",
}};

template <>
struct field_accessor<v776::CameraAimAssistPresetDefinition> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.identifier;
        }
        else if constexpr (I == 1) {
            return value.exclusion_list;
        }
        else if constexpr (I == 2) {
            return value.liquid_targeting_list;
        }
        else if constexpr (I == 3) {
            return value.item_settings;
        }
        else if constexpr (I == 4) {
            return value.default_item_settings;
        }
        else {
            return value.hand_settings;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v898::CameraAimAssistPresetDefinition> = true;

template <>
inline constexpr std::string_view struct_name_v<v898::CameraAimAssistPresetDefinition>{"CameraAimAssistPresetDefinition"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<v898::CameraAimAssistPresetDefinition>{{
    "identifier",
    "exclusion_settings",
    "liquid_targeting_list",
    "item_settings",
    "default_item_settings",
    "hand_settings",
}};

template <>
struct field_accessor<v898::CameraAimAssistPresetDefinition> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.identifier;
        }
        else if constexpr (I == 1) {
            return value.exclusion_settings;
        }
        else if constexpr (I == 2) {
            return value.liquid_targeting_list;
        }
        else if constexpr (I == 3) {
            return value.item_settings;
        }
        else if constexpr (I == 4) {
            return value.default_item_settings;
        }
        else {
            return value.hand_settings;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::CameraAimAssistPresetDefinition> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::CameraAimAssistPresetDefinition>{"CameraAimAssistPresetDefinition"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<v924::CameraAimAssistPresetDefinition>{{
    "identifier",
    "exclusion_settings",
    "liquid_targeting_list",
    "item_settings",
    "default_item_settings",
    "hand_settings",
}};

template <>
struct field_accessor<v924::CameraAimAssistPresetDefinition> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.identifier;
        }
        else if constexpr (I == 1) {
            return value.exclusion_settings;
        }
        else if constexpr (I == 2) {
            return value.liquid_targeting_list;
        }
        else if constexpr (I == 3) {
            return value.item_settings;
        }
        else if constexpr (I == 4) {
            return value.default_item_settings;
        }
        else {
            return value.hand_settings;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v766::CameraAimAssistCategoriesDefinition> = true;

template <>
inline constexpr std::string_view struct_name_v<v766::CameraAimAssistCategoriesDefinition>{"CameraAimAssistCategoriesDefinition"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v766::CameraAimAssistCategoriesDefinition>{{
    "identifier",
    "categories",
}};

template <>
struct field_accessor<v766::CameraAimAssistCategoriesDefinition> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.identifier;
        }
        else {
            return value.categories;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v766::CameraAimAssistPresetsPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v766::CameraAimAssistPresetsPacket>{"CameraAimAssistPresetsPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v766::CameraAimAssistPresetsPacket>{{
    "categories",
    "presets",
}};

template <>
struct field_accessor<v766::CameraAimAssistPresetsPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.categories;
        }
        else {
            return value.presets;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v776::CameraAimAssistPresetsPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v776::CameraAimAssistPresetsPacket>{"CameraAimAssistPresetsPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v776::CameraAimAssistPresetsPacket>{{
    "categories",
    "presets",
    "operation",
}};

template <>
struct field_accessor<v776::CameraAimAssistPresetsPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.categories;
        }
        else if constexpr (I == 1) {
            return value.presets;
        }
        else {
            return value.operation;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v898::CameraAimAssistPresetsPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v898::CameraAimAssistPresetsPacket>{"CameraAimAssistPresetsPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v898::CameraAimAssistPresetsPacket>{{
    "categories",
    "presets",
    "operation",
}};

template <>
struct field_accessor<v898::CameraAimAssistPresetsPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.categories;
        }
        else if constexpr (I == 1) {
            return value.presets;
        }
        else {
            return value.operation;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::CameraAimAssistPresetsPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::CameraAimAssistPresetsPacket>{"CameraAimAssistPresetsPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v924::CameraAimAssistPresetsPacket>{{
    "categories",
    "presets",
    "operation",
}};

template <>
struct field_accessor<v924::CameraAimAssistPresetsPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.categories;
        }
        else if constexpr (I == 1) {
            return value.presets;
        }
        else {
            return value.operation;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::CameraInstructionOptions::SetInstruction::EaseOption> = true;

template <>
inline constexpr std::string_view struct_name_v<base::CameraInstructionOptions::SetInstruction::EaseOption>{"CameraInstructionOptions::SetInstruction::EaseOption"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<base::CameraInstructionOptions::SetInstruction::EaseOption>{{
    "easing_type",
    "easing_time",
}};

template <>
struct field_accessor<base::CameraInstructionOptions::SetInstruction::EaseOption> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.easing_type;
        }
        else {
            return value.easing_time;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::CameraInstructionOptions::SetInstruction::PosOption> = true;

template <>
inline constexpr std::string_view struct_name_v<base::CameraInstructionOptions::SetInstruction::PosOption>{"CameraInstructionOptions::SetInstruction::PosOption"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::CameraInstructionOptions::SetInstruction::PosOption>{{
    "pos",
}};

template <>
struct field_accessor<base::CameraInstructionOptions::SetInstruction::PosOption> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.pos;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::CameraInstructionOptions::SetInstruction::RotOption> = true;

template <>
inline constexpr std::string_view struct_name_v<base::CameraInstructionOptions::SetInstruction::RotOption>{"CameraInstructionOptions::SetInstruction::RotOption"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<base::CameraInstructionOptions::SetInstruction::RotOption>{{
    "rot_x",
    "rot_y",
}};

template <>
struct field_accessor<base::CameraInstructionOptions::SetInstruction::RotOption> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.rot_x;
        }
        else {
            return value.rot_y;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::CameraInstructionOptions::SetInstruction::FacingOption> = true;

template <>
inline constexpr std::string_view struct_name_v<base::CameraInstructionOptions::SetInstruction::FacingOption>{"CameraInstructionOptions::SetInstruction::FacingOption"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::CameraInstructionOptions::SetInstruction::FacingOption>{{
    "facing_pos",
}};

template <>
struct field_accessor<base::CameraInstructionOptions::SetInstruction::FacingOption> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.facing_pos;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::CameraInstructionOptions::SetInstruction::ViewOffsetOption> = true;

template <>
inline constexpr std::string_view struct_name_v<base::CameraInstructionOptions::SetInstruction::ViewOffsetOption>{"CameraInstructionOptions::SetInstruction::ViewOffsetOption"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<base::CameraInstructionOptions::SetInstruction::ViewOffsetOption>{{
    "view_offset_x",
    "view_offset_y",
}};

template <>
struct field_accessor<base::CameraInstructionOptions::SetInstruction::ViewOffsetOption> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.view_offset_x;
        }
        else {
            return value.view_offset_y;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::CameraInstructionOptions::SetInstruction::EntityOffsetOption> = true;

template <>
inline constexpr std::string_view struct_name_v<base::CameraInstructionOptions::SetInstruction::EntityOffsetOption>{"CameraInstructionOptions::SetInstruction::EntityOffsetOption"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<base::CameraInstructionOptions::SetInstruction::EntityOffsetOption>{{
    "entity_offset_x",
    "entity_offset_y",
    "entity_offset_z",
}};

template <>
struct field_accessor<base::CameraInstructionOptions::SetInstruction::EntityOffsetOption> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.entity_offset_x;
        }
        else if constexpr (I == 1) {
            return value.entity_offset_y;
        }
        else {
            return value.entity_offset_z;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::CameraInstructionOptions::SetInstruction> = true;

template <>
inline constexpr std::string_view struct_name_v<base::CameraInstructionOptions::SetInstruction>{"CameraInstructionOptions::SetInstruction"};

template <>
inline constexpr std::array<std::string_view, 7> field_names_v<base::CameraInstructionOptions::SetInstruction>{{
    "preset_index",
    "ease",
    "pos",
    "rot",
    "facing",
    "view_offset",
    "default_",
}};

template <>
struct field_accessor<base::CameraInstructionOptions::SetInstruction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.preset_index;
        }
        else if constexpr (I == 1) {
            return value.ease;
        }
        else if constexpr (I == 2) {
            return value.pos;
        }
        else if constexpr (I == 3) {
            return value.rot;
        }
        else if constexpr (I == 4) {
            return value.facing;
        }
        else if constexpr (I == 5) {
            return value.view_offset;
        }
        else {
            return value.default_;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::CameraInstructionOptions::FadeInstruction::TimeOption> = true;

template <>
inline constexpr std::string_view struct_name_v<base::CameraInstructionOptions::FadeInstruction::TimeOption>{"CameraInstructionOptions::FadeInstruction::TimeOption"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<base::CameraInstructionOptions::FadeInstruction::TimeOption>{{
    "fade_in_time",
    "hold_time",
    "fade_out_time",
}};

template <>
struct field_accessor<base::CameraInstructionOptions::FadeInstruction::TimeOption> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.fade_in_time;
        }
        else if constexpr (I == 1) {
            return value.hold_time;
        }
        else {
            return value.fade_out_time;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::CameraInstructionOptions::FadeInstruction::ColorOption> = true;

template <>
inline constexpr std::string_view struct_name_v<base::CameraInstructionOptions::FadeInstruction::ColorOption>{"CameraInstructionOptions::FadeInstruction::ColorOption"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<base::CameraInstructionOptions::FadeInstruction::ColorOption>{{
    "red",
    "green",
    "blue",
}};

template <>
struct field_accessor<base::CameraInstructionOptions::FadeInstruction::ColorOption> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.red;
        }
        else if constexpr (I == 1) {
            return value.green;
        }
        else {
            return value.blue;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::CameraInstructionOptions::FadeInstruction> = true;

template <>
inline constexpr std::string_view struct_name_v<base::CameraInstructionOptions::FadeInstruction>{"CameraInstructionOptions::FadeInstruction"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<base::CameraInstructionOptions::FadeInstruction>{{
    "time",
    "color",
}};

template <>
struct field_accessor<base::CameraInstructionOptions::FadeInstruction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.time;
        }
        else {
            return value.color;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::CameraInstructionOptions::TargetInstruction> = true;

template <>
inline constexpr std::string_view struct_name_v<base::CameraInstructionOptions::TargetInstruction>{"CameraInstructionOptions::TargetInstruction"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<base::CameraInstructionOptions::TargetInstruction>{{
    "target_center_offset",
    "target_actor_id",
}};

template <>
struct field_accessor<base::CameraInstructionOptions::TargetInstruction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.target_center_offset;
        }
        else {
            return value.target_actor_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::CameraInstructionOptions::FovInstruction> = true;

template <>
inline constexpr std::string_view struct_name_v<base::CameraInstructionOptions::FovInstruction>{"CameraInstructionOptions::FovInstruction"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<base::CameraInstructionOptions::FovInstruction>{{
    "fov",
    "fov_ease_time",
    "fov_ease_type",
    "fov_clear",
}};

template <>
struct field_accessor<base::CameraInstructionOptions::FovInstruction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.fov;
        }
        else if constexpr (I == 1) {
            return value.fov_ease_time;
        }
        else if constexpr (I == 2) {
            return value.fov_ease_type;
        }
        else {
            return value.fov_clear;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::CameraInstructionOptions::AttachToEntityInstruction> = true;

template <>
inline constexpr std::string_view struct_name_v<base::CameraInstructionOptions::AttachToEntityInstruction>{"CameraInstructionOptions::AttachToEntityInstruction"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::CameraInstructionOptions::AttachToEntityInstruction>{{
    "attach_to_entity_id",
}};

template <>
struct field_accessor<base::CameraInstructionOptions::AttachToEntityInstruction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.attach_to_entity_id;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::CameraInstructionOptions::SplineInstruction::SplineRotationOption> = true;

template <>
inline constexpr std::string_view struct_name_v<base::CameraInstructionOptions::SplineInstruction::SplineRotationOption>{"CameraInstructionOptions::SplineInstruction::SplineRotationOption"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<base::CameraInstructionOptions::SplineInstruction::SplineRotationOption>{{
    "rotation_key_frame_value",
    "rotation_key_frame_time",
}};

template <>
struct field_accessor<base::CameraInstructionOptions::SplineInstruction::SplineRotationOption> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.rotation_key_frame_value;
        }
        else {
            return value.rotation_key_frame_time;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::CameraInstructionOptions::SplineInstruction::SplineProgressOption> = true;

template <>
inline constexpr std::string_view struct_name_v<base::CameraInstructionOptions::SplineInstruction::SplineProgressOption>{"CameraInstructionOptions::SplineInstruction::SplineProgressOption"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<base::CameraInstructionOptions::SplineInstruction::SplineProgressOption>{{
    "progress_key_frame_value",
    "progress_key_frame_time",
    "progress_key_frames_easing_func",
}};

template <>
struct field_accessor<base::CameraInstructionOptions::SplineInstruction::SplineProgressOption> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.progress_key_frame_value;
        }
        else if constexpr (I == 1) {
            return value.progress_key_frame_time;
        }
        else {
            return value.progress_key_frames_easing_func;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::CameraInstructionOptions::SplineInstruction> = true;

template <>
inline constexpr std::string_view struct_name_v<base::CameraInstructionOptions::SplineInstruction>{"CameraInstructionOptions::SplineInstruction"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<base::CameraInstructionOptions::SplineInstruction>{{
    "total_time",
    "curve_type",
    "curve",
    "progress_key_frames",
    "spline_rotation_option",
}};

template <>
struct field_accessor<base::CameraInstructionOptions::SplineInstruction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.total_time;
        }
        else if constexpr (I == 1) {
            return value.curve_type;
        }
        else if constexpr (I == 2) {
            return value.curve;
        }
        else if constexpr (I == 3) {
            return value.progress_key_frames;
        }
        else {
            return value.spline_rotation_option;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v748::CameraInstructionOptions::SetInstruction::EaseOption> = true;

template <>
inline constexpr std::string_view struct_name_v<v748::CameraInstructionOptions::SetInstruction::EaseOption>{"CameraInstructionOptions::SetInstruction::EaseOption"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v748::CameraInstructionOptions::SetInstruction::EaseOption>{{
    "easing_type",
    "easing_time",
}};

template <>
struct field_accessor<v748::CameraInstructionOptions::SetInstruction::EaseOption> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.easing_type;
        }
        else {
            return value.easing_time;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v748::CameraInstructionOptions::SetInstruction::PosOption> = true;

template <>
inline constexpr std::string_view struct_name_v<v748::CameraInstructionOptions::SetInstruction::PosOption>{"CameraInstructionOptions::SetInstruction::PosOption"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v748::CameraInstructionOptions::SetInstruction::PosOption>{{
    "pos",
}};

template <>
struct field_accessor<v748::CameraInstructionOptions::SetInstruction::PosOption> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.pos;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v748::CameraInstructionOptions::SetInstruction::RotOption> = true;

template <>
inline constexpr std::string_view struct_name_v<v748::CameraInstructionOptions::SetInstruction::RotOption>{"CameraInstructionOptions::SetInstruction::RotOption"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v748::CameraInstructionOptions::SetInstruction::RotOption>{{
    "rot_x",
    "rot_y",
}};

template <>
struct field_accessor<v748::CameraInstructionOptions::SetInstruction::RotOption> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.rot_x;
        }
        else {
            return value.rot_y;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v748::CameraInstructionOptions::SetInstruction::FacingOption> = true;

template <>
inline constexpr std::string_view struct_name_v<v748::CameraInstructionOptions::SetInstruction::FacingOption>{"CameraInstructionOptions::SetInstruction::FacingOption"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v748::CameraInstructionOptions::SetInstruction::FacingOption>{{
    "facing_pos",
}};

template <>
struct field_accessor<v748::CameraInstructionOptions::SetInstruction::FacingOption> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.facing_pos;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v748::CameraInstructionOptions::SetInstruction::ViewOffsetOption> = true;

template <>
inline constexpr std::string_view struct_name_v<v748::CameraInstructionOptions::SetInstruction::ViewOffsetOption>{"CameraInstructionOptions::SetInstruction::ViewOffsetOption"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v748::CameraInstructionOptions::SetInstruction::ViewOffsetOption>{{
    "view_offset_x",
    "view_offset_y",
}};

template <>
struct field_accessor<v748::CameraInstructionOptions::SetInstruction::ViewOffsetOption> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.view_offset_x;
        }
        else {
            return value.view_offset_y;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v748::CameraInstructionOptions::SetInstruction::EntityOffsetOption> = true;

template <>
inline constexpr std::string_view struct_name_v<v748::CameraInstructionOptions::SetInstruction::EntityOffsetOption>{"CameraInstructionOptions::SetInstruction::EntityOffsetOption"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v748::CameraInstructionOptions::SetInstruction::EntityOffsetOption>{{
    "entity_offset_x",
    "entity_offset_y",
    "entity_offset_z",
}};

template <>
struct field_accessor<v748::CameraInstructionOptions::SetInstruction::EntityOffsetOption> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.entity_offset_x;
        }
        else if constexpr (I == 1) {
            return value.entity_offset_y;
        }
        else {
            return value.entity_offset_z;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v748::CameraInstructionOptions::SetInstruction> = true;

template <>
inline constexpr std::string_view struct_name_v<v748::CameraInstructionOptions::SetInstruction>{"CameraInstructionOptions::SetInstruction"};

template <>
inline constexpr std::array<std::string_view, 8> field_names_v<v748::CameraInstructionOptions::SetInstruction>{{
    "preset_index",
    "ease",
    "pos",
    "rot",
    "facing",
    "view_offset",
    "entity_offset",
    "default_",
}};

template <>
struct field_accessor<v748::CameraInstructionOptions::SetInstruction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.preset_index;
        }
        else if constexpr (I == 1) {
            return value.ease;
        }
        else if constexpr (I == 2) {
            return value.pos;
        }
        else if constexpr (I == 3) {
            return value.rot;
        }
        else if constexpr (I == 4) {
            return value.facing;
        }
        else if constexpr (I == 5) {
            return value.view_offset;
        }
        else if constexpr (I == 6) {
            return value.entity_offset;
        }
        else {
            return value.default_;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v748::CameraInstructionOptions::SplineInstruction::SplineRotationOption> = true;

template <>
inline constexpr std::string_view struct_name_v<v748::CameraInstructionOptions::SplineInstruction::SplineRotationOption>{"CameraInstructionOptions::SplineInstruction::SplineRotationOption"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v748::CameraInstructionOptions::SplineInstruction::SplineRotationOption>{{
    "rotation_key_frame_value",
    "rotation_key_frame_time",
}};

template <>
struct field_accessor<v748::CameraInstructionOptions::SplineInstruction::SplineRotationOption> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.rotation_key_frame_value;
        }
        else {
            return value.rotation_key_frame_time;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v748::CameraInstructionOptions::SplineInstruction::SplineProgressOption> = true;

template <>
inline constexpr std::string_view struct_name_v<v748::CameraInstructionOptions::SplineInstruction::SplineProgressOption>{"CameraInstructionOptions::SplineInstruction::SplineProgressOption"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v748::CameraInstructionOptions::SplineInstruction::SplineProgressOption>{{
    "progress_key_frame_value",
    "progress_key_frame_time",
    "progress_key_frames_easing_func",
}};

template <>
struct field_accessor<v748::CameraInstructionOptions::SplineInstruction::SplineProgressOption> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.progress_key_frame_value;
        }
        else if constexpr (I == 1) {
            return value.progress_key_frame_time;
        }
        else {
            return value.progress_key_frames_easing_func;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v748::CameraInstructionOptions::SplineInstruction> = true;

template <>
inline constexpr std::string_view struct_name_v<v748::CameraInstructionOptions::SplineInstruction>{"CameraInstructionOptions::SplineInstruction"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v748::CameraInstructionOptions::SplineInstruction>{{
    "total_time",
    "curve_type",
    "curve",
    "progress_key_frames",
    "spline_rotation_option",
}};

template <>
struct field_accessor<v748::CameraInstructionOptions::SplineInstruction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.total_time;
        }
        else if constexpr (I == 1) {
            return value.curve_type;
        }
        else if constexpr (I == 2) {
            return value.curve;
        }
        else if constexpr (I == 3) {
            return value.progress_key_frames;
        }
        else {
            return value.spline_rotation_option;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v818::CameraInstructionOptions::SetInstruction::EaseOption> = true;

template <>
inline constexpr std::string_view struct_name_v<v818::CameraInstructionOptions::SetInstruction::EaseOption>{"CameraInstructionOptions::SetInstruction::EaseOption"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v818::CameraInstructionOptions::SetInstruction::EaseOption>{{
    "easing_type",
    "easing_time",
}};

template <>
struct field_accessor<v818::CameraInstructionOptions::SetInstruction::EaseOption> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.easing_type;
        }
        else {
            return value.easing_time;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v818::CameraInstructionOptions::SetInstruction::PosOption> = true;

template <>
inline constexpr std::string_view struct_name_v<v818::CameraInstructionOptions::SetInstruction::PosOption>{"CameraInstructionOptions::SetInstruction::PosOption"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v818::CameraInstructionOptions::SetInstruction::PosOption>{{
    "pos",
}};

template <>
struct field_accessor<v818::CameraInstructionOptions::SetInstruction::PosOption> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.pos;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v818::CameraInstructionOptions::SetInstruction::RotOption> = true;

template <>
inline constexpr std::string_view struct_name_v<v818::CameraInstructionOptions::SetInstruction::RotOption>{"CameraInstructionOptions::SetInstruction::RotOption"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v818::CameraInstructionOptions::SetInstruction::RotOption>{{
    "rot_x",
    "rot_y",
}};

template <>
struct field_accessor<v818::CameraInstructionOptions::SetInstruction::RotOption> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.rot_x;
        }
        else {
            return value.rot_y;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v818::CameraInstructionOptions::SetInstruction::FacingOption> = true;

template <>
inline constexpr std::string_view struct_name_v<v818::CameraInstructionOptions::SetInstruction::FacingOption>{"CameraInstructionOptions::SetInstruction::FacingOption"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v818::CameraInstructionOptions::SetInstruction::FacingOption>{{
    "facing_pos",
}};

template <>
struct field_accessor<v818::CameraInstructionOptions::SetInstruction::FacingOption> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.facing_pos;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v818::CameraInstructionOptions::SetInstruction::ViewOffsetOption> = true;

template <>
inline constexpr std::string_view struct_name_v<v818::CameraInstructionOptions::SetInstruction::ViewOffsetOption>{"CameraInstructionOptions::SetInstruction::ViewOffsetOption"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v818::CameraInstructionOptions::SetInstruction::ViewOffsetOption>{{
    "view_offset_x",
    "view_offset_y",
}};

template <>
struct field_accessor<v818::CameraInstructionOptions::SetInstruction::ViewOffsetOption> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.view_offset_x;
        }
        else {
            return value.view_offset_y;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v818::CameraInstructionOptions::SetInstruction::EntityOffsetOption> = true;

template <>
inline constexpr std::string_view struct_name_v<v818::CameraInstructionOptions::SetInstruction::EntityOffsetOption>{"CameraInstructionOptions::SetInstruction::EntityOffsetOption"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v818::CameraInstructionOptions::SetInstruction::EntityOffsetOption>{{
    "entity_offset_x",
    "entity_offset_y",
    "entity_offset_z",
}};

template <>
struct field_accessor<v818::CameraInstructionOptions::SetInstruction::EntityOffsetOption> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.entity_offset_x;
        }
        else if constexpr (I == 1) {
            return value.entity_offset_y;
        }
        else {
            return value.entity_offset_z;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v818::CameraInstructionOptions::SetInstruction> = true;

template <>
inline constexpr std::string_view struct_name_v<v818::CameraInstructionOptions::SetInstruction>{"CameraInstructionOptions::SetInstruction"};

template <>
inline constexpr std::array<std::string_view, 9> field_names_v<v818::CameraInstructionOptions::SetInstruction>{{
    "preset_index",
    "ease",
    "pos",
    "rot",
    "facing",
    "view_offset",
    "entity_offset",
    "default_",
    "remove_ignore_starting_values_component",
}};

template <>
struct field_accessor<v818::CameraInstructionOptions::SetInstruction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.preset_index;
        }
        else if constexpr (I == 1) {
            return value.ease;
        }
        else if constexpr (I == 2) {
            return value.pos;
        }
        else if constexpr (I == 3) {
            return value.rot;
        }
        else if constexpr (I == 4) {
            return value.facing;
        }
        else if constexpr (I == 5) {
            return value.view_offset;
        }
        else if constexpr (I == 6) {
            return value.entity_offset;
        }
        else if constexpr (I == 7) {
            return value.default_;
        }
        else {
            return value.remove_ignore_starting_values_component;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v818::CameraInstructionOptions::SplineInstruction::SplineRotationOption> = true;

template <>
inline constexpr std::string_view struct_name_v<v818::CameraInstructionOptions::SplineInstruction::SplineRotationOption>{"CameraInstructionOptions::SplineInstruction::SplineRotationOption"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v818::CameraInstructionOptions::SplineInstruction::SplineRotationOption>{{
    "rotation_key_frame_value",
    "rotation_key_frame_time",
}};

template <>
struct field_accessor<v818::CameraInstructionOptions::SplineInstruction::SplineRotationOption> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.rotation_key_frame_value;
        }
        else {
            return value.rotation_key_frame_time;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v818::CameraInstructionOptions::SplineInstruction::SplineProgressOption> = true;

template <>
inline constexpr std::string_view struct_name_v<v818::CameraInstructionOptions::SplineInstruction::SplineProgressOption>{"CameraInstructionOptions::SplineInstruction::SplineProgressOption"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v818::CameraInstructionOptions::SplineInstruction::SplineProgressOption>{{
    "progress_key_frame_value",
    "progress_key_frame_time",
    "progress_key_frames_easing_func",
}};

template <>
struct field_accessor<v818::CameraInstructionOptions::SplineInstruction::SplineProgressOption> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.progress_key_frame_value;
        }
        else if constexpr (I == 1) {
            return value.progress_key_frame_time;
        }
        else {
            return value.progress_key_frames_easing_func;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v818::CameraInstructionOptions::SplineInstruction> = true;

template <>
inline constexpr std::string_view struct_name_v<v818::CameraInstructionOptions::SplineInstruction>{"CameraInstructionOptions::SplineInstruction"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v818::CameraInstructionOptions::SplineInstruction>{{
    "total_time",
    "curve_type",
    "curve",
    "progress_key_frames",
    "spline_rotation_option",
}};

template <>
struct field_accessor<v818::CameraInstructionOptions::SplineInstruction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.total_time;
        }
        else if constexpr (I == 1) {
            return value.curve_type;
        }
        else if constexpr (I == 2) {
            return value.curve;
        }
        else if constexpr (I == 3) {
            return value.progress_key_frames;
        }
        else {
            return value.spline_rotation_option;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::CameraInstructionOptions::SetInstruction::EaseOption> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::CameraInstructionOptions::SetInstruction::EaseOption>{"CameraInstructionOptions::SetInstruction::EaseOption"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v924::CameraInstructionOptions::SetInstruction::EaseOption>{{
    "easing_type",
    "easing_time",
}};

template <>
struct field_accessor<v924::CameraInstructionOptions::SetInstruction::EaseOption> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.easing_type;
        }
        else {
            return value.easing_time;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::CameraInstructionOptions::SetInstruction::PosOption> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::CameraInstructionOptions::SetInstruction::PosOption>{"CameraInstructionOptions::SetInstruction::PosOption"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v924::CameraInstructionOptions::SetInstruction::PosOption>{{
    "pos",
}};

template <>
struct field_accessor<v924::CameraInstructionOptions::SetInstruction::PosOption> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.pos;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::CameraInstructionOptions::SetInstruction::RotOption> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::CameraInstructionOptions::SetInstruction::RotOption>{"CameraInstructionOptions::SetInstruction::RotOption"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v924::CameraInstructionOptions::SetInstruction::RotOption>{{
    "rot_x",
    "rot_y",
}};

template <>
struct field_accessor<v924::CameraInstructionOptions::SetInstruction::RotOption> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.rot_x;
        }
        else {
            return value.rot_y;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::CameraInstructionOptions::SetInstruction::FacingOption> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::CameraInstructionOptions::SetInstruction::FacingOption>{"CameraInstructionOptions::SetInstruction::FacingOption"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v924::CameraInstructionOptions::SetInstruction::FacingOption>{{
    "facing_pos",
}};

template <>
struct field_accessor<v924::CameraInstructionOptions::SetInstruction::FacingOption> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.facing_pos;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::CameraInstructionOptions::SetInstruction::ViewOffsetOption> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::CameraInstructionOptions::SetInstruction::ViewOffsetOption>{"CameraInstructionOptions::SetInstruction::ViewOffsetOption"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v924::CameraInstructionOptions::SetInstruction::ViewOffsetOption>{{
    "view_offset_x",
    "view_offset_y",
}};

template <>
struct field_accessor<v924::CameraInstructionOptions::SetInstruction::ViewOffsetOption> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.view_offset_x;
        }
        else {
            return value.view_offset_y;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::CameraInstructionOptions::SetInstruction::EntityOffsetOption> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::CameraInstructionOptions::SetInstruction::EntityOffsetOption>{"CameraInstructionOptions::SetInstruction::EntityOffsetOption"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v924::CameraInstructionOptions::SetInstruction::EntityOffsetOption>{{
    "entity_offset_x",
    "entity_offset_y",
    "entity_offset_z",
}};

template <>
struct field_accessor<v924::CameraInstructionOptions::SetInstruction::EntityOffsetOption> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.entity_offset_x;
        }
        else if constexpr (I == 1) {
            return value.entity_offset_y;
        }
        else {
            return value.entity_offset_z;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::CameraInstructionOptions::SetInstruction> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::CameraInstructionOptions::SetInstruction>{"CameraInstructionOptions::SetInstruction"};

template <>
inline constexpr std::array<std::string_view, 9> field_names_v<v924::CameraInstructionOptions::SetInstruction>{{
    "preset_index",
    "ease",
    "pos",
    "rot",
    "facing",
    "view_offset",
    "entity_offset",
    "default_",
    "remove_ignore_starting_values_component",
}};

template <>
struct field_accessor<v924::CameraInstructionOptions::SetInstruction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.preset_index;
        }
        else if constexpr (I == 1) {
            return value.ease;
        }
        else if constexpr (I == 2) {
            return value.pos;
        }
        else if constexpr (I == 3) {
            return value.rot;
        }
        else if constexpr (I == 4) {
            return value.facing;
        }
        else if constexpr (I == 5) {
            return value.view_offset;
        }
        else if constexpr (I == 6) {
            return value.entity_offset;
        }
        else if constexpr (I == 7) {
            return value.default_;
        }
        else {
            return value.remove_ignore_starting_values_component;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::CameraInstructionOptions::SplineInstruction::SplineRotationOption> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::CameraInstructionOptions::SplineInstruction::SplineRotationOption>{"CameraInstructionOptions::SplineInstruction::SplineRotationOption"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v924::CameraInstructionOptions::SplineInstruction::SplineRotationOption>{{
    "rotation_key_frame_value",
    "rotation_key_frame_time",
    "rotation_key_frames_easing_func",
}};

template <>
struct field_accessor<v924::CameraInstructionOptions::SplineInstruction::SplineRotationOption> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.rotation_key_frame_value;
        }
        else if constexpr (I == 1) {
            return value.rotation_key_frame_time;
        }
        else {
            return value.rotation_key_frames_easing_func;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::CameraInstructionOptions::SplineInstruction::SplineProgressOption> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::CameraInstructionOptions::SplineInstruction::SplineProgressOption>{"CameraInstructionOptions::SplineInstruction::SplineProgressOption"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v924::CameraInstructionOptions::SplineInstruction::SplineProgressOption>{{
    "progress_key_frame_value",
    "progress_key_frame_time",
    "progress_key_frames_easing_func",
}};

template <>
struct field_accessor<v924::CameraInstructionOptions::SplineInstruction::SplineProgressOption> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.progress_key_frame_value;
        }
        else if constexpr (I == 1) {
            return value.progress_key_frame_time;
        }
        else {
            return value.progress_key_frames_easing_func;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::CameraInstructionOptions::SplineInstruction> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::CameraInstructionOptions::SplineInstruction>{"CameraInstructionOptions::SplineInstruction"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v924::CameraInstructionOptions::SplineInstruction>{{
    "total_time",
    "curve_type",
    "curve",
    "progress_key_frames",
    "spline_rotation_option",
}};

template <>
struct field_accessor<v924::CameraInstructionOptions::SplineInstruction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.total_time;
        }
        else if constexpr (I == 1) {
            return value.curve_type;
        }
        else if constexpr (I == 2) {
            return value.curve;
        }
        else if constexpr (I == 3) {
            return value.progress_key_frames;
        }
        else {
            return value.spline_rotation_option;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::CameraInstructionOptions::SetInstruction::EaseOption> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::CameraInstructionOptions::SetInstruction::EaseOption>{"CameraInstructionOptions::SetInstruction::EaseOption"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v944::CameraInstructionOptions::SetInstruction::EaseOption>{{
    "easing_type",
    "easing_time",
}};

template <>
struct field_accessor<v944::CameraInstructionOptions::SetInstruction::EaseOption> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.easing_type;
        }
        else {
            return value.easing_time;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::CameraInstructionOptions::SetInstruction::PosOption> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::CameraInstructionOptions::SetInstruction::PosOption>{"CameraInstructionOptions::SetInstruction::PosOption"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v944::CameraInstructionOptions::SetInstruction::PosOption>{{
    "pos",
}};

template <>
struct field_accessor<v944::CameraInstructionOptions::SetInstruction::PosOption> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.pos;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::CameraInstructionOptions::SetInstruction::RotOption> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::CameraInstructionOptions::SetInstruction::RotOption>{"CameraInstructionOptions::SetInstruction::RotOption"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v944::CameraInstructionOptions::SetInstruction::RotOption>{{
    "rot_x",
    "rot_y",
}};

template <>
struct field_accessor<v944::CameraInstructionOptions::SetInstruction::RotOption> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.rot_x;
        }
        else {
            return value.rot_y;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::CameraInstructionOptions::SetInstruction::FacingOption> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::CameraInstructionOptions::SetInstruction::FacingOption>{"CameraInstructionOptions::SetInstruction::FacingOption"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v944::CameraInstructionOptions::SetInstruction::FacingOption>{{
    "facing_pos",
}};

template <>
struct field_accessor<v944::CameraInstructionOptions::SetInstruction::FacingOption> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.facing_pos;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::CameraInstructionOptions::SetInstruction::ViewOffsetOption> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::CameraInstructionOptions::SetInstruction::ViewOffsetOption>{"CameraInstructionOptions::SetInstruction::ViewOffsetOption"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v944::CameraInstructionOptions::SetInstruction::ViewOffsetOption>{{
    "view_offset_x",
    "view_offset_y",
}};

template <>
struct field_accessor<v944::CameraInstructionOptions::SetInstruction::ViewOffsetOption> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.view_offset_x;
        }
        else {
            return value.view_offset_y;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::CameraInstructionOptions::SetInstruction::EntityOffsetOption> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::CameraInstructionOptions::SetInstruction::EntityOffsetOption>{"CameraInstructionOptions::SetInstruction::EntityOffsetOption"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v944::CameraInstructionOptions::SetInstruction::EntityOffsetOption>{{
    "entity_offset_x",
    "entity_offset_y",
    "entity_offset_z",
}};

template <>
struct field_accessor<v944::CameraInstructionOptions::SetInstruction::EntityOffsetOption> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.entity_offset_x;
        }
        else if constexpr (I == 1) {
            return value.entity_offset_y;
        }
        else {
            return value.entity_offset_z;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::CameraInstructionOptions::SetInstruction> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::CameraInstructionOptions::SetInstruction>{"CameraInstructionOptions::SetInstruction"};

template <>
inline constexpr std::array<std::string_view, 9> field_names_v<v944::CameraInstructionOptions::SetInstruction>{{
    "preset_index",
    "ease",
    "pos",
    "rot",
    "facing",
    "view_offset",
    "entity_offset",
    "default_",
    "remove_ignore_starting_values_component",
}};

template <>
struct field_accessor<v944::CameraInstructionOptions::SetInstruction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.preset_index;
        }
        else if constexpr (I == 1) {
            return value.ease;
        }
        else if constexpr (I == 2) {
            return value.pos;
        }
        else if constexpr (I == 3) {
            return value.rot;
        }
        else if constexpr (I == 4) {
            return value.facing;
        }
        else if constexpr (I == 5) {
            return value.view_offset;
        }
        else if constexpr (I == 6) {
            return value.entity_offset;
        }
        else if constexpr (I == 7) {
            return value.default_;
        }
        else {
            return value.remove_ignore_starting_values_component;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::CameraInstructionOptions::SplineInstruction::SplineRotationOption> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::CameraInstructionOptions::SplineInstruction::SplineRotationOption>{"CameraInstructionOptions::SplineInstruction::SplineRotationOption"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v944::CameraInstructionOptions::SplineInstruction::SplineRotationOption>{{
    "rotation_key_frame_value",
    "rotation_key_frame_time",
    "rotation_key_frames_easing_func",
}};

template <>
struct field_accessor<v944::CameraInstructionOptions::SplineInstruction::SplineRotationOption> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.rotation_key_frame_value;
        }
        else if constexpr (I == 1) {
            return value.rotation_key_frame_time;
        }
        else {
            return value.rotation_key_frames_easing_func;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::CameraInstructionOptions::SplineInstruction::SplineProgressOption> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::CameraInstructionOptions::SplineInstruction::SplineProgressOption>{"CameraInstructionOptions::SplineInstruction::SplineProgressOption"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v944::CameraInstructionOptions::SplineInstruction::SplineProgressOption>{{
    "progress_key_frame_value",
    "progress_key_frame_time",
    "progress_key_frames_easing_func",
}};

template <>
struct field_accessor<v944::CameraInstructionOptions::SplineInstruction::SplineProgressOption> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.progress_key_frame_value;
        }
        else if constexpr (I == 1) {
            return value.progress_key_frame_time;
        }
        else {
            return value.progress_key_frames_easing_func;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::CameraInstructionOptions::SplineInstruction> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::CameraInstructionOptions::SplineInstruction>{"CameraInstructionOptions::SplineInstruction"};

template <>
inline constexpr std::array<std::string_view, 7> field_names_v<v944::CameraInstructionOptions::SplineInstruction>{{
    "total_time",
    "curve_type",
    "curve",
    "progress_key_frames",
    "spline_rotation_option",
    "spline_identifier",
    "load_from_json",
}};

template <>
struct field_accessor<v944::CameraInstructionOptions::SplineInstruction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.total_time;
        }
        else if constexpr (I == 1) {
            return value.curve_type;
        }
        else if constexpr (I == 2) {
            return value.curve;
        }
        else if constexpr (I == 3) {
            return value.progress_key_frames;
        }
        else if constexpr (I == 4) {
            return value.spline_rotation_option;
        }
        else if constexpr (I == 5) {
            return value.spline_identifier;
        }
        else {
            return value.load_from_json;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::CameraInstructionOptions> = true;

template <>
inline constexpr std::string_view struct_name_v<base::CameraInstructionOptions>{"CameraInstructionOptions"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<base::CameraInstructionOptions>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<v748::CameraInstructionOptions> = true;

template <>
inline constexpr std::string_view struct_name_v<v748::CameraInstructionOptions>{"CameraInstructionOptions"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<v748::CameraInstructionOptions>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<v818::CameraInstructionOptions> = true;

template <>
inline constexpr std::string_view struct_name_v<v818::CameraInstructionOptions>{"CameraInstructionOptions"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<v818::CameraInstructionOptions>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<v924::CameraInstructionOptions> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::CameraInstructionOptions>{"CameraInstructionOptions"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<v924::CameraInstructionOptions>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<v944::CameraInstructionOptions> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::CameraInstructionOptions>{"CameraInstructionOptions"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<v944::CameraInstructionOptions>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<base::CameraInstruction> = true;

template <>
inline constexpr std::string_view struct_name_v<base::CameraInstruction>{"CameraInstruction"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<base::CameraInstruction>{{
    "set",
    "clear",
    "fade",
    "target",
    "remove_target",
}};

template <>
struct field_accessor<base::CameraInstruction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.set;
        }
        else if constexpr (I == 1) {
            return value.clear;
        }
        else if constexpr (I == 2) {
            return value.fade;
        }
        else if constexpr (I == 3) {
            return value.target;
        }
        else {
            return value.remove_target;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v748::CameraInstruction> = true;

template <>
inline constexpr std::string_view struct_name_v<v748::CameraInstruction>{"CameraInstruction"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v748::CameraInstruction>{{
    "set",
    "clear",
    "fade",
    "target",
    "remove_target",
}};

template <>
struct field_accessor<v748::CameraInstruction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.set;
        }
        else if constexpr (I == 1) {
            return value.clear;
        }
        else if constexpr (I == 2) {
            return value.fade;
        }
        else if constexpr (I == 3) {
            return value.target;
        }
        else {
            return value.remove_target;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v818::CameraInstruction> = true;

template <>
inline constexpr std::string_view struct_name_v<v818::CameraInstruction>{"CameraInstruction"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v818::CameraInstruction>{{
    "set",
    "clear",
    "fade",
    "target",
    "remove_target",
}};

template <>
struct field_accessor<v818::CameraInstruction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.set;
        }
        else if constexpr (I == 1) {
            return value.clear;
        }
        else if constexpr (I == 2) {
            return value.fade;
        }
        else if constexpr (I == 3) {
            return value.target;
        }
        else {
            return value.remove_target;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v827::CameraInstruction> = true;

template <>
inline constexpr std::string_view struct_name_v<v827::CameraInstruction>{"CameraInstruction"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<v827::CameraInstruction>{{
    "set",
    "clear",
    "fade",
    "target",
    "remove_target",
    "field_of_view",
}};

template <>
struct field_accessor<v827::CameraInstruction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.set;
        }
        else if constexpr (I == 1) {
            return value.clear;
        }
        else if constexpr (I == 2) {
            return value.fade;
        }
        else if constexpr (I == 3) {
            return value.target;
        }
        else if constexpr (I == 4) {
            return value.remove_target;
        }
        else {
            return value.field_of_view;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v859::CameraInstruction> = true;

template <>
inline constexpr std::string_view struct_name_v<v859::CameraInstruction>{"CameraInstruction"};

template <>
inline constexpr std::array<std::string_view, 9> field_names_v<v859::CameraInstruction>{{
    "set",
    "clear",
    "fade",
    "target",
    "remove_target",
    "field_of_view",
    "spline",
    "attach_to_entity",
    "detach_from_entity",
}};

template <>
struct field_accessor<v859::CameraInstruction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.set;
        }
        else if constexpr (I == 1) {
            return value.clear;
        }
        else if constexpr (I == 2) {
            return value.fade;
        }
        else if constexpr (I == 3) {
            return value.target;
        }
        else if constexpr (I == 4) {
            return value.remove_target;
        }
        else if constexpr (I == 5) {
            return value.field_of_view;
        }
        else if constexpr (I == 6) {
            return value.spline;
        }
        else if constexpr (I == 7) {
            return value.attach_to_entity;
        }
        else {
            return value.detach_from_entity;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::CameraInstruction> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::CameraInstruction>{"CameraInstruction"};

template <>
inline constexpr std::array<std::string_view, 9> field_names_v<v924::CameraInstruction>{{
    "set",
    "clear",
    "fade",
    "target",
    "remove_target",
    "field_of_view",
    "spline",
    "attach_to_entity",
    "detach_from_entity",
}};

template <>
struct field_accessor<v924::CameraInstruction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.set;
        }
        else if constexpr (I == 1) {
            return value.clear;
        }
        else if constexpr (I == 2) {
            return value.fade;
        }
        else if constexpr (I == 3) {
            return value.target;
        }
        else if constexpr (I == 4) {
            return value.remove_target;
        }
        else if constexpr (I == 5) {
            return value.field_of_view;
        }
        else if constexpr (I == 6) {
            return value.spline;
        }
        else if constexpr (I == 7) {
            return value.attach_to_entity;
        }
        else {
            return value.detach_from_entity;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::CameraInstruction> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::CameraInstruction>{"CameraInstruction"};

template <>
inline constexpr std::array<std::string_view, 9> field_names_v<v944::CameraInstruction>{{
    "set",
    "clear",
    "fade",
    "target",
    "remove_target",
    "field_of_view",
    "spline",
    "attach_to_entity",
    "detach_from_entity",
}};

template <>
struct field_accessor<v944::CameraInstruction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.set;
        }
        else if constexpr (I == 1) {
            return value.clear;
        }
        else if constexpr (I == 2) {
            return value.fade;
        }
        else if constexpr (I == 3) {
            return value.target;
        }
        else if constexpr (I == 4) {
            return value.remove_target;
        }
        else if constexpr (I == 5) {
            return value.field_of_view;
        }
        else if constexpr (I == 6) {
            return value.spline;
        }
        else if constexpr (I == 7) {
            return value.attach_to_entity;
        }
        else {
            return value.detach_from_entity;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::CameraInstructionPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::CameraInstructionPacket>{"CameraInstructionPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::CameraInstructionPacket>{{
    "camera_instruction",
}};

template <>
struct field_accessor<base::CameraInstructionPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.camera_instruction;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v748::CameraInstructionPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v748::CameraInstructionPacket>{"CameraInstructionPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v748::CameraInstructionPacket>{{
    "camera_instruction",
}};

template <>
struct field_accessor<v748::CameraInstructionPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.camera_instruction;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v818::CameraInstructionPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v818::CameraInstructionPacket>{"CameraInstructionPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v818::CameraInstructionPacket>{{
    "camera_instruction",
}};

template <>
struct field_accessor<v818::CameraInstructionPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.camera_instruction;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v827::CameraInstructionPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v827::CameraInstructionPacket>{"CameraInstructionPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v827::CameraInstructionPacket>{{
    "camera_instruction",
}};

template <>
struct field_accessor<v827::CameraInstructionPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.camera_instruction;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v859::CameraInstructionPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v859::CameraInstructionPacket>{"CameraInstructionPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v859::CameraInstructionPacket>{{
    "camera_instruction",
}};

template <>
struct field_accessor<v859::CameraInstructionPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.camera_instruction;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::CameraInstructionPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::CameraInstructionPacket>{"CameraInstructionPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v924::CameraInstructionPacket>{{
    "camera_instruction",
}};

template <>
struct field_accessor<v924::CameraInstructionPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.camera_instruction;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::CameraInstructionPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::CameraInstructionPacket>{"CameraInstructionPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v944::CameraInstructionPacket>{{
    "camera_instruction",
}};

template <>
struct field_accessor<v944::CameraInstructionPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.camera_instruction;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<CameraSplineControlPoint> = true;

template <>
inline constexpr std::string_view struct_name_v<CameraSplineControlPoint>{"CameraSplineControlPoint"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<CameraSplineControlPoint>{{
    "position",
}};

template <>
struct field_accessor<CameraSplineControlPoint> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.position;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<CameraSplineProgressKeyFrame> = true;

template <>
inline constexpr std::string_view struct_name_v<CameraSplineProgressKeyFrame>{"CameraSplineProgressKeyFrame"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<CameraSplineProgressKeyFrame>{{
    "alpha",
    "time_seconds",
    "easing_type",
}};

template <>
struct field_accessor<CameraSplineProgressKeyFrame> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.alpha;
        }
        else if constexpr (I == 1) {
            return value.time_seconds;
        }
        else {
            return value.easing_type;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<CameraSplineRotationKeyFrame> = true;

template <>
inline constexpr std::string_view struct_name_v<CameraSplineRotationKeyFrame>{"CameraSplineRotationKeyFrame"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<CameraSplineRotationKeyFrame>{{
    "rotation",
    "time_seconds",
    "easing_type",
}};

template <>
struct field_accessor<CameraSplineRotationKeyFrame> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.rotation;
        }
        else if constexpr (I == 1) {
            return value.time_seconds;
        }
        else {
            return value.easing_type;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<CameraSplineDefinition> = true;

template <>
inline constexpr std::string_view struct_name_v<CameraSplineDefinition>{"CameraSplineDefinition"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<CameraSplineDefinition>{{
    "name",
    "total_time",
    "spline_type",
    "spline_control_points",
    "spline_progress_frames",
    "spline_rotation_frames",
}};

template <>
struct field_accessor<CameraSplineDefinition> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.name;
        }
        else if constexpr (I == 1) {
            return value.total_time;
        }
        else if constexpr (I == 2) {
            return value.spline_type;
        }
        else if constexpr (I == 3) {
            return value.spline_control_points;
        }
        else if constexpr (I == 4) {
            return value.spline_progress_frames;
        }
        else {
            return value.spline_rotation_frames;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::CameraSplinePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::CameraSplinePacket>{"CameraSplinePacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v924::CameraSplinePacket>{{
    "splines",
}};

template <>
struct field_accessor<v924::CameraSplinePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.splines;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v800::ClientboundControlSchemeSetPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v800::ClientboundControlSchemeSetPacket>{"ClientboundControlSchemeSetPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v800::ClientboundControlSchemeSetPacket>{{
    "control_scheme",
}};

template <>
struct field_accessor<v800::ClientboundControlSchemeSetPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.control_scheme;
    }
};

}  // namespace detail


template <>
struct Serializer<v766::CameraAimAssistCommandPresetDefinition> {
    static void serialize(BinaryWriter &stream, const v766::CameraAimAssistCommandPresetDefinition &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v766::CameraAimAssistCommandPresetDefinition, std::error_code>;
};

template <>
struct Serializer<base::CameraPreset> {
    static void serialize(BinaryWriter &stream, const base::CameraPreset &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::CameraPreset, std::error_code>;
};

template <>
struct Serializer<v748::CameraPreset> {
    static void serialize(BinaryWriter &stream, const v748::CameraPreset &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v748::CameraPreset, std::error_code>;
};

template <>
struct Serializer<v766::CameraPreset> {
    static void serialize(BinaryWriter &stream, const v766::CameraPreset &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v766::CameraPreset, std::error_code>;
};

template <>
struct Serializer<v776::CameraPreset> {
    static void serialize(BinaryWriter &stream, const v776::CameraPreset &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v776::CameraPreset, std::error_code>;
};

template <>
struct Serializer<v800::CameraPreset> {
    static void serialize(BinaryWriter &stream, const v800::CameraPreset &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v800::CameraPreset, std::error_code>;
};

template <>
struct Serializer<v818::CameraPreset> {
    static void serialize(BinaryWriter &stream, const v818::CameraPreset &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v818::CameraPreset, std::error_code>;
};

template <>
struct Serializer<v2193::CameraPreset> {
    static void serialize(BinaryWriter &stream, const v2193::CameraPreset &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::CameraPreset, std::error_code>;
};

template <>
struct Serializer<base::CameraPresets> {
    static void serialize(BinaryWriter &stream, const base::CameraPresets &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::CameraPresets, std::error_code>;
};

template <>
struct Serializer<v748::CameraPresets> {
    static void serialize(BinaryWriter &stream, const v748::CameraPresets &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v748::CameraPresets, std::error_code>;
};

template <>
struct Serializer<v766::CameraPresets> {
    static void serialize(BinaryWriter &stream, const v766::CameraPresets &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v766::CameraPresets, std::error_code>;
};

template <>
struct Serializer<v776::CameraPresets> {
    static void serialize(BinaryWriter &stream, const v776::CameraPresets &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v776::CameraPresets, std::error_code>;
};

template <>
struct Serializer<v800::CameraPresets> {
    static void serialize(BinaryWriter &stream, const v800::CameraPresets &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v800::CameraPresets, std::error_code>;
};

template <>
struct Serializer<v818::CameraPresets> {
    static void serialize(BinaryWriter &stream, const v818::CameraPresets &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v818::CameraPresets, std::error_code>;
};

template <>
struct Serializer<v2193::CameraPresets> {
    static void serialize(BinaryWriter &stream, const v2193::CameraPresets &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::CameraPresets, std::error_code>;
};

template <>
struct Serializer<base::CameraPresetsPacket> {
    static void serialize(BinaryWriter &stream, const base::CameraPresetsPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::CameraPresetsPacket, std::error_code>;
};

template <>
struct Serializer<v748::CameraPresetsPacket> {
    static void serialize(BinaryWriter &stream, const v748::CameraPresetsPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v748::CameraPresetsPacket, std::error_code>;
};

template <>
struct Serializer<v766::CameraPresetsPacket> {
    static void serialize(BinaryWriter &stream, const v766::CameraPresetsPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v766::CameraPresetsPacket, std::error_code>;
};

template <>
struct Serializer<v776::CameraPresetsPacket> {
    static void serialize(BinaryWriter &stream, const v776::CameraPresetsPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v776::CameraPresetsPacket, std::error_code>;
};

template <>
struct Serializer<v800::CameraPresetsPacket> {
    static void serialize(BinaryWriter &stream, const v800::CameraPresetsPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v800::CameraPresetsPacket, std::error_code>;
};

template <>
struct Serializer<v818::CameraPresetsPacket> {
    static void serialize(BinaryWriter &stream, const v818::CameraPresetsPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v818::CameraPresetsPacket, std::error_code>;
};

template <>
struct Serializer<v2193::CameraPresetsPacket> {
    static void serialize(BinaryWriter &stream, const v2193::CameraPresetsPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::CameraPresetsPacket, std::error_code>;
};

template <>
struct Serializer<CameraPacket> {
    static void serialize(BinaryWriter &stream, const CameraPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<CameraPacket, std::error_code>;
};

template <>
struct Serializer<CameraShakePacket> {
    static void serialize(BinaryWriter &stream, const CameraShakePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<CameraShakePacket, std::error_code>;
};

template <>
struct Serializer<CameraAimAssistActorPriority::PriorityData> {
    static void serialize(BinaryWriter &stream, const CameraAimAssistActorPriority::PriorityData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<CameraAimAssistActorPriority::PriorityData, std::error_code>;
};

template <>
struct Serializer<v924::CameraAimAssistActorPriorityPacket> {
    static void serialize(BinaryWriter &stream, const v924::CameraAimAssistActorPriorityPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::CameraAimAssistActorPriorityPacket, std::error_code>;
};

template <>
struct Serializer<v776::ClientCameraAimAssistPacket> {
    static void serialize(BinaryWriter &stream, const v776::ClientCameraAimAssistPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v776::ClientCameraAimAssistPacket, std::error_code>;
};

template <>
struct Serializer<base::CameraAimAssistPacket> {
    static void serialize(BinaryWriter &stream, const base::CameraAimAssistPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::CameraAimAssistPacket, std::error_code>;
};

template <>
struct Serializer<v766::CameraAimAssistPacket> {
    static void serialize(BinaryWriter &stream, const v766::CameraAimAssistPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v766::CameraAimAssistPacket, std::error_code>;
};

template <>
struct Serializer<v827::CameraAimAssistPacket> {
    static void serialize(BinaryWriter &stream, const v827::CameraAimAssistPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v827::CameraAimAssistPacket, std::error_code>;
};

template <>
struct Serializer<v766::CameraAimAssistCategoryPriorities> {
    static void serialize(BinaryWriter &stream, const v766::CameraAimAssistCategoryPriorities &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v766::CameraAimAssistCategoryPriorities, std::error_code>;
};

template <>
struct Serializer<v898::CameraAimAssistCategoryPriorities> {
    static void serialize(BinaryWriter &stream, const v898::CameraAimAssistCategoryPriorities &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v898::CameraAimAssistCategoryPriorities, std::error_code>;
};

template <>
struct Serializer<v924::CameraAimAssistCategoryPriorities> {
    static void serialize(BinaryWriter &stream, const v924::CameraAimAssistCategoryPriorities &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::CameraAimAssistCategoryPriorities, std::error_code>;
};

template <>
struct Serializer<v766::CameraAimAssistCategoryDefinition> {
    static void serialize(BinaryWriter &stream, const v766::CameraAimAssistCategoryDefinition &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v766::CameraAimAssistCategoryDefinition, std::error_code>;
};

template <>
struct Serializer<v898::CameraAimAssistCategoryDefinition> {
    static void serialize(BinaryWriter &stream, const v898::CameraAimAssistCategoryDefinition &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v898::CameraAimAssistCategoryDefinition, std::error_code>;
};

template <>
struct Serializer<v924::CameraAimAssistCategoryDefinition> {
    static void serialize(BinaryWriter &stream, const v924::CameraAimAssistCategoryDefinition &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::CameraAimAssistCategoryDefinition, std::error_code>;
};

template <>
struct Serializer<v898::CameraAimAssistPresetExclusionDefinition> {
    static void serialize(BinaryWriter &stream, const v898::CameraAimAssistPresetExclusionDefinition &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v898::CameraAimAssistPresetExclusionDefinition, std::error_code>;
};

template <>
struct Serializer<v924::CameraAimAssistPresetExclusionDefinition> {
    static void serialize(BinaryWriter &stream, const v924::CameraAimAssistPresetExclusionDefinition &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::CameraAimAssistPresetExclusionDefinition, std::error_code>;
};

template <>
struct Serializer<v766::CameraAimAssistPresetDefinition> {
    static void serialize(BinaryWriter &stream, const v766::CameraAimAssistPresetDefinition &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v766::CameraAimAssistPresetDefinition, std::error_code>;
};

template <>
struct Serializer<v776::CameraAimAssistPresetDefinition> {
    static void serialize(BinaryWriter &stream, const v776::CameraAimAssistPresetDefinition &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v776::CameraAimAssistPresetDefinition, std::error_code>;
};

template <>
struct Serializer<v898::CameraAimAssistPresetDefinition> {
    static void serialize(BinaryWriter &stream, const v898::CameraAimAssistPresetDefinition &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v898::CameraAimAssistPresetDefinition, std::error_code>;
};

template <>
struct Serializer<v924::CameraAimAssistPresetDefinition> {
    static void serialize(BinaryWriter &stream, const v924::CameraAimAssistPresetDefinition &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::CameraAimAssistPresetDefinition, std::error_code>;
};

template <>
struct Serializer<v766::CameraAimAssistCategoriesDefinition> {
    static void serialize(BinaryWriter &stream, const v766::CameraAimAssistCategoriesDefinition &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v766::CameraAimAssistCategoriesDefinition, std::error_code>;
};

template <>
struct Serializer<v766::CameraAimAssistPresetsPacket> {
    static void serialize(BinaryWriter &stream, const v766::CameraAimAssistPresetsPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v766::CameraAimAssistPresetsPacket, std::error_code>;
};

template <>
struct Serializer<v776::CameraAimAssistPresetsPacket> {
    static void serialize(BinaryWriter &stream, const v776::CameraAimAssistPresetsPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v776::CameraAimAssistPresetsPacket, std::error_code>;
};

template <>
struct Serializer<v898::CameraAimAssistPresetsPacket> {
    static void serialize(BinaryWriter &stream, const v898::CameraAimAssistPresetsPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v898::CameraAimAssistPresetsPacket, std::error_code>;
};

template <>
struct Serializer<v924::CameraAimAssistPresetsPacket> {
    static void serialize(BinaryWriter &stream, const v924::CameraAimAssistPresetsPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::CameraAimAssistPresetsPacket, std::error_code>;
};

template <>
struct Serializer<base::CameraInstructionOptions::SetInstruction::EaseOption> {
    static void serialize(BinaryWriter &stream, const base::CameraInstructionOptions::SetInstruction::EaseOption &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::CameraInstructionOptions::SetInstruction::EaseOption, std::error_code>;
};

template <>
struct Serializer<base::CameraInstructionOptions::SetInstruction::PosOption> {
    static void serialize(BinaryWriter &stream, const base::CameraInstructionOptions::SetInstruction::PosOption &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::CameraInstructionOptions::SetInstruction::PosOption, std::error_code>;
};

template <>
struct Serializer<base::CameraInstructionOptions::SetInstruction::RotOption> {
    static void serialize(BinaryWriter &stream, const base::CameraInstructionOptions::SetInstruction::RotOption &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::CameraInstructionOptions::SetInstruction::RotOption, std::error_code>;
};

template <>
struct Serializer<base::CameraInstructionOptions::SetInstruction::FacingOption> {
    static void serialize(BinaryWriter &stream, const base::CameraInstructionOptions::SetInstruction::FacingOption &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::CameraInstructionOptions::SetInstruction::FacingOption, std::error_code>;
};

template <>
struct Serializer<base::CameraInstructionOptions::SetInstruction::ViewOffsetOption> {
    static void serialize(BinaryWriter &stream, const base::CameraInstructionOptions::SetInstruction::ViewOffsetOption &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::CameraInstructionOptions::SetInstruction::ViewOffsetOption, std::error_code>;
};

template <>
struct Serializer<base::CameraInstructionOptions::SetInstruction::EntityOffsetOption> {
    static void serialize(BinaryWriter &stream, const base::CameraInstructionOptions::SetInstruction::EntityOffsetOption &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::CameraInstructionOptions::SetInstruction::EntityOffsetOption, std::error_code>;
};

template <>
struct Serializer<base::CameraInstructionOptions::SetInstruction> {
    static void serialize(BinaryWriter &stream, const base::CameraInstructionOptions::SetInstruction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::CameraInstructionOptions::SetInstruction, std::error_code>;
};

template <>
struct Serializer<base::CameraInstructionOptions::FadeInstruction::TimeOption> {
    static void serialize(BinaryWriter &stream, const base::CameraInstructionOptions::FadeInstruction::TimeOption &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::CameraInstructionOptions::FadeInstruction::TimeOption, std::error_code>;
};

template <>
struct Serializer<base::CameraInstructionOptions::FadeInstruction::ColorOption> {
    static void serialize(BinaryWriter &stream, const base::CameraInstructionOptions::FadeInstruction::ColorOption &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::CameraInstructionOptions::FadeInstruction::ColorOption, std::error_code>;
};

template <>
struct Serializer<base::CameraInstructionOptions::FadeInstruction> {
    static void serialize(BinaryWriter &stream, const base::CameraInstructionOptions::FadeInstruction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::CameraInstructionOptions::FadeInstruction, std::error_code>;
};

template <>
struct Serializer<base::CameraInstructionOptions::TargetInstruction> {
    static void serialize(BinaryWriter &stream, const base::CameraInstructionOptions::TargetInstruction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::CameraInstructionOptions::TargetInstruction, std::error_code>;
};

template <>
struct Serializer<base::CameraInstructionOptions::FovInstruction> {
    static void serialize(BinaryWriter &stream, const base::CameraInstructionOptions::FovInstruction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::CameraInstructionOptions::FovInstruction, std::error_code>;
};

template <>
struct Serializer<base::CameraInstructionOptions::AttachToEntityInstruction> {
    static void serialize(BinaryWriter &stream, const base::CameraInstructionOptions::AttachToEntityInstruction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::CameraInstructionOptions::AttachToEntityInstruction, std::error_code>;
};

template <>
struct Serializer<base::CameraInstructionOptions::SplineInstruction::SplineRotationOption> {
    static void serialize(BinaryWriter &stream, const base::CameraInstructionOptions::SplineInstruction::SplineRotationOption &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::CameraInstructionOptions::SplineInstruction::SplineRotationOption, std::error_code>;
};

template <>
struct Serializer<base::CameraInstructionOptions::SplineInstruction::SplineProgressOption> {
    static void serialize(BinaryWriter &stream, const base::CameraInstructionOptions::SplineInstruction::SplineProgressOption &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::CameraInstructionOptions::SplineInstruction::SplineProgressOption, std::error_code>;
};

template <>
struct Serializer<base::CameraInstructionOptions::SplineInstruction> {
    static void serialize(BinaryWriter &stream, const base::CameraInstructionOptions::SplineInstruction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::CameraInstructionOptions::SplineInstruction, std::error_code>;
};

template <>
struct Serializer<v748::CameraInstructionOptions::SetInstruction::EaseOption> {
    static void serialize(BinaryWriter &stream, const v748::CameraInstructionOptions::SetInstruction::EaseOption &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v748::CameraInstructionOptions::SetInstruction::EaseOption, std::error_code>;
};

template <>
struct Serializer<v748::CameraInstructionOptions::SetInstruction::PosOption> {
    static void serialize(BinaryWriter &stream, const v748::CameraInstructionOptions::SetInstruction::PosOption &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v748::CameraInstructionOptions::SetInstruction::PosOption, std::error_code>;
};

template <>
struct Serializer<v748::CameraInstructionOptions::SetInstruction::RotOption> {
    static void serialize(BinaryWriter &stream, const v748::CameraInstructionOptions::SetInstruction::RotOption &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v748::CameraInstructionOptions::SetInstruction::RotOption, std::error_code>;
};

template <>
struct Serializer<v748::CameraInstructionOptions::SetInstruction::FacingOption> {
    static void serialize(BinaryWriter &stream, const v748::CameraInstructionOptions::SetInstruction::FacingOption &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v748::CameraInstructionOptions::SetInstruction::FacingOption, std::error_code>;
};

template <>
struct Serializer<v748::CameraInstructionOptions::SetInstruction::ViewOffsetOption> {
    static void serialize(BinaryWriter &stream, const v748::CameraInstructionOptions::SetInstruction::ViewOffsetOption &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v748::CameraInstructionOptions::SetInstruction::ViewOffsetOption, std::error_code>;
};

template <>
struct Serializer<v748::CameraInstructionOptions::SetInstruction::EntityOffsetOption> {
    static void serialize(BinaryWriter &stream, const v748::CameraInstructionOptions::SetInstruction::EntityOffsetOption &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v748::CameraInstructionOptions::SetInstruction::EntityOffsetOption, std::error_code>;
};

template <>
struct Serializer<v748::CameraInstructionOptions::SetInstruction> {
    static void serialize(BinaryWriter &stream, const v748::CameraInstructionOptions::SetInstruction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v748::CameraInstructionOptions::SetInstruction, std::error_code>;
};

template <>
struct Serializer<v748::CameraInstructionOptions::SplineInstruction::SplineRotationOption> {
    static void serialize(BinaryWriter &stream, const v748::CameraInstructionOptions::SplineInstruction::SplineRotationOption &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v748::CameraInstructionOptions::SplineInstruction::SplineRotationOption, std::error_code>;
};

template <>
struct Serializer<v748::CameraInstructionOptions::SplineInstruction::SplineProgressOption> {
    static void serialize(BinaryWriter &stream, const v748::CameraInstructionOptions::SplineInstruction::SplineProgressOption &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v748::CameraInstructionOptions::SplineInstruction::SplineProgressOption, std::error_code>;
};

template <>
struct Serializer<v748::CameraInstructionOptions::SplineInstruction> {
    static void serialize(BinaryWriter &stream, const v748::CameraInstructionOptions::SplineInstruction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v748::CameraInstructionOptions::SplineInstruction, std::error_code>;
};

template <>
struct Serializer<v818::CameraInstructionOptions::SetInstruction::EaseOption> {
    static void serialize(BinaryWriter &stream, const v818::CameraInstructionOptions::SetInstruction::EaseOption &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v818::CameraInstructionOptions::SetInstruction::EaseOption, std::error_code>;
};

template <>
struct Serializer<v818::CameraInstructionOptions::SetInstruction::PosOption> {
    static void serialize(BinaryWriter &stream, const v818::CameraInstructionOptions::SetInstruction::PosOption &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v818::CameraInstructionOptions::SetInstruction::PosOption, std::error_code>;
};

template <>
struct Serializer<v818::CameraInstructionOptions::SetInstruction::RotOption> {
    static void serialize(BinaryWriter &stream, const v818::CameraInstructionOptions::SetInstruction::RotOption &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v818::CameraInstructionOptions::SetInstruction::RotOption, std::error_code>;
};

template <>
struct Serializer<v818::CameraInstructionOptions::SetInstruction::FacingOption> {
    static void serialize(BinaryWriter &stream, const v818::CameraInstructionOptions::SetInstruction::FacingOption &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v818::CameraInstructionOptions::SetInstruction::FacingOption, std::error_code>;
};

template <>
struct Serializer<v818::CameraInstructionOptions::SetInstruction::ViewOffsetOption> {
    static void serialize(BinaryWriter &stream, const v818::CameraInstructionOptions::SetInstruction::ViewOffsetOption &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v818::CameraInstructionOptions::SetInstruction::ViewOffsetOption, std::error_code>;
};

template <>
struct Serializer<v818::CameraInstructionOptions::SetInstruction::EntityOffsetOption> {
    static void serialize(BinaryWriter &stream, const v818::CameraInstructionOptions::SetInstruction::EntityOffsetOption &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v818::CameraInstructionOptions::SetInstruction::EntityOffsetOption, std::error_code>;
};

template <>
struct Serializer<v818::CameraInstructionOptions::SetInstruction> {
    static void serialize(BinaryWriter &stream, const v818::CameraInstructionOptions::SetInstruction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v818::CameraInstructionOptions::SetInstruction, std::error_code>;
};

template <>
struct Serializer<v818::CameraInstructionOptions::SplineInstruction::SplineRotationOption> {
    static void serialize(BinaryWriter &stream, const v818::CameraInstructionOptions::SplineInstruction::SplineRotationOption &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v818::CameraInstructionOptions::SplineInstruction::SplineRotationOption, std::error_code>;
};

template <>
struct Serializer<v818::CameraInstructionOptions::SplineInstruction::SplineProgressOption> {
    static void serialize(BinaryWriter &stream, const v818::CameraInstructionOptions::SplineInstruction::SplineProgressOption &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v818::CameraInstructionOptions::SplineInstruction::SplineProgressOption, std::error_code>;
};

template <>
struct Serializer<v818::CameraInstructionOptions::SplineInstruction> {
    static void serialize(BinaryWriter &stream, const v818::CameraInstructionOptions::SplineInstruction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v818::CameraInstructionOptions::SplineInstruction, std::error_code>;
};

template <>
struct Serializer<v924::CameraInstructionOptions::SetInstruction::EaseOption> {
    static void serialize(BinaryWriter &stream, const v924::CameraInstructionOptions::SetInstruction::EaseOption &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::CameraInstructionOptions::SetInstruction::EaseOption, std::error_code>;
};

template <>
struct Serializer<v924::CameraInstructionOptions::SetInstruction::PosOption> {
    static void serialize(BinaryWriter &stream, const v924::CameraInstructionOptions::SetInstruction::PosOption &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::CameraInstructionOptions::SetInstruction::PosOption, std::error_code>;
};

template <>
struct Serializer<v924::CameraInstructionOptions::SetInstruction::RotOption> {
    static void serialize(BinaryWriter &stream, const v924::CameraInstructionOptions::SetInstruction::RotOption &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::CameraInstructionOptions::SetInstruction::RotOption, std::error_code>;
};

template <>
struct Serializer<v924::CameraInstructionOptions::SetInstruction::FacingOption> {
    static void serialize(BinaryWriter &stream, const v924::CameraInstructionOptions::SetInstruction::FacingOption &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::CameraInstructionOptions::SetInstruction::FacingOption, std::error_code>;
};

template <>
struct Serializer<v924::CameraInstructionOptions::SetInstruction::ViewOffsetOption> {
    static void serialize(BinaryWriter &stream, const v924::CameraInstructionOptions::SetInstruction::ViewOffsetOption &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::CameraInstructionOptions::SetInstruction::ViewOffsetOption, std::error_code>;
};

template <>
struct Serializer<v924::CameraInstructionOptions::SetInstruction::EntityOffsetOption> {
    static void serialize(BinaryWriter &stream, const v924::CameraInstructionOptions::SetInstruction::EntityOffsetOption &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::CameraInstructionOptions::SetInstruction::EntityOffsetOption, std::error_code>;
};

template <>
struct Serializer<v924::CameraInstructionOptions::SetInstruction> {
    static void serialize(BinaryWriter &stream, const v924::CameraInstructionOptions::SetInstruction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::CameraInstructionOptions::SetInstruction, std::error_code>;
};

template <>
struct Serializer<v924::CameraInstructionOptions::SplineInstruction::SplineRotationOption> {
    static void serialize(BinaryWriter &stream, const v924::CameraInstructionOptions::SplineInstruction::SplineRotationOption &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::CameraInstructionOptions::SplineInstruction::SplineRotationOption, std::error_code>;
};

template <>
struct Serializer<v924::CameraInstructionOptions::SplineInstruction::SplineProgressOption> {
    static void serialize(BinaryWriter &stream, const v924::CameraInstructionOptions::SplineInstruction::SplineProgressOption &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::CameraInstructionOptions::SplineInstruction::SplineProgressOption, std::error_code>;
};

template <>
struct Serializer<v924::CameraInstructionOptions::SplineInstruction> {
    static void serialize(BinaryWriter &stream, const v924::CameraInstructionOptions::SplineInstruction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::CameraInstructionOptions::SplineInstruction, std::error_code>;
};

template <>
struct Serializer<v944::CameraInstructionOptions::SetInstruction::EaseOption> {
    static void serialize(BinaryWriter &stream, const v944::CameraInstructionOptions::SetInstruction::EaseOption &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::CameraInstructionOptions::SetInstruction::EaseOption, std::error_code>;
};

template <>
struct Serializer<v944::CameraInstructionOptions::SetInstruction::PosOption> {
    static void serialize(BinaryWriter &stream, const v944::CameraInstructionOptions::SetInstruction::PosOption &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::CameraInstructionOptions::SetInstruction::PosOption, std::error_code>;
};

template <>
struct Serializer<v944::CameraInstructionOptions::SetInstruction::RotOption> {
    static void serialize(BinaryWriter &stream, const v944::CameraInstructionOptions::SetInstruction::RotOption &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::CameraInstructionOptions::SetInstruction::RotOption, std::error_code>;
};

template <>
struct Serializer<v944::CameraInstructionOptions::SetInstruction::FacingOption> {
    static void serialize(BinaryWriter &stream, const v944::CameraInstructionOptions::SetInstruction::FacingOption &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::CameraInstructionOptions::SetInstruction::FacingOption, std::error_code>;
};

template <>
struct Serializer<v944::CameraInstructionOptions::SetInstruction::ViewOffsetOption> {
    static void serialize(BinaryWriter &stream, const v944::CameraInstructionOptions::SetInstruction::ViewOffsetOption &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::CameraInstructionOptions::SetInstruction::ViewOffsetOption, std::error_code>;
};

template <>
struct Serializer<v944::CameraInstructionOptions::SetInstruction::EntityOffsetOption> {
    static void serialize(BinaryWriter &stream, const v944::CameraInstructionOptions::SetInstruction::EntityOffsetOption &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::CameraInstructionOptions::SetInstruction::EntityOffsetOption, std::error_code>;
};

template <>
struct Serializer<v944::CameraInstructionOptions::SetInstruction> {
    static void serialize(BinaryWriter &stream, const v944::CameraInstructionOptions::SetInstruction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::CameraInstructionOptions::SetInstruction, std::error_code>;
};

template <>
struct Serializer<v944::CameraInstructionOptions::SplineInstruction::SplineRotationOption> {
    static void serialize(BinaryWriter &stream, const v944::CameraInstructionOptions::SplineInstruction::SplineRotationOption &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::CameraInstructionOptions::SplineInstruction::SplineRotationOption, std::error_code>;
};

template <>
struct Serializer<v944::CameraInstructionOptions::SplineInstruction::SplineProgressOption> {
    static void serialize(BinaryWriter &stream, const v944::CameraInstructionOptions::SplineInstruction::SplineProgressOption &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::CameraInstructionOptions::SplineInstruction::SplineProgressOption, std::error_code>;
};

template <>
struct Serializer<v944::CameraInstructionOptions::SplineInstruction> {
    static void serialize(BinaryWriter &stream, const v944::CameraInstructionOptions::SplineInstruction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::CameraInstructionOptions::SplineInstruction, std::error_code>;
};

template <>
struct Serializer<base::CameraInstruction> {
    static void serialize(BinaryWriter &stream, const base::CameraInstruction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::CameraInstruction, std::error_code>;
};

template <>
struct Serializer<v748::CameraInstruction> {
    static void serialize(BinaryWriter &stream, const v748::CameraInstruction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v748::CameraInstruction, std::error_code>;
};

template <>
struct Serializer<v818::CameraInstruction> {
    static void serialize(BinaryWriter &stream, const v818::CameraInstruction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v818::CameraInstruction, std::error_code>;
};

template <>
struct Serializer<v827::CameraInstruction> {
    static void serialize(BinaryWriter &stream, const v827::CameraInstruction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v827::CameraInstruction, std::error_code>;
};

template <>
struct Serializer<v859::CameraInstruction> {
    static void serialize(BinaryWriter &stream, const v859::CameraInstruction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v859::CameraInstruction, std::error_code>;
};

template <>
struct Serializer<v924::CameraInstruction> {
    static void serialize(BinaryWriter &stream, const v924::CameraInstruction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::CameraInstruction, std::error_code>;
};

template <>
struct Serializer<v944::CameraInstruction> {
    static void serialize(BinaryWriter &stream, const v944::CameraInstruction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::CameraInstruction, std::error_code>;
};

template <>
struct Serializer<base::CameraInstructionPacket> {
    static void serialize(BinaryWriter &stream, const base::CameraInstructionPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::CameraInstructionPacket, std::error_code>;
};

template <>
struct Serializer<v748::CameraInstructionPacket> {
    static void serialize(BinaryWriter &stream, const v748::CameraInstructionPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v748::CameraInstructionPacket, std::error_code>;
};

template <>
struct Serializer<v818::CameraInstructionPacket> {
    static void serialize(BinaryWriter &stream, const v818::CameraInstructionPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v818::CameraInstructionPacket, std::error_code>;
};

template <>
struct Serializer<v827::CameraInstructionPacket> {
    static void serialize(BinaryWriter &stream, const v827::CameraInstructionPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v827::CameraInstructionPacket, std::error_code>;
};

template <>
struct Serializer<v859::CameraInstructionPacket> {
    static void serialize(BinaryWriter &stream, const v859::CameraInstructionPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v859::CameraInstructionPacket, std::error_code>;
};

template <>
struct Serializer<v924::CameraInstructionPacket> {
    static void serialize(BinaryWriter &stream, const v924::CameraInstructionPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::CameraInstructionPacket, std::error_code>;
};

template <>
struct Serializer<v944::CameraInstructionPacket> {
    static void serialize(BinaryWriter &stream, const v944::CameraInstructionPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::CameraInstructionPacket, std::error_code>;
};

template <>
struct Serializer<CameraSplineControlPoint> {
    static void serialize(BinaryWriter &stream, const CameraSplineControlPoint &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<CameraSplineControlPoint, std::error_code>;
};

template <>
struct Serializer<CameraSplineProgressKeyFrame> {
    static void serialize(BinaryWriter &stream, const CameraSplineProgressKeyFrame &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<CameraSplineProgressKeyFrame, std::error_code>;
};

template <>
struct Serializer<CameraSplineRotationKeyFrame> {
    static void serialize(BinaryWriter &stream, const CameraSplineRotationKeyFrame &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<CameraSplineRotationKeyFrame, std::error_code>;
};

template <>
struct Serializer<CameraSplineDefinition> {
    static void serialize(BinaryWriter &stream, const CameraSplineDefinition &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<CameraSplineDefinition, std::error_code>;
};

template <>
struct Serializer<v924::CameraSplinePacket> {
    static void serialize(BinaryWriter &stream, const v924::CameraSplinePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::CameraSplinePacket, std::error_code>;
};

template <>
struct Serializer<v800::ClientboundControlSchemeSetPacket> {
    static void serialize(BinaryWriter &stream, const v800::ClientboundControlSchemeSetPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v800::ClientboundControlSchemeSetPacket, std::error_code>;
};
using TargetMode = TargetMode_<2225>;
using CameraAimAssistCommandPresetDefinition = CameraAimAssistCommandPresetDefinition_<2225>;
using CameraPreset = CameraPreset_<2225>;
using CameraPresets = CameraPresets_<2225>;
using CameraPresetsPacket = CameraPresetsPacket_<2225>;
using CameraAimAssistActorPriorityPacket = CameraAimAssistActorPriorityPacket_<2225>;
using ClientCameraAimAssistPacketAction = ClientCameraAimAssistPacketAction_<2225>;
using ClientCameraAimAssistPacket = ClientCameraAimAssistPacket_<2225>;
using CameraAimAssistPacket = CameraAimAssistPacket_<2225>;
using CameraAimAssistCategoryPriorities = CameraAimAssistCategoryPriorities_<2225>;
using CameraAimAssistCategoryDefinition = CameraAimAssistCategoryDefinition_<2225>;
using CameraAimAssistPresetExclusionDefinition = CameraAimAssistPresetExclusionDefinition_<2225>;
using CameraAimAssistPresetDefinition = CameraAimAssistPresetDefinition_<2225>;
using CameraAimAssistPresetsPacketOperation = CameraAimAssistPresetsPacketOperation_<2225>;
using CameraAimAssistPresetsPacket = CameraAimAssistPresetsPacket_<2225>;
using CameraInstructionOptions = CameraInstructionOptions_<2225>;
using CameraInstruction = CameraInstruction_<2225>;
using CameraInstructionPacket = CameraInstructionPacket_<2225>;
using CameraSplinePacket = CameraSplinePacket_<2225>;
using ClientboundControlSchemeSetPacket = ClientboundControlSchemeSetPacket_<2225>;

}  // namespace bedrock::protocol
