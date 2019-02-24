#include "ergodox_ez.h"

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
