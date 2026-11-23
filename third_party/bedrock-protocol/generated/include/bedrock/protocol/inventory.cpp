#include <bedrock/protocol/inventory.h>

namespace bedrock::protocol {


void Serializer<base::FullContainerName>::serialize(BinaryWriter &stream, const base::FullContainerName &value)
{
    stream.write<std::uint8_t>(value.name);
    stream.write<bool>(value.dynamic_id.has_value());
    if (value.dynamic_id.has_value()) {
        stream.write<std::uint32_t>((*value.dynamic_id));
    }
}

auto Serializer<base::FullContainerName>::deserialize(BinaryReader &stream) -> std::expected<base::FullContainerName, std::error_code>
{
    base::FullContainerName out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.name = static_cast<base::ContainerEnumName>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::uint32_t staged{};
            auto v = stream.read<std::uint32_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<std::uint32_t>(*v);
            out.dynamic_id = std::move(staged);
        }
    }
    return out;
}

void Serializer<v924::FullContainerName>::serialize(BinaryWriter &stream, const v924::FullContainerName &value)
{
    stream.write<std::uint8_t>(value.name);
    stream.write<bool>(value.dynamic_id.has_value());
    if (value.dynamic_id.has_value()) {
        stream.write<std::uint32_t>((*value.dynamic_id));
    }
}

auto Serializer<v924::FullContainerName>::deserialize(BinaryReader &stream) -> std::expected<v924::FullContainerName, std::error_code>
{
    v924::FullContainerName out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.name = static_cast<v924::ContainerEnumName>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::uint32_t staged{};
            auto v = stream.read<std::uint32_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<std::uint32_t>(*v);
            out.dynamic_id = std::move(staged);
        }
    }
    return out;
}

void Serializer<v2225::FullContainerName>::serialize(BinaryWriter &stream, const v2225::FullContainerName &value)
{
    stream.write<std::uint8_t>(value.name);
    stream.write<bool>(value.dynamic_id.has_value());
    if (value.dynamic_id.has_value()) {
        stream.write<std::uint32_t>((*value.dynamic_id));
    }
}

auto Serializer<v2225::FullContainerName>::deserialize(BinaryReader &stream) -> std::expected<v2225::FullContainerName, std::error_code>
{
    v2225::FullContainerName out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.name = static_cast<v2225::ContainerEnumName>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::uint32_t staged{};
            auto v = stream.read<std::uint32_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<std::uint32_t>(*v);
            out.dynamic_id = std::move(staged);
        }
    }
    return out;
}

void Serializer<base::InventoryContentPacket>::serialize(BinaryWriter &stream, const base::InventoryContentPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.inventory_id);
    stream.writeVarInt<std::uint32_t>(value.slots.size());
    for (const auto &e0 : value.slots) {
        Serializer<NetworkItemStackDescriptor>::serialize(stream, e0);
    }
    Serializer<base::FullContainerName>::serialize(stream, value.full_container_name);
    stream.writeVarInt<std::uint32_t>(value.dynamic_container_size);
}

auto Serializer<base::InventoryContentPacket>::deserialize(BinaryReader &stream) -> std::expected<base::InventoryContentPacket, std::error_code>
{
    base::InventoryContentPacket out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.inventory_id = static_cast<base::ContainerID>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.slots.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.slots.emplace_back();
            auto v = Serializer<NetworkItemStackDescriptor>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.slots.back() = *v;
        }
    }
    {
        auto v = Serializer<base::FullContainerName>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.full_container_name = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.dynamic_container_size = static_cast<std::uint32_t>(*v);
    }
    return out;
}

void Serializer<v748::InventoryContentPacket>::serialize(BinaryWriter &stream, const v748::InventoryContentPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.inventory_id);
    stream.writeVarInt<std::uint32_t>(value.slots.size());
    for (const auto &e0 : value.slots) {
        Serializer<NetworkItemStackDescriptor>::serialize(stream, e0);
    }
    Serializer<base::FullContainerName>::serialize(stream, value.full_container_name);
    Serializer<NetworkItemStackDescriptor>::serialize(stream, value.storage_item);
}

auto Serializer<v748::InventoryContentPacket>::deserialize(BinaryReader &stream) -> std::expected<v748::InventoryContentPacket, std::error_code>
{
    v748::InventoryContentPacket out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.inventory_id = static_cast<v748::ContainerID>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.slots.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.slots.emplace_back();
            auto v = Serializer<NetworkItemStackDescriptor>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.slots.back() = *v;
        }
    }
    {
        auto v = Serializer<base::FullContainerName>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.full_container_name = *v;
    }
    {
        auto v = Serializer<NetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.storage_item = *v;
    }
    return out;
}

void Serializer<v924::InventoryContentPacket>::serialize(BinaryWriter &stream, const v924::InventoryContentPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.inventory_id);
    stream.writeVarInt<std::uint32_t>(value.slots.size());
    for (const auto &e0 : value.slots) {
        Serializer<NetworkItemStackDescriptor>::serialize(stream, e0);
    }
    Serializer<v924::FullContainerName>::serialize(stream, value.full_container_name);
    Serializer<NetworkItemStackDescriptor>::serialize(stream, value.storage_item);
}

auto Serializer<v924::InventoryContentPacket>::deserialize(BinaryReader &stream) -> std::expected<v924::InventoryContentPacket, std::error_code>
{
    v924::InventoryContentPacket out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.inventory_id = static_cast<v748::ContainerID>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.slots.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.slots.emplace_back();
            auto v = Serializer<NetworkItemStackDescriptor>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.slots.back() = *v;
        }
    }
    {
        auto v = Serializer<v924::FullContainerName>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.full_container_name = *v;
    }
    {
        auto v = Serializer<NetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.storage_item = *v;
    }
    return out;
}

void Serializer<v1001::InventoryContentPacket>::serialize(BinaryWriter &stream, const v1001::InventoryContentPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.inventory_id);
    stream.writeVarInt<std::uint32_t>(value.slots.size());
    for (const auto &e0 : value.slots) {
        Serializer<base::SerializedNetworkItemStackDescriptor>::serialize(stream, e0);
    }
    Serializer<v924::FullContainerName>::serialize(stream, value.full_container_name);
    Serializer<base::SerializedNetworkItemStackDescriptor>::serialize(stream, value.storage_item);
}

auto Serializer<v1001::InventoryContentPacket>::deserialize(BinaryReader &stream) -> std::expected<v1001::InventoryContentPacket, std::error_code>
{
    v1001::InventoryContentPacket out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.inventory_id = static_cast<v748::ContainerID>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.slots.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.slots.emplace_back();
            auto v = Serializer<base::SerializedNetworkItemStackDescriptor>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.slots.back() = *v;
        }
    }
    {
        auto v = Serializer<v924::FullContainerName>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.full_container_name = *v;
    }
    {
        auto v = Serializer<base::SerializedNetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.storage_item = *v;
    }
    return out;
}

void Serializer<v2168::InventoryContentPacket>::serialize(BinaryWriter &stream, const v2168::InventoryContentPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.inventory_id);
    stream.writeVarInt<std::uint32_t>(value.slots.size());
    for (const auto &e0 : value.slots) {
        Serializer<v2168::SerializedNetworkItemStackDescriptor>::serialize(stream, e0);
    }
    Serializer<v924::FullContainerName>::serialize(stream, value.full_container_name);
    Serializer<v2168::SerializedNetworkItemStackDescriptor>::serialize(stream, value.storage_item);
}

auto Serializer<v2168::InventoryContentPacket>::deserialize(BinaryReader &stream) -> std::expected<v2168::InventoryContentPacket, std::error_code>
{
    v2168::InventoryContentPacket out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.inventory_id = static_cast<v748::ContainerID>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.slots.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.slots.emplace_back();
            auto v = Serializer<v2168::SerializedNetworkItemStackDescriptor>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.slots.back() = *v;
        }
    }
    {
        auto v = Serializer<v924::FullContainerName>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.full_container_name = *v;
    }
    {
        auto v = Serializer<v2168::SerializedNetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.storage_item = *v;
    }
    return out;
}

void Serializer<v2225::InventoryContentPacket>::serialize(BinaryWriter &stream, const v2225::InventoryContentPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.inventory_id);
    stream.writeVarInt<std::uint32_t>(value.slots.size());
    for (const auto &e0 : value.slots) {
        Serializer<v2168::SerializedNetworkItemStackDescriptor>::serialize(stream, e0);
    }
    Serializer<v2225::FullContainerName>::serialize(stream, value.full_container_name);
    Serializer<v2168::SerializedNetworkItemStackDescriptor>::serialize(stream, value.storage_item);
}

auto Serializer<v2225::InventoryContentPacket>::deserialize(BinaryReader &stream) -> std::expected<v2225::InventoryContentPacket, std::error_code>
{
    v2225::InventoryContentPacket out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.inventory_id = static_cast<v748::ContainerID>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.slots.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.slots.emplace_back();
            auto v = Serializer<v2168::SerializedNetworkItemStackDescriptor>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.slots.back() = *v;
        }
    }
    {
        auto v = Serializer<v2225::FullContainerName>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.full_container_name = *v;
    }
    {
        auto v = Serializer<v2168::SerializedNetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.storage_item = *v;
    }
    return out;
}

void Serializer<base::InventorySlotPacket>::serialize(BinaryWriter &stream, const base::InventorySlotPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.inventory_id);
    stream.writeVarInt<std::uint32_t>(value.slot);
    Serializer<base::FullContainerName>::serialize(stream, value.full_container_name);
    stream.writeVarInt<std::uint32_t>(value.dynamic_container_size);
    Serializer<NetworkItemStackDescriptor>::serialize(stream, value.item);
}

auto Serializer<base::InventorySlotPacket>::deserialize(BinaryReader &stream) -> std::expected<base::InventorySlotPacket, std::error_code>
{
    base::InventorySlotPacket out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.inventory_id = static_cast<base::ContainerID>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = Serializer<base::FullContainerName>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.full_container_name = *v;
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.dynamic_container_size = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = Serializer<NetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.item = *v;
    }
    return out;
}

void Serializer<v748::InventorySlotPacket>::serialize(BinaryWriter &stream, const v748::InventorySlotPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.inventory_id);
    stream.writeVarInt<std::uint32_t>(value.slot);
    Serializer<base::FullContainerName>::serialize(stream, value.full_container_name);
    Serializer<NetworkItemStackDescriptor>::serialize(stream, value.storage_item);
    Serializer<NetworkItemStackDescriptor>::serialize(stream, value.item);
}

auto Serializer<v748::InventorySlotPacket>::deserialize(BinaryReader &stream) -> std::expected<v748::InventorySlotPacket, std::error_code>
{
    v748::InventorySlotPacket out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.inventory_id = static_cast<v748::ContainerID>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = Serializer<base::FullContainerName>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.full_container_name = *v;
    }
    {
        auto v = Serializer<NetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.storage_item = *v;
    }
    {
        auto v = Serializer<NetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.item = *v;
    }
    return out;
}

void Serializer<v924::InventorySlotPacket>::serialize(BinaryWriter &stream, const v924::InventorySlotPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.inventory_id);
    stream.writeVarInt<std::uint32_t>(value.slot);
    Serializer<v924::FullContainerName>::serialize(stream, value.full_container_name);
    Serializer<NetworkItemStackDescriptor>::serialize(stream, value.storage_item);
    Serializer<NetworkItemStackDescriptor>::serialize(stream, value.item);
}

auto Serializer<v924::InventorySlotPacket>::deserialize(BinaryReader &stream) -> std::expected<v924::InventorySlotPacket, std::error_code>
{
    v924::InventorySlotPacket out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.inventory_id = static_cast<v748::ContainerID>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = Serializer<v924::FullContainerName>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.full_container_name = *v;
    }
    {
        auto v = Serializer<NetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.storage_item = *v;
    }
    {
        auto v = Serializer<NetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.item = *v;
    }
    return out;
}

void Serializer<v975::InventorySlotPacket>::serialize(BinaryWriter &stream, const v975::InventorySlotPacket &value)
{
    stream.write<std::int8_t>(value.inventory_id);
    stream.writeVarInt<std::uint32_t>(value.slot);
    stream.write<bool>(value.full_container_name.has_value());
    if (value.full_container_name.has_value()) {
        Serializer<v924::FullContainerName>::serialize(stream, (*value.full_container_name));
    }
    stream.write<bool>(value.storage_item.has_value());
    if (value.storage_item.has_value()) {
        Serializer<base::SerializedNetworkItemStackDescriptor>::serialize(stream, (*value.storage_item));
    }
    Serializer<base::SerializedNetworkItemStackDescriptor>::serialize(stream, value.item);
}

auto Serializer<v975::InventorySlotPacket>::deserialize(BinaryReader &stream) -> std::expected<v975::InventorySlotPacket, std::error_code>
{
    v975::InventorySlotPacket out;
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.inventory_id = static_cast<v748::ContainerID>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::uint32_t>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v924::FullContainerName staged{};
            auto v = Serializer<v924::FullContainerName>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.full_container_name = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            base::SerializedNetworkItemStackDescriptor staged{};
            auto v = Serializer<base::SerializedNetworkItemStackDescriptor>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.storage_item = std::move(staged);
        }
    }
    {
        auto v = Serializer<base::SerializedNetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.item = *v;
    }
    return out;
}

void Serializer<v2168::InventorySlotPacket>::serialize(BinaryWriter &stream, const v2168::InventorySlotPacket &value)
{
    stream.write<std::int8_t>(value.inventory_id);
    stream.writeVarInt<std::uint32_t>(value.slot);
    stream.write<bool>(value.full_container_name.has_value());
    if (value.full_container_name.has_value()) {
        Serializer<v924::FullContainerName>::serialize(stream, (*value.full_container_name));
    }
    stream.write<bool>(value.storage_item.has_value());
    if (value.storage_item.has_value()) {
        Serializer<v2168::SerializedNetworkItemStackDescriptor>::serialize(stream, (*value.storage_item));
    }
    Serializer<v2168::SerializedNetworkItemStackDescriptor>::serialize(stream, value.item);
}

auto Serializer<v2168::InventorySlotPacket>::deserialize(BinaryReader &stream) -> std::expected<v2168::InventorySlotPacket, std::error_code>
{
    v2168::InventorySlotPacket out;
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.inventory_id = static_cast<v748::ContainerID>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::uint32_t>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v924::FullContainerName staged{};
            auto v = Serializer<v924::FullContainerName>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.full_container_name = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v2168::SerializedNetworkItemStackDescriptor staged{};
            auto v = Serializer<v2168::SerializedNetworkItemStackDescriptor>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.storage_item = std::move(staged);
        }
    }
    {
        auto v = Serializer<v2168::SerializedNetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.item = *v;
    }
    return out;
}

void Serializer<v2225::InventorySlotPacket>::serialize(BinaryWriter &stream, const v2225::InventorySlotPacket &value)
{
    stream.write<std::int8_t>(value.inventory_id);
    stream.writeVarInt<std::uint32_t>(value.slot);
    stream.write<bool>(value.full_container_name.has_value());
    if (value.full_container_name.has_value()) {
        Serializer<v2225::FullContainerName>::serialize(stream, (*value.full_container_name));
    }
    stream.write<bool>(value.storage_item.has_value());
    if (value.storage_item.has_value()) {
        Serializer<v2168::SerializedNetworkItemStackDescriptor>::serialize(stream, (*value.storage_item));
    }
    Serializer<v2168::SerializedNetworkItemStackDescriptor>::serialize(stream, value.item);
}

auto Serializer<v2225::InventorySlotPacket>::deserialize(BinaryReader &stream) -> std::expected<v2225::InventorySlotPacket, std::error_code>
{
    v2225::InventorySlotPacket out;
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.inventory_id = static_cast<v748::ContainerID>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::uint32_t>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v2225::FullContainerName staged{};
            auto v = Serializer<v2225::FullContainerName>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.full_container_name = std::move(staged);
        }
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            v2168::SerializedNetworkItemStackDescriptor staged{};
            auto v = Serializer<v2168::SerializedNetworkItemStackDescriptor>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.storage_item = std::move(staged);
        }
    }
    {
        auto v = Serializer<v2168::SerializedNetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.item = *v;
    }
    return out;
}

void Serializer<base::ContainerClosePacket>::serialize(BinaryWriter &stream, const base::ContainerClosePacket &value)
{
    stream.write<std::int8_t>(value.container_id);
    stream.write<std::int8_t>(value.container_type);
    stream.write<bool>(value.server_initiated_close);
}

auto Serializer<base::ContainerClosePacket>::deserialize(BinaryReader &stream) -> std::expected<base::ContainerClosePacket, std::error_code>
{
    base::ContainerClosePacket out;
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.container_id = static_cast<base::ContainerID>(*v);
    }
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.container_type = static_cast<base::ContainerType>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.server_initiated_close = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v748::ContainerClosePacket>::serialize(BinaryWriter &stream, const v748::ContainerClosePacket &value)
{
    stream.write<std::int8_t>(value.container_id);
    stream.write<std::int8_t>(value.container_type);
    stream.write<bool>(value.server_initiated_close);
}

auto Serializer<v748::ContainerClosePacket>::deserialize(BinaryReader &stream) -> std::expected<v748::ContainerClosePacket, std::error_code>
{
    v748::ContainerClosePacket out;
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.container_id = static_cast<v748::ContainerID>(*v);
    }
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.container_type = static_cast<base::ContainerType>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.server_initiated_close = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v2193::ContainerClosePacket>::serialize(BinaryWriter &stream, const v2193::ContainerClosePacket &value)
{
    stream.write<std::int8_t>(value.container_id);
    stream.write<std::int8_t>(value.container_type);
    stream.write<bool>(value.server_initiated_close);
}

auto Serializer<v2193::ContainerClosePacket>::deserialize(BinaryReader &stream) -> std::expected<v2193::ContainerClosePacket, std::error_code>
{
    v2193::ContainerClosePacket out;
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.container_id = static_cast<v748::ContainerID>(*v);
    }
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.container_type = static_cast<v2193::ContainerType>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.server_initiated_close = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v2225::ContainerClosePacket>::serialize(BinaryWriter &stream, const v2225::ContainerClosePacket &value)
{
    stream.write<std::int8_t>(value.container_id);
    stream.write<std::int8_t>(value.container_type);
    stream.write<bool>(value.server_initiated_close);
}

auto Serializer<v2225::ContainerClosePacket>::deserialize(BinaryReader &stream) -> std::expected<v2225::ContainerClosePacket, std::error_code>
{
    v2225::ContainerClosePacket out;
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.container_id = static_cast<v748::ContainerID>(*v);
    }
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.container_type = static_cast<v2225::ContainerType>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.server_initiated_close = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<base::PlayerHotbarPacket>::serialize(BinaryWriter &stream, const base::PlayerHotbarPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.selected_slot);
    stream.write<std::int8_t>(value.container_id);
    stream.write<bool>(value.should_select_slot);
}

auto Serializer<base::PlayerHotbarPacket>::deserialize(BinaryReader &stream) -> std::expected<base::PlayerHotbarPacket, std::error_code>
{
    base::PlayerHotbarPacket out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.selected_slot = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.container_id = static_cast<base::ContainerID>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.should_select_slot = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v748::PlayerHotbarPacket>::serialize(BinaryWriter &stream, const v748::PlayerHotbarPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.selected_slot);
    stream.write<std::int8_t>(value.container_id);
    stream.write<bool>(value.should_select_slot);
}

auto Serializer<v748::PlayerHotbarPacket>::deserialize(BinaryReader &stream) -> std::expected<v748::PlayerHotbarPacket, std::error_code>
{
    v748::PlayerHotbarPacket out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.selected_slot = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.container_id = static_cast<v748::ContainerID>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.should_select_slot = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<base::ContainerSetDataPacket>::serialize(BinaryWriter &stream, const base::ContainerSetDataPacket &value)
{
    stream.write<std::int8_t>(value.container_id);
    stream.writeVarInt<std::int32_t>(value.id);
    stream.writeVarInt<std::int32_t>(value.value);
}

auto Serializer<base::ContainerSetDataPacket>::deserialize(BinaryReader &stream) -> std::expected<base::ContainerSetDataPacket, std::error_code>
{
    base::ContainerSetDataPacket out;
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.container_id = static_cast<base::ContainerID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.id = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.value = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<v748::ContainerSetDataPacket>::serialize(BinaryWriter &stream, const v748::ContainerSetDataPacket &value)
{
    stream.write<std::int8_t>(value.container_id);
    stream.writeVarInt<std::int32_t>(value.id);
    stream.writeVarInt<std::int32_t>(value.value);
}

auto Serializer<v748::ContainerSetDataPacket>::deserialize(BinaryReader &stream) -> std::expected<v748::ContainerSetDataPacket, std::error_code>
{
    v748::ContainerSetDataPacket out;
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.container_id = static_cast<v748::ContainerID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.id = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.value = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<GuiDataPickItemPacket>::serialize(BinaryWriter &stream, const GuiDataPickItemPacket &value)
{
    stream.write(value.item_name);
    stream.write(value.item_effect_name);
    stream.write<std::int32_t>(value.slot);
}

auto Serializer<GuiDataPickItemPacket>::deserialize(BinaryReader &stream) -> std::expected<GuiDataPickItemPacket, std::error_code>
{
    GuiDataPickItemPacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.item_name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.item_effect_name = *v;
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<CompletedUsingItemPacket>::serialize(BinaryWriter &stream, const CompletedUsingItemPacket &value)
{
    stream.write<std::int16_t>(value.item_id);
    stream.write<std::int32_t>(value.item_use_method);
}

auto Serializer<CompletedUsingItemPacket>::deserialize(BinaryReader &stream) -> std::expected<CompletedUsingItemPacket, std::error_code>
{
    CompletedUsingItemPacket out;
    {
        auto v = stream.read<std::int16_t>();
        if (!v) return std::unexpected(v.error());
        out.item_id = static_cast<std::int16_t>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.item_use_method = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<PlayerToggleCrafterSlotRequestPacket>::serialize(BinaryWriter &stream, const PlayerToggleCrafterSlotRequestPacket &value)
{
    stream.write<std::int32_t>(value.pos_x);
    stream.write<std::int32_t>(value.pos_y);
    stream.write<std::int32_t>(value.pos_z);
    stream.write<std::uint8_t>(value.slot_index);
    stream.write<bool>(value.is_disabled);
}

auto Serializer<PlayerToggleCrafterSlotRequestPacket>::deserialize(BinaryReader &stream) -> std::expected<PlayerToggleCrafterSlotRequestPacket, std::error_code>
{
    PlayerToggleCrafterSlotRequestPacket out;
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.pos_x = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.pos_y = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.pos_z = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.slot_index = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_disabled = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<base::ContainerOpenPacket>::serialize(BinaryWriter &stream, const base::ContainerOpenPacket &value)
{
    stream.write<std::int8_t>(value.container_id);
    stream.write<std::int8_t>(value.type);
    Serializer<base::NetworkBlockPosition>::serialize(stream, value.pos);
    stream.writeVarInt<std::int64_t>(value.entity_unique_id);
}

auto Serializer<base::ContainerOpenPacket>::deserialize(BinaryReader &stream) -> std::expected<base::ContainerOpenPacket, std::error_code>
{
    base::ContainerOpenPacket out;
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.container_id = static_cast<base::ContainerID>(*v);
    }
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<base::ContainerType>(*v);
    }
    {
        auto v = Serializer<base::NetworkBlockPosition>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_unique_id = static_cast<ActorUniqueID>(*v);
    }
    return out;
}

void Serializer<v748::ContainerOpenPacket>::serialize(BinaryWriter &stream, const v748::ContainerOpenPacket &value)
{
    stream.write<std::int8_t>(value.container_id);
    stream.write<std::int8_t>(value.type);
    Serializer<base::NetworkBlockPosition>::serialize(stream, value.pos);
    stream.writeVarInt<std::int64_t>(value.entity_unique_id);
}

auto Serializer<v748::ContainerOpenPacket>::deserialize(BinaryReader &stream) -> std::expected<v748::ContainerOpenPacket, std::error_code>
{
    v748::ContainerOpenPacket out;
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.container_id = static_cast<v748::ContainerID>(*v);
    }
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<base::ContainerType>(*v);
    }
    {
        auto v = Serializer<base::NetworkBlockPosition>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_unique_id = static_cast<ActorUniqueID>(*v);
    }
    return out;
}

void Serializer<v944::ContainerOpenPacket>::serialize(BinaryWriter &stream, const v944::ContainerOpenPacket &value)
{
    stream.write<std::int8_t>(value.container_id);
    stream.write<std::int8_t>(value.type);
    Serializer<BlockPos>::serialize(stream, value.pos);
    stream.writeVarInt<std::int64_t>(value.entity_unique_id);
}

auto Serializer<v944::ContainerOpenPacket>::deserialize(BinaryReader &stream) -> std::expected<v944::ContainerOpenPacket, std::error_code>
{
    v944::ContainerOpenPacket out;
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.container_id = static_cast<v748::ContainerID>(*v);
    }
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<base::ContainerType>(*v);
    }
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_unique_id = static_cast<ActorUniqueID>(*v);
    }
    return out;
}

void Serializer<v2193::ContainerOpenPacket>::serialize(BinaryWriter &stream, const v2193::ContainerOpenPacket &value)
{
    stream.write<std::int8_t>(value.container_id);
    stream.write<std::int8_t>(value.type);
    Serializer<BlockPos>::serialize(stream, value.pos);
    stream.writeVarInt<std::int64_t>(value.entity_unique_id);
}

auto Serializer<v2193::ContainerOpenPacket>::deserialize(BinaryReader &stream) -> std::expected<v2193::ContainerOpenPacket, std::error_code>
{
    v2193::ContainerOpenPacket out;
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.container_id = static_cast<v748::ContainerID>(*v);
    }
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<v2193::ContainerType>(*v);
    }
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_unique_id = static_cast<ActorUniqueID>(*v);
    }
    return out;
}

void Serializer<v2225::ContainerOpenPacket>::serialize(BinaryWriter &stream, const v2225::ContainerOpenPacket &value)
{
    stream.write<std::int8_t>(value.container_id);
    stream.write<std::int8_t>(value.type);
    Serializer<BlockPos>::serialize(stream, value.pos);
    stream.writeVarInt<std::int64_t>(value.entity_unique_id);
}

auto Serializer<v2225::ContainerOpenPacket>::deserialize(BinaryReader &stream) -> std::expected<v2225::ContainerOpenPacket, std::error_code>
{
    v2225::ContainerOpenPacket out;
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.container_id = static_cast<v748::ContainerID>(*v);
    }
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<v2225::ContainerType>(*v);
    }
    {
        auto v = Serializer<BlockPos>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.pos = *v;
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_unique_id = static_cast<ActorUniqueID>(*v);
    }
    return out;
}

void Serializer<base::ContainerRegistryCleanupPacket>::serialize(BinaryWriter &stream, const base::ContainerRegistryCleanupPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.removed_containers.size());
    for (const auto &e0 : value.removed_containers) {
        Serializer<base::FullContainerName>::serialize(stream, e0);
    }
}

auto Serializer<base::ContainerRegistryCleanupPacket>::deserialize(BinaryReader &stream) -> std::expected<base::ContainerRegistryCleanupPacket, std::error_code>
{
    base::ContainerRegistryCleanupPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.removed_containers.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.removed_containers.emplace_back();
            auto v = Serializer<base::FullContainerName>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.removed_containers.back() = *v;
        }
    }
    return out;
}

void Serializer<v924::ContainerRegistryCleanupPacket>::serialize(BinaryWriter &stream, const v924::ContainerRegistryCleanupPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.removed_containers.size());
    for (const auto &e0 : value.removed_containers) {
        Serializer<v924::FullContainerName>::serialize(stream, e0);
    }
}

auto Serializer<v924::ContainerRegistryCleanupPacket>::deserialize(BinaryReader &stream) -> std::expected<v924::ContainerRegistryCleanupPacket, std::error_code>
{
    v924::ContainerRegistryCleanupPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.removed_containers.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.removed_containers.emplace_back();
            auto v = Serializer<v924::FullContainerName>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.removed_containers.back() = *v;
        }
    }
    return out;
}

void Serializer<v2225::ContainerRegistryCleanupPacket>::serialize(BinaryWriter &stream, const v2225::ContainerRegistryCleanupPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.removed_containers.size());
    for (const auto &e0 : value.removed_containers) {
        Serializer<v2225::FullContainerName>::serialize(stream, e0);
    }
}

auto Serializer<v2225::ContainerRegistryCleanupPacket>::deserialize(BinaryReader &stream) -> std::expected<v2225::ContainerRegistryCleanupPacket, std::error_code>
{
    v2225::ContainerRegistryCleanupPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.removed_containers.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.removed_containers.emplace_back();
            auto v = Serializer<v2225::FullContainerName>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.removed_containers.back() = *v;
        }
    }
    return out;
}

void Serializer<InventoryOptions>::serialize(BinaryWriter &stream, const InventoryOptions &value)
{
    stream.writeVarInt<std::int32_t>(value.left_inventory_tab);
    stream.writeVarInt<std::int32_t>(value.right_inventory_tab);
    stream.write<bool>(value.filtering);
    stream.writeVarInt<std::int32_t>(value.layout_inv);
    stream.writeVarInt<std::int32_t>(value.layout_craft);
}

auto Serializer<InventoryOptions>::deserialize(BinaryReader &stream) -> std::expected<InventoryOptions, std::error_code>
{
    InventoryOptions out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.left_inventory_tab = static_cast<InventoryLeftTabIndex>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.right_inventory_tab = static_cast<InventoryRightTabIndex>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.filtering = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.layout_inv = static_cast<InventoryLayout>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.layout_craft = static_cast<InventoryLayout>(*v);
    }
    return out;
}

void Serializer<SetPlayerInventoryOptionsPacket>::serialize(BinaryWriter &stream, const SetPlayerInventoryOptionsPacket &value)
{
    Serializer<InventoryOptions>::serialize(stream, value.inventory_options);
}

auto Serializer<SetPlayerInventoryOptionsPacket>::deserialize(BinaryReader &stream) -> std::expected<SetPlayerInventoryOptionsPacket, std::error_code>
{
    SetPlayerInventoryOptionsPacket out;
    {
        auto v = Serializer<InventoryOptions>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.inventory_options = *v;
    }
    return out;
}

void Serializer<FurnaceOptions>::serialize(BinaryWriter &stream, const FurnaceOptions &value)
{
    stream.writeVarInt<std::int32_t>(value.left_furnace_tab);
    stream.write<bool>(value.filtering);
    stream.writeVarInt<std::int32_t>(value.layout);
}

auto Serializer<FurnaceOptions>::deserialize(BinaryReader &stream) -> std::expected<FurnaceOptions, std::error_code>
{
    FurnaceOptions out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.left_furnace_tab = static_cast<FurnaceLeftTabIndex>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.filtering = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.layout = static_cast<FurnaceLayout>(*v);
    }
    return out;
}

void Serializer<v2193::SetPlayerFurnaceOptionsPacket>::serialize(BinaryWriter &stream, const v2193::SetPlayerFurnaceOptionsPacket &value)
{
    stream.write<std::uint8_t>(value.furnace_type);
    Serializer<FurnaceOptions>::serialize(stream, value.furnace_options);
}

auto Serializer<v2193::SetPlayerFurnaceOptionsPacket>::deserialize(BinaryReader &stream) -> std::expected<v2193::SetPlayerFurnaceOptionsPacket, std::error_code>
{
    v2193::SetPlayerFurnaceOptionsPacket out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.furnace_type = static_cast<v2193::SetPlayerFurnaceOptionsPacket::FurnaceType>(*v);
    }
    {
        auto v = Serializer<FurnaceOptions>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.furnace_options = *v;
    }
    return out;
}

void Serializer<v2225::ServerboundStonecutterSetRecipePacket>::serialize(BinaryWriter &stream, const v2225::ServerboundStonecutterSetRecipePacket &value)
{
    stream.write<std::int8_t>(value.container_id);
    stream.writeVarInt<std::int32_t>(value.recipe_index);
}

auto Serializer<v2225::ServerboundStonecutterSetRecipePacket>::deserialize(BinaryReader &stream) -> std::expected<v2225::ServerboundStonecutterSetRecipePacket, std::error_code>
{
    v2225::ServerboundStonecutterSetRecipePacket out;
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.container_id = static_cast<v748::ContainerID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.recipe_index = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<v2225::ClientboundStonecutterSetRecipePacket>::serialize(BinaryWriter &stream, const v2225::ClientboundStonecutterSetRecipePacket &value)
{
    stream.writeVarInt<std::int64_t>(value.player_id);
    stream.write<std::int8_t>(value.container_id);
    stream.writeVarInt<std::int32_t>(value.recipe_index);
}

auto Serializer<v2225::ClientboundStonecutterSetRecipePacket>::deserialize(BinaryReader &stream) -> std::expected<v2225::ClientboundStonecutterSetRecipePacket, std::error_code>
{
    v2225::ClientboundStonecutterSetRecipePacket out;
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.player_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.container_id = static_cast<v748::ContainerID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.recipe_index = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<v2225::ServerboundCursorItemDragPacket>::serialize(BinaryWriter &stream, const v2225::ServerboundCursorItemDragPacket &value)
{
    stream.write<std::uint8_t>(value.state);
}

auto Serializer<v2225::ServerboundCursorItemDragPacket>::deserialize(BinaryReader &stream) -> std::expected<v2225::ServerboundCursorItemDragPacket, std::error_code>
{
    v2225::ServerboundCursorItemDragPacket out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.state = static_cast<CursorItemDragState>(*v);
    }
    return out;
}

void Serializer<base::UpdateTradePacket>::serialize(BinaryWriter &stream, const base::UpdateTradePacket &value)
{
    stream.write<std::int8_t>(value.container_id);
    stream.write<std::int8_t>(value.type);
    stream.writeVarInt<std::int32_t>(value.size);
    stream.writeVarInt<std::int32_t>(value.trader_tier);
    stream.writeVarInt<std::int64_t>(value.entity_unique_id);
    stream.writeVarInt<std::int64_t>(value.last_trading_player);
    stream.write(value.display_name);
    stream.write<bool>(value.use_new_trade_screen);
    stream.write<bool>(value.using_economy_trade);
    Serializer<CompoundTag>::serialize(stream, value.data);
}

auto Serializer<base::UpdateTradePacket>::deserialize(BinaryReader &stream) -> std::expected<base::UpdateTradePacket, std::error_code>
{
    base::UpdateTradePacket out;
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.container_id = static_cast<base::ContainerID>(*v);
    }
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<base::ContainerType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.size = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.trader_tier = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_unique_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.last_trading_player = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.display_name = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.use_new_trade_screen = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.using_economy_trade = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<CompoundTag>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.data = *v;
    }
    return out;
}

void Serializer<v748::UpdateTradePacket>::serialize(BinaryWriter &stream, const v748::UpdateTradePacket &value)
{
    stream.write<std::int8_t>(value.container_id);
    stream.write<std::int8_t>(value.type);
    stream.writeVarInt<std::int32_t>(value.size);
    stream.writeVarInt<std::int32_t>(value.trader_tier);
    stream.writeVarInt<std::int64_t>(value.entity_unique_id);
    stream.writeVarInt<std::int64_t>(value.last_trading_player);
    stream.write(value.display_name);
    stream.write<bool>(value.use_new_trade_screen);
    stream.write<bool>(value.using_economy_trade);
    Serializer<CompoundTag>::serialize(stream, value.data);
}

auto Serializer<v748::UpdateTradePacket>::deserialize(BinaryReader &stream) -> std::expected<v748::UpdateTradePacket, std::error_code>
{
    v748::UpdateTradePacket out;
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.container_id = static_cast<v748::ContainerID>(*v);
    }
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<base::ContainerType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.size = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.trader_tier = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_unique_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.last_trading_player = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.display_name = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.use_new_trade_screen = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.using_economy_trade = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<CompoundTag>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.data = *v;
    }
    return out;
}

void Serializer<v2193::UpdateTradePacket>::serialize(BinaryWriter &stream, const v2193::UpdateTradePacket &value)
{
    stream.write<std::int8_t>(value.container_id);
    stream.write<std::int8_t>(value.type);
    stream.writeVarInt<std::int32_t>(value.size);
    stream.writeVarInt<std::int32_t>(value.trader_tier);
    stream.writeVarInt<std::int64_t>(value.entity_unique_id);
    stream.writeVarInt<std::int64_t>(value.last_trading_player);
    stream.write(value.display_name);
    stream.write<bool>(value.use_new_trade_screen);
    stream.write<bool>(value.using_economy_trade);
    Serializer<CompoundTag>::serialize(stream, value.data);
}

auto Serializer<v2193::UpdateTradePacket>::deserialize(BinaryReader &stream) -> std::expected<v2193::UpdateTradePacket, std::error_code>
{
    v2193::UpdateTradePacket out;
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.container_id = static_cast<v748::ContainerID>(*v);
    }
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<v2193::ContainerType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.size = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.trader_tier = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_unique_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.last_trading_player = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.display_name = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.use_new_trade_screen = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.using_economy_trade = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<CompoundTag>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.data = *v;
    }
    return out;
}

void Serializer<v2225::UpdateTradePacket>::serialize(BinaryWriter &stream, const v2225::UpdateTradePacket &value)
{
    stream.write<std::int8_t>(value.container_id);
    stream.write<std::int8_t>(value.type);
    stream.writeVarInt<std::int32_t>(value.size);
    stream.writeVarInt<std::int32_t>(value.trader_tier);
    stream.writeVarInt<std::int64_t>(value.entity_unique_id);
    stream.writeVarInt<std::int64_t>(value.last_trading_player);
    stream.write(value.display_name);
    stream.write<bool>(value.use_new_trade_screen);
    stream.write<bool>(value.using_economy_trade);
    Serializer<CompoundTag>::serialize(stream, value.data);
}

auto Serializer<v2225::UpdateTradePacket>::deserialize(BinaryReader &stream) -> std::expected<v2225::UpdateTradePacket, std::error_code>
{
    v2225::UpdateTradePacket out;
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.container_id = static_cast<v748::ContainerID>(*v);
    }
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<v2225::ContainerType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.size = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.trader_tier = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_unique_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.last_trading_player = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.display_name = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.use_new_trade_screen = static_cast<bool>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.using_economy_trade = static_cast<bool>(*v);
    }
    {
        auto v = Serializer<CompoundTag>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.data = *v;
    }
    return out;
}

void Serializer<base::UpdateEquipPacket>::serialize(BinaryWriter &stream, const base::UpdateEquipPacket &value)
{
    stream.write<std::int8_t>(value.container_id);
    stream.write<std::int8_t>(value.type);
    stream.writeVarInt<std::int32_t>(value.size);
    stream.writeVarInt<std::int64_t>(value.entity_unique_id);
    Serializer<CompoundTag>::serialize(stream, value.data);
}

auto Serializer<base::UpdateEquipPacket>::deserialize(BinaryReader &stream) -> std::expected<base::UpdateEquipPacket, std::error_code>
{
    base::UpdateEquipPacket out;
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.container_id = static_cast<base::ContainerID>(*v);
    }
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<base::ContainerType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.size = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_unique_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = Serializer<CompoundTag>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.data = *v;
    }
    return out;
}

void Serializer<v748::UpdateEquipPacket>::serialize(BinaryWriter &stream, const v748::UpdateEquipPacket &value)
{
    stream.write<std::int8_t>(value.container_id);
    stream.write<std::int8_t>(value.type);
    stream.writeVarInt<std::int32_t>(value.size);
    stream.writeVarInt<std::int64_t>(value.entity_unique_id);
    Serializer<CompoundTag>::serialize(stream, value.data);
}

auto Serializer<v748::UpdateEquipPacket>::deserialize(BinaryReader &stream) -> std::expected<v748::UpdateEquipPacket, std::error_code>
{
    v748::UpdateEquipPacket out;
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.container_id = static_cast<v748::ContainerID>(*v);
    }
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<base::ContainerType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.size = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_unique_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = Serializer<CompoundTag>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.data = *v;
    }
    return out;
}

void Serializer<v2193::UpdateEquipPacket>::serialize(BinaryWriter &stream, const v2193::UpdateEquipPacket &value)
{
    stream.write<std::int8_t>(value.container_id);
    stream.write<std::int8_t>(value.type);
    stream.writeVarInt<std::int32_t>(value.size);
    stream.writeVarInt<std::int64_t>(value.entity_unique_id);
    Serializer<CompoundTag>::serialize(stream, value.data);
}

auto Serializer<v2193::UpdateEquipPacket>::deserialize(BinaryReader &stream) -> std::expected<v2193::UpdateEquipPacket, std::error_code>
{
    v2193::UpdateEquipPacket out;
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.container_id = static_cast<v748::ContainerID>(*v);
    }
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<v2193::ContainerType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.size = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_unique_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = Serializer<CompoundTag>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.data = *v;
    }
    return out;
}

void Serializer<v2225::UpdateEquipPacket>::serialize(BinaryWriter &stream, const v2225::UpdateEquipPacket &value)
{
    stream.write<std::int8_t>(value.container_id);
    stream.write<std::int8_t>(value.type);
    stream.writeVarInt<std::int32_t>(value.size);
    stream.writeVarInt<std::int64_t>(value.entity_unique_id);
    Serializer<CompoundTag>::serialize(stream, value.data);
}

auto Serializer<v2225::UpdateEquipPacket>::deserialize(BinaryReader &stream) -> std::expected<v2225::UpdateEquipPacket, std::error_code>
{
    v2225::UpdateEquipPacket out;
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.container_id = static_cast<v748::ContainerID>(*v);
    }
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.type = static_cast<v2225::ContainerType>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.size = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int64_t>();
        if (!v) return std::unexpected(v.error());
        out.entity_unique_id = static_cast<ActorUniqueID>(*v);
    }
    {
        auto v = Serializer<CompoundTag>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.data = *v;
    }
    return out;
}

void Serializer<base::MobEquipmentPacket>::serialize(BinaryWriter &stream, const base::MobEquipmentPacket &value)
{
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    Serializer<NetworkItemStackDescriptor>::serialize(stream, value.item);
    stream.write<std::uint8_t>(value.slot);
    stream.write<std::uint8_t>(value.selected_slot);
    stream.write<std::int8_t>(value.container_id);
}

auto Serializer<base::MobEquipmentPacket>::deserialize(BinaryReader &stream) -> std::expected<base::MobEquipmentPacket, std::error_code>
{
    base::MobEquipmentPacket out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = Serializer<NetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.item = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.selected_slot = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.container_id = static_cast<base::ContainerID>(*v);
    }
    return out;
}

void Serializer<v748::MobEquipmentPacket>::serialize(BinaryWriter &stream, const v748::MobEquipmentPacket &value)
{
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    Serializer<NetworkItemStackDescriptor>::serialize(stream, value.item);
    stream.write<std::uint8_t>(value.slot);
    stream.write<std::uint8_t>(value.selected_slot);
    stream.write<std::int8_t>(value.container_id);
}

auto Serializer<v748::MobEquipmentPacket>::deserialize(BinaryReader &stream) -> std::expected<v748::MobEquipmentPacket, std::error_code>
{
    v748::MobEquipmentPacket out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = Serializer<NetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.item = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.selected_slot = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.container_id = static_cast<v748::ContainerID>(*v);
    }
    return out;
}

void Serializer<v975::MobEquipmentPacket>::serialize(BinaryWriter &stream, const v975::MobEquipmentPacket &value)
{
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    Serializer<base::SerializedNetworkItemStackDescriptor>::serialize(stream, value.item);
    stream.write<std::uint8_t>(value.slot);
    stream.write<std::uint8_t>(value.selected_slot);
    stream.write<std::int8_t>(value.container_id);
}

auto Serializer<v975::MobEquipmentPacket>::deserialize(BinaryReader &stream) -> std::expected<v975::MobEquipmentPacket, std::error_code>
{
    v975::MobEquipmentPacket out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = Serializer<base::SerializedNetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.item = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.selected_slot = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.container_id = static_cast<v748::ContainerID>(*v);
    }
    return out;
}

void Serializer<v2168::MobEquipmentPacket>::serialize(BinaryWriter &stream, const v2168::MobEquipmentPacket &value)
{
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    Serializer<v2168::SerializedNetworkItemStackDescriptor>::serialize(stream, value.item);
    stream.write<std::uint8_t>(value.slot);
    stream.write<std::uint8_t>(value.selected_slot);
    stream.write<std::int8_t>(value.container_id);
}

auto Serializer<v2168::MobEquipmentPacket>::deserialize(BinaryReader &stream) -> std::expected<v2168::MobEquipmentPacket, std::error_code>
{
    v2168::MobEquipmentPacket out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = Serializer<v2168::SerializedNetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.item = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.selected_slot = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::int8_t>();
        if (!v) return std::unexpected(v.error());
        out.container_id = static_cast<v748::ContainerID>(*v);
    }
    return out;
}

void Serializer<base::MobArmorEquipmentPacket>::serialize(BinaryWriter &stream, const base::MobArmorEquipmentPacket &value)
{
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    Serializer<NetworkItemStackDescriptor>::serialize(stream, value.head);
    Serializer<NetworkItemStackDescriptor>::serialize(stream, value.torso);
    Serializer<NetworkItemStackDescriptor>::serialize(stream, value.legs);
    Serializer<NetworkItemStackDescriptor>::serialize(stream, value.feet);
    Serializer<NetworkItemStackDescriptor>::serialize(stream, value.body);
}

auto Serializer<base::MobArmorEquipmentPacket>::deserialize(BinaryReader &stream) -> std::expected<base::MobArmorEquipmentPacket, std::error_code>
{
    base::MobArmorEquipmentPacket out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = Serializer<NetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.head = *v;
    }
    {
        auto v = Serializer<NetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.torso = *v;
    }
    {
        auto v = Serializer<NetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.legs = *v;
    }
    {
        auto v = Serializer<NetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.feet = *v;
    }
    {
        auto v = Serializer<NetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.body = *v;
    }
    return out;
}

void Serializer<v1001::MobArmorEquipmentPacket>::serialize(BinaryWriter &stream, const v1001::MobArmorEquipmentPacket &value)
{
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    Serializer<base::SerializedNetworkItemStackDescriptor>::serialize(stream, value.head);
    Serializer<base::SerializedNetworkItemStackDescriptor>::serialize(stream, value.torso);
    Serializer<base::SerializedNetworkItemStackDescriptor>::serialize(stream, value.legs);
    Serializer<base::SerializedNetworkItemStackDescriptor>::serialize(stream, value.feet);
    Serializer<base::SerializedNetworkItemStackDescriptor>::serialize(stream, value.body);
}

auto Serializer<v1001::MobArmorEquipmentPacket>::deserialize(BinaryReader &stream) -> std::expected<v1001::MobArmorEquipmentPacket, std::error_code>
{
    v1001::MobArmorEquipmentPacket out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = Serializer<base::SerializedNetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.head = *v;
    }
    {
        auto v = Serializer<base::SerializedNetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.torso = *v;
    }
    {
        auto v = Serializer<base::SerializedNetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.legs = *v;
    }
    {
        auto v = Serializer<base::SerializedNetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.feet = *v;
    }
    {
        auto v = Serializer<base::SerializedNetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.body = *v;
    }
    return out;
}

void Serializer<v2168::MobArmorEquipmentPacket>::serialize(BinaryWriter &stream, const v2168::MobArmorEquipmentPacket &value)
{
    stream.writeVarInt<std::uint64_t>(value.runtime_id);
    Serializer<v2168::SerializedNetworkItemStackDescriptor>::serialize(stream, value.head);
    Serializer<v2168::SerializedNetworkItemStackDescriptor>::serialize(stream, value.torso);
    Serializer<v2168::SerializedNetworkItemStackDescriptor>::serialize(stream, value.legs);
    Serializer<v2168::SerializedNetworkItemStackDescriptor>::serialize(stream, value.feet);
    Serializer<v2168::SerializedNetworkItemStackDescriptor>::serialize(stream, value.body);
}

auto Serializer<v2168::MobArmorEquipmentPacket>::deserialize(BinaryReader &stream) -> std::expected<v2168::MobArmorEquipmentPacket, std::error_code>
{
    v2168::MobArmorEquipmentPacket out;
    {
        auto v = stream.readVarInt<std::uint64_t>();
        if (!v) return std::unexpected(v.error());
        out.runtime_id = static_cast<ActorRuntimeID>(*v);
    }
    {
        auto v = Serializer<v2168::SerializedNetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.head = *v;
    }
    {
        auto v = Serializer<v2168::SerializedNetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.torso = *v;
    }
    {
        auto v = Serializer<v2168::SerializedNetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.legs = *v;
    }
    {
        auto v = Serializer<v2168::SerializedNetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.feet = *v;
    }
    {
        auto v = Serializer<v2168::SerializedNetworkItemStackDescriptor>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.body = *v;
    }
    return out;
}

}  // namespace bedrock::protocol
