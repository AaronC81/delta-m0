#include "input.h"
#include "tokens.h"

#include "ssd1306.h"

enum token input_tokens[INPUT_TOKEN_LIMIT] = { 0 };

// Change these sizes if INPUT_TOKEN_LIMIT goes over their max
token_index_t input_tokens_cursor = 0; // The token which your cursor is BEFORE
token_index_t input_tokens_length = 0;

void input_cursor_left(void) {
    if (input_tokens_cursor == 0) {
        // Wrap to the end
        input_tokens_cursor = input_tokens_length;
    } else {
        input_tokens_cursor--;
    }
}

void input_cursor_right(void) {
    if (input_tokens_cursor >= input_tokens_length) {
        // Wrap to the start
        input_tokens_cursor = 0;
    } else {
        input_tokens_cursor++;
    }
}

bool input_insert(enum token tk) {
    if (input_tokens_length == INPUT_TOKEN_LIMIT) {
        return false;
    }

    // Move everything one forwards
    for (token_index_t i = input_tokens_cursor; i < input_tokens_length; i++) {
        input_tokens[i + 1] = input_tokens[i];
    }

    // Insert new token
    input_tokens[input_tokens_length] = tk;
    input_tokens_length++;
    input_tokens_cursor++;

    return true;
}

void input_delete(void) {
    // Move everything one back (overwrites current item)
    for (token_index_t i = input_tokens_cursor; i < input_tokens_length; i++) {
        input_tokens[i] = input_tokens[i + 1];
    }

    input_tokens_length--;
}

void input_redraw_tokens(uint8_t x, uint8_t page) {
    const uint8_t padding = 3; // Space between bitmaps
    
    for (token_index_t i = 0; i < input_tokens_length; i++) {
        // Get the bitmap
        uint8_t *bitmap = token_bitmaps[input_tokens[i]];

        // Draw it
        ssd1306_draw_bitmap(bitmap, x, page);

        // Move on
        x += bitmap[0] + padding;
    }
}
