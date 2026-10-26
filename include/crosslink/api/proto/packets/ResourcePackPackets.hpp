#pragma once

#include "crosslink/api/proto/TypedPacket.hpp"

#include <cstdint>
#include <string_view>

namespace crosslink::proto {

enum class ResourcePackResponse : std::uint8_t {
    Refused      = 1,
    SendPacks    = 2,
    HaveAllPacks = 3,
    Completed    = 4,
};

/// The client's answer to ResourcePacksInfo / ResourcePackStack.
///
/// During a handoff the gateway answers on the client's behalf: the packs the
/// target announces were already accepted at first login, and re-downloading them
/// would be both slow and visible.
class CROSSLINK_API ResourcePackClientResponsePacket final
: public TypedPacket<ResourcePackClientResponsePacket, PacketId::ResourcePackClientResponse> {
public:
    static constexpr std::string_view staticName = "ResourcePackClientResponsePacket";

    using TypedPacket::TypedPacket;

    explicit ResourcePackClientResponsePacket(ResourcePackResponse response);

    [[nodiscard]] ResourcePackResponse response() const;
    void                               setResponse(ResourcePackResponse response);

protected:
    Result<> decodeImpl() override;
    Result<> encodeImpl() override;

private:
    ResourcePackResponse mResponse{ResourcePackResponse::Completed};
};

} // namespace crosslink::proto
