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

-- The advertised version must match the codecs vendored in
-- third_party/bedrock-protocol. CrossLink never rewrites a dependency's sources.
option("protocol_version")
    set_default(2225)
    set_showmenu(true)
    set_description("Bedrock network protocol version")
option_end()

option("game_version")
    set_default("1.26.60")
    set_showmenu(true)
    set_description("Bedrock game version advertised in the MOTD")
option_end()

add_requires("nlohmann_json v3.12.0")
add_requires("fmt")
add_requires("magic_enum v0.9.7")
add_requires("openssl3", {configs = {shared = false}})
add_requires("zlib", {configs = {shared = false}})
add_requires("snappy", {configs = {shared = false}})
-- NetherNet is WebRTC. libdatachannel carries ICE/DTLS/SCTP/DCEP; the
-- NetherNet-specific signalling, SDP and framing live in src/net/nethernet.
-- media=false builds the data-channel-only library, which is all Bedrock uses.
add_requires("libdatachannel v0.24.6", {configs = {shared = false, media = false, websocket = false}})

-- Bedrock packet codecs. Vendored as pre-generated C++ (third_party/bedrock-protocol/
-- VENDOR.md), so unlike a checkout of the upstream repo this needs no Python at build
-- time. STL-only: no xrepo packages.
target("bedrock_codec")
    set_kind("static")
    set_group("deps")
    set_languages("c++23")
    set_warnings(nil)
    if is_plat("windows") then
        add_cxflags("/utf-8", "/bigobj", {force = true})
    end
    add_sysincludedirs("third_party/bedrock-protocol/include", {public = true})
    add_sysincludedirs("third_party/bedrock-protocol/generated/include", {public = true})
    add_files("third_party/bedrock-protocol/generated/include/bedrock/protocol/*.cpp")
target_end()

--- Common settings for first-party CrossLink code.
local function crosslink_target(target)
    target:set("languages", "c++latest")
    if is_plat("windows") then
        target:add("defines", "NOMINMAX", "UNICODE", "_WIN32_WINNT=0x0A00")
        target:add("cxflags", "/utf-8", "/Zc:preprocessor", "/bigobj", "/permissive-")
        target:set("runtimes", "MD")
        target:add("syslinks", "ws2_32", "crypt32", "iphlpapi")
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
    add_deps("bedrock_codec")
    add_packages("nlohmann_json", "fmt", "magic_enum", "openssl3", "zlib", "snappy", "libdatachannel")
    add_defines("CROSSLINK_BUILDING_CORE=1")
    on_load(function (target)
        crosslink_target(target)
        -- Resolved here because get_config() is only reliable once options are set.
        local protocol = tostring(get_config("protocol_version") or 2225)
        local game = tostring(get_config("game_version") or "1.26.60")
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