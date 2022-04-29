#ifndef TEST_STRIP_H
#define TEST_STRIP_H

#include <array>
#include <Adafruit_NeoPixel.h>

#include "constants.h"

const char * const mqtt_name = "test";
const char * const mqtt_password = "";

constexpr uint8_t num_strips = 1;
constexpr uint8_t num_topics = 2;

std::array<Adafruit_NeoPixel, num_strips> strips {
  Adafruit_NeoPixel(1, 5, NEO_GRB + NEO_KHZ800)
};

std::array<const String, num_topics> topics {
  "all" + color_suffix, 
  "test" + color_suffix
};

std::array<const String, num_strips> topics_per_strip {
  topics[0] + topic_delimiter + topics[1]
};

#endif
