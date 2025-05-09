#include "Display.h"

mData player_colors[4] = {mYellow, mBlue, mGreen, mRed};

Display::Display(): GyverGFX(M_WIDTH, M_HEIGHT)
{
  m_matrix.setBrightness(100);
}

void Display::setColor(mData color)
{
  m_color = color;
}

void Display::setBrightness(uint8_t value)
{
  m_matrix.setBrightness(value);
  update();
}

void Display::dot(int x, int y, uint8_t fill)
{
  m_matrix.set(x, y, fill == 1 ? m_color : mBlack);
}

void Display::update()
{
  m_matrix.show();
}

void Display::reset()
{
  clear();
  update();
}

void Display::countdown(bool timeOnly, int time)
{
  if(!timeOnly)
  {
    clear();
    drawFrame(mWhite, 1);
  }

  if(time >= 0)
  {
    setColor(mWhite);
    setCursor(2, 4);

    if (time < 10)
    {
      print(0);
      setCursor(9, 4);
      print(time);
    }
    else 
    {
      print(time / 10);
      setCursor(9, 4);
      print(time % 10);
    }
  }

  update();
}

void Display::press(int player)
{
  clear();

  if(player >= 0)
  {
    setColor(player_colors[player % 4]);
    fill();
  }

  update();
}

void Display::falstart(int player)
{
  clear();

  if(player >= 0)
  {
    drawFrame(player_colors[player % 4], 2);
    setColor(mWhite);
    setCursor(5, 4);
    print('F');
  }

  update();
}

void Display::drawFrame(mData color, int width=1)
{
  setColor(color);
  rect(0, 0, 15, 15, true);
  setColor(mBlack);
  rect(width, width, 15-width, 15-width, true);
}

