#pragma once

#include <array>
#include <bitset>
#include <cstddef>
#include <cstdint>
#include <expected>
#include <optional>
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
#include <bedrock/protocol/item.h>
#include <bedrock/protocol/item_stack.h>
#include <bedrock/protocol/network.h>
#include <bedrock/protocol/transaction.h>

namespace bedrock::protocol {

enum class InputMode : std::uint32_t {
    Undefined = 0,
    Mouse = 1,
    Touch = 2,
    GamePad = 3,
    MotionControllerDeprecated = 4,
    Count = 5,
};

enum class ClientPlayMode : std::uint32_t {
    Normal = 0,
    Teaser = 1,
    Screen = 2,
    ViewerDeprecated = 3,
    RealityDeprecated = 4,
    PlacementDeprecated = 5,
    LivingRoomDeprecated = 6,
    ExitLevel = 7,
    ExitLevelLivingRoomDeprecated = 8,
    NumModes = 9,
};

enum class NewInteractionModel : int {
    Touch = 0,
    Crosshair = 1,
    Classic = 2,
    Count = 3,
};

namespace base {

enum class PlayerActionType : int {
    Unknown = -1,
    StartDestroyBlock = 0,
    AbortDestroyBlock = 1,
    StopDestroyBlock = 2,
    GetUpdatedBlock = 3,
    DropItem = 4,
    StartSleeping = 5,
    StopSleeping = 6,
    Respawn = 7,
    StartJump = 8,
    StartSprinting = 9,
    StopSprinting = 10,
    StartSneaking = 11,
    StopSneaking = 12,
    CreativeDestroyBlock = 13,
    ChangeDimensionAck = 14,
    StartGliding = 15,
    StopGliding = 16,
    DenyDestroyBlock = 17,
    CrackBlock = 18,
    ChangeSkin = 19,
    DeprecatedUpdatedEnchantingSeed = 20,
    StartSwimming = 21,
    StopSwimming = 22,
    StartSpinAttack = 23,
    StopSpinAttack = 24,
    InteractWithBlock = 25,
    PredictDestroyBlock = 26,
    ContinueDestroyBlock = 27,
    StartItemUseOn = 28,
    StopItemUseOn = 29,
    HandledTeleport = 30,
    MissedSwing = 31,
    StartCrawling = 32,
    StopCrawling = 33,
    StartFlying = 34,
    StopFlying = 35,
    DeprecatedClientAckServerData = 36,
    Count = 37,
};

struct PlayerBlockActionData {
    base::PlayerActionType player_action_type{};
    BlockPos pos{};
    std::int32_t facing{};
};

struct PackedItemUseLegacyInventoryTransaction {
    std::int32_t id{};
    std::vector<base::LegacySetSlot> slots{};
    legacy::base::ItemUseInventoryTransaction transaction{};
};

namespace PlayerAuthInputPacket_nested {

enum class InputData : std::uint32_t {
    Ascend = 0,
    Descend = 1,
    NorthJumpDeprecated = 2,
    JumpDown = 3,
    SprintDown = 4,
    ChangeHeight = 5,
    Jumping = 6,
    AutoJumpingInWater = 7,
    Sneaking = 8,
    SneakDown = 9,
    Up = 10,
    Down = 11,
    Left = 12,
    Right = 13,
    UpLeft = 14,
    UpRight = 15,
    WantUp = 16,
    WantDown = 17,
    WantDownSlow = 18,
    WantUpSlow = 19,
    Sprinting = 20,
    AscendBlock = 21,
    DescendBlock = 22,
    SneakToggleDown = 23,
    PersistSneak = 24,
    StartSprinting = 25,
    StopSprinting = 26,
    StartSneaking = 27,
    StopSneaking = 28,
    StartSwimming = 29,
    StopSwimming = 30,
    StartJumping = 31,
    StartGliding = 32,
    StopGliding = 33,
    PerformItemInteraction = 34,
    PerformBlockActions = 35,
    PerformItemStackRequest = 36,
    HandledTeleport = 37,
    Emoting = 38,
    MissedSwing = 39,
    StartCrawling = 40,
    StopCrawling = 41,
    StartFlying = 42,
    StopFlying = 43,
    ClientAckServerData = 44,
    IsInClientPredictedVehicle = 45,
    PaddlingLeft = 46,
    PaddlingRight = 47,
    BlockBreakingDelayEnabled = 48,
    HorizontalCollision = 49,
    VerticalCollision = 50,
    DownLeft = 51,
    DownRight = 52,
    InputNum = 53,
};

}  // namespace PlayerAuthInputPacket_nested

struct PlayerAuthInputPacket {
    using InputData = PlayerAuthInputPacket_nested::InputData;

    static constexpr int Id = 144;
    Vec2 rot{};
    Vec3 pos{};
    Vec2 move{};
    float y_head_rot{};
    std::bitset<53> input_data{};
    InputMode input_mode{};
    ClientPlayMode play_mode{};
    NewInteractionModel new_interaction_model{};
    Vec3 gaze_direction{};
    PlayerInputTick client_tick{};
    Vec3 pos_delta{};
    base::PackedItemUseLegacyInventoryTransaction item_use_transaction{};
    base::ItemStackRequestData item_stack_request{};
    std::vector<base::PlayerBlockActionData> player_block_actions{};
    Vec2 vehicle_rot{};
    ActorUniqueID client_predicted_vehicle{};
    Vec2 analog_move_vector{};
};

struct PlayerActionPacket {
    static constexpr int Id = 36;
    ActorRuntimeID runtime_id{};
    base::PlayerActionType action{};
    base::NetworkBlockPosition pos{};
    base::NetworkBlockPosition result_pos{};
    std::int32_t face{};
};

struct UpdateClientInputLocksPacket {
    static constexpr int Id = 196;
    std::uint32_t input_lock_component_data{};
    Vec3 server_pos{};
};

struct PassengerJumpPacket {
    static constexpr int Id = 20;
    std::int32_t jump_scale{};
};

struct PlayerInputPacket {
    static constexpr int Id = 57;
    Vec2 mov{};
    bool is_jumping{};
    bool is_sneaking{};
};

}  // namespace base

namespace v748 {

enum class PlayerActionType : int {
    Unknown = -1,
    StartDestroyBlock = 0,
    AbortDestroyBlock = 1,
    StopDestroyBlock = 2,
    GetUpdatedBlock = 3,
    DropItem = 4,
    StartSleeping = 5,
    StopSleeping = 6,
    Respawn = 7,
    StartJump = 8,
    StartSprinting = 9,
    StopSprinting = 10,
    StartSneaking = 11,
    StopSneaking = 12,
    CreativeDestroyBlock = 13,
    ChangeDimensionAck = 14,
    StartGliding = 15,
    StopGliding = 16,
    DenyDestroyBlock = 17,
    CrackBlock = 18,
    ChangeSkin = 19,
    DeprecatedUpdatedEnchantingSeed = 20,
    StartSwimming = 21,
    StopSwimming = 22,
    StartSpinAttack = 23,
    StopSpinAttack = 24,
    InteractWithBlock = 25,
    PredictDestroyBlock = 26,
    ContinueDestroyBlock = 27,
    StartItemUseOn = 28,
    StopItemUseOn = 29,
    HandledTeleport = 30,
    MissedSwing = 31,
    StartCrawling = 32,
    StopCrawling = 33,
    StartFlying = 34,
    StopFlying = 35,
    DeprecatedClientAckServerData = 36,
    StartUsingItem = 37,
    Count = 38,
};

struct PlayerBlockActionData {
    v748::PlayerActionType player_action_type{};
    BlockPos pos{};
    std::int32_t facing{};
};

struct PackedItemUseLegacyInventoryTransaction {
    std::int32_t id{};
    std::vector<base::LegacySetSlot> slots{};
    legacy::v748::ItemUseInventoryTransaction transaction{};
};

namespace PlayerAuthInputPacket_nested {

enum class InputData : std::uint32_t {
    Ascend = 0,
    Descend = 1,
    NorthJumpDeprecated = 2,
    JumpDown = 3,
    SprintDown = 4,
    ChangeHeight = 5,
    Jumping = 6,
    AutoJumpingInWater = 7,
    Sneaking = 8,
    SneakDown = 9,
    Up = 10,
    Down = 11,
    Left = 12,
    Right = 13,
    UpLeft = 14,
    UpRight = 15,
    WantUp = 16,
    WantDown = 17,
    WantDownSlow = 18,
    WantUpSlow = 19,
    Sprinting = 20,
    AscendBlock = 21,
    DescendBlock = 22,
    SneakToggleDown = 23,
    PersistSneak = 24,
    StartSprinting = 25,
    StopSprinting = 26,
    StartSneaking = 27,
    StopSneaking = 28,
    StartSwimming = 29,
    StopSwimming = 30,
    StartJumping = 31,
    StartGliding = 32,
    StopGliding = 33,
    PerformItemInteraction = 34,
    PerformBlockActions = 35,
    PerformItemStackRequest = 36,
    HandledTeleport = 37,
    Emoting = 38,
    MissedSwing = 39,
    StartCrawling = 40,
    StopCrawling = 41,
    StartFlying = 42,
    StopFlying = 43,
    ClientAckServerData = 44,
    IsInClientPredictedVehicle = 45,
    PaddlingLeft = 46,
    PaddlingRight = 47,
    BlockBreakingDelayEnabled = 48,
    HorizontalCollision = 49,
    VerticalCollision = 50,
    DownLeft = 51,
    DownRight = 52,
    StartUsingItem = 53,
    IsCameraRelativeMovementEnabledDeprecated = 54,
    IsRotControlledByMoveDirectionDeprecated = 55,
    StartSpinAttack = 56,
    StopSpinAttack = 57,
    InputNum = 58,
};

}  // namespace PlayerAuthInputPacket_nested

struct PlayerAuthInputPacket {
    using InputData = PlayerAuthInputPacket_nested::InputData;

    static constexpr int Id = 144;
    Vec2 rot{};
    Vec3 pos{};
    Vec2 move{};
    float y_head_rot{};
    std::bitset<58> input_data{};
    InputMode input_mode{};
    ClientPlayMode play_mode{};
    NewInteractionModel new_interaction_model{};
    Vec2 interact_rotation{};
    PlayerInputTick client_tick{};
    Vec3 pos_delta{};
    v748::PackedItemUseLegacyInventoryTransaction item_use_transaction{};
    base::ItemStackRequestData item_stack_request{};
    std::vector<v748::PlayerBlockActionData> player_block_actions{};
    Vec2 vehicle_rot{};
    ActorUniqueID client_predicted_vehicle{};
    Vec2 analog_move_vector{};
    Vec3 camera_orientation{};
};

struct PlayerActionPacket {
    static constexpr int Id = 36;
    ActorRuntimeID runtime_id{};
    v748::PlayerActionType action{};
    base::NetworkBlockPosition pos{};
    base::NetworkBlockPosition result_pos{};
    std::int32_t face{};
};

using UpdateClientInputLocksPacket = base::UpdateClientInputLocksPacket;

using PassengerJumpPacket = base::PassengerJumpPacket;

using PlayerInputPacket = base::PlayerInputPacket;

}  // namespace v748

namespace v766 {

using PlayerActionType = v748::PlayerActionType;

using PlayerBlockActionData = v748::PlayerBlockActionData;

using PackedItemUseLegacyInventoryTransaction = v748::PackedItemUseLegacyInventoryTransaction;

namespace PlayerAuthInputPacket_nested {

enum class InputData : std::uint32_t {
    Ascend = 0,
    Descend = 1,
    NorthJumpDeprecated = 2,
    JumpDown = 3,
    SprintDown = 4,
    ChangeHeight = 5,
    Jumping = 6,
    AutoJumpingInWater = 7,
    Sneaking = 8,
    SneakDown = 9,
    Up = 10,
    Down = 11,
    Left = 12,
    Right = 13,
    UpLeft = 14,
    UpRight = 15,
    WantUp = 16,
    WantDown = 17,
    WantDownSlow = 18,
    WantUpSlow = 19,
    Sprinting = 20,
    AscendBlock = 21,
    DescendBlock = 22,
    SneakToggleDown = 23,
    PersistSneak = 24,
    StartSprinting = 25,
    StopSprinting = 26,
    StartSneaking = 27,
    StopSneaking = 28,
    StartSwimming = 29,
    StopSwimming = 30,
    StartJumping = 31,
    StartGliding = 32,
    StopGliding = 33,
    PerformItemInteraction = 34,
    PerformBlockActions = 35,
    PerformItemStackRequest = 36,
    HandledTeleport = 37,
    Emoting = 38,
    MissedSwing = 39,
    StartCrawling = 40,
    StopCrawling = 41,
    StartFlying = 42,
    StopFlying = 43,
    ClientAckServerData = 44,
    IsInClientPredictedVehicle = 45,
    PaddlingLeft = 46,
    PaddlingRight = 47,
    BlockBreakingDelayEnabled = 48,
    HorizontalCollision = 49,
    VerticalCollision = 50,
    DownLeft = 51,
    DownRight = 52,
    StartUsingItem = 53,
    IsCameraRelativeMovementEnabledDeprecated = 54,
    IsRotControlledByMoveDirectionDeprecated = 55,
    StartSpinAttack = 56,
    StopSpinAttack = 57,
    IsHotbarOnlyTouch = 58,
    JumpReleasedRaw = 59,
    JumpPressedRaw = 60,
    JumpCurrentRaw = 61,
    SneakReleasedRaw = 62,
    SneakPressedRaw = 63,
    SneakCurrentRaw = 64,
    InputNum = 65,
};

}  // namespace PlayerAuthInputPacket_nested

struct PlayerAuthInputPacket {
    using InputData = PlayerAuthInputPacket_nested::InputData;

    static constexpr int Id = 144;
    Vec2 rot{};
    Vec3 pos{};
    Vec2 move{};
    float y_head_rot{};
    std::bitset<65> input_data{};
    InputMode input_mode{};
    ClientPlayMode play_mode{};
    NewInteractionModel new_interaction_model{};
    Vec2 interact_rotation{};
    PlayerInputTick client_tick{};
    Vec3 pos_delta{};
    v748::PackedItemUseLegacyInventoryTransaction item_use_transaction{};
    base::ItemStackRequestData item_stack_request{};
    std::vector<v748::PlayerBlockActionData> player_block_actions{};
    Vec2 vehicle_rot{};
    ActorUniqueID client_predicted_vehicle{};
    Vec2 analog_move_vector{};
    Vec3 camera_orientation{};
    Vec2 raw_move_vector{};
};

using PlayerActionPacket = v748::PlayerActionPacket;

using UpdateClientInputLocksPacket = base::UpdateClientInputLocksPacket;

using PassengerJumpPacket = base::PassengerJumpPacket;

using PlayerInputPacket = base::PlayerInputPacket;

}  // namespace v766

namespace v776 {

using PlayerActionType = v748::PlayerActionType;

using PlayerBlockActionData = v748::PlayerBlockActionData;

using PackedItemUseLegacyInventoryTransaction = v748::PackedItemUseLegacyInventoryTransaction;

using PlayerAuthInputPacket = v766::PlayerAuthInputPacket;

using PlayerActionPacket = v748::PlayerActionPacket;

using UpdateClientInputLocksPacket = base::UpdateClientInputLocksPacket;

using PassengerJumpPacket = base::PassengerJumpPacket;

using PlayerInputPacket = base::PlayerInputPacket;

}  // namespace v776

namespace v786 {

using PlayerActionType = v748::PlayerActionType;

using PlayerBlockActionData = v748::PlayerBlockActionData;

using PackedItemUseLegacyInventoryTransaction = v748::PackedItemUseLegacyInventoryTransaction;

using PlayerAuthInputPacket = v766::PlayerAuthInputPacket;

using PlayerActionPacket = v748::PlayerActionPacket;

using UpdateClientInputLocksPacket = base::UpdateClientInputLocksPacket;

using PassengerJumpPacket = base::PassengerJumpPacket;

using PlayerInputPacket = base::PlayerInputPacket;

}  // namespace v786

namespace v800 {

using PlayerActionType = v748::PlayerActionType;

using PlayerBlockActionData = v748::PlayerBlockActionData;

using PackedItemUseLegacyInventoryTransaction = v748::PackedItemUseLegacyInventoryTransaction;

using PlayerAuthInputPacket = v766::PlayerAuthInputPacket;

using PlayerActionPacket = v748::PlayerActionPacket;

using UpdateClientInputLocksPacket = base::UpdateClientInputLocksPacket;

}  // namespace v800

namespace v818 {

using PlayerActionType = v748::PlayerActionType;

using PlayerBlockActionData = v748::PlayerBlockActionData;

using PackedItemUseLegacyInventoryTransaction = v748::PackedItemUseLegacyInventoryTransaction;

using PlayerAuthInputPacket = v766::PlayerAuthInputPacket;

using PlayerActionPacket = v748::PlayerActionPacket;

using UpdateClientInputLocksPacket = base::UpdateClientInputLocksPacket;

}  // namespace v818

namespace v827 {

using PlayerActionType = v748::PlayerActionType;

using PlayerBlockActionData = v748::PlayerBlockActionData;

using PackedItemUseLegacyInventoryTransaction = v748::PackedItemUseLegacyInventoryTransaction;

using PlayerAuthInputPacket = v766::PlayerAuthInputPacket;

using PlayerActionPacket = v748::PlayerActionPacket;

using UpdateClientInputLocksPacket = base::UpdateClientInputLocksPacket;

}  // namespace v827

namespace v844 {

using PlayerActionType = v748::PlayerActionType;

using PlayerBlockActionData = v748::PlayerBlockActionData;

struct PackedItemUseLegacyInventoryTransaction {
    std::int32_t id{};
    std::vector<base::LegacySetSlot> slots{};
    legacy::v844::ItemUseInventoryTransaction transaction{};
};

namespace PlayerAuthInputPacket_nested {

enum class InputData : std::uint32_t {
    Ascend = 0,
    Descend = 1,
    NorthJumpDeprecated = 2,
    JumpDown = 3,
    SprintDown = 4,
    ChangeHeight = 5,
    Jumping = 6,
    AutoJumpingInWater = 7,
    Sneaking = 8,
    SneakDown = 9,
    Up = 10,
    Down = 11,
    Left = 12,
    Right = 13,
    UpLeft = 14,
    UpRight = 15,
    WantUp = 16,
    WantDown = 17,
    WantDownSlow = 18,
    WantUpSlow = 19,
    Sprinting = 20,
    AscendBlock = 21,
    DescendBlock = 22,
    SneakToggleDown = 23,
    PersistSneak = 24,
    StartSprinting = 25,
    StopSprinting = 26,
    StartSneaking = 27,
    StopSneaking = 28,
    StartSwimming = 29,
    StopSwimming = 30,
    StartJumping = 31,
    StartGliding = 32,
    StopGliding = 33,
    PerformItemInteraction = 34,
    PerformBlockActions = 35,
    PerformItemStackRequest = 36,
    HandledTeleport = 37,
    Emoting = 38,
    MissedSwing = 39,
    StartCrawling = 40,
    StopCrawling = 41,
    StartFlying = 42,
    StopFlying = 43,
    ClientAckServerData = 44,
    IsInClientPredictedVehicle = 45,
    PaddlingLeft = 46,
    PaddlingRight = 47,
    BlockBreakingDelayEnabled = 48,
    HorizontalCollision = 49,
    VerticalCollision = 50,
    DownLeft = 51,
    DownRight = 52,
    StartUsingItem = 53,
    IsCameraRelativeMovementEnabledDeprecated = 54,
    IsRotControlledByMoveDirectionDeprecated = 55,
    StartSpinAttack = 56,
    StopSpinAttack = 57,
    IsHotbarOnlyTouch = 58,
    JumpReleasedRaw = 59,
    JumpPressedRaw = 60,
    JumpCurrentRaw = 61,
    SneakReleasedRaw = 62,
    SneakPressedRaw = 63,
    SneakCurrentRaw = 64,
    InputNum = 65,
};

}  // namespace PlayerAuthInputPacket_nested

struct PlayerAuthInputPacket {
    using InputData = PlayerAuthInputPacket_nested::InputData;

    static constexpr int Id = 144;
    Vec2 rot{};
    Vec3 pos{};
    Vec2 move{};
    float y_head_rot{};
    std::bitset<65> input_data{};
    InputMode input_mode{};
    ClientPlayMode play_mode{};
    NewInteractionModel new_interaction_model{};
    Vec2 interact_rotation{};
    PlayerInputTick client_tick{};
    Vec3 pos_delta{};
    v844::PackedItemUseLegacyInventoryTransaction item_use_transaction{};
    base::ItemStackRequestData item_stack_request{};
    std::vector<v748::PlayerBlockActionData> player_block_actions{};
    Vec2 vehicle_rot{};
    ActorUniqueID client_predicted_vehicle{};
    Vec2 analog_move_vector{};
    Vec3 camera_orientation{};
    Vec2 raw_move_vector{};
};

using PlayerActionPacket = v748::PlayerActionPacket;

using UpdateClientInputLocksPacket = base::UpdateClientInputLocksPacket;

}  // namespace v844

namespace v859 {

using PlayerActionType = v748::PlayerActionType;

using PlayerBlockActionData = v748::PlayerBlockActionData;

using PackedItemUseLegacyInventoryTransaction = v844::PackedItemUseLegacyInventoryTransaction;

using PlayerAuthInputPacket = v844::PlayerAuthInputPacket;

using PlayerActionPacket = v748::PlayerActionPacket;

using UpdateClientInputLocksPacket = base::UpdateClientInputLocksPacket;

}  // namespace v859

namespace v898 {

using PlayerActionType = v748::PlayerActionType;

using PlayerBlockActionData = v748::PlayerBlockActionData;

using PackedItemUseLegacyInventoryTransaction = v844::PackedItemUseLegacyInventoryTransaction;

using PlayerAuthInputPacket = v844::PlayerAuthInputPacket;

using PlayerActionPacket = v748::PlayerActionPacket;

using UpdateClientInputLocksPacket = base::UpdateClientInputLocksPacket;

}  // namespace v898

namespace v924 {

using PlayerActionType = v748::PlayerActionType;

using PlayerBlockActionData = v748::PlayerBlockActionData;

struct PackedItemUseLegacyInventoryTransaction {
    std::int32_t id{};
    std::vector<v924::LegacySetSlot> slots{};
    legacy::v844::ItemUseInventoryTransaction transaction{};
};

namespace PlayerAuthInputPacket_nested {

enum class InputData : std::uint32_t {
    Ascend = 0,
    Descend = 1,
    NorthJumpDeprecated = 2,
    JumpDown = 3,
    SprintDown = 4,
    ChangeHeight = 5,
    Jumping = 6,
    AutoJumpingInWater = 7,
    Sneaking = 8,
    SneakDown = 9,
    Up = 10,
    Down = 11,
    Left = 12,
    Right = 13,
    UpLeft = 14,
    UpRight = 15,
    WantUp = 16,
    WantDown = 17,
    WantDownSlow = 18,
    WantUpSlow = 19,
    Sprinting = 20,
    AscendBlock = 21,
    DescendBlock = 22,
    SneakToggleDown = 23,
    PersistSneak = 24,
    StartSprinting = 25,
    StopSprinting = 26,
    StartSneaking = 27,
    StopSneaking = 28,
    StartSwimming = 29,
    StopSwimming = 30,
    StartJumping = 31,
    StartGliding = 32,
    StopGliding = 33,
    PerformItemInteraction = 34,
    PerformBlockActions = 35,
    PerformItemStackRequest = 36,
    HandledTeleport = 37,
    Emoting = 38,
    MissedSwing = 39,
    StartCrawling = 40,
    StopCrawling = 41,
    StartFlying = 42,
    StopFlying = 43,
    ClientAckServerData = 44,
    IsInClientPredictedVehicle = 45,
    PaddlingLeft = 46,
    PaddlingRight = 47,
    BlockBreakingDelayEnabled = 48,
    HorizontalCollision = 49,
    VerticalCollision = 50,
    DownLeft = 51,
    DownRight = 52,
    StartUsingItem = 53,
    IsCameraRelativeMovementEnabledDeprecated = 54,
    IsRotControlledByMoveDirectionDeprecated = 55,
    StartSpinAttack = 56,
    StopSpinAttack = 57,
    IsHotbarOnlyTouch = 58,
    JumpReleasedRaw = 59,
    JumpPressedRaw = 60,
    JumpCurrentRaw = 61,
    SneakReleasedRaw = 62,
    SneakPressedRaw = 63,
    SneakCurrentRaw = 64,
    InputNum = 65,
};

}  // namespace PlayerAuthInputPacket_nested

struct PlayerAuthInputPacket {
    using InputData = PlayerAuthInputPacket_nested::InputData;

    static constexpr int Id = 144;
    Vec2 rot{};
    Vec3 pos{};
    Vec2 move{};
    float y_head_rot{};
    std::bitset<65> input_data{};
    InputMode input_mode{};
    ClientPlayMode play_mode{};
    NewInteractionModel new_interaction_model{};
    Vec2 interact_rotation{};
    PlayerInputTick client_tick{};
    Vec3 pos_delta{};
    v924::PackedItemUseLegacyInventoryTransaction item_use_transaction{};
    v924::ItemStackRequestData item_stack_request{};
    std::vector<v748::PlayerBlockActionData> player_block_actions{};
    Vec2 vehicle_rot{};
    ActorUniqueID client_predicted_vehicle{};
    Vec2 analog_move_vector{};
    Vec3 camera_orientation{};
    Vec2 raw_move_vector{};
};

using PlayerActionPacket = v748::PlayerActionPacket;

using UpdateClientInputLocksPacket = base::UpdateClientInputLocksPacket;

}  // namespace v924

namespace v944 {

using PlayerActionType = v748::PlayerActionType;

using PlayerBlockActionData = v748::PlayerBlockActionData;

struct PackedItemUseLegacyInventoryTransaction {
    std::int32_t id{};
    std::vector<v924::LegacySetSlot> slots{};
    legacy::v944::ItemUseInventoryTransaction transaction{};
};

namespace PlayerAuthInputPacket_nested {

enum class InputData : std::uint32_t {
    Ascend = 0,
    Descend = 1,
    NorthJumpDeprecated = 2,
    JumpDown = 3,
    SprintDown = 4,
    ChangeHeight = 5,
    Jumping = 6,
    AutoJumpingInWater = 7,
    Sneaking = 8,
    SneakDown = 9,
    Up = 10,
    Down = 11,
    Left = 12,
    Right = 13,
    UpLeft = 14,
    UpRight = 15,
    WantUp = 16,
    WantDown = 17,
    WantDownSlow = 18,
    WantUpSlow = 19,
    Sprinting = 20,
    AscendBlock = 21,
    DescendBlock = 22,
    SneakToggleDown = 23,
    PersistSneak = 24,
    StartSprinting = 25,
    StopSprinting = 26,
    StartSneaking = 27,
    StopSneaking = 28,
    StartSwimming = 29,
    StopSwimming = 30,
    StartJumping = 31,
    StartGliding = 32,
    StopGliding = 33,
    PerformItemInteraction = 34,
    PerformBlockActions = 35,
    PerformItemStackRequest = 36,
    HandledTeleport = 37,
    Emoting = 38,
    MissedSwing = 39,
    StartCrawling = 40,
    StopCrawling = 41,
    StartFlying = 42,
    StopFlying = 43,
    ClientAckServerData = 44,
    IsInClientPredictedVehicle = 45,
    PaddlingLeft = 46,
    PaddlingRight = 47,
    BlockBreakingDelayEnabled = 48,
    HorizontalCollision = 49,
    VerticalCollision = 50,
    DownLeft = 51,
    DownRight = 52,
    StartUsingItem = 53,
    IsCameraRelativeMovementEnabledDeprecated = 54,
    IsRotControlledByMoveDirectionDeprecated = 55,
    StartSpinAttack = 56,
    StopSpinAttack = 57,
    IsHotbarOnlyTouch = 58,
    JumpReleasedRaw = 59,
    JumpPressedRaw = 60,
    JumpCurrentRaw = 61,
    SneakReleasedRaw = 62,
    SneakPressedRaw = 63,
    SneakCurrentRaw = 64,
    InputNum = 65,
};

}  // namespace PlayerAuthInputPacket_nested

struct PlayerAuthInputPacket {
    using InputData = PlayerAuthInputPacket_nested::InputData;

    static constexpr int Id = 144;
    Vec2 rot{};
    Vec3 pos{};
    Vec2 move{};
    float y_head_rot{};
    std::bitset<65> input_data{};
    InputMode input_mode{};
    ClientPlayMode play_mode{};
    NewInteractionModel new_interaction_model{};
    Vec2 interact_rotation{};
    PlayerInputTick client_tick{};
    Vec3 pos_delta{};
    v944::PackedItemUseLegacyInventoryTransaction item_use_transaction{};
    v924::ItemStackRequestData item_stack_request{};
    std::vector<v748::PlayerBlockActionData> player_block_actions{};
    Vec2 vehicle_rot{};
    ActorUniqueID client_predicted_vehicle{};
    Vec2 analog_move_vector{};
    Vec3 camera_orientation{};
    Vec2 raw_move_vector{};
};

struct PlayerActionPacket {
    static constexpr int Id = 36;
    ActorRuntimeID runtime_id{};
    v748::PlayerActionType action{};
    BlockPos pos{};
    BlockPos result_pos{};
    std::int32_t face{};
};

struct UpdateClientInputLocksPacket {
    static constexpr int Id = 196;
    std::uint32_t input_lock_component_data{};
};

}  // namespace v944

namespace v975 {

using PlayerActionType = v748::PlayerActionType;

using PlayerBlockActionData = v748::PlayerBlockActionData;

using PackedItemUseLegacyInventoryTransaction = v944::PackedItemUseLegacyInventoryTransaction;

namespace PlayerAuthInputPacket_nested {

enum class InputData : std::uint32_t {
    Ascend = 0,
    Descend = 1,
    NorthJumpDeprecated = 2,
    JumpDown = 3,
    SprintDown = 4,
    ChangeHeight = 5,
    Jumping = 6,
    AutoJumpingInWater = 7,
    Sneaking = 8,
    SneakDown = 9,
    Up = 10,
    Down = 11,
    Left = 12,
    Right = 13,
    UpLeft = 14,
    UpRight = 15,
    WantUp = 16,
    WantDown = 17,
    WantDownSlow = 18,
    WantUpSlow = 19,
    Sprinting = 20,
    AscendBlock = 21,
    DescendBlock = 22,
    SneakToggleDown = 23,
    PersistSneak = 24,
    StartSprinting = 25,
    StopSprinting = 26,
    StartSneaking = 27,
    StopSneaking = 28,
    StartSwimming = 29,
    StopSwimming = 30,
    StartJumping = 31,
    StartGliding = 32,
    StopGliding = 33,
    PerformItemInteraction = 34,
    PerformBlockActions = 35,
    PerformItemStackRequest = 36,
    HandledTeleport = 37,
    Emoting = 38,
    MissedSwing = 39,
    StartCrawling = 40,
    StopCrawling = 41,
    StartFlying = 42,
    StopFlying = 43,
    ClientAckServerData = 44,
    IsInClientPredictedVehicle = 45,
    PaddlingLeft = 46,
    PaddlingRight = 47,
    BlockBreakingDelayEnabled = 48,
    HorizontalCollision = 49,
    VerticalCollision = 50,
    DownLeft = 51,
    DownRight = 52,
    StartUsingItem = 53,
    IsCameraRelativeMovementEnabledDeprecated = 54,
    IsRotControlledByMoveDirectionDeprecated = 55,
    StartSpinAttack = 56,
    StopSpinAttack = 57,
    IsHotbarOnlyTouch = 58,
    JumpReleasedRaw = 59,
    JumpPressedRaw = 60,
    JumpCurrentRaw = 61,
    SneakReleasedRaw = 62,
    SneakPressedRaw = 63,
    SneakCurrentRaw = 64,
    InputNum = 65,
};

}  // namespace PlayerAuthInputPacket_nested

struct PlayerAuthInputPacket {
    using InputData = PlayerAuthInputPacket_nested::InputData;

    static constexpr int Id = 144;
    Vec2 rot{};
    Vec3 pos{};
    Vec2 move{};
    float y_head_rot{};
    std::bitset<65> input_data{};
    InputMode input_mode{};
    ClientPlayMode play_mode{};
    NewInteractionModel new_interaction_model{};
    Vec2 interact_rotation{};
    PlayerInputTick client_tick{};
    Vec3 pos_delta{};
    v944::PackedItemUseLegacyInventoryTransaction item_use_transaction{};
    v975::ItemStackRequestData item_stack_request{};
    std::vector<v748::PlayerBlockActionData> player_block_actions{};
    Vec2 vehicle_rot{};
    ActorUniqueID client_predicted_vehicle{};
    Vec2 analog_move_vector{};
    Vec3 camera_orientation{};
    Vec2 raw_move_vector{};
};

using PlayerActionPacket = v944::PlayerActionPacket;

using UpdateClientInputLocksPacket = v944::UpdateClientInputLocksPacket;

}  // namespace v975

namespace v1001 {

using PlayerActionType = v748::PlayerActionType;

using PlayerBlockActionData = v748::PlayerBlockActionData;

struct PackedItemUseLegacyInventoryTransaction {
    std::int32_t id{};
    std::vector<v924::LegacySetSlot> slots{};
    legacy::v1001::ItemUseInventoryTransaction transaction{};
};

namespace PlayerAuthInputPacket_nested {

enum class InputData : std::uint32_t {
    Ascend = 0,
    Descend = 1,
    NorthJumpDeprecated = 2,
    JumpDown = 3,
    SprintDown = 4,
    ChangeHeight = 5,
    Jumping = 6,
    AutoJumpingInWater = 7,
    Sneaking = 8,
    SneakDown = 9,
    Up = 10,
    Down = 11,
    Left = 12,
    Right = 13,
    UpLeft = 14,
    UpRight = 15,
    WantUp = 16,
    WantDown = 17,
    WantDownSlow = 18,
    WantUpSlow = 19,
    Sprinting = 20,
    AscendBlock = 21,
    DescendBlock = 22,
    SneakToggleDown = 23,
    PersistSneak = 24,
    StartSprinting = 25,
    StopSprinting = 26,
    StartSneaking = 27,
    StopSneaking = 28,
    StartSwimming = 29,
    StopSwimming = 30,
    StartJumping = 31,
    StartGliding = 32,
    StopGliding = 33,
    PerformItemInteraction = 34,
    PerformBlockActions = 35,
    PerformItemStackRequest = 36,
    HandledTeleport = 37,
    Emoting = 38,
    MissedSwing = 39,
    StartCrawling = 40,
    StopCrawling = 41,
    StartFlying = 42,
    StopFlying = 43,
    ClientAckServerData = 44,
    IsInClientPredictedVehicle = 45,
    PaddlingLeft = 46,
    PaddlingRight = 47,
    BlockBreakingDelayEnabled = 48,
    HorizontalCollision = 49,
    VerticalCollision = 50,
    DownLeft = 51,
    DownRight = 52,
    StartUsingItem = 53,
    IsCameraRelativeMovementEnabledDeprecated = 54,
    IsRotControlledByMoveDirectionDeprecated = 55,
    StartSpinAttack = 56,
    StopSpinAttack = 57,
    IsHotbarOnlyTouch = 58,
    JumpReleasedRaw = 59,
    JumpPressedRaw = 60,
    JumpCurrentRaw = 61,
    SneakReleasedRaw = 62,
    SneakPressedRaw = 63,
    SneakCurrentRaw = 64,
    InputNum = 65,
};

}  // namespace PlayerAuthInputPacket_nested

struct PlayerAuthInputPacket {
    using InputData = PlayerAuthInputPacket_nested::InputData;

    static constexpr int Id = 144;
    Vec2 rot{};
    Vec3 pos{};
    Vec2 move{};
    float y_head_rot{};
    std::bitset<65> input_data{};
    InputMode input_mode{};
    ClientPlayMode play_mode{};
    NewInteractionModel new_interaction_model{};
    Vec2 interact_rotation{};
    PlayerInputTick client_tick{};
    Vec3 pos_delta{};
    v1001::PackedItemUseLegacyInventoryTransaction item_use_transaction{};
    v975::ItemStackRequestData item_stack_request{};
    std::vector<v748::PlayerBlockActionData> player_block_actions{};
    Vec2 vehicle_rot{};
    ActorUniqueID client_predicted_vehicle{};
    Vec2 analog_move_vector{};
    Vec3 camera_orientation{};
    Vec2 raw_move_vector{};
};

using PlayerActionPacket = v944::PlayerActionPacket;

using UpdateClientInputLocksPacket = v944::UpdateClientInputLocksPacket;

}  // namespace v1001

namespace v2168 {

enum class PlayerActionType : int {
    Unknown = -1,
    StartDestroyBlock = 0,
    AbortDestroyBlock = 1,
    StopDestroyBlock = 2,
    GetUpdatedBlock = 3,
    DropItem = 4,
    StartSleeping = 5,
    StopSleeping = 6,
    Respawn = 7,
    StartJump = 8,
    StartSprinting = 9,
    StopSprinting = 10,
    StartSneaking = 11,
    StopSneaking = 12,
    CreativeDestroyBlock = 13,
    ChangeDimensionAck = 14,
    StartGliding = 15,
    StopGliding = 16,
    DenyDestroyBlock = 17,
    CrackBlock = 18,
    ChangeSkin = 19,
    DeprecatedUpdatedEnchantingSeed = 20,
    StartSwimming = 21,
    StopSwimming = 22,
    StartSpinAttack = 23,
    StopSpinAttack = 24,
    InteractWithBlock = 25,
    PredictDestroyBlock = 26,
    ContinueDestroyBlock = 27,
    StartItemUseOn = 28,
    StopItemUseOn = 29,
    HandledTeleport = 30,
    MissedSwing = 31,
    StartCrawling = 32,
    StopCrawling = 33,
    StartFlying = 34,
    StopFlying = 35,
    DeprecatedClientAckServerData = 36,
    StartUsingItem = 37,
    InternalUpdate = 38,
    Count = 39,
};

struct PlayerBlockActionData {
    v2168::PlayerActionType player_action_type{};
    BlockPos pos{};
    std::int32_t facing{};
};

struct PackedItemUseLegacyInventoryTransaction {
    ItemStackLegacyRequestId id{};
    std::optional<std::vector<v924::LegacySetSlot>> slots{};
    v2168::ItemUseInventoryTransaction transaction{};
};

namespace PlayerAuthInputPacket_nested {

enum class InputData : int {
    Ascend = 0,
    Descend = 1,
    NorthJumpDeprecated = 2,
    JumpDown = 3,
    SprintDown = 4,
    ChangeHeight = 5,
    Jumping = 6,
    AutoJumpingInWater = 7,
    Sneaking = 8,
    SneakDown = 9,
    Up = 10,
    Down = 11,
    Left = 12,
    Right = 13,
    UpLeft = 14,
    UpRight = 15,
    WantUp = 16,
    WantDown = 17,
    WantDownSlow = 18,
    WantUpSlow = 19,
    Sprinting = 20,
    AscendBlock = 21,
    DescendBlock = 22,
    SneakToggleDown = 23,
    PersistSneak = 24,
    StartSprinting = 25,
    StopSprinting = 26,
    StartSneaking = 27,
    StopSneaking = 28,
    StartSwimming = 29,
    StopSwimming = 30,
    StartJumping = 31,
    StartGliding = 32,
    StopGliding = 33,
    PerformItemInteraction = 34,
    PerformBlockActions = 35,
    PerformItemStackRequest = 36,
    HandledTeleport = 37,
    Emoting = 38,
    MissedSwing = 39,
    StartCrawling = 40,
    StopCrawling = 41,
    StartFlying = 42,
    StopFlying = 43,
    ClientAckServerData = 44,
    IsInClientPredictedVehicle = 45,
    PaddlingLeft = 46,
    PaddlingRight = 47,
    BlockBreakingDelayEnabled = 48,
    HorizontalCollision = 49,
    VerticalCollision = 50,
    DownLeft = 51,
    DownRight = 52,
    StartUsingItem = 53,
    IsCameraRelativeMovementEnabledDeprecated = 54,
    IsRotControlledByMoveDirectionDeprecated = 55,
    StartSpinAttack = 56,
    StopSpinAttack = 57,
    IsHotbarOnlyTouch = 58,
    JumpReleasedRaw = 59,
    JumpPressedRaw = 60,
    JumpCurrentRaw = 61,
    SneakReleasedRaw = 62,
    SneakPressedRaw = 63,
    SneakCurrentRaw = 64,
    InternalUpdate = 65,
    InputNum = 66,
};

}  // namespace PlayerAuthInputPacket_nested

struct PlayerAuthInputPacket {
    using InputData = PlayerAuthInputPacket_nested::InputData;

    static constexpr int Id = 144;
    Vec2 rot{};
    Vec3 pos{};
    Vec2 move{};
    float y_head_rot{};
    std::vector<v2168::PlayerAuthInputPacket::InputData> input_data{};
    InputMode input_mode{};
    ClientPlayMode play_mode{};
    NewInteractionModel new_interaction_model{};
    Vec2 interact_rotation{};
    PlayerInputTick client_tick{};
    Vec3 pos_delta{};
    std::optional<v2168::PackedItemUseLegacyInventoryTransaction> item_use_transaction{};
    std::optional<v2168::ItemStackRequestCereal::RequestData> item_stack_request{};
    std::optional<std::vector<v2168::PlayerBlockActionData>> player_block_actions{};
    std::optional<Vec2> vehicle_rot{};
    std::optional<ActorUniqueID> client_predicted_vehicle{};
    Vec2 analog_move_vector{};
    Vec3 camera_orientation{};
    Vec2 raw_move_vector{};
};

struct PlayerActionPacket {
    static constexpr int Id = 36;
    ActorRuntimeID runtime_id{};
    v2168::PlayerActionType action{};
    BlockPos pos{};
    BlockPos result_pos{};
    std::int32_t face{};
};

using UpdateClientInputLocksPacket = v944::UpdateClientInputLocksPacket;

}  // namespace v2168

namespace v2193 {

using PlayerActionType = v2168::PlayerActionType;

using PlayerBlockActionData = v2168::PlayerBlockActionData;

struct PackedItemUseLegacyInventoryTransaction {
    ItemStackLegacyRequestId id{};
    std::optional<std::vector<v924::LegacySetSlot>> slots{};
    v2193::ItemUseInventoryTransaction transaction{};
};

namespace PlayerAuthInputPacket_nested {

enum class InputData : int {
    Ascend = 0,
    Descend = 1,
    NorthJumpDeprecated = 2,
    JumpDown = 3,
    SprintDown = 4,
    ChangeHeight = 5,
    Jumping = 6,
    AutoJumpingInWater = 7,
    Sneaking = 8,
    SneakDown = 9,
    Up = 10,
    Down = 11,
    Left = 12,
    Right = 13,
    UpLeft = 14,
    UpRight = 15,
    WantUp = 16,
    WantDown = 17,
    WantDownSlow = 18,
    WantUpSlow = 19,
    Sprinting = 20,
    AscendBlock = 21,
    DescendBlock = 22,
    SneakToggleDown = 23,
    PersistSneak = 24,
    StartSprinting = 25,
    StopSprinting = 26,
    StartSneaking = 27,
    StopSneaking = 28,
    StartSwimming = 29,
    StopSwimming = 30,
    StartJumping = 31,
    StartGliding = 32,
    StopGliding = 33,
    PerformItemInteraction = 34,
    PerformBlockActions = 35,
    PerformItemStackRequest = 36,
    HandledTeleport = 37,
    Emoting = 38,
    MissedSwing = 39,
    StartCrawling = 40,
    StopCrawling = 41,
    StartFlying = 42,
    StopFlying = 43,
    ClientAckServerData = 44,
    IsInClientPredictedVehicle = 45,
    PaddlingLeft = 46,
    PaddlingRight = 47,
    BlockBreakingDelayEnabled = 48,
    HorizontalCollision = 49,
    VerticalCollision = 50,
    DownLeft = 51,
    DownRight = 52,
    StartUsingItem = 53,
    IsCameraRelativeMovementEnabledDeprecated = 54,
    IsRotControlledByMoveDirectionDeprecated = 55,
    StartSpinAttack = 56,
    StopSpinAttack = 57,
    IsHotbarOnlyTouch = 58,
    JumpReleasedRaw = 59,
    JumpPressedRaw = 60,
    JumpCurrentRaw = 61,
    SneakReleasedRaw = 62,
    SneakPressedRaw = 63,
    SneakCurrentRaw = 64,
    InternalUpdate = 65,
    InputNum = 66,
};

}  // namespace PlayerAuthInputPacket_nested

struct PlayerAuthInputPacket {
    using InputData = PlayerAuthInputPacket_nested::InputData;

    static constexpr int Id = 144;
    Vec2 rot{};
    Vec3 pos{};
    Vec2 move{};
    float y_head_rot{};
    std::vector<v2193::PlayerAuthInputPacket::InputData> input_data{};
    InputMode input_mode{};
    ClientPlayMode play_mode{};
    NewInteractionModel new_interaction_model{};
    Vec2 interact_rotation{};
    PlayerInputTick client_tick{};
    Vec3 pos_delta{};
    std::optional<v2193::PackedItemUseLegacyInventoryTransaction> item_use_transaction{};
    std::optional<v2168::ItemStackRequestCereal::RequestData> item_stack_request{};
    std::optional<std::vector<v2168::PlayerBlockActionData>> player_block_actions{};
    std::optional<Vec2> vehicle_rot{};
    std::optional<ActorUniqueID> client_predicted_vehicle{};
    Vec2 analog_move_vector{};
    Vec3 camera_orientation{};
    Vec2 raw_move_vector{};
};

using PlayerActionPacket = v2168::PlayerActionPacket;

using UpdateClientInputLocksPacket = v944::UpdateClientInputLocksPacket;

}  // namespace v2193

namespace v2225 {

using PlayerActionType = v2168::PlayerActionType;

using PlayerBlockActionData = v2168::PlayerBlockActionData;

struct PackedItemUseLegacyInventoryTransaction {
    ItemStackLegacyRequestId id{};
    std::optional<std::vector<v2225::LegacySetSlot>> slots{};
    v2193::ItemUseInventoryTransaction transaction{};
};

namespace PlayerAuthInputPacket_nested {

enum class InputData : int {
    Ascend = 0,
    Descend = 1,
    NorthJumpDeprecated = 2,
    JumpDown = 3,
    SprintDown = 4,
    ChangeHeight = 5,
    Jumping = 6,
    AutoJumpingInWater = 7,
    Sneaking = 8,
    SneakDown = 9,
    Up = 10,
    Down = 11,
    Left = 12,
    Right = 13,
    UpLeft = 14,
    UpRight = 15,
    WantUp = 16,
    WantDown = 17,
    WantDownSlow = 18,
    WantUpSlow = 19,
    Sprinting = 20,
    AscendBlock = 21,
    DescendBlock = 22,
    SneakToggleDown = 23,
    PersistSneak = 24,
    StartSprinting = 25,
    StopSprinting = 26,
    StartSneaking = 27,
    StopSneaking = 28,
    StartSwimming = 29,
    StopSwimming = 30,
    StartJumping = 31,
    StartGliding = 32,
    StopGliding = 33,
    PerformItemInteraction = 34,
    PerformBlockActions = 35,
    PerformItemStackRequest = 36,
    HandledTeleport = 37,
    Emoting = 38,
    MissedSwing = 39,
    StartCrawling = 40,
    StopCrawling = 41,
    StartFlying = 42,
    StopFlying = 43,
    ClientAckServerData = 44,
    IsInClientPredictedVehicle = 45,
    PaddlingLeft = 46,
    PaddlingRight = 47,
    BlockBreakingDelayEnabled = 48,
    HorizontalCollision = 49,
    VerticalCollision = 50,
    DownLeft = 51,
    DownRight = 52,
    StartUsingItem = 53,
    IsCameraRelativeMovementEnabledDeprecated = 54,
    IsRotControlledByMoveDirectionDeprecated = 55,
    StartSpinAttack = 56,
    StopSpinAttack = 57,
    IsHotbarOnlyTouch = 58,
    JumpReleasedRaw = 59,
    JumpPressedRaw = 60,
    JumpCurrentRaw = 61,
    SneakReleasedRaw = 62,
    SneakPressedRaw = 63,
    SneakCurrentRaw = 64,
    InternalUpdate = 65,
    InputNum = 66,
};

}  // namespace PlayerAuthInputPacket_nested

struct PlayerAuthInputPacket {
    using InputData = PlayerAuthInputPacket_nested::InputData;

    static constexpr int Id = 144;
    Vec2 rot{};
    Vec3 pos{};
    Vec2 move{};
    float y_head_rot{};
    std::vector<v2225::PlayerAuthInputPacket::InputData> input_data{};
    InputMode input_mode{};
    ClientPlayMode play_mode{};
    NewInteractionModel new_interaction_model{};
    Vec2 interact_rotation{};
    PlayerInputTick client_tick{};
    Vec3 pos_delta{};
    std::optional<v2225::PackedItemUseLegacyInventoryTransaction> item_use_transaction{};
    std::optional<v2225::ItemStackRequestCereal::RequestData> item_stack_request{};
    std::optional<std::vector<v2168::PlayerBlockActionData>> player_block_actions{};
    std::optional<Vec2> vehicle_rot{};
    std::optional<ActorUniqueID> client_predicted_vehicle{};
    Vec2 analog_move_vector{};
    Vec3 camera_orientation{};
    Vec2 raw_move_vector{};
};

using PlayerActionPacket = v2168::PlayerActionPacket;

using UpdateClientInputLocksPacket = v944::UpdateClientInputLocksPacket;

}  // namespace v2225

namespace detail {

template <int V>
struct PlayerActionType_;

template <int V> requires (V < 748)
struct PlayerActionType_<V> { using type = base::PlayerActionType; };

template <int V> requires (V >= 748 && V < 2168)
struct PlayerActionType_<V> { using type = v748::PlayerActionType; };

template <int V> requires (V >= 2168)
struct PlayerActionType_<V> { using type = v2168::PlayerActionType; };

template <int V>
struct PlayerBlockActionData_;

template <int V> requires (V < 748)
struct PlayerBlockActionData_<V> { using type = base::PlayerBlockActionData; };

template <int V> requires (V >= 748 && V < 2168)
struct PlayerBlockActionData_<V> { using type = v748::PlayerBlockActionData; };

template <int V> requires (V >= 2168)
struct PlayerBlockActionData_<V> { using type = v2168::PlayerBlockActionData; };

template <int V>
struct PackedItemUseLegacyInventoryTransaction_;

template <int V> requires (V < 748)
struct PackedItemUseLegacyInventoryTransaction_<V> { using type = base::PackedItemUseLegacyInventoryTransaction; };

template <int V> requires (V >= 748 && V < 844)
struct PackedItemUseLegacyInventoryTransaction_<V> { using type = v748::PackedItemUseLegacyInventoryTransaction; };

template <int V> requires (V >= 844 && V < 924)
struct PackedItemUseLegacyInventoryTransaction_<V> { using type = v844::PackedItemUseLegacyInventoryTransaction; };

template <int V> requires (V >= 924 && V < 944)
struct PackedItemUseLegacyInventoryTransaction_<V> { using type = v924::PackedItemUseLegacyInventoryTransaction; };

template <int V> requires (V >= 944 && V < 1001)
struct PackedItemUseLegacyInventoryTransaction_<V> { using type = v944::PackedItemUseLegacyInventoryTransaction; };

template <int V> requires (V >= 1001 && V < 2168)
struct PackedItemUseLegacyInventoryTransaction_<V> { using type = v1001::PackedItemUseLegacyInventoryTransaction; };

template <int V> requires (V >= 2168 && V < 2193)
struct PackedItemUseLegacyInventoryTransaction_<V> { using type = v2168::PackedItemUseLegacyInventoryTransaction; };

template <int V> requires (V >= 2193 && V < 2225)
struct PackedItemUseLegacyInventoryTransaction_<V> { using type = v2193::PackedItemUseLegacyInventoryTransaction; };

template <int V> requires (V >= 2225)
struct PackedItemUseLegacyInventoryTransaction_<V> { using type = v2225::PackedItemUseLegacyInventoryTransaction; };

template <int V>
struct PlayerAuthInputPacket_;

template <int V> requires (V < 748)
struct PlayerAuthInputPacket_<V> { using type = base::PlayerAuthInputPacket; };

template <int V> requires (V >= 748 && V < 766)
struct PlayerAuthInputPacket_<V> { using type = v748::PlayerAuthInputPacket; };

template <int V> requires (V >= 766 && V < 844)
struct PlayerAuthInputPacket_<V> { using type = v766::PlayerAuthInputPacket; };

template <int V> requires (V >= 844 && V < 924)
struct PlayerAuthInputPacket_<V> { using type = v844::PlayerAuthInputPacket; };

template <int V> requires (V >= 924 && V < 944)
struct PlayerAuthInputPacket_<V> { using type = v924::PlayerAuthInputPacket; };

template <int V> requires (V >= 944 && V < 975)
struct PlayerAuthInputPacket_<V> { using type = v944::PlayerAuthInputPacket; };

template <int V> requires (V >= 975 && V < 1001)
struct PlayerAuthInputPacket_<V> { using type = v975::PlayerAuthInputPacket; };

template <int V> requires (V >= 1001 && V < 2168)
struct PlayerAuthInputPacket_<V> { using type = v1001::PlayerAuthInputPacket; };

template <int V> requires (V >= 2168 && V < 2193)
struct PlayerAuthInputPacket_<V> { using type = v2168::PlayerAuthInputPacket; };

template <int V> requires (V >= 2193 && V < 2225)
struct PlayerAuthInputPacket_<V> { using type = v2193::PlayerAuthInputPacket; };

template <int V> requires (V >= 2225)
struct PlayerAuthInputPacket_<V> { using type = v2225::PlayerAuthInputPacket; };

template <int V>
struct PlayerActionPacket_;

template <int V> requires (V < 748)
struct PlayerActionPacket_<V> { using type = base::PlayerActionPacket; };

template <int V> requires (V >= 748 && V < 944)
struct PlayerActionPacket_<V> { using type = v748::PlayerActionPacket; };

template <int V> requires (V >= 944 && V < 2168)
struct PlayerActionPacket_<V> { using type = v944::PlayerActionPacket; };

template <int V> requires (V >= 2168)
struct PlayerActionPacket_<V> { using type = v2168::PlayerActionPacket; };

template <int V>
struct UpdateClientInputLocksPacket_;

template <int V> requires (V < 944)
struct UpdateClientInputLocksPacket_<V> { using type = base::UpdateClientInputLocksPacket; };

template <int V> requires (V >= 944)
struct UpdateClientInputLocksPacket_<V> { using type = v944::UpdateClientInputLocksPacket; };

template <int V>
struct PassengerJumpPacket_;

template <int V> requires (V < 800)
struct PassengerJumpPacket_<V> { using type = base::PassengerJumpPacket; };

template <int V>
struct PlayerInputPacket_;

template <int V> requires (V < 800)
struct PlayerInputPacket_<V> { using type = base::PlayerInputPacket; };

}  // namespace detail

template <int V> using PlayerActionType_ = typename detail::PlayerActionType_<V>::type;
template <int V> using PlayerBlockActionData_ = typename detail::PlayerBlockActionData_<V>::type;
template <int V> using PackedItemUseLegacyInventoryTransaction_ = typename detail::PackedItemUseLegacyInventoryTransaction_<V>::type;
template <int V> using PlayerAuthInputPacket_ = typename detail::PlayerAuthInputPacket_<V>::type;
template <int V> using PlayerActionPacket_ = typename detail::PlayerActionPacket_<V>::type;
template <int V> using UpdateClientInputLocksPacket_ = typename detail::UpdateClientInputLocksPacket_<V>::type;
template <int V> using PassengerJumpPacket_ = typename detail::PassengerJumpPacket_<V>::type;
template <int V> using PlayerInputPacket_ = typename detail::PlayerInputPacket_<V>::type;

template <int V> requires (V < 800)
struct packet_of<V, 20> { using type = PassengerJumpPacket_<V>; };

template <int V>
struct packet_of<V, 36> { using type = PlayerActionPacket_<V>; };

template <int V> requires (V < 800)
struct packet_of<V, 57> { using type = PlayerInputPacket_<V>; };

template <int V>
struct packet_of<V, 144> { using type = PlayerAuthInputPacket_<V>; };

template <int V>
struct packet_of<V, 196> { using type = UpdateClientInputLocksPacket_<V>; };

namespace detail {

template <>
inline constexpr std::array<InputMode, 6> values_v<InputMode>{{
    InputMode::Undefined,
    InputMode::Mouse,
    InputMode::Touch,
    InputMode::GamePad,
    InputMode::MotionControllerDeprecated,
    InputMode::Count,
}};

template <>
inline constexpr std::array<std::string_view, 6> names_v<InputMode>{{
    "undefined",
    "mouse",
    "touch",
    "gamepad",
    "motioncontrollerdeprecated",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<InputMode>{"InputMode"};

template <>
inline constexpr std::array<ClientPlayMode, 10> values_v<ClientPlayMode>{{
    ClientPlayMode::Normal,
    ClientPlayMode::Teaser,
    ClientPlayMode::Screen,
    ClientPlayMode::ViewerDeprecated,
    ClientPlayMode::RealityDeprecated,
    ClientPlayMode::PlacementDeprecated,
    ClientPlayMode::LivingRoomDeprecated,
    ClientPlayMode::ExitLevel,
    ClientPlayMode::ExitLevelLivingRoomDeprecated,
    ClientPlayMode::NumModes,
}};

template <>
inline constexpr std::array<std::string_view, 10> names_v<ClientPlayMode>{{
    "normal",
    "teaser",
    "screen",
    "viewerdeprecated",
    "realitydeprecated",
    "placementdeprecated",
    "livingroomdeprecated",
    "exitlevel",
    "exitlevellivingroomdeprecated",
    "nummodes",
}};

template <>
inline constexpr std::string_view type_name_v<ClientPlayMode>{"ClientPlayMode"};

template <>
inline constexpr std::array<NewInteractionModel, 4> values_v<NewInteractionModel>{{
    NewInteractionModel::Touch,
    NewInteractionModel::Crosshair,
    NewInteractionModel::Classic,
    NewInteractionModel::Count,
}};

template <>
inline constexpr std::array<std::string_view, 4> names_v<NewInteractionModel>{{
    "touch",
    "crosshair",
    "classic",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<NewInteractionModel>{"NewInteractionModel"};

template <>
inline constexpr std::array<base::PlayerActionType, 39> values_v<base::PlayerActionType>{{
    base::PlayerActionType::Unknown,
    base::PlayerActionType::StartDestroyBlock,
    base::PlayerActionType::AbortDestroyBlock,
    base::PlayerActionType::StopDestroyBlock,
    base::PlayerActionType::GetUpdatedBlock,
    base::PlayerActionType::DropItem,
    base::PlayerActionType::StartSleeping,
    base::PlayerActionType::StopSleeping,
    base::PlayerActionType::Respawn,
    base::PlayerActionType::StartJump,
    base::PlayerActionType::StartSprinting,
    base::PlayerActionType::StopSprinting,
    base::PlayerActionType::StartSneaking,
    base::PlayerActionType::StopSneaking,
    base::PlayerActionType::CreativeDestroyBlock,
    base::PlayerActionType::ChangeDimensionAck,
    base::PlayerActionType::StartGliding,
    base::PlayerActionType::StopGliding,
    base::PlayerActionType::DenyDestroyBlock,
    base::PlayerActionType::CrackBlock,
    base::PlayerActionType::ChangeSkin,
    base::PlayerActionType::DeprecatedUpdatedEnchantingSeed,
    base::PlayerActionType::StartSwimming,
    base::PlayerActionType::StopSwimming,
    base::PlayerActionType::StartSpinAttack,
    base::PlayerActionType::StopSpinAttack,
    base::PlayerActionType::InteractWithBlock,
    base::PlayerActionType::PredictDestroyBlock,
    base::PlayerActionType::ContinueDestroyBlock,
    base::PlayerActionType::StartItemUseOn,
    base::PlayerActionType::StopItemUseOn,
    base::PlayerActionType::HandledTeleport,
    base::PlayerActionType::MissedSwing,
    base::PlayerActionType::StartCrawling,
    base::PlayerActionType::StopCrawling,
    base::PlayerActionType::StartFlying,
    base::PlayerActionType::StopFlying,
    base::PlayerActionType::DeprecatedClientAckServerData,
    base::PlayerActionType::Count,
}};

template <>
inline constexpr std::array<std::string_view, 39> names_v<base::PlayerActionType>{{
    "unknown",
    "startdestroyblock",
    "abortdestroyblock",
    "stopdestroyblock",
    "getupdatedblock",
    "dropitem",
    "startsleeping",
    "stopsleeping",
    "respawn",
    "startjump",
    "startsprinting",
    "stopsprinting",
    "startsneaking",
    "stopsneaking",
    "creativedestroyblock",
    "changedimensionack",
    "startgliding",
    "stopgliding",
    "denydestroyblock",
    "crackblock",
    "changeskin",
    "deprecatedupdatedenchantingseed",
    "startswimming",
    "stopswimming",
    "startspinattack",
    "stopspinattack",
    "interactwithblock",
    "predictdestroyblock",
    "continuedestroyblock",
    "startitemuseon",
    "stopitemuseon",
    "handledteleport",
    "missedswing",
    "startcrawling",
    "stopcrawling",
    "startflying",
    "stopflying",
    "deprecatedclientackserverdata",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<base::PlayerActionType>{"PlayerActionType"};

template <>
inline constexpr std::array<v748::PlayerActionType, 40> values_v<v748::PlayerActionType>{{
    v748::PlayerActionType::Unknown,
    v748::PlayerActionType::StartDestroyBlock,
    v748::PlayerActionType::AbortDestroyBlock,
    v748::PlayerActionType::StopDestroyBlock,
    v748::PlayerActionType::GetUpdatedBlock,
    v748::PlayerActionType::DropItem,
    v748::PlayerActionType::StartSleeping,
    v748::PlayerActionType::StopSleeping,
    v748::PlayerActionType::Respawn,
    v748::PlayerActionType::StartJump,
    v748::PlayerActionType::StartSprinting,
    v748::PlayerActionType::StopSprinting,
    v748::PlayerActionType::StartSneaking,
    v748::PlayerActionType::StopSneaking,
    v748::PlayerActionType::CreativeDestroyBlock,
    v748::PlayerActionType::ChangeDimensionAck,
    v748::PlayerActionType::StartGliding,
    v748::PlayerActionType::StopGliding,
    v748::PlayerActionType::DenyDestroyBlock,
    v748::PlayerActionType::CrackBlock,
    v748::PlayerActionType::ChangeSkin,
    v748::PlayerActionType::DeprecatedUpdatedEnchantingSeed,
    v748::PlayerActionType::StartSwimming,
    v748::PlayerActionType::StopSwimming,
    v748::PlayerActionType::StartSpinAttack,
    v748::PlayerActionType::StopSpinAttack,
    v748::PlayerActionType::InteractWithBlock,
    v748::PlayerActionType::PredictDestroyBlock,
    v748::PlayerActionType::ContinueDestroyBlock,
    v748::PlayerActionType::StartItemUseOn,
    v748::PlayerActionType::StopItemUseOn,
    v748::PlayerActionType::HandledTeleport,
    v748::PlayerActionType::MissedSwing,
    v748::PlayerActionType::StartCrawling,
    v748::PlayerActionType::StopCrawling,
    v748::PlayerActionType::StartFlying,
    v748::PlayerActionType::StopFlying,
    v748::PlayerActionType::DeprecatedClientAckServerData,
    v748::PlayerActionType::StartUsingItem,
    v748::PlayerActionType::Count,
}};

template <>
inline constexpr std::array<std::string_view, 40> names_v<v748::PlayerActionType>{{
    "unknown",
    "startdestroyblock",
    "abortdestroyblock",
    "stopdestroyblock",
    "getupdatedblock",
    "dropitem",
    "startsleeping",
    "stopsleeping",
    "respawn",
    "startjump",
    "startsprinting",
    "stopsprinting",
    "startsneaking",
    "stopsneaking",
    "creativedestroyblock",
    "changedimensionack",
    "startgliding",
    "stopgliding",
    "denydestroyblock",
    "crackblock",
    "changeskin",
    "deprecatedupdatedenchantingseed",
    "startswimming",
    "stopswimming",
    "startspinattack",
    "stopspinattack",
    "interactwithblock",
    "predictdestroyblock",
    "continuedestroyblock",
    "startitemuseon",
    "stopitemuseon",
    "handledteleport",
    "missedswing",
    "startcrawling",
    "stopcrawling",
    "startflying",
    "stopflying",
    "deprecatedclientackserverdata",
    "startusingitem",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<v748::PlayerActionType>{"PlayerActionType"};

template <>
inline constexpr std::array<v2168::PlayerActionType, 41> values_v<v2168::PlayerActionType>{{
    v2168::PlayerActionType::Unknown,
    v2168::PlayerActionType::StartDestroyBlock,
    v2168::PlayerActionType::AbortDestroyBlock,
    v2168::PlayerActionType::StopDestroyBlock,
    v2168::PlayerActionType::GetUpdatedBlock,
    v2168::PlayerActionType::DropItem,
    v2168::PlayerActionType::StartSleeping,
    v2168::PlayerActionType::StopSleeping,
    v2168::PlayerActionType::Respawn,
    v2168::PlayerActionType::StartJump,
    v2168::PlayerActionType::StartSprinting,
    v2168::PlayerActionType::StopSprinting,
    v2168::PlayerActionType::StartSneaking,
    v2168::PlayerActionType::StopSneaking,
    v2168::PlayerActionType::CreativeDestroyBlock,
    v2168::PlayerActionType::ChangeDimensionAck,
    v2168::PlayerActionType::StartGliding,
    v2168::PlayerActionType::StopGliding,
    v2168::PlayerActionType::DenyDestroyBlock,
    v2168::PlayerActionType::CrackBlock,
    v2168::PlayerActionType::ChangeSkin,
    v2168::PlayerActionType::DeprecatedUpdatedEnchantingSeed,
    v2168::PlayerActionType::StartSwimming,
    v2168::PlayerActionType::StopSwimming,
    v2168::PlayerActionType::StartSpinAttack,
    v2168::PlayerActionType::StopSpinAttack,
    v2168::PlayerActionType::InteractWithBlock,
    v2168::PlayerActionType::PredictDestroyBlock,
    v2168::PlayerActionType::ContinueDestroyBlock,
    v2168::PlayerActionType::StartItemUseOn,
    v2168::PlayerActionType::StopItemUseOn,
    v2168::PlayerActionType::HandledTeleport,
    v2168::PlayerActionType::MissedSwing,
    v2168::PlayerActionType::StartCrawling,
    v2168::PlayerActionType::StopCrawling,
    v2168::PlayerActionType::StartFlying,
    v2168::PlayerActionType::StopFlying,
    v2168::PlayerActionType::DeprecatedClientAckServerData,
    v2168::PlayerActionType::StartUsingItem,
    v2168::PlayerActionType::InternalUpdate,
    v2168::PlayerActionType::Count,
}};

template <>
inline constexpr std::array<std::string_view, 41> names_v<v2168::PlayerActionType>{{
    "unknown",
    "startdestroyblock",
    "abortdestroyblock",
    "stopdestroyblock",
    "getupdatedblock",
    "dropitem",
    "startsleeping",
    "stopsleeping",
    "respawn",
    "startjump",
    "startsprinting",
    "stopsprinting",
    "startsneaking",
    "stopsneaking",
    "creativedestroyblock",
    "changedimensionack",
    "startgliding",
    "stopgliding",
    "denydestroyblock",
    "crackblock",
    "changeskin",
    "deprecatedupdatedenchantingseed",
    "startswimming",
    "stopswimming",
    "startspinattack",
    "stopspinattack",
    "interactwithblock",
    "predictdestroyblock",
    "continuedestroyblock",
    "startitemuseon",
    "stopitemuseon",
    "handledteleport",
    "missedswing",
    "startcrawling",
    "stopcrawling",
    "startflying",
    "stopflying",
    "deprecatedclientackserverdata",
    "startusingitem",
    "internalupdate",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<v2168::PlayerActionType>{"PlayerActionType"};

template <>
inline constexpr std::array<base::PlayerAuthInputPacket::InputData, 54> values_v<base::PlayerAuthInputPacket::InputData>{{
    base::PlayerAuthInputPacket::InputData::Ascend,
    base::PlayerAuthInputPacket::InputData::Descend,
    base::PlayerAuthInputPacket::InputData::NorthJumpDeprecated,
    base::PlayerAuthInputPacket::InputData::JumpDown,
    base::PlayerAuthInputPacket::InputData::SprintDown,
    base::PlayerAuthInputPacket::InputData::ChangeHeight,
    base::PlayerAuthInputPacket::InputData::Jumping,
    base::PlayerAuthInputPacket::InputData::AutoJumpingInWater,
    base::PlayerAuthInputPacket::InputData::Sneaking,
    base::PlayerAuthInputPacket::InputData::SneakDown,
    base::PlayerAuthInputPacket::InputData::Up,
    base::PlayerAuthInputPacket::InputData::Down,
    base::PlayerAuthInputPacket::InputData::Left,
    base::PlayerAuthInputPacket::InputData::Right,
    base::PlayerAuthInputPacket::InputData::UpLeft,
    base::PlayerAuthInputPacket::InputData::UpRight,
    base::PlayerAuthInputPacket::InputData::WantUp,
    base::PlayerAuthInputPacket::InputData::WantDown,
    base::PlayerAuthInputPacket::InputData::WantDownSlow,
    base::PlayerAuthInputPacket::InputData::WantUpSlow,
    base::PlayerAuthInputPacket::InputData::Sprinting,
    base::PlayerAuthInputPacket::InputData::AscendBlock,
    base::PlayerAuthInputPacket::InputData::DescendBlock,
    base::PlayerAuthInputPacket::InputData::SneakToggleDown,
    base::PlayerAuthInputPacket::InputData::PersistSneak,
    base::PlayerAuthInputPacket::InputData::StartSprinting,
    base::PlayerAuthInputPacket::InputData::StopSprinting,
    base::PlayerAuthInputPacket::InputData::StartSneaking,
    base::PlayerAuthInputPacket::InputData::StopSneaking,
    base::PlayerAuthInputPacket::InputData::StartSwimming,
    base::PlayerAuthInputPacket::InputData::StopSwimming,
    base::PlayerAuthInputPacket::InputData::StartJumping,
    base::PlayerAuthInputPacket::InputData::StartGliding,
    base::PlayerAuthInputPacket::InputData::StopGliding,
    base::PlayerAuthInputPacket::InputData::PerformItemInteraction,
    base::PlayerAuthInputPacket::InputData::PerformBlockActions,
    base::PlayerAuthInputPacket::InputData::PerformItemStackRequest,
    base::PlayerAuthInputPacket::InputData::HandledTeleport,
    base::PlayerAuthInputPacket::InputData::Emoting,
    base::PlayerAuthInputPacket::InputData::MissedSwing,
    base::PlayerAuthInputPacket::InputData::StartCrawling,
    base::PlayerAuthInputPacket::InputData::StopCrawling,
    base::PlayerAuthInputPacket::InputData::StartFlying,
    base::PlayerAuthInputPacket::InputData::StopFlying,
    base::PlayerAuthInputPacket::InputData::ClientAckServerData,
    base::PlayerAuthInputPacket::InputData::IsInClientPredictedVehicle,
    base::PlayerAuthInputPacket::InputData::PaddlingLeft,
    base::PlayerAuthInputPacket::InputData::PaddlingRight,
    base::PlayerAuthInputPacket::InputData::BlockBreakingDelayEnabled,
    base::PlayerAuthInputPacket::InputData::HorizontalCollision,
    base::PlayerAuthInputPacket::InputData::VerticalCollision,
    base::PlayerAuthInputPacket::InputData::DownLeft,
    base::PlayerAuthInputPacket::InputData::DownRight,
    base::PlayerAuthInputPacket::InputData::InputNum,
}};

template <>
inline constexpr std::array<std::string_view, 54> names_v<base::PlayerAuthInputPacket::InputData>{{
    "ascend",
    "descend",
    "northjumpdeprecated",
    "jumpdown",
    "sprintdown",
    "changeheight",
    "jumping",
    "autojumpinginwater",
    "sneaking",
    "sneakdown",
    "up",
    "down",
    "left",
    "right",
    "upleft",
    "upright",
    "wantup",
    "wantdown",
    "wantdownslow",
    "wantupslow",
    "sprinting",
    "ascendblock",
    "descendblock",
    "sneaktoggledown",
    "persistsneak",
    "startsprinting",
    "stopsprinting",
    "startsneaking",
    "stopsneaking",
    "startswimming",
    "stopswimming",
    "startjumping",
    "startgliding",
    "stopgliding",
    "performiteminteraction",
    "performblockactions",
    "performitemstackrequest",
    "handledteleport",
    "emoting",
    "missedswing",
    "startcrawling",
    "stopcrawling",
    "startflying",
    "stopflying",
    "clientackserverdata",
    "isinclientpredictedvehicle",
    "paddlingleft",
    "paddlingright",
    "blockbreakingdelayenabled",
    "horizontalcollision",
    "verticalcollision",
    "downleft",
    "downright",
    "inputnum",
}};

template <>
inline constexpr std::string_view type_name_v<base::PlayerAuthInputPacket::InputData>{"PlayerAuthInputPacket::InputData"};

template <>
inline constexpr std::array<v748::PlayerAuthInputPacket::InputData, 59> values_v<v748::PlayerAuthInputPacket::InputData>{{
    v748::PlayerAuthInputPacket::InputData::Ascend,
    v748::PlayerAuthInputPacket::InputData::Descend,
    v748::PlayerAuthInputPacket::InputData::NorthJumpDeprecated,
    v748::PlayerAuthInputPacket::InputData::JumpDown,
    v748::PlayerAuthInputPacket::InputData::SprintDown,
    v748::PlayerAuthInputPacket::InputData::ChangeHeight,
    v748::PlayerAuthInputPacket::InputData::Jumping,
    v748::PlayerAuthInputPacket::InputData::AutoJumpingInWater,
    v748::PlayerAuthInputPacket::InputData::Sneaking,
    v748::PlayerAuthInputPacket::InputData::SneakDown,
    v748::PlayerAuthInputPacket::InputData::Up,
    v748::PlayerAuthInputPacket::InputData::Down,
    v748::PlayerAuthInputPacket::InputData::Left,
    v748::PlayerAuthInputPacket::InputData::Right,
    v748::PlayerAuthInputPacket::InputData::UpLeft,
    v748::PlayerAuthInputPacket::InputData::UpRight,
    v748::PlayerAuthInputPacket::InputData::WantUp,
    v748::PlayerAuthInputPacket::InputData::WantDown,
    v748::PlayerAuthInputPacket::InputData::WantDownSlow,
    v748::PlayerAuthInputPacket::InputData::WantUpSlow,
    v748::PlayerAuthInputPacket::InputData::Sprinting,
    v748::PlayerAuthInputPacket::InputData::AscendBlock,
    v748::PlayerAuthInputPacket::InputData::DescendBlock,
    v748::PlayerAuthInputPacket::InputData::SneakToggleDown,
    v748::PlayerAuthInputPacket::InputData::PersistSneak,
    v748::PlayerAuthInputPacket::InputData::StartSprinting,
    v748::PlayerAuthInputPacket::InputData::StopSprinting,
    v748::PlayerAuthInputPacket::InputData::StartSneaking,
    v748::PlayerAuthInputPacket::InputData::StopSneaking,
    v748::PlayerAuthInputPacket::InputData::StartSwimming,
    v748::PlayerAuthInputPacket::InputData::StopSwimming,
    v748::PlayerAuthInputPacket::InputData::StartJumping,
    v748::PlayerAuthInputPacket::InputData::StartGliding,
    v748::PlayerAuthInputPacket::InputData::StopGliding,
    v748::PlayerAuthInputPacket::InputData::PerformItemInteraction,
    v748::PlayerAuthInputPacket::InputData::PerformBlockActions,
    v748::PlayerAuthInputPacket::InputData::PerformItemStackRequest,
    v748::PlayerAuthInputPacket::InputData::HandledTeleport,
    v748::PlayerAuthInputPacket::InputData::Emoting,
    v748::PlayerAuthInputPacket::InputData::MissedSwing,
    v748::PlayerAuthInputPacket::InputData::StartCrawling,
    v748::PlayerAuthInputPacket::InputData::StopCrawling,
    v748::PlayerAuthInputPacket::InputData::StartFlying,
    v748::PlayerAuthInputPacket::InputData::StopFlying,
    v748::PlayerAuthInputPacket::InputData::ClientAckServerData,
    v748::PlayerAuthInputPacket::InputData::IsInClientPredictedVehicle,
    v748::PlayerAuthInputPacket::InputData::PaddlingLeft,
    v748::PlayerAuthInputPacket::InputData::PaddlingRight,
    v748::PlayerAuthInputPacket::InputData::BlockBreakingDelayEnabled,
    v748::PlayerAuthInputPacket::InputData::HorizontalCollision,
    v748::PlayerAuthInputPacket::InputData::VerticalCollision,
    v748::PlayerAuthInputPacket::InputData::DownLeft,
    v748::PlayerAuthInputPacket::InputData::DownRight,
    v748::PlayerAuthInputPacket::InputData::StartUsingItem,
    v748::PlayerAuthInputPacket::InputData::IsCameraRelativeMovementEnabledDeprecated,
    v748::PlayerAuthInputPacket::InputData::IsRotControlledByMoveDirectionDeprecated,
    v748::PlayerAuthInputPacket::InputData::StartSpinAttack,
    v748::PlayerAuthInputPacket::InputData::StopSpinAttack,
    v748::PlayerAuthInputPacket::InputData::InputNum,
}};

template <>
inline constexpr std::array<std::string_view, 59> names_v<v748::PlayerAuthInputPacket::InputData>{{
    "ascend",
    "descend",
    "northjumpdeprecated",
    "jumpdown",
    "sprintdown",
    "changeheight",
    "jumping",
    "autojumpinginwater",
    "sneaking",
    "sneakdown",
    "up",
    "down",
    "left",
    "right",
    "upleft",
    "upright",
    "wantup",
    "wantdown",
    "wantdownslow",
    "wantupslow",
    "sprinting",
    "ascendblock",
    "descendblock",
    "sneaktoggledown",
    "persistsneak",
    "startsprinting",
    "stopsprinting",
    "startsneaking",
    "stopsneaking",
    "startswimming",
    "stopswimming",
    "startjumping",
    "startgliding",
    "stopgliding",
    "performiteminteraction",
    "performblockactions",
    "performitemstackrequest",
    "handledteleport",
    "emoting",
    "missedswing",
    "startcrawling",
    "stopcrawling",
    "startflying",
    "stopflying",
    "clientackserverdata",
    "isinclientpredictedvehicle",
    "paddlingleft",
    "paddlingright",
    "blockbreakingdelayenabled",
    "horizontalcollision",
    "verticalcollision",
    "downleft",
    "downright",
    "startusingitem",
    "iscamerarelativemovementenableddeprecated",
    "isrotcontrolledbymovedirectiondeprecated",
    "startspinattack",
    "stopspinattack",
    "inputnum",
}};

template <>
inline constexpr std::string_view type_name_v<v748::PlayerAuthInputPacket::InputData>{"PlayerAuthInputPacket::InputData"};

template <>
inline constexpr std::array<v766::PlayerAuthInputPacket::InputData, 66> values_v<v766::PlayerAuthInputPacket::InputData>{{
    v766::PlayerAuthInputPacket::InputData::Ascend,
    v766::PlayerAuthInputPacket::InputData::Descend,
    v766::PlayerAuthInputPacket::InputData::NorthJumpDeprecated,
    v766::PlayerAuthInputPacket::InputData::JumpDown,
    v766::PlayerAuthInputPacket::InputData::SprintDown,
    v766::PlayerAuthInputPacket::InputData::ChangeHeight,
    v766::PlayerAuthInputPacket::InputData::Jumping,
    v766::PlayerAuthInputPacket::InputData::AutoJumpingInWater,
    v766::PlayerAuthInputPacket::InputData::Sneaking,
    v766::PlayerAuthInputPacket::InputData::SneakDown,
    v766::PlayerAuthInputPacket::InputData::Up,
    v766::PlayerAuthInputPacket::InputData::Down,
    v766::PlayerAuthInputPacket::InputData::Left,
    v766::PlayerAuthInputPacket::InputData::Right,
    v766::PlayerAuthInputPacket::InputData::UpLeft,
    v766::PlayerAuthInputPacket::InputData::UpRight,
    v766::PlayerAuthInputPacket::InputData::WantUp,
    v766::PlayerAuthInputPacket::InputData::WantDown,
    v766::PlayerAuthInputPacket::InputData::WantDownSlow,
    v766::PlayerAuthInputPacket::InputData::WantUpSlow,
    v766::PlayerAuthInputPacket::InputData::Sprinting,
    v766::PlayerAuthInputPacket::InputData::AscendBlock,
    v766::PlayerAuthInputPacket::InputData::DescendBlock,
    v766::PlayerAuthInputPacket::InputData::SneakToggleDown,
    v766::PlayerAuthInputPacket::InputData::PersistSneak,
    v766::PlayerAuthInputPacket::InputData::StartSprinting,
    v766::PlayerAuthInputPacket::InputData::StopSprinting,
    v766::PlayerAuthInputPacket::InputData::StartSneaking,
    v766::PlayerAuthInputPacket::InputData::StopSneaking,
    v766::PlayerAuthInputPacket::InputData::StartSwimming,
    v766::PlayerAuthInputPacket::InputData::StopSwimming,
    v766::PlayerAuthInputPacket::InputData::StartJumping,
    v766::PlayerAuthInputPacket::InputData::StartGliding,
    v766::PlayerAuthInputPacket::InputData::StopGliding,
    v766::PlayerAuthInputPacket::InputData::PerformItemInteraction,
    v766::PlayerAuthInputPacket::InputData::PerformBlockActions,
    v766::PlayerAuthInputPacket::InputData::PerformItemStackRequest,
    v766::PlayerAuthInputPacket::InputData::HandledTeleport,
    v766::PlayerAuthInputPacket::InputData::Emoting,
    v766::PlayerAuthInputPacket::InputData::MissedSwing,
    v766::PlayerAuthInputPacket::InputData::StartCrawling,
    v766::PlayerAuthInputPacket::InputData::StopCrawling,
    v766::PlayerAuthInputPacket::InputData::StartFlying,
    v766::PlayerAuthInputPacket::InputData::StopFlying,
    v766::PlayerAuthInputPacket::InputData::ClientAckServerData,
    v766::PlayerAuthInputPacket::InputData::IsInClientPredictedVehicle,
    v766::PlayerAuthInputPacket::InputData::PaddlingLeft,
    v766::PlayerAuthInputPacket::InputData::PaddlingRight,
    v766::PlayerAuthInputPacket::InputData::BlockBreakingDelayEnabled,
    v766::PlayerAuthInputPacket::InputData::HorizontalCollision,
    v766::PlayerAuthInputPacket::InputData::VerticalCollision,
    v766::PlayerAuthInputPacket::InputData::DownLeft,
    v766::PlayerAuthInputPacket::InputData::DownRight,
    v766::PlayerAuthInputPacket::InputData::StartUsingItem,
    v766::PlayerAuthInputPacket::InputData::IsCameraRelativeMovementEnabledDeprecated,
    v766::PlayerAuthInputPacket::InputData::IsRotControlledByMoveDirectionDeprecated,
    v766::PlayerAuthInputPacket::InputData::StartSpinAttack,
    v766::PlayerAuthInputPacket::InputData::StopSpinAttack,
    v766::PlayerAuthInputPacket::InputData::IsHotbarOnlyTouch,
    v766::PlayerAuthInputPacket::InputData::JumpReleasedRaw,
    v766::PlayerAuthInputPacket::InputData::JumpPressedRaw,
    v766::PlayerAuthInputPacket::InputData::JumpCurrentRaw,
    v766::PlayerAuthInputPacket::InputData::SneakReleasedRaw,
    v766::PlayerAuthInputPacket::InputData::SneakPressedRaw,
    v766::PlayerAuthInputPacket::InputData::SneakCurrentRaw,
    v766::PlayerAuthInputPacket::InputData::InputNum,
}};

template <>
inline constexpr std::array<std::string_view, 66> names_v<v766::PlayerAuthInputPacket::InputData>{{
    "ascend",
    "descend",
    "northjumpdeprecated",
    "jumpdown",
    "sprintdown",
    "changeheight",
    "jumping",
    "autojumpinginwater",
    "sneaking",
    "sneakdown",
    "up",
    "down",
    "left",
    "right",
    "upleft",
    "upright",
    "wantup",
    "wantdown",
    "wantdownslow",
    "wantupslow",
    "sprinting",
    "ascendblock",
    "descendblock",
    "sneaktoggledown",
    "persistsneak",
    "startsprinting",
    "stopsprinting",
    "startsneaking",
    "stopsneaking",
    "startswimming",
    "stopswimming",
    "startjumping",
    "startgliding",
    "stopgliding",
    "performiteminteraction",
    "performblockactions",
    "performitemstackrequest",
    "handledteleport",
    "emoting",
    "missedswing",
    "startcrawling",
    "stopcrawling",
    "startflying",
    "stopflying",
    "clientackserverdata",
    "isinclientpredictedvehicle",
    "paddlingleft",
    "paddlingright",
    "blockbreakingdelayenabled",
    "horizontalcollision",
    "verticalcollision",
    "downleft",
    "downright",
    "startusingitem",
    "iscamerarelativemovementenableddeprecated",
    "isrotcontrolledbymovedirectiondeprecated",
    "startspinattack",
    "stopspinattack",
    "ishotbaronlytouch",
    "jumpreleasedraw",
    "jumppressedraw",
    "jumpcurrentraw",
    "sneakreleasedraw",
    "sneakpressedraw",
    "sneakcurrentraw",
    "inputnum",
}};

template <>
inline constexpr std::string_view type_name_v<v766::PlayerAuthInputPacket::InputData>{"PlayerAuthInputPacket::InputData"};

template <>
inline constexpr std::array<v844::PlayerAuthInputPacket::InputData, 66> values_v<v844::PlayerAuthInputPacket::InputData>{{
    v844::PlayerAuthInputPacket::InputData::Ascend,
    v844::PlayerAuthInputPacket::InputData::Descend,
    v844::PlayerAuthInputPacket::InputData::NorthJumpDeprecated,
    v844::PlayerAuthInputPacket::InputData::JumpDown,
    v844::PlayerAuthInputPacket::InputData::SprintDown,
    v844::PlayerAuthInputPacket::InputData::ChangeHeight,
    v844::PlayerAuthInputPacket::InputData::Jumping,
    v844::PlayerAuthInputPacket::InputData::AutoJumpingInWater,
    v844::PlayerAuthInputPacket::InputData::Sneaking,
    v844::PlayerAuthInputPacket::InputData::SneakDown,
    v844::PlayerAuthInputPacket::InputData::Up,
    v844::PlayerAuthInputPacket::InputData::Down,
    v844::PlayerAuthInputPacket::InputData::Left,
    v844::PlayerAuthInputPacket::InputData::Right,
    v844::PlayerAuthInputPacket::InputData::UpLeft,
    v844::PlayerAuthInputPacket::InputData::UpRight,
    v844::PlayerAuthInputPacket::InputData::WantUp,
    v844::PlayerAuthInputPacket::InputData::WantDown,
    v844::PlayerAuthInputPacket::InputData::WantDownSlow,
    v844::PlayerAuthInputPacket::InputData::WantUpSlow,
    v844::PlayerAuthInputPacket::InputData::Sprinting,
    v844::PlayerAuthInputPacket::InputData::AscendBlock,
    v844::PlayerAuthInputPacket::InputData::DescendBlock,
    v844::PlayerAuthInputPacket::InputData::SneakToggleDown,
    v844::PlayerAuthInputPacket::InputData::PersistSneak,
    v844::PlayerAuthInputPacket::InputData::StartSprinting,
    v844::PlayerAuthInputPacket::InputData::StopSprinting,
    v844::PlayerAuthInputPacket::InputData::StartSneaking,
    v844::PlayerAuthInputPacket::InputData::StopSneaking,
    v844::PlayerAuthInputPacket::InputData::StartSwimming,
    v844::PlayerAuthInputPacket::InputData::StopSwimming,
    v844::PlayerAuthInputPacket::InputData::StartJumping,
    v844::PlayerAuthInputPacket::InputData::StartGliding,
    v844::PlayerAuthInputPacket::InputData::StopGliding,
    v844::PlayerAuthInputPacket::InputData::PerformItemInteraction,
    v844::PlayerAuthInputPacket::InputData::PerformBlockActions,
    v844::PlayerAuthInputPacket::InputData::PerformItemStackRequest,
    v844::PlayerAuthInputPacket::InputData::HandledTeleport,
    v844::PlayerAuthInputPacket::InputData::Emoting,
    v844::PlayerAuthInputPacket::InputData::MissedSwing,
    v844::PlayerAuthInputPacket::InputData::StartCrawling,
    v844::PlayerAuthInputPacket::InputData::StopCrawling,
    v844::PlayerAuthInputPacket::InputData::StartFlying,
    v844::PlayerAuthInputPacket::InputData::StopFlying,
    v844::PlayerAuthInputPacket::InputData::ClientAckServerData,
    v844::PlayerAuthInputPacket::InputData::IsInClientPredictedVehicle,
    v844::PlayerAuthInputPacket::InputData::PaddlingLeft,
    v844::PlayerAuthInputPacket::InputData::PaddlingRight,
    v844::PlayerAuthInputPacket::InputData::BlockBreakingDelayEnabled,
    v844::PlayerAuthInputPacket::InputData::HorizontalCollision,
    v844::PlayerAuthInputPacket::InputData::VerticalCollision,
    v844::PlayerAuthInputPacket::InputData::DownLeft,
    v844::PlayerAuthInputPacket::InputData::DownRight,
    v844::PlayerAuthInputPacket::InputData::StartUsingItem,
    v844::PlayerAuthInputPacket::InputData::IsCameraRelativeMovementEnabledDeprecated,
    v844::PlayerAuthInputPacket::InputData::IsRotControlledByMoveDirectionDeprecated,
    v844::PlayerAuthInputPacket::InputData::StartSpinAttack,
    v844::PlayerAuthInputPacket::InputData::StopSpinAttack,
    v844::PlayerAuthInputPacket::InputData::IsHotbarOnlyTouch,
    v844::PlayerAuthInputPacket::InputData::JumpReleasedRaw,
    v844::PlayerAuthInputPacket::InputData::JumpPressedRaw,
    v844::PlayerAuthInputPacket::InputData::JumpCurrentRaw,
    v844::PlayerAuthInputPacket::InputData::SneakReleasedRaw,
    v844::PlayerAuthInputPacket::InputData::SneakPressedRaw,
    v844::PlayerAuthInputPacket::InputData::SneakCurrentRaw,
    v844::PlayerAuthInputPacket::InputData::InputNum,
}};

template <>
inline constexpr std::array<std::string_view, 66> names_v<v844::PlayerAuthInputPacket::InputData>{{
    "ascend",
    "descend",
    "northjumpdeprecated",
    "jumpdown",
    "sprintdown",
    "changeheight",
    "jumping",
    "autojumpinginwater",
    "sneaking",
    "sneakdown",
    "up",
    "down",
    "left",
    "right",
    "upleft",
    "upright",
    "wantup",
    "wantdown",
    "wantdownslow",
    "wantupslow",
    "sprinting",
    "ascendblock",
    "descendblock",
    "sneaktoggledown",
    "persistsneak",
    "startsprinting",
    "stopsprinting",
    "startsneaking",
    "stopsneaking",
    "startswimming",
    "stopswimming",
    "startjumping",
    "startgliding",
    "stopgliding",
    "performiteminteraction",
    "performblockactions",
    "performitemstackrequest",
    "handledteleport",
    "emoting",
    "missedswing",
    "startcrawling",
    "stopcrawling",
    "startflying",
    "stopflying",
    "clientackserverdata",
    "isinclientpredictedvehicle",
    "paddlingleft",
    "paddlingright",
    "blockbreakingdelayenabled",
    "horizontalcollision",
    "verticalcollision",
    "downleft",
    "downright",
    "startusingitem",
    "iscamerarelativemovementenableddeprecated",
    "isrotcontrolledbymovedirectiondeprecated",
    "startspinattack",
    "stopspinattack",
    "ishotbaronlytouch",
    "jumpreleasedraw",
    "jumppressedraw",
    "jumpcurrentraw",
    "sneakreleasedraw",
    "sneakpressedraw",
    "sneakcurrentraw",
    "inputnum",
}};

template <>
inline constexpr std::string_view type_name_v<v844::PlayerAuthInputPacket::InputData>{"PlayerAuthInputPacket::InputData"};

template <>
inline constexpr std::array<v924::PlayerAuthInputPacket::InputData, 66> values_v<v924::PlayerAuthInputPacket::InputData>{{
    v924::PlayerAuthInputPacket::InputData::Ascend,
    v924::PlayerAuthInputPacket::InputData::Descend,
    v924::PlayerAuthInputPacket::InputData::NorthJumpDeprecated,
    v924::PlayerAuthInputPacket::InputData::JumpDown,
    v924::PlayerAuthInputPacket::InputData::SprintDown,
    v924::PlayerAuthInputPacket::InputData::ChangeHeight,
    v924::PlayerAuthInputPacket::InputData::Jumping,
    v924::PlayerAuthInputPacket::InputData::AutoJumpingInWater,
    v924::PlayerAuthInputPacket::InputData::Sneaking,
    v924::PlayerAuthInputPacket::InputData::SneakDown,
    v924::PlayerAuthInputPacket::InputData::Up,
    v924::PlayerAuthInputPacket::InputData::Down,
    v924::PlayerAuthInputPacket::InputData::Left,
    v924::PlayerAuthInputPacket::InputData::Right,
    v924::PlayerAuthInputPacket::InputData::UpLeft,
    v924::PlayerAuthInputPacket::InputData::UpRight,
    v924::PlayerAuthInputPacket::InputData::WantUp,
    v924::PlayerAuthInputPacket::InputData::WantDown,
    v924::PlayerAuthInputPacket::InputData::WantDownSlow,
    v924::PlayerAuthInputPacket::InputData::WantUpSlow,
    v924::PlayerAuthInputPacket::InputData::Sprinting,
    v924::PlayerAuthInputPacket::InputData::AscendBlock,
    v924::PlayerAuthInputPacket::InputData::DescendBlock,
    v924::PlayerAuthInputPacket::InputData::SneakToggleDown,
    v924::PlayerAuthInputPacket::InputData::PersistSneak,
    v924::PlayerAuthInputPacket::InputData::StartSprinting,
    v924::PlayerAuthInputPacket::InputData::StopSprinting,
    v924::PlayerAuthInputPacket::InputData::StartSneaking,
    v924::PlayerAuthInputPacket::InputData::StopSneaking,
    v924::PlayerAuthInputPacket::InputData::StartSwimming,
    v924::PlayerAuthInputPacket::InputData::StopSwimming,
    v924::PlayerAuthInputPacket::InputData::StartJumping,
    v924::PlayerAuthInputPacket::InputData::StartGliding,
    v924::PlayerAuthInputPacket::InputData::StopGliding,
    v924::PlayerAuthInputPacket::InputData::PerformItemInteraction,
    v924::PlayerAuthInputPacket::InputData::PerformBlockActions,
    v924::PlayerAuthInputPacket::InputData::PerformItemStackRequest,
    v924::PlayerAuthInputPacket::InputData::HandledTeleport,
    v924::PlayerAuthInputPacket::InputData::Emoting,
    v924::PlayerAuthInputPacket::InputData::MissedSwing,
    v924::PlayerAuthInputPacket::InputData::StartCrawling,
    v924::PlayerAuthInputPacket::InputData::StopCrawling,
    v924::PlayerAuthInputPacket::InputData::StartFlying,
    v924::PlayerAuthInputPacket::InputData::StopFlying,
    v924::PlayerAuthInputPacket::InputData::ClientAckServerData,
    v924::PlayerAuthInputPacket::InputData::IsInClientPredictedVehicle,
    v924::PlayerAuthInputPacket::InputData::PaddlingLeft,
    v924::PlayerAuthInputPacket::InputData::PaddlingRight,
    v924::PlayerAuthInputPacket::InputData::BlockBreakingDelayEnabled,
    v924::PlayerAuthInputPacket::InputData::HorizontalCollision,
    v924::PlayerAuthInputPacket::InputData::VerticalCollision,
    v924::PlayerAuthInputPacket::InputData::DownLeft,
    v924::PlayerAuthInputPacket::InputData::DownRight,
    v924::PlayerAuthInputPacket::InputData::StartUsingItem,
    v924::PlayerAuthInputPacket::InputData::IsCameraRelativeMovementEnabledDeprecated,
    v924::PlayerAuthInputPacket::InputData::IsRotControlledByMoveDirectionDeprecated,
    v924::PlayerAuthInputPacket::InputData::StartSpinAttack,
    v924::PlayerAuthInputPacket::InputData::StopSpinAttack,
    v924::PlayerAuthInputPacket::InputData::IsHotbarOnlyTouch,
    v924::PlayerAuthInputPacket::InputData::JumpReleasedRaw,
    v924::PlayerAuthInputPacket::InputData::JumpPressedRaw,
    v924::PlayerAuthInputPacket::InputData::JumpCurrentRaw,
    v924::PlayerAuthInputPacket::InputData::SneakReleasedRaw,
    v924::PlayerAuthInputPacket::InputData::SneakPressedRaw,
    v924::PlayerAuthInputPacket::InputData::SneakCurrentRaw,
    v924::PlayerAuthInputPacket::InputData::InputNum,
}};

template <>
inline constexpr std::array<std::string_view, 66> names_v<v924::PlayerAuthInputPacket::InputData>{{
    "ascend",
    "descend",
    "northjumpdeprecated",
    "jumpdown",
    "sprintdown",
    "changeheight",
    "jumping",
    "autojumpinginwater",
    "sneaking",
    "sneakdown",
    "up",
    "down",
    "left",
    "right",
    "upleft",
    "upright",
    "wantup",
    "wantdown",
    "wantdownslow",
    "wantupslow",
    "sprinting",
    "ascendblock",
    "descendblock",
    "sneaktoggledown",
    "persistsneak",
    "startsprinting",
    "stopsprinting",
    "startsneaking",
    "stopsneaking",
    "startswimming",
    "stopswimming",
    "startjumping",
    "startgliding",
    "stopgliding",
    "performiteminteraction",
    "performblockactions",
    "performitemstackrequest",
    "handledteleport",
    "emoting",
    "missedswing",
    "startcrawling",
    "stopcrawling",
    "startflying",
    "stopflying",
    "clientackserverdata",
    "isinclientpredictedvehicle",
    "paddlingleft",
    "paddlingright",
    "blockbreakingdelayenabled",
    "horizontalcollision",
    "verticalcollision",
    "downleft",
    "downright",
    "startusingitem",
    "iscamerarelativemovementenableddeprecated",
    "isrotcontrolledbymovedirectiondeprecated",
    "startspinattack",
    "stopspinattack",
    "ishotbaronlytouch",
    "jumpreleasedraw",
    "jumppressedraw",
    "jumpcurrentraw",
    "sneakreleasedraw",
    "sneakpressedraw",
    "sneakcurrentraw",
    "inputnum",
}};

template <>
inline constexpr std::string_view type_name_v<v924::PlayerAuthInputPacket::InputData>{"PlayerAuthInputPacket::InputData"};

template <>
inline constexpr std::array<v944::PlayerAuthInputPacket::InputData, 66> values_v<v944::PlayerAuthInputPacket::InputData>{{
    v944::PlayerAuthInputPacket::InputData::Ascend,
    v944::PlayerAuthInputPacket::InputData::Descend,
    v944::PlayerAuthInputPacket::InputData::NorthJumpDeprecated,
    v944::PlayerAuthInputPacket::InputData::JumpDown,
    v944::PlayerAuthInputPacket::InputData::SprintDown,
    v944::PlayerAuthInputPacket::InputData::ChangeHeight,
    v944::PlayerAuthInputPacket::InputData::Jumping,
    v944::PlayerAuthInputPacket::InputData::AutoJumpingInWater,
    v944::PlayerAuthInputPacket::InputData::Sneaking,
    v944::PlayerAuthInputPacket::InputData::SneakDown,
    v944::PlayerAuthInputPacket::InputData::Up,
    v944::PlayerAuthInputPacket::InputData::Down,
    v944::PlayerAuthInputPacket::InputData::Left,
    v944::PlayerAuthInputPacket::InputData::Right,
    v944::PlayerAuthInputPacket::InputData::UpLeft,
    v944::PlayerAuthInputPacket::InputData::UpRight,
    v944::PlayerAuthInputPacket::InputData::WantUp,
    v944::PlayerAuthInputPacket::InputData::WantDown,
    v944::PlayerAuthInputPacket::InputData::WantDownSlow,
    v944::PlayerAuthInputPacket::InputData::WantUpSlow,
    v944::PlayerAuthInputPacket::InputData::Sprinting,
    v944::PlayerAuthInputPacket::InputData::AscendBlock,
    v944::PlayerAuthInputPacket::InputData::DescendBlock,
    v944::PlayerAuthInputPacket::InputData::SneakToggleDown,
    v944::PlayerAuthInputPacket::InputData::PersistSneak,
    v944::PlayerAuthInputPacket::InputData::StartSprinting,
    v944::PlayerAuthInputPacket::InputData::StopSprinting,
    v944::PlayerAuthInputPacket::InputData::StartSneaking,
    v944::PlayerAuthInputPacket::InputData::StopSneaking,
    v944::PlayerAuthInputPacket::InputData::StartSwimming,
    v944::PlayerAuthInputPacket::InputData::StopSwimming,
    v944::PlayerAuthInputPacket::InputData::StartJumping,
    v944::PlayerAuthInputPacket::InputData::StartGliding,
    v944::PlayerAuthInputPacket::InputData::StopGliding,
    v944::PlayerAuthInputPacket::InputData::PerformItemInteraction,
    v944::PlayerAuthInputPacket::InputData::PerformBlockActions,
    v944::PlayerAuthInputPacket::InputData::PerformItemStackRequest,
    v944::PlayerAuthInputPacket::InputData::HandledTeleport,
    v944::PlayerAuthInputPacket::InputData::Emoting,
    v944::PlayerAuthInputPacket::InputData::MissedSwing,
    v944::PlayerAuthInputPacket::InputData::StartCrawling,
    v944::PlayerAuthInputPacket::InputData::StopCrawling,
    v944::PlayerAuthInputPacket::InputData::StartFlying,
    v944::PlayerAuthInputPacket::InputData::StopFlying,
    v944::PlayerAuthInputPacket::InputData::ClientAckServerData,
    v944::PlayerAuthInputPacket::InputData::IsInClientPredictedVehicle,
    v944::PlayerAuthInputPacket::InputData::PaddlingLeft,
    v944::PlayerAuthInputPacket::InputData::PaddlingRight,
    v944::PlayerAuthInputPacket::InputData::BlockBreakingDelayEnabled,
    v944::PlayerAuthInputPacket::InputData::HorizontalCollision,
    v944::PlayerAuthInputPacket::InputData::VerticalCollision,
    v944::PlayerAuthInputPacket::InputData::DownLeft,
    v944::PlayerAuthInputPacket::InputData::DownRight,
    v944::PlayerAuthInputPacket::InputData::StartUsingItem,
    v944::PlayerAuthInputPacket::InputData::IsCameraRelativeMovementEnabledDeprecated,
    v944::PlayerAuthInputPacket::InputData::IsRotControlledByMoveDirectionDeprecated,
    v944::PlayerAuthInputPacket::InputData::StartSpinAttack,
    v944::PlayerAuthInputPacket::InputData::StopSpinAttack,
    v944::PlayerAuthInputPacket::InputData::IsHotbarOnlyTouch,
    v944::PlayerAuthInputPacket::InputData::JumpReleasedRaw,
    v944::PlayerAuthInputPacket::InputData::JumpPressedRaw,
    v944::PlayerAuthInputPacket::InputData::JumpCurrentRaw,
    v944::PlayerAuthInputPacket::InputData::SneakReleasedRaw,
    v944::PlayerAuthInputPacket::InputData::SneakPressedRaw,
    v944::PlayerAuthInputPacket::InputData::SneakCurrentRaw,
    v944::PlayerAuthInputPacket::InputData::InputNum,
}};

template <>
inline constexpr std::array<std::string_view, 66> names_v<v944::PlayerAuthInputPacket::InputData>{{
    "ascend",
    "descend",
    "northjumpdeprecated",
    "jumpdown",
    "sprintdown",
    "changeheight",
    "jumping",
    "autojumpinginwater",
    "sneaking",
    "sneakdown",
    "up",
    "down",
    "left",
    "right",
    "upleft",
    "upright",
    "wantup",
    "wantdown",
    "wantdownslow",
    "wantupslow",
    "sprinting",
    "ascendblock",
    "descendblock",
    "sneaktoggledown",
    "persistsneak",
    "startsprinting",
    "stopsprinting",
    "startsneaking",
    "stopsneaking",
    "startswimming",
    "stopswimming",
    "startjumping",
    "startgliding",
    "stopgliding",
    "performiteminteraction",
    "performblockactions",
    "performitemstackrequest",
    "handledteleport",
    "emoting",
    "missedswing",
    "startcrawling",
    "stopcrawling",
    "startflying",
    "stopflying",
    "clientackserverdata",
    "isinclientpredictedvehicle",
    "paddlingleft",
    "paddlingright",
    "blockbreakingdelayenabled",
    "horizontalcollision",
    "verticalcollision",
    "downleft",
    "downright",
    "startusingitem",
    "iscamerarelativemovementenableddeprecated",
    "isrotcontrolledbymovedirectiondeprecated",
    "startspinattack",
    "stopspinattack",
    "ishotbaronlytouch",
    "jumpreleasedraw",
    "jumppressedraw",
    "jumpcurrentraw",
    "sneakreleasedraw",
    "sneakpressedraw",
    "sneakcurrentraw",
    "inputnum",
}};

template <>
inline constexpr std::string_view type_name_v<v944::PlayerAuthInputPacket::InputData>{"PlayerAuthInputPacket::InputData"};

template <>
inline constexpr std::array<v975::PlayerAuthInputPacket::InputData, 66> values_v<v975::PlayerAuthInputPacket::InputData>{{
    v975::PlayerAuthInputPacket::InputData::Ascend,
    v975::PlayerAuthInputPacket::InputData::Descend,
    v975::PlayerAuthInputPacket::InputData::NorthJumpDeprecated,
    v975::PlayerAuthInputPacket::InputData::JumpDown,
    v975::PlayerAuthInputPacket::InputData::SprintDown,
    v975::PlayerAuthInputPacket::InputData::ChangeHeight,
    v975::PlayerAuthInputPacket::InputData::Jumping,
    v975::PlayerAuthInputPacket::InputData::AutoJumpingInWater,
    v975::PlayerAuthInputPacket::InputData::Sneaking,
    v975::PlayerAuthInputPacket::InputData::SneakDown,
    v975::PlayerAuthInputPacket::InputData::Up,
    v975::PlayerAuthInputPacket::InputData::Down,
    v975::PlayerAuthInputPacket::InputData::Left,
    v975::PlayerAuthInputPacket::InputData::Right,
    v975::PlayerAuthInputPacket::InputData::UpLeft,
    v975::PlayerAuthInputPacket::InputData::UpRight,
    v975::PlayerAuthInputPacket::InputData::WantUp,
    v975::PlayerAuthInputPacket::InputData::WantDown,
    v975::PlayerAuthInputPacket::InputData::WantDownSlow,
    v975::PlayerAuthInputPacket::InputData::WantUpSlow,
    v975::PlayerAuthInputPacket::InputData::Sprinting,
    v975::PlayerAuthInputPacket::InputData::AscendBlock,
    v975::PlayerAuthInputPacket::InputData::DescendBlock,
    v975::PlayerAuthInputPacket::InputData::SneakToggleDown,
    v975::PlayerAuthInputPacket::InputData::PersistSneak,
    v975::PlayerAuthInputPacket::InputData::StartSprinting,
    v975::PlayerAuthInputPacket::InputData::StopSprinting,
    v975::PlayerAuthInputPacket::InputData::StartSneaking,
    v975::PlayerAuthInputPacket::InputData::StopSneaking,
    v975::PlayerAuthInputPacket::InputData::StartSwimming,
    v975::PlayerAuthInputPacket::InputData::StopSwimming,
    v975::PlayerAuthInputPacket::InputData::StartJumping,
    v975::PlayerAuthInputPacket::InputData::StartGliding,
    v975::PlayerAuthInputPacket::InputData::StopGliding,
    v975::PlayerAuthInputPacket::InputData::PerformItemInteraction,
    v975::PlayerAuthInputPacket::InputData::PerformBlockActions,
    v975::PlayerAuthInputPacket::InputData::PerformItemStackRequest,
    v975::PlayerAuthInputPacket::InputData::HandledTeleport,
    v975::PlayerAuthInputPacket::InputData::Emoting,
    v975::PlayerAuthInputPacket::InputData::MissedSwing,
    v975::PlayerAuthInputPacket::InputData::StartCrawling,
    v975::PlayerAuthInputPacket::InputData::StopCrawling,
    v975::PlayerAuthInputPacket::InputData::StartFlying,
    v975::PlayerAuthInputPacket::InputData::StopFlying,
    v975::PlayerAuthInputPacket::InputData::ClientAckServerData,
    v975::PlayerAuthInputPacket::InputData::IsInClientPredictedVehicle,
    v975::PlayerAuthInputPacket::InputData::PaddlingLeft,
    v975::PlayerAuthInputPacket::InputData::PaddlingRight,
    v975::PlayerAuthInputPacket::InputData::BlockBreakingDelayEnabled,
    v975::PlayerAuthInputPacket::InputData::HorizontalCollision,
    v975::PlayerAuthInputPacket::InputData::VerticalCollision,
    v975::PlayerAuthInputPacket::InputData::DownLeft,
    v975::PlayerAuthInputPacket::InputData::DownRight,
    v975::PlayerAuthInputPacket::InputData::StartUsingItem,
    v975::PlayerAuthInputPacket::InputData::IsCameraRelativeMovementEnabledDeprecated,
    v975::PlayerAuthInputPacket::InputData::IsRotControlledByMoveDirectionDeprecated,
    v975::PlayerAuthInputPacket::InputData::StartSpinAttack,
    v975::PlayerAuthInputPacket::InputData::StopSpinAttack,
    v975::PlayerAuthInputPacket::InputData::IsHotbarOnlyTouch,
    v975::PlayerAuthInputPacket::InputData::JumpReleasedRaw,
    v975::PlayerAuthInputPacket::InputData::JumpPressedRaw,
    v975::PlayerAuthInputPacket::InputData::JumpCurrentRaw,
    v975::PlayerAuthInputPacket::InputData::SneakReleasedRaw,
    v975::PlayerAuthInputPacket::InputData::SneakPressedRaw,
    v975::PlayerAuthInputPacket::InputData::SneakCurrentRaw,
    v975::PlayerAuthInputPacket::InputData::InputNum,
}};

template <>
inline constexpr std::array<std::string_view, 66> names_v<v975::PlayerAuthInputPacket::InputData>{{
    "ascend",
    "descend",
    "northjumpdeprecated",
    "jumpdown",
    "sprintdown",
    "changeheight",
    "jumping",
    "autojumpinginwater",
    "sneaking",
    "sneakdown",
    "up",
    "down",
    "left",
    "right",
    "upleft",
    "upright",
    "wantup",
    "wantdown",
    "wantdownslow",
    "wantupslow",
    "sprinting",
    "ascendblock",
    "descendblock",
    "sneaktoggledown",
    "persistsneak",
    "startsprinting",
    "stopsprinting",
    "startsneaking",
    "stopsneaking",
    "startswimming",
    "stopswimming",
    "startjumping",
    "startgliding",
    "stopgliding",
    "performiteminteraction",
    "performblockactions",
    "performitemstackrequest",
    "handledteleport",
    "emoting",
    "missedswing",
    "startcrawling",
    "stopcrawling",
    "startflying",
    "stopflying",
    "clientackserverdata",
    "isinclientpredictedvehicle",
    "paddlingleft",
    "paddlingright",
    "blockbreakingdelayenabled",
    "horizontalcollision",
    "verticalcollision",
    "downleft",
    "downright",
    "startusingitem",
    "iscamerarelativemovementenableddeprecated",
    "isrotcontrolledbymovedirectiondeprecated",
    "startspinattack",
    "stopspinattack",
    "ishotbaronlytouch",
    "jumpreleasedraw",
    "jumppressedraw",
    "jumpcurrentraw",
    "sneakreleasedraw",
    "sneakpressedraw",
    "sneakcurrentraw",
    "inputnum",
}};

template <>
inline constexpr std::string_view type_name_v<v975::PlayerAuthInputPacket::InputData>{"PlayerAuthInputPacket::InputData"};

template <>
inline constexpr std::array<v1001::PlayerAuthInputPacket::InputData, 66> values_v<v1001::PlayerAuthInputPacket::InputData>{{
    v1001::PlayerAuthInputPacket::InputData::Ascend,
    v1001::PlayerAuthInputPacket::InputData::Descend,
    v1001::PlayerAuthInputPacket::InputData::NorthJumpDeprecated,
    v1001::PlayerAuthInputPacket::InputData::JumpDown,
    v1001::PlayerAuthInputPacket::InputData::SprintDown,
    v1001::PlayerAuthInputPacket::InputData::ChangeHeight,
    v1001::PlayerAuthInputPacket::InputData::Jumping,
    v1001::PlayerAuthInputPacket::InputData::AutoJumpingInWater,
    v1001::PlayerAuthInputPacket::InputData::Sneaking,
    v1001::PlayerAuthInputPacket::InputData::SneakDown,
    v1001::PlayerAuthInputPacket::InputData::Up,
    v1001::PlayerAuthInputPacket::InputData::Down,
    v1001::PlayerAuthInputPacket::InputData::Left,
    v1001::PlayerAuthInputPacket::InputData::Right,
    v1001::PlayerAuthInputPacket::InputData::UpLeft,
    v1001::PlayerAuthInputPacket::InputData::UpRight,
    v1001::PlayerAuthInputPacket::InputData::WantUp,
    v1001::PlayerAuthInputPacket::InputData::WantDown,
    v1001::PlayerAuthInputPacket::InputData::WantDownSlow,
    v1001::PlayerAuthInputPacket::InputData::WantUpSlow,
    v1001::PlayerAuthInputPacket::InputData::Sprinting,
    v1001::PlayerAuthInputPacket::InputData::AscendBlock,
    v1001::PlayerAuthInputPacket::InputData::DescendBlock,
    v1001::PlayerAuthInputPacket::InputData::SneakToggleDown,
    v1001::PlayerAuthInputPacket::InputData::PersistSneak,
    v1001::PlayerAuthInputPacket::InputData::StartSprinting,
    v1001::PlayerAuthInputPacket::InputData::StopSprinting,
    v1001::PlayerAuthInputPacket::InputData::StartSneaking,
    v1001::PlayerAuthInputPacket::InputData::StopSneaking,
    v1001::PlayerAuthInputPacket::InputData::StartSwimming,
    v1001::PlayerAuthInputPacket::InputData::StopSwimming,
    v1001::PlayerAuthInputPacket::InputData::StartJumping,
    v1001::PlayerAuthInputPacket::InputData::StartGliding,
    v1001::PlayerAuthInputPacket::InputData::StopGliding,
    v1001::PlayerAuthInputPacket::InputData::PerformItemInteraction,
    v1001::PlayerAuthInputPacket::InputData::PerformBlockActions,
    v1001::PlayerAuthInputPacket::InputData::PerformItemStackRequest,
    v1001::PlayerAuthInputPacket::InputData::HandledTeleport,
    v1001::PlayerAuthInputPacket::InputData::Emoting,
    v1001::PlayerAuthInputPacket::InputData::MissedSwing,
    v1001::PlayerAuthInputPacket::InputData::StartCrawling,
    v1001::PlayerAuthInputPacket::InputData::StopCrawling,
    v1001::PlayerAuthInputPacket::InputData::StartFlying,
    v1001::PlayerAuthInputPacket::InputData::StopFlying,
    v1001::PlayerAuthInputPacket::InputData::ClientAckServerData,
    v1001::PlayerAuthInputPacket::InputData::IsInClientPredictedVehicle,
    v1001::PlayerAuthInputPacket::InputData::PaddlingLeft,
    v1001::PlayerAuthInputPacket::InputData::PaddlingRight,
    v1001::PlayerAuthInputPacket::InputData::BlockBreakingDelayEnabled,
    v1001::PlayerAuthInputPacket::InputData::HorizontalCollision,
    v1001::PlayerAuthInputPacket::InputData::VerticalCollision,
    v1001::PlayerAuthInputPacket::InputData::DownLeft,
    v1001::PlayerAuthInputPacket::InputData::DownRight,
    v1001::PlayerAuthInputPacket::InputData::StartUsingItem,
    v1001::PlayerAuthInputPacket::InputData::IsCameraRelativeMovementEnabledDeprecated,
    v1001::PlayerAuthInputPacket::InputData::IsRotControlledByMoveDirectionDeprecated,
    v1001::PlayerAuthInputPacket::InputData::StartSpinAttack,
    v1001::PlayerAuthInputPacket::InputData::StopSpinAttack,
    v1001::PlayerAuthInputPacket::InputData::IsHotbarOnlyTouch,
    v1001::PlayerAuthInputPacket::InputData::JumpReleasedRaw,
    v1001::PlayerAuthInputPacket::InputData::JumpPressedRaw,
    v1001::PlayerAuthInputPacket::InputData::JumpCurrentRaw,
    v1001::PlayerAuthInputPacket::InputData::SneakReleasedRaw,
    v1001::PlayerAuthInputPacket::InputData::SneakPressedRaw,
    v1001::PlayerAuthInputPacket::InputData::SneakCurrentRaw,
    v1001::PlayerAuthInputPacket::InputData::InputNum,
}};

template <>
inline constexpr std::array<std::string_view, 66> names_v<v1001::PlayerAuthInputPacket::InputData>{{
    "ascend",
    "descend",
    "northjumpdeprecated",
    "jumpdown",
    "sprintdown",
    "changeheight",
    "jumping",
    "autojumpinginwater",
    "sneaking",
    "sneakdown",
    "up",
    "down",
    "left",
    "right",
    "upleft",
    "upright",
    "wantup",
    "wantdown",
    "wantdownslow",
    "wantupslow",
    "sprinting",
    "ascendblock",
    "descendblock",
    "sneaktoggledown",
    "persistsneak",
    "startsprinting",
    "stopsprinting",
    "startsneaking",
    "stopsneaking",
    "startswimming",
    "stopswimming",
    "startjumping",
    "startgliding",
    "stopgliding",
    "performiteminteraction",
    "performblockactions",
    "performitemstackrequest",
    "handledteleport",
    "emoting",
    "missedswing",
    "startcrawling",
    "stopcrawling",
    "startflying",
    "stopflying",
    "clientackserverdata",
    "isinclientpredictedvehicle",
    "paddlingleft",
    "paddlingright",
    "blockbreakingdelayenabled",
    "horizontalcollision",
    "verticalcollision",
    "downleft",
    "downright",
    "startusingitem",
    "iscamerarelativemovementenableddeprecated",
    "isrotcontrolledbymovedirectiondeprecated",
    "startspinattack",
    "stopspinattack",
    "ishotbaronlytouch",
    "jumpreleasedraw",
    "jumppressedraw",
    "jumpcurrentraw",
    "sneakreleasedraw",
    "sneakpressedraw",
    "sneakcurrentraw",
    "inputnum",
}};

template <>
inline constexpr std::string_view type_name_v<v1001::PlayerAuthInputPacket::InputData>{"PlayerAuthInputPacket::InputData"};

template <>
inline constexpr std::array<v2168::PlayerAuthInputPacket::InputData, 67> values_v<v2168::PlayerAuthInputPacket::InputData>{{
    v2168::PlayerAuthInputPacket::InputData::Ascend,
    v2168::PlayerAuthInputPacket::InputData::Descend,
    v2168::PlayerAuthInputPacket::InputData::NorthJumpDeprecated,
    v2168::PlayerAuthInputPacket::InputData::JumpDown,
    v2168::PlayerAuthInputPacket::InputData::SprintDown,
    v2168::PlayerAuthInputPacket::InputData::ChangeHeight,
    v2168::PlayerAuthInputPacket::InputData::Jumping,
    v2168::PlayerAuthInputPacket::InputData::AutoJumpingInWater,
    v2168::PlayerAuthInputPacket::InputData::Sneaking,
    v2168::PlayerAuthInputPacket::InputData::SneakDown,
    v2168::PlayerAuthInputPacket::InputData::Up,
    v2168::PlayerAuthInputPacket::InputData::Down,
    v2168::PlayerAuthInputPacket::InputData::Left,
    v2168::PlayerAuthInputPacket::InputData::Right,
    v2168::PlayerAuthInputPacket::InputData::UpLeft,
    v2168::PlayerAuthInputPacket::InputData::UpRight,
    v2168::PlayerAuthInputPacket::InputData::WantUp,
    v2168::PlayerAuthInputPacket::InputData::WantDown,
    v2168::PlayerAuthInputPacket::InputData::WantDownSlow,
    v2168::PlayerAuthInputPacket::InputData::WantUpSlow,
    v2168::PlayerAuthInputPacket::InputData::Sprinting,
    v2168::PlayerAuthInputPacket::InputData::AscendBlock,
    v2168::PlayerAuthInputPacket::InputData::DescendBlock,
    v2168::PlayerAuthInputPacket::InputData::SneakToggleDown,
    v2168::PlayerAuthInputPacket::InputData::PersistSneak,
    v2168::PlayerAuthInputPacket::InputData::StartSprinting,
    v2168::PlayerAuthInputPacket::InputData::StopSprinting,
    v2168::PlayerAuthInputPacket::InputData::StartSneaking,
    v2168::PlayerAuthInputPacket::InputData::StopSneaking,
    v2168::PlayerAuthInputPacket::InputData::StartSwimming,
    v2168::PlayerAuthInputPacket::InputData::StopSwimming,
    v2168::PlayerAuthInputPacket::InputData::StartJumping,
    v2168::PlayerAuthInputPacket::InputData::StartGliding,
    v2168::PlayerAuthInputPacket::InputData::StopGliding,
    v2168::PlayerAuthInputPacket::InputData::PerformItemInteraction,
    v2168::PlayerAuthInputPacket::InputData::PerformBlockActions,
    v2168::PlayerAuthInputPacket::InputData::PerformItemStackRequest,
    v2168::PlayerAuthInputPacket::InputData::HandledTeleport,
    v2168::PlayerAuthInputPacket::InputData::Emoting,
    v2168::PlayerAuthInputPacket::InputData::MissedSwing,
    v2168::PlayerAuthInputPacket::InputData::StartCrawling,
    v2168::PlayerAuthInputPacket::InputData::StopCrawling,
    v2168::PlayerAuthInputPacket::InputData::StartFlying,
    v2168::PlayerAuthInputPacket::InputData::StopFlying,
    v2168::PlayerAuthInputPacket::InputData::ClientAckServerData,
    v2168::PlayerAuthInputPacket::InputData::IsInClientPredictedVehicle,
    v2168::PlayerAuthInputPacket::InputData::PaddlingLeft,
    v2168::PlayerAuthInputPacket::InputData::PaddlingRight,
    v2168::PlayerAuthInputPacket::InputData::BlockBreakingDelayEnabled,
    v2168::PlayerAuthInputPacket::InputData::HorizontalCollision,
    v2168::PlayerAuthInputPacket::InputData::VerticalCollision,
    v2168::PlayerAuthInputPacket::InputData::DownLeft,
    v2168::PlayerAuthInputPacket::InputData::DownRight,
    v2168::PlayerAuthInputPacket::InputData::StartUsingItem,
    v2168::PlayerAuthInputPacket::InputData::IsCameraRelativeMovementEnabledDeprecated,
    v2168::PlayerAuthInputPacket::InputData::IsRotControlledByMoveDirectionDeprecated,
    v2168::PlayerAuthInputPacket::InputData::StartSpinAttack,
    v2168::PlayerAuthInputPacket::InputData::StopSpinAttack,
    v2168::PlayerAuthInputPacket::InputData::IsHotbarOnlyTouch,
    v2168::PlayerAuthInputPacket::InputData::JumpReleasedRaw,
    v2168::PlayerAuthInputPacket::InputData::JumpPressedRaw,
    v2168::PlayerAuthInputPacket::InputData::JumpCurrentRaw,
    v2168::PlayerAuthInputPacket::InputData::SneakReleasedRaw,
    v2168::PlayerAuthInputPacket::InputData::SneakPressedRaw,
    v2168::PlayerAuthInputPacket::InputData::SneakCurrentRaw,
    v2168::PlayerAuthInputPacket::InputData::InternalUpdate,
    v2168::PlayerAuthInputPacket::InputData::InputNum,
}};

template <>
inline constexpr std::array<std::string_view, 67> names_v<v2168::PlayerAuthInputPacket::InputData>{{
    "ascend",
    "descend",
    "northjumpdeprecated",
    "jumpdown",
    "sprintdown",
    "changeheight",
    "jumping",
    "autojumpinginwater",
    "sneaking",
    "sneakdown",
    "up",
    "down",
    "left",
    "right",
    "upleft",
    "upright",
    "wantup",
    "wantdown",
    "wantdownslow",
    "wantupslow",
    "sprinting",
    "ascendblock",
    "descendblock",
    "sneaktoggledown",
    "persistsneak",
    "startsprinting",
    "stopsprinting",
    "startsneaking",
    "stopsneaking",
    "startswimming",
    "stopswimming",
    "startjumping",
    "startgliding",
    "stopgliding",
    "performiteminteraction",
    "performblockactions",
    "performitemstackrequest",
    "handledteleport",
    "emoting",
    "missedswing",
    "startcrawling",
    "stopcrawling",
    "startflying",
    "stopflying",
    "clientackserverdata",
    "isinclientpredictedvehicle",
    "paddlingleft",
    "paddlingright",
    "blockbreakingdelayenabled",
    "horizontalcollision",
    "verticalcollision",
    "downleft",
    "downright",
    "startusingitem",
    "iscamerarelativemovementenableddeprecated",
    "isrotcontrolledbymovedirectiondeprecated",
    "startspinattack",
    "stopspinattack",
    "ishotbaronlytouch",
    "jumpreleasedraw",
    "jumppressedraw",
    "jumpcurrentraw",
    "sneakreleasedraw",
    "sneakpressedraw",
    "sneakcurrentraw",
    "internalupdate",
    "inputnum",
}};

template <>
inline constexpr std::string_view type_name_v<v2168::PlayerAuthInputPacket::InputData>{"PlayerAuthInputPacket::InputData"};

template <>
inline constexpr std::array<v2193::PlayerAuthInputPacket::InputData, 67> values_v<v2193::PlayerAuthInputPacket::InputData>{{
    v2193::PlayerAuthInputPacket::InputData::Ascend,
    v2193::PlayerAuthInputPacket::InputData::Descend,
    v2193::PlayerAuthInputPacket::InputData::NorthJumpDeprecated,
    v2193::PlayerAuthInputPacket::InputData::JumpDown,
    v2193::PlayerAuthInputPacket::InputData::SprintDown,
    v2193::PlayerAuthInputPacket::InputData::ChangeHeight,
    v2193::PlayerAuthInputPacket::InputData::Jumping,
    v2193::PlayerAuthInputPacket::InputData::AutoJumpingInWater,
    v2193::PlayerAuthInputPacket::InputData::Sneaking,
    v2193::PlayerAuthInputPacket::InputData::SneakDown,
    v2193::PlayerAuthInputPacket::InputData::Up,
    v2193::PlayerAuthInputPacket::InputData::Down,
    v2193::PlayerAuthInputPacket::InputData::Left,
    v2193::PlayerAuthInputPacket::InputData::Right,
    v2193::PlayerAuthInputPacket::InputData::UpLeft,
    v2193::PlayerAuthInputPacket::InputData::UpRight,
    v2193::PlayerAuthInputPacket::InputData::WantUp,
    v2193::PlayerAuthInputPacket::InputData::WantDown,
    v2193::PlayerAuthInputPacket::InputData::WantDownSlow,
    v2193::PlayerAuthInputPacket::InputData::WantUpSlow,
    v2193::PlayerAuthInputPacket::InputData::Sprinting,
    v2193::PlayerAuthInputPacket::InputData::AscendBlock,
    v2193::PlayerAuthInputPacket::InputData::DescendBlock,
    v2193::PlayerAuthInputPacket::InputData::SneakToggleDown,
    v2193::PlayerAuthInputPacket::InputData::PersistSneak,
    v2193::PlayerAuthInputPacket::InputData::StartSprinting,
    v2193::PlayerAuthInputPacket::InputData::StopSprinting,
    v2193::PlayerAuthInputPacket::InputData::StartSneaking,
    v2193::PlayerAuthInputPacket::InputData::StopSneaking,
    v2193::PlayerAuthInputPacket::InputData::StartSwimming,
    v2193::PlayerAuthInputPacket::InputData::StopSwimming,
    v2193::PlayerAuthInputPacket::InputData::StartJumping,
    v2193::PlayerAuthInputPacket::InputData::StartGliding,
    v2193::PlayerAuthInputPacket::InputData::StopGliding,
    v2193::PlayerAuthInputPacket::InputData::PerformItemInteraction,
    v2193::PlayerAuthInputPacket::InputData::PerformBlockActions,
    v2193::PlayerAuthInputPacket::InputData::PerformItemStackRequest,
    v2193::PlayerAuthInputPacket::InputData::HandledTeleport,
    v2193::PlayerAuthInputPacket::InputData::Emoting,
    v2193::PlayerAuthInputPacket::InputData::MissedSwing,
    v2193::PlayerAuthInputPacket::InputData::StartCrawling,
    v2193::PlayerAuthInputPacket::InputData::StopCrawling,
    v2193::PlayerAuthInputPacket::InputData::StartFlying,
    v2193::PlayerAuthInputPacket::InputData::StopFlying,
    v2193::PlayerAuthInputPacket::InputData::ClientAckServerData,
    v2193::PlayerAuthInputPacket::InputData::IsInClientPredictedVehicle,
    v2193::PlayerAuthInputPacket::InputData::PaddlingLeft,
    v2193::PlayerAuthInputPacket::InputData::PaddlingRight,
    v2193::PlayerAuthInputPacket::InputData::BlockBreakingDelayEnabled,
    v2193::PlayerAuthInputPacket::InputData::HorizontalCollision,
    v2193::PlayerAuthInputPacket::InputData::VerticalCollision,
    v2193::PlayerAuthInputPacket::InputData::DownLeft,
    v2193::PlayerAuthInputPacket::InputData::DownRight,
    v2193::PlayerAuthInputPacket::InputData::StartUsingItem,
    v2193::PlayerAuthInputPacket::InputData::IsCameraRelativeMovementEnabledDeprecated,
    v2193::PlayerAuthInputPacket::InputData::IsRotControlledByMoveDirectionDeprecated,
    v2193::PlayerAuthInputPacket::InputData::StartSpinAttack,
    v2193::PlayerAuthInputPacket::InputData::StopSpinAttack,
    v2193::PlayerAuthInputPacket::InputData::IsHotbarOnlyTouch,
    v2193::PlayerAuthInputPacket::InputData::JumpReleasedRaw,
    v2193::PlayerAuthInputPacket::InputData::JumpPressedRaw,
    v2193::PlayerAuthInputPacket::InputData::JumpCurrentRaw,
    v2193::PlayerAuthInputPacket::InputData::SneakReleasedRaw,
    v2193::PlayerAuthInputPacket::InputData::SneakPressedRaw,
    v2193::PlayerAuthInputPacket::InputData::SneakCurrentRaw,
    v2193::PlayerAuthInputPacket::InputData::InternalUpdate,
    v2193::PlayerAuthInputPacket::InputData::InputNum,
}};

template <>
inline constexpr std::array<std::string_view, 67> names_v<v2193::PlayerAuthInputPacket::InputData>{{
    "ascend",
    "descend",
    "northjumpdeprecated",
    "jumpdown",
    "sprintdown",
    "changeheight",
    "jumping",
    "autojumpinginwater",
    "sneaking",
    "sneakdown",
    "up",
    "down",
    "left",
    "right",
    "upleft",
    "upright",
    "wantup",
    "wantdown",
    "wantdownslow",
    "wantupslow",
    "sprinting",
    "ascendblock",
    "descendblock",
    "sneaktoggledown",
    "persistsneak",
    "startsprinting",
    "stopsprinting",
    "startsneaking",
    "stopsneaking",
    "startswimming",
    "stopswimming",
    "startjumping",
    "startgliding",
    "stopgliding",
    "performiteminteraction",
    "performblockactions",
    "performitemstackrequest",
    "handledteleport",
    "emoting",
    "missedswing",
    "startcrawling",
    "stopcrawling",
    "startflying",
    "stopflying",
    "clientackserverdata",
    "isinclientpredictedvehicle",
    "paddlingleft",
    "paddlingright",
    "blockbreakingdelayenabled",
    "horizontalcollision",
    "verticalcollision",
    "downleft",
    "downright",
    "startusingitem",
    "iscamerarelativemovementenableddeprecated",
    "isrotcontrolledbymovedirectiondeprecated",
    "startspinattack",
    "stopspinattack",
    "ishotbaronlytouch",
    "jumpreleasedraw",
    "jumppressedraw",
    "jumpcurrentraw",
    "sneakreleasedraw",
    "sneakpressedraw",
    "sneakcurrentraw",
    "internalupdate",
    "inputnum",
}};

template <>
inline constexpr std::string_view type_name_v<v2193::PlayerAuthInputPacket::InputData>{"PlayerAuthInputPacket::InputData"};

template <>
inline constexpr std::array<v2225::PlayerAuthInputPacket::InputData, 67> values_v<v2225::PlayerAuthInputPacket::InputData>{{
    v2225::PlayerAuthInputPacket::InputData::Ascend,
    v2225::PlayerAuthInputPacket::InputData::Descend,
    v2225::PlayerAuthInputPacket::InputData::NorthJumpDeprecated,
    v2225::PlayerAuthInputPacket::InputData::JumpDown,
    v2225::PlayerAuthInputPacket::InputData::SprintDown,
    v2225::PlayerAuthInputPacket::InputData::ChangeHeight,
    v2225::PlayerAuthInputPacket::InputData::Jumping,
    v2225::PlayerAuthInputPacket::InputData::AutoJumpingInWater,
    v2225::PlayerAuthInputPacket::InputData::Sneaking,
    v2225::PlayerAuthInputPacket::InputData::SneakDown,
    v2225::PlayerAuthInputPacket::InputData::Up,
    v2225::PlayerAuthInputPacket::InputData::Down,
    v2225::PlayerAuthInputPacket::InputData::Left,
    v2225::PlayerAuthInputPacket::InputData::Right,
    v2225::PlayerAuthInputPacket::InputData::UpLeft,
    v2225::PlayerAuthInputPacket::InputData::UpRight,
    v2225::PlayerAuthInputPacket::InputData::WantUp,
    v2225::PlayerAuthInputPacket::InputData::WantDown,
    v2225::PlayerAuthInputPacket::InputData::WantDownSlow,
    v2225::PlayerAuthInputPacket::InputData::WantUpSlow,
    v2225::PlayerAuthInputPacket::InputData::Sprinting,
    v2225::PlayerAuthInputPacket::InputData::AscendBlock,
    v2225::PlayerAuthInputPacket::InputData::DescendBlock,
    v2225::PlayerAuthInputPacket::InputData::SneakToggleDown,
    v2225::PlayerAuthInputPacket::InputData::PersistSneak,
    v2225::PlayerAuthInputPacket::InputData::StartSprinting,
    v2225::PlayerAuthInputPacket::InputData::StopSprinting,
    v2225::PlayerAuthInputPacket::InputData::StartSneaking,
    v2225::PlayerAuthInputPacket::InputData::StopSneaking,
    v2225::PlayerAuthInputPacket::InputData::StartSwimming,
    v2225::PlayerAuthInputPacket::InputData::StopSwimming,
    v2225::PlayerAuthInputPacket::InputData::StartJumping,
    v2225::PlayerAuthInputPacket::InputData::StartGliding,
    v2225::PlayerAuthInputPacket::InputData::StopGliding,
    v2225::PlayerAuthInputPacket::InputData::PerformItemInteraction,
    v2225::PlayerAuthInputPacket::InputData::PerformBlockActions,
    v2225::PlayerAuthInputPacket::InputData::PerformItemStackRequest,
    v2225::PlayerAuthInputPacket::InputData::HandledTeleport,
    v2225::PlayerAuthInputPacket::InputData::Emoting,
    v2225::PlayerAuthInputPacket::InputData::MissedSwing,
    v2225::PlayerAuthInputPacket::InputData::StartCrawling,
    v2225::PlayerAuthInputPacket::InputData::StopCrawling,
    v2225::PlayerAuthInputPacket::InputData::StartFlying,
    v2225::PlayerAuthInputPacket::InputData::StopFlying,
    v2225::PlayerAuthInputPacket::InputData::ClientAckServerData,
    v2225::PlayerAuthInputPacket::InputData::IsInClientPredictedVehicle,
    v2225::PlayerAuthInputPacket::InputData::PaddlingLeft,
    v2225::PlayerAuthInputPacket::InputData::PaddlingRight,
    v2225::PlayerAuthInputPacket::InputData::BlockBreakingDelayEnabled,
    v2225::PlayerAuthInputPacket::InputData::HorizontalCollision,
    v2225::PlayerAuthInputPacket::InputData::VerticalCollision,
    v2225::PlayerAuthInputPacket::InputData::DownLeft,
    v2225::PlayerAuthInputPacket::InputData::DownRight,
    v2225::PlayerAuthInputPacket::InputData::StartUsingItem,
    v2225::PlayerAuthInputPacket::InputData::IsCameraRelativeMovementEnabledDeprecated,
    v2225::PlayerAuthInputPacket::InputData::IsRotControlledByMoveDirectionDeprecated,
    v2225::PlayerAuthInputPacket::InputData::StartSpinAttack,
    v2225::PlayerAuthInputPacket::InputData::StopSpinAttack,
    v2225::PlayerAuthInputPacket::InputData::IsHotbarOnlyTouch,
    v2225::PlayerAuthInputPacket::InputData::JumpReleasedRaw,
    v2225::PlayerAuthInputPacket::InputData::JumpPressedRaw,
    v2225::PlayerAuthInputPacket::InputData::JumpCurrentRaw,
    v2225::PlayerAuthInputPacket::InputData::SneakReleasedRaw,
    v2225::PlayerAuthInputPacket::InputData::SneakPressedRaw,
    v2225::PlayerAuthInputPacket::InputData::SneakCurrentRaw,
    v2225::PlayerAuthInputPacket::InputData::InternalUpdate,
    v2225::PlayerAuthInputPacket::InputData::InputNum,
}};

template <>
inline constexpr std::array<std::string_view, 67> names_v<v2225::PlayerAuthInputPacket::InputData>{{
    "ascend",
    "descend",
    "northjumpdeprecated",
    "jumpdown",
    "sprintdown",
    "changeheight",
    "jumping",
    "autojumpinginwater",
    "sneaking",
    "sneakdown",
    "up",
    "down",
    "left",
    "right",
    "upleft",
    "upright",
    "wantup",
    "wantdown",
    "wantdownslow",
    "wantupslow",
    "sprinting",
    "ascendblock",
    "descendblock",
    "sneaktoggledown",
    "persistsneak",
    "startsprinting",
    "stopsprinting",
    "startsneaking",
    "stopsneaking",
    "startswimming",
    "stopswimming",
    "startjumping",
    "startgliding",
    "stopgliding",
    "performiteminteraction",
    "performblockactions",
    "performitemstackrequest",
    "handledteleport",
    "emoting",
    "missedswing",
    "startcrawling",
    "stopcrawling",
    "startflying",
    "stopflying",
    "clientackserverdata",
    "isinclientpredictedvehicle",
    "paddlingleft",
    "paddlingright",
    "blockbreakingdelayenabled",
    "horizontalcollision",
    "verticalcollision",
    "downleft",
    "downright",
    "startusingitem",
    "iscamerarelativemovementenableddeprecated",
    "isrotcontrolledbymovedirectiondeprecated",
    "startspinattack",
    "stopspinattack",
    "ishotbaronlytouch",
    "jumpreleasedraw",
    "jumppressedraw",
    "jumpcurrentraw",
    "sneakreleasedraw",
    "sneakpressedraw",
    "sneakcurrentraw",
    "internalupdate",
    "inputnum",
}};

template <>
inline constexpr std::string_view type_name_v<v2225::PlayerAuthInputPacket::InputData>{"PlayerAuthInputPacket::InputData"};

}  // namespace detail

namespace detail {

template <>
inline constexpr bool is_reflected_struct_v<base::PlayerBlockActionData> = true;

template <>
inline constexpr std::string_view struct_name_v<base::PlayerBlockActionData>{"PlayerBlockActionData"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<base::PlayerBlockActionData>{{
    "player_action_type",
    "pos",
    "facing",
}};

template <>
struct field_accessor<base::PlayerBlockActionData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.player_action_type;
        }
        else if constexpr (I == 1) {
            return value.pos;
        }
        else {
            return value.facing;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v748::PlayerBlockActionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v748::PlayerBlockActionData>{"PlayerBlockActionData"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v748::PlayerBlockActionData>{{
    "player_action_type",
    "pos",
    "facing",
}};

template <>
struct field_accessor<v748::PlayerBlockActionData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.player_action_type;
        }
        else if constexpr (I == 1) {
            return value.pos;
        }
        else {
            return value.facing;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::PlayerBlockActionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::PlayerBlockActionData>{"PlayerBlockActionData"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v2168::PlayerBlockActionData>{{
    "player_action_type",
    "pos",
    "facing",
}};

template <>
struct field_accessor<v2168::PlayerBlockActionData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.player_action_type;
        }
        else if constexpr (I == 1) {
            return value.pos;
        }
        else {
            return value.facing;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::PackedItemUseLegacyInventoryTransaction> = true;

template <>
inline constexpr std::string_view struct_name_v<base::PackedItemUseLegacyInventoryTransaction>{"PackedItemUseLegacyInventoryTransaction"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<base::PackedItemUseLegacyInventoryTransaction>{{
    "id",
    "slots",
    "transaction",
}};

template <>
struct field_accessor<base::PackedItemUseLegacyInventoryTransaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.id;
        }
        else if constexpr (I == 1) {
            return value.slots;
        }
        else {
            return value.transaction;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v748::PackedItemUseLegacyInventoryTransaction> = true;

template <>
inline constexpr std::string_view struct_name_v<v748::PackedItemUseLegacyInventoryTransaction>{"PackedItemUseLegacyInventoryTransaction"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v748::PackedItemUseLegacyInventoryTransaction>{{
    "id",
    "slots",
    "transaction",
}};

template <>
struct field_accessor<v748::PackedItemUseLegacyInventoryTransaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.id;
        }
        else if constexpr (I == 1) {
            return value.slots;
        }
        else {
            return value.transaction;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v844::PackedItemUseLegacyInventoryTransaction> = true;

template <>
inline constexpr std::string_view struct_name_v<v844::PackedItemUseLegacyInventoryTransaction>{"PackedItemUseLegacyInventoryTransaction"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v844::PackedItemUseLegacyInventoryTransaction>{{
    "id",
    "slots",
    "transaction",
}};

template <>
struct field_accessor<v844::PackedItemUseLegacyInventoryTransaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.id;
        }
        else if constexpr (I == 1) {
            return value.slots;
        }
        else {
            return value.transaction;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::PackedItemUseLegacyInventoryTransaction> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::PackedItemUseLegacyInventoryTransaction>{"PackedItemUseLegacyInventoryTransaction"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v924::PackedItemUseLegacyInventoryTransaction>{{
    "id",
    "slots",
    "transaction",
}};

template <>
struct field_accessor<v924::PackedItemUseLegacyInventoryTransaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.id;
        }
        else if constexpr (I == 1) {
            return value.slots;
        }
        else {
            return value.transaction;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::PackedItemUseLegacyInventoryTransaction> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::PackedItemUseLegacyInventoryTransaction>{"PackedItemUseLegacyInventoryTransaction"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v944::PackedItemUseLegacyInventoryTransaction>{{
    "id",
    "slots",
    "transaction",
}};

template <>
struct field_accessor<v944::PackedItemUseLegacyInventoryTransaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.id;
        }
        else if constexpr (I == 1) {
            return value.slots;
        }
        else {
            return value.transaction;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::PackedItemUseLegacyInventoryTransaction> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::PackedItemUseLegacyInventoryTransaction>{"PackedItemUseLegacyInventoryTransaction"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v1001::PackedItemUseLegacyInventoryTransaction>{{
    "id",
    "slots",
    "transaction",
}};

template <>
struct field_accessor<v1001::PackedItemUseLegacyInventoryTransaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.id;
        }
        else if constexpr (I == 1) {
            return value.slots;
        }
        else {
            return value.transaction;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::PackedItemUseLegacyInventoryTransaction> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::PackedItemUseLegacyInventoryTransaction>{"PackedItemUseLegacyInventoryTransaction"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v2168::PackedItemUseLegacyInventoryTransaction>{{
    "id",
    "slots",
    "transaction",
}};

template <>
struct field_accessor<v2168::PackedItemUseLegacyInventoryTransaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.id;
        }
        else if constexpr (I == 1) {
            return value.slots;
        }
        else {
            return value.transaction;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2193::PackedItemUseLegacyInventoryTransaction> = true;

template <>
inline constexpr std::string_view struct_name_v<v2193::PackedItemUseLegacyInventoryTransaction>{"PackedItemUseLegacyInventoryTransaction"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v2193::PackedItemUseLegacyInventoryTransaction>{{
    "id",
    "slots",
    "transaction",
}};

template <>
struct field_accessor<v2193::PackedItemUseLegacyInventoryTransaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.id;
        }
        else if constexpr (I == 1) {
            return value.slots;
        }
        else {
            return value.transaction;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::PackedItemUseLegacyInventoryTransaction> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::PackedItemUseLegacyInventoryTransaction>{"PackedItemUseLegacyInventoryTransaction"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v2225::PackedItemUseLegacyInventoryTransaction>{{
    "id",
    "slots",
    "transaction",
}};

template <>
struct field_accessor<v2225::PackedItemUseLegacyInventoryTransaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.id;
        }
        else if constexpr (I == 1) {
            return value.slots;
        }
        else {
            return value.transaction;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::PlayerAuthInputPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::PlayerAuthInputPacket>{"PlayerAuthInputPacket"};

template <>
inline constexpr std::array<std::string_view, 17> field_names_v<base::PlayerAuthInputPacket>{{
    "rot",
    "pos",
    "move",
    "y_head_rot",
    "input_data",
    "input_mode",
    "play_mode",
    "new_interaction_model",
    "gaze_direction",
    "client_tick",
    "pos_delta",
    "item_use_transaction",
    "item_stack_request",
    "player_block_actions",
    "vehicle_rot",
    "client_predicted_vehicle",
    "analog_move_vector",
}};

template <>
struct field_accessor<base::PlayerAuthInputPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.rot;
        }
        else if constexpr (I == 1) {
            return value.pos;
        }
        else if constexpr (I == 2) {
            return value.move;
        }
        else if constexpr (I == 3) {
            return value.y_head_rot;
        }
        else if constexpr (I == 4) {
            return value.input_data;
        }
        else if constexpr (I == 5) {
            return value.input_mode;
        }
        else if constexpr (I == 6) {
            return value.play_mode;
        }
        else if constexpr (I == 7) {
            return value.new_interaction_model;
        }
        else if constexpr (I == 8) {
            return value.gaze_direction;
        }
        else if constexpr (I == 9) {
            return value.client_tick;
        }
        else if constexpr (I == 10) {
            return value.pos_delta;
        }
        else if constexpr (I == 11) {
            return value.item_use_transaction;
        }
        else if constexpr (I == 12) {
            return value.item_stack_request;
        }
        else if constexpr (I == 13) {
            return value.player_block_actions;
        }
        else if constexpr (I == 14) {
            return value.vehicle_rot;
        }
        else if constexpr (I == 15) {
            return value.client_predicted_vehicle;
        }
        else {
            return value.analog_move_vector;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v748::PlayerAuthInputPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v748::PlayerAuthInputPacket>{"PlayerAuthInputPacket"};

template <>
inline constexpr std::array<std::string_view, 18> field_names_v<v748::PlayerAuthInputPacket>{{
    "rot",
    "pos",
    "move",
    "y_head_rot",
    "input_data",
    "input_mode",
    "play_mode",
    "new_interaction_model",
    "interact_rotation",
    "client_tick",
    "pos_delta",
    "item_use_transaction",
    "item_stack_request",
    "player_block_actions",
    "vehicle_rot",
    "client_predicted_vehicle",
    "analog_move_vector",
    "camera_orientation",
}};

template <>
struct field_accessor<v748::PlayerAuthInputPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.rot;
        }
        else if constexpr (I == 1) {
            return value.pos;
        }
        else if constexpr (I == 2) {
            return value.move;
        }
        else if constexpr (I == 3) {
            return value.y_head_rot;
        }
        else if constexpr (I == 4) {
            return value.input_data;
        }
        else if constexpr (I == 5) {
            return value.input_mode;
        }
        else if constexpr (I == 6) {
            return value.play_mode;
        }
        else if constexpr (I == 7) {
            return value.new_interaction_model;
        }
        else if constexpr (I == 8) {
            return value.interact_rotation;
        }
        else if constexpr (I == 9) {
            return value.client_tick;
        }
        else if constexpr (I == 10) {
            return value.pos_delta;
        }
        else if constexpr (I == 11) {
            return value.item_use_transaction;
        }
        else if constexpr (I == 12) {
            return value.item_stack_request;
        }
        else if constexpr (I == 13) {
            return value.player_block_actions;
        }
        else if constexpr (I == 14) {
            return value.vehicle_rot;
        }
        else if constexpr (I == 15) {
            return value.client_predicted_vehicle;
        }
        else if constexpr (I == 16) {
            return value.analog_move_vector;
        }
        else {
            return value.camera_orientation;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v766::PlayerAuthInputPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v766::PlayerAuthInputPacket>{"PlayerAuthInputPacket"};

template <>
inline constexpr std::array<std::string_view, 19> field_names_v<v766::PlayerAuthInputPacket>{{
    "rot",
    "pos",
    "move",
    "y_head_rot",
    "input_data",
    "input_mode",
    "play_mode",
    "new_interaction_model",
    "interact_rotation",
    "client_tick",
    "pos_delta",
    "item_use_transaction",
    "item_stack_request",
    "player_block_actions",
    "vehicle_rot",
    "client_predicted_vehicle",
    "analog_move_vector",
    "camera_orientation",
    "raw_move_vector",
}};

template <>
struct field_accessor<v766::PlayerAuthInputPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.rot;
        }
        else if constexpr (I == 1) {
            return value.pos;
        }
        else if constexpr (I == 2) {
            return value.move;
        }
        else if constexpr (I == 3) {
            return value.y_head_rot;
        }
        else if constexpr (I == 4) {
            return value.input_data;
        }
        else if constexpr (I == 5) {
            return value.input_mode;
        }
        else if constexpr (I == 6) {
            return value.play_mode;
        }
        else if constexpr (I == 7) {
            return value.new_interaction_model;
        }
        else if constexpr (I == 8) {
            return value.interact_rotation;
        }
        else if constexpr (I == 9) {
            return value.client_tick;
        }
        else if constexpr (I == 10) {
            return value.pos_delta;
        }
        else if constexpr (I == 11) {
            return value.item_use_transaction;
        }
        else if constexpr (I == 12) {
            return value.item_stack_request;
        }
        else if constexpr (I == 13) {
            return value.player_block_actions;
        }
        else if constexpr (I == 14) {
            return value.vehicle_rot;
        }
        else if constexpr (I == 15) {
            return value.client_predicted_vehicle;
        }
        else if constexpr (I == 16) {
            return value.analog_move_vector;
        }
        else if constexpr (I == 17) {
            return value.camera_orientation;
        }
        else {
            return value.raw_move_vector;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v844::PlayerAuthInputPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v844::PlayerAuthInputPacket>{"PlayerAuthInputPacket"};

template <>
inline constexpr std::array<std::string_view, 19> field_names_v<v844::PlayerAuthInputPacket>{{
    "rot",
    "pos",
    "move",
    "y_head_rot",
    "input_data",
    "input_mode",
    "play_mode",
    "new_interaction_model",
    "interact_rotation",
    "client_tick",
    "pos_delta",
    "item_use_transaction",
    "item_stack_request",
    "player_block_actions",
    "vehicle_rot",
    "client_predicted_vehicle",
    "analog_move_vector",
    "camera_orientation",
    "raw_move_vector",
}};

template <>
struct field_accessor<v844::PlayerAuthInputPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.rot;
        }
        else if constexpr (I == 1) {
            return value.pos;
        }
        else if constexpr (I == 2) {
            return value.move;
        }
        else if constexpr (I == 3) {
            return value.y_head_rot;
        }
        else if constexpr (I == 4) {
            return value.input_data;
        }
        else if constexpr (I == 5) {
            return value.input_mode;
        }
        else if constexpr (I == 6) {
            return value.play_mode;
        }
        else if constexpr (I == 7) {
            return value.new_interaction_model;
        }
        else if constexpr (I == 8) {
            return value.interact_rotation;
        }
        else if constexpr (I == 9) {
            return value.client_tick;
        }
        else if constexpr (I == 10) {
            return value.pos_delta;
        }
        else if constexpr (I == 11) {
            return value.item_use_transaction;
        }
        else if constexpr (I == 12) {
            return value.item_stack_request;
        }
        else if constexpr (I == 13) {
            return value.player_block_actions;
        }
        else if constexpr (I == 14) {
            return value.vehicle_rot;
        }
        else if constexpr (I == 15) {
            return value.client_predicted_vehicle;
        }
        else if constexpr (I == 16) {
            return value.analog_move_vector;
        }
        else if constexpr (I == 17) {
            return value.camera_orientation;
        }
        else {
            return value.raw_move_vector;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::PlayerAuthInputPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::PlayerAuthInputPacket>{"PlayerAuthInputPacket"};

template <>
inline constexpr std::array<std::string_view, 19> field_names_v<v924::PlayerAuthInputPacket>{{
    "rot",
    "pos",
    "move",
    "y_head_rot",
    "input_data",
    "input_mode",
    "play_mode",
    "new_interaction_model",
    "interact_rotation",
    "client_tick",
    "pos_delta",
    "item_use_transaction",
    "item_stack_request",
    "player_block_actions",
    "vehicle_rot",
    "client_predicted_vehicle",
    "analog_move_vector",
    "camera_orientation",
    "raw_move_vector",
}};

template <>
struct field_accessor<v924::PlayerAuthInputPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.rot;
        }
        else if constexpr (I == 1) {
            return value.pos;
        }
        else if constexpr (I == 2) {
            return value.move;
        }
        else if constexpr (I == 3) {
            return value.y_head_rot;
        }
        else if constexpr (I == 4) {
            return value.input_data;
        }
        else if constexpr (I == 5) {
            return value.input_mode;
        }
        else if constexpr (I == 6) {
            return value.play_mode;
        }
        else if constexpr (I == 7) {
            return value.new_interaction_model;
        }
        else if constexpr (I == 8) {
            return value.interact_rotation;
        }
        else if constexpr (I == 9) {
            return value.client_tick;
        }
        else if constexpr (I == 10) {
            return value.pos_delta;
        }
        else if constexpr (I == 11) {
            return value.item_use_transaction;
        }
        else if constexpr (I == 12) {
            return value.item_stack_request;
        }
        else if constexpr (I == 13) {
            return value.player_block_actions;
        }
        else if constexpr (I == 14) {
            return value.vehicle_rot;
        }
        else if constexpr (I == 15) {
            return value.client_predicted_vehicle;
        }
        else if constexpr (I == 16) {
            return value.analog_move_vector;
        }
        else if constexpr (I == 17) {
            return value.camera_orientation;
        }
        else {
            return value.raw_move_vector;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::PlayerAuthInputPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::PlayerAuthInputPacket>{"PlayerAuthInputPacket"};

template <>
inline constexpr std::array<std::string_view, 19> field_names_v<v944::PlayerAuthInputPacket>{{
    "rot",
    "pos",
    "move",
    "y_head_rot",
    "input_data",
    "input_mode",
    "play_mode",
    "new_interaction_model",
    "interact_rotation",
    "client_tick",
    "pos_delta",
    "item_use_transaction",
    "item_stack_request",
    "player_block_actions",
    "vehicle_rot",
    "client_predicted_vehicle",
    "analog_move_vector",
    "camera_orientation",
    "raw_move_vector",
}};

template <>
struct field_accessor<v944::PlayerAuthInputPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.rot;
        }
        else if constexpr (I == 1) {
            return value.pos;
        }
        else if constexpr (I == 2) {
            return value.move;
        }
        else if constexpr (I == 3) {
            return value.y_head_rot;
        }
        else if constexpr (I == 4) {
            return value.input_data;
        }
        else if constexpr (I == 5) {
            return value.input_mode;
        }
        else if constexpr (I == 6) {
            return value.play_mode;
        }
        else if constexpr (I == 7) {
            return value.new_interaction_model;
        }
        else if constexpr (I == 8) {
            return value.interact_rotation;
        }
        else if constexpr (I == 9) {
            return value.client_tick;
        }
        else if constexpr (I == 10) {
            return value.pos_delta;
        }
        else if constexpr (I == 11) {
            return value.item_use_transaction;
        }
        else if constexpr (I == 12) {
            return value.item_stack_request;
        }
        else if constexpr (I == 13) {
            return value.player_block_actions;
        }
        else if constexpr (I == 14) {
            return value.vehicle_rot;
        }
        else if constexpr (I == 15) {
            return value.client_predicted_vehicle;
        }
        else if constexpr (I == 16) {
            return value.analog_move_vector;
        }
        else if constexpr (I == 17) {
            return value.camera_orientation;
        }
        else {
            return value.raw_move_vector;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v975::PlayerAuthInputPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v975::PlayerAuthInputPacket>{"PlayerAuthInputPacket"};

template <>
inline constexpr std::array<std::string_view, 19> field_names_v<v975::PlayerAuthInputPacket>{{
    "rot",
    "pos",
    "move",
    "y_head_rot",
    "input_data",
    "input_mode",
    "play_mode",
    "new_interaction_model",
    "interact_rotation",
    "client_tick",
    "pos_delta",
    "item_use_transaction",
    "item_stack_request",
    "player_block_actions",
    "vehicle_rot",
    "client_predicted_vehicle",
    "analog_move_vector",
    "camera_orientation",
    "raw_move_vector",
}};

template <>
struct field_accessor<v975::PlayerAuthInputPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.rot;
        }
        else if constexpr (I == 1) {
            return value.pos;
        }
        else if constexpr (I == 2) {
            return value.move;
        }
        else if constexpr (I == 3) {
            return value.y_head_rot;
        }
        else if constexpr (I == 4) {
            return value.input_data;
        }
        else if constexpr (I == 5) {
            return value.input_mode;
        }
        else if constexpr (I == 6) {
            return value.play_mode;
        }
        else if constexpr (I == 7) {
            return value.new_interaction_model;
        }
        else if constexpr (I == 8) {
            return value.interact_rotation;
        }
        else if constexpr (I == 9) {
            return value.client_tick;
        }
        else if constexpr (I == 10) {
            return value.pos_delta;
        }
        else if constexpr (I == 11) {
            return value.item_use_transaction;
        }
        else if constexpr (I == 12) {
            return value.item_stack_request;
        }
        else if constexpr (I == 13) {
            return value.player_block_actions;
        }
        else if constexpr (I == 14) {
            return value.vehicle_rot;
        }
        else if constexpr (I == 15) {
            return value.client_predicted_vehicle;
        }
        else if constexpr (I == 16) {
            return value.analog_move_vector;
        }
        else if constexpr (I == 17) {
            return value.camera_orientation;
        }
        else {
            return value.raw_move_vector;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::PlayerAuthInputPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::PlayerAuthInputPacket>{"PlayerAuthInputPacket"};

template <>
inline constexpr std::array<std::string_view, 19> field_names_v<v1001::PlayerAuthInputPacket>{{
    "rot",
    "pos",
    "move",
    "y_head_rot",
    "input_data",
    "input_mode",
    "play_mode",
    "new_interaction_model",
    "interact_rotation",
    "client_tick",
    "pos_delta",
    "item_use_transaction",
    "item_stack_request",
    "player_block_actions",
    "vehicle_rot",
    "client_predicted_vehicle",
    "analog_move_vector",
    "camera_orientation",
    "raw_move_vector",
}};

template <>
struct field_accessor<v1001::PlayerAuthInputPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.rot;
        }
        else if constexpr (I == 1) {
            return value.pos;
        }
        else if constexpr (I == 2) {
            return value.move;
        }
        else if constexpr (I == 3) {
            return value.y_head_rot;
        }
        else if constexpr (I == 4) {
            return value.input_data;
        }
        else if constexpr (I == 5) {
            return value.input_mode;
        }
        else if constexpr (I == 6) {
            return value.play_mode;
        }
        else if constexpr (I == 7) {
            return value.new_interaction_model;
        }
        else if constexpr (I == 8) {
            return value.interact_rotation;
        }
        else if constexpr (I == 9) {
            return value.client_tick;
        }
        else if constexpr (I == 10) {
            return value.pos_delta;
        }
        else if constexpr (I == 11) {
            return value.item_use_transaction;
        }
        else if constexpr (I == 12) {
            return value.item_stack_request;
        }
        else if constexpr (I == 13) {
            return value.player_block_actions;
        }
        else if constexpr (I == 14) {
            return value.vehicle_rot;
        }
        else if constexpr (I == 15) {
            return value.client_predicted_vehicle;
        }
        else if constexpr (I == 16) {
            return value.analog_move_vector;
        }
        else if constexpr (I == 17) {
            return value.camera_orientation;
        }
        else {
            return value.raw_move_vector;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::PlayerAuthInputPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::PlayerAuthInputPacket>{"PlayerAuthInputPacket"};

template <>
inline constexpr std::array<std::string_view, 19> field_names_v<v2168::PlayerAuthInputPacket>{{
    "rot",
    "pos",
    "move",
    "y_head_rot",
    "input_data",
    "input_mode",
    "play_mode",
    "new_interaction_model",
    "interact_rotation",
    "client_tick",
    "pos_delta",
    "item_use_transaction",
    "item_stack_request",
    "player_block_actions",
    "vehicle_rot",
    "client_predicted_vehicle",
    "analog_move_vector",
    "camera_orientation",
    "raw_move_vector",
}};

template <>
struct field_accessor<v2168::PlayerAuthInputPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.rot;
        }
        else if constexpr (I == 1) {
            return value.pos;
        }
        else if constexpr (I == 2) {
            return value.move;
        }
        else if constexpr (I == 3) {
            return value.y_head_rot;
        }
        else if constexpr (I == 4) {
            return value.input_data;
        }
        else if constexpr (I == 5) {
            return value.input_mode;
        }
        else if constexpr (I == 6) {
            return value.play_mode;
        }
        else if constexpr (I == 7) {
            return value.new_interaction_model;
        }
        else if constexpr (I == 8) {
            return value.interact_rotation;
        }
        else if constexpr (I == 9) {
            return value.client_tick;
        }
        else if constexpr (I == 10) {
            return value.pos_delta;
        }
        else if constexpr (I == 11) {
            return value.item_use_transaction;
        }
        else if constexpr (I == 12) {
            return value.item_stack_request;
        }
        else if constexpr (I == 13) {
            return value.player_block_actions;
        }
        else if constexpr (I == 14) {
            return value.vehicle_rot;
        }
        else if constexpr (I == 15) {
            return value.client_predicted_vehicle;
        }
        else if constexpr (I == 16) {
            return value.analog_move_vector;
        }
        else if constexpr (I == 17) {
            return value.camera_orientation;
        }
        else {
            return value.raw_move_vector;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2193::PlayerAuthInputPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2193::PlayerAuthInputPacket>{"PlayerAuthInputPacket"};

template <>
inline constexpr std::array<std::string_view, 19> field_names_v<v2193::PlayerAuthInputPacket>{{
    "rot",
    "pos",
    "move",
    "y_head_rot",
    "input_data",
    "input_mode",
    "play_mode",
    "new_interaction_model",
    "interact_rotation",
    "client_tick",
    "pos_delta",
    "item_use_transaction",
    "item_stack_request",
    "player_block_actions",
    "vehicle_rot",
    "client_predicted_vehicle",
    "analog_move_vector",
    "camera_orientation",
    "raw_move_vector",
}};

template <>
struct field_accessor<v2193::PlayerAuthInputPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.rot;
        }
        else if constexpr (I == 1) {
            return value.pos;
        }
        else if constexpr (I == 2) {
            return value.move;
        }
        else if constexpr (I == 3) {
            return value.y_head_rot;
        }
        else if constexpr (I == 4) {
            return value.input_data;
        }
        else if constexpr (I == 5) {
            return value.input_mode;
        }
        else if constexpr (I == 6) {
            return value.play_mode;
        }
        else if constexpr (I == 7) {
            return value.new_interaction_model;
        }
        else if constexpr (I == 8) {
            return value.interact_rotation;
        }
        else if constexpr (I == 9) {
            return value.client_tick;
        }
        else if constexpr (I == 10) {
            return value.pos_delta;
        }
        else if constexpr (I == 11) {
            return value.item_use_transaction;
        }
        else if constexpr (I == 12) {
            return value.item_stack_request;
        }
        else if constexpr (I == 13) {
            return value.player_block_actions;
        }
        else if constexpr (I == 14) {
            return value.vehicle_rot;
        }
        else if constexpr (I == 15) {
            return value.client_predicted_vehicle;
        }
        else if constexpr (I == 16) {
            return value.analog_move_vector;
        }
        else if constexpr (I == 17) {
            return value.camera_orientation;
        }
        else {
            return value.raw_move_vector;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::PlayerAuthInputPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::PlayerAuthInputPacket>{"PlayerAuthInputPacket"};

template <>
inline constexpr std::array<std::string_view, 19> field_names_v<v2225::PlayerAuthInputPacket>{{
    "rot",
    "pos",
    "move",
    "y_head_rot",
    "input_data",
    "input_mode",
    "play_mode",
    "new_interaction_model",
    "interact_rotation",
    "client_tick",
    "pos_delta",
    "item_use_transaction",
    "item_stack_request",
    "player_block_actions",
    "vehicle_rot",
    "client_predicted_vehicle",
    "analog_move_vector",
    "camera_orientation",
    "raw_move_vector",
}};

template <>
struct field_accessor<v2225::PlayerAuthInputPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.rot;
        }
        else if constexpr (I == 1) {
            return value.pos;
        }
        else if constexpr (I == 2) {
            return value.move;
        }
        else if constexpr (I == 3) {
            return value.y_head_rot;
        }
        else if constexpr (I == 4) {
            return value.input_data;
        }
        else if constexpr (I == 5) {
            return value.input_mode;
        }
        else if constexpr (I == 6) {
            return value.play_mode;
        }
        else if constexpr (I == 7) {
            return value.new_interaction_model;
        }
        else if constexpr (I == 8) {
            return value.interact_rotation;
        }
        else if constexpr (I == 9) {
            return value.client_tick;
        }
        else if constexpr (I == 10) {
            return value.pos_delta;
        }
        else if constexpr (I == 11) {
            return value.item_use_transaction;
        }
        else if constexpr (I == 12) {
            return value.item_stack_request;
        }
        else if constexpr (I == 13) {
            return value.player_block_actions;
        }
        else if constexpr (I == 14) {
            return value.vehicle_rot;
        }
        else if constexpr (I == 15) {
            return value.client_predicted_vehicle;
        }
        else if constexpr (I == 16) {
            return value.analog_move_vector;
        }
        else if constexpr (I == 17) {
            return value.camera_orientation;
        }
        else {
            return value.raw_move_vector;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::PlayerActionPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::PlayerActionPacket>{"PlayerActionPacket"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<base::PlayerActionPacket>{{
    "runtime_id",
    "action",
    "pos",
    "result_pos",
    "face",
}};

template <>
struct field_accessor<base::PlayerActionPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.runtime_id;
        }
        else if constexpr (I == 1) {
            return value.action;
        }
        else if constexpr (I == 2) {
            return value.pos;
        }
        else if constexpr (I == 3) {
            return value.result_pos;
        }
        else {
            return value.face;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v748::PlayerActionPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v748::PlayerActionPacket>{"PlayerActionPacket"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v748::PlayerActionPacket>{{
    "runtime_id",
    "action",
    "pos",
    "result_pos",
    "face",
}};

template <>
struct field_accessor<v748::PlayerActionPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.runtime_id;
        }
        else if constexpr (I == 1) {
            return value.action;
        }
        else if constexpr (I == 2) {
            return value.pos;
        }
        else if constexpr (I == 3) {
            return value.result_pos;
        }
        else {
            return value.face;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::PlayerActionPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::PlayerActionPacket>{"PlayerActionPacket"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v944::PlayerActionPacket>{{
    "runtime_id",
    "action",
    "pos",
    "result_pos",
    "face",
}};

template <>
struct field_accessor<v944::PlayerActionPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.runtime_id;
        }
        else if constexpr (I == 1) {
            return value.action;
        }
        else if constexpr (I == 2) {
            return value.pos;
        }
        else if constexpr (I == 3) {
            return value.result_pos;
        }
        else {
            return value.face;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::PlayerActionPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::PlayerActionPacket>{"PlayerActionPacket"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v2168::PlayerActionPacket>{{
    "runtime_id",
    "action",
    "pos",
    "result_pos",
    "face",
}};

template <>
struct field_accessor<v2168::PlayerActionPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.runtime_id;
        }
        else if constexpr (I == 1) {
            return value.action;
        }
        else if constexpr (I == 2) {
            return value.pos;
        }
        else if constexpr (I == 3) {
            return value.result_pos;
        }
        else {
            return value.face;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::UpdateClientInputLocksPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::UpdateClientInputLocksPacket>{"UpdateClientInputLocksPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<base::UpdateClientInputLocksPacket>{{
    "input_lock_component_data",
    "server_pos",
}};

template <>
struct field_accessor<base::UpdateClientInputLocksPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.input_lock_component_data;
        }
        else {
            return value.server_pos;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::UpdateClientInputLocksPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::UpdateClientInputLocksPacket>{"UpdateClientInputLocksPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v944::UpdateClientInputLocksPacket>{{
    "input_lock_component_data",
}};

template <>
struct field_accessor<v944::UpdateClientInputLocksPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.input_lock_component_data;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::PassengerJumpPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::PassengerJumpPacket>{"PassengerJumpPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::PassengerJumpPacket>{{
    "jump_scale",
}};

template <>
struct field_accessor<base::PassengerJumpPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.jump_scale;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::PlayerInputPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::PlayerInputPacket>{"PlayerInputPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<base::PlayerInputPacket>{{
    "mov",
    "is_jumping",
    "is_sneaking",
}};

template <>
struct field_accessor<base::PlayerInputPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.mov;
        }
        else if constexpr (I == 1) {
            return value.is_jumping;
        }
        else {
            return value.is_sneaking;
        }
    }
};

}  // namespace detail


template <>
struct Serializer<base::PlayerBlockActionData> {
    static void serialize(BinaryWriter &stream, const base::PlayerBlockActionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::PlayerBlockActionData, std::error_code>;
};

template <>
struct Serializer<v748::PlayerBlockActionData> {
    static void serialize(BinaryWriter &stream, const v748::PlayerBlockActionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v748::PlayerBlockActionData, std::error_code>;
};

template <>
struct Serializer<v2168::PlayerBlockActionData> {
    static void serialize(BinaryWriter &stream, const v2168::PlayerBlockActionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::PlayerBlockActionData, std::error_code>;
};

template <>
struct Serializer<base::PackedItemUseLegacyInventoryTransaction> {
    static void serialize(BinaryWriter &stream, const base::PackedItemUseLegacyInventoryTransaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::PackedItemUseLegacyInventoryTransaction, std::error_code>;
};

template <>
struct Serializer<v748::PackedItemUseLegacyInventoryTransaction> {
    static void serialize(BinaryWriter &stream, const v748::PackedItemUseLegacyInventoryTransaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v748::PackedItemUseLegacyInventoryTransaction, std::error_code>;
};

template <>
struct Serializer<v844::PackedItemUseLegacyInventoryTransaction> {
    static void serialize(BinaryWriter &stream, const v844::PackedItemUseLegacyInventoryTransaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v844::PackedItemUseLegacyInventoryTransaction, std::error_code>;
};

template <>
struct Serializer<v924::PackedItemUseLegacyInventoryTransaction> {
    static void serialize(BinaryWriter &stream, const v924::PackedItemUseLegacyInventoryTransaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::PackedItemUseLegacyInventoryTransaction, std::error_code>;
};

template <>
struct Serializer<v944::PackedItemUseLegacyInventoryTransaction> {
    static void serialize(BinaryWriter &stream, const v944::PackedItemUseLegacyInventoryTransaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::PackedItemUseLegacyInventoryTransaction, std::error_code>;
};

template <>
struct Serializer<v1001::PackedItemUseLegacyInventoryTransaction> {
    static void serialize(BinaryWriter &stream, const v1001::PackedItemUseLegacyInventoryTransaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::PackedItemUseLegacyInventoryTransaction, std::error_code>;
};

template <>
struct Serializer<v2168::PackedItemUseLegacyInventoryTransaction> {
    static void serialize(BinaryWriter &stream, const v2168::PackedItemUseLegacyInventoryTransaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::PackedItemUseLegacyInventoryTransaction, std::error_code>;
};

template <>
struct Serializer<v2193::PackedItemUseLegacyInventoryTransaction> {
    static void serialize(BinaryWriter &stream, const v2193::PackedItemUseLegacyInventoryTransaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::PackedItemUseLegacyInventoryTransaction, std::error_code>;
};

template <>
struct Serializer<v2225::PackedItemUseLegacyInventoryTransaction> {
    static void serialize(BinaryWriter &stream, const v2225::PackedItemUseLegacyInventoryTransaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::PackedItemUseLegacyInventoryTransaction, std::error_code>;
};

template <>
struct Serializer<base::PlayerAuthInputPacket> {
    static void serialize(BinaryWriter &stream, const base::PlayerAuthInputPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::PlayerAuthInputPacket, std::error_code>;
};

template <>
struct Serializer<v748::PlayerAuthInputPacket> {
    static void serialize(BinaryWriter &stream, const v748::PlayerAuthInputPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v748::PlayerAuthInputPacket, std::error_code>;
};

template <>
struct Serializer<v766::PlayerAuthInputPacket> {
    static void serialize(BinaryWriter &stream, const v766::PlayerAuthInputPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v766::PlayerAuthInputPacket, std::error_code>;
};

template <>
struct Serializer<v844::PlayerAuthInputPacket> {
    static void serialize(BinaryWriter &stream, const v844::PlayerAuthInputPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v844::PlayerAuthInputPacket, std::error_code>;
};

template <>
struct Serializer<v924::PlayerAuthInputPacket> {
    static void serialize(BinaryWriter &stream, const v924::PlayerAuthInputPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::PlayerAuthInputPacket, std::error_code>;
};

template <>
struct Serializer<v944::PlayerAuthInputPacket> {
    static void serialize(BinaryWriter &stream, const v944::PlayerAuthInputPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::PlayerAuthInputPacket, std::error_code>;
};

template <>
struct Serializer<v975::PlayerAuthInputPacket> {
    static void serialize(BinaryWriter &stream, const v975::PlayerAuthInputPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v975::PlayerAuthInputPacket, std::error_code>;
};

template <>
struct Serializer<v1001::PlayerAuthInputPacket> {
    static void serialize(BinaryWriter &stream, const v1001::PlayerAuthInputPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::PlayerAuthInputPacket, std::error_code>;
};

template <>
struct Serializer<v2168::PlayerAuthInputPacket> {
    static void serialize(BinaryWriter &stream, const v2168::PlayerAuthInputPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::PlayerAuthInputPacket, std::error_code>;
};

template <>
struct Serializer<v2193::PlayerAuthInputPacket> {
    static void serialize(BinaryWriter &stream, const v2193::PlayerAuthInputPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::PlayerAuthInputPacket, std::error_code>;
};

template <>
struct Serializer<v2225::PlayerAuthInputPacket> {
    static void serialize(BinaryWriter &stream, const v2225::PlayerAuthInputPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::PlayerAuthInputPacket, std::error_code>;
};

template <>
struct Serializer<base::PlayerActionPacket> {
    static void serialize(BinaryWriter &stream, const base::PlayerActionPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::PlayerActionPacket, std::error_code>;
};

template <>
struct Serializer<v748::PlayerActionPacket> {
    static void serialize(BinaryWriter &stream, const v748::PlayerActionPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v748::PlayerActionPacket, std::error_code>;
};

template <>
struct Serializer<v944::PlayerActionPacket> {
    static void serialize(BinaryWriter &stream, const v944::PlayerActionPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::PlayerActionPacket, std::error_code>;
};

template <>
struct Serializer<v2168::PlayerActionPacket> {
    static void serialize(BinaryWriter &stream, const v2168::PlayerActionPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::PlayerActionPacket, std::error_code>;
};

template <>
struct Serializer<base::UpdateClientInputLocksPacket> {
    static void serialize(BinaryWriter &stream, const base::UpdateClientInputLocksPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::UpdateClientInputLocksPacket, std::error_code>;
};

template <>
struct Serializer<v944::UpdateClientInputLocksPacket> {
    static void serialize(BinaryWriter &stream, const v944::UpdateClientInputLocksPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::UpdateClientInputLocksPacket, std::error_code>;
};

template <>
struct Serializer<base::PassengerJumpPacket> {
    static void serialize(BinaryWriter &stream, const base::PassengerJumpPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::PassengerJumpPacket, std::error_code>;
};

template <>
struct Serializer<base::PlayerInputPacket> {
    static void serialize(BinaryWriter &stream, const base::PlayerInputPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::PlayerInputPacket, std::error_code>;
};
using PlayerActionType = PlayerActionType_<2225>;
using PlayerBlockActionData = PlayerBlockActionData_<2225>;
using PackedItemUseLegacyInventoryTransaction = PackedItemUseLegacyInventoryTransaction_<2225>;
using PlayerAuthInputPacket = PlayerAuthInputPacket_<2225>;
using PlayerActionPacket = PlayerActionPacket_<2225>;
using UpdateClientInputLocksPacket = UpdateClientInputLocksPacket_<2225>;

}  // namespace bedrock::protocol
