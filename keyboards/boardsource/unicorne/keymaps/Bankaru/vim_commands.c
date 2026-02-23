#include "vim_commands.h"
#include "vim_motions.h"
#include "custom_keycodes.h"
#include <stdint.h>
#include "action.h"
#include "keycodes.h"

vim_command_t vim_command;
bool command_mode_active;

void init_vim_commands(void) {
	memset(vim_command, 0, sizeof(vim_command));
	command_mode_active = false;
}

void next_word(uint8_t number = 0) {
	for (uint8_t i = 0; i < number; i++) {
		tap_code16(LCTL(KC_RGHT);
	}
}
				
void yank() {
	
}


void yankline() {

}

void delete() {

}

bool update_vim_command(uint16_t keycode) {
	switch (keycode) {
		case KC_0: case KC_KP_0:
		case KC_1: case KC_KP_1:
		case KC_2: case KC_KP_2:
		case KC_3: case KC_KP_3:
		case KC_4: case KC_KP_4:
		case KC_5: case KC_KP_5:
		case KC_6: case KC_KP_6:
		case KC_7: case KC_KP_7:
		case KC_8: case KC_KP_8:
		case KC_9: case KC_KP_9:
			vim_command.number = keycode_to_digit(keycode);
			return false;	
		
		//VI_Q..command... it's complicated...
		case VI_W: //motion.
		//VI_E can't be done
		case VI_Y: //Op 		Command
		case VI_U: //Command
		case VI_I: //Command (in my H position)
		case VI_O: //Command
		case VI_P: //Op
		case VI_{: //Motion
		case VI_}: //Motion
		case VI_(: //Motion
		case VI_): //Motion
		//VI_[:  Dunno...
		//VI_]:  Dunno...
		case VI_A: //Command	
		case VI_S: //Command
		case VI_D: //Op 		Command
		//VI_F can't be done
		case VI_G: //extra //motion
		case VI_H: //Motion		-> I use "home"
				   //(in my J position)
		case VI_J: //Motion 	-> I use "page down"	join lines not used...yet.
				   //(in my k position)
		case VI_K: //Motion		-> I use "page up." 	help not used. ever.
				   //(in my I position)
		case VI_L: //Motion		-> I use "end"
		case VI_;: //Motion,	Command
				   //but isn't it kind of a command?
				   //to use this, you can choose to not clear the struct until the next
				   //key press after it is used. or full. may need another bool for that.
		// VI_': Can't implement.  Requires Application Text awareness.
		case VI_BAR: //Motion		//not used.
		case VI_Z: //Extra
		case VI_X: //Command
		case VI_C: //Op			Command
		case VI_V: //Command
		case VI_B: //Motion
		case VI_N: //Motion
		//VI_M Can't implement marks or middle of screen.
		case VI_CMA: //you separately have to handle the brackets....
		

bool execute_vim_command(void) {
	bool reset_values = false;
	bool result = true;
	if (vim_command.operation != 0) {
		if (vim_command.number == 0) {
			if (vim_command.motion == 0) {
				if (vim_command.timer > VIM_TERM) {
					//there is only a operation, and nothing else has been entered.
					tap_code(vim_command.operation);
					reset_values = true;
					result = false;
				}
		} else {//there is a operation and a motion
			tap_code(vim_command.motion);
			tap_code(vim_command.operation);
			reset_values = true;
			result = false;
		}
	} else { //there is a operation and a number and a motion.
		for (int8_t i = 0; i < vim_command.number; i++) {
			tap_code(vim_command.motion);
			}
		tap_code(vim_command.operation);
		reset_values = true;
		result = false;
	} else {// there is no operation;
		if (vim_command.motion == 0 ) { //no operation and no motion
			reset_values = false;
		 	result = true;
		}

uint8_t keycode_to_digit(uint16_t keycode) {
    switch (keycode) {
        case KC_1: case KC_KP_1: return 1;
        case KC_2: case KC_KP_2: return 2;
        case KC_3: case KC_KP_3: return 3;
        case KC_4: case KC_KP_4: return 4;
        case KC_5: case KC_KP_5: return 5;
        case KC_6: case KC_KP_6: return 6;
        case KC_7: case KC_KP_7: return 7;
        case KC_8: case KC_KP_8: return 8;
        case KC_9: case KC_KP_9: return 9;
        case KC_0: case KC_KP_0: return 0;
        default: return 0xFF; // or -1 to indicate invalid
    }
}
