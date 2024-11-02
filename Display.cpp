#include "Display.h"

Display::Display(Matrix& matrix): GyverGFX(M_WIDTH, M_HEIGHT), m_matrix(matrix)
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
}

void Display::dot(int x, int y, uint8_t fill)
{
  m_matrix.set(x, y, fill == 1 ? m_color : mBlack);
}

void Display::update()
{
  m_matrix.show();
}