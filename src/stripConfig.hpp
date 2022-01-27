#include <string>

struct StripConfig {
    StripConfig(
        int num_leds, 
        int led_pin, 
        int led_kind, 
        std::string mqtt_name
    ) : 
        num_leds(num_leds), 
        led_pin(led_pin), 
        led_kind(led_kind), 
        mqtt_name(mqtt_name) 
    {};
    
    int num_leds;
    int led_pin;
    int led_kind;
    std::string mqtt_name;
};
