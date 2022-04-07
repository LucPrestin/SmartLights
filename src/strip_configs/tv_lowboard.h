#include <array>
#include <Adafruit_NeoPixel.h>

#include "../mqtt_config.h"

constexpr uint8_t num_strips = 2;
constexpr uint8_t num_topics = 4;

std::array<Adafruit_NeoPixel, num_strips> strips {
  Adafruit_NeoPixel(12, 12, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(12, 14, NEO_GRB + NEO_KHZ800)
};

std::array<const String, num_topics> topics {
  "all", "tv_lowboard", "tv_lowboard/left", "tv_lowboard/right"
};

std::array<const String, num_strips> topics_per_strip {
  "all" + topic_delimiter + "tv_lowboard" + topic_delimiter + "tv_lowboard/left",
  "all" + topic_delimiter + "tv_lowboard" + topic_delimiter + "tv_lowboard/right"
};

constexpr std::array<uint8_t, num_strips> num_stars {3, 3};

constexpr uint8_t max_nr_stars = 3;
