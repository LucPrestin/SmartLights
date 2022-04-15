#include "mqtt_client.h"

boolean mqtt_connected() {
  return client.connected();
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

void run_mqtt_loop() {
  client.loop();
}

std::array<bool, num_strips> get_strip_affection (String & topic) {
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
  if (length == 4) {
    ArrayToInteger converter;

    for (int i = 0; i < length; i++) {
      converter.array[i] = *payload;
      payload++;
    }

    return converter.integer;
  }

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
