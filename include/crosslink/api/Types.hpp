#pragma once

#include "crosslink/api/Export.hpp"

#include <compare>
#include <cstdint>
#include <functional>
#include <span>
#include <string>
#include <string_view>
#include <vector>

namespace crosslink {

using Bytes      = std::vector<std::byte>;
using ByteSpan   = std::span<const std::byte>;
using ByteWriter = std::span<std::byte>;

inline ByteSpan bytesOf(std::string_view text) noexcept {
    return {reinterpret_cast<const std::byte*>(text.data()), text.size()};
}

inline std::string_view viewOf(ByteSpan bytes) noexcept {
    return {reinterpret_cast<const char*>(bytes.data()), bytes.size()};
}

/// A string id that cannot be confused with another id kind at compile time.
template <typename Tag>
struct StrongId {
    std::string value;

    StrongId() = default;
    StrongId(std::string_view text) : value(text) {}
    StrongId(std::string text) : value(std::move(text)) {}

    [[nodiscard]] bool                empty() const noexcept { return value.empty(); }
    [[nodiscard]] std::string_view    view() const noexcept { return value; }
    [[nodiscard]] std::string const&  str() const noexcept { return value; }
    explicit operator bool() const noexcept { return !value.empty(); }

    [[nodiscard]] auto operator<=>(StrongId const&) const = default;
};

struct ServerIdTag;
struct SessionIdTag;
struct AgentIdTag;

using ServerId  = StrongId<ServerIdTag>;
using SessionId = StrongId<SessionIdTag>;
using AgentId   = StrongId<AgentIdTag>;

struct Endpoint {
    std::string   host;
    std::uint16_t port{};

    [[nodiscard]] std::string toString() const;
    [[nodiscard]] auto        operator<=>(Endpoint const&) const = default;
};

struct Vec3 {
    float x{};
    float y{};
    float z{};

    [[nodiscard]] auto operator<=>(Vec3 const&) const = default;
};

enum class GameType : std::int32_t {
    Undefined = -1,
    Survival  = 0,
    Creative  = 1,
    Adventure = 2,
    Spectator = 6,
    Default   = 5,
};

enum class Dimension : std::int32_t {
    Overworld = 0,
    Nether    = 1,
    TheEnd    = 2,
};

/// What the gateway knows about a player, gathered while the login packet is
/// relayed. XUID is the preferred key; offline backends may only have a name.
struct PlayerIdentity {
    std::string xuid;
    std::string name;
    std::string playFabId;
    std::string identity;

    /// Stable lookup key: xuid when present, else the offline identity, else name.
    [[nodiscard]] std::string const& key() const noexcept;
};

/// Describes one backend server as seen by the routing layer.
struct ServerInfo {
    ServerId id;
    Endpoint gameEndpoint;
    Endpoint agentEndpoint;
    bool     isLobby{};
};

} // namespace crosslink

template <typename Tag>
struct std::hash<crosslink::StrongId<Tag>> {
    [[nodiscard]] std::size_t operator()(crosslink::StrongId<Tag> const& id) const noexcept {
        return std::hash<std::string>{}(id.value);
    }
};
