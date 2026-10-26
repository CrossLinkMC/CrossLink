#pragma once

#include "control/AgentChannelImpl.hpp"
#include "crosslink/api/Config.hpp"

#include <atomic>
#include <cstdint>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

namespace crosslink {

class Gateway;

namespace control {

/// The TCP endpoint backend agents dial into.
///
/// Framing is JSON Lines; the first message on a connection must be a `hello`
/// carrying the shared token and the server id the agent runs on. Only then is a
/// channel registered and the connection handed to plugins through
/// `AgentRegistry`. Everything after that is request/reply or notification, and
/// the host interprets nothing beyond hello, ping and pong.
class ControlServer {
public:
    explicit ControlServer(Gateway& gateway);
    ~ControlServer();

    ControlServer(ControlServer const&)            = delete;
    ControlServer& operator=(ControlServer const&) = delete;

    [[nodiscard]] Result<> start(config::ControlConfig const& config);
    void                   stop() noexcept;

    [[nodiscard]] std::size_t channelCount() const;

private:
    void acceptLoop();
    void connectionLoop(SocketHandle socket, std::string remote);
    void watchdogLoop();
    void registerChannel(std::shared_ptr<AgentChannelImpl> const& channel);
    void dropChannel(std::shared_ptr<AgentChannelImpl> const& channel, std::string_view reason);

    Gateway&                                   mGateway;
    config::ControlConfig                      mConfig;
    std::atomic_bool                           mStopping{false};
    SocketHandle                               mListener{invalidSocket};
    std::thread                                mAcceptThread;
    std::thread                                mWatchdogThread;
    mutable std::mutex                         mMutex;
    std::vector<std::shared_ptr<AgentChannelImpl>> mChannels;
    std::atomic<std::uint64_t>                 mNextAgentId{1};
    bool                                       mWinsockStarted{};
};

} // namespace control
} // namespace crosslink
