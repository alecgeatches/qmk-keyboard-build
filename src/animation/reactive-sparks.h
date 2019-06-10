#pragma once
#if ALECG_ENABLE_CUSTOM_ANIMATION_REACTIVE_SPARKS

#define ALECG_SPARKS_BOARD_MARGIN 1
#define ALECG_SPARKS_BOARD_WIDTH 2*ALECG_SPARKS_BOARD_MARGIN + ALECG_RGB_COLUMNS
#define ALECG_SPARKS_BOARD_HEIGHT 2*ALECG_SPARKS_BOARD_MARGIN + ALECG_RGB_ROWS
#define ALECG_SPARKS_BOARD_COORDINATE_MAX 65535

#include "ergodox_ez.h"

void alecg_sparks_get_board_coordinates_by_led(uint8_t, uint16_t *, uint16_t *);

extern const rgb_led g_rgb_leds[DRIVER_LED_TOTAL];
extern rgb_config_t rgb_matrix_config;
extern rgb_counters_t g_rgb_counters;
extern alecg_reactive_counters_t alecg_reactive_counters[DRIVER_LED_TOTAL];

uint16_t spark_x = 0;
uint16_t spark_y = 0;

void alecg_animate_reactive_sparks(void) {
  HSV hsv = {.h = 0, .s = 0, .v = 0};
  RGB rgb;

  for (uint8_t key_i = 0; key_i < DRIVER_LED_TOTAL; key_i++) {
    uint16_t led_x, led_y;
    alecg_sparks_get_board_coordinates_by_led(key_i, &led_x, &led_y);

    // uint16_t dx = led_x > spark_x ? (led_x - spark_x) : (spark_x - led_x);
    // uint16_t dy = led_y > spark_y ? (led_y - spark_y) : (spark_y - led_y);
    // uint16_t dist = sqrt16(dx * dx + dy * dy);

    if(led_x == spark_x && led_y == spark_y) {
      hsv.v = 200;
    } else {
      hsv.v = 0;
    }

    // hsv.v = ((float)dist / ALECG_SPARKS_BOARD_COORDINATE_MAX) * 255;

    rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(key_i, rgb.r, rgb.g, rgb.b);
  }
}

void alecg_sparks_get_board_coordinates_by_led(uint8_t key_i, uint16_t *board_x, uint16_t *board_y) {
  uint8_t row, column;
  alecg_get_position_by_led(key_i, &row, &column);

  // Might be optimizeable
  *board_x = ((ALECG_SPARKS_BOARD_MARGIN + .5f + column)/(float)ALECG_SPARKS_BOARD_WIDTH) * ALECG_SPARKS_BOARD_COORDINATE_MAX;
  *board_y = ((ALECG_SPARKS_BOARD_HEIGHT + .5f + row)/(float)ALECG_SPARKS_BOARD_HEIGHT) * ALECG_SPARKS_BOARD_COORDINATE_MAX;
}

void alecg_reactive_sparks_process_key(uint8_t key_i, bool pressed) {
  if(pressed) {
    alecg_sparks_get_board_coordinates_by_led(key_i, &spark_x, &spark_y);
  }
}

#endif
