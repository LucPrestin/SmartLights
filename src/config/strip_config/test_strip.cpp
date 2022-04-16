#ifdef USE_CONFIG_TEST_STRIP

#include "config/strip_configs/test_strip.h"

std::array<Adafruit_NeoPixel, num_strips> strips {
  Adafruit_NeoPixel(1, 5, NEO_GRB + NEO_KHZ800)
};

std::array<const String, num_topics> topics {
  "all" + color_suffix, "test" + color_suffix
};

std::array<const String, num_strips> topics_per_strip {
  "all" + color_suffix + topic_delimiter + "test" + color_suffix
};

#endif
