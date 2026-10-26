#include "app/Application.hpp"

#include <atomic>
#include <chrono>
#include <csignal>
#include <cstdio>
#include <iostream>
#include <string>
#include <string_view>
#include <thread>

#ifdef CROSSLINK_PLATFORM_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

namespace {

std::atomic_bool g_stopRequested{false};

void requestStop() { g_stopRequested.store(true); }

#ifdef CROSSLINK_PLATFORM_WINDOWS
BOOL WINAPI consoleHandler(DWORD controlType) {
    switch (controlType) {
    case CTRL_C_EVENT:
    case CTRL_BREAK_EVENT:
    case CTRL_CLOSE_EVENT:
    case CTRL_LOGOFF_EVENT:
    case CTRL_SHUTDOWN_EVENT:
        requestStop();
        return TRUE;
    default:
        return FALSE;
    }
}
#endif

void printUsage(std::string_view program) {
    std::cout << "CrossLink - a packet forwarding gateway for Minecraft Bedrock server meshes\n\n"
              << "Usage: " << program << " [options] [config.json]\n\n"
              << "Options:\n"
              << "  -c, --config <path>   configuration file (default: config/crosslink.json)\n"
              << "      --dump-config     write a default configuration to the path and exit\n"
              << "  -v, --version         print version information and exit\n"
              << "  -h, --help            print this help and exit\n\n"
              << "The gateway itself only routes protocol packets between one lobby server and N\n"
              << "sub servers. Behaviour such as seamless cross-server transfer is provided by\n"
              << "plugins loaded from the configured plugin directory.\n";
}

} // namespace

int main(int argc, char** argv) {
#ifdef CROSSLINK_PLATFORM_WINDOWS
    ::SetConsoleCtrlHandler(consoleHandler, TRUE);
#else
    std::signal(SIGINT, [](int) { requestStop(); });
    std::signal(SIGTERM, [](int) { requestStop(); });
#endif

    std::string configPath = "config/crosslink.json";
    bool dumpConfig = false;

    for (int index = 1; index < argc; ++index) {
        const std::string_view argument{argv[index]};
        if (argument == "-h" || argument == "--help") {
            printUsage(argv[0]);
            return 0;
        }
        if (argument == "-v" || argument == "--version") {
            std::cout << "CrossLink " << CROSSLINK_VERSION << " (plugin API " << CROSSLINK_PLUGIN_API_VERSION
                      << ", protocol " << CROSSLINK_PROTOCOL_VERSION << ", game " << CROSSLINK_GAME_VERSION << ")\n";
            return 0;
        }
        if (argument == "--dump-config") {
            dumpConfig = true;
            continue;
        }
        if (argument == "-c" || argument == "--config") {
            if (index + 1 >= argc) {
                std::cerr << "--config needs a path\n";
                return 64;
            }
            configPath = argv[++index];
            continue;
        }
        if (argument.starts_with("-")) {
            std::cerr << "unknown option: " << argument << "\n";
            printUsage(argv[0]);
            return 64;
        }
        configPath = argument;
    }

    if (dumpConfig) {
        const auto saved = crosslink::config::saveFile(crosslink::config::defaultConfig(), configPath);
        if (!saved) {
            std::cerr << "cannot write " << configPath << ": " << saved.error().message << '\n';
            return 73;
        }
        std::cout << "wrote a default configuration to " << configPath << '\n';
        return 0;
    }

    crosslink::Application application;
    if (auto initialized = application.initialize(configPath); !initialized) {
        std::cerr << "initialization failed: " << initialized.error().message << '\n';
        return 78;
    }
    if (auto started = application.start(); !started) {
        std::cerr << "start-up failed: " << started.error().message << '\n';
        application.stop();
        return 70;
    }

    auto& logger = application.gateway().logger();
    logger.info("gateway is running; press Ctrl+C to stop");

    while (!g_stopRequested.load()) std::this_thread::sleep_for(std::chrono::milliseconds(100));

    logger.info("shutting down");
    application.stop();
    return 0;
}
