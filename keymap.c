// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum ferris_layers {
    _COLEMAK,
    _SYMBOL,
    _NAVI,
    _NUMS,
};

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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_COLEMAK] = LAYOUT( /* COLEMAK */
                        KC_Q,    KC_W,    KC_F,    KC_P,        KC_B,            KC_J,     KC_L,   KC_U,    KC_Y,   KC_SCLN,
                        KC_A,    KC_R,    KC_S,    KC_T,        KC_G,            KC_M,     KC_N,   KC_E,    KC_I,   KC_O,
                        KC_Z,    KC_X,    KC_C,    KC_D,        KC_V,            KC_K,     KC_H,   KC_COMM, KC_DOT, KC_SLSH,
                                                   MO(_SYMBOL), MO(_NAVI),       KC_SPACE, KC_BSPC
                        ),

    [_SYMBOL] = LAYOUT( /* [> SYMBOL <] */
                       KC_TRNS,      KC_TAB,       KC_GRV,       KC_BSLS,      KC_TRNS,         KC_TILD, KC_GRV,    KC_QUOT,         KC_DQT,   KC_EQL,
                       OSM(MOD_LGUI), OSM(MOD_LALT), OSM(MOD_LCTL), OSM(MOD_LSFT), KC_TRNS,     KC_TRNS, TD(TD_PARENS), TD(TD_SQUARE), TD(TD_CURLY), TD(TD_ANGLED),
                       KC_TRNS,      KC_TRNS,      KC_TRNS,      KC_TRNS,      KC_TRNS,         KC_LT,   TD(TD_QUOTE),  TD(TD_DOUBLE_QUOTE), KC_SLSH,  KC_MINS,
                                                                 KC_TRNS,      MO(_NUMS),       KC_TRNS, KC_TRNS
                       ),

    [_NAVI] = LAYOUT( /* [> NAVIGATION <] */
                     KC_TRNS,      KC_TRNS,      KC_TRNS,      KC_TRNS,      KC_TRNS,           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                     OSM(MOD_LGUI), OSM(MOD_LALT), OSM(MOD_LCTL), OSM(MOD_LSFT), KC_TRNS,           KC_TRNS, KC_LEFT, KC_UP,   KC_DOWN, KC_RIGHT,
                     KC_TRNS,      KC_TRNS,      KC_TRNS,      KC_TRNS,      KC_TRNS,           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                                               MO(_NUMS),    KC_TRNS,           KC_TRNS, KC_TRNS
                     ),

    [_NUMS] = LAYOUT( /* [> NUMBERS <] */
                     KC_TRNS, KC_AMPR,   KC_ASTR, KC_LPRN, QK_BOOT,            KC_TRNS, KC_7, KC_8, KC_9, KC_TRNS,
                     KC_TRNS, KC_DOLLAR, KC_PERC, KC_CIRC, KC_END,          KC_TRNS, KC_4, KC_5, KC_6, KC_TRNS,
                     KC_TRNS, KC_EXLM,   KC_AT,   KC_HASH, KC_BTN2,         KC_0,    KC_1, KC_2, KC_3, KC_TRNS,
                                                  KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS
                     )
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
