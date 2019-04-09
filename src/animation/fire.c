#include "ergodox_ez.h"

// See https://github.com/mic159/NeoFire/blob/master/NeoFire.ino

#define ALEGC_FIRE_TICKS_PER_FRAME 1
#define ALECG_INTERPOLATION_PER_STEP 10 // 0-100
#define ALECG_FIRE_VALUE_MINIMUM_FLICKER 60 // 0-255
#define ALECG_FIRE_VALUE_MINIMUM_NORMAL 180 // 0-255

// these values are substracted from the generated values to give a shape to the animation
const uint8_t ALECG_FIRE_VALUE_MASK[ALECG_RGB_ROWS][ALECG_RGB_COLUMNS] = {
    {200, 160, 128, 160, 200,    200, 160, 128, 160, 200},
    {128, 96 , 64 , 96 , 128,    128, 96 , 64 , 96 , 128},
    {64 , 52 , 16 , 52 , 80 ,    80 , 52 , 16 , 52 , 64 },
    {32 , 16 , 0  , 16 , 32 ,    60 , 16 , 0  , 16 , 32 },
    {16 , 0  , 0  , 0  , 0  ,    0  , 0  , 0  , 0  , 16 },
};

// should be between 0 (red) to about 25 (yellow)
const uint8_t ALECG_FIRE_HUE_MASK[ALECG_RGB_ROWS][ALECG_RGB_COLUMNS] = {
    {0 , 0 , 1 , 0 , 0 ,    0 , 0 , 1 , 0 , 0 },
    {5 , 8 , 10, 5 , 3 ,    3 , 5 , 10, 8 , 5 },
    {12, 12, 15, 9 , 8 ,    8 , 9 , 15, 12, 12},
    {18, 26, 30, 14, 10,    10, 14, 30, 26, 18},
    {25, 36, 40, 26, 0 ,    0 , 26, 40, 36, 25},
};

uint8_t fire_value_matrix[ALECG_RGB_ROWS][ALECG_RGB_COLUMNS] = {{0}};
uint8_t fire_value_next_line[ALECG_RGB_COLUMNS] = {0};

void generate_line(void);
void shift_up(void);
void draw_fire_frame(float percent_interpolation);

void alecg_animate_fire(bool initialize_animation, uint32_t tick) {
    static float fire_interpolation_percent = 0;

    if(initialize_animation) {
        fire_interpolation_percent = 0;
        generate_line();
    }

    if(fire_interpolation_percent >= 100) {
        shift_up();
        generate_line();
        fire_interpolation_percent = 0;
    }

    draw_fire_frame(fire_interpolation_percent);

    if((tick % ALEGC_FIRE_TICKS_PER_FRAME) == 0) {
        fire_interpolation_percent += ALECG_INTERPOLATION_PER_STEP;
    }
}

void generate_line() {
    for(uint8_t i = 0; i < ALECG_RGB_COLUMNS/2; i++) {
        if(rand() % 10 == 0) {
            fire_value_next_line[i] = /* between ALECG_FIRE_VALUE_MINIMUM_FLICKER and 255 */ ALECG_FIRE_VALUE_MINIMUM_FLICKER + (uint8_t)(rand() % (255 - ALECG_FIRE_VALUE_MINIMUM_FLICKER));
        } else {
            fire_value_next_line[i] = /* between ALECG_FIRE_VALUE_MINIMUM_NORMAL and 255 */ ALECG_FIRE_VALUE_MINIMUM_NORMAL + (uint8_t)(rand() % (255 - ALECG_FIRE_VALUE_MINIMUM_NORMAL));
        }

    }
}

void shift_up() {
    for(uint8_t row = 0; row < ALECG_RGB_ROWS - 1; row++) {
        for(uint8_t column = 0; column < ALECG_RGB_COLUMNS/2; column++) {
            fire_value_matrix[row][column] = fire_value_matrix[row + 1][column];
        }
    }

    for(uint8_t column = 0; column < ALECG_RGB_COLUMNS/2; column++) {
        fire_value_matrix[ALECG_RGB_ROWS - 1][column] = fire_value_next_line[column];
    }
}

void draw_fire_frame(float percent_interpolation) {
    float interpolated_value;
    RGB rgb;
    HSV hsv = { .h = 0, .s = 255, .v = 0 };
    uint8_t led_i;

    // Bottom row interpolates with the next generated line
    for(uint8_t column = 0; column < ALECG_RGB_COLUMNS/2; column++) {
        hsv.h = ALECG_FIRE_HUE_MASK[ALECG_RGB_ROWS - 1][column];
        hsv.v = (((100.0 - percent_interpolation) * fire_value_matrix[ALECG_RGB_ROWS - 1][column] + percent_interpolation * fire_value_next_line[column]) / 100.0);

        rgb = hsv_to_rgb(hsv);

        led_i = alecg_get_led_by_position(/* row */ ALECG_RGB_ROWS - 1, column);
        rgb_matrix_set_color(led_i, rgb.r, rgb.g, rgb.b);
    }

    // 2nd-top rows interpolate with the one before it
    for(int8_t row = ALECG_RGB_ROWS - 2; row >= 0; row--) {
        for(uint8_t column = 0; column < ALECG_RGB_COLUMNS/2; column++) {
            interpolated_value = (((100.0 - percent_interpolation) * fire_value_matrix[row][column] + percent_interpolation * fire_value_matrix[row + 1][column]) / 100.0) - ALECG_FIRE_VALUE_MASK[row][column];

            hsv.h = ALECG_FIRE_HUE_MASK[row][column];
            hsv.v = MIN(MAX(interpolated_value, 0), 255);

            rgb = hsv_to_rgb(hsv);

            led_i = alecg_get_led_by_position(row, column);
            rgb_matrix_set_color(led_i, rgb.r, rgb.g, rgb.b);
        }
    }
}
