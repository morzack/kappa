include .build_config

SKETCH = kappa/kappa.cpp
CHIP = esp32

BUILD_DIR = build

LIBS = $(ESP_LIBS)/WiFi/src \
	$(ESP_LIBS)/WebServer/src \
	$(ESP_LIBS)/FS/src \
	$(ESP_LIBS)/SimpleBLE/src \
	$(ESP_LIBS)/HTTPClient/src \
	$(ESP_LIBS)/WiFiClientSecure/src \
	Alfredo-NoU2 \
	ArduinoWebsockets/src \
	ArduinoJson/src

include $(ESP_MAKE_DIR)/makeEspArduino.mk
