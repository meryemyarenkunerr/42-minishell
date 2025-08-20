/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:56:48 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/20 14:21:06 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	is_special_operator(t_token_types type)
{
	if (type == TOKEN_REDIRECT_IN
		|| type == TOKEN_REDIRECT_OUT
		|| type == TOKEN_APPEND
		|| type == TOKEN_HEREDOC)
		return (1);
	return (0);
}

int	check_redirects(t_token *tokens)
{
	t_token	*current;

	if (!tokens)
		return (1);
	current = tokens;
	if (current->type == TOKEN_PIPE)
		return (0);
	while (current->next)
		current = current->next;
	if (current->type == TOKEN_PIPE)
		return (0);
	current = tokens;
	while (current)
	{
		if (is_special_operator(current->type))
		{
			if (current->next && is_special_operator(current->next->type))
				return (0);
		}
		current = current->next;
	}
	return (1);
}
