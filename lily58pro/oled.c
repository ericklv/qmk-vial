// Lily58 Pro R2G — OLED screens (128x32)
//   Left  (master): WPM + history graph on top, active layer + caps below (2x text)
//   Right (slave):  Clawd, the Claude Code mascot — types on a laptop while
//                   you type, wanders around when idle, sleeps after a while
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#ifdef OLED_ENABLE

#define FRAME_MS 100   // animation tick (10 fps)
#define SLEEP_MS 15000 // no input for this long -> Clawd falls asleep

static uint32_t rng_state = 0x2545F491;

static uint8_t rnd(uint8_t n) {
    rng_state ^= rng_state << 13;
    rng_state ^= rng_state >> 17;
    rng_state ^= rng_state << 5;
    return rng_state % n;
}

static void fill_rect(int16_t x, int16_t y, uint8_t w, uint8_t h, bool on) {
    for (uint8_t j = 0; j < h; j++)
        for (uint8_t i = 0; i < w; i++)
            if (x + i >= 0 && x + i < 128 && y + j >= 0 && y + j < 32) oled_write_pixel(x + i, y + j, on);
}

// Draws a 1-bit bitmap where each row is a bitmask (MSB = leftmost of `w` columns), scaled by `s`
static void draw_bitmap(const uint16_t *rows, uint8_t h, uint8_t w, int16_t x, int16_t y, uint8_t s) {
    for (uint8_t r = 0; r < h; r++)
        for (uint8_t c = 0; c < w; c++)
            if (rows[r] & (1u << (w - 1 - c))) fill_rect(x + c * s, y + r * s, s, s, true);
}

// Text at any pixel position and integer scale, using the OLED's own 6x8 font
extern const unsigned char font[];

static void draw_text(int16_t x, int16_t y, const char *s, uint8_t scale, bool invert) {
    for (; *s; s++, x += 6 * scale)
        for (uint8_t c = 0; c < 6; c++) {
            uint8_t bits = pgm_read_byte(&font[(uint8_t)*s * 6 + c]);
            for (uint8_t r = 0; r < 8; r++) fill_rect(x + c * scale, y + r * scale, scale, scale, ((bits >> r) & 1) != invert);
        }
}

/* ─────────────────────────────── Left: WPM + layer ─────────────────────────────── */

#define WPM_SAMPLES 21   // 2 px per sample, right of the WPM readout
#define WPM_GRAPH_X 84
#define WPM_SAMPLE_MS 500
#define WPM_MAX 120

// Burn-in guard: the whole left screen drifts by a pixel every few minutes
#define SHIFT_MS 300000
static const int8_t shift_xy[][2] = {{0, 0}, {1, 0}, {2, 0}, {2, 1}, {1, 1}, {0, 1}};

static uint8_t  wpm_hist[WPM_SAMPLES];
static uint8_t  wpm_head;
static uint32_t wpm_timer;

static void render_master(void) {
    uint8_t wpm = get_current_wpm();

    if (timer_elapsed32(wpm_timer) > WPM_SAMPLE_MS) {
        wpm_timer           = timer_read32();
        wpm_hist[wpm_head]  = wpm;
        wpm_head            = (wpm_head + 1) % WPM_SAMPLES;
    }

    oled_clear();

    // Top half (2x): "WPM 087" + scrolling history graph, oldest on the left
    const int8_t *o  = shift_xy[(timer_read32() / SHIFT_MS) % (sizeof(shift_xy) / sizeof(shift_xy[0]))];
    int8_t        ox = o[0], oy = o[1];

    draw_text(ox, oy, "WPM", 2, false);
    draw_text(ox + 42, oy, get_u8_str(wpm, '0'), 2, false);
    for (uint8_t i = 0; i < WPM_SAMPLES; i++) {
        uint8_t v = wpm_hist[(wpm_head + i) % WPM_SAMPLES];
        uint8_t h = (v > WPM_MAX ? WPM_MAX : v) * 14 / WPM_MAX;
        if (v && !h) h = 1;
        fill_rect(ox + WPM_GRAPH_X + i * 2, oy + 15 - h, 1, h, true);
    }

    // Bottom half (2x): active layer name + caps indicator
    static const char *const names[] = {"BASE", "NUM", "FN", "ADJ"};
    uint8_t                  layer   = get_highest_layer(layer_state);
    draw_text(ox, oy + 16, layer < 4 ? names[layer] : "L?", 2, false);
    if (host_keyboard_led_state().caps_lock) {
        fill_rect(ox + 76, oy + 16, 50, 16, true);
        draw_text(ox + 78, oy + 16, "CAPS", 2, true);
    }
}

/* ─────────────────────────────── Right: Clawd ─────────────────────────────── */

// Clawd sprite in "units" (1 unit = 3 px): 14 cols x 8 rows -> 42 x 24 px
#define U 3
#define CLAWD_W 14
#define CLAWD_H 8
#define GROUND 31

// Body + arms (rows 0-5); legs (rows 6-7) are separate poses
static const uint16_t PROGMEM body_idle[6] = {
    0b00111111110000,
    0b00111111110000,
    0b11111111111100,
    0b11111111111100,
    0b00111111110000,
    0b00111111110000,
};
static const uint16_t PROGMEM body_type_a[6] = { // right hand down on the keys
    0b00111111110000,
    0b00111111110000,
    0b11111111110000,
    0b11111111111110,
    0b00111111110000,
    0b00111111110000,
};
static const uint16_t PROGMEM body_type_b[6] = { // right hand lifted
    0b00111111110000,
    0b00111111110000,
    0b11111111111110,
    0b11111111110000,
    0b00111111110000,
    0b00111111110000,
};
static const uint16_t PROGMEM legs_stand[2] = {0b00101001010000, 0b00101001010000};
static const uint16_t PROGMEM legs_walk_a[2] = {0b00101001010000, 0b00100001000000};
static const uint16_t PROGMEM legs_walk_b[2] = {0b00101001010000, 0b00001000010000};

// Claude Code spinner: · ✢ ✳ ✻ (7x7), played forwards then backwards
static const uint16_t PROGMEM spinner[4][7] = {
    {0, 0, 0, 0b0001000, 0, 0, 0},
    {0, 0b0001000, 0b0001000, 0b0110110, 0b0001000, 0b0001000, 0},
    {0, 0b0101010, 0b0011100, 0b0110110, 0b0011100, 0b0101010, 0},
    {0b1001001, 0b0101010, 0b0011100, 0b1110111, 0b0011100, 0b0101010, 0b1001001},
};
static const uint8_t spinner_seq[] = {0, 1, 2, 3, 3, 2, 1};

static const char PROGMEM verbs[][8] = {"Coding", "Typing", "Hacking", "Brewing", "Musing", "Vibing", "Cooking", "Booping"};

enum clawd_state { CLAWD_IDLE, CLAWD_WALK, CLAWD_TYPE, CLAWD_SLEEP };

static struct {
    uint8_t  state;
    int16_t  x, target;
    int8_t   look;     // eye offset in px: -1 left, 0 center, 1 right
    uint8_t  blink;    // frames left with eyes closed
    uint16_t wait;     // idle frames before next wander
    uint32_t tick;     // frame counter
    uint32_t timer;
} clawd = {.state = CLAWD_IDLE, .x = 4, .wait = 20};

static void copy_rows(uint16_t *dst, const uint16_t *src, uint8_t n) {
    for (uint8_t i = 0; i < n; i++) dst[i] = pgm_read_word(&src[i]);
}

// Eyes are holes punched in the body at unit columns 3 and 8, row 1
static void draw_eyes(int16_t x, int16_t y, int8_t look, bool closed) {
    for (uint8_t e = 0; e < 2; e++) {
        int16_t ex = x + (e ? 8 : 3) * U + look;
        if (closed)
            fill_rect(ex, y + U + 2, U, 1, false);
        else
            fill_rect(ex, y + U, U, U, false);
    }
}

static void draw_clawd(int16_t x, const uint16_t *body_P, const uint16_t *legs_P, int8_t bob, bool eyes_closed) {
    uint16_t rows[CLAWD_H];
    copy_rows(rows, body_P, 6);
    copy_rows(rows + 6, legs_P, 2);
    int16_t y = GROUND + 1 - CLAWD_H * U + bob;
    draw_bitmap(rows, CLAWD_H, CLAWD_W, x, y, U);
    draw_eyes(x, y, clawd.look, eyes_closed);
}

// Front-facing laptop: screen with scrolling "code", keyboard base under Clawd's hand
static void draw_laptop(int16_t x) {
    const int16_t sy = 6, sw = 24, sh = 15;
    // screen frame
    fill_rect(x, sy, sw, 1, true);
    fill_rect(x, sy + sh - 1, sw, 1, true);
    fill_rect(x, sy, 1, sh, true);
    fill_rect(x + sw - 1, sy, 1, sh, true);
    // code lines: lengths scroll up every few frames
    static const uint8_t code[] = {12, 7, 15, 9, 4, 13, 10, 6, 16, 8, 11, 5};
    uint8_t              off    = (clawd.tick / 3) % sizeof(code);
    for (uint8_t l = 0; l < 5; l++) {
        uint8_t len    = code[(off + l) % sizeof(code)];
        uint8_t indent = ((off + l) % 3) * 2;
        fill_rect(x + 3 + indent, sy + 2 + l * 2, len, 1, true);
    }
    // cursor blink on the last line
    if ((clawd.tick / 4) % 2) fill_rect(x + 3 + 16, sy + 10, 2, 2, true);
    // keyboard base
    fill_rect(x - 3, sy + sh, sw + 6, 2, true);
    fill_rect(x - 1, sy + sh + 2, sw + 2, 1, true);
}

static void draw_spinner_text(void) {
    uint16_t rows[7];
    uint8_t  f = spinner_seq[(clawd.tick / 2) % sizeof(spinner_seq)];
    copy_rows(rows, spinner[f], 7);
    draw_bitmap(rows, 7, 7, 76, 12, 1);
    draw_text(86, 12, verbs[(clawd.tick / 40) % (sizeof(verbs) / sizeof(verbs[0]))], 1, false);
}

static void draw_zzz(int16_t x) {
    // three z's (small -> big) drifting up, staggered; beside Clawd on whichever side has room
    bool right = x + CLAWD_W * U + 26 <= 128;
    for (uint8_t i = 0; i < 3; i++) {
        uint8_t phase = (clawd.tick / 2 + i * 7) % 21;
        uint8_t s     = 4 + i;
        int16_t zx    = right ? x + CLAWD_W * U - 4 + i * 8 + phase / 3 : x + 4 - s - i * 8 - phase / 3;
        int16_t zy    = 24 - s - phase;
        if (zy < 0) continue;
        fill_rect(zx, zy, s, 1, true);
        for (uint8_t k = 1; k < s - 1; k++) fill_rect(zx + s - 1 - k, zy + k, 1, 1, true);
        fill_rect(zx, zy + s - 1, s, 1, true);
    }
}

static void update_clawd(void) {
    bool typing = get_current_wpm() > 0;
    bool asleep = last_input_activity_elapsed() > SLEEP_MS;

    if (typing) {
        clawd.state = clawd.x > 4 ? CLAWD_WALK : CLAWD_TYPE;
        clawd.target = 4;
    } else if (asleep) {
        clawd.state = CLAWD_SLEEP;
    } else if (clawd.state == CLAWD_TYPE || clawd.state == CLAWD_SLEEP) {
        clawd.state = CLAWD_IDLE;
        clawd.wait  = 30;
    }

    switch (clawd.state) {
        case CLAWD_IDLE:
            if (!clawd.blink && !rnd(25)) clawd.blink = 2;
            if (!rnd(30)) clawd.look = (int8_t)rnd(3) - 1;
            if (clawd.wait) {
                clawd.wait--;
            } else {
                clawd.target = 4 + rnd(128 - CLAWD_W * U - 8);
                clawd.state  = CLAWD_WALK;
            }
            break;
        case CLAWD_WALK: {
            int8_t dir = clawd.target > clawd.x ? 1 : -1;
            uint8_t step = typing ? 4 : 2;
            clawd.look = dir;
            if ((clawd.target - clawd.x) * dir <= step) {
                clawd.x     = clawd.target;
                clawd.state = typing ? CLAWD_TYPE : CLAWD_IDLE;
                clawd.wait  = 20 + rnd(40);
                clawd.look  = 0;
            } else {
                clawd.x += dir * step;
            }
            break;
        }
        case CLAWD_TYPE:
            clawd.look = 1; // eyes on the screen
            break;
        default:
            break;
    }
    if (clawd.blink) clawd.blink--;
}

static void render_slave(void) {
    if (timer_elapsed32(clawd.timer) < FRAME_MS) return;
    clawd.timer = timer_read32();
    clawd.tick++;
    update_clawd();

    oled_clear();
    switch (clawd.state) {
        case CLAWD_TYPE: {
            // hand speed follows WPM: faster typing -> faster taps
            uint8_t wpm    = get_current_wpm();
            uint8_t period = wpm > 80 ? 1 : wpm > 40 ? 2 : 3;
            bool    down   = (clawd.tick / period) % 2;
            draw_clawd(clawd.x, down ? body_type_a : body_type_b, legs_stand, 0, clawd.blink);
            draw_laptop(clawd.x + CLAWD_W * U - 2);
            draw_spinner_text();
            break;
        }
        case CLAWD_WALK: {
            bool a = (clawd.tick / 2) % 2;
            draw_clawd(clawd.x, body_idle, a ? legs_walk_a : legs_walk_b, a ? 0 : -1, false);
            break;
        }
        case CLAWD_SLEEP:
            // crouched: legs hidden, eyes closed, slow breathing
            draw_clawd(clawd.x, body_idle, legs_stand, 2 * U + ((clawd.tick / 10) % 2), true);
            draw_zzz(clawd.x);
            break;
        default:
            draw_clawd(clawd.x, body_idle, legs_stand, 0, clawd.blink);
            break;
    }
}

/* ─────────────────────────────── Hooks ─────────────────────────────── */

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) return OLED_ROTATION_180; // flips the display 180 degrees if offhand
    return rotation;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_master();
    } else {
        render_slave();
    }
    return false; // skip the stock r2g screens
}

#endif // OLED_ENABLE
