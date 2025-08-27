/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuner <mkuner@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:35:22 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/27 15:30:08 by mkuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	process_command(t_shell *shell, char *command)
{
	if (!shell || !command)
		return ;
	cleanup_previous_state(shell);
	shell->pipeline = process_input(command, shell);
	free(command);
	if (!shell->pipeline)
		return ;
	if (!builds_commands_from_pipeline(shell))
		return ;
	if (!setup_file_descriptors(shell))
		return ;
	executer(shell);
}
