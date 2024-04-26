#ifndef NANOFONT
#define NANOFONT

#include "constants.h"
#include "utils.h"
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

void scroll_up_line(CRGB *leds)
{
  for (int i = 0; i < 4; i++)
  {
    scroll_up(leds);
    FastLED.delay(random(80, 200));
    FastLED.show();
  }
}

void nanofont_draw_line(CRGB *leds, CRGB color, uint8_t *line)
{
  scroll_up_line(leds);
  for (int i = 0; i < 6; i++)
  {
    draw_nanofont_char(leds, 4*i, 4, line[i], color);
    FastLED.delay(random(50, 200));
    FastLED.show();
  }
}

void nanofont(CRGB * leds)
{
  CRGB color = ColorFromPalette(RainbowColors_p, millis() / 25);

  uint8_t line[2][6] = {
    {35, 53, 52, 41, 37},
    {38, 41, 33, 46, 35, 37}
  };
  for (int i=0; i < 2; i++) {
    nanofont_draw_line(leds, color, line[i]);
  }
}

#endif