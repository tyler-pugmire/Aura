#pragma once

#include "Aura/Core/Application.h"
#include "Aura/Core/Base.h"

extern Aura::Application *Aura::CreateApplication(int argc, char **argv);

int main(int argc, char **argv) {
  Aura::Core::Initialize();
  Aura::Application *app = Aura::CreateApplication(argc, argv);

  app->Run();
  delete app;
  Aura::Core::Shutdown();
}
