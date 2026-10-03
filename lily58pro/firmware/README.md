# Lily58 firmware builds

Each version folder holds the `.uf2` and an OLED preview of **that same build** (rendered by running its `oled.c` in a PC simulator).

| Version | Date | Changes | Firmware | Preview |
|---------|------|---------|----------|---------|
| [v2](v2/) | 2026-10-03 | Left OLED text at 2× (WPM + graph on top, layer name + CAPS below); WPM removed from the right screen; OLEDs dimmed (contrast 24, lower pre-charge/VCOMH) and left screen drifts 1–2 px every 5 min against burn-in | [`.uf2`](v2/lily58_r2g_lily58pro_promicro_rp2040.uf2) | [gif](v2/oled_preview.gif) |
| [v1](v1/) | 2026-10-03 | Corne-parity layout (L1/L2); OLED: WPM/graph/layer chips on the left, Clawd animation on the right (no WPM); OLEDs dimmed and left screen drifts 1–2 px every 5 min against burn-in | [`.uf2`](v1/lily58_r2g_lily58pro_promicro_rp2040.uf2) | [gif](v1/oled_preview.gif) |

New build → add a `vN/` folder with both files and a row at the top of this table.
