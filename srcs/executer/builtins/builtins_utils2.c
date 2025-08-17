#include "../../../includes/minishell.h"

int	cmd_counter_except_first(t_command *cmd)
{
	int	count;

	count = 0;
	if (!cmd || !cmd->arguments)
		return (0);
	while (cmd->arguments[count + 1])
		count++;
	return (count);
}

void	remove_env_variable(t_env **env, const char *key)
{
	t_env	*curr;
	t_env	*prev;

	if (!env || !*env || !key)
		return ;
	prev = NULL;
	curr = *env;
	while (curr)
	{
		if (curr->key && ft_strcmp(curr->key, key) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			free_env_node(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	set_env_variable(t_env **env, const char *key, const char *val)
{
	t_env	*curr;
	t_env	*new;

	curr = *env;
	while (curr)
	{
		if (curr->key && ft_strcmp(curr->key, key) == 0)
		{
			if (curr->value)
				free(curr->value);
			curr->value = ft_strdup(val);
			return ;
		}
		curr = curr->next;
	}
	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->key = ft_strdup(key);
	new->value = ft_strdup(val);
	new->next = *env;
	*env = new;
}

char	*get_env_value(t_env *env, const char *key)
{
	t_env	*curr;

	curr = env;
	while (curr)
	{
		if (curr->key && ft_strcmp(curr->key, key) == 0)
			return (curr->value);
		curr = curr->next;
	}
	return (NULL);
}

void	update_pwd_env(t_shell *shell, char *old_pwd)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return ;
	if (old_pwd)
		set_env_variable(&shell->environment, "OLDPWD", old_pwd);
	set_env_variable(&shell->environment, "PWD", new_pwd);
	free(new_pwd);
}