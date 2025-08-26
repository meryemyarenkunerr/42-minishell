/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuner <mkuner@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:35:22 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/25 17:32:35 by mkuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	wait_pipeline_processes(t_shell * shell, t_command *cmds, int cmd_count)
{
	int			i;
	int			last_exit_status;
	t_command	*cmd;
	int			status;
	int			exit_code;

	//printf("DEBUG: Waiting for %d processes\n", cmd_count);
	i = 0;
	last_exit_status = 0;
	cmd = cmds;
	while (i < cmd_count && cmd)
	{
		if (cmd->pid > 0)
		{
			waitpid(cmd->pid, &status, 0);
			//printf("DEBUG: Process %d finished with status %d\n", cmd->pid, status);
			if (WIFEXITED(status))
			{
				exit_code = WEXITSTATUS(status);
				if (i == cmd_count - 1)
					last_exit_status = exit_code;
			}
			else if (WIFSIGNALED(status))
			{
				if (i == cmd_count - 1)
					last_exit_status = 128 + WTERMSIG(status);
			}
		}
		cmd = cmd->next;
		i++;
	}
	shell->exit_status = last_exit_status;
}

void	setup_pipeline_fds(t_command *cmd, int **pipes, int idx, int cmd_count)
{
	if (idx > 0)
	{
		if (cmd->file_handler == 1 && cmd->fd_in == STDIN_FILENO)
		{
			if (dup2(pipes[idx - 1][0], STDIN_FILENO) == -1)
				perror("dup2 pipe input");
		}
		close(pipes[idx - 1][0]);
	}
	if (idx < cmd_count - 1)
	{
		if (cmd->file_handler == 1 && cmd->fd_out == STDOUT_FILENO)
		{
			if (dup2(pipes[idx][1], STDOUT_FILENO) == -1)
				perror("dup2 pipe output");
		}
		close(pipes[idx][1]);
	}
	close_remaining_pipe_fds(pipes, cmd_count - 1, idx);
}
