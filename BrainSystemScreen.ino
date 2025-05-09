#include "Display.h"

#define USE_ARDUINO_UART_LINK
#include "src/Link/ArduinoUartLink.h"

#define BRIGHTNESS_PIN A4

using namespace vgs::link;

enum State
{
  Idle,
  Countdown,
  Press,
  Falstart
};

Display display;
ArduinoUartLink link(&Serial);
State state;

int brightness = 100;

void setup() {
  Serial.begin(9600);
  display.setScale(1);

  pinMode(5, OUTPUT);
  digitalWrite(5, 1);
  delay(1000);
  digitalWrite(5, 0);
}

void loop() {
  int newBrightness = (1024 - analogRead(BRIGHTNESS_PIN)) / 6 + 10;
  if (abs(newBrightness - brightness) > 5)
  {
    brightness = newBrightness;
    display.setBrightness(brightness);
    display.update();
  }

  link.tick();

  switch(link.getCommand())
  {
    case Command::LedsOff:
    {
      if(state != Idle)
      {
        state = Idle;
        display.reset();
      }
    }
    break;

    case Command::PlayerLedOn:
    case Command::DisplayPlayerLedOn:
    {
      if(state == Countdown || state == Idle)
      {
        state = Press;
        display.press(link.getData());
      }
    }
    break;

    case Command::PlayerLedBlink:
    case Command::DisplayPlayerLedBlink:
    {
      if(state == Idle)
      {
        state = Falstart;
        display.falstart(link.getData());
      }
    }
    break;

    case Command::SignalLedOn:
    {
      if(state == Idle)
      {
        state = Countdown;
        display.countdown(false);
      }
    }
    break; 

    case Command::UpdateTime:
    {
      if(state == Countdown)
      {
        display.countdown(true, link.getData());
      }
    }
    break; 
  }
}
