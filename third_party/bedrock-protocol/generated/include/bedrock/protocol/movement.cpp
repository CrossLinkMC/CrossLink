#include <bedrock/protocol/movement.h>

#include <bedrock/protocol/detail/bitset.hpp>

namespace bedrock::protocol {


void Serializer<v2168::MovePlayerTeleportData>::serialize(BinaryWriter &stream, const v2168::MovePlayerTeleportData &value)
{
    stream.write<std::int32_t>(value.cause);
    stream.write<std::int32_t>(value.source_entity_type);
}

auto Serializer<v2168::MovePlayerTeleportData>::deserialize(BinaryReader &stream) -> std::expected<v2168::MovePlayerTeleportData, std::error_code>
{
    v2168::MovePlayerTeleportData out;
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.cause = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.source_entity_type = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<base::MoveActorDeltaData>::serialize(BinaryWriter &stream, const base::MoveActorDeltaData &value)
{
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    stream.write<std::uint16_t>(value.header);
    if (((value.header) & (1)) != (0)) {
        stream.write<float>(value.new_position_x);
    }
    if (((value.header) & (2)) != (0)) {
        stream.write<float>(value.new_position_y);
    }
    if (((value.header) & (4)) != (0)) {
        stream.write<float>(value.new_position_z);
    }
    if (((value.header) & (8)) != (0)) {
        stream.write<std::int8_t>(value.rot_x);
    }
    if (((value.header) & (16)) != (0)) {
        stream.write<std::int8_t>(value.rot_y);
    }
    if (((value.header) & (32)) != (0)) {
        stream.write<std::int8_t>(value.rot_y_head);
    }
}

auto Serializer<base::MoveActorDeltaData>::deserialize(BinaryReader &stream) -> std::expected<base::MoveActorDeltaData, std::error_code>
{
    base::MoveActorDeltaData out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.header = static_cast<std::uint16_t>(*v);
    }
    if (((out.header) & (1)) != (0)) {
        {
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            out.new_position_x = static_cast<float>(*v);
        }
    }
    if (((out.header) & (2)) != (0)) {
        {
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            out.new_position_y = static_cast<float>(*v);
        }
    }
    if (((out.header) & (4)) != (0)) {
        {
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            out.new_position_z = static_cast<float>(*v);
        }
    }
    if (((out.header) & (8)) != (0)) {
        {
            auto v = stream.read<std::int8_t>();
            if (!v) return std::unexpected(v.error());
            out.rot_x = static_cast<std::int8_t>(*v);
        }
    }
    if (((out.header) & (16)) != (0)) {
        {
            auto v = stream.read<std::int8_t>();
            if (!v) return std::unexpected(v.error());
            out.rot_y = static_cast<std::int8_t>(*v);
        }
    }
    if (((out.header) & (32)) != (0)) {
        {
            auto v = stream.read<std::int8_t>();
            if (!v) return std::unexpected(v.error());
            out.rot_y_head = static_cast<std::int8_t>(*v);
        }
    }
    return out;
}

void Serializer<v2168::MoveActorDeltaData>::serialize(BinaryWriter &stream, const v2168::MoveActorDeltaData &value)
{
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    stream.write<bool>(value.new_position_x.has_value());
    if (value.new_position_x.has_value()) {
        stream.write<float>((*value.new_position_x));
    }
    stream.write<bool>(value.new_position_y.has_value());
    if (value.new_position_y.has_value()) {
        stream.write<float>((*value.new_position_y));
    }
    stream.write<bool>(value.new_position_z.has_value());
    if (value.new_position_z.has_value()) {
        stream.write<float>((*value.new_position_z));
    }
    stream.write<bool>(value.rot_x.has_value());
    if (value.rot_x.has_value()) {
        stream.write<std::int8_t>((*value.rot_x));
    }
    stream.write<bool>(value.rot_y.has_value());
    if (value.rot_y.has_value()) {
        stream.write<std::int8_t>((*value.rot_y));
    }
    stream.write<bool>(value.rot_y_head.has_value());
    if (value.rot_y_head.has_value()) {
        stream.write<std::int8_t>((*value.rot_y_head));
    }
    stream.write<bool>(value.is_on_ground);
    stream.write<bool>(value.force_move);
    stream.write<bool>(value.force_move_local_entity);
    stream.write<bool>(value.force_completion);
}

auto Serializer<v2168::MoveActorDeltaData>::deserialize(BinaryReader &stream) -> std::expected<v2168::MoveActorDeltaData, std::error_code>
{
    v2168::MoveActorDeltaData out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.new_position_x = std::move(staged);
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
            out.new_position_y = std::move(staged);
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
            out.new_position_z = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::int8_t staged{};
            auto v = stream.read<std::int8_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<std::int8_t>(*v);
            out.rot_x = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::int8_t staged{};
            auto v = stream.read<std::int8_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<std::int8_t>(*v);
            out.rot_y = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::int8_t staged{};
            auto v = stream.read<std::int8_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<std::int8_t>(*v);
            out.rot_y_head = std::move(staged);
        }
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_on_ground = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.force_move = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.force_move_local_entity = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.force_completion = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v2193::MoveActorDeltaData>::serialize(BinaryWriter &stream, const v2193::MoveActorDeltaData &value)
{
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    stream.write<bool>(value.new_position_x.has_value());
    if (value.new_position_x.has_value()) {
        stream.write<float>((*value.new_position_x));
    }
    stream.write<bool>(value.new_position_y.has_value());
    if (value.new_position_y.has_value()) {
        stream.write<float>((*value.new_position_y));
    }
    stream.write<bool>(value.new_position_z.has_value());
    if (value.new_position_z.has_value()) {
        stream.write<float>((*value.new_position_z));
    }
    stream.write<bool>(value.rot_x.has_value());
    if (value.rot_x.has_value()) {
        stream.write<std::int8_t>((*value.rot_x));
    }
    stream.write<bool>(value.rot_y.has_value());
    if (value.rot_y.has_value()) {
        stream.write<std::int8_t>((*value.rot_y));
    }
    stream.write<bool>(value.rot_y_head.has_value());
    if (value.rot_y_head.has_value()) {
        stream.write<std::int8_t>((*value.rot_y_head));
    }
    stream.write<bool>(value.is_on_ground);
    stream.write<bool>(value.force_move);
    stream.write<bool>(value.force_move_local_entity);
    stream.write<bool>(value.force_completion);
    stream.writeVarInt<std::uint64_t>(value.ticks);
}

auto Serializer<v2193::MoveActorDeltaData>::deserialize(BinaryReader &stream) -> std::expected<v2193::MoveActorDeltaData, std::error_code>
{
    v2193::MoveActorDeltaData out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.new_position_x = std::move(staged);
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
            out.new_position_y = std::move(staged);
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
            out.new_position_z = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::int8_t staged{};
            auto v = stream.read<std::int8_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<std::int8_t>(*v);
            out.rot_x = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::int8_t staged{};
            auto v = stream.read<std::int8_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<std::int8_t>(*v);
            out.rot_y = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::int8_t staged{};
            auto v = stream.read<std::int8_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<std::int8_t>(*v);
            out.rot_y_head = std::move(staged);
        }
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_on_ground = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.force_move = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.force_move_local_entity = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.force_completion = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.ticks = static_cast<std::uint64_t>(*v);
    }
    return out;
}

void Serializer<base::MovePlayerPacket>::serialize(BinaryWriter &stream, const base::MovePlayerPacket &value)
{
    stream.writeVarInt<std::uint64_t>(value.player_id);
    Serializer<Vec3>::serialize(stream, value.pos);
    Serializer<Vec2>::serialize(stream, value.rot);
    stream.write<float>(value.y_head_rot);
    stream.write<std::uint8_t>(value.reset_position);
    stream.write<bool>(value.on_ground);
    stream.writeVarInt<std::uint64_t>(value.riding_id);
    if ((value.reset_position) == (PlayerPositionModeComponent::PositionMode::Teleport)) {
        stream.write<std::int32_t>(value.cause);
        stream.write<std::int32_t>(value.source_entity_type);
    }
    stream.writeVarInt<std::uint64_t>(value.tick);
}

auto Serializer<base::MovePlayerPacket>::deserialize(BinaryReader &stream) -> std::expected<base::MovePlayerPacket, std::error_code>
{
    base::MovePlayerPacket out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.player_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.rot = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.y_head_rot = static_cast<float>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.reset_position = static_cast<PlayerPositionModeComponent::PositionMode>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.on_ground = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.riding_id = static_cast<ActorRuntimeID>(*v);
    }
    if ((out.reset_position) == (PlayerPositionModeComponent::PositionMode::Teleport)) {
        {
            auto v = stream.read<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            out.cause = static_cast<std::int32_t>(*v);
        }
        {
            auto v = stream.read<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            out.source_entity_type = static_cast<std::int32_t>(*v);
        }
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.tick = static_cast<PlayerInputTick>(*v);
    }
    return out;
}

void Serializer<v2168::MovePlayerPacket>::serialize(BinaryWriter &stream, const v2168::MovePlayerPacket &value)
{
    stream.writeVarInt<std::uint64_t>(value.player_id);
    Serializer<Vec3>::serialize(stream, value.pos);
    Serializer<Vec2>::serialize(stream, value.rot);
    stream.write<float>(value.y_head_rot);
    stream.write<std::uint8_t>(value.reset_position);
    stream.write<bool>(value.on_ground);
    stream.writeVarInt<std::uint64_t>(value.riding_id);
    stream.write<bool>(value.teleport_data.has_value());
    if (value.teleport_data.has_value()) {
        Serializer<v2168::MovePlayerTeleportData>::serialize(stream, (*value.teleport_data));
    }
    stream.writeVarInt<std::uint64_t>(value.tick);
}

auto Serializer<v2168::MovePlayerPacket>::deserialize(BinaryReader &stream) -> std::expected<v2168::MovePlayerPacket, std::error_code>
{
    v2168::MovePlayerPacket out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.player_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.rot = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.y_head_rot = static_cast<float>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.reset_position = static_cast<PlayerPositionModeComponent::PositionMode>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.on_ground = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.riding_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v2168::MovePlayerTeleportData staged{};
            auto v = Serializer<v2168::MovePlayerTeleportData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.teleport_data = std::move(staged);
        }
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.tick = static_cast<PlayerInputTick>(*v);
    }
    return out;
}

void Serializer<base::MoveActorDeltaPacket>::serialize(BinaryWriter &stream, const base::MoveActorDeltaPacket &value)
{
    Serializer<base::MoveActorDeltaData>::serialize(stream, value.move_data);
}

auto Serializer<base::MoveActorDeltaPacket>::deserialize(BinaryReader &stream) -> std::expected<base::MoveActorDeltaPacket, std::error_code>
{
    base::MoveActorDeltaPacket out;
    {
        auto v = Serializer<base::MoveActorDeltaData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.move_data = *v;
    }
    return out;
}

void Serializer<v2168::MoveActorDeltaPacket>::serialize(BinaryWriter &stream, const v2168::MoveActorDeltaPacket &value)
{
    Serializer<v2168::MoveActorDeltaData>::serialize(stream, value.move_data);
}

auto Serializer<v2168::MoveActorDeltaPacket>::deserialize(BinaryReader &stream) -> std::expected<v2168::MoveActorDeltaPacket, std::error_code>
{
    v2168::MoveActorDeltaPacket out;
    {
        auto v = Serializer<v2168::MoveActorDeltaData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.move_data = *v;
    }
    return out;
}

void Serializer<v2193::MoveActorDeltaPacket>::serialize(BinaryWriter &stream, const v2193::MoveActorDeltaPacket &value)
{
    Serializer<v2193::MoveActorDeltaData>::serialize(stream, value.move_data);
}

auto Serializer<v2193::MoveActorDeltaPacket>::deserialize(BinaryReader &stream) -> std::expected<v2193::MoveActorDeltaPacket, std::error_code>
{
    v2193::MoveActorDeltaPacket out;
    {
        auto v = Serializer<v2193::MoveActorDeltaData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.move_data = *v;
    }
    return out;
}

void Serializer<ServerPlayerPostMovePositionPacket>::serialize(BinaryWriter &stream, const ServerPlayerPostMovePositionPacket &value)
{
    Serializer<Vec3>::serialize(stream, value.pos);
}

auto Serializer<ServerPlayerPostMovePositionPacket>::deserialize(BinaryReader &stream) -> std::expected<ServerPlayerPostMovePositionPacket, std::error_code>
{
    ServerPlayerPostMovePositionPacket out;
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    return out;
}

void Serializer<v776::ActorDataFlagComponent>::serialize(BinaryWriter &stream, const v776::ActorDataFlagComponent &value)
{
    Serializer<std::bitset<120>>::serialize(stream, value.value);
}

auto Serializer<v776::ActorDataFlagComponent>::deserialize(BinaryReader &stream) -> std::expected<v776::ActorDataFlagComponent, std::error_code>
{
    v776::ActorDataFlagComponent out;
    {
        auto v = Serializer<std::bitset<120>>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.value = *v;
    }
    return out;
}

void Serializer<v786::ActorDataFlagComponent>::serialize(BinaryWriter &stream, const v786::ActorDataFlagComponent &value)
{
    Serializer<std::bitset<123>>::serialize(stream, value.value);
}

auto Serializer<v786::ActorDataFlagComponent>::deserialize(BinaryReader &stream) -> std::expected<v786::ActorDataFlagComponent, std::error_code>
{
    v786::ActorDataFlagComponent out;
    {
        auto v = Serializer<std::bitset<123>>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.value = *v;
    }
    return out;
}

void Serializer<v800::ActorDataFlagComponent>::serialize(BinaryWriter &stream, const v800::ActorDataFlagComponent &value)
{
    Serializer<std::bitset<124>>::serialize(stream, value.value);
}

auto Serializer<v800::ActorDataFlagComponent>::deserialize(BinaryReader &stream) -> std::expected<v800::ActorDataFlagComponent, std::error_code>
{
    v800::ActorDataFlagComponent out;
    {
        auto v = Serializer<std::bitset<124>>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.value = *v;
    }
    return out;
}

void Serializer<v818::ActorDataFlagComponent>::serialize(BinaryWriter &stream, const v818::ActorDataFlagComponent &value)
{
    Serializer<std::bitset<125>>::serialize(stream, value.value);
}

auto Serializer<v818::ActorDataFlagComponent>::deserialize(BinaryReader &stream) -> std::expected<v818::ActorDataFlagComponent, std::error_code>
{
    v818::ActorDataFlagComponent out;
    {
        auto v = Serializer<std::bitset<125>>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.value = *v;
    }
    return out;
}

void Serializer<v844::ActorDataFlagComponent>::serialize(BinaryWriter &stream, const v844::ActorDataFlagComponent &value)
{
    Serializer<std::bitset<126>>::serialize(stream, value.value);
}

auto Serializer<v844::ActorDataFlagComponent>::deserialize(BinaryReader &stream) -> std::expected<v844::ActorDataFlagComponent, std::error_code>
{
    v844::ActorDataFlagComponent out;
    {
        auto v = Serializer<std::bitset<126>>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.value = *v;
    }
    return out;
}

void Serializer<v898::ActorDataFlagComponent>::serialize(BinaryWriter &stream, const v898::ActorDataFlagComponent &value)
{
    Serializer<std::bitset<127>>::serialize(stream, value.value);
}

auto Serializer<v898::ActorDataFlagComponent>::deserialize(BinaryReader &stream) -> std::expected<v898::ActorDataFlagComponent, std::error_code>
{
    v898::ActorDataFlagComponent out;
    {
        auto v = Serializer<std::bitset<127>>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.value = *v;
    }
    return out;
}

void Serializer<v975::ActorDataFlagComponent>::serialize(BinaryWriter &stream, const v975::ActorDataFlagComponent &value)
{
    Serializer<std::bitset<130>>::serialize(stream, value.value);
}

auto Serializer<v975::ActorDataFlagComponent>::deserialize(BinaryReader &stream) -> std::expected<v975::ActorDataFlagComponent, std::error_code>
{
    v975::ActorDataFlagComponent out;
    {
        auto v = Serializer<std::bitset<130>>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.value = *v;
    }
    return out;
}

void Serializer<v2168::ActorDataFlagComponent>::serialize(BinaryWriter &stream, const v2168::ActorDataFlagComponent &value)
{
    Serializer<std::bitset<131>>::serialize(stream, value.value);
}

auto Serializer<v2168::ActorDataFlagComponent>::deserialize(BinaryReader &stream) -> std::expected<v2168::ActorDataFlagComponent, std::error_code>
{
    v2168::ActorDataFlagComponent out;
    {
        auto v = Serializer<std::bitset<131>>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.value = *v;
    }
    return out;
}

void Serializer<v776::ActorDataBoundingBoxComponent>::serialize(BinaryWriter &stream, const v776::ActorDataBoundingBoxComponent &value)
{
    for (const auto &e0 : value.value) {
        stream.write<float>(e0);
    }
}

auto Serializer<v776::ActorDataBoundingBoxComponent>::deserialize(BinaryReader &stream) -> std::expected<v776::ActorDataBoundingBoxComponent, std::error_code>
{
    v776::ActorDataBoundingBoxComponent out;
    {
        for (std::size_t i0 = 0; i0 < 3; ++i0) {
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            out.value[i0] = static_cast<float>(*v);
        }
    }
    return out;
}

void Serializer<v776::ClientMovementPredictionSyncPacket>::serialize(BinaryWriter &stream, const v776::ClientMovementPredictionSyncPacket &value)
{
    Serializer<v776::ActorDataFlagComponent>::serialize(stream, value.actor_data_flag);
    Serializer<v776::ActorDataBoundingBoxComponent>::serialize(stream, value.actor_bounding_box);
    for (const auto &e0 : value.movement_attributes) {
        stream.write<float>(e0);
    }
    stream.writeVarInt<std::int64_t>(value.actor_id);
}

auto Serializer<v776::ClientMovementPredictionSyncPacket>::deserialize(BinaryReader &stream) -> std::expected<v776::ClientMovementPredictionSyncPacket, std::error_code>
{
    v776::ClientMovementPredictionSyncPacket out;
    {
        auto v = Serializer<v776::ActorDataFlagComponent>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.actor_data_flag = *v;
    }
    {
        auto v = Serializer<v776::ActorDataBoundingBoxComponent>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.actor_bounding_box = *v;
    }
    {
        for (std::size_t i0 = 0; i0 < 6; ++i0) {
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            out.movement_attributes[i0] = static_cast<float>(*v);
        }
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.actor_id = static_cast<ActorUniqueID>(*v);
    }
    return out;
}

void Serializer<v786::ClientMovementPredictionSyncPacket>::serialize(BinaryWriter &stream, const v786::ClientMovementPredictionSyncPacket &value)
{
    Serializer<v786::ActorDataFlagComponent>::serialize(stream, value.actor_data_flag);
    Serializer<v776::ActorDataBoundingBoxComponent>::serialize(stream, value.actor_bounding_box);
    for (const auto &e0 : value.movement_attributes) {
        stream.write<float>(e0);
    }
    stream.writeVarInt<std::int64_t>(value.actor_id);
    stream.write<bool>(value.is_flying);
}

auto Serializer<v786::ClientMovementPredictionSyncPacket>::deserialize(BinaryReader &stream) -> std::expected<v786::ClientMovementPredictionSyncPacket, std::error_code>
{
    v786::ClientMovementPredictionSyncPacket out;
    {
        auto v = Serializer<v786::ActorDataFlagComponent>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.actor_data_flag = *v;
    }
    {
        auto v = Serializer<v776::ActorDataBoundingBoxComponent>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.actor_bounding_box = *v;
    }
    {
        for (std::size_t i0 = 0; i0 < 6; ++i0) {
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            out.movement_attributes[i0] = static_cast<float>(*v);
        }
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.actor_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_flying = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v800::ClientMovementPredictionSyncPacket>::serialize(BinaryWriter &stream, const v800::ClientMovementPredictionSyncPacket &value)
{
    Serializer<v800::ActorDataFlagComponent>::serialize(stream, value.actor_data_flag);
    Serializer<v776::ActorDataBoundingBoxComponent>::serialize(stream, value.actor_bounding_box);
    for (const auto &e0 : value.movement_attributes) {
        stream.write<float>(e0);
    }
    stream.writeVarInt<std::int64_t>(value.actor_id);
    stream.write<bool>(value.is_flying);
}

auto Serializer<v800::ClientMovementPredictionSyncPacket>::deserialize(BinaryReader &stream) -> std::expected<v800::ClientMovementPredictionSyncPacket, std::error_code>
{
    v800::ClientMovementPredictionSyncPacket out;
    {
        auto v = Serializer<v800::ActorDataFlagComponent>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.actor_data_flag = *v;
    }
    {
        auto v = Serializer<v776::ActorDataBoundingBoxComponent>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.actor_bounding_box = *v;
    }
    {
        for (std::size_t i0 = 0; i0 < 6; ++i0) {
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            out.movement_attributes[i0] = static_cast<float>(*v);
        }
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.actor_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_flying = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v818::ClientMovementPredictionSyncPacket>::serialize(BinaryWriter &stream, const v818::ClientMovementPredictionSyncPacket &value)
{
    Serializer<v818::ActorDataFlagComponent>::serialize(stream, value.actor_data_flag);
    Serializer<v776::ActorDataBoundingBoxComponent>::serialize(stream, value.actor_bounding_box);
    for (const auto &e0 : value.movement_attributes) {
        stream.write<float>(e0);
    }
    stream.writeVarInt<std::int64_t>(value.actor_id);
    stream.write<bool>(value.is_flying);
}

auto Serializer<v818::ClientMovementPredictionSyncPacket>::deserialize(BinaryReader &stream) -> std::expected<v818::ClientMovementPredictionSyncPacket, std::error_code>
{
    v818::ClientMovementPredictionSyncPacket out;
    {
        auto v = Serializer<v818::ActorDataFlagComponent>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.actor_data_flag = *v;
    }
    {
        auto v = Serializer<v776::ActorDataBoundingBoxComponent>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.actor_bounding_box = *v;
    }
    {
        for (std::size_t i0 = 0; i0 < 6; ++i0) {
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            out.movement_attributes[i0] = static_cast<float>(*v);
        }
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.actor_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_flying = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v844::ClientMovementPredictionSyncPacket>::serialize(BinaryWriter &stream, const v844::ClientMovementPredictionSyncPacket &value)
{
    Serializer<v844::ActorDataFlagComponent>::serialize(stream, value.actor_data_flag);
    Serializer<v776::ActorDataBoundingBoxComponent>::serialize(stream, value.actor_bounding_box);
    for (const auto &e0 : value.movement_attributes) {
        stream.write<float>(e0);
    }
    stream.writeVarInt<std::int64_t>(value.actor_id);
    stream.write<bool>(value.is_flying);
}

auto Serializer<v844::ClientMovementPredictionSyncPacket>::deserialize(BinaryReader &stream) -> std::expected<v844::ClientMovementPredictionSyncPacket, std::error_code>
{
    v844::ClientMovementPredictionSyncPacket out;
    {
        auto v = Serializer<v844::ActorDataFlagComponent>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.actor_data_flag = *v;
    }
    {
        auto v = Serializer<v776::ActorDataBoundingBoxComponent>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.actor_bounding_box = *v;
    }
    {
        for (std::size_t i0 = 0; i0 < 6; ++i0) {
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            out.movement_attributes[i0] = static_cast<float>(*v);
        }
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.actor_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_flying = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v898::ClientMovementPredictionSyncPacket>::serialize(BinaryWriter &stream, const v898::ClientMovementPredictionSyncPacket &value)
{
    Serializer<v898::ActorDataFlagComponent>::serialize(stream, value.actor_data_flag);
    Serializer<v776::ActorDataBoundingBoxComponent>::serialize(stream, value.actor_bounding_box);
    for (const auto &e0 : value.movement_attributes) {
        stream.write<float>(e0);
    }
    stream.writeVarInt<std::int64_t>(value.actor_id);
    stream.write<bool>(value.is_flying);
}

auto Serializer<v898::ClientMovementPredictionSyncPacket>::deserialize(BinaryReader &stream) -> std::expected<v898::ClientMovementPredictionSyncPacket, std::error_code>
{
    v898::ClientMovementPredictionSyncPacket out;
    {
        auto v = Serializer<v898::ActorDataFlagComponent>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.actor_data_flag = *v;
    }
    {
        auto v = Serializer<v776::ActorDataBoundingBoxComponent>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.actor_bounding_box = *v;
    }
    {
        for (std::size_t i0 = 0; i0 < 6; ++i0) {
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            out.movement_attributes[i0] = static_cast<float>(*v);
        }
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.actor_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_flying = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v975::ClientMovementPredictionSyncPacket>::serialize(BinaryWriter &stream, const v975::ClientMovementPredictionSyncPacket &value)
{
    Serializer<v975::ActorDataFlagComponent>::serialize(stream, value.actor_data_flag);
    Serializer<v776::ActorDataBoundingBoxComponent>::serialize(stream, value.actor_bounding_box);
    for (const auto &e0 : value.movement_attributes) {
        stream.write<float>(e0);
    }
    stream.writeVarInt<std::int64_t>(value.actor_id);
    stream.write<bool>(value.is_flying);
}

auto Serializer<v975::ClientMovementPredictionSyncPacket>::deserialize(BinaryReader &stream) -> std::expected<v975::ClientMovementPredictionSyncPacket, std::error_code>
{
    v975::ClientMovementPredictionSyncPacket out;
    {
        auto v = Serializer<v975::ActorDataFlagComponent>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.actor_data_flag = *v;
    }
    {
        auto v = Serializer<v776::ActorDataBoundingBoxComponent>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.actor_bounding_box = *v;
    }
    {
        for (std::size_t i0 = 0; i0 < 9; ++i0) {
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            out.movement_attributes[i0] = static_cast<float>(*v);
        }
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.actor_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_flying = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v2168::ClientMovementPredictionSyncPacket>::serialize(BinaryWriter &stream, const v2168::ClientMovementPredictionSyncPacket &value)
{
    Serializer<v2168::ActorDataFlagComponent>::serialize(stream, value.actor_data_flag);
    Serializer<v776::ActorDataBoundingBoxComponent>::serialize(stream, value.actor_bounding_box);
    for (const auto &e0 : value.movement_attributes) {
        stream.write<float>(e0);
    }
    stream.writeVarInt<std::int64_t>(value.actor_id);
    stream.write<bool>(value.is_flying);
}

auto Serializer<v2168::ClientMovementPredictionSyncPacket>::deserialize(BinaryReader &stream) -> std::expected<v2168::ClientMovementPredictionSyncPacket, std::error_code>
{
    v2168::ClientMovementPredictionSyncPacket out;
    {
        auto v = Serializer<v2168::ActorDataFlagComponent>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.actor_data_flag = *v;
    }
    {
        auto v = Serializer<v776::ActorDataBoundingBoxComponent>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.actor_bounding_box = *v;
    }
    {
        for (std::size_t i0 = 0; i0 < 9; ++i0) {
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            out.movement_attributes[i0] = static_cast<float>(*v);
        }
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.actor_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_flying = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<base::CorrectPlayerMovePredictionPacket>::serialize(BinaryWriter &stream, const base::CorrectPlayerMovePredictionPacket &value)
{
    stream.write<std::uint8_t>(value.prediction_type);
    Serializer<Vec3>::serialize(stream, value.pos);
    Serializer<Vec3>::serialize(stream, value.pos_delta);
    if ((value.prediction_type) == (RewindType::Vehicle)) {
        Serializer<Vec2>::serialize(stream, value.vehicle_rotation);
        stream.write<bool>(value.vehicle_angular_velocity.has_value());
        if (value.vehicle_angular_velocity.has_value()) {
            stream.write<float>((*value.vehicle_angular_velocity));
        }
    }
    stream.write<bool>(value.on_ground);
    stream.writeVarInt<std::uint64_t>(value.tick);
}

auto Serializer<base::CorrectPlayerMovePredictionPacket>::deserialize(BinaryReader &stream) -> std::expected<base::CorrectPlayerMovePredictionPacket, std::error_code>
{
    base::CorrectPlayerMovePredictionPacket out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.prediction_type = static_cast<RewindType>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos_delta = *v;
    }
    if ((out.prediction_type) == (RewindType::Vehicle)) {
        {
            auto v = Serializer<Vec2>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.vehicle_rotation = *v;
        }
        {
            auto present = stream.read<bool>();
            if (!present) return std::unexpected(present.error());
            if (*present) {
                float staged{};
                auto v = stream.read<float>();
                if (!v) return std::unexpected(v.error());
                staged = static_cast<float>(*v);
                out.vehicle_angular_velocity = std::move(staged);
            }
        }
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.on_ground = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.tick = static_cast<PlayerInputTick>(*v);
    }
    return out;
}

void Serializer<v827::CorrectPlayerMovePredictionPacket>::serialize(BinaryWriter &stream, const v827::CorrectPlayerMovePredictionPacket &value)
{
    stream.write<std::uint8_t>(value.prediction_type);
    Serializer<Vec3>::serialize(stream, value.pos);
    Serializer<Vec3>::serialize(stream, value.pos_delta);
    Serializer<Vec2>::serialize(stream, value.vehicle_rotation);
    stream.write<bool>(value.vehicle_angular_velocity.has_value());
    if (value.vehicle_angular_velocity.has_value()) {
        stream.write<float>((*value.vehicle_angular_velocity));
    }
    stream.write<bool>(value.on_ground);
    stream.writeVarInt<std::uint64_t>(value.tick);
}

auto Serializer<v827::CorrectPlayerMovePredictionPacket>::deserialize(BinaryReader &stream) -> std::expected<v827::CorrectPlayerMovePredictionPacket, std::error_code>
{
    v827::CorrectPlayerMovePredictionPacket out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.prediction_type = static_cast<RewindType>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos_delta = *v;
    }
    {
        auto v = Serializer<Vec2>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.vehicle_rotation = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            float staged{};
            auto v = stream.read<float>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<float>(*v);
            out.vehicle_angular_velocity = std::move(staged);
        }
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.on_ground = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.tick = static_cast<PlayerInputTick>(*v);
    }
    return out;
}

void Serializer<v748::SetMovementAuthorityPacket>::serialize(BinaryWriter &stream, const v748::SetMovementAuthorityPacket &value)
{
    stream.write<std::uint8_t>(value.new_auth_movement_mode);
}

auto Serializer<v748::SetMovementAuthorityPacket>::deserialize(BinaryReader &stream) -> std::expected<v748::SetMovementAuthorityPacket, std::error_code>
{
    v748::SetMovementAuthorityPacket out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.new_auth_movement_mode = static_cast<ServerAuthMovementMode>(*v);
    }
    return out;
}

}  // namespace bedrock::protocol
