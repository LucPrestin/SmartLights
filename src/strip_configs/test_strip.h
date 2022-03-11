#include <array>
#include <Adafruit_NeoPixel.h>

constexpr uint8_t num_strips = 1;

std::array<Adafruit_NeoPixel, num_strips> strips {
  Adafruit_NeoPixel(1, 5, NEO_GRB + NEO_KHZ800)
};

std::array<const char *, num_strips> topics {
  "all-test"
};

constexpr std::array<uint8_t, num_strips> num_stars {1};

constexpr uint8_t max_nr_stars = 1;
