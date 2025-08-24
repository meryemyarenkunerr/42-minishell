/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_classifier.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:25:10 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/24 15:07:01 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	is_redirect_token(t_token *token)
{
	if (!token)
		return (0);
	return (token->type == TOKEN_REDIRECT_IN
		|| token->type == TOKEN_REDIRECT_OUT
		|| token->type == TOKEN_APPEND);
}

static void	classify_token_in_segment_loop(t_token *current, int *cmd_assigned)
{
	while (current)
	{
		if (is_redirect_token(current))
		{
			if (current->next && current->next->type == TOKEN_NONE)
			{
				current->next->type = TOKEN_FILE;
				current = current->next;
			}
		}
		else if (current->type == TOKEN_NONE)
		{
			if (!*cmd_assigned)
			{
				current->type = TOKEN_COMMAND;
				*cmd_assigned = 1;	
			}
			else
				current->type = TOKEN_ARGUMENT;
		}
		current = current->next;
	}
}

static void	classify_tokens_in_segment(t_token *segment_head)
{
	t_token	*current;
	int		cmd_assigned;

	if (!segment_head)
		return ;
	current = segment_head;
	cmd_assigned = 0;
	classify_token_in_segment_loop(current, &cmd_assigned);
}

void	classify_pipeline_tokens(t_pipeline *pipeline)
{
	int	i;

	if (!pipeline || !pipeline->token_lists)
		return ;
	i = 0;
	while (i < pipeline->count)
	{
		if (pipeline->token_lists[i])
			classify_tokens_in_segment(pipeline->token_lists[i]);
		i++;
	}
}
