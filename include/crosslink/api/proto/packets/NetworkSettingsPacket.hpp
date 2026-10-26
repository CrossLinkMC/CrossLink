#pragma once

#include "crosslink/api/net/Transport.hpp"
#include "crosslink/api/proto/TypedPacket.hpp"

#include <cstdint>
#include <string_view>

namespace crosslink::proto {

/// Compression and throttling settings a backend announces right after
/// RequestNetworkSettings. Each leg negotiates its own: the gateway applies the
/// backend's settings to the backend leg and, on the first login, relays the
/// packet to the client and applies them to the client leg too.
class CROSSLINK_API NetworkSettingsPacket final
: public TypedPacket<NetworkSettingsPacket, PacketId::NetworkSettings> {
public:
    static constexpr std::string_view staticName = "NetworkSettingsPacket";

    using TypedPacket::TypedPacket;

    NetworkSettingsPacket(net::Compression algorithm, std::uint16_t threshold);

    [[nodiscard]] std::uint16_t     compressionThreshold() const;
    [[nodiscard]] net::Compression  compressionAlgorithm() const;
    [[nodiscard]] bool              clientThrottleEnabled() const;
    [[nodiscard]] std::uint8_t      clientThrottleThreshold() const;
    [[nodiscard]] float             clientThrottleScalar() const;

    void setCompression(net::Compression algorithm, std::uint16_t threshold);

protected:
    Result<> decodeImpl() override;
    Result<> encodeImpl() override;

private:
    net::Compression mCompressionAlgorithm{net::Compression::None};
    std::uint16_t    mCompressionThreshold{1};
    bool             mClientThrottleEnabled{};
    std::uint8_t     mClientThrottleThreshold{};
    float            mClientThrottleScalar{};
};

} // namespace crosslink::proto
