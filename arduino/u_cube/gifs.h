uint8_t frame = 0;

uint16_t read(const uint16_t* gif, uint8_t f, uint8_t x, uint8_t y) {
  uint16_t color; 
  uint16_t idx;
  idx = (uint16_t)f * NUM_LEDS + XY_im(x, y);
  color = pgm_read_word(&(gif[idx]));
  return color;
}

void draw_gif(const uint16_t* gif, uint8_t number_of_frames, uint16_t delay) {
  int idx = 0;
  uint16_t color;
  
  frame = (frame + 1) % number_of_frames;
  for(uint8_t x=0; x<WIDTH; x++) {
    for(uint8_t y=0; y<HEIGHT; y++) {
      idx = XY(x, y);
      color = read(gif, frame, x, y);
      leds[idx].r = 8 * ((color & 0b1111100000000000) >> 11);
      leds[idx].g = 8 * ((color & 0b0000011111100000) >> 5);
      leds[idx].b = 8 * ((color & 0b0000000000111111));
    }
  }
  FastLED.delay(delay);
}
