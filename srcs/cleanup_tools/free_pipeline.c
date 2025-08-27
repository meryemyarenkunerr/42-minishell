/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:14:28 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/27 03:45:00 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_token_array(t_token *tokens)
{
	t_token	*curr;
	t_token	*next;

	if (!tokens)
		return ;
	curr = tokens;
	while (curr->prev)
		curr = curr->prev;
	while (curr)
	{
		next = curr->next;
		if (curr->content)
			free(curr->content);
		free(curr);
		curr = next;
	}
}

void	free_pipeline(t_pipeline *pipeline)
{
	int	i;

	if (!pipeline)
		return ;
	if (pipeline->token_lists)
	{
		i = 0;
		while (i < pipeline->count)
		{
			if (pipeline->token_lists[i])
				free_token_array(pipeline->token_lists[i]);
			i++;
		}
		free(pipeline->token_lists);
	}
	free(pipeline);
}
