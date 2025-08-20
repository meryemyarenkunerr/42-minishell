#include "../../includes/minishell.h"

void	ft_exit(t_shell *shell, t_command *cmd)
{
	write(STDERR_FILENO, "bye bye <3\n", 11);
	shell->exit_status = ft_atoi(cmd->arguments[1]);
	shell->exit = 1;
}

void	numeric_argument_error_exit(t_shell *shell, t_command *cmd)
{
	write(STDERR_FILENO, "minishell: exit: ", 17);
	write(STDERR_FILENO, cmd->arguments[1], ft_strlen(cmd->arguments[1]));
	write(STDERR_FILENO, ": numeric argument required\n", 28);
	shell->exit_status = 2;
	shell->exit = 1;
}

void	too_many_argument_error_exit(t_shell *shell, t_command *cmd)
{
	write(STDERR_FILENO, "minishell: exit: ", 17);
	write(STDERR_FILENO, cmd->arguments[1], ft_strlen(cmd->arguments[1]));
	write(STDERR_FILENO, ": too many arguments\n", 21);
	shell->exit_status = 1;
}
