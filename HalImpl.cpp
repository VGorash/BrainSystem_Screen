#include "HalImpl.h"
#include "bitmaps.h"
#include "src/Framework/colors.h"

#include <LittleFS.h>

using namespace vgs;

HalImpl::HalImpl()
{
  m_matrix = new Adafruit_NeoMatrix(
    LED_MATRIX_WIDTH, LED_MATRIX_HEIGHT, LED_MATRIX_PIN,
    LED_MATRIX_ROW_ORDER + LED_MATRIX_COLUMN_ORDER + LED_MATRIX_ORIENTATION + LED_MATRIX_SEQUENCE,
    LED_MATRIX_COLOR_ORDER + LED_MATRIX_FREQUENCY
  );

#ifdef USE_UART_LINK
  m_uartLink = new link::ArduinoUartLink(&Serial, link::UartLinkVersion::V2);
#endif
}

HalImpl::~HalImpl()
{
  delete m_matrix;

#ifdef USE_UART_LINK
  delete m_uartLink;
#endif
}

void HalImpl::init()
{
  Serial.begin(9600, SERIAL_8N1);

  LittleFS.begin();
  loadBrightness();

  m_eb.init(ENCODER_S1_PIN, ENCODER_S2_PIN, ENCODER_KEY_PIN, ENCODER_ENCODER_PIN_MODE, ENCODER_KEY_PIN_MODE);

  m_matrix->begin();
  m_matrix->setBrightness(m_brightness);
  m_matrix->show();
}

void HalImpl::tick()
{
  m_eb.tick();

#ifdef USE_UART_LINK
  m_uartLink->tick();
#endif
}

void HalImpl::updateDisplay(const GameDisplayInfo& info)
{
  switch(info.state)
  {
    case GameState::Press:
    {
      vgs::Color playerColor = colorFromPlayerNumber(info.player);
      m_matrix->fillScreen(m_matrix->Color(playerColor.r, playerColor.g, playerColor.b));
      break;
    }
    case GameState::Falstart:
    {
      vgs::Color playerColor = colorFromPlayerNumber(info.player);
      m_matrix->fillScreen(m_matrix->Color(playerColor.r, playerColor.g, playerColor.b));
      m_matrix->fillRect(2, 2, 12, 12, m_matrix->Color(0, 0, 0));
      m_matrix->drawBitmap(2, 2, bitmap_falstart_en_12x12, 12, 12, m_matrix->Color(255, 255, 255));
      break;
    }
    case GameState::Countdown:
    {
      m_matrix->fillScreen(m_matrix->Color(0, 0, 0));

      if(info.gameTime < 0)
      {
        break;
      }
      if(info.gameTime < 10)
      {
        m_matrix->drawBitmap(4, 0, bitmaps_digit_8x16[info.gameTime], 8, 16, m_matrix->Color(255, 255, 255));
        break;
      }
      if(info.gameTime < 100)
      {
        int first = info.gameTime / 10;
        int second = info.gameTime % 10;
        m_matrix->drawBitmap(0, 0, bitmaps_digit_8x16[first], 8, 16, m_matrix->Color(255, 255, 255));
        m_matrix->drawBitmap(8, 0, bitmaps_digit_8x16[second], 8, 16, m_matrix->Color(255, 255, 255));
        break;
      }
      break;
    }
    case GameState::Idle:
    {
      m_matrix->fillScreen(m_matrix->Color(0, 0, 0));
      break;
    }
    default:
    {
      break;
    }
  }

  m_matrix->show();
}

ButtonState HalImpl::getButtonState()
{
  ButtonState state;

  if(m_eb.click())
  {
    state.enter = true;
  }
  if(m_eb.hold())
  {
    state.menu = true;
  }
  if(m_eb.turn())
  {
    if(m_eb.dir() < 0)
    {
      state.start = true;
    }
    else
    {
      state.stop = true;
    }
  }

  return state;
}

unsigned long HalImpl::getTimeMillis()
{
  return millis();
}

uint8_t HalImpl::getBrightness()
{
  return m_brightness;
}

void HalImpl::setBrightness(uint8_t brightness)
{
  m_brightness = brightness;
  m_matrix->setBrightness(m_brightness);
  m_matrix->show();
}

void HalImpl::loadBrightness()
{
  File file = LittleFS.open("/brightness.bin", "r");

  if (file) 
  {
    uint8_t brightness;
    file.read(&brightness, sizeof(uint8_t));
    setBrightness(brightness);
    file.close();
  }
}

void HalImpl::saveBrightness()
{
  File file = LittleFS.open("/brightness.bin", "w");

  if (file) 
  {
    file.write(&m_brightness, sizeof(uint8_t));
    file.close();
  }
}

#ifdef USE_UART_LINK
link::ArduinoUartLink& HalImpl::getUartLink()
{
  return *m_uartLink;
}
#endif
