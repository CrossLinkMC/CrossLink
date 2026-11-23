#include <bedrock/protocol/boss.h>

namespace bedrock::protocol {


void Serializer<base::BossEventPacket>::serialize(BinaryWriter &stream, const base::BossEventPacket &value)
{
    stream.writeVarInt<std::int64_t>(value.boss_id);
    stream.write<std::uint8_t>(value.event_type);
    if (((value.event_type) == (BossEventUpdateType::PlayerAdded)) || ((value.event_type) == (BossEventUpdateType::PlayerRemoved)) || ((value.event_type) == (BossEventUpdateType::Query))) {
        stream.writeVarInt<std::int64_t>(value.player_id);
    }
    if (((value.event_type) == (BossEventUpdateType::Add)) || ((value.event_type) == (BossEventUpdateType::UpdateName))) {
        stream.write(value.name);
    }
    if (((value.event_type) == (BossEventUpdateType::Add)) || ((value.event_type) == (BossEventUpdateType::UpdatePercent))) {
        stream.write<float>(value.health_percent);
    }
    if (((value.event_type) == (BossEventUpdateType::Add)) || ((value.event_type) == (BossEventUpdateType::UpdateProperties))) {
        stream.write<std::uint8_t>(value.darken_screen);
        stream.write<std::uint8_t>(value.create_world_fog);
    }
    if (((value.event_type) == (BossEventUpdateType::Add)) || ((value.event_type) == (BossEventUpdateType::UpdateProperties)) || ((value.event_type) == (BossEventUpdateType::UpdateStyle))) {
        stream.write<std::uint8_t>(value.color);
        stream.write<std::uint8_t>(value.overlay);
    }
}

auto Serializer<base::BossEventPacket>::deserialize(BinaryReader &stream) -> std::expected<base::BossEventPacket, std::error_code>
{
    base::BossEventPacket out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.boss_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.event_type = static_cast<BossEventUpdateType>(*v);
    }
    if (((out.event_type) == (BossEventUpdateType::PlayerAdded)) || ((out.event_type) == (BossEventUpdateType::PlayerRemoved)) || ((out.event_type) == (BossEventUpdateType::Query))) {
        {
            auto v = stream.readVarInt<std::int64_t>();
            if (!v) return std::unexpected(v.error());
            out.player_id = static_cast<ActorUniqueID>(*v);
        }
    }
    if (((out.event_type) == (BossEventUpdateType::Add)) || ((out.event_type) == (BossEventUpdateType::UpdateName))) {
        {
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.name = *v;
        }
    }
    if (((out.event_type) == (BossEventUpdateType::Add)) || ((out.event_type) == (BossEventUpdateType::UpdatePercent))) {
        {
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            out.health_percent = static_cast<float>(*v);
        }
    }
    if (((out.event_type) == (BossEventUpdateType::Add)) || ((out.event_type) == (BossEventUpdateType::UpdateProperties))) {
        {
            auto v = stream.read<std::uint8_t>();
            if (!v) return std::unexpected(v.error());
            out.darken_screen = static_cast<std::uint8_t>(*v);
        }
        {
            auto v = stream.read<std::uint8_t>();
            if (!v) return std::unexpected(v.error());
            out.create_world_fog = static_cast<std::uint8_t>(*v);
        }
    }
    if (((out.event_type) == (BossEventUpdateType::Add)) || ((out.event_type) == (BossEventUpdateType::UpdateProperties)) || ((out.event_type) == (BossEventUpdateType::UpdateStyle))) {
        {
            auto v = stream.read<std::uint8_t>();
            if (!v) return std::unexpected(v.error());
            out.color = static_cast<BossBarColor>(*v);
        }
        {
            auto v = stream.read<std::uint8_t>();
            if (!v) return std::unexpected(v.error());
            out.overlay = static_cast<BossBarOverlay>(*v);
        }
    }
    return out;
}

void Serializer<v776::BossEventPacket>::serialize(BinaryWriter &stream, const v776::BossEventPacket &value)
{
    stream.writeVarInt<std::int64_t>(value.boss_id);
    stream.write<std::uint8_t>(value.event_type);
    if (((value.event_type) == (BossEventUpdateType::PlayerAdded)) || ((value.event_type) == (BossEventUpdateType::PlayerRemoved)) || ((value.event_type) == (BossEventUpdateType::Query))) {
        stream.writeVarInt<std::int64_t>(value.player_id);
    }
    if (((value.event_type) == (BossEventUpdateType::Add)) || ((value.event_type) == (BossEventUpdateType::UpdateName))) {
        stream.write(value.name);
        stream.write(value.filtered_name);
    }
    if (((value.event_type) == (BossEventUpdateType::Add)) || ((value.event_type) == (BossEventUpdateType::UpdatePercent))) {
        stream.write<float>(value.health_percent);
    }
    if (((value.event_type) == (BossEventUpdateType::Add)) || ((value.event_type) == (BossEventUpdateType::UpdateProperties))) {
        stream.write<std::uint8_t>(value.darken_screen);
        stream.write<std::uint8_t>(value.create_world_fog);
    }
    if (((value.event_type) == (BossEventUpdateType::Add)) || ((value.event_type) == (BossEventUpdateType::UpdateProperties)) || ((value.event_type) == (BossEventUpdateType::UpdateStyle))) {
        stream.write<std::uint8_t>(value.color);
        stream.write<std::uint8_t>(value.overlay);
    }
}

auto Serializer<v776::BossEventPacket>::deserialize(BinaryReader &stream) -> std::expected<v776::BossEventPacket, std::error_code>
{
    v776::BossEventPacket out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.boss_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.event_type = static_cast<BossEventUpdateType>(*v);
    }
    if (((out.event_type) == (BossEventUpdateType::PlayerAdded)) || ((out.event_type) == (BossEventUpdateType::PlayerRemoved)) || ((out.event_type) == (BossEventUpdateType::Query))) {
        {
            auto v = stream.readVarInt<std::int64_t>();
            if (!v) return std::unexpected(v.error());
            out.player_id = static_cast<ActorUniqueID>(*v);
        }
    }
    if (((out.event_type) == (BossEventUpdateType::Add)) || ((out.event_type) == (BossEventUpdateType::UpdateName))) {
        {
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.name = *v;
        }
        {
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.filtered_name = *v;
        }
    }
    if (((out.event_type) == (BossEventUpdateType::Add)) || ((out.event_type) == (BossEventUpdateType::UpdatePercent))) {
        {
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            out.health_percent = static_cast<float>(*v);
        }
    }
    if (((out.event_type) == (BossEventUpdateType::Add)) || ((out.event_type) == (BossEventUpdateType::UpdateProperties))) {
        {
            auto v = stream.read<std::uint8_t>();
            if (!v) return std::unexpected(v.error());
            out.darken_screen = static_cast<std::uint8_t>(*v);
        }
        {
            auto v = stream.read<std::uint8_t>();
            if (!v) return std::unexpected(v.error());
            out.create_world_fog = static_cast<std::uint8_t>(*v);
        }
    }
    if (((out.event_type) == (BossEventUpdateType::Add)) || ((out.event_type) == (BossEventUpdateType::UpdateProperties)) || ((out.event_type) == (BossEventUpdateType::UpdateStyle))) {
        {
            auto v = stream.read<std::uint8_t>();
            if (!v) return std::unexpected(v.error());
            out.color = static_cast<BossBarColor>(*v);
        }
        {
            auto v = stream.read<std::uint8_t>();
            if (!v) return std::unexpected(v.error());
            out.overlay = static_cast<BossBarOverlay>(*v);
        }
    }
    return out;
}

void Serializer<v1001::BossEventPacket>::serialize(BinaryWriter &stream, const v1001::BossEventPacket &value)
{
    stream.writeVarInt<std::int64_t>(value.boss_id);
    stream.writeVarInt<std::int64_t>(value.player_id);
    stream.write<std::uint8_t>(value.event_type);
    stream.write(value.name);
    stream.write(value.filtered_name);
    stream.write<float>(value.health_percent);
    stream.write<std::uint8_t>(value.color);
    stream.write<std::uint8_t>(value.overlay);
}

auto Serializer<v1001::BossEventPacket>::deserialize(BinaryReader &stream) -> std::expected<v1001::BossEventPacket, std::error_code>
{
    v1001::BossEventPacket out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.boss_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.player_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.event_type = static_cast<BossEventUpdateType>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.filtered_name = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.health_percent = static_cast<float>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.color = static_cast<BossBarColor>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.overlay = static_cast<BossBarOverlay>(*v);
    }
    return out;
}

void Serializer<v2193::BossEventPacket>::serialize(BinaryWriter &stream, const v2193::BossEventPacket &value)
{
    stream.writeVarInt<std::int64_t>(value.boss_id);
    stream.write<std::uint8_t>(value.event_type);
    stream.write(value.name);
    stream.write(value.filtered_name);
    stream.write<float>(value.health_percent);
    stream.write<std::uint8_t>(value.color);
    stream.write<std::uint8_t>(value.overlay);
}

auto Serializer<v2193::BossEventPacket>::deserialize(BinaryReader &stream) -> std::expected<v2193::BossEventPacket, std::error_code>
{
    v2193::BossEventPacket out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.boss_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.event_type = static_cast<BossEventUpdateType>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.filtered_name = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.health_percent = static_cast<float>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.color = static_cast<BossBarColor>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.overlay = static_cast<BossBarOverlay>(*v);
    }
    return out;
}

}  // namespace bedrock::protocol
