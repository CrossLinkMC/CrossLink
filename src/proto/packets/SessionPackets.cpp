#include "crosslink/api/proto/packets/SessionPackets.hpp"

#include "proto/EndstoneBridge.hpp"

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
    mStatus = static_cast<std::int32_t>(packet->status);
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
    mReason = static_cast<std::int32_t>(packet->reason);
    // The message pair is optional on the wire: absent means the client hides it.
    if (const auto* messages = std::get_if<bp::DisconnectPacketMessages>(&packet->messages)) {
        mSkipMessage = false;
        mMessage     = messages->message;
    } else {
        mSkipMessage = true;
    }
    return {};
}

Result<> DisconnectPacket::encodeImpl() {
    bp::DisconnectPacket packet;
    packet.reason   = static_cast<bp::v2225::DisconnectFailReason>(mReason);
    packet.messages =
        mSkipMessage ? std::variant<bp::DisconnectPacketMessages, std::monostate>{std::monostate{}}
                     : std::variant<bp::DisconnectPacketMessages, std::monostate>{
                           bp::DisconnectPacketMessages{.message = mMessage, .filtered_message = mMessage}
                       };
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
    mAddress      = std::move(packet->destination);
    mPort         = packet->destination_port;
    mReloadWorld  = packet->reload_world;
    return {};
}

Result<> TransferPacket::encodeImpl() {
    bp::TransferPacket packet;
    packet.destination       = mAddress;
    packet.destination_port  = mPort;
    packet.reload_world      = mReloadWorld;
    setSerialized(bridge::serialize(header(), packet), bridge::serializedHeaderSize(header()));
    return {};
}

// ---- RequestNetworkSettings --------------------------------------------

RequestNetworkSettingsPacket::RequestNetworkSettingsPacket(std::int32_t protocolVersion) : mProtocolVersion(protocolVersion) {}

std::int32_t RequestNetworkSettingsPacket::protocolVersion() const { return mProtocolVersion; }

Result<> RequestNetworkSettingsPacket::decodeImpl() {
    auto packet = bridge::decode<bp::RequestNetworkSettingsPacket>(payload());
    if (!packet) return std::unexpected(packet.error());
    mProtocolVersion = packet->client_network_version;
    return {};
}

Result<> RequestNetworkSettingsPacket::encodeImpl() {
    bp::RequestNetworkSettingsPacket packet;
    packet.client_network_version = mProtocolVersion;
    setSerialized(bridge::serialize(header(), packet), bridge::serializedHeaderSize(header()));
    return {};
}

} // namespace crosslink::proto
