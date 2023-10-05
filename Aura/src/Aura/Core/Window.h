#pragma once

#include <string>

namespace Aura
{
    struct WindowSpecification
    {
        std::string m_title = "Aura Engine";
        uint32_t m_width = 800;
        uint32_t m_height = 600;
        bool m_decorated = true;
        bool m_fullscreen = false;
        bool m_vSync = false;
    };
    class Window
    {
    public:
        void Init(const WindowSpecification &spec);
        void ProcessEvents();
    };
} // namespace Aura
