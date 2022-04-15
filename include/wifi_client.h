#pragma once

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#include <WiFi.h>
#include "wifi_config.h"

#include "light.h"

WiFiClient espClient;

void wait_for_wifi_connection();
void setup_wifi();
