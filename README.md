# kappa
2020 season MiniFRC robot

CAD will be posted later, when I actually finish building the bot :P

## building
follow setup instructions for [makeEspArduino](https://github.com/plerup/makeEspArduino) because I am opinionated and hate the Arduino IDE

make a file `.build_config` and populate it with the following variables

- `ESP_ROOT` -- directory containing the ESP32 libs and toolchain
- `ESP_MAKE_DIR` -- directory where makeEspArduino was cloned

to build/flash, use `./build.sh`