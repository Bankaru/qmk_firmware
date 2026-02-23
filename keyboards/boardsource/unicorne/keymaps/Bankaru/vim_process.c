#include <stdint.h>
#include "custom_keycodes.h"
#include "vim_motions.h"
#include "vim_commands.h"


//make the struct in here, not in vim_commands...
bool process_vim(uint16_t keycode, keyrecord_t *record) {
	//first determine if it belongs here...
	//	is it regular text for input mode or a non-vim button?
	//	if "input_mode", a command, we make the struct our command and execute it.
	//
	//	or is it for the VIM struct?
	//
	//
	//determine what type of keycode it is... operator, motion, number, command, extra 
	//
	//next determine if struct is ready to go. //hopefully that can be done without the matrix scan
	//
	//if so, execute
	//if not, await further input.
	//
}
