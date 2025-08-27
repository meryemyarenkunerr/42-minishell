/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuner <mkuner@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:14:28 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/27 07:05:59 by mkuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	close_parent_pipe_ends(int **pipes, int i, int cmd_count)
{
	if (i > 0 && pipes && pipes[i - 1])
	{
		if (pipes[i - 1][0] >= 0)
		{
			close(pipes[i - 1][0]);
			pipes[i - 1][0] = -1;
		}
	}
	if (i < cmd_count - 1 && pipes && pipes[i])
	{
		if (pipes[i][1] >= 0)
		{
			close(pipes[i][1]);
			pipes[i][1] = -1;
		}
	}
}

static int	fork_and_execute_pipeline(t_shell *shell, t_command *cmd,
	int **pipes, int i)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
	{
		perror("fork");
		shell->exit_status = 1;
		return (FALSE);
	}
	if (cmd->pid == 0)
		execute_pipeline_child(shell, cmd, pipes, i);
	return (TRUE);
}

static void	execute_loop(t_shell *shell, int cmd_count, int **pipes)
{
	t_command	*cmd;
	int			i;

	cmd = shell->commands;
	i = 0;
	while (i < cmd_count && cmd)
	{
		if (!fork_and_execute_pipeline(shell, cmd, pipes, i))
			break ;
		close_parent_pipe_ends(pipes, i, cmd_count);
		cmd = cmd->next;
		i++;
	}
}

void	execute_multiple_commands(t_shell *shell, int cmd_count)
{
	int	**pipes;

	if (!shell || !shell->commands)
		return ;
	pipes = create_pipeline_pipes(cmd_count - 1);
	if (!pipes && cmd_count > 1)
	{
		pipes_creation_error(shell);
		return ;
	}
	execute_loop(shell, cmd_count, pipes);
	if (pipes)
		close_all_pipe_fds(pipes, cmd_count - 1);
	wait_pipeline_processes(shell, shell->commands, cmd_count);
	if (pipes)
		cleanup_pipes(pipes, cmd_count - 1);
}
