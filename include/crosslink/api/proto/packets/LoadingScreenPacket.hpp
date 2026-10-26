#pragma once

#include "crosslink/api/proto/TypedPacket.hpp"

#include <cstdint>
#include <optional>
#include <string_view>

namespace crosslink::proto {

enum class LoadingScreenType : std::uint8_t {
    NoChange           = 0,
    StartLoadingScreen = 1,
    EndLoadingScreen   = 2,
};

/// The client's side of the loading screen handshake introduced for dimension
/// changes. A handoff has to pair the server's ChangeDimension with the client's
/// Start/End pair, and synthesize an End for a backend that was never told the
/// client is loading.
class CROSSLINK_API LoadingScreenPacket final
: public TypedPacket<LoadingScreenPacket, PacketId::ServerboundLoadingScreen> {
public:
    static constexpr std::string_view staticName = "LoadingScreenPacket";

    using TypedPacket::TypedPacket;

    explicit LoadingScreenPacket(LoadingScreenType type, std::optional<std::uint32_t> loadingScreenId = {});

    [[nodiscard]] LoadingScreenType        type() const;
    [[nodiscard]] std::optional<std::uint32_t> loadingScreenId() const;

    void setType(LoadingScreenType type);
    void setLoadingScreenId(std::optional<std::uint32_t> id);

protected:
    Result<> decodeImpl() override;
    Result<> encodeImpl() override;

private:
    LoadingScreenType            mType{LoadingScreenType::NoChange};
    std::optional<std::uint32_t> mLoadingScreenId{};
};

} // namespace crosslink::proto
