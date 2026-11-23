#include <bedrock/protocol/command.h>

namespace bedrock::protocol {


void Serializer<CommandPermissionLevel>::serialize(BinaryWriter &stream, CommandPermissionLevel value)
{
    stream.write(enum_name(value));
}

auto Serializer<CommandPermissionLevel>::deserialize(BinaryReader &stream) -> std::expected<CommandPermissionLevel, std::error_code>
{
    auto v = stream.read<std::string>();
    if (!v) return std::unexpected(v.error());
    const auto value = enum_cast<CommandPermissionLevel>(*v);
    if (!value) return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
    return *value;
}

void Serializer<SettingsCommandPacket>::serialize(BinaryWriter &stream, const SettingsCommandPacket &value)
{
    stream.write(value.command_string);
    stream.write<bool>(value.suppress_output);
}

auto Serializer<SettingsCommandPacket>::deserialize(BinaryReader &stream) -> std::expected<SettingsCommandPacket, std::error_code>
{
    SettingsCommandPacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.command_string = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.suppress_output = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<AvailableCommandsPacket::EnumData>::serialize(BinaryWriter &stream, const AvailableCommandsPacket::EnumData &value)
{
    stream.write(value.name);
    stream.writeVarInt<std::uint32_t>(value.values.size());
    for (const auto &e0 : value.values) {
        stream.write<std::uint32_t>(e0);
    }
}

auto Serializer<AvailableCommandsPacket::EnumData>::deserialize(BinaryReader &stream) -> std::expected<AvailableCommandsPacket::EnumData, std::error_code>
{
    AvailableCommandsPacket::EnumData out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.values.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.values.emplace_back();
            auto v = stream.read<std::uint32_t>();
            if (!v) return std::unexpected(v.error());
            out.values.back() = static_cast<std::uint32_t>(*v);
        }
    }
    return out;
}

void Serializer<AvailableCommandsPacket::ChainedSubcommandRelationship>::serialize(BinaryWriter &stream, const AvailableCommandsPacket::ChainedSubcommandRelationship &value)
{
    stream.writeVarInt<std::uint32_t>(value.sub_command_first_value);
    stream.writeVarInt<std::uint32_t>(value.sub_command_second_value);
}

auto Serializer<AvailableCommandsPacket::ChainedSubcommandRelationship>::deserialize(BinaryReader &stream) -> std::expected<AvailableCommandsPacket::ChainedSubcommandRelationship, std::error_code>
{
    AvailableCommandsPacket::ChainedSubcommandRelationship out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.sub_command_first_value = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.sub_command_second_value = static_cast<std::uint32_t>(*v);
    }
    return out;
}

void Serializer<AvailableCommandsPacket::ChainedSubcommandData>::serialize(BinaryWriter &stream, const AvailableCommandsPacket::ChainedSubcommandData &value)
{
    stream.write(value.name);
    stream.writeVarInt<std::uint32_t>(value.values.size());
    for (const auto &e0 : value.values) {
        Serializer<AvailableCommandsPacket::ChainedSubcommandRelationship>::serialize(stream, e0);
    }
}

auto Serializer<AvailableCommandsPacket::ChainedSubcommandData>::deserialize(BinaryReader &stream) -> std::expected<AvailableCommandsPacket::ChainedSubcommandData, std::error_code>
{
    AvailableCommandsPacket::ChainedSubcommandData out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.values.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.values.emplace_back();
            auto v = Serializer<AvailableCommandsPacket::ChainedSubcommandRelationship>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.values.back() = *v;
        }
    }
    return out;
}

void Serializer<AvailableCommandsPacket::SoftEnumData>::serialize(BinaryWriter &stream, const AvailableCommandsPacket::SoftEnumData &value)
{
    stream.write(value.name);
    stream.writeVarInt<std::uint32_t>(value.values.size());
    for (const auto &e0 : value.values) {
        stream.write(e0);
    }
}

auto Serializer<AvailableCommandsPacket::SoftEnumData>::deserialize(BinaryReader &stream) -> std::expected<AvailableCommandsPacket::SoftEnumData, std::error_code>
{
    AvailableCommandsPacket::SoftEnumData out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.values.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.values.emplace_back();
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.values.back() = *v;
        }
    }
    return out;
}

void Serializer<AvailableCommandsPacket::ConstrainedValueData>::serialize(BinaryWriter &stream, const AvailableCommandsPacket::ConstrainedValueData &value)
{
    stream.write<std::uint32_t>(value.enum_value_symbol);
    stream.write<std::uint32_t>(value.enum_symbol);
    stream.writeVarInt<std::uint32_t>(value.constraints.size());
    for (const auto &e0 : value.constraints) {
        stream.write<std::uint8_t>(e0);
    }
}

auto Serializer<AvailableCommandsPacket::ConstrainedValueData>::deserialize(BinaryReader &stream) -> std::expected<AvailableCommandsPacket::ConstrainedValueData, std::error_code>
{
    AvailableCommandsPacket::ConstrainedValueData out;
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.enum_value_symbol = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.enum_symbol = static_cast<std::uint32_t>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.constraints.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.constraints.emplace_back();
            auto v = stream.read<std::uint8_t>();
            if (!v) return std::unexpected(v.error());
            out.constraints.back() = static_cast<std::uint8_t>(*v);
        }
    }
    return out;
}

void Serializer<AvailableCommandsPacket::ParamData>::serialize(BinaryWriter &stream, const AvailableCommandsPacket::ParamData &value)
{
    stream.write(value.name);
    stream.write<std::uint32_t>(value.parse_symbol);
    stream.write<bool>(value.optional);
    stream.write<std::uint8_t>(value.param_options);
}

auto Serializer<AvailableCommandsPacket::ParamData>::deserialize(BinaryReader &stream) -> std::expected<AvailableCommandsPacket::ParamData, std::error_code>
{
    AvailableCommandsPacket::ParamData out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.parse_symbol = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.optional = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.param_options = static_cast<std::uint8_t>(*v);
    }
    return out;
}

void Serializer<AvailableCommandsPacket::OverloadData>::serialize(BinaryWriter &stream, const AvailableCommandsPacket::OverloadData &value)
{
    stream.write<bool>(value.is_chaining);
    stream.writeVarInt<std::uint32_t>(value.params.size());
    for (const auto &e0 : value.params) {
        Serializer<AvailableCommandsPacket::ParamData>::serialize(stream, e0);
    }
}

auto Serializer<AvailableCommandsPacket::OverloadData>::deserialize(BinaryReader &stream) -> std::expected<AvailableCommandsPacket::OverloadData, std::error_code>
{
    AvailableCommandsPacket::OverloadData out;
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_chaining = static_cast<bool>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.params.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.params.emplace_back();
            auto v = Serializer<AvailableCommandsPacket::ParamData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.params.back() = *v;
        }
    }
    return out;
}

void Serializer<AvailableCommandsPacket::CommandData>::serialize(BinaryWriter &stream, const AvailableCommandsPacket::CommandData &value)
{
    stream.write(value.name);
    stream.write(value.description);
    stream.write<std::uint16_t>(value.flags);
    Serializer<CommandPermissionLevel>::serialize(stream, value.permission);
    stream.write<std::int32_t>(value.alias_enum);
    stream.writeVarInt<std::uint32_t>(value.chained_subcommand_indexes.size());
    for (const auto &e0 : value.chained_subcommand_indexes) {
        stream.write<std::uint32_t>(e0);
    }
    stream.writeVarInt<std::uint32_t>(value.overloads.size());
    for (const auto &e0 : value.overloads) {
        Serializer<AvailableCommandsPacket::OverloadData>::serialize(stream, e0);
    }
}

auto Serializer<AvailableCommandsPacket::CommandData>::deserialize(BinaryReader &stream) -> std::expected<AvailableCommandsPacket::CommandData, std::error_code>
{
    AvailableCommandsPacket::CommandData out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.description = *v;
    }
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.flags = static_cast<std::uint16_t>(*v);
    }
    {
        auto v = Serializer<CommandPermissionLevel>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.permission = *v;
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.alias_enum = static_cast<std::int32_t>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.chained_subcommand_indexes.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.chained_subcommand_indexes.emplace_back();
            auto v = stream.read<std::uint32_t>();
            if (!v) return std::unexpected(v.error());
            out.chained_subcommand_indexes.back() = static_cast<std::uint32_t>(*v);
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.overloads.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.overloads.emplace_back();
            auto v = Serializer<AvailableCommandsPacket::OverloadData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.overloads.back() = *v;
        }
    }
    return out;
}

void Serializer<AvailableCommandsPacket>::serialize(BinaryWriter &stream, const AvailableCommandsPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.enum_values.size());
    for (const auto &e0 : value.enum_values) {
        stream.write(e0);
    }
    stream.writeVarInt<std::uint32_t>(value.chained_subcommand_values.size());
    for (const auto &e0 : value.chained_subcommand_values) {
        stream.write(e0);
    }
    stream.writeVarInt<std::uint32_t>(value.postfixes.size());
    for (const auto &e0 : value.postfixes) {
        stream.write(e0);
    }
    stream.writeVarInt<std::uint32_t>(value.enums.size());
    for (const auto &e0 : value.enums) {
        Serializer<AvailableCommandsPacket::EnumData>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.chained_subcommands.size());
    for (const auto &e0 : value.chained_subcommands) {
        Serializer<AvailableCommandsPacket::ChainedSubcommandData>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.commands.size());
    for (const auto &e0 : value.commands) {
        Serializer<AvailableCommandsPacket::CommandData>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.soft_enums.size());
    for (const auto &e0 : value.soft_enums) {
        Serializer<AvailableCommandsPacket::SoftEnumData>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.constraints.size());
    for (const auto &e0 : value.constraints) {
        Serializer<AvailableCommandsPacket::ConstrainedValueData>::serialize(stream, e0);
    }
}

auto Serializer<AvailableCommandsPacket>::deserialize(BinaryReader &stream) -> std::expected<AvailableCommandsPacket, std::error_code>
{
    AvailableCommandsPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.enum_values.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.enum_values.emplace_back();
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.enum_values.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.chained_subcommand_values.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.chained_subcommand_values.emplace_back();
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.chained_subcommand_values.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.postfixes.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.postfixes.emplace_back();
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.postfixes.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.enums.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.enums.emplace_back();
            auto v = Serializer<AvailableCommandsPacket::EnumData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.enums.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.chained_subcommands.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.chained_subcommands.emplace_back();
            auto v = Serializer<AvailableCommandsPacket::ChainedSubcommandData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.chained_subcommands.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.commands.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.commands.emplace_back();
            auto v = Serializer<AvailableCommandsPacket::CommandData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.commands.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.soft_enums.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.soft_enums.emplace_back();
            auto v = Serializer<AvailableCommandsPacket::SoftEnumData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.soft_enums.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.constraints.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.constraints.emplace_back();
            auto v = Serializer<AvailableCommandsPacket::ConstrainedValueData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.constraints.back() = *v;
        }
    }
    return out;
}

void Serializer<base::CommandBlockUpdatePacket::EntityCommandTarget>::serialize(BinaryWriter &stream, const base::CommandBlockUpdatePacket::EntityCommandTarget &value)
{
    stream.writeVarInt<std::uint64_t>(value.entity_id);
}

auto Serializer<base::CommandBlockUpdatePacket::EntityCommandTarget>::deserialize(BinaryReader &stream) -> std::expected<base::CommandBlockUpdatePacket::EntityCommandTarget, std::error_code>
{
    base::CommandBlockUpdatePacket::EntityCommandTarget out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_id = static_cast<ActorRuntimeID>(*v);
    }
    return out;
}

void Serializer<base::CommandBlockUpdatePacket::BlockCommandData>::serialize(BinaryWriter &stream, const base::CommandBlockUpdatePacket::BlockCommandData &value)
{
    Serializer<base::NetworkBlockPosition>::serialize(stream, value.block_pos);
    stream.writeVarInt<std::uint32_t>(value.mode);
    stream.write<bool>(value.redstone_mode);
    stream.write<bool>(value.is_conditional);
}

auto Serializer<base::CommandBlockUpdatePacket::BlockCommandData>::deserialize(BinaryReader &stream) -> std::expected<base::CommandBlockUpdatePacket::BlockCommandData, std::error_code>
{
    base::CommandBlockUpdatePacket::BlockCommandData out;
    {
        auto v = Serializer<base::NetworkBlockPosition>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.block_pos = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.mode = static_cast<CommandBlockMode>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.redstone_mode = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_conditional = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v776::CommandBlockUpdatePacket::BlockCommandData>::serialize(BinaryWriter &stream, const v776::CommandBlockUpdatePacket::BlockCommandData &value)
{
    Serializer<base::NetworkBlockPosition>::serialize(stream, value.block_pos);
    stream.writeVarInt<std::uint32_t>(value.mode);
    stream.write<bool>(value.redstone_mode);
    stream.write<bool>(value.is_conditional);
}

auto Serializer<v776::CommandBlockUpdatePacket::BlockCommandData>::deserialize(BinaryReader &stream) -> std::expected<v776::CommandBlockUpdatePacket::BlockCommandData, std::error_code>
{
    v776::CommandBlockUpdatePacket::BlockCommandData out;
    {
        auto v = Serializer<base::NetworkBlockPosition>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.block_pos = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.mode = static_cast<CommandBlockMode>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.redstone_mode = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_conditional = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v944::CommandBlockUpdatePacket::BlockCommandData>::serialize(BinaryWriter &stream, const v944::CommandBlockUpdatePacket::BlockCommandData &value)
{
    Serializer<BlockPos>::serialize(stream, value.block_pos);
    stream.writeVarInt<std::uint32_t>(value.mode);
    stream.write<bool>(value.redstone_mode);
    stream.write<bool>(value.is_conditional);
}

auto Serializer<v944::CommandBlockUpdatePacket::BlockCommandData>::deserialize(BinaryReader &stream) -> std::expected<v944::CommandBlockUpdatePacket::BlockCommandData, std::error_code>
{
    v944::CommandBlockUpdatePacket::BlockCommandData out;
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.block_pos = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.mode = static_cast<CommandBlockMode>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.redstone_mode = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_conditional = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v2168::CommandBlockUpdatePacket::BlockCommandData>::serialize(BinaryWriter &stream, const v2168::CommandBlockUpdatePacket::BlockCommandData &value)
{
    Serializer<BlockPos>::serialize(stream, value.block_pos);
    stream.writeVarInt<std::uint32_t>(value.mode);
    stream.write<bool>(value.redstone_mode);
    stream.write<bool>(value.is_conditional);
}

auto Serializer<v2168::CommandBlockUpdatePacket::BlockCommandData>::deserialize(BinaryReader &stream) -> std::expected<v2168::CommandBlockUpdatePacket::BlockCommandData, std::error_code>
{
    v2168::CommandBlockUpdatePacket::BlockCommandData out;
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.block_pos = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.mode = static_cast<CommandBlockMode>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.redstone_mode = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_conditional = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<base::CommandBlockUpdatePacket>::serialize(BinaryWriter &stream, const base::CommandBlockUpdatePacket &value)
{
    stream.writeVarInt<std::uint32_t>((value.target).index());
    switch ((value.target).index()) {
        case 0: {
            Serializer<base::CommandBlockUpdatePacket::EntityCommandTarget>::serialize(stream, std::get<0>(value.target));
            break;
        }
        case 1: {
            Serializer<base::CommandBlockUpdatePacket::BlockCommandData>::serialize(stream, std::get<1>(value.target));
            break;
        }
    }
    stream.write(value.command);
    stream.write(value.last_output);
    stream.write(value.name);
    stream.write<bool>(value.track_output);
    stream.write<std::uint32_t>(value.tick_delay);
    stream.write<bool>(value.execute_on_first_tick);
}

auto Serializer<base::CommandBlockUpdatePacket>::deserialize(BinaryReader &stream) -> std::expected<base::CommandBlockUpdatePacket, std::error_code>
{
    base::CommandBlockUpdatePacket out;
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<base::CommandBlockUpdatePacket::EntityCommandTarget, base::CommandBlockUpdatePacket::BlockCommandData> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<base::CommandBlockUpdatePacket::EntityCommandTarget, base::CommandBlockUpdatePacket::BlockCommandData>> alt0{};
                {
                    auto v = Serializer<base::CommandBlockUpdatePacket::EntityCommandTarget>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<base::CommandBlockUpdatePacket::EntityCommandTarget, base::CommandBlockUpdatePacket::BlockCommandData>> alt0{};
                {
                    auto v = Serializer<base::CommandBlockUpdatePacket::BlockCommandData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.target = var0;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.command = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.last_output = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.track_output = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.tick_delay = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.execute_on_first_tick = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v776::CommandBlockUpdatePacket>::serialize(BinaryWriter &stream, const v776::CommandBlockUpdatePacket &value)
{
    stream.writeVarInt<std::uint32_t>((value.target).index());
    switch ((value.target).index()) {
        case 0: {
            Serializer<v776::CommandBlockUpdatePacket::EntityCommandTarget>::serialize(stream, std::get<0>(value.target));
            break;
        }
        case 1: {
            Serializer<v776::CommandBlockUpdatePacket::BlockCommandData>::serialize(stream, std::get<1>(value.target));
            break;
        }
    }
    stream.write(value.command);
    stream.write(value.last_output);
    stream.write(value.name);
    stream.write(value.filtered_name);
    stream.write<bool>(value.track_output);
    stream.write<std::uint32_t>(value.tick_delay);
    stream.write<bool>(value.execute_on_first_tick);
}

auto Serializer<v776::CommandBlockUpdatePacket>::deserialize(BinaryReader &stream) -> std::expected<v776::CommandBlockUpdatePacket, std::error_code>
{
    v776::CommandBlockUpdatePacket out;
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v776::CommandBlockUpdatePacket::EntityCommandTarget, v776::CommandBlockUpdatePacket::BlockCommandData> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v776::CommandBlockUpdatePacket::EntityCommandTarget, v776::CommandBlockUpdatePacket::BlockCommandData>> alt0{};
                {
                    auto v = Serializer<v776::CommandBlockUpdatePacket::EntityCommandTarget>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v776::CommandBlockUpdatePacket::EntityCommandTarget, v776::CommandBlockUpdatePacket::BlockCommandData>> alt0{};
                {
                    auto v = Serializer<v776::CommandBlockUpdatePacket::BlockCommandData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.target = var0;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.command = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.last_output = *v;
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
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.track_output = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.tick_delay = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.execute_on_first_tick = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v944::CommandBlockUpdatePacket>::serialize(BinaryWriter &stream, const v944::CommandBlockUpdatePacket &value)
{
    stream.writeVarInt<std::uint32_t>((value.target).index());
    switch ((value.target).index()) {
        case 0: {
            Serializer<v944::CommandBlockUpdatePacket::EntityCommandTarget>::serialize(stream, std::get<0>(value.target));
            break;
        }
        case 1: {
            Serializer<v944::CommandBlockUpdatePacket::BlockCommandData>::serialize(stream, std::get<1>(value.target));
            break;
        }
    }
    stream.write(value.command);
    stream.write(value.last_output);
    stream.write(value.name);
    stream.write(value.filtered_name);
    stream.write<bool>(value.track_output);
    stream.write<std::uint32_t>(value.tick_delay);
    stream.write<bool>(value.execute_on_first_tick);
}

auto Serializer<v944::CommandBlockUpdatePacket>::deserialize(BinaryReader &stream) -> std::expected<v944::CommandBlockUpdatePacket, std::error_code>
{
    v944::CommandBlockUpdatePacket out;
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v944::CommandBlockUpdatePacket::EntityCommandTarget, v944::CommandBlockUpdatePacket::BlockCommandData> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v944::CommandBlockUpdatePacket::EntityCommandTarget, v944::CommandBlockUpdatePacket::BlockCommandData>> alt0{};
                {
                    auto v = Serializer<v944::CommandBlockUpdatePacket::EntityCommandTarget>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v944::CommandBlockUpdatePacket::EntityCommandTarget, v944::CommandBlockUpdatePacket::BlockCommandData>> alt0{};
                {
                    auto v = Serializer<v944::CommandBlockUpdatePacket::BlockCommandData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.target = var0;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.command = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.last_output = *v;
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
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.track_output = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.tick_delay = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.execute_on_first_tick = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v2168::CommandBlockUpdatePacket>::serialize(BinaryWriter &stream, const v2168::CommandBlockUpdatePacket &value)
{
    stream.writeVarInt<std::uint32_t>((value.target).index());
    switch ((value.target).index()) {
        case 0: {
            Serializer<v2168::CommandBlockUpdatePacket::EntityCommandTarget>::serialize(stream, std::get<0>(value.target));
            break;
        }
        case 1: {
            Serializer<v2168::CommandBlockUpdatePacket::BlockCommandData>::serialize(stream, std::get<1>(value.target));
            break;
        }
    }
    stream.write(value.command);
    stream.write(value.last_output);
    stream.write(value.name);
    stream.write(value.filtered_name);
    stream.write<bool>(value.track_output);
    stream.write<std::int32_t>(value.tick_delay);
    stream.write<bool>(value.execute_on_first_tick);
}

auto Serializer<v2168::CommandBlockUpdatePacket>::deserialize(BinaryReader &stream) -> std::expected<v2168::CommandBlockUpdatePacket, std::error_code>
{
    v2168::CommandBlockUpdatePacket out;
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v2168::CommandBlockUpdatePacket::EntityCommandTarget, v2168::CommandBlockUpdatePacket::BlockCommandData> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v2168::CommandBlockUpdatePacket::EntityCommandTarget, v2168::CommandBlockUpdatePacket::BlockCommandData>> alt0{};
                {
                    auto v = Serializer<v2168::CommandBlockUpdatePacket::EntityCommandTarget>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v2168::CommandBlockUpdatePacket::EntityCommandTarget, v2168::CommandBlockUpdatePacket::BlockCommandData>> alt0{};
                {
                    auto v = Serializer<v2168::CommandBlockUpdatePacket::BlockCommandData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.target = var0;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.command = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.last_output = *v;
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
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.track_output = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.tick_delay = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.execute_on_first_tick = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<CommandOriginType>::serialize(BinaryWriter &stream, CommandOriginType value)
{
    stream.write(enum_name(value));
}

auto Serializer<CommandOriginType>::deserialize(BinaryReader &stream) -> std::expected<CommandOriginType, std::error_code>
{
    auto v = stream.read<std::string>();
    if (!v) return std::unexpected(v.error());
    const auto value = enum_cast<CommandOriginType>(*v);
    if (!value) return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
    return *value;
}

void Serializer<CommandOriginData>::serialize(BinaryWriter &stream, const CommandOriginData &value)
{
    Serializer<CommandOriginType>::serialize(stream, value.type);
    Serializer<UUID>::serialize(stream, value.uuid);
    stream.write(value.request_id);
    stream.write<std::int64_t>(value.player_id);
}

auto Serializer<CommandOriginData>::deserialize(BinaryReader &stream) -> std::expected<CommandOriginData, std::error_code>
{
    CommandOriginData out;
    {
        auto v = Serializer<CommandOriginType>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.type = *v;
    }
    {
        auto v = Serializer<UUID>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.uuid = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.request_id = *v;
    }
    {
        auto v = stream.read<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.player_id = static_cast<ActorUniqueID>(*v);
    }
    return out;
}

void Serializer<base::CurrentCmdVersion>::serialize(BinaryWriter &stream, base::CurrentCmdVersion value)
{
    stream.write(enum_name(value));
}

auto Serializer<base::CurrentCmdVersion>::deserialize(BinaryReader &stream) -> std::expected<base::CurrentCmdVersion, std::error_code>
{
    auto v = stream.read<std::string>();
    if (!v) return std::unexpected(v.error());
    const auto value = enum_cast<base::CurrentCmdVersion>(*v);
    if (!value) return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
    return *value;
}

void Serializer<v786::CurrentCmdVersion>::serialize(BinaryWriter &stream, v786::CurrentCmdVersion value)
{
    stream.write(enum_name(value));
}

auto Serializer<v786::CurrentCmdVersion>::deserialize(BinaryReader &stream) -> std::expected<v786::CurrentCmdVersion, std::error_code>
{
    auto v = stream.read<std::string>();
    if (!v) return std::unexpected(v.error());
    const auto value = enum_cast<v786::CurrentCmdVersion>(*v);
    if (!value) return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
    return *value;
}

void Serializer<v818::CurrentCmdVersion>::serialize(BinaryWriter &stream, v818::CurrentCmdVersion value)
{
    stream.write(enum_name(value));
}

auto Serializer<v818::CurrentCmdVersion>::deserialize(BinaryReader &stream) -> std::expected<v818::CurrentCmdVersion, std::error_code>
{
    auto v = stream.read<std::string>();
    if (!v) return std::unexpected(v.error());
    const auto value = enum_cast<v818::CurrentCmdVersion>(*v);
    if (!value) return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
    return *value;
}

void Serializer<v898::CurrentCmdVersion>::serialize(BinaryWriter &stream, v898::CurrentCmdVersion value)
{
    stream.write(enum_name(value));
}

auto Serializer<v898::CurrentCmdVersion>::deserialize(BinaryReader &stream) -> std::expected<v898::CurrentCmdVersion, std::error_code>
{
    auto v = stream.read<std::string>();
    if (!v) return std::unexpected(v.error());
    const auto value = enum_cast<v898::CurrentCmdVersion>(*v);
    if (!value) return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
    return *value;
}

void Serializer<v975::CurrentCmdVersion>::serialize(BinaryWriter &stream, v975::CurrentCmdVersion value)
{
    stream.write(enum_name(value));
}

auto Serializer<v975::CurrentCmdVersion>::deserialize(BinaryReader &stream) -> std::expected<v975::CurrentCmdVersion, std::error_code>
{
    auto v = stream.read<std::string>();
    if (!v) return std::unexpected(v.error());
    const auto value = enum_cast<v975::CurrentCmdVersion>(*v);
    if (!value) return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
    return *value;
}

void Serializer<v1001::CurrentCmdVersion>::serialize(BinaryWriter &stream, v1001::CurrentCmdVersion value)
{
    stream.write(enum_name(value));
}

auto Serializer<v1001::CurrentCmdVersion>::deserialize(BinaryReader &stream) -> std::expected<v1001::CurrentCmdVersion, std::error_code>
{
    auto v = stream.read<std::string>();
    if (!v) return std::unexpected(v.error());
    const auto value = enum_cast<v1001::CurrentCmdVersion>(*v);
    if (!value) return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
    return *value;
}

void Serializer<v2168::CurrentCmdVersion>::serialize(BinaryWriter &stream, v2168::CurrentCmdVersion value)
{
    stream.write(enum_name(value));
}

auto Serializer<v2168::CurrentCmdVersion>::deserialize(BinaryReader &stream) -> std::expected<v2168::CurrentCmdVersion, std::error_code>
{
    auto v = stream.read<std::string>();
    if (!v) return std::unexpected(v.error());
    const auto value = enum_cast<v2168::CurrentCmdVersion>(*v);
    if (!value) return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
    return *value;
}

void Serializer<v2193::CurrentCmdVersion>::serialize(BinaryWriter &stream, v2193::CurrentCmdVersion value)
{
    stream.write(enum_name(value));
}

auto Serializer<v2193::CurrentCmdVersion>::deserialize(BinaryReader &stream) -> std::expected<v2193::CurrentCmdVersion, std::error_code>
{
    auto v = stream.read<std::string>();
    if (!v) return std::unexpected(v.error());
    const auto value = enum_cast<v2193::CurrentCmdVersion>(*v);
    if (!value) return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
    return *value;
}

void Serializer<v2225::CurrentCmdVersion>::serialize(BinaryWriter &stream, v2225::CurrentCmdVersion value)
{
    stream.write(enum_name(value));
}

auto Serializer<v2225::CurrentCmdVersion>::deserialize(BinaryReader &stream) -> std::expected<v2225::CurrentCmdVersion, std::error_code>
{
    auto v = stream.read<std::string>();
    if (!v) return std::unexpected(v.error());
    const auto value = enum_cast<v2225::CurrentCmdVersion>(*v);
    if (!value) return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
    return *value;
}

void Serializer<base::CommandRequestPacket>::serialize(BinaryWriter &stream, const base::CommandRequestPacket &value)
{
    stream.write(value.command);
    Serializer<CommandOriginData>::serialize(stream, value.origin);
    stream.write<bool>(value.internal_source);
    Serializer<base::CurrentCmdVersion>::serialize(stream, value.version);
}

auto Serializer<base::CommandRequestPacket>::deserialize(BinaryReader &stream) -> std::expected<base::CommandRequestPacket, std::error_code>
{
    base::CommandRequestPacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.command = *v;
    }
    {
        auto v = Serializer<CommandOriginData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.origin = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.internal_source = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<base::CurrentCmdVersion>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.version = *v;
    }
    return out;
}

void Serializer<v786::CommandRequestPacket>::serialize(BinaryWriter &stream, const v786::CommandRequestPacket &value)
{
    stream.write(value.command);
    Serializer<CommandOriginData>::serialize(stream, value.origin);
    stream.write<bool>(value.internal_source);
    Serializer<v786::CurrentCmdVersion>::serialize(stream, value.version);
}

auto Serializer<v786::CommandRequestPacket>::deserialize(BinaryReader &stream) -> std::expected<v786::CommandRequestPacket, std::error_code>
{
    v786::CommandRequestPacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.command = *v;
    }
    {
        auto v = Serializer<CommandOriginData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.origin = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.internal_source = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<v786::CurrentCmdVersion>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.version = *v;
    }
    return out;
}

void Serializer<v818::CommandRequestPacket>::serialize(BinaryWriter &stream, const v818::CommandRequestPacket &value)
{
    stream.write(value.command);
    Serializer<CommandOriginData>::serialize(stream, value.origin);
    stream.write<bool>(value.internal_source);
    Serializer<v818::CurrentCmdVersion>::serialize(stream, value.version);
}

auto Serializer<v818::CommandRequestPacket>::deserialize(BinaryReader &stream) -> std::expected<v818::CommandRequestPacket, std::error_code>
{
    v818::CommandRequestPacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.command = *v;
    }
    {
        auto v = Serializer<CommandOriginData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.origin = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.internal_source = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<v818::CurrentCmdVersion>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.version = *v;
    }
    return out;
}

void Serializer<v898::CommandRequestPacket>::serialize(BinaryWriter &stream, const v898::CommandRequestPacket &value)
{
    stream.write(value.command);
    Serializer<CommandOriginData>::serialize(stream, value.origin);
    stream.write<bool>(value.internal_source);
    Serializer<v898::CurrentCmdVersion>::serialize(stream, value.version);
}

auto Serializer<v898::CommandRequestPacket>::deserialize(BinaryReader &stream) -> std::expected<v898::CommandRequestPacket, std::error_code>
{
    v898::CommandRequestPacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.command = *v;
    }
    {
        auto v = Serializer<CommandOriginData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.origin = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.internal_source = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<v898::CurrentCmdVersion>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.version = *v;
    }
    return out;
}

void Serializer<v975::CommandRequestPacket>::serialize(BinaryWriter &stream, const v975::CommandRequestPacket &value)
{
    stream.write(value.command);
    Serializer<CommandOriginData>::serialize(stream, value.origin);
    stream.write<bool>(value.internal_source);
    Serializer<v975::CurrentCmdVersion>::serialize(stream, value.version);
}

auto Serializer<v975::CommandRequestPacket>::deserialize(BinaryReader &stream) -> std::expected<v975::CommandRequestPacket, std::error_code>
{
    v975::CommandRequestPacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.command = *v;
    }
    {
        auto v = Serializer<CommandOriginData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.origin = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.internal_source = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<v975::CurrentCmdVersion>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.version = *v;
    }
    return out;
}

void Serializer<v1001::CommandRequestPacket>::serialize(BinaryWriter &stream, const v1001::CommandRequestPacket &value)
{
    stream.write(value.command);
    Serializer<CommandOriginData>::serialize(stream, value.origin);
    stream.write<bool>(value.internal_source);
    Serializer<v1001::CurrentCmdVersion>::serialize(stream, value.version);
}

auto Serializer<v1001::CommandRequestPacket>::deserialize(BinaryReader &stream) -> std::expected<v1001::CommandRequestPacket, std::error_code>
{
    v1001::CommandRequestPacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.command = *v;
    }
    {
        auto v = Serializer<CommandOriginData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.origin = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.internal_source = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<v1001::CurrentCmdVersion>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.version = *v;
    }
    return out;
}

void Serializer<v2168::CommandRequestPacket>::serialize(BinaryWriter &stream, const v2168::CommandRequestPacket &value)
{
    stream.write(value.command);
    Serializer<CommandOriginData>::serialize(stream, value.origin);
    stream.write<bool>(value.internal_source);
    Serializer<v2168::CurrentCmdVersion>::serialize(stream, value.version);
}

auto Serializer<v2168::CommandRequestPacket>::deserialize(BinaryReader &stream) -> std::expected<v2168::CommandRequestPacket, std::error_code>
{
    v2168::CommandRequestPacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.command = *v;
    }
    {
        auto v = Serializer<CommandOriginData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.origin = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.internal_source = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<v2168::CurrentCmdVersion>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.version = *v;
    }
    return out;
}

void Serializer<v2193::CommandRequestPacket>::serialize(BinaryWriter &stream, const v2193::CommandRequestPacket &value)
{
    stream.write(value.command);
    Serializer<CommandOriginData>::serialize(stream, value.origin);
    stream.write<bool>(value.internal_source);
    Serializer<v2193::CurrentCmdVersion>::serialize(stream, value.version);
}

auto Serializer<v2193::CommandRequestPacket>::deserialize(BinaryReader &stream) -> std::expected<v2193::CommandRequestPacket, std::error_code>
{
    v2193::CommandRequestPacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.command = *v;
    }
    {
        auto v = Serializer<CommandOriginData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.origin = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.internal_source = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<v2193::CurrentCmdVersion>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.version = *v;
    }
    return out;
}

void Serializer<v2225::CommandRequestPacket>::serialize(BinaryWriter &stream, const v2225::CommandRequestPacket &value)
{
    stream.write(value.command);
    Serializer<CommandOriginData>::serialize(stream, value.origin);
    stream.write<bool>(value.internal_source);
    Serializer<v2225::CurrentCmdVersion>::serialize(stream, value.version);
}

auto Serializer<v2225::CommandRequestPacket>::deserialize(BinaryReader &stream) -> std::expected<v2225::CommandRequestPacket, std::error_code>
{
    v2225::CommandRequestPacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.command = *v;
    }
    {
        auto v = Serializer<CommandOriginData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.origin = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.internal_source = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<v2225::CurrentCmdVersion>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.version = *v;
    }
    return out;
}

void Serializer<CommandOutputType>::serialize(BinaryWriter &stream, CommandOutputType value)
{
    stream.write(enum_name(value));
}

auto Serializer<CommandOutputType>::deserialize(BinaryReader &stream) -> std::expected<CommandOutputType, std::error_code>
{
    auto v = stream.read<std::string>();
    if (!v) return std::unexpected(v.error());
    const auto value = enum_cast<CommandOutputType>(*v);
    if (!value) return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
    return *value;
}

void Serializer<CommandOutputMessage>::serialize(BinaryWriter &stream, const CommandOutputMessage &value)
{
    stream.write(value.message_id);
    stream.write<bool>(value.successful);
    stream.writeVarInt<std::uint32_t>(value.params.size());
    for (const auto &e0 : value.params) {
        stream.write(e0);
    }
}

auto Serializer<CommandOutputMessage>::deserialize(BinaryReader &stream) -> std::expected<CommandOutputMessage, std::error_code>
{
    CommandOutputMessage out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.message_id = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.successful = static_cast<bool>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.params.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.params.emplace_back();
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.params.back() = *v;
        }
    }
    return out;
}

void Serializer<CommandOutput>::serialize(BinaryWriter &stream, const CommandOutput &value)
{
    Serializer<CommandOutputType>::serialize(stream, value.type);
    stream.write<std::uint32_t>(value.success_count);
    stream.writeVarInt<std::uint32_t>(value.messages.size());
    for (const auto &e0 : value.messages) {
        Serializer<CommandOutputMessage>::serialize(stream, e0);
    }
    stream.write<bool>(value.data.has_value());
    if (value.data.has_value()) {
        stream.write((*value.data));
    }
}

auto Serializer<CommandOutput>::deserialize(BinaryReader &stream) -> std::expected<CommandOutput, std::error_code>
{
    CommandOutput out;
    {
        auto v = Serializer<CommandOutputType>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.type = *v;
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.success_count = static_cast<std::uint32_t>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.messages.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.messages.emplace_back();
            auto v = Serializer<CommandOutputMessage>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.messages.back() = *v;
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
            out.data = std::move(staged);
        }
    }
    return out;
}

void Serializer<CommandOutputPacket>::serialize(BinaryWriter &stream, const CommandOutputPacket &value)
{
    Serializer<CommandOriginData>::serialize(stream, value.origin_data);
    Serializer<CommandOutput>::serialize(stream, value.output);
}

auto Serializer<CommandOutputPacket>::deserialize(BinaryReader &stream) -> std::expected<CommandOutputPacket, std::error_code>
{
    CommandOutputPacket out;
    {
        auto v = Serializer<CommandOriginData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.origin_data = *v;
    }
    {
        auto v = Serializer<CommandOutput>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.output = *v;
    }
    return out;
}

void Serializer<UpdateSoftEnumPacket>::serialize(BinaryWriter &stream, const UpdateSoftEnumPacket &value)
{
    stream.write(value.enum_name);
    stream.writeVarInt<std::uint32_t>(value.values.size());
    for (const auto &e0 : value.values) {
        stream.write(e0);
    }
    stream.write<std::uint8_t>(value.type);
}

auto Serializer<UpdateSoftEnumPacket>::deserialize(BinaryReader &stream) -> std::expected<UpdateSoftEnumPacket, std::error_code>
{
    UpdateSoftEnumPacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.enum_name = *v;
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.values.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.values.emplace_back();
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.values.back() = *v;
        }
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<SoftEnumUpdateType>(*v);
    }
    return out;
}

}  // namespace bedrock::protocol
