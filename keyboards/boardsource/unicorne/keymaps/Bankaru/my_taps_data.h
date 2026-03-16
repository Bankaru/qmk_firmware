#include QMK_KEYBOARD_H
#define REPEAT_DELAY 1000
#define REPEAT_INTERVAL 200

extern uint16_t my_taps_hold_timer;
//must be different from my_taps_timer
//if it is reset it won't make it past the void matrix_user
extern bool repeat_started;
typedef uint8_t my_tap_action_mask;
typedef struct {
	//bool fire_on_hold;
	//bool repeatable;
	my_tap_action_mask action_mask;
}	my_tap_t ;

extern uint8_t active_tap_index;
extern uint8_t keycode_to_my_tap(uint16_t);
extern my_tap_t my_taps[];
extern bool do_my_taps_action(uint8_t index, uint8_t taps);
enum uint8_t {
	ONE_TAP_REPEATABLE,
	ONE_TAP_HOLDABLE,
	ONE_TAP_ON_RELEASE,//THIS MEANS YOU DO AN ON-RELEASE. Can be used w/ holdable for "while held" functionality.
	TWO_TAP_REPEATABLE,
	TWO_TAP_HOLDABLE,
	TWO_TAP_ON_RELEASE,//THIS MEANS YOU DO AN ON-RELEASE.
} MY_TAP_ACTION_FLAGS;

