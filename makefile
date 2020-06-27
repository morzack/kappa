include .build_config

SKETCH = src/kappa.cpp
CHIP = esp32

LIBS = Alfredo-NoU2 \
	$(ESP_LIBS)/WiFi/src \
	$(ESP_LIBS)/WebServer/src \
	$(ESP_LIBS)/FS/src

include $(ESP_MAKE_DIR)/makeEspArduino.mk