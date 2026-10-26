#pragma once

#include "crosslink/api/proto/Packet.hpp"

namespace crosslink::proto {

/// Registers the codec for every packet type CrossLink interprets. Called once by
/// the application during start-up, before any traffic is accepted, so that the
/// table is complete and predictable rather than depending on static init order.
void registerBuiltinCodecs(PacketCodecs& codecs = PacketCodecs::instance());

} // namespace crosslink::proto
