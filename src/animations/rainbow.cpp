#include "animations/rainbow.h"

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

template <uint8_t num_strips>
void rainbow(std::array<Adafruit_NeoPixel, num_strips> strips, uint8_t wait) {
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
