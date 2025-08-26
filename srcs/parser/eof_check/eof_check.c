/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eof_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:26:10 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/26 20:39:16 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	contains_char(const char *str, char c)
{
	while (*str != '\0')
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

void	mark_eof_tokens(t_token *tokens)
{
	t_token	*current;

	if (!tokens)
		return ;
	current = tokens;
	while (current)
	{
		if (current->next && current->type == TOKEN_HEREDOC
			&& current->next->type == TOKEN_NONE)
		{
			if (contains_char(current->next->content, '\'')
				|| contains_char(current->next->content, '\"'))
			{
				current->next->type = TOKEN_EOF_QUOTE;
				current = current->next;
			}
			else
			{
				current->next->type = TOKEN_EOF;
				current = current->next;
			}
		}
		current = current->next;
	}
}
