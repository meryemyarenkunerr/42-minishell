#include "../../includes/minishell.h"

static t_env	*create_env_node(const char *key, const char *value)
{
	t_env	*new_env;

	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return (NULL);
	new_env->key = ft_strdup(key);
	if (value)
		new_env->value = ft_strdup(value);
	else
		new_env->value = NULL;
	new_env->next = NULL;
	return (new_env);
}

static void	append_env_node(t_shell *shell, t_env *new_env)
{
	t_env	*curr;

	if (!shell->environment)
	{
		shell->environment = new_env;
		return;
	}
	curr = shell->environment;
	while (curr->next)
		curr = curr->next;
	curr->next = new_env;
}

void	add_env_variable(t_shell *shell, const char *key, const char *value)
{
	t_env	*new_env;

	if (!key)
		return;
	new_env = create_env_node(key, value);
	if (!new_env)
	{
		shell->exit_status = 1;
		return;
	}
	append_env_node(shell, new_env);
}

t_env	*find_env_variable(t_env *env_list, const char *key)
{
	t_env	*curr;

	if (!key)
		return (NULL);
	curr = env_list;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

void	set_env_variable(t_shell *shell, const char *var_value)
{
	char	*key;
	char	*val;
	char	*equals_pos;
	t_env	*existing;

	equals_pos = ft_strchr(var_value, '=');
	key = ft_substr(var_value, 0, equals_pos - var_value);
	val = ft_strdup(equals_pos + 1);
	existing = find_env_variable(shell->environment, key);
	if (existing)
	{
		free(existing->value);
		existing->value = val;
	}
	else
		add_env_variable(shell, key, val);
	free(key);
	free(val);
}