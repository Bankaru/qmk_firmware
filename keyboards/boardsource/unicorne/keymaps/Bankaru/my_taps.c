#ifdef MY_TAPS
#include <iso646.h>
#include "action.h"
#include "config.h"
#include "timer.h"
#include <stdint.h>
#include "custom_keycodes.h"
#include "my_taps_data.h"
#include QMK_KEYBOARD_H

bool my_tap_held = false;

static uint8_t active_my_tap;
static uint8_t taps = 0;
static uint16_t my_taps_timer = 0;
static bool completed;

void clean_up_taps(){
    my_tap_held = false;
    taps = 0;
    completed = false;
}

bool process_my_taps(uint16_t keycode, keyrecord_t *record) {
	uint8_t current_index = keycode_to_my_tap(keycode);
	if (current_index == 255) {
		return true;
		//it is not a my_tap key.  Continue processing in process_record_user
	}

	if (record->event.pressed) {
		active_my_tap = current_index;
		my_tap_held = true;

		if (taps == 0) {
			my_taps_timer = timer_read();
			taps = 1;
		} else {
			my_taps_timer = timer_read();
			taps = 2;
		}
	} 
	else {
		//i may not need this, cause you reset taps to 0;
		//well, i think need it for the second one.
		//
		//is there any thing you want to do here for on release?
		//as long as you don't do duplicate it in do_my_taps_action...
		//the only place it would fire there is 
		my_tap_held = false;
		if (taps == 2) {
			if (timer_elapsed(my_taps_timer > TAPPING_TERM)) {
				//send tap2 option; tap_code(keycode);
				return false;
			}
		}
	}

	return false;
}

void process_my_tap_timing(void) {
	if (taps == 0) {
		return;
	}

    //this is longer than the time.
	if (taps == 1 && timer_elapsed(my_taps_timer) > TAPPING_TERM) {
        //so it should fire if it is held the held effect should take place.
        //held effect should either be repeating or a different function should fire.
        completed = do_my_taps_action(active_tap_index);
		if (completed) {
			clean_up_taps();
		}
		return;
	}

	if (taps == 2 && timer_elapsed(my_taps_timer) > TAPPING_TERM) {
		completed = do_my_taps_action(active_tap_index);

		if (completed) {
			clean_up_taps();
		}
		
		//double tap hold detected, process hold
        //if its not a double tap hold, it will be processed on On Release.
	}
}





#endif

//flow summary
//First:    Key input sets Taps to one or two
//          timer is started.
//If an interrupting key comes in
//  Taps will be set to zero, and (if necessary timer also set to zero)
//
//Second:  matrix scan user calls process_my_tap_timing(), which checks if tapping time is passed.
//If it is passed and the key is not held it will do the action.
//  If it is not passed the time it will wait.
//If it is passed and the key is held it will do the held action.
//Whether or not to do the action must be determined in the do_tap_action method.
//Held Actions:
//Repeat or Consume.
//
