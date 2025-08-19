/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 11:53:58 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/19 14:35:43 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	syntax_check(char *input)
{
	int	i;
	int	single_quotes;
	int	double_quotes;

	i = 0;
	single_quotes = 0;
	double_quotes = 0;
	while (input[i])
	{
		if (input[i] == '\'')
		{
			if (double_quotes == 0)
				single_quotes = !single_quotes;
		}
		else if (input[i] == '\"')
			if (single_quotes == 0)
				double_quotes = !double_quotes;
		i++;
	}
	if (single_quotes != 0 || double_quotes != 0)
		return (0);
	return (1);
}
