#ifndef BITBOARD_H
#define BITBOARD_H

uint8_t bitboard[NUM_LEDS / 8];

bool bb_get(int8_t x, int8_t y, uint8_t *bb)
{
  if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
    return 0;
  }
  uint16_t idx;
  uint16_t bidx;
  short delta;
  idx = (uint16_t)(x)*WIDTH + y;
  bidx = idx / 8;
  delta = idx % 8;

  return (bool)(bb[bidx] & (1 << delta));
}

void bb_set(uint8_t x, uint8_t y, uint8_t* bb)
{
  uint16_t idx;
  uint16_t bidx;
  uint8_t delta;

  idx = (uint16_t)(x)*WIDTH + y;
  bidx = idx / 8;
  delta = idx % 8;
  bb[bidx] = bb[bidx] | (1 << delta);
}

void bb_clear(uint8_t x, uint8_t y, uint8_t *bb)
{
  uint16_t idx;
  uint16_t bidx;
  uint8_t delta;

  idx = (uint16_t)(x)*WIDTH + y;
  bidx = idx / 8;
  delta = idx % 8;
  bb[bidx] = bb[bidx] & ~(1 << delta);
}

// void bitboard_test(CRGB *leds)
// {
//   fadeToBlackBy(leds, NUM_LEDS, 5);
//   long t = millis() / 5;

//   for (uint8_t x = 0; x < WIDTH; x++)
//   {
//     for (uint8_t y = 0; y < HEIGHT; y++)
//     {
//       if (inoise8(x * 8, y * 8, t) > 150)
//       {
//         bb_set(x, y, bitboard);
//       }
//       else
//       {
//         bb_clear(x, y, bitboard);
//       }
//     }
//   }

//   update_board(leds);

//   for (uint8_t x = 0; x < WIDTH; x++)
//   {
//     for (uint8_t y = 0; y < HEIGHT; y++)
//     {
//       if (bb_get(x, y, bitboard))
//       {
//         leds[XY(x, y)] += ColorFromPalette(RainbowColors_p, millis() / 100);
//       }
//     }
//   }
// }
#endif
