#pragma once

// NetherNet's HTTP signalling, which BDS serves on the same port number as the
// game socket: GET /v1/join answers a ping, POST /v1/join/{networkId} trades an
// SDP offer for an answer. A connection whose first byte opens a TLS record is
// served over TLS when a certificate is configured and refused at once when not,
// which is what makes a client fall back to plain HTTP.

#include "crosslink/api/Result.hpp"
#include "crosslink/api/Types.hpp"

#include <chrono>
#include <cstdint>
#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <string_view>

namespace crosslink::net::nethernet {

/// What a probe tells the client before it commits to joining.
struct ServerPing {
    std::string   name;
    std::uint32_t protocol{};
    std::string   version;
    std::string   level{"Bedrock level"};
    std::uint32_t players{};
    std::uint32_t maxPlayers{};
    std::int32_t  gameType{};

    [[nodiscard]] std::string toJson() const;
};

/// NetherNet's session error codes, as they appear in a refusal body.
enum class SessionError : std::uint32_t {
    None                       = 0,
    NegotiationTimeout         = 2,
    FailedToCreatePeerConnection = 4,
    Ice                        = 5,
    InactivityTimeout          = 9,
    FailedToCreateAnswer       = 11,
    FailedToSetRemoteDescription = 13,
    IncomingConnectionIgnored  = 16,
    SignalingParsingFailure    = 17,
    NoSignalingChannel         = 24,
    SignalingFailedToSend      = 26,
    DataChannelClosed          = 32,
    GenericFailure             = 35,
    FailedToCreateIdentityAssertion = 36,
    IdentityNotAllowed         = 37,
};

struct TlsConfig {
    /// Both empty disables TLS: a ClientHello is answered with a fatal
    /// handshake_failure alert so the client retries in plain HTTP immediately.
    std::string certificateChainFile;
    std::string privateKeyFile;
};

struct SignalingLimits {
    std::size_t             maxRequestBytes{65536};
    std::chrono::milliseconds requestTimeout{std::chrono::seconds{10}};
    std::chrono::milliseconds writeTimeout{std::chrono::seconds{10}};
    /// How long a join may take to produce an answer before it becomes a 504.
    std::chrono::milliseconds joinTimeout{std::chrono::seconds{10}};
};

/// Completes one join exactly once, from any thread.
class JoinResponse {
public:
    JoinResponse() = default;

    void answer(std::string sdp) const;
    void reject(SessionError error) const;

private:
    friend class SignalingServer;
    struct Pending;
    explicit JoinResponse(std::shared_ptr<Pending> pending);
    std::shared_ptr<Pending> mPending;
};

struct JoinRequest {
    std::string networkId;
    /// The offer exactly as the client sent it, a=identity included.
    std::string offer;
    std::string remoteAddress;
    /// The port the client dialled, from the Host header when it named one.
    std::optional<std::uint16_t> hostPort;
};

struct SignalingHooks {
    /// `protocol` and `version` are what the client asked for; the answer should
    /// echo the protocol when it is supported and advertise the newest otherwise.
    std::function<ServerPing(std::optional<std::uint32_t> protocol, std::string_view version)> onPing;
    std::function<void(JoinRequest const&, JoinResponse)>                                      onJoin;
};

class SignalingServer {
public:
    SignalingServer(std::string host, std::uint16_t port, SignalingHooks hooks, SignalingLimits limits, TlsConfig tls);
    ~SignalingServer();

    SignalingServer(SignalingServer const&)            = delete;
    SignalingServer& operator=(SignalingServer const&) = delete;

    [[nodiscard]] Result<> start();
    void                   stop() noexcept;
    [[nodiscard]] std::uint16_t port() const noexcept;

private:
    struct Impl;
    std::unique_ptr<Impl> mImpl;
};

/// The dialer's half. A probe is one GET; a dial is a GET followed by a POST,
/// each on a fresh connection, trying TLS first and falling back to plain HTTP
/// only when the TLS attempt produced no response at all.
class SignalingClient {
public:
    struct Limits {
        std::chrono::milliseconds connectTimeout{std::chrono::seconds{5}};
        std::chrono::milliseconds requestTimeout{std::chrono::seconds{10}};
        std::size_t             maxResponseBytes{65536};
    };

    /// A 2xx to GET /v1/join means the target speaks NetherNet. The body may be
    /// empty (BDS with LAN visibility off), which still counts as supported.
    [[nodiscard]] static Result<std::optional<ServerPing>> probe(
        std::string_view host,
        std::uint16_t    port,
        Limits           limits = {}
    );

    /// Returns the answer SDP, or the session error the body carried.
    [[nodiscard]] static Result<std::string> requestAnswer(
        std::string_view host,
        std::uint16_t    port,
        std::string_view networkId,
        std::string_view offer,
        Limits           limits = {}
    );
};

} // namespace crosslink::net::nethernet