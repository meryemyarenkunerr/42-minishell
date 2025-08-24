/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:14:28 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/24 14:49:35 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	wait_for_child(t_shell *shell, pid_t pid)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
	{
		if (errno != ECHILD)
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
	{
		execute_child_process(shell, cmd, exec_path);
		exit(127);
	}
	return (pid);
}

void	execute_external(t_shell *shell, t_command *cmd)
{
	char	*exec_path;
	pid_t	pid;

	if (!shell || !cmd || !cmd->cmd)
		return ;
	if (cmd->cmd[0] == '\0')
		return ;
	exec_path = find_executable_path(shell, cmd->cmd);
	if (!exec_path)
	{
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
