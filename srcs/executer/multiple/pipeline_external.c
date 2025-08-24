/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_external.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas    <iaktas@student.42istanbul>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:14:28 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/23 15:14:28 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	execute_external_in_pipeline(t_shell *shell, t_command *cmd)
{
	char	**env_array;
	char	*executable_path;

	executable_path = find_executable_path(shell, cmd->cmd);
	if (!executable_path)
	{
		write(STDERR_FILENO, cmd->cmd, ft_strlen(cmd->cmd));
		write(STDERR_FILENO, ": command not found\n", 20);
		exit(127);
	}
	env_array = convert_env_to_array(shell->environment);
	if (!env_array)
	{
		free(executable_path);
		exit(127);
	}
	if (execve(executable_path, cmd->arguments, env_array) == -1)
	{
		handle_execve_error(cmd->cmd);
		free_string_array(env_array);
		free(executable_path);
		exit(127);
	}
}
