#include QMK_KEYBOARD_H

enum dz60_layers {
  _BL, // Base layer
  _FL, // Function layer
};

enum my_keycodes {
  BR_UP = SAFE_RANGE,
  BR_DOWN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* ,-----------------------------------------------------------------------------------------.
   * |  `  | 1   | 2   | 3   | 4   | 5   | 6   | 7   | 8   | 9   | 0   | -   | =   | Del | Bsp |
   * |-----------------------------------------------------------------------------------------+
   * | Tab    | Q   | W   | E   | R   | T   | Y   | U   | I   | O   | P   | [   | ]   |   \    |
   * |-----------------------------------------------------------------------------------------+
   * | Esc/_FL  | A   | S   | D   | F   | G   | H   | J   | K   | L   | ;   | '   | Enter      |
   * |-----------------------------------------------------------------------------------------+
   * | Shift     | Z   | X   | C   | V   | B   | N   | M   | ,   | .   | /   | PLAY| Up  |Shift|
   * |-----------------------------------------------------------------------------------------+
   * | Ctrl | Alt  | CMD  |             Space                 | CMD | Alt/_FL| Left| Down| Right|
   * `-----------------------------------------------------------------------------------------'
   */
  [_BL] = LAYOUT_2_shifts(
    KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_DEL, KC_BSPC,
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
    LT(_FL, KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
    KC_LSFT, KC_NO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_MEDIA_PLAY_PAUSE, KC_UP, KC_RSFT,
    KC_LCTL, KC_LALT, KC_LCMD, KC_NO, KC_SPC, KC_NO, KC_RCMD, MO(_FL), KC_LEFT, KC_DOWN, KC_RIGHT),


  /* ,-----------------------------------------------------------------------------------------.
   * |Sleep| F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 | F11 | F12 |  V- |  V+ |
   * |-----------------------------------------------------------------------------------------+
   * |        | BR- | BR+ |     |     |     |     |     |     |     |     | PREV | NEXT | PLAY |
   * |-----------------------------------------------------------------------------------------+
   * |          |     |     |     |     |     |      |    |     |     |     |     |            |
   * |-----------------------------------------------------------------------------------------+
   * |           |     |     |     |     |     |     |     |     |     |     |     | PgUp |    |
   * |-----------------------------------------------------------------------------------------+
   * | Reset|      |      |                                      |     |     | Home| PgDwn| End|
   * `-----------------------------------------------------------------------------------------'
   */
  [_FL] = LAYOUT_2_shifts(
    LCLS(KC_POWER), KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC__VOLDOWN, KC__VOLUP,
    _______, BR_DOWN, BR_UP, _______, _______, _______, _______, _______, _______, _______, _______, KC_MEDIA_PREV_TRACK, KC_MEDIA_NEXT_TRACK, KC_MEDIA_PLAY_PAUSE,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, KC_NO,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PGUP, _______,
    RESET, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_END),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  uint8_t key;
  switch (keycode) {
    case BR_DOWN:
    case BR_UP:
      // Clear the RGUI modifier placed by LM for _ML layer as brightness don't
      // work with modifiers.
      key = (keycode == BR_DOWN) ? KC_SLCK : KC_PAUS;
      if (record->event.pressed) {
          unregister_mods(MOD_RGUI);
          add_key(key);
          send_keyboard_report();
      } else {
          del_key(key);
          send_keyboard_report();
      }
      return false; // Skip all further processing of this key
    default:
      return true; // Process all other keycodes normally
  }
}
