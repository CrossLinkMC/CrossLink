#include "proto/BuiltinCodecs.hpp"

#include "crosslink/api/proto/packets/AllPackets.hpp"

namespace crosslink::proto {

void registerBuiltinCodecs(PacketCodecs& codecs) {
    // Packets with their own class.
    LoginPacket::registerIn(codecs);
    NetworkSettingsPacket::registerIn(codecs);
    ServerToClientHandshakePacket::registerIn(codecs);
    ClientToServerHandshakePacket::registerIn(codecs);
    StartGamePacket::registerIn(codecs);
    ChangeDimensionPacket::registerIn(codecs);
    RespawnPacket::registerIn(codecs);
    LoadingScreenPacket::registerIn(codecs);
    ResourcePackClientResponsePacket::registerIn(codecs);
    SetLocalPlayerAsInitializedPacket::registerIn(codecs);
    ClientCacheStatusPacket::registerIn(codecs);
    SetPlayerGameTypePacket::registerIn(codecs);
    SetPlayerInventoryOptionsPacket::registerIn(codecs);
    LevelChunkPacket::registerIn(codecs);
    SubChunkPacket::registerIn(codecs);
    SubChunkRequestPacket::registerIn(codecs);
    PlayerActionPacket::registerIn(codecs);
    InventoryTransactionPacket::registerIn(codecs);
    PlayStatusPacket::registerIn(codecs);
    DisconnectPacket::registerIn(codecs);
    TransferPacket::registerIn(codecs);
    RequestNetworkSettingsPacket::registerIn(codecs);

    // The runtime-id group shares one class; every id it covers gets the same
    // factory. PlayerAction and Respawn are deliberately not part of it: they
    // have classes of their own that also expose more than the runtime id.
    for (const auto id : RuntimeIdPacket::coveredIds()) {
        codecs.registerCodec(id, [](PacketHeader const& header, Bytes&& bytes, std::size_t headerSize) -> PacketPtr {
            if (bytes.empty()) return std::make_unique<RuntimeIdPacket>(header);
            return std::make_unique<RuntimeIdPacket>(header, std::move(bytes), headerSize);
        });
    }
}

} // namespace crosslink::proto
