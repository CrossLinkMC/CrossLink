#include <bedrock/protocol/camera.h>

namespace bedrock::protocol {


void Serializer<v766::CameraAimAssistCommandPresetDefinition>::serialize(BinaryWriter &stream, const v766::CameraAimAssistCommandPresetDefinition &value)
{
    stream.write<bool>(value.preset_id.has_value());
    if (value.preset_id.has_value()) {
        stream.write((*value.preset_id));
    }
    stream.write<bool>(value.target_mode.has_value());
    if (value.target_mode.has_value()) {
        stream.write<std::uint8_t>((*value.target_mode));
    }
    stream.write<bool>(value.angle.has_value());
    if (value.angle.has_value()) {
        Serializer<Vec2>::serialize(stream, (*value.angle));
    }
    stream.write<bool>(value.distance.has_value());
    if (value.distance.has_value()) {
        stream.write<float>((*value.distance));
    }
}

auto Serializer<v766::CameraAimAssistCommandPresetDefinition>::deserialize(BinaryReader &stream) -> std::expected<v766::CameraAimAssistCommandPresetDefinition, std::error_code>
{
    v766::CameraAimAssistCommandPresetDefinition out;
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::string staged{};
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.preset_id = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v766::TargetMode staged{};
            auto v = stream.read<std::uint8_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<v766::TargetMode>(*v);
            out.target_mode = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec2 staged{};
            auto v = Serializer<Vec2>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.angle = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.distance = std::move(staged);
        }
    }
    return out;
}

void Serializer<base::CameraPreset>::serialize(BinaryWriter &stream, const base::CameraPreset &value)
{
    stream.write(value.name);
    stream.write(value.inherit_from);
    stream.write<bool>(value.pos_x.has_value());
    if (value.pos_x.has_value()) {
        stream.write<float>((*value.pos_x));
    }
    stream.write<bool>(value.pos_y.has_value());
    if (value.pos_y.has_value()) {
        stream.write<float>((*value.pos_y));
    }
    stream.write<bool>(value.pos_z.has_value());
    if (value.pos_z.has_value()) {
        stream.write<float>((*value.pos_z));
    }
    stream.write<bool>(value.rot_x.has_value());
    if (value.rot_x.has_value()) {
        stream.write<float>((*value.rot_x));
    }
    stream.write<bool>(value.rot_y.has_value());
    if (value.rot_y.has_value()) {
        stream.write<float>((*value.rot_y));
    }
    stream.write<bool>(value.camera_rotation_speed.has_value());
    if (value.camera_rotation_speed.has_value()) {
        stream.write<float>((*value.camera_rotation_speed));
    }
    stream.write<bool>(value.snap_to_target.has_value());
    if (value.snap_to_target.has_value()) {
        stream.write<bool>((*value.snap_to_target));
    }
    stream.write<bool>(value.view_offset.has_value());
    if (value.view_offset.has_value()) {
        Serializer<Vec2>::serialize(stream, (*value.view_offset));
    }
    stream.write<bool>(value.entity_offset.has_value());
    if (value.entity_offset.has_value()) {
        Serializer<Vec3>::serialize(stream, (*value.entity_offset));
    }
    stream.write<bool>(value.radius.has_value());
    if (value.radius.has_value()) {
        stream.write<float>((*value.radius));
    }
    stream.write<bool>(value.listener.has_value());
    if (value.listener.has_value()) {
        stream.write<std::uint8_t>((*value.listener));
    }
    stream.write<bool>(value.player_effects.has_value());
    if (value.player_effects.has_value()) {
        stream.write<bool>((*value.player_effects));
    }
}

auto Serializer<base::CameraPreset>::deserialize(BinaryReader &stream) -> std::expected<base::CameraPreset, std::error_code>
{
    base::CameraPreset out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.inherit_from = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.pos_x = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.pos_y = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.pos_z = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.rot_x = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.rot_y = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.camera_rotation_speed = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.snap_to_target = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec2 staged{};
            auto v = Serializer<Vec2>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.view_offset = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec3 staged{};
            auto v = Serializer<Vec3>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.entity_offset = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.radius = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            base::CameraPreset::AudioListener staged{};
            auto v = stream.read<std::uint8_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<base::CameraPreset::AudioListener>(*v);
            out.listener = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.player_effects = std::move(staged);
        }
    }
    return out;
}

void Serializer<v748::CameraPreset>::serialize(BinaryWriter &stream, const v748::CameraPreset &value)
{
    stream.write(value.name);
    stream.write(value.inherit_from);
    stream.write<bool>(value.pos_x.has_value());
    if (value.pos_x.has_value()) {
        stream.write<float>((*value.pos_x));
    }
    stream.write<bool>(value.pos_y.has_value());
    if (value.pos_y.has_value()) {
        stream.write<float>((*value.pos_y));
    }
    stream.write<bool>(value.pos_z.has_value());
    if (value.pos_z.has_value()) {
        stream.write<float>((*value.pos_z));
    }
    stream.write<bool>(value.rot_x.has_value());
    if (value.rot_x.has_value()) {
        stream.write<float>((*value.rot_x));
    }
    stream.write<bool>(value.rot_y.has_value());
    if (value.rot_y.has_value()) {
        stream.write<float>((*value.rot_y));
    }
    stream.write<bool>(value.camera_rotation_speed.has_value());
    if (value.camera_rotation_speed.has_value()) {
        stream.write<float>((*value.camera_rotation_speed));
    }
    stream.write<bool>(value.snap_to_target.has_value());
    if (value.snap_to_target.has_value()) {
        stream.write<bool>((*value.snap_to_target));
    }
    stream.write<bool>(value.horizontal_rotation_limit.has_value());
    if (value.horizontal_rotation_limit.has_value()) {
        Serializer<Vec2>::serialize(stream, (*value.horizontal_rotation_limit));
    }
    stream.write<bool>(value.vertical_rotation_limit.has_value());
    if (value.vertical_rotation_limit.has_value()) {
        Serializer<Vec2>::serialize(stream, (*value.vertical_rotation_limit));
    }
    stream.write<bool>(value.continue_targeting.has_value());
    if (value.continue_targeting.has_value()) {
        stream.write<bool>((*value.continue_targeting));
    }
    stream.write<bool>(value.view_offset.has_value());
    if (value.view_offset.has_value()) {
        Serializer<Vec2>::serialize(stream, (*value.view_offset));
    }
    stream.write<bool>(value.entity_offset.has_value());
    if (value.entity_offset.has_value()) {
        Serializer<Vec3>::serialize(stream, (*value.entity_offset));
    }
    stream.write<bool>(value.radius.has_value());
    if (value.radius.has_value()) {
        stream.write<float>((*value.radius));
    }
    stream.write<bool>(value.listener.has_value());
    if (value.listener.has_value()) {
        stream.write<std::uint8_t>((*value.listener));
    }
    stream.write<bool>(value.player_effects.has_value());
    if (value.player_effects.has_value()) {
        stream.write<bool>((*value.player_effects));
    }
    stream.write<bool>(value.align_target_and_camera_forward.has_value());
    if (value.align_target_and_camera_forward.has_value()) {
        stream.write<bool>((*value.align_target_and_camera_forward));
    }
}

auto Serializer<v748::CameraPreset>::deserialize(BinaryReader &stream) -> std::expected<v748::CameraPreset, std::error_code>
{
    v748::CameraPreset out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.inherit_from = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.pos_x = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.pos_y = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.pos_z = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.rot_x = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.rot_y = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.camera_rotation_speed = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.snap_to_target = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec2 staged{};
            auto v = Serializer<Vec2>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.horizontal_rotation_limit = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec2 staged{};
            auto v = Serializer<Vec2>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.vertical_rotation_limit = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.continue_targeting = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec2 staged{};
            auto v = Serializer<Vec2>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.view_offset = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec3 staged{};
            auto v = Serializer<Vec3>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.entity_offset = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.radius = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v748::CameraPreset::AudioListener staged{};
            auto v = stream.read<std::uint8_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<v748::CameraPreset::AudioListener>(*v);
            out.listener = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.player_effects = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.align_target_and_camera_forward = std::move(staged);
        }
    }
    return out;
}

void Serializer<v766::CameraPreset>::serialize(BinaryWriter &stream, const v766::CameraPreset &value)
{
    stream.write(value.name);
    stream.write(value.inherit_from);
    stream.write<bool>(value.pos_x.has_value());
    if (value.pos_x.has_value()) {
        stream.write<float>((*value.pos_x));
    }
    stream.write<bool>(value.pos_y.has_value());
    if (value.pos_y.has_value()) {
        stream.write<float>((*value.pos_y));
    }
    stream.write<bool>(value.pos_z.has_value());
    if (value.pos_z.has_value()) {
        stream.write<float>((*value.pos_z));
    }
    stream.write<bool>(value.rot_x.has_value());
    if (value.rot_x.has_value()) {
        stream.write<float>((*value.rot_x));
    }
    stream.write<bool>(value.rot_y.has_value());
    if (value.rot_y.has_value()) {
        stream.write<float>((*value.rot_y));
    }
    stream.write<bool>(value.camera_rotation_speed.has_value());
    if (value.camera_rotation_speed.has_value()) {
        stream.write<float>((*value.camera_rotation_speed));
    }
    stream.write<bool>(value.snap_to_target.has_value());
    if (value.snap_to_target.has_value()) {
        stream.write<bool>((*value.snap_to_target));
    }
    stream.write<bool>(value.horizontal_rotation_limit.has_value());
    if (value.horizontal_rotation_limit.has_value()) {
        Serializer<Vec2>::serialize(stream, (*value.horizontal_rotation_limit));
    }
    stream.write<bool>(value.vertical_rotation_limit.has_value());
    if (value.vertical_rotation_limit.has_value()) {
        Serializer<Vec2>::serialize(stream, (*value.vertical_rotation_limit));
    }
    stream.write<bool>(value.continue_targeting.has_value());
    if (value.continue_targeting.has_value()) {
        stream.write<bool>((*value.continue_targeting));
    }
    stream.write<bool>(value.tracking_radius.has_value());
    if (value.tracking_radius.has_value()) {
        stream.write<float>((*value.tracking_radius));
    }
    stream.write<bool>(value.view_offset.has_value());
    if (value.view_offset.has_value()) {
        Serializer<Vec2>::serialize(stream, (*value.view_offset));
    }
    stream.write<bool>(value.entity_offset.has_value());
    if (value.entity_offset.has_value()) {
        Serializer<Vec3>::serialize(stream, (*value.entity_offset));
    }
    stream.write<bool>(value.radius.has_value());
    if (value.radius.has_value()) {
        stream.write<float>((*value.radius));
    }
    stream.write<bool>(value.listener.has_value());
    if (value.listener.has_value()) {
        stream.write<std::uint8_t>((*value.listener));
    }
    stream.write<bool>(value.player_effects.has_value());
    if (value.player_effects.has_value()) {
        stream.write<bool>((*value.player_effects));
    }
    stream.write<bool>(value.align_target_and_camera_forward.has_value());
    if (value.align_target_and_camera_forward.has_value()) {
        stream.write<bool>((*value.align_target_and_camera_forward));
    }
    stream.write<bool>(value.aim_assist.has_value());
    if (value.aim_assist.has_value()) {
        Serializer<v766::CameraAimAssistCommandPresetDefinition>::serialize(stream, (*value.aim_assist));
    }
}

auto Serializer<v766::CameraPreset>::deserialize(BinaryReader &stream) -> std::expected<v766::CameraPreset, std::error_code>
{
    v766::CameraPreset out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.inherit_from = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.pos_x = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.pos_y = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.pos_z = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.rot_x = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.rot_y = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.camera_rotation_speed = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.snap_to_target = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec2 staged{};
            auto v = Serializer<Vec2>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.horizontal_rotation_limit = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec2 staged{};
            auto v = Serializer<Vec2>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.vertical_rotation_limit = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.continue_targeting = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.tracking_radius = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec2 staged{};
            auto v = Serializer<Vec2>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.view_offset = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec3 staged{};
            auto v = Serializer<Vec3>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.entity_offset = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.radius = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v766::CameraPreset::AudioListener staged{};
            auto v = stream.read<std::uint8_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<v766::CameraPreset::AudioListener>(*v);
            out.listener = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.player_effects = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.align_target_and_camera_forward = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v766::CameraAimAssistCommandPresetDefinition staged{};
            auto v = Serializer<v766::CameraAimAssistCommandPresetDefinition>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.aim_assist = std::move(staged);
        }
    }
    return out;
}

void Serializer<v776::CameraPreset>::serialize(BinaryWriter &stream, const v776::CameraPreset &value)
{
    stream.write(value.name);
    stream.write(value.inherit_from);
    stream.write<bool>(value.pos_x.has_value());
    if (value.pos_x.has_value()) {
        stream.write<float>((*value.pos_x));
    }
    stream.write<bool>(value.pos_y.has_value());
    if (value.pos_y.has_value()) {
        stream.write<float>((*value.pos_y));
    }
    stream.write<bool>(value.pos_z.has_value());
    if (value.pos_z.has_value()) {
        stream.write<float>((*value.pos_z));
    }
    stream.write<bool>(value.rot_x.has_value());
    if (value.rot_x.has_value()) {
        stream.write<float>((*value.rot_x));
    }
    stream.write<bool>(value.rot_y.has_value());
    if (value.rot_y.has_value()) {
        stream.write<float>((*value.rot_y));
    }
    stream.write<bool>(value.camera_rotation_speed.has_value());
    if (value.camera_rotation_speed.has_value()) {
        stream.write<float>((*value.camera_rotation_speed));
    }
    stream.write<bool>(value.snap_to_target.has_value());
    if (value.snap_to_target.has_value()) {
        stream.write<bool>((*value.snap_to_target));
    }
    stream.write<bool>(value.horizontal_rotation_limit.has_value());
    if (value.horizontal_rotation_limit.has_value()) {
        Serializer<Vec2>::serialize(stream, (*value.horizontal_rotation_limit));
    }
    stream.write<bool>(value.vertical_rotation_limit.has_value());
    if (value.vertical_rotation_limit.has_value()) {
        Serializer<Vec2>::serialize(stream, (*value.vertical_rotation_limit));
    }
    stream.write<bool>(value.continue_targeting.has_value());
    if (value.continue_targeting.has_value()) {
        stream.write<bool>((*value.continue_targeting));
    }
    stream.write<bool>(value.tracking_radius.has_value());
    if (value.tracking_radius.has_value()) {
        stream.write<float>((*value.tracking_radius));
    }
    stream.write<bool>(value.view_offset.has_value());
    if (value.view_offset.has_value()) {
        Serializer<Vec2>::serialize(stream, (*value.view_offset));
    }
    stream.write<bool>(value.entity_offset.has_value());
    if (value.entity_offset.has_value()) {
        Serializer<Vec3>::serialize(stream, (*value.entity_offset));
    }
    stream.write<bool>(value.radius.has_value());
    if (value.radius.has_value()) {
        stream.write<float>((*value.radius));
    }
    stream.write<bool>(value.yaw_limit_min.has_value());
    if (value.yaw_limit_min.has_value()) {
        stream.write<float>((*value.yaw_limit_min));
    }
    stream.write<bool>(value.yaw_limit_max.has_value());
    if (value.yaw_limit_max.has_value()) {
        stream.write<float>((*value.yaw_limit_max));
    }
    stream.write<bool>(value.listener.has_value());
    if (value.listener.has_value()) {
        stream.write<std::uint8_t>((*value.listener));
    }
    stream.write<bool>(value.player_effects.has_value());
    if (value.player_effects.has_value()) {
        stream.write<bool>((*value.player_effects));
    }
    stream.write<bool>(value.align_target_and_camera_forward.has_value());
    if (value.align_target_and_camera_forward.has_value()) {
        stream.write<bool>((*value.align_target_and_camera_forward));
    }
    stream.write<bool>(value.aim_assist.has_value());
    if (value.aim_assist.has_value()) {
        Serializer<v766::CameraAimAssistCommandPresetDefinition>::serialize(stream, (*value.aim_assist));
    }
}

auto Serializer<v776::CameraPreset>::deserialize(BinaryReader &stream) -> std::expected<v776::CameraPreset, std::error_code>
{
    v776::CameraPreset out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.inherit_from = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.pos_x = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.pos_y = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.pos_z = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.rot_x = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.rot_y = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.camera_rotation_speed = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.snap_to_target = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec2 staged{};
            auto v = Serializer<Vec2>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.horizontal_rotation_limit = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec2 staged{};
            auto v = Serializer<Vec2>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.vertical_rotation_limit = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.continue_targeting = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.tracking_radius = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec2 staged{};
            auto v = Serializer<Vec2>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.view_offset = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec3 staged{};
            auto v = Serializer<Vec3>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.entity_offset = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.radius = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.yaw_limit_min = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.yaw_limit_max = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v776::CameraPreset::AudioListener staged{};
            auto v = stream.read<std::uint8_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<v776::CameraPreset::AudioListener>(*v);
            out.listener = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.player_effects = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.align_target_and_camera_forward = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v766::CameraAimAssistCommandPresetDefinition staged{};
            auto v = Serializer<v766::CameraAimAssistCommandPresetDefinition>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.aim_assist = std::move(staged);
        }
    }
    return out;
}

void Serializer<v800::CameraPreset>::serialize(BinaryWriter &stream, const v800::CameraPreset &value)
{
    stream.write(value.name);
    stream.write(value.inherit_from);
    stream.write<bool>(value.pos_x.has_value());
    if (value.pos_x.has_value()) {
        stream.write<float>((*value.pos_x));
    }
    stream.write<bool>(value.pos_y.has_value());
    if (value.pos_y.has_value()) {
        stream.write<float>((*value.pos_y));
    }
    stream.write<bool>(value.pos_z.has_value());
    if (value.pos_z.has_value()) {
        stream.write<float>((*value.pos_z));
    }
    stream.write<bool>(value.rot_x.has_value());
    if (value.rot_x.has_value()) {
        stream.write<float>((*value.rot_x));
    }
    stream.write<bool>(value.rot_y.has_value());
    if (value.rot_y.has_value()) {
        stream.write<float>((*value.rot_y));
    }
    stream.write<bool>(value.camera_rotation_speed.has_value());
    if (value.camera_rotation_speed.has_value()) {
        stream.write<float>((*value.camera_rotation_speed));
    }
    stream.write<bool>(value.snap_to_target.has_value());
    if (value.snap_to_target.has_value()) {
        stream.write<bool>((*value.snap_to_target));
    }
    stream.write<bool>(value.horizontal_rotation_limit.has_value());
    if (value.horizontal_rotation_limit.has_value()) {
        Serializer<Vec2>::serialize(stream, (*value.horizontal_rotation_limit));
    }
    stream.write<bool>(value.vertical_rotation_limit.has_value());
    if (value.vertical_rotation_limit.has_value()) {
        Serializer<Vec2>::serialize(stream, (*value.vertical_rotation_limit));
    }
    stream.write<bool>(value.continue_targeting.has_value());
    if (value.continue_targeting.has_value()) {
        stream.write<bool>((*value.continue_targeting));
    }
    stream.write<bool>(value.tracking_radius.has_value());
    if (value.tracking_radius.has_value()) {
        stream.write<float>((*value.tracking_radius));
    }
    stream.write<bool>(value.view_offset.has_value());
    if (value.view_offset.has_value()) {
        Serializer<Vec2>::serialize(stream, (*value.view_offset));
    }
    stream.write<bool>(value.entity_offset.has_value());
    if (value.entity_offset.has_value()) {
        Serializer<Vec3>::serialize(stream, (*value.entity_offset));
    }
    stream.write<bool>(value.radius.has_value());
    if (value.radius.has_value()) {
        stream.write<float>((*value.radius));
    }
    stream.write<bool>(value.yaw_limit_min.has_value());
    if (value.yaw_limit_min.has_value()) {
        stream.write<float>((*value.yaw_limit_min));
    }
    stream.write<bool>(value.yaw_limit_max.has_value());
    if (value.yaw_limit_max.has_value()) {
        stream.write<float>((*value.yaw_limit_max));
    }
    stream.write<bool>(value.listener.has_value());
    if (value.listener.has_value()) {
        stream.write<std::uint8_t>((*value.listener));
    }
    stream.write<bool>(value.player_effects.has_value());
    if (value.player_effects.has_value()) {
        stream.write<bool>((*value.player_effects));
    }
    stream.write<bool>(value.align_target_and_camera_forward.has_value());
    if (value.align_target_and_camera_forward.has_value()) {
        stream.write<bool>((*value.align_target_and_camera_forward));
    }
    stream.write<bool>(value.aim_assist.has_value());
    if (value.aim_assist.has_value()) {
        Serializer<v766::CameraAimAssistCommandPresetDefinition>::serialize(stream, (*value.aim_assist));
    }
    stream.write<bool>(value.control_scheme.has_value());
    if (value.control_scheme.has_value()) {
        stream.write<std::uint8_t>((*value.control_scheme));
    }
}

auto Serializer<v800::CameraPreset>::deserialize(BinaryReader &stream) -> std::expected<v800::CameraPreset, std::error_code>
{
    v800::CameraPreset out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.inherit_from = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.pos_x = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.pos_y = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.pos_z = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.rot_x = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.rot_y = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.camera_rotation_speed = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.snap_to_target = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec2 staged{};
            auto v = Serializer<Vec2>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.horizontal_rotation_limit = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec2 staged{};
            auto v = Serializer<Vec2>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.vertical_rotation_limit = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.continue_targeting = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.tracking_radius = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec2 staged{};
            auto v = Serializer<Vec2>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.view_offset = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec3 staged{};
            auto v = Serializer<Vec3>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.entity_offset = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.radius = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.yaw_limit_min = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.yaw_limit_max = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v800::CameraPreset::AudioListener staged{};
            auto v = stream.read<std::uint8_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<v800::CameraPreset::AudioListener>(*v);
            out.listener = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.player_effects = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.align_target_and_camera_forward = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v766::CameraAimAssistCommandPresetDefinition staged{};
            auto v = Serializer<v766::CameraAimAssistCommandPresetDefinition>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.aim_assist = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Scheme staged{};
            auto v = stream.read<std::uint8_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<Scheme>(*v);
            out.control_scheme = std::move(staged);
        }
    }
    return out;
}

void Serializer<v818::CameraPreset>::serialize(BinaryWriter &stream, const v818::CameraPreset &value)
{
    stream.write(value.name);
    stream.write(value.inherit_from);
    stream.write<bool>(value.pos_x.has_value());
    if (value.pos_x.has_value()) {
        stream.write<float>((*value.pos_x));
    }
    stream.write<bool>(value.pos_y.has_value());
    if (value.pos_y.has_value()) {
        stream.write<float>((*value.pos_y));
    }
    stream.write<bool>(value.pos_z.has_value());
    if (value.pos_z.has_value()) {
        stream.write<float>((*value.pos_z));
    }
    stream.write<bool>(value.rot_x.has_value());
    if (value.rot_x.has_value()) {
        stream.write<float>((*value.rot_x));
    }
    stream.write<bool>(value.rot_y.has_value());
    if (value.rot_y.has_value()) {
        stream.write<float>((*value.rot_y));
    }
    stream.write<bool>(value.camera_rotation_speed.has_value());
    if (value.camera_rotation_speed.has_value()) {
        stream.write<float>((*value.camera_rotation_speed));
    }
    stream.write<bool>(value.snap_to_target.has_value());
    if (value.snap_to_target.has_value()) {
        stream.write<bool>((*value.snap_to_target));
    }
    stream.write<bool>(value.horizontal_rotation_limit.has_value());
    if (value.horizontal_rotation_limit.has_value()) {
        Serializer<Vec2>::serialize(stream, (*value.horizontal_rotation_limit));
    }
    stream.write<bool>(value.vertical_rotation_limit.has_value());
    if (value.vertical_rotation_limit.has_value()) {
        Serializer<Vec2>::serialize(stream, (*value.vertical_rotation_limit));
    }
    stream.write<bool>(value.continue_targeting.has_value());
    if (value.continue_targeting.has_value()) {
        stream.write<bool>((*value.continue_targeting));
    }
    stream.write<bool>(value.tracking_radius.has_value());
    if (value.tracking_radius.has_value()) {
        stream.write<float>((*value.tracking_radius));
    }
    stream.write<bool>(value.view_offset.has_value());
    if (value.view_offset.has_value()) {
        Serializer<Vec2>::serialize(stream, (*value.view_offset));
    }
    stream.write<bool>(value.entity_offset.has_value());
    if (value.entity_offset.has_value()) {
        Serializer<Vec3>::serialize(stream, (*value.entity_offset));
    }
    stream.write<bool>(value.radius.has_value());
    if (value.radius.has_value()) {
        stream.write<float>((*value.radius));
    }
    stream.write<bool>(value.yaw_limit_min.has_value());
    if (value.yaw_limit_min.has_value()) {
        stream.write<float>((*value.yaw_limit_min));
    }
    stream.write<bool>(value.yaw_limit_max.has_value());
    if (value.yaw_limit_max.has_value()) {
        stream.write<float>((*value.yaw_limit_max));
    }
    stream.write<bool>(value.listener.has_value());
    if (value.listener.has_value()) {
        stream.write<std::uint8_t>((*value.listener));
    }
    stream.write<bool>(value.player_effects.has_value());
    if (value.player_effects.has_value()) {
        stream.write<bool>((*value.player_effects));
    }
    stream.write<bool>(value.aim_assist.has_value());
    if (value.aim_assist.has_value()) {
        Serializer<v766::CameraAimAssistCommandPresetDefinition>::serialize(stream, (*value.aim_assist));
    }
    stream.write<bool>(value.control_scheme.has_value());
    if (value.control_scheme.has_value()) {
        stream.write<std::uint8_t>((*value.control_scheme));
    }
}

auto Serializer<v818::CameraPreset>::deserialize(BinaryReader &stream) -> std::expected<v818::CameraPreset, std::error_code>
{
    v818::CameraPreset out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.inherit_from = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.pos_x = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.pos_y = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.pos_z = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.rot_x = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.rot_y = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.camera_rotation_speed = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.snap_to_target = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec2 staged{};
            auto v = Serializer<Vec2>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.horizontal_rotation_limit = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec2 staged{};
            auto v = Serializer<Vec2>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.vertical_rotation_limit = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.continue_targeting = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.tracking_radius = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec2 staged{};
            auto v = Serializer<Vec2>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.view_offset = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec3 staged{};
            auto v = Serializer<Vec3>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.entity_offset = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.radius = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.yaw_limit_min = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.yaw_limit_max = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v818::CameraPreset::AudioListener staged{};
            auto v = stream.read<std::uint8_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<v818::CameraPreset::AudioListener>(*v);
            out.listener = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.player_effects = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v766::CameraAimAssistCommandPresetDefinition staged{};
            auto v = Serializer<v766::CameraAimAssistCommandPresetDefinition>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.aim_assist = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Scheme staged{};
            auto v = stream.read<std::uint8_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<Scheme>(*v);
            out.control_scheme = std::move(staged);
        }
    }
    return out;
}

void Serializer<v2193::CameraPreset>::serialize(BinaryWriter &stream, const v2193::CameraPreset &value)
{
    stream.write(value.name);
    stream.write(value.inherit_from);
    stream.write<bool>(value.pos_x.has_value());
    if (value.pos_x.has_value()) {
        stream.write<float>((*value.pos_x));
    }
    stream.write<bool>(value.pos_y.has_value());
    if (value.pos_y.has_value()) {
        stream.write<float>((*value.pos_y));
    }
    stream.write<bool>(value.pos_z.has_value());
    if (value.pos_z.has_value()) {
        stream.write<float>((*value.pos_z));
    }
    stream.write<bool>(value.rot_x.has_value());
    if (value.rot_x.has_value()) {
        stream.write<float>((*value.rot_x));
    }
    stream.write<bool>(value.rot_y.has_value());
    if (value.rot_y.has_value()) {
        stream.write<float>((*value.rot_y));
    }
    stream.write<bool>(value.camera_rotation_speed.has_value());
    if (value.camera_rotation_speed.has_value()) {
        stream.write<float>((*value.camera_rotation_speed));
    }
    stream.write<bool>(value.snap_to_target.has_value());
    if (value.snap_to_target.has_value()) {
        stream.write<bool>((*value.snap_to_target));
    }
    stream.write<bool>(value.horizontal_rotation_limit.has_value());
    if (value.horizontal_rotation_limit.has_value()) {
        Serializer<Vec2>::serialize(stream, (*value.horizontal_rotation_limit));
    }
    stream.write<bool>(value.vertical_rotation_limit.has_value());
    if (value.vertical_rotation_limit.has_value()) {
        Serializer<Vec2>::serialize(stream, (*value.vertical_rotation_limit));
    }
    stream.write<bool>(value.continue_targeting.has_value());
    if (value.continue_targeting.has_value()) {
        stream.write<bool>((*value.continue_targeting));
    }
    stream.write<bool>(value.tracking_radius.has_value());
    if (value.tracking_radius.has_value()) {
        stream.write<float>((*value.tracking_radius));
    }
    stream.write<bool>(value.view_offset.has_value());
    if (value.view_offset.has_value()) {
        Serializer<Vec2>::serialize(stream, (*value.view_offset));
    }
    stream.write<bool>(value.entity_offset.has_value());
    if (value.entity_offset.has_value()) {
        Serializer<Vec3>::serialize(stream, (*value.entity_offset));
    }
    stream.write<bool>(value.radius.has_value());
    if (value.radius.has_value()) {
        stream.write<float>((*value.radius));
    }
    stream.write<bool>(value.yaw_limit_min.has_value());
    if (value.yaw_limit_min.has_value()) {
        stream.write<float>((*value.yaw_limit_min));
    }
    stream.write<bool>(value.yaw_limit_max.has_value());
    if (value.yaw_limit_max.has_value()) {
        stream.write<float>((*value.yaw_limit_max));
    }
    stream.write<bool>(value.listener.has_value());
    if (value.listener.has_value()) {
        stream.write<std::uint8_t>((*value.listener));
    }
    stream.write<bool>(value.player_effects.has_value());
    if (value.player_effects.has_value()) {
        stream.write<bool>((*value.player_effects));
    }
    stream.write<bool>(value.aim_assist.has_value());
    if (value.aim_assist.has_value()) {
        Serializer<v766::CameraAimAssistCommandPresetDefinition>::serialize(stream, (*value.aim_assist));
    }
    stream.write<bool>(value.control_scheme.has_value());
    if (value.control_scheme.has_value()) {
        stream.write<std::uint8_t>((*value.control_scheme));
    }
    stream.write<bool>(value.apply_inherited_starting_rotation);
    stream.write<bool>(value.starting_rot.has_value());
    if (value.starting_rot.has_value()) {
        Serializer<Vec2>::serialize(stream, (*value.starting_rot));
    }
}

auto Serializer<v2193::CameraPreset>::deserialize(BinaryReader &stream) -> std::expected<v2193::CameraPreset, std::error_code>
{
    v2193::CameraPreset out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.inherit_from = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.pos_x = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.pos_y = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.pos_z = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.rot_x = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.rot_y = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.camera_rotation_speed = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.snap_to_target = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec2 staged{};
            auto v = Serializer<Vec2>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.horizontal_rotation_limit = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec2 staged{};
            auto v = Serializer<Vec2>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.vertical_rotation_limit = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.continue_targeting = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.tracking_radius = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec2 staged{};
            auto v = Serializer<Vec2>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.view_offset = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec3 staged{};
            auto v = Serializer<Vec3>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.entity_offset = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.radius = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.yaw_limit_min = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.yaw_limit_max = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v2193::CameraPreset::AudioListener staged{};
            auto v = stream.read<std::uint8_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<v2193::CameraPreset::AudioListener>(*v);
            out.listener = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.player_effects = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v766::CameraAimAssistCommandPresetDefinition staged{};
            auto v = Serializer<v766::CameraAimAssistCommandPresetDefinition>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.aim_assist = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Scheme staged{};
            auto v = stream.read<std::uint8_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<Scheme>(*v);
            out.control_scheme = std::move(staged);
        }
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.apply_inherited_starting_rotation = static_cast<bool>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec2 staged{};
            auto v = Serializer<Vec2>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.starting_rot = std::move(staged);
        }
    }
    return out;
}

void Serializer<base::CameraPresets>::serialize(BinaryWriter &stream, const base::CameraPresets &value)
{
    stream.writeVarInt<std::uint32_t>(value.presets.size());
    for (const auto &e0 : value.presets) {
        Serializer<base::CameraPreset>::serialize(stream, e0);
    }
}

auto Serializer<base::CameraPresets>::deserialize(BinaryReader &stream) -> std::expected<base::CameraPresets, std::error_code>
{
    base::CameraPresets out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.presets.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.presets.emplace_back();
            auto v = Serializer<base::CameraPreset>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.presets.back() = *v;
        }
    }
    return out;
}

void Serializer<v748::CameraPresets>::serialize(BinaryWriter &stream, const v748::CameraPresets &value)
{
    stream.writeVarInt<std::uint32_t>(value.presets.size());
    for (const auto &e0 : value.presets) {
        Serializer<v748::CameraPreset>::serialize(stream, e0);
    }
}

auto Serializer<v748::CameraPresets>::deserialize(BinaryReader &stream) -> std::expected<v748::CameraPresets, std::error_code>
{
    v748::CameraPresets out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.presets.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.presets.emplace_back();
            auto v = Serializer<v748::CameraPreset>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.presets.back() = *v;
        }
    }
    return out;
}

void Serializer<v766::CameraPresets>::serialize(BinaryWriter &stream, const v766::CameraPresets &value)
{
    stream.writeVarInt<std::uint32_t>(value.presets.size());
    for (const auto &e0 : value.presets) {
        Serializer<v766::CameraPreset>::serialize(stream, e0);
    }
}

auto Serializer<v766::CameraPresets>::deserialize(BinaryReader &stream) -> std::expected<v766::CameraPresets, std::error_code>
{
    v766::CameraPresets out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.presets.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.presets.emplace_back();
            auto v = Serializer<v766::CameraPreset>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.presets.back() = *v;
        }
    }
    return out;
}

void Serializer<v776::CameraPresets>::serialize(BinaryWriter &stream, const v776::CameraPresets &value)
{
    stream.writeVarInt<std::uint32_t>(value.presets.size());
    for (const auto &e0 : value.presets) {
        Serializer<v776::CameraPreset>::serialize(stream, e0);
    }
}

auto Serializer<v776::CameraPresets>::deserialize(BinaryReader &stream) -> std::expected<v776::CameraPresets, std::error_code>
{
    v776::CameraPresets out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.presets.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.presets.emplace_back();
            auto v = Serializer<v776::CameraPreset>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.presets.back() = *v;
        }
    }
    return out;
}

void Serializer<v800::CameraPresets>::serialize(BinaryWriter &stream, const v800::CameraPresets &value)
{
    stream.writeVarInt<std::uint32_t>(value.presets.size());
    for (const auto &e0 : value.presets) {
        Serializer<v800::CameraPreset>::serialize(stream, e0);
    }
}

auto Serializer<v800::CameraPresets>::deserialize(BinaryReader &stream) -> std::expected<v800::CameraPresets, std::error_code>
{
    v800::CameraPresets out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.presets.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.presets.emplace_back();
            auto v = Serializer<v800::CameraPreset>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.presets.back() = *v;
        }
    }
    return out;
}

void Serializer<v818::CameraPresets>::serialize(BinaryWriter &stream, const v818::CameraPresets &value)
{
    stream.writeVarInt<std::uint32_t>(value.presets.size());
    for (const auto &e0 : value.presets) {
        Serializer<v818::CameraPreset>::serialize(stream, e0);
    }
}

auto Serializer<v818::CameraPresets>::deserialize(BinaryReader &stream) -> std::expected<v818::CameraPresets, std::error_code>
{
    v818::CameraPresets out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.presets.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.presets.emplace_back();
            auto v = Serializer<v818::CameraPreset>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.presets.back() = *v;
        }
    }
    return out;
}

void Serializer<v2193::CameraPresets>::serialize(BinaryWriter &stream, const v2193::CameraPresets &value)
{
    stream.writeVarInt<std::uint32_t>(value.presets.size());
    for (const auto &e0 : value.presets) {
        Serializer<v2193::CameraPreset>::serialize(stream, e0);
    }
}

auto Serializer<v2193::CameraPresets>::deserialize(BinaryReader &stream) -> std::expected<v2193::CameraPresets, std::error_code>
{
    v2193::CameraPresets out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.presets.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.presets.emplace_back();
            auto v = Serializer<v2193::CameraPreset>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.presets.back() = *v;
        }
    }
    return out;
}

void Serializer<base::CameraPresetsPacket>::serialize(BinaryWriter &stream, const base::CameraPresetsPacket &value)
{
    Serializer<base::CameraPresets>::serialize(stream, value.camera_presets);
}

auto Serializer<base::CameraPresetsPacket>::deserialize(BinaryReader &stream) -> std::expected<base::CameraPresetsPacket, std::error_code>
{
    base::CameraPresetsPacket out;
    {
        auto v = Serializer<base::CameraPresets>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.camera_presets = *v;
    }
    return out;
}

void Serializer<v748::CameraPresetsPacket>::serialize(BinaryWriter &stream, const v748::CameraPresetsPacket &value)
{
    Serializer<v748::CameraPresets>::serialize(stream, value.camera_presets);
}

auto Serializer<v748::CameraPresetsPacket>::deserialize(BinaryReader &stream) -> std::expected<v748::CameraPresetsPacket, std::error_code>
{
    v748::CameraPresetsPacket out;
    {
        auto v = Serializer<v748::CameraPresets>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.camera_presets = *v;
    }
    return out;
}

void Serializer<v766::CameraPresetsPacket>::serialize(BinaryWriter &stream, const v766::CameraPresetsPacket &value)
{
    Serializer<v766::CameraPresets>::serialize(stream, value.camera_presets);
}

auto Serializer<v766::CameraPresetsPacket>::deserialize(BinaryReader &stream) -> std::expected<v766::CameraPresetsPacket, std::error_code>
{
    v766::CameraPresetsPacket out;
    {
        auto v = Serializer<v766::CameraPresets>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.camera_presets = *v;
    }
    return out;
}

void Serializer<v776::CameraPresetsPacket>::serialize(BinaryWriter &stream, const v776::CameraPresetsPacket &value)
{
    Serializer<v776::CameraPresets>::serialize(stream, value.camera_presets);
}

auto Serializer<v776::CameraPresetsPacket>::deserialize(BinaryReader &stream) -> std::expected<v776::CameraPresetsPacket, std::error_code>
{
    v776::CameraPresetsPacket out;
    {
        auto v = Serializer<v776::CameraPresets>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.camera_presets = *v;
    }
    return out;
}

void Serializer<v800::CameraPresetsPacket>::serialize(BinaryWriter &stream, const v800::CameraPresetsPacket &value)
{
    Serializer<v800::CameraPresets>::serialize(stream, value.camera_presets);
}

auto Serializer<v800::CameraPresetsPacket>::deserialize(BinaryReader &stream) -> std::expected<v800::CameraPresetsPacket, std::error_code>
{
    v800::CameraPresetsPacket out;
    {
        auto v = Serializer<v800::CameraPresets>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.camera_presets = *v;
    }
    return out;
}

void Serializer<v818::CameraPresetsPacket>::serialize(BinaryWriter &stream, const v818::CameraPresetsPacket &value)
{
    Serializer<v818::CameraPresets>::serialize(stream, value.camera_presets);
}

auto Serializer<v818::CameraPresetsPacket>::deserialize(BinaryReader &stream) -> std::expected<v818::CameraPresetsPacket, std::error_code>
{
    v818::CameraPresetsPacket out;
    {
        auto v = Serializer<v818::CameraPresets>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.camera_presets = *v;
    }
    return out;
}

void Serializer<v2193::CameraPresetsPacket>::serialize(BinaryWriter &stream, const v2193::CameraPresetsPacket &value)
{
    Serializer<v2193::CameraPresets>::serialize(stream, value.camera_presets);
}

auto Serializer<v2193::CameraPresetsPacket>::deserialize(BinaryReader &stream) -> std::expected<v2193::CameraPresetsPacket, std::error_code>
{
    v2193::CameraPresetsPacket out;
    {
        auto v = Serializer<v2193::CameraPresets>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.camera_presets = *v;
    }
    return out;
}

void Serializer<CameraPacket>::serialize(BinaryWriter &stream, const CameraPacket &value)
{
    stream.writeVarInt<std::int64_t>(value.camera_id);
    stream.writeVarInt<std::int64_t>(value.target_player_id);
}

auto Serializer<CameraPacket>::deserialize(BinaryReader &stream) -> std::expected<CameraPacket, std::error_code>
{
    CameraPacket out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.camera_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.target_player_id = static_cast<ActorUniqueID>(*v);
    }
    return out;
}

void Serializer<CameraShakePacket>::serialize(BinaryWriter &stream, const CameraShakePacket &value)
{
    stream.write<float>(value.intensity);
    stream.write<float>(value.seconds);
    stream.write<std::uint8_t>(value.shake_type);
    stream.write<std::uint8_t>(value.shake_action);
}

auto Serializer<CameraShakePacket>::deserialize(BinaryReader &stream) -> std::expected<CameraShakePacket, std::error_code>
{
    CameraShakePacket out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.intensity = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.seconds = static_cast<float>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.shake_type = static_cast<CameraShakeType>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.shake_action = static_cast<CameraShakeAction>(*v);
    }
    return out;
}

void Serializer<CameraAimAssistActorPriority::PriorityData>::serialize(BinaryWriter &stream, const CameraAimAssistActorPriority::PriorityData &value)
{
    stream.write<std::int32_t>(value.preset_index);
    stream.write<std::int32_t>(value.category_index);
    stream.write<std::int32_t>(value.actor_index);
    stream.write<std::int32_t>(value.priority_value);
}

auto Serializer<CameraAimAssistActorPriority::PriorityData>::deserialize(BinaryReader &stream) -> std::expected<CameraAimAssistActorPriority::PriorityData, std::error_code>
{
    CameraAimAssistActorPriority::PriorityData out;
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.preset_index = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.category_index = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.actor_index = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.priority_value = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<v924::CameraAimAssistActorPriorityPacket>::serialize(BinaryWriter &stream, const v924::CameraAimAssistActorPriorityPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.camera_aim_assist_actor_priority_list.size());
    for (const auto &e0 : value.camera_aim_assist_actor_priority_list) {
        Serializer<CameraAimAssistActorPriority::PriorityData>::serialize(stream, e0);
    }
}

auto Serializer<v924::CameraAimAssistActorPriorityPacket>::deserialize(BinaryReader &stream) -> std::expected<v924::CameraAimAssistActorPriorityPacket, std::error_code>
{
    v924::CameraAimAssistActorPriorityPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.camera_aim_assist_actor_priority_list.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.camera_aim_assist_actor_priority_list.emplace_back();
            auto v = Serializer<CameraAimAssistActorPriority::PriorityData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.camera_aim_assist_actor_priority_list.back() = *v;
        }
    }
    return out;
}

void Serializer<v776::ClientCameraAimAssistPacket>::serialize(BinaryWriter &stream, const v776::ClientCameraAimAssistPacket &value)
{
    stream.write(value.camera_preset_id);
    stream.write<std::uint8_t>(value.action);
    stream.write<bool>(value.allow_aim_assist);
}

auto Serializer<v776::ClientCameraAimAssistPacket>::deserialize(BinaryReader &stream) -> std::expected<v776::ClientCameraAimAssistPacket, std::error_code>
{
    v776::ClientCameraAimAssistPacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.camera_preset_id = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.action = static_cast<v776::ClientCameraAimAssistPacketAction>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.allow_aim_assist = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<base::CameraAimAssistPacket>::serialize(BinaryWriter &stream, const base::CameraAimAssistPacket &value)
{
    Serializer<Vec2>::serialize(stream, value.view_angle);
    stream.write<float>(value.distance);
    stream.write<std::uint8_t>(value.target_mode);
    stream.write<std::uint8_t>(value.action);
}

auto Serializer<base::CameraAimAssistPacket>::deserialize(BinaryReader &stream) -> std::expected<base::CameraAimAssistPacket, std::error_code>
{
    base::CameraAimAssistPacket out;
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.view_angle = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.distance = static_cast<float>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.target_mode = static_cast<base::CameraAimAssistPacket::TargetMode>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.action = static_cast<base::CameraAimAssistPacket::Action>(*v);
    }
    return out;
}

void Serializer<v766::CameraAimAssistPacket>::serialize(BinaryWriter &stream, const v766::CameraAimAssistPacket &value)
{
    stream.write(value.preset_id);
    Serializer<Vec2>::serialize(stream, value.view_angle);
    stream.write<float>(value.distance);
    stream.write<std::uint8_t>(value.target_mode);
    stream.write<std::uint8_t>(value.action);
}

auto Serializer<v766::CameraAimAssistPacket>::deserialize(BinaryReader &stream) -> std::expected<v766::CameraAimAssistPacket, std::error_code>
{
    v766::CameraAimAssistPacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.preset_id = *v;
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.view_angle = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.distance = static_cast<float>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.target_mode = static_cast<v766::CameraAimAssistPacket::TargetMode>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.action = static_cast<v766::CameraAimAssistPacket::Action>(*v);
    }
    return out;
}

void Serializer<v827::CameraAimAssistPacket>::serialize(BinaryWriter &stream, const v827::CameraAimAssistPacket &value)
{
    stream.write(value.preset_id);
    Serializer<Vec2>::serialize(stream, value.view_angle);
    stream.write<float>(value.distance);
    stream.write<std::uint8_t>(value.target_mode);
    stream.write<std::uint8_t>(value.action);
    stream.write<bool>(value.show_debug_render);
}

auto Serializer<v827::CameraAimAssistPacket>::deserialize(BinaryReader &stream) -> std::expected<v827::CameraAimAssistPacket, std::error_code>
{
    v827::CameraAimAssistPacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.preset_id = *v;
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.view_angle = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.distance = static_cast<float>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.target_mode = static_cast<v827::CameraAimAssistPacket::TargetMode>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.action = static_cast<v827::CameraAimAssistPacket::Action>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.show_debug_render = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v766::CameraAimAssistCategoryPriorities>::serialize(BinaryWriter &stream, const v766::CameraAimAssistCategoryPriorities &value)
{
    stream.writeVarInt<std::uint32_t>(value.entities.size());
    for (const auto &[k0, v0] : value.entities) {
        stream.write(k0);
        stream.write<std::int32_t>(v0);
    }
    stream.writeVarInt<std::uint32_t>(value.blocks.size());
    for (const auto &[k0, v0] : value.blocks) {
        stream.write(k0);
        stream.write<std::int32_t>(v0);
    }
    stream.write<bool>(value.entity_default.has_value());
    if (value.entity_default.has_value()) {
        stream.write<std::int32_t>((*value.entity_default));
    }
    stream.write<bool>(value.block_default.has_value());
    if (value.block_default.has_value()) {
        stream.write<std::int32_t>((*value.block_default));
    }
}

auto Serializer<v766::CameraAimAssistCategoryPriorities>::deserialize(BinaryReader &stream) -> std::expected<v766::CameraAimAssistCategoryPriorities, std::error_code>
{
    v766::CameraAimAssistCategoryPriorities out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.entities.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            std::string key0{};
            {
                auto v = stream.read<std::string>();
                if (!v) return std::unexpected(v.error());
                key0 = *v;
            }
            auto v = stream.read<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            out.entities[key0] = static_cast<std::int32_t>(*v);
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.blocks.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            std::string key0{};
            {
                auto v = stream.read<std::string>();
                if (!v) return std::unexpected(v.error());
                key0 = *v;
            }
            auto v = stream.read<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            out.blocks[key0] = static_cast<std::int32_t>(*v);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::int32_t staged{};
            auto v = stream.read<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<std::int32_t>(*v);
            out.entity_default = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::int32_t staged{};
            auto v = stream.read<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<std::int32_t>(*v);
            out.block_default = std::move(staged);
        }
    }
    return out;
}

void Serializer<v898::CameraAimAssistCategoryPriorities>::serialize(BinaryWriter &stream, const v898::CameraAimAssistCategoryPriorities &value)
{
    stream.writeVarInt<std::uint32_t>(value.entities.size());
    for (const auto &[k0, v0] : value.entities) {
        stream.write(k0);
        stream.write<std::int32_t>(v0);
    }
    stream.writeVarInt<std::uint32_t>(value.blocks.size());
    for (const auto &[k0, v0] : value.blocks) {
        stream.write(k0);
        stream.write<std::int32_t>(v0);
    }
    stream.writeVarInt<std::uint32_t>(value.block_tags.size());
    for (const auto &[k0, v0] : value.block_tags) {
        stream.write(k0);
        stream.write<std::int32_t>(v0);
    }
    stream.write<bool>(value.entity_default.has_value());
    if (value.entity_default.has_value()) {
        stream.write<std::int32_t>((*value.entity_default));
    }
    stream.write<bool>(value.block_default.has_value());
    if (value.block_default.has_value()) {
        stream.write<std::int32_t>((*value.block_default));
    }
}

auto Serializer<v898::CameraAimAssistCategoryPriorities>::deserialize(BinaryReader &stream) -> std::expected<v898::CameraAimAssistCategoryPriorities, std::error_code>
{
    v898::CameraAimAssistCategoryPriorities out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.entities.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            std::string key0{};
            {
                auto v = stream.read<std::string>();
                if (!v) return std::unexpected(v.error());
                key0 = *v;
            }
            auto v = stream.read<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            out.entities[key0] = static_cast<std::int32_t>(*v);
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.blocks.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            std::string key0{};
            {
                auto v = stream.read<std::string>();
                if (!v) return std::unexpected(v.error());
                key0 = *v;
            }
            auto v = stream.read<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            out.blocks[key0] = static_cast<std::int32_t>(*v);
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.block_tags.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            std::string key0{};
            {
                auto v = stream.read<std::string>();
                if (!v) return std::unexpected(v.error());
                key0 = *v;
            }
            auto v = stream.read<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            out.block_tags[key0] = static_cast<std::int32_t>(*v);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::int32_t staged{};
            auto v = stream.read<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<std::int32_t>(*v);
            out.entity_default = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::int32_t staged{};
            auto v = stream.read<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<std::int32_t>(*v);
            out.block_default = std::move(staged);
        }
    }
    return out;
}

void Serializer<v924::CameraAimAssistCategoryPriorities>::serialize(BinaryWriter &stream, const v924::CameraAimAssistCategoryPriorities &value)
{
    stream.writeVarInt<std::uint32_t>(value.entities.size());
    for (const auto &[k0, v0] : value.entities) {
        stream.write(k0);
        stream.write<std::int32_t>(v0);
    }
    stream.writeVarInt<std::uint32_t>(value.blocks.size());
    for (const auto &[k0, v0] : value.blocks) {
        stream.write(k0);
        stream.write<std::int32_t>(v0);
    }
    stream.writeVarInt<std::uint32_t>(value.block_tags.size());
    for (const auto &[k0, v0] : value.block_tags) {
        stream.write(k0);
        stream.write<std::int32_t>(v0);
    }
    stream.writeVarInt<std::uint32_t>(value.entity_type_families.size());
    for (const auto &[k0, v0] : value.entity_type_families) {
        stream.write(k0);
        stream.write<std::int32_t>(v0);
    }
    stream.write<bool>(value.entity_default.has_value());
    if (value.entity_default.has_value()) {
        stream.write<std::int32_t>((*value.entity_default));
    }
    stream.write<bool>(value.block_default.has_value());
    if (value.block_default.has_value()) {
        stream.write<std::int32_t>((*value.block_default));
    }
}

auto Serializer<v924::CameraAimAssistCategoryPriorities>::deserialize(BinaryReader &stream) -> std::expected<v924::CameraAimAssistCategoryPriorities, std::error_code>
{
    v924::CameraAimAssistCategoryPriorities out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.entities.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            std::string key0{};
            {
                auto v = stream.read<std::string>();
                if (!v) return std::unexpected(v.error());
                key0 = *v;
            }
            auto v = stream.read<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            out.entities[key0] = static_cast<std::int32_t>(*v);
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.blocks.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            std::string key0{};
            {
                auto v = stream.read<std::string>();
                if (!v) return std::unexpected(v.error());
                key0 = *v;
            }
            auto v = stream.read<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            out.blocks[key0] = static_cast<std::int32_t>(*v);
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.block_tags.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            std::string key0{};
            {
                auto v = stream.read<std::string>();
                if (!v) return std::unexpected(v.error());
                key0 = *v;
            }
            auto v = stream.read<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            out.block_tags[key0] = static_cast<std::int32_t>(*v);
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.entity_type_families.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            std::string key0{};
            {
                auto v = stream.read<std::string>();
                if (!v) return std::unexpected(v.error());
                key0 = *v;
            }
            auto v = stream.read<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            out.entity_type_families[key0] = static_cast<std::int32_t>(*v);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::int32_t staged{};
            auto v = stream.read<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<std::int32_t>(*v);
            out.entity_default = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::int32_t staged{};
            auto v = stream.read<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<std::int32_t>(*v);
            out.block_default = std::move(staged);
        }
    }
    return out;
}

void Serializer<v766::CameraAimAssistCategoryDefinition>::serialize(BinaryWriter &stream, const v766::CameraAimAssistCategoryDefinition &value)
{
    stream.write(value.name);
    Serializer<v766::CameraAimAssistCategoryPriorities>::serialize(stream, value.priorities);
}

auto Serializer<v766::CameraAimAssistCategoryDefinition>::deserialize(BinaryReader &stream) -> std::expected<v766::CameraAimAssistCategoryDefinition, std::error_code>
{
    v766::CameraAimAssistCategoryDefinition out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = Serializer<v766::CameraAimAssistCategoryPriorities>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.priorities = *v;
    }
    return out;
}

void Serializer<v898::CameraAimAssistCategoryDefinition>::serialize(BinaryWriter &stream, const v898::CameraAimAssistCategoryDefinition &value)
{
    stream.write(value.name);
    Serializer<v898::CameraAimAssistCategoryPriorities>::serialize(stream, value.priorities);
}

auto Serializer<v898::CameraAimAssistCategoryDefinition>::deserialize(BinaryReader &stream) -> std::expected<v898::CameraAimAssistCategoryDefinition, std::error_code>
{
    v898::CameraAimAssistCategoryDefinition out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = Serializer<v898::CameraAimAssistCategoryPriorities>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.priorities = *v;
    }
    return out;
}

void Serializer<v924::CameraAimAssistCategoryDefinition>::serialize(BinaryWriter &stream, const v924::CameraAimAssistCategoryDefinition &value)
{
    stream.write(value.name);
    Serializer<v924::CameraAimAssistCategoryPriorities>::serialize(stream, value.priorities);
}

auto Serializer<v924::CameraAimAssistCategoryDefinition>::deserialize(BinaryReader &stream) -> std::expected<v924::CameraAimAssistCategoryDefinition, std::error_code>
{
    v924::CameraAimAssistCategoryDefinition out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = Serializer<v924::CameraAimAssistCategoryPriorities>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.priorities = *v;
    }
    return out;
}

void Serializer<v898::CameraAimAssistPresetExclusionDefinition>::serialize(BinaryWriter &stream, const v898::CameraAimAssistPresetExclusionDefinition &value)
{
    stream.writeVarInt<std::uint32_t>(value.block_exclusion_list.size());
    for (const auto &e0 : value.block_exclusion_list) {
        stream.write(e0);
    }
    stream.writeVarInt<std::uint32_t>(value.actor_exclusion_list.size());
    for (const auto &e0 : value.actor_exclusion_list) {
        stream.write(e0);
    }
    stream.writeVarInt<std::uint32_t>(value.block_tag_exclusion_list.size());
    for (const auto &e0 : value.block_tag_exclusion_list) {
        stream.write(e0);
    }
}

auto Serializer<v898::CameraAimAssistPresetExclusionDefinition>::deserialize(BinaryReader &stream) -> std::expected<v898::CameraAimAssistPresetExclusionDefinition, std::error_code>
{
    v898::CameraAimAssistPresetExclusionDefinition out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.block_exclusion_list.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.block_exclusion_list.emplace_back();
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.block_exclusion_list.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.actor_exclusion_list.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.actor_exclusion_list.emplace_back();
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.actor_exclusion_list.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.block_tag_exclusion_list.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.block_tag_exclusion_list.emplace_back();
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.block_tag_exclusion_list.back() = *v;
        }
    }
    return out;
}

void Serializer<v924::CameraAimAssistPresetExclusionDefinition>::serialize(BinaryWriter &stream, const v924::CameraAimAssistPresetExclusionDefinition &value)
{
    stream.writeVarInt<std::uint32_t>(value.block_exclusion_list.size());
    for (const auto &e0 : value.block_exclusion_list) {
        stream.write(e0);
    }
    stream.writeVarInt<std::uint32_t>(value.actor_exclusion_list.size());
    for (const auto &e0 : value.actor_exclusion_list) {
        stream.write(e0);
    }
    stream.writeVarInt<std::uint32_t>(value.block_tag_exclusion_list.size());
    for (const auto &e0 : value.block_tag_exclusion_list) {
        stream.write(e0);
    }
    stream.writeVarInt<std::uint32_t>(value.entity_type_family_exclusion_list.size());
    for (const auto &e0 : value.entity_type_family_exclusion_list) {
        stream.write(e0);
    }
}

auto Serializer<v924::CameraAimAssistPresetExclusionDefinition>::deserialize(BinaryReader &stream) -> std::expected<v924::CameraAimAssistPresetExclusionDefinition, std::error_code>
{
    v924::CameraAimAssistPresetExclusionDefinition out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.block_exclusion_list.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.block_exclusion_list.emplace_back();
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.block_exclusion_list.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.actor_exclusion_list.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.actor_exclusion_list.emplace_back();
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.actor_exclusion_list.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.block_tag_exclusion_list.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.block_tag_exclusion_list.emplace_back();
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.block_tag_exclusion_list.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.entity_type_family_exclusion_list.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.entity_type_family_exclusion_list.emplace_back();
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.entity_type_family_exclusion_list.back() = *v;
        }
    }
    return out;
}

void Serializer<v766::CameraAimAssistPresetDefinition>::serialize(BinaryWriter &stream, const v766::CameraAimAssistPresetDefinition &value)
{
    stream.write(value.identifier);
    stream.write(value.categories);
    stream.writeVarInt<std::uint32_t>(value.exclusion_list.size());
    for (const auto &e0 : value.exclusion_list) {
        stream.write(e0);
    }
    stream.writeVarInt<std::uint32_t>(value.liquid_targeting_list.size());
    for (const auto &e0 : value.liquid_targeting_list) {
        stream.write(e0);
    }
    stream.writeVarInt<std::uint32_t>(value.item_settings.size());
    for (const auto &[k0, v0] : value.item_settings) {
        stream.write(k0);
        stream.write(v0);
    }
    stream.write<bool>(value.default_item_settings.has_value());
    if (value.default_item_settings.has_value()) {
        stream.write((*value.default_item_settings));
    }
    stream.write<bool>(value.hand_settings.has_value());
    if (value.hand_settings.has_value()) {
        stream.write((*value.hand_settings));
    }
}

auto Serializer<v766::CameraAimAssistPresetDefinition>::deserialize(BinaryReader &stream) -> std::expected<v766::CameraAimAssistPresetDefinition, std::error_code>
{
    v766::CameraAimAssistPresetDefinition out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.identifier = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.categories = *v;
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.exclusion_list.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.exclusion_list.emplace_back();
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.exclusion_list.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.liquid_targeting_list.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.liquid_targeting_list.emplace_back();
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.liquid_targeting_list.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.item_settings.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            std::string key0{};
            {
                auto v = stream.read<std::string>();
                if (!v) return std::unexpected(v.error());
                key0 = *v;
            }
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.item_settings[key0] = *v;
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::string staged{};
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.default_item_settings = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::string staged{};
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.hand_settings = std::move(staged);
        }
    }
    return out;
}

void Serializer<v776::CameraAimAssistPresetDefinition>::serialize(BinaryWriter &stream, const v776::CameraAimAssistPresetDefinition &value)
{
    stream.write(value.identifier);
    stream.writeVarInt<std::uint32_t>(value.exclusion_list.size());
    for (const auto &e0 : value.exclusion_list) {
        stream.write(e0);
    }
    stream.writeVarInt<std::uint32_t>(value.liquid_targeting_list.size());
    for (const auto &e0 : value.liquid_targeting_list) {
        stream.write(e0);
    }
    stream.writeVarInt<std::uint32_t>(value.item_settings.size());
    for (const auto &[k0, v0] : value.item_settings) {
        stream.write(k0);
        stream.write(v0);
    }
    stream.write<bool>(value.default_item_settings.has_value());
    if (value.default_item_settings.has_value()) {
        stream.write((*value.default_item_settings));
    }
    stream.write<bool>(value.hand_settings.has_value());
    if (value.hand_settings.has_value()) {
        stream.write((*value.hand_settings));
    }
}

auto Serializer<v776::CameraAimAssistPresetDefinition>::deserialize(BinaryReader &stream) -> std::expected<v776::CameraAimAssistPresetDefinition, std::error_code>
{
    v776::CameraAimAssistPresetDefinition out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.identifier = *v;
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.exclusion_list.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.exclusion_list.emplace_back();
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.exclusion_list.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.liquid_targeting_list.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.liquid_targeting_list.emplace_back();
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.liquid_targeting_list.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.item_settings.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            std::string key0{};
            {
                auto v = stream.read<std::string>();
                if (!v) return std::unexpected(v.error());
                key0 = *v;
            }
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.item_settings[key0] = *v;
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::string staged{};
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.default_item_settings = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::string staged{};
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.hand_settings = std::move(staged);
        }
    }
    return out;
}

void Serializer<v898::CameraAimAssistPresetDefinition>::serialize(BinaryWriter &stream, const v898::CameraAimAssistPresetDefinition &value)
{
    stream.write(value.identifier);
    Serializer<v898::CameraAimAssistPresetExclusionDefinition>::serialize(stream, value.exclusion_settings);
    stream.writeVarInt<std::uint32_t>(value.liquid_targeting_list.size());
    for (const auto &e0 : value.liquid_targeting_list) {
        stream.write(e0);
    }
    stream.writeVarInt<std::uint32_t>(value.item_settings.size());
    for (const auto &[k0, v0] : value.item_settings) {
        stream.write(k0);
        stream.write(v0);
    }
    stream.write<bool>(value.default_item_settings.has_value());
    if (value.default_item_settings.has_value()) {
        stream.write((*value.default_item_settings));
    }
    stream.write<bool>(value.hand_settings.has_value());
    if (value.hand_settings.has_value()) {
        stream.write((*value.hand_settings));
    }
}

auto Serializer<v898::CameraAimAssistPresetDefinition>::deserialize(BinaryReader &stream) -> std::expected<v898::CameraAimAssistPresetDefinition, std::error_code>
{
    v898::CameraAimAssistPresetDefinition out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.identifier = *v;
    }
    {
        auto v = Serializer<v898::CameraAimAssistPresetExclusionDefinition>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.exclusion_settings = *v;
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.liquid_targeting_list.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.liquid_targeting_list.emplace_back();
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.liquid_targeting_list.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.item_settings.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            std::string key0{};
            {
                auto v = stream.read<std::string>();
                if (!v) return std::unexpected(v.error());
                key0 = *v;
            }
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.item_settings[key0] = *v;
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::string staged{};
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.default_item_settings = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::string staged{};
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.hand_settings = std::move(staged);
        }
    }
    return out;
}

void Serializer<v924::CameraAimAssistPresetDefinition>::serialize(BinaryWriter &stream, const v924::CameraAimAssistPresetDefinition &value)
{
    stream.write(value.identifier);
    Serializer<v924::CameraAimAssistPresetExclusionDefinition>::serialize(stream, value.exclusion_settings);
    stream.writeVarInt<std::uint32_t>(value.liquid_targeting_list.size());
    for (const auto &e0 : value.liquid_targeting_list) {
        stream.write(e0);
    }
    stream.writeVarInt<std::uint32_t>(value.item_settings.size());
    for (const auto &[k0, v0] : value.item_settings) {
        stream.write(k0);
        stream.write(v0);
    }
    stream.write<bool>(value.default_item_settings.has_value());
    if (value.default_item_settings.has_value()) {
        stream.write((*value.default_item_settings));
    }
    stream.write<bool>(value.hand_settings.has_value());
    if (value.hand_settings.has_value()) {
        stream.write((*value.hand_settings));
    }
}

auto Serializer<v924::CameraAimAssistPresetDefinition>::deserialize(BinaryReader &stream) -> std::expected<v924::CameraAimAssistPresetDefinition, std::error_code>
{
    v924::CameraAimAssistPresetDefinition out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.identifier = *v;
    }
    {
        auto v = Serializer<v924::CameraAimAssistPresetExclusionDefinition>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.exclusion_settings = *v;
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.liquid_targeting_list.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.liquid_targeting_list.emplace_back();
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.liquid_targeting_list.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.item_settings.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            std::string key0{};
            {
                auto v = stream.read<std::string>();
                if (!v) return std::unexpected(v.error());
                key0 = *v;
            }
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.item_settings[key0] = *v;
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::string staged{};
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.default_item_settings = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::string staged{};
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.hand_settings = std::move(staged);
        }
    }
    return out;
}

void Serializer<v766::CameraAimAssistCategoriesDefinition>::serialize(BinaryWriter &stream, const v766::CameraAimAssistCategoriesDefinition &value)
{
    stream.write(value.identifier);
    stream.writeVarInt<std::uint32_t>(value.categories.size());
    for (const auto &e0 : value.categories) {
        Serializer<v766::CameraAimAssistCategoryDefinition>::serialize(stream, e0);
    }
}

auto Serializer<v766::CameraAimAssistCategoriesDefinition>::deserialize(BinaryReader &stream) -> std::expected<v766::CameraAimAssistCategoriesDefinition, std::error_code>
{
    v766::CameraAimAssistCategoriesDefinition out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.identifier = *v;
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.categories.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.categories.emplace_back();
            auto v = Serializer<v766::CameraAimAssistCategoryDefinition>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.categories.back() = *v;
        }
    }
    return out;
}

void Serializer<v766::CameraAimAssistPresetsPacket>::serialize(BinaryWriter &stream, const v766::CameraAimAssistPresetsPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.categories.size());
    for (const auto &e0 : value.categories) {
        Serializer<v766::CameraAimAssistCategoriesDefinition>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.presets.size());
    for (const auto &e0 : value.presets) {
        Serializer<v766::CameraAimAssistPresetDefinition>::serialize(stream, e0);
    }
}

auto Serializer<v766::CameraAimAssistPresetsPacket>::deserialize(BinaryReader &stream) -> std::expected<v766::CameraAimAssistPresetsPacket, std::error_code>
{
    v766::CameraAimAssistPresetsPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.categories.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.categories.emplace_back();
            auto v = Serializer<v766::CameraAimAssistCategoriesDefinition>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.categories.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.presets.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.presets.emplace_back();
            auto v = Serializer<v766::CameraAimAssistPresetDefinition>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.presets.back() = *v;
        }
    }
    return out;
}

void Serializer<v776::CameraAimAssistPresetsPacket>::serialize(BinaryWriter &stream, const v776::CameraAimAssistPresetsPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.categories.size());
    for (const auto &e0 : value.categories) {
        Serializer<v766::CameraAimAssistCategoryDefinition>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.presets.size());
    for (const auto &e0 : value.presets) {
        Serializer<v776::CameraAimAssistPresetDefinition>::serialize(stream, e0);
    }
    stream.write<std::uint8_t>(value.operation);
}

auto Serializer<v776::CameraAimAssistPresetsPacket>::deserialize(BinaryReader &stream) -> std::expected<v776::CameraAimAssistPresetsPacket, std::error_code>
{
    v776::CameraAimAssistPresetsPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.categories.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.categories.emplace_back();
            auto v = Serializer<v766::CameraAimAssistCategoryDefinition>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.categories.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.presets.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.presets.emplace_back();
            auto v = Serializer<v776::CameraAimAssistPresetDefinition>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.presets.back() = *v;
        }
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.operation = static_cast<v776::CameraAimAssistPresetsPacketOperation>(*v);
    }
    return out;
}

void Serializer<v898::CameraAimAssistPresetsPacket>::serialize(BinaryWriter &stream, const v898::CameraAimAssistPresetsPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.categories.size());
    for (const auto &e0 : value.categories) {
        Serializer<v898::CameraAimAssistCategoryDefinition>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.presets.size());
    for (const auto &e0 : value.presets) {
        Serializer<v898::CameraAimAssistPresetDefinition>::serialize(stream, e0);
    }
    stream.write<std::uint8_t>(value.operation);
}

auto Serializer<v898::CameraAimAssistPresetsPacket>::deserialize(BinaryReader &stream) -> std::expected<v898::CameraAimAssistPresetsPacket, std::error_code>
{
    v898::CameraAimAssistPresetsPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.categories.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.categories.emplace_back();
            auto v = Serializer<v898::CameraAimAssistCategoryDefinition>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.categories.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.presets.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.presets.emplace_back();
            auto v = Serializer<v898::CameraAimAssistPresetDefinition>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.presets.back() = *v;
        }
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.operation = static_cast<v776::CameraAimAssistPresetsPacketOperation>(*v);
    }
    return out;
}

void Serializer<v924::CameraAimAssistPresetsPacket>::serialize(BinaryWriter &stream, const v924::CameraAimAssistPresetsPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.categories.size());
    for (const auto &e0 : value.categories) {
        Serializer<v924::CameraAimAssistCategoryDefinition>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.presets.size());
    for (const auto &e0 : value.presets) {
        Serializer<v924::CameraAimAssistPresetDefinition>::serialize(stream, e0);
    }
    stream.write<std::uint8_t>(value.operation);
}

auto Serializer<v924::CameraAimAssistPresetsPacket>::deserialize(BinaryReader &stream) -> std::expected<v924::CameraAimAssistPresetsPacket, std::error_code>
{
    v924::CameraAimAssistPresetsPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.categories.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.categories.emplace_back();
            auto v = Serializer<v924::CameraAimAssistCategoryDefinition>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.categories.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.presets.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.presets.emplace_back();
            auto v = Serializer<v924::CameraAimAssistPresetDefinition>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.presets.back() = *v;
        }
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.operation = static_cast<v776::CameraAimAssistPresetsPacketOperation>(*v);
    }
    return out;
}

void Serializer<base::CameraInstructionOptions::SetInstruction::EaseOption>::serialize(BinaryWriter &stream, const base::CameraInstructionOptions::SetInstruction::EaseOption &value)
{
    stream.write<std::uint8_t>(value.easing_type);
    stream.write<float>(value.easing_time);
}

auto Serializer<base::CameraInstructionOptions::SetInstruction::EaseOption>::deserialize(BinaryReader &stream) -> std::expected<base::CameraInstructionOptions::SetInstruction::EaseOption, std::error_code>
{
    base::CameraInstructionOptions::SetInstruction::EaseOption out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.easing_type = static_cast<EasingType>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.easing_time = static_cast<float>(*v);
    }
    return out;
}

void Serializer<base::CameraInstructionOptions::SetInstruction::PosOption>::serialize(BinaryWriter &stream, const base::CameraInstructionOptions::SetInstruction::PosOption &value)
{
    Serializer<Vec3>::serialize(stream, value.pos);
}

auto Serializer<base::CameraInstructionOptions::SetInstruction::PosOption>::deserialize(BinaryReader &stream) -> std::expected<base::CameraInstructionOptions::SetInstruction::PosOption, std::error_code>
{
    base::CameraInstructionOptions::SetInstruction::PosOption out;
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    return out;
}

void Serializer<base::CameraInstructionOptions::SetInstruction::RotOption>::serialize(BinaryWriter &stream, const base::CameraInstructionOptions::SetInstruction::RotOption &value)
{
    stream.write<float>(value.rot_x);
    stream.write<float>(value.rot_y);
}

auto Serializer<base::CameraInstructionOptions::SetInstruction::RotOption>::deserialize(BinaryReader &stream) -> std::expected<base::CameraInstructionOptions::SetInstruction::RotOption, std::error_code>
{
    base::CameraInstructionOptions::SetInstruction::RotOption out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.rot_x = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.rot_y = static_cast<float>(*v);
    }
    return out;
}

void Serializer<base::CameraInstructionOptions::SetInstruction::FacingOption>::serialize(BinaryWriter &stream, const base::CameraInstructionOptions::SetInstruction::FacingOption &value)
{
    Serializer<Vec3>::serialize(stream, value.facing_pos);
}

auto Serializer<base::CameraInstructionOptions::SetInstruction::FacingOption>::deserialize(BinaryReader &stream) -> std::expected<base::CameraInstructionOptions::SetInstruction::FacingOption, std::error_code>
{
    base::CameraInstructionOptions::SetInstruction::FacingOption out;
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.facing_pos = *v;
    }
    return out;
}

void Serializer<base::CameraInstructionOptions::SetInstruction::ViewOffsetOption>::serialize(BinaryWriter &stream, const base::CameraInstructionOptions::SetInstruction::ViewOffsetOption &value)
{
    stream.write<float>(value.view_offset_x);
    stream.write<float>(value.view_offset_y);
}

auto Serializer<base::CameraInstructionOptions::SetInstruction::ViewOffsetOption>::deserialize(BinaryReader &stream) -> std::expected<base::CameraInstructionOptions::SetInstruction::ViewOffsetOption, std::error_code>
{
    base::CameraInstructionOptions::SetInstruction::ViewOffsetOption out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.view_offset_x = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.view_offset_y = static_cast<float>(*v);
    }
    return out;
}

void Serializer<base::CameraInstructionOptions::SetInstruction::EntityOffsetOption>::serialize(BinaryWriter &stream, const base::CameraInstructionOptions::SetInstruction::EntityOffsetOption &value)
{
    stream.write<float>(value.entity_offset_x);
    stream.write<float>(value.entity_offset_y);
    stream.write<float>(value.entity_offset_z);
}

auto Serializer<base::CameraInstructionOptions::SetInstruction::EntityOffsetOption>::deserialize(BinaryReader &stream) -> std::expected<base::CameraInstructionOptions::SetInstruction::EntityOffsetOption, std::error_code>
{
    base::CameraInstructionOptions::SetInstruction::EntityOffsetOption out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.entity_offset_x = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.entity_offset_y = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.entity_offset_z = static_cast<float>(*v);
    }
    return out;
}

void Serializer<base::CameraInstructionOptions::SetInstruction>::serialize(BinaryWriter &stream, const base::CameraInstructionOptions::SetInstruction &value)
{
    stream.write<std::uint32_t>(value.preset_index);
    stream.write<bool>(value.ease.has_value());
    if (value.ease.has_value()) {
        Serializer<base::CameraInstructionOptions::SetInstruction::EaseOption>::serialize(stream, (*value.ease));
    }
    stream.write<bool>(value.pos.has_value());
    if (value.pos.has_value()) {
        Serializer<base::CameraInstructionOptions::SetInstruction::PosOption>::serialize(stream, (*value.pos));
    }
    stream.write<bool>(value.rot.has_value());
    if (value.rot.has_value()) {
        Serializer<base::CameraInstructionOptions::SetInstruction::RotOption>::serialize(stream, (*value.rot));
    }
    stream.write<bool>(value.facing.has_value());
    if (value.facing.has_value()) {
        Serializer<base::CameraInstructionOptions::SetInstruction::FacingOption>::serialize(stream, (*value.facing));
    }
    stream.write<bool>(value.view_offset.has_value());
    if (value.view_offset.has_value()) {
        Serializer<base::CameraInstructionOptions::SetInstruction::ViewOffsetOption>::serialize(stream, (*value.view_offset));
    }
    stream.write<bool>(value.default_.has_value());
    if (value.default_.has_value()) {
        stream.write<bool>((*value.default_));
    }
}

auto Serializer<base::CameraInstructionOptions::SetInstruction>::deserialize(BinaryReader &stream) -> std::expected<base::CameraInstructionOptions::SetInstruction, std::error_code>
{
    base::CameraInstructionOptions::SetInstruction out;
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.preset_index = static_cast<std::uint32_t>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            base::CameraInstructionOptions::SetInstruction::EaseOption staged{};
            auto v = Serializer<base::CameraInstructionOptions::SetInstruction::EaseOption>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.ease = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            base::CameraInstructionOptions::SetInstruction::PosOption staged{};
            auto v = Serializer<base::CameraInstructionOptions::SetInstruction::PosOption>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.pos = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            base::CameraInstructionOptions::SetInstruction::RotOption staged{};
            auto v = Serializer<base::CameraInstructionOptions::SetInstruction::RotOption>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.rot = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            base::CameraInstructionOptions::SetInstruction::FacingOption staged{};
            auto v = Serializer<base::CameraInstructionOptions::SetInstruction::FacingOption>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.facing = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            base::CameraInstructionOptions::SetInstruction::ViewOffsetOption staged{};
            auto v = Serializer<base::CameraInstructionOptions::SetInstruction::ViewOffsetOption>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.view_offset = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.default_ = std::move(staged);
        }
    }
    return out;
}

void Serializer<base::CameraInstructionOptions::FadeInstruction::TimeOption>::serialize(BinaryWriter &stream, const base::CameraInstructionOptions::FadeInstruction::TimeOption &value)
{
    stream.write<float>(value.fade_in_time);
    stream.write<float>(value.hold_time);
    stream.write<float>(value.fade_out_time);
}

auto Serializer<base::CameraInstructionOptions::FadeInstruction::TimeOption>::deserialize(BinaryReader &stream) -> std::expected<base::CameraInstructionOptions::FadeInstruction::TimeOption, std::error_code>
{
    base::CameraInstructionOptions::FadeInstruction::TimeOption out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.fade_in_time = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.hold_time = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.fade_out_time = static_cast<float>(*v);
    }
    return out;
}

void Serializer<base::CameraInstructionOptions::FadeInstruction::ColorOption>::serialize(BinaryWriter &stream, const base::CameraInstructionOptions::FadeInstruction::ColorOption &value)
{
    stream.write<float>(value.red);
    stream.write<float>(value.green);
    stream.write<float>(value.blue);
}

auto Serializer<base::CameraInstructionOptions::FadeInstruction::ColorOption>::deserialize(BinaryReader &stream) -> std::expected<base::CameraInstructionOptions::FadeInstruction::ColorOption, std::error_code>
{
    base::CameraInstructionOptions::FadeInstruction::ColorOption out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.red = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.green = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.blue = static_cast<float>(*v);
    }
    return out;
}

void Serializer<base::CameraInstructionOptions::FadeInstruction>::serialize(BinaryWriter &stream, const base::CameraInstructionOptions::FadeInstruction &value)
{
    stream.write<bool>(value.time.has_value());
    if (value.time.has_value()) {
        Serializer<base::CameraInstructionOptions::FadeInstruction::TimeOption>::serialize(stream, (*value.time));
    }
    stream.write<bool>(value.color.has_value());
    if (value.color.has_value()) {
        Serializer<base::CameraInstructionOptions::FadeInstruction::ColorOption>::serialize(stream, (*value.color));
    }
}

auto Serializer<base::CameraInstructionOptions::FadeInstruction>::deserialize(BinaryReader &stream) -> std::expected<base::CameraInstructionOptions::FadeInstruction, std::error_code>
{
    base::CameraInstructionOptions::FadeInstruction out;
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            base::CameraInstructionOptions::FadeInstruction::TimeOption staged{};
            auto v = Serializer<base::CameraInstructionOptions::FadeInstruction::TimeOption>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.time = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            base::CameraInstructionOptions::FadeInstruction::ColorOption staged{};
            auto v = Serializer<base::CameraInstructionOptions::FadeInstruction::ColorOption>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.color = std::move(staged);
        }
    }
    return out;
}

void Serializer<base::CameraInstructionOptions::TargetInstruction>::serialize(BinaryWriter &stream, const base::CameraInstructionOptions::TargetInstruction &value)
{
    stream.write<bool>(value.target_center_offset.has_value());
    if (value.target_center_offset.has_value()) {
        Serializer<Vec3>::serialize(stream, (*value.target_center_offset));
    }
    stream.write<std::int64_t>(value.target_actor_id);
}

auto Serializer<base::CameraInstructionOptions::TargetInstruction>::deserialize(BinaryReader &stream) -> std::expected<base::CameraInstructionOptions::TargetInstruction, std::error_code>
{
    base::CameraInstructionOptions::TargetInstruction out;
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec3 staged{};
            auto v = Serializer<Vec3>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.target_center_offset = std::move(staged);
        }
    }
    {
        auto v = stream.read<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.target_actor_id = static_cast<ActorUniqueID>(*v);
    }
    return out;
}

void Serializer<base::CameraInstructionOptions::FovInstruction>::serialize(BinaryWriter &stream, const base::CameraInstructionOptions::FovInstruction &value)
{
    stream.write<float>(value.fov);
    stream.write<float>(value.fov_ease_time);
    Serializer<EasingType>::serialize(stream, value.fov_ease_type);
    stream.write<bool>(value.fov_clear);
}

auto Serializer<base::CameraInstructionOptions::FovInstruction>::deserialize(BinaryReader &stream) -> std::expected<base::CameraInstructionOptions::FovInstruction, std::error_code>
{
    base::CameraInstructionOptions::FovInstruction out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.fov = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.fov_ease_time = static_cast<float>(*v);
    }
    {
        auto v = Serializer<EasingType>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.fov_ease_type = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.fov_clear = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<base::CameraInstructionOptions::AttachToEntityInstruction>::serialize(BinaryWriter &stream, const base::CameraInstructionOptions::AttachToEntityInstruction &value)
{
    stream.write<std::int64_t>(value.attach_to_entity_id);
}

auto Serializer<base::CameraInstructionOptions::AttachToEntityInstruction>::deserialize(BinaryReader &stream) -> std::expected<base::CameraInstructionOptions::AttachToEntityInstruction, std::error_code>
{
    base::CameraInstructionOptions::AttachToEntityInstruction out;
    {
        auto v = stream.read<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.attach_to_entity_id = static_cast<ActorUniqueID>(*v);
    }
    return out;
}

void Serializer<base::CameraInstructionOptions::SplineInstruction::SplineRotationOption>::serialize(BinaryWriter &stream, const base::CameraInstructionOptions::SplineInstruction::SplineRotationOption &value)
{
    Serializer<Vec3>::serialize(stream, value.rotation_key_frame_value);
    stream.write<float>(value.rotation_key_frame_time);
}

auto Serializer<base::CameraInstructionOptions::SplineInstruction::SplineRotationOption>::deserialize(BinaryReader &stream) -> std::expected<base::CameraInstructionOptions::SplineInstruction::SplineRotationOption, std::error_code>
{
    base::CameraInstructionOptions::SplineInstruction::SplineRotationOption out;
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.rotation_key_frame_value = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.rotation_key_frame_time = static_cast<float>(*v);
    }
    return out;
}

void Serializer<base::CameraInstructionOptions::SplineInstruction::SplineProgressOption>::serialize(BinaryWriter &stream, const base::CameraInstructionOptions::SplineInstruction::SplineProgressOption &value)
{
    stream.write<float>(value.progress_key_frame_value);
    stream.write<float>(value.progress_key_frame_time);
    Serializer<EasingType>::serialize(stream, value.progress_key_frames_easing_func);
}

auto Serializer<base::CameraInstructionOptions::SplineInstruction::SplineProgressOption>::deserialize(BinaryReader &stream) -> std::expected<base::CameraInstructionOptions::SplineInstruction::SplineProgressOption, std::error_code>
{
    base::CameraInstructionOptions::SplineInstruction::SplineProgressOption out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.progress_key_frame_value = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.progress_key_frame_time = static_cast<float>(*v);
    }
    {
        auto v = Serializer<EasingType>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.progress_key_frames_easing_func = *v;
    }
    return out;
}

void Serializer<base::CameraInstructionOptions::SplineInstruction>::serialize(BinaryWriter &stream, const base::CameraInstructionOptions::SplineInstruction &value)
{
    stream.write<float>(value.total_time);
    stream.write<std::uint8_t>(value.curve_type);
    stream.writeVarInt<std::uint32_t>(value.curve.size());
    for (const auto &e0 : value.curve) {
        Serializer<Vec3>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.progress_key_frames.size());
    for (const auto &e0 : value.progress_key_frames) {
        Serializer<Vec2>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.spline_rotation_option.size());
    for (const auto &e0 : value.spline_rotation_option) {
        Serializer<base::CameraInstructionOptions::SplineInstruction::SplineRotationOption>::serialize(stream, e0);
    }
}

auto Serializer<base::CameraInstructionOptions::SplineInstruction>::deserialize(BinaryReader &stream) -> std::expected<base::CameraInstructionOptions::SplineInstruction, std::error_code>
{
    base::CameraInstructionOptions::SplineInstruction out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.total_time = static_cast<float>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.curve_type = static_cast<SplineType>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.curve.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.curve.emplace_back();
            auto v = Serializer<Vec3>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.curve.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.progress_key_frames.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.progress_key_frames.emplace_back();
            auto v = Serializer<Vec2>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.progress_key_frames.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.spline_rotation_option.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.spline_rotation_option.emplace_back();
            auto v = Serializer<base::CameraInstructionOptions::SplineInstruction::SplineRotationOption>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.spline_rotation_option.back() = *v;
        }
    }
    return out;
}

void Serializer<v748::CameraInstructionOptions::SetInstruction::EaseOption>::serialize(BinaryWriter &stream, const v748::CameraInstructionOptions::SetInstruction::EaseOption &value)
{
    stream.write<std::uint8_t>(value.easing_type);
    stream.write<float>(value.easing_time);
}

auto Serializer<v748::CameraInstructionOptions::SetInstruction::EaseOption>::deserialize(BinaryReader &stream) -> std::expected<v748::CameraInstructionOptions::SetInstruction::EaseOption, std::error_code>
{
    v748::CameraInstructionOptions::SetInstruction::EaseOption out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.easing_type = static_cast<EasingType>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.easing_time = static_cast<float>(*v);
    }
    return out;
}

void Serializer<v748::CameraInstructionOptions::SetInstruction::PosOption>::serialize(BinaryWriter &stream, const v748::CameraInstructionOptions::SetInstruction::PosOption &value)
{
    Serializer<Vec3>::serialize(stream, value.pos);
}

auto Serializer<v748::CameraInstructionOptions::SetInstruction::PosOption>::deserialize(BinaryReader &stream) -> std::expected<v748::CameraInstructionOptions::SetInstruction::PosOption, std::error_code>
{
    v748::CameraInstructionOptions::SetInstruction::PosOption out;
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    return out;
}

void Serializer<v748::CameraInstructionOptions::SetInstruction::RotOption>::serialize(BinaryWriter &stream, const v748::CameraInstructionOptions::SetInstruction::RotOption &value)
{
    stream.write<float>(value.rot_x);
    stream.write<float>(value.rot_y);
}

auto Serializer<v748::CameraInstructionOptions::SetInstruction::RotOption>::deserialize(BinaryReader &stream) -> std::expected<v748::CameraInstructionOptions::SetInstruction::RotOption, std::error_code>
{
    v748::CameraInstructionOptions::SetInstruction::RotOption out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.rot_x = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.rot_y = static_cast<float>(*v);
    }
    return out;
}

void Serializer<v748::CameraInstructionOptions::SetInstruction::FacingOption>::serialize(BinaryWriter &stream, const v748::CameraInstructionOptions::SetInstruction::FacingOption &value)
{
    Serializer<Vec3>::serialize(stream, value.facing_pos);
}

auto Serializer<v748::CameraInstructionOptions::SetInstruction::FacingOption>::deserialize(BinaryReader &stream) -> std::expected<v748::CameraInstructionOptions::SetInstruction::FacingOption, std::error_code>
{
    v748::CameraInstructionOptions::SetInstruction::FacingOption out;
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.facing_pos = *v;
    }
    return out;
}

void Serializer<v748::CameraInstructionOptions::SetInstruction::ViewOffsetOption>::serialize(BinaryWriter &stream, const v748::CameraInstructionOptions::SetInstruction::ViewOffsetOption &value)
{
    stream.write<float>(value.view_offset_x);
    stream.write<float>(value.view_offset_y);
}

auto Serializer<v748::CameraInstructionOptions::SetInstruction::ViewOffsetOption>::deserialize(BinaryReader &stream) -> std::expected<v748::CameraInstructionOptions::SetInstruction::ViewOffsetOption, std::error_code>
{
    v748::CameraInstructionOptions::SetInstruction::ViewOffsetOption out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.view_offset_x = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.view_offset_y = static_cast<float>(*v);
    }
    return out;
}

void Serializer<v748::CameraInstructionOptions::SetInstruction::EntityOffsetOption>::serialize(BinaryWriter &stream, const v748::CameraInstructionOptions::SetInstruction::EntityOffsetOption &value)
{
    stream.write<float>(value.entity_offset_x);
    stream.write<float>(value.entity_offset_y);
    stream.write<float>(value.entity_offset_z);
}

auto Serializer<v748::CameraInstructionOptions::SetInstruction::EntityOffsetOption>::deserialize(BinaryReader &stream) -> std::expected<v748::CameraInstructionOptions::SetInstruction::EntityOffsetOption, std::error_code>
{
    v748::CameraInstructionOptions::SetInstruction::EntityOffsetOption out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.entity_offset_x = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.entity_offset_y = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.entity_offset_z = static_cast<float>(*v);
    }
    return out;
}

void Serializer<v748::CameraInstructionOptions::SetInstruction>::serialize(BinaryWriter &stream, const v748::CameraInstructionOptions::SetInstruction &value)
{
    stream.write<std::uint32_t>(value.preset_index);
    stream.write<bool>(value.ease.has_value());
    if (value.ease.has_value()) {
        Serializer<v748::CameraInstructionOptions::SetInstruction::EaseOption>::serialize(stream, (*value.ease));
    }
    stream.write<bool>(value.pos.has_value());
    if (value.pos.has_value()) {
        Serializer<v748::CameraInstructionOptions::SetInstruction::PosOption>::serialize(stream, (*value.pos));
    }
    stream.write<bool>(value.rot.has_value());
    if (value.rot.has_value()) {
        Serializer<v748::CameraInstructionOptions::SetInstruction::RotOption>::serialize(stream, (*value.rot));
    }
    stream.write<bool>(value.facing.has_value());
    if (value.facing.has_value()) {
        Serializer<v748::CameraInstructionOptions::SetInstruction::FacingOption>::serialize(stream, (*value.facing));
    }
    stream.write<bool>(value.view_offset.has_value());
    if (value.view_offset.has_value()) {
        Serializer<v748::CameraInstructionOptions::SetInstruction::ViewOffsetOption>::serialize(stream, (*value.view_offset));
    }
    stream.write<bool>(value.entity_offset.has_value());
    if (value.entity_offset.has_value()) {
        Serializer<v748::CameraInstructionOptions::SetInstruction::EntityOffsetOption>::serialize(stream, (*value.entity_offset));
    }
    stream.write<bool>(value.default_.has_value());
    if (value.default_.has_value()) {
        stream.write<bool>((*value.default_));
    }
}

auto Serializer<v748::CameraInstructionOptions::SetInstruction>::deserialize(BinaryReader &stream) -> std::expected<v748::CameraInstructionOptions::SetInstruction, std::error_code>
{
    v748::CameraInstructionOptions::SetInstruction out;
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.preset_index = static_cast<std::uint32_t>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v748::CameraInstructionOptions::SetInstruction::EaseOption staged{};
            auto v = Serializer<v748::CameraInstructionOptions::SetInstruction::EaseOption>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.ease = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v748::CameraInstructionOptions::SetInstruction::PosOption staged{};
            auto v = Serializer<v748::CameraInstructionOptions::SetInstruction::PosOption>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.pos = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v748::CameraInstructionOptions::SetInstruction::RotOption staged{};
            auto v = Serializer<v748::CameraInstructionOptions::SetInstruction::RotOption>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.rot = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v748::CameraInstructionOptions::SetInstruction::FacingOption staged{};
            auto v = Serializer<v748::CameraInstructionOptions::SetInstruction::FacingOption>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.facing = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v748::CameraInstructionOptions::SetInstruction::ViewOffsetOption staged{};
            auto v = Serializer<v748::CameraInstructionOptions::SetInstruction::ViewOffsetOption>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.view_offset = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v748::CameraInstructionOptions::SetInstruction::EntityOffsetOption staged{};
            auto v = Serializer<v748::CameraInstructionOptions::SetInstruction::EntityOffsetOption>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.entity_offset = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.default_ = std::move(staged);
        }
    }
    return out;
}

void Serializer<v748::CameraInstructionOptions::SplineInstruction::SplineRotationOption>::serialize(BinaryWriter &stream, const v748::CameraInstructionOptions::SplineInstruction::SplineRotationOption &value)
{
    Serializer<Vec3>::serialize(stream, value.rotation_key_frame_value);
    stream.write<float>(value.rotation_key_frame_time);
}

auto Serializer<v748::CameraInstructionOptions::SplineInstruction::SplineRotationOption>::deserialize(BinaryReader &stream) -> std::expected<v748::CameraInstructionOptions::SplineInstruction::SplineRotationOption, std::error_code>
{
    v748::CameraInstructionOptions::SplineInstruction::SplineRotationOption out;
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.rotation_key_frame_value = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.rotation_key_frame_time = static_cast<float>(*v);
    }
    return out;
}

void Serializer<v748::CameraInstructionOptions::SplineInstruction::SplineProgressOption>::serialize(BinaryWriter &stream, const v748::CameraInstructionOptions::SplineInstruction::SplineProgressOption &value)
{
    stream.write<float>(value.progress_key_frame_value);
    stream.write<float>(value.progress_key_frame_time);
    Serializer<EasingType>::serialize(stream, value.progress_key_frames_easing_func);
}

auto Serializer<v748::CameraInstructionOptions::SplineInstruction::SplineProgressOption>::deserialize(BinaryReader &stream) -> std::expected<v748::CameraInstructionOptions::SplineInstruction::SplineProgressOption, std::error_code>
{
    v748::CameraInstructionOptions::SplineInstruction::SplineProgressOption out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.progress_key_frame_value = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.progress_key_frame_time = static_cast<float>(*v);
    }
    {
        auto v = Serializer<EasingType>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.progress_key_frames_easing_func = *v;
    }
    return out;
}

void Serializer<v748::CameraInstructionOptions::SplineInstruction>::serialize(BinaryWriter &stream, const v748::CameraInstructionOptions::SplineInstruction &value)
{
    stream.write<float>(value.total_time);
    stream.write<std::uint8_t>(value.curve_type);
    stream.writeVarInt<std::uint32_t>(value.curve.size());
    for (const auto &e0 : value.curve) {
        Serializer<Vec3>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.progress_key_frames.size());
    for (const auto &e0 : value.progress_key_frames) {
        Serializer<Vec2>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.spline_rotation_option.size());
    for (const auto &e0 : value.spline_rotation_option) {
        Serializer<v748::CameraInstructionOptions::SplineInstruction::SplineRotationOption>::serialize(stream, e0);
    }
}

auto Serializer<v748::CameraInstructionOptions::SplineInstruction>::deserialize(BinaryReader &stream) -> std::expected<v748::CameraInstructionOptions::SplineInstruction, std::error_code>
{
    v748::CameraInstructionOptions::SplineInstruction out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.total_time = static_cast<float>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.curve_type = static_cast<SplineType>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.curve.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.curve.emplace_back();
            auto v = Serializer<Vec3>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.curve.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.progress_key_frames.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.progress_key_frames.emplace_back();
            auto v = Serializer<Vec2>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.progress_key_frames.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.spline_rotation_option.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.spline_rotation_option.emplace_back();
            auto v = Serializer<v748::CameraInstructionOptions::SplineInstruction::SplineRotationOption>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.spline_rotation_option.back() = *v;
        }
    }
    return out;
}

void Serializer<v818::CameraInstructionOptions::SetInstruction::EaseOption>::serialize(BinaryWriter &stream, const v818::CameraInstructionOptions::SetInstruction::EaseOption &value)
{
    stream.write<std::uint8_t>(value.easing_type);
    stream.write<float>(value.easing_time);
}

auto Serializer<v818::CameraInstructionOptions::SetInstruction::EaseOption>::deserialize(BinaryReader &stream) -> std::expected<v818::CameraInstructionOptions::SetInstruction::EaseOption, std::error_code>
{
    v818::CameraInstructionOptions::SetInstruction::EaseOption out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.easing_type = static_cast<EasingType>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.easing_time = static_cast<float>(*v);
    }
    return out;
}

void Serializer<v818::CameraInstructionOptions::SetInstruction::PosOption>::serialize(BinaryWriter &stream, const v818::CameraInstructionOptions::SetInstruction::PosOption &value)
{
    Serializer<Vec3>::serialize(stream, value.pos);
}

auto Serializer<v818::CameraInstructionOptions::SetInstruction::PosOption>::deserialize(BinaryReader &stream) -> std::expected<v818::CameraInstructionOptions::SetInstruction::PosOption, std::error_code>
{
    v818::CameraInstructionOptions::SetInstruction::PosOption out;
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    return out;
}

void Serializer<v818::CameraInstructionOptions::SetInstruction::RotOption>::serialize(BinaryWriter &stream, const v818::CameraInstructionOptions::SetInstruction::RotOption &value)
{
    stream.write<float>(value.rot_x);
    stream.write<float>(value.rot_y);
}

auto Serializer<v818::CameraInstructionOptions::SetInstruction::RotOption>::deserialize(BinaryReader &stream) -> std::expected<v818::CameraInstructionOptions::SetInstruction::RotOption, std::error_code>
{
    v818::CameraInstructionOptions::SetInstruction::RotOption out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.rot_x = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.rot_y = static_cast<float>(*v);
    }
    return out;
}

void Serializer<v818::CameraInstructionOptions::SetInstruction::FacingOption>::serialize(BinaryWriter &stream, const v818::CameraInstructionOptions::SetInstruction::FacingOption &value)
{
    Serializer<Vec3>::serialize(stream, value.facing_pos);
}

auto Serializer<v818::CameraInstructionOptions::SetInstruction::FacingOption>::deserialize(BinaryReader &stream) -> std::expected<v818::CameraInstructionOptions::SetInstruction::FacingOption, std::error_code>
{
    v818::CameraInstructionOptions::SetInstruction::FacingOption out;
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.facing_pos = *v;
    }
    return out;
}

void Serializer<v818::CameraInstructionOptions::SetInstruction::ViewOffsetOption>::serialize(BinaryWriter &stream, const v818::CameraInstructionOptions::SetInstruction::ViewOffsetOption &value)
{
    stream.write<float>(value.view_offset_x);
    stream.write<float>(value.view_offset_y);
}

auto Serializer<v818::CameraInstructionOptions::SetInstruction::ViewOffsetOption>::deserialize(BinaryReader &stream) -> std::expected<v818::CameraInstructionOptions::SetInstruction::ViewOffsetOption, std::error_code>
{
    v818::CameraInstructionOptions::SetInstruction::ViewOffsetOption out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.view_offset_x = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.view_offset_y = static_cast<float>(*v);
    }
    return out;
}

void Serializer<v818::CameraInstructionOptions::SetInstruction::EntityOffsetOption>::serialize(BinaryWriter &stream, const v818::CameraInstructionOptions::SetInstruction::EntityOffsetOption &value)
{
    stream.write<float>(value.entity_offset_x);
    stream.write<float>(value.entity_offset_y);
    stream.write<float>(value.entity_offset_z);
}

auto Serializer<v818::CameraInstructionOptions::SetInstruction::EntityOffsetOption>::deserialize(BinaryReader &stream) -> std::expected<v818::CameraInstructionOptions::SetInstruction::EntityOffsetOption, std::error_code>
{
    v818::CameraInstructionOptions::SetInstruction::EntityOffsetOption out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.entity_offset_x = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.entity_offset_y = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.entity_offset_z = static_cast<float>(*v);
    }
    return out;
}

void Serializer<v818::CameraInstructionOptions::SetInstruction>::serialize(BinaryWriter &stream, const v818::CameraInstructionOptions::SetInstruction &value)
{
    stream.write<std::uint32_t>(value.preset_index);
    stream.write<bool>(value.ease.has_value());
    if (value.ease.has_value()) {
        Serializer<v818::CameraInstructionOptions::SetInstruction::EaseOption>::serialize(stream, (*value.ease));
    }
    stream.write<bool>(value.pos.has_value());
    if (value.pos.has_value()) {
        Serializer<v818::CameraInstructionOptions::SetInstruction::PosOption>::serialize(stream, (*value.pos));
    }
    stream.write<bool>(value.rot.has_value());
    if (value.rot.has_value()) {
        Serializer<v818::CameraInstructionOptions::SetInstruction::RotOption>::serialize(stream, (*value.rot));
    }
    stream.write<bool>(value.facing.has_value());
    if (value.facing.has_value()) {
        Serializer<v818::CameraInstructionOptions::SetInstruction::FacingOption>::serialize(stream, (*value.facing));
    }
    stream.write<bool>(value.view_offset.has_value());
    if (value.view_offset.has_value()) {
        Serializer<v818::CameraInstructionOptions::SetInstruction::ViewOffsetOption>::serialize(stream, (*value.view_offset));
    }
    stream.write<bool>(value.entity_offset.has_value());
    if (value.entity_offset.has_value()) {
        Serializer<v818::CameraInstructionOptions::SetInstruction::EntityOffsetOption>::serialize(stream, (*value.entity_offset));
    }
    stream.write<bool>(value.default_.has_value());
    if (value.default_.has_value()) {
        stream.write<bool>((*value.default_));
    }
    stream.write<bool>(value.remove_ignore_starting_values_component);
}

auto Serializer<v818::CameraInstructionOptions::SetInstruction>::deserialize(BinaryReader &stream) -> std::expected<v818::CameraInstructionOptions::SetInstruction, std::error_code>
{
    v818::CameraInstructionOptions::SetInstruction out;
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.preset_index = static_cast<std::uint32_t>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v818::CameraInstructionOptions::SetInstruction::EaseOption staged{};
            auto v = Serializer<v818::CameraInstructionOptions::SetInstruction::EaseOption>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.ease = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v818::CameraInstructionOptions::SetInstruction::PosOption staged{};
            auto v = Serializer<v818::CameraInstructionOptions::SetInstruction::PosOption>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.pos = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v818::CameraInstructionOptions::SetInstruction::RotOption staged{};
            auto v = Serializer<v818::CameraInstructionOptions::SetInstruction::RotOption>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.rot = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v818::CameraInstructionOptions::SetInstruction::FacingOption staged{};
            auto v = Serializer<v818::CameraInstructionOptions::SetInstruction::FacingOption>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.facing = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v818::CameraInstructionOptions::SetInstruction::ViewOffsetOption staged{};
            auto v = Serializer<v818::CameraInstructionOptions::SetInstruction::ViewOffsetOption>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.view_offset = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v818::CameraInstructionOptions::SetInstruction::EntityOffsetOption staged{};
            auto v = Serializer<v818::CameraInstructionOptions::SetInstruction::EntityOffsetOption>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.entity_offset = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.default_ = std::move(staged);
        }
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.remove_ignore_starting_values_component = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v818::CameraInstructionOptions::SplineInstruction::SplineRotationOption>::serialize(BinaryWriter &stream, const v818::CameraInstructionOptions::SplineInstruction::SplineRotationOption &value)
{
    Serializer<Vec3>::serialize(stream, value.rotation_key_frame_value);
    stream.write<float>(value.rotation_key_frame_time);
}

auto Serializer<v818::CameraInstructionOptions::SplineInstruction::SplineRotationOption>::deserialize(BinaryReader &stream) -> std::expected<v818::CameraInstructionOptions::SplineInstruction::SplineRotationOption, std::error_code>
{
    v818::CameraInstructionOptions::SplineInstruction::SplineRotationOption out;
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.rotation_key_frame_value = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.rotation_key_frame_time = static_cast<float>(*v);
    }
    return out;
}

void Serializer<v818::CameraInstructionOptions::SplineInstruction::SplineProgressOption>::serialize(BinaryWriter &stream, const v818::CameraInstructionOptions::SplineInstruction::SplineProgressOption &value)
{
    stream.write<float>(value.progress_key_frame_value);
    stream.write<float>(value.progress_key_frame_time);
    Serializer<EasingType>::serialize(stream, value.progress_key_frames_easing_func);
}

auto Serializer<v818::CameraInstructionOptions::SplineInstruction::SplineProgressOption>::deserialize(BinaryReader &stream) -> std::expected<v818::CameraInstructionOptions::SplineInstruction::SplineProgressOption, std::error_code>
{
    v818::CameraInstructionOptions::SplineInstruction::SplineProgressOption out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.progress_key_frame_value = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.progress_key_frame_time = static_cast<float>(*v);
    }
    {
        auto v = Serializer<EasingType>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.progress_key_frames_easing_func = *v;
    }
    return out;
}

void Serializer<v818::CameraInstructionOptions::SplineInstruction>::serialize(BinaryWriter &stream, const v818::CameraInstructionOptions::SplineInstruction &value)
{
    stream.write<float>(value.total_time);
    stream.write<std::uint8_t>(value.curve_type);
    stream.writeVarInt<std::uint32_t>(value.curve.size());
    for (const auto &e0 : value.curve) {
        Serializer<Vec3>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.progress_key_frames.size());
    for (const auto &e0 : value.progress_key_frames) {
        Serializer<Vec2>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.spline_rotation_option.size());
    for (const auto &e0 : value.spline_rotation_option) {
        Serializer<v818::CameraInstructionOptions::SplineInstruction::SplineRotationOption>::serialize(stream, e0);
    }
}

auto Serializer<v818::CameraInstructionOptions::SplineInstruction>::deserialize(BinaryReader &stream) -> std::expected<v818::CameraInstructionOptions::SplineInstruction, std::error_code>
{
    v818::CameraInstructionOptions::SplineInstruction out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.total_time = static_cast<float>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.curve_type = static_cast<SplineType>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.curve.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.curve.emplace_back();
            auto v = Serializer<Vec3>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.curve.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.progress_key_frames.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.progress_key_frames.emplace_back();
            auto v = Serializer<Vec2>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.progress_key_frames.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.spline_rotation_option.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.spline_rotation_option.emplace_back();
            auto v = Serializer<v818::CameraInstructionOptions::SplineInstruction::SplineRotationOption>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.spline_rotation_option.back() = *v;
        }
    }
    return out;
}

void Serializer<v924::CameraInstructionOptions::SetInstruction::EaseOption>::serialize(BinaryWriter &stream, const v924::CameraInstructionOptions::SetInstruction::EaseOption &value)
{
    stream.write<std::uint8_t>(value.easing_type);
    stream.write<float>(value.easing_time);
}

auto Serializer<v924::CameraInstructionOptions::SetInstruction::EaseOption>::deserialize(BinaryReader &stream) -> std::expected<v924::CameraInstructionOptions::SetInstruction::EaseOption, std::error_code>
{
    v924::CameraInstructionOptions::SetInstruction::EaseOption out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.easing_type = static_cast<EasingType>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.easing_time = static_cast<float>(*v);
    }
    return out;
}

void Serializer<v924::CameraInstructionOptions::SetInstruction::PosOption>::serialize(BinaryWriter &stream, const v924::CameraInstructionOptions::SetInstruction::PosOption &value)
{
    Serializer<Vec3>::serialize(stream, value.pos);
}

auto Serializer<v924::CameraInstructionOptions::SetInstruction::PosOption>::deserialize(BinaryReader &stream) -> std::expected<v924::CameraInstructionOptions::SetInstruction::PosOption, std::error_code>
{
    v924::CameraInstructionOptions::SetInstruction::PosOption out;
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    return out;
}

void Serializer<v924::CameraInstructionOptions::SetInstruction::RotOption>::serialize(BinaryWriter &stream, const v924::CameraInstructionOptions::SetInstruction::RotOption &value)
{
    stream.write<float>(value.rot_x);
    stream.write<float>(value.rot_y);
}

auto Serializer<v924::CameraInstructionOptions::SetInstruction::RotOption>::deserialize(BinaryReader &stream) -> std::expected<v924::CameraInstructionOptions::SetInstruction::RotOption, std::error_code>
{
    v924::CameraInstructionOptions::SetInstruction::RotOption out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.rot_x = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.rot_y = static_cast<float>(*v);
    }
    return out;
}

void Serializer<v924::CameraInstructionOptions::SetInstruction::FacingOption>::serialize(BinaryWriter &stream, const v924::CameraInstructionOptions::SetInstruction::FacingOption &value)
{
    Serializer<Vec3>::serialize(stream, value.facing_pos);
}

auto Serializer<v924::CameraInstructionOptions::SetInstruction::FacingOption>::deserialize(BinaryReader &stream) -> std::expected<v924::CameraInstructionOptions::SetInstruction::FacingOption, std::error_code>
{
    v924::CameraInstructionOptions::SetInstruction::FacingOption out;
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.facing_pos = *v;
    }
    return out;
}

void Serializer<v924::CameraInstructionOptions::SetInstruction::ViewOffsetOption>::serialize(BinaryWriter &stream, const v924::CameraInstructionOptions::SetInstruction::ViewOffsetOption &value)
{
    stream.write<float>(value.view_offset_x);
    stream.write<float>(value.view_offset_y);
}

auto Serializer<v924::CameraInstructionOptions::SetInstruction::ViewOffsetOption>::deserialize(BinaryReader &stream) -> std::expected<v924::CameraInstructionOptions::SetInstruction::ViewOffsetOption, std::error_code>
{
    v924::CameraInstructionOptions::SetInstruction::ViewOffsetOption out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.view_offset_x = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.view_offset_y = static_cast<float>(*v);
    }
    return out;
}

void Serializer<v924::CameraInstructionOptions::SetInstruction::EntityOffsetOption>::serialize(BinaryWriter &stream, const v924::CameraInstructionOptions::SetInstruction::EntityOffsetOption &value)
{
    stream.write<float>(value.entity_offset_x);
    stream.write<float>(value.entity_offset_y);
    stream.write<float>(value.entity_offset_z);
}

auto Serializer<v924::CameraInstructionOptions::SetInstruction::EntityOffsetOption>::deserialize(BinaryReader &stream) -> std::expected<v924::CameraInstructionOptions::SetInstruction::EntityOffsetOption, std::error_code>
{
    v924::CameraInstructionOptions::SetInstruction::EntityOffsetOption out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.entity_offset_x = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.entity_offset_y = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.entity_offset_z = static_cast<float>(*v);
    }
    return out;
}

void Serializer<v924::CameraInstructionOptions::SetInstruction>::serialize(BinaryWriter &stream, const v924::CameraInstructionOptions::SetInstruction &value)
{
    stream.write<std::uint32_t>(value.preset_index);
    stream.write<bool>(value.ease.has_value());
    if (value.ease.has_value()) {
        Serializer<v924::CameraInstructionOptions::SetInstruction::EaseOption>::serialize(stream, (*value.ease));
    }
    stream.write<bool>(value.pos.has_value());
    if (value.pos.has_value()) {
        Serializer<v924::CameraInstructionOptions::SetInstruction::PosOption>::serialize(stream, (*value.pos));
    }
    stream.write<bool>(value.rot.has_value());
    if (value.rot.has_value()) {
        Serializer<v924::CameraInstructionOptions::SetInstruction::RotOption>::serialize(stream, (*value.rot));
    }
    stream.write<bool>(value.facing.has_value());
    if (value.facing.has_value()) {
        Serializer<v924::CameraInstructionOptions::SetInstruction::FacingOption>::serialize(stream, (*value.facing));
    }
    stream.write<bool>(value.view_offset.has_value());
    if (value.view_offset.has_value()) {
        Serializer<v924::CameraInstructionOptions::SetInstruction::ViewOffsetOption>::serialize(stream, (*value.view_offset));
    }
    stream.write<bool>(value.entity_offset.has_value());
    if (value.entity_offset.has_value()) {
        Serializer<v924::CameraInstructionOptions::SetInstruction::EntityOffsetOption>::serialize(stream, (*value.entity_offset));
    }
    stream.write<bool>(value.default_.has_value());
    if (value.default_.has_value()) {
        stream.write<bool>((*value.default_));
    }
    stream.write<bool>(value.remove_ignore_starting_values_component);
}

auto Serializer<v924::CameraInstructionOptions::SetInstruction>::deserialize(BinaryReader &stream) -> std::expected<v924::CameraInstructionOptions::SetInstruction, std::error_code>
{
    v924::CameraInstructionOptions::SetInstruction out;
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.preset_index = static_cast<std::uint32_t>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v924::CameraInstructionOptions::SetInstruction::EaseOption staged{};
            auto v = Serializer<v924::CameraInstructionOptions::SetInstruction::EaseOption>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.ease = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v924::CameraInstructionOptions::SetInstruction::PosOption staged{};
            auto v = Serializer<v924::CameraInstructionOptions::SetInstruction::PosOption>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.pos = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v924::CameraInstructionOptions::SetInstruction::RotOption staged{};
            auto v = Serializer<v924::CameraInstructionOptions::SetInstruction::RotOption>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.rot = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v924::CameraInstructionOptions::SetInstruction::FacingOption staged{};
            auto v = Serializer<v924::CameraInstructionOptions::SetInstruction::FacingOption>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.facing = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v924::CameraInstructionOptions::SetInstruction::ViewOffsetOption staged{};
            auto v = Serializer<v924::CameraInstructionOptions::SetInstruction::ViewOffsetOption>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.view_offset = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v924::CameraInstructionOptions::SetInstruction::EntityOffsetOption staged{};
            auto v = Serializer<v924::CameraInstructionOptions::SetInstruction::EntityOffsetOption>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.entity_offset = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.default_ = std::move(staged);
        }
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.remove_ignore_starting_values_component = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v924::CameraInstructionOptions::SplineInstruction::SplineRotationOption>::serialize(BinaryWriter &stream, const v924::CameraInstructionOptions::SplineInstruction::SplineRotationOption &value)
{
    Serializer<Vec3>::serialize(stream, value.rotation_key_frame_value);
    stream.write<float>(value.rotation_key_frame_time);
    Serializer<EasingType>::serialize(stream, value.rotation_key_frames_easing_func);
}

auto Serializer<v924::CameraInstructionOptions::SplineInstruction::SplineRotationOption>::deserialize(BinaryReader &stream) -> std::expected<v924::CameraInstructionOptions::SplineInstruction::SplineRotationOption, std::error_code>
{
    v924::CameraInstructionOptions::SplineInstruction::SplineRotationOption out;
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.rotation_key_frame_value = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.rotation_key_frame_time = static_cast<float>(*v);
    }
    {
        auto v = Serializer<EasingType>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.rotation_key_frames_easing_func = *v;
    }
    return out;
}

void Serializer<v924::CameraInstructionOptions::SplineInstruction::SplineProgressOption>::serialize(BinaryWriter &stream, const v924::CameraInstructionOptions::SplineInstruction::SplineProgressOption &value)
{
    stream.write<float>(value.progress_key_frame_value);
    stream.write<float>(value.progress_key_frame_time);
    Serializer<EasingType>::serialize(stream, value.progress_key_frames_easing_func);
}

auto Serializer<v924::CameraInstructionOptions::SplineInstruction::SplineProgressOption>::deserialize(BinaryReader &stream) -> std::expected<v924::CameraInstructionOptions::SplineInstruction::SplineProgressOption, std::error_code>
{
    v924::CameraInstructionOptions::SplineInstruction::SplineProgressOption out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.progress_key_frame_value = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.progress_key_frame_time = static_cast<float>(*v);
    }
    {
        auto v = Serializer<EasingType>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.progress_key_frames_easing_func = *v;
    }
    return out;
}

void Serializer<v924::CameraInstructionOptions::SplineInstruction>::serialize(BinaryWriter &stream, const v924::CameraInstructionOptions::SplineInstruction &value)
{
    stream.write<float>(value.total_time);
    stream.write<std::uint8_t>(value.curve_type);
    stream.writeVarInt<std::uint32_t>(value.curve.size());
    for (const auto &e0 : value.curve) {
        Serializer<Vec3>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.progress_key_frames.size());
    for (const auto &e0 : value.progress_key_frames) {
        Serializer<v924::CameraInstructionOptions::SplineInstruction::SplineProgressOption>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.spline_rotation_option.size());
    for (const auto &e0 : value.spline_rotation_option) {
        Serializer<v924::CameraInstructionOptions::SplineInstruction::SplineRotationOption>::serialize(stream, e0);
    }
}

auto Serializer<v924::CameraInstructionOptions::SplineInstruction>::deserialize(BinaryReader &stream) -> std::expected<v924::CameraInstructionOptions::SplineInstruction, std::error_code>
{
    v924::CameraInstructionOptions::SplineInstruction out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.total_time = static_cast<float>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.curve_type = static_cast<SplineType>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.curve.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.curve.emplace_back();
            auto v = Serializer<Vec3>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.curve.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.progress_key_frames.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.progress_key_frames.emplace_back();
            auto v = Serializer<v924::CameraInstructionOptions::SplineInstruction::SplineProgressOption>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.progress_key_frames.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.spline_rotation_option.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.spline_rotation_option.emplace_back();
            auto v = Serializer<v924::CameraInstructionOptions::SplineInstruction::SplineRotationOption>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.spline_rotation_option.back() = *v;
        }
    }
    return out;
}

void Serializer<v944::CameraInstructionOptions::SetInstruction::EaseOption>::serialize(BinaryWriter &stream, const v944::CameraInstructionOptions::SetInstruction::EaseOption &value)
{
    stream.write<std::uint8_t>(value.easing_type);
    stream.write<float>(value.easing_time);
}

auto Serializer<v944::CameraInstructionOptions::SetInstruction::EaseOption>::deserialize(BinaryReader &stream) -> std::expected<v944::CameraInstructionOptions::SetInstruction::EaseOption, std::error_code>
{
    v944::CameraInstructionOptions::SetInstruction::EaseOption out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.easing_type = static_cast<EasingType>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.easing_time = static_cast<float>(*v);
    }
    return out;
}

void Serializer<v944::CameraInstructionOptions::SetInstruction::PosOption>::serialize(BinaryWriter &stream, const v944::CameraInstructionOptions::SetInstruction::PosOption &value)
{
    Serializer<Vec3>::serialize(stream, value.pos);
}

auto Serializer<v944::CameraInstructionOptions::SetInstruction::PosOption>::deserialize(BinaryReader &stream) -> std::expected<v944::CameraInstructionOptions::SetInstruction::PosOption, std::error_code>
{
    v944::CameraInstructionOptions::SetInstruction::PosOption out;
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    return out;
}

void Serializer<v944::CameraInstructionOptions::SetInstruction::RotOption>::serialize(BinaryWriter &stream, const v944::CameraInstructionOptions::SetInstruction::RotOption &value)
{
    stream.write<float>(value.rot_x);
    stream.write<float>(value.rot_y);
}

auto Serializer<v944::CameraInstructionOptions::SetInstruction::RotOption>::deserialize(BinaryReader &stream) -> std::expected<v944::CameraInstructionOptions::SetInstruction::RotOption, std::error_code>
{
    v944::CameraInstructionOptions::SetInstruction::RotOption out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.rot_x = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.rot_y = static_cast<float>(*v);
    }
    return out;
}

void Serializer<v944::CameraInstructionOptions::SetInstruction::FacingOption>::serialize(BinaryWriter &stream, const v944::CameraInstructionOptions::SetInstruction::FacingOption &value)
{
    Serializer<Vec3>::serialize(stream, value.facing_pos);
}

auto Serializer<v944::CameraInstructionOptions::SetInstruction::FacingOption>::deserialize(BinaryReader &stream) -> std::expected<v944::CameraInstructionOptions::SetInstruction::FacingOption, std::error_code>
{
    v944::CameraInstructionOptions::SetInstruction::FacingOption out;
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.facing_pos = *v;
    }
    return out;
}

void Serializer<v944::CameraInstructionOptions::SetInstruction::ViewOffsetOption>::serialize(BinaryWriter &stream, const v944::CameraInstructionOptions::SetInstruction::ViewOffsetOption &value)
{
    stream.write<float>(value.view_offset_x);
    stream.write<float>(value.view_offset_y);
}

auto Serializer<v944::CameraInstructionOptions::SetInstruction::ViewOffsetOption>::deserialize(BinaryReader &stream) -> std::expected<v944::CameraInstructionOptions::SetInstruction::ViewOffsetOption, std::error_code>
{
    v944::CameraInstructionOptions::SetInstruction::ViewOffsetOption out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.view_offset_x = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.view_offset_y = static_cast<float>(*v);
    }
    return out;
}

void Serializer<v944::CameraInstructionOptions::SetInstruction::EntityOffsetOption>::serialize(BinaryWriter &stream, const v944::CameraInstructionOptions::SetInstruction::EntityOffsetOption &value)
{
    stream.write<float>(value.entity_offset_x);
    stream.write<float>(value.entity_offset_y);
    stream.write<float>(value.entity_offset_z);
}

auto Serializer<v944::CameraInstructionOptions::SetInstruction::EntityOffsetOption>::deserialize(BinaryReader &stream) -> std::expected<v944::CameraInstructionOptions::SetInstruction::EntityOffsetOption, std::error_code>
{
    v944::CameraInstructionOptions::SetInstruction::EntityOffsetOption out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.entity_offset_x = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.entity_offset_y = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.entity_offset_z = static_cast<float>(*v);
    }
    return out;
}

void Serializer<v944::CameraInstructionOptions::SetInstruction>::serialize(BinaryWriter &stream, const v944::CameraInstructionOptions::SetInstruction &value)
{
    stream.write<std::uint32_t>(value.preset_index);
    stream.write<bool>(value.ease.has_value());
    if (value.ease.has_value()) {
        Serializer<v944::CameraInstructionOptions::SetInstruction::EaseOption>::serialize(stream, (*value.ease));
    }
    stream.write<bool>(value.pos.has_value());
    if (value.pos.has_value()) {
        Serializer<v944::CameraInstructionOptions::SetInstruction::PosOption>::serialize(stream, (*value.pos));
    }
    stream.write<bool>(value.rot.has_value());
    if (value.rot.has_value()) {
        Serializer<v944::CameraInstructionOptions::SetInstruction::RotOption>::serialize(stream, (*value.rot));
    }
    stream.write<bool>(value.facing.has_value());
    if (value.facing.has_value()) {
        Serializer<v944::CameraInstructionOptions::SetInstruction::FacingOption>::serialize(stream, (*value.facing));
    }
    stream.write<bool>(value.view_offset.has_value());
    if (value.view_offset.has_value()) {
        Serializer<v944::CameraInstructionOptions::SetInstruction::ViewOffsetOption>::serialize(stream, (*value.view_offset));
    }
    stream.write<bool>(value.entity_offset.has_value());
    if (value.entity_offset.has_value()) {
        Serializer<v944::CameraInstructionOptions::SetInstruction::EntityOffsetOption>::serialize(stream, (*value.entity_offset));
    }
    stream.write<bool>(value.default_.has_value());
    if (value.default_.has_value()) {
        stream.write<bool>((*value.default_));
    }
    stream.write<bool>(value.remove_ignore_starting_values_component);
}

auto Serializer<v944::CameraInstructionOptions::SetInstruction>::deserialize(BinaryReader &stream) -> std::expected<v944::CameraInstructionOptions::SetInstruction, std::error_code>
{
    v944::CameraInstructionOptions::SetInstruction out;
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.preset_index = static_cast<std::uint32_t>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v944::CameraInstructionOptions::SetInstruction::EaseOption staged{};
            auto v = Serializer<v944::CameraInstructionOptions::SetInstruction::EaseOption>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.ease = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v944::CameraInstructionOptions::SetInstruction::PosOption staged{};
            auto v = Serializer<v944::CameraInstructionOptions::SetInstruction::PosOption>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.pos = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v944::CameraInstructionOptions::SetInstruction::RotOption staged{};
            auto v = Serializer<v944::CameraInstructionOptions::SetInstruction::RotOption>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.rot = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v944::CameraInstructionOptions::SetInstruction::FacingOption staged{};
            auto v = Serializer<v944::CameraInstructionOptions::SetInstruction::FacingOption>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.facing = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v944::CameraInstructionOptions::SetInstruction::ViewOffsetOption staged{};
            auto v = Serializer<v944::CameraInstructionOptions::SetInstruction::ViewOffsetOption>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.view_offset = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v944::CameraInstructionOptions::SetInstruction::EntityOffsetOption staged{};
            auto v = Serializer<v944::CameraInstructionOptions::SetInstruction::EntityOffsetOption>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.entity_offset = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.default_ = std::move(staged);
        }
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.remove_ignore_starting_values_component = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v944::CameraInstructionOptions::SplineInstruction::SplineRotationOption>::serialize(BinaryWriter &stream, const v944::CameraInstructionOptions::SplineInstruction::SplineRotationOption &value)
{
    Serializer<Vec3>::serialize(stream, value.rotation_key_frame_value);
    stream.write<float>(value.rotation_key_frame_time);
    Serializer<EasingType>::serialize(stream, value.rotation_key_frames_easing_func);
}

auto Serializer<v944::CameraInstructionOptions::SplineInstruction::SplineRotationOption>::deserialize(BinaryReader &stream) -> std::expected<v944::CameraInstructionOptions::SplineInstruction::SplineRotationOption, std::error_code>
{
    v944::CameraInstructionOptions::SplineInstruction::SplineRotationOption out;
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.rotation_key_frame_value = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.rotation_key_frame_time = static_cast<float>(*v);
    }
    {
        auto v = Serializer<EasingType>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.rotation_key_frames_easing_func = *v;
    }
    return out;
}

void Serializer<v944::CameraInstructionOptions::SplineInstruction::SplineProgressOption>::serialize(BinaryWriter &stream, const v944::CameraInstructionOptions::SplineInstruction::SplineProgressOption &value)
{
    stream.write<float>(value.progress_key_frame_value);
    stream.write<float>(value.progress_key_frame_time);
    Serializer<EasingType>::serialize(stream, value.progress_key_frames_easing_func);
}

auto Serializer<v944::CameraInstructionOptions::SplineInstruction::SplineProgressOption>::deserialize(BinaryReader &stream) -> std::expected<v944::CameraInstructionOptions::SplineInstruction::SplineProgressOption, std::error_code>
{
    v944::CameraInstructionOptions::SplineInstruction::SplineProgressOption out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.progress_key_frame_value = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.progress_key_frame_time = static_cast<float>(*v);
    }
    {
        auto v = Serializer<EasingType>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.progress_key_frames_easing_func = *v;
    }
    return out;
}

void Serializer<v944::CameraInstructionOptions::SplineInstruction>::serialize(BinaryWriter &stream, const v944::CameraInstructionOptions::SplineInstruction &value)
{
    stream.write<float>(value.total_time);
    stream.write<std::uint8_t>(value.curve_type);
    stream.writeVarInt<std::uint32_t>(value.curve.size());
    for (const auto &e0 : value.curve) {
        Serializer<Vec3>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.progress_key_frames.size());
    for (const auto &e0 : value.progress_key_frames) {
        Serializer<v944::CameraInstructionOptions::SplineInstruction::SplineProgressOption>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.spline_rotation_option.size());
    for (const auto &e0 : value.spline_rotation_option) {
        Serializer<v944::CameraInstructionOptions::SplineInstruction::SplineRotationOption>::serialize(stream, e0);
    }
    stream.write(value.spline_identifier);
    stream.write<bool>(value.load_from_json);
}

auto Serializer<v944::CameraInstructionOptions::SplineInstruction>::deserialize(BinaryReader &stream) -> std::expected<v944::CameraInstructionOptions::SplineInstruction, std::error_code>
{
    v944::CameraInstructionOptions::SplineInstruction out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.total_time = static_cast<float>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.curve_type = static_cast<SplineType>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.curve.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.curve.emplace_back();
            auto v = Serializer<Vec3>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.curve.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.progress_key_frames.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.progress_key_frames.emplace_back();
            auto v = Serializer<v944::CameraInstructionOptions::SplineInstruction::SplineProgressOption>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.progress_key_frames.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.spline_rotation_option.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.spline_rotation_option.emplace_back();
            auto v = Serializer<v944::CameraInstructionOptions::SplineInstruction::SplineRotationOption>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.spline_rotation_option.back() = *v;
        }
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.spline_identifier = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.load_from_json = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<base::CameraInstruction>::serialize(BinaryWriter &stream, const base::CameraInstruction &value)
{
    stream.write<bool>(value.set.has_value());
    if (value.set.has_value()) {
        Serializer<base::CameraInstructionOptions::SetInstruction>::serialize(stream, (*value.set));
    }
    stream.write<bool>(value.clear.has_value());
    if (value.clear.has_value()) {
        stream.write<bool>((*value.clear));
    }
    stream.write<bool>(value.fade.has_value());
    if (value.fade.has_value()) {
        Serializer<base::CameraInstructionOptions::FadeInstruction>::serialize(stream, (*value.fade));
    }
    stream.write<bool>(value.target.has_value());
    if (value.target.has_value()) {
        Serializer<base::CameraInstructionOptions::TargetInstruction>::serialize(stream, (*value.target));
    }
    stream.write<bool>(value.remove_target.has_value());
    if (value.remove_target.has_value()) {
        stream.write<bool>((*value.remove_target));
    }
}

auto Serializer<base::CameraInstruction>::deserialize(BinaryReader &stream) -> std::expected<base::CameraInstruction, std::error_code>
{
    base::CameraInstruction out;
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            base::CameraInstructionOptions::SetInstruction staged{};
            auto v = Serializer<base::CameraInstructionOptions::SetInstruction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.set = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.clear = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            base::CameraInstructionOptions::FadeInstruction staged{};
            auto v = Serializer<base::CameraInstructionOptions::FadeInstruction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.fade = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            base::CameraInstructionOptions::TargetInstruction staged{};
            auto v = Serializer<base::CameraInstructionOptions::TargetInstruction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.target = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.remove_target = std::move(staged);
        }
    }
    return out;
}

void Serializer<v748::CameraInstruction>::serialize(BinaryWriter &stream, const v748::CameraInstruction &value)
{
    stream.write<bool>(value.set.has_value());
    if (value.set.has_value()) {
        Serializer<v748::CameraInstructionOptions::SetInstruction>::serialize(stream, (*value.set));
    }
    stream.write<bool>(value.clear.has_value());
    if (value.clear.has_value()) {
        stream.write<bool>((*value.clear));
    }
    stream.write<bool>(value.fade.has_value());
    if (value.fade.has_value()) {
        Serializer<v748::CameraInstructionOptions::FadeInstruction>::serialize(stream, (*value.fade));
    }
    stream.write<bool>(value.target.has_value());
    if (value.target.has_value()) {
        Serializer<v748::CameraInstructionOptions::TargetInstruction>::serialize(stream, (*value.target));
    }
    stream.write<bool>(value.remove_target.has_value());
    if (value.remove_target.has_value()) {
        stream.write<bool>((*value.remove_target));
    }
}

auto Serializer<v748::CameraInstruction>::deserialize(BinaryReader &stream) -> std::expected<v748::CameraInstruction, std::error_code>
{
    v748::CameraInstruction out;
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v748::CameraInstructionOptions::SetInstruction staged{};
            auto v = Serializer<v748::CameraInstructionOptions::SetInstruction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.set = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.clear = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v748::CameraInstructionOptions::FadeInstruction staged{};
            auto v = Serializer<v748::CameraInstructionOptions::FadeInstruction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.fade = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v748::CameraInstructionOptions::TargetInstruction staged{};
            auto v = Serializer<v748::CameraInstructionOptions::TargetInstruction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.target = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.remove_target = std::move(staged);
        }
    }
    return out;
}

void Serializer<v818::CameraInstruction>::serialize(BinaryWriter &stream, const v818::CameraInstruction &value)
{
    stream.write<bool>(value.set.has_value());
    if (value.set.has_value()) {
        Serializer<v818::CameraInstructionOptions::SetInstruction>::serialize(stream, (*value.set));
    }
    stream.write<bool>(value.clear.has_value());
    if (value.clear.has_value()) {
        stream.write<bool>((*value.clear));
    }
    stream.write<bool>(value.fade.has_value());
    if (value.fade.has_value()) {
        Serializer<v818::CameraInstructionOptions::FadeInstruction>::serialize(stream, (*value.fade));
    }
    stream.write<bool>(value.target.has_value());
    if (value.target.has_value()) {
        Serializer<v818::CameraInstructionOptions::TargetInstruction>::serialize(stream, (*value.target));
    }
    stream.write<bool>(value.remove_target.has_value());
    if (value.remove_target.has_value()) {
        stream.write<bool>((*value.remove_target));
    }
}

auto Serializer<v818::CameraInstruction>::deserialize(BinaryReader &stream) -> std::expected<v818::CameraInstruction, std::error_code>
{
    v818::CameraInstruction out;
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v818::CameraInstructionOptions::SetInstruction staged{};
            auto v = Serializer<v818::CameraInstructionOptions::SetInstruction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.set = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.clear = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v818::CameraInstructionOptions::FadeInstruction staged{};
            auto v = Serializer<v818::CameraInstructionOptions::FadeInstruction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.fade = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v818::CameraInstructionOptions::TargetInstruction staged{};
            auto v = Serializer<v818::CameraInstructionOptions::TargetInstruction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.target = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.remove_target = std::move(staged);
        }
    }
    return out;
}

void Serializer<v827::CameraInstruction>::serialize(BinaryWriter &stream, const v827::CameraInstruction &value)
{
    stream.write<bool>(value.set.has_value());
    if (value.set.has_value()) {
        Serializer<v818::CameraInstructionOptions::SetInstruction>::serialize(stream, (*value.set));
    }
    stream.write<bool>(value.clear.has_value());
    if (value.clear.has_value()) {
        stream.write<bool>((*value.clear));
    }
    stream.write<bool>(value.fade.has_value());
    if (value.fade.has_value()) {
        Serializer<v818::CameraInstructionOptions::FadeInstruction>::serialize(stream, (*value.fade));
    }
    stream.write<bool>(value.target.has_value());
    if (value.target.has_value()) {
        Serializer<v818::CameraInstructionOptions::TargetInstruction>::serialize(stream, (*value.target));
    }
    stream.write<bool>(value.remove_target.has_value());
    if (value.remove_target.has_value()) {
        stream.write<bool>((*value.remove_target));
    }
    stream.write<bool>(value.field_of_view.has_value());
    if (value.field_of_view.has_value()) {
        Serializer<v818::CameraInstructionOptions::FovInstruction>::serialize(stream, (*value.field_of_view));
    }
}

auto Serializer<v827::CameraInstruction>::deserialize(BinaryReader &stream) -> std::expected<v827::CameraInstruction, std::error_code>
{
    v827::CameraInstruction out;
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v818::CameraInstructionOptions::SetInstruction staged{};
            auto v = Serializer<v818::CameraInstructionOptions::SetInstruction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.set = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.clear = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v818::CameraInstructionOptions::FadeInstruction staged{};
            auto v = Serializer<v818::CameraInstructionOptions::FadeInstruction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.fade = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v818::CameraInstructionOptions::TargetInstruction staged{};
            auto v = Serializer<v818::CameraInstructionOptions::TargetInstruction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.target = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.remove_target = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v818::CameraInstructionOptions::FovInstruction staged{};
            auto v = Serializer<v818::CameraInstructionOptions::FovInstruction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.field_of_view = std::move(staged);
        }
    }
    return out;
}

void Serializer<v859::CameraInstruction>::serialize(BinaryWriter &stream, const v859::CameraInstruction &value)
{
    stream.write<bool>(value.set.has_value());
    if (value.set.has_value()) {
        Serializer<v818::CameraInstructionOptions::SetInstruction>::serialize(stream, (*value.set));
    }
    stream.write<bool>(value.clear.has_value());
    if (value.clear.has_value()) {
        stream.write<bool>((*value.clear));
    }
    stream.write<bool>(value.fade.has_value());
    if (value.fade.has_value()) {
        Serializer<v818::CameraInstructionOptions::FadeInstruction>::serialize(stream, (*value.fade));
    }
    stream.write<bool>(value.target.has_value());
    if (value.target.has_value()) {
        Serializer<v818::CameraInstructionOptions::TargetInstruction>::serialize(stream, (*value.target));
    }
    stream.write<bool>(value.remove_target.has_value());
    if (value.remove_target.has_value()) {
        stream.write<bool>((*value.remove_target));
    }
    stream.write<bool>(value.field_of_view.has_value());
    if (value.field_of_view.has_value()) {
        Serializer<v818::CameraInstructionOptions::FovInstruction>::serialize(stream, (*value.field_of_view));
    }
    stream.write<bool>(value.spline.has_value());
    if (value.spline.has_value()) {
        Serializer<v818::CameraInstructionOptions::SplineInstruction>::serialize(stream, (*value.spline));
    }
    stream.write<bool>(value.attach_to_entity.has_value());
    if (value.attach_to_entity.has_value()) {
        Serializer<v818::CameraInstructionOptions::AttachToEntityInstruction>::serialize(stream, (*value.attach_to_entity));
    }
    stream.write<bool>(value.detach_from_entity.has_value());
    if (value.detach_from_entity.has_value()) {
        stream.write<bool>((*value.detach_from_entity));
    }
}

auto Serializer<v859::CameraInstruction>::deserialize(BinaryReader &stream) -> std::expected<v859::CameraInstruction, std::error_code>
{
    v859::CameraInstruction out;
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v818::CameraInstructionOptions::SetInstruction staged{};
            auto v = Serializer<v818::CameraInstructionOptions::SetInstruction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.set = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.clear = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v818::CameraInstructionOptions::FadeInstruction staged{};
            auto v = Serializer<v818::CameraInstructionOptions::FadeInstruction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.fade = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v818::CameraInstructionOptions::TargetInstruction staged{};
            auto v = Serializer<v818::CameraInstructionOptions::TargetInstruction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.target = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.remove_target = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v818::CameraInstructionOptions::FovInstruction staged{};
            auto v = Serializer<v818::CameraInstructionOptions::FovInstruction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.field_of_view = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v818::CameraInstructionOptions::SplineInstruction staged{};
            auto v = Serializer<v818::CameraInstructionOptions::SplineInstruction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.spline = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v818::CameraInstructionOptions::AttachToEntityInstruction staged{};
            auto v = Serializer<v818::CameraInstructionOptions::AttachToEntityInstruction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.attach_to_entity = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.detach_from_entity = std::move(staged);
        }
    }
    return out;
}

void Serializer<v924::CameraInstruction>::serialize(BinaryWriter &stream, const v924::CameraInstruction &value)
{
    stream.write<bool>(value.set.has_value());
    if (value.set.has_value()) {
        Serializer<v924::CameraInstructionOptions::SetInstruction>::serialize(stream, (*value.set));
    }
    stream.write<bool>(value.clear.has_value());
    if (value.clear.has_value()) {
        stream.write<bool>((*value.clear));
    }
    stream.write<bool>(value.fade.has_value());
    if (value.fade.has_value()) {
        Serializer<v924::CameraInstructionOptions::FadeInstruction>::serialize(stream, (*value.fade));
    }
    stream.write<bool>(value.target.has_value());
    if (value.target.has_value()) {
        Serializer<v924::CameraInstructionOptions::TargetInstruction>::serialize(stream, (*value.target));
    }
    stream.write<bool>(value.remove_target.has_value());
    if (value.remove_target.has_value()) {
        stream.write<bool>((*value.remove_target));
    }
    stream.write<bool>(value.field_of_view.has_value());
    if (value.field_of_view.has_value()) {
        Serializer<v924::CameraInstructionOptions::FovInstruction>::serialize(stream, (*value.field_of_view));
    }
    stream.write<bool>(value.spline.has_value());
    if (value.spline.has_value()) {
        Serializer<v924::CameraInstructionOptions::SplineInstruction>::serialize(stream, (*value.spline));
    }
    stream.write<bool>(value.attach_to_entity.has_value());
    if (value.attach_to_entity.has_value()) {
        Serializer<v924::CameraInstructionOptions::AttachToEntityInstruction>::serialize(stream, (*value.attach_to_entity));
    }
    stream.write<bool>(value.detach_from_entity.has_value());
    if (value.detach_from_entity.has_value()) {
        stream.write<bool>((*value.detach_from_entity));
    }
}

auto Serializer<v924::CameraInstruction>::deserialize(BinaryReader &stream) -> std::expected<v924::CameraInstruction, std::error_code>
{
    v924::CameraInstruction out;
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v924::CameraInstructionOptions::SetInstruction staged{};
            auto v = Serializer<v924::CameraInstructionOptions::SetInstruction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.set = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.clear = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v924::CameraInstructionOptions::FadeInstruction staged{};
            auto v = Serializer<v924::CameraInstructionOptions::FadeInstruction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.fade = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v924::CameraInstructionOptions::TargetInstruction staged{};
            auto v = Serializer<v924::CameraInstructionOptions::TargetInstruction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.target = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.remove_target = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v924::CameraInstructionOptions::FovInstruction staged{};
            auto v = Serializer<v924::CameraInstructionOptions::FovInstruction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.field_of_view = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v924::CameraInstructionOptions::SplineInstruction staged{};
            auto v = Serializer<v924::CameraInstructionOptions::SplineInstruction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.spline = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v924::CameraInstructionOptions::AttachToEntityInstruction staged{};
            auto v = Serializer<v924::CameraInstructionOptions::AttachToEntityInstruction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.attach_to_entity = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.detach_from_entity = std::move(staged);
        }
    }
    return out;
}

void Serializer<v944::CameraInstruction>::serialize(BinaryWriter &stream, const v944::CameraInstruction &value)
{
    stream.write<bool>(value.set.has_value());
    if (value.set.has_value()) {
        Serializer<v944::CameraInstructionOptions::SetInstruction>::serialize(stream, (*value.set));
    }
    stream.write<bool>(value.clear.has_value());
    if (value.clear.has_value()) {
        stream.write<bool>((*value.clear));
    }
    stream.write<bool>(value.fade.has_value());
    if (value.fade.has_value()) {
        Serializer<v944::CameraInstructionOptions::FadeInstruction>::serialize(stream, (*value.fade));
    }
    stream.write<bool>(value.target.has_value());
    if (value.target.has_value()) {
        Serializer<v944::CameraInstructionOptions::TargetInstruction>::serialize(stream, (*value.target));
    }
    stream.write<bool>(value.remove_target.has_value());
    if (value.remove_target.has_value()) {
        stream.write<bool>((*value.remove_target));
    }
    stream.write<bool>(value.field_of_view.has_value());
    if (value.field_of_view.has_value()) {
        Serializer<v944::CameraInstructionOptions::FovInstruction>::serialize(stream, (*value.field_of_view));
    }
    stream.write<bool>(value.spline.has_value());
    if (value.spline.has_value()) {
        Serializer<v944::CameraInstructionOptions::SplineInstruction>::serialize(stream, (*value.spline));
    }
    stream.write<bool>(value.attach_to_entity.has_value());
    if (value.attach_to_entity.has_value()) {
        Serializer<v944::CameraInstructionOptions::AttachToEntityInstruction>::serialize(stream, (*value.attach_to_entity));
    }
    stream.write<bool>(value.detach_from_entity.has_value());
    if (value.detach_from_entity.has_value()) {
        stream.write<bool>((*value.detach_from_entity));
    }
}

auto Serializer<v944::CameraInstruction>::deserialize(BinaryReader &stream) -> std::expected<v944::CameraInstruction, std::error_code>
{
    v944::CameraInstruction out;
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v944::CameraInstructionOptions::SetInstruction staged{};
            auto v = Serializer<v944::CameraInstructionOptions::SetInstruction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.set = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.clear = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v944::CameraInstructionOptions::FadeInstruction staged{};
            auto v = Serializer<v944::CameraInstructionOptions::FadeInstruction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.fade = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v944::CameraInstructionOptions::TargetInstruction staged{};
            auto v = Serializer<v944::CameraInstructionOptions::TargetInstruction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.target = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.remove_target = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v944::CameraInstructionOptions::FovInstruction staged{};
            auto v = Serializer<v944::CameraInstructionOptions::FovInstruction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.field_of_view = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v944::CameraInstructionOptions::SplineInstruction staged{};
            auto v = Serializer<v944::CameraInstructionOptions::SplineInstruction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.spline = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v944::CameraInstructionOptions::AttachToEntityInstruction staged{};
            auto v = Serializer<v944::CameraInstructionOptions::AttachToEntityInstruction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.attach_to_entity = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.detach_from_entity = std::move(staged);
        }
    }
    return out;
}

void Serializer<base::CameraInstructionPacket>::serialize(BinaryWriter &stream, const base::CameraInstructionPacket &value)
{
    Serializer<base::CameraInstruction>::serialize(stream, value.camera_instruction);
}

auto Serializer<base::CameraInstructionPacket>::deserialize(BinaryReader &stream) -> std::expected<base::CameraInstructionPacket, std::error_code>
{
    base::CameraInstructionPacket out;
    {
        auto v = Serializer<base::CameraInstruction>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.camera_instruction = *v;
    }
    return out;
}

void Serializer<v748::CameraInstructionPacket>::serialize(BinaryWriter &stream, const v748::CameraInstructionPacket &value)
{
    Serializer<v748::CameraInstruction>::serialize(stream, value.camera_instruction);
}

auto Serializer<v748::CameraInstructionPacket>::deserialize(BinaryReader &stream) -> std::expected<v748::CameraInstructionPacket, std::error_code>
{
    v748::CameraInstructionPacket out;
    {
        auto v = Serializer<v748::CameraInstruction>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.camera_instruction = *v;
    }
    return out;
}

void Serializer<v818::CameraInstructionPacket>::serialize(BinaryWriter &stream, const v818::CameraInstructionPacket &value)
{
    Serializer<v818::CameraInstruction>::serialize(stream, value.camera_instruction);
}

auto Serializer<v818::CameraInstructionPacket>::deserialize(BinaryReader &stream) -> std::expected<v818::CameraInstructionPacket, std::error_code>
{
    v818::CameraInstructionPacket out;
    {
        auto v = Serializer<v818::CameraInstruction>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.camera_instruction = *v;
    }
    return out;
}

void Serializer<v827::CameraInstructionPacket>::serialize(BinaryWriter &stream, const v827::CameraInstructionPacket &value)
{
    Serializer<v827::CameraInstruction>::serialize(stream, value.camera_instruction);
}

auto Serializer<v827::CameraInstructionPacket>::deserialize(BinaryReader &stream) -> std::expected<v827::CameraInstructionPacket, std::error_code>
{
    v827::CameraInstructionPacket out;
    {
        auto v = Serializer<v827::CameraInstruction>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.camera_instruction = *v;
    }
    return out;
}

void Serializer<v859::CameraInstructionPacket>::serialize(BinaryWriter &stream, const v859::CameraInstructionPacket &value)
{
    Serializer<v859::CameraInstruction>::serialize(stream, value.camera_instruction);
}

auto Serializer<v859::CameraInstructionPacket>::deserialize(BinaryReader &stream) -> std::expected<v859::CameraInstructionPacket, std::error_code>
{
    v859::CameraInstructionPacket out;
    {
        auto v = Serializer<v859::CameraInstruction>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.camera_instruction = *v;
    }
    return out;
}

void Serializer<v924::CameraInstructionPacket>::serialize(BinaryWriter &stream, const v924::CameraInstructionPacket &value)
{
    Serializer<v924::CameraInstruction>::serialize(stream, value.camera_instruction);
}

auto Serializer<v924::CameraInstructionPacket>::deserialize(BinaryReader &stream) -> std::expected<v924::CameraInstructionPacket, std::error_code>
{
    v924::CameraInstructionPacket out;
    {
        auto v = Serializer<v924::CameraInstruction>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.camera_instruction = *v;
    }
    return out;
}

void Serializer<v944::CameraInstructionPacket>::serialize(BinaryWriter &stream, const v944::CameraInstructionPacket &value)
{
    Serializer<v944::CameraInstruction>::serialize(stream, value.camera_instruction);
}

auto Serializer<v944::CameraInstructionPacket>::deserialize(BinaryReader &stream) -> std::expected<v944::CameraInstructionPacket, std::error_code>
{
    v944::CameraInstructionPacket out;
    {
        auto v = Serializer<v944::CameraInstruction>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.camera_instruction = *v;
    }
    return out;
}

void Serializer<CameraSplineControlPoint>::serialize(BinaryWriter &stream, const CameraSplineControlPoint &value)
{
    Serializer<Vec3>::serialize(stream, value.position);
}

auto Serializer<CameraSplineControlPoint>::deserialize(BinaryReader &stream) -> std::expected<CameraSplineControlPoint, std::error_code>
{
    CameraSplineControlPoint out;
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.position = *v;
    }
    return out;
}

void Serializer<CameraSplineProgressKeyFrame>::serialize(BinaryWriter &stream, const CameraSplineProgressKeyFrame &value)
{
    stream.write<float>(value.alpha);
    stream.write<float>(value.time_seconds);
    stream.write<bool>(value.easing_type.has_value());
    if (value.easing_type.has_value()) {
        Serializer<EasingType>::serialize(stream, (*value.easing_type));
    }
}

auto Serializer<CameraSplineProgressKeyFrame>::deserialize(BinaryReader &stream) -> std::expected<CameraSplineProgressKeyFrame, std::error_code>
{
    CameraSplineProgressKeyFrame out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.alpha = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.time_seconds = static_cast<float>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            EasingType staged{};
            auto v = Serializer<EasingType>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.easing_type = std::move(staged);
        }
    }
    return out;
}

void Serializer<CameraSplineRotationKeyFrame>::serialize(BinaryWriter &stream, const CameraSplineRotationKeyFrame &value)
{
    Serializer<Vec3>::serialize(stream, value.rotation);
    stream.write<float>(value.time_seconds);
    stream.write<bool>(value.easing_type.has_value());
    if (value.easing_type.has_value()) {
        Serializer<EasingType>::serialize(stream, (*value.easing_type));
    }
}

auto Serializer<CameraSplineRotationKeyFrame>::deserialize(BinaryReader &stream) -> std::expected<CameraSplineRotationKeyFrame, std::error_code>
{
    CameraSplineRotationKeyFrame out;
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.rotation = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.time_seconds = static_cast<float>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            EasingType staged{};
            auto v = Serializer<EasingType>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.easing_type = std::move(staged);
        }
    }
    return out;
}

void Serializer<CameraSplineDefinition>::serialize(BinaryWriter &stream, const CameraSplineDefinition &value)
{
    stream.write(value.name);
    stream.write<float>(value.total_time);
    stream.write(value.spline_type);
    stream.writeVarInt<std::uint32_t>(value.spline_control_points.size());
    for (const auto &e0 : value.spline_control_points) {
        Serializer<CameraSplineControlPoint>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.spline_progress_frames.size());
    for (const auto &e0 : value.spline_progress_frames) {
        Serializer<CameraSplineProgressKeyFrame>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.spline_rotation_frames.size());
    for (const auto &e0 : value.spline_rotation_frames) {
        Serializer<CameraSplineRotationKeyFrame>::serialize(stream, e0);
    }
}

auto Serializer<CameraSplineDefinition>::deserialize(BinaryReader &stream) -> std::expected<CameraSplineDefinition, std::error_code>
{
    CameraSplineDefinition out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.total_time = static_cast<float>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.spline_type = *v;
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.spline_control_points.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.spline_control_points.emplace_back();
            auto v = Serializer<CameraSplineControlPoint>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.spline_control_points.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.spline_progress_frames.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.spline_progress_frames.emplace_back();
            auto v = Serializer<CameraSplineProgressKeyFrame>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.spline_progress_frames.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.spline_rotation_frames.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.spline_rotation_frames.emplace_back();
            auto v = Serializer<CameraSplineRotationKeyFrame>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.spline_rotation_frames.back() = *v;
        }
    }
    return out;
}

void Serializer<v924::CameraSplinePacket>::serialize(BinaryWriter &stream, const v924::CameraSplinePacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.splines.size());
    for (const auto &e0 : value.splines) {
        Serializer<CameraSplineDefinition>::serialize(stream, e0);
    }
}

auto Serializer<v924::CameraSplinePacket>::deserialize(BinaryReader &stream) -> std::expected<v924::CameraSplinePacket, std::error_code>
{
    v924::CameraSplinePacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.splines.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.splines.emplace_back();
            auto v = Serializer<CameraSplineDefinition>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.splines.back() = *v;
        }
    }
    return out;
}

void Serializer<v800::ClientboundControlSchemeSetPacket>::serialize(BinaryWriter &stream, const v800::ClientboundControlSchemeSetPacket &value)
{
    stream.write<std::uint8_t>(value.control_scheme);
}

auto Serializer<v800::ClientboundControlSchemeSetPacket>::deserialize(BinaryReader &stream) -> std::expected<v800::ClientboundControlSchemeSetPacket, std::error_code>
{
    v800::ClientboundControlSchemeSetPacket out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.control_scheme = static_cast<Scheme>(*v);
    }
    return out;
}

}  // namespace bedrock::protocol
