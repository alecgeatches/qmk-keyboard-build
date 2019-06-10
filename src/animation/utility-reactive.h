#pragma once

#include "ergodox_ez.h"

#if ALECG_ENABLE_CUSTOM_ANIMATION_REACTIVE_HEATMAP
void alecg_reactive_heatmap_process_key(uint8_t, bool);
#endif

#if ALECG_ENABLE_CUSTOM_ANIMATION_REACTIVE_SPARKS
void alecg_reactive_sparks_process_key(uint8_t, bool);
#endif

typedef struct PACKED {
  // Global tick at ~1000 Hz
  uint32_t last_hit_tick;
} alecg_reactive_counters_t;

static alecg_reactive_counters_t alecg_reactive_counters[DRIVER_LED_TOTAL] = {{0}};

extern const rgb_led g_rgb_leds[DRIVER_LED_TOTAL];
extern rgb_counters_t g_rgb_counters;
extern uint16_t alecg_custom_animation;

void alecg_reactive_process_key(uint8_t led_i, bool pressed) {
  if(pressed) {
    alecg_reactive_counters[led_i].last_hit_tick = g_rgb_counters.tick;
  }

  #if ALECG_ENABLE_CUSTOM_ANIMATION_REACTIVE_HEATMAP
  alecg_reactive_heatmap_process_key(led_i, pressed);
  #endif

  #if ALECG_ENABLE_CUSTOM_ANIMATION_REACTIVE_SPARKS
  if(alecg_custom_animation == ALECG_CUSTOM_ANIMATION_REACTIVE_SPARKS) {
    alecg_reactive_sparks_process_key(led_i, pressed);
  }
  #endif
}
