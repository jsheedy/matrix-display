#ifndef UTILS_H
#define UTILS_H

#include "constants.h"
#include "FastLED.h"

struct Point_t
{
  uint8_t x;
  uint8_t y;
};

uint16_t XY(uint8_t x, uint8_t y);

void draw_circle(CRGB *leds, uint8_t x, uint8_t y, uint8_t r, CRGB color);
void scroll_up(CRGB *leds);

#endif
