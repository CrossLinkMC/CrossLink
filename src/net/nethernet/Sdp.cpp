#include "net/nethernet/Sdp.hpp"

#include <nlohmann/json.hpp>

#include <algorithm>
#include <cctype>
#include <charconv>
#include <format>

namespace crosslink::net::nethernet::sdp {
namespace {

using Json = nlohmann::ordered_json;

[[nodiscard]] bool startsWith(std::string_view text, std::string_view prefix) noexcept {
    return text.size() >= prefix.size() && text.compare(0, prefix.size(), prefix) == 0;
}

[[nodiscard]] std::string lower(std::string_view text) {
    std::string out{text};
    std::transform(out.begin(), out.end(), out.begin(), [](unsigned char ch) {
        return static_cast<char>(std::tolower(ch));
    });
    return out;
}

[[nodiscard]] std::string_view trim(std::string_view text) noexcept {
    while (!text.empty() && (text.front() == ' ' || text.front() == '\t')) text.remove_prefix(1);
    while (!text.empty() && (text.back() == ' ' || text.back() == '\t')) text.remove_suffix(1);
    return text;
}

[[nodiscard]] std::string join(std::vector<std::string> const& parts) {
    std::string out;
    for (auto const& part : parts) {
        out += part;
        out += "\r\n";
    }
    return out;
}

constexpr std::string_view kIdentityPrefix = "a=identity:";
constexpr std::string_view kFingerprintPrefix = "a=fingerprint:";
constexpr std::string_view kMaxMessageSizePrefix = "a=max-message-size:";

} // namespace

std::vector<std::string> lines(std::string_view text) {
    std::vector<std::string> out;
    std::size_t start = 0;
    while (start <= text.size()) {
        const auto end = text.find('\n', start);
        auto line = end == std::string_view::npos ? text.substr(start) : text.substr(start, end - start);
        if (!line.empty() && line.back() == '\r') line.remove_suffix(1);
        if (!line.empty()) out.emplace_back(line);
        if (end == std::string_view::npos) break;
        start = end + 1;
    }
    return out;
}

std::vector<Fingerprint> fingerprints(std::string_view text) {
    std::vector<Fingerprint> out;
    for (auto const& line : lines(text)) {
        const std::string_view view{line};
        if (!startsWith(lower(view), kFingerprintPrefix)) continue;
        const auto value = trim(view.substr(kFingerprintPrefix.size()));
        const auto space = value.find(' ');
        if (space == std::string_view::npos) continue;
        Fingerprint fingerprint;
        fingerprint.algorithm = lower(trim(value.substr(0, space)));
        fingerprint.digest = std::string{trim(value.substr(space + 1))};
        if (fingerprint.algorithm.empty() || fingerprint.digest.empty()) continue;
        out.push_back(std::move(fingerprint));
    }
    return out;
}

std::string fingerprintJson(std::string_view text) {
    auto found = fingerprints(text);
    std::sort(found.begin(), found.end());

    Json entries = Json::array();
    for (auto const& fingerprint : found) {
        Json entry;
        entry["algorithm"] = fingerprint.algorithm;
        entry["digest"] = fingerprint.digest;
        entries.push_back(std::move(entry));
    }
    Json root;
    root["fingerprint"] = std::move(entries);
    return root.dump();
}

std::optional<std::string> identity(std::string_view text) {
    for (auto const& line : lines(text)) {
        const std::string_view view{line};
        if (startsWith(lower(view), kIdentityPrefix)) {
            return std::string{trim(view.substr(kIdentityPrefix.size()))};
        }
    }
    return std::nullopt;
}

std::string withoutIdentity(std::string_view text) {
    std::vector<std::string> kept;
    for (auto const& line : lines(text)) {
        if (startsWith(lower(std::string_view{line}), kIdentityPrefix)) continue;
        kept.push_back(line);
    }
    return join(kept);
}

std::string withIpCandidates(std::string_view text) {
    std::vector<std::string> kept;
    std::size_t candidates = 0;
    for (auto const& line : lines(text)) {
        const std::string_view view{line};
        if (startsWith(view, "a=candidate:")) {
            if (candidates >= 32) continue;
            // foundation component transport priority address port typ type ...
            std::vector<std::string_view> tokens;
            auto rest = view.substr(12);
            while (!rest.empty()) {
                const auto space = rest.find(' ');
                tokens.push_back(rest.substr(0, space));
                if (space == std::string_view::npos) break;
                rest.remove_prefix(space + 1);
            }
            if (tokens.size() < 8 || tokens[6] != "typ") continue;
            const auto address = tokens[4];
            const bool ipv4 = address.find('.') != std::string_view::npos
                           && address.find_first_not_of("0123456789.") == std::string_view::npos;
            const bool ipv6 = address.find(':') != std::string_view::npos;
            if (!ipv4 && !ipv6) continue;
            ++candidates;
        }
        kept.push_back(line);
    }
    return join(kept);
}

std::string withIdentity(std::string_view text, std::string_view value) {
    auto parts = lines(text);
    const auto firstMedia = std::find_if(parts.begin(), parts.end(), [](std::string const& line) {
        return startsWith(line, "m=");
    });
    parts.insert(firstMedia, std::format("{}{}", kIdentityPrefix, value));
    return join(parts);
}

std::string withMaxMessageSize(std::string_view text, std::uint32_t size) {
    auto parts = lines(text);
    const std::string replacement = std::format("{}{}", kMaxMessageSizePrefix, size);
    bool replaced = false;
    for (auto& line : parts) {
        if (startsWith(lower(std::string_view{line}), kMaxMessageSizePrefix)) {
            line = replacement;
            replaced = true;
        }
    }
    if (!replaced) {
        const auto sctpPort = std::find_if(parts.begin(), parts.end(), [](std::string const& line) {
            return startsWith(line, "a=sctp-port:");
        });
        if (sctpPort != parts.end()) {
            parts.insert(sctpPort + 1, replacement);
        } else {
            parts.push_back(replacement);
        }
    }
    return join(parts);
}

std::optional<std::uint32_t> maxMessageSize(std::string_view text) {
    for (auto const& line : lines(text)) {
        const std::string_view view{line};
        if (!startsWith(lower(view), kMaxMessageSizePrefix)) continue;
        const auto value = trim(view.substr(kMaxMessageSizePrefix.size()));
        std::uint32_t size = 0;
        const auto* end = value.data() + value.size();
        const auto result = std::from_chars(value.data(), end, size);
        if (result.ec == std::errc{} && result.ptr == end) return size;
    }
    return std::nullopt;
}

std::optional<std::string> iceUfrag(std::string_view text) {
    for (auto const& line : lines(text)) {
        const std::string_view view{line};
        if (startsWith(view, "a=ice-ufrag:")) return std::string{trim(view.substr(12))};
    }
    return std::nullopt;
}

} // namespace crosslink::net::nethernet::sdp