#include <stdbool.h>
#include "custom_keycodes.h"

//operators need to handle starting the process and finishing the process.
//yank, delete, indent, un-indent, change
bool selection_started;

bool process_vim_operator(uint16_t keycode, keyrecord_t *record) {
	h
}
void yank() {
	//if in visual mode, execute operation. DONE
	//if not in visual mode, start operation.
	selection_started = true;
	//if we pass that to the motion, they can handle when to press shift...
}

