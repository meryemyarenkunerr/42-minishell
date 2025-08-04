#include "libft.h"

static unsigned int	ft_numbersize(int n)
{
	unsigned int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*s;
	unsigned int	num;
	unsigned int	len;

	len = ft_numbersize(n);
	s = (char *)malloc(sizeof(char) * (len + 1));
	if (s == NULL)
		return (NULL);
	if (n < 0)
	{
		s[0] = '-';
		num = -n;
	}
	else
		num = n;
	if (num == 0)
		s[0] = '0';
	s[len] = '\0';
	while (num != 0)
	{
		s[len - 1] = (num % 10) + '0';
		num /= 10;
		len--;
	}
	return (s);
}
