#include <bedrock/protocol/presence.h>

namespace bedrock::protocol {


void Serializer<base::PresenceConfiguration>::serialize(BinaryWriter &stream, const base::PresenceConfiguration &value)
{
    stream.write(value.experience_name);
    stream.write(value.world_name);
}

auto Serializer<base::PresenceConfiguration>::deserialize(BinaryReader &stream) -> std::expected<base::PresenceConfiguration, std::error_code>
{
    base::PresenceConfiguration out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.experience_name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.world_name = *v;
    }
    return out;
}

void Serializer<v1001::PresenceConfiguration>::serialize(BinaryWriter &stream, const v1001::PresenceConfiguration &value)
{
    stream.write<bool>(value.experience_name.has_value());
    if (value.experience_name.has_value()) {
        stream.write((*value.experience_name));
    }
    stream.write<bool>(value.world_name.has_value());
    if (value.world_name.has_value()) {
        stream.write((*value.world_name));
    }
    stream.write(value.rich_presence_id);
}

auto Serializer<v1001::PresenceConfiguration>::deserialize(BinaryReader &stream) -> std::expected<v1001::PresenceConfiguration, std::error_code>
{
    v1001::PresenceConfiguration out;
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::string staged{};
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.experience_name = std::move(staged);
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
            out.world_name = std::move(staged);
        }
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.rich_presence_id = *v;
    }
    return out;
}

void Serializer<v2168::PresenceConfiguration>::serialize(BinaryWriter &stream, const v2168::PresenceConfiguration &value)
{
    stream.write<bool>(value.rich_presence_id.has_value());
    if (value.rich_presence_id.has_value()) {
        stream.write((*value.rich_presence_id));
    }
}

auto Serializer<v2168::PresenceConfiguration>::deserialize(BinaryReader &stream) -> std::expected<v2168::PresenceConfiguration, std::error_code>
{
    v2168::PresenceConfiguration out;
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::string staged{};
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.rich_presence_id = std::move(staged);
        }
    }
    return out;
}

void Serializer<base::GatheringsConfigurationJoinInfo>::serialize(BinaryWriter &stream, const base::GatheringsConfigurationJoinInfo &value)
{
    stream.write(value.experience_id);
    stream.write(value.experience_name);
    stream.write(value.experience_world_id);
    stream.write(value.experience_world_name);
    stream.write(value.creator_id);
    stream.write(value.store_id);
    stream.write(value.store_name);
}

auto Serializer<base::GatheringsConfigurationJoinInfo>::deserialize(BinaryReader &stream) -> std::expected<base::GatheringsConfigurationJoinInfo, std::error_code>
{
    base::GatheringsConfigurationJoinInfo out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.experience_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.experience_name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.experience_world_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.experience_world_name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.creator_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.store_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.store_name = *v;
    }
    return out;
}

void Serializer<v944::GatheringsConfigurationJoinInfo>::serialize(BinaryWriter &stream, const v944::GatheringsConfigurationJoinInfo &value)
{
    Serializer<UUID>::serialize(stream, value.experience_id);
    stream.write(value.experience_name);
    Serializer<UUID>::serialize(stream, value.experience_world_id);
    stream.write(value.experience_world_name);
    stream.write(value.creator_id);
    Serializer<UUID>::serialize(stream, value.target_id);
    stream.write(value.scenario_id);
    stream.write(value.server_id);
}

auto Serializer<v944::GatheringsConfigurationJoinInfo>::deserialize(BinaryReader &stream) -> std::expected<v944::GatheringsConfigurationJoinInfo, std::error_code>
{
    v944::GatheringsConfigurationJoinInfo out;
    {
        auto v = Serializer<UUID>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.experience_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.experience_name = *v;
    }
    {
        auto v = Serializer<UUID>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.experience_world_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.experience_world_name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.creator_id = *v;
    }
    {
        auto v = Serializer<UUID>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.target_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.scenario_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.server_id = *v;
    }
    return out;
}

void Serializer<v2168::GatheringsConfigurationJoinInfo>::serialize(BinaryWriter &stream, const v2168::GatheringsConfigurationJoinInfo &value)
{
    Serializer<UUID>::serialize(stream, value.experience_id);
    stream.write(value.experience_name);
    stream.write<bool>(value.experience_world_id.has_value());
    if (value.experience_world_id.has_value()) {
        Serializer<UUID>::serialize(stream, (*value.experience_world_id));
    }
    stream.write<bool>(value.experience_world_name.has_value());
    if (value.experience_world_name.has_value()) {
        stream.write((*value.experience_world_name));
    }
    stream.write(value.creator_id);
    stream.write<bool>(value.target_id.has_value());
    if (value.target_id.has_value()) {
        Serializer<UUID>::serialize(stream, (*value.target_id));
    }
    stream.write<bool>(value.mpsas_scenario_id.has_value());
    if (value.mpsas_scenario_id.has_value()) {
        stream.write((*value.mpsas_scenario_id));
    }
    stream.write<bool>(value.server_id.has_value());
    if (value.server_id.has_value()) {
        stream.write((*value.server_id));
    }
}

auto Serializer<v2168::GatheringsConfigurationJoinInfo>::deserialize(BinaryReader &stream) -> std::expected<v2168::GatheringsConfigurationJoinInfo, std::error_code>
{
    v2168::GatheringsConfigurationJoinInfo out;
    {
        auto v = Serializer<UUID>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.experience_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.experience_name = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            UUID staged{};
            auto v = Serializer<UUID>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.experience_world_id = std::move(staged);
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
            out.experience_world_name = std::move(staged);
        }
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.creator_id = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            UUID staged{};
            auto v = Serializer<UUID>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.target_id = std::move(staged);
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
            out.mpsas_scenario_id = std::move(staged);
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
            out.server_id = std::move(staged);
        }
    }
    return out;
}

void Serializer<ClientStoreEntryPointConfiguration>::serialize(BinaryWriter &stream, const ClientStoreEntryPointConfiguration &value)
{
    stream.write(value.store_id);
    stream.write(value.store_name);
}

auto Serializer<ClientStoreEntryPointConfiguration>::deserialize(BinaryReader &stream) -> std::expected<ClientStoreEntryPointConfiguration, std::error_code>
{
    ClientStoreEntryPointConfiguration out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.store_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.store_name = *v;
    }
    return out;
}

void Serializer<base::ServerConfigurationJoinInfo>::serialize(BinaryWriter &stream, const base::ServerConfigurationJoinInfo &value)
{
    stream.write<bool>(value.gatherings_configuration.has_value());
    if (value.gatherings_configuration.has_value()) {
        Serializer<base::GatheringsConfigurationJoinInfo>::serialize(stream, (*value.gatherings_configuration));
    }
}

auto Serializer<base::ServerConfigurationJoinInfo>::deserialize(BinaryReader &stream) -> std::expected<base::ServerConfigurationJoinInfo, std::error_code>
{
    base::ServerConfigurationJoinInfo out;
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            base::GatheringsConfigurationJoinInfo staged{};
            auto v = Serializer<base::GatheringsConfigurationJoinInfo>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.gatherings_configuration = std::move(staged);
        }
    }
    return out;
}

void Serializer<v944::ServerConfigurationJoinInfo>::serialize(BinaryWriter &stream, const v944::ServerConfigurationJoinInfo &value)
{
    stream.write<bool>(value.gatherings_configuration.has_value());
    if (value.gatherings_configuration.has_value()) {
        Serializer<v944::GatheringsConfigurationJoinInfo>::serialize(stream, (*value.gatherings_configuration));
    }
    stream.write<bool>(value.client_store_entry_point_configuration.has_value());
    if (value.client_store_entry_point_configuration.has_value()) {
        Serializer<ClientStoreEntryPointConfiguration>::serialize(stream, (*value.client_store_entry_point_configuration));
    }
    stream.write<bool>(value.presence_configuration.has_value());
    if (value.presence_configuration.has_value()) {
        Serializer<base::PresenceConfiguration>::serialize(stream, (*value.presence_configuration));
    }
}

auto Serializer<v944::ServerConfigurationJoinInfo>::deserialize(BinaryReader &stream) -> std::expected<v944::ServerConfigurationJoinInfo, std::error_code>
{
    v944::ServerConfigurationJoinInfo out;
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v944::GatheringsConfigurationJoinInfo staged{};
            auto v = Serializer<v944::GatheringsConfigurationJoinInfo>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.gatherings_configuration = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            ClientStoreEntryPointConfiguration staged{};
            auto v = Serializer<ClientStoreEntryPointConfiguration>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.client_store_entry_point_configuration = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            base::PresenceConfiguration staged{};
            auto v = Serializer<base::PresenceConfiguration>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.presence_configuration = std::move(staged);
        }
    }
    return out;
}

void Serializer<v1001::ServerConfigurationJoinInfo>::serialize(BinaryWriter &stream, const v1001::ServerConfigurationJoinInfo &value)
{
    stream.write<bool>(value.gatherings_configuration.has_value());
    if (value.gatherings_configuration.has_value()) {
        Serializer<v944::GatheringsConfigurationJoinInfo>::serialize(stream, (*value.gatherings_configuration));
    }
    stream.write<bool>(value.client_store_entry_point_configuration.has_value());
    if (value.client_store_entry_point_configuration.has_value()) {
        Serializer<ClientStoreEntryPointConfiguration>::serialize(stream, (*value.client_store_entry_point_configuration));
    }
    stream.write<bool>(value.presence_configuration.has_value());
    if (value.presence_configuration.has_value()) {
        Serializer<v1001::PresenceConfiguration>::serialize(stream, (*value.presence_configuration));
    }
}

auto Serializer<v1001::ServerConfigurationJoinInfo>::deserialize(BinaryReader &stream) -> std::expected<v1001::ServerConfigurationJoinInfo, std::error_code>
{
    v1001::ServerConfigurationJoinInfo out;
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v944::GatheringsConfigurationJoinInfo staged{};
            auto v = Serializer<v944::GatheringsConfigurationJoinInfo>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.gatherings_configuration = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            ClientStoreEntryPointConfiguration staged{};
            auto v = Serializer<ClientStoreEntryPointConfiguration>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.client_store_entry_point_configuration = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v1001::PresenceConfiguration staged{};
            auto v = Serializer<v1001::PresenceConfiguration>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.presence_configuration = std::move(staged);
        }
    }
    return out;
}

void Serializer<v2168::ServerConfigurationJoinInfo>::serialize(BinaryWriter &stream, const v2168::ServerConfigurationJoinInfo &value)
{
    stream.write<bool>(value.gatherings_configuration.has_value());
    if (value.gatherings_configuration.has_value()) {
        Serializer<v2168::GatheringsConfigurationJoinInfo>::serialize(stream, (*value.gatherings_configuration));
    }
    stream.write<bool>(value.client_store_entry_point_configuration.has_value());
    if (value.client_store_entry_point_configuration.has_value()) {
        Serializer<ClientStoreEntryPointConfiguration>::serialize(stream, (*value.client_store_entry_point_configuration));
    }
    stream.write<bool>(value.presence_configuration.has_value());
    if (value.presence_configuration.has_value()) {
        Serializer<v2168::PresenceConfiguration>::serialize(stream, (*value.presence_configuration));
    }
}

auto Serializer<v2168::ServerConfigurationJoinInfo>::deserialize(BinaryReader &stream) -> std::expected<v2168::ServerConfigurationJoinInfo, std::error_code>
{
    v2168::ServerConfigurationJoinInfo out;
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v2168::GatheringsConfigurationJoinInfo staged{};
            auto v = Serializer<v2168::GatheringsConfigurationJoinInfo>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.gatherings_configuration = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            ClientStoreEntryPointConfiguration staged{};
            auto v = Serializer<ClientStoreEntryPointConfiguration>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.client_store_entry_point_configuration = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v2168::PresenceConfiguration staged{};
            auto v = Serializer<v2168::PresenceConfiguration>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.presence_configuration = std::move(staged);
        }
    }
    return out;
}

void Serializer<ServerTelemetryData>::serialize(BinaryWriter &stream, const ServerTelemetryData &value)
{
    stream.write(value.server_id);
    stream.write(value.scenario_id);
    stream.write(value.world_id);
    stream.write(value.owner_id);
}

auto Serializer<ServerTelemetryData>::deserialize(BinaryReader &stream) -> std::expected<ServerTelemetryData, std::error_code>
{
    ServerTelemetryData out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.server_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.scenario_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.world_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.owner_id = *v;
    }
    return out;
}

void Serializer<v975::ServerPresenceInfoPacket>::serialize(BinaryWriter &stream, const v975::ServerPresenceInfoPacket &value)
{
    stream.write<bool>(value.presence_configuration.has_value());
    if (value.presence_configuration.has_value()) {
        Serializer<base::PresenceConfiguration>::serialize(stream, (*value.presence_configuration));
    }
}

auto Serializer<v975::ServerPresenceInfoPacket>::deserialize(BinaryReader &stream) -> std::expected<v975::ServerPresenceInfoPacket, std::error_code>
{
    v975::ServerPresenceInfoPacket out;
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            base::PresenceConfiguration staged{};
            auto v = Serializer<base::PresenceConfiguration>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.presence_configuration = std::move(staged);
        }
    }
    return out;
}

void Serializer<v1001::ServerPresenceInfoPacket>::serialize(BinaryWriter &stream, const v1001::ServerPresenceInfoPacket &value)
{
    stream.write<bool>(value.presence_configuration.has_value());
    if (value.presence_configuration.has_value()) {
        Serializer<v1001::PresenceConfiguration>::serialize(stream, (*value.presence_configuration));
    }
}

auto Serializer<v1001::ServerPresenceInfoPacket>::deserialize(BinaryReader &stream) -> std::expected<v1001::ServerPresenceInfoPacket, std::error_code>
{
    v1001::ServerPresenceInfoPacket out;
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v1001::PresenceConfiguration staged{};
            auto v = Serializer<v1001::PresenceConfiguration>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.presence_configuration = std::move(staged);
        }
    }
    return out;
}

void Serializer<v2168::ServerPresenceInfoPacket>::serialize(BinaryWriter &stream, const v2168::ServerPresenceInfoPacket &value)
{
    stream.write<bool>(value.presence_configuration.has_value());
    if (value.presence_configuration.has_value()) {
        Serializer<v2168::PresenceConfiguration>::serialize(stream, (*value.presence_configuration));
    }
}

auto Serializer<v2168::ServerPresenceInfoPacket>::deserialize(BinaryReader &stream) -> std::expected<v2168::ServerPresenceInfoPacket, std::error_code>
{
    v2168::ServerPresenceInfoPacket out;
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v2168::PresenceConfiguration staged{};
            auto v = Serializer<v2168::PresenceConfiguration>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.presence_configuration = std::move(staged);
        }
    }
    return out;
}

void Serializer<base::TransferPacket>::serialize(BinaryWriter &stream, const base::TransferPacket &value)
{
    stream.write(value.destination);
    stream.write<std::uint16_t>(value.destination_port);
    stream.write<bool>(value.reload_world);
}

auto Serializer<base::TransferPacket>::deserialize(BinaryReader &stream) -> std::expected<base::TransferPacket, std::error_code>
{
    base::TransferPacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.destination = *v;
    }
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.destination_port = static_cast<std::uint16_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.reload_world = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v944::TransferPacket>::serialize(BinaryWriter &stream, const v944::TransferPacket &value)
{
    stream.write(value.destination);
    stream.write<std::uint16_t>(value.destination_port);
    stream.write<bool>(value.reload_world);
}

auto Serializer<v944::TransferPacket>::deserialize(BinaryReader &stream) -> std::expected<v944::TransferPacket, std::error_code>
{
    v944::TransferPacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.destination = *v;
    }
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.destination_port = static_cast<std::uint16_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.reload_world = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v2168::TransferPacket>::serialize(BinaryWriter &stream, const v2168::TransferPacket &value)
{
    stream.write(value.destination);
    stream.write<std::uint16_t>(value.destination_port);
    stream.write<bool>(value.reload_world);
    stream.write<bool>(value.gatherings_configuration.has_value());
    if (value.gatherings_configuration.has_value()) {
        Serializer<v2168::GatheringsConfigurationJoinInfo>::serialize(stream, (*value.gatherings_configuration));
    }
}

auto Serializer<v2168::TransferPacket>::deserialize(BinaryReader &stream) -> std::expected<v2168::TransferPacket, std::error_code>
{
    v2168::TransferPacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.destination = *v;
    }
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.destination_port = static_cast<std::uint16_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.reload_world = static_cast<bool>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v2168::GatheringsConfigurationJoinInfo staged{};
            auto v = Serializer<v2168::GatheringsConfigurationJoinInfo>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.gatherings_configuration = std::move(staged);
        }
    }
    return out;
}

void Serializer<v1001::PartyDestinationCookieResponsePacket>::serialize(BinaryWriter &stream, const v1001::PartyDestinationCookieResponsePacket &value)
{
    stream.write(value.cookie);
    stream.write<bool>(value.accepted);
}

auto Serializer<v1001::PartyDestinationCookieResponsePacket>::deserialize(BinaryReader &stream) -> std::expected<v1001::PartyDestinationCookieResponsePacket, std::error_code>
{
    v1001::PartyDestinationCookieResponsePacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.cookie = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.accepted = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<PlayerPartyInfo>::serialize(BinaryWriter &stream, const PlayerPartyInfo &value)
{
    stream.write(value.party_id);
    stream.write<bool>(value.is_leader);
}

auto Serializer<PlayerPartyInfo>::deserialize(BinaryReader &stream) -> std::expected<PlayerPartyInfo, std::error_code>
{
    PlayerPartyInfo out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.party_id = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_leader = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v944::PartyChangedPacket>::serialize(BinaryWriter &stream, const v944::PartyChangedPacket &value)
{
    stream.write<bool>(value.party_id.has_value());
    if (value.party_id.has_value()) {
        stream.write((*value.party_id));
    }
}

auto Serializer<v944::PartyChangedPacket>::deserialize(BinaryReader &stream) -> std::expected<v944::PartyChangedPacket, std::error_code>
{
    v944::PartyChangedPacket out;
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::string staged{};
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.party_id = std::move(staged);
        }
    }
    return out;
}

void Serializer<v975::PartyChangedPacket>::serialize(BinaryWriter &stream, const v975::PartyChangedPacket &value)
{
    stream.write<bool>(value.party_info.has_value());
    if (value.party_info.has_value()) {
        Serializer<PlayerPartyInfo>::serialize(stream, (*value.party_info));
    }
}

auto Serializer<v975::PartyChangedPacket>::deserialize(BinaryReader &stream) -> std::expected<v975::PartyChangedPacket, std::error_code>
{
    v975::PartyChangedPacket out;
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            PlayerPartyInfo staged{};
            auto v = Serializer<PlayerPartyInfo>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.party_info = std::move(staged);
        }
    }
    return out;
}

void Serializer<PartyDestinationCookieIntent>::serialize(BinaryWriter &stream, PartyDestinationCookieIntent value)
{
    stream.write(enum_name(value));
}

auto Serializer<PartyDestinationCookieIntent>::deserialize(BinaryReader &stream) -> std::expected<PartyDestinationCookieIntent, std::error_code>
{
    auto v = stream.read<std::string>();
    if (!v) return std::unexpected(v.error());
    const auto value = enum_cast<PartyDestinationCookieIntent>(*v);
    if (!value) return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
    return *value;
}

void Serializer<v1001::SendPartyDestinationCookiePacket>::serialize(BinaryWriter &stream, const v1001::SendPartyDestinationCookiePacket &value)
{
    stream.write(value.cookie);
    Serializer<PartyDestinationCookieIntent>::serialize(stream, value.intent);
    stream.write(value.destination_name);
}

auto Serializer<v1001::SendPartyDestinationCookiePacket>::deserialize(BinaryReader &stream) -> std::expected<v1001::SendPartyDestinationCookiePacket, std::error_code>
{
    v1001::SendPartyDestinationCookiePacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.cookie = *v;
    }
    {
        auto v = Serializer<PartyDestinationCookieIntent>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.intent = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.destination_name = *v;
    }
    return out;
}

void Serializer<MatchmakingStateOptions>::serialize(BinaryWriter &stream, const MatchmakingStateOptions &value)
{
    stream.write<bool>(value.triggering_player_name.has_value());
    if (value.triggering_player_name.has_value()) {
        stream.write((*value.triggering_player_name));
    }
    stream.write<bool>(value.triggered_by_local_player.has_value());
    if (value.triggered_by_local_player.has_value()) {
        stream.write<bool>((*value.triggered_by_local_player));
    }
}

auto Serializer<MatchmakingStateOptions>::deserialize(BinaryReader &stream) -> std::expected<MatchmakingStateOptions, std::error_code>
{
    MatchmakingStateOptions out;
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::string staged{};
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.triggering_player_name = std::move(staged);
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
            out.triggered_by_local_player = std::move(staged);
        }
    }
    return out;
}

void Serializer<v2225::ClientboundMatchmakingStatePacket>::serialize(BinaryWriter &stream, const v2225::ClientboundMatchmakingStatePacket &value)
{
    stream.write<std::uint8_t>(value.state);
    stream.write(value.destination_name);
    stream.write<bool>(value.options.has_value());
    if (value.options.has_value()) {
        Serializer<MatchmakingStateOptions>::serialize(stream, (*value.options));
    }
}

auto Serializer<v2225::ClientboundMatchmakingStatePacket>::deserialize(BinaryReader &stream) -> std::expected<v2225::ClientboundMatchmakingStatePacket, std::error_code>
{
    v2225::ClientboundMatchmakingStatePacket out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.state = static_cast<MatchmakingState>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.destination_name = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            MatchmakingStateOptions staged{};
            auto v = Serializer<MatchmakingStateOptions>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.options = std::move(staged);
        }
    }
    return out;
}

void Serializer<v2225::ServerboundMatchmakingCancelPacket>::serialize(BinaryWriter &stream, const v2225::ServerboundMatchmakingCancelPacket &value)
{
}

auto Serializer<v2225::ServerboundMatchmakingCancelPacket>::deserialize(BinaryReader &stream) -> std::expected<v2225::ServerboundMatchmakingCancelPacket, std::error_code>
{
    v2225::ServerboundMatchmakingCancelPacket out;
    return out;
}

}  // namespace bedrock::protocol
