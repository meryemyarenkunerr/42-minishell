#include "../../../includes/minishell.h"

void	execute_heredoc_parent(t_command *cmd, int fds[2], pid_t pid)
{
	int	status;

	close(fds[1]);
	waitpid(pid, &status, 0);
	if (cmd->fd_in != STDIN_FILENO)
		close(cmd->fd_in);
	cmd->fd_in = fds[0];
}
