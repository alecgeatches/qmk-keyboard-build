#pragma once
#if ALECG_ENABLE_CUSTOM_ANIMATION_REACTIVE_HEATMAP

#include "ergodox_ez.h"

#define ALECG_REACTIVE_HEATMAP_MEMORY_TICKS (uint32_t)1000 * 60 * 60 * 4
#define ALECG_REACTIVE_HEATMAP_FADE_TICKS 10000
#define ALECG_REACTIVE_HEATMAP_MAXIMUM_HIT_COUNTER_BASE 20

void alecg_reactive_heatmap_recalculate_maximum_hits(void);

extern const rgb_led g_rgb_leds[DRIVER_LED_TOTAL];
extern rgb_config_t rgb_matrix_config;
extern rgb_counters_t g_rgb_counters;
extern alecg_reactive_counters_t alecg_reactive_counters[DRIVER_LED_TOTAL];

const RGB alecg_heatmap_pallete[] = {
  {68,13,84},
  {72,21,104},
  {72,38,119},
  {69,55,129},
  {63,71,136},
  {57,85,140},
  {50,100,142},
  {45,112,142},
  {39,125,142},
  {35,138,141},
  {31,150,139},
  {32,163,134},
  {41,175,127},
  {60,188,117},
  {86,198,103},
  {116,208,85},
  {148,216,64},
  {184,222,41},
  {220,227,23},
  {253,231,37},
};

const uint8_t alecg_heatmap_pallete_size = sizeof(alecg_heatmap_pallete) / sizeof(alecg_heatmap_pallete[0]);

static uint16_t alecg_reactive_heatmap_counters[DRIVER_LED_TOTAL] = {0};
static uint16_t alecg_reactive_max_hit_counter = ALECG_REACTIVE_HEATMAP_MAXIMUM_HIT_COUNTER_BASE;

void alecg_animate_reactive_heatmap(void) {
  for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
    uint16_t count_hits = alecg_reactive_heatmap_counters[i];

    uint8_t pallete_color_index = ((float)count_hits/alecg_reactive_max_hit_counter) * (alecg_heatmap_pallete_size - 1);

    RGB heatmap_color = alecg_heatmap_pallete[pallete_color_index];

    uint32_t ticks_since_last_hit = g_rgb_counters.tick - alecg_reactive_counters[i].last_hit_tick;

    if(ticks_since_last_hit < ALECG_REACTIVE_HEATMAP_MEMORY_TICKS) {
      // Do nothing
    } else if(ticks_since_last_hit < (ALECG_REACTIVE_HEATMAP_MEMORY_TICKS + ALECG_REACTIVE_HEATMAP_FADE_TICKS)) {
      uint8_t interpolation = 255.0 * (ticks_since_last_hit - ALECG_REACTIVE_HEATMAP_MEMORY_TICKS) / (float)ALECG_REACTIVE_HEATMAP_FADE_TICKS;

      RGB base_color = alecg_heatmap_pallete[0];
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

void alecg_reactive_heatmap_process_key_hit(uint8_t key_i) {
  alecg_reactive_heatmap_counters[key_i] += 1;

  if(alecg_reactive_heatmap_counters[key_i] > alecg_reactive_max_hit_counter) {
    alecg_reactive_max_hit_counter = alecg_reactive_heatmap_counters[key_i];
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
