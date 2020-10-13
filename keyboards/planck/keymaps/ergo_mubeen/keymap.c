/* Copyright 2015-2017 Jack Humbert
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
#include "muse.h"
#include "mubeen.h"

extern keymap_config_t keymap_config;

enum planck_layers {
  _COLEMAK,
  _LOWER,
  _RAISE,
  _ADJUST,
  _NUM,
  _FN,
  _SYM,
  _NAV
};

enum planck_keycodes {
  COLEMAK = SAFE_RANGE
};

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_LOWER TO(_LOWER)
#define KC_RAISE TO(_RAISE)
#define KC_ADJST TO(_ADJUST)
#define KC_RST   RESET
#define KC_ALGUI LGUI_T(KC_A)
#define KC_RLALT LALT_T(KC_R)
#define KC_SLCTL LCTL_T(KC_S)
#define KC_TLSFT LSFT_T(KC_T)
#define KC_GLWR  LT(_LOWER, KC_G)
#define KC_MRSE  LT(_RAISE, KC_M)
#define KC_NRSFT RSFT_T(KC_N)
#define KC_ERCTL RCTL_T(KC_E)
#define KC_IRALT RALT_T(KC_I)
#define KC_ORGUI RGUI_T(KC_O)
#define KC_EXLM  LSFT(KC_1)
#define KC_AT    LSFT(KC_2)
#define KC_HASH  LSFT(KC_3)
#define KC_DLR   LSFT(KC_4)
#define KC_PERC  LSFT(KC_5)
#define KC_CIRC  LSFT(KC_6)
#define KC_AMPR  LSFT(KC_7)
#define KC_ASTR  LSFT(KC_8)
#define KC_LPRN  LSFT(KC_9)
#define KC_RPRN  LSFT(KC_0)
#define KC_PIPE  LSFT(KC_BSLS)
#define KC_RCBR  LSFT(KC_RBRC)
#define KC_LCBR  LSFT(KC_LBRC)
#define KC_TILD  LSFT(KC_GRV)
#define KC_LESS  LSFT(KC_COMM)
#define KC_GRTR  LSFT(KC_DOT)
#define KC_QUES  LSFT(KC_SLSH)
#define KC_BKNV  LT(_NAV, KC_BSPC)
#define KC_TBFN  LT(_FN, KC_TAB)
#define KC_ENSYM LT(_SYM, KC_ENT)
#define KC_SPCNM LT(_NUM, KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_COLEMAK] = KC_KEYMAP( \

  //,-----------------------------------------------------------------------------------.
          Q,     W,     F,     P,     B,   TAB,  BSPC,     J,     L,     U,     Y,  SCLN,\
  //|------+------+------+------+------+------+------+------+------+------+------+------|
      ALGUI, RLALT, SLCTL, TLSFT,  GLWR,   ESC,  QUOT,  MRSE, NRSFT, ERCTL, IRALT, ORGUI,\
  //|------+------+------+------+------+------+------+------+------+------+------+------|
          Z,     X,     C,     D,     V,  LSFT,   ENT,     K,     H,  COMM,   DOT,  SLSH,\
  //|------+------+------+------+------+------+------+------+------+------+------+------|
       PSCR,  LCTL,  LALT,  LGUI,  BKNV,  TBFN, ENSYM, SPCNM,  LEFT,  DOWN,    UP,  RGHT\
  //|------+------+------+------+------+------+------+------+------+------+------+------'

),

[_NUM] = KC_KEYMAP( \

  //,-----------------------------------------------------------------------------------.
       LBRC,     7,     8,     9,  RBRC, _____, _____, _____, _____, _____, _____, _____,\
  //|------+------+------+------+------+------+------+------+------+------+------+------|
       SCLN,     4,     5,     6,   EQL, _____, _____, _____, _____, _____, _____, _____,\
  //|------+------+------+------+------+------+------+------+------+------+------+------|
        GRV,     1,     2,     3,  BSLS, _____, _____, _____, _____, _____, _____, _____,\
  //|------+------+------+------+------+------+------+------+------+------+------+------|
      _____, _____,   DOT,     0,  MINS, _____, _____, _____, _____, _____, _____, _____ \
  //|------+------+------+------+------+------+------+------+------+------+------+------'

),

[_FN] = KC_KEYMAP( \

  //,-----------------------------------------------------------------------------------.
        F12,    F7,    F8,    F9,  PSCR, _____, _____, _____, _____, _____, _____, _____,\
  //|------+------+------+------+------+------+------+------+------+------+------+------|
        F11,    F4,    F5,    F6,  SLCK, _____, _____, _____, _____, _____, _____, _____,\
  //|------+------+------+------+------+------+------+------+------+------+------+------|
        F10,    F1,    F2,    F3,  PAUS, _____, _____, _____, _____, _____, _____, _____,\
  //|------+------+------+------+------+------+------+------+------+------+------+------|
      _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____ \
  //|------+------+------+------+------+------+------+------+------+------+------+------'

),

[_SYM] = KC_KEYMAP( \

  //,-----------------------------------------------------------------------------------.
       LCBR,  AMPR,  ASTR,  LPRN,  RCBR, _____, _____, _____, _____, _____, _____, _____,\
  //|------+------+------+------+------+------+------+------+------+------+------+------|
       COLN,   DLR,  PERC,  CIRC,  PLUS, _____, _____, _____, _____, _____, _____, _____,\
  //|------+------+------+------+------+------+------+------+------+------+------+------|
       TILD,  EXLM,    AT,  HASH,  PIPE, _____, _____, _____, _____, _____, _____, _____,\
  //|------+------+------+------+------+------+------+------+------+------+------+------|
      _____, _____,    GT,  RPRN,  UNDS, _____, _____, _____, _____, _____, _____, _____ \
  //|------+------+------+------+------+------+------+------+------+------+------+------'

),

[_NAV] = KC_KEYMAP( \

  //,-----------------------------------------------------------------------------------.
      _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____,\
  //|------+------+------+------+------+------+------+------+------+------+------+------|
      _____, _____, _____, _____, _____, _____, _____, _____,  LEFT,  DOWN,    UP,  RGHT,\
  //|------+------+------+------+------+------+------+------+------+------+------+------|
      _____, _____, _____, _____, _____, _____, _____,   INS,  HOME,  PGDN,  PGUP,   END,\
  //|------+------+------+------+------+------+------+------+------+------+------+------|
      _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____, _____ \
  //|------+------+------+------+------+------+------+------+------+------+------+------'

),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |Aud on|Audoff|      |AGnorm|AGswap|      |Colemk|      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */

[_ADJUST] = LAYOUT_planck_grid(
    _______,   RESET,   DEBUG,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  RGB_VAI, RGB_VAD, KC_DEL ,
    _______,  MU_MOD,   AU_ON,    AU_OFF, _______,  AG_NORM, AG_SWAP, _______,  COLEMAK,  _______,  _______,  _______,
    _______,  MUV_DE,  MUV_IN,     MU_ON,  MU_OFF,  MI_ON,   MI_OFF,  TERM_ON, TERM_OFF, _______, _______, _______,
    _______, _______, _______,  _______,  _______, _______, _______, _______, _______,  _______, _______, _______
)

};

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // case QWERTY:
    //   if (record->event.pressed) {
    //     print("mode just switched to qwerty and this is a huge string\n");
    //     set_single_persistent_default_layer(_QWERTY);
    //   }
    //   return false;
    //   break;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;
//     // case BACKLIT:
//     //   if (record->event.pressed) {
//     //     register_code(KC_RSFT);
//     //     #ifdef BACKLIGHT_ENABLE
//     //       backlight_step();
//     //     #endif
//     //     #ifdef KEYBOARD_planck_rev5
//     //       PORTE &= ~(1<<6);
//     //     #endif
//     //   } else {
//     //     unregister_code(KC_RSFT);
//     //     #ifdef KEYBOARD_planck_rev5
//     //       PORTE |= (1<<6);
//     //     #endif
//     //   }
//     //   return false;
//     //   break;
  }
  return true;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update(bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
      #ifdef MOUSEKEY_ENABLE
        register_code(KC_MS_WH_DOWN);
        unregister_code(KC_MS_WH_DOWN);
      #else
        register_code(KC_PGDN);
        unregister_code(KC_PGDN);
      #endif
    } else {
      #ifdef MOUSEKEY_ENABLE
        register_code(KC_MS_WH_UP);
        unregister_code(KC_MS_WH_UP);
      #else
        register_code(KC_PGUP);
        unregister_code(KC_PGUP);
      #endif
    }
  }
}

void matrix_scan_user(void) {
  #ifdef AUDIO_ENABLE
    if (muse_mode) {
      if (muse_counter == 0) {
        uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
        if (muse_note != last_muse_note) {
          stop_note(compute_freq_for_midi_note(last_muse_note));
          play_note(compute_freq_for_midi_note(muse_note), 0xF);
          last_muse_note = muse_note;
        }
      }
      muse_counter = (muse_counter + 1) % muse_tempo;
    }
  #endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case _RAISE:
    case _LOWER:
      return false;
    default:
      return true;
  }
}
