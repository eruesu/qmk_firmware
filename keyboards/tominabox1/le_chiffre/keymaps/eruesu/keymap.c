/* Copyright 2020 tominabox1
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

enum layers{
  _BASE,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum keycodes {
  KC_USR_CMD_TAB = SAFE_RANGE,
  KC_USR_CMD_SHIFT_TAB,
};


// Layer + Space
#define KC_SPC_LWR LT(_LOWER, KC_SPC)
#define KC_SPC_RSE LT(_RAISE, KC_SPC)
#define KC_GA LGUI_T(KC_A)
#define KC_AS LALT_T(KC_S)
#define KC_CD LCTL_T(KC_D)
#define KC_SF LSFT_T(KC_F)
#define KC_SJ RSFT_T(KC_J)
#define KC_CK RCTL_T(KC_K)
#define KC_AL RALT_T(KC_L)
#define KC_GSCLN RGUI_T(KC_SCLN)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    KC_Q,           KC_W,   KC_E,   KC_R,   KC_T,  KC_MPLY,  KC_Y,   KC_U,    KC_I,   KC_O,     KC_P,
    LCTL_T(KC_A),   KC_S,  KC_D,  KC_F,   KC_G,              KC_H,  KC_J,   KC_K,   KC_L,    RCTL_T(KC_SCLN),
    LSFT_T(KC_Z),   KC_X,   KC_C,   KC_V,   KC_B,            KC_N,   KC_M, KC_COMM, KC_DOT,  RSFT_T(KC_SLSH),
                      KC_RGUI, KC_SPC_LWR,            KC_SPC_RSE, KC_RALT
  ),

  [_LOWER] = LAYOUT(
      KC_1,     KC_2,     KC_3,     KC_4,     KC_5,    _______,  KC_6,     KC_7,     KC_8,     KC_9,     KC_0,
      KC_TAB,  _______,  KC_USR_CMD_SHIFT_TAB,  KC_USR_CMD_TAB,  _______,           KC_LEFT,  KC_DOWN,  KC_UP,  KC_RIGHT,   _______,
      _______,  _______,  _______,  _______,  _______,           _______,  _______,  _______,   _______,  _______,
                      KC_RGUI, KC_SPC_LWR,            KC_SPC_RSE, KC_RALT
  ),

  [_RAISE] = LAYOUT(
      KC_GRV,  _______,  _______,  _______,  _______, _______,   _______,  KC_MINS,    KC_EQL,  KC_LBRC, KC_RBRC,
      KC_TAB,  _______,  _______,  _______,  _______,           KC_LEFT,  KC_DOWN,  KC_UP,  KC_RIGHT,   KC_BSPC,
      _______,  _______,  _______,  _______,  _______,           _______,  _______,  _______,   _______,  KC_ENT,
                                  KC_RGUI, KC_SPC_LWR,            KC_SPC_RSE, KC_RALT
  ),

  [_ADJUST] = LAYOUT(
      _______,  _______,  _______,  _______,  _______, _______,  _______,  KC_MS_WH_UP,  KC_MS_WH_DOWN,   _______,  RGB_TOG,
      _______,  _______,  _______,  _______,  _______,           KC_MS_LEFT, KC_MS_DOWN, KC_MS_UP, KC_MS_RIGHT,  RGB_MODE_FORWARD,
      _______,  _______,  _______,  _______,  _______,           _______,  KC_MS_BTN1,  KC_MS_BTN2,   _______,  RGB_MODE_REVERSE,
                      KC_RGUI, KC_SPC_LWR,            KC_SPC_RSE, KC_RALT
  ),
};

// ADJUST Tri-state Layer
layer_state_t layer_state_set_user(layer_state_t state) {
   return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

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
const uint16_t PROGMEM combo_quot[] = {KC_L, RCTL_T(KC_SCLN), COMBO_END};
const uint16_t PROGMEM combo_tab[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM combo_tab_home[] = {KC_F, KC_D, COMBO_END};
const uint16_t PROGMEM combo_esc[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM combo_grv[] = {KC_1, KC_2, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [COMBO_BSLASH] =      COMBO(combo_bslash, KC_BSLASH),
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

#ifdef RGBLIGHT_ENABLE
void keyboard_post_init_user(void) {
  rgblight_enable_noeeprom(); // Enables RGB, without saving settings
  rgblight_sethsv_noeeprom(HSV_PURPLE);
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
}
#endif

#ifdef OLED_DRIVER_ENABLE  //Special thanks to Sickbabies for this great OLED widget!
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_90;  // rotates for proper orientation
}

void render_lechiffre_logo(void) {
    static const char PROGMEM lechiffre_logo[] = {
	// 'lechiffre_logo', 32x20px
   0x00, 0x3e, 0x20, 0x20, 0x00, 0x18, 0x2c, 0xa8, 0x80, 0x00, 0x1c, 0x22, 0x22, 0x00, 0x3e, 0x08,
0x30, 0x00, 0x34, 0x00, 0x3c, 0x0a, 0x00, 0xbc, 0x8a, 0x00, 0x38, 0x08, 0x00, 0x18, 0x2c, 0x28,
0x00, 0xb6, 0xb6, 0x00, 0xdb, 0xdb, 0x00, 0x6d, 0x6d, 0x00, 0xdb, 0xdb, 0x00, 0xdb, 0xdb, 0x00,
0x00, 0xdb, 0xdb, 0x00, 0xdb, 0xdb, 0x00, 0x6d, 0x6d, 0x00, 0xdb, 0xdb, 0x00, 0xb6, 0xb6, 0x00,
0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x06, 0x06, 0x06, 0x00, 0x06, 0x06, 0x06, 0x06, 0x06, 0x00,
0x00, 0x06, 0x06, 0x06, 0x06, 0x06, 0x00, 0x06, 0x06, 0x06, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00
};

  oled_write_raw_P(lechiffre_logo, sizeof(lechiffre_logo));
}

static void render_layer_status(void) {
    oled_write_P(PSTR("-----"), false);
    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_ln_P(PSTR("BASE"), false);
            break;
        case _LOWER
            oled_write_ln_P(PSTR("LOWR"), false);
            break;
        case _RAISE:
            oled_write_ln_P(PSTR("RISE"), false);
            break;
        case _ADJUST:
            oled_write_ln_P(PSTR("ADJT"), false);
            break;
        default:
            oled_write_ln_P(PSTR("?????"), false);
    }
}

#    define KEYLOG_LEN 11
char     keylog_str[KEYLOG_LEN] = {};
uint8_t  keylogs_str_idx        = 0;
uint16_t log_timer              = 0;

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void add_keylog(uint16_t keycode) {
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
        keycode = keycode & 0xFF;
    }

    for (uint8_t i = KEYLOG_LEN - 1; i > 0; i--) {
        keylog_str[i] = keylog_str[i - 1];
    }
    if (keycode < 60) {
        keylog_str[0] = code_to_name[keycode];
    }
    keylog_str[KEYLOG_LEN - 1] = 0;

    log_timer = timer_read();
}

void update_log(void) {
    if (timer_elapsed(log_timer) > 750) {
        add_keylog(0);
    }
}

//Text only renders
void render_keylogger_status(void) {
    oled_write_P(PSTR("-----"), false);
    oled_write(keylog_str, false);
}

void render_keylock_status(led_t led_state) {
    oled_write_P(PSTR("-----"), false);
    oled_write_P(PSTR("C"), led_state.caps_lock);
	oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("N"), led_state.num_lock);
	oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("S"), led_state.scroll_lock);
    //oled_write_ln_P(PSTR(" "), false);
}

void render_mod_status(uint8_t modifiers) {
       oled_write_P(PSTR("-----"), false);
    oled_write_ln_P(PSTR("SHFT"), (modifiers & MOD_MASK_SHIFT));
    oled_write_ln_P(PSTR("ALT"), (modifiers & MOD_MASK_ALT));
    oled_write_ln_P(PSTR("CTRL"), (modifiers & MOD_MASK_CTRL));
    oled_write_ln_P(PSTR("GUI"), (modifiers & MOD_MASK_GUI));
}

void oled_task_user(void) {
    render_lechiffre_logo();
    oled_set_cursor(0,3);
    render_layer_status();	// Renders the current keyboard state (layer, lock, caps, scroll, etc)
	render_mod_status(get_mods()|get_oneshot_mods());
	render_keylock_status(host_keyboard_led_state());
	render_keylogger_status();
}

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

#ifdef OLED_DRIVER_ENABLE  //Special thanks to Sickbabies for this great OLED widget!
  if (record->event.pressed) {
    add_keylog(keycode);
  }
#endif

  if (record->event.pressed) {
    switch (keycode) {
      case KC_USR_CMD_TAB:
        SEND_STRING(SS_RGUI(SS_TAP(X_TAB)));
        break;
      case KC_USR_CMD_SHIFT_TAB:
        SEND_STRING(SS_RGUI(SS_LSFT(SS_TAP(X_TAB))));
        break;
    }
  }

  return true;
}
