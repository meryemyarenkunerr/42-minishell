/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_lexer_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 12:39:46 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/19 14:37:05 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int	is_redirect_operator(char c)
{
	return (c == '<' || c == '>');
}

int	is_pipe(char c)
{
	return (c == '|');
}

int	skip_whitespace(char *input, int *i)
{
	while (input[*i] && is_whitespace(input[*i]))
		(*i)++;
	return (*i);
}
