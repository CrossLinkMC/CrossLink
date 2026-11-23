#include <bedrock/protocol/data_store.h>

namespace bedrock::protocol {


void Serializer<v898::DataStoreUpdate>::serialize(BinaryWriter &stream, const v898::DataStoreUpdate &value)
{
    stream.write(value.data_store_name);
    stream.write(value.property);
    stream.write(value.path);
    stream.writeVarInt<std::uint32_t>((value.data).index());
    switch ((value.data).index()) {
        case 0: {
            stream.write<double>(std::get<0>(value.data));
            break;
        }
        case 1: {
            stream.write<bool>(std::get<1>(value.data));
            break;
        }
        case 2: {
            stream.write(std::get<2>(value.data));
            break;
        }
    }
    stream.write<std::uint32_t>(value.update_count);
}

auto Serializer<v898::DataStoreUpdate>::deserialize(BinaryReader &stream) -> std::expected<v898::DataStoreUpdate, std::error_code>
{
    v898::DataStoreUpdate out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.data_store_name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.property = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.path = *v;
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<double, bool, std::string> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<double, bool, std::string>> alt0{};
                {
                    auto v = stream.read<double>();
                    if (!v) return std::unexpected(v.error());
                    alt0 = static_cast<double>(*v);
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<double, bool, std::string>> alt0{};
                {
                    auto v = stream.read<bool>();
                    if (!v) return std::unexpected(v.error());
                    alt0 = static_cast<bool>(*v);
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<double, bool, std::string>> alt0{};
                {
                    auto v = stream.read<std::string>();
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
        out.data = var0;
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.update_count = static_cast<std::uint32_t>(*v);
    }
    return out;
}

void Serializer<v924::DataStoreUpdate>::serialize(BinaryWriter &stream, const v924::DataStoreUpdate &value)
{
    stream.write(value.data_store_name);
    stream.write(value.property);
    stream.write(value.path);
    stream.writeVarInt<std::uint32_t>((value.data).index());
    switch ((value.data).index()) {
        case 0: {
            stream.write<double>(std::get<0>(value.data));
            break;
        }
        case 1: {
            stream.write<bool>(std::get<1>(value.data));
            break;
        }
        case 2: {
            stream.write(std::get<2>(value.data));
            break;
        }
    }
    stream.write<std::uint32_t>(value.property_update_count);
    stream.write<std::uint32_t>(value.path_update_count);
}

auto Serializer<v924::DataStoreUpdate>::deserialize(BinaryReader &stream) -> std::expected<v924::DataStoreUpdate, std::error_code>
{
    v924::DataStoreUpdate out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.data_store_name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.property = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.path = *v;
    }
    {
        auto tag0 = stream.readVarInt<std::uint32_t>();
        if (!tag0) return std::unexpected(tag0.error());
        std::variant<double, bool, std::string> var0{};
        switch (*tag0) {
            case 0: {
                std::variant_alternative_t<0, std::variant<double, bool, std::string>> alt0{};
                {
                    auto v = stream.read<double>();
                    if (!v) return std::unexpected(v.error());
                    alt0 = static_cast<double>(*v);
                }
                var0.emplace<0>(alt0);
                break;
            }
            case 1: {
                std::variant_alternative_t<1, std::variant<double, bool, std::string>> alt0{};
                {
                    auto v = stream.read<bool>();
                    if (!v) return std::unexpected(v.error());
                    alt0 = static_cast<bool>(*v);
                }
                var0.emplace<1>(alt0);
                break;
            }
            case 2: {
                std::variant_alternative_t<2, std::variant<double, bool, std::string>> alt0{};
                {
                    auto v = stream.read<std::string>();
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
        out.data = var0;
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.property_update_count = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.path_update_count = static_cast<std::uint32_t>(*v);
    }
    return out;
}

void Serializer<DataStoreChange>::serialize(BinaryWriter &stream, const DataStoreChange &value)
{
    stream.write(value.data_store_name);
    stream.write(value.property);
    stream.write<std::uint32_t>(value.update_count);
    Serializer<DynamicValue>::serialize(stream, value.new_data);
}

auto Serializer<DataStoreChange>::deserialize(BinaryReader &stream) -> std::expected<DataStoreChange, std::error_code>
{
    DataStoreChange out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.data_store_name = *v;
    }
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.property = *v;
    }
    {
        auto v = stream.read<std::uint32_t>();
        if (!v) return std::unexpected(v.error());
        out.update_count = static_cast<std::uint32_t>(*v);
    }
    {
        auto v = Serializer<DynamicValue>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.new_data = *v;
    }
    return out;
}

void Serializer<DataStoreRemoval>::serialize(BinaryWriter &stream, const DataStoreRemoval &value)
{
    stream.write(value.data_store_name);
}

auto Serializer<DataStoreRemoval>::deserialize(BinaryReader &stream) -> std::expected<DataStoreRemoval, std::error_code>
{
    DataStoreRemoval out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.data_store_name = *v;
    }
    return out;
}

void Serializer<v898::ClientboundDataStorePacket>::serialize(BinaryWriter &stream, const v898::ClientboundDataStorePacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.updates.size());
    for (const auto &e0 : value.updates) {
        stream.writeVarInt<std::uint32_t>((e0).index());
        switch ((e0).index()) {
            case 0: {
                Serializer<v898::DataStoreUpdate>::serialize(stream, std::get<0>(e0));
                break;
            }
            case 1: {
                Serializer<DataStoreChange>::serialize(stream, std::get<1>(e0));
                break;
            }
            case 2: {
                Serializer<DataStoreRemoval>::serialize(stream, std::get<2>(e0));
                break;
            }
        }
    }
}

auto Serializer<v898::ClientboundDataStorePacket>::deserialize(BinaryReader &stream) -> std::expected<v898::ClientboundDataStorePacket, std::error_code>
{
    v898::ClientboundDataStorePacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.updates.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.updates.emplace_back();
            auto tag1 = stream.readVarInt<std::uint32_t>();
            if (!tag1) return std::unexpected(tag1.error());
            std::variant<v898::DataStoreUpdate, DataStoreChange, DataStoreRemoval> var1{};
            switch (*tag1) {
                case 0: {
                    std::variant_alternative_t<0, std::variant<v898::DataStoreUpdate, DataStoreChange, DataStoreRemoval>> alt1{};
                    {
                        auto v = Serializer<v898::DataStoreUpdate>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<0>(alt1);
                    break;
                }
                case 1: {
                    std::variant_alternative_t<1, std::variant<v898::DataStoreUpdate, DataStoreChange, DataStoreRemoval>> alt1{};
                    {
                        auto v = Serializer<DataStoreChange>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<1>(alt1);
                    break;
                }
                case 2: {
                    std::variant_alternative_t<2, std::variant<v898::DataStoreUpdate, DataStoreChange, DataStoreRemoval>> alt1{};
                    {
                        auto v = Serializer<DataStoreRemoval>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<2>(alt1);
                    break;
                }
                default: {
                    return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
                }
            }
            out.updates.back() = var1;
        }
    }
    return out;
}

void Serializer<v924::ClientboundDataStorePacket>::serialize(BinaryWriter &stream, const v924::ClientboundDataStorePacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.updates.size());
    for (const auto &e0 : value.updates) {
        stream.writeVarInt<std::uint32_t>((e0).index());
        switch ((e0).index()) {
            case 0: {
                Serializer<v924::DataStoreUpdate>::serialize(stream, std::get<0>(e0));
                break;
            }
            case 1: {
                Serializer<DataStoreChange>::serialize(stream, std::get<1>(e0));
                break;
            }
            case 2: {
                Serializer<DataStoreRemoval>::serialize(stream, std::get<2>(e0));
                break;
            }
        }
    }
}

auto Serializer<v924::ClientboundDataStorePacket>::deserialize(BinaryReader &stream) -> std::expected<v924::ClientboundDataStorePacket, std::error_code>
{
    v924::ClientboundDataStorePacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.updates.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.updates.emplace_back();
            auto tag1 = stream.readVarInt<std::uint32_t>();
            if (!tag1) return std::unexpected(tag1.error());
            std::variant<v924::DataStoreUpdate, DataStoreChange, DataStoreRemoval> var1{};
            switch (*tag1) {
                case 0: {
                    std::variant_alternative_t<0, std::variant<v924::DataStoreUpdate, DataStoreChange, DataStoreRemoval>> alt1{};
                    {
                        auto v = Serializer<v924::DataStoreUpdate>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<0>(alt1);
                    break;
                }
                case 1: {
                    std::variant_alternative_t<1, std::variant<v924::DataStoreUpdate, DataStoreChange, DataStoreRemoval>> alt1{};
                    {
                        auto v = Serializer<DataStoreChange>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<1>(alt1);
                    break;
                }
                case 2: {
                    std::variant_alternative_t<2, std::variant<v924::DataStoreUpdate, DataStoreChange, DataStoreRemoval>> alt1{};
                    {
                        auto v = Serializer<DataStoreRemoval>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<2>(alt1);
                    break;
                }
                default: {
                    return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
                }
            }
            out.updates.back() = var1;
        }
    }
    return out;
}

void Serializer<v898::ServerboundDataStorePacket>::serialize(BinaryWriter &stream, const v898::ServerboundDataStorePacket &value)
{
    Serializer<v898::DataStoreUpdate>::serialize(stream, value.update);
}

auto Serializer<v898::ServerboundDataStorePacket>::deserialize(BinaryReader &stream) -> std::expected<v898::ServerboundDataStorePacket, std::error_code>
{
    v898::ServerboundDataStorePacket out;
    {
        auto v = Serializer<v898::DataStoreUpdate>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.update = *v;
    }
    return out;
}

void Serializer<v924::ServerboundDataStorePacket>::serialize(BinaryWriter &stream, const v924::ServerboundDataStorePacket &value)
{
    Serializer<v924::DataStoreUpdate>::serialize(stream, value.update);
}

auto Serializer<v924::ServerboundDataStorePacket>::deserialize(BinaryReader &stream) -> std::expected<v924::ServerboundDataStorePacket, std::error_code>
{
    v924::ServerboundDataStorePacket out;
    {
        auto v = Serializer<v924::DataStoreUpdate>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.update = *v;
    }
    return out;
}

void Serializer<v859::DataStoreSyncPacket>::serialize(BinaryWriter &stream, const v859::DataStoreSyncPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.updates.size());
    for (const auto &e0 : value.updates) {
        stream.writeVarInt<std::uint32_t>((e0).index());
        switch ((e0).index()) {
            case 0: {
                Serializer<DataStoreChange>::serialize(stream, std::get<0>(e0));
                break;
            }
            case 1: {
                Serializer<DataStoreRemoval>::serialize(stream, std::get<1>(e0));
                break;
            }
        }
    }
}

auto Serializer<v859::DataStoreSyncPacket>::deserialize(BinaryReader &stream) -> std::expected<v859::DataStoreSyncPacket, std::error_code>
{
    v859::DataStoreSyncPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.updates.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.updates.emplace_back();
            auto tag1 = stream.readVarInt<std::uint32_t>();
            if (!tag1) return std::unexpected(tag1.error());
            std::variant<DataStoreChange, DataStoreRemoval> var1{};
            switch (*tag1) {
                case 0: {
                    std::variant_alternative_t<0, std::variant<DataStoreChange, DataStoreRemoval>> alt1{};
                    {
                        auto v = Serializer<DataStoreChange>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<0>(alt1);
                    break;
                }
                case 1: {
                    std::variant_alternative_t<1, std::variant<DataStoreChange, DataStoreRemoval>> alt1{};
                    {
                        auto v = Serializer<DataStoreRemoval>::deserialize(stream);
                        if (!v) return std::unexpected(v.error());
                        alt1 = *v;
                    }
                    var1.emplace<1>(alt1);
                    break;
                }
                default: {
                    return std::unexpected(std::make_error_code(std::errc::illegal_byte_sequence));
                }
            }
            out.updates.back() = var1;
        }
    }
    return out;
}

}  // namespace bedrock::protocol
