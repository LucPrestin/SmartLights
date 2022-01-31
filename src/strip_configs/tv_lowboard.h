#include <array>
#include <Adafruit_NeoPixel.h>

constexpr uint8_t num_strips = 2;

std::array<Adafruit_NeoPixel, num_strips> strips {
  Adafruit_NeoPixel(12, 12, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(12, 14, NEO_GRB + NEO_KHZ800)
};

constexpr std::array<uint8_t, num_strips> num_stars {3, 3};

constexpr uint8_t max_nr_stars = 3;
