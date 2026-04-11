# qmk-vial

Configuraciones de firmware QMK/VIAL para mis teclados mecánicos.

Compatibles con [vial.rocks](https://vial.rocks) — configuración en el navegador, sin instalar nada.

## Teclados

| Carpeta | Teclado | Controlador | Notas |
|---------|---------|-------------|-------|
| [`cornev4/`](cornev4/) | Corne v4.1 foostan | RP2040 | Anti-EMI + VIAL + 6 layers |
| [`lily58pro/`](lily58pro/) | Lily58 Pro R2G | RP2040 | VIAL + RGB completo |

---

## Setup inicial (solo la primera vez)

### 1. Instalar QMK CLI

```bash
python3 -m pip install --user qmk
```

### 2. Clonar vial-qmk (fork con soporte VIAL)

```bash
git clone https://github.com/vial-kb/vial-qmk.git ~/qmk_firmware
cd ~/qmk_firmware
git submodule update --init --recursive
qmk config user.qmk_home=~/qmk_firmware
```

### 3. Clonar este repo y copiar los keymaps

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

## Compilar

### Corne v4.1

```bash
cd ~/qmk_firmware
qmk compile -kb crkbd/rev4_1/standard -km cornev4
# Resultado: crkbd_rev4_1_standard_cornev4.uf2
```

### Lily58 Pro R2G

```bash
cd ~/qmk_firmware
qmk compile -kb lily58/r2g -km lily58pro -e CONVERT_TO=promicro_rp2040
# Resultado: lily58_r2g_lily58pro_promicro_rp2040.uf2
```

---

## Flashear (ambos teclados, RP2040)

1. Doble-click rápido en el botón **RESET** del teclado
2. Aparece un disco USB llamado **`RPI-RP2`**
3. Arrastrar el `.uf2` al disco → se flashea y reinicia solo
4. Repetir para la **otra mitad** (en teclados split)

---

## Configurar con VIAL (sin recompilar)

1. Abrir **[vial.rocks](https://vial.rocks)** en Chrome o Edge
2. Conectar el teclado y pulsar "Authorize device"
3. Para desbloquear edición:
   - **Corne**: mantener **Q + W** al conectar
   - **Lily58**: mantener las teclas de desbloqueo definidas en `config.h`

---

## Descripción de las capas — Corne v4.1

| Capa | Descripción |
|------|-------------|
| 0 | QWERTY base |
| 1 | Números + navegación (hold MO1) |
| 2 | F-keys + VIM nav (hold MO2) |
| 3 | RGB control + QK_BOOT (toggle desde L2) |
| 4-5 | Libres / transparentes |

### Optimizaciones Anti-EMI incluidas

- `DEBOUNCE_TYPE = sym_defer_g` — filtra pulsos de < 8ms
- `SERIAL_USART_SPEED = 460800` — más inmune a ruido en cable TRRS
- `SPLIT_WATCHDOG_TIMEOUT = 3000ms` — auto-reset si esclava se cuelga
- `RGB_MATRIX_FRAMERATE = 20Hz` — reduce switching noise de LEDs
