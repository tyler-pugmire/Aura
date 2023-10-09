#include "Window.h"
#include "GLFW/glfw3.h"
#include "vulkan/vulkan.h"
#include <iostream>

namespace
{
    bool s_GLFWInitialized = false;
    GLFWwindow *s_pGLFWWindow = nullptr;
} // namespace

namespace Aura
{

    void Window::Init(const WindowSpecification &spec)
    {

        if (!s_GLFWInitialized)
        {
            if (!glfwInit())
            {
                return;
            }
            s_GLFWInitialized = true;
        }
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        if (!spec.m_decorated)
        {
            glfwWindowHint(GLFW_DECORATED, false);
        }

        s_pGLFWWindow = glfwCreateWindow((int)spec.m_width, (int)spec.m_height, spec.m_title.c_str(), nullptr, nullptr);
        glfwSetWindowCloseCallback(s_pGLFWWindow, [](GLFWwindow *window) {});

        int32_t extensionCount = 0;

        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

        std::cout << extensionCount << " extensions supported\n";
    }

    void Window::ProcessEvents()
    {
        glfwPollEvents();
    }

} // namespace Aura
