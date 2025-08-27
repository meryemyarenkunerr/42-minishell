/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:35:22 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/27 02:33:23 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	wait_pipeline_processes(t_shell *shell, t_command *cmds , int cmd_count)
{
	t_command *cmd;
	int last_exit_status = 0;

	(void)cmd_count;
	cmd = cmds;
	while (cmd && cmd->next)
	{
		if (cmd->pid > 0)
			waitpid(cmd->pid, NULL, WNOHANG); // sadece temizle
		cmd = cmd->next;
	}
	if (cmd && cmd->pid > 0)
	{
		int status;
		waitpid(cmd->pid, &status, 0);

		last_exit_status = WIFEXITED(status) ? 
							WEXITSTATUS(status) : 128 + WTERMSIG(status);
		t_command *cleanup = cmds;
		while (cleanup)
		{
			if (cleanup->pid > 0 && cleanup != cmd)
			{
				kill(cleanup->pid, SIGTERM);
				waitpid(cleanup->pid, NULL, 0);
			}
			cleanup = cleanup->next;
		}
	}
	shell->exit_status = last_exit_status;
}


void	setup_pipeline_fds(t_command *cmd, int **pipes, int idx, int cmd_count)
{	
	int input_handled;
	int output_handled;
	
	input_handled = 0;
	output_handled = 0;
	if (cmd->fd_in != STDIN_FILENO && cmd->fd_in >= 3)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
			perror("dup2 input redirection");
		close(cmd->fd_in);
		input_handled = 1;
	}
	if (cmd->fd_out != STDOUT_FILENO && cmd->fd_out >= 3)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			perror("dup2 output redirection");
		close(cmd->fd_out);
		output_handled = 1;
	}
	if (!input_handled && idx > 0 && pipes && pipes[idx - 1] && pipes[idx - 1][0] >= 0)
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
	if (!output_handled && idx < cmd_count - 1 && pipes && pipes[idx] && pipes[idx][1] >= 0)
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
	close_remaining_pipe_fds(pipes, cmd_count - 1, idx);
}
