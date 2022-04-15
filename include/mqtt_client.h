#pragma once

#include <PubSubClient.h>

#include "wifi_client.h"
#include "mqtt_config.h"

PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

union ArrayToInteger {
  byte array[4];
  uint32_t integer;
};

boolean mqtt_connected();
void reconnect_mqtt();
void run_mqtt_loop();
std::array<bool, num_strips> get_strip_affection (char * topic);
uint32_t get_color_from_message(byte * payload, unsigned int length);
void mqtt_callback(const char * topic, byte * payload, unsigned int length);
void setup_mqtt();
