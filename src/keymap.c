#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "keymap_german.h"
#include "keymap_nordic.h"

#include "quantum.h"
#include <math.h>

#ifndef PI
#define PI 3.14159265
#endif

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  RGB_SLD,
  HSV_197_148_255,
  HSV_135_121_255,
  ALECG_RGB_TO_GRAD,
  ALECG_RGB_HUE_CYCLE_ONE_BUTTON,
  ALECG_RGB_CUSTOM_ANIMATION,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_ergodox(KC_ESCAPE,KC_1,KC_2,KC_3,KC_4,KC_5,MO(3),KC_TAB,KC_Q,KC_W,KC_F,KC_P,KC_G,KC_TRANSPARENT,KC_BSPACE,KC_A,KC_R,KC_S,KC_T,KC_D,KC_LSHIFT,KC_Z,KC_X,KC_C,KC_V,KC_B,MO(5),KC_GRAVE,KC_QUOTE,LALT(KC_NO),KC_LCTRL,KC_RCTRL,KC_APPLICATION,KC_LGUI, /* tF1: */ RGB_MOD,KC_SPACE,MO(2), /* tF2: */ ALECG_RGB_CUSTOM_ANIMATION,TG(1),KC_6,KC_7,KC_8,KC_9,KC_0,KC_MINUS,KC_TRANSPARENT,KC_J,KC_L,KC_U,KC_Y,KC_SCOLON,KC_BSLASH,KC_H,KC_N,KC_E,KC_I,KC_O,KC_QUOTE,KC_MEH,KC_K,KC_M,KC_COMMA,KC_DOT,KC_SLASH,KC_RSHIFT,MO(4),KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_RGUI,KC_DELETE,/* tF3: */ ALECG_RGB_TO_GRAD, /* tF4: */ ALECG_RGB_HUE_CYCLE_ONE_BUTTON,LALT(KC_NO),KC_ENTER),

  [1] = LAYOUT_ergodox(KC_TRANSPARENT,KC_1,KC_2,KC_3,KC_4,KC_5,KC_TRANSPARENT,KC_TRANSPARENT,KC_Q,KC_W,KC_E,KC_R,KC_T,TO(0),KC_TRANSPARENT,KC_A,KC_S,KC_D,KC_F,KC_G,KC_TRANSPARENT,KC_Z,KC_X,KC_C,KC_V,KC_B,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,RGB_MOD,KC_TRANSPARENT,KC_TRANSPARENT,RGB_SLD,KC_TRANSPARENT,KC_6,KC_7,KC_8,KC_9,KC_0,KC_TRANSPARENT,KC_TRANSPARENT,KC_Y,KC_U,KC_I,KC_O,KC_P,KC_TRANSPARENT,KC_H,KC_J,KC_K,KC_L,KC_SCOLON,KC_TRANSPARENT,KC_TRANSPARENT,KC_N,KC_M,KC_COMMA,KC_DOT,KC_SLASH,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,RGB_HUI,RGB_HUD,KC_TRANSPARENT,KC_TRANSPARENT),

  [2] = LAYOUT_ergodox(KC_TRANSPARENT,KC_F1,KC_F2,KC_F3,KC_F4,KC_F5,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_UP,KC_TRANSPARENT,KC_TRANSPARENT,TO(0),KC_KP_ENTER,KC_TRANSPARENT,KC_LEFT,KC_DOWN,KC_RIGHT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,RGB_VAI,KC_TRANSPARENT,KC_TRANSPARENT,RGB_VAD,KC_TRANSPARENT,KC_F6,KC_F7,KC_F8,KC_F9,KC_F10,KC_F11,KC_TRANSPARENT,KC_PERC,KC_LCBR,KC_RCBR,KC_UNDS,KC_PLUS,KC_F12,KC_DLR,KC_LPRN,KC_RPRN,KC_KP_MINUS,KC_EQUAL,KC_TRANSPARENT,KC_TRANSPARENT,KC_ASTR,KC_LBRACKET,KC_RBRACKET,KC_AT,KC_HASH,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,RGB_TOG,RGB_SLD,HSV_197_148_255,HSV_135_121_255,RGB_HUD,RGB_HUI),

  [3] = LAYOUT_ergodox(KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_MS_UP,KC_TRANSPARENT,KC_TRANSPARENT,TO(0),KC_TRANSPARENT,KC_TRANSPARENT,KC_MS_LEFT,KC_MS_DOWN,KC_MS_RIGHT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_MS_BTN1,KC_MS_BTN2,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_KP_SLASH,KC_KP_ASTERISK,KC_KP_MINUS,KC_TRANSPARENT,KC_TRANSPARENT,KC_AUDIO_VOL_UP,KC_7,KC_8,KC_9,KC_KP_PLUS,KC_TRANSPARENT,KC_AUDIO_VOL_DOWN,KC_4,KC_5,KC_6,KC_NO,KC_TRANSPARENT,KC_TRANSPARENT,KC_AUDIO_MUTE,KC_1,KC_2,KC_3,KC_KP_ENTER,KC_TRANSPARENT,KC_TRANSPARENT,KC_KP_0,KC_KP_DOT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_I),

  [4] = LAYOUT_ergodox(KC_TRANSPARENT,KC_TRANSPARENT,KC_NO,KC_NO,KC_NO,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_NO,KC_NO,KC_PGUP,KC_NO,KC_NO,TO(0),KC_TRANSPARENT,KC_NO,KC_HOME,KC_PGDOWN,KC_END,KC_NO,KC_TRANSPARENT,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_NO,KC_NO,KC_NO,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_NO,KC_NO,KC_UP,KC_NO,KC_NO,KC_TRANSPARENT,KC_NO,KC_LEFT,KC_DOWN,KC_RIGHT,KC_NO,KC_TRANSPARENT,KC_TRANSPARENT,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT),

  [5] = LAYOUT_ergodox(KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,LALT(LCTL(LSFT(KC_7))),LALT(LCTL(LSFT(KC_8))),LALT(LCTL(LSFT(KC_9))),KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,LALT(LCTL(LSFT(KC_4))),LALT(LCTL(LSFT(KC_5))),LALT(LCTL(LSFT(KC_6))),KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,LALT(LCTL(LSFT(KC_1))),LALT(LCTL(LSFT(KC_2))),LALT(LCTL(LSFT(KC_3))),KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,LALT(LCTL(LSFT(KC_0))),KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT),

};

bool suspended = false;
rgb_config_t rgb_matrix_config;

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    [1] = { {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {0,204,255}, {154,255,255}, {154,255,255}, {154,255,255}, {0,204,255}, {0,204,255}, {0,204,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255} },

    [2] = { {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {0,0,0}, {0,0,0}, {249,228,255}, {0,0,0}, {0,0,0}, {0,0,0}, {249,228,255}, {249,228,255}, {249,228,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [3] = { {0,0,0}, {0,0,0}, {14,255,255}, {14,255,255}, {14,255,255}, {105,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {14,255,255}, {105,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {0,0,0}, {249,228,255}, {35,255,255}, {35,255,255}, {35,255,255}, {105,255,255}, {0,0,0}, {35,255,255}, {35,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {35,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {35,255,255}, {35,255,255}, {35,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {35,255,255}, {35,255,255}, {0,0,0}, {0,0,0} },

    [4] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {250,159,255}, {0,0,0}, {0,0,0}, {0,0,0}, {250,159,255}, {250,159,255}, {250,159,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {14,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {105,255,255}, {14,255,255}, {105,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [5] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {134,255,213}, {134,255,213}, {134,255,213}, {0,0,0}, {0,0,0}, {134,255,213}, {134,255,213}, {134,255,213}, {0,0,0}, {0,0,0}, {134,255,213}, {85,203,158}, {134,255,213}, {0,0,0}, {0,0,0}, {10,225,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

};

void set_leds_color(int layer) {
  rgb_matrix_mode_noeeprom(1);
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    uint8_t val = pgm_read_byte(&ledmap[layer][i][2]);
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = val == 0 ? 0 : rgb_matrix_config.val
    };
    RGB rgb = hsv_to_rgb( hsv );
    rgb_matrix_set_color( i, rgb.r, rgb.g, rgb.b );
  }
}

enum alecg_keyboard_side {
  SIDE_LEFT = 0,
  SIDE_RIGHT = 1,
};

uint8_t alecg_get_led_by_position(uint8_t side, uint8_t row, uint8_t column) {
  static uint8_t alecg_led_mapping[2][5][5] = {{{255}}};

  if(row > 4 || column > 4) {
    return 0;
  }

  // Left side of the board goes right-to-left, so reverse column coordinate if on left side
  if(side == SIDE_LEFT) {
    column = 4 - column;
  }

  // All columns after the first row start at index 5. If we're getting row 1+, add 5 first
  if(row > 1) {
    column += 5;
  }

  if(alecg_led_mapping[0][0][0] == 255) {
    uint8_t led_count_initializer = side == SIDE_RIGHT ? 0 : DRIVER_1_LED_TOTAL;
    uint8_t led_count_end         = side == SIDE_RIGHT ? DRIVER_1_LED_TOTAL : DRIVER_LED_TOTAL;
    rgb_led led;

    for (uint8_t i = led_count_initializer; i < led_count_end; i++) {
      led = g_rgb_leds[i];
      if (row == led.matrix_co.row && column == led.matrix_co.col) {
        alecg_led_mapping[side][row][column] = i;
      }
    }
  }

  return alecg_led_mapping[side][row][column];
}

void alecg_get_position_from_index(uint8_t key_index, uint8_t *row_output, uint8_t *column_output) {
  static uint8_t alecg_position_mapping[DRIVER_LED_TOTAL][2] = {{255}};

  if(key_index > DRIVER_LED_TOTAL) {
    return;
  }

  rgb_led led;
  uint8_t row;
  uint8_t column;

  if(alecg_position_mapping[0][0] == 255) {
    for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
      led = g_rgb_leds[i];

      row = led.matrix_co.row;
      column = led.matrix_co.col;

      // All columns after the first row start at index 5. If we're getting row 1+, subtract 5 first
      if(row > 0) {
        column -= 5;
      }

      if(i < DRIVER_1_LED_TOTAL) {
        // Add 5 if the column is on the right side (first 24 LEDS)
        column += 5;
      } else {
        // Columns on left side are right-to-left. If this is the case, reverse the column index
        column = 4 - column;
      }

      alecg_position_mapping[i][0] = row;
      alecg_position_mapping[i][1] = column;
    }
  }

  if(row_output) {
    *row_output = alecg_position_mapping[key_index][0];
  }

  if(column_output) {
    *column_output = alecg_position_mapping[key_index][1];
  }
}

enum alecg_custom_animations {
  ALECG_CUSTOM_ANIMATION_OFF = 0,
  ALECG_CUSTOM_ANIMATION_GRADIENT_BREATHE,
  ALECG_CUSTOM_ANIMATION_RAINBOW_HOME_KEYS,
  ALECG_CUSTOM_ANIMATION_SCANNING,
  ALECG_CUSTOM_ANIMATION_LAST,
};

#define ALECG_BREATH_MAX 80
#define ALECG_BREATH_TICKS_PER_FRAME 4
#define ALECG_BREATH_CYCLE_FRAMES 250

#define ALECG_RAINBOW_HOME_KEYS_TICKS_PER_FRAME 3

#define ALECG_SCANNING_COLUMNS 10
#define ALECG_SCANNING_SCAN_TIME_MS 2000
#define ALECG_SCANNING_FALLOFF_RATE_MS 1500

uint16_t alecg_custom_animation = ALECG_CUSTOM_ANIMATION_OFF;
uint16_t alecg_timer;

void alecg_run_custom_animation(void) {
  uint32_t tick = rgb_matrix_get_tick();
  static uint16_t alecg_timer_elapsed_ms;

  alecg_timer_elapsed_ms = timer_elapsed(alecg_timer);
  alecg_timer = timer_read();

  // ALECG_CUSTOM_ANIMATION_GRADIENT_BREATHE
  if(alecg_custom_animation == ALECG_CUSTOM_ANIMATION_GRADIENT_BREATHE) {
    static float breathe_current = 0;
    static uint16_t breathe_frame = 0;
    static int8_t breathe_direction = 1;

    if((tick % ALECG_BREATH_TICKS_PER_FRAME) == 0) {
      breathe_frame += breathe_direction;

      float t = (float)breathe_frame / (float)ALECG_BREATH_CYCLE_FRAMES;

      // https://easings.net
      // http://www.gizma.com/easing/
      // https://stackoverflow.com/a/25730573/770938 (ParametricBlend)
      // float sqt = square(t);
      // breathe_current = sqt / (2.0f * (sqt - t) + 1.0f);

      // https://stackoverflow.com/a/25730573/770938 (InOutQuadBlend)
      if(t <= 0.5f) {
        breathe_current = 2.0f * square(t);
      } else {
        t -= 0.5f;
        breathe_current = 2.0f * t * (1.0f - t) + 0.5;
      }

      if(breathe_frame == 0 || breathe_frame >= ALECG_BREATH_CYCLE_FRAMES) {
        breathe_direction *= -1;
      }
    }

    int16_t h1 = rgb_matrix_config.hue;
    int16_t h2 = (rgb_matrix_config.hue + 180) % 360;
    int16_t deltaH = h2 - h1;

    // Take the shortest path between hues
    if (deltaH > 127) {
      deltaH -= 256;
    } else if (deltaH < -127) {
      deltaH += 256;
    }

    // Divide delta by 4, this gives the delta per row
    deltaH /= 4;

    int16_t s1 = rgb_matrix_config.sat;
    int16_t s2 = rgb_matrix_config.hue;
    int16_t deltaS = (s2 - s1) / 4;

    HSV hsv = { .h = 0, .s = 255, .v = rgb_matrix_config.val };
    RGB rgb;
    Point point;
    for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
      // map_led_to_point( i, &point );
      point = g_rgb_leds[i].point;
      // The y range will be 0..64, map this to 0..4
      uint8_t y = (point.y >> 4);
      // Relies on hue being 8-bit and wrapping
      hsv.h = rgb_matrix_config.hue + (deltaH * y) + (int)(breathe_current * (float)ALECG_BREATH_MAX);
      hsv.s = rgb_matrix_config.sat + (deltaS * y);
      rgb = hsv_to_rgb( hsv );
      rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }

  // ALECG_CUSTOM_ANIMATION_RAINBOW_HOME_KEYS
  } else if(alecg_custom_animation == ALECG_CUSTOM_ANIMATION_RAINBOW_HOME_KEYS) {
    static uint8_t v_modifier = 0;
    if((tick % ALECG_RAINBOW_HOME_KEYS_TICKS_PER_FRAME) == 0) {
      v_modifier += 1;
    }

    for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
        RGB rgb;
        HSV hsv = { .h = rgb_matrix_config.hue, .s = rgb_matrix_config.sat * 0.8, .v = rgb_matrix_config.val * 0.8 };
        rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }

    uint8_t home_keys[] = {
      alecg_get_led_by_position(SIDE_LEFT, 2, 0), alecg_get_led_by_position(SIDE_LEFT, 2, 1), alecg_get_led_by_position(SIDE_LEFT, 2, 2), alecg_get_led_by_position(SIDE_LEFT, 2, 3),
      alecg_get_led_by_position(SIDE_RIGHT, 2, 1), alecg_get_led_by_position(SIDE_RIGHT, 2, 2), alecg_get_led_by_position(SIDE_RIGHT, 2, 3), alecg_get_led_by_position(SIDE_RIGHT, 2, 4),
    };
    uint8_t home_keys_length = sizeof(home_keys) / sizeof(uint8_t);

    RGB rgb;
    HSV hsv = { .h = 0, .s = 255, .v = 255 };

    for(int i = 0; i < home_keys_length; i++) {
      uint8_t key = home_keys[i];

      hsv.h = i * (150 / home_keys_length) - v_modifier;
      rgb = hsv_to_rgb(hsv);
      rgb_matrix_set_color(key, rgb.r, rgb.g, rgb.b);
    }

  // ALECG_CUSTOM_ANIMATION_SCANNING
  } else if(alecg_custom_animation == ALECG_CUSTOM_ANIMATION_SCANNING) {
    static float scan_values[ALECG_SCANNING_COLUMNS] = {0};
    static int16_t scan_current_ms = 0;
    static int8_t scan_direction = 1;

    scan_current_ms = MIN(scan_current_ms + alecg_timer_elapsed_ms, ALECG_SCANNING_SCAN_TIME_MS);

    // https://stackoverflow.com/a/25730573/770938 (InOutQuadBlend)
    float t = ((float)scan_current_ms / (float)ALECG_SCANNING_SCAN_TIME_MS);
    if(scan_direction == -1) {
      t = 1.0 - t;
    }

    float ease_output = 0;
    if(t <= 0.5f) {
      ease_output = 2.0f * square(t);
    } else {
      t -= 0.5f;
      ease_output = 2.0f * t * (1.0f - t) + 0.5;
    }

    if(scan_current_ms >= ALECG_SCANNING_SCAN_TIME_MS) {
      scan_current_ms = 0;
      scan_direction *= -1;
    }

    float scan_location_column = ease_output * (float)(ALECG_SCANNING_COLUMNS - 1);
    float distance_from_scan_line;
    float falloff_value;

    for(uint8_t column_index = 0; column_index < ALECG_SCANNING_COLUMNS; column_index++) {
      distance_from_scan_line = fabs(scan_location_column - (float)column_index);
      falloff_value = scan_values[column_index] * (((float)ALECG_SCANNING_FALLOFF_RATE_MS - alecg_timer_elapsed_ms)/(float)ALECG_SCANNING_FALLOFF_RATE_MS);

      if(distance_from_scan_line <= 2.0) {
        // If the scan line is close to this column, set the brightness according to the distance from the line, or the current falloff value if it's higher
        scan_values[column_index] = fmaxf(falloff_value, (2.0 - distance_from_scan_line)/2.0);
      } else {
        scan_values[column_index] = falloff_value;
      }
    }

    HSV hsv = { .h = 74 , .s = 255, .v = 255 };
    RGB rgb;
    uint8_t column;

    for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
      alecg_get_position_from_index(i, /* row */ NULL, &column);
      hsv.v = (uint8_t)(scan_values[column] * 255.0);

      rgb = hsv_to_rgb(hsv);
      rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
  }
}

void rgb_matrix_indicators_user(void) {
  if(suspended) {
    return;
  }

  uint8_t layer = biton32(layer_state);
  switch (layer) {
    case 0:
      rgb_matrix_config.raw = eeprom_read_dword(EECONFIG_RGB_MATRIX);

      if(alecg_custom_animation == ALECG_CUSTOM_ANIMATION_OFF) {
        rgb_matrix_mode_noeeprom(rgb_matrix_config.mode);
        if(rgb_matrix_config.mode != 1) {
          rgb_matrix_sethsv_noeeprom(rgb_matrix_config.hue, rgb_matrix_config.sat, rgb_matrix_config.val);
        }
      } else {
        rgb_matrix_mode_noeeprom(1);
        alecg_run_custom_animation();
      }
      break;
    case 1:
      set_leds_color(1);
      break;
    case 2:
      set_leds_color(2);
      break;
    case 3:
      set_leds_color(3);
      break;
    case 4:
      set_leds_color(4);
      break;
    case 5:
      set_leds_color(5);
      break;
  }
}
const uint16_t PROGMEM fn_actions[] = {
  [1] = ACTION_LAYER_TAP_TOGGLE(1)
};

// leaving this in place for compatibilty with old keymaps cloned and re-compiled.
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case 0:
        if (record->event.pressed) {
          SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        }
        break;
      }
    return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
      break;
    case HSV_197_148_255:
      if (record->event.pressed) {
        #ifdef RGB_MATRIX_ENABLE
          rgblight_mode(1);
          rgblight_sethsv(197,148,255);
        #endif
      }
      return false;
      break;
    case HSV_135_121_255:
      if (record->event.pressed) {
        #ifdef RGB_MATRIX_ENABLE
          rgblight_mode(1);
          rgblight_sethsv(135,121,255);
        #endif
      }
      return false;
      break;
    case ALECG_RGB_TO_GRAD:
      if (record->event.pressed) {
        rgb_matrix_mode(RGB_MATRIX_GRADIENT_UP_DOWN);
      }
      return false;
      break;
    case ALECG_RGB_HUE_CYCLE_ONE_BUTTON:
      if (record->event.pressed) {
        rgb_matrix_config.raw = eeprom_read_dword(EECONFIG_RGB_MATRIX);

        uint8_t shifted = get_mods() & (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT));
        if(shifted) {
          rgb_matrix_config.hue = rgb_matrix_config.hue - 8;
        } else {
          rgb_matrix_config.hue = rgb_matrix_config.hue + 8;
        }

        if(rgb_matrix_config.hue > 255) {
          rgb_matrix_config.hue = 0;
        }

        eeprom_update_dword(EECONFIG_RGB_MATRIX, rgb_matrix_config.raw);
      }
      return false;
      break;
    case ALECG_RGB_CUSTOM_ANIMATION:
      if (record->event.pressed) {
        alecg_custom_animation++;
        alecg_timer = timer_read();

        if (alecg_custom_animation >= ALECG_CUSTOM_ANIMATION_LAST) {
          alecg_custom_animation = ALECG_CUSTOM_ANIMATION_OFF;
        }
      }
      return false;
      break;
  }
  return true;
}

uint32_t layer_state_set_user(uint32_t state) {

    uint8_t layer = biton32(state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      case 1:
        ergodox_right_led_1_on();
        break;
      case 2:
        ergodox_right_led_2_on();
        break;
      case 3:
        ergodox_right_led_3_on();
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        break;
      default:
        break;
    }
    return state;

};
