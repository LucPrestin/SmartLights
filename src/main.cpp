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
  currentTime = millis();
  if ((WiFi.status() != WL_CONNECTED) && (currentTime - previousTime >= timeoutInterval)) {
    WiFi.reconnect();
    wait_for_wifi_connection();
    previousTime = currentTime;
  }

  // if (!client.connected()) {
  //   reconnect();
  // }
  // client.loop();
}
