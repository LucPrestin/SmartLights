#ifdef USE_CONFIG_TV_LOWBOARD

#ifndef TV_LOWBOARD_H
#define TV_LOWBOARD_H

#include <array>
#include <Adafruit_NeoPixel.h>

#include "constants.h"

constexpr uint8_t num_strips = 2;
constexpr uint8_t num_topics = 4;

extern std::array<Adafruit_NeoPixel, num_strips> strips;
extern std::array<const String, num_topics> topics;
extern std::array<const String, num_strips> topics_per_strip;

#endif

#endif
