#include "Aura.h"
#include "Aura/EntryPoint.h"

#include "Aura/Core/Event/EventManager.h"
#include "Aura/Core/String/CRC32.h"

#include <iostream>

struct KeyPressed
{
    KeyPressed(int keycode) : m_keycode(keycode)
    {
    }
    int m_keycode;
};

class SandboxApp : public Aura::Application
{
public:
    SandboxApp()
    {
    }

    void OnInit()
    {
        m_pListener = std::move(GetEventSystem().CreateListener());
        m_pListener->Subscribe(Aura::Core::CRC32i("TestEvent"),
                               [](Aura::Core::Event const &e) -> void { std::cout << "Handling test event\n"; });
        m_pListener->Subscribe(Aura::Core::CRC32i("WindowClose"), [](Aura::Core::Event const &e) -> void {
            std::cout << "Handling window close event\n";
        });
        m_pListener->Subscribe(Aura::Core::CRC32i("KeyPressed"), this, &SandboxApp::handleKeyPress);

        GetEventSystem().BroadcastEvent(Aura::Core::CRC32i("TestEvent"));
        GetEventSystem().BroadcastEvent(Aura::Core::CRC32i("WindowClose"));
        GetEventSystem().BroadcastEvent<KeyPressed>(Aura::Core::CRC32i("KeyPressed"), 0);
        GetEventSystem().BroadcastEvent<KeyPressed>(Aura::Core::CRC32i("KeyPressed"), 3445);
        GetEventSystem().BroadcastEvent<KeyPressed>(Aura::Core::CRC32i("KeyPressed"), 3244);
        GetEventSystem().BroadcastEvent<KeyPressed>(Aura::Core::CRC32i("KeyPressed"), 4988);
        GetEventSystem().BroadcastEvent<KeyPressed>(Aura::Core::CRC32i("KeyPressed"), 5443);
    }
    void OnShutdown()
    {
    }

    void handleKeyPress(Aura::Core::Event const &e)
    {
        KeyPressed const key = *e.DataAs<KeyPressed>();
        std::cout << "KeyPressed: (" << key.m_keycode << ")\n";
    }

    std::unique_ptr<Aura::Core::EventListener> m_pListener;
};

namespace Aura
{
    Application *CreateApplication(int argc, char **argv)
    {
        return new SandboxApp();
    }
} // namespace Aura
