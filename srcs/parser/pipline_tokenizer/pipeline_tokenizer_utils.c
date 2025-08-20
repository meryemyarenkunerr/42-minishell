/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_tokenizer_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 15:56:30 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/19 15:48:30 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static t_token	*copy_token(t_token *original)
{
	t_token	*new_token;

	new_token = create_token(original->content, original->type);
	return (new_token);
}

static void	add_token_to_segment(t_token **segment_head, t_token *token_to_add)
{
	t_token	*current;
	t_token	*new_token;

	new_token = copy_token(token_to_add);
	if (!new_token)
		return ;
	if (!*segment_head)
	{
		*segment_head = new_token;
		return ;
	}
	current = *segment_head;
	while (current->next)
		current = current->next;
	current->next = new_token;
	new_token->prev = current;
}

void	fill_pipeline_segments(t_pipeline *pipeline, t_token *tokens)
{
	t_token	*current;
	int		segment_index;

	current = tokens;
	segment_index = 0;
	while (current && segment_index < pipeline->count)
	{
		if (current->type == TOKEN_PIPE)
			segment_index++;
		else
			add_token_to_segment(&pipeline->token_lists[segment_index],
				current);
		current = current->next;
	}
}
