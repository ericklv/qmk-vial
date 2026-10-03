 /* Copyright 2020 Naoki Katahira
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

enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
  _MO4,
  _MO5
};

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY (base)
 *
 * ┌──────┬──────┬──────┬──────┬──────┬──────┐                 ┌──────┬──────┬──────┬──────┬──────┬──────┐
 * │ ESC  │  1   │  2   │  3   │  4   │  5   │                 │  6   │  7   │  8   │  9   │  0   │ BSPC │
 * ├──────┼──────┼──────┼──────┼──────┼──────┤                 ├──────┼──────┼──────┼──────┼──────┼──────┤
 * │ CAPS │  Q   │  W   │  E   │  R   │  T   │                 │  Y   │  U   │  I   │  O   │  P   │  -   │
 * ├──────┼──────┼──────┼──────┼──────┼──────┤                 ├──────┼──────┼──────┼──────┼──────┼──────┤
 * │ TAB  │  A   │  S   │  D   │  F   │  G   │                 │  H   │  J   │  K   │  L   │  ;   │  '   │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┐   ┌──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │ LSFT │  Z   │  X   │  C   │  V   │  B   │  [   │   │  ]   │  N   │  M   │  ,   │  .   │  /   │ ENT  │
 * └──────┴──────┴──────┼──────┼──────┼──────┼──────┤   ├──────┼──────┼──────┼──────┼──────┴──────┴──────┘
 *                      │ LGUI │ MO1  │ PGDN │ SPC  │   │ RALT │ PGUP │ MO2  │ RCTL │
 *                      └──────┴──────┴──────┴──────┘   └──────┴──────┴──────┴──────┘
 */
[_QWERTY] = LAYOUT(
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_CAPS, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
  KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LBRC, KC_RBRC, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
                             KC_LGUI, LOWER,   KC_PGDN, KC_SPC,  KC_RALT, KC_PGUP, RAISE,   KC_RCTL
),

/* LOWER — Numbers / Navigation (hold MO1)
 *
 * ┌──────┬──────┬──────┬──────┬──────┬──────┐                 ┌──────┬──────┬──────┬──────┬──────┬──────┐
 * │  `   │  !   │  @   │  #   │  $   │  %   │                 │  ^   │  &   │  *   │  (   │  )   │ BSPC │
 * ├──────┼──────┼──────┼──────┼──────┼──────┤                 ├──────┼──────┼──────┼──────┼──────┼──────┤
 * │  `   │  1   │  2   │  3   │  4   │  5   │                 │  6   │  7   │  8   │  9   │  0   │ BSPC │
 * ├──────┼──────┼──────┼──────┼──────┼──────┤                 ├──────┼──────┼──────┼──────┼──────┼──────┤
 * │ PGUP │  6   │  7   │  8   │  9   │  0   │                 │ LEFT │ DOWN │  UP  │ RGHT │  `   │  =   │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┐   ┌──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │ PGDN │  Z   │  X   │ LEFT │ RGHT │  M   │ LALT │   │ RALT │  [   │  ]   │  ,   │  .   │  \   │  -   │
 * └──────┴──────┴──────┼──────┼──────┼──────┼──────┤   ├──────┼──────┼──────┼──────┼──────┴──────┴──────┘
 *                      │  ▽   │  ▽   │ LCTL │  ▽   │   │ ENT  │ RCTL │  ▽   │  ▽   │
 *                      └──────┴──────┴──────┴──────┘   └──────┴──────┴──────┴──────┘
 */
[_LOWER] = LAYOUT(
  KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_PGUP, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,                      KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_GRV,  KC_EQL,
  KC_PGDN, KC_Z,    KC_X,    KC_LEFT, KC_RGHT, KC_M,    KC_LALT, KC_RALT, KC_LBRC, KC_RBRC, KC_COMM, KC_DOT,  KC_BSLS, KC_MINS,
                             _______, _______, KC_LCTL, _______, KC_ENT,  KC_RCTL, _______, _______
),

/* RAISE — Function / Nav (hold MO2)
 *
 * ┌──────┬──────┬──────┬──────┬──────┬──────┐                 ┌──────┬──────┬──────┬──────┬──────┬──────┐
 * │  ▽   │  ▽   │  ▽   │  ▽   │  ▽   │  ▽   │                 │  ▽   │  ▽   │  ▽   │  ▽   │  ▽   │  ▽   │
 * ├──────┼──────┼──────┼──────┼──────┼──────┤                 ├──────┼──────┼──────┼──────┼──────┼──────┤
 * │  ▽   │  F1  │  F2  │  F3  │  F4  │  F5  │                 │  F6  │  F7  │  F8  │  F9  │ F10  │ PSCR │
 * ├──────┼──────┼──────┼──────┼──────┼──────┤                 ├──────┼──────┼──────┼──────┼──────┼──────┤
 * │ CAPS │ LEFT │ DOWN │  UP  │ RGHT │  ▽   │                 │ HOME │ PGDN │ PGUP │ END  │ F11  │ DEL  │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┐   ┌──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │ TG3  │  ▽   │ BSPC │  ▽   │  ▽   │ SLEP │  ▽   │   │  ▽   │ F12  │ MUTE │ VOLD │ VOLU │ MPLY │  ▽   │
 * └──────┴──────┴──────┼──────┼──────┼──────┼──────┤   ├──────┼──────┼──────┼──────┼──────┴──────┴──────┘
 *                      │ C+A  │ C+RA │ F11  │  ▽   │   │ ENT  │ F12  │  ▽   │  ▽   │
 *                      └──────┴──────┴──────┴──────┘   └──────┴──────┴──────┴──────┘
 */
[_RAISE] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_PSCR,
  KC_CAPS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,                   KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_F11,  KC_DEL,
  TG(3),   _______, KC_BSPC, _______, _______, KC_SLEP, _______, _______, KC_F12,  KC_MUTE, KC_VOLD, KC_VOLU, KC_MPLY, _______,
                             LALT(KC_LCTL), RCTL(KC_RALT), KC_F11, _______, KC_ENT,  KC_F12,  _______, _______
),

/* ADJUST — RGB / Media / Boot (MO1 + MO2, or TG3 from RAISE)
 *
 * ┌──────┬──────┬──────┬──────┬──────┬──────┐                 ┌──────┬──────┬──────┬──────┬──────┬──────┐
 * │ BOOT │      │      │      │      │      │                 │      │      │      │      │      │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┤                 ├──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │      │      │      │      │      │                 │      │      │      │      │      │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┤                 ├──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │      │ MPRV │ MPLY │ MNXT │ VOLU │                 │      │ RGB  │ MODE │ HUE+ │ SAT+ │ VAL+ │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┐   ┌──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │ TG3  │      │      │ MUTE │      │ VOLD │      │   │      │      │ SPD+ │ SPD- │ HUE- │ SAT- │ VAL- │
 * └──────┴──────┴──────┼──────┼──────┼──────┼──────┤   ├──────┼──────┼──────┼──────┼──────┴──────┴──────┘
 *                      │  ▽   │  ▽   │  ▽   │  ▽   │   │  ▽   │  ▽   │  ▽   │  ▽   │
 *                      └──────┴──────┴──────┴──────┘   └──────┴──────┴──────┴──────┘
 */
[_ADJUST] = LAYOUT(
  QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLU,                   XXXXXXX, RM_TOGG, RM_NEXT, RM_HUEU, RM_SATU, RM_VALU,
  TG(3),   XXXXXXX, XXXXXXX, KC_MUTE, XXXXXXX, KC_VOLD, XXXXXXX, XXXXXXX, XXXXXXX, RM_SPDU, RM_SPDD, RM_HUED, RM_SATD, RM_VALD,
                             _______, _______, _______, _______, _______, _______, _______, _______
),

/* MO4 — free
 */
[_MO4] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                             _______, _______, _______, _______, _______, _______, _______, _______
),

/* MO5 — free
 */
[_MO5] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                             _______, _______, _______, _______, _______, _______, _______, _______
)
};

// Tri-layer: hold LOWER + RAISE -> ADJUST
layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);
}

// OLED screens live in oled.c
