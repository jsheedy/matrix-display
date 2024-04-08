#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#include "constants.h"
#include "bitboard.h"
#include "utils.h"
// #include "plasma.h"
// http://pi.math.cornell.edu/~lipa/mec/lesson6.html

void glider(uint8_t x, uint8_t y)
{
  bb_set(x, y, bitboard);
  bb_set(x + 1, y, bitboard);
  bb_set(x + 2, y, bitboard);

  bb_set(x, y + 1, bitboard);
  bb_set(x + 1, y + 2, bitboard);
}

void lightweight_space_ship(uint8_t x, uint8_t y)
{
  bb_set(x + 1, y, bitboard);
  bb_set(x + 4, y, bitboard);

  bb_set(x, y, bitboard);

  bb_set(x, y + 2, bitboard);
  bb_set(x + 4, y + 2, bitboard);

  bb_set(x + 0, y + 3, bitboard);
  bb_set(x + 1, y + 3, bitboard);
  bb_set(x + 2, y + 3, bitboard);
  bb_set(x + 3, y + 3, bitboard);
}

void update_board(CRGB *leds) {
  uint8_t sum;
  uint8_t t = (millis() / 50) % 255;
  uint8_t bitboard2[NUM_LEDS / 8];

  // flip on random cell
  bb_set(random(0, WIDTH), random(0, HEIGHT), bitboard);

  for (uint8_t x = 0; x < WIDTH; x++)
  {
    for (uint8_t y = 0; y < HEIGHT; y++)
    {
      sum = bb_get(x - 1, y - 1, bitboard)
        + bb_get(x - 1, y, bitboard)
        + bb_get(x - 1, y + 1, bitboard)
        + bb_get(x, y - 1, bitboard)
        + bb_get(x, y + 1, bitboard)
        + bb_get(x + 1, y - 1, bitboard)
        + bb_get(x + 1, y, bitboard)
        + bb_get(x + 1, y + 1, bitboard);

      if (sum == 3)
      {
        // cell survives or new cell born
        bb_set(x, y, bitboard2);
        leds[XY(x, y)] =ColorFromPalette(PartyColors_p, t+16);
      }
      else if (sum == 2 && bb_get(x, y, bitboard))
      {
        // cell survives
        bb_set(x, y, bitboard2);
        leds[XY(x, y)] = ColorFromPalette(PartyColors_p, t);
      }
      else
      {
        bb_clear(x, y, bitboard2);
      }
    }
  }

  for (uint8_t i = 0; i < NUM_LEDS / 8; i++) {
    bitboard[i] = bitboard2[i];
  }

}

void game_of_life(CRGB *leds, bool fade)
{

  EVERY_N_MILLISECONDS(100)
  {
    update_board(leds);
    if (random(40) == 0)
    {
      glider(random(1, WIDTH - 4), random(1, HEIGHT - 4));
    }
    if (random(50) == 0)
    {
      lightweight_space_ship(random(1, WIDTH - 5), random(1, HEIGHT - 4));
    }
  }

  for (uint8_t x = 0; x < WIDTH; x++)
  {
    for (uint8_t y = 0; y < HEIGHT; y++)
    {
      if (! bb_get(x, y, bitboard)) {
        if (fade) {
          leds[XY(x, y)]--;
        } else {
          leds[XY(x, y)] = CRGB(0, 0, 0);
        }
      }
    }
  }
}

#endif
