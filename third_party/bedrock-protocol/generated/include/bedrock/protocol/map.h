#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <expected>
#include <optional>
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

#include <bedrock/protocol/actor.h>
#include <bedrock/protocol/common.h>
#include <bedrock/protocol/network.h>

namespace bedrock::protocol {

namespace MapInfoRequestPacket_nested {

struct ClientPixelsProxy {
    std::uint32_t pixel{};
    std::uint16_t index{};
};

}  // namespace MapInfoRequestPacket_nested

struct MapInfoRequestPacket {
    using ClientPixelsProxy = MapInfoRequestPacket_nested::ClientPixelsProxy;

    static constexpr int Id = 68;
    ActorUniqueID map_id{};
    std::vector<MapInfoRequestPacket::ClientPixelsProxy> client_pixels{};
};

struct MapCreateLockedCopyPacket {
    static constexpr int Id = 131;
    ActorUniqueID original_map_id{};
    ActorUniqueID new_map_id{};
};

struct CreatePhotoPacket {
    static constexpr int Id = 171;
    ActorUniqueID id{};
    std::string photo_name{};
    std::string photo_item_name{};
};

enum class PhotoType : std::uint8_t {
    Portfolio = 0,
    PhotoItem = 1,
    Book = 2,
};

struct PhotoTransferPacket {
    static constexpr int Id = 99;
    std::string photo_name{};
    std::string photo_data{};
    std::string book_id{};
    PhotoType type{};
    PhotoType source_type{};
    ActorUniqueID owner_id{};
    std::string new_photo_name{};
};

namespace base {

namespace MapItemTrackedActor_nested {

enum class Type : int {
    Entity = 0,
    BlockEntity = 1,
    Other = 2,
};

struct UniqueId {
    Type type{};
    ActorUniqueID key_entity_id{};
    base::NetworkBlockPosition key_block_pos{};
};

}  // namespace MapItemTrackedActor_nested

struct MapItemTrackedActor {
    using Type = MapItemTrackedActor_nested::Type;
    using UniqueId = MapItemTrackedActor_nested::UniqueId;
};

namespace MapDecoration_nested {

enum class Type : std::int8_t {
    MarkerWhite = 0,
    MarkerGreen = 1,
    MarkerRed = 2,
    MarkerBlue = 3,
    XWhite = 4,
    TriangleRed = 5,
    SquareWhite = 6,
    MarkerSign = 7,
    MarkerPink = 8,
    MarkerOrange = 9,
    MarkerYellow = 10,
    MarkerTeal = 11,
    TriangleGreen = 12,
    SmallSquareWhite = 13,
    Mansion = 14,
    Monument = 15,
    NoDraw = 16,
    VillageDesert = 17,
    VillagePlains = 18,
    VillageSavanna = 19,
    VillageSnowy = 20,
    VillageTaiga = 21,
    JungleTemple = 22,
    WitchHut = 23,
    TrialChambers = 24,
    Count = 25,
};

}  // namespace MapDecoration_nested

struct MapDecoration {
    using Type = MapDecoration_nested::Type;

    base::MapDecoration::Type image{};
    std::int8_t rotation{};
    std::int8_t x{};
    std::int8_t y{};
    std::string label{};
    Color color{};
};

namespace ClientboundMapItemDataPacket_nested {

enum class Type : int {
    Invalid = 0,
    TextureUpdate = 2,
    DecorationUpdate = 4,
    Creation = 8,
};

}  // namespace ClientboundMapItemDataPacket_nested

struct ClientboundMapItemDataPacket {
    using Type = ClientboundMapItemDataPacket_nested::Type;

    static constexpr int Id = 67;
    ActorUniqueID map_id{};
    std::uint32_t type{};
    std::uint8_t dimension{};
    bool locked{};
    BlockPos map_origin{};
    std::vector<ActorUniqueID> map_ids{};
    std::int8_t scale{};
    std::vector<base::MapItemTrackedActor::UniqueId> unique_ids{};
    std::vector<base::MapDecoration> decorations{};
    std::int32_t width{};
    std::int32_t height{};
    std::int32_t start_x{};
    std::int32_t start_y{};
    std::vector<std::uint32_t> map_pixels{};
};

}  // namespace base

namespace v748 {

using MapItemTrackedActor = base::MapItemTrackedActor;

using MapDecoration = base::MapDecoration;

using ClientboundMapItemDataPacket = base::ClientboundMapItemDataPacket;

}  // namespace v748

namespace v766 {

using MapItemTrackedActor = base::MapItemTrackedActor;

using MapDecoration = base::MapDecoration;

using ClientboundMapItemDataPacket = base::ClientboundMapItemDataPacket;

}  // namespace v766

namespace v776 {

using MapItemTrackedActor = base::MapItemTrackedActor;

using MapDecoration = base::MapDecoration;

using ClientboundMapItemDataPacket = base::ClientboundMapItemDataPacket;

}  // namespace v776

namespace v786 {

using MapItemTrackedActor = base::MapItemTrackedActor;

using MapDecoration = base::MapDecoration;

using ClientboundMapItemDataPacket = base::ClientboundMapItemDataPacket;

namespace PlayerVideoCapturePacket_nested {

struct StartVideoCapture {
    std::uint32_t frame_rate{};
    std::string file_prefix{};
};

struct StopVideoCapture {
};

}  // namespace PlayerVideoCapturePacket_nested

struct PlayerVideoCapturePacket {
    using StartVideoCapture = PlayerVideoCapturePacket_nested::StartVideoCapture;
    using StopVideoCapture = PlayerVideoCapturePacket_nested::StopVideoCapture;

    static constexpr int Id = 324;
    std::variant<v786::PlayerVideoCapturePacket::StartVideoCapture, v786::PlayerVideoCapturePacket::StopVideoCapture> start_video_capture{};
    std::variant<v786::PlayerVideoCapturePacket::StartVideoCapture, v786::PlayerVideoCapturePacket::StopVideoCapture> stop_video_capture{};
};

}  // namespace v786

namespace v800 {

using MapItemTrackedActor = base::MapItemTrackedActor;

using MapDecoration = base::MapDecoration;

using ClientboundMapItemDataPacket = base::ClientboundMapItemDataPacket;

using PlayerVideoCapturePacket = v786::PlayerVideoCapturePacket;

}  // namespace v800

namespace v818 {

using MapItemTrackedActor = base::MapItemTrackedActor;

using MapDecoration = base::MapDecoration;

using ClientboundMapItemDataPacket = base::ClientboundMapItemDataPacket;

using PlayerVideoCapturePacket = v786::PlayerVideoCapturePacket;

}  // namespace v818

namespace v827 {

using MapItemTrackedActor = base::MapItemTrackedActor;

using MapDecoration = base::MapDecoration;

using ClientboundMapItemDataPacket = base::ClientboundMapItemDataPacket;

using PlayerVideoCapturePacket = v786::PlayerVideoCapturePacket;

}  // namespace v827

namespace v844 {

using MapItemTrackedActor = base::MapItemTrackedActor;

using MapDecoration = base::MapDecoration;

using ClientboundMapItemDataPacket = base::ClientboundMapItemDataPacket;

using PlayerVideoCapturePacket = v786::PlayerVideoCapturePacket;

}  // namespace v844

namespace v859 {

using MapItemTrackedActor = base::MapItemTrackedActor;

using MapDecoration = base::MapDecoration;

using ClientboundMapItemDataPacket = base::ClientboundMapItemDataPacket;

using PlayerVideoCapturePacket = v786::PlayerVideoCapturePacket;

}  // namespace v859

namespace v898 {

using MapItemTrackedActor = base::MapItemTrackedActor;

using MapDecoration = base::MapDecoration;

using ClientboundMapItemDataPacket = base::ClientboundMapItemDataPacket;

using PlayerVideoCapturePacket = v786::PlayerVideoCapturePacket;

}  // namespace v898

namespace v924 {

using MapItemTrackedActor = base::MapItemTrackedActor;

using MapDecoration = base::MapDecoration;

using ClientboundMapItemDataPacket = base::ClientboundMapItemDataPacket;

using PlayerVideoCapturePacket = v786::PlayerVideoCapturePacket;

}  // namespace v924

namespace v944 {

namespace MapItemTrackedActor_nested {

using Type = base::MapItemTrackedActor::Type;

struct UniqueId {
    Type type{};
    ActorUniqueID key_entity_id{};
    BlockPos key_block_pos{};
};

}  // namespace MapItemTrackedActor_nested

struct MapItemTrackedActor {
    using Type = MapItemTrackedActor_nested::Type;
    using UniqueId = MapItemTrackedActor_nested::UniqueId;
};

using MapDecoration = base::MapDecoration;

namespace ClientboundMapItemDataPacket_nested {

using Type = base::ClientboundMapItemDataPacket::Type;

}  // namespace ClientboundMapItemDataPacket_nested

struct ClientboundMapItemDataPacket {
    using Type = ClientboundMapItemDataPacket_nested::Type;

    static constexpr int Id = 67;
    ActorUniqueID map_id{};
    std::uint32_t type{};
    std::uint8_t dimension{};
    bool locked{};
    BlockPos map_origin{};
    std::vector<ActorUniqueID> map_ids{};
    std::int8_t scale{};
    std::vector<v944::MapItemTrackedActor::UniqueId> unique_ids{};
    std::vector<base::MapDecoration> decorations{};
    std::int32_t width{};
    std::int32_t height{};
    std::int32_t start_x{};
    std::int32_t start_y{};
    std::vector<std::uint32_t> map_pixels{};
};

using PlayerVideoCapturePacket = v786::PlayerVideoCapturePacket;

}  // namespace v944

namespace v975 {

using MapItemTrackedActor = v944::MapItemTrackedActor;

using MapDecoration = base::MapDecoration;

using ClientboundMapItemDataPacket = v944::ClientboundMapItemDataPacket;

using PlayerVideoCapturePacket = v786::PlayerVideoCapturePacket;

}  // namespace v975

namespace v1001 {

using MapItemTrackedActor = v944::MapItemTrackedActor;

using MapDecoration = base::MapDecoration;

using ClientboundMapItemDataPacket = v944::ClientboundMapItemDataPacket;

using PlayerVideoCapturePacket = v786::PlayerVideoCapturePacket;

}  // namespace v1001

namespace v2168 {

namespace MapItemTrackedActor_nested {

using Type = base::MapItemTrackedActor::Type;

struct UniqueId {
    Type type{};
    std::optional<ActorUniqueID> key_entity_id{};
    std::optional<BlockPos> key_block_pos{};
};

}  // namespace MapItemTrackedActor_nested

struct MapItemTrackedActor {
    using Type = MapItemTrackedActor_nested::Type;
    using UniqueId = MapItemTrackedActor_nested::UniqueId;
};

namespace MapDecoration_nested {

enum class Type : std::int8_t {
    MarkerWhite = 0,
    MarkerGreen = 1,
    MarkerRed = 2,
    MarkerBlue = 3,
    XWhite = 4,
    TriangleRed = 5,
    SquareWhite = 6,
    MarkerSign = 7,
    MarkerPink = 8,
    MarkerOrange = 9,
    MarkerYellow = 10,
    MarkerTeal = 11,
    TriangleGreen = 12,
    SmallSquareWhite = 13,
    Mansion = 14,
    Monument = 15,
    NoDraw = 16,
    VillageDesert = 17,
    VillagePlains = 18,
    VillageSavanna = 19,
    VillageSnowy = 20,
    VillageTaiga = 21,
    JungleTemple = 22,
    WitchHut = 23,
    TrialChambers = 24,
    Count = 25,
};

}  // namespace MapDecoration_nested

struct MapDecoration {
    using Type = MapDecoration_nested::Type;

    v2168::MapDecoration::Type image{};
    std::int8_t rotation{};
    std::int8_t x{};
    std::int8_t y{};
    std::string label{};
    Color color{};
};

namespace ClientboundMapItemDataPacket_nested {

using Type = base::ClientboundMapItemDataPacket::Type;

}  // namespace ClientboundMapItemDataPacket_nested

struct ClientboundMapItemDataPacket {
    using Type = ClientboundMapItemDataPacket_nested::Type;

    static constexpr int Id = 67;
    ActorUniqueID map_id{};
    std::uint8_t dimension{};
    bool locked{};
    BlockPos map_origin{};
    std::optional<std::vector<ActorUniqueID>> creation_map_ids{};
    std::optional<std::int8_t> scale{};
    std::optional<std::vector<v2168::MapItemTrackedActor::UniqueId>> unique_ids{};
    std::optional<std::vector<v2168::MapDecoration>> decorations{};
    std::optional<std::int32_t> width{};
    std::optional<std::int32_t> height{};
    std::optional<std::int32_t> start_x{};
    std::optional<std::int32_t> start_y{};
    std::optional<std::vector<std::uint32_t>> map_pixels{};
};

using PlayerVideoCapturePacket = v786::PlayerVideoCapturePacket;

}  // namespace v2168

namespace v2193 {

using MapItemTrackedActor = v2168::MapItemTrackedActor;

namespace MapDecoration_nested {

enum class Type : std::int8_t {
    MarkerWhite = 0,
    MarkerGreen = 1,
    MarkerRed = 2,
    MarkerBlue = 3,
    XWhite = 4,
    TriangleRed = 5,
    SquareWhite = 6,
    MarkerSign = 7,
    MarkerPink = 8,
    MarkerOrange = 9,
    MarkerYellow = 10,
    MarkerTeal = 11,
    TriangleGreen = 12,
    SmallSquareWhite = 13,
    Mansion = 14,
    Monument = 15,
    NoDraw = 16,
    VillageDesert = 17,
    VillagePlains = 18,
    VillageSavanna = 19,
    VillageSnowy = 20,
    VillageTaiga = 21,
    JungleTemple = 22,
    WitchHut = 23,
    TrialChambers = 24,
    AbandonedCamp = 25,
    BuriedAncientCity = 26,
    BuriedMineshaft = 27,
    DesertPyramid = 28,
    WarmOceanRuins = 29,
    Count = 30,
};

}  // namespace MapDecoration_nested

struct MapDecoration {
    using Type = MapDecoration_nested::Type;

    v2193::MapDecoration::Type image{};
    std::int8_t rotation{};
    std::int8_t x{};
    std::int8_t y{};
    std::string label{};
    Color color{};
};

namespace ClientboundMapItemDataPacket_nested {

using Type = base::ClientboundMapItemDataPacket::Type;

}  // namespace ClientboundMapItemDataPacket_nested

struct ClientboundMapItemDataPacket {
    using Type = ClientboundMapItemDataPacket_nested::Type;

    static constexpr int Id = 67;
    ActorUniqueID map_id{};
    std::uint8_t dimension{};
    bool locked{};
    BlockPos map_origin{};
    std::optional<std::vector<ActorUniqueID>> creation_map_ids{};
    std::optional<std::int8_t> scale{};
    std::optional<std::vector<v2168::MapItemTrackedActor::UniqueId>> unique_ids{};
    std::optional<std::vector<v2193::MapDecoration>> decorations{};
    std::optional<std::int32_t> width{};
    std::optional<std::int32_t> height{};
    std::optional<std::int32_t> start_x{};
    std::optional<std::int32_t> start_y{};
    std::optional<std::vector<std::uint32_t>> map_pixels{};
};

using PlayerVideoCapturePacket = v786::PlayerVideoCapturePacket;

}  // namespace v2193

namespace v2225 {

using MapItemTrackedActor = v2168::MapItemTrackedActor;

using MapDecoration = v2193::MapDecoration;

using ClientboundMapItemDataPacket = v2193::ClientboundMapItemDataPacket;

using PlayerVideoCapturePacket = v786::PlayerVideoCapturePacket;

}  // namespace v2225

namespace detail {

template <int V>
struct MapItemTrackedActor_;

template <int V> requires (V < 944)
struct MapItemTrackedActor_<V> { using type = base::MapItemTrackedActor; };

template <int V> requires (V >= 944 && V < 2168)
struct MapItemTrackedActor_<V> { using type = v944::MapItemTrackedActor; };

template <int V> requires (V >= 2168)
struct MapItemTrackedActor_<V> { using type = v2168::MapItemTrackedActor; };

template <int V>
struct MapDecoration_;

template <int V> requires (V < 2168)
struct MapDecoration_<V> { using type = base::MapDecoration; };

template <int V> requires (V >= 2168 && V < 2193)
struct MapDecoration_<V> { using type = v2168::MapDecoration; };

template <int V> requires (V >= 2193)
struct MapDecoration_<V> { using type = v2193::MapDecoration; };

template <int V>
struct ClientboundMapItemDataPacket_;

template <int V> requires (V < 944)
struct ClientboundMapItemDataPacket_<V> { using type = base::ClientboundMapItemDataPacket; };

template <int V> requires (V >= 944 && V < 2168)
struct ClientboundMapItemDataPacket_<V> { using type = v944::ClientboundMapItemDataPacket; };

template <int V> requires (V >= 2168 && V < 2193)
struct ClientboundMapItemDataPacket_<V> { using type = v2168::ClientboundMapItemDataPacket; };

template <int V> requires (V >= 2193)
struct ClientboundMapItemDataPacket_<V> { using type = v2193::ClientboundMapItemDataPacket; };

template <int V>
struct PlayerVideoCapturePacket_;

template <int V> requires (V >= 786)
struct PlayerVideoCapturePacket_<V> { using type = v786::PlayerVideoCapturePacket; };

}  // namespace detail

template <int V> using MapItemTrackedActor_ = typename detail::MapItemTrackedActor_<V>::type;
template <int V> using MapDecoration_ = typename detail::MapDecoration_<V>::type;
template <int V> using ClientboundMapItemDataPacket_ = typename detail::ClientboundMapItemDataPacket_<V>::type;
template <int V> using PlayerVideoCapturePacket_ = typename detail::PlayerVideoCapturePacket_<V>::type;

template <int V>
struct packet_of<V, 67> { using type = ClientboundMapItemDataPacket_<V>; };

template <int V>
struct packet_of<V, 68> { using type = MapInfoRequestPacket; };

template <int V>
struct packet_of<V, 99> { using type = PhotoTransferPacket; };

template <int V>
struct packet_of<V, 131> { using type = MapCreateLockedCopyPacket; };

template <int V>
struct packet_of<V, 171> { using type = CreatePhotoPacket; };

template <int V> requires (V >= 786)
struct packet_of<V, 324> { using type = PlayerVideoCapturePacket_<V>; };

namespace detail {

template <>
inline constexpr std::array<base::MapItemTrackedActor::Type, 3> values_v<base::MapItemTrackedActor::Type>{{
    base::MapItemTrackedActor::Type::Entity,
    base::MapItemTrackedActor::Type::BlockEntity,
    base::MapItemTrackedActor::Type::Other,
}};

template <>
inline constexpr std::array<std::string_view, 3> names_v<base::MapItemTrackedActor::Type>{{
    "entity",
    "blockentity",
    "other",
}};

template <>
inline constexpr std::string_view type_name_v<base::MapItemTrackedActor::Type>{"MapItemTrackedActor::Type"};

template <>
inline constexpr std::array<base::MapDecoration::Type, 26> values_v<base::MapDecoration::Type>{{
    base::MapDecoration::Type::MarkerWhite,
    base::MapDecoration::Type::MarkerGreen,
    base::MapDecoration::Type::MarkerRed,
    base::MapDecoration::Type::MarkerBlue,
    base::MapDecoration::Type::XWhite,
    base::MapDecoration::Type::TriangleRed,
    base::MapDecoration::Type::SquareWhite,
    base::MapDecoration::Type::MarkerSign,
    base::MapDecoration::Type::MarkerPink,
    base::MapDecoration::Type::MarkerOrange,
    base::MapDecoration::Type::MarkerYellow,
    base::MapDecoration::Type::MarkerTeal,
    base::MapDecoration::Type::TriangleGreen,
    base::MapDecoration::Type::SmallSquareWhite,
    base::MapDecoration::Type::Mansion,
    base::MapDecoration::Type::Monument,
    base::MapDecoration::Type::NoDraw,
    base::MapDecoration::Type::VillageDesert,
    base::MapDecoration::Type::VillagePlains,
    base::MapDecoration::Type::VillageSavanna,
    base::MapDecoration::Type::VillageSnowy,
    base::MapDecoration::Type::VillageTaiga,
    base::MapDecoration::Type::JungleTemple,
    base::MapDecoration::Type::WitchHut,
    base::MapDecoration::Type::TrialChambers,
    base::MapDecoration::Type::Count,
}};

template <>
inline constexpr std::array<std::string_view, 26> names_v<base::MapDecoration::Type>{{
    "markerwhite",
    "markergreen",
    "markerred",
    "markerblue",
    "xwhite",
    "trianglered",
    "squarewhite",
    "markersign",
    "markerpink",
    "markerorange",
    "markeryellow",
    "markerteal",
    "trianglegreen",
    "smallsquarewhite",
    "mansion",
    "monument",
    "nodraw",
    "villagedesert",
    "villageplains",
    "villagesavanna",
    "villagesnowy",
    "villagetaiga",
    "jungletemple",
    "witchhut",
    "trialchambers",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<base::MapDecoration::Type>{"MapDecoration::Type"};

template <>
inline constexpr std::array<v2168::MapDecoration::Type, 26> values_v<v2168::MapDecoration::Type>{{
    v2168::MapDecoration::Type::MarkerWhite,
    v2168::MapDecoration::Type::MarkerGreen,
    v2168::MapDecoration::Type::MarkerRed,
    v2168::MapDecoration::Type::MarkerBlue,
    v2168::MapDecoration::Type::XWhite,
    v2168::MapDecoration::Type::TriangleRed,
    v2168::MapDecoration::Type::SquareWhite,
    v2168::MapDecoration::Type::MarkerSign,
    v2168::MapDecoration::Type::MarkerPink,
    v2168::MapDecoration::Type::MarkerOrange,
    v2168::MapDecoration::Type::MarkerYellow,
    v2168::MapDecoration::Type::MarkerTeal,
    v2168::MapDecoration::Type::TriangleGreen,
    v2168::MapDecoration::Type::SmallSquareWhite,
    v2168::MapDecoration::Type::Mansion,
    v2168::MapDecoration::Type::Monument,
    v2168::MapDecoration::Type::NoDraw,
    v2168::MapDecoration::Type::VillageDesert,
    v2168::MapDecoration::Type::VillagePlains,
    v2168::MapDecoration::Type::VillageSavanna,
    v2168::MapDecoration::Type::VillageSnowy,
    v2168::MapDecoration::Type::VillageTaiga,
    v2168::MapDecoration::Type::JungleTemple,
    v2168::MapDecoration::Type::WitchHut,
    v2168::MapDecoration::Type::TrialChambers,
    v2168::MapDecoration::Type::Count,
}};

template <>
inline constexpr std::array<std::string_view, 26> names_v<v2168::MapDecoration::Type>{{
    "markerwhite",
    "markergreen",
    "markerred",
    "markerblue",
    "xwhite",
    "trianglered",
    "squarewhite",
    "markersign",
    "markerpink",
    "markerorange",
    "markeryellow",
    "markerteal",
    "trianglegreen",
    "smallsquarewhite",
    "mansion",
    "monument",
    "nodraw",
    "villagedesert",
    "villageplains",
    "villagesavanna",
    "villagesnowy",
    "villagetaiga",
    "jungletemple",
    "witchhut",
    "trialchambers",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<v2168::MapDecoration::Type>{"MapDecoration::Type"};

template <>
inline constexpr std::array<v2193::MapDecoration::Type, 31> values_v<v2193::MapDecoration::Type>{{
    v2193::MapDecoration::Type::MarkerWhite,
    v2193::MapDecoration::Type::MarkerGreen,
    v2193::MapDecoration::Type::MarkerRed,
    v2193::MapDecoration::Type::MarkerBlue,
    v2193::MapDecoration::Type::XWhite,
    v2193::MapDecoration::Type::TriangleRed,
    v2193::MapDecoration::Type::SquareWhite,
    v2193::MapDecoration::Type::MarkerSign,
    v2193::MapDecoration::Type::MarkerPink,
    v2193::MapDecoration::Type::MarkerOrange,
    v2193::MapDecoration::Type::MarkerYellow,
    v2193::MapDecoration::Type::MarkerTeal,
    v2193::MapDecoration::Type::TriangleGreen,
    v2193::MapDecoration::Type::SmallSquareWhite,
    v2193::MapDecoration::Type::Mansion,
    v2193::MapDecoration::Type::Monument,
    v2193::MapDecoration::Type::NoDraw,
    v2193::MapDecoration::Type::VillageDesert,
    v2193::MapDecoration::Type::VillagePlains,
    v2193::MapDecoration::Type::VillageSavanna,
    v2193::MapDecoration::Type::VillageSnowy,
    v2193::MapDecoration::Type::VillageTaiga,
    v2193::MapDecoration::Type::JungleTemple,
    v2193::MapDecoration::Type::WitchHut,
    v2193::MapDecoration::Type::TrialChambers,
    v2193::MapDecoration::Type::AbandonedCamp,
    v2193::MapDecoration::Type::BuriedAncientCity,
    v2193::MapDecoration::Type::BuriedMineshaft,
    v2193::MapDecoration::Type::DesertPyramid,
    v2193::MapDecoration::Type::WarmOceanRuins,
    v2193::MapDecoration::Type::Count,
}};

template <>
inline constexpr std::array<std::string_view, 31> names_v<v2193::MapDecoration::Type>{{
    "markerwhite",
    "markergreen",
    "markerred",
    "markerblue",
    "xwhite",
    "trianglered",
    "squarewhite",
    "markersign",
    "markerpink",
    "markerorange",
    "markeryellow",
    "markerteal",
    "trianglegreen",
    "smallsquarewhite",
    "mansion",
    "monument",
    "nodraw",
    "villagedesert",
    "villageplains",
    "villagesavanna",
    "villagesnowy",
    "villagetaiga",
    "jungletemple",
    "witchhut",
    "trialchambers",
    "abandonedcamp",
    "buriedancientcity",
    "buriedmineshaft",
    "desertpyramid",
    "warmoceanruins",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<v2193::MapDecoration::Type>{"MapDecoration::Type"};

template <>
inline constexpr std::array<base::ClientboundMapItemDataPacket::Type, 4> values_v<base::ClientboundMapItemDataPacket::Type>{{
    base::ClientboundMapItemDataPacket::Type::Invalid,
    base::ClientboundMapItemDataPacket::Type::TextureUpdate,
    base::ClientboundMapItemDataPacket::Type::DecorationUpdate,
    base::ClientboundMapItemDataPacket::Type::Creation,
}};

template <>
inline constexpr std::array<std::string_view, 4> names_v<base::ClientboundMapItemDataPacket::Type>{{
    "invalid",
    "textureupdate",
    "decorationupdate",
    "creation",
}};

template <>
inline constexpr std::string_view type_name_v<base::ClientboundMapItemDataPacket::Type>{"ClientboundMapItemDataPacket::Type"};

template <>
inline constexpr std::array<PhotoType, 3> values_v<PhotoType>{{
    PhotoType::Portfolio,
    PhotoType::PhotoItem,
    PhotoType::Book,
}};

template <>
inline constexpr std::array<std::string_view, 3> names_v<PhotoType>{{
    "portfolio",
    "photoitem",
    "book",
}};

template <>
inline constexpr std::string_view type_name_v<PhotoType>{"PhotoType"};

}  // namespace detail

namespace detail {

template <>
inline constexpr bool is_reflected_struct_v<base::MapItemTrackedActor::UniqueId> = true;

template <>
inline constexpr std::string_view struct_name_v<base::MapItemTrackedActor::UniqueId>{"MapItemTrackedActor::UniqueId"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<base::MapItemTrackedActor::UniqueId>{{
    "type",
    "key_entity_id",
    "key_block_pos",
}};

template <>
struct field_accessor<base::MapItemTrackedActor::UniqueId> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.type;
        }
        else if constexpr (I == 1) {
            return value.key_entity_id;
        }
        else {
            return value.key_block_pos;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::MapItemTrackedActor::UniqueId> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::MapItemTrackedActor::UniqueId>{"MapItemTrackedActor::UniqueId"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v944::MapItemTrackedActor::UniqueId>{{
    "type",
    "key_entity_id",
    "key_block_pos",
}};

template <>
struct field_accessor<v944::MapItemTrackedActor::UniqueId> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.type;
        }
        else if constexpr (I == 1) {
            return value.key_entity_id;
        }
        else {
            return value.key_block_pos;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::MapItemTrackedActor::UniqueId> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::MapItemTrackedActor::UniqueId>{"MapItemTrackedActor::UniqueId"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v2168::MapItemTrackedActor::UniqueId>{{
    "type",
    "key_entity_id",
    "key_block_pos",
}};

template <>
struct field_accessor<v2168::MapItemTrackedActor::UniqueId> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.type;
        }
        else if constexpr (I == 1) {
            return value.key_entity_id;
        }
        else {
            return value.key_block_pos;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::MapItemTrackedActor> = true;

template <>
inline constexpr std::string_view struct_name_v<base::MapItemTrackedActor>{"MapItemTrackedActor"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<base::MapItemTrackedActor>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<v944::MapItemTrackedActor> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::MapItemTrackedActor>{"MapItemTrackedActor"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<v944::MapItemTrackedActor>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<v2168::MapItemTrackedActor> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::MapItemTrackedActor>{"MapItemTrackedActor"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<v2168::MapItemTrackedActor>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<base::MapDecoration> = true;

template <>
inline constexpr std::string_view struct_name_v<base::MapDecoration>{"MapDecoration"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<base::MapDecoration>{{
    "image",
    "rotation",
    "x",
    "y",
    "label",
    "color",
}};

template <>
struct field_accessor<base::MapDecoration> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.image;
        }
        else if constexpr (I == 1) {
            return value.rotation;
        }
        else if constexpr (I == 2) {
            return value.x;
        }
        else if constexpr (I == 3) {
            return value.y;
        }
        else if constexpr (I == 4) {
            return value.label;
        }
        else {
            return value.color;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::MapDecoration> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::MapDecoration>{"MapDecoration"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<v2168::MapDecoration>{{
    "image",
    "rotation",
    "x",
    "y",
    "label",
    "color",
}};

template <>
struct field_accessor<v2168::MapDecoration> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.image;
        }
        else if constexpr (I == 1) {
            return value.rotation;
        }
        else if constexpr (I == 2) {
            return value.x;
        }
        else if constexpr (I == 3) {
            return value.y;
        }
        else if constexpr (I == 4) {
            return value.label;
        }
        else {
            return value.color;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2193::MapDecoration> = true;

template <>
inline constexpr std::string_view struct_name_v<v2193::MapDecoration>{"MapDecoration"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<v2193::MapDecoration>{{
    "image",
    "rotation",
    "x",
    "y",
    "label",
    "color",
}};

template <>
struct field_accessor<v2193::MapDecoration> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.image;
        }
        else if constexpr (I == 1) {
            return value.rotation;
        }
        else if constexpr (I == 2) {
            return value.x;
        }
        else if constexpr (I == 3) {
            return value.y;
        }
        else if constexpr (I == 4) {
            return value.label;
        }
        else {
            return value.color;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::ClientboundMapItemDataPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ClientboundMapItemDataPacket>{"ClientboundMapItemDataPacket"};

template <>
inline constexpr std::array<std::string_view, 14> field_names_v<base::ClientboundMapItemDataPacket>{{
    "map_id",
    "type",
    "dimension",
    "locked",
    "map_origin",
    "map_ids",
    "scale",
    "unique_ids",
    "decorations",
    "width",
    "height",
    "start_x",
    "start_y",
    "map_pixels",
}};

template <>
struct field_accessor<base::ClientboundMapItemDataPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.map_id;
        }
        else if constexpr (I == 1) {
            return value.type;
        }
        else if constexpr (I == 2) {
            return value.dimension;
        }
        else if constexpr (I == 3) {
            return value.locked;
        }
        else if constexpr (I == 4) {
            return value.map_origin;
        }
        else if constexpr (I == 5) {
            return value.map_ids;
        }
        else if constexpr (I == 6) {
            return value.scale;
        }
        else if constexpr (I == 7) {
            return value.unique_ids;
        }
        else if constexpr (I == 8) {
            return value.decorations;
        }
        else if constexpr (I == 9) {
            return value.width;
        }
        else if constexpr (I == 10) {
            return value.height;
        }
        else if constexpr (I == 11) {
            return value.start_x;
        }
        else if constexpr (I == 12) {
            return value.start_y;
        }
        else {
            return value.map_pixels;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::ClientboundMapItemDataPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::ClientboundMapItemDataPacket>{"ClientboundMapItemDataPacket"};

template <>
inline constexpr std::array<std::string_view, 14> field_names_v<v944::ClientboundMapItemDataPacket>{{
    "map_id",
    "type",
    "dimension",
    "locked",
    "map_origin",
    "map_ids",
    "scale",
    "unique_ids",
    "decorations",
    "width",
    "height",
    "start_x",
    "start_y",
    "map_pixels",
}};

template <>
struct field_accessor<v944::ClientboundMapItemDataPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.map_id;
        }
        else if constexpr (I == 1) {
            return value.type;
        }
        else if constexpr (I == 2) {
            return value.dimension;
        }
        else if constexpr (I == 3) {
            return value.locked;
        }
        else if constexpr (I == 4) {
            return value.map_origin;
        }
        else if constexpr (I == 5) {
            return value.map_ids;
        }
        else if constexpr (I == 6) {
            return value.scale;
        }
        else if constexpr (I == 7) {
            return value.unique_ids;
        }
        else if constexpr (I == 8) {
            return value.decorations;
        }
        else if constexpr (I == 9) {
            return value.width;
        }
        else if constexpr (I == 10) {
            return value.height;
        }
        else if constexpr (I == 11) {
            return value.start_x;
        }
        else if constexpr (I == 12) {
            return value.start_y;
        }
        else {
            return value.map_pixels;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ClientboundMapItemDataPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ClientboundMapItemDataPacket>{"ClientboundMapItemDataPacket"};

template <>
inline constexpr std::array<std::string_view, 13> field_names_v<v2168::ClientboundMapItemDataPacket>{{
    "map_id",
    "dimension",
    "locked",
    "map_origin",
    "creation_map_ids",
    "scale",
    "unique_ids",
    "decorations",
    "width",
    "height",
    "start_x",
    "start_y",
    "map_pixels",
}};

template <>
struct field_accessor<v2168::ClientboundMapItemDataPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.map_id;
        }
        else if constexpr (I == 1) {
            return value.dimension;
        }
        else if constexpr (I == 2) {
            return value.locked;
        }
        else if constexpr (I == 3) {
            return value.map_origin;
        }
        else if constexpr (I == 4) {
            return value.creation_map_ids;
        }
        else if constexpr (I == 5) {
            return value.scale;
        }
        else if constexpr (I == 6) {
            return value.unique_ids;
        }
        else if constexpr (I == 7) {
            return value.decorations;
        }
        else if constexpr (I == 8) {
            return value.width;
        }
        else if constexpr (I == 9) {
            return value.height;
        }
        else if constexpr (I == 10) {
            return value.start_x;
        }
        else if constexpr (I == 11) {
            return value.start_y;
        }
        else {
            return value.map_pixels;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2193::ClientboundMapItemDataPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2193::ClientboundMapItemDataPacket>{"ClientboundMapItemDataPacket"};

template <>
inline constexpr std::array<std::string_view, 13> field_names_v<v2193::ClientboundMapItemDataPacket>{{
    "map_id",
    "dimension",
    "locked",
    "map_origin",
    "creation_map_ids",
    "scale",
    "unique_ids",
    "decorations",
    "width",
    "height",
    "start_x",
    "start_y",
    "map_pixels",
}};

template <>
struct field_accessor<v2193::ClientboundMapItemDataPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.map_id;
        }
        else if constexpr (I == 1) {
            return value.dimension;
        }
        else if constexpr (I == 2) {
            return value.locked;
        }
        else if constexpr (I == 3) {
            return value.map_origin;
        }
        else if constexpr (I == 4) {
            return value.creation_map_ids;
        }
        else if constexpr (I == 5) {
            return value.scale;
        }
        else if constexpr (I == 6) {
            return value.unique_ids;
        }
        else if constexpr (I == 7) {
            return value.decorations;
        }
        else if constexpr (I == 8) {
            return value.width;
        }
        else if constexpr (I == 9) {
            return value.height;
        }
        else if constexpr (I == 10) {
            return value.start_x;
        }
        else if constexpr (I == 11) {
            return value.start_y;
        }
        else {
            return value.map_pixels;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<MapInfoRequestPacket::ClientPixelsProxy> = true;

template <>
inline constexpr std::string_view struct_name_v<MapInfoRequestPacket::ClientPixelsProxy>{"MapInfoRequestPacket::ClientPixelsProxy"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<MapInfoRequestPacket::ClientPixelsProxy>{{
    "pixel",
    "index",
}};

template <>
struct field_accessor<MapInfoRequestPacket::ClientPixelsProxy> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.pixel;
        }
        else {
            return value.index;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<MapInfoRequestPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<MapInfoRequestPacket>{"MapInfoRequestPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<MapInfoRequestPacket>{{
    "map_id",
    "client_pixels",
}};

template <>
struct field_accessor<MapInfoRequestPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.map_id;
        }
        else {
            return value.client_pixels;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<MapCreateLockedCopyPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<MapCreateLockedCopyPacket>{"MapCreateLockedCopyPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<MapCreateLockedCopyPacket>{{
    "original_map_id",
    "new_map_id",
}};

template <>
struct field_accessor<MapCreateLockedCopyPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.original_map_id;
        }
        else {
            return value.new_map_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<CreatePhotoPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<CreatePhotoPacket>{"CreatePhotoPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<CreatePhotoPacket>{{
    "id",
    "photo_name",
    "photo_item_name",
}};

template <>
struct field_accessor<CreatePhotoPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.id;
        }
        else if constexpr (I == 1) {
            return value.photo_name;
        }
        else {
            return value.photo_item_name;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<PhotoTransferPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<PhotoTransferPacket>{"PhotoTransferPacket"};

template <>
inline constexpr std::array<std::string_view, 7> field_names_v<PhotoTransferPacket>{{
    "photo_name",
    "photo_data",
    "book_id",
    "type",
    "source_type",
    "owner_id",
    "new_photo_name",
}};

template <>
struct field_accessor<PhotoTransferPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.photo_name;
        }
        else if constexpr (I == 1) {
            return value.photo_data;
        }
        else if constexpr (I == 2) {
            return value.book_id;
        }
        else if constexpr (I == 3) {
            return value.type;
        }
        else if constexpr (I == 4) {
            return value.source_type;
        }
        else if constexpr (I == 5) {
            return value.owner_id;
        }
        else {
            return value.new_photo_name;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v786::PlayerVideoCapturePacket::StartVideoCapture> = true;

template <>
inline constexpr std::string_view struct_name_v<v786::PlayerVideoCapturePacket::StartVideoCapture>{"PlayerVideoCapturePacket::StartVideoCapture"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v786::PlayerVideoCapturePacket::StartVideoCapture>{{
    "frame_rate",
    "file_prefix",
}};

template <>
struct field_accessor<v786::PlayerVideoCapturePacket::StartVideoCapture> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.frame_rate;
        }
        else {
            return value.file_prefix;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v786::PlayerVideoCapturePacket::StopVideoCapture> = true;

template <>
inline constexpr std::string_view struct_name_v<v786::PlayerVideoCapturePacket::StopVideoCapture>{"PlayerVideoCapturePacket::StopVideoCapture"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<v786::PlayerVideoCapturePacket::StopVideoCapture>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<v786::PlayerVideoCapturePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v786::PlayerVideoCapturePacket>{"PlayerVideoCapturePacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v786::PlayerVideoCapturePacket>{{
    "start_video_capture",
    "stop_video_capture",
}};

template <>
struct field_accessor<v786::PlayerVideoCapturePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.start_video_capture;
        }
        else {
            return value.stop_video_capture;
        }
    }
};

}  // namespace detail


template <>
struct Serializer<base::MapItemTrackedActor::UniqueId> {
    static void serialize(BinaryWriter &stream, const base::MapItemTrackedActor::UniqueId &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::MapItemTrackedActor::UniqueId, std::error_code>;
};

template <>
struct Serializer<v944::MapItemTrackedActor::UniqueId> {
    static void serialize(BinaryWriter &stream, const v944::MapItemTrackedActor::UniqueId &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::MapItemTrackedActor::UniqueId, std::error_code>;
};

template <>
struct Serializer<v2168::MapItemTrackedActor::UniqueId> {
    static void serialize(BinaryWriter &stream, const v2168::MapItemTrackedActor::UniqueId &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::MapItemTrackedActor::UniqueId, std::error_code>;
};

template <>
struct Serializer<base::MapDecoration> {
    static void serialize(BinaryWriter &stream, const base::MapDecoration &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::MapDecoration, std::error_code>;
};

template <>
struct Serializer<v2168::MapDecoration> {
    static void serialize(BinaryWriter &stream, const v2168::MapDecoration &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::MapDecoration, std::error_code>;
};

template <>
struct Serializer<v2193::MapDecoration> {
    static void serialize(BinaryWriter &stream, const v2193::MapDecoration &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::MapDecoration, std::error_code>;
};

template <>
struct Serializer<base::ClientboundMapItemDataPacket> {
    static void serialize(BinaryWriter &stream, const base::ClientboundMapItemDataPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ClientboundMapItemDataPacket, std::error_code>;
};

template <>
struct Serializer<v944::ClientboundMapItemDataPacket> {
    static void serialize(BinaryWriter &stream, const v944::ClientboundMapItemDataPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::ClientboundMapItemDataPacket, std::error_code>;
};

template <>
struct Serializer<v2168::ClientboundMapItemDataPacket> {
    static void serialize(BinaryWriter &stream, const v2168::ClientboundMapItemDataPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ClientboundMapItemDataPacket, std::error_code>;
};

template <>
struct Serializer<v2193::ClientboundMapItemDataPacket> {
    static void serialize(BinaryWriter &stream, const v2193::ClientboundMapItemDataPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::ClientboundMapItemDataPacket, std::error_code>;
};

template <>
struct Serializer<MapInfoRequestPacket::ClientPixelsProxy> {
    static void serialize(BinaryWriter &stream, const MapInfoRequestPacket::ClientPixelsProxy &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<MapInfoRequestPacket::ClientPixelsProxy, std::error_code>;
};

template <>
struct Serializer<MapInfoRequestPacket> {
    static void serialize(BinaryWriter &stream, const MapInfoRequestPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<MapInfoRequestPacket, std::error_code>;
};

template <>
struct Serializer<MapCreateLockedCopyPacket> {
    static void serialize(BinaryWriter &stream, const MapCreateLockedCopyPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<MapCreateLockedCopyPacket, std::error_code>;
};

template <>
struct Serializer<CreatePhotoPacket> {
    static void serialize(BinaryWriter &stream, const CreatePhotoPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<CreatePhotoPacket, std::error_code>;
};

template <>
struct Serializer<PhotoTransferPacket> {
    static void serialize(BinaryWriter &stream, const PhotoTransferPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<PhotoTransferPacket, std::error_code>;
};

template <>
struct Serializer<v786::PlayerVideoCapturePacket::StartVideoCapture> {
    static void serialize(BinaryWriter &stream, const v786::PlayerVideoCapturePacket::StartVideoCapture &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v786::PlayerVideoCapturePacket::StartVideoCapture, std::error_code>;
};

template <>
struct Serializer<v786::PlayerVideoCapturePacket::StopVideoCapture> {
    static void serialize(BinaryWriter &stream, const v786::PlayerVideoCapturePacket::StopVideoCapture &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v786::PlayerVideoCapturePacket::StopVideoCapture, std::error_code>;
};

template <>
struct Serializer<v786::PlayerVideoCapturePacket> {
    static void serialize(BinaryWriter &stream, const v786::PlayerVideoCapturePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v786::PlayerVideoCapturePacket, std::error_code>;
};
using MapItemTrackedActor = MapItemTrackedActor_<2225>;
using MapDecoration = MapDecoration_<2225>;
using ClientboundMapItemDataPacket = ClientboundMapItemDataPacket_<2225>;
using PlayerVideoCapturePacket = PlayerVideoCapturePacket_<2225>;

}  // namespace bedrock::protocol
