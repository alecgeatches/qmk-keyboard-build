#include "ergodox_ez.h"

#define ALECG_PLASMA_TICKS_PER_FRAME 2

uint8_t fastled_sin8(uint8_t theta);

void alecg_animate_plasma(uint32_t tick) {
    static uint8_t offset = 0;

    if((tick % ALECG_PLASMA_TICKS_PER_FRAME) == 0) {
        offset += 1;
    }

    // Draw board
    uint8_t led_i, color;
    // RGB rgb;

    for(uint8_t row = 0; row < ALECG_RGB_ROWS; row++) {
        for(uint8_t column = 0; column < ALECG_RGB_COLUMNS; column++) {
            color = fastled_sin8((column + row) * 50 - offset);

            led_i = alecg_get_led_by_position(row, column);
            rgb_matrix_set_color(led_i, color, color, color);
        }
    }
}

// FastLED 3.1's sin8_C function
// http://fastled.io/docs/3.1/group___trig.html#ga46933a9b42921c6605588268d11f7c1e
const uint8_t b_m16_interleave[] = {0, 49, 49, 41, 90, 27, 117, 10};
uint8_t fastled_sin8(uint8_t theta) {
    uint8_t offset = theta;
    if( theta & 0x40 ) {
        offset = (uint8_t)255 - offset;
    }
    offset &= 0x3F; // 0..63

    uint8_t secoffset  = offset & 0x0F; // 0..15
    if( theta & 0x40) secoffset++;

    uint8_t section = offset >> 4; // 0..3
    uint8_t s2 = section * 2;
    const uint8_t* p = b_m16_interleave;
    p += s2;
    uint8_t b   =  *p;
    p++;
    uint8_t m16 =  *p;

    uint8_t mx = (m16 * secoffset) >> 4;

    int8_t y = mx + b;
    if( theta & 0x80 ) y = -y;

    y += 128;

    return y;
}
