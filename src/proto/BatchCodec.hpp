#pragma once

// The Bedrock batch layer: what sits between one transport message and the
// individual protocol packets the gateway routes. A batch is a compression
// header plus a run of length-prefixed packets, optionally encrypted. NetherNet
// carries it verbatim; RakNet used to prefix 0xFE, which nothing above this file
// ever saw.

#include "crosslink/api/Result.hpp"
#include "crosslink/api/Types.hpp"
#include "crosslink/api/net/Transport.hpp"

#include <cstdint>
#include <functional>
#include <memory>
#include <span>

namespace crosslink::proto {

/// AES-256 run as a keystream across every batch in one direction, never
/// finalised, with SHA-256(counter, batch, key) truncated to 8 bytes sealed in
/// behind each batch. The counter is per direction and per batch, not per byte.
class BatchCipher {
public:
    static constexpr std::size_t kKeySize = 32;
    static constexpr std::size_t kChecksumSize = 8;

    explicit BatchCipher(Bytes key);
    ~BatchCipher();

    BatchCipher(BatchCipher const&)            = delete;
    BatchCipher& operator=(BatchCipher const&) = delete;

    [[nodiscard]] Result<Bytes> seal(ByteSpan plaintext);
    [[nodiscard]] Result<Bytes> open(ByteSpan ciphertext);

private:
    struct Impl;
    std::unique_ptr<Impl> mImpl;
};

/// Compression and encryption state for one connection, both directions.
class BatchCodec {
public:
    BatchCodec();
    ~BatchCodec();

    BatchCodec(BatchCodec const&)            = delete;
    BatchCodec& operator=(BatchCodec const&) = delete;

    void setCompression(net::Compression algorithm, std::int32_t threshold);
    [[nodiscard]] Result<> enableEncryption(ByteSpan key);
    [[nodiscard]] bool     encrypted() const noexcept;

    /// Each packet is header + body, without its length prefix.
    [[nodiscard]] Result<Bytes> encode(std::span<const ByteSpan> packets);

    /// Delivers every packet in the batch to `sink`, in order. The sink may
    /// rewrite the buffer; the codec does not keep it.
    [[nodiscard]] Result<> decode(ByteSpan batch, std::function<void(Bytes&)> const& sink);

private:
    net::Compression          mCompression{net::Compression::None};
    std::int32_t              mThreshold{0};
    bool                      mCompressionEnabled{};
    /// Set by the first batch that verifies under the cipher. Until then a peer
    /// may still flush a batch it queued before switching encryption on.
    bool                      mEncryptionConfirmed{};
    bool                      mPlaintextTransitionLogged{};
    std::unique_ptr<BatchCipher> mCipher;
};

} // namespace crosslink::proto