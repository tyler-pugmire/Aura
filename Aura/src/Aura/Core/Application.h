#pragma once

#include <memory>

namespace Aura
{
    class Window;
    namespace Core
    {
        class EventSystem;
    }

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
    };
} // namespace Aura
