#pragma once

#include <stdint.h>
#include "assets/graphics.h"

enum token {
    TOKEN_NONE = 0,
    TOKEN_0 = 1,
    TOKEN_1 = 2,
    TOKEN_2 = 3,
    TOKEN_3 = 4,
    TOKEN_4 = 5,
    TOKEN_5 = 6,
    TOKEN_6 = 7,
    TOKEN_7 = 8,
    TOKEN_8 = 9,
    TOKEN_9 = 10,
    TOKEN_LPAREN = 11,
    TOKEN_RPAREN = 12,
    TOKEN_PLUS = 13,
    TOKEN_DOT = 14,
} __attribute__((__packed__));

// Type large enough to index into token array + 1
#define token_index_t uint8_t

// Make sure the token enum is nice and small
_Static_assert(sizeof(enum token) == 1, "token enum is too large");

#define TOKEN_BITMAPS_LENGTH 15

extern const uint8_t *token_bitmaps[TOKEN_BITMAPS_LENGTH];
