/*
  Set any config.h overrides for your specific keymap here.
  See config.h options at https://docs.qmk.fm/#/config_options?id=the-configh-file
*/

#define DISABLE_RGB_MATRIX_DIGITAL_RAIN
#define DISABLE_RGB_MATRIX_ALPHAS_MODS

#define RGB_MATRIX_KEYPRESSES

#define EECONFIG_RGB_MATRIX (uint32_t *)16

// Animations

#define ALECG_ENABLE_CUSTOM_ANIMATION_RAINBOW_HOME_KEYS false
#define ALECG_ENABLE_CUSTOM_ANIMATION_PLASMA false
#define ALECG_ENABLE_CUSTOM_ANIMATION_REACTIVE_HEATMAP false
#define ALECG_ENABLE_CUSTOM_ANIMATION_SCANNING false
#define ALECG_ENABLE_CUSTOM_ANIMATION_TRON false
#define ALECG_ENABLE_CUSTOM_ANIMATION_REACTIVE_SPARKS false
#define ALECG_ENABLE_CUSTOM_ANIMATION_GRADIENT_BREATHE false

// #define LED_HITS_TO_REMEMBER 48
