workspace "AuraEngine"
architecture "x64"
targetdir "build"

configurations
{
    "Debug",
    "Release"
}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Aura"
location "Aura"
kind "ConsoleApp"
cppdialect "C++20"

targetdir("bin/" .. outputdir .. "/%{prj.name}")

objdir("bin-int/" .. outputdir .. "/%{prj.name}")

files
{
    "%{prj.name}/src/**.h",
    "%{prj.name}/src/**.cpp",
}

includedirs
{
    "%{prj.name}/src"
}
