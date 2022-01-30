#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <cmath>
#include <algorithm>
#include <array>

// here goes the config you want to use
#include "./strip_configs/three_strips.h"

void stars(uint16_t count, uint8_t wait) {
  #define stepSize 1
  // reset strips
  for (auto & strip: strips) {
    strip.clear();
  }

  // create index arrays
  std::array<std::array<uint8_t, max_nr_stars>, num_strips> star_indices;
  for (uint8_t strip_index = 0; strip_index < num_strips; strip_index++) {
    for (uint8_t star_index = 0; star_index < num_stars.at(strip_index); star_index++) {
      star_indices.at(strip_index).at(star_index) = 0;
    }
  }


  for(uint8_t stars_shown = 0; stars_shown < count; stars_shown++){
    // choose random leds per strip
    for (uint8_t strip_index = 0; strip_index < num_strips; strip_index++) {
      for (uint8_t star_index = 0; star_index < num_stars[strip_index]; star_index++) {
        star_indices.at(strip_index).at(star_index) = random(0, strips[strip_index].numPixels());
      }
    }
    
    // light the chosen leds up
    for(uint16_t step = 0; step <= 255; step += stepSize){
      for (uint8_t strip_index = 0; strip_index < num_strips; strip_index++) {
        for (uint8_t star_index = 0; star_index < num_stars.at(strip_index); star_index++) {
          strips[strip_index].setPixelColor(star_indices.at(strip_index).at(star_index), strips[strip_index].Color(255 - step, 255 - step, 0));
        }
      }
      for (auto & strip: strips) {
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
      for (auto & strip: strips) {
        for(i = 0; i < strip.numPixels(); i++) {
          strip.setPixelColor(i, Wheel(strip, (i + j) & 255));
        }
      }

      for (auto & strip: strips) {
        strip.show();
      }
      
      delay(wait);
    }
}

void setup() {
  for (auto & strip: strips) {
    strip.begin();
  }

  for (auto & strip: strips) {
    strip.show();
  }
}

void loop() {
    randomSeed(analogRead(1));

    stars(20, 3);
    rainbow(40);
}
