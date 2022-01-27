#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <cmath>
#include <vector>

// here goes the config you want to use
// #include "../strip_configs/three_strips.h"

auto strip1 = Adafruit_NeoPixel(8, 19, NEO_GRB + NEO_KHZ800);
auto strip2 = Adafruit_NeoPixel(12, 18, NEO_GRB + NEO_KHZ800);
auto strip3 = Adafruit_NeoPixel(12, 5, NEO_GRB + NEO_KHZ800);

void stars(uint16_t count, uint8_t wait) {
  #define stepSize 1
  // reset strips
  strip1.clear();
  strip2.clear();
  strip3.clear();

  uint8_t num_stars = 3;
  uint8_t strip1_indexes[num_stars];
  uint8_t strip2_indexes[num_stars];
  uint8_t strip3_indexes[num_stars];


  for(uint8_t stars_shown = 0; stars_shown < count; stars_shown++){
    // choose random leds per strip
    for (uint8_t star_index = 0; star_index < num_stars; star_index++) {
      strip1_indexes[star_index] = random(0, strip1.numPixels());
      strip2_indexes[star_index] = random(0, strip3.numPixels());
      strip3_indexes[star_index] = random(0, strip3.numPixels());
    }
    
    // light the chosen leds up
    for(uint16_t step = 0; step <= 255; step += stepSize){
      for (uint8_t star_index = 0; star_index < num_stars; star_index++) {
        strip1.setPixelColor(strip1_indexes[star_index], strip1.Color(255 - step, 255 - step, 0));
        strip2.setPixelColor(strip2_indexes[star_index], strip2.Color(255 - step, 255 - step, 0));
        strip3.setPixelColor(strip3_indexes[star_index], strip3.Color(255 - step, 255 - step, 0));
      }
      strip1.show();
      strip2.show();
      strip3.show();
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
      for(i = 0; i < strip1.numPixels(); i++) {
        strip1.setPixelColor(i, Wheel(strip1, (i + j) & 255));
      }
      for(i = 0; i < strip2.numPixels(); i++) {
        strip2.setPixelColor(i, Wheel(strip2, (i + j) & 255));
      }
      for(i = 0; i < strip3.numPixels(); i++) {
        strip3.setPixelColor(i, Wheel(strip3, (i + j) & 255));
      }
      strip1.show();
      strip2.show();
      strip3.show();
      delay(wait);
    }
}

void setup() {
  strip1.begin();
  strip2.begin();
  strip3.begin();

  strip1.show();
  strip2.show();
  strip3.show();
}

void loop() {
    randomSeed(analogRead(1));

    //stars(20, 3);
    rainbow(40);
}
