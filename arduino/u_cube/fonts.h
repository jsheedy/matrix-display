#ifndef FONTS_H
#define FONTS_H

void draw_char(short ul_x, short ul_y, uint8_t idx, CRGB color)
{
    uint8_t c;
    if (idx == 32)
    { // space
        return;
    }
    for (uint8_t y = 0; y < 8; y++)
    {
        c = pgm_read_byte(&atari[idx * 8 + y]);
        for (uint8_t x = 0; x < 8; x++)
        {
            if (c & (1 << x))
            {
                leds[XY(ul_x + x, ul_y + 8 - y)] = color;
            }
        }
    }
}

void draw_string_horizontal(const __FlashStringHelper *msg, int x0, CRGB color)
{
    char idx;
    char c = 1;
    uint8_t i = -1;
    uint8_t y = 8;
    int x;
    do
    {
        i++;
        x = x0 - i * 8;
        if (x > (WIDTH + 8)) {
            continue;
        }
        if (x <= -8) {
            break;
        }
        // hat tip https://gist.github.com/sticilface/e54016485fcccd10950e93ddcd4461a3
        strncpy_P(&c, (PGM_P)msg + i, 1);
        if (c >= 65)
        {
            idx = c - 65;
        }
        else
        {
            idx = 32; // space
        }
        // y = beatsin8(60, 4, HEIGHT - 14, 0, i * 32);
        draw_char(x, y, idx, color);
    } while (c != 0); //'\0');
}

void draw_atari()
{
    fadeToBlackBy(leds, NUM_LEDS, 80);
    CRGB color = ColorFromPalette(RainbowColors_p, millis() / 25);
    int x = -16 + (millis() / 30) % (60 * 8 + WIDTH + 8);
    draw_string_horizontal(F("IF YOU KNOW THE WAY BROADLY YOU WILL SEE IT IN EVERYTHING"), x, color);
    // draw_string_horizontal(F("THE MUSIC OF THE FUTURE WILL BE BASED ON ALGORITHMS"), x, color);
}

void draw_algorithm()
{
    CRGB color = ColorFromPalette(RainbowColors_p, millis() / 25);

    draw_char(15, 15, 0, color); // A
    draw_char(8, 15, 11, color); // L
    draw_char(1, 15, 6, color);  // G

    draw_char(15, 8, 14, color); // O
    draw_char(8, 8, 17, color);  // R
    draw_char(1, 8, 8, color);   // I

    draw_char(15, 1, 19, color); // T
    draw_char(8, 1, 7, color);   // H
    draw_char(1, 1, 12, color);  // M
}

#endif