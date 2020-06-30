include .build_config

SKETCH = kappa/kappa.cpp
CHIP = esp32

BUILD_DIR = build

LIBS = Alfredo-NoU2 \
	$(ESP_LIBS)/WiFi/src \
	$(ESP_LIBS)/WebServer/src \
	$(ESP_LIBS)/FS/src \
	$(ESP_LIBS)/SimpleBLE/src \
	ArduinoJson/src

include $(ESP_MAKE_DIR)/makeEspArduino.mk
