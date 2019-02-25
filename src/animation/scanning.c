#include "ergodox_ez.h"

#define ALECG_SCANNING_COLUMNS 10
#define ALECG_SCANNING_SCAN_TIME_MS 2000
#define ALECG_SCANNING_FALLOFF_RATE_MS 2000

void alecg_animate_scanning(bool initialize_animation, uint16_t elapsed_ms) {
    static float scan_values[ALECG_SCANNING_COLUMNS] = {0};
    static int16_t scan_current_ms = 0;
    static int8_t scan_direction = 1;

    scan_current_ms = MIN(scan_current_ms + elapsed_ms, ALECG_SCANNING_SCAN_TIME_MS);

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
        falloff_value = scan_values[column_index] * (((float)ALECG_SCANNING_FALLOFF_RATE_MS - elapsed_ms)/(float)ALECG_SCANNING_FALLOFF_RATE_MS);

        if(distance_from_scan_line <= 2.0) {
            // If the scan line is close to this column, set the brightness according to the distance from the line, or the current falloff value if it's higher
            scan_values[column_index] = fmaxf(falloff_value, (2.0 - distance_from_scan_line)/2.0);
        } else {
            scan_values[column_index] = falloff_value;
        }
    }

    HSV hsv = { .h = 74 , .s = 255, .v = 255 };
    RGB rgb;
    uint8_t led_i;

    for(uint8_t row = 0; row < 5; row++) {
        for(uint8_t column = 0; column < 10; column++) {
            if(row == 4 && (column == 4 || column == 5)) {
                // No LEDs here, skip
                continue;
            }

            hsv.v = scan_values[column] * 255.0;
            rgb = hsv_to_rgb(hsv);

            led_i = alecg_get_led_by_position(row, column);
            rgb_matrix_set_color(led_i, rgb.r, rgb.g, rgb.b);
        }
    }
}
