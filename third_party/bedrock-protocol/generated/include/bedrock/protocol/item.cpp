#include <bedrock/protocol/item.h>

namespace bedrock::protocol {


void Serializer<base::ItemData>::serialize(BinaryWriter &stream, const base::ItemData &value)
{
    stream.write(value.name);
    stream.write<std::int16_t>(value.id);
    stream.write<bool>(value.is_component_based);
    stream.writeVarInt<std::int32_t>(value.item_version);
    Serializer<CompoundTag>::serialize(stream, value.component_data);
}

auto Serializer<base::ItemData>::deserialize(BinaryReader &stream) -> std::expected<base::ItemData, std::error_code>
{
    base::ItemData out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = stream.read<std::int16_t>();
        if (!v) return std::unexpected(v.error());
        out.id = static_cast<std::int16_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_component_based = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.item_version = static_cast<base::ItemVersion>(*v);
    }
    {
        auto v = Serializer<CompoundTag>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.component_data = *v;
    }
    return out;
}

void Serializer<v776::ItemData>::serialize(BinaryWriter &stream, const v776::ItemData &value)
{
    stream.write(value.name);
    stream.write<std::int16_t>(value.id);
    stream.write<bool>(value.is_component_based);
    stream.writeVarInt<std::int32_t>(value.item_version);
    Serializer<CompoundTag>::serialize(stream, value.component_data);
}

auto Serializer<v776::ItemData>::deserialize(BinaryReader &stream) -> std::expected<v776::ItemData, std::error_code>
{
    v776::ItemData out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = stream.read<std::int16_t>();
        if (!v) return std::unexpected(v.error());
        out.id = static_cast<std::int16_t>(*v);
    }
    {
        auto v = stream.read<bool>();
        if (!v) return std::unexpected(v.error());
        out.is_component_based = static_cast<bool>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.item_version = static_cast<v776::ItemVersion>(*v);
    }
    {
        auto v = Serializer<CompoundTag>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.component_data = *v;
    }
    return out;
}

void Serializer<ItemComponentEntry>::serialize(BinaryWriter &stream, const ItemComponentEntry &value)
{
    stream.write(value.name);
    Serializer<CompoundTag>::serialize(stream, value.component_data);
}

auto Serializer<ItemComponentEntry>::deserialize(BinaryReader &stream) -> std::expected<ItemComponentEntry, std::error_code>
{
    ItemComponentEntry out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.name = *v;
    }
    {
        auto v = Serializer<CompoundTag>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.component_data = *v;
    }
    return out;
}

void Serializer<v776::ItemRegistryPacket>::serialize(BinaryWriter &stream, const v776::ItemRegistryPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.items.size());
    for (const auto &e0 : value.items) {
        Serializer<v776::ItemData>::serialize(stream, e0);
    }
}

auto Serializer<v776::ItemRegistryPacket>::deserialize(BinaryReader &stream) -> std::expected<v776::ItemRegistryPacket, std::error_code>
{
    v776::ItemRegistryPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.items.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.items.emplace_back();
            auto v = Serializer<v776::ItemData>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.items.back() = *v;
        }
    }
    return out;
}

void Serializer<PlayerStartItemCooldownPacket>::serialize(BinaryWriter &stream, const PlayerStartItemCooldownPacket &value)
{
    stream.write(value.item_category);
    stream.writeVarInt<std::int32_t>(value.duration_ticks);
}

auto Serializer<PlayerStartItemCooldownPacket>::deserialize(BinaryReader &stream) -> std::expected<PlayerStartItemCooldownPacket, std::error_code>
{
    PlayerStartItemCooldownPacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.item_category = *v;
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.duration_ticks = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<ReplacePage>::serialize(BinaryWriter &stream, const ReplacePage &value)
{
    stream.writeVarInt<std::int32_t>(value.page_index);
    stream.write(value.page_text);
    stream.write(value.photo_name);
}

auto Serializer<ReplacePage>::deserialize(BinaryReader &stream) -> std::expected<ReplacePage, std::error_code>
{
    ReplacePage out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.page_index = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.page_text = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.photo_name = *v;
    }
    return out;
}

void Serializer<AddPage>::serialize(BinaryWriter &stream, const AddPage &value)
{
    stream.writeVarInt<std::int32_t>(value.page_index);
    stream.write(value.page_text);
    stream.write(value.photo_name);
}

auto Serializer<AddPage>::deserialize(BinaryReader &stream) -> std::expected<AddPage, std::error_code>
{
    AddPage out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.page_index = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.page_text = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.photo_name = *v;
    }
    return out;
}

void Serializer<DeletePage>::serialize(BinaryWriter &stream, const DeletePage &value)
{
    stream.writeVarInt<std::int32_t>(value.page_index);
}

auto Serializer<DeletePage>::deserialize(BinaryReader &stream) -> std::expected<DeletePage, std::error_code>
{
    DeletePage out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.page_index = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<SwapPages>::serialize(BinaryWriter &stream, const SwapPages &value)
{
    stream.writeVarInt<std::int32_t>(value.page_index);
    stream.writeVarInt<std::int32_t>(value.swap_with_index);
}

auto Serializer<SwapPages>::deserialize(BinaryReader &stream) -> std::expected<SwapPages, std::error_code>
{
    SwapPages out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.page_index = static_cast<std::int32_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.swap_with_index = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<Finalize>::serialize(BinaryWriter &stream, const Finalize &value)
{
    stream.write(value.title);
    stream.write(value.author);
    stream.write(value.xuid);
}

auto Serializer<Finalize>::deserialize(BinaryReader &stream) -> std::expected<Finalize, std::error_code>
{
    Finalize out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.title = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.author = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.xuid = *v;
    }
    return out;
}

void Serializer<base::BookEditPacket>::serialize(BinaryWriter &stream, const base::BookEditPacket &value)
{
    stream.write<std::uint8_t>(value.action);
    stream.write<std::uint8_t>(value.book_slot);
    if ((value.action) != (BookEditAction::Finalize)) {
        stream.write<std::uint8_t>(value.page_index);
    }
    if ((value.action) == (BookEditAction::SwapPages)) {
        stream.write<std::uint8_t>(value.swap_with_index);
    }
    if (((value.action) == (BookEditAction::ReplacePage)) || ((value.action) == (BookEditAction::AddPage))) {
        stream.write(value.page_text);
        stream.write(value.photo_name);
    }
    if ((value.action) == (BookEditAction::Finalize)) {
        stream.write(value.title);
        stream.write(value.author);
        stream.write(value.xuid);
    }
}

auto Serializer<base::BookEditPacket>::deserialize(BinaryReader &stream) -> std::expected<base::BookEditPacket, std::error_code>
{
    base::BookEditPacket out;
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.action = static_cast<BookEditAction>(*v);
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.book_slot = static_cast<std::int32_t>(*v);
    }
    if ((out.action) != (BookEditAction::Finalize)) {
        {
            auto v = stream.read<std::uint8_t>();
            if (!v) return std::unexpected(v.error());
            out.page_index = static_cast<std::int32_t>(*v);
        }
    }
    if ((out.action) == (BookEditAction::SwapPages)) {
        {
            auto v = stream.read<std::uint8_t>();
            if (!v) return std::unexpected(v.error());
            out.swap_with_index = static_cast<std::int32_t>(*v);
        }
    }
    if (((out.action) == (BookEditAction::ReplacePage)) || ((out.action) == (BookEditAction::AddPage))) {
        {
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.page_text = *v;
        }
        {
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.photo_name = *v;
        }
    }
    if ((out.action) == (BookEditAction::Finalize)) {
        {
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.title = *v;
        }
        {
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.author = *v;
        }
        {
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.xuid = *v;
        }
    }
    return out;
}

void Serializer<v924::BookEditPacket>::serialize(BinaryWriter &stream, const v924::BookEditPacket &value)
{
    stream.writeVarInt<std::int32_t>(value.book_slot);
    stream.writeVarInt<std::uint32_t>((value.operation).index());
    switch ((value.operation).index()) {
        case 0: {
            Serializer<ReplacePage>::serialize(stream, std::get<0>(value.operation));
            break;
        }
        case 1: {
            Serializer<AddPage>::serialize(stream, std::get<1>(value.operation));
            break;
        }
        case 2: {
            Serializer<DeletePage>::serialize(stream, std::get<2>(value.operation));
            break;
        }
        case 3: {
            Serializer<SwapPages>::serialize(stream, std::get<3>(value.operation));
            break;
        }
        case 4: {
            Serializer<Finalize>::serialize(stream, std::get<4>(value.operation));
            break;
        }
    }
}

auto Serializer<v924::BookEditPacket>::deserialize(BinaryReader &stream) -> std::expected<v924::BookEditPacket, std::error_code>
{
    v924::BookEditPacket out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.book_slot = static_cast<std::int32_t>(*v);
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<ReplacePage, AddPage, DeletePage, SwapPages, Finalize> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<ReplacePage, AddPage, DeletePage, SwapPages, Finalize>> alt0{};
                {
                    auto v = Serializer<ReplacePage>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<ReplacePage, AddPage, DeletePage, SwapPages, Finalize>> alt0{};
                {
                    auto v = Serializer<AddPage>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<ReplacePage, AddPage, DeletePage, SwapPages, Finalize>> alt0{};
                {
                    auto v = Serializer<DeletePage>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
                break;
            }
            case 3: {
                std::variant_alternative_t<3, std::variant<ReplacePage, AddPage, DeletePage, SwapPages, Finalize>> alt0{};
                {
                    auto v = Serializer<SwapPages>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<3>(alt0);
                break;
            }
            case 4: {
                std::variant_alternative_t<4, std::variant<ReplacePage, AddPage, DeletePage, SwapPages, Finalize>> alt0{};
                {
                    auto v = Serializer<Finalize>::deserialize(stream);
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
        out.operation = var0;
    }
    return out;
}

void Serializer<TrimPattern>::serialize(BinaryWriter &stream, const TrimPattern &value)
{
    stream.write(value.item_name);
    stream.write(value.pattern_id);
}

auto Serializer<TrimPattern>::deserialize(BinaryReader &stream) -> std::expected<TrimPattern, std::error_code>
{
    TrimPattern out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.item_name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.pattern_id = *v;
    }
    return out;
}

void Serializer<TrimMaterial>::serialize(BinaryWriter &stream, const TrimMaterial &value)
{
    stream.write(value.material_id);
    stream.write(value.color);
    stream.write(value.item_name);
}

auto Serializer<TrimMaterial>::deserialize(BinaryReader &stream) -> std::expected<TrimMaterial, std::error_code>
{
    TrimMaterial out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.material_id = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.color = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.item_name = *v;
    }
    return out;
}

void Serializer<TrimDataPacket>::serialize(BinaryWriter &stream, const TrimDataPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.trim_patterns.size());
    for (const auto &e0 : value.trim_patterns) {
        Serializer<TrimPattern>::serialize(stream, e0);
    }
    stream.writeVarInt<std::uint32_t>(value.trim_materials.size());
    for (const auto &e0 : value.trim_materials) {
        Serializer<TrimMaterial>::serialize(stream, e0);
    }
}

auto Serializer<TrimDataPacket>::deserialize(BinaryReader &stream) -> std::expected<TrimDataPacket, std::error_code>
{
    TrimDataPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.trim_patterns.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.trim_patterns.emplace_back();
            auto v = Serializer<TrimPattern>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.trim_patterns.back() = *v;
        }
    }
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.trim_materials.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.trim_materials.emplace_back();
            auto v = Serializer<TrimMaterial>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.trim_materials.back() = *v;
        }
    }
    return out;
}

void Serializer<ItemStackNetId>::serialize(BinaryWriter &stream, const ItemStackNetId &value)
{
    stream.writeVarInt<std::int32_t>(value.raw_id);
}

auto Serializer<ItemStackNetId>::deserialize(BinaryReader &stream) -> std::expected<ItemStackNetId, std::error_code>
{
    ItemStackNetId out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.raw_id = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<ItemStackRequestId>::serialize(BinaryWriter &stream, const ItemStackRequestId &value)
{
    stream.writeVarInt<std::int32_t>(value.raw_id);
}

auto Serializer<ItemStackRequestId>::deserialize(BinaryReader &stream) -> std::expected<ItemStackRequestId, std::error_code>
{
    ItemStackRequestId out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.raw_id = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<ItemStackLegacyRequestId>::serialize(BinaryWriter &stream, const ItemStackLegacyRequestId &value)
{
    stream.writeVarInt<std::int32_t>(value.raw_id);
}

auto Serializer<ItemStackLegacyRequestId>::deserialize(BinaryReader &stream) -> std::expected<ItemStackLegacyRequestId, std::error_code>
{
    ItemStackLegacyRequestId out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.raw_id = static_cast<std::int32_t>(*v);
    }
    return out;
}

void Serializer<NetworkItemStackDescriptor>::serialize(BinaryWriter &stream, const NetworkItemStackDescriptor &value)
{
    stream.writeVarInt<std::int32_t>(value.id);
    if ((value.id) != (0)) {
        stream.write<std::uint16_t>(value.stack_size);
        stream.writeVarInt<std::uint32_t>(value.aux_value);
        stream.write<bool>(value.net_id.has_value());
        if (value.net_id.has_value()) {
            Serializer<ItemStackNetId>::serialize(stream, (*value.net_id));
        }
        stream.writeVarInt<std::int32_t>(value.block_runtime_id);
        stream.write(value.user_data_buffer);
    }
}

auto Serializer<NetworkItemStackDescriptor>::deserialize(BinaryReader &stream) -> std::expected<NetworkItemStackDescriptor, std::error_code>
{
    NetworkItemStackDescriptor out;
    {
        auto v = stream.readVarInt<std::int32_t>();
        if (!v) return std::unexpected(v.error());
        out.id = static_cast<std::int32_t>(*v);
    }
    if ((out.id) != (0)) {
        {
            auto v = stream.read<std::uint16_t>();
            if (!v) return std::unexpected(v.error());
            out.stack_size = static_cast<std::uint16_t>(*v);
        }
        {
            auto v = stream.readVarInt<std::uint32_t>();
            if (!v) return std::unexpected(v.error());
            out.aux_value = static_cast<std::uint32_t>(*v);
        }
        {
            auto present = stream.read<bool>();
            if (!present) return std::unexpected(present.error());
            if (*present) {
                ItemStackNetId staged{};
                auto v = Serializer<ItemStackNetId>::deserialize(stream);
                if (!v) return std::unexpected(v.error());
                staged = *v;
                out.net_id = std::move(staged);
            }
        }
        {
            auto v = stream.readVarInt<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            out.block_runtime_id = static_cast<BlockRuntimeId>(*v);
        }
        {
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.user_data_buffer = *v;
        }
    }
    return out;
}

void Serializer<base::SerializedNetworkItemStackDescriptor>::serialize(BinaryWriter &stream, const base::SerializedNetworkItemStackDescriptor &value)
{
    stream.write<std::int16_t>(value.id);
    stream.write<std::uint16_t>(value.stack_size);
    stream.writeVarInt<std::uint32_t>(value.aux_value);
    stream.write<bool>(value.net_id_variant.has_value());
    if (value.net_id_variant.has_value()) {
        stream.writeVarInt<std::uint32_t>(((*value.net_id_variant)).index());
        switch (((*value.net_id_variant)).index()) {
            case 0: {
                Serializer<ItemStackNetId>::serialize(stream, std::get<0>((*value.net_id_variant)));
                break;
            }
            case 1: {
                Serializer<ItemStackRequestId>::serialize(stream, std::get<1>((*value.net_id_variant)));
                break;
            }
            case 2: {
                Serializer<ItemStackLegacyRequestId>::serialize(stream, std::get<2>((*value.net_id_variant)));
                break;
            }
        }
    }
    stream.writeVarInt<std::uint32_t>(value.block_runtime_id);
    stream.write(value.user_data_buffer);
}

auto Serializer<base::SerializedNetworkItemStackDescriptor>::deserialize(BinaryReader &stream) -> std::expected<base::SerializedNetworkItemStackDescriptor, std::error_code>
{
    base::SerializedNetworkItemStackDescriptor out;
    {
        auto v = stream.read<std::int16_t>();
        if (!v) return std::unexpected(v.error());
        out.id = static_cast<std::int16_t>(*v);
    }
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.stack_size = static_cast<std::uint16_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.aux_value = static_cast<std::uint32_t>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::variant<ItemStackNetId, ItemStackRequestId, ItemStackLegacyRequestId> staged{};
            auto tag0 = stream.readVarInt<std::uint32_t>();
            if (!tag0) return std::unexpected(tag0.error());
            std::variant<ItemStackNetId, ItemStackRequestId, ItemStackLegacyRequestId> var0{};
            switch (*tag0) {
                case 0: {
                    std::variant_alternative_t<0, std::variant<ItemStackNetId, ItemStackRequestId, ItemStackLegacyRequestId>> alt0{};
                    {
                        auto v = Serializer<ItemStackNetId>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt0 = *v;
                    }
                    var0.emplace<0>(alt0);
                    break;
                }
                case 1: {
                    std::variant_alternative_t<1, std::variant<ItemStackNetId, ItemStackRequestId, ItemStackLegacyRequestId>> alt0{};
                    {
                        auto v = Serializer<ItemStackRequestId>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt0 = *v;
                    }
                    var0.emplace<1>(alt0);
                    break;
                }
                case 2: {
                    std::variant_alternative_t<2, std::variant<ItemStackNetId, ItemStackRequestId, ItemStackLegacyRequestId>> alt0{};
                    {
                        auto v = Serializer<ItemStackLegacyRequestId>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt0 = *v;
                    }
                    var0.emplace<2>(alt0);
                    break;
                }
                default: {
                    return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
                }
            }
            staged = var0;
            out.net_id_variant = std::move(staged);
        }
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

void Serializer<v2168::SerializedNetworkItemStackDescriptor>::serialize(BinaryWriter &stream, const v2168::SerializedNetworkItemStackDescriptor &value)
{
    stream.write<std::int16_t>(value.id);
    stream.write<std::uint16_t>(value.stack_size);
    stream.writeVarInt<std::uint32_t>(value.aux_value);
    stream.write<bool>(value.net_id_variant.has_value());
    if (value.net_id_variant.has_value()) {
        stream.writeVarInt<std::int32_t>((*value.net_id_variant));
    }
    stream.writeVarInt<std::uint32_t>(value.block_runtime_id);
    stream.write(value.user_data_buffer);
}

auto Serializer<v2168::SerializedNetworkItemStackDescriptor>::deserialize(BinaryReader &stream) -> std::expected<v2168::SerializedNetworkItemStackDescriptor, std::error_code>
{
    v2168::SerializedNetworkItemStackDescriptor out;
    {
        auto v = stream.read<std::int16_t>();
        if (!v) return std::unexpected(v.error());
        out.id = static_cast<std::int16_t>(*v);
    }
    {
        auto v = stream.read<std::uint16_t>();
        if (!v) return std::unexpected(v.error());
        out.stack_size = static_cast<std::uint16_t>(*v);
    }
    {
        auto v = stream.readVarInt<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.aux_value = static_cast<std::uint32_t>(*v);
    }
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            std::int32_t staged{};
            auto v = stream.readVarInt<std::int32_t>();
            if (!v) return std::unexpected(v.error());
            staged = static_cast<std::int32_t>(*v);
            out.net_id_variant = std::move(staged);
        }
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

void Serializer<base::ItemComponentPacket>::serialize(BinaryWriter &stream, const base::ItemComponentPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.items.size());
    for (const auto &e0 : value.items) {
        Serializer<ItemComponentEntry>::serialize(stream, e0);
    }
}

auto Serializer<base::ItemComponentPacket>::deserialize(BinaryReader &stream) -> std::expected<base::ItemComponentPacket, std::error_code>
{
    base::ItemComponentPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.items.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.items.emplace_back();
            auto v = Serializer<ItemComponentEntry>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            out.items.back() = *v;
        }
    }
    return out;
}

void Serializer<ItemStackNetIdVariant>::serialize(BinaryWriter &stream, const ItemStackNetIdVariant &value)
{
    stream.writeVarInt<std::uint32_t>((value).index());
    switch ((value).index()) {
        case 0: {
            Serializer<ItemStackNetId>::serialize(stream, std::get<0>(value));
            break;
        }
        case 1: {
            Serializer<ItemStackRequestId>::serialize(stream, std::get<1>(value));
            break;
        }
        case 2: {
            Serializer<ItemStackLegacyRequestId>::serialize(stream, std::get<2>(value));
            break;
        }
    }
}

auto Serializer<ItemStackNetIdVariant>::deserialize(BinaryReader &stream) -> std::expected<ItemStackNetIdVariant, std::error_code>
{
    ItemStackNetIdVariant out;
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<ItemStackNetId, ItemStackRequestId, ItemStackLegacyRequestId> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<ItemStackNetId, ItemStackRequestId, ItemStackLegacyRequestId>> alt0{};
                {
                    auto v = Serializer<ItemStackNetId>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<ItemStackNetId, ItemStackRequestId, ItemStackLegacyRequestId>> alt0{};
                {
                    auto v = Serializer<ItemStackRequestId>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<ItemStackNetId, ItemStackRequestId, ItemStackLegacyRequestId>> alt0{};
                {
                    auto v = Serializer<ItemStackLegacyRequestId>::deserialize(stream);
                    if (!v) return std::unexpected(v.error());
                    alt0 = *v;
                }
                var0.emplace<2>(alt0);
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
