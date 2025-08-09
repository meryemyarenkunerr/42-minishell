#include "../../includes/minishell.h"

static int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

static char	*extract_var_name(char *str, int start, int *end)
{
	int		i;
	char	*var_name;
	int		len;

	i = start;
	while (str[i] && is_valid_var_char(str[i]))
		i++;

	*end = i;
	len = i - start;

	if (len == 0)
		return (NULL);

	var_name = malloc(len + 1);
	if (!var_name)
		return (NULL);

	ft_strlcpy(var_name, str + start, len + 1);
	return (var_name);
}

static char	*get_var_value(char *var_name, t_env *env)
{
	char	*value;

	if (!var_name)
		return (ft_strdup(""));

	value = get_env_value(env, var_name);
	if (value)
		return (ft_strdup(value));

	return (ft_strdup(""));
}

static char	*expand_variables_only(char *content, t_env *env)
{
	char	*result;
	char	*temp;
	char	*var_name;
	char	*var_value;
	int		i;
	int		j;
	int		var_end;
	int		in_single_quotes;

	result = ft_strdup("");
	if (!result)
		return (NULL);

	i = 0;
	in_single_quotes = 0;

	while (content[i])
	{
		// Track single quotes - no expansion inside them
		if (content[i] == '\'' && !in_single_quotes)
		{
			in_single_quotes = 1;
			// Copy the quote
			temp = malloc(ft_strlen(result) + 2);
			if (!temp)
			{
				free(result);
				return (NULL);
			}
			ft_strlcpy(temp, result, ft_strlen(result) + 1);
			j = ft_strlen(temp);
			temp[j] = content[i];
			temp[j + 1] = '\0';
			free(result);
			result = temp;
			i++;
		}
		else if (content[i] == '\'' && in_single_quotes)
		{
			in_single_quotes = 0;
			// Copy the quote
			temp = malloc(ft_strlen(result) + 2);
			if (!temp)
			{
				free(result);
				return (NULL);
			}
			ft_strlcpy(temp, result, ft_strlen(result) + 1);
			j = ft_strlen(temp);
			temp[j] = content[i];
			temp[j + 1] = '\0';
			free(result);
			result = temp;
			i++;
		}
		else if (content[i] == '$' && !in_single_quotes && content[i + 1] && is_valid_var_char(content[i + 1]))
		{
			// Variable expansion (not in single quotes)
			var_name = extract_var_name(content, i + 1, &var_end);
			var_value = get_var_value(var_name, env);

			temp = ft_strjoin(result, var_value);
			free(result);
			free(var_name);
			free(var_value);
			result = temp;

			i = var_end;
		}
		else
		{
			// Regular character
			temp = malloc(ft_strlen(result) + 2);
			if (!temp)
			{
				free(result);
				return (NULL);
			}
			ft_strlcpy(temp, result, ft_strlen(result) + 1);
			j = ft_strlen(temp);
			temp[j] = content[i];
			temp[j + 1] = '\0';

			free(result);
			result = temp;
			i++;
		}
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
		// Only expand TOKEN_NONE tokens (word tokens)
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