/*
 * Corne v4.1 — corne_emi keymap
 * Layout restored 1:1 from layout.vil backup
 *
 * Copyright 2019 @foostan / Copyright 2020 Drashna Jaelre <@drashna>
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * LAYOUT_split_3x6_3_ex2 argument order:
 *   LR0: [0,0..6]              RR0: [4,6] [4,5] [4,4] [4,3] [4,2] [4,1] [4,0]
 *   LR1: [1,0..6]              RR1: [5,6] [5,5] [5,4] [5,3] [5,2] [5,1] [5,0]
 *   LR2: [2,0..5]              RR2: [6,5] [6,4] [6,3] [6,2] [6,1] [6,0]
 *   LTH: [3,3][3,4][3,5]       RTH: [7,5] [7,4] [7,3]
 */

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* ─────────────────────────────────────────────────────────────────────────
   * Layer 0 — Base QWERTY
   * ─────────────────────────────────────────────────────────────────────────
   * ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┐   ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┐
   * │ ESC  │  Q   │  W   │  E   │  R   │  T   │ PGUP │   │ PGDN │  Y   │  U   │  I   │  O   │  P   │ BSPC │
   * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤   ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
   * │ TAB  │  A   │  S   │  D   │  F   │  G   │  [   │   │  ]   │  H   │  J   │  K   │  L   │  ;   │  '   │
   * ├──────┼──────┼──────┼──────┼──────┼──────┘       └──┼──────┼──────┼──────┼──────┼──────┼──────┤
   * │ LSFT │  Z   │  X   │  C   │  V   │  B   │           │  N   │  M   │  ,   │  .   │  /   │ ENT  │
   * └──────┴──────┴──────┼──────┼──────┼──────┤           ├──────┼──────┼──────┼──────┴──────┴──────┘
   *                       │ LGUI │ MO1  │ SPC  │           │ RALT │ MO2  │ RCTL │
   *                       └──────┴──────┴──────┘           └──────┴──────┴──────┘
   */
  [0] = LAYOUT_split_3x6_3_ex2(
    KC_ESC,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_PGUP,
    KC_PGDN,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_TAB,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_LBRC,
    KC_RBRC,  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
              KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
    KC_LGUI,  MO(1),   KC_SPC,
    KC_RALT,  MO(2),   KC_RCTL
  ),

  /* ─────────────────────────────────────────────────────────────────────────
   * Layer 1 — Numbers / Navigation  (left thumb hold)
   * ─────────────────────────────────────────────────────────────────────────
   * ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┐   ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┐
   * │  `   │  1   │  2   │  3   │  4   │  5   │ LCTL │   │ RCTL │  6   │  7   │  8   │  9   │  0   │ BSPC │
   * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤   ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
   * │ PGUP │  6   │  7   │  8   │  9   │  0   │ LALT │   │ RALT │ LEFT │ DOWN │  UP  │ RGHT │  `   │  =   │
   * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┘   └──────┼──────┼──────┼──────┼──────┼──────┼──────┤
   * │ PGDN │  Z   │  X   │ LEFT │ RGHT │  M   │                 │  [   │  ]   │  ,   │  .   │  \   │  -   │
   * └──────┴──────┴──────┼──────┼──────┼──────┤                 ├──────┼──────┼──────┼──────┴──────┴──────┘
   *                       │ LGUI │ MO1  │ SPC  │                 │ ENT  │ MO2  │ RCTL │
   *                       └──────┴──────┴──────┘                 └──────┴──────┴──────┘
   */
  [1] = LAYOUT_split_3x6_3_ex2(
    KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_LCTL,
    KC_RCTL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_PGUP,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_LALT,
    KC_RALT,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_GRV,  KC_EQL,
    KC_PGDN,  KC_Z,    KC_X,    KC_LEFT, KC_RGHT, KC_M,
              KC_LBRC, KC_RBRC, KC_COMM, KC_DOT,  KC_BSLS, KC_MINS,
    KC_LGUI,  MO(1),   KC_SPC,
    KC_ENT,   MO(2),   KC_RCTL
  ),

  /* ─────────────────────────────────────────────────────────────────────────
   * Layer 2 — Function / Mouse nav  (right thumb hold)
   * ─────────────────────────────────────────────────────────────────────────
   * ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┐   ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┐
   * │ TRNS │  F1  │  F2  │  F3  │  F4  │  F5  │ F11  │   │ F12  │  F6  │  F7  │  F8  │  F9  │ F10  │ PSCR │
   * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤   ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
   * │ CAPS │ LEFT │ DOWN │  UP  │ RGHT │ TRNS │ TRNS │   │ TRNS │ TRNS │  U   │ LEFT │  I   │ F11  │  DEL │
   * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┘   └──────┼──────┼──────┼──────┼──────┼──────┼──────┤
   * │ TG3  │ TRNS │ BSPC │ TRNS │ TRNS │ SLEP │                 │ F12  │  J   │ RGHT │  K   │ END  │ HOME │
   * └──────┴──────┴──────┼──────┼──────┼──────┤                 ├──────┼──────┼──────┼──────┴──────┴──────┘
   *                       │ A(LC)│C(RA) │ MO0  │                 │ ENT  │ TRNS │ TRNS │
   *                       └──────┴──────┴──────┘                 └──────┴──────┴──────┘
   */
  [2] = LAYOUT_split_3x6_3_ex2(
    KC_TRNS,        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F11,
    KC_F12,         KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_PSCR,
    KC_CAPS,        KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_TRNS, KC_TRNS,
    KC_TRNS,        KC_TRNS, KC_U,    KC_LEFT, KC_I,    KC_F11,  KC_DEL,
    TG(3),          KC_TRNS, KC_BSPC, KC_TRNS, KC_TRNS, KC_SLEP,
                    KC_F12,  KC_J,    KC_RGHT, KC_K,    KC_END,  KC_HOME,
    LALT(KC_LCTL),  RCTL(KC_RALT), MO(0),
    KC_ENT,         KC_TRNS, KC_TRNS
  ),

  /* ─────────────────────────────────────────────────────────────────────────
   * Layer 3 — RGB / Boot  (toggle from layer 2)
   * ─────────────────────────────────────────────────────────────────────────
   */
  [3] = LAYOUT_split_3x6_3_ex2(
    QK_BOOT,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    RM_TOGG,  RM_HUEU, RM_SATU, RM_VALU, KC_NO,   KC_NO,   KC_A,
    KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    RM_NEXT,  RM_HUED, RM_SATD, RM_VALD, KC_NO,   KC_NO,
              KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_LGUI,  KC_TRNS, KC_SPC,
    KC_ENT,   KC_TRNS, KC_RGUI
  ),

  /* ─────────────────────────────────────────────────────────────────────────
   * Layers 4 & 5 — Transparent (empty, ready to use)
   * ─────────────────────────────────────────────────────────────────────────
   */
  [4] = LAYOUT_split_3x6_3_ex2(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS
  ),

  [5] = LAYOUT_split_3x6_3_ex2(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS
  ),
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT) },
    [1] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT) },
    [2] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT) },
    [3] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT) },
    [4] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT) },
    [5] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT) },
};
#endif
