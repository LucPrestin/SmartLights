# SmartLights

## Installation

1. Clone the repository: `git clone git@github.com:LucPrestin/SmartLights.git`
2. Go in the project folder `cd SmartLights`
3. Ignore changes to files with passwords or other sensitive data
    - Ignore changes to the wifi config file: `git update-index --skip-worktree include/wifi_config.h`
    - Ignore changes to the mqtt config file: `git update-index --skip-worktree include/mqtt_config.h`
    - Ignore changes to the strip configs: `git update-index --skip-worktree include/strip_configs/`
4. Adapt the sensitive data from above
    - Adapt ssid and password in `include/wifi_config.h`
    - Adapt server ip and port in `include/mqtt_config.h`
    - Adapt strip names and passwords according to the config of your mqtt broker
5. Adapt any strip configs to your hardware layout or add additional configs
6. Flash to an ESP32
