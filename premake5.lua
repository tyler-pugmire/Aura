require "scripts.premake.export-compile-commands"

include "scripts/premake/dependencies.lua"
include "scripts/premake/cmake-project.lua"

workspace "AuraEngine"
do
    architecture "x64"
    targetdir "build"
    startproject "sandbox"


    configurations
    {
        "Debug",
        "Release"
    }

    flags
    {
        "MultiProcessorCompile"
    }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    group "vendor"
    cmakeproject("glfw", "C")
    -- include "Aura/vendor/glfw"
    -- externalproject "GLFW"
    -- location "bin-int/glfw/"
    -- uuid "57940020-8E99-AEB6-271F-61E0F7F6B73B"
    -- kind "StaticLib"
    -- language "C"
    -- targetdir("bin/" .. outputdir .. "/%{prj.name}")
    group ""

    group "Engine"
    project "Aura"
    do
        location "Aura"
        kind "StaticLib"
        cppdialect "C++20"
        staticruntime "off"

        targetdir("bin/" .. outputdir .. "/%{prj.name}")
        objdir("bin-int/" .. outputdir .. "/%{prj.name}")

        files
        {
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp"
        }

        includedirs
        {
            "%{prj.name}/src",
            "%{IncludeDirs.GLFW}",
        }

        libdirs
        {
            "bin/libs/%{cfg.buildcfg}"
        }

        links
        {
            "glfw3",
        }

        prebuildcommands
        {
            "mkdir -p ../bin/libs/%{cfg.buildcfg}/",
            "cp ../bin-int/glfw/src/libglfw3.a ../bin/libs/%{cfg.buildcfg}",
        }
    end

    group ""
    project "sandbox"
    do
        location "sandbox"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++20"
        staticruntime "off"

        targetdir("bin/" .. outputdir .. "/%{prj.name}")
        objdir("bin-int/" .. outputdir .. "/%{prj.name}")

        libdirs
        {
            "bin/libs/%{cfg.buildcfg}"
        }

        links
        {
            "Aura",
            "glfw3",
        }

        files
        {
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.c",
            "%{prj.name}/src/**.hpp",
            "%{prj.name}/src/**.cpp"
        }

        includedirs
        {
            "%{prj.name}/src",
            "Aura/src",
        }
    end
end
