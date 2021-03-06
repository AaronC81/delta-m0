#include "key_mapping.h"

#include "input.h"
#include "tokens.h"

bool key_shift = false;

#define KEY_HANDLE(_normal, _shift) \
    if (key_shift) { \
        _shift; \
        key_shift = false; \
    } else { \
        _normal; \
    }

void key_mapping_action(uint8_t row, uint8_t col) {
    switch (row) {
    case 0:
        // TODO: this will be (SHIFT < > MENU) but need to implement shift first
        switch (col) {
        case 0:
            key_shift = !key_shift;
            return;
        case 1:
            KEY_HANDLE(input_cursor_left(), input_insert(TOKEN_LPAREN));
            return;
        case 2:
            KEY_HANDLE(input_cursor_right(), input_insert(TOKEN_RPAREN));
            return;
        case 3:
            return;
        }
        return;
    case 1:
        switch (col) {
        case 0:
            input_insert(TOKEN_7);
            return;
        case 1:
            input_insert(TOKEN_8);
            return;
        case 2:
            input_insert(TOKEN_9);
            return;
        case 3:
            input_insert(TOKEN_PLUS);
            return;
        }
        return;
    case 2:
        switch (col) {
        case 0:
            input_insert(TOKEN_4);
            return;
        case 1:
            input_insert(TOKEN_5);
            return;
        case 2:
            input_insert(TOKEN_6);
            return;
        case 3:
            input_insert(TOKEN_SUBTRACT);
            return;
        }
        return;
    case 3:
        switch (col) {
        case 0:
            input_insert(TOKEN_1);
            return;
        case 1:
            input_insert(TOKEN_2);
            return;
        case 2:
            input_insert(TOKEN_3);
            return;
        case 3:
            input_insert(TOKEN_MULTIPLY);
            return;
        }
        return;
    case 4:
        switch (col) {
        case 0:
            input_insert(TOKEN_0);
            return;
        case 2:
            KEY_HANDLE(input_delete(), input_clear());
            return;
        case 3:
            input_insert(TOKEN_DIVIDE);
            return;
        }
        return;
    }
}
