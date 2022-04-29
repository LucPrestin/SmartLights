#ifndef STOOL_H
#define STOOL_H

#include <array>
#include <Adafruit_NeoPixel.h>

#include "constants.h"

const char * const mqtt_name = "stool";
const char * const mqtt_password = "";

constexpr uint8_t num_strips = 1;
constexpr uint8_t num_topics = 2;

std::array<Adafruit_NeoPixel, num_strips> strips {
  Adafruit_NeoPixel(12, 12, NEO_GRB + NEO_KHZ800)
};

std::array<const String, num_topics> topics {
  "all" + color_suffix, 
  "stool" + color_suffix
};

std::array<const String, num_strips> topics_per_strip {
  topics[0] + topic_delimiter + topics[1]
};

#endif
