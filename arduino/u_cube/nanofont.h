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

void nanofont(CRGB *leds) {
  CRGB color = ColorFromPalette(RainbowColors_p, millis() / 25);

  draw_nanofont_char(leds, 0, 7, 35, color); // C
  FastLED.delay(random(50, 200));
  FastLED.show();
  draw_nanofont_char(leds, 4, 7, 53, color); // U
  FastLED.delay(random(50, 200));
  FastLED.show();
  draw_nanofont_char(leds, 8, 7, 52, color); // T
  FastLED.delay(random(50, 200));
  FastLED.show();
  draw_nanofont_char(leds, 12, 7, 41, color); // I
  FastLED.delay(random(50, 200));
  FastLED.show();
  draw_nanofont_char(leds, 16, 7, 37, color); // E
  FastLED.delay(random(50, 200));
  FastLED.show();

  draw_nanofont_char(leds, 0, 3, 38, color); // F
  FastLED.delay(random(50, 200));
  FastLED.show();
  draw_nanofont_char(leds, 4, 3, 41, color); // I
  FastLED.delay(random(50, 200));
  FastLED.show();
  draw_nanofont_char(leds, 8, 3, 33, color); // A
  FastLED.delay(random(50, 200));
  FastLED.show();
  draw_nanofont_char(leds, 12, 3, 46, color); // N
  FastLED.delay(random(50, 200));
  FastLED.show();
  draw_nanofont_char(leds, 16, 3, 35, color); // C
  FastLED.delay(random(50, 200));
  FastLED.show();
  draw_nanofont_char(leds, 20, 3, 37, color); // E
  FastLED.delay(random(50, 200));
  FastLED.show();

  scroll_up(leds);
  FastLED.delay(120);
  FastLED.show();
  scroll_up(leds);
  FastLED.delay(110);
  FastLED.show();
  scroll_up(leds);
  FastLED.delay(100);
  FastLED.show();
  scroll_up(leds);
  FastLED.delay(130);
  FastLED.show();

  scroll_up(leds);
  FastLED.delay(120);
  FastLED.show();
  scroll_up(leds);
  FastLED.delay(110);
  FastLED.show();
  scroll_up(leds);
  FastLED.delay(100);
  FastLED.show();
  scroll_up(leds);
  FastLED.delay(130);
  FastLED.show();

}

#endif