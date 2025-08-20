#include "../includes/minishell.h"

// 1. echo (no arguments)
t_pipeline *test_echo_no_args()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[1];
    tokens[0] = create_token("echo", TOKEN_COMMAND);

    link_tokens(tokens, 1);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 2. echo hello
t_pipeline *test_echo_hello()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[2];
    tokens[0] = create_token("echo", TOKEN_COMMAND);
    tokens[1] = create_token("hello", TOKEN_ARGUMENT);

    link_tokens(tokens, 2);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 3. echo hello world
t_pipeline *test_echo_hello_world()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[3];
    tokens[0] = create_token("echo", TOKEN_COMMAND);
    tokens[1] = create_token("hello", TOKEN_ARGUMENT);
    tokens[2] = create_token("world", TOKEN_ARGUMENT);

    link_tokens(tokens, 3);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 4. echo -n hello
t_pipeline *test_echo_n_hello()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[3];
    tokens[0] = create_token("echo", TOKEN_COMMAND);
    tokens[1] = create_token("-n", TOKEN_ARGUMENT);
    tokens[2] = create_token("hello", TOKEN_ARGUMENT);

    link_tokens(tokens, 3);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 5. echo -nn hello
t_pipeline *test_echo_nn_hello()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[3];
    tokens[0] = create_token("echo", TOKEN_COMMAND);
    tokens[1] = create_token("-nn", TOKEN_ARGUMENT);
    tokens[2] = create_token("hello", TOKEN_ARGUMENT);

    link_tokens(tokens, 3);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 6. echo -nnn -nn hello
t_pipeline *test_echo_multiple_n_flags()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[4];
    tokens[0] = create_token("echo", TOKEN_COMMAND);
    tokens[1] = create_token("-nnn", TOKEN_ARGUMENT);
    tokens[2] = create_token("-nn", TOKEN_ARGUMENT);
    tokens[3] = create_token("hello", TOKEN_ARGUMENT);

    link_tokens(tokens, 4);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 7. echo -na hello (invalid flag)
t_pipeline *test_echo_invalid_flag()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[3];
    tokens[0] = create_token("echo", TOKEN_COMMAND);
    tokens[1] = create_token("-na", TOKEN_ARGUMENT);
    tokens[2] = create_token("hello", TOKEN_ARGUMENT);

    link_tokens(tokens, 3);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 8. echo hello -n world (flag not at beginning)
t_pipeline *test_echo_flag_middle()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[4];
    tokens[0] = create_token("echo", TOKEN_COMMAND);
    tokens[1] = create_token("hello", TOKEN_ARGUMENT);
    tokens[2] = create_token("-n", TOKEN_ARGUMENT);
    tokens[3] = create_token("world", TOKEN_ARGUMENT);

    link_tokens(tokens, 4);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 9. echo -n -nn -nnn hello world
t_pipeline *test_echo_consecutive_n_flags()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[6];
    tokens[0] = create_token("echo", TOKEN_COMMAND);
    tokens[1] = create_token("-n", TOKEN_ARGUMENT);
    tokens[2] = create_token("-nn", TOKEN_ARGUMENT);
    tokens[3] = create_token("-nnn", TOKEN_ARGUMENT);
    tokens[4] = create_token("hello", TOKEN_ARGUMENT);
    tokens[5] = create_token("world", TOKEN_ARGUMENT);

    link_tokens(tokens, 6);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 10. echo -nnn -na hello (valid then invalid)
t_pipeline *test_echo_valid_then_invalid_flag()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[4];
    tokens[0] = create_token("echo", TOKEN_COMMAND);
    tokens[1] = create_token("-nnn", TOKEN_ARGUMENT);
    tokens[2] = create_token("-na", TOKEN_ARGUMENT);
    tokens[3] = create_token("hello", TOKEN_ARGUMENT);

    link_tokens(tokens, 4);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 11. echo hello > output.txt (redirection)
t_pipeline *test_echo_redirect_output()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[4];
    tokens[0] = create_token("echo", TOKEN_COMMAND);
    tokens[1] = create_token("serhat", TOKEN_ARGUMENT);
    tokens[2] = create_token(">", TOKEN_REDIRECT_OUT);
    tokens[3] = create_token("yaren", TOKEN_FILE);

    link_tokens(tokens, 4);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}

// 12. echo -n hello >> append.txt (append + no newline)
t_pipeline *test_echo_n_append()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[5];
    tokens[0] = create_token("echo", TOKEN_COMMAND);
    tokens[1] = create_token("-n", TOKEN_ARGUMENT);
    tokens[2] = create_token("hello", TOKEN_ARGUMENT);
    tokens[3] = create_token(">>", TOKEN_APPEND);
    tokens[4] = create_token("append.txt", TOKEN_FILE);

    link_tokens(tokens, 5);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}
