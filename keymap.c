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
  int state;
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


int cur_dance (qk_tap_dance_state_t *state);

//for the x tap dance. Put it here so it can be used in any keymap
void parens_finished (qk_tap_dance_state_t *state, void *user_data);
void parens_reset (qk_tap_dance_state_t *state, void *user_data);
void square_finished (qk_tap_dance_state_t *state, void *user_data);
void square_reset (qk_tap_dance_state_t *state, void *user_data);
void curly_finished (qk_tap_dance_state_t *state, void *user_data);
void curly_reset (qk_tap_dance_state_t *state, void *user_data);
void angled_finished (qk_tap_dance_state_t *state, void *user_data);
void angled_reset (qk_tap_dance_state_t *state, void *user_data);
void quote_finished (qk_tap_dance_state_t *state, void *user_data);
void quote_reset (qk_tap_dance_state_t *state, void *user_data);
void dquote_finished (qk_tap_dance_state_t *state, void *user_data);
void dquote_reset (qk_tap_dance_state_t *state, void *user_data);


enum ferris_tap_dances {
  TD_PARENS = 0,
  TD_SQUARE,
  TD_CURLY,
  TD_ANGLED,
  TD_QUOTE,
  TD_DOUBLE_QUOTE
};

#define KC_CTSC RCTL_T(KC_SCLN)
#define KC_CTLA LCTL_T(KC_A)
#define KC_LSHZ LSFT_T(KC_Z)
#define KC_RLSH RSFT_T(KC_SLSH)
#define KC_SPM2 LT(2, KC_SPC)
#define KC_BSM1 LT(1, KC_BSPC)
#define KC_GUTA GUI_T(KC_TAB)
#define KC_CLGV CTL_T(KC_GRV)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_COLEMAK] = LAYOUT( /* COLEMAK */
    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,            KC_J,    KC_L,  KC_L,    KC_Y,   KC_SCLN,
    KC_A,    KC_R,    KC_S,    KC_T,    KC_G,            KC_M,    KC_N,  KC_E,    KC_I,   KC_O,
    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,            KC_K,    KC_H,  KC_COMM, KC_DOT, KC_SLSH,
                                    KC_CLGV, KC_BSM1, KC_SPM2, KC_GUTA
  ),

  [_SYMBOL] = LAYOUT( /* [> LOWER <] */
    KC_TRNS,      KC_TAB,       KC_GRV,       KC_BSLS,      KC_TRNS,         KC_TILD, KC_GRV,  KC_QUOT, KC_DQT,  KC_EQL,
    OSM(KC_LGUI), OSM(KC_LALT), OSM(KC_LCTL), OSM(KC_LSFT), KC_TRNS,         KC_TRNS, KC_DOWN, KC_UP,   KC_RGHT, KC_TRNS,
    KC_TRNS,      KC_TRNS,      KC_TRNS,      KC_TRNS,      KC_TRNS,         KC_LT, KC_MS_D, KC_MS_U, KC_MS_R, KC_TRNS,
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
    QK_GESC, KC_HOME, KC_PGDN, KC_PGUP, KC_END,          KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_QUOT,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,         KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_ENT,
                                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),
  [_FUNCS] = LAYOUT( /* [> LOWER <] */
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,            KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    QK_GESC, KC_HOME, KC_PGDN, KC_PGUP, KC_END,          KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_QUOT,
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

// Tap Dance Definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Q, twice for ESC
    [TD_Q_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_ESC)
  [ TD_PARENS ]= ACTION_TAP_DANCE_DOUBLE()
  [ TD_SQUARE ]=
  [ TD_CURLY ]=
  [ TD_ANGLED ]=
  [ TD_QUOTE ]=
  [ TD_DOUBLE_QUOTE ]=
};
