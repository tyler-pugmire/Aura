require "export-compile-commands"

include "dependencies.lua"

workspace "AuraEngine"
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

group ""
project "sandbox"
-- location "sandbox"
kind "ConsoleApp"
language "C++"
cppdialect "C++20"
staticruntime "off"

targetdir("bin/" .. outputdir .. "/%{prj.name}")
objdir("bin-int/" .. outputdir .. "/%{prj.name}")

links
{
    "Aura"
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


group "Engine"
project "Aura"
-- location "Aura"
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

links
{
    "~/project/Aura/bin/" .. outputdir .. "/GLFW/libGLFW.a",
}

group "vendor"
include "Aura/vendor/glfw"
group ""
