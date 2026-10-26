#pragma once

#include "crosslink/api/Result.hpp"
#include "crosslink/api/plugin/Manifest.hpp"

#include <nlohmann/json.hpp>

namespace crosslink::plugin {

/// Manifest JSON <-> struct. Kept out of the public headers so that plugins do
/// not need a JSON library to describe themselves.
[[nodiscard]] Result<Manifest> manifestFromJson(nlohmann::ordered_json const& json);
[[nodiscard]] nlohmann::ordered_json manifestToJson(Manifest const& manifest);

} // namespace crosslink::plugin
