#pragma once

#include "ergodox_ez.h"

#if !defined(PI)
#define PI 3.14159265
#endif

enum alecg_custom_animations {
  ALECG_CUSTOM_ANIMATION_OFF = 0,

  #if ALECG_ENABLE_CUSTOM_ANIMATION_REACTIVE_SPARKS
  ALECG_CUSTOM_ANIMATION_REACTIVE_SPARKS,
  #endif
  #if ALECG_ENABLE_CUSTOM_ANIMATION_REACTIVE_HEATMAP
  ALECG_CUSTOM_ANIMATION_REACTIVE_HEATMAP,
  #endif
  #if ALECG_ENABLE_CUSTOM_ANIMATION_GRADIENT_BREATHE
  ALECG_CUSTOM_ANIMATION_GRADIENT_BREATHE,
  #endif
  #if ALECG_ENABLE_CUSTOM_ANIMATION_RAINBOW_HOME_KEYS
  ALECG_CUSTOM_ANIMATION_RAINBOW_HOME_KEYS,
  #endif
  #if ALECG_ENABLE_CUSTOM_ANIMATION_PLASMA
  ALECG_CUSTOM_ANIMATION_PLASMA,
  #endif
  #if ALECG_ENABLE_CUSTOM_ANIMATION_SCANNING
  ALECG_CUSTOM_ANIMATION_SCANNING,
  #endif
  #if ALECG_ENABLE_CUSTOM_ANIMATION_TRON
  ALECG_CUSTOM_ANIMATION_TRON,
  #endif

  ALECG_CUSTOM_ANIMATION_LAST
};

#define ALECG_RGB_ROWS 5
#define ALECG_RGB_COLUMNS 10

/*
  Ergodox EZ Glow LED positions look like this:

  | left side     |    right side |
  ---------------------------------
  28 27 26 25 24  |  00 01 02 03 04
  33 32 31 30 29  |  05 06 07 08 09
  38 37 36 35 34  |  10 11 12 13 14
  43 42 41 40 39  |  15 16 17 18 19
  47 46 45 44     |     20 21 22 23

  To get led_i, do some math depending on the side
*/

uint8_t alecg_get_led_by_position(uint8_t row, uint8_t column) {
  if(row > 4 || column > 9) {
    return 255;
  } else if(row == 4 && (column == 4 || column == 5)) {
    // No LEDs in these two places on Ergodox EZ
    return 255;
  }

  // Adjust column for missing LED in last row
  if(row == 4) {
    if(column <= 4) {
      // Left side
      column += 1;
    } else {
      // Right side
      column -= 1;
    }
  }

  if(column <= 4) {
    // Left side
    return 24 + (4 - column) + row * 5;
  } else {
    // Right side
    return column - 5 + row * 5;
  }
}

void alecg_get_position_by_led(uint8_t key_i, uint8_t *row, uint8_t *column) {
  *row = 0;
  *column = 0;

  // Right side
  if(key_i < 24) {
    *column = 5 + (key_i % 5);
    if(key_i >= 20) {
      *column += 1;
    }

    *row = key_i / 5;

  // Left side
  } else if(key_i < 48) {
    key_i -= 24;
    *column = (4 - (key_i % 5));
    if(key_i >= 20) {
      *column -= 1;
    }

    *row = key_i / 5;
  }
}