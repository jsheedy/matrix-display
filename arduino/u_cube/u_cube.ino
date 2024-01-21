#include <EEPROM.h>

#include <FastLED.h>
//#include <power_mgt.h>

#include "constants.h"

#include "utils.h"
#include "image.h"
#include "game_of_life.h"
// #include "gifs.h"
#include "plasma.h"
#include "sorting.h"
#include "lines.h"
#include "fonts.h"
#include "transforms.h"
// #include "palettes.h"

// add one extra which never gets lit but
// allows XY() to fill in there
CRGB leds[NUM_LEDS + 1];

volatile uint8_t mode = 0;
uint8_t palette_i = 0;
long t;

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
  randomizeArr();
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
  long t = millis() / 19;
  // uint8_t scale = map(inoise8(t), 20, 190, 1, 30); // beatsin8(2, 2, 40, 0, 0);
  uint8_t scale = 10;
  for (uint8_t x = 0; x < WIDTH; x++)
  {
    for (uint8_t y = 0; y < HEIGHT; y++)
    {
      leds[XY(x, y)] = ColorFromPalette(PartyColors_p, map(inoise8((x)*scale, (y)*scale, t), 30, 180, 0, 255));
    }
  }
}

void noise_lava(CRGB *leds)
{
  long t = millis() / 19;
  uint8_t scale = 12;
  for (uint8_t x = 0; x < WIDTH; x++)
  {
    for (uint8_t y = 0; y < HEIGHT; y++)
    {
      leds[XY(x, y)] = ColorFromPalette(LavaColors_p, map(inoise8((x)*scale, (y)*scale, t), 30, 180, 0, 255));
    }
  }
}

bool checkerboard(Point_t p, uint8_t size);
bool checkerboard(Point_t p, uint8_t size)
{
  return
    (((p.x % (size * 2)) < size) &&
    ((p.y % (size * 2)) < size))
    ||
    (((p.x % (size * 2)) >= size) &&
    ((p.y % (size * 2)) >= size));
}

void lut_deformation(CRGB *leds)
{
  Point_t p;

  float t = (float)millis() / 1200.0;
  float s = sin(t);
  float c = cos(t);

  for (p.x = 0; p.x < WIDTH; p.x++)
  {
    for (p.y = 0; p.y < HEIGHT; p.y++)
    {
      if (checkerboard(LUT_distort(p, s, c), beatsin8(2, 4, 18, 0, 0))) {
        leds[XY(p.x, p.y)] = CRGB::DarkMagenta;
      } else {
        leds[XY(p.x, p.y)] = CRGB::DarkOrange;
      }
    }
  }
}

void three_d_checker(CRGB *leds)
{
  // https://tixy.land/?code=%28%28%28x+-+8%29+%2F+y+%2B+t+*+5%29+%26+1+%5E+1+%2F+y+*+8+%26+1%29+*y+%2F+5%3B
  Point_t p;
  float t = (float) millis() / 500.0;
  short x, y;
  float i;
  float xx;
  CRGB c;

  for (x = 0; x < WIDTH; x++)
  {
    for (y = 0; y < HEIGHT; y++)
    {
      i = (x - WIDTH/2) / (float)y + t;
      xx = (float)((int)i & 1 ^ 1 / y * 15 & 1) * y;
      i = xx * 16;
      leds[XY(WIDTH - x - 1, HEIGHT-y - 1)] = CRGB(i, i, i);
    }
  }
}

void three_d_checker_vert(CRGB *leds)
{
  Point_t p;
  t = millis();
  for (p.x = 0; p.x < WIDTH; p.x++)
  {
    for (p.y = 0; p.y < HEIGHT; p.y++)
    {
      if (p.y > 16) {
        leds[XY(p.x, p.y)] = CHSV(100, 100 + p.y * 4, 100);
        continue;
      }
      if (checkerboard(LUT_distort2(p, t), 3))
      {
        leds[XY(p.x, p.y)] = CRGB::Black;
      }
      else
      {
        leds[XY(p.x, p.y)] = CRGB::Green;
      }
    }
  }
}

typedef void (*Modes[])(CRGB *);

Modes modes = {
    hbars,
    vbars,
    bubblesort,
    three_d_checker,
    // three_d_checker_vert,
    lut_deformation,
    draw_atari,
    draw_algorithm,
    lines,
    gol2,
    gol,
    noise_plasma,
    noise_lava,
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
