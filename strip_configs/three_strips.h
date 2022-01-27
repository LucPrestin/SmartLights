#include <vector>
#include <string>
#include "../src/stripConfig.hpp"
#include <Adafruit_NeoPixel.h>

std::vector<StripConfig> configurations {
    StripConfig(8, 19, NEO_GRB + NEO_KHZ800, "little_frame"),
    StripConfig(12, 18, NEO_GRB + NEO_KHZ800, "middle_frame"),
    StripConfig(12, 5, NEO_GRB + NEO_KHZ800, "big_frame")
};
