#include <EEPROM.h>

#include <FastLED.h>
//#include <power_mgt.h>

#include "constants.h"
#include "bitboard.h"

#include "utils.h"
#include "image.h"
#include "game_of_life.h"
// #include "gifs.h"
#include "plasma.h"
#include "lines.h"
// #include "palettes.h"

volatile uint8_t mode = 0;
uint8_t palette_i = 0;

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void setup() {

  mode = EEPROM.read(0);
  FastLED.addLeds<APA102, BGR>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(40);

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  //  pinMode(LED_BUILTIN, OUTPUT);
  //  digitalWrite(LED_BUILTIN, HIGH);
  // Serial.begin(9600); // open the serial port at 9600 bps:

  // hardware SPI on itsy bitsy crashes until PB0 is OUTPUT
  // https://www.reddit.com/r/FastLED/comments/fmjdm2/comment/fl5o9u2/?utm_source=share&utm_medium=web2x&context=3
  pinMode(17, OUTPUT);

  // https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), isr, FALLING);
}

CRGBPalette16 palettes[4] = {
  LavaColors_p,
  PartyColors_p,
  RainbowColors_p,
  HeatColors_p,
};

void plasma_lava() {
  plasma(LavaColors_p);
}
void plasma_ocean() {
  plasma(OceanColors_p);
}
void plasma_clouds() {
  plasma(CloudColors_p);
}
// void plasma_party() {
//   plasma(palettes[1]);
// }

void solid_green() {
  fill_solid(leds, NUM_LEDS, CRGB::Green);
}

// void gif_rgb() {
//    draw_gif(rgb, rgb_length, 300);
// }
//void gif_amiga() {
//   draw_gif(amiga, amiga_length, 100);
//}
void gol() {
  game_of_life(true);
}

void gol2() {
  game_of_life(false);
}


void jbl_ride() {
  uint8_t scale = 10;
  uint8_t back_range;
  uint8_t mid_range;
  uint8_t front_range;

  long t = millis() / 5;

  plasma_clouds();
  // sun
  draw_circle(beatsin8(3, 0, WIDTH, 0, 0), beatsin8(3, HEIGHT-8, HEIGHT, 0, 0), 8, CRGB::Yellow);

  for(uint8_t x=0; x<WIDTH; x++) {
    back_range = map(inoise8((3.0 * x/WIDTH) * scale * x + t), 30, 180, 0, HEIGHT - 10);
    mid_range= map(inoise8((2.0 * x/WIDTH) * scale * x + t), 30, 180, 0, HEIGHT - 14);
    front_range= map(inoise8(scale * x + t), 30, 180, 0, HEIGHT - 20);

    for(uint8_t y=0; y<HEIGHT; y++) {
      if (y <= back_range && y > mid_range) {
        leds[XY(x, y)] = CRGB(0, 30, 0);
      }
      else if (y <= mid_range && y > front_range) {
        leds[XY(x, y)] = CRGB(0, 100, 0);
      }
      else if (y <= front_range) {
        leds[XY(x, y)] = CRGB(0, 255, 0);
      }
    }
  }
}

void x0r_texture(bool move) {

  uint8_t x0r = 0;
  uint8_t x0 = 0, y0 = 0;


  if(move) {
     x0 = millis() / 50;
  }

  for(uint8_t x=0; x<WIDTH; x++) {
    for(uint8_t y=0; y<HEIGHT; y++) {
        x0r = (x + x0) ^ (y + y0);
        leds[XY(x, y)] = ColorFromPalette(palettes[palette_i], 10 * (x0r));
    }
  }

  nblendPaletteTowardPalette(palettes[palette_i], palettes[(palette_i + 1) % ARRAY_SIZE(palettes)], 100);

  EVERY_N_SECONDS(7) {
    palette_i = (palette_i + 1 )  % ARRAY_SIZE(palettes);
  }
}

void x0r_texture_motion() {
  x0r_texture(true);
}
void x0r_texture_static() {
  x0r_texture(false);
}

void bitboard_test() {
  for (uint8_t x = 0; x < WIDTH; x++)
  {
    for (uint8_t y = 0; y < HEIGHT; y++)
    {
      if (bb_get(x, y, bitboard))
      {
        leds[XY(x, y)] = ColorFromPalette(RainbowColors_p, 100);
      }
    }
  }

  fadeToBlackBy(leds, NUM_LEDS, 10);

  {
    for (uint8_t x = 0; x < WIDTH; x++)
    {
      for (uint8_t y = 0; y < HEIGHT; y++)
      {
        if (random8() > 250) {
          bb_set(x, y, bitboard);
        } else {
          bb_clear(x, y, bitboard);
        }
      }
    }
  }
}

typedef void (*Modes[])();

Modes modes = {
  lines,
    gol,
    gol2,
    bitboard_test,
    // solid_green,
    x0r_texture_static,
    x0r_texture_motion,
    jbl_ride,
    plasma_ocean,
    // plasma_lava,
    // plasma_party,
    // gif_rgb,
    //        gif_amiga,
};

void isr()
{
  static unsigned long last_interrupt_time = 0;
  if (millis() - last_interrupt_time > 300)
  {
    last_interrupt_time = millis();
    mode = (mode + 1) % ARRAY_SIZE(modes);
    EEPROM.write(0, mode);
  }
}

void loop()
{
  // TODO: implement LUT deformation:
  // https://iquilezles.org/articles/deform/
  modes[mode]();
  FastLED.show();
}
