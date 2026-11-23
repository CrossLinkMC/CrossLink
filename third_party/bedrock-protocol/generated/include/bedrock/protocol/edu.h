#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <expected>
#include <optional>
#include <string>
#include <string_view>
#include <system_error>

#include <bedrock/protocol/detail/reflect.hpp>
#include <bedrock/protocol/enum.hpp>
#include <bedrock/protocol/packet.hpp>
#include <bedrock/protocol/serializer.hpp>
#include <bedrock/protocol/stream.hpp>

#include <bedrock/protocol/actor.h>

namespace bedrock::protocol {

struct EduSharedUriResource {
    std::string button_name{};
    std::string link_uri{};
};

struct CodeBuilderPacket {
    static constexpr int Id = 150;
    std::string url{};
    bool should_open_code_builder{};
};

enum class LessonAction : std::int8_t {
    Start = 0,
    Complete = 1,
    Restart = 2,
};

struct LessonProgressPacket {
    static constexpr int Id = 183;
    LessonAction action{};
    std::int32_t score{};
    std::string activity_id{};
};

struct AgentCapabilities {
    std::optional<bool> can_modify_blocks{};
};

struct EducationLocalLevelSettings {
    std::optional<std::string> code_builder_override_uri{};
};

struct ExternalLinkSettings {
    std::string url{};
    std::string display_name{};
};

struct EducationLevelSettings {
    std::string code_builder_default_uri{};
    std::string code_builder_title{};
    bool can_resize_code_builder{};
    bool disable_legacy_title_bar{};
    std::string post_process_filter{};
    std::string screenshot_border_resource_path{};
    std::optional<AgentCapabilities> agent_capabilities{};
    EducationLocalLevelSettings local_settings{};
    std::optional<ExternalLinkSettings> external_link_settings{};
};

struct EducationSettingsPacket {
    static constexpr int Id = 137;
    EducationLevelSettings education_level_settings{};
};

struct EduUriResourcePacket {
    static constexpr int Id = 170;
    EduSharedUriResource edu_shared_uri_resource{};
};

enum class Operation : std::uint8_t {
    None = 0,
    Get = 1,
    Set = 2,
    Reset = 3,
};

enum class Category : std::uint8_t {
    None = 0,
    CodeStatus = 1,
    Instantiation = 2,
};

enum class CodeStatus : std::uint8_t {
    None = 0,
    NotStarted = 1,
    InProgress = 2,
    Paused = 3,
    Error = 4,
    Succeeded = 5,
};

struct CodeBuilderSourcePacket {
    static constexpr int Id = 178;
    Operation operation{};
    Category category{};
    CodeStatus code_status{};
};

enum class AgentAnimation : std::uint8_t {
    ArmSwing = 0,
    Shrug = 1,
};

struct AgentAnimationPacket {
    static constexpr int Id = 304;
    AgentAnimation anim{};
    ActorRuntimeID runtime_id{};
};

enum class AgentActionType : int {
    Attack = 1,
    Collect = 2,
    Destroy = 3,
    DetectRedstone = 4,
    DetectObstacle = 5,
    Drop = 6,
    DropAll = 7,
    Inspect = 8,
    InspectData = 9,
    InspectItemCount = 10,
    InspectItemDetail = 11,
    InspectItemSpace = 12,
    Interact = 13,
    Move = 14,
    PlaceBlock = 15,
    Till = 16,
    TransferItemTo = 17,
    Turn = 18,
};

struct AgentActionEventPacket {
    static constexpr int Id = 181;
    std::string request_id{};
    AgentActionType action{};
    std::string response{};
};

template <int V>
struct packet_of<V, 137> { using type = EducationSettingsPacket; };

template <int V>
struct packet_of<V, 150> { using type = CodeBuilderPacket; };

template <int V>
struct packet_of<V, 170> { using type = EduUriResourcePacket; };

template <int V>
struct packet_of<V, 178> { using type = CodeBuilderSourcePacket; };

template <int V>
struct packet_of<V, 181> { using type = AgentActionEventPacket; };

template <int V>
struct packet_of<V, 183> { using type = LessonProgressPacket; };

template <int V>
struct packet_of<V, 304> { using type = AgentAnimationPacket; };

namespace detail {

template <>
inline constexpr std::array<LessonAction, 3> values_v<LessonAction>{{
    LessonAction::Start,
    LessonAction::Complete,
    LessonAction::Restart,
}};

template <>
inline constexpr std::array<std::string_view, 3> names_v<LessonAction>{{
    "start",
    "complete",
    "restart",
}};

template <>
inline constexpr std::string_view type_name_v<LessonAction>{"LessonAction"};

template <>
inline constexpr std::array<Operation, 4> values_v<Operation>{{
    Operation::None,
    Operation::Get,
    Operation::Set,
    Operation::Reset,
}};

template <>
inline constexpr std::array<std::string_view, 4> names_v<Operation>{{
    "none",
    "get",
    "set",
    "reset",
}};

template <>
inline constexpr std::string_view type_name_v<Operation>{"Operation"};

template <>
inline constexpr std::array<Category, 3> values_v<Category>{{
    Category::None,
    Category::CodeStatus,
    Category::Instantiation,
}};

template <>
inline constexpr std::array<std::string_view, 3> names_v<Category>{{
    "none",
    "codestatus",
    "instantiation",
}};

template <>
inline constexpr std::string_view type_name_v<Category>{"Category"};

template <>
inline constexpr std::array<CodeStatus, 6> values_v<CodeStatus>{{
    CodeStatus::None,
    CodeStatus::NotStarted,
    CodeStatus::InProgress,
    CodeStatus::Paused,
    CodeStatus::Error,
    CodeStatus::Succeeded,
}};

template <>
inline constexpr std::array<std::string_view, 6> names_v<CodeStatus>{{
    "none",
    "notstarted",
    "inprogress",
    "paused",
    "error",
    "succeeded",
}};

template <>
inline constexpr std::string_view type_name_v<CodeStatus>{"CodeStatus"};

template <>
inline constexpr std::array<AgentAnimation, 2> values_v<AgentAnimation>{{
    AgentAnimation::ArmSwing,
    AgentAnimation::Shrug,
}};

template <>
inline constexpr std::array<std::string_view, 2> names_v<AgentAnimation>{{
    "armswing",
    "shrug",
}};

template <>
inline constexpr std::string_view type_name_v<AgentAnimation>{"AgentAnimation"};

template <>
inline constexpr std::array<AgentActionType, 18> values_v<AgentActionType>{{
    AgentActionType::Attack,
    AgentActionType::Collect,
    AgentActionType::Destroy,
    AgentActionType::DetectRedstone,
    AgentActionType::DetectObstacle,
    AgentActionType::Drop,
    AgentActionType::DropAll,
    AgentActionType::Inspect,
    AgentActionType::InspectData,
    AgentActionType::InspectItemCount,
    AgentActionType::InspectItemDetail,
    AgentActionType::InspectItemSpace,
    AgentActionType::Interact,
    AgentActionType::Move,
    AgentActionType::PlaceBlock,
    AgentActionType::Till,
    AgentActionType::TransferItemTo,
    AgentActionType::Turn,
}};

template <>
inline constexpr std::array<std::string_view, 18> names_v<AgentActionType>{{
    "attack",
    "collect",
    "destroy",
    "detectredstone",
    "detectobstacle",
    "drop",
    "dropall",
    "inspect",
    "inspectdata",
    "inspectitemcount",
    "inspectitemdetail",
    "inspectitemspace",
    "interact",
    "move",
    "placeblock",
    "till",
    "transferitemto",
    "turn",
}};

template <>
inline constexpr std::string_view type_name_v<AgentActionType>{"AgentActionType"};

}  // namespace detail

namespace detail {

template <>
inline constexpr bool is_reflected_struct_v<EduSharedUriResource> = true;

template <>
inline constexpr std::string_view struct_name_v<EduSharedUriResource>{"EduSharedUriResource"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<EduSharedUriResource>{{
    "button_name",
    "link_uri",
}};

template <>
struct field_accessor<EduSharedUriResource> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.button_name;
        }
        else {
            return value.link_uri;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<CodeBuilderPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<CodeBuilderPacket>{"CodeBuilderPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<CodeBuilderPacket>{{
    "url",
    "should_open_code_builder",
}};

template <>
struct field_accessor<CodeBuilderPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.url;
        }
        else {
            return value.should_open_code_builder;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<LessonProgressPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<LessonProgressPacket>{"LessonProgressPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<LessonProgressPacket>{{
    "action",
    "score",
    "activity_id",
}};

template <>
struct field_accessor<LessonProgressPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.action;
        }
        else if constexpr (I == 1) {
            return value.score;
        }
        else {
            return value.activity_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<AgentCapabilities> = true;

template <>
inline constexpr std::string_view struct_name_v<AgentCapabilities>{"AgentCapabilities"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<AgentCapabilities>{{
    "can_modify_blocks",
}};

template <>
struct field_accessor<AgentCapabilities> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.can_modify_blocks;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<EducationLocalLevelSettings> = true;

template <>
inline constexpr std::string_view struct_name_v<EducationLocalLevelSettings>{"EducationLocalLevelSettings"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<EducationLocalLevelSettings>{{
    "code_builder_override_uri",
}};

template <>
struct field_accessor<EducationLocalLevelSettings> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.code_builder_override_uri;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<ExternalLinkSettings> = true;

template <>
inline constexpr std::string_view struct_name_v<ExternalLinkSettings>{"ExternalLinkSettings"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<ExternalLinkSettings>{{
    "url",
    "display_name",
}};

template <>
struct field_accessor<ExternalLinkSettings> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.url;
        }
        else {
            return value.display_name;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<EducationLevelSettings> = true;

template <>
inline constexpr std::string_view struct_name_v<EducationLevelSettings>{"EducationLevelSettings"};

template <>
inline constexpr std::array<std::string_view, 9> field_names_v<EducationLevelSettings>{{
    "code_builder_default_uri",
    "code_builder_title",
    "can_resize_code_builder",
    "disable_legacy_title_bar",
    "post_process_filter",
    "screenshot_border_resource_path",
    "agent_capabilities",
    "local_settings",
    "external_link_settings",
}};

template <>
struct field_accessor<EducationLevelSettings> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.code_builder_default_uri;
        }
        else if constexpr (I == 1) {
            return value.code_builder_title;
        }
        else if constexpr (I == 2) {
            return value.can_resize_code_builder;
        }
        else if constexpr (I == 3) {
            return value.disable_legacy_title_bar;
        }
        else if constexpr (I == 4) {
            return value.post_process_filter;
        }
        else if constexpr (I == 5) {
            return value.screenshot_border_resource_path;
        }
        else if constexpr (I == 6) {
            return value.agent_capabilities;
        }
        else if constexpr (I == 7) {
            return value.local_settings;
        }
        else {
            return value.external_link_settings;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<EducationSettingsPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<EducationSettingsPacket>{"EducationSettingsPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<EducationSettingsPacket>{{
    "education_level_settings",
}};

template <>
struct field_accessor<EducationSettingsPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.education_level_settings;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<EduUriResourcePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<EduUriResourcePacket>{"EduUriResourcePacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<EduUriResourcePacket>{{
    "edu_shared_uri_resource",
}};

template <>
struct field_accessor<EduUriResourcePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.edu_shared_uri_resource;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<CodeBuilderSourcePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<CodeBuilderSourcePacket>{"CodeBuilderSourcePacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<CodeBuilderSourcePacket>{{
    "operation",
    "category",
    "code_status",
}};

template <>
struct field_accessor<CodeBuilderSourcePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.operation;
        }
        else if constexpr (I == 1) {
            return value.category;
        }
        else {
            return value.code_status;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<AgentAnimationPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<AgentAnimationPacket>{"AgentAnimationPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<AgentAnimationPacket>{{
    "anim",
    "runtime_id",
}};

template <>
struct field_accessor<AgentAnimationPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.anim;
        }
        else {
            return value.runtime_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<AgentActionEventPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<AgentActionEventPacket>{"AgentActionEventPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<AgentActionEventPacket>{{
    "request_id",
    "action",
    "response",
}};

template <>
struct field_accessor<AgentActionEventPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.request_id;
        }
        else if constexpr (I == 1) {
            return value.action;
        }
        else {
            return value.response;
        }
    }
};

}  // namespace detail


template <>
struct Serializer<EduSharedUriResource> {
    static void serialize(BinaryWriter &stream, const EduSharedUriResource &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<EduSharedUriResource, std::error_code>;
};

template <>
struct Serializer<CodeBuilderPacket> {
    static void serialize(BinaryWriter &stream, const CodeBuilderPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<CodeBuilderPacket, std::error_code>;
};

template <>
struct Serializer<LessonProgressPacket> {
    static void serialize(BinaryWriter &stream, const LessonProgressPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<LessonProgressPacket, std::error_code>;
};

template <>
struct Serializer<AgentCapabilities> {
    static void serialize(BinaryWriter &stream, const AgentCapabilities &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<AgentCapabilities, std::error_code>;
};

template <>
struct Serializer<EducationLocalLevelSettings> {
    static void serialize(BinaryWriter &stream, const EducationLocalLevelSettings &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<EducationLocalLevelSettings, std::error_code>;
};

template <>
struct Serializer<ExternalLinkSettings> {
    static void serialize(BinaryWriter &stream, const ExternalLinkSettings &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<ExternalLinkSettings, std::error_code>;
};

template <>
struct Serializer<EducationLevelSettings> {
    static void serialize(BinaryWriter &stream, const EducationLevelSettings &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<EducationLevelSettings, std::error_code>;
};

template <>
struct Serializer<EducationSettingsPacket> {
    static void serialize(BinaryWriter &stream, const EducationSettingsPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<EducationSettingsPacket, std::error_code>;
};

template <>
struct Serializer<EduUriResourcePacket> {
    static void serialize(BinaryWriter &stream, const EduUriResourcePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<EduUriResourcePacket, std::error_code>;
};

template <>
struct Serializer<CodeBuilderSourcePacket> {
    static void serialize(BinaryWriter &stream, const CodeBuilderSourcePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<CodeBuilderSourcePacket, std::error_code>;
};

template <>
struct Serializer<AgentAnimationPacket> {
    static void serialize(BinaryWriter &stream, const AgentAnimationPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<AgentAnimationPacket, std::error_code>;
};

template <>
struct Serializer<AgentActionEventPacket> {
    static void serialize(BinaryWriter &stream, const AgentActionEventPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<AgentActionEventPacket, std::error_code>;
};

}  // namespace bedrock::protocol
