#include "window.h"
#include "GLFW/glfw3.h"
#include <iostream>

namespace TEST
{
    GLFWwindow *pWindow;
    void CreateWindow()
    {
        if (!glfwInit())
        {
            std::cout << "failed to init glfw" << std::endl;
            return;
        }

        pWindow = glfwCreateWindow(800, 600, "Hello World", nullptr, nullptr);
        if (!pWindow)
        {
            std::cout << "failed to create window\n";
            glfwTerminate();
            return;
        }
    }
} // namespace TEST
