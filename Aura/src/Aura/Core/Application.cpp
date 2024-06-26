#include "Application.h"
#include "Aura/Core/Event/EventManager.h"
#include "Aura/Core/Window.h"
#include "Aura/Platform/Vulkan/VulkanTest.h"
#include "Aura/Core/Log.h"

namespace Aura
{
    Application *Application::Instance = nullptr;
    Application::Application()
    {
        Instance = this;

        Log::Init();
        m_pWindow = std::make_unique<Window>();
        WindowSpecification spec;
        m_pWindow->Init(spec);

        m_pEventManager = std::make_unique<Core::EventSystem>();
        m_pEventListener = std::move(m_pEventManager->CreateListener());

        m_pEventListener->Subscribe(WindowEvent::Closed, this, &Application::HandleWindowClosed);

        Graphics::VulkanTest::Init();
    }

    Application::~Application()
    {
        m_pWindow.reset();
        Log::Shutdown();
    }

    void Application::Run()
    {
        OnInit();
        while (m_running)
        {
            m_pWindow->ProcessEvents();
            
            m_pEventManager->Dispatch();
        }
        OnShutdown();
    }

    void Application::Close()
    {
        m_running = false;
    }

    void Application::HandleWindowClosed(Core::Event const &event)
    {
        m_running = false;
    }
} // namespace Aura
