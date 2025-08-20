#include "../../../includes/minishell.h"

int	is_valid_number(const char *str)
{
	int	i;

	i = 0;
	if (str[0] == '+' || str[0] == '-')
		i = 1;
	if (!str[i])
		return (FALSE);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	execute_builtin_exit(t_shell *shell, t_command *cmd)
{
	int	exit_code;
	int	i;

	if (!cmd->arguments[1])
	{
		printf("bye bye <3\n");
		shell->exit = 1;
		return ;
	}
	i = 1;

	if (cmd->arguments[2])
	{
		too_many_argument_error(shell);
		return ;
	}
	if (!is_valid_number(cmd->arguments[1]))
		numeric_argument_error(shell, cmd);
	else
	{
		exit_code = ft_atoi(cmd->arguments[1]);
		shell->exit_status = exit_code & 255;
	}
	shell->exit = 1;
}
