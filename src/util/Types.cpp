#include "crosslink/api/Types.hpp"

#include <format>

namespace crosslink {

std::string Endpoint::toString() const { return std::format("{}:{}", host, port); }

std::string const& PlayerIdentity::key() const noexcept {
    if (!xuid.empty()) return xuid;
    if (!identity.empty()) return identity;
    return name;
}

} // namespace crosslink
