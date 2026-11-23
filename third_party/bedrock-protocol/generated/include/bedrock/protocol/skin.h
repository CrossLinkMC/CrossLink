#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <expected>
#include <map>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>

#include <bedrock/protocol/detail/reflect.hpp>
#include <bedrock/protocol/enum.hpp>
#include <bedrock/protocol/packet.hpp>
#include <bedrock/protocol/serializer.hpp>
#include <bedrock/protocol/stream.hpp>
#include <bedrock/protocol/uuid.hpp>

#include <bedrock/protocol/actor.h>
#include <bedrock/protocol/common.h>

namespace bedrock::protocol {

enum class ArmSizeType : std::uint8_t {
    Slim = 0,
    Wide = 1,
    Count = 2,
    Unknown = 3,
};

namespace legacy {

enum class PieceType : std::uint32_t {
    Skeleton = 1,
    Body = 2,
    Skin = 3,
    Bottom = 4,
    Feet = 5,
    Dress = 6,
    Top = 7,
    HighPants = 8,
    Hands = 9,
    Outerwear = 10,
    FacialHair = 11,
    Mouth = 12,
    Eyes = 13,
    Hair = 14,
    Hood = 15,
    Back = 16,
    FaceAccessory = 17,
    Head = 18,
    Legs = 19,
    LeftLeg = 20,
    RightLeg = 21,
    Arms = 22,
    LeftArm = 23,
    RightArm = 24,
    Capes = 25,
    ClassicSkin = 26,
    Emote = 27,
};

}  // namespace legacy

enum class AnimatedTextureType : std::uint32_t {
    None = 0,
    Face = 1,
    Body32x32 = 2,
    Body128x128 = 3,
};

enum class AnimationExpression : std::uint32_t {
    Linear = 0,
    Blinking = 1,
};

enum class TrustedSkinFlag : std::int8_t {
    Unset = 0,
    False = 1,
    True = 2,
};

struct SkinImage {
    std::uint32_t width{};
    std::uint32_t height{};
    std::string image_bytes{};
};

struct AnimatedImageData {
    SkinImage image{};
    AnimatedTextureType type{};
    float frames{};
    AnimationExpression animation_expression{};
};

namespace legacy {

struct AnimatedImageData {
    std::uint32_t image_width{};
    std::uint32_t image_height{};
    std::string image_bytes{};
    AnimatedTextureType type{};
    float frames{};
    AnimationExpression animation_expression{};
};

struct SerializedPersonaPieceHandle {
    std::string piece_id{};
    PieceType piece_type{};
    std::string pack_id{};
    bool is_default_piece{};
    std::string product_id{};
};

}  // namespace legacy

struct TintMapColor {
    std::array<Color, 4> colors{};
};

namespace legacy {

struct TintMapColor {
    PieceType piece_type{};
    std::vector<std::string> colors{};
};

struct SerializedSkinRef {
    std::string id{};
    std::string play_fab_id{};
    std::string resource_patch{};
    std::uint32_t image_width{};
    std::uint32_t image_height{};
    std::string image_bytes{};
    std::vector<AnimatedImageData> animated_image_data{};
    std::uint32_t cape_image_width{};
    std::uint32_t cape_image_height{};
    std::string cape_image_bytes{};
    std::string geometry_data{};
    std::string geometry_data_min_engine_version{};
    std::string animation_data{};
    std::string cape_id{};
    std::string full_id{};
    ArmSizeType arm_size{};
    std::string skin_color{};
    std::vector<SerializedPersonaPieceHandle> persona_pieces{};
    std::vector<TintMapColor> piece_tint_colors{};
    bool is_premium{};
    bool is_persona{};
    bool is_persona_cape_on_classic_skin{};
    bool is_primary_user{};
    bool overrides_player_appearance{};
};

}  // namespace legacy

namespace EmotePacket_nested {

enum class Flags : std::uint8_t {
    ServerSide = 1,
    MuteEmoteChat = 2,
};

}  // namespace EmotePacket_nested

struct EmotePacket {
    using Flags = EmotePacket_nested::Flags;

    static constexpr int Id = 138;
    ActorRuntimeID runtime_id{};
    std::string piece_id{};
    std::uint32_t emote_ticks{};
    std::string xuid{};
    std::string platform_id{};
    std::uint8_t flags{};
};

struct EmoteListPacket {
    static constexpr int Id = 152;
    ActorRuntimeID runtime_id{};
    std::vector<UUID> emote_piece_ids{};
};

namespace base {

enum class PieceType : std::uint32_t {
    Unknown = 0,
    Skeleton = 1,
    Body = 2,
    Skin = 3,
    Bottom = 4,
    Feet = 5,
    Dress = 6,
    Top = 7,
    HighPants = 8,
    Hands = 9,
    Outerwear = 10,
    FacialHair = 11,
    Mouth = 12,
    Eyes = 13,
    Hair = 14,
    Hood = 15,
    Back = 16,
    FaceAccessory = 17,
    Head = 18,
    Legs = 19,
    LeftLeg = 20,
    RightLeg = 21,
    Arms = 22,
    LeftArm = 23,
    RightArm = 24,
    Capes = 25,
    ClassicSkin = 26,
    Emote = 27,
    Unsupported = 28,
    Count = 29,
};

struct SerializedPersonaPieceHandle {
    std::string piece_id{};
    base::PieceType piece_type{};
    UUID pack_id{};
    bool is_default_piece{};
    std::string product_id{};
};

struct SerializedSkinRef {
    std::string id{};
    std::string play_fab_id{};
    std::string resource_patch{};
    SkinImage image_data{};
    std::vector<AnimatedImageData> animated_image_data{};
    SkinImage cape_image_data{};
    std::string geometry_data{};
    std::string geometry_data_min_engine_version{};
    std::string animation_data{};
    std::string cape_id{};
    std::string full_id{};
    ArmSizeType arm_size{};
    Color skin_color{};
    std::vector<base::SerializedPersonaPieceHandle> persona_pieces{};
    std::map<base::PieceType, TintMapColor> piece_tint_colors{};
    bool is_premium{};
    bool is_persona{};
    bool is_persona_cape_on_classic_skin{};
    bool is_primary_user{};
    bool overrides_player_appearance{};
    TrustedSkinFlag trusted_skin_flag{};
};

struct PlayerSkinPacket {
    static constexpr int Id = 93;
    UUID uuid{};
    legacy::SerializedSkinRef skin{};
    std::string localized_new_skin_name{};
    std::string localized_old_skin_name{};
    bool trusted_skin{};
};

}  // namespace base

namespace v766 {

using PieceType = base::PieceType;

using SerializedPersonaPieceHandle = base::SerializedPersonaPieceHandle;

using SerializedSkinRef = base::SerializedSkinRef;

using PlayerSkinPacket = base::PlayerSkinPacket;

}  // namespace v766

namespace v776 {

using PieceType = base::PieceType;

using SerializedPersonaPieceHandle = base::SerializedPersonaPieceHandle;

using SerializedSkinRef = base::SerializedSkinRef;

using PlayerSkinPacket = base::PlayerSkinPacket;

}  // namespace v776

namespace v786 {

using PieceType = base::PieceType;

using SerializedPersonaPieceHandle = base::SerializedPersonaPieceHandle;

using SerializedSkinRef = base::SerializedSkinRef;

using PlayerSkinPacket = base::PlayerSkinPacket;

}  // namespace v786

namespace v800 {

using PieceType = base::PieceType;

using SerializedPersonaPieceHandle = base::SerializedPersonaPieceHandle;

using SerializedSkinRef = base::SerializedSkinRef;

using PlayerSkinPacket = base::PlayerSkinPacket;

}  // namespace v800

namespace v818 {

using PieceType = base::PieceType;

using SerializedPersonaPieceHandle = base::SerializedPersonaPieceHandle;

using SerializedSkinRef = base::SerializedSkinRef;

using PlayerSkinPacket = base::PlayerSkinPacket;

}  // namespace v818

namespace v827 {

using PieceType = base::PieceType;

using SerializedPersonaPieceHandle = base::SerializedPersonaPieceHandle;

using SerializedSkinRef = base::SerializedSkinRef;

using PlayerSkinPacket = base::PlayerSkinPacket;

}  // namespace v827

namespace v844 {

using PieceType = base::PieceType;

using SerializedPersonaPieceHandle = base::SerializedPersonaPieceHandle;

using SerializedSkinRef = base::SerializedSkinRef;

using PlayerSkinPacket = base::PlayerSkinPacket;

}  // namespace v844

namespace v859 {

using PieceType = base::PieceType;

using SerializedPersonaPieceHandle = base::SerializedPersonaPieceHandle;

using SerializedSkinRef = base::SerializedSkinRef;

using PlayerSkinPacket = base::PlayerSkinPacket;

}  // namespace v859

namespace v898 {

using PieceType = base::PieceType;

using SerializedPersonaPieceHandle = base::SerializedPersonaPieceHandle;

using SerializedSkinRef = base::SerializedSkinRef;

using PlayerSkinPacket = base::PlayerSkinPacket;

}  // namespace v898

namespace v924 {

using PieceType = base::PieceType;

using SerializedPersonaPieceHandle = base::SerializedPersonaPieceHandle;

using SerializedSkinRef = base::SerializedSkinRef;

using PlayerSkinPacket = base::PlayerSkinPacket;

}  // namespace v924

namespace v944 {

using PieceType = base::PieceType;

using SerializedPersonaPieceHandle = base::SerializedPersonaPieceHandle;

using SerializedSkinRef = base::SerializedSkinRef;

struct PlayerSkinPacket {
    static constexpr int Id = 93;
    UUID uuid{};
    base::SerializedSkinRef skin{};
    std::string localized_new_skin_name{};
    std::string localized_old_skin_name{};
};

}  // namespace v944

namespace v975 {

using PieceType = base::PieceType;

using SerializedPersonaPieceHandle = base::SerializedPersonaPieceHandle;

using SerializedSkinRef = base::SerializedSkinRef;

using PlayerSkinPacket = v944::PlayerSkinPacket;

}  // namespace v975

namespace v2168 {

using PieceType = base::PieceType;

using SerializedPersonaPieceHandle = base::SerializedPersonaPieceHandle;

struct SerializedSkinRef {
    std::string id{};
    std::string play_fab_id{};
    std::string resource_patch{};
    SkinImage image_data{};
    std::vector<AnimatedImageData> animated_image_data{};
    SkinImage cape_image_data{};
    std::string geometry_data{};
    std::string geometry_data_min_engine_version{};
    std::string animation_data{};
    std::string cape_id{};
    std::string full_id{};
    ArmSizeType arm_size{};
    Color skin_color{};
    std::vector<base::SerializedPersonaPieceHandle> persona_pieces{};
    std::map<base::PieceType, TintMapColor> piece_tint_colors{};
    bool is_premium{};
    bool is_persona{};
    bool is_persona_cape_on_classic_skin{};
    bool is_primary_user{};
    bool overrides_player_appearance{};
    TrustedSkinFlag trusted_skin_flag{};
    std::string profile_hash{};
};

struct PlayerSkinPacket {
    static constexpr int Id = 93;
    UUID uuid{};
    v2168::SerializedSkinRef skin{};
    std::string localized_new_skin_name{};
    std::string localized_old_skin_name{};
};

}  // namespace v2168

namespace v2225 {

enum class PieceType : std::uint32_t {
    Unknown = 0,
    Skeleton = 1,
    Body = 2,
    Skin = 3,
    Bottom = 4,
    Feet = 5,
    Dress = 6,
    Top = 7,
    HighPants = 8,
    Hands = 9,
    Outerwear = 10,
    FacialHair = 11,
    Mouth = 12,
    Eyes = 13,
    Hair = 14,
    Hood = 15,
    Back = 16,
    FaceAccessory = 17,
    Head = 18,
    Legs = 19,
    LeftLeg = 20,
    RightLeg = 21,
    Arms = 22,
    LeftArm = 23,
    RightArm = 24,
    Capes = 25,
    ClassicSkin = 26,
    Emote = 27,
    Coco = 28,
    Unsupported = 29,
    Count = 30,
};

struct SerializedPersonaPieceHandle {
    std::string piece_id{};
    v2225::PieceType piece_type{};
    UUID pack_id{};
    bool is_default_piece{};
    std::string product_id{};
};

struct SerializedSkinRef {
    std::string id{};
    std::string resource_patch{};
    SkinImage image_data{};
    std::vector<AnimatedImageData> animated_image_data{};
    SkinImage cape_image_data{};
    std::string geometry_data{};
    std::string geometry_data_min_engine_version{};
    std::string animation_data{};
    std::string cape_id{};
    std::string full_id{};
    ArmSizeType arm_size{};
    Color skin_color{};
    std::vector<v2225::SerializedPersonaPieceHandle> persona_pieces{};
    std::map<v2225::PieceType, TintMapColor> piece_tint_colors{};
    bool is_premium{};
    bool is_persona{};
    bool is_persona_cape_on_classic_skin{};
    bool is_primary_user{};
    bool overrides_player_appearance{};
    TrustedSkinFlag trusted_skin_flag{};
    std::string profile_hash{};
};

struct PlayerSkinPacket {
    static constexpr int Id = 93;
    UUID uuid{};
    v2225::SerializedSkinRef skin{};
    std::string localized_new_skin_name{};
    std::string localized_old_skin_name{};
};

}  // namespace v2225

namespace detail {

template <int V>
struct PieceType_;

template <int V> requires (V < 2225)
struct PieceType_<V> { using type = base::PieceType; };

template <int V> requires (V >= 2225)
struct PieceType_<V> { using type = v2225::PieceType; };

template <int V>
struct SerializedPersonaPieceHandle_;

template <int V> requires (V < 2225)
struct SerializedPersonaPieceHandle_<V> { using type = base::SerializedPersonaPieceHandle; };

template <int V> requires (V >= 2225)
struct SerializedPersonaPieceHandle_<V> { using type = v2225::SerializedPersonaPieceHandle; };

template <int V>
struct SerializedSkinRef_;

template <int V> requires (V < 2168)
struct SerializedSkinRef_<V> { using type = base::SerializedSkinRef; };

template <int V> requires (V >= 2168 && V < 2225)
struct SerializedSkinRef_<V> { using type = v2168::SerializedSkinRef; };

template <int V> requires (V >= 2225)
struct SerializedSkinRef_<V> { using type = v2225::SerializedSkinRef; };

template <int V>
struct PlayerSkinPacket_;

template <int V> requires (V < 944)
struct PlayerSkinPacket_<V> { using type = base::PlayerSkinPacket; };

template <int V> requires (V >= 944 && V < 2168)
struct PlayerSkinPacket_<V> { using type = v944::PlayerSkinPacket; };

template <int V> requires (V >= 2168 && V < 2225)
struct PlayerSkinPacket_<V> { using type = v2168::PlayerSkinPacket; };

template <int V> requires (V >= 2225)
struct PlayerSkinPacket_<V> { using type = v2225::PlayerSkinPacket; };

}  // namespace detail

template <int V> using PieceType_ = typename detail::PieceType_<V>::type;
template <int V> using SerializedPersonaPieceHandle_ = typename detail::SerializedPersonaPieceHandle_<V>::type;
template <int V> using SerializedSkinRef_ = typename detail::SerializedSkinRef_<V>::type;
template <int V> using PlayerSkinPacket_ = typename detail::PlayerSkinPacket_<V>::type;

template <int V>
struct packet_of<V, 93> { using type = PlayerSkinPacket_<V>; };

template <int V>
struct packet_of<V, 138> { using type = EmotePacket; };

template <int V>
struct packet_of<V, 152> { using type = EmoteListPacket; };

namespace detail {

template <>
inline constexpr std::array<ArmSizeType, 4> values_v<ArmSizeType>{{
    ArmSizeType::Slim,
    ArmSizeType::Wide,
    ArmSizeType::Count,
    ArmSizeType::Unknown,
}};

template <>
inline constexpr std::array<std::string_view, 4> names_v<ArmSizeType>{{
    "slim",
    "wide",
    "count",
    "unknown",
}};

template <>
inline constexpr std::string_view type_name_v<ArmSizeType>{"ArmSizeType"};

template <>
inline constexpr std::array<base::PieceType, 30> values_v<base::PieceType>{{
    base::PieceType::Unknown,
    base::PieceType::Skeleton,
    base::PieceType::Body,
    base::PieceType::Skin,
    base::PieceType::Bottom,
    base::PieceType::Feet,
    base::PieceType::Dress,
    base::PieceType::Top,
    base::PieceType::HighPants,
    base::PieceType::Hands,
    base::PieceType::Outerwear,
    base::PieceType::FacialHair,
    base::PieceType::Mouth,
    base::PieceType::Eyes,
    base::PieceType::Hair,
    base::PieceType::Hood,
    base::PieceType::Back,
    base::PieceType::FaceAccessory,
    base::PieceType::Head,
    base::PieceType::Legs,
    base::PieceType::LeftLeg,
    base::PieceType::RightLeg,
    base::PieceType::Arms,
    base::PieceType::LeftArm,
    base::PieceType::RightArm,
    base::PieceType::Capes,
    base::PieceType::ClassicSkin,
    base::PieceType::Emote,
    base::PieceType::Unsupported,
    base::PieceType::Count,
}};

template <>
inline constexpr std::array<std::string_view, 30> names_v<base::PieceType>{{
    "unknown",
    "skeleton",
    "body",
    "skin",
    "bottom",
    "feet",
    "dress",
    "top",
    "high_pants",
    "hands",
    "outerwear",
    "facialhair",
    "mouth",
    "eyes",
    "hair",
    "hood",
    "back",
    "faceaccessory",
    "head",
    "legs",
    "leftleg",
    "rightleg",
    "arms",
    "leftarm",
    "rightarm",
    "capes",
    "classicskin",
    "emote",
    "unsupported",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<base::PieceType>{"PieceType"};

template <>
inline constexpr std::array<v2225::PieceType, 31> values_v<v2225::PieceType>{{
    v2225::PieceType::Unknown,
    v2225::PieceType::Skeleton,
    v2225::PieceType::Body,
    v2225::PieceType::Skin,
    v2225::PieceType::Bottom,
    v2225::PieceType::Feet,
    v2225::PieceType::Dress,
    v2225::PieceType::Top,
    v2225::PieceType::HighPants,
    v2225::PieceType::Hands,
    v2225::PieceType::Outerwear,
    v2225::PieceType::FacialHair,
    v2225::PieceType::Mouth,
    v2225::PieceType::Eyes,
    v2225::PieceType::Hair,
    v2225::PieceType::Hood,
    v2225::PieceType::Back,
    v2225::PieceType::FaceAccessory,
    v2225::PieceType::Head,
    v2225::PieceType::Legs,
    v2225::PieceType::LeftLeg,
    v2225::PieceType::RightLeg,
    v2225::PieceType::Arms,
    v2225::PieceType::LeftArm,
    v2225::PieceType::RightArm,
    v2225::PieceType::Capes,
    v2225::PieceType::ClassicSkin,
    v2225::PieceType::Emote,
    v2225::PieceType::Coco,
    v2225::PieceType::Unsupported,
    v2225::PieceType::Count,
}};

template <>
inline constexpr std::array<std::string_view, 31> names_v<v2225::PieceType>{{
    "unknown",
    "skeleton",
    "body",
    "skin",
    "bottom",
    "feet",
    "dress",
    "top",
    "high_pants",
    "hands",
    "outerwear",
    "facialhair",
    "mouth",
    "eyes",
    "hair",
    "hood",
    "back",
    "faceaccessory",
    "head",
    "legs",
    "leftleg",
    "rightleg",
    "arms",
    "leftarm",
    "rightarm",
    "capes",
    "classicskin",
    "emote",
    "coco",
    "unsupported",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<v2225::PieceType>{"PieceType"};

template <>
inline constexpr std::array<legacy::PieceType, 27> values_v<legacy::PieceType>{{
    legacy::PieceType::Skeleton,
    legacy::PieceType::Body,
    legacy::PieceType::Skin,
    legacy::PieceType::Bottom,
    legacy::PieceType::Feet,
    legacy::PieceType::Dress,
    legacy::PieceType::Top,
    legacy::PieceType::HighPants,
    legacy::PieceType::Hands,
    legacy::PieceType::Outerwear,
    legacy::PieceType::FacialHair,
    legacy::PieceType::Mouth,
    legacy::PieceType::Eyes,
    legacy::PieceType::Hair,
    legacy::PieceType::Hood,
    legacy::PieceType::Back,
    legacy::PieceType::FaceAccessory,
    legacy::PieceType::Head,
    legacy::PieceType::Legs,
    legacy::PieceType::LeftLeg,
    legacy::PieceType::RightLeg,
    legacy::PieceType::Arms,
    legacy::PieceType::LeftArm,
    legacy::PieceType::RightArm,
    legacy::PieceType::Capes,
    legacy::PieceType::ClassicSkin,
    legacy::PieceType::Emote,
}};

template <>
inline constexpr std::array<std::string_view, 27> names_v<legacy::PieceType>{{
    "persona_skeleton",
    "persona_body",
    "persona_skin",
    "persona_bottom",
    "persona_feet",
    "persona_dress",
    "persona_top",
    "persona_high_pants",
    "persona_hand",
    "persona_outerwear",
    "persona_facial_hair",
    "persona_mouth",
    "persona_eyes",
    "persona_hair",
    "persona_hood",
    "persona_back",
    "persona_face_accessory",
    "persona_head",
    "persona_legs",
    "persona_left_leg",
    "persona_right_leg",
    "persona_arms",
    "persona_left_arm",
    "persona_right_arm",
    "persona_capes",
    "persona_classic_skin",
    "persona_emote",
}};

template <>
inline constexpr std::string_view type_name_v<legacy::PieceType>{"PieceType"};

template <>
inline constexpr std::array<AnimatedTextureType, 4> values_v<AnimatedTextureType>{{
    AnimatedTextureType::None,
    AnimatedTextureType::Face,
    AnimatedTextureType::Body32x32,
    AnimatedTextureType::Body128x128,
}};

template <>
inline constexpr std::array<std::string_view, 4> names_v<AnimatedTextureType>{{
    "none",
    "face",
    "body32x32",
    "body128x128",
}};

template <>
inline constexpr std::string_view type_name_v<AnimatedTextureType>{"AnimatedTextureType"};

template <>
inline constexpr std::array<AnimationExpression, 2> values_v<AnimationExpression>{{
    AnimationExpression::Linear,
    AnimationExpression::Blinking,
}};

template <>
inline constexpr std::array<std::string_view, 2> names_v<AnimationExpression>{{
    "linear",
    "blinking",
}};

template <>
inline constexpr std::string_view type_name_v<AnimationExpression>{"AnimationExpression"};

template <>
inline constexpr std::array<TrustedSkinFlag, 3> values_v<TrustedSkinFlag>{{
    TrustedSkinFlag::Unset,
    TrustedSkinFlag::False,
    TrustedSkinFlag::True,
}};

template <>
inline constexpr std::array<std::string_view, 3> names_v<TrustedSkinFlag>{{
    "unset",
    "false",
    "true",
}};

template <>
inline constexpr std::string_view type_name_v<TrustedSkinFlag>{"TrustedSkinFlag"};

template <>
inline constexpr std::array<EmotePacket::Flags, 2> values_v<EmotePacket::Flags>{{
    EmotePacket::Flags::ServerSide,
    EmotePacket::Flags::MuteEmoteChat,
}};

template <>
inline constexpr std::array<std::string_view, 2> names_v<EmotePacket::Flags>{{
    "serverside",
    "muteemotechat",
}};

template <>
inline constexpr std::string_view type_name_v<EmotePacket::Flags>{"EmotePacket::Flags"};

}  // namespace detail

namespace detail {

template <>
inline constexpr bool is_reflected_struct_v<SkinImage> = true;

template <>
inline constexpr std::string_view struct_name_v<SkinImage>{"SkinImage"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<SkinImage>{{
    "width",
    "height",
    "image_bytes",
}};

template <>
struct field_accessor<SkinImage> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.width;
        }
        else if constexpr (I == 1) {
            return value.height;
        }
        else {
            return value.image_bytes;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<AnimatedImageData> = true;

template <>
inline constexpr std::string_view struct_name_v<AnimatedImageData>{"AnimatedImageData"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<AnimatedImageData>{{
    "image",
    "type",
    "frames",
    "animation_expression",
}};

template <>
struct field_accessor<AnimatedImageData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.image;
        }
        else if constexpr (I == 1) {
            return value.type;
        }
        else if constexpr (I == 2) {
            return value.frames;
        }
        else {
            return value.animation_expression;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<legacy::AnimatedImageData> = true;

template <>
inline constexpr std::string_view struct_name_v<legacy::AnimatedImageData>{"AnimatedImageData"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<legacy::AnimatedImageData>{{
    "image_width",
    "image_height",
    "image_bytes",
    "type",
    "frames",
    "animation_expression",
}};

template <>
struct field_accessor<legacy::AnimatedImageData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.image_width;
        }
        else if constexpr (I == 1) {
            return value.image_height;
        }
        else if constexpr (I == 2) {
            return value.image_bytes;
        }
        else if constexpr (I == 3) {
            return value.type;
        }
        else if constexpr (I == 4) {
            return value.frames;
        }
        else {
            return value.animation_expression;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::SerializedPersonaPieceHandle> = true;

template <>
inline constexpr std::string_view struct_name_v<base::SerializedPersonaPieceHandle>{"SerializedPersonaPieceHandle"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<base::SerializedPersonaPieceHandle>{{
    "piece_id",
    "piece_type",
    "pack_id",
    "is_default_piece",
    "product_id",
}};

template <>
struct field_accessor<base::SerializedPersonaPieceHandle> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.piece_id;
        }
        else if constexpr (I == 1) {
            return value.piece_type;
        }
        else if constexpr (I == 2) {
            return value.pack_id;
        }
        else if constexpr (I == 3) {
            return value.is_default_piece;
        }
        else {
            return value.product_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::SerializedPersonaPieceHandle> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::SerializedPersonaPieceHandle>{"SerializedPersonaPieceHandle"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v2225::SerializedPersonaPieceHandle>{{
    "piece_id",
    "piece_type",
    "pack_id",
    "is_default_piece",
    "product_id",
}};

template <>
struct field_accessor<v2225::SerializedPersonaPieceHandle> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.piece_id;
        }
        else if constexpr (I == 1) {
            return value.piece_type;
        }
        else if constexpr (I == 2) {
            return value.pack_id;
        }
        else if constexpr (I == 3) {
            return value.is_default_piece;
        }
        else {
            return value.product_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<legacy::SerializedPersonaPieceHandle> = true;

template <>
inline constexpr std::string_view struct_name_v<legacy::SerializedPersonaPieceHandle>{"SerializedPersonaPieceHandle"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<legacy::SerializedPersonaPieceHandle>{{
    "piece_id",
    "piece_type",
    "pack_id",
    "is_default_piece",
    "product_id",
}};

template <>
struct field_accessor<legacy::SerializedPersonaPieceHandle> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.piece_id;
        }
        else if constexpr (I == 1) {
            return value.piece_type;
        }
        else if constexpr (I == 2) {
            return value.pack_id;
        }
        else if constexpr (I == 3) {
            return value.is_default_piece;
        }
        else {
            return value.product_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<TintMapColor> = true;

template <>
inline constexpr std::string_view struct_name_v<TintMapColor>{"TintMapColor"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<TintMapColor>{{
    "colors",
}};

template <>
struct field_accessor<TintMapColor> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.colors;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<legacy::TintMapColor> = true;

template <>
inline constexpr std::string_view struct_name_v<legacy::TintMapColor>{"TintMapColor"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<legacy::TintMapColor>{{
    "piece_type",
    "colors",
}};

template <>
struct field_accessor<legacy::TintMapColor> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.piece_type;
        }
        else {
            return value.colors;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<legacy::SerializedSkinRef> = true;

template <>
inline constexpr std::string_view struct_name_v<legacy::SerializedSkinRef>{"SerializedSkinRef"};

template <>
inline constexpr std::array<std::string_view, 24> field_names_v<legacy::SerializedSkinRef>{{
    "id",
    "play_fab_id",
    "resource_patch",
    "image_width",
    "image_height",
    "image_bytes",
    "animated_image_data",
    "cape_image_width",
    "cape_image_height",
    "cape_image_bytes",
    "geometry_data",
    "geometry_data_min_engine_version",
    "animation_data",
    "cape_id",
    "full_id",
    "arm_size",
    "skin_color",
    "persona_pieces",
    "piece_tint_colors",
    "is_premium",
    "is_persona",
    "is_persona_cape_on_classic_skin",
    "is_primary_user",
    "overrides_player_appearance",
}};

template <>
struct field_accessor<legacy::SerializedSkinRef> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.id;
        }
        else if constexpr (I == 1) {
            return value.play_fab_id;
        }
        else if constexpr (I == 2) {
            return value.resource_patch;
        }
        else if constexpr (I == 3) {
            return value.image_width;
        }
        else if constexpr (I == 4) {
            return value.image_height;
        }
        else if constexpr (I == 5) {
            return value.image_bytes;
        }
        else if constexpr (I == 6) {
            return value.animated_image_data;
        }
        else if constexpr (I == 7) {
            return value.cape_image_width;
        }
        else if constexpr (I == 8) {
            return value.cape_image_height;
        }
        else if constexpr (I == 9) {
            return value.cape_image_bytes;
        }
        else if constexpr (I == 10) {
            return value.geometry_data;
        }
        else if constexpr (I == 11) {
            return value.geometry_data_min_engine_version;
        }
        else if constexpr (I == 12) {
            return value.animation_data;
        }
        else if constexpr (I == 13) {
            return value.cape_id;
        }
        else if constexpr (I == 14) {
            return value.full_id;
        }
        else if constexpr (I == 15) {
            return value.arm_size;
        }
        else if constexpr (I == 16) {
            return value.skin_color;
        }
        else if constexpr (I == 17) {
            return value.persona_pieces;
        }
        else if constexpr (I == 18) {
            return value.piece_tint_colors;
        }
        else if constexpr (I == 19) {
            return value.is_premium;
        }
        else if constexpr (I == 20) {
            return value.is_persona;
        }
        else if constexpr (I == 21) {
            return value.is_persona_cape_on_classic_skin;
        }
        else if constexpr (I == 22) {
            return value.is_primary_user;
        }
        else {
            return value.overrides_player_appearance;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::SerializedSkinRef> = true;

template <>
inline constexpr std::string_view struct_name_v<base::SerializedSkinRef>{"SerializedSkinRef"};

template <>
inline constexpr std::array<std::string_view, 21> field_names_v<base::SerializedSkinRef>{{
    "id",
    "play_fab_id",
    "resource_patch",
    "image_data",
    "animated_image_data",
    "cape_image_data",
    "geometry_data",
    "geometry_data_min_engine_version",
    "animation_data",
    "cape_id",
    "full_id",
    "arm_size",
    "skin_color",
    "persona_pieces",
    "piece_tint_colors",
    "is_premium",
    "is_persona",
    "is_persona_cape_on_classic_skin",
    "is_primary_user",
    "overrides_player_appearance",
    "trusted_skin_flag",
}};

template <>
struct field_accessor<base::SerializedSkinRef> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.id;
        }
        else if constexpr (I == 1) {
            return value.play_fab_id;
        }
        else if constexpr (I == 2) {
            return value.resource_patch;
        }
        else if constexpr (I == 3) {
            return value.image_data;
        }
        else if constexpr (I == 4) {
            return value.animated_image_data;
        }
        else if constexpr (I == 5) {
            return value.cape_image_data;
        }
        else if constexpr (I == 6) {
            return value.geometry_data;
        }
        else if constexpr (I == 7) {
            return value.geometry_data_min_engine_version;
        }
        else if constexpr (I == 8) {
            return value.animation_data;
        }
        else if constexpr (I == 9) {
            return value.cape_id;
        }
        else if constexpr (I == 10) {
            return value.full_id;
        }
        else if constexpr (I == 11) {
            return value.arm_size;
        }
        else if constexpr (I == 12) {
            return value.skin_color;
        }
        else if constexpr (I == 13) {
            return value.persona_pieces;
        }
        else if constexpr (I == 14) {
            return value.piece_tint_colors;
        }
        else if constexpr (I == 15) {
            return value.is_premium;
        }
        else if constexpr (I == 16) {
            return value.is_persona;
        }
        else if constexpr (I == 17) {
            return value.is_persona_cape_on_classic_skin;
        }
        else if constexpr (I == 18) {
            return value.is_primary_user;
        }
        else if constexpr (I == 19) {
            return value.overrides_player_appearance;
        }
        else {
            return value.trusted_skin_flag;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::SerializedSkinRef> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::SerializedSkinRef>{"SerializedSkinRef"};

template <>
inline constexpr std::array<std::string_view, 22> field_names_v<v2168::SerializedSkinRef>{{
    "id",
    "play_fab_id",
    "resource_patch",
    "image_data",
    "animated_image_data",
    "cape_image_data",
    "geometry_data",
    "geometry_data_min_engine_version",
    "animation_data",
    "cape_id",
    "full_id",
    "arm_size",
    "skin_color",
    "persona_pieces",
    "piece_tint_colors",
    "is_premium",
    "is_persona",
    "is_persona_cape_on_classic_skin",
    "is_primary_user",
    "overrides_player_appearance",
    "trusted_skin_flag",
    "profile_hash",
}};

template <>
struct field_accessor<v2168::SerializedSkinRef> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.id;
        }
        else if constexpr (I == 1) {
            return value.play_fab_id;
        }
        else if constexpr (I == 2) {
            return value.resource_patch;
        }
        else if constexpr (I == 3) {
            return value.image_data;
        }
        else if constexpr (I == 4) {
            return value.animated_image_data;
        }
        else if constexpr (I == 5) {
            return value.cape_image_data;
        }
        else if constexpr (I == 6) {
            return value.geometry_data;
        }
        else if constexpr (I == 7) {
            return value.geometry_data_min_engine_version;
        }
        else if constexpr (I == 8) {
            return value.animation_data;
        }
        else if constexpr (I == 9) {
            return value.cape_id;
        }
        else if constexpr (I == 10) {
            return value.full_id;
        }
        else if constexpr (I == 11) {
            return value.arm_size;
        }
        else if constexpr (I == 12) {
            return value.skin_color;
        }
        else if constexpr (I == 13) {
            return value.persona_pieces;
        }
        else if constexpr (I == 14) {
            return value.piece_tint_colors;
        }
        else if constexpr (I == 15) {
            return value.is_premium;
        }
        else if constexpr (I == 16) {
            return value.is_persona;
        }
        else if constexpr (I == 17) {
            return value.is_persona_cape_on_classic_skin;
        }
        else if constexpr (I == 18) {
            return value.is_primary_user;
        }
        else if constexpr (I == 19) {
            return value.overrides_player_appearance;
        }
        else if constexpr (I == 20) {
            return value.trusted_skin_flag;
        }
        else {
            return value.profile_hash;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::SerializedSkinRef> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::SerializedSkinRef>{"SerializedSkinRef"};

template <>
inline constexpr std::array<std::string_view, 21> field_names_v<v2225::SerializedSkinRef>{{
    "id",
    "resource_patch",
    "image_data",
    "animated_image_data",
    "cape_image_data",
    "geometry_data",
    "geometry_data_min_engine_version",
    "animation_data",
    "cape_id",
    "full_id",
    "arm_size",
    "skin_color",
    "persona_pieces",
    "piece_tint_colors",
    "is_premium",
    "is_persona",
    "is_persona_cape_on_classic_skin",
    "is_primary_user",
    "overrides_player_appearance",
    "trusted_skin_flag",
    "profile_hash",
}};

template <>
struct field_accessor<v2225::SerializedSkinRef> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.id;
        }
        else if constexpr (I == 1) {
            return value.resource_patch;
        }
        else if constexpr (I == 2) {
            return value.image_data;
        }
        else if constexpr (I == 3) {
            return value.animated_image_data;
        }
        else if constexpr (I == 4) {
            return value.cape_image_data;
        }
        else if constexpr (I == 5) {
            return value.geometry_data;
        }
        else if constexpr (I == 6) {
            return value.geometry_data_min_engine_version;
        }
        else if constexpr (I == 7) {
            return value.animation_data;
        }
        else if constexpr (I == 8) {
            return value.cape_id;
        }
        else if constexpr (I == 9) {
            return value.full_id;
        }
        else if constexpr (I == 10) {
            return value.arm_size;
        }
        else if constexpr (I == 11) {
            return value.skin_color;
        }
        else if constexpr (I == 12) {
            return value.persona_pieces;
        }
        else if constexpr (I == 13) {
            return value.piece_tint_colors;
        }
        else if constexpr (I == 14) {
            return value.is_premium;
        }
        else if constexpr (I == 15) {
            return value.is_persona;
        }
        else if constexpr (I == 16) {
            return value.is_persona_cape_on_classic_skin;
        }
        else if constexpr (I == 17) {
            return value.is_primary_user;
        }
        else if constexpr (I == 18) {
            return value.overrides_player_appearance;
        }
        else if constexpr (I == 19) {
            return value.trusted_skin_flag;
        }
        else {
            return value.profile_hash;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::PlayerSkinPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::PlayerSkinPacket>{"PlayerSkinPacket"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<base::PlayerSkinPacket>{{
    "uuid",
    "skin",
    "localized_new_skin_name",
    "localized_old_skin_name",
    "trusted_skin",
}};

template <>
struct field_accessor<base::PlayerSkinPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.uuid;
        }
        else if constexpr (I == 1) {
            return value.skin;
        }
        else if constexpr (I == 2) {
            return value.localized_new_skin_name;
        }
        else if constexpr (I == 3) {
            return value.localized_old_skin_name;
        }
        else {
            return value.trusted_skin;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::PlayerSkinPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::PlayerSkinPacket>{"PlayerSkinPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v944::PlayerSkinPacket>{{
    "uuid",
    "skin",
    "localized_new_skin_name",
    "localized_old_skin_name",
}};

template <>
struct field_accessor<v944::PlayerSkinPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.uuid;
        }
        else if constexpr (I == 1) {
            return value.skin;
        }
        else if constexpr (I == 2) {
            return value.localized_new_skin_name;
        }
        else {
            return value.localized_old_skin_name;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::PlayerSkinPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::PlayerSkinPacket>{"PlayerSkinPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v2168::PlayerSkinPacket>{{
    "uuid",
    "skin",
    "localized_new_skin_name",
    "localized_old_skin_name",
}};

template <>
struct field_accessor<v2168::PlayerSkinPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.uuid;
        }
        else if constexpr (I == 1) {
            return value.skin;
        }
        else if constexpr (I == 2) {
            return value.localized_new_skin_name;
        }
        else {
            return value.localized_old_skin_name;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::PlayerSkinPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::PlayerSkinPacket>{"PlayerSkinPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v2225::PlayerSkinPacket>{{
    "uuid",
    "skin",
    "localized_new_skin_name",
    "localized_old_skin_name",
}};

template <>
struct field_accessor<v2225::PlayerSkinPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.uuid;
        }
        else if constexpr (I == 1) {
            return value.skin;
        }
        else if constexpr (I == 2) {
            return value.localized_new_skin_name;
        }
        else {
            return value.localized_old_skin_name;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<EmotePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<EmotePacket>{"EmotePacket"};

template <>
inline constexpr std::array<std::string_view, 6> field_names_v<EmotePacket>{{
    "runtime_id",
    "piece_id",
    "emote_ticks",
    "xuid",
    "platform_id",
    "flags",
}};

template <>
struct field_accessor<EmotePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.runtime_id;
        }
        else if constexpr (I == 1) {
            return value.piece_id;
        }
        else if constexpr (I == 2) {
            return value.emote_ticks;
        }
        else if constexpr (I == 3) {
            return value.xuid;
        }
        else if constexpr (I == 4) {
            return value.platform_id;
        }
        else {
            return value.flags;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<EmoteListPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<EmoteListPacket>{"EmoteListPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<EmoteListPacket>{{
    "runtime_id",
    "emote_piece_ids",
}};

template <>
struct field_accessor<EmoteListPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.runtime_id;
        }
        else {
            return value.emote_piece_ids;
        }
    }
};

}  // namespace detail


template <>
struct Serializer<ArmSizeType> {
    static void serialize(BinaryWriter &stream, ArmSizeType value);
    static auto deserialize(BinaryReader &stream) -> std::expected<ArmSizeType, std::error_code>;
};

template <>
struct Serializer<base::PieceType> {
    static void serialize(BinaryWriter &stream, base::PieceType value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::PieceType, std::error_code>;
};

template <>
struct Serializer<v2225::PieceType> {
    static void serialize(BinaryWriter &stream, v2225::PieceType value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::PieceType, std::error_code>;
};

template <>
struct Serializer<legacy::PieceType> {
    static void serialize(BinaryWriter &stream, legacy::PieceType value);
    static auto deserialize(BinaryReader &stream) -> std::expected<legacy::PieceType, std::error_code>;
};

template <>
struct Serializer<TrustedSkinFlag> {
    static void serialize(BinaryWriter &stream, TrustedSkinFlag value);
    static auto deserialize(BinaryReader &stream) -> std::expected<TrustedSkinFlag, std::error_code>;
};

template <>
struct Serializer<SkinImage> {
    static void serialize(BinaryWriter &stream, const SkinImage &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<SkinImage, std::error_code>;
};

template <>
struct Serializer<AnimatedImageData> {
    static void serialize(BinaryWriter &stream, const AnimatedImageData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<AnimatedImageData, std::error_code>;
};

template <>
struct Serializer<legacy::AnimatedImageData> {
    static void serialize(BinaryWriter &stream, const legacy::AnimatedImageData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<legacy::AnimatedImageData, std::error_code>;
};

template <>
struct Serializer<base::SerializedPersonaPieceHandle> {
    static void serialize(BinaryWriter &stream, const base::SerializedPersonaPieceHandle &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::SerializedPersonaPieceHandle, std::error_code>;
};

template <>
struct Serializer<v2225::SerializedPersonaPieceHandle> {
    static void serialize(BinaryWriter &stream, const v2225::SerializedPersonaPieceHandle &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::SerializedPersonaPieceHandle, std::error_code>;
};

template <>
struct Serializer<legacy::SerializedPersonaPieceHandle> {
    static void serialize(BinaryWriter &stream, const legacy::SerializedPersonaPieceHandle &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<legacy::SerializedPersonaPieceHandle, std::error_code>;
};

template <>
struct Serializer<TintMapColor> {
    static void serialize(BinaryWriter &stream, const TintMapColor &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<TintMapColor, std::error_code>;
};

template <>
struct Serializer<legacy::TintMapColor> {
    static void serialize(BinaryWriter &stream, const legacy::TintMapColor &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<legacy::TintMapColor, std::error_code>;
};

template <>
struct Serializer<legacy::SerializedSkinRef> {
    static void serialize(BinaryWriter &stream, const legacy::SerializedSkinRef &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<legacy::SerializedSkinRef, std::error_code>;
};

template <>
struct Serializer<base::SerializedSkinRef> {
    static void serialize(BinaryWriter &stream, const base::SerializedSkinRef &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::SerializedSkinRef, std::error_code>;
};

template <>
struct Serializer<v2168::SerializedSkinRef> {
    static void serialize(BinaryWriter &stream, const v2168::SerializedSkinRef &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::SerializedSkinRef, std::error_code>;
};

template <>
struct Serializer<v2225::SerializedSkinRef> {
    static void serialize(BinaryWriter &stream, const v2225::SerializedSkinRef &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::SerializedSkinRef, std::error_code>;
};

template <>
struct Serializer<base::PlayerSkinPacket> {
    static void serialize(BinaryWriter &stream, const base::PlayerSkinPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::PlayerSkinPacket, std::error_code>;
};

template <>
struct Serializer<v944::PlayerSkinPacket> {
    static void serialize(BinaryWriter &stream, const v944::PlayerSkinPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::PlayerSkinPacket, std::error_code>;
};

template <>
struct Serializer<v2168::PlayerSkinPacket> {
    static void serialize(BinaryWriter &stream, const v2168::PlayerSkinPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::PlayerSkinPacket, std::error_code>;
};

template <>
struct Serializer<v2225::PlayerSkinPacket> {
    static void serialize(BinaryWriter &stream, const v2225::PlayerSkinPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::PlayerSkinPacket, std::error_code>;
};

template <>
struct Serializer<EmotePacket> {
    static void serialize(BinaryWriter &stream, const EmotePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<EmotePacket, std::error_code>;
};

template <>
struct Serializer<EmoteListPacket> {
    static void serialize(BinaryWriter &stream, const EmoteListPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<EmoteListPacket, std::error_code>;
};
using PieceType = PieceType_<2225>;
using SerializedPersonaPieceHandle = SerializedPersonaPieceHandle_<2225>;
using SerializedSkinRef = SerializedSkinRef_<2225>;
using PlayerSkinPacket = PlayerSkinPacket_<2225>;

}  // namespace bedrock::protocol
