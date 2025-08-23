/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   improved_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 00:00:00 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/23 15:24:09 by iaktas           ###   ########.fr       */
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

static char	*append_exit_status(char *result, t_shell *shell, int *i)
{
	char	*var_value;
	char	*temp;

	var_value = ft_itoa(shell->exit_status);
	temp = ft_strjoin(result, var_value);
	free(result);
	free(var_value);
	*i = *i + 2;
	return (temp);
}

static char	*process_character(char *content, char *result, t_shell *shell, int *quotesi)
{
	if (content[quotesi[0]] == '"' && !quotesi[1])
	{
		
		quotesi[2] = !quotesi[2];
		result = append_char_to_result(result, content[quotesi[0]]);
		(quotesi[0])++;
	}
	else if (content[quotesi[0]] == '\'' && !quotesi[2])
	{
		quotesi[1] = !quotesi[1];
		result = append_char_to_result(result, content[quotesi[0]]);
		(quotesi[0])++;
	}
	else if (content[quotesi[0]] == '$' && !quotesi[1]
		&& content[quotesi[0] + 1] && content[quotesi[0] + 1] == '?')
	{
		result = append_exit_status(result, shell, &quotesi[0]);
	}
	else if (content[quotesi[0]] == '$' && !quotesi[1]
		&& content[quotesi[0] + 1] && is_valid_var_char(content[quotesi[0] + 1]))
	{
		result = process_variable_expansion(content, result, shell->environment, &quotesi[0]);
	}
	else
	{
		result = append_char_to_result(result, content[quotesi[0]]);
		(quotesi[0])++;
	}
	return (result);
}

static char	*expand_variables_only(char *content, t_shell *shell)
{
	char	*result;
	int		quotesi[3];

	result = ft_strdup("");
	if (!result)
		return (NULL);
	quotesi[0] = 0;
	quotesi[1] = 0;
	quotesi[2] = 0;
	while (content[quotesi[0]])
	{
		result = process_character(content, result, shell, quotesi);
		if (!result)
			return (NULL);
	}
	return (result);
}

void	improved_expand_tokens(t_token *tokens, t_shell *shell)
{
	t_token	*current;
	char	*expanded_content;

	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_NONE)
		{
			expanded_content = expand_variables_only(current->content, shell);
			if (expanded_content)
			{
				free(current->content);
				current->content = expanded_content;
			}
		}
		current = current->next;
	}
}
