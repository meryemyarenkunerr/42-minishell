#include "../includes/minishell.h"

t_token	*create_token(char *content, t_token_types type)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->content = ft_strdup(content);
	new_token->type = type;
	new_token->prev = NULL;
	new_token->next = NULL;
	return (new_token);
}

void	add_token_to_list(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (!*head)
	{
		*head = new_token;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_token;
	new_token->prev = current;
}

static t_token_types	get_token_type(char *str)
{
	if (ft_strncmp(str, "|", 2) == 0)
		return (TOKEN_PIPE);
	else if (ft_strncmp(str, "<<", 3) == 0)
		return (TOKEN_HEREDOC);
	else if (ft_strncmp(str, ">>", 3) == 0)
		return (TOKEN_APPEND);
	else if (ft_strncmp(str, "<", 2) == 0)
		return (TOKEN_REDIRECT_IN);
	else if (ft_strncmp(str, ">", 2) == 0)
		return (TOKEN_REDIRECT_OUT);
	else
		return (TOKEN_WORD);
}

t_token	*lexer(char *input)
{
	t_token	*head;
	t_token	*new_token;
	char	**tokens;
	int		i;

	if (!input || !*input)
		return (NULL);
	tokens = ft_split(input, ' ');
	if (!tokens)
		return (NULL);
	head = NULL;
	i = 0;
	while (tokens[i])
	{
		new_token = create_token(tokens[i], get_token_type(tokens[i]));
		if (!new_token)
		{
			free_tokens(head);
			free_array(tokens);
			return (NULL);
		}
		add_token_to_list(&head, new_token);
		i++;
	}
	free_array(tokens);
	return (head);
}

void	free_tokens(t_token *tokens)
{
	t_token	*temp;

	while (tokens)
	{
		temp = tokens;
		tokens = tokens->next;
		if (temp->content)
			free(temp->content);
		free(temp);
	}
}
