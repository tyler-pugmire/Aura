require "scripts.premake.export-compile-commands"

include "scripts/premake/dependencies.lua"
include "scripts/premake/cmake-project.lua"
include "conan_dependencies/conandeps.premake5.lua"

workspace "AuraEngine"
do
    architecture "x64"
    targetdir "build"
    startproject "sandbox"


    configurations
    {
        "Debug",
        "Profile",
        "Release"
    }

    flags
    {
        "MultiProcessorCompile"
    }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    filter "configurations:Debug"
    do
        defines { "DEBUG" }
        symbols "On"
    end

    filter "configurations:Profile"
    do
        defines { "DEBUG" }
        symbols "On"
        optimize "On"
    end

    filter "configurations:Release"
    do
        defines { "NDEBUG" }
        optimize "On"
    end

    filter "system:Linux"
    do
        defines "LINUX"
    end

    filter "system:Windows"
    do
        defines "WIN32"
    end


    group "vendor"
    --cmakeproject("glfw", "C")
    include "Aura/vendor/glfw"
    group ""

    group "Engine"
    project "Aura"
    do
        location "Aura"
        kind "StaticLib"
        cppdialect "C++latest"
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

        filter "configurations:Debug"
        do
            conan_setup("debug_x86_64", "eastl")
            conan_setup("debug_x86_64", "eabase")
            conan_setup("debug_x86_64", "spdlog")
            conan_setup("debug_x86_64", "fmt")
        end

        filter "configurations:Profile"
        do
            conan_setup("debug_x86_64", "eastl")
            conan_setup("debug_x86_64", "eabase")
            conan_setup("debug_x86_64", "spdlog")
            conan_setup("debug_x86_64", "fmt")
        end

        filter "configurations:Release"
        do
            conan_setup("release_x86_64", "eastl")
            conan_setup("release_x86_64", "eabase")
            conan_setup("release_x86_64", "spdlog")
            conan_setup("release_x86_64", "fmt")
        end

        filter "system:Windows"
        do
            includedirs
            {
                "%{IncludeDirs.Vulkan}",
            }

            links
            {
                "%{Library.Vulkan}",
                --"%{Library.VulkanUtils}",
            }
        end

        filter "system:unix"
        do
            links
            {
                "vulkan"
            }
        end
    end

    group ""
    project "sandbox"
    do
        location "sandbox"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++latest"
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

        filter "configurations:Debug"
        do
            conan_setup("debug_x86_64", "eastl")
            conan_setup("debug_x86_64", "eabase")
            conan_setup("debug_x86_64", "spdlog")
            conan_setup("debug_x86_64", "fmt")
        end

        filter "configurations:Profile"
        do
            conan_setup("debug_x86_64", "eastl")
            conan_setup("debug_x86_64", "eabase")
            conan_setup("debug_x86_64", "spdlog")
            conan_setup("debug_x86_64", "fmt")
        end

        filter "configurations:Release"
        do
            conan_setup("release_x86_64", "eastl")
            conan_setup("release_x86_64", "eabase")
            conan_setup("release_x86_64", "spdlog")
            conan_setup("release_x86_64", "fmt")
        end

        filter "system:unix"
        do
            links
            {
                "vulkan"
            }
        end
    end
end
