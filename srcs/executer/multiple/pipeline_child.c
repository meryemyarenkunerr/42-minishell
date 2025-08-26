/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:14:28 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/26 14:15:48 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include <unistd.h>

static void execute_builtin_pipeline(t_shell *shell, t_command *cmd, int **pipes)
{
	ft_putstr_fd("\nDEBUG BUILTIN: Starting built-in command: ", STDERR_FILENO);
	ft_putstr_fd(cmd->cmd, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	
	ft_putstr_fd("DEBUG BUILTIN: fd_in=", STDERR_FILENO);
	ft_putnbr_fd(cmd->fd_in, STDERR_FILENO);
	ft_putstr_fd(", fd_out=", STDERR_FILENO);
	ft_putnbr_fd(cmd->fd_out, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	
	ft_putstr_fd("DEBUG BUILTIN: Calling built-in function\n", STDERR_FILENO);
	call_builtin_function(shell, cmd);
	ft_putstr_fd("DEBUG BUILTIN: Built-in function completed\n", STDERR_FILENO);

	// Tüm dosya tanımlayıcılarını kapatmayı deneyelim
	ft_putstr_fd("DEBUG BUILTIN: Trying to close all possible file descriptors\n", STDERR_FILENO);
	
	// Standart output'u kapatma (opsiyonel bir test)
	if (cmd->fd_out > 0 && cmd->fd_out != STDOUT_FILENO) {
	    ft_putstr_fd("DEBUG BUILTIN: Closing cmd->fd_out\n", STDERR_FILENO);
	    close(cmd->fd_out);
	}
	
	// Standart input'u kapatma (opsiyonel bir test)
	if (cmd->fd_in > 0 && cmd->fd_in != STDIN_FILENO) {
	    ft_putstr_fd("DEBUG BUILTIN: Closing cmd->fd_in\n", STDERR_FILENO);
	    close(cmd->fd_in);
	}

	/* Cleanup resources before exit */
	ft_putstr_fd("DEBUG BUILTIN: Cleaning up resources\n", STDERR_FILENO);
	free_at_exit(shell);
	
	if (pipes && shell && shell->pipeline)
	{
		ft_putstr_fd("DEBUG BUILTIN: Cleaning up pipes\n", STDERR_FILENO);
		cleanup_pipes(pipes, shell->pipeline->count - 1);
	}
	
	ft_putstr_fd("DEBUG BUILTIN: Exit with status ", STDERR_FILENO);
	ft_putnbr_fd(shell->exit_status, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	
	// Standart çıkışları kapatmayı deneyelim
	ft_putstr_fd("DEBUG BUILTIN: Trying to close standard file descriptors\n", STDERR_FILENO);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	
	// Exit ile direkt çıkış yap (_exit kullan)
	_exit(shell->exit_status);
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
	// ft_putstr_fd("char *s", STDERR_FILENO);
	ft_putstr_fd("\nDEBUG: ", STDERR_FILENO);
    ft_putstr_fd(cmd->cmd, STDERR_FILENO);
    ft_putstr_fd(": fd_in -> ", STDERR_FILENO);
	if (idx >= 1)
    	ft_putnbr_fd(pipes[idx - 1][0], STDERR_FILENO);
    ft_putstr_fd(" ---- fd_out -> ", STDERR_FILENO);
	if (idx < cmd_count - 1)
    	ft_putnbr_fd(pipes[idx][1], STDERR_FILENO);
    ft_putstr_fd("\n", STDERR_FILENO);
	
	// Redirection sonrası cmd->fd_in ve cmd->fd_out değerleri 
	// artık STDIN_FILENO ve STDOUT_FILENO'dur.
	// O yüzden tekrar dup2 yapmaya gerek yok.
	
	if (is_builtin_command(cmd->cmd))
	{
		execute_builtin_pipeline(shell, cmd, pipes);
		// execute_builtin_pipeline fonksiyonu process'i exit ile sonlandırır
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
			       if (pipes && shell && shell->pipeline)
				       cleanup_pipes(pipes, shell->pipeline->count - 1);
			       _exit(127);
			}
		}
		execve(command_path, cmd->arguments, env_array);
		command_not_found_error(shell, cmd->cmd);
		free_at_exit(shell);
		free(command_path);
		free_string_array(env_array);
		if (pipes && shell && shell->pipeline)
			cleanup_pipes(pipes, shell->pipeline->count - 1);
		_exit(127);
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
       if (pipes && shell && shell->pipeline)
	       cleanup_pipes(pipes, shell->pipeline->count - 1);
       _exit(1);
}

void	execute_pipeline_child(t_shell *shell, t_command *cmd,
	int **pipes, int idx)
{
	ft_putstr_fd("\nDEBUG CHILD: Starting child process for command: ", STDERR_FILENO);
	ft_putstr_fd(cmd->cmd, STDERR_FILENO);
	ft_putstr_fd(", index=", STDERR_FILENO);
	ft_putnbr_fd(idx, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	
	if (cmd->file_handler == 0 || cmd->cmd[0] == '\0')
	{
		ft_putstr_fd("DEBUG CHILD: Command has invalid file handler or empty command\n", STDERR_FILENO);
		execute_failed_pipeline_command(shell, cmd, pipes, idx);
	}
	else
	{
		ft_putstr_fd("DEBUG CHILD: Executing pipeline command\n", STDERR_FILENO);
		execute_pipeline_command(shell, cmd, pipes, idx);
	}
	
	ft_putstr_fd("DEBUG CHILD: Child process reached end without executing - exiting\n", STDERR_FILENO);
	_exit(1); // exit yerine _exit kullan
}
