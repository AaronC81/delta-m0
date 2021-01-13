#pragma once

#include "tokens.h"

#include <stdbool.h>
#include "evaluator.h"

#define INPUT_ENTRY_PAGE 6

extern enum token input_tokens[TOKEN_LIMIT];

void input_cursor_left(void);
void input_cursor_right(void);
bool input_insert(enum token tk); // Returns success of insertion
void input_delete(void);
void input_clear_from_cursor(int8_t offset);
void input_redraw_tokens(uint8_t x, uint8_t page);
void input_evaluate(void);
void input_draw_evaluator_t(evaluator_t number, uint8_t x, uint8_t page);
void input_clear(void);
