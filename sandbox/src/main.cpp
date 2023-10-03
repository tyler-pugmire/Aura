#include "Aura/Core/Application.h"
#include "Aura/EntryPoint.h"

class SandboxApp : public Aura::Application {
public:
  SandboxApp() {}

  void OnInit() {}
  void OnShutdown() {}
};

Aura::Application *Aura::CreateApplication(int argc, char **argv) {
  return new SandboxApp;
}
