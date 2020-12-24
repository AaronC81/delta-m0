#include <assert.h>

#include "evaluator.h"
#include "tokens.h"

#define ASSERT_END assert(ctx.idx == ctx.tokens_length)

int main(void) {
    struct evaluator_context ctx;


    // Test accept
    ctx.idx = 0;
    ctx.tokens = (enum token[]){ TOKEN_1 };
    ctx.tokens_length = 1;
    assert(evaluator_accept(&ctx, TOKEN_0) == false);
    assert(evaluator_accept(&ctx, TOKEN_1) == true);
    assert(ctx.idx == 1);


    // Test expect
    ctx.idx = 0;
    ctx.tokens = (enum token[]){ TOKEN_1 };
    ctx.tokens_length = 1;
    assert(evaluator_expect(&ctx, TOKEN_0) == EVALUATOR_STATUS_SYNTAX_ERROR);
    assert(evaluator_expect(&ctx, TOKEN_1) == EVALUATOR_STATUS_OK);
    ASSERT_END;


    // Test digit accept
    ctx.idx = 0;
    ctx.tokens = (enum token[]){ TOKEN_1 };
    ctx.tokens_length = 1;
    {
        uint8_t digit;
        assert(evaluator_accept_digit(&ctx, &digit) == true);
        assert(digit == 1);
        ASSERT_END;
    }


    // Test integer evaluation
    ctx.idx = 0;
    ctx.tokens = (enum token[]){ TOKEN_1, TOKEN_0, TOKEN_2 };
    ctx.tokens_length = 3;
    {
        evaluator_t result;
        assert(evaluator_integer(&ctx, &result) == EVALUATOR_STATUS_OK);
        assert(result == 102);
        ASSERT_END;
    }


    // Test expression evaluation
    ctx.idx = 0;
    ctx.tokens = (enum token[]){ TOKEN_1, TOKEN_PLUS, TOKEN_2, TOKEN_MULTIPLY, TOKEN_2 };
    ctx.tokens_length = 5;
    {
        evaluator_t result;
        assert(evaluator_expression(&ctx, &result) == EVALUATOR_STATUS_OK);
        assert(result == 5);
        ASSERT_END;
    }

    ctx.idx = 0;
    ctx.tokens = (enum token[]){ TOKEN_LPAREN, TOKEN_1, TOKEN_PLUS, TOKEN_2, TOKEN_RPAREN, TOKEN_MULTIPLY, TOKEN_2 };
    ctx.tokens_length = 7;
    {
        evaluator_t result;
        assert(evaluator_expression(&ctx, &result) == EVALUATOR_STATUS_OK);
        assert(result == 6);
        ASSERT_END;
    }
}
