#include "../../includes/minishell.h"

static int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

static char	**split_by_whitespace(char *str)
{
	char	**result;
	int		word_count;
	int		i;
	int		j;
	int		start;
	int		len;

	if (!str || !*str)
		return (NULL);

	// Count words
	word_count = 0;
	i = 0;
	while (str[i])
	{
		// Skip whitespace
		while (str[i] && is_whitespace(str[i]))
			i++;
		if (str[i])
		{
			word_count++;
			// Skip word
			while (str[i] && !is_whitespace(str[i]))
				i++;
		}
	}

	if (word_count == 0)
		return (NULL);

	result = malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (NULL);

	// Extract words
	j = 0;
	i = 0;
	while (str[i] && j < word_count)
	{
		// Skip whitespace
		while (str[i] && is_whitespace(str[i]))
			i++;

		if (str[i])
		{
			start = i;
			// Find end of word
			while (str[i] && !is_whitespace(str[i]))
				i++;

			len = i - start;
			result[j] = malloc(len + 1);
			if (!result[j])
			{
				free_array(result);
				return (NULL);
			}
			ft_strlcpy(result[j], str + start, len + 1);
			j++;
		}
	}
	result[j] = NULL;
	return (result);
}

static void	insert_tokens_after(t_token *after_token, char **words)
{
	t_token	*new_token;
	t_token	*current;
	int		i;

	if (!words || !words[0])
		return;

	current = after_token;
	i = 0;

	while (words[i])
	{
		new_token = create_token(words[i], TOKEN_NONE);
		if (!new_token)
			return;

		// Insert after current
		new_token->next = current->next;
		new_token->prev = current;

		if (current->next)
			current->next->prev = new_token;
		current->next = new_token;

		current = new_token;
		i++;
	}
}

void	post_expansion_tokenize(t_token **head)
{
	t_token	*current;
	t_token	*next;
	char	**words;
	int		word_count;

	if (!head || !*head)
		return;

	current = *head;
	while (current)
	{
		next = current->next;  // Save next before potential removal

		// Only process TOKEN_NONE tokens that might contain spaces
		if (current->type == TOKEN_NONE && current->content)
		{
			words = split_by_whitespace(current->content);
			if (words)
			{
				// Count words
				word_count = 0;
				while (words[word_count])
					word_count++;

				if (word_count > 1)
				{
					// Multiple words - need to split
					// Replace current token content with first word
					free(current->content);
					current->content = ft_strdup(words[0]);

					// Insert remaining words as new tokens
					char **remaining_words = words + 1;  // Skip first word
					insert_tokens_after(current, remaining_words);
				}
				else if (word_count == 1)
				{
					// Single word - just update content (remove extra spaces)
					free(current->content);
					current->content = ft_strdup(words[0]);
				}

				free_array(words);
			}
		}

		current = next;
	}
}
