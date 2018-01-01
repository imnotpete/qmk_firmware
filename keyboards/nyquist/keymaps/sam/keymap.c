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

enum custom_keycodes {
	QWERTY = SAFE_RANGE,
	LOWER,
	RAISE,
	ADJUST,
	FN,
};

enum {
	TD_TAB_ESC = 0, // single Tab, double Esc
	TD_ESC_CTRL, // single Esc, hold Ctrl
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define TBNXT  LCTL(KC_PGDN)
#define TBPRV  LCTL(KC_PGUP)
#define CAD    LCTL(LALT(KC_DEL))
#define CTRLW  LCTL(KC_W)
#define FIND   LALT(LSFT(KC_F7))
#define FN_SPC LT(_FN, KC_SPC)
#define RS_SPC LT(_RAISE, KC_SPC)
#define LW_SPC LT(_LOWER, KC_SPC)
#define NUMPAD LT(_NUMPAD, KC_TAB)
#define TD_TAB TD(TD_TAB_ESC)
#define TD_ESC TD(TD_ESC_CTRL)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | CAD  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |TabNum|   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bspc |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |EscCtl|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      | GUI  | Alt  |Space |FnSpce|FnSpce|Raise |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = KEYMAP( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    CAD, \
  NUMPAD,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
  TD_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT, \
  _______, _______, KC_LGUI, KC_LALT, KC_SPC,  FN_SPC,  FN_SPC,  RS_SPC,  _______, _______, _______, _______ \
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |      |    \  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | |      |      |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
[_LOWER] = KEYMAP( \
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, \
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL, \
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,S(KC_NUHS),S(KC_NUBS),_______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
),
 */

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |   (  |   )  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = KEYMAP( \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_LPRN, KC_RPRN, _______, \
  _______, _______, _______, _______, _______, _______, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
  _______, _______, _______, _______, _______, _______, _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
),

/* Fn
* ,-----------------------------------------------------------------------------------.
* |  F12 |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 | 
* |------+------+------+------+------+------+------+------+------+------+------+------|
* |TabPrv|      |Ctrl-W|      |      |      |      | PgUp | Home | PgDn | PScr | Del  |
* |------+------+------+------+------+-------------+------+------+------+------+------|
* |TabNxt|      |      |      | Find |  Go  | Left | Down |  Up  |Right |      |      |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |      |      |      |      |      |      |  End |      |      |      |      |      |
* |------+------+------+------+------+------+------+------+------+------+------+------|
* |      |      |      |      |      |             |      |      |      |      |      |
* `-----------------------------------------------------------------------------------'
*/
[_FN] = KEYMAP( \
	KC_F12, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, \
	TBPRV,   _______, CTRLW,   _______, _______, _______, _______, KC_PGUP, KC_HOME, KC_PGDN, KC_PSCR, KC_DEL, \
	TBNXT,   _______, _______, _______, FIND,    KC_F3,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, \
	_______, _______, _______, _______, _______, _______, KC_END,  _______, _______, _______, _______, _______, \
	CAD,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
),

/* NumPad
* ,-----------------------------------------------------------------------------------.
* |      |      |      |      |      |      |      |  7   |  8   |  9   |  *   |      |
* |------+------+------+------+------+-------------+------+------+------+------+------|
* |      |      |      |      |      |      |      |  4   |  5   |  6   |  -   |      |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |      |      |      |      |      |      |      |  1   |  2   |  3   |  +   |      |
* |------+------+------+------+------+------+------+------+------+------+------+------|
* |      |      |      |      |      |      |      |  0   |Enter |  .   |  /   |      |
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
	return true;
}


//**************** Definitions needed for quad function to work *********************//
//Enums used to clearly convey the state of the tap dance
enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4, 
  DOUBLE_SINGLE_TAP = 5 //send SINGLE_TAP twice - NOT DOUBLE_TAP
  // Add more enums here if you want for triple, quadruple, etc. 
};

typedef struct {
  bool is_press_action;
  int state;
} tap;

int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    //If count = 1, and it has been interrupted - it doesn't matter if it is pressed or not: Send SINGLE_TAP
    if (state->interrupted || state->pressed==0) return SINGLE_TAP;
    else return SINGLE_HOLD;
  }
  //If count = 2, and it has been interrupted - assume that user is trying to type the letter associated
  //with single tap. In example below, that means to send `xx` instead of `Escape`.
  else if (state->count == 2) {
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  } 
  else return 6; //magic number. At some point this method will expand to work for more presses
}

//**************** Definitions needed for quad function to work *********************//
static tap esc_tap_state = { 
  .is_press_action = true,
  .state = 0
};

void esc_finished (qk_tap_dance_state_t *state, void *user_data) {
  esc_tap_state.state = cur_dance(state);
  switch (esc_tap_state.state) {
    case SINGLE_TAP: register_code(KC_ESC); break;
    case SINGLE_HOLD: register_code(KC_LCTRL); break;
   // case DOUBLE_TAP: register_code(KC_ESC); break;
   // case DOUBLE_HOLD: register_code(KC_LALT); break;
   // case DOUBLE_SINGLE_TAP: register_code(KC_X); unregister_code(KC_X); register_code(KC_X);
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void esc_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (esc_tap_state.state) {
    case SINGLE_TAP: unregister_code(KC_ESC); break;
    case SINGLE_HOLD: unregister_code(KC_LCTRL); break;
//    case DOUBLE_TAP: unregister_code(KC_ESC); break;
//    case DOUBLE_HOLD: unregister_code(KC_LALT);
//    case DOUBLE_SINGLE_TAP: unregister_code(KC_X);
  }
  esc_tap_state.state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
	[TD_TAB_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_TAB, KC_ESC),
	[TD_ESC_CTRL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, esc_finished, esc_reset)
};
