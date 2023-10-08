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
    --cmakeproject("glfw", "C")
    include "Aura/vendor/glfw"
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
            "glfw",
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
            "glfw",
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
