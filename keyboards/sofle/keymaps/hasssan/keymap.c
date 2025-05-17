// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

#include "layout.h"

enum layers {
    BASE,  // 0
    SYM,   // 1
    NAV,   // 2
    NUM,   // 3
    WIN,   // 4
    FUN,   // 5
    EXT,   // 6
    NOHRM, // 7
};

// Left-hand home row mods
#define HRM_S LALT_T(KC_S)
#define HRM_N LT(SYM, KC_N)
#define HRM_T LSFT_T(KC_T)
#define HRM_H LT(NAV, KC_H)

#define HRM_F LGUI_T(KC_F)
#define HRM_L LCTL_T(KC_L)

#define EXT_UND LT(EXT, KC_UNDS)

// Right-hand home row mods
#define HRM_COM LT(FUN, KC_COMM)
#define HRM_A LT(NUM, KC_A)
#define HRM_E RSFT_T(KC_E)
#define HRM_I LT(SYM, KC_I)
#define HRM_C LALT_T(KC_C)

#define HRM_U LCTL_T(KC_C)
#define HRM_Y LT(WIN, KC_Y)
#define HRM_B RGUI_T(KC_B)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[BASE] = LAYOUT_LR( // Hands Down Promethium (Inverted)
    /* Left side */
    KC_GRV , KC_DEL , C(KC_V), C(KC_A), C(KC_C), MS_BTN1,
    KC_TAB , KC_V   , KC_W   , KC_G   , KC_M   , KC_J   ,
    KC_BSPC, HRM_S  , HRM_N  , HRM_T  , HRM_H  , KC_K   ,
    EXT_UND, HRM_F  , KC_P   , KC_D   , HRM_L  , KC_X   , KC_MUTE,
                      KC_LEFT, KC_RGHT, KC_BSPC, KC_R   , KC_ESC,

                /* Right side */
                         KC_HOME, KC_PGUP, KC_PGDN, KC_END, KC_MNXT, KC_MPLY,
                         KC_SCLN, KC_DOT , KC_QUOT, KC_EQL, KC_SLSH, KC_Z   ,
                         HRM_COM, HRM_A  , HRM_E  , HRM_I , HRM_C  , KC_Q   ,
                XXXXXXX, KC_MINS, HRM_U  , KC_O   , HRM_Y , HRM_B  , KC_ENT ,
                QK_REP , KC_SPC , KC_TAB , KC_UP  , KC_DOWN
),
[SYM] = LAYOUT_LR(
    /* Left side */
    _______, _______, _______, _______, _______, _______,
    _______, KC_GRV,  KC_LT,   KC_GT,   KC_MINS, KC_PIPE,
    _______, KC_EXLM, KC_ASTR, KC_SLSH, KC_EQL,  KC_AMPR,
    _______, KC_TILD, KC_PLUS, KC_LBRC, KC_RBRC, KC_PERC, _______,
                      _______, _______, _______, _______, TO(0),

                /* Right side */
                         _______, _______, _______, _______, _______, _______,
                         KC_CIRC, KC_LCBR, KC_RCBR, KC_DLR,  KC_PERC, _______,
                         KC_HASH, KC_LPRN, KC_RPRN, KC_SCLN, KC_DQUO, _______,
                _______, KC_AT,   KC_COLN, KC_COMM, KC_DOT,  TO(3),   _______,
                TO(1),   _______, _______, _______, _______
),
[NUM] = LAYOUT_LR(
    /* Left side */
    _______, _______, _______, _______, _______, _______,
    _______, KC_SLSH, KC_9,    KC_8,    KC_7,    KC_ASTR,
    _______, KC_MINS, KC_3,    KC_2,    KC_1,    KC_PLUS,
    _______, KC_X,    KC_6,    KC_5,    KC_4,    KC_PERC, _______,
                      _______, _______, _______, _______, TO(0),

                /* Right side */
                         _______, _______, _______, _______, _______, _______,
                         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
                         XXXXXXX, KC_LCTL, KC_E,    KC_LALT, KC_LGUI, _______,
                _______, XXXXXXX, XXXXXXX, KC_COMM, KC_DOT,  TO(3),   _______,
                TO(1),   _______, _______, _______, _______
),
[FUN] = LAYOUT_LR(
    /* Left side */
    _______, _______, _______, _______, _______, _______,
    _______, KC_F12,  KC_F9,   KC_F8,   KC_F7,   XXXXXXX,
    _______, KC_F10,  KC_F3,   KC_F2,   KC_F1,   XXXXXXX,
    _______, KC_F11,  KC_F6,   KC_F5,   KC_F4,   XXXXXXX, _______,
                      _______, _______, _______, _______, TO(0),

                /* Right side */
                         _______, _______, _______, _______, _______, _______,
                         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
                         XXXXXXX, KC_LCTL, KC_E,    KC_LALT, KC_LGUI, _______,
                _______, XXXXXXX, XXXXXXX, KC_COMM, KC_DOT,  XXXXXXX, _______,
                TO(1),   _______, _______, _______, _______
),
};

// bool process_record_user(uint16_t keycode, keyrecord_t *record) {}

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(MS_WHLU, MS_WHLD) },
    [SYM] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(MS_WHLU, MS_WHLD) },
    [NUM] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(MS_WHLU, MS_WHLD) },
    [FUN] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(MS_WHLU, MS_WHLD) },
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
