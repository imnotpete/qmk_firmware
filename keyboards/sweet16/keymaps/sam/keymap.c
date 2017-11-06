#include "sweet16.h"
#include "emailHeader.h"

#define LAYOUT_MACROS 0
#define LAYOUT_NUMPAD 1

enum custom_keycodes {
		UP_URL = SAFE_RANGE,
		CAD, // Ctrl+Alt+Del
		CSE, // Ctrl+Shift+Esc
		COMMENT, // HTML open comment
		SCRSHT // Take screenshot, paste into Paint
};

enum {
		TD_EMAIL_NOTEPAD = 0, // single tap open notepad; double type email header
		TD_DEL_CAD, // single CAD, double Del
		TD_ESC_F12, // single Esc, double F12
		TD_PLAY_LAYER, // single play/pause, triple layer
		TD_ENTER_LAYER // single Enter, triple layer
};

#define TD_EMAIL TD(TD_EMAIL_NOTEPAD)
#define TD_DEL TD(TD_DEL_CAD)
#define TD_ESC TD(TD_ESC_F12)
#define PLAYER TD(TD_PLAY_LAYER)
#define LAYTER TD(TD_ENTER_LAYER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Macros
 * ,---------------------------.
 * | Esc  | HTML |Email |Screen|
 * |------+------+------+------|
 * |Step I|Step A|Step O|Resume|
 * |------+------+------+------|
 * | Mute |Vol Up|Vol Dn| Task |
 * |------+------+------+------|
 * | Prev |Player| Next | Del  |
 * `---------------------------'
 */
[LAYOUT_MACROS] = KEYMAP(
		TD_ESC,  COMMENT, TD_EMAIL, SCRSHT,
		KC_F5,   KC_F6,   KC_F7,    KC_F8,
		KC_MUTE, KC_VOLD, KC_VOLU,  CSE,
		KC_MPRV, PLAYER,  KC_MNXT,  TD_DEL 
), 

/* Numpad
 * ,---------------------------.
 * |  7   |  8   |  9   |  *   |
 * |------+------+------+------|
 * |  4   |  5   |  6   |  -   |
 * |------+------+------+------|
 * |  1   |  2   |  3   |  +   |
 * |------+------+------+------|
 * |  0   |Layter|  .   |  /   |
 * `---------------------------'
 */
[LAYOUT_NUMPAD] = KEYMAP(
		KC_7, KC_8,   KC_9,   KC_ASTR,
		KC_4, KC_5,   KC_6,   KC_MINS,
		KC_1, KC_2,   KC_3,   KC_PLUS,
		KC_0, LAYTER, KC_DOT, KC_SLSH
)
};

void persistent_default_layer_set(uint16_t default_layer) {
		eeconfig_update_default_layer(default_layer);
		default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
		switch (keycode) {
				case CSE: 
						if (record->event.pressed) {
								SEND_STRING(SS_DOWN(X_LCTRL) SS_DOWN(X_LSHIFT) SS_TAP(X_ESCAPE) SS_UP(X_LSHIFT) SS_UP(X_LCTRL));
								return false;
						}
						break;
				case COMMENT: 
						if (record->event.pressed) {
								SEND_STRING("<!--");
								return false;
						}
						break;
				case SCRSHT: 
						if (record->event.pressed) {
								SEND_STRING(SS_TAP(X_PSCREEN) SS_LGUI("r"));
								_delay_ms(750);
								SEND_STRING("mspaint" SS_TAP(X_ENTER));
								_delay_ms(750);
								SEND_STRING(SS_LCTRL("v"));
								return false;
						}
						break;
		}
		return true;
};

void dance_email_notepad(qk_tap_dance_state_t *state, void *user_data) {
		if (state->count == 1) {
				SEND_STRING(SS_LGUI("r"));
				_delay_ms(750);
				SEND_STRING("notepad" SS_TAP(X_ENTER));
		} else {
				send_string(my_str);
		}
}

void dance_delete_cad(qk_tap_dance_state_t *state, void *user_data) {
		if (state->count == 1) {
				SEND_STRING(SS_LCTRL(SS_LALT(SS_TAP(X_DELETE))));
		} else {
				SEND_STRING(SS_TAP(X_DELETE));
		}
}

void dance_player(qk_tap_dance_state_t *state, void *user_data) {
		if (state->count <= 2) {
				register_code(KC_MPLY);
		} else {
				persistent_default_layer_set(1UL<<LAYOUT_NUMPAD);
		}
}

void dance_layter(qk_tap_dance_state_t *state, void *user_data) {
		if (state->count <= 2) {
				SEND_STRING(SS_TAP(X_ENTER));
		} else {
				persistent_default_layer_set(1UL<<LAYOUT_MACROS);
		}
}

qk_tap_dance_action_t tap_dance_actions[] = {
		[TD_EMAIL_NOTEPAD] = ACTION_TAP_DANCE_FN(dance_email_notepad),
		[TD_DEL_CAD] = ACTION_TAP_DANCE_FN(dance_delete_cad),
		[TD_ESC_F12] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_F12),
		[TD_PLAY_LAYER] = ACTION_TAP_DANCE_FN(dance_player),
		[TD_ENTER_LAYER] = ACTION_TAP_DANCE_FN(dance_layter)
};
