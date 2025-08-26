/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_builder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:35:22 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/26 21:39:14 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	validate_pipeline(t_shell *shell)
{
	if (!shell || !shell->pipeline || !shell->pipeline->token_lists)
		return (FALSE);
	if (shell->pipeline->count == 0)
		return (FALSE);
	return (TRUE);
}

static void	link_command_to_chain(t_shell *shell, t_command *cmd,
	t_command **prev)
{
	if (*prev)
		(*prev)->next = cmd;
	else
		shell->commands = cmd;
	*prev = cmd;
}

static int	process_pipeline_segment(t_shell *shell, int segment_index,
	t_command **prev)
{
	t_command	*curr;
	t_token		*token_list;

	token_list = shell->pipeline->token_lists[segment_index];
	curr = create_command_from_tokens(token_list);
	if (!curr)
	{
		curr = create_empty_command_with_redirections(token_list);
		if (!curr)
			return (FALSE);
	}
	link_command_to_chain(shell, curr, prev);
	return (TRUE);
}

int	builds_commands_from_pipeline(t_shell *shell)
{
	int			i;
	t_command	*prev;

	if (!validate_pipeline(shell))
		return (FALSE);
	prev = NULL;
	i = 0;
	while (i < shell->pipeline->count)
	{
		if (!process_pipeline_segment(shell, i, &prev))
			return (cleanup_and_return_error(shell));
		i++;
	}
	if (!shell->commands)
		return (FALSE);
	return (TRUE);
}
