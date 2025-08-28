/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_waits.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuner <mkuner@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:35:22 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/28 15:36:43 by mkuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	wait_intermediate_processes(t_command *cmds)
{
	t_command	*cmd;
	int			status;
	pid_t		result;

	cmd = cmds;
	while (cmd && cmd->next)
	{
		if (cmd->pid > 0)
		{
			result = waitpid(cmd->pid, &status, WNOHANG);
			if (result == -1)
				perror("waitpid");
		}
		cmd = cmd->next;
	}
}

static int	wait_last_process(t_command *cmds)
{
	t_command	*cmd;
	int			status;
	int			last_exit_status;

	last_exit_status = 0;
	cmd = cmds;
	while (cmd && cmd->next)
		cmd = cmd->next;
	if (cmd && cmd->pid > 0)
	{
		waitpid(cmd->pid, &status, 0);
		if (WIFEXITED(status))
			last_exit_status = WEXITSTATUS(status);
		else
			last_exit_status = 128 + WTERMSIG(status);
	}
	return (last_exit_status);
}

static void	cleanup_other_processes(t_command *cmds, t_command *last)
{
	t_command	*cmd;

	cmd = cmds;
	while (cmd)
	{
		if (cmd->pid > 0 && cmd != last)
		{
			kill(cmd->pid, SIGTERM);
			waitpid(cmd->pid, NULL, 0);
		}
		cmd = cmd->next;
	}
}

void	wait_pipeline_processes(t_shell *shell, t_command *cmds,
	int cmd_count)
{
	int			last_status;
	t_command	*last_cmd;

	(void)cmd_count;
	wait_intermediate_processes(cmds);
	last_status = wait_last_process(cmds);
	last_cmd = cmds;
	while (last_cmd && last_cmd->next)
		last_cmd = last_cmd->next;
	cleanup_other_processes(cmds, last_cmd);
	shell->exit_status = last_status;
}
