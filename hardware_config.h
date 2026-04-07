#ifndef HARDWARE_CONFIG_H
#define HARDWARE_CONFIG_H

// LINK PARAMETERS
#define USE_UART_LINK       // Comment if UART link isn't used
#define USE_WIRELESS_LINK   // Comment if wireless link isn't used

// LED MATRIX PARAMETERS
// For NeoMatrix parameters see documentation: https://github.com/adafruit/Adafruit_NeoMatrix
#include <Adafruit_NeoMatrix.h>
#define LED_MATRIX_PIN D2
#define LED_MATRIX_HEIGHT 16
#define LED_MATRIX_WIDTH 16
#define LED_MATRIX_ROW_ORDER NEO_MATRIX_BOTTOM // or NEO_MATRIX_TOP
#define LED_MATRIX_COLUMN_ORDER NEO_MATRIX_LEFT // or NEO_MATRIX_RIGHT
#define LED_MATRIX_ORIENTATION NEO_MATRIX_ROWS // or NEO_MATRIX_COLUMNS
#define LED_MATRIX_SEQUENCE NEO_MATRIX_ZIGZAG // or NEO_MATRIX_PROGRESSIVE
#define LED_MATRIX_COLOR_ORDER NEO_GRB // or NEO_RGB, NEO_BRG, NEO_RBG
#define LED_MATRIX_FREQUENCY NEO_KHZ800 // or NEO_KHZ400

// ENCODER PARAMETERS
#define ENCODER_S1_PIN D0 // value for S1 pin for old hardware version
//#define ENCODER_S1_PIN D7
#define ENCODER_S2_PIN D6
#define ENCODER_KEY_PIN D5
#define ENCODER_ENCODER_PIN_MODE INPUT
#define ENCODER_KEY_PIN_MODE INPUT_PULLUP

#endif