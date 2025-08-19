#include "../../includes/minishell.h"

void	close_command_fds(t_command *cmd)
{
	if (!cmd)
		return ;
	if (cmd->fd_in > STDERR_FILENO)
	{
		close(cmd->fd_in);
		cmd->fd_in = STDIN_FILENO;
	}
	if (cmd->fd_out > STDERR_FILENO)
	{
		close(cmd->fd_out);
		cmd->fd_out = STDOUT_FILENO;
	}
}

void	close_all_command_fds(t_shell *shell)
{
	t_command	*curr;

	if (!shell || !shell->commands)
		return ;
	curr = shell->commands;
	while (curr)
	{
		close_command_fds(curr);
		curr = curr->next;
	}
}
