/* Copyright 2021 StefanGrindelwald
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN1,
    _FN2
};

enum custom_keycodes {
	FFXIV = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
        KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                           KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
        KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                           KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_QUOT,
        MO(_FN1), KC_MINS,  KC_EQL,  KC_LEFT, KC_RGHT,                                                          KC_UP,   KC_DOWN, KC_LBRC, KC_RBRC, MO(_FN1),
                                                               KC_DEL, KC_END,    KC_LGUI, KC_RCTL,
                                                                        KC_HOME,    KC_PGUP,
                                                      KC_SPC, KC_LCTL,  KC_LALT,     KC_PGDN, KC_RSFT,  KC_SPC
    ),
    [_FN1] = LAYOUT(
        KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                                          KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_F11,  KC_F12,
        _______,  _______, _______, _______, _______, _______,                                        _______, _______, _______,  _______, _______, _______,
        _______,  _______, _______, _______, _______, _______,                                        _______, _______, _______,  _______, _______, _______,
        MO(_FN2), _______, _______, _______, _______, _______,                                        _______, _______, RGB_RMOD, RGB_MOD, RGB_TOG, MO(_FN2),
        _______,  _______, KC_MUTE, KC_VOLD, KC_VOLU,                                                          RGB_VAI, RGB_VAD,  RGB_SAI, RGB_SAD, _______,
                                                               _______, FFXIV,    _______, _______,
                                                                        CG_NORM,    RGB_HUI,
                                                      _______, _______, CG_SWAP,    RGB_HUD, _______, _______
    ),
    [_FN2] = LAYOUT(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                                          KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_F11,  KC_F12,
        _______, _______, _______, _______, _______, _______,                                        _______, _______, _______,  _______, _______, _______,
        _______, _______, _______, RESET,   _______, _______,                                        _______, _______, RESET,    _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                                        _______, _______, RGB_RMOD, RGB_MOD, RGB_TOG, _______,
        _______, _______, KC_MUTE, KC_VOLD, KC_VOLU,                                                          RGB_VAI, RGB_VAD,  RGB_SAI, RGB_SAD, _______,
                                                              _______, _______,    _______, _______,
                                                                       _______,    RGB_HUI,
                                                     _______, _______, _______,    RGB_HUD, _______, _______
    )

};

uint32_t ffxiv_delay = 600000;  // 10 minutes
bool ffxiv_active = false;
uint32_t ffxiv_timer = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case FFXIV:  // When you press custom FFXIV keycode
      if (record->event.pressed) {
        ffxiv_active = !ffxiv_active;  // Toggle ffxiv anti-afk
        ffxiv_timer = timer_read32(); // Reset anti-afk timer
      }
	  return false;
      break;
	default:
	  return true;
  }
}

void matrix_scan_user(void){
  if (ffxiv_active) {  
    // Check if it's been longer than the ffxiv_delay time
    if (timer_elapsed32(ffxiv_timer) > ffxiv_delay) {
      tap_code(KC_W);           // Send a W
	  ffxiv_delay = 600000 + (rand() % 180000); // reset the timer to between 10-13 minutes randomly.
      ffxiv_timer = timer_read32();  // Reset timer
    }
  }
}