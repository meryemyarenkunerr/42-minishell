#include "../../../includes/minishell.h"

static char	*join_and_free(char *s1, char *s2)
{
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	result = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (result);
}

static char	*char_to_string(char c)
{
	char	*str;

	str = malloc(2);
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

static char	*extract_and_expand_var(char *str, int *index, t_shell *shell)
{
	char	*var_name;
	char	*var_value;
	int		start;

	if (str[0] == '?')
	{
		(*index)++;
		return (ft_itoa(shell->exit_status));
	}
	start = 0;
	while (str[start] && (ft_isalnum(str[start]) || str[start] == '_'))
		start++;
	if (start == 0)
		return (ft_strdup("$"));
	var_name = ft_substr(str, 0, start);
	var_value = get_env_value(shell->environment, var_name);
	*index += start;
	free(var_name);
	if (var_value)
		return (ft_strdup(var_value));
	else
		return (ft_strdup(""));
}

char	*expand_variable(char *line, t_shell *shell)
{
	char	*result;
	char	*temp;
	int		i;

	if (!line || !shell)
		return (NULL);
	result = ft_strdup("");
	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1])
		{
			i++;
			temp = extract_and_expand_var(&line[i], &i, shell);
			result = join_and_free(result, temp);
		}
		else
		{
			temp = char_to_string(line[i]);
			result = join_and_free(result, temp);
			i++;
		}
	}
	return (result);
}
