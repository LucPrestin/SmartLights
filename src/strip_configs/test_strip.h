#include <array>
#include <Adafruit_NeoPixel.h>

#include "../mqtt_config.h"

constexpr uint8_t num_strips = 1;
constexpr uint8_t num_topics = 2;

std::array<Adafruit_NeoPixel, num_strips> strips {
  Adafruit_NeoPixel(1, 5, NEO_GRB + NEO_KHZ800)
};

std::array<const String, num_topics> topics {
  "all", "test"
};

std::array<const String, num_strips> topics_per_strip {
  "all"  + topic_delimiter + "test"
};

constexpr std::array<uint8_t, num_strips> num_stars {1};

constexpr uint8_t max_nr_stars = 1;
