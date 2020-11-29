#pragma once

#include "tokens.h"
#include <stdbool.h>

// TODO: bad bad bad bad
//       In a *calculator* of all things, we don't want binary inaccuracies
//       Implement a better format later on!
#define evaluator_t double

struct evaluator_context {
    enum token *tokens;
    token_index_t tokens_length;
    token_index_t idx;
};

enum evaluator_status {
    EVALUATOR_STATUS_OK = 0,
    EVALUATOR_STATUS_SYNTAX_ERROR,
};

#define EVALUATOR_STATUS_PROP(x) if ((__evaluator_status_temp = (x)) != EVALUATOR_STATUS_OK) { return __evaluator_status_temp; }

bool evaluator_peek(struct evaluator_context *ctx, enum token what);
bool evaluator_accept(struct evaluator_context *ctx, enum token what);
bool evaluator_accept_digit(struct evaluator_context *ctx, uint8_t *digit);
enum evaluator_status evaluator_expect(struct evaluator_context *ctx, enum token what);

enum evaluator_status evaluator_integer(struct evaluator_context *ctx, evaluator_t *result);

enum evaluator_status evaluator_expression(struct evaluator_context *ctx, evaluator_t *result);
enum evaluator_status evaluator_add_sub_cascade(struct evaluator_context *ctx, evaluator_t *result);
enum evaluator_status evaluator_mul_div_cascade(struct evaluator_context *ctx, evaluator_t *result);
enum evaluator_status evaluator_brackets_cascade(struct evaluator_context *ctx, evaluator_t *result);
enum evaluator_status evaluator_number_cascade(struct evaluator_context *ctx, evaluator_t *result);
