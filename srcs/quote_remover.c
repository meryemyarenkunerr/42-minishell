#include "../includes/minishell.h"

static char	*remove_all_quotes(char *str)
{
	char	*result;
	int		i;
	int		j;
	int		len;

	if (!str)
		return (NULL);

	len = ft_strlen(str);
	result = malloc(len + 1);
	if (!result)
		return (NULL);

	i = 0;
	j = 0;
	while (str[i])
	{
		// Skip all quotes (both single and double)
		if (str[i] == '\'' || str[i] == '"')
		{
			i++;
			continue;
		}
		// Copy non-quote characters
		result[j] = str[i];
		j++;
		i++;
	}

	result[j] = '\0';
	return (result);
}

void	remove_quotes_from_tokens(t_token *tokens)
{
	t_token	*current;
	char	*cleaned_content;

	current = tokens;
	while (current)
	{
		// Only process TOKEN_NONE tokens (word tokens)
		if (current->type == TOKEN_NONE && current->content)
		{
			cleaned_content = remove_all_quotes(current->content);
			if (cleaned_content)
			{
				free(current->content);
				current->content = cleaned_content;
			}
		}
		current = current->next;
	}
}
