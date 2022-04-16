#include <Arduino.h>

#include "wifi_client.h"
#include "mqtt_client.h"
#include "light.h"

void setup() {
  setup_strips();
  setup_wifi();
  setup_mqtt();
}

void loop() {
  assure_wifi_connected();
  assure_mqtt_connected();
  
  run_mqtt_loop();
}
