# SmartLights

## Installation

1. Clone the repository: `git clone git@github.com:LucPrestin/SmartLights.git`
2. Ignore changes to the wifi config file: `cd SmartLights && git update-index --skip-worktree src/wifi_config.h src/mqtt_config.h`
3. Adapt the ssid and password in the `src/wifi_config.h` file
4. Adapt the server, port and name in the `src/mqtt_config.h` file
5. Flash to an ESP32
