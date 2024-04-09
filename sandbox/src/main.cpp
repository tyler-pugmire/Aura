#include "Aura.h"
#include "Aura/EntryPoint.h"

#include "Aura/Core/Event/EventManager.h"
#include "Aura/Core/String/CRC32.h"
#include "Aura/Core/Log.h"

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
#ifdef LINUX
        AURA_LOG("Sandbox", "Linux");
#elif WIN32
        AURA_LOG("Sandbox", "Windows");
#endif
    }
    void OnShutdown()
    {
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
