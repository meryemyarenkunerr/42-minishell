#include "../includes/minishell.h"

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static t_env	*create_env_node(char *key, char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	if (!new_node->key || !new_node->value)
	{
		free_env_list(new_node);
		return (NULL);
	}
	return (new_node);
}

t_env	*copy_env(char **envp)
{
	t_env	*head;
	t_env	*current;
	t_env	*new_node;
	char	*equals_sign;
	int		i;

	head = NULL;
	i = 0;
	while (envp[i])
	{
		equals_sign = ft_strchr(envp[i], '=');
		if (equals_sign)
		{
			*equals_sign = '\0';
			new_node = create_env_node(envp[i], equals_sign + 1);
			*equals_sign = '=';
			if (!new_node)
			{
				free_env_list(head);
				return (NULL);
			}
			if (!head)
				head = new_node;
			else
			{
				current = head;
				while (current->next)
					current = current->next;
				current->next = new_node;
			}
		}
		i++;
	}
	return (head);
}

char	*get_env_value(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key) + 1) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	set_env_value(t_env **env, char *key, char *value)
{
	t_env	*current;
	t_env	*new_node;

	current = *env;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
	new_node = create_env_node(key, value);
	if (new_node)
	{
		new_node->next = *env;
		*env = new_node;
	}
}
