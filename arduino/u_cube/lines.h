#ifndef LINES_H
#define LINES_H

#include "constants.h"
#include "utils.h"

void bresenham(CRGB *leds, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
  // http://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm#C

  int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
  int err = (dx > dy ? dx : -dy) / 2, e2;

  long t = millis() / 5;
  for (;;)
  {
    leds[XY(x0, y0)] = ColorFromPalette(PartyColors_p, t + x0 * y0);

    if (x0 == x1 && y0 == y1)
      break;
    e2 = err;
    if (e2 > -dx)
    {
      err -= dy;
      x0 += sx;
    }
    if (e2 < dy)
    {
      err += dx;
      y0 += sy;
    }
  }
}

void lines(CRGB *leds) {
  fadeToBlackBy(leds, NUM_LEDS, 5);
  uint8_t x0=0, y0=0, x1=WIDTH-1, y1=HEIGHT-1;
  // int dt = map(beatsin8(5, 0, 255, 0, 0), 0, 255, 1000, 2000);
  int dt = 1150;
  int f = millis() % dt;

  if (f < dt/2) {
    y0 = map(f, 0, dt/2, 0, HEIGHT-1);
    y1 = HEIGHT - 1 - y0;

  } else
  {
    x1 = map(f, dt/2, dt, 0, WIDTH - 1);
    x0 = WIDTH - 1 - x1;
  }

  bresenham(leds, x0, y0, x1, y1);
}
#endif
