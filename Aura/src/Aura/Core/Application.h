#pragma once

#include <memory>

namespace Aura
{
    class Window;
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

    private:
        bool m_running = true;
        std::unique_ptr<Window> m_pWindow;
        static Application *Instance;
    };
} // namespace Aura
