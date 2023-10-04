#include "Aura.h"
#include "Aura/EntryPoint.h"

class SandboxApp : public Aura::Application {
public:
  SandboxApp() {}

  void OnInit() {}
  void OnShutdown() {}
};

namespace Aura{
Application * CreateApplication(int argc, char** argv) {
  return new SandboxApp();
}
}
