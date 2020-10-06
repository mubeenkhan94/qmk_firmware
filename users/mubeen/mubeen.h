#pragma once

#include "quantum.h"
#include "process_keycode/process_tap_dance.h"

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

//Tap dance enums
enum {
  X_CTL = 0,
  Y_ALT,
  Z_CUTCPYPST,
  A_SUNRELK,
  TD_TSK_CAD,
  B_ESCTSKCAD,
  C_PRTGUI,
  D_ESCWIN,
  E_SPCENT
};

int cur_dance (qk_tap_dance_state_t *state);

//for the x tap dance. Put it here so it can be used in any keymap
void x_finished (qk_tap_dance_state_t *state, void *user_data);
void x_reset (qk_tap_dance_state_t *state, void *user_data);

//for the y tap dance. Put it here so it can be used in any keymap
void y_finished (qk_tap_dance_state_t *state, void *user_data);
void y_reset (qk_tap_dance_state_t *state, void *user_data);
