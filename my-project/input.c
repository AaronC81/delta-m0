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
    if (input_tokens_length > 0) {
        for (token_index_t i = input_tokens_length - 1; i >= input_tokens_cursor; i--) {
            input_tokens[i + 1] = input_tokens[i];
        }
    }

    // Insert new token
    input_tokens[input_tokens_cursor] = tk;
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

uint8_t input_last_cursor_x = 0;

// TODO: will have to rewrite this to make it much better at some point
// It doesn't scroll and smears for non-end insertions
// For now, just clear the screen each time in main.c
void input_redraw_tokens(uint8_t x, uint8_t page) {
    const uint8_t padding = 3; // Space between bitmaps

    // Remove last cursor
    uint8_t not_cursor[] = { 1, 2, 0, 0 };
    ssd1306_draw_bitmap(not_cursor, input_last_cursor_x, page);
    
    for (token_index_t i = 0; i < input_tokens_length; i++) {
        // Get the bitmap
        uint8_t *bitmap = token_bitmaps[input_tokens[i]];
        uint8_t bitmap_width = bitmap[0];

        // Draw it
        ssd1306_draw_bitmap(bitmap, x, page);

        // TODO: make cursor better
        uint8_t cursor[] = { 1, 2, 0xFF, 0xFF };

        // Is this the first token and the cursor is before it?
        // If so, draw a line
        if (i == 0 && input_tokens_cursor == 0) {
            input_last_cursor_x = x - 1;
            ssd1306_draw_bitmap(cursor, input_last_cursor_x, page);
        }

        // Is the cursor before the next token (i.e. after this one)?
        // If so, draw a line
        if (input_tokens_cursor == i + 1) {
            input_last_cursor_x = x + bitmap_width + 1;
            ssd1306_draw_bitmap(cursor, input_last_cursor_x, page);
        }

        // Move on
        x += bitmap_width + padding;
    }
}
