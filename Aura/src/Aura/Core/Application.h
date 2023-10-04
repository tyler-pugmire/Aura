#pragma once

namespace Aura
{
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

        static Application *Instance;
    };
} // namespace Aura
