local VENDOR_DIR = "%{wks.location}/Aura/vendor"
VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDirs = {}
IncludeDirs["GLFW"] = "" .. VENDOR_DIR .. "/glfw/include"
IncludeDirs["Vulkan"] = "%{VULKAN_SDK}/Include"

LibraryDir = {}
LibraryDir["Vulkan"] = "%{VULKAN_SDK}/Lib"

Library = {}
Library["Vulkan"] = "%{LibraryDir.Vulkan}/vulkan-1.lib"
Library["VulkanUtils"] = "%{LibraryDir.Vulkan}/VkLayer_utils.lib"