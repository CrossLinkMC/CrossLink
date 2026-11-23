#include <bedrock/protocol/network.h>

#include <bit>

namespace bedrock::protocol {


void Serializer<LoginPacket>::serialize(BinaryWriter &stream, const LoginPacket &value)
{
    stream.write<std::int32_t, std::endian::big>(value.client_network_version);
    stream.write(value.connection_request);
}

auto Serializer<LoginPacket>::deserialize(BinaryReader &stream) -> std::expected<LoginPacket, std::error_code>
{
    LoginPacket out;
    {
        auto v = stream.read<std::int32_t, std::endian::big>();
        if (!v) return std::unexpected(v.error());
        out.client_network_version = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.connection_request = *v;
    }
    return out;
}

void Serializer<PlayStatusPacket>::serialize(BinaryWriter &stream, const PlayStatusPacket &value)
{
    stream.write<std::int32_t, std::endian::big>(value.status);
}

auto Serializer<PlayStatusPacket>::deserialize(BinaryReader &stream) -> std::expected<PlayStatusPacket, std::error_code>
{
    PlayStatusPacket out;
    {
        auto v = stream.read<std::int32_t, std::endian::big>();
        if (!v) return std::unexpected(v.error());
        out.status = static_cast<PlayStatus>(*v);
    }
    return out;
}

void Serializer<ServerToClientHandshakePacket>::serialize(BinaryWriter &stream, const ServerToClientHandshakePacket &value)
{
    stream.write(value.token);
}

auto Serializer<ServerToClientHandshakePacket>::deserialize(BinaryReader &stream) -> std::expected<ServerToClientHandshakePacket, std::error_code>
{
    ServerToClientHandshakePacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.token = *v;
    }
    return out;
}

void Serializer<DisconnectPacketMessages>::serialize(BinaryWriter &stream, const DisconnectPacketMessages &value)
{
    stream.write(value.message);
    stream.write(value.filtered_message);
}

auto Serializer<DisconnectPacketMessages>::deserialize(BinaryReader &stream) -> std::expected<DisconnectPacketMessages, std::error_code>
{
    DisconnectPacketMessages out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.message = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.filtered_message = *v;
    }
    return out;
}

void Serializer<base::DisconnectPacket>::serialize(BinaryWriter &stream, const base::DisconnectPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.reason);
    stream.writeVarInt<std::uint32_t>((value.messages).index());
    switch ((value.messages).index()) {
        case 0: {
            Serializer<DisconnectPacketMessages>::serialize(stream, std::get<0>(value.messages));
            break;
        }
        case 1: {
            break;
        }
    }
}

auto Serializer<base::DisconnectPacket>::deserialize(BinaryReader &stream) -> std::expected<base::DisconnectPacket, std::error_code>
{
    base::DisconnectPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.reason = static_cast<base::DisconnectFailReason>(*v);
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<DisconnectPacketMessages, std::monostate> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<DisconnectPacketMessages, std::monostate>> alt0{};
                {
                    auto v = Serializer<DisconnectPacketMessages>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<DisconnectPacketMessages, std::monostate>> alt0{};
                var0.emplace<1>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.messages = var0;
    }
    return out;
}

void Serializer<v800::DisconnectPacket>::serialize(BinaryWriter &stream, const v800::DisconnectPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.reason);
    stream.writeVarInt<std::uint32_t>((value.messages).index());
    switch ((value.messages).index()) {
        case 0: {
            Serializer<DisconnectPacketMessages>::serialize(stream, std::get<0>(value.messages));
            break;
        }
        case 1: {
            break;
        }
    }
}

auto Serializer<v800::DisconnectPacket>::deserialize(BinaryReader &stream) -> std::expected<v800::DisconnectPacket, std::error_code>
{
    v800::DisconnectPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.reason = static_cast<v800::DisconnectFailReason>(*v);
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<DisconnectPacketMessages, std::monostate> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<DisconnectPacketMessages, std::monostate>> alt0{};
                {
                    auto v = Serializer<DisconnectPacketMessages>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<DisconnectPacketMessages, std::monostate>> alt0{};
                var0.emplace<1>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.messages = var0;
    }
    return out;
}

void Serializer<v818::DisconnectPacket>::serialize(BinaryWriter &stream, const v818::DisconnectPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.reason);
    stream.writeVarInt<std::uint32_t>((value.messages).index());
    switch ((value.messages).index()) {
        case 0: {
            Serializer<DisconnectPacketMessages>::serialize(stream, std::get<0>(value.messages));
            break;
        }
        case 1: {
            break;
        }
    }
}

auto Serializer<v818::DisconnectPacket>::deserialize(BinaryReader &stream) -> std::expected<v818::DisconnectPacket, std::error_code>
{
    v818::DisconnectPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.reason = static_cast<v818::DisconnectFailReason>(*v);
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<DisconnectPacketMessages, std::monostate> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<DisconnectPacketMessages, std::monostate>> alt0{};
                {
                    auto v = Serializer<DisconnectPacketMessages>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<DisconnectPacketMessages, std::monostate>> alt0{};
                var0.emplace<1>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.messages = var0;
    }
    return out;
}

void Serializer<v827::DisconnectPacket>::serialize(BinaryWriter &stream, const v827::DisconnectPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.reason);
    stream.writeVarInt<std::uint32_t>((value.messages).index());
    switch ((value.messages).index()) {
        case 0: {
            Serializer<DisconnectPacketMessages>::serialize(stream, std::get<0>(value.messages));
            break;
        }
        case 1: {
            break;
        }
    }
}

auto Serializer<v827::DisconnectPacket>::deserialize(BinaryReader &stream) -> std::expected<v827::DisconnectPacket, std::error_code>
{
    v827::DisconnectPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.reason = static_cast<v827::DisconnectFailReason>(*v);
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<DisconnectPacketMessages, std::monostate> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<DisconnectPacketMessages, std::monostate>> alt0{};
                {
                    auto v = Serializer<DisconnectPacketMessages>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<DisconnectPacketMessages, std::monostate>> alt0{};
                var0.emplace<1>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.messages = var0;
    }
    return out;
}

void Serializer<v859::DisconnectPacket>::serialize(BinaryWriter &stream, const v859::DisconnectPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.reason);
    stream.writeVarInt<std::uint32_t>((value.messages).index());
    switch ((value.messages).index()) {
        case 0: {
            Serializer<DisconnectPacketMessages>::serialize(stream, std::get<0>(value.messages));
            break;
        }
        case 1: {
            break;
        }
    }
}

auto Serializer<v859::DisconnectPacket>::deserialize(BinaryReader &stream) -> std::expected<v859::DisconnectPacket, std::error_code>
{
    v859::DisconnectPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.reason = static_cast<v859::DisconnectFailReason>(*v);
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<DisconnectPacketMessages, std::monostate> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<DisconnectPacketMessages, std::monostate>> alt0{};
                {
                    auto v = Serializer<DisconnectPacketMessages>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<DisconnectPacketMessages, std::monostate>> alt0{};
                var0.emplace<1>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.messages = var0;
    }
    return out;
}

void Serializer<v898::DisconnectPacket>::serialize(BinaryWriter &stream, const v898::DisconnectPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.reason);
    stream.writeVarInt<std::uint32_t>((value.messages).index());
    switch ((value.messages).index()) {
        case 0: {
            Serializer<DisconnectPacketMessages>::serialize(stream, std::get<0>(value.messages));
            break;
        }
        case 1: {
            break;
        }
    }
}

auto Serializer<v898::DisconnectPacket>::deserialize(BinaryReader &stream) -> std::expected<v898::DisconnectPacket, std::error_code>
{
    v898::DisconnectPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.reason = static_cast<v898::DisconnectFailReason>(*v);
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<DisconnectPacketMessages, std::monostate> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<DisconnectPacketMessages, std::monostate>> alt0{};
                {
                    auto v = Serializer<DisconnectPacketMessages>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<DisconnectPacketMessages, std::monostate>> alt0{};
                var0.emplace<1>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.messages = var0;
    }
    return out;
}

void Serializer<v975::DisconnectPacket>::serialize(BinaryWriter &stream, const v975::DisconnectPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.reason);
    stream.writeVarInt<std::uint32_t>((value.messages).index());
    switch ((value.messages).index()) {
        case 0: {
            Serializer<DisconnectPacketMessages>::serialize(stream, std::get<0>(value.messages));
            break;
        }
        case 1: {
            break;
        }
    }
}

auto Serializer<v975::DisconnectPacket>::deserialize(BinaryReader &stream) -> std::expected<v975::DisconnectPacket, std::error_code>
{
    v975::DisconnectPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.reason = static_cast<v975::DisconnectFailReason>(*v);
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<DisconnectPacketMessages, std::monostate> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<DisconnectPacketMessages, std::monostate>> alt0{};
                {
                    auto v = Serializer<DisconnectPacketMessages>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<DisconnectPacketMessages, std::monostate>> alt0{};
                var0.emplace<1>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.messages = var0;
    }
    return out;
}

void Serializer<v1001::DisconnectPacket>::serialize(BinaryWriter &stream, const v1001::DisconnectPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.reason);
    stream.writeVarInt<std::uint32_t>((value.messages).index());
    switch ((value.messages).index()) {
        case 0: {
            Serializer<DisconnectPacketMessages>::serialize(stream, std::get<0>(value.messages));
            break;
        }
        case 1: {
            break;
        }
    }
}

auto Serializer<v1001::DisconnectPacket>::deserialize(BinaryReader &stream) -> std::expected<v1001::DisconnectPacket, std::error_code>
{
    v1001::DisconnectPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.reason = static_cast<v1001::DisconnectFailReason>(*v);
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<DisconnectPacketMessages, std::monostate> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<DisconnectPacketMessages, std::monostate>> alt0{};
                {
                    auto v = Serializer<DisconnectPacketMessages>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<DisconnectPacketMessages, std::monostate>> alt0{};
                var0.emplace<1>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.messages = var0;
    }
    return out;
}

void Serializer<v2168::DisconnectPacket>::serialize(BinaryWriter &stream, const v2168::DisconnectPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.reason);
    stream.writeVarInt<std::uint32_t>((value.messages).index());
    switch ((value.messages).index()) {
        case 0: {
            Serializer<DisconnectPacketMessages>::serialize(stream, std::get<0>(value.messages));
            break;
        }
        case 1: {
            break;
        }
    }
}

auto Serializer<v2168::DisconnectPacket>::deserialize(BinaryReader &stream) -> std::expected<v2168::DisconnectPacket, std::error_code>
{
    v2168::DisconnectPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.reason = static_cast<v2168::DisconnectFailReason>(*v);
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<DisconnectPacketMessages, std::monostate> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<DisconnectPacketMessages, std::monostate>> alt0{};
                {
                    auto v = Serializer<DisconnectPacketMessages>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<DisconnectPacketMessages, std::monostate>> alt0{};
                var0.emplace<1>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.messages = var0;
    }
    return out;
}

void Serializer<v2193::DisconnectPacket>::serialize(BinaryWriter &stream, const v2193::DisconnectPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.reason);
    stream.writeVarInt<std::uint32_t>((value.messages).index());
    switch ((value.messages).index()) {
        case 0: {
            Serializer<DisconnectPacketMessages>::serialize(stream, std::get<0>(value.messages));
            break;
        }
        case 1: {
            break;
        }
    }
}

auto Serializer<v2193::DisconnectPacket>::deserialize(BinaryReader &stream) -> std::expected<v2193::DisconnectPacket, std::error_code>
{
    v2193::DisconnectPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.reason = static_cast<v2193::DisconnectFailReason>(*v);
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<DisconnectPacketMessages, std::monostate> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<DisconnectPacketMessages, std::monostate>> alt0{};
                {
                    auto v = Serializer<DisconnectPacketMessages>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<DisconnectPacketMessages, std::monostate>> alt0{};
                var0.emplace<1>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.messages = var0;
    }
    return out;
}

void Serializer<v2225::DisconnectPacket>::serialize(BinaryWriter &stream, const v2225::DisconnectPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.reason);
    stream.writeVarInt<std::uint32_t>((value.messages).index());
    switch ((value.messages).index()) {
        case 0: {
            Serializer<DisconnectPacketMessages>::serialize(stream, std::get<0>(value.messages));
            break;
        }
        case 1: {
            break;
        }
    }
}

auto Serializer<v2225::DisconnectPacket>::deserialize(BinaryReader &stream) -> std::expected<v2225::DisconnectPacket, std::error_code>
{
    v2225::DisconnectPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.reason = static_cast<v2225::DisconnectFailReason>(*v);
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<DisconnectPacketMessages, std::monostate> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<DisconnectPacketMessages, std::monostate>> alt0{};
                {
                    auto v = Serializer<DisconnectPacketMessages>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<DisconnectPacketMessages, std::monostate>> alt0{};
                var0.emplace<1>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.messages = var0;
    }
    return out;
}

void Serializer<base::PacketViolationWarningPacket>::serialize(BinaryWriter &stream, const base::PacketViolationWarningPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.violation_type);
    stream.writeVarInt<std::int32_t>(value.violation_severity);
    stream.writeVarInt<std::int32_t>(value.violating_packet_id);
    stream.write(value.violation_context);
}

auto Serializer<base::PacketViolationWarningPacket>::deserialize(BinaryReader &stream) -> std::expected<base::PacketViolationWarningPacket, std::error_code>
{
    base::PacketViolationWarningPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.violation_type = static_cast<PacketViolationType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.violation_severity = static_cast<PacketViolationSeverity>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.violating_packet_id = static_cast<base::MinecraftPacketIds>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.violation_context = *v;
    }
    return out;
}

void Serializer<v748::PacketViolationWarningPacket>::serialize(BinaryWriter &stream, const v748::PacketViolationWarningPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.violation_type);
    stream.writeVarInt<std::int32_t>(value.violation_severity);
    stream.writeVarInt<std::int32_t>(value.violating_packet_id);
    stream.write(value.violation_context);
}

auto Serializer<v748::PacketViolationWarningPacket>::deserialize(BinaryReader &stream) -> std::expected<v748::PacketViolationWarningPacket, std::error_code>
{
    v748::PacketViolationWarningPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.violation_type = static_cast<PacketViolationType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.violation_severity = static_cast<PacketViolationSeverity>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.violating_packet_id = static_cast<v748::MinecraftPacketIds>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.violation_context = *v;
    }
    return out;
}

void Serializer<v766::PacketViolationWarningPacket>::serialize(BinaryWriter &stream, const v766::PacketViolationWarningPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.violation_type);
    stream.writeVarInt<std::int32_t>(value.violation_severity);
    stream.writeVarInt<std::int32_t>(value.violating_packet_id);
    stream.write(value.violation_context);
}

auto Serializer<v766::PacketViolationWarningPacket>::deserialize(BinaryReader &stream) -> std::expected<v766::PacketViolationWarningPacket, std::error_code>
{
    v766::PacketViolationWarningPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.violation_type = static_cast<PacketViolationType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.violation_severity = static_cast<PacketViolationSeverity>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.violating_packet_id = static_cast<v766::MinecraftPacketIds>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.violation_context = *v;
    }
    return out;
}

void Serializer<v776::PacketViolationWarningPacket>::serialize(BinaryWriter &stream, const v776::PacketViolationWarningPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.violation_type);
    stream.writeVarInt<std::int32_t>(value.violation_severity);
    stream.writeVarInt<std::int32_t>(value.violating_packet_id);
    stream.write(value.violation_context);
}

auto Serializer<v776::PacketViolationWarningPacket>::deserialize(BinaryReader &stream) -> std::expected<v776::PacketViolationWarningPacket, std::error_code>
{
    v776::PacketViolationWarningPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.violation_type = static_cast<PacketViolationType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.violation_severity = static_cast<PacketViolationSeverity>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.violating_packet_id = static_cast<v776::MinecraftPacketIds>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.violation_context = *v;
    }
    return out;
}

void Serializer<v786::PacketViolationWarningPacket>::serialize(BinaryWriter &stream, const v786::PacketViolationWarningPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.violation_type);
    stream.writeVarInt<std::int32_t>(value.violation_severity);
    stream.writeVarInt<std::int32_t>(value.violating_packet_id);
    stream.write(value.violation_context);
}

auto Serializer<v786::PacketViolationWarningPacket>::deserialize(BinaryReader &stream) -> std::expected<v786::PacketViolationWarningPacket, std::error_code>
{
    v786::PacketViolationWarningPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.violation_type = static_cast<PacketViolationType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.violation_severity = static_cast<PacketViolationSeverity>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.violating_packet_id = static_cast<v786::MinecraftPacketIds>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.violation_context = *v;
    }
    return out;
}

void Serializer<v800::PacketViolationWarningPacket>::serialize(BinaryWriter &stream, const v800::PacketViolationWarningPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.violation_type);
    stream.writeVarInt<std::int32_t>(value.violation_severity);
    stream.writeVarInt<std::int32_t>(value.violating_packet_id);
    stream.write(value.violation_context);
}

auto Serializer<v800::PacketViolationWarningPacket>::deserialize(BinaryReader &stream) -> std::expected<v800::PacketViolationWarningPacket, std::error_code>
{
    v800::PacketViolationWarningPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.violation_type = static_cast<PacketViolationType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.violation_severity = static_cast<PacketViolationSeverity>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.violating_packet_id = static_cast<v800::MinecraftPacketIds>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.violation_context = *v;
    }
    return out;
}

void Serializer<v818::PacketViolationWarningPacket>::serialize(BinaryWriter &stream, const v818::PacketViolationWarningPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.violation_type);
    stream.writeVarInt<std::int32_t>(value.violation_severity);
    stream.writeVarInt<std::int32_t>(value.violating_packet_id);
    stream.write(value.violation_context);
}

auto Serializer<v818::PacketViolationWarningPacket>::deserialize(BinaryReader &stream) -> std::expected<v818::PacketViolationWarningPacket, std::error_code>
{
    v818::PacketViolationWarningPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.violation_type = static_cast<PacketViolationType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.violation_severity = static_cast<PacketViolationSeverity>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.violating_packet_id = static_cast<v818::MinecraftPacketIds>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.violation_context = *v;
    }
    return out;
}

void Serializer<v844::PacketViolationWarningPacket>::serialize(BinaryWriter &stream, const v844::PacketViolationWarningPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.violation_type);
    stream.writeVarInt<std::int32_t>(value.violation_severity);
    stream.writeVarInt<std::int32_t>(value.violating_packet_id);
    stream.write(value.violation_context);
}

auto Serializer<v844::PacketViolationWarningPacket>::deserialize(BinaryReader &stream) -> std::expected<v844::PacketViolationWarningPacket, std::error_code>
{
    v844::PacketViolationWarningPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.violation_type = static_cast<PacketViolationType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.violation_severity = static_cast<PacketViolationSeverity>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.violating_packet_id = static_cast<v844::MinecraftPacketIds>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.violation_context = *v;
    }
    return out;
}

void Serializer<v859::PacketViolationWarningPacket>::serialize(BinaryWriter &stream, const v859::PacketViolationWarningPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.violation_type);
    stream.writeVarInt<std::int32_t>(value.violation_severity);
    stream.writeVarInt<std::int32_t>(value.violating_packet_id);
    stream.write(value.violation_context);
}

auto Serializer<v859::PacketViolationWarningPacket>::deserialize(BinaryReader &stream) -> std::expected<v859::PacketViolationWarningPacket, std::error_code>
{
    v859::PacketViolationWarningPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.violation_type = static_cast<PacketViolationType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.violation_severity = static_cast<PacketViolationSeverity>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.violating_packet_id = static_cast<v859::MinecraftPacketIds>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.violation_context = *v;
    }
    return out;
}

void Serializer<v898::PacketViolationWarningPacket>::serialize(BinaryWriter &stream, const v898::PacketViolationWarningPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.violation_type);
    stream.writeVarInt<std::int32_t>(value.violation_severity);
    stream.writeVarInt<std::int32_t>(value.violating_packet_id);
    stream.write(value.violation_context);
}

auto Serializer<v898::PacketViolationWarningPacket>::deserialize(BinaryReader &stream) -> std::expected<v898::PacketViolationWarningPacket, std::error_code>
{
    v898::PacketViolationWarningPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.violation_type = static_cast<PacketViolationType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.violation_severity = static_cast<PacketViolationSeverity>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.violating_packet_id = static_cast<v898::MinecraftPacketIds>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.violation_context = *v;
    }
    return out;
}

void Serializer<v924::PacketViolationWarningPacket>::serialize(BinaryWriter &stream, const v924::PacketViolationWarningPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.violation_type);
    stream.writeVarInt<std::int32_t>(value.violation_severity);
    stream.writeVarInt<std::int32_t>(value.violating_packet_id);
    stream.write(value.violation_context);
}

auto Serializer<v924::PacketViolationWarningPacket>::deserialize(BinaryReader &stream) -> std::expected<v924::PacketViolationWarningPacket, std::error_code>
{
    v924::PacketViolationWarningPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.violation_type = static_cast<PacketViolationType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.violation_severity = static_cast<PacketViolationSeverity>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.violating_packet_id = static_cast<v924::MinecraftPacketIds>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.violation_context = *v;
    }
    return out;
}

void Serializer<v944::PacketViolationWarningPacket>::serialize(BinaryWriter &stream, const v944::PacketViolationWarningPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.violation_type);
    stream.writeVarInt<std::int32_t>(value.violation_severity);
    stream.writeVarInt<std::int32_t>(value.violating_packet_id);
    stream.write(value.violation_context);
}

auto Serializer<v944::PacketViolationWarningPacket>::deserialize(BinaryReader &stream) -> std::expected<v944::PacketViolationWarningPacket, std::error_code>
{
    v944::PacketViolationWarningPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.violation_type = static_cast<PacketViolationType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.violation_severity = static_cast<PacketViolationSeverity>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.violating_packet_id = static_cast<v944::MinecraftPacketIds>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.violation_context = *v;
    }
    return out;
}

void Serializer<v975::PacketViolationWarningPacket>::serialize(BinaryWriter &stream, const v975::PacketViolationWarningPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.violation_type);
    stream.writeVarInt<std::int32_t>(value.violation_severity);
    stream.writeVarInt<std::int32_t>(value.violating_packet_id);
    stream.write(value.violation_context);
}

auto Serializer<v975::PacketViolationWarningPacket>::deserialize(BinaryReader &stream) -> std::expected<v975::PacketViolationWarningPacket, std::error_code>
{
    v975::PacketViolationWarningPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.violation_type = static_cast<PacketViolationType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.violation_severity = static_cast<PacketViolationSeverity>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.violating_packet_id = static_cast<v975::MinecraftPacketIds>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.violation_context = *v;
    }
    return out;
}

void Serializer<v1001::PacketViolationWarningPacket>::serialize(BinaryWriter &stream, const v1001::PacketViolationWarningPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.violation_type);
    stream.writeVarInt<std::int32_t>(value.violation_severity);
    stream.writeVarInt<std::int32_t>(value.violating_packet_id);
    stream.write(value.violation_context);
}

auto Serializer<v1001::PacketViolationWarningPacket>::deserialize(BinaryReader &stream) -> std::expected<v1001::PacketViolationWarningPacket, std::error_code>
{
    v1001::PacketViolationWarningPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.violation_type = static_cast<PacketViolationType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.violation_severity = static_cast<PacketViolationSeverity>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.violating_packet_id = static_cast<v1001::MinecraftPacketIds>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.violation_context = *v;
    }
    return out;
}

void Serializer<v2193::PacketViolationWarningPacket>::serialize(BinaryWriter &stream, const v2193::PacketViolationWarningPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.violation_type);
    stream.writeVarInt<std::int32_t>(value.violation_severity);
    stream.writeVarInt<std::int32_t>(value.violating_packet_id);
    stream.write(value.violation_context);
}

auto Serializer<v2193::PacketViolationWarningPacket>::deserialize(BinaryReader &stream) -> std::expected<v2193::PacketViolationWarningPacket, std::error_code>
{
    v2193::PacketViolationWarningPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.violation_type = static_cast<PacketViolationType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.violation_severity = static_cast<PacketViolationSeverity>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.violating_packet_id = static_cast<v2193::MinecraftPacketIds>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.violation_context = *v;
    }
    return out;
}

void Serializer<v2225::PacketViolationWarningPacket>::serialize(BinaryWriter &stream, const v2225::PacketViolationWarningPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.violation_type);
    stream.writeVarInt<std::int32_t>(value.violation_severity);
    stream.writeVarInt<std::int32_t>(value.violating_packet_id);
    stream.write(value.violation_context);
}

auto Serializer<v2225::PacketViolationWarningPacket>::deserialize(BinaryReader &stream) -> std::expected<v2225::PacketViolationWarningPacket, std::error_code>
{
    v2225::PacketViolationWarningPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.violation_type = static_cast<PacketViolationType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.violation_severity = static_cast<PacketViolationSeverity>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.violating_packet_id = static_cast<v2225::MinecraftPacketIds>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.violation_context = *v;
    }
    return out;
}

void Serializer<RequestNetworkSettingsPacket>::serialize(BinaryWriter &stream, const RequestNetworkSettingsPacket &value)
{
    stream.write<std::int32_t, std::endian::big>(value.client_network_version);
}

auto Serializer<RequestNetworkSettingsPacket>::deserialize(BinaryReader &stream) -> std::expected<RequestNetworkSettingsPacket, std::error_code>
{
    RequestNetworkSettingsPacket out;
    {
        auto v = stream.read<std::int32_t, std::endian::big>();
        if (!v) return std::unexpected(v.error());
        out.client_network_version = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<ClientToServerHandshakePacket>::serialize(BinaryWriter &stream, const ClientToServerHandshakePacket &value)
{
}

auto Serializer<ClientToServerHandshakePacket>::deserialize(BinaryReader &stream) -> std::expected<ClientToServerHandshakePacket, std::error_code>
{
    ClientToServerHandshakePacket out;
    return out;
}

void Serializer<NetworkStackLatencyPacket>::serialize(BinaryWriter &stream, const NetworkStackLatencyPacket &value)
{
    stream.write<std::uint64_t>(value.create_time);
    stream.write<bool>(value.from_server);
}

auto Serializer<NetworkStackLatencyPacket>::deserialize(BinaryReader &stream) -> std::expected<NetworkStackLatencyPacket, std::error_code>
{
    NetworkStackLatencyPacket out;
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.create_time = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.from_server = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<ClientCacheStatusPacket>::serialize(BinaryWriter &stream, const ClientCacheStatusPacket &value)
{
    stream.write<bool>(value.enabled);
}

auto Serializer<ClientCacheStatusPacket>::deserialize(BinaryReader &stream) -> std::expected<ClientCacheStatusPacket, std::error_code>
{
    ClientCacheStatusPacket out;
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.enabled = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<ServerStatsPacket>::serialize(BinaryWriter &stream, const ServerStatsPacket &value)
{
    stream.write<float>(value.server_time);
    stream.write<float>(value.network_time);
}

auto Serializer<ServerStatsPacket>::deserialize(BinaryReader &stream) -> std::expected<ServerStatsPacket, std::error_code>
{
    ServerStatsPacket out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.server_time = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.network_time = static_cast<float>(*v);
    }
    return out;
}

void Serializer<WebSocketPacketData>::serialize(BinaryWriter &stream, const WebSocketPacketData &value)
{
    stream.write(value.ip);
}

auto Serializer<WebSocketPacketData>::deserialize(BinaryReader &stream) -> std::expected<WebSocketPacketData, std::error_code>
{
    WebSocketPacketData out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.ip = *v;
    }
    return out;
}

void Serializer<AutomationClientConnectPacket>::serialize(BinaryWriter &stream, const AutomationClientConnectPacket &value)
{
    Serializer<WebSocketPacketData>::serialize(stream, value.web_socket_data);
}

auto Serializer<AutomationClientConnectPacket>::deserialize(BinaryReader &stream) -> std::expected<AutomationClientConnectPacket, std::error_code>
{
    AutomationClientConnectPacket out;
    {
        auto v = Serializer<WebSocketPacketData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.web_socket_data = *v;
    }
    return out;
}

void Serializer<MissingBlobData>::serialize(BinaryWriter &stream, const MissingBlobData &value)
{
    stream.write<std::uint64_t>(value.blob_id);
    stream.write(value.blob_data);
}

auto Serializer<MissingBlobData>::deserialize(BinaryReader &stream) -> std::expected<MissingBlobData, std::error_code>
{
    MissingBlobData out;
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.blob_id = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.blob_data = *v;
    }
    return out;
}

void Serializer<ClientCacheMissResponsePacket>::serialize(BinaryWriter &stream, const ClientCacheMissResponsePacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.blobs.size());
    for (const auto &e0 : value.blobs) {
        Serializer<MissingBlobData>::serialize(stream, e0);
    }
}

auto Serializer<ClientCacheMissResponsePacket>::deserialize(BinaryReader &stream) -> std::expected<ClientCacheMissResponsePacket, std::error_code>
{
    ClientCacheMissResponsePacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.blobs.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.blobs.emplace_back();
            auto v = Serializer<MissingBlobData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.blobs.back() = *v;
        }
    }
    return out;
}

void Serializer<NetworkSettingsPacket>::serialize(BinaryWriter &stream, const NetworkSettingsPacket &value)
{
    stream.write<std::uint16_t>(value.compression_threshold);
    stream.write<std::uint16_t>(value.compression_algorithm);
    stream.write<bool>(value.client_throttle_enabled);
    stream.write<std::uint8_t>(value.client_throttle_threshold);
    stream.write<float>(value.client_throttle_scalar);
}

auto Serializer<NetworkSettingsPacket>::deserialize(BinaryReader &stream) -> std::expected<NetworkSettingsPacket, std::error_code>
{
    NetworkSettingsPacket out;
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.compression_threshold = static_cast<std::uint16_t>(*v);
    }
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.compression_algorithm = static_cast<PacketCompressionAlgorithm>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.client_throttle_enabled = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.client_throttle_threshold = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.client_throttle_scalar = static_cast<float>(*v);
    }
    return out;
}

void Serializer<SubClientLoginPacket>::serialize(BinaryWriter &stream, const SubClientLoginPacket &value)
{
    stream.write(value.connection_request);
}

auto Serializer<SubClientLoginPacket>::deserialize(BinaryReader &stream) -> std::expected<SubClientLoginPacket, std::error_code>
{
    SubClientLoginPacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.connection_request = *v;
    }
    return out;
}

void Serializer<base::ClientCacheBlobStatusPacket>::serialize(BinaryWriter &stream, const base::ClientCacheBlobStatusPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.missing_count);
    stream.writeVarInt<std::uint32_t>(value.found_count);
    for (const auto &e0 : value.missing_ids) {
        stream.write<std::uint64_t>(e0);
    }
    for (const auto &e0 : value.found_ids) {
        stream.write<std::uint64_t>(e0);
    }
}

auto Serializer<base::ClientCacheBlobStatusPacket>::deserialize(BinaryReader &stream) -> std::expected<base::ClientCacheBlobStatusPacket, std::error_code>
{
    base::ClientCacheBlobStatusPacket out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.missing_count = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.found_count = static_cast<std::uint32_t>(*v);
    }
    {
        out.missing_ids.clear();
        for (auto rep0 = out.missing_count; rep0 > 0; --rep0) {
            out.missing_ids.emplace_back();
            auto v = stream.read<std::uint64_t>();
            if (!v) return std::unexpected(v.error());
            out.missing_ids.back() = static_cast<std::uint64_t>(*v);
        }
    }
    {
        out.found_ids.clear();
        for (auto rep0 = out.found_count; rep0 > 0; --rep0) {
            out.found_ids.emplace_back();
            auto v = stream.read<std::uint64_t>();
            if (!v) return std::unexpected(v.error());
            out.found_ids.back() = static_cast<std::uint64_t>(*v);
        }
    }
    return out;
}

void Serializer<v1001::ClientCacheBlobStatusPacket>::serialize(BinaryWriter &stream, const v1001::ClientCacheBlobStatusPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.missing_ids.size());
    for (const auto &e0 : value.missing_ids) {
        stream.write<std::uint64_t>(e0);
    }
    stream.writeVarInt<std::uint32_t>(value.found_ids.size());
    for (const auto &e0 : value.found_ids) {
        stream.write<std::uint64_t>(e0);
    }
}

auto Serializer<v1001::ClientCacheBlobStatusPacket>::deserialize(BinaryReader &stream) -> std::expected<v1001::ClientCacheBlobStatusPacket, std::error_code>
{
    v1001::ClientCacheBlobStatusPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.missing_ids.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.missing_ids.emplace_back();
            auto v = stream.read<std::uint64_t>();
            if (!v) return std::unexpected(v.error());
            out.missing_ids.back() = static_cast<std::uint64_t>(*v);
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.found_ids.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.found_ids.emplace_back();
            auto v = stream.read<std::uint64_t>();
            if (!v) return std::unexpected(v.error());
            out.found_ids.back() = static_cast<std::uint64_t>(*v);
        }
    }
    return out;
}

void Serializer<NetworkPermissions>::serialize(BinaryWriter &stream, const NetworkPermissions &value)
{
    stream.write<bool>(value.server_auth_sound_enabled);
}

auto Serializer<NetworkPermissions>::deserialize(BinaryReader &stream) -> std::expected<NetworkPermissions, std::error_code>
{
    NetworkPermissions out;
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.server_auth_sound_enabled = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<base::NetworkBlockPosition>::serialize(BinaryWriter &stream, const base::NetworkBlockPosition &value)
{
    stream.writeVarInt<std::int32_t>(value.x);
    stream.writeVarInt<std::uint32_t>(value.y);
    stream.writeVarInt<std::int32_t>(value.z);
}

auto Serializer<base::NetworkBlockPosition>::deserialize(BinaryReader &stream) -> std::expected<base::NetworkBlockPosition, std::error_code>
{
    base::NetworkBlockPosition out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.x = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.y = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.z = static_cast<std::int32_t>(*v);
    }
    return out;
}

}  // namespace bedrock::protocol
