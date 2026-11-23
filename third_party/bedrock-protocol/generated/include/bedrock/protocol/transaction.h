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

#include <bedrock/protocol/actor.h>
#include <bedrock/protocol/common.h>
#include <bedrock/protocol/inventory.h>
#include <bedrock/protocol/item.h>
#include <bedrock/protocol/network.h>

namespace bedrock::protocol {

enum class InventorySourceType : std::uint32_t {
    InvalidInventory = static_cast<std::uint32_t>(-1),
    ContainerInventory = 0,
    GlobalInventory = 1,
    WorldInteraction = 2,
    CreativeInventory = 3,
    NonImplementedFeatureTodo = 99999,
};

namespace base {

struct LegacySetSlot {
    base::ContainerEnumName container_enum{};
    std::string slots{};
};

namespace InventorySource_nested {

enum class InventorySourceFlags : std::uint32_t {
    NoFlag = 0,
    WorldInteractionRandom = 1,
};

}  // namespace InventorySource_nested

struct InventorySource {
    using InventorySourceFlags = InventorySource_nested::InventorySourceFlags;

    InventorySourceType type{};
    base::ContainerID container_id{};
    base::InventorySource::InventorySourceFlags flags{};
};

struct InventoryAction {
    base::InventorySource source{};
    std::uint32_t slot{};
    NetworkItemStackDescriptor from_item_descriptor{};
    NetworkItemStackDescriptor to_item_descriptor{};
};

struct InventoryTransaction {
    std::vector<base::InventoryAction> actions{};
};

struct NormalTransactionData {
    base::InventoryTransaction transaction{};
};

struct InventoryMismatchData {
    base::InventoryTransaction transaction{};
};

namespace ItemUseInventoryTransaction_nested {

enum class ActionType : int {
    Place = 0,
    Use = 1,
    Destroy = 2,
};

enum class TriggerType : std::uint8_t {
    Unknown = 0,
    PlayerInput = 1,
    SimulationTick = 2,
};

enum class PredictedResult : std::uint8_t {
    Failure = 0,
    Success = 1,
};

enum class ClientCooldownState : std::uint8_t {
    Off = 0,
    On = 1,
};

}  // namespace ItemUseInventoryTransaction_nested

struct ItemUseInventoryTransaction {
    using ActionType = ItemUseInventoryTransaction_nested::ActionType;
    using TriggerType = ItemUseInventoryTransaction_nested::TriggerType;
    using PredictedResult = ItemUseInventoryTransaction_nested::PredictedResult;
    using ClientCooldownState = ItemUseInventoryTransaction_nested::ClientCooldownState;

    base::InventoryTransaction transaction{};
    base::ItemUseInventoryTransaction::ActionType action_type{};
    base::ItemUseInventoryTransaction::TriggerType trigger_type{};
    base::NetworkBlockPosition pos{};
    std::int32_t face{};
    std::int32_t slot{};
    NetworkItemStackDescriptor item{};
    Vec3 from_pos{};
    Vec3 click_pos{};
    BlockRuntimeId target_block_id{};
    base::ItemUseInventoryTransaction::PredictedResult client_predicted_result{};
};

}  // namespace base

namespace legacy {

namespace base {

struct ItemUseInventoryTransaction {
    std::vector<bedrock::protocol::base::InventoryAction> actions{};
    bedrock::protocol::base::ItemUseInventoryTransaction::ActionType action_type{};
    bedrock::protocol::base::ItemUseInventoryTransaction::TriggerType trigger_type{};
    bedrock::protocol::base::NetworkBlockPosition pos{};
    std::int32_t face{};
    std::int32_t slot{};
    NetworkItemStackDescriptor item{};
    Vec3 from_pos{};
    Vec3 click_pos{};
    BlockRuntimeId target_block_id{};
    bedrock::protocol::base::ItemUseInventoryTransaction::PredictedResult client_predicted_result{};
};

}  // namespace base

}  // namespace legacy

namespace base {

namespace ItemUseOnActorInventoryTransaction_nested {

enum class ActionType : int {
    Interact = 0,
    Attack = 1,
    ItemInteract = 2,
};

}  // namespace ItemUseOnActorInventoryTransaction_nested

struct ItemUseOnActorInventoryTransaction {
    using ActionType = ItemUseOnActorInventoryTransaction_nested::ActionType;

    base::InventoryTransaction transaction{};
    ActorRuntimeID runtime_id{};
    base::ItemUseOnActorInventoryTransaction::ActionType action_type{};
    std::int32_t slot{};
    NetworkItemStackDescriptor item{};
    Vec3 from_pos{};
    Vec3 hit_pos{};
};

namespace ItemReleaseInventoryTransaction_nested {

enum class ActionType : int {
    Release = 0,
    Use = 1,
};

}  // namespace ItemReleaseInventoryTransaction_nested

struct ItemReleaseInventoryTransaction {
    using ActionType = ItemReleaseInventoryTransaction_nested::ActionType;

    base::InventoryTransaction transaction{};
    base::ItemReleaseInventoryTransaction::ActionType action_type{};
    std::int32_t slot{};
    NetworkItemStackDescriptor item{};
    Vec3 from_pos{};
};

struct InventoryTransactionPacket {
    static constexpr int Id = 30;
    std::int32_t legacy_request_id{};
    std::vector<base::LegacySetSlot> legacy_set_item_slots{};
    std::variant<base::NormalTransactionData, base::InventoryMismatchData, base::ItemUseInventoryTransaction, base::ItemUseOnActorInventoryTransaction, base::ItemReleaseInventoryTransaction> transaction{};
};

using TransactionData = std::variant<base::NormalTransactionData, base::InventoryMismatchData, base::ItemUseInventoryTransaction, base::ItemUseOnActorInventoryTransaction, base::ItemReleaseInventoryTransaction>;

}  // namespace base

namespace v748 {

using LegacySetSlot = base::LegacySetSlot;

namespace InventorySource_nested {

using InventorySourceFlags = base::InventorySource::InventorySourceFlags;

}  // namespace InventorySource_nested

struct InventorySource {
    using InventorySourceFlags = InventorySource_nested::InventorySourceFlags;

    InventorySourceType type{};
    v748::ContainerID container_id{};
    v748::InventorySource::InventorySourceFlags flags{};
};

struct InventoryAction {
    v748::InventorySource source{};
    std::uint32_t slot{};
    NetworkItemStackDescriptor from_item_descriptor{};
    NetworkItemStackDescriptor to_item_descriptor{};
};

struct InventoryTransaction {
    std::vector<v748::InventoryAction> actions{};
};

struct NormalTransactionData {
    v748::InventoryTransaction transaction{};
};

struct InventoryMismatchData {
    v748::InventoryTransaction transaction{};
};

namespace ItemUseInventoryTransaction_nested {

enum class ActionType : int {
    Place = 0,
    Use = 1,
    Destroy = 2,
};

using TriggerType = base::ItemUseInventoryTransaction::TriggerType;
using PredictedResult = base::ItemUseInventoryTransaction::PredictedResult;
using ClientCooldownState = base::ItemUseInventoryTransaction::ClientCooldownState;

}  // namespace ItemUseInventoryTransaction_nested

struct ItemUseInventoryTransaction {
    using ActionType = ItemUseInventoryTransaction_nested::ActionType;
    using TriggerType = ItemUseInventoryTransaction_nested::TriggerType;
    using PredictedResult = ItemUseInventoryTransaction_nested::PredictedResult;
    using ClientCooldownState = ItemUseInventoryTransaction_nested::ClientCooldownState;

    v748::InventoryTransaction transaction{};
    v748::ItemUseInventoryTransaction::ActionType action_type{};
    v748::ItemUseInventoryTransaction::TriggerType trigger_type{};
    base::NetworkBlockPosition pos{};
    std::int32_t face{};
    std::int32_t slot{};
    NetworkItemStackDescriptor item{};
    Vec3 from_pos{};
    Vec3 click_pos{};
    BlockRuntimeId target_block_id{};
    v748::ItemUseInventoryTransaction::PredictedResult client_predicted_result{};
};

}  // namespace v748

namespace legacy {

namespace v748 {

struct ItemUseInventoryTransaction {
    std::vector<bedrock::protocol::v748::InventoryAction> actions{};
    bedrock::protocol::v748::ItemUseInventoryTransaction::ActionType action_type{};
    bedrock::protocol::v748::ItemUseInventoryTransaction::TriggerType trigger_type{};
    bedrock::protocol::base::NetworkBlockPosition pos{};
    std::int32_t face{};
    std::int32_t slot{};
    NetworkItemStackDescriptor item{};
    Vec3 from_pos{};
    Vec3 click_pos{};
    BlockRuntimeId target_block_id{};
    bedrock::protocol::v748::ItemUseInventoryTransaction::PredictedResult client_predicted_result{};
};

}  // namespace v748

}  // namespace legacy

namespace v748 {

namespace ItemUseOnActorInventoryTransaction_nested {

using ActionType = base::ItemUseOnActorInventoryTransaction::ActionType;

}  // namespace ItemUseOnActorInventoryTransaction_nested

struct ItemUseOnActorInventoryTransaction {
    using ActionType = ItemUseOnActorInventoryTransaction_nested::ActionType;

    v748::InventoryTransaction transaction{};
    ActorRuntimeID runtime_id{};
    v748::ItemUseOnActorInventoryTransaction::ActionType action_type{};
    std::int32_t slot{};
    NetworkItemStackDescriptor item{};
    Vec3 from_pos{};
    Vec3 hit_pos{};
};

namespace ItemReleaseInventoryTransaction_nested {

using ActionType = base::ItemReleaseInventoryTransaction::ActionType;

}  // namespace ItemReleaseInventoryTransaction_nested

struct ItemReleaseInventoryTransaction {
    using ActionType = ItemReleaseInventoryTransaction_nested::ActionType;

    v748::InventoryTransaction transaction{};
    v748::ItemReleaseInventoryTransaction::ActionType action_type{};
    std::int32_t slot{};
    NetworkItemStackDescriptor item{};
    Vec3 from_pos{};
};

struct InventoryTransactionPacket {
    static constexpr int Id = 30;
    std::int32_t legacy_request_id{};
    std::vector<base::LegacySetSlot> legacy_set_item_slots{};
    std::variant<v748::NormalTransactionData, v748::InventoryMismatchData, v748::ItemUseInventoryTransaction, v748::ItemUseOnActorInventoryTransaction, v748::ItemReleaseInventoryTransaction> transaction{};
};

using TransactionData = std::variant<v748::NormalTransactionData, v748::InventoryMismatchData, v748::ItemUseInventoryTransaction, v748::ItemUseOnActorInventoryTransaction, v748::ItemReleaseInventoryTransaction>;

}  // namespace v748

namespace v766 {

using LegacySetSlot = base::LegacySetSlot;

using InventorySource = v748::InventorySource;

using InventoryAction = v748::InventoryAction;

using InventoryTransaction = v748::InventoryTransaction;

using NormalTransactionData = v748::NormalTransactionData;

using InventoryMismatchData = v748::InventoryMismatchData;

using ItemUseInventoryTransaction = v748::ItemUseInventoryTransaction;

}  // namespace v766

namespace legacy {

namespace v766 {

using ItemUseInventoryTransaction = v748::ItemUseInventoryTransaction;

}  // namespace v766

}  // namespace legacy

namespace v766 {

using ItemUseOnActorInventoryTransaction = v748::ItemUseOnActorInventoryTransaction;

using ItemReleaseInventoryTransaction = v748::ItemReleaseInventoryTransaction;

using InventoryTransactionPacket = v748::InventoryTransactionPacket;

using TransactionData = v748::TransactionData;

}  // namespace v766

namespace v776 {

using LegacySetSlot = base::LegacySetSlot;

using InventorySource = v748::InventorySource;

using InventoryAction = v748::InventoryAction;

using InventoryTransaction = v748::InventoryTransaction;

using NormalTransactionData = v748::NormalTransactionData;

using InventoryMismatchData = v748::InventoryMismatchData;

using ItemUseInventoryTransaction = v748::ItemUseInventoryTransaction;

}  // namespace v776

namespace legacy {

namespace v776 {

using ItemUseInventoryTransaction = v748::ItemUseInventoryTransaction;

}  // namespace v776

}  // namespace legacy

namespace v776 {

using ItemUseOnActorInventoryTransaction = v748::ItemUseOnActorInventoryTransaction;

using ItemReleaseInventoryTransaction = v748::ItemReleaseInventoryTransaction;

using InventoryTransactionPacket = v748::InventoryTransactionPacket;

using TransactionData = v748::TransactionData;

}  // namespace v776

namespace v786 {

using LegacySetSlot = base::LegacySetSlot;

using InventorySource = v748::InventorySource;

using InventoryAction = v748::InventoryAction;

using InventoryTransaction = v748::InventoryTransaction;

using NormalTransactionData = v748::NormalTransactionData;

using InventoryMismatchData = v748::InventoryMismatchData;

using ItemUseInventoryTransaction = v748::ItemUseInventoryTransaction;

}  // namespace v786

namespace legacy {

namespace v786 {

using ItemUseInventoryTransaction = v748::ItemUseInventoryTransaction;

}  // namespace v786

}  // namespace legacy

namespace v786 {

using ItemUseOnActorInventoryTransaction = v748::ItemUseOnActorInventoryTransaction;

using ItemReleaseInventoryTransaction = v748::ItemReleaseInventoryTransaction;

using InventoryTransactionPacket = v748::InventoryTransactionPacket;

using TransactionData = v748::TransactionData;

}  // namespace v786

namespace v800 {

using LegacySetSlot = base::LegacySetSlot;

using InventorySource = v748::InventorySource;

using InventoryAction = v748::InventoryAction;

using InventoryTransaction = v748::InventoryTransaction;

using NormalTransactionData = v748::NormalTransactionData;

using InventoryMismatchData = v748::InventoryMismatchData;

using ItemUseInventoryTransaction = v748::ItemUseInventoryTransaction;

}  // namespace v800

namespace legacy {

namespace v800 {

using ItemUseInventoryTransaction = v748::ItemUseInventoryTransaction;

}  // namespace v800

}  // namespace legacy

namespace v800 {

using ItemUseOnActorInventoryTransaction = v748::ItemUseOnActorInventoryTransaction;

using ItemReleaseInventoryTransaction = v748::ItemReleaseInventoryTransaction;

using InventoryTransactionPacket = v748::InventoryTransactionPacket;

using TransactionData = v748::TransactionData;

}  // namespace v800

namespace v818 {

using LegacySetSlot = base::LegacySetSlot;

using InventorySource = v748::InventorySource;

using InventoryAction = v748::InventoryAction;

using InventoryTransaction = v748::InventoryTransaction;

using NormalTransactionData = v748::NormalTransactionData;

using InventoryMismatchData = v748::InventoryMismatchData;

using ItemUseInventoryTransaction = v748::ItemUseInventoryTransaction;

}  // namespace v818

namespace legacy {

namespace v818 {

using ItemUseInventoryTransaction = v748::ItemUseInventoryTransaction;

}  // namespace v818

}  // namespace legacy

namespace v818 {

using ItemUseOnActorInventoryTransaction = v748::ItemUseOnActorInventoryTransaction;

using ItemReleaseInventoryTransaction = v748::ItemReleaseInventoryTransaction;

using InventoryTransactionPacket = v748::InventoryTransactionPacket;

using TransactionData = v748::TransactionData;

}  // namespace v818

namespace v827 {

using LegacySetSlot = base::LegacySetSlot;

using InventorySource = v748::InventorySource;

using InventoryAction = v748::InventoryAction;

using InventoryTransaction = v748::InventoryTransaction;

using NormalTransactionData = v748::NormalTransactionData;

using InventoryMismatchData = v748::InventoryMismatchData;

using ItemUseInventoryTransaction = v748::ItemUseInventoryTransaction;

}  // namespace v827

namespace legacy {

namespace v827 {

using ItemUseInventoryTransaction = v748::ItemUseInventoryTransaction;

}  // namespace v827

}  // namespace legacy

namespace v827 {

using ItemUseOnActorInventoryTransaction = v748::ItemUseOnActorInventoryTransaction;

using ItemReleaseInventoryTransaction = v748::ItemReleaseInventoryTransaction;

using InventoryTransactionPacket = v748::InventoryTransactionPacket;

using TransactionData = v748::TransactionData;

}  // namespace v827

namespace v844 {

using LegacySetSlot = base::LegacySetSlot;

using InventorySource = v748::InventorySource;

using InventoryAction = v748::InventoryAction;

using InventoryTransaction = v748::InventoryTransaction;

using NormalTransactionData = v748::NormalTransactionData;

using InventoryMismatchData = v748::InventoryMismatchData;

namespace ItemUseInventoryTransaction_nested {

enum class ActionType : int {
    Place = 0,
    Use = 1,
    Destroy = 2,
    UseAsAttack = 3,
};

using TriggerType = base::ItemUseInventoryTransaction::TriggerType;
using PredictedResult = base::ItemUseInventoryTransaction::PredictedResult;
using ClientCooldownState = base::ItemUseInventoryTransaction::ClientCooldownState;

}  // namespace ItemUseInventoryTransaction_nested

struct ItemUseInventoryTransaction {
    using ActionType = ItemUseInventoryTransaction_nested::ActionType;
    using TriggerType = ItemUseInventoryTransaction_nested::TriggerType;
    using PredictedResult = ItemUseInventoryTransaction_nested::PredictedResult;
    using ClientCooldownState = ItemUseInventoryTransaction_nested::ClientCooldownState;

    v748::InventoryTransaction transaction{};
    v844::ItemUseInventoryTransaction::ActionType action_type{};
    v844::ItemUseInventoryTransaction::TriggerType trigger_type{};
    base::NetworkBlockPosition pos{};
    std::int32_t face{};
    std::int32_t slot{};
    NetworkItemStackDescriptor item{};
    Vec3 from_pos{};
    Vec3 click_pos{};
    BlockRuntimeId target_block_id{};
    v844::ItemUseInventoryTransaction::PredictedResult client_predicted_result{};
};

}  // namespace v844

namespace legacy {

namespace v844 {

struct ItemUseInventoryTransaction {
    std::vector<bedrock::protocol::v748::InventoryAction> actions{};
    bedrock::protocol::v844::ItemUseInventoryTransaction::ActionType action_type{};
    bedrock::protocol::v844::ItemUseInventoryTransaction::TriggerType trigger_type{};
    bedrock::protocol::base::NetworkBlockPosition pos{};
    std::int32_t face{};
    std::int32_t slot{};
    NetworkItemStackDescriptor item{};
    Vec3 from_pos{};
    Vec3 click_pos{};
    BlockRuntimeId target_block_id{};
    bedrock::protocol::v844::ItemUseInventoryTransaction::PredictedResult client_predicted_result{};
};

}  // namespace v844

}  // namespace legacy

namespace v844 {

using ItemUseOnActorInventoryTransaction = v748::ItemUseOnActorInventoryTransaction;

using ItemReleaseInventoryTransaction = v748::ItemReleaseInventoryTransaction;

struct InventoryTransactionPacket {
    static constexpr int Id = 30;
    std::int32_t legacy_request_id{};
    std::vector<base::LegacySetSlot> legacy_set_item_slots{};
    std::variant<v748::NormalTransactionData, v748::InventoryMismatchData, v844::ItemUseInventoryTransaction, v748::ItemUseOnActorInventoryTransaction, v748::ItemReleaseInventoryTransaction> transaction{};
};

using TransactionData = std::variant<v748::NormalTransactionData, v748::InventoryMismatchData, v844::ItemUseInventoryTransaction, v748::ItemUseOnActorInventoryTransaction, v748::ItemReleaseInventoryTransaction>;

}  // namespace v844

namespace v859 {

using LegacySetSlot = base::LegacySetSlot;

using InventorySource = v748::InventorySource;

using InventoryAction = v748::InventoryAction;

using InventoryTransaction = v748::InventoryTransaction;

using NormalTransactionData = v748::NormalTransactionData;

using InventoryMismatchData = v748::InventoryMismatchData;

using ItemUseInventoryTransaction = v844::ItemUseInventoryTransaction;

}  // namespace v859

namespace legacy {

namespace v859 {

using ItemUseInventoryTransaction = v844::ItemUseInventoryTransaction;

}  // namespace v859

}  // namespace legacy

namespace v859 {

using ItemUseOnActorInventoryTransaction = v748::ItemUseOnActorInventoryTransaction;

using ItemReleaseInventoryTransaction = v748::ItemReleaseInventoryTransaction;

using InventoryTransactionPacket = v844::InventoryTransactionPacket;

using TransactionData = v844::TransactionData;

}  // namespace v859

namespace v898 {

using LegacySetSlot = base::LegacySetSlot;

using InventorySource = v748::InventorySource;

using InventoryAction = v748::InventoryAction;

using InventoryTransaction = v748::InventoryTransaction;

using NormalTransactionData = v748::NormalTransactionData;

using InventoryMismatchData = v748::InventoryMismatchData;

using ItemUseInventoryTransaction = v844::ItemUseInventoryTransaction;

}  // namespace v898

namespace legacy {

namespace v898 {

using ItemUseInventoryTransaction = v844::ItemUseInventoryTransaction;

}  // namespace v898

}  // namespace legacy

namespace v898 {

using ItemUseOnActorInventoryTransaction = v748::ItemUseOnActorInventoryTransaction;

using ItemReleaseInventoryTransaction = v748::ItemReleaseInventoryTransaction;

using InventoryTransactionPacket = v844::InventoryTransactionPacket;

using TransactionData = v844::TransactionData;

}  // namespace v898

namespace v924 {

struct LegacySetSlot {
    v924::ContainerEnumName container_enum{};
    std::string slots{};
};

using InventorySource = v748::InventorySource;

using InventoryAction = v748::InventoryAction;

using InventoryTransaction = v748::InventoryTransaction;

using NormalTransactionData = v748::NormalTransactionData;

using InventoryMismatchData = v748::InventoryMismatchData;

using ItemUseInventoryTransaction = v844::ItemUseInventoryTransaction;

}  // namespace v924

namespace legacy {

namespace v924 {

using ItemUseInventoryTransaction = v844::ItemUseInventoryTransaction;

}  // namespace v924

}  // namespace legacy

namespace v924 {

using ItemUseOnActorInventoryTransaction = v748::ItemUseOnActorInventoryTransaction;

using ItemReleaseInventoryTransaction = v748::ItemReleaseInventoryTransaction;

struct InventoryTransactionPacket {
    static constexpr int Id = 30;
    std::int32_t legacy_request_id{};
    std::vector<v924::LegacySetSlot> legacy_set_item_slots{};
    std::variant<v748::NormalTransactionData, v748::InventoryMismatchData, v844::ItemUseInventoryTransaction, v748::ItemUseOnActorInventoryTransaction, v748::ItemReleaseInventoryTransaction> transaction{};
};

using TransactionData = v844::TransactionData;

}  // namespace v924

namespace v944 {

using LegacySetSlot = v924::LegacySetSlot;

using InventorySource = v748::InventorySource;

using InventoryAction = v748::InventoryAction;

using InventoryTransaction = v748::InventoryTransaction;

using NormalTransactionData = v748::NormalTransactionData;

using InventoryMismatchData = v748::InventoryMismatchData;

namespace ItemUseInventoryTransaction_nested {

enum class ActionType : int {
    Place = 0,
    Use = 1,
    Destroy = 2,
    UseAsAttack = 3,
};

using TriggerType = base::ItemUseInventoryTransaction::TriggerType;
using PredictedResult = base::ItemUseInventoryTransaction::PredictedResult;
using ClientCooldownState = base::ItemUseInventoryTransaction::ClientCooldownState;

}  // namespace ItemUseInventoryTransaction_nested

struct ItemUseInventoryTransaction {
    using ActionType = ItemUseInventoryTransaction_nested::ActionType;
    using TriggerType = ItemUseInventoryTransaction_nested::TriggerType;
    using PredictedResult = ItemUseInventoryTransaction_nested::PredictedResult;
    using ClientCooldownState = ItemUseInventoryTransaction_nested::ClientCooldownState;

    v748::InventoryTransaction transaction{};
    v944::ItemUseInventoryTransaction::ActionType action_type{};
    v944::ItemUseInventoryTransaction::TriggerType trigger_type{};
    BlockPos pos{};
    std::int32_t face{};
    std::int32_t slot{};
    NetworkItemStackDescriptor item{};
    Vec3 from_pos{};
    Vec3 click_pos{};
    BlockRuntimeId target_block_id{};
    v944::ItemUseInventoryTransaction::PredictedResult client_predicted_result{};
    v944::ItemUseInventoryTransaction::ClientCooldownState client_cooldown_state{};
};

}  // namespace v944

namespace legacy {

namespace v944 {

struct ItemUseInventoryTransaction {
    std::vector<bedrock::protocol::v748::InventoryAction> actions{};
    bedrock::protocol::v944::ItemUseInventoryTransaction::ActionType action_type{};
    bedrock::protocol::v944::ItemUseInventoryTransaction::TriggerType trigger_type{};
    BlockPos pos{};
    std::int32_t face{};
    std::int32_t slot{};
    NetworkItemStackDescriptor item{};
    Vec3 from_pos{};
    Vec3 click_pos{};
    BlockRuntimeId target_block_id{};
    bedrock::protocol::v944::ItemUseInventoryTransaction::PredictedResult client_predicted_result{};
    bedrock::protocol::v944::ItemUseInventoryTransaction::ClientCooldownState client_cooldown_state{};
};

}  // namespace v944

}  // namespace legacy

namespace v944 {

using ItemUseOnActorInventoryTransaction = v748::ItemUseOnActorInventoryTransaction;

using ItemReleaseInventoryTransaction = v748::ItemReleaseInventoryTransaction;

struct InventoryTransactionPacket {
    static constexpr int Id = 30;
    std::int32_t legacy_request_id{};
    std::vector<v924::LegacySetSlot> legacy_set_item_slots{};
    std::variant<v748::NormalTransactionData, v748::InventoryMismatchData, v944::ItemUseInventoryTransaction, v748::ItemUseOnActorInventoryTransaction, v748::ItemReleaseInventoryTransaction> transaction{};
};

using TransactionData = std::variant<v748::NormalTransactionData, v748::InventoryMismatchData, v944::ItemUseInventoryTransaction, v748::ItemUseOnActorInventoryTransaction, v748::ItemReleaseInventoryTransaction>;

}  // namespace v944

namespace v975 {

using LegacySetSlot = v924::LegacySetSlot;

using InventorySource = v748::InventorySource;

using InventoryAction = v748::InventoryAction;

using InventoryTransaction = v748::InventoryTransaction;

using NormalTransactionData = v748::NormalTransactionData;

using InventoryMismatchData = v748::InventoryMismatchData;

using ItemUseInventoryTransaction = v944::ItemUseInventoryTransaction;

}  // namespace v975

namespace legacy {

namespace v975 {

using ItemUseInventoryTransaction = v944::ItemUseInventoryTransaction;

}  // namespace v975

}  // namespace legacy

namespace v975 {

using ItemUseOnActorInventoryTransaction = v748::ItemUseOnActorInventoryTransaction;

using ItemReleaseInventoryTransaction = v748::ItemReleaseInventoryTransaction;

using InventoryTransactionPacket = v944::InventoryTransactionPacket;

using TransactionData = v944::TransactionData;

}  // namespace v975

namespace v1001 {

using LegacySetSlot = v924::LegacySetSlot;

namespace InventorySource_nested {

using InventorySourceFlags = base::InventorySource::InventorySourceFlags;

}  // namespace InventorySource_nested

struct InventorySource {
    using InventorySourceFlags = InventorySource_nested::InventorySourceFlags;

    InventorySourceType type{};
    std::optional<v748::ContainerID> container_id{};
    std::optional<v1001::InventorySource::InventorySourceFlags> flags{};
};

struct InventoryAction {
    v1001::InventorySource source{};
    std::uint32_t slot{};
    base::SerializedNetworkItemStackDescriptor from_item_descriptor{};
    base::SerializedNetworkItemStackDescriptor to_item_descriptor{};
};

struct InventoryTransaction {
    std::vector<v1001::InventoryAction> actions{};
};

struct NormalTransactionData {
    v1001::InventoryTransaction transaction{};
};

struct InventoryMismatchData {
    v1001::InventoryTransaction transaction{};
};

namespace ItemUseInventoryTransaction_nested {

enum class ActionType : int {
    Place = 0,
    Use = 1,
    Destroy = 2,
    UseAsAttack = 3,
};

using TriggerType = base::ItemUseInventoryTransaction::TriggerType;
using PredictedResult = base::ItemUseInventoryTransaction::PredictedResult;
using ClientCooldownState = base::ItemUseInventoryTransaction::ClientCooldownState;

}  // namespace ItemUseInventoryTransaction_nested

struct ItemUseInventoryTransaction {
    using ActionType = ItemUseInventoryTransaction_nested::ActionType;
    using TriggerType = ItemUseInventoryTransaction_nested::TriggerType;
    using PredictedResult = ItemUseInventoryTransaction_nested::PredictedResult;
    using ClientCooldownState = ItemUseInventoryTransaction_nested::ClientCooldownState;

    v1001::InventoryTransaction transaction{};
    v1001::ItemUseInventoryTransaction::ActionType action_type{};
    v1001::ItemUseInventoryTransaction::TriggerType trigger_type{};
    BlockPos pos{};
    std::uint8_t face{};
    std::int32_t slot{};
    base::SerializedNetworkItemStackDescriptor item{};
    Vec3 from_pos{};
    Vec3 click_pos{};
    BlockRuntimeId target_block_id{};
    v1001::ItemUseInventoryTransaction::PredictedResult client_predicted_result{};
    v1001::ItemUseInventoryTransaction::ClientCooldownState client_cooldown_state{};
};

}  // namespace v1001

namespace legacy {

namespace v1001 {

struct ItemUseInventoryTransaction {
    std::vector<bedrock::protocol::v1001::InventoryAction> actions{};
    bedrock::protocol::v1001::ItemUseInventoryTransaction::ActionType action_type{};
    bedrock::protocol::v1001::ItemUseInventoryTransaction::TriggerType trigger_type{};
    BlockPos pos{};
    std::int32_t face{};
    std::int32_t slot{};
    bedrock::protocol::base::SerializedNetworkItemStackDescriptor item{};
    Vec3 from_pos{};
    Vec3 click_pos{};
    BlockRuntimeId target_block_id{};
    bedrock::protocol::v1001::ItemUseInventoryTransaction::PredictedResult client_predicted_result{};
    bedrock::protocol::v1001::ItemUseInventoryTransaction::ClientCooldownState client_cooldown_state{};
};

}  // namespace v1001

}  // namespace legacy

namespace v1001 {

namespace ItemUseOnActorInventoryTransaction_nested {

using ActionType = base::ItemUseOnActorInventoryTransaction::ActionType;

}  // namespace ItemUseOnActorInventoryTransaction_nested

struct ItemUseOnActorInventoryTransaction {
    using ActionType = ItemUseOnActorInventoryTransaction_nested::ActionType;

    v1001::InventoryTransaction transaction{};
    ActorRuntimeID runtime_id{};
    v1001::ItemUseOnActorInventoryTransaction::ActionType action_type{};
    std::int32_t slot{};
    base::SerializedNetworkItemStackDescriptor item{};
    Vec3 from_pos{};
    Vec3 hit_pos{};
};

namespace ItemReleaseInventoryTransaction_nested {

using ActionType = base::ItemReleaseInventoryTransaction::ActionType;

}  // namespace ItemReleaseInventoryTransaction_nested

struct ItemReleaseInventoryTransaction {
    using ActionType = ItemReleaseInventoryTransaction_nested::ActionType;

    v1001::InventoryTransaction transaction{};
    v1001::ItemReleaseInventoryTransaction::ActionType action_type{};
    std::int32_t slot{};
    base::SerializedNetworkItemStackDescriptor item{};
    Vec3 from_pos{};
};

struct InventoryTransactionPacket {
    static constexpr int Id = 30;
    std::int32_t legacy_request_id{};
    std::optional<std::vector<v924::LegacySetSlot>> legacy_set_item_slots{};
    std::variant<v1001::NormalTransactionData, v1001::InventoryMismatchData, v1001::ItemUseInventoryTransaction, v1001::ItemUseOnActorInventoryTransaction, v1001::ItemReleaseInventoryTransaction> transaction{};
};

using TransactionData = std::variant<v1001::NormalTransactionData, v1001::InventoryMismatchData, v1001::ItemUseInventoryTransaction, v1001::ItemUseOnActorInventoryTransaction, v1001::ItemReleaseInventoryTransaction>;

}  // namespace v1001

namespace v2168 {

using LegacySetSlot = v924::LegacySetSlot;

using InventorySource = v1001::InventorySource;

struct InventoryAction {
    v1001::InventorySource source{};
    std::uint32_t slot{};
    v2168::SerializedNetworkItemStackDescriptor from_item_descriptor{};
    v2168::SerializedNetworkItemStackDescriptor to_item_descriptor{};
};

struct InventoryTransaction {
    std::vector<v2168::InventoryAction> actions{};
};

struct NormalTransactionData {
    v2168::InventoryTransaction transaction{};
};

struct InventoryMismatchData {
    v2168::InventoryTransaction transaction{};
};

namespace ItemUseInventoryTransaction_nested {

enum class ActionType : int {
    Place = 0,
    Use = 1,
    Destroy = 2,
    UseAsAttack = 3,
};

using TriggerType = base::ItemUseInventoryTransaction::TriggerType;
using PredictedResult = base::ItemUseInventoryTransaction::PredictedResult;
using ClientCooldownState = base::ItemUseInventoryTransaction::ClientCooldownState;

}  // namespace ItemUseInventoryTransaction_nested

struct ItemUseInventoryTransaction {
    using ActionType = ItemUseInventoryTransaction_nested::ActionType;
    using TriggerType = ItemUseInventoryTransaction_nested::TriggerType;
    using PredictedResult = ItemUseInventoryTransaction_nested::PredictedResult;
    using ClientCooldownState = ItemUseInventoryTransaction_nested::ClientCooldownState;

    v2168::InventoryTransaction transaction{};
    v2168::ItemUseInventoryTransaction::ActionType action_type{};
    v2168::ItemUseInventoryTransaction::TriggerType trigger_type{};
    BlockPos pos{};
    std::uint8_t face{};
    std::int32_t slot{};
    v2168::SerializedNetworkItemStackDescriptor item{};
    Vec3 from_pos{};
    Vec3 click_pos{};
    BlockRuntimeId target_block_id{};
    v2168::ItemUseInventoryTransaction::PredictedResult client_predicted_result{};
    v2168::ItemUseInventoryTransaction::ClientCooldownState client_cooldown_state{};
};

}  // namespace v2168

namespace legacy {

namespace v2168 {

struct ItemUseInventoryTransaction {
    std::vector<bedrock::protocol::v2168::InventoryAction> actions{};
    bedrock::protocol::v2168::ItemUseInventoryTransaction::ActionType action_type{};
    bedrock::protocol::v2168::ItemUseInventoryTransaction::TriggerType trigger_type{};
    BlockPos pos{};
    std::int32_t face{};
    std::int32_t slot{};
    bedrock::protocol::v2168::SerializedNetworkItemStackDescriptor item{};
    Vec3 from_pos{};
    Vec3 click_pos{};
    BlockRuntimeId target_block_id{};
    bedrock::protocol::v2168::ItemUseInventoryTransaction::PredictedResult client_predicted_result{};
    bedrock::protocol::v2168::ItemUseInventoryTransaction::ClientCooldownState client_cooldown_state{};
};

}  // namespace v2168

}  // namespace legacy

namespace v2168 {

namespace ItemUseOnActorInventoryTransaction_nested {

using ActionType = base::ItemUseOnActorInventoryTransaction::ActionType;

}  // namespace ItemUseOnActorInventoryTransaction_nested

struct ItemUseOnActorInventoryTransaction {
    using ActionType = ItemUseOnActorInventoryTransaction_nested::ActionType;

    v2168::InventoryTransaction transaction{};
    ActorRuntimeID runtime_id{};
    v2168::ItemUseOnActorInventoryTransaction::ActionType action_type{};
    std::int32_t slot{};
    v2168::SerializedNetworkItemStackDescriptor item{};
    Vec3 from_pos{};
    Vec3 hit_pos{};
};

namespace ItemReleaseInventoryTransaction_nested {

using ActionType = base::ItemReleaseInventoryTransaction::ActionType;

}  // namespace ItemReleaseInventoryTransaction_nested

struct ItemReleaseInventoryTransaction {
    using ActionType = ItemReleaseInventoryTransaction_nested::ActionType;

    v2168::InventoryTransaction transaction{};
    v2168::ItemReleaseInventoryTransaction::ActionType action_type{};
    std::int32_t slot{};
    v2168::SerializedNetworkItemStackDescriptor item{};
    Vec3 from_pos{};
};

struct InventoryTransactionPacket {
    static constexpr int Id = 30;
    std::int32_t legacy_request_id{};
    std::optional<std::vector<v924::LegacySetSlot>> legacy_set_item_slots{};
    std::variant<v2168::NormalTransactionData, v2168::InventoryMismatchData, v2168::ItemUseInventoryTransaction, v2168::ItemUseOnActorInventoryTransaction, v2168::ItemReleaseInventoryTransaction> transaction{};
};

using TransactionData = std::variant<v2168::NormalTransactionData, v2168::InventoryMismatchData, v2168::ItemUseInventoryTransaction, v2168::ItemUseOnActorInventoryTransaction, v2168::ItemReleaseInventoryTransaction>;

}  // namespace v2168

namespace v2193 {

using LegacySetSlot = v924::LegacySetSlot;

namespace InventorySource_nested {

using InventorySourceFlags = base::InventorySource::InventorySourceFlags;

}  // namespace InventorySource_nested

struct InventorySource {
    using InventorySourceFlags = InventorySource_nested::InventorySourceFlags;

    InventorySourceType type{};
    std::optional<v748::ContainerID> container_id{};
    std::optional<v2193::InventorySource::InventorySourceFlags> flags{};
};

struct InventoryAction {
    v2193::InventorySource source{};
    std::uint32_t slot{};
    v2168::SerializedNetworkItemStackDescriptor from_item_descriptor{};
    v2168::SerializedNetworkItemStackDescriptor to_item_descriptor{};
};

struct InventoryTransaction {
    std::vector<v2193::InventoryAction> actions{};
};

struct NormalTransactionData {
    v2193::InventoryTransaction transaction{};
};

struct InventoryMismatchData {
    v2193::InventoryTransaction transaction{};
};

namespace ItemUseInventoryTransaction_nested {

enum class ActionType : int {
    Place = 0,
    Use = 1,
    Destroy = 2,
    UseAsAttack = 3,
};

using TriggerType = base::ItemUseInventoryTransaction::TriggerType;
using PredictedResult = base::ItemUseInventoryTransaction::PredictedResult;
using ClientCooldownState = base::ItemUseInventoryTransaction::ClientCooldownState;

}  // namespace ItemUseInventoryTransaction_nested

struct ItemUseInventoryTransaction {
    using ActionType = ItemUseInventoryTransaction_nested::ActionType;
    using TriggerType = ItemUseInventoryTransaction_nested::TriggerType;
    using PredictedResult = ItemUseInventoryTransaction_nested::PredictedResult;
    using ClientCooldownState = ItemUseInventoryTransaction_nested::ClientCooldownState;

    v2193::InventoryTransaction transaction{};
    v2193::ItemUseInventoryTransaction::ActionType action_type{};
    v2193::ItemUseInventoryTransaction::TriggerType trigger_type{};
    BlockPos pos{};
    std::uint8_t face{};
    std::int32_t slot{};
    HandSlot hand{};
    v2168::SerializedNetworkItemStackDescriptor item{};
    Vec3 from_pos{};
    Vec3 click_pos{};
    BlockRuntimeId target_block_id{};
    v2193::ItemUseInventoryTransaction::PredictedResult client_predicted_result{};
    v2193::ItemUseInventoryTransaction::ClientCooldownState client_cooldown_state{};
};

}  // namespace v2193

namespace legacy {

namespace v2193 {

struct ItemUseInventoryTransaction {
    std::vector<bedrock::protocol::v2193::InventoryAction> actions{};
    bedrock::protocol::v2193::ItemUseInventoryTransaction::ActionType action_type{};
    bedrock::protocol::v2193::ItemUseInventoryTransaction::TriggerType trigger_type{};
    BlockPos pos{};
    std::int32_t face{};
    std::int32_t slot{};
    bedrock::protocol::v2168::SerializedNetworkItemStackDescriptor item{};
    Vec3 from_pos{};
    Vec3 click_pos{};
    BlockRuntimeId target_block_id{};
    bedrock::protocol::v2193::ItemUseInventoryTransaction::PredictedResult client_predicted_result{};
    bedrock::protocol::v2193::ItemUseInventoryTransaction::ClientCooldownState client_cooldown_state{};
};

}  // namespace v2193

}  // namespace legacy

namespace v2193 {

namespace ItemUseOnActorInventoryTransaction_nested {

using ActionType = base::ItemUseOnActorInventoryTransaction::ActionType;

}  // namespace ItemUseOnActorInventoryTransaction_nested

struct ItemUseOnActorInventoryTransaction {
    using ActionType = ItemUseOnActorInventoryTransaction_nested::ActionType;

    v2193::InventoryTransaction transaction{};
    ActorRuntimeID runtime_id{};
    v2193::ItemUseOnActorInventoryTransaction::ActionType action_type{};
    std::int32_t slot{};
    v2168::SerializedNetworkItemStackDescriptor item{};
    Vec3 from_pos{};
    Vec3 hit_pos{};
};

namespace ItemReleaseInventoryTransaction_nested {

using ActionType = base::ItemReleaseInventoryTransaction::ActionType;

}  // namespace ItemReleaseInventoryTransaction_nested

struct ItemReleaseInventoryTransaction {
    using ActionType = ItemReleaseInventoryTransaction_nested::ActionType;

    v2193::InventoryTransaction transaction{};
    v2193::ItemReleaseInventoryTransaction::ActionType action_type{};
    std::int32_t slot{};
    v2168::SerializedNetworkItemStackDescriptor item{};
    Vec3 from_pos{};
};

struct InventoryTransactionPacket {
    static constexpr int Id = 30;
    std::int32_t legacy_request_id{};
    std::optional<std::vector<v924::LegacySetSlot>> legacy_set_item_slots{};
    std::variant<v2193::NormalTransactionData, v2193::InventoryMismatchData, v2193::ItemUseInventoryTransaction, v2193::ItemUseOnActorInventoryTransaction, v2193::ItemReleaseInventoryTransaction> transaction{};
};

using TransactionData = std::variant<v2193::NormalTransactionData, v2193::InventoryMismatchData, v2193::ItemUseInventoryTransaction, v2193::ItemUseOnActorInventoryTransaction, v2193::ItemReleaseInventoryTransaction>;

}  // namespace v2193

namespace v2225 {

struct LegacySetSlot {
    v2225::ContainerEnumName container_enum{};
    std::string slots{};
};

using InventorySource = v2193::InventorySource;

using InventoryAction = v2193::InventoryAction;

using InventoryTransaction = v2193::InventoryTransaction;

using NormalTransactionData = v2193::NormalTransactionData;

using InventoryMismatchData = v2193::InventoryMismatchData;

using ItemUseInventoryTransaction = v2193::ItemUseInventoryTransaction;

}  // namespace v2225

namespace legacy {

namespace v2225 {

using ItemUseInventoryTransaction = v2193::ItemUseInventoryTransaction;

}  // namespace v2225

}  // namespace legacy

namespace v2225 {

namespace ItemUseOnActorInventoryTransaction_nested {

using ActionType = base::ItemUseOnActorInventoryTransaction::ActionType;

}  // namespace ItemUseOnActorInventoryTransaction_nested

struct ItemUseOnActorInventoryTransaction {
    using ActionType = ItemUseOnActorInventoryTransaction_nested::ActionType;

    v2193::InventoryTransaction transaction{};
    ActorRuntimeID runtime_id{};
    v2225::ItemUseOnActorInventoryTransaction::ActionType action_type{};
    std::int32_t slot{};
    HandSlot hand{};
    v2168::SerializedNetworkItemStackDescriptor item{};
    Vec3 from_pos{};
    Vec3 hit_pos{};
};

namespace ItemReleaseInventoryTransaction_nested {

using ActionType = base::ItemReleaseInventoryTransaction::ActionType;

}  // namespace ItemReleaseInventoryTransaction_nested

struct ItemReleaseInventoryTransaction {
    using ActionType = ItemReleaseInventoryTransaction_nested::ActionType;

    v2193::InventoryTransaction transaction{};
    v2225::ItemReleaseInventoryTransaction::ActionType action_type{};
    std::int32_t slot{};
    v2168::SerializedNetworkItemStackDescriptor item{};
    Vec3 from_pos{};
    HandSlot hand{};
};

struct InventoryTransactionPacket {
    static constexpr int Id = 30;
    std::int32_t legacy_request_id{};
    std::optional<std::vector<v2225::LegacySetSlot>> legacy_set_item_slots{};
    std::variant<v2193::NormalTransactionData, v2193::InventoryMismatchData, v2193::ItemUseInventoryTransaction, v2225::ItemUseOnActorInventoryTransaction, v2225::ItemReleaseInventoryTransaction> transaction{};
};

using TransactionData = std::variant<v2193::NormalTransactionData, v2193::InventoryMismatchData, v2193::ItemUseInventoryTransaction, v2225::ItemUseOnActorInventoryTransaction, v2225::ItemReleaseInventoryTransaction>;

}  // namespace v2225

namespace detail {

template <int V>
struct LegacySetSlot_;

template <int V> requires (V < 924)
struct LegacySetSlot_<V> { using type = base::LegacySetSlot; };

template <int V> requires (V >= 924 && V < 2225)
struct LegacySetSlot_<V> { using type = v924::LegacySetSlot; };

template <int V> requires (V >= 2225)
struct LegacySetSlot_<V> { using type = v2225::LegacySetSlot; };

template <int V>
struct InventorySource_;

template <int V> requires (V < 748)
struct InventorySource_<V> { using type = base::InventorySource; };

template <int V> requires (V >= 748 && V < 1001)
struct InventorySource_<V> { using type = v748::InventorySource; };

template <int V> requires (V >= 1001 && V < 2193)
struct InventorySource_<V> { using type = v1001::InventorySource; };

template <int V> requires (V >= 2193)
struct InventorySource_<V> { using type = v2193::InventorySource; };

template <int V>
struct InventoryAction_;

template <int V> requires (V < 748)
struct InventoryAction_<V> { using type = base::InventoryAction; };

template <int V> requires (V >= 748 && V < 1001)
struct InventoryAction_<V> { using type = v748::InventoryAction; };

template <int V> requires (V >= 1001 && V < 2168)
struct InventoryAction_<V> { using type = v1001::InventoryAction; };

template <int V> requires (V >= 2168 && V < 2193)
struct InventoryAction_<V> { using type = v2168::InventoryAction; };

template <int V> requires (V >= 2193)
struct InventoryAction_<V> { using type = v2193::InventoryAction; };

template <int V>
struct InventoryTransaction_;

template <int V> requires (V < 748)
struct InventoryTransaction_<V> { using type = base::InventoryTransaction; };

template <int V> requires (V >= 748 && V < 1001)
struct InventoryTransaction_<V> { using type = v748::InventoryTransaction; };

template <int V> requires (V >= 1001 && V < 2168)
struct InventoryTransaction_<V> { using type = v1001::InventoryTransaction; };

template <int V> requires (V >= 2168 && V < 2193)
struct InventoryTransaction_<V> { using type = v2168::InventoryTransaction; };

template <int V> requires (V >= 2193)
struct InventoryTransaction_<V> { using type = v2193::InventoryTransaction; };

template <int V>
struct NormalTransactionData_;

template <int V> requires (V < 748)
struct NormalTransactionData_<V> { using type = base::NormalTransactionData; };

template <int V> requires (V >= 748 && V < 1001)
struct NormalTransactionData_<V> { using type = v748::NormalTransactionData; };

template <int V> requires (V >= 1001 && V < 2168)
struct NormalTransactionData_<V> { using type = v1001::NormalTransactionData; };

template <int V> requires (V >= 2168 && V < 2193)
struct NormalTransactionData_<V> { using type = v2168::NormalTransactionData; };

template <int V> requires (V >= 2193)
struct NormalTransactionData_<V> { using type = v2193::NormalTransactionData; };

template <int V>
struct InventoryMismatchData_;

template <int V> requires (V < 748)
struct InventoryMismatchData_<V> { using type = base::InventoryMismatchData; };

template <int V> requires (V >= 748 && V < 1001)
struct InventoryMismatchData_<V> { using type = v748::InventoryMismatchData; };

template <int V> requires (V >= 1001 && V < 2168)
struct InventoryMismatchData_<V> { using type = v1001::InventoryMismatchData; };

template <int V> requires (V >= 2168 && V < 2193)
struct InventoryMismatchData_<V> { using type = v2168::InventoryMismatchData; };

template <int V> requires (V >= 2193)
struct InventoryMismatchData_<V> { using type = v2193::InventoryMismatchData; };

template <int V>
struct ItemUseInventoryTransaction_;

template <int V> requires (V < 748)
struct ItemUseInventoryTransaction_<V> { using type = base::ItemUseInventoryTransaction; };

template <int V> requires (V >= 748 && V < 844)
struct ItemUseInventoryTransaction_<V> { using type = v748::ItemUseInventoryTransaction; };

template <int V> requires (V >= 844 && V < 944)
struct ItemUseInventoryTransaction_<V> { using type = v844::ItemUseInventoryTransaction; };

template <int V> requires (V >= 944 && V < 1001)
struct ItemUseInventoryTransaction_<V> { using type = v944::ItemUseInventoryTransaction; };

template <int V> requires (V >= 1001 && V < 2168)
struct ItemUseInventoryTransaction_<V> { using type = v1001::ItemUseInventoryTransaction; };

template <int V> requires (V >= 2168 && V < 2193)
struct ItemUseInventoryTransaction_<V> { using type = v2168::ItemUseInventoryTransaction; };

template <int V> requires (V >= 2193)
struct ItemUseInventoryTransaction_<V> { using type = v2193::ItemUseInventoryTransaction; };

template <int V>
struct ItemUseOnActorInventoryTransaction_;

template <int V> requires (V < 748)
struct ItemUseOnActorInventoryTransaction_<V> { using type = base::ItemUseOnActorInventoryTransaction; };

template <int V> requires (V >= 748 && V < 1001)
struct ItemUseOnActorInventoryTransaction_<V> { using type = v748::ItemUseOnActorInventoryTransaction; };

template <int V> requires (V >= 1001 && V < 2168)
struct ItemUseOnActorInventoryTransaction_<V> { using type = v1001::ItemUseOnActorInventoryTransaction; };

template <int V> requires (V >= 2168 && V < 2193)
struct ItemUseOnActorInventoryTransaction_<V> { using type = v2168::ItemUseOnActorInventoryTransaction; };

template <int V> requires (V >= 2193 && V < 2225)
struct ItemUseOnActorInventoryTransaction_<V> { using type = v2193::ItemUseOnActorInventoryTransaction; };

template <int V> requires (V >= 2225)
struct ItemUseOnActorInventoryTransaction_<V> { using type = v2225::ItemUseOnActorInventoryTransaction; };

template <int V>
struct ItemReleaseInventoryTransaction_;

template <int V> requires (V < 748)
struct ItemReleaseInventoryTransaction_<V> { using type = base::ItemReleaseInventoryTransaction; };

template <int V> requires (V >= 748 && V < 1001)
struct ItemReleaseInventoryTransaction_<V> { using type = v748::ItemReleaseInventoryTransaction; };

template <int V> requires (V >= 1001 && V < 2168)
struct ItemReleaseInventoryTransaction_<V> { using type = v1001::ItemReleaseInventoryTransaction; };

template <int V> requires (V >= 2168 && V < 2193)
struct ItemReleaseInventoryTransaction_<V> { using type = v2168::ItemReleaseInventoryTransaction; };

template <int V> requires (V >= 2193 && V < 2225)
struct ItemReleaseInventoryTransaction_<V> { using type = v2193::ItemReleaseInventoryTransaction; };

template <int V> requires (V >= 2225)
struct ItemReleaseInventoryTransaction_<V> { using type = v2225::ItemReleaseInventoryTransaction; };

template <int V>
struct InventoryTransactionPacket_;

template <int V> requires (V < 748)
struct InventoryTransactionPacket_<V> { using type = base::InventoryTransactionPacket; };

template <int V> requires (V >= 748 && V < 844)
struct InventoryTransactionPacket_<V> { using type = v748::InventoryTransactionPacket; };

template <int V> requires (V >= 844 && V < 924)
struct InventoryTransactionPacket_<V> { using type = v844::InventoryTransactionPacket; };

template <int V> requires (V >= 924 && V < 944)
struct InventoryTransactionPacket_<V> { using type = v924::InventoryTransactionPacket; };

template <int V> requires (V >= 944 && V < 1001)
struct InventoryTransactionPacket_<V> { using type = v944::InventoryTransactionPacket; };

template <int V> requires (V >= 1001 && V < 2168)
struct InventoryTransactionPacket_<V> { using type = v1001::InventoryTransactionPacket; };

template <int V> requires (V >= 2168 && V < 2193)
struct InventoryTransactionPacket_<V> { using type = v2168::InventoryTransactionPacket; };

template <int V> requires (V >= 2193 && V < 2225)
struct InventoryTransactionPacket_<V> { using type = v2193::InventoryTransactionPacket; };

template <int V> requires (V >= 2225)
struct InventoryTransactionPacket_<V> { using type = v2225::InventoryTransactionPacket; };

template <int V>
struct TransactionData_;

template <int V> requires (V < 748)
struct TransactionData_<V> { using type = base::TransactionData; };

template <int V> requires (V >= 748 && V < 844)
struct TransactionData_<V> { using type = v748::TransactionData; };

template <int V> requires (V >= 844 && V < 944)
struct TransactionData_<V> { using type = v844::TransactionData; };

template <int V> requires (V >= 944 && V < 1001)
struct TransactionData_<V> { using type = v944::TransactionData; };

template <int V> requires (V >= 1001 && V < 2168)
struct TransactionData_<V> { using type = v1001::TransactionData; };

template <int V> requires (V >= 2168 && V < 2193)
struct TransactionData_<V> { using type = v2168::TransactionData; };

template <int V> requires (V >= 2193 && V < 2225)
struct TransactionData_<V> { using type = v2193::TransactionData; };

template <int V> requires (V >= 2225)
struct TransactionData_<V> { using type = v2225::TransactionData; };

}  // namespace detail

template <int V> using LegacySetSlot_ = typename detail::LegacySetSlot_<V>::type;
template <int V> using InventorySource_ = typename detail::InventorySource_<V>::type;
template <int V> using InventoryAction_ = typename detail::InventoryAction_<V>::type;
template <int V> using InventoryTransaction_ = typename detail::InventoryTransaction_<V>::type;
template <int V> using NormalTransactionData_ = typename detail::NormalTransactionData_<V>::type;
template <int V> using InventoryMismatchData_ = typename detail::InventoryMismatchData_<V>::type;
template <int V> using ItemUseInventoryTransaction_ = typename detail::ItemUseInventoryTransaction_<V>::type;
template <int V> using ItemUseOnActorInventoryTransaction_ = typename detail::ItemUseOnActorInventoryTransaction_<V>::type;
template <int V> using ItemReleaseInventoryTransaction_ = typename detail::ItemReleaseInventoryTransaction_<V>::type;
template <int V> using InventoryTransactionPacket_ = typename detail::InventoryTransactionPacket_<V>::type;
template <int V> using TransactionData_ = typename detail::TransactionData_<V>::type;

namespace legacy {

namespace detail {

template <int V>
struct ItemUseInventoryTransaction_;

template <int V> requires (V < 748)
struct ItemUseInventoryTransaction_<V> { using type = base::ItemUseInventoryTransaction; };

template <int V> requires (V >= 748 && V < 844)
struct ItemUseInventoryTransaction_<V> { using type = v748::ItemUseInventoryTransaction; };

template <int V> requires (V >= 844 && V < 944)
struct ItemUseInventoryTransaction_<V> { using type = v844::ItemUseInventoryTransaction; };

template <int V> requires (V >= 944 && V < 1001)
struct ItemUseInventoryTransaction_<V> { using type = v944::ItemUseInventoryTransaction; };

template <int V> requires (V >= 1001 && V < 2168)
struct ItemUseInventoryTransaction_<V> { using type = v1001::ItemUseInventoryTransaction; };

template <int V> requires (V >= 2168 && V < 2193)
struct ItemUseInventoryTransaction_<V> { using type = v2168::ItemUseInventoryTransaction; };

template <int V> requires (V >= 2193)
struct ItemUseInventoryTransaction_<V> { using type = v2193::ItemUseInventoryTransaction; };

}  // namespace detail

template <int V> using ItemUseInventoryTransaction_ = typename detail::ItemUseInventoryTransaction_<V>::type;

using ItemUseInventoryTransaction = ItemUseInventoryTransaction_<2225>;
}  // namespace legacy

template <int V>
struct packet_of<V, 30> { using type = InventoryTransactionPacket_<V>; };

namespace detail {

template <>
inline constexpr std::array<InventorySourceType, 6> values_v<InventorySourceType>{{
    InventorySourceType::InvalidInventory,
    InventorySourceType::ContainerInventory,
    InventorySourceType::GlobalInventory,
    InventorySourceType::WorldInteraction,
    InventorySourceType::CreativeInventory,
    InventorySourceType::NonImplementedFeatureTodo,
}};

template <>
inline constexpr std::array<std::string_view, 6> names_v<InventorySourceType>{{
    "invalidinventory",
    "containerinventory",
    "globalinventory",
    "worldinteraction",
    "creativeinventory",
    "nonimplementedfeaturetodo",
}};

template <>
inline constexpr std::string_view type_name_v<InventorySourceType>{"InventorySourceType"};

template <>
inline constexpr std::array<base::InventorySource::InventorySourceFlags, 2> values_v<base::InventorySource::InventorySourceFlags>{{
    base::InventorySource::InventorySourceFlags::NoFlag,
    base::InventorySource::InventorySourceFlags::WorldInteractionRandom,
}};

template <>
inline constexpr std::array<std::string_view, 2> names_v<base::InventorySource::InventorySourceFlags>{{
    "noflag",
    "worldinteractionrandom",
}};

template <>
inline constexpr std::string_view type_name_v<base::InventorySource::InventorySourceFlags>{"InventorySource::InventorySourceFlags"};

template <>
inline constexpr std::array<base::ItemUseInventoryTransaction::ActionType, 3> values_v<base::ItemUseInventoryTransaction::ActionType>{{
    base::ItemUseInventoryTransaction::ActionType::Place,
    base::ItemUseInventoryTransaction::ActionType::Use,
    base::ItemUseInventoryTransaction::ActionType::Destroy,
}};

template <>
inline constexpr std::array<std::string_view, 3> names_v<base::ItemUseInventoryTransaction::ActionType>{{
    "place",
    "use",
    "destroy",
}};

template <>
inline constexpr std::string_view type_name_v<base::ItemUseInventoryTransaction::ActionType>{"ItemUseInventoryTransaction::ActionType"};

template <>
inline constexpr std::array<base::ItemUseInventoryTransaction::TriggerType, 3> values_v<base::ItemUseInventoryTransaction::TriggerType>{{
    base::ItemUseInventoryTransaction::TriggerType::Unknown,
    base::ItemUseInventoryTransaction::TriggerType::PlayerInput,
    base::ItemUseInventoryTransaction::TriggerType::SimulationTick,
}};

template <>
inline constexpr std::array<std::string_view, 3> names_v<base::ItemUseInventoryTransaction::TriggerType>{{
    "unknown",
    "playerinput",
    "simulationtick",
}};

template <>
inline constexpr std::string_view type_name_v<base::ItemUseInventoryTransaction::TriggerType>{"ItemUseInventoryTransaction::TriggerType"};

template <>
inline constexpr std::array<base::ItemUseInventoryTransaction::PredictedResult, 2> values_v<base::ItemUseInventoryTransaction::PredictedResult>{{
    base::ItemUseInventoryTransaction::PredictedResult::Failure,
    base::ItemUseInventoryTransaction::PredictedResult::Success,
}};

template <>
inline constexpr std::array<std::string_view, 2> names_v<base::ItemUseInventoryTransaction::PredictedResult>{{
    "failure",
    "success",
}};

template <>
inline constexpr std::string_view type_name_v<base::ItemUseInventoryTransaction::PredictedResult>{"ItemUseInventoryTransaction::PredictedResult"};

template <>
inline constexpr std::array<base::ItemUseInventoryTransaction::ClientCooldownState, 2> values_v<base::ItemUseInventoryTransaction::ClientCooldownState>{{
    base::ItemUseInventoryTransaction::ClientCooldownState::Off,
    base::ItemUseInventoryTransaction::ClientCooldownState::On,
}};

template <>
inline constexpr std::array<std::string_view, 2> names_v<base::ItemUseInventoryTransaction::ClientCooldownState>{{
    "off",
    "on",
}};

template <>
inline constexpr std::string_view type_name_v<base::ItemUseInventoryTransaction::ClientCooldownState>{"ItemUseInventoryTransaction::ClientCooldownState"};

template <>
inline constexpr std::array<v748::ItemUseInventoryTransaction::ActionType, 3> values_v<v748::ItemUseInventoryTransaction::ActionType>{{
    v748::ItemUseInventoryTransaction::ActionType::Place,
    v748::ItemUseInventoryTransaction::ActionType::Use,
    v748::ItemUseInventoryTransaction::ActionType::Destroy,
}};

template <>
inline constexpr std::array<std::string_view, 3> names_v<v748::ItemUseInventoryTransaction::ActionType>{{
    "place",
    "use",
    "destroy",
}};

template <>
inline constexpr std::string_view type_name_v<v748::ItemUseInventoryTransaction::ActionType>{"ItemUseInventoryTransaction::ActionType"};

template <>
inline constexpr std::array<v844::ItemUseInventoryTransaction::ActionType, 4> values_v<v844::ItemUseInventoryTransaction::ActionType>{{
    v844::ItemUseInventoryTransaction::ActionType::Place,
    v844::ItemUseInventoryTransaction::ActionType::Use,
    v844::ItemUseInventoryTransaction::ActionType::Destroy,
    v844::ItemUseInventoryTransaction::ActionType::UseAsAttack,
}};

template <>
inline constexpr std::array<std::string_view, 4> names_v<v844::ItemUseInventoryTransaction::ActionType>{{
    "place",
    "use",
    "destroy",
    "useasattack",
}};

template <>
inline constexpr std::string_view type_name_v<v844::ItemUseInventoryTransaction::ActionType>{"ItemUseInventoryTransaction::ActionType"};

template <>
inline constexpr std::array<v944::ItemUseInventoryTransaction::ActionType, 4> values_v<v944::ItemUseInventoryTransaction::ActionType>{{
    v944::ItemUseInventoryTransaction::ActionType::Place,
    v944::ItemUseInventoryTransaction::ActionType::Use,
    v944::ItemUseInventoryTransaction::ActionType::Destroy,
    v944::ItemUseInventoryTransaction::ActionType::UseAsAttack,
}};

template <>
inline constexpr std::array<std::string_view, 4> names_v<v944::ItemUseInventoryTransaction::ActionType>{{
    "place",
    "use",
    "destroy",
    "useasattack",
}};

template <>
inline constexpr std::string_view type_name_v<v944::ItemUseInventoryTransaction::ActionType>{"ItemUseInventoryTransaction::ActionType"};

template <>
inline constexpr std::array<v1001::ItemUseInventoryTransaction::ActionType, 4> values_v<v1001::ItemUseInventoryTransaction::ActionType>{{
    v1001::ItemUseInventoryTransaction::ActionType::Place,
    v1001::ItemUseInventoryTransaction::ActionType::Use,
    v1001::ItemUseInventoryTransaction::ActionType::Destroy,
    v1001::ItemUseInventoryTransaction::ActionType::UseAsAttack,
}};

template <>
inline constexpr std::array<std::string_view, 4> names_v<v1001::ItemUseInventoryTransaction::ActionType>{{
    "place",
    "use",
    "destroy",
    "useasattack",
}};

template <>
inline constexpr std::string_view type_name_v<v1001::ItemUseInventoryTransaction::ActionType>{"ItemUseInventoryTransaction::ActionType"};

template <>
inline constexpr std::array<v2168::ItemUseInventoryTransaction::ActionType, 4> values_v<v2168::ItemUseInventoryTransaction::ActionType>{{
    v2168::ItemUseInventoryTransaction::ActionType::Place,
    v2168::ItemUseInventoryTransaction::ActionType::Use,
    v2168::ItemUseInventoryTransaction::ActionType::Destroy,
    v2168::ItemUseInventoryTransaction::ActionType::UseAsAttack,
}};

template <>
inline constexpr std::array<std::string_view, 4> names_v<v2168::ItemUseInventoryTransaction::ActionType>{{
    "place",
    "use",
    "destroy",
    "useasattack",
}};

template <>
inline constexpr std::string_view type_name_v<v2168::ItemUseInventoryTransaction::ActionType>{"ItemUseInventoryTransaction::ActionType"};

template <>
inline constexpr std::array<v2193::ItemUseInventoryTransaction::ActionType, 4> values_v<v2193::ItemUseInventoryTransaction::ActionType>{{
    v2193::ItemUseInventoryTransaction::ActionType::Place,
    v2193::ItemUseInventoryTransaction::ActionType::Use,
    v2193::ItemUseInventoryTransaction::ActionType::Destroy,
    v2193::ItemUseInventoryTransaction::ActionType::UseAsAttack,
}};

template <>
inline constexpr std::array<std::string_view, 4> names_v<v2193::ItemUseInventoryTransaction::ActionType>{{
    "place",
    "use",
    "destroy",
    "useasattack",
}};

template <>
inline constexpr std::string_view type_name_v<v2193::ItemUseInventoryTransaction::ActionType>{"ItemUseInventoryTransaction::ActionType"};

template <>
inline constexpr std::array<base::ItemUseOnActorInventoryTransaction::ActionType, 3> values_v<base::ItemUseOnActorInventoryTransaction::ActionType>{{
    base::ItemUseOnActorInventoryTransaction::ActionType::Interact,
    base::ItemUseOnActorInventoryTransaction::ActionType::Attack,
    base::ItemUseOnActorInventoryTransaction::ActionType::ItemInteract,
}};

template <>
inline constexpr std::array<std::string_view, 3> names_v<base::ItemUseOnActorInventoryTransaction::ActionType>{{
    "interact",
    "attack",
    "iteminteract",
}};

template <>
inline constexpr std::string_view type_name_v<base::ItemUseOnActorInventoryTransaction::ActionType>{"ItemUseOnActorInventoryTransaction::ActionType"};

template <>
inline constexpr std::array<base::ItemReleaseInventoryTransaction::ActionType, 2> values_v<base::ItemReleaseInventoryTransaction::ActionType>{{
    base::ItemReleaseInventoryTransaction::ActionType::Release,
    base::ItemReleaseInventoryTransaction::ActionType::Use,
}};

template <>
inline constexpr std::array<std::string_view, 2> names_v<base::ItemReleaseInventoryTransaction::ActionType>{{
    "release",
    "use",
}};

template <>
inline constexpr std::string_view type_name_v<base::ItemReleaseInventoryTransaction::ActionType>{"ItemReleaseInventoryTransaction::ActionType"};

}  // namespace detail

namespace detail {

template <>
inline constexpr bool is_reflected_struct_v<base::LegacySetSlot> = true;

template <>
inline constexpr std::string_view struct_name_v<base::LegacySetSlot>{"LegacySetSlot"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<base::LegacySetSlot>{{
    "container_enum",
    "slots",
}};

template <>
struct field_accessor<base::LegacySetSlot> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.container_enum;
        }
        else {
            return value.slots;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::LegacySetSlot> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::LegacySetSlot>{"LegacySetSlot"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v924::LegacySetSlot>{{
    "container_enum",
    "slots",
}};

template <>
struct field_accessor<v924::LegacySetSlot> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.container_enum;
        }
        else {
            return value.slots;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::LegacySetSlot> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::LegacySetSlot>{"LegacySetSlot"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2225::LegacySetSlot>{{
    "container_enum",
    "slots",
}};

template <>
struct field_accessor<v2225::LegacySetSlot> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.container_enum;
        }
        else {
            return value.slots;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::InventorySource> = true;

template <>
inline constexpr std::string_view struct_name_v<base::InventorySource>{"InventorySource"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<base::InventorySource>{{
    "type",
    "container_id",
    "flags",
}};

template <>
struct field_accessor<base::InventorySource> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.type;
        }
        else if constexpr (I == 1) {
            return value.container_id;
        }
        else {
            return value.flags;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v748::InventorySource> = true;

template <>
inline constexpr std::string_view struct_name_v<v748::InventorySource>{"InventorySource"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v748::InventorySource>{{
    "type",
    "container_id",
    "flags",
}};

template <>
struct field_accessor<v748::InventorySource> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.type;
        }
        else if constexpr (I == 1) {
            return value.container_id;
        }
        else {
            return value.flags;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::InventorySource> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::InventorySource>{"InventorySource"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v1001::InventorySource>{{
    "type",
    "container_id",
    "flags",
}};

template <>
struct field_accessor<v1001::InventorySource> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.type;
        }
        else if constexpr (I == 1) {
            return value.container_id;
        }
        else {
            return value.flags;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2193::InventorySource> = true;

template <>
inline constexpr std::string_view struct_name_v<v2193::InventorySource>{"InventorySource"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v2193::InventorySource>{{
    "type",
    "container_id",
    "flags",
}};

template <>
struct field_accessor<v2193::InventorySource> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.type;
        }
        else if constexpr (I == 1) {
            return value.container_id;
        }
        else {
            return value.flags;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::InventoryAction> = true;

template <>
inline constexpr std::string_view struct_name_v<base::InventoryAction>{"InventoryAction"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<base::InventoryAction>{{
    "source",
    "slot",
    "from_item_descriptor",
    "to_item_descriptor",
}};

template <>
struct field_accessor<base::InventoryAction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.source;
        }
        else if constexpr (I == 1) {
            return value.slot;
        }
        else if constexpr (I == 2) {
            return value.from_item_descriptor;
        }
        else {
            return value.to_item_descriptor;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v748::InventoryAction> = true;

template <>
inline constexpr std::string_view struct_name_v<v748::InventoryAction>{"InventoryAction"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v748::InventoryAction>{{
    "source",
    "slot",
    "from_item_descriptor",
    "to_item_descriptor",
}};

template <>
struct field_accessor<v748::InventoryAction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.source;
        }
        else if constexpr (I == 1) {
            return value.slot;
        }
        else if constexpr (I == 2) {
            return value.from_item_descriptor;
        }
        else {
            return value.to_item_descriptor;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::InventoryAction> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::InventoryAction>{"InventoryAction"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v1001::InventoryAction>{{
    "source",
    "slot",
    "from_item_descriptor",
    "to_item_descriptor",
}};

template <>
struct field_accessor<v1001::InventoryAction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.source;
        }
        else if constexpr (I == 1) {
            return value.slot;
        }
        else if constexpr (I == 2) {
            return value.from_item_descriptor;
        }
        else {
            return value.to_item_descriptor;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::InventoryAction> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::InventoryAction>{"InventoryAction"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v2168::InventoryAction>{{
    "source",
    "slot",
    "from_item_descriptor",
    "to_item_descriptor",
}};

template <>
struct field_accessor<v2168::InventoryAction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.source;
        }
        else if constexpr (I == 1) {
            return value.slot;
        }
        else if constexpr (I == 2) {
            return value.from_item_descriptor;
        }
        else {
            return value.to_item_descriptor;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2193::InventoryAction> = true;

template <>
inline constexpr std::string_view struct_name_v<v2193::InventoryAction>{"InventoryAction"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v2193::InventoryAction>{{
    "source",
    "slot",
    "from_item_descriptor",
    "to_item_descriptor",
}};

template <>
struct field_accessor<v2193::InventoryAction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.source;
        }
        else if constexpr (I == 1) {
            return value.slot;
        }
        else if constexpr (I == 2) {
            return value.from_item_descriptor;
        }
        else {
            return value.to_item_descriptor;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::InventoryTransaction> = true;

template <>
inline constexpr std::string_view struct_name_v<base::InventoryTransaction>{"InventoryTransaction"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::InventoryTransaction>{{
    "actions",
}};

template <>
struct field_accessor<base::InventoryTransaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.actions;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v748::InventoryTransaction> = true;

template <>
inline constexpr std::string_view struct_name_v<v748::InventoryTransaction>{"InventoryTransaction"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v748::InventoryTransaction>{{
    "actions",
}};

template <>
struct field_accessor<v748::InventoryTransaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.actions;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::InventoryTransaction> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::InventoryTransaction>{"InventoryTransaction"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v1001::InventoryTransaction>{{
    "actions",
}};

template <>
struct field_accessor<v1001::InventoryTransaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.actions;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::InventoryTransaction> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::InventoryTransaction>{"InventoryTransaction"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2168::InventoryTransaction>{{
    "actions",
}};

template <>
struct field_accessor<v2168::InventoryTransaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.actions;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2193::InventoryTransaction> = true;

template <>
inline constexpr std::string_view struct_name_v<v2193::InventoryTransaction>{"InventoryTransaction"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2193::InventoryTransaction>{{
    "actions",
}};

template <>
struct field_accessor<v2193::InventoryTransaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.actions;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::NormalTransactionData> = true;

template <>
inline constexpr std::string_view struct_name_v<base::NormalTransactionData>{"NormalTransactionData"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::NormalTransactionData>{{
    "transaction",
}};

template <>
struct field_accessor<base::NormalTransactionData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.transaction;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v748::NormalTransactionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v748::NormalTransactionData>{"NormalTransactionData"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v748::NormalTransactionData>{{
    "transaction",
}};

template <>
struct field_accessor<v748::NormalTransactionData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.transaction;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::NormalTransactionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::NormalTransactionData>{"NormalTransactionData"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v1001::NormalTransactionData>{{
    "transaction",
}};

template <>
struct field_accessor<v1001::NormalTransactionData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.transaction;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::NormalTransactionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::NormalTransactionData>{"NormalTransactionData"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2168::NormalTransactionData>{{
    "transaction",
}};

template <>
struct field_accessor<v2168::NormalTransactionData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.transaction;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2193::NormalTransactionData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2193::NormalTransactionData>{"NormalTransactionData"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2193::NormalTransactionData>{{
    "transaction",
}};

template <>
struct field_accessor<v2193::NormalTransactionData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.transaction;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::InventoryMismatchData> = true;

template <>
inline constexpr std::string_view struct_name_v<base::InventoryMismatchData>{"InventoryMismatchData"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::InventoryMismatchData>{{
    "transaction",
}};

template <>
struct field_accessor<base::InventoryMismatchData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.transaction;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v748::InventoryMismatchData> = true;

template <>
inline constexpr std::string_view struct_name_v<v748::InventoryMismatchData>{"InventoryMismatchData"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v748::InventoryMismatchData>{{
    "transaction",
}};

template <>
struct field_accessor<v748::InventoryMismatchData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.transaction;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::InventoryMismatchData> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::InventoryMismatchData>{"InventoryMismatchData"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v1001::InventoryMismatchData>{{
    "transaction",
}};

template <>
struct field_accessor<v1001::InventoryMismatchData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.transaction;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::InventoryMismatchData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::InventoryMismatchData>{"InventoryMismatchData"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2168::InventoryMismatchData>{{
    "transaction",
}};

template <>
struct field_accessor<v2168::InventoryMismatchData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.transaction;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2193::InventoryMismatchData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2193::InventoryMismatchData>{"InventoryMismatchData"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2193::InventoryMismatchData>{{
    "transaction",
}};

template <>
struct field_accessor<v2193::InventoryMismatchData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.transaction;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::ItemUseInventoryTransaction> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ItemUseInventoryTransaction>{"ItemUseInventoryTransaction"};

template <>
inline constexpr std::array<std::string_view, 11> field_names_v<base::ItemUseInventoryTransaction>{{
    "transaction",
    "action_type",
    "trigger_type",
    "pos",
    "face",
    "slot",
    "item",
    "from_pos",
    "click_pos",
    "target_block_id",
    "client_predicted_result",
}};

template <>
struct field_accessor<base::ItemUseInventoryTransaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.transaction;
        }
        else if constexpr (I == 1) {
            return value.action_type;
        }
        else if constexpr (I == 2) {
            return value.trigger_type;
        }
        else if constexpr (I == 3) {
            return value.pos;
        }
        else if constexpr (I == 4) {
            return value.face;
        }
        else if constexpr (I == 5) {
            return value.slot;
        }
        else if constexpr (I == 6) {
            return value.item;
        }
        else if constexpr (I == 7) {
            return value.from_pos;
        }
        else if constexpr (I == 8) {
            return value.click_pos;
        }
        else if constexpr (I == 9) {
            return value.target_block_id;
        }
        else {
            return value.client_predicted_result;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v748::ItemUseInventoryTransaction> = true;

template <>
inline constexpr std::string_view struct_name_v<v748::ItemUseInventoryTransaction>{"ItemUseInventoryTransaction"};

template <>
inline constexpr std::array<std::string_view, 11> field_names_v<v748::ItemUseInventoryTransaction>{{
    "transaction",
    "action_type",
    "trigger_type",
    "pos",
    "face",
    "slot",
    "item",
    "from_pos",
    "click_pos",
    "target_block_id",
    "client_predicted_result",
}};

template <>
struct field_accessor<v748::ItemUseInventoryTransaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.transaction;
        }
        else if constexpr (I == 1) {
            return value.action_type;
        }
        else if constexpr (I == 2) {
            return value.trigger_type;
        }
        else if constexpr (I == 3) {
            return value.pos;
        }
        else if constexpr (I == 4) {
            return value.face;
        }
        else if constexpr (I == 5) {
            return value.slot;
        }
        else if constexpr (I == 6) {
            return value.item;
        }
        else if constexpr (I == 7) {
            return value.from_pos;
        }
        else if constexpr (I == 8) {
            return value.click_pos;
        }
        else if constexpr (I == 9) {
            return value.target_block_id;
        }
        else {
            return value.client_predicted_result;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v844::ItemUseInventoryTransaction> = true;

template <>
inline constexpr std::string_view struct_name_v<v844::ItemUseInventoryTransaction>{"ItemUseInventoryTransaction"};

template <>
inline constexpr std::array<std::string_view, 11> field_names_v<v844::ItemUseInventoryTransaction>{{
    "transaction",
    "action_type",
    "trigger_type",
    "pos",
    "face",
    "slot",
    "item",
    "from_pos",
    "click_pos",
    "target_block_id",
    "client_predicted_result",
}};

template <>
struct field_accessor<v844::ItemUseInventoryTransaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.transaction;
        }
        else if constexpr (I == 1) {
            return value.action_type;
        }
        else if constexpr (I == 2) {
            return value.trigger_type;
        }
        else if constexpr (I == 3) {
            return value.pos;
        }
        else if constexpr (I == 4) {
            return value.face;
        }
        else if constexpr (I == 5) {
            return value.slot;
        }
        else if constexpr (I == 6) {
            return value.item;
        }
        else if constexpr (I == 7) {
            return value.from_pos;
        }
        else if constexpr (I == 8) {
            return value.click_pos;
        }
        else if constexpr (I == 9) {
            return value.target_block_id;
        }
        else {
            return value.client_predicted_result;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::ItemUseInventoryTransaction> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::ItemUseInventoryTransaction>{"ItemUseInventoryTransaction"};

template <>
inline constexpr std::array<std::string_view, 12> field_names_v<v944::ItemUseInventoryTransaction>{{
    "transaction",
    "action_type",
    "trigger_type",
    "pos",
    "face",
    "slot",
    "item",
    "from_pos",
    "click_pos",
    "target_block_id",
    "client_predicted_result",
    "client_cooldown_state",
}};

template <>
struct field_accessor<v944::ItemUseInventoryTransaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.transaction;
        }
        else if constexpr (I == 1) {
            return value.action_type;
        }
        else if constexpr (I == 2) {
            return value.trigger_type;
        }
        else if constexpr (I == 3) {
            return value.pos;
        }
        else if constexpr (I == 4) {
            return value.face;
        }
        else if constexpr (I == 5) {
            return value.slot;
        }
        else if constexpr (I == 6) {
            return value.item;
        }
        else if constexpr (I == 7) {
            return value.from_pos;
        }
        else if constexpr (I == 8) {
            return value.click_pos;
        }
        else if constexpr (I == 9) {
            return value.target_block_id;
        }
        else if constexpr (I == 10) {
            return value.client_predicted_result;
        }
        else {
            return value.client_cooldown_state;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::ItemUseInventoryTransaction> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::ItemUseInventoryTransaction>{"ItemUseInventoryTransaction"};

template <>
inline constexpr std::array<std::string_view, 12> field_names_v<v1001::ItemUseInventoryTransaction>{{
    "transaction",
    "action_type",
    "trigger_type",
    "pos",
    "face",
    "slot",
    "item",
    "from_pos",
    "click_pos",
    "target_block_id",
    "client_predicted_result",
    "client_cooldown_state",
}};

template <>
struct field_accessor<v1001::ItemUseInventoryTransaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.transaction;
        }
        else if constexpr (I == 1) {
            return value.action_type;
        }
        else if constexpr (I == 2) {
            return value.trigger_type;
        }
        else if constexpr (I == 3) {
            return value.pos;
        }
        else if constexpr (I == 4) {
            return value.face;
        }
        else if constexpr (I == 5) {
            return value.slot;
        }
        else if constexpr (I == 6) {
            return value.item;
        }
        else if constexpr (I == 7) {
            return value.from_pos;
        }
        else if constexpr (I == 8) {
            return value.click_pos;
        }
        else if constexpr (I == 9) {
            return value.target_block_id;
        }
        else if constexpr (I == 10) {
            return value.client_predicted_result;
        }
        else {
            return value.client_cooldown_state;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ItemUseInventoryTransaction> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ItemUseInventoryTransaction>{"ItemUseInventoryTransaction"};

template <>
inline constexpr std::array<std::string_view, 12> field_names_v<v2168::ItemUseInventoryTransaction>{{
    "transaction",
    "action_type",
    "trigger_type",
    "pos",
    "face",
    "slot",
    "item",
    "from_pos",
    "click_pos",
    "target_block_id",
    "client_predicted_result",
    "client_cooldown_state",
}};

template <>
struct field_accessor<v2168::ItemUseInventoryTransaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.transaction;
        }
        else if constexpr (I == 1) {
            return value.action_type;
        }
        else if constexpr (I == 2) {
            return value.trigger_type;
        }
        else if constexpr (I == 3) {
            return value.pos;
        }
        else if constexpr (I == 4) {
            return value.face;
        }
        else if constexpr (I == 5) {
            return value.slot;
        }
        else if constexpr (I == 6) {
            return value.item;
        }
        else if constexpr (I == 7) {
            return value.from_pos;
        }
        else if constexpr (I == 8) {
            return value.click_pos;
        }
        else if constexpr (I == 9) {
            return value.target_block_id;
        }
        else if constexpr (I == 10) {
            return value.client_predicted_result;
        }
        else {
            return value.client_cooldown_state;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2193::ItemUseInventoryTransaction> = true;

template <>
inline constexpr std::string_view struct_name_v<v2193::ItemUseInventoryTransaction>{"ItemUseInventoryTransaction"};

template <>
inline constexpr std::array<std::string_view, 13> field_names_v<v2193::ItemUseInventoryTransaction>{{
    "transaction",
    "action_type",
    "trigger_type",
    "pos",
    "face",
    "slot",
    "hand",
    "item",
    "from_pos",
    "click_pos",
    "target_block_id",
    "client_predicted_result",
    "client_cooldown_state",
}};

template <>
struct field_accessor<v2193::ItemUseInventoryTransaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.transaction;
        }
        else if constexpr (I == 1) {
            return value.action_type;
        }
        else if constexpr (I == 2) {
            return value.trigger_type;
        }
        else if constexpr (I == 3) {
            return value.pos;
        }
        else if constexpr (I == 4) {
            return value.face;
        }
        else if constexpr (I == 5) {
            return value.slot;
        }
        else if constexpr (I == 6) {
            return value.hand;
        }
        else if constexpr (I == 7) {
            return value.item;
        }
        else if constexpr (I == 8) {
            return value.from_pos;
        }
        else if constexpr (I == 9) {
            return value.click_pos;
        }
        else if constexpr (I == 10) {
            return value.target_block_id;
        }
        else if constexpr (I == 11) {
            return value.client_predicted_result;
        }
        else {
            return value.client_cooldown_state;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<legacy::base::ItemUseInventoryTransaction> = true;

template <>
inline constexpr std::string_view struct_name_v<legacy::base::ItemUseInventoryTransaction>{"ItemUseInventoryTransaction"};

template <>
inline constexpr std::array<std::string_view, 11> field_names_v<legacy::base::ItemUseInventoryTransaction>{{
    "actions",
    "action_type",
    "trigger_type",
    "pos",
    "face",
    "slot",
    "item",
    "from_pos",
    "click_pos",
    "target_block_id",
    "client_predicted_result",
}};

template <>
struct field_accessor<legacy::base::ItemUseInventoryTransaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.actions;
        }
        else if constexpr (I == 1) {
            return value.action_type;
        }
        else if constexpr (I == 2) {
            return value.trigger_type;
        }
        else if constexpr (I == 3) {
            return value.pos;
        }
        else if constexpr (I == 4) {
            return value.face;
        }
        else if constexpr (I == 5) {
            return value.slot;
        }
        else if constexpr (I == 6) {
            return value.item;
        }
        else if constexpr (I == 7) {
            return value.from_pos;
        }
        else if constexpr (I == 8) {
            return value.click_pos;
        }
        else if constexpr (I == 9) {
            return value.target_block_id;
        }
        else {
            return value.client_predicted_result;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<legacy::v748::ItemUseInventoryTransaction> = true;

template <>
inline constexpr std::string_view struct_name_v<legacy::v748::ItemUseInventoryTransaction>{"ItemUseInventoryTransaction"};

template <>
inline constexpr std::array<std::string_view, 11> field_names_v<legacy::v748::ItemUseInventoryTransaction>{{
    "actions",
    "action_type",
    "trigger_type",
    "pos",
    "face",
    "slot",
    "item",
    "from_pos",
    "click_pos",
    "target_block_id",
    "client_predicted_result",
}};

template <>
struct field_accessor<legacy::v748::ItemUseInventoryTransaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.actions;
        }
        else if constexpr (I == 1) {
            return value.action_type;
        }
        else if constexpr (I == 2) {
            return value.trigger_type;
        }
        else if constexpr (I == 3) {
            return value.pos;
        }
        else if constexpr (I == 4) {
            return value.face;
        }
        else if constexpr (I == 5) {
            return value.slot;
        }
        else if constexpr (I == 6) {
            return value.item;
        }
        else if constexpr (I == 7) {
            return value.from_pos;
        }
        else if constexpr (I == 8) {
            return value.click_pos;
        }
        else if constexpr (I == 9) {
            return value.target_block_id;
        }
        else {
            return value.client_predicted_result;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<legacy::v844::ItemUseInventoryTransaction> = true;

template <>
inline constexpr std::string_view struct_name_v<legacy::v844::ItemUseInventoryTransaction>{"ItemUseInventoryTransaction"};

template <>
inline constexpr std::array<std::string_view, 11> field_names_v<legacy::v844::ItemUseInventoryTransaction>{{
    "actions",
    "action_type",
    "trigger_type",
    "pos",
    "face",
    "slot",
    "item",
    "from_pos",
    "click_pos",
    "target_block_id",
    "client_predicted_result",
}};

template <>
struct field_accessor<legacy::v844::ItemUseInventoryTransaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.actions;
        }
        else if constexpr (I == 1) {
            return value.action_type;
        }
        else if constexpr (I == 2) {
            return value.trigger_type;
        }
        else if constexpr (I == 3) {
            return value.pos;
        }
        else if constexpr (I == 4) {
            return value.face;
        }
        else if constexpr (I == 5) {
            return value.slot;
        }
        else if constexpr (I == 6) {
            return value.item;
        }
        else if constexpr (I == 7) {
            return value.from_pos;
        }
        else if constexpr (I == 8) {
            return value.click_pos;
        }
        else if constexpr (I == 9) {
            return value.target_block_id;
        }
        else {
            return value.client_predicted_result;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<legacy::v944::ItemUseInventoryTransaction> = true;

template <>
inline constexpr std::string_view struct_name_v<legacy::v944::ItemUseInventoryTransaction>{"ItemUseInventoryTransaction"};

template <>
inline constexpr std::array<std::string_view, 12> field_names_v<legacy::v944::ItemUseInventoryTransaction>{{
    "actions",
    "action_type",
    "trigger_type",
    "pos",
    "face",
    "slot",
    "item",
    "from_pos",
    "click_pos",
    "target_block_id",
    "client_predicted_result",
    "client_cooldown_state",
}};

template <>
struct field_accessor<legacy::v944::ItemUseInventoryTransaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.actions;
        }
        else if constexpr (I == 1) {
            return value.action_type;
        }
        else if constexpr (I == 2) {
            return value.trigger_type;
        }
        else if constexpr (I == 3) {
            return value.pos;
        }
        else if constexpr (I == 4) {
            return value.face;
        }
        else if constexpr (I == 5) {
            return value.slot;
        }
        else if constexpr (I == 6) {
            return value.item;
        }
        else if constexpr (I == 7) {
            return value.from_pos;
        }
        else if constexpr (I == 8) {
            return value.click_pos;
        }
        else if constexpr (I == 9) {
            return value.target_block_id;
        }
        else if constexpr (I == 10) {
            return value.client_predicted_result;
        }
        else {
            return value.client_cooldown_state;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<legacy::v1001::ItemUseInventoryTransaction> = true;

template <>
inline constexpr std::string_view struct_name_v<legacy::v1001::ItemUseInventoryTransaction>{"ItemUseInventoryTransaction"};

template <>
inline constexpr std::array<std::string_view, 12> field_names_v<legacy::v1001::ItemUseInventoryTransaction>{{
    "actions",
    "action_type",
    "trigger_type",
    "pos",
    "face",
    "slot",
    "item",
    "from_pos",
    "click_pos",
    "target_block_id",
    "client_predicted_result",
    "client_cooldown_state",
}};

template <>
struct field_accessor<legacy::v1001::ItemUseInventoryTransaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.actions;
        }
        else if constexpr (I == 1) {
            return value.action_type;
        }
        else if constexpr (I == 2) {
            return value.trigger_type;
        }
        else if constexpr (I == 3) {
            return value.pos;
        }
        else if constexpr (I == 4) {
            return value.face;
        }
        else if constexpr (I == 5) {
            return value.slot;
        }
        else if constexpr (I == 6) {
            return value.item;
        }
        else if constexpr (I == 7) {
            return value.from_pos;
        }
        else if constexpr (I == 8) {
            return value.click_pos;
        }
        else if constexpr (I == 9) {
            return value.target_block_id;
        }
        else if constexpr (I == 10) {
            return value.client_predicted_result;
        }
        else {
            return value.client_cooldown_state;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<legacy::v2168::ItemUseInventoryTransaction> = true;

template <>
inline constexpr std::string_view struct_name_v<legacy::v2168::ItemUseInventoryTransaction>{"ItemUseInventoryTransaction"};

template <>
inline constexpr std::array<std::string_view, 12> field_names_v<legacy::v2168::ItemUseInventoryTransaction>{{
    "actions",
    "action_type",
    "trigger_type",
    "pos",
    "face",
    "slot",
    "item",
    "from_pos",
    "click_pos",
    "target_block_id",
    "client_predicted_result",
    "client_cooldown_state",
}};

template <>
struct field_accessor<legacy::v2168::ItemUseInventoryTransaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.actions;
        }
        else if constexpr (I == 1) {
            return value.action_type;
        }
        else if constexpr (I == 2) {
            return value.trigger_type;
        }
        else if constexpr (I == 3) {
            return value.pos;
        }
        else if constexpr (I == 4) {
            return value.face;
        }
        else if constexpr (I == 5) {
            return value.slot;
        }
        else if constexpr (I == 6) {
            return value.item;
        }
        else if constexpr (I == 7) {
            return value.from_pos;
        }
        else if constexpr (I == 8) {
            return value.click_pos;
        }
        else if constexpr (I == 9) {
            return value.target_block_id;
        }
        else if constexpr (I == 10) {
            return value.client_predicted_result;
        }
        else {
            return value.client_cooldown_state;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<legacy::v2193::ItemUseInventoryTransaction> = true;

template <>
inline constexpr std::string_view struct_name_v<legacy::v2193::ItemUseInventoryTransaction>{"ItemUseInventoryTransaction"};

template <>
inline constexpr std::array<std::string_view, 12> field_names_v<legacy::v2193::ItemUseInventoryTransaction>{{
    "actions",
    "action_type",
    "trigger_type",
    "pos",
    "face",
    "slot",
    "item",
    "from_pos",
    "click_pos",
    "target_block_id",
    "client_predicted_result",
    "client_cooldown_state",
}};

template <>
struct field_accessor<legacy::v2193::ItemUseInventoryTransaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.actions;
        }
        else if constexpr (I == 1) {
            return value.action_type;
        }
        else if constexpr (I == 2) {
            return value.trigger_type;
        }
        else if constexpr (I == 3) {
            return value.pos;
        }
        else if constexpr (I == 4) {
            return value.face;
        }
        else if constexpr (I == 5) {
            return value.slot;
        }
        else if constexpr (I == 6) {
            return value.item;
        }
        else if constexpr (I == 7) {
            return value.from_pos;
        }
        else if constexpr (I == 8) {
            return value.click_pos;
        }
        else if constexpr (I == 9) {
            return value.target_block_id;
        }
        else if constexpr (I == 10) {
            return value.client_predicted_result;
        }
        else {
            return value.client_cooldown_state;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::ItemUseOnActorInventoryTransaction> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ItemUseOnActorInventoryTransaction>{"ItemUseOnActorInventoryTransaction"};

template <>
inline constexpr std::array<std::string_view, 7> field_names_v<base::ItemUseOnActorInventoryTransaction>{{
    "transaction",
    "runtime_id",
    "action_type",
    "slot",
    "item",
    "from_pos",
    "hit_pos",
}};

template <>
struct field_accessor<base::ItemUseOnActorInventoryTransaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.transaction;
        }
        else if constexpr (I == 1) {
            return value.runtime_id;
        }
        else if constexpr (I == 2) {
            return value.action_type;
        }
        else if constexpr (I == 3) {
            return value.slot;
        }
        else if constexpr (I == 4) {
            return value.item;
        }
        else if constexpr (I == 5) {
            return value.from_pos;
        }
        else {
            return value.hit_pos;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v748::ItemUseOnActorInventoryTransaction> = true;

template <>
inline constexpr std::string_view struct_name_v<v748::ItemUseOnActorInventoryTransaction>{"ItemUseOnActorInventoryTransaction"};

template <>
inline constexpr std::array<std::string_view, 7> field_names_v<v748::ItemUseOnActorInventoryTransaction>{{
    "transaction",
    "runtime_id",
    "action_type",
    "slot",
    "item",
    "from_pos",
    "hit_pos",
}};

template <>
struct field_accessor<v748::ItemUseOnActorInventoryTransaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.transaction;
        }
        else if constexpr (I == 1) {
            return value.runtime_id;
        }
        else if constexpr (I == 2) {
            return value.action_type;
        }
        else if constexpr (I == 3) {
            return value.slot;
        }
        else if constexpr (I == 4) {
            return value.item;
        }
        else if constexpr (I == 5) {
            return value.from_pos;
        }
        else {
            return value.hit_pos;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::ItemUseOnActorInventoryTransaction> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::ItemUseOnActorInventoryTransaction>{"ItemUseOnActorInventoryTransaction"};

template <>
inline constexpr std::array<std::string_view, 7> field_names_v<v1001::ItemUseOnActorInventoryTransaction>{{
    "transaction",
    "runtime_id",
    "action_type",
    "slot",
    "item",
    "from_pos",
    "hit_pos",
}};

template <>
struct field_accessor<v1001::ItemUseOnActorInventoryTransaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.transaction;
        }
        else if constexpr (I == 1) {
            return value.runtime_id;
        }
        else if constexpr (I == 2) {
            return value.action_type;
        }
        else if constexpr (I == 3) {
            return value.slot;
        }
        else if constexpr (I == 4) {
            return value.item;
        }
        else if constexpr (I == 5) {
            return value.from_pos;
        }
        else {
            return value.hit_pos;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ItemUseOnActorInventoryTransaction> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ItemUseOnActorInventoryTransaction>{"ItemUseOnActorInventoryTransaction"};

template <>
inline constexpr std::array<std::string_view, 7> field_names_v<v2168::ItemUseOnActorInventoryTransaction>{{
    "transaction",
    "runtime_id",
    "action_type",
    "slot",
    "item",
    "from_pos",
    "hit_pos",
}};

template <>
struct field_accessor<v2168::ItemUseOnActorInventoryTransaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.transaction;
        }
        else if constexpr (I == 1) {
            return value.runtime_id;
        }
        else if constexpr (I == 2) {
            return value.action_type;
        }
        else if constexpr (I == 3) {
            return value.slot;
        }
        else if constexpr (I == 4) {
            return value.item;
        }
        else if constexpr (I == 5) {
            return value.from_pos;
        }
        else {
            return value.hit_pos;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2193::ItemUseOnActorInventoryTransaction> = true;

template <>
inline constexpr std::string_view struct_name_v<v2193::ItemUseOnActorInventoryTransaction>{"ItemUseOnActorInventoryTransaction"};

template <>
inline constexpr std::array<std::string_view, 7> field_names_v<v2193::ItemUseOnActorInventoryTransaction>{{
    "transaction",
    "runtime_id",
    "action_type",
    "slot",
    "item",
    "from_pos",
    "hit_pos",
}};

template <>
struct field_accessor<v2193::ItemUseOnActorInventoryTransaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.transaction;
        }
        else if constexpr (I == 1) {
            return value.runtime_id;
        }
        else if constexpr (I == 2) {
            return value.action_type;
        }
        else if constexpr (I == 3) {
            return value.slot;
        }
        else if constexpr (I == 4) {
            return value.item;
        }
        else if constexpr (I == 5) {
            return value.from_pos;
        }
        else {
            return value.hit_pos;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::ItemUseOnActorInventoryTransaction> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::ItemUseOnActorInventoryTransaction>{"ItemUseOnActorInventoryTransaction"};

template <>
inline constexpr std::array<std::string_view, 8> field_names_v<v2225::ItemUseOnActorInventoryTransaction>{{
    "transaction",
    "runtime_id",
    "action_type",
    "slot",
    "hand",
    "item",
    "from_pos",
    "hit_pos",
}};

template <>
struct field_accessor<v2225::ItemUseOnActorInventoryTransaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.transaction;
        }
        else if constexpr (I == 1) {
            return value.runtime_id;
        }
        else if constexpr (I == 2) {
            return value.action_type;
        }
        else if constexpr (I == 3) {
            return value.slot;
        }
        else if constexpr (I == 4) {
            return value.hand;
        }
        else if constexpr (I == 5) {
            return value.item;
        }
        else if constexpr (I == 6) {
            return value.from_pos;
        }
        else {
            return value.hit_pos;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::ItemReleaseInventoryTransaction> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ItemReleaseInventoryTransaction>{"ItemReleaseInventoryTransaction"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<base::ItemReleaseInventoryTransaction>{{
    "transaction",
    "action_type",
    "slot",
    "item",
    "from_pos",
}};

template <>
struct field_accessor<base::ItemReleaseInventoryTransaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.transaction;
        }
        else if constexpr (I == 1) {
            return value.action_type;
        }
        else if constexpr (I == 2) {
            return value.slot;
        }
        else if constexpr (I == 3) {
            return value.item;
        }
        else {
            return value.from_pos;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v748::ItemReleaseInventoryTransaction> = true;

template <>
inline constexpr std::string_view struct_name_v<v748::ItemReleaseInventoryTransaction>{"ItemReleaseInventoryTransaction"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v748::ItemReleaseInventoryTransaction>{{
    "transaction",
    "action_type",
    "slot",
    "item",
    "from_pos",
}};

template <>
struct field_accessor<v748::ItemReleaseInventoryTransaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.transaction;
        }
        else if constexpr (I == 1) {
            return value.action_type;
        }
        else if constexpr (I == 2) {
            return value.slot;
        }
        else if constexpr (I == 3) {
            return value.item;
        }
        else {
            return value.from_pos;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::ItemReleaseInventoryTransaction> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::ItemReleaseInventoryTransaction>{"ItemReleaseInventoryTransaction"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v1001::ItemReleaseInventoryTransaction>{{
    "transaction",
    "action_type",
    "slot",
    "item",
    "from_pos",
}};

template <>
struct field_accessor<v1001::ItemReleaseInventoryTransaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.transaction;
        }
        else if constexpr (I == 1) {
            return value.action_type;
        }
        else if constexpr (I == 2) {
            return value.slot;
        }
        else if constexpr (I == 3) {
            return value.item;
        }
        else {
            return value.from_pos;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ItemReleaseInventoryTransaction> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ItemReleaseInventoryTransaction>{"ItemReleaseInventoryTransaction"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v2168::ItemReleaseInventoryTransaction>{{
    "transaction",
    "action_type",
    "slot",
    "item",
    "from_pos",
}};

template <>
struct field_accessor<v2168::ItemReleaseInventoryTransaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.transaction;
        }
        else if constexpr (I == 1) {
            return value.action_type;
        }
        else if constexpr (I == 2) {
            return value.slot;
        }
        else if constexpr (I == 3) {
            return value.item;
        }
        else {
            return value.from_pos;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2193::ItemReleaseInventoryTransaction> = true;

template <>
inline constexpr std::string_view struct_name_v<v2193::ItemReleaseInventoryTransaction>{"ItemReleaseInventoryTransaction"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v2193::ItemReleaseInventoryTransaction>{{
    "transaction",
    "action_type",
    "slot",
    "item",
    "from_pos",
}};

template <>
struct field_accessor<v2193::ItemReleaseInventoryTransaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.transaction;
        }
        else if constexpr (I == 1) {
            return value.action_type;
        }
        else if constexpr (I == 2) {
            return value.slot;
        }
        else if constexpr (I == 3) {
            return value.item;
        }
        else {
            return value.from_pos;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::ItemReleaseInventoryTransaction> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::ItemReleaseInventoryTransaction>{"ItemReleaseInventoryTransaction"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<v2225::ItemReleaseInventoryTransaction>{{
    "transaction",
    "action_type",
    "slot",
    "item",
    "from_pos",
    "hand",
}};

template <>
struct field_accessor<v2225::ItemReleaseInventoryTransaction> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.transaction;
        }
        else if constexpr (I == 1) {
            return value.action_type;
        }
        else if constexpr (I == 2) {
            return value.slot;
        }
        else if constexpr (I == 3) {
            return value.item;
        }
        else if constexpr (I == 4) {
            return value.from_pos;
        }
        else {
            return value.hand;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::InventoryTransactionPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::InventoryTransactionPacket>{"InventoryTransactionPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<base::InventoryTransactionPacket>{{
    "legacy_request_id",
    "legacy_set_item_slots",
    "transaction",
}};

template <>
struct field_accessor<base::InventoryTransactionPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.legacy_request_id;
        }
        else if constexpr (I == 1) {
            return value.legacy_set_item_slots;
        }
        else {
            return value.transaction;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v748::InventoryTransactionPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v748::InventoryTransactionPacket>{"InventoryTransactionPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v748::InventoryTransactionPacket>{{
    "legacy_request_id",
    "legacy_set_item_slots",
    "transaction",
}};

template <>
struct field_accessor<v748::InventoryTransactionPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.legacy_request_id;
        }
        else if constexpr (I == 1) {
            return value.legacy_set_item_slots;
        }
        else {
            return value.transaction;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v844::InventoryTransactionPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v844::InventoryTransactionPacket>{"InventoryTransactionPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v844::InventoryTransactionPacket>{{
    "legacy_request_id",
    "legacy_set_item_slots",
    "transaction",
}};

template <>
struct field_accessor<v844::InventoryTransactionPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.legacy_request_id;
        }
        else if constexpr (I == 1) {
            return value.legacy_set_item_slots;
        }
        else {
            return value.transaction;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::InventoryTransactionPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::InventoryTransactionPacket>{"InventoryTransactionPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v924::InventoryTransactionPacket>{{
    "legacy_request_id",
    "legacy_set_item_slots",
    "transaction",
}};

template <>
struct field_accessor<v924::InventoryTransactionPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.legacy_request_id;
        }
        else if constexpr (I == 1) {
            return value.legacy_set_item_slots;
        }
        else {
            return value.transaction;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::InventoryTransactionPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::InventoryTransactionPacket>{"InventoryTransactionPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v944::InventoryTransactionPacket>{{
    "legacy_request_id",
    "legacy_set_item_slots",
    "transaction",
}};

template <>
struct field_accessor<v944::InventoryTransactionPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.legacy_request_id;
        }
        else if constexpr (I == 1) {
            return value.legacy_set_item_slots;
        }
        else {
            return value.transaction;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::InventoryTransactionPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::InventoryTransactionPacket>{"InventoryTransactionPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v1001::InventoryTransactionPacket>{{
    "legacy_request_id",
    "legacy_set_item_slots",
    "transaction",
}};

template <>
struct field_accessor<v1001::InventoryTransactionPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.legacy_request_id;
        }
        else if constexpr (I == 1) {
            return value.legacy_set_item_slots;
        }
        else {
            return value.transaction;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::InventoryTransactionPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::InventoryTransactionPacket>{"InventoryTransactionPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v2168::InventoryTransactionPacket>{{
    "legacy_request_id",
    "legacy_set_item_slots",
    "transaction",
}};

template <>
struct field_accessor<v2168::InventoryTransactionPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.legacy_request_id;
        }
        else if constexpr (I == 1) {
            return value.legacy_set_item_slots;
        }
        else {
            return value.transaction;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2193::InventoryTransactionPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2193::InventoryTransactionPacket>{"InventoryTransactionPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v2193::InventoryTransactionPacket>{{
    "legacy_request_id",
    "legacy_set_item_slots",
    "transaction",
}};

template <>
struct field_accessor<v2193::InventoryTransactionPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.legacy_request_id;
        }
        else if constexpr (I == 1) {
            return value.legacy_set_item_slots;
        }
        else {
            return value.transaction;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::InventoryTransactionPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::InventoryTransactionPacket>{"InventoryTransactionPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v2225::InventoryTransactionPacket>{{
    "legacy_request_id",
    "legacy_set_item_slots",
    "transaction",
}};

template <>
struct field_accessor<v2225::InventoryTransactionPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.legacy_request_id;
        }
        else if constexpr (I == 1) {
            return value.legacy_set_item_slots;
        }
        else {
            return value.transaction;
        }
    }
};

}  // namespace detail


template <>
struct Serializer<base::LegacySetSlot> {
    static void serialize(BinaryWriter &stream, const base::LegacySetSlot &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::LegacySetSlot, std::error_code>;
};

template <>
struct Serializer<v924::LegacySetSlot> {
    static void serialize(BinaryWriter &stream, const v924::LegacySetSlot &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::LegacySetSlot, std::error_code>;
};

template <>
struct Serializer<v2225::LegacySetSlot> {
    static void serialize(BinaryWriter &stream, const v2225::LegacySetSlot &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::LegacySetSlot, std::error_code>;
};

template <>
struct Serializer<base::InventorySource> {
    static void serialize(BinaryWriter &stream, const base::InventorySource &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::InventorySource, std::error_code>;
};

template <>
struct Serializer<v748::InventorySource> {
    static void serialize(BinaryWriter &stream, const v748::InventorySource &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v748::InventorySource, std::error_code>;
};

template <>
struct Serializer<v1001::InventorySource> {
    static void serialize(BinaryWriter &stream, const v1001::InventorySource &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::InventorySource, std::error_code>;
};

template <>
struct Serializer<v2193::InventorySource> {
    static void serialize(BinaryWriter &stream, const v2193::InventorySource &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::InventorySource, std::error_code>;
};

template <>
struct Serializer<base::InventoryAction> {
    static void serialize(BinaryWriter &stream, const base::InventoryAction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::InventoryAction, std::error_code>;
};

template <>
struct Serializer<v748::InventoryAction> {
    static void serialize(BinaryWriter &stream, const v748::InventoryAction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v748::InventoryAction, std::error_code>;
};

template <>
struct Serializer<v1001::InventoryAction> {
    static void serialize(BinaryWriter &stream, const v1001::InventoryAction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::InventoryAction, std::error_code>;
};

template <>
struct Serializer<v2168::InventoryAction> {
    static void serialize(BinaryWriter &stream, const v2168::InventoryAction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::InventoryAction, std::error_code>;
};

template <>
struct Serializer<v2193::InventoryAction> {
    static void serialize(BinaryWriter &stream, const v2193::InventoryAction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::InventoryAction, std::error_code>;
};

template <>
struct Serializer<base::InventoryTransaction> {
    static void serialize(BinaryWriter &stream, const base::InventoryTransaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::InventoryTransaction, std::error_code>;
};

template <>
struct Serializer<v748::InventoryTransaction> {
    static void serialize(BinaryWriter &stream, const v748::InventoryTransaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v748::InventoryTransaction, std::error_code>;
};

template <>
struct Serializer<v1001::InventoryTransaction> {
    static void serialize(BinaryWriter &stream, const v1001::InventoryTransaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::InventoryTransaction, std::error_code>;
};

template <>
struct Serializer<v2168::InventoryTransaction> {
    static void serialize(BinaryWriter &stream, const v2168::InventoryTransaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::InventoryTransaction, std::error_code>;
};

template <>
struct Serializer<v2193::InventoryTransaction> {
    static void serialize(BinaryWriter &stream, const v2193::InventoryTransaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::InventoryTransaction, std::error_code>;
};

template <>
struct Serializer<base::NormalTransactionData> {
    static void serialize(BinaryWriter &stream, const base::NormalTransactionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::NormalTransactionData, std::error_code>;
};

template <>
struct Serializer<v748::NormalTransactionData> {
    static void serialize(BinaryWriter &stream, const v748::NormalTransactionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v748::NormalTransactionData, std::error_code>;
};

template <>
struct Serializer<v1001::NormalTransactionData> {
    static void serialize(BinaryWriter &stream, const v1001::NormalTransactionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::NormalTransactionData, std::error_code>;
};

template <>
struct Serializer<v2168::NormalTransactionData> {
    static void serialize(BinaryWriter &stream, const v2168::NormalTransactionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::NormalTransactionData, std::error_code>;
};

template <>
struct Serializer<v2193::NormalTransactionData> {
    static void serialize(BinaryWriter &stream, const v2193::NormalTransactionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::NormalTransactionData, std::error_code>;
};

template <>
struct Serializer<base::InventoryMismatchData> {
    static void serialize(BinaryWriter &stream, const base::InventoryMismatchData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::InventoryMismatchData, std::error_code>;
};

template <>
struct Serializer<v748::InventoryMismatchData> {
    static void serialize(BinaryWriter &stream, const v748::InventoryMismatchData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v748::InventoryMismatchData, std::error_code>;
};

template <>
struct Serializer<v1001::InventoryMismatchData> {
    static void serialize(BinaryWriter &stream, const v1001::InventoryMismatchData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::InventoryMismatchData, std::error_code>;
};

template <>
struct Serializer<v2168::InventoryMismatchData> {
    static void serialize(BinaryWriter &stream, const v2168::InventoryMismatchData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::InventoryMismatchData, std::error_code>;
};

template <>
struct Serializer<v2193::InventoryMismatchData> {
    static void serialize(BinaryWriter &stream, const v2193::InventoryMismatchData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::InventoryMismatchData, std::error_code>;
};

template <>
struct Serializer<base::ItemUseInventoryTransaction> {
    static void serialize(BinaryWriter &stream, const base::ItemUseInventoryTransaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ItemUseInventoryTransaction, std::error_code>;
};

template <>
struct Serializer<v748::ItemUseInventoryTransaction> {
    static void serialize(BinaryWriter &stream, const v748::ItemUseInventoryTransaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v748::ItemUseInventoryTransaction, std::error_code>;
};

template <>
struct Serializer<v844::ItemUseInventoryTransaction> {
    static void serialize(BinaryWriter &stream, const v844::ItemUseInventoryTransaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v844::ItemUseInventoryTransaction, std::error_code>;
};

template <>
struct Serializer<v944::ItemUseInventoryTransaction> {
    static void serialize(BinaryWriter &stream, const v944::ItemUseInventoryTransaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::ItemUseInventoryTransaction, std::error_code>;
};

template <>
struct Serializer<v1001::ItemUseInventoryTransaction> {
    static void serialize(BinaryWriter &stream, const v1001::ItemUseInventoryTransaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::ItemUseInventoryTransaction, std::error_code>;
};

template <>
struct Serializer<v2168::ItemUseInventoryTransaction> {
    static void serialize(BinaryWriter &stream, const v2168::ItemUseInventoryTransaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ItemUseInventoryTransaction, std::error_code>;
};

template <>
struct Serializer<v2193::ItemUseInventoryTransaction> {
    static void serialize(BinaryWriter &stream, const v2193::ItemUseInventoryTransaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::ItemUseInventoryTransaction, std::error_code>;
};

template <>
struct Serializer<legacy::base::ItemUseInventoryTransaction> {
    static void serialize(BinaryWriter &stream, const legacy::base::ItemUseInventoryTransaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<legacy::base::ItemUseInventoryTransaction, std::error_code>;
};

template <>
struct Serializer<legacy::v748::ItemUseInventoryTransaction> {
    static void serialize(BinaryWriter &stream, const legacy::v748::ItemUseInventoryTransaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<legacy::v748::ItemUseInventoryTransaction, std::error_code>;
};

template <>
struct Serializer<legacy::v844::ItemUseInventoryTransaction> {
    static void serialize(BinaryWriter &stream, const legacy::v844::ItemUseInventoryTransaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<legacy::v844::ItemUseInventoryTransaction, std::error_code>;
};

template <>
struct Serializer<legacy::v944::ItemUseInventoryTransaction> {
    static void serialize(BinaryWriter &stream, const legacy::v944::ItemUseInventoryTransaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<legacy::v944::ItemUseInventoryTransaction, std::error_code>;
};

template <>
struct Serializer<legacy::v1001::ItemUseInventoryTransaction> {
    static void serialize(BinaryWriter &stream, const legacy::v1001::ItemUseInventoryTransaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<legacy::v1001::ItemUseInventoryTransaction, std::error_code>;
};

template <>
struct Serializer<legacy::v2168::ItemUseInventoryTransaction> {
    static void serialize(BinaryWriter &stream, const legacy::v2168::ItemUseInventoryTransaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<legacy::v2168::ItemUseInventoryTransaction, std::error_code>;
};

template <>
struct Serializer<legacy::v2193::ItemUseInventoryTransaction> {
    static void serialize(BinaryWriter &stream, const legacy::v2193::ItemUseInventoryTransaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<legacy::v2193::ItemUseInventoryTransaction, std::error_code>;
};

template <>
struct Serializer<base::ItemUseOnActorInventoryTransaction> {
    static void serialize(BinaryWriter &stream, const base::ItemUseOnActorInventoryTransaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ItemUseOnActorInventoryTransaction, std::error_code>;
};

template <>
struct Serializer<v748::ItemUseOnActorInventoryTransaction> {
    static void serialize(BinaryWriter &stream, const v748::ItemUseOnActorInventoryTransaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v748::ItemUseOnActorInventoryTransaction, std::error_code>;
};

template <>
struct Serializer<v1001::ItemUseOnActorInventoryTransaction> {
    static void serialize(BinaryWriter &stream, const v1001::ItemUseOnActorInventoryTransaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::ItemUseOnActorInventoryTransaction, std::error_code>;
};

template <>
struct Serializer<v2168::ItemUseOnActorInventoryTransaction> {
    static void serialize(BinaryWriter &stream, const v2168::ItemUseOnActorInventoryTransaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ItemUseOnActorInventoryTransaction, std::error_code>;
};

template <>
struct Serializer<v2193::ItemUseOnActorInventoryTransaction> {
    static void serialize(BinaryWriter &stream, const v2193::ItemUseOnActorInventoryTransaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::ItemUseOnActorInventoryTransaction, std::error_code>;
};

template <>
struct Serializer<v2225::ItemUseOnActorInventoryTransaction> {
    static void serialize(BinaryWriter &stream, const v2225::ItemUseOnActorInventoryTransaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::ItemUseOnActorInventoryTransaction, std::error_code>;
};

template <>
struct Serializer<base::ItemReleaseInventoryTransaction> {
    static void serialize(BinaryWriter &stream, const base::ItemReleaseInventoryTransaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ItemReleaseInventoryTransaction, std::error_code>;
};

template <>
struct Serializer<v748::ItemReleaseInventoryTransaction> {
    static void serialize(BinaryWriter &stream, const v748::ItemReleaseInventoryTransaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v748::ItemReleaseInventoryTransaction, std::error_code>;
};

template <>
struct Serializer<v1001::ItemReleaseInventoryTransaction> {
    static void serialize(BinaryWriter &stream, const v1001::ItemReleaseInventoryTransaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::ItemReleaseInventoryTransaction, std::error_code>;
};

template <>
struct Serializer<v2168::ItemReleaseInventoryTransaction> {
    static void serialize(BinaryWriter &stream, const v2168::ItemReleaseInventoryTransaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ItemReleaseInventoryTransaction, std::error_code>;
};

template <>
struct Serializer<v2193::ItemReleaseInventoryTransaction> {
    static void serialize(BinaryWriter &stream, const v2193::ItemReleaseInventoryTransaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::ItemReleaseInventoryTransaction, std::error_code>;
};

template <>
struct Serializer<v2225::ItemReleaseInventoryTransaction> {
    static void serialize(BinaryWriter &stream, const v2225::ItemReleaseInventoryTransaction &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::ItemReleaseInventoryTransaction, std::error_code>;
};

template <>
struct Serializer<base::InventoryTransactionPacket> {
    static void serialize(BinaryWriter &stream, const base::InventoryTransactionPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::InventoryTransactionPacket, std::error_code>;
};

template <>
struct Serializer<v748::InventoryTransactionPacket> {
    static void serialize(BinaryWriter &stream, const v748::InventoryTransactionPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v748::InventoryTransactionPacket, std::error_code>;
};

template <>
struct Serializer<v844::InventoryTransactionPacket> {
    static void serialize(BinaryWriter &stream, const v844::InventoryTransactionPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v844::InventoryTransactionPacket, std::error_code>;
};

template <>
struct Serializer<v924::InventoryTransactionPacket> {
    static void serialize(BinaryWriter &stream, const v924::InventoryTransactionPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::InventoryTransactionPacket, std::error_code>;
};

template <>
struct Serializer<v944::InventoryTransactionPacket> {
    static void serialize(BinaryWriter &stream, const v944::InventoryTransactionPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::InventoryTransactionPacket, std::error_code>;
};

template <>
struct Serializer<v1001::InventoryTransactionPacket> {
    static void serialize(BinaryWriter &stream, const v1001::InventoryTransactionPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::InventoryTransactionPacket, std::error_code>;
};

template <>
struct Serializer<v2168::InventoryTransactionPacket> {
    static void serialize(BinaryWriter &stream, const v2168::InventoryTransactionPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::InventoryTransactionPacket, std::error_code>;
};

template <>
struct Serializer<v2193::InventoryTransactionPacket> {
    static void serialize(BinaryWriter &stream, const v2193::InventoryTransactionPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::InventoryTransactionPacket, std::error_code>;
};

template <>
struct Serializer<v2225::InventoryTransactionPacket> {
    static void serialize(BinaryWriter &stream, const v2225::InventoryTransactionPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::InventoryTransactionPacket, std::error_code>;
};

template <>
struct Serializer<base::TransactionData> {
    static void serialize(BinaryWriter &stream, const base::TransactionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::TransactionData, std::error_code>;
};

template <>
struct Serializer<v748::TransactionData> {
    static void serialize(BinaryWriter &stream, const v748::TransactionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v748::TransactionData, std::error_code>;
};

template <>
struct Serializer<v844::TransactionData> {
    static void serialize(BinaryWriter &stream, const v844::TransactionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v844::TransactionData, std::error_code>;
};

template <>
struct Serializer<v944::TransactionData> {
    static void serialize(BinaryWriter &stream, const v944::TransactionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::TransactionData, std::error_code>;
};

template <>
struct Serializer<v1001::TransactionData> {
    static void serialize(BinaryWriter &stream, const v1001::TransactionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::TransactionData, std::error_code>;
};

template <>
struct Serializer<v2168::TransactionData> {
    static void serialize(BinaryWriter &stream, const v2168::TransactionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::TransactionData, std::error_code>;
};

template <>
struct Serializer<v2193::TransactionData> {
    static void serialize(BinaryWriter &stream, const v2193::TransactionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::TransactionData, std::error_code>;
};

template <>
struct Serializer<v2225::TransactionData> {
    static void serialize(BinaryWriter &stream, const v2225::TransactionData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::TransactionData, std::error_code>;
};
using LegacySetSlot = LegacySetSlot_<2225>;
using InventorySource = InventorySource_<2225>;
using InventoryAction = InventoryAction_<2225>;
using InventoryTransaction = InventoryTransaction_<2225>;
using NormalTransactionData = NormalTransactionData_<2225>;
using InventoryMismatchData = InventoryMismatchData_<2225>;
using ItemUseInventoryTransaction = ItemUseInventoryTransaction_<2225>;
using ItemUseOnActorInventoryTransaction = ItemUseOnActorInventoryTransaction_<2225>;
using ItemReleaseInventoryTransaction = ItemReleaseInventoryTransaction_<2225>;
using InventoryTransactionPacket = InventoryTransactionPacket_<2225>;
using TransactionData = TransactionData_<2225>;

}  // namespace bedrock::protocol
