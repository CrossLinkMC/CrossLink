#include "crosslink/api/proto/packets/HandshakePackets.hpp"

#include "proto/SculkBridge.hpp"

#include <sculk/protocol/codec/packet/ClientToServerHandshakePacket.hpp>
#include <sculk/protocol/codec/packet/ServerToClientHandshakePacket.hpp>

namespace crosslink::proto {
namespace {

namespace bp = bridge::bp;

} // namespace

ServerToClientHandshakePacket::ServerToClientHandshakePacket(std::string token) : mToken(std::move(token)) {}

std::string const& ServerToClientHandshakePacket::token() const { return mToken; }

void ServerToClientHandshakePacket::setToken(std::string token) {
    mToken = std::move(token);
    markDirty();
}

Result<> ServerToClientHandshakePacket::decodeImpl() {
    auto packet = bridge::decode<bp::ServerToClientHandshakePacket>(payload());
    if (!packet) return std::unexpected(packet.error());
    mToken = std::move(packet->mHandshakeWebToken);
    return {};
}

Result<> ServerToClientHandshakePacket::encodeImpl() {
    bp::ServerToClientHandshakePacket packet;
    packet.mHandshakeWebToken = mToken;
    setSerialized(bridge::serialize(header(), packet), bridge::serializedHeaderSize(header()));
    return {};
}

Result<> ClientToServerHandshakePacket::decodeImpl() { return {}; }

Result<> ClientToServerHandshakePacket::encodeImpl() {
    bp::ClientToServerHandshakePacket packet;
    setSerialized(bridge::serialize(header(), packet), bridge::serializedHeaderSize(header()));
    return {};
}

} // namespace crosslink::proto
