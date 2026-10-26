#include "plugin/PluginLoadPlanner.hpp"

#include <algorithm>
#include <format>
#include <functional>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace crosslink::plugin {
namespace {

struct Graph {
    std::map<std::string, std::set<std::string>> successors;
};

/// Kahn's algorithm with an alphabetical tie-break, so the load order is stable
/// across runs and across machines.
std::vector<std::string> topologicalSort(std::set<std::string> const& nodes, Graph const& graph) {
    std::map<std::string, std::size_t> incoming;
    for (auto const& node : nodes) incoming[node] = 0;
    for (auto const& [from, targets] : graph.successors) {
        if (!nodes.contains(from)) continue;
        for (auto const& to : targets) {
            if (nodes.contains(to)) ++incoming[to];
        }
    }

    std::priority_queue<std::string, std::vector<std::string>, std::greater<>> ready;
    for (auto const& [node, count] : incoming) {
        if (count == 0) ready.push(node);
    }

    std::vector<std::string> order;
    order.reserve(nodes.size());
    while (!ready.empty()) {
        auto node = ready.top();
        ready.pop();
        order.push_back(node);
        const auto found = graph.successors.find(node);
        if (found == graph.successors.end()) continue;
        for (auto const& to : found->second) {
            if (!nodes.contains(to)) continue;
            if (--incoming[to] == 0) ready.push(to);
        }
    }
    return order;
}

/// Names of every node that sits on a cycle, found with Tarjan's SCC algorithm.
std::set<std::string> cyclicNodes(std::set<std::string> const& nodes, Graph const& graph) {
    std::unordered_map<std::string, int> index;
    std::unordered_map<std::string, int> lowLink;
    std::unordered_set<std::string> onStack;
    std::vector<std::string> stack;
    std::set<std::string> cyclic;
    int nextIndex = 0;

    // Recursive descent is fine here: plugin graphs are tens of nodes at most.
    std::function<void(std::string const&)> visit = [&](std::string const& node) {
        index[node] = lowLink[node] = nextIndex++;
        stack.push_back(node);
        onStack.insert(node);

        const auto found = graph.successors.find(node);
        if (found != graph.successors.end()) {
            for (auto const& to : found->second) {
                if (!nodes.contains(to)) continue;
                if (!index.contains(to)) {
                    visit(to);
                    lowLink[node] = std::min(lowLink[node], lowLink[to]);
                } else if (onStack.contains(to)) {
                    lowLink[node] = std::min(lowLink[node], index[to]);
                }
            }
        }

        if (lowLink[node] != index[node]) return;
        std::vector<std::string> component;
        while (true) {
            auto member = stack.back();
            stack.pop_back();
            onStack.erase(member);
            component.push_back(member);
            if (member == node) break;
        }
        if (component.size() > 1) {
            for (auto const& member : component) cyclic.insert(member);
            return;
        }
        // A single node is only a cycle when it depends on itself.
        if (found != graph.successors.end() && found->second.contains(node)) cyclic.insert(node);
    };

    for (auto const& node : nodes) {
        if (!index.contains(node)) visit(node);
    }
    return cyclic;
}

} // namespace

bool PluginLoadPlanner::matchesDependency(Manifest const& target, Dependency const& dependency) {
    if (dependency.version.empty()) return true;
    if (!target.version) return false;
    return dependency.version.matches(*target.version);
}

LoadPlan PluginLoadPlanner::resolve(std::map<std::string, Manifest> const& manifests) {
    LoadPlan plan;

    auto reject = [&plan](std::string const& name, LoadIssue issue) {
        plan.rejected.insert_or_assign(name, std::move(issue));
    };

    std::map<std::string, Manifest> candidates;
    std::queue<std::string> pending;

    // Roots: everything that is not passive, in name order for determinism.
    for (auto const& [name, manifest] : manifests) {
        if (!manifest.compatibleWithHost()) {
            reject(
                name,
                {LoadIssueKind::IncompatiblePlatform,
                 std::string{pluginPlatformName(manifest.platform.value_or(PluginPlatform::Universal))},
                 std::format("plugin '{}' requires platform '{}', host is '{}", name,
                             pluginPlatformName(manifest.platform.value_or(PluginPlatform::Universal)),
                             pluginPlatformName(hostPlatform()))}
            );
            continue;
        }
        if (manifest.isPassive()) continue;
        candidates[name] = manifest;
        pending.push(name);
    }

    // Transitive closure over hard and (when satisfiable) optional dependencies.
    while (!pending.empty()) {
        const auto name = pending.front();
        pending.pop();
        const auto manifest = candidates.at(name);

        for (auto const& dependency : manifest.dependencies) {
            const auto target = manifests.find(dependency.name);
            if (target == manifests.end()) {
                reject(name, {LoadIssueKind::MissingDependency,
                              dependency.name,
                              std::format("plugin '{}' needs '{}' which was not found", name, dependency.name)});
                candidates.erase(name);
                continue;
            }
            if (!matchesDependency(target->second, dependency)) {
                reject(name, {LoadIssueKind::IncompatibleDependencyVersion,
                              dependency.name,
                              std::format("plugin '{}' needs '{}' {} but found {}", name, dependency.name,
                                          dependency.version.toString(), target->second.versionString())});
                candidates.erase(name);
                continue;
            }
            if (candidates.contains(dependency.name)) continue;
            if (!target->second.compatibleWithHost()) {
                reject(name, {LoadIssueKind::IncompatiblePlatform,
                              dependency.name,
                              std::format("dependency '{}' of plugin '{}' is not compatible with this host",
                                          dependency.name, name)});
                candidates.erase(name);
                continue;
            }
            candidates[dependency.name] = target->second;
            pending.push(dependency.name);
        }

        for (auto const& dependency : manifest.optionalDependencies) {
            const auto target = manifests.find(dependency.name);
            if (target == manifests.end()) continue;
            if (!matchesDependency(target->second, dependency)) continue;
            if (!target->second.compatibleWithHost()) continue;
            if (candidates.contains(dependency.name)) continue;
            candidates[dependency.name] = target->second;
            pending.push(dependency.name);
        }
    }

    // Conflicts: a plugin naming a present candidate as incompatible is the one
    // that gets rejected, matching LeviLamina's rule.
    std::vector<std::string> conflictCandidates;
    conflictCandidates.reserve(candidates.size());
    for (auto const& [candidateName, candidateManifest] : candidates) conflictCandidates.push_back(candidateName);

    for (auto const& name : conflictCandidates) {
        if (!candidates.contains(name)) continue;
        const auto manifest = candidates.at(name);
        for (auto const& conflict : manifest.conflicts) {
            const auto other = candidates.find(conflict.name);
            if (other == candidates.end()) continue;
            if (!matchesDependency(other->second, conflict)) continue;
            reject(name, {LoadIssueKind::Conflict,
                          conflict.name,
                          std::format("plugin '{}' conflicts with '{}'", name, conflict.name)});
            candidates.erase(name);
            break;
        }
    }

    // Ordering and rejection propagate into each other: dropping a plugin can
    // strand its dependents, which can strand theirs, and removing those can
    // break a cycle that was previously reported.
    while (true) {
        bool changed = true;
        while (changed) {
            changed = false;
            std::vector<std::string> names;
            names.reserve(candidates.size());
            for (auto const& [name, manifest] : candidates) names.push_back(name);

            for (auto const& name : names) {
                if (!candidates.contains(name)) continue;
                for (auto const& dependency : candidates.at(name).dependencies) {
                    if (candidates.contains(dependency.name)) continue;
                    const auto kind = plan.rejected.contains(dependency.name) || manifests.contains(dependency.name)
                                          ? LoadIssueKind::DependencyUnavailable
                                          : LoadIssueKind::MissingDependency;
                    reject(name, {kind,
                                  dependency.name,
                                  std::format("dependency '{}' of plugin '{}' is not loadable", dependency.name, name)});
                    candidates.erase(name);
                    changed = true;
                    break;
                }
            }
        }

        std::set<std::string> nodes;
        for (auto const& [name, manifest] : candidates) nodes.insert(name);

        Graph graph;
        for (auto const& name : nodes) {
            auto const& manifest = candidates.at(name);
            auto dependOn = [&graph, &nodes](std::string const& dependency, std::string const& dependent) {
                if (nodes.contains(dependency)) graph.successors[dependency].insert(dependent);
            };
            for (auto const& dependency : manifest.dependencies) dependOn(dependency.name, name);
            for (auto const& dependency : manifest.optionalDependencies) {
                if (nodes.contains(dependency.name) && matchesDependency(candidates.at(dependency.name), dependency)) {
                    dependOn(dependency.name, name);
                }
            }
            for (auto const& before : manifest.loadBefore) {
                if (nodes.contains(before.name) && matchesDependency(candidates.at(before.name), before)) {
                    graph.successors[name].insert(before.name);
                }
            }
        }

        auto order = topologicalSort(nodes, graph);
        if (order.size() == nodes.size()) {
            plan.order = std::move(order);
            break;
        }

        const auto cycle = cyclicNodes(nodes, graph);
        if (cycle.empty()) {
            // Should not happen; report whatever is left instead of looping.
            for (auto const& name : nodes) {
                if (std::find(order.begin(), order.end(), name) == order.end()) {
                    reject(name, {LoadIssueKind::DependencyCycle, {}, std::format("plugin '{}' is part of a dependency cycle", name)});
                    candidates.erase(name);
                }
            }
            continue;
        }

        std::string members;
        for (auto const& name : cycle) {
            if (!members.empty()) members += ", ";
            members += name;
        }
        for (auto const& name : cycle) {
            reject(name, {LoadIssueKind::DependencyCycle,
                          members,
                          std::format("dependency cycle between: {}", members)});
            candidates.erase(name);
        }
    }

    for (auto const& name : plan.order) {
        auto const& manifest = candidates.at(name);
        std::set<std::string> bound;
        for (auto const& dependency : manifest.dependencies) bound.insert(dependency.name);
        for (auto const& dependency : manifest.optionalDependencies) {
            const auto target = candidates.find(dependency.name);
            if (target != candidates.end() && matchesDependency(target->second, dependency)) {
                bound.insert(dependency.name);
            }
        }
        plan.lifecycleDependencies[name] = std::move(bound);
        plan.loadable.push_back(name);
    }

    return plan;
}

} // namespace crosslink::plugin
