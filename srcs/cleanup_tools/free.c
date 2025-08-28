/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:35:15 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/28 20:35:19 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_at_exit(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->environment)
	{
		free_env_list(shell->environment);
		shell->environment = NULL;
	}
	if (shell->commands)
	{
		free_command_list(shell->commands);
		shell->commands = NULL;
	}
	if (shell->pipeline)
	{
		free_pipeline(shell->pipeline);
		shell->pipeline = NULL;
	}
	rl_clear_history();
}

void	cleanup_previous_state(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->commands)
	{
		free_command_list(shell->commands);
		shell->commands = NULL;
	}
	if (shell->pipeline)
	{
		free_pipeline(shell->pipeline);
		shell->pipeline = NULL;
	}
}
