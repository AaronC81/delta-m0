#pragma once

#include "tokens.h"

#include <stdbool.h>

#define INPUT_TOKEN_LIMIT 128

extern enum token input_tokens[INPUT_TOKEN_LIMIT];

// Type large enough to index into token array + 1
#define token_index_t uint8_t

void input_cursor_left(void);
void input_cursor_right(void);
bool input_insert(enum token tk); // Returns success of insertion
void input_delete(void);
void input_redraw_tokens(uint8_t x, uint8_t page);
