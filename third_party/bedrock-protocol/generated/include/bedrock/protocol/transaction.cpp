#include <bedrock/protocol/transaction.h>

namespace bedrock::protocol {


void Serializer<base::LegacySetSlot>::serialize(BinaryWriter &stream, const base::LegacySetSlot &value)
{
    stream.write<std::uint8_t>(value.container_enum);
    stream.write(value.slots);
}

auto Serializer<base::LegacySetSlot>::deserialize(BinaryReader &stream) -> std::expected<base::LegacySetSlot, std::error_code>
{
    base::LegacySetSlot out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.container_enum = static_cast<base::ContainerEnumName>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.slots = *v;
    }
    return out;
}

void Serializer<v924::LegacySetSlot>::serialize(BinaryWriter &stream, const v924::LegacySetSlot &value)
{
    stream.write<std::uint8_t>(value.container_enum);
    stream.write(value.slots);
}

auto Serializer<v924::LegacySetSlot>::deserialize(BinaryReader &stream) -> std::expected<v924::LegacySetSlot, std::error_code>
{
    v924::LegacySetSlot out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.container_enum = static_cast<v924::ContainerEnumName>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.slots = *v;
    }
    return out;
}

void Serializer<v2225::LegacySetSlot>::serialize(BinaryWriter &stream, const v2225::LegacySetSlot &value)
{
    stream.write<std::uint8_t>(value.container_enum);
    stream.write(value.slots);
}

auto Serializer<v2225::LegacySetSlot>::deserialize(BinaryReader &stream) -> std::expected<v2225::LegacySetSlot, std::error_code>
{
    v2225::LegacySetSlot out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.container_enum = static_cast<v2225::ContainerEnumName>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.slots = *v;
    }
    return out;
}

void Serializer<base::InventorySource>::serialize(BinaryWriter &stream, const base::InventorySource &value)
{
    stream.writeVarInt<std::uint32_t>(value.type);
    if (((value.type) == (InventorySourceType::ContainerInventory)) || ((value.type) == (InventorySourceType::NonImplementedFeatureTodo))) {
        stream.writeVarInt<std::int32_t>(value.container_id);
    }
    if ((value.type) == (InventorySourceType::WorldInteraction)) {
        stream.writeVarInt<std::uint32_t>(value.flags);
    }
}

auto Serializer<base::InventorySource>::deserialize(BinaryReader &stream) -> std::expected<base::InventorySource, std::error_code>
{
    base::InventorySource out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<InventorySourceType>(*v);
    }
    if (((out.type) == (InventorySourceType::ContainerInventory)) || ((out.type) == (InventorySourceType::NonImplementedFeatureTodo))) {
        {
            auto v = stream.readVarInt<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            out.container_id = static_cast<base::ContainerID>(*v);
        }
    }
    if ((out.type) == (InventorySourceType::WorldInteraction)) {
        {
            auto v = stream.readVarInt<std::uint32_t>();
            if (!v) return std::unexpected(v.error());
            out.flags = static_cast<base::InventorySource::InventorySourceFlags>(*v);
        }
    }
    return out;
}

void Serializer<v748::InventorySource>::serialize(BinaryWriter &stream, const v748::InventorySource &value)
{
    stream.writeVarInt<std::uint32_t>(value.type);
    if (((value.type) == (InventorySourceType::ContainerInventory)) || ((value.type) == (InventorySourceType::NonImplementedFeatureTodo))) {
        stream.writeVarInt<std::int32_t>(value.container_id);
    }
    if ((value.type) == (InventorySourceType::WorldInteraction)) {
        stream.writeVarInt<std::uint32_t>(value.flags);
    }
}

auto Serializer<v748::InventorySource>::deserialize(BinaryReader &stream) -> std::expected<v748::InventorySource, std::error_code>
{
    v748::InventorySource out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<InventorySourceType>(*v);
    }
    if (((out.type) == (InventorySourceType::ContainerInventory)) || ((out.type) == (InventorySourceType::NonImplementedFeatureTodo))) {
        {
            auto v = stream.readVarInt<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            out.container_id = static_cast<v748::ContainerID>(*v);
        }
    }
    if ((out.type) == (InventorySourceType::WorldInteraction)) {
        {
            auto v = stream.readVarInt<std::uint32_t>();
            if (!v) return std::unexpected(v.error());
            out.flags = static_cast<v748::InventorySource::InventorySourceFlags>(*v);
        }
    }
    return out;
}

void Serializer<v1001::InventorySource>::serialize(BinaryWriter &stream, const v1001::InventorySource &value)
{
    stream.writeVarInt<std::uint32_t>(value.type);
    stream.write<bool>(true);
    stream.write<bool>(value.container_id.has_value());
    if (value.container_id.has_value()) {
        stream.write<std::int8_t>((*value.container_id));
    }
    stream.write<bool>(true);
    stream.write<bool>(value.flags.has_value());
    if (value.flags.has_value()) {
        stream.writeVarInt<std::uint32_t>((*value.flags));
    }
}

auto Serializer<v1001::InventorySource>::deserialize(BinaryReader &stream) -> std::expected<v1001::InventorySource, std::error_code>
{
    v1001::InventorySource out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<InventorySourceType>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        if (*v != true) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v748::ContainerID staged{};
            auto v = stream.read<std::int8_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<v748::ContainerID>(*v);
            out.container_id = std::move(staged);
        }
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        if (*v != true) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v1001::InventorySource::InventorySourceFlags staged{};
            auto v = stream.readVarInt<std::uint32_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<v1001::InventorySource::InventorySourceFlags>(*v);
            out.flags = std::move(staged);
        }
    }
    return out;
}

void Serializer<v2193::InventorySource>::serialize(BinaryWriter &stream, const v2193::InventorySource &value)
{
    stream.writeVarInt<std::uint32_t>(value.type);
    stream.write<bool>(value.container_id.has_value());
    if (value.container_id.has_value()) {
        stream.write<std::int8_t>((*value.container_id));
    }
    stream.write<bool>(value.flags.has_value());
    if (value.flags.has_value()) {
        stream.writeVarInt<std::uint32_t>((*value.flags));
    }
}

auto Serializer<v2193::InventorySource>::deserialize(BinaryReader &stream) -> std::expected<v2193::InventorySource, std::error_code>
{
    v2193::InventorySource out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<InventorySourceType>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v748::ContainerID staged{};
            auto v = stream.read<std::int8_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<v748::ContainerID>(*v);
            out.container_id = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v2193::InventorySource::InventorySourceFlags staged{};
            auto v = stream.readVarInt<std::uint32_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<v2193::InventorySource::InventorySourceFlags>(*v);
            out.flags = std::move(staged);
        }
    }
    return out;
}

void Serializer<base::InventoryAction>::serialize(BinaryWriter &stream, const base::InventoryAction &value)
{
    Serializer<base::InventorySource>::serialize(stream, value.source);
    stream.writeVarInt<std::uint32_t>(value.slot);
    Serializer<NetworkItemStackDescriptor>::serialize(stream, value.from_item_descriptor);
    Serializer<NetworkItemStackDescriptor>::serialize(stream, value.to_item_descriptor);
}

auto Serializer<base::InventoryAction>::deserialize(BinaryReader &stream) -> std::expected<base::InventoryAction, std::error_code>
{
    base::InventoryAction out;
    {
        auto v = Serializer<base::InventorySource>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.source = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = Serializer<NetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.from_item_descriptor = *v;
    }
    {
        auto v = Serializer<NetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.to_item_descriptor = *v;
    }
    return out;
}

void Serializer<v748::InventoryAction>::serialize(BinaryWriter &stream, const v748::InventoryAction &value)
{
    Serializer<v748::InventorySource>::serialize(stream, value.source);
    stream.writeVarInt<std::uint32_t>(value.slot);
    Serializer<NetworkItemStackDescriptor>::serialize(stream, value.from_item_descriptor);
    Serializer<NetworkItemStackDescriptor>::serialize(stream, value.to_item_descriptor);
}

auto Serializer<v748::InventoryAction>::deserialize(BinaryReader &stream) -> std::expected<v748::InventoryAction, std::error_code>
{
    v748::InventoryAction out;
    {
        auto v = Serializer<v748::InventorySource>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.source = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = Serializer<NetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.from_item_descriptor = *v;
    }
    {
        auto v = Serializer<NetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.to_item_descriptor = *v;
    }
    return out;
}

void Serializer<v1001::InventoryAction>::serialize(BinaryWriter &stream, const v1001::InventoryAction &value)
{
    Serializer<v1001::InventorySource>::serialize(stream, value.source);
    stream.writeVarInt<std::uint32_t>(value.slot);
    Serializer<base::SerializedNetworkItemStackDescriptor>::serialize(stream, value.from_item_descriptor);
    Serializer<base::SerializedNetworkItemStackDescriptor>::serialize(stream, value.to_item_descriptor);
}

auto Serializer<v1001::InventoryAction>::deserialize(BinaryReader &stream) -> std::expected<v1001::InventoryAction, std::error_code>
{
    v1001::InventoryAction out;
    {
        auto v = Serializer<v1001::InventorySource>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.source = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = Serializer<base::SerializedNetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.from_item_descriptor = *v;
    }
    {
        auto v = Serializer<base::SerializedNetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.to_item_descriptor = *v;
    }
    return out;
}

void Serializer<v2168::InventoryAction>::serialize(BinaryWriter &stream, const v2168::InventoryAction &value)
{
    Serializer<v1001::InventorySource>::serialize(stream, value.source);
    stream.writeVarInt<std::uint32_t>(value.slot);
    Serializer<v2168::SerializedNetworkItemStackDescriptor>::serialize(stream, value.from_item_descriptor);
    Serializer<v2168::SerializedNetworkItemStackDescriptor>::serialize(stream, value.to_item_descriptor);
}

auto Serializer<v2168::InventoryAction>::deserialize(BinaryReader &stream) -> std::expected<v2168::InventoryAction, std::error_code>
{
    v2168::InventoryAction out;
    {
        auto v = Serializer<v1001::InventorySource>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.source = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = Serializer<v2168::SerializedNetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.from_item_descriptor = *v;
    }
    {
        auto v = Serializer<v2168::SerializedNetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.to_item_descriptor = *v;
    }
    return out;
}

void Serializer<v2193::InventoryAction>::serialize(BinaryWriter &stream, const v2193::InventoryAction &value)
{
    Serializer<v2193::InventorySource>::serialize(stream, value.source);
    stream.writeVarInt<std::uint32_t>(value.slot);
    Serializer<v2168::SerializedNetworkItemStackDescriptor>::serialize(stream, value.from_item_descriptor);
    Serializer<v2168::SerializedNetworkItemStackDescriptor>::serialize(stream, value.to_item_descriptor);
}

auto Serializer<v2193::InventoryAction>::deserialize(BinaryReader &stream) -> std::expected<v2193::InventoryAction, std::error_code>
{
    v2193::InventoryAction out;
    {
        auto v = Serializer<v2193::InventorySource>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.source = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = Serializer<v2168::SerializedNetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.from_item_descriptor = *v;
    }
    {
        auto v = Serializer<v2168::SerializedNetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.to_item_descriptor = *v;
    }
    return out;
}

void Serializer<base::InventoryTransaction>::serialize(BinaryWriter &stream, const base::InventoryTransaction &value)
{
    stream.writeVarInt<std::uint32_t>(value.actions.size());
    for (const auto &e0 : value.actions) {
        Serializer<base::InventoryAction>::serialize(stream, e0);
    }
}

auto Serializer<base::InventoryTransaction>::deserialize(BinaryReader &stream) -> std::expected<base::InventoryTransaction, std::error_code>
{
    base::InventoryTransaction out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.actions.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.actions.emplace_back();
            auto v = Serializer<base::InventoryAction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.actions.back() = *v;
        }
    }
    return out;
}

void Serializer<v748::InventoryTransaction>::serialize(BinaryWriter &stream, const v748::InventoryTransaction &value)
{
    stream.writeVarInt<std::uint32_t>(value.actions.size());
    for (const auto &e0 : value.actions) {
        Serializer<v748::InventoryAction>::serialize(stream, e0);
    }
}

auto Serializer<v748::InventoryTransaction>::deserialize(BinaryReader &stream) -> std::expected<v748::InventoryTransaction, std::error_code>
{
    v748::InventoryTransaction out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.actions.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.actions.emplace_back();
            auto v = Serializer<v748::InventoryAction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.actions.back() = *v;
        }
    }
    return out;
}

void Serializer<v1001::InventoryTransaction>::serialize(BinaryWriter &stream, const v1001::InventoryTransaction &value)
{
    stream.write<bool>(true);
    stream.writeVarInt<std::uint32_t>(value.actions.size());
    for (const auto &e0 : value.actions) {
        Serializer<v1001::InventoryAction>::serialize(stream, e0);
    }
}

auto Serializer<v1001::InventoryTransaction>::deserialize(BinaryReader &stream) -> std::expected<v1001::InventoryTransaction, std::error_code>
{
    v1001::InventoryTransaction out;
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        if (*v != true) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.actions.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.actions.emplace_back();
            auto v = Serializer<v1001::InventoryAction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.actions.back() = *v;
        }
    }
    return out;
}

void Serializer<v2168::InventoryTransaction>::serialize(BinaryWriter &stream, const v2168::InventoryTransaction &value)
{
    stream.write<bool>(true);
    stream.writeVarInt<std::uint32_t>(value.actions.size());
    for (const auto &e0 : value.actions) {
        Serializer<v2168::InventoryAction>::serialize(stream, e0);
    }
}

auto Serializer<v2168::InventoryTransaction>::deserialize(BinaryReader &stream) -> std::expected<v2168::InventoryTransaction, std::error_code>
{
    v2168::InventoryTransaction out;
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        if (*v != true) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.actions.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.actions.emplace_back();
            auto v = Serializer<v2168::InventoryAction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.actions.back() = *v;
        }
    }
    return out;
}

void Serializer<v2193::InventoryTransaction>::serialize(BinaryWriter &stream, const v2193::InventoryTransaction &value)
{
    stream.writeVarInt<std::uint32_t>(value.actions.size());
    for (const auto &e0 : value.actions) {
        Serializer<v2193::InventoryAction>::serialize(stream, e0);
    }
}

auto Serializer<v2193::InventoryTransaction>::deserialize(BinaryReader &stream) -> std::expected<v2193::InventoryTransaction, std::error_code>
{
    v2193::InventoryTransaction out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.actions.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.actions.emplace_back();
            auto v = Serializer<v2193::InventoryAction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.actions.back() = *v;
        }
    }
    return out;
}

void Serializer<base::NormalTransactionData>::serialize(BinaryWriter &stream, const base::NormalTransactionData &value)
{
    Serializer<base::InventoryTransaction>::serialize(stream, value.transaction);
}

auto Serializer<base::NormalTransactionData>::deserialize(BinaryReader &stream) -> std::expected<base::NormalTransactionData, std::error_code>
{
    base::NormalTransactionData out;
    {
        auto v = Serializer<base::InventoryTransaction>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.transaction = *v;
    }
    return out;
}

void Serializer<v748::NormalTransactionData>::serialize(BinaryWriter &stream, const v748::NormalTransactionData &value)
{
    Serializer<v748::InventoryTransaction>::serialize(stream, value.transaction);
}

auto Serializer<v748::NormalTransactionData>::deserialize(BinaryReader &stream) -> std::expected<v748::NormalTransactionData, std::error_code>
{
    v748::NormalTransactionData out;
    {
        auto v = Serializer<v748::InventoryTransaction>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.transaction = *v;
    }
    return out;
}

void Serializer<v1001::NormalTransactionData>::serialize(BinaryWriter &stream, const v1001::NormalTransactionData &value)
{
    Serializer<v1001::InventoryTransaction>::serialize(stream, value.transaction);
}

auto Serializer<v1001::NormalTransactionData>::deserialize(BinaryReader &stream) -> std::expected<v1001::NormalTransactionData, std::error_code>
{
    v1001::NormalTransactionData out;
    {
        auto v = Serializer<v1001::InventoryTransaction>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.transaction = *v;
    }
    return out;
}

void Serializer<v2168::NormalTransactionData>::serialize(BinaryWriter &stream, const v2168::NormalTransactionData &value)
{
    Serializer<v2168::InventoryTransaction>::serialize(stream, value.transaction);
}

auto Serializer<v2168::NormalTransactionData>::deserialize(BinaryReader &stream) -> std::expected<v2168::NormalTransactionData, std::error_code>
{
    v2168::NormalTransactionData out;
    {
        auto v = Serializer<v2168::InventoryTransaction>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.transaction = *v;
    }
    return out;
}

void Serializer<v2193::NormalTransactionData>::serialize(BinaryWriter &stream, const v2193::NormalTransactionData &value)
{
    Serializer<v2193::InventoryTransaction>::serialize(stream, value.transaction);
}

auto Serializer<v2193::NormalTransactionData>::deserialize(BinaryReader &stream) -> std::expected<v2193::NormalTransactionData, std::error_code>
{
    v2193::NormalTransactionData out;
    {
        auto v = Serializer<v2193::InventoryTransaction>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.transaction = *v;
    }
    return out;
}

void Serializer<base::InventoryMismatchData>::serialize(BinaryWriter &stream, const base::InventoryMismatchData &value)
{
    Serializer<base::InventoryTransaction>::serialize(stream, value.transaction);
}

auto Serializer<base::InventoryMismatchData>::deserialize(BinaryReader &stream) -> std::expected<base::InventoryMismatchData, std::error_code>
{
    base::InventoryMismatchData out;
    {
        auto v = Serializer<base::InventoryTransaction>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.transaction = *v;
    }
    return out;
}

void Serializer<v748::InventoryMismatchData>::serialize(BinaryWriter &stream, const v748::InventoryMismatchData &value)
{
    Serializer<v748::InventoryTransaction>::serialize(stream, value.transaction);
}

auto Serializer<v748::InventoryMismatchData>::deserialize(BinaryReader &stream) -> std::expected<v748::InventoryMismatchData, std::error_code>
{
    v748::InventoryMismatchData out;
    {
        auto v = Serializer<v748::InventoryTransaction>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.transaction = *v;
    }
    return out;
}

void Serializer<v1001::InventoryMismatchData>::serialize(BinaryWriter &stream, const v1001::InventoryMismatchData &value)
{
    Serializer<v1001::InventoryTransaction>::serialize(stream, value.transaction);
}

auto Serializer<v1001::InventoryMismatchData>::deserialize(BinaryReader &stream) -> std::expected<v1001::InventoryMismatchData, std::error_code>
{
    v1001::InventoryMismatchData out;
    {
        auto v = Serializer<v1001::InventoryTransaction>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.transaction = *v;
    }
    return out;
}

void Serializer<v2168::InventoryMismatchData>::serialize(BinaryWriter &stream, const v2168::InventoryMismatchData &value)
{
    Serializer<v2168::InventoryTransaction>::serialize(stream, value.transaction);
}

auto Serializer<v2168::InventoryMismatchData>::deserialize(BinaryReader &stream) -> std::expected<v2168::InventoryMismatchData, std::error_code>
{
    v2168::InventoryMismatchData out;
    {
        auto v = Serializer<v2168::InventoryTransaction>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.transaction = *v;
    }
    return out;
}

void Serializer<v2193::InventoryMismatchData>::serialize(BinaryWriter &stream, const v2193::InventoryMismatchData &value)
{
    Serializer<v2193::InventoryTransaction>::serialize(stream, value.transaction);
}

auto Serializer<v2193::InventoryMismatchData>::deserialize(BinaryReader &stream) -> std::expected<v2193::InventoryMismatchData, std::error_code>
{
    v2193::InventoryMismatchData out;
    {
        auto v = Serializer<v2193::InventoryTransaction>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.transaction = *v;
    }
    return out;
}

void Serializer<base::ItemUseInventoryTransaction>::serialize(BinaryWriter &stream, const base::ItemUseInventoryTransaction &value)
{
    Serializer<base::InventoryTransaction>::serialize(stream, value.transaction);
    stream.writeVarInt<std::uint32_t>(value.action_type);
    stream.write<std::uint8_t>(value.trigger_type);
    Serializer<base::NetworkBlockPosition>::serialize(stream, value.pos);
    stream.writeVarInt<std::int32_t>(value.face);
    stream.writeVarInt<std::int32_t>(value.slot);
    Serializer<NetworkItemStackDescriptor>::serialize(stream, value.item);
    Serializer<Vec3>::serialize(stream, value.from_pos);
    Serializer<Vec3>::serialize(stream, value.click_pos);
    stream.writeVarInt<std::uint32_t>(value.target_block_id);
    stream.writeVarInt<std::uint32_t>(value.client_predicted_result);
}

auto Serializer<base::ItemUseInventoryTransaction>::deserialize(BinaryReader &stream) -> std::expected<base::ItemUseInventoryTransaction, std::error_code>
{
    base::ItemUseInventoryTransaction out;
    {
        auto v = Serializer<base::InventoryTransaction>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.transaction = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.action_type = static_cast<base::ItemUseInventoryTransaction::ActionType>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.trigger_type = static_cast<base::ItemUseInventoryTransaction::TriggerType>(*v);
    }
    {
        auto v = Serializer<base::NetworkBlockPosition>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.face = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::int32_t>(*v);
    }
    {
        auto v = Serializer<NetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.item = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.from_pos = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.click_pos = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.target_block_id = static_cast<BlockRuntimeId>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.client_predicted_result = static_cast<base::ItemUseInventoryTransaction::PredictedResult>(*v);
    }
    return out;
}

void Serializer<v748::ItemUseInventoryTransaction>::serialize(BinaryWriter &stream, const v748::ItemUseInventoryTransaction &value)
{
    Serializer<v748::InventoryTransaction>::serialize(stream, value.transaction);
    stream.writeVarInt<std::uint32_t>(value.action_type);
    stream.write<std::uint8_t>(value.trigger_type);
    Serializer<base::NetworkBlockPosition>::serialize(stream, value.pos);
    stream.writeVarInt<std::int32_t>(value.face);
    stream.writeVarInt<std::int32_t>(value.slot);
    Serializer<NetworkItemStackDescriptor>::serialize(stream, value.item);
    Serializer<Vec3>::serialize(stream, value.from_pos);
    Serializer<Vec3>::serialize(stream, value.click_pos);
    stream.writeVarInt<std::uint32_t>(value.target_block_id);
    stream.writeVarInt<std::uint32_t>(value.client_predicted_result);
}

auto Serializer<v748::ItemUseInventoryTransaction>::deserialize(BinaryReader &stream) -> std::expected<v748::ItemUseInventoryTransaction, std::error_code>
{
    v748::ItemUseInventoryTransaction out;
    {
        auto v = Serializer<v748::InventoryTransaction>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.transaction = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.action_type = static_cast<v748::ItemUseInventoryTransaction::ActionType>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.trigger_type = static_cast<v748::ItemUseInventoryTransaction::TriggerType>(*v);
    }
    {
        auto v = Serializer<base::NetworkBlockPosition>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.face = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::int32_t>(*v);
    }
    {
        auto v = Serializer<NetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.item = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.from_pos = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.click_pos = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.target_block_id = static_cast<BlockRuntimeId>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.client_predicted_result = static_cast<v748::ItemUseInventoryTransaction::PredictedResult>(*v);
    }
    return out;
}

void Serializer<v844::ItemUseInventoryTransaction>::serialize(BinaryWriter &stream, const v844::ItemUseInventoryTransaction &value)
{
    Serializer<v748::InventoryTransaction>::serialize(stream, value.transaction);
    stream.writeVarInt<std::uint32_t>(value.action_type);
    stream.write<std::uint8_t>(value.trigger_type);
    Serializer<base::NetworkBlockPosition>::serialize(stream, value.pos);
    stream.writeVarInt<std::int32_t>(value.face);
    stream.writeVarInt<std::int32_t>(value.slot);
    Serializer<NetworkItemStackDescriptor>::serialize(stream, value.item);
    Serializer<Vec3>::serialize(stream, value.from_pos);
    Serializer<Vec3>::serialize(stream, value.click_pos);
    stream.writeVarInt<std::uint32_t>(value.target_block_id);
    stream.writeVarInt<std::uint32_t>(value.client_predicted_result);
}

auto Serializer<v844::ItemUseInventoryTransaction>::deserialize(BinaryReader &stream) -> std::expected<v844::ItemUseInventoryTransaction, std::error_code>
{
    v844::ItemUseInventoryTransaction out;
    {
        auto v = Serializer<v748::InventoryTransaction>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.transaction = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.action_type = static_cast<v844::ItemUseInventoryTransaction::ActionType>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.trigger_type = static_cast<v844::ItemUseInventoryTransaction::TriggerType>(*v);
    }
    {
        auto v = Serializer<base::NetworkBlockPosition>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.face = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::int32_t>(*v);
    }
    {
        auto v = Serializer<NetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.item = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.from_pos = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.click_pos = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.target_block_id = static_cast<BlockRuntimeId>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.client_predicted_result = static_cast<v844::ItemUseInventoryTransaction::PredictedResult>(*v);
    }
    return out;
}

void Serializer<v944::ItemUseInventoryTransaction>::serialize(BinaryWriter &stream, const v944::ItemUseInventoryTransaction &value)
{
    Serializer<v748::InventoryTransaction>::serialize(stream, value.transaction);
    stream.writeVarInt<std::uint32_t>(value.action_type);
    stream.write<std::uint8_t>(value.trigger_type);
    Serializer<BlockPos>::serialize(stream, value.pos);
    stream.writeVarInt<std::int32_t>(value.face);
    stream.writeVarInt<std::int32_t>(value.slot);
    Serializer<NetworkItemStackDescriptor>::serialize(stream, value.item);
    Serializer<Vec3>::serialize(stream, value.from_pos);
    Serializer<Vec3>::serialize(stream, value.click_pos);
    stream.writeVarInt<std::uint32_t>(value.target_block_id);
    stream.writeVarInt<std::uint32_t>(value.client_predicted_result);
    stream.write<std::uint8_t>(value.client_cooldown_state);
}

auto Serializer<v944::ItemUseInventoryTransaction>::deserialize(BinaryReader &stream) -> std::expected<v944::ItemUseInventoryTransaction, std::error_code>
{
    v944::ItemUseInventoryTransaction out;
    {
        auto v = Serializer<v748::InventoryTransaction>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.transaction = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.action_type = static_cast<v944::ItemUseInventoryTransaction::ActionType>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.trigger_type = static_cast<v944::ItemUseInventoryTransaction::TriggerType>(*v);
    }
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.face = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::int32_t>(*v);
    }
    {
        auto v = Serializer<NetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.item = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.from_pos = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.click_pos = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.target_block_id = static_cast<BlockRuntimeId>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.client_predicted_result = static_cast<v944::ItemUseInventoryTransaction::PredictedResult>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.client_cooldown_state = static_cast<v944::ItemUseInventoryTransaction::ClientCooldownState>(*v);
    }
    return out;
}

void Serializer<v1001::ItemUseInventoryTransaction>::serialize(BinaryWriter &stream, const v1001::ItemUseInventoryTransaction &value)
{
    Serializer<v1001::InventoryTransaction>::serialize(stream, value.transaction);
    stream.writeVarInt<std::int32_t>(value.action_type);
    stream.write<std::uint8_t>(value.trigger_type);
    Serializer<BlockPos>::serialize(stream, value.pos);
    stream.write<std::uint8_t>(value.face);
    stream.writeVarInt<std::int32_t>(value.slot);
    Serializer<base::SerializedNetworkItemStackDescriptor>::serialize(stream, value.item);
    Serializer<Vec3>::serialize(stream, value.from_pos);
    Serializer<Vec3>::serialize(stream, value.click_pos);
    stream.writeVarInt<std::uint32_t>(value.target_block_id);
    stream.write<std::uint8_t>(value.client_predicted_result);
    stream.write<std::uint8_t>(value.client_cooldown_state);
}

auto Serializer<v1001::ItemUseInventoryTransaction>::deserialize(BinaryReader &stream) -> std::expected<v1001::ItemUseInventoryTransaction, std::error_code>
{
    v1001::ItemUseInventoryTransaction out;
    {
        auto v = Serializer<v1001::InventoryTransaction>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.transaction = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.action_type = static_cast<v1001::ItemUseInventoryTransaction::ActionType>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.trigger_type = static_cast<v1001::ItemUseInventoryTransaction::TriggerType>(*v);
    }
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.face = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::int32_t>(*v);
    }
    {
        auto v = Serializer<base::SerializedNetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.item = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.from_pos = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.click_pos = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.target_block_id = static_cast<BlockRuntimeId>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.client_predicted_result = static_cast<v1001::ItemUseInventoryTransaction::PredictedResult>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.client_cooldown_state = static_cast<v1001::ItemUseInventoryTransaction::ClientCooldownState>(*v);
    }
    return out;
}

void Serializer<v2168::ItemUseInventoryTransaction>::serialize(BinaryWriter &stream, const v2168::ItemUseInventoryTransaction &value)
{
    Serializer<v2168::InventoryTransaction>::serialize(stream, value.transaction);
    stream.writeVarInt<std::int32_t>(value.action_type);
    stream.write<std::uint8_t>(value.trigger_type);
    Serializer<BlockPos>::serialize(stream, value.pos);
    stream.write<std::uint8_t>(value.face);
    stream.writeVarInt<std::int32_t>(value.slot);
    Serializer<v2168::SerializedNetworkItemStackDescriptor>::serialize(stream, value.item);
    Serializer<Vec3>::serialize(stream, value.from_pos);
    Serializer<Vec3>::serialize(stream, value.click_pos);
    stream.writeVarInt<std::uint32_t>(value.target_block_id);
    stream.write<std::uint8_t>(value.client_predicted_result);
    stream.write<std::uint8_t>(value.client_cooldown_state);
}

auto Serializer<v2168::ItemUseInventoryTransaction>::deserialize(BinaryReader &stream) -> std::expected<v2168::ItemUseInventoryTransaction, std::error_code>
{
    v2168::ItemUseInventoryTransaction out;
    {
        auto v = Serializer<v2168::InventoryTransaction>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.transaction = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.action_type = static_cast<v2168::ItemUseInventoryTransaction::ActionType>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.trigger_type = static_cast<v2168::ItemUseInventoryTransaction::TriggerType>(*v);
    }
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.face = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::int32_t>(*v);
    }
    {
        auto v = Serializer<v2168::SerializedNetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.item = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.from_pos = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.click_pos = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.target_block_id = static_cast<BlockRuntimeId>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.client_predicted_result = static_cast<v2168::ItemUseInventoryTransaction::PredictedResult>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.client_cooldown_state = static_cast<v2168::ItemUseInventoryTransaction::ClientCooldownState>(*v);
    }
    return out;
}

void Serializer<v2193::ItemUseInventoryTransaction>::serialize(BinaryWriter &stream, const v2193::ItemUseInventoryTransaction &value)
{
    Serializer<v2193::InventoryTransaction>::serialize(stream, value.transaction);
    stream.writeVarInt<std::int32_t>(value.action_type);
    stream.write<std::uint8_t>(value.trigger_type);
    Serializer<BlockPos>::serialize(stream, value.pos);
    stream.write<std::uint8_t>(value.face);
    stream.writeVarInt<std::int32_t>(value.slot);
    stream.write<std::uint8_t>(value.hand);
    Serializer<v2168::SerializedNetworkItemStackDescriptor>::serialize(stream, value.item);
    Serializer<Vec3>::serialize(stream, value.from_pos);
    Serializer<Vec3>::serialize(stream, value.click_pos);
    stream.writeVarInt<std::uint32_t>(value.target_block_id);
    stream.write<std::uint8_t>(value.client_predicted_result);
    stream.write<std::uint8_t>(value.client_cooldown_state);
}

auto Serializer<v2193::ItemUseInventoryTransaction>::deserialize(BinaryReader &stream) -> std::expected<v2193::ItemUseInventoryTransaction, std::error_code>
{
    v2193::ItemUseInventoryTransaction out;
    {
        auto v = Serializer<v2193::InventoryTransaction>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.transaction = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.action_type = static_cast<v2193::ItemUseInventoryTransaction::ActionType>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.trigger_type = static_cast<v2193::ItemUseInventoryTransaction::TriggerType>(*v);
    }
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.face = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.hand = static_cast<HandSlot>(*v);
    }
    {
        auto v = Serializer<v2168::SerializedNetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.item = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.from_pos = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.click_pos = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.target_block_id = static_cast<BlockRuntimeId>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.client_predicted_result = static_cast<v2193::ItemUseInventoryTransaction::PredictedResult>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.client_cooldown_state = static_cast<v2193::ItemUseInventoryTransaction::ClientCooldownState>(*v);
    }
    return out;
}

void Serializer<legacy::base::ItemUseInventoryTransaction>::serialize(BinaryWriter &stream, const legacy::base::ItemUseInventoryTransaction &value)
{
    stream.writeVarInt<std::uint32_t>(value.actions.size());
    for (const auto &e0 : value.actions) {
        Serializer<base::InventoryAction>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.action_type);
    stream.write<std::uint8_t>(value.trigger_type);
    Serializer<base::NetworkBlockPosition>::serialize(stream, value.pos);
    stream.writeVarInt<std::int32_t>(value.face);
    stream.writeVarInt<std::int32_t>(value.slot);
    Serializer<NetworkItemStackDescriptor>::serialize(stream, value.item);
    Serializer<Vec3>::serialize(stream, value.from_pos);
    Serializer<Vec3>::serialize(stream, value.click_pos);
    stream.writeVarInt<std::uint32_t>(value.target_block_id);
    stream.writeVarInt<std::uint32_t>(value.client_predicted_result);
}

auto Serializer<legacy::base::ItemUseInventoryTransaction>::deserialize(BinaryReader &stream) -> std::expected<legacy::base::ItemUseInventoryTransaction, std::error_code>
{
    legacy::base::ItemUseInventoryTransaction out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.actions.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.actions.emplace_back();
            auto v = Serializer<base::InventoryAction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.actions.back() = *v;
        }
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.action_type = static_cast<base::ItemUseInventoryTransaction::ActionType>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.trigger_type = static_cast<base::ItemUseInventoryTransaction::TriggerType>(*v);
    }
    {
        auto v = Serializer<base::NetworkBlockPosition>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.face = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::int32_t>(*v);
    }
    {
        auto v = Serializer<NetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.item = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.from_pos = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.click_pos = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.target_block_id = static_cast<BlockRuntimeId>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.client_predicted_result = static_cast<base::ItemUseInventoryTransaction::PredictedResult>(*v);
    }
    return out;
}

void Serializer<legacy::v748::ItemUseInventoryTransaction>::serialize(BinaryWriter &stream, const legacy::v748::ItemUseInventoryTransaction &value)
{
    stream.writeVarInt<std::uint32_t>(value.actions.size());
    for (const auto &e0 : value.actions) {
        Serializer<v748::InventoryAction>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.action_type);
    stream.write<std::uint8_t>(value.trigger_type);
    Serializer<base::NetworkBlockPosition>::serialize(stream, value.pos);
    stream.writeVarInt<std::int32_t>(value.face);
    stream.writeVarInt<std::int32_t>(value.slot);
    Serializer<NetworkItemStackDescriptor>::serialize(stream, value.item);
    Serializer<Vec3>::serialize(stream, value.from_pos);
    Serializer<Vec3>::serialize(stream, value.click_pos);
    stream.writeVarInt<std::uint32_t>(value.target_block_id);
    stream.writeVarInt<std::uint32_t>(value.client_predicted_result);
}

auto Serializer<legacy::v748::ItemUseInventoryTransaction>::deserialize(BinaryReader &stream) -> std::expected<legacy::v748::ItemUseInventoryTransaction, std::error_code>
{
    legacy::v748::ItemUseInventoryTransaction out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.actions.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.actions.emplace_back();
            auto v = Serializer<v748::InventoryAction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.actions.back() = *v;
        }
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.action_type = static_cast<v748::ItemUseInventoryTransaction::ActionType>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.trigger_type = static_cast<v748::ItemUseInventoryTransaction::TriggerType>(*v);
    }
    {
        auto v = Serializer<base::NetworkBlockPosition>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.face = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::int32_t>(*v);
    }
    {
        auto v = Serializer<NetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.item = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.from_pos = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.click_pos = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.target_block_id = static_cast<BlockRuntimeId>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.client_predicted_result = static_cast<v748::ItemUseInventoryTransaction::PredictedResult>(*v);
    }
    return out;
}

void Serializer<legacy::v844::ItemUseInventoryTransaction>::serialize(BinaryWriter &stream, const legacy::v844::ItemUseInventoryTransaction &value)
{
    stream.writeVarInt<std::uint32_t>(value.actions.size());
    for (const auto &e0 : value.actions) {
        Serializer<v748::InventoryAction>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.action_type);
    stream.write<std::uint8_t>(value.trigger_type);
    Serializer<base::NetworkBlockPosition>::serialize(stream, value.pos);
    stream.writeVarInt<std::int32_t>(value.face);
    stream.writeVarInt<std::int32_t>(value.slot);
    Serializer<NetworkItemStackDescriptor>::serialize(stream, value.item);
    Serializer<Vec3>::serialize(stream, value.from_pos);
    Serializer<Vec3>::serialize(stream, value.click_pos);
    stream.writeVarInt<std::uint32_t>(value.target_block_id);
    stream.writeVarInt<std::uint32_t>(value.client_predicted_result);
}

auto Serializer<legacy::v844::ItemUseInventoryTransaction>::deserialize(BinaryReader &stream) -> std::expected<legacy::v844::ItemUseInventoryTransaction, std::error_code>
{
    legacy::v844::ItemUseInventoryTransaction out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.actions.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.actions.emplace_back();
            auto v = Serializer<v748::InventoryAction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.actions.back() = *v;
        }
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.action_type = static_cast<v844::ItemUseInventoryTransaction::ActionType>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.trigger_type = static_cast<v844::ItemUseInventoryTransaction::TriggerType>(*v);
    }
    {
        auto v = Serializer<base::NetworkBlockPosition>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.face = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::int32_t>(*v);
    }
    {
        auto v = Serializer<NetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.item = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.from_pos = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.click_pos = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.target_block_id = static_cast<BlockRuntimeId>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.client_predicted_result = static_cast<v844::ItemUseInventoryTransaction::PredictedResult>(*v);
    }
    return out;
}

void Serializer<legacy::v944::ItemUseInventoryTransaction>::serialize(BinaryWriter &stream, const legacy::v944::ItemUseInventoryTransaction &value)
{
    stream.writeVarInt<std::uint32_t>(value.actions.size());
    for (const auto &e0 : value.actions) {
        Serializer<v748::InventoryAction>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.action_type);
    stream.write<std::uint8_t>(value.trigger_type);
    Serializer<BlockPos>::serialize(stream, value.pos);
    stream.writeVarInt<std::int32_t>(value.face);
    stream.writeVarInt<std::int32_t>(value.slot);
    Serializer<NetworkItemStackDescriptor>::serialize(stream, value.item);
    Serializer<Vec3>::serialize(stream, value.from_pos);
    Serializer<Vec3>::serialize(stream, value.click_pos);
    stream.writeVarInt<std::uint32_t>(value.target_block_id);
    stream.writeVarInt<std::uint32_t>(value.client_predicted_result);
    stream.write<std::uint8_t>(value.client_cooldown_state);
}

auto Serializer<legacy::v944::ItemUseInventoryTransaction>::deserialize(BinaryReader &stream) -> std::expected<legacy::v944::ItemUseInventoryTransaction, std::error_code>
{
    legacy::v944::ItemUseInventoryTransaction out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.actions.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.actions.emplace_back();
            auto v = Serializer<v748::InventoryAction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.actions.back() = *v;
        }
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.action_type = static_cast<v944::ItemUseInventoryTransaction::ActionType>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.trigger_type = static_cast<v944::ItemUseInventoryTransaction::TriggerType>(*v);
    }
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.face = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::int32_t>(*v);
    }
    {
        auto v = Serializer<NetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.item = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.from_pos = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.click_pos = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.target_block_id = static_cast<BlockRuntimeId>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.client_predicted_result = static_cast<v944::ItemUseInventoryTransaction::PredictedResult>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.client_cooldown_state = static_cast<v944::ItemUseInventoryTransaction::ClientCooldownState>(*v);
    }
    return out;
}

void Serializer<legacy::v1001::ItemUseInventoryTransaction>::serialize(BinaryWriter &stream, const legacy::v1001::ItemUseInventoryTransaction &value)
{
    stream.writeVarInt<std::uint32_t>(value.actions.size());
    for (const auto &e0 : value.actions) {
        Serializer<v1001::InventoryAction>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.action_type);
    stream.write<std::uint8_t>(value.trigger_type);
    Serializer<BlockPos>::serialize(stream, value.pos);
    stream.writeVarInt<std::int32_t>(value.face);
    stream.writeVarInt<std::int32_t>(value.slot);
    Serializer<base::SerializedNetworkItemStackDescriptor>::serialize(stream, value.item);
    Serializer<Vec3>::serialize(stream, value.from_pos);
    Serializer<Vec3>::serialize(stream, value.click_pos);
    stream.writeVarInt<std::uint32_t>(value.target_block_id);
    stream.write<std::uint8_t>(value.client_predicted_result);
    stream.write<std::uint8_t>(value.client_cooldown_state);
}

auto Serializer<legacy::v1001::ItemUseInventoryTransaction>::deserialize(BinaryReader &stream) -> std::expected<legacy::v1001::ItemUseInventoryTransaction, std::error_code>
{
    legacy::v1001::ItemUseInventoryTransaction out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.actions.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.actions.emplace_back();
            auto v = Serializer<v1001::InventoryAction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.actions.back() = *v;
        }
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.action_type = static_cast<v1001::ItemUseInventoryTransaction::ActionType>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.trigger_type = static_cast<v1001::ItemUseInventoryTransaction::TriggerType>(*v);
    }
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.face = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::int32_t>(*v);
    }
    {
        auto v = Serializer<base::SerializedNetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.item = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.from_pos = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.click_pos = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.target_block_id = static_cast<BlockRuntimeId>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.client_predicted_result = static_cast<v1001::ItemUseInventoryTransaction::PredictedResult>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.client_cooldown_state = static_cast<v1001::ItemUseInventoryTransaction::ClientCooldownState>(*v);
    }
    return out;
}

void Serializer<legacy::v2168::ItemUseInventoryTransaction>::serialize(BinaryWriter &stream, const legacy::v2168::ItemUseInventoryTransaction &value)
{
    stream.writeVarInt<std::uint32_t>(value.actions.size());
    for (const auto &e0 : value.actions) {
        Serializer<v2168::InventoryAction>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.action_type);
    stream.write<std::uint8_t>(value.trigger_type);
    Serializer<BlockPos>::serialize(stream, value.pos);
    stream.writeVarInt<std::int32_t>(value.face);
    stream.writeVarInt<std::int32_t>(value.slot);
    Serializer<v2168::SerializedNetworkItemStackDescriptor>::serialize(stream, value.item);
    Serializer<Vec3>::serialize(stream, value.from_pos);
    Serializer<Vec3>::serialize(stream, value.click_pos);
    stream.writeVarInt<std::uint32_t>(value.target_block_id);
    stream.write<std::uint8_t>(value.client_predicted_result);
    stream.write<std::uint8_t>(value.client_cooldown_state);
}

auto Serializer<legacy::v2168::ItemUseInventoryTransaction>::deserialize(BinaryReader &stream) -> std::expected<legacy::v2168::ItemUseInventoryTransaction, std::error_code>
{
    legacy::v2168::ItemUseInventoryTransaction out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.actions.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.actions.emplace_back();
            auto v = Serializer<v2168::InventoryAction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.actions.back() = *v;
        }
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.action_type = static_cast<v2168::ItemUseInventoryTransaction::ActionType>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.trigger_type = static_cast<v2168::ItemUseInventoryTransaction::TriggerType>(*v);
    }
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.face = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::int32_t>(*v);
    }
    {
        auto v = Serializer<v2168::SerializedNetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.item = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.from_pos = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.click_pos = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.target_block_id = static_cast<BlockRuntimeId>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.client_predicted_result = static_cast<v2168::ItemUseInventoryTransaction::PredictedResult>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.client_cooldown_state = static_cast<v2168::ItemUseInventoryTransaction::ClientCooldownState>(*v);
    }
    return out;
}

void Serializer<legacy::v2193::ItemUseInventoryTransaction>::serialize(BinaryWriter &stream, const legacy::v2193::ItemUseInventoryTransaction &value)
{
    stream.writeVarInt<std::uint32_t>(value.actions.size());
    for (const auto &e0 : value.actions) {
        Serializer<v2193::InventoryAction>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.action_type);
    stream.write<std::uint8_t>(value.trigger_type);
    Serializer<BlockPos>::serialize(stream, value.pos);
    stream.writeVarInt<std::int32_t>(value.face);
    stream.writeVarInt<std::int32_t>(value.slot);
    Serializer<v2168::SerializedNetworkItemStackDescriptor>::serialize(stream, value.item);
    Serializer<Vec3>::serialize(stream, value.from_pos);
    Serializer<Vec3>::serialize(stream, value.click_pos);
    stream.writeVarInt<std::uint32_t>(value.target_block_id);
    stream.write<std::uint8_t>(value.client_predicted_result);
    stream.write<std::uint8_t>(value.client_cooldown_state);
}

auto Serializer<legacy::v2193::ItemUseInventoryTransaction>::deserialize(BinaryReader &stream) -> std::expected<legacy::v2193::ItemUseInventoryTransaction, std::error_code>
{
    legacy::v2193::ItemUseInventoryTransaction out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.actions.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.actions.emplace_back();
            auto v = Serializer<v2193::InventoryAction>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.actions.back() = *v;
        }
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.action_type = static_cast<v2193::ItemUseInventoryTransaction::ActionType>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.trigger_type = static_cast<v2193::ItemUseInventoryTransaction::TriggerType>(*v);
    }
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.face = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::int32_t>(*v);
    }
    {
        auto v = Serializer<v2168::SerializedNetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.item = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.from_pos = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.click_pos = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.target_block_id = static_cast<BlockRuntimeId>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.client_predicted_result = static_cast<v2193::ItemUseInventoryTransaction::PredictedResult>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.client_cooldown_state = static_cast<v2193::ItemUseInventoryTransaction::ClientCooldownState>(*v);
    }
    return out;
}

void Serializer<base::ItemUseOnActorInventoryTransaction>::serialize(BinaryWriter &stream, const base::ItemUseOnActorInventoryTransaction &value)
{
    Serializer<base::InventoryTransaction>::serialize(stream, value.transaction);
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    stream.writeVarInt<std::uint32_t>(value.action_type);
    stream.writeVarInt<std::int32_t>(value.slot);
    Serializer<NetworkItemStackDescriptor>::serialize(stream, value.item);
    Serializer<Vec3>::serialize(stream, value.from_pos);
    Serializer<Vec3>::serialize(stream, value.hit_pos);
}

auto Serializer<base::ItemUseOnActorInventoryTransaction>::deserialize(BinaryReader &stream) -> std::expected<base::ItemUseOnActorInventoryTransaction, std::error_code>
{
    base::ItemUseOnActorInventoryTransaction out;
    {
        auto v = Serializer<base::InventoryTransaction>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.transaction = *v;
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.action_type = static_cast<base::ItemUseOnActorInventoryTransaction::ActionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::int32_t>(*v);
    }
    {
        auto v = Serializer<NetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.item = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.from_pos = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.hit_pos = *v;
    }
    return out;
}

void Serializer<v748::ItemUseOnActorInventoryTransaction>::serialize(BinaryWriter &stream, const v748::ItemUseOnActorInventoryTransaction &value)
{
    Serializer<v748::InventoryTransaction>::serialize(stream, value.transaction);
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    stream.writeVarInt<std::uint32_t>(value.action_type);
    stream.writeVarInt<std::int32_t>(value.slot);
    Serializer<NetworkItemStackDescriptor>::serialize(stream, value.item);
    Serializer<Vec3>::serialize(stream, value.from_pos);
    Serializer<Vec3>::serialize(stream, value.hit_pos);
}

auto Serializer<v748::ItemUseOnActorInventoryTransaction>::deserialize(BinaryReader &stream) -> std::expected<v748::ItemUseOnActorInventoryTransaction, std::error_code>
{
    v748::ItemUseOnActorInventoryTransaction out;
    {
        auto v = Serializer<v748::InventoryTransaction>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.transaction = *v;
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.action_type = static_cast<v748::ItemUseOnActorInventoryTransaction::ActionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::int32_t>(*v);
    }
    {
        auto v = Serializer<NetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.item = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.from_pos = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.hit_pos = *v;
    }
    return out;
}

void Serializer<v1001::ItemUseOnActorInventoryTransaction>::serialize(BinaryWriter &stream, const v1001::ItemUseOnActorInventoryTransaction &value)
{
    Serializer<v1001::InventoryTransaction>::serialize(stream, value.transaction);
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    stream.writeVarInt<std::int32_t>(value.action_type);
    stream.writeVarInt<std::int32_t>(value.slot);
    Serializer<base::SerializedNetworkItemStackDescriptor>::serialize(stream, value.item);
    Serializer<Vec3>::serialize(stream, value.from_pos);
    Serializer<Vec3>::serialize(stream, value.hit_pos);
}

auto Serializer<v1001::ItemUseOnActorInventoryTransaction>::deserialize(BinaryReader &stream) -> std::expected<v1001::ItemUseOnActorInventoryTransaction, std::error_code>
{
    v1001::ItemUseOnActorInventoryTransaction out;
    {
        auto v = Serializer<v1001::InventoryTransaction>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.transaction = *v;
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.action_type = static_cast<v1001::ItemUseOnActorInventoryTransaction::ActionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::int32_t>(*v);
    }
    {
        auto v = Serializer<base::SerializedNetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.item = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.from_pos = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.hit_pos = *v;
    }
    return out;
}

void Serializer<v2168::ItemUseOnActorInventoryTransaction>::serialize(BinaryWriter &stream, const v2168::ItemUseOnActorInventoryTransaction &value)
{
    Serializer<v2168::InventoryTransaction>::serialize(stream, value.transaction);
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    stream.writeVarInt<std::int32_t>(value.action_type);
    stream.writeVarInt<std::int32_t>(value.slot);
    Serializer<v2168::SerializedNetworkItemStackDescriptor>::serialize(stream, value.item);
    Serializer<Vec3>::serialize(stream, value.from_pos);
    Serializer<Vec3>::serialize(stream, value.hit_pos);
}

auto Serializer<v2168::ItemUseOnActorInventoryTransaction>::deserialize(BinaryReader &stream) -> std::expected<v2168::ItemUseOnActorInventoryTransaction, std::error_code>
{
    v2168::ItemUseOnActorInventoryTransaction out;
    {
        auto v = Serializer<v2168::InventoryTransaction>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.transaction = *v;
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.action_type = static_cast<v2168::ItemUseOnActorInventoryTransaction::ActionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::int32_t>(*v);
    }
    {
        auto v = Serializer<v2168::SerializedNetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.item = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.from_pos = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.hit_pos = *v;
    }
    return out;
}

void Serializer<v2193::ItemUseOnActorInventoryTransaction>::serialize(BinaryWriter &stream, const v2193::ItemUseOnActorInventoryTransaction &value)
{
    Serializer<v2193::InventoryTransaction>::serialize(stream, value.transaction);
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    stream.writeVarInt<std::int32_t>(value.action_type);
    stream.writeVarInt<std::int32_t>(value.slot);
    Serializer<v2168::SerializedNetworkItemStackDescriptor>::serialize(stream, value.item);
    Serializer<Vec3>::serialize(stream, value.from_pos);
    Serializer<Vec3>::serialize(stream, value.hit_pos);
}

auto Serializer<v2193::ItemUseOnActorInventoryTransaction>::deserialize(BinaryReader &stream) -> std::expected<v2193::ItemUseOnActorInventoryTransaction, std::error_code>
{
    v2193::ItemUseOnActorInventoryTransaction out;
    {
        auto v = Serializer<v2193::InventoryTransaction>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.transaction = *v;
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.action_type = static_cast<v2193::ItemUseOnActorInventoryTransaction::ActionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::int32_t>(*v);
    }
    {
        auto v = Serializer<v2168::SerializedNetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.item = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.from_pos = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.hit_pos = *v;
    }
    return out;
}

void Serializer<v2225::ItemUseOnActorInventoryTransaction>::serialize(BinaryWriter &stream, const v2225::ItemUseOnActorInventoryTransaction &value)
{
    Serializer<v2193::InventoryTransaction>::serialize(stream, value.transaction);
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    stream.writeVarInt<std::int32_t>(value.action_type);
    stream.writeVarInt<std::int32_t>(value.slot);
    stream.write<std::uint8_t>(value.hand);
    Serializer<v2168::SerializedNetworkItemStackDescriptor>::serialize(stream, value.item);
    Serializer<Vec3>::serialize(stream, value.from_pos);
    Serializer<Vec3>::serialize(stream, value.hit_pos);
}

auto Serializer<v2225::ItemUseOnActorInventoryTransaction>::deserialize(BinaryReader &stream) -> std::expected<v2225::ItemUseOnActorInventoryTransaction, std::error_code>
{
    v2225::ItemUseOnActorInventoryTransaction out;
    {
        auto v = Serializer<v2193::InventoryTransaction>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.transaction = *v;
    }
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.action_type = static_cast<v2225::ItemUseOnActorInventoryTransaction::ActionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.hand = static_cast<HandSlot>(*v);
    }
    {
        auto v = Serializer<v2168::SerializedNetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.item = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.from_pos = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.hit_pos = *v;
    }
    return out;
}

void Serializer<base::ItemReleaseInventoryTransaction>::serialize(BinaryWriter &stream, const base::ItemReleaseInventoryTransaction &value)
{
    Serializer<base::InventoryTransaction>::serialize(stream, value.transaction);
    stream.writeVarInt<std::uint32_t>(value.action_type);
    stream.writeVarInt<std::int32_t>(value.slot);
    Serializer<NetworkItemStackDescriptor>::serialize(stream, value.item);
    Serializer<Vec3>::serialize(stream, value.from_pos);
}

auto Serializer<base::ItemReleaseInventoryTransaction>::deserialize(BinaryReader &stream) -> std::expected<base::ItemReleaseInventoryTransaction, std::error_code>
{
    base::ItemReleaseInventoryTransaction out;
    {
        auto v = Serializer<base::InventoryTransaction>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.transaction = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.action_type = static_cast<base::ItemReleaseInventoryTransaction::ActionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::int32_t>(*v);
    }
    {
        auto v = Serializer<NetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.item = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.from_pos = *v;
    }
    return out;
}

void Serializer<v748::ItemReleaseInventoryTransaction>::serialize(BinaryWriter &stream, const v748::ItemReleaseInventoryTransaction &value)
{
    Serializer<v748::InventoryTransaction>::serialize(stream, value.transaction);
    stream.writeVarInt<std::uint32_t>(value.action_type);
    stream.writeVarInt<std::int32_t>(value.slot);
    Serializer<NetworkItemStackDescriptor>::serialize(stream, value.item);
    Serializer<Vec3>::serialize(stream, value.from_pos);
}

auto Serializer<v748::ItemReleaseInventoryTransaction>::deserialize(BinaryReader &stream) -> std::expected<v748::ItemReleaseInventoryTransaction, std::error_code>
{
    v748::ItemReleaseInventoryTransaction out;
    {
        auto v = Serializer<v748::InventoryTransaction>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.transaction = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.action_type = static_cast<v748::ItemReleaseInventoryTransaction::ActionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::int32_t>(*v);
    }
    {
        auto v = Serializer<NetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.item = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.from_pos = *v;
    }
    return out;
}

void Serializer<v1001::ItemReleaseInventoryTransaction>::serialize(BinaryWriter &stream, const v1001::ItemReleaseInventoryTransaction &value)
{
    Serializer<v1001::InventoryTransaction>::serialize(stream, value.transaction);
    stream.writeVarInt<std::int32_t>(value.action_type);
    stream.writeVarInt<std::int32_t>(value.slot);
    Serializer<base::SerializedNetworkItemStackDescriptor>::serialize(stream, value.item);
    Serializer<Vec3>::serialize(stream, value.from_pos);
}

auto Serializer<v1001::ItemReleaseInventoryTransaction>::deserialize(BinaryReader &stream) -> std::expected<v1001::ItemReleaseInventoryTransaction, std::error_code>
{
    v1001::ItemReleaseInventoryTransaction out;
    {
        auto v = Serializer<v1001::InventoryTransaction>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.transaction = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.action_type = static_cast<v1001::ItemReleaseInventoryTransaction::ActionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::int32_t>(*v);
    }
    {
        auto v = Serializer<base::SerializedNetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.item = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.from_pos = *v;
    }
    return out;
}

void Serializer<v2168::ItemReleaseInventoryTransaction>::serialize(BinaryWriter &stream, const v2168::ItemReleaseInventoryTransaction &value)
{
    Serializer<v2168::InventoryTransaction>::serialize(stream, value.transaction);
    stream.writeVarInt<std::int32_t>(value.action_type);
    stream.writeVarInt<std::int32_t>(value.slot);
    Serializer<v2168::SerializedNetworkItemStackDescriptor>::serialize(stream, value.item);
    Serializer<Vec3>::serialize(stream, value.from_pos);
}

auto Serializer<v2168::ItemReleaseInventoryTransaction>::deserialize(BinaryReader &stream) -> std::expected<v2168::ItemReleaseInventoryTransaction, std::error_code>
{
    v2168::ItemReleaseInventoryTransaction out;
    {
        auto v = Serializer<v2168::InventoryTransaction>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.transaction = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.action_type = static_cast<v2168::ItemReleaseInventoryTransaction::ActionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::int32_t>(*v);
    }
    {
        auto v = Serializer<v2168::SerializedNetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.item = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.from_pos = *v;
    }
    return out;
}

void Serializer<v2193::ItemReleaseInventoryTransaction>::serialize(BinaryWriter &stream, const v2193::ItemReleaseInventoryTransaction &value)
{
    Serializer<v2193::InventoryTransaction>::serialize(stream, value.transaction);
    stream.writeVarInt<std::int32_t>(value.action_type);
    stream.writeVarInt<std::int32_t>(value.slot);
    Serializer<v2168::SerializedNetworkItemStackDescriptor>::serialize(stream, value.item);
    Serializer<Vec3>::serialize(stream, value.from_pos);
}

auto Serializer<v2193::ItemReleaseInventoryTransaction>::deserialize(BinaryReader &stream) -> std::expected<v2193::ItemReleaseInventoryTransaction, std::error_code>
{
    v2193::ItemReleaseInventoryTransaction out;
    {
        auto v = Serializer<v2193::InventoryTransaction>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.transaction = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.action_type = static_cast<v2193::ItemReleaseInventoryTransaction::ActionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::int32_t>(*v);
    }
    {
        auto v = Serializer<v2168::SerializedNetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.item = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.from_pos = *v;
    }
    return out;
}

void Serializer<v2225::ItemReleaseInventoryTransaction>::serialize(BinaryWriter &stream, const v2225::ItemReleaseInventoryTransaction &value)
{
    Serializer<v2193::InventoryTransaction>::serialize(stream, value.transaction);
    stream.writeVarInt<std::int32_t>(value.action_type);
    stream.writeVarInt<std::int32_t>(value.slot);
    Serializer<v2168::SerializedNetworkItemStackDescriptor>::serialize(stream, value.item);
    Serializer<Vec3>::serialize(stream, value.from_pos);
    stream.write<std::uint8_t>(value.hand);
}

auto Serializer<v2225::ItemReleaseInventoryTransaction>::deserialize(BinaryReader &stream) -> std::expected<v2225::ItemReleaseInventoryTransaction, std::error_code>
{
    v2225::ItemReleaseInventoryTransaction out;
    {
        auto v = Serializer<v2193::InventoryTransaction>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.transaction = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.action_type = static_cast<v2225::ItemReleaseInventoryTransaction::ActionType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::int32_t>(*v);
    }
    {
        auto v = Serializer<v2168::SerializedNetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.item = *v;
    }
    {
        auto v = Serializer<Vec3>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.from_pos = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.hand = static_cast<HandSlot>(*v);
    }
    return out;
}

void Serializer<base::InventoryTransactionPacket>::serialize(BinaryWriter &stream, const base::InventoryTransactionPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.legacy_request_id);
    if ((value.legacy_request_id) != (0)) {
        stream.writeVarInt<std::uint32_t>(value.legacy_set_item_slots.size());
        for (const auto &e0 : value.legacy_set_item_slots) {
            Serializer<base::LegacySetSlot>::serialize(stream, e0);
        }
    }
    stream.writeVarInt<std::uint32_t>((value.transaction).index());
    switch ((value.transaction).index()) {
        case 0: {
            Serializer<base::NormalTransactionData>::serialize(stream, std::get<0>(value.transaction));
            break;
        }
        case 1: {
            Serializer<base::InventoryMismatchData>::serialize(stream, std::get<1>(value.transaction));
            break;
        }
        case 2: {
            Serializer<base::ItemUseInventoryTransaction>::serialize(stream, std::get<2>(value.transaction));
            break;
        }
        case 3: {
            Serializer<base::ItemUseOnActorInventoryTransaction>::serialize(stream, std::get<3>(value.transaction));
            break;
        }
        case 4: {
            Serializer<base::ItemReleaseInventoryTransaction>::serialize(stream, std::get<4>(value.transaction));
            break;
        }
    }
}

auto Serializer<base::InventoryTransactionPacket>::deserialize(BinaryReader &stream) -> std::expected<base::InventoryTransactionPacket, std::error_code>
{
    base::InventoryTransactionPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.legacy_request_id = static_cast<std::int32_t>(*v);
    }
    if ((out.legacy_request_id) != (0)) {
        {
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            out.legacy_set_item_slots.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                out.legacy_set_item_slots.emplace_back();
                auto v = Serializer<base::LegacySetSlot>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                out.legacy_set_item_slots.back() = *v;
            }
        }
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<base::NormalTransactionData, base::InventoryMismatchData, base::ItemUseInventoryTransaction, base::ItemUseOnActorInventoryTransaction, base::ItemReleaseInventoryTransaction> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<base::NormalTransactionData, base::InventoryMismatchData, base::ItemUseInventoryTransaction, base::ItemUseOnActorInventoryTransaction, base::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<base::NormalTransactionData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<base::NormalTransactionData, base::InventoryMismatchData, base::ItemUseInventoryTransaction, base::ItemUseOnActorInventoryTransaction, base::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<base::InventoryMismatchData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<base::NormalTransactionData, base::InventoryMismatchData, base::ItemUseInventoryTransaction, base::ItemUseOnActorInventoryTransaction, base::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<base::ItemUseInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<base::NormalTransactionData, base::InventoryMismatchData, base::ItemUseInventoryTransaction, base::ItemUseOnActorInventoryTransaction, base::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<base::ItemUseOnActorInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            case 4: {
                std::variant_alternative_t<4, std::variant<base::NormalTransactionData, base::InventoryMismatchData, base::ItemUseInventoryTransaction, base::ItemUseOnActorInventoryTransaction, base::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<base::ItemReleaseInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<4>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.transaction = var0;
    }
    return out;
}

void Serializer<v748::InventoryTransactionPacket>::serialize(BinaryWriter &stream, const v748::InventoryTransactionPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.legacy_request_id);
    if ((value.legacy_request_id) != (0)) {
        stream.writeVarInt<std::uint32_t>(value.legacy_set_item_slots.size());
        for (const auto &e0 : value.legacy_set_item_slots) {
            Serializer<base::LegacySetSlot>::serialize(stream, e0);
        }
    }
    stream.writeVarInt<std::uint32_t>((value.transaction).index());
    switch ((value.transaction).index()) {
        case 0: {
            Serializer<v748::NormalTransactionData>::serialize(stream, std::get<0>(value.transaction));
            break;
        }
        case 1: {
            Serializer<v748::InventoryMismatchData>::serialize(stream, std::get<1>(value.transaction));
            break;
        }
        case 2: {
            Serializer<v748::ItemUseInventoryTransaction>::serialize(stream, std::get<2>(value.transaction));
            break;
        }
        case 3: {
            Serializer<v748::ItemUseOnActorInventoryTransaction>::serialize(stream, std::get<3>(value.transaction));
            break;
        }
        case 4: {
            Serializer<v748::ItemReleaseInventoryTransaction>::serialize(stream, std::get<4>(value.transaction));
            break;
        }
    }
}

auto Serializer<v748::InventoryTransactionPacket>::deserialize(BinaryReader &stream) -> std::expected<v748::InventoryTransactionPacket, std::error_code>
{
    v748::InventoryTransactionPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.legacy_request_id = static_cast<std::int32_t>(*v);
    }
    if ((out.legacy_request_id) != (0)) {
        {
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            out.legacy_set_item_slots.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                out.legacy_set_item_slots.emplace_back();
                auto v = Serializer<base::LegacySetSlot>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                out.legacy_set_item_slots.back() = *v;
            }
        }
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v748::NormalTransactionData, v748::InventoryMismatchData, v748::ItemUseInventoryTransaction, v748::ItemUseOnActorInventoryTransaction, v748::ItemReleaseInventoryTransaction> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v748::NormalTransactionData, v748::InventoryMismatchData, v748::ItemUseInventoryTransaction, v748::ItemUseOnActorInventoryTransaction, v748::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v748::NormalTransactionData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v748::NormalTransactionData, v748::InventoryMismatchData, v748::ItemUseInventoryTransaction, v748::ItemUseOnActorInventoryTransaction, v748::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v748::InventoryMismatchData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<v748::NormalTransactionData, v748::InventoryMismatchData, v748::ItemUseInventoryTransaction, v748::ItemUseOnActorInventoryTransaction, v748::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v748::ItemUseInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<v748::NormalTransactionData, v748::InventoryMismatchData, v748::ItemUseInventoryTransaction, v748::ItemUseOnActorInventoryTransaction, v748::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v748::ItemUseOnActorInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            case 4: {
                std::variant_alternative_t<4, std::variant<v748::NormalTransactionData, v748::InventoryMismatchData, v748::ItemUseInventoryTransaction, v748::ItemUseOnActorInventoryTransaction, v748::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v748::ItemReleaseInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<4>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.transaction = var0;
    }
    return out;
}

void Serializer<v844::InventoryTransactionPacket>::serialize(BinaryWriter &stream, const v844::InventoryTransactionPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.legacy_request_id);
    if ((value.legacy_request_id) != (0)) {
        stream.writeVarInt<std::uint32_t>(value.legacy_set_item_slots.size());
        for (const auto &e0 : value.legacy_set_item_slots) {
            Serializer<base::LegacySetSlot>::serialize(stream, e0);
        }
    }
    stream.writeVarInt<std::uint32_t>((value.transaction).index());
    switch ((value.transaction).index()) {
        case 0: {
            Serializer<v748::NormalTransactionData>::serialize(stream, std::get<0>(value.transaction));
            break;
        }
        case 1: {
            Serializer<v748::InventoryMismatchData>::serialize(stream, std::get<1>(value.transaction));
            break;
        }
        case 2: {
            Serializer<v844::ItemUseInventoryTransaction>::serialize(stream, std::get<2>(value.transaction));
            break;
        }
        case 3: {
            Serializer<v748::ItemUseOnActorInventoryTransaction>::serialize(stream, std::get<3>(value.transaction));
            break;
        }
        case 4: {
            Serializer<v748::ItemReleaseInventoryTransaction>::serialize(stream, std::get<4>(value.transaction));
            break;
        }
    }
}

auto Serializer<v844::InventoryTransactionPacket>::deserialize(BinaryReader &stream) -> std::expected<v844::InventoryTransactionPacket, std::error_code>
{
    v844::InventoryTransactionPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.legacy_request_id = static_cast<std::int32_t>(*v);
    }
    if ((out.legacy_request_id) != (0)) {
        {
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            out.legacy_set_item_slots.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                out.legacy_set_item_slots.emplace_back();
                auto v = Serializer<base::LegacySetSlot>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                out.legacy_set_item_slots.back() = *v;
            }
        }
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v748::NormalTransactionData, v748::InventoryMismatchData, v844::ItemUseInventoryTransaction, v748::ItemUseOnActorInventoryTransaction, v748::ItemReleaseInventoryTransaction> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v748::NormalTransactionData, v748::InventoryMismatchData, v844::ItemUseInventoryTransaction, v748::ItemUseOnActorInventoryTransaction, v748::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v748::NormalTransactionData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v748::NormalTransactionData, v748::InventoryMismatchData, v844::ItemUseInventoryTransaction, v748::ItemUseOnActorInventoryTransaction, v748::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v748::InventoryMismatchData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<v748::NormalTransactionData, v748::InventoryMismatchData, v844::ItemUseInventoryTransaction, v748::ItemUseOnActorInventoryTransaction, v748::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v844::ItemUseInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<v748::NormalTransactionData, v748::InventoryMismatchData, v844::ItemUseInventoryTransaction, v748::ItemUseOnActorInventoryTransaction, v748::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v748::ItemUseOnActorInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            case 4: {
                std::variant_alternative_t<4, std::variant<v748::NormalTransactionData, v748::InventoryMismatchData, v844::ItemUseInventoryTransaction, v748::ItemUseOnActorInventoryTransaction, v748::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v748::ItemReleaseInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<4>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.transaction = var0;
    }
    return out;
}

void Serializer<v924::InventoryTransactionPacket>::serialize(BinaryWriter &stream, const v924::InventoryTransactionPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.legacy_request_id);
    if ((value.legacy_request_id) != (0)) {
        stream.writeVarInt<std::uint32_t>(value.legacy_set_item_slots.size());
        for (const auto &e0 : value.legacy_set_item_slots) {
            Serializer<v924::LegacySetSlot>::serialize(stream, e0);
        }
    }
    stream.writeVarInt<std::uint32_t>((value.transaction).index());
    switch ((value.transaction).index()) {
        case 0: {
            Serializer<v748::NormalTransactionData>::serialize(stream, std::get<0>(value.transaction));
            break;
        }
        case 1: {
            Serializer<v748::InventoryMismatchData>::serialize(stream, std::get<1>(value.transaction));
            break;
        }
        case 2: {
            Serializer<v844::ItemUseInventoryTransaction>::serialize(stream, std::get<2>(value.transaction));
            break;
        }
        case 3: {
            Serializer<v748::ItemUseOnActorInventoryTransaction>::serialize(stream, std::get<3>(value.transaction));
            break;
        }
        case 4: {
            Serializer<v748::ItemReleaseInventoryTransaction>::serialize(stream, std::get<4>(value.transaction));
            break;
        }
    }
}

auto Serializer<v924::InventoryTransactionPacket>::deserialize(BinaryReader &stream) -> std::expected<v924::InventoryTransactionPacket, std::error_code>
{
    v924::InventoryTransactionPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.legacy_request_id = static_cast<std::int32_t>(*v);
    }
    if ((out.legacy_request_id) != (0)) {
        {
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            out.legacy_set_item_slots.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                out.legacy_set_item_slots.emplace_back();
                auto v = Serializer<v924::LegacySetSlot>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                out.legacy_set_item_slots.back() = *v;
            }
        }
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v748::NormalTransactionData, v748::InventoryMismatchData, v844::ItemUseInventoryTransaction, v748::ItemUseOnActorInventoryTransaction, v748::ItemReleaseInventoryTransaction> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v748::NormalTransactionData, v748::InventoryMismatchData, v844::ItemUseInventoryTransaction, v748::ItemUseOnActorInventoryTransaction, v748::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v748::NormalTransactionData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v748::NormalTransactionData, v748::InventoryMismatchData, v844::ItemUseInventoryTransaction, v748::ItemUseOnActorInventoryTransaction, v748::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v748::InventoryMismatchData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<v748::NormalTransactionData, v748::InventoryMismatchData, v844::ItemUseInventoryTransaction, v748::ItemUseOnActorInventoryTransaction, v748::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v844::ItemUseInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<v748::NormalTransactionData, v748::InventoryMismatchData, v844::ItemUseInventoryTransaction, v748::ItemUseOnActorInventoryTransaction, v748::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v748::ItemUseOnActorInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            case 4: {
                std::variant_alternative_t<4, std::variant<v748::NormalTransactionData, v748::InventoryMismatchData, v844::ItemUseInventoryTransaction, v748::ItemUseOnActorInventoryTransaction, v748::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v748::ItemReleaseInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<4>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.transaction = var0;
    }
    return out;
}

void Serializer<v944::InventoryTransactionPacket>::serialize(BinaryWriter &stream, const v944::InventoryTransactionPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.legacy_request_id);
    if ((value.legacy_request_id) != (0)) {
        stream.writeVarInt<std::uint32_t>(value.legacy_set_item_slots.size());
        for (const auto &e0 : value.legacy_set_item_slots) {
            Serializer<v924::LegacySetSlot>::serialize(stream, e0);
        }
    }
    stream.writeVarInt<std::uint32_t>((value.transaction).index());
    switch ((value.transaction).index()) {
        case 0: {
            Serializer<v748::NormalTransactionData>::serialize(stream, std::get<0>(value.transaction));
            break;
        }
        case 1: {
            Serializer<v748::InventoryMismatchData>::serialize(stream, std::get<1>(value.transaction));
            break;
        }
        case 2: {
            Serializer<v944::ItemUseInventoryTransaction>::serialize(stream, std::get<2>(value.transaction));
            break;
        }
        case 3: {
            Serializer<v748::ItemUseOnActorInventoryTransaction>::serialize(stream, std::get<3>(value.transaction));
            break;
        }
        case 4: {
            Serializer<v748::ItemReleaseInventoryTransaction>::serialize(stream, std::get<4>(value.transaction));
            break;
        }
    }
}

auto Serializer<v944::InventoryTransactionPacket>::deserialize(BinaryReader &stream) -> std::expected<v944::InventoryTransactionPacket, std::error_code>
{
    v944::InventoryTransactionPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.legacy_request_id = static_cast<std::int32_t>(*v);
    }
    if ((out.legacy_request_id) != (0)) {
        {
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            out.legacy_set_item_slots.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                out.legacy_set_item_slots.emplace_back();
                auto v = Serializer<v924::LegacySetSlot>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                out.legacy_set_item_slots.back() = *v;
            }
        }
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v748::NormalTransactionData, v748::InventoryMismatchData, v944::ItemUseInventoryTransaction, v748::ItemUseOnActorInventoryTransaction, v748::ItemReleaseInventoryTransaction> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v748::NormalTransactionData, v748::InventoryMismatchData, v944::ItemUseInventoryTransaction, v748::ItemUseOnActorInventoryTransaction, v748::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v748::NormalTransactionData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v748::NormalTransactionData, v748::InventoryMismatchData, v944::ItemUseInventoryTransaction, v748::ItemUseOnActorInventoryTransaction, v748::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v748::InventoryMismatchData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<v748::NormalTransactionData, v748::InventoryMismatchData, v944::ItemUseInventoryTransaction, v748::ItemUseOnActorInventoryTransaction, v748::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v944::ItemUseInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<v748::NormalTransactionData, v748::InventoryMismatchData, v944::ItemUseInventoryTransaction, v748::ItemUseOnActorInventoryTransaction, v748::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v748::ItemUseOnActorInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            case 4: {
                std::variant_alternative_t<4, std::variant<v748::NormalTransactionData, v748::InventoryMismatchData, v944::ItemUseInventoryTransaction, v748::ItemUseOnActorInventoryTransaction, v748::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v748::ItemReleaseInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<4>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.transaction = var0;
    }
    return out;
}

void Serializer<v1001::InventoryTransactionPacket>::serialize(BinaryWriter &stream, const v1001::InventoryTransactionPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.legacy_request_id);
    stream.write<bool>(value.legacy_set_item_slots.has_value());
    if (value.legacy_set_item_slots.has_value()) {
        stream.writeVarInt<std::uint32_t>((*value.legacy_set_item_slots).size());
        for (const auto &e0 : (*value.legacy_set_item_slots)) {
            Serializer<v924::LegacySetSlot>::serialize(stream, e0);
        }
    }
    stream.write<bool>(true);
    stream.writeVarInt<std::uint32_t>((value.transaction).index());
    switch ((value.transaction).index()) {
        case 0: {
            Serializer<v1001::NormalTransactionData>::serialize(stream, std::get<0>(value.transaction));
            break;
        }
        case 1: {
            Serializer<v1001::InventoryMismatchData>::serialize(stream, std::get<1>(value.transaction));
            break;
        }
        case 2: {
            Serializer<v1001::ItemUseInventoryTransaction>::serialize(stream, std::get<2>(value.transaction));
            break;
        }
        case 3: {
            Serializer<v1001::ItemUseOnActorInventoryTransaction>::serialize(stream, std::get<3>(value.transaction));
            break;
        }
        case 4: {
            Serializer<v1001::ItemReleaseInventoryTransaction>::serialize(stream, std::get<4>(value.transaction));
            break;
        }
    }
}

auto Serializer<v1001::InventoryTransactionPacket>::deserialize(BinaryReader &stream) -> std::expected<v1001::InventoryTransactionPacket, std::error_code>
{
    v1001::InventoryTransactionPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.legacy_request_id = static_cast<std::int32_t>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::vector<v924::LegacySetSlot> staged{};
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            staged.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                staged.emplace_back();
                auto v = Serializer<v924::LegacySetSlot>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                staged.back() = *v;
            }
            out.legacy_set_item_slots = std::move(staged);
        }
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        if (*v != true) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v1001::NormalTransactionData, v1001::InventoryMismatchData, v1001::ItemUseInventoryTransaction, v1001::ItemUseOnActorInventoryTransaction, v1001::ItemReleaseInventoryTransaction> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v1001::NormalTransactionData, v1001::InventoryMismatchData, v1001::ItemUseInventoryTransaction, v1001::ItemUseOnActorInventoryTransaction, v1001::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v1001::NormalTransactionData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v1001::NormalTransactionData, v1001::InventoryMismatchData, v1001::ItemUseInventoryTransaction, v1001::ItemUseOnActorInventoryTransaction, v1001::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v1001::InventoryMismatchData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<v1001::NormalTransactionData, v1001::InventoryMismatchData, v1001::ItemUseInventoryTransaction, v1001::ItemUseOnActorInventoryTransaction, v1001::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v1001::ItemUseInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<v1001::NormalTransactionData, v1001::InventoryMismatchData, v1001::ItemUseInventoryTransaction, v1001::ItemUseOnActorInventoryTransaction, v1001::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v1001::ItemUseOnActorInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            case 4: {
                std::variant_alternative_t<4, std::variant<v1001::NormalTransactionData, v1001::InventoryMismatchData, v1001::ItemUseInventoryTransaction, v1001::ItemUseOnActorInventoryTransaction, v1001::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v1001::ItemReleaseInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<4>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.transaction = var0;
    }
    return out;
}

void Serializer<v2168::InventoryTransactionPacket>::serialize(BinaryWriter &stream, const v2168::InventoryTransactionPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.legacy_request_id);
    stream.write<bool>(value.legacy_set_item_slots.has_value());
    if (value.legacy_set_item_slots.has_value()) {
        stream.writeVarInt<std::uint32_t>((*value.legacy_set_item_slots).size());
        for (const auto &e0 : (*value.legacy_set_item_slots)) {
            Serializer<v924::LegacySetSlot>::serialize(stream, e0);
        }
    }
    stream.write<bool>(true);
    stream.writeVarInt<std::uint32_t>((value.transaction).index());
    switch ((value.transaction).index()) {
        case 0: {
            Serializer<v2168::NormalTransactionData>::serialize(stream, std::get<0>(value.transaction));
            break;
        }
        case 1: {
            Serializer<v2168::InventoryMismatchData>::serialize(stream, std::get<1>(value.transaction));
            break;
        }
        case 2: {
            Serializer<v2168::ItemUseInventoryTransaction>::serialize(stream, std::get<2>(value.transaction));
            break;
        }
        case 3: {
            Serializer<v2168::ItemUseOnActorInventoryTransaction>::serialize(stream, std::get<3>(value.transaction));
            break;
        }
        case 4: {
            Serializer<v2168::ItemReleaseInventoryTransaction>::serialize(stream, std::get<4>(value.transaction));
            break;
        }
    }
}

auto Serializer<v2168::InventoryTransactionPacket>::deserialize(BinaryReader &stream) -> std::expected<v2168::InventoryTransactionPacket, std::error_code>
{
    v2168::InventoryTransactionPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.legacy_request_id = static_cast<std::int32_t>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::vector<v924::LegacySetSlot> staged{};
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            staged.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                staged.emplace_back();
                auto v = Serializer<v924::LegacySetSlot>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                staged.back() = *v;
            }
            out.legacy_set_item_slots = std::move(staged);
        }
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        if (*v != true) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v2168::NormalTransactionData, v2168::InventoryMismatchData, v2168::ItemUseInventoryTransaction, v2168::ItemUseOnActorInventoryTransaction, v2168::ItemReleaseInventoryTransaction> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v2168::NormalTransactionData, v2168::InventoryMismatchData, v2168::ItemUseInventoryTransaction, v2168::ItemUseOnActorInventoryTransaction, v2168::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v2168::NormalTransactionData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v2168::NormalTransactionData, v2168::InventoryMismatchData, v2168::ItemUseInventoryTransaction, v2168::ItemUseOnActorInventoryTransaction, v2168::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v2168::InventoryMismatchData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<v2168::NormalTransactionData, v2168::InventoryMismatchData, v2168::ItemUseInventoryTransaction, v2168::ItemUseOnActorInventoryTransaction, v2168::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v2168::ItemUseInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<v2168::NormalTransactionData, v2168::InventoryMismatchData, v2168::ItemUseInventoryTransaction, v2168::ItemUseOnActorInventoryTransaction, v2168::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v2168::ItemUseOnActorInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            case 4: {
                std::variant_alternative_t<4, std::variant<v2168::NormalTransactionData, v2168::InventoryMismatchData, v2168::ItemUseInventoryTransaction, v2168::ItemUseOnActorInventoryTransaction, v2168::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v2168::ItemReleaseInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<4>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.transaction = var0;
    }
    return out;
}

void Serializer<v2193::InventoryTransactionPacket>::serialize(BinaryWriter &stream, const v2193::InventoryTransactionPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.legacy_request_id);
    stream.write<bool>(value.legacy_set_item_slots.has_value());
    if (value.legacy_set_item_slots.has_value()) {
        stream.writeVarInt<std::uint32_t>((*value.legacy_set_item_slots).size());
        for (const auto &e0 : (*value.legacy_set_item_slots)) {
            Serializer<v924::LegacySetSlot>::serialize(stream, e0);
        }
    }
    stream.writeVarInt<std::uint32_t>((value.transaction).index());
    switch ((value.transaction).index()) {
        case 0: {
            Serializer<v2193::NormalTransactionData>::serialize(stream, std::get<0>(value.transaction));
            break;
        }
        case 1: {
            Serializer<v2193::InventoryMismatchData>::serialize(stream, std::get<1>(value.transaction));
            break;
        }
        case 2: {
            Serializer<v2193::ItemUseInventoryTransaction>::serialize(stream, std::get<2>(value.transaction));
            break;
        }
        case 3: {
            Serializer<v2193::ItemUseOnActorInventoryTransaction>::serialize(stream, std::get<3>(value.transaction));
            break;
        }
        case 4: {
            Serializer<v2193::ItemReleaseInventoryTransaction>::serialize(stream, std::get<4>(value.transaction));
            break;
        }
    }
}

auto Serializer<v2193::InventoryTransactionPacket>::deserialize(BinaryReader &stream) -> std::expected<v2193::InventoryTransactionPacket, std::error_code>
{
    v2193::InventoryTransactionPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.legacy_request_id = static_cast<std::int32_t>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::vector<v924::LegacySetSlot> staged{};
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            staged.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                staged.emplace_back();
                auto v = Serializer<v924::LegacySetSlot>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                staged.back() = *v;
            }
            out.legacy_set_item_slots = std::move(staged);
        }
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v2193::NormalTransactionData, v2193::InventoryMismatchData, v2193::ItemUseInventoryTransaction, v2193::ItemUseOnActorInventoryTransaction, v2193::ItemReleaseInventoryTransaction> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v2193::NormalTransactionData, v2193::InventoryMismatchData, v2193::ItemUseInventoryTransaction, v2193::ItemUseOnActorInventoryTransaction, v2193::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v2193::NormalTransactionData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v2193::NormalTransactionData, v2193::InventoryMismatchData, v2193::ItemUseInventoryTransaction, v2193::ItemUseOnActorInventoryTransaction, v2193::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v2193::InventoryMismatchData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<v2193::NormalTransactionData, v2193::InventoryMismatchData, v2193::ItemUseInventoryTransaction, v2193::ItemUseOnActorInventoryTransaction, v2193::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v2193::ItemUseInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<v2193::NormalTransactionData, v2193::InventoryMismatchData, v2193::ItemUseInventoryTransaction, v2193::ItemUseOnActorInventoryTransaction, v2193::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v2193::ItemUseOnActorInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            case 4: {
                std::variant_alternative_t<4, std::variant<v2193::NormalTransactionData, v2193::InventoryMismatchData, v2193::ItemUseInventoryTransaction, v2193::ItemUseOnActorInventoryTransaction, v2193::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v2193::ItemReleaseInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<4>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.transaction = var0;
    }
    return out;
}

void Serializer<v2225::InventoryTransactionPacket>::serialize(BinaryWriter &stream, const v2225::InventoryTransactionPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.legacy_request_id);
    stream.write<bool>(value.legacy_set_item_slots.has_value());
    if (value.legacy_set_item_slots.has_value()) {
        stream.writeVarInt<std::uint32_t>((*value.legacy_set_item_slots).size());
        for (const auto &e0 : (*value.legacy_set_item_slots)) {
            Serializer<v2225::LegacySetSlot>::serialize(stream, e0);
        }
    }
    stream.writeVarInt<std::uint32_t>((value.transaction).index());
    switch ((value.transaction).index()) {
        case 0: {
            Serializer<v2193::NormalTransactionData>::serialize(stream, std::get<0>(value.transaction));
            break;
        }
        case 1: {
            Serializer<v2193::InventoryMismatchData>::serialize(stream, std::get<1>(value.transaction));
            break;
        }
        case 2: {
            Serializer<v2193::ItemUseInventoryTransaction>::serialize(stream, std::get<2>(value.transaction));
            break;
        }
        case 3: {
            Serializer<v2225::ItemUseOnActorInventoryTransaction>::serialize(stream, std::get<3>(value.transaction));
            break;
        }
        case 4: {
            Serializer<v2225::ItemReleaseInventoryTransaction>::serialize(stream, std::get<4>(value.transaction));
            break;
        }
    }
}

auto Serializer<v2225::InventoryTransactionPacket>::deserialize(BinaryReader &stream) -> std::expected<v2225::InventoryTransactionPacket, std::error_code>
{
    v2225::InventoryTransactionPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.legacy_request_id = static_cast<std::int32_t>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::vector<v2225::LegacySetSlot> staged{};
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            staged.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                staged.emplace_back();
                auto v = Serializer<v2225::LegacySetSlot>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                staged.back() = *v;
            }
            out.legacy_set_item_slots = std::move(staged);
        }
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v2193::NormalTransactionData, v2193::InventoryMismatchData, v2193::ItemUseInventoryTransaction, v2225::ItemUseOnActorInventoryTransaction, v2225::ItemReleaseInventoryTransaction> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v2193::NormalTransactionData, v2193::InventoryMismatchData, v2193::ItemUseInventoryTransaction, v2225::ItemUseOnActorInventoryTransaction, v2225::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v2193::NormalTransactionData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v2193::NormalTransactionData, v2193::InventoryMismatchData, v2193::ItemUseInventoryTransaction, v2225::ItemUseOnActorInventoryTransaction, v2225::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v2193::InventoryMismatchData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<v2193::NormalTransactionData, v2193::InventoryMismatchData, v2193::ItemUseInventoryTransaction, v2225::ItemUseOnActorInventoryTransaction, v2225::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v2193::ItemUseInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<v2193::NormalTransactionData, v2193::InventoryMismatchData, v2193::ItemUseInventoryTransaction, v2225::ItemUseOnActorInventoryTransaction, v2225::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v2225::ItemUseOnActorInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            case 4: {
                std::variant_alternative_t<4, std::variant<v2193::NormalTransactionData, v2193::InventoryMismatchData, v2193::ItemUseInventoryTransaction, v2225::ItemUseOnActorInventoryTransaction, v2225::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v2225::ItemReleaseInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<4>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out.transaction = var0;
    }
    return out;
}

void Serializer<base::TransactionData>::serialize(BinaryWriter &stream, const base::TransactionData &value)
{
    stream.writeVarInt<std::uint32_t>((value).index());
    switch ((value).index()) {
        case 0: {
            Serializer<base::NormalTransactionData>::serialize(stream, std::get<0>(value));
            break;
        }
        case 1: {
            Serializer<base::InventoryMismatchData>::serialize(stream, std::get<1>(value));
            break;
        }
        case 2: {
            Serializer<base::ItemUseInventoryTransaction>::serialize(stream, std::get<2>(value));
            break;
        }
        case 3: {
            Serializer<base::ItemUseOnActorInventoryTransaction>::serialize(stream, std::get<3>(value));
            break;
        }
        case 4: {
            Serializer<base::ItemReleaseInventoryTransaction>::serialize(stream, std::get<4>(value));
            break;
        }
    }
}

auto Serializer<base::TransactionData>::deserialize(BinaryReader &stream) -> std::expected<base::TransactionData, std::error_code>
{
    base::TransactionData out;
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<base::NormalTransactionData, base::InventoryMismatchData, base::ItemUseInventoryTransaction, base::ItemUseOnActorInventoryTransaction, base::ItemReleaseInventoryTransaction> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<base::NormalTransactionData, base::InventoryMismatchData, base::ItemUseInventoryTransaction, base::ItemUseOnActorInventoryTransaction, base::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<base::NormalTransactionData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<base::NormalTransactionData, base::InventoryMismatchData, base::ItemUseInventoryTransaction, base::ItemUseOnActorInventoryTransaction, base::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<base::InventoryMismatchData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<base::NormalTransactionData, base::InventoryMismatchData, base::ItemUseInventoryTransaction, base::ItemUseOnActorInventoryTransaction, base::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<base::ItemUseInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<base::NormalTransactionData, base::InventoryMismatchData, base::ItemUseInventoryTransaction, base::ItemUseOnActorInventoryTransaction, base::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<base::ItemUseOnActorInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            case 4: {
                std::variant_alternative_t<4, std::variant<base::NormalTransactionData, base::InventoryMismatchData, base::ItemUseInventoryTransaction, base::ItemUseOnActorInventoryTransaction, base::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<base::ItemReleaseInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<4>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out = var0;
    }
    return out;
}

void Serializer<v748::TransactionData>::serialize(BinaryWriter &stream, const v748::TransactionData &value)
{
    stream.writeVarInt<std::uint32_t>((value).index());
    switch ((value).index()) {
        case 0: {
            Serializer<v748::NormalTransactionData>::serialize(stream, std::get<0>(value));
            break;
        }
        case 1: {
            Serializer<v748::InventoryMismatchData>::serialize(stream, std::get<1>(value));
            break;
        }
        case 2: {
            Serializer<v748::ItemUseInventoryTransaction>::serialize(stream, std::get<2>(value));
            break;
        }
        case 3: {
            Serializer<v748::ItemUseOnActorInventoryTransaction>::serialize(stream, std::get<3>(value));
            break;
        }
        case 4: {
            Serializer<v748::ItemReleaseInventoryTransaction>::serialize(stream, std::get<4>(value));
            break;
        }
    }
}

auto Serializer<v748::TransactionData>::deserialize(BinaryReader &stream) -> std::expected<v748::TransactionData, std::error_code>
{
    v748::TransactionData out;
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v748::NormalTransactionData, v748::InventoryMismatchData, v748::ItemUseInventoryTransaction, v748::ItemUseOnActorInventoryTransaction, v748::ItemReleaseInventoryTransaction> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v748::NormalTransactionData, v748::InventoryMismatchData, v748::ItemUseInventoryTransaction, v748::ItemUseOnActorInventoryTransaction, v748::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v748::NormalTransactionData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v748::NormalTransactionData, v748::InventoryMismatchData, v748::ItemUseInventoryTransaction, v748::ItemUseOnActorInventoryTransaction, v748::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v748::InventoryMismatchData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<v748::NormalTransactionData, v748::InventoryMismatchData, v748::ItemUseInventoryTransaction, v748::ItemUseOnActorInventoryTransaction, v748::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v748::ItemUseInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<v748::NormalTransactionData, v748::InventoryMismatchData, v748::ItemUseInventoryTransaction, v748::ItemUseOnActorInventoryTransaction, v748::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v748::ItemUseOnActorInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            case 4: {
                std::variant_alternative_t<4, std::variant<v748::NormalTransactionData, v748::InventoryMismatchData, v748::ItemUseInventoryTransaction, v748::ItemUseOnActorInventoryTransaction, v748::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v748::ItemReleaseInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<4>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out = var0;
    }
    return out;
}

void Serializer<v844::TransactionData>::serialize(BinaryWriter &stream, const v844::TransactionData &value)
{
    stream.writeVarInt<std::uint32_t>((value).index());
    switch ((value).index()) {
        case 0: {
            Serializer<v748::NormalTransactionData>::serialize(stream, std::get<0>(value));
            break;
        }
        case 1: {
            Serializer<v748::InventoryMismatchData>::serialize(stream, std::get<1>(value));
            break;
        }
        case 2: {
            Serializer<v844::ItemUseInventoryTransaction>::serialize(stream, std::get<2>(value));
            break;
        }
        case 3: {
            Serializer<v748::ItemUseOnActorInventoryTransaction>::serialize(stream, std::get<3>(value));
            break;
        }
        case 4: {
            Serializer<v748::ItemReleaseInventoryTransaction>::serialize(stream, std::get<4>(value));
            break;
        }
    }
}

auto Serializer<v844::TransactionData>::deserialize(BinaryReader &stream) -> std::expected<v844::TransactionData, std::error_code>
{
    v844::TransactionData out;
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v748::NormalTransactionData, v748::InventoryMismatchData, v844::ItemUseInventoryTransaction, v748::ItemUseOnActorInventoryTransaction, v748::ItemReleaseInventoryTransaction> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v748::NormalTransactionData, v748::InventoryMismatchData, v844::ItemUseInventoryTransaction, v748::ItemUseOnActorInventoryTransaction, v748::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v748::NormalTransactionData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v748::NormalTransactionData, v748::InventoryMismatchData, v844::ItemUseInventoryTransaction, v748::ItemUseOnActorInventoryTransaction, v748::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v748::InventoryMismatchData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<v748::NormalTransactionData, v748::InventoryMismatchData, v844::ItemUseInventoryTransaction, v748::ItemUseOnActorInventoryTransaction, v748::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v844::ItemUseInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<v748::NormalTransactionData, v748::InventoryMismatchData, v844::ItemUseInventoryTransaction, v748::ItemUseOnActorInventoryTransaction, v748::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v748::ItemUseOnActorInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            case 4: {
                std::variant_alternative_t<4, std::variant<v748::NormalTransactionData, v748::InventoryMismatchData, v844::ItemUseInventoryTransaction, v748::ItemUseOnActorInventoryTransaction, v748::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v748::ItemReleaseInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<4>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out = var0;
    }
    return out;
}

void Serializer<v944::TransactionData>::serialize(BinaryWriter &stream, const v944::TransactionData &value)
{
    stream.writeVarInt<std::uint32_t>((value).index());
    switch ((value).index()) {
        case 0: {
            Serializer<v748::NormalTransactionData>::serialize(stream, std::get<0>(value));
            break;
        }
        case 1: {
            Serializer<v748::InventoryMismatchData>::serialize(stream, std::get<1>(value));
            break;
        }
        case 2: {
            Serializer<v944::ItemUseInventoryTransaction>::serialize(stream, std::get<2>(value));
            break;
        }
        case 3: {
            Serializer<v748::ItemUseOnActorInventoryTransaction>::serialize(stream, std::get<3>(value));
            break;
        }
        case 4: {
            Serializer<v748::ItemReleaseInventoryTransaction>::serialize(stream, std::get<4>(value));
            break;
        }
    }
}

auto Serializer<v944::TransactionData>::deserialize(BinaryReader &stream) -> std::expected<v944::TransactionData, std::error_code>
{
    v944::TransactionData out;
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v748::NormalTransactionData, v748::InventoryMismatchData, v944::ItemUseInventoryTransaction, v748::ItemUseOnActorInventoryTransaction, v748::ItemReleaseInventoryTransaction> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v748::NormalTransactionData, v748::InventoryMismatchData, v944::ItemUseInventoryTransaction, v748::ItemUseOnActorInventoryTransaction, v748::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v748::NormalTransactionData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v748::NormalTransactionData, v748::InventoryMismatchData, v944::ItemUseInventoryTransaction, v748::ItemUseOnActorInventoryTransaction, v748::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v748::InventoryMismatchData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<v748::NormalTransactionData, v748::InventoryMismatchData, v944::ItemUseInventoryTransaction, v748::ItemUseOnActorInventoryTransaction, v748::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v944::ItemUseInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<v748::NormalTransactionData, v748::InventoryMismatchData, v944::ItemUseInventoryTransaction, v748::ItemUseOnActorInventoryTransaction, v748::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v748::ItemUseOnActorInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            case 4: {
                std::variant_alternative_t<4, std::variant<v748::NormalTransactionData, v748::InventoryMismatchData, v944::ItemUseInventoryTransaction, v748::ItemUseOnActorInventoryTransaction, v748::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v748::ItemReleaseInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<4>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out = var0;
    }
    return out;
}

void Serializer<v1001::TransactionData>::serialize(BinaryWriter &stream, const v1001::TransactionData &value)
{
    stream.writeVarInt<std::uint32_t>((value).index());
    switch ((value).index()) {
        case 0: {
            Serializer<v1001::NormalTransactionData>::serialize(stream, std::get<0>(value));
            break;
        }
        case 1: {
            Serializer<v1001::InventoryMismatchData>::serialize(stream, std::get<1>(value));
            break;
        }
        case 2: {
            Serializer<v1001::ItemUseInventoryTransaction>::serialize(stream, std::get<2>(value));
            break;
        }
        case 3: {
            Serializer<v1001::ItemUseOnActorInventoryTransaction>::serialize(stream, std::get<3>(value));
            break;
        }
        case 4: {
            Serializer<v1001::ItemReleaseInventoryTransaction>::serialize(stream, std::get<4>(value));
            break;
        }
    }
}

auto Serializer<v1001::TransactionData>::deserialize(BinaryReader &stream) -> std::expected<v1001::TransactionData, std::error_code>
{
    v1001::TransactionData out;
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v1001::NormalTransactionData, v1001::InventoryMismatchData, v1001::ItemUseInventoryTransaction, v1001::ItemUseOnActorInventoryTransaction, v1001::ItemReleaseInventoryTransaction> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v1001::NormalTransactionData, v1001::InventoryMismatchData, v1001::ItemUseInventoryTransaction, v1001::ItemUseOnActorInventoryTransaction, v1001::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v1001::NormalTransactionData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v1001::NormalTransactionData, v1001::InventoryMismatchData, v1001::ItemUseInventoryTransaction, v1001::ItemUseOnActorInventoryTransaction, v1001::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v1001::InventoryMismatchData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<v1001::NormalTransactionData, v1001::InventoryMismatchData, v1001::ItemUseInventoryTransaction, v1001::ItemUseOnActorInventoryTransaction, v1001::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v1001::ItemUseInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<v1001::NormalTransactionData, v1001::InventoryMismatchData, v1001::ItemUseInventoryTransaction, v1001::ItemUseOnActorInventoryTransaction, v1001::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v1001::ItemUseOnActorInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            case 4: {
                std::variant_alternative_t<4, std::variant<v1001::NormalTransactionData, v1001::InventoryMismatchData, v1001::ItemUseInventoryTransaction, v1001::ItemUseOnActorInventoryTransaction, v1001::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v1001::ItemReleaseInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<4>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out = var0;
    }
    return out;
}

void Serializer<v2168::TransactionData>::serialize(BinaryWriter &stream, const v2168::TransactionData &value)
{
    stream.writeVarInt<std::uint32_t>((value).index());
    switch ((value).index()) {
        case 0: {
            Serializer<v2168::NormalTransactionData>::serialize(stream, std::get<0>(value));
            break;
        }
        case 1: {
            Serializer<v2168::InventoryMismatchData>::serialize(stream, std::get<1>(value));
            break;
        }
        case 2: {
            Serializer<v2168::ItemUseInventoryTransaction>::serialize(stream, std::get<2>(value));
            break;
        }
        case 3: {
            Serializer<v2168::ItemUseOnActorInventoryTransaction>::serialize(stream, std::get<3>(value));
            break;
        }
        case 4: {
            Serializer<v2168::ItemReleaseInventoryTransaction>::serialize(stream, std::get<4>(value));
            break;
        }
    }
}

auto Serializer<v2168::TransactionData>::deserialize(BinaryReader &stream) -> std::expected<v2168::TransactionData, std::error_code>
{
    v2168::TransactionData out;
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v2168::NormalTransactionData, v2168::InventoryMismatchData, v2168::ItemUseInventoryTransaction, v2168::ItemUseOnActorInventoryTransaction, v2168::ItemReleaseInventoryTransaction> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v2168::NormalTransactionData, v2168::InventoryMismatchData, v2168::ItemUseInventoryTransaction, v2168::ItemUseOnActorInventoryTransaction, v2168::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v2168::NormalTransactionData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v2168::NormalTransactionData, v2168::InventoryMismatchData, v2168::ItemUseInventoryTransaction, v2168::ItemUseOnActorInventoryTransaction, v2168::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v2168::InventoryMismatchData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<v2168::NormalTransactionData, v2168::InventoryMismatchData, v2168::ItemUseInventoryTransaction, v2168::ItemUseOnActorInventoryTransaction, v2168::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v2168::ItemUseInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<v2168::NormalTransactionData, v2168::InventoryMismatchData, v2168::ItemUseInventoryTransaction, v2168::ItemUseOnActorInventoryTransaction, v2168::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v2168::ItemUseOnActorInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            case 4: {
                std::variant_alternative_t<4, std::variant<v2168::NormalTransactionData, v2168::InventoryMismatchData, v2168::ItemUseInventoryTransaction, v2168::ItemUseOnActorInventoryTransaction, v2168::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v2168::ItemReleaseInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<4>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out = var0;
    }
    return out;
}

void Serializer<v2193::TransactionData>::serialize(BinaryWriter &stream, const v2193::TransactionData &value)
{
    stream.writeVarInt<std::uint32_t>((value).index());
    switch ((value).index()) {
        case 0: {
            Serializer<v2193::NormalTransactionData>::serialize(stream, std::get<0>(value));
            break;
        }
        case 1: {
            Serializer<v2193::InventoryMismatchData>::serialize(stream, std::get<1>(value));
            break;
        }
        case 2: {
            Serializer<v2193::ItemUseInventoryTransaction>::serialize(stream, std::get<2>(value));
            break;
        }
        case 3: {
            Serializer<v2193::ItemUseOnActorInventoryTransaction>::serialize(stream, std::get<3>(value));
            break;
        }
        case 4: {
            Serializer<v2193::ItemReleaseInventoryTransaction>::serialize(stream, std::get<4>(value));
            break;
        }
    }
}

auto Serializer<v2193::TransactionData>::deserialize(BinaryReader &stream) -> std::expected<v2193::TransactionData, std::error_code>
{
    v2193::TransactionData out;
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v2193::NormalTransactionData, v2193::InventoryMismatchData, v2193::ItemUseInventoryTransaction, v2193::ItemUseOnActorInventoryTransaction, v2193::ItemReleaseInventoryTransaction> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v2193::NormalTransactionData, v2193::InventoryMismatchData, v2193::ItemUseInventoryTransaction, v2193::ItemUseOnActorInventoryTransaction, v2193::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v2193::NormalTransactionData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v2193::NormalTransactionData, v2193::InventoryMismatchData, v2193::ItemUseInventoryTransaction, v2193::ItemUseOnActorInventoryTransaction, v2193::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v2193::InventoryMismatchData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<v2193::NormalTransactionData, v2193::InventoryMismatchData, v2193::ItemUseInventoryTransaction, v2193::ItemUseOnActorInventoryTransaction, v2193::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v2193::ItemUseInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<v2193::NormalTransactionData, v2193::InventoryMismatchData, v2193::ItemUseInventoryTransaction, v2193::ItemUseOnActorInventoryTransaction, v2193::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v2193::ItemUseOnActorInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            case 4: {
                std::variant_alternative_t<4, std::variant<v2193::NormalTransactionData, v2193::InventoryMismatchData, v2193::ItemUseInventoryTransaction, v2193::ItemUseOnActorInventoryTransaction, v2193::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v2193::ItemReleaseInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<4>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out = var0;
    }
    return out;
}

void Serializer<v2225::TransactionData>::serialize(BinaryWriter &stream, const v2225::TransactionData &value)
{
    stream.writeVarInt<std::uint32_t>((value).index());
    switch ((value).index()) {
        case 0: {
            Serializer<v2193::NormalTransactionData>::serialize(stream, std::get<0>(value));
            break;
        }
        case 1: {
            Serializer<v2193::InventoryMismatchData>::serialize(stream, std::get<1>(value));
            break;
        }
        case 2: {
            Serializer<v2193::ItemUseInventoryTransaction>::serialize(stream, std::get<2>(value));
            break;
        }
        case 3: {
            Serializer<v2225::ItemUseOnActorInventoryTransaction>::serialize(stream, std::get<3>(value));
            break;
        }
        case 4: {
            Serializer<v2225::ItemReleaseInventoryTransaction>::serialize(stream, std::get<4>(value));
            break;
        }
    }
}

auto Serializer<v2225::TransactionData>::deserialize(BinaryReader &stream) -> std::expected<v2225::TransactionData, std::error_code>
{
    v2225::TransactionData out;
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v2193::NormalTransactionData, v2193::InventoryMismatchData, v2193::ItemUseInventoryTransaction, v2225::ItemUseOnActorInventoryTransaction, v2225::ItemReleaseInventoryTransaction> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v2193::NormalTransactionData, v2193::InventoryMismatchData, v2193::ItemUseInventoryTransaction, v2225::ItemUseOnActorInventoryTransaction, v2225::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v2193::NormalTransactionData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v2193::NormalTransactionData, v2193::InventoryMismatchData, v2193::ItemUseInventoryTransaction, v2225::ItemUseOnActorInventoryTransaction, v2225::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v2193::InventoryMismatchData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<v2193::NormalTransactionData, v2193::InventoryMismatchData, v2193::ItemUseInventoryTransaction, v2225::ItemUseOnActorInventoryTransaction, v2225::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v2193::ItemUseInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<v2193::NormalTransactionData, v2193::InventoryMismatchData, v2193::ItemUseInventoryTransaction, v2225::ItemUseOnActorInventoryTransaction, v2225::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v2225::ItemUseOnActorInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            case 4: {
                std::variant_alternative_t<4, std::variant<v2193::NormalTransactionData, v2193::InventoryMismatchData, v2193::ItemUseInventoryTransaction, v2225::ItemUseOnActorInventoryTransaction, v2225::ItemReleaseInventoryTransaction>> alt0{};
                {
                    auto v = Serializer<v2225::ItemReleaseInventoryTransaction>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<4>(alt0);
                break;
            }
            default: {
                return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
            }
        }
        out = var0;
    }
    return out;
}

}  // namespace bedrock::protocol
