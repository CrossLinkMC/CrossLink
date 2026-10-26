#pragma once

#include "crosslink/api/proto/ConnectionRequest.hpp"
#include "crosslink/api/proto/Crypto.hpp"
#include "crosslink/api/proto/TypedPacket.hpp"

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>

namespace crosslink::proto {

/// The client's login. The gateway rewrites and replays this packet for every
/// backend it serves the player on, so it is the one packet that has to survive a
/// full decode/encode round trip.
class CROSSLINK_API LoginPacket final : public TypedPacket<LoginPacket, PacketId::Login> {
public:
    static constexpr std::string_view staticName = "LoginPacket";

    using TypedPacket::TypedPacket;

    [[nodiscard]] std::int32_t  networkVersion() const;
    [[nodiscard]] std::string const& rawConnectionRequest() const;
    void                  setRawConnectionRequest(std::string raw);

    /// Who the client claims to be, before any backend has confirmed it.
    [[nodiscard]] Result<auth::ConnectionRequestView> inspect() const;

    /// Re-signs the embedded connection request with `keyPair` so the packet can
    /// be replayed to another backend, optionally overwriting the two client
    /// property fields a trusted agent reads the verified identity from.
    [[nodiscard]] Result<> resign(
        crypto::KeyPair const&          keyPair,
        std::optional<std::string>      deviceIdOverride    = {},
        std::optional<std::string>      deviceModelOverride = {}
    );

protected:
    Result<> decodeImpl() override;
    Result<> encodeImpl() override;

private:
    std::int32_t mNetworkVersion{};
    std::string  mRawConnectionRequest;
};

} // namespace crosslink::proto
