#ifndef NANOFONT
#define NANOFONT

#include "constants.h"
#include "bitboard.h"

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
      if (pix_on) {
        leds[XY(ul_x + x, ul_y - y)] = color;
        bb_set(ul_x + x, ul_y - y, bitboard);

      } else {
        leds[XY(ul_x + x, ul_y - y)] = off_color;
        bb_clear(ul_x + x, ul_y - y, bitboard);
      }
    }
  }
}

void nanofont_test(CRGB *leds) {
  CRGB color = ColorFromPalette(RainbowColors_p, millis() / 25);
  uint8_t idx = 32;
  for (uint8_t y = HEIGHT - 1; y > 3; y -= 4) {
    for (uint8_t x = 0; x < WIDTH; x += 4) {
      draw_nanofont_char(leds, x, y, idx, color);
      idx++;
    }
  }
}

void nanofont(CRGB *leds) {
  CRGB color = ColorFromPalette(RainbowColors_p, millis() / 25);

  draw_nanofont_char(leds, 0, 22, 35, color); // C
  draw_nanofont_char(leds, 4, 22, 53, color); // U
  draw_nanofont_char(leds, 8, 22, 52, color); // T
  draw_nanofont_char(leds, 12, 22, 41, color); // I
  draw_nanofont_char(leds, 16, 22, 37, color); // E

  draw_nanofont_char(leds, 0, 18, 38, color); // F
  draw_nanofont_char(leds, 4, 18, 41, color); // I
  draw_nanofont_char(leds, 8, 18, 33, color); // A
  draw_nanofont_char(leds, 12, 18, 46, color); // N
  draw_nanofont_char(leds, 16, 18, 35, color); // C
  draw_nanofont_char(leds, 20, 18, 37, color); // E

}

#endif