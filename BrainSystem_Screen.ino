#include "src/Framework/Core/Engine.h"

#include "HalImpl.h"
#include "MainApp.h"

using namespace vgs;
 
Engine engine(new HalImpl(), new MainApp(), nullptr);

void setup()
{
  engine.init();
}

void loop() 
{
  engine.tick();
}