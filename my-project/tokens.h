#pragma once

#include <stdint.h>
#include "assets/graphics.h"

enum token {
    TOKEN_NONE = 0,
    TOKEN_0 = 1,
    TOKEN_1 = 2,
    TOKEN_2 = 3,
} __attribute__((__packed__));

// Make sure the token enum is nice and small
_Static_assert(sizeof(enum token) == 1, "token enum is too large");

#define TOKEN_BITMAPS_LENGTH 3

extern const uint8_t *token_bitmaps[TOKEN_BITMAPS_LENGTH];
