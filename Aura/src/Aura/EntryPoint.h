#pragma once
namespace Aura {
	extern Application* CreateApplication(int argc, char** argv);
}
bool g_ApplicationRunning = true;

int main(int argc, char** argv)
{
	while (g_ApplicationRunning)
	{
		Aura::Application* app = Aura::CreateApplication(argc, argv);
		app->Run();
		delete app;
	}
	return 0;
}
