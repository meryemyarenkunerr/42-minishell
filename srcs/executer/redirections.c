/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuner <mkuner@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:43:56 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/24 20:45:14 by mkuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h>

int	setup_input_redirection(t_shell *shell, t_command *cmd)
{
	int	i;
	int	fd;

	if (!cmd || !cmd->input_files || cmd->input_count == 0)
		return (TRUE);
	i = 0;
	while (i < cmd->input_count)
	{
		fd = open(cmd->input_files[i], O_RDONLY);
		if (fd == -1)
		{
			ft_putstr_fd(cmd->input_files[i], STDERR_FILENO);
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
			//perror(cmd->input_files[i]);
			shell->exit_status = 1;
			return (FALSE);
		}
		if (cmd->fd_in != STDIN_FILENO && cmd->fd_in != -1)
			close(cmd->fd_in);
		cmd->fd_in = fd;
		i++;
	}
	return (TRUE);
}

int	setup_output_redirection(t_shell *shell, t_command *cmd)
{
	int	i;
	int	fd;

	if (!cmd || !cmd->output_files || cmd->output_count == 0)
		return (TRUE);
	i = -1;
	while (++i < cmd->output_count)
	{
		fd = open_output_file(shell, cmd, i);
		if (fd == -1)
			return (FALSE);
		close_old_fd(&cmd->fd_out);
		cmd->fd_out = fd;
	}
	return (TRUE);
}

int	setup_command_fds(t_shell *shell, t_command *cmd)
{
	if (!cmd)
		return (FALSE);
	if (!setup_heredoc_fds(shell, cmd))
		return (FALSE);
	if (!setup_output_redirection(shell, cmd))
		return (FALSE);
	if (!setup_input_redirection(shell, cmd))
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
