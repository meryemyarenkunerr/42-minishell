#include "../../../includes/minishell.h"

void	free_string_array_partial(char **array, int count)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (i < count)
	{
		if (array[i])
			free(array[i]);
		i++;
	}
	free(array);
}

int	count_env_entries(t_env *env)
{
	t_env	*curr;
	int		count;

	count = 0;
	curr = env;
	while (curr)
	{
		if (curr->key && curr->value)
			count++;
		curr = curr->next;
	}
	return (count);
}