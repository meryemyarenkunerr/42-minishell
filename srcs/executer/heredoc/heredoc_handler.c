#include "../../../includes/minishell.h"

int	setup_heredoc_fds(t_shell *shell, t_command *cmd)
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
	if (pid == 0)
		execute_heredoc_child(shell, cmd, pipe_fds);
	else
		execute_heredoc_parent(cmd, pipe_fds, pid);
	return (TRUE);
}
