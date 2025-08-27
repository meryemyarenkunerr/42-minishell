/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:35:22 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/27 03:25:38 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <string.h>

void	process_command(t_shell *shell, char *command)
{
	// char	*temp;
	// char	**cmds;

	if (!shell || !command)
		return ;
	cleanup_previous_state(shell);
	shell->pipeline = process_input(command, shell);
	// cmds = ft_split(command,' ');
	// if (*cmds[0] == '$' && ft_strlen(cmds[0]) > 2 && cmds[1] == NULL)
	// {
	// 	temp = get_env_value(shell->environment, cmds[0] + 1);
	// 	if (!temp)
	// 	{
	// 		shell->exit_status = 0;
	// 		free(temp);
	// 		return ;
	// 	}
	// }
	free(command);
	if (!shell->pipeline)
		return ;
	if (!builds_commands_from_pipeline(shell))
		return ;
	if (!setup_file_descriptors(shell))
		return ;
	// print_shell_info(shell);
	executer(shell);
}
