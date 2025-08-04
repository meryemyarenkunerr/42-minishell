#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = ft_strlen(s1);
	s = (char *)malloc(sizeof(*s) * (j + 1));
	if (!s)
		return (0);
	while (i < j)
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}
