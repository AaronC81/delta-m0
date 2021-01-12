#pragma once

#include "tokens.h"
#include <stdbool.h>

// TODO: bad bad bad bad
//       In a *calculator* of all things, we don't want binary inaccuracies
//       Implement a better format later on!
#define evaluator_t double

enum evaluator_status {
    EVALUATOR_STATUS_OK = 0,
    EVALUATOR_STATUS_SYNTAX_ERROR,
};

struct evaluator_postfix_item {
    bool is_operator;
    union {
        evaluator_t number;
        enum token operator;
    } value;
};

enum evaluator_status evaluator_shunt(
    enum token *tokens, token_index_t tokens_length,
    struct evaluator_postfix_item *output, token_index_t *output_length
);