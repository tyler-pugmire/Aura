local math = require("math")

local function hash(str)
    h = 5381;

    for c in str:gmatch "." do
        h = ((h << 5) + h) + string.byte(c)
    end
    return h
end


local random = math.random
local function uuid(seed)
    math.randomseed(hash(seed))
    local template = 'xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx'
    return string.gsub(template, '[xy]', function(c)
        local v = (c == 'x') and random(0, 0xf) or random(8, 0xb)
        return string.format('%x', v)
    end)
end

local outlibs = {}
outlibs["glfw"] = "libglfw3.a"

function cmakeproject(name, lang)
    externalproject "GLFW"
    location("./bin-int/" .. name .. "/")
    uuid(uuid(name))
    kind "StaticLib"
    language(lang)

    -- filter "system:linux"
    postbuildcommands {
        "cp ./bin-int/%{name}/src/lib%{name}.a ./bin/libs/%{cfg.buildcfg}/%{outlibs[name]}",
    }

    postbuildmessage "Copying lib..."
end
