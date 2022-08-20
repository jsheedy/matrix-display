#include <EEPROM.h>

#include <FastLED.h>
//#include <power_mgt.h>

#include "constants.h"

#include "utils.h"
#include "image.h"
#include "game_of_life.h"
// #include "gifs.h"
#include "plasma.h"
#include "lines.h"
#include "fonts.h"
#include "transforms.h"
// #include "palettes.h"

// add one extra which never gets lit but
// allows XY() to fill in there
CRGB leds[NUM_LEDS + 1];

volatile uint8_t mode = 0;
uint8_t palette_i = 0;

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void setup() {

  mode = EEPROM.read(0);
  FastLED.addLeds<APA102, BGR>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(50);

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


void plasma_clouds(CRGB *leds) {
  plasma(leds, CloudColors_p);
}

// void gif_rgb() {
//    draw_gif(rgb, rgb_length, 300);
// }
//void gif_amiga() {
//   draw_gif(amiga, amiga_length, 100);
//}

void gol(CRGB *leds) {
  game_of_life(leds, true);
}

void gol2(CRGB *leds) {
  game_of_life(leds, false);
}

void jbl_ride(CRGB *leds) {
  uint8_t scale = 10;
  uint8_t back_range;
  uint8_t mid_range;
  uint8_t front_range;

  long t = millis() / 5;

  plasma_clouds(leds);
  // sun
  draw_circle(leds, beatsin8(3, 0, WIDTH, 0, 0), beatsin8(3, HEIGHT-8, HEIGHT, 0, 0), 8, CRGB::Yellow);

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

void x0r_texture(CRGB *leds, bool move) {

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

void x0r_texture_motion(CRGB *leds) {
  x0r_texture(leds, true);
}

void x0r_texture_static(CRGB *leds) {
  x0r_texture(leds, false);
}

void noise_plasma(CRGB *leds)
{
  long t = millis() / 5;
  uint8_t scale = map(inoise8(t), 20, 190, 1, 30); // beatsin8(2, 2, 40, 0, 0);
  for (uint8_t x = 0; x < WIDTH; x++)
  {
    for (uint8_t y = 0; y < HEIGHT; y++)
    {
      leds[XY(x, y)] = ColorFromPalette(PartyColors_p, map(inoise8((x)*scale, (y)*scale, t), 30, 180, 0, 255));
    }
  }
}

CRGB checkerboard(Point_t p, uint8_t size);
CRGB checkerboard(Point_t p, uint8_t size)
{

  if ((
          ((p.x % (size * 2)) < size) &&
          ((p.y % (size * 2)) < size)) ||
      (((p.x % (size * 2)) >= size) &&
       ((p.y % (size * 2)) >= size)))
  {
    return ColorFromPalette(LavaColors_p, millis() / 2000);
  }
  else
  {
    return ColorFromPalette(OceanColors_p, millis() / 1999);
  }
}

void lut_deformation(CRGB *leds)
{
  Point_t p;

  float t = (float)millis() / 500.0;
  float s = sin(t);
  float c = cos(t);

  for (p.x = 0; p.x < WIDTH; p.x++)
  {
    for (p.y = 0; p.y < HEIGHT; p.y++)
    {
      leds[XY(p.x, p.y)] = checkerboard(LUT_distort(p, s, c), beatsin8(2, 2, 24, 0, 0));
    }
  }
}

typedef void (*Modes[])(CRGB *);

Modes modes = {
    lut_deformation,
    draw_atari,
    draw_algorithm,
    lines,
    gol2,
    gol,
    noise_plasma,
    x0r_texture_static,
    x0r_texture_motion,
    jbl_ride,
    // bitboard_test,
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
  modes[mode](leds);
  FastLED.show();
}
