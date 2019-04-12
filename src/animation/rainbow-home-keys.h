#pragma once
#if ALECG_ENABLE_CUSTOM_ANIMATION_RAINBOW_HOME_KEYS

#include "ergodox_ez.h"

extern rgb_counters_t g_rgb_counters;
extern rgb_config_t rgb_matrix_config;

void alecg_animate_rainbow_home_keys(void) {
    uint8_t time = scale16by8(g_rgb_counters.tick, rgb_matrix_config.speed / 4);

    rgb_matrix_set_color_all(0, 0, 0);

    uint8_t home_keys[] = {
        alecg_get_led_by_position(2, 0), alecg_get_led_by_position(2, 1), alecg_get_led_by_position(2, 2), alecg_get_led_by_position(2, 3),
        alecg_get_led_by_position(2, 6), alecg_get_led_by_position(2, 7), alecg_get_led_by_position(2, 8), alecg_get_led_by_position(2, 9),
    };
    uint8_t home_keys_length = sizeof(home_keys) / sizeof(uint8_t);

    RGB rgb;
    HSV hsv = { .h = 0, .s = 160, .v = 255 };

    for(int i = 0; i < home_keys_length; i++) {
        uint8_t key = home_keys[i];

        hsv.h = i * (150 / home_keys_length) - time;
        rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color(key, rgb.r, rgb.g, rgb.b);
    }
}

#endif
