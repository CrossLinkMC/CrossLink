#include <bedrock/protocol/item_stack.h>

namespace bedrock::protocol {


void Serializer<v766::RedactableString>::serialize(BinaryWriter &stream, const v766::RedactableString &value)
{
    stream.write(value.unredacted_string);
    stream.write(value.redacted_string);
}

auto Serializer<v766::RedactableString>::deserialize(BinaryReader &stream) -> std::expected<v766::RedactableString, std::error_code>
{
    v766::RedactableString out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.unredacted_string = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.redacted_string = *v;
    }
    return out;
}

void Serializer<v2168::RedactableString>::serialize(BinaryWriter &stream, const v2168::RedactableString &value)
{
    stream.write(value.unredacted_string);
    stream.write<bool>(value.redacted_string.has_value());
    if (value.redacted_string.has_value()) {
        stream.write((*value.redacted_string));
    }
}

auto Serializer<v2168::RedactableString>::deserialize(BinaryReader &stream) -> std::expected<v2168::RedactableString, std::error_code>
{
    v2168::RedactableString out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.unredacted_string = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::string staged{};
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.redacted_string = std::move(staged);
        }
    }
    return out;
}

void Serializer<base::ItemStackResponseSlotInfo>::serialize(BinaryWriter &stream, const base::ItemStackResponseSlotInfo &value)
{
    stream.write<std::uint8_t>(value.requested_slot);
    stream.write<std::uint8_t>(value.slot);
    stream.write<std::uint8_t>(value.amount);
    Serializer<ItemStackNetId>::serialize(stream, value.item_stack_net_id);
    stream.write(value.custom_name);
    stream.writeVarInt<std::int32_t>(value.durability_correction);
}

auto Serializer<base::ItemStackResponseSlotInfo>::deserialize(BinaryReader &stream) -> std::expected<base::ItemStackResponseSlotInfo, std::error_code>
{
    base::ItemStackResponseSlotInfo out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.requested_slot = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.amount = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = Serializer<ItemStackNetId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.item_stack_net_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.custom_name = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.durability_correction = static_cast<std::int16_t>(*v);
    }
    return out;
}

void Serializer<v766::ItemStackResponseSlotInfo>::serialize(BinaryWriter &stream, const v766::ItemStackResponseSlotInfo &value)
{
    stream.write<std::uint8_t>(value.requested_slot);
    stream.write<std::uint8_t>(value.slot);
    stream.write<std::uint8_t>(value.amount);
    Serializer<ItemStackNetId>::serialize(stream, value.item_stack_net_id);
    Serializer<v766::RedactableString>::serialize(stream, value.custom_name);
    stream.writeVarInt<std::int32_t>(value.durability_correction);
}

auto Serializer<v766::ItemStackResponseSlotInfo>::deserialize(BinaryReader &stream) -> std::expected<v766::ItemStackResponseSlotInfo, std::error_code>
{
    v766::ItemStackResponseSlotInfo out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.requested_slot = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.amount = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = Serializer<ItemStackNetId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.item_stack_net_id = *v;
    }
    {
        auto v = Serializer<v766::RedactableString>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.custom_name = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.durability_correction = static_cast<std::int16_t>(*v);
    }
    return out;
}

void Serializer<v2168::ItemStackResponseSlotInfo>::serialize(BinaryWriter &stream, const v2168::ItemStackResponseSlotInfo &value)
{
    stream.write<std::uint8_t>(value.requested_slot);
    stream.write<std::uint8_t>(value.slot);
    stream.write<std::uint8_t>(value.amount);
    stream.write<bool>(true);
    stream.write<bool>(value.item_stack_net_id.has_value());
    if (value.item_stack_net_id.has_value()) {
        Serializer<ItemStackNetId>::serialize(stream, (*value.item_stack_net_id));
    }
    Serializer<v2168::RedactableString>::serialize(stream, value.custom_name);
    stream.writeVarInt<std::int32_t>(value.durability_correction);
}

auto Serializer<v2168::ItemStackResponseSlotInfo>::deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackResponseSlotInfo, std::error_code>
{
    v2168::ItemStackResponseSlotInfo out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.requested_slot = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.amount = static_cast<std::uint8_t>(*v);
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
            ItemStackNetId staged{};
            auto v = Serializer<ItemStackNetId>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.item_stack_net_id = std::move(staged);
        }
    }
    {
        auto v = Serializer<v2168::RedactableString>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.custom_name = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.durability_correction = static_cast<std::int16_t>(*v);
    }
    return out;
}

void Serializer<v2193::ItemStackResponseSlotInfo>::serialize(BinaryWriter &stream, const v2193::ItemStackResponseSlotInfo &value)
{
    stream.write<std::uint8_t>(value.requested_slot);
    stream.write<std::uint8_t>(value.slot);
    stream.write<std::uint8_t>(value.amount);
    stream.write<bool>(value.item_stack_net_id.has_value());
    if (value.item_stack_net_id.has_value()) {
        Serializer<ItemStackNetId>::serialize(stream, (*value.item_stack_net_id));
    }
    Serializer<v2168::RedactableString>::serialize(stream, value.custom_name);
    stream.writeVarInt<std::int32_t>(value.durability_correction);
}

auto Serializer<v2193::ItemStackResponseSlotInfo>::deserialize(BinaryReader &stream) -> std::expected<v2193::ItemStackResponseSlotInfo, std::error_code>
{
    v2193::ItemStackResponseSlotInfo out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.requested_slot = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.amount = static_cast<std::uint8_t>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            ItemStackNetId staged{};
            auto v = Serializer<ItemStackNetId>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.item_stack_net_id = std::move(staged);
        }
    }
    {
        auto v = Serializer<v2168::RedactableString>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.custom_name = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.durability_correction = static_cast<std::int16_t>(*v);
    }
    return out;
}

void Serializer<base::ItemStackResponseContainerInfo>::serialize(BinaryWriter &stream, const base::ItemStackResponseContainerInfo &value)
{
    Serializer<base::FullContainerName>::serialize(stream, value.full_container_name);
    stream.writeVarInt<std::uint32_t>(value.slots.size());
    for (const auto &e0 : value.slots) {
        Serializer<base::ItemStackResponseSlotInfo>::serialize(stream, e0);
    }
}

auto Serializer<base::ItemStackResponseContainerInfo>::deserialize(BinaryReader &stream) -> std::expected<base::ItemStackResponseContainerInfo, std::error_code>
{
    base::ItemStackResponseContainerInfo out;
    {
        auto v = Serializer<base::FullContainerName>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.full_container_name = *v;
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.slots.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.slots.emplace_back();
            auto v = Serializer<base::ItemStackResponseSlotInfo>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.slots.back() = *v;
        }
    }
    return out;
}

void Serializer<v766::ItemStackResponseContainerInfo>::serialize(BinaryWriter &stream, const v766::ItemStackResponseContainerInfo &value)
{
    Serializer<base::FullContainerName>::serialize(stream, value.full_container_name);
    stream.writeVarInt<std::uint32_t>(value.slots.size());
    for (const auto &e0 : value.slots) {
        Serializer<v766::ItemStackResponseSlotInfo>::serialize(stream, e0);
    }
}

auto Serializer<v766::ItemStackResponseContainerInfo>::deserialize(BinaryReader &stream) -> std::expected<v766::ItemStackResponseContainerInfo, std::error_code>
{
    v766::ItemStackResponseContainerInfo out;
    {
        auto v = Serializer<base::FullContainerName>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.full_container_name = *v;
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.slots.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.slots.emplace_back();
            auto v = Serializer<v766::ItemStackResponseSlotInfo>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.slots.back() = *v;
        }
    }
    return out;
}

void Serializer<v924::ItemStackResponseContainerInfo>::serialize(BinaryWriter &stream, const v924::ItemStackResponseContainerInfo &value)
{
    Serializer<v924::FullContainerName>::serialize(stream, value.full_container_name);
    stream.writeVarInt<std::uint32_t>(value.slots.size());
    for (const auto &e0 : value.slots) {
        Serializer<v766::ItemStackResponseSlotInfo>::serialize(stream, e0);
    }
}

auto Serializer<v924::ItemStackResponseContainerInfo>::deserialize(BinaryReader &stream) -> std::expected<v924::ItemStackResponseContainerInfo, std::error_code>
{
    v924::ItemStackResponseContainerInfo out;
    {
        auto v = Serializer<v924::FullContainerName>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.full_container_name = *v;
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.slots.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.slots.emplace_back();
            auto v = Serializer<v766::ItemStackResponseSlotInfo>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.slots.back() = *v;
        }
    }
    return out;
}

void Serializer<v2168::ItemStackResponseContainerInfo>::serialize(BinaryWriter &stream, const v2168::ItemStackResponseContainerInfo &value)
{
    Serializer<v924::FullContainerName>::serialize(stream, value.full_container_name);
    stream.writeVarInt<std::uint32_t>(value.slots.size());
    for (const auto &e0 : value.slots) {
        Serializer<v2168::ItemStackResponseSlotInfo>::serialize(stream, e0);
    }
}

auto Serializer<v2168::ItemStackResponseContainerInfo>::deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackResponseContainerInfo, std::error_code>
{
    v2168::ItemStackResponseContainerInfo out;
    {
        auto v = Serializer<v924::FullContainerName>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.full_container_name = *v;
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.slots.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.slots.emplace_back();
            auto v = Serializer<v2168::ItemStackResponseSlotInfo>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.slots.back() = *v;
        }
    }
    return out;
}

void Serializer<v2193::ItemStackResponseContainerInfo>::serialize(BinaryWriter &stream, const v2193::ItemStackResponseContainerInfo &value)
{
    Serializer<v924::FullContainerName>::serialize(stream, value.full_container_name);
    stream.writeVarInt<std::uint32_t>(value.slots.size());
    for (const auto &e0 : value.slots) {
        Serializer<v2193::ItemStackResponseSlotInfo>::serialize(stream, e0);
    }
}

auto Serializer<v2193::ItemStackResponseContainerInfo>::deserialize(BinaryReader &stream) -> std::expected<v2193::ItemStackResponseContainerInfo, std::error_code>
{
    v2193::ItemStackResponseContainerInfo out;
    {
        auto v = Serializer<v924::FullContainerName>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.full_container_name = *v;
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.slots.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.slots.emplace_back();
            auto v = Serializer<v2193::ItemStackResponseSlotInfo>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.slots.back() = *v;
        }
    }
    return out;
}

void Serializer<v2225::ItemStackResponseContainerInfo>::serialize(BinaryWriter &stream, const v2225::ItemStackResponseContainerInfo &value)
{
    Serializer<v2225::FullContainerName>::serialize(stream, value.full_container_name);
    stream.writeVarInt<std::uint32_t>(value.slots.size());
    for (const auto &e0 : value.slots) {
        Serializer<v2193::ItemStackResponseSlotInfo>::serialize(stream, e0);
    }
}

auto Serializer<v2225::ItemStackResponseContainerInfo>::deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackResponseContainerInfo, std::error_code>
{
    v2225::ItemStackResponseContainerInfo out;
    {
        auto v = Serializer<v2225::FullContainerName>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.full_container_name = *v;
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.slots.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.slots.emplace_back();
            auto v = Serializer<v2193::ItemStackResponseSlotInfo>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.slots.back() = *v;
        }
    }
    return out;
}

void Serializer<base::ItemStackResponseInfo>::serialize(BinaryWriter &stream, const base::ItemStackResponseInfo &value)
{
    stream.write<std::uint8_t>(value.result);
    Serializer<ItemStackRequestId>::serialize(stream, value.client_request_id);
    if ((value.result) == (ItemStackNetResult::Success)) {
        stream.writeVarInt<std::uint32_t>(value.containers.size());
        for (const auto &e0 : value.containers) {
            Serializer<base::ItemStackResponseContainerInfo>::serialize(stream, e0);
        }
    }
}

auto Serializer<base::ItemStackResponseInfo>::deserialize(BinaryReader &stream) -> std::expected<base::ItemStackResponseInfo, std::error_code>
{
    base::ItemStackResponseInfo out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.result = static_cast<ItemStackNetResult>(*v);
    }
    {
        auto v = Serializer<ItemStackRequestId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.client_request_id = *v;
    }
    if ((out.result) == (ItemStackNetResult::Success)) {
        {
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            out.containers.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                out.containers.emplace_back();
                auto v = Serializer<base::ItemStackResponseContainerInfo>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                out.containers.back() = *v;
            }
        }
    }
    return out;
}

void Serializer<v766::ItemStackResponseInfo>::serialize(BinaryWriter &stream, const v766::ItemStackResponseInfo &value)
{
    stream.write<std::uint8_t>(value.result);
    Serializer<ItemStackRequestId>::serialize(stream, value.client_request_id);
    if ((value.result) == (ItemStackNetResult::Success)) {
        stream.writeVarInt<std::uint32_t>(value.containers.size());
        for (const auto &e0 : value.containers) {
            Serializer<v766::ItemStackResponseContainerInfo>::serialize(stream, e0);
        }
    }
}

auto Serializer<v766::ItemStackResponseInfo>::deserialize(BinaryReader &stream) -> std::expected<v766::ItemStackResponseInfo, std::error_code>
{
    v766::ItemStackResponseInfo out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.result = static_cast<ItemStackNetResult>(*v);
    }
    {
        auto v = Serializer<ItemStackRequestId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.client_request_id = *v;
    }
    if ((out.result) == (ItemStackNetResult::Success)) {
        {
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            out.containers.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                out.containers.emplace_back();
                auto v = Serializer<v766::ItemStackResponseContainerInfo>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                out.containers.back() = *v;
            }
        }
    }
    return out;
}

void Serializer<v924::ItemStackResponseInfo>::serialize(BinaryWriter &stream, const v924::ItemStackResponseInfo &value)
{
    stream.write<std::uint8_t>(value.result);
    Serializer<ItemStackRequestId>::serialize(stream, value.client_request_id);
    if ((value.result) == (ItemStackNetResult::Success)) {
        stream.writeVarInt<std::uint32_t>(value.containers.size());
        for (const auto &e0 : value.containers) {
            Serializer<v924::ItemStackResponseContainerInfo>::serialize(stream, e0);
        }
    }
}

auto Serializer<v924::ItemStackResponseInfo>::deserialize(BinaryReader &stream) -> std::expected<v924::ItemStackResponseInfo, std::error_code>
{
    v924::ItemStackResponseInfo out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.result = static_cast<ItemStackNetResult>(*v);
    }
    {
        auto v = Serializer<ItemStackRequestId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.client_request_id = *v;
    }
    if ((out.result) == (ItemStackNetResult::Success)) {
        {
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            out.containers.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                out.containers.emplace_back();
                auto v = Serializer<v924::ItemStackResponseContainerInfo>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                out.containers.back() = *v;
            }
        }
    }
    return out;
}

void Serializer<v2168::ItemStackResponseInfo>::serialize(BinaryWriter &stream, const v2168::ItemStackResponseInfo &value)
{
    stream.write<std::uint8_t>(value.result);
    Serializer<ItemStackRequestId>::serialize(stream, value.client_request_id);
    stream.write<bool>(true);
    stream.write<bool>(value.containers.has_value());
    if (value.containers.has_value()) {
        stream.writeVarInt<std::uint32_t>((*value.containers).size());
        for (const auto &e0 : (*value.containers)) {
            Serializer<v2168::ItemStackResponseContainerInfo>::serialize(stream, e0);
        }
    }
}

auto Serializer<v2168::ItemStackResponseInfo>::deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackResponseInfo, std::error_code>
{
    v2168::ItemStackResponseInfo out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.result = static_cast<ItemStackNetResult>(*v);
    }
    {
        auto v = Serializer<ItemStackRequestId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.client_request_id = *v;
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
            std::vector<v2168::ItemStackResponseContainerInfo> staged{};
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            staged.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                staged.emplace_back();
                auto v = Serializer<v2168::ItemStackResponseContainerInfo>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                staged.back() = *v;
            }
            out.containers = std::move(staged);
        }
    }
    return out;
}

void Serializer<v2193::ItemStackResponseInfo>::serialize(BinaryWriter &stream, const v2193::ItemStackResponseInfo &value)
{
    stream.write<std::uint8_t>(value.result);
    Serializer<ItemStackRequestId>::serialize(stream, value.client_request_id);
    stream.write<bool>(value.containers.has_value());
    if (value.containers.has_value()) {
        stream.writeVarInt<std::uint32_t>((*value.containers).size());
        for (const auto &e0 : (*value.containers)) {
            Serializer<v2193::ItemStackResponseContainerInfo>::serialize(stream, e0);
        }
    }
}

auto Serializer<v2193::ItemStackResponseInfo>::deserialize(BinaryReader &stream) -> std::expected<v2193::ItemStackResponseInfo, std::error_code>
{
    v2193::ItemStackResponseInfo out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.result = static_cast<ItemStackNetResult>(*v);
    }
    {
        auto v = Serializer<ItemStackRequestId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.client_request_id = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::vector<v2193::ItemStackResponseContainerInfo> staged{};
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            staged.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                staged.emplace_back();
                auto v = Serializer<v2193::ItemStackResponseContainerInfo>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                staged.back() = *v;
            }
            out.containers = std::move(staged);
        }
    }
    return out;
}

void Serializer<v2225::ItemStackResponseInfo>::serialize(BinaryWriter &stream, const v2225::ItemStackResponseInfo &value)
{
    stream.write<std::uint8_t>(value.result);
    Serializer<ItemStackRequestId>::serialize(stream, value.client_request_id);
    stream.write<bool>(value.containers.has_value());
    if (value.containers.has_value()) {
        stream.writeVarInt<std::uint32_t>((*value.containers).size());
        for (const auto &e0 : (*value.containers)) {
            Serializer<v2225::ItemStackResponseContainerInfo>::serialize(stream, e0);
        }
    }
}

auto Serializer<v2225::ItemStackResponseInfo>::deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackResponseInfo, std::error_code>
{
    v2225::ItemStackResponseInfo out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.result = static_cast<ItemStackNetResult>(*v);
    }
    {
        auto v = Serializer<ItemStackRequestId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.client_request_id = *v;
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::vector<v2225::ItemStackResponseContainerInfo> staged{};
            auto len0 = stream.readVarInt<std::uint32_t>();
            if (!len0) return std::unexpected(len0.error());
            staged.clear();
            for (auto rep0 = *len0; rep0 > 0; --rep0) {
                staged.emplace_back();
                auto v = Serializer<v2225::ItemStackResponseContainerInfo>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                staged.back() = *v;
            }
            out.containers = std::move(staged);
        }
    }
    return out;
}

void Serializer<base::ItemStackResponsePacket>::serialize(BinaryWriter &stream, const base::ItemStackResponsePacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.responses.size());
    for (const auto &e0 : value.responses) {
        Serializer<base::ItemStackResponseInfo>::serialize(stream, e0);
    }
}

auto Serializer<base::ItemStackResponsePacket>::deserialize(BinaryReader &stream) -> std::expected<base::ItemStackResponsePacket, std::error_code>
{
    base::ItemStackResponsePacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.responses.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.responses.emplace_back();
            auto v = Serializer<base::ItemStackResponseInfo>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.responses.back() = *v;
        }
    }
    return out;
}

void Serializer<v766::ItemStackResponsePacket>::serialize(BinaryWriter &stream, const v766::ItemStackResponsePacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.responses.size());
    for (const auto &e0 : value.responses) {
        Serializer<v766::ItemStackResponseInfo>::serialize(stream, e0);
    }
}

auto Serializer<v766::ItemStackResponsePacket>::deserialize(BinaryReader &stream) -> std::expected<v766::ItemStackResponsePacket, std::error_code>
{
    v766::ItemStackResponsePacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.responses.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.responses.emplace_back();
            auto v = Serializer<v766::ItemStackResponseInfo>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.responses.back() = *v;
        }
    }
    return out;
}

void Serializer<v924::ItemStackResponsePacket>::serialize(BinaryWriter &stream, const v924::ItemStackResponsePacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.responses.size());
    for (const auto &e0 : value.responses) {
        Serializer<v924::ItemStackResponseInfo>::serialize(stream, e0);
    }
}

auto Serializer<v924::ItemStackResponsePacket>::deserialize(BinaryReader &stream) -> std::expected<v924::ItemStackResponsePacket, std::error_code>
{
    v924::ItemStackResponsePacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.responses.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.responses.emplace_back();
            auto v = Serializer<v924::ItemStackResponseInfo>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.responses.back() = *v;
        }
    }
    return out;
}

void Serializer<v2168::ItemStackResponsePacket>::serialize(BinaryWriter &stream, const v2168::ItemStackResponsePacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.responses.size());
    for (const auto &e0 : value.responses) {
        Serializer<v2168::ItemStackResponseInfo>::serialize(stream, e0);
    }
}

auto Serializer<v2168::ItemStackResponsePacket>::deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackResponsePacket, std::error_code>
{
    v2168::ItemStackResponsePacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.responses.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.responses.emplace_back();
            auto v = Serializer<v2168::ItemStackResponseInfo>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.responses.back() = *v;
        }
    }
    return out;
}

void Serializer<v2193::ItemStackResponsePacket>::serialize(BinaryWriter &stream, const v2193::ItemStackResponsePacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.responses.size());
    for (const auto &e0 : value.responses) {
        Serializer<v2193::ItemStackResponseInfo>::serialize(stream, e0);
    }
}

auto Serializer<v2193::ItemStackResponsePacket>::deserialize(BinaryReader &stream) -> std::expected<v2193::ItemStackResponsePacket, std::error_code>
{
    v2193::ItemStackResponsePacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.responses.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.responses.emplace_back();
            auto v = Serializer<v2193::ItemStackResponseInfo>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.responses.back() = *v;
        }
    }
    return out;
}

void Serializer<v2225::ItemStackResponsePacket>::serialize(BinaryWriter &stream, const v2225::ItemStackResponsePacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.responses.size());
    for (const auto &e0 : value.responses) {
        Serializer<v2225::ItemStackResponseInfo>::serialize(stream, e0);
    }
}

auto Serializer<v2225::ItemStackResponsePacket>::deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackResponsePacket, std::error_code>
{
    v2225::ItemStackResponsePacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.responses.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.responses.emplace_back();
            auto v = Serializer<v2225::ItemStackResponseInfo>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.responses.back() = *v;
        }
    }
    return out;
}

void Serializer<v2168::ItemStackRequestCereal::EmptyItemDescriptorData>::serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::EmptyItemDescriptorData &value)
{
    stream.write<std::uint8_t>(0);
}

auto Serializer<v2168::ItemStackRequestCereal::EmptyItemDescriptorData>::deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::EmptyItemDescriptorData, std::error_code>
{
    v2168::ItemStackRequestCereal::EmptyItemDescriptorData out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 0) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    return out;
}

void Serializer<v2168::ItemStackRequestCereal::ItemNameDescriptorData>::serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::ItemNameDescriptorData &value)
{
    stream.write<std::uint8_t>(1);
    stream.write(value.full_name);
    stream.writeVarInt<std::int32_t>(value.aux_value);
}

auto Serializer<v2168::ItemStackRequestCereal::ItemNameDescriptorData>::deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::ItemNameDescriptorData, std::error_code>
{
    v2168::ItemStackRequestCereal::ItemNameDescriptorData out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 1) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.full_name = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.aux_value = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<v2168::ItemStackRequestCereal::MolangItemDescriptorData>::serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::MolangItemDescriptorData &value)
{
    stream.write<std::uint8_t>(2);
    stream.write(value.tag_expression);
    stream.write<std::int16_t>(value.molang_version);
}

auto Serializer<v2168::ItemStackRequestCereal::MolangItemDescriptorData>::deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::MolangItemDescriptorData, std::error_code>
{
    v2168::ItemStackRequestCereal::MolangItemDescriptorData out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 2) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.tag_expression = *v;
    }
    {
        auto v = stream.read<std::int16_t>();
        if (!v) return std::unexpected(v.error());
        out.molang_version = static_cast<v827::MolangVersion>(*v);
    }
    return out;
}

void Serializer<v2168::ItemStackRequestCereal::ItemTagDescriptorData>::serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::ItemTagDescriptorData &value)
{
    stream.write<std::uint8_t>(3);
    stream.write(value.item_tag);
}

auto Serializer<v2168::ItemStackRequestCereal::ItemTagDescriptorData>::deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::ItemTagDescriptorData, std::error_code>
{
    v2168::ItemStackRequestCereal::ItemTagDescriptorData out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 3) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.item_tag = *v;
    }
    return out;
}

void Serializer<v2168::ItemStackRequestCereal::NetworkItemInstanceDescriptorData>::serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::NetworkItemInstanceDescriptorData &value)
{
    stream.writeVarInt<std::uint32_t>((value.item_descriptor).index());
    switch ((value.item_descriptor).index()) {
        case 0: {
            Serializer<v2168::ItemStackRequestCereal::EmptyItemDescriptorData>::serialize(stream, std::get<0>(value.item_descriptor));
            break;
        }
        case 1: {
            Serializer<v2168::ItemStackRequestCereal::ItemNameDescriptorData>::serialize(stream, std::get<1>(value.item_descriptor));
            break;
        }
        case 2: {
            Serializer<v2168::ItemStackRequestCereal::MolangItemDescriptorData>::serialize(stream, std::get<2>(value.item_descriptor));
            break;
        }
        case 3: {
            Serializer<v2168::ItemStackRequestCereal::ItemTagDescriptorData>::serialize(stream, std::get<3>(value.item_descriptor));
            break;
        }
    }
    stream.write<std::uint16_t>(value.stack_size);
    stream.writeVarInt<std::uint32_t>(value.block_runtime_id);
    stream.write(value.user_data_buffer);
}

auto Serializer<v2168::ItemStackRequestCereal::NetworkItemInstanceDescriptorData>::deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::NetworkItemInstanceDescriptorData, std::error_code>
{
    v2168::ItemStackRequestCereal::NetworkItemInstanceDescriptorData out;
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v2168::ItemStackRequestCereal::EmptyItemDescriptorData, v2168::ItemStackRequestCereal::ItemNameDescriptorData, v2168::ItemStackRequestCereal::MolangItemDescriptorData, v2168::ItemStackRequestCereal::ItemTagDescriptorData> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v2168::ItemStackRequestCereal::EmptyItemDescriptorData, v2168::ItemStackRequestCereal::ItemNameDescriptorData, v2168::ItemStackRequestCereal::MolangItemDescriptorData, v2168::ItemStackRequestCereal::ItemTagDescriptorData>> alt0{};
                {
                    auto v = Serializer<v2168::ItemStackRequestCereal::EmptyItemDescriptorData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v2168::ItemStackRequestCereal::EmptyItemDescriptorData, v2168::ItemStackRequestCereal::ItemNameDescriptorData, v2168::ItemStackRequestCereal::MolangItemDescriptorData, v2168::ItemStackRequestCereal::ItemTagDescriptorData>> alt0{};
                {
                    auto v = Serializer<v2168::ItemStackRequestCereal::ItemNameDescriptorData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<v2168::ItemStackRequestCereal::EmptyItemDescriptorData, v2168::ItemStackRequestCereal::ItemNameDescriptorData, v2168::ItemStackRequestCereal::MolangItemDescriptorData, v2168::ItemStackRequestCereal::ItemTagDescriptorData>> alt0{};
                {
                    auto v = Serializer<v2168::ItemStackRequestCereal::MolangItemDescriptorData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<v2168::ItemStackRequestCereal::EmptyItemDescriptorData, v2168::ItemStackRequestCereal::ItemNameDescriptorData, v2168::ItemStackRequestCereal::MolangItemDescriptorData, v2168::ItemStackRequestCereal::ItemTagDescriptorData>> alt0{};
                {
                    auto v = Serializer<v2168::ItemStackRequestCereal::ItemTagDescriptorData>::deserialize(stream);
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
        out.item_descriptor = var0;
    }
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.stack_size = static_cast<std::uint16_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.block_runtime_id = static_cast<BlockRuntimeId>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.user_data_buffer = *v;
    }
    return out;
}

void Serializer<v2168::ItemStackRequestCereal::RecipeIngredientData>::serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::RecipeIngredientData &value)
{
    stream.writeVarInt<std::uint32_t>((value.item_descriptor).index());
    switch ((value.item_descriptor).index()) {
        case 0: {
            Serializer<v2168::ItemStackRequestCereal::EmptyItemDescriptorData>::serialize(stream, std::get<0>(value.item_descriptor));
            break;
        }
        case 1: {
            Serializer<v2168::ItemStackRequestCereal::ItemNameDescriptorData>::serialize(stream, std::get<1>(value.item_descriptor));
            break;
        }
        case 2: {
            Serializer<v2168::ItemStackRequestCereal::MolangItemDescriptorData>::serialize(stream, std::get<2>(value.item_descriptor));
            break;
        }
        case 3: {
            Serializer<v2168::ItemStackRequestCereal::ItemTagDescriptorData>::serialize(stream, std::get<3>(value.item_descriptor));
            break;
        }
    }
    stream.write<std::uint16_t>(value.stack_size);
}

auto Serializer<v2168::ItemStackRequestCereal::RecipeIngredientData>::deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::RecipeIngredientData, std::error_code>
{
    v2168::ItemStackRequestCereal::RecipeIngredientData out;
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<v2168::ItemStackRequestCereal::EmptyItemDescriptorData, v2168::ItemStackRequestCereal::ItemNameDescriptorData, v2168::ItemStackRequestCereal::MolangItemDescriptorData, v2168::ItemStackRequestCereal::ItemTagDescriptorData> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<v2168::ItemStackRequestCereal::EmptyItemDescriptorData, v2168::ItemStackRequestCereal::ItemNameDescriptorData, v2168::ItemStackRequestCereal::MolangItemDescriptorData, v2168::ItemStackRequestCereal::ItemTagDescriptorData>> alt0{};
                {
                    auto v = Serializer<v2168::ItemStackRequestCereal::EmptyItemDescriptorData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<v2168::ItemStackRequestCereal::EmptyItemDescriptorData, v2168::ItemStackRequestCereal::ItemNameDescriptorData, v2168::ItemStackRequestCereal::MolangItemDescriptorData, v2168::ItemStackRequestCereal::ItemTagDescriptorData>> alt0{};
                {
                    auto v = Serializer<v2168::ItemStackRequestCereal::ItemNameDescriptorData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<v2168::ItemStackRequestCereal::EmptyItemDescriptorData, v2168::ItemStackRequestCereal::ItemNameDescriptorData, v2168::ItemStackRequestCereal::MolangItemDescriptorData, v2168::ItemStackRequestCereal::ItemTagDescriptorData>> alt0{};
                {
                    auto v = Serializer<v2168::ItemStackRequestCereal::MolangItemDescriptorData>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<v2168::ItemStackRequestCereal::EmptyItemDescriptorData, v2168::ItemStackRequestCereal::ItemNameDescriptorData, v2168::ItemStackRequestCereal::MolangItemDescriptorData, v2168::ItemStackRequestCereal::ItemTagDescriptorData>> alt0{};
                {
                    auto v = Serializer<v2168::ItemStackRequestCereal::ItemTagDescriptorData>::deserialize(stream);
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
        out.item_descriptor = var0;
    }
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.stack_size = static_cast<std::uint16_t>(*v);
    }
    return out;
}

void Serializer<v2168::ItemStackRequestCereal::SlotInfoData>::serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::SlotInfoData &value)
{
    Serializer<v924::FullContainerName>::serialize(stream, value.full_container_name);
    stream.write<std::uint8_t>(value.slot);
    stream.write<std::int32_t>(value.net_id_variant);
}

auto Serializer<v2168::ItemStackRequestCereal::SlotInfoData>::deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::SlotInfoData, std::error_code>
{
    v2168::ItemStackRequestCereal::SlotInfoData out;
    {
        auto v = Serializer<v924::FullContainerName>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.full_container_name = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.net_id_variant = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<v2168::ItemStackRequestCereal::TakeActionData>::serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::TakeActionData &value)
{
    stream.write<std::uint8_t>(0);
    stream.write<std::uint8_t>(value.amount);
    Serializer<v2168::ItemStackRequestCereal::SlotInfoData>::serialize(stream, value.source);
    Serializer<v2168::ItemStackRequestCereal::SlotInfoData>::serialize(stream, value.destination);
}

auto Serializer<v2168::ItemStackRequestCereal::TakeActionData>::deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::TakeActionData, std::error_code>
{
    v2168::ItemStackRequestCereal::TakeActionData out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 0) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.amount = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = Serializer<v2168::ItemStackRequestCereal::SlotInfoData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.source = *v;
    }
    {
        auto v = Serializer<v2168::ItemStackRequestCereal::SlotInfoData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.destination = *v;
    }
    return out;
}

void Serializer<v2168::ItemStackRequestCereal::PlaceActionData>::serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::PlaceActionData &value)
{
    stream.write<std::uint8_t>(1);
    stream.write<std::uint8_t>(value.amount);
    Serializer<v2168::ItemStackRequestCereal::SlotInfoData>::serialize(stream, value.source);
    Serializer<v2168::ItemStackRequestCereal::SlotInfoData>::serialize(stream, value.destination);
}

auto Serializer<v2168::ItemStackRequestCereal::PlaceActionData>::deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::PlaceActionData, std::error_code>
{
    v2168::ItemStackRequestCereal::PlaceActionData out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 1) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.amount = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = Serializer<v2168::ItemStackRequestCereal::SlotInfoData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.source = *v;
    }
    {
        auto v = Serializer<v2168::ItemStackRequestCereal::SlotInfoData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.destination = *v;
    }
    return out;
}

void Serializer<v2168::ItemStackRequestCereal::SwapActionData>::serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::SwapActionData &value)
{
    stream.write<std::uint8_t>(2);
    Serializer<v2168::ItemStackRequestCereal::SlotInfoData>::serialize(stream, value.source);
    Serializer<v2168::ItemStackRequestCereal::SlotInfoData>::serialize(stream, value.destination);
}

auto Serializer<v2168::ItemStackRequestCereal::SwapActionData>::deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::SwapActionData, std::error_code>
{
    v2168::ItemStackRequestCereal::SwapActionData out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 2) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = Serializer<v2168::ItemStackRequestCereal::SlotInfoData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.source = *v;
    }
    {
        auto v = Serializer<v2168::ItemStackRequestCereal::SlotInfoData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.destination = *v;
    }
    return out;
}

void Serializer<v2168::ItemStackRequestCereal::DropActionData>::serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::DropActionData &value)
{
    stream.write<std::uint8_t>(3);
    stream.write<std::uint8_t>(value.amount);
    Serializer<v2168::ItemStackRequestCereal::SlotInfoData>::serialize(stream, value.source);
    stream.write<bool>(value.randomly);
}

auto Serializer<v2168::ItemStackRequestCereal::DropActionData>::deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::DropActionData, std::error_code>
{
    v2168::ItemStackRequestCereal::DropActionData out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 3) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.amount = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = Serializer<v2168::ItemStackRequestCereal::SlotInfoData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.source = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.randomly = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v2168::ItemStackRequestCereal::DestroyActionData>::serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::DestroyActionData &value)
{
    stream.write<std::uint8_t>(4);
    stream.write<std::uint8_t>(value.amount);
    Serializer<v2168::ItemStackRequestCereal::SlotInfoData>::serialize(stream, value.source);
}

auto Serializer<v2168::ItemStackRequestCereal::DestroyActionData>::deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::DestroyActionData, std::error_code>
{
    v2168::ItemStackRequestCereal::DestroyActionData out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 4) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.amount = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = Serializer<v2168::ItemStackRequestCereal::SlotInfoData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.source = *v;
    }
    return out;
}

void Serializer<v2168::ItemStackRequestCereal::ConsumeActionData>::serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::ConsumeActionData &value)
{
    stream.write<std::uint8_t>(5);
    stream.write<std::uint8_t>(value.amount);
    Serializer<v2168::ItemStackRequestCereal::SlotInfoData>::serialize(stream, value.source);
}

auto Serializer<v2168::ItemStackRequestCereal::ConsumeActionData>::deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::ConsumeActionData, std::error_code>
{
    v2168::ItemStackRequestCereal::ConsumeActionData out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 5) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.amount = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = Serializer<v2168::ItemStackRequestCereal::SlotInfoData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.source = *v;
    }
    return out;
}

void Serializer<v2168::ItemStackRequestCereal::CreateActionData>::serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::CreateActionData &value)
{
    stream.write<std::uint8_t>(6);
    stream.write<std::uint8_t>(value.results_index);
}

auto Serializer<v2168::ItemStackRequestCereal::CreateActionData>::deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::CreateActionData, std::error_code>
{
    v2168::ItemStackRequestCereal::CreateActionData out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 6) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.results_index = static_cast<std::uint8_t>(*v);
    }
    return out;
}

void Serializer<v2168::ItemStackRequestCereal::LabTableCombineActionData>::serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::LabTableCombineActionData &value)
{
    stream.write<std::uint8_t>(9);
}

auto Serializer<v2168::ItemStackRequestCereal::LabTableCombineActionData>::deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::LabTableCombineActionData, std::error_code>
{
    v2168::ItemStackRequestCereal::LabTableCombineActionData out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 9) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    return out;
}

void Serializer<v2168::ItemStackRequestCereal::BeaconPaymentActionData>::serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::BeaconPaymentActionData &value)
{
    stream.write<std::uint8_t>(10);
    stream.writeVarInt<std::int32_t>(value.primary_effect_id);
    stream.writeVarInt<std::int32_t>(value.secondary_effect_id);
}

auto Serializer<v2168::ItemStackRequestCereal::BeaconPaymentActionData>::deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::BeaconPaymentActionData, std::error_code>
{
    v2168::ItemStackRequestCereal::BeaconPaymentActionData out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 10) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.primary_effect_id = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.secondary_effect_id = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<v2168::ItemStackRequestCereal::MineBlockActionData>::serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::MineBlockActionData &value)
{
    stream.write<std::uint8_t>(11);
    stream.writeVarInt<std::int32_t>(value.slot);
    stream.writeVarInt<std::int32_t>(value.predicted_durability);
    stream.write<std::int32_t>(value.net_id_variant);
}

auto Serializer<v2168::ItemStackRequestCereal::MineBlockActionData>::deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::MineBlockActionData, std::error_code>
{
    v2168::ItemStackRequestCereal::MineBlockActionData out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 11) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.predicted_durability = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.net_id_variant = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<v2168::ItemStackRequestCereal::CraftRecipeActionData>::serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::CraftRecipeActionData &value)
{
    stream.write<std::uint8_t>(12);
    Serializer<RecipeNetId>::serialize(stream, value.recipe_net_id);
    stream.write<std::uint8_t>(value.num_crafts);
}

auto Serializer<v2168::ItemStackRequestCereal::CraftRecipeActionData>::deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::CraftRecipeActionData, std::error_code>
{
    v2168::ItemStackRequestCereal::CraftRecipeActionData out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 12) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = Serializer<RecipeNetId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.recipe_net_id = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.num_crafts = static_cast<std::uint8_t>(*v);
    }
    return out;
}

void Serializer<v2168::ItemStackRequestCereal::CraftRecipeAutoActionData>::serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::CraftRecipeAutoActionData &value)
{
    stream.write<std::uint8_t>(13);
    Serializer<RecipeNetId>::serialize(stream, value.recipe_net_id);
    stream.write<std::uint8_t>(value.num_crafts);
    stream.writeVarInt<std::uint32_t>(value.ingredients.size());
    for (const auto &e0 : value.ingredients) {
        Serializer<v2168::ItemStackRequestCereal::RecipeIngredientData>::serialize(stream, e0);
    }
}

auto Serializer<v2168::ItemStackRequestCereal::CraftRecipeAutoActionData>::deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::CraftRecipeAutoActionData, std::error_code>
{
    v2168::ItemStackRequestCereal::CraftRecipeAutoActionData out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 13) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = Serializer<RecipeNetId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.recipe_net_id = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.num_crafts = static_cast<std::uint8_t>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.ingredients.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.ingredients.emplace_back();
            auto v = Serializer<v2168::ItemStackRequestCereal::RecipeIngredientData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.ingredients.back() = *v;
        }
    }
    return out;
}

void Serializer<v2168::ItemStackRequestCereal::CraftCreativeActionData>::serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::CraftCreativeActionData &value)
{
    stream.write<std::uint8_t>(14);
    stream.writeVarInt<std::uint32_t>(value.creative_item_net_id);
    stream.write<std::uint8_t>(value.num_crafts);
}

auto Serializer<v2168::ItemStackRequestCereal::CraftCreativeActionData>::deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::CraftCreativeActionData, std::error_code>
{
    v2168::ItemStackRequestCereal::CraftCreativeActionData out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 14) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.creative_item_net_id = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.num_crafts = static_cast<std::uint8_t>(*v);
    }
    return out;
}

void Serializer<v2168::ItemStackRequestCereal::CraftRecipeOptionalActionData>::serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::CraftRecipeOptionalActionData &value)
{
    stream.write<std::uint8_t>(15);
    Serializer<RecipeNetId>::serialize(stream, value.recipe_net_id);
    stream.write<std::int32_t>(value.filtered_string_index);
}

auto Serializer<v2168::ItemStackRequestCereal::CraftRecipeOptionalActionData>::deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::CraftRecipeOptionalActionData, std::error_code>
{
    v2168::ItemStackRequestCereal::CraftRecipeOptionalActionData out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 15) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = Serializer<RecipeNetId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.recipe_net_id = *v;
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.filtered_string_index = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<v2168::ItemStackRequestCereal::CraftRepairAndDisenchantActionData>::serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::CraftRepairAndDisenchantActionData &value)
{
    stream.write<std::uint8_t>(16);
    stream.write<std::int32_t>(value.recipe_net_id);
    stream.write<std::uint8_t>(value.num_crafts);
    stream.writeVarInt<std::int32_t>(value.repair_cost);
}

auto Serializer<v2168::ItemStackRequestCereal::CraftRepairAndDisenchantActionData>::deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::CraftRepairAndDisenchantActionData, std::error_code>
{
    v2168::ItemStackRequestCereal::CraftRepairAndDisenchantActionData out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 16) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.recipe_net_id = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.num_crafts = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.repair_cost = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<v2168::ItemStackRequestCereal::CraftLoomActionData>::serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::CraftLoomActionData &value)
{
    stream.write<std::uint8_t>(17);
    stream.write(value.pattern_name_id);
    stream.write<std::uint8_t>(value.num_crafts);
}

auto Serializer<v2168::ItemStackRequestCereal::CraftLoomActionData>::deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::CraftLoomActionData, std::error_code>
{
    v2168::ItemStackRequestCereal::CraftLoomActionData out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 17) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.pattern_name_id = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.num_crafts = static_cast<std::uint8_t>(*v);
    }
    return out;
}

void Serializer<v2168::ItemStackRequestCereal::CraftNonImplementedActionData>::serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::CraftNonImplementedActionData &value)
{
    stream.write<std::uint8_t>(18);
}

auto Serializer<v2168::ItemStackRequestCereal::CraftNonImplementedActionData>::deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::CraftNonImplementedActionData, std::error_code>
{
    v2168::ItemStackRequestCereal::CraftNonImplementedActionData out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 18) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    return out;
}

void Serializer<v2168::ItemStackRequestCereal::CraftResultsActionData>::serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::CraftResultsActionData &value)
{
    stream.write<std::uint8_t>(19);
    stream.writeVarInt<std::uint32_t>(value.craft_results.size());
    for (const auto &e0 : value.craft_results) {
        Serializer<v2168::ItemStackRequestCereal::NetworkItemInstanceDescriptorData>::serialize(stream, e0);
    }
    stream.write<std::uint8_t>(value.num_crafts);
}

auto Serializer<v2168::ItemStackRequestCereal::CraftResultsActionData>::deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::CraftResultsActionData, std::error_code>
{
    v2168::ItemStackRequestCereal::CraftResultsActionData out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 19) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.craft_results.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.craft_results.emplace_back();
            auto v = Serializer<v2168::ItemStackRequestCereal::NetworkItemInstanceDescriptorData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.craft_results.back() = *v;
        }
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.num_crafts = static_cast<std::uint8_t>(*v);
    }
    return out;
}

void Serializer<v2168::ItemStackRequestCereal::RequestData>::serialize(BinaryWriter &stream, const v2168::ItemStackRequestCereal::RequestData &value)
{
    Serializer<ItemStackRequestId>::serialize(stream, value.client_request_id);
    stream.writeVarInt<std::uint32_t>(value.actions.size());
    for (const auto &e0 : value.actions) {
        stream.writeVarInt<std::uint32_t>((e0).index());
        switch ((e0).index()) {
            case 0: {
                Serializer<v2168::ItemStackRequestCereal::TakeActionData>::serialize(stream, std::get<0>(e0));
                break;
            }
            case 1: {
                Serializer<v2168::ItemStackRequestCereal::PlaceActionData>::serialize(stream, std::get<1>(e0));
                break;
            }
            case 2: {
                Serializer<v2168::ItemStackRequestCereal::SwapActionData>::serialize(stream, std::get<2>(e0));
                break;
            }
            case 3: {
                Serializer<v2168::ItemStackRequestCereal::DropActionData>::serialize(stream, std::get<3>(e0));
                break;
            }
            case 4: {
                Serializer<v2168::ItemStackRequestCereal::DestroyActionData>::serialize(stream, std::get<4>(e0));
                break;
            }
            case 5: {
                Serializer<v2168::ItemStackRequestCereal::ConsumeActionData>::serialize(stream, std::get<5>(e0));
                break;
            }
            case 6: {
                Serializer<v2168::ItemStackRequestCereal::CreateActionData>::serialize(stream, std::get<6>(e0));
                break;
            }
            case 7: {
                Serializer<v2168::ItemStackRequestCereal::LabTableCombineActionData>::serialize(stream, std::get<7>(e0));
                break;
            }
            case 8: {
                Serializer<v2168::ItemStackRequestCereal::BeaconPaymentActionData>::serialize(stream, std::get<8>(e0));
                break;
            }
            case 9: {
                Serializer<v2168::ItemStackRequestCereal::MineBlockActionData>::serialize(stream, std::get<9>(e0));
                break;
            }
            case 10: {
                Serializer<v2168::ItemStackRequestCereal::CraftRecipeActionData>::serialize(stream, std::get<10>(e0));
                break;
            }
            case 11: {
                Serializer<v2168::ItemStackRequestCereal::CraftRecipeAutoActionData>::serialize(stream, std::get<11>(e0));
                break;
            }
            case 12: {
                Serializer<v2168::ItemStackRequestCereal::CraftCreativeActionData>::serialize(stream, std::get<12>(e0));
                break;
            }
            case 13: {
                Serializer<v2168::ItemStackRequestCereal::CraftRecipeOptionalActionData>::serialize(stream, std::get<13>(e0));
                break;
            }
            case 14: {
                Serializer<v2168::ItemStackRequestCereal::CraftRepairAndDisenchantActionData>::serialize(stream, std::get<14>(e0));
                break;
            }
            case 15: {
                Serializer<v2168::ItemStackRequestCereal::CraftLoomActionData>::serialize(stream, std::get<15>(e0));
                break;
            }
            case 16: {
                Serializer<v2168::ItemStackRequestCereal::CraftNonImplementedActionData>::serialize(stream, std::get<16>(e0));
                break;
            }
            case 17: {
                Serializer<v2168::ItemStackRequestCereal::CraftResultsActionData>::serialize(stream, std::get<17>(e0));
                break;
            }
        }
    }
    stream.writeVarInt<std::uint32_t>(value.strings_to_filter.size());
    for (const auto &e0 : value.strings_to_filter) {
        stream.write(e0);
    }
    stream.write<std::int32_t>(value.strings_to_filter_origin);
}

auto Serializer<v2168::ItemStackRequestCereal::RequestData>::deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestCereal::RequestData, std::error_code>
{
    v2168::ItemStackRequestCereal::RequestData out;
    {
        auto v = Serializer<ItemStackRequestId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.client_request_id = *v;
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.actions.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.actions.emplace_back();
            auto tag1 = stream.readVarInt<std::uint32_t>();
            if (!tag1) return std::unexpected(tag1.error());
            std::variant<v2168::ItemStackRequestCereal::TakeActionData, v2168::ItemStackRequestCereal::PlaceActionData, v2168::ItemStackRequestCereal::SwapActionData, v2168::ItemStackRequestCereal::DropActionData, v2168::ItemStackRequestCereal::DestroyActionData, v2168::ItemStackRequestCereal::ConsumeActionData, v2168::ItemStackRequestCereal::CreateActionData, v2168::ItemStackRequestCereal::LabTableCombineActionData, v2168::ItemStackRequestCereal::BeaconPaymentActionData, v2168::ItemStackRequestCereal::MineBlockActionData, v2168::ItemStackRequestCereal::CraftRecipeActionData, v2168::ItemStackRequestCereal::CraftRecipeAutoActionData, v2168::ItemStackRequestCereal::CraftCreativeActionData, v2168::ItemStackRequestCereal::CraftRecipeOptionalActionData, v2168::ItemStackRequestCereal::CraftRepairAndDisenchantActionData, v2168::ItemStackRequestCereal::CraftLoomActionData, v2168::ItemStackRequestCereal::CraftNonImplementedActionData, v2168::ItemStackRequestCereal::CraftResultsActionData> var1{};
            switch (*tag1) {
                case 0: {
                    std::variant_alternative_t<0, std::variant<v2168::ItemStackRequestCereal::TakeActionData, v2168::ItemStackRequestCereal::PlaceActionData, v2168::ItemStackRequestCereal::SwapActionData, v2168::ItemStackRequestCereal::DropActionData, v2168::ItemStackRequestCereal::DestroyActionData, v2168::ItemStackRequestCereal::ConsumeActionData, v2168::ItemStackRequestCereal::CreateActionData, v2168::ItemStackRequestCereal::LabTableCombineActionData, v2168::ItemStackRequestCereal::BeaconPaymentActionData, v2168::ItemStackRequestCereal::MineBlockActionData, v2168::ItemStackRequestCereal::CraftRecipeActionData, v2168::ItemStackRequestCereal::CraftRecipeAutoActionData, v2168::ItemStackRequestCereal::CraftCreativeActionData, v2168::ItemStackRequestCereal::CraftRecipeOptionalActionData, v2168::ItemStackRequestCereal::CraftRepairAndDisenchantActionData, v2168::ItemStackRequestCereal::CraftLoomActionData, v2168::ItemStackRequestCereal::CraftNonImplementedActionData, v2168::ItemStackRequestCereal::CraftResultsActionData>> alt1{};
                    {
                        auto v = Serializer<v2168::ItemStackRequestCereal::TakeActionData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<0>(alt1);
                    break;
                }
                case 1: {
                    std::variant_alternative_t<1, std::variant<v2168::ItemStackRequestCereal::TakeActionData, v2168::ItemStackRequestCereal::PlaceActionData, v2168::ItemStackRequestCereal::SwapActionData, v2168::ItemStackRequestCereal::DropActionData, v2168::ItemStackRequestCereal::DestroyActionData, v2168::ItemStackRequestCereal::ConsumeActionData, v2168::ItemStackRequestCereal::CreateActionData, v2168::ItemStackRequestCereal::LabTableCombineActionData, v2168::ItemStackRequestCereal::BeaconPaymentActionData, v2168::ItemStackRequestCereal::MineBlockActionData, v2168::ItemStackRequestCereal::CraftRecipeActionData, v2168::ItemStackRequestCereal::CraftRecipeAutoActionData, v2168::ItemStackRequestCereal::CraftCreativeActionData, v2168::ItemStackRequestCereal::CraftRecipeOptionalActionData, v2168::ItemStackRequestCereal::CraftRepairAndDisenchantActionData, v2168::ItemStackRequestCereal::CraftLoomActionData, v2168::ItemStackRequestCereal::CraftNonImplementedActionData, v2168::ItemStackRequestCereal::CraftResultsActionData>> alt1{};
                    {
                        auto v = Serializer<v2168::ItemStackRequestCereal::PlaceActionData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<1>(alt1);
                    break;
                }
                case 2: {
                    std::variant_alternative_t<2, std::variant<v2168::ItemStackRequestCereal::TakeActionData, v2168::ItemStackRequestCereal::PlaceActionData, v2168::ItemStackRequestCereal::SwapActionData, v2168::ItemStackRequestCereal::DropActionData, v2168::ItemStackRequestCereal::DestroyActionData, v2168::ItemStackRequestCereal::ConsumeActionData, v2168::ItemStackRequestCereal::CreateActionData, v2168::ItemStackRequestCereal::LabTableCombineActionData, v2168::ItemStackRequestCereal::BeaconPaymentActionData, v2168::ItemStackRequestCereal::MineBlockActionData, v2168::ItemStackRequestCereal::CraftRecipeActionData, v2168::ItemStackRequestCereal::CraftRecipeAutoActionData, v2168::ItemStackRequestCereal::CraftCreativeActionData, v2168::ItemStackRequestCereal::CraftRecipeOptionalActionData, v2168::ItemStackRequestCereal::CraftRepairAndDisenchantActionData, v2168::ItemStackRequestCereal::CraftLoomActionData, v2168::ItemStackRequestCereal::CraftNonImplementedActionData, v2168::ItemStackRequestCereal::CraftResultsActionData>> alt1{};
                    {
                        auto v = Serializer<v2168::ItemStackRequestCereal::SwapActionData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<2>(alt1);
                    break;
                }
                case 3: {
                    std::variant_alternative_t<3, std::variant<v2168::ItemStackRequestCereal::TakeActionData, v2168::ItemStackRequestCereal::PlaceActionData, v2168::ItemStackRequestCereal::SwapActionData, v2168::ItemStackRequestCereal::DropActionData, v2168::ItemStackRequestCereal::DestroyActionData, v2168::ItemStackRequestCereal::ConsumeActionData, v2168::ItemStackRequestCereal::CreateActionData, v2168::ItemStackRequestCereal::LabTableCombineActionData, v2168::ItemStackRequestCereal::BeaconPaymentActionData, v2168::ItemStackRequestCereal::MineBlockActionData, v2168::ItemStackRequestCereal::CraftRecipeActionData, v2168::ItemStackRequestCereal::CraftRecipeAutoActionData, v2168::ItemStackRequestCereal::CraftCreativeActionData, v2168::ItemStackRequestCereal::CraftRecipeOptionalActionData, v2168::ItemStackRequestCereal::CraftRepairAndDisenchantActionData, v2168::ItemStackRequestCereal::CraftLoomActionData, v2168::ItemStackRequestCereal::CraftNonImplementedActionData, v2168::ItemStackRequestCereal::CraftResultsActionData>> alt1{};
                    {
                        auto v = Serializer<v2168::ItemStackRequestCereal::DropActionData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<3>(alt1);
                    break;
                }
                case 4: {
                    std::variant_alternative_t<4, std::variant<v2168::ItemStackRequestCereal::TakeActionData, v2168::ItemStackRequestCereal::PlaceActionData, v2168::ItemStackRequestCereal::SwapActionData, v2168::ItemStackRequestCereal::DropActionData, v2168::ItemStackRequestCereal::DestroyActionData, v2168::ItemStackRequestCereal::ConsumeActionData, v2168::ItemStackRequestCereal::CreateActionData, v2168::ItemStackRequestCereal::LabTableCombineActionData, v2168::ItemStackRequestCereal::BeaconPaymentActionData, v2168::ItemStackRequestCereal::MineBlockActionData, v2168::ItemStackRequestCereal::CraftRecipeActionData, v2168::ItemStackRequestCereal::CraftRecipeAutoActionData, v2168::ItemStackRequestCereal::CraftCreativeActionData, v2168::ItemStackRequestCereal::CraftRecipeOptionalActionData, v2168::ItemStackRequestCereal::CraftRepairAndDisenchantActionData, v2168::ItemStackRequestCereal::CraftLoomActionData, v2168::ItemStackRequestCereal::CraftNonImplementedActionData, v2168::ItemStackRequestCereal::CraftResultsActionData>> alt1{};
                    {
                        auto v = Serializer<v2168::ItemStackRequestCereal::DestroyActionData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<4>(alt1);
                    break;
                }
                case 5: {
                    std::variant_alternative_t<5, std::variant<v2168::ItemStackRequestCereal::TakeActionData, v2168::ItemStackRequestCereal::PlaceActionData, v2168::ItemStackRequestCereal::SwapActionData, v2168::ItemStackRequestCereal::DropActionData, v2168::ItemStackRequestCereal::DestroyActionData, v2168::ItemStackRequestCereal::ConsumeActionData, v2168::ItemStackRequestCereal::CreateActionData, v2168::ItemStackRequestCereal::LabTableCombineActionData, v2168::ItemStackRequestCereal::BeaconPaymentActionData, v2168::ItemStackRequestCereal::MineBlockActionData, v2168::ItemStackRequestCereal::CraftRecipeActionData, v2168::ItemStackRequestCereal::CraftRecipeAutoActionData, v2168::ItemStackRequestCereal::CraftCreativeActionData, v2168::ItemStackRequestCereal::CraftRecipeOptionalActionData, v2168::ItemStackRequestCereal::CraftRepairAndDisenchantActionData, v2168::ItemStackRequestCereal::CraftLoomActionData, v2168::ItemStackRequestCereal::CraftNonImplementedActionData, v2168::ItemStackRequestCereal::CraftResultsActionData>> alt1{};
                    {
                        auto v = Serializer<v2168::ItemStackRequestCereal::ConsumeActionData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<5>(alt1);
                    break;
                }
                case 6: {
                    std::variant_alternative_t<6, std::variant<v2168::ItemStackRequestCereal::TakeActionData, v2168::ItemStackRequestCereal::PlaceActionData, v2168::ItemStackRequestCereal::SwapActionData, v2168::ItemStackRequestCereal::DropActionData, v2168::ItemStackRequestCereal::DestroyActionData, v2168::ItemStackRequestCereal::ConsumeActionData, v2168::ItemStackRequestCereal::CreateActionData, v2168::ItemStackRequestCereal::LabTableCombineActionData, v2168::ItemStackRequestCereal::BeaconPaymentActionData, v2168::ItemStackRequestCereal::MineBlockActionData, v2168::ItemStackRequestCereal::CraftRecipeActionData, v2168::ItemStackRequestCereal::CraftRecipeAutoActionData, v2168::ItemStackRequestCereal::CraftCreativeActionData, v2168::ItemStackRequestCereal::CraftRecipeOptionalActionData, v2168::ItemStackRequestCereal::CraftRepairAndDisenchantActionData, v2168::ItemStackRequestCereal::CraftLoomActionData, v2168::ItemStackRequestCereal::CraftNonImplementedActionData, v2168::ItemStackRequestCereal::CraftResultsActionData>> alt1{};
                    {
                        auto v = Serializer<v2168::ItemStackRequestCereal::CreateActionData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<6>(alt1);
                    break;
                }
                case 7: {
                    std::variant_alternative_t<7, std::variant<v2168::ItemStackRequestCereal::TakeActionData, v2168::ItemStackRequestCereal::PlaceActionData, v2168::ItemStackRequestCereal::SwapActionData, v2168::ItemStackRequestCereal::DropActionData, v2168::ItemStackRequestCereal::DestroyActionData, v2168::ItemStackRequestCereal::ConsumeActionData, v2168::ItemStackRequestCereal::CreateActionData, v2168::ItemStackRequestCereal::LabTableCombineActionData, v2168::ItemStackRequestCereal::BeaconPaymentActionData, v2168::ItemStackRequestCereal::MineBlockActionData, v2168::ItemStackRequestCereal::CraftRecipeActionData, v2168::ItemStackRequestCereal::CraftRecipeAutoActionData, v2168::ItemStackRequestCereal::CraftCreativeActionData, v2168::ItemStackRequestCereal::CraftRecipeOptionalActionData, v2168::ItemStackRequestCereal::CraftRepairAndDisenchantActionData, v2168::ItemStackRequestCereal::CraftLoomActionData, v2168::ItemStackRequestCereal::CraftNonImplementedActionData, v2168::ItemStackRequestCereal::CraftResultsActionData>> alt1{};
                    {
                        auto v = Serializer<v2168::ItemStackRequestCereal::LabTableCombineActionData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<7>(alt1);
                    break;
                }
                case 8: {
                    std::variant_alternative_t<8, std::variant<v2168::ItemStackRequestCereal::TakeActionData, v2168::ItemStackRequestCereal::PlaceActionData, v2168::ItemStackRequestCereal::SwapActionData, v2168::ItemStackRequestCereal::DropActionData, v2168::ItemStackRequestCereal::DestroyActionData, v2168::ItemStackRequestCereal::ConsumeActionData, v2168::ItemStackRequestCereal::CreateActionData, v2168::ItemStackRequestCereal::LabTableCombineActionData, v2168::ItemStackRequestCereal::BeaconPaymentActionData, v2168::ItemStackRequestCereal::MineBlockActionData, v2168::ItemStackRequestCereal::CraftRecipeActionData, v2168::ItemStackRequestCereal::CraftRecipeAutoActionData, v2168::ItemStackRequestCereal::CraftCreativeActionData, v2168::ItemStackRequestCereal::CraftRecipeOptionalActionData, v2168::ItemStackRequestCereal::CraftRepairAndDisenchantActionData, v2168::ItemStackRequestCereal::CraftLoomActionData, v2168::ItemStackRequestCereal::CraftNonImplementedActionData, v2168::ItemStackRequestCereal::CraftResultsActionData>> alt1{};
                    {
                        auto v = Serializer<v2168::ItemStackRequestCereal::BeaconPaymentActionData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<8>(alt1);
                    break;
                }
                case 9: {
                    std::variant_alternative_t<9, std::variant<v2168::ItemStackRequestCereal::TakeActionData, v2168::ItemStackRequestCereal::PlaceActionData, v2168::ItemStackRequestCereal::SwapActionData, v2168::ItemStackRequestCereal::DropActionData, v2168::ItemStackRequestCereal::DestroyActionData, v2168::ItemStackRequestCereal::ConsumeActionData, v2168::ItemStackRequestCereal::CreateActionData, v2168::ItemStackRequestCereal::LabTableCombineActionData, v2168::ItemStackRequestCereal::BeaconPaymentActionData, v2168::ItemStackRequestCereal::MineBlockActionData, v2168::ItemStackRequestCereal::CraftRecipeActionData, v2168::ItemStackRequestCereal::CraftRecipeAutoActionData, v2168::ItemStackRequestCereal::CraftCreativeActionData, v2168::ItemStackRequestCereal::CraftRecipeOptionalActionData, v2168::ItemStackRequestCereal::CraftRepairAndDisenchantActionData, v2168::ItemStackRequestCereal::CraftLoomActionData, v2168::ItemStackRequestCereal::CraftNonImplementedActionData, v2168::ItemStackRequestCereal::CraftResultsActionData>> alt1{};
                    {
                        auto v = Serializer<v2168::ItemStackRequestCereal::MineBlockActionData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<9>(alt1);
                    break;
                }
                case 10: {
                    std::variant_alternative_t<10, std::variant<v2168::ItemStackRequestCereal::TakeActionData, v2168::ItemStackRequestCereal::PlaceActionData, v2168::ItemStackRequestCereal::SwapActionData, v2168::ItemStackRequestCereal::DropActionData, v2168::ItemStackRequestCereal::DestroyActionData, v2168::ItemStackRequestCereal::ConsumeActionData, v2168::ItemStackRequestCereal::CreateActionData, v2168::ItemStackRequestCereal::LabTableCombineActionData, v2168::ItemStackRequestCereal::BeaconPaymentActionData, v2168::ItemStackRequestCereal::MineBlockActionData, v2168::ItemStackRequestCereal::CraftRecipeActionData, v2168::ItemStackRequestCereal::CraftRecipeAutoActionData, v2168::ItemStackRequestCereal::CraftCreativeActionData, v2168::ItemStackRequestCereal::CraftRecipeOptionalActionData, v2168::ItemStackRequestCereal::CraftRepairAndDisenchantActionData, v2168::ItemStackRequestCereal::CraftLoomActionData, v2168::ItemStackRequestCereal::CraftNonImplementedActionData, v2168::ItemStackRequestCereal::CraftResultsActionData>> alt1{};
                    {
                        auto v = Serializer<v2168::ItemStackRequestCereal::CraftRecipeActionData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<10>(alt1);
                    break;
                }
                case 11: {
                    std::variant_alternative_t<11, std::variant<v2168::ItemStackRequestCereal::TakeActionData, v2168::ItemStackRequestCereal::PlaceActionData, v2168::ItemStackRequestCereal::SwapActionData, v2168::ItemStackRequestCereal::DropActionData, v2168::ItemStackRequestCereal::DestroyActionData, v2168::ItemStackRequestCereal::ConsumeActionData, v2168::ItemStackRequestCereal::CreateActionData, v2168::ItemStackRequestCereal::LabTableCombineActionData, v2168::ItemStackRequestCereal::BeaconPaymentActionData, v2168::ItemStackRequestCereal::MineBlockActionData, v2168::ItemStackRequestCereal::CraftRecipeActionData, v2168::ItemStackRequestCereal::CraftRecipeAutoActionData, v2168::ItemStackRequestCereal::CraftCreativeActionData, v2168::ItemStackRequestCereal::CraftRecipeOptionalActionData, v2168::ItemStackRequestCereal::CraftRepairAndDisenchantActionData, v2168::ItemStackRequestCereal::CraftLoomActionData, v2168::ItemStackRequestCereal::CraftNonImplementedActionData, v2168::ItemStackRequestCereal::CraftResultsActionData>> alt1{};
                    {
                        auto v = Serializer<v2168::ItemStackRequestCereal::CraftRecipeAutoActionData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<11>(alt1);
                    break;
                }
                case 12: {
                    std::variant_alternative_t<12, std::variant<v2168::ItemStackRequestCereal::TakeActionData, v2168::ItemStackRequestCereal::PlaceActionData, v2168::ItemStackRequestCereal::SwapActionData, v2168::ItemStackRequestCereal::DropActionData, v2168::ItemStackRequestCereal::DestroyActionData, v2168::ItemStackRequestCereal::ConsumeActionData, v2168::ItemStackRequestCereal::CreateActionData, v2168::ItemStackRequestCereal::LabTableCombineActionData, v2168::ItemStackRequestCereal::BeaconPaymentActionData, v2168::ItemStackRequestCereal::MineBlockActionData, v2168::ItemStackRequestCereal::CraftRecipeActionData, v2168::ItemStackRequestCereal::CraftRecipeAutoActionData, v2168::ItemStackRequestCereal::CraftCreativeActionData, v2168::ItemStackRequestCereal::CraftRecipeOptionalActionData, v2168::ItemStackRequestCereal::CraftRepairAndDisenchantActionData, v2168::ItemStackRequestCereal::CraftLoomActionData, v2168::ItemStackRequestCereal::CraftNonImplementedActionData, v2168::ItemStackRequestCereal::CraftResultsActionData>> alt1{};
                    {
                        auto v = Serializer<v2168::ItemStackRequestCereal::CraftCreativeActionData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<12>(alt1);
                    break;
                }
                case 13: {
                    std::variant_alternative_t<13, std::variant<v2168::ItemStackRequestCereal::TakeActionData, v2168::ItemStackRequestCereal::PlaceActionData, v2168::ItemStackRequestCereal::SwapActionData, v2168::ItemStackRequestCereal::DropActionData, v2168::ItemStackRequestCereal::DestroyActionData, v2168::ItemStackRequestCereal::ConsumeActionData, v2168::ItemStackRequestCereal::CreateActionData, v2168::ItemStackRequestCereal::LabTableCombineActionData, v2168::ItemStackRequestCereal::BeaconPaymentActionData, v2168::ItemStackRequestCereal::MineBlockActionData, v2168::ItemStackRequestCereal::CraftRecipeActionData, v2168::ItemStackRequestCereal::CraftRecipeAutoActionData, v2168::ItemStackRequestCereal::CraftCreativeActionData, v2168::ItemStackRequestCereal::CraftRecipeOptionalActionData, v2168::ItemStackRequestCereal::CraftRepairAndDisenchantActionData, v2168::ItemStackRequestCereal::CraftLoomActionData, v2168::ItemStackRequestCereal::CraftNonImplementedActionData, v2168::ItemStackRequestCereal::CraftResultsActionData>> alt1{};
                    {
                        auto v = Serializer<v2168::ItemStackRequestCereal::CraftRecipeOptionalActionData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<13>(alt1);
                    break;
                }
                case 14: {
                    std::variant_alternative_t<14, std::variant<v2168::ItemStackRequestCereal::TakeActionData, v2168::ItemStackRequestCereal::PlaceActionData, v2168::ItemStackRequestCereal::SwapActionData, v2168::ItemStackRequestCereal::DropActionData, v2168::ItemStackRequestCereal::DestroyActionData, v2168::ItemStackRequestCereal::ConsumeActionData, v2168::ItemStackRequestCereal::CreateActionData, v2168::ItemStackRequestCereal::LabTableCombineActionData, v2168::ItemStackRequestCereal::BeaconPaymentActionData, v2168::ItemStackRequestCereal::MineBlockActionData, v2168::ItemStackRequestCereal::CraftRecipeActionData, v2168::ItemStackRequestCereal::CraftRecipeAutoActionData, v2168::ItemStackRequestCereal::CraftCreativeActionData, v2168::ItemStackRequestCereal::CraftRecipeOptionalActionData, v2168::ItemStackRequestCereal::CraftRepairAndDisenchantActionData, v2168::ItemStackRequestCereal::CraftLoomActionData, v2168::ItemStackRequestCereal::CraftNonImplementedActionData, v2168::ItemStackRequestCereal::CraftResultsActionData>> alt1{};
                    {
                        auto v = Serializer<v2168::ItemStackRequestCereal::CraftRepairAndDisenchantActionData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<14>(alt1);
                    break;
                }
                case 15: {
                    std::variant_alternative_t<15, std::variant<v2168::ItemStackRequestCereal::TakeActionData, v2168::ItemStackRequestCereal::PlaceActionData, v2168::ItemStackRequestCereal::SwapActionData, v2168::ItemStackRequestCereal::DropActionData, v2168::ItemStackRequestCereal::DestroyActionData, v2168::ItemStackRequestCereal::ConsumeActionData, v2168::ItemStackRequestCereal::CreateActionData, v2168::ItemStackRequestCereal::LabTableCombineActionData, v2168::ItemStackRequestCereal::BeaconPaymentActionData, v2168::ItemStackRequestCereal::MineBlockActionData, v2168::ItemStackRequestCereal::CraftRecipeActionData, v2168::ItemStackRequestCereal::CraftRecipeAutoActionData, v2168::ItemStackRequestCereal::CraftCreativeActionData, v2168::ItemStackRequestCereal::CraftRecipeOptionalActionData, v2168::ItemStackRequestCereal::CraftRepairAndDisenchantActionData, v2168::ItemStackRequestCereal::CraftLoomActionData, v2168::ItemStackRequestCereal::CraftNonImplementedActionData, v2168::ItemStackRequestCereal::CraftResultsActionData>> alt1{};
                    {
                        auto v = Serializer<v2168::ItemStackRequestCereal::CraftLoomActionData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<15>(alt1);
                    break;
                }
                case 16: {
                    std::variant_alternative_t<16, std::variant<v2168::ItemStackRequestCereal::TakeActionData, v2168::ItemStackRequestCereal::PlaceActionData, v2168::ItemStackRequestCereal::SwapActionData, v2168::ItemStackRequestCereal::DropActionData, v2168::ItemStackRequestCereal::DestroyActionData, v2168::ItemStackRequestCereal::ConsumeActionData, v2168::ItemStackRequestCereal::CreateActionData, v2168::ItemStackRequestCereal::LabTableCombineActionData, v2168::ItemStackRequestCereal::BeaconPaymentActionData, v2168::ItemStackRequestCereal::MineBlockActionData, v2168::ItemStackRequestCereal::CraftRecipeActionData, v2168::ItemStackRequestCereal::CraftRecipeAutoActionData, v2168::ItemStackRequestCereal::CraftCreativeActionData, v2168::ItemStackRequestCereal::CraftRecipeOptionalActionData, v2168::ItemStackRequestCereal::CraftRepairAndDisenchantActionData, v2168::ItemStackRequestCereal::CraftLoomActionData, v2168::ItemStackRequestCereal::CraftNonImplementedActionData, v2168::ItemStackRequestCereal::CraftResultsActionData>> alt1{};
                    {
                        auto v = Serializer<v2168::ItemStackRequestCereal::CraftNonImplementedActionData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<16>(alt1);
                    break;
                }
                case 17: {
                    std::variant_alternative_t<17, std::variant<v2168::ItemStackRequestCereal::TakeActionData, v2168::ItemStackRequestCereal::PlaceActionData, v2168::ItemStackRequestCereal::SwapActionData, v2168::ItemStackRequestCereal::DropActionData, v2168::ItemStackRequestCereal::DestroyActionData, v2168::ItemStackRequestCereal::ConsumeActionData, v2168::ItemStackRequestCereal::CreateActionData, v2168::ItemStackRequestCereal::LabTableCombineActionData, v2168::ItemStackRequestCereal::BeaconPaymentActionData, v2168::ItemStackRequestCereal::MineBlockActionData, v2168::ItemStackRequestCereal::CraftRecipeActionData, v2168::ItemStackRequestCereal::CraftRecipeAutoActionData, v2168::ItemStackRequestCereal::CraftCreativeActionData, v2168::ItemStackRequestCereal::CraftRecipeOptionalActionData, v2168::ItemStackRequestCereal::CraftRepairAndDisenchantActionData, v2168::ItemStackRequestCereal::CraftLoomActionData, v2168::ItemStackRequestCereal::CraftNonImplementedActionData, v2168::ItemStackRequestCereal::CraftResultsActionData>> alt1{};
                    {
                        auto v = Serializer<v2168::ItemStackRequestCereal::CraftResultsActionData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<17>(alt1);
                    break;
                }
                default: {
                    return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
                }
            }
            out.actions.back() = var1;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.strings_to_filter.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.strings_to_filter.emplace_back();
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.strings_to_filter.back() = *v;
        }
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.strings_to_filter_origin = static_cast<v975::TextProcessingEventOrigin>(*v);
    }
    return out;
}

void Serializer<v2225::ItemStackRequestCereal::MolangItemDescriptorData>::serialize(BinaryWriter &stream, const v2225::ItemStackRequestCereal::MolangItemDescriptorData &value)
{
    stream.write<std::uint8_t>(2);
    stream.write(value.tag_expression);
    stream.write<std::int16_t>(value.molang_version);
}

auto Serializer<v2225::ItemStackRequestCereal::MolangItemDescriptorData>::deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackRequestCereal::MolangItemDescriptorData, std::error_code>
{
    v2225::ItemStackRequestCereal::MolangItemDescriptorData out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 2) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.tag_expression = *v;
    }
    {
        auto v = stream.read<std::int16_t>();
        if (!v) return std::unexpected(v.error());
        out.molang_version = static_cast<v827::MolangVersion>(*v);
    }
    return out;
}

void Serializer<v2225::ItemStackRequestCereal::SlotInfoData>::serialize(BinaryWriter &stream, const v2225::ItemStackRequestCereal::SlotInfoData &value)
{
    Serializer<v2225::FullContainerName>::serialize(stream, value.full_container_name);
    stream.write<std::uint8_t>(value.slot);
    stream.write<std::int32_t>(value.net_id_variant);
}

auto Serializer<v2225::ItemStackRequestCereal::SlotInfoData>::deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackRequestCereal::SlotInfoData, std::error_code>
{
    v2225::ItemStackRequestCereal::SlotInfoData out;
    {
        auto v = Serializer<v2225::FullContainerName>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.full_container_name = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.net_id_variant = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<v2225::ItemStackRequestCereal::TakeActionData>::serialize(BinaryWriter &stream, const v2225::ItemStackRequestCereal::TakeActionData &value)
{
    stream.write<std::uint8_t>(0);
    stream.write<std::uint8_t>(value.amount);
    Serializer<v2225::ItemStackRequestCereal::SlotInfoData>::serialize(stream, value.source);
    Serializer<v2225::ItemStackRequestCereal::SlotInfoData>::serialize(stream, value.destination);
}

auto Serializer<v2225::ItemStackRequestCereal::TakeActionData>::deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackRequestCereal::TakeActionData, std::error_code>
{
    v2225::ItemStackRequestCereal::TakeActionData out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 0) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.amount = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = Serializer<v2225::ItemStackRequestCereal::SlotInfoData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.source = *v;
    }
    {
        auto v = Serializer<v2225::ItemStackRequestCereal::SlotInfoData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.destination = *v;
    }
    return out;
}

void Serializer<v2225::ItemStackRequestCereal::PlaceActionData>::serialize(BinaryWriter &stream, const v2225::ItemStackRequestCereal::PlaceActionData &value)
{
    stream.write<std::uint8_t>(1);
    stream.write<std::uint8_t>(value.amount);
    Serializer<v2225::ItemStackRequestCereal::SlotInfoData>::serialize(stream, value.source);
    Serializer<v2225::ItemStackRequestCereal::SlotInfoData>::serialize(stream, value.destination);
}

auto Serializer<v2225::ItemStackRequestCereal::PlaceActionData>::deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackRequestCereal::PlaceActionData, std::error_code>
{
    v2225::ItemStackRequestCereal::PlaceActionData out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 1) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.amount = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = Serializer<v2225::ItemStackRequestCereal::SlotInfoData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.source = *v;
    }
    {
        auto v = Serializer<v2225::ItemStackRequestCereal::SlotInfoData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.destination = *v;
    }
    return out;
}

void Serializer<v2225::ItemStackRequestCereal::SwapActionData>::serialize(BinaryWriter &stream, const v2225::ItemStackRequestCereal::SwapActionData &value)
{
    stream.write<std::uint8_t>(2);
    Serializer<v2225::ItemStackRequestCereal::SlotInfoData>::serialize(stream, value.source);
    Serializer<v2225::ItemStackRequestCereal::SlotInfoData>::serialize(stream, value.destination);
}

auto Serializer<v2225::ItemStackRequestCereal::SwapActionData>::deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackRequestCereal::SwapActionData, std::error_code>
{
    v2225::ItemStackRequestCereal::SwapActionData out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 2) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = Serializer<v2225::ItemStackRequestCereal::SlotInfoData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.source = *v;
    }
    {
        auto v = Serializer<v2225::ItemStackRequestCereal::SlotInfoData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.destination = *v;
    }
    return out;
}

void Serializer<v2225::ItemStackRequestCereal::DropActionData>::serialize(BinaryWriter &stream, const v2225::ItemStackRequestCereal::DropActionData &value)
{
    stream.write<std::uint8_t>(3);
    stream.write<std::uint8_t>(value.amount);
    Serializer<v2225::ItemStackRequestCereal::SlotInfoData>::serialize(stream, value.source);
    stream.write<bool>(value.randomly);
}

auto Serializer<v2225::ItemStackRequestCereal::DropActionData>::deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackRequestCereal::DropActionData, std::error_code>
{
    v2225::ItemStackRequestCereal::DropActionData out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 3) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.amount = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = Serializer<v2225::ItemStackRequestCereal::SlotInfoData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.source = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.randomly = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v2225::ItemStackRequestCereal::DestroyActionData>::serialize(BinaryWriter &stream, const v2225::ItemStackRequestCereal::DestroyActionData &value)
{
    stream.write<std::uint8_t>(4);
    stream.write<std::uint8_t>(value.amount);
    Serializer<v2225::ItemStackRequestCereal::SlotInfoData>::serialize(stream, value.source);
}

auto Serializer<v2225::ItemStackRequestCereal::DestroyActionData>::deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackRequestCereal::DestroyActionData, std::error_code>
{
    v2225::ItemStackRequestCereal::DestroyActionData out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 4) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.amount = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = Serializer<v2225::ItemStackRequestCereal::SlotInfoData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.source = *v;
    }
    return out;
}

void Serializer<v2225::ItemStackRequestCereal::ConsumeActionData>::serialize(BinaryWriter &stream, const v2225::ItemStackRequestCereal::ConsumeActionData &value)
{
    stream.write<std::uint8_t>(5);
    stream.write<std::uint8_t>(value.amount);
    Serializer<v2225::ItemStackRequestCereal::SlotInfoData>::serialize(stream, value.source);
}

auto Serializer<v2225::ItemStackRequestCereal::ConsumeActionData>::deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackRequestCereal::ConsumeActionData, std::error_code>
{
    v2225::ItemStackRequestCereal::ConsumeActionData out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 5) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.amount = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = Serializer<v2225::ItemStackRequestCereal::SlotInfoData>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.source = *v;
    }
    return out;
}

void Serializer<v2225::ItemStackRequestCereal::CreateActionData>::serialize(BinaryWriter &stream, const v2225::ItemStackRequestCereal::CreateActionData &value)
{
    stream.write<std::uint8_t>(6);
    stream.write<std::uint8_t>(value.results_index);
}

auto Serializer<v2225::ItemStackRequestCereal::CreateActionData>::deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackRequestCereal::CreateActionData, std::error_code>
{
    v2225::ItemStackRequestCereal::CreateActionData out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 6) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.results_index = static_cast<std::uint8_t>(*v);
    }
    return out;
}

void Serializer<v2225::ItemStackRequestCereal::LabTableCombineActionData>::serialize(BinaryWriter &stream, const v2225::ItemStackRequestCereal::LabTableCombineActionData &value)
{
    stream.write<std::uint8_t>(9);
}

auto Serializer<v2225::ItemStackRequestCereal::LabTableCombineActionData>::deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackRequestCereal::LabTableCombineActionData, std::error_code>
{
    v2225::ItemStackRequestCereal::LabTableCombineActionData out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 9) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    return out;
}

void Serializer<v2225::ItemStackRequestCereal::BeaconPaymentActionData>::serialize(BinaryWriter &stream, const v2225::ItemStackRequestCereal::BeaconPaymentActionData &value)
{
    stream.write<std::uint8_t>(10);
    stream.writeVarInt<std::int32_t>(value.primary_effect_id);
    stream.writeVarInt<std::int32_t>(value.secondary_effect_id);
}

auto Serializer<v2225::ItemStackRequestCereal::BeaconPaymentActionData>::deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackRequestCereal::BeaconPaymentActionData, std::error_code>
{
    v2225::ItemStackRequestCereal::BeaconPaymentActionData out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 10) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.primary_effect_id = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.secondary_effect_id = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<v2225::ItemStackRequestCereal::MineBlockActionData>::serialize(BinaryWriter &stream, const v2225::ItemStackRequestCereal::MineBlockActionData &value)
{
    stream.write<std::uint8_t>(11);
    stream.writeVarInt<std::int32_t>(value.slot);
    stream.writeVarInt<std::int32_t>(value.predicted_durability);
    stream.write<std::int32_t>(value.net_id_variant);
}

auto Serializer<v2225::ItemStackRequestCereal::MineBlockActionData>::deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackRequestCereal::MineBlockActionData, std::error_code>
{
    v2225::ItemStackRequestCereal::MineBlockActionData out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 11) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.predicted_durability = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.net_id_variant = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<v2225::ItemStackRequestCereal::CraftRecipeActionData>::serialize(BinaryWriter &stream, const v2225::ItemStackRequestCereal::CraftRecipeActionData &value)
{
    stream.write<std::uint8_t>(12);
    Serializer<RecipeNetId>::serialize(stream, value.recipe_net_id);
    stream.write<std::uint8_t>(value.num_crafts);
}

auto Serializer<v2225::ItemStackRequestCereal::CraftRecipeActionData>::deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackRequestCereal::CraftRecipeActionData, std::error_code>
{
    v2225::ItemStackRequestCereal::CraftRecipeActionData out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 12) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = Serializer<RecipeNetId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.recipe_net_id = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.num_crafts = static_cast<std::uint8_t>(*v);
    }
    return out;
}

void Serializer<v2225::ItemStackRequestCereal::CraftRecipeAutoActionData>::serialize(BinaryWriter &stream, const v2225::ItemStackRequestCereal::CraftRecipeAutoActionData &value)
{
    stream.write<std::uint8_t>(13);
    Serializer<RecipeNetId>::serialize(stream, value.recipe_net_id);
    stream.write<std::uint8_t>(value.num_crafts);
    stream.writeVarInt<std::uint32_t>(value.ingredients.size());
    for (const auto &e0 : value.ingredients) {
        Serializer<v2225::ItemStackRequestCereal::RecipeIngredientData>::serialize(stream, e0);
    }
}

auto Serializer<v2225::ItemStackRequestCereal::CraftRecipeAutoActionData>::deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackRequestCereal::CraftRecipeAutoActionData, std::error_code>
{
    v2225::ItemStackRequestCereal::CraftRecipeAutoActionData out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 13) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = Serializer<RecipeNetId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.recipe_net_id = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.num_crafts = static_cast<std::uint8_t>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.ingredients.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.ingredients.emplace_back();
            auto v = Serializer<v2225::ItemStackRequestCereal::RecipeIngredientData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.ingredients.back() = *v;
        }
    }
    return out;
}

void Serializer<v2225::ItemStackRequestCereal::CraftCreativeActionData>::serialize(BinaryWriter &stream, const v2225::ItemStackRequestCereal::CraftCreativeActionData &value)
{
    stream.write<std::uint8_t>(14);
    stream.writeVarInt<std::uint32_t>(value.creative_item_net_id);
    stream.write<std::uint8_t>(value.num_crafts);
}

auto Serializer<v2225::ItemStackRequestCereal::CraftCreativeActionData>::deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackRequestCereal::CraftCreativeActionData, std::error_code>
{
    v2225::ItemStackRequestCereal::CraftCreativeActionData out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 14) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.creative_item_net_id = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.num_crafts = static_cast<std::uint8_t>(*v);
    }
    return out;
}

void Serializer<v2225::ItemStackRequestCereal::CraftRecipeOptionalActionData>::serialize(BinaryWriter &stream, const v2225::ItemStackRequestCereal::CraftRecipeOptionalActionData &value)
{
    stream.write<std::uint8_t>(15);
    Serializer<RecipeNetId>::serialize(stream, value.recipe_net_id);
    stream.write<std::int32_t>(value.filtered_string_index);
}

auto Serializer<v2225::ItemStackRequestCereal::CraftRecipeOptionalActionData>::deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackRequestCereal::CraftRecipeOptionalActionData, std::error_code>
{
    v2225::ItemStackRequestCereal::CraftRecipeOptionalActionData out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 15) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = Serializer<RecipeNetId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.recipe_net_id = *v;
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.filtered_string_index = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<v2225::ItemStackRequestCereal::CraftRepairAndDisenchantActionData>::serialize(BinaryWriter &stream, const v2225::ItemStackRequestCereal::CraftRepairAndDisenchantActionData &value)
{
    stream.write<std::uint8_t>(16);
    stream.write<std::int32_t>(value.recipe_net_id);
    stream.write<std::uint8_t>(value.num_crafts);
    stream.writeVarInt<std::int32_t>(value.repair_cost);
}

auto Serializer<v2225::ItemStackRequestCereal::CraftRepairAndDisenchantActionData>::deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackRequestCereal::CraftRepairAndDisenchantActionData, std::error_code>
{
    v2225::ItemStackRequestCereal::CraftRepairAndDisenchantActionData out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 16) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.recipe_net_id = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.num_crafts = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.repair_cost = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<v2225::ItemStackRequestCereal::CraftLoomActionData>::serialize(BinaryWriter &stream, const v2225::ItemStackRequestCereal::CraftLoomActionData &value)
{
    stream.write<std::uint8_t>(17);
    stream.write(value.pattern_name_id);
    stream.write<std::uint8_t>(value.num_crafts);
}

auto Serializer<v2225::ItemStackRequestCereal::CraftLoomActionData>::deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackRequestCereal::CraftLoomActionData, std::error_code>
{
    v2225::ItemStackRequestCereal::CraftLoomActionData out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 17) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.pattern_name_id = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.num_crafts = static_cast<std::uint8_t>(*v);
    }
    return out;
}

void Serializer<v2225::ItemStackRequestCereal::CraftDiscPressActionData>::serialize(BinaryWriter &stream, const v2225::ItemStackRequestCereal::CraftDiscPressActionData &value)
{
    stream.write<std::uint8_t>(18);
    stream.write(value.reserved_id);
    stream.write<std::uint8_t>(value.num_crafts);
}

auto Serializer<v2225::ItemStackRequestCereal::CraftDiscPressActionData>::deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackRequestCereal::CraftDiscPressActionData, std::error_code>
{
    v2225::ItemStackRequestCereal::CraftDiscPressActionData out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 18) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.reserved_id = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.num_crafts = static_cast<std::uint8_t>(*v);
    }
    return out;
}

void Serializer<v2225::ItemStackRequestCereal::CraftNonImplementedActionData>::serialize(BinaryWriter &stream, const v2225::ItemStackRequestCereal::CraftNonImplementedActionData &value)
{
    stream.write<std::uint8_t>(19);
}

auto Serializer<v2225::ItemStackRequestCereal::CraftNonImplementedActionData>::deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackRequestCereal::CraftNonImplementedActionData, std::error_code>
{
    v2225::ItemStackRequestCereal::CraftNonImplementedActionData out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 19) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    return out;
}

void Serializer<v2225::ItemStackRequestCereal::CraftResultsActionData>::serialize(BinaryWriter &stream, const v2225::ItemStackRequestCereal::CraftResultsActionData &value)
{
    stream.write<std::uint8_t>(20);
    stream.writeVarInt<std::uint32_t>(value.craft_results.size());
    for (const auto &e0 : value.craft_results) {
        Serializer<v2225::ItemStackRequestCereal::NetworkItemInstanceDescriptorData>::serialize(stream, e0);
    }
    stream.write<std::uint8_t>(value.num_crafts);
}

auto Serializer<v2225::ItemStackRequestCereal::CraftResultsActionData>::deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackRequestCereal::CraftResultsActionData, std::error_code>
{
    v2225::ItemStackRequestCereal::CraftResultsActionData out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        if (*v != 20) {
            return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.craft_results.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.craft_results.emplace_back();
            auto v = Serializer<v2225::ItemStackRequestCereal::NetworkItemInstanceDescriptorData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.craft_results.back() = *v;
        }
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.num_crafts = static_cast<std::uint8_t>(*v);
    }
    return out;
}

void Serializer<v2225::ItemStackRequestCereal::RequestData>::serialize(BinaryWriter &stream, const v2225::ItemStackRequestCereal::RequestData &value)
{
    Serializer<ItemStackRequestId>::serialize(stream, value.client_request_id);
    stream.writeVarInt<std::uint32_t>(value.actions.size());
    for (const auto &e0 : value.actions) {
        stream.writeVarInt<std::uint32_t>((e0).index());
        switch ((e0).index()) {
            case 0: {
                Serializer<v2225::ItemStackRequestCereal::TakeActionData>::serialize(stream, std::get<0>(e0));
                break;
            }
            case 1: {
                Serializer<v2225::ItemStackRequestCereal::PlaceActionData>::serialize(stream, std::get<1>(e0));
                break;
            }
            case 2: {
                Serializer<v2225::ItemStackRequestCereal::SwapActionData>::serialize(stream, std::get<2>(e0));
                break;
            }
            case 3: {
                Serializer<v2225::ItemStackRequestCereal::DropActionData>::serialize(stream, std::get<3>(e0));
                break;
            }
            case 4: {
                Serializer<v2225::ItemStackRequestCereal::DestroyActionData>::serialize(stream, std::get<4>(e0));
                break;
            }
            case 5: {
                Serializer<v2225::ItemStackRequestCereal::ConsumeActionData>::serialize(stream, std::get<5>(e0));
                break;
            }
            case 6: {
                Serializer<v2225::ItemStackRequestCereal::CreateActionData>::serialize(stream, std::get<6>(e0));
                break;
            }
            case 7: {
                Serializer<v2225::ItemStackRequestCereal::LabTableCombineActionData>::serialize(stream, std::get<7>(e0));
                break;
            }
            case 8: {
                Serializer<v2225::ItemStackRequestCereal::BeaconPaymentActionData>::serialize(stream, std::get<8>(e0));
                break;
            }
            case 9: {
                Serializer<v2225::ItemStackRequestCereal::MineBlockActionData>::serialize(stream, std::get<9>(e0));
                break;
            }
            case 10: {
                Serializer<v2225::ItemStackRequestCereal::CraftRecipeActionData>::serialize(stream, std::get<10>(e0));
                break;
            }
            case 11: {
                Serializer<v2225::ItemStackRequestCereal::CraftRecipeAutoActionData>::serialize(stream, std::get<11>(e0));
                break;
            }
            case 12: {
                Serializer<v2225::ItemStackRequestCereal::CraftCreativeActionData>::serialize(stream, std::get<12>(e0));
                break;
            }
            case 13: {
                Serializer<v2225::ItemStackRequestCereal::CraftRecipeOptionalActionData>::serialize(stream, std::get<13>(e0));
                break;
            }
            case 14: {
                Serializer<v2225::ItemStackRequestCereal::CraftRepairAndDisenchantActionData>::serialize(stream, std::get<14>(e0));
                break;
            }
            case 15: {
                Serializer<v2225::ItemStackRequestCereal::CraftLoomActionData>::serialize(stream, std::get<15>(e0));
                break;
            }
            case 16: {
                Serializer<v2225::ItemStackRequestCereal::CraftDiscPressActionData>::serialize(stream, std::get<16>(e0));
                break;
            }
            case 17: {
                Serializer<v2225::ItemStackRequestCereal::CraftNonImplementedActionData>::serialize(stream, std::get<17>(e0));
                break;
            }
            case 18: {
                Serializer<v2225::ItemStackRequestCereal::CraftResultsActionData>::serialize(stream, std::get<18>(e0));
                break;
            }
        }
    }
    stream.writeVarInt<std::uint32_t>(value.strings_to_filter.size());
    for (const auto &e0 : value.strings_to_filter) {
        stream.write(e0);
    }
    stream.write<std::int32_t>(value.strings_to_filter_origin);
}

auto Serializer<v2225::ItemStackRequestCereal::RequestData>::deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackRequestCereal::RequestData, std::error_code>
{
    v2225::ItemStackRequestCereal::RequestData out;
    {
        auto v = Serializer<ItemStackRequestId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.client_request_id = *v;
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.actions.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.actions.emplace_back();
            auto tag1 = stream.readVarInt<std::uint32_t>();
            if (!tag1) return std::unexpected(tag1.error());
            std::variant<v2225::ItemStackRequestCereal::TakeActionData, v2225::ItemStackRequestCereal::PlaceActionData, v2225::ItemStackRequestCereal::SwapActionData, v2225::ItemStackRequestCereal::DropActionData, v2225::ItemStackRequestCereal::DestroyActionData, v2225::ItemStackRequestCereal::ConsumeActionData, v2225::ItemStackRequestCereal::CreateActionData, v2225::ItemStackRequestCereal::LabTableCombineActionData, v2225::ItemStackRequestCereal::BeaconPaymentActionData, v2225::ItemStackRequestCereal::MineBlockActionData, v2225::ItemStackRequestCereal::CraftRecipeActionData, v2225::ItemStackRequestCereal::CraftRecipeAutoActionData, v2225::ItemStackRequestCereal::CraftCreativeActionData, v2225::ItemStackRequestCereal::CraftRecipeOptionalActionData, v2225::ItemStackRequestCereal::CraftRepairAndDisenchantActionData, v2225::ItemStackRequestCereal::CraftLoomActionData, v2225::ItemStackRequestCereal::CraftDiscPressActionData, v2225::ItemStackRequestCereal::CraftNonImplementedActionData, v2225::ItemStackRequestCereal::CraftResultsActionData> var1{};
            switch (*tag1) {
                case 0: {
                    std::variant_alternative_t<0, std::variant<v2225::ItemStackRequestCereal::TakeActionData, v2225::ItemStackRequestCereal::PlaceActionData, v2225::ItemStackRequestCereal::SwapActionData, v2225::ItemStackRequestCereal::DropActionData, v2225::ItemStackRequestCereal::DestroyActionData, v2225::ItemStackRequestCereal::ConsumeActionData, v2225::ItemStackRequestCereal::CreateActionData, v2225::ItemStackRequestCereal::LabTableCombineActionData, v2225::ItemStackRequestCereal::BeaconPaymentActionData, v2225::ItemStackRequestCereal::MineBlockActionData, v2225::ItemStackRequestCereal::CraftRecipeActionData, v2225::ItemStackRequestCereal::CraftRecipeAutoActionData, v2225::ItemStackRequestCereal::CraftCreativeActionData, v2225::ItemStackRequestCereal::CraftRecipeOptionalActionData, v2225::ItemStackRequestCereal::CraftRepairAndDisenchantActionData, v2225::ItemStackRequestCereal::CraftLoomActionData, v2225::ItemStackRequestCereal::CraftDiscPressActionData, v2225::ItemStackRequestCereal::CraftNonImplementedActionData, v2225::ItemStackRequestCereal::CraftResultsActionData>> alt1{};
                    {
                        auto v = Serializer<v2225::ItemStackRequestCereal::TakeActionData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<0>(alt1);
                    break;
                }
                case 1: {
                    std::variant_alternative_t<1, std::variant<v2225::ItemStackRequestCereal::TakeActionData, v2225::ItemStackRequestCereal::PlaceActionData, v2225::ItemStackRequestCereal::SwapActionData, v2225::ItemStackRequestCereal::DropActionData, v2225::ItemStackRequestCereal::DestroyActionData, v2225::ItemStackRequestCereal::ConsumeActionData, v2225::ItemStackRequestCereal::CreateActionData, v2225::ItemStackRequestCereal::LabTableCombineActionData, v2225::ItemStackRequestCereal::BeaconPaymentActionData, v2225::ItemStackRequestCereal::MineBlockActionData, v2225::ItemStackRequestCereal::CraftRecipeActionData, v2225::ItemStackRequestCereal::CraftRecipeAutoActionData, v2225::ItemStackRequestCereal::CraftCreativeActionData, v2225::ItemStackRequestCereal::CraftRecipeOptionalActionData, v2225::ItemStackRequestCereal::CraftRepairAndDisenchantActionData, v2225::ItemStackRequestCereal::CraftLoomActionData, v2225::ItemStackRequestCereal::CraftDiscPressActionData, v2225::ItemStackRequestCereal::CraftNonImplementedActionData, v2225::ItemStackRequestCereal::CraftResultsActionData>> alt1{};
                    {
                        auto v = Serializer<v2225::ItemStackRequestCereal::PlaceActionData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<1>(alt1);
                    break;
                }
                case 2: {
                    std::variant_alternative_t<2, std::variant<v2225::ItemStackRequestCereal::TakeActionData, v2225::ItemStackRequestCereal::PlaceActionData, v2225::ItemStackRequestCereal::SwapActionData, v2225::ItemStackRequestCereal::DropActionData, v2225::ItemStackRequestCereal::DestroyActionData, v2225::ItemStackRequestCereal::ConsumeActionData, v2225::ItemStackRequestCereal::CreateActionData, v2225::ItemStackRequestCereal::LabTableCombineActionData, v2225::ItemStackRequestCereal::BeaconPaymentActionData, v2225::ItemStackRequestCereal::MineBlockActionData, v2225::ItemStackRequestCereal::CraftRecipeActionData, v2225::ItemStackRequestCereal::CraftRecipeAutoActionData, v2225::ItemStackRequestCereal::CraftCreativeActionData, v2225::ItemStackRequestCereal::CraftRecipeOptionalActionData, v2225::ItemStackRequestCereal::CraftRepairAndDisenchantActionData, v2225::ItemStackRequestCereal::CraftLoomActionData, v2225::ItemStackRequestCereal::CraftDiscPressActionData, v2225::ItemStackRequestCereal::CraftNonImplementedActionData, v2225::ItemStackRequestCereal::CraftResultsActionData>> alt1{};
                    {
                        auto v = Serializer<v2225::ItemStackRequestCereal::SwapActionData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<2>(alt1);
                    break;
                }
                case 3: {
                    std::variant_alternative_t<3, std::variant<v2225::ItemStackRequestCereal::TakeActionData, v2225::ItemStackRequestCereal::PlaceActionData, v2225::ItemStackRequestCereal::SwapActionData, v2225::ItemStackRequestCereal::DropActionData, v2225::ItemStackRequestCereal::DestroyActionData, v2225::ItemStackRequestCereal::ConsumeActionData, v2225::ItemStackRequestCereal::CreateActionData, v2225::ItemStackRequestCereal::LabTableCombineActionData, v2225::ItemStackRequestCereal::BeaconPaymentActionData, v2225::ItemStackRequestCereal::MineBlockActionData, v2225::ItemStackRequestCereal::CraftRecipeActionData, v2225::ItemStackRequestCereal::CraftRecipeAutoActionData, v2225::ItemStackRequestCereal::CraftCreativeActionData, v2225::ItemStackRequestCereal::CraftRecipeOptionalActionData, v2225::ItemStackRequestCereal::CraftRepairAndDisenchantActionData, v2225::ItemStackRequestCereal::CraftLoomActionData, v2225::ItemStackRequestCereal::CraftDiscPressActionData, v2225::ItemStackRequestCereal::CraftNonImplementedActionData, v2225::ItemStackRequestCereal::CraftResultsActionData>> alt1{};
                    {
                        auto v = Serializer<v2225::ItemStackRequestCereal::DropActionData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<3>(alt1);
                    break;
                }
                case 4: {
                    std::variant_alternative_t<4, std::variant<v2225::ItemStackRequestCereal::TakeActionData, v2225::ItemStackRequestCereal::PlaceActionData, v2225::ItemStackRequestCereal::SwapActionData, v2225::ItemStackRequestCereal::DropActionData, v2225::ItemStackRequestCereal::DestroyActionData, v2225::ItemStackRequestCereal::ConsumeActionData, v2225::ItemStackRequestCereal::CreateActionData, v2225::ItemStackRequestCereal::LabTableCombineActionData, v2225::ItemStackRequestCereal::BeaconPaymentActionData, v2225::ItemStackRequestCereal::MineBlockActionData, v2225::ItemStackRequestCereal::CraftRecipeActionData, v2225::ItemStackRequestCereal::CraftRecipeAutoActionData, v2225::ItemStackRequestCereal::CraftCreativeActionData, v2225::ItemStackRequestCereal::CraftRecipeOptionalActionData, v2225::ItemStackRequestCereal::CraftRepairAndDisenchantActionData, v2225::ItemStackRequestCereal::CraftLoomActionData, v2225::ItemStackRequestCereal::CraftDiscPressActionData, v2225::ItemStackRequestCereal::CraftNonImplementedActionData, v2225::ItemStackRequestCereal::CraftResultsActionData>> alt1{};
                    {
                        auto v = Serializer<v2225::ItemStackRequestCereal::DestroyActionData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<4>(alt1);
                    break;
                }
                case 5: {
                    std::variant_alternative_t<5, std::variant<v2225::ItemStackRequestCereal::TakeActionData, v2225::ItemStackRequestCereal::PlaceActionData, v2225::ItemStackRequestCereal::SwapActionData, v2225::ItemStackRequestCereal::DropActionData, v2225::ItemStackRequestCereal::DestroyActionData, v2225::ItemStackRequestCereal::ConsumeActionData, v2225::ItemStackRequestCereal::CreateActionData, v2225::ItemStackRequestCereal::LabTableCombineActionData, v2225::ItemStackRequestCereal::BeaconPaymentActionData, v2225::ItemStackRequestCereal::MineBlockActionData, v2225::ItemStackRequestCereal::CraftRecipeActionData, v2225::ItemStackRequestCereal::CraftRecipeAutoActionData, v2225::ItemStackRequestCereal::CraftCreativeActionData, v2225::ItemStackRequestCereal::CraftRecipeOptionalActionData, v2225::ItemStackRequestCereal::CraftRepairAndDisenchantActionData, v2225::ItemStackRequestCereal::CraftLoomActionData, v2225::ItemStackRequestCereal::CraftDiscPressActionData, v2225::ItemStackRequestCereal::CraftNonImplementedActionData, v2225::ItemStackRequestCereal::CraftResultsActionData>> alt1{};
                    {
                        auto v = Serializer<v2225::ItemStackRequestCereal::ConsumeActionData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<5>(alt1);
                    break;
                }
                case 6: {
                    std::variant_alternative_t<6, std::variant<v2225::ItemStackRequestCereal::TakeActionData, v2225::ItemStackRequestCereal::PlaceActionData, v2225::ItemStackRequestCereal::SwapActionData, v2225::ItemStackRequestCereal::DropActionData, v2225::ItemStackRequestCereal::DestroyActionData, v2225::ItemStackRequestCereal::ConsumeActionData, v2225::ItemStackRequestCereal::CreateActionData, v2225::ItemStackRequestCereal::LabTableCombineActionData, v2225::ItemStackRequestCereal::BeaconPaymentActionData, v2225::ItemStackRequestCereal::MineBlockActionData, v2225::ItemStackRequestCereal::CraftRecipeActionData, v2225::ItemStackRequestCereal::CraftRecipeAutoActionData, v2225::ItemStackRequestCereal::CraftCreativeActionData, v2225::ItemStackRequestCereal::CraftRecipeOptionalActionData, v2225::ItemStackRequestCereal::CraftRepairAndDisenchantActionData, v2225::ItemStackRequestCereal::CraftLoomActionData, v2225::ItemStackRequestCereal::CraftDiscPressActionData, v2225::ItemStackRequestCereal::CraftNonImplementedActionData, v2225::ItemStackRequestCereal::CraftResultsActionData>> alt1{};
                    {
                        auto v = Serializer<v2225::ItemStackRequestCereal::CreateActionData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<6>(alt1);
                    break;
                }
                case 7: {
                    std::variant_alternative_t<7, std::variant<v2225::ItemStackRequestCereal::TakeActionData, v2225::ItemStackRequestCereal::PlaceActionData, v2225::ItemStackRequestCereal::SwapActionData, v2225::ItemStackRequestCereal::DropActionData, v2225::ItemStackRequestCereal::DestroyActionData, v2225::ItemStackRequestCereal::ConsumeActionData, v2225::ItemStackRequestCereal::CreateActionData, v2225::ItemStackRequestCereal::LabTableCombineActionData, v2225::ItemStackRequestCereal::BeaconPaymentActionData, v2225::ItemStackRequestCereal::MineBlockActionData, v2225::ItemStackRequestCereal::CraftRecipeActionData, v2225::ItemStackRequestCereal::CraftRecipeAutoActionData, v2225::ItemStackRequestCereal::CraftCreativeActionData, v2225::ItemStackRequestCereal::CraftRecipeOptionalActionData, v2225::ItemStackRequestCereal::CraftRepairAndDisenchantActionData, v2225::ItemStackRequestCereal::CraftLoomActionData, v2225::ItemStackRequestCereal::CraftDiscPressActionData, v2225::ItemStackRequestCereal::CraftNonImplementedActionData, v2225::ItemStackRequestCereal::CraftResultsActionData>> alt1{};
                    {
                        auto v = Serializer<v2225::ItemStackRequestCereal::LabTableCombineActionData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<7>(alt1);
                    break;
                }
                case 8: {
                    std::variant_alternative_t<8, std::variant<v2225::ItemStackRequestCereal::TakeActionData, v2225::ItemStackRequestCereal::PlaceActionData, v2225::ItemStackRequestCereal::SwapActionData, v2225::ItemStackRequestCereal::DropActionData, v2225::ItemStackRequestCereal::DestroyActionData, v2225::ItemStackRequestCereal::ConsumeActionData, v2225::ItemStackRequestCereal::CreateActionData, v2225::ItemStackRequestCereal::LabTableCombineActionData, v2225::ItemStackRequestCereal::BeaconPaymentActionData, v2225::ItemStackRequestCereal::MineBlockActionData, v2225::ItemStackRequestCereal::CraftRecipeActionData, v2225::ItemStackRequestCereal::CraftRecipeAutoActionData, v2225::ItemStackRequestCereal::CraftCreativeActionData, v2225::ItemStackRequestCereal::CraftRecipeOptionalActionData, v2225::ItemStackRequestCereal::CraftRepairAndDisenchantActionData, v2225::ItemStackRequestCereal::CraftLoomActionData, v2225::ItemStackRequestCereal::CraftDiscPressActionData, v2225::ItemStackRequestCereal::CraftNonImplementedActionData, v2225::ItemStackRequestCereal::CraftResultsActionData>> alt1{};
                    {
                        auto v = Serializer<v2225::ItemStackRequestCereal::BeaconPaymentActionData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<8>(alt1);
                    break;
                }
                case 9: {
                    std::variant_alternative_t<9, std::variant<v2225::ItemStackRequestCereal::TakeActionData, v2225::ItemStackRequestCereal::PlaceActionData, v2225::ItemStackRequestCereal::SwapActionData, v2225::ItemStackRequestCereal::DropActionData, v2225::ItemStackRequestCereal::DestroyActionData, v2225::ItemStackRequestCereal::ConsumeActionData, v2225::ItemStackRequestCereal::CreateActionData, v2225::ItemStackRequestCereal::LabTableCombineActionData, v2225::ItemStackRequestCereal::BeaconPaymentActionData, v2225::ItemStackRequestCereal::MineBlockActionData, v2225::ItemStackRequestCereal::CraftRecipeActionData, v2225::ItemStackRequestCereal::CraftRecipeAutoActionData, v2225::ItemStackRequestCereal::CraftCreativeActionData, v2225::ItemStackRequestCereal::CraftRecipeOptionalActionData, v2225::ItemStackRequestCereal::CraftRepairAndDisenchantActionData, v2225::ItemStackRequestCereal::CraftLoomActionData, v2225::ItemStackRequestCereal::CraftDiscPressActionData, v2225::ItemStackRequestCereal::CraftNonImplementedActionData, v2225::ItemStackRequestCereal::CraftResultsActionData>> alt1{};
                    {
                        auto v = Serializer<v2225::ItemStackRequestCereal::MineBlockActionData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<9>(alt1);
                    break;
                }
                case 10: {
                    std::variant_alternative_t<10, std::variant<v2225::ItemStackRequestCereal::TakeActionData, v2225::ItemStackRequestCereal::PlaceActionData, v2225::ItemStackRequestCereal::SwapActionData, v2225::ItemStackRequestCereal::DropActionData, v2225::ItemStackRequestCereal::DestroyActionData, v2225::ItemStackRequestCereal::ConsumeActionData, v2225::ItemStackRequestCereal::CreateActionData, v2225::ItemStackRequestCereal::LabTableCombineActionData, v2225::ItemStackRequestCereal::BeaconPaymentActionData, v2225::ItemStackRequestCereal::MineBlockActionData, v2225::ItemStackRequestCereal::CraftRecipeActionData, v2225::ItemStackRequestCereal::CraftRecipeAutoActionData, v2225::ItemStackRequestCereal::CraftCreativeActionData, v2225::ItemStackRequestCereal::CraftRecipeOptionalActionData, v2225::ItemStackRequestCereal::CraftRepairAndDisenchantActionData, v2225::ItemStackRequestCereal::CraftLoomActionData, v2225::ItemStackRequestCereal::CraftDiscPressActionData, v2225::ItemStackRequestCereal::CraftNonImplementedActionData, v2225::ItemStackRequestCereal::CraftResultsActionData>> alt1{};
                    {
                        auto v = Serializer<v2225::ItemStackRequestCereal::CraftRecipeActionData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<10>(alt1);
                    break;
                }
                case 11: {
                    std::variant_alternative_t<11, std::variant<v2225::ItemStackRequestCereal::TakeActionData, v2225::ItemStackRequestCereal::PlaceActionData, v2225::ItemStackRequestCereal::SwapActionData, v2225::ItemStackRequestCereal::DropActionData, v2225::ItemStackRequestCereal::DestroyActionData, v2225::ItemStackRequestCereal::ConsumeActionData, v2225::ItemStackRequestCereal::CreateActionData, v2225::ItemStackRequestCereal::LabTableCombineActionData, v2225::ItemStackRequestCereal::BeaconPaymentActionData, v2225::ItemStackRequestCereal::MineBlockActionData, v2225::ItemStackRequestCereal::CraftRecipeActionData, v2225::ItemStackRequestCereal::CraftRecipeAutoActionData, v2225::ItemStackRequestCereal::CraftCreativeActionData, v2225::ItemStackRequestCereal::CraftRecipeOptionalActionData, v2225::ItemStackRequestCereal::CraftRepairAndDisenchantActionData, v2225::ItemStackRequestCereal::CraftLoomActionData, v2225::ItemStackRequestCereal::CraftDiscPressActionData, v2225::ItemStackRequestCereal::CraftNonImplementedActionData, v2225::ItemStackRequestCereal::CraftResultsActionData>> alt1{};
                    {
                        auto v = Serializer<v2225::ItemStackRequestCereal::CraftRecipeAutoActionData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<11>(alt1);
                    break;
                }
                case 12: {
                    std::variant_alternative_t<12, std::variant<v2225::ItemStackRequestCereal::TakeActionData, v2225::ItemStackRequestCereal::PlaceActionData, v2225::ItemStackRequestCereal::SwapActionData, v2225::ItemStackRequestCereal::DropActionData, v2225::ItemStackRequestCereal::DestroyActionData, v2225::ItemStackRequestCereal::ConsumeActionData, v2225::ItemStackRequestCereal::CreateActionData, v2225::ItemStackRequestCereal::LabTableCombineActionData, v2225::ItemStackRequestCereal::BeaconPaymentActionData, v2225::ItemStackRequestCereal::MineBlockActionData, v2225::ItemStackRequestCereal::CraftRecipeActionData, v2225::ItemStackRequestCereal::CraftRecipeAutoActionData, v2225::ItemStackRequestCereal::CraftCreativeActionData, v2225::ItemStackRequestCereal::CraftRecipeOptionalActionData, v2225::ItemStackRequestCereal::CraftRepairAndDisenchantActionData, v2225::ItemStackRequestCereal::CraftLoomActionData, v2225::ItemStackRequestCereal::CraftDiscPressActionData, v2225::ItemStackRequestCereal::CraftNonImplementedActionData, v2225::ItemStackRequestCereal::CraftResultsActionData>> alt1{};
                    {
                        auto v = Serializer<v2225::ItemStackRequestCereal::CraftCreativeActionData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<12>(alt1);
                    break;
                }
                case 13: {
                    std::variant_alternative_t<13, std::variant<v2225::ItemStackRequestCereal::TakeActionData, v2225::ItemStackRequestCereal::PlaceActionData, v2225::ItemStackRequestCereal::SwapActionData, v2225::ItemStackRequestCereal::DropActionData, v2225::ItemStackRequestCereal::DestroyActionData, v2225::ItemStackRequestCereal::ConsumeActionData, v2225::ItemStackRequestCereal::CreateActionData, v2225::ItemStackRequestCereal::LabTableCombineActionData, v2225::ItemStackRequestCereal::BeaconPaymentActionData, v2225::ItemStackRequestCereal::MineBlockActionData, v2225::ItemStackRequestCereal::CraftRecipeActionData, v2225::ItemStackRequestCereal::CraftRecipeAutoActionData, v2225::ItemStackRequestCereal::CraftCreativeActionData, v2225::ItemStackRequestCereal::CraftRecipeOptionalActionData, v2225::ItemStackRequestCereal::CraftRepairAndDisenchantActionData, v2225::ItemStackRequestCereal::CraftLoomActionData, v2225::ItemStackRequestCereal::CraftDiscPressActionData, v2225::ItemStackRequestCereal::CraftNonImplementedActionData, v2225::ItemStackRequestCereal::CraftResultsActionData>> alt1{};
                    {
                        auto v = Serializer<v2225::ItemStackRequestCereal::CraftRecipeOptionalActionData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<13>(alt1);
                    break;
                }
                case 14: {
                    std::variant_alternative_t<14, std::variant<v2225::ItemStackRequestCereal::TakeActionData, v2225::ItemStackRequestCereal::PlaceActionData, v2225::ItemStackRequestCereal::SwapActionData, v2225::ItemStackRequestCereal::DropActionData, v2225::ItemStackRequestCereal::DestroyActionData, v2225::ItemStackRequestCereal::ConsumeActionData, v2225::ItemStackRequestCereal::CreateActionData, v2225::ItemStackRequestCereal::LabTableCombineActionData, v2225::ItemStackRequestCereal::BeaconPaymentActionData, v2225::ItemStackRequestCereal::MineBlockActionData, v2225::ItemStackRequestCereal::CraftRecipeActionData, v2225::ItemStackRequestCereal::CraftRecipeAutoActionData, v2225::ItemStackRequestCereal::CraftCreativeActionData, v2225::ItemStackRequestCereal::CraftRecipeOptionalActionData, v2225::ItemStackRequestCereal::CraftRepairAndDisenchantActionData, v2225::ItemStackRequestCereal::CraftLoomActionData, v2225::ItemStackRequestCereal::CraftDiscPressActionData, v2225::ItemStackRequestCereal::CraftNonImplementedActionData, v2225::ItemStackRequestCereal::CraftResultsActionData>> alt1{};
                    {
                        auto v = Serializer<v2225::ItemStackRequestCereal::CraftRepairAndDisenchantActionData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<14>(alt1);
                    break;
                }
                case 15: {
                    std::variant_alternative_t<15, std::variant<v2225::ItemStackRequestCereal::TakeActionData, v2225::ItemStackRequestCereal::PlaceActionData, v2225::ItemStackRequestCereal::SwapActionData, v2225::ItemStackRequestCereal::DropActionData, v2225::ItemStackRequestCereal::DestroyActionData, v2225::ItemStackRequestCereal::ConsumeActionData, v2225::ItemStackRequestCereal::CreateActionData, v2225::ItemStackRequestCereal::LabTableCombineActionData, v2225::ItemStackRequestCereal::BeaconPaymentActionData, v2225::ItemStackRequestCereal::MineBlockActionData, v2225::ItemStackRequestCereal::CraftRecipeActionData, v2225::ItemStackRequestCereal::CraftRecipeAutoActionData, v2225::ItemStackRequestCereal::CraftCreativeActionData, v2225::ItemStackRequestCereal::CraftRecipeOptionalActionData, v2225::ItemStackRequestCereal::CraftRepairAndDisenchantActionData, v2225::ItemStackRequestCereal::CraftLoomActionData, v2225::ItemStackRequestCereal::CraftDiscPressActionData, v2225::ItemStackRequestCereal::CraftNonImplementedActionData, v2225::ItemStackRequestCereal::CraftResultsActionData>> alt1{};
                    {
                        auto v = Serializer<v2225::ItemStackRequestCereal::CraftLoomActionData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<15>(alt1);
                    break;
                }
                case 16: {
                    std::variant_alternative_t<16, std::variant<v2225::ItemStackRequestCereal::TakeActionData, v2225::ItemStackRequestCereal::PlaceActionData, v2225::ItemStackRequestCereal::SwapActionData, v2225::ItemStackRequestCereal::DropActionData, v2225::ItemStackRequestCereal::DestroyActionData, v2225::ItemStackRequestCereal::ConsumeActionData, v2225::ItemStackRequestCereal::CreateActionData, v2225::ItemStackRequestCereal::LabTableCombineActionData, v2225::ItemStackRequestCereal::BeaconPaymentActionData, v2225::ItemStackRequestCereal::MineBlockActionData, v2225::ItemStackRequestCereal::CraftRecipeActionData, v2225::ItemStackRequestCereal::CraftRecipeAutoActionData, v2225::ItemStackRequestCereal::CraftCreativeActionData, v2225::ItemStackRequestCereal::CraftRecipeOptionalActionData, v2225::ItemStackRequestCereal::CraftRepairAndDisenchantActionData, v2225::ItemStackRequestCereal::CraftLoomActionData, v2225::ItemStackRequestCereal::CraftDiscPressActionData, v2225::ItemStackRequestCereal::CraftNonImplementedActionData, v2225::ItemStackRequestCereal::CraftResultsActionData>> alt1{};
                    {
                        auto v = Serializer<v2225::ItemStackRequestCereal::CraftDiscPressActionData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<16>(alt1);
                    break;
                }
                case 17: {
                    std::variant_alternative_t<17, std::variant<v2225::ItemStackRequestCereal::TakeActionData, v2225::ItemStackRequestCereal::PlaceActionData, v2225::ItemStackRequestCereal::SwapActionData, v2225::ItemStackRequestCereal::DropActionData, v2225::ItemStackRequestCereal::DestroyActionData, v2225::ItemStackRequestCereal::ConsumeActionData, v2225::ItemStackRequestCereal::CreateActionData, v2225::ItemStackRequestCereal::LabTableCombineActionData, v2225::ItemStackRequestCereal::BeaconPaymentActionData, v2225::ItemStackRequestCereal::MineBlockActionData, v2225::ItemStackRequestCereal::CraftRecipeActionData, v2225::ItemStackRequestCereal::CraftRecipeAutoActionData, v2225::ItemStackRequestCereal::CraftCreativeActionData, v2225::ItemStackRequestCereal::CraftRecipeOptionalActionData, v2225::ItemStackRequestCereal::CraftRepairAndDisenchantActionData, v2225::ItemStackRequestCereal::CraftLoomActionData, v2225::ItemStackRequestCereal::CraftDiscPressActionData, v2225::ItemStackRequestCereal::CraftNonImplementedActionData, v2225::ItemStackRequestCereal::CraftResultsActionData>> alt1{};
                    {
                        auto v = Serializer<v2225::ItemStackRequestCereal::CraftNonImplementedActionData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<17>(alt1);
                    break;
                }
                case 18: {
                    std::variant_alternative_t<18, std::variant<v2225::ItemStackRequestCereal::TakeActionData, v2225::ItemStackRequestCereal::PlaceActionData, v2225::ItemStackRequestCereal::SwapActionData, v2225::ItemStackRequestCereal::DropActionData, v2225::ItemStackRequestCereal::DestroyActionData, v2225::ItemStackRequestCereal::ConsumeActionData, v2225::ItemStackRequestCereal::CreateActionData, v2225::ItemStackRequestCereal::LabTableCombineActionData, v2225::ItemStackRequestCereal::BeaconPaymentActionData, v2225::ItemStackRequestCereal::MineBlockActionData, v2225::ItemStackRequestCereal::CraftRecipeActionData, v2225::ItemStackRequestCereal::CraftRecipeAutoActionData, v2225::ItemStackRequestCereal::CraftCreativeActionData, v2225::ItemStackRequestCereal::CraftRecipeOptionalActionData, v2225::ItemStackRequestCereal::CraftRepairAndDisenchantActionData, v2225::ItemStackRequestCereal::CraftLoomActionData, v2225::ItemStackRequestCereal::CraftDiscPressActionData, v2225::ItemStackRequestCereal::CraftNonImplementedActionData, v2225::ItemStackRequestCereal::CraftResultsActionData>> alt1{};
                    {
                        auto v = Serializer<v2225::ItemStackRequestCereal::CraftResultsActionData>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<18>(alt1);
                    break;
                }
                default: {
                    return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
                }
            }
            out.actions.back() = var1;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.strings_to_filter.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.strings_to_filter.emplace_back();
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.strings_to_filter.back() = *v;
        }
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.strings_to_filter_origin = static_cast<v975::TextProcessingEventOrigin>(*v);
    }
    return out;
}

void Serializer<base::ItemStackRequestSlotInfo>::serialize(BinaryWriter &stream, const base::ItemStackRequestSlotInfo &value)
{
    Serializer<base::FullContainerName>::serialize(stream, value.full_container_name);
    stream.write<std::uint8_t>(value.slot);
    stream.writeVarInt<std::int32_t>(value.net_id_variant);
}

auto Serializer<base::ItemStackRequestSlotInfo>::deserialize(BinaryReader &stream) -> std::expected<base::ItemStackRequestSlotInfo, std::error_code>
{
    base::ItemStackRequestSlotInfo out;
    {
        auto v = Serializer<base::FullContainerName>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.full_container_name = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.net_id_variant = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<v924::ItemStackRequestSlotInfo>::serialize(BinaryWriter &stream, const v924::ItemStackRequestSlotInfo &value)
{
    Serializer<v924::FullContainerName>::serialize(stream, value.full_container_name);
    stream.write<std::uint8_t>(value.slot);
    stream.writeVarInt<std::int32_t>(value.net_id_variant);
}

auto Serializer<v924::ItemStackRequestSlotInfo>::deserialize(BinaryReader &stream) -> std::expected<v924::ItemStackRequestSlotInfo, std::error_code>
{
    v924::ItemStackRequestSlotInfo out;
    {
        auto v = Serializer<v924::FullContainerName>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.full_container_name = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.net_id_variant = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<base::ItemStackRequestActionTake>::serialize(BinaryWriter &stream, const base::ItemStackRequestActionTake &value)
{
    stream.write<std::uint8_t>(value.amount);
    Serializer<base::ItemStackRequestSlotInfo>::serialize(stream, value.src);
    Serializer<base::ItemStackRequestSlotInfo>::serialize(stream, value.dst);
}

auto Serializer<base::ItemStackRequestActionTake>::deserialize(BinaryReader &stream) -> std::expected<base::ItemStackRequestActionTake, std::error_code>
{
    base::ItemStackRequestActionTake out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.amount = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = Serializer<base::ItemStackRequestSlotInfo>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.src = *v;
    }
    {
        auto v = Serializer<base::ItemStackRequestSlotInfo>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.dst = *v;
    }
    return out;
}

void Serializer<v924::ItemStackRequestActionTake>::serialize(BinaryWriter &stream, const v924::ItemStackRequestActionTake &value)
{
    stream.write<std::uint8_t>(value.amount);
    Serializer<v924::ItemStackRequestSlotInfo>::serialize(stream, value.src);
    Serializer<v924::ItemStackRequestSlotInfo>::serialize(stream, value.dst);
}

auto Serializer<v924::ItemStackRequestActionTake>::deserialize(BinaryReader &stream) -> std::expected<v924::ItemStackRequestActionTake, std::error_code>
{
    v924::ItemStackRequestActionTake out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.amount = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = Serializer<v924::ItemStackRequestSlotInfo>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.src = *v;
    }
    {
        auto v = Serializer<v924::ItemStackRequestSlotInfo>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.dst = *v;
    }
    return out;
}

void Serializer<base::ItemStackRequestActionPlace>::serialize(BinaryWriter &stream, const base::ItemStackRequestActionPlace &value)
{
    stream.write<std::uint8_t>(value.amount);
    Serializer<base::ItemStackRequestSlotInfo>::serialize(stream, value.src);
    Serializer<base::ItemStackRequestSlotInfo>::serialize(stream, value.dst);
}

auto Serializer<base::ItemStackRequestActionPlace>::deserialize(BinaryReader &stream) -> std::expected<base::ItemStackRequestActionPlace, std::error_code>
{
    base::ItemStackRequestActionPlace out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.amount = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = Serializer<base::ItemStackRequestSlotInfo>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.src = *v;
    }
    {
        auto v = Serializer<base::ItemStackRequestSlotInfo>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.dst = *v;
    }
    return out;
}

void Serializer<v924::ItemStackRequestActionPlace>::serialize(BinaryWriter &stream, const v924::ItemStackRequestActionPlace &value)
{
    stream.write<std::uint8_t>(value.amount);
    Serializer<v924::ItemStackRequestSlotInfo>::serialize(stream, value.src);
    Serializer<v924::ItemStackRequestSlotInfo>::serialize(stream, value.dst);
}

auto Serializer<v924::ItemStackRequestActionPlace>::deserialize(BinaryReader &stream) -> std::expected<v924::ItemStackRequestActionPlace, std::error_code>
{
    v924::ItemStackRequestActionPlace out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.amount = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = Serializer<v924::ItemStackRequestSlotInfo>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.src = *v;
    }
    {
        auto v = Serializer<v924::ItemStackRequestSlotInfo>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.dst = *v;
    }
    return out;
}

void Serializer<base::ItemStackRequestActionSwap>::serialize(BinaryWriter &stream, const base::ItemStackRequestActionSwap &value)
{
    Serializer<base::ItemStackRequestSlotInfo>::serialize(stream, value.src);
    Serializer<base::ItemStackRequestSlotInfo>::serialize(stream, value.dst);
}

auto Serializer<base::ItemStackRequestActionSwap>::deserialize(BinaryReader &stream) -> std::expected<base::ItemStackRequestActionSwap, std::error_code>
{
    base::ItemStackRequestActionSwap out;
    {
        auto v = Serializer<base::ItemStackRequestSlotInfo>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.src = *v;
    }
    {
        auto v = Serializer<base::ItemStackRequestSlotInfo>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.dst = *v;
    }
    return out;
}

void Serializer<v924::ItemStackRequestActionSwap>::serialize(BinaryWriter &stream, const v924::ItemStackRequestActionSwap &value)
{
    Serializer<v924::ItemStackRequestSlotInfo>::serialize(stream, value.src);
    Serializer<v924::ItemStackRequestSlotInfo>::serialize(stream, value.dst);
}

auto Serializer<v924::ItemStackRequestActionSwap>::deserialize(BinaryReader &stream) -> std::expected<v924::ItemStackRequestActionSwap, std::error_code>
{
    v924::ItemStackRequestActionSwap out;
    {
        auto v = Serializer<v924::ItemStackRequestSlotInfo>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.src = *v;
    }
    {
        auto v = Serializer<v924::ItemStackRequestSlotInfo>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.dst = *v;
    }
    return out;
}

void Serializer<base::ItemStackRequestActionDrop>::serialize(BinaryWriter &stream, const base::ItemStackRequestActionDrop &value)
{
    stream.write<std::uint8_t>(value.amount);
    Serializer<base::ItemStackRequestSlotInfo>::serialize(stream, value.src);
    stream.write<bool>(value.randomly);
}

auto Serializer<base::ItemStackRequestActionDrop>::deserialize(BinaryReader &stream) -> std::expected<base::ItemStackRequestActionDrop, std::error_code>
{
    base::ItemStackRequestActionDrop out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.amount = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = Serializer<base::ItemStackRequestSlotInfo>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.src = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.randomly = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<v924::ItemStackRequestActionDrop>::serialize(BinaryWriter &stream, const v924::ItemStackRequestActionDrop &value)
{
    stream.write<std::uint8_t>(value.amount);
    Serializer<v924::ItemStackRequestSlotInfo>::serialize(stream, value.src);
    stream.write<bool>(value.randomly);
}

auto Serializer<v924::ItemStackRequestActionDrop>::deserialize(BinaryReader &stream) -> std::expected<v924::ItemStackRequestActionDrop, std::error_code>
{
    v924::ItemStackRequestActionDrop out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.amount = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = Serializer<v924::ItemStackRequestSlotInfo>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.src = *v;
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.randomly = static_cast<bool>(*v);
    }
    return out;
}

void Serializer<base::ItemStackRequestActionDestroy>::serialize(BinaryWriter &stream, const base::ItemStackRequestActionDestroy &value)
{
    stream.write<std::uint8_t>(value.amount);
    Serializer<base::ItemStackRequestSlotInfo>::serialize(stream, value.src);
}

auto Serializer<base::ItemStackRequestActionDestroy>::deserialize(BinaryReader &stream) -> std::expected<base::ItemStackRequestActionDestroy, std::error_code>
{
    base::ItemStackRequestActionDestroy out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.amount = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = Serializer<base::ItemStackRequestSlotInfo>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.src = *v;
    }
    return out;
}

void Serializer<v924::ItemStackRequestActionDestroy>::serialize(BinaryWriter &stream, const v924::ItemStackRequestActionDestroy &value)
{
    stream.write<std::uint8_t>(value.amount);
    Serializer<v924::ItemStackRequestSlotInfo>::serialize(stream, value.src);
}

auto Serializer<v924::ItemStackRequestActionDestroy>::deserialize(BinaryReader &stream) -> std::expected<v924::ItemStackRequestActionDestroy, std::error_code>
{
    v924::ItemStackRequestActionDestroy out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.amount = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = Serializer<v924::ItemStackRequestSlotInfo>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.src = *v;
    }
    return out;
}

void Serializer<base::ItemStackRequestActionConsume>::serialize(BinaryWriter &stream, const base::ItemStackRequestActionConsume &value)
{
    stream.write<std::uint8_t>(value.amount);
    Serializer<base::ItemStackRequestSlotInfo>::serialize(stream, value.src);
}

auto Serializer<base::ItemStackRequestActionConsume>::deserialize(BinaryReader &stream) -> std::expected<base::ItemStackRequestActionConsume, std::error_code>
{
    base::ItemStackRequestActionConsume out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.amount = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = Serializer<base::ItemStackRequestSlotInfo>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.src = *v;
    }
    return out;
}

void Serializer<v924::ItemStackRequestActionConsume>::serialize(BinaryWriter &stream, const v924::ItemStackRequestActionConsume &value)
{
    stream.write<std::uint8_t>(value.amount);
    Serializer<v924::ItemStackRequestSlotInfo>::serialize(stream, value.src);
}

auto Serializer<v924::ItemStackRequestActionConsume>::deserialize(BinaryReader &stream) -> std::expected<v924::ItemStackRequestActionConsume, std::error_code>
{
    v924::ItemStackRequestActionConsume out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.amount = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = Serializer<v924::ItemStackRequestSlotInfo>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.src = *v;
    }
    return out;
}

void Serializer<base::ItemStackRequestActionCreate>::serialize(BinaryWriter &stream, const base::ItemStackRequestActionCreate &value)
{
    stream.write<std::uint8_t>(value.results_index);
}

auto Serializer<base::ItemStackRequestActionCreate>::deserialize(BinaryReader &stream) -> std::expected<base::ItemStackRequestActionCreate, std::error_code>
{
    base::ItemStackRequestActionCreate out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.results_index = static_cast<std::uint8_t>(*v);
    }
    return out;
}

void Serializer<base::ItemStackRequestActionLabTableCombine>::serialize(BinaryWriter &stream, const base::ItemStackRequestActionLabTableCombine &value)
{
}

auto Serializer<base::ItemStackRequestActionLabTableCombine>::deserialize(BinaryReader &stream) -> std::expected<base::ItemStackRequestActionLabTableCombine, std::error_code>
{
    base::ItemStackRequestActionLabTableCombine out;
    return out;
}

void Serializer<base::ItemStackRequestActionBeaconPayment>::serialize(BinaryWriter &stream, const base::ItemStackRequestActionBeaconPayment &value)
{
    stream.writeVarInt<std::int32_t>(value.primary_effect_id);
    stream.writeVarInt<std::int32_t>(value.secondary_effect_id);
}

auto Serializer<base::ItemStackRequestActionBeaconPayment>::deserialize(BinaryReader &stream) -> std::expected<base::ItemStackRequestActionBeaconPayment, std::error_code>
{
    base::ItemStackRequestActionBeaconPayment out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.primary_effect_id = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.secondary_effect_id = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<base::ItemStackRequestActionMineBlock>::serialize(BinaryWriter &stream, const base::ItemStackRequestActionMineBlock &value)
{
    stream.writeVarInt<std::int32_t>(value.slot);
    stream.writeVarInt<std::int32_t>(value.predicted_durability);
    stream.writeVarInt<std::int32_t>(value.net_id_variant);
}

auto Serializer<base::ItemStackRequestActionMineBlock>::deserialize(BinaryReader &stream) -> std::expected<base::ItemStackRequestActionMineBlock, std::error_code>
{
    base::ItemStackRequestActionMineBlock out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.slot = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.predicted_durability = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.net_id_variant = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<base::ItemStackRequestActionCraftRecipe>::serialize(BinaryWriter &stream, const base::ItemStackRequestActionCraftRecipe &value)
{
    Serializer<RecipeNetId>::serialize(stream, value.recipe_net_id);
    stream.write<std::uint8_t>(value.num_crafts);
}

auto Serializer<base::ItemStackRequestActionCraftRecipe>::deserialize(BinaryReader &stream) -> std::expected<base::ItemStackRequestActionCraftRecipe, std::error_code>
{
    base::ItemStackRequestActionCraftRecipe out;
    {
        auto v = Serializer<RecipeNetId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.recipe_net_id = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.num_crafts = static_cast<std::uint8_t>(*v);
    }
    return out;
}

void Serializer<base::ItemStackRequestActionCraftRecipeAuto>::serialize(BinaryWriter &stream, const base::ItemStackRequestActionCraftRecipeAuto &value)
{
    Serializer<RecipeNetId>::serialize(stream, value.recipe_net_id);
    stream.write<std::uint8_t>(value.num_crafts);
    stream.write<std::uint8_t>(value.num_ingredients);
    stream.writeVarInt<std::uint32_t>(value.ingredients.size());
    for (const auto &e0 : value.ingredients) {
        Serializer<base::SerializedRecipeIngredient>::serialize(stream, e0);
    }
}

auto Serializer<base::ItemStackRequestActionCraftRecipeAuto>::deserialize(BinaryReader &stream) -> std::expected<base::ItemStackRequestActionCraftRecipeAuto, std::error_code>
{
    base::ItemStackRequestActionCraftRecipeAuto out;
    {
        auto v = Serializer<RecipeNetId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.recipe_net_id = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.num_crafts = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.num_ingredients = static_cast<std::uint8_t>(*v);
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.ingredients.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.ingredients.emplace_back();
            auto v = Serializer<base::SerializedRecipeIngredient>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.ingredients.back() = *v;
        }
    }
    return out;
}

void Serializer<base::ItemStackRequestActionCraftCreative>::serialize(BinaryWriter &stream, const base::ItemStackRequestActionCraftCreative &value)
{
    Serializer<CreativeItemNetId>::serialize(stream, value.creative_item_net_id);
    stream.write<std::uint8_t>(value.num_crafts);
}

auto Serializer<base::ItemStackRequestActionCraftCreative>::deserialize(BinaryReader &stream) -> std::expected<base::ItemStackRequestActionCraftCreative, std::error_code>
{
    base::ItemStackRequestActionCraftCreative out;
    {
        auto v = Serializer<CreativeItemNetId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.creative_item_net_id = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.num_crafts = static_cast<std::uint8_t>(*v);
    }
    return out;
}

void Serializer<base::ItemStackRequestActionCraftRecipeOptional>::serialize(BinaryWriter &stream, const base::ItemStackRequestActionCraftRecipeOptional &value)
{
    Serializer<RecipeNetId>::serialize(stream, value.recipe_net_id);
    stream.write<std::int32_t>(value.filtered_string_index);
}

auto Serializer<base::ItemStackRequestActionCraftRecipeOptional>::deserialize(BinaryReader &stream) -> std::expected<base::ItemStackRequestActionCraftRecipeOptional, std::error_code>
{
    base::ItemStackRequestActionCraftRecipeOptional out;
    {
        auto v = Serializer<RecipeNetId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.recipe_net_id = *v;
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.filtered_string_index = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<base::ItemStackRequestActionCraftGrindstone>::serialize(BinaryWriter &stream, const base::ItemStackRequestActionCraftGrindstone &value)
{
    stream.writeVarInt<std::uint32_t>(value.recipe_net_id);
    stream.write<std::uint8_t>(value.num_crafts);
    stream.writeVarInt<std::int32_t>(value.repair_cost);
}

auto Serializer<base::ItemStackRequestActionCraftGrindstone>::deserialize(BinaryReader &stream) -> std::expected<base::ItemStackRequestActionCraftGrindstone, std::error_code>
{
    base::ItemStackRequestActionCraftGrindstone out;
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.recipe_net_id = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.num_crafts = static_cast<std::uint8_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.repair_cost = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<base::ItemStackRequestActionCraftLoom>::serialize(BinaryWriter &stream, const base::ItemStackRequestActionCraftLoom &value)
{
    stream.write(value.pattern_name_id);
    stream.write<std::uint8_t>(value.num_crafts);
}

auto Serializer<base::ItemStackRequestActionCraftLoom>::deserialize(BinaryReader &stream) -> std::expected<base::ItemStackRequestActionCraftLoom, std::error_code>
{
    base::ItemStackRequestActionCraftLoom out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.pattern_name_id = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.num_crafts = static_cast<std::uint8_t>(*v);
    }
    return out;
}

void Serializer<base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING>::serialize(BinaryWriter &stream, const base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING &value)
{
}

auto Serializer<base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING>::deserialize(BinaryReader &stream) -> std::expected<base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, std::error_code>
{
    base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING out;
    return out;
}

void Serializer<base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>::serialize(BinaryWriter &stream, const base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING &value)
{
    stream.writeVarInt<std::uint32_t>(value.craft_results.size());
    for (const auto &e0 : value.craft_results) {
        Serializer<base::SerializedNetworkItemInstanceDescriptor>::serialize(stream, e0);
    }
    stream.write<std::uint8_t>(value.num_crafts);
}

auto Serializer<base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>::deserialize(BinaryReader &stream) -> std::expected<base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING, std::error_code>
{
    base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.craft_results.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.craft_results.emplace_back();
            auto v = Serializer<base::SerializedNetworkItemInstanceDescriptor>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.craft_results.back() = *v;
        }
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.num_crafts = static_cast<std::uint8_t>(*v);
    }
    return out;
}

void Serializer<base::ItemStackRequestData>::serialize(BinaryWriter &stream, const base::ItemStackRequestData &value)
{
    Serializer<ItemStackRequestId>::serialize(stream, value.client_request_id);
    stream.writeVarInt<std::uint32_t>(value.actions.size());
    for (const auto &e0 : value.actions) {
        stream.writeVarInt<std::uint32_t>((e0).index());
        switch ((e0).index()) {
            case 0: {
                Serializer<base::ItemStackRequestActionTake>::serialize(stream, std::get<0>(e0));
                break;
            }
            case 1: {
                Serializer<base::ItemStackRequestActionPlace>::serialize(stream, std::get<1>(e0));
                break;
            }
            case 2: {
                Serializer<base::ItemStackRequestActionSwap>::serialize(stream, std::get<2>(e0));
                break;
            }
            case 3: {
                Serializer<base::ItemStackRequestActionDrop>::serialize(stream, std::get<3>(e0));
                break;
            }
            case 4: {
                Serializer<base::ItemStackRequestActionDestroy>::serialize(stream, std::get<4>(e0));
                break;
            }
            case 5: {
                Serializer<base::ItemStackRequestActionConsume>::serialize(stream, std::get<5>(e0));
                break;
            }
            case 6: {
                Serializer<base::ItemStackRequestActionCreate>::serialize(stream, std::get<6>(e0));
                break;
            }
            case 7: {
                break;
            }
            case 8: {
                break;
            }
            case 9: {
                Serializer<base::ItemStackRequestActionLabTableCombine>::serialize(stream, std::get<9>(e0));
                break;
            }
            case 10: {
                Serializer<base::ItemStackRequestActionBeaconPayment>::serialize(stream, std::get<10>(e0));
                break;
            }
            case 11: {
                Serializer<base::ItemStackRequestActionMineBlock>::serialize(stream, std::get<11>(e0));
                break;
            }
            case 12: {
                Serializer<base::ItemStackRequestActionCraftRecipe>::serialize(stream, std::get<12>(e0));
                break;
            }
            case 13: {
                Serializer<base::ItemStackRequestActionCraftRecipeAuto>::serialize(stream, std::get<13>(e0));
                break;
            }
            case 14: {
                Serializer<base::ItemStackRequestActionCraftCreative>::serialize(stream, std::get<14>(e0));
                break;
            }
            case 15: {
                Serializer<base::ItemStackRequestActionCraftRecipeOptional>::serialize(stream, std::get<15>(e0));
                break;
            }
            case 16: {
                Serializer<base::ItemStackRequestActionCraftGrindstone>::serialize(stream, std::get<16>(e0));
                break;
            }
            case 17: {
                Serializer<base::ItemStackRequestActionCraftLoom>::serialize(stream, std::get<17>(e0));
                break;
            }
            case 18: {
                Serializer<base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING>::serialize(stream, std::get<18>(e0));
                break;
            }
            case 19: {
                Serializer<base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>::serialize(stream, std::get<19>(e0));
                break;
            }
        }
    }
    stream.writeVarInt<std::uint32_t>(value.strings_to_filter.size());
    for (const auto &e0 : value.strings_to_filter) {
        stream.write(e0);
    }
    stream.write<std::int32_t>(value.strings_to_filter_origin);
}

auto Serializer<base::ItemStackRequestData>::deserialize(BinaryReader &stream) -> std::expected<base::ItemStackRequestData, std::error_code>
{
    base::ItemStackRequestData out;
    {
        auto v = Serializer<ItemStackRequestId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.client_request_id = *v;
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.actions.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.actions.emplace_back();
            auto tag1 = stream.readVarInt<std::uint32_t>();
            if (!tag1) return std::unexpected(tag1.error());
            std::variant<base::ItemStackRequestActionTake, base::ItemStackRequestActionPlace, base::ItemStackRequestActionSwap, base::ItemStackRequestActionDrop, base::ItemStackRequestActionDestroy, base::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING> var1{};
            switch (*tag1) {
                case 0: {
                    std::variant_alternative_t<0, std::variant<base::ItemStackRequestActionTake, base::ItemStackRequestActionPlace, base::ItemStackRequestActionSwap, base::ItemStackRequestActionDrop, base::ItemStackRequestActionDestroy, base::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<base::ItemStackRequestActionTake>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<0>(alt1);
                    break;
                }
                case 1: {
                    std::variant_alternative_t<1, std::variant<base::ItemStackRequestActionTake, base::ItemStackRequestActionPlace, base::ItemStackRequestActionSwap, base::ItemStackRequestActionDrop, base::ItemStackRequestActionDestroy, base::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<base::ItemStackRequestActionPlace>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<1>(alt1);
                    break;
                }
                case 2: {
                    std::variant_alternative_t<2, std::variant<base::ItemStackRequestActionTake, base::ItemStackRequestActionPlace, base::ItemStackRequestActionSwap, base::ItemStackRequestActionDrop, base::ItemStackRequestActionDestroy, base::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<base::ItemStackRequestActionSwap>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<2>(alt1);
                    break;
                }
                case 3: {
                    std::variant_alternative_t<3, std::variant<base::ItemStackRequestActionTake, base::ItemStackRequestActionPlace, base::ItemStackRequestActionSwap, base::ItemStackRequestActionDrop, base::ItemStackRequestActionDestroy, base::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<base::ItemStackRequestActionDrop>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<3>(alt1);
                    break;
                }
                case 4: {
                    std::variant_alternative_t<4, std::variant<base::ItemStackRequestActionTake, base::ItemStackRequestActionPlace, base::ItemStackRequestActionSwap, base::ItemStackRequestActionDrop, base::ItemStackRequestActionDestroy, base::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<base::ItemStackRequestActionDestroy>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<4>(alt1);
                    break;
                }
                case 5: {
                    std::variant_alternative_t<5, std::variant<base::ItemStackRequestActionTake, base::ItemStackRequestActionPlace, base::ItemStackRequestActionSwap, base::ItemStackRequestActionDrop, base::ItemStackRequestActionDestroy, base::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<base::ItemStackRequestActionConsume>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<5>(alt1);
                    break;
                }
                case 6: {
                    std::variant_alternative_t<6, std::variant<base::ItemStackRequestActionTake, base::ItemStackRequestActionPlace, base::ItemStackRequestActionSwap, base::ItemStackRequestActionDrop, base::ItemStackRequestActionDestroy, base::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<base::ItemStackRequestActionCreate>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<6>(alt1);
                    break;
                }
                case 7: {
                    std::variant_alternative_t<7, std::variant<base::ItemStackRequestActionTake, base::ItemStackRequestActionPlace, base::ItemStackRequestActionSwap, base::ItemStackRequestActionDrop, base::ItemStackRequestActionDestroy, base::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    var1.emplace<7>(alt1);
                    break;
                }
                case 8: {
                    std::variant_alternative_t<8, std::variant<base::ItemStackRequestActionTake, base::ItemStackRequestActionPlace, base::ItemStackRequestActionSwap, base::ItemStackRequestActionDrop, base::ItemStackRequestActionDestroy, base::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    var1.emplace<8>(alt1);
                    break;
                }
                case 9: {
                    std::variant_alternative_t<9, std::variant<base::ItemStackRequestActionTake, base::ItemStackRequestActionPlace, base::ItemStackRequestActionSwap, base::ItemStackRequestActionDrop, base::ItemStackRequestActionDestroy, base::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<base::ItemStackRequestActionLabTableCombine>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<9>(alt1);
                    break;
                }
                case 10: {
                    std::variant_alternative_t<10, std::variant<base::ItemStackRequestActionTake, base::ItemStackRequestActionPlace, base::ItemStackRequestActionSwap, base::ItemStackRequestActionDrop, base::ItemStackRequestActionDestroy, base::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<base::ItemStackRequestActionBeaconPayment>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<10>(alt1);
                    break;
                }
                case 11: {
                    std::variant_alternative_t<11, std::variant<base::ItemStackRequestActionTake, base::ItemStackRequestActionPlace, base::ItemStackRequestActionSwap, base::ItemStackRequestActionDrop, base::ItemStackRequestActionDestroy, base::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<base::ItemStackRequestActionMineBlock>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<11>(alt1);
                    break;
                }
                case 12: {
                    std::variant_alternative_t<12, std::variant<base::ItemStackRequestActionTake, base::ItemStackRequestActionPlace, base::ItemStackRequestActionSwap, base::ItemStackRequestActionDrop, base::ItemStackRequestActionDestroy, base::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<base::ItemStackRequestActionCraftRecipe>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<12>(alt1);
                    break;
                }
                case 13: {
                    std::variant_alternative_t<13, std::variant<base::ItemStackRequestActionTake, base::ItemStackRequestActionPlace, base::ItemStackRequestActionSwap, base::ItemStackRequestActionDrop, base::ItemStackRequestActionDestroy, base::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<base::ItemStackRequestActionCraftRecipeAuto>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<13>(alt1);
                    break;
                }
                case 14: {
                    std::variant_alternative_t<14, std::variant<base::ItemStackRequestActionTake, base::ItemStackRequestActionPlace, base::ItemStackRequestActionSwap, base::ItemStackRequestActionDrop, base::ItemStackRequestActionDestroy, base::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<base::ItemStackRequestActionCraftCreative>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<14>(alt1);
                    break;
                }
                case 15: {
                    std::variant_alternative_t<15, std::variant<base::ItemStackRequestActionTake, base::ItemStackRequestActionPlace, base::ItemStackRequestActionSwap, base::ItemStackRequestActionDrop, base::ItemStackRequestActionDestroy, base::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<base::ItemStackRequestActionCraftRecipeOptional>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<15>(alt1);
                    break;
                }
                case 16: {
                    std::variant_alternative_t<16, std::variant<base::ItemStackRequestActionTake, base::ItemStackRequestActionPlace, base::ItemStackRequestActionSwap, base::ItemStackRequestActionDrop, base::ItemStackRequestActionDestroy, base::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<base::ItemStackRequestActionCraftGrindstone>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<16>(alt1);
                    break;
                }
                case 17: {
                    std::variant_alternative_t<17, std::variant<base::ItemStackRequestActionTake, base::ItemStackRequestActionPlace, base::ItemStackRequestActionSwap, base::ItemStackRequestActionDrop, base::ItemStackRequestActionDestroy, base::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<base::ItemStackRequestActionCraftLoom>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<17>(alt1);
                    break;
                }
                case 18: {
                    std::variant_alternative_t<18, std::variant<base::ItemStackRequestActionTake, base::ItemStackRequestActionPlace, base::ItemStackRequestActionSwap, base::ItemStackRequestActionDrop, base::ItemStackRequestActionDestroy, base::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<18>(alt1);
                    break;
                }
                case 19: {
                    std::variant_alternative_t<19, std::variant<base::ItemStackRequestActionTake, base::ItemStackRequestActionPlace, base::ItemStackRequestActionSwap, base::ItemStackRequestActionDrop, base::ItemStackRequestActionDestroy, base::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<19>(alt1);
                    break;
                }
                default: {
                    return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
                }
            }
            out.actions.back() = var1;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.strings_to_filter.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.strings_to_filter.emplace_back();
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.strings_to_filter.back() = *v;
        }
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.strings_to_filter_origin = static_cast<base::TextProcessingEventOrigin>(*v);
    }
    return out;
}

void Serializer<v924::ItemStackRequestData>::serialize(BinaryWriter &stream, const v924::ItemStackRequestData &value)
{
    Serializer<ItemStackRequestId>::serialize(stream, value.client_request_id);
    stream.writeVarInt<std::uint32_t>(value.actions.size());
    for (const auto &e0 : value.actions) {
        stream.writeVarInt<std::uint32_t>((e0).index());
        switch ((e0).index()) {
            case 0: {
                Serializer<v924::ItemStackRequestActionTake>::serialize(stream, std::get<0>(e0));
                break;
            }
            case 1: {
                Serializer<v924::ItemStackRequestActionPlace>::serialize(stream, std::get<1>(e0));
                break;
            }
            case 2: {
                Serializer<v924::ItemStackRequestActionSwap>::serialize(stream, std::get<2>(e0));
                break;
            }
            case 3: {
                Serializer<v924::ItemStackRequestActionDrop>::serialize(stream, std::get<3>(e0));
                break;
            }
            case 4: {
                Serializer<v924::ItemStackRequestActionDestroy>::serialize(stream, std::get<4>(e0));
                break;
            }
            case 5: {
                Serializer<v924::ItemStackRequestActionConsume>::serialize(stream, std::get<5>(e0));
                break;
            }
            case 6: {
                Serializer<base::ItemStackRequestActionCreate>::serialize(stream, std::get<6>(e0));
                break;
            }
            case 7: {
                break;
            }
            case 8: {
                break;
            }
            case 9: {
                Serializer<base::ItemStackRequestActionLabTableCombine>::serialize(stream, std::get<9>(e0));
                break;
            }
            case 10: {
                Serializer<base::ItemStackRequestActionBeaconPayment>::serialize(stream, std::get<10>(e0));
                break;
            }
            case 11: {
                Serializer<base::ItemStackRequestActionMineBlock>::serialize(stream, std::get<11>(e0));
                break;
            }
            case 12: {
                Serializer<base::ItemStackRequestActionCraftRecipe>::serialize(stream, std::get<12>(e0));
                break;
            }
            case 13: {
                Serializer<base::ItemStackRequestActionCraftRecipeAuto>::serialize(stream, std::get<13>(e0));
                break;
            }
            case 14: {
                Serializer<base::ItemStackRequestActionCraftCreative>::serialize(stream, std::get<14>(e0));
                break;
            }
            case 15: {
                Serializer<base::ItemStackRequestActionCraftRecipeOptional>::serialize(stream, std::get<15>(e0));
                break;
            }
            case 16: {
                Serializer<base::ItemStackRequestActionCraftGrindstone>::serialize(stream, std::get<16>(e0));
                break;
            }
            case 17: {
                Serializer<base::ItemStackRequestActionCraftLoom>::serialize(stream, std::get<17>(e0));
                break;
            }
            case 18: {
                Serializer<base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING>::serialize(stream, std::get<18>(e0));
                break;
            }
            case 19: {
                Serializer<base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>::serialize(stream, std::get<19>(e0));
                break;
            }
        }
    }
    stream.writeVarInt<std::uint32_t>(value.strings_to_filter.size());
    for (const auto &e0 : value.strings_to_filter) {
        stream.write(e0);
    }
    stream.write<std::int32_t>(value.strings_to_filter_origin);
}

auto Serializer<v924::ItemStackRequestData>::deserialize(BinaryReader &stream) -> std::expected<v924::ItemStackRequestData, std::error_code>
{
    v924::ItemStackRequestData out;
    {
        auto v = Serializer<ItemStackRequestId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.client_request_id = *v;
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.actions.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.actions.emplace_back();
            auto tag1 = stream.readVarInt<std::uint32_t>();
            if (!tag1) return std::unexpected(tag1.error());
            std::variant<v924::ItemStackRequestActionTake, v924::ItemStackRequestActionPlace, v924::ItemStackRequestActionSwap, v924::ItemStackRequestActionDrop, v924::ItemStackRequestActionDestroy, v924::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING> var1{};
            switch (*tag1) {
                case 0: {
                    std::variant_alternative_t<0, std::variant<v924::ItemStackRequestActionTake, v924::ItemStackRequestActionPlace, v924::ItemStackRequestActionSwap, v924::ItemStackRequestActionDrop, v924::ItemStackRequestActionDestroy, v924::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<v924::ItemStackRequestActionTake>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<0>(alt1);
                    break;
                }
                case 1: {
                    std::variant_alternative_t<1, std::variant<v924::ItemStackRequestActionTake, v924::ItemStackRequestActionPlace, v924::ItemStackRequestActionSwap, v924::ItemStackRequestActionDrop, v924::ItemStackRequestActionDestroy, v924::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<v924::ItemStackRequestActionPlace>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<1>(alt1);
                    break;
                }
                case 2: {
                    std::variant_alternative_t<2, std::variant<v924::ItemStackRequestActionTake, v924::ItemStackRequestActionPlace, v924::ItemStackRequestActionSwap, v924::ItemStackRequestActionDrop, v924::ItemStackRequestActionDestroy, v924::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<v924::ItemStackRequestActionSwap>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<2>(alt1);
                    break;
                }
                case 3: {
                    std::variant_alternative_t<3, std::variant<v924::ItemStackRequestActionTake, v924::ItemStackRequestActionPlace, v924::ItemStackRequestActionSwap, v924::ItemStackRequestActionDrop, v924::ItemStackRequestActionDestroy, v924::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<v924::ItemStackRequestActionDrop>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<3>(alt1);
                    break;
                }
                case 4: {
                    std::variant_alternative_t<4, std::variant<v924::ItemStackRequestActionTake, v924::ItemStackRequestActionPlace, v924::ItemStackRequestActionSwap, v924::ItemStackRequestActionDrop, v924::ItemStackRequestActionDestroy, v924::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<v924::ItemStackRequestActionDestroy>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<4>(alt1);
                    break;
                }
                case 5: {
                    std::variant_alternative_t<5, std::variant<v924::ItemStackRequestActionTake, v924::ItemStackRequestActionPlace, v924::ItemStackRequestActionSwap, v924::ItemStackRequestActionDrop, v924::ItemStackRequestActionDestroy, v924::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<v924::ItemStackRequestActionConsume>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<5>(alt1);
                    break;
                }
                case 6: {
                    std::variant_alternative_t<6, std::variant<v924::ItemStackRequestActionTake, v924::ItemStackRequestActionPlace, v924::ItemStackRequestActionSwap, v924::ItemStackRequestActionDrop, v924::ItemStackRequestActionDestroy, v924::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<base::ItemStackRequestActionCreate>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<6>(alt1);
                    break;
                }
                case 7: {
                    std::variant_alternative_t<7, std::variant<v924::ItemStackRequestActionTake, v924::ItemStackRequestActionPlace, v924::ItemStackRequestActionSwap, v924::ItemStackRequestActionDrop, v924::ItemStackRequestActionDestroy, v924::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    var1.emplace<7>(alt1);
                    break;
                }
                case 8: {
                    std::variant_alternative_t<8, std::variant<v924::ItemStackRequestActionTake, v924::ItemStackRequestActionPlace, v924::ItemStackRequestActionSwap, v924::ItemStackRequestActionDrop, v924::ItemStackRequestActionDestroy, v924::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    var1.emplace<8>(alt1);
                    break;
                }
                case 9: {
                    std::variant_alternative_t<9, std::variant<v924::ItemStackRequestActionTake, v924::ItemStackRequestActionPlace, v924::ItemStackRequestActionSwap, v924::ItemStackRequestActionDrop, v924::ItemStackRequestActionDestroy, v924::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<base::ItemStackRequestActionLabTableCombine>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<9>(alt1);
                    break;
                }
                case 10: {
                    std::variant_alternative_t<10, std::variant<v924::ItemStackRequestActionTake, v924::ItemStackRequestActionPlace, v924::ItemStackRequestActionSwap, v924::ItemStackRequestActionDrop, v924::ItemStackRequestActionDestroy, v924::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<base::ItemStackRequestActionBeaconPayment>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<10>(alt1);
                    break;
                }
                case 11: {
                    std::variant_alternative_t<11, std::variant<v924::ItemStackRequestActionTake, v924::ItemStackRequestActionPlace, v924::ItemStackRequestActionSwap, v924::ItemStackRequestActionDrop, v924::ItemStackRequestActionDestroy, v924::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<base::ItemStackRequestActionMineBlock>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<11>(alt1);
                    break;
                }
                case 12: {
                    std::variant_alternative_t<12, std::variant<v924::ItemStackRequestActionTake, v924::ItemStackRequestActionPlace, v924::ItemStackRequestActionSwap, v924::ItemStackRequestActionDrop, v924::ItemStackRequestActionDestroy, v924::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<base::ItemStackRequestActionCraftRecipe>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<12>(alt1);
                    break;
                }
                case 13: {
                    std::variant_alternative_t<13, std::variant<v924::ItemStackRequestActionTake, v924::ItemStackRequestActionPlace, v924::ItemStackRequestActionSwap, v924::ItemStackRequestActionDrop, v924::ItemStackRequestActionDestroy, v924::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<base::ItemStackRequestActionCraftRecipeAuto>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<13>(alt1);
                    break;
                }
                case 14: {
                    std::variant_alternative_t<14, std::variant<v924::ItemStackRequestActionTake, v924::ItemStackRequestActionPlace, v924::ItemStackRequestActionSwap, v924::ItemStackRequestActionDrop, v924::ItemStackRequestActionDestroy, v924::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<base::ItemStackRequestActionCraftCreative>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<14>(alt1);
                    break;
                }
                case 15: {
                    std::variant_alternative_t<15, std::variant<v924::ItemStackRequestActionTake, v924::ItemStackRequestActionPlace, v924::ItemStackRequestActionSwap, v924::ItemStackRequestActionDrop, v924::ItemStackRequestActionDestroy, v924::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<base::ItemStackRequestActionCraftRecipeOptional>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<15>(alt1);
                    break;
                }
                case 16: {
                    std::variant_alternative_t<16, std::variant<v924::ItemStackRequestActionTake, v924::ItemStackRequestActionPlace, v924::ItemStackRequestActionSwap, v924::ItemStackRequestActionDrop, v924::ItemStackRequestActionDestroy, v924::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<base::ItemStackRequestActionCraftGrindstone>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<16>(alt1);
                    break;
                }
                case 17: {
                    std::variant_alternative_t<17, std::variant<v924::ItemStackRequestActionTake, v924::ItemStackRequestActionPlace, v924::ItemStackRequestActionSwap, v924::ItemStackRequestActionDrop, v924::ItemStackRequestActionDestroy, v924::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<base::ItemStackRequestActionCraftLoom>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<17>(alt1);
                    break;
                }
                case 18: {
                    std::variant_alternative_t<18, std::variant<v924::ItemStackRequestActionTake, v924::ItemStackRequestActionPlace, v924::ItemStackRequestActionSwap, v924::ItemStackRequestActionDrop, v924::ItemStackRequestActionDestroy, v924::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<18>(alt1);
                    break;
                }
                case 19: {
                    std::variant_alternative_t<19, std::variant<v924::ItemStackRequestActionTake, v924::ItemStackRequestActionPlace, v924::ItemStackRequestActionSwap, v924::ItemStackRequestActionDrop, v924::ItemStackRequestActionDestroy, v924::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<19>(alt1);
                    break;
                }
                default: {
                    return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
                }
            }
            out.actions.back() = var1;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.strings_to_filter.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.strings_to_filter.emplace_back();
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.strings_to_filter.back() = *v;
        }
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.strings_to_filter_origin = static_cast<base::TextProcessingEventOrigin>(*v);
    }
    return out;
}

void Serializer<v975::ItemStackRequestData>::serialize(BinaryWriter &stream, const v975::ItemStackRequestData &value)
{
    Serializer<ItemStackRequestId>::serialize(stream, value.client_request_id);
    stream.writeVarInt<std::uint32_t>(value.actions.size());
    for (const auto &e0 : value.actions) {
        stream.writeVarInt<std::uint32_t>((e0).index());
        switch ((e0).index()) {
            case 0: {
                Serializer<v924::ItemStackRequestActionTake>::serialize(stream, std::get<0>(e0));
                break;
            }
            case 1: {
                Serializer<v924::ItemStackRequestActionPlace>::serialize(stream, std::get<1>(e0));
                break;
            }
            case 2: {
                Serializer<v924::ItemStackRequestActionSwap>::serialize(stream, std::get<2>(e0));
                break;
            }
            case 3: {
                Serializer<v924::ItemStackRequestActionDrop>::serialize(stream, std::get<3>(e0));
                break;
            }
            case 4: {
                Serializer<v924::ItemStackRequestActionDestroy>::serialize(stream, std::get<4>(e0));
                break;
            }
            case 5: {
                Serializer<v924::ItemStackRequestActionConsume>::serialize(stream, std::get<5>(e0));
                break;
            }
            case 6: {
                Serializer<base::ItemStackRequestActionCreate>::serialize(stream, std::get<6>(e0));
                break;
            }
            case 7: {
                break;
            }
            case 8: {
                break;
            }
            case 9: {
                Serializer<base::ItemStackRequestActionLabTableCombine>::serialize(stream, std::get<9>(e0));
                break;
            }
            case 10: {
                Serializer<base::ItemStackRequestActionBeaconPayment>::serialize(stream, std::get<10>(e0));
                break;
            }
            case 11: {
                Serializer<base::ItemStackRequestActionMineBlock>::serialize(stream, std::get<11>(e0));
                break;
            }
            case 12: {
                Serializer<base::ItemStackRequestActionCraftRecipe>::serialize(stream, std::get<12>(e0));
                break;
            }
            case 13: {
                Serializer<base::ItemStackRequestActionCraftRecipeAuto>::serialize(stream, std::get<13>(e0));
                break;
            }
            case 14: {
                Serializer<base::ItemStackRequestActionCraftCreative>::serialize(stream, std::get<14>(e0));
                break;
            }
            case 15: {
                Serializer<base::ItemStackRequestActionCraftRecipeOptional>::serialize(stream, std::get<15>(e0));
                break;
            }
            case 16: {
                Serializer<base::ItemStackRequestActionCraftGrindstone>::serialize(stream, std::get<16>(e0));
                break;
            }
            case 17: {
                Serializer<base::ItemStackRequestActionCraftLoom>::serialize(stream, std::get<17>(e0));
                break;
            }
            case 18: {
                Serializer<base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING>::serialize(stream, std::get<18>(e0));
                break;
            }
            case 19: {
                Serializer<base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>::serialize(stream, std::get<19>(e0));
                break;
            }
        }
    }
    stream.writeVarInt<std::uint32_t>(value.strings_to_filter.size());
    for (const auto &e0 : value.strings_to_filter) {
        stream.write(e0);
    }
    stream.write<std::int32_t>(value.strings_to_filter_origin);
}

auto Serializer<v975::ItemStackRequestData>::deserialize(BinaryReader &stream) -> std::expected<v975::ItemStackRequestData, std::error_code>
{
    v975::ItemStackRequestData out;
    {
        auto v = Serializer<ItemStackRequestId>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.client_request_id = *v;
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.actions.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.actions.emplace_back();
            auto tag1 = stream.readVarInt<std::uint32_t>();
            if (!tag1) return std::unexpected(tag1.error());
            std::variant<v924::ItemStackRequestActionTake, v924::ItemStackRequestActionPlace, v924::ItemStackRequestActionSwap, v924::ItemStackRequestActionDrop, v924::ItemStackRequestActionDestroy, v924::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING> var1{};
            switch (*tag1) {
                case 0: {
                    std::variant_alternative_t<0, std::variant<v924::ItemStackRequestActionTake, v924::ItemStackRequestActionPlace, v924::ItemStackRequestActionSwap, v924::ItemStackRequestActionDrop, v924::ItemStackRequestActionDestroy, v924::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<v924::ItemStackRequestActionTake>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<0>(alt1);
                    break;
                }
                case 1: {
                    std::variant_alternative_t<1, std::variant<v924::ItemStackRequestActionTake, v924::ItemStackRequestActionPlace, v924::ItemStackRequestActionSwap, v924::ItemStackRequestActionDrop, v924::ItemStackRequestActionDestroy, v924::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<v924::ItemStackRequestActionPlace>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<1>(alt1);
                    break;
                }
                case 2: {
                    std::variant_alternative_t<2, std::variant<v924::ItemStackRequestActionTake, v924::ItemStackRequestActionPlace, v924::ItemStackRequestActionSwap, v924::ItemStackRequestActionDrop, v924::ItemStackRequestActionDestroy, v924::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<v924::ItemStackRequestActionSwap>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<2>(alt1);
                    break;
                }
                case 3: {
                    std::variant_alternative_t<3, std::variant<v924::ItemStackRequestActionTake, v924::ItemStackRequestActionPlace, v924::ItemStackRequestActionSwap, v924::ItemStackRequestActionDrop, v924::ItemStackRequestActionDestroy, v924::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<v924::ItemStackRequestActionDrop>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<3>(alt1);
                    break;
                }
                case 4: {
                    std::variant_alternative_t<4, std::variant<v924::ItemStackRequestActionTake, v924::ItemStackRequestActionPlace, v924::ItemStackRequestActionSwap, v924::ItemStackRequestActionDrop, v924::ItemStackRequestActionDestroy, v924::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<v924::ItemStackRequestActionDestroy>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<4>(alt1);
                    break;
                }
                case 5: {
                    std::variant_alternative_t<5, std::variant<v924::ItemStackRequestActionTake, v924::ItemStackRequestActionPlace, v924::ItemStackRequestActionSwap, v924::ItemStackRequestActionDrop, v924::ItemStackRequestActionDestroy, v924::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<v924::ItemStackRequestActionConsume>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<5>(alt1);
                    break;
                }
                case 6: {
                    std::variant_alternative_t<6, std::variant<v924::ItemStackRequestActionTake, v924::ItemStackRequestActionPlace, v924::ItemStackRequestActionSwap, v924::ItemStackRequestActionDrop, v924::ItemStackRequestActionDestroy, v924::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<base::ItemStackRequestActionCreate>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<6>(alt1);
                    break;
                }
                case 7: {
                    std::variant_alternative_t<7, std::variant<v924::ItemStackRequestActionTake, v924::ItemStackRequestActionPlace, v924::ItemStackRequestActionSwap, v924::ItemStackRequestActionDrop, v924::ItemStackRequestActionDestroy, v924::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    var1.emplace<7>(alt1);
                    break;
                }
                case 8: {
                    std::variant_alternative_t<8, std::variant<v924::ItemStackRequestActionTake, v924::ItemStackRequestActionPlace, v924::ItemStackRequestActionSwap, v924::ItemStackRequestActionDrop, v924::ItemStackRequestActionDestroy, v924::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    var1.emplace<8>(alt1);
                    break;
                }
                case 9: {
                    std::variant_alternative_t<9, std::variant<v924::ItemStackRequestActionTake, v924::ItemStackRequestActionPlace, v924::ItemStackRequestActionSwap, v924::ItemStackRequestActionDrop, v924::ItemStackRequestActionDestroy, v924::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<base::ItemStackRequestActionLabTableCombine>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<9>(alt1);
                    break;
                }
                case 10: {
                    std::variant_alternative_t<10, std::variant<v924::ItemStackRequestActionTake, v924::ItemStackRequestActionPlace, v924::ItemStackRequestActionSwap, v924::ItemStackRequestActionDrop, v924::ItemStackRequestActionDestroy, v924::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<base::ItemStackRequestActionBeaconPayment>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<10>(alt1);
                    break;
                }
                case 11: {
                    std::variant_alternative_t<11, std::variant<v924::ItemStackRequestActionTake, v924::ItemStackRequestActionPlace, v924::ItemStackRequestActionSwap, v924::ItemStackRequestActionDrop, v924::ItemStackRequestActionDestroy, v924::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<base::ItemStackRequestActionMineBlock>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<11>(alt1);
                    break;
                }
                case 12: {
                    std::variant_alternative_t<12, std::variant<v924::ItemStackRequestActionTake, v924::ItemStackRequestActionPlace, v924::ItemStackRequestActionSwap, v924::ItemStackRequestActionDrop, v924::ItemStackRequestActionDestroy, v924::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<base::ItemStackRequestActionCraftRecipe>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<12>(alt1);
                    break;
                }
                case 13: {
                    std::variant_alternative_t<13, std::variant<v924::ItemStackRequestActionTake, v924::ItemStackRequestActionPlace, v924::ItemStackRequestActionSwap, v924::ItemStackRequestActionDrop, v924::ItemStackRequestActionDestroy, v924::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<base::ItemStackRequestActionCraftRecipeAuto>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<13>(alt1);
                    break;
                }
                case 14: {
                    std::variant_alternative_t<14, std::variant<v924::ItemStackRequestActionTake, v924::ItemStackRequestActionPlace, v924::ItemStackRequestActionSwap, v924::ItemStackRequestActionDrop, v924::ItemStackRequestActionDestroy, v924::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<base::ItemStackRequestActionCraftCreative>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<14>(alt1);
                    break;
                }
                case 15: {
                    std::variant_alternative_t<15, std::variant<v924::ItemStackRequestActionTake, v924::ItemStackRequestActionPlace, v924::ItemStackRequestActionSwap, v924::ItemStackRequestActionDrop, v924::ItemStackRequestActionDestroy, v924::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<base::ItemStackRequestActionCraftRecipeOptional>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<15>(alt1);
                    break;
                }
                case 16: {
                    std::variant_alternative_t<16, std::variant<v924::ItemStackRequestActionTake, v924::ItemStackRequestActionPlace, v924::ItemStackRequestActionSwap, v924::ItemStackRequestActionDrop, v924::ItemStackRequestActionDestroy, v924::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<base::ItemStackRequestActionCraftGrindstone>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<16>(alt1);
                    break;
                }
                case 17: {
                    std::variant_alternative_t<17, std::variant<v924::ItemStackRequestActionTake, v924::ItemStackRequestActionPlace, v924::ItemStackRequestActionSwap, v924::ItemStackRequestActionDrop, v924::ItemStackRequestActionDestroy, v924::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<base::ItemStackRequestActionCraftLoom>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<17>(alt1);
                    break;
                }
                case 18: {
                    std::variant_alternative_t<18, std::variant<v924::ItemStackRequestActionTake, v924::ItemStackRequestActionPlace, v924::ItemStackRequestActionSwap, v924::ItemStackRequestActionDrop, v924::ItemStackRequestActionDestroy, v924::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<18>(alt1);
                    break;
                }
                case 19: {
                    std::variant_alternative_t<19, std::variant<v924::ItemStackRequestActionTake, v924::ItemStackRequestActionPlace, v924::ItemStackRequestActionSwap, v924::ItemStackRequestActionDrop, v924::ItemStackRequestActionDestroy, v924::ItemStackRequestActionConsume, base::ItemStackRequestActionCreate, std::monostate, std::monostate, base::ItemStackRequestActionLabTableCombine, base::ItemStackRequestActionBeaconPayment, base::ItemStackRequestActionMineBlock, base::ItemStackRequestActionCraftRecipe, base::ItemStackRequestActionCraftRecipeAuto, base::ItemStackRequestActionCraftCreative, base::ItemStackRequestActionCraftRecipeOptional, base::ItemStackRequestActionCraftGrindstone, base::ItemStackRequestActionCraftLoom, base::ItemStackRequestActionCraftNonImplemented_DEPRECATEDASKTYLAING, base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>> alt1{};
                    {
                        auto v = Serializer<base::ItemStackRequestActionCraftResults_DEPRECATEDASKTYLAING>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<19>(alt1);
                    break;
                }
                default: {
                    return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
                }
            }
            out.actions.back() = var1;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.strings_to_filter.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.strings_to_filter.emplace_back();
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.strings_to_filter.back() = *v;
        }
    }
    {
        auto v = stream.read<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.strings_to_filter_origin = static_cast<v975::TextProcessingEventOrigin>(*v);
    }
    return out;
}

void Serializer<base::ItemStackRequestPacket>::serialize(BinaryWriter &stream, const base::ItemStackRequestPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.requests.size());
    for (const auto &e0 : value.requests) {
        Serializer<base::ItemStackRequestData>::serialize(stream, e0);
    }
}

auto Serializer<base::ItemStackRequestPacket>::deserialize(BinaryReader &stream) -> std::expected<base::ItemStackRequestPacket, std::error_code>
{
    base::ItemStackRequestPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.requests.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.requests.emplace_back();
            auto v = Serializer<base::ItemStackRequestData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.requests.back() = *v;
        }
    }
    return out;
}

void Serializer<v924::ItemStackRequestPacket>::serialize(BinaryWriter &stream, const v924::ItemStackRequestPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.requests.size());
    for (const auto &e0 : value.requests) {
        Serializer<v924::ItemStackRequestData>::serialize(stream, e0);
    }
}

auto Serializer<v924::ItemStackRequestPacket>::deserialize(BinaryReader &stream) -> std::expected<v924::ItemStackRequestPacket, std::error_code>
{
    v924::ItemStackRequestPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.requests.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.requests.emplace_back();
            auto v = Serializer<v924::ItemStackRequestData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.requests.back() = *v;
        }
    }
    return out;
}

void Serializer<v975::ItemStackRequestPacket>::serialize(BinaryWriter &stream, const v975::ItemStackRequestPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.requests.size());
    for (const auto &e0 : value.requests) {
        Serializer<v975::ItemStackRequestData>::serialize(stream, e0);
    }
}

auto Serializer<v975::ItemStackRequestPacket>::deserialize(BinaryReader &stream) -> std::expected<v975::ItemStackRequestPacket, std::error_code>
{
    v975::ItemStackRequestPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.requests.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.requests.emplace_back();
            auto v = Serializer<v975::ItemStackRequestData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.requests.back() = *v;
        }
    }
    return out;
}

void Serializer<v2168::ItemStackRequestPacket>::serialize(BinaryWriter &stream, const v2168::ItemStackRequestPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.requests.size());
    for (const auto &e0 : value.requests) {
        Serializer<v2168::ItemStackRequestCereal::RequestData>::serialize(stream, e0);
    }
}

auto Serializer<v2168::ItemStackRequestPacket>::deserialize(BinaryReader &stream) -> std::expected<v2168::ItemStackRequestPacket, std::error_code>
{
    v2168::ItemStackRequestPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.requests.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.requests.emplace_back();
            auto v = Serializer<v2168::ItemStackRequestCereal::RequestData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.requests.back() = *v;
        }
    }
    return out;
}

void Serializer<v2225::ItemStackRequestPacket>::serialize(BinaryWriter &stream, const v2225::ItemStackRequestPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.requests.size());
    for (const auto &e0 : value.requests) {
        Serializer<v2225::ItemStackRequestCereal::RequestData>::serialize(stream, e0);
    }
}

auto Serializer<v2225::ItemStackRequestPacket>::deserialize(BinaryReader &stream) -> std::expected<v2225::ItemStackRequestPacket, std::error_code>
{
    v2225::ItemStackRequestPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.requests.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.requests.emplace_back();
            auto v = Serializer<v2225::ItemStackRequestCereal::RequestData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.requests.back() = *v;
        }
    }
    return out;
}

}  // namespace bedrock::protocol
