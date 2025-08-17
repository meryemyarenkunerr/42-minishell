#include "../includes/minishell.h"

t_pipeline	*mock_echo_append_heredoc()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[6];
    tokens[0] = create_token("echo", TOKEN_COMMAND);
    tokens[1] = create_token("hello", TOKEN_ARGUMENT);
    tokens[2] = create_token(">>", TOKEN_APPEND);
    tokens[3] = create_token("out.txt", TOKEN_FILE);
    tokens[4] = create_token("<<", TOKEN_HEREDOC);
    tokens[5] = create_token("EOF1", TOKEN_WORD);

    link_tokens(tokens, 6);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}