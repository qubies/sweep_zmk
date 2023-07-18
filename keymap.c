// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include "oneshot.h"
#include "oneshot.c"
#include QMK_KEYBOARD_H


enum ferris_layers {
    _COLEMAK,
    _NAVI,
    _NUMS,
    _SYMBOL,
};

#define LA_SYM MO(_SYMBOL)
#define LA_NAV MO(_NAVI)
#define LA_NUMS MO(_NUMS)

int cur_dance (tap_dance_state_t *state);

//for the x tap dance. Put it here so it can be used in any keymap
void parens_tap (tap_dance_state_t *state, void *user_data);
void square_tap (tap_dance_state_t *state, void *user_data);
void curly_tap (tap_dance_state_t *state, void *user_data);
void angled_tap (tap_dance_state_t *state, void *user_data);
void quote_tap (tap_dance_state_t *state, void *user_data);
void d_quote_tap (tap_dance_state_t *state, void *user_data);


enum ferris_tap_dances {
    TD_PARENS = 0,
    TD_SQUARE,
    TD_CURLY,
    TD_ANGLED,
    TD_QUOTE,
    TD_DOUBLE_QUOTE
};

enum keycodes {
    // Custom oneshot mod implementation with no timers.
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_CMD,
};

enum combos {
    COMBO_ESC,
    COMBO_TAB,
    COMBO_TILDE,
    COMBO_BSLSH,
    COMBO_EQUALS,
    COMBO_SQT,
    COMBO_MINUS,
    COMBO_ENTER,
    COMBO_PASTE,
    COMBO_COPY,
    COMBO_CUT,
    COMBO_DELETE,
    COMBO_DROPDOWN,
    COMBO_DROPDOWN_2,
};

const uint16_t PROGMEM combo_esc[] = {KC_F, KC_P, COMBO_END};
const uint16_t PROGMEM combo_tab[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM combo_tilde[] = {KC_A, KC_R, COMBO_END};
const uint16_t PROGMEM combo_bslsh[] = {KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM combo_sqt[] = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM combo_equals[] = {KC_Y, KC_SCLN, COMBO_END};
const uint16_t PROGMEM combo_minus[] = {KC_DOT, KC_SLSH, COMBO_END};
const uint16_t PROGMEM combo_enter[] = {KC_L, KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM combo_paste[] = {KC_D, KC_V, COMBO_END};
const uint16_t PROGMEM combo_copy[] = {KC_C, KC_D, COMBO_END};
const uint16_t PROGMEM combo_cut[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM combo_delete[] = {KC_BSPC, KC_SPACE, COMBO_END};
const uint16_t PROGMEM combo_dropdown[] = {KC_L, KC_U, COMBO_END};
const uint16_t PROGMEM combo_dropdown_2[] = {KC_H, KC_COMM, COMBO_END};

combo_t key_combos[] = {
    [COMBO_ESC] = COMBO(combo_esc, KC_ESC),
    [COMBO_TAB] = COMBO(combo_tab, KC_TAB),
    [COMBO_TILDE] = COMBO(combo_tilde, KC_GRV),
    [COMBO_BSLSH] = COMBO(combo_bslsh, KC_BSLS),
    [COMBO_EQUALS] = COMBO(combo_equals, KC_EQUAL),
    [COMBO_SQT] = COMBO(combo_sqt, KC_QUOT),
    [COMBO_MINUS] = COMBO(combo_minus, KC_MINS),
    [COMBO_ENTER] = COMBO(combo_enter, KC_ENTER),
    [COMBO_PASTE] = COMBO(combo_paste, LGUI(KC_V)),
    [COMBO_COPY] = COMBO(combo_copy, LGUI(KC_C)),
    [COMBO_CUT] = COMBO(combo_cut, LGUI(KC_X)),
    [COMBO_DELETE] = COMBO(combo_delete, KC_DEL),
    [COMBO_DROPDOWN] = COMBO(combo_dropdown, LCTL(KC_ESC)),
    [COMBO_DROPDOWN_2] = COMBO(combo_dropdown_2, LCTL(KC_ESC)),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_COLEMAK] = LAYOUT( /* COLEMAK */
        KC_Q,             KC_W,          KC_F,          KC_P,              KC_B,            KC_J,     KC_L,               KC_U,                KC_Y,         KC_SCLN,
        KC_A,             KC_R,          KC_S,          MT(MOD_LSFT,KC_T), KC_G,            KC_M,     MT(MOD_RSFT, KC_N), KC_E,                KC_I,         KC_O,
        LT(_SYMBOL,KC_Z), KC_X,          KC_C,          KC_D,              KC_V,            KC_K,     KC_H,               KC_COMM,             KC_DOT,       KC_SLSH,
        LA_NAV,           LA_NUMS,                                                          KC_SPACE, KC_BSPC
    ),

    [_NAVI] = LAYOUT( /* [> NAVIGATION <] */
        KC_TRNS,          KC_TRNS,       KC_TRNS,       KC_TRNS,           KC_TRNS,         KC_TRNS,  KC_TRNS,            KC_TRNS,             KC_TRNS,      KC_TRNS,
        OS_CMD,           OS_ALT,        OS_CTRL,       OS_SHFT,           KC_TRNS,         KC_TRNS,  KC_LEFT,            KC_DOWN,             KC_UP,        KC_RIGHT,
        KC_TRNS,          KC_TRNS,       KC_TRNS,       KC_TRNS,           KC_TRNS,         KC_TRNS,  KC_TRNS,            KC_TRNS,             KC_TRNS,      KC_TRNS,
        KC_TRNS,          LA_SYM,                                                           KC_TRNS,  KC_TRNS
    ),

    [_NUMS] = LAYOUT( /* [> NUMBERS <] */
        KC_TRNS,          KC_AMPR,       KC_ASTR,       KC_LPRN,           QK_BOOT,         KC_TRNS,  KC_7,               KC_8,                KC_9,         KC_TRNS,
        KC_TRNS,          KC_DOLLAR,     KC_PERC,       KC_CIRC,           KC_END,          KC_TRNS,  KC_4,               KC_5,                KC_6,         KC_TRNS,
        KC_TRNS,          KC_EXLM,       KC_AT,         KC_HASH,           KC_BTN2,         KC_0,     KC_1,               KC_2,                KC_3,         KC_TRNS,
        LA_SYM,           KC_TRNS,                                                          KC_TRNS,  KC_TRNS
    ),

    [_SYMBOL] = LAYOUT( /* [> SYMBOL <] */
        KC_TRNS,          KC_TAB,        KC_GRV,        KC_BSLS,           KC_TRNS,         KC_TILD,  KC_GRV,             KC_QUOT,             KC_DQT,       KC_EQL,
        OS_CMD,           OS_ALT,        OS_CTRL,       OS_SHFT,           KC_TRNS,         KC_TRNS,  TD(TD_PARENS),      TD(TD_SQUARE),       TD(TD_CURLY), TD(TD_ANGLED),
        KC_TRNS,          KC_TRNS,       KC_TRNS,       KC_TRNS,           KC_TRNS,         KC_LT,    TD(TD_QUOTE),       TD(TD_DOUBLE_QUOTE), KC_SLSH,      KC_MINS,
        KC_TRNS,          KC_TRNS,                                                          KC_TRNS,  KC_TRNS
    ),
};


void parens_tap (tap_dance_state_t *state, void *user_data){
    switch (state->count) {
        case 1: register_code(KC_LEFT_SHIFT); register_code(KC_9); unregister_code(KC_LEFT_SHIFT); unregister_code(KC_9); break;
        case 2: register_code(KC_LEFT_SHIFT); register_code(KC_0); unregister_code(KC_LEFT_SHIFT); unregister_code(KC_0); break;
        default: register_code(KC_LEFT_SHIFT);  register_code(KC_9); register_code(KC_0); unregister_code(KC_LEFT_SHIFT); unregister_code(KC_9); unregister_code(KC_0); register_code(KC_LEFT); unregister_code(KC_LEFT); break;
    }
}

void square_tap (tap_dance_state_t *state, void *user_data){
    switch (state->count) {
        case 1: register_code(KC_LBRC); unregister_code(KC_LBRC); break;
        case 2: register_code(KC_RBRC); unregister_code(KC_RBRC); break;
        default: register_code(KC_LBRC);  unregister_code(KC_LBRC); register_code(KC_RBRC); unregister_code(KC_RBRC); register_code(KC_LEFT); unregister_code(KC_LEFT); break;
    }
}
void curly_tap (tap_dance_state_t *state, void *user_data){
    switch (state->count) {
        case 1: register_code(KC_LEFT_SHIFT); register_code(KC_LBRC); unregister_code(KC_LEFT_SHIFT); unregister_code(KC_LBRC); break;
        case 2: register_code(KC_LEFT_SHIFT); register_code(KC_RBRC); unregister_code(KC_LEFT_SHIFT); unregister_code(KC_RBRC); break;
        default: register_code(KC_LEFT_SHIFT);  register_code(KC_LBRC); register_code(KC_RBRC); unregister_code(KC_LEFT_SHIFT); unregister_code(KC_LBRC); unregister_code(KC_RBRC); register_code(KC_LEFT); unregister_code(KC_LEFT); break;
    }
}
void angled_tap (tap_dance_state_t *state, void *user_data){
    switch (state->count) {
        case 1: register_code(KC_LEFT_SHIFT); register_code(KC_COMM); unregister_code(KC_LEFT_SHIFT); unregister_code(KC_COMM); break;
        case 2: register_code(KC_LEFT_SHIFT); register_code(KC_DOT); unregister_code(KC_LEFT_SHIFT); unregister_code(KC_DOT); break;
        default: register_code(KC_LEFT_SHIFT);  register_code(KC_COMM); register_code(KC_DOT); unregister_code(KC_LEFT_SHIFT); unregister_code(KC_COMM); unregister_code(KC_DOT); register_code(KC_LEFT); unregister_code(KC_LEFT); break;
    }
}
void quote_tap (tap_dance_state_t *state, void *user_data){
    switch (state->count) {
        case 1: register_code(KC_QUOT); unregister_code(KC_QUOT); break;
        default: register_code(KC_QUOT); unregister_code(KC_QUOT);register_code(KC_QUOT); unregister_code(KC_QUOT); register_code(KC_LEFT); unregister_code(KC_LEFT); break;
    }
}
void d_quote_tap (tap_dance_state_t *state, void *user_data){
    switch (state->count) {
        case 1: register_code(KC_LEFT_SHIFT); register_code(KC_QUOT); unregister_code(KC_QUOT); unregister_code(KC_LEFT_SHIFT); break;
        default: register_code(KC_LEFT_SHIFT); register_code(KC_QUOT); unregister_code(KC_QUOT);register_code(KC_QUOT); unregister_code(KC_QUOT); unregister_code(KC_LEFT_SHIFT); register_code(KC_LEFT); unregister_code(KC_LEFT); break;
    }
}

// Tap Dance Definitions
tap_dance_action_t tap_dance_actions[] = {
    [TD_PARENS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, NULL, parens_tap),
    [TD_SQUARE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, NULL, square_tap),
    [TD_CURLY] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, NULL, curly_tap),
    [TD_ANGLED] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, NULL, angled_tap),
    [TD_QUOTE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, NULL, quote_tap),
    [TD_DOUBLE_QUOTE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, NULL, d_quote_tap)
};


bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case KC_ESC:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case LA_SYM:
    case LA_NAV:
    case LA_NUMS:
    case KC_LSFT:
    case KC_RSFT:
    case OS_SHFT:
    case OS_CTRL:
    case OS_ALT:
    case OS_CMD:
        return true;
    default:
        return false;
    }
}

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_oneshot(
        &os_shft_state, KC_LSFT, OS_SHFT,
        keycode, record
    );
    update_oneshot(
        &os_ctrl_state, KC_LCTL, OS_CTRL,
        keycode, record
    );
    update_oneshot(
        &os_alt_state, KC_LALT, OS_ALT,
        keycode, record
    );
    update_oneshot(
        &os_cmd_state, KC_LCMD, OS_CMD,
        keycode, record
    );

    return true;
}
