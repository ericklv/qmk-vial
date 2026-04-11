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

On layer 1 the right thumb changes to: `ENTER │ MO(2) │ RGUI`

---

## Anti-EMI Optimizations

| Setting | Value | Effect |
|---------|-------|--------|
| `DEBOUNCE_TYPE` | `sym_defer_g` | Filters EMI pulses shorter than 8 ms |
| `DEBOUNCE` | `8` ms | Absorbs typical TRRS cable noise spikes |
| `SERIAL_USART_SPEED` | `460800` | Doubles bit period → more noise-immune |
| `SPLIT_USB_DETECT` | enabled | Prevents handedness confusion on boot |
| `SPLIT_WATCHDOG_TIMEOUT` | `3000` ms | Auto-resets if slave half freezes |
| `MATRIX_IO_DELAY` | `30` µs | Electrical settling after EMI events |
| `RGB_MATRIX_FRAMERATE` | `20` Hz | Reduces LED switching noise |

---

## Flashing the firmware (.uf2)

### Method 1 — Bootloader key combo (no physical button needed)

Hold the key while plugging in the USB cable to that half:

| Half to flash | Hold this key while connecting USB |
|---------------|-------------------------------------|
| **Left half** | **P** |
| **Right half** | **Q** |

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

> **VIAL security unlock:** if vial.rocks shows a lock icon, hold **Q + W** simultaneously until it unlocks. This is a VIAL feature to prevent accidental remapping — it is **not** related to flashing.

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
