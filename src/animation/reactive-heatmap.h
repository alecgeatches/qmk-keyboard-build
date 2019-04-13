#pragma once
#if ALECG_ENABLE_CUSTOM_ANIMATION_REACTIVE_HEATMAP

#include "ergodox_ez.h"

extern const rgb_led g_rgb_leds[DRIVER_LED_TOTAL];
extern rgb_config_t rgb_matrix_config;
extern rgb_counters_t g_rgb_counters;
extern alecg_reactive_counters_t alecg_reactive_counters[DRIVER_LED_TOTAL];

const RGB alecg_heatmap_pallete[] = {
  {127,0,0},
  {179,0,0},
  {215,48,31},
  {239,101,72},
  {252,141,89},
  {253,187,132},
  {253,212,158},
  {254,232,200},
  {255,247,236},
};

const uint8_t alecg_heatmap_pallete_size = sizeof(alecg_heatmap_pallete) / sizeof(alecg_heatmap_pallete[0]);

static uint16_t alecg_reactive_heatmap_counters[DRIVER_LED_TOTAL] = {0};
static uint16_t alecg_reactive_max_hit_counter = 0;

void alecg_animate_reactive_heatmap(void) {
  for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
    uint16_t count_hits = alecg_reactive_heatmap_counters[i];

    if(count_hits > alecg_reactive_max_hit_counter) {
      alecg_reactive_max_hit_counter = count_hits;
    }

    uint8_t pallete_color_index = ((float)count_hits/alecg_reactive_max_hit_counter) * (alecg_heatmap_pallete_size - 1);

    RGB rgb = alecg_heatmap_pallete[pallete_color_index];
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
  }
}

void alecg_reactive_heatmap_process_key_hit(uint8_t key_i) {
  alecg_reactive_heatmap_counters[key_i] += 1;
}


// for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
//   HSV hsv = { 0, 255, 255 };
//   uint32_t ticks_since_last_hit = g_rgb_counters.tick - alecg_reactive_counters[i].last_hit_tick;

//   if(ticks_since_last_hit <= ALECG_REACTIVE_DOTS_TICKS_TO_KEEP_LIT) {
//     RGB rgb = hsv_to_rgb(hsv);
//     rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
//   } else if(ticks_since_last_hit > ALECG_REACTIVE_DOTS_TICKS_TO_KEEP_LIT && ticks_since_last_hit <= (ALECG_REACTIVE_DOTS_TICKS_TO_KEEP_LIT + ALECG_REACTIVE_DOTS_TICKS_TO_FADE)) {
//     hsv.v = (1.0 - (ticks_since_last_hit - ALECG_REACTIVE_DOTS_TICKS_TO_KEEP_LIT)/(float)ALECG_REACTIVE_DOTS_TICKS_TO_FADE) * 255;
//     RGB rgb = hsv_to_rgb(hsv);
//     rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
//   } else {
//     rgb_matrix_set_color(i, 0, 0, 0);
//   }
// }

#endif
