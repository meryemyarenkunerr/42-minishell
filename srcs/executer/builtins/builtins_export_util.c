#include "../../../includes/minishell.h"

int	is_valid_identifier_export(const char *str)
{
	int	i;

	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (FALSE);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	count_env_keys(t_env *env)
{
	int		count;
	t_env	*curr;

	count = 0;
	curr = env;
	while (curr)
	{
		if (curr->key)
			count++;
		curr = curr->next;
	}
	return (count);
}

void	copy_env_to_array(t_env *env, t_env **array)
{
	int		i;
	t_env	*curr;

	i = 0;
	curr = env;
	while (curr)
	{
		if (curr->key)
		{
			array[i] = curr;
			i++;
		}
		curr = curr->next;
	}
	array[i] = NULL;
}

void	sort_env_array(t_env **array, int size)
{
	int		i;
	int		j;
	t_env	*temp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - 1)
		{
			if (ft_strcmp(array[j]->key, array[j + 1]->key) > 0)
			{
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}