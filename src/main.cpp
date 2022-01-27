#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <cmath>
#include <vector>

// here goes the config you want to use
#include "../strip_configs/three_strips.h"

std::vector<Adafruit_NeoPixel> strips;

void stars(uint16_t count, uint8_t wait) {
  #define stepSize 1
  // reset strips
  for (auto & strip : strips) {
    strip.clear();
  }

  // determine how many stars per strip are needed
  std::vector<std::vector<uint8_t>> star_indices;
  for (auto & config : configurations) {
    auto amout_of_stars = static_cast<int>(std::sqrt(config.num_leds));
    std::vector<uint8_t> indices;
    for (; amout_of_stars > 0; amout_of_stars--) {
      indices.push_back(-1);
    }
    star_indices.push_back(indices);
  }

  for(uint8_t current_star_iteration = 0; current_star_iteration < count; current_star_iteration++){
    // choose random leds per strip
    for (uint8_t strip_index = 0; strip_index < star_indices.size(); strip_index++) {
      auto & strip = strips[strip_index];
      auto strip_star_indices = star_indices[strip_index];
      for (uint8_t star_index = 0; star_index < strip_star_indices.size(); star_index++) {
        strip_star_indices[star_index] = random(0, strip.numPixels());
      }
    }
    
    // light the chosen leds up
    for(uint16_t step = 0; step <= 255; step += stepSize){
      for (uint8_t strip_index = 0; strip_index < star_indices.size(); strip_index++) {
        auto & strip = strips[strip_index];
        auto strip_star_indices = star_indices[strip_index];
        for (uint8_t star_index = 0; star_index < strip_star_indices.size(); star_index++) {
          strip.setPixelColor(strip_star_indices[star_index], strip.Color(255 - step, 255 - step, 0));
        }
        strip.show();
      }
      delay(round(500.0 * wait / 255));
    }       
  }
}

uint32_t Wheel(Adafruit_NeoPixel & strip, byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void rainbow(uint8_t wait) {
    uint16_t i, j;

    for(j = 0; j < 256; j++) {
      for (auto & strip : strips) {
        for(i = 0; i < strip.numPixels(); i++) {
          strip.setPixelColor(i, Wheel(strip, (i + j) & 255));
        }
        strip.show();
      }
      delay(wait);
    }
}

void setup() {
  for(auto & config : configurations) {
    strips.push_back(Adafruit_NeoPixel(config.num_leds, config.led_pin, config.led_kind));
  }

  for (auto & strip : strips) {
    strip.begin();
    strip.show();
  }
}

void loop() {
    randomSeed(analogRead(1));

    //stars(20, 3);
    rainbow(40);

    delay (2000);
}
