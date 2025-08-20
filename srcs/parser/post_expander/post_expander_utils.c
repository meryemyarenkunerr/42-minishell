/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_expander_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 16:22:19 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/19 14:34:20 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	scan_word_end(char *s, int i, int *in_s, int *in_d)
{
	while (s[i])
	{
		if (s[i] == '\'' && !(*in_d))
			*in_s = !(*in_s);
		else if (s[i] == '"' && !(*in_s))
			*in_d = !(*in_d);
		if (is_whitespace(s[i]) && !(*in_s) && !(*in_d))
			break ;
		i++;
	}
	return (i);
}

static char	*extract_word(char *str, int start, int end)
{
	char	*word;
	int		len;

	len = end - start;
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	ft_strlcpy(word, str + start, len + 1);
	return (word);
}

static int	count_words_in_str(char *str)
{
	int	i;
	int	wc;
	int	in_s;
	int	in_d;

	i = 0;
	wc = 0;
	in_s = 0;
	in_d = 0;
	while (str[i])
	{
		while (str[i] && is_whitespace(str[i]) && !in_s && !in_d)
			i++;
		if (!str[i])
			break ;
		wc++;
		i = scan_word_end(str, i, &in_s, &in_d);
	}
	return (wc);
}

static int	fill_result_array(char **result, char *str, int wc)
{
	int	i;
	int	j;
	int	start;
	int	in_i[2];
	int	end;

	i = 0;
	j = 0;
	in_i[0] = 0;
	in_i[1] = 0;
	while (str[i] && j < wc)
	{
		i = skip_ws(str, i);
		if (!str[i])
			break ;
		start = i;
		end = scan_word_end(str, i, &in_i[0], &in_i[1]);
		result[j] = extract_word(str, start, end);
		if (!result[j])
			return (0);
		i = end;
		j++;
	}
	result[j] = NULL;
	return (1);
}

char	**split_by_whitespace_respect_quotes(char *str)
{
	char	**result;
	int		wc;

	if (!str || !*str)
		return (NULL);
	wc = count_words_in_str(str);
	if (wc == 0)
		return (NULL);
	result = malloc(sizeof(char *) * (wc + 1));
	if (!result)
		return (NULL);
	if (!fill_result_array(result, str, wc))
	{
		free_array(result);
		return (NULL);
	}
	return (result);
}
