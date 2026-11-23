#include <bedrock/protocol/store.h>

namespace bedrock::protocol {


void Serializer<ShowProfilePacket>::serialize(BinaryWriter &stream, const ShowProfilePacket &value)
{
    stream.write(value.player_xuid);
}

auto Serializer<ShowProfilePacket>::deserialize(BinaryReader &stream) -> std::expected<ShowProfilePacket, std::error_code>
{
    ShowProfilePacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.player_xuid = *v;
    }
    return out;
}

void Serializer<RefreshEntitlementsPacket>::serialize(BinaryWriter &stream, const RefreshEntitlementsPacket &value)
{
}

auto Serializer<RefreshEntitlementsPacket>::deserialize(BinaryReader &stream) -> std::expected<RefreshEntitlementsPacket, std::error_code>
{
    RefreshEntitlementsPacket out;
    return out;
}

void Serializer<base::ShowStoreOfferPacket>::serialize(BinaryWriter &stream, const base::ShowStoreOfferPacket &value)
{
    stream.write(value.offer_id);
    stream.write<std::uint8_t>(value.redirect_type);
}

auto Serializer<base::ShowStoreOfferPacket>::deserialize(BinaryReader &stream) -> std::expected<base::ShowStoreOfferPacket, std::error_code>
{
    base::ShowStoreOfferPacket out;
    {
        auto v = stream.read<std::string>();
        if (!v) return std::unexpected(v.error());
        out.offer_id = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.redirect_type = static_cast<ShowStoreOfferRedirectType>(*v);
    }
    return out;
}

void Serializer<v859::ShowStoreOfferPacket>::serialize(BinaryWriter &stream, const v859::ShowStoreOfferPacket &value)
{
    Serializer<UUID>::serialize(stream, value.offer_id);
    stream.write<std::uint8_t>(value.redirect_type);
}

auto Serializer<v859::ShowStoreOfferPacket>::deserialize(BinaryReader &stream) -> std::expected<v859::ShowStoreOfferPacket, std::error_code>
{
    v859::ShowStoreOfferPacket out;
    {
        auto v = Serializer<UUID>::deserialize(stream);
        if (!v) return std::unexpected(v.error());
        out.offer_id = *v;
    }
    {
        auto v = stream.read<std::uint8_t>();
        if (!v) return std::unexpected(v.error());
        out.redirect_type = static_cast<ShowStoreOfferRedirectType>(*v);
    }
    return out;
}

void Serializer<PurchaseReceiptPacket>::serialize(BinaryWriter &stream, const PurchaseReceiptPacket &value)
{
    stream.writeVarInt<std::uint32_t>(value.purchase_receipts.size());
    for (const auto &e0 : value.purchase_receipts) {
        stream.write(e0);
    }
}

auto Serializer<PurchaseReceiptPacket>::deserialize(BinaryReader &stream) -> std::expected<PurchaseReceiptPacket, std::error_code>
{
    PurchaseReceiptPacket out;
    {
        auto len0 = stream.readVarInt<std::uint32_t>();
        if (!len0) return std::unexpected(len0.error());
        out.purchase_receipts.clear();
        for (auto rep0 = *len0; rep0 > 0; --rep0) {
            out.purchase_receipts.emplace_back();
            auto v = stream.read<std::string>();
            if (!v) return std::unexpected(v.error());
            out.purchase_receipts.back() = *v;
        }
    }
    return out;
}

void Serializer<v975::ServerStoreInfoPacket>::serialize(BinaryWriter &stream, const v975::ServerStoreInfoPacket &value)
{
    stream.write<bool>(value.client_store_entry_point_configuration.has_value());
    if (value.client_store_entry_point_configuration.has_value()) {
        Serializer<ClientStoreEntryPointConfiguration>::serialize(stream, (*value.client_store_entry_point_configuration));
    }
}

auto Serializer<v975::ServerStoreInfoPacket>::deserialize(BinaryReader &stream) -> std::expected<v975::ServerStoreInfoPacket, std::error_code>
{
    v975::ServerStoreInfoPacket out;
    {
        auto present = stream.read<bool>();
        if (!present) return std::unexpected(present.error());
        if (*present) {
            ClientStoreEntryPointConfiguration staged{};
            auto v = Serializer<ClientStoreEntryPointConfiguration>::deserialize(stream);
            if (!v) return std::unexpected(v.error());
            staged = *v;
            out.client_store_entry_point_configuration = std::move(staged);
        }
    }
    return out;
}

}  // namespace bedrock::protocol
