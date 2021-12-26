
#include QMK_KEYBOARD_H
#include <stdio.h>
#include "lily58.h"

#define L_WORKMAN 0
#define L_QWERTY (1 << 1)
#define L_NAV (1 << 2)
#define L_NUM (1 << 3)


char layer_state_str[24];

const char *read_layer_state(void) {
  switch (layer_state)
  {
  case L_WORKMAN:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Workman");
    break;
  case L_QWERTY:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: QWERTY");
    break;
  case L_NAV:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: NAV");
    break;
  case L_NUM:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: NUM");
    break;
  default:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Undef-%ld", layer_state);
  }

  return layer_state_str;
}
