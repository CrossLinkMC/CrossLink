#include "plugin/ManifestJson.hpp"

#include <format>

namespace crosslink::plugin {
namespace {

std::string requireString(nlohmann::ordered_json const& json, std::string_view key, std::string& error) {
    if (const auto found = json.find(key); found != json.end()) {
        if (found->is_string()) return found->get<std::string>();
        error = std::format("'{}' must be a string", key);
        return {};
    }
    error = std::format("missing required field '{}'", key);
    return {};
}

std::string optionalString(nlohmann::ordered_json const& json, std::string_view key) {
    if (const auto found = json.find(key); found != json.end() && found->is_string()) return found->get<std::string>();
    return {};
}

Result<DependencyList> parseDependencies(nlohmann::ordered_json const& json, std::string_view key) {
    DependencyList dependencies;
    const auto found = json.find(key);
    if (found == json.end() || found->is_null()) return dependencies;
    if (!found->is_array()) return std::unexpected(Error{std::format("'{}' must be an array", key)});

    for (auto const& entry : *found) {
        Dependency dependency;
        if (entry.is_string()) {
            dependency.name = entry.get<std::string>();
        } else if (entry.is_object()) {
            if (const auto name = entry.find("name"); name != entry.end() && name->is_string()) {
                dependency.name = name->get<std::string>();
            } else {
                return std::unexpected(Error{std::format("each '{}' entry needs a name", key)});
            }
            if (const auto version = entry.find("version"); version != entry.end() && !version->is_null()) {
                std::string text;
                if (version->is_string()) {
                    text = version->get<std::string>();
                } else {
                    text = version->dump();
                }
                const auto requirement = VersionRequirement::parse(text);
                if (!requirement) return std::unexpected(requirement.error());
                dependency.version = *requirement;
            }
        } else {
            return std::unexpected(Error{std::format("'{}' entries must be strings or objects", key)});
        }
        if (dependency.name.empty()) return std::unexpected(Error{std::format("'{}' contains an empty name", key)});
        dependencies.push_back(std::move(dependency));
    }
    return dependencies;
}

nlohmann::ordered_json dependenciesToJson(DependencyList const& dependencies) {
    auto array = nlohmann::ordered_json::array();
    for (auto const& dependency : dependencies) {
        auto entry = nlohmann::ordered_json::object();
        entry["name"] = dependency.name;
        if (!dependency.version.empty()) entry["version"] = dependency.version.toString();
        array.push_back(std::move(entry));
    }
    return array;
}

} // namespace

PluginPlatform parsePluginPlatform(std::string_view text, PluginPlatform fallback) noexcept {
    if (text == "universal" || text.empty()) return PluginPlatform::Universal;
    if (text == "windows" || text == "win" || text == "win32") return PluginPlatform::Windows;
    if (text == "linux") return PluginPlatform::Linux;
    return fallback;
}

std::string_view pluginPlatformName(PluginPlatform platform) noexcept {
    switch (platform) {
    case PluginPlatform::Universal: return "universal";
    case PluginPlatform::Windows:   return "windows";
    case PluginPlatform::Linux:     return "linux";
    }
    return "universal";
}

PluginPlatform hostPlatform() noexcept {
#ifdef CROSSLINK_PLATFORM_WINDOWS
    return PluginPlatform::Windows;
#else
    return PluginPlatform::Linux;
#endif
}

std::string Manifest::versionString() const { return version ? version->toString() : std::string{"0.0.0"}; }

bool Manifest::compatibleWithHost() const noexcept {
    return !platform.has_value() || *platform == PluginPlatform::Universal || *platform == hostPlatform();
}

Result<Manifest> manifestFromJson(nlohmann::ordered_json const& json) {
    if (!json.is_object()) return std::unexpected(Error{"manifest must be a JSON object"});

    Manifest manifest;
    std::string error;

    manifest.name = requireString(json, "name", error);
    if (!error.empty()) return std::unexpected(Error{error});
    manifest.entry = requireString(json, "entry", error);
    if (!error.empty()) return std::unexpected(Error{error});

    if (const auto type = optionalString(json, "type"); !type.empty()) manifest.type = type;
    manifest.author = optionalString(json, "author");
    manifest.description = optionalString(json, "description");
    manifest.homepage = optionalString(json, "homepage");
    manifest.license = optionalString(json, "license");

    if (const auto found = json.find("version"); found != json.end() && !found->is_null()) {
        const auto text = found->is_string() ? found->get<std::string>() : found->dump();
        const auto version = Version::parse(text);
        if (!version) return std::unexpected(version.error());
        manifest.version = *version;
    }

    if (const auto found = json.find("platform"); found != json.end() && found->is_string()) {
        manifest.platform = parsePluginPlatform(found->get<std::string>(), PluginPlatform::Universal);
    }
    if (const auto found = json.find("passive"); found != json.end() && found->is_boolean()) {
        manifest.passive = found->get<bool>();
    }

    for (const auto* key : {"dependencies", "optionalDependencies", "conflicts", "loadBefore"}) {
        const auto parsed = parseDependencies(json, key);
        if (!parsed) return std::unexpected(parsed.error());
        if (std::string_view{key} == "dependencies") manifest.dependencies = *parsed;
        else if (std::string_view{key} == "optionalDependencies") manifest.optionalDependencies = *parsed;
        else if (std::string_view{key} == "conflicts") manifest.conflicts = *parsed;
        else manifest.loadBefore = *parsed;
    }

    if (const auto found = json.find("extraInfo"); found != json.end() && found->is_object()) {
        for (auto const& [key, value] : found->items()) {
            manifest.extraInfo[key] = value.is_string() ? value.get<std::string>() : value.dump();
        }
    }

    return manifest;
}

nlohmann::ordered_json manifestToJson(Manifest const& manifest) {
    auto json = nlohmann::ordered_json::object();
    json["name"] = manifest.name;
    json["entry"] = manifest.entry;
    json["type"] = manifest.type;
    if (manifest.version) json["version"] = manifest.version->toString();
    if (manifest.platform) json["platform"] = std::string{pluginPlatformName(*manifest.platform)};
    if (manifest.passive) json["passive"] = *manifest.passive;
    if (!manifest.author.empty()) json["author"] = manifest.author;
    if (!manifest.description.empty()) json["description"] = manifest.description;
    if (!manifest.homepage.empty()) json["homepage"] = manifest.homepage;
    if (!manifest.license.empty()) json["license"] = manifest.license;
    if (!manifest.dependencies.empty()) json["dependencies"] = dependenciesToJson(manifest.dependencies);
    if (!manifest.optionalDependencies.empty()) {
        json["optionalDependencies"] = dependenciesToJson(manifest.optionalDependencies);
    }
    if (!manifest.conflicts.empty()) json["conflicts"] = dependenciesToJson(manifest.conflicts);
    if (!manifest.loadBefore.empty()) json["loadBefore"] = dependenciesToJson(manifest.loadBefore);
    if (!manifest.extraInfo.empty()) {
        auto extra = nlohmann::ordered_json::object();
        for (auto const& [key, value] : manifest.extraInfo) extra[key] = value;
        json["extraInfo"] = std::move(extra);
    }
    return json;
}

} // namespace crosslink::plugin
