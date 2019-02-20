/* Copyright 2019 Danny Nguyen <danny@keeb.io>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "emailHeader.h"

enum custom_keycodes {
	UP_URL = SAFE_RANGE,
	SCRSHT // Take screenshot, paste into Paint
};

enum {
	TD_EMAIL_NOTEPAD = 0, // single tap open notepad; double type email header
	TD_ESC_F12, // single Esc, double F12
};

#define TD_EMAIL TD(TD_EMAIL_NOTEPAD)
#define TD_ESC TD(TD_ESC_F12)
#define OUT LSFT(KC_F11)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_MUTE, TD_EMAIL, KC_MPLY, \
        TD_ESC,  KC_F8,    SCRSHT, \
        KC_F11,  KC_F10,   OUT  \
    ),
	/*
    [1] = LAYOUT(
        RESET,   BL_STEP, KC_STOP, \
        _______, KC_HOME, RGB_MOD, \
        KC_MPRV, KC_END,  KC_MNXT \
    ),
	*/
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    else if (index == 1) {
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
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

qk_tap_dance_action_t tap_dance_actions[] = {
	[TD_EMAIL_NOTEPAD] = ACTION_TAP_DANCE_FN(dance_email_notepad),
	[TD_ESC_F12] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_F12),
};
