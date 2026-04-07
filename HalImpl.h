#ifndef HAL_IMPL_H
#define HAL_IMPL_H

#include <EncButton.h>

#include "hardware_config.h"
#include "src/Framework/Core/Hal.h"

#ifdef USE_UART_LINK
  #define USE_ARDUINO_UART_LINK
  #include "src/Link/ArduinoUartLink.h"
#endif

class HalImpl : public vgs::IHal
{
public:
  HalImpl();
  ~HalImpl() override;

  void init() override;
  void tick() override;

  //buttons
  vgs::ButtonState getButtonState() override;

  //leds (NOT NEEDED FOR THIS IMPL)
  void correctPressSignal(int player) override {};
  void falstartPressSignal(int player) override {};
  void pendingPressSignal(int player) override {};
  void gameStartSignal() override {};
  void clearSignals() override {};

  //sound (NOT NEEDED FOR THIS IMPL)
  void sound(vgs::HalSound soundType) override {};
  void sound(unsigned int frequency, unsigned int duration) override {};

  //display
  void updateDisplay(const vgs::GameDisplayInfo& info) override;
  void updateDisplay(const vgs::CustomDisplayInfo& info) override {};

  //time
  unsigned long getTimeMillis() override;

  //brightness
  uint8_t getBrightness();
  void setBrightness(uint8_t brightness);
  void loadBrightness();
  void saveBrightness();

#ifdef USE_UART_LINK
  vgs::link::ArduinoUartLink& getUartLink();
#endif

private:  
  EncButton m_eb;
  Adafruit_NeoMatrix* m_matrix;

#ifdef USE_UART_LINK
  vgs::link::ArduinoUartLink* m_uartLink;
#endif

  uint8_t m_brightness = 10;
};

#endif