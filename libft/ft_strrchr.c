#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	*ch;

	ch = NULL;
	while (*s)
	{
		if (*s == (unsigned char)c)
			ch = (unsigned char *)s;
		s++;
	}
	if (*s == (unsigned char)c)
		return ((char *)s);
	return ((char *)ch);
}
