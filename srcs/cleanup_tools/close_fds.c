/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuner <mkuner@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:14:28 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/28 15:31:41 by mkuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	partial_cleanup_fds(int **pipes, int cmd_count, int idx)
{
	int	i;

	if (!pipes || cmd_count <= 1)
		return ;
	i = 0;
	while (i < cmd_count - 1)
	{
		if (i == idx - 1)
		{
			if (pipes[i][1] >= 0)
				close(pipes[i][1]);
		}
		else if (i == idx)
		{
			if (pipes[i][0] >= 0)
				close(pipes[i][0]);
		}
		else
		{
			if (pipes[i][0] >= 0)
				close(pipes[i][0]);
			if (pipes[i][1] >= 0)
				close(pipes[i][1]);
		}
		i++;
	}
}
