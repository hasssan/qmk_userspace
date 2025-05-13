// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

// Left-hand home row mods
#define H_S LGUI_T(KC_S)
#define H_N LALT_T(KC_N)
#define H_T LSFT_T(KC_T)
#define H_H LCTL_T(KC_H)

// Right-hand home row mods
#define H_A RCTL_T(KC_A)
#define H_E RSFT_T(KC_E)
#define H_I LALT_T(KC_I)
#define H_C RGUI_T(KC_C)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Hands Down Promethium (Inverted) BASE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |  DEL |  C-V |  C-A |  C-C |A-TAB |                    | HOME | PGUP | PGDN |  END |      | PLAY |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   V  |   W  |   G  |   M  |   J  |                    |   ;  |   .  |   '  |   =  |   /  |  Z   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |   S  |   N  |   T  |   H  |   K  |-------.    ,-------|   ,  |   A  |   E  |   I  |   C  |  Q   |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * |   _  |   F  |   P  |   D  |   L  |   X  |-------|    |-------|   -  |   U  |   O  |   Y  |   B  |BKSPC |
 * `-----------------------------------------/       /    \       \-----------------------------------------'
 *            | LEFT |RIGHT | BKSPC |  R  | / ESC   /      \  SYM  \  | SPC  | ENT  |  UP  | DOWN |
 *            |      |      |      |      |/       /        \       \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

[0] = LAYOUT(
  KC_GRV,   KC_DEL, C(KC_V), C(KC_A), C(KC_C), A(KC_TAB),                     KC_HOME, KC_PGUP, KC_PGDN, KC_END, XXXXXXX,  KC_MPLY,
  KC_TAB,   KC_V,   KC_W,    KC_G,    KC_M,    KC_J,                          KC_SCLN, KC_DOT,  KC_QUOT, KC_EQL, KC_SLSH,  KC_Z,
/*  KC_ESC,   H_S,    H_N,     H_T,     H_H,     KC_K,                          KC_COMM, H_A,     H_E,     H_I,    H_C,      KC_Q, */
  KC_ESC,   KC_S,   KC_N,    KC_T,    KC_H,    KC_K,                          KC_COMM, KC_A,    KC_E,    KC_I,   KC_C,     KC_Q,
  KC_UNDS,  KC_F,   KC_P,    KC_D,    KC_L,    KC_X, KC_MUTE,        XXXXXXX, KC_MINS, KC_U,    KC_O,    KC_Y,   KC_B,     KC_BSPC,
                 KC_LEFT,    KC_RGHT, KC_BSPC, KC_R, KC_ESC,         TO(1),   KC_SPC,  KC_ENT,  KC_UP,   KC_DOWN
),
/* SYM
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   `  |   <  |   >  |   -  |   |  |                    |   ^  |   {  |   }  |   $  |   %  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   !  |   *  |   /  |   =  |   &  |-------.    ,-------|   #  |   (  |   )  |   ;  |   "  |      |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * |      |  ~   |  +   |  [   |   ]  |   %  |-------|    |-------|   @  |   :  |   ,  |   .  |   '  |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LEFT |RIGHT |   R  |  SPC | / BASE  /       \ NUM  \  |BKSPC | ENT  |  UP  | DOWN |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[1] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                         _______, _______, _______, _______, _______, _______,
  _______, KC_GRV,  KC_LT,   KC_GT,   KC_MINS, KC_PIPE,                         KC_CIRC, KC_LCBR, KC_RCBR, KC_DLR,  KC_PERC, _______,
  _______, KC_EXLM, KC_ASTR, KC_SLSH, KC_EQL,  KC_AMPR,                         KC_HASH, KC_LPRN, KC_RPRN, KC_SCLN, KC_DQUO, _______,
  _______, KC_TILD, KC_PLUS, KC_LBRC, KC_RBRC, KC_PERC, _______,       _______, KC_AT,   KC_COLN, KC_COMM, KC_DOT,  KC_QUOT, _______,
                    _______, _______, _______, _______, TO(0),         TO(2),   _______, _______, _______, _______
),
/* NUM
 * ,----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  /   |  9   |  8   |  7   |  *   |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  -   |  3   |  2   |  1   |  +   |-------.    ,-------|      | CTRL |   E  | ALT  | GUI  |      |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * |      |  x   |  6   |  5   |  4   |  %   |-------|    |-------|      |      |   ,  |  .   | FUN  |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LEFT |RIGHT |   R  |  SPC | / BASE  /       \ SYM  \  |BKSPC | ENT  |  UP  | DOWN |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[2] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                         _______, _______, _______, _______, _______, _______,
  _______, KC_SLSH, KC_9,    KC_8,    KC_7,    KC_ASTR,                         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  _______, KC_MINS, KC_3,    KC_2,    KC_1,    KC_PLUS,                         XXXXXXX, KC_LCTL, H_E,     KC_LALT, KC_LGUI, _______,
  _______, KC_X,    KC_6,    KC_5,    KC_4,    KC_PERC, _______,       _______, XXXXXXX, XXXXXXX, KC_COMM, KC_DOT,  TO(3),   _______,
                    _______, _______, _______, _______, TO(0),         TO(1),   _______, _______, _______, _______
),
/* FUN
 * ,----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  F12 |  F9  |  F8  |  F7  |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  F10 |  F3  |  F2  |  F1  |      |-------.    ,-------|      | CTRL |SHIFT | ALT  | GUI  |      |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * |      |  F11 |  F6  |  F5  |  F4  |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LEFT |RIGHT |   R  |  SPC | / BASE  /       \ SYM  \  |BKSPC | ENT  |  UP  | DOWN |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[3] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                         _______, _______, _______, _______, _______, _______,
  _______, KC_F12,  KC_F9,   KC_F8,   KC_F7,   XXXXXXX,                         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  _______, KC_F10,  KC_F3,   KC_F2,   KC_F1,   XXXXXXX,                         XXXXXXX, KC_LCTL, H_E,     KC_LALT, KC_LGUI, _______,
  _______, KC_F11,  KC_F6,   KC_F5,   KC_F4,   XXXXXXX, _______,       _______, XXXXXXX, XXXXXXX, KC_COMM, KC_DOT,  XXXXXXX, _______,
                    _______, _______, _______, _______, TO(0),         TO(1),   _______, _______, _______, _______
),
};

// bool process_record_user(uint16_t keycode, keyrecord_t *record) {}

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(MS_WHLU, MS_WHLD) },
    [1] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(MS_WHLU, MS_WHLD) },
    [2] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(MS_WHLU, MS_WHLD) },
    [3] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(MS_WHLU, MS_WHLD) },
};
#endif

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0
    };
    oled_write_P(qmk_logo, false);
}

void my_print_status_narrow(void) {
    oled_write_P(PSTR("\n\n"), false);
    oled_write_ln_P(PSTR("HDPi"), false);

    oled_write_P(PSTR("\n\n"), false);
    oled_write_ln_P(PSTR("LAYER"), false);
    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("Base\n"), false);
            break;
        case 1:
            oled_write_P(PSTR("Sym\n"), false);
            break;
        case 2:
            oled_write_P(PSTR("Num\n"), false);
            break;
        case 3:
            oled_write_P(PSTR("Fun\n"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }

    oled_write_P(PSTR("\n\n"), false);
    oled_write_ln_P(PSTR("HSSN"), false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        my_print_status_narrow();
    } else {
        render_logo();
    }
    return false;
}

#endif
