#include "mubeen.h"
#include "quantum.h"
#include "action.h"
#include "process_keycode/process_tap_dance.h"

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicative that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
int cur_dance (qk_tap_dance_state_t *state) {
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

//instantiate an instance of 'tap' for the 'x' tap dance.
static tap xtap_state = {
  .is_press_action = true,
  .state = 0
};

void x_finished (qk_tap_dance_state_t *state, void *user_data) {
  xtap_state.state = cur_dance(state);
  switch (xtap_state.state) {
    case SINGLE_TAP: register_code(KC_DOT); break;
    case SINGLE_HOLD: register_code(KC_LCTRL); break;
    case DOUBLE_TAP: register_code(KC_LSFT); register_code(KC_SLSH); break;
    case DOUBLE_HOLD: register_code(KC_LCTRL); register_code(KC_LSFT); break;
    case DOUBLE_SINGLE_TAP: register_code(KC_DOT); unregister_code(KC_DOT); register_code(KC_DOT);
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void x_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (xtap_state.state) {
    case SINGLE_TAP: unregister_code(KC_DOT); break;
    case SINGLE_HOLD: unregister_code(KC_LCTRL); break;
    case DOUBLE_TAP: unregister_code(KC_LSFT); unregister_code(KC_SLSH); break;
    case DOUBLE_HOLD: unregister_code(KC_LCTRL); unregister_code(KC_LSFT);
    case DOUBLE_SINGLE_TAP: unregister_code(KC_DOT);
  }
  xtap_state.state = 0;
}

//instantiate an instance of 'tap' for the 'y' tap dance.
static tap ytap_state = {
  .is_press_action = true,
  .state = 0
};

void y_finished (qk_tap_dance_state_t *state, void *user_data) {
  ytap_state.state = cur_dance(state);
  switch (ytap_state.state) {
    case SINGLE_TAP: register_code(KC_COMM); break;
    case SINGLE_HOLD: register_code(KC_LALT); break;
    case DOUBLE_TAP: register_code(KC_LSFT); register_code(KC_1); break;
    case DOUBLE_HOLD: register_code(KC_LALT); break;
    case DOUBLE_SINGLE_TAP: register_code(KC_COMM); unregister_code(KC_COMM); register_code(KC_COMM);
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void y_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (ytap_state.state) {
    case SINGLE_TAP: unregister_code(KC_COMM); break;
    case SINGLE_HOLD: unregister_code(KC_LALT); break;
    case DOUBLE_TAP: unregister_code(KC_LSFT); unregister_code(KC_1); break;
    case DOUBLE_HOLD: unregister_code(KC_LALT);
    case DOUBLE_SINGLE_TAP: unregister_code(KC_COMM);
  }
  ytap_state.state = 0;
}

//instantiate an instance of 'tap' for the 'z' tap dance.
static tap ztap_state = {
    .is_press_action = true,
    .state = 0};

void z_finished(qk_tap_dance_state_t *state, void *user_data)
{
  ztap_state.state = cur_dance(state);
  switch (ztap_state.state)
  {
  case SINGLE_TAP:
    // Tap to copy
    register_code(KC_LCTL);
    register_code(KC_C);
    break;
  case SINGLE_HOLD:
    // Hold to paste
    register_code(KC_LCTL);
    register_code(KC_V);
    break;
  case DOUBLE_TAP:
    // Double-tap to cut
    register_code(KC_LCTL);
    register_code(KC_X);
    break;
  case TRIPLE_TAP:
    // Triple-tap to select all
    register_code(KC_LCTL);
    register_code(KC_A);
  }
}

void z_reset(qk_tap_dance_state_t *state, void *user_data)
{
  switch (ztap_state.state)
  {
  case SINGLE_TAP:
    unregister_code(KC_LCTL);
    unregister_code(KC_C);
    break;
  case SINGLE_HOLD:
    unregister_code(KC_LCTL);
    unregister_code(KC_V);
    break;
  case DOUBLE_TAP:
    unregister_code(KC_LCTL);
    unregister_code(KC_A);
    break;
  case TRIPLE_TAP:
    unregister_code(KC_LCTL);
    unregister_code(KC_X);
  }
  ztap_state.state = 0;
}

//instantiate an instance of 'tap' for the 'a' tap dance.
static tap atap_state = {
    .is_press_action = true,
    .state = 0};

void a_finished(qk_tap_dance_state_t * state, void *user_data)
{
  atap_state.state = cur_dance(state);
  switch (atap_state.state)
  {
  case SINGLE_TAP:
    // Tap to save
    register_code(KC_LCTL);
    register_code(KC_S);
    break;
  case SINGLE_HOLD:
    // Hold to lock (WIN)
    register_code(KC_LWIN);
    register_code(KC_L);
    break;
  case DOUBLE_TAP:
    // Double-tap to undo
    register_code(KC_LCTL);
    register_code(KC_Z);
    break;
  case DOUBLE_HOLD:
    // Tap once and then hold to Save As
    register_code(KC_LCTL);
    register_code(KC_LSFT);
    register_code(KC_S);
    break;
  case TRIPLE_TAP:
    // Triple-tap to redo
    register_code(KC_LCTL);
    register_code(KC_Y);
  }
}

void a_reset(qk_tap_dance_state_t * state, void *user_data)
{
  switch (atap_state.state)
  {
  case SINGLE_TAP:
    unregister_code(KC_LCTL);
    unregister_code(KC_S);
    break;
  case SINGLE_HOLD:
    unregister_code(KC_LWIN);
    unregister_code(KC_L);
    break;
  case DOUBLE_TAP:
    unregister_code(KC_LCTL);
    unregister_code(KC_Z);
    break;
  case DOUBLE_HOLD:
    unregister_code(KC_LCTL);
    unregister_code(KC_LSFT);
    unregister_code(KC_S);
    break;
  case TRIPLE_TAP:
    unregister_code(KC_LCTL);
    unregister_code(KC_Y);
  }
  atap_state.state = 0;
}

  //instantiate an instance of 'tap' for the 'b' tap dance.
  static tap btap_state = {
      .is_press_action = true,
      .state = 0};

  void b_finished(qk_tap_dance_state_t * state, void *user_data)
  {
    btap_state.state = cur_dance(state);
    switch (btap_state.state)
    {
    case SINGLE_TAP:
      // Tap for Esc
      register_code(KC_ESC);
      break;
    case DOUBLE_TAP:
      // Double-tap to open Task Manager (WIN)
      register_code(KC_LCTL);
      register_code(KC_LSFT);
      register_code(KC_ESC);
      break;
    case TRIPLE_TAP:
      // Triple-tap to CTRL+ALT+DELETE
      register_code(KC_LCTL);
      register_code(KC_LALT);
      register_code(KC_DEL);
    }
  }

  void b_reset(qk_tap_dance_state_t * state, void *user_data)
  {
    switch (btap_state.state)
    {
    case SINGLE_TAP:
      // Tap for Esc
      unregister_code(KC_ESC);
      break;
    case DOUBLE_TAP:
      // Double-tap to open Task Manager(WIN)
      unregister_code(KC_LCTL);
      unregister_code(KC_LSFT);
      unregister_code(KC_ESC);
      break;
    case TRIPLE_TAP:
      // Triple-tap to CTRL + ALT + DELETE
      register_code(KC_LCTL);
      unregister_code(KC_LALT);
      unregister_code(KC_DEL);
    }
    btap_state.state = 0;
  }

  //instantiate an instance of 'tap' for the 'c' tap dance.
  static tap ctap_state = {
      .is_press_action = true,
      .state = 0};

  void c_finished(qk_tap_dance_state_t *state, void *user_data)
  {
    ctap_state.state = cur_dance(state);
    switch (ctap_state.state)
    {
    case SINGLE_TAP:
      // Tap for LGUI
      register_code(KC_LGUI);
      break;
    case DOUBLE_TAP:
      // Double-tap for Print Screen
      register_code(KC_PSCR);
      break;
    case SINGLE_HOLD:
      // Hold for LGUI
      register_code(KC_LGUI);
    }
  }

  void c_reset(qk_tap_dance_state_t *state, void *user_data)
  {
    switch (ctap_state.state)
    {
    case SINGLE_TAP:
      // Tap for LGUI
      unregister_code(KC_LGUI);
      break;
    case DOUBLE_TAP:
      // Double-tap for Print Screen
      unregister_code(KC_PSCR);
      break;
    case SINGLE_HOLD:
      // Hold for LGUI
      unregister_code(KC_LGUI);
    }
    ctap_state.state = 0;
  }

  //instantiate an instance of 'tap' for the 'd' tap dance.
  static tap dtap_state = {
      .is_press_action = true,
      .state = 0};

  void d_finished(qk_tap_dance_state_t *state, void *user_data)
  {
    dtap_state.state = cur_dance(state);
    switch (dtap_state.state)
    {
    case SINGLE_TAP:
      // Tap for Esc
      register_code(KC_ESC);
      break;
    case SINGLE_HOLD:
      register_code(KC_LWIN);
      register_code(KC_L);
      break;
    case DOUBLE_TAP:
      // Double-tap to open Task Manager (WIN)
      register_code(KC_LCTL);
      register_code(KC_LSFT);
      register_code(KC_ESC);
      break;
    case TRIPLE_TAP:
      // Triple-tap to CTRL+ALT+DELETE
      register_code(KC_LCTL);
      register_code(KC_LALT);
      register_code(KC_DEL);
    }
  }

  void d_reset(qk_tap_dance_state_t *state, void *user_data)
  {
    switch (dtap_state.state)
    {
    case SINGLE_TAP:
      // Tap for Esc
      unregister_code(KC_ESC);
      break;
    case SINGLE_HOLD:
      unregister_code(KC_LWIN);
      unregister_code(KC_L);
      break;
    case DOUBLE_TAP:
      // Double-tap to open Task Manager(WIN)
      unregister_code(KC_LCTL);
      unregister_code(KC_LSFT);
      unregister_code(KC_ESC);
      break;
    case TRIPLE_TAP:
      // Triple-tap to CTRL + ALT + DELETE
      register_code(KC_LCTL);
      unregister_code(KC_LALT);
      unregister_code(KC_DEL);
    }
    dtap_state.state = 0;
  }

  qk_tap_dance_action_t tap_dance_actions[] = {
      [X_CTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished, x_reset),
      [Y_ALT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, y_finished, y_reset),
      [Z_CUTCPYPST] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, z_finished, z_reset),
      [A_SUNRELK] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, a_finished, a_reset),
      [TD_TSK_CAD] = ACTION_TAP_DANCE_DOUBLE(LCTL(LSFT(KC_ESC)), LCTL(LALT(KC_DEL))),
      [B_ESCTSKCAD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, b_finished, b_reset),
      [C_PRTGUI] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, c_finished, c_reset),
      [D_ESCWIN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, d_finished, d_reset),
      [E_SPCENT] = ACTION_TAP_DANCE_DOUBLE(KC_SPC, KC_ENT)
      };
