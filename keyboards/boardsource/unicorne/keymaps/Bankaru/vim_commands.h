#include <stdint.h>
#include <stdbool.h>
#define VIM_TERM (TAPPING_TERM * 2)

typedef struct{
	uint16_t timer;
	uint16_t operation; //yank, select, change (same as select almost...),
	uint16_t motion; //word, back, directional keys
	uint8_t number; //for now, 9 is the limit.
} vim_command_t;



extern vim_command_t vim_command;
extern void init_vim_commands(void);
extern uint8_t keycode_to_digit(uint16_t keycode);
extern bool execute_vim_command(void);
extern bool command_mode_active;


