#include <bedrock/protocol/diagnostics.h>

namespace bedrock::protocol {


void Serializer<v924::MemoryCategoryCounter>::serialize(BinaryWriter &stream, const v924::MemoryCategoryCounter &value)
{
    stream.write<std::uint8_t>(value.category);
    stream.write<std::uint64_t>(value.current_bytes);
}

auto Serializer<v924::MemoryCategoryCounter>::deserialize(BinaryReader &stream) -> std::expected<v924::MemoryCategoryCounter, std::error_code>
{
    v924::MemoryCategoryCounter out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.category = static_cast<v898::MemoryCategory>(*v);
    }
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.current_bytes = static_cast<std::uint64_t>(*v);
    }
    return out;
}

void Serializer<v944::MemoryCategoryCounter>::serialize(BinaryWriter &stream, const v944::MemoryCategoryCounter &value)
{
    stream.write<std::uint8_t>(value.category);
    stream.write<std::uint64_t>(value.current_bytes);
}

auto Serializer<v944::MemoryCategoryCounter>::deserialize(BinaryReader &stream) -> std::expected<v944::MemoryCategoryCounter, std::error_code>
{
    v944::MemoryCategoryCounter out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.category = static_cast<v944::MemoryCategory>(*v);
    }
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.current_bytes = static_cast<std::uint64_t>(*v);
    }
    return out;
}

void Serializer<v975::MemoryCategoryCounter>::serialize(BinaryWriter &stream, const v975::MemoryCategoryCounter &value)
{
    stream.write<std::uint8_t>(value.category);
    stream.write<std::uint64_t>(value.current_bytes);
}

auto Serializer<v975::MemoryCategoryCounter>::deserialize(BinaryReader &stream) -> std::expected<v975::MemoryCategoryCounter, std::error_code>
{
    v975::MemoryCategoryCounter out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.category = static_cast<v975::MemoryCategory>(*v);
    }
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.current_bytes = static_cast<std::uint64_t>(*v);
    }
    return out;
}

void Serializer<v2168::MemoryCategoryCounter>::serialize(BinaryWriter &stream, const v2168::MemoryCategoryCounter &value)
{
    stream.write<std::uint8_t>(value.category);
    stream.write<std::uint64_t>(value.current_bytes);
}

auto Serializer<v2168::MemoryCategoryCounter>::deserialize(BinaryReader &stream) -> std::expected<v2168::MemoryCategoryCounter, std::error_code>
{
    v2168::MemoryCategoryCounter out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.category = static_cast<v2168::MemoryCategory>(*v);
    }
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.current_bytes = static_cast<std::uint64_t>(*v);
    }
    return out;
}

void Serializer<v2193::MemoryCategoryCounter>::serialize(BinaryWriter &stream, const v2193::MemoryCategoryCounter &value)
{
    stream.write<std::uint8_t>(value.category);
    stream.write<std::uint64_t>(value.current_bytes);
}

auto Serializer<v2193::MemoryCategoryCounter>::deserialize(BinaryReader &stream) -> std::expected<v2193::MemoryCategoryCounter, std::error_code>
{
    v2193::MemoryCategoryCounter out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.category = static_cast<v2193::MemoryCategory>(*v);
    }
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.current_bytes = static_cast<std::uint64_t>(*v);
    }
    return out;
}

void Serializer<v2225::MemoryCategoryCounter>::serialize(BinaryWriter &stream, const v2225::MemoryCategoryCounter &value)
{
    stream.write<std::uint8_t>(value.category);
    stream.write<std::uint64_t>(value.current_bytes);
}

auto Serializer<v2225::MemoryCategoryCounter>::deserialize(BinaryReader &stream) -> std::expected<v2225::MemoryCategoryCounter, std::error_code>
{
    v2225::MemoryCategoryCounter out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.category = static_cast<v2225::MemoryCategory>(*v);
    }
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.current_bytes = static_cast<std::uint64_t>(*v);
    }
    return out;
}

void Serializer<base::EntityDiagnosticTimingInfo>::serialize(BinaryWriter &stream, const base::EntityDiagnosticTimingInfo &value)
{
    stream.write(value.display_name);
    stream.write(value.entity);
    stream.write<std::uint64_t>(value.time_in_ns);
    stream.write<std::uint8_t>(value.percent_of_total);
}

auto Serializer<base::EntityDiagnosticTimingInfo>::deserialize(BinaryReader &stream) -> std::expected<base::EntityDiagnosticTimingInfo, std::error_code>
{
    base::EntityDiagnosticTimingInfo out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.display_name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.entity = *v;
    }
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.time_in_ns = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.percent_of_total = static_cast<std::uint8_t>(*v);
    }
    return out;
}

void Serializer<v2193::EntityDiagnosticTimingInfo>::serialize(BinaryWriter &stream, const v2193::EntityDiagnosticTimingInfo &value)
{
    stream.write(value.display_name);
    stream.write(value.entity);
    stream.write<std::uint64_t>(value.time_in_ns);
    stream.write<std::uint8_t>(value.percent_of_total);
    stream.write<bool>(value.position.has_value());
    if (value.position.has_value()) {
        Serializer<Vec3>::serialize(stream, (*value.position));
    }
    stream.write<bool>(value.dimension.has_value());
    if (value.dimension.has_value()) {
        stream.write((*value.dimension));
    }
}

auto Serializer<v2193::EntityDiagnosticTimingInfo>::deserialize(BinaryReader &stream) -> std::expected<v2193::EntityDiagnosticTimingInfo, std::error_code>
{
    v2193::EntityDiagnosticTimingInfo out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.display_name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.entity = *v;
    }
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.time_in_ns = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.percent_of_total = static_cast<std::uint8_t>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            Vec3 staged{};
            auto v = Serializer<Vec3>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.position = std::move(staged);
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
            out.dimension = std::move(staged);
        }
    }
    return out;
}

void Serializer<SystemDiagnosticTimingInfo>::serialize(BinaryWriter &stream, const SystemDiagnosticTimingInfo &value)
{
    stream.write(value.display_name);
    stream.write<std::uint64_t>(value.system_index);
    stream.write<std::uint64_t>(value.time_in_ns);
    stream.write<std::uint8_t>(value.percent_of_total);
}

auto Serializer<SystemDiagnosticTimingInfo>::deserialize(BinaryReader &stream) -> std::expected<SystemDiagnosticTimingInfo, std::error_code>
{
    SystemDiagnosticTimingInfo out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.display_name = *v;
    }
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.system_index = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.time_in_ns = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.percent_of_total = static_cast<std::uint8_t>(*v);
    }
    return out;
}

void Serializer<v2168::SystemCategory>::serialize(BinaryWriter &stream, const v2168::SystemCategory &value)
{
    stream.write(value.category_name);
    stream.write<std::uint64_t>(value.system_index);
}

auto Serializer<v2168::SystemCategory>::deserialize(BinaryReader &stream) -> std::expected<v2168::SystemCategory, std::error_code>
{
    v2168::SystemCategory out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.category_name = *v;
    }
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.system_index = static_cast<std::uint64_t>(*v);
    }
    return out;
}

void Serializer<ScopeDataSummary>::serialize(BinaryWriter &stream, const ScopeDataSummary &value)
{
    stream.write(value.label);
    stream.write(value.indentation);
    stream.write<std::uint64_t>(value.total_high_cost_ns);
    stream.write<std::uint64_t>(value.total_mid_cost_ns);
    stream.write<std::uint64_t>(value.total_low_cost_ns);
}

auto Serializer<ScopeDataSummary>::deserialize(BinaryReader &stream) -> std::expected<ScopeDataSummary, std::error_code>
{
    ScopeDataSummary out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.label = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.indentation = *v;
    }
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.total_high_cost_ns = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.total_mid_cost_ns = static_cast<std::uint64_t>(*v);
    }
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.total_low_cost_ns = static_cast<std::uint64_t>(*v);
    }
    return out;
}

void Serializer<base::ServerboundDiagnosticsPacket>::serialize(BinaryWriter &stream, const base::ServerboundDiagnosticsPacket &value)
{
    stream.write<float>(value.avg_fps);
    stream.write<float>(value.avg_server_sim_tick_time_ms);
    stream.write<float>(value.avg_client_sim_tick_time_ms);
    stream.write<float>(value.avg_begin_frame_time_ms);
    stream.write<float>(value.avg_input_time_ms);
    stream.write<float>(value.avg_render_time_ms);
    stream.write<float>(value.avg_end_frame_time_ms);
    stream.write<float>(value.avg_remainder_time_percent);
    stream.write<float>(value.avg_unaccounted_time_percent);
}

auto Serializer<base::ServerboundDiagnosticsPacket>::deserialize(BinaryReader &stream) -> std::expected<base::ServerboundDiagnosticsPacket, std::error_code>
{
    base::ServerboundDiagnosticsPacket out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_fps = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_server_sim_tick_time_ms = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_client_sim_tick_time_ms = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_begin_frame_time_ms = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_input_time_ms = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_render_time_ms = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_end_frame_time_ms = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_remainder_time_percent = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_unaccounted_time_percent = static_cast<float>(*v);
    }
    return out;
}

void Serializer<v924::ServerboundDiagnosticsPacket>::serialize(BinaryWriter &stream, const v924::ServerboundDiagnosticsPacket &value)
{
    stream.write<float>(value.avg_fps);
    stream.write<float>(value.avg_server_sim_tick_time_ms);
    stream.write<float>(value.avg_client_sim_tick_time_ms);
    stream.write<float>(value.avg_begin_frame_time_ms);
    stream.write<float>(value.avg_input_time_ms);
    stream.write<float>(value.avg_render_time_ms);
    stream.write<float>(value.avg_end_frame_time_ms);
    stream.write<float>(value.avg_remainder_time_percent);
    stream.write<float>(value.avg_unaccounted_time_percent);
    stream.writeVarInt<std::uint32_t>(value.category_counters.size());
    for (const auto &e0 : value.category_counters) {
        Serializer<v924::MemoryCategoryCounter>::serialize(stream, e0);
    }
}

auto Serializer<v924::ServerboundDiagnosticsPacket>::deserialize(BinaryReader &stream) -> std::expected<v924::ServerboundDiagnosticsPacket, std::error_code>
{
    v924::ServerboundDiagnosticsPacket out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_fps = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_server_sim_tick_time_ms = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_client_sim_tick_time_ms = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_begin_frame_time_ms = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_input_time_ms = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_render_time_ms = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_end_frame_time_ms = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_remainder_time_percent = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_unaccounted_time_percent = static_cast<float>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.category_counters.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.category_counters.emplace_back();
            auto v = Serializer<v924::MemoryCategoryCounter>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.category_counters.back() = *v;
        }
    }
    return out;
}

void Serializer<v944::ServerboundDiagnosticsPacket>::serialize(BinaryWriter &stream, const v944::ServerboundDiagnosticsPacket &value)
{
    stream.write<float>(value.avg_fps);
    stream.write<float>(value.avg_server_sim_tick_time_ms);
    stream.write<float>(value.avg_client_sim_tick_time_ms);
    stream.write<float>(value.avg_begin_frame_time_ms);
    stream.write<float>(value.avg_input_time_ms);
    stream.write<float>(value.avg_render_time_ms);
    stream.write<float>(value.avg_end_frame_time_ms);
    stream.write<float>(value.avg_remainder_time_percent);
    stream.write<float>(value.avg_unaccounted_time_percent);
    stream.writeVarInt<std::uint32_t>(value.category_counters.size());
    for (const auto &e0 : value.category_counters) {
        Serializer<v944::MemoryCategoryCounter>::serialize(stream, e0);
    }
}

auto Serializer<v944::ServerboundDiagnosticsPacket>::deserialize(BinaryReader &stream) -> std::expected<v944::ServerboundDiagnosticsPacket, std::error_code>
{
    v944::ServerboundDiagnosticsPacket out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_fps = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_server_sim_tick_time_ms = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_client_sim_tick_time_ms = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_begin_frame_time_ms = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_input_time_ms = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_render_time_ms = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_end_frame_time_ms = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_remainder_time_percent = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_unaccounted_time_percent = static_cast<float>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.category_counters.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.category_counters.emplace_back();
            auto v = Serializer<v944::MemoryCategoryCounter>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.category_counters.back() = *v;
        }
    }
    return out;
}

void Serializer<v975::ServerboundDiagnosticsPacket>::serialize(BinaryWriter &stream, const v975::ServerboundDiagnosticsPacket &value)
{
    stream.write<float>(value.avg_fps);
    stream.write<float>(value.avg_server_sim_tick_time_ms);
    stream.write<float>(value.avg_client_sim_tick_time_ms);
    stream.write<float>(value.avg_begin_frame_time_ms);
    stream.write<float>(value.avg_input_time_ms);
    stream.write<float>(value.avg_render_time_ms);
    stream.write<float>(value.avg_end_frame_time_ms);
    stream.write<float>(value.avg_remainder_time_percent);
    stream.write<float>(value.avg_unaccounted_time_percent);
    stream.writeVarInt<std::uint32_t>(value.category_counters.size());
    for (const auto &e0 : value.category_counters) {
        Serializer<v975::MemoryCategoryCounter>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.entity_timings.size());
    for (const auto &e0 : value.entity_timings) {
        Serializer<base::EntityDiagnosticTimingInfo>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.system_timings.size());
    for (const auto &e0 : value.system_timings) {
        Serializer<SystemDiagnosticTimingInfo>::serialize(stream, e0);
    }
}

auto Serializer<v975::ServerboundDiagnosticsPacket>::deserialize(BinaryReader &stream) -> std::expected<v975::ServerboundDiagnosticsPacket, std::error_code>
{
    v975::ServerboundDiagnosticsPacket out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_fps = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_server_sim_tick_time_ms = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_client_sim_tick_time_ms = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_begin_frame_time_ms = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_input_time_ms = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_render_time_ms = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_end_frame_time_ms = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_remainder_time_percent = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_unaccounted_time_percent = static_cast<float>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.category_counters.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.category_counters.emplace_back();
            auto v = Serializer<v975::MemoryCategoryCounter>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.category_counters.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.entity_timings.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.entity_timings.emplace_back();
            auto v = Serializer<base::EntityDiagnosticTimingInfo>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.entity_timings.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.system_timings.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.system_timings.emplace_back();
            auto v = Serializer<SystemDiagnosticTimingInfo>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.system_timings.back() = *v;
        }
    }
    return out;
}

void Serializer<v1001::ServerboundDiagnosticsPacket>::serialize(BinaryWriter &stream, const v1001::ServerboundDiagnosticsPacket &value)
{
    stream.write<float>(value.avg_fps);
    stream.write<float>(value.avg_server_sim_tick_time_ms);
    stream.write<float>(value.avg_client_sim_tick_time_ms);
    stream.write<float>(value.avg_begin_frame_time_ms);
    stream.write<float>(value.avg_input_time_ms);
    stream.write<float>(value.avg_render_time_ms);
    stream.write<float>(value.avg_end_frame_time_ms);
    stream.write<float>(value.avg_remainder_time_percent);
    stream.write<float>(value.avg_unaccounted_time_percent);
    stream.writeVarInt<std::uint32_t>(value.category_counters.size());
    for (const auto &e0 : value.category_counters) {
        Serializer<v975::MemoryCategoryCounter>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.entity_timings.size());
    for (const auto &e0 : value.entity_timings) {
        Serializer<base::EntityDiagnosticTimingInfo>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.system_timings.size());
    for (const auto &e0 : value.system_timings) {
        Serializer<SystemDiagnosticTimingInfo>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.whisker_data.size());
    for (const auto &e0 : value.whisker_data) {
        Serializer<ScopeDataSummary>::serialize(stream, e0);
    }
}

auto Serializer<v1001::ServerboundDiagnosticsPacket>::deserialize(BinaryReader &stream) -> std::expected<v1001::ServerboundDiagnosticsPacket, std::error_code>
{
    v1001::ServerboundDiagnosticsPacket out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_fps = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_server_sim_tick_time_ms = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_client_sim_tick_time_ms = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_begin_frame_time_ms = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_input_time_ms = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_render_time_ms = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_end_frame_time_ms = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_remainder_time_percent = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_unaccounted_time_percent = static_cast<float>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.category_counters.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.category_counters.emplace_back();
            auto v = Serializer<v975::MemoryCategoryCounter>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.category_counters.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.entity_timings.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.entity_timings.emplace_back();
            auto v = Serializer<base::EntityDiagnosticTimingInfo>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.entity_timings.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.system_timings.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.system_timings.emplace_back();
            auto v = Serializer<SystemDiagnosticTimingInfo>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.system_timings.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.whisker_data.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.whisker_data.emplace_back();
            auto v = Serializer<ScopeDataSummary>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.whisker_data.back() = *v;
        }
    }
    return out;
}

void Serializer<v2168::ServerboundDiagnosticsPacket>::serialize(BinaryWriter &stream, const v2168::ServerboundDiagnosticsPacket &value)
{
    stream.write<float>(value.avg_fps);
    stream.write<float>(value.avg_server_sim_tick_time_ms);
    stream.write<float>(value.avg_client_sim_tick_time_ms);
    stream.write<float>(value.avg_begin_frame_time_ms);
    stream.write<float>(value.avg_input_time_ms);
    stream.write<float>(value.avg_render_time_ms);
    stream.write<float>(value.avg_end_frame_time_ms);
    stream.write<float>(value.avg_remainder_time_percent);
    stream.write<float>(value.avg_unaccounted_time_percent);
    stream.writeVarInt<std::uint32_t>(value.category_counters.size());
    for (const auto &e0 : value.category_counters) {
        Serializer<v2168::MemoryCategoryCounter>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.entity_timings.size());
    for (const auto &e0 : value.entity_timings) {
        Serializer<base::EntityDiagnosticTimingInfo>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.system_timings.size());
    for (const auto &e0 : value.system_timings) {
        Serializer<SystemDiagnosticTimingInfo>::serialize(stream, e0);
    }
    stream.write<bool>(value.system_categories.has_value());
    if (value.system_categories.has_value()) {
        stream.writeVarInt<std::uint32_t>((*value.system_categories).size());
        for (const auto &e0 : (*value.system_categories)) {
            Serializer<v2168::SystemCategory>::serialize(stream, e0);
        }
    }
    stream.writeVarInt<std::uint32_t>(value.whisker_data.size());
    for (const auto &e0 : value.whisker_data) {
        Serializer<ScopeDataSummary>::serialize(stream, e0);
    }
}

auto Serializer<v2168::ServerboundDiagnosticsPacket>::deserialize(BinaryReader &stream) -> std::expected<v2168::ServerboundDiagnosticsPacket, std::error_code>
{
    v2168::ServerboundDiagnosticsPacket out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_fps = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_server_sim_tick_time_ms = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_client_sim_tick_time_ms = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_begin_frame_time_ms = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_input_time_ms = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_render_time_ms = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_end_frame_time_ms = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_remainder_time_percent = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_unaccounted_time_percent = static_cast<float>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.category_counters.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.category_counters.emplace_back();
            auto v = Serializer<v2168::MemoryCategoryCounter>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.category_counters.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.entity_timings.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.entity_timings.emplace_back();
            auto v = Serializer<base::EntityDiagnosticTimingInfo>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.entity_timings.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.system_timings.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.system_timings.emplace_back();
            auto v = Serializer<SystemDiagnosticTimingInfo>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.system_timings.back() = *v;
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::vector<v2168::SystemCategory> staged{};
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            staged.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                staged.emplace_back();
                auto v = Serializer<v2168::SystemCategory>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                staged.back() = *v;
            }
            out.system_categories = std::move(staged);
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.whisker_data.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.whisker_data.emplace_back();
            auto v = Serializer<ScopeDataSummary>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.whisker_data.back() = *v;
        }
    }
    return out;
}

void Serializer<v2193::ServerboundDiagnosticsPacket>::serialize(BinaryWriter &stream, const v2193::ServerboundDiagnosticsPacket &value)
{
    stream.write<float>(value.avg_fps);
    stream.write<float>(value.avg_server_sim_tick_time_ms);
    stream.write<float>(value.avg_client_sim_tick_time_ms);
    stream.write<float>(value.avg_begin_frame_time_ms);
    stream.write<float>(value.avg_input_time_ms);
    stream.write<float>(value.avg_render_time_ms);
    stream.write<float>(value.avg_end_frame_time_ms);
    stream.write<float>(value.avg_remainder_time_percent);
    stream.write<float>(value.avg_unaccounted_time_percent);
    stream.writeVarInt<std::uint32_t>(value.category_counters.size());
    for (const auto &e0 : value.category_counters) {
        Serializer<v2193::MemoryCategoryCounter>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.entity_timings.size());
    for (const auto &e0 : value.entity_timings) {
        Serializer<v2193::EntityDiagnosticTimingInfo>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.system_timings.size());
    for (const auto &e0 : value.system_timings) {
        Serializer<SystemDiagnosticTimingInfo>::serialize(stream, e0);
    }
    stream.write<bool>(value.system_categories.has_value());
    if (value.system_categories.has_value()) {
        stream.writeVarInt<std::uint32_t>((*value.system_categories).size());
        for (const auto &e0 : (*value.system_categories)) {
            Serializer<v2168::SystemCategory>::serialize(stream, e0);
        }
    }
    stream.writeVarInt<std::uint32_t>(value.whisker_data.size());
    for (const auto &e0 : value.whisker_data) {
        Serializer<ScopeDataSummary>::serialize(stream, e0);
    }
}

auto Serializer<v2193::ServerboundDiagnosticsPacket>::deserialize(BinaryReader &stream) -> std::expected<v2193::ServerboundDiagnosticsPacket, std::error_code>
{
    v2193::ServerboundDiagnosticsPacket out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_fps = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_server_sim_tick_time_ms = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_client_sim_tick_time_ms = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_begin_frame_time_ms = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_input_time_ms = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_render_time_ms = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_end_frame_time_ms = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_remainder_time_percent = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_unaccounted_time_percent = static_cast<float>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.category_counters.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.category_counters.emplace_back();
            auto v = Serializer<v2193::MemoryCategoryCounter>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.category_counters.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.entity_timings.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.entity_timings.emplace_back();
            auto v = Serializer<v2193::EntityDiagnosticTimingInfo>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.entity_timings.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.system_timings.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.system_timings.emplace_back();
            auto v = Serializer<SystemDiagnosticTimingInfo>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.system_timings.back() = *v;
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::vector<v2168::SystemCategory> staged{};
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            staged.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                staged.emplace_back();
                auto v = Serializer<v2168::SystemCategory>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                staged.back() = *v;
            }
            out.system_categories = std::move(staged);
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.whisker_data.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.whisker_data.emplace_back();
            auto v = Serializer<ScopeDataSummary>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.whisker_data.back() = *v;
        }
    }
    return out;
}

void Serializer<v2225::ServerboundDiagnosticsPacket>::serialize(BinaryWriter &stream, const v2225::ServerboundDiagnosticsPacket &value)
{
    stream.write<float>(value.avg_fps);
    stream.write<float>(value.avg_server_sim_tick_time_ms);
    stream.write<float>(value.avg_client_sim_tick_time_ms);
    stream.write<float>(value.avg_begin_frame_time_ms);
    stream.write<float>(value.avg_input_time_ms);
    stream.write<float>(value.avg_render_time_ms);
    stream.write<float>(value.avg_end_frame_time_ms);
    stream.write<float>(value.avg_remainder_time_percent);
    stream.write<float>(value.avg_unaccounted_time_percent);
    stream.writeVarInt<std::uint32_t>(value.category_counters.size());
    for (const auto &e0 : value.category_counters) {
        Serializer<v2225::MemoryCategoryCounter>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.entity_timings.size());
    for (const auto &e0 : value.entity_timings) {
        Serializer<v2193::EntityDiagnosticTimingInfo>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.system_timings.size());
    for (const auto &e0 : value.system_timings) {
        Serializer<SystemDiagnosticTimingInfo>::serialize(stream, e0);
    }
    stream.write<bool>(value.system_categories.has_value());
    if (value.system_categories.has_value()) {
        stream.writeVarInt<std::uint32_t>((*value.system_categories).size());
        for (const auto &e0 : (*value.system_categories)) {
            Serializer<v2168::SystemCategory>::serialize(stream, e0);
        }
    }
    stream.writeVarInt<std::uint32_t>(value.whisker_data.size());
    for (const auto &e0 : value.whisker_data) {
        Serializer<ScopeDataSummary>::serialize(stream, e0);
    }
}

auto Serializer<v2225::ServerboundDiagnosticsPacket>::deserialize(BinaryReader &stream) -> std::expected<v2225::ServerboundDiagnosticsPacket, std::error_code>
{
    v2225::ServerboundDiagnosticsPacket out;
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_fps = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_server_sim_tick_time_ms = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_client_sim_tick_time_ms = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_begin_frame_time_ms = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_input_time_ms = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_render_time_ms = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_end_frame_time_ms = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_remainder_time_percent = static_cast<float>(*v);
    }
    {
        auto v = stream.read<float>();
        if (!v) return std::unexpected(v.error());
        out.avg_unaccounted_time_percent = static_cast<float>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.category_counters.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.category_counters.emplace_back();
            auto v = Serializer<v2225::MemoryCategoryCounter>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.category_counters.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.entity_timings.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.entity_timings.emplace_back();
            auto v = Serializer<v2193::EntityDiagnosticTimingInfo>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.entity_timings.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.system_timings.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.system_timings.emplace_back();
            auto v = Serializer<SystemDiagnosticTimingInfo>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.system_timings.back() = *v;
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::vector<v2168::SystemCategory> staged{};
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            staged.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                staged.emplace_back();
                auto v = Serializer<v2168::SystemCategory>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                staged.back() = *v;
            }
            out.system_categories = std::move(staged);
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.whisker_data.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.whisker_data.emplace_back();
            auto v = Serializer<ScopeDataSummary>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.whisker_data.back() = *v;
        }
    }
    return out;
}

void Serializer<base::EditorNetworkPacket>::serialize(BinaryWriter &stream, const base::EditorNetworkPacket &value)
{
    stream.write<bool>(value.route_to_manager);
    Serializer<CompoundTag>::serialize(stream, value.payload);
}

auto Serializer<base::EditorNetworkPacket>::deserialize(BinaryReader &stream) -> std::expected<base::EditorNetworkPacket, std::error_code>
{
    base::EditorNetworkPacket out;
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.route_to_manager = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<CompoundTag>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.payload = *v;
    }
    return out;
}

void Serializer<v944::EditorNetworkPacket>::serialize(BinaryWriter &stream, const v944::EditorNetworkPacket &value)
{
    stream.write<bool>(value.route_to_manager);
    stream.write(value.raw_variant_name);
    stream.write(value.raw_variant_data);
}

auto Serializer<v944::EditorNetworkPacket>::deserialize(BinaryReader &stream) -> std::expected<v944::EditorNetworkPacket, std::error_code>
{
    v944::EditorNetworkPacket out;
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.route_to_manager = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.raw_variant_name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.raw_variant_data = *v;
    }
    return out;
}

void Serializer<DebugInfoPacket>::serialize(BinaryWriter &stream, const DebugInfoPacket &value)
{
    stream.writeVarInt<std::int64_t>(value.actor_id);
    stream.write(value.data);
}

auto Serializer<DebugInfoPacket>::deserialize(BinaryReader &stream) -> std::expected<DebugInfoPacket, std::error_code>
{
    DebugInfoPacket out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.actor_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.data = *v;
    }
    return out;
}

void Serializer<ClientboundDebugRendererPacket::PayloadType>::serialize(BinaryWriter &stream, ClientboundDebugRendererPacket::PayloadType value)
{
    stream.write(enum_name(value));
}

auto Serializer<ClientboundDebugRendererPacket::PayloadType>::deserialize(BinaryReader &stream) -> std::expected<ClientboundDebugRendererPacket::PayloadType, std::error_code>
{
    auto v = stream.read<std::string>();
    if (!v) return std::unexpected(v.error());
    const auto value = enum_cast<ClientboundDebugRendererPacket::PayloadType>(*v);
    if (!value) return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
    return *value;
}

void Serializer<ClientboundDebugRendererPacket::DebugMarkerData>::serialize(BinaryWriter &stream, const ClientboundDebugRendererPacket::DebugMarkerData &value)
{
    stream.write(value.text);
    Serializer<Vec3>::serialize(stream, value.position);
    stream.write<std::int32_t>(value.color);
    stream.write<std::uint64_t>(value.duration_ms);
}

auto Serializer<ClientboundDebugRendererPacket::DebugMarkerData>::deserialize(BinaryReader &stream) -> std::expected<ClientboundDebugRendererPacket::DebugMarkerData, std::error_code>
{
    ClientboundDebugRendererPacket::DebugMarkerData out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.text = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.position = *v;
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.color = static_cast<Color>(*v);
    }
    {
        auto v = stream.read<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.duration_ms = static_cast<std::uint64_t>(*v);
    }
    return out;
}

void Serializer<ClientboundDebugRendererPacket>::serialize(BinaryWriter &stream, const ClientboundDebugRendererPacket &value)
{
    Serializer<ClientboundDebugRendererPacket::PayloadType>::serialize(stream, value.type);
    stream.write<bool>(value.debug_marker_data.has_value());
    if (value.debug_marker_data.has_value()) {
        Serializer<ClientboundDebugRendererPacket::DebugMarkerData>::serialize(stream, (*value.debug_marker_data));
    }
}

auto Serializer<ClientboundDebugRendererPacket>::deserialize(BinaryReader &stream) -> std::expected<ClientboundDebugRendererPacket, std::error_code>
{
    ClientboundDebugRendererPacket out;
    {
        auto v = Serializer<ClientboundDebugRendererPacket::PayloadType>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.type = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            ClientboundDebugRendererPacket::DebugMarkerData staged{};
            auto v = Serializer<ClientboundDebugRendererPacket::DebugMarkerData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.debug_marker_data = std::move(staged);
        }
    }
    return out;
}

}  // namespace bedrock::protocol
