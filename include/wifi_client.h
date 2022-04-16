#ifndef WIFI_CLIENT_H
#define WIFI_CLIENT_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#include <WiFi.h>
#include "config/wifi_config.h"

#include "light.h"

extern WiFiClient espClient;

const unsigned long timeoutInterval = 30000;
extern unsigned long previousTime;
extern unsigned long currentTime;

void assure_wifi_connected();
void wait_for_wifi_connection();
void setup_wifi();

#endif
