/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuner <mkuner@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:35:22 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/28 13:18:48 by mkuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	handle_input_fd(t_command *cmd, int **pipes, int idx)
{
	int	input_handler;

	//fprintf(stderr, "\n=== INPUT DEBUG ===\n");
	//fprintf(stderr, "INPUT: cmd=%s, idx=%d, fd_in=%d\n",
	//		cmd->arguments[0], idx, cmd->fd_in);
	//fprintf(stderr, "INPUT: stdin before = %s\n",
	//		isatty(0) ? "terminal" : "pipe/file");

	input_handler = 0;
	if (cmd->fd_in != STDIN_FILENO && cmd->fd_in >= 3)
	{
		// fprintf(stderr, "INPUT: File redirection - fd_in=%d\n", cmd->fd_in);
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
			perror("dup2 input redirection");
		close(cmd->fd_in);
		input_handler = 1;
		// fprintf(stderr, "INPUT: After file redirect, stdin = %s\n",
		// 	isatty(0) ? "terminal" : "pipe/file");
	}
	if (!input_handler && idx > 0 && pipes && pipes[idx - 1]
		&& pipes[idx - 1][0] >= 0)
	{
		// fprintf(stderr, "INPUT: Pipe redirection - pipes[%d][0]=%d\n",
		// 		idx-1, pipes[idx-1][0]);
		if (dup2(pipes[idx - 1][0], STDIN_FILENO) == -1)
			perror("dup2 pipe input");
		close(pipes[idx - 1][0]);
		pipes[idx - 1][0] = -1;
		// fprintf(stderr, "INPUT: After pipe redirect, stdin = %s\n",
		// 		isatty(0) ? "terminal" : "pipe/file");
	}
	else if (idx > 0 && pipes && pipes[idx - 1] && pipes[idx - 1][0] >= 0)
	{
		// fprintf(stderr, "INPUT: Closing unused pipe - pipes[%d][0]=%d\n",
		// 		idx-1, pipes[idx-1][0]);
		close(pipes[idx - 1][0]);
		pipes[idx - 1][0] = -1;
	}
	// fprintf(stderr, "INPUT: Final stdin = %s\n",
	// 		isatty(0) ? "terminal" : "pipe/file");
}

static void	handle_output_fd(t_command *cmd, int **pipes, int idx,
	int cmd_count)
{
	int	output_handler;

	// fprintf(stderr, "\n=== OUTPUT DEBUG ===\n");
	// fprintf(stderr, "OUTPUT: cmd=%s, idx=%d, cmd_count=%d, fd_out=%d\n",
	//		cmd->arguments[0], idx, cmd_count, cmd->fd_out);
	// fprintf(stderr, "OUTPUT: stdout before = %s\n",
	// 		isatty(1) ? "terminal" : "pipe/file");

	output_handler = 0;
	if (cmd->fd_out != STDOUT_FILENO && cmd->fd_out >= 3)
	{
		// fprintf(stderr, "OUTPUT: File redirection - fd_out=%d\n", cmd->fd_out);

		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			perror("dup2 output redirection");
		close(cmd->fd_out);
		output_handler = 1;

		// fprintf(stderr, "OUTPUT: After file redirect, stdout = %s\n",
		// 		isatty(1) ? "terminal" : "pipe/file");
	}
	if (!output_handler && idx < cmd_count - 1 && pipes
		&& pipes[idx] && pipes[idx][1] >= 0)
	{
		// fprintf(stderr, "OUTPUT: Pipe redirection - pipes[%d][1]=%d\n",
		// 		idx, pipes[idx][1]);

		if (dup2(pipes[idx][1], STDOUT_FILENO) == -1)
			perror("dup2 pipe output");
		close(pipes[idx][1]);
		pipes[idx][1] = -1;

		// fprintf(stderr, "OUTPUT: After pipe redirect, stdout = %s\n",
		// 		isatty(1) ? "terminal" : "pipe/file");
	}
	else if (idx < cmd_count - 1 && pipes && pipes[idx] && pipes[idx][1] >= 0)
	{
		// fprintf(stderr, "OUTPUT: Closing unused pipe - pipes[%d][1]=%d\n",
		// 		idx, pipes[idx][1]);

		close(pipes[idx][1]);
		pipes[idx][1] = -1;

		// fprintf(stderr, "OUTPUT: Final stdout = %s\n",
		// 	isatty(1) ? "terminal" : "pipe/file");
	}
}

void	setup_pipeline_fds(t_command *cmd, int **pipes, int idx, int cmd_count)
{
	handle_input_fd(cmd, pipes, idx);
	handle_output_fd(cmd, pipes, idx, cmd_count);
	close_remaining_pipe_fds(pipes, cmd_count - 1, idx);
}
