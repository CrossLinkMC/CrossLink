#include "crosslink/api/proto/packets/SessionPackets.hpp"

#include "proto/SculkBridge.hpp"

#include <sculk/protocol/codec/packet/DisconnectPacket.hpp>
#include <sculk/protocol/codec/packet/PlayStatusPacket.hpp>
#include <sculk/protocol/codec/packet/RequestNetworkSettingsPacket.hpp>
#include <sculk/protocol/codec/packet/TransferPacket.hpp>

namespace crosslink::proto {
namespace {

namespace bp = bridge::bp;

} // namespace

// ---- PlayStatus --------------------------------------------------------

std::int32_t PlayStatusPacket::status() const { return mStatus; }

bool PlayStatusPacket::isLoginSuccess() const { return mStatus == static_cast<std::int32_t>(bp::PlayStatus::LoginSuccess); }

Result<> PlayStatusPacket::decodeImpl() {
    auto packet = bridge::decode<bp::PlayStatusPacket>(payload());
    if (!packet) return std::unexpected(packet.error());
    mStatus = static_cast<std::int32_t>(packet->mStatus);
    return {};
}

// ---- Disconnect --------------------------------------------------------

DisconnectPacket::DisconnectPacket(std::int32_t reason, std::string message)
: mReason(reason), mMessage(std::move(message)) {}

std::int32_t DisconnectPacket::reason() const { return mReason; }

bool DisconnectPacket::skipMessage() const { return mSkipMessage; }

std::string const& DisconnectPacket::message() const { return mMessage; }

void DisconnectPacket::setMessage(std::string message) {
    mMessage = std::move(message);
    markDirty();
}

Result<> DisconnectPacket::decodeImpl() {
    auto packet = bridge::decode<bp::DisconnectPacket>(payload());
    if (!packet) return std::unexpected(packet.error());
    mReason = static_cast<std::int32_t>(packet->mReason);
    mSkipMessage = packet->mSkipMessage;
    mMessage = std::move(packet->mMessage);
    return {};
}

Result<> DisconnectPacket::encodeImpl() {
    bp::DisconnectPacket packet;
    packet.mReason = static_cast<bp::DisconnectFailReason>(mReason);
    packet.mSkipMessage = mSkipMessage;
    packet.mMessage = mMessage;
    packet.mFilteredMessage = mMessage;
    setSerialized(bridge::serialize(header(), packet), bridge::serializedHeaderSize(header()));
    return {};
}

// ---- Transfer ----------------------------------------------------------

TransferPacket::TransferPacket(std::string address, std::uint16_t port, bool reloadWorld)
: mAddress(std::move(address)), mPort(port), mReloadWorld(reloadWorld) {}

std::string const& TransferPacket::address() const { return mAddress; }

std::uint16_t TransferPacket::port() const { return mPort; }

bool TransferPacket::reloadWorld() const { return mReloadWorld; }

Result<> TransferPacket::decodeImpl() {
    auto packet = bridge::decode<bp::TransferPacket>(payload());
    if (!packet) return std::unexpected(packet.error());
    mAddress = std::move(packet->mServerAddress);
    mPort = packet->mServerPort;
    mReloadWorld = packet->mReloadWorld;
    return {};
}

Result<> TransferPacket::encodeImpl() {
    bp::TransferPacket packet;
    packet.mServerAddress = mAddress;
    packet.mServerPort = mPort;
    packet.mReloadWorld = mReloadWorld;
    setSerialized(bridge::serialize(header(), packet), bridge::serializedHeaderSize(header()));
    return {};
}

// ---- RequestNetworkSettings --------------------------------------------

RequestNetworkSettingsPacket::RequestNetworkSettingsPacket(std::int32_t protocolVersion) : mProtocolVersion(protocolVersion) {}

std::int32_t RequestNetworkSettingsPacket::protocolVersion() const { return mProtocolVersion; }

Result<> RequestNetworkSettingsPacket::decodeImpl() {
    auto packet = bridge::decode<bp::RequestNetworkSettingsPacket>(payload());
    if (!packet) return std::unexpected(packet.error());
    mProtocolVersion = packet->mClientNetworkVersion;
    return {};
}

Result<> RequestNetworkSettingsPacket::encodeImpl() {
    bp::RequestNetworkSettingsPacket packet;
    packet.mClientNetworkVersion = mProtocolVersion;
    setSerialized(bridge::serialize(header(), packet), bridge::serializedHeaderSize(header()));
    return {};
}

} // namespace crosslink::proto
