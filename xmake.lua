add_rules("mode.debug", "mode.release")

set_project("CrossLink")
set_version("0.1.0")

option("build_tests")
    set_default(true)
    set_showmenu(true)
    set_description("Build the CrossLink unit tests")
option_end()

option("build_plugins")
    set_default(true)
    set_showmenu(true)
    set_description("Build the bundled CrossLink plugins")
option_end()

-- The advertised version must match the BedrockProtocol checkout pinned in
-- xmake/deps.lua. CrossLink never rewrites a dependency's sources.
option("protocol_version")
    set_default(1001)
    set_showmenu(true)
    set_description("Bedrock network protocol version")
option_end()

option("game_version")
    set_default("26.30")
    set_showmenu(true)
    set_description("Bedrock game version advertised in the MOTD")
option_end()

-- Third-party dependencies. The git-only ones are fetched by xmake/deps.lua at
-- pinned commits into .deps/ (no submodules); the rest come from xrepo.
add_requires("nlohmann_json v3.12.0")
add_requires("fmt")
add_requires("magic_enum v0.9.7")
add_requires("boost_pfr 2.2.0")
add_requires("concurrentqueue v1.0.4")
add_requires("parallel-hashmap v2.0.0")
add_requires("cpp-httplib v0.46.0", {configs = {ssl = true, zlib = false, brotli = false, zstd = false}})
add_requires("openssl3", {configs = {shared = false}})
add_requires("zlib", {configs = {shared = false}})
add_requires("snappy", {configs = {shared = false}})

--- NOTE: dependency fetching happens inside target on_load hooks. xmake's
-- sandbox only exposes `import` there, and a closure created in the root scope
-- would keep the root environment (where `import` is nil).

-- Vendored dependency targets are third-party code: no warnings, C++23, no RTTI,
-- matching how BedrockProtocol's own CMake builds them.
target("raknet")
    set_kind("static")
    set_group("deps")
    set_languages("c++23")
    set_warnings(nil)
    add_defines("RAKNET_SUPPORT_IPV6=1", "NOMINMAX", {public = true})
    if is_plat("windows") then
        add_defines("UNICODE", "_WIN32_WINNT=0x0A00")
        add_cxflags("/utf-8", "/GR-", "/bigobj", {force = true})
        add_syslinks("ws2_32", "winmm")
    else
        add_cxflags("-fno-rtti", {force = true})
        add_syslinks("pthread")
    end
    on_load(function (target)
        local deps = import("deps", {rootdir = path.join(os.projectdir(), "xmake")})
        local root = path.join(deps.ensure(os.projectdir()), "RakNet")
        target:add("files", path.join(root, "Source/*.cpp"))
        target:add("sysincludedirs", path.join(root, "Source"), {public = true})
    end)
target_end()

target("bedrock_protocol")
    set_kind("static")
    set_group("deps")
    set_languages("c++23")
    set_warnings(nil)
    add_deps("raknet")
    add_packages(
        "openssl3",
        "zlib",
        "snappy",
        "cpp-httplib",
        "magic_enum",
        "boost_pfr",
        "fmt",
        "concurrentqueue",
        "parallel-hashmap",
        {public = true}
    )
    add_defines(
        "SCULK_PROTOCOL_ENABLE_CONNECTION",
        "CPPHTTPLIB_OPENSSL_SUPPORT",
        "CPPHTTPLIB_NO_EXCEPTIONS",
        "JSONC_NO_EXCEPTION",
        "NOMINMAX",
        {public = true}
    )
    -- PROTOCOL_ENABLE_DETAIL_ERRORS / PROTOCOL_ENABLE_FORMATTING change ErrorInfo's
    -- layout and IPacket's vtable. Both stay OFF so the library and every consumer
    -- translation unit agree on the ABI.
    if is_plat("windows") then
        add_defines("UNICODE", "_WIN32_WINNT=0x0A00")
        add_cxflags("/utf-8", "/GR-", "/Zc:preprocessor", "/permissive-", "/bigobj", {force = true})
    else
        add_cxflags("-fno-rtti", {force = true})
    end
    on_load(function (target)
        local deps = import("deps", {rootdir = path.join(os.projectdir(), "xmake")})
        local root = deps.ensure(os.projectdir())
        local protocol = path.join(root, "BedrockProtocol")
        target:add("files", path.join(protocol, "src/sculk/protocol/codec/**.cpp"))
        target:add("files", path.join(protocol, "src/sculk/protocol/auth/*.cpp"))
        target:add("files", path.join(protocol, "src/sculk/protocol/connection/**.cpp"))
        target:add("sysincludedirs", path.join(protocol, "include"), {public = true})
        target:add("sysincludedirs", path.join(root, "Reflection/include"), {public = true})
        target:add("sysincludedirs", path.join(root, "JSONC/include"), {public = true})
    end)
target_end()

--- Common settings for first-party CrossLink code.
local function crosslink_target(target)
    target:set("languages", "c++latest")
    if is_plat("windows") then
        target:add("defines", "NOMINMAX", "UNICODE", "_WIN32_WINNT=0x0A00")
        target:add("cxflags", "/utf-8", "/Zc:preprocessor", "/bigobj", "/permissive-")
        target:set("runtimes", "MD")
        target:add("syslinks", "ws2_32", "crypt32")
    else
        target:add("syslinks", "pthread")
    end
end

-- The shared core *is* the stable plugin ABI boundary: plugins link against its
-- import library and never against the vendored protocol library.
target("crosslink_core")
    set_kind("shared")
    set_group("crosslink")
    set_exceptions("cxx")
    add_files("src/**.cpp")
    add_includedirs("include", {public = true})
    add_includedirs("src")
    add_headerfiles("include/(crosslink/**.hpp)")
    add_deps("bedrock_protocol")
    add_packages("nlohmann_json", "fmt", "magic_enum")
    add_defines("CROSSLINK_BUILDING_CORE=1")
    on_load(function (target)
        crosslink_target(target)
        -- Resolved here because get_config() is only reliable once options are set.
        local protocol = tostring(get_config("protocol_version") or 1001)
        local game = tostring(get_config("game_version") or "26.30")
        local version = tostring(get_config("version") or "0.1.0")
        target:add("defines", "CROSSLINK_PROTOCOL_VERSION=" .. protocol, {public = true})
        target:add("defines", "CROSSLINK_GAME_VERSION=\"" .. game .. "\"", {public = true})
        target:add("defines", "CROSSLINK_VERSION=\"" .. version .. "\"", {public = true})
    end)
target_end()

target("crosslink")
    set_kind("binary")
    set_group("crosslink")
    add_files("launcher/**.cpp")
    add_deps("crosslink_core")
    add_includedirs("include", "src")
    add_packages("nlohmann_json")
    on_load(function (target)
        crosslink_target(target)
    end)
    -- Put the gateway next to the plugins/ and config/ trees it expects at runtime.
    after_build(function (target)
        local bindir = path.join(os.projectdir(), "bin")
        os.mkdir(bindir)
        os.cp(target:targetfile(), bindir)
        local core = target:dep("crosslink_core")
        for _, name in ipairs({core:targetfile(), core:targetfile() .. ".pdb"}) do
            if os.isfile(name) then
                os.cp(name, bindir)
            end
        end
    end)
target_end()

if has_config("build_plugins") then
    includes("plugins/*/xmake.lua")
end

if has_config("build_tests") then
    target("crosslink_tests")
        set_kind("binary")
        set_group("crosslink")
        set_default(false)
        add_files("tests/**.cpp")
        add_deps("crosslink_core")
        add_includedirs("include", "src")
        add_packages("nlohmann_json", "fmt")
        add_tests("default")
        on_load(function (target)
            crosslink_target(target)
        end)
    target_end()
end
