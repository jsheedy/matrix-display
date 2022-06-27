#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "FastLED.h"

const uint8_t WIDTH  = 24;
const uint8_t HEIGHT = 24;
const uint16_t NUM_LEDS = WIDTH * HEIGHT;
const uint8_t BUTTON_PIN = 7;

// add one extra which never gets lit but
// allows XY() to fill in there
CRGB leds[NUM_LEDS + 1];
uint8_t bitboard[NUM_LEDS / 8];

#endif
