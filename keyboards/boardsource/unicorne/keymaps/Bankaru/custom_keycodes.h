#include "quantum_keycodes.h"
enum custom_keycodes {
    MY_SYST = SAFE_RANGE,
    MY_BASE,
    MY_COPY,
    MY_CUT,
    MY_PASTE,
#ifdef MY_TAPS
	TP_SYM,
#endif
#ifdef VIM_MOTIONS
	//I'll just use my symbols to make it less complicated for now...jikl instead of hjkl
	//Maybe you should make functions you can't do like "till" be useful F functions -rename symbol, debug step...
	VI_W,
	//VI_E, //This won't be usable since sometimes ctrl + right has a space after the word and sometimes it doesn't.
	VI_R,
	//VI_T, Use for something else
	VI_Y,
	VI_U,
	VI_O,
	VI_P,
	VI_A,
	VI_S,
	VI_D,
	//VI_F, how to make find?
	VI_G,
	VI_H, //I use this as insert.
	//VI_;, how to make repeat?  or go next?  Can't really use commands here...  Unless you  make a helper program.  DON'T DO IT.
	VI_Z, //I don't even know what this is or how to use it. ZZ saves and quits, ZQ quits without saving.
	VI_X,
	VI_C,
	VI_V,
	VI_B,
	//VI_N, how to make next?
	//VI_M, I don't know what this does or if i can do it.  I think it just centers the screen?
	//VI_,  Can't really reverse t or f..
	//VI_.  Can't really repeat cmd...
	//VI_/  Can't really do search other than ctrl f and see what happens...  might not be a bad idea i guess.
#endif
};
