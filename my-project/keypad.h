#pragma once
/*
Controls the 4x5 keypad.
*/

#include <stdint.h>
#include <stdbool.h>

#define KEYPAD_ROWS 5
#define KEYPAD_COLS 4

void keypad_init(void);
void keypad_set_row(uint8_t row);
uint8_t keypad_read_cols(void);
bool keypad_get_pressed(uint8_t *row, uint8_t *col);
