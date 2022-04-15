#include <array>
#include <Adafruit_NeoPixel.h>

#include "../constants.h"

constexpr uint8_t num_strips = 3;
constexpr uint8_t num_topics = 5;

std::array<Adafruit_NeoPixel, num_strips> strips {
  Adafruit_NeoPixel(8, 19, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(12, 18, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(12, 5, NEO_GRB + NEO_KHZ800)
};

std::array<const String, num_topics> topics {
  "all" + color_suffix, "shelves" + color_suffix, "shelves/+" + color_suffix
};

std::array<const String, num_strips> topics_per_strip {
  "all" + color_suffix + topic_delimiter + "shelves" + color_suffix + topic_delimiter + "shelves/top" + color_suffix,
  "all" + color_suffix + topic_delimiter + "shelves" + color_suffix + topic_delimiter + "shelves/middle" + color_suffix,
  "all" + color_suffix + topic_delimiter + "shelves" + color_suffix + topic_delimiter + "shelves/bottom" + color_suffix
};

constexpr std::array<uint8_t, num_strips> num_stars {2, 3, 3};

constexpr uint8_t max_nr_stars = 3;
