/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas    <iaktas@student.42istanbul>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:14:28 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/23 15:14:28 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void execute_builtin_pipeline(t_shell *shell, t_command *cmd, int **pipes)
{
	write(STDERR_FILENO, "DEBUG BUILTIN START\n", 20);
	call_builtin_function(shell, cmd);
	write(STDERR_FILENO, "DEBUG BUILTIN END\n", 18);

	/* Cleanup resources before exit */
	free_at_exit(shell);
	if (pipes)
		free(pipes);
}

static char	**get_env_array(t_env *environment)
{
	t_env	*env;
	char	**env_array;
	int		count;
	int		i;

	/* Count environment variables */
	count = 0;
	env = environment;
	while (env)
	{
		count++;
		env = env->next;
	}
	/* Allocate array */
	env_array = malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	/* Fill array */
	env = environment;
	i = 0;
	while (env && i < count)
	{
		int key_len = ft_strlen(env->key);
		int val_len = env->value ? ft_strlen(env->value) : 0;
		env_array[i] = malloc(key_len + val_len + 2); /* key=value\0 */
		if (env_array[i])
		{
			ft_strlcpy(env_array[i], env->key, key_len + val_len + 2);
			ft_strlcat(env_array[i], "=", key_len + val_len + 2);
			if (env->value)
				ft_strlcat(env_array[i], env->value, key_len + val_len + 2);
			}
		env = env->next;
		i++;
	}
	env_array[count] = NULL;
	return (env_array);
}

static void	execute_pipeline_command(t_shell *shell, t_command *cmd,
	int **pipes, int idx)
{
	char	**env_array;
	int		cmd_count;
	char	*command_path;

	cmd_count = shell->pipeline->count;
	setup_pipeline_fds(cmd, pipes, idx, cmd_count);
	if (cmd->fd_in != STDIN_FILENO)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
			perror("dup2 input");
		close(cmd->fd_in);
	}
	if (cmd->fd_out != 1 && cmd->fd_out != STDOUT_FILENO)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			perror("dup2 output");
		close(cmd->fd_out);
	}
	if (is_builtin_command(cmd->cmd))
	{
		printf("builtins\n");
		execute_builtin_pipeline(shell, cmd, pipes);
		free_at_exit(shell);
		exit(shell->exit_status);
	}
	else
	{
		env_array = get_env_array(shell->environment);
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
				free_at_exit(shell);
				free(pipes);
				exit(127);
			}
		}
		execve(command_path, cmd->arguments, env_array);
		command_not_found_error(shell, cmd->cmd);
		free_at_exit(shell);
		free(command_path);
		free_string_array(env_array);
		free(pipes);
		exit(127);
	}
}

static void	execute_failed_pipeline_command(t_shell *shell, t_command *cmd,
	int **pipes, int idx)
{
	int		cmd_count;
	char	single_byte;

	cmd_count = shell->pipeline->count;
	setup_pipeline_fds(cmd, pipes, idx, cmd_count);
	if (idx > 0)
	{
		while (read(STDIN_FILENO, &single_byte, 1) > 1)
			;
	}
	if (cmd->cmd[0] == '\0')
		command_not_found_error(shell, "''");
	free_at_exit(shell);
	free(pipes);
	exit(1);
}

void	execute_pipeline_child(t_shell *shell, t_command *cmd,
	int **pipes, int idx)
{
	if (cmd->file_handler == 0 || cmd->cmd[0] == '\0')
		execute_failed_pipeline_command(shell, cmd, pipes, idx);
	else
		execute_pipeline_command(shell, cmd, pipes, idx);
	exit(1);
}
