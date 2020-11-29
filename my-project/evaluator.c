#include "evaluator.h"

enum evaluator_status __evaluator_status_temp;

bool evaluator_peek(struct evaluator_context *ctx, enum token what) {
    return ctx->idx < ctx->tokens_length && ctx->tokens[ctx->idx] == what;
}

bool evaluator_accept(struct evaluator_context *ctx, enum token what) {
    if (evaluator_peek(ctx, what)) {
        ctx->idx++;
        return true;
    }
    return false;
}

bool evaluator_accept_digit(struct evaluator_context *ctx, uint8_t *digit) {
    for (uint8_t i = 0; i < 10; i++) {
        if (evaluator_accept(ctx, TOKEN_0 + i)) {
            *digit = i;
            return true;
        }
    }

    return false;
}

enum evaluator_status evaluator_expect(struct evaluator_context *ctx, enum token what) {
    if (evaluator_accept(ctx, what)) {
        return EVALUATOR_STATUS_OK;
    }
    return EVALUATOR_STATUS_SYNTAX_ERROR;
}

#include <stdio.h>

enum evaluator_status evaluator_integer(struct evaluator_context *ctx, evaluator_t *result) {
    uint8_t digit;
    
    // We need at least one digit
    if (!evaluator_accept_digit(ctx, &digit)) {
        return EVALUATOR_STATUS_SYNTAX_ERROR;
    }

    *result = digit;

    // Now deal with more digits
    while (evaluator_accept_digit(ctx, &digit)) {
        *result *= 10;
        *result += digit;
    }

    return EVALUATOR_STATUS_OK;
}

enum evaluator_status evaluator_expression(struct evaluator_context *ctx, evaluator_t *result) {
    return evaluator_add_sub_cascade(ctx, result);
}

enum evaluator_status evaluator_add_sub_cascade(struct evaluator_context *ctx, evaluator_t *result) {
    EVALUATOR_STATUS_PROP(evaluator_mul_div_cascade(ctx, result));

    // TODO: also handle minus
    if (evaluator_accept(ctx, TOKEN_PLUS)) {
        evaluator_t recurse_result;
        EVALUATOR_STATUS_PROP(evaluator_add_sub_cascade(ctx, &recurse_result));

        *result += recurse_result;
    }

    return EVALUATOR_STATUS_OK;
}

enum evaluator_status evaluator_mul_div_cascade(struct evaluator_context *ctx, evaluator_t *result) {
    EVALUATOR_STATUS_PROP(evaluator_brackets_cascade(ctx, result));

    // TODO: also handle divide
    if (evaluator_accept(ctx, TOKEN_DOT)) {
        evaluator_t recurse_result;
        EVALUATOR_STATUS_PROP(evaluator_mul_div_cascade(ctx, &recurse_result));

        *result *= recurse_result;
    }

    return EVALUATOR_STATUS_OK;
}

enum evaluator_status evaluator_brackets_cascade(struct evaluator_context *ctx, evaluator_t *result) {
    if (evaluator_accept(ctx, TOKEN_LPAREN)) {
        enum evaluator_status status = evaluator_expression(ctx, result);
        evaluator_expect(ctx, TOKEN_RPAREN);
        return status;
    } else {
        return evaluator_number_cascade(ctx, result);
    }
}

enum evaluator_status evaluator_number_cascade(struct evaluator_context *ctx, evaluator_t *result) {
    // TODO: decimals
    return evaluator_integer(ctx, result);
}
