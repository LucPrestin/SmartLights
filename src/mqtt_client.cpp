#include "mqtt_client.h"

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
