#include "../../../includes/minishell.h"

int	cleanup_and_return_error(t_shell *shell)
{
	if (shell->commands)
		free_command_list(shell->commands);
	shell->commands = NULL;
	return (FALSE);
}

int	argument_counter(t_token *token_list)
{
	t_token	*curr;
	int		arg_count;

	arg_count = 0;
	curr = token_list;
	while (curr)
	{
		if (curr->type == TOKEN_COMMAND || curr->type == TOKEN_ARGUMENT)
			arg_count++;
		curr = curr->next;
	}
	return (arg_count);
}

