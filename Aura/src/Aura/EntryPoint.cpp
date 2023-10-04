#include "EntryPoint.h"

int main(int argc, char **argv)
{
    {
        Aura::Application *app = Aura::CreateApplication(argc, argv);
        app->Run();
        delete app;
    }
    return 0;
}
