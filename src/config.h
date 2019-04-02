/*
  Set any config.h overrides for your specific keymap here.
  See config.h options at https://docs.qmk.fm/#/config_options?id=the-configh-file
*/
#define DISABLE_RGB_MATRIX_DIGITAL_RAIN
#define DISABLE_RGB_MATRIX_ALPHAS_MODS

#define EECONFIG_RGB_MATRIX (uint32_t *)16

// #define FORCE_NKRO
// #define QMK_KEYS_PER_SCAN 4

// Animations

#define ALECG_ENABLE_CUSTOM_ANIMATION_GRADIENT_BREATHE true // (+632)
#define ALECG_ENABLE_CUSTOM_ANIMATION_RAINBOW_HOME_KEYS true // (+384)
#define ALECG_ENABLE_CUSTOM_ANIMATION_SCANNING true // (+764)
#define ALECG_ENABLE_CUSTOM_ANIMATION_PLASMA true // (+388)
#define ALECG_ENABLE_CUSTOM_ANIMATION_TRON true // (+1530)
