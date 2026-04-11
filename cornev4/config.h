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

// --- Debounce: sym_defer_g filters fast electrical glitches ---
// Higher value = more noise rejection. Default is 5ms.
// At 8ms we absorb the typical EMI pulse window (~6ms on TRRS cables)
// without impacting perceived typing feel.
#define DEBOUNCE 8

// --- Split serial: limit USART baud rate for better noise immunity ---
// Default on RP2040 vendor driver is ~921600. Dropping to 460800
// doubles the bit-period, making it much harder for EMI to corrupt bits.
#define SERIAL_USART_SPEED 460800

// --- Split transport: detect USB side automatically ---
// Avoids handedness confusion caused by EMI on GP21 pin at startup.
#define SPLIT_USB_DETECT
#define SPLIT_USB_TIMEOUT 2000
#define SPLIT_USB_TIMEOUT_POLL 10

// --- Watchdog: already enabled in info.json, tune the timeout ---
// Must be greater than SPLIT_USB_TIMEOUT (2000ms).
// If the slave half goes silent for 3s, master triggers a reset.
// Prevents "frozen half" caused by burst EMI corrupting the sync packet.
#define SPLIT_WATCHDOG_TIMEOUT 3000

// --- Matrix scan: add a small delay for electrical settling ---
// Gives matrix lines time to stabilize after strong EMI events.
#define MATRIX_IO_DELAY 30

// --- RGB: reduce switching frequency to cut self-generated EMI ---
// RGB LEDs are the #1 source of internal EMI on the Corne.
// Lowering the framerate reduces the high-frequency switching noise
// that couples into the TRRS cable and corrupts split comms.
#define RGB_MATRIX_DEFAULT_SPD 80   // Slower animations = less switching
#undef  RGB_MATRIX_FRAMERATE
#define RGB_MATRIX_FRAMERATE 20     // 20 Hz instead of default 60 Hz

// --- RP2040 crystal: extra startup delay for noisy power rails ---
// Already set in rev4_1/config.h to 64; re-affirm here for clarity.
#define PICO_XOSC_STARTUP_DELAY_MULTIPLIER 64
