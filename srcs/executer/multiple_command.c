/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuner <mkuner@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:14:28 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/25 21:40:30 by mkuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_pipeline_commands(t_shell *shell, int cmd_count)
{
	int		**pipes;
	pid_t	*pids;

	if (!shell || !shell->commands || cmd_count < 2)
		return ;
	pipes = create_pipeline_pipes(cmd_count);
	if (!pipes)
	{
		shell->exit_status = 1;
		return ;
	}
	pids = execute_pipeline_processes(shell, pipes, cmd_count);
	if (!pids)
	{
		cleanup_pipes(pipes, cmd_count);
		shell->exit_status = 1;
		return ;
	}
	cleanup_pipeline(shell, pipes, pids, cmd_count);
}
