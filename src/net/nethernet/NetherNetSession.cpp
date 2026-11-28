#include "net/nethernet/NetherNetSession.hpp"

#include "crosslink/api/Logger.hpp"
#include "net/nethernet/Sdp.hpp"

#include <rtc/datachannel.hpp>
#include <rtc/description.hpp>
#include <rtc/global.hpp>
#include <rtc/peerconnection.hpp>

#include <algorithm>
#include <array>
#include <condition_variable>
#include <format>
#include <mutex>
#include <thread>
#include <utility>

namespace crosslink::net::nethernet {
namespace {

constexpr std::string_view kReliableLabel = "ReliableDataChannel";
constexpr std::string_view kUnreliableLabel = "UnreliableDataChannel";

void configureSctpOnce() {
    static std::once_flag flag;
    std::call_once(flag, [] {
        rtc::SctpSettings settings;
        // Bedrock holds a SACK for up to 200ms, which is exactly libdatachannel's
        // default minimum RTO: data was retransmitted just as the SACK came due and
        // the congestion window collapsed. 400ms is what the client and BDS use.
        settings.minRetransmitTimeout = std::chrono::milliseconds{400};
        rtc::SetSctpSettings(settings);
    });
}

/// Deleting a PeerConnection joins its task queue, so doing it from inside one of
/// its own callbacks deadlocks. Sessions therefore hand their peer to this reaper,
/// which always destroys them on a thread of its own.
class PeerReaper {
public:
    static PeerReaper& instance() {
        static PeerReaper reaper;
        return reaper;
    }

    ~PeerReaper() {
        {
            std::lock_guard lock{mMutex};
            mStopping = true;
        }
        mCondition.notify_all();
        if (mThread.joinable()) mThread.join();
    }

    void add(std::unique_ptr<rtc::PeerConnection> peer) {
        if (!peer) return;
        {
            std::lock_guard lock{mMutex};
            mQueue.push_back(std::move(peer));
        }
        mCondition.notify_all();
    }

private:
    PeerReaper() {
        mThread = std::thread{[this] {
            for (;;) {
                std::vector<std::unique_ptr<rtc::PeerConnection>> doomed;
                {
                    std::unique_lock lock{mMutex};
                    mCondition.wait(lock, [this] { return mStopping || !mQueue.empty(); });
                    if (mStopping && mQueue.empty()) return;
                    doomed.swap(mQueue);
                }
                doomed.clear();
            }
        }};
    }

    std::mutex                                     mMutex;
    std::condition_variable                        mCondition;
    std::vector<std::unique_ptr<rtc::PeerConnection>> mQueue;
    std::thread                                    mThread;
    bool                                           mStopping{};
};

[[nodiscard]] std::string hexPreview(ByteSpan bytes, std::size_t limit = 16) {
    std::string out;
    for (std::size_t index = 0; index < bytes.size() && index < limit; ++index) {
        out += std::format("{:02x}", static_cast<unsigned char>(bytes[index]));
    }
    if (bytes.size() > limit) out += "...";
    return out;
}

[[nodiscard]] Endpoint parseEndpoint(std::string const& address) {
    Endpoint endpoint;
    if (address.empty()) return endpoint;
    const auto colon = address.rfind(':');
    if (colon == std::string::npos) {
        endpoint.host = address;
        return endpoint;
    }
    endpoint.host = address.substr(0, colon);
    if (!endpoint.host.empty() && endpoint.host.front() == '[' && endpoint.host.back() == ']') {
        endpoint.host = endpoint.host.substr(1, endpoint.host.size() - 2);
    }
    const auto portText = address.substr(colon + 1);
    std::uint32_t port = 0;
    for (const char ch : portText) {
        if (ch < '0' || ch > '9') return endpoint;
        port = port * 10 + static_cast<std::uint32_t>(ch - '0');
    }
    endpoint.port = static_cast<std::uint16_t>(std::min<std::uint32_t>(port, 65535));
    return endpoint;
}

} // namespace

NetherNetSession::NetherNetSession(Config config, Hooks hooks, Role role)
: mConfig(std::move(config)), mHooks(std::move(hooks)), mRole(role) {
    rtc::Configuration configuration;
    configuration.disableAutoNegotiation = true;
    configuration.maxMessageSize = mConfig.maxMessageSize;
    configuration.portRangeBegin = mConfig.portRangeBegin;
    configuration.portRangeEnd = mConfig.portRangeEnd;
    if (!mConfig.bindAddress.empty()) configuration.bindAddress = mConfig.bindAddress;
    for (auto const& url : mConfig.iceServers) configuration.iceServers.emplace_back(url);
    mPeer = std::make_unique<rtc::PeerConnection>(configuration);
}

NetherNetSession::~NetherNetSession() {
    // Never delete the peer here: this may be running on one of its own callbacks.
    PeerReaper::instance().add(std::move(mPeer));
}

Result<std::shared_ptr<NetherNetSession>> NetherNetSession::create(Config config, Hooks hooks, Role role) {
    configureSctpOnce();
    std::shared_ptr<NetherNetSession> self;
    try {
        self = std::shared_ptr<NetherNetSession>{new NetherNetSession{std::move(config), std::move(hooks), role}};
    } catch (std::exception const& error) {
        return std::unexpected(Error{std::format("cannot create a NetherNet session: {}", error.what())});
    }
    self->attach();
    return self;
}

void NetherNetSession::attach() {
    std::weak_ptr<NetherNetSession> weak = weak_from_this();

    mPeer->onGatheringStateChange([weak](rtc::PeerConnection::GatheringState state) {
        const auto self = weak.lock();
        if (!self || state != rtc::PeerConnection::GatheringState::Complete) return;
        {
            std::lock_guard lock{self->mMutex};
            self->mGatheringComplete = true;
        }
        self->mCondition.notify_all();
    });

    mPeer->onStateChange([weak](rtc::PeerConnection::State state) {
        const auto self = weak.lock();
        if (!self) return;
        switch (state) {
        case rtc::PeerConnection::State::Failed:       self->fail("the WebRTC connection failed"); break;
        case rtc::PeerConnection::State::Disconnected: self->fail("the WebRTC connection disconnected"); break;
        case rtc::PeerConnection::State::Closed:       self->fail("the WebRTC connection closed"); break;
        default: break;
        }
    });

    if (mRole == Role::Answerer) {
        mPeer->onDataChannel([weak](std::shared_ptr<rtc::DataChannel> channel) {
            const auto self = weak.lock();
            if (!self) return;
            const bool reliable = channel->label() == kReliableLabel;
            self->bindChannel(std::move(channel), reliable);
        });
        return;
    }

    // A Bedrock client opens both channels itself; a dialer has to open them.
    const auto reliable = mPeer->createDataChannel(std::string{kReliableLabel}, rtc::DataChannelInit{});
    bindChannel(reliable, true);

    rtc::DataChannelInit unreliableInit;
    unreliableInit.reliability.unordered = true;
    unreliableInit.reliability.maxRetransmits = 0u;
    const auto unreliable = mPeer->createDataChannel(std::string{kUnreliableLabel}, unreliableInit);
    bindChannel(unreliable, false);
}

void NetherNetSession::bindChannel(std::shared_ptr<rtc::DataChannel> channel, bool reliable) {
    if (!channel) return;
    {
        std::lock_guard lock{mMutex};
        if (reliable) {
            mReliable = channel;
        } else {
            mUnreliable = channel;
        }
    }

    std::weak_ptr<NetherNetSession> weak = weak_from_this();
    // Register the reader before anything else: the engine stalls a worker once
    // enough unread messages queue up, and the buffer does not outlive the call.
    channel->onMessage(
        [weak, reliable](rtc::binary data) {
            const auto self = weak.lock();
            if (!self) return;
            self->onChannelMessage(reliable, std::move(data));
        },
        [weak, reliable](rtc::string data) {
            const auto self = weak.lock();
            if (!self) return;
            // Bedrock sends binary; a text frame is handled the same way rather
            // than dropped, so a peer's choice of PPID cannot stall the session.
            std::vector<std::byte> bytes(data.size());
            for (std::size_t index = 0; index < data.size(); ++index) {
                bytes[index] = static_cast<std::byte>(static_cast<unsigned char>(data[index]));
            }
            self->onChannelMessage(reliable, std::move(bytes));
        }
    );
    channel->onOpen([weak, reliable] {
        const auto self = weak.lock();
        if (!self || !reliable) return;
        bool becameOpen = false;
        {
            std::lock_guard lock{self->mMutex};
            if (!self->mOpen && !self->mClosed) {
                self->mOpen = true;
                becameOpen = true;
            }
        }
        if (becameOpen) {
            logger("nethernet").debug(
                "{} reliable channel open (label '{}', stream {})",
                self->mRole == Role::Dialer ? "dialer" : "answerer",
                self->mReliable ? self->mReliable->label() : "?",
                self->mReliable && self->mReliable->stream() ? std::to_string(*self->mReliable->stream()) : "?"
            );
            if (self->mHooks.onOpen) self->mHooks.onOpen();
        }
    });
    channel->onClosed([weak, reliable] {
        const auto self = weak.lock();
        if (!self || !reliable) return;
        self->fail("the reliable data channel closed");
    });
    channel->onError([weak](std::string error) {
        const auto self = weak.lock();
        if (!self) return;
        self->fail(std::format("data channel error: {}", error));
    });

    if (reliable && channel->isOpen()) {
        bool becameOpen = false;
        {
            std::lock_guard lock{mMutex};
            if (!mOpen && !mClosed) {
                mOpen = true;
                becameOpen = true;
            }
        }
        if (becameOpen && mHooks.onOpen) mHooks.onOpen();
    }
}

Result<std::string> NetherNetSession::localSdp() {
    std::unique_lock lock{mMutex};
    if (!mCondition.wait_for(lock, mConfig.gatheringTimeout, [this] { return mGatheringComplete || mClosed; })) {
        return std::unexpected(Error{"ICE gathering did not finish in time"});
    }
    if (mClosed) return std::unexpected(Error{"the session closed while gathering candidates"});
    lock.unlock();

    const auto description = mPeer->localDescription();
    if (!description) return std::unexpected(Error{"the peer connection produced no local description"});
    return description->generateSdp();
}

Result<std::string> NetherNetSession::finalize(std::string text) {
    text = sdp::withMaxMessageSize(text, static_cast<std::uint32_t>(mConfig.maxMessageSize));
    if (mConfig.identity) {
        CROSSLINK_ASSIGN(assertion, mConfig.identity->assertion(text));
        text = sdp::withIdentity(text, *assertion);
    }
    return text;
}

Result<std::string> NetherNetSession::acceptOffer(std::string_view offer) {
    try {
        mPeer->setRemoteDescription(
            rtc::Description{sdp::withIpCandidates(sdp::withoutIdentity(offer)), rtc::Description::Type::Offer}
        );
        mPeer->setLocalDescription(rtc::Description::Type::Answer);
    } catch (std::exception const& error) {
        return std::unexpected(Error{std::format("cannot answer the offer: {}", error.what())});
    }
    CROSSLINK_ASSIGN(local, localSdp());
    return finalize(std::move(*local));
}

Result<std::string> NetherNetSession::createOffer() {
    try {
        mPeer->setLocalDescription(rtc::Description::Type::Offer);
    } catch (std::exception const& error) {
        return std::unexpected(Error{std::format("cannot create an offer: {}", error.what())});
    }
    CROSSLINK_ASSIGN(local, localSdp());
    return finalize(std::move(*local));
}

Result<> NetherNetSession::acceptAnswer(std::string_view answer) {
    try {
        mPeer->setRemoteDescription(
            rtc::Description{sdp::withIpCandidates(sdp::withoutIdentity(answer)), rtc::Description::Type::Answer}
        );
    } catch (std::exception const& error) {
        return std::unexpected(Error{std::format("cannot apply the answer: {}", error.what())});
    }
    return {};
}

void NetherNetSession::onChannelMessage(bool reliable, std::vector<std::byte> message) {
    if (mLoggedReceives++ < 8) {
        logger("nethernet").debug(
            "{} recv: {} message {} bytes [{}]",
            mRole == Role::Dialer ? "dialer" : "answerer",
            reliable ? "reliable" : "unreliable",
            message.size(),
            hexPreview(message)
        );
    }
    if (message.size() <= 1) {
        fail("a NetherNet message carried no payload");
        return;
    }

    Bytes batch;
    std::string failure;
    {
        std::lock_guard lock{mMutex};
        if (mClosed) return;
        const auto header = static_cast<std::uint8_t>(message[0]);
        const ByteSpan payload{message.data() + 1, message.size() - 1};

        if (!reliable) {
            // Unreliable messages are never fragmented.
            batch.assign(payload.begin(), payload.end());
        } else if (!mPartial && header == 0) {
            batch.assign(payload.begin(), payload.end());
        } else {
            if (!mPartial) {
                mPartial = Partial{.expected = header, .data = {}};
            } else if (header != mPartial->expected) {
                failure = "a NetherNet fragment countdown broke";
            }
            if (failure.empty()) {
                if (mPartial->data.size() + payload.size() > mConfig.maxPacketBytes) {
                    failure = "a reassembled packet exceeded the ingress limit";
                } else {
                    mPartial->data.insert(mPartial->data.end(), payload.begin(), payload.end());
                    if (header != 0) {
                        --mPartial->expected;
                        return;
                    }
                    batch = std::move(mPartial->data);
                    mPartial.reset();
                }
            }
        }
    }

    if (!failure.empty()) {
        fail(std::move(failure));
        return;
    }
    if (!batch.empty()) deliver(std::move(batch));
}

void NetherNetSession::deliver(Bytes batch) {
    std::vector<Bytes> packets;
    std::string failure;
    {
        std::lock_guard lock{mMutex};
        if (mClosed) return;
        if (auto decoded = mCodec.decode(batch, [&packets](Bytes& packet) { packets.push_back(packet); }); !decoded) {
            failure = std::format("cannot decode a batch: {}", decoded.error().message);
        }
    }
    if (!failure.empty()) {
        fail(std::move(failure));
        return;
    }
    for (auto& packet : packets) {
        if (mHooks.onPacket) mHooks.onPacket(packet);
    }
}

Result<> NetherNetSession::send(ByteSpan packet, bool immediate) {
    (void)immediate; // one batch per packet: there is nothing left to flush
    // One batch's cipher bytes and countdown fragments must stay contiguous.
    std::lock_guard sendLock{mMutex};
    std::shared_ptr<rtc::DataChannel> channel;
    Bytes batch;
    {
        std::lock_guard lock{mMutex};
        if (mClosed) return std::unexpected(Error{"the session is closed"});
        if (!mOpen || !mReliable) return std::unexpected(Error{"the session is not open"});
        channel = mReliable;
        const std::array packets{packet};
        CROSSLINK_ASSIGN(encoded, mCodec.encode(packets));
        batch = std::move(*encoded);
        if (mLoggedSends++ < 8) {
            logger("nethernet").debug(
                "{} send: packet {} bytes -> batch {} bytes [{}]",
                mRole == Role::Dialer ? "dialer" : "answerer",
                packet.size(),
                batch.size(),
                hexPreview(batch)
            );
        }
    }

    const auto segment = mConfig.maxSegmentBytes > 1 ? mConfig.maxSegmentBytes - 1 : 1;
    if (batch.size() > 255 * segment) {
        return std::unexpected(Error{"a packet is too large to fragment"});
    }

    auto fragments = batch.empty() ? 1u : static_cast<unsigned>((batch.size() - 1) / segment + 1);
    std::size_t offset = 0;
    while (fragments > 0) {
        --fragments;
        const auto length = std::min(batch.size() - offset, segment);
        std::vector<std::byte> fragment;
        fragment.reserve(length + 1);
        fragment.push_back(static_cast<std::byte>(fragments));
        fragment.insert(fragment.end(), batch.begin() + static_cast<std::ptrdiff_t>(offset),
                        batch.begin() + static_cast<std::ptrdiff_t>(offset + length));
        offset += length;
        try {
            // false means buffered, not refused.
            channel->send(fragment.data(), fragment.size());
        } catch (std::exception const& error) {
            return std::unexpected(Error{std::format("cannot send a fragment: {}", error.what())});
        }
    }
    return {};
}

void NetherNetSession::setCompression(Compression algorithm, std::int32_t threshold) {
    std::lock_guard lock{mMutex};
    mCodec.setCompression(algorithm, threshold);
}

Result<> NetherNetSession::enableEncryption(ByteSpan key) {
    std::lock_guard lock{mMutex};
    return mCodec.enableEncryption(key);
}

bool NetherNetSession::encrypted() const noexcept {
    std::lock_guard lock{mMutex};
    return mCodec.encrypted();
}

bool NetherNetSession::open() const noexcept {
    std::lock_guard lock{mMutex};
    return mOpen && !mClosed;
}

bool NetherNetSession::closed() const noexcept {
    std::lock_guard lock{mMutex};
    return mClosed;
}

Endpoint NetherNetSession::remote() const noexcept {
    if (!mPeer) return {};
    const auto address = mPeer->remoteAddress();
    return address ? parseEndpoint(*address) : Endpoint{};
}

void NetherNetSession::fail(std::string reason) {
    bool report = false;
    {
        std::lock_guard lock{mMutex};
        if (mClosed) return;
        mClosed = true;
        report = !mCloseReported;
        mCloseReported = true;
    }
    mCondition.notify_all();
    if (mPeer) mPeer->close();
    logger("nethernet").debug("session closed: {}", reason);
    if (report && mHooks.onClosed) mHooks.onClosed(std::move(reason));
}

void NetherNetSession::close() noexcept { fail("closed locally"); }

} // namespace crosslink::net::nethernet