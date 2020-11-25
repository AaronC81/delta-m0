#include "tokens.h"

#include <stddef.h>

const uint8_t *token_bitmaps[TOKEN_BITMAPS_LENGTH] = {
    graphics_token_none,
    graphics_token_0,
    graphics_token_1,
    graphics_token_2,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    graphics_token_lparen,
    graphics_token_rparen,
    graphics_token_plus,
    graphics_token_dot,
};
