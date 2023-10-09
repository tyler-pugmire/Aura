project "vulkan"
do
    kind "StaticLib"
    language "C++"

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    includedirs
    {

        "Vulkan-Headers/include",
        "Vulkan-Loader/loader",
        "Vulkan-Loader/loader/generated"
    }

    files
    {
        "Vulkan-Headers/include/**.h",
        "Vulkan-Loader/loader/**.h",
        "Vulkan-Loader/loader/**.c",
    }

    filter "system:linux"
    do
        defines
        {
            "BUILD_WSI_XLIB_SUPPORT",
            "VK_USE_PLATFORM_XLIB_KHR",
            "COMMON_UNIX_PLATFORMS",
            "LOADER_ENABLE_LINUX_SORT",
            "FALLBACK_CONFIG_DIRS=\"/etc/xdg\"",
            "FALLBACK_DATA_DIRS=\"/usr/local/share:/usr/share\"",
            "SYSCONFDIR=\"\""
        }
        removefiles
        {
            "Vulkan-Loader/loader/dirent_on_windows.c",
            "Vulkan-Loader/loader/dirent_on_windows.h"
        }
    end
end
