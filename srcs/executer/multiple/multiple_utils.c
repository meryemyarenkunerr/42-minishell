/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:35:22 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/24 13:56:52 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

//static void	handle_empty_command_child(t_command *cmd, t_pipeline_ctx *ctx)
//{
//	setup_pipeline_child(cmd, ctx->pipes, ctx->cmd_count, ctx->index);
//	free_at_exit(ctx->shell);
//	exit(0);
//}

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
	// NULL kontrolleri
	if (!cmd || !*cmd || !ctx || !pids)
		return (0);

	// Empty command kontrolü
	if (!(*cmd)->cmd || (*cmd)->cmd[0] == '\0')
	{
		// Empty command yerine /bin/true kullan
		(*cmd)->cmd = ft_strdup("/usr/bin/true");

		// Arguments da NULL ise boş array oluştur
		if (!(*cmd)->arguments)
		{
			(*cmd)->arguments = malloc(2 * sizeof(char *));
			if ((*cmd)->arguments)
			{
				(*cmd)->arguments[0] = ft_strdup("/bin/true");
				(*cmd)->arguments[1] = NULL;
			}
		}

		// Normal execution'a devam et (skip etme)
		return (0);
	}
	return (0);

	//if (!(*cmd)->cmd)
	//{
	//	pids[i] = 0;
	//	*cmd = (*cmd)->next;
	//	return (1);
	//}
	//return (0);
}

int	handle_pipe_error(int **pipes, int i)
{
	perror("pipe");
	free(pipes[i]);
	cleanup_partial_pipes(pipes, i);
	return (1);
}
