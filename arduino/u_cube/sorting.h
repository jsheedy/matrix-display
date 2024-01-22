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
void shuffle() {
  // Fisher-Yates shuffle
  uint8_t j = 0;
  uint8_t i = 0;
  // first initialize array, in order
  for (i=0; i < WIDTH; i++) {
    arr[i] = i+1;
  }
  // shuffle with xor swap
  for (i = WIDTH-1; i > 0; i--)
  {
    j = random(i);
    // xor swap
    arr[i] = arr[i] ^ arr[j];
    arr[j] = arr[j] ^ arr[i];
    arr[i] = arr[i] ^ arr[j];
  }
}

void bubblesort_draw(CRGB *leds)
{
  for (uint8_t x = 0; x < WIDTH; x++)
  {
    for (uint8_t y = 0; y < HEIGHT; y++)
    {
      if (y < arr[x])
      {
        leds[XY(x, y)] = CRGB(255 - arr[x] * 10, arr[x] * 10, arr[x] * 4);
      }
      else
      {
        leds[XY(x, y)] = CRGB(0, 0, 0);
        // leds[XY(x, y)] = CHSV(millis() / 50, 255, 90);
      }
    }
  }
}

void singlesort(CRGB *leds)
{
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
    FastLED.delay(2000);
    for (i=0; i< 15; i++) {
      shuffle();
      bubblesort_draw(leds);
      FastLED.delay(100);
    }
    FastLED.delay(1000);
  }
}

void bubblesort(CRGB *leds)
{
  singlesort(leds);
  bubblesort_draw(leds);
}

#endif
