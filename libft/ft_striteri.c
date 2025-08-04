void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	j;

	j = 0;
	while (s[j])
	{
		f(j, (char *)(s + j));
		j++;
	}
}
