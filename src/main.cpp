#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <cmath>
#include <algorithm>
#include <array>
#include <utility>

#include <WiFi.h>
#include "wifi_config.h"

#include <PubSubClient.h>
#include "mqtt_config.h"

// here goes the config you want to use
#include "./strip_configs/test_strip.h"

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

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

void stars(uint16_t count, uint8_t wait) {
  #define stepSize 1
  // reset strips
  for (auto & strip : strips) {
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
          strips[strip_index].setPixelColor(star_indices.at(strip_index).at(star_index), Adafruit_NeoPixel::Color(255 - step, 255 - step, 0));
        }
      }
      show_all_strips();
      delay(round(500.0 * wait / 255));
    }       
  }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return Adafruit_NeoPixel::Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return Adafruit_NeoPixel::Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return Adafruit_NeoPixel::Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void rainbow(uint8_t wait) {
    uint16_t i;

    for(i = 0; i < 256; i++) {
      set_all_strips_to(Wheel(i & 255));
      show_all_strips();
      delay(wait);
    }
}

void setup_strips() {
  for (auto & strip : strips) {
    strip.begin();
  }

  show_all_strips();
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

void reconnect_mqtt() {
  while (!client.connected()) {
    if (client.connect(mqtt_name)) {
      for (auto topic : topics) {
        client.subscribe(topic.c_str());
      }
    } else {
      delay(5000);
    }
  }
}

std::array<bool, num_strips> get_strip_affection (char * topic) {
  std::array<bool, num_strips> result;
  result.fill(false);

  for (int i = 0; i < num_strips; i++) {
    auto topic_string = topics_per_strip[i];
    int position = -1;

    while((position = topic_string.indexOf(topic_delimiter)) != -1) {
      auto current_strip_topic = topic_string.substring(0, position);
      if (current_strip_topic == topic) {
        result[i] = true;
        break;
      }
      topic_string = topic_string.substring(position + 1);
    }
  }

  return result;
}

uint32_t get_color_from_message(byte * payload, unsigned int length) {
  payload[length] = 0;
  String message = String((char *) payload);

  message.remove(0, color_prefix.length());
  message.remove(message.length() - color_suffix.length() - 1);
}

void mqtt_callback(const char * topic, byte * payload, unsigned int length) {
  
}

void setup_mqtt() {
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(mqtt_callback);
}

void setup() {
  setup_strips();
  setup_wifi();
  setup_mqtt();
}

void loop() {
  // if (!client.connected()) {
  //   reconnect();
  // }
  // client.loop();
  currentTime = millis();
  if ((WiFi.status() != WL_CONNECTED) && (currentTime - previousTime >= timeoutInterval)) {
    WiFi.reconnect();
    wait_for_wifi_connection();
    previousTime = currentTime;
  }

  randomSeed(analogRead(1));

  stars(20, 3);
  rainbow(40);
}
