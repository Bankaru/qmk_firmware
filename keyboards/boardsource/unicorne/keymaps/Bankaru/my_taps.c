#ifdef MY_TAPS
#include <iso646.h>
#include "action.h"
#include "config.h"
#include "timer.h"
#include <stdint.h>
#include "custom_keycodes.h"
#include "my_taps_data.h"
#include "my_taps.h"
#include QMK_KEYBOARD_H

bool my_tap_held = false;
bool my_taps_interrupt = false;

static uint8_t active_my_tap;
static uint8_t taps = 0;
static uint16_t my_taps_pressed_timer = 0;
static uint16_t my_taps_gap_timer = 0;
static bool completed;

void clean_up_taps(){
    //my_tap_held = false;
    taps = 0;
    completed = false;
	active_my_tap = 255;
	repeat_started = false;
	my_taps_interrupt = false;
	//set my_taps_pressed_timer = 0;  No need as long as timer_elapsed is always logically behind timer_read
}

bool process_my_taps(uint16_t keycode, keyrecord_t *record) {
	uint8_t current_index = keycode_to_my_tap(keycode);
	if (current_index == 255) {
		if (taps != 0) {
			if (!my_tap_held) {
			do_my_taps_action(active_my_tap, taps);
			//You might need a mod flag for the action mask.
			clean_up_taps();
			 }
			// else if (mod_active) {
			// 	you don't really need to do anything....
			//  because the mod is already active.
			// }
		}

		if (mod_active) {
			my_taps_interrupt = true;
		}

		return true;
		//It is not a my_tap key.  Continue processing in process_record_user
	}


	if (record->event.pressed) {
		// this currently cannot handle holding multiple buttons if they are tap buttons.
		// you could make:
		// 	a mask to handle multiple active_my_tap
		// 	a mask to handle multiple my_tap_held
		//  a corresponding uint16_t[] to handle multiple timings.	
		// 
		// if (active_my_tap != current_index){
		// 	if (taps == 1) {
		// 		DoOneTapAction(active_my_tap, my_tap_held);
		// 	} else if (taps == 2) {
		// 		DoTwoTapAction(active_my_tap, my_tap_held);
		// 	}
		// 	clean_up_taps();
		// }
		// Let's handle the basic tap functionality first.

		active_my_tap = current_index;
		my_tap_held = true;
		my_taps_pressed_timer = timer_read();
		// if (taps == 0) {
		// 	my_taps_pressed_timer = timer_read();
		// 	taps = 1;
		// } else {
		// 	my_taps_pressed_timer = timer_read();
		// 	taps = 2;
		// }
		do_my_taps_down_action(active_my_tap, taps);
		
	} 
	else {
		//i may not need this, cause you reset taps to 0;
		//well, i think need it for the second one.
		uint16_t elapsed = timer_elapsed(my_taps_pressed_timer);
		if (elapsed < TAPPING_TERM && my_taps_interrupt == false) {
			if (taps == 0) {
				taps = 1;
			} else {
				taps = 2;
			}
			my_taps_gap_timer = timer_read();
		}

		if (mod_active) {
			//for do-while-held stuff.
			do_my_taps_release_action(active_my_tap, taps);
			mod_active = false;
			my_taps_interrupt = false;
		} 
		else if (elapsed >= TAPPING_TERM) {
			//for fire-after-hold stuff.
			//this is probably irrelevant...
			//this should happen in the timing method.
			do_my_taps_release_action(active_my_tap, taps);
		}
		
		my_tap_held = false;

		//my_taps_gap_timer = timer_read();
		//commented out because at this time we only want double taps to be possible,
		//not hold + taps


		//you might need to start counting taps from the release so that the hold
		//can happen while held, and then the tap can happen if it released before
		//the tapping term?
		//Then double tap happens if it is released again before another tapping term?
		//So potentially waiting 2 tapping terms.
		
		//is there any thing you want to do here for on release?
		//as long as you don't do duplicate it in do_my_taps_action...
		//the only place it would fire there is 
	
		// if (taps == 2) {
		// 	if (timer_elapsed(my_taps_pressed_timer > TAPPING_TERM)) {
		// 		//send tap2 option; tap_code(keycode);
		// 		return false;
		// 	}
		// }
	}

	return false;
}

void process_my_tap_timing(void) {
	if (taps == 0) {
		return;
	}

	uint16_t elapsed = timer_elapsed(my_taps_gap_timer);
    //this is longer than the time.
	if (taps == 1 && elapsed > TAPPING_TERM) {
        //so it should fire if it is held the held effect should take place.
        //held effect should either be repeating or a different function should fire.
		//That is handled in do_my_taps_action.
        completed = do_my_taps_action(active_my_tap, taps);
		if (completed) {
			clean_up_taps();
		}
		return;
	}

	if (taps == 2 && elapsed > TAPPING_TERM) {
		completed = do_my_taps_action(active_my_tap, taps);

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
//If the time is passed
//	if key is not held it will do tap actions
//	if the key is held it will do hold actions or tap actions
//	
//If the time is not passed the time it will wait.
//
//Whether or not to do the action must be determined in the do_tap_action method.
//Held Actions:
//Repeat or Consume.
//
