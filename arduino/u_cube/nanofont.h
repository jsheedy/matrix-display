#ifndef NANOFONT
#define NANOFONT

#include "constants.h"

void draw_nanofont_char(CRGB *leds, short ul_x, short ul_y, uint8_t idx, CRGB color)
{
  uint16_t word, byte_swapped_word;
  bool pix_on;
  byte_swapped_word = pgm_read_word(&nanofont_bits[idx * 2]);
  word = (byte_swapped_word << 8) | (byte_swapped_word >> 8);

  CRGB off_color = CRGB(0, 0, 0);
  for (uint8_t y = 0; y < 4; y++)
  {
    for (uint8_t x = 0; x < 4; x++)
    {
      pix_on = word & (1 << (15 - (y * 4 + x)));
      leds[XY(ul_x + x, ul_y - y)] = pix_on ? color : off_color;
    }
  }
}

void nanofont(CRGB *leds) {
  CRGB color = ColorFromPalette(RainbowColors_p, millis() / 25);
  uint8_t idx = 32;
  for (uint8_t y = HEIGHT - 1; y > 3; y -= 4) {
    for (uint8_t x = 0; x < WIDTH; x += 4) {
      draw_nanofont_char(leds, x, y, idx, color);
      idx++;
    }
  }
}

#endif