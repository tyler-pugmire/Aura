#include "Application.h"

namespace Aura
{
    Application *Application::Instance = nullptr;
    Application::Application()
    {
        Instance = this;
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        OnInit();
        while (m_running)
        {
        }
        OnShutdown();
    }

    void Application::Close()
    {
        m_running = false;
    }

} // namespace Aura
