/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuner <mkuner@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:35:22 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/25 17:32:35 by mkuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	handle_child(t_shell *shell, t_command *cmd, int **pipes,
				int i)
{
	setup_pipeline_child(cmd, pipes, shell->pipeline->count, i);
	execute_pipeline_child(shell, cmd);
	free_single_command(cmd);
	free_at_exit(shell);
	exit(127);
}

int	skip_empty_command(pid_t *pids, t_command **cmd, t_pipeline_ctx *ctx)
{
	if (!cmd || !*cmd || !ctx || !pids)
		return (0);
	if (!(*cmd)->cmd || (*cmd)->cmd[0] == '\0')
	{
		(*cmd)->cmd = ft_strdup("/usr/bin/true");
		if (!(*cmd)->arguments)
		{
			(*cmd)->arguments = malloc(2 * sizeof(char *));
			if ((*cmd)->arguments)
			{
				(*cmd)->arguments[0] = ft_strdup("/bin/true");
				(*cmd)->arguments[1] = NULL;
			}
		}
		return (0);
	}
	return (0);
}

int	handle_pipe_error(int **pipes, int i)
{
	perror("pipe");
	free(pipes[i]);
	cleanup_partial_pipes(pipes, i);
	return (1);
}
