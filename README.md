# qmk-vial

Personal QMK/VIAL firmware configurations for my mechanical keyboards.

All keymaps are compatible with **[vial.rocks](https://vial.rocks)** — live keymap editing directly in the browser, no software install required.

## Keyboards

| Folder | Keyboard | Controller | Notes |
|--------|----------|------------|-------|
| [`cornev4/`](cornev4/) | Corne v4.1 (foostan) | RP2040 | Anti-EMI + VIAL + 6 layers |
| [`lily58pro/`](lily58pro/) | Lily58 Pro R2G | RP2040 | VIAL + 40+ RGB animations |

---

## First-time Setup

### 1. Install QMK CLI

```bash
python3 -m pip install --user qmk
```

### 2. Clone vial-qmk (VIAL fork of QMK)

```bash
git clone https://github.com/vial-kb/vial-qmk.git ~/qmk_firmware
cd ~/qmk_firmware
git submodule update --init --recursive
qmk config user.qmk_home=~/qmk_firmware
```

### 3. Clone this repo and copy the keymaps

```bash
git clone git@github.com:ericklv/qmk-vial.git ~/qmk-vial

# Corne v4.1
mkdir -p ~/qmk_firmware/keyboards/crkbd/keymaps/cornev4
cp -r ~/qmk-vial/cornev4/* ~/qmk_firmware/keyboards/crkbd/keymaps/cornev4/

# Lily58 Pro R2G
mkdir -p ~/qmk_firmware/keyboards/lily58/keymaps/lily58pro
cp -r ~/qmk-vial/lily58pro/* ~/qmk_firmware/keyboards/lily58/keymaps/lily58pro/
```

---

## Compile

### Corne v4.1

```bash
cd ~/qmk_firmware
qmk compile -kb crkbd/rev4_1/standard -km cornev4
# Output: crkbd_rev4_1_standard_cornev4.uf2
```

### Lily58 Pro R2G

```bash
cd ~/qmk_firmware
qmk compile -kb lily58/r2g -km lily58pro -e CONVERT_TO=promicro_rp2040
# Output: lily58_r2g_lily58pro_promicro_rp2040.uf2
```

---

## Flash (RP2040 — both keyboards)

1. Double-click the **RESET** button on the keyboard half
2. A USB drive named **`RPI-RP2`** will appear
3. Drag the `.uf2` file onto the drive — it flashes and reboots automatically
4. Repeat for the **other half**

> Pre-compiled `.uf2` files are included in each keyboard folder so you can flash immediately without building.

---

## Live Configuration with vial.rocks

1. Open **[vial.rocks](https://vial.rocks)** in **Chrome or Edge**
2. Click **"Connect"** — the browser shows a native WebHID device picker
3. Select your keyboard from the list
4. To unlock key remapping, hold the unlock combo (see each keyboard's `README.md`)

---

## Corne v4.1 — Layer Summary

| Layer | Description |
|-------|-------------|
| 0 | QWERTY base |
| 1 | Numbers + navigation (hold MO1) |
| 2 | F-keys + VIM nav (hold MO2) |
| 3 | RGB control + QK_BOOT (toggle from L2) |
| 4–5 | Free / transparent |
