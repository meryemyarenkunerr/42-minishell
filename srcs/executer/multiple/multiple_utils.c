/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuner <mkuner@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:35:22 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/25 21:37:15 by mkuner           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	handle_child(t_shell *shell, t_command *cmd, int **pipes,
				int i)
{
	int cmd_count = shell->pipeline->count;

    // Eğer dosya açılmadıysa child sadece exit etsin
    if (cmd->file_handler == 0)
    {
        close_all_pipes_in_child(pipes, cmd_count);
        exit(1);
    }

    setup_pipeline_child(cmd, pipes, cmd_count, i);

    if (is_builtin_command(cmd->cmd))
    {
        execute_builtin(shell, cmd);
        exit(shell->exit_status);
    }
    else
        execute_external_in_pipeline(shell, cmd);
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

void	handle_pipe_error(int **pipes, int count)
{
	int	i;

	perror("pipe");
	i = 0;
	while (i < count)
	{
		if (pipes[i])
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
			free(pipes[i]);
		}
		i++;
	}
	free(pipes);
}
