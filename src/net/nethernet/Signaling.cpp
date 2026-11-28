#include "net/nethernet/Signaling.hpp"

#include "crosslink/api/Logger.hpp"

#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <ws2tcpip.h>

#include <openssl/err.h>
#include <openssl/ssl.h>

#include <nlohmann/json.hpp>

#include <algorithm>
#include <array>
#include <atomic>
#include <charconv>
#include <condition_variable>
#include <exception>
#include <format>
#include <mutex>
#include <span>
#include <thread>
#include <utility>
#include <vector>

namespace crosslink::net::nethernet {
namespace {

using Json  = nlohmann::ordered_json;
using Clock = std::chrono::steady_clock;

constexpr std::string_view kJoinPath   = "/v1/join";
constexpr std::string_view kJoinPrefix = "/v1/join/";
constexpr std::string_view kUserAgent  = "libhttpclient/1.0.0.0";

/// A fatal handshake_failure alert, sent verbatim when no certificate is
/// configured: it is what makes a client retry in plain HTTP immediately.
constexpr std::string_view kHandshakeFailureAlert{"\x15\x03\x01\x00\x02\x02\x28", 7};

constexpr std::size_t kMaxConnections  = 32;
constexpr std::size_t kTlsDrainBytes   = 16384;
constexpr int         kIoChunkBytes    = 8192;
constexpr auto        kPollSlice       = std::chrono::milliseconds{200};
constexpr auto        kTlsDrainWindow  = std::chrono::milliseconds{100};
constexpr auto        kTlsCloseWindow  = std::chrono::seconds{1};

Logger& log() { return logger("nethernet"); }

// ---- small text helpers -------------------------------------------------

[[nodiscard]] bool isDigit(char ch) noexcept { return ch >= '0' && ch <= '9'; }

[[nodiscard]] std::string_view trimOws(std::string_view text) noexcept {
    const auto first = text.find_first_not_of(" \t");
    if (first == std::string_view::npos) return {};
    return text.substr(first, text.find_last_not_of(" \t") - first + 1);
}

[[nodiscard]] std::string_view trimSpace(std::string_view text) noexcept {
    const auto first = text.find_first_not_of(" \t\r\n");
    if (first == std::string_view::npos) return {};
    return text.substr(first, text.find_last_not_of(" \t\r\n") - first + 1);
}

[[nodiscard]] std::string lowerCase(std::string_view text) {
    std::string out{text};
    for (char& ch : out) {
        if (ch >= 'A' && ch <= 'Z') ch = static_cast<char>(ch - 'A' + 'a');
    }
    return out;
}

/// Pure decimal, whole string: a sign, whitespace or trailing junk must not parse.
template <typename T>
[[nodiscard]] std::optional<T> parseDecimal(std::string_view text) {
    if (text.empty()) return std::nullopt;
    for (const char ch : text) {
        if (!isDigit(ch)) return std::nullopt;
    }
    T value{};
    const auto result = std::from_chars(text.data(), text.data() + text.size(), value);
    if (result.ec != std::errc{} || result.ptr != text.data() + text.size()) return std::nullopt;
    return value;
}

/// Tolerant number parse for ping fields, which some peers send as strings.
template <typename T>
[[nodiscard]] std::optional<T> parseNumber(std::string_view text) {
    if (text.empty()) return std::nullopt;
    T value{};
    const auto result = std::from_chars(text.data(), text.data() + text.size(), value);
    if (result.ec != std::errc{} || result.ptr != text.data() + text.size()) return std::nullopt;
    return value;
}

[[nodiscard]] std::vector<std::string_view> splitLines(std::string_view head) {
    std::vector<std::string_view> lines;
    std::size_t                   start = 0;
    while (start < head.size()) {
        const auto end = head.find("\r\n", start);
        if (end == std::string_view::npos) {
            lines.push_back(head.substr(start));
            break;
        }
        lines.push_back(head.substr(start, end - start));
        start = end + 2;
    }
    return lines;
}

[[nodiscard]] std::string unbracket(std::string_view host) {
    if (host.size() >= 2 && host.front() == '[' && host.back() == ']') return std::string{host.substr(1, host.size() - 2)};
    return std::string{host};
}

[[nodiscard]] bool isIpLiteral(std::string_view host) {
    const std::string text = unbracket(host);
    in_addr           v4{};
    in6_addr          v6{};
    return ::inet_pton(AF_INET, text.c_str(), &v4) == 1 || ::inet_pton(AF_INET6, text.c_str(), &v6) == 1;
}

/// Host always names the port, and an IPv6 literal has to be bracketed.
[[nodiscard]] std::string authority(std::string_view host, std::uint16_t port) {
    if (host.find(':') != std::string_view::npos && !host.starts_with('[')) return std::format("[{}]:{}", host, port);
    return std::format("{}:{}", host, port);
}

[[nodiscard]] std::string addressText(sockaddr_storage const& peer) {
    char text[INET6_ADDRSTRLEN] = {};
    if (peer.ss_family == AF_INET) {
        const auto* v4 = reinterpret_cast<sockaddr_in const*>(&peer);
        (void)::inet_ntop(AF_INET, &v4->sin_addr, text, sizeof(text));
    } else if (peer.ss_family == AF_INET6) {
        const auto* v6 = reinterpret_cast<sockaddr_in6 const*>(&peer);
        (void)::inet_ntop(AF_INET6, &v6->sin6_addr, text, sizeof(text));
    }
    return std::string{text};
}

[[nodiscard]] std::uint16_t addressPort(sockaddr_storage const& peer) noexcept {
    if (peer.ss_family == AF_INET) return ntohs(reinterpret_cast<sockaddr_in const*>(&peer)->sin_port);
    if (peer.ss_family == AF_INET6) return ntohs(reinterpret_cast<sockaddr_in6 const*>(&peer)->sin6_port);
    return 0;
}

// ---- sockets ------------------------------------------------------------

[[nodiscard]] bool ensureWinsock() noexcept {
    // One process-wide reference taken once and never released: signalling must
    // not tear winsock down under the game socket when it stops.
    static const bool ready = [] {
        WSADATA data{};
        return ::WSAStartup(MAKEWORD(2, 2), &data) == 0;
    }();
    return ready;
}

void setNonBlocking(SOCKET socket) noexcept {
    u_long mode = 1;
    (void)::ioctlsocket(socket, FIONBIO, &mode);
}

[[nodiscard]] std::string socketError() { return std::format("winsock error {}", ::WSAGetLastError()); }

/// Owns one socket. Closing it also unblocks any peer parked in a read.
class Socket {
public:
    Socket() noexcept = default;
    explicit Socket(SOCKET handle) noexcept : mHandle(handle) {}
    ~Socket() { reset(); }

    Socket(Socket const&)            = delete;
    Socket& operator=(Socket const&) = delete;

    Socket(Socket&& other) noexcept : mHandle(std::exchange(other.mHandle, INVALID_SOCKET)) {}
    Socket& operator=(Socket&& other) noexcept {
        if (this != &other) {
            reset();
            mHandle = std::exchange(other.mHandle, INVALID_SOCKET);
        }
        return *this;
    }

    [[nodiscard]] SOCKET get() const noexcept { return mHandle; }
    [[nodiscard]] bool   valid() const noexcept { return mHandle != INVALID_SOCKET; }

    void reset() noexcept {
        if (!valid()) return;
        (void)::shutdown(mHandle, SD_BOTH);
        (void)::closesocket(mHandle);
        mHandle = INVALID_SOCKET;
    }

private:
    SOCKET mHandle{INVALID_SOCKET};
};

struct AddrInfoDeleter {
    void operator()(addrinfo* info) const noexcept { ::freeaddrinfo(info); }
};
using AddrInfoPtr = std::unique_ptr<addrinfo, AddrInfoDeleter>;

struct SslCtxDeleter {
    void operator()(SSL_CTX* ctx) const noexcept { SSL_CTX_free(ctx); }
};
struct SslDeleter {
    void operator()(SSL* ssl) const noexcept { SSL_free(ssl); }
};
using SslCtxPtr = std::unique_ptr<SSL_CTX, SslCtxDeleter>;
using SslPtr    = std::unique_ptr<SSL, SslDeleter>;

/// select() in short slices so a worker notices stop() while a peer is silent,
/// with the deadline still bounding the whole operation.
[[nodiscard]] bool waitFor(
    SOCKET                   socket,
    Clock::time_point        deadline,
    bool                     forWrite,
    std::atomic<bool> const* stopping
) noexcept {
    while (true) {
        if (stopping != nullptr && stopping->load(std::memory_order_relaxed)) return false;
        const auto now = Clock::now();
        if (now >= deadline) return false;
        const auto slice  = std::min<Clock::duration>(deadline - now, kPollSlice);
        const auto micros = std::chrono::duration_cast<std::chrono::microseconds>(slice).count();

        fd_set set{};
        FD_ZERO(&set);
        FD_SET(socket, &set);
        timeval wait{};
        wait.tv_sec  = static_cast<long>(micros / 1000000);
        wait.tv_usec = static_cast<long>(micros % 1000000);
        const int ready =
            forWrite ? ::select(0, nullptr, &set, nullptr, &wait) : ::select(0, &set, nullptr, nullptr, &wait);
        if (ready > 0) return true;
        if (ready < 0) return false;
    }
}

[[nodiscard]] bool waitReadable(
    SOCKET                   socket,
    Clock::time_point        deadline,
    std::atomic<bool> const* stopping = nullptr
) noexcept {
    return waitFor(socket, deadline, false, stopping);
}

[[nodiscard]] bool waitWritable(
    SOCKET                   socket,
    Clock::time_point        deadline,
    std::atomic<bool> const* stopping = nullptr
) noexcept {
    return waitFor(socket, deadline, true, stopping);
}

// ---- TLS ----------------------------------------------------------------

[[nodiscard]] Result<SslCtxPtr> makeTlsContext(bool server) {
    SslCtxPtr ctx{SSL_CTX_new(server ? TLS_server_method() : TLS_client_method())};
    if (!ctx) return std::unexpected(Error{"cannot create a TLS context"});
    // NetherNet peers negotiate TLS 1.2 or 1.3 only; the legacy versions must not
    // be reachable even when the local OpenSSL defaults still allow them.
    SSL_CTX_set_options(ctx.get(), SSL_OP_NO_SSLv2 | SSL_OP_NO_SSLv3 | SSL_OP_NO_TLSv1 | SSL_OP_NO_TLSv1_1);
    if (SSL_CTX_set_min_proto_version(ctx.get(), TLS1_2_VERSION) != 1) {
        return std::unexpected(Error{"cannot require TLS 1.2 or newer"});
    }
    if (!server) {
        // NetherNet servers present self-signed certificates; the session is
        // authenticated by the identity assertion inside the SDP instead.
        SSL_CTX_set_verify(ctx.get(), SSL_VERIFY_NONE, nullptr);
    }
    return ctx;
}

void prepareSession(SSL* ssl, SOCKET socket) noexcept {
    SSL_set_fd(ssl, static_cast<int>(socket));
    // A write retried after WANT_WRITE may resume from a different offset.
    SSL_set_mode(ssl, SSL_MODE_ENABLE_PARTIAL_WRITE | SSL_MODE_ACCEPT_MOVING_WRITE_BUFFER);
}

[[nodiscard]] Result<> tlsHandshake(
    SSL*                     ssl,
    SOCKET                   socket,
    Clock::time_point        deadline,
    std::atomic<bool> const* stopping,
    bool                     server
) {
    while (true) {
        const int result = server ? SSL_accept(ssl) : SSL_connect(ssl);
        if (result == 1) return {};
        const int error = SSL_get_error(ssl, result);
        if (error == SSL_ERROR_WANT_READ) {
            if (!waitReadable(socket, deadline, stopping)) return std::unexpected(Error{"the TLS handshake timed out"});
            continue;
        }
        if (error == SSL_ERROR_WANT_WRITE) {
            if (!waitWritable(socket, deadline, stopping)) return std::unexpected(Error{"the TLS handshake timed out"});
            continue;
        }
        return std::unexpected(Error{std::format("the TLS handshake failed (SSL error {})", error)});
    }
}

void tlsShutdown(SSL* ssl, SOCKET socket, Clock::time_point deadline, std::atomic<bool> const* stopping) noexcept {
    while (Clock::now() < deadline) {
        const int result = SSL_shutdown(ssl);
        if (result == 1) return;
        if (result == 0) {
            // Our close_notify is out; the peer's may still be on its way.
            if (!waitReadable(socket, deadline, stopping)) return;
            continue;
        }
        const int error = SSL_get_error(ssl, result);
        if (error == SSL_ERROR_WANT_READ) {
            if (!waitReadable(socket, deadline, stopping)) return;
            continue;
        }
        if (error == SSL_ERROR_WANT_WRITE) {
            if (!waitWritable(socket, deadline, stopping)) return;
            continue;
        }
        return;
    }
}

/// One connection, plain or TLS. Both run non-blocking underneath because
/// SSL_read/SSL_write can want the opposite direction, which a socket receive
/// timeout cannot express.
class Stream {
public:
    Stream(SOCKET socket, SSL* ssl, std::atomic<bool> const* stopping) noexcept
    : mSocket(socket), mSsl(ssl), mStopping(stopping) {}

    /// Reads what is available; 0 means the peer closed its side.
    [[nodiscard]] Result<std::size_t> read(std::span<char> out, Clock::time_point deadline) {
        while (true) {
            if (mSsl == nullptr) {
                if (!waitReadable(mSocket, deadline, mStopping)) {
                    return std::unexpected(Error{"the peer stopped sending"});
                }
                const int received = ::recv(mSocket, out.data(), static_cast<int>(out.size()), 0);
                if (received > 0) return static_cast<std::size_t>(received);
                if (received == 0) return std::size_t{0};
                const int error = ::WSAGetLastError();
                if (error == WSAEWOULDBLOCK) continue;
                return std::unexpected(Error{std::format("recv failed: winsock error {}", error)});
            }
            const int received = SSL_read(mSsl, out.data(), static_cast<int>(out.size()));
            if (received > 0) return static_cast<std::size_t>(received);
            const int error = SSL_get_error(mSsl, received);
            if (error == SSL_ERROR_ZERO_RETURN) return std::size_t{0};
            // Peers that close without close_notify are common; treat that as the
            // end of the stream, exactly like a plain recv() returning 0.
            if (error == SSL_ERROR_SYSCALL) return std::size_t{0};
            if (error == SSL_ERROR_WANT_READ) {
                if (!waitReadable(mSocket, deadline, mStopping)) return std::unexpected(Error{"the peer stopped sending"});
                continue;
            }
            if (error == SSL_ERROR_WANT_WRITE) {
                if (!waitWritable(mSocket, deadline, mStopping)) return std::unexpected(Error{"the peer stopped sending"});
                continue;
            }
            return std::unexpected(Error{std::format("TLS read failed (SSL error {})", error)});
        }
    }

    [[nodiscard]] Result<> write(std::string_view data, Clock::time_point deadline) {
        std::size_t sent = 0;
        while (sent < data.size()) {
            const auto chunk = data.substr(sent, std::min<std::size_t>(data.size() - sent, kIoChunkBytes));
            int        written = 0;
            if (mSsl == nullptr) {
                if (!waitWritable(mSocket, deadline, mStopping)) return std::unexpected(Error{"the peer stopped reading"});
                written = ::send(mSocket, chunk.data(), static_cast<int>(chunk.size()), 0);
                if (written == SOCKET_ERROR) {
                    const int error = ::WSAGetLastError();
                    if (error == WSAEWOULDBLOCK) continue;
                    return std::unexpected(Error{std::format("send failed: winsock error {}", error)});
                }
            } else {
                written = SSL_write(mSsl, chunk.data(), static_cast<int>(chunk.size()));
                if (written <= 0) {
                    const int error = SSL_get_error(mSsl, written);
                    if (error == SSL_ERROR_WANT_READ) {
                        if (!waitReadable(mSocket, deadline, mStopping)) {
                            return std::unexpected(Error{"the peer stopped reading"});
                        }
                        continue;
                    }
                    if (error == SSL_ERROR_WANT_WRITE) {
                        if (!waitWritable(mSocket, deadline, mStopping)) {
                            return std::unexpected(Error{"the peer stopped reading"});
                        }
                        continue;
                    }
                    return std::unexpected(Error{std::format("TLS write failed (SSL error {})", error)});
                }
            }
            if (written <= 0) return std::unexpected(Error{"the connection closed while writing"});
            sent += static_cast<std::size_t>(written);
        }
        return {};
    }

private:
    SOCKET                   mSocket;
    SSL*                     mSsl;
    std::atomic<bool> const* mStopping;
};

// ---- HTTP ---------------------------------------------------------------

struct Request {
    std::string                  method;
    std::string                  path;
    std::string                  query;
    std::string                  body;
    std::optional<std::uint16_t> hostPort;
};

[[nodiscard]] std::string response(
    int              status,
    std::string_view reason,
    std::string_view contentType,
    std::string_view body
) {
    return std::format(
        "HTTP/1.1 {} {}\r\nContent-Type: {}\r\nContent-Length: {}\r\nConnection: close\r\n\r\n{}",
        status,
        reason,
        contentType,
        body.size(),
        body
    );
}

[[nodiscard]] std::string textResponse(int status, std::string_view reason, std::string_view body) {
    return response(status, reason, "text/plain", body);
}

[[nodiscard]] Result<std::optional<std::uint16_t>> parsePortSuffix(std::string_view suffix) {
    if (suffix.empty()) return std::optional<std::uint16_t>{};
    if (!suffix.starts_with(':')) return std::unexpected(Error{"a Host port must follow ':'"});
    const auto port = parseDecimal<std::uint32_t>(suffix.substr(1));
    if (!port || *port > 65535) return std::unexpected(Error{"a Host port must be a decimal <= 65535"});
    return static_cast<std::uint16_t>(*port);
}

/// Host is optional, but when present it must name exactly one authority: an
/// IPv6 literal has to be bracketed and a port has to be a decimal <= 65535.
[[nodiscard]] Result<std::optional<std::uint16_t>> parseHost(std::string_view value) {
    if (value.empty()) return std::unexpected(Error{"an empty Host header"});
    if (value.starts_with('[')) {
        const auto close = value.find(']');
        if (close == std::string_view::npos) return std::unexpected(Error{"an unterminated IPv6 Host literal"});
        const std::string literal{value.substr(1, close - 1)};
        in6_addr          address{};
        if (::inet_pton(AF_INET6, literal.c_str(), &address) != 1) {
            return std::unexpected(Error{"a bracketed Host must hold an IPv6 literal"});
        }
        return parsePortSuffix(value.substr(close + 1));
    }
    const auto colon = value.find(':');
    if (colon != std::string_view::npos && value.find(':', colon + 1) != std::string_view::npos) {
        return std::unexpected(Error{"an IPv6 Host literal must be bracketed"});
    }
    const auto host = colon == std::string_view::npos ? value : value.substr(0, colon);
    if (host.empty() || host.find_first_of(" \t") != std::string_view::npos) {
        return std::unexpected(Error{"a malformed Host header"});
    }
    return parsePortSuffix(colon == std::string_view::npos ? std::string_view{} : value.substr(colon));
}

/// Reads one whole request: the head, then exactly Content-Length body bytes.
/// Every failure here means "close without answering".
[[nodiscard]] Result<Request> readRequest(Stream& stream, SignalingLimits const& limits, Clock::time_point deadline) {
    std::string                buffer;
    std::array<char, kIoChunkBytes> chunk{};
    std::size_t                headEnd = std::string::npos;
    while (headEnd == std::string::npos) {
        if (buffer.size() >= limits.maxRequestBytes) return std::unexpected(Error{"the request head is too large"});
        CROSSLINK_ASSIGN(received, stream.read(std::span<char>{chunk.data(), chunk.size()}, deadline));
        if (*received == 0) return std::unexpected(Error{"the peer closed before sending a request"});
        buffer.append(chunk.data(), *received);
        headEnd = buffer.find("\r\n\r\n");
    }

    const std::size_t headBytes = headEnd + 4;
    if (headBytes > limits.maxRequestBytes) return std::unexpected(Error{"the request head is too large"});
    const auto lines = splitLines(std::string_view{buffer.data(), headEnd});
    if (lines.empty()) return std::unexpected(Error{"an empty request head"});

    const auto requestLine = lines.front();
    const auto firstSpace  = requestLine.find(' ');
    const auto secondSpace = firstSpace == std::string_view::npos ? firstSpace : requestLine.find(' ', firstSpace + 1);
    if (firstSpace == std::string_view::npos || secondSpace == std::string_view::npos
        || requestLine.find(' ', secondSpace + 1) != std::string_view::npos) {
        return std::unexpected(Error{"a malformed request line"});
    }
    const auto method  = requestLine.substr(0, firstSpace);
    const auto target  = requestLine.substr(firstSpace + 1, secondSpace - firstSpace - 1);
    const auto version = requestLine.substr(secondSpace + 1);
    // A lowercase method is not a method at all, so it is dropped in silence.
    if (method.empty() || method.size() > 16) return std::unexpected(Error{"a malformed request method"});
    for (const char ch : method) {
        if (ch < 'A' || ch > 'Z') return std::unexpected(Error{"a malformed request method"});
    }
    if (!version.starts_with("HTTP/1.") || !target.starts_with('/')) {
        return std::unexpected(Error{"a malformed request line"});
    }

    Request request;
    request.method = std::string{method};
    const auto question = target.find('?');
    request.path  = std::string{question == std::string_view::npos ? target : target.substr(0, question)};
    request.query = std::string{question == std::string_view::npos ? std::string_view{} : target.substr(question + 1)};

    std::size_t                hostCount = 0;
    std::optional<std::size_t> contentLength;
    for (std::size_t index = 1; index < lines.size(); ++index) {
        const auto line  = lines[index];
        const auto colon = line.find(':');
        if (colon == std::string_view::npos) return std::unexpected(Error{"a malformed header line"});
        const auto name  = lowerCase(line.substr(0, colon));
        const auto value = trimOws(line.substr(colon + 1));
        if (name.empty() || name.find_first_of(" \t") != std::string_view::npos) {
            return std::unexpected(Error{"a malformed header name"});
        }
        if (name == "host") {
            if (++hostCount > 1) return std::unexpected(Error{"a duplicate Host header"});
            CROSSLINK_ASSIGN(port, parseHost(value));
            request.hostPort = *port;
        } else if (name == "content-length") {
            const auto length = parseDecimal<std::size_t>(value);
            if (!length) return std::unexpected(Error{"a malformed Content-Length"});
            if (contentLength && *contentLength != *length) {
                return std::unexpected(Error{"disagreeing Content-Length headers"});
            }
            contentLength = *length;
        }
    }

    const std::size_t wanted = contentLength.value_or(0);
    if (headBytes + wanted > limits.maxRequestBytes) return std::unexpected(Error{"the request body is too large"});
    request.body = buffer.substr(headEnd + 4);
    if (request.body.size() > wanted) request.body.resize(wanted);
    while (request.body.size() < wanted) {
        const auto want = std::min<std::size_t>(wanted - request.body.size(), chunk.size());
        CROSSLINK_ASSIGN(received, stream.read(std::span<char>{chunk.data(), want}, deadline));
        if (*received == 0) return std::unexpected(Error{"the request body ended early"});
        request.body.append(chunk.data(), *received);
    }
    return request;
}

[[nodiscard]] bool validNetworkId(std::string_view id) noexcept {
    if (id.empty() || id.size() > 128) return false;
    for (const char ch : id) {
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || isDigit(ch)) continue;
        if (ch == '-' || ch == '.' || ch == '_' || ch == '~' || ch == '%') continue;
        return false;
    }
    return true;
}

[[nodiscard]] std::string servePing(Request const& request, SignalingHooks const& hooks) {
    std::optional<std::uint32_t> protocol;
    std::string_view             version;
    std::string_view             query = request.query;
    while (!query.empty()) {
        const auto amp   = query.find('&');
        const auto pair  = query.substr(0, amp);
        query            = amp == std::string_view::npos ? std::string_view{} : query.substr(amp + 1);
        const auto equal = pair.find('=');
        const auto key   = equal == std::string_view::npos ? pair : pair.substr(0, equal);
        const auto value = equal == std::string_view::npos ? std::string_view{} : pair.substr(equal + 1);
        if (key == "protocol") {
            protocol = parseDecimal<std::uint32_t>(value);
        } else if (key == "version") {
            version = value;
        }
        // Everything else, notably id and platform, is deliberately ignored.
    }

    try {
        const ServerPing ping = hooks.onPing ? hooks.onPing(protocol, version) : ServerPing{};
        return response(200, "OK", "application/json", ping.toJson());
    } catch (std::exception const& error) {
        log().warn("the nethernet ping hook failed: {}", error.what());
        return textResponse(500, "Internal Server Error", "Internal Server Error");
    }
}

// ---- server state -------------------------------------------------------

struct Worker {
    std::thread thread;
    /// Shared with the running thread so a worker detached by stop() can still
    /// mark itself finished after the registry entry is gone.
    std::shared_ptr<std::atomic<bool>> finished{std::make_shared<std::atomic<bool>>(false)};
};

/// Everything a worker touches lives here and is shared with the workers: stop()
/// may be called from a handler thread, which cannot join itself and must still
/// find its state alive once the server object is destroyed.
struct State {
    std::string    host;
    std::uint16_t  port{};
    SignalingHooks hooks;
    SignalingLimits limits;
    TlsConfig      tls;
    SslCtxPtr      tlsContext;

    std::atomic<bool>          stopping{false};
    std::atomic<bool>          stopEntered{false};
    std::atomic<std::uint16_t> boundPort{0};
    std::atomic<SOCKET>        listener{INVALID_SOCKET};
    Socket                     listenerSocket;
    std::thread                acceptThread;

    std::mutex                           mutex;
    std::vector<std::shared_ptr<Worker>> workers;
};

/// Joins and drops the workers that have already finished. The lock is held.
void reapWorkers(State& state) {
    std::erase_if(state.workers, [](std::shared_ptr<Worker> const& worker) {
        if (!worker->finished->load(std::memory_order_acquire)) return false;
        if (worker->thread.joinable()) worker->thread.join();
        return true;
    });
}

struct BoundListener {
    Socket        socket;
    std::uint16_t port{};
};

[[nodiscard]] Result<BoundListener> bindListener(std::string const& host, std::uint16_t port) {
    addrinfo hints{};
    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags    = AI_PASSIVE;

    const std::string service = std::format("{}", port);
    addrinfo*         results = nullptr;
    if (::getaddrinfo(host.empty() ? nullptr : host.c_str(), service.c_str(), &hints, &results) != 0
        || results == nullptr) {
        return std::unexpected(Error{std::format("cannot resolve the signaling host '{}'", host)});
    }
    AddrInfoPtr owned{results};

    std::string lastError{"no usable address"};
    for (addrinfo* cursor = results; cursor != nullptr; cursor = cursor->ai_next) {
        Socket socket{::socket(cursor->ai_family, cursor->ai_socktype, cursor->ai_protocol)};
        if (!socket.valid()) {
            lastError = socketError();
            continue;
        }
        // No SO_REUSEADDR: on Windows it would let a second gateway share the
        // game port silently instead of failing loudly.
        if (::bind(socket.get(), cursor->ai_addr, static_cast<int>(cursor->ai_addrlen)) != 0) {
            lastError = socketError();
            continue;
        }
        if (::listen(socket.get(), SOMAXCONN) != 0) {
            lastError = socketError();
            continue;
        }
        sockaddr_storage bound{};
        int              boundSize = static_cast<int>(sizeof(bound));
        std::uint16_t    actual    = port;
        if (::getsockname(socket.get(), reinterpret_cast<sockaddr*>(&bound), &boundSize) == 0) {
            actual = addressPort(bound);
        }
        setNonBlocking(socket.get());
        return BoundListener{std::move(socket), actual};
    }
    return std::unexpected(Error{std::format("cannot listen on {}:{}: {}", host, port, lastError)});
}

/// Without a certificate the only useful answer to a ClientHello is a fatal
/// alert, so the client falls back to plain HTTP at once instead of timing out.
void refuseTls(State const& state, SOCKET socket) {
    const auto                    deadline = Clock::now() + kTlsDrainWindow;
    std::array<char, kIoChunkBytes> scratch{};
    std::size_t                   drained = 0;
    while (drained < kTlsDrainBytes) {
        if (!waitReadable(socket, deadline, &state.stopping)) break;
        const auto want     = static_cast<int>(std::min<std::size_t>(kTlsDrainBytes - drained, scratch.size()));
        const int  received = ::recv(socket, scratch.data(), want, 0);
        if (received <= 0) break;
        drained += static_cast<std::size_t>(received);
    }
    Stream stream{socket, nullptr, &state.stopping};
    (void)stream.write(kHandshakeFailureAlert, Clock::now() + state.limits.writeTimeout);
}

// ---- client -------------------------------------------------------------

struct HttpResponse {
    int         status{};
    std::string body;
};

[[nodiscard]] Result<Socket> connectTcp(
    std::string_view          host,
    std::uint16_t             port,
    std::chrono::milliseconds timeout
) {
    if (!ensureWinsock()) return std::unexpected(Error{"WSAStartup failed"});

    addrinfo hints{};
    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    const std::string node    = unbracket(host);
    const std::string service = std::format("{}", port);
    addrinfo*         results = nullptr;
    if (::getaddrinfo(node.c_str(), service.c_str(), &hints, &results) != 0 || results == nullptr) {
        return std::unexpected(Error{std::format("cannot resolve '{}'", host)});
    }
    AddrInfoPtr owned{results};

    const auto  deadline = Clock::now() + timeout;
    std::string lastError{"no address to try"};
    for (addrinfo* cursor = results; cursor != nullptr; cursor = cursor->ai_next) {
        Socket socket{::socket(cursor->ai_family, cursor->ai_socktype, cursor->ai_protocol)};
        if (!socket.valid()) {
            lastError = socketError();
            continue;
        }
        setNonBlocking(socket.get());
        if (::connect(socket.get(), cursor->ai_addr, static_cast<int>(cursor->ai_addrlen)) == 0) return socket;
        const int error = ::WSAGetLastError();
        if (error != WSAEWOULDBLOCK && error != WSAEINPROGRESS) {
            lastError = std::format("winsock error {}", error);
            continue;
        }
        if (!waitWritable(socket.get(), deadline)) {
            lastError = "the connect timed out";
            continue;
        }
        int soError = 0;
        int length  = static_cast<int>(sizeof(soError));
        if (::getsockopt(socket.get(), SOL_SOCKET, SO_ERROR, reinterpret_cast<char*>(&soError), &length) != 0
            || soError != 0) {
            lastError = std::format("winsock error {}", soError);
            continue;
        }
        return socket;
    }
    return std::unexpected(Error{std::format("cannot connect to {}:{}: {}", host, port, lastError)});
}

[[nodiscard]] Result<HttpResponse> readResponse(
    Stream&                       stream,
    SignalingClient::Limits const& limits,
    Clock::time_point             deadline
) {
    std::string                     buffer;
    std::array<char, kIoChunkBytes> chunk{};
    std::size_t                     headEnd = std::string::npos;
    while (headEnd == std::string::npos) {
        if (buffer.size() >= limits.maxResponseBytes) return std::unexpected(Error{"the response head is too large"});
        CROSSLINK_ASSIGN(received, stream.read(std::span<char>{chunk.data(), chunk.size()}, deadline));
        if (*received == 0) break;
        buffer.append(chunk.data(), *received);
        headEnd = buffer.find("\r\n\r\n");
    }
    if (headEnd == std::string::npos) return std::unexpected(Error{"the response ended before its head"});

    const auto lines = splitLines(std::string_view{buffer.data(), headEnd});
    if (lines.empty()) return std::unexpected(Error{"an empty response head"});
    const auto statusLine = lines.front();
    const auto space      = statusLine.find(' ');
    if (space == std::string_view::npos) return std::unexpected(Error{"a malformed status line"});
    const auto codeText = statusLine.substr(space + 1, 3);
    const auto status   = parseDecimal<int>(codeText);
    if (!status || !statusLine.starts_with("HTTP/")) return std::unexpected(Error{"a malformed status line"});

    std::optional<std::size_t> contentLength;
    for (std::size_t index = 1; index < lines.size(); ++index) {
        const auto colon = lines[index].find(':');
        if (colon == std::string_view::npos) continue;
        if (lowerCase(lines[index].substr(0, colon)) != "content-length") continue;
        contentLength = parseDecimal<std::size_t>(trimOws(lines[index].substr(colon + 1)));
    }

    std::string body = buffer.substr(headEnd + 4);
    if (contentLength) {
        if (*contentLength > limits.maxResponseBytes) return std::unexpected(Error{"the response body is too large"});
        while (body.size() < *contentLength) {
            const auto want = std::min<std::size_t>(*contentLength - body.size(), chunk.size());
            CROSSLINK_ASSIGN(received, stream.read(std::span<char>{chunk.data(), want}, deadline));
            if (*received == 0) break;
            body.append(chunk.data(), *received);
        }
        if (body.size() > *contentLength) body.resize(*contentLength);
    } else {
        // No length: the body runs to the close, still capped.
        while (body.size() < limits.maxResponseBytes) {
            const auto want = std::min<std::size_t>(limits.maxResponseBytes - body.size(), chunk.size());
            CROSSLINK_ASSIGN(received, stream.read(std::span<char>{chunk.data(), want}, deadline));
            if (*received == 0) break;
            body.append(chunk.data(), *received);
        }
    }
    return HttpResponse{*status, std::move(body)};
}

/// One request over a fresh connection. A failure here means no response at all,
/// which is the only outcome that may fall back to the other transport.
[[nodiscard]] Result<HttpResponse> exchange(
    std::string_view               host,
    std::uint16_t                  port,
    std::string_view               request,
    SignalingClient::Limits const& limits,
    bool                           useTls
) {
    CROSSLINK_ASSIGN(socket, connectTcp(host, port, limits.connectTimeout));
    const auto deadline = Clock::now() + limits.requestTimeout;

    SslPtr ssl;
    if (useTls) {
        CROSSLINK_ASSIGN(context, makeTlsContext(false));
        ssl = SslPtr{SSL_new(context->get())};
        if (!ssl) return std::unexpected(Error{"cannot create a TLS session"});
        prepareSession(ssl.get(), socket->get());
        const std::string name = unbracket(host);
        // RFC 6066 forbids an IP literal in SNI.
        if (!isIpLiteral(name)) SSL_set_tlsext_host_name(ssl.get(), name.c_str());
        CROSSLINK_PROPAGATE(tlsHandshake(ssl.get(), socket->get(), deadline, nullptr, false));
    }

    Stream stream{socket->get(), ssl.get(), nullptr};
    CROSSLINK_PROPAGATE(stream.write(request, deadline));
    return readResponse(stream, limits, deadline);
}

[[nodiscard]] Result<HttpResponse> exchangeWithFallback(
    std::string_view               host,
    std::uint16_t                  port,
    std::string_view               request,
    SignalingClient::Limits const& limits
) {
    auto overTls = exchange(host, port, request, limits, true);
    // An HTTP status, even 4xx or 5xx, is a final answer: only a transport
    // failure may fall back to plain HTTP.
    if (overTls) return overTls;
    log().debug("nethernet TLS to {}:{} failed ({}); retrying in plain HTTP", host, port, overTls.error().message);
    return exchange(host, port, request, limits, false);
}

[[nodiscard]] std::string pingRequest(std::string_view host, std::uint16_t port) {
    return std::format(
        "GET /v1/join HTTP/1.1\r\nHost: {}\r\nUser-Agent: {}\r\nAccept: */*\r\nConnection: Keep-Alive\r\n\r\n",
        authority(host, port),
        kUserAgent
    );
}

[[nodiscard]] std::string joinRequest(
    std::string_view host,
    std::uint16_t    port,
    std::string_view networkId,
    std::string_view offer
) {
    return std::format(
        "POST /v1/join/{} HTTP/1.1\r\nHost: {}\r\nUser-Agent: {}\r\nContent-Type: application/sdp\r\n"
        "Connection: Keep-Alive\r\nContent-Length: {}\r\n\r\n{}",
        networkId,
        authority(host, port),
        kUserAgent,
        offer.size(),
        offer
    );
}

[[nodiscard]] std::string jsonText(Json const& json, std::string_view key) {
    const auto found = json.find(std::string{key});
    if (found == json.end() || !found->is_string()) return {};
    return found->get<std::string>();
}

template <typename T>
[[nodiscard]] T jsonNumber(Json const& json, std::string_view key, T fallback) {
    const auto found = json.find(std::string{key});
    if (found == json.end()) return fallback;
    if (found->is_number_integer() || found->is_number_unsigned()) return static_cast<T>(found->get<std::int64_t>());
    if (found->is_number_float()) return static_cast<T>(found->get<double>());
    if (found->is_string()) return parseNumber<T>(found->get<std::string>()).value_or(fallback);
    return fallback;
}

[[nodiscard]] ServerPing pingFromJson(Json const& json) {
    ServerPing ping;
    ping.name       = jsonText(json, "name");
    ping.protocol   = jsonNumber<std::uint32_t>(json, "protocol", 0);
    ping.version    = jsonText(json, "version");
    ping.players    = jsonNumber<std::uint32_t>(json, "players", 0);
    ping.maxPlayers = jsonNumber<std::uint32_t>(json, "maxPlayers", 0);
    ping.gameType   = jsonNumber<std::int32_t>(json, "gameType", 0);
    // The level name keeps its default unless the server actually named one.
    if (const auto found = json.find("level"); found != json.end() && found->is_string()) {
        ping.level = found->get<std::string>();
    }
    return ping;
}

} // namespace

// ---- ServerPing ---------------------------------------------------------

std::string ServerPing::toJson() const {
    // ordered_json keeps the key order NetherNet clients expect, and dump()
    // without an indent is the compact form.
    Json json;
    json["name"]       = name;
    json["protocol"]   = protocol;
    json["version"]    = version;
    json["level"]      = level;
    json["players"]    = players;
    json["maxPlayers"] = maxPlayers;
    json["gameType"]   = gameType;
    return json.dump();
}

// ---- JoinResponse -------------------------------------------------------

struct JoinResponse::Pending {
    std::mutex                 mutex;
    std::condition_variable    ready;
    bool                       done{false};
    std::optional<std::string> answer;
    SessionError               error{SessionError::None};
};

JoinResponse::JoinResponse(std::shared_ptr<Pending> pending) : mPending(std::move(pending)) {}

void JoinResponse::answer(std::string sdp) const {
    if (!mPending) return;
    {
        std::lock_guard lock{mPending->mutex};
        if (mPending->done) return;
        mPending->answer = std::move(sdp);
        mPending->done   = true;
    }
    mPending->ready.notify_all();
}

void JoinResponse::reject(SessionError error) const {
    if (!mPending) return;
    {
        std::lock_guard lock{mPending->mutex};
        if (mPending->done) return;
        mPending->error = error;
        mPending->done  = true;
    }
    mPending->ready.notify_all();
}

// ---- SignalingServer ----------------------------------------------------

struct SignalingServer::Impl {
    std::shared_ptr<State> state{std::make_shared<State>()};

    [[nodiscard]] Result<> start();
    void                   stop() noexcept;

    // Static, and taking the shared state, so a worker detached by stop() can
    // finish without an Impl instance. serveJoin lives here because Pending is
    // private to JoinResponse and only a member of this class may reach it.
    static void acceptLoop(std::shared_ptr<State> state);
    static void handleConnection(State& state, Socket socket, std::string remote);
    static void serveHttp(State& state, Stream& stream, std::string_view remote, Clock::time_point deadline);
    [[nodiscard]] static std::string serveJoin(
        State const&     state,
        Request const&   request,
        std::string_view remote
    );
};

Result<> SignalingServer::Impl::start() {
    if (!ensureWinsock()) return std::unexpected(Error{"WSAStartup failed"});
    if (state->listener.load() != INVALID_SOCKET) {
        return std::unexpected(Error{"the signaling server is already running"});
    }

    // The certificate is loaded once here so a bad path fails start() rather
    // than every single connection.
    const bool hasChain = !state->tls.certificateChainFile.empty();
    const bool hasKey   = !state->tls.privateKeyFile.empty();
    if (hasChain && hasKey) {
        CROSSLINK_ASSIGN(context, makeTlsContext(true));
        if (SSL_CTX_use_certificate_chain_file(context->get(), state->tls.certificateChainFile.c_str()) != 1) {
            return std::unexpected(
                Error{std::format("cannot load the nethernet certificate chain '{}'", state->tls.certificateChainFile)}
            );
        }
        if (SSL_CTX_use_PrivateKey_file(context->get(), state->tls.privateKeyFile.c_str(), SSL_FILETYPE_PEM) != 1) {
            return std::unexpected(
                Error{std::format("cannot load the nethernet private key '{}'", state->tls.privateKeyFile)}
            );
        }
        if (SSL_CTX_check_private_key(context->get()) != 1) {
            return std::unexpected(Error{"the nethernet private key does not match the certificate"});
        }
        state->tlsContext = std::move(*context);
    } else if (hasChain || hasKey) {
        log().warn("nethernet TLS needs both a certificate chain and a private key; serving plain HTTP only");
    }

    CROSSLINK_ASSIGN(bound, bindListener(state->host, state->port));
    state->boundPort.store(bound->port);
    state->listener.store(bound->socket.get(), std::memory_order_release);
    state->stopping.store(false, std::memory_order_release);
    state->stopEntered.store(false, std::memory_order_release);
    // The listener stays owned here; the accept loop only borrows the handle.
    state->listenerSocket = std::move(bound->socket);
    state->acceptThread   = std::thread([shared = state] { acceptLoop(shared); });

    log().info(
        "nethernet signaling listening on {}:{} ({})",
        state->host.empty() ? std::string{"*"} : state->host,
        bound->port,
        state->tlsContext ? "TLS and plain HTTP" : "plain HTTP"
    );
    return {};
}

void SignalingServer::Impl::stop() noexcept {
    const auto shared = state;
    if (!shared || shared->stopEntered.exchange(true)) return;
    shared->stopping.store(true, std::memory_order_release);

    if (shared->acceptThread.joinable()) {
        if (shared->acceptThread.get_id() == std::this_thread::get_id()) shared->acceptThread.detach();
        else shared->acceptThread.join();
    }
    // The accept loop is gone, so the handle can be retired without a race.
    if (shared->listener.exchange(INVALID_SOCKET) != INVALID_SOCKET) shared->listenerSocket.reset();

    std::vector<std::shared_ptr<Worker>> workers;
    {
        std::lock_guard lock{shared->mutex};
        workers.swap(shared->workers);
    }
    for (auto& worker : workers) {
        if (!worker->thread.joinable()) continue;
        // A handler may call stop(); joining itself would deadlock, so it is
        // detached and finishes on the state it already owns.
        if (worker->thread.get_id() == std::this_thread::get_id()) {
            worker->thread.detach();
            continue;
        }
        try {
            worker->thread.join();
        } catch (...) {
            worker->thread.detach();
        }
    }
}

void SignalingServer::Impl::acceptLoop(std::shared_ptr<State> shared) {
    State& state = *shared;
    while (!state.stopping.load(std::memory_order_relaxed)) {
        const SOCKET listener = state.listener.load(std::memory_order_acquire);
        if (listener == INVALID_SOCKET) break;
        if (!waitReadable(listener, Clock::now() + kPollSlice, &state.stopping)) continue;

        sockaddr_storage peer{};
        int              peerSize = static_cast<int>(sizeof(peer));
        const SOCKET     accepted = ::accept(listener, reinterpret_cast<sockaddr*>(&peer), &peerSize);
        if (accepted == INVALID_SOCKET) continue;
        std::string remote = addressText(peer);

        std::lock_guard lock{state.mutex};
        reapWorkers(state);
        if (state.workers.size() >= kMaxConnections) {
            // Bounded on purpose: a flood of silent connections must not be able
            // to exhaust the process's threads.
            (void)::closesocket(accepted);
            continue;
        }
        auto worker = std::make_shared<Worker>();
        auto done   = worker->finished;
        worker->thread = std::thread([shared, done, accepted, remote = std::move(remote)]() mutable {
            handleConnection(*shared, Socket{accepted}, std::move(remote));
            done->store(true, std::memory_order_release);
        });
        state.workers.push_back(std::move(worker));
    }
}

void SignalingServer::Impl::handleConnection(State& state, Socket socket, std::string remote) {
    // One deadline for the whole request, the TLS handshake included, measured
    // from accept.
    const auto   deadline = Clock::now() + state.limits.requestTimeout;
    const SOCKET handle   = socket.get();
    if (!waitReadable(handle, deadline, &state.stopping)) return;

    char      first  = 0;
    const int peeked = ::recv(handle, &first, 1, MSG_PEEK);
    if (peeked != 1) return;
    setNonBlocking(handle);

    if (static_cast<unsigned char>(first) != 0x16) {
        Stream stream{handle, nullptr, &state.stopping};
        serveHttp(state, stream, remote, deadline);
        return;
    }
    if (!state.tlsContext) {
        refuseTls(state, handle);
        return;
    }

    SslPtr ssl{SSL_new(state.tlsContext.get())};
    if (!ssl) return;
    prepareSession(ssl.get(), handle);
    if (auto result = tlsHandshake(ssl.get(), handle, deadline, &state.stopping, true); !result) {
        log().debug("nethernet dropped a TLS connection from {}: {}", remote, result.error().message);
        return;
    }
    Stream stream{handle, ssl.get(), &state.stopping};
    serveHttp(state, stream, remote, deadline);
    tlsShutdown(ssl.get(), handle, Clock::now() + kTlsCloseWindow, &state.stopping);
}

void SignalingServer::Impl::serveHttp(
    State&            state,
    Stream&           stream,
    std::string_view  remote,
    Clock::time_point deadline
) {
    auto request = readRequest(stream, state.limits, deadline);
    if (!request) {
        log().debug("nethernet dropped a request from {}: {}", remote, request.error().message);
        return;
    }

    std::string answer;
    if (request->method == "GET" && std::string_view{request->path} == kJoinPath) {
        answer = servePing(*request, state.hooks);
    } else if (request->method == "POST" && request->path.starts_with(kJoinPrefix)) {
        answer = serveJoin(state, *request, remote);
    } else {
        answer = textResponse(404, "Not Found", "Not Found");
    }
    (void)stream.write(answer, Clock::now() + state.limits.writeTimeout);
}

std::string SignalingServer::Impl::serveJoin(State const& state, Request const& request, std::string_view remote) {
    const std::string networkId = request.path.substr(kJoinPrefix.size());
    if (!validNetworkId(networkId)) {
        return textResponse(400, "Expected /v1/join/{networkId}", "Expected /v1/join/{networkId}");
    }
    if (request.body.empty()) {
        return textResponse(400, "Missing SDP offer in request body", "Missing SDP offer in request body");
    }

    auto         pending = std::make_shared<JoinResponse::Pending>();
    JoinResponse responder{pending};

    JoinRequest join;
    join.networkId     = networkId;
    join.offer         = request.body;
    join.remoteAddress = std::string{remote};
    join.hostPort      = request.hostPort;

    if (!state.hooks.onJoin) {
        responder.reject(SessionError::GenericFailure);
    } else {
        try {
            state.hooks.onJoin(join, responder);
        } catch (std::exception const& error) {
            log().warn("the nethernet join hook failed for '{}': {}", join.networkId, error.what());
            responder.reject(SessionError::GenericFailure);
        }
    }

    const auto deadline = Clock::now() + state.limits.joinTimeout;
    {
        std::unique_lock lock{pending->mutex};
        while (!pending->done && !state.stopping.load(std::memory_order_relaxed)) {
            const auto now = Clock::now();
            if (now >= deadline) break;
            pending->ready.wait_until(lock, std::min(now + kPollSlice, deadline));
        }
        if (!pending->done) return textResponse(504, "Gateway Timeout", "Gateway Timeout");
        if (pending->answer) return response(200, "OK", "application/sdp", *pending->answer);
        return response(200, "OK", "application/sdp", std::format("{}", static_cast<std::uint32_t>(pending->error)));
    }
}

SignalingServer::SignalingServer(
    std::string    host,
    std::uint16_t  port,
    SignalingHooks hooks,
    SignalingLimits limits,
    TlsConfig      tls
)
: mImpl(std::make_unique<Impl>()) {
    mImpl->state->host   = std::move(host);
    mImpl->state->port   = port;
    mImpl->state->hooks  = std::move(hooks);
    mImpl->state->limits = limits;
    mImpl->state->tls    = std::move(tls);
}

SignalingServer::~SignalingServer() { stop(); }

Result<> SignalingServer::start() {
    try {
        return mImpl->start();
    } catch (std::exception const& error) {
        return std::unexpected(Error{std::format("cannot start nethernet signaling: {}", error.what())});
    }
}

void SignalingServer::stop() noexcept {
    if (mImpl) mImpl->stop();
}

std::uint16_t SignalingServer::port() const noexcept { return mImpl ? mImpl->state->boundPort.load() : 0; }

// ---- SignalingClient ----------------------------------------------------

Result<std::optional<ServerPing>> SignalingClient::probe(std::string_view host, std::uint16_t port, Limits limits) {
    const auto request = pingRequest(host, port);
    CROSSLINK_ASSIGN(answer, exchangeWithFallback(host, port, request, limits));
    if (answer->status < 200 || answer->status > 299) {
        return std::unexpected(Error{std::format("nethernet probe: {}:{} answered HTTP {}", host, port, answer->status)});
    }

    const auto body = trimSpace(answer->body);
    // BDS with LAN visibility off answers 200 with no body, which still means
    // NetherNet is there; so does a body we cannot make sense of.
    if (body.empty()) return std::optional<ServerPing>{};
    const auto json = Json::parse(body, nullptr, false);
    if (json.is_discarded() || !json.is_object()) {
        log().debug("nethernet probe: {}:{} sent an unreadable ping body", host, port);
        return std::optional<ServerPing>{};
    }
    return pingFromJson(json);
}

Result<std::string> SignalingClient::requestAnswer(
    std::string_view host,
    std::uint16_t    port,
    std::string_view networkId,
    std::string_view offer,
    Limits           limits
) {
    // The GET first: a target that does not speak NetherNet must not be sent an
    // offer at all.
    CROSSLINK_ASSIGN(capability, probe(host, port, limits));

    const auto request = joinRequest(host, port, networkId, offer);
    auto       answer  = exchangeWithFallback(host, port, request, limits);
    if (!answer) {
        return std::unexpected(
            Error{std::format("nethernet signaling failed to send (26): {}", answer.error().message)}
        );
    }
    if (answer->status < 200 || answer->status > 299) {
        return std::unexpected(
            Error{std::format("nethernet signaling failed to send (26): {}:{} answered HTTP {}", host, port, answer->status)}
        );
    }

    const auto body = trimSpace(answer->body);
    if (body.starts_with("v=")) return std::string{body};
    // A refusal body is the bare decimal session error. Callers recognise it by
    // this exact prefix: "nethernet session error <code>".
    if (!body.empty() && std::all_of(body.begin(), body.end(), isDigit)) {
        return std::unexpected(Error{std::format("nethernet session error {}", body)});
    }
    return std::unexpected(
        Error{std::format("nethernet signaling parsing failure (17): {}:{} sent an unusable answer", host, port)}
    );
}

} // namespace crosslink::net::nethernet