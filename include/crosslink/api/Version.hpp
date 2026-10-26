#pragma once

#include "crosslink/api/Export.hpp"
#include "crosslink/api/Result.hpp"

#include <compare>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

namespace crosslink {

/// Semantic version, the same shape LeviLamina uses for mod manifests.
struct CROSSLINK_API Version {
    std::uint16_t major{};
    std::uint16_t minor{};
    std::uint16_t patch{};
    std::string   preRelease;
    std::string   build;

    Version() = default;
    Version(std::uint16_t majorVersion, std::uint16_t minorVersion, std::uint16_t patchVersion)
    : major(majorVersion), minor(minorVersion), patch(patchVersion) {}

    [[nodiscard]] static Result<Version> parse(std::string_view text);
    [[nodiscard]] std::string            toString() const;

    /// Pre-release versions sort before their release counterpart.
    [[nodiscard]] std::strong_ordering operator<=>(Version const& other) const;
    [[nodiscard]] bool                 operator==(Version const& other) const;
};

/// An npm-style version requirement: `^1.2`, `>=1.0.0 <2.0.0`, `1.2.3 - 2.0.0`,
/// `*`, or alternatives joined with `||`. Whitespace inside one group means AND.
class CROSSLINK_API VersionRequirement {
public:
    VersionRequirement() = default;

    [[nodiscard]] static Result<VersionRequirement> parse(std::string_view text);

    /// An empty requirement matches every version, which is what a dependency
    /// without a version field means.
    [[nodiscard]] bool        empty() const noexcept;
    [[nodiscard]] bool        matches(Version const& version) const;
    [[nodiscard]] std::string toString() const;

private:
    enum class Operator : std::uint8_t { Equal, Greater, GreaterEqual, Less, LessEqual };

    struct Comparator {
        Operator op{Operator::Equal};
        Version  version;
    };

    // Disjunctive normal form: any group matching is enough.
    std::vector<std::vector<Comparator>> mGroups;
    std::string                          mText;
};

} // namespace crosslink
