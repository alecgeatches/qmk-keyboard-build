#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "keymap_german.h"
#include "keymap_nordic.h"

#include "quantum.h"
#include <math.h>

#include "animation/utility.c"

#if ALECG_ENABLE_CUSTOM_ANIMATION_GRADIENT_BREATHE
#include "animation/gradient-breathe.c"
#endif
#if ALECG_ENABLE_CUSTOM_ANIMATION_RAINBOW_HOME_KEYS
#include "animation/rainbow-home-keys.c"
#endif
#if ALECG_ENABLE_CUSTOM_ANIMATION_SCANNING
#include "animation/scanning.c"
#endif
#if ALECG_ENABLE_CUSTOM_ANIMATION_PLASMA
#include "animation/plasma.c"
#endif
#if ALECG_ENABLE_CUSTOM_ANIMATION_TRON
#include "animation/tron.c"
#endif

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
    [0] = LAYOUT_ergodox(KC_ESCAPE,KC_1,KC_2,KC_3,KC_4,KC_5,MO(3),KC_TAB,KC_Q,KC_W,KC_F,KC_P,KC_G,KC_TRANSPARENT,KC_BSPACE,KC_A,KC_R,KC_S,KC_T,KC_D,KC_LSHIFT,KC_Z,KC_X,KC_C,KC_V,KC_B,MO(5),KC_GRAVE,KC_QUOTE,KC_TRANSPARENT,KC_LALT,KC_LCTRL,KC_APPLICATION,KC_LGUI, /* tF1: */ RGB_MOD,KC_SPACE,MO(2),/* tF2: */ ALECG_RGB_CUSTOM_ANIMATION,TG(1),KC_6,KC_7,KC_8,KC_9,KC_0,KC_MINUS,KC_TRANSPARENT,KC_J,KC_L,KC_U,KC_Y,KC_SCOLON,KC_BSLASH,KC_H,KC_N,KC_E,KC_I,KC_O,KC_QUOTE,KC_MEH,KC_K,KC_M,KC_COMMA,KC_DOT,KC_SLASH,KC_RSHIFT,MO(4),KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_RGUI,KC_DELETE, /* tF3: */ ALECG_RGB_TO_GRAD, /* tF4: */ ALECG_RGB_HUE_CYCLE_ONE_BUTTON,LALT(KC_NO),KC_ENTER),

    [1] = LAYOUT_ergodox(KC_TRANSPARENT,KC_1,KC_2,KC_3,KC_4,KC_5,KC_TRANSPARENT,KC_TRANSPARENT,KC_Q,KC_W,KC_E,KC_R,KC_T,KC_M,KC_TRANSPARENT,KC_A,KC_S,KC_D,KC_F,KC_G,KC_TRANSPARENT,KC_Z,KC_X,KC_C,KC_V,KC_B,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,RGB_MOD,KC_TRANSPARENT,KC_TRANSPARENT,RGB_SLD,KC_TRANSPARENT,KC_6,KC_7,KC_8,KC_9,KC_0,KC_TRANSPARENT,KC_TRANSPARENT,KC_Y,KC_U,KC_I,KC_O,KC_P,KC_TRANSPARENT,KC_H,KC_J,KC_K,KC_L,KC_SCOLON,KC_TRANSPARENT,KC_TRANSPARENT,KC_N,KC_M,KC_COMMA,KC_DOT,KC_SLASH,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,RGB_HUI,RGB_HUD,KC_TRANSPARENT,KC_TRANSPARENT),

    [2] = LAYOUT_ergodox(KC_TRANSPARENT,KC_F1,KC_F2,KC_F3,KC_F4,KC_F5,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_NO,KC_TRANSPARENT,KC_TRANSPARENT,LALT(LCTL(LSFT(KC_R))),LALT(LCTL(LSFT(KC_S))),LALT(LCTL(LSFT(KC_T))),KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,RGB_VAI,KC_TRANSPARENT,KC_TRANSPARENT,RGB_VAD,KC_TRANSPARENT,KC_F6,KC_F7,KC_F8,KC_F9,KC_F10,KC_F11,KC_TRANSPARENT,KC_ASTR,KC_LCBR,KC_RCBR,KC_UNDS,KC_PLUS,KC_F12,KC_DLR,KC_LPRN,KC_RPRN,KC_KP_MINUS,KC_EQUAL,KC_TRANSPARENT,KC_TRANSPARENT,KC_PERC,KC_LBRACKET,KC_RBRACKET,KC_AT,KC_HASH,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,RGB_TOG,RGB_SLD,HSV_197_148_255,HSV_135_121_255,RGB_HUD,RGB_HUI),

    [3] = LAYOUT_ergodox(KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_MS_UP,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_MS_LEFT,KC_MS_DOWN,KC_MS_RIGHT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_MS_BTN1,KC_MS_BTN2,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_KP_SLASH,KC_KP_ASTERISK,KC_KP_MINUS,KC_TRANSPARENT,KC_TRANSPARENT,KC_AUDIO_VOL_UP,KC_7,KC_8,KC_9,KC_KP_PLUS,KC_TRANSPARENT,KC_AUDIO_VOL_DOWN,KC_4,KC_5,KC_6,KC_NO,KC_TRANSPARENT,KC_TRANSPARENT,KC_AUDIO_MUTE,KC_1,KC_2,KC_3,KC_KP_ENTER,KC_TRANSPARENT,KC_TRANSPARENT,KC_KP_0,KC_KP_DOT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_I),

    [4] = LAYOUT_ergodox(KC_TRANSPARENT,KC_TRANSPARENT,KC_NO,KC_NO,KC_NO,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_NO,KC_NO,KC_PGUP,KC_NO,KC_NO,KC_TRANSPARENT,KC_TRANSPARENT,KC_NO,KC_HOME,KC_PGDOWN,KC_END,KC_NO,KC_TRANSPARENT,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_NO,KC_NO,KC_NO,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_NO,KC_NO,KC_UP,KC_NO,KC_NO,KC_TRANSPARENT,KC_NO,KC_LEFT,KC_DOWN,KC_RIGHT,KC_NO,KC_TRANSPARENT,KC_TRANSPARENT,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT),

    [5] = LAYOUT_ergodox(KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,LALT(LCTL(LSFT(KC_7))),LALT(LCTL(LSFT(KC_8))),LALT(LCTL(LSFT(KC_9))),KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,LALT(LCTL(LSFT(KC_4))),LALT(LCTL(LSFT(KC_5))),LALT(LCTL(LSFT(KC_6))),KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,LALT(LCTL(LSFT(KC_1))),LALT(LCTL(LSFT(KC_2))),LALT(LCTL(LSFT(KC_3))),KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,LALT(LCTL(LSFT(KC_0))),KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT),

};

bool suspended = false;
rgb_config_t rgb_matrix_config;

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
        [1] = { {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {205,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {0,204,255}, {154,255,255}, {154,255,255}, {154,255,255}, {0,204,255}, {0,204,255}, {0,204,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255} },

        [2] = { {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {105,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {154,255,255}, {249,228,255}, {154,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

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

enum alecg_custom_animations {
    ALECG_CUSTOM_ANIMATION_OFF = 0,

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

uint16_t alecg_custom_animation = ALECG_CUSTOM_ANIMATION_OFF;
bool alecg_custom_animation_changed = false;
uint16_t alecg_timer;

void alecg_run_custom_animation(bool initialize_animation) {
    uint32_t tick = rgb_matrix_get_tick();
    static uint16_t alecg_timer_elapsed_ms;

    alecg_timer_elapsed_ms = timer_elapsed(alecg_timer);
    alecg_timer = timer_read();

    // Mark variables as used so that the compiler doesn't complain if animations are #ifdef'd out
    (void)tick;
    (void)alecg_timer_elapsed_ms;

    if(alecg_custom_animation == ALECG_CUSTOM_ANIMATION_OFF) {
        // Do nothing

    #if ALECG_ENABLE_CUSTOM_ANIMATION_GRADIENT_BREATHE
    } else if(alecg_custom_animation == ALECG_CUSTOM_ANIMATION_GRADIENT_BREATHE) {
        alecg_animate_gradient_breathe(tick);
    #endif

    #if ALECG_ENABLE_CUSTOM_ANIMATION_RAINBOW_HOME_KEYS
    } else if(alecg_custom_animation == ALECG_CUSTOM_ANIMATION_RAINBOW_HOME_KEYS) {
        alecg_animate_rainbow_home_keys(tick);
    #endif

    #if ALECG_ENABLE_CUSTOM_ANIMATION_SCANNING
    } else if(alecg_custom_animation == ALECG_CUSTOM_ANIMATION_SCANNING) {
        alecg_animate_scanning(initialize_animation, alecg_timer_elapsed_ms);
    #endif

    #if ALECG_ENABLE_CUSTOM_ANIMATION_TRON
    } else if(alecg_custom_animation == ALECG_CUSTOM_ANIMATION_TRON) {
        alecg_animate_tron(initialize_animation, alecg_timer_elapsed_ms);
    #endif

    #if ALECG_ENABLE_CUSTOM_ANIMATION_PLASMA
    } else if(alecg_custom_animation == ALECG_CUSTOM_ANIMATION_PLASMA) {
        alecg_animate_plasma(tick);
    #endif

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
                alecg_custom_animation = ALECG_CUSTOM_ANIMATION_OFF;
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
