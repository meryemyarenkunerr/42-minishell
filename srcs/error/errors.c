#include "../../includes/minishell.h"

void	handle_export_error(t_shell *shell, const char *arg)
{
	write(STDERR_FILENO, "export `", 8);
	write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, "': not a valid identifier\n", 26);
	shell->exit_status = 1;
}

int	handle_fork_error(int fds[2])
{
	perror("fork");
	close(fds[0]);
	close(fds[1]);
	return (FALSE);
}

void	command_not_found_error(t_shell *shell, char *cmd)
{
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, ": command not found\n", 20);
	shell->exit_status = 127;
}

void	handle_execve_error(char *cmd)
{
	if (errno == ENOENT)
	{
		write(STDERR_FILENO, "minishell: ", 11);
		write(STDERR_FILENO, cmd, ft_strlen(cmd));
		write(STDERR_FILENO, ": No such file or directory\n", 28);
	}
	else if (errno == EACCES)
	{
		write(STDERR_FILENO, "minishell: ", 11);
		write(STDERR_FILENO, cmd, ft_strlen(cmd));
		write(STDERR_FILENO, ": Permission denied\n", 20);
	}
	else
		perror("minishell: execve");
}

