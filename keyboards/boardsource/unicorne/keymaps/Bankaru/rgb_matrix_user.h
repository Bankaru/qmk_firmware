#pragma once

#include "quantum.h"
#include "unicorne_leds.h"
#include "color.h"
#define PHASE_TIME 96
#define CIRCUIT_FINISH_TIME 48
#define BREATHE_SPEED 4
#define CIRCUIT_SIZE 6
#define CIRCUIT_COUNT 6
#define THUMB_MASK_L_OUTER (1 << 0)
#define THUMB_MASK_L_MID (1 << 1)
#define THUMB_MASK_L_INNER (1 << 2)
#define THUMB_MASK_R_OUTER (1 << 3)
#define THUMB_MASK_R_MID (1 << 4)
#define THUMB_MASK_R_INNER (1 << 5)
#define CONN_MASK ((1 << 2) | (1 << 3) | (1 << 4))

typedef uint8_t col_mask_t;
extern col_mask_t col_mask;
typedef uint8_t thumb_key_mask_t;
extern thumb_key_mask_t thumb_key_mask;

typedef struct {
    uint16_t start_time;
    uint8_t  phase;
    // used by input to write which keys are active.
    // used by rgb to read which keys are active;
    uint8_t    active_leds[CIRCUIT_SIZE];
    col_mask_t active_led_mask;
    rgb_t      color;

} circuit;

extern circuit circuits[6];

typedef struct {
	circuit circuits[6];
	thumb_key_mask_t thumb_key_mask;
} rgb_sync_t;

extern rgb_sync_t rgb_sync;

typedef enum {
    //NONE,
    LEFT_TOP_CIR,
    LEFT_MID_CIR,
    LEFT_BTM_CIR,
    RIGHT_TOP_CIR,
    RIGHT_MID_CIR,
    RIGHT_BTM_CIR,
} circuit_location;

typedef enum {
    COL_MASK_OUTER = 1 << 0,
    COL_MASK_PINKY = 1 << 1,
    COL_MASK_RING  = 1 << 2,
    COL_MASK_MID   = 1 << 3,
    COL_MASK_INDEX = 1 << 4,
    COL_MASK_INNER = 1 << 5,
}column_mask_t;

typedef enum {
    COL_INDEX_OUTER,
    COL_INDEX_PINKY,
    COL_INDEX_RING,
    COL_INDEX_MID,
    COL_INDEX_INDEX,
    COL_INDEX_INNER,
} col_index_t;

typedef enum { 
	CIRCUIT_PHASE_OFF, 
	CIRCUIT_PHASE_P1, 
	CIRCUIT_PHASE_P2, 
	CIRCUIT_PHASE_P3, 
	CIRCUIT_PHASE_COMPLETE
} circuit_phase;

bool circuit_complete_effect(effect_params_t *params);
extern void send_circuit_led(uint8_t led, bool on);
// const uint8_t COL_OUTER = 1;
// const uint8_t COL_PINKY = 2;
// const uint8_t COL_RING = 4;
// const uint8_t COL_MID = 8;
// const uint8_t COL_INDEX = 16;
// const uint8_t COL_INNER = 32;

// From the bitset, we need to get which circuit the ones belong to,
// and which
