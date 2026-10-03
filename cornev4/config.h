// Copyright 2024 corne_emi keymap
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// ============================================================
// VIAL CONFIGURATION
// ============================================================

// Unique keyboard ID for vial.rocks (taken from official crkbd vial keymap)
#define VIAL_KEYBOARD_UID {0x3B, 0x6B, 0xA0, 0x29, 0x80, 0x56, 0xED, 0xD1}

// Unlock combo: hold Q (left half) + P (right half) simultaneously
// Unlock combo: Q (left half [0,1]) + P (right half [4,1]) held simultaneously
#define VIAL_UNLOCK_COMBO_ROWS {0, 4}
#define VIAL_UNLOCK_COMBO_COLS {1, 1}

// Match the 6 layers from the user's saved .vil backup
#define DYNAMIC_KEYMAP_LAYER_COUNT 6

// ============================================================
// ANTI-EMI CONFIGURATION — Corne v4.1 (RP2040)
// ============================================================
// rev4_1 hardware: direct-pin matrix (one GPIO per key, internal pull-ups),
// single-wire half-duplex split on GP12 (TRS or TRRS), VBUS sense on GP13.

// --- Debounce: sym_defer_pk (rules.mk) ---
// A change is reported only after the key is stable for 8 ms (default 5),
// filtering short EMI glitches per key without delaying other keys.
#define DEBOUNCE 8

// --- Split serial: lower baud rate for better noise immunity ---
// QMK default is 230400. 115200 doubles the bit period, so a noise spike
// is less likely to flip a bit; split traffic is tiny, latency is unaffected.
#define SERIAL_USART_SPEED 115200

// --- Split watchdog (enabled in info.json) ---
// Boot-time guard: if the slave gets no ping from the master within 3 s
// after power-up, it resets itself and retries the handshake.
// Master/slave detection uses the hardware VBUS pin (GP13); do NOT define
// SPLIT_USB_DETECT, which would replace it with a slower USB-enumeration poll.
#define SPLIT_WATCHDOG_TIMEOUT 3000

// --- RGB: fewer LED updates = less self-generated switching noise ---
// LEDs are the main internal noise source. Flush at most every 33 ms
// (~30 fps, default 16 ms ~60 fps). Max brightness stays at the vial-qmk
// crkbd default (120/255); lower RGB_MATRIX_MAXIMUM_BRIGHTNESS to cut more noise.
#define RGB_MATRIX_LED_FLUSH_LIMIT 33
