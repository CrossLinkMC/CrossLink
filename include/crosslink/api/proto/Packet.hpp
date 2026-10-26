#pragma once

#include "crosslink/api/Export.hpp"
#include "crosslink/api/Result.hpp"
#include "crosslink/api/Types.hpp"
#include "crosslink/api/proto/PacketId.hpp"

#include <cstddef>
#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <string_view>
#include <utility>

namespace crosslink::proto {

/// Bedrock's packet header: one unsigned varint holding the id and the two
/// sub-client ids.
struct PacketHeader {
    PacketId      id{};
    std::uint8_t  senderSubClientId{};
    std::uint8_t  targetSubClientId{};

    [[nodiscard]] auto operator<=>(PacketHeader const&) const = default;
};

[[nodiscard]] CROSSLINK_API Result<PacketHeader> readPacketHeader(ByteSpan bytes);
CROSSLINK_API void                               writePacketHeader(Bytes& out, PacketHeader const& header);
[[nodiscard]] CROSSLINK_API std::string_view     packetName(PacketId id) noexcept;

/// Unified abstraction over every protocol packet the gateway touches.
///
/// A packet is always backed by its full serialized form (`bytes()`, header
/// included) so that forwarding never has to re-encode anything. Subclasses add
/// typed accessors; `decode()` fills them lazily and `encode()` writes them back
/// only when something was mutated. Packets without special handling stay
/// RawPacket and are forwarded byte for byte.
///
/// CrossLink's own packet classes deliberately hide the vendored protocol
/// library: plugins compile against POD accessors only, so the plugin ABI does
/// not move when the transport library is swapped (see net/Transport.hpp).
class CROSSLINK_API Packet {
public:
    Packet(Packet const&)            = delete;
    Packet& operator=(Packet const&) = delete;
    virtual ~Packet();

    [[nodiscard]] virtual std::string_view name() const noexcept = 0;

    [[nodiscard]] PacketHeader const& header() const noexcept { return mHeader; }
    [[nodiscard]] PacketId            id() const noexcept { return mHeader.id; }
    void                              setSubClientIds(std::uint8_t sender, std::uint8_t target) noexcept;

    /// Full serialized packet, header included. Empty until a synthetic packet
    /// is encoded.
    [[nodiscard]] Bytes const& bytes() const noexcept { return mBytes; }
    [[nodiscard]] ByteSpan     payload() const noexcept;

    /// Escape hatch for byte level surgery; invalidates the typed view.
    [[nodiscard]] Bytes& mutableBytes() noexcept;
    void                 replaceBytes(Bytes bytes);

    [[nodiscard]] bool decoded() const noexcept { return mDecoded; }
    [[nodiscard]] bool dirty() const noexcept { return mDirty; }

    /// Idempotent: decodes once and caches the result.
    [[nodiscard]] Result<> decode();

    /// Re-serializes into `bytes()` when the typed view was mutated.
    [[nodiscard]] Result<> encode();

    /// Decodes if needed, then re-serializes if needed.
    [[nodiscard]] Result<> normalize();

protected:
    Packet(PacketHeader header, Bytes bytes, std::size_t headerSize);
    explicit Packet(PacketHeader header);

    virtual Result<> decodeImpl() { return {}; }
    virtual Result<> encodeImpl() { return {}; }

    void markDirty() noexcept { mDirty = true; }
    void markDecoded() noexcept { mDecoded = true; }
    /// Replaces the payload while keeping the header, marking the packet dirty.
    void setPayload(Bytes payload);
    /// Called by encodeImpl() with the freshly serialized packet.
    void setSerialized(Bytes bytes, std::size_t headerSize);

    PacketHeader mHeader;
    Bytes        mBytes;
    std::size_t  mHeaderSize{};
    bool         mDecoded{};
    bool         mDirty{};
};

/// A packet CrossLink forwards without interpreting.
class CROSSLINK_API RawPacket final : public Packet {
public:
    RawPacket(PacketHeader header, Bytes bytes, std::size_t headerSize);
    explicit RawPacket(PacketHeader header);

    [[nodiscard]] std::string_view name() const noexcept override;
};

using PacketPtr = std::unique_ptr<Packet>;

/// Builds packets from serialized bytes.
///
/// The registry is open on purpose: a plugin can replace the codec for an id or
/// add ids the built-in table does not know, which is how an alternative
/// transport (for example the post-26.60 nethernet stack) is meant to hook in
/// without the gateway core changing.
class CROSSLINK_API PacketCodecs {
public:
    using Factory = std::function<PacketPtr(PacketHeader const&, Bytes&&, std::size_t)>;

    [[nodiscard]] static PacketCodecs& instance();

    bool registerCodec(PacketId id, Factory factory);
    bool unregisterCodec(PacketId id);
    [[nodiscard]] bool hasCodec(PacketId id) const;

    /// Wraps a serialized packet, choosing the registered codec or RawPacket.
    [[nodiscard]] Result<PacketPtr> wrap(Bytes bytes) const;

    /// Builds a typed packet from a header only, for packets the gateway or a
    /// plugin synthesizes. Returns nullptr when no codec is registered.
    [[nodiscard]] PacketPtr create(PacketHeader header) const;

    template <typename T>
    bool registerPacket(PacketId id) {
        return registerCodec(id, [](PacketHeader const& header, Bytes&& bytes, std::size_t headerSize) -> PacketPtr {
            if (bytes.empty()) return std::make_unique<T>(header);
            return std::make_unique<T>(header, std::move(bytes), headerSize);
        });
    }

private:
    PacketCodecs();
    ~PacketCodecs();

    struct Impl;
    std::unique_ptr<Impl> mImpl;
};

/// `packet.as<StartGamePacket>()` — the typed view of a packet, or an error when
/// the id does not carry that type.
template <typename T>
[[nodiscard]] Result<T&> as(Packet& packet) {
    if (auto* typed = dynamic_cast<T*>(std::addressof(packet))) return *typed;
    return std::unexpected(Error{std::string("packet is not a ") + T::staticName});
}

template <typename T>
[[nodiscard]] T* asOrNull(Packet& packet) noexcept {
    return dynamic_cast<T*>(std::addressof(packet));
}

} // namespace crosslink::proto
