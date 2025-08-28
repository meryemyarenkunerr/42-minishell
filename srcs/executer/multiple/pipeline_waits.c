/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_waits.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuner <mkuner@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:35:22 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/28 12:53:55 by mkuner           ###   ########.fr       */
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
			fprintf(stderr, "PARENT: About to wait for %s (pid=%d)\n", cmd->arguments[0], cmd->pid);

			// Non-blocking wait dene
			result = waitpid(cmd->pid, &status, 0);
			if (result == 0) {
				// Process henüz bitmemiş, devam et
				fprintf(stderr, "PARENT: %s still running, skipping for now\n", cmd->arguments[0]);
			} else if (result > 0) {
				fprintf(stderr, "PARENT: %s (pid=%d) finished with status %d\n", cmd->arguments[0], cmd->pid, status);
			}
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
		fprintf(stderr, "PARENT: About to wait for LAST process %s (pid=%d)\n", cmd->arguments[0], cmd->pid);

		waitpid(cmd->pid, &status, 0);

		fprintf(stderr, "PARENT: LAST process %s finished with status %d\n", cmd->arguments[0], status);

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

	fprintf(stderr, "PARENT: Starting to wait for ALL processes\n");
	(void)cmd_count;
	wait_intermediate_processes(cmds);
	last_status = wait_last_process(cmds);
	last_cmd = cmds;
	while (last_cmd && last_cmd->next)
		last_cmd = last_cmd->next;
	cleanup_other_processes(cmds, last_cmd);
	shell->exit_status = last_status;

	fprintf(stderr, "PARENT: All processes finished, pipeline complete\n");
	fprintf(stderr, "PARENT: Returning to main shell loop\n");
}
