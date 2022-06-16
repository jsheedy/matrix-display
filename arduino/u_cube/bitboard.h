#ifndef BITBOARD_H
#define BITBOARD_H

#include "constants.h"

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

#endif
