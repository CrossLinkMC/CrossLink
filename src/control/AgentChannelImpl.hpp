#pragma once

#include "crosslink/api/control/ControlChannel.hpp"

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cstdint>
#include <map>
#include <memory>
#include <mutex>
#include <string>

#ifdef CROSSLINK_PLATFORM_WINDOWS
#include <winsock2.h>
using SocketHandle = SOCKET;
inline constexpr SocketHandle invalidSocket = INVALID_SOCKET;
#else
using SocketHandle = int;
inline constexpr SocketHandle invalidSocket = -1;
#endif

namespace crosslink::control {

/// One authenticated agent connection. Owns the socket, the JSON Lines framing,
/// and the request/reply correlation table.
class AgentChannelImpl final : public AgentChannel {
public:
    AgentChannelImpl(AgentId id, ServerId server, std::string remote, SocketHandle socket);
    ~AgentChannelImpl() override;

    AgentChannelImpl(AgentChannelImpl const&)            = delete;
    AgentChannelImpl& operator=(AgentChannelImpl const&) = delete;

    [[nodiscard]] AgentId     id() const override;
    [[nodiscard]] ServerId    server() const override;
    [[nodiscard]] std::string remote() const override;
    [[nodiscard]] bool        online() const override;
    [[nodiscard]] Json        capabilities() const override;

    [[nodiscard]] Result<>   notify(std::string_view kind, Json payload = {}) const override;
    [[nodiscard]] Result<Json> request(std::string_view kind, Json payload, std::chrono::milliseconds timeout) const override;
    [[nodiscard]] Result<>   requestAsync(std::string_view kind, Json payload, ResponseHandler handler,
                                          std::chrono::milliseconds timeout) const override;

    void close(std::string_view reason) noexcept override;

    // ---- host side ----------------------------------------------------
    void setCapabilities(Json capabilities);
    /// Writes one JSON object followed by '\n'. Thread safe.
    [[nodiscard]] bool sendLine(Json const& json) const;
    /// Correlates a reply, or dispatches a request/notification.
    void handleInbound(Message const& message);
    /// Called by the reader thread when the socket went away.
    void failAllPending(std::string_view reason);
    /// Resolves requests whose deadline passed; driven by the host's watchdog.
    void expireRequests();
    void touch() const noexcept;
    [[nodiscard]] bool silentFor(std::chrono::seconds limit) const noexcept;
    [[nodiscard]] SocketHandle socket() const noexcept { return mSocket; }

private:
    struct Pending {
        std::mutex               mutex;
        std::condition_variable  condition;
        bool                     done{};
        Result<Json>             result{std::unexpected(Error{"the agent did not answer"})};
        ResponseHandler          handler;
        std::chrono::steady_clock::time_point deadline{};
    };

    [[nodiscard]] Result<Json> sendRequest(std::string_view kind, Json payload, std::chrono::milliseconds timeout,
                                           ResponseHandler handler) const;

    AgentId                              mId;
    ServerId                             mServer;
    std::string                          mRemote;
    mutable std::recursive_mutex         mSendMutex;
    SocketHandle                         mSocket;
    mutable std::atomic<std::uint64_t>   mNextRequestId{1};
    mutable std::mutex                   mPendingMutex;
    mutable std::map<std::uint64_t, std::shared_ptr<Pending>> mPending;
    mutable std::mutex                   mCapabilitiesMutex;
    Json                                 mCapabilities = Json::object();
    mutable std::atomic_bool             mOnline{true};
    mutable std::atomic<std::chrono::steady_clock::time_point> mLastTraffic{std::chrono::steady_clock::now()};
};

} // namespace crosslink::control
