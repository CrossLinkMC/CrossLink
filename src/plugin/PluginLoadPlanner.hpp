#pragma once

#include "crosslink/api/plugin/Manifest.hpp"

#include <map>
#include <set>
#include <string>
#include <vector>

namespace crosslink::plugin {

enum class LoadIssueKind {
    MissingDependency,
    IncompatibleDependencyVersion,
    IncompatiblePlatform,
    Conflict,
    DependencyUnavailable,
    DependencyCycle,
    InvalidManifest,
};

struct LoadIssue {
    LoadIssueKind kind{LoadIssueKind::InvalidManifest};
    std::string   related;
    std::string   message;
};

/// What one resolution pass decided. Rejections carry a reason so the host can
/// tell the operator why a plugin did not load instead of silently skipping it.
struct LoadPlan {
    std::vector<std::string>                     order;
    std::vector<std::string>                     loadable;
    std::map<std::string, std::set<std::string>> lifecycleDependencies;
    std::map<std::string, LoadIssue>             rejected;
};

/// Pure dependency resolution, modelled on LeviLamina's ModLoadPlanner.
///
/// Roots are the non-passive manifests; passive ones only join when something
/// depends on them. The result is a deterministic load order (alphabetical
/// tie-breaks) with cycles detected and rejected as a whole.
class PluginLoadPlanner {
public:
    [[nodiscard]] static bool matchesDependency(Manifest const& target, Dependency const& dependency);

    [[nodiscard]] static LoadPlan resolve(std::map<std::string, Manifest> const& manifests);
};

} // namespace crosslink::plugin
