void plasma(CRGBPalette16 palette) {
 for(uint8_t x=0; x<WIDTH; x++) {
    for(uint8_t y=0; y<HEIGHT; y++) {
      // FastLED provides several 'preset' palettes: RainbowColors_p, RainbowStripeColors_p,
      // OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p.
      // also http://fastled.io/tools/paletteknife/

      leds[XY(x, y)] = ColorFromPalette(
          palette,
          beatsin8(5, 0, 42, 0, x*8)
          + beatsin8(11, 0, 42, 0, -x*9)

          + beatsin8(9, 0, 42, 0, y*10)
          + beatsin8(13, 0, 42, 0, -y*11)

          + beatsin8(7, 0, 42, 0, (x + y)*12)
          + beatsin8(15, 0, 42, 0, -(x + y)*13)
        ,255
       );

    }
  }
}
