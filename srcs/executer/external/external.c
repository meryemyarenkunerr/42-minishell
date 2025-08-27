/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:14:28 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/27 02:53:13 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	wait_for_child(t_shell *shell, pid_t pid)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
	{
		perror("minishell: waitpid");
		shell->exit_status = 1;
		return ;
	}
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_status = 128 + WTERMSIG(status);
}

pid_t	fork_and_execute(t_shell *shell, t_command *cmd, char *exec_path)
{
	pid_t	pid;

	g_sigint_received = IN_CMD;
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		shell->exit_status = 1;
		return (-1);
	}
	if (pid == 0)
		execute_child_process(shell, cmd, exec_path);
	return (pid);
}

char	*current_directory(t_shell *shell, char *cmd)
{
	char	*current_dir;
	char	*temp_path;
	char	*exec_path;

	(void)shell;
	current_dir = getcwd(NULL, 0);
	temp_path = ft_strjoin(current_dir, "/");
	exec_path = ft_strjoin(temp_path, cmd);
	free(current_dir);
	free(temp_path);
	if (exec_path && access(exec_path, X_OK) == 0)
		return (exec_path);
	free(exec_path);
	return (NULL);
}

void	execute_external(t_shell *shell, t_command *cmd)
{
	char	*exec_path;
	pid_t	pid;

	if (!shell || !cmd || !cmd->cmd)
		return ;
	exec_path = find_executable_path(shell, cmd->cmd);
	if (!exec_path)
	{
		if (!access(cmd->cmd, F_OK))
		{
			perror("Permission denied");
			shell->exit_status = 126;	
		}
		else
			command_not_found_error(shell, cmd->cmd);
		return ;
	}
	pid = fork_and_execute(shell, cmd, exec_path);
	if (pid > 0)
		wait_for_child(shell, pid);
	free(exec_path);
	g_sigint_received = AFTER_CMD;
	handle_signals();
}
