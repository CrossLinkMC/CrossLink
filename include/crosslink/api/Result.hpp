#pragma once

#include "crosslink/api/Export.hpp"

#include <expected>
#include <string>
#include <string_view>
#include <utility>

namespace crosslink {

// Every failure crossing the plugin boundary is a value, never an exception. The
// host still catches exceptions thrown by plugin callbacks and converts them.
struct Error {
    std::string message;

    Error() = default;
    Error(std::string_view text) : message(text) {}
    Error(const char* text) : message(text) {}

    [[nodiscard]] std::string_view what() const noexcept { return message; }
    [[nodiscard]] explicit operator bool() const noexcept { return !message.empty(); }
};

template <typename T = void>
using Result = std::expected<T, Error>;

[[nodiscard]] inline Error makeError(std::string_view message) { return Error{message}; }

// `CROSSLINK_PROPAGATE(expr)` runs expr and returns its error when it fails.
#define CROSSLINK_PROPAGATE(...)                                                                                      \
    if (auto&& crosslinkResult = (__VA_ARGS__); !crosslinkResult) {                                                    \
        return std::unexpected(::crosslink::Error{crosslinkResult.error().message});                                   \
    }

// `CROSSLINK_ASSIGN(name, expr)` binds name to the Result and returns early on
// failure; use `*name` / `name->member` to reach the value.
#define CROSSLINK_ASSIGN(name, ...)                                                                                   \
    auto&& name = (__VA_ARGS__);                                                                                       \
    if (!name) {                                                                                                       \
        return std::unexpected(::crosslink::Error{name.error().message});                                               \
    }

} // namespace crosslink
