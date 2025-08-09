#include "../../includes/minishell.h"



int	has_heredoc(t_token *tokens)
{
	t_token	*curr;

	curr = tokens;
	while (curr)
	{
		if (curr->type == TOKEN_HEREDOC)
			return TRUE;	// heredoc var
		curr = curr->next;
	}
	return FALSE; // heredoc yok
}