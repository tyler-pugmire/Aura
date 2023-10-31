#include "Aura.h"
#include "VulkanTest.h"
#include <cstring>
#include <iostream>
#include <vector>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

#include "GLFW/glfw3.h"
namespace
{
    const std::vector<char const *> s_validationLayers{"VK_LAYER_KHRONOS_validation"};

#ifdef DEBUG
    constexpr bool s_enableValidationLayers = true;
#else
    constexpr bool s_enableValidationLayers = false;
#endif

    VkInstance s_instance;
    void createInstance();
    bool checkValidationLayerSupport();
} // namespace

namespace Aura::Graphics
{
    void VulkanTest::Init()
    {
        u32 extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::cout << extensionCount << " extensions supported\n";

        createInstance();
    }

    void VulkanTest::Shutdown()
    {
        vkDestroyInstance(s_instance, nullptr);
    }
} // namespace Aura::Graphics
  //
namespace
{
    void createInstance()
    {

        if (s_enableValidationLayers && !checkValidationLayerSupport())
        {
            std::cout << "System does not support validation layers\n";
            return;
        }

        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Aura Editor";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "Aura Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        // TODO(tyler) do this without glfw
        u32 glfwExtensionCount = 0;
        char const **glfwExtensions;

        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;

        if constexpr (s_enableValidationLayers)
        {
            createInfo.enabledLayerCount = static_cast<u32>(s_validationLayers.size());
            createInfo.ppEnabledLayerNames = s_validationLayers.data();
        }
        else
        {
            createInfo.enabledLayerCount = 0;
        }

        VkResult result = vkCreateInstance(&createInfo, nullptr, &s_instance);

        if (result != VK_SUCCESS)
        {
            std::cout << "Failed to create instance\n";
        }
    }

    bool checkValidationLayerSupport()
    {
        u32 layerCount = 0;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        std::cout << "Supported instance layers\n{\n";
        for (auto const &layer : availableLayers)
        {
            std::cout << "\t" << layer.layerName << "\n";
        }
        std::cout << "}\n";

        for (auto const *layer : s_validationLayers)
        {
            bool layerFound = false;

            for (auto const &layerProperties : availableLayers)
            {
                std::cout << "Comparing " << layer << " == " << layerProperties.layerName << "\n";
                if (strcmp(layer, layerProperties.layerName) == 0)
                {
                    layerFound = true;
                    break;
                }
            }

            if (!layerFound)
            {
                return false;
            }
        }

        return true;
    }
} // namespace
