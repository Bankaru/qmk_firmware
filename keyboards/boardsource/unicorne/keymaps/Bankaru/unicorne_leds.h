// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// =============================================================================
// Unicorne LED Index Definitions
// =============================================================================

// -----------------------------------------------------------------------------
// Back Light LEDs (Underglow/Background Lighting)
// -----------------------------------------------------------------------------
#define LED_BACK_0 0
#define LED_BACK_1 1
#define LED_BACK_2 2
#define LED_BACK_3 3
#define LED_BACK_4 4
#define LED_BACK_5 5

#define LED_BACK_6 27
#define LED_BACK_7 28
#define LED_BACK_8 29
#define LED_BACK_9 30
#define LED_BACK_10 31
#define LED_BACK_11 32

// -----------------------------------------------------------------------------
// Key Position LEDs - Row 0 (Top Row)
// -----------------------------------------------------------------------------
#define LED_L_0_OUTER 24
#define LED_L_0_PINKY 23
#define LED_L_0_RING 18
#define LED_L_0_MID 17
#define LED_L_0_INDEX 10
#define LED_L_0_INNER 9

#define LED_R_0_INNER 36
#define LED_R_0_INDEX 37
#define LED_R_0_MID 44
#define LED_R_0_RING 45
#define LED_R_0_PINKY 50
#define LED_R_0_OUTER 51

// -----------------------------------------------------------------------------
// Key Position LEDs - Row 1 (Home Row)
// -----------------------------------------------------------------------------
#define LED_L_1_OUTER 25
#define LED_L_1_PINKY 22
#define LED_L_1_RING 19
#define LED_L_1_MID 16
#define LED_L_1_INDEX 11
#define LED_L_1_INNER 8

#define LED_R_1_INNER 35
#define LED_R_1_INDEX 38
#define LED_R_1_MID 43
#define LED_R_1_RING 46
#define LED_R_1_PINKY 49
#define LED_R_1_OUTER 52

// -----------------------------------------------------------------------------
// Key Position LEDs - Row 2
// -----------------------------------------------------------------------------
#define LED_L_2_OUTER 26
#define LED_L_2_PINKY 21
#define LED_L_2_RING 20
#define LED_L_2_MID 15
#define LED_L_2_INDEX 12
#define LED_L_2_INNER 7

#define LED_R_2_INNER 34
#define LED_R_2_INDEX 39
#define LED_R_2_MID 42
#define LED_R_2_RING 47
#define LED_R_2_PINKY 48
#define LED_R_2_OUTER 53

// -----------------------------------------------------------------------------
// Key Position LEDs - Row 3 (Thumb/Bottom Row)
// -----------------------------------------------------------------------------
#define LED_L_3_THUMB_OUTER 14
#define LED_L_3_THUMB_MID 13
#define LED_L_3_THUMB_INNER 6

#define LED_R_3_THUMB_INNER 33
#define LED_R_3_THUMB_MID 40
#define LED_R_3_THUMB_OUTER 41

// -----------------------------------------------------------------------------
// Optional Finger Position Aliases
// -----------------------------------------------------------------------------
// Left Hand Finger Aliases
#define LED_LEFT_PINKY_TOP LED_L_0_PINKY
#define LED_LEFT_PINKY_HOME LED_L_1_PINKY
#define LED_LEFT_PINKY_BOTTOM LED_L_2_PINKY

#define LED_LEFT_RING_TOP LED_L_0_RING
#define LED_LEFT_RING_HOME LED_L_1_RING
#define LED_LEFT_RING_BOTTOM LED_L_2_RING

#define LED_LEFT_MID_TOP LED_L_0_MID
#define LED_LEFT_MID_HOME LED_L_1_MID
#define LED_LEFT_MID_BOTTOM LED_L_2_MID

#define LED_LEFT_INDEX_TOP LED_L_0_INDEX
#define LED_LEFT_INDEX_HOME LED_L_1_INDEX
#define LED_LEFT_INDEX_BOTTOM LED_L_2_INDEX

// Right Hand Finger Aliases
#define LED_RIGHT_PINKY_TOP LED_R_0_PINKY
#define LED_RIGHT_PINKY_HOME LED_R_1_PINKY
#define LED_RIGHT_PINKY_BOTTOM LED_R_2_PINKY

#define LED_RIGHT_RING_TOP LED_R_0_RING
#define LED_RIGHT_RING_HOME LED_R_1_RING
#define LED_RIGHT_RING_BOTTOM LED_R_2_RING

#define LED_RIGHT_MID_TOP LED_R_0_MID
#define LED_RIGHT_MID_HOME LED_R_1_MID
#define LED_RIGHT_MID_BOTTOM LED_R_2_MID

#define LED_RIGHT_INDEX_TOP LED_R_0_INDEX
#define LED_RIGHT_INDEX_HOME LED_R_1_INDEX
#define LED_RIGHT_INDEX_BOTTOM LED_R_2_INDEX
