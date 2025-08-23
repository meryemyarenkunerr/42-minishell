/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas    <iaktas@student.42istanbul>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:35:22 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/23 17:35:22 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_string_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_single_command(t_command *command)
{
	if (!command)
		return ;
	if (command->cmd)
		free(command->cmd);
	if (command->arguments)
		free_string_array(command->arguments);
	if (command->heredoc_delimiter)
		free_string_array(command->heredoc_delimiter);
	if (command->input_files)
		free_string_array(command->input_files);
	if (command->output_files)
		free_string_array(command->output_files);
	if (command->fd_in > STDERR_FILENO)
		close(command->fd_in);
	if (command->fd_out > STDERR_FILENO)
		close(command->fd_out);
	if (command->append_modes)
		free(command->append_modes);
	free(command);
}

void	free_command_list(t_command *commands)
{
	t_command	*curr;
	t_command	*next;

	curr = commands;
	while (curr)
	{
		next = curr->next;
		free_single_command(curr);
		curr = next;
	}
}

int	cleanup_and_return_error(t_shell *shell)
{
	if (shell && shell->commands)
	{
		free_command_list(shell->commands);
		shell->commands = NULL;
	}
	return (FALSE);
}
