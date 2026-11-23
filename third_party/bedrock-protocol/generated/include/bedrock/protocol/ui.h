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

#include <bedrock/protocol/actor.h>
#include <bedrock/protocol/common.h>

namespace bedrock::protocol {

enum class HudElement : int {
    PaperDoll = 0,
    Armor = 1,
    ToolTips = 2,
    TouchControls = 3,
    Crosshair = 4,
    HotBar = 5,
    Health = 6,
    ProgressBar = 7,
    Hunger = 8,
    AirBubbles = 9,
    HorseHealth = 10,
    StatusEffects = 11,
    ItemText = 12,
    Count = 13,
};

enum class HudVisibility : int {
    Hide = 0,
    Reset = 1,
    Count = 2,
};

enum class ServerboundLoadingScreenPacketType : int {
    Unknown = 0,
    StartLoadingScreen = 1,
    EndLoadingScreen = 2,
};

struct ServerboundLoadingScreenPacket {
    static constexpr int Id = 312;
    ServerboundLoadingScreenPacketType loading_screen_packet_type{};
    std::optional<std::uint32_t> loading_screen_id{};
};

struct WorldPosition {
    Vec3 pos{};
    DimensionType dimension_type{};
};

namespace WaypointGroup_nested {

struct WaypointHandle {
    UUID uuid{};
};

}  // namespace WaypointGroup_nested

struct WaypointGroup {
    using WaypointHandle = WaypointGroup_nested::WaypointHandle;
};

namespace ServerWaypointGroup_nested {

enum class Action : std::uint8_t {
    None = 0,
    Add = 1,
    Remove = 2,
    Update = 3,
};

}  // namespace ServerWaypointGroup_nested

struct ServerWaypointGroup {
    using Action = ServerWaypointGroup_nested::Action;
};

enum class DataDrivenScreenClosedReason : std::uint8_t {
    ProgrammaticClose = 0,
    ProgrammaticCloseAll = 1,
    ClientCanceled = 2,
    UserBusy = 3,
    InvalidForm = 4,
};

struct ModalFormRequestPacket {
    static constexpr int Id = 100;
    std::uint32_t form_id{};
    std::string form_json{};
};

struct ServerSettingsRequestPacket {
    static constexpr int Id = 102;
};

struct ServerSettingsResponsePacket {
    static constexpr int Id = 103;
    std::uint32_t form_id{};
    std::string form_json{};
};

struct ClientboundCloseFormPacket {
    static constexpr int Id = 310;
};

enum class ModalFormCancelReason : std::uint8_t {
    UserClosed = 0,
    UserBusy = 1,
};

struct ModalFormResponsePacket {
    static constexpr int Id = 101;
    std::uint32_t form_id{};
    std::optional<std::string> json_response{};
    std::optional<ModalFormCancelReason> form_cancel_reason{};
};

struct OnScreenTextureAnimationPacket {
    static constexpr int Id = 130;
    std::uint32_t effect_id{};
};

namespace base {

struct SetHudPacket {
    static constexpr int Id = 308;
    std::vector<HudElement> hud_element{};
    HudVisibility hud_visible{};
};

namespace ServerWaypoint_nested {

struct Payload {
    std::uint32_t update_flag{};
    std::optional<bool> is_visible{};
    std::optional<WorldPosition> world_position{};
    std::optional<std::uint32_t> texture_id{};
    std::optional<Color> color{};
    std::optional<bool> client_position_authority{};
    std::optional<ActorUniqueID> actor_id{};
};

}  // namespace ServerWaypoint_nested

struct ServerWaypoint {
    using Payload = ServerWaypoint_nested::Payload;
};

struct LocatorBarWaypointPayload {
    WaypointGroup::WaypointHandle handle{};
    base::ServerWaypoint::Payload payload{};
    ServerWaypointGroup::Action action{};
};

}  // namespace base

namespace v766 {

using SetHudPacket = base::SetHudPacket;

using ServerWaypoint = base::ServerWaypoint;

using LocatorBarWaypointPayload = base::LocatorBarWaypointPayload;

}  // namespace v766

namespace v776 {

using SetHudPacket = base::SetHudPacket;

using ServerWaypoint = base::ServerWaypoint;

using LocatorBarWaypointPayload = base::LocatorBarWaypointPayload;

}  // namespace v776

namespace v786 {

struct SetHudPacket {
    static constexpr int Id = 308;
    std::vector<HudElement> hud_element{};
    HudVisibility hud_visible{};
};

using ServerWaypoint = base::ServerWaypoint;

using LocatorBarWaypointPayload = base::LocatorBarWaypointPayload;

}  // namespace v786

namespace v800 {

using SetHudPacket = v786::SetHudPacket;

using ServerWaypoint = base::ServerWaypoint;

using LocatorBarWaypointPayload = base::LocatorBarWaypointPayload;

}  // namespace v800

namespace v818 {

using SetHudPacket = v786::SetHudPacket;

using ServerWaypoint = base::ServerWaypoint;

using LocatorBarWaypointPayload = base::LocatorBarWaypointPayload;

}  // namespace v818

namespace v827 {

using SetHudPacket = v786::SetHudPacket;

using ServerWaypoint = base::ServerWaypoint;

using LocatorBarWaypointPayload = base::LocatorBarWaypointPayload;

}  // namespace v827

namespace v844 {

using SetHudPacket = v786::SetHudPacket;

using ServerWaypoint = base::ServerWaypoint;

using LocatorBarWaypointPayload = base::LocatorBarWaypointPayload;

}  // namespace v844

namespace v859 {

using SetHudPacket = v786::SetHudPacket;

using ServerWaypoint = base::ServerWaypoint;

using LocatorBarWaypointPayload = base::LocatorBarWaypointPayload;

}  // namespace v859

namespace v898 {

using SetHudPacket = v786::SetHudPacket;

using ServerWaypoint = base::ServerWaypoint;

using LocatorBarWaypointPayload = base::LocatorBarWaypointPayload;

}  // namespace v898

namespace v924 {

struct ClientboundDataDrivenUIReloadPacket {
    static constexpr int Id = 335;
};

using SetHudPacket = v786::SetHudPacket;

struct ClientboundDataDrivenUIShowScreenPacket {
    static constexpr int Id = 333;
    std::string screen_id{};
};

namespace ClientboundTextureShiftPacket_nested {

enum class Action : std::uint8_t {
    Invalid = 0,
    Initialize = 1,
    Start = 2,
    SetEnabled = 3,
    Sync = 4,
};

}  // namespace ClientboundTextureShiftPacket_nested

struct ClientboundTextureShiftPacket {
    using Action = ClientboundTextureShiftPacket_nested::Action;

    static constexpr int Id = 336;
    v924::ClientboundTextureShiftPacket::Action action{};
    std::string collection_name{};
    std::string from_step{};
    std::string to_step{};
    std::vector<std::string> all_steps{};
    std::uint64_t current_length_in_ticks{};
    std::uint64_t total_length_in_ticks{};
    bool enabled{};
};

using ServerWaypoint = base::ServerWaypoint;

using LocatorBarWaypointPayload = base::LocatorBarWaypointPayload;

struct ClientboundDataDrivenUICloseAllScreensPacket {
    static constexpr int Id = 334;
};

}  // namespace v924

namespace v944 {

using ClientboundDataDrivenUIReloadPacket = v924::ClientboundDataDrivenUIReloadPacket;

using SetHudPacket = v786::SetHudPacket;

struct ClientboundDataDrivenUICloseScreenPacket {
    static constexpr int Id = 334;
    std::optional<std::uint32_t> form_id{};
};

struct ClientboundDataDrivenUIShowScreenPacket {
    static constexpr int Id = 333;
    std::string screen_id{};
    std::uint32_t form_id{};
    std::optional<std::uint32_t> data_instance_id{};
};

using ClientboundTextureShiftPacket = v924::ClientboundTextureShiftPacket;

using ServerWaypoint = base::ServerWaypoint;

using LocatorBarWaypointPayload = base::LocatorBarWaypointPayload;

struct LocatorBarPacket {
    static constexpr int Id = 341;
    std::vector<base::LocatorBarWaypointPayload> waypoints{};
};

struct ServerboundDataDrivenScreenClosedPacket {
    static constexpr int Id = 343;
    std::uint32_t form_id{};
    DataDrivenScreenClosedReason close_reason{};
};

}  // namespace v944

namespace v975 {

using ClientboundDataDrivenUIReloadPacket = v924::ClientboundDataDrivenUIReloadPacket;

using SetHudPacket = v786::SetHudPacket;

using ClientboundDataDrivenUICloseScreenPacket = v944::ClientboundDataDrivenUICloseScreenPacket;

using ClientboundDataDrivenUIShowScreenPacket = v944::ClientboundDataDrivenUIShowScreenPacket;

using ClientboundTextureShiftPacket = v924::ClientboundTextureShiftPacket;

namespace ServerWaypoint_nested {

struct Payload {
    std::uint32_t update_flag{};
    std::optional<bool> is_visible{};
    std::optional<WorldPosition> world_position{};
    std::optional<std::string> texture_path{};
    std::optional<Vec2> icon_size{};
    std::optional<Color> color{};
    std::optional<bool> client_position_authority{};
    std::optional<ActorUniqueID> actor_id{};
};

}  // namespace ServerWaypoint_nested

struct ServerWaypoint {
    using Payload = ServerWaypoint_nested::Payload;
};

struct LocatorBarWaypointPayload {
    WaypointGroup::WaypointHandle handle{};
    v975::ServerWaypoint::Payload payload{};
    ServerWaypointGroup::Action action{};
};

struct LocatorBarPacket {
    static constexpr int Id = 341;
    std::vector<v975::LocatorBarWaypointPayload> waypoints{};
};

using ServerboundDataDrivenScreenClosedPacket = v944::ServerboundDataDrivenScreenClosedPacket;

}  // namespace v975

namespace v2168 {

using ClientboundDataDrivenUIReloadPacket = v924::ClientboundDataDrivenUIReloadPacket;

using SetHudPacket = v786::SetHudPacket;

using ClientboundDataDrivenUICloseScreenPacket = v944::ClientboundDataDrivenUICloseScreenPacket;

using ClientboundDataDrivenUIShowScreenPacket = v944::ClientboundDataDrivenUIShowScreenPacket;

using ClientboundTextureShiftPacket = v924::ClientboundTextureShiftPacket;

using ServerWaypoint = v975::ServerWaypoint;

using LocatorBarWaypointPayload = v975::LocatorBarWaypointPayload;

using LocatorBarPacket = v975::LocatorBarPacket;

using ServerboundDataDrivenScreenClosedPacket = v944::ServerboundDataDrivenScreenClosedPacket;

}  // namespace v2168

namespace v2225 {

using ClientboundDataDrivenUIReloadPacket = v924::ClientboundDataDrivenUIReloadPacket;

using SetHudPacket = v786::SetHudPacket;

using ClientboundDataDrivenUICloseScreenPacket = v944::ClientboundDataDrivenUICloseScreenPacket;

using ClientboundDataDrivenUIShowScreenPacket = v944::ClientboundDataDrivenUIShowScreenPacket;

using ClientboundTextureShiftPacket = v924::ClientboundTextureShiftPacket;

using ServerWaypoint = v975::ServerWaypoint;

using LocatorBarWaypointPayload = v975::LocatorBarWaypointPayload;

using LocatorBarPacket = v975::LocatorBarPacket;

using ServerboundDataDrivenScreenClosedPacket = v944::ServerboundDataDrivenScreenClosedPacket;

}  // namespace v2225

namespace detail {

template <int V>
struct ClientboundDataDrivenUIReloadPacket_;

template <int V> requires (V >= 924)
struct ClientboundDataDrivenUIReloadPacket_<V> { using type = v924::ClientboundDataDrivenUIReloadPacket; };

template <int V>
struct SetHudPacket_;

template <int V> requires (V < 786)
struct SetHudPacket_<V> { using type = base::SetHudPacket; };

template <int V> requires (V >= 786)
struct SetHudPacket_<V> { using type = v786::SetHudPacket; };

template <int V>
struct ClientboundDataDrivenUICloseScreenPacket_;

template <int V> requires (V >= 944)
struct ClientboundDataDrivenUICloseScreenPacket_<V> { using type = v944::ClientboundDataDrivenUICloseScreenPacket; };

template <int V>
struct ClientboundDataDrivenUIShowScreenPacket_;

template <int V> requires (V >= 924 && V < 944)
struct ClientboundDataDrivenUIShowScreenPacket_<V> { using type = v924::ClientboundDataDrivenUIShowScreenPacket; };

template <int V> requires (V >= 944)
struct ClientboundDataDrivenUIShowScreenPacket_<V> { using type = v944::ClientboundDataDrivenUIShowScreenPacket; };

template <int V>
struct ClientboundTextureShiftPacket_;

template <int V> requires (V >= 924)
struct ClientboundTextureShiftPacket_<V> { using type = v924::ClientboundTextureShiftPacket; };

template <int V>
struct ServerWaypoint_;

template <int V> requires (V < 975)
struct ServerWaypoint_<V> { using type = base::ServerWaypoint; };

template <int V> requires (V >= 975)
struct ServerWaypoint_<V> { using type = v975::ServerWaypoint; };

template <int V>
struct LocatorBarWaypointPayload_;

template <int V> requires (V < 975)
struct LocatorBarWaypointPayload_<V> { using type = base::LocatorBarWaypointPayload; };

template <int V> requires (V >= 975)
struct LocatorBarWaypointPayload_<V> { using type = v975::LocatorBarWaypointPayload; };

template <int V>
struct LocatorBarPacket_;

template <int V> requires (V >= 944 && V < 975)
struct LocatorBarPacket_<V> { using type = v944::LocatorBarPacket; };

template <int V> requires (V >= 975)
struct LocatorBarPacket_<V> { using type = v975::LocatorBarPacket; };

template <int V>
struct ServerboundDataDrivenScreenClosedPacket_;

template <int V> requires (V >= 944)
struct ServerboundDataDrivenScreenClosedPacket_<V> { using type = v944::ServerboundDataDrivenScreenClosedPacket; };

template <int V>
struct ClientboundDataDrivenUICloseAllScreensPacket_;

template <int V> requires (V >= 924 && V < 944)
struct ClientboundDataDrivenUICloseAllScreensPacket_<V> { using type = v924::ClientboundDataDrivenUICloseAllScreensPacket; };

}  // namespace detail

template <int V> using ClientboundDataDrivenUIReloadPacket_ = typename detail::ClientboundDataDrivenUIReloadPacket_<V>::type;
template <int V> using SetHudPacket_ = typename detail::SetHudPacket_<V>::type;
template <int V> using ClientboundDataDrivenUICloseScreenPacket_ = typename detail::ClientboundDataDrivenUICloseScreenPacket_<V>::type;
template <int V> using ClientboundDataDrivenUIShowScreenPacket_ = typename detail::ClientboundDataDrivenUIShowScreenPacket_<V>::type;
template <int V> using ClientboundTextureShiftPacket_ = typename detail::ClientboundTextureShiftPacket_<V>::type;
template <int V> using ServerWaypoint_ = typename detail::ServerWaypoint_<V>::type;
template <int V> using LocatorBarWaypointPayload_ = typename detail::LocatorBarWaypointPayload_<V>::type;
template <int V> using LocatorBarPacket_ = typename detail::LocatorBarPacket_<V>::type;
template <int V> using ServerboundDataDrivenScreenClosedPacket_ = typename detail::ServerboundDataDrivenScreenClosedPacket_<V>::type;
template <int V> using ClientboundDataDrivenUICloseAllScreensPacket_ = typename detail::ClientboundDataDrivenUICloseAllScreensPacket_<V>::type;

template <int V>
struct packet_of<V, 100> { using type = ModalFormRequestPacket; };

template <int V>
struct packet_of<V, 101> { using type = ModalFormResponsePacket; };

template <int V>
struct packet_of<V, 102> { using type = ServerSettingsRequestPacket; };

template <int V>
struct packet_of<V, 103> { using type = ServerSettingsResponsePacket; };

template <int V>
struct packet_of<V, 130> { using type = OnScreenTextureAnimationPacket; };

template <int V>
struct packet_of<V, 308> { using type = SetHudPacket_<V>; };

template <int V>
struct packet_of<V, 310> { using type = ClientboundCloseFormPacket; };

template <int V>
struct packet_of<V, 312> { using type = ServerboundLoadingScreenPacket; };

template <int V> requires (V >= 924)
struct packet_of<V, 333> { using type = ClientboundDataDrivenUIShowScreenPacket_<V>; };

template <int V> requires (V >= 924 && V < 944)
struct packet_of<V, 334> { using type = ClientboundDataDrivenUICloseAllScreensPacket_<V>; };

template <int V> requires (V >= 944)
struct packet_of<V, 334> { using type = ClientboundDataDrivenUICloseScreenPacket_<V>; };

template <int V> requires (V >= 924)
struct packet_of<V, 335> { using type = ClientboundDataDrivenUIReloadPacket_<V>; };

template <int V> requires (V >= 924)
struct packet_of<V, 336> { using type = ClientboundTextureShiftPacket_<V>; };

template <int V> requires (V >= 944)
struct packet_of<V, 341> { using type = LocatorBarPacket_<V>; };

template <int V> requires (V >= 944)
struct packet_of<V, 343> { using type = ServerboundDataDrivenScreenClosedPacket_<V>; };

namespace detail {

template <>
inline constexpr std::array<HudElement, 14> values_v<HudElement>{{
    HudElement::PaperDoll,
    HudElement::Armor,
    HudElement::ToolTips,
    HudElement::TouchControls,
    HudElement::Crosshair,
    HudElement::HotBar,
    HudElement::Health,
    HudElement::ProgressBar,
    HudElement::Hunger,
    HudElement::AirBubbles,
    HudElement::HorseHealth,
    HudElement::StatusEffects,
    HudElement::ItemText,
    HudElement::Count,
}};

template <>
inline constexpr std::array<std::string_view, 14> names_v<HudElement>{{
    "paperdoll",
    "armor",
    "tooltips",
    "touchcontrols",
    "crosshair",
    "hotbar",
    "health",
    "progressbar",
    "hunger",
    "airbubbles",
    "horsehealth",
    "statuseffects",
    "itemtext",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<HudElement>{"HudElement"};

template <>
inline constexpr std::array<HudVisibility, 3> values_v<HudVisibility>{{
    HudVisibility::Hide,
    HudVisibility::Reset,
    HudVisibility::Count,
}};

template <>
inline constexpr std::array<std::string_view, 3> names_v<HudVisibility>{{
    "hide",
    "reset",
    "count",
}};

template <>
inline constexpr std::string_view type_name_v<HudVisibility>{"HudVisibility"};

template <>
inline constexpr std::array<ServerboundLoadingScreenPacketType, 3> values_v<ServerboundLoadingScreenPacketType>{{
    ServerboundLoadingScreenPacketType::Unknown,
    ServerboundLoadingScreenPacketType::StartLoadingScreen,
    ServerboundLoadingScreenPacketType::EndLoadingScreen,
}};

template <>
inline constexpr std::array<std::string_view, 3> names_v<ServerboundLoadingScreenPacketType>{{
    "unknown",
    "startloadingscreen",
    "endloadingscreen",
}};

template <>
inline constexpr std::string_view type_name_v<ServerboundLoadingScreenPacketType>{"ServerboundLoadingScreenPacketType"};

template <>
inline constexpr std::array<v924::ClientboundTextureShiftPacket::Action, 5> values_v<v924::ClientboundTextureShiftPacket::Action>{{
    v924::ClientboundTextureShiftPacket::Action::Invalid,
    v924::ClientboundTextureShiftPacket::Action::Initialize,
    v924::ClientboundTextureShiftPacket::Action::Start,
    v924::ClientboundTextureShiftPacket::Action::SetEnabled,
    v924::ClientboundTextureShiftPacket::Action::Sync,
}};

template <>
inline constexpr std::array<std::string_view, 5> names_v<v924::ClientboundTextureShiftPacket::Action>{{
    "invalid",
    "initialize",
    "start",
    "setenabled",
    "sync",
}};

template <>
inline constexpr std::string_view type_name_v<v924::ClientboundTextureShiftPacket::Action>{"ClientboundTextureShiftPacket::Action"};

template <>
inline constexpr std::array<ServerWaypointGroup::Action, 4> values_v<ServerWaypointGroup::Action>{{
    ServerWaypointGroup::Action::None,
    ServerWaypointGroup::Action::Add,
    ServerWaypointGroup::Action::Remove,
    ServerWaypointGroup::Action::Update,
}};

template <>
inline constexpr std::array<std::string_view, 4> names_v<ServerWaypointGroup::Action>{{
    "none",
    "add",
    "remove",
    "update",
}};

template <>
inline constexpr std::string_view type_name_v<ServerWaypointGroup::Action>{"ServerWaypointGroup::Action"};

template <>
inline constexpr std::array<DataDrivenScreenClosedReason, 5> values_v<DataDrivenScreenClosedReason>{{
    DataDrivenScreenClosedReason::ProgrammaticClose,
    DataDrivenScreenClosedReason::ProgrammaticCloseAll,
    DataDrivenScreenClosedReason::ClientCanceled,
    DataDrivenScreenClosedReason::UserBusy,
    DataDrivenScreenClosedReason::InvalidForm,
}};

template <>
inline constexpr std::array<std::string_view, 5> names_v<DataDrivenScreenClosedReason>{{
    "programmaticclose",
    "programmaticcloseall",
    "clientcanceled",
    "userbusy",
    "invalidform",
}};

template <>
inline constexpr std::string_view type_name_v<DataDrivenScreenClosedReason>{"DataDrivenScreenClosedReason"};

template <>
inline constexpr std::array<ModalFormCancelReason, 2> values_v<ModalFormCancelReason>{{
    ModalFormCancelReason::UserClosed,
    ModalFormCancelReason::UserBusy,
}};

template <>
inline constexpr std::array<std::string_view, 2> names_v<ModalFormCancelReason>{{
    "userclosed",
    "userbusy",
}};

template <>
inline constexpr std::string_view type_name_v<ModalFormCancelReason>{"ModalFormCancelReason"};

}  // namespace detail

namespace detail {

template <>
inline constexpr bool is_reflected_struct_v<v924::ClientboundDataDrivenUIReloadPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::ClientboundDataDrivenUIReloadPacket>{"ClientboundDataDrivenUIReloadPacket"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<v924::ClientboundDataDrivenUIReloadPacket>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<base::SetHudPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<base::SetHudPacket>{"SetHudPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<base::SetHudPacket>{{
    "hud_element",
    "hud_visible",
}};

template <>
struct field_accessor<base::SetHudPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.hud_element;
        }
        else {
            return value.hud_visible;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v786::SetHudPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v786::SetHudPacket>{"SetHudPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v786::SetHudPacket>{{
    "hud_element",
    "hud_visible",
}};

template <>
struct field_accessor<v786::SetHudPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.hud_element;
        }
        else {
            return value.hud_visible;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<ServerboundLoadingScreenPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<ServerboundLoadingScreenPacket>{"ServerboundLoadingScreenPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<ServerboundLoadingScreenPacket>{{
    "loading_screen_packet_type",
    "loading_screen_id",
}};

template <>
struct field_accessor<ServerboundLoadingScreenPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.loading_screen_packet_type;
        }
        else {
            return value.loading_screen_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::ClientboundDataDrivenUICloseScreenPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::ClientboundDataDrivenUICloseScreenPacket>{"ClientboundDataDrivenUICloseScreenPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v944::ClientboundDataDrivenUICloseScreenPacket>{{
    "form_id",
}};

template <>
struct field_accessor<v944::ClientboundDataDrivenUICloseScreenPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.form_id;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::ClientboundDataDrivenUIShowScreenPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::ClientboundDataDrivenUIShowScreenPacket>{"ClientboundDataDrivenUIShowScreenPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v924::ClientboundDataDrivenUIShowScreenPacket>{{
    "screen_id",
}};

template <>
struct field_accessor<v924::ClientboundDataDrivenUIShowScreenPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.screen_id;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::ClientboundDataDrivenUIShowScreenPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::ClientboundDataDrivenUIShowScreenPacket>{"ClientboundDataDrivenUIShowScreenPacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v944::ClientboundDataDrivenUIShowScreenPacket>{{
    "screen_id",
    "form_id",
    "data_instance_id",
}};

template <>
struct field_accessor<v944::ClientboundDataDrivenUIShowScreenPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.screen_id;
        }
        else if constexpr (I == 1) {
            return value.form_id;
        }
        else {
            return value.data_instance_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::ClientboundTextureShiftPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::ClientboundTextureShiftPacket>{"ClientboundTextureShiftPacket"};

template <>
inline constexpr std::array<std::string_view, 8> field_names_v<v924::ClientboundTextureShiftPacket>{{
    "action",
    "collection_name",
    "from_step",
    "to_step",
    "all_steps",
    "current_length_in_ticks",
    "total_length_in_ticks",
    "enabled",
}};

template <>
struct field_accessor<v924::ClientboundTextureShiftPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.action;
        }
        else if constexpr (I == 1) {
            return value.collection_name;
        }
        else if constexpr (I == 2) {
            return value.from_step;
        }
        else if constexpr (I == 3) {
            return value.to_step;
        }
        else if constexpr (I == 4) {
            return value.all_steps;
        }
        else if constexpr (I == 5) {
            return value.current_length_in_ticks;
        }
        else if constexpr (I == 6) {
            return value.total_length_in_ticks;
        }
        else {
            return value.enabled;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<WorldPosition> = true;

template <>
inline constexpr std::string_view struct_name_v<WorldPosition>{"WorldPosition"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<WorldPosition>{{
    "pos",
    "dimension_type",
}};

template <>
struct field_accessor<WorldPosition> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.pos;
        }
        else {
            return value.dimension_type;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<WaypointGroup::WaypointHandle> = true;

template <>
inline constexpr std::string_view struct_name_v<WaypointGroup::WaypointHandle>{"WaypointGroup::WaypointHandle"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<WaypointGroup::WaypointHandle>{{
    "uuid",
}};

template <>
struct field_accessor<WaypointGroup::WaypointHandle> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.uuid;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<WaypointGroup> = true;

template <>
inline constexpr std::string_view struct_name_v<WaypointGroup>{"WaypointGroup"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<WaypointGroup>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<base::ServerWaypoint::Payload> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ServerWaypoint::Payload>{"ServerWaypoint::Payload"};

template <>
inline constexpr std::array<std::string_view, 7> field_names_v<base::ServerWaypoint::Payload>{{
    "update_flag",
    "is_visible",
    "world_position",
    "texture_id",
    "color",
    "client_position_authority",
    "actor_id",
}};

template <>
struct field_accessor<base::ServerWaypoint::Payload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.update_flag;
        }
        else if constexpr (I == 1) {
            return value.is_visible;
        }
        else if constexpr (I == 2) {
            return value.world_position;
        }
        else if constexpr (I == 3) {
            return value.texture_id;
        }
        else if constexpr (I == 4) {
            return value.color;
        }
        else if constexpr (I == 5) {
            return value.client_position_authority;
        }
        else {
            return value.actor_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v975::ServerWaypoint::Payload> = true;

template <>
inline constexpr std::string_view struct_name_v<v975::ServerWaypoint::Payload>{"ServerWaypoint::Payload"};

template <>
inline constexpr std::array<std::string_view, 8> field_names_v<v975::ServerWaypoint::Payload>{{
    "update_flag",
    "is_visible",
    "world_position",
    "texture_path",
    "icon_size",
    "color",
    "client_position_authority",
    "actor_id",
}};

template <>
struct field_accessor<v975::ServerWaypoint::Payload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.update_flag;
        }
        else if constexpr (I == 1) {
            return value.is_visible;
        }
        else if constexpr (I == 2) {
            return value.world_position;
        }
        else if constexpr (I == 3) {
            return value.texture_path;
        }
        else if constexpr (I == 4) {
            return value.icon_size;
        }
        else if constexpr (I == 5) {
            return value.color;
        }
        else if constexpr (I == 6) {
            return value.client_position_authority;
        }
        else {
            return value.actor_id;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<base::ServerWaypoint> = true;

template <>
inline constexpr std::string_view struct_name_v<base::ServerWaypoint>{"ServerWaypoint"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<base::ServerWaypoint>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<v975::ServerWaypoint> = true;

template <>
inline constexpr std::string_view struct_name_v<v975::ServerWaypoint>{"ServerWaypoint"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<v975::ServerWaypoint>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<ServerWaypointGroup> = true;

template <>
inline constexpr std::string_view struct_name_v<ServerWaypointGroup>{"ServerWaypointGroup"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<ServerWaypointGroup>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<base::LocatorBarWaypointPayload> = true;

template <>
inline constexpr std::string_view struct_name_v<base::LocatorBarWaypointPayload>{"LocatorBarWaypointPayload"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<base::LocatorBarWaypointPayload>{{
    "handle",
    "payload",
    "action",
}};

template <>
struct field_accessor<base::LocatorBarWaypointPayload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.handle;
        }
        else if constexpr (I == 1) {
            return value.payload;
        }
        else {
            return value.action;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v975::LocatorBarWaypointPayload> = true;

template <>
inline constexpr std::string_view struct_name_v<v975::LocatorBarWaypointPayload>{"LocatorBarWaypointPayload"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<v975::LocatorBarWaypointPayload>{{
    "handle",
    "payload",
    "action",
}};

template <>
struct field_accessor<v975::LocatorBarWaypointPayload> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.handle;
        }
        else if constexpr (I == 1) {
            return value.payload;
        }
        else {
            return value.action;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::LocatorBarPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::LocatorBarPacket>{"LocatorBarPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v944::LocatorBarPacket>{{
    "waypoints",
}};

template <>
struct field_accessor<v944::LocatorBarPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.waypoints;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v975::LocatorBarPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v975::LocatorBarPacket>{"LocatorBarPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<v975::LocatorBarPacket>{{
    "waypoints",
}};

template <>
struct field_accessor<v975::LocatorBarPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.waypoints;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v944::ServerboundDataDrivenScreenClosedPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v944::ServerboundDataDrivenScreenClosedPacket>{"ServerboundDataDrivenScreenClosedPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<v944::ServerboundDataDrivenScreenClosedPacket>{{
    "form_id",
    "close_reason",
}};

template <>
struct field_accessor<v944::ServerboundDataDrivenScreenClosedPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.form_id;
        }
        else {
            return value.close_reason;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<ModalFormRequestPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<ModalFormRequestPacket>{"ModalFormRequestPacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<ModalFormRequestPacket>{{
    "form_id",
    "form_json",
}};

template <>
struct field_accessor<ModalFormRequestPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.form_id;
        }
        else {
            return value.form_json;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<ServerSettingsRequestPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<ServerSettingsRequestPacket>{"ServerSettingsRequestPacket"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<ServerSettingsRequestPacket>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<ServerSettingsResponsePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<ServerSettingsResponsePacket>{"ServerSettingsResponsePacket"};

template <>
inline constexpr std::array<std::string_view, 2> field_names_v<ServerSettingsResponsePacket>{{
    "form_id",
    "form_json",
}};

template <>
struct field_accessor<ServerSettingsResponsePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.form_id;
        }
        else {
            return value.form_json;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<ClientboundCloseFormPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<ClientboundCloseFormPacket>{"ClientboundCloseFormPacket"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<ClientboundCloseFormPacket>{{
}};

template <>
inline constexpr bool is_reflected_struct_v<ModalFormResponsePacket> = true;

template <>
inline constexpr std::string_view struct_name_v<ModalFormResponsePacket>{"ModalFormResponsePacket"};

template <>
inline constexpr std::array<std::string_view, 3> field_names_v<ModalFormResponsePacket>{{
    "form_id",
    "json_response",
    "form_cancel_reason",
}};

template <>
struct field_accessor<ModalFormResponsePacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        if constexpr (I == 0) {
            return value.form_id;
        }
        else if constexpr (I == 1) {
            return value.json_response;
        }
        else {
            return value.form_cancel_reason;
        }
    }
};

template <>
inline constexpr bool is_reflected_struct_v<OnScreenTextureAnimationPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<OnScreenTextureAnimationPacket>{"OnScreenTextureAnimationPacket"};

template <>
inline constexpr std::array<std::string_view, 1> field_names_v<OnScreenTextureAnimationPacket>{{
    "effect_id",
}};

template <>
struct field_accessor<OnScreenTextureAnimationPacket> {
    template <std::size_t I, typename S>
    static constexpr auto &get(S &value) noexcept
    {
        return value.effect_id;
    }
};

template <>
inline constexpr bool is_reflected_struct_v<v924::ClientboundDataDrivenUICloseAllScreensPacket> = true;

template <>
inline constexpr std::string_view struct_name_v<v924::ClientboundDataDrivenUICloseAllScreensPacket>{"ClientboundDataDrivenUICloseAllScreensPacket"};

template <>
inline constexpr std::array<std::string_view, 0> field_names_v<v924::ClientboundDataDrivenUICloseAllScreensPacket>{{
}};

}  // namespace detail


template <>
struct Serializer<v924::ClientboundDataDrivenUIReloadPacket> {
    static void serialize(BinaryWriter &stream, const v924::ClientboundDataDrivenUIReloadPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::ClientboundDataDrivenUIReloadPacket, std::error_code>;
};

template <>
struct Serializer<base::SetHudPacket> {
    static void serialize(BinaryWriter &stream, const base::SetHudPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::SetHudPacket, std::error_code>;
};

template <>
struct Serializer<v786::SetHudPacket> {
    static void serialize(BinaryWriter &stream, const v786::SetHudPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v786::SetHudPacket, std::error_code>;
};

template <>
struct Serializer<ServerboundLoadingScreenPacket> {
    static void serialize(BinaryWriter &stream, const ServerboundLoadingScreenPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<ServerboundLoadingScreenPacket, std::error_code>;
};

template <>
struct Serializer<v944::ClientboundDataDrivenUICloseScreenPacket> {
    static void serialize(BinaryWriter &stream, const v944::ClientboundDataDrivenUICloseScreenPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::ClientboundDataDrivenUICloseScreenPacket, std::error_code>;
};

template <>
struct Serializer<v924::ClientboundDataDrivenUIShowScreenPacket> {
    static void serialize(BinaryWriter &stream, const v924::ClientboundDataDrivenUIShowScreenPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::ClientboundDataDrivenUIShowScreenPacket, std::error_code>;
};

template <>
struct Serializer<v944::ClientboundDataDrivenUIShowScreenPacket> {
    static void serialize(BinaryWriter &stream, const v944::ClientboundDataDrivenUIShowScreenPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::ClientboundDataDrivenUIShowScreenPacket, std::error_code>;
};

template <>
struct Serializer<v924::ClientboundTextureShiftPacket> {
    static void serialize(BinaryWriter &stream, const v924::ClientboundTextureShiftPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::ClientboundTextureShiftPacket, std::error_code>;
};

template <>
struct Serializer<WorldPosition> {
    static void serialize(BinaryWriter &stream, const WorldPosition &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<WorldPosition, std::error_code>;
};

template <>
struct Serializer<WaypointGroup::WaypointHandle> {
    static void serialize(BinaryWriter &stream, const WaypointGroup::WaypointHandle &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<WaypointGroup::WaypointHandle, std::error_code>;
};

template <>
struct Serializer<base::ServerWaypoint::Payload> {
    static void serialize(BinaryWriter &stream, const base::ServerWaypoint::Payload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::ServerWaypoint::Payload, std::error_code>;
};

template <>
struct Serializer<v975::ServerWaypoint::Payload> {
    static void serialize(BinaryWriter &stream, const v975::ServerWaypoint::Payload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v975::ServerWaypoint::Payload, std::error_code>;
};

template <>
struct Serializer<base::LocatorBarWaypointPayload> {
    static void serialize(BinaryWriter &stream, const base::LocatorBarWaypointPayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<base::LocatorBarWaypointPayload, std::error_code>;
};

template <>
struct Serializer<v975::LocatorBarWaypointPayload> {
    static void serialize(BinaryWriter &stream, const v975::LocatorBarWaypointPayload &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v975::LocatorBarWaypointPayload, std::error_code>;
};

template <>
struct Serializer<v944::LocatorBarPacket> {
    static void serialize(BinaryWriter &stream, const v944::LocatorBarPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::LocatorBarPacket, std::error_code>;
};

template <>
struct Serializer<v975::LocatorBarPacket> {
    static void serialize(BinaryWriter &stream, const v975::LocatorBarPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v975::LocatorBarPacket, std::error_code>;
};

template <>
struct Serializer<DataDrivenScreenClosedReason> {
    static void serialize(BinaryWriter &stream, DataDrivenScreenClosedReason value);
    static auto deserialize(BinaryReader &stream) -> std::expected<DataDrivenScreenClosedReason, std::error_code>;
};

template <>
struct Serializer<v944::ServerboundDataDrivenScreenClosedPacket> {
    static void serialize(BinaryWriter &stream, const v944::ServerboundDataDrivenScreenClosedPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v944::ServerboundDataDrivenScreenClosedPacket, std::error_code>;
};

template <>
struct Serializer<ModalFormRequestPacket> {
    static void serialize(BinaryWriter &stream, const ModalFormRequestPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<ModalFormRequestPacket, std::error_code>;
};

template <>
struct Serializer<ServerSettingsRequestPacket> {
    static void serialize(BinaryWriter &stream, const ServerSettingsRequestPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<ServerSettingsRequestPacket, std::error_code>;
};

template <>
struct Serializer<ServerSettingsResponsePacket> {
    static void serialize(BinaryWriter &stream, const ServerSettingsResponsePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<ServerSettingsResponsePacket, std::error_code>;
};

template <>
struct Serializer<ClientboundCloseFormPacket> {
    static void serialize(BinaryWriter &stream, const ClientboundCloseFormPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<ClientboundCloseFormPacket, std::error_code>;
};

template <>
struct Serializer<ModalFormResponsePacket> {
    static void serialize(BinaryWriter &stream, const ModalFormResponsePacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<ModalFormResponsePacket, std::error_code>;
};

template <>
struct Serializer<OnScreenTextureAnimationPacket> {
    static void serialize(BinaryWriter &stream, const OnScreenTextureAnimationPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<OnScreenTextureAnimationPacket, std::error_code>;
};

template <>
struct Serializer<v924::ClientboundDataDrivenUICloseAllScreensPacket> {
    static void serialize(BinaryWriter &stream, const v924::ClientboundDataDrivenUICloseAllScreensPacket &value);
    static auto deserialize(BinaryReader &stream) -> std::expected<v924::ClientboundDataDrivenUICloseAllScreensPacket, std::error_code>;
};
using ClientboundDataDrivenUIReloadPacket = ClientboundDataDrivenUIReloadPacket_<2225>;
using SetHudPacket = SetHudPacket_<2225>;
using ClientboundDataDrivenUICloseScreenPacket = ClientboundDataDrivenUICloseScreenPacket_<2225>;
using ClientboundDataDrivenUIShowScreenPacket = ClientboundDataDrivenUIShowScreenPacket_<2225>;
using ClientboundTextureShiftPacket = ClientboundTextureShiftPacket_<2225>;
using ServerWaypoint = ServerWaypoint_<2225>;
using LocatorBarWaypointPayload = LocatorBarWaypointPayload_<2225>;
using LocatorBarPacket = LocatorBarPacket_<2225>;
using ServerboundDataDrivenScreenClosedPacket = ServerboundDataDrivenScreenClosedPacket_<2225>;

}  // namespace bedrock::protocol
