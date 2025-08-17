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

	if (!cmd->arguments[1])
	{
		shell->exit = 1;
		return ;
	}
	if (cmd->arguments[2])
	{
		printf("minishell: exit: too many arguments\n");
		shell->exit_status = 1;
		return ;
	}
	printf("bye bye <3\n");
	if (!is_valid_number(cmd->arguments[1]))
	{
		printf("minishell: exit: %s: numeric argument required\n", cmd->arguments[1]);
		shell->exit_status = 2; // error + exit status
	}
	else
	{
		exit_code = ft_atoi(cmd->arguments[1]);
		shell->exit_status = exit_code & 255;
	}
	shell->exit = 1;
}