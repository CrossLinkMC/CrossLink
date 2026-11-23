#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <expected>
#include <optional>
#include <string>
#include <string_view>
#include <system_error>

#include <bedrock/protocol/detail/reflect.hpp>
#include <bedrock/protocol/enum.hpp>
#include <bedrock/protocol/packet.hpp>
#include <bedrock/protocol/serializer.hpp>
#include <bedrock/protocol/stream.hpp>
#include <bedrock/protocol/uuid.hpp>

namespace bedrock::protocol {

struct ClientStoreEntryPointConfiguration {
    std::string store_id{};
    std::string store_name{};
};

struct ServerTelemetryData {
    std::string server_id{};
    std::string scenario_id{};
    std::string world_id{};
    std::string owner_id{};
};

struct PlayerPartyInfo {
    std::string party_id{};
    bool is_leader{};
};

enum class PartyDestinationCookieIntent : std::int8_t {
    Notify = 0,
    OptIn = 1,
    OptOut = 2,
};

enum class MatchmakingState : std::uint8_t {
    Idle = 0,
    Matchmaking = 1,
    MatchFound = 2,
    Canceled = 3,
    PlayerLeftParty = 4,
    PlayerLeftServer = 5,
    ServerShutdown = 6,
    TimedOut = 7,
    RequeueAsParty = 8,
};

struct MatchmakingStateOptions {
    std::optional<std::string> triggering_player_name{};
    std::optional<bool> triggered_by_local_player{};
};

namespace base {

struct PresenceConfiguration {
    std::string experience_name{};
    std::string world_name{};
};

struct GatheringsConfigurationJoinInfo {
    std::string experience_id{};
    std::string experience_name{};
    std::string experience_world_id{};
    std::string experience_world_name{};
    std::string creator_id{};
    std::string store_id{};
    std::string store_name{};
};

struct ServerConfigurationJoinInfo {
    std::optional<base::GatheringsConfigurationJoinInfo> gatherings_configuration{};
};

struct TransferPacket {
    static constexpr int Id = 85;
    std::string destination{};
    std::uint16_t destination_port{};
    bool reload_world{};
};

}  // namespace base

namespace v944 {

using PresenceConfiguration = base::PresenceConfiguration;

struct GatheringsConfigurationJoinInfo {
    UUID experience_id{};
    std::string experience_name{};
    UUID experience_world_id{};
    std::string experience_world_name{};
    std::string creator_id{};
    UUID target_id{};
    std::string scenario_id{};
    std::string server_id{};
};

struct ServerConfigurationJoinInfo {
    std::optional<v944::GatheringsConfigurationJoinInfo> gatherings_configuration{};
    std::optional<ClientStoreEntryPointConfiguration> client_store_entry_point_configuration{};
    std::optional<base::PresenceConfiguration> presence_configuration{};
};

struct TransferPacket {
    static constexpr int Id = 85;
    std::string destination{};
    std::uint16_t destination_port{};
    bool reload_world{};
};

struct PartyChangedPacket {
    static constexpr int Id = 342;
    std::optional<std::string> party_id{};
};

}  // namespace v944

namespace v975 {

using PresenceConfiguration = base::PresenceConfiguration;

using GatheringsConfigurationJoinInfo = v944::GatheringsConfigurationJoinInfo;

using ServerConfigurationJoinInfo = v944::ServerConfigurationJoinInfo;

struct ServerPresenceInfoPacket {
    static constexpr int Id = 347;
    std::optional<base::PresenceConfiguration> presence_configuration{};
};

using TransferPacket = v944::TransferPacket;

struct PartyChangedPacket {
    static constexpr int Id = 342;
    std::optional<PlayerPartyInfo> party_info{};
};

}  // namespace v975

namespace v1001 {

struct PresenceConfiguration {
    std::optional<std::string> experience_name{};
    std::optional<std::string> world_name{};
    std::string rich_presence_id{};
};

using GatheringsConfigurationJoinInfo = v944::GatheringsConfigurationJoinInfo;

struct ServerConfigurationJoinInfo {
    std::optional<v944::GatheringsConfigurationJoinInfo> gatherings_configuration{};
    std::optional<ClientStoreEntryPointConfiguration> client_store_entry_point_configuration{};
    std::optional<v1001::PresenceConfiguration> presence_configuration{};
};

struct ServerPresenceInfoPacket {
    static constexpr int Id = 347;
    std::optional<v1001::PresenceConfiguration> presence_configuration{};
};

using TransferPacket = v944::TransferPacket;

struct PartyDestinationCookieResponsePacket {
    static constexpr int Id = 350;
    std::string cookie{};
    bool accepted{};
};

using PartyChangedPacket = v975::PartyChangedPacket;

struct SendPartyDestinationCookiePacket {
    static constexpr int Id = 349;
    std::string cookie{};
    PartyDestinationCookieIntent intent{};
    std::string destination_name{};
};

}  // namespace v1001

namespace v2168 {

struct PresenceConfiguration {
    std::optional<std::string> rich_presence_id{};
};

struct GatheringsConfigurationJoinInfo {
    UUID experience_id{};
    std::string experience_name{};
    std::optional<UUID> experience_world_id{};
    std::optional<std::string> experience_world_name{};
    std::string creator_id{};
    std::optional<UUID> target_id{};
    std::optional<std::string> mpsas_scenario_id{};
    std::optional<std::string> server_id{};
};

struct ServerConfigurationJoinInfo {
    std::optional<v2168::GatheringsConfigurationJoinInfo> gatherings_configuration{};
    std::optional<ClientStoreEntryPointConfiguration> client_store_entry_point_configuration{};
    std::optional<v2168::PresenceConfiguration> presence_configuration{};
};

struct ServerPresenceInfoPacket {
    static constexpr int Id = 347;
    std::optional<v2168::PresenceConfiguration> presence_configuration{};
};

struct TransferPacket {
    static constexpr int Id = 85;
    std::string destination{};
    std::uint16_t destination_port{};
    bool reload_world{};
    std::optional<v2168::GatheringsConfigurationJoinInfo> gatherings_configuration{};
};

using PartyDestinationCookieResponsePacket = v1001::PartyDestinationCookieResponsePacket;

using PartyChangedPacket = v975::PartyChangedPacket;

using SendPartyDestinationCookiePacket = v1001::SendPartyDestinationCookiePacket;

}  // namespace v2168

namespace v2225 {

using PresenceConfiguration = v2168::PresenceConfiguration;

using GatheringsConfigurationJoinInfo = v2168::GatheringsConfigurationJoinInfo;

using ServerConfigurationJoinInfo = v2168::ServerConfigurationJoinInfo;

using ServerPresenceInfoPacket = v2168::ServerPresenceInfoPacket;

using TransferPacket = v2168::TransferPacket;

using PartyDestinationCookieResponsePacket = v1001::PartyDestinationCookieResponsePacket;

using PartyChangedPacket = v975::PartyChangedPacket;

using SendPartyDestinationCookiePacket = v1001::SendPartyDestinationCookiePacket;

struct ClientboundMatchmakingStatePacket {
    static constexpr int Id = 353;
    MatchmakingState state{};
    std::string destination_name{};
    std::optional<MatchmakingStateOptions> options{};
};

struct ServerboundMatchmakingCancelPacket {
    static constexpr int Id = 356;
};

}  // namespace v2225

namespace detail {

template <int V>
struct PresenceConfiguration_;

template <int V> requires (V < 1001)
struct PresenceConfiguration_<V> { using type = base::PresenceConfiguration; };

template <int V> requires (V >= 1001 && V < 2168)
struct PresenceConfiguration_<V> { using type = v1001::PresenceConfiguration; };

template <int V> requires (V >= 2168)
struct PresenceConfiguration_<V> { using type = v2168::PresenceConfiguration; };

template <int V>
struct GatheringsConfigurationJoinInfo_;

template <int V> requires (V < 944)
struct GatheringsConfigurationJoinInfo_<V> { using type = base::GatheringsConfigurationJoinInfo; };

template <int V> requires (V >= 944 && V < 2168)
struct GatheringsConfigurationJoinInfo_<V> { using type = v944::GatheringsConfigurationJoinInfo; };

template <int V> requires (V >= 2168)
struct GatheringsConfigurationJoinInfo_<V> { using type = v2168::GatheringsConfigurationJoinInfo; };

template <int V>
struct ServerConfigurationJoinInfo_;

template <int V> requires (V < 944)
struct ServerConfigurationJoinInfo_<V> { using type = base::ServerConfigurationJoinInfo; };

template <int V> requires (V >= 944 && V < 1001)
struct ServerConfigurationJoinInfo_<V> { using type = v944::ServerConfigurationJoinInfo; };

template <int V> requires (V >= 1001 && V < 2168)
struct ServerConfigurationJoinInfo_<V> { using type = v1001::ServerConfigurationJoinInfo; };

template <int V> requires (V >= 2168)
struct ServerConfigurationJoinInfo_<V> { using type = v2168::ServerConfigurationJoinInfo; };

template <int V>
struct ServerPresenceInfoPacket_;

template <int V> requires (V >= 975 && V < 1001)
struct ServerPresenceInfoPacket_<V> { using type = v975::ServerPresenceInfoPacket; };

template <int V> requires (V >= 1001 && V < 2168)
struct ServerPresenceInfoPacket_<V> { using type = v1001::ServerPresenceInfoPacket; };

template <int V> requires (V >= 2168)
struct ServerPresenceInfoPacket_<V> { using type = v2168::ServerPresenceInfoPacket; };

template <int V>
struct TransferPacket_;

template <int V> requires (V < 944)
struct TransferPacket_<V> { using type = base::TransferPacket; };

template <int V> requires (V >= 944 && V < 2168)
struct TransferPacket_<V> { using type = v944::TransferPacket; };

template <int V> requires (V >= 2168)
struct TransferPacket_<V> { using type = v2168::TransferPacket; };

template <int V>
struct PartyDestinationCookieResponsePacket_;

template <int V> requires (V >= 1001)
struct PartyDestinationCookieResponsePacket_<V> { using type = v1001::PartyDestinationCookieResponsePacket; };

template <int V>
struct PartyChangedPacket_;

template <int V> requires (V >= 944 && V < 975)
struct PartyChangedPacket_<V> { using type = v944::PartyChangedPacket; };

template <int V> requires (V >= 975)
struct PartyChangedPacket_<V> { using type = v975::PartyChangedPacket; };

template <int V>
struct SendPartyDestinationCookiePacket_;

template <int V> requires (V >= 1001)
struct SendPartyDestinationCookiePacket_<V> { using type = v1001::SendPartyDestinationCookiePacket; };

template <int V>
struct ClientboundMatchmakingStatePacket_;

template <int V> requires (V >= 2225)
struct ClientboundMatchmakingStatePacket_<V> { using type = v2225::ClientboundMatchmakingStatePacket; };

template <int V>
struct ServerboundMatchmakingCancelPacket_;

template <int V> requires (V >= 2225)
struct ServerboundMatchmakingCancelPacket_<V> { using type = v2225::ServerboundMatchmakingCancelPacket; };

}  // namespace detail

template <int V> using PresenceConfiguration_ = typename detail::PresenceConfiguration_<V>::type;
template <int V> using GatheringsConfigurationJoinInfo_ = typename detail::GatheringsConfigurationJoinInfo_<V>::type;
template <int V> using ServerConfigurationJoinInfo_ = typename detail::ServerConfigurationJoinInfo_<V>::type;
template <int V> using ServerPresenceInfoPacket_ = typename detail::ServerPresenceInfoPacket_<V>::type;
template <int V> using TransferPacket_ = typename detail::TransferPacket_<V>::type;
template <int V> using PartyDestinationCookieResponsePacket_ = typename detail::PartyDestinationCookieResponsePacket_<V>::type;
template <int V> using PartyChangedPacket_ = typename detail::PartyChangedPacket_<V>::type;
template <int V> using SendPartyDestinationCookiePacket_ = typename detail::SendPartyDestinationCookiePacket_<V>::type;
template <int V> using ClientboundMatchmakingStatePacket_ = typename detail::ClientboundMatchmakingStatePacket_<V>::type;
template <int V> using ServerboundMatchmakingCancelPacket_ = typename detail::ServerboundMatchmakingCancelPacket_<V>::type;

template <int V>
struct packet_of<V, 85> { using type = TransferPacket_<V>; };

template <int V> requires (V >= 944)
struct packet_of<V, 342> { using type = PartyChangedPacket_<V>; };

template <int V> requires (V >= 975)
struct packet_of<V, 347> { using type = ServerPresenceInfoPacket_<V>; };

template <int V> requires (V >= 1001)
struct packet_of<V, 349> { using type = SendPartyDestinationCookiePacket_<V>; };

template <int V> requires (V >= 1001)
struct packet_of<V, 350> { using type = PartyDestinationCookieResponsePacket_<V>; };

template <int V> requires (V >= 2225)
struct packet_of<V, 353> { using type = ClientboundMatchmakingStatePacket_<V>; };

template <int V> requires (V >= 2225)
struct packet_of<V, 356> { using type = ServerboundMatchmakingCancelPacket_<V>; };

namespace detail {

template <>
inline constexpr std::array<PartyDestinationCookieIntent, 3> values_v<PartyDestinationCookieIntent>{{
    PartyDestinationCookieIntent::Notify,
    PartyDestinationCookieIntent::OptIn,
    PartyDestinationCookieIntent::OptOut,
}};

template <>
inline constexpr std::array<std::string_view, 3> names_v<PartyDestinationCookieIntent>{{
    "notify",
    "optin",
    "optout",
}};

template <>
inline constexpr std::string_view type_name_v<PartyDestinationCookieIntent>{"PartyDestinationCookieIntent"};

template <>
inline constexpr std::array<MatchmakingState, 9> values_v<MatchmakingState>{{
    MatchmakingState::Idle,
    MatchmakingState::Matchmaking,
    MatchmakingState::MatchFound,
    MatchmakingState::Canceled,
    MatchmakingState::PlayerLeftParty,
    MatchmakingState::PlayerLeftServer,
    MatchmakingState::ServerShutdown,
    MatchmakingState::TimedOut,
    MatchmakingState::RequeueAsParty,
}};

template <>
inline constexpr std::array<std::string_view, 9> names_v<MatchmakingState>{{
    "idle",
    "matchmaking",
    "matchfound",
    "canceled",
    "playerleftparty",
    "playerleftserver",
    "servershutdown",
    "timedout",
    "requeueasparty",
}};

template <>
inline constexpr std::string_view type_name_v<MatchmakingState>{"MatchmakingState"};

}  // namespace detail

namespace detail {

template <>
inline constexpr bool is_reflected_struct_v<base::PresenceConfiguration> = true;

template <>
inline constexpr std::string_view struct_name_v<base::PresenceConfiguration>{"PresenceConfiguration"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<base::PresenceConfiguration>{{
    "experience_name",
    "world_name",
}};

template <>
struct field_accessor<base::PresenceConfiguration> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.experience_name;
        }
        else {
            return value.world_name;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::PresenceConfiguration> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::PresenceConfiguration>{"PresenceConfiguration"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v1001::PresenceConfiguration>{{
    "experience_name",
    "world_name",
    "rich_presence_id",
}};

template <>
struct field_accessor<v1001::PresenceConfiguration> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.experience_name;
        }
        else if constexpr (I == 1) {
            return value.world_name;
        }
        else {
            return value.rich_presence_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::PresenceConfiguration> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::PresenceConfiguration>{"PresenceConfiguration"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2168::PresenceConfiguration>{{
    "rich_presence_id",
}};

template <>
struct field_accessor<v2168::PresenceConfiguration> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.rich_presence_id;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::GatheringsConfigurationJoinInfo> = true;

template <>
inline constexpr std::string_view struct_name_v<base::GatheringsConfigurationJoinInfo>{"GatheringsConfigurationJoinInfo"};

template <>
inline constexpr std::array<std::string_view, 7> field_names_v<base::GatheringsConfigurationJoinInfo>{{
    "experience_id",
    "experience_name",
    "experience_world_id",
    "experience_world_name",
    "creator_id",
    "store_id",
    "store_name",
}};

template <>
struct field_accessor<base::GatheringsConfigurationJoinInfo> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.experience_id;
        }
        else if constexpr (I == 1) {
            return value.experience_name;
        }
        else if constexpr (I == 2) {
            return value.experience_world_id;
        }
        else if constexpr (I == 3) {
            return value.experience_world_name;
        }
        else if constexpr (I == 4) {
            return value.creator_id;
        }
        else if constexpr (I == 5) {
            return value.store_id;
        }
        else {
            return value.store_name;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::GatheringsConfigurationJoinInfo> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::GatheringsConfigurationJoinInfo>{"GatheringsConfigurationJoinInfo"};

template <>
inline constexpr std::array<std::string_view, 8> field_names_v<v944::GatheringsConfigurationJoinInfo>{{
    "experience_id",
    "experience_name",
    "experience_world_id",
    "experience_world_name",
    "creator_id",
    "target_id",
    "scenario_id",
    "server_id",
}};

template <>
struct field_accessor<v944::GatheringsConfigurationJoinInfo> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.experience_id;
        }
        else if constexpr (I == 1) {
            return value.experience_name;
        }
        else if constexpr (I == 2) {
            return value.experience_world_id;
        }
        else if constexpr (I == 3) {
            return value.experience_world_name;
        }
        else if constexpr (I == 4) {
            return value.creator_id;
        }
        else if constexpr (I == 5) {
            return value.target_id;
        }
        else if constexpr (I == 6) {
            return value.scenario_id;
        }
        else {
            return value.server_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::GatheringsConfigurationJoinInfo> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::GatheringsConfigurationJoinInfo>{"GatheringsConfigurationJoinInfo"};

template <>
inline constexpr std::array<std::string_view, 8> field_names_v<v2168::GatheringsConfigurationJoinInfo>{{
    "experience_id",
    "experience_name",
    "experience_world_id",
    "experience_world_name",
    "creator_id",
    "target_id",
    "mpsas_scenario_id",
    "server_id",
}};

template <>
struct field_accessor<v2168::GatheringsConfigurationJoinInfo> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.experience_id;
        }
        else if constexpr (I == 1) {
            return value.experience_name;
        }
        else if constexpr (I == 2) {
            return value.experience_world_id;
        }
        else if constexpr (I == 3) {
            return value.experience_world_name;
        }
        else if constexpr (I == 4) {
            return value.creator_id;
        }
        else if constexpr (I == 5) {
            return value.target_id;
        }
        else if constexpr (I == 6) {
            return value.mpsas_scenario_id;
        }
        else {
            return value.server_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<ClientStoreEntryPointConfiguration> = true;

template <>
inline constexpr std::string_view struct_name_v<ClientStoreEntryPointConfiguration>{"ClientStoreEntryPointConfiguration"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<ClientStoreEntryPointConfiguration>{{
    "store_id",
    "store_name",
}};

template <>
struct field_accessor<ClientStoreEntryPointConfiguration> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.store_id;
        }
        else {
            return value.store_name;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::ServerConfigurationJoinInfo> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ServerConfigurationJoinInfo>{"ServerConfigurationJoinInfo"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::ServerConfigurationJoinInfo>{{
    "gatherings_configuration",
}};

template <>
struct field_accessor<base::ServerConfigurationJoinInfo> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.gatherings_configuration;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::ServerConfigurationJoinInfo> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::ServerConfigurationJoinInfo>{"ServerConfigurationJoinInfo"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v944::ServerConfigurationJoinInfo>{{
    "gatherings_configuration",
    "client_store_entry_point_configuration",
    "presence_configuration",
}};

template <>
struct field_accessor<v944::ServerConfigurationJoinInfo> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.gatherings_configuration;
        }
        else if constexpr (I == 1) {
            return value.client_store_entry_point_configuration;
        }
        else {
            return value.presence_configuration;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::ServerConfigurationJoinInfo> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::ServerConfigurationJoinInfo>{"ServerConfigurationJoinInfo"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v1001::ServerConfigurationJoinInfo>{{
    "gatherings_configuration",
    "client_store_entry_point_configuration",
    "presence_configuration",
}};

template <>
struct field_accessor<v1001::ServerConfigurationJoinInfo> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.gatherings_configuration;
        }
        else if constexpr (I == 1) {
            return value.client_store_entry_point_configuration;
        }
        else {
            return value.presence_configuration;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ServerConfigurationJoinInfo> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ServerConfigurationJoinInfo>{"ServerConfigurationJoinInfo"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v2168::ServerConfigurationJoinInfo>{{
    "gatherings_configuration",
    "client_store_entry_point_configuration",
    "presence_configuration",
}};

template <>
struct field_accessor<v2168::ServerConfigurationJoinInfo> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.gatherings_configuration;
        }
        else if constexpr (I == 1) {
            return value.client_store_entry_point_configuration;
        }
        else {
            return value.presence_configuration;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<ServerTelemetryData> = true;

template <>
inline constexpr std::string_view struct_name_v<ServerTelemetryData>{"ServerTelemetryData"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<ServerTelemetryData>{{
    "server_id",
    "scenario_id",
    "world_id",
    "owner_id",
}};

template <>
struct field_accessor<ServerTelemetryData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.server_id;
        }
        else if constexpr (I == 1) {
            return value.scenario_id;
        }
        else if constexpr (I == 2) {
            return value.world_id;
        }
        else {
            return value.owner_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v975::ServerPresenceInfoPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v975::ServerPresenceInfoPacket>{"ServerPresenceInfoPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v975::ServerPresenceInfoPacket>{{
    "presence_configuration",
}};

template <>
struct field_accessor<v975::ServerPresenceInfoPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.presence_configuration;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::ServerPresenceInfoPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::ServerPresenceInfoPacket>{"ServerPresenceInfoPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v1001::ServerPresenceInfoPacket>{{
    "presence_configuration",
}};

template <>
struct field_accessor<v1001::ServerPresenceInfoPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.presence_configuration;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ServerPresenceInfoPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ServerPresenceInfoPacket>{"ServerPresenceInfoPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2168::ServerPresenceInfoPacket>{{
    "presence_configuration",
}};

template <>
struct field_accessor<v2168::ServerPresenceInfoPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.presence_configuration;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::TransferPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::TransferPacket>{"TransferPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<base::TransferPacket>{{
    "destination",
    "destination_port",
    "reload_world",
}};

template <>
struct field_accessor<base::TransferPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.destination;
        }
        else if constexpr (I == 1) {
            return value.destination_port;
        }
        else {
            return value.reload_world;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::TransferPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::TransferPacket>{"TransferPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v944::TransferPacket>{{
    "destination",
    "destination_port",
    "reload_world",
}};

template <>
struct field_accessor<v944::TransferPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.destination;
        }
        else if constexpr (I == 1) {
            return value.destination_port;
        }
        else {
            return value.reload_world;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::TransferPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::TransferPacket>{"TransferPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v2168::TransferPacket>{{
    "destination",
    "destination_port",
    "reload_world",
    "gatherings_configuration",
}};

template <>
struct field_accessor<v2168::TransferPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.destination;
        }
        else if constexpr (I == 1) {
            return value.destination_port;
        }
        else if constexpr (I == 2) {
            return value.reload_world;
        }
        else {
            return value.gatherings_configuration;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::PartyDestinationCookieResponsePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::PartyDestinationCookieResponsePacket>{"PartyDestinationCookieResponsePacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v1001::PartyDestinationCookieResponsePacket>{{
    "cookie",
    "accepted",
}};

template <>
struct field_accessor<v1001::PartyDestinationCookieResponsePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.cookie;
        }
        else {
            return value.accepted;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<PlayerPartyInfo> = true;

template <>
inline constexpr std::string_view struct_name_v<PlayerPartyInfo>{"PlayerPartyInfo"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<PlayerPartyInfo>{{
    "party_id",
    "is_leader",
}};

template <>
struct field_accessor<PlayerPartyInfo> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.party_id;
        }
        else {
            return value.is_leader;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::PartyChangedPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::PartyChangedPacket>{"PartyChangedPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v944::PartyChangedPacket>{{
    "party_id",
}};

template <>
struct field_accessor<v944::PartyChangedPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.party_id;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v975::PartyChangedPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v975::PartyChangedPacket>{"PartyChangedPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v975::PartyChangedPacket>{{
    "party_info",
}};

template <>
struct field_accessor<v975::PartyChangedPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.party_info;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v1001::SendPartyDestinationCookiePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v1001::SendPartyDestinationCookiePacket>{"SendPartyDestinationCookiePacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v1001::SendPartyDestinationCookiePacket>{{
    "cookie",
    "intent",
    "destination_name",
}};

template <>
struct field_accessor<v1001::SendPartyDestinationCookiePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.cookie;
        }
        else if constexpr (I == 1) {
            return value.intent;
        }
        else {
            return value.destination_name;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<MatchmakingStateOptions> = true;

template <>
inline constexpr std::string_view struct_name_v<MatchmakingStateOptions>{"MatchmakingStateOptions"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<MatchmakingStateOptions>{{
    "triggering_player_name",
    "triggered_by_local_player",
}};

template <>
struct field_accessor<MatchmakingStateOptions> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.triggering_player_name;
        }
        else {
            return value.triggered_by_local_player;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::ClientboundMatchmakingStatePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::ClientboundMatchmakingStatePacket>{"ClientboundMatchmakingStatePacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v2225::ClientboundMatchmakingStatePacket>{{
    "state",
    "destination_name",
    "options",
}};

template <>
struct field_accessor<v2225::ClientboundMatchmakingStatePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.state;
        }
        else if constexpr (I == 1) {
            return value.destination_name;
        }
        else {
            return value.options;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2225::ServerboundMatchmakingCancelPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2225::ServerboundMatchmakingCancelPacket>{"ServerboundMatchmakingCancelPacket"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<v2225::ServerboundMatchmakingCancelPacket>{{
}};

}  // namespace detail


template <>
struct Serializer<base::PresenceConfiguration> {
    static void serialize(BinaryWriter &stream, const base::PresenceConfiguration &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::PresenceConfiguration, std::error_code>;
};

template <>
struct Serializer<v1001::PresenceConfiguration> {
    static void serialize(BinaryWriter &stream, const v1001::PresenceConfiguration &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::PresenceConfiguration, std::error_code>;
};

template <>
struct Serializer<v2168::PresenceConfiguration> {
    static void serialize(BinaryWriter &stream, const v2168::PresenceConfiguration &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::PresenceConfiguration, std::error_code>;
};

template <>
struct Serializer<base::GatheringsConfigurationJoinInfo> {
    static void serialize(BinaryWriter &stream, const base::GatheringsConfigurationJoinInfo &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::GatheringsConfigurationJoinInfo, std::error_code>;
};

template <>
struct Serializer<v944::GatheringsConfigurationJoinInfo> {
    static void serialize(BinaryWriter &stream, const v944::GatheringsConfigurationJoinInfo &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::GatheringsConfigurationJoinInfo, std::error_code>;
};

template <>
struct Serializer<v2168::GatheringsConfigurationJoinInfo> {
    static void serialize(BinaryWriter &stream, const v2168::GatheringsConfigurationJoinInfo &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::GatheringsConfigurationJoinInfo, std::error_code>;
};

template <>
struct Serializer<ClientStoreEntryPointConfiguration> {
    static void serialize(BinaryWriter &stream, const ClientStoreEntryPointConfiguration &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<ClientStoreEntryPointConfiguration, std::error_code>;
};

template <>
struct Serializer<base::ServerConfigurationJoinInfo> {
    static void serialize(BinaryWriter &stream, const base::ServerConfigurationJoinInfo &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ServerConfigurationJoinInfo, std::error_code>;
};

template <>
struct Serializer<v944::ServerConfigurationJoinInfo> {
    static void serialize(BinaryWriter &stream, const v944::ServerConfigurationJoinInfo &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::ServerConfigurationJoinInfo, std::error_code>;
};

template <>
struct Serializer<v1001::ServerConfigurationJoinInfo> {
    static void serialize(BinaryWriter &stream, const v1001::ServerConfigurationJoinInfo &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::ServerConfigurationJoinInfo, std::error_code>;
};

template <>
struct Serializer<v2168::ServerConfigurationJoinInfo> {
    static void serialize(BinaryWriter &stream, const v2168::ServerConfigurationJoinInfo &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ServerConfigurationJoinInfo, std::error_code>;
};

template <>
struct Serializer<ServerTelemetryData> {
    static void serialize(BinaryWriter &stream, const ServerTelemetryData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<ServerTelemetryData, std::error_code>;
};

template <>
struct Serializer<v975::ServerPresenceInfoPacket> {
    static void serialize(BinaryWriter &stream, const v975::ServerPresenceInfoPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v975::ServerPresenceInfoPacket, std::error_code>;
};

template <>
struct Serializer<v1001::ServerPresenceInfoPacket> {
    static void serialize(BinaryWriter &stream, const v1001::ServerPresenceInfoPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::ServerPresenceInfoPacket, std::error_code>;
};

template <>
struct Serializer<v2168::ServerPresenceInfoPacket> {
    static void serialize(BinaryWriter &stream, const v2168::ServerPresenceInfoPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ServerPresenceInfoPacket, std::error_code>;
};

template <>
struct Serializer<base::TransferPacket> {
    static void serialize(BinaryWriter &stream, const base::TransferPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::TransferPacket, std::error_code>;
};

template <>
struct Serializer<v944::TransferPacket> {
    static void serialize(BinaryWriter &stream, const v944::TransferPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::TransferPacket, std::error_code>;
};

template <>
struct Serializer<v2168::TransferPacket> {
    static void serialize(BinaryWriter &stream, const v2168::TransferPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::TransferPacket, std::error_code>;
};

template <>
struct Serializer<v1001::PartyDestinationCookieResponsePacket> {
    static void serialize(BinaryWriter &stream, const v1001::PartyDestinationCookieResponsePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::PartyDestinationCookieResponsePacket, std::error_code>;
};

template <>
struct Serializer<PlayerPartyInfo> {
    static void serialize(BinaryWriter &stream, const PlayerPartyInfo &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<PlayerPartyInfo, std::error_code>;
};

template <>
struct Serializer<v944::PartyChangedPacket> {
    static void serialize(BinaryWriter &stream, const v944::PartyChangedPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::PartyChangedPacket, std::error_code>;
};

template <>
struct Serializer<v975::PartyChangedPacket> {
    static void serialize(BinaryWriter &stream, const v975::PartyChangedPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v975::PartyChangedPacket, std::error_code>;
};

template <>
struct Serializer<PartyDestinationCookieIntent> {
    static void serialize(BinaryWriter &stream, PartyDestinationCookieIntent value);
    static auto deserialize(BinaryReader &stream) -> std::expected<PartyDestinationCookieIntent, std::error_code>;
};

template <>
struct Serializer<v1001::SendPartyDestinationCookiePacket> {
    static void serialize(BinaryWriter &stream, const v1001::SendPartyDestinationCookiePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v1001::SendPartyDestinationCookiePacket, std::error_code>;
};

template <>
struct Serializer<MatchmakingStateOptions> {
    static void serialize(BinaryWriter &stream, const MatchmakingStateOptions &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<MatchmakingStateOptions, std::error_code>;
};

template <>
struct Serializer<v2225::ClientboundMatchmakingStatePacket> {
    static void serialize(BinaryWriter &stream, const v2225::ClientboundMatchmakingStatePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::ClientboundMatchmakingStatePacket, std::error_code>;
};

template <>
struct Serializer<v2225::ServerboundMatchmakingCancelPacket> {
    static void serialize(BinaryWriter &stream, const v2225::ServerboundMatchmakingCancelPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2225::ServerboundMatchmakingCancelPacket, std::error_code>;
};
using PresenceConfiguration = PresenceConfiguration_<2225>;
using GatheringsConfigurationJoinInfo = GatheringsConfigurationJoinInfo_<2225>;
using ServerConfigurationJoinInfo = ServerConfigurationJoinInfo_<2225>;
using ServerPresenceInfoPacket = ServerPresenceInfoPacket_<2225>;
using TransferPacket = TransferPacket_<2225>;
using PartyDestinationCookieResponsePacket = PartyDestinationCookieResponsePacket_<2225>;
using PartyChangedPacket = PartyChangedPacket_<2225>;
using SendPartyDestinationCookiePacket = SendPartyDestinationCookiePacket_<2225>;
using ClientboundMatchmakingStatePacket = ClientboundMatchmakingStatePacket_<2225>;
using ServerboundMatchmakingCancelPacket = ServerboundMatchmakingCancelPacket_<2225>;

}  // namespace bedrock::protocol
