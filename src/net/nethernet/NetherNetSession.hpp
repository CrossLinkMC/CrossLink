#pragma once

// One NetherNet session: a WebRTC peer connection carrying the two data channels
// Bedrock opens, NetherNet's fragment framing on top of them, and the Bedrock
// batch layer on top of that. DTLS already provides confidentiality, so the
// Bedrock encryption handshake is never run here.

#include "crosslink/api/Result.hpp"
#include "crosslink/api/Types.hpp"
#include "crosslink/api/net/Transport.hpp"
#include "net/nethernet/Identity.hpp"
#include "proto/BatchCodec.hpp"

#include <condition_variable>
#include <cstdint>
#include <functional>
#include <memory>
#include <mutex>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace rtc {
class PeerConnection;
class DataChannel;
} // namespace rtc

namespace crosslink::net::nethernet {

class NetherNetSession : public std::enable_shared_from_this<NetherNetSession> {
public:
    /// Answerer faces a game client; Dialer faces a backend and opens the channels.
    enum class Role { Answerer, Dialer };

    struct Config {
        std::string                  bindAddress;
        std::uint16_t                portRangeBegin{1024};
        std::uint16_t                portRangeEnd{65535};
        /// Advertised to the peer, and the reassembly ceiling it implies.
        std::size_t                  maxMessageSize{262144};
        /// What one outbound fragment may carry. Smaller than the advertised
        /// limit on purpose: a huge SCTP message stalls the channel behind one loss.
        std::size_t                  maxSegmentBytes{10000};
        std::size_t                  maxPacketBytes{8u * 1024u * 1024u};
        std::shared_ptr<IdentityKey> identity;
        std::vector<std::string>     iceServers;
        std::chrono::milliseconds    gatheringTimeout{std::chrono::seconds{10}};
    };

    struct Hooks {
        std::function<void()>            onOpen;
        std::function<void(Bytes&)>      onPacket;
        std::function<void(std::string)> onClosed;
    };

    [[nodiscard]] static Result<std::shared_ptr<NetherNetSession>> create(Config config, Hooks hooks, Role role);

    ~NetherNetSession();

    NetherNetSession(NetherNetSession const&)            = delete;
    NetherNetSession& operator=(NetherNetSession const&) = delete;

    /// Answerer: consumes the offer and returns the answer to send back over
    /// signalling. Blocks until ICE gathering finishes.
    [[nodiscard]] Result<std::string> acceptOffer(std::string_view offer);

    /// Dialer: returns the offer to POST. Blocks until ICE gathering finishes.
    [[nodiscard]] Result<std::string> createOffer();
    [[nodiscard]] Result<>            acceptAnswer(std::string_view answer);

    [[nodiscard]] Result<> send(ByteSpan packet, bool immediate);
    void                   setCompression(Compression algorithm, std::int32_t threshold);
    /// Bedrock's own AES batch layer, on top of DTLS. BDS 1.26.60 still runs the
    /// ServerToClientHandshake / ClientToServerHandshake exchange over NetherNet.
    [[nodiscard]] Result<> enableEncryption(ByteSpan key);
    [[nodiscard]] bool     encrypted() const noexcept;

    [[nodiscard]] bool     open() const noexcept;
    [[nodiscard]] bool     closed() const noexcept;
    [[nodiscard]] Endpoint remote() const noexcept;
    void                   close() noexcept;

private:
    NetherNetSession(Config config, Hooks hooks, Role role);

    void attach();
    void bindChannel(std::shared_ptr<rtc::DataChannel> channel, bool reliable);
    void onChannelMessage(bool reliable, std::vector<std::byte> message);
    void deliver(Bytes batch);
    void fail(std::string reason);
    [[nodiscard]] Result<std::string> localSdp();
    [[nodiscard]] Result<std::string> finalize(std::string sdp);

    Config       mConfig;
    Hooks        mHooks;
    Role         mRole;
    proto::BatchCodec mCodec;

    mutable std::recursive_mutex      mMutex;
    std::condition_variable_any       mCondition;
    std::unique_ptr<rtc::PeerConnection> mPeer;
    std::shared_ptr<rtc::DataChannel> mReliable;
    std::shared_ptr<rtc::DataChannel> mUnreliable;

    struct Partial {
        std::uint8_t expected{};
        Bytes        data;
    };
    std::optional<Partial> mPartial;

    bool mGatheringComplete{};
    bool mOpen{};
    bool mClosed{};
    bool mCloseReported{};
    /// The login window is where a relay silently breaks; log the first few
    /// messages each way with a byte preview, then stop to keep the volume sane.
    std::uint32_t mLoggedSends{};
    std::uint32_t mLoggedReceives{};
};

} // namespace crosslink::net::nethernet