/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuner <mkuner@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:14:28 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/25 21:19:31 by mkuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	execute_pipeline_child(t_shell *shell, t_command *cmd)
{
	if (!cmd || !cmd->cmd)
		exit(127);
	if (is_builtin_command(cmd->cmd))
	{
		execute_builtin(shell, cmd);
		free_single_command(cmd);
		free_at_exit(shell);
		exit(shell->exit_status);
	}
	else
	{
		execute_external_in_pipeline(shell, cmd);
		perror("execve");
		exit(127);
	}
}
