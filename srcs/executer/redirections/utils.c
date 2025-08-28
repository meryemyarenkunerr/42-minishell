/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:33:01 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/28 20:33:03 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_input_file(t_command *cmd, char *filename)
{
	int	i;

	if (!cmd->input_files)
		return (FALSE);
	i = 0;
	while (i < cmd->input_count)
	{
		if (ft_strcmp(cmd->input_files[i], filename) == 0)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	is_output_file(t_command *cmd, char *filename)
{
	int	i;

	if (!cmd->output_files)
		return (FALSE);
	i = 0;
	while (i < cmd->output_count)
	{
		if (ft_strcmp(cmd->output_files[i], filename) == 0)
			return (TRUE);
		i++;
	}
	return (FALSE);
}
