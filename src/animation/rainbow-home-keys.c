#include "ergodox_ez.h"

#define ALECG_RAINBOW_HOME_KEYS_TICKS_PER_FRAME 3

void alecg_animate_rainbow_home_keys(uint32_t tick) {
    static uint8_t v_modifier = 0;
    if((tick % ALECG_RAINBOW_HOME_KEYS_TICKS_PER_FRAME) == 0) {
        v_modifier += 1;
    }

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

        hsv.h = i * (150 / home_keys_length) - v_modifier;
        rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color(key, rgb.r, rgb.g, rgb.b);
    }
}
