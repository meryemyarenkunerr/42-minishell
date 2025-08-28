/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_child_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuner <mkuner@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:14:28 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/28 10:20:53 by mkuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*join_key_value(const char *key, const char *value)
{
	int		len;
	char	*str;

	len = ft_strlen(key) + 1;
	if (value)
		len += ft_strlen(value);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, key, len + 1);
	ft_strlcat(str, "=", len + 1);
	if (value)
		ft_strlcat(str, value, len + 1);
	return (str);
}

char	**get_env_array(t_env *environment)
{
	t_env	*env;
	char	**env_array;
	int		count;
	int		i;

	count = 0;
	env = environment;
	while (env)
	{
		count++;
		env = env->next;
	}
	env_array = malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	env = environment;
	i = 0;
	while (env && i < count)
	{
		env_array[i] = join_key_value(env->key, env->value);
		env = env->next;
		i++;
	}
	env_array[count] = NULL;
	return (env_array);
}

char	*resolve_command_path(t_shell *shell, t_command *cmd,
	char **env_array, int **pipes)
{
	char	*command_path;

	command_path = find_executable_path(shell, cmd->cmd);
	if (!command_path)
	{
		if (access(cmd->cmd, F_OK | X_OK) == 0)
			command_path = ft_strdup(cmd->cmd);
		if (!command_path)
		{
			if (env_array)
				free_string_array(env_array);
			command_not_found_error(shell, cmd->cmd);
			if (shell && shell->pipeline && pipes)
				cleanup_pipes(pipes, shell->pipeline->count - 1);
			free_at_exit(shell);
			exit(127);
		}
	}
	return (command_path);
}
