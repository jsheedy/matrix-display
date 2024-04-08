#include "utils.h"

uint16_t XY(uint8_t x, uint8_t y)
{
    if (x >= WIDTH || y >= HEIGHT)
    {
        return NUM_LEDS - 1;
    }

    if (x % 2 == 0)
    {
        return (uint16_t)(WIDTH - 1 - x) * HEIGHT + (HEIGHT - 1 - y);
    }
    else
    {
        return (uint16_t)(WIDTH - 1 - x) * HEIGHT + (y);
    }
}

void draw_circle(CRGB *leds, uint8_t x, uint8_t y, uint8_t r, CRGB color)
{
    long r2 = r << 1;
    uint16_t idx = 0;
    for (int i = x - r; i < x + r; i++)
    {
        for (int j = y - r; j < y + r; j++)
        {
            if ((pow((i - x), 2) + pow((j - y), 2)) < r2)
            {
                idx = XY(i, j);
                if (idx < NUM_LEDS)
                {
                    leds[idx] = color;
                }
            }
        }
    }
}