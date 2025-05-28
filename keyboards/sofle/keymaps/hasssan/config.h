// Copyright 2024 Santosh Kumar (@santosh)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Tap-hold configuration for home row mods.
#define TAPPING_TERM 225
#define TAPPING_TERM_PER_KEY
#define CHORDAL_HOLD
#define PERMISSIVE_HOLD
#define QUICK_TAP_TERM_PER_KEY

#define FLOW_TAP_TERM 150

// Caps word timeout after 3 seconds.
#define CAPS_WORD_IDLE_TIMEOUT 3000
// Holding Shift while Caps Word is active inverts the shift state.
#define CAPS_WORD_INVERT_ON_SHIFT

// When idle, turn off Layer Lock after 60 seconds.
#define LAYER_LOCK_IDLE_TIMEOUT 60000
