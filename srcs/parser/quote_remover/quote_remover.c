/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_remover.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 00:00:00 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/23 16:44:00 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	handle_double_quote(char *str, int i, int *in_dq)
{
	if (str[i] == '"' && !(*in_dq))
	{
		*in_dq = 1;
		return (i + 1);
	}
	if (str[i] == '"' && *in_dq)
	{
		*in_dq = 0;
		return (i + 1);
	}
	return (i);
}

static int	handle_single_quote(char *str, char *res, int i, int *j)
{
	if (str[i] == '\'')
	{
		i++;
		while (str[i] && str[i] != '\'')
		{
			res[*j] = str[i];
			(*j)++;
			i++;
		}
		if (str[i] == '\'')
			i++;
	}
	return (i);
}

static char	*remove_paired_quotes_loop(char *str, char *res)
{
	int	i;
	int	j;
	int	in_dq;

	i = 0;
	j = 0;
	in_dq = 0;
	while (str[i])
	{
		if (str[i] == '"')
			i = handle_double_quote(str, i, &in_dq);
		else if (str[i] == '\'' && !in_dq)
			i = handle_single_quote(str, res, i, &j);
		else
		{
			res[j] = str[i];
			j++;
			i++;
		}
	}
	res[j] = '\0';
	return (res);
}

static char	*remove_paired_quotes(char *str)
{
	char	*result;
	int		len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	return (remove_paired_quotes_loop(str, result));
}

void	remove_quotes_from_tokens(t_token *tokens)
{
	t_token	*current;
	char	*cleaned_content;

	current = tokens;
	while (current)
	{
		if (current->content)
		{
			cleaned_content = remove_paired_quotes(current->content);
			if (cleaned_content)
			{
				free(current->content);
				current->content = cleaned_content;
			}
		}
		current = current->next;
	}
}
