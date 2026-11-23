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

namespace bedrock::protocol {

enum class TextPacketType : std::uint8_t {
    Raw = 0,
    Chat = 1,
    Translate = 2,
    Popup = 3,
    JukeboxPopup = 4,
    Tip = 5,
    SystemMessage = 6,
    Whisper = 7,
    Announcement = 8,
    TextObjectWhisper = 9,
    TextObject = 10,
    TextObjectAnnouncement = 11,
};

struct ToastRequestPacket {
    static constexpr int Id = 186;
    std::string title{};
    std::string content{};
};

namespace SetTitlePacket_nested {

enum class TitleType : int {
    Clear = 0,
    Reset = 1,
    Title = 2,
    Subtitle = 3,
    Actionbar = 4,
    Times = 5,
    TitleTextObject = 6,
    SubtitleTextObject = 7,
    ActionbarTextObject = 8,
};

}  // namespace SetTitlePacket_nested

struct SetTitlePacket {
    using TitleType = SetTitlePacket_nested::TitleType;

    static constexpr int Id = 88;
    SetTitlePacket::TitleType type{};
    std::string title_text{};
    std::int32_t fade_in_time{};
    std::int32_t stay_time{};
    std::int32_t fade_out_time{};
    std::string xuid{};
    std::string platform_online_id{};
    std::string filtered_title_text{};
};

namespace base {

namespace TextPacket_nested {

struct MessageOnly {
    TextPacketType type{};
    std::string message{};
};

struct AuthorAndMessage {
    TextPacketType type{};
    std::string author{};
    std::string message{};
};

struct MessageAndParams {
    TextPacketType type{};
    std::string message{};
    std::vector<std::string> params{};
};

}  // namespace TextPacket_nested

struct TextPacket {
    using MessageOnly = TextPacket_nested::MessageOnly;
    using AuthorAndMessage = TextPacket_nested::AuthorAndMessage;
    using MessageAndParams = TextPacket_nested::MessageAndParams;

    static constexpr int Id = 9;
    bool localize{};
    std::variant<base::TextPacket::MessageOnly, base::TextPacket::AuthorAndMessage, base::TextPacket::MessageAndParams> body{};
    std::string xuid{};
    std::string platform_id{};
    std::optional<std::string> filtered_message{};
};

}  // namespace base

namespace v898 {

namespace TextPacket_nested {

struct MessageOnly {
    TextPacketType type{};
    std::string message{};
};

struct AuthorAndMessage {
    TextPacketType type{};
    std::string author{};
    std::string message{};
};

struct MessageAndParams {
    TextPacketType type{};
    std::string message{};
    std::vector<std::string> params{};
};

}  // namespace TextPacket_nested

struct TextPacket {
    using MessageOnly = TextPacket_nested::MessageOnly;
    using AuthorAndMessage = TextPacket_nested::AuthorAndMessage;
    using MessageAndParams = TextPacket_nested::MessageAndParams;

    static constexpr int Id = 9;
    bool localize{};
    std::variant<v898::TextPacket::MessageOnly, v898::TextPacket::AuthorAndMessage, v898::TextPacket::MessageAndParams> body{};
    std::string xuid{};
    std::string platform_id{};
    std::optional<std::string> filtered_message{};
};

}  // namespace v898

namespace v924 {

namespace TextPacket_nested {

struct MessageOnly {
    TextPacketType type{};
    std::string message{};
};

struct AuthorAndMessage {
    TextPacketType type{};
    std::string author{};
    std::string message{};
};

struct MessageAndParams {
    TextPacketType type{};
    std::string message{};
    std::vector<std::string> params{};
};

}  // namespace TextPacket_nested

struct TextPacket {
    using MessageOnly = TextPacket_nested::MessageOnly;
    using AuthorAndMessage = TextPacket_nested::AuthorAndMessage;
    using MessageAndParams = TextPacket_nested::MessageAndParams;

    static constexpr int Id = 9;
    bool localize{};
    std::variant<v924::TextPacket::MessageOnly, v924::TextPacket::AuthorAndMessage, v924::TextPacket::MessageAndParams> body{};
    std::string xuid{};
    std::string platform_id{};
    std::optional<std::string> filtered_message{};
};

}  // namespace v924

namespace detail {

template <int V>
struct TextPacket_;

template <int V> requires (V < 898)
struct TextPacket_<V> { using type = base::TextPacket; };

template <int V> requires (V >= 898 && V < 924)
struct TextPacket_<V> { using type = v898::TextPacket; };

template <int V> requires (V >= 924)
struct TextPacket_<V> { using type = v924::TextPacket; };

}  // namespace detail

template <int V> using TextPacket_ = typename detail::TextPacket_<V>::type;

template <int V>
struct packet_of<V, 9> { using type = TextPacket_<V>; };

template <int V>
struct packet_of<V, 88> { using type = SetTitlePacket; };

template <int V>
struct packet_of<V, 186> { using type = ToastRequestPacket; };

namespace detail {

template <>
inline constexpr std::array<TextPacketType, 12> values_v<TextPacketType>{{
    TextPacketType::Raw,
    TextPacketType::Chat,
    TextPacketType::Translate,
    TextPacketType::Popup,
    TextPacketType::JukeboxPopup,
    TextPacketType::Tip,
    TextPacketType::SystemMessage,
    TextPacketType::Whisper,
    TextPacketType::Announcement,
    TextPacketType::TextObjectWhisper,
    TextPacketType::TextObject,
    TextPacketType::TextObjectAnnouncement,
}};

template <>
inline constexpr std::array<std::string_view, 12> names_v<TextPacketType>{{
    "raw",
    "chat",
    "translate",
    "popup",
    "jukeboxpopup",
    "tip",
    "systemmessage",
    "whisper",
    "announcement",
    "textobjectwhisper",
    "textobject",
    "textobjectannouncement",
}};

template <>
inline constexpr std::string_view type_name_v<TextPacketType>{"TextPacketType"};

template <>
inline constexpr std::array<SetTitlePacket::TitleType, 9> values_v<SetTitlePacket::TitleType>{{
    SetTitlePacket::TitleType::Clear,
    SetTitlePacket::TitleType::Reset,
    SetTitlePacket::TitleType::Title,
    SetTitlePacket::TitleType::Subtitle,
    SetTitlePacket::TitleType::Actionbar,
    SetTitlePacket::TitleType::Times,
    SetTitlePacket::TitleType::TitleTextObject,
    SetTitlePacket::TitleType::SubtitleTextObject,
    SetTitlePacket::TitleType::ActionbarTextObject,
}};

template <>
inline constexpr std::array<std::string_view, 9> names_v<SetTitlePacket::TitleType>{{
    "clear",
    "reset",
    "title",
    "subtitle",
    "actionbar",
    "times",
    "titletextobject",
    "subtitletextobject",
    "actionbartextobject",
}};

template <>
inline constexpr std::string_view type_name_v<SetTitlePacket::TitleType>{"SetTitlePacket::TitleType"};

}  // namespace detail

namespace detail {

template <>
inline constexpr bool is_reflected_struct_v<base::TextPacket::MessageOnly> = true;

template <>
inline constexpr std::string_view struct_name_v<base::TextPacket::MessageOnly>{"TextPacket::MessageOnly"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<base::TextPacket::MessageOnly>{{
    "type",
    "message",
}};

template <>
struct field_accessor<base::TextPacket::MessageOnly> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.type;
        }
        else {
            return value.message;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::TextPacket::AuthorAndMessage> = true;

template <>
inline constexpr std::string_view struct_name_v<base::TextPacket::AuthorAndMessage>{"TextPacket::AuthorAndMessage"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<base::TextPacket::AuthorAndMessage>{{
    "type",
    "author",
    "message",
}};

template <>
struct field_accessor<base::TextPacket::AuthorAndMessage> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.type;
        }
        else if constexpr (I == 1) {
            return value.author;
        }
        else {
            return value.message;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::TextPacket::MessageAndParams> = true;

template <>
inline constexpr std::string_view struct_name_v<base::TextPacket::MessageAndParams>{"TextPacket::MessageAndParams"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<base::TextPacket::MessageAndParams>{{
    "type",
    "message",
    "params",
}};

template <>
struct field_accessor<base::TextPacket::MessageAndParams> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.type;
        }
        else if constexpr (I == 1) {
            return value.message;
        }
        else {
            return value.params;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v898::TextPacket::MessageOnly> = true;

template <>
inline constexpr std::string_view struct_name_v<v898::TextPacket::MessageOnly>{"TextPacket::MessageOnly"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v898::TextPacket::MessageOnly>{{
    "type",
    "message",
}};

template <>
struct field_accessor<v898::TextPacket::MessageOnly> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.type;
        }
        else {
            return value.message;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v898::TextPacket::AuthorAndMessage> = true;

template <>
inline constexpr std::string_view struct_name_v<v898::TextPacket::AuthorAndMessage>{"TextPacket::AuthorAndMessage"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v898::TextPacket::AuthorAndMessage>{{
    "type",
    "author",
    "message",
}};

template <>
struct field_accessor<v898::TextPacket::AuthorAndMessage> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.type;
        }
        else if constexpr (I == 1) {
            return value.author;
        }
        else {
            return value.message;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v898::TextPacket::MessageAndParams> = true;

template <>
inline constexpr std::string_view struct_name_v<v898::TextPacket::MessageAndParams>{"TextPacket::MessageAndParams"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v898::TextPacket::MessageAndParams>{{
    "type",
    "message",
    "params",
}};

template <>
struct field_accessor<v898::TextPacket::MessageAndParams> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.type;
        }
        else if constexpr (I == 1) {
            return value.message;
        }
        else {
            return value.params;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::TextPacket::MessageOnly> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::TextPacket::MessageOnly>{"TextPacket::MessageOnly"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v924::TextPacket::MessageOnly>{{
    "type",
    "message",
}};

template <>
struct field_accessor<v924::TextPacket::MessageOnly> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.type;
        }
        else {
            return value.message;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::TextPacket::AuthorAndMessage> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::TextPacket::AuthorAndMessage>{"TextPacket::AuthorAndMessage"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v924::TextPacket::AuthorAndMessage>{{
    "type",
    "author",
    "message",
}};

template <>
struct field_accessor<v924::TextPacket::AuthorAndMessage> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.type;
        }
        else if constexpr (I == 1) {
            return value.author;
        }
        else {
            return value.message;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::TextPacket::MessageAndParams> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::TextPacket::MessageAndParams>{"TextPacket::MessageAndParams"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v924::TextPacket::MessageAndParams>{{
    "type",
    "message",
    "params",
}};

template <>
struct field_accessor<v924::TextPacket::MessageAndParams> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.type;
        }
        else if constexpr (I == 1) {
            return value.message;
        }
        else {
            return value.params;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::TextPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::TextPacket>{"TextPacket"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<base::TextPacket>{{
    "localize",
    "body",
    "xuid",
    "platform_id",
    "filtered_message",
}};

template <>
struct field_accessor<base::TextPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.localize;
        }
        else if constexpr (I == 1) {
            return value.body;
        }
        else if constexpr (I == 2) {
            return value.xuid;
        }
        else if constexpr (I == 3) {
            return value.platform_id;
        }
        else {
            return value.filtered_message;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v898::TextPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v898::TextPacket>{"TextPacket"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v898::TextPacket>{{
    "localize",
    "body",
    "xuid",
    "platform_id",
    "filtered_message",
}};

template <>
struct field_accessor<v898::TextPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.localize;
        }
        else if constexpr (I == 1) {
            return value.body;
        }
        else if constexpr (I == 2) {
            return value.xuid;
        }
        else if constexpr (I == 3) {
            return value.platform_id;
        }
        else {
            return value.filtered_message;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::TextPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::TextPacket>{"TextPacket"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v924::TextPacket>{{
    "localize",
    "body",
    "xuid",
    "platform_id",
    "filtered_message",
}};

template <>
struct field_accessor<v924::TextPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.localize;
        }
        else if constexpr (I == 1) {
            return value.body;
        }
        else if constexpr (I == 2) {
            return value.xuid;
        }
        else if constexpr (I == 3) {
            return value.platform_id;
        }
        else {
            return value.filtered_message;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<ToastRequestPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<ToastRequestPacket>{"ToastRequestPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<ToastRequestPacket>{{
    "title",
    "content",
}};

template <>
struct field_accessor<ToastRequestPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.title;
        }
        else {
            return value.content;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<SetTitlePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<SetTitlePacket>{"SetTitlePacket"};

template <>
inline constexpr std::array<std::string_view, 8> field_names_v<SetTitlePacket>{{
    "type",
    "title_text",
    "fade_in_time",
    "stay_time",
    "fade_out_time",
    "xuid",
    "platform_online_id",
    "filtered_title_text",
}};

template <>
struct field_accessor<SetTitlePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.type;
        }
        else if constexpr (I == 1) {
            return value.title_text;
        }
        else if constexpr (I == 2) {
            return value.fade_in_time;
        }
        else if constexpr (I == 3) {
            return value.stay_time;
        }
        else if constexpr (I == 4) {
            return value.fade_out_time;
        }
        else if constexpr (I == 5) {
            return value.xuid;
        }
        else if constexpr (I == 6) {
            return value.platform_online_id;
        }
        else {
            return value.filtered_title_text;
        }
    }
};

}  // namespace detail


template <>
struct Serializer<base::TextPacket::MessageOnly> {
    static void serialize(BinaryWriter &stream, const base::TextPacket::MessageOnly &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::TextPacket::MessageOnly, std::error_code>;
};

template <>
struct Serializer<base::TextPacket::AuthorAndMessage> {
    static void serialize(BinaryWriter &stream, const base::TextPacket::AuthorAndMessage &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::TextPacket::AuthorAndMessage, std::error_code>;
};

template <>
struct Serializer<base::TextPacket::MessageAndParams> {
    static void serialize(BinaryWriter &stream, const base::TextPacket::MessageAndParams &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::TextPacket::MessageAndParams, std::error_code>;
};

template <>
struct Serializer<v898::TextPacket::MessageOnly> {
    static void serialize(BinaryWriter &stream, const v898::TextPacket::MessageOnly &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v898::TextPacket::MessageOnly, std::error_code>;
};

template <>
struct Serializer<v898::TextPacket::AuthorAndMessage> {
    static void serialize(BinaryWriter &stream, const v898::TextPacket::AuthorAndMessage &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v898::TextPacket::AuthorAndMessage, std::error_code>;
};

template <>
struct Serializer<v898::TextPacket::MessageAndParams> {
    static void serialize(BinaryWriter &stream, const v898::TextPacket::MessageAndParams &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v898::TextPacket::MessageAndParams, std::error_code>;
};

template <>
struct Serializer<v924::TextPacket::MessageOnly> {
    static void serialize(BinaryWriter &stream, const v924::TextPacket::MessageOnly &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::TextPacket::MessageOnly, std::error_code>;
};

template <>
struct Serializer<v924::TextPacket::AuthorAndMessage> {
    static void serialize(BinaryWriter &stream, const v924::TextPacket::AuthorAndMessage &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::TextPacket::AuthorAndMessage, std::error_code>;
};

template <>
struct Serializer<v924::TextPacket::MessageAndParams> {
    static void serialize(BinaryWriter &stream, const v924::TextPacket::MessageAndParams &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::TextPacket::MessageAndParams, std::error_code>;
};

template <>
struct Serializer<base::TextPacket> {
    static void serialize(BinaryWriter &stream, const base::TextPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::TextPacket, std::error_code>;
};

template <>
struct Serializer<v898::TextPacket> {
    static void serialize(BinaryWriter &stream, const v898::TextPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v898::TextPacket, std::error_code>;
};

template <>
struct Serializer<v924::TextPacket> {
    static void serialize(BinaryWriter &stream, const v924::TextPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::TextPacket, std::error_code>;
};

template <>
struct Serializer<ToastRequestPacket> {
    static void serialize(BinaryWriter &stream, const ToastRequestPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<ToastRequestPacket, std::error_code>;
};

template <>
struct Serializer<SetTitlePacket> {
    static void serialize(BinaryWriter &stream, const SetTitlePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<SetTitlePacket, std::error_code>;
};
using TextPacket = TextPacket_<2225>;

}  // namespace bedrock::protocol
