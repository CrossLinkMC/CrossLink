#include <bedrock/protocol/edu.h>

namespace bedrock::protocol {


void Serializer<EduSharedUriResource>::serialize(BinaryWriter &stream, const EduSharedUriResource &value)
{
    stream.write(value.button_name);
    stream.write(value.link_uri);
}

auto Serializer<EduSharedUriResource>::deserialize(BinaryReader &stream) -> std::expected<EduSharedUriResource, std::error_code>
{
    EduSharedUriResource out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.button_name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.link_uri = *v;
    }
    return out;
}

void Serializer<CodeBuilderPacket>::serialize(BinaryWriter &stream, const CodeBuilderPacket &value)
{
    stream.write(value.url);
    stream.write<bool>(value.should_open_code_builder);
}

auto Serializer<CodeBuilderPacket>::deserialize(BinaryReader &stream) -> std::expected<CodeBuilderPacket, std::error_code>
{
    CodeBuilderPacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.url = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.should_open_code_builder = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<LessonProgressPacket>::serialize(BinaryWriter &stream, const LessonProgressPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.action);
    stream.writeVarInt<std::int32_t>(value.score);
    stream.write(value.activity_id);
}

auto Serializer<LessonProgressPacket>::deserialize(BinaryReader &stream) -> std::expected<LessonProgressPacket, std::error_code>
{
    LessonProgressPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.action = static_cast<LessonAction>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.score = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.activity_id = *v;
    }
    return out;
}

void Serializer<AgentCapabilities>::serialize(BinaryWriter &stream, const AgentCapabilities &value)
{
    stream.write<bool>(value.can_modify_blocks.has_value());
    if (value.can_modify_blocks.has_value()) {
        stream.write<bool>((*value.can_modify_blocks));
    }
}

auto Serializer<AgentCapabilities>::deserialize(BinaryReader &stream) -> std::expected<AgentCapabilities, std::error_code>
{
    AgentCapabilities out;
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.can_modify_blocks = std::move(staged);
        }
    }
    return out;
}

void Serializer<EducationLocalLevelSettings>::serialize(BinaryWriter &stream, const EducationLocalLevelSettings &value)
{
    stream.write<bool>(value.code_builder_override_uri.has_value());
    if (value.code_builder_override_uri.has_value()) {
        stream.write((*value.code_builder_override_uri));
    }
}

auto Serializer<EducationLocalLevelSettings>::deserialize(BinaryReader &stream) -> std::expected<EducationLocalLevelSettings, std::error_code>
{
    EducationLocalLevelSettings out;
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::string staged{};
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.code_builder_override_uri = std::move(staged);
        }
    }
    return out;
}

void Serializer<ExternalLinkSettings>::serialize(BinaryWriter &stream, const ExternalLinkSettings &value)
{
    stream.write(value.url);
    stream.write(value.display_name);
}

auto Serializer<ExternalLinkSettings>::deserialize(BinaryReader &stream) -> std::expected<ExternalLinkSettings, std::error_code>
{
    ExternalLinkSettings out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.url = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.display_name = *v;
    }
    return out;
}

void Serializer<EducationLevelSettings>::serialize(BinaryWriter &stream, const EducationLevelSettings &value)
{
    stream.write(value.code_builder_default_uri);
    stream.write(value.code_builder_title);
    stream.write<bool>(value.can_resize_code_builder);
    stream.write<bool>(value.disable_legacy_title_bar);
    stream.write(value.post_process_filter);
    stream.write(value.screenshot_border_resource_path);
    stream.write<bool>(value.agent_capabilities.has_value());
    if (value.agent_capabilities.has_value()) {
        Serializer<AgentCapabilities>::serialize(stream, (*value.agent_capabilities));
    }
    Serializer<EducationLocalLevelSettings>::serialize(stream, value.local_settings);
    stream.write<bool>(false);
    stream.write<bool>(value.external_link_settings.has_value());
    if (value.external_link_settings.has_value()) {
        Serializer<ExternalLinkSettings>::serialize(stream, (*value.external_link_settings));
    }
}

auto Serializer<EducationLevelSettings>::deserialize(BinaryReader &stream) -> std::expected<EducationLevelSettings, std::error_code>
{
    EducationLevelSettings out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.code_builder_default_uri = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.code_builder_title = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.can_resize_code_builder = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.disable_legacy_title_bar = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.post_process_filter = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.screenshot_border_resource_path = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            AgentCapabilities staged{};
            auto v = Serializer<AgentCapabilities>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.agent_capabilities = std::move(staged);
        }
    }
    {
        auto v = Serializer<EducationLocalLevelSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.local_settings = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        if (*v != false) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            ExternalLinkSettings staged{};
            auto v = Serializer<ExternalLinkSettings>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.external_link_settings = std::move(staged);
        }
    }
    return out;
}

void Serializer<EducationSettingsPacket>::serialize(BinaryWriter &stream, const EducationSettingsPacket &value)
{
    Serializer<EducationLevelSettings>::serialize(stream, value.education_level_settings);
}

auto Serializer<EducationSettingsPacket>::deserialize(BinaryReader &stream) -> std::expected<EducationSettingsPacket, std::error_code>
{
    EducationSettingsPacket out;
    {
        auto v = Serializer<EducationLevelSettings>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.education_level_settings = *v;
    }
    return out;
}

void Serializer<EduUriResourcePacket>::serialize(BinaryWriter &stream, const EduUriResourcePacket &value)
{
    Serializer<EduSharedUriResource>::serialize(stream, value.edu_shared_uri_resource);
}

auto Serializer<EduUriResourcePacket>::deserialize(BinaryReader &stream) -> std::expected<EduUriResourcePacket, std::error_code>
{
    EduUriResourcePacket out;
    {
        auto v = Serializer<EduSharedUriResource>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.edu_shared_uri_resource = *v;
    }
    return out;
}

void Serializer<CodeBuilderSourcePacket>::serialize(BinaryWriter &stream, const CodeBuilderSourcePacket &value)
{
    stream.write<std::uint8_t>(value.operation);
    stream.write<std::uint8_t>(value.category);
    stream.write<std::uint8_t>(value.code_status);
}

auto Serializer<CodeBuilderSourcePacket>::deserialize(BinaryReader &stream) -> std::expected<CodeBuilderSourcePacket, std::error_code>
{
    CodeBuilderSourcePacket out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.operation = static_cast<Operation>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.category = static_cast<Category>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.code_status = static_cast<CodeStatus>(*v);
    }
    return out;
}

void Serializer<AgentAnimationPacket>::serialize(BinaryWriter &stream, const AgentAnimationPacket &value)
{
    stream.write<std::uint8_t>(value.anim);
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
}

auto Serializer<AgentAnimationPacket>::deserialize(BinaryReader &stream) -> std::expected<AgentAnimationPacket, std::error_code>
{
    AgentAnimationPacket out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.anim = static_cast<AgentAnimation>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    return out;
}

void Serializer<AgentActionEventPacket>::serialize(BinaryWriter &stream, const AgentActionEventPacket &value)
{
    stream.write(value.request_id);
    stream.write<std::int32_t>(value.action);
    stream.write(value.response);
}

auto Serializer<AgentActionEventPacket>::deserialize(BinaryReader &stream) -> std::expected<AgentActionEventPacket, std::error_code>
{
    AgentActionEventPacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.request_id = *v;
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.action = static_cast<AgentActionType>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.response = *v;
    }
    return out;
}

}  // namespace bedrock::protocol
