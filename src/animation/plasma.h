#pragma once
#if ALECG_ENABLE_CUSTOM_ANIMATION_PLASMA

#include "ergodox_ez.h"

#define ALECG_PLASMA_DISTANCE_DROPOFF 100 // Out of 255
#define ALECG_PLASMA_MINIMUM_INTENSITY 50 // Out of 255

extern rgb_counters_t g_rgb_counters;
extern rgb_config_t rgb_matrix_config;

void alecg_animate_plasma(void) {
    static uint8_t points[ALECG_RGB_COLUMNS] = {0};

    uint8_t time = scale16by8(g_rgb_counters.tick, rgb_matrix_config.speed / 4);

    for(uint8_t i = 0; i < ALECG_RGB_COLUMNS; i++) {
        points[i] = sin8(i * 20 + time);
    }

    uint8_t led_i, intensity;
    HSV hsv = {.h = 0, .s = 0, .v = 255};
    RGB rgb;

    for(uint8_t row = 0; row < ALECG_RGB_ROWS; row++) {
        for(uint8_t column = 0; column < ALECG_RGB_COLUMNS; column++) {
            // Diagonal:
            // color = sin8((column + row) * 50 - offset);

            // Circular:
            // uint8_t distance_row_2 = ((float)row - (ALECG_RGB_ROWS / 2.0f)) * ((float)row - (ALECG_RGB_ROWS / 2.0f));
            // uint8_t distance_column_2 = ((float)column - (ALECG_RGB_COLUMNS / 2.0f)) * ((float)column - (ALECG_RGB_COLUMNS / 2.0f));
            // color = sin8(fastled_sqrt16(distance_row_2 + distance_column_2) * 50 - offset);

            uint8_t row_value = 255.0f * ((float)row/(ALECG_RGB_ROWS - 1));
            uint8_t distance_from_point = abs((int16_t)row_value - (int16_t)points[column]);

            if(distance_from_point > ALECG_PLASMA_DISTANCE_DROPOFF) {
                intensity = 0;
            } else {
                intensity = 255.0f * (1.0f - (float)distance_from_point / ALECG_PLASMA_DISTANCE_DROPOFF);
            }

            intensity = MAX(intensity, ALECG_PLASMA_MINIMUM_INTENSITY);

            hsv.v = intensity;

            led_i = alecg_get_led_by_position(row, column);
            rgb = hsv_to_rgb(hsv);
            rgb_matrix_set_color(led_i, rgb.r, rgb.g, rgb.b);
        }
    }
}

#endif
