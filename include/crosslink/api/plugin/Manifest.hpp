#pragma once

#include "crosslink/api/Export.hpp"
#include "crosslink/api/Version.hpp"

#include <map>
#include <optional>
#include <string>
#include <vector>

namespace crosslink::plugin {

/// One dependency edge in a manifest. An empty requirement matches any version.
struct Dependency {
    std::string        name;
    VersionRequirement version;

    [[nodiscard]] bool operator==(Dependency const& other) const { return name == other.name; }
};

using DependencyList = std::vector<Dependency>;

enum class PluginPlatform : std::uint8_t {
    Universal = 0,
    Windows   = 1,
    Linux     = 2,
};

[[nodiscard]] CROSSLINK_API PluginPlatform parsePluginPlatform(std::string_view text, PluginPlatform fallback) noexcept;
[[nodiscard]] CROSSLINK_API std::string_view pluginPlatformName(PluginPlatform platform) noexcept;
[[nodiscard]] CROSSLINK_API PluginPlatform hostPlatform() noexcept;

/// Everything `plugins/<name>/manifest.json` can express. The loader model
/// follows LeviLamina's mod manifest: identity, version, an optional platform
/// filter, a passive flag, and four dependency relation kinds.
struct CROSSLINK_API Manifest {
    std::string name;
    std::string entry;
    std::string type{"native"};

    std::optional<Version>         version;
    std::optional<PluginPlatform>  platform;
    std::optional<bool>            passive;

    std::string author;
    std::string description;
    std::string homepage;
    std::string license;

    DependencyList dependencies;
    DependencyList optionalDependencies;
    DependencyList conflicts;
    DependencyList loadBefore;

    /// Free-form string bag, so a plugin can carry its own metadata without
    /// CrossLink having to know the schema.
    std::map<std::string, std::string> extraInfo;

    [[nodiscard]] bool        isPassive() const noexcept { return passive.value_or(false); }
    [[nodiscard]] std::string versionString() const;
    [[nodiscard]] bool        compatibleWithHost() const noexcept;
};

} // namespace crosslink::plugin
