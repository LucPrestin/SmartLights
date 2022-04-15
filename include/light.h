#pragma once

#include <Arduino.h>

// here goes the config for the strip you want to use
#include "./strip_configs/test_strip.h"

void set_all_strips_to(uint32_t color);
void set_strip_to(uint32_t color, int index);
void show_all_strips();
void setup_strips();
