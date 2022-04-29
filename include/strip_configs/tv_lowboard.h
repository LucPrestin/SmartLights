#ifndef TV_LOWBOARD_H
#define TV_LOWBOARD_H

#include <array>
#include <Adafruit_NeoPixel.h>

#include "constants.h"

const char * const mqtt_name = "tv_lowboard";
const char * const mqtt_password = "";

constexpr uint8_t num_strips = 2;
constexpr uint8_t num_topics = 4;

std::array<Adafruit_NeoPixel, num_strips> strips {
  Adafruit_NeoPixel(12, 12, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(14, 12, NEO_GRB + NEO_KHZ800)
};

std::array<const String, num_topics> topics {
  "all" + color_suffix, 
  "tv_lowboard" + color_suffix,
  "tv_lowboard/left" + color_suffix,
  "tv_lowboard/right" + color_suffix,
};

std::array<const String, num_strips> topics_per_strip {
  topics[0] + topic_delimiter + topics[1] + topic_delimiter + topics[2],
  topics[0] + topic_delimiter + topics[1] + topic_delimiter + topics[3]
};

#endif
