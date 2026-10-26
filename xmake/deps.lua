-- Submodule-free dependency fetching.
--
-- BedrockProtocol and the three git-only libraries it needs have no xrepo
-- package, so they are cloned at pinned commits into .deps/ by xmake itself.
-- Everything else comes from xrepo through add_requires() in xmake.lua.
--
-- This module is imported from target on_load hooks, where xmake's sandbox
-- exposes the full Lua API (import/os.execv/try).

local pinned = {
    {
        name   = "BedrockProtocol",
        url    = "https://github.com/SculkCatalystMC/BedrockProtocol.git",
        commit = "e61289fb9fa27d8085074f1d5856772cca9bd04d",
    },
    {
        name   = "RakNet",
        url    = "https://github.com/SculkCatalystMC/RakNet.git",
        commit = "9a42fd9b6e25fd5cdc5829ceaedfc06a6404e6d3",
    },
    {
        name   = "Reflection",
        url    = "https://github.com/SculkCatalystMC/Reflection.git",
        commit = "0ba47f0d8eefac0d37e6cfbe309badb5b7d34a4a",
    },
    {
        name   = "JSONC",
        url    = "https://github.com/SculkCatalystMC/JSONC.git",
        commit = "d6467789ff1f643829e9a912638dff5be0a95386",
    },
}

local cached = nil

local function head_commit(dir)
    if not os.isdir(path.join(dir, ".git")) then
        return nil
    end
    -- xmake's sandboxed try returns the block result on success and nothing on
    -- failure, so a nil here means "git could not tell us".
    local out = try {
        function ()
            return os.iorunv("git", {"rev-parse", "HEAD"}, {curdir = dir})
        end,
        catch {
            function ()
            end
        },
    }
    if type(out) ~= "string" then
        return nil
    end
    return (out:gsub("%s+$", ""))
end

local function fetch(dep, rootdir)
    local dir = path.join(rootdir, ".deps", dep.name)
    if head_commit(dir) == dep.commit then
        return dir
    end

    cprint("=> fetching ${bright}%s${clear} @ %s", dep.name, dep.commit:sub(1, 12))
    if os.isdir(dir) then
        os.rm(dir)
    end
    os.mkdir(dir)

    local function run(...)
        os.execv("git", {...}, {curdir = dir})
    end

    run("init", "-q", ".")
    run("remote", "add", "origin", dep.url)
    -- GitHub allows fetching an arbitrary sha with depth 1, which keeps the
    -- checkout small while still pinning the commit exactly.
    run("fetch", "-q", "--depth", "1", "origin", dep.commit)
    run("checkout", "-q", "FETCH_HEAD")

    if head_commit(dir) ~= dep.commit then
        raise("dependency %s did not check out at %s", dep.name, dep.commit)
    end
    return dir
end

--- Ensures every pinned dependency is present and returns the .deps root.
-- Offline builds work as long as .deps/ is already populated.
function ensure(rootdir)
    if cached then
        return cached
    end
    for _, dep in ipairs(pinned) do
        local failure = nil
        local result = try {
            function ()
                return fetch(dep, rootdir)
            end,
            catch {
                function (errors)
                    failure = tostring(errors)
                end
            },
        }
        if not result then
            raise(
                "cannot fetch dependency %s from %s: %s\nclone it manually into %s at commit %s",
                dep.name,
                dep.url,
                failure or "unknown git error",
                path.join(rootdir, ".deps", dep.name),
                dep.commit
            )
        end
    end
    cached = path.join(rootdir, ".deps")
    return cached
end

function list()
    return pinned
end
