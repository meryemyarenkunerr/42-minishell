/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas    <iaktas@student.42istanbul>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:14:28 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/23 15:14:28 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_exit_status(int idx, int *exit_stat, int cmd_count, int status)
{
	if (idx == cmd_count - 1)
	{
		if (WIFEXITED(status))
			*exit_stat = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			*exit_stat = 128 + WTERMSIG(status);
	}
}

void	cleanup_pipeline(t_shell *shell, int **pipes, pid_t *pids,
	int cmd_count)
{
	int	i;
	int	status;
	int	last_exit_status;

	last_exit_status = 0;
	close_all_pipes_in_parent(pipes, cmd_count);
	i = 0;
	while (i < cmd_count)
	{
		if (pids[i] > 0)
		{
			if (waitpid(pids[i], &status, 0) == -1)
				perror("waitpid");
			else
				update_exit_status(i, &last_exit_status, cmd_count, status);
		}
		i++;
	}
	shell->exit_status = last_exit_status;
	cleanup_pipes(pipes, cmd_count);
	free(pids);
}

void	cleanup_pipes(int **pipes, int cmd_count)
{
	int	i;
	int	pipe_count;

	if (!pipes)
		return ;
	pipe_count = cmd_count - 1;
	i = 0;
	while (i < pipe_count)
	{
		if (pipes[i])
			free(pipes[i]);
		i++;
	}
	free(pipes);
}

void	cleanup_partial_pipes(int **pipes, int created_count)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (i < created_count)
	{
		if (pipes[i])
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
			free(pipes[i]);
		}
		i++;
	}
	free(pipes);
}

void	cleanup_partial_processes(pid_t *pids, int created_count)
{
	int	i;
	int	status;

	if (!pids)
		return ;
	i = 0;
	while (i < created_count)
	{
		kill(pids[i], SIGTERM);
		waitpid(pids[i], &status, 0);
		i++;
	}
	free(pids);
}
