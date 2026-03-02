#include <stdint.h>


typedef uint8_t my_tap_dance_mask_t; //only 7 keys available.
extern my_tap_dance_mask_t my_tap_dance_mask;

extern bool my_tap_held;

extern uint16_t my_tap_repeat_timer;
extern uint16_t my_tap_repeat_increment;
extern uint8_t saved_mods;
extern uint8_t saved_weak_mods;
