#include "ergodox_ez.h"

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
        return 0;
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
