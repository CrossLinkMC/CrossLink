#pragma once

#include "crosslink/api/proto/TypedPacket.hpp"

#include <cstdint>
#include <string>
#include <string_view>

namespace crosslink::proto {

enum class PlayStatus : std::int32_t {
    LoginSuccess   = 0,
    PlayerSpawn    = 3,
    LoginFailedClientOld = 1,
    LoginFailedServerOld = 2,
};

/// Login outcome. A backend refusing the replayed login shows up here first.
class CROSSLINK_API PlayStatusPacket final : public TypedPacket<PlayStatusPacket, PacketId::PlayStatus> {
public:
    static constexpr std::string_view staticName = "PlayStatusPacket";

    using TypedPacket::TypedPacket;

    [[nodiscard]] std::int32_t status() const;
    [[nodiscard]] bool         isLoginSuccess() const;

protected:
    Result<> decodeImpl() override;

private:
    std::int32_t mStatus{};
};

class CROSSLINK_API DisconnectPacket final : public TypedPacket<DisconnectPacket, PacketId::Disconnect> {
public:
    static constexpr std::string_view staticName = "DisconnectPacket";

    using TypedPacket::TypedPacket;

    DisconnectPacket(std::int32_t reason, std::string message);

    [[nodiscard]] std::int32_t       reason() const;
    [[nodiscard]] bool               skipMessage() const;
    [[nodiscard]] std::string const& message() const;

    void setMessage(std::string message);

protected:
    Result<> decodeImpl() override;
    Result<> encodeImpl() override;

private:
    std::int32_t mReason{};
    bool         mSkipMessage{};
    std::string  mMessage;
};

/// The vanilla cross-server transfer. It makes the client tear down its RakNet
/// session and dial a new address, which is exactly what a seamless gateway must
/// not do — so the gateway exposes it, and a plugin is expected to swallow it.
class CROSSLINK_API TransferPacket final : public TypedPacket<TransferPacket, PacketId::Transfer> {
public:
    static constexpr std::string_view staticName = "TransferPacket";

    using TypedPacket::TypedPacket;

    TransferPacket(std::string address, std::uint16_t port, bool reloadWorld = false);

    [[nodiscard]] std::string const& address() const;
    [[nodiscard]] std::uint16_t      port() const;
    [[nodiscard]] bool               reloadWorld() const;

protected:
    Result<> decodeImpl() override;
    Result<> encodeImpl() override;

private:
    std::string   mAddress;
    std::uint16_t mPort{};
    bool          mReloadWorld{};
};

/// Asks the server for NetworkSettings. The gateway caches the client's copy so a
/// handoff can replay it verbatim to a target that has not seen it.
class CROSSLINK_API RequestNetworkSettingsPacket final
: public TypedPacket<RequestNetworkSettingsPacket, PacketId::RequestNetworkSettings> {
public:
    static constexpr std::string_view staticName = "RequestNetworkSettingsPacket";

    using TypedPacket::TypedPacket;

    explicit RequestNetworkSettingsPacket(std::int32_t protocolVersion);

    [[nodiscard]] std::int32_t protocolVersion() const;

protected:
    Result<> decodeImpl() override;
    Result<> encodeImpl() override;

private:
    std::int32_t mProtocolVersion{};
};

} // namespace crosslink::proto
