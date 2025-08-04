#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	*ch;

	ch = (unsigned char *)s;
	while (*ch)
	{
		if (*ch == (unsigned char)c)
			return ((char *)ch);
		ch++;
	}
	if (*ch == (unsigned char)c)
		return ((char *)ch);
	return (NULL);
}
