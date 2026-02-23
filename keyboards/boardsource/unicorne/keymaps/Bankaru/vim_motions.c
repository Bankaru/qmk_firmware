#include "vim_motions.h"
#include "custom_keycodes.h"
#include "my_keymap.h"
#include "quantum/action_util.h"

static static void b_o_w() {
	tap_code16(LCTL(KC_RGHT);
	tap_code16(LCTL(KC_LEFT);
}

//actually, this should be switching on an enum, not the keycode.
void execute_motion(uint16_t keycode, uint8_t number) {
	switch (keycode) {
		case VI_W:
			next_word(number);
			break;
		case VI_B:
			prev_word(number);
			break;
		case VI_J:
			left_col(number);
			break;
		case VI_K:
			down_row(number);
			break;
		case VI_I:
			up_row(number);
			break;
		case VI_L:
			right_col(number);
			break;
	}
}

void execute_shift_motion(uint16_t keycode, uint8_t number) {
	switch (keycode) {
		case VI_I:
			page_up();
			break;
		case VI_J:
			soft_bol();
			break;
		case VI_K:
			page_down();
			break;
		case VI_L:
			eol();
	}
}

static void left_col(uint8_t number, bool select) {
	if (select){
		add_weak_mods(MOD_BIT(KC_LSHIFT));
		send_keyboard_report();
			for (uint8_t i = 1; i <= number; i++) {
			tap_code(KC_LEFT);
			}
		set_weak_mods(saved_weak_mods);
	} else {
		for (uint8_t i = 1; i <= number; i++) {
		tap_code(KC_LEFT);
		}
	}
}

static void up_row(uint8_t number) {
	for (uint8_t i = 1; i <= number; i++) {
	tap_code(KC_UP);
	}
}

static void down_row(uint8_t number) {
	for (uint8_t i = 1; i <= number; i++) {
	tap_code(KC_DOWN);
	}
}

static void right_col(uint8_t number) {
	for (uint8_t i = 1; i <= number; i++) {
	tap_code(KC_RGHT);
	}
}


static void prev_word(uint8_t number) {
	//get to the start of the word.
	b_o_w();
	for (uint8_t i = 1; i <= number; i++) {
		tap_code16(LCTL(KC_LEFT);
	}
}

static void next_word(uint8_t number) {
	//get to the start of the word.
	b_o_w();
	for (uint8_t i = 1; i <= number; i++) {
		tap_code16(LCTL(KC_RGHT);
	}
}

static void soft_bol(uint8_t number) {
	tap_code(KC_HOME);
}

static void eol(uint8_t number) {
	tap_code(KC_END);
}

static void page_up(uint8_t number) {
	tap_code(KC_PGUP);
}

static void page_down(uint8_t number) {
	tap_code(KC_PGDN);
}
