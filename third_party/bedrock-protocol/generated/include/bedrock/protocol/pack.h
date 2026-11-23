#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <expected>
#include <string>
#include <string_view>
#include <system_error>
#include <variant>
#include <vector>

#include <bedrock/protocol/detail/reflect.hpp>
#include <bedrock/protocol/enum.hpp>
#include <bedrock/protocol/packet.hpp>
#include <bedrock/protocol/serializer.hpp>
#include <bedrock/protocol/stream.hpp>
#include <bedrock/protocol/uuid.hpp>

#include <bedrock/protocol/game.h>

namespace bedrock::protocol {

struct SemVersion {
    std::string version{};
};

struct ContentIdentity {
    std::string identity{};
};

enum class ResourcePackResponse : std::int8_t {
    Cancel = 1,
    Downloading = 2,
    DownloadingFinished = 3,
    ResourcePackStackFinished = 4,
};

struct PackInstanceId {
    std::string pack_id{};
    std::string version{};
    std::string subpack_name{};
};

enum class PackType : std::int8_t {
    Invalid = 0,
    Addon = 1,
    Cached = 2,
    CopyProtected = 3,
    Behavior = 4,
    PersonaPiece = 5,
    Resources = 6,
    Skins = 7,
    WorldTemplate = 8,
    Count = 9,
};

struct ResourcePackDataInfoPacket {
    static constexpr int Id = 82;
    std::string resource_name{};
    std::uint32_t chunk_size{};
    std::uint32_t nb_chunks{};
    std::uint64_t file_size{};
    std::string file_hash{};
    bool is_premium{};
    PackType pack_type{};
};

struct ResourcePackChunkDataPacket {
    static constexpr int Id = 83;
    std::string resource_name{};
    std::uint32_t chunk_id{};
    std::uint64_t byte_offset{};
    std::string data{};
};

namespace base {

struct PackIdVersion {
    std::string id{};
    SemVersion version{};
};

struct PackInfoData {
    base::PackIdVersion pack_id_version{};
    std::uint64_t pack_size{};
    std::string content_key{};
    std::string subpack_name{};
    ContentIdentity content_identity{};
    bool has_scripts{};
    bool is_addon_pack{};
    bool is_ray_tracing_capable{};
};

struct PackUrl {
    std::string pack_id_and_version{};
    std::string url{};
};

struct ResourcePacksInfoPacket {
    static constexpr int Id = 6;
    bool resource_pack_required{};
    bool has_addon_packs{};
    bool has_scripts{};
    std::vector<base::PackInfoData> resource_packs{};
    std::vector<base::PackUrl> pack_urls{};
};

namespace ResourcePackClientResponsePacket_nested {

struct Cancel {
};

struct Downloading {
    std::vector<std::string> downloading_packs{};
};

struct DownloadingFinished {
};

struct ResourcePackStackFinished {
};

}  // namespace ResourcePackClientResponsePacket_nested

struct ResourcePackClientResponsePacket {
    using Cancel = ResourcePackClientResponsePacket_nested::Cancel;
    using Downloading = ResourcePackClientResponsePacket_nested::Downloading;
    using DownloadingFinished = ResourcePackClientResponsePacket_nested::DownloadingFinished;
    using ResourcePackStackFinished = ResourcePackClientResponsePacket_nested::ResourcePackStackFinished;

    static constexpr int Id = 8;
    ResourcePackResponse response{};
    std::vector<std::string> downloading_packs{};
};

struct ResourcePackStackPacket {
    static constexpr int Id = 7;
    bool texture_pack_required{};
    std::vector<PackInstanceId> add_on_ids_and_versions{};
    std::vector<PackInstanceId> texture_pack_ids_and_versions{};
    std::string base_game_version{};
    Experiments experiments{};
    bool include_editor_packs{};
};

struct ResourcePackChunkRequestPacket {
    static constexpr int Id = 84;
    std::string resource_name{};
    std::uint32_t chunk{};
};

}  // namespace base

namespace v748 {

using PackIdVersion = base::PackIdVersion;

struct PackInfoData {
    base::PackIdVersion pack_id_version{};
    std::uint64_t pack_size{};
    std::string content_key{};
    std::string subpack_name{};
    ContentIdentity content_identity{};
    bool has_scripts{};
    bool is_addon_pack{};
    bool is_ray_tracing_capable{};
    std::string cdn_url{};
};

struct ResourcePacksInfoPacket {
    static constexpr int Id = 6;
    bool resource_pack_required{};
    bool has_addon_packs{};
    bool has_scripts{};
    std::vector<v748::PackInfoData> resource_packs{};
};

using ResourcePackClientResponsePacket = base::ResourcePackClientResponsePacket;

using ResourcePackStackPacket = base::ResourcePackStackPacket;

using ResourcePackChunkRequestPacket = base::ResourcePackChunkRequestPacket;

}  // namespace v748

namespace v766 {

struct PackIdVersion {
    UUID id{};
    SemVersion version{};
};

struct PackInfoData {
    v766::PackIdVersion pack_id_version{};
    std::uint64_t pack_size{};
    std::string content_key{};
    std::string subpack_name{};
    ContentIdentity content_identity{};
    bool has_scripts{};
    bool is_addon_pack{};
    bool is_ray_tracing_capable{};
    std::string cdn_url{};
};

struct ResourcePacksInfoPacket {
    static constexpr int Id = 6;
    bool resource_pack_required{};
    bool has_addon_packs{};
    bool has_scripts{};
    v766::PackIdVersion world_template_id_and_version{};
    std::vector<v766::PackInfoData> resource_packs{};
};

using ResourcePackClientResponsePacket = base::ResourcePackClientResponsePacket;

using ResourcePackStackPacket = base::ResourcePackStackPacket;

using ResourcePackChunkRequestPacket = base::ResourcePackChunkRequestPacket;

}  // namespace v766

namespace v776 {

using PackIdVersion = v766::PackIdVersion;

using PackInfoData = v766::PackInfoData;

using ResourcePacksInfoPacket = v766::ResourcePacksInfoPacket;

using ResourcePackClientResponsePacket = base::ResourcePackClientResponsePacket;

using ResourcePackStackPacket = base::ResourcePackStackPacket;

using ResourcePackChunkRequestPacket = base::ResourcePackChunkRequestPacket;

}  // namespace v776

namespace v786 {

using PackIdVersion = v766::PackIdVersion;

using PackInfoData = v766::PackInfoData;

using ResourcePacksInfoPacket = v766::ResourcePacksInfoPacket;

using ResourcePackClientResponsePacket = base::ResourcePackClientResponsePacket;

using ResourcePackStackPacket = base::ResourcePackStackPacket;

using ResourcePackChunkRequestPacket = base::ResourcePackChunkRequestPacket;

}  // namespace v786

namespace v800 {

using PackIdVersion = v766::PackIdVersion;

using PackInfoData = v766::PackInfoData;

using ResourcePacksInfoPacket = v766::ResourcePacksInfoPacket;

using ResourcePackClientResponsePacket = base::ResourcePackClientResponsePacket;

using ResourcePackStackPacket = base::ResourcePackStackPacket;

using ResourcePackChunkRequestPacket = base::ResourcePackChunkRequestPacket;

}  // namespace v800

namespace v818 {

using PackIdVersion = v766::PackIdVersion;

using PackInfoData = v766::PackInfoData;

struct ResourcePacksInfoPacket {
    static constexpr int Id = 6;
    bool resource_pack_required{};
    bool has_addon_packs{};
    bool has_scripts{};
    bool force_disable_vibrant_visuals{};
    v766::PackIdVersion world_template_id_and_version{};
    std::vector<v766::PackInfoData> resource_packs{};
};

using ResourcePackClientResponsePacket = base::ResourcePackClientResponsePacket;

using ResourcePackStackPacket = base::ResourcePackStackPacket;

using ResourcePackChunkRequestPacket = base::ResourcePackChunkRequestPacket;

}  // namespace v818

namespace v827 {

using PackIdVersion = v766::PackIdVersion;

using PackInfoData = v766::PackInfoData;

using ResourcePacksInfoPacket = v818::ResourcePacksInfoPacket;

using ResourcePackClientResponsePacket = base::ResourcePackClientResponsePacket;

using ResourcePackStackPacket = base::ResourcePackStackPacket;

using ResourcePackChunkRequestPacket = base::ResourcePackChunkRequestPacket;

}  // namespace v827

namespace v844 {

using PackIdVersion = v766::PackIdVersion;

using PackInfoData = v766::PackInfoData;

using ResourcePacksInfoPacket = v818::ResourcePacksInfoPacket;

using ResourcePackClientResponsePacket = base::ResourcePackClientResponsePacket;

struct ServerboundPackSettingChangePacket {
    static constexpr int Id = 329;
    UUID pack_id{};
    std::string setting_name{};
    std::variant<float, bool, std::string> setting_value{};
};

using ResourcePackStackPacket = base::ResourcePackStackPacket;

using ResourcePackChunkRequestPacket = base::ResourcePackChunkRequestPacket;

}  // namespace v844

namespace v859 {

using PackIdVersion = v766::PackIdVersion;

using PackInfoData = v766::PackInfoData;

using ResourcePacksInfoPacket = v818::ResourcePacksInfoPacket;

using ResourcePackClientResponsePacket = base::ResourcePackClientResponsePacket;

using ServerboundPackSettingChangePacket = v844::ServerboundPackSettingChangePacket;

using ResourcePackStackPacket = base::ResourcePackStackPacket;

using ResourcePackChunkRequestPacket = base::ResourcePackChunkRequestPacket;

}  // namespace v859

namespace v898 {

using PackIdVersion = v766::PackIdVersion;

using PackInfoData = v766::PackInfoData;

using ResourcePacksInfoPacket = v818::ResourcePacksInfoPacket;

using ResourcePackClientResponsePacket = base::ResourcePackClientResponsePacket;

using ServerboundPackSettingChangePacket = v844::ServerboundPackSettingChangePacket;

struct ResourcePackStackPacket {
    static constexpr int Id = 7;
    bool texture_pack_required{};
    std::vector<PackInstanceId> texture_pack_ids_and_versions{};
    std::string base_game_version{};
    Experiments experiments{};
    bool include_editor_packs{};
};

using ResourcePackChunkRequestPacket = base::ResourcePackChunkRequestPacket;

}  // namespace v898

namespace v924 {

using PackIdVersion = v766::PackIdVersion;

using PackInfoData = v766::PackInfoData;

using ResourcePacksInfoPacket = v818::ResourcePacksInfoPacket;

using ResourcePackClientResponsePacket = base::ResourcePackClientResponsePacket;

using ServerboundPackSettingChangePacket = v844::ServerboundPackSettingChangePacket;

using ResourcePackStackPacket = v898::ResourcePackStackPacket;

using ResourcePackChunkRequestPacket = base::ResourcePackChunkRequestPacket;

}  // namespace v924

namespace v944 {

using PackIdVersion = v766::PackIdVersion;

using PackInfoData = v766::PackInfoData;

using ResourcePacksInfoPacket = v818::ResourcePacksInfoPacket;

using ResourcePackClientResponsePacket = base::ResourcePackClientResponsePacket;

using ServerboundPackSettingChangePacket = v844::ServerboundPackSettingChangePacket;

using ResourcePackStackPacket = v898::ResourcePackStackPacket;

using ResourcePackChunkRequestPacket = base::ResourcePackChunkRequestPacket;

struct ResourcePacksReadyForValidationPacket {
    static constexpr int Id = 340;
};

}  // namespace v944

namespace v975 {

using PackIdVersion = v766::PackIdVersion;

using PackInfoData = v766::PackInfoData;

using ResourcePacksInfoPacket = v818::ResourcePacksInfoPacket;

using ResourcePackClientResponsePacket = base::ResourcePackClientResponsePacket;

using ServerboundPackSettingChangePacket = v844::ServerboundPackSettingChangePacket;

using ResourcePackStackPacket = v898::ResourcePackStackPacket;

using ResourcePackChunkRequestPacket = base::ResourcePackChunkRequestPacket;

using ResourcePacksReadyForValidationPacket = v944::ResourcePacksReadyForValidationPacket;

}  // namespace v975

namespace v1001 {

using PackIdVersion = v766::PackIdVersion;

using PackInfoData = v766::PackInfoData;

using ResourcePacksInfoPacket = v818::ResourcePacksInfoPacket;

using ResourcePackClientResponsePacket = base::ResourcePackClientResponsePacket;

using ServerboundPackSettingChangePacket = v844::ServerboundPackSettingChangePacket;

using ResourcePackStackPacket = v898::ResourcePackStackPacket;

using ResourcePackChunkRequestPacket = base::ResourcePackChunkRequestPacket;

using ResourcePacksReadyForValidationPacket = v944::ResourcePacksReadyForValidationPacket;

}  // namespace v1001

namespace v2168 {

using PackIdVersion = v766::PackIdVersion;

using PackInfoData = v766::PackInfoData;

struct ResourcePacksInfoPacket {
    static constexpr int Id = 6;
    bool resource_pack_required{};
    bool has_addon_packs{};
    bool has_scripts{};
    bool force_disable_vibrant_visuals{};
    v766::PackIdVersion world_template_id_and_version{};
    std::vector<v766::PackInfoData> resource_packs{};
};

namespace ResourcePackClientResponsePacket_nested {

using Cancel = base::ResourcePackClientResponsePacket::Cancel;
using Downloading = base::ResourcePackClientResponsePacket::Downloading;
using DownloadingFinished = base::ResourcePackClientResponsePacket::DownloadingFinished;
using ResourcePackStackFinished = base::ResourcePackClientResponsePacket::ResourcePackStackFinished;

}  // namespace ResourcePackClientResponsePacket_nested

struct ResourcePackClientResponsePacket {
    using Cancel = ResourcePackClientResponsePacket_nested::Cancel;
    using Downloading = ResourcePackClientResponsePacket_nested::Downloading;
    using DownloadingFinished = ResourcePackClientResponsePacket_nested::DownloadingFinished;
    using ResourcePackStackFinished = ResourcePackClientResponsePacket_nested::ResourcePackStackFinished;

    static constexpr int Id = 8;
    std::variant<v2168::ResourcePackClientResponsePacket::Cancel, v2168::ResourcePackClientResponsePacket::Downloading, v2168::ResourcePackClientResponsePacket::DownloadingFinished, v2168::ResourcePackClientResponsePacket::ResourcePackStackFinished> response{};
};

using ServerboundPackSettingChangePacket = v844::ServerboundPackSettingChangePacket;

using ResourcePackStackPacket = v898::ResourcePackStackPacket;

struct ResourcePackChunkRequestPacket {
    static constexpr int Id = 84;
    std::string resource_name{};
    std::int32_t chunk{};
};

using ResourcePacksReadyForValidationPacket = v944::ResourcePacksReadyForValidationPacket;

}  // namespace v2168

namespace v2193 {

using PackIdVersion = v766::PackIdVersion;

using PackInfoData = v766::PackInfoData;

using ResourcePacksInfoPacket = v2168::ResourcePacksInfoPacket;

using ResourcePackClientResponsePacket = v2168::ResourcePackClientResponsePacket;

struct ServerboundPackSettingChangePacket {
    static constexpr int Id = 329;
    UUID pack_id{};
    std::string setting_name{};
    std::variant<float, bool, std::string, std::vector<std::string>> setting_value{};
};

using ResourcePackStackPacket = v898::ResourcePackStackPacket;

using ResourcePackChunkRequestPacket = v2168::ResourcePackChunkRequestPacket;

using ResourcePacksReadyForValidationPacket = v944::ResourcePacksReadyForValidationPacket;

}  // namespace v2193

namespace v2225 {

using PackIdVersion = v766::PackIdVersion;

using PackInfoData = v766::PackInfoData;

using ResourcePacksInfoPacket = v2168::ResourcePacksInfoPacket;

using ResourcePackClientResponsePacket = v2168::ResourcePackClientResponsePacket;

using ServerboundPackSettingChangePacket = v2193::ServerboundPackSettingChangePacket;

using ResourcePackStackPacket = v898::ResourcePackStackPacket;

using ResourcePackChunkRequestPacket = v2168::ResourcePackChunkRequestPacket;

using ResourcePacksReadyForValidationPacket = v944::ResourcePacksReadyForValidationPacket;

}  // namespace v2225

namespace detail {

template <int V>
struct PackIdVersion_;

template <int V> requires (V < 766)
struct PackIdVersion_<V> { using type = base::PackIdVersion; };

template <int V> requires (V >= 766)
struct PackIdVersion_<V> { using type = v766::PackIdVersion; };

template <int V>
struct PackInfoData_;

template <int V> requires (V < 748)
struct PackInfoData_<V> { using type = base::PackInfoData; };

template <int V> requires (V >= 748 && V < 766)
struct PackInfoData_<V> { using type = v748::PackInfoData; };

template <int V> requires (V >= 766)
struct PackInfoData_<V> { using type = v766::PackInfoData; };

template <int V>
struct PackUrl_;

template <int V> requires (V < 748)
struct PackUrl_<V> { using type = base::PackUrl; };

template <int V>
struct ResourcePacksInfoPacket_;

template <int V> requires (V < 748)
struct ResourcePacksInfoPacket_<V> { using type = base::ResourcePacksInfoPacket; };

template <int V> requires (V >= 748 && V < 766)
struct ResourcePacksInfoPacket_<V> { using type = v748::ResourcePacksInfoPacket; };

template <int V> requires (V >= 766 && V < 818)
struct ResourcePacksInfoPacket_<V> { using type = v766::ResourcePacksInfoPacket; };

template <int V> requires (V >= 818 && V < 2168)
struct ResourcePacksInfoPacket_<V> { using type = v818::ResourcePacksInfoPacket; };

template <int V> requires (V >= 2168)
struct ResourcePacksInfoPacket_<V> { using type = v2168::ResourcePacksInfoPacket; };

template <int V>
struct ResourcePackClientResponsePacket_;

template <int V> requires (V < 2168)
struct ResourcePackClientResponsePacket_<V> { using type = base::ResourcePackClientResponsePacket; };

template <int V> requires (V >= 2168)
struct ResourcePackClientResponsePacket_<V> { using type = v2168::ResourcePackClientResponsePacket; };

template <int V>
struct ServerboundPackSettingChangePacket_;

template <int V> requires (V >= 844 && V < 2193)
struct ServerboundPackSettingChangePacket_<V> { using type = v844::ServerboundPackSettingChangePacket; };

template <int V> requires (V >= 2193)
struct ServerboundPackSettingChangePacket_<V> { using type = v2193::ServerboundPackSettingChangePacket; };

template <int V>
struct ResourcePackStackPacket_;

template <int V> requires (V < 898)
struct ResourcePackStackPacket_<V> { using type = base::ResourcePackStackPacket; };

template <int V> requires (V >= 898)
struct ResourcePackStackPacket_<V> { using type = v898::ResourcePackStackPacket; };

template <int V>
struct ResourcePackChunkRequestPacket_;

template <int V> requires (V < 2168)
struct ResourcePackChunkRequestPacket_<V> { using type = base::ResourcePackChunkRequestPacket; };

template <int V> requires (V >= 2168)
struct ResourcePackChunkRequestPacket_<V> { using type = v2168::ResourcePackChunkRequestPacket; };

template <int V>
struct ResourcePacksReadyForValidationPacket_;

template <int V> requires (V >= 944)
struct ResourcePacksReadyForValidationPacket_<V> { using type = v944::ResourcePacksReadyForValidationPacket; };

}  // namespace detail

template <int V> using PackIdVersion_ = typename detail::PackIdVersion_<V>::type;
template <int V> using PackInfoData_ = typename detail::PackInfoData_<V>::type;
template <int V> using PackUrl_ = typename detail::PackUrl_<V>::type;
template <int V> using ResourcePacksInfoPacket_ = typename detail::ResourcePacksInfoPacket_<V>::type;
template <int V> using ResourcePackClientResponsePacket_ = typename detail::ResourcePackClientResponsePacket_<V>::type;
template <int V> using ServerboundPackSettingChangePacket_ = typename detail::ServerboundPackSettingChangePacket_<V>::type;
template <int V> using ResourcePackStackPacket_ = typename detail::ResourcePackStackPacket_<V>::type;
template <int V> using ResourcePackChunkRequestPacket_ = typename detail::ResourcePackChunkRequestPacket_<V>::type;
template <int V> using ResourcePacksReadyForValidationPacket_ = typename detail::ResourcePacksReadyForValidationPacket_<V>::type;

template <int V>
struct packet_of<V, 6> { using type = ResourcePacksInfoPacket_<V>; };

template <int V>
struct packet_of<V, 7> { using type = ResourcePackStackPacket_<V>; };

template <int V>
struct packet_of<V, 8> { using type = ResourcePackClientResponsePacket_<V>; };

template <int V>
struct packet_of<V, 82> { using type = ResourcePackDataInfoPacket; };

template <int V>
struct packet_of<V, 83> { using type = ResourcePackChunkDataPacket; };

template <int V>
struct packet_of<V, 84> { using type = ResourcePackChunkRequestPacket_<V>; };

template <int V> requires (V >= 844)
struct packet_of<V, 329> { using type = ServerboundPackSettingChangePacket_<V>; };

template <int V> requires (V >= 944)
struct packet_of<V, 340> { using type = ResourcePacksReadyForValidationPacket_<V>; };

namespace detail {

template <>
inline constexpr std::array<ResourcePackResponse, 4> values_v<ResourcePackResponse>{{
    ResourcePackResponse::Cancel,
    ResourcePackResponse::Downloading,
    ResourcePackResponse::DownloadingFinished,
    ResourcePackResponse::ResourcePackStackFinished,
}};

template <>
inline constexpr std::array<std::string_view, 4> names_v<ResourcePackResponse>{{
    "cancel",
    "downloading",
    "downloadingfinished",
    "resourcepackstackfinished",
}};

template <>
inline constexpr std::string_view type_name_v<ResourcePackResponse>{"ResourcePackResponse"};

template <>
inline constexpr std::array<PackType, 10> values_v<PackType>{{
    PackType::Invalid,
    PackType::Addon,
    PackType::Cached,
    PackType::CopyProtected,
    PackType::Behavior,
    PackType::PersonaPiece,
    PackType::Resources,
    PackType::Skins,
    PackType::WorldTemplate,
    PackType::Count,
}};

template <>
inline constexpr std::array<std::string_view, 10> names_v<PackType>{{
    "invalid",
    "addon",
    "cached",
    "copyprotected",
    "behavior",
    "personapiece",
    "resources",
    "skins",
    "worldtemplate",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<PackType>{"PackType"};

}  // namespace detail

namespace detail {

template <>
inline constexpr bool is_reflected_struct_v<SemVersion> = true;

template <>
inline constexpr std::string_view struct_name_v<SemVersion>{"SemVersion"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<SemVersion>{{
    "version",
}};

template <>
struct field_accessor<SemVersion> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.version;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<ContentIdentity> = true;

template <>
inline constexpr std::string_view struct_name_v<ContentIdentity>{"ContentIdentity"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<ContentIdentity>{{
    "identity",
}};

template <>
struct field_accessor<ContentIdentity> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.identity;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::PackIdVersion> = true;

template <>
inline constexpr std::string_view struct_name_v<base::PackIdVersion>{"PackIdVersion"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<base::PackIdVersion>{{
    "id",
    "version",
}};

template <>
struct field_accessor<base::PackIdVersion> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.id;
        }
        else {
            return value.version;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v766::PackIdVersion> = true;

template <>
inline constexpr std::string_view struct_name_v<v766::PackIdVersion>{"PackIdVersion"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v766::PackIdVersion>{{
    "id",
    "version",
}};

template <>
struct field_accessor<v766::PackIdVersion> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.id;
        }
        else {
            return value.version;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::PackInfoData> = true;

template <>
inline constexpr std::string_view struct_name_v<base::PackInfoData>{"PackInfoData"};

template <>
inline constexpr std::array<std::string_view, 8> field_names_v<base::PackInfoData>{{
    "pack_id_version",
    "pack_size",
    "content_key",
    "subpack_name",
    "content_identity",
    "has_scripts",
    "is_addon_pack",
    "is_ray_tracing_capable",
}};

template <>
struct field_accessor<base::PackInfoData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.pack_id_version;
        }
        else if constexpr (I == 1) {
            return value.pack_size;
        }
        else if constexpr (I == 2) {
            return value.content_key;
        }
        else if constexpr (I == 3) {
            return value.subpack_name;
        }
        else if constexpr (I == 4) {
            return value.content_identity;
        }
        else if constexpr (I == 5) {
            return value.has_scripts;
        }
        else if constexpr (I == 6) {
            return value.is_addon_pack;
        }
        else {
            return value.is_ray_tracing_capable;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v748::PackInfoData> = true;

template <>
inline constexpr std::string_view struct_name_v<v748::PackInfoData>{"PackInfoData"};

template <>
inline constexpr std::array<std::string_view, 9> field_names_v<v748::PackInfoData>{{
    "pack_id_version",
    "pack_size",
    "content_key",
    "subpack_name",
    "content_identity",
    "has_scripts",
    "is_addon_pack",
    "is_ray_tracing_capable",
    "cdn_url",
}};

template <>
struct field_accessor<v748::PackInfoData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.pack_id_version;
        }
        else if constexpr (I == 1) {
            return value.pack_size;
        }
        else if constexpr (I == 2) {
            return value.content_key;
        }
        else if constexpr (I == 3) {
            return value.subpack_name;
        }
        else if constexpr (I == 4) {
            return value.content_identity;
        }
        else if constexpr (I == 5) {
            return value.has_scripts;
        }
        else if constexpr (I == 6) {
            return value.is_addon_pack;
        }
        else if constexpr (I == 7) {
            return value.is_ray_tracing_capable;
        }
        else {
            return value.cdn_url;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v766::PackInfoData> = true;

template <>
inline constexpr std::string_view struct_name_v<v766::PackInfoData>{"PackInfoData"};

template <>
inline constexpr std::array<std::string_view, 9> field_names_v<v766::PackInfoData>{{
    "pack_id_version",
    "pack_size",
    "content_key",
    "subpack_name",
    "content_identity",
    "has_scripts",
    "is_addon_pack",
    "is_ray_tracing_capable",
    "cdn_url",
}};

template <>
struct field_accessor<v766::PackInfoData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.pack_id_version;
        }
        else if constexpr (I == 1) {
            return value.pack_size;
        }
        else if constexpr (I == 2) {
            return value.content_key;
        }
        else if constexpr (I == 3) {
            return value.subpack_name;
        }
        else if constexpr (I == 4) {
            return value.content_identity;
        }
        else if constexpr (I == 5) {
            return value.has_scripts;
        }
        else if constexpr (I == 6) {
            return value.is_addon_pack;
        }
        else if constexpr (I == 7) {
            return value.is_ray_tracing_capable;
        }
        else {
            return value.cdn_url;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::PackUrl> = true;

template <>
inline constexpr std::string_view struct_name_v<base::PackUrl>{"PackUrl"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<base::PackUrl>{{
    "pack_id_and_version",
    "url",
}};

template <>
struct field_accessor<base::PackUrl> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.pack_id_and_version;
        }
        else {
            return value.url;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::ResourcePacksInfoPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ResourcePacksInfoPacket>{"ResourcePacksInfoPacket"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<base::ResourcePacksInfoPacket>{{
    "resource_pack_required",
    "has_addon_packs",
    "has_scripts",
    "resource_packs",
    "pack_urls",
}};

template <>
struct field_accessor<base::ResourcePacksInfoPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.resource_pack_required;
        }
        else if constexpr (I == 1) {
            return value.has_addon_packs;
        }
        else if constexpr (I == 2) {
            return value.has_scripts;
        }
        else if constexpr (I == 3) {
            return value.resource_packs;
        }
        else {
            return value.pack_urls;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v748::ResourcePacksInfoPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v748::ResourcePacksInfoPacket>{"ResourcePacksInfoPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v748::ResourcePacksInfoPacket>{{
    "resource_pack_required",
    "has_addon_packs",
    "has_scripts",
    "resource_packs",
}};

template <>
struct field_accessor<v748::ResourcePacksInfoPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.resource_pack_required;
        }
        else if constexpr (I == 1) {
            return value.has_addon_packs;
        }
        else if constexpr (I == 2) {
            return value.has_scripts;
        }
        else {
            return value.resource_packs;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v766::ResourcePacksInfoPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v766::ResourcePacksInfoPacket>{"ResourcePacksInfoPacket"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v766::ResourcePacksInfoPacket>{{
    "resource_pack_required",
    "has_addon_packs",
    "has_scripts",
    "world_template_id_and_version",
    "resource_packs",
}};

template <>
struct field_accessor<v766::ResourcePacksInfoPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.resource_pack_required;
        }
        else if constexpr (I == 1) {
            return value.has_addon_packs;
        }
        else if constexpr (I == 2) {
            return value.has_scripts;
        }
        else if constexpr (I == 3) {
            return value.world_template_id_and_version;
        }
        else {
            return value.resource_packs;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v818::ResourcePacksInfoPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v818::ResourcePacksInfoPacket>{"ResourcePacksInfoPacket"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<v818::ResourcePacksInfoPacket>{{
    "resource_pack_required",
    "has_addon_packs",
    "has_scripts",
    "force_disable_vibrant_visuals",
    "world_template_id_and_version",
    "resource_packs",
}};

template <>
struct field_accessor<v818::ResourcePacksInfoPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.resource_pack_required;
        }
        else if constexpr (I == 1) {
            return value.has_addon_packs;
        }
        else if constexpr (I == 2) {
            return value.has_scripts;
        }
        else if constexpr (I == 3) {
            return value.force_disable_vibrant_visuals;
        }
        else if constexpr (I == 4) {
            return value.world_template_id_and_version;
        }
        else {
            return value.resource_packs;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ResourcePacksInfoPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ResourcePacksInfoPacket>{"ResourcePacksInfoPacket"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<v2168::ResourcePacksInfoPacket>{{
    "resource_pack_required",
    "has_addon_packs",
    "has_scripts",
    "force_disable_vibrant_visuals",
    "world_template_id_and_version",
    "resource_packs",
}};

template <>
struct field_accessor<v2168::ResourcePacksInfoPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.resource_pack_required;
        }
        else if constexpr (I == 1) {
            return value.has_addon_packs;
        }
        else if constexpr (I == 2) {
            return value.has_scripts;
        }
        else if constexpr (I == 3) {
            return value.force_disable_vibrant_visuals;
        }
        else if constexpr (I == 4) {
            return value.world_template_id_and_version;
        }
        else {
            return value.resource_packs;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::ResourcePackClientResponsePacket::Cancel> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ResourcePackClientResponsePacket::Cancel>{"ResourcePackClientResponsePacket::Cancel"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<base::ResourcePackClientResponsePacket::Cancel>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<base::ResourcePackClientResponsePacket::Downloading> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ResourcePackClientResponsePacket::Downloading>{"ResourcePackClientResponsePacket::Downloading"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::ResourcePackClientResponsePacket::Downloading>{{
    "downloading_packs",
}};

template <>
struct field_accessor<base::ResourcePackClientResponsePacket::Downloading> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.downloading_packs;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::ResourcePackClientResponsePacket::DownloadingFinished> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ResourcePackClientResponsePacket::DownloadingFinished>{"ResourcePackClientResponsePacket::DownloadingFinished"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<base::ResourcePackClientResponsePacket::DownloadingFinished>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<base::ResourcePackClientResponsePacket::ResourcePackStackFinished> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ResourcePackClientResponsePacket::ResourcePackStackFinished>{"ResourcePackClientResponsePacket::ResourcePackStackFinished"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<base::ResourcePackClientResponsePacket::ResourcePackStackFinished>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<base::ResourcePackClientResponsePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ResourcePackClientResponsePacket>{"ResourcePackClientResponsePacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<base::ResourcePackClientResponsePacket>{{
    "response",
    "downloading_packs",
}};

template <>
struct field_accessor<base::ResourcePackClientResponsePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.response;
        }
        else {
            return value.downloading_packs;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ResourcePackClientResponsePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ResourcePackClientResponsePacket>{"ResourcePackClientResponsePacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2168::ResourcePackClientResponsePacket>{{
    "response",
}};

template <>
struct field_accessor<v2168::ResourcePackClientResponsePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.response;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v844::ServerboundPackSettingChangePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v844::ServerboundPackSettingChangePacket>{"ServerboundPackSettingChangePacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v844::ServerboundPackSettingChangePacket>{{
    "pack_id",
    "setting_name",
    "setting_value",
}};

template <>
struct field_accessor<v844::ServerboundPackSettingChangePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.pack_id;
        }
        else if constexpr (I == 1) {
            return value.setting_name;
        }
        else {
            return value.setting_value;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2193::ServerboundPackSettingChangePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2193::ServerboundPackSettingChangePacket>{"ServerboundPackSettingChangePacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v2193::ServerboundPackSettingChangePacket>{{
    "pack_id",
    "setting_name",
    "setting_value",
}};

template <>
struct field_accessor<v2193::ServerboundPackSettingChangePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.pack_id;
        }
        else if constexpr (I == 1) {
            return value.setting_name;
        }
        else {
            return value.setting_value;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<PackInstanceId> = true;

template <>
inline constexpr std::string_view struct_name_v<PackInstanceId>{"PackInstanceId"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<PackInstanceId>{{
    "pack_id",
    "version",
    "subpack_name",
}};

template <>
struct field_accessor<PackInstanceId> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.pack_id;
        }
        else if constexpr (I == 1) {
            return value.version;
        }
        else {
            return value.subpack_name;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::ResourcePackStackPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ResourcePackStackPacket>{"ResourcePackStackPacket"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<base::ResourcePackStackPacket>{{
    "texture_pack_required",
    "add_on_ids_and_versions",
    "texture_pack_ids_and_versions",
    "base_game_version",
    "experiments",
    "include_editor_packs",
}};

template <>
struct field_accessor<base::ResourcePackStackPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.texture_pack_required;
        }
        else if constexpr (I == 1) {
            return value.add_on_ids_and_versions;
        }
        else if constexpr (I == 2) {
            return value.texture_pack_ids_and_versions;
        }
        else if constexpr (I == 3) {
            return value.base_game_version;
        }
        else if constexpr (I == 4) {
            return value.experiments;
        }
        else {
            return value.include_editor_packs;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v898::ResourcePackStackPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v898::ResourcePackStackPacket>{"ResourcePackStackPacket"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v898::ResourcePackStackPacket>{{
    "texture_pack_required",
    "texture_pack_ids_and_versions",
    "base_game_version",
    "experiments",
    "include_editor_packs",
}};

template <>
struct field_accessor<v898::ResourcePackStackPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.texture_pack_required;
        }
        else if constexpr (I == 1) {
            return value.texture_pack_ids_and_versions;
        }
        else if constexpr (I == 2) {
            return value.base_game_version;
        }
        else if constexpr (I == 3) {
            return value.experiments;
        }
        else {
            return value.include_editor_packs;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<ResourcePackDataInfoPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<ResourcePackDataInfoPacket>{"ResourcePackDataInfoPacket"};

template <>
inline constexpr std::array<std::string_view, 7> field_names_v<ResourcePackDataInfoPacket>{{
    "resource_name",
    "chunk_size",
    "nb_chunks",
    "file_size",
    "file_hash",
    "is_premium",
    "pack_type",
}};

template <>
struct field_accessor<ResourcePackDataInfoPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.resource_name;
        }
        else if constexpr (I == 1) {
            return value.chunk_size;
        }
        else if constexpr (I == 2) {
            return value.nb_chunks;
        }
        else if constexpr (I == 3) {
            return value.file_size;
        }
        else if constexpr (I == 4) {
            return value.file_hash;
        }
        else if constexpr (I == 5) {
            return value.is_premium;
        }
        else {
            return value.pack_type;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<ResourcePackChunkDataPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<ResourcePackChunkDataPacket>{"ResourcePackChunkDataPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<ResourcePackChunkDataPacket>{{
    "resource_name",
    "chunk_id",
    "byte_offset",
    "data",
}};

template <>
struct field_accessor<ResourcePackChunkDataPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.resource_name;
        }
        else if constexpr (I == 1) {
            return value.chunk_id;
        }
        else if constexpr (I == 2) {
            return value.byte_offset;
        }
        else {
            return value.data;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::ResourcePackChunkRequestPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ResourcePackChunkRequestPacket>{"ResourcePackChunkRequestPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<base::ResourcePackChunkRequestPacket>{{
    "resource_name",
    "chunk",
}};

template <>
struct field_accessor<base::ResourcePackChunkRequestPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.resource_name;
        }
        else {
            return value.chunk;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ResourcePackChunkRequestPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ResourcePackChunkRequestPacket>{"ResourcePackChunkRequestPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2168::ResourcePackChunkRequestPacket>{{
    "resource_name",
    "chunk",
}};

template <>
struct field_accessor<v2168::ResourcePackChunkRequestPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.resource_name;
        }
        else {
            return value.chunk;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::ResourcePacksReadyForValidationPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::ResourcePacksReadyForValidationPacket>{"ResourcePacksReadyForValidationPacket"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<v944::ResourcePacksReadyForValidationPacket>{{
}};

}  // namespace detail


template <>
struct Serializer<SemVersion> {
    static void serialize(BinaryWriter &stream, const SemVersion &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<SemVersion, std::error_code>;
};

template <>
struct Serializer<ContentIdentity> {
    static void serialize(BinaryWriter &stream, const ContentIdentity &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<ContentIdentity, std::error_code>;
};

template <>
struct Serializer<base::PackIdVersion> {
    static void serialize(BinaryWriter &stream, const base::PackIdVersion &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::PackIdVersion, std::error_code>;
};

template <>
struct Serializer<v766::PackIdVersion> {
    static void serialize(BinaryWriter &stream, const v766::PackIdVersion &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v766::PackIdVersion, std::error_code>;
};

template <>
struct Serializer<base::PackInfoData> {
    static void serialize(BinaryWriter &stream, const base::PackInfoData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::PackInfoData, std::error_code>;
};

template <>
struct Serializer<v748::PackInfoData> {
    static void serialize(BinaryWriter &stream, const v748::PackInfoData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v748::PackInfoData, std::error_code>;
};

template <>
struct Serializer<v766::PackInfoData> {
    static void serialize(BinaryWriter &stream, const v766::PackInfoData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v766::PackInfoData, std::error_code>;
};

template <>
struct Serializer<base::PackUrl> {
    static void serialize(BinaryWriter &stream, const base::PackUrl &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::PackUrl, std::error_code>;
};

template <>
struct Serializer<base::ResourcePacksInfoPacket> {
    static void serialize(BinaryWriter &stream, const base::ResourcePacksInfoPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ResourcePacksInfoPacket, std::error_code>;
};

template <>
struct Serializer<v748::ResourcePacksInfoPacket> {
    static void serialize(BinaryWriter &stream, const v748::ResourcePacksInfoPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v748::ResourcePacksInfoPacket, std::error_code>;
};

template <>
struct Serializer<v766::ResourcePacksInfoPacket> {
    static void serialize(BinaryWriter &stream, const v766::ResourcePacksInfoPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v766::ResourcePacksInfoPacket, std::error_code>;
};

template <>
struct Serializer<v818::ResourcePacksInfoPacket> {
    static void serialize(BinaryWriter &stream, const v818::ResourcePacksInfoPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v818::ResourcePacksInfoPacket, std::error_code>;
};

template <>
struct Serializer<v2168::ResourcePacksInfoPacket> {
    static void serialize(BinaryWriter &stream, const v2168::ResourcePacksInfoPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ResourcePacksInfoPacket, std::error_code>;
};

template <>
struct Serializer<base::ResourcePackClientResponsePacket::Cancel> {
    static void serialize(BinaryWriter &stream, const base::ResourcePackClientResponsePacket::Cancel &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ResourcePackClientResponsePacket::Cancel, std::error_code>;
};

template <>
struct Serializer<base::ResourcePackClientResponsePacket::Downloading> {
    static void serialize(BinaryWriter &stream, const base::ResourcePackClientResponsePacket::Downloading &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ResourcePackClientResponsePacket::Downloading, std::error_code>;
};

template <>
struct Serializer<base::ResourcePackClientResponsePacket::DownloadingFinished> {
    static void serialize(BinaryWriter &stream, const base::ResourcePackClientResponsePacket::DownloadingFinished &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ResourcePackClientResponsePacket::DownloadingFinished, std::error_code>;
};

template <>
struct Serializer<base::ResourcePackClientResponsePacket::ResourcePackStackFinished> {
    static void serialize(BinaryWriter &stream, const base::ResourcePackClientResponsePacket::ResourcePackStackFinished &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ResourcePackClientResponsePacket::ResourcePackStackFinished, std::error_code>;
};

template <>
struct Serializer<base::ResourcePackClientResponsePacket> {
    static void serialize(BinaryWriter &stream, const base::ResourcePackClientResponsePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ResourcePackClientResponsePacket, std::error_code>;
};

template <>
struct Serializer<v2168::ResourcePackClientResponsePacket> {
    static void serialize(BinaryWriter &stream, const v2168::ResourcePackClientResponsePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ResourcePackClientResponsePacket, std::error_code>;
};

template <>
struct Serializer<v844::ServerboundPackSettingChangePacket> {
    static void serialize(BinaryWriter &stream, const v844::ServerboundPackSettingChangePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v844::ServerboundPackSettingChangePacket, std::error_code>;
};

template <>
struct Serializer<v2193::ServerboundPackSettingChangePacket> {
    static void serialize(BinaryWriter &stream, const v2193::ServerboundPackSettingChangePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::ServerboundPackSettingChangePacket, std::error_code>;
};

template <>
struct Serializer<PackInstanceId> {
    static void serialize(BinaryWriter &stream, const PackInstanceId &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<PackInstanceId, std::error_code>;
};

template <>
struct Serializer<base::ResourcePackStackPacket> {
    static void serialize(BinaryWriter &stream, const base::ResourcePackStackPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ResourcePackStackPacket, std::error_code>;
};

template <>
struct Serializer<v898::ResourcePackStackPacket> {
    static void serialize(BinaryWriter &stream, const v898::ResourcePackStackPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v898::ResourcePackStackPacket, std::error_code>;
};

template <>
struct Serializer<ResourcePackDataInfoPacket> {
    static void serialize(BinaryWriter &stream, const ResourcePackDataInfoPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<ResourcePackDataInfoPacket, std::error_code>;
};

template <>
struct Serializer<ResourcePackChunkDataPacket> {
    static void serialize(BinaryWriter &stream, const ResourcePackChunkDataPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<ResourcePackChunkDataPacket, std::error_code>;
};

template <>
struct Serializer<base::ResourcePackChunkRequestPacket> {
    static void serialize(BinaryWriter &stream, const base::ResourcePackChunkRequestPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ResourcePackChunkRequestPacket, std::error_code>;
};

template <>
struct Serializer<v2168::ResourcePackChunkRequestPacket> {
    static void serialize(BinaryWriter &stream, const v2168::ResourcePackChunkRequestPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ResourcePackChunkRequestPacket, std::error_code>;
};

template <>
struct Serializer<v944::ResourcePacksReadyForValidationPacket> {
    static void serialize(BinaryWriter &stream, const v944::ResourcePacksReadyForValidationPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::ResourcePacksReadyForValidationPacket, std::error_code>;
};
using PackIdVersion = PackIdVersion_<2225>;
using PackInfoData = PackInfoData_<2225>;
using ResourcePacksInfoPacket = ResourcePacksInfoPacket_<2225>;
using ResourcePackClientResponsePacket = ResourcePackClientResponsePacket_<2225>;
using ServerboundPackSettingChangePacket = ServerboundPackSettingChangePacket_<2225>;
using ResourcePackStackPacket = ResourcePackStackPacket_<2225>;
using ResourcePackChunkRequestPacket = ResourcePackChunkRequestPacket_<2225>;
using ResourcePacksReadyForValidationPacket = ResourcePacksReadyForValidationPacket_<2225>;

}  // namespace bedrock::protocol
