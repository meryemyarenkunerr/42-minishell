/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:33:30 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/28 20:33:32 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	handle_input_fd(t_command *cmd, int **pipes, int idx)
{
	int	input_handler;

	input_handler = 0;
	if (cmd->fd_in != STDIN_FILENO && cmd->fd_in >= 3)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
			perror("dup2 input redirection");
		close(cmd->fd_in);
		input_handler = 1;
	}
	if (!input_handler && idx > 0 && pipes && pipes[idx - 1]
		&& pipes[idx - 1][0] >= 0)
	{
		if (dup2(pipes[idx - 1][0], STDIN_FILENO) == -1)
			perror("dup2 pipe input");
		close(pipes[idx - 1][0]);
		pipes[idx - 1][0] = -1;
	}
	else if (idx > 0 && pipes && pipes[idx - 1] && pipes[idx - 1][0] >= 0)
	{
		close(pipes[idx - 1][0]);
		pipes[idx - 1][0] = -1;
	}
}

static void	handle_output_fd(t_command *cmd, int **pipes, int idx,
	int cmd_count)
{
	int	output_handler;

	output_handler = 0;
	if (cmd->fd_out != STDOUT_FILENO && cmd->fd_out >= 3)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			perror("dup2 output redirection");
		close(cmd->fd_out);
		output_handler = 1;
	}
	if (!output_handler && idx < cmd_count - 1 && pipes
		&& pipes[idx] && pipes[idx][1] >= 0)
	{
		if (dup2(pipes[idx][1], STDOUT_FILENO) == -1)
			perror("dup2 pipe output");
		close(pipes[idx][1]);
		pipes[idx][1] = -1;
	}
	else if (idx < cmd_count - 1 && pipes && pipes[idx] && pipes[idx][1] >= 0)
	{
		close(pipes[idx][1]);
		pipes[idx][1] = -1;
	}
}

void	setup_pipeline_fds(t_command *cmd, int **pipes, int idx, int cmd_count)
{
	handle_input_fd(cmd, pipes, idx);
	handle_output_fd(cmd, pipes, idx, cmd_count);
	close_remaining_pipe_fds(pipes, cmd_count - 1, idx);
}
