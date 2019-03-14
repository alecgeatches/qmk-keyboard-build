#include "ergodox_ez.h"

#define ALECG_PLASMA_TICKS_PER_FRAME 2
#define ALECG_PLASMA_DISTANCE_DROPOFF 100 // Out of 255
#define ALECG_PLASMA_MINIMUM_INTENSITY 50 // Out of 255

uint8_t fastled_sin8(uint8_t theta);
uint8_t fastled_sqrt16(uint16_t x);

void alecg_animate_plasma(uint32_t tick) {
    static uint8_t points[ALECG_RGB_COLUMNS] = {0};
    static uint8_t offset = 0;

    if((tick % ALECG_PLASMA_TICKS_PER_FRAME) == 0) {
        offset += 1;
    }

    for(uint8_t i = 0; i < ALECG_RGB_COLUMNS; i++) {
        points[i] = fastled_sin8(i * 20 + offset);
    }

    // Draw board
    uint8_t led_i, intensity;
    HSV hsv = {.h = 0, .s = 0, .v = 255};
    RGB rgb;

    for(uint8_t row = 0; row < ALECG_RGB_ROWS; row++) {
        for(uint8_t column = 0; column < ALECG_RGB_COLUMNS; column++) {
            // Diagonal:
            // color = fastled_sin8((column + row) * 50 - offset);

            // Circular:
            // uint8_t distance_row_2 = ((float)row - (ALECG_RGB_ROWS / 2.0f)) * ((float)row - (ALECG_RGB_ROWS / 2.0f));
            // uint8_t distance_column_2 = ((float)column - (ALECG_RGB_COLUMNS / 2.0f)) * ((float)column - (ALECG_RGB_COLUMNS / 2.0f));
            // color = fastled_sin8(fastled_sqrt16(distance_row_2 + distance_column_2) * 50 - offset);;

            // Red fire hue between 0 and 43
            // Blue fire hue between 160 and 173
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

// FastLED 3.1's sin8_C function
// http://fastled.io/docs/3.1/group___trig.html
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

// FastLED 3.1's sqrt16 function
// http://fastled.io/docs/3.1/group___math.html