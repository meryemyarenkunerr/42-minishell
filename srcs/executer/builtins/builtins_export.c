/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:35:22 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/25 12:21:57 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	process_mark_for_export(t_shell *shell, const char *key)
{
	char	*existing_val;

	if (!is_valid_identifier_export(key))
	{
		write(STDERR_FILENO, "minishell: export: `", 20);
		write(STDERR_FILENO, key, ft_strlen(key));
		write(STDERR_FILENO, "': not a valid identifier\n", 26);
		return (FALSE);
	}
	existing_val = get_env_value(shell->environment, key);
	if (existing_val)
		set_env_variable(&shell->environment, key, existing_val);
	else
		set_env_variable(&shell->environment, key, "");
	return (TRUE);
}

int	process_assignment(t_shell *shell, const char *arg, char *equal_pos)
{
	char	*key;
	int		key_len;
	char	*temp_val;

	temp_val = NULL;
	key_len = equal_pos - arg;
	key = ft_substr(arg, 0, key_len);
	if (!is_valid_identifier_export(key))
	{
		write(STDERR_FILENO, "minishell: export: `", 20);
		write(STDERR_FILENO, arg, ft_strlen(arg));
		write(STDERR_FILENO, "': not a valid identifier\n", 26);
		free(key);
		return (FALSE);
	}
	if (*(equal_pos + 1) == '\0')
	{
		temp_val = ft_strdup("\1");
		set_env_variable(&shell->environment, key, temp_val);
		free(temp_val);
	}
	else
		set_env_variable(&shell->environment, key, (equal_pos + 1));
	free(key);
	return (TRUE);
}

int	process_export_arguments(t_shell *shell, const char *arg)
{
	char	*equal_pos;

	equal_pos = ft_strchr(arg, '=');
	if (equal_pos)
		return (process_assignment(shell, arg, equal_pos));
	else
		return (process_mark_for_export(shell, arg));
}

void	print_export_variables(t_env *env)
{
	t_env	**env_array;
	int		count;
	int		i;

	count = count_env_keys(env);
	if (count == 0)
		return ;
	env_array = malloc(sizeof(t_env *) * count + 1);
	if (!env_array)
		return ;
	copy_env_to_array(env, env_array);
	sort_env_array(env_array, count);
	i = 0;
	while (i < count)
	{
		if (ft_strlen(env_array[i]->value) > 0)
			printf("declare -x %s=\"%s\"\n", env_array[i]->key,
				env_array[i]->value);
		else
			printf("declare -x %s\n", env_array[i]->key);
		i++;
	}
	free(env_array);
}

void	execute_builtin_export(t_shell *shell, t_command *cmd)
{
	int	i;
	int	error_flag;

	if (!cmd->arguments[1])
	{
		print_export_variables(shell->environment);
		shell->exit_status = 0;
		return ;
	}
	error_flag = 0;
	i = 1;
	while (cmd->arguments[i])
	{
		error_flag = process_export_arguments(shell, cmd->arguments[i]);
		i++;
	}
	if (error_flag == FALSE)
		shell->exit_status = 1;
	else
		shell->exit_status = 0;
}
