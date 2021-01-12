#include "input.h"
#include "tokens.h"

#include "ssd1306.h"

enum token input_tokens[TOKEN_LIMIT] = { 0 };

// Change these sizes if TOKEN_LIMIT goes over their max
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
    if (input_tokens_length == TOKEN_LIMIT) {
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
    // We can't delete if we're at the beginning
    if (input_tokens_cursor == 0) {
        return;
    }
    
    // Move everything one back (overwrites current item)
    for (token_index_t i = input_tokens_cursor; i < input_tokens_length; i++) {
        input_tokens[i] = input_tokens[i + 1];
    }

    input_tokens_cursor--;
    input_tokens_length--;
}

uint8_t input_last_cursor_x = 0;
const uint8_t input_digit_padding = 3; // Space between bitmaps

// TODO: will have to rewrite this to make it much better at some point
// It doesn't scroll and smears for non-end insertions
// For now, just clear the screen each time in main.c
void input_redraw_tokens(uint8_t x, uint8_t page) {

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
        x += bitmap_width + input_digit_padding;
    }
}

void input_evaluate(void) {
    // Shunt to postfix, and then evaluate if that was successful
    struct evaluator_postfix_item items[TOKEN_LIMIT];
    token_index_t items_length;
    enum evaluator_status status = evaluator_shunt(
        input_tokens, input_tokens_length, items, &items_length
    );
    
    evaluator_t result;
    if (status == EVALUATOR_STATUS_OK) {
        status = evaluator_evaluate(items, items_length, &result);
    }

    switch (status) {
    case EVALUATOR_STATUS_OK:
        input_draw_evaluator_t(result, 126, 2);
        break;
    case EVALUATOR_STATUS_SYNTAX_ERROR:
        ssd1306_draw_bitmap(graphics_syntax_error, 126 - graphics_syntax_error[0], 2);
        break;
    }
}

// This implementation will break if evaluator_t isn't double
_Static_assert(sizeof(evaluator_t) == sizeof(double), "expected evaluator_t to be double");
void input_draw_evaluator_t(evaluator_t number, uint8_t x, uint8_t page) {
    const uint8_t digit_width = token_bitmaps[TOKEN_0][0];

    bool negative = false;
    if (number < 0) {
        negative = true;
        number = -number;
    }
    
    // Print the whole part
    uint32_t whole = number / 1;
    while (whole > 0) {
        x -= digit_width + input_digit_padding;
        uint8_t digit = whole % 10;
        ssd1306_draw_bitmap(token_bitmaps[TOKEN_0 + digit], x, page);
        whole /= 10;
    }

    // Print negative sign if needed
    if (negative) {
        x -= token_bitmaps[TOKEN_SUBTRACT][0];
        ssd1306_draw_bitmap(token_bitmaps[TOKEN_SUBTRACT], x, page);
    }
}
