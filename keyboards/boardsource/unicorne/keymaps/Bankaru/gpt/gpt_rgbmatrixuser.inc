#include "rgb_matrix_user.h"

RGB_MATRIX_EFFECT(circuit_complete)


#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS
/* =========================
 * Timing constants (ms)
 * ========================= */
#define STEP_TIME        150
#define COMPLETE_DELAY   150
#define BREATH_SPEED     3

/* =========================
 * Colors
 * ========================= */
#define WHITE_R 255
#define WHITE_G 255
#define WHITE_B 255

//typedef struct {
//    uint8_t r;
//    uint8_t g;
//    uint8_t b;
//} rgb_t;

static const rgb_t row_theme[3] = {
    {255, 120, 0},   // Row 0 - Orange
    {0,   255, 80},  // Row 1 - Green
    {0,   120, 255}  // Row 2 - Blue
};

/* =========================
 * Column definitions
 *
 * Per half (0 = left, 1 = right)
 * These match the Unicorne 3x6 layout
 * ========================= */

// Columns relative to each half
enum {
    COL_PINKY = 0,
    COL_RING  = 1,
    COL_MID   = 2,
    COL_INDEX = 3,
    COL_INNER = 4,
    COL_OUTER = 5, // excluded from circuit
};

/* =========================
 * Circuit description
 * ========================= */

typedef struct {
    uint8_t row;
    bool    right_half;

    uint8_t source_outer;
    uint8_t source_inner;

    uint8_t conn[3];

    uint8_t lit_mask;   // bitmask for connection keys
    uint16_t timer;
    bool complete;
} circuit_t;

/* =========================
 * Circuit table (6 total)
 * ========================= */

static circuit_t circuits[6];
static bool circuits_initialized = false;

/* =========================
 * Helpers
 * ========================= */

//static inline uint8_t matrix_index(uint8_t row, uint8_t col, bool right) {
//    return rgb_matrix_map[row][right ? col + 6 : col];
//} Corrected to the below
static inline uint8_t matrix_index(uint8_t row, uint8_t col, bool right) {
    if (row >= MATRIX_ROWS || col >= MATRIX_COLS) {
        return NO_LED;
    }
    return g_led_config.matrix_co[row][col];
}

//uint8_t led = g_led_config.matrix_co[row][col]; part of this correction, but i don't think I need it.

//static bool key_down(uint8_t index) {
//    return rgb_matrix_get_key_down(index);
//}

bool key_down(uint8_t row, uint8_t col){
    return matrix_is_on=(row, col);
    //return matrix_index]=(row, col);
}

/* =========================
 * Initialize circuits
 * ========================= */

static void init_circuits(void) {
    uint8_t c = 0;

    for (uint8_t half = 0; half < 2; half++) {
        for (uint8_t row = 0; row < 3; row++) {
            circuit_t *ci = &circuits[c++];

            ci->row = row;
            ci->right_half = half;

            ci->source_outer = matrix_index(row, COL_PINKY, half);
            ci->source_inner = matrix_index(row, COL_INNER, half);

            ci->conn[0] = matrix_index(row, COL_RING,  half);
            ci->conn[1] = matrix_index(row, COL_MID,   half);
            ci->conn[2] = matrix_index(row, COL_INDEX, half);

            ci->lit_mask = 0;
            ci->timer = 0;
            ci->complete = false;
        }
    }

    circuits_initialized = true;
}

/* =========================
 * Main effect
 * ========================= */

bool rgb_matrix_effect_circuit_complete(effect_params_t *params) {
    if (!circuits_initialized) {
        init_circuits();
    }

    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    for (uint8_t i = led_min; i < led_max; i++) {
        rgb_matrix_set_color(i, 0, 0, 0);
    }

    uint16_t now = timer_read();

    for (uint8_t i = 0; i < 6; i++) {
        circuit_t *c = &circuits[i];
        rgb_t theme = row_theme[c->row];

        bool active = false;

        if (key_down(c->source_outer) || key_down(c->source_inner)) {
            active = true;
        }

        for (uint8_t k = 0; k < 3; k++) {
            if (key_down(c->conn[k])) {
                active = true;
            }
        }

        if (!active) {
            c->lit_mask = 0;
            c->complete = false;
            c->timer = now;
            continue;
        }

        rgb_matrix_set_color(c->source_outer, WHITE_R, WHITE_G, WHITE_B);
        rgb_matrix_set_color(c->source_inner, WHITE_R, WHITE_G, WHITE_B);

        uint16_t elapsed = timer_elapsed(c->timer);

        if (!c->complete) {
            uint8_t steps = elapsed / STEP_TIME;

            for (uint8_t s = 0; s < steps && s < 3; s++) {
                if (!(c->lit_mask & (1 << s))) {
                    c->lit_mask |= (1 << s);
                }
            }

            for (uint8_t k = 0; k < 3; k++) {
                if (c->lit_mask & (1 << k)) {
                    rgb_matrix_set_color(c->conn[k], WHITE_R, WHITE_G, WHITE_B);
                }
            }

            if (c->lit_mask == 0x07 && elapsed > (3 * STEP_TIME + COMPLETE_DELAY)) {
                c->complete = true;
                c->timer = now;
            }
        } else {
            uint8_t breath = (sin8(now / BREATH_SPEED) >> 1) + 128;

            for (uint8_t k = 0; k < 3; k++) {
                rgb_matrix_set_color(
                    c->conn[k],
                    scale8(theme.r, breath),
                    scale8(theme.g, breath),
                    scale8(theme.b, breath)
                );
            }

            rgb_matrix_set_color(
                c->source_outer,
                scale8(theme.r, breath),
                scale8(theme.g, breath),
                scale8(theme.b, breath)
            );

            rgb_matrix_set_color(
                c->source_inner,
                scale8(theme.r, breath),
                scale8(theme.g, breath),
                scale8(theme.b, breath)
            );
        }
    }

    /* Outer-most keys: light independently in theme color */
    for (uint8_t half = 0; half < 2; half++) {
        for (uint8_t row = 0; row < 3; row++) {
            uint8_t idx = matrix_index(row, COL_OUTER, half);
            if (key_down(idx)) {
                rgb_t t = row_theme[row];
                rgb_matrix_set_color(idx, t.r, t.g, t.b);
            }
        }
    }

    return false;
}
#endif
