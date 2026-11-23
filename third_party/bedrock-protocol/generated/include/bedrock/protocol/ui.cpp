#include <bedrock/protocol/ui.h>

namespace bedrock::protocol {


void Serializer<v924::ClientboundDataDrivenUIReloadPacket>::serialize(BinaryWriter &stream, const v924::ClientboundDataDrivenUIReloadPacket &value)
{
}

auto Serializer<v924::ClientboundDataDrivenUIReloadPacket>::deserialize(BinaryReader &stream) -> std::expected<v924::ClientboundDataDrivenUIReloadPacket, std::error_code>
{
    v924::ClientboundDataDrivenUIReloadPacket out;
    return out;
}

void Serializer<base::SetHudPacket>::serialize(BinaryWriter &stream, const base::SetHudPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.hud_element.size());
    for (const auto &e0 : value.hud_element) {
        stream.writeVarInt<std::uint32_t>(e0);
    }
    stream.write<std::uint8_t>(value.hud_visible);
}

auto Serializer<base::SetHudPacket>::deserialize(BinaryReader &stream) -> std::expected<base::SetHudPacket, std::error_code>
{
    base::SetHudPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.hud_element.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.hud_element.emplace_back();
            auto v = stream.readVarInt<std::uint32_t>();
            if (!v) return std::unexpected(v.error());
            out.hud_element.back() = static_cast<HudElement>(*v);
        }
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.hud_visible = static_cast<HudVisibility>(*v);
    }
    return out;
}

void Serializer<v786::SetHudPacket>::serialize(BinaryWriter &stream, const v786::SetHudPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.hud_element.size());
    for (const auto &e0 : value.hud_element) {
        stream.writeVarInt<std::int32_t>(e0);
    }
    stream.writeVarInt<std::int32_t>(value.hud_visible);
}

auto Serializer<v786::SetHudPacket>::deserialize(BinaryReader &stream) -> std::expected<v786::SetHudPacket, std::error_code>
{
    v786::SetHudPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.hud_element.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.hud_element.emplace_back();
            auto v = stream.readVarInt<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            out.hud_element.back() = static_cast<HudElement>(*v);
        }
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.hud_visible = static_cast<HudVisibility>(*v);
    }
    return out;
}

void Serializer<ServerboundLoadingScreenPacket>::serialize(BinaryWriter &stream, const ServerboundLoadingScreenPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.loading_screen_packet_type);
    stream.write<bool>(value.loading_screen_id.has_value());
    if (value.loading_screen_id.has_value()) {
        stream.write<std::uint32_t>((*value.loading_screen_id));
    }
}

auto Serializer<ServerboundLoadingScreenPacket>::deserialize(BinaryReader &stream) -> std::expected<ServerboundLoadingScreenPacket, std::error_code>
{
    ServerboundLoadingScreenPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.loading_screen_packet_type = static_cast<ServerboundLoadingScreenPacketType>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::uint32_t staged{};
            auto v = stream.read<std::uint32_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<std::uint32_t>(*v);
            out.loading_screen_id = std::move(staged);
        }
    }
    return out;
}

void Serializer<v944::ClientboundDataDrivenUICloseScreenPacket>::serialize(BinaryWriter &stream, const v944::ClientboundDataDrivenUICloseScreenPacket &value)
{
    stream.write<bool>(value.form_id.has_value());
    if (value.form_id.has_value()) {
        stream.write<std::uint32_t>((*value.form_id));
    }
}

auto Serializer<v944::ClientboundDataDrivenUICloseScreenPacket>::deserialize(BinaryReader &stream) -> std::expected<v944::ClientboundDataDrivenUICloseScreenPacket, std::error_code>
{
    v944::ClientboundDataDrivenUICloseScreenPacket out;
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::uint32_t staged{};
            auto v = stream.read<std::uint32_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<std::uint32_t>(*v);
            out.form_id = std::move(staged);
        }
    }
    return out;
}

void Serializer<v924::ClientboundDataDrivenUIShowScreenPacket>::serialize(BinaryWriter &stream, const v924::ClientboundDataDrivenUIShowScreenPacket &value)
{
    stream.write(value.screen_id);
}

auto Serializer<v924::ClientboundDataDrivenUIShowScreenPacket>::deserialize(BinaryReader &stream) -> std::expected<v924::ClientboundDataDrivenUIShowScreenPacket, std::error_code>
{
    v924::ClientboundDataDrivenUIShowScreenPacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.screen_id = *v;
    }
    return out;
}

void Serializer<v944::ClientboundDataDrivenUIShowScreenPacket>::serialize(BinaryWriter &stream, const v944::ClientboundDataDrivenUIShowScreenPacket &value)
{
    stream.write(value.screen_id);
    stream.write<std::uint32_t>(value.form_id);
    stream.write<bool>(value.data_instance_id.has_value());
    if (value.data_instance_id.has_value()) {
        stream.write<std::uint32_t>((*value.data_instance_id));
    }
}

auto Serializer<v944::ClientboundDataDrivenUIShowScreenPacket>::deserialize(BinaryReader &stream) -> std::expected<v944::ClientboundDataDrivenUIShowScreenPacket, std::error_code>
{
    v944::ClientboundDataDrivenUIShowScreenPacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.screen_id = *v;
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.form_id = static_cast<std::uint32_t>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::uint32_t staged{};
            auto v = stream.read<std::uint32_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<std::uint32_t>(*v);
            out.data_instance_id = std::move(staged);
        }
    }
    return out;
}

void Serializer<v924::ClientboundTextureShiftPacket>::serialize(BinaryWriter &stream, const v924::ClientboundTextureShiftPacket &value)
{
    stream.write<std::uint8_t>(value.action);
    stream.write(value.collection_name);
    stream.write(value.from_step);
    stream.write(value.to_step);
    stream.writeVarInt<std::uint32_t>(value.all_steps.size());
    for (const auto &e0 : value.all_steps) {
        stream.write(e0);
    }
    stream.writeVarInt<std::uint64_t>(value.current_length_in_ticks);
    stream.writeVarInt<std::uint64_t>(value.total_length_in_ticks);
    stream.write<bool>(value.enabled);
}

auto Serializer<v924::ClientboundTextureShiftPacket>::deserialize(BinaryReader &stream) -> std::expected<v924::ClientboundTextureShiftPacket, std::error_code>
{
    v924::ClientboundTextureShiftPacket out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.action = static_cast<v924::ClientboundTextureShiftPacket::Action>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.collection_name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.from_step = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.to_step = *v;
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.all_steps.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.all_steps.emplace_back();
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.all_steps.back() = *v;
        }
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.current_length_in_ticks = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.total_length_in_ticks = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.enabled = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<WorldPosition>::serialize(BinaryWriter &stream, const WorldPosition &value)
{
    Serializer<Vec3>::serialize(stream, value.pos);
    stream.writeVarInt<std::int32_t>(value.dimension_type);
}

auto Serializer<WorldPosition>::deserialize(BinaryReader &stream) -> std::expected<WorldPosition, std::error_code>
{
    WorldPosition out;
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.dimension_type = static_cast<DimensionType>(*v);
    }
    return out;
}

void Serializer<WaypointGroup::WaypointHandle>::serialize(BinaryWriter &stream, const WaypointGroup::WaypointHandle &value)
{
    Serializer<UUID>::serialize(stream, value.uuid);
}

auto Serializer<WaypointGroup::WaypointHandle>::deserialize(BinaryReader &stream) -> std::expected<WaypointGroup::WaypointHandle, std::error_code>
{
    WaypointGroup::WaypointHandle out;
    {
        auto v = Serializer<UUID>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.uuid = *v;
    }
    return out;
}

void Serializer<base::ServerWaypoint::Payload>::serialize(BinaryWriter &stream, const base::ServerWaypoint::Payload &value)
{
    stream.write<std::uint32_t>(value.update_flag);
    stream.write<bool>(value.is_visible.has_value());
    if (value.is_visible.has_value()) {
        stream.write<bool>((*value.is_visible));
    }
    stream.write<bool>(value.world_position.has_value());
    if (value.world_position.has_value()) {
        Serializer<WorldPosition>::serialize(stream, (*value.world_position));
    }
    stream.write<bool>(value.texture_id.has_value());
    if (value.texture_id.has_value()) {
        stream.write<std::uint32_t>((*value.texture_id));
    }
    stream.write<bool>(value.color.has_value());
    if (value.color.has_value()) {
        stream.write<std::int32_t>((*value.color));
    }
    stream.write<bool>(value.client_position_authority.has_value());
    if (value.client_position_authority.has_value()) {
        stream.write<bool>((*value.client_position_authority));
    }
    stream.write<bool>(value.actor_id.has_value());
    if (value.actor_id.has_value()) {
        stream.writeVarInt<std::int64_t>((*value.actor_id));
    }
}

auto Serializer<base::ServerWaypoint::Payload>::deserialize(BinaryReader &stream) -> std::expected<base::ServerWaypoint::Payload, std::error_code>
{
    base::ServerWaypoint::Payload out;
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.update_flag = static_cast<std::uint32_t>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.is_visible = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            WorldPosition staged{};
            auto v = Serializer<WorldPosition>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.world_position = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::uint32_t staged{};
            auto v = stream.read<std::uint32_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<std::uint32_t>(*v);
            out.texture_id = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Color staged{};
            auto v = stream.read<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<Color>(*v);
            out.color = std::move(staged);
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
            out.client_position_authority = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            ActorUniqueID staged{};
            auto v = stream.readVarInt<std::int64_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<ActorUniqueID>(*v);
            out.actor_id = std::move(staged);
        }
    }
    return out;
}

void Serializer<v975::ServerWaypoint::Payload>::serialize(BinaryWriter &stream, const v975::ServerWaypoint::Payload &value)
{
    stream.write<std::uint32_t>(value.update_flag);
    stream.write<bool>(value.is_visible.has_value());
    if (value.is_visible.has_value()) {
        stream.write<bool>((*value.is_visible));
    }
    stream.write<bool>(value.world_position.has_value());
    if (value.world_position.has_value()) {
        Serializer<WorldPosition>::serialize(stream, (*value.world_position));
    }
    stream.write<bool>(value.texture_path.has_value());
    if (value.texture_path.has_value()) {
        stream.write((*value.texture_path));
    }
    stream.write<bool>(value.icon_size.has_value());
    if (value.icon_size.has_value()) {
        Serializer<Vec2>::serialize(stream, (*value.icon_size));
    }
    stream.write<bool>(value.color.has_value());
    if (value.color.has_value()) {
        stream.write<std::int32_t>((*value.color));
    }
    stream.write<bool>(value.client_position_authority.has_value());
    if (value.client_position_authority.has_value()) {
        stream.write<bool>((*value.client_position_authority));
    }
    stream.write<bool>(value.actor_id.has_value());
    if (value.actor_id.has_value()) {
        stream.writeVarInt<std::int64_t>((*value.actor_id));
    }
}

auto Serializer<v975::ServerWaypoint::Payload>::deserialize(BinaryReader &stream) -> std::expected<v975::ServerWaypoint::Payload, std::error_code>
{
    v975::ServerWaypoint::Payload out;
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.update_flag = static_cast<std::uint32_t>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            bool staged{};
            auto v = stream.read<bool>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<bool>(*v);
            out.is_visible = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            WorldPosition staged{};
            auto v = Serializer<WorldPosition>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.world_position = std::move(staged);
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
            out.texture_path = std::move(staged);
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
            out.icon_size = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Color staged{};
            auto v = stream.read<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<Color>(*v);
            out.color = std::move(staged);
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
            out.client_position_authority = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            ActorUniqueID staged{};
            auto v = stream.readVarInt<std::int64_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<ActorUniqueID>(*v);
            out.actor_id = std::move(staged);
        }
    }
    return out;
}

void Serializer<base::LocatorBarWaypointPayload>::serialize(BinaryWriter &stream, const base::LocatorBarWaypointPayload &value)
{
    Serializer<WaypointGroup::WaypointHandle>::serialize(stream, value.handle);
    Serializer<base::ServerWaypoint::Payload>::serialize(stream, value.payload);
    stream.write<std::uint8_t>(value.action);
}

auto Serializer<base::LocatorBarWaypointPayload>::deserialize(BinaryReader &stream) -> std::expected<base::LocatorBarWaypointPayload, std::error_code>
{
    base::LocatorBarWaypointPayload out;
    {
        auto v = Serializer<WaypointGroup::WaypointHandle>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.handle = *v;
    }
    {
        auto v = Serializer<base::ServerWaypoint::Payload>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.payload = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.action = static_cast<ServerWaypointGroup::Action>(*v);
    }
    return out;
}

void Serializer<v975::LocatorBarWaypointPayload>::serialize(BinaryWriter &stream, const v975::LocatorBarWaypointPayload &value)
{
    Serializer<WaypointGroup::WaypointHandle>::serialize(stream, value.handle);
    Serializer<v975::ServerWaypoint::Payload>::serialize(stream, value.payload);
    stream.write<std::uint8_t>(value.action);
}

auto Serializer<v975::LocatorBarWaypointPayload>::deserialize(BinaryReader &stream) -> std::expected<v975::LocatorBarWaypointPayload, std::error_code>
{
    v975::LocatorBarWaypointPayload out;
    {
        auto v = Serializer<WaypointGroup::WaypointHandle>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.handle = *v;
    }
    {
        auto v = Serializer<v975::ServerWaypoint::Payload>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.payload = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.action = static_cast<ServerWaypointGroup::Action>(*v);
    }
    return out;
}

void Serializer<v944::LocatorBarPacket>::serialize(BinaryWriter &stream, const v944::LocatorBarPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.waypoints.size());
    for (const auto &e0 : value.waypoints) {
        Serializer<base::LocatorBarWaypointPayload>::serialize(stream, e0);
    }
}

auto Serializer<v944::LocatorBarPacket>::deserialize(BinaryReader &stream) -> std::expected<v944::LocatorBarPacket, std::error_code>
{
    v944::LocatorBarPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.waypoints.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.waypoints.emplace_back();
            auto v = Serializer<base::LocatorBarWaypointPayload>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.waypoints.back() = *v;
        }
    }
    return out;
}

void Serializer<v975::LocatorBarPacket>::serialize(BinaryWriter &stream, const v975::LocatorBarPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.waypoints.size());
    for (const auto &e0 : value.waypoints) {
        Serializer<v975::LocatorBarWaypointPayload>::serialize(stream, e0);
    }
}

auto Serializer<v975::LocatorBarPacket>::deserialize(BinaryReader &stream) -> std::expected<v975::LocatorBarPacket, std::error_code>
{
    v975::LocatorBarPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.waypoints.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.waypoints.emplace_back();
            auto v = Serializer<v975::LocatorBarWaypointPayload>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.waypoints.back() = *v;
        }
    }
    return out;
}

void Serializer<DataDrivenScreenClosedReason>::serialize(BinaryWriter &stream, DataDrivenScreenClosedReason value)
{
    stream.write(enum_name(value));
}

auto Serializer<DataDrivenScreenClosedReason>::deserialize(BinaryReader &stream) -> std::expected<DataDrivenScreenClosedReason, std::error_code>
{
    auto v = stream.read<std::string>();
    if (!v) return std::unexpected(v.error());
    const auto value = enum_cast<DataDrivenScreenClosedReason>(*v);
    if (!value) return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
    return *value;
}

void Serializer<v944::ServerboundDataDrivenScreenClosedPacket>::serialize(BinaryWriter &stream, const v944::ServerboundDataDrivenScreenClosedPacket &value)
{
    stream.write<std::uint32_t>(value.form_id);
    Serializer<DataDrivenScreenClosedReason>::serialize(stream, value.close_reason);
}

auto Serializer<v944::ServerboundDataDrivenScreenClosedPacket>::deserialize(BinaryReader &stream) -> std::expected<v944::ServerboundDataDrivenScreenClosedPacket, std::error_code>
{
    v944::ServerboundDataDrivenScreenClosedPacket out;
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.form_id = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = Serializer<DataDrivenScreenClosedReason>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.close_reason = *v;
    }
    return out;
}

void Serializer<ModalFormRequestPacket>::serialize(BinaryWriter &stream, const ModalFormRequestPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.form_id);
    stream.write(value.form_json);
}

auto Serializer<ModalFormRequestPacket>::deserialize(BinaryReader &stream) -> std::expected<ModalFormRequestPacket, std::error_code>
{
    ModalFormRequestPacket out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.form_id = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.form_json = *v;
    }
    return out;
}

void Serializer<ServerSettingsRequestPacket>::serialize(BinaryWriter &stream, const ServerSettingsRequestPacket &value)
{
}

auto Serializer<ServerSettingsRequestPacket>::deserialize(BinaryReader &stream) -> std::expected<ServerSettingsRequestPacket, std::error_code>
{
    ServerSettingsRequestPacket out;
    return out;
}

void Serializer<ServerSettingsResponsePacket>::serialize(BinaryWriter &stream, const ServerSettingsResponsePacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.form_id);
    stream.write(value.form_json);
}

auto Serializer<ServerSettingsResponsePacket>::deserialize(BinaryReader &stream) -> std::expected<ServerSettingsResponsePacket, std::error_code>
{
    ServerSettingsResponsePacket out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.form_id = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.form_json = *v;
    }
    return out;
}

void Serializer<ClientboundCloseFormPacket>::serialize(BinaryWriter &stream, const ClientboundCloseFormPacket &value)
{
}

auto Serializer<ClientboundCloseFormPacket>::deserialize(BinaryReader &stream) -> std::expected<ClientboundCloseFormPacket, std::error_code>
{
    ClientboundCloseFormPacket out;
    return out;
}

void Serializer<ModalFormResponsePacket>::serialize(BinaryWriter &stream, const ModalFormResponsePacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.form_id);
    stream.write<bool>(value.json_response.has_value());
    if (value.json_response.has_value()) {
        stream.write((*value.json_response));
    }
    stream.write<bool>(value.form_cancel_reason.has_value());
    if (value.form_cancel_reason.has_value()) {
        stream.write<std::uint8_t>((*value.form_cancel_reason));
    }
}

auto Serializer<ModalFormResponsePacket>::deserialize(BinaryReader &stream) -> std::expected<ModalFormResponsePacket, std::error_code>
{
    ModalFormResponsePacket out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.form_id = static_cast<std::uint32_t>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::string staged{};
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.json_response = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            ModalFormCancelReason staged{};
            auto v = stream.read<std::uint8_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<ModalFormCancelReason>(*v);
            out.form_cancel_reason = std::move(staged);
        }
    }
    return out;
}

void Serializer<OnScreenTextureAnimationPacket>::serialize(BinaryWriter &stream, const OnScreenTextureAnimationPacket &value)
{
    stream.write<std::uint32_t>(value.effect_id);
}

auto Serializer<OnScreenTextureAnimationPacket>::deserialize(BinaryReader &stream) -> std::expected<OnScreenTextureAnimationPacket, std::error_code>
{
    OnScreenTextureAnimationPacket out;
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.effect_id = static_cast<std::uint32_t>(*v);
    }
    return out;
}

void Serializer<v924::ClientboundDataDrivenUICloseAllScreensPacket>::serialize(BinaryWriter &stream, const v924::ClientboundDataDrivenUICloseAllScreensPacket &value)
{
}

auto Serializer<v924::ClientboundDataDrivenUICloseAllScreensPacket>::deserialize(BinaryReader &stream) -> std::expected<v924::ClientboundDataDrivenUICloseAllScreensPacket, std::error_code>
{
    v924::ClientboundDataDrivenUICloseAllScreensPacket out;
    return out;
}

}  // namespace bedrock::protocol
