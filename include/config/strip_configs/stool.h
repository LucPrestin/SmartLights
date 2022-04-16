#ifdef USE_CONFIG_STOOL

#ifndef STOOL_H
#define STOOL_H

#include <array>
#include <Adafruit_NeoPixel.h>

#include "constants.h"

constexpr uint8_t num_strips = 1;
constexpr uint8_t num_topics = 2;

extern std::array<Adafruit_NeoPixel, num_strips> strips;
extern std::array<const String, num_topics> topics;
extern std::array<const String, num_strips> topics_per_strip;

#endif

#endif
