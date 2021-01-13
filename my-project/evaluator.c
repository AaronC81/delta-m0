#include "evaluator.h"

// So this is definitely the worst way of creating a data structure in C
// But whatever! It works
#define STACK_LENGTH(_stack) (_stack##_length)
#define STACK_PUSH(_stack, _value) { _stack[_stack##_length] = (_value); _stack##_length++; }
#define STACK_POP(_stack) (_stack##_length--, _stack[_stack##_length])
#define STACK_PEEK(_stack) (_stack[_stack##_length - 1])

#define OUTPUT_LAST (output[*output_length - 1])
#define OUTPUT_PUSH(value) { output[*output_length] = (value); (*output_length)++; }
#define OUTPUT_PUSH_OPERATOR(op) OUTPUT_PUSH(((struct evaluator_postfix_item){ \
        .is_operator = true, .value = { .operator = op } \
    }))
#define OUTPUT_PUSH_NUMBER(num) OUTPUT_PUSH(((struct evaluator_postfix_item){ \
        .is_operator = false, .value = { .number = num } \
    }))

// Adapted from algorithm at:
//   https://en.wikipedia.org/wiki/Shunting-yard_algorithm
enum evaluator_status evaluator_shunt(
    enum token *tokens, token_index_t tokens_length,
    struct evaluator_postfix_item *output, token_index_t *output_length
) {
    // Set up pointers and data structures
    token_index_t tokens_index = 0;

    *output_length = 0;

    enum token operator_stack[TOKEN_LIMIT];
    token_index_t operator_stack_length = 0;

    bool last_was_digit = false;

    // Iterate over tokens
    while (tokens_index < tokens_length) {
        enum token this_token = tokens[tokens_index];
        bool this_was_digit = false;

        // If this token is a digit...
        if (this_token >= TOKEN_0 && this_token <= TOKEN_9) {
            // Get the numeric value of this digit
            evaluator_t value = this_token - TOKEN_0;

            // Is the previous value in the output also a digit?
            // (If there exists a previous value)
            if (last_was_digit) {
                // If so, add this digit to continue that numeric literal
                OUTPUT_LAST.value.number *= 10;
                OUTPUT_LAST.value.number += value;
            } else {
                // Otherwise, just push it straight on
                OUTPUT_PUSH_NUMBER(value);
            }

            this_was_digit = true;
        }
        // Or, if this token is a left paren...
        else if (this_token == TOKEN_LPAREN) {
            // Push it onto the stack
            STACK_PUSH(operator_stack, TOKEN_LPAREN);
        }
        // Or, if this token is a right paren...
        else if (this_token == TOKEN_RPAREN) {
            // Pop the operator stack until we empty it or encounter left paren
            while (STACK_LENGTH(operator_stack) > 0) {
                enum token popped_token = STACK_POP(operator_stack);
                if (popped_token == TOKEN_LPAREN) {
                    goto matching_paren_found;
                } else {
                    OUTPUT_PUSH_OPERATOR(popped_token);
                }
            }

            // We emptied the stack and didn't find a matching bracket, that's a
            // syntax error
            return EVALUATOR_STATUS_SYNTAX_ERROR;

            matching_paren_found:;
        }
        // Or, if this token is an operator
        else if (token_is_operator(this_token)) {
            // While...
            while (
                // ...there's a token at the top of the operator stack...
                STACK_LENGTH(operator_stack) > 0
                && token_is_operator(STACK_PEEK(operator_stack)) 
                // ...and the stack token has at least the precedence of the
                // one in the input...
                // (NOTE: shortcut because all implemented ops are left-assoc)
                && token_operator_precedence(STACK_PEEK(operator_stack))
                    >= token_operator_precedence(this_token)
                // ...and the stack token isn't an lparen
                && STACK_PEEK(operator_stack) != TOKEN_LPAREN
            ) {
                // Push the token onto the operator stack
                OUTPUT_PUSH_OPERATOR(STACK_POP(operator_stack));
            }

            STACK_PUSH(operator_stack, this_token);
        }
        
        tokens_index++;
        last_was_digit = this_was_digit;
    }

    // Empty the operator stack
    while (STACK_LENGTH(operator_stack) > 0) {
        OUTPUT_PUSH_OPERATOR(STACK_POP(operator_stack));
    }

    return EVALUATOR_STATUS_OK;
}

enum evaluator_status evaluator_evaluate(
    struct evaluator_postfix_item *items, token_index_t items_length,
    evaluator_t *result
) {
    // Special case: no items is 0
    if (items_length == 0) {
        *result = 0;
        return;
    }

    // Set up everything
    evaluator_t stack[TOKEN_LIMIT];
    token_index_t stack_length = 0;

    token_index_t items_index = 0;

    // Iterate over tokens
    while (items_index < items_length) {
        struct evaluator_postfix_item this_item = items[items_index];

        // If this is a number, push it onto the stack
        if (!this_item.is_operator) {
            STACK_PUSH(stack, this_item.value.number);
        }
        // Otherwise, it's an operator, deal with that
        else {
            evaluator_t a, b;

            switch (this_item.value.operator) {
            case TOKEN_PLUS:
                a = STACK_POP(stack);
                b = STACK_POP(stack);
                STACK_PUSH(stack, b + a);
                break;
            case TOKEN_SUBTRACT:
                a = STACK_POP(stack);
                b = STACK_POP(stack);
                STACK_PUSH(stack, b - a);
                break;
            case TOKEN_MULTIPLY:
                a = STACK_POP(stack);
                b = STACK_POP(stack);
                STACK_PUSH(stack, b * a);
                break;
            case TOKEN_DIVIDE:
                a = STACK_POP(stack);
                b = STACK_POP(stack);
                STACK_PUSH(stack, b / a);
                break;
            default:
                return EVALUATOR_STATUS_SYNTAX_ERROR;
            }
        }

        items_index++;
    }

    // There should only be one item left on the stack
    if (STACK_LENGTH(stack) != 1) {
        return EVALUATOR_STATUS_SYNTAX_ERROR;
    }

    // The result is the only remaining item
    *result = STACK_POP(stack);
    return EVALUATOR_STATUS_OK;
}
