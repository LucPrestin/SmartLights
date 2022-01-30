#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <cmath>
#include <algorithm>
#include <array>

// here goes the config you want to use
#include "strip_configs/three_strips.h"

// here go the animations you want to use
#include "animations/rainbow.h"
#include "animations/stars.h"

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

    stars<num_strips, max_nr_stars>(strips, num_stars, 20, 3);
    rainbow<num_strips>(strips, 40);
}
