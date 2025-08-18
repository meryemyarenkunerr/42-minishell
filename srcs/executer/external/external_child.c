#include "../../../includes/minishell.h"

char	*create_env_string(char *key, char *val)
{
	char	*env_str;
	int		key_len;
	int		val_len;
	int		total_len;

	if (!key || !val)
		return (NULL);
	key_len = ft_strlen(key);
	val_len = ft_strlen(val);
	total_len = key_len + val_len + 2;
	env_str = malloc(total_len);
	if (!env_str)
		return (NULL);
	ft_strlcpy(env_str, key, total_len);
	ft_strlcpy(env_str, "=", total_len);
	ft_strlcpy(env_str, val, total_len);
	return (env_str);
}

int	fill_env_array(char **env_array, t_env *env)
{
	t_env	*curr;
	int		i;

	i = 0;
	curr = env;
	while (curr)
	{
		if (curr->key && curr->value)
		{
			env_array[i] = create_env_string(curr->key, curr->value);
			if (!env_array[i])
			{
				free_string_array_partial(env_array, i);
				return (FALSE);
			}
			i++;
		}
		curr = curr->next;
	}
	env_array[i] = NULL;
	return (TRUE);
}

char	**convert_env_to_array(t_env *env)
{
	char	**env_array;
	int		count;

	count = count_env_entries(env);
	env_array = malloc((count + 1) * sizeof(char *));
	if (!env_array)
		return (NULL);
	if (!fill_env_array(env_array, env))
	{
		free_string_array(env_array);
		return (NULL);
	}
	return (env_array);
}

void	execute_child_process(t_shell *shell, t_command *cmd, char *exec_path)
{
	char	**env_array;

	env_array = convert_env_to_array(shell->environment);
	if (!env_array)
	{
		perror("minishell: environment conversion failed");
		exit(127);
	}
	if (execve(exec_path, cmd->arguments, env_array) == -1)
	{
		handle_execve_error(cmd->cmd);
		free_string_array(env_array);
		exit(127);
	}
}