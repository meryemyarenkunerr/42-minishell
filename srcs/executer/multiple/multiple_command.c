/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas    <iaktas@student.42istanbul>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:14:28 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/23 15:14:28 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	**create_pipeline_pipes(int pipe_count)
{
	int	**pipes;
	int	i;

	pipes = malloc(pipe_count * sizeof(int *));
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < pipe_count)
	{
		pipes[i] = malloc(2 * sizeof(int));
		if (!pipes[i] || pipe(pipes[i]) == -1)
		{
			perror("pipe");
			cleanup_pipes(pipes, i);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

void	execute_multiple_commands(t_shell *shell, int cmd_count)
{
	t_command	*cmd;
	int			**pipes;
	int			i;

	if (!shell || !shell->commands)
		return ;
	pipes = create_pipeline_pipes(cmd_count - 1);  // pipelar oluşturuluyor
	if (!pipes)
	{
		pipes_creation_error(shell);
		return ;
	}
	cmd = shell->commands;
	i = 0;
	while (i < cmd_count && cmd) // her bir komutun üzerinden geçilir
	{
		cmd->pid = fork();
		if (cmd->pid == -1)
		{
			perror("fork");
			shell->exit_status = 1;
			break ;
		}
		if (cmd->pid == 0) // child
			execute_pipeline_child(shell, cmd, pipes, i);
		cmd = cmd->next;
		i++;
	}
	if (pipes)
		close_all_pipe_fds(pipes, cmd_count - 1);
	wait_pipeline_processes(shell, shell->commands, cmd_count);
	if (pipes)
		cleanup_pipes(pipes, cmd_count - 1);
}
