#ifndef THREE_SHELVES_H
#define THREE_SHELVES_H

#include <array>
#include <Adafruit_NeoPixel.h>

#include "constants.h"

const char * const mqtt_name = "three_shelves";
const char * const mqtt_password = "";

constexpr uint8_t num_strips = 3;
constexpr uint8_t num_topics = 5;

std::array<Adafruit_NeoPixel, num_strips> strips {
  Adafruit_NeoPixel(8, 5, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(12, 18, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(12, 19, NEO_GRB + NEO_KHZ800)
};

std::array<const String, num_topics> topics {
  "all" + color_suffix, 
  "three_shelves" + color_suffix, 
  "three_shelves/top" + color_suffix, 
  "three_shelves/middle" + color_suffix,
  "three_shelves/bottom" + color_suffix
};

std::array<const String, num_strips> topics_per_strip {
  topics[0] + topic_delimiter + topics[1] + topic_delimiter + topics[2],
  topics[0] + topic_delimiter + topics[1] + topic_delimiter + topics[3],
  topics[0] + topic_delimiter + topics[1] + topic_delimiter + topics[4]
};

#endif
