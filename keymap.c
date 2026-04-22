#include QMK_KEYBOARD_H
#include "keymap_us_international.h"

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _COLEMAK,
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
    _FUNC,
    _GAMING,
    _GAMING_2,
    _MOUSE
};

// custom keycodes
enum custom_keycodes {
  C_FN = SAFE_RANGE,
  C_BLK,
  C_TERMINAL,
  C_QSINGLE,
  C_QDOUBLE,
  C_QGRAVE,
  C_TILDE,
  C_HAT,
  C_CONSOLE,
  C_FEAT,
  C_DEV,
  C_BULLET_JUMP,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define FUNC MO(_FUNC)


const uint16_t PROGMEM combo_esc[] = {KC_Q, KC_SCLN, COMBO_END};
const uint16_t PROGMEM combo_feat[] = {KC_F, KC_E, KC_T, COMBO_END};

combo_t key_combos[] = {
  COMBO(combo_esc, KC_ESC),
  COMBO(combo_feat, C_FEAT),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Colemak
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   Q  |   W  |   F  |   P  |   B  |           |   J  |   L  |   U  |   Y  |   ;  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   A  |   R  |   S  |   T  |   G  |           |   M  |   N  |   E  |   I  |   O  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   Z  |   X  |   C  |   D  |   V  |           |   K  |   H  |   ,  |   .  |   _  |
 * `-------------+--------------------'           `----------------------------------'
 *                  ,--------------------.    ,--------------------.
 *                  | Ctrl  |backsp|R/Spa|    |L/Ente|Func  | Alt  |
 *                  `--------------------'    `--------------------.
 */

// Default config uses home row mods. So hold each of the keys on the home row to use ctrl, gui, alt, or shift
[_COLEMAK] = LAYOUT_split_3x5_3(
  KC_Q,         KC_W,         KC_F,         KC_P,         KC_B,         KC_J,    KC_L,         KC_U,         KC_Y,         KC_SCLN,
  KC_A,         KC_R,         KC_S,         KC_T,         KC_G,         KC_M,    KC_N,         KC_E,         KC_I,         KC_O,
  KC_Z,         KC_X,         KC_C,         KC_D,         KC_V,         KC_K,    KC_H,         KC_COMMA,     KC_DOT,       KC_SLASH,
                              LCTL_T(KC_TAB),  LT(FUNC, KC_BSPC),      LT(RAISE,KC_SPACE),               LT(LOWER,KC_ENTER), KC_LSFT,   LALT_T(KC_LGUI)   
),


/* Raise
 *
 * ,----------------------------------.           ,----------------------------------.
 * |  ^   |   !  |   <  |   >  |   "  |           |   ({ |   => |   =  |   \  |   ~  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  |   |   _  |   {  |   }  |   '  |           |  *   |   (  |   )  |   :  |   #  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  &   |   @  |   [  |   ]  |   `  |           |  -   |  +   |   ?  |   $  |   %  |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,--------------------.
 *                  |      |      |      |    |      | home |  end |
 *                  `--------------------'    `--------------------.
 */
[_RAISE] = LAYOUT_split_3x5_3(
  C_HAT,          KC_EXLM,      KC_LT,       KC_GT,       C_QDOUBLE,          C_BLK,            C_FN,             KC_EQUAL,   KC_NUBS,    C_TILDE,
  KC_PIPE,        KC_UNDS,      KC_LCBR,     KC_RCBR,     C_QSINGLE,          S(KC_8),       KC_LPRN,          KC_RPRN,    KC_COLON,   S(KC_3),
  KC_AMPR,        KC_AT,        KC_LBRC,     KC_RBRC,     C_QGRAVE,           KC_MINUS,         KC_PLUS,          KC_QUES,    KC_DLR, S(KC_5),
                                _______,     _______,     _______,            _______,          KC_HOME,          KC_END
),

/* Lower
 *
 * ,----------------------------------.           ,----------------------------------.
 * | meh  |   1  |   2  |   3  |   .  |           |  /   |  +   |  up  |moveup|tab   |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * | hyper|   4  |   5  |   6  |   ,  |           |  *   |left  |down  | right|enter |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * | ctrl |   7  |   8  |   9  |   0  |           |  -   |  +   |explr |movedo|lattap|
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,--------------------.
 *                  |      |       |     |    |      |      |      |
 *                  `--------------------'    `--------------------.
 */
[_LOWER] = LAYOUT_split_3x5_3(
  KC_LGUI, KC_1,   KC_2, KC_3, KC_DOT,         KC_SLASH,  S(KC_5), KC_UP, A(KC_UP), C(A(KC_TAB)),
  KC_LSFT,  KC_4, KC_5, KC_6, KC_COMMA,        S(KC_8), KC_LEFT, KC_DOWN, KC_RIGHT, KC_ENTER,
  KC_LCTL, KC_7, KC_8, KC_9, KC_0,             KC_MINUS, KC_PLUS, G(KC_E), A(KC_DOWN),  C(S(KC_T)),
                    KC_LALT, KC_LGUI, _______, _______,  _______, _______
),

/* Adjust (Lower + Raise)
 *
 * ,----------------------------------.           ,----------------------------------.
 * |      |      |shot  |      |COLEMK|           |rndm  |loud- |ue    |loud+ |      |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |ae    |      |sz    |      |GAMING|           |      |prev  |Play  |next  |oe    |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |pwr   |      |      |      |      |           |      |      |      |      | Reset|
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,--------------------.
 *                  |      |      |      |    |      |      |      |
 *                  `--------------------'    `--------------------.
 */
[_ADJUST] =  LAYOUT_split_3x5_3(
  _______, _______, G(S(KC_S)), _______, TO(_COLEMAK),       KC_MUTE,   KC_VOLD,    RALT(KC_Y),   KC_VOLU,    _______,
  RALT(KC_Q), _______,  RALT(KC_S), _______, TO(_GAMING),       _______,   KC_MPRV,   KC_MPLY,   KC_MNXT,    RALT(KC_P),
  KC_PWR, _______,  _______, _______, _______,           _______,  KC_BRID,  _______, KC_BRIU,  QK_BOOT,
                     _______, _______, _______,           _______, _______, _______
),

/* Function layer
 *
 * ,----------------------------------.           ,----------------------------------.
 * |esc   |vsexpl| formt|cmdpal| del  |           |  f1  |      |      |      |home  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |undo  |redo  | save |search| bspc |           |      |      |      |      |pgup  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |chkout|merge |commen|palet |term  |           |      |      |      |  f12 |pgdwn |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,--------------------.
 *                  |      |      |      |    |      |      | win  |
 *                  `--------------------'    `--------------------.
 */
[_FUNC] = LAYOUT_split_3x5_3(
  KC_ESC, C(S(KC_E)), A(S(KC_F)), C(S(KC_P)), KC_DEL,        KC_F1, KC_F2, KC_F3, KC_F4, KC_HOME,
  C(KC_Z), C(S(KC_Z)), C(KC_S), C(S(KC_F)), KC_BSPC,           KC_F5, KC_F6, KC_F7, KC_F8, KC_PGUP,
  MEH(KC_C), MEH(KC_F), C(KC_SLASH), C(KC_P), C_TERMINAL,      KC_F9, KC_F10, KC_F11, KC_F12,   KC_PGDN,
                   _______, _______, _______,              _______,  KC_LGUI, KC_LALT
),
/* Mouse layer 
 *
 * ,----------------------------------.           ,----------------------------------.
 * |      |acell0|acell1|acell2|      |           |      |wheell|mv up |wheelr|      |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |      |right |middle|left  |      |           |      |mv l  |mv do |mv r  |      |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |      |      |      |      |      |           |      |      |      |      |      |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,--------------------.
 *                  |      |      |      |    |wheelu|wheeld|      |
 *                  `--------------------'    `--------------------.
 */
 [_MOUSE] = LAYOUT_split_3x5_3(
  _______, MS_ACL0, MS_ACL1, MS_ACL2, _______,        _______, MS_WHLL, MS_UP, MS_WHLR, _______,
  _______, MS_BTN2, MS_BTN3, MS_BTN1, _______,        _______, MS_LEFT, MS_DOWN, MS_RGHT, _______,
  QK_BOOT, _______, _______ ,_______, _______,        _______, _______, _______, _______,   _______,
                    _______, _______, _______,        MS_WHLU,  MS_WHLD, _______
),
};


layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
    state = update_tri_layer_state(state, _RAISE, _FUNC, _MOUSE);
    return state;
}

int keys_down = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    keys_down++;
  } else {
    keys_down--;
  }

  if (record->event.pressed) {
    switch (keycode) {
      case C_FEAT:
        SEND_STRING("feat(msp-):");
        tap_code(KC_LEFT);
        tap_code(KC_LEFT);
        return false;
      case C_DEV:
        SEND_STRING("yarn dev");
        return false;
      case C_CONSOLE:
        SEND_STRING("console.log()");
        tap_code(KC_LEFT);
        return false;
      case C_FN:
        SEND_STRING("=>");
        return false;
      case C_BLK:
        SEND_STRING("({");
        return false;
      case C_BULLET_JUMP:
        register_code(KC_LCTL);
        tap_code(KC_SPACE);
        return false;
      case C_QDOUBLE:
        tap_code16(KC_DQUO);
        tap_code(KC_SPACE);
        return false;
      case C_QSINGLE:
        tap_code(KC_QUOT);
        tap_code(KC_SPACE);
        return false;
      case C_QGRAVE:
        tap_code(KC_GRV);
        tap_code(KC_SPACE);
        return false;
      case C_TILDE:
        tap_code16(S(KC_GRV));
        tap_code(KC_SPACE);
        return false;
      case C_HAT:
        tap_code16(KC_CIRC);
        tap_code(KC_SPACE);
        return false;
      case C_TERMINAL:
        tap_code16(C(KC_K));
        tap_code16(C(KC_COMMA));
        return false;
    }
  } else {
    switch (keycode) {
      case C_BULLET_JUMP:
        unregister_code(KC_LCTL);
        return false;
    }
  }
  return true;
}

bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(RAISE, KC_SPACE):
        case LT(LOWER, KC_ENTER):
            return true;
        default:
            return false;
    }
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(RAISE, KC_SPACE):
        case LT(LOWER, KC_ENTER):
            return 140;
        default:
            return TAPPING_TERM;
    }
}


