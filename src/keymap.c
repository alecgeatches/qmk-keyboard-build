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
    [0] = LAYOUT_ergodox(KC_ESCAPE,KC_1,KC_2,KC_3,KC_4,KC_5,MO(3),KC_TAB,KC_Q,KC_W,KC_F,KC_P,KC_G,KC_TRANSPARENT,KC_BSPACE,KC_A,KC_R,KC_S,KC_T,KC_D,KC_LSHIFT,KC_Z,KC_X,KC_C,KC_V,KC_B,MO(5),KC_GRAVE,KC_QUOTE,KC_TRANSPARENT,LALT(KC_NO),KC_LCTRL,KC_APPLICATION,KC_LGUI, /* tF1: */ RGB_MOD,KC_SPACE,MO(2), /* tF2: */ ALECG_RGB_CUSTOM_ANIMATION,TG(1),KC_6,KC_7,KC_8,KC_9,KC_0,KC_MINUS,KC_TRANSPARENT,KC_J,KC_L,KC_U,KC_Y,KC_SCOLON,KC_BSLASH,KC_H,KC_N,KC_E,KC_I,KC_O,KC_QUOTE,KC_MEH,KC_K,KC_M,KC_COMMA,KC_DOT,KC_SLASH,KC_RSHIFT,MO(4),KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_RGUI,KC_DELETE,/* tF3: */ ALECG_RGB_TO_GRAD, /* tF4: */ ALECG_RGB_HUE_CYCLE_ONE_BUTTON,LALT(KC_NO),KC_ENTER),

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

uint8_t alecg_get_led_by_position(uint8_t row, uint8_t column) {
    static uint8_t alecg_led_mapping[5][10] = {{255}};

    if(row > 4 || column > 9) {
        return 0;
    }

    if(alecg_led_mapping[0][0] == 255) {
        uint8_t row, column;
        rgb_led led;

        // Left side
        for (uint8_t i = DRIVER_1_LED_TOTAL; i < DRIVER_LED_TOTAL; i++) {
            led = g_rgb_leds[i];
            row = led.matrix_co.row;
            column = led.matrix_co.col;

            // All columns after the first row start at index 5. If we're getting row 1+, subtract 5 first
            if(row >= 1) {
                column -= 5;
            }

            // Left side of the board goes right-to-left, so reverse column coordinate
            column = 4 - column;

            alecg_led_mapping[row][column] = i;
        }

        // Right side
        for (uint8_t i = 0; i < DRIVER_1_LED_TOTAL; i++) {
            led = g_rgb_leds[i];
            row = led.matrix_co.row;
            column = led.matrix_co.col;

            // All columns after the first row start at index 5. If we're getting row 0, add 5 first to compensate for right side
            if(row == 0) {
                column += 5;
            }

            alecg_led_mapping[row][column] = i;
        }
    }

    return alecg_led_mapping[row][column];
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

uint8_t alecg_map_row_column_to_led(uint8_t row, uint8_t column) {
    rgb_led led;

    for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
        led = g_rgb_leds[i];
        if (row == led.matrix_co.row && column == led.matrix_co.col) {
            return i;
        }
    }

    return 0;
}

enum alecg_custom_animations {
    ALECG_CUSTOM_ANIMATION_OFF = 0,
    ALECG_CUSTOM_ANIMATION_GRADIENT_BREATHE,
    ALECG_CUSTOM_ANIMATION_RAINBOW_HOME_KEYS,
    ALECG_CUSTOM_ANIMATION_SCANNING,
    // ALECG_CUSTOM_ANIMATION_REACTIVE_RED_FADE,
    ALECG_CUSTOM_ANIMATION_TRON,
    ALECG_CUSTOM_ANIMATION_LAST,
};

#define ALECG_BREATH_MAX 80
#define ALECG_BREATH_TICKS_PER_FRAME 4
#define ALECG_BREATH_CYCLE_FRAMES 250

#define ALECG_RAINBOW_HOME_KEYS_TICKS_PER_FRAME 3

#define ALECG_SCANNING_COLUMNS 10
#define ALECG_SCANNING_SCAN_TIME_MS 2000
#define ALECG_SCANNING_FALLOFF_RATE_MS 1500

#define ALECG_TRON_TURN_TIME_MS 150

uint16_t alecg_custom_animation = ALECG_CUSTOM_ANIMATION_OFF;
bool alecg_custom_animation_changed = false;
uint16_t alecg_timer;

#define ALECG_LED_HITS_TO_REMEMBER 8
uint8_t alecg_last_led_count;
uint8_t alecg_last_led_hit[ALECG_LED_HITS_TO_REMEMBER];
uint16_t alecg_key_hit_timer[DRIVER_LED_TOTAL];

bool alecg_is_valid_location(uint8_t row, uint8_t column) {
    if(row > 4 || column > 9) {
        return false;
    } else if(row == 4 && (column == 4 || column == 5)) {
        return false;
    }

    return true;
}

bool alecg_make_next_tron_move(uint8_t player, uint8_t player_positons[][10], uint8_t player_head[]) {
    int direction = rand() % 4;

    for(int move_tries = 0; move_tries < 4; move_tries += 1) {
        // Try left
        if(direction == 0) {
            if(alecg_is_valid_location(player_head[0], player_head[1] - 1) && player_positons[player_head[0]][player_head[1] - 1] == 0) {
                player_head[1] = player_head[1] - 1;
                return true;
            }

        // Try right
        } else if(direction == 1) {
            if(alecg_is_valid_location(player_head[0], player_head[1] + 1) && player_positons[player_head[0]][player_head[1] + 1] == 0) {
                player_head[1] = player_head[1] + 1;
                return true;
            }

        // Try up
        } else if(direction == 2) {
            if(alecg_is_valid_location(player_head[0] - 1, player_head[1]) && player_positons[player_head[0] - 1][player_head[1]] == 0) {
                player_head[0] = player_head[0] - 1;
                return true;
            }

        // Try down
        } else if(direction == 3) {
            if(alecg_is_valid_location(player_head[0] + 1, player_head[1]) && player_positons[player_head[0] + 1][player_head[1]] == 0) {
                player_head[0] = player_head[0] + 1;
                return true;
            }
        }

        direction = (direction + 1) % 4;
    }

    return false;
}

void alecg_run_custom_animation(bool initialize_animation) {
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
            HSV hsv = { .h = rgb_matrix_config.hue, .s = rgb_matrix_config.sat * 0.8, .v = 0 };
            rgb = hsv_to_rgb(hsv);
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }

        uint8_t home_keys[] = {
            alecg_get_led_by_position(2, 0), alecg_get_led_by_position(2, 1), alecg_get_led_by_position(2, 2), alecg_get_led_by_position(2, 3),
            alecg_get_led_by_position(2, 6), alecg_get_led_by_position(2, 7), alecg_get_led_by_position(2, 8), alecg_get_led_by_position(2, 9),
        };
        uint8_t home_keys_length = sizeof(home_keys) / sizeof(uint8_t);

        RGB rgb;
        HSV hsv = { .h = 0, .s = 160, .v = 255 };

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
            hsv.v = scan_values[column] * 255.0;

            rgb = hsv_to_rgb(hsv);
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }

    // ALECG_CUSTOM_ANIMATION_REACTIVE_RED_FADE
    // } else if(alecg_custom_animation == ALECG_CUSTOM_ANIMATION_REACTIVE_RED_FADE) {
    //     HSV hsv = { .h = 0, .s = 255, .v = 0 };
    //     RGB rgb;
    //     uint8_t led_i;
    //     uint16_t led_timer, elapsed_since_hit;

    //     rgb_matrix_set_color_all(0, 0, 0);

    //     for (uint8_t i = 0; i < alecg_last_led_count; i++) {
    //         led_i = alecg_last_led_hit[i];
    //         led_timer = alecg_key_hit_timer[i];
    //         elapsed_since_hit = timer_elapsed(led_timer);

    //         if(elapsed_since_hit > 5000) {
    //             continue;
    //         }

    //         hsv.v = (1.0 - ((float)elapsed_since_hit / 5000.0)) * 255.0;

    //         rgb = hsv_to_rgb(hsv);
    //         rgb_matrix_set_color(led_i, rgb.r, rgb.g, rgb.b);
    //     }

    // ALECG_CUSTOM_ANIMATION_TRON
    } else if(alecg_custom_animation == ALECG_CUSTOM_ANIMATION_TRON) {
        static uint8_t player_positons[5][10] = {{0}};
        static uint8_t player_one_head[2] = {0};
        static uint8_t player_two_head[2] = {0};
        static uint16_t time_since_last_turn;

        if(initialize_animation == true) {
            player_one_head[0] = 0;
            player_one_head[1] = 0;
            player_two_head[0] = 4;
            player_two_head[1] = 9;

            for(uint8_t row = 0; row < 5; row++) {
                for(uint8_t column = 0; column < 10; column++) {
                    player_positons[row][column] = 0;
                }
            }

            player_positons[0][0] = 1;
            player_positons[4][9] = 2;

            time_since_last_turn = 0;
        }

        time_since_last_turn += alecg_timer_elapsed_ms;

        if(time_since_last_turn >= ALECG_TRON_TURN_TIME_MS) {
            time_since_last_turn = 0;

            // Movement logic
            bool player_one_moved = alecg_make_next_tron_move(1, player_positons, player_one_head);
            if(player_one_moved) {
                player_positons[player_one_head[0]][player_one_head[1]] = 1;
            } else {
                bool position_reset = false;

                for(uint8_t row = 0; row < 5; row++) {
                    for(uint8_t column = 0; column < 10; column++) {
                        if(player_positons[row][column] == 1) {
                            player_positons[row][column] = 0;
                        }

                        if(!position_reset && player_positons[row][column] == 0) {
                            player_one_head[0] = row;
                            player_one_head[1] = column;
                            player_positons[row][column] = 1;
                            position_reset = true;
                        }
                    }
                }
            }

            bool player_two_moved = alecg_make_next_tron_move(2, player_positons, player_two_head);
            if(player_two_moved) {
                player_positons[player_two_head[0]][player_two_head[1]] = 2;
            } else {
                bool position_reset = false;

                for(int8_t column = 9; column >= 0; column--) {
                    for(int8_t row = 4; row >= 0; row--) {
                        if(player_positons[row][column] == 2) {
                            player_positons[row][column] = 0;
                        }

                        if(!position_reset && player_positons[row][column] == 0) {
                            player_two_head[0] = row;
                            player_two_head[1] = column;
                            player_positons[row][column] = 2;
                            position_reset = true;
                        }
                    }
                }
            }
        }

        // Draw board
        rgb_matrix_set_color_all(0, 0, 0);

        HSV player_one_hsv = { .h = 27, .s = 255, .v = 255 };
        RGB player_one_rgb = hsv_to_rgb(player_one_hsv);

        HSV player_two_hsv = { .h = 125, .s = 255, .v = 255 };
        RGB player_two_rgb = hsv_to_rgb(player_two_hsv);
        // Draw player tails
        uint8_t led_i, row, column;

        for(row = 0; row < 5; row++) {
            for(column = 0; column < 10; column++) {
                if(player_positons[row][column] == 1) {
                    led_i = alecg_get_led_by_position(row, column);
                    rgb_matrix_set_color(led_i, player_one_rgb.r, player_one_rgb.g, player_one_rgb.b);
                } else if(player_positons[row][column] == 2) {
                    led_i = alecg_get_led_by_position(row, column);
                    rgb_matrix_set_color(led_i, player_two_rgb.r, player_two_rgb.g, player_two_rgb.b);
                }
            }
        }

        // Draw player heads
        uint8_t head_i, head_brightness;
        head_brightness = ((float)time_since_last_turn / (float)ALECG_TRON_TURN_TIME_MS) * 255.0;

        player_one_hsv.v = head_brightness;
        player_one_rgb = hsv_to_rgb(player_one_hsv);
        head_i = alecg_get_led_by_position(player_one_head[0], player_one_head[1]);
        rgb_matrix_set_color(head_i, player_one_rgb.r, player_one_rgb.g, player_one_rgb.b);

        player_two_hsv.v = head_brightness;
        player_two_rgb = hsv_to_rgb(player_two_hsv);
        head_i = alecg_get_led_by_position(player_two_head[0], player_two_head[1]);
        rgb_matrix_set_color(head_i, player_two_rgb.r, player_two_rgb.g, player_two_rgb.b);
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
                if(alecg_custom_animation_changed) {
                    alecg_custom_animation_changed = false;
                    alecg_run_custom_animation(/* initialize_animation */ true);
                } else {
                    alecg_run_custom_animation(false);
                }
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
    if (record->event.pressed) {
        // uint8_t led_i = alecg_map_row_column_to_led(record->event.key.row, record->event.key.col);

        // alecg_last_led_count = 1;
        // alecg_last_led_hit[0] = led_i;
        // alecg_key_hit_timer[0] = alecg_timer;

        // if (led_count > 0) {
        //     for (uint8_t i = LED_HITS_TO_REMEMBER; i > 1; i--) {
        //         g_last_led_hit[i - 1] = g_last_led_hit[i - 2];
        //     }
        //     g_last_led_hit[0] = led[0];
        //     g_last_led_count = MIN(LED_HITS_TO_REMEMBER, g_last_led_count + 1);
        // }
        // for(uint8_t i = 0; i < led_count; i++)
        //     g_key_hit[led[i]] = 0;
        // g_any_key_hit = 0;
    }

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
                alecg_custom_animation_changed = true;
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
