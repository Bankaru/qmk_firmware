#ifdef VIM_MOTIONS
#include <stdint.h>
#include "process_tap_dance.h"
typedef uint8_t command_mask_t;
extern command_mask_t active_vim_commands;

typedef uint8_t key_release_mask_t;
extern key_release_mask_t key_release_mask;

//the bool returned determines if the operator immediately executes
//or if they...wait they all immediately execute.

enum {
	RL_VI_Y = 1 << 0,
	RL_VI_P = 1 << 1,
} KEY_RELEASE_TRACKER;

enum {
	VI_TAP_DANCE_Y = 1 << 0,
} VI_TAP_DANCE;

extern bool w_vim_key(bool down);
extern bool r_vim_key(bool down);
extern bool u_vim_key(bool down);
extern bool o_vim_key(bool down);
extern bool p_vim_key(bool down);


extern void tap_dance_VI_Y(tap_dance_state_t *state, void *user_data);

extern void init_vim_motions(void);
extern void yank_line(void);
extern void yank_to_eol(void);
enum {
	SEL_IS_ACTIVE,
	INS_IS_ACTIVE,
};
#endif
