#include "MainApp.h"
#include "HalImpl.h"

using namespace vgs;

MainApp::MainApp()
{
  m_brightnessSaveTimer.setTime(5000);
  m_brightnessSaveTimer.setPeriodMode(false);
}

void MainApp::init(IHal& hal)
{

}

void MainApp::tick(IHal& hal)
{
  HalImpl* halImpl = (HalImpl*) &hal;

  link::Command command = link::Command::None;
  int data = -1;

#ifdef USE_UART_LINK
  link::ArduinoUartLink& uartLink = halImpl->getUartLink();
  command = uartLink.getCommand();
  data = uartLink.getData();
#endif

  switch(command)
  {
    case link::Command::DisplayCorrectPressSignal:
    {
      processCorrectPressSignal(hal, data);
      break;
    }
    case link::Command::DisplayFalstartPressSignal:
    {
      processFalstartPressSignal(hal, data);
      break;
    }
    case link::Command::UpdateTime:
    {
      processUpdateTime(hal, data);
      break;
    }
    case link::Command::Clear:
    {
      processClear(hal);
      break;
    }
    default:
    {
      break;
    }
  }

  ButtonState buttonState = hal.getButtonState();

  if(buttonState.start)
  {
    halImpl->setBrightness(min((int)halImpl->getBrightness() + 1, 255));
    m_brightnessSaveTimer.start(hal);
  }
  else if(buttonState.stop)
  {
    halImpl->setBrightness(max((int)halImpl->getBrightness() - 1, 1));
    m_brightnessSaveTimer.start(hal);
  }

  if(m_brightnessSaveTimer.tick(hal))
  {
    halImpl->saveBrightness();
  }
}

void MainApp::processCorrectPressSignal(IHal& hal, int player)
{
  GameDisplayInfo info;

  info.state = GameState::Press;
  info.player = player;

  hal.updateDisplay(info);
}

void MainApp::processFalstartPressSignal(IHal& hal, int player)
{
  GameDisplayInfo info;

  info.state = GameState::Falstart;
  info.player = player;

  hal.updateDisplay(info);
}

void MainApp::processUpdateTime(vgs::IHal& hal, int time)
{
  GameDisplayInfo info;

  info.state = GameState::Countdown;
  info.gameTime = time;

  hal.updateDisplay(info);
}

void MainApp::processClear(vgs::IHal& hal)
{
  GameDisplayInfo info;

  info.state = GameState::Idle;

  hal.updateDisplay(info);
}

AppChangeType MainApp::appChangeNeeded()
{
  return AppChangeType::None;
}

IApp* MainApp::createCustomApp()
{
  return nullptr;
}
