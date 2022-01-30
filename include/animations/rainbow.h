#pragma once

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <array>

uint32_t Wheel(Adafruit_NeoPixel & strip, byte WheelPos);

template <uint8_t num_strips>
void rainbow(std::array<Adafruit_NeoPixel, num_strips> strips, uint8_t wait);
