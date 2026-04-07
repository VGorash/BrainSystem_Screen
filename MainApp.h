#ifndef MAIN_APP_H
#define MAIN_APP_H

#include "src/Framework/Core/App.h"
#include "src/Framework/Timer.h"

class MainApp : public vgs::IApp
{
public:
  MainApp();

  void init(vgs::IHal& hal) override;
  void tick(vgs::IHal& hal) override;

  vgs::AppChangeType appChangeNeeded() override;
  vgs::IApp* createCustomApp() override;

private:
  void processCorrectPressSignal(vgs::IHal& hal, int player);
  void processFalstartPressSignal(vgs::IHal& hal, int player);
  void processUpdateTime(vgs::IHal& hal, int time);
  void processClear(vgs::IHal& hal);

private:
  vgs::Timer m_brightnessSaveTimer;
};

#endif