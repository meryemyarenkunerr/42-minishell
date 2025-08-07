#include "../includes/minishell.h"

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
		return;

	if (!*segment_head)
	{
		*segment_head = new_token;
		return;
	}

	current = *segment_head;
	while (current->next)
		current = current->next;

	current->next = new_token;
	new_token->prev = current;
}

t_pipeline	*split_by_pipes(t_token *tokens)
{
	t_pipeline	*pipeline;
	t_token		*current;
	int			pipe_count;
	int			segment_index;

	if (!tokens)
		return (NULL);

	pipe_count = count_pipes(tokens);

	pipeline = malloc(sizeof(t_pipeline));
	if (!pipeline)
		return (NULL);

	pipeline->count = pipe_count + 1;  // Number of commands = pipes + 1
	pipeline->token_lists = malloc(sizeof(t_token *) * pipeline->count);
	if (!pipeline->token_lists)
	{
		free(pipeline);
		return (NULL);
	}

	// Initialize all token lists to NULL
	int i;
	for (i = 0; i < pipeline->count; i++)
		pipeline->token_lists[i] = NULL;

	current = tokens;
	segment_index = 0;

	while (current && segment_index < pipeline->count)
	{
		if (current->type == TOKEN_PIPE)
		{
			// Move to next segment
			segment_index++;
		}
		else
		{
			// Add token to current segment
			add_token_to_segment(&pipeline->token_lists[segment_index], current);
		}
		current = current->next;
	}

	return (pipeline);
}

void	free_pipeline(t_pipeline *pipeline)
{
	int	i;

	if (!pipeline)
		return;

	if (pipeline->token_lists)
	{
		for (i = 0; i < pipeline->count; i++)
		{
			if (pipeline->token_lists[i])
				free_tokens(pipeline->token_lists[i]);
		}
		free(pipeline->token_lists);
	}
	free(pipeline);
}
