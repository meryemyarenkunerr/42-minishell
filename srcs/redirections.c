#include "../includes/minishell.h"

int	check_redirection_syntax(t_shell *shell, t_token *tokens)
{
	t_token	*curr;

	curr = tokens;
	while (curr)
	{
		if (curr->type == TOKEN_REDIRECT_IN
			|| curr->type == TOKEN_REDIRECT_OUT
			|| curr->type == TOKEN_APPEND
			|| curr->type == TOKEN_HEREDOC)
		{
			// yönlendirmeden sonra token yok
			if (!curr->next)
			{
				printf("syntaxerror: unexpected end of file after redirection!\n");
				shell->exit_status = 2;
				return TRUE;
			}
			// token var ama pipe ya da başka bir yönlendirme
			if (curr->next->type == TOKEN_REDIRECT_IN
				|| curr->next->type == TOKEN_REDIRECT_OUT
				|| curr->next->type == TOKEN_APPEND
				|| curr->next->type == TOKEN_HEREDOC
				|| curr->next->type == TOKEN_PIPE)
			{
				printf("syntax error near unexpected token `%s'\n", curr->next->content);
				shell->exit_status = 2;
				return TRUE;
			}
		}
		curr = curr->next;
	}
	return FALSE;
}