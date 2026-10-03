# VIAL support — enables configuration from vial.rocks
VIA_ENABLE          = yes
VIAL_ENABLE         = yes
VIALRGB_ENABLE      = yes

# Anti-EMI: symmetric deferred per-key debounce
# Reports a change only after the key is stable for DEBOUNCE ms; per key,
# so noise on one key never delays the others (sym_defer_g is board-wide)
DEBOUNCE_TYPE = sym_defer_pk

# Encoder map support
ENCODER_MAP_ENABLE = yes
