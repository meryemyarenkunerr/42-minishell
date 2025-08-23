#include "../../includes/minishell.h"

void	add_new_env_node(t_env **env, t_env *tail)
{
	t_env	*curr;

	if (!env || !tail)
		return ;
	if (!*env)
	{
		*env = tail;
		return ;
	}
	curr = *env;
	while (curr->next)
		curr = curr->next;
	curr->next = tail;
}

t_env	*create_env_node_empty(void)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = NULL;
	node->value = NULL;
	node->next = NULL;
	return (node);
}

t_env	*create_env_node(char *key, char *val)
{
	t_env	*node;

	node = create_env_node_empty();
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	if (!node->key)
	{
		free_env_node(node);
		return (NULL);
	}
	if (val)
	{
		node->value = ft_strdup(val);
		if (!node->value)
		{
			free_env_node(node);
			return (NULL);
		}
	}
	return (node);
}

int	extract_key_value(char *env_pair, char **key, char **val)
{
	char	*equal_pos;
	int		len;

	equal_pos = ft_strchr(env_pair, '=');
	if (!equal_pos)
		return (FALSE);
	len = equal_pos - env_pair;
	*key = ft_substr(env_pair, 0, len);
	if (!*key)
		return (FALSE);
	*val = ft_strdup(equal_pos + 1);
	if (!*val)
	{
		free(*key);
		return (FALSE);
	}
	return (TRUE);
}

int	add_key_value_pair(t_env **env, char *env_pair)
{
	char	*key;
	char	*val;
	t_env	*node;

	if (!extract_key_value(env_pair, &key, &val))
		return (FALSE);
	node = create_env_node(key, val);
	free(key);
	free(val);
	if (!node)
		return (FALSE);
	add_new_env_node(env, node);
	return (TRUE);
}
