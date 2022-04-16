#ifndef LIGHT_H
#define LIGHT_H

#include <Arduino.h>

// here goes the config for the strip you want to use
// only one must be uncommented

#define USE_CONFIG_TEST_STRIP 
// #define USE_CONFIG_STOOL
// #define USE_CONFIG_THREE_SHELVES
// #define USE_CONFIG_TV_LOWBOARD

#if defined(USE_CONFIG_STOOL)
    #include "config/strip_configs/stool.h"
#elif defined(USE_CONFIG_TEST_STRIP)
    #include "config/strip_configs/test_strip.h"
#elif defined(USE_CONFIG_THREE_SHELVES)
    #include "config/strip_configs/three_shelves.h"
#elif defined(USE_CONFIG_TV_LOWBOARD)
    #include "config/strip_configs/tv_lowboard.h"
#endif

void set_all_strips_to(uint32_t color);
void set_strip_to(uint32_t color, int index);
void show_all_strips();
void setup_strips();

#endif
