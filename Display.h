#pragma once

#define M_PIN 7
#define M_WIDTH 16
#define M_HEIGHT 16
#define NUM_LEDS (M_WIDTH * M_HEIGHT)

#include <microLED.h>
#include <GyverGFX.h>

#define Matrix microLED<NUM_LEDS, M_PIN, MLED_NO_CLOCK, LED_WS2812, ORDER_GRB, CLI_AVER, SAVE_MILLIS>

class Display : public GyverGFX
{
  public:
    Display(Matrix& matrix);

    void setColor(mData color);
    void setBrightness(uint8_t value);

    void dot(int x, int y, uint8_t fill = GFX_FILL) override;
    void update() override;

  private:
    Matrix& m_matrix;
    mData m_color = mBlack;
};