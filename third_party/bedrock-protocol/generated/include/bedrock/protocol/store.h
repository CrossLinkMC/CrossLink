#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <expected>
#include <optional>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>

#include <bedrock/protocol/detail/reflect.hpp>
#include <bedrock/protocol/enum.hpp>
#include <bedrock/protocol/packet.hpp>
#include <bedrock/protocol/serializer.hpp>
#include <bedrock/protocol/stream.hpp>
#include <bedrock/protocol/uuid.hpp>

#include <bedrock/protocol/presence.h>

namespace bedrock::protocol {

struct ShowProfilePacket {
    static constexpr int Id = 104;
    std::string player_xuid{};
};

struct RefreshEntitlementsPacket {
    static constexpr int Id = 305;
};

enum class ShowStoreOfferRedirectType : std::uint8_t {
    MarketplaceOffer = 0,
    DressingRoomOffer = 1,
    ThirdPartyServerPage = 2,
    Count = 3,
};

struct PurchaseReceiptPacket {
    static constexpr int Id = 92;
    std::vector<std::string> purchase_receipts{};
};

namespace base {

struct ShowStoreOfferPacket {
    static constexpr int Id = 91;
    std::string offer_id{};
    ShowStoreOfferRedirectType redirect_type{};
};

}  // namespace base

namespace v859 {

struct ShowStoreOfferPacket {
    static constexpr int Id = 91;
    UUID offer_id{};
    ShowStoreOfferRedirectType redirect_type{};
};

}  // namespace v859

namespace v944 {

using ShowStoreOfferPacket = v859::ShowStoreOfferPacket;

}  // namespace v944

namespace v975 {

using ShowStoreOfferPacket = v859::ShowStoreOfferPacket;

struct ServerStoreInfoPacket {
    static constexpr int Id = 346;
    std::optional<ClientStoreEntryPointConfiguration> client_store_entry_point_configuration{};
};

}  // namespace v975

namespace v1001 {

using ShowStoreOfferPacket = v859::ShowStoreOfferPacket;

using ServerStoreInfoPacket = v975::ServerStoreInfoPacket;

}  // namespace v1001

namespace v2168 {

using ShowStoreOfferPacket = v859::ShowStoreOfferPacket;

using ServerStoreInfoPacket = v975::ServerStoreInfoPacket;

}  // namespace v2168

namespace v2225 {

using ShowStoreOfferPacket = v859::ShowStoreOfferPacket;

using ServerStoreInfoPacket = v975::ServerStoreInfoPacket;

}  // namespace v2225

namespace detail {

template <int V>
struct ShowStoreOfferPacket_;

template <int V> requires (V < 859)
struct ShowStoreOfferPacket_<V> { using type = base::ShowStoreOfferPacket; };

template <int V> requires (V >= 859)
struct ShowStoreOfferPacket_<V> { using type = v859::ShowStoreOfferPacket; };

template <int V>
struct ServerStoreInfoPacket_;

template <int V> requires (V >= 975)
struct ServerStoreInfoPacket_<V> { using type = v975::ServerStoreInfoPacket; };

}  // namespace detail

template <int V> using ShowStoreOfferPacket_ = typename detail::ShowStoreOfferPacket_<V>::type;
template <int V> using ServerStoreInfoPacket_ = typename detail::ServerStoreInfoPacket_<V>::type;

template <int V>
struct packet_of<V, 91> { using type = ShowStoreOfferPacket_<V>; };

template <int V>
struct packet_of<V, 92> { using type = PurchaseReceiptPacket; };

template <int V>
struct packet_of<V, 104> { using type = ShowProfilePacket; };

template <int V>
struct packet_of<V, 305> { using type = RefreshEntitlementsPacket; };

template <int V> requires (V >= 975)
struct packet_of<V, 346> { using type = ServerStoreInfoPacket_<V>; };

namespace detail {

template <>
inline constexpr std::array<ShowStoreOfferRedirectType, 4> values_v<ShowStoreOfferRedirectType>{{
    ShowStoreOfferRedirectType::MarketplaceOffer,
    ShowStoreOfferRedirectType::DressingRoomOffer,
    ShowStoreOfferRedirectType::ThirdPartyServerPage,
    ShowStoreOfferRedirectType::Count,
}};

template <>
inline constexpr std::array<std::string_view, 4> names_v<ShowStoreOfferRedirectType>{{
    "marketplaceoffer",
    "dressingroomoffer",
    "thirdpartyserverpage",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<ShowStoreOfferRedirectType>{"ShowStoreOfferRedirectType"};

}  // namespace detail

namespace detail {

template <>
inline constexpr bool is_reflected_struct_v<ShowProfilePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<ShowProfilePacket>{"ShowProfilePacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<ShowProfilePacket>{{
    "player_xuid",
}};

template <>
struct field_accessor<ShowProfilePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.player_xuid;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<RefreshEntitlementsPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<RefreshEntitlementsPacket>{"RefreshEntitlementsPacket"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<RefreshEntitlementsPacket>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<base::ShowStoreOfferPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ShowStoreOfferPacket>{"ShowStoreOfferPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<base::ShowStoreOfferPacket>{{
    "offer_id",
    "redirect_type",
}};

template <>
struct field_accessor<base::ShowStoreOfferPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.offer_id;
        }
        else {
            return value.redirect_type;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v859::ShowStoreOfferPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v859::ShowStoreOfferPacket>{"ShowStoreOfferPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v859::ShowStoreOfferPacket>{{
    "offer_id",
    "redirect_type",
}};

template <>
struct field_accessor<v859::ShowStoreOfferPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.offer_id;
        }
        else {
            return value.redirect_type;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<PurchaseReceiptPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<PurchaseReceiptPacket>{"PurchaseReceiptPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<PurchaseReceiptPacket>{{
    "purchase_receipts",
}};

template <>
struct field_accessor<PurchaseReceiptPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.purchase_receipts;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v975::ServerStoreInfoPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v975::ServerStoreInfoPacket>{"ServerStoreInfoPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v975::ServerStoreInfoPacket>{{
    "client_store_entry_point_configuration",
}};

template <>
struct field_accessor<v975::ServerStoreInfoPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.client_store_entry_point_configuration;
    }
};

}  // namespace detail


template <>
struct Serializer<ShowProfilePacket> {
    static void serialize(BinaryWriter &stream, const ShowProfilePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<ShowProfilePacket, std::error_code>;
};

template <>
struct Serializer<RefreshEntitlementsPacket> {
    static void serialize(BinaryWriter &stream, const RefreshEntitlementsPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<RefreshEntitlementsPacket, std::error_code>;
};

template <>
struct Serializer<base::ShowStoreOfferPacket> {
    static void serialize(BinaryWriter &stream, const base::ShowStoreOfferPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ShowStoreOfferPacket, std::error_code>;
};

template <>
struct Serializer<v859::ShowStoreOfferPacket> {
    static void serialize(BinaryWriter &stream, const v859::ShowStoreOfferPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v859::ShowStoreOfferPacket, std::error_code>;
};

template <>
struct Serializer<PurchaseReceiptPacket> {
    static void serialize(BinaryWriter &stream, const PurchaseReceiptPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<PurchaseReceiptPacket, std::error_code>;
};

template <>
struct Serializer<v975::ServerStoreInfoPacket> {
    static void serialize(BinaryWriter &stream, const v975::ServerStoreInfoPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v975::ServerStoreInfoPacket, std::error_code>;
};
using ShowStoreOfferPacket = ShowStoreOfferPacket_<2225>;
using ServerStoreInfoPacket = ServerStoreInfoPacket_<2225>;

}  // namespace bedrock::protocol
