#include "../../../includes/minishell.h"

int	is_valid_identifier(const char *str)
{
	int	i;

	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (FALSE);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	execute_builtin_unset(t_shell *shell, t_command *cmd)
{
	int	i;

	if (!cmd->arguments[1])
	{
		shell->exit_status = 0;
		return ;
	}
	i = 1;
	while (cmd->arguments[i])
	{
		if (is_valid_identifier(cmd->arguments[i]))
			remove_env_variable(&shell->environment, cmd->arguments[i]);
		else
			unset_not_valid_identifier_error(shell, cmd, i);
		i++;
	}
	if (shell->exit_status != 1)
		shell->exit_status = 0;
}
