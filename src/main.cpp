#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN 12
#define NUM_LEDS 24

Adafruit_NeoPixel strip = Adafruit_NeoPixel(24, LED_PIN, NEO_GRB + NEO_KHZ800);

void stars(uint16_t count, uint8_t count_parallel, uint8_t wait) {
  #define stepSize 1
  strip.clear();

  uint8_t indices[count_parallel] = {};

  for(uint16_t i = 0; i < count; i++){
    for (uint8_t k = 0; k < count_parallel; k++) {
      indices[k] = random(0,strip.numPixels());
    }
    
    for(uint16_t j=0; j <= 255; j += stepSize){
      for (uint8_t l = 0; l < count_parallel; l++) {
        strip.setPixelColor(indices[l], strip.Color(255-j, 255-j, 0));
      }
      strip.show();
      delay(round(500.0 * wait / 255));
    }       
  }
}

uint32_t Wheel(byte WheelPos) {
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

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
    randomSeed(analogRead(1));

    stars(40, 3, 3);
    rainbow(40);

    delay (2000);
}
