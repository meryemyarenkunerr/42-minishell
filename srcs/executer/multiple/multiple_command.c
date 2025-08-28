/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuner <mkuner@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:14:28 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/28 13:23:19 by mkuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	close_parent_pipe_ends(int **pipes, int i, int cmd_count)
{
	//fprintf(stderr, "\n=== CLOSE PARENT PIPE DEBUG ===\n");
	//fprintf(stderr, "PARENT CLOSE: cmd_idx=%d, cmd_count=%d\n", i, cmd_count);

	if (i == cmd_count)
	{
		//fprintf(stderr, "PARENT CLOSE: Single command, no pipes to close.\n");
		return ;
	}
	if (i > 0 && pipes && pipes[i - 1])
	{
		if (pipes[i - 1][0] >= 0)
		{
			//fprintf(stderr, "PARENT CLOSE: Closing pipes[%d][0]=%d (read end)\n",
			//		i-1, pipes[i-1][0]);
			close(pipes[i - 1][0]);
			pipes[i - 1][0] = -1;
		}
		else
		{
			//fprintf(stderr, "PARENT CLOSE: pipes[%d][0] already closed\n", i-1);
		}
	}
	else
	{
		//fprintf(stderr, "PARENT CLOSE: No previous pipe to close (i=%d)\n", i);
	}

	if (i < cmd_count - 1 && pipes && pipes[i])
	{
		if (pipes[i][1] >= 0)
		{
			//fprintf(stderr, "PARENT CLOSE: Closing pipes[%d][1]=%d (write end)\n",
			//		i, pipes[i][1]);
			close(pipes[i][1]);
			pipes[i][1] = -1;
		}
		else
		{
			//fprintf(stderr, "PARENT CLOSE: pipes[%d][1] already closed\n", i);
		}
	}
	else
	{
		//fprintf(stderr, "PARENT CLOSE: No current pipe to close (i=%d, cmd_count=%d)\n",
		//		i, cmd_count);
	}

	//fprintf(stderr, "PARENT CLOSE: Finished for cmd_idx=%d\n", i);
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
	{
		if (i < shell->pipeline->count)
		{
			setup_pipeline_fds(cmd, pipes, i, shell->pipeline->count);
			execute_pipeline_child(shell, cmd, pipes, i);
		}
		exit(1);
	}
	return (TRUE);
}

static void	execute_loop(t_shell *shell, int cmd_count, int **pipes)
{
	t_command	*cmd;
	int			i;

	cmd = shell->commands;
	i = 0;
	while (i < cmd_count + 1)
	{
		if (!fork_and_execute_pipeline(shell, cmd, pipes, i))
			break ;
		close_parent_pipe_ends(pipes, i, shell->pipeline->count);
		if(cmd->next)
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
	ft_putstr_fd("00000000000\n", 2);
	wait_pipeline_processes(shell, shell->commands, cmd_count);
	if (pipes)
	{
		close_all_pipe_fds(pipes, cmd_count - 1);
		cleanup_pipes(pipes, cmd_count - 1);
	}
}
