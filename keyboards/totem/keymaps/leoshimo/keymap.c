/* 
                                             ▀▀▀▀▀     ▀▀▀▀▀          ▀▀█▀▀
                                             ▄▀▀▀▄  ▄  ▄▀▀▀▄  ▄  ▄▀▀▀▄  █  ▄▀▀▀▄
                                             █   █  █  █   █  █  █   █  █  █   █
                                              ▀▀▀   █   ▀▀▀   █   ▀▀▀   ▀   ▀▀▀
                                                    █      ▄▄▄█▄▄▄    █   █  
                                                    ▀      █  █  █     █▄█
                                                  ▀▀▀▀▀    █  █  █      ▀   
                                                           ▀  ▀  ▀  L E O S H I M O
                                                                                                                                  
▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
*/

#include QMK_KEYBOARD_H
#include <stdio.h>
#include "totem.h"

// ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ D E F I N I T I O N S                                                                                                  │
// └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// ▝▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▘

// ┌─────────────────────────────────────────────────┐
// │ d e f i n e   l a y e r s                       │
// └─────────────────────────────────────────────────┘

enum totem_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
};


// ┌─────────────────────────────────────────────────┐
// │ d e f i n e   m a c r o n a m e s               │
// └─────────────────────────────────────────────────┘

#define SFT_Z LSFT_T(KC_Z)
#define SFT_SLSH RSFT_T(KC_SLSH)

#define LCTL_A LCTL_T(KC_A)

// ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ C O M B O S                                                                                                            │
// └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// ▝▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▘

enum combo_events {
  COMBO_BSLASH,
  COMBO_QUOT,
  COMBO_ESC,
  COMBO_TAB,
  COMBO_TAB_HOME,
  COMBO_GRV,
};

#ifdef COMBO_ENABLE

const uint16_t PROGMEM combo_bslash[] = {KC_O, KC_P, COMBO_END};
const uint16_t PROGMEM combo_quot[] = {KC_L, KC_SCLN, COMBO_END};
const uint16_t PROGMEM combo_tab[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM combo_tab_home[] = {KC_F, KC_D, COMBO_END};
const uint16_t PROGMEM combo_esc[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM combo_grv[] = {KC_1, KC_2, COMBO_END};

#define COMBO_COUNT 6
combo_t key_combos[COMBO_COUNT] = {
  [COMBO_BSLASH] =      COMBO(combo_bslash, KC_BACKSLASH),
  [COMBO_QUOT] =        COMBO(combo_quot, KC_QUOT),
  [COMBO_ESC] =         COMBO(combo_esc, KC_ESC),
  [COMBO_TAB] =         COMBO(combo_tab, KC_TAB),
  [COMBO_TAB_HOME] =    COMBO(combo_tab_home, KC_TAB),
  [COMBO_GRV] =         COMBO(combo_grv, KC_GRV),
};

uint16_t get_combo_term(uint16_t index, combo_t *combo) {
  switch (index) {
    case COMBO_ESC:
    case COMBO_TAB_HOME:
      return 150;
    default:
      return COMBO_TERM;
  }
}

#endif


// ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ K E Y M A P S                                                                                                          │
// └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// ▝▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▘

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

   [_QWERTY] = LAYOUT(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
              KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,      KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,  
              LCTL_A,   KC_S,     KC_D,     KC_F,     KC_G,      KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,    
    LCTL_A,   SFT_Z,    KC_X,     KC_C,     KC_V,     KC_B,      KC_N,     KC_M,     KC_COMM,  KC_DOT,   SFT_SLSH,  RSFT_T(KC_ENT),
                       KC_LGUI,  MO(_LOWER), KC_SPC,    KC_SPC,   MO(_RAISE),  KC_RALT
 ),

   [_LOWER] = LAYOUT(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
              KC_1,     KC_2,     KC_3,     KC_4,     KC_5,      KC_6,     KC_7,     KC_8,     KC_9,     KC_0,
              KC_TAB,   _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,   _______,
                                  _______,  _______,  _______,   _______,  _______,  _______
 ),

   [_RAISE] = LAYOUT(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
              _______,  _______,  _______,  _______,  _______,   _______,  KC_MINS,  KC_EQL,   KC_LBRC,   KC_RBRC,
              _______,  _______,  _______,  _______,  _______,   KC_LEFT,  KC_DOWN,  KC_UP,    KC_RIGHT,  KC_BSPC,
    _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,   _______,
                                  _______,  _______,  _______,   _______,  _______,  _______
 ),

   [_ADJUST] = LAYOUT(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
              QK_BOOT,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,   
              DB_TOGG,  _______,  _______,  _______,  _______,   KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,   _______,
                                  _______,  _______,  _______,   _______,  _______,  _______  
 )

};


// ADJUST Tri-state Layer
layer_state_t layer_state_set_user(layer_state_t state) {
   return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

 /*
  ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸


                                                          ██████
                                                            ██  ▄▄▄▄
                                                            ██ ██▀▀██
                                                            ▀▀ ██▄▄██
                                                        ██████  ▀▀▀▀
                                                          ██ ▄▄▄▄▄▄
                                                          ██ ██▀▀▀▀
                                                          ██ ██████
                                                             ██▄▄▄▄
                                                             ▀▀▀▀▀▀
                                                           ████████
                                                           ██ ██ ██
                                                           ██ ██ ██
                                                           ▀▀ ▀▀ ▀▀
                                                          ████████

*/


