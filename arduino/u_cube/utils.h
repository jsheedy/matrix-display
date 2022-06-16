#ifndef UTILS_H
#define UTILS_H

#include "constants.h"

uint16_t XY_im(uint8_t x, uint8_t y)
{
  return (uint16_t)(x)*WIDTH + y;
}

uint16_t XY(uint8_t x, uint8_t y) {
    if (x % 2 == 0) {
      return XY_im(x, y);
    } else {
      return ((uint16_t)(x)+1) * WIDTH - 1 - y;
    }
}

void draw_circle(uint8_t x, uint8_t y, uint8_t r, CRGB color) {
  long r2 = r<<1;
  int idx = 0;
  for (int i=x-r; i< x+r; i++) {
     for(int j=y-r;j< y+r; j++) {
        if ( ( pow((i - x), 2)+ pow((j-y), 2) ) < r2)   {
          idx = XY(i, j);
          if (idx < NUM_LEDS) {
              leds[idx] = color;
          }
      }
    }
  }
}
#endif
