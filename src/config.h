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

#define ALECG_ENABLE_CUSTOM_ANIMATION_GRADIENT_BREATHE false // (+632)
#define ALECG_ENABLE_CUSTOM_ANIMATION_RAINBOW_HOME_KEYS false // (+250)
#define ALECG_ENABLE_CUSTOM_ANIMATION_SCANNING false // (+764)
#define ALECG_ENABLE_CUSTOM_ANIMATION_PLASMA false // (+388)
#define ALECG_ENABLE_CUSTOM_ANIMATION_TRON false // (+1530)
#define ALECG_ENABLE_CUSTOM_ANIMATION_FIRE false
