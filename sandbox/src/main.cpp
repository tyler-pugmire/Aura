#include "Aura.h"
#include "Aura/EntryPoint.h"

#include "Aura/Core/String/CRC32.h"

#include <iostream>

class SandboxApp : public Aura::Application
{
public:
    SandboxApp()
    {
    }

    void OnInit()
    {
    }
    void OnShutdown()
    {
        std::cout << "OnShutdown" << std::endl;
    }
};

namespace Aura
{
    Application *CreateApplication(int argc, char **argv)
    {
        return new SandboxApp();
    }
} // namespace Aura
