#include "../includes/minishell.h"

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