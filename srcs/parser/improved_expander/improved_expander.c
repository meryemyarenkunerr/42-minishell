/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   improved_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 00:00:00 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/19 14:27:14 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*append_char_to_result(char *result, char c)
{
	char	*temp;
	int		j;

	temp = malloc(ft_strlen(result) + 2);
	if (!temp)
	{
		free(result);
		return (NULL);
	}
	ft_strlcpy(temp, result, ft_strlen(result) + 1);
	j = ft_strlen(temp);
	temp[j] = c;
	temp[j + 1] = '\0';
	free(result);
	return (temp);
}

static char	*process_variable_expansion(char *content, char *result,
		t_env *env, int *i)
{
	char	*var_name;
	char	*var_value;
	char	*temp;
	int		var_end;

	var_name = extract_var_name(content, *i + 1, &var_end);
	var_value = get_var_value(var_name, env);
	temp = ft_strjoin(result, var_value);
	free(result);
	free(var_name);
	free(var_value);
	*i = var_end;
	return (temp);
}

static char	*process_character(char *content, char *result, t_env *env, int *i)
{
	int	quotes[2];

	quotes[0] = 0;
	quotes[1] = 0;
	if (content[*i] == '"' && !quotes[0])
	{
		quotes[1] = !quotes[1];
		result = append_char_to_result(result, content[*i]);
		(*i)++;
	}
	else if (content[*i] == '\'' && !quotes[1])
	{
		quotes[0] = !quotes[0];
		result = append_char_to_result(result, content[*i]);
		(*i)++;
	}
	else if (content[*i] == '$' && !quotes[0]
		&& content[*i + 1] && is_valid_var_char(content[*i + 1]))
		result = process_variable_expansion(content, result, env, i);
	else
	{
		result = append_char_to_result(result, content[*i]);
		(*i)++;
	}
	return (result);
}

static char	*expand_variables_only(char *content, t_env *env)
{
	char	*result;
	int		i;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (content[i])
	{
		result = process_character(content, result, env, &i);
		if (!result)
			return (NULL);
	}
	return (result);
}

void	improved_expand_tokens(t_token *tokens, t_env *env)
{
	t_token	*current;
	char	*expanded_content;

	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_NONE)
		{
			expanded_content = expand_variables_only(current->content, env);
			if (expanded_content)
			{
				free(current->content);
				current->content = expanded_content;
			}
		}
		current = current->next;
	}
}
