#pragma once

#include "ergodox_ez.h"

typedef struct PACKED {
  // Global tick at 20 Hz
  uint32_t tick_hit;
} alecg_reactive_counters_t;

static alecg_reactive_counters_t alecg_reactive_counters[DRIVER_LED_TOTAL] = {{0}};

extern const rgb_led g_rgb_leds[DRIVER_LED_TOTAL];
extern rgb_counters_t g_rgb_counters;

void alecg_reactive_process_record(keyrecord_t *record) {
  uint8_t row = record->event.key.row;
  uint8_t column = record->event.key.col;
  matrix_co_t matrix_co;

  // alecg: Speed could be improved by caching led values
  for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
    matrix_co = g_rgb_leds[i].matrix_co;

    if (row == matrix_co.row && column == matrix_co.col) {
      alecg_reactive_counters[i].tick_hit = g_rgb_counters.tick;
      break;
    }
  }
}
