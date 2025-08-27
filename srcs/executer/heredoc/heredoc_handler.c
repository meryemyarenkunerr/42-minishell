/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iaktas <iaktas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:14:28 by iaktas            #+#    #+#             */
/*   Updated: 2025/08/27 09:46:11 by iaktas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	execute_heredoc_parent(t_command *cmd, int fds[2])
{
	close(fds[1]);
	if (cmd->fd_in != STDIN_FILENO)
		close(cmd->fd_in);
	cmd->fd_in = fds[0];
}

static void	handle_heredoc_input(t_shell *shell, t_command *cmd, int fds[2])
{
	int	i;

	i = 0;
	g_sigint_received = IN_HEREDOC;
	handle_signals();
	while (i < cmd->heredoc_count && !is_heredoc_interrupted())
	{
		if (i == cmd->heredoc_count - 1)
			process_single_heredoc(shell, cmd->heredoc_delimiter[i], fds);
		else
			process_single_heredoc_ignore(shell,
				cmd->heredoc_delimiter[i], fds);
		i++;
	}
	g_sigint_received = AFTER_HEREDOC;
	handle_signals();
	close(fds[1]);
}

int	setup_heredoc_fds(t_shell *shell, t_command *cmd)
{
	int	pipe_fds[2];

	if (!cmd || cmd->heredoc_count == 0)
		return (TRUE);
	if (pipe(pipe_fds) == -1)
	{
		perror("pipe");
		return (FALSE);
	}
	handle_heredoc_input(shell, cmd, pipe_fds);
	execute_heredoc_parent(cmd, pipe_fds);
	return (TRUE);
}
