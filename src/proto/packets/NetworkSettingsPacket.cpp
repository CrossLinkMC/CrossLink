#include "crosslink/api/proto/packets/NetworkSettingsPacket.hpp"

#include "proto/EndstoneBridge.hpp"

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
    mCompressionThreshold = packet->compression_threshold;
    mCompressionAlgorithm = bridge::fromWire(packet->compression_algorithm);
    mClientThrottleEnabled = packet->client_throttle_enabled;
    mClientThrottleThreshold = packet->client_throttle_threshold;
    mClientThrottleScalar = packet->client_throttle_scalar;
    return {};
}

Result<> NetworkSettingsPacket::encodeImpl() {
    bp::NetworkSettingsPacket packet;
    packet.compression_threshold = mCompressionThreshold;
    packet.compression_algorithm = bridge::toWire(mCompressionAlgorithm);
    packet.client_throttle_enabled = mClientThrottleEnabled;
    packet.client_throttle_threshold = mClientThrottleThreshold;
    packet.client_throttle_scalar = mClientThrottleScalar;
    setSerialized(bridge::serialize(header(), packet), bridge::serializedHeaderSize(header()));
    return {};
}

} // namespace crosslink::proto
