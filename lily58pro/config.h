/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

/* VIAL UID for Lily58*/
#define VIAL_KEYBOARD_UID {0x7E, 0xFD, 0xFC, 0x5B, 0x7D, 0x39, 0x48, 0x06}

/* VIAL secure unlock keystroke - currently both big keys (typ. SPACE/ENTER) */
#define VIAL_UNLOCK_COMBO_ROWS {4, 9}
#define VIAL_UNLOCK_COMBO_COLS {4, 4}

/* Space reduction */

#define DYNAMIC_KEYMAP_LAYER_COUNT 6
#define VIAL_TAP_DANCE_ENTRIES 4
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
#define NO_ACTION_ONESHOT

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#define USE_SERIAL_PD2

#define TAPPING_FORCE_HOLD
#define TAPPING_TERM 100

#define TAPPING_TERM 100

// Dim the OLEDs to reduce burn-in. Contrast alone barely changes perceived
// brightness on SSD1306 panels, so also shorten pre-charge and lower VCOMH.
#define OLED_BRIGHTNESS 24        // contrast, 0-255 (QMK default 255)
#define OLED_PRE_CHARGE_PERIOD 0x22 // default 0xF1
#define OLED_VCOM_DETECT 0x00       // ~0.65 x Vcc, default 0x20

// Enable all 30+ RGB Matrix Effects
#define ENABLE_RGB_MATRIX_ANIMATIONS
#define ENABLE_RGB_MATRIX_KEYPRESS

// OLED: sync WPM so the right half can animate while typing,
// and sync activity so both screens sleep/wake together
#define SPLIT_WPM_ENABLE
#define SPLIT_ACTIVITY_ENABLE
