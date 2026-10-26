#include "crosslink/api/proto/packets/InventoryTransactionPacket.hpp"

#include "proto/SculkBridge.hpp"

#include <sculk/protocol/codec/inventory/transaction/InventoryTransactionType.hpp>
#include <sculk/protocol/codec/inventory/transaction/ItemUseOnActorInventoryTransaction.hpp>
#include <sculk/protocol/codec/packet/InventoryTransactionPacket.hpp>

#include <variant>

namespace crosslink::proto {
namespace {

namespace bp = bridge::bp;

} // namespace

std::optional<std::uint64_t> InventoryTransactionPacket::attackTargetRuntimeId() {
    if (mAttackTargetRuntimeId) return mAttackTargetRuntimeId;

    auto packet = bridge::decode<bp::InventoryTransactionPacket>(payload());
    if (!packet) return std::nullopt;
    if (packet->mTransaction.type() != bp::InventoryTransactionType::ItemUseOnActorInventoryTransaction) return std::nullopt;

    const auto* transaction = std::get_if<bp::ItemUseOnActorInventoryTransaction>(&packet->mTransaction.mValue);
    if (transaction == nullptr) return std::nullopt;
    if (transaction->mActionType != bp::ItemUseOnActorInventoryTransaction::ActionType::Attack) return std::nullopt;

    mAttackTargetRuntimeId = transaction->mRuntimeId;
    mDecoded = true;
    return mAttackTargetRuntimeId;
}

Result<> InventoryTransactionPacket::decodeImpl() {
    // Only the attack target is interesting; a full decode of every transaction
    // variant would cost more than the whole rest of the pipeline.
    (void)attackTargetRuntimeId();
    return {};
}

} // namespace crosslink::proto
