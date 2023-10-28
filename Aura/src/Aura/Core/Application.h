#pragma once

#include <memory>

namespace Aura
{
    class Window;
    namespace Core
    {
        class Event;
        class EventSystem;
        class EventListener;
    } // namespace Core

    class Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();
        void Close();

        virtual void OnInit()
        {
        }
        virtual void OnShutdown(){};

        static inline Application &Get()
        {
            return *Instance;
        }

        Core::EventSystem &GetEventSystem()
        {
            return *m_pEventManager;
        }

    private:
        bool m_running = true;
        std::unique_ptr<Window> m_pWindow;
        static Application *Instance;
        std::unique_ptr<Core::EventSystem> m_pEventManager;
        std::unique_ptr<Core::EventListener> m_pEventListener;

        void HandleWindowClosed(Core::Event const &event);
    };
} // namespace Aura
