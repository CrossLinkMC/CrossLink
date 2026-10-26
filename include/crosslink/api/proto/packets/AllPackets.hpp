#pragma once

// Every packet CrossLink interprets. Including this header is enough for the
// codecs to be registered; the registration itself happens in each packet's
// translation unit inside crosslink_core.

#include "crosslink/api/proto/packets/ChunkPackets.hpp"
#include "crosslink/api/proto/packets/ChangeDimensionPacket.hpp"
#include "crosslink/api/proto/packets/HandshakePackets.hpp"
#include "crosslink/api/proto/packets/InventoryTransactionPacket.hpp"
#include "crosslink/api/proto/packets/LoadingScreenPacket.hpp"
#include "crosslink/api/proto/packets/LoginPacket.hpp"
#include "crosslink/api/proto/packets/NetworkSettingsPacket.hpp"
#include "crosslink/api/proto/packets/PlayerActionPacket.hpp"
#include "crosslink/api/proto/packets/PlayerInitPackets.hpp"
#include "crosslink/api/proto/packets/ResourcePackPackets.hpp"
#include "crosslink/api/proto/packets/RespawnPacket.hpp"
#include "crosslink/api/proto/packets/RuntimeIdPackets.hpp"
#include "crosslink/api/proto/packets/SessionPackets.hpp"
#include "crosslink/api/proto/packets/StartGamePacket.hpp"
