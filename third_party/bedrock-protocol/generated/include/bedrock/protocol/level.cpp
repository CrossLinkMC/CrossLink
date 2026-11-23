#include <bedrock/protocol/level.h>

namespace bedrock::protocol {


void Serializer<SetTimePacket>::serialize(BinaryWriter &stream, const SetTimePacket &value)
{
    stream.writeVarInt<std::int32_t>(value.time);
}

auto Serializer<SetTimePacket>::deserialize(BinaryReader &stream) -> std::expected<SetTimePacket, std::error_code>
{
    SetTimePacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.time = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<SyncWorldClockStateData>::serialize(BinaryWriter &stream, const SyncWorldClockStateData &value)
{
    stream.writeVarInt<std::uint64_t>(value.clock_id);
    stream.writeVarInt<std::int32_t>(value.time);
    stream.write<bool>(value.is_paused);
}

auto Serializer<SyncWorldClockStateData>::deserialize(BinaryReader &stream) -> std::expected<SyncWorldClockStateData, std::error_code>
{
    SyncWorldClockStateData out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.clock_id = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.time = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_paused = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<TimeMarkerData>::serialize(BinaryWriter &stream, const TimeMarkerData &value)
{
    stream.writeVarInt<std::uint64_t>(value.id);
    stream.write(value.name);
    stream.writeVarInt<std::int32_t>(value.time);
    stream.write<bool>(value.period.has_value());
    if (value.period.has_value()) {
        stream.write<std::int32_t>((*value.period));
    }
}

auto Serializer<TimeMarkerData>::deserialize(BinaryReader &stream) -> std::expected<TimeMarkerData, std::error_code>
{
    TimeMarkerData out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.id = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.time = static_cast<std::int32_t>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::int32_t staged{};
            auto v = stream.read<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<std::int32_t>(*v);
            out.period = std::move(staged);
        }
    }
    return out;
}

void Serializer<WorldClockData>::serialize(BinaryWriter &stream, const WorldClockData &value)
{
    stream.writeVarInt<std::uint64_t>(value.id);
    stream.write(value.name);
    stream.writeVarInt<std::int32_t>(value.time);
    stream.write<bool>(value.is_paused);
    stream.writeVarInt<std::uint32_t>(value.time_markers.size());
    for (const auto &e0 : value.time_markers) {
        Serializer<TimeMarkerData>::serialize(stream, e0);
    }
}

auto Serializer<WorldClockData>::deserialize(BinaryReader &stream) -> std::expected<WorldClockData, std::error_code>
{
    WorldClockData out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.id = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.time = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_paused = static_cast<bool>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.time_markers.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.time_markers.emplace_back();
            auto v = Serializer<TimeMarkerData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.time_markers.back() = *v;
        }
    }
    return out;
}

void Serializer<v944::SyncWorldClocksPacket::SyncStateData>::serialize(BinaryWriter &stream, const v944::SyncWorldClocksPacket::SyncStateData &value)
{
    stream.writeVarInt<std::uint32_t>(value.clock_data.size());
    for (const auto &e0 : value.clock_data) {
        Serializer<SyncWorldClockStateData>::serialize(stream, e0);
    }
}

auto Serializer<v944::SyncWorldClocksPacket::SyncStateData>::deserialize(BinaryReader &stream) -> std::expected<v944::SyncWorldClocksPacket::SyncStateData, std::error_code>
{
    v944::SyncWorldClocksPacket::SyncStateData out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.clock_data.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.clock_data.emplace_back();
            auto v = Serializer<SyncWorldClockStateData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.clock_data.back() = *v;
        }
    }
    return out;
}

void Serializer<v944::SyncWorldClocksPacket::InitializeRegistryData>::serialize(BinaryWriter &stream, const v944::SyncWorldClocksPacket::InitializeRegistryData &value)
{
    stream.writeVarInt<std::uint32_t>(value.clock_data.size());
    for (const auto &e0 : value.clock_data) {
        Serializer<WorldClockData>::serialize(stream, e0);
    }
}

auto Serializer<v944::SyncWorldClocksPacket::InitializeRegistryData>::deserialize(BinaryReader &stream) -> std::expected<v944::SyncWorldClocksPacket::InitializeRegistryData, std::error_code>
{
    v944::SyncWorldClocksPacket::InitializeRegistryData out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.clock_data.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.clock_data.emplace_back();
            auto v = Serializer<WorldClockData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.clock_data.back() = *v;
        }
    }
    return out;
}

void Serializer<v944::SyncWorldClocksPacket::AddTimeMarkerData>::serialize(BinaryWriter &stream, const v944::SyncWorldClocksPacket::AddTimeMarkerData &value)
{
    stream.writeVarInt<std::uint64_t>(value.clock_id);
    stream.writeVarInt<std::uint32_t>(value.time_markers.size());
    for (const auto &e0 : value.time_markers) {
        Serializer<TimeMarkerData>::serialize(stream, e0);
    }
}

auto Serializer<v944::SyncWorldClocksPacket::AddTimeMarkerData>::deserialize(BinaryReader &stream) -> std::expected<v944::SyncWorldClocksPacket::AddTimeMarkerData, std::error_code>
{
    v944::SyncWorldClocksPacket::AddTimeMarkerData out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.clock_id = static_cast<std::uint64_t>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.time_markers.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.time_markers.emplace_back();
            auto v = Serializer<TimeMarkerData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.time_markers.back() = *v;
        }
    }
    return out;
}

void Serializer<v944::SyncWorldClocksPacket::RemoveTimeMarkerData>::serialize(BinaryWriter &stream, const v944::SyncWorldClocksPacket::RemoveTimeMarkerData &value)
{
    stream.writeVarInt<std::uint64_t>(value.clock_id);
    stream.writeVarInt<std::uint32_t>(value.time_marker_ids.size());
    for (const auto &e0 : value.time_marker_ids) {
        stream.writeVarInt<std::uint64_t>(e0);
    }
}

auto Serializer<v944::SyncWorldClocksPacket::RemoveTimeMarkerData>::deserialize(BinaryReader &stream) -> std::expected<v944::SyncWorldClocksPacket::RemoveTimeMarkerData, std::error_code>
{
    v944::SyncWorldClocksPacket::RemoveTimeMarkerData out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.clock_id = static_cast<std::uint64_t>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.time_marker_ids.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.time_marker_ids.emplace_back();
            auto v = stream.readVarInt<std::uint64_t>();
            if (!v) return std::unexpected(v.error());
            out.time_marker_ids.back() = static_cast<std::uint64_t>(*v);
        }
    }
    return out;
}

void Serializer<v944::SyncWorldClocksPacket>::serialize(BinaryWriter &stream, const v944::SyncWorldClocksPacket &value)
{
    stream.writeVarInt<std::uint32_t>((value.data).index());
    switch ((value.data).index()) {
        case 0: {
            Serializer<v944::SyncWorldClocksPacket::SyncStateData>::serialize(stream, std::get<0>(value.data));
            break;
        }
        case 1: {
            Serializer<v944::SyncWorldClocksPacket::InitializeRegistryData>::serialize(stream, std::get<1>(value.data));
            break;
        }
        case 2: {
            Serializer<v944::SyncWorldClocksPacket::AddTimeMarkerData>::serialize(stream, std::get<2>(value.data));
            break;
        }
        case 3: {
            Serializer<v944::SyncWorldClocksPacket::RemoveTimeMarkerData>::serialize(stream, std::get<3>(value.data));
            break;
        }
    }
}

auto Serializer<v944::SyncWorldClocksPacket>::deserialize(BinaryReader &stream) -> std::expected<v944::SyncWorldClocksPacket, std::error_code>
{
    v944::SyncWorldClocksPacket out;
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v944::SyncWorldClocksPacket::SyncStateData, v944::SyncWorldClocksPacket::InitializeRegistryData, v944::SyncWorldClocksPacket::AddTimeMarkerData, v944::SyncWorldClocksPacket::RemoveTimeMarkerData> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v944::SyncWorldClocksPacket::SyncStateData, v944::SyncWorldClocksPacket::InitializeRegistryData, v944::SyncWorldClocksPacket::AddTimeMarkerData, v944::SyncWorldClocksPacket::RemoveTimeMarkerData>> alt0{};
                {
                    auto v = Serializer<v944::SyncWorldClocksPacket::SyncStateData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v944::SyncWorldClocksPacket::SyncStateData, v944::SyncWorldClocksPacket::InitializeRegistryData, v944::SyncWorldClocksPacket::AddTimeMarkerData, v944::SyncWorldClocksPacket::RemoveTimeMarkerData>> alt0{};
                {
                    auto v = Serializer<v944::SyncWorldClocksPacket::InitializeRegistryData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<v944::SyncWorldClocksPacket::SyncStateData, v944::SyncWorldClocksPacket::InitializeRegistryData, v944::SyncWorldClocksPacket::AddTimeMarkerData, v944::SyncWorldClocksPacket::RemoveTimeMarkerData>> alt0{};
                {
                    auto v = Serializer<v944::SyncWorldClocksPacket::AddTimeMarkerData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<v944::SyncWorldClocksPacket::SyncStateData, v944::SyncWorldClocksPacket::InitializeRegistryData, v944::SyncWorldClocksPacket::AddTimeMarkerData, v944::SyncWorldClocksPacket::RemoveTimeMarkerData>> alt0{};
                {
                    auto v = Serializer<v944::SyncWorldClocksPacket::RemoveTimeMarkerData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.data = var0;
    }
    return out;
}

void Serializer<PositionTrackingId>::serialize(BinaryWriter &stream, const PositionTrackingId &value)
{
    stream.writeVarInt<std::int32_t>(value.raw_id);
}

auto Serializer<PositionTrackingId>::deserialize(BinaryReader &stream) -> std::expected<PositionTrackingId, std::error_code>
{
    PositionTrackingId out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.raw_id = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<PositionTrackingDBServerBroadcastPacket>::serialize(BinaryWriter &stream, const PositionTrackingDBServerBroadcastPacket &value)
{
    stream.write<std::uint8_t>(value.action);
    Serializer<PositionTrackingId>::serialize(stream, value.id);
    Serializer<CompoundTag>::serialize(stream, value.data);
}

auto Serializer<PositionTrackingDBServerBroadcastPacket>::deserialize(BinaryReader &stream) -> std::expected<PositionTrackingDBServerBroadcastPacket, std::error_code>
{
    PositionTrackingDBServerBroadcastPacket out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.action = static_cast<PositionTrackingDBServerBroadcastPacket::Action>(*v);
    }
    {
        auto v = Serializer<PositionTrackingId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.id = *v;
    }
    {
        auto v = Serializer<CompoundTag>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.data = *v;
    }
    return out;
}

void Serializer<PositionTrackingDBClientRequestPacket>::serialize(BinaryWriter &stream, const PositionTrackingDBClientRequestPacket &value)
{
    stream.write<std::uint8_t>(value.action);
    Serializer<PositionTrackingId>::serialize(stream, value.id);
}

auto Serializer<PositionTrackingDBClientRequestPacket>::deserialize(BinaryReader &stream) -> std::expected<PositionTrackingDBClientRequestPacket, std::error_code>
{
    PositionTrackingDBClientRequestPacket out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.action = static_cast<PositionTrackingDBClientRequestPacket::Action>(*v);
    }
    {
        auto v = Serializer<PositionTrackingId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.id = *v;
    }
    return out;
}

}  // namespace bedrock::protocol
