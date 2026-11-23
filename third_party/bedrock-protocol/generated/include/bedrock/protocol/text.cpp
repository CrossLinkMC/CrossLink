#include <bedrock/protocol/text.h>

namespace bedrock::protocol {


void Serializer<base::TextPacket::MessageOnly>::serialize(BinaryWriter &stream, const base::TextPacket::MessageOnly &value)
{
    stream.write<std::uint8_t>(value.type);
    stream.write(value.message);
}

auto Serializer<base::TextPacket::MessageOnly>::deserialize(BinaryReader &stream) -> std::expected<base::TextPacket::MessageOnly, std::error_code>
{
    base::TextPacket::MessageOnly out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<TextPacketType>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.message = *v;
    }
    return out;
}

void Serializer<base::TextPacket::AuthorAndMessage>::serialize(BinaryWriter &stream, const base::TextPacket::AuthorAndMessage &value)
{
    stream.write<std::uint8_t>(value.type);
    stream.write(value.author);
    stream.write(value.message);
}

auto Serializer<base::TextPacket::AuthorAndMessage>::deserialize(BinaryReader &stream) -> std::expected<base::TextPacket::AuthorAndMessage, std::error_code>
{
    base::TextPacket::AuthorAndMessage out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<TextPacketType>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.author = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.message = *v;
    }
    return out;
}

void Serializer<base::TextPacket::MessageAndParams>::serialize(BinaryWriter &stream, const base::TextPacket::MessageAndParams &value)
{
    stream.write<std::uint8_t>(value.type);
    stream.write(value.message);
    stream.writeVarInt<std::uint32_t>(value.params.size());
    for (const auto &e0 : value.params) {
        stream.write(e0);
    }
}

auto Serializer<base::TextPacket::MessageAndParams>::deserialize(BinaryReader &stream) -> std::expected<base::TextPacket::MessageAndParams, std::error_code>
{
    base::TextPacket::MessageAndParams out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<TextPacketType>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.message = *v;
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.params.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.params.emplace_back();
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.params.back() = *v;
        }
    }
    return out;
}

void Serializer<v898::TextPacket::MessageOnly>::serialize(BinaryWriter &stream, const v898::TextPacket::MessageOnly &value)
{
    stream.write("raw");
    stream.write("tip");
    stream.write("systemmessage");
    stream.write("textobjectwhisper");
    stream.write("textobjectannouncement");
    stream.write("textobject");
    stream.write<std::uint8_t>(value.type);
    stream.write(value.message);
}

auto Serializer<v898::TextPacket::MessageOnly>::deserialize(BinaryReader &stream) -> std::expected<v898::TextPacket::MessageOnly, std::error_code>
{
    v898::TextPacket::MessageOnly out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        if (*v != "raw") {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        if (*v != "tip") {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        if (*v != "systemmessage") {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        if (*v != "textobjectwhisper") {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        if (*v != "textobjectannouncement") {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        if (*v != "textobject") {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<TextPacketType>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.message = *v;
    }
    return out;
}

void Serializer<v898::TextPacket::AuthorAndMessage>::serialize(BinaryWriter &stream, const v898::TextPacket::AuthorAndMessage &value)
{
    stream.write("chat");
    stream.write("whisper");
    stream.write("announcement");
    stream.write<std::uint8_t>(value.type);
    stream.write(value.author);
    stream.write(value.message);
}

auto Serializer<v898::TextPacket::AuthorAndMessage>::deserialize(BinaryReader &stream) -> std::expected<v898::TextPacket::AuthorAndMessage, std::error_code>
{
    v898::TextPacket::AuthorAndMessage out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        if (*v != "chat") {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        if (*v != "whisper") {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        if (*v != "announcement") {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<TextPacketType>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.author = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.message = *v;
    }
    return out;
}

void Serializer<v898::TextPacket::MessageAndParams>::serialize(BinaryWriter &stream, const v898::TextPacket::MessageAndParams &value)
{
    stream.write("translate");
    stream.write("popup");
    stream.write("jukeboxpopup");
    stream.write<std::uint8_t>(value.type);
    stream.write(value.message);
    stream.writeVarInt<std::uint32_t>(value.params.size());
    for (const auto &e0 : value.params) {
        stream.write(e0);
    }
}

auto Serializer<v898::TextPacket::MessageAndParams>::deserialize(BinaryReader &stream) -> std::expected<v898::TextPacket::MessageAndParams, std::error_code>
{
    v898::TextPacket::MessageAndParams out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        if (*v != "translate") {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        if (*v != "popup") {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        if (*v != "jukeboxpopup") {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<TextPacketType>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.message = *v;
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.params.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.params.emplace_back();
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.params.back() = *v;
        }
    }
    return out;
}

void Serializer<v924::TextPacket::MessageOnly>::serialize(BinaryWriter &stream, const v924::TextPacket::MessageOnly &value)
{
    stream.write<std::uint8_t>(value.type);
    stream.write(value.message);
}

auto Serializer<v924::TextPacket::MessageOnly>::deserialize(BinaryReader &stream) -> std::expected<v924::TextPacket::MessageOnly, std::error_code>
{
    v924::TextPacket::MessageOnly out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<TextPacketType>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.message = *v;
    }
    return out;
}

void Serializer<v924::TextPacket::AuthorAndMessage>::serialize(BinaryWriter &stream, const v924::TextPacket::AuthorAndMessage &value)
{
    stream.write<std::uint8_t>(value.type);
    stream.write(value.author);
    stream.write(value.message);
}

auto Serializer<v924::TextPacket::AuthorAndMessage>::deserialize(BinaryReader &stream) -> std::expected<v924::TextPacket::AuthorAndMessage, std::error_code>
{
    v924::TextPacket::AuthorAndMessage out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<TextPacketType>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.author = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.message = *v;
    }
    return out;
}

void Serializer<v924::TextPacket::MessageAndParams>::serialize(BinaryWriter &stream, const v924::TextPacket::MessageAndParams &value)
{
    stream.write<std::uint8_t>(value.type);
    stream.write(value.message);
    stream.writeVarInt<std::uint32_t>(value.params.size());
    for (const auto &e0 : value.params) {
        stream.write(e0);
    }
}

auto Serializer<v924::TextPacket::MessageAndParams>::deserialize(BinaryReader &stream) -> std::expected<v924::TextPacket::MessageAndParams, std::error_code>
{
    v924::TextPacket::MessageAndParams out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<TextPacketType>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.message = *v;
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.params.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.params.emplace_back();
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.params.back() = *v;
        }
    }
    return out;
}

void Serializer<base::TextPacket>::serialize(BinaryWriter &stream, const base::TextPacket &value)
{
    stream.write<bool>(value.localize);
    stream.writeVarInt<std::uint32_t>((value.body).index());
    switch ((value.body).index()) {
        case 0: {
            Serializer<base::TextPacket::MessageOnly>::serialize(stream, std::get<0>(value.body));
            break;
        }
        case 1: {
            Serializer<base::TextPacket::AuthorAndMessage>::serialize(stream, std::get<1>(value.body));
            break;
        }
        case 2: {
            Serializer<base::TextPacket::MessageAndParams>::serialize(stream, std::get<2>(value.body));
            break;
        }
    }
    stream.write(value.xuid);
    stream.write(value.platform_id);
    stream.write<bool>(value.filtered_message.has_value());
    if (value.filtered_message.has_value()) {
        stream.write((*value.filtered_message));
    }
}

auto Serializer<base::TextPacket>::deserialize(BinaryReader &stream) -> std::expected<base::TextPacket, std::error_code>
{
    base::TextPacket out;
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.localize = static_cast<bool>(*v);
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<base::TextPacket::MessageOnly, base::TextPacket::AuthorAndMessage, base::TextPacket::MessageAndParams> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<base::TextPacket::MessageOnly, base::TextPacket::AuthorAndMessage, base::TextPacket::MessageAndParams>> alt0{};
                {
                    auto v = Serializer<base::TextPacket::MessageOnly>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<base::TextPacket::MessageOnly, base::TextPacket::AuthorAndMessage, base::TextPacket::MessageAndParams>> alt0{};
                {
                    auto v = Serializer<base::TextPacket::AuthorAndMessage>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<base::TextPacket::MessageOnly, base::TextPacket::AuthorAndMessage, base::TextPacket::MessageAndParams>> alt0{};
                {
                    auto v = Serializer<base::TextPacket::MessageAndParams>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.body = var0;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.xuid = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.platform_id = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::string staged{};
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.filtered_message = std::move(staged);
        }
    }
    return out;
}

void Serializer<v898::TextPacket>::serialize(BinaryWriter &stream, const v898::TextPacket &value)
{
    stream.write<bool>(value.localize);
    stream.writeVarInt<std::uint32_t>((value.body).index());
    switch ((value.body).index()) {
        case 0: {
            Serializer<v898::TextPacket::MessageOnly>::serialize(stream, std::get<0>(value.body));
            break;
        }
        case 1: {
            Serializer<v898::TextPacket::AuthorAndMessage>::serialize(stream, std::get<1>(value.body));
            break;
        }
        case 2: {
            Serializer<v898::TextPacket::MessageAndParams>::serialize(stream, std::get<2>(value.body));
            break;
        }
    }
    stream.write(value.xuid);
    stream.write(value.platform_id);
    stream.write<bool>(value.filtered_message.has_value());
    if (value.filtered_message.has_value()) {
        stream.write((*value.filtered_message));
    }
}

auto Serializer<v898::TextPacket>::deserialize(BinaryReader &stream) -> std::expected<v898::TextPacket, std::error_code>
{
    v898::TextPacket out;
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.localize = static_cast<bool>(*v);
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v898::TextPacket::MessageOnly, v898::TextPacket::AuthorAndMessage, v898::TextPacket::MessageAndParams> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v898::TextPacket::MessageOnly, v898::TextPacket::AuthorAndMessage, v898::TextPacket::MessageAndParams>> alt0{};
                {
                    auto v = Serializer<v898::TextPacket::MessageOnly>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v898::TextPacket::MessageOnly, v898::TextPacket::AuthorAndMessage, v898::TextPacket::MessageAndParams>> alt0{};
                {
                    auto v = Serializer<v898::TextPacket::AuthorAndMessage>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<v898::TextPacket::MessageOnly, v898::TextPacket::AuthorAndMessage, v898::TextPacket::MessageAndParams>> alt0{};
                {
                    auto v = Serializer<v898::TextPacket::MessageAndParams>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.body = var0;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.xuid = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.platform_id = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::string staged{};
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.filtered_message = std::move(staged);
        }
    }
    return out;
}

void Serializer<v924::TextPacket>::serialize(BinaryWriter &stream, const v924::TextPacket &value)
{
    stream.write<bool>(value.localize);
    stream.writeVarInt<std::uint32_t>((value.body).index());
    switch ((value.body).index()) {
        case 0: {
            Serializer<v924::TextPacket::MessageOnly>::serialize(stream, std::get<0>(value.body));
            break;
        }
        case 1: {
            Serializer<v924::TextPacket::AuthorAndMessage>::serialize(stream, std::get<1>(value.body));
            break;
        }
        case 2: {
            Serializer<v924::TextPacket::MessageAndParams>::serialize(stream, std::get<2>(value.body));
            break;
        }
    }
    stream.write(value.xuid);
    stream.write(value.platform_id);
    stream.write<bool>(value.filtered_message.has_value());
    if (value.filtered_message.has_value()) {
        stream.write((*value.filtered_message));
    }
}

auto Serializer<v924::TextPacket>::deserialize(BinaryReader &stream) -> std::expected<v924::TextPacket, std::error_code>
{
    v924::TextPacket out;
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.localize = static_cast<bool>(*v);
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v924::TextPacket::MessageOnly, v924::TextPacket::AuthorAndMessage, v924::TextPacket::MessageAndParams> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v924::TextPacket::MessageOnly, v924::TextPacket::AuthorAndMessage, v924::TextPacket::MessageAndParams>> alt0{};
                {
                    auto v = Serializer<v924::TextPacket::MessageOnly>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v924::TextPacket::MessageOnly, v924::TextPacket::AuthorAndMessage, v924::TextPacket::MessageAndParams>> alt0{};
                {
                    auto v = Serializer<v924::TextPacket::AuthorAndMessage>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<v924::TextPacket::MessageOnly, v924::TextPacket::AuthorAndMessage, v924::TextPacket::MessageAndParams>> alt0{};
                {
                    auto v = Serializer<v924::TextPacket::MessageAndParams>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.body = var0;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.xuid = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.platform_id = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::string staged{};
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.filtered_message = std::move(staged);
        }
    }
    return out;
}

void Serializer<ToastRequestPacket>::serialize(BinaryWriter &stream, const ToastRequestPacket &value)
{
    stream.write(value.title);
    stream.write(value.content);
}

auto Serializer<ToastRequestPacket>::deserialize(BinaryReader &stream) -> std::expected<ToastRequestPacket, std::error_code>
{
    ToastRequestPacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.title = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.content = *v;
    }
    return out;
}

void Serializer<SetTitlePacket>::serialize(BinaryWriter &stream, const SetTitlePacket &value)
{
    stream.writeVarInt<std::int32_t>(value.type);
    stream.write(value.title_text);
    stream.writeVarInt<std::int32_t>(value.fade_in_time);
    stream.writeVarInt<std::int32_t>(value.stay_time);
    stream.writeVarInt<std::int32_t>(value.fade_out_time);
    stream.write(value.xuid);
    stream.write(value.platform_online_id);
    stream.write(value.filtered_title_text);
}

auto Serializer<SetTitlePacket>::deserialize(BinaryReader &stream) -> std::expected<SetTitlePacket, std::error_code>
{
    SetTitlePacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<SetTitlePacket::TitleType>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.title_text = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.fade_in_time = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.stay_time = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.fade_out_time = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.xuid = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.platform_online_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.filtered_title_text = *v;
    }
    return out;
}

}  // namespace bedrock::protocol
