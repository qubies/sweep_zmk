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
    _FUNCS,
    _MEDIA
};

typedef struct {
    bool is_press_action;
    uint8_t state;
} tap;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD = 2,
    DOUBLE_TAP = 3,
    DOUBLE_HOLD = 4,
    DOUBLE_SINGLE_TAP = 5, //send two single taps
    TRIPLE_TAP = 6,
    TRIPLE_HOLD = 7
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
                        KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,            KC_J,    KC_L,  KC_L,    KC_Y,   KC_SCLN,
                        KC_A,    KC_R,    KC_S,    KC_T,    KC_G,            KC_M,    KC_N,  KC_E,    KC_I,   KC_O,
                        KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,            KC_K,    KC_H,  KC_COMM, KC_DOT, KC_SLSH,
                        KC_Z, KC_Z, KC_Z, KC_Z
                        ),

    [_SYMBOL] = LAYOUT( /* [> LOWER <] */
                       KC_TRNS,      KC_TAB,       KC_GRV,       KC_BSLS,      KC_TRNS,         KC_TILD, KC_GRV,  KC_QUOT, KC_DQT,  KC_EQL,
                       OSM(KC_LGUI), OSM(KC_LALT), OSM(KC_LCTL), OSM(KC_LSFT), KC_TRNS,         KC_TRNS, TD_PARENS, TD_SQUARE,   TD_CURLY, TD_ANGLED,
                       KC_TRNS,      KC_TRNS,      KC_TRNS,      KC_TRNS,      KC_TRNS,         KC_LT, TD_QUOTE, TD_DOUBLE_QUOTE, KC_SLSH, KC_MINS,
                       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
                       ),

    [_NAVI] = LAYOUT( /* [> RAISE <] */
                     KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,           KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
                     KC_TAB,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_PIPE,
                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_UNDS, KC_PLUS, KC_TRNS, KC_TRNS, QK_BOOT,
                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
                     ),
    [_NUMS] = LAYOUT( /* [> LOWER <] */
                     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,            KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
                     KC_Z, KC_HOME, KC_PGDN, KC_PGUP, KC_END,          KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_QUOT,
                     KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,         KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_ENT,
                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
                     ),
    [_FUNCS] = LAYOUT( /* [> LOWER <] */
                      KC_1,    KC_2,    KC_3,    KC_4,    KC_5,            KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
                      KC_Z, KC_HOME, KC_PGDN, KC_PGUP, KC_END,          KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_QUOT,
                      KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,         KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_ENT,
                      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
                      ),
    [_MEDIA] = LAYOUT( /* [> LOWER <] */
                      KC_1,    KC_2,    KC_3,    KC_4,    KC_5,            KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
                      QK_GESC, KC_HOME, KC_PGDN, KC_PGUP, KC_END,          KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_QUOT,
                      KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,         KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_ENT,
                      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
                      )
};


int cur_dance (tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed)  return SINGLE_TAP;
            //key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
        else return SINGLE_HOLD;
    }
    else if (state->count == 2) {
        /*
     * DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
     * action when hitting 'pp'. Suggested use case for this return value is when you want to send two
     * keystrokes of the key, and not the 'double tap' action/macro.
    */
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    //Assumes no one is trying to type the same letter three times (at least not quickly).
    //If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    //an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
        else return TRIPLE_HOLD;
    }
    else return 8; //magic number. At some point this method will expand to work for more presses
}

//instanalize an instance of 'tap' for the 'x' tap dance.
static tap xtap_state = {
    .is_press_action = true,
    .state = 0
};

void parens_tap (tap_dance_state_t *state, void *user_data){
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP: register_code(KC_LEFT_SHIFT); register_code(KC_9); unregister_code(KC_LEFT_SHIFT); unregister_code(KC_9); break;
        case SINGLE_HOLD: register_code(KC_LEFT_SHIFT); register_code(KC_0); unregister_code(KC_LEFT_SHIFT); unregister_code(KC_0); break;
        case DOUBLE_TAP: register_code(KC_LEFT_SHIFT);  register_code(KC_9); register_code(KC_0); unregister_code(KC_LEFT_SHIFT); register_code(KC_LEFT); break;
    }
}

void square_tap (tap_dance_state_t *state, void *user_data){
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP: register_code(KC_LEFT_SHIFT); register_code(KC_9); unregister_code(KC_LEFT_SHIFT); unregister_code(KC_9); break;
        case SINGLE_HOLD: register_code(KC_LEFT_SHIFT); register_code(KC_0); unregister_code(KC_LEFT_SHIFT); unregister_code(KC_0); break;
        case DOUBLE_TAP: register_code(KC_LEFT_SHIFT);  register_code(KC_9); register_code(KC_0); unregister_code(KC_LEFT_SHIFT); register_code(KC_LEFT); break;
    }
}
void curly_tap (tap_dance_state_t *state, void *user_data){
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP: register_code(KC_LEFT_SHIFT); register_code(KC_9); unregister_code(KC_LEFT_SHIFT); unregister_code(KC_9); break;
        case SINGLE_HOLD: register_code(KC_LEFT_SHIFT); register_code(KC_0); unregister_code(KC_LEFT_SHIFT); unregister_code(KC_0); break;
        case DOUBLE_TAP: register_code(KC_LEFT_SHIFT);  register_code(KC_9); register_code(KC_0); unregister_code(KC_LEFT_SHIFT); register_code(KC_LEFT); break;
    }
}
void angled_tap (tap_dance_state_t *state, void *user_data){
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP: register_code(KC_LEFT_SHIFT); register_code(KC_9); unregister_code(KC_LEFT_SHIFT); unregister_code(KC_9); break;
        case SINGLE_HOLD: register_code(KC_LEFT_SHIFT); register_code(KC_0); unregister_code(KC_LEFT_SHIFT); unregister_code(KC_0); break;
        case DOUBLE_TAP: register_code(KC_LEFT_SHIFT);  register_code(KC_9); register_code(KC_0); unregister_code(KC_LEFT_SHIFT); register_code(KC_LEFT); break;
    }
}
void quote_tap (tap_dance_state_t *state, void *user_data){
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP: register_code(KC_LEFT_SHIFT); register_code(KC_9); unregister_code(KC_LEFT_SHIFT); unregister_code(KC_9); break;
        case SINGLE_HOLD: register_code(KC_LEFT_SHIFT); register_code(KC_0); unregister_code(KC_LEFT_SHIFT); unregister_code(KC_0); break;
        case DOUBLE_TAP: register_code(KC_LEFT_SHIFT);  register_code(KC_9); register_code(KC_0); unregister_code(KC_LEFT_SHIFT); register_code(KC_LEFT); break;
    }
}
void d_quote_tap (tap_dance_state_t *state, void *user_data){
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP: register_code(KC_LEFT_SHIFT); register_code(KC_9); unregister_code(KC_LEFT_SHIFT); unregister_code(KC_9); break;
        case SINGLE_HOLD: register_code(KC_LEFT_SHIFT); register_code(KC_0); unregister_code(KC_LEFT_SHIFT); unregister_code(KC_0); break;
        case DOUBLE_TAP: register_code(KC_LEFT_SHIFT);  register_code(KC_9); register_code(KC_0); unregister_code(KC_LEFT_SHIFT); register_code(KC_LEFT); break;
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
