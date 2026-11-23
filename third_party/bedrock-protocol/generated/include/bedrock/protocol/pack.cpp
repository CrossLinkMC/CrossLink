#include <bedrock/protocol/pack.h>

namespace bedrock::protocol {


void Serializer<SemVersion>::serialize(BinaryWriter &stream, const SemVersion &value)
{
    stream.write(value.version);
}

auto Serializer<SemVersion>::deserialize(BinaryReader &stream) -> std::expected<SemVersion, std::error_code>
{
    SemVersion out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.version = *v;
    }
    return out;
}

void Serializer<ContentIdentity>::serialize(BinaryWriter &stream, const ContentIdentity &value)
{
    stream.write(value.identity);
}

auto Serializer<ContentIdentity>::deserialize(BinaryReader &stream) -> std::expected<ContentIdentity, std::error_code>
{
    ContentIdentity out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.identity = *v;
    }
    return out;
}

void Serializer<base::PackIdVersion>::serialize(BinaryWriter &stream, const base::PackIdVersion &value)
{
    stream.write(value.id);
    Serializer<SemVersion>::serialize(stream, value.version);
}

auto Serializer<base::PackIdVersion>::deserialize(BinaryReader &stream) -> std::expected<base::PackIdVersion, std::error_code>
{
    base::PackIdVersion out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.id = *v;
    }
    {
        auto v = Serializer<SemVersion>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.version = *v;
    }
    return out;
}

void Serializer<v766::PackIdVersion>::serialize(BinaryWriter &stream, const v766::PackIdVersion &value)
{
    Serializer<UUID>::serialize(stream, value.id);
    Serializer<SemVersion>::serialize(stream, value.version);
}

auto Serializer<v766::PackIdVersion>::deserialize(BinaryReader &stream) -> std::expected<v766::PackIdVersion, std::error_code>
{
    v766::PackIdVersion out;
    {
        auto v = Serializer<UUID>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.id = *v;
    }
    {
        auto v = Serializer<SemVersion>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.version = *v;
    }
    return out;
}

void Serializer<base::PackInfoData>::serialize(BinaryWriter &stream, const base::PackInfoData &value)
{
    Serializer<base::PackIdVersion>::serialize(stream, value.pack_id_version);
    stream.write<std::uint64_t>(value.pack_size);
    stream.write(value.content_key);
    stream.write(value.subpack_name);
    Serializer<ContentIdentity>::serialize(stream, value.content_identity);
    stream.write<bool>(value.has_scripts);
    stream.write<bool>(value.is_addon_pack);
    stream.write<bool>(value.is_ray_tracing_capable);
}

auto Serializer<base::PackInfoData>::deserialize(BinaryReader &stream) -> std::expected<base::PackInfoData, std::error_code>
{
    base::PackInfoData out;
    {
        auto v = Serializer<base::PackIdVersion>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pack_id_version = *v;
    }
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.pack_size = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.content_key = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.subpack_name = *v;
    }
    {
        auto v = Serializer<ContentIdentity>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.content_identity = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_scripts = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_addon_pack = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_ray_tracing_capable = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v748::PackInfoData>::serialize(BinaryWriter &stream, const v748::PackInfoData &value)
{
    Serializer<base::PackIdVersion>::serialize(stream, value.pack_id_version);
    stream.write<std::uint64_t>(value.pack_size);
    stream.write(value.content_key);
    stream.write(value.subpack_name);
    Serializer<ContentIdentity>::serialize(stream, value.content_identity);
    stream.write<bool>(value.has_scripts);
    stream.write<bool>(value.is_addon_pack);
    stream.write<bool>(value.is_ray_tracing_capable);
    stream.write(value.cdn_url);
}

auto Serializer<v748::PackInfoData>::deserialize(BinaryReader &stream) -> std::expected<v748::PackInfoData, std::error_code>
{
    v748::PackInfoData out;
    {
        auto v = Serializer<base::PackIdVersion>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pack_id_version = *v;
    }
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.pack_size = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.content_key = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.subpack_name = *v;
    }
    {
        auto v = Serializer<ContentIdentity>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.content_identity = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_scripts = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_addon_pack = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_ray_tracing_capable = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.cdn_url = *v;
    }
    return out;
}

void Serializer<v766::PackInfoData>::serialize(BinaryWriter &stream, const v766::PackInfoData &value)
{
    Serializer<v766::PackIdVersion>::serialize(stream, value.pack_id_version);
    stream.write<std::uint64_t>(value.pack_size);
    stream.write(value.content_key);
    stream.write(value.subpack_name);
    Serializer<ContentIdentity>::serialize(stream, value.content_identity);
    stream.write<bool>(value.has_scripts);
    stream.write<bool>(value.is_addon_pack);
    stream.write<bool>(value.is_ray_tracing_capable);
    stream.write(value.cdn_url);
}

auto Serializer<v766::PackInfoData>::deserialize(BinaryReader &stream) -> std::expected<v766::PackInfoData, std::error_code>
{
    v766::PackInfoData out;
    {
        auto v = Serializer<v766::PackIdVersion>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pack_id_version = *v;
    }
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.pack_size = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.content_key = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.subpack_name = *v;
    }
    {
        auto v = Serializer<ContentIdentity>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.content_identity = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_scripts = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_addon_pack = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_ray_tracing_capable = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.cdn_url = *v;
    }
    return out;
}

void Serializer<base::PackUrl>::serialize(BinaryWriter &stream, const base::PackUrl &value)
{
    stream.write(value.pack_id_and_version);
    stream.write(value.url);
}

auto Serializer<base::PackUrl>::deserialize(BinaryReader &stream) -> std::expected<base::PackUrl, std::error_code>
{
    base::PackUrl out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.pack_id_and_version = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.url = *v;
    }
    return out;
}

void Serializer<base::ResourcePacksInfoPacket>::serialize(BinaryWriter &stream, const base::ResourcePacksInfoPacket &value)
{
    stream.write<bool>(value.resource_pack_required);
    stream.write<bool>(value.has_addon_packs);
    stream.write<bool>(value.has_scripts);
    stream.write<std::uint16_t>(value.resource_packs.size());
    for (const auto &e0 : value.resource_packs) {
        Serializer<base::PackInfoData>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.pack_urls.size());
    for (const auto &e0 : value.pack_urls) {
        Serializer<base::PackUrl>::serialize(stream, e0);
    }
}

auto Serializer<base::ResourcePacksInfoPacket>::deserialize(BinaryReader &stream) -> std::expected<base::ResourcePacksInfoPacket, std::error_code>
{
    base::ResourcePacksInfoPacket out;
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.resource_pack_required = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_addon_packs = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_scripts = static_cast<bool>(*v);
    }
    {
        auto len0 = stream.read<std::uint16_t>();
        if (!len0) return std::unexpected(len0.error());
        out.resource_packs.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.resource_packs.emplace_back();
            auto v = Serializer<base::PackInfoData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.resource_packs.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.pack_urls.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.pack_urls.emplace_back();
            auto v = Serializer<base::PackUrl>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.pack_urls.back() = *v;
        }
    }
    return out;
}

void Serializer<v748::ResourcePacksInfoPacket>::serialize(BinaryWriter &stream, const v748::ResourcePacksInfoPacket &value)
{
    stream.write<bool>(value.resource_pack_required);
    stream.write<bool>(value.has_addon_packs);
    stream.write<bool>(value.has_scripts);
    stream.write<std::uint16_t>(value.resource_packs.size());
    for (const auto &e0 : value.resource_packs) {
        Serializer<v748::PackInfoData>::serialize(stream, e0);
    }
}

auto Serializer<v748::ResourcePacksInfoPacket>::deserialize(BinaryReader &stream) -> std::expected<v748::ResourcePacksInfoPacket, std::error_code>
{
    v748::ResourcePacksInfoPacket out;
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.resource_pack_required = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_addon_packs = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_scripts = static_cast<bool>(*v);
    }
    {
        auto len0 = stream.read<std::uint16_t>();
        if (!len0) return std::unexpected(len0.error());
        out.resource_packs.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.resource_packs.emplace_back();
            auto v = Serializer<v748::PackInfoData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.resource_packs.back() = *v;
        }
    }
    return out;
}

void Serializer<v766::ResourcePacksInfoPacket>::serialize(BinaryWriter &stream, const v766::ResourcePacksInfoPacket &value)
{
    stream.write<bool>(value.resource_pack_required);
    stream.write<bool>(value.has_addon_packs);
    stream.write<bool>(value.has_scripts);
    Serializer<v766::PackIdVersion>::serialize(stream, value.world_template_id_and_version);
    stream.write<std::uint16_t>(value.resource_packs.size());
    for (const auto &e0 : value.resource_packs) {
        Serializer<v766::PackInfoData>::serialize(stream, e0);
    }
}

auto Serializer<v766::ResourcePacksInfoPacket>::deserialize(BinaryReader &stream) -> std::expected<v766::ResourcePacksInfoPacket, std::error_code>
{
    v766::ResourcePacksInfoPacket out;
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.resource_pack_required = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_addon_packs = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_scripts = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<v766::PackIdVersion>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.world_template_id_and_version = *v;
    }
    {
        auto len0 = stream.read<std::uint16_t>();
        if (!len0) return std::unexpected(len0.error());
        out.resource_packs.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.resource_packs.emplace_back();
            auto v = Serializer<v766::PackInfoData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.resource_packs.back() = *v;
        }
    }
    return out;
}

void Serializer<v818::ResourcePacksInfoPacket>::serialize(BinaryWriter &stream, const v818::ResourcePacksInfoPacket &value)
{
    stream.write<bool>(value.resource_pack_required);
    stream.write<bool>(value.has_addon_packs);
    stream.write<bool>(value.has_scripts);
    stream.write<bool>(value.force_disable_vibrant_visuals);
    Serializer<v766::PackIdVersion>::serialize(stream, value.world_template_id_and_version);
    stream.write<std::uint16_t>(value.resource_packs.size());
    for (const auto &e0 : value.resource_packs) {
        Serializer<v766::PackInfoData>::serialize(stream, e0);
    }
}

auto Serializer<v818::ResourcePacksInfoPacket>::deserialize(BinaryReader &stream) -> std::expected<v818::ResourcePacksInfoPacket, std::error_code>
{
    v818::ResourcePacksInfoPacket out;
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.resource_pack_required = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_addon_packs = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_scripts = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.force_disable_vibrant_visuals = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<v766::PackIdVersion>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.world_template_id_and_version = *v;
    }
    {
        auto len0 = stream.read<std::uint16_t>();
        if (!len0) return std::unexpected(len0.error());
        out.resource_packs.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.resource_packs.emplace_back();
            auto v = Serializer<v766::PackInfoData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.resource_packs.back() = *v;
        }
    }
    return out;
}

void Serializer<v2168::ResourcePacksInfoPacket>::serialize(BinaryWriter &stream, const v2168::ResourcePacksInfoPacket &value)
{
    stream.write<bool>(value.resource_pack_required);
    stream.write<bool>(value.has_addon_packs);
    stream.write<bool>(value.has_scripts);
    stream.write<bool>(value.force_disable_vibrant_visuals);
    Serializer<v766::PackIdVersion>::serialize(stream, value.world_template_id_and_version);
    stream.writeVarInt<std::uint32_t>(value.resource_packs.size());
    for (const auto &e0 : value.resource_packs) {
        Serializer<v766::PackInfoData>::serialize(stream, e0);
    }
}

auto Serializer<v2168::ResourcePacksInfoPacket>::deserialize(BinaryReader &stream) -> std::expected<v2168::ResourcePacksInfoPacket, std::error_code>
{
    v2168::ResourcePacksInfoPacket out;
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.resource_pack_required = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_addon_packs = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.has_scripts = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.force_disable_vibrant_visuals = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<v766::PackIdVersion>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.world_template_id_and_version = *v;
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.resource_packs.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.resource_packs.emplace_back();
            auto v = Serializer<v766::PackInfoData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.resource_packs.back() = *v;
        }
    }
    return out;
}

void Serializer<base::ResourcePackClientResponsePacket::Cancel>::serialize(BinaryWriter &stream, const base::ResourcePackClientResponsePacket::Cancel &value)
{
    stream.write("cancel");
}

auto Serializer<base::ResourcePackClientResponsePacket::Cancel>::deserialize(BinaryReader &stream) -> std::expected<base::ResourcePackClientResponsePacket::Cancel, std::error_code>
{
    base::ResourcePackClientResponsePacket::Cancel out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        if (*v != "cancel") {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    return out;
}

void Serializer<base::ResourcePackClientResponsePacket::Downloading>::serialize(BinaryWriter &stream, const base::ResourcePackClientResponsePacket::Downloading &value)
{
    stream.write("downloading");
    stream.writeVarInt<std::uint32_t>(value.downloading_packs.size());
    for (const auto &e0 : value.downloading_packs) {
        stream.write(e0);
    }
}

auto Serializer<base::ResourcePackClientResponsePacket::Downloading>::deserialize(BinaryReader &stream) -> std::expected<base::ResourcePackClientResponsePacket::Downloading, std::error_code>
{
    base::ResourcePackClientResponsePacket::Downloading out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        if (*v != "downloading") {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.downloading_packs.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.downloading_packs.emplace_back();
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.downloading_packs.back() = *v;
        }
    }
    return out;
}

void Serializer<base::ResourcePackClientResponsePacket::DownloadingFinished>::serialize(BinaryWriter &stream, const base::ResourcePackClientResponsePacket::DownloadingFinished &value)
{
    stream.write("downloadingfinished");
}

auto Serializer<base::ResourcePackClientResponsePacket::DownloadingFinished>::deserialize(BinaryReader &stream) -> std::expected<base::ResourcePackClientResponsePacket::DownloadingFinished, std::error_code>
{
    base::ResourcePackClientResponsePacket::DownloadingFinished out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        if (*v != "downloadingfinished") {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    return out;
}

void Serializer<base::ResourcePackClientResponsePacket::ResourcePackStackFinished>::serialize(BinaryWriter &stream, const base::ResourcePackClientResponsePacket::ResourcePackStackFinished &value)
{
    stream.write("resourcepackstackfinished");
}

auto Serializer<base::ResourcePackClientResponsePacket::ResourcePackStackFinished>::deserialize(BinaryReader &stream) -> std::expected<base::ResourcePackClientResponsePacket::ResourcePackStackFinished, std::error_code>
{
    base::ResourcePackClientResponsePacket::ResourcePackStackFinished out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        if (*v != "resourcepackstackfinished") {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    return out;
}

void Serializer<base::ResourcePackClientResponsePacket>::serialize(BinaryWriter &stream, const base::ResourcePackClientResponsePacket &value)
{
    stream.write<std::int8_t>(value.response);
    stream.write<std::uint16_t>(value.downloading_packs.size());
    for (const auto &e0 : value.downloading_packs) {
        stream.write(e0);
    }
}

auto Serializer<base::ResourcePackClientResponsePacket>::deserialize(BinaryReader &stream) -> std::expected<base::ResourcePackClientResponsePacket, std::error_code>
{
    base::ResourcePackClientResponsePacket out;
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.response = static_cast<ResourcePackResponse>(*v);
    }
    {
        auto len0 = stream.read<std::uint16_t>();
        if (!len0) return std::unexpected(len0.error());
        out.downloading_packs.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.downloading_packs.emplace_back();
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.downloading_packs.back() = *v;
        }
    }
    return out;
}

void Serializer<v2168::ResourcePackClientResponsePacket>::serialize(BinaryWriter &stream, const v2168::ResourcePackClientResponsePacket &value)
{
    stream.writeVarInt<std::uint32_t>((value.response).index());
    switch ((value.response).index()) {
        case 0: {
            Serializer<v2168::ResourcePackClientResponsePacket::Cancel>::serialize(stream, std::get<0>(value.response));
            break;
        }
        case 1: {
            Serializer<v2168::ResourcePackClientResponsePacket::Downloading>::serialize(stream, std::get<1>(value.response));
            break;
        }
        case 2: {
            Serializer<v2168::ResourcePackClientResponsePacket::DownloadingFinished>::serialize(stream, std::get<2>(value.response));
            break;
        }
        case 3: {
            Serializer<v2168::ResourcePackClientResponsePacket::ResourcePackStackFinished>::serialize(stream, std::get<3>(value.response));
            break;
        }
    }
}

auto Serializer<v2168::ResourcePackClientResponsePacket>::deserialize(BinaryReader &stream) -> std::expected<v2168::ResourcePackClientResponsePacket, std::error_code>
{
    v2168::ResourcePackClientResponsePacket out;
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v2168::ResourcePackClientResponsePacket::Cancel, v2168::ResourcePackClientResponsePacket::Downloading, v2168::ResourcePackClientResponsePacket::DownloadingFinished, v2168::ResourcePackClientResponsePacket::ResourcePackStackFinished> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v2168::ResourcePackClientResponsePacket::Cancel, v2168::ResourcePackClientResponsePacket::Downloading, v2168::ResourcePackClientResponsePacket::DownloadingFinished, v2168::ResourcePackClientResponsePacket::ResourcePackStackFinished>> alt0{};
                {
                    auto v = Serializer<v2168::ResourcePackClientResponsePacket::Cancel>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v2168::ResourcePackClientResponsePacket::Cancel, v2168::ResourcePackClientResponsePacket::Downloading, v2168::ResourcePackClientResponsePacket::DownloadingFinished, v2168::ResourcePackClientResponsePacket::ResourcePackStackFinished>> alt0{};
                {
                    auto v = Serializer<v2168::ResourcePackClientResponsePacket::Downloading>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<v2168::ResourcePackClientResponsePacket::Cancel, v2168::ResourcePackClientResponsePacket::Downloading, v2168::ResourcePackClientResponsePacket::DownloadingFinished, v2168::ResourcePackClientResponsePacket::ResourcePackStackFinished>> alt0{};
                {
                    auto v = Serializer<v2168::ResourcePackClientResponsePacket::DownloadingFinished>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<v2168::ResourcePackClientResponsePacket::Cancel, v2168::ResourcePackClientResponsePacket::Downloading, v2168::ResourcePackClientResponsePacket::DownloadingFinished, v2168::ResourcePackClientResponsePacket::ResourcePackStackFinished>> alt0{};
                {
                    auto v = Serializer<v2168::ResourcePackClientResponsePacket::ResourcePackStackFinished>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.response = var0;
    }
    return out;
}

void Serializer<v844::ServerboundPackSettingChangePacket>::serialize(BinaryWriter &stream, const v844::ServerboundPackSettingChangePacket &value)
{
    Serializer<UUID>::serialize(stream, value.pack_id);
    stream.write(value.setting_name);
    stream.writeVarInt<std::uint32_t>((value.setting_value).index());
    switch ((value.setting_value).index()) {
        case 0: {
            stream.write<float>(std::get<0>(value.setting_value));
            break;
        }
        case 1: {
            stream.write<bool>(std::get<1>(value.setting_value));
            break;
        }
        case 2: {
            stream.write(std::get<2>(value.setting_value));
            break;
        }
    }
}

auto Serializer<v844::ServerboundPackSettingChangePacket>::deserialize(BinaryReader &stream) -> std::expected<v844::ServerboundPackSettingChangePacket, std::error_code>
{
    v844::ServerboundPackSettingChangePacket out;
    {
        auto v = Serializer<UUID>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pack_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.setting_name = *v;
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<float, bool, std::string> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<float, bool, std::string>> alt0{};
                {
                    auto v = stream.read<float>();
                    if (!v) return std::unexpected(v.error());
                    alt0 = static_cast<float>(*v);
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<float, bool, std::string>> alt0{};
                {
                    auto v = stream.read<bool>();
                    if (!v) return std::unexpected(v.error());
                    alt0 = static_cast<bool>(*v);
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<float, bool, std::string>> alt0{};
                {
                    auto v = stream.read<std::string>();
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
        out.setting_value = var0;
    }
    return out;
}

void Serializer<v2193::ServerboundPackSettingChangePacket>::serialize(BinaryWriter &stream, const v2193::ServerboundPackSettingChangePacket &value)
{
    Serializer<UUID>::serialize(stream, value.pack_id);
    stream.write(value.setting_name);
    stream.writeVarInt<std::uint32_t>((value.setting_value).index());
    switch ((value.setting_value).index()) {
        case 0: {
            stream.write<float>(std::get<0>(value.setting_value));
            break;
        }
        case 1: {
            stream.write<bool>(std::get<1>(value.setting_value));
            break;
        }
        case 2: {
            stream.write(std::get<2>(value.setting_value));
            break;
        }
        case 3: {
            stream.writeVarInt<std::uint32_t>(std::get<3>(value.setting_value).size());
            for (const auto &e1 : std::get<3>(value.setting_value)) {
                stream.write(e1);
            }
            break;
        }
    }
}

auto Serializer<v2193::ServerboundPackSettingChangePacket>::deserialize(BinaryReader &stream) -> std::expected<v2193::ServerboundPackSettingChangePacket, std::error_code>
{
    v2193::ServerboundPackSettingChangePacket out;
    {
        auto v = Serializer<UUID>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pack_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.setting_name = *v;
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<float, bool, std::string, std::vector<std::string>> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<float, bool, std::string, std::vector<std::string>>> alt0{};
                {
                    auto v = stream.read<float>();
                    if (!v) return std::unexpected(v.error());
                    alt0 = static_cast<float>(*v);
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<float, bool, std::string, std::vector<std::string>>> alt0{};
                {
                    auto v = stream.read<bool>();
                    if (!v) return std::unexpected(v.error());
                    alt0 = static_cast<bool>(*v);
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<float, bool, std::string, std::vector<std::string>>> alt0{};
                {
                    auto v = stream.read<std::string>();
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<float, bool, std::string, std::vector<std::string>>> alt0{};
                {
                    auto len1 = stream.readVarInt<std::uint32_t>();
                    if (!len1) return std::unexpected(len1.error());
                    alt0.clear();
                    for (auto rep1 = *len1; rep1 > 0; --rep1) {
                        alt0.emplace_back();
                        auto v = stream.read<std::string>();
                        if (!v) return std::unexpected(v.error());
                        alt0.back() = *v;
                    }
                }
                var0.emplace<3>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.setting_value = var0;
    }
    return out;
}

void Serializer<PackInstanceId>::serialize(BinaryWriter &stream, const PackInstanceId &value)
{
    stream.write(value.pack_id);
    stream.write(value.version);
    stream.write(value.subpack_name);
}

auto Serializer<PackInstanceId>::deserialize(BinaryReader &stream) -> std::expected<PackInstanceId, std::error_code>
{
    PackInstanceId out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.pack_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.version = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.subpack_name = *v;
    }
    return out;
}

void Serializer<base::ResourcePackStackPacket>::serialize(BinaryWriter &stream, const base::ResourcePackStackPacket &value)
{
    stream.write<bool>(value.texture_pack_required);
    stream.writeVarInt<std::uint32_t>(value.add_on_ids_and_versions.size());
    for (const auto &e0 : value.add_on_ids_and_versions) {
        Serializer<PackInstanceId>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.texture_pack_ids_and_versions.size());
    for (const auto &e0 : value.texture_pack_ids_and_versions) {
        Serializer<PackInstanceId>::serialize(stream, e0);
    }
    stream.write(value.base_game_version);
    Serializer<Experiments>::serialize(stream, value.experiments);
    stream.write<bool>(value.include_editor_packs);
}

auto Serializer<base::ResourcePackStackPacket>::deserialize(BinaryReader &stream) -> std::expected<base::ResourcePackStackPacket, std::error_code>
{
    base::ResourcePackStackPacket out;
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.texture_pack_required = static_cast<bool>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.add_on_ids_and_versions.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.add_on_ids_and_versions.emplace_back();
            auto v = Serializer<PackInstanceId>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.add_on_ids_and_versions.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.texture_pack_ids_and_versions.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.texture_pack_ids_and_versions.emplace_back();
            auto v = Serializer<PackInstanceId>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.texture_pack_ids_and_versions.back() = *v;
        }
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.base_game_version = *v;
    }
    {
        auto v = Serializer<Experiments>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.experiments = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.include_editor_packs = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v898::ResourcePackStackPacket>::serialize(BinaryWriter &stream, const v898::ResourcePackStackPacket &value)
{
    stream.write<bool>(value.texture_pack_required);
    stream.writeVarInt<std::uint32_t>(value.texture_pack_ids_and_versions.size());
    for (const auto &e0 : value.texture_pack_ids_and_versions) {
        Serializer<PackInstanceId>::serialize(stream, e0);
    }
    stream.write(value.base_game_version);
    Serializer<Experiments>::serialize(stream, value.experiments);
    stream.write<bool>(value.include_editor_packs);
}

auto Serializer<v898::ResourcePackStackPacket>::deserialize(BinaryReader &stream) -> std::expected<v898::ResourcePackStackPacket, std::error_code>
{
    v898::ResourcePackStackPacket out;
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.texture_pack_required = static_cast<bool>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.texture_pack_ids_and_versions.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.texture_pack_ids_and_versions.emplace_back();
            auto v = Serializer<PackInstanceId>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.texture_pack_ids_and_versions.back() = *v;
        }
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.base_game_version = *v;
    }
    {
        auto v = Serializer<Experiments>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.experiments = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.include_editor_packs = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<ResourcePackDataInfoPacket>::serialize(BinaryWriter &stream, const ResourcePackDataInfoPacket &value)
{
    stream.write(value.resource_name);
    stream.write<std::uint32_t>(value.chunk_size);
    stream.write<std::uint32_t>(value.nb_chunks);
    stream.write<std::uint64_t>(value.file_size);
    stream.write(value.file_hash);
    stream.write<bool>(value.is_premium);
    stream.write<std::int8_t>(value.pack_type);
}

auto Serializer<ResourcePackDataInfoPacket>::deserialize(BinaryReader &stream) -> std::expected<ResourcePackDataInfoPacket, std::error_code>
{
    ResourcePackDataInfoPacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.resource_name = *v;
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.chunk_size = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.nb_chunks = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.file_size = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.file_hash = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_premium = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.pack_type = static_cast<PackType>(*v);
    }
    return out;
}

void Serializer<ResourcePackChunkDataPacket>::serialize(BinaryWriter &stream, const ResourcePackChunkDataPacket &value)
{
    stream.write(value.resource_name);
    stream.write<std::uint32_t>(value.chunk_id);
    stream.write<std::uint64_t>(value.byte_offset);
    stream.write(value.data);
}

auto Serializer<ResourcePackChunkDataPacket>::deserialize(BinaryReader &stream) -> std::expected<ResourcePackChunkDataPacket, std::error_code>
{
    ResourcePackChunkDataPacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.resource_name = *v;
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.chunk_id = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.byte_offset = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.data = *v;
    }
    return out;
}

void Serializer<base::ResourcePackChunkRequestPacket>::serialize(BinaryWriter &stream, const base::ResourcePackChunkRequestPacket &value)
{
    stream.write(value.resource_name);
    stream.write<std::uint32_t>(value.chunk);
}

auto Serializer<base::ResourcePackChunkRequestPacket>::deserialize(BinaryReader &stream) -> std::expected<base::ResourcePackChunkRequestPacket, std::error_code>
{
    base::ResourcePackChunkRequestPacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.resource_name = *v;
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.chunk = static_cast<std::uint32_t>(*v);
    }
    return out;
}

void Serializer<v2168::ResourcePackChunkRequestPacket>::serialize(BinaryWriter &stream, const v2168::ResourcePackChunkRequestPacket &value)
{
    stream.write(value.resource_name);
    stream.write<std::int32_t>(value.chunk);
}

auto Serializer<v2168::ResourcePackChunkRequestPacket>::deserialize(BinaryReader &stream) -> std::expected<v2168::ResourcePackChunkRequestPacket, std::error_code>
{
    v2168::ResourcePackChunkRequestPacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.resource_name = *v;
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.chunk = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<v944::ResourcePacksReadyForValidationPacket>::serialize(BinaryWriter &stream, const v944::ResourcePacksReadyForValidationPacket &value)
{
}

auto Serializer<v944::ResourcePacksReadyForValidationPacket>::deserialize(BinaryReader &stream) -> std::expected<v944::ResourcePacksReadyForValidationPacket, std::error_code>
{
    v944::ResourcePacksReadyForValidationPacket out;
    return out;
}

}  // namespace bedrock::protocol
