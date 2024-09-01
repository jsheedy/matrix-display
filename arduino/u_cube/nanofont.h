#ifndef NANOFONT
#define NANOFONT

#include "constants.h"
#include "utils.h"
#include "bitboard.h"

uint8_t NANOFONT_LINE = 0;

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
    draw_nanofont_char(leds, 4*i, 3, line[i], color);
    FastLED.delay(random(50, 200));
    FastLED.show();
  }
}

void nanofont(CRGB * leds)
{
  CRGB color = ColorFromPalette(RainbowColors_p, millis() / 25);

  // paste in output from tools/text-to-nanofont.py here

  // uint8_t line[11][6] = {
  //   {35, 53, 52, 41, 37},
  //   {38, 41, 33, 46, 35, 37},
  //   {36, 47, 0, 57, 47, 53},
  //   {55, 33, 46, 46, 33},
  //   {45, 33, 50, 50, 57},
  //   {45, 37},
  //   {50, 37, 33, 44},
  //   {51, 47, 47, 46},
  //   {},
  //   {41, 0, 44, 47, 54, 37},
  //   {57, 47, 53}
  // };
  uint8_t line[10][6] = {
      {55, 41, 51, 36, 47, 45},
      {},
      {35, 47, 53, 50, 13},
      {33, 39, 37},
      {},
      {42, 53, 51, 52},
      {13, 41, 35, 37},
      {},
      {52, 37, 45, 48, 37, 13},
      {50, 33, 46, 35, 37},
  };

  uint8_t nlines = 10;

  EVERY_N_MILLISECONDS(500) {
    nanofont_draw_line(leds, color, line[NANOFONT_LINE]);
    NANOFONT_LINE++;
    if (NANOFONT_LINE >= nlines) {
      NANOFONT_LINE = 0;
      scroll_up_line(leds);
      scroll_up_line(leds);
      scroll_up_line(leds);
      scroll_up_line(leds);
    }
  }

}

#endif