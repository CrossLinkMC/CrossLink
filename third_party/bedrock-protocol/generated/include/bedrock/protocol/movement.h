#pragma once

#include <array>
#include <bitset>
#include <cstddef>
#include <cstdint>
#include <expected>
#include <optional>
#include <string_view>
#include <system_error>

#include <bedrock/protocol/detail/reflect.hpp>
#include <bedrock/protocol/enum.hpp>
#include <bedrock/protocol/packet.hpp>
#include <bedrock/protocol/serializer.hpp>
#include <bedrock/protocol/stream.hpp>

#include <bedrock/protocol/actor.h>
#include <bedrock/protocol/common.h>

namespace bedrock::protocol {

namespace PlayerPositionModeComponent_nested {

enum class PositionMode : std::uint8_t {
    Normal = 0,
    Respawn = 1,
    Teleport = 2,
    OnlyHeadRot = 3,
};

}  // namespace PlayerPositionModeComponent_nested

struct PlayerPositionModeComponent {
    using PositionMode = PlayerPositionModeComponent_nested::PositionMode;
};

struct ServerPlayerPostMovePositionPacket {
    static constexpr int Id = 16;
    Vec3 pos{};
};

enum class RewindType : std::uint8_t {
    Player = 0,
    Vehicle = 1,
};

enum class ServerAuthMovementMode : std::uint8_t {
    LegacyClientAuthoritativeV1Deprecated = 0,
    ClientAuthoritativeV2 = 1,
    ServerAuthoritativeV3 = 2,
};

namespace base {

struct MoveActorDeltaData {
    ActorRuntimeID runtime_id{};
    std::uint16_t header{};
    float new_position_x{};
    float new_position_y{};
    float new_position_z{};
    std::int8_t rot_x{};
    std::int8_t rot_y{};
    std::int8_t rot_y_head{};
};

struct MovePlayerPacket {
    static constexpr int Id = 19;
    ActorRuntimeID player_id{};
    Vec3 pos{};
    Vec2 rot{};
    float y_head_rot{};
    PlayerPositionModeComponent::PositionMode reset_position{};
    bool on_ground{};
    ActorRuntimeID riding_id{};
    std::int32_t cause{};
    std::int32_t source_entity_type{};
    PlayerInputTick tick{};
};

struct MoveActorDeltaPacket {
    static constexpr int Id = 111;
    base::MoveActorDeltaData move_data{};
};

struct CorrectPlayerMovePredictionPacket {
    static constexpr int Id = 161;
    RewindType prediction_type{};
    Vec3 pos{};
    Vec3 pos_delta{};
    Vec2 vehicle_rotation{};
    std::optional<float> vehicle_angular_velocity{};
    bool on_ground{};
    PlayerInputTick tick{};
};

}  // namespace base

namespace v748 {

using MoveActorDeltaData = base::MoveActorDeltaData;

using MovePlayerPacket = base::MovePlayerPacket;

using MoveActorDeltaPacket = base::MoveActorDeltaPacket;

using CorrectPlayerMovePredictionPacket = base::CorrectPlayerMovePredictionPacket;

struct SetMovementAuthorityPacket {
    static constexpr int Id = 319;
    ServerAuthMovementMode new_auth_movement_mode{};
};

}  // namespace v748

namespace v766 {

using MoveActorDeltaData = base::MoveActorDeltaData;

using MovePlayerPacket = base::MovePlayerPacket;

using MoveActorDeltaPacket = base::MoveActorDeltaPacket;

using CorrectPlayerMovePredictionPacket = base::CorrectPlayerMovePredictionPacket;

using SetMovementAuthorityPacket = v748::SetMovementAuthorityPacket;

}  // namespace v766

namespace v776 {

using MoveActorDeltaData = base::MoveActorDeltaData;

using MovePlayerPacket = base::MovePlayerPacket;

using MoveActorDeltaPacket = base::MoveActorDeltaPacket;

struct ActorDataFlagComponent {
    std::bitset<120> value{};
};

struct ActorDataBoundingBoxComponent {
    std::array<float, 3> value{};
};

struct ClientMovementPredictionSyncPacket {
    static constexpr int Id = 322;
    v776::ActorDataFlagComponent actor_data_flag{};
    v776::ActorDataBoundingBoxComponent actor_bounding_box{};
    std::array<float, 6> movement_attributes{};
    ActorUniqueID actor_id{};
};

using CorrectPlayerMovePredictionPacket = base::CorrectPlayerMovePredictionPacket;

using SetMovementAuthorityPacket = v748::SetMovementAuthorityPacket;

}  // namespace v776

namespace v786 {

using MoveActorDeltaData = base::MoveActorDeltaData;

using MovePlayerPacket = base::MovePlayerPacket;

using MoveActorDeltaPacket = base::MoveActorDeltaPacket;

struct ActorDataFlagComponent {
    std::bitset<123> value{};
};

using ActorDataBoundingBoxComponent = v776::ActorDataBoundingBoxComponent;

struct ClientMovementPredictionSyncPacket {
    static constexpr int Id = 322;
    v786::ActorDataFlagComponent actor_data_flag{};
    v776::ActorDataBoundingBoxComponent actor_bounding_box{};
    std::array<float, 6> movement_attributes{};
    ActorUniqueID actor_id{};
    bool is_flying{};
};

using CorrectPlayerMovePredictionPacket = base::CorrectPlayerMovePredictionPacket;

using SetMovementAuthorityPacket = v748::SetMovementAuthorityPacket;

}  // namespace v786

namespace v800 {

using MoveActorDeltaData = base::MoveActorDeltaData;

using MovePlayerPacket = base::MovePlayerPacket;

using MoveActorDeltaPacket = base::MoveActorDeltaPacket;

struct ActorDataFlagComponent {
    std::bitset<124> value{};
};

using ActorDataBoundingBoxComponent = v776::ActorDataBoundingBoxComponent;

struct ClientMovementPredictionSyncPacket {
    static constexpr int Id = 322;
    v800::ActorDataFlagComponent actor_data_flag{};
    v776::ActorDataBoundingBoxComponent actor_bounding_box{};
    std::array<float, 6> movement_attributes{};
    ActorUniqueID actor_id{};
    bool is_flying{};
};

using CorrectPlayerMovePredictionPacket = base::CorrectPlayerMovePredictionPacket;

using SetMovementAuthorityPacket = v748::SetMovementAuthorityPacket;

}  // namespace v800

namespace v818 {

using MoveActorDeltaData = base::MoveActorDeltaData;

using MovePlayerPacket = base::MovePlayerPacket;

using MoveActorDeltaPacket = base::MoveActorDeltaPacket;

struct ActorDataFlagComponent {
    std::bitset<125> value{};
};

using ActorDataBoundingBoxComponent = v776::ActorDataBoundingBoxComponent;

struct ClientMovementPredictionSyncPacket {
    static constexpr int Id = 322;
    v818::ActorDataFlagComponent actor_data_flag{};
    v776::ActorDataBoundingBoxComponent actor_bounding_box{};
    std::array<float, 6> movement_attributes{};
    ActorUniqueID actor_id{};
    bool is_flying{};
};

using CorrectPlayerMovePredictionPacket = base::CorrectPlayerMovePredictionPacket;

}  // namespace v818

namespace v827 {

using MoveActorDeltaData = base::MoveActorDeltaData;

using MovePlayerPacket = base::MovePlayerPacket;

using MoveActorDeltaPacket = base::MoveActorDeltaPacket;

using ActorDataFlagComponent = v818::ActorDataFlagComponent;

using ActorDataBoundingBoxComponent = v776::ActorDataBoundingBoxComponent;

using ClientMovementPredictionSyncPacket = v818::ClientMovementPredictionSyncPacket;

struct CorrectPlayerMovePredictionPacket {
    static constexpr int Id = 161;
    RewindType prediction_type{};
    Vec3 pos{};
    Vec3 pos_delta{};
    Vec2 vehicle_rotation{};
    std::optional<float> vehicle_angular_velocity{};
    bool on_ground{};
    PlayerInputTick tick{};
};

}  // namespace v827

namespace v844 {

using MoveActorDeltaData = base::MoveActorDeltaData;

using MovePlayerPacket = base::MovePlayerPacket;

using MoveActorDeltaPacket = base::MoveActorDeltaPacket;

struct ActorDataFlagComponent {
    std::bitset<126> value{};
};

using ActorDataBoundingBoxComponent = v776::ActorDataBoundingBoxComponent;

struct ClientMovementPredictionSyncPacket {
    static constexpr int Id = 322;
    v844::ActorDataFlagComponent actor_data_flag{};
    v776::ActorDataBoundingBoxComponent actor_bounding_box{};
    std::array<float, 6> movement_attributes{};
    ActorUniqueID actor_id{};
    bool is_flying{};
};

using CorrectPlayerMovePredictionPacket = v827::CorrectPlayerMovePredictionPacket;

}  // namespace v844

namespace v859 {

using MoveActorDeltaData = base::MoveActorDeltaData;

using MovePlayerPacket = base::MovePlayerPacket;

using MoveActorDeltaPacket = base::MoveActorDeltaPacket;

using ActorDataFlagComponent = v844::ActorDataFlagComponent;

using ActorDataBoundingBoxComponent = v776::ActorDataBoundingBoxComponent;

using ClientMovementPredictionSyncPacket = v844::ClientMovementPredictionSyncPacket;

using CorrectPlayerMovePredictionPacket = v827::CorrectPlayerMovePredictionPacket;

}  // namespace v859

namespace v898 {

using MoveActorDeltaData = base::MoveActorDeltaData;

using MovePlayerPacket = base::MovePlayerPacket;

using MoveActorDeltaPacket = base::MoveActorDeltaPacket;

struct ActorDataFlagComponent {
    std::bitset<127> value{};
};

using ActorDataBoundingBoxComponent = v776::ActorDataBoundingBoxComponent;

struct ClientMovementPredictionSyncPacket {
    static constexpr int Id = 322;
    v898::ActorDataFlagComponent actor_data_flag{};
    v776::ActorDataBoundingBoxComponent actor_bounding_box{};
    std::array<float, 6> movement_attributes{};
    ActorUniqueID actor_id{};
    bool is_flying{};
};

using CorrectPlayerMovePredictionPacket = v827::CorrectPlayerMovePredictionPacket;

}  // namespace v898

namespace v924 {

using MoveActorDeltaData = base::MoveActorDeltaData;

using MovePlayerPacket = base::MovePlayerPacket;

using MoveActorDeltaPacket = base::MoveActorDeltaPacket;

using ActorDataFlagComponent = v898::ActorDataFlagComponent;

using ActorDataBoundingBoxComponent = v776::ActorDataBoundingBoxComponent;

using ClientMovementPredictionSyncPacket = v898::ClientMovementPredictionSyncPacket;

using CorrectPlayerMovePredictionPacket = v827::CorrectPlayerMovePredictionPacket;

}  // namespace v924

namespace v975 {

using MoveActorDeltaData = base::MoveActorDeltaData;

using MovePlayerPacket = base::MovePlayerPacket;

using MoveActorDeltaPacket = base::MoveActorDeltaPacket;

struct ActorDataFlagComponent {
    std::bitset<130> value{};
};

using ActorDataBoundingBoxComponent = v776::ActorDataBoundingBoxComponent;

struct ClientMovementPredictionSyncPacket {
    static constexpr int Id = 322;
    v975::ActorDataFlagComponent actor_data_flag{};
    v776::ActorDataBoundingBoxComponent actor_bounding_box{};
    std::array<float, 9> movement_attributes{};
    ActorUniqueID actor_id{};
    bool is_flying{};
};

using CorrectPlayerMovePredictionPacket = v827::CorrectPlayerMovePredictionPacket;

}  // namespace v975

namespace v2168 {

struct MovePlayerTeleportData {
    std::int32_t cause{};
    std::int32_t source_entity_type{};
};

struct MoveActorDeltaData {
    ActorRuntimeID runtime_id{};
    std::optional<float> new_position_x{};
    std::optional<float> new_position_y{};
    std::optional<float> new_position_z{};
    std::optional<std::int8_t> rot_x{};
    std::optional<std::int8_t> rot_y{};
    std::optional<std::int8_t> rot_y_head{};
    bool is_on_ground{};
    bool force_move{};
    bool force_move_local_entity{};
    bool force_completion{};
};

struct MovePlayerPacket {
    static constexpr int Id = 19;
    ActorRuntimeID player_id{};
    Vec3 pos{};
    Vec2 rot{};
    float y_head_rot{};
    PlayerPositionModeComponent::PositionMode reset_position{};
    bool on_ground{};
    ActorRuntimeID riding_id{};
    std::optional<v2168::MovePlayerTeleportData> teleport_data{};
    PlayerInputTick tick{};
};

struct MoveActorDeltaPacket {
    static constexpr int Id = 111;
    v2168::MoveActorDeltaData move_data{};
};

struct ActorDataFlagComponent {
    std::bitset<131> value{};
};

using ActorDataBoundingBoxComponent = v776::ActorDataBoundingBoxComponent;

struct ClientMovementPredictionSyncPacket {
    static constexpr int Id = 322;
    v2168::ActorDataFlagComponent actor_data_flag{};
    v776::ActorDataBoundingBoxComponent actor_bounding_box{};
    std::array<float, 9> movement_attributes{};
    ActorUniqueID actor_id{};
    bool is_flying{};
};

using CorrectPlayerMovePredictionPacket = v827::CorrectPlayerMovePredictionPacket;

}  // namespace v2168

namespace v2193 {

using MovePlayerTeleportData = v2168::MovePlayerTeleportData;

struct MoveActorDeltaData {
    ActorRuntimeID runtime_id{};
    std::optional<float> new_position_x{};
    std::optional<float> new_position_y{};
    std::optional<float> new_position_z{};
    std::optional<std::int8_t> rot_x{};
    std::optional<std::int8_t> rot_y{};
    std::optional<std::int8_t> rot_y_head{};
    bool is_on_ground{};
    bool force_move{};
    bool force_move_local_entity{};
    bool force_completion{};
    std::uint64_t ticks{};
};

using MovePlayerPacket = v2168::MovePlayerPacket;

struct MoveActorDeltaPacket {
    static constexpr int Id = 111;
    v2193::MoveActorDeltaData move_data{};
};

using ActorDataFlagComponent = v2168::ActorDataFlagComponent;

using ActorDataBoundingBoxComponent = v776::ActorDataBoundingBoxComponent;

using ClientMovementPredictionSyncPacket = v2168::ClientMovementPredictionSyncPacket;

using CorrectPlayerMovePredictionPacket = v827::CorrectPlayerMovePredictionPacket;

}  // namespace v2193

namespace v2225 {

using MovePlayerTeleportData = v2168::MovePlayerTeleportData;

using MoveActorDeltaData = v2193::MoveActorDeltaData;

using MovePlayerPacket = v2168::MovePlayerPacket;

using MoveActorDeltaPacket = v2193::MoveActorDeltaPacket;

using ActorDataFlagComponent = v2168::ActorDataFlagComponent;

using ActorDataBoundingBoxComponent = v776::ActorDataBoundingBoxComponent;

using ClientMovementPredictionSyncPacket = v2168::ClientMovementPredictionSyncPacket;

using CorrectPlayerMovePredictionPacket = v827::CorrectPlayerMovePredictionPacket;

}  // namespace v2225

namespace detail {

template <int V>
struct MovePlayerTeleportData_;

template <int V> requires (V >= 2168)
struct MovePlayerTeleportData_<V> { using type = v2168::MovePlayerTeleportData; };

template <int V>
struct MoveActorDeltaData_;

template <int V> requires (V < 2168)
struct MoveActorDeltaData_<V> { using type = base::MoveActorDeltaData; };

template <int V> requires (V >= 2168 && V < 2193)
struct MoveActorDeltaData_<V> { using type = v2168::MoveActorDeltaData; };

template <int V> requires (V >= 2193)
struct MoveActorDeltaData_<V> { using type = v2193::MoveActorDeltaData; };

template <int V>
struct MovePlayerPacket_;

template <int V> requires (V < 2168)
struct MovePlayerPacket_<V> { using type = base::MovePlayerPacket; };

template <int V> requires (V >= 2168)
struct MovePlayerPacket_<V> { using type = v2168::MovePlayerPacket; };

template <int V>
struct MoveActorDeltaPacket_;

template <int V> requires (V < 2168)
struct MoveActorDeltaPacket_<V> { using type = base::MoveActorDeltaPacket; };

template <int V> requires (V >= 2168 && V < 2193)
struct MoveActorDeltaPacket_<V> { using type = v2168::MoveActorDeltaPacket; };

template <int V> requires (V >= 2193)
struct MoveActorDeltaPacket_<V> { using type = v2193::MoveActorDeltaPacket; };

template <int V>
struct ActorDataFlagComponent_;

template <int V> requires (V >= 776 && V < 786)
struct ActorDataFlagComponent_<V> { using type = v776::ActorDataFlagComponent; };

template <int V> requires (V >= 786 && V < 800)
struct ActorDataFlagComponent_<V> { using type = v786::ActorDataFlagComponent; };

template <int V> requires (V >= 800 && V < 818)
struct ActorDataFlagComponent_<V> { using type = v800::ActorDataFlagComponent; };

template <int V> requires (V >= 818 && V < 844)
struct ActorDataFlagComponent_<V> { using type = v818::ActorDataFlagComponent; };

template <int V> requires (V >= 844 && V < 898)
struct ActorDataFlagComponent_<V> { using type = v844::ActorDataFlagComponent; };

template <int V> requires (V >= 898 && V < 975)
struct ActorDataFlagComponent_<V> { using type = v898::ActorDataFlagComponent; };

template <int V> requires (V >= 975 && V < 2168)
struct ActorDataFlagComponent_<V> { using type = v975::ActorDataFlagComponent; };

template <int V> requires (V >= 2168)
struct ActorDataFlagComponent_<V> { using type = v2168::ActorDataFlagComponent; };

template <int V>
struct ActorDataBoundingBoxComponent_;

template <int V> requires (V >= 776)
struct ActorDataBoundingBoxComponent_<V> { using type = v776::ActorDataBoundingBoxComponent; };

template <int V>
struct ClientMovementPredictionSyncPacket_;

template <int V> requires (V >= 776 && V < 786)
struct ClientMovementPredictionSyncPacket_<V> { using type = v776::ClientMovementPredictionSyncPacket; };

template <int V> requires (V >= 786 && V < 800)
struct ClientMovementPredictionSyncPacket_<V> { using type = v786::ClientMovementPredictionSyncPacket; };

template <int V> requires (V >= 800 && V < 818)
struct ClientMovementPredictionSyncPacket_<V> { using type = v800::ClientMovementPredictionSyncPacket; };

template <int V> requires (V >= 818 && V < 844)
struct ClientMovementPredictionSyncPacket_<V> { using type = v818::ClientMovementPredictionSyncPacket; };

template <int V> requires (V >= 844 && V < 898)
struct ClientMovementPredictionSyncPacket_<V> { using type = v844::ClientMovementPredictionSyncPacket; };

template <int V> requires (V >= 898 && V < 975)
struct ClientMovementPredictionSyncPacket_<V> { using type = v898::ClientMovementPredictionSyncPacket; };

template <int V> requires (V >= 975 && V < 2168)
struct ClientMovementPredictionSyncPacket_<V> { using type = v975::ClientMovementPredictionSyncPacket; };

template <int V> requires (V >= 2168)
struct ClientMovementPredictionSyncPacket_<V> { using type = v2168::ClientMovementPredictionSyncPacket; };

template <int V>
struct CorrectPlayerMovePredictionPacket_;

template <int V> requires (V < 827)
struct CorrectPlayerMovePredictionPacket_<V> { using type = base::CorrectPlayerMovePredictionPacket; };

template <int V> requires (V >= 827)
struct CorrectPlayerMovePredictionPacket_<V> { using type = v827::CorrectPlayerMovePredictionPacket; };

template <int V>
struct SetMovementAuthorityPacket_;

template <int V> requires (V >= 748 && V < 818)
struct SetMovementAuthorityPacket_<V> { using type = v748::SetMovementAuthorityPacket; };

}  // namespace detail

template <int V> using MovePlayerTeleportData_ = typename detail::MovePlayerTeleportData_<V>::type;
template <int V> using MoveActorDeltaData_ = typename detail::MoveActorDeltaData_<V>::type;
template <int V> using MovePlayerPacket_ = typename detail::MovePlayerPacket_<V>::type;
template <int V> using MoveActorDeltaPacket_ = typename detail::MoveActorDeltaPacket_<V>::type;
template <int V> using ActorDataFlagComponent_ = typename detail::ActorDataFlagComponent_<V>::type;
template <int V> using ActorDataBoundingBoxComponent_ = typename detail::ActorDataBoundingBoxComponent_<V>::type;
template <int V> using ClientMovementPredictionSyncPacket_ = typename detail::ClientMovementPredictionSyncPacket_<V>::type;
template <int V> using CorrectPlayerMovePredictionPacket_ = typename detail::CorrectPlayerMovePredictionPacket_<V>::type;
template <int V> using SetMovementAuthorityPacket_ = typename detail::SetMovementAuthorityPacket_<V>::type;

template <int V>
struct packet_of<V, 16> { using type = ServerPlayerPostMovePositionPacket; };

template <int V>
struct packet_of<V, 19> { using type = MovePlayerPacket_<V>; };

template <int V>
struct packet_of<V, 111> { using type = MoveActorDeltaPacket_<V>; };

template <int V>
struct packet_of<V, 161> { using type = CorrectPlayerMovePredictionPacket_<V>; };

template <int V> requires (V >= 748 && V < 818)
struct packet_of<V, 319> { using type = SetMovementAuthorityPacket_<V>; };

template <int V> requires (V >= 776)
struct packet_of<V, 322> { using type = ClientMovementPredictionSyncPacket_<V>; };

namespace detail {

template <>
inline constexpr std::array<PlayerPositionModeComponent::PositionMode, 4> values_v<PlayerPositionModeComponent::PositionMode>{{
    PlayerPositionModeComponent::PositionMode::Normal,
    PlayerPositionModeComponent::PositionMode::Respawn,
    PlayerPositionModeComponent::PositionMode::Teleport,
    PlayerPositionModeComponent::PositionMode::OnlyHeadRot,
}};

template <>
inline constexpr std::array<std::string_view, 4> names_v<PlayerPositionModeComponent::PositionMode>{{
    "normal",
    "respawn",
    "teleport",
    "onlyheadrot",
}};

template <>
inline constexpr std::string_view type_name_v<PlayerPositionModeComponent::PositionMode>{"PlayerPositionModeComponent::PositionMode"};

template <>
inline constexpr std::array<RewindType, 2> values_v<RewindType>{{
    RewindType::Player,
    RewindType::Vehicle,
}};

template <>
inline constexpr std::array<std::string_view, 2> names_v<RewindType>{{
    "player",
    "vehicle",
}};

template <>
inline constexpr std::string_view type_name_v<RewindType>{"RewindType"};

template <>
inline constexpr std::array<ServerAuthMovementMode, 3> values_v<ServerAuthMovementMode>{{
    ServerAuthMovementMode::LegacyClientAuthoritativeV1Deprecated,
    ServerAuthMovementMode::ClientAuthoritativeV2,
    ServerAuthMovementMode::ServerAuthoritativeV3,
}};

template <>
inline constexpr std::array<std::string_view, 3> names_v<ServerAuthMovementMode>{{
    "legacyclientauthoritativev1deprecated",
    "clientauthoritativev2",
    "serverauthoritativev3",
}};

template <>
inline constexpr std::string_view type_name_v<ServerAuthMovementMode>{"ServerAuthMovementMode"};

}  // namespace detail

namespace detail {

template <>
inline constexpr bool is_reflected_struct_v<PlayerPositionModeComponent> = true;

template <>
inline constexpr std::string_view struct_name_v<PlayerPositionModeComponent>{"PlayerPositionModeComponent"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<PlayerPositionModeComponent>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<v2168::MovePlayerTeleportData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::MovePlayerTeleportData>{"MovePlayerTeleportData"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v2168::MovePlayerTeleportData>{{
    "cause",
    "source_entity_type",
}};

template <>
struct field_accessor<v2168::MovePlayerTeleportData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.cause;
        }
        else {
            return value.source_entity_type;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::MoveActorDeltaData> = true;

template <>
inline constexpr std::string_view struct_name_v<base::MoveActorDeltaData>{"MoveActorDeltaData"};

template <>
inline constexpr std::array<std::string_view, 8> field_names_v<base::MoveActorDeltaData>{{
    "runtime_id",
    "header",
    "new_position_x",
    "new_position_y",
    "new_position_z",
    "rot_x",
    "rot_y",
    "rot_y_head",
}};

template <>
struct field_accessor<base::MoveActorDeltaData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.runtime_id;
        }
        else if constexpr (I == 1) {
            return value.header;
        }
        else if constexpr (I == 2) {
            return value.new_position_x;
        }
        else if constexpr (I == 3) {
            return value.new_position_y;
        }
        else if constexpr (I == 4) {
            return value.new_position_z;
        }
        else if constexpr (I == 5) {
            return value.rot_x;
        }
        else if constexpr (I == 6) {
            return value.rot_y;
        }
        else {
            return value.rot_y_head;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::MoveActorDeltaData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::MoveActorDeltaData>{"MoveActorDeltaData"};

template <>
inline constexpr std::array<std::string_view, 11> field_names_v<v2168::MoveActorDeltaData>{{
    "runtime_id",
    "new_position_x",
    "new_position_y",
    "new_position_z",
    "rot_x",
    "rot_y",
    "rot_y_head",
    "is_on_ground",
    "force_move",
    "force_move_local_entity",
    "force_completion",
}};

template <>
struct field_accessor<v2168::MoveActorDeltaData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.runtime_id;
        }
        else if constexpr (I == 1) {
            return value.new_position_x;
        }
        else if constexpr (I == 2) {
            return value.new_position_y;
        }
        else if constexpr (I == 3) {
            return value.new_position_z;
        }
        else if constexpr (I == 4) {
            return value.rot_x;
        }
        else if constexpr (I == 5) {
            return value.rot_y;
        }
        else if constexpr (I == 6) {
            return value.rot_y_head;
        }
        else if constexpr (I == 7) {
            return value.is_on_ground;
        }
        else if constexpr (I == 8) {
            return value.force_move;
        }
        else if constexpr (I == 9) {
            return value.force_move_local_entity;
        }
        else {
            return value.force_completion;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2193::MoveActorDeltaData> = true;

template <>
inline constexpr std::string_view struct_name_v<v2193::MoveActorDeltaData>{"MoveActorDeltaData"};

template <>
inline constexpr std::array<std::string_view, 12> field_names_v<v2193::MoveActorDeltaData>{{
    "runtime_id",
    "new_position_x",
    "new_position_y",
    "new_position_z",
    "rot_x",
    "rot_y",
    "rot_y_head",
    "is_on_ground",
    "force_move",
    "force_move_local_entity",
    "force_completion",
    "ticks",
}};

template <>
struct field_accessor<v2193::MoveActorDeltaData> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.runtime_id;
        }
        else if constexpr (I == 1) {
            return value.new_position_x;
        }
        else if constexpr (I == 2) {
            return value.new_position_y;
        }
        else if constexpr (I == 3) {
            return value.new_position_z;
        }
        else if constexpr (I == 4) {
            return value.rot_x;
        }
        else if constexpr (I == 5) {
            return value.rot_y;
        }
        else if constexpr (I == 6) {
            return value.rot_y_head;
        }
        else if constexpr (I == 7) {
            return value.is_on_ground;
        }
        else if constexpr (I == 8) {
            return value.force_move;
        }
        else if constexpr (I == 9) {
            return value.force_move_local_entity;
        }
        else if constexpr (I == 10) {
            return value.force_completion;
        }
        else {
            return value.ticks;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::MovePlayerPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::MovePlayerPacket>{"MovePlayerPacket"};

template <>
inline constexpr std::array<std::string_view, 10> field_names_v<base::MovePlayerPacket>{{
    "player_id",
    "pos",
    "rot",
    "y_head_rot",
    "reset_position",
    "on_ground",
    "riding_id",
    "cause",
    "source_entity_type",
    "tick",
}};

template <>
struct field_accessor<base::MovePlayerPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.player_id;
        }
        else if constexpr (I == 1) {
            return value.pos;
        }
        else if constexpr (I == 2) {
            return value.rot;
        }
        else if constexpr (I == 3) {
            return value.y_head_rot;
        }
        else if constexpr (I == 4) {
            return value.reset_position;
        }
        else if constexpr (I == 5) {
            return value.on_ground;
        }
        else if constexpr (I == 6) {
            return value.riding_id;
        }
        else if constexpr (I == 7) {
            return value.cause;
        }
        else if constexpr (I == 8) {
            return value.source_entity_type;
        }
        else {
            return value.tick;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::MovePlayerPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::MovePlayerPacket>{"MovePlayerPacket"};

template <>
inline constexpr std::array<std::string_view, 9> field_names_v<v2168::MovePlayerPacket>{{
    "player_id",
    "pos",
    "rot",
    "y_head_rot",
    "reset_position",
    "on_ground",
    "riding_id",
    "teleport_data",
    "tick",
}};

template <>
struct field_accessor<v2168::MovePlayerPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.player_id;
        }
        else if constexpr (I == 1) {
            return value.pos;
        }
        else if constexpr (I == 2) {
            return value.rot;
        }
        else if constexpr (I == 3) {
            return value.y_head_rot;
        }
        else if constexpr (I == 4) {
            return value.reset_position;
        }
        else if constexpr (I == 5) {
            return value.on_ground;
        }
        else if constexpr (I == 6) {
            return value.riding_id;
        }
        else if constexpr (I == 7) {
            return value.teleport_data;
        }
        else {
            return value.tick;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::MoveActorDeltaPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::MoveActorDeltaPacket>{"MoveActorDeltaPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<base::MoveActorDeltaPacket>{{
    "move_data",
}};

template <>
struct field_accessor<base::MoveActorDeltaPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.move_data;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::MoveActorDeltaPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::MoveActorDeltaPacket>{"MoveActorDeltaPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2168::MoveActorDeltaPacket>{{
    "move_data",
}};

template <>
struct field_accessor<v2168::MoveActorDeltaPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.move_data;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2193::MoveActorDeltaPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2193::MoveActorDeltaPacket>{"MoveActorDeltaPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2193::MoveActorDeltaPacket>{{
    "move_data",
}};

template <>
struct field_accessor<v2193::MoveActorDeltaPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.move_data;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<ServerPlayerPostMovePositionPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<ServerPlayerPostMovePositionPacket>{"ServerPlayerPostMovePositionPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<ServerPlayerPostMovePositionPacket>{{
    "pos",
}};

template <>
struct field_accessor<ServerPlayerPostMovePositionPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.pos;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v776::ActorDataFlagComponent> = true;

template <>
inline constexpr std::string_view struct_name_v<v776::ActorDataFlagComponent>{"ActorDataFlagComponent"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v776::ActorDataFlagComponent>{{
    "value",
}};

template <>
struct field_accessor<v776::ActorDataFlagComponent> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.value;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v786::ActorDataFlagComponent> = true;

template <>
inline constexpr std::string_view struct_name_v<v786::ActorDataFlagComponent>{"ActorDataFlagComponent"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v786::ActorDataFlagComponent>{{
    "value",
}};

template <>
struct field_accessor<v786::ActorDataFlagComponent> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.value;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v800::ActorDataFlagComponent> = true;

template <>
inline constexpr std::string_view struct_name_v<v800::ActorDataFlagComponent>{"ActorDataFlagComponent"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v800::ActorDataFlagComponent>{{
    "value",
}};

template <>
struct field_accessor<v800::ActorDataFlagComponent> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.value;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v818::ActorDataFlagComponent> = true;

template <>
inline constexpr std::string_view struct_name_v<v818::ActorDataFlagComponent>{"ActorDataFlagComponent"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v818::ActorDataFlagComponent>{{
    "value",
}};

template <>
struct field_accessor<v818::ActorDataFlagComponent> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.value;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v844::ActorDataFlagComponent> = true;

template <>
inline constexpr std::string_view struct_name_v<v844::ActorDataFlagComponent>{"ActorDataFlagComponent"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v844::ActorDataFlagComponent>{{
    "value",
}};

template <>
struct field_accessor<v844::ActorDataFlagComponent> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.value;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v898::ActorDataFlagComponent> = true;

template <>
inline constexpr std::string_view struct_name_v<v898::ActorDataFlagComponent>{"ActorDataFlagComponent"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v898::ActorDataFlagComponent>{{
    "value",
}};

template <>
struct field_accessor<v898::ActorDataFlagComponent> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.value;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v975::ActorDataFlagComponent> = true;

template <>
inline constexpr std::string_view struct_name_v<v975::ActorDataFlagComponent>{"ActorDataFlagComponent"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v975::ActorDataFlagComponent>{{
    "value",
}};

template <>
struct field_accessor<v975::ActorDataFlagComponent> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.value;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ActorDataFlagComponent> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ActorDataFlagComponent>{"ActorDataFlagComponent"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v2168::ActorDataFlagComponent>{{
    "value",
}};

template <>
struct field_accessor<v2168::ActorDataFlagComponent> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.value;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v776::ActorDataBoundingBoxComponent> = true;

template <>
inline constexpr std::string_view struct_name_v<v776::ActorDataBoundingBoxComponent>{"ActorDataBoundingBoxComponent"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v776::ActorDataBoundingBoxComponent>{{
    "value",
}};

template <>
struct field_accessor<v776::ActorDataBoundingBoxComponent> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.value;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v776::ClientMovementPredictionSyncPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v776::ClientMovementPredictionSyncPacket>{"ClientMovementPredictionSyncPacket"};

template <>
inline constexpr std::array<std::string_view, 4> field_names_v<v776::ClientMovementPredictionSyncPacket>{{
    "actor_data_flag",
    "actor_bounding_box",
    "movement_attributes",
    "actor_id",
}};

template <>
struct field_accessor<v776::ClientMovementPredictionSyncPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.actor_data_flag;
        }
        else if constexpr (I == 1) {
            return value.actor_bounding_box;
        }
        else if constexpr (I == 2) {
            return value.movement_attributes;
        }
        else {
            return value.actor_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v786::ClientMovementPredictionSyncPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v786::ClientMovementPredictionSyncPacket>{"ClientMovementPredictionSyncPacket"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v786::ClientMovementPredictionSyncPacket>{{
    "actor_data_flag",
    "actor_bounding_box",
    "movement_attributes",
    "actor_id",
    "is_flying",
}};

template <>
struct field_accessor<v786::ClientMovementPredictionSyncPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.actor_data_flag;
        }
        else if constexpr (I == 1) {
            return value.actor_bounding_box;
        }
        else if constexpr (I == 2) {
            return value.movement_attributes;
        }
        else if constexpr (I == 3) {
            return value.actor_id;
        }
        else {
            return value.is_flying;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v800::ClientMovementPredictionSyncPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v800::ClientMovementPredictionSyncPacket>{"ClientMovementPredictionSyncPacket"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v800::ClientMovementPredictionSyncPacket>{{
    "actor_data_flag",
    "actor_bounding_box",
    "movement_attributes",
    "actor_id",
    "is_flying",
}};

template <>
struct field_accessor<v800::ClientMovementPredictionSyncPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.actor_data_flag;
        }
        else if constexpr (I == 1) {
            return value.actor_bounding_box;
        }
        else if constexpr (I == 2) {
            return value.movement_attributes;
        }
        else if constexpr (I == 3) {
            return value.actor_id;
        }
        else {
            return value.is_flying;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v818::ClientMovementPredictionSyncPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v818::ClientMovementPredictionSyncPacket>{"ClientMovementPredictionSyncPacket"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v818::ClientMovementPredictionSyncPacket>{{
    "actor_data_flag",
    "actor_bounding_box",
    "movement_attributes",
    "actor_id",
    "is_flying",
}};

template <>
struct field_accessor<v818::ClientMovementPredictionSyncPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.actor_data_flag;
        }
        else if constexpr (I == 1) {
            return value.actor_bounding_box;
        }
        else if constexpr (I == 2) {
            return value.movement_attributes;
        }
        else if constexpr (I == 3) {
            return value.actor_id;
        }
        else {
            return value.is_flying;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v844::ClientMovementPredictionSyncPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v844::ClientMovementPredictionSyncPacket>{"ClientMovementPredictionSyncPacket"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v844::ClientMovementPredictionSyncPacket>{{
    "actor_data_flag",
    "actor_bounding_box",
    "movement_attributes",
    "actor_id",
    "is_flying",
}};

template <>
struct field_accessor<v844::ClientMovementPredictionSyncPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.actor_data_flag;
        }
        else if constexpr (I == 1) {
            return value.actor_bounding_box;
        }
        else if constexpr (I == 2) {
            return value.movement_attributes;
        }
        else if constexpr (I == 3) {
            return value.actor_id;
        }
        else {
            return value.is_flying;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v898::ClientMovementPredictionSyncPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v898::ClientMovementPredictionSyncPacket>{"ClientMovementPredictionSyncPacket"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v898::ClientMovementPredictionSyncPacket>{{
    "actor_data_flag",
    "actor_bounding_box",
    "movement_attributes",
    "actor_id",
    "is_flying",
}};

template <>
struct field_accessor<v898::ClientMovementPredictionSyncPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.actor_data_flag;
        }
        else if constexpr (I == 1) {
            return value.actor_bounding_box;
        }
        else if constexpr (I == 2) {
            return value.movement_attributes;
        }
        else if constexpr (I == 3) {
            return value.actor_id;
        }
        else {
            return value.is_flying;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v975::ClientMovementPredictionSyncPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v975::ClientMovementPredictionSyncPacket>{"ClientMovementPredictionSyncPacket"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v975::ClientMovementPredictionSyncPacket>{{
    "actor_data_flag",
    "actor_bounding_box",
    "movement_attributes",
    "actor_id",
    "is_flying",
}};

template <>
struct field_accessor<v975::ClientMovementPredictionSyncPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.actor_data_flag;
        }
        else if constexpr (I == 1) {
            return value.actor_bounding_box;
        }
        else if constexpr (I == 2) {
            return value.movement_attributes;
        }
        else if constexpr (I == 3) {
            return value.actor_id;
        }
        else {
            return value.is_flying;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v2168::ClientMovementPredictionSyncPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v2168::ClientMovementPredictionSyncPacket>{"ClientMovementPredictionSyncPacket"};

template <>
inline constexpr std::array<std::string_view, 5> field_names_v<v2168::ClientMovementPredictionSyncPacket>{{
    "actor_data_flag",
    "actor_bounding_box",
    "movement_attributes",
    "actor_id",
    "is_flying",
}};

template <>
struct field_accessor<v2168::ClientMovementPredictionSyncPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.actor_data_flag;
        }
        else if constexpr (I == 1) {
            return value.actor_bounding_box;
        }
        else if constexpr (I == 2) {
            return value.movement_attributes;
        }
        else if constexpr (I == 3) {
            return value.actor_id;
        }
        else {
            return value.is_flying;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::CorrectPlayerMovePredictionPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::CorrectPlayerMovePredictionPacket>{"CorrectPlayerMovePredictionPacket"};

template <>
inline constexpr std::array<std::string_view, 7> field_names_v<base::CorrectPlayerMovePredictionPacket>{{
    "prediction_type",
    "pos",
    "pos_delta",
    "vehicle_rotation",
    "vehicle_angular_velocity",
    "on_ground",
    "tick",
}};

template <>
struct field_accessor<base::CorrectPlayerMovePredictionPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.prediction_type;
        }
        else if constexpr (I == 1) {
            return value.pos;
        }
        else if constexpr (I == 2) {
            return value.pos_delta;
        }
        else if constexpr (I == 3) {
            return value.vehicle_rotation;
        }
        else if constexpr (I == 4) {
            return value.vehicle_angular_velocity;
        }
        else if constexpr (I == 5) {
            return value.on_ground;
        }
        else {
            return value.tick;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v827::CorrectPlayerMovePredictionPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v827::CorrectPlayerMovePredictionPacket>{"CorrectPlayerMovePredictionPacket"};

template <>
inline constexpr std::array<std::string_view, 7> field_names_v<v827::CorrectPlayerMovePredictionPacket>{{
    "prediction_type",
    "pos",
    "pos_delta",
    "vehicle_rotation",
    "vehicle_angular_velocity",
    "on_ground",
    "tick",
}};

template <>
struct field_accessor<v827::CorrectPlayerMovePredictionPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.prediction_type;
        }
        else if constexpr (I == 1) {
            return value.pos;
        }
        else if constexpr (I == 2) {
            return value.pos_delta;
        }
        else if constexpr (I == 3) {
            return value.vehicle_rotation;
        }
        else if constexpr (I == 4) {
            return value.vehicle_angular_velocity;
        }
        else if constexpr (I == 5) {
            return value.on_ground;
        }
        else {
            return value.tick;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v748::SetMovementAuthorityPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v748::SetMovementAuthorityPacket>{"SetMovementAuthorityPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v748::SetMovementAuthorityPacket>{{
    "new_auth_movement_mode",
}};

template <>
struct field_accessor<v748::SetMovementAuthorityPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.new_auth_movement_mode;
    }
};

}  // namespace detail


template <>
struct Serializer<v2168::MovePlayerTeleportData> {
    static void serialize(BinaryWriter &stream, const v2168::MovePlayerTeleportData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::MovePlayerTeleportData, std::error_code>;
};

template <>
struct Serializer<base::MoveActorDeltaData> {
    static void serialize(BinaryWriter &stream, const base::MoveActorDeltaData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::MoveActorDeltaData, std::error_code>;
};

template <>
struct Serializer<v2168::MoveActorDeltaData> {
    static void serialize(BinaryWriter &stream, const v2168::MoveActorDeltaData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::MoveActorDeltaData, std::error_code>;
};

template <>
struct Serializer<v2193::MoveActorDeltaData> {
    static void serialize(BinaryWriter &stream, const v2193::MoveActorDeltaData &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::MoveActorDeltaData, std::error_code>;
};

template <>
struct Serializer<base::MovePlayerPacket> {
    static void serialize(BinaryWriter &stream, const base::MovePlayerPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::MovePlayerPacket, std::error_code>;
};

template <>
struct Serializer<v2168::MovePlayerPacket> {
    static void serialize(BinaryWriter &stream, const v2168::MovePlayerPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::MovePlayerPacket, std::error_code>;
};

template <>
struct Serializer<base::MoveActorDeltaPacket> {
    static void serialize(BinaryWriter &stream, const base::MoveActorDeltaPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::MoveActorDeltaPacket, std::error_code>;
};

template <>
struct Serializer<v2168::MoveActorDeltaPacket> {
    static void serialize(BinaryWriter &stream, const v2168::MoveActorDeltaPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::MoveActorDeltaPacket, std::error_code>;
};

template <>
struct Serializer<v2193::MoveActorDeltaPacket> {
    static void serialize(BinaryWriter &stream, const v2193::MoveActorDeltaPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2193::MoveActorDeltaPacket, std::error_code>;
};

template <>
struct Serializer<ServerPlayerPostMovePositionPacket> {
    static void serialize(BinaryWriter &stream, const ServerPlayerPostMovePositionPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<ServerPlayerPostMovePositionPacket, std::error_code>;
};

template <>
struct Serializer<v776::ActorDataFlagComponent> {
    static void serialize(BinaryWriter &stream, const v776::ActorDataFlagComponent &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v776::ActorDataFlagComponent, std::error_code>;
};

template <>
struct Serializer<v786::ActorDataFlagComponent> {
    static void serialize(BinaryWriter &stream, const v786::ActorDataFlagComponent &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v786::ActorDataFlagComponent, std::error_code>;
};

template <>
struct Serializer<v800::ActorDataFlagComponent> {
    static void serialize(BinaryWriter &stream, const v800::ActorDataFlagComponent &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v800::ActorDataFlagComponent, std::error_code>;
};

template <>
struct Serializer<v818::ActorDataFlagComponent> {
    static void serialize(BinaryWriter &stream, const v818::ActorDataFlagComponent &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v818::ActorDataFlagComponent, std::error_code>;
};

template <>
struct Serializer<v844::ActorDataFlagComponent> {
    static void serialize(BinaryWriter &stream, const v844::ActorDataFlagComponent &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v844::ActorDataFlagComponent, std::error_code>;
};

template <>
struct Serializer<v898::ActorDataFlagComponent> {
    static void serialize(BinaryWriter &stream, const v898::ActorDataFlagComponent &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v898::ActorDataFlagComponent, std::error_code>;
};

template <>
struct Serializer<v975::ActorDataFlagComponent> {
    static void serialize(BinaryWriter &stream, const v975::ActorDataFlagComponent &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v975::ActorDataFlagComponent, std::error_code>;
};

template <>
struct Serializer<v2168::ActorDataFlagComponent> {
    static void serialize(BinaryWriter &stream, const v2168::ActorDataFlagComponent &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ActorDataFlagComponent, std::error_code>;
};

template <>
struct Serializer<v776::ActorDataBoundingBoxComponent> {
    static void serialize(BinaryWriter &stream, const v776::ActorDataBoundingBoxComponent &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v776::ActorDataBoundingBoxComponent, std::error_code>;
};

template <>
struct Serializer<v776::ClientMovementPredictionSyncPacket> {
    static void serialize(BinaryWriter &stream, const v776::ClientMovementPredictionSyncPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v776::ClientMovementPredictionSyncPacket, std::error_code>;
};

template <>
struct Serializer<v786::ClientMovementPredictionSyncPacket> {
    static void serialize(BinaryWriter &stream, const v786::ClientMovementPredictionSyncPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v786::ClientMovementPredictionSyncPacket, std::error_code>;
};

template <>
struct Serializer<v800::ClientMovementPredictionSyncPacket> {
    static void serialize(BinaryWriter &stream, const v800::ClientMovementPredictionSyncPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v800::ClientMovementPredictionSyncPacket, std::error_code>;
};

template <>
struct Serializer<v818::ClientMovementPredictionSyncPacket> {
    static void serialize(BinaryWriter &stream, const v818::ClientMovementPredictionSyncPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v818::ClientMovementPredictionSyncPacket, std::error_code>;
};

template <>
struct Serializer<v844::ClientMovementPredictionSyncPacket> {
    static void serialize(BinaryWriter &stream, const v844::ClientMovementPredictionSyncPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v844::ClientMovementPredictionSyncPacket, std::error_code>;
};

template <>
struct Serializer<v898::ClientMovementPredictionSyncPacket> {
    static void serialize(BinaryWriter &stream, const v898::ClientMovementPredictionSyncPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v898::ClientMovementPredictionSyncPacket, std::error_code>;
};

template <>
struct Serializer<v975::ClientMovementPredictionSyncPacket> {
    static void serialize(BinaryWriter &stream, const v975::ClientMovementPredictionSyncPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v975::ClientMovementPredictionSyncPacket, std::error_code>;
};

template <>
struct Serializer<v2168::ClientMovementPredictionSyncPacket> {
    static void serialize(BinaryWriter &stream, const v2168::ClientMovementPredictionSyncPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v2168::ClientMovementPredictionSyncPacket, std::error_code>;
};

template <>
struct Serializer<base::CorrectPlayerMovePredictionPacket> {
    static void serialize(BinaryWriter &stream, const base::CorrectPlayerMovePredictionPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::CorrectPlayerMovePredictionPacket, std::error_code>;
};

template <>
struct Serializer<v827::CorrectPlayerMovePredictionPacket> {
    static void serialize(BinaryWriter &stream, const v827::CorrectPlayerMovePredictionPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v827::CorrectPlayerMovePredictionPacket, std::error_code>;
};

template <>
struct Serializer<v748::SetMovementAuthorityPacket> {
    static void serialize(BinaryWriter &stream, const v748::SetMovementAuthorityPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v748::SetMovementAuthorityPacket, std::error_code>;
};
using MovePlayerTeleportData = MovePlayerTeleportData_<2225>;
using MoveActorDeltaData = MoveActorDeltaData_<2225>;
using MovePlayerPacket = MovePlayerPacket_<2225>;
using MoveActorDeltaPacket = MoveActorDeltaPacket_<2225>;
using ActorDataFlagComponent = ActorDataFlagComponent_<2225>;
using ActorDataBoundingBoxComponent = ActorDataBoundingBoxComponent_<2225>;
using ClientMovementPredictionSyncPacket = ClientMovementPredictionSyncPacket_<2225>;
using CorrectPlayerMovePredictionPacket = CorrectPlayerMovePredictionPacket_<2225>;

}  // namespace bedrock::protocol
