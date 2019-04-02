#include "ergodox_ez.h"

#define ALECG_BREATH_MAX 80
#define ALECG_BREATH_TICKS_PER_FRAME 4
#define ALECG_BREATH_CYCLE_FRAMES 250

extern rgb_config_t rgb_matrix_config;

void alecg_animate_gradient_breathe(uint32_t tick) {
    static float breathe_current = 0;
    static uint16_t breathe_frame = 0;
    static int8_t breathe_direction = 1;

    if((tick % ALECG_BREATH_TICKS_PER_FRAME) == 0) {
        breathe_frame += breathe_direction;

        float t = (float)breathe_frame / (float)ALECG_BREATH_CYCLE_FRAMES;

        // https://easings.net
        // http://www.gizma.com/easing/
        // https://stackoverflow.com/a/25730573/770938 (ParametricBlend)
        // float sqt = square(t);
        // breathe_current = sqt / (2.0f * (sqt - t) + 1.0f);

        // https://stackoverflow.com/a/25730573/770938 (InOutQuadBlend)
        if(t <= 0.5f) {
            breathe_current = 2.0f * square(t);
        } else {
            t -= 0.5f;
            breathe_current = 2.0f * t * (1.0f - t) + 0.5;
        }

        if(breathe_frame == 0 || breathe_frame >= ALECG_BREATH_CYCLE_FRAMES) {
            breathe_direction *= -1;
        }
    }

    int16_t h1 = rgb_matrix_config.hue;
    int16_t h2 = (rgb_matrix_config.hue + 180) % 360;
    int16_t deltaH = h2 - h1;

    // Take the shortest path between hues
    if (deltaH > 127) {
        deltaH -= 256;
    } else if (deltaH < -127) {
        deltaH += 256;
    }

    // Divide delta by 4, this gives the delta per row
    deltaH /= 4;

    int16_t s1 = rgb_matrix_config.sat;
    int16_t s2 = rgb_matrix_config.hue;
    int16_t deltaS = (s2 - s1) / 4;

    HSV hsv = { .h = 0, .s = 255, .v = rgb_matrix_config.val };
    RGB rgb;
    Point point;
    for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
        // map_led_to_point( i, &point );
        point = g_rgb_leds[i].point;
        // The y range will be 0..64, map this to 0..4
        uint8_t y = (point.y >> 4);
        // Relies on hue being 8-bit and wrapping
        hsv.h = rgb_matrix_config.hue + (deltaH * y) + (int)(breathe_current * (float)ALECG_BREATH_MAX);
        hsv.s = rgb_matrix_config.sat + (deltaS * y);
        rgb = hsv_to_rgb( hsv );
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
}
