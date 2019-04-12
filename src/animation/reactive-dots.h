#pragma once
#if ALECG_ENABLE_CUSTOM_ANIMATION_REACTIVE_DOTS

#include "ergodox_ez.h"

#define ALECG_REACTIVE_DOTS_TICKS_TO_KEEP_LIT 3000
#define ALECG_REACTIVE_DOTS_TICKS_TO_FADE 3000

extern const rgb_led g_rgb_leds[DRIVER_LED_TOTAL];
extern rgb_config_t rgb_matrix_config;
extern rgb_counters_t g_rgb_counters;

extern alecg_reactive_counters_t alecg_reactive_counters[DRIVER_LED_TOTAL];

void alecg_animate_reactive_dots(void) {
  for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
    HSV hsv = { 0, 255, 255 };
    uint32_t ticks_since_last_hit = g_rgb_counters.tick - alecg_reactive_counters[i].tick_hit;

    if(ticks_since_last_hit <= ALECG_REACTIVE_DOTS_TICKS_TO_KEEP_LIT) {
      RGB rgb = hsv_to_rgb(hsv);
      rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    } else if(ticks_since_last_hit > ALECG_REACTIVE_DOTS_TICKS_TO_KEEP_LIT && ticks_since_last_hit <= (ALECG_REACTIVE_DOTS_TICKS_TO_KEEP_LIT + ALECG_REACTIVE_DOTS_TICKS_TO_FADE)) {
      hsv.v = (1.0 - (ticks_since_last_hit - ALECG_REACTIVE_DOTS_TICKS_TO_KEEP_LIT)/(float)ALECG_REACTIVE_DOTS_TICKS_TO_FADE) * 255;
      RGB rgb = hsv_to_rgb(hsv);
      rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    } else {
      rgb_matrix_set_color(i, 0, 0, 0);
    }
  }
}

#endif
