#pragma once

#include "crosslink/api/proto/TypedPacket.hpp"

#include <cstdint>
#include <optional>
#include <string_view>

namespace crosslink::proto {

/// Inventory transaction. The gateway reads just enough of it to notice an attack
/// on an actor, because that is the packet that breaks first when the runtime ids
/// of two servers disagree.
class CROSSLINK_API InventoryTransactionPacket final
: public TypedPacket<InventoryTransactionPacket, PacketId::InventoryTransaction> {
public:
    static constexpr std::string_view staticName = "InventoryTransactionPacket";

    using TypedPacket::TypedPacket;

    /// Set when this is an item-use-on-actor transaction with the attack action.
    [[nodiscard]] std::optional<std::uint64_t> attackTargetRuntimeId();

protected:
    Result<> decodeImpl() override;

private:
    std::optional<std::uint64_t> mAttackTargetRuntimeId{};
};

} // namespace crosslink::proto
