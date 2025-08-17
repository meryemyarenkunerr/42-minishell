#include "../../../includes/minishell.h"

int	setup_heredoc_fds(t_command *cmd)
{
	int		pipe_fds[2];
	pid_t	pid;

	if (!cmd || cmd->heredoc_count == 0)
		return (TRUE);
	if (pipe(pipe_fds) == -1)
	{
		perror("pipe");
		return (FALSE);
	}
	pid = fork();
	if (pid == -1)
		return (handle_fork_error(pipe_fds));
	if (pid == 0) // child process
		execute_heredoc_child(cmd, pipe_fds);
	else // parent process
		execute_heredoc_parent(cmd, pipe_fds, pid);
	return (TRUE);
}