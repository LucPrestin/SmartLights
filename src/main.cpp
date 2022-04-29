#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

#include "constants.h"
#include "wifi_config.h"
#include "mqtt_config.h"

// ============================== build config ============================== //

// here goes the config for the strip you want to use
// only one must be uncommented

#define USE_CONFIG_TEST_STRIP 
// #define USE_CONFIG_STOOL
// #define USE_CONFIG_THREE_SHELVES
// #define USE_CONFIG_TV_LOWBOARD

#if defined(USE_CONFIG_STOOL)
    #include "strip_configs/stool.h"
#elif defined(USE_CONFIG_TEST_STRIP)
    #include "strip_configs/test_strip.h"
#elif defined(USE_CONFIG_THREE_SHELVES)
    #include "strip_configs/three_shelves.h"
#elif defined(USE_CONFIG_TV_LOWBOARD)
    #include "strip_configs/tv_lowboard.h"
#endif

// ============================== build config end ============================== //

// ============================== helpers ============================== //

union ArrayToInteger {
  byte array[4];
  uint32_t integer;
};

// ============================== helpers end ============================== //

// ============================== light ============================== //

void set_all_strips_to(uint32_t color) {
  for (auto & strip : strips) {
    strip.fill(color, 0, strip.numPixels());
  }
}

void set_strip_to(uint32_t color, int index) {
  auto & strip = strips.at(index);
  strip.fill(color, 0, strip.numPixels());
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

// ============================== light end ============================== //

// ============================== wifi ============================== //

WiFiClient espClient = WiFiClient();

const unsigned long timeoutInterval = 30000;
unsigned long previousTime = millis();
unsigned long currentTime = millis();

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

void assure_wifi_connected() {
  currentTime = millis();
  if ((WiFi.status() != WL_CONNECTED) && (currentTime - previousTime >= timeoutInterval)) {
    WiFi.reconnect();
    wait_for_wifi_connection();
    previousTime = currentTime;
  }
}

void setup_wifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  wait_for_wifi_connection();
}

// ============================== wifi end ============================== //

// ============================== mqtt ============================== //

PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void reconnect_mqtt() {
  while (!client.connected()) {
    if (client.connect(mqtt_name, mqtt_name, mqtt_password)) {
      for (auto topic : topics) {
        client.subscribe(topic.c_str());
      }
    } else {
      delay(5000);
    }
  }
}

void assure_mqtt_connected() {
  if (!client.connected()) {
    reconnect_mqtt();
  }
}

void run_mqtt_loop() {
  client.loop();
}

std::array<bool, num_strips> get_strip_affection (String & topic){
  std::array<bool, num_strips> result;
  result.fill(false);

  for (int i = 0; i < num_strips; i++) {
    auto & topic_string = topics_per_strip[i];
    result[i] = topic_string.indexOf(topic) != -1;
  }

  return result;
}

uint32_t get_color_from_message(byte * payload, unsigned int length) {
  if (length == 4 || length == 8) {
    ArrayToInteger converter;
    for (int i = 0; i < 4; i++) {
      converter.array[i] = *(payload + i);
    }
    return converter.integer;
  }

  // default black for if something went wrong
  return 0;
}

void apply_color_to_strips(String topic, byte * payload, unsigned int length) {
  auto color = get_color_from_message(payload, length);
  auto strip_affection = get_strip_affection(topic);

  for (int i = 0; i < num_strips; i++) {
    if (strip_affection.at(i)) {
      set_strip_to(color, i);
    }
  }

  show_all_strips();
}

void mqtt_callback(const char * topic, byte * payload, unsigned int length) {
  String sTopic = String(topic);

  if (sTopic.endsWith(color_suffix)) {
    apply_color_to_strips(sTopic, payload, length);
  }
}

void setup_mqtt() {
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(mqtt_callback);
}


// ============================== mqtt end ============================== //

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
