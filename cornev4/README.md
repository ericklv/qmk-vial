# Corne v4.1 — `cornev4` Keymap (Anti-EMI + VIAL)

Custom keymap for the **Corne v4.1 foostan** with **RP2040** controller.

Includes software anti-EMI optimizations and full [vial.rocks](https://vial.rocks) browser support.

---

## Layers

| Layer | Description |
|-------|-------------|
| 0 | QWERTY base — ESC/PGUP/PGDN on extra inner keys |
| 1 | Numbers (1–0 across two rows), symbols, arrow navigation |
| 2 | F1–F12, VIM-style nav (H/J/K/L + U/I), Home/End, screenshot |
| 3 | RGB control + `QK_BOOT` — toggle from Layer 2 with `TG(3)` |
| 4–5 | Transparent — free to customize via vial.rocks |

### Thumb cluster

```
Left:   LGUI │ MO(1) │ SPACE
Right:  RALT │ MO(2) │ RCTRL
```

On layer 1 the right thumb changes to: `ENTER │ MO(2) │ RCTRL`

---

## Anti-EMI Optimizations

rev4_1 hardware: direct-pin matrix (one GPIO per key, RP2040 internal pull-ups), single-wire half-duplex split on GP12 (TRS or TRRS), VBUS sense on GP13.

| Setting | Value | Effect |
|---------|-------|--------|
| `DEBOUNCE_TYPE` | `sym_defer_pk` | Per-key deferred debounce: a noisy key never delays the others |
| `DEBOUNCE` | `8` ms | Change reported only after 8 ms stable (default 5) |
| `SERIAL_USART_SPEED` | `115200` | Half the QMK default (230400) → 2× bit period, more noise-immune |
| Master detection | VBUS pin (GP13) | Hardware detection; `SPLIT_USB_DETECT` intentionally not defined |
| `SPLIT_WATCHDOG_TIMEOUT` | `3000` ms | Boot-time: slave resets if it gets no ping from the master within 3 s |
| `RGB_MATRIX_LED_FLUSH_LIMIT` | `33` ms | LED refresh ~30 fps (default ~60) → fewer LED data bursts |

- RGB max brightness: 120/255 (vial-qmk `crkbd` default). Lower `RGB_MATRIX_MAXIMUM_BRIGHTNESS` to cut more noise.
- Hardware: the single data wire carries all split traffic — use a short, shielded TRS/TRRS cable; never hot-plug it.

Versioned builds: [`firmware/`](firmware/).

---

## Flashing the firmware (.uf2)

### Method 1 — Bootloader key combo (no physical button needed)

Hold the key while plugging in the USB cable to that half (bootmagic — also resets EEPROM: Vial keymap/RGB revert to firmware defaults):

| Half to flash | Hold this key while connecting USB |
|---------------|-------------------------------------|
| **Left half** | **Q** |
| **Right half** | **P** |

The drive `RPI-RP2` will appear. Drag the `.uf2` onto it — done.

### Method 2 — `QK_BOOT` keycode (keyboard connected and working)

Go to **Layer 3** (hold MO2 from L2, then TG3) and press `QK_BOOT`.
The half will reboot into bootloader and `RPI-RP2` will appear.

### Method 3 — Physical reset button (if accessible on the PCB)

Double-click the RESET button on the RP2040 board quickly.

---

## Configure with vial.rocks (no compile needed)

1. Open **[vial.rocks](https://vial.rocks)** in Chrome or Edge
2. Click **"Connect"** — your browser shows a native WebHID device picker
3. Select your Corne from the list
4. Keymap editing is available immediately in the browser

> **VIAL security unlock:** if vial.rocks shows a lock icon, hold **Q + P** simultaneously until it unlocks. This is a VIAL feature to prevent accidental remapping — it is **not** related to flashing.

---

## Build from source

### Prerequisites

```bash
# Install QMK CLI
python3 -m pip install --user qmk

# Clone vial-qmk (required for vial.rocks support)
git clone https://github.com/vial-kb/vial-qmk.git ~/qmk_firmware
cd ~/qmk_firmware
git submodule update --init --recursive
qmk config user.qmk_home=~/qmk_firmware
```

### Install the keymap

```bash
mkdir -p ~/qmk_firmware/keyboards/crkbd/keymaps/cornev4
cp -r cornev4/* ~/qmk_firmware/keyboards/crkbd/keymaps/cornev4/
```

### Compile

```bash
cd ~/qmk_firmware
qmk compile -kb crkbd/rev4_1/standard -km cornev4
# Output: crkbd_rev4_1_standard_cornev4.uf2
```
