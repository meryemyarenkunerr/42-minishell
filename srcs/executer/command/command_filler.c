/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_filler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuner <mkuner@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 05:13:35 by mkuner            #+#    #+#             */
/*   Updated: 2025/08/27 05:13:36 by mkuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	fill_args_from_tokens(t_command *cmd, t_token *tokens,
	char *cmd_name, int arg_count)
{
	t_token	*curr;
	int		i;

	curr = tokens;
	i = 1;
	while (curr && i < arg_count)
	{
		if (is_valid_argument_token(curr, cmd_name))
			cmd->arguments[i++] = ft_strdup(curr->content);
		curr = curr->next;
	}
	cmd->arguments[i] = NULL;
}

static int	init_command_args(t_command *cmd, char *cmd_name, int arg_count)
{
	cmd->arguments = malloc((arg_count + 1) * sizeof(char *));
	if (!cmd->arguments)
		return (FALSE);
	cmd->cmd = ft_strdup(cmd_name);
	if (!cmd->cmd)
		return (FALSE);
	cmd->arguments[0] = ft_strdup(cmd_name);
	if (!cmd->arguments[0])
		return (FALSE);
	return (TRUE);
}

char	*find_command_name(t_token *token_list)
{
	t_token	*curr;

	curr = token_list;
	while (curr)
	{
		if (curr->type == TOKEN_COMMAND)
			return (ft_strdup(curr->content));
		curr = curr->next;
	}
	return (NULL);
}

int	fill_command_arguments(t_command *cmd, t_token *token_list,
	int arg_count)
{
	char	*cmd_name;

	cmd_name = find_command_name(token_list);
	if (!cmd_name)
		return (FALSE);
	if (!init_command_args(cmd, cmd_name, arg_count))
	{
		free(cmd_name);
		return (FALSE);
	}
	fill_args_from_tokens(cmd, token_list, cmd_name, arg_count);
	free(cmd_name);
	return (TRUE);
}
