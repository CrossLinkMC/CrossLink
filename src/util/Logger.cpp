#include "crosslink/api/Logger.hpp"

#include <cctype>
#include <chrono>
#include <cstdio>
#include <ctime>
#include <filesystem>
#include <format>
#include <fstream>
#include <map>
#include <mutex>
#include <string>

#ifdef CROSSLINK_PLATFORM_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

namespace crosslink {
namespace {

std::string_view levelTag(LogLevel level) noexcept {
    switch (level) {
    case LogLevel::Trace: return "trace";
    case LogLevel::Debug: return "debug";
    case LogLevel::Info:  return "info ";
    case LogLevel::Warn:  return "warn ";
    case LogLevel::Error: return "error";
    case LogLevel::Fatal: return "fatal";
    case LogLevel::Off:   return "off  ";
    }
    return "?    ";
}

const char* levelColor(LogLevel level) noexcept {
    switch (level) {
    case LogLevel::Trace: return "\x1b[90m";
    case LogLevel::Debug: return "\x1b[36m";
    case LogLevel::Info:  return "\x1b[32m";
    case LogLevel::Warn:  return "\x1b[33m";
    case LogLevel::Error: return "\x1b[31m";
    case LogLevel::Fatal: return "\x1b[1;31m";
    case LogLevel::Off:   return "";
    }
    return "";
}

void enableVirtualTerminal() {
#ifdef CROSSLINK_PLATFORM_WINDOWS
    static const bool enabled = [] {
        HANDLE console = ::GetStdHandle(STD_OUTPUT_HANDLE);
        if (console == nullptr || console == INVALID_HANDLE_VALUE) return false;
        DWORD mode{};
        if (::GetConsoleMode(console, &mode) == 0) return false;
        return ::SetConsoleMode(console, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING) != 0;
    }();
    (void)enabled;
#endif
}

std::string timestamp() {
    const auto now = std::chrono::system_clock::now();
    const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
    const std::time_t seconds = std::chrono::system_clock::to_time_t(now);
    std::tm local{};
#ifdef CROSSLINK_PLATFORM_WINDOWS
    ::localtime_s(&local, &seconds);
#else
    ::localtime_r(&seconds, &local);
#endif
    return std::format(
        "{:04}-{:02}-{:02} {:02}:{:02}:{:02}.{:03}",
        local.tm_year + 1900,
        local.tm_mon + 1,
        local.tm_mday,
        local.tm_hour,
        local.tm_min,
        local.tm_sec,
        ms.count()
    );
}

} // namespace

struct LoggerRegistry::Impl {
    std::recursive_mutex                           mutex;
    std::map<std::string, std::unique_ptr<Logger>> loggers;
    LogLevel                                       defaultLevel{LogLevel::Info};
    std::ofstream                                  file;
    LogLevel                                       fileLevel{LogLevel::Info};
    bool                                           color{true};
};

std::string_view logLevelName(LogLevel level) noexcept { return levelTag(level); }

LogLevel parseLogLevel(std::string_view text, LogLevel fallback) noexcept {
    std::string lowered;
    lowered.reserve(text.size());
    for (const char ch : text) lowered.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));

    if (lowered == "trace") return LogLevel::Trace;
    if (lowered == "debug") return LogLevel::Debug;
    if (lowered == "info") return LogLevel::Info;
    if (lowered == "warn" || lowered == "warning") return LogLevel::Warn;
    if (lowered == "error") return LogLevel::Error;
    if (lowered == "fatal") return LogLevel::Fatal;
    if (lowered == "off" || lowered == "none") return LogLevel::Off;
    return fallback;
}

Logger::Logger(std::string name) : mName(std::move(name)) {}

void Logger::setLevel(LogLevel level) noexcept { mLevel = level; }

void Logger::log(LogLevel level, std::string_view message) const {
    auto& impl = *LoggerRegistry::instance().mImpl;
    if (level < mLevel) return;

    enableVirtualTerminal();

    const auto line = std::format("[{}] [{}] [{}] {}", timestamp(), levelTag(level), mName, message);

    std::lock_guard lock{impl.mutex};
    std::FILE* out = level >= LogLevel::Warn ? stderr : stdout;
    if (impl.color) {
        std::fprintf(out, "%s%s\x1b[0m\n", levelColor(level), line.c_str());
    } else {
        std::fprintf(out, "%s\n", line.c_str());
    }
    std::fflush(out);

    if (impl.file.is_open() && level >= impl.fileLevel) {
        impl.file << line << '\n';
        impl.file.flush();
    }
}

LoggerRegistry::LoggerRegistry() : mImpl(std::make_unique<Impl>()) {}
LoggerRegistry::~LoggerRegistry() { closeLogFile(); }

LoggerRegistry& LoggerRegistry::instance() {
    static LoggerRegistry registry;
    return registry;
}

Logger& LoggerRegistry::getOrCreate(std::string_view name) {
    auto& impl = *mImpl;
    std::lock_guard lock{impl.mutex};
    const auto key = std::string{name};
    if (const auto found = impl.loggers.find(key); found != impl.loggers.end()) return *found->second;
    auto created = std::make_unique<Logger>(key);
    created->setLevel(impl.defaultLevel);
    auto& reference = *created;
    impl.loggers.emplace(key, std::move(created));
    return reference;
}

Logger& LoggerRegistry::get(std::string_view name) const { return const_cast<LoggerRegistry*>(this)->getOrCreate(name); }

void LoggerRegistry::forget(std::string_view name) {
    auto& impl = *mImpl;
    std::lock_guard lock{impl.mutex};
    impl.loggers.erase(std::string{name});
}

void LoggerRegistry::setLevel(LogLevel level) {
    auto& impl = *mImpl;
    std::lock_guard lock{impl.mutex};
    impl.defaultLevel = level;
    for (auto& [name, logger] : impl.loggers) logger->setLevel(level);
}

bool LoggerRegistry::setLogFile(std::string_view path, LogLevel minimum) {
    auto& impl = *mImpl;
    std::lock_guard lock{impl.mutex};
    impl.file.close();
    if (path.empty()) return true;

    std::filesystem::path file{path};
    if (file.has_parent_path()) {
        std::error_code ignored;
        std::filesystem::create_directories(file.parent_path(), ignored);
    }
    impl.file.open(file, std::ios::app);
    if (!impl.file.is_open()) return false;
    impl.fileLevel = minimum;
    return true;
}

void LoggerRegistry::closeLogFile() {
    auto& impl = *mImpl;
    std::lock_guard lock{impl.mutex};
    if (impl.file.is_open()) impl.file.close();
}

} // namespace crosslink
