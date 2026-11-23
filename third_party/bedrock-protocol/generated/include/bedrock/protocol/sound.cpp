#include <bedrock/protocol/sound.h>

namespace bedrock::protocol {


void Serializer<ServerSoundHandle>::serialize(BinaryWriter &stream, const ServerSoundHandle &value)
{
    stream.write<std::uint64_t>(value.value);
}

auto Serializer<ServerSoundHandle>::deserialize(BinaryReader &stream) -> std::expected<ServerSoundHandle, std::error_code>
{
    ServerSoundHandle out;
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.value = static_cast<std::uint64_t>(*v);
    }
    return out;
}

void Serializer<base::PlaySoundPacket>::serialize(BinaryWriter &stream, const base::PlaySoundPacket &value)
{
    stream.write(value.name);
    Serializer<base::NetworkBlockPosition>::serialize(stream, value.pos);
    stream.write<float>(value.volume);
    stream.write<float>(value.pitch);
}

auto Serializer<base::PlaySoundPacket>::deserialize(BinaryReader &stream) -> std::expected<base::PlaySoundPacket, std::error_code>
{
    base::PlaySoundPacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = Serializer<base::NetworkBlockPosition>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.volume = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.pitch = static_cast<float>(*v);
    }
    return out;
}

void Serializer<v944::PlaySoundPacket>::serialize(BinaryWriter &stream, const v944::PlaySoundPacket &value)
{
    stream.write(value.name);
    Serializer<BlockPos>::serialize(stream, value.pos);
    stream.write<float>(value.volume);
    stream.write<float>(value.pitch);
}

auto Serializer<v944::PlaySoundPacket>::deserialize(BinaryReader &stream) -> std::expected<v944::PlaySoundPacket, std::error_code>
{
    v944::PlaySoundPacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.volume = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.pitch = static_cast<float>(*v);
    }
    return out;
}

void Serializer<v975::PlaySoundPacket>::serialize(BinaryWriter &stream, const v975::PlaySoundPacket &value)
{
    stream.write(value.name);
    Serializer<BlockPos>::serialize(stream, value.pos);
    stream.write<float>(value.volume);
    stream.write<float>(value.pitch);
    stream.write<bool>(value.server_sound_handle.has_value());
    if (value.server_sound_handle.has_value()) {
        Serializer<ServerSoundHandle>::serialize(stream, (*value.server_sound_handle));
    }
}

auto Serializer<v975::PlaySoundPacket>::deserialize(BinaryReader &stream) -> std::expected<v975::PlaySoundPacket, std::error_code>
{
    v975::PlaySoundPacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.volume = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.pitch = static_cast<float>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            ServerSoundHandle staged{};
            auto v = Serializer<ServerSoundHandle>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.server_sound_handle = std::move(staged);
        }
    }
    return out;
}

void Serializer<v2168::PlaySoundPacket>::serialize(BinaryWriter &stream, const v2168::PlaySoundPacket &value)
{
    stream.write(value.name);
    Serializer<BlockPos>::serialize(stream, value.pos);
    stream.write<float>(value.volume);
    stream.write<float>(value.pitch);
    stream.writeVarInt<std::int32_t>(value.loop_count);
    stream.write<bool>(value.server_sound_handle.has_value());
    if (value.server_sound_handle.has_value()) {
        Serializer<ServerSoundHandle>::serialize(stream, (*value.server_sound_handle));
    }
}

auto Serializer<v2168::PlaySoundPacket>::deserialize(BinaryReader &stream) -> std::expected<v2168::PlaySoundPacket, std::error_code>
{
    v2168::PlaySoundPacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.volume = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.pitch = static_cast<float>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.loop_count = static_cast<std::int32_t>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            ServerSoundHandle staged{};
            auto v = Serializer<ServerSoundHandle>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.server_sound_handle = std::move(staged);
        }
    }
    return out;
}

void Serializer<v2193::PlaySoundPacket>::serialize(BinaryWriter &stream, const v2193::PlaySoundPacket &value)
{
    stream.write(value.name);
    Serializer<BlockPos>::serialize(stream, value.pos);
    stream.write<float>(value.volume);
    stream.write<float>(value.pitch);
    stream.writeVarInt<std::int32_t>(value.loop_count);
    stream.write<bool>(value.bypass_listener_range_check);
    stream.write<bool>(value.server_sound_handle.has_value());
    if (value.server_sound_handle.has_value()) {
        Serializer<ServerSoundHandle>::serialize(stream, (*value.server_sound_handle));
    }
    stream.write<bool>(value.playback_position_seconds.has_value());
    if (value.playback_position_seconds.has_value()) {
        stream.write<float>((*value.playback_position_seconds));
    }
}

auto Serializer<v2193::PlaySoundPacket>::deserialize(BinaryReader &stream) -> std::expected<v2193::PlaySoundPacket, std::error_code>
{
    v2193::PlaySoundPacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.volume = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.pitch = static_cast<float>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.loop_count = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.bypass_listener_range_check = static_cast<bool>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            ServerSoundHandle staged{};
            auto v = Serializer<ServerSoundHandle>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.server_sound_handle = std::move(staged);
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
            out.playback_position_seconds = std::move(staged);
        }
    }
    return out;
}

void Serializer<v2168::Stop>::serialize(BinaryWriter &stream, const v2168::Stop &value)
{
}

auto Serializer<v2168::Stop>::deserialize(BinaryReader &stream) -> std::expected<v2168::Stop, std::error_code>
{
    v2168::Stop out;
    return out;
}

void Serializer<v2225::Stop>::serialize(BinaryWriter &stream, const v2225::Stop &value)
{
    stream.write<std::uint8_t>(0);
}

auto Serializer<v2225::Stop>::deserialize(BinaryReader &stream) -> std::expected<v2225::Stop, std::error_code>
{
    v2225::Stop out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 0) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    return out;
}

void Serializer<v2168::SetVolume>::serialize(BinaryWriter &stream, const v2168::SetVolume &value)
{
    stream.write<float>(value.volume);
}

auto Serializer<v2168::SetVolume>::deserialize(BinaryReader &stream) -> std::expected<v2168::SetVolume, std::error_code>
{
    v2168::SetVolume out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.volume = static_cast<float>(*v);
    }
    return out;
}

void Serializer<v2225::SetVolume>::serialize(BinaryWriter &stream, const v2225::SetVolume &value)
{
    stream.write<std::uint8_t>(1);
    stream.write<float>(value.volume);
}

auto Serializer<v2225::SetVolume>::deserialize(BinaryReader &stream) -> std::expected<v2225::SetVolume, std::error_code>
{
    v2225::SetVolume out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 1) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.volume = static_cast<float>(*v);
    }
    return out;
}

void Serializer<v2168::SetPitch>::serialize(BinaryWriter &stream, const v2168::SetPitch &value)
{
    stream.write<float>(value.pitch);
}

auto Serializer<v2168::SetPitch>::deserialize(BinaryReader &stream) -> std::expected<v2168::SetPitch, std::error_code>
{
    v2168::SetPitch out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.pitch = static_cast<float>(*v);
    }
    return out;
}

void Serializer<v2225::SetPitch>::serialize(BinaryWriter &stream, const v2225::SetPitch &value)
{
    stream.write<std::uint8_t>(2);
    stream.write<float>(value.pitch);
}

auto Serializer<v2225::SetPitch>::deserialize(BinaryReader &stream) -> std::expected<v2225::SetPitch, std::error_code>
{
    v2225::SetPitch out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 2) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.pitch = static_cast<float>(*v);
    }
    return out;
}

void Serializer<v2168::Fade>::serialize(BinaryWriter &stream, const v2168::Fade &value)
{
    stream.write<float>(value.duration);
    stream.write<float>(value.target_volume);
}

auto Serializer<v2168::Fade>::deserialize(BinaryReader &stream) -> std::expected<v2168::Fade, std::error_code>
{
    v2168::Fade out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.duration = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.target_volume = static_cast<float>(*v);
    }
    return out;
}

void Serializer<v2225::Fade>::serialize(BinaryWriter &stream, const v2225::Fade &value)
{
    stream.write<std::uint8_t>(3);
    stream.write<float>(value.duration);
    stream.write<float>(value.target_volume);
}

auto Serializer<v2225::Fade>::deserialize(BinaryReader &stream) -> std::expected<v2225::Fade, std::error_code>
{
    v2225::Fade out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 3) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.duration = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.target_volume = static_cast<float>(*v);
    }
    return out;
}

void Serializer<v2168::SeekTo>::serialize(BinaryWriter &stream, const v2168::SeekTo &value)
{
    stream.write<float>(value.seconds);
}

auto Serializer<v2168::SeekTo>::deserialize(BinaryReader &stream) -> std::expected<v2168::SeekTo, std::error_code>
{
    v2168::SeekTo out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.seconds = static_cast<float>(*v);
    }
    return out;
}

void Serializer<v2225::SeekTo>::serialize(BinaryWriter &stream, const v2225::SeekTo &value)
{
    stream.write<std::uint8_t>(4);
    stream.write<float>(value.seconds);
}

auto Serializer<v2225::SeekTo>::deserialize(BinaryReader &stream) -> std::expected<v2225::SeekTo, std::error_code>
{
    v2225::SeekTo out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 4) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.seconds = static_cast<float>(*v);
    }
    return out;
}

void Serializer<v2168::Pause>::serialize(BinaryWriter &stream, const v2168::Pause &value)
{
}

auto Serializer<v2168::Pause>::deserialize(BinaryReader &stream) -> std::expected<v2168::Pause, std::error_code>
{
    v2168::Pause out;
    return out;
}

void Serializer<v2225::Pause>::serialize(BinaryWriter &stream, const v2225::Pause &value)
{
    stream.write<std::uint8_t>(5);
}

auto Serializer<v2225::Pause>::deserialize(BinaryReader &stream) -> std::expected<v2225::Pause, std::error_code>
{
    v2225::Pause out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 5) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    return out;
}

void Serializer<v2168::Resume>::serialize(BinaryWriter &stream, const v2168::Resume &value)
{
}

auto Serializer<v2168::Resume>::deserialize(BinaryReader &stream) -> std::expected<v2168::Resume, std::error_code>
{
    v2168::Resume out;
    return out;
}

void Serializer<v2225::Resume>::serialize(BinaryWriter &stream, const v2225::Resume &value)
{
    stream.write<std::uint8_t>(6);
}

auto Serializer<v2225::Resume>::deserialize(BinaryReader &stream) -> std::expected<v2225::Resume, std::error_code>
{
    v2225::Resume out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 6) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    return out;
}

void Serializer<base::SoundDataEvent>::serialize(BinaryWriter &stream, base::SoundDataEvent value)
{
    stream.write(enum_name(value));
}

auto Serializer<base::SoundDataEvent>::deserialize(BinaryReader &stream) -> std::expected<base::SoundDataEvent, std::error_code>
{
    auto v = stream.read<std::string>();
    if (!v) return std::unexpected(v.error());
    const auto value = enum_cast<base::SoundDataEvent>(*v);
    if (!value) return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
    return *value;
}

void Serializer<v1001::ClientboundUpdateSoundDataPacket>::serialize(BinaryWriter &stream, const v1001::ClientboundUpdateSoundDataPacket &value)
{
    Serializer<ServerSoundHandle>::serialize(stream, value.server_sound_handle);
    Serializer<base::SoundDataEvent>::serialize(stream, value.sound_event);
}

auto Serializer<v1001::ClientboundUpdateSoundDataPacket>::deserialize(BinaryReader &stream) -> std::expected<v1001::ClientboundUpdateSoundDataPacket, std::error_code>
{
    v1001::ClientboundUpdateSoundDataPacket out;
    {
        auto v = Serializer<ServerSoundHandle>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.server_sound_handle = *v;
    }
    {
        auto v = Serializer<base::SoundDataEvent>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.sound_event = *v;
    }
    return out;
}

void Serializer<v2168::ClientboundUpdateSoundDataPacket>::serialize(BinaryWriter &stream, const v2168::ClientboundUpdateSoundDataPacket &value)
{
    Serializer<ServerSoundHandle>::serialize(stream, value.server_sound_handle);
    stream.writeVarInt<std::uint32_t>((value.stop).index());
    switch ((value.stop).index()) {
        case 0: {
            Serializer<v2168::Stop>::serialize(stream, std::get<0>(value.stop));
            break;
        }
        case 1: {
            Serializer<v2168::SetVolume>::serialize(stream, std::get<1>(value.stop));
            break;
        }
        case 2: {
            Serializer<v2168::SetPitch>::serialize(stream, std::get<2>(value.stop));
            break;
        }
        case 3: {
            Serializer<v2168::Fade>::serialize(stream, std::get<3>(value.stop));
            break;
        }
        case 4: {
            Serializer<v2168::SeekTo>::serialize(stream, std::get<4>(value.stop));
            break;
        }
        case 5: {
            Serializer<v2168::Pause>::serialize(stream, std::get<5>(value.stop));
            break;
        }
        case 6: {
            Serializer<v2168::Resume>::serialize(stream, std::get<6>(value.stop));
            break;
        }
    }
    stream.writeVarInt<std::uint32_t>((value.set_volume).index());
    switch ((value.set_volume).index()) {
        case 0: {
            Serializer<v2168::Stop>::serialize(stream, std::get<0>(value.set_volume));
            break;
        }
        case 1: {
            Serializer<v2168::SetVolume>::serialize(stream, std::get<1>(value.set_volume));
            break;
        }
        case 2: {
            Serializer<v2168::SetPitch>::serialize(stream, std::get<2>(value.set_volume));
            break;
        }
        case 3: {
            Serializer<v2168::Fade>::serialize(stream, std::get<3>(value.set_volume));
            break;
        }
        case 4: {
            Serializer<v2168::SeekTo>::serialize(stream, std::get<4>(value.set_volume));
            break;
        }
        case 5: {
            Serializer<v2168::Pause>::serialize(stream, std::get<5>(value.set_volume));
            break;
        }
        case 6: {
            Serializer<v2168::Resume>::serialize(stream, std::get<6>(value.set_volume));
            break;
        }
    }
    stream.writeVarInt<std::uint32_t>((value.set_pitch).index());
    switch ((value.set_pitch).index()) {
        case 0: {
            Serializer<v2168::Stop>::serialize(stream, std::get<0>(value.set_pitch));
            break;
        }
        case 1: {
            Serializer<v2168::SetVolume>::serialize(stream, std::get<1>(value.set_pitch));
            break;
        }
        case 2: {
            Serializer<v2168::SetPitch>::serialize(stream, std::get<2>(value.set_pitch));
            break;
        }
        case 3: {
            Serializer<v2168::Fade>::serialize(stream, std::get<3>(value.set_pitch));
            break;
        }
        case 4: {
            Serializer<v2168::SeekTo>::serialize(stream, std::get<4>(value.set_pitch));
            break;
        }
        case 5: {
            Serializer<v2168::Pause>::serialize(stream, std::get<5>(value.set_pitch));
            break;
        }
        case 6: {
            Serializer<v2168::Resume>::serialize(stream, std::get<6>(value.set_pitch));
            break;
        }
    }
    stream.writeVarInt<std::uint32_t>((value.fade).index());
    switch ((value.fade).index()) {
        case 0: {
            Serializer<v2168::Stop>::serialize(stream, std::get<0>(value.fade));
            break;
        }
        case 1: {
            Serializer<v2168::SetVolume>::serialize(stream, std::get<1>(value.fade));
            break;
        }
        case 2: {
            Serializer<v2168::SetPitch>::serialize(stream, std::get<2>(value.fade));
            break;
        }
        case 3: {
            Serializer<v2168::Fade>::serialize(stream, std::get<3>(value.fade));
            break;
        }
        case 4: {
            Serializer<v2168::SeekTo>::serialize(stream, std::get<4>(value.fade));
            break;
        }
        case 5: {
            Serializer<v2168::Pause>::serialize(stream, std::get<5>(value.fade));
            break;
        }
        case 6: {
            Serializer<v2168::Resume>::serialize(stream, std::get<6>(value.fade));
            break;
        }
    }
    stream.writeVarInt<std::uint32_t>((value.seek_to).index());
    switch ((value.seek_to).index()) {
        case 0: {
            Serializer<v2168::Stop>::serialize(stream, std::get<0>(value.seek_to));
            break;
        }
        case 1: {
            Serializer<v2168::SetVolume>::serialize(stream, std::get<1>(value.seek_to));
            break;
        }
        case 2: {
            Serializer<v2168::SetPitch>::serialize(stream, std::get<2>(value.seek_to));
            break;
        }
        case 3: {
            Serializer<v2168::Fade>::serialize(stream, std::get<3>(value.seek_to));
            break;
        }
        case 4: {
            Serializer<v2168::SeekTo>::serialize(stream, std::get<4>(value.seek_to));
            break;
        }
        case 5: {
            Serializer<v2168::Pause>::serialize(stream, std::get<5>(value.seek_to));
            break;
        }
        case 6: {
            Serializer<v2168::Resume>::serialize(stream, std::get<6>(value.seek_to));
            break;
        }
    }
    stream.writeVarInt<std::uint32_t>((value.pause).index());
    switch ((value.pause).index()) {
        case 0: {
            Serializer<v2168::Stop>::serialize(stream, std::get<0>(value.pause));
            break;
        }
        case 1: {
            Serializer<v2168::SetVolume>::serialize(stream, std::get<1>(value.pause));
            break;
        }
        case 2: {
            Serializer<v2168::SetPitch>::serialize(stream, std::get<2>(value.pause));
            break;
        }
        case 3: {
            Serializer<v2168::Fade>::serialize(stream, std::get<3>(value.pause));
            break;
        }
        case 4: {
            Serializer<v2168::SeekTo>::serialize(stream, std::get<4>(value.pause));
            break;
        }
        case 5: {
            Serializer<v2168::Pause>::serialize(stream, std::get<5>(value.pause));
            break;
        }
        case 6: {
            Serializer<v2168::Resume>::serialize(stream, std::get<6>(value.pause));
            break;
        }
    }
    stream.writeVarInt<std::uint32_t>((value.resume).index());
    switch ((value.resume).index()) {
        case 0: {
            Serializer<v2168::Stop>::serialize(stream, std::get<0>(value.resume));
            break;
        }
        case 1: {
            Serializer<v2168::SetVolume>::serialize(stream, std::get<1>(value.resume));
            break;
        }
        case 2: {
            Serializer<v2168::SetPitch>::serialize(stream, std::get<2>(value.resume));
            break;
        }
        case 3: {
            Serializer<v2168::Fade>::serialize(stream, std::get<3>(value.resume));
            break;
        }
        case 4: {
            Serializer<v2168::SeekTo>::serialize(stream, std::get<4>(value.resume));
            break;
        }
        case 5: {
            Serializer<v2168::Pause>::serialize(stream, std::get<5>(value.resume));
            break;
        }
        case 6: {
            Serializer<v2168::Resume>::serialize(stream, std::get<6>(value.resume));
            break;
        }
    }
}

auto Serializer<v2168::ClientboundUpdateSoundDataPacket>::deserialize(BinaryReader &stream) -> std::expected<v2168::ClientboundUpdateSoundDataPacket, std::error_code>
{
    v2168::ClientboundUpdateSoundDataPacket out;
    {
        auto v = Serializer<ServerSoundHandle>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.server_sound_handle = *v;
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume>> alt0{};
                {
                    auto v = Serializer<v2168::Stop>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume>> alt0{};
                {
                    auto v = Serializer<v2168::SetVolume>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume>> alt0{};
                {
                    auto v = Serializer<v2168::SetPitch>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume>> alt0{};
                {
                    auto v = Serializer<v2168::Fade>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            case 4: {
                std::variant_alternative_t<4, std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume>> alt0{};
                {
                    auto v = Serializer<v2168::SeekTo>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<4>(alt0);
                break;
            }
            case 5: {
                std::variant_alternative_t<5, std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume>> alt0{};
                {
                    auto v = Serializer<v2168::Pause>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<5>(alt0);
                break;
            }
            case 6: {
                std::variant_alternative_t<6, std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume>> alt0{};
                {
                    auto v = Serializer<v2168::Resume>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<6>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.stop = var0;
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume>> alt0{};
                {
                    auto v = Serializer<v2168::Stop>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume>> alt0{};
                {
                    auto v = Serializer<v2168::SetVolume>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume>> alt0{};
                {
                    auto v = Serializer<v2168::SetPitch>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume>> alt0{};
                {
                    auto v = Serializer<v2168::Fade>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            case 4: {
                std::variant_alternative_t<4, std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume>> alt0{};
                {
                    auto v = Serializer<v2168::SeekTo>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<4>(alt0);
                break;
            }
            case 5: {
                std::variant_alternative_t<5, std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume>> alt0{};
                {
                    auto v = Serializer<v2168::Pause>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<5>(alt0);
                break;
            }
            case 6: {
                std::variant_alternative_t<6, std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume>> alt0{};
                {
                    auto v = Serializer<v2168::Resume>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<6>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.set_volume = var0;
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume>> alt0{};
                {
                    auto v = Serializer<v2168::Stop>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume>> alt0{};
                {
                    auto v = Serializer<v2168::SetVolume>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume>> alt0{};
                {
                    auto v = Serializer<v2168::SetPitch>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume>> alt0{};
                {
                    auto v = Serializer<v2168::Fade>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            case 4: {
                std::variant_alternative_t<4, std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume>> alt0{};
                {
                    auto v = Serializer<v2168::SeekTo>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<4>(alt0);
                break;
            }
            case 5: {
                std::variant_alternative_t<5, std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume>> alt0{};
                {
                    auto v = Serializer<v2168::Pause>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<5>(alt0);
                break;
            }
            case 6: {
                std::variant_alternative_t<6, std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume>> alt0{};
                {
                    auto v = Serializer<v2168::Resume>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<6>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.set_pitch = var0;
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume>> alt0{};
                {
                    auto v = Serializer<v2168::Stop>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume>> alt0{};
                {
                    auto v = Serializer<v2168::SetVolume>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume>> alt0{};
                {
                    auto v = Serializer<v2168::SetPitch>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume>> alt0{};
                {
                    auto v = Serializer<v2168::Fade>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            case 4: {
                std::variant_alternative_t<4, std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume>> alt0{};
                {
                    auto v = Serializer<v2168::SeekTo>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<4>(alt0);
                break;
            }
            case 5: {
                std::variant_alternative_t<5, std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume>> alt0{};
                {
                    auto v = Serializer<v2168::Pause>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<5>(alt0);
                break;
            }
            case 6: {
                std::variant_alternative_t<6, std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume>> alt0{};
                {
                    auto v = Serializer<v2168::Resume>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<6>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.fade = var0;
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume>> alt0{};
                {
                    auto v = Serializer<v2168::Stop>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume>> alt0{};
                {
                    auto v = Serializer<v2168::SetVolume>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume>> alt0{};
                {
                    auto v = Serializer<v2168::SetPitch>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume>> alt0{};
                {
                    auto v = Serializer<v2168::Fade>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            case 4: {
                std::variant_alternative_t<4, std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume>> alt0{};
                {
                    auto v = Serializer<v2168::SeekTo>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<4>(alt0);
                break;
            }
            case 5: {
                std::variant_alternative_t<5, std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume>> alt0{};
                {
                    auto v = Serializer<v2168::Pause>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<5>(alt0);
                break;
            }
            case 6: {
                std::variant_alternative_t<6, std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume>> alt0{};
                {
                    auto v = Serializer<v2168::Resume>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<6>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.seek_to = var0;
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume>> alt0{};
                {
                    auto v = Serializer<v2168::Stop>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume>> alt0{};
                {
                    auto v = Serializer<v2168::SetVolume>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume>> alt0{};
                {
                    auto v = Serializer<v2168::SetPitch>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume>> alt0{};
                {
                    auto v = Serializer<v2168::Fade>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            case 4: {
                std::variant_alternative_t<4, std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume>> alt0{};
                {
                    auto v = Serializer<v2168::SeekTo>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<4>(alt0);
                break;
            }
            case 5: {
                std::variant_alternative_t<5, std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume>> alt0{};
                {
                    auto v = Serializer<v2168::Pause>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<5>(alt0);
                break;
            }
            case 6: {
                std::variant_alternative_t<6, std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume>> alt0{};
                {
                    auto v = Serializer<v2168::Resume>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<6>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.pause = var0;
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume>> alt0{};
                {
                    auto v = Serializer<v2168::Stop>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume>> alt0{};
                {
                    auto v = Serializer<v2168::SetVolume>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume>> alt0{};
                {
                    auto v = Serializer<v2168::SetPitch>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume>> alt0{};
                {
                    auto v = Serializer<v2168::Fade>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            case 4: {
                std::variant_alternative_t<4, std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume>> alt0{};
                {
                    auto v = Serializer<v2168::SeekTo>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<4>(alt0);
                break;
            }
            case 5: {
                std::variant_alternative_t<5, std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume>> alt0{};
                {
                    auto v = Serializer<v2168::Pause>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<5>(alt0);
                break;
            }
            case 6: {
                std::variant_alternative_t<6, std::variant<v2168::Stop, v2168::SetVolume, v2168::SetPitch, v2168::Fade, v2168::SeekTo, v2168::Pause, v2168::Resume>> alt0{};
                {
                    auto v = Serializer<v2168::Resume>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<6>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.resume = var0;
    }
    return out;
}

void Serializer<v2225::ClientboundUpdateSoundDataPacket>::serialize(BinaryWriter &stream, const v2225::ClientboundUpdateSoundDataPacket &value)
{
    Serializer<ServerSoundHandle>::serialize(stream, value.server_sound_handle);
    stream.writeVarInt<std::uint32_t>((value.event).index());
    switch ((value.event).index()) {
        case 0: {
            Serializer<v2225::Stop>::serialize(stream, std::get<0>(value.event));
            break;
        }
        case 1: {
            Serializer<v2225::SetVolume>::serialize(stream, std::get<1>(value.event));
            break;
        }
        case 2: {
            Serializer<v2225::SetPitch>::serialize(stream, std::get<2>(value.event));
            break;
        }
        case 3: {
            Serializer<v2225::Fade>::serialize(stream, std::get<3>(value.event));
            break;
        }
        case 4: {
            Serializer<v2225::SeekTo>::serialize(stream, std::get<4>(value.event));
            break;
        }
        case 5: {
            Serializer<v2225::Pause>::serialize(stream, std::get<5>(value.event));
            break;
        }
        case 6: {
            Serializer<v2225::Resume>::serialize(stream, std::get<6>(value.event));
            break;
        }
    }
}

auto Serializer<v2225::ClientboundUpdateSoundDataPacket>::deserialize(BinaryReader &stream) -> std::expected<v2225::ClientboundUpdateSoundDataPacket, std::error_code>
{
    v2225::ClientboundUpdateSoundDataPacket out;
    {
        auto v = Serializer<ServerSoundHandle>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.server_sound_handle = *v;
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v2225::Stop, v2225::SetVolume, v2225::SetPitch, v2225::Fade, v2225::SeekTo, v2225::Pause, v2225::Resume> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v2225::Stop, v2225::SetVolume, v2225::SetPitch, v2225::Fade, v2225::SeekTo, v2225::Pause, v2225::Resume>> alt0{};
                {
                    auto v = Serializer<v2225::Stop>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v2225::Stop, v2225::SetVolume, v2225::SetPitch, v2225::Fade, v2225::SeekTo, v2225::Pause, v2225::Resume>> alt0{};
                {
                    auto v = Serializer<v2225::SetVolume>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<v2225::Stop, v2225::SetVolume, v2225::SetPitch, v2225::Fade, v2225::SeekTo, v2225::Pause, v2225::Resume>> alt0{};
                {
                    auto v = Serializer<v2225::SetPitch>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<v2225::Stop, v2225::SetVolume, v2225::SetPitch, v2225::Fade, v2225::SeekTo, v2225::Pause, v2225::Resume>> alt0{};
                {
                    auto v = Serializer<v2225::Fade>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            case 4: {
                std::variant_alternative_t<4, std::variant<v2225::Stop, v2225::SetVolume, v2225::SetPitch, v2225::Fade, v2225::SeekTo, v2225::Pause, v2225::Resume>> alt0{};
                {
                    auto v = Serializer<v2225::SeekTo>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<4>(alt0);
                break;
            }
            case 5: {
                std::variant_alternative_t<5, std::variant<v2225::Stop, v2225::SetVolume, v2225::SetPitch, v2225::Fade, v2225::SeekTo, v2225::Pause, v2225::Resume>> alt0{};
                {
                    auto v = Serializer<v2225::Pause>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<5>(alt0);
                break;
            }
            case 6: {
                std::variant_alternative_t<6, std::variant<v2225::Stop, v2225::SetVolume, v2225::SetPitch, v2225::Fade, v2225::SeekTo, v2225::Pause, v2225::Resume>> alt0{};
                {
                    auto v = Serializer<v2225::Resume>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<6>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.event = var0;
    }
    return out;
}

void Serializer<base::LevelSoundEventPacket>::serialize(BinaryWriter &stream, const base::LevelSoundEventPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.event_id);
    Serializer<Vec3>::serialize(stream, value.pos);
    stream.writeVarInt<std::int32_t>(value.data);
    stream.write(value.actor_identifier);
    stream.write<bool>(value.is_baby);
    stream.write<bool>(value.is_global);
}

auto Serializer<base::LevelSoundEventPacket>::deserialize(BinaryReader &stream) -> std::expected<base::LevelSoundEventPacket, std::error_code>
{
    base::LevelSoundEventPacket out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.event_id = static_cast<base::LevelSoundEvent>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.data = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.actor_identifier = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_baby = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_global = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v766::LevelSoundEventPacket>::serialize(BinaryWriter &stream, const v766::LevelSoundEventPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.event_id);
    Serializer<Vec3>::serialize(stream, value.pos);
    stream.writeVarInt<std::int32_t>(value.data);
    stream.write(value.actor_identifier);
    stream.write<bool>(value.is_baby);
    stream.write<bool>(value.is_global);
}

auto Serializer<v766::LevelSoundEventPacket>::deserialize(BinaryReader &stream) -> std::expected<v766::LevelSoundEventPacket, std::error_code>
{
    v766::LevelSoundEventPacket out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.event_id = static_cast<v766::LevelSoundEvent>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.data = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.actor_identifier = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_baby = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_global = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v786::LevelSoundEventPacket>::serialize(BinaryWriter &stream, const v786::LevelSoundEventPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.event_id);
    Serializer<Vec3>::serialize(stream, value.pos);
    stream.writeVarInt<std::int32_t>(value.data);
    stream.write(value.actor_identifier);
    stream.write<bool>(value.is_baby);
    stream.write<bool>(value.is_global);
    stream.write<std::int64_t>(value.actor);
}

auto Serializer<v786::LevelSoundEventPacket>::deserialize(BinaryReader &stream) -> std::expected<v786::LevelSoundEventPacket, std::error_code>
{
    v786::LevelSoundEventPacket out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.event_id = static_cast<v766::LevelSoundEvent>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.data = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.actor_identifier = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_baby = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_global = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.actor = static_cast<ActorUniqueID>(*v);
    }
    return out;
}

void Serializer<v800::LevelSoundEventPacket>::serialize(BinaryWriter &stream, const v800::LevelSoundEventPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.event_id);
    Serializer<Vec3>::serialize(stream, value.pos);
    stream.writeVarInt<std::int32_t>(value.data);
    stream.write(value.actor_identifier);
    stream.write<bool>(value.is_baby);
    stream.write<bool>(value.is_global);
    stream.write<std::int64_t>(value.actor);
}

auto Serializer<v800::LevelSoundEventPacket>::deserialize(BinaryReader &stream) -> std::expected<v800::LevelSoundEventPacket, std::error_code>
{
    v800::LevelSoundEventPacket out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.event_id = static_cast<v800::LevelSoundEvent>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.data = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.actor_identifier = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_baby = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_global = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.actor = static_cast<ActorUniqueID>(*v);
    }
    return out;
}

void Serializer<v818::LevelSoundEventPacket>::serialize(BinaryWriter &stream, const v818::LevelSoundEventPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.event_id);
    Serializer<Vec3>::serialize(stream, value.pos);
    stream.writeVarInt<std::int32_t>(value.data);
    stream.write(value.actor_identifier);
    stream.write<bool>(value.is_baby);
    stream.write<bool>(value.is_global);
    stream.write<std::int64_t>(value.actor);
}

auto Serializer<v818::LevelSoundEventPacket>::deserialize(BinaryReader &stream) -> std::expected<v818::LevelSoundEventPacket, std::error_code>
{
    v818::LevelSoundEventPacket out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.event_id = static_cast<v818::LevelSoundEvent>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.data = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.actor_identifier = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_baby = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_global = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.actor = static_cast<ActorUniqueID>(*v);
    }
    return out;
}

void Serializer<v819::LevelSoundEventPacket>::serialize(BinaryWriter &stream, const v819::LevelSoundEventPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.event_id);
    Serializer<Vec3>::serialize(stream, value.pos);
    stream.writeVarInt<std::int32_t>(value.data);
    stream.write(value.actor_identifier);
    stream.write<bool>(value.is_baby);
    stream.write<bool>(value.is_global);
    stream.write<std::int64_t>(value.actor);
}

auto Serializer<v819::LevelSoundEventPacket>::deserialize(BinaryReader &stream) -> std::expected<v819::LevelSoundEventPacket, std::error_code>
{
    v819::LevelSoundEventPacket out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.event_id = static_cast<v819::LevelSoundEvent>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.data = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.actor_identifier = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_baby = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_global = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.actor = static_cast<ActorUniqueID>(*v);
    }
    return out;
}

void Serializer<v827::LevelSoundEventPacket>::serialize(BinaryWriter &stream, const v827::LevelSoundEventPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.event_id);
    Serializer<Vec3>::serialize(stream, value.pos);
    stream.writeVarInt<std::int32_t>(value.data);
    stream.write(value.actor_identifier);
    stream.write<bool>(value.is_baby);
    stream.write<bool>(value.is_global);
    stream.write<std::int64_t>(value.actor);
}

auto Serializer<v827::LevelSoundEventPacket>::deserialize(BinaryReader &stream) -> std::expected<v827::LevelSoundEventPacket, std::error_code>
{
    v827::LevelSoundEventPacket out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.event_id = static_cast<v827::LevelSoundEvent>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.data = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.actor_identifier = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_baby = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_global = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.actor = static_cast<ActorUniqueID>(*v);
    }
    return out;
}

void Serializer<v844::LevelSoundEventPacket>::serialize(BinaryWriter &stream, const v844::LevelSoundEventPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.event_id);
    Serializer<Vec3>::serialize(stream, value.pos);
    stream.writeVarInt<std::int32_t>(value.data);
    stream.write(value.actor_identifier);
    stream.write<bool>(value.is_baby);
    stream.write<bool>(value.is_global);
    stream.write<std::int64_t>(value.actor);
}

auto Serializer<v844::LevelSoundEventPacket>::deserialize(BinaryReader &stream) -> std::expected<v844::LevelSoundEventPacket, std::error_code>
{
    v844::LevelSoundEventPacket out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.event_id = static_cast<v844::LevelSoundEvent>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.data = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.actor_identifier = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_baby = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_global = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.actor = static_cast<ActorUniqueID>(*v);
    }
    return out;
}

void Serializer<v898::LevelSoundEventPacket>::serialize(BinaryWriter &stream, const v898::LevelSoundEventPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.event_id);
    Serializer<Vec3>::serialize(stream, value.pos);
    stream.writeVarInt<std::int32_t>(value.data);
    stream.write(value.actor_identifier);
    stream.write<bool>(value.is_baby);
    stream.write<bool>(value.is_global);
    stream.write<std::int64_t>(value.actor);
}

auto Serializer<v898::LevelSoundEventPacket>::deserialize(BinaryReader &stream) -> std::expected<v898::LevelSoundEventPacket, std::error_code>
{
    v898::LevelSoundEventPacket out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.event_id = static_cast<v898::LevelSoundEvent>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.data = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.actor_identifier = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_baby = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_global = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.actor = static_cast<ActorUniqueID>(*v);
    }
    return out;
}

void Serializer<v924::LevelSoundEventPacket>::serialize(BinaryWriter &stream, const v924::LevelSoundEventPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.event_id);
    Serializer<Vec3>::serialize(stream, value.pos);
    stream.writeVarInt<std::int32_t>(value.data);
    stream.write(value.actor_identifier);
    stream.write<bool>(value.is_baby);
    stream.write<bool>(value.is_global);
    stream.write<std::int64_t>(value.actor);
}

auto Serializer<v924::LevelSoundEventPacket>::deserialize(BinaryReader &stream) -> std::expected<v924::LevelSoundEventPacket, std::error_code>
{
    v924::LevelSoundEventPacket out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.event_id = static_cast<v924::LevelSoundEvent>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.data = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.actor_identifier = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_baby = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_global = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.actor = static_cast<ActorUniqueID>(*v);
    }
    return out;
}

void Serializer<v944::LevelSoundEventPacket>::serialize(BinaryWriter &stream, const v944::LevelSoundEventPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.event_id);
    Serializer<Vec3>::serialize(stream, value.pos);
    stream.writeVarInt<std::int32_t>(value.data);
    stream.write(value.actor_identifier);
    stream.write<bool>(value.is_baby);
    stream.write<bool>(value.is_global);
    stream.write<std::int64_t>(value.actor);
}

auto Serializer<v944::LevelSoundEventPacket>::deserialize(BinaryReader &stream) -> std::expected<v944::LevelSoundEventPacket, std::error_code>
{
    v944::LevelSoundEventPacket out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.event_id = static_cast<v944::LevelSoundEvent>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.data = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.actor_identifier = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_baby = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_global = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.actor = static_cast<ActorUniqueID>(*v);
    }
    return out;
}

void Serializer<v975::LevelSoundEventPacket>::serialize(BinaryWriter &stream, const v975::LevelSoundEventPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.event_id);
    Serializer<Vec3>::serialize(stream, value.pos);
    stream.writeVarInt<std::int32_t>(value.data);
    stream.write(value.actor_identifier);
    stream.write<bool>(value.is_baby);
    stream.write<bool>(value.is_global);
    stream.write<std::int64_t>(value.actor);
    stream.write<bool>(value.fire_at_position.has_value());
    if (value.fire_at_position.has_value()) {
        Serializer<Vec3>::serialize(stream, (*value.fire_at_position));
    }
}

auto Serializer<v975::LevelSoundEventPacket>::deserialize(BinaryReader &stream) -> std::expected<v975::LevelSoundEventPacket, std::error_code>
{
    v975::LevelSoundEventPacket out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.event_id = static_cast<v975::LevelSoundEvent>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.data = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.actor_identifier = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_baby = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_global = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.actor = static_cast<ActorUniqueID>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec3 staged{};
            auto v = Serializer<Vec3>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.fire_at_position = std::move(staged);
        }
    }
    return out;
}

void Serializer<v1001::LevelSoundEventPacket>::serialize(BinaryWriter &stream, const v1001::LevelSoundEventPacket &value)
{
    stream.write(value.sound_event);
    Serializer<Vec3>::serialize(stream, value.pos);
    stream.writeVarInt<std::int32_t>(value.data);
    stream.write(value.actor_identifier);
    stream.write<bool>(value.is_baby);
    stream.write<bool>(value.is_global);
    stream.write<std::int64_t>(value.actor);
    stream.write<bool>(value.fire_at_position.has_value());
    if (value.fire_at_position.has_value()) {
        Serializer<Vec3>::serialize(stream, (*value.fire_at_position));
    }
}

auto Serializer<v1001::LevelSoundEventPacket>::deserialize(BinaryReader &stream) -> std::expected<v1001::LevelSoundEventPacket, std::error_code>
{
    v1001::LevelSoundEventPacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.sound_event = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.data = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.actor_identifier = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_baby = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_global = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.actor = static_cast<ActorUniqueID>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec3 staged{};
            auto v = Serializer<Vec3>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.fire_at_position = std::move(staged);
        }
    }
    return out;
}

void Serializer<v2168::LevelSoundEventPacket>::serialize(BinaryWriter &stream, const v2168::LevelSoundEventPacket &value)
{
    stream.write(value.sound_event);
    Serializer<Vec3>::serialize(stream, value.pos);
    stream.writeVarInt<std::int32_t>(value.data);
    stream.write(value.actor_identifier);
    stream.write<bool>(value.is_baby);
    stream.write<bool>(value.is_global);
    stream.write<std::int64_t>(value.actor);
    stream.write<bool>(value.fire_at_position.has_value());
    if (value.fire_at_position.has_value()) {
        Serializer<Vec3>::serialize(stream, (*value.fire_at_position));
    }
}

auto Serializer<v2168::LevelSoundEventPacket>::deserialize(BinaryReader &stream) -> std::expected<v2168::LevelSoundEventPacket, std::error_code>
{
    v2168::LevelSoundEventPacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.sound_event = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.data = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.actor_identifier = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_baby = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_global = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.actor = static_cast<ActorUniqueID>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec3 staged{};
            auto v = Serializer<Vec3>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.fire_at_position = std::move(staged);
        }
    }
    return out;
}

void Serializer<v2225::LevelSoundEventPacket>::serialize(BinaryWriter &stream, const v2225::LevelSoundEventPacket &value)
{
    stream.write(value.sound_event);
    Serializer<Vec3>::serialize(stream, value.pos);
    stream.writeVarInt<std::int32_t>(value.data);
    stream.write(value.actor_identifier);
    stream.write<bool>(value.is_baby);
    stream.write<bool>(value.is_global);
    stream.write<std::int64_t>(value.actor);
    stream.write<bool>(value.fire_at_position.has_value());
    if (value.fire_at_position.has_value()) {
        Serializer<Vec3>::serialize(stream, (*value.fire_at_position));
    }
}

auto Serializer<v2225::LevelSoundEventPacket>::deserialize(BinaryReader &stream) -> std::expected<v2225::LevelSoundEventPacket, std::error_code>
{
    v2225::LevelSoundEventPacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.sound_event = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.data = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.actor_identifier = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_baby = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_global = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.actor = static_cast<ActorUniqueID>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec3 staged{};
            auto v = Serializer<Vec3>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.fire_at_position = std::move(staged);
        }
    }
    return out;
}

void Serializer<v2193::RecordStartedPacket>::serialize(BinaryWriter &stream, const v2193::RecordStartedPacket &value)
{
    Serializer<BlockPos>::serialize(stream, value.block_pos);
    Serializer<ServerSoundHandle>::serialize(stream, value.server_sound_handle);
}

auto Serializer<v2193::RecordStartedPacket>::deserialize(BinaryReader &stream) -> std::expected<v2193::RecordStartedPacket, std::error_code>
{
    v2193::RecordStartedPacket out;
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.block_pos = *v;
    }
    {
        auto v = Serializer<ServerSoundHandle>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.server_sound_handle = *v;
    }
    return out;
}

void Serializer<StopSoundPacket>::serialize(BinaryWriter &stream, const StopSoundPacket &value)
{
    stream.write(value.name);
    stream.write<bool>(value.stop_all);
    stream.write<bool>(value.stop_music_legacy);
}

auto Serializer<StopSoundPacket>::deserialize(BinaryReader &stream) -> std::expected<StopSoundPacket, std::error_code>
{
    StopSoundPacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.stop_all = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.stop_music_legacy = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<SignedAudioContent>::serialize(BinaryWriter &stream, const SignedAudioContent &value)
{
    stream.write(value.compact_jwt);
}

auto Serializer<SignedAudioContent>::deserialize(BinaryReader &stream) -> std::expected<SignedAudioContent, std::error_code>
{
    SignedAudioContent out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.compact_jwt = *v;
    }
    return out;
}

void Serializer<AudioContentPlaybackType>::serialize(BinaryWriter &stream, AudioContentPlaybackType value)
{
    stream.write(enum_name(value));
}

auto Serializer<AudioContentPlaybackType>::deserialize(BinaryReader &stream) -> std::expected<AudioContentPlaybackType, std::error_code>
{
    auto v = stream.read<std::string>();
    if (!v) return std::unexpected(v.error());
    const auto value = enum_cast<AudioContentPlaybackType>(*v);
    if (!value) return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
    return *value;
}

void Serializer<v2225::ClientboundPlayAudioContentPacket>::serialize(BinaryWriter &stream, const v2225::ClientboundPlayAudioContentPacket &value)
{
    Serializer<SignedAudioContent>::serialize(stream, value.shared_metadata);
    Serializer<SignedAudioContent>::serialize(stream, value.playback_content);
    Serializer<AudioContentPlaybackType>::serialize(stream, value.playback_type);
    Serializer<v2193::PlaySoundPacket>::serialize(stream, value.play_sound);
}

auto Serializer<v2225::ClientboundPlayAudioContentPacket>::deserialize(BinaryReader &stream) -> std::expected<v2225::ClientboundPlayAudioContentPacket, std::error_code>
{
    v2225::ClientboundPlayAudioContentPacket out;
    {
        auto v = Serializer<SignedAudioContent>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.shared_metadata = *v;
    }
    {
        auto v = Serializer<SignedAudioContent>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.playback_content = *v;
    }
    {
        auto v = Serializer<AudioContentPlaybackType>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.playback_type = *v;
    }
    {
        auto v = Serializer<v2193::PlaySoundPacket>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.play_sound = *v;
    }
    return out;
}

void Serializer<AudioContentRegistrationEntry>::serialize(BinaryWriter &stream, const AudioContentRegistrationEntry &value)
{
    stream.write(value.audio_content_id);
    Serializer<SignedAudioContent>::serialize(stream, value.shared_metadata);
    Serializer<SignedAudioContent>::serialize(stream, value.server_content);
    Serializer<SignedAudioContent>::serialize(stream, value.playback_content);
}

auto Serializer<AudioContentRegistrationEntry>::deserialize(BinaryReader &stream) -> std::expected<AudioContentRegistrationEntry, std::error_code>
{
    AudioContentRegistrationEntry out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.audio_content_id = *v;
    }
    {
        auto v = Serializer<SignedAudioContent>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.shared_metadata = *v;
    }
    {
        auto v = Serializer<SignedAudioContent>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.server_content = *v;
    }
    {
        auto v = Serializer<SignedAudioContent>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.playback_content = *v;
    }
    return out;
}

void Serializer<v2225::ServerboundRegisterAudioContentPacket>::serialize(BinaryWriter &stream, const v2225::ServerboundRegisterAudioContentPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.registrations.size());
    for (const auto &e0 : value.registrations) {
        Serializer<AudioContentRegistrationEntry>::serialize(stream, e0);
    }
}

auto Serializer<v2225::ServerboundRegisterAudioContentPacket>::deserialize(BinaryReader &stream) -> std::expected<v2225::ServerboundRegisterAudioContentPacket, std::error_code>
{
    v2225::ServerboundRegisterAudioContentPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.registrations.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.registrations.emplace_back();
            auto v = Serializer<AudioContentRegistrationEntry>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.registrations.back() = *v;
        }
    }
    return out;
}

void Serializer<base::LevelSoundEventPacketV1>::serialize(BinaryWriter &stream, const base::LevelSoundEventPacketV1 &value)
{
    stream.write<std::uint8_t>(value.event_id);
    Serializer<Vec3>::serialize(stream, value.pos);
    stream.writeVarInt<std::int32_t>(value.data);
    stream.writeVarInt<std::int32_t>(value.entity_type);
    stream.write<bool>(value.is_baby_mob);
    stream.write<bool>(value.is_global);
}

auto Serializer<base::LevelSoundEventPacketV1>::deserialize(BinaryReader &stream) -> std::expected<base::LevelSoundEventPacketV1, std::error_code>
{
    base::LevelSoundEventPacketV1 out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.event_id = static_cast<base::LevelSoundEvent>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.data = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_type = static_cast<base::ActorType>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_baby_mob = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_global = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v766::LevelSoundEventPacketV1>::serialize(BinaryWriter &stream, const v766::LevelSoundEventPacketV1 &value)
{
    stream.write<std::uint8_t>(value.event_id);
    Serializer<Vec3>::serialize(stream, value.pos);
    stream.writeVarInt<std::int32_t>(value.data);
    stream.writeVarInt<std::int32_t>(value.entity_type);
    stream.write<bool>(value.is_baby_mob);
    stream.write<bool>(value.is_global);
}

auto Serializer<v766::LevelSoundEventPacketV1>::deserialize(BinaryReader &stream) -> std::expected<v766::LevelSoundEventPacketV1, std::error_code>
{
    v766::LevelSoundEventPacketV1 out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.event_id = static_cast<v766::LevelSoundEvent>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.data = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_type = static_cast<v766::ActorType>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_baby_mob = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_global = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<base::LevelSoundEventPacketV2>::serialize(BinaryWriter &stream, const base::LevelSoundEventPacketV2 &value)
{
    stream.write<std::uint8_t>(value.event_id);
    Serializer<Vec3>::serialize(stream, value.pos);
    stream.writeVarInt<std::int32_t>(value.data);
    stream.write(value.entity_identifier);
    stream.write<bool>(value.is_baby_mob);
    stream.write<bool>(value.is_global);
}

auto Serializer<base::LevelSoundEventPacketV2>::deserialize(BinaryReader &stream) -> std::expected<base::LevelSoundEventPacketV2, std::error_code>
{
    base::LevelSoundEventPacketV2 out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.event_id = static_cast<base::LevelSoundEvent>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.data = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.entity_identifier = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_baby_mob = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_global = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v766::LevelSoundEventPacketV2>::serialize(BinaryWriter &stream, const v766::LevelSoundEventPacketV2 &value)
{
    stream.write<std::uint8_t>(value.event_id);
    Serializer<Vec3>::serialize(stream, value.pos);
    stream.writeVarInt<std::int32_t>(value.data);
    stream.write(value.entity_identifier);
    stream.write<bool>(value.is_baby_mob);
    stream.write<bool>(value.is_global);
}

auto Serializer<v766::LevelSoundEventPacketV2>::deserialize(BinaryReader &stream) -> std::expected<v766::LevelSoundEventPacketV2, std::error_code>
{
    v766::LevelSoundEventPacketV2 out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.event_id = static_cast<v766::LevelSoundEvent>(*v);
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.data = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.entity_identifier = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_baby_mob = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_global = static_cast<bool>(*v);
    }
    return out;
}

}  // namespace bedrock::protocol
