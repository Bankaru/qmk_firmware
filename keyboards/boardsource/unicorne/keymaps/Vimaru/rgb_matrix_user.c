#include "rgb_matrix_user.inc"
//#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS
//green
// static uint8_t green_r = 0;
// static uint8_t green_g = 255;
// static uint8_t green_b = 0;
// //orange
// static uint8_t orange_r = 255;
// static uint8_t orange_g = 162;
// static uint8_t orange_b = 0;
// //blue
// static uint8_t blue_r = 43;
// static uint8_t blue_g = 0;
// static uint8_t blue_b = 255;
//
//
bool my_cool_effect(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for (uint8_t i = led_min; i < led_max; i++) {
        //rgb_matrix_set_color(i, green_r, green_g, green_b);
        rgb_matrix_set_color(i, 0, 0, 255);
    }
    return rgb_matrix_check_finished_leds(led_max);
}

//RGB_MATRIX_EFFECT(my_cool_effect2)

//#endif
// void keyboard_post_init_user(void) {
//     rgb_matrix_enable();
//     rgb_matrix_mode(RGB_MATRIX_CUSTOM_my_cool_effect);
//     }


