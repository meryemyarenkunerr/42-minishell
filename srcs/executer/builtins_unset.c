#include "../../includes/minishell.h"

static void	remove_env_variable(t_shell *shell, const char *key)
{
	t_env	*curr;
	t_env	*prev;

	if (!key || !shell->environment)
		return ;
	curr = shell->environment;
	prev = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (prev == NULL)
				shell->environment = curr->next;
			else
				prev->next = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	execute_builtin_unset(t_shell *shell, t_command *cmd)
{
	int	i;

	i = 1;
	while (cmd->arguments && cmd->arguments[i])
	{
		remove_env_variable(shell, cmd->arguments[i]);
		i++;
	}
	shell->exit_status = 0;
}