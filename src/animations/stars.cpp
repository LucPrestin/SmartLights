#include "animations/stars.h"

template<uint8_t num_strips, uint8_t max_nr_stars>
void stars(
    std::array<Adafruit_NeoPixel, num_strips> strips, 
    std::array<uint8_t, num_strips> num_stars, 
    uint16_t count, 
    uint8_t wait
) {
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
