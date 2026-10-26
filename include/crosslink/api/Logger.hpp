#pragma once

#include "crosslink/api/Export.hpp"

#include <format>
#include <memory>
#include <string>
#include <string_view>

namespace crosslink {

enum class LogLevel : int {
    Trace = 0,
    Debug = 1,
    Info  = 2,
    Warn  = 3,
    Error = 4,
    Fatal = 5,
    Off   = 6,
};

[[nodiscard]] CROSSLINK_API std::string_view logLevelName(LogLevel level) noexcept;
[[nodiscard]] CROSSLINK_API LogLevel         parseLogLevel(std::string_view text, LogLevel fallback = LogLevel::Info) noexcept;

/// Formatting happens in the caller's translation unit so that no formatter
/// instantiation ever crosses the DLL boundary; only the finished string does.
class CROSSLINK_API Logger {
public:
    explicit Logger(std::string name);

    [[nodiscard]] std::string_view name() const noexcept { return mName; }

    void      setLevel(LogLevel level) noexcept;
    [[nodiscard]] LogLevel level() const noexcept { return mLevel; }

    void log(LogLevel level, std::string_view message) const;

    template <typename... Args>
    void trace(std::format_string<Args...> fmt, Args&&... args) const {
        log(LogLevel::Trace, std::format(fmt, std::forward<Args>(args)...));
    }

    template <typename... Args>
    void debug(std::format_string<Args...> fmt, Args&&... args) const {
        log(LogLevel::Debug, std::format(fmt, std::forward<Args>(args)...));
    }

    template <typename... Args>
    void info(std::format_string<Args...> fmt, Args&&... args) const {
        log(LogLevel::Info, std::format(fmt, std::forward<Args>(args)...));
    }

    template <typename... Args>
    void warn(std::format_string<Args...> fmt, Args&&... args) const {
        log(LogLevel::Warn, std::format(fmt, std::forward<Args>(args)...));
    }

    template <typename... Args>
    void error(std::format_string<Args...> fmt, Args&&... args) const {
        log(LogLevel::Error, std::format(fmt, std::forward<Args>(args)...));
    }

    template <typename... Args>
    void fatal(std::format_string<Args...> fmt, Args&&... args) const {
        log(LogLevel::Fatal, std::format(fmt, std::forward<Args>(args)...));
    }

private:
    std::string mName;
    LogLevel    mLevel{LogLevel::Info};
};

/// Owns one logger per subsystem and per plugin, mirroring how LeviLamina hands
/// every mod its own named logger.
class CROSSLINK_API LoggerRegistry {
public:
    LoggerRegistry(LoggerRegistry const&)            = delete;
    LoggerRegistry& operator=(LoggerRegistry const&) = delete;

    [[nodiscard]] static LoggerRegistry& instance();
    [[nodiscard]] Logger& getOrCreate(std::string_view name);
    [[nodiscard]] Logger& get(std::string_view name) const;
    void                  forget(std::string_view name);

    /// Applied to loggers created afterwards and to every existing one.
    void setLevel(LogLevel level);

    /// Mirrors everything at or above the given level into a file.
    [[nodiscard]] bool setLogFile(std::string_view path, LogLevel minimum = LogLevel::Info);
    void               closeLogFile();

private:
    friend class Logger;

    LoggerRegistry();
    ~LoggerRegistry();

    struct Impl;
    std::unique_ptr<Impl> mImpl;
};

[[nodiscard]] inline Logger& logger(std::string_view name) { return LoggerRegistry::instance().getOrCreate(name); }

} // namespace crosslink
