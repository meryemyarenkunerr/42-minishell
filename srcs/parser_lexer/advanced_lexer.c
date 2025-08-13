#include "../../includes/minishell.h"

static int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

static int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

static int	is_redirect_operator(char c)
{
	return (c == '<' || c == '>');
}

static int	is_pipe(char c)
{
	return (c == '|');
}

static int	skip_whitespace(char *input, int *i)
{
	while (input[*i] && is_whitespace(input[*i]))
		(*i)++;
	return (*i);
}

static int	find_quote_end(char *input, int start, char quote_char)
{
	int	i;

	i = start + 1;
	while (input[i])
	{
		if (input[i] == quote_char)
			return (i);
		i++;
	}
	return (-1); // Unclosed quote
}

static char	*extract_quoted_string(char *input, int *i)
{
	char	quote_char;
	int		start;
	int		end;
	char	*result;

	quote_char = input[*i];
	start = *i;
	end = find_quote_end(input, start, quote_char);

	if (end == -1)
	{
		// Unclosed quote - include everything until end
		end = ft_strlen(input) - 1;
	}

	result = malloc(end - start + 2);
	if (!result)
		return (NULL);

	ft_strlcpy(result, input + start, end - start + 2);
	*i = end + 1;
	return (result);
}

static char	*extract_word_until_delimiter(char *input, int *i)
{
	int		start;
	int		len;
	char	*result;

	start = *i;
	len = 0;

	while (input[*i] && !is_whitespace(input[*i]) &&
			!is_quote(input[*i]) && !is_redirect_operator(input[*i]) &&
			!is_pipe(input[*i]))
	{
		(*i)++;
		len++;
	}

	if (len == 0)
		return (NULL);

	result = malloc(len + 1);
	if (!result)
		return (NULL);

	ft_strlcpy(result, input + start, len + 1);
	return (result);
}

static char	*extract_operator(char *input, int *i)
{
	char	*result;

	if (input[*i] == '>' && input[*i + 1] == '>')
	{
		result = ft_strdup(">>");
		*i += 2;
	}
	else if (input[*i] == '<' && input[*i + 1] == '<')
	{
		result = ft_strdup("<<");
		*i += 2;
	}
	else if (is_redirect_operator(input[*i]) || is_pipe(input[*i]))
	{
		result = malloc(2);
		if (!result)
			return (NULL);
		result[0] = input[*i];
		result[1] = '\0';
		(*i)++;
	}
	else
		return (NULL);

	return (result);
}

static char	*extract_complex_token(char *input, int *i)
{
	char	*result;
	char	*temp;
	char	*part;
	int		original_i;

	result = ft_strdup("");
	if (!result)
		return (NULL);

	original_i = *i;

	// Extract concatenated parts until whitespace or operator
	while (input[*i] && !is_whitespace(input[*i]) &&
			!is_redirect_operator(input[*i]) && !is_pipe(input[*i]))
	{
		if (is_quote(input[*i]))
		{
			part = extract_quoted_string(input, i);
		}
		else
		{
			part = extract_word_until_delimiter(input, i);
		}

		if (!part)
			break;

		temp = ft_strjoin(result, part);
		free(result);
		free(part);
		result = temp;

		if (!result)
			return (NULL);
	}

	// If no progress was made, return NULL
	if (*i == original_i)
	{
		free(result);
		return (NULL);
	}

	return (result);
}

static t_token_types	get_advanced_token_type(char *str)
{
	if (ft_strcmp(str, "|") == 0)
		return (TOKEN_PIPE);
	else if (ft_strcmp(str, "<<") == 0)
		return (TOKEN_HEREDOC);
	else if (ft_strcmp(str, ">>") == 0)
		return (TOKEN_APPEND);
	else if (ft_strcmp(str, "<") == 0)
		return (TOKEN_REDIRECT_IN);
	else if (ft_strcmp(str, ">") == 0)
		return (TOKEN_REDIRECT_OUT);
	else
		return (TOKEN_WORD);  // Changed to TOKEN_NONE as per your specification
}

t_token	*advanced_lexer(char *input)
{
	t_token	*head;
	t_token	*new_token;
	char	*token_content;
	int		i;

	if (!input || !*input)
		return (NULL);

	head = NULL;
	i = 0;

	while (input[i])
	{
		// Skip whitespace
		skip_whitespace(input, &i);
		if (!input[i])
			break;

		// Check for operators first
		if (is_redirect_operator(input[i]) || is_pipe(input[i]))
		{
			token_content = extract_operator(input, &i);
		}
		else
		{
			// Extract complex token (can contain quotes and concatenated parts)
			token_content = extract_complex_token(input, &i);
		}

		if (!token_content)
			break;

		new_token = create_token(token_content, get_advanced_token_type(token_content));
		if (!new_token)
		{
			free(token_content);
			free_tokens(head);
			return (NULL);
		}

		add_token_to_list(&head, new_token);
		free(token_content);
	}

	return (head);
}
