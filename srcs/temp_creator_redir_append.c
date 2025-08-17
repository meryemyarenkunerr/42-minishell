#include "../includes/minishell.h"

t_pipeline	*mock_echo_append()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[4];
    tokens[0] = create_token("echo", TOKEN_COMMAND);
    tokens[1] = create_token("hello", TOKEN_ARGUMENT);
    tokens[2] = create_token(">>", TOKEN_APPEND);
    tokens[3] = create_token("out.txt", TOKEN_FILE);

    link_tokens(tokens, 4);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}