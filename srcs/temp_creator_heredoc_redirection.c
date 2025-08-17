#include "../includes/minishell.h"

t_pipeline	*mock_cat_heredoc_redirect()
{
    t_pipeline *pipeline = malloc(sizeof(t_pipeline));
    pipeline->count = 1;
    pipeline->token_lists = malloc(1 * sizeof(t_token*));

    t_token *tokens[5];
    tokens[0] = create_token("cat", TOKEN_COMMAND);
    tokens[1] = create_token("<<", TOKEN_HEREDOC);
    tokens[2] = create_token("END", TOKEN_WORD);
    tokens[3] = create_token(">", TOKEN_REDIRECT_OUT);
    tokens[4] = create_token("output.txt", TOKEN_FILE);

    link_tokens(tokens, 5);
    pipeline->token_lists[0] = tokens[0];

    return pipeline;
}