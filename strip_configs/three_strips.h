#include <vector>
#include <Adafruit_NeoPixel.h>

#define num_stars 3

std::vector<Adafruit_NeoPixel> strips {
  Adafruit_NeoPixel(8, 19, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(12, 18, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(12, 5, NEO_GRB + NEO_KHZ800)
};
