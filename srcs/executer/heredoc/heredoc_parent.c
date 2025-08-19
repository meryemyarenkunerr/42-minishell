#include "../../../includes/minishell.h"

void	execute_heredoc_parent(t_command *cmd, int fds[2], pid_t pid)
{
	int	status;

	close(fds[1]); // write end'i kapat
	waitpid(pid, &status, 0); // child'ı bekle
	if (cmd->fd_in != STDIN_FILENO) // eğer input file varsa ignore et
		close(cmd->fd_in);
	cmd->fd_in = fds[0]; // read end'i fd_in olarak set et
}