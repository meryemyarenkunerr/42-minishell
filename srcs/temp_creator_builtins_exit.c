#include "../includes/minishell.h"

// 1. exit (no argument)
t_pipeline *test_exit_no_arg()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[1];
    tokens[0] = create_token("exit", TOKEN_COMMAND);

    link_tokens(tokens, 1);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 2. exit 0
t_pipeline *test_exit_zero()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[2];
    tokens[0] = create_token("exit", TOKEN_COMMAND);
    tokens[1] = create_token("0", TOKEN_ARGUMENT);

    link_tokens(tokens, 2);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 3. exit 42
t_pipeline *test_exit_forty_two()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[2];
    tokens[0] = create_token("exit", TOKEN_COMMAND);
    tokens[1] = create_token("42", TOKEN_ARGUMENT);

    link_tokens(tokens, 2);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 4. exit 256 (modulo test)
t_pipeline *test_exit_modulo()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[2];
    tokens[0] = create_token("exit", TOKEN_COMMAND);
    tokens[1] = create_token("256", TOKEN_ARGUMENT);

    link_tokens(tokens, 2);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 5. exit -1 (negative number)
t_pipeline *test_exit_negative()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[2];
    tokens[0] = create_token("exit", TOKEN_COMMAND);
    tokens[1] = create_token("-1", TOKEN_ARGUMENT);

    link_tokens(tokens, 2);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 6. exit abc (invalid argument)
t_pipeline *test_exit_invalid()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[2];
    tokens[0] = create_token("exit", TOKEN_COMMAND);
    tokens[1] = create_token("abc", TOKEN_ARGUMENT);

    link_tokens(tokens, 2);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 7. exit 1 2 (too many arguments)
t_pipeline *test_exit_too_many_args()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[3];
    tokens[0] = create_token("exit", TOKEN_COMMAND);
    tokens[1] = create_token("1", TOKEN_ARGUMENT);
    tokens[2] = create_token("2", TOKEN_ARGUMENT);

    link_tokens(tokens, 3);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 8. exit +42 (positive sign)
t_pipeline *test_exit_positive_sign()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[2];
    tokens[0] = create_token("exit", TOKEN_COMMAND);
    tokens[1] = create_token("+42", TOKEN_ARGUMENT);

    link_tokens(tokens, 2);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 9. exit 123abc (partially invalid)
t_pipeline *test_exit_partial_invalid()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[2];
    tokens[0] = create_token("exit", TOKEN_COMMAND);
    tokens[1] = create_token("123abc", TOKEN_ARGUMENT);

    link_tokens(tokens, 2);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}