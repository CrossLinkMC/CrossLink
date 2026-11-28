#pragma once

// SDP text handling for NetherNet. The WebRTC engine owns the negotiation, so
// everything NetherNet adds on top — the a=identity envelope, the message-size
// floor, the fingerprint digest an assertion signs — is done to the SDP string
// on its way in or out, never inside the engine's own state.

#include "crosslink/api/Result.hpp"
#include "crosslink/api/Types.hpp"

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace crosslink::net::nethernet::sdp {

/// One `a=fingerprint` line, split into its two halves.
struct Fingerprint {
    std::string algorithm;
    std::string digest;

    [[nodiscard]] auto operator<=>(Fingerprint const&) const = default;
};

[[nodiscard]] std::vector<Fingerprint> fingerprints(std::string_view text);

/// The canonical JSON an identity assertion signs: every fingerprint in the SDP,
/// sorted by (algorithm, digest). Signing the SDP lines themselves does not work.
[[nodiscard]] std::string fingerprintJson(std::string_view text);

[[nodiscard]] std::optional<std::string> identity(std::string_view text);

/// Removes every a=identity line, which a WebRTC stack must not be asked to parse.
[[nodiscard]] std::string withoutIdentity(std::string_view text);

/// Keeps only candidates whose address is an IP literal, at most 32 of them.
/// A client may offer mDNS `.local` names, and one unparseable candidate makes
/// the whole description fail.
[[nodiscard]] std::string withIpCandidates(std::string_view text);

/// Inserts a=identity immediately before the first m= line, where NetherNet puts it.
[[nodiscard]] std::string withIdentity(std::string_view text, std::string_view value);

/// Replaces or adds a=max-message-size in every m-section.
[[nodiscard]] std::string withMaxMessageSize(std::string_view text, std::uint32_t size);

[[nodiscard]] std::optional<std::uint32_t> maxMessageSize(std::string_view text);

/// The ICE ufrag the local side answers to; a session is identified by it.
[[nodiscard]] std::optional<std::string> iceUfrag(std::string_view text);

[[nodiscard]] std::vector<std::string> lines(std::string_view text);

} // namespace crosslink::net::nethernet::sdp