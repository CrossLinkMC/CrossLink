#include "crosslink/api/proto/packets/NetworkSettingsPacket.hpp"

#include "proto/SculkBridge.hpp"

#include <sculk/protocol/codec/packet/NetworkSettingsPacket.hpp>

namespace crosslink::proto {
namespace {

namespace bp = bridge::bp;

} // namespace

NetworkSettingsPacket::NetworkSettingsPacket(net::Compression algorithm, std::uint16_t threshold)
: mCompressionAlgorithm(algorithm), mCompressionThreshold(threshold) {}

std::uint16_t NetworkSettingsPacket::compressionThreshold() const { return mCompressionThreshold; }

net::Compression NetworkSettingsPacket::compressionAlgorithm() const { return mCompressionAlgorithm; }

bool NetworkSettingsPacket::clientThrottleEnabled() const { return mClientThrottleEnabled; }

std::uint8_t NetworkSettingsPacket::clientThrottleThreshold() const { return mClientThrottleThreshold; }

float NetworkSettingsPacket::clientThrottleScalar() const { return mClientThrottleScalar; }

void NetworkSettingsPacket::setCompression(net::Compression algorithm, std::uint16_t threshold) {
    mCompressionAlgorithm = algorithm;
    mCompressionThreshold = threshold;
    markDirty();
}

Result<> NetworkSettingsPacket::decodeImpl() {
    auto packet = bridge::decode<bp::NetworkSettingsPacket>(payload());
    if (!packet) return std::unexpected(packet.error());
    mCompressionThreshold = packet->mCompressionThreshold;
    mCompressionAlgorithm = bridge::fromSculk(packet->mCompressionAlgorithm);
    mClientThrottleEnabled = packet->mClientThrottleEnabled;
    mClientThrottleThreshold = packet->mClientThrottleThreshold;
    mClientThrottleScalar = packet->mClientThrottleScalar;
    return {};
}

Result<> NetworkSettingsPacket::encodeImpl() {
    bp::NetworkSettingsPacket packet;
    packet.mCompressionThreshold = mCompressionThreshold;
    packet.mCompressionAlgorithm = bridge::toSculk(mCompressionAlgorithm);
    packet.mClientThrottleEnabled = mClientThrottleEnabled;
    packet.mClientThrottleThreshold = mClientThrottleThreshold;
    packet.mClientThrottleScalar = mClientThrottleScalar;
    setSerialized(bridge::serialize(header(), packet), bridge::serializedHeaderSize(header()));
    return {};
}

} // namespace crosslink::proto
