/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuner <mkuner@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:35:22 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/27 05:06:13 by mkuner           ###   ########.fr       */
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
	cmd->fd_in = STDIN_FILENO;
	cmd->file_handler = 1;
	return (cmd);
}

int	is_valid_argument_token(t_token *token, const char *cmd_name)
{
	if (!token || !cmd_name)
		return (FALSE);
	if (token->type == TOKEN_ARGUMENT)
		return (TRUE);
	return (FALSE);
}

int	allocate_new_arrays(t_command *cmd, char ***new_files,
	int **new_modes)
{
	*new_files = malloc((cmd->output_count + 2) * sizeof(char *));
	*new_modes = malloc((cmd->output_count + 1) * sizeof(int));
	if (!*new_files || !*new_modes)
		return (0);
	return (1);
}
