#pragma once
#if ALECG_ENABLE_CUSTOM_ANIMATION_REACTIVE_HEATMAP

#include "ergodox_ez.h"

#define ALECG_REACTIVE_HEATMAP_MEMORY_TICKS (uint32_t)1000 * 60 * 60 * 8
extern alecg_reactive_counters_t alecg_reactive_counters[DRIVER_LED_TOTAL];

const HSV alecg_heatmap_pallete[] = {
  {0, 255, 200},
  {20, 255, 225},
  {40, 255, 235},
  {60, 255, 245},
  {80, 255, 255},
};

const uint8_t alecg_heatmap_pallete_size = sizeof(alecg_heatmap_pallete) / sizeof(alecg_heatmap_pallete[0]);

static uint16_t alecg_reactive_heatmap_counters[DRIVER_LED_TOTAL] = {0};
static uint16_t alecg_reactive_max_hit_counter = ALECG_REACTIVE_HEATMAP_MAXIMUM_HIT_COUNTER_BASE;

void alecg_animate_reactive_heatmap(void) {
  for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
    uint16_t count_hits = alecg_reactive_heatmap_counters[i];

    uint8_t pallete_color_index = ((float)count_hits/alecg_reactive_max_hit_counter) * (alecg_heatmap_pallete_size - 1);

    HSV heatmap_color_hsv = alecg_heatmap_pallete[pallete_color_index];
    RGB heatmap_color = hsv_to_rgb(heatmap_color_hsv);

    uint32_t ticks_since_last_hit = g_rgb_counters.tick - alecg_reactive_counters[i].last_hit_tick;

    if(ticks_since_last_hit < ALECG_REACTIVE_HEATMAP_MEMORY_TICKS) {
      // Do nothing
    } else if(ticks_since_last_hit < (ALECG_REACTIVE_HEATMAP_MEMORY_TICKS + ALECG_REACTIVE_HEATMAP_FADE_TICKS)) {
      uint8_t interpolation = 255.0 * (ticks_since_last_hit - ALECG_REACTIVE_HEATMAP_MEMORY_TICKS) / (float)ALECG_REACTIVE_HEATMAP_FADE_TICKS;

      RGB base_color = hsv_to_rgb(alecg_heatmap_pallete[0]);
      heatmap_color = (RGB){
        .r = lerp8by8(heatmap_color.r, base_color.r, interpolation),
        .g = lerp8by8(heatmap_color.g, base_color.g, interpolation),
        .b = lerp8by8(heatmap_color.b, base_color.b, interpolation),
      };
    } else if(ticks_since_last_hit > (ALECG_REACTIVE_HEATMAP_MEMORY_TICKS + ALECG_REACTIVE_HEATMAP_FADE_TICKS) && count_hits > 0) {
      alecg_reactive_heatmap_counters[i] = 0;

      if(count_hits >= alecg_reactive_max_hit_counter) {
        alecg_reactive_heatmap_recalculate_maximum_hits();
      }
    }

    rgb_matrix_set_color(i, heatmap_color.r, heatmap_color.g, heatmap_color.b);
  }
}

void alecg_reactive_heatmap_process_key(uint8_t key_i, bool pressed) {
  if(pressed) {
    alecg_reactive_heatmap_counters[key_i] += 1;

    if(alecg_reactive_heatmap_counters[key_i] > alecg_reactive_max_hit_counter) {
      alecg_reactive_max_hit_counter = alecg_reactive_heatmap_counters[key_i];
    }
  }
}

void alecg_reactive_heatmap_recalculate_maximum_hits(void) {
  alecg_reactive_max_hit_counter = ALECG_REACTIVE_HEATMAP_MAXIMUM_HIT_COUNTER_BASE;

  for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
    if(alecg_reactive_heatmap_counters[i] > alecg_reactive_max_hit_counter) {
      alecg_reactive_max_hit_counter = alecg_reactive_heatmap_counters[i];
    }
  }
}

#endif
