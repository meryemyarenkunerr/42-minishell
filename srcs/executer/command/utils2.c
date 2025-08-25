/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuner <mkuner@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:35:22 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/25 14:24:53 by mkuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	copy_existing_outputs(t_command *cmd, char **new_files,
	int *new_modes)
{
	int	i;

	i = 0;
	while (i < cmd->output_count)
	{
		new_files[i] = cmd->output_files[i];
		new_modes[i] = cmd->append_modes[i];
		i++;
	}
}

static int	allocate_new_arrays(t_command *cmd, char ***new_files,
	int **new_modes)
{
	*new_files = malloc((cmd->output_count + 2) * sizeof(char *));
	*new_modes = malloc((cmd->output_count + 1) * sizeof(int));
	if (!*new_files || !*new_modes)
		return (0);
	return (1);
}

static void	update_command_arrays(t_command *cmd, char **new_files,
	int *new_modes)
{
	if (cmd->output_files)
		free(cmd->output_files);
	if (cmd->append_modes)
		free(cmd->append_modes);
	cmd->output_files = new_files;
	cmd->append_modes = new_modes;
	cmd->output_count++;
}

void	add_output_file(t_command *cmd, const char *filename, int append_mode)
{
	char	**new_files;
	int		*new_modes;

	if (!cmd || !filename)
		return ;
	if (!allocate_new_arrays(cmd, &new_files, &new_modes))
		return ;
	copy_existing_outputs(cmd, new_files, new_modes);
	new_files[cmd->output_count] = ft_strdup(filename);
	new_files[cmd->output_count + 1] = NULL;
	new_modes[cmd->output_count] = append_mode;
	update_command_arrays(cmd, new_files, new_modes);
	add_to_ordered_files(cmd, filename);
}

void	add_to_ordered_files(t_command *cmd, const char *filename)
{
	char	**new_files;
	int		count;
	int		i;

	count = 0;
	if (cmd->ordered_all_files)
	{
		while (cmd->ordered_all_files[count])
			count++;
	}
	new_files = malloc((count + 2) * sizeof(char *));
	if (!new_files)
		return ;
	i = 0;
	while (i < count)
	{
		new_files[i] = cmd->ordered_all_files[i];
		i++;
	}
	new_files[count] = ft_strdup(filename);
	new_files[count + 1] = NULL;
	if (cmd->ordered_all_files)
		free(cmd->ordered_all_files);
	cmd->ordered_all_files = new_files;
}
