#include <Adafruit_NeoPixel.h>

#define num_strips 3

Adafruit_NeoPixel strips[num_strips] {
  Adafruit_NeoPixel(8, 19, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(12, 18, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(12, 5, NEO_GRB + NEO_KHZ800)
}

uint8_t num_stars[num_strips] {2, 3, 3};
