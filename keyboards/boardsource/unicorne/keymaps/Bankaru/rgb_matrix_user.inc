RGB_MATRIX_EFFECT(circuit_complete_effect)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#include "rgb_matrix_user.h"
#include "lib/lib8tion/trig8.h"
#include "lib/lib8tion/scale8.h"

uint8_t backlight_leds[12] = {
    LED_BACK_0,
    LED_BACK_1,
    LED_BACK_2,
    LED_BACK_3,
    LED_BACK_4,
    LED_BACK_5,
    LED_BACK_6,
    LED_BACK_7,
    LED_BACK_8,
    LED_BACK_9,
    LED_BACK_10,
    LED_BACK_11
};

//static const rgb_t row_theme[3] = {
//    {255, 120, 0},   // Row 0 - Orange
//    {0,   255, 80},  // Row 1 - Green
//    {0,   120, 255}  // Row 2 - Blue
    //RGB_ORANGE,
    //RGB_GREEN,
    //RGB_BLUE,
//};

thumb_key_mask_t thumb_key_mask;
circuit circuits[6];
rgb_sync_t rgb_sync;

static bool circuits_are_initialized = false;


void housekeeping_task_user(void) {
    if (is_keyboard_master()) {
        memcpy(rgb_sync.circuits, circuits, sizeof(circuits));
        rgb_sync.thumb_key_mask = thumb_key_mask;
    } else {
        memcpy(circuits, rgb_sync.circuits, sizeof(circuits));
        thumb_key_mask = rgb_sync.thumb_key_mask;
    }
}

static void initialize_circuits(void) {
    thumb_key_mask = 0;
    memset(circuits, 0, sizeof(circuits));

    circuit *c_lt = &circuits[LEFT_TOP_CIR];
    c_lt->active_leds[COL_INDEX_OUTER] = LED_L_0_OUTER;
    c_lt->active_leds[COL_INDEX_PINKY] = LED_L_0_PINKY;
    c_lt->active_leds[COL_INDEX_RING] = LED_L_0_RING;
    c_lt->active_leds[COL_INDEX_MID] = LED_L_0_MID;
    c_lt->active_leds[COL_INDEX_INDEX] = LED_L_0_INDEX;
    c_lt->active_leds[COL_INDEX_INNER] = LED_L_0_INNER;

    c_lt->color.r = 0xFF;
    c_lt->color.g = 0x80;
    c_lt->color.b = 0x00;

    c_lt->start_time = 0;
    c_lt->phase = 0;

    circuit *c_lm = &circuits[LEFT_MID_CIR];
    c_lm->active_leds[COL_INDEX_OUTER] = LED_L_1_OUTER;
    c_lm->active_leds[COL_INDEX_PINKY] = LED_L_1_PINKY;
    c_lm->active_leds[COL_INDEX_RING] = LED_L_1_RING;
    c_lm->active_leds[COL_INDEX_MID] = LED_L_1_MID;
    c_lm->active_leds[COL_INDEX_INDEX] = LED_L_1_INDEX;
    c_lm->active_leds[COL_INDEX_INNER] = LED_L_1_INNER;

    c_lm->color.r = 0x00;
    c_lm->color.g = 0xFF;
    c_lm->color.b = 0x00;

    c_lm->start_time = 0;
    c_lm->phase = 0;

    circuit *c_lb = &circuits[LEFT_BTM_CIR];
    c_lb->active_leds[COL_INDEX_OUTER] = LED_L_2_OUTER;
    c_lb->active_leds[COL_INDEX_PINKY] = LED_L_2_PINKY;
    c_lb->active_leds[COL_INDEX_RING] = LED_L_2_RING;
    c_lb->active_leds[COL_INDEX_MID] = LED_L_2_MID;
    c_lb->active_leds[COL_INDEX_INDEX] = LED_L_2_INDEX;
    c_lb->active_leds[COL_INDEX_INNER] = LED_L_2_INNER;

    c_lb->color.r = 0x00;
    c_lb->color.g = 0x00;
    c_lb->color.b = 0xFF;

    c_lb->start_time = 0;
    c_lb->phase = 0;

     circuit *c_rt = &circuits[RIGHT_TOP_CIR];
    c_rt->active_leds[COL_INDEX_OUTER] = LED_R_0_OUTER;
    c_rt->active_leds[COL_INDEX_PINKY] = LED_R_0_PINKY;
    c_rt->active_leds[COL_INDEX_RING] = LED_R_0_RING;
    c_rt->active_leds[COL_INDEX_MID] = LED_R_0_MID;
    c_rt->active_leds[COL_INDEX_INDEX] = LED_R_0_INDEX;
    c_rt->active_leds[COL_INDEX_INNER] = LED_R_0_INNER;

    c_rt->color.r = 0xFF;
    c_rt->color.g = 0x80;
    c_rt->color.b = 0x00;

    c_rt->start_time = 0;
    c_rt->phase = 0;

    circuit *c_rm = &circuits[RIGHT_MID_CIR];
    c_rm->active_leds[COL_INDEX_OUTER] = LED_R_1_OUTER;
    c_rm->active_leds[COL_INDEX_PINKY] = LED_R_1_PINKY;
    c_rm->active_leds[COL_INDEX_RING] = LED_R_1_RING;
    c_rm->active_leds[COL_INDEX_MID] = LED_R_1_MID;
    c_rm->active_leds[COL_INDEX_INDEX] = LED_R_1_INDEX;
    c_rm->active_leds[COL_INDEX_INNER] = LED_R_1_INNER;

    c_rm->color.r = 0x00;
    c_rm->color.g = 0xFF;
    c_rm->color.b = 0x00;

    c_rm->start_time = 0;
    c_rm->phase = 0;

    circuit *c_rb = &circuits[RIGHT_BTM_CIR];
    c_rb->active_leds[COL_INDEX_OUTER] = LED_R_2_OUTER;
    c_rb->active_leds[COL_INDEX_PINKY] = LED_R_2_PINKY;
    c_rb->active_leds[COL_INDEX_RING] = LED_R_2_RING;
    c_rb->active_leds[COL_INDEX_MID] = LED_R_2_MID;
    c_rb->active_leds[COL_INDEX_INDEX] = LED_R_2_INDEX;
    c_rb->active_leds[COL_INDEX_INNER] = LED_R_2_INNER;

    c_rb->color.r = 0x00;
    c_rb->color.g = 0x00;
    c_rb->color.b = 0xFF;

    c_rb->start_time = 0;
    c_rb->phase = 0;

    circuits_are_initialized = true;
}

static void set_circuit_phase_off(circuit *cir){
    rgb_matrix_set_color(cir->active_leds[COL_INDEX_RING], RGB_OFF);
    rgb_matrix_set_color(cir->active_leds[COL_INDEX_MID], RGB_OFF);
    rgb_matrix_set_color(cir->active_leds[COL_INDEX_INDEX], RGB_OFF);
    if (cir->active_led_mask & COL_MASK_OUTER) {
        rgb_matrix_set_color(cir->active_leds[COL_INDEX_OUTER],
                cir->color.r, cir->color.g, cir->color.b);
        } else {
        rgb_matrix_set_color(cir->active_leds[COL_INDEX_OUTER], RGB_OFF);
        }
    if (cir->active_led_mask & COL_MASK_PINKY) {
        rgb_matrix_set_color(cir->active_leds[COL_INDEX_PINKY],
                cir->color.r, cir->color.g, cir->color.b);
        } else {
        rgb_matrix_set_color(cir->active_leds[COL_INDEX_PINKY], RGB_OFF);
        }
    if (cir->active_led_mask & COL_MASK_INNER) {
        rgb_matrix_set_color(cir->active_leds[COL_INDEX_INNER],
                cir->color.r, cir->color.g, cir->color.b);
        } else {
        rgb_matrix_set_color(cir->active_leds[COL_INDEX_INNER], RGB_OFF);
        }
}

static void set_circuit_phase_one(circuit *cir){
    rgb_matrix_set_color(cir->active_leds[COL_INDEX_RING], RGB_OFF);
    rgb_matrix_set_color(cir->active_leds[COL_INDEX_MID], RGB_OFF);
    rgb_matrix_set_color(cir->active_leds[COL_INDEX_INDEX], RGB_OFF);

    rgb_matrix_set_color(cir->active_leds[COL_INDEX_PINKY], RGB_WHITE);
                //cir->color.r, cir->color.g, cir->color.b);
    rgb_matrix_set_color(cir->active_leds[COL_INDEX_INNER], RGB_WHITE);
                //cir->color.r, cir->color.g, cir->color.b);

    if (cir->active_led_mask & COL_MASK_OUTER) {
        rgb_matrix_set_color(cir->active_leds[COL_INDEX_OUTER],
            cir->color.r, cir->color.g, cir->color.b);
        } else {
        rgb_matrix_set_color(cir->active_leds[COL_INDEX_OUTER], RGB_OFF);
    }
}

static void set_circuit_phase_two(circuit *cir){

    rgb_matrix_set_color(cir->active_leds[COL_INDEX_RING], RGB_WHITE);
    rgb_matrix_set_color(cir->active_leds[COL_INDEX_MID], RGB_OFF);
    rgb_matrix_set_color(cir->active_leds[COL_INDEX_INDEX], RGB_WHITE);

    rgb_matrix_set_color(cir->active_leds[COL_INDEX_PINKY], RGB_WHITE);
                //cir->color.r, cir->color.g, cir->color.b);
    rgb_matrix_set_color(cir->active_leds[COL_INDEX_INNER], RGB_WHITE);
                //cir->color.r, cir->color.g, cir->color.b);

    if (cir->active_led_mask & COL_MASK_OUTER) {
        rgb_matrix_set_color(cir->active_leds[COL_INDEX_OUTER],
                cir->color.r, cir->color.g, cir->color.b);
       } else {
       rgb_matrix_set_color(cir->active_leds[COL_INDEX_OUTER], RGB_OFF);
   }
}

static void set_circuit_phase_three(circuit *cir){
    rgb_matrix_set_color(cir->active_leds[COL_INDEX_RING], RGB_WHITE);
    rgb_matrix_set_color(cir->active_leds[COL_INDEX_MID], RGB_WHITE);
    rgb_matrix_set_color(cir->active_leds[COL_INDEX_INDEX], RGB_WHITE);

    rgb_matrix_set_color(cir->active_leds[COL_INDEX_PINKY], RGB_WHITE);
                //cir->color.r, cir->color.g, cir->color.b);
    rgb_matrix_set_color(cir->active_leds[COL_INDEX_INNER], RGB_WHITE);
               // cir->color.r, cir->color.g, cir->color.b);


    if (cir->active_led_mask & COL_MASK_OUTER) {
        rgb_matrix_set_color(cir->active_leds[COL_INDEX_OUTER],
                cir->color.r, cir->color.g, cir->color.b);
       } else {
        rgb_matrix_set_color(cir->active_leds[COL_INDEX_OUTER], RGB_OFF);
    }
}

static void set_circuit_phase_complete(circuit *cir){
    //breathe it.
    uint8_t breathe = (sin8(timer_read() / BREATHE_SPEED) >> 1) + 128;
    uint8_t r = scale8(cir->color.r, breathe);
    uint8_t g = scale8(cir->color.g, breathe);
    uint8_t b = scale8(cir->color.b, breathe);

    rgb_matrix_set_color(cir->active_leds[COL_INDEX_RING], r, g, b);
    rgb_matrix_set_color(cir->active_leds[COL_INDEX_MID], r, g, b);
    rgb_matrix_set_color(cir->active_leds[COL_INDEX_INDEX], r, g, b);
    rgb_matrix_set_color(cir->active_leds[COL_INDEX_PINKY], r, g, b);
    rgb_matrix_set_color(cir->active_leds[COL_INDEX_INNER], r, g, b);

    if (cir->active_led_mask & COL_MASK_OUTER) {
        rgb_matrix_set_color(cir->active_leds[COL_INDEX_OUTER],
                cir->color.r, cir->color.g, cir->color.b);
       } else {
        rgb_matrix_set_color(cir->active_leds[COL_INDEX_OUTER], RGB_OFF);
    }
}

void set_corne_backlight_leds(void){
    for (uint8_t i = 0; i < ARRAY_SIZE(backlight_leds); i++) {
        rgb_matrix_set_color(backlight_leds[i], RGB_OFF);
    }
}

bool circuit_complete_effect(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    if (!circuits_are_initialized) {
        initialize_circuits();
    }

    for (uint8_t c = LEFT_TOP_CIR; c < ARRAY_SIZE(circuits); c++){
        circuit *cir = &circuits[c];

        //if the circuit is off, start if there's activity or keep it off
        if (cir->phase == CIRCUIT_PHASE_OFF) {
            if ((cir->active_led_mask & CONN_MASK) != 0){
                cir->start_time = timer_read();
                cir->phase = CIRCUIT_PHASE_P1;
                set_circuit_phase_one(cir);
            } else {
                set_circuit_phase_off(cir);
            }
            continue;
        }

        //if circuit is active, and nothing is pressed, turn it off.
        if ((cir->active_led_mask & CONN_MASK) == 0) {
            cir->phase = CIRCUIT_PHASE_OFF;
            cir->start_time = 0; //unnecessary: this won't be read until phase is turned on again, at which point it will be set.
            set_circuit_phase_off(cir);
            continue;
        }
        //if circuit is active and is already complete, just continue;
        if (cir->phase == CIRCUIT_PHASE_COMPLETE) {
            set_circuit_phase_complete(cir);
            continue;
        }

        //otherwise, figure out what phase we should be in.
        uint16_t new_time = timer_elapsed(cir->start_time);

        if (new_time > ((PHASE_TIME * 2) + CIRCUIT_FINISH_TIME)) {
            cir->phase = CIRCUIT_PHASE_COMPLETE;
            //set the start time for the breathe function
            //that time probably needs to be passed as an argument to the function.
            set_circuit_phase_complete(cir);
            continue;
        }
        if (new_time > PHASE_TIME * 2) {
            cir->phase = CIRCUIT_PHASE_P3;
            set_circuit_phase_three(cir);
            continue;
        }
        if (new_time > PHASE_TIME) {
            cir->phase = CIRCUIT_PHASE_P2;
            set_circuit_phase_two(cir);
            continue;
        }

        cir->phase = CIRCUIT_PHASE_P1;
        set_circuit_phase_one(cir);
     }

    //Illuminate Thumb Keys
    if (thumb_key_mask & THUMB_MASK_L_OUTER){
        rgb_matrix_set_color(LED_L_3_THUMB_OUTER, RGB_GOLD);
    } else {
        rgb_matrix_set_color(LED_L_3_THUMB_OUTER, RGB_OFF);
    }
    if (thumb_key_mask & THUMB_MASK_L_MID){
        rgb_matrix_set_color(LED_L_3_THUMB_MID, RGB_GOLD);
    } else {
        rgb_matrix_set_color(LED_L_3_THUMB_MID, RGB_OFF);
    }
    if (thumb_key_mask & THUMB_MASK_L_INNER){
        rgb_matrix_set_color(LED_L_3_THUMB_INNER, RGB_GOLD);
    } else {
        rgb_matrix_set_color(LED_L_3_THUMB_INNER, RGB_OFF);
    }
    if (thumb_key_mask & THUMB_MASK_R_OUTER){
        rgb_matrix_set_color(LED_R_3_THUMB_OUTER, RGB_GOLD);
    } else {
        rgb_matrix_set_color(LED_R_3_THUMB_OUTER, RGB_OFF);
    }
    if (thumb_key_mask & THUMB_MASK_R_MID){
        rgb_matrix_set_color(LED_R_3_THUMB_MID, RGB_GOLD);
    } else {
        rgb_matrix_set_color(LED_R_3_THUMB_MID, RGB_OFF);
    }
    if (thumb_key_mask & THUMB_MASK_R_INNER){
        rgb_matrix_set_color(LED_R_3_THUMB_INNER, RGB_GOLD);
    } else {
        rgb_matrix_set_color(LED_R_3_THUMB_INNER, RGB_OFF);
    }

    //set backlight leds (no lighting designed for them now)
    set_corne_backlight_leds();

    return false;
}

#endif


