/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:14:28 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/28 20:27:32 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	exec_pipeline_builtin(t_shell *shell, t_command *cmd,
	int **pipes)
{
	call_builtin_function(shell, cmd);
	if (cmd->fd_out > 1 && cmd->fd_out != STDOUT_FILENO)
		close(cmd->fd_out);
	if (cmd->fd_in > 0 && cmd->fd_in != STDIN_FILENO)
		close(cmd->fd_in);
	if (pipes && shell && shell->pipeline)
		cleanup_pipes(pipes, shell->pipeline->count - 1);
	free_at_exit(shell);
	exit(shell->exit_status);
}

static void	exec_pipeline_external(t_shell *shell, t_command *cmd,
	int **pipes)
{
	char	**env_array;
	char	*command_path;

	env_array = get_env_array(shell->environment);
	command_path = resolve_command_path(shell, cmd, env_array, pipes);
	if (execve(command_path, cmd->arguments, env_array) == -1)
	{
		free(command_path);
		free_string_array(env_array);
		if (pipes && shell && shell->pipeline)
			cleanup_pipes(pipes, shell->pipeline->count - 1);
		free_at_exit(shell);
		exit(127);
	}
}

static void	execute_pipeline_command(t_shell *shell, t_command *cmd,
	int **pipes)
{
	if (is_builtin_command(cmd->cmd))
		exec_pipeline_builtin(shell, cmd, pipes);
	else
		exec_pipeline_external(shell, cmd, pipes);
}

static void	execute_failed_pipeline_command(t_shell *shell, t_command *cmd,
	int **pipes)
{
	if (cmd->cmd == NULL && cmd->input_count == 0 && cmd->output_count == 0
		&& cmd->heredoc_count == 0)
		command_not_found_error(shell, "''");
	if (pipes && shell && shell->pipeline)
		cleanup_pipes(pipes, shell->pipeline->count - 1);
	free_at_exit(shell);
}

void	execute_pipeline_child(t_shell *shell, t_command *cmd,
	int **pipes, int idx)
{
	partial_cleanup_fds(pipes, shell->pipeline->count, idx);
	if (cmd->file_handler == 0 || cmd->cmd == NULL)
		execute_failed_pipeline_command(shell, cmd, pipes);
	else
		execute_pipeline_command(shell, cmd, pipes);
	exit(1);
}
