#include "text.h"

#include "ssd1306.h"

// What 80-character line limit?
const uint8_t *text_h12_letters_lower[] = { graphics_font_h12_a, graphics_font_h12_b, graphics_font_h12_c, graphics_font_h12_d, graphics_font_h12_e, graphics_font_h12_f, graphics_font_h12_g, graphics_font_h12_h, graphics_font_h12_i, graphics_font_h12_j, graphics_font_h12_k, graphics_font_h12_l, graphics_font_h12_m, graphics_font_h12_n, graphics_font_h12_o, graphics_font_h12_p, graphics_font_h12_q, graphics_font_h12_r, graphics_font_h12_s, graphics_font_h12_t, graphics_font_h12_u, graphics_font_h12_v, graphics_font_h12_w, graphics_font_h12_x, graphics_font_h12_y, graphics_font_h12_z };
const uint8_t *text_h12_letters_upper[] = { graphics_font_h12_A, graphics_font_h12_B, graphics_font_h12_C, graphics_font_h12_D, graphics_font_h12_E, graphics_font_h12_F, graphics_font_h12_G, graphics_font_h12_H, graphics_font_h12_I, graphics_font_h12_J, graphics_font_h12_K, graphics_font_h12_L, graphics_font_h12_M, graphics_font_h12_N, graphics_font_h12_O, graphics_font_h12_P, graphics_font_h12_Q, graphics_font_h12_R, graphics_font_h12_S, graphics_font_h12_T, graphics_font_h12_U, graphics_font_h12_V, graphics_font_h12_W, graphics_font_h12_X, graphics_font_h12_Y, graphics_font_h12_Z };

const struct text_font text_font_h12 = {
    .lower = text_h12_letters_lower,
    .upper = text_h12_letters_upper,
    .numerals = 0,
    .symbols = (struct text_font_symbols){
        .comma = graphics_font_h12_comma,
        .space = graphics_font_h12_space,
    },
};

void text_write(struct text_font font, char *s, uint8_t x, uint8_t page) {
    uint8_t ptr = 0;
    while (s[ptr] != 0) {
        x += text_write_char(font, s[ptr], x, page);
        ptr++;
    }
}

uint8_t text_write_char(struct text_font font, char c, uint8_t x, uint8_t page) {
    uint8_t *bitmap = graphics_token_none;

    if (c >= 'A' && c <= 'Z') {
        // Uppercase letters
        bitmap = font.upper[c - 'A'];
    } else if (c >= 'a' && c <= 'z') {
        // Lowercase letters
        bitmap = font.lower[c - 'a'];
    } else if (c >= '0' && c <= '9') {
        // Numerals
        bitmap = font.numerals[c - '0'];
    } else {
        // Symbols, hopefully
        switch (c) {
        case ' ':
            bitmap = font.symbols.space;
            break;
        case ',':
            bitmap = font.symbols.comma;
            break;
        }
    }

    ssd1306_draw_bitmap(bitmap, x, page);
    return bitmap[0];
}
