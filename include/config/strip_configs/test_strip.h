#ifdef USE_CONFIG_TEST_STRIP

#ifndef TEST_STRIP_H
#define TEST_STRIP_H

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
