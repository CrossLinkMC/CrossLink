#pragma once

#include "crosslink/api/Export.hpp"
#include "crosslink/api/Result.hpp"
#include "crosslink/api/Types.hpp"
#include "crosslink/api/proto/Crypto.hpp"

#include <optional>
#include <string>
#include <string_view>

namespace crosslink::proto::auth {

/// Read-only view of the connection request carried inside a Login packet.
struct ConnectionRequestView {
    std::string xuid;
    std::string name;
    std::string playFabId;
    /// Stable offline identity (UUID string) used when there is no XUID.
    std::string identity;
    std::string clientPublicKey;
    std::string deviceId;
    std::string deviceModel;
    std::string selfSignedId;
    std::string serverAddress;
    std::string gameVersion;
    int         platformType{};
    bool        onlineAuthenticated{};

    [[nodiscard]] PlayerIdentity toIdentity() const;
};

[[nodiscard]] CROSSLINK_API Result<ConnectionRequestView> inspect(std::string_view rawConnectionRequest);

/// Re-signs a connection request with the gateway's own key so it can be replayed
/// to another backend, optionally overwriting the two client-property fields a
/// trusted backend agent reads the verified identity from.
struct ResignRequest {
    std::string         rawConnectionRequest;
    crypto::KeyPair     keyPair;
    std::optional<std::string> deviceIdOverride;
    std::optional<std::string> deviceModelOverride;
};

[[nodiscard]] CROSSLINK_API Result<std::string> resign(ResignRequest const& request);

} // namespace crosslink::proto::auth
