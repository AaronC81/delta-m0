#pragma once

#include <stdint.h>
#include "assets/graphics.h"

struct text_font_symbols {
    const uint8_t *space;
    const uint8_t *comma;
};

struct text_font {
    const uint8_t **lower;
    const uint8_t **upper;
    const uint8_t **numerals;
    const struct text_font_symbols symbols; 
};

extern const struct text_font text_font_h12;

void text_write(struct text_font font, char *s, uint8_t x, uint8_t page);
uint8_t text_write_char(struct text_font font, char c, uint8_t x, uint8_t page);
