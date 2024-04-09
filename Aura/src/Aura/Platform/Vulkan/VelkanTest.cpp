#include "Aura.h"
#include "VulkanTest.h"
#include <cstring>
#include <iostream>
#include <vector>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>
#include "Aura/Core/Log.h"

#include "GLFW/glfw3.h"
namespace
{
    const std::vector<char const *> s_validationLayers{"VK_LAYER_KHRONOS_validation"};

#if defined DEBUG && WIN32
    constexpr bool s_enableValidationLayers = true;
#else
    constexpr bool s_enableValidationLayers = false;
#endif

    static VkInstance s_instance;
    static VkDebugUtilsMessengerEXT s_debugMessenger;
    void createInstance();
    bool checkValidationLayerSupport();
    std::vector<char const *> getRequiredExtensions();

    VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                 VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                 VkDebugUtilsMessengerCallbackDataEXT const *pCallbackData,
                                                 void *pUserData);
    void setupDebugMessenger();
    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerCreateInfoEXT const *pCreateInfo,
                                          VkAllocationCallbacks const *pAllocator,
                                          VkDebugUtilsMessengerEXT *pDebugMessenger);

    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger,
                                       VkAllocationCallbacks const *pAllocator);

} // namespace

namespace Aura::Graphics
{
    void VulkanTest::Init()
    {
        u32 extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        AURA_DEBUG("Graphics", "{} extensions supported", extensionCount);

        createInstance();
    }

    void VulkanTest::Shutdown()
    {
        // DestroyDebugUtilsMessengerEXT(s_instance, s_debugMessenger, nullptr);
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
            AURA_ERROR("Graphics", "System does not support validation layers");
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

        auto extentions = getRequiredExtensions();
        createInfo.enabledExtensionCount = static_cast<u32>(extentions.size());
        createInfo.ppEnabledExtensionNames = extentions.data();

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
            AURA_ERROR("Graphics", "Failed to create vulkan instance");
        }

        setupDebugMessenger();
    }

    bool checkValidationLayerSupport()
    {
        u32 layerCount = 0;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
        
        AURA_TRACE("Graphics", "Supported instance layers");
        AURA_TRACE("Graphics", "{{");
        for (auto const &layer : availableLayers)
        {
            AURA_TRACE("Graphics", "\t{}", layer.layerName);
        }
        AURA_TRACE("Graphics", "}}");

        for (auto const *layer : s_validationLayers)
        {
            bool layerFound = false;

            for (auto const &layerProperties : availableLayers)
            {
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

    std::vector<char const *> getRequiredExtensions()
    {
        // TODO(tyler) do this without glfw
        u32 glfwExtensionCount = 0;
        char const **glfwExtensions;

        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<char const *> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        if constexpr (s_enableValidationLayers)
        {
            extensions.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }
        return extensions;
    }
    VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                 VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                 VkDebugUtilsMessengerCallbackDataEXT const *pCallbackData,
                                                 void *pUserData)
    {
        AURA_DEBUG("Graphics", "{}", pCallbackData->pMessage);
        return VK_FALSE;
    }

    void setupDebugMessenger()
    {
        if constexpr (!s_enableValidationLayers)
        {
            return;
        }

        VkDebugUtilsMessengerCreateInfoEXT createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                                     VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                                     VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                                 VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                                 VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback = debugCallback;
        createInfo.pUserData = nullptr;

        if (CreateDebugUtilsMessengerEXT(s_instance, &createInfo, nullptr, &s_debugMessenger) != VK_SUCCESS)
        {
            AURA_ERROR("Graphics", "Failed to create debug callback");
        }
    }
    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerCreateInfoEXT const *pCreateInfo,
                                          VkAllocationCallbacks const *pAllocator,
                                          VkDebugUtilsMessengerEXT *pDebugMessenger)
    {
        auto func =
            (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
        if (func != nullptr)
        {
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
        }
        else
        {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }

    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger,
                                       VkAllocationCallbacks const *pAllocator)
    {
        auto func =
            (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr)
        {
            func(instance, debugMessenger, pAllocator);
        }
    }

} // namespace
