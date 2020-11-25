#include "key_mapping.h"

#include "input.h"
#include "tokens.h"

void key_mapping_action(uint8_t row, uint8_t col) {
    switch (row) {
    case 0:
        // TODO: this will be (SHIFT < > MENU) but need to implement shift first
        switch (col) {
        case 0:
            input_insert(TOKEN_LPAREN);
            return;
        case 3:
            input_insert(TOKEN_RPAREN);
            return;
        }
        return;
    case 1:
        switch (col) {
        case 3:
            input_insert(TOKEN_PLUS);
            return;
        }
        return;
    case 2:
        switch (col) {
        case 3:
            input_insert(TOKEN_DOT);
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
        }
        return;
    case 4:
        switch (col) {
        case 0:
            input_insert(TOKEN_0);
            return;
        }
        return;
    }
}
