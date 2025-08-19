/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 00:00:00 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/19 15:52:23 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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

static t_token	*process_token_array(char **tokens, t_token *head)
{
	t_token	*new_token;
	int		i;

	i = 0;
	while (tokens[i])
	{
		new_token = create_token(tokens[i], get_token_type(tokens[i]));
		if (!new_token)
		{
			free_token_array(head);
			return (NULL);
		}
		add_token_to_list(&head, new_token);
		i++;
	}
	return (head);
}

t_token	*lexer(char *input)
{
	t_token	*head;
	char	**tokens;

	if (!input || !*input)
		return (NULL);
	tokens = ft_split(input, ' ');
	if (!tokens)
		return (NULL);
	head = NULL;
	head = process_token_array(tokens, head);
	if (!head)
	{
		free_array(tokens);
		return (NULL);
	}
	free_array(tokens);
	return (head);
}
