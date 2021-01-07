#include <assert.h>

#include "evaluator.h"
#include "tokens.h"

#define ASSERT_END assert(ctx.idx == ctx.tokens_length)

struct evaluator_context ctx;

void test_expression(enum token* tokens, token_index_t tokens_length, evaluator_t expected_result) {
    ctx.idx = 0;
    ctx.tokens = tokens;
    ctx.tokens_length = tokens_length;

    evaluator_t result;
    assert(evaluator_expression(&ctx, &result) == EVALUATOR_STATUS_OK);
    assert(result == expected_result);
    ASSERT_END;
}

int main(void) {
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
    test_expression(
        (enum token[]){
            TOKEN_6
        }, 1,
        6
    );


    // Test integer evaluation
    test_expression(
        (enum token[]){
            TOKEN_1, TOKEN_0, TOKEN_2
        }, 3,
        102
    );
    

    // Test expression evaluation
    test_expression(
        (enum token[]){
            TOKEN_1, TOKEN_PLUS, TOKEN_2, TOKEN_MULTIPLY, TOKEN_2
        }, 5,
        5
    );

    test_expression(
        (enum token[]){
            TOKEN_LPAREN, TOKEN_1, TOKEN_PLUS, TOKEN_2, TOKEN_RPAREN, TOKEN_MULTIPLY, TOKEN_2
        }, 7,
        6
    );
}
