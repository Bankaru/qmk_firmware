#include "my_taps_data.h"

enum uint8_t MY_TAP_CODES {
	ZERO_SYM,
}; 

my_tap_t zero_sym;

my_tap_t my_taps[] {
	zero_sym,
};

uint16_t my_taps_hold_timer;
uint8_t delay_index = 0;
uint16_t delay_times[] {
	REPEAT_DELAY,
	REPEAT_INTERVAL,
};
//put most of this in a my_taps_actions.c file.
static bool default_cleanup();

//the bool says if the action is completed or not.
//repeatable actions will be false (not completed) until my_tap_held is no longer true.
bool do_my_taps_action(uint8_t index) {
	switch (index) {
		case ZERO_SYM:
			//set complete if it should be set complete.
			if (!my_tap_held) {
				if (!my_taps[ZERO_SYM].fire_on_hold) {
					if (taps == 1) {// this differentiation is not clean...
						layer_invert(_SYM);//you have to handle the swap in AND swap out
										   //
						//this might result in always a quick extra tap at the end of repeatables.
					} else {
						tap_code(KC_0);
					}
				}
				return true;
			}
			
			//for repeatable tasks taps:
			if (my_taps[ZERO_SYM].repeatable) {
				if (repeat_tap_action() {
					if (taps == 1) {
						tapcode(KC_0);
					} else {
						//nothing for a layer change.
					}
				}
				return false;
			}
			else {// a non-repeatable, fire on hold key.
				//tap_code(TP_SYM);
				return true;
			}
			
			//for hold tasks:
			//probably don't have to do anything, just handle it in release.
			
		}
	}
}

static void default_cleanup() {
	taps = 0;
	completed = false;
}

//the bool result says if it is time to do the action.
static bool repeat_tap_action() {
	if (repeat_started) {
		if (timer_elapsed(my_taps_hold_timer) > delay_times[delay_index]) {
			delay_index = 1;
			my_taps_repeat_timer = timer_read();
			return true;
		} else {
			return false;
		} 
	} else {
		my_taps_hold_timer = timer_read();
		delay_index = 0;
		repeat_started = true;
		return false;
	}
}

static bool fire_held_key() {
	if (timer_elapsed(my_taps_timer) >= TAPPING_TERM * 2) {
		return true;
	}
}	


uint8_t keycode_to_my_tap(uint16_t keycode){
	switch (keycode) {
		case TP_SYM:
			return ZERO_SYM;

		default: return 255;
	}
}
