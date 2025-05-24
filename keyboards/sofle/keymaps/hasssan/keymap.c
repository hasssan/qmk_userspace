// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

#include "layout.h"

enum layers {
    BASE, // 0
    SYM,  // 1
    NAV,  // 2
    NUM,  // 3
    WIN,  // 4
    FUN,  // 5
    EXT,  // 6
    NHRM, // 7
};

enum custom_keycodes {
    KC_NXWD = SAFE_RANGE, // Next Window ALT+TAB (Windows) or CMD+TAB (macOS)
    KC_NXSW,              // Next Window same app for macOS CMD+`
    KC_NXTB,              // Next Tab CTRL+TAB, Windows and macOS behave the same
};

#define NX_TIMER 700 // Timer for NX keycodes

bool     is_nxwd_active = false;
bool     is_nxsw_active = false;
bool     is_nxtb_active = false;
uint16_t nxwd_timer     = 0;
uint16_t nxsw_timer     = 0;
uint16_t nxtb_timer     = 0;

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

#define HRM_U LCTL_T(KC_U)
#define HRM_Y LT(WIN, KC_Y)
#define HRM_B RGUI_T(KC_B)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[BASE] = LAYOUT_LR( // Hands Down Promethium (Inverted)
    /* Left side */
    KC_GRV , KC_DEL , C(KC_V), C(KC_A), C(KC_C), MS_BTN1,
    KC_TAB , KC_V   , KC_W   , KC_G   , KC_M   , KC_J   ,
    KC_ESC , HRM_S  , HRM_N  , HRM_T  , HRM_H  , KC_K   ,
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
    _______, KC_GRV , KC_LT  , KC_GT  , KC_MINS, KC_PIPE,
    _______, KC_EXLM, KC_ASTR, KC_SLSH, KC_EQL , KC_AMPR,
    _______, KC_TILD, KC_PLUS, KC_LBRC, KC_RBRC, KC_PERC, _______,
                      _______, _______, _______, _______, _______,

             /* Right side */
                      _______, _______, _______, _______, _______, _______,
                      KC_CIRC, KC_LCBR, KC_RCBR, KC_DLR , KC_PERC, _______,
                      KC_HASH, KC_LPRN, KC_RPRN, KC_SCLN, KC_DQUO, _______,
             _______, KC_AT  , KC_COLN, KC_COMM, KC_DOT , KC_QUOT, _______,
             _______, _______, _______, _______, _______
),
[NAV] = LAYOUT_LR(
    /* Left side */
    _______, _______, _______, _______, _______, _______,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, KC_LALT, XXXXXXX, KC_LSFT, XXXXXXX, XXXXXXX,
    _______, KC_LGUI, XXXXXXX, XXXXXXX, KC_LCTL, XXXXXXX, _______,
                      _______, _______, _______, _______, _______,

             /* Right side */
                      _______, _______, _______, _______, _______, _______,
                      KC_PGUP, KC_HOME, KC_UP  , KC_END , XXXXXXX, _______,
                      KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, _______,
             _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
             QK_LLCK, _______, _______, _______, _______
),
[NUM] = LAYOUT_LR(
    /* Left side */
    _______, _______, _______, _______, _______, _______,
    _______, KC_SLSH, KC_9,    KC_8,    KC_7,    KC_ASTR,
    _______, KC_MINS, KC_3,    KC_2,    KC_1,    KC_PLUS,
    _______, KC_X,    KC_6,    KC_5,    KC_4,    KC_PERC, _______,
                      _______, _______, _______, _______, _______,

             /* Right side */
                      _______, _______, _______, _______, _______, _______,
                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
                      XXXXXXX, XXXXXXX, HRM_E  , XXXXXXX, KC_LALT, _______,
             _______, XXXXXXX, KC_LCTL, KC_COMM, KC_DOT , KC_LGUI, _______,
             QK_LLCK,   KC_0   , _______, _______, _______
),
[WIN] = LAYOUT_LR(
    /* Left side */
    _______, _______, _______, _______, _______, _______,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, KC_LSFT, LCTL(3), LCTL(2), LCTL(1), XXXXXXX,
    _______, XXXXXXX, LCTL(6), LCTL(5), LCTL(4), C(KC_W), _______  ,
                      _______, _______, _______, _______, G(KC_SPC),

             /* Right side */
                      _______, _______, _______, _______, _______, _______,
                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
                      XXXXXXX, XXXXXXX, KC_NXSW, XXXXXXX, XXXXXXX, _______,
             _______, XXXXXXX, KC_NXTB, KC_NXWD, XXXXXXX, XXXXXXX, _______,
             QK_LLCK, _______, _______, _______, _______
),
[FUN] = LAYOUT_LR(
    /* Left side */
    _______, _______, _______, _______, _______, _______,
    _______, KC_F12 , KC_F9  , KC_F8  , KC_F7  , XXXXXXX,
    _______, KC_F10 , KC_F3  , KC_F2  , KC_F1  , XXXXXXX,
    _______, KC_F11 , KC_F6  , KC_F5  , KC_F4  , XXXXXXX, _______,
                      _______, _______, _______, _______, _______,

             /* Right side */
                      _______, _______, _______, _______, _______, _______,
                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
                      XXXXXXX, XXXXXXX, KC_LSFT, XXXXXXX, KC_LALT, _______,
             _______, XXXXXXX, KC_LCTL, XXXXXXX, XXXXXXX, KC_LGUI, _______,
             QK_LLCK, _______, _______, _______, _______
),
[EXT] = LAYOUT_LR(
    /* Left side */
    _______, _______ , _______, _______, _______, _______,
    _______, TO(NHRM), XXXXXXX, XXXXXXX, CG_TOGG, XXXXXXX,
    _______, KC_LALT , KC_LCTL, KC_LSFT, XXXXXXX, XXXXXXX,
    _______, KC_LGUI , C(KC_V), C(KC_A), C(KC_C), XXXXXXX, _______,
                       _______, _______, _______, _______, MS_BTN1,

             /* Right side */
                      _______, _______, _______, _______, _______, _______,
                      MS_WHLU, MS_BTN1, MS_UP  , MS_BTN2, XXXXXXX, _______,
                      MS_WHLD, MS_LEFT, MS_DOWN, MS_RGHT, XXXXXXX, _______,
             _______, XXXXXXX, MS_WHLL, XXXXXXX, MS_WHLR, XXXXXXX, _______,
             QK_LLCK, _______, _______, _______, _______
),
[NHRM] = LAYOUT_LR( // Hands Down Promethium (Inverted)
    /* Left side */
    _______, TO(BASE), _______, _______, _______, _______,
    _______, KC_V    , KC_W   , KC_G   , KC_M   , KC_J   ,
    _______, KC_S    , KC_N   , KC_T   , KC_H   , KC_K   ,
    EXT_UND, KC_F    , KC_P   , KC_D   , KC_L   , KC_X   , KC_MUTE,
                       KC_LEFT, KC_RGHT, KC_BSPC, KC_R   , KC_ESC,

             /* Right side */
                      _______, _______, _______, _______, _______, _______,
                      KC_SCLN, KC_DOT , KC_QUOT, KC_EQL, KC_SLSH, KC_Z   ,
                      KC_COMM, KC_A   , KC_E   , KC_I  , KC_C   , KC_Q   ,
             XXXXXXX, KC_MINS, KC_U   , KC_O   , KC_Y  , KC_B   , KC_ENT ,
             QK_REP , KC_SPC , KC_TAB , KC_UP  , KC_DOWN
),
};

// clang-format on
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_NXWD:
            // Next Window ALT+TAB (Windows) or CMD+TAB (macOS)
            if (record->event.pressed) {
                if (!is_nxwd_active) {
                    is_nxwd_active = true;
                    if (keymap_config.swap_lctl_lgui) {
                        register_mods(mod_config(MOD_LGUI));
                    } else {
                        register_mods(mod_config(MOD_LALT));
                    }
                }

                nxwd_timer = timer_read();
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            break;
        case KC_NXSW:
            // Next Window same app for macOS CMD+`
            if (record->event.pressed) {
                if (!is_nxsw_active) {
                    is_nxsw_active = true;
                    if (keymap_config.swap_lctl_lgui) {
                        register_mods(mod_config(MOD_LGUI));
                    } else {
                        register_mods(mod_config(MOD_LALT));
                    }
                }
                nxsw_timer = timer_read();
                register_code(KC_GRV);
            } else {
                unregister_code(KC_GRV);
            }
            break;
        case KC_NXTB:
            // Next Tab CTRL+TAB
            if (record->event.pressed) {
                if (!is_nxtb_active) {
                    is_nxtb_active = true;
                    register_mods(mod_config(MOD_LCTL));
                }
                nxtb_timer = timer_read();
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            break;
    }
    return true;
}

// Combo definitions
const uint16_t PROGMEM caps_combo[]      = {KC_D, KC_O, COMBO_END};
const uint16_t PROGMEM backslash_combo[] = {KC_P, KC_D, COMBO_END};

combo_t key_combos[] = {
    COMBO(caps_combo, CW_TOGG),      // D and O toggle Caps Word
    COMBO(backslash_combo, KC_BSLS), // P and D produce Backslash
};

void matrix_scan_user(void) {
    if (is_nxwd_active && timer_elapsed(nxwd_timer) > NX_TIMER) {
        if (keymap_config.swap_lctl_lgui) {
            unregister_mods(mod_config(MOD_LGUI));
        } else {
            unregister_mods(mod_config(MOD_LALT));
        }
        is_nxwd_active = false;
    }
    if (is_nxsw_active && timer_elapsed(nxsw_timer) > NX_TIMER) {
        if (keymap_config.swap_lctl_lgui) {
            unregister_mods(mod_config(MOD_LGUI));
        } else {
            unregister_mods(mod_config(MOD_LALT));
        }
        is_nxsw_active = false;
    }
    if (is_nxtb_active && timer_elapsed(nxtb_timer) > NX_TIMER) {
        unregister_mods(mod_config(MOD_LCTL));
        is_nxtb_active = false;
    }
}
// clang-format off

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(MS_WHLU, MS_WHLD) },
    [SYM] =  { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(MS_WHLU, MS_WHLD) },
    [NAV] =  { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(MS_WHLU, MS_WHLD) },
    [NUM] =  { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(MS_WHLU, MS_WHLD) },
    [FUN] =  { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(MS_WHLU, MS_WHLD) },
    [EXT] =  { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(MS_WHLU, MS_WHLD) },
    [NHRM] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(MS_WHLU, MS_WHLD) },
};
#endif // ENCODER_MAP_ENABLE

#ifdef CHORDAL_HOLD
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT_LR(
    /* Left side */
    '*'    , '*'    , '*'    , '*'    , '*'    , '*'    ,
    '*'    , 'L'    , 'L'    , 'L'    , 'L'    , 'L'    ,
    '*'    , 'L'    , 'L'    , 'L'    , 'L'    , 'L'    ,
    '*'    , 'L'    , 'L'    , 'L'    , 'L'    , 'L'    , 'L'    ,
                      '*'    , '*'    , '*'    , '*'    , '*'    ,

             /* Right side */
                      '*'    , '*'    , '*'    , '*'    , '*'    , '*'    ,
                      'R'    , 'R'    , 'R'    , 'R'    , 'R'    , '*'    ,
                      'R'    , 'R'    , 'R'    , 'R'    , 'R'    , '*'    ,
             'R'    , 'R'    , 'R'    , 'R'    , 'R'    , 'R'    , '*'    ,
             '*'    , '*'    , '*'    , '*'    , '*'
    );
#endif // CHORDAL_HOLD

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
        case BASE:
            oled_write_P(PSTR("Base\n"), false);
            break;
        case SYM:
            oled_write_P(PSTR("Sym\n"), false);
            break;
        case NAV:
            oled_write_P(PSTR("Nav\n"), false);
            break;
        case NUM:
            oled_write_P(PSTR("Num\n"), false);
            break;
        case WIN:
            oled_write_P(PSTR("Win\n"), false);
            break;
        case FUN:
            oled_write_P(PSTR("Fun\n"), false);
            break;
        case EXT:
            oled_write_P(PSTR("EXT\n"), false);
            break;
        case NHRM:
            oled_write_P(PSTR("NHRM\n"), false);
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

#endif // OLED_ENABLE
