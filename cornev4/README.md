# corne_emi — Corne v4.1 Keymap (Anti-EMI + VIAL)

Keymap personalizado para el **Corne v4.1 foostan** con controlador **RP2040**.

Incluye optimizaciones anti-EMI por software y soporte completo de [vial.rocks](https://vial.rocks).

## Layout

| Capa | Descripción |
|------|-------------|
| 0    | QWERTY base — ESC/PGUP/PGDN en extras |
| 1    | Números (1-0 en dos filas), símbolos, navegación |
| 2    | F1-F12, VIM nav (HJKL+UI), Home/End, screenshot |
| 3    | RGB (toggle desde L2 con TG3) + QK_BOOT |
| 4-5  | Transparentes — libres para personalizar |

### Thumbs
```
Izquierda:  LGUI │ MO(1) │ SPACE
Derecha:    RALT │ MO(2) │ RCTRL
```
En layer 1 el thumb derecho cambia a: `ENTER │ MO(2) │ RGUI`

## Optimizaciones Anti-EMI

| Parámetro | Valor | Efecto |
|-----------|-------|--------|
| `DEBOUNCE_TYPE` | `sym_defer_g` | Filtra pulsos EMI de < 8ms |
| `DEBOUNCE` | 8ms | Absorbe el pulso típico de cables TRRS |
| `SERIAL_USART_SPEED` | 460800 | Doble período de bit → más inmune a ruido |
| `SPLIT_USB_DETECT` | activado | Evita confusión de handedness por EMI en arranque |
| `SPLIT_WATCHDOG_TIMEOUT` | 3000ms | Auto-reset si la mitad esclava se congestiona |
| `MATRIX_IO_DELAY` | 30µs | Estabilización eléctrica tras eventos EMI |
| `RGB_MATRIX_FRAMERATE` | 20 Hz | Reduce switching noise de los LEDs |

## Compilar el firmware

### Requisitos previos

```bash
# 1. Instalar QMK CLI
python3 -m pip install --user qmk

# 2. Clonar el fork VIAL de QMK (necesario para soporte VIAL/vial.rocks)
git clone https://github.com/vial-kb/vial-qmk.git ~/qmk_firmware
cd ~/qmk_firmware
git submodule update --init --recursive

# 3. Configurar QMK para que use este directorio
qmk config user.qmk_home=~/qmk_firmware
```

### Instalar el keymap

```bash
# Copiar la carpeta del keymap al lugar correcto dentro de QMK
cp -r crkbd/keymaps/corne_emi ~/qmk_firmware/keyboards/crkbd/keymaps/
```

### Compilar

```bash
cd ~/qmk_firmware
qmk compile -kb crkbd/rev4_1/standard -km corne_emi
```

El archivo resultante se llamará:
```
crkbd_rev4_1_standard_corne_emi.uf2
```

### Flashear

1. Conectar la mitad **izquierda** al PC
2. Hacer **doble-click rápido** en el botón reset del RP2040
3. Aparecerá un disco USB llamado `RPI-RP2`
4. Arrastrar el `.uf2` al disco → se flashea y reinicia solo
5. Repetir con la mitad **derecha**

### Configurar desde vial.rocks

1. Abrir [https://vial.rocks](https://vial.rocks) en Chrome o Edge
2. Conectar el teclado
3. Pulsar "Authorize device" → seleccionar "Corne v4.1"
4. Para desbloquear edición: mantener **Q + W** mientras conectas
