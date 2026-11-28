#include "proto/BatchCodec.hpp"

#include "crosslink/api/Logger.hpp"
#include "proto/Jose.hpp"

#include <openssl/evp.h>

#include <snappy.h>
#include <zlib.h>

#include <algorithm>
#include <array>
#include <cstring>
#include <format>
#include <utility>
#include <vector>

namespace crosslink::proto {
namespace {

constexpr std::size_t kMaxVarIntBytes = 5;

[[nodiscard]] unsigned char byteValue(std::byte value) noexcept { return static_cast<unsigned char>(value); }

void appendVarInt(Bytes& out, std::uint32_t value) {
    while (value >= 0x80U) {
        out.push_back(static_cast<std::byte>((value & 0x7FU) | 0x80U));
        value >>= 7U;
    }
    out.push_back(static_cast<std::byte>(value));
}

[[nodiscard]] Result<std::uint32_t> readVarInt(ByteSpan data, std::size_t& offset) {
    std::uint32_t value = 0;
    for (std::size_t index = 0; index < kMaxVarIntBytes; ++index) {
        if (offset >= data.size()) return std::unexpected(Error{"a batch ended inside a packet length"});
        const auto byte = byteValue(data[offset++]);
        value |= static_cast<std::uint32_t>(byte & 0x7FU) << (7U * index);
        if ((byte & 0x80U) == 0) return value;
    }
    return std::unexpected(Error{"a batch carries an overlong packet length"});
}

[[nodiscard]] Result<Bytes> deflateRaw(ByteSpan input) {
    z_stream stream{};
    if (deflateInit2(&stream, Z_DEFAULT_COMPRESSION, Z_DEFLATED, -15, 8, Z_DEFAULT_STRATEGY) != Z_OK) {
        return std::unexpected(Error{"cannot initialize deflate"});
    }

    Bytes out(deflateBound(&stream, static_cast<uLong>(input.size())));
    stream.next_in = reinterpret_cast<Bytef*>(const_cast<std::byte*>(input.data()));
    stream.avail_in = static_cast<uInt>(input.size());
    stream.next_out = reinterpret_cast<Bytef*>(out.data());
    stream.avail_out = static_cast<uInt>(out.size());

    const int status = deflate(&stream, Z_FINISH);
    const auto produced = stream.total_out;
    deflateEnd(&stream);
    if (status != Z_STREAM_END) return std::unexpected(Error{"deflate did not finish a batch"});
    out.resize(produced);
    return out;
}

[[nodiscard]] Result<Bytes> inflateRaw(ByteSpan input) {
    z_stream stream{};
    if (inflateInit2(&stream, -15) != Z_OK) {
        return std::unexpected(Error{"cannot initialize inflate"});
    }

    stream.next_in = reinterpret_cast<Bytef*>(const_cast<std::byte*>(input.data()));
    stream.avail_in = static_cast<uInt>(input.size());

    Bytes out;
    std::array<std::byte, 64 * 1024> chunk{};
    int status = Z_OK;
    do {
        stream.next_out = reinterpret_cast<Bytef*>(chunk.data());
        stream.avail_out = static_cast<uInt>(chunk.size());
        status = inflate(&stream, Z_NO_FLUSH);
        if (status != Z_OK && status != Z_STREAM_END && status != Z_BUF_ERROR) {
            inflateEnd(&stream);
            return std::unexpected(Error{"a batch is not valid deflate data"});
        }
        const auto produced = chunk.size() - stream.avail_out;
        out.insert(out.end(), chunk.begin(), chunk.begin() + static_cast<std::ptrdiff_t>(produced));
        if (status == Z_BUF_ERROR && produced == 0) break;
    } while (status != Z_STREAM_END);

    inflateEnd(&stream);
    if (status != Z_STREAM_END) return std::unexpected(Error{"a deflate batch ended early"});
    return out;
}

[[nodiscard]] Result<Bytes> snappyCompress(ByteSpan input) {
    std::string out;
    snappy::Compress(reinterpret_cast<const char*>(input.data()), input.size(), &out);
    Bytes result(out.size());
    std::memcpy(result.data(), out.data(), out.size());
    return result;
}

[[nodiscard]] Result<Bytes> snappyDecompress(ByteSpan input) {
    std::size_t length = 0;
    if (!snappy::GetUncompressedLength(reinterpret_cast<const char*>(input.data()), input.size(), &length)) {
        return std::unexpected(Error{"a batch is not valid snappy data"});
    }
    Bytes out(length);
    if (!snappy::RawUncompress(
            reinterpret_cast<const char*>(input.data()),
            input.size(),
            reinterpret_cast<char*>(out.data())
        )) {
        return std::unexpected(Error{"a snappy batch did not decompress"});
    }
    return out;
}

[[nodiscard]] std::string hexPreview(ByteSpan bytes, std::size_t limit = 24) {
    std::string out;
    for (std::size_t index = 0; index < bytes.size() && index < limit; ++index) {
        out += std::format("{:02x}", byteValue(bytes[index]));
    }
    if (bytes.size() > limit) out += "...";
    return out;
}

/// A plaintext batch is a compression header plus a payload that actually
/// decompresses and splits into length-prefixed packets. Checking for a varint
/// right after the header is wrong: for a compressed batch those bytes are the
/// compressed stream, not a length.
[[nodiscard]] bool looksLikePlaintextBatch(ByteSpan batch) {
    if (batch.size() < 2) return false;
    const auto header = static_cast<std::int8_t>(byteValue(batch.front()));
    const ByteSpan body{batch.data() + 1, batch.size() - 1};

    Bytes payload;
    if (header == static_cast<std::int8_t>(net::Compression::None)) {
        payload.assign(body.begin(), body.end());
    } else if (header == static_cast<std::int8_t>(net::Compression::Zlib)) {
        auto inflated = inflateRaw(body);
        if (!inflated) return false;
        payload = std::move(*inflated);
    } else if (header == static_cast<std::int8_t>(net::Compression::Snappy)) {
        auto inflated = snappyDecompress(body);
        if (!inflated) return false;
        payload = std::move(*inflated);
    } else {
        return false;
    }

    std::size_t offset = 0;
    const auto length = readVarInt(payload, offset);
    return length && *length > 0 && *length <= payload.size() - offset;
}

struct CipherContextDeleter {
    void operator()(EVP_CIPHER_CTX* ctx) const noexcept { EVP_CIPHER_CTX_free(ctx); }
};
using CipherContextPtr = std::unique_ptr<EVP_CIPHER_CTX, CipherContextDeleter>;

} // namespace

// ---- BatchCipher ------------------------------------------------------

struct BatchCipher::Impl {
    Bytes key;
    /// AES-256-CTR started at key[0..12] || 00 00 00 02, which is the first
    /// keystream block of AES-256-GCM under the same key and a 96-bit IV. Bedrock
    /// runs it as one uninterrupted stream per direction.
    std::array<std::byte, 16> initialCounter{};
    CipherContextPtr encrypt;
    CipherContextPtr decrypt;
    std::uint64_t encryptCounter{};
    std::uint64_t decryptCounter{};

    [[nodiscard]] Result<Bytes> checksum(std::uint64_t counter, ByteSpan data) const {
        std::array<std::byte, 8> littleEndian{};
        for (std::size_t index = 0; index < littleEndian.size(); ++index) {
            littleEndian[index] = static_cast<std::byte>((counter >> (8U * index)) & 0xFFU);
        }
        const std::array parts{ByteSpan{littleEndian}, data, ByteSpan{key}};
        CROSSLINK_ASSIGN(digest, jose::sha256(parts));
        if (digest->size() < kChecksumSize) return std::unexpected(Error{"a truncated batch checksum"});
        Bytes sum(digest->begin(), digest->begin() + static_cast<std::ptrdiff_t>(kChecksumSize));
        return sum;
    }

    [[nodiscard]] Result<> init(CipherContextPtr& context, bool encrypting) const {
        context.reset(EVP_CIPHER_CTX_new());
        if (!context) return std::unexpected(Error{"cannot allocate a batch cipher"});
        if (EVP_CipherInit_ex(
                context.get(),
                EVP_aes_256_ctr(),
                nullptr,
                reinterpret_cast<const unsigned char*>(key.data()),
                reinterpret_cast<const unsigned char*>(initialCounter.data()),
                encrypting ? 1 : 0
            )
            != 1) {
            return std::unexpected(Error{"cannot initialize the batch cipher"});
        }
        if (EVP_CIPHER_CTX_set_padding(context.get(), 0) != 1) {
            return std::unexpected(Error{"cannot disable batch cipher padding"});
        }
        return {};
    }

    [[nodiscard]] Result<Bytes> crypt(CipherContextPtr& context, ByteSpan input, bool encrypting) const {
        if (!context) {
            if (auto ready = init(context, encrypting); !ready) return std::unexpected(ready.error());
        }
        Bytes out(input.size());
        int produced = 0;
        if (EVP_CipherUpdate(
                context.get(),
                reinterpret_cast<unsigned char*>(out.data()),
                &produced,
                reinterpret_cast<const unsigned char*>(input.data()),
                static_cast<int>(input.size())
            )
            != 1
            || static_cast<std::size_t>(produced) != out.size()) {
            return std::unexpected(Error{"the batch cipher refused a batch"});
        }
        return out;
    }
};

BatchCipher::BatchCipher(Bytes key) : mImpl(std::make_unique<Impl>()) {
    mImpl->key = std::move(key);
    std::copy_n(mImpl->key.begin(), std::min<std::size_t>(12, mImpl->key.size()), mImpl->initialCounter.begin());
    mImpl->initialCounter[15] = std::byte{0x02};
}

BatchCipher::~BatchCipher() = default;

Result<Bytes> BatchCipher::seal(ByteSpan plaintext) {
    CROSSLINK_ASSIGN(sum, mImpl->checksum(mImpl->encryptCounter, plaintext));
    Bytes framed(plaintext.begin(), plaintext.end());
    framed.insert(framed.end(), sum->begin(), sum->end());
    CROSSLINK_ASSIGN(sealed, mImpl->crypt(mImpl->encrypt, framed, true));
    ++mImpl->encryptCounter;
    return *sealed;
}

Result<Bytes> BatchCipher::open(ByteSpan ciphertext) {
    if (ciphertext.size() < kChecksumSize) {
        return std::unexpected(Error{"a batch is too short to carry its checksum"});
    }
    if (!mImpl->decrypt) {
        if (auto ready = mImpl->init(mImpl->decrypt, false); !ready) return std::unexpected(ready.error());
    }

    // Decrypt on a copy: a failed attempt must not consume keystream, or every
    // later batch would be offset by this one's length.
    CipherContextPtr trial{EVP_CIPHER_CTX_new()};
    if (!trial) return std::unexpected(Error{"cannot allocate a batch cipher"});
    if (EVP_CIPHER_CTX_copy(trial.get(), mImpl->decrypt.get()) != 1) {
        return std::unexpected(Error{"cannot snapshot the batch cipher"});
    }

    Bytes clear(ciphertext.size());
    int produced = 0;
    if (EVP_CipherUpdate(
            trial.get(),
            reinterpret_cast<unsigned char*>(clear.data()),
            &produced,
            reinterpret_cast<const unsigned char*>(ciphertext.data()),
            static_cast<int>(ciphertext.size())
        )
        != 1
        || static_cast<std::size_t>(produced) != clear.size()) {
        return std::unexpected(Error{"the batch cipher refused a batch"});
    }

    const auto payloadSize = clear.size() - kChecksumSize;
    const ByteSpan payload{clear.data(), payloadSize};
    CROSSLINK_ASSIGN(sum, mImpl->checksum(mImpl->decryptCounter, payload));
    const ByteSpan expected{clear.data() + payloadSize, kChecksumSize};
    if (!std::equal(sum->begin(), sum->end(), expected.begin())) {
        return std::unexpected(Error{"a batch checksum does not match"});
    }

    mImpl->decrypt = std::move(trial);
    ++mImpl->decryptCounter;
    clear.resize(payloadSize);
    return clear;
}

// ---- BatchCodec -------------------------------------------------------

BatchCodec::BatchCodec() = default;

BatchCodec::~BatchCodec() = default;

void BatchCodec::setCompression(net::Compression algorithm, std::int32_t threshold) {
    mCompression = algorithm;
    mThreshold = threshold;
    mCompressionEnabled = true;
}

Result<> BatchCodec::enableEncryption(ByteSpan key) {
    if (key.size() != BatchCipher::kKeySize) {
        return std::unexpected(Error{std::format("a session key must be {} bytes", BatchCipher::kKeySize)});
    }
    mCipher = std::make_unique<BatchCipher>(Bytes{key.begin(), key.end()});
    return {};
}

bool BatchCodec::encrypted() const noexcept { return mCipher != nullptr; }

Result<Bytes> BatchCodec::encode(std::span<const ByteSpan> packets) {
    Bytes payload;
    for (const auto packet : packets) {
        appendVarInt(payload, static_cast<std::uint32_t>(packet.size()));
        payload.insert(payload.end(), packet.begin(), packet.end());
    }

    Bytes batch;
    if (mCompressionEnabled) {
        auto header = net::Compression::None;
        if (payload.size() >= static_cast<std::size_t>(std::max<std::int32_t>(mThreshold, 0))) {
            header = mCompression;
        }
        batch.push_back(static_cast<std::byte>(static_cast<std::int8_t>(header)));
        switch (header) {
        case net::Compression::Zlib: {
            CROSSLINK_ASSIGN(compressed, deflateRaw(payload));
            batch.insert(batch.end(), compressed->begin(), compressed->end());
            break;
        }
        case net::Compression::Snappy: {
            CROSSLINK_ASSIGN(compressed, snappyCompress(payload));
            batch.insert(batch.end(), compressed->begin(), compressed->end());
            break;
        }
        case net::Compression::None:
            batch.insert(batch.end(), payload.begin(), payload.end());
            break;
        }
    } else {
        batch = std::move(payload);
    }

    // Mirror the peer: BDS and the game client both keep sending in the clear for
    // a while after the handshake ack, so encrypting before they switch would make
    // every outbound batch unreadable to them. Outbound encryption turns on with
    // the first batch that verifies under the cipher.
    if (mCipher && mEncryptionConfirmed) return mCipher->seal(batch);
    return batch;
}

Result<> BatchCodec::decode(ByteSpan batch, std::function<void(Bytes&)> const& sink) {
    Bytes opened;
    if (mCipher) {
        auto clear = mCipher->open(batch);
        if (clear) {
            mEncryptionConfirmed = true;
            opened = std::move(*clear);
            batch = opened;
        } else if (!mEncryptionConfirmed && looksLikePlaintextBatch(batch)) {
            // BDS can flush a batch it queued before enabling encryption, so the
            // first post-handshake batch may still be in the clear. Tolerate that
            // only until one batch has actually verified under the cipher.
            if (!mPlaintextTransitionLogged) {
                logger("nethernet").debug("peer is still using plaintext batches after handshake ({} bytes)", batch.size());
                mPlaintextTransitionLogged = true;
            }
        } else {
            logger("nethernet").warn(
                "batch decrypt failed ({}); raw {} bytes [{}], looks like plaintext: {}",
                clear.error().message,
                batch.size(),
                hexPreview(batch),
                looksLikePlaintextBatch(batch) ? "YES" : "no"
            );
            return std::unexpected(clear.error());
        }
    }

    Bytes decompressed;
    if (mCompressionEnabled) {
        if (batch.empty()) return std::unexpected(Error{"a batch is missing its compression header"});
        const auto header = static_cast<std::int8_t>(byteValue(batch.front()));
        const ByteSpan body{batch.data() + 1, batch.size() - 1};
        switch (static_cast<net::Compression>(header)) {
        case net::Compression::Zlib: {
            CROSSLINK_ASSIGN(clear, inflateRaw(body));
            decompressed = std::move(*clear);
            break;
        }
        case net::Compression::Snappy: {
            CROSSLINK_ASSIGN(clear, snappyDecompress(body));
            decompressed = std::move(*clear);
            break;
        }
        case net::Compression::None:
            decompressed.assign(body.begin(), body.end());
            break;
        default:
            return std::unexpected(Error{std::format("unknown batch compression {}", header)});
        }
        batch = decompressed;
    }

    std::size_t offset = 0;
    while (offset < batch.size()) {
        CROSSLINK_ASSIGN(length, readVarInt(batch, offset));
        if (static_cast<std::size_t>(*length) > batch.size() - offset) {
            return std::unexpected(Error{"a batch ended inside a packet"});
        }
        Bytes packet(batch.begin() + static_cast<std::ptrdiff_t>(offset),
                     batch.begin() + static_cast<std::ptrdiff_t>(offset + *length));
        offset += *length;
        sink(packet);
    }
    return {};
}

} // namespace crosslink::proto