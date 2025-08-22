#include "../../includes/minishell.h"

int	setup_input_redirection(t_command *cmd)
{
	if (!cmd || !cmd->input_file)
		return (TRUE);
	cmd->fd_in = open(cmd->input_file, O_RDONLY);
	if (cmd->fd_in == -1)
	{
		perror(cmd->input_file);
		return (FALSE);
	}
	return (TRUE);
}

int	setup_output_redirection(t_command *cmd)
{
	int	flags;

	if (!cmd || !cmd->output_file)
		return (TRUE);
	if (cmd->append_mode)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	cmd->fd_out = open(cmd->output_file, flags, 0644);
	if (cmd->fd_out == -1)
	{
		perror(cmd->output_file);
		return (FALSE);
	}
	return (TRUE);
}

int	setup_command_fds(t_shell *shell, t_command *cmd)
{
	if (!cmd)
		return (FALSE);
	if (!setup_output_redirection(cmd))
		return (FALSE);
	if (!setup_input_redirection(cmd))
		return (FALSE);
	if (!setup_heredoc_fds(shell, cmd))
		return (FALSE);
	return (TRUE);
}

int	setup_file_descriptors(t_shell *shell)
{
	t_command	*curr;

	if (!shell || !shell->commands)
		return (FALSE);
	curr = shell->commands;
	while (curr)
	{
		if (!setup_command_fds(shell, curr))
		{
			shell->exit_status = 1;
			close_all_command_fds(shell);
			return (FALSE);
		}
		curr = curr->next;
	}
	return (TRUE);
}
