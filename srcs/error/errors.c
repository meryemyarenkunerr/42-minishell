#include "../../includes/minishell.h"

void	handle_export_error(t_shell *shell, const char *arg)
{
	printf("export `%s': not a valid identifier\n", arg);
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
	printf("minishell: %s: command not found\n", cmd);
	shell->exit_status = 127;
}

void	handle_execve_error(char *cmd)
{
	if (errno == ENOENT)
		printf("minishell: %s: Nu such file or directory\n", cmd);
	else if (errno == EACCES)
		printf("minishell: %s: Permission denied\n", cmd);
	else
		perror("minishell: execve");
}
