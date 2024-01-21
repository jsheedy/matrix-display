#ifndef SORTING_H
#define SORTING_H

#include <FastLED.h>
#include "constants.h"
#include "utils.h"


void hbars(CRGB *leds) {
 for(uint8_t x=0; x<WIDTH; x++) {
    for(uint8_t y=0; y<HEIGHT; y++) {
      if (y % 2 == 0) {
        leds[XY(x, y)] = CRGB::Red;
      } else {
        leds[XY(x, y)] = CRGB::Blue;
      }
    }
  }
}

void vbars(CRGB *leds)
{
  for (uint8_t x = 0; x < WIDTH; x++)
  {
    for (uint8_t y = 0; y < HEIGHT; y++)
    {
      if (x % 2 == 0)
      {
        leds[XY(x, y)] = CRGB::DarkSlateBlue;
      }
      else
      {
        leds[XY(x, y)] = CRGB::DarkMagenta;
      }
    }
  }
}

uint8_t arr[WIDTH];
void randomizeArr() {
  uint8_t j = 0;
  uint8_t i = 0;
  // first place in order
  for (i=0; i < WIDTH; i++) {
    arr[i] = i+1;
  }
  // (bogo)shuffle with xor swap
  for (i = 0; i < WIDTH; i++)
  {
    j = random(WIDTH);
    if (i == j) {
      continue;
    }
    // xor swap
    arr[i] = arr[i] ^ arr[j];
    arr[j] = arr[j] ^ arr[i];
    arr[i] = arr[i] ^ arr[j];
  }
}

void singlesort() {
  // one iteration of sort and draw
  uint8_t i = 0;
  uint8_t j = 0;
  bool inOrder = true;
  for (i = 0; i < WIDTH - 1; i++)
  {
    j = i + 1;
    if (arr[i] > arr[j])
    {
      inOrder = false;
      // xor swap
      arr[i] = arr[i] ^ arr[j];
      arr[j] = arr[j] ^ arr[i];
      arr[i] = arr[i] ^ arr[j];
      FastLED.delay(50);
      break;
    }
  }
  if (inOrder) {
    FastLED.delay(1000);
    randomizeArr();
  }
}
void bubblesort(CRGB *leds)
{
  singlesort();
  for (uint8_t x = 0; x < WIDTH; x++)
  {
    for (uint8_t y = 0; y < HEIGHT; y++)
    {
        if (y < arr[x]) {
          leds[XY(x, y)] = CRGB(200, 200, 0);
        } else {
          leds[XY(x, y)] = CRGB(50, 20, 10);
        }
    }
  }
}

#endif
