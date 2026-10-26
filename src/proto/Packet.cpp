#include "crosslink/api/proto/Packet.hpp"

#include "proto/SculkBridge.hpp"

#include <magic_enum/magic_enum.hpp>

#include <format>
#include <map>
#include <mutex>
#include <utility>

namespace crosslink::proto {

Result<PacketHeader> readPacketHeader(ByteSpan bytes) {
    const auto header = bridge::readSculkHeader(bytes);
    if (!header) return std::unexpected(header.error());
    return bridge::fromSculk(*header);
}

void writePacketHeader(Bytes& out, PacketHeader const& header) {
    bridge::bp::BinaryStream stream{out};
    bridge::bp::MinecraftPackets::writePacketHeader(stream, bridge::toSculk(header));
}

std::string_view packetName(PacketId id) noexcept {
    const auto name = magic_enum::enum_name(id);
    return name.empty() ? std::string_view{"Unknown"} : name;
}

Packet::~Packet() = default;

Packet::Packet(PacketHeader header, Bytes bytes, std::size_t headerSize)
: mHeader(header), mBytes(std::move(bytes)), mHeaderSize(headerSize), mDecoded(false) {}

Packet::Packet(PacketHeader header) : mHeader(header), mHeaderSize(0) {}

void Packet::setSubClientIds(std::uint8_t sender, std::uint8_t target) noexcept {
    if (mHeader.senderSubClientId == sender && mHeader.targetSubClientId == target) return;
    mHeader.senderSubClientId = sender;
    mHeader.targetSubClientId = target;
    // The header lives inside mBytes, so it has to be rewritten.
    if (!mBytes.empty() && mHeaderSize != 0) {
        Bytes tail{mBytes.begin() + static_cast<std::ptrdiff_t>(mHeaderSize), mBytes.end()};
        mBytes.clear();
        writePacketHeader(mBytes, mHeader);
        mHeaderSize = mBytes.size();
        mBytes.insert(mBytes.end(), tail.begin(), tail.end());
    } else {
        mDirty = true;
    }
}

ByteSpan Packet::payload() const noexcept {
    if (mBytes.size() <= mHeaderSize) return {};
    return ByteSpan{mBytes}.subspan(mHeaderSize);
}

Bytes& Packet::mutableBytes() noexcept {
    // Hand-edited bytes win over the typed view.
    mDecoded = false;
    mDirty = false;
    return mBytes;
}

void Packet::replaceBytes(Bytes bytes) {
    const auto header = readPacketHeader(bytes);
    if (header) {
        mHeader = *header;
        mHeaderSize = bridge::serializedHeaderSize(*header);
    }
    mBytes = std::move(bytes);
    mDecoded = false;
    mDirty = false;
}

Result<> Packet::decode() {
    if (mDecoded) return {};
    auto result = decodeImpl();
    if (!result) return result;
    mDecoded = true;
    return {};
}

Result<> Packet::encode() {
    if (!mDirty) {
        if (mBytes.empty()) {
            auto result = encodeImpl();
            if (!result) return result;
        }
        return {};
    }
    auto result = encodeImpl();
    if (!result) return result;
    mDirty = false;
    return {};
}

Result<> Packet::normalize() {
    CROSSLINK_PROPAGATE(decode());
    return encode();
}

void Packet::setPayload(Bytes payload) {
    mBytes.clear();
    writePacketHeader(mBytes, mHeader);
    mHeaderSize = mBytes.size();
    mBytes.insert(mBytes.end(), payload.begin(), payload.end());
    mDecoded = false;
    mDirty = false;
}

void Packet::setSerialized(Bytes bytes, std::size_t headerSize) {
    mBytes = std::move(bytes);
    mHeaderSize = headerSize;
    mDirty = false;
}

RawPacket::RawPacket(PacketHeader header, Bytes bytes, std::size_t headerSize)
: Packet(header, std::move(bytes), headerSize) {}

RawPacket::RawPacket(PacketHeader header) : Packet(header) {}

std::string_view RawPacket::name() const noexcept { return packetName(id()); }

struct PacketCodecs::Impl {
    mutable std::recursive_mutex                    mutex;
    std::map<std::uint16_t, PacketCodecs::Factory> factories;
};

PacketCodecs::PacketCodecs() : mImpl(std::make_unique<Impl>()) {}
PacketCodecs::~PacketCodecs() = default;

PacketCodecs& PacketCodecs::instance() {
    static PacketCodecs codecs;
    return codecs;
}

bool PacketCodecs::registerCodec(PacketId id, Factory factory) {
    if (!factory) return false;
    std::lock_guard lock{mImpl->mutex};
    mImpl->factories.insert_or_assign(packetIdValue(id), std::move(factory));
    return true;
}

bool PacketCodecs::unregisterCodec(PacketId id) {
    std::lock_guard lock{mImpl->mutex};
    return mImpl->factories.erase(packetIdValue(id)) > 0;
}

bool PacketCodecs::hasCodec(PacketId id) const {
    std::lock_guard lock{mImpl->mutex};
    return mImpl->factories.contains(packetIdValue(id));
}

Result<PacketPtr> PacketCodecs::wrap(Bytes bytes) const {
    const auto header = readPacketHeader(bytes);
    if (!header) return std::unexpected(header.error());

    const auto headerSize = bridge::serializedHeaderSize(*header);
    std::lock_guard lock{mImpl->mutex};
    const auto found = mImpl->factories.find(packetIdValue(header->id));
    if (found == mImpl->factories.end()) {
        return PacketPtr{std::make_unique<RawPacket>(*header, std::move(bytes), headerSize)};
    }
    return found->second(*header, std::move(bytes), headerSize);
}

PacketPtr PacketCodecs::create(PacketHeader header) const {
    std::lock_guard lock{mImpl->mutex};
    const auto found = mImpl->factories.find(packetIdValue(header.id));
    if (found == mImpl->factories.end()) return std::make_unique<RawPacket>(header);
    return found->second(header, Bytes{}, 0);
}

} // namespace crosslink::proto
