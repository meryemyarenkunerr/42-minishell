/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuner <mkuner@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:35:22 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/25 21:38:27 by mkuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	setup_pipeline_child(t_command *cmd, int **pipes,
	int cmd_count, int cmd_index)
{
	// stdin ve stdout yönlendirmesi
    if (cmd_index > 0 && cmd->fd_in == STDIN_FILENO)
        dup2(pipes[cmd_index - 1][0], STDIN_FILENO);

    if (cmd_index < cmd_count - 1 && cmd->fd_out == STDOUT_FILENO)
        dup2(pipes[cmd_index][1], STDOUT_FILENO);

    close_all_pipes_in_child(pipes, cmd_count);

    if (cmd->fd_in != STDIN_FILENO)
    {
        dup2(cmd->fd_in, STDIN_FILENO);
        close(cmd->fd_in);
    }
    if (cmd->fd_out != STDOUT_FILENO)
    {
        dup2(cmd->fd_out, STDOUT_FILENO);
        close(cmd->fd_out);
    }
}

static int	process_command_p(pid_t *pids, t_command **cmd, t_pipeline_ctx *ctx)
{
	//int	i;

	pids[ctx->index] = fork();
	if (pids[ctx->index] == -1)
	{
		perror("fork");
		// i = 0;
		// while (i < ctx->index)
		// {
		// 	if (pids[i] > 0)
		// 		waitpid(pids[i], NULL, 0);
		// 	i++;
		// }
		return (1);
	}
	if (pids[ctx->index] == 0)
	{
		handle_child(ctx->shell, *cmd, ctx->pipes, ctx->index);
		exit(127);
	}
	*cmd = (*cmd)->next;
	return (0);
}

pid_t	*execute_pipeline_processes(t_shell *shell, int **pipes, int cmd_count)
{
	pid_t			*pids;
	t_command		*cmd;
	t_pipeline_ctx	ctx;
	int				i;

	pids = malloc(cmd_count * sizeof(pid_t));
	if (!pids)
		return (NULL);
	ctx.shell = shell;
	ctx.pipes = pipes;
	ctx.cmd_count = cmd_count;
	cmd = shell->commands;
	i = 0;
	g_sigint_received = IN_CMD;
	while (i < cmd_count && cmd)
	{
		ctx.index = i;
		if (process_command_p(pids, &cmd, &ctx))
		{
			free(pids);
			return (NULL);
		}
		i++;
	}
	g_sigint_received = AFTER_CMD;
	handle_signals();
	return (pids);
}

int	**create_pipeline_pipes(int pipe_count)
{
	int **pipes;
    int i;

    if (pipe_count <= 0)
        return NULL;

    pipes = malloc(sizeof(int *) * pipe_count);
    if (!pipes)
        return NULL;

    for (i = 0; i < pipe_count; i++)
    {
        pipes[i] = malloc(sizeof(int) * 2);
        if (!pipes[i])
        {
            while (--i >= 0)
            {
                close(pipes[i][0]);
                close(pipes[i][1]);
                free(pipes[i]);
            }
            free(pipes);
            return NULL;
        }
        if (pipe(pipes[i]) == -1)
        {
            perror("pipe");
            while (i >= 0)
            {
                close(pipes[i][0]);
                close(pipes[i][1]);
                free(pipes[i]);
                i--;
            }
            free(pipes);
            return NULL;
        }
    }
    return pipes;
}
