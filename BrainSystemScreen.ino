#include "Display.h"

#define UART_CLEANUP 0x10
#define UART_ENABLE_LED 0x20
#define UART_BLINK_LED 0x30
#define UART_ENABLE_SIGNAL 0x40
#define UART_TIME_EVENT 0x80

Matrix matrix(M_WIDTH, M_HEIGHT, ZIGZAG, LEFT_TOP, DIR_RIGHT);
Display display(matrix);

mData player_colors[4] = {mYellow, mBlue, mGreen, mRed};

int brightness = 50;

void drawFrame(mData color, int width=1)
{
  display.setColor(color);
  display.rect(0, 0, 15, 15, true);
  display.setColor(mBlack);
  display.rect(width, width, 15-width, 15-width, true);
}

void showTime(int time)
{
  display.setColor(mWhite);
  display.setCursor(2, 4);
  if (time < 10)
  {
    display.print(0);
    display.setCursor(9, 4);
    display.print(time);
  }
  else 
  {
    display.print(time / 10);
    display.setCursor(9, 4);
    display.print(time % 10);
  }
}

void setup() {
  Serial.begin(9600);
  display.setScale(1);
}

void loop() {
  int newBrightness = (analogRead(A4)) / 6 + 10;
  if (abs(newBrightness - brightness) > 5)
  {
    brightness = newBrightness;
    display.setBrightness(brightness);
    display.update();
  }
  if(Serial.available())
  {
    int data = Serial.read();
    if(data == -1)
    {
      return;
    }
    byte command = (byte)data & 0xF0;
    byte payload = (byte)data & 0x0F;
    if(command >= 0x80)
    {
      command = 0x80;
    }
    switch(command)
    {
      case UART_CLEANUP:
      {
        display.clear();
        display.update();
        break;
      }
      case UART_BLINK_LED:
      {
        display.clear();
        drawFrame(player_colors[payload % 4], 2);
        display.setColor(mWhite);
        display.setCursor(5, 4);
        display.print('F');
        display.update();
        break;
      }
      case UART_ENABLE_LED:
      {
        display.clear();
        display.setColor(player_colors[payload % 4]);
        display.fill();
        display.update();
        break;
      }
      case UART_ENABLE_SIGNAL:
      {
        display.clear();
        drawFrame(mWhite, 1);
        display.update();
        break;
      }
      case UART_TIME_EVENT:
      {
        showTime((byte)data & 0x7F);
        display.update();
        break;
      }
    }
  }
}
