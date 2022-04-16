#ifdef USE_CONFIG_THREE_SHELVES

#include "config/strip_configs/three_shelves.h"

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

#endif
