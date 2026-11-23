#include "crosslink/api/proto/packets/InventoryTransactionPacket.hpp"

#include "proto/EndstoneBridge.hpp"

#include <variant>

namespace crosslink::proto {
namespace {

namespace bp = bridge::bp;

} // namespace

std::optional<std::uint64_t> InventoryTransactionPacket::attackTargetRuntimeId() {
    if (mAttackTargetRuntimeId) return mAttackTargetRuntimeId;

    auto packet = bridge::decode<bp::InventoryTransactionPacket>(payload());
    if (!packet) return std::nullopt;

    const auto* transaction = std::get_if<bp::ItemUseOnActorInventoryTransaction>(&packet->transaction);
    if (transaction == nullptr) return std::nullopt;
    if (transaction->action_type != bp::ItemUseOnActorInventoryTransaction::ActionType::Attack) return std::nullopt;

    mAttackTargetRuntimeId = transaction->runtime_id;
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
