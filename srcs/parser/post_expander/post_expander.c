/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 00:00:00 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/23 16:56:37 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	insert_tokens_after(t_token *after_token, char **words)
{
	t_token	*new_token;
	t_token	*current;
	int		i;

	if (!words || !words[0])
		return ;
	current = after_token;
	i = 0;
	while (words[i])
	{
		new_token = create_token(words[i], TOKEN_NONE);
		if (!new_token)
			return ;
		new_token->next = current->next;
		new_token->prev = current;
		if (current->next)
			current->next->prev = new_token;
		current->next = new_token;
		current = new_token;
		i++;
	}
}

static int	count_words(char **words)
{
	int	count;

	count = 0;
	while (words[count])
		count++;
	return (count);
}

static void	process_token_content(t_token *current)
{
	char	**words;
	int		word_count;
	char	**remaining_words;

	words = split_by_whitespace_respect_quotes(current->content);
	if (!words)
		return ;
	word_count = count_words(words);
	if (word_count > 1)
	{
		free(current->content);
		current->content = ft_strdup(words[0]);
		remaining_words = words + 1;
		insert_tokens_after(current, remaining_words);
	}
	else if (word_count == 1)
	{
		free(current->content);
		current->content = ft_strdup(words[0]);
	}
	free_string_array(words);
}

void	post_expansion_tokenize(t_token **head)
{
	t_token	*current;
	t_token	*next;

	if (!head || !*head)
		return ;
	current = *head;
	while (current)
	{
		next = current->next;
		if (current->type == TOKEN_NONE && current->content)
			process_token_content(current);
		current = next;
	}
}
