#include "../includes/minishell.h"

t_pipeline *mock_cat_heredoc()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[3];
    tokens[0] = create_token("cat", TOKEN_COMMAND);
    tokens[1] = create_token("<<", TOKEN_HEREDOC);
    tokens[2] = create_token("EOF", TOKEN_WORD);

    link_tokens(tokens, 3);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}