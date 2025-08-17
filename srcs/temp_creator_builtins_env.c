#include "../includes/minishell.h"

// 1. env (basic usage)
t_pipeline *test_env_basic()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[1];
    tokens[0] = create_token("env", TOKEN_COMMAND);

    link_tokens(tokens, 1);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 2. env with argument (should ignore)
t_pipeline *test_env_with_arg()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[2];
    tokens[0] = create_token("env", TOKEN_COMMAND);
    tokens[1] = create_token("ignored_arg", TOKEN_ARGUMENT);

    link_tokens(tokens, 2);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 3. env > output.txt (redirection)
t_pipeline *test_env_redirect_output()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[3];
    tokens[0] = create_token("env", TOKEN_COMMAND);
    tokens[1] = create_token(">", TOKEN_REDIRECT_OUT);
    tokens[2] = create_token("env_output.txt", TOKEN_FILE);

    link_tokens(tokens, 3);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 4. env >> append.txt (append redirection)
t_pipeline *test_env_append()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[3];
    tokens[0] = create_token("env", TOKEN_COMMAND);
    tokens[1] = create_token(">>", TOKEN_APPEND);
    tokens[2] = create_token("env_append.txt", TOKEN_FILE);

    link_tokens(tokens, 3);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 5. env | head (pipeline test - future)
t_pipeline *test_env_pipe()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 2;
    pipeline->token_lists = malloc(2 * sizeof(t_token*));

    // First command: env
    t_token *tokens1[1];
    tokens1[0] = create_token("env", TOKEN_COMMAND);
    link_tokens(tokens1, 1);
    pipeline->token_lists[0] = tokens1[0];

    // Second command: head
    t_token *tokens2[1];
    tokens2[0] = create_token("head", TOKEN_COMMAND);
    link_tokens(tokens2, 1);
    pipeline->token_lists[1] = tokens2[0];

    return pipeline;
}