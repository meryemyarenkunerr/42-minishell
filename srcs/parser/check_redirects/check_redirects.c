/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 00:29:11 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/22 14:39:05 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	is_special_operator_rs(t_token_types type)
{
	if (type == TOKEN_REDIRECT_IN
		|| type == TOKEN_REDIRECT_OUT
		|| type == TOKEN_APPEND
		|| type == TOKEN_HEREDOC)
		return (1);
	return (0);
}

char	*check_redirects_strings(t_token *tokens)
{
	t_token	*current;

	if (!tokens)
		return (NULL);
	current = tokens;
	if (current->type == TOKEN_PIPE)
		return ("|");
	while (current->next)
		current = current->next;
	if (current->type == TOKEN_PIPE)
		return ("|");
	if (is_special_operator_rs(current->type))
		return ("newline");
	current = tokens;
	while (current)
	{
		if (is_special_operator_rs(current->type))
		{
			if ((current->next) && (is_special_operator_rs(current->next->type)
					|| current->next->type == TOKEN_PIPE))
				return (current->next->content);
		}
		current = current->next;
	}
	return (NULL);
}
