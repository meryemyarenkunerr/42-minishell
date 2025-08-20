/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:53:31 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/19 14:32:53 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	free_commands(t_command *cmd_list)
{
	t_command	*temp;

	while (cmd_list)
	{
		temp = cmd_list;
		cmd_list = cmd_list->next;
		if (temp->arguments)
			free_array(temp->arguments);
		if (temp->input_file)
			free(temp->input_file);
		if (temp->output_file)
			free(temp->output_file);
		free(temp);
	}
}
