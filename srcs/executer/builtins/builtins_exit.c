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
	int	cmd_count;

	cmd_count = cmd_counter_except_first(cmd);
	if (cmd_count == 0)
	{
		write(STDOUT_FILENO, "bye bye <3\n", 11);
		shell->exit = 1;
		return ;
	}
	else
	{
		if (is_valid_number(cmd->arguments[1]) && cmd_count == 1)
		{
			ft_exit(shell, cmd);
			return ;
		}
		else if (is_valid_number(cmd->arguments[1]) && cmd_count > 1)
			too_many_argument_error_exit(shell, cmd);
		else
		{
			numeric_argument_error_exit(shell, cmd);
			return ;
		}
	}
}
