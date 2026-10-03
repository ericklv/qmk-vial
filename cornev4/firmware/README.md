# Corne v4.1 firmware builds

| Version | Date | Changes | Firmware |
|---------|------|---------|----------|
| [v2](v2/) | 2026-10-03 | Layout from `corne-wired/layout.vil` (L1/L2). Anti-EMI review: split serial 115200 baud (was 460800, QMK default 230400); hardware VBUS master detection (dropped `SPLIT_USB_DETECT`); per-key debounce `sym_defer_pk` 8 ms; RGB flush limit 33 ms (~30 fps); removed no-op/redundant defines (`RGB_MATRIX_FRAMERATE`, `MATRIX_IO_DELAY`, `PICO_XOSC_STARTUP_DELAY_MULTIPLIER`). RGB defaults left stock | [`.uf2`](v2/crkbd_rev4_1_standard_cornev4.uf2) |
| [v1](v1/) | 2026-10-02 | Initial anti-EMI keymap (previous layout) | [`.uf2`](v1/crkbd_rev4_1_standard_cornev4.uf2) |

New build → add a `vN/` folder and a row at the top of this table.
