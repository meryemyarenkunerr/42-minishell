/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_lexer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 00:00:00 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/19 15:51:51 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*extract_and_join_part(char *input, int *i, char *result)
{
	char	*part;
	char	*temp;

	if (is_quote(input[*i]))
		part = extract_quoted_string(input, i);
	else
		part = extract_word_until_delimiter(input, i);
	if (!part)
		return (result);
	temp = ft_strjoin(result, part);
	free(result);
	free(part);
	return (temp);
}

static char	*extract_complex_token(char *input, int *i)
{
	char	*result;
	int		original_i;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	original_i = *i;
	while (input[*i] && !is_whitespace(input[*i])
		&& !is_redirect_operator(input[*i]) && !is_pipe(input[*i]))
	{
		result = extract_and_join_part(input, i, result);
		if (!result)
			return (NULL);
	}
	if (*i == original_i)
	{
		free(result);
		return (NULL);
	}
	return (result);
}

static t_token	*process_single_token(char *input, int *i, t_token *head)
{
	char	*token_content;
	t_token	*new_token;

	if (is_redirect_operator(input[*i]) || is_pipe(input[*i]))
		token_content = extract_operator(input, i);
	else
		token_content = extract_complex_token(input, i);
	if (!token_content)
		return (head);
	new_token = create_token(token_content,
			get_advanced_token_type(token_content));
	if (!new_token)
	{
		free(token_content);
		free_token_array(head);
		return (NULL);
	}
	add_token_to_list(&head, new_token);
	free(token_content);
	return (head);
}

static t_token	*advanced_lexer_loop(char *input)
{
	t_token	*head;
	int		i;

	head = NULL;
	i = 0;
	while (input[i])
	{
		skip_whitespace(input, &i);
		if (!input[i])
			break ;
		head = process_single_token(input, &i, head);
		if (!head && i > 0)
			return (NULL);
	}
	return (head);
}

t_token	*advanced_lexer(char *input)
{
	if (!input || !*input)
		return (NULL);
	return (advanced_lexer_loop(input));
}
