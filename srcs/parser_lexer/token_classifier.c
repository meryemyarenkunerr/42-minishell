#include "../../includes/minishell.h"

static int	is_redirect_token(t_token *token)
{
	if (!token)
		return (0);
	return (token->type == TOKEN_REDIRECT_IN ||
			token->type == TOKEN_REDIRECT_OUT ||
			token->type == TOKEN_APPEND ||
			token->type == TOKEN_HEREDOC);
}

static void	classify_tokens_in_segment(t_token *segment_head)
{
	t_token	*current;
	int		cmd_assigned;

	if (!segment_head)
		return;

	current = segment_head;
	cmd_assigned = 0;

	while (current)
	{
		if (is_redirect_token(current))
		{
			// This is a redirect operator, next token should be FILE
			if (current->next && current->next->type == TOKEN_NONE)
			{
				current->next->type = TOKEN_FILE;
				current = current->next; // Move to FILE token
			}
		}
		else if (current->type == TOKEN_NONE)
		{
			// Regular token - CMD if first, otherwise ARG
			if (!cmd_assigned)
			{
				current->type = TOKEN_COMMAND;
				cmd_assigned = 1;
			}
			else
				current->type = TOKEN_ARGUMENT;
		}
		// If current is already a classified token, don't change it

		current = current->next;
	}
}

void	classify_pipeline_tokens(t_pipeline *pipeline)
{
	int	i;

	if (!pipeline || !pipeline->token_lists)
		return;

	for (i = 0; i < pipeline->count; i++)
	{
		if (pipeline->token_lists[i])
			classify_tokens_in_segment(pipeline->token_lists[i]);
	}
}