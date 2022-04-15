#include "light.h"

void set_all_strips_to(uint32_t color) {
  for (auto & strip : strips) {
    strip.fill(color, 0, strip.numPixels());
  }
}

void show_all_strips() {
  for (auto & strip : strips) {
    strip.show();
  }
}

void setup_strips() {
  for (auto & strip : strips) {
    strip.begin();
  }

  show_all_strips();
}
