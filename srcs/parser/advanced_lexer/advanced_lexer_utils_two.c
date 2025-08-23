/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_lexer_utils_two.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 12:23:47 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/23 20:20:37 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	find_quote_end(char *input, int start, char quote_char)
{
	int	i;

	i = start + 1;
	while (input[i])
	{
		if (input[i] == quote_char)
			return (i);
		i++;
	}
	return (-1);
}

t_token_types	get_advanced_token_type(char *str)
{
	if (ft_strcmp(str, "|") == 0)
		return (TOKEN_PIPE);
	else if (ft_strcmp(str, "<<") == 0)
		return (TOKEN_HEREDOC);
	else if (ft_strcmp(str, ">>") == 0)
		return (TOKEN_APPEND);
	else if (ft_strcmp(str, "<") == 0)
		return (TOKEN_REDIRECT_IN);
	else if (ft_strcmp(str, ">") == 0)
		return (TOKEN_REDIRECT_OUT);
	else
		return (TOKEN_NONE);
}

char	*extract_operator(char *input, int *i)
{
	char	*result;

	if (input[*i] == '>' && input[*i + 1] == '>')
	{
		result = ft_strdup(">>");
		*i += 2;
	}
	else if (input[*i] == '<' && input[*i + 1] == '<')
	{
		result = ft_strdup("<<");
		*i += 2;
	}
	else if (is_redirect_operator(input[*i]) || is_pipe(input[*i]))
	{
		result = malloc(2);
		if (!result)
			return (NULL);
		result[0] = input[*i];
		result[1] = '\0';
		(*i)++;
	}
	else
		return (NULL);
	return (result);
}

char	*extract_word_until_delimiter(char *input, int *i)
{
	int		start;
	int		len;
	char	*result;

	start = *i;
	len = 0;
	while (input[*i] && !is_whitespace(input[*i])
		&& !is_quote(input[*i]) && !is_redirect_operator(input[*i])
		&& !is_pipe(input[*i]))
	{
		(*i)++;
		len++;
	}
	if (len == 0)
		return (NULL);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, input + start, len + 1);
	return (result);
}

char	*extract_quoted_string(char *input, int *i)
{
	char	quote_char;
	int		start;
	int		end;
	char	*result;

	quote_char = input[*i];
	start = *i;
	end = find_quote_end(input, start, quote_char);
	if (end == -1)
		end = ft_strlen(input) - 1;
	result = malloc(end - start + 2);
	if (!result)
		return (NULL);
	ft_strlcpy(result, input + start, end - start + 2);
	*i = end + 1;
	return (result);
}
