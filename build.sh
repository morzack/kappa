#!/usr/bin/zsh

# this is a file that will need to be configured manually
# should be self explanatory as to what vars are needed
source .build_config

make -f $ESP_MAKE_DIR/makeEspArduino.mk \
    ESP_ROOT=$ESP_ROOT \
    CHIP=esp32 \
    SKETCH=src/kappa.cpp \
    CUSTOM_LIBS=Alfredo-NoU2 \
    flash