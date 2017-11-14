#include "nyquist.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 3
#define _RAISE 4
#define _FN 5
#define _NUMPAD 6
#define _ADJUST 16

enum custom_keycodes {
		QWERTY = SAFE_RANGE,
		LOWER,
		RAISE,
		ADJUST,
		FN,
		NUMPAD
};

enum {
		TD_TAB_ESC = 0, // single Tab, double Esc
		TD_FN_SPACE // single Tab, double Esc
};

#define TBNXT 0
#define TBPRV 1
#define CAD   2

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define M_TBNXT M(TBNXT)
#define M_TBPRV M(TBPRV)
#define M_CAD   M(CAD)

#define FIND    LALT(LSFT(KC_F7))

#define FN_SPC	LT(_FN, KC_SPC)
#define RS_SPC	LT(_RAISE, KC_SPC)
#define LW_SPC	LT(_LOWER, KC_SPC)

#define TD_TAB   TD(TD_TAB_ESC)
#define TD_SPACE TD(TD_FN_SPACE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bspc |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |NumPad| GUI  | Alt  |Lower |FnSpce|FnSpce|Raise | Home | PgDn | PgUp | End  |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = KEYMAP( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL, \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
  KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT , \
  KC_LCTL, NUMPAD,  KC_LGUI, KC_LALT, LW_SPC,  FN_SPC,  FN_SPC,  RS_SPC,  KC_HOME, KC_PGDN, KC_PGUP, KC_END \
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |     |    \  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | |      |      |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = KEYMAP( \
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, \
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL, \
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,S(KC_NUHS),S(KC_NUBS),_______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |      |      |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = KEYMAP( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL, \
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Reset|RGB Tg|RGB Md|Hue Up|Hue Dn|Sat Up|Sat Dn|Val Up|Val Dn|      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] =  KEYMAP( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, \
  _______, RESET  , RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, _______, KC_DEL, \
  _______, _______, _______, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
),

/* Fn
* ,-----------------------------------------------------------------------------------.
* |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
* |------+------+------+------+------+------+------+------+------+------+------+------|
* |TabPrv|      |      |      |      |      |      | PgUp | Home | PgDn | PScr | Del  |
* |------+------+------+------+------+-------------+------+------+------+------+------|
* |TabNxt|      |      |      | Find |  Go  | Left | Down |  Up  |Right |      |      |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |      |      |      |      |      |      |  End |      |      |      |      |Enter |
* |------+------+------+------+------+------+------+------+------+------+------+------|
* |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
* `-----------------------------------------------------------------------------------'
*/
[_FN] = KEYMAP( \
	_______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, \
	M_TBPRV, _______, _______, _______, _______, _______, _______, KC_PGUP, KC_HOME, KC_PGDN, KC_PSCR, KC_DEL, \
	M_TBNXT, _______, _______, _______, FIND,    KC_F3,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, \
	_______, _______, _______, _______, _______, _______, KC_END,  _______, _______, _______, _______, _______, \
	M_CAD,   _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
),

/* NumPad
* ,-----------------------------------------------------------------------------------.
* |      |      |      |      |      |      |      |  7   |  8   |  9   |  *   |      |
* |------+------+------+------+------+-------------+------+------+------+------+------|
* |      |      |      |      |      |      |      |  4   |  5   |  6   |  -   |      |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |      |      |      |      |      |      |      |  1   |  2   |  3   |  +   |      |
* |------+------+------+------+------+------+------+------+------+------+------+------|
* |      |      |      |      |      |      |      |  0   |      |  .   |  /   |      |
* |------+------+------+------+------+------+------+------+------+------+------+------|
* |      |      |      |      |      |             |      |      |      |      |      |
* `-----------------------------------------------------------------------------------'
*/
[_NUMPAD] = KEYMAP( \
	_______, _______, _______, _______, _______, _______, _______, KC_7,    KC_8,    KC_9,    KC_ASTR, _______, \
	_______, _______, _______, _______, _______, _______, _______, KC_4,    KC_5,    KC_6,    KC_MINS, _______, \
	_______, _______, _______, _______, _______, _______, _______, KC_1,    KC_2,    KC_3,    KC_PLUS, _______, \
	_______, _______, _______, _______, _______, _______, _______, KC_0,    KC_ENT,  KC_DOT,  KC_SLSH, _______, \
	_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ 
)

};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case QWERTY:
			if (record->event.pressed) {
				persistent_default_layer_set(1UL<<_QWERTY);
			}
			return false;
			break;
		case LOWER:
			if (record->event.pressed) {
				layer_on(_LOWER);
				update_tri_layer(_LOWER, _RAISE, _ADJUST);
			} else {
				layer_off(_LOWER);
				update_tri_layer(_LOWER, _RAISE, _ADJUST);
			}
			return false;
			break;
		case RAISE:
			if (record->event.pressed) {
				layer_on(_RAISE);
				update_tri_layer(_LOWER, _RAISE, _ADJUST);
			} else {
				layer_off(_RAISE);
				update_tri_layer(_LOWER, _RAISE, _ADJUST);
			}
			return false;
			break;
		case ADJUST:
			if (record->event.pressed) {
				layer_on(_ADJUST);
			} else {
				layer_off(_ADJUST);
			}
			return false;
			break;
		case FN:
			if (record->event.pressed) {
				layer_on(_FN);
			} else {
				layer_off(_FN);
			}
			return false;
			break;
		case NUMPAD:
			if (record->event.pressed) {
				layer_on(_NUMPAD);
			} else {
				layer_off(_NUMPAD);
			}
			return false;
			break;
	}
	return true;
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
	switch(id) {
		case TBNXT:
			if (record->event.pressed) {
				return MACRO( D(LCTL), T(PGDN), U(LCTL), END  ); 
			}
			break;
		case TBPRV: 
			if (record->event.pressed) {
				return MACRO( D(LCTL), T(PGUP), U(LCTL), END  ); 
			}
			break;
		case CAD: 
			if (record->event.pressed) {
				return MACRO( D(LCTL), D(LALT), T(DEL), U(LALT), U(LCTL), END  ); 
			}
			break;
		case CTRL_W: 
			if (record->event.pressed) {
				return MACRO( D(LCTL), T(X), U(LCTL), END  ); 
			}
			break;
	}
	return MACRO_NONE;
};

qk_tap_dance_action_t tap_dance_actions[] = {
	[TD_TAB_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_TAB, KC_ESC)
};
