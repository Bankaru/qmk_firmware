#include "my_taps_data.h"
#include "my_taps.h"
#include "custom_keycodes.h"

static bool repeat_tap_action(void);

enum {
    ZERO_SYM,
} MY_TAP_CODES;

my_tap_t my_taps[1] = {
    [ZERO_SYM] = {
            .action_mask = 0b0001110,
        },
};

static bool repeat_started;
uint16_t my_taps_hold_timer;
uint8_t  delay_index    = 0;
uint16_t delay_times[2] = {
    REPEAT_DELAY,
    REPEAT_INTERVAL,
};
// put most of this in a my_taps_actions.c file.
// static bool default_cleanup(); use clean_up_taps from my_taps.c
//
// We should only arrive at this function when the timer has exceeded TAPPING_TERM after a tap
// the bool says if the action is completed or not.
// repeatable actions will be false (not completed) until my_tap_held is no longer true.
bool do_my_taps_action(uint8_t index, uint8_t taps) {
    // set complete if it should be set complete.
    switch (index) {
        case ZERO_SYM:
            if (!my_tap_held) {
                if ((my_taps[ZERO_SYM].action_mask & ONE_TAP_HOLDABLE) == 0) {
                    if (taps == 1) {        // this differentiation is not clean...
                        layer_invert(_SYM); // you have to handle the swap in AND swap out
                                            //
                                            // this might result in always a quick extra tap at the end of repeatables.
                    } else {                // taps == 2
                        tap_code(KC_0);
                    }
                }
                return true;
            }

            // for repeatable task taps and holds:
            if ((my_taps[ZERO_SYM].action_mask & ONE_TAP_REPEATABLE) || (my_taps[ZERO_SYM].action_mask & TWO_TAP_REPEATABLE)) {
                if (repeat_tap_action()) {
                    if (taps == 1) {
                        // Layer change is not repeatable, however
                        // It should do MT(SYM_Layer) until released.
                        // This doesn't work since 0 is repeatable but SYM toggle is not.
                    } else { // taps == 2
                        tap_code(KC_0);
                    }
                }
                return false;
            } else { // a non-repeatable, fire on hold key.
                     // tap_code(TP_SYM);
                return true;
            }

            // for hold tasks:
            // probably don't have to do anything, just handle it in release.
    }

    return false;
}

void do_my_taps_release_action(uint8_t index, uint8_t taps) {
    if ((taps == 1) && (my_taps[index].action_mask & ONE_TAP_ON_RELEASE)) {
        // do the action that corresponds to the one tap on release;
        clean_up_taps();
        return;
    }
    if ((taps == 2) && (my_taps[index].action_mask & TWO_TAP_ON_RELEASE)) {
        // do the action that corresponds to double tap on release;
        clean_up_taps();
        return;
    }
}

// static void default_cleanup() {
// 	taps = 0;
// 	completed = false;
// }

// the bool result says if it is time to do the action.
static bool repeat_tap_action() {
    if (repeat_started) {
        if (timer_elapsed(my_taps_hold_timer) > delay_times[delay_index]) {
            delay_index        = 1;
            my_taps_hold_timer = timer_read();
            return true;
        } else {
            return false;
        }
    } else {
        my_taps_hold_timer = timer_read();
        delay_index        = 0;
        repeat_started     = true;
        return false;
    }
}

uint8_t keycode_to_my_tap(uint16_t keycode) {
    switch (keycode) {
        case TP_SYM:
            return ZERO_SYM;

        default:
            return 255;
    }
}
