/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_tokenizer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 00:00:00 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/01 00:00:00 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	count_pipes(t_token *tokens)
{
	int		count;
	t_token	*current;

	count = 0;
	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_PIPE)
			count++;
		current = current->next;
	}
	return (count);
}

static t_pipeline	*init_pipeline(int pipe_count)
{
	t_pipeline	*pipeline;

	pipeline = malloc(sizeof(t_pipeline));
	if (!pipeline)
		return (NULL);
	pipeline->count = pipe_count + 1;
	pipeline->token_lists = malloc(sizeof(t_token *) * pipeline->count);
	if (!pipeline->token_lists)
	{
		free(pipeline);
		return (NULL);
	}
	return (pipeline);
}

static void	init_token_lists(t_pipeline *pipeline)
{
	int	i;

	i = 0;
	while (i < pipeline->count)
	{
		pipeline->token_lists[i] = NULL;
		i++;
	}
}

t_pipeline	*split_by_pipes(t_token *tokens)
{
	t_pipeline	*pipeline;
	int			pipe_count;

	if (!tokens)
		return (NULL);
	pipe_count = count_pipes(tokens);
	pipeline = init_pipeline(pipe_count);
	if (!pipeline)
		return (NULL);
	init_token_lists(pipeline);
	fill_pipeline_segments(pipeline, tokens);
	return (pipeline);
}
