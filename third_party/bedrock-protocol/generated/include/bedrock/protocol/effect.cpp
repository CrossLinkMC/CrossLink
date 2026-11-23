#include <bedrock/protocol/effect.h>

namespace bedrock::protocol {


void Serializer<base::MobEffectPacket>::serialize(BinaryWriter &stream, const base::MobEffectPacket &value)
{
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    stream.write<std::uint8_t>(value.event_id);
    stream.writeVarInt<std::int32_t>(value.effect_id);
    stream.writeVarInt<std::int32_t>(value.effect_amplifier);
    stream.write<bool>(value.show_particles);
    stream.writeVarInt<std::int32_t>(value.effect_duration_ticks);
    stream.write<std::uint64_t>(value.tick);
}

auto Serializer<base::MobEffectPacket>::deserialize(BinaryReader &stream) -> std::expected<base::MobEffectPacket, std::error_code>
{
    base::MobEffectPacket out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.event_id = static_cast<base::MobEffectPacket::Event>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.effect_id = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.effect_amplifier = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.show_particles = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.effect_duration_ticks = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.tick = static_cast<PlayerInputTick>(*v);
    }
    return out;
}

void Serializer<v748::MobEffectPacket>::serialize(BinaryWriter &stream, const v748::MobEffectPacket &value)
{
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    stream.write<std::uint8_t>(value.event_id);
    stream.writeVarInt<std::int32_t>(value.effect_id);
    stream.writeVarInt<std::int32_t>(value.effect_amplifier);
    stream.write<bool>(value.show_particles);
    stream.writeVarInt<std::int32_t>(value.effect_duration_ticks);
    stream.writeVarInt<std::uint64_t>(value.tick);
}

auto Serializer<v748::MobEffectPacket>::deserialize(BinaryReader &stream) -> std::expected<v748::MobEffectPacket, std::error_code>
{
    v748::MobEffectPacket out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.event_id = static_cast<v748::MobEffectPacket::Event>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.effect_id = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.effect_amplifier = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.show_particles = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.effect_duration_ticks = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.tick = static_cast<PlayerInputTick>(*v);
    }
    return out;
}

void Serializer<v898::MobEffectPacket>::serialize(BinaryWriter &stream, const v898::MobEffectPacket &value)
{
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    stream.write<std::uint8_t>(value.event_id);
    stream.writeVarInt<std::int32_t>(value.effect_id);
    stream.writeVarInt<std::int32_t>(value.effect_amplifier);
    stream.write<bool>(value.show_particles);
    stream.writeVarInt<std::int32_t>(value.effect_duration_ticks);
    stream.writeVarInt<std::uint64_t>(value.tick);
    stream.write<bool>(value.ambient);
}

auto Serializer<v898::MobEffectPacket>::deserialize(BinaryReader &stream) -> std::expected<v898::MobEffectPacket, std::error_code>
{
    v898::MobEffectPacket out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.event_id = static_cast<v898::MobEffectPacket::Event>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.effect_id = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.effect_amplifier = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.show_particles = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.effect_duration_ticks = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.tick = static_cast<PlayerInputTick>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.ambient = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v748::MovementEffectPacket>::serialize(BinaryWriter &stream, const v748::MovementEffectPacket &value)
{
    stream.writeVarInt<std::uint64_t>(value.target_runtime_id);
    stream.writeVarInt<std::int32_t>(value.effect_id);
    stream.writeVarInt<std::int32_t>(value.effect_duration);
    stream.writeVarInt<std::uint64_t>(value.tick);
}

auto Serializer<v748::MovementEffectPacket>::deserialize(BinaryReader &stream) -> std::expected<v748::MovementEffectPacket, std::error_code>
{
    v748::MovementEffectPacket out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.target_runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.effect_id = static_cast<base::MovementEffectType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.effect_duration = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.tick = static_cast<PlayerInputTick>(*v);
    }
    return out;
}

void Serializer<v776::MovementEffectPacket>::serialize(BinaryWriter &stream, const v776::MovementEffectPacket &value)
{
    stream.writeVarInt<std::uint64_t>(value.target_runtime_id);
    stream.writeVarInt<std::int32_t>(value.effect_id);
    stream.writeVarInt<std::int32_t>(value.effect_duration);
    stream.writeVarInt<std::uint64_t>(value.tick);
}

auto Serializer<v776::MovementEffectPacket>::deserialize(BinaryReader &stream) -> std::expected<v776::MovementEffectPacket, std::error_code>
{
    v776::MovementEffectPacket out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.target_runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.effect_id = static_cast<v776::MovementEffectType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.effect_duration = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.tick = static_cast<PlayerInputTick>(*v);
    }
    return out;
}

void Serializer<v1001::MovementEffectPacket>::serialize(BinaryWriter &stream, const v1001::MovementEffectPacket &value)
{
    stream.writeVarInt<std::uint64_t>(value.target_runtime_id);
    stream.writeVarInt<std::int32_t>(value.effect_id);
    stream.writeVarInt<std::int32_t>(value.effect_duration);
    stream.writeVarInt<std::uint64_t>(value.tick);
}

auto Serializer<v1001::MovementEffectPacket>::deserialize(BinaryReader &stream) -> std::expected<v1001::MovementEffectPacket, std::error_code>
{
    v1001::MovementEffectPacket out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.target_runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.effect_id = static_cast<v1001::MovementEffectType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.effect_duration = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.tick = static_cast<PlayerInputTick>(*v);
    }
    return out;
}

}  // namespace bedrock::protocol
