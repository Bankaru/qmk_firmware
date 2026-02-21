#ifdef VIM_MOTIONS
#include "action_util.h"
#include "keycodes.h"
#include "modifiers.h"
#include "vim_motions.h"
#include "my_keymap.h"
#include QMK_KEYBOARD_H

command_mask_t active_vim_commands;
//my_tap_dance_t curr_tap_dance;

void init_vim_motions(void){
	active_vim_commands = 0;
	//memset(&curr_tap_dance, 0, sizeof(curr_tap_dance));
}

bool w_vim_key(bool down) {
	if (down) {
		tap_code16(LCTL(KC_RIGHT));
				return false;
		} else {
	return true;
	}
}
//skip key E, because there is no E functionality generic to most programs.

bool r_vim_key(bool down) {
	if (!down) {
		return true;
	}
	if (get_mods() & MOD_MASK_SHIFT) {
		// this is probably not worth it.  Too hard to use, and not used often.
		//active_vim_commands |= INS_IS_ACTIVE;//not sure i even need to track this since i just go to the default level
		//tap_code(KC_INS);
		//layer_clear();
		return true;
	}
	tap_code16(S(KC_RGHT));
	tap_code(KC_LEFT);
	layer_clear();
	return false;
}

// bool y_vim_key(bool down) {
// 	if (!down) {
// 		return true;
// 	}
// 	if (my_tap_dance_mask & VI_TD_Y) {
// 		if (timer_elapsed(my_td_timer < TAPPING_TERM) {
// 			yank_line();
// 			my_tap_dance_mask &= ~0xFF;
// 			return false;
// 		}
// 	} else {How do you tell the tap dance which keypress it is looking out for?  Is it based on its location in the 
// 	//this tap dancing won't work correctly because the other commands will be sent first.
// 	//I have to wait until tapping term is passed to send.
// 	//However, you cannot have it send after a time period because process record user
// 	//only fires when typed.
// 	//you would have to start a coroutine, which you're not going to get into.
// 	//So built in tap_dance functionality is the only choice.
// 	if (get_mods() & MOD_MASK_SHIFT) {
// 		my_tap_dance_mask |= VI_TAP_DANCE_Y;
// 		timer.read(my_tap_dance_timer);
// 		tap_code16(S(KC_END));
// 		tap_code16(C(KC_C));//how will you handle terminals...Delay like before?
// 		tap_code(KC_LEFT);
// 		return false;
// 	}
//
// 	my_tap_dance_mask |= VI_TAP_DANCE_Y;
// 	tap_code16(C(KC_C));
// 	return false;
// }
void tap_dance_VI_Y(tap_dance_state_t *state, void *user_data) {
	if (state->count > 1) {
		yank_line();
	} else {
		if (get_mods() & MOD_MASK_SHIFT) {
			yank_to_eol();
		} else {
			tap_code16(C(KC_C));
		}
	}
}
void yank_to_eol() {
	// uint8_t saved_mods = get_mods();
	// clear_mods();
	// clear_oneshot_mods();
	//
	// register_code(KC_LSFT);
	 tap_code(KC_END); //this is sub ideal, but you can't un shift a shifted.
	// unregister_code(KC_LSFT);
	// 
	// tap_code16(C(KC_C));
	// tap_code(KC_LEFT);
	// tap_code(KC_RIGHT);
	//
	// set_mods(saved_mods);
}

void yank_line(void) {
	tap_code(KC_HOME);
	tap_code16(S(KC_END));
	tap_code16(C(KC_C));  //how will you handle terminals...3x tap?
	tap_code(KC_LEFT);
}

void yank(void) {
	if (get_mods() & MOD_MASK_SHIFT) {			//yank to eol
		tap_code16(S(KC_END));
		tap_code16(C(KC_C));//how will you handle terminals...3x tap?
		tap_code(KC_LEFT);
	} else {									//yank selected
		tap_code16(C(KC_C));
	}
}

bool u_vim_key(bool down) {
	if (!down) {
		return true;
	}
	tap_code16(C(KC_Z));
	return false;
}

bool o_vim_key(bool down) {
	if (down) {
		if (get_mods() & MOD_MASK_SHIFT) {
			tap_code(KC_HOME);
			tap_code(KC_ENT);
			tap_code(KC_UP);
			return false;
		}
		tap_code(KC_DOWN);
		tap_code(KC_HOME);
		tap_code(KC_ENT);
		tap_code(KC_UP);
		tap_code(KC_HOME);
		return false;
	} else {
	if (get_mods() & MOD_MASK_SHIFT) {
		tap_code(KC_HOME);
		tap_code(KC_ENT);
		tap_code(KC_UP);
		return false;
	}

	tap_code(KC_DOWN);
	tap_code(KC_HOME);
	tap_code(KC_ENT);
	tap_code(KC_UP);
	tap_code(KC_HOME);
	return false;
	}
}

bool p_vim_key (bool down) {
	if (!down) {
 		return true;
	}

	if (get_mods() & MOD_MASK_SHIFT) {
		tap_code(KC_UP);
		tap_code(KC_HOME);
		tap_code(KC_ENT);
		tap_code(KC_UP);
		tap_code16(C(KC_V));
		return false;
	}

	tap_code16(C(KC_V));
	return false;
}
#endif
			
	


