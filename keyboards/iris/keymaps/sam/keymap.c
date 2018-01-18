#include "iris.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

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

#define TBNXT  LCTL(KC_PGDN)
#define TBPRV  LCTL(KC_PGUP)
#define CAD    LCTL(LALT(KC_DEL))
#define CTRLW  LCTL(KC_W)
#define CTRLT  LCTL(KC_T)
#define FIND   LALT(LSFT(KC_F7))
#define FN_SPC LT(_FN, KC_SPC)
#define RS_SPC LT(_RAISE, KC_SPC)
#define LW_SPC LT(_LOWER, KC_SPC)
#define NUMPAD LT(_NUMPAD, KC_TAB)
#define TD_TAB TD(TD_TAB_ESC)
#define TD_ESC TD(TD_ESC_CTRL)

#define KC_ KC_TRNS
#define _______ KC_TRNS

#define KC_NUMP NUMPAD
#define KC_FSPC FN_SPC
#define KC_RSPC RS_SPC
#define KC_CAD CAD
#define KC_TESC TD_ESC
#define KC_TPRV TBPRV
#define KC_TNXT TBNXT
#define KC_CTLW CTRLW
#define KC_CTLT CTRLT
#define KC_FIND FIND
#define KC_LOWR LOWER
#define KC_RASE RAISE
#define KC_RST RESET
#define KC_BL_S BL_STEP

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = KC_KEYMAP(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     GRV , 1  , 2  , 3  , 4  , 5  ,                6  , 7  , 8  , 9  , 0  ,BSPC,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     NUMP, Q  , W  , E  , R  , T  ,                Y  , U  , I  , O  , P  ,BSLS,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     TESC, A  , S  , D  , F  , G  ,                H  , J  , K  , L  ,SCLN,QUOT,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     LSFT, Z  , X  , C  , V  , B  ,FSPC,     FSPC, N  , M  ,COMM,DOT ,SLSH,ENT ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       LGUI,LALT,FSPC ,        FSPC,RSPC,CAD
  //                  `----+----+----'        `----+----+----'
  ),

  [_RAISE] = KC_KEYMAP(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
         ,    ,    ,    ,    ,    ,                   ,    ,    ,LPRN,RPRN,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,                   ,UNDS,PLUS,LCBR,RCBR,PIPE,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,                   ,MINS, EQL,LBRC,RBRC,BSLS,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,             ,    ,    
  //                  `----+----+----'        `----+----+----'
  ),

  [_FN] = KC_KEYMAP(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     F12 , F1 , F2 , F3 , F4 , F5 ,                F6 , F7 , F8 , F9 ,F10 ,F11 ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     TPRV,    ,CTLW,    ,    ,CTLT,                   ,PGUP,HOME,PGDN,PSCR,DEL ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     TNXT,    ,    ,    ,FIND, F3 ,               LEFT,DOWN, UP ,RGHT,    ,    ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         ,END ,    ,    ,    ,    ,    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,             ,    ,    
  //                  `----+----+----'        `----+----+----'
  ),

  [_NUMPAD] = KC_KEYMAP(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
         ,    ,    ,    ,    ,    ,                   , 7  , 8  , 9  ,ASTR,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,                   , 4  , 5  , 6  ,MINS,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,                   , 1  , 2  , 3  ,PLUS,    ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         ,    , 0  ,ENT ,DOT ,SLSH,    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,             ,    ,    
  //                  `----+----+----'        `----+----+----'
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
