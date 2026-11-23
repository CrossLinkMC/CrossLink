#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <expected>
#include <optional>
#include <string>
#include <string_view>
#include <system_error>
#include <variant>
#include <vector>

#include <bedrock/protocol/detail/reflect.hpp>
#include <bedrock/protocol/enum.hpp>
#include <bedrock/protocol/packet.hpp>
#include <bedrock/protocol/serializer.hpp>
#include <bedrock/protocol/stream.hpp>

#include <bedrock/protocol/actor.h>

namespace bedrock::protocol {

struct ScoreboardId {
    std::int64_t raw_id{};
};

struct PlayerScoreboardId {
    ActorUniqueID actor_unique_id{};
};

namespace IdentityDefinition_nested {

enum class Type : std::uint8_t {
    Invalid = 0,
    Player = 1,
    Entity = 2,
    FakePlayer = 3,
};

}  // namespace IdentityDefinition_nested

struct IdentityDefinition {
    using Type = IdentityDefinition_nested::Type;
};

enum class ScorePacketType : std::uint8_t {
    Change = 0,
    Remove = 1,
};

enum class ScoreboardIdentityPacketType : std::uint8_t {
    Update = 0,
    Remove = 1,
};

struct ScorePacketInfo {
    ScoreboardId scoreboard_id{};
    std::string objective_name{};
    std::int32_t score_value{};
    IdentityDefinition::Type identity_type{};
    PlayerScoreboardId player_id{};
    ActorUniqueID entity_id{};
    std::string fake_player_name{};
};

struct RemoveObjectivePacket {
    static constexpr int Id = 106;
    std::string objective_name{};
};

enum class ObjectiveSortOrder : std::uint8_t {
    Ascending = 0,
    Descending = 1,
};

struct SetDisplayObjectivePacket {
    static constexpr int Id = 107;
    std::string display_slot_name{};
    std::string objective_name{};
    std::string objective_display_name{};
    std::string criteria_name{};
    ObjectiveSortOrder sort_order{};
};

namespace base {

struct ScoreboardIdentityPacketInfo {
    ScoreboardId scoreboard_id{};
    PlayerScoreboardId player_id{};
};

namespace SetScorePacket_nested {

struct RemovedScorePacketInfo {
    ScoreboardId scoreboard_id{};
    std::string objective_name{};
    std::int32_t score_value{};
};

}  // namespace SetScorePacket_nested

struct SetScorePacket {
    using RemovedScorePacketInfo = SetScorePacket_nested::RemovedScorePacketInfo;

    static constexpr int Id = 108;
    ScorePacketType type{};
    std::vector<ScorePacketInfo> score_info{};
    std::vector<base::SetScorePacket::RemovedScorePacketInfo> removed_score_info{};
};

struct SetScoreboardIdentityPacket {
    static constexpr int Id = 112;
    ScoreboardIdentityPacketType type{};
    std::vector<base::ScoreboardIdentityPacketInfo> identity_info{};
    std::vector<ScoreboardId> removed_identity_info{};
};

}  // namespace base

namespace v766 {

using ScoreboardIdentityPacketInfo = base::ScoreboardIdentityPacketInfo;

using SetScorePacket = base::SetScorePacket;

using SetScoreboardIdentityPacket = base::SetScoreboardIdentityPacket;

}  // namespace v766

namespace v776 {

using ScoreboardIdentityPacketInfo = base::ScoreboardIdentityPacketInfo;

using SetScorePacket = base::SetScorePacket;

using SetScoreboardIdentityPacket = base::SetScoreboardIdentityPacket;

}  // namespace v776

namespace v786 {

using ScoreboardIdentityPacketInfo = base::ScoreboardIdentityPacketInfo;

using SetScorePacket = base::SetScorePacket;

using SetScoreboardIdentityPacket = base::SetScoreboardIdentityPacket;

}  // namespace v786

namespace v800 {

using ScoreboardIdentityPacketInfo = base::ScoreboardIdentityPacketInfo;

using SetScorePacket = base::SetScorePacket;

using SetScoreboardIdentityPacket = base::SetScoreboardIdentityPacket;

}  // namespace v800

namespace v818 {

using ScoreboardIdentityPacketInfo = base::ScoreboardIdentityPacketInfo;

using SetScorePacket = base::SetScorePacket;

using SetScoreboardIdentityPacket = base::SetScoreboardIdentityPacket;

}  // namespace v818

namespace v827 {

using ScoreboardIdentityPacketInfo = base::ScoreboardIdentityPacketInfo;

using SetScorePacket = base::SetScorePacket;

using SetScoreboardIdentityPacket = base::SetScoreboardIdentityPacket;

}  // namespace v827

namespace v844 {

using ScoreboardIdentityPacketInfo = base::ScoreboardIdentityPacketInfo;

using SetScorePacket = base::SetScorePacket;

using SetScoreboardIdentityPacket = base::SetScoreboardIdentityPacket;

}  // namespace v844

namespace v859 {

using ScoreboardIdentityPacketInfo = base::ScoreboardIdentityPacketInfo;

using SetScorePacket = base::SetScorePacket;

using SetScoreboardIdentityPacket = base::SetScoreboardIdentityPacket;

}  // namespace v859

namespace v898 {

using ScoreboardIdentityPacketInfo = base::ScoreboardIdentityPacketInfo;

using SetScorePacket = base::SetScorePacket;

using SetScoreboardIdentityPacket = base::SetScoreboardIdentityPacket;

}  // namespace v898

namespace v924 {

using ScoreboardIdentityPacketInfo = base::ScoreboardIdentityPacketInfo;

using SetScorePacket = base::SetScorePacket;

using SetScoreboardIdentityPacket = base::SetScoreboardIdentityPacket;

}  // namespace v924

namespace v975 {

using ScoreboardIdentityPacketInfo = base::ScoreboardIdentityPacketInfo;

using SetScorePacket = base::SetScorePacket;

using SetScoreboardIdentityPacket = base::SetScoreboardIdentityPacket;

}  // namespace v975

namespace v2168 {

enum class ScorePacketEntryAction : std::uint8_t {
    Remove = 0,
    ChangePlayer = 1,
    ChangeEntity = 2,
    ChangeFakePlayer = 3,
};

struct RemoveScore {
    ScoreboardId scoreboard_id{};
    std::optional<std::string> objective_name{};
};

struct ChangePlayerScore {
    ScoreboardId scoreboard_id{};
    std::string objective_name{};
    std::int32_t score_value{};
    PlayerScoreboardId player_id{};
};

struct ChangeEntityScore {
    ScoreboardId scoreboard_id{};
    std::string objective_name{};
    std::int32_t score_value{};
    ActorUniqueID entity_id{};
};

struct ChangeFakePlayerScore {
    ScoreboardId scoreboard_id{};
    std::string objective_name{};
    std::int32_t score_value{};
    std::string fake_player_name{};
};

struct ScoreboardIdentityPacketInfo {
    ScoreboardId scoreboard_id{};
    std::optional<ActorUniqueID> player_id{};
};

namespace SetScorePacket_nested {

using RemovedScorePacketInfo = base::SetScorePacket::RemovedScorePacketInfo;

}  // namespace SetScorePacket_nested

struct SetScorePacket {
    using RemovedScorePacketInfo = SetScorePacket_nested::RemovedScorePacketInfo;

    static constexpr int Id = 108;
    std::vector<std::variant<v2168::RemoveScore, v2168::ChangePlayerScore, v2168::ChangeEntityScore, v2168::ChangeFakePlayerScore>> score_info{};
};

struct SetScoreboardIdentityPacket {
    static constexpr int Id = 112;
    ScoreboardIdentityPacketType type{};
    std::vector<v2168::ScoreboardIdentityPacketInfo> identity_info{};
};

}  // namespace v2168

namespace v2225 {

using ScorePacketEntryAction = v2168::ScorePacketEntryAction;

using RemoveScore = v2168::RemoveScore;

using ChangePlayerScore = v2168::ChangePlayerScore;

using ChangeEntityScore = v2168::ChangeEntityScore;

using ChangeFakePlayerScore = v2168::ChangeFakePlayerScore;

using ScoreboardIdentityPacketInfo = v2168::ScoreboardIdentityPacketInfo;

using SetScorePacket = v2168::SetScorePacket;

using SetScoreboardIdentityPacket = v2168::SetScoreboardIdentityPacket;

}  // namespace v2225

namespace detail {

template <int V>
struct ScorePacketEntryAction_;

template <int V> requires (V >= 2168)
struct ScorePacketEntryAction_<V> { using type = v2168::ScorePacketEntryAction; };

template <int V>
struct RemoveScore_;

template <int V> requires (V >= 2168)
struct RemoveScore_<V> { using type = v2168::RemoveScore; };

template <int V>
struct ChangePlayerScore_;

template <int V> requires (V >= 2168)
struct ChangePlayerScore_<V> { using type = v2168::ChangePlayerScore; };

template <int V>
struct ChangeEntityScore_;

template <int V> requires (V >= 2168)
struct ChangeEntityScore_<V> { using type = v2168::ChangeEntityScore; };

template <int V>
struct ChangeFakePlayerScore_;

template <int V> requires (V >= 2168)
struct ChangeFakePlayerScore_<V> { using type = v2168::ChangeFakePlayerScore; };

template <int V>
struct ScoreboardIdentityPacketInfo_;

template <int V> requires (V < 2168)
struct ScoreboardIdentityPacketInfo_<V> { using type = base::ScoreboardIdentityPacketInfo; };

template <int V> requires (V >= 2168)
struct ScoreboardIdentityPacketInfo_<V> { using type = v2168::ScoreboardIdentityPacketInfo; };

template <int V>
struct SetScorePacket_;

template <int V> requires (V < 2168)
struct SetScorePacket_<V> { using type = base::SetScorePacket; };

template <int V> requires (V >= 2168)
struct SetScorePacket_<V> { using type = v2168::SetScorePacket; };

template <int V>
struct SetScoreboardIdentityPacket_;

template <int V> requires (V < 2168)
struct SetScoreboardIdentityPacket_<V> { using type = base::SetScoreboardIdentityPacket; };

template <int V> requires (V >= 2168)
struct SetScoreboardIdentityPacket_<V> { using type = v2168::SetScoreboardIdentityPacket; };

}  // namespace detail

template <int V> using ScorePacketEntryAction_ = typename detail::ScorePacketEntryAction_<V>::type;
template <int V> using RemoveScore_ = typename detail::RemoveScore_<V>::type;
template <int V> using ChangePlayerScore_ = typename detail::ChangePlayerScore_<V>::type;
template <int V> using ChangeEntityScore_ = typename detail::ChangeEntityScore_<V>::type;
template <int V> using ChangeFakePlayerScore_ = typename detail::ChangeFakePlayerScore_<V>::type;
template <int V> using ScoreboardIdentityPacketInfo_ = typename detail::ScoreboardIdentityPacketInfo_<V>::type;
template <int V> using SetScorePacket_ = typename detail::SetScorePacket_<V>::type;
template <int V> using SetScoreboardIdentityPacket_ = typename detail::SetScoreboardIdentityPacket_<V>::type;

template <int V>
struct packet_of<V, 106> { using type = RemoveObjectivePacket; };

template <int V>
struct packet_of<V, 107> { using type = SetDisplayObjectivePacket; };

template <int V>
struct packet_of<V, 108> { using type = SetScorePacket_<V>; };

template <int V>
struct packet_of<V, 112> { using type = SetScoreboardIdentityPacket_<V>; };

namespace detail {

template <>
inline constexpr std::array<IdentityDefinition::Type, 4> values_v<IdentityDefinition::Type>{{
    IdentityDefinition::Type::Invalid,
    IdentityDefinition::Type::Player,
    IdentityDefinition::Type::Entity,
    IdentityDefinition::Type::FakePlayer,
}};

template <>
inline constexpr std::array<std::string_view, 4> names_v<IdentityDefinition::Type>{{
    "invalid",
    "player",
    "entity",
    "fakeplayer",
}};

template <>
inline constexpr std::string_view type_name_v<IdentityDefinition::Type>{"IdentityDefinition::Type"};

template <>
inline constexpr std::array<ScorePacketType, 2> values_v<ScorePacketType>{{
    ScorePacketType::Change,
    ScorePacketType::Remove,
}};

template <>
inline constexpr std::array<std::string_view, 2> names_v<ScorePacketType>{{
    "change",
    "remove",
}};

template <>
inline constexpr std::string_view type_name_v<ScorePacketType>{"ScorePacketType"};

template <>
inline constexpr std::array<v2168::ScorePacketEntryAction, 4> values_v<v2168::ScorePacketEntryAction>{{
    v2168::ScorePacketEntryAction::Remove,
    v2168::ScorePacketEntryAction::ChangePlayer,
    v2168::ScorePacketEntryAction::ChangeEntity,
    v2168::ScorePacketEntryAction::ChangeFakePlayer,
}};

template <>
inline constexpr std::array<std::string_view, 4> names_v<v2168::ScorePacketEntryAction>{{
    "remove",
    "changeplayer",
    "changeentity",
    "changefakeplayer",
}};

template <>
inline constexpr std::string_view type_name_v<v2168::ScorePacketEntryAction>{"ScorePacketEntryAction"};

template <>
inline constexpr std::array<ScoreboardIdentityPacketType, 2> values_v<ScoreboardIdentityPacketType>{{
    ScoreboardIdentityPacketType::Update,
    ScoreboardIdentityPacketType::Remove,
}};

template <>
inline constexpr std::array<std::string_view, 2> names_v<ScoreboardIdentityPacketType>{{
    "update",
    "remove",
}};

template <>
inline constexpr std::string_view type_name_v<ScoreboardIdentityPacketType>{"ScoreboardIdentityPacketType"};

template <>
inline constexpr std::array<ObjectiveSortOrder, 2> values_v<ObjectiveSortOrder>{{
    ObjectiveSortOrder::Ascending,
    ObjectiveSortOrder::Descending,
}};

template <>
inline constexpr std::array<std::string_view, 2> names_v<ObjectiveSortOrder>{{
    "ascending",
    "descending",
}};

template <>
inline constexpr std::string_view type_name_v<ObjectiveSortOrder>{"ObjectiveSortOrder"};

}  // namespace detail

namespace detail {

template <>
inline constexpr bool is_reflected_struct_v<ScoreboardId> = true;

template <>
inline constexpr std::string_view struct_name_v<ScoreboardId>{"ScoreboardId"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<ScoreboardId>{{
    "raw_id",
}};

template <>
struct field_accessor<ScoreboardId> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.raw_id;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<PlayerScoreboardId> = true;

template <>
inline constexpr std::string_view struct_name_v<PlayerScoreboardId>{"PlayerScoreboardId"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<PlayerScoreboardId>{{
    "actor_unique_id",
}};

template <>
struct field_accessor<PlayerScoreboardId> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.actor_unique_id;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<IdentityDefinition> = true;

template <>
inline constexpr std::string_view struct_name_v<IdentityDefinition>{"IdentityDefinition"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<IdentityDefinition>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<ScorePacketInfo> = true;

template <>
inline constexpr std::string_view struct_name_v<ScorePacketInfo>{"ScorePacketInfo"};

template <>
inline constexpr std::array<std::string_view, 7> field_names_v<ScorePacketInfo>{{
    "scoreboard_id",
    "objective_name",
    "score_value",
    "identity_type",
    "player_id",
    "entity_id",
    "fake_player_name",
}};

template <>
struct field_accessor<ScorePacketInfo> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.scoreboard_id;
        }
        else if constexpr (I == 1) {
            return value.objective_name;
        }
        else if constexpr (I == 2) {
            return value.score_value;
        }
        else if constexpr (I == 3) {
            return value.identity_type;
        }
        else if constexpr (I == 4) {
            return value.player_id;
        }
        else if constexpr (I == 5) {
            return value.entity_id;
        }
        else {
            return value.fake_player_name;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::RemoveScore> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::RemoveScore>{"RemoveScore"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2168::RemoveScore>{{
    "scoreboard_id",
    "objective_name",
}};

template <>
struct field_accessor<v2168::RemoveScore> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.scoreboard_id;
        }
        else {
            return value.objective_name;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ChangePlayerScore> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ChangePlayerScore>{"ChangePlayerScore"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v2168::ChangePlayerScore>{{
    "scoreboard_id",
    "objective_name",
    "score_value",
    "player_id",
}};

template <>
struct field_accessor<v2168::ChangePlayerScore> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.scoreboard_id;
        }
        else if constexpr (I == 1) {
            return value.objective_name;
        }
        else if constexpr (I == 2) {
            return value.score_value;
        }
        else {
            return value.player_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ChangeEntityScore> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ChangeEntityScore>{"ChangeEntityScore"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v2168::ChangeEntityScore>{{
    "scoreboard_id",
    "objective_name",
    "score_value",
    "entity_id",
}};

template <>
struct field_accessor<v2168::ChangeEntityScore> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.scoreboard_id;
        }
        else if constexpr (I == 1) {
            return value.objective_name;
        }
        else if constexpr (I == 2) {
            return value.score_value;
        }
        else {
            return value.entity_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ChangeFakePlayerScore> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ChangeFakePlayerScore>{"ChangeFakePlayerScore"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v2168::ChangeFakePlayerScore>{{
    "scoreboard_id",
    "objective_name",
    "score_value",
    "fake_player_name",
}};

template <>
struct field_accessor<v2168::ChangeFakePlayerScore> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.scoreboard_id;
        }
        else if constexpr (I == 1) {
            return value.objective_name;
        }
        else if constexpr (I == 2) {
            return value.score_value;
        }
        else {
            return value.fake_player_name;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::ScoreboardIdentityPacketInfo> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ScoreboardIdentityPacketInfo>{"ScoreboardIdentityPacketInfo"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<base::ScoreboardIdentityPacketInfo>{{
    "scoreboard_id",
    "player_id",
}};

template <>
struct field_accessor<base::ScoreboardIdentityPacketInfo> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.scoreboard_id;
        }
        else {
            return value.player_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ScoreboardIdentityPacketInfo> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ScoreboardIdentityPacketInfo>{"ScoreboardIdentityPacketInfo"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2168::ScoreboardIdentityPacketInfo>{{
    "scoreboard_id",
    "player_id",
}};

template <>
struct field_accessor<v2168::ScoreboardIdentityPacketInfo> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.scoreboard_id;
        }
        else {
            return value.player_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::SetScorePacket::RemovedScorePacketInfo> = true;

template <>
inline constexpr std::string_view struct_name_v<base::SetScorePacket::RemovedScorePacketInfo>{"SetScorePacket::RemovedScorePacketInfo"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<base::SetScorePacket::RemovedScorePacketInfo>{{
    "scoreboard_id",
    "objective_name",
    "score_value",
}};

template <>
struct field_accessor<base::SetScorePacket::RemovedScorePacketInfo> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.scoreboard_id;
        }
        else if constexpr (I == 1) {
            return value.objective_name;
        }
        else {
            return value.score_value;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::SetScorePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::SetScorePacket>{"SetScorePacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<base::SetScorePacket>{{
    "type",
    "score_info",
    "removed_score_info",
}};

template <>
struct field_accessor<base::SetScorePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.type;
        }
        else if constexpr (I == 1) {
            return value.score_info;
        }
        else {
            return value.removed_score_info;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::SetScorePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::SetScorePacket>{"SetScorePacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2168::SetScorePacket>{{
    "score_info",
}};

template <>
struct field_accessor<v2168::SetScorePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.score_info;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::SetScoreboardIdentityPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::SetScoreboardIdentityPacket>{"SetScoreboardIdentityPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<base::SetScoreboardIdentityPacket>{{
    "type",
    "identity_info",
    "removed_identity_info",
}};

template <>
struct field_accessor<base::SetScoreboardIdentityPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.type;
        }
        else if constexpr (I == 1) {
            return value.identity_info;
        }
        else {
            return value.removed_identity_info;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::SetScoreboardIdentityPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::SetScoreboardIdentityPacket>{"SetScoreboardIdentityPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2168::SetScoreboardIdentityPacket>{{
    "type",
    "identity_info",
}};

template <>
struct field_accessor<v2168::SetScoreboardIdentityPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.type;
        }
        else {
            return value.identity_info;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<RemoveObjectivePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<RemoveObjectivePacket>{"RemoveObjectivePacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<RemoveObjectivePacket>{{
    "objective_name",
}};

template <>
struct field_accessor<RemoveObjectivePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.objective_name;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<SetDisplayObjectivePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<SetDisplayObjectivePacket>{"SetDisplayObjectivePacket"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<SetDisplayObjectivePacket>{{
    "display_slot_name",
    "objective_name",
    "objective_display_name",
    "criteria_name",
    "sort_order",
}};

template <>
struct field_accessor<SetDisplayObjectivePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.display_slot_name;
        }
        else if constexpr (I == 1) {
            return value.objective_name;
        }
        else if constexpr (I == 2) {
            return value.objective_display_name;
        }
        else if constexpr (I == 3) {
            return value.criteria_name;
        }
        else {
            return value.sort_order;
        }
    }
};

}  // namespace detail


template <>
struct Serializer<ScoreboardId> {
    static void serialize(BinaryWriter &stream, const ScoreboardId &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<ScoreboardId, std::error_code>;
};

template <>
struct Serializer<PlayerScoreboardId> {
    static void serialize(BinaryWriter &stream, const PlayerScoreboardId &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<PlayerScoreboardId, std::error_code>;
};

template <>
struct Serializer<ScorePacketInfo> {
    static void serialize(BinaryWriter &stream, const ScorePacketInfo &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<ScorePacketInfo, std::error_code>;
};

template <>
struct Serializer<v2168::RemoveScore> {
    static void serialize(BinaryWriter &stream, const v2168::RemoveScore &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::RemoveScore, std::error_code>;
};

template <>
struct Serializer<v2168::ChangePlayerScore> {
    static void serialize(BinaryWriter &stream, const v2168::ChangePlayerScore &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ChangePlayerScore, std::error_code>;
};

template <>
struct Serializer<v2168::ChangeEntityScore> {
    static void serialize(BinaryWriter &stream, const v2168::ChangeEntityScore &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ChangeEntityScore, std::error_code>;
};

template <>
struct Serializer<v2168::ChangeFakePlayerScore> {
    static void serialize(BinaryWriter &stream, const v2168::ChangeFakePlayerScore &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ChangeFakePlayerScore, std::error_code>;
};

template <>
struct Serializer<base::ScoreboardIdentityPacketInfo> {
    static void serialize(BinaryWriter &stream, const base::ScoreboardIdentityPacketInfo &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ScoreboardIdentityPacketInfo, std::error_code>;
};

template <>
struct Serializer<v2168::ScoreboardIdentityPacketInfo> {
    static void serialize(BinaryWriter &stream, const v2168::ScoreboardIdentityPacketInfo &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ScoreboardIdentityPacketInfo, std::error_code>;
};

template <>
struct Serializer<base::SetScorePacket::RemovedScorePacketInfo> {
    static void serialize(BinaryWriter &stream, const base::SetScorePacket::RemovedScorePacketInfo &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::SetScorePacket::RemovedScorePacketInfo, std::error_code>;
};

template <>
struct Serializer<base::SetScorePacket> {
    static void serialize(BinaryWriter &stream, const base::SetScorePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::SetScorePacket, std::error_code>;
};

template <>
struct Serializer<v2168::SetScorePacket> {
    static void serialize(BinaryWriter &stream, const v2168::SetScorePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::SetScorePacket, std::error_code>;
};

template <>
struct Serializer<base::SetScoreboardIdentityPacket> {
    static void serialize(BinaryWriter &stream, const base::SetScoreboardIdentityPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::SetScoreboardIdentityPacket, std::error_code>;
};

template <>
struct Serializer<v2168::SetScoreboardIdentityPacket> {
    static void serialize(BinaryWriter &stream, const v2168::SetScoreboardIdentityPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::SetScoreboardIdentityPacket, std::error_code>;
};

template <>
struct Serializer<RemoveObjectivePacket> {
    static void serialize(BinaryWriter &stream, const RemoveObjectivePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<RemoveObjectivePacket, std::error_code>;
};

template <>
struct Serializer<SetDisplayObjectivePacket> {
    static void serialize(BinaryWriter &stream, const SetDisplayObjectivePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<SetDisplayObjectivePacket, std::error_code>;
};
using ScorePacketEntryAction = ScorePacketEntryAction_<2225>;
using RemoveScore = RemoveScore_<2225>;
using ChangePlayerScore = ChangePlayerScore_<2225>;
using ChangeEntityScore = ChangeEntityScore_<2225>;
using ChangeFakePlayerScore = ChangeFakePlayerScore_<2225>;
using ScoreboardIdentityPacketInfo = ScoreboardIdentityPacketInfo_<2225>;
using SetScorePacket = SetScorePacket_<2225>;
using SetScoreboardIdentityPacket = SetScoreboardIdentityPacket_<2225>;

}  // namespace bedrock::protocol
