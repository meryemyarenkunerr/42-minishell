/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:35:22 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/26 22:54:45 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_command	*init_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	ft_memset(cmd, 0, sizeof(t_command));
	cmd->fd_out = STDOUT_FILENO;
	return (cmd);
}

void	add_input_file(t_command *cmd, const char *filename)
{
	char	**new_files;
	int		i;

	if (!cmd || !filename)
		return ;
	new_files = malloc((cmd->input_count + 2) * sizeof(char *));
	if (!new_files)
		return ;
	i = 0;
	while (i < cmd->input_count)
	{
		new_files[i] = cmd->input_files[i];
		i++;
	}
	new_files[cmd->input_count] = ft_strdup(filename);
	new_files[cmd->input_count + 1] = NULL;
	if (cmd->input_files)
		free(cmd->input_files);
	cmd->input_files = new_files;
	cmd->input_count++;
	add_to_ordered_files(cmd, filename);
}

t_command	*create_empty_command_with_redirections(t_token *token_list)
{
	t_command	*cmd;
	t_token		*current;

	cmd = init_command();
	if (!cmd)
		return (NULL);
	current = token_list;
	extract_redirections_and_heredocs(cmd, current);
	return (cmd);
}
