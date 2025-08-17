#include "../includes/minishell.h"

// Helper function to create a token
t_token	*create_token(const char *content, t_token_types type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return NULL;

	token->content = ft_strdup(content);
	token->type = type;
	token->prev = NULL;
	token->next = NULL;
	return token;
}

// Helper function to link tokens in a doubly linked list
void	link_tokens(t_token *tokens[], int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (i > 0)
		{
			tokens[i]->prev = tokens[i - 1];
			tokens[i - 1]->next = tokens[i];
		}
		i++;
	}
}