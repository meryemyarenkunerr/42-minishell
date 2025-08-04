#include "libft.h"

static char	**ft_free(char **strs, size_t i)
{
	while (i > 0)
	{
		free(strs[i - 1]);
		i--;
	}
	free(strs);
	return (NULL);
}

static size_t	ft_token_count(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			++count;
			while (*s && *s != c)
				++s;
		}
		else
			++s;
	}
	return (count);
}

static char	**ft_fill_arr(char **arr, char const *s, char c)
{
	int	end;
	int	start;
	int	index;

	end = 0;
	index = 0;
	while (s[end])
	{
		while (s[end] && s[end] == c)
			end++;
		start = end;
		while (s[end] && s[end] != c)
			end++;
		if (end > start)
		{
			arr[index] = ft_substr(s, start, end - start);
			if (arr[index] == NULL)
				return (ft_free(arr, index));
			index++;
		}
	}
	arr[index] = NULL;
	return (arr);
}

char	**ft_split(const char *s, char c)
{
	char	**strs;

	if (!s)
		return (0);
	strs = (char **)malloc(sizeof(char *) * (ft_token_count(s, c) + 1));
	if (strs == NULL)
		return (NULL);
	return (ft_fill_arr(strs, s, c));
}
