#pragma once

// CrossLink's plugin ABI boundary lives in crosslink_core.dll. Plugins link
// against its import library and only ever see these headers.
#if defined(_WIN32) || defined(_WIN64)
#define CROSSLINK_PLATFORM_WINDOWS 1
#endif

#if defined(CROSSLINK_PLATFORM_WINDOWS)
#define CROSSLINK_EXPORT __declspec(dllexport)
#define CROSSLINK_IMPORT __declspec(dllimport)
#else
#define CROSSLINK_EXPORT __attribute__((visibility("default")))
#define CROSSLINK_IMPORT __attribute__((visibility("default")))
#endif

#if defined(CROSSLINK_BUILDING_CORE)
#define CROSSLINK_API CROSSLINK_EXPORT
#else
#define CROSSLINK_API CROSSLINK_IMPORT
#endif

// Exported C entry points of a plugin DLL. See plugin/RegisterHelper.hpp.
#if defined(CROSSLINK_PLATFORM_WINDOWS)
#define CROSSLINK_PLUGIN_ENTRY extern "C" __declspec(dllexport)
#else
#define CROSSLINK_PLUGIN_ENTRY extern "C" __attribute__((visibility("default")))
#endif

// Bumped whenever the plugin-facing ABI changes. A plugin whose
// CROSSLINK_PLUGIN_API_VERSION differs from the host's is refused at load time.
#define CROSSLINK_PLUGIN_API_VERSION 1u
