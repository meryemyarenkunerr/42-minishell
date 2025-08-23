#include "../../includes/minishell.h"

void	handle_export_error(t_shell *shell, char *arg)
{
	ft_putstr_fd("export `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	shell->exit_status = 1;
}

int	handle_fork_error(int fds[2])
{
	perror("fork");
	close(fds[0]);
	close(fds[1]);
	return (FALSE);
}

pid_t	*handle_fork_error_multiple(pid_t *pids, int i)
{
	perror("fork");
	cleanup_partial_processes(pids, i);
	return (NULL);
}

void	command_not_found_error(t_shell *shell, char *cmd)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	shell->exit_status = 127;
}

void	handle_execve_error(char *cmd)
{
	if (errno == ENOENT)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	}
	else if (errno == EACCES)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	}
	else
		perror("minishell: execve");
}
