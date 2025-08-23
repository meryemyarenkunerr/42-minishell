/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas    <iaktas@student.42istanbul>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:35:22 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/23 17:35:22 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	handle_child(t_shell *shell, t_command *cmd, int **pipes,
				int i)
{
	setup_pipeline_child(cmd, pipes, shell->pipeline->count, i);
	execute_pipeline_child(shell, cmd);
	free_single_command(cmd);
	free_at_exit(shell);
	exit(127);
}

int	skip_empty_command(pid_t *pids, t_command **cmd, int i)
{
	if (!(*cmd)->cmd)
	{
		pids[i] = 0;
		*cmd = (*cmd)->next;
		return (1);
	}
	return (0);
}

int	handle_pipe_error(int **pipes, int i)
{
	perror("pipe");
	free(pipes[i]);
	cleanup_partial_pipes(pipes, i);
	return (1);
}
