#include "util.hpp"
#include "GFX.hpp"
#include "freedeck.hpp"
#include "hardware/gpio.h"
#include "init.hpp"
#include "settings.hpp"

#ifdef DEBUG
void o_debug(const char *message, uint display) {
  set_mux_address(display);
  oled[display]->clear();
  oled[display]->drawString(0, 0, message);
  oled[display]->display();
}
#else
void o_debug(const char *message, uint display) { (void *)message; }
#endif
int getBitValue(int number, int place) { return (number & (1 << place)) >> place; }

void set_mux_address(int address, uint8_t type) {
#ifdef CUSTOM_ORDER
  if (type == TYPE_DISPLAY)
    address = addressToScreen[address];
  else if (type == TYPE_BUTTON)
    address = addressToButton[address];
#endif
  int S0 = getBitValue(address, 0);
  gpio_put(S0_PIN, S0);

#if BD_COUNT > 2
  int S1 = getBitValue(address, 1);
  gpio_put(S1_PIN, S1);
#endif

#if BD_COUNT > 4
  int S2 = getBitValue(address, 2);
  gpio_put(S2_PIN, S2);
#endif

#if BD_COUNT > 8
  int S3 = getBitValue(address, 3);
  gpio_put(S3_PIN, S3);
#endif
}
void set_mux_address(int address) { set_mux_address(address, TYPE_DISPLAY); }