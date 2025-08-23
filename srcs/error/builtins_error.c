#include "../../includes/minishell.h"

void	ft_exit(t_shell *shell, t_command *cmd)
{
	shell->exit_status = ft_atoi(cmd->arguments[1]);
	shell->exit = 1;
}

void	numeric_argument_error_exit(t_shell *shell, t_command *cmd)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(cmd->arguments[1], STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	shell->exit_status = 2;
	shell->exit = 1;
}

void	too_many_argument_error_exit(t_shell *shell, t_command *cmd)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(cmd->arguments[1], STDERR_FILENO);
	ft_putstr_fd(": too many arguments\n", STDERR_FILENO);
	shell->exit_status = 1;
}
