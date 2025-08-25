/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuner <mkuner@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:43:56 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/25 17:03:54 by mkuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_append_mode(t_command *cmd, char *filename)
{
	int	i;

	if (!cmd->output_files || !cmd->append_modes)
		return (0);
	i = 0;
	while (i < cmd->output_count)
	{
		if (ft_strcmp(cmd->output_files[i], filename) == 0)
			return (cmd->append_modes[i]);
		i++;
	}
	return (0);
}

static int	process_file_in_order(t_shell *shell, t_command *cmd, char *filename)
{
	if (is_input_file(cmd, filename))
	{
		if (!setup_single_input_file(shell, cmd, filename))
			return (FALSE);
	}
	else if (is_output_file(cmd, filename))
	{
		int append_mode = get_append_mode(cmd, filename);
		if (!setup_single_output_file(shell, cmd, filename, append_mode))
			return (FALSE);
	}
	return (TRUE);
}

int	setup_command_fds(t_shell *shell, t_command *cmd)
{
	int	i;

	if (!cmd)
		return (FALSE);
	if (!setup_heredoc_fds(shell, cmd))
		return (FALSE);
	if (!cmd->ordered_all_files)
		return (TRUE);
	i = 0;
	while (cmd->ordered_all_files[i])
	{
		if (!process_file_in_order(shell, cmd, cmd->ordered_all_files[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	setup_file_descriptors(t_shell *shell)
{
	t_command	*curr;

	if (!shell || !shell->commands)
		return (FALSE);
	curr = shell->commands;
	while (curr)
	{
		if (!setup_command_fds(shell, curr))
		{
			shell->exit_status = 1;
			close_command_fds(curr);
			free(curr->cmd);
			curr->cmd = NULL;
			if (shell->pipeline->count == 1)
				return (FALSE);
		}
		curr = curr->next;
	}
	return (TRUE);
}
