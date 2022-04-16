#include "wifi_client.h"

WiFiClient espClient = WiFiClient();

unsigned long previousTime = millis();
unsigned long currentTime = millis();

void assure_wifi_connected() {
  currentTime = millis();
  if ((WiFi.status() != WL_CONNECTED) && (currentTime - previousTime >= timeoutInterval)) {
    WiFi.reconnect();
    wait_for_wifi_connection();
    previousTime = currentTime;
  }
}

void wait_for_wifi_connection() {
  set_all_strips_to(Adafruit_NeoPixel::Color(255, 165, 0));
  show_all_strips();

  delay(1000);

  auto status = WiFi.status();
  while (status != WL_CONNECTED && status != WL_CONNECT_FAILED) {
    delay(1000);
    status = WiFi.status();
  }

  switch (status) {
    case WL_CONNECT_FAILED:
      set_all_strips_to(Adafruit_NeoPixel::Color(255, 0, 0));
      show_all_strips();
      break;
    case WL_CONNECTED:
      set_all_strips_to(Adafruit_NeoPixel::Color(0, 255, 0));
      show_all_strips();
      delay(2000);
      set_all_strips_to(Adafruit_NeoPixel::Color(0, 0, 0));
      show_all_strips();
      delay(1000);
      break;
    default:
      break;
  }
}

void setup_wifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  wait_for_wifi_connection();
}
