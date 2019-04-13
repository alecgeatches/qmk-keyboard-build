#pragma once

#include "ergodox_ez.h"

#if ALECG_ENABLE_CUSTOM_ANIMATION_REACTIVE_HEATMAP
void alecg_reactive_heatmap_process_key_hit(uint8_t);
#endif

typedef struct PACKED {
  // Global tick at ~1000 Hz
  uint32_t last_hit_tick;
} alecg_reactive_counters_t;

static alecg_reactive_counters_t alecg_reactive_counters[DRIVER_LED_TOTAL] = {{0}};

extern const rgb_led g_rgb_leds[DRIVER_LED_TOTAL];
extern rgb_counters_t g_rgb_counters;

void alecg_reactive_process_key_hit(uint8_t key_i) {
  alecg_reactive_counters[key_i].last_hit_tick = g_rgb_counters.tick;

  #if ALECG_ENABLE_CUSTOM_ANIMATION_REACTIVE_HEATMAP
  alecg_reactive_heatmap_process_key_hit(key_i);
  #endif
}
