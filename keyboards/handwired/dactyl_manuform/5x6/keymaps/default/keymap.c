#include QMK_KEYBOARD_H

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _FPS 3

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)
#define FPS TG(_FPS)

enum custom_keycodes {
    MUTE_OBS = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_5x6(
        KC_ESC , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                         KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,KC_GRV,
        KC_TAB , KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  ,                         KC_Y  , KC_U  , KC_I  , KC_O  , KC_P  ,KC_MINS,
        MT(MOD_LSFT, KC_CAPS), KC_A ,KC_S ,KC_D, KC_F, KC_G,                     KC_H  , KC_J  , KC_K  , KC_L  ,KC_SCLN,KC_QUOT,
        KC_LCTL, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  ,                          KC_N  , KC_M  ,KC_COMM,KC_DOT ,KC_SLSH,KC_BSLS,
                         KC_LBRC,KC_RBRC,                                                       KC_PLUS, KC_EQL,
                                         RAISE,KC_SPC,                           KC_BSPC, LOWER,
                                         KC_LALT,KC_LGUI,                        KC_ENT,  KC_DEL,
                                         FPS, KC_HOME,                           KC_END, RAISE
    ),

    [_LOWER] = LAYOUT_5x6(
        KC_TILD,KC_EXLM, KC_AT ,KC_HASH,KC_DLR ,KC_PERC,                        KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,KC_DEL,
        _______,_______,_______,_______,_______,KC_LBRC,                        KC_RBRC, KC_P7 , KC_P8 , KC_P9 ,_______,KC_PLUS,
        _______,KC_HOME,KC_PGUP,KC_PGDN,KC_END ,KC_LPRN,                        KC_RPRN, KC_P4 , KC_P5 , KC_P6 ,KC_MINS,KC_PIPE,
        _______,_______,_______,_______,_______,KC_LCBR,                        KC_RCBR, KC_P1 , KC_P2 , KC_P3 ,KC_EQL ,KC_UNDS,
                        _______,KC_PSCR,                                                        MUTE_OBS, KC_P0,
                                                _______,_______,            _______,_______,
                                                _______,_______,            _______,_______,
                                                _______,_______,            _______,_______
    ),

    [_RAISE] = LAYOUT_5x6(
          KC_F12 , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,                        KC_F6  , KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_F11,
          _______,_______,_______,_______,_______,KC_LBRC,                        KC_RBRC,_______,KC_NUM,KC_INS ,KC_SCRL,KC_MUTE,
          _______,KC_LCBR,KC_RCBR,KC_LPRN,KC_RPRN,_______,                        KC_LEFT,KC_DOWN  ,KC_UP,KC_RGHT,_______,KC_VOLU,
          _______,_______,_______,_______,_______,_______,                        KC_RPRN,KC_MPRV,KC_MPLY,KC_MNXT,_______,KC_VOLD,
                                  _______,MUTE_OBS,                                                 KC_EQL ,_______,
                                                  _______,_______,            _______,_______,
                                                  _______,_______,            _______,_______,
                                                  QK_BOOT,_______,            _______,_______
    ),

    [_FPS] = LAYOUT_5x6(
        _______, _______, _______, _______, _______, _______,                    _______  , _______  , _______  , _______  , _______  ,_______,
        KC_TAB               , _______ , KC_Q  , KC_W  , KC_E, KC_R,             _______  , _______  , _______  , _______  , _______  ,_______,
        KC_LSFT, KC_A    , KC_A  , KC_S  , KC_D, KC_F,                           _______  , _______  , _______  , _______  , _______  ,_______,
        KC_LCTL              , KC_Z    , KC_X  , KC_C  , KC_V, KC_B,             _______  , _______  , _______  , _______  , _______  ,_______,
                         _______,_______,                                                       _______, _______,
                                         _______, _______,                           _______, _______,
                                         _______, _______,                           _______, _______,
                                         _______, _______,                          _______, _______
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
    #ifdef CONSOLE_ENABLE
        uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
    #endif 

    switch (keycode) {
        case MUTE_OBS:
            if (record->event.pressed) {
                register_code(KC_LGUI);
                register_code(KC_F2);
                unregister_code(KC_F2);
                unregister_code(KC_LGUI);
            }
    }

  return true;
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QK_BOOT:
            return TAPPING_TERM + 1250;
        default:
            return TAPPING_TERM;
    }
}
