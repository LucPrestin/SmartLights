#pragma once

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <array>

#define stepSize 1

template<uint8_t num_strips, uint8_t max_nr_stars>
void stars(
    std::array<Adafruit_NeoPixel, num_strips> strips, 
    std::array<uint8_t, num_strips> num_stars, 
    uint8_t count, 
    uint8_t wait
);
