#include "crosslink/api/Version.hpp"

#include <algorithm>
#include <cctype>
#include <charconv>
#include <format>
#include <string>
#include <vector>

namespace crosslink {
namespace {

std::vector<std::string_view> split(std::string_view text, char separator) {
    std::vector<std::string_view> parts;
    std::size_t start = 0;
    while (start <= text.size()) {
        const auto found = text.find(separator, start);
        if (found == std::string_view::npos) {
            parts.push_back(text.substr(start));
            break;
        }
        parts.push_back(text.substr(start, found - start));
        start = found + 1;
    }
    return parts;
}

std::string_view trim(std::string_view text) {
    const auto isSpace = [](unsigned char ch) { return std::isspace(ch) != 0; };
    while (!text.empty() && isSpace(static_cast<unsigned char>(text.front()))) text.remove_prefix(1);
    while (!text.empty() && isSpace(static_cast<unsigned char>(text.back()))) text.remove_suffix(1);
    return text;
}

bool parseNumber(std::string_view text, std::uint16_t& out) {
    if (text.empty()) return false;
    if (text == "*" || text == "x" || text == "X") {
        out = 0;
        return true;
    }
    std::uint32_t value{};
    const auto* first = text.data();
    const auto [ptr, error] = std::from_chars(first, first + text.size(), value);
    if (error != std::errc{} || ptr != first + text.size() || value > 0xFFFFu) return false;
    out = static_cast<std::uint16_t>(value);
    return true;
}

/// Parses `1`, `1.2`, `1.2.3`, `1.2.3-pre`, `1.2.3-pre+build`. Missing parts are
/// zero; `partsPresent` reports how many numeric parts were written.
Result<Version> parseVersion(std::string_view text, int& partsPresent) {
    partsPresent = 0;
    Version version;

    std::string_view core = text;
    std::string_view remainder;
    if (const auto plus = core.find('+'); plus != std::string_view::npos) {
        version.build = std::string{core.substr(plus + 1)};
        core = core.substr(0, plus);
    }
    if (const auto dash = core.find('-'); dash != std::string_view::npos) {
        version.preRelease = std::string{core.substr(dash + 1)};
        core = core.substr(0, dash);
    }
    remainder = core;

    const auto parts = split(remainder, '.');
    if (parts.empty() || parts.size() > 3) return std::unexpected(Error{std::format("invalid version '{}'", text)});

    std::uint16_t values[3] = {0, 0, 0};
    for (std::size_t index = 0; index < parts.size(); ++index) {
        if (!parseNumber(trim(parts[index]), values[index])) {
            return std::unexpected(Error{std::format("invalid version component in '{}'", text)});
        }
    }
    partsPresent = static_cast<int>(parts.size());
    version.major = values[0];
    version.minor = values[1];
    version.patch = values[2];
    return version;
}

int comparePreRelease(std::string_view left, std::string_view right) {
    if (left == right) return 0;
    // A release outranks any of its pre-releases.
    if (left.empty()) return 1;
    if (right.empty()) return -1;

    const auto leftParts = split(left, '.');
    const auto rightParts = split(right, '.');
    for (std::size_t index = 0; index < std::max(leftParts.size(), rightParts.size()); ++index) {
        if (index >= leftParts.size()) return -1;
        if (index >= rightParts.size()) return 1;
        const auto l = leftParts[index];
        const auto r = rightParts[index];
        std::uint32_t lNumber{};
        std::uint32_t rNumber{};
        const auto lNumeric = !l.empty() && std::all_of(l.begin(), l.end(), [](char ch) { return std::isdigit(static_cast<unsigned char>(ch)) != 0; });
        const auto rNumeric = !r.empty() && std::all_of(r.begin(), r.end(), [](char ch) { return std::isdigit(static_cast<unsigned char>(ch)) != 0; });
        if (lNumeric && rNumeric) {
            std::from_chars(l.data(), l.data() + l.size(), lNumber);
            std::from_chars(r.data(), r.data() + r.size(), rNumber);
            if (lNumber != rNumber) return lNumber < rNumber ? -1 : 1;
            continue;
        }
        if (lNumeric != rNumeric) return lNumeric ? -1 : 1;
        if (const auto order = l.compare(r); order != 0) return order < 0 ? -1 : 1;
    }
    return 0;
}

} // namespace

Result<Version> Version::parse(std::string_view text) {
    int partsPresent{};
    return parseVersion(trim(text), partsPresent);
}

std::string Version::toString() const {
    auto text = std::format("{}.{}.{}", major, minor, patch);
    if (!preRelease.empty()) text += "-" + preRelease;
    if (!build.empty()) text += "+" + build;
    return text;
}

std::strong_ordering Version::operator<=>(Version const& other) const {
    if (const auto order = major <=> other.major; order != 0) return order;
    if (const auto order = minor <=> other.minor; order != 0) return order;
    if (const auto order = patch <=> other.patch; order != 0) return order;
    const auto preReleaseOrder = comparePreRelease(preRelease, other.preRelease);
    if (preReleaseOrder != 0) return preReleaseOrder < 0 ? std::strong_ordering::less : std::strong_ordering::greater;
    return std::strong_ordering::equal;
}

bool Version::operator==(Version const& other) const { return (*this <=> other) == 0; }

bool VersionRequirement::empty() const noexcept { return mGroups.empty(); }

std::string VersionRequirement::toString() const { return mText; }

Result<VersionRequirement> VersionRequirement::parse(std::string_view text) {
    VersionRequirement requirement;
    requirement.mText = std::string{trim(text)};
    if (requirement.mText.empty() || requirement.mText == "*" || requirement.mText == "x") {
        // Matches everything; leaving mGroups empty is how that is represented.
        return requirement;
    }

    for (const auto alternative : split(requirement.mText, '|')) {
        // "||" separates alternatives; a lone "|" leaves an empty piece.
        if (trim(alternative).empty()) continue;
        std::string groupText{trim(alternative)};

        std::vector<Comparator> group;

        if (const auto hyphen = groupText.find(" - "); hyphen != std::string_view::npos) {
            const auto lowText = trim(std::string_view{groupText}.substr(0, hyphen));
            const auto highText = trim(std::string_view{groupText}.substr(hyphen + 3));
            const auto low = Version::parse(lowText);
            const auto high = Version::parse(highText);
            if (!low) return std::unexpected(low.error());
            if (!high) return std::unexpected(high.error());
            group.push_back({Operator::GreaterEqual, *low});
            group.push_back({Operator::LessEqual, *high});
        } else {
            std::size_t start = 0;
            while (start < groupText.size()) {
                while (start < groupText.size() && std::isspace(static_cast<unsigned char>(groupText[start]))) ++start;
                if (start >= groupText.size()) break;
                std::size_t end = start;
                while (end < groupText.size() && !std::isspace(static_cast<unsigned char>(groupText[end]))) ++end;
                const auto token = std::string_view{groupText}.substr(start, end - start);
                start = end;

                if (token == "*" || token == "x" || token == "X") continue;

                Operator op = Operator::Equal;
                std::string_view versionText = token;
                if (token.starts_with(">=")) {
                    op = Operator::GreaterEqual;
                    versionText = token.substr(2);
                } else if (token.starts_with("<=")) {
                    op = Operator::LessEqual;
                    versionText = token.substr(2);
                } else if (token.starts_with(">")) {
                    op = Operator::Greater;
                    versionText = token.substr(1);
                } else if (token.starts_with("<")) {
                    op = Operator::Less;
                    versionText = token.substr(1);
                } else if (token.starts_with("=")) {
                    versionText = token.substr(1);
                } else if (token.starts_with("^")) {
                    int partsPresent{};
                    const auto base = parseVersion(trim(token.substr(1)), partsPresent);
                    if (!base) return std::unexpected(base.error());
                    Version ceiling = *base;
                    if (partsPresent <= 1 || base->major > 0) {
                        ceiling = Version{static_cast<std::uint16_t>(base->major + 1), 0, 0};
                    } else if (base->minor > 0) {
                        ceiling = Version{0, static_cast<std::uint16_t>(base->minor + 1), 0};
                    } else {
                        ceiling = Version{0, 0, static_cast<std::uint16_t>(base->patch + 1)};
                    }
                    group.push_back({Operator::GreaterEqual, *base});
                    group.push_back({Operator::Less, ceiling});
                    continue;
                } else if (token.starts_with("~")) {
                    int partsPresent{};
                    const auto base = parseVersion(trim(token.substr(1)), partsPresent);
                    if (!base) return std::unexpected(base.error());
                    const Version ceiling = partsPresent <= 1
                                                ? Version{static_cast<std::uint16_t>(base->major + 1), 0, 0}
                                                : Version{base->major, static_cast<std::uint16_t>(base->minor + 1), 0};
                    group.push_back({Operator::GreaterEqual, *base});
                    group.push_back({Operator::Less, ceiling});
                    continue;
                }

                int partsPresent{};
                const auto version = parseVersion(trim(versionText), partsPresent);
                if (!version) return std::unexpected(version.error());

                // A partial version such as "1.2" means the whole "1.2.x" range.
                if (op == Operator::Equal && partsPresent < 3) {
                    Version ceiling = *version;
                    if (partsPresent <= 1) {
                        ceiling = Version{static_cast<std::uint16_t>(version->major + 1), 0, 0};
                    } else {
                        ceiling = Version{version->major, static_cast<std::uint16_t>(version->minor + 1), 0};
                    }
                    group.push_back({Operator::GreaterEqual, *version});
                    group.push_back({Operator::Less, ceiling});
                    continue;
                }
                group.push_back({op, *version});
            }
        }

        if (!group.empty()) requirement.mGroups.push_back(std::move(group));
    }

    return requirement;
}

bool VersionRequirement::matches(Version const& version) const {
    if (mGroups.empty()) return true;

    for (auto const& group : mGroups) {
        bool ok = true;
        bool preReleaseAllowed = false;
        for (auto const& comparator : group) {
            const auto order = version <=> comparator.version;
            switch (comparator.op) {
            case Operator::Equal:        ok = order == 0; break;
            case Operator::Greater:      ok = order > 0; break;
            case Operator::GreaterEqual: ok = order >= 0; break;
            case Operator::Less:         ok = order < 0; break;
            case Operator::LessEqual:    ok = order <= 0; break;
            }
            if (!comparator.version.preRelease.empty() && comparator.version.major == version.major &&
                comparator.version.minor == version.minor && comparator.version.patch == version.patch) {
                preReleaseAllowed = true;
            }
            if (!ok) break;
        }
        // A pre-release only matches a group that explicitly mentions one, so
        // "1.0.0-rc1" is never picked up by a plain "^1.0.0".
        if (ok && (version.preRelease.empty() || preReleaseAllowed)) return true;
    }
    return false;
}

} // namespace crosslink
