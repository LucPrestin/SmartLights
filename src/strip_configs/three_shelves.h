#include <array>
#include <Adafruit_NeoPixel.h>

#include "../mqtt_config.h"

constexpr uint8_t num_strips = 3;
constexpr uint8_t num_topics = 5;

std::array<Adafruit_NeoPixel, num_strips> strips {
  Adafruit_NeoPixel(8, 19, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(12, 18, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(12, 5, NEO_GRB + NEO_KHZ800)
};

std::array<const String, num_topics> topics {
  "all", "shelves", "shelves/top", "shelves/middle", "shelves/bottom"
};

std::array<const String, num_strips> topics_per_strip {
  "all"  + topic_delimiter + "shelves"  + topic_delimiter + "shelves/top",
  "all"  + topic_delimiter + "shelves"  + topic_delimiter + "shelves/middle",
  "all"  + topic_delimiter + "shelves"  + topic_delimiter + "shelves/bottom"
};

constexpr std::array<uint8_t, num_strips> num_stars {2, 3, 3};

constexpr uint8_t max_nr_stars = 3;
