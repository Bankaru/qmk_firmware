#define REPEAT_DELAY 1000
#define REPEAT_INTERVAL 200

extern uint16_t my_taps_hold_timer;
//must be different from my_taps_timer
//if it is reset it won't make it past the void matrix_user
extern bool repeat_started;
typedef struct {
	bool fire_on_hold;
	bool repeatable;
}	my_tap_t ;

extern uint8_t active_tap_index;
extern uint8_t keycode_to_my_tap(uint16_t);
extern my_tap_t my_taps[];
extern bool do_my_taps_action(uint8_t index);
