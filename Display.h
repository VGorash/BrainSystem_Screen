#ifndef DISPLAY_H
#define DISPLAY_H

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
    Display();

    
    void setBrightness(uint8_t value);

    void dot(int x, int y, uint8_t fill = GFX_FILL) override;
    void update() override;

    void reset();
    void countdown(bool timeOnly, int time = -1);
    void press(int player);
    void falstart(int player);

  private:
    void setColor(mData color);
    void drawFrame(mData color, int width=1);

  private:
    Matrix m_matrix = Matrix(M_WIDTH, M_HEIGHT, ZIGZAG, LEFT_TOP, DIR_RIGHT);
    mData m_color = mBlack;
};

#endif
